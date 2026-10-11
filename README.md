# C++实验

## 当前进度

- CMake环境配置完成
- Visual Studio 2022工具链配置完成
- Debug模式编译通过
- Tutorial程序运行成功

输出：

sqrt(9)=3
## 基础配置补齐（2026-10-11）

参考教程：https://cmake.org/cmake/help/v3.20/guide/tutorial/index.html
旧提交中的 Step3/Step4 是此前聊天使用的编号，与官方教程编号不完全一致。
本次补齐官方 Step1–Step3 的配置头文件、C++11、条件编译和库头文件使用要求。
MathFunctions 当前仍封装标准 sqrt；自定义计算算法将在后续步骤中实现。

- `TutorialConfig.h.in` 在配置时生成版本号和 `USE_MYMATH` 宏。
- `USE_MYMATH=ON` 使用 MathFunctions，OFF 使用 std::sqrt。
- 无参数运行保留原先的 `sqrt(9)=3` 调试示例，也支持命令行传入数字。
- 官方教程的无参数行为为显示用法；这里保留原调试习惯，测试步骤将据此编写。

在项目根目录的 PowerShell 中查看两种实现（可截图）：

```powershell
.\build\Debug\Tutorial.exe 25
.\build\standard\Debug\Tutorial.exe 25
```

后续待完成：安装和 CTest、系统函数检测、构建时生成文件、CPack、Dashboard。
课程 start 工程未提供，尚未核验；本 README 不代表实验0全部完成。
