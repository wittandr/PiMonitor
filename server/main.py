from concurrent import futures
import logging
import datetime

import grpc
import ping_pb2
import ping_pb2_grpc


class PingService(ping_pb2_grpc.PingServiceServicer):

    def Ping(self, request, context):
        now = datetime.datetime.now()
        date_time = now.strftime("%m/%d/%Y, %H:%M:%S")
        print("Ping request at: ", date_time)
        return ping_pb2.PingResponse(id=request.id)


def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    server.add_insecure_port('[::]:50051')
    print(server)
    server.start()
    server.wait_for_termination()


if __name__ == '__main__':
    logging.basicConfig()
    serve()
