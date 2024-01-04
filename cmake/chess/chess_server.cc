
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "chess.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using chess::PIECES;
using chess::Void;
using chess::Move;
using chess::MoveResult;
using chess::MoveHistory;

ABSL_FLAG(uint16_t, port, 5005, "Server port for the chess service");


class ChessServiceImpl final: public Chess::Service{

    Status MakeMove(ServerContext* context, const Move* request,
                    MoveResult* reply) override {
        
        int piece_id = request->id();
        std::string to = request->to();
        MoveResult mr = request->result();

        


    }


}