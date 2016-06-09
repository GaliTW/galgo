PROJ := galgo

CC := gcc
INCLUDES := -I./include
CFLAGS += $(INCLUDES) -std=c99 

VALID_PATH ?= valid

SRCS := $(wildcard container/*.c)
OBJS := $(SRCS:.c=.o)

V_SRCS := $(wildcard $(VALID_PATH)/*.c)
V_OBJS := $(V_SRCS:.c=.o)
VALIDS := $(V_SRCS:$(VALID_PATH)/%.c=%)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $< 

all: $(VALIDS)

$(VALIDS): $(VALID_PATH)/$(VALIDS).o $(OBJS)
	$(CC) -o $@ $^
	
clean:
	rm -f $(V_OBJS) $(OBJS) $(VALIDS)
	
.PHONY: all clean
	