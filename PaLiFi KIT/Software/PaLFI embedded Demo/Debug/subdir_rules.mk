################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
DCO_Library.obj: ../DCO_Library.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ticcs5/ccsv6/tools/compiler/ti-cgt-msp430_4.4.4/bin/cl430" --silicon_version=msp -g --include_path="C:/ticcs5/ccsv6/ccs_base/msp430/include" --include_path="C:/ticcs5/ccsv6/tools/compiler/ti-cgt-msp430_4.4.4/include" --include_path="C:/ticcs5/ccsv6/tools/compiler/ti-cgt-msp430_4.4.4/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="DCO_Library.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

PaLFI\ Demo.obj: ../PaLFI\ Demo.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ticcs5/ccsv6/tools/compiler/ti-cgt-msp430_4.4.4/bin/cl430" --silicon_version=msp -g --include_path="C:/ticcs5/ccsv6/ccs_base/msp430/include" --include_path="C:/ticcs5/ccsv6/tools/compiler/ti-cgt-msp430_4.4.4/include" --include_path="C:/ticcs5/ccsv6/tools/compiler/ti-cgt-msp430_4.4.4/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="PaLFI Demo.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

SPI_LowLevel.obj: ../SPI_LowLevel.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ticcs5/ccsv6/tools/compiler/ti-cgt-msp430_4.4.4/bin/cl430" --silicon_version=msp -g --include_path="C:/ticcs5/ccsv6/ccs_base/msp430/include" --include_path="C:/ticcs5/ccsv6/tools/compiler/ti-cgt-msp430_4.4.4/include" --include_path="C:/ticcs5/ccsv6/tools/compiler/ti-cgt-msp430_4.4.4/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="SPI_LowLevel.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

SPI_Stack.obj: ../SPI_Stack.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ticcs5/ccsv6/tools/compiler/ti-cgt-msp430_4.4.4/bin/cl430" --silicon_version=msp -g --include_path="C:/ticcs5/ccsv6/ccs_base/msp430/include" --include_path="C:/ticcs5/ccsv6/tools/compiler/ti-cgt-msp430_4.4.4/include" --include_path="C:/ticcs5/ccsv6/tools/compiler/ti-cgt-msp430_4.4.4/include" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="SPI_Stack.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


