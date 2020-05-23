import grpc
import rkt_pb2
import rkt_pb2_grpc

class RocketteClient:
	def __init__(self, config):
		self.config = config
		self.host_string = '{0}:{1}'.format(self.config['host'], self.config['port'])
		self.channel = grpc.insecure_channel(self.host_string)

	def UpdateDashIntData(self, intValue):
		stub = rkt_pb2_grpc.RocketteServiceStub(self.channel)
		response = stub.UpdateIntData(intValue)
		return response

	def UpdateFloatData(self, floatValue):
		stub = rkt_pb2_grpc.RocketteServiceStub(self.channel)
		response = stub.UpdateFloatData(floatValue)
		return response

	def UpdateStringData(self, stringValue):
		stub = rkt_pb2_grpc.RocketteServiceStub(self.channel)
		response = stub.UpdateStringData(stringValue)
		return response

	def UpdateBytesData(self, bytesValue):
		stub = rkt_pb2_grpc.RocketteServiceStub(self.channel)
		response = stub.UpdateBytesData(bytesValue)
		return response
