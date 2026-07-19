# Execution Plan — 静态自定义组件支持跨 Ability 实例迁移

> **状态**: Draft
> **关联 Design**: design.md（Approved）
> **关联 Spec**: spec.md
> **创建日期**: 2026-06-11

---

## 1. 执行概要

| 项 | 值 |
|----|-----|
| 目标 | 实现静态自定义组件跨 UIAbility 实例迁移 |
| 涉及仓库 | ace_engine（单仓，仅 ArkTS 前端层） |
| Task 数量 | 2 |
| 预计影响文件数 | 6（纯 ArkTS/TS） |
| C++ 改动 | 0 行 |
| 新增 ANI 注册 | 0 个 |
| 无新增/修改 Public API | 是 |

## 2. 工作区状态

| 检查项 | 状态 |
|--------|------|
| git 工作区干净 | 待确认 |
| 无未提交的脏改 | 待确认 |
| 基于最新 main 分支 | 待确认 |

## 3. 改动文件清单

| # | 文件路径 | 改动内容 |
|---|----------|----------|
| 1 | `arkui-ohos/src/ArkComponentRoot.ets` | `getEnvInstanceId` 闭包中合并 Env + Switch 逻辑 |
| 2 | `arkui-ohos/src/CallbackTransformer.ets` | `FreeRootNode.updateUIContext()` 条目转移；`transformFromCustomBuilder` UIContext 延迟获取 |
| 3 | `arkui-ohos/src/component/extendableComponent.ets` | 新增 `__updateUIContext__Internal`/`__updateFreeRootUIContext__Internal`/`__propagateInstanceSwitch__Internal`/`__getIExtendableDelegate__Internal` |
| 4 | `arkui-ohos/src/component/customComponent.ets` | `CustomDelegate.__updateUIContext__Internal()` 更新 uiContext |
| 5 | `arkui-ohos/src/component/staticComponents.ets` | `ArkCustomComponentRootPeer.updateFreeRootUIContext()` 遍历 freezeRoot |
| 6 | `arkui-ohos/src/base/UIContextImpl.ets` | `DetachedRootEntryManager.freezedRoots_` 从 private 改为 public |

## 4. Task 编排

### 依赖关系

```
TASK-01（核心 Switch 逻辑）  ← 无依赖
TASK-02（UIContextImpl + CallbackTransformer 优化）  ← 无依赖

TASK-01 和 TASK-02 可并行执行。
```

### Task 列表

| Task ID | 目标 | 受影响文件 | AC | 优先级 |
|---------|------|----------|-----|--------|
| TASK-01 | 核心 Switch 逻辑：Env+Switch 闭包合并、UIContext 更新、FreeRootNode 转移、子组件递归传播 | `ArkComponentRoot.ets`, `extendableComponent.ets`, `customComponent.ets`, `staticComponents.ets` | AC-1.1~1.3, AC-2.1, AC-3.1~3.3, AC-4.1, AC-6.1 | P0 |
| TASK-02 | UIContextImpl 访问限定符变更 + transformFromCustomBuilder UIContext 延迟获取 | `UIContextImpl.ets`, `CallbackTransformer.ets` | AC-6.1, AC-6.2 | P0 |

## 5. 执行顺序

| 阶段 | Task | 说明 |
|------|------|------|
| Phase 1 | TASK-01 + TASK-02 并行 | TASK-01: 核心迁移逻辑（4 个文件）；TASK-02: 前置条件修改（2 个文件） |
| Phase 2 | SPEC E2E 验证 | SPEC-001~008 参考 E2E 测试验证全部 17 个 AC |

## 6. 验证策略

| 验证层级 | 方式 | 覆盖 AC |
|---------|------|---------|
| 前端 E2E | SPEC-001~008 参考代码，hilog 断言 | 全部 17 个 AC |
| 回归验证 | 同 Ability 内操作无副作用（SPEC-005） | AC-3.1, AC-3.2 |
| 异常验证 | GC 子组件后迁移不崩溃（SPEC-006） | ER-1, ER-2 |

## 7. 交接信息

| 项 | 值 |
|----|-----|
| 设计文档 | design.md（Approved） |
| 特性规格 | spec.md |
| Task 规格 | task.md |
| 测试参考代码 | spec.md 附录 B（SPEC-001~008 完整代码） |
