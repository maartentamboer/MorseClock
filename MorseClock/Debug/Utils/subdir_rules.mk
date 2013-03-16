################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Utils/uartstdio.obj: C:/StellarisWare/utils/uartstdio.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/tms470_4.9.5/bin/cl470" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -g --include_path="C:/ti/ccsv5/tools/compiler/tms470_4.9.5/include" --include_path="C:/StellarisWare" --define=TARGET_IS_BLIZZARD_RA1 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="Utils/uartstdio.pp" --obj_directory="Utils" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Utils/ustdlib.obj: C:/StellarisWare/utils/ustdlib.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv5/tools/compiler/tms470_4.9.5/bin/cl470" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -g --include_path="C:/ti/ccsv5/tools/compiler/tms470_4.9.5/include" --include_path="C:/StellarisWare" --define=TARGET_IS_BLIZZARD_RA1 --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="Utils/ustdlib.pp" --obj_directory="Utils" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


