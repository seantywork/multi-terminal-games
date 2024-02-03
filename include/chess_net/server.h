#ifndef _CHESS_GRPC_SERVER_H_
#define _CHESS_GRPC_SERVER_H_

#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include <fstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

#include <random>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "chess.v1.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerWriter;
using grpc::Status;

using gmchess::GameChess;

using gmchess::TALK;
using gmchess::SIDE;
using gmchess::PIECES;

using gmchess::Room;
using gmchess::RoomLock;
using gmchess::RoomResult;


using gmchess::Void;

using gmchess::Move;
using gmchess::MoveRecord;
using gmchess::MoveResult;
using gmchess::MoveHistory;

using gmchess::GG;
using gmchess::Report;

void InitRandomDevice();

int GetTimeDiffSeconds(std::chrono::time_point<std::chrono::high_resolution_clock> t_start);

std::string GetStringTimeNow();

std::string GenRandomHexString(int keysize);

int RoomRegister(Room* new_r);

int MatchWatcher(Room* new_r, RoomResult* ret_rr);

int MatchFinder(const Room* req_r, RoomResult* ret_rr);


TALK AuthIncomingRequest(Move* req_mv);

TALK ChessMove(Move* req_mv, MoveRecord* mr_res, MoveResult* mv_result);

TALK WatchChessMove(Move* req_mv, MoveRecord* watch_mr_res, MoveResult* watch_mv_result);

void PrintReqMove(Move* mv);

void SetMoveResult(MoveResult* mr);

void SetMoveRecord(MoveRecord* mrec, Move* mv, MoveResult* mr);

int AddToMoveHistory(MoveRecord* mrec);


int ConstructLeaveReport(GG* req_gg, Report* ret_rep);

#define MAX_TIMEOUT_SECONDS 60



extern std::mutex SERVER_MTX;

extern std::map<std::string, Room> ROOM_OPENED;

extern std::map<std::string, RoomLock> ROOM_CLOSED;

extern std::random_device RD;
extern std::mt19937 RANDEV;


template <typename T> void Loggerln(T msg){


    std::string now_str = GetStringTimeNow();

    now_str = "[ " + now_str + " ] ";


    std::cout << now_str <<  msg << std::endl;


}

#endif