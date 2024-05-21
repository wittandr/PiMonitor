# grpc.py
# All gRPC specific code goes in here

from concurrent import futures
import logging
import datetime
import grpc
import ping_pb2, ping_pb2_grpc


class PingService(ping_pb2_grpc.PingServiceServicer):

    def __init__(self, data_subject):
        super(ping_pb2_grpc.PingServiceServicer, self).__init__()
        self.data_subject = data_subject

    def Ping(self, request, context):
        now = datetime.datetime.now()
        date_time = now.strftime("%m/%d/%Y, %H:%M:%S")
        print("Ping request at: ", date_time)
        self.data_subject.latency = date_time
        return ping_pb2.PingResponse(id=request.id)


class DataService(ping_pb2_grpc.DataServiceServicer):

    def __init__(self, data_subject):
        super(ping_pb2_grpc.DataServiceServicer, self).__init__()
        self.data_subject = data_subject

    def DataTransfer(self, request, context):
        if request.type == "cputemp":
            self.data_subject.cputemp = request.temp
        elif request.type == "gputemp":
            self.data_subject.gputemp = request.temp
        return ping_pb2.DataResponse(status="received")


