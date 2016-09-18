# MAKEFILE_PATH = $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
# ROOT = $(realpath ..)

CC = g++

BUILD_DIR = build

CC_FLAGS= -w -std=c++11
LD_FLAGS= -lSDL2 -lSDL2_image -lSDL2_ttf -lopenal -lalut

INC_PATHS= 	Tests/Catch/single_include	\
			Asset/include 		\
			Options/include
INC=		$(foreach d, $(INC_PATHS), -I$d)

SRC_FILES=	Asset/AssetManager.cpp
SRC=		$(foreach d, $(SRC_FILES), $d)
SRC_DIRS=   $(foreach d, $(SRC_FILES), $(dir $d))

OBJS = 		$(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRC))

TEST_TARGET_NAME = 	unit_test
TEST_TARGET = 		$(TEST_TARGET_NAME)
TEST_SRC_FILES = 	Tests/Tests.cpp
TEST_SRC =			$(foreach d, $(TEST_SRC_FILES), $d)
TEST_SRC_DIRS =   	$(foreach d, $(TEST_SRC_FILES), $(dir $d))

TEST_OBJS = 		$(patsubst %.cpp,$(BUILD_DIR)/%.o,$(TEST_SRC))

.PHONY: clean distclean

all: dir

tests: dir test-dir $(TEST_TARGET)

dir:
	@mkdir -p $(BUILD_DIR)
	$(foreach d, $(SRC_DIRS), $(shell mkdir -p $(BUILD_DIR)/$d))

test-dir:
	@mkdir -p $(BUILD_DIR)
	$(foreach d, $(TEST_SRC_DIRS), $(shell mkdir -p $(BUILD_DIR)/$d))

$(TEST_TARGET): $(OBJS) $(TEST_OBJS)
	@echo Linking $@
	@$(CC) -ggdb $^ -o $@ $(LD_FLAGS)

$(BUILD_DIR)/%.o : %.cpp
$(BUILD_DIR)/%.o : %.cpp $(BUILD_DIR)/%.d
	@echo Compiling $< to $@
	@$(CC) -ggdb $(CC_FLAGS) $(INC) -c $< -o $@ -MT $@ -MMD -MP -MF $(@:.o=.d)

clean:
	@$(foreach d, $(SRC_DIRS), $(shell rm -rf $(BUILD_DIR)/$d))
	@rm -f $(TARGET)

tests-clean:
	@$(foreach d, $(TEST_SRC_DIRS), $(shell rm -rf $(BUILD_DIR)/$d))
	@rm -f $(TEST_TARGET)

clean-tests: tests-clean	

distclean:
	@rm -rf $(BUILD_DIR)
	@rm -f $(TARGET)
	@rm -f $(TEST_TARGET)

$(BUILD_DIR)/%.d: ;
.PRECIOUS: $(BUILD_DIR)/%.d

-include $(OBJS:.o=.d)
-include $(TEST_OBJS:.o=.d)
