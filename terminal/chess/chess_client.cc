#include <condition_variable>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <mutex>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

#include <grpcpp/grpcpp.h>


#include "chess.v1.grpc.pb.h"

ABSL_FLAG(std::string, target, "localhost:5005", "Server address");

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using gmchess::GameChess;

using gmchess::PIECES;
using gmchess::Void;
using gmchess::Move;
using gmchess::MoveRecord;
using gmchess::MoveResult;
using gmchess::MoveHistory;


class GameChessClient{
public:

  GameChessClient(std::shared_ptr<Channel> channel):
    stub_(GameChess::NewStub(channel)) {}

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
  GameChessClient gcc(
    grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
  PIECES id = PIECES::BLACK_KING;
  std::string to = "df8";
  gcc.MakeMove(id, to);

  return 0;

}