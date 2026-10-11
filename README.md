# C++ 实验0 CMake Tutorial

## 当前结果

2026-10-11，使用 CMake 4.4.3、Visual Studio 2022 / MSVC 19.44 构建。
本项目按 CMake 3.20 官方旧版 Tutorial 的 Step1–Step8 组织：
https://cmake.org/cmake/help/v3.20/guide/tutorial/index.html
此前聊天和早期 Git 提交的步骤编号与此版本不同，以以下对应关系为准。

| 步骤 | 实现与验证 | 提交 |
| --- | --- | --- |
| Step1 基础工程 | 版本号、配置头文件、C++11、命令行参数 | 1309834 |
| Step2 添加库 | MathFunctions；USE_MYMATH 开关控制链接和条件编译 | 原有代码及 1309834 |
| Step3 使用要求 | 库通过 INTERFACE 传播头文件目录 | 1309834 |
| Step4 安装和测试 | 安装可执行文件、库和头文件；12 项 CTest | 94d9c87 |
| Step5 系统检测 | 检测 log/exp；检测成功走 exp(log(x)/2)，失败走迭代 | 987b291、5bcda86 |
| Step6 生成文件 | MakeTable → Table.h → MathFunctions；查表辅助牛顿迭代 | 9391b78 |
| Step7 打包 | CPack 生成 Release 二进制 ZIP 和源码 ZIP；解压运行成功 | 1dcda15 |
| Step8 Dashboard | CTestConfig.cmake；本地 Configure、Build、Test XML | be014f4 |

Step6 按教程替换 Step5 的 log/exp 实现，Step5 的代码保留在上述提交中。
Step8 已完成配置和本地运行，尚未向公共 CDash 提交，不能作为线上提交成功的证明。

## 实现说明

无参数运行保留原有调试示例 sqrt(9)=3，与官方无参数显示用法略有不同。
输入非法文本、尾随字符、非有限数或多余参数时，返回非零退出码。
自定义算法对 1 至 10 之间的输入使用生成表作为初值；其他正数先进行二进制缩放再迭代，避免简单固定次数迭代对大数、小数收敛不足。负数返回 NaN。

最终验证：
- 自定义库 Debug：12/12 通过。
- 自定义库 Release：12/12 通过。
- 标准库 Debug（USE_MYMATH=OFF）：12/12 通过。
- 本地 Dashboard：0 编译错误、0 编译警告、12/12 测试通过。
- 安装目录中的程序和二进制 ZIP 解压后的程序均运行成功。

## 重现与截图

以下命令在项目根目录的 PowerShell 运行，要求 CMake 在 PATH 中。

### 构建和测试截图

```powershell
cmake -S . -B build -DUSE_MYMATH=ON
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

截图包含最后的 `100% tests passed`。测试涵盖默认输入、整数平方根、非整数结果、零、小数、大数及四类非法参数。

### 生成表及运行截图

```powershell
Get-Content .\build\MathFunctions\Table.h
.\build\Debug\Tutorial.exe 9
```

截图包含 `Using generated Table.h` 和 `sqrt(9)=3`。

### 安装截图

```powershell
cmake --install build --config Debug --prefix build/install
.\build\install\bin\Tutorial.exe 25
```

Debug 安装用于本机验证；对外分发使用 Release ZIP。

### 两种实现截图

```powershell
cmake -S . -B build/standard -DUSE_MYMATH=OFF
cmake --build build/standard --config Debug
ctest --test-dir build/standard -C Debug --output-on-failure
.\build\standard\Debug\Tutorial.exe 9
```

### Step5 历史阶段截图

以下操作导出旧提交至被忽略的 build 目录，不切换当前分支。

```powershell
git archive --format=zip --output=build/step5-snapshot.zip 5bcda86
Expand-Archive build/step5-snapshot.zip build/step5-source -Force
cmake -S build/step5-source -B build/step5-build -G "Visual Studio 17 2022" -A x64
cmake --build build/step5-build --config Debug
.\build\step5-build\Debug\Tutorial.exe 25
```

可截图 `log - found`、`exp - found` 与 `Computing with detected log and exp`。

### 打包截图

```powershell
cmake --build build --config Release
Push-Location build
cpack -C Release
cpack --config CPackSourceConfig.cmake
Pop-Location
Get-ChildItem .\build\Tutorial-*.zip
```

二进制：`build/Tutorial-1.0-win64.zip`；源码演示包：`build/Tutorial-1.0-Source.zip`。
CPack 源码演示包不含 .git，因此不是评分标准要求的最终整体源码包。
最终提交时须另打包包含 .git 历史的整个源码项目，排除 build 等产物。

### Dashboard 截图

```powershell
ctest --test-dir build -C Debug -D ExperimentalStart -D ExperimentalConfigure -D ExperimentalBuild -D ExperimentalTest --output-on-failure
Get-ChildItem .\build\Testing -Recurse -Filter *.xml
```

上述命令仅生成本地结果，不联网提交。CTestConfig.cmake 已配置官方教程的 CDash 地址，线上提交尚未执行或验证。

### 提交历史截图

```powershell
git log --oneline -10
git status
```

新增提交均保存在本地，尚未 push。

## 实验0仍需补充的材料

- 环境搭建的真实过程截图：不能用当前成功构建代替过去安装过程。
- 课程 start 工程源码未提供，尚未验证其构建与测试；Tutorial 不替代 start 工程。
- 根据上述命令补真实截图，并整理到最终 Word 实验报告。
- 最终报告、含 Git 历史的整体源码包按学号和姓名命名。

因此本仓库完成的是 Tutorial 实现及本地验证，不代表实验0所有提交材料已经齐全。
