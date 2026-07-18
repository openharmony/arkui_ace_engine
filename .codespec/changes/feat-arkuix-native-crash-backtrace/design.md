# 架构设计 — ArkUI-X 跨平台原生崩溃栈收集（FP 链回溯）

## 设计元数据

| 字段 | 内容 |
|------|------|
| 关联 spec | `.codespec/changes/feat-arkuix-native-crash-backtrace/spec.md` |
| 复杂度 | 标准 |
| 涉及仓 | arkui_for_android（**无需改动，已符合**）、arkui_for_ios（2 项输出格式对齐） |
| 状态 | Approved |

## 需求基线

见 proposal.md §三。核心：在加载跨平台核心库时注册 5 个崩溃信号的 AS-safe handler，基于 fp/x29 收集并输出可符号化崩溃栈；两端输出格式对齐到统一规格。

## 上下文和现状

### 涉及仓和模块

| 仓 | 文件 | 职责 | 本期改动 |
|----|------|------|----------|
| arkui_for_android | `entrance/java/jni/backtrace_handler.{h,cpp}` | 信号注册 + FP 回溯 + maps 解析 | **无（已符合规格）** |
| arkui_for_android | `entrance/java/jni/jni_load.cpp` | `JNI_OnLoad` 内调用注册 | 无 |
| arkui_for_ios | `osal/backtrace_handler.{h,cpp}` | 信号注册 + FP 回溯 + dyld 缓存 | **2 项输出格式对齐** |
| arkui_for_ios | `stage/ability/StageApplication.mm` | `+initApplication:` 起始调用注册 | 无 |

### 当前架构（两 PR 初版，已合并）

两端共享约 80% 设计（AS-safe append 原语、FP 链走栈骨架、信号链转发、幂等安装）。差异集中在镜像表获取、输出通道、`#0` 帧取值方式、若干鲁棒性细节（均为平台固有或实现内部）。

## 架构设计

### 核心数据流（统一骨架，平台取值细节见下）

```
信号到达 → CrashHandler(sig, info, uc)
   ├─ g_inHandler CAS（进程级重入 guard；失败→ForwardToPrevious）
   ├─ 取崩溃上下文寄存器（fp；iOS 另取 faultPc=__ss.__pc）
   ├─ DumpSignalHeader（信号名/si_code/fault addr）
   ├─ 镜像表加载（Android: LoadMaps 实时 / iOS: LoadImages 预缓存）
   └─ DumpBacktrace
         ├─ #0 = 崩溃函数（见下“#0 取值”）
         ├─ 按 x29 链：lr=[fp+8], next=[fp], callSite=lr-4，逐帧 PrintFrame
         └─ PrintFrame：模块归属 + 符号化地址，统一格式 `  #N pc=0x<abs> <name> +0x<rel>`
   → ForwardToPrevious（链式转发旧 handler + raise 还原默认动作）
```

### #0 取值（两端均 = 崩溃指令 mcontext.pc）

| 平台 | #0 取得方式 | 结果 |
|------|------------|------|
| iOS | 显式取 `mcontext.__ss.__pc`（崩溃指令）作 #0，再走 FP 链 | #0 = 崩溃指令/函数 |
| Android | **Delta-1 已应用**：取 `mcontext.pc`（崩溃指令）作 #0，再走 FP 链（与 iOS 一致） | #0 = 崩溃指令/函数 |

> 勘误之勘误（2026-07-16 更正）：早期一度认为"Android FP 链 #0=调用者、崩函数丢失"，提议 Delta-1（补 `mcontext.pc` 作 #0）。2026-07-15 用**递归** forceCrash 栈（`#0=libentry.so+0xbb0`）又判断"Android 已捕获崩函数、Delta-1 撤销"——**这个撤销判断错了**：递归崩溃时崩函数与调用者同名（#0==#1），掩盖了"Android #0 其实是调用者 `[fp+8]-4`、崩函数那帧被丢"的事实。2026-07-16 的**非递归**用例证伪了撤销判断：多线程裸 `CrashOnGo`（#0=libc、崩函数 CrashOnGo 消失）、`forceAbort`（#0=ForceAbort 而 libc abort 帧丢失）。故 **Delta-1 重新落地**：Android 补读 `mcontext.pc` 作 #0，对齐 iOS/标准；flush 策略不变。详见 §本期 Deltas / §已撤销与恢复项。

### 平台固有差异（保留）

| 维度 | Android | iOS |
|------|---------|-----|
| 镜像表来源 | `/proc/self/maps` 实时 `open/read`（4096 条 / 1MB） | dyld 预缓存（init 时 `_dyld_*`，1024 条） |
| 符号化地址 | `pc - loadBase` → `addr2line`/`llvm-symbolizer` | `pc - slide` → `atos -arch arm64` |
| 次级输出 | 额外 `__android_log_write(FATAL,"ArkUI-x")` 逐行 | 仅 `write(STDERR)`（fd2→syslog/Console） |
| flush 策略 | 阈值批 flush（剩余<256B） | 逐帧 flush | 
| 栈边界保护 | maps 栈映射 `[fp,fp+16)⊆栈区间` 严格校验 | 16 字节对齐 + 单调递增 + 深度上限 |
| 已知限制 | — | init 后 `dlopen` 的库不在镜像表内 |

> flush 策略差异为**实现内部**：两策略对外输出逐字节等价（仅在 handler 内二次崩溃的极端情形下，逐帧 flush 丢帧更少）。非对外规格要求，不强求统一。

### 共同基线（不变）

- 全程 AS-safe：handler 内无 malloc/stdio/锁/HILOG；手写 hex/dec；仅 `open/read/write/sigaction`。
- 备用栈 64KB（`SA_ONSTACK`），仅保护注册线程。
- 进程级重入 guard `g_inHandler`：多线程并发崩溃仅首线程 dump。
- 链式转发旧 handler 后还原默认动作并 `raise` → 系统崩溃日志仍产出。
- 幂等安装 `g_installed`；`MAX_STACK_DEPTH=64`；`INSTRUCTION_LENGTH=4`。
- 对外 API：`void InitBacktraceHandler()` + `void DumpBacktraceFromFp(uintptr_t fp)`。

---

## 本期 Deltas（仅 iOS 2 项输出格式对齐）

两端输出格式统一为 `  #N pc=0x<abs> <name> +0x<rel>`（name 与 +0x 间有空格，name 完整）。Android 输出已符合（name 完整、含空格）；iOS 需 2 项对齐：

### Delta-A（iOS）：镜像名完整不截断
初版 `ImageRecord::name` 为 `char[128]` 截断拷贝。改为直接持有 dyld 名称指针（完整路径，无拷贝、无截断、无堆）。

```cpp
struct ImageRecord { uintptr_t loadAddr; intptr_t slide; const char* name; }; // 指针替数组
// LoadImages：img.name = name;   （替代 128 截断拷贝循环）
// AppendStrN → null-safe AppendStr（匹配 Android）
```

dyld 名称指针与已存储的 `loadAddr`（mach_header 指针）生命周期一致——镜像加载期间有效；ArkUI-X 共享库进程内常驻不卸载，故安全且 AS-safe（只读遍历）。

### Delta-B（iOS）：帧格式加空格
```cpp
AppendLit(buf, " +0x");   // 由 "+0x" 改为 " +0x"，与 Android 统一
```

### Deltas 汇总

| Delta | 平台 | 改动文件 | 行变化 | 状态 |
|-------|------|----------|--------|------|
| A 镜像名完整 | iOS | `osal/backtrace_handler.cpp` | ImageRecord const char* + AppendStr | ✅ 已应用（cpp +17/-17 内含此项与 B） |
| B 帧格式空格 | iOS | `osal/backtrace_handler.{cpp,h}` | " +0x" + 文档 | ✅ 已应用（h +1/-1） |
| C #0=崩溃指令（Delta-1） | Android | `entrance/java/jni/backtrace_handler.cpp` | CrashHandler 补 `mcontext.pc`；DumpBacktrace 加 faultPc 作 #0；抽 AppendFrame | ✅ 已应用（+46/-24，flush 不变） |

实测 diff：iOS cpp +17/-17、h +1/-1；Android cpp +46/-24（均在本地 adapter 仓工作副本应用）。

---

## 已撤销与恢复项

| 项 | 经过 | 当前 |
|----|------|------|
| Android #0 = mcontext.pc（Delta-1） | 最初提议 → 2026-07-15 因递归 forceCrash 栈误判而撤销 → 2026-07-16 非递归用例（多线程/abort）证伪撤销判断 → **重新落地** | ✅ 已应用（对齐 iOS/标准） |
| Android 逐帧 flush | 曾拟对齐 iOS 逐帧 flush | ❌ 不做：flush 策略为输出等价的实现内部细节，Android 保持阈值批 flush，无对外影响 |

---

## 架构决策记录（ADR）

### ADR-1：维持各 adapter 仓独立副本，不抽共享核心到 ace_engine
- **决策：** 维持独立副本。
- **理由：** 信号处理属平台/系统级（CLAUDE.md 边界“平台相关逻辑置于 adapter”）；两 adapter 独立仓，共享核心会引入跨仓依赖与平台头入核心；两 PR 已合并上线，独立副本改动最小。

### ADR-2：信号集合取 5 个（SEGV/ABRT/BUS/ILL/FPE）
- **理由：** 与两 PR 线上现状一致；ILL/FPE 同为典型崩溃信号。需求文案 3 个为下限表述。

### ADR-3：注册时机统一规则·各自实例化点
- **规则：** 平台自身信号链 handler 就绪后尽早注册。
- **实例化：** Android=`JNI_OnLoad` 运行时拉起后；iOS=`+initApplication:` 起始。

### ADR-4：输出格式对齐方向（勘误后定稿）
- **对齐：** 帧格式 `name +0x<off>`、镜像名完整——两端对齐到此（Android 已符合，iOS 2 项 deltas）。
- **勘误：** 原列“#0=崩溃PC(向iOS)”“逐帧 flush(向iOS)”两项，经真实栈验证：#0 两端已各自捕获崩溃函数（机制不同，语义对齐，无需改动）；flush 为输出等价的内部细节，不强求统一。故本期实际代码改动仅 iOS name + iOS format 两项。

---

## Performance & Memory Budget

- 常态零开销：handler 仅崩溃时执行，不在正常渲染/布局路径。
- Android 静态缓冲：`g_maps[4096]` + `g_mapsFileBuf[1MB]`（BSS，进程级，复用）。
- iOS 静态缓冲：`g_images[1024]`（无堆，名称为 dyld 指针）。
- 输出缓冲 `DumpBuffer[8192]`。

## Build 影响

- Android：`BUILD.gn` 已含 `libs=["mediandk","log"]`，本期无新增依赖、无改动。
- iOS：`osal/BUILD.gn` 已含 `backtrace_handler.cpp`，本期无新增依赖。
- 编译依赖：两端需开启 `-fno-omit-frame-pointer`（FP 链前提，推测已满足，需 build 侧确认）。

## 验证路径

1. 代码审查：iOS name 完整 + 格式空格；AS-safe 未破坏。
2. 实机：iOS 构造 SIGSEGV/abort/栈溢出，抓 Console/syslog，`atos` 符号化 #0 为崩溃函数；与 Android 输出格式比对一致。
3. 回归：系统崩溃日志（tombstone/Console）仍产出。

## 后续演进项（非本期）

| 项 | 现状 | 建议 |
|----|------|------|
| 全线程备用栈 | 仅注册线程 | 框架建线程时 hook `sigaltstack` |
| iOS 镜像表刷新 | init 后 dlopen 的库缺失 | 加载点刷新缓存（dyld 非 AS-safe，须正常上下） |
| ~~Android 精确崩溃指令~~ | 已由 Delta-1 落地（#0=`mcontext.pc`，对齐 iOS） | ✅ 完成 |
| 抽共享 AS-safe 核心 | 各仓独立 | 若第三平台接入再评估 |
