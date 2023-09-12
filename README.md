# Link Switcher

The Link Switcher allows changing the target of directory links by command-line arguments, such as switching Java versions.

## Usage

In the following steps, the JDK environment located at `D:\Environment\Java` will be used for demonstration purposes.

```
D:\Environment\Java
├─OpenJDK_11.0.18
├─OpenJDK_17.0.6
├─OpenJDK_19.0.2
└─OpenJDK_8.362
```

1. Copy `LinkSwitcher.exe` to this directory and rename it to `swj.exe` (or to any name you prefer).

2. Create an empty directory named `CurrentJDK` (or any name you prefer), and add `D:\Environment\Java` and `D:\Environment\Java\CurrentJDK` to the `PATH` environment variable.

3. Create a text file named `swj.ini` (same as Step 1). After these 3 steps, the contents of the directory are as follows:

```
D:\Environment\Java
├─OpenJDK_11.0.18
├─OpenJDK_17.0.6
├─OpenJDK_19.0.2
├─OpenJDK_8.362
├─CurrentJDK
├─swj.exe
└─swj.ini
```

4. Configure the `swj.ini`. The content of the file is as follows:

```ini
[App]
Link=CurrentJDK

[Items]
J8=OpenJDK_8.362
J11=OpenJDK_11.0.18
J17=OpenJDK_17.0.6
J19=OpenJDK_19.0.2
```

5. To switch to Java 8, run `swj j8` in the command line.

```
swj j8
```

## Additional notes

```ini
[App]
Base=D:\Environment\Python
Link=D:\Environment\CurrentPython

[Items]
PY38=Python38
PY311=E:\Python311
```

- **App**: `Optional` The configuration of the app.
    - **Base**: `Optional` The base path for all relative paths. It can be relative to the directory of the executable file.
    - **Link**: `Optional` The link of directory is created here.

- **Items**: `Required` All key-path pairs. The key is used as the command-line argument.
