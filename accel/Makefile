CC := g++
LDFLAGS := -lupm-i2clcd -lupm-mma7660
CXXFLAGS := -Wall -Wextra -g

all:accel

accel:
	@$(CC) $(CFLAGS) src/accel.cpp -o accel $(LDFLAGS)
clean:
	@rm -f ./accel
