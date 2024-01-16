
#include "chess_net/server.h"


ABSL_FLAG(uint16_t, port, 5005, "Server port for the chess service");

std::mutex SERVER_MTX;

std::map<std::string, Room> ROOM_OPENED;

std::map<std::string, RoomLock> ROOM_CLOSED;





class GameChessServiceImpl final: public GameChess::Service{


    Status PostRoom(ServerContext* context, const Room* request,
                    ServerWriter<RoomResult>* reply_writer) override {
        
        int room_created = 0;

        int match_found = 0; 

        int lapsed_sec = 0;

        Room new_r;

        RoomResult r_res;

        int match_timeout = request->match_timeout();

        if (match_timeout > MAX_TIMEOUT_SECONDS){
          match_timeout = MAX_TIMEOUT_SECONDS;
        }

        new_r.set_room_id(request->room_id());
        new_r.set_room_name(request->room_name());
        new_r.set_host_color(request->host_color());
        new_r.set_match_timeout(request->match_timeout());
        new_r.set_move_timeout(request->move_timeout());


        room_created = RoomRegister(&new_r);

        if(room_created < 1){

          r_res.set_status(TALK::ABORT);

          reply_writer->Write(r_res);

          return Status::CANCELLED;
        }

        auto t_start = std::chrono::high_resolution_clock::now();

        
        for (;;){

          r_res.set_status(TALK::WAIT);

          reply_writer->Write(r_res);

          lapsed_sec = GetTimeDiffSeconds(t_start);

          if (lapsed_sec > match_timeout){
            
            r_res.set_status(TALK::TIMEOUT);

            reply_writer->Write(r_res);

            return Status::CANCELLED;
          }

          match_found = MatchWatcher(&new_r, &r_res); 

          if(match_found == 1){

            r_res.set_status(TALK::MATCH);

            reply_writer->Write(r_res);

            break;
          }

        }


        return Status::OK;
    }

    Status JoinRoom(ServerContext* context, const Room* request,
                    ServerWriter<RoomResult>* reply_writer){

        int match_found = 0; 

        int lapsed_sec = 0;

        int match_timeout = request->match_timeout();

        if (match_timeout > MAX_TIMEOUT_SECONDS){
          match_timeout = MAX_TIMEOUT_SECONDS;
        }

        RoomResult r_res;

        auto t_start = std::chrono::high_resolution_clock::now();

        for(;;){

          r_res.set_status(TALK::WAIT);

          reply_writer->Write(r_res);

          lapsed_sec = GetTimeDiffSeconds(t_start);

          if (lapsed_sec > match_timeout){
            
            r_res.set_status(TALK::TIMEOUT);

            reply_writer->Write(r_res);

            return Status::CANCELLED;
          }

          match_found = MatchFinder(request, &r_res); 

          if(match_found == 1){

            r_res.set_status(TALK::MATCH);

            reply_writer->Write(r_res);

            break;
          }

        }


        return Status::OK;
    }

    Status MakeMove(ServerContext* context, const Move* request,
                    MoveResult* reply) override {

        Move req_mv = *request;

        MoveRecord mrec;

        PrintReqMove(&req_mv);

        SetMoveResult(reply);

        std::cout << "set move result success " << std::endl; 

        SetMoveRecord(&mrec, &req_mv, reply);

        std::cout << "set move record success" << std::endl;

        int retcode = AddToMoveHistory(&mrec);

        if(retcode == 0){

          std::cout << "add to move history success" << std::endl;

          return Status::OK;


        } else {

          return Status::CANCELLED;
        }

    }


};


void RunServer(uint16_t port){

  std::string server_address = absl::StrFormat("0.0.0.0:%d", port);
  GameChessServiceImpl service;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  ServerBuilder builder;

  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

  builder.RegisterService(&service);

  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Game Chess Server listening on " << server_address << std::endl;

  server->Wait();

}



int main (int argc, char** argv){

  InitRandomDevice();

  absl::ParseCommandLine(argc, argv);
  RunServer(absl::GetFlag(FLAGS_port));
  return 0;
}