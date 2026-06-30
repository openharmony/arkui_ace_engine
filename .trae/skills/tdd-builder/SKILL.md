---
name: "tdd-builder"
description: "Compiles, runs, and diagnoses ACE Engine TDD unit tests on OpenHarmony. Invoke when user needs to build/run TDD, fix TDD errors (crash, build failure, coverage), or debug test failures."
---

# TDD Builder — ACE Engine 单元测试编译、运行与报错诊断

本 Skill 专门用于 OpenHarmony ACE Engine 的 TDD（单元测试）编译、运行和报错诊断，覆盖从编译命令执行到崩溃栈反编译定位的完整链路。

## 一、何时触发此 Skill

当用户需要以下操作时触发：
- 编译/构建 TDD 测试用例
- 在设备或本地运行 TDD 测试
- 定位 TDD 编译错误（头文件缺失、链接错误、编译选项问题）
- 定位 TDD 运行时 crash（SIGABRT、SIGSEGV 等）
- 定位覆盖率问题（覆盖率为 0、覆盖率报告缺失）
- 配置 HDC 连接设备
- 任何与 ACE Engine TDD 相关的任务

## 二、核心知识

### 2.1 TDD 编译

#### 编译命令

```bash
# 编译单个 TDD 测试套
./build.sh --product-name rk3568 --ccache --build-target <tdd_target_name>

# 编译单个 TDD（带 Ninja 并行参数）
./build.sh --product-name rk3568 --ccache --no-prebuilt-sdk --build-target <tdd_target_name> --ninjia-args=-j30

# 编译 ACE 所有 TDD
./build.sh --product-name rk3568 --ccache --build-target ace_engine_test

# 编译覆盖率版本（添加 --coverage 编译选项到 BUILD.gn 后）
./build.sh --product-name rk3568 --build-target <tdd_target_name>
```

#### 编译原理

- TDD 编译入口在 `bundle.json` 的 `test` 字段，通过 group 逐级关联到 `ohos_unittest()` 或 `ace_unittest()`
- `ace_unittest` 是封装的 `ohos_unittest` 模板，规范了固定 `source_set` 依赖，降低了新增 TDD 难度
- TDD 测试套是独立可执行文件，地位等同于应用(hap)
- **编译到 TDD 中的内容决定了 TDD 执行什么**——理解这一点对解决问题至关重要
- 测试文件与被测试文件参与编译，外部模块通过 mock 编译到测试套中

#### 编译产出路径

**重要**：产出路径中的目录名由 BUILD.gn 中的 `module_name` 字段决定，不是简单映射源码目录结构。

| 产物 | 路径 | 说明 |
|------|------|------|
| 测试套二进制 | `out/rk3568/tests/unittest/ace_engine/<module_name>/` | 目录名 = `module_name`，如 `Component-RichEditor`、`Component-Text` |
| 符号表(带调试信息) | `out/rk3568/exe.unstripped/tests/unittest/ace_engine/<module_name>/` | 与二进制同名，带调试信息 |
| 动态库符号表 | `out/rk3568/lib.unstripped/arkui/ace_engine/libace.z.so` | 主引擎符号表 |

**查找实际产出路径的方法**：
```bash
# 方法1：通过 Glob 搜索 out 目录查找二进制
find out/rk3568/tests -name "<tdd_target_name>" -type f

# 方法2：从 BUILD.gn 的 module_name 推断
# ace_unittest("rich_editor_test_ng") { module_name = "Component-RichEditor" }
# → 路径为 out/rk3568/tests/unittest/ace_engine/Component-RichEditor/rich_editor_test_ng

# 方法3：查看 module_out_path
# module_out_path = "ace_engine/Component-RichEditor" → 对应产出路径中的 ace_engine/Component-RichEditor/
```

**架构注意**：rk3568 编译产出为 ARM 架构二进制，无法在 x86 Linux 主机上直接运行（会报 `Exec format error`）。必须在 ARM 设备上运行，或编译 x86 版本。

#### 如何查找 TDD 编译目标名

1. 在测试目录的 `BUILD.gn` 中找到 `ace_unittest("xxx_test_ng")` 或 `ohos_unittest("xxx_test_ng")`
2. `xxx_test_ng` 即为编译目标名
3. 也可以通过 `module_name` 字段确定编译产物位置

#### 编译常见问题处理

| 问题 | 原因 | 解决方法 |
|------|------|---------|
| 头文件找不到 | 依赖缺失或 BUILD.gn 中未声明 | 在 BUILD.gn 的 sources/deps 中添加依赖 |
| 链接错误(undefined reference) | 缺少动态库依赖 | 在 BUILD.gn 的 external_deps 中添加依赖 |
| 头文件引用次数门禁拦截 | 新增头文件导致引用次数超阈值(20) | 使用前向声明替代头文件引入，在 cpp 中添加实际依赖 |
| PermissionError (SemLock) | 沙箱限制 /dev/shm 访问 | 在 sandbox.json 的 readWrite 中添加 `/dev/shm` |
| 编译时间过长 | 模板实例化或头文件膨胀 | 分析编译耗时，减少不必要的头文件依赖 |

### 2.2 TDD 运行

#### developer_test 框架运行

```bash
# 进入测试框架目录
cd test/testfwk/developer_test

# 启动交互式测试框架
./start.sh

# 在框架中执行命令
run -t UT                                    # 所有测试套
run -t UT -ts <test_suite_name>              # 单个测试套
run -t UT -tp ace_engine --productform rk3568  # 指定部件
run -t UT -ts <name> -cov coverage            # 跑覆盖率
```

#### 直接运行单个测试套（无需 developer_test 框架）

**x86 环境（本地运行）**：
```bash
# 直接执行编译出的 x86 二进制
./out/<x86_product>/tests/.../<test_suite_name>

# 使用 gtest 过滤器运行单个用例
./out/<x86_product>/tests/.../<test_suite_name> --gtest_filter=<TestCaseName>
```

**ARM 环境（通过 HDC 推送到设备运行）**（实测经验）：

rk3568 编译产出为 ARM 二进制，无法在 x86 主机运行（报 `Exec format error`）。必须推送到 ARM 设备执行：

```bash
# Step 1：推送测试二进制到设备
# 注意：WSL 下需使用 UNC 路径（详见 HDC 设备连接部分）
hdc file send <本地二进制路径> /data/local/tmp/<test_suite_name>
# 或 WSL 下：
hdc file send '\\wsl.localhost\Ubuntu-20.04\tmp\<test_suite_name>' /data/local/tmp/<test_suite_name>

# Step 2：赋予执行权限并运行
hdc shell "chmod 755 /data/local/tmp/<test_suite_name> && /data/local/tmp/<test_suite_name>"

# Step 3（推荐）：指定 XML 输出路径避免 SIGABRT
# gtest 默认输出路径 "/./<test_suite_name>.xml" 在设备上不存在，会导致 FATAL → SIGABRT
# 解决方案：创建输出目录并指定有效路径
hdc shell "mkdir -p /data/local/tmp/test_output && /data/local/tmp/<test_suite_name> --gtest_output=xml:/data/local/tmp/test_output/<test_suite_name>.xml"

# 使用 gtest 过滤器运行单个用例
hdc shell "/data/local/tmp/<test_suite_name> --gtest_filter=<TestCaseName>"
```

#### HDC 设备连接

**原生 Linux 环境（USB 直连）**：
```bash
# Linux 上有 USB 连接设备，hdc 在 PATH 中
hdc list targets
```

**通过 SSH 隧道远程连接（Windows→Linux 反向隧道）**：
```bash
# Windows 端：python setup_windows.py start
# Linux 端连接：
hdc -s 127.0.0.1:18711 list targets
hdc -s 127.0.0.1:18711 shell
```

**WSL 环境通过 Interop 调用 Windows 原生 hdc.exe**（实测经验）：

WSL 中 Linux 原生 hdc 无法识别 USB 设备，必须通过 Windows 侧的 hdc.exe 操作。完整流程如下：

```bash
# Step 1：查找 Windows 侧 hdc.exe 的实际路径
/mnt/c/Windows/System32/cmd.exe /c "where hdc.exe"
# 输出示例：D:\soft\DevEco Studio\sdk\default\openharmony\toolchains\hdc.exe

# Step 2：创建符号链接（路径根据 Step 1 结果调整）
sudo ln -sf "/mnt/d/soft/DevEco Studio/sdk/default/openharmony/toolchains/hdc.exe" /usr/local/bin/hdc

# Step 3：验证设备连接
hdc list targets
# 输出设备序列号表示连接成功，输出 [Empty] 表示无设备连接

# Step 4（重要）：WSL 下 hdc file send 的路径问题
# hdc.exe 无法直接识别 WSL 的 /home/... 路径，会拼接 UNC 路径导致找不到文件
# 解决方案：将文件复制到 /tmp，然后用 Windows UNC 路径推送

# 复制文件到 /tmp（沙箱允许 /tmp 操作，不允许 /mnt/c）
cp /home/bao/ohos/master/out/rk3568/tests/unittest/ace_engine/Component-RichEditor/rich_editor_test_ng /tmp/rich_editor_test_ng

# 使用 UNC 路径推送（注意 WSL 发行版名称，如 Ubuntu-20.04）
hdc file send '\\wsl.localhost\Ubuntu-20.04\tmp\rich_editor_test_ng' /data/local/tmp/rich_editor_test_ng
```

**注意**：trae-sandbox 可能限制 `/mnt/c` 等路径的访问，但允许 `/tmp` 操作。如遇沙箱拦截，先复制到 `/tmp` 再操作。

#### user_config.xml 配置要点

- `device/sn`：指定设备序列号（单台设备可留空）
- `test_cases`：测试用例存放路径（必选）
- `coverage/outpath`：覆盖率插桩文件目录（跑覆盖率时需要）

### 2.3 TDD 报错诊断

#### Crash 问题定位流程

**Step 1：获取崩溃日志**
```bash
# 设备上崩溃日志路径
hdc shell cat /data/log/faultlog/faultlogger/cppcrash-<test_suite_name>-*

# 或查看 temp 目录下更详细的崩溃栈
hdc shell ls /data/log/faultlog/temp/
```

**Step 2：获取符号表**
```bash
# 符号表路径（与测试套同名）
ls out/rk3568/exe.unstripped/tests/unittest/ace_engine/.../<test_suite_name>
```

**Step 3：反编译定位崩溃位置**
```bash
# 使用 llvm-addr2line 反编译
prebuilts/clang/ohos/linux-x86_64/llvm/bin/llvm-addr2line \
  -f -i -C -a -e <符号表路径> <崩溃栈地址1> <崩溃栈地址2> ...

# 示例
prebuilts/clang/ohos/linux-x86_64/llvm/bin/llvm-addr2line \
  -f -i -C -a -e out/rk3568/exe.unstripped/tests/unittest/ace_engine/.../navigation_test_ng \
  006bd24c 00198043
```

**关键注意**：符号表和崩溃栈必须对应同一编译版本！

#### 常见崩溃类型诊断

| 类型 | 信号 | 常见原因 | 排查方向 |
|------|------|---------|---------|
| SIGABRT | signal 6 | 主动 abort()：std 库异常值、框架规则违反 | 栈顶就是触发 abort 的位置 |
| SIGSEGV(空指针) | signal 11 | 空指针调用、未初始化指针 | 由崩溃栈找到负责部分，分析空指针原因 |
| SIGSEGV(越界) | signal 11 | 容器/数组访问越界、已销毁对象 | 先分析越界行为，再考虑多线程 |
| 多线程踩踏 | signal 11 | 多线程读写造成地址踩踏 | 打出崩溃线程号定位失败原因 |

#### 覆盖率问题诊断

| 问题 | 原因 | 解决方法 |
|------|------|---------|
| 覆盖率报告未生成 | 1) 测试用例 crash 2) module_run.log 中有 leak | 先修复 crash，再检查 memory leak |
| 覆盖率为 0 或很低 | subsystem_config.json 路径不匹配 | **必须修改 `all_subsystem_config.json`**（不是 subsystem_config.json） |
| 找不到 .gcda 文件 | 未添加 --coverage 编译选项 | 在被测模块 BUILD.gn 中添加 `cflags_cc = ["--coverage"]` 和 `ldflags = ["--coverage"]` |
| 报告不包含目标代码 | all_subsystem_config.json 路径配置错误 | 确保 path 配置包含目标源码的相对路径 |

#### 覆盖率多判断条件要点

- **或条件(||)**：需要覆盖所有组合（如 false||false||false, false||false||true, false||true||true, true||true||true）
- **与条件(&&)**：同样需要覆盖所有组合
- 验证方法：在源码函数中打印条件值，确认所有 "0"/"1" 组合都被覆盖

#### developer_test 框架测试报告位置

```
test/testfwk/developer_test/reports/<最新目录>/
├── log/<test_suite_name>/crash_log_<test_suite_name>*   # crash 日志
├── result/                                               # XML 结果文件
└── summary_report.xml                                    # 汇总数据
```

## 三、执行流程

### 3.1 编译 TDD 时

1. 确认编译目标名（从 BUILD.gn 的 ace_unittest/ohos_unittest 中获取）
2. 执行编译命令，监控编译过程
3. 如遇编译错误：
   - 头文件缺失 → 检查 BUILD.gn 的 deps/sources 配置
   - 链接错误 → 检查 external_deps 配置
   - 沙箱权限 → 配置 sandbox.json 的 readWrite 添加 `/dev/shm`
4. 编译成功后确认产出路径

### 3.2 运行 TDD 时

1. 确认编译产出路径（通过 `module_name` 或搜索确认，不要假设）
2. 检查 HDC 设备连接状态（`hdc list targets`）
   - WSL 环境：先创建 hdc.exe 符号链接，再验证连接
3. 确认测试套二进制存在
4. 判断运行环境：
   - **x86 本地** → 直接执行二进制
   - **ARM 设备端** → 推送二进制到设备（WSL 下注意路径问题），赋予执行权限后运行
5. 运行测试时指定 `--gtest_output` 参数，避免设备端 SIGABRT
6. 查看运行结果和日志

### 3.3 定位 Crash 时

1. 从崩溃日志中提取崩溃栈地址和崩溃类型
2. 找到对应的符号表文件（exe.unstripped 下）
3. 使用 llvm-addr2line 反编译定位具体代码行
4. 根据崩溃类型分析根因（空指针/SIGABRT/越界等）
5. 修复问题（修改用例或源码）

## 四、参考文档路径

所有 TDD 相关指导文档位于：
```
foundation/arkui/ace_engine/note-master/
├── note-master/tdd自查.md                    # TDD 执行环境、覆盖率、crash 全面指南
├── tdd/run_time/快速参考.md                   # TDD 运行时间分析
├── tdd/fast-tdd-run/README.md                # developer_test 框架提速改造
├── tdd/write_tdd/修复tdd问题.md               # Crash 定位与覆盖率问题
├── tdd/write_tdd/ace_engine_tdd_guide.md     # TDD 开发完整指南
├── tdd/write_tdd/如何跑覆盖率.md              # 覆盖率执行完整流程
├── tdd/hdc_connect_linux_rk3568/tdd_hdc_v2/  # HDC 隧道连接方案
├── build/tdd_compile_time/README.md           # TDD 编译效率分析
└── note-master/arkui编译问题自查.md           # 编译问题自查
```

## 五、注意事项

1. **符号表与崩溃栈必须同一编译版本**：不同版本的符号表反编译结果会错误
2. **覆盖率配置必须修改 all_subsystem_config.json**：subsystem_config.json 每次运行会被覆盖还原
3. **修复 crash 时建议更改用例而非删除**：除非确实找不到方案
4. **头文件门禁拦截时使用前向声明**：头文件中用前向声明，cpp 中引入实际头文件
5. **沙箱权限问题**：编译需要 `/dev/shm` 访问权限，确保 sandbox.json 中已添加
6. **HDC 版本一致性**：确保使用正确版本的 hdc 工具（系统 PATH 中可能有旧版本）
7. **ARM 二进制不能在 x86 上运行**：rk3568 产出为 ARM 架构，x86 主机直接运行会报 `Exec format error`，必须推送到设备或编译 x86 版本
8. **编译产出路径由 module_name 决定**：不要假设路径与源码目录结构一致，通过 `module_name` 或实际搜索确认产出位置
9. **WSL 下 hdc file send 路径问题**：hdc.exe 无法识别 WSL 的 `/home/...` 路径，需将文件复制到 `/tmp`，再使用 UNC 路径 `\\wsl.localhost\<WSL发行版名>\tmp\<文件名>` 推送
10. **设备上 gtest XML 输出路径**：gtest 默认输出路径 `"/./xxx.xml"` 在设备上不存在会导致 SIGABRT，运行时必须用 `--gtest_output=xml:/data/local/tmp/test_output/xxx.xml` 指定有效路径

## 六、TDD 用例生成约束

### 6.1 保证新增 TDD 用例能够执行成功

- **每一条新增的 TDD 用例都必须能够编译通过并运行成功**，不允许生成无法执行的用例。
- 生成用例后，必须执行编译验证，确认无编译错误。
- 编译通过后，必须执行运行验证，确认用例通过（PASS），不产生 crash 或 FAIL。
- 如果新增用例运行失败，必须分析原因并修复，直到用例全部通过为止。

### 6.2 分支覆盖率尽量达到 100%

- **对修改的代码，新增 TDD 用例的分支覆盖率应尽量达到 100%**。
- 需要覆盖所有分支路径，包括：
  - `if/else` 的所有分支
  - `switch/case` 的所有 case（包括 default）
  - 条件表达式中的所有组合（`&&` 和 `||` 的真假组合）
  - 异常路径和边界条件
- 生成用例时，应先阅读被测源码，分析所有分支条件，确保每个分支都有对应的测试用例覆盖。
- 如覆盖率未达 100%，需补充用例直到覆盖率满足要求。

### 6.3 无法直接覆盖时从调用方入手

- **当某个函数/分支无法在 TDD 中直接覆盖时**（例如私有函数、内部回调、框架层自动调用路径等），应考虑从调用方入手进行 TDD 覆盖。
- 具体策略：
  - 通过调用该函数的上层公开接口来间接触发目标分支
  - 通过构造特定的输入参数或状态，使调用链到达目标代码路径
  - 通过模拟（Mock）外部依赖，控制调用链走向目标分支
  - 通过设置组件属性/事件，触发内部逻辑执行到目标代码

### 6.4 参考已有组件的 TDD 用例

- **当修改了某个组件的代码并需要生成新 TDD 时，必须先参考该组件已有的 TDD 用例**。
- 具体要求：
  - 新增用例前，先搜索并阅读目标组件的现有 TDD 测试文件（通常在 `test/unittest/core/pattern/<component>/` 或 `test/unittest/core/components_ng/<component>/` 目录下）
  - 学习已有用例的：测试框架搭建方式（Mock 类、Test 类定义）、初始化流程（MockPipelineContext、FrameNode 创建等）、断言风格、命名规范
  - 新增用例应与已有用例保持一致的编码风格和测试模式，不引入新的测试模式
  - 如已有用例中存在对应的辅助函数或 Mock 类，应复用而非重新创建
- **示例**：如果修改了 RichEditor 组件的代码，生成新 TDD 时应参考 `test/unittest/core/pattern/rich_editor/rich_editor_event_test_ng.cpp` 等已有用例，复用其中定义的 Mock 类和辅助函数。
