#!/usr/bin/env python3
# __main__.py

from PyQt5 import QtWidgets
from mainapplication import MainApplication
import sys

if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    window = MainApplication()
    app.exec_()
