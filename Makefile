BIN=bin
SRC=src
OBJ=obj
BAT=bat
INC=include

SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst %.c,$(OBJ)/%.o,$(notdir $(SRCS)))

CXX=gcc

$(BIN)/main:$(OBJS)
	@$(CXX) $^ -o $@
$(OBJ)/%o:$(SRC)/%c
	@$(CXX) -I $(INC) -c $< -o $@

.PHONY:clean
clean:
	@rm -f $(BIN)/* $(OBJ)/*.o $(BAT)/*