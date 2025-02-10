NAME    = philo
CC      = cc
CFLAGS  = -Wextra -Wall -Werror -g  -I includes/

# รายการไฟล์ .c ที่ต้องคอมไพล์
MAIN    = main.c simulation.c time.c solo.c
PHASER  = phaser.c phaser_data.c

# สร้าง path ของไฟล์ .c
SRCS = $(addprefix srcs/main/, $(MAIN)) \
       $(addprefix srcs/phaser/, $(PHASER))

# สร้างไฟล์ .o ให้ตรงกับตำแหน่งของไฟล์ .c
OBJS = $(SRCS:.c=.o)

# เป้าหมายหลัก
all: $(NAME)

$(NAME): $(OBJS)
	@echo "\e[1;36mCompiling philosopher..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "Done!"

# คอมไพล์ไฟล์ .c เป็น .o (ตรงกับโฟลเดอร์ของ srcs/)
srcs/%.o: srcs/%.c
	@echo "\e[0;30mCompiling $< -> $@"
	@$(CC) $(CFLAGS) -c $< -o $@

# ทำความสะอาดไฟล์ .o
clean:
	@rm -f $(OBJS)

# ลบไฟล์ที่คอมไพล์ในโปรเจ็กต์หลัก
fclean: clean
	@rm -f $(NAME)

# ทำใหม่ทั้งหมด
re: fclean all

.PHONY: all clean fclean re