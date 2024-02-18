.PHONY: debug release compile_debug compile_release clean metadata

PROJECT_NAME        = arcade_collection
METADATA_RAW 		= metadata.rc
METADATA_COMPILED 	= metadata.rc.data
SRC_DIR 	 		= src

CC = gcc
CFLAGS = -Wall -Werror -std=c99 -D_DEFAULT_SOURCE -DPLATFORM_DESKTOP
CFLAGS_DEBUG = -Og -g3
CFLAGS_RELEASE = -s -O1 -Wl,--subsystem,windows
LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
SOURCE_FILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c)


debug: compile_debug
	./\$(PROJECT_NAME).exe

release: compile_release
	mkdir -p $(PROJECT_NAME)
	cp -r assets $(PROJECT_NAME).exe $(PROJECT_NAME)/
	7z a -tzip $(PROJECT_NAME).zip $(PROJECT_NAME)
	rm -rf $(PROJECT_NAME)

compile_debug: clean metadata
	$(CC) $(SOURCE_FILES) -o $(PROJECT_NAME) $(CFLAGS) $(CFLAGS_DEBUG) $(METADATA_COMPILED) $(LDLIBS)

compile_release: clean metadata
	$(CC) $(SOURCE_FILES) -o $(PROJECT_NAME) $(CFLAGS) $(CFLAGS_RELEASE) $(METADATA_COMPILED) $(LDLIBS)

clean:
	rm -rf $(PROJECT_NAME).exe $(PROJECT_NAME).zip $(METADATA_COMPILED) $(PROJECT_NAME)

metadata:
	windres $(METADATA_RAW) -o $(METADATA_COMPILED) --target=pe-x86-64
