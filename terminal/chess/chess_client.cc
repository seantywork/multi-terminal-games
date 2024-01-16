
#include "chess_net/client.h"

ABSL_FLAG(std::string, target, "localhost:5005", "Server address");



class GameChessClient{
public:

  GameChessClient(std::shared_ptr<Channel> channel):
    stub_(GameChess::NewStub(channel)) {}

  int PostRoom(std::string room_name, SIDE host_color, int match_timeout, int move_timeout){

    int post_result = 0;

    ClientContext context;

    Room request;

    request.set_room_name(room_name);

    request.set_host_color(host_color);

    request.set_match_timeout(match_timeout);

    request.set_move_timeout(move_timeout);

    RoomResult reply_written;

    std::unique_ptr<ClientReader<RoomResult>> reader(
      stub_->PostRoom(&context, request)
    );

    std::cout << "receiving message *** " << std::endl;

    while(reader->Read(&reply_written)){ 
      continue;
    }

    std::cout << "received message *** " << std::endl;

    std::cout << "status: " <<  reply_written.status() << std::endl;

    std::cout << "key: " <<  reply_written.key() << std::endl;

    Room* resp_r = reply_written.mutable_r();

    std::cout << "room_id: " << resp_r->room_id() << std::endl;

    std::cout << "room_name: " << resp_r->room_name() << std::endl;

    std::cout << "host_color: " << resp_r->host_color() << std::endl;

    std::cout << "match_timeout: " << resp_r->match_timeout() << std::endl;

    std::cout << "move_timeout: " << resp_r->move_timeout() << std::endl; 


    Status status = reader->Finish();

    if(status.ok()){
      post_result = 1;
      Loggerln<std::string>("room post successful");
    } else{
      Loggerln<std::string>("room post failed");
    }

    return post_result;

  }

  int JoinRoom(std::string room_name, SIDE host_color, int match_timeout, int move_timeout){

    int join_result = 0;

    ClientContext context;

    Room request;

    request.set_room_name(room_name);

    request.set_host_color(host_color);

    request.set_match_timeout(match_timeout);

    request.set_move_timeout(move_timeout);

    RoomResult reply_written;

    std::unique_ptr<ClientReader<RoomResult>> reader(
      stub_->JoinRoom(&context, request)
    );

    std::cout << "waiting for a room to join *** " << std::endl;

    while(reader->Read(&reply_written)){ 
      continue;
    }

    std::cout << "received message *** " << std::endl;

    std::cout << "status: " <<  reply_written.status() << std::endl;

    std::cout << "key: " <<  reply_written.key() << std::endl;

    Room* resp_r = reply_written.mutable_r();

    std::cout << "room_id: " << resp_r->room_id() << std::endl;

    std::cout << "room_name: " << resp_r->room_name() << std::endl;

    std::cout << "host_color: " << resp_r->host_color() << std::endl;

    std::cout << "match_timeout: " << resp_r->match_timeout() << std::endl;

    std::cout << "move_timeout: " << resp_r->move_timeout() << std::endl;

    Status status = reader->Finish();

    if(status.ok()){
      join_result = 1;
      Loggerln<std::string>("joined");
    } else{
      Loggerln<std::string>("failed to join");
    }

    return join_result; 
  }
  

  void MakeMove(PIECES id, std::string to){

    Move request;

    request.set_id(id);
    request.set_to(to);

    MoveResult reply;


    ClientContext context;


    Status status = stub_->MakeMove(&context, request, &reply);

    if(status.ok()){
      std::cout<< "success: "<< reply.success() << std::endl;
      std::cout<< "resolve timestamp: " << reply.resolve_time_stamp() << std::endl;

    } else {
      std::cout << status.error_code() << ": " << status.error_message()
            << std::endl;
      std::cout << "RPC failed" << std::endl;
    }

  }


private:

  std::unique_ptr<GameChess::Stub> stub_;

};



int main (int argc, char** argv){

  absl::ParseCommandLine(argc, argv);
  std::string target_str = absl::GetFlag(FLAGS_target);


  std::stringstream str_stream;
/*
  std::string key;
  std::ifstream key_file;

  std::string cert;
  std::ifstream cert_file;
*/
  std::string ca;
  std::ifstream ca_file;

/*
  key_file.open("server.key");
  str_stream << key_file.rdbuf();
  key = str_stream.str();
  key_file.close();

  cert_file.open("server.pem");
  str_stream<< cert_file.rdbuf();
  cert = str_stream.str();
  cert_file.close();
*/
  ca_file.open("ca.pem");
  str_stream << ca_file.rdbuf();
  ca = str_stream.str();
  ca_file.close();

  grpc::SslCredentialsOptions ssl_opt = {
    ca
  };


  GameChessClient gcc(
    grpc::CreateChannel(target_str, grpc::SslCredentials (ssl_opt)));


  std::string target = argv[1];

  if(target == "post"){

    int ret_code = gcc.PostRoom("myroom-hi", SIDE::BLACK, 30, 30);
    
  } else if(target == "join"){

    int ret_codde = gcc.JoinRoom("myroom-hi", SIDE::WHITE, 30, 30);

  } else if(target == "make-move"){

    PIECES id = PIECES::BLACK_KING;
    std::string to = "df8";
    gcc.MakeMove(id, to);

  } else {

    std::cout << "wrong argument: " << target << std::endl;
 
  }


  return 0;

}