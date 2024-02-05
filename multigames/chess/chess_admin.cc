#include "chess_net/server.h"


int RoomRegister(Room* new_r){

    int ret_stat = 0;

    int unique_id = 0;

    std::string new_room_name = new_r->room_name();

    std::string ro_name;

    std::string rc_name;

    std::string new_id;

    SERVER_MTX.lock();

    for(const auto& ro: ROOM_OPENED){

        ro_name = ro.second.room_name();

        if(new_room_name == ro_name){
            ret_stat = -2;
            break;
        }

    }

    if (ret_stat == 0){

    for(;unique_id < 10; unique_id++){

        new_id = GenRandomHexString(32);

        new_r->set_room_id(new_id);

        if(ROOM_OPENED.find(new_id) != ROOM_OPENED.end()){


            continue;

        }

        if(ROOM_CLOSED.find(new_id) != ROOM_CLOSED.end()){

            continue;

        }

        break;

    }

    } else{

        Loggerln<std::string>("room registry: failed to register: same room name already exists");

    }


    if (unique_id < 10 && ret_stat == 0){

        ROOM_OPENED.insert({new_id, *new_r});

        ret_stat = 1;

        Loggerln<std::string>("room registry: success for: " + new_room_name);

    } else if (unique_id >= 10) {

        new_r->set_room_id("");

        Loggerln<std::string>("room registry: failed to register: no available unique id");

        ret_stat = -1;

    } else {

        new_r->set_room_id("");

        Loggerln<std::string>("room registry: failed to register: error");

        ret_stat = -1;

    }


    SERVER_MTX.unlock();



    return ret_stat;
}


int MatchWatcher(Room* new_r, RoomResult* ret_rr){

    int ret_stat = 0;

    std::string room_id = new_r->room_id();

    SERVER_MTX.lock();

    if(ROOM_CLOSED.find(room_id) != ROOM_CLOSED.end()){

        ret_stat = 1;

    }

    if(ret_stat == 1){

        std::string poster_key = GenRandomHexString(32);

        ROOM_CLOSED[room_id].set_poster_key(poster_key);
    
        ret_rr->set_key(poster_key);

        *ret_rr->mutable_r() = *new_r;
    }


    SERVER_MTX.unlock();

    return ret_stat;
}




int MatchFinder(const Room* req_r, RoomResult* ret_rr){


    int ret_stat = 0;

    std::string ro_name;

    std::string query_room_id = req_r->room_id();

    std::string query_room_name = req_r->room_name();

    SIDE query_host_color = req_r->host_color();

    int query_match_timeout = req_r->match_timeout();

    int query_move_timeout = req_r->move_timeout();

    std::string target_room_id;
    std::string target_room_name; 
    SIDE target_host_color;
    int target_match_timeout;
    int target_move_timeout;

    Room matching_r;
    RoomLock rl;
    RoomStatus rs;

    SERVER_MTX.lock();


    for(const auto& ro: ROOM_OPENED){

        target_room_id = ro.second.room_id();
        target_room_name = ro.second.room_name();

        target_host_color = ro.second.host_color();
        target_match_timeout = ro.second.match_timeout();
        target_move_timeout = ro.second.move_timeout();

        if(target_room_id == query_room_id){

            ret_stat = 1;

            matching_r = ro.second;
            
            break;

        }

        if(target_room_name == query_room_name){
            
            ret_stat = 1;

            matching_r = ro.second;

            break;
        }



        if(
            target_host_color == query_host_color &&
            target_match_timeout >= query_match_timeout &&
            target_move_timeout >= query_move_timeout 
        ){
            ret_stat = 1;
            matching_r = ro.second;
            break;
        }

    }

    if (ret_stat == 1){

        std::string joiner_key = GenRandomHexString(32);

        ROOM_OPENED.erase(target_room_id);

        *rl.mutable_r() = matching_r;

        rl.set_joiner_key(joiner_key);

        ROOM_CLOSED.insert({target_room_id, rl});

        *rs.mutable_r() = matching_r;

        ROOM_CLOSED_STATUS.insert({target_room_id, rs});

        Loggerln<std::string>("matching room [" + target_room_name + "] status changed: locked");

        Room ret_r;
        ret_r.set_room_id(target_room_id);
        ret_r.set_room_name(target_room_name);
        ret_r.set_host_color(target_host_color);
        ret_r.set_match_timeout(target_match_timeout);
        ret_r.set_move_timeout(target_move_timeout);

        ret_rr->set_key(joiner_key);
        *ret_rr->mutable_r() = ret_r;

        Loggerln<std::string>("matching room [" + target_room_name + "] status: ready");


    } else{
        Loggerln<std::string>("matching room not found");
    }

    SERVER_MTX.unlock();

    return ret_stat;
}



TALK AuthIncomingRequest(Move* req_mv){


    TALK ret_stat;

    
    std::string room_id = req_mv->room_id();

    std::string key = req_mv->key();

    int auth_flag = AuthCheckIfValidTurn(room_id, key);

    if(auth_flag < 1){

        Loggerln<std::string>("authentication failure: " + std::to_string(auth_flag)); 

        ret_stat = TALK::EAUTH;

        return ret_stat;

    }
    
    Loggerln<std::string>("authentication success: " + std::to_string(auth_flag));

    ret_stat = TALK::MATCH;


    return ret_stat;
}

int AuthCheckIfValidTurn(std::string room_id, std::string key){

    int ret_stat;

    std::string log_str;

    SERVER_MTX.lock();

    if(ROOM_CLOSED.find(room_id) == ROOM_CLOSED.end()){

        Loggerln<std::string>("couldn't find room lock for room id: " + room_id);

        SERVER_MTX.unlock();

        return -1;
    }

    if(ROOM_CLOSED_STATUS.find(room_id) == ROOM_CLOSED_STATUS.end()){


        Loggerln<std::string>("couldn't find room lock status for room id: " + room_id);

        SERVER_MTX.unlock();

        return -2;

    }


    int is_poster_key = 0;

    int is_poster_white = 0;

    int opening = 0;

    int white_turn = 0;



    RoomLock* rl = &ROOM_CLOSED[room_id];

    RoomStatus* rs = &ROOM_CLOSED_STATUS[room_id];    

    if(rl->poster_key() == key){

        is_poster_key = 1;

    } else if(rl->joiner_key() == key){

        is_poster_key = 0;
    
    } else {

        log_str = "invalid key: " + key + ", for room id: " + room_id; 

        Loggerln<std::string>(log_str);

        SERVER_MTX.unlock();

        return -3;

    } 


    Room* r = rl->mutable_r();

    SIDE host_color = r->host_color();

    if(host_color == SIDE::WHITE){
        is_poster_white = 1;
    } else {
        is_poster_white = 0;
    }


    MoveHistory* mv_hist = rs->mutable_move_history();
    
    int mv_hist_size = mv_hist->move_history_size();

    if(mv_hist_size == 0){

        Loggerln<std::string>("opening move for white");

        opening = 1;

        if(is_poster_white == 1 && is_poster_key != 1){

            Loggerln<std::string>("host should open, but guest tried to open");

            SERVER_MTX.unlock();

            return -4;

        } else if (is_poster_white == 0 && is_poster_key == 1){

            Loggerln<std::string>("guest should open, but host tried to open");

            SERVER_MTX.unlock();

            return -5;

        }

    }


    if(opening == 1){
        return 0;
    }


    MoveRecord* mv_last = rs->mutable_move_last();

    PIECES piece_id = mv_last->id();

    int piece_id_int = (int)piece_id;

    if(piece_id_int < 15){

                


    } else {




    }




    



    SERVER_MTX.unlock();


    return 1;

}


int ConstructLeaveReport(GG* req_gg, Report* ret_rep){


    int ret_stat;




    return ret_stat;

}