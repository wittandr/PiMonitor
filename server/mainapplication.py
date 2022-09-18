from PyQt5 import uic, QtWidgets
from app import Server, DataSubject
import threading
import time


class MainApplication(QtWidgets.QMainWindow):

    def worker(self):
        while True:
            if self.data_subject.state == 1:
                self.lblStatus.setText("Ping received: " + self.data_subject.latency)
                self.data_subject.state = 0
            time.sleep(1)

    def __init__(self):
        super().__init__()
        uic.loadUi('FormFiles/main.ui', self)
        self.show()
        self.data_subject = DataSubject()
        server = Server(self.data_subject)
        server_thread = threading.Thread(target=server.run)
        server_thread.start()
        worker_thread = threading.Thread(target=self.worker)
        worker_thread.start()



