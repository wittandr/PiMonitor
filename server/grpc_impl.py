# grpc.py
# All gRPC specific code goes in here

from concurrent import futures
import logging
import datetime

import grpc
import ping_pb2, ping_pb2_grpc


class PingService(ping_pb2_grpc.PingServiceServicer):

    def Ping(self, request, context):
        now = datetime.datetime.now()
        date_time = now.strftime("%m/%d/%Y, %H:%M:%S")
        print("Ping request at: ", date_time)
        return ping_pb2.PingResponse(id=request.id)

