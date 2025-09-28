
HAL_VERSION:=v1.28.3

.PHONY=deps

deps:
	mkdir deps
	git clone --recursive  --depth 1 --branch $(HAL_VERSION) https://github.com/STMicroelectronics/STM32CubeF4.git deps/STM32CubeF4
	cd deps && wget https://elm-chan.org/fsw/ff/arc/ff16.zip && unzip ff16.zip

cmake:
	cmake -B build -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake
	cmake --build build
	arm-none-eabi-objcopy -O ihex build/fatfs_spi_driver_test build/fatfs_spi_driver_test.hex


clean:
	rm -rf build

