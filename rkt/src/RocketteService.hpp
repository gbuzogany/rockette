#ifndef DashService_hpp
#define DashService_hpp

#include <stdio.h>
#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>
#include "rkt/proto/rkt.grpc.pb.h"


using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;
using rkt::RocketteService;
using rkt::IntValue;
using rkt::FloatValue;
using rkt::StringValue;
using rkt::BytesValue;
using rkt::StatusResponse;

class RocketteServiceImpl final : public RocketteService::Service {
public:
    RocketteServiceImpl();
    
    int getIntValue(std::string identifier, int& result);
    int getIntValueAsString(std::string identifier, std::string& result);
    int getFloatValue(std::string identifier, float& result);
    int getFloatValueAsString(std::string identifier, std::string& result, int precision = 0);
    int getStringValue(std::string identifier, std::string& result);
    int getBytesValue(std::string identifier, std::string& result);
    
private:
    
    std::map<std::string, int> intValues;
    std::map<std::string, float> floatValues;
    std::map<std::string, std::string> stringValues;
    std::map<std::string, std::string> byteValues;
    
    Status UpdateIntData(ServerContext* context, const IntValue* request, StatusResponse* response);
    Status UpdateFloatData(ServerContext* context, const FloatValue* request, StatusResponse* response);
    Status UpdateStringData(ServerContext* context, const StringValue* request, StatusResponse* response);
    Status UpdateBytesData(ServerContext* context, const BytesValue* request, StatusResponse* response);
};

#endif /* DashService_hpp */
