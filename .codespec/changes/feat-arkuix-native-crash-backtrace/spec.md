# ArkUI-X 跨平台原生崩溃栈收集 — Spec

> ArkUI 测试设计 Spec | 版本: v0.2
> 规格口径以 `arkui_for_android`/`arkui_for_ios` adapter 仓源码事实与本 `.codespec` 产物为准。

---

## 元信息

| 字段 | 内容 |
|------|------|
| 需求编号 | REQ-ARKUIX-CRASH-BACKTRACE |
| 需求名称 | 跨平台原生崩溃栈收集（FP 链回溯） |
| 特性编号 | FEAT-CRASH-BACKTRACE |
| 需求来源 | 需求 Owner + 已合并 PR #770 / #691 |
| 优先级 | P1 |
| 目标版本 | TBD |
| SIG归属 | SIG_ArkUI（跨平台 adapter） |
| 状态 | Approved |
| 复杂度 | 标准 |
| 创建日期 | 2026-07-15 |
| 最后更新 | 2026-07-15 |

---

## 一、需求目标与规格

### 1.1 US-1：崩溃信号注册与触发

**角色：** 框架/平台开发者
**Want：** 加载跨平台核心库时注册 SIGSEGV/SIGABRT/SIGBUS/SIGILL/SIGFPE 的 AS-safe 处理函数
**以便：** 原生崩溃时能产出崩溃栈，即使 `.so` 被 strip 掉 unwind 表
**优先级：** P1

#### AC

| AC编号 | 验收标准（Given/WHEN/THEN） | 类型 |
|--------|------------------------------|------|
| AC-1.1 | Given 跨平台核心库已加载并调用 `InitBacktraceHandler()`，WHEN 进程收到 SIGSEGV/SIGABRT/SIGBUS/SIGILL/SIGFPE 任一信号，THEN 输出含信号名、`si_code`、`fault addr` 的 header | 正常 |
| AC-1.2 | Given `InitBacktraceHandler()` 已调用，WHEN 再次调用，THEN 不重复注册（幂等） | 边界 |
| AC-1.3 | Given 注册采用 `SA_SIGINFO\|SA_ONSTACK`，WHEN 触发栈溢出类崩溃（仅注册线程），THEN handler 在备用栈（64KB）上运行 | 边界 |

### 1.2 US-2：FP 链崩溃栈收集

**角色：** 框架开发者
**Want：** 基于崩溃上下文 fp/x29 走帧指针链，输出可符号化崩溃栈
**优先级：** P1

#### AC

| AC编号 | 验收标准（Given/WHEN/THEN） | 类型 |
|--------|------------------------------|------|
| AC-2.1 | Given arm64/aarch64 崩溃，THEN **#0 = 崩溃指令 `mcontext.pc`**（iOS 取 `__ss.__pc`；Android 经 Delta-1 取 `mcontext.pc`，对齐 iOS/标准） | 正常 |
| AC-2.2 | Given 帧输出格式，THEN 每帧严格为 `  #N pc=0x<abs> <name> +0x<rel>`（name 与 +0x 间有空格） | 正常 |
| AC-2.3 | Given 帧归属镜像，THEN `<name>` 为完整路径/模块名，**不截断**（无名称长度上限；iOS 原 MAX_NAME_LEN=128 已移除改 dyld 指针直存。唯一硬上界=输出缓冲 `DUMP_BUF_SIZE=8192`，由 `AppendCh` 在 `buf.len≥8191` 时静默丢弃；iOS 逐帧 flush / Android 阈值批 flush，硬上界一致；实际路径远不触及） | 正常 |
| AC-2.4 | Given 帧逐帧可见输出，THEN flush 策略为实现内部细节（Android 阈值批 / iOS 逐帧，对外输出等价），非规格硬约束 | 正常 |
| AC-2.5 | Given 非 arm64/aarch64 ABI，THEN 仅输出信号 header，不回溯 FP 链 | 边界 |
| AC-2.6 | Given fp=0，THEN 输出 `fp == 0, cannot walk the chain` 后停止 | 边界 |
| AC-2.7 | Given 回溯深度，THEN 不超过 MAX_STACK_DEPTH=64 | 边界 |

### 1.3 US-3：可符号化地址（平台固有差异）

**角色：** 框架开发者
**Want：** 输出的相对地址可被平台工具直接消费
**优先级：** P1

#### AC

| AC编号 | 验收标准（Given/WHEN/THEN） | 类型 |
|--------|------------------------------|------|
| AC-3.1 | Given Android，THEN `<rel>` = `pc - loadBase`，可被 `addr2line`/`llvm-symbolizer` 直接消费，无需手动基址修正 | 正常 |
| AC-3.2 | Given iOS，THEN `<rel>` = `pc - slide`（静态未滑移地址），可被 `atos -arch arm64` 直接消费 | 正常 |

### 1.4 US-4：链式转发与并发安全

**角色：** 框架开发者
**Want：** 不破坏系统崩溃日志，且多线程并发崩溃不互斥死锁
**优先级：** P1

#### AC

| AC编号 | 验收标准（Given/WHEN/THEN） | 类型 |
|--------|------------------------------|------|
| AC-4.1 | Given 注册时保存了旧 handler，THEN dump 完成后链式转发旧 handler，随后还原默认动作并 `raise`，系统仍产出 tombstone/Console 崩溃日志 | 正常 |
| AC-4.2 | Given 多线程并发崩溃，THEN 仅首个崩溃线程输出 backtrace（进程级 `g_inHandler` guard），其余直接转发 | 边界 |
| AC-4.3 | Given handler 执行中再次崩溃（re-entrancy），THEN 跳过 dump 直接转发，不递归 | 异常 |

---

## 二、规则定义

### 2.1 功能规则（FR）

| 规则ID | 描述 | 关联AC |
|--------|------|--------|
| FR-1.1 | `InitBacktraceHandler()` 注册 5 信号，`sigaction`+`SA_SIGINFO\|SA_ONSTACK`，幂等 | AC-1.1, AC-1.2 |
| FR-1.2 | 注册时机：平台自身信号链 handler 就绪后尽早注册（Android=JNI_OnLoad 运行时拉起后；iOS=initApplication 起始） | AC-1.1 |
| FR-2.1 | #0 = 崩溃指令 `mcontext.pc`：iOS=`__ss.__pc`；Android 经 Delta-1=`mcontext.pc`（对齐 iOS/标准） | AC-2.1 |
| FR-2.2 | 帧格式统一 `  #N pc=0x<abs> <name> +0x<rel>` | AC-2.2 |
| FR-2.3 | `<name>` 完整不截断，无最大长度上限（iOS 改 dyld 指针直存，移除 MAX_NAME_LEN=128；Android 本就指向 maps 缓冲完整名） | AC-2.3 |
| FR-2.4 | 输出逐帧可见；flush 策略为实现内部细节（输出等价） | AC-2.4 |
| FR-3.1 | Android：镜像表实时读 `/proc/self/maps`，`<rel>`=pc-loadBase | AC-3.1 |
| FR-3.2 | iOS：镜像表 init 时 dyld 预缓存，`<rel>`=pc-slide | AC-3.2 |
| FR-4.1 | 链式转发旧 handler + raise 还原默认动作 | AC-4.1 |
| FR-4.2 | 进程级 `g_inHandler` 单线程 dump | AC-4.2, AC-4.3 |

### 2.2 业务规则（BR）

| 规则ID | 描述 | 关联AC |
|--------|------|--------|
| BR-1.1 | FP 链回溯仅 arm64/aarch64；省略 fp 的帧（JIT/JS、部分三方库）终止链 | AC-2.5 |
| BR-1.2 | 备用栈仅保护注册所在线程；其他线程栈溢出可能不被捕获（规格声明限制） | AC-1.3 |
| BR-3.1 | iOS 镜像表 init 后 `dlopen` 的库不在表内（规格声明限制） | AC-3.2 |

### 2.3 异常/豁免规则（ER）

| 规则ID | 场景 | 处理方式 | 关联AC |
|--------|------|----------|--------|
| ER-1.1 | `/proc/self/maps` 或 dyld 不可用 | 镜像表为空，帧仍输出绝对 PC（无模块名/+0x） | AC-2.2 |
| ER-2.1 | fp 落在已知栈映射外（Android）或对齐失败（iOS） | 停止回溯，已输出帧保留 | AC-2.6 |
| ER-2.2 | handler 内再次崩溃 | `g_inHandler` 重入 guard 跳过 dump，直接转发 | AC-4.3 |

### 2.4 恢复契约（RC）

| 规则ID | 触发条件 | 恢复策略 | 约束 |
|--------|----------|----------|------|
| RC-1.1 | dump 完成 | 转发旧 handler；若旧为 SIG_DFL/IGN 则还原并 raise | 系统崩溃日志仍产出 |

---

## 三、2D 能力特征分析

### 3.1 是否涉及新增开放 API — **否**

仅内部 C 接口 `InitBacktraceHandler()` / `DumpBacktraceFromFp(uintptr_t fp)`，未对外暴露为 ArkTS/Public API。

### 3.2 是否涉及应用兼容性 — **是（仅 iOS 输出格式细化）**

| 字段 | 内容 |
|------|------|
| 修改前规格 | iOS 镜像名截断 128、帧格式 `name+0x`（无空格）；Android 镜像名完整、帧格式含空格 |
| 修改后规格 | 统一：镜像名完整、帧格式 `name +0x<off>`（Android 已符合，iOS 本次对齐） |
| 是否版本隔离 | 否（adapter 内部崩溃诊断输出，无对外契约） |
| changelog | iOS 对齐：镜像名完整输出 + 帧格式加空格；Android 无改动 |

### 3.3 是否涉及支持跨平台 — **是（本特性即为跨平台）**

Android（arm64-v8a）与 iOS（arm64）。两端平台固有差异见 §1.3 与 design.md，规格显式声明保留。

### 3.4 ~ 3.12（IDE预览/编译工具链/全球化/深浅色/材质/无障碍/多设备/适老化/资料） — **否 / N/A**

本特性为原生崩溃诊断，不涉及 UI 渲染、国际化、无障碍、主题等面。

---

## 四、非功能性需求（NFR）

### 4.1 性能 — **是（仅崩溃路径，非热路径）**

| 指标项 | 目标 | 验证 |
|--------|------|------|
| handler 开销 | 仅崩溃时执行，常态零开销 | 代码审查（不在正常执行路径） |
| `/proc/self/maps` 解析 | 4096 条 / 1MB 上限，覆盖 ArkUI-X 进程典型 ~3900 条 | 实机 |

### 4.2 稳定性 & 可靠性 — **是**

| 指标项 | 目标值 | 验证方法 |
|--------|--------|----------|
| AS-safe | handler 内禁 malloc/stdio/锁/HILOG | 代码审查 |
| 二次崩溃不丢栈 | flush + 重入 guard | 实机 + 代码审查 |
| 多线程并发 | 仅首线程 dump，无死锁 | 代码审查 |
| 系统日志不破坏 | 链式转发 + raise | 实机 |

### 4.3 安全隐私合规 — **否**

不采集/存储/传输隐私数据，不新增权限。

### 4.4 DFX — **是（本特性即 DFX 诊断能力）**

输出即崩溃诊断信息（stderr / logcat / Console）。

---

## 五、验证映射

| AC | 验证方式 | 当前证据 | 需新增验证 |
|----|----------|----------|--------|
| AC-1.1 | 实机 + 代码审查 | 两 PR header 格式一致 | — |
| AC-1.2 | 代码审查 | `g_installed` CAS | — |
| AC-1.3 | 代码审查 | `sigaltstack` 64KB + SA_ONSTACK | 备用栈仅注册线程的限制需文档化 |
| AC-2.1 | 实机 | Android 真实栈 #0=libentry.so+0xbb0（崩溃函数）；iOS `__ss.__pc` #0 | iOS 实机验证 #0=崩溃函数 |
| AC-2.2 | 双端输出比对 | iOS 本次统一格式（加空格）；Android 已含空格 | — |
| AC-2.3 | 代码审查 | iOS 本次去掉 128 截断；Android 本就完整 | — |
| AC-2.4 | 代码审查 | flush 策略实现内部、输出等价 | — |
| AC-2.5~2.7 | 代码审查 | 已实现 | — |
| AC-3.1 | addr2line 消费 | Android loadBase 逻辑（真实栈已验证可符号化） | — |
| AC-3.2 | atos 消费 | iOS slide 逻辑 | dyld 后加载库限制需文档化 |
| AC-4.1 | 实机 | ForwardToPrevious + raise | — |
| AC-4.2 | 代码审查 | `g_inHandler` 进程级 | — |
| AC-4.3 | 代码审查 | 重入 guard | — |

---

## 附录：术语表

| 术语 | 定义 |
|------|------|
| FP 链 | 帧指针链（x29），`[fp]=上帧fp`、`[fp+8]=LR`，逐帧回溯 |
| AS-safe | 异步信号安全：禁用 malloc/stdio/锁等非可重入调用 |
| loadBase | Android：同名 offset0 映射的起始地址（库装载基址） |
| slide | iOS：dyld ASLR 滑移量 |
| callSite | `LR - 4`，调用指令地址（aarch64 定长 4 字节） |
