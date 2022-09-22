CXX		   = g++
DEBUG		 = -g
ODIR	   = obj
OPTIMIZE = -O2
RM		   = rm -f
SDIR	   = src
TARGET   = gblc

SRCS  = gblc.cpp
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
