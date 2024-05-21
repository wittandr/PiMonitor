from PyQt5 import uic, QtWidgets
from PyQt5.QtGui import QPalette, QColor
from PyQt5.QtCore import Qt
from app import Server, DataSubject
import threading
import time
import platform


class MainApplication(QtWidgets.QMainWindow):

    def worker(self):
        while True:
            self.lblStatus.setText("Ping received: " + str(self.data_subject.latency))
            self.lcdCPUTemp.display(self.data_subject.cputemp)
            self.lcdGPUTemp.display(self.data_subject.gputemp)
            self.data_subject.state = 0
            time.sleep(1)

    def __init__(self):
        super().__init__()
        uic.loadUi('FormFiles/main.ui', self)
        # Now use a palette to switch to dark colors:
        palette = QPalette()
        palette.setColor(QPalette.Window, QColor(53, 53, 53))
        palette.setColor(QPalette.WindowText, Qt.white)
        palette.setColor(QPalette.Base, QColor(25, 25, 25))
        palette.setColor(QPalette.AlternateBase, QColor(53, 53, 53))
        palette.setColor(QPalette.ToolTipBase, Qt.black)
        palette.setColor(QPalette.ToolTipText, Qt.white)
        palette.setColor(QPalette.Text, Qt.white)
        palette.setColor(QPalette.Button, QColor(53, 53, 53))
        palette.setColor(QPalette.ButtonText, Qt.white)
        palette.setColor(QPalette.BrightText, Qt.red)
        palette.setColor(QPalette.Link, QColor(42, 130, 218))
        palette.setColor(QPalette.Highlight, QColor(42, 130, 218))
        palette.setColor(QPalette.HighlightedText, Qt.black)
        self.setPalette(palette)
        if platform.machine() == "AMD64":
            self.show()
        else:
            self.showFullScreen()
        self.data_subject = DataSubject()
        server = Server(self.data_subject)
        server_thread = threading.Thread(target=server.run)
        server_thread.start()
        worker_thread = threading.Thread(target=self.worker)
        worker_thread.start()



