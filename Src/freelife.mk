include ../common.mk

OBJS = field.o life.o main.o settings.o utils.o zoom.o 
TARGET = freelife
LIBS = 
CFLAGS +=
CFLAGS += $(if $(filter 1 YES, $(DEBUG)), -g -O0, -g0 -O2)
LDFLAGS += 
include ../compile.mk	
