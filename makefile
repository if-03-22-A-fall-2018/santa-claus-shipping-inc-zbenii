CC					= g++
CCLINK			= g++
LIBS				=
CCOPTIONS		= -Wall -pedantic -g
LDOPTIONS		=
HDRS				= list.h child_data_mgmt.h tour_plan.h test_santa_claus.h shortcut.h

TEST = test_santa_claus
PROGRAM = santa_claus

TESTOBJECT = santa_claus_test_driver.o
MAINOBJECT = santa_claus_main_driver.o
OBJS = shortcut.o list.o test_santa_claus.o tour_plan.o child_data_mgmt.o

#DOXY            = /Applications/Doxygen/Doxygen.app/Contents/Resources/doxygen

all: $(PROGRAM)
	./$(PROGRAM)

$(TEST): $(OBJS) $(TESTOBJECT)
	$(CCLINK) -o $@ $(LDOPTIONS) $(OBJS) $(TESTOBJECT)

$(PROGRAM): $(OBJS) $(MAINOBJECT)
	$(CCLINK) -o $@ $(LDOPTIONS) $(OBJS) $(MAINOBJECT)

#.PHONY: clean cleanall doxy test setsample setassignment definesample defineassignment assignmentfolder
.PHONY: clean cleanall test setsample setassignment definesample defineassignment assignmentfolder

clean:
	rm -f $(PROGRAM) $(TEST) $(TESTOBJECT) $(MAINOBJECT) $(OBJS)

cleanall:
	rm -f $(PROGRAM) $(TEST) $(TESTOBJECT) $(MAINOBJECT) $(OBJS) index.html
	rm -R html

doxy:
	$(DOXY)
	ln -s html/index.html index.html

test: $(TEST)
	./$(TEST)

#sets project as sample solution
setsample:
	cp car.cpp.sample car.cpp
	cp car.h.sample car.h

#sets project as assignment
setassignment:
	cp car.cpp.assignment car.cpp
	cp car.h.assignment car.h

# defines current state of project as sample solution
definesample:
	cp car.cpp car.cpp.sample
	cp car.h car.h.sample

# defines current sate of project as assignment
defineassignment:
	cp car.cpp car.cpp.assignment
	cp car.h car.h.assignment

# creates a folder which can serve as a publishable assignment
assignmentfolder:
	make setassignment
	#make doxy
	mkdir ../assignment
	cp -R * ../assignment
	rm ../assignment/*.sample
	rm ../assignment/*.assignment
	make cleanall

%.o: %.cpp $(HDRS)
	$(CC) $(CCOPTIONS) -c $<
