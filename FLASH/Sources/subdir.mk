################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Events.c" \
"../Sources/IIC.c" \
"../Sources/LCD.c" \
"../Sources/RTC.c" \
"../Sources/convfunc.c" \
"../Sources/keyboard.c" \
"../Sources/main.c" \
"../Sources/menu.c" \

C_SRCS += \
../Sources/Events.c \
../Sources/IIC.c \
../Sources/LCD.c \
../Sources/RTC.c \
../Sources/convfunc.c \
../Sources/keyboard.c \
../Sources/main.c \
../Sources/menu.c \

OBJS += \
./Sources/Events_c.obj \
./Sources/IIC_c.obj \
./Sources/LCD_c.obj \
./Sources/RTC_c.obj \
./Sources/convfunc_c.obj \
./Sources/keyboard_c.obj \
./Sources/main_c.obj \
./Sources/menu_c.obj \

OBJS_QUOTED += \
"./Sources/Events_c.obj" \
"./Sources/IIC_c.obj" \
"./Sources/LCD_c.obj" \
"./Sources/RTC_c.obj" \
"./Sources/convfunc_c.obj" \
"./Sources/keyboard_c.obj" \
"./Sources/main_c.obj" \
"./Sources/menu_c.obj" \

C_DEPS += \
./Sources/Events_c.d \
./Sources/IIC_c.d \
./Sources/LCD_c.d \
./Sources/RTC_c.d \
./Sources/convfunc_c.d \
./Sources/keyboard_c.d \
./Sources/main_c.d \
./Sources/menu_c.d \

C_DEPS_QUOTED += \
"./Sources/Events_c.d" \
"./Sources/IIC_c.d" \
"./Sources/LCD_c.d" \
"./Sources/RTC_c.d" \
"./Sources/convfunc_c.d" \
"./Sources/keyboard_c.d" \
"./Sources/main_c.d" \
"./Sources/menu_c.d" \

OBJS_OS_FORMAT += \
./Sources/Events_c.obj \
./Sources/IIC_c.obj \
./Sources/LCD_c.obj \
./Sources/RTC_c.obj \
./Sources/convfunc_c.obj \
./Sources/keyboard_c.obj \
./Sources/main_c.obj \
./Sources/menu_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/Events_c.obj: ../Sources/Events.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/Events.args" -ObjN="Sources/Events_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/IIC_c.obj: ../Sources/IIC.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/IIC.args" -ObjN="Sources/IIC_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/LCD_c.obj: ../Sources/LCD.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/LCD.args" -ObjN="Sources/LCD_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/RTC_c.obj: ../Sources/RTC.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/RTC.args" -ObjN="Sources/RTC_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/convfunc_c.obj: ../Sources/convfunc.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/convfunc.args" -ObjN="Sources/convfunc_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/keyboard_c.obj: ../Sources/keyboard.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/keyboard.args" -ObjN="Sources/keyboard_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/main.args" -ObjN="Sources/main_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/menu_c.obj: ../Sources/menu.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/menu.args" -ObjN="Sources/menu_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


