# Compile all binary or delete all binaries and obj

.PHONY = all clean

CC = gcc

FLAG = -lm

SRCS := $(wildcard *.c)
BINS := $(SRCS:%.c=%)

all: ${BINS}

%: %.o
	@echo "Checking.."
	${CC} ${FLAG} $< -0 $@

%.o: %.c
	@echo "Creating object.."
	${CC} -c $<

clean:
	@echo "Cleaning up.."
	rm -rvf *.o ${BINS}
