# app.py

from concurrent import futures
import grpc

import ping_pb2_grpc
from grpc_impl import PingService


class Server:

    @staticmethod
    def run():
        server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
        ping_pb2_grpc.add_PingServiceServicer_to_server(PingService(), server)
        server.add_insecure_port('[::]:50051')
        print(server)
        server.start()
        server.wait_for_termination()