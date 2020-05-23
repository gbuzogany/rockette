import json
import rkt_pb2
import socket

from RocketteClient import RocketteClient

config_file = 'config.json'

if __name__ == '__main__':

	with open(config_file) as data_file:
		config = json.load(data_file)

	rkt = RocketteClient(config)

	hostname = socket.gethostname()
	ip_address = socket.gethostbyname(hostname)

	stringData = rkt_pb2.StringValue(
				value="My IP is "+ip_address,
				identifier='message',
			)

	rkt.UpdateStringData(stringData)


