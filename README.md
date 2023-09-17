# 目录链接指向切换工具

目录链接指向切换工具用于通过命令行快速切换目录链接的指向，例如通过配置文件让它作为 Java 环境版本切换工具。

## 命令行参数

```
LinkSwitch <key|#> [profile]
```

- **Key** 或 **#**: `必选`
    - **Key**:  切换目标的标签，在配置文件中指定。
    - **#**: 打印配置文件中的所有可用标签。
- **Profile**: `可选` 配置文件路径，如果不指定则使用当前可执行文件所在目录下的同名配置文件。

## 配置文件

通过下列示例配置文件讲述配置项的作用。

```ini
[App]
Base=D:\Environment\Python
Link=CurrentPython
; Same as Link=D:\Environment\Python\CurrentPython

[Items]
PY311=E:\Python311
PY38=Python38
; Same as PY38=D:\Environment\Python\Python38
```

- **App**: `可选` 切换工具配置。
    - **Base**: `可选` 所有相对路径的基础路径，如果是相对路径则是相对于当前可执行文件所在目录的。默认为当前可执行文件所在目录。
    - **Link**: `可选` 生成的目录链接所在目录。默认为当前可执行文件所在目录下的 `Current` 目录。

- **Items**: `必选` 所有标签与路径的键值对，标签用于命令行参数。

## 使用演示

通过下列步骤，将目录链接指向切换工具配置为 Java 环境版本切换工具。演示目录为 `D:\Java` 和 `E:\Java`。

```sh
D:\Java
├─OpenJDK_11.0.18
└─OpenJDK_8.362
```

```sh
E:\Java
├─OpenJDK_19.0.2
└─OpenJDK_17.0.6
```

1. 将 `LinkSwitch.exe` 复制到任意目录并重命名为 `swj.exe`（或任何名字）。

2. 将这个目录加入到环境变量 `PATH` 中（例如 `D:\VersionSwitch`）。

3. 创建 `swj.ini`（与 `swj.exe` 同名），文件内容如下：

```ini
[App]
Link=CurrentJDK

[Items]
8=D:\Java\OpenJDK_8.362
11=D:\Java\OpenJDK_11.0.18
17=E:\Java\OpenJDK_17.0.6
19=E:\Java\OpenJDK_19.0.2
```

4. 将 `swj.exe` 所在目录下的 `CurrentJDK` 目录（例如 `D:\VersionSwitch\CurrentJDK`）加入到环境变量 `PATH` 中。

5. 在命令行中运行 `swj 8` 即可切换到 Java 8。

```sh
> swj 8
> java -version
openjdk version "1.8.0_362"
```

```sh
> swj 11
> java -version
openjdk version "11.0.18" 2023-01-17 LTS
```

## 编译

### Visual Studio

1. 确保 Visual Studio 安装了 C++ 桌面开发组件。
2. 打开 `LinkSwitch.sln` 并使用 `Release` 编译。

### CMake

1. 确保环境中存在 CMake 和 Ninja。
2. 确保环境中存在 MinGW 或已进入安装了 C++ 桌面开发组件的 Visual Studio 开发者命令行。
3. 在项目目录下执行下列命令：

```sh
cmake -GNinja -Bbld
ninja -Cbld
```
