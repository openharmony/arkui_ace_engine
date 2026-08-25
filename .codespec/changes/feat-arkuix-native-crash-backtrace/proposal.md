# 需求文档 — ArkUI-X 跨平台原生崩溃栈收集（FP 链回溯）

## 一、原始需求

### 基本信息

| 字段 | 内容 |
|------|------|
| 需求ID | REQ-ARKUIX-CRASH-BACKTRACE |
| 需求名称 | 应用崩溃触发 SIGABRT/SIGSEGV/SIGBUS 等信号时，加载跨平台核心库阶段注册信号处理函数，基于崩溃寄存器（fp/x29）收集并输出原生崩溃栈 |
| 来源 | 需求 Owner 提出 |
| CodeSpec ID | feat-arkuix-native-crash-backtrace |
| 关联 PR | android https://gitcode.com/arkui-x/arkui_for_android/pull/770 ；ios https://gitcode.com/arkui-x/arkui_for_ios/pull/691 |
| 提出人 | 需求 Owner |
| 目标发行版本 | TBD |
| 候选 Profile | arkui（跨平台 adapter） |
| 优先级 | P1 |
| 状态 | Baselined |

### 原始描述

应用崩溃会触发 SIGABRT、SIGSEGV、SIGBUS 等信号。在加载跨平台核心库时，注册 SIGABRT/SIGSEGV/SIGBUS 等信号的处理函数；根据崩溃时的寄存器信息，通过 fp 寄存器实现崩溃栈收集。

**输出：应用崩溃栈。**

**范围备注：** 需求包含 iOS 与 Android。两平台规格不一致处可分开讨论。Android（PR #770）、iOS（PR #691）已实现。

### 背景证据

| 证据类型 | 链接/路径 | 说明 |
|----------|-----------|------|
| Android 实现 | `arkui_for_android/entrance/java/jni/backtrace_handler.{h,cpp}`（PR #770，已合并 master，commit bbab722） | /proc/self/maps 实时解析 + logcat 输出 |
| iOS 实现 | `arkui_for_ios/osal/backtrace_handler.{h,cpp}`（PR #691，已合并 master） | dyld 预缓存镜像表 + stderr 输出 |

### 初始范围

**包含：**
- 注册 SIGSEGV/SIGABRT/SIGBUS/SIGILL/SIGFPE 信号处理（`sigaction` + `SA_SIGINFO|SA_ONSTACK`）
- 异步信号安全（AS-safe）的崩溃栈收集：fp/x29 链回溯、镜像归属解析、可符号化地址输出
- 链式转发旧 handler，保证系统级崩溃日志仍产出
- iOS 输出格式对齐（镜像名完整 + 帧格式加空格，2 项 deltas）；Android 应用 Delta-1（#0=mcontext.pc，对齐 iOS）

**明确不包含：**
- 抽取共享核心到 ace_engine（决策：维持各 adapter 仓独立副本）
- OHOS 侧实现（OHOS 有独立 dfx/hiview 崩溃采集，不在本需求范围）
- DWARF/unwind-tables 级别的完整栈回溯（仅 FP 链，不含省略 fp 的 JIT/JS 帧）
- 崩溃栈的服务端上报/落盘管道（仅“输出”，不涉及采集后传输）

### 初始假设

| 假设 | 类型 | 验证方式 | 状态 |
|------|------|----------|------|
| 跨平台核心库 = Android `libarkui_android.so` / iOS 引擎 framework | 技术 | 源码核对 jni_load.cpp / StageApplication.mm | 已确认 |
| 两端编译开启 frame-pointer（`-fno-omit-frame-pointer`） | 技术 | 编译选项核对 | 推测（需 build 侧确认；FP 链依赖此） |
| 两端均为 arm64/aarch64 | 技术 | 平台事实 | 已确认（非 arm64 仅输出信号，不回溯） |

### 初始分级判断

| 判断项 | 结果 | 依据 |
|--------|------|------|
| 复杂度 | 标准 | 跨两 adapter 仓，原生 C/C++，无 Public ArkTS API |
| 涉及仓数量 | 2（adapter android/ios）+ 1（ace_engine 仅规格） | — |
| 是否涉及 Public/System API | 否 | 仅内部 C 接口 `InitBacktraceHandler()`/`DumpBacktraceFromFp()`，未对外暴露 |
| 是否涉及安全/性能关键路径 | 是（可靠性/AS-safe） | 信号处理路径，错误实现可致二次崩溃 |
| 是否跨 SIG | 否 | — |

---

## 二、澄清记录

### 待澄清问题与结论

| 编号 | 问题 | 结论 | 状态 |
|------|------|------|------|
| Q-1 | 代码落点：抽共享核心到 ace_engine 还是各 adapter 仓独立？ | **维持各 adapter 仓独立副本**（ADR-1） | 已澄清 |
| Q-2 | 注册信号集合：3 个（需求文案）还是 5 个（PR 现状）？ | **5 个** SEGV/ABRT/BUS/ILL/FPE（ADR-2） | 已澄清 |
| Q-3 | #0 帧是否含崩溃指令 PC？ | 勘误之勘误：2026-07-16 非递归用例（多线程/abort）证 Android 原 #0=调用者会丢崩函数；**Delta-1 已应用**（Android 补 `mcontext.pc` 作 #0，对齐 iOS）。两端 #0 = 崩溃指令 | 已澄清（勘误之勘误） |
| Q-4 | 镜像名是否截断？（iOS 截断 128，Android 完整） | **统一完整不截断**（向 Android） | 已澄清 |
| Q-5 | 帧格式 `name+0x` 还是 `name +0x`？ | **统一 `name +0x<off>`**（向 Android，含空格） | 已澄清 |
| Q-6 | 缓冲 flush 策略？（Android 阈值批，iOS 逐帧） | **统一逐帧 flush**（向 iOS，抗二次崩溃） | 已澄清 |
| Q-7 | 注册时机？（Android 晚=运行时拉起后；iOS 早=initApplication 起始） | **统一规则·各自实例化点**（ADR-3） | 已澄清 |

### 讨论记录

| 日期 | 参与人 | 讨论主题 | 结论 |
|------|--------|----------|------|
| 2026-07-15 | Owner | 代码落点 | 维持各 adapter 仓独立副本 |
| 2026-07-15 | Owner | 信号集合 | 5 个（与两 PR 一致） |
| 2026-07-16 | Owner | #0 帧 | 非递归用例（多线程裸 CrashOnGo #0=libc、forceAbort 丢 abort 帧）证 Android 原 #0=调用者会丢崩函数；Delta-1（补 mcontext.pc 作 #0）重新落地，对齐 iOS/标准 |
| 2026-07-15 | Owner | 镜像名/格式/flush | 镜像名完整、格式加空格、逐帧 flush |
| 2026-07-15 | Owner | 注册时机 | 平台自身信号链 handler 就绪后尽早注册，各自实例化点 |

---

## 三、需求基线

### 基线信息

| 字段 | 内容 |
|------|------|
| 基线版本 | v1.0 |
| 基线日期 | 2026-07-15 |
| Owner | 需求 Owner |
| 复杂度 | 标准 |
| Profile | arkui（跨平台 adapter） |
| 目标发行版本 | TBD |
| 版本状态 | proposed |

### 问题陈述

ArkUI-X 跨平台应用在 iOS/Android 上的原生（C/C++）崩溃缺乏可定位的崩溃栈：默认系统崩溃日志（tombstone/Console）对被 strip 掉 unwind 表的 `.so` 无法回溯。需求要求在加载跨平台核心库时注册崩溃信号处理函数，基于崩溃上下文寄存器（fp/x29）实现 FP 链回溯，输出可被 `addr2line`/`llvm-symbolizer`（Android）或 `atos`（iOS）直接符号化的崩溃栈。

两平台已分别由 PR #770 / #691 实现初版，但存在 4 处行为不一致（#0 帧语义、镜像名截断、帧格式、flush 策略）与若干规格未固化项。本期固化统一规格并对齐两端行为。

### 目标和成功指标

| 目标 | 成功指标 | 验证方式 |
|------|----------|----------|
| 崩溃产出可符号化栈 | 任一注册信号触发→输出 header + FP 链帧，地址可被平台符号化工具消费 | 实机崩溃 + 符号化 |
| #0 = 崩溃指令 | #0 = `mcontext.pc`（iOS `__ss.__pc`；Android 经 Delta-1 `mcontext.pc`） | 实机（多线程/abort 非递归用例验证） |
| 两端输出一致 | 帧格式 `  #N pc=0x<abs> <name> +0x<rel>`，镜像名完整 | 双端输出比对 |
| AS-safe | handler 内无 malloc/stdio/锁/HILOG | 代码审查 |
| 不破坏系统崩溃日志 | 链式转发后系统仍产出 tombstone/Console 日志 | 实机验证 |
| 幂等 | 重复 InitBacktraceHandler 不重复注册 | 代码审查 |

### 范围边界

**包含：** 信号注册、AS-safe FP 链回溯、镜像归属解析、可符号化地址、链式转发、iOS 输出格式对齐（镜像名完整 + 帧格式加空格，2 项 deltas）、Android Delta-1（#0=mcontext.pc，对齐 iOS）。
**不包含：** ace_engine 共享核心抽取、OHOS 侧实现、DWARF 完整回溯、上报/落盘管道。

### 影响范围

| 子系统 | 仓库 | 模块/路径 | 影响类型 |
|--------|------|-----------|----------|
| ArkUI-X/Android | arkui_for_android | `entrance/java/jni/backtrace_handler.{h,cpp}` | 无改动（已符合） |
| ArkUI-X/iOS | arkui_for_ios | `osal/backtrace_handler.{h,cpp}` | 修改（2 项 deltas：镜像名完整 + 帧格式加空格） |

### 进入设计/Spec 条件

- [x] 所有用户故事有 AC
- [x] 每条 AC 可测试、可度量
- [x] 范围内/外已确认
- [x] 涉及仓、模块已识别
- [x] 不涉及项已标记 N/A
- [x] 7 项决策已澄清

**基线结论:** 通过
