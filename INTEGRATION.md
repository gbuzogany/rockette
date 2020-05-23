# Rockette example gRPC integration

## Introduction

Rockette comes with a basic example of a gRPC integration. The interface is described in `rkt/proto/rkt.proto`, which describes the `RocketteService`. This allows applications written in any of the languages supported by gRPC to send/receive data from the Rockette application, on the same host or through the network.

## RocketteService

Looking at `rkt/proto/rkt.proto`, we have:

```
service RocketteService {
  rpc UpdateIntData (IntValue) returns (StatusResponse) {}
  rpc UpdateFloatData (FloatValue) returns (StatusResponse) {}
  rpc UpdateStringData (StringValue) returns (StatusResponse) {}
  rpc UpdateBytesData (BytesValue) returns (StatusResponse) {}
}
```
Each of these methods receive an argument with an `identifier` (string), and a `value` (with matching types).

This service is implemented in `src/RocketteService.cpp`. This file contains the class responsible for handling the RPC calls. The base implementation has a `std::map<string, type>` for each type, and stores the `value` with the `identifier` key. These can then be retrieved from the `RocketteService` class through the public accessor methods:

```
int getIntValue(std::string identifier, int& result);
int getIntValueAsString(std::string identifier, std::string& result);
int getFloatValue(std::string identifier, float& result);
int getFloatValueAsString(std::string identifier, std::string& result, int precision = 0);
int getStringValue(std::string identifier, std::string& result);
int getBytesValue(std::string identifier, std::string& result);
```

This way you can retrieve data sent to your graphical application by other applications.

## Generating gRPC code, a Python example

To create a new application that's able to make RPC calls in our Rockette application, you should generate the base implementation from the `rkt.proto` file.

First, make sure you have all the dependencies described by the [documentation](https://grpc.io/docs/quickstart/python/).

Then, from `rkt/proto/`, run:

```
python -m grpc_tools.protoc -I. --python_out=. --grpc_python_out=. rkt.proto
```

This command will generate two new files: `rkt_pb2_grpc.py` and `rkt_pb2.py`. You will need to update these files every time the `rkt.proto` file is modified.

In `integration/examples/python`, there is an example of how to use these files to make RPC calls. Make sure to update the `config.json` file to connect to the correct host.

To run the `rkt-control` example, run:

```
python main.py
```