CXX=g++
BD=build
FPRO=SmartCalcV2.pro
APP=$(BD)/SmartCalcV2.app
MDL=src/model/
CTL=src/controller/
VIW=src/view/
SUP=--suppress=
TFILE=src/test.cpp
TFLAGS=-lgtest -lpthread
GFLAGS=--coverage -fprofile-arcs -ftest-coverage
STD=--std=c++17

SOURCES=$(MDL)calculator_model.cpp \
		$(MDL)credit_model.cpp \
		$(CTL)calculator_controller.cpp \
		$(CTL)credit_controller.cpp \
		$(VIW)main.cpp \
		$(VIW)mainwindow.cpp \
		$(VIW)choosewindow.cpp \
		$(VIW)plotwindow.cpp \
		$(VIW)creditwindow.cpp 

HEADERS=$(MDL)calculator_model.h \
		$(MDL)credit_model.h \
		$(CTL)calculator_controller.h \
		$(CTL)credit_controller.h

TSRC=$(CTL)calculator_controller.cpp \
	$(MDL)calculator_model.cpp \
	$(CTL)credit_controller.cpp \
	$(MDL)credit_model.cpp

all: install open

open: 
	open $(APP)

install:
	mkdir $(BD)
	cp src/$(FPRO) $(BD)
	cp src/qcustomplot.h $(BD)
	cp src/qcustomplot.cpp $(BD)
	cd $(BD); qmake -makefile $(FPRO)
	make -C $(BD)
	make clean -C $(BD)

test:
	$(CXX) $(STD) $(TFILE) $(TSRC) $(TFLAGS) -o test.out 
	./test.out

gcov_report:
	$(CXX) $(STD) $(TFILE) $(TSRC) $(TFLAGS) $(GFLAGS) -o gcov_test.out
	./gcov_test.out
	lcov -t "coverage" -o coverage.info -c -d .
	genhtml -o report coverage.info
	open report/index.html

dist:
	tar -cvf SmartCalcV2.tar $(APP)
	gzip SmartCalcV2.tar

dvi:
	open src/guide.html

uninstall:
	rm -rf $(APP)

cpplint:
	python3 materials/linters/cpplint.py --filter=-build/include_subdir $(SOURCES)

cppcheck:
	cppcheck --enable=all --language=c++ $(SUP)unusedFunction $(SUP)constParameter $(SUP)unmatchedSuppression $(SUP)missingInclude $(SUP)unknownMacro $(SUP)unusedStructMember $(SOURCES) $(HEADERS)

clean:
	rm -rf *.o *.out *.a *.gcda *.gcno *.info test
	rm -rf ./report/
	rm -rf ./$(BD)*