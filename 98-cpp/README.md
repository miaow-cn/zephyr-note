## Files

```bash
03-devicetree
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

## DTC related variables

variables for build system

- **DTC_OVERLAY_FILE**
  If not set, default to:
  - `socs/<SOC>_<BOARD_QUALIFIERS>.overlay` if exists (not exist by default)
  - `boards/<BOAR>.overlay` in addition to the above if exists (not exist by default)
  - `boards/<BOARD>_<revision>.overlay` in addition to the above if exists and the current board has multiple revisions (not exist by default)
  - If one or more files have been found in the previous steps, the build system stops looking and just uses those files
  - Otherwise, use `<BOARD>.overlay` if exists, and the build system will stop looking for more files  (not exist by default)
  - Otherwise, use `app.overlay` if exists (yes, we use `app.overlay` in this demo)

 - **EXTRA_DTC_OVERLAY_FILE**
   Appends overlays specified in EXTRA_DTC_OVERLAY_FILE to DTC_OVERLAY_FILE. 

 - **DTS_ROOT**
   The build system looks for bindings in `dts/bindings` subdirectories of the following places:
   - zephyr repository
   - your application directory
   - your board directory
   - any shield directories
   - any directories manually included in the `DTS_ROOT`
   - any module that defines a dts_root in its build settings