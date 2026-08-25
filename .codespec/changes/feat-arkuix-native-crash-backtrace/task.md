# Task Specs — ArkUI-X 跨平台原生崩溃栈收集

> **状态**: 进行中（iOS deltas 已在工作副本应用）
> **关联 Execution Plan**: execution-plan.md
> **创建日期**: 2026-07-15

---

## TASK-IOS-ALIGN: iOS 镜像名完整 + 帧格式空格

| 项 | 值 |
|----|-----|
| 仓 | arkui_for_ios |
| 目标 | 镜像名不截断（dyld 指针直存）；帧格式 `name +0x<off>`（加空格），对齐 Android |
| 依赖 | 无 |
| 关联 AC | AC-2.2, AC-2.3 |
| 关联规则 | FR-2.2, FR-2.3 |

### 受影响文件
- `osal/backtrace_handler.cpp`
- `osal/backtrace_handler.h`

### 实现步骤
1. 移除 `constexpr size_t MAX_NAME_LEN = 128;`。
2. `ImageRecord::name`：`char name[MAX_NAME_LEN]` → `const char* name;`（注释 dyld 生命周期）。
3. `LoadImages`：删除截断拷贝循环，改为 `img.name = name;`。
4. `AppendStrN` → `AppendStr`（null-safe，NUL 终止）。
5. `PrintFrame`：`AppendStr(buf, img->name)` + `AppendLit(buf, " +0x")`。
6. `.h`：`<image>+0x` → `<image> +0x`。

### 状态
✅ 已应用（`git diff`：cpp +17/-17, h +1/-1）。

---

## TASK-VERIFY: 实机验证（iOS）

| 项 | 值 |
|----|-----|
| 目标 | 实机构造崩溃，验证 #0=崩溃函数、iOS 格式/名对齐、系统日志不破坏 |
| 依赖 | TASK-IOS-ALIGN |
| 关联 AC | 全部 |

### 步骤
1. iOS：野指针 SIGSEGV、`abort()`、栈溢出；抓 syslog/Console，`atos -arch arm64 -o <binary/dsym> <#0 rel>` 解析到崩溃函数。
2. 与 Android 输出比对：帧格式 `  #N pc=0x<abs> <name> +0x<rel>` 一致、镜像名完整。
3. 确认系统 Console 崩溃日志仍产出。

### 状态
⏳ 待 iOS 工具链/设备执行。

---

## TASK-ANDROID-ALIGN: Android #0 = mcontext.pc（Delta-1，重新落地）

### ~~TASK-ANDROID-ALIGN~~（撤销）

Delta-1（Android #0 = `mcontext.pc`）经 2026-07-16 非递归用例验证后**重新落地**：多线程裸 `CrashOnGo`（#0=libc、崩函数丢失）、`forceAbort`（abort 帧丢失）证明 Android 原 #0=调用者语义会丢崩函数。已在 adapter/android 应用（+46/-24，对齐 iOS/标准，flush 不变）。逐帧 flush 仍不做（输出等价的内部细节）。

→ 状态：✅ Delta-1 已应用（adapter/android +46/-24）；逐帧 flush 不做。
