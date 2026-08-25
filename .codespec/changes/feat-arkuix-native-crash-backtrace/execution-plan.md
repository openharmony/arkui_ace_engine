# 执行计划 — ArkUI-X 跨平台原生崩溃栈收集

## 计划元数据

| 字段 | 内容 |
|------|------|
| 关联 spec | spec.md / design.md |
| 复杂度 | 标准 |
| 状态 | 进行中（iOS 2 项 deltas + Android Delta-1 已在工作副本应用） |
| 创建日期 | 2026-07-15 |

## 执行策略

跨平台核心库阶段注册崩溃信号 handler、基于 fp/x29 输出可符号化崩溃栈。两端初版（PR #770/#691）已合并；本期做输出格式对齐 + Android #0 对齐：**Android 应用 Delta-1（#0=mcontext.pc，对齐 iOS/标准）；iOS 应用 2 项输出格式 deltas（镜像名完整 + 帧格式加空格）**。不抽共享核心、不新增依赖、不改对外 API。

> 勘误之勘误：Delta-1（#0=mcontext.pc）曾因 2026-07-15 递归 forceCrash 栈误判而撤销，2026-07-16 非递归用例（多线程/abort 丢失崩函数）证伪后**重新应用**；逐帧 flush 仍不做（输出等价的内部细节）。详见 design.md §已撤销与恢复项。

工作副本：`adapter/android`（master + Delta-1）、`adapter/ios`（master + 2 项 deltas）。

## 任务拆解

### Task 1: iOS 输出格式对齐（Delta-A 镜像名完整 + Delta-B 帧格式空格）
- 仓：`arkui_for_ios`
- 文件：`osal/backtrace_handler.cpp`、`osal/backtrace_handler.h`
- 步骤：
  1. 移除 `MAX_NAME_LEN=128`；`ImageRecord::name` 由 `char[128]` 改 `const char*`（dyld 指针，完整不截断）。
  2. `LoadImages` 用 `img.name = name` 替代 128 截断拷贝循环。
  3. `AppendStrN` → null-safe `AppendStr`（匹配 Android）。
  4. `PrintFrame` 用 `AppendStr(buf, img->name)` + `AppendLit(buf, " +0x")`（加空格）。
  5. `.h` 文档 `<image>+0x` → `<image> +0x`。
- 关联 AC：AC-2.2, AC-2.3
- 状态：✅ 已应用（diff: cpp +17/-17, h +1/-1）

### Task 2: 规格基线登记（ace_engine）
- 产出 manifest/lineage/proposal/spec/design/execution-plan/task + registry 更新。
- 状态：✅ 完成

### Task 3: 验证与评审
- 代码审查：iOS name 完整 + 格式空格；AS-safe 未破坏（已完成；诊断均为既有 include-path 产物）。
- 实机：iOS（野指针 SIGSEGV / abort / 栈溢出）抓 syslog/Console，`atos -arch arm64` 符号化 #0 为崩溃函数；与 Android 输出格式比对一致。
- 回归：系统 Console 崩溃日志仍产出。
- 状态：⏳ 待实机（需 iOS 工具链/设备）

### Android 任务（Delta-1 重新落地）
- Android #0 = mcontext.pc（Delta-1）：**已应用**（2026-07-16 非递归用例证伪撤销判断后重新落地，adapter/android +46/-24）。
- Android 逐帧 flush：不做（输出等价的内部细节）。

## 任务依赖关系

```
Task 2（规格） ── 指导 ──> Task 1（iOS 实现） ──> Task 3（验证）
```

## 交接信息

- iOS 工作副本改动已就绪，需在 `arkui_for_ios` 仓提 PR 评审合入（合入前补实机验证证据）。
- Android 无需改动。
- 合入后更新 manifest `commits` 与 registry status。
- 不改对外 API、不新增依赖、不触 ace_engine 核心代码。

## 实现偏差记录

- Delta-1（Android #0=mcontext.pc）经非递归用例验证后重新落地。最终实现 = iOS 2 项输出格式 + Android Delta-1，严格按 design.md §本期 Deltas。
