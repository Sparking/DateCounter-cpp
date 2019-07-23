CXX      := g++
CPPFLAGS := -Wall -Werror -std=c++11
CXXFLAGS := -O0 -g
LDFLAGS  :=
LIBS     :=

OUTPUT   := main
SRC      := date_counter.cc main.cc
DEPENDS  := $(patsubst %.cc, %.d, $(SRC))
OBJS	 := $(patsubst %.cc, %.o, $(SRC))

$(OUTPUT): $(OBJS)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $^ $(LIBS)
-include $(DEPENDS)
$(OBJS): %.o: %.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -c -o $@ $<
.PHONY: clean
clean:
	$(RM) $(OUTPUT)
	$(RM) $(DEPENDS)
	$(RM) $(OBJS)
