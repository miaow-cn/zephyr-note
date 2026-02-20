This is a template for zephyr app of *workspace type*.

```bash
01-template
├── app.overlay
├── CMakeLists.txt
├── prj.conf
├── README.md
├── src
│   └── main.c
└── VERSION
```

- **app.overlay**: Device tree overlay that specifies application-specfic changes applied to the base devicetree for the board. The build system looks for `app.overlay` by default.
- **prj.conf**: application specfic Kconfig. The build system looks for `prj.conf` by default.
- **VERSION**: Version infomation fields to manage application lifecycle and automate providing application version for signing images.
- **main.c**: Source code
- **CmakeLists.txt**: For build

