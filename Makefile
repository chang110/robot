# 定义编译器
CC = gcc

# 定义编译选项
CFLAGS = -Wall -fPIC -I. -g

# 定义库文件链接选项
LDFLAGS = -shared

# 定义源文件列表
SRCS = motor_ctl.c pin_list.c

# 定义目标文件列表
OBJS = $(SRCS:.c=.o)

# 定义目标动态库文件名
TARGET = librobot.so

# 默认规则：编译生成动态库
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# 规则：编译源文件为对象文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理规则：删除生成的文件
clean:
	rm -f $(OBJS) $(TARGET)