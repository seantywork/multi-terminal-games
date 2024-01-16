#include "chess_net/server.h"




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