CXX = g++-12 -std=c++20
CXXFLAGS = -Wall -g -MMD  # use -MMD to generate dependencies
SRC_DIR = src
BUILD_DIR = build
SOURCES = $(wildcard $(SRC_DIR)/*.cc)   # list of all .cc files in the current directory
OBJECTS = ${SOURCES:#(SRC_DIR)/%.cc=$(BUILD_DIR)/%.o}  # .o files depend upon .cc files with same names
OBJECTS += $(BUILD_DIR)/gaussian-int.o  # Add gaussian-int.o to OBJECTS
DEPENDS = ${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC=gaussian-factorise

# First target in the makefile is the default target.
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)

# Compile each .cc file to a corresponding .o file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Rule for compiling gaussian-int.cc to gaussian-int.o
$(BUILD_DIR)/gaussian-int.o: $(SRC_DIR)/gaussian-int.cc 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Include dependency files
-include $(DEPENDS)

.PHONY: clean 
clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d $(EXEC)
