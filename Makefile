# -*- tab-width: 4 -*-

SOURCE	:= $(wildcard *.cpp)
EXECUTE	:= sample

CXX			:= clang++
CXXFLAGS	:= -Wall

check: $(EXECUTE)
	# check
	./$(EXECUTE)

$(EXECUTE) : $(SOURCE) $(wildcard *.hpp)
	# create: $@
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $@

clean:
	rm -f $(EXECUTE)
	find . -name '*~' -print0 | xargs -0 rm -f

.PHONY: check clean
