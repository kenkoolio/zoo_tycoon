#
# @file - Makefile for Project 2 - Zoo Tycoon
# @author - Huy Nguyen <nguyehu6@oregonstate.edu>
# @description - Simple makefile for Project 2
# @citation - Adapted from lecture videos and 
#	intermediate_make_sample (Harlan James <waldroha@oregonstate.edu>)
#

# Project name
PROJ = zoo

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS =
CXXFLAGS += -std=c++11
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
LDFLAGS =
#LDFLAGS += -lboost_date_time

# Valgrind options
VOPT =
VOPT += --tool=memcheck
VOPT += --leak-check=full
VOPT += --show-reachable=yes
VOPT += --show-leak-kinds=all
VOPT += --track-origins=yes

# Headers
HEADERS =
HEADERS += Menu.hpp
HEADERS += MyRandom.hpp
HEADERS += ValidateInput.hpp
HEADERS += AnimalConstants.hpp
HEADERS += Animal.hpp
HEADERS += Tiger.hpp
HEADERS += Penguin.hpp
HEADERS += Turtle.hpp
HEADERS += CustomAnimal.hpp
HEADERS += Zoo.hpp

# Source files
SRCS =
SRCS += main.cpp
SRCS += Menu.cpp
SRCS += MyRandom.cpp
SRCS += ValidateInput.cpp
SRCS += AnimalConstants.cpp
SRCS += Animal.cpp
SRCS += Tiger.cpp
SRCS += Penguin.cpp
SRCS += Turtle.cpp
SRCS += CustomAnimal.cpp
SRCS += Zoo.cpp

# Create an object for each source file
OBJS = $(SRCS:.cpp=.o)


# Targets
${PROJ}: ${OBJS}
	${CXX} ${LDFLAGS} ${OBJS} -o ${PROJ}

${OBJS}: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

debug:
	@valgrind ${VOPT} ./${PROJ}

zip:
	zip Project2_Nguyen_Huy.zip *.hpp *.cpp *.txt *.pdf makefile -D

clean:
	rm *.o ${PROJ} ${TEST}

