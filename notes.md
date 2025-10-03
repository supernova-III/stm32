## Dependencies
* STM32 HAL
```sh
git clone --recursive  --depth 1 --branch v1.28.3 https://github.com/STMicroelectronics/STM32CubeF4.git
```
* FatFS
```sh
wget https://elm-chan.org/fsw/ff/arc/ff16.zip
```
* sudo apt install stlink-tools

* https://allthingsembedded.com/post/2020-04-11-mastering-the-gnu-linker-script/

## SDIO pins:
* PC8 - D0
* PC9 - D1
* PC10 - D2
* PC11 - D3
* PC12 - CLK
* PA6 - D12 - CMD
