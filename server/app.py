# app.py

from concurrent import futures
from grpc_impl import PingService
from typing import List
import grpc
import ping_pb2_grpc
import threading

def locked(func):
    def wrap(*args, **kwargs):
        lock = threading.Lock()
        lock.acquire()
        func(*args, **kwargs)
        lock.release()
    return wrap


class DataSubject:
    gputemp = 0
    cputemp = 0
    latency = 0
    state = 0

    @locked
    def update_gpu_temp(self, temp):
        self.gputemp = temp
        self.state = 1

    @locked
    def update_cpu_temp(self, temp):
        self.cputemp = temp
        self.state = 1

    @locked
    def update_latency(self, latency):
        self.latency = latency
        self.state = 1

    def get_latency(self):
        return self.latency


class Server:
    def __init__(self, data_subject):
        self.data_subject = data_subject

    def run(self):
        server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
        ping_pb2_grpc.add_PingServiceServicer_to_server(PingService(self.data_subject), server)
        server.add_insecure_port('[::]:50051')
        print(server)
        server.start()
        server.wait_for_termination()

