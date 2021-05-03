VPATH = ./src
CC = g++
WIN_CC = i686-w64-mingw32-g++
CFLAGS = -ggdb -std=c++17
EXE = MiniRPG

OBJ_DIR = ./obj
INCLUDES = -Iinclude
INCLUDES_LINUX = $(INCLUDES) -Llib
INCLUDES_WIN = $(INCLUDES) -Iraylib32/include/ -Lraylib32/lib/

OBJS:=main.o GameObject.o Player.o Scene.o AssetManager.o
OBJ_DEPS = $(patsubst %,$(OBJ_DIR)/%,$(OBJS))

build: linux

linux: dirs $(EXE)

$(OBJ_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -MD -MP $< -c -o $@

$(EXE): $(OBJ_DEPS)
	$(CC) $(CFLAGS) $^ -o ./build/$@ -Wall -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

windows: dirs_win deps_win $(EXE).exe

$(OBJ_DIR)/win32/%.o: %.cpp
	$(WIN_CC) $(CFLAGS) $(INCLUDES_WIN) -MD -MP $< -c -o $@

$(EXE).exe: $(patsubst %,$(OBJ_DIR)/win32/%,$(OBJS))
	$(WIN_CC) $(CFLAGS) $^ $(INCLUDES_WIN) -o ./build/$(EXE).exe -Wall -lraylib.dll -lopengl32 -lgdi32 -lwinmm -static -lpthread

dirs:
	mkdir -p obj build

dirs_win:
	mkdir -p obj obj/win32 build

deps_win: copy_resources copy_raylibdll

copy_resources:
	cp -r ./resources ./build/resources

copy_raylibdll:
	cp ./raylib32/bin/libraylib.dll ./build/raylib.dll

.PHONY: clean
.PHONY: linux
.PHONY: windows
.PHONY: build

clean:
	rm -rf ./build ./obj

-include $(OBJS:.o=.d)
