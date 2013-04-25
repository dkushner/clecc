################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../FFUtil.cpp \
../main.cpp 

OBJS += \
./FFUtil.o \
./main.o 

CPP_DEPS += \
./FFUtil.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: NVCC Compiler'
	nvcc -I/opt/cuda/include -I/usr/include -I/usr/include/c++/4.8.0 -I/usr/include/GL -I/usr/local/include/SDL2 -I/usr/include/glm -O2  -odir "" -M -o "$(@:%.o=%.d)" "$<"
	nvcc -I/opt/cuda/include -I/usr/include -I/usr/include/c++/4.8.0 -I/usr/include/GL -I/usr/local/include/SDL2 -I/usr/include/glm -O2 --compile  -x c++ -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


