This tests explains how to build and run the unit tests. Qt5 and qmake are required for the tests to work. The following commands should be ran from a Linux terminal.

HOW TO BUILD:

	cd <INSTALLED_DIR>/CS206/unittests
	qmake -project "QT += testlib" "QMAKE_CXXFLAGS += -std=c++11"
	qmake
	make

HOW TO RUN:

	./unittests
