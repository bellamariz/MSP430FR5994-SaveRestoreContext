################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
fram-utilities/ctpl/%.obj: ../fram-utilities/ctpl/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/Users/AdmGistLab2/Documents/msp430novo/CTPLTest/driverlib/MSP430FR5xx_6xx" --include_path="C:/ti/ccs1230/ccs/ccs_base/msp430/include" --include_path="C:/Users/AdmGistLab2/Documents/msp430novo/CTPLTest" --include_path="C:/Users/AdmGistLab2/Documents/msp430novo/CTPLTest/fram-utilities/ctpl" --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power=all --advice:hw_config=all --define=__MSP430FR5994__ --define=CTPL_STACK_SIZE=160 --define=_MPU_ENABLE -g --printf_support=minimal --diag_suppress=10367 --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="fram-utilities/ctpl/$(basename $(<F)).d_raw" --obj_directory="fram-utilities/ctpl" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

fram-utilities/ctpl/%.obj: ../fram-utilities/ctpl/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/Users/AdmGistLab2/Documents/msp430novo/CTPLTest/driverlib/MSP430FR5xx_6xx" --include_path="C:/ti/ccs1230/ccs/ccs_base/msp430/include" --include_path="C:/Users/AdmGistLab2/Documents/msp430novo/CTPLTest" --include_path="C:/Users/AdmGistLab2/Documents/msp430novo/CTPLTest/fram-utilities/ctpl" --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-msp430_21.6.1.LTS/include" --advice:power=all --advice:hw_config=all --define=__MSP430FR5994__ --define=CTPL_STACK_SIZE=160 --define=_MPU_ENABLE -g --printf_support=minimal --diag_suppress=10367 --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="fram-utilities/ctpl/$(basename $(<F)).d_raw" --obj_directory="fram-utilities/ctpl" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


