This is a template for zephyr app of *workspace type*.

## Files

```bash
├── app.overlay
├── CMakeLists.txt
├── debug.conf
├── Kconfig
├── prj.conf
├── README.md
├── src
│   └── main.c
└── VERSION
```

- **app.overlay**: Device tree overlay that specifies application-specfic changes applied to the base devicetree for the board. The build system looks for `app.overlay` by default.
- **prj.conf**: application specfic Kconfig. The build system looks for `prj.conf` by default.
- **VERSION**: Version infomation fields to manage application lifecycle and automate providing application version for signing images.
- **Kconfig**: If app has its own kernel configuration options, create a Kconfig file in the same directory as the app's `CMakeLists.txt`
- **main.c**: Source code
- **CmakeLists.txt**: For build

## Configure

> Configure step is optional. You can reconfigure anytime you want.
> After (re)configuration, a build is required.

In `01-template` directory,
```bash
west build -b fk743m5_xih6 -t menuconfig
```

For reconfigure, both 2 commands are :
```bash
west build -t menuconfig
```
or
```bash
cd build
ninja menuconfig
```

## Build

In `01-template` directory,
```bash
west build -b fk743m5_xih6
```
or
```bash
cmake -Bbuild -DAPPLICATION_CONFIG_DIR=/path/to/app_cfg .
cmake --build build
```

> If the board is given or set when configure, we can skip the `-b` option

executable is:
- build/zephyr/zephyr.elf
- build/zephyr/zephyr.bin
- build/zephyr/zephyr.hex

map is:
- build/zephyr/zephyr.map

device tree is:
- build/zephyr/zephyr.dts

compile_commands:
- build/compile_commands.json

config:
- build/zephyr/.config

linker script:
- build/zephyr/linker.cmd

Part of the variables can be supplied to the build system:

- **ZEPHYR_BASE**

  Set by:
  - find_package(Zephyr) in CMakeLists.txt
  - set as an environment variable

- **APPLICATION_CONFIG_DIR**

  `[EXTRA_]CONF_FILE` and `[EXTRA_]DTC_OVERLAY_FILE` is assumed to be in `APPLICATION_CONFIG_DIR` if not set to an absolute path.
  
  Set by:
  - west build -- -DAPPLICATION_CONFIG_DIR=/path/to/app_cfg
  - cmake -Bbuild -DAPPLICATION_CONFIG_DIR=/path/to/app_cfg . && cmake --build build
  - set(APPLICATION_CONFIG_DIR /path/to/app_cfg) before find_package(Zephyr) in CMakeLists.txt

  If not set, it is the app’s source directory


- **BOARD**

    Set by:
  - cmake cache
  - west build -b fk743m5_xih6
  - cmake -Bbuild -DBOARD=fk743m5_xih6 . && cmake --build build
  - environment variable BOARD
  - set(BOARD fk743m5_xih6) before find_package(Zephyr) in CMakeLists.txt

- **CONF_FILE**

  Set by:
  - cmake cache
  - west build -- -DCONF_FILE="fragment_file1.conf;fragment_file2.conf"
  - cmake -Bbuild -DCONF_FILE="fragment_file1.conf;fragment_file2.conf" . && cmake --build build
  - before find_package(Zephyr) in CMakeLists.txt
    ```cmake
    set(CONF_FILE "fragment_file1.conf")
    list(APPEND CONF_FILE "fragment_file2.conf")
    ```

  if not set, `boards/<BOARD>.conf` exists in app:
  - `prj.conf` merged with `boards/<BOARD>.conf`is used
  - addtionally, if board revisions are used and `boards/<BOARD>_<revision>.conf` exists, `boards/<BOARD>_<revision>.conf` is also merged
 
  otherwise, `prj.conf` is used.

- **EXTRA_CONF_FILE**

  Additional Kconfig configuration fragment files, same setting methods as `CONF_FILE`

- **DTC_OVERLAY_FILE**
  
  Devicetree overlay files to use, same setting methods as `CONF_FILE`. 
  
  If not set, default to:
  - `socs/<SOC>_<BOARD_QUALIFIERS>.overlay` if exists
  - `boards/<BOAR>.overlay` in addition to the above if exists
  - `boards/<BOARD>_<revision>.overlay` in addition to the above if exists and the current board has multiple revisions
  - If one or more files have been found in the previous steps, the build system stops looking and just uses those files.
  - Otherwise, use `<BOARD>.overlay` if exists, and the build system will stop looking for more files
  - Otherwise, use `app.overlay exists` if exists.

 - **EXTRA_DTC_OVERLAY_FILE**
 
   Appends overlays specified in EXTRA_DTC_OVERLAY_FILE to DTC_OVERLAY_FILE. 
   
   Same setting methods as `DTC_OVERLAY_FILE`.

- **SHIELD**

  for  "add-on" or "daughter boards"
  - west build -b xxx --shield subboard1 --shield subboard2
  - cmake -Bbuild -DSHIELD=subboard1;subboard2 . && cmake --build build
  - before find_package(Zephyr) in CMakeLists.txt
    ```cmake
    set(SHIELD "subboard1")
    list(APPEND SHIELD "subboard2")
    ```

- **ZEPHYR_MODULES**

  A CMake list containing absolute paths of additional directories with source code, Kconfig, etc. If you set this variable, it must be a complete list of all modules to use.

- **EXTRA_ZEPHYR_MODULES**
  
  Like `ZEPHYR_MODULES`, except these will be added to the list of modules.

- **FILE_SUFFIX**

  Optional suffix for filenames that will be added to Kconfig fragments and devicetree overlays.

- **KCONFIG_ROOT**

  The `Kconfig` file is automatically detected when placed in the app directory, but it is also possible for it to be found elsewhere if the CMake variable `KCONFIG_ROOT` is set with an absolute path.

## Clean
Preserve `.config` file:
```bash
west build -t clean
```
or
``` bash
ninja clean
```

Distclean:
```bash
west build -t pristine
```
or
```bash
ninja pristine
```

## Flash

```bash
west flash
```
or
```bash
ninja flash
```