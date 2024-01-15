#ifndef _CHESS_GRPC_SERVER_H_
#define _CHESS_GRPC_SERVER_H_

#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include <fstream>
#include <iomanip>
#include <ctime>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "chess.v1.grpc.pb.h"

#endif