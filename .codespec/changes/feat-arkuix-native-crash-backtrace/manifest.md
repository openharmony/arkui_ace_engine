---
id: feat-arkuix-native-crash-backtrace
type: feature
title: "ArkUI-X 跨平台原生崩溃栈收集（FP 链回溯）"
spec_schema: ohos-sdd/v1
profile: arkui
subprofiles: []
target_release:
  id: TBD
  status: proposed
complexity: standard
lineage: new-on-legacy
status: implementing
owner: "TBD (需求 Owner: longruoluo / liulong)"
source_issue: "需求 Owner 提出（对应已合并 PR: android #770、ios #691）"
created_at: 2026-07-15
updated_at: 2026-07-15
related:
  - "https://gitcode.com/arkui-x/arkui_for_android/pull/770"
  - "https://gitcode.com/arkui-x/arkui_for_ios/pull/691"
related_tasks:
  - TASK-IOS-ALIGN
related_decisions:
  - ADR-1
  - ADR-2
  - ADR-3
  - ADR-4
code_refs:
  - "arkui_for_android/entrance/java/jni/backtrace_handler.{h,cpp}"
  - "arkui_for_android/entrance/java/jni/jni_load.cpp"
  - "arkui_for_android/entrance/java/jni/BUILD.gn"
  - "arkui_for_ios/osal/backtrace_handler.{h,cpp}"
  - "arkui_for_ios/stage/ability/StageApplication.mm"
  - "arkui_for_ios/osal/BUILD.gn"
commits: []
---

# Manifest — ArkUI-X 跨平台原生崩溃栈收集（FP 链回溯）

## 需求标识

| 字段 | 内容 |
|------|------|
| 需求ID | REQ-ARKUIX-CRASH-BACKTRACE |
| 需求名称 | 应用崩溃（SIGABRT/SIGSEGV/SIGBUS 等）时，加载跨平台核心库阶段注册信号处理函数，基于崩溃寄存器（fp/x29）收集并输出原生崩溃栈 |
| feat_id | Feat-CrashBacktrace |
| 来源 | 需求 Owner 提出；Android 已实现（PR #770）、iOS 已实现（PR #691） |

## 功能域路径

```
跨平台适配 (L1) > 崩溃诊断 (L2) > 原生崩溃栈收集 (L3)
```

> 说明：本特性代码落在独立 adapter 仓 `arkui_for_android` 与 `arkui_for_ios`，不在 ace_engine 核心仓。
> 本 `.codespec` 产物作为**跨平台统一规格基线**登记在 ace_engine umbrella 仓，约束两侧 adapter 实现一致。

## 长期规格路径

| 资产 | 路径 |
|------|------|
| 长期 spec | `.codespec/changes/feat-arkuix-native-crash-backtrace/spec.md` |
| 长期 design | `.codespec/changes/feat-arkuix-native-crash-backtrace/design.md` |
| SpecTest feature | N/A（原生 C/C++ 信号处理，无 ArkUI 组件可测面） |

## 阶段状态

| 阶段 | 状态 | 产物 |
|------|------|------|
| 定义 (Stage 1) | Approved | proposal.md |
| 规格说明 (Stage 2) | Approved | spec.md, design.md |
| 设计 (Stage 3) | Approved | design.md（含 4 项对齐 deltas 设计） |
| 计划 (Stage 4) | Approved | execution-plan.md, task.md |
| 实现 | 进行中 | 4 项对齐 deltas 已在工作副本应用（android/ios），待评审合入 |

### 实现现状

- Android PR #770（`bbab722 "add backktrace"`，已合并 master）与 iOS PR #691（已合并 master）已交付初版 FP 链崩溃栈。
- **Android 应用 Delta-1**（补读 `mcontext.pc` 作 #0，对齐 iOS/标准；2026-07-16 非递归用例证伪了此前"零改动"的判断）。
- **iOS 应用 2 项输出格式 deltas**（镜像名完整 + 帧格式加空格）。
- 勘误之勘误：Delta-1 曾因 2026-07-15 递归 forceCrash 栈误判而撤销，2026-07-16 非递归用例（多线程/abort 丢失崩函数）证伪后**重新应用**（见 design.md §已撤销与恢复项）；逐帧 flush 仍不做（输出等价的内部细节）。

## baseline_approval

| 字段 | 内容 |
|------|------|
| approved | true |
| approver | 需求 Owner |
| evidence | 对话确认 7 项决策点（落点/信号/时机/输出格式对齐）；#0 经 2026-07-16 非递归用例验证后 Delta-1 重新应用（Android 补 mcontext.pc 作 #0）；flush 不统一；2026-07-16 |
| date | 2026-07-15 |
