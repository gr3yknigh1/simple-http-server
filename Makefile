CC         = gcc
CFLAGS     = -g -Wall -Werror
RM         = rm -rf

SOURCE_DIR = src
SOURCE     = $(SOURCE_DIR)/*.c
HEADERS    = $(SOURCE_DIR)/*.h

BUILD_DIR  = build
PROG       = $(BUILD_DIR)/main

OBJS       = *.o


default: all

all: main

run:
	[ -d $(BUILD_DIR) ] || make all

	$(PROG)

main: $(OBJS)
	[ -d $(BUILD_DIR) ] || mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)

$(OBJS): $(SOURCE) $(HEADERS)
	[ -d $(OBJS_DIR) ] || mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $(SOURCE)

clean veryclean:
	$(RM) $(OBJS)
	$(RM) $(BUILD_DIR)
