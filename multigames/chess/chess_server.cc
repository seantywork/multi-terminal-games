
#include "chess_server.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerWriter;
using grpc::Status;

using gmchess::GameChess;

using gmchess::PIECES;

using gmchess::Room;
using gmchess::RoomResult;
using gmchess::RoomRequest;
using gmchess::RoomResponse;

using gmchess::Void;

using gmchess::Move;
using gmchess::MoveRecord;
using gmchess::MoveResult;
using gmchess::MoveHistory;

ABSL_FLAG(uint16_t, port, 5005, "Server port for the chess service");

std::string GetStringTimeNow(){



    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    std::string ts = oss.str();


    return ts;

}



void PrintReqMove(Move* mv){


  int piece_id = mv->id();
  std::string to = mv->to();

  std::cout<< "client piece id: " << piece_id << std::endl;
  std::cout<< "client move: " << to << std::endl;

}

void SetMoveResult(MoveResult* mr){

  mr->set_success(true);
  mr->set_resolve_time_stamp(GetStringTimeNow());

}


void SetMoveRecord(MoveRecord* mrec, Move* mv, MoveResult* mr){

  int step = 0;
  PIECES id = mv->id();
  std::string to = mv->to();

  mrec->set_step(step);
  mrec->set_id(id);
  mrec->set_to(to);
  *mrec->mutable_result() = *mr;

}


int AddToMoveHistory(MoveRecord* mrec){


  MoveHistory mhist;

  std::string bin_path = "bin/history.bin";

  std::fstream input(bin_path, std::ios::in | std::ios::binary);

  if(!input){
    std::cout << "Creating new at: " << bin_path << std::endl; 
  } else if (!mhist.ParseFromIstream(&input)) {
    std::cerr << "Failed parsing from :" << bin_path << std::endl;
    return -1;
  }

  auto new_mrec = mhist.add_move_history();

  new_mrec->set_step(mrec->step());
  new_mrec->set_id(mrec->id());
  new_mrec->set_to(mrec->to());
  *new_mrec->mutable_result() = *mrec->mutable_result();

  std::fstream output(bin_path, std::ios::out | std::ios::trunc | std::ios::binary);
  if(!mhist.SerializeToOstream(&output)){
    std::cerr << "Failed writing to: " << bin_path << std::endl;
    return -1;
  }

  return 0;
}

class GameChessServiceImpl final: public GameChess::Service{

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

    Status PostRoom(ServerContext* context, const Room* request,
                    ServerWriter<RoomResult>* reply) override {

          // write search function

          // write status until match is made

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

  absl::ParseCommandLine(argc, argv);
  RunServer(absl::GetFlag(FLAGS_port));
  return 0;
}