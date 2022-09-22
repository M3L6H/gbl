CXX		   = g++
DEBUG		 = -g -Wall
ODIR	   = obj
OPTIMIZE = -O2
RM		   = rm -f
SDIR	   = src
TARGET   = gblc

SRCS  = gblc.cpp lexer.cpp utils.cpp
_OBJS = $(subst .cpp,.o,$(SRCS))
OBJS  = $(patsubst %,$(ODIR)/%,$(_OBJS))

all: main

main: $(OBJS)
	$(CXX) $(DEBUG) -o $(TARGET) $(OBJS)

optimal: $(OBJS)
	$(CXX) $(OPTIMIZE) -o $(TARGET) $(OBJS)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CXX) $(DEBUG) -c $< -o $@

clean:
	$(RM) $(OBJS) $(TARGET)

docs: Doxyfile src/*
	doxygen Doxyfile
