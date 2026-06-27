# Task Specs — 静态自定义组件支持跨 Ability 实例迁移

> **状态**: Draft
> **关联 Execution Plan**: execution-plan.md
> **创建日期**: 2026-06-11

---

## TASK-01: 核心 Switch 逻辑

| 项 | 值 |
|----|-----|
| 目标 | 在 `getEnvInstanceId` 闭包中合并 Env+Switch 逻辑，实现 UIContext 更新、FreeRootNode 条目转移、子组件递归传播 |
| 依赖 | 无 |
| 关联 AC | AC-1.1~1.3, AC-2.1, AC-3.1~3.3, AC-4.1, AC-6.1 |
| 关联规则 | FR-1.1~1.3, FR-2.1~2.4, FR-3.1, FR-4.1 |

### 实现步骤

#### 1. `ArkComponentRoot.ets` — 合并 Env+Switch 闭包

在 `getEnvInstanceId` 回调中新增 Step B Switch 逻辑：
- 获取 `oldContext = switchComponent.getUIContext()`
- 幂等检查：`oldContext.getInstanceId() === newInstanceId` → 返回
- 获取 `newContext = UIContextUtil.getOrCreateUIContextById(newInstanceId)`
- 调用 `delegateComponent.__updateUIContext__Internal(newContext)`
- 调用 `peer.updateFreeRootUIContext(oldContext, newContext)`
- 调用 `switchComponent.__propagateInstanceSwitch__Internal(newInstanceId, newContext)`

#### 2. `extendableComponent.ets` — 新增接口和传播方法

- `IExtendableComponent` 接口添加 `__updateUIContext__Internal(context: UIContext)` 声明
- 新增 `__updateFreeRootUIContext__Internal(oldContext: UIContext, newContext: UIContext)` — 获取 peer，调用 `updateFreeRootUIContext`
- 新增 `__propagateInstanceSwitch__Internal(newInstanceId: int32, newContext: UIContext)` — 遍历 `childrenWeakRefMap_`，`weak.deref()` 返回 undefined 跳过，先保存 `childOldContext`，再更新子组件 UIContext/FreeRootNode，递归传播
- 新增 `__getIExtendableDelegate__Internal(): IExtendableComponent | undefined` — 返回 delegate 的接口类型

#### 3. `customComponent.ets` — CustomDelegate UIContext 更新

- `CustomDelegate` 实现 `__updateUIContext__Internal(context: UIContext)` — 更新 `this.uiContext = context`

#### 4. `staticComponents.ets` — updateFreeRootUIContext

- `ArkCustomComponentRootPeer.updateFreeRootUIContext(oldContext, newContext)` — 遍历 freezeRoot，调用 `FreeRootNode.updateUIContext`

### 受影响文件

- `arkui-ohos/src/ArkComponentRoot.ets`
- `arkui-ohos/src/component/extendableComponent.ets`
- `arkui-ohos/src/component/customComponent.ets`
- `arkui-ohos/src/component/staticComponents.ets`

### 验证方式

- SPEC-001: 迁移后 UIContext ID 更新（AC-1.1）
- SPEC-002: @State/@Watch 迁移后回调正常（AC-1.2, AC-1.3）
- SPEC-003: 冻结功能迁移后 @Monitor 正常（AC-6.1）
- SPEC-004: 父-子-孙三层传播（AC-2.1, AC-3.3）
- SPEC-005: 幂等保护（AC-3.1, AC-3.2）
- SPEC-006: GC 子组件安全跳过（ER-1, ER-2）
- SPEC-007: @ComponentV2 V2 状态管理迁移后回调正常（AC-4.1）

---

## TASK-02: UIContextImpl 访问限定符 + transformFromCustomBuilder 优化

| 项 | 值 |
|----|-----|
| 目标 | 修改 `freezedRoots_` 访问限定符为 public；将 `transformFromCustomBuilder` 中 UIContext 获取延迟到闭包内部 |
| 依赖 | 无（可与 TASK-01 并行） |
| 关联 AC | AC-6.1, AC-6.2 |
| 关联规则 | FR-2.4 |

### 实现步骤

#### 1. `UIContextImpl.ets` — freezedRoots_ 访问限定符

- 将 `DetachedRootEntryManager` 的 `freezedRoots_` 从 `private` 改为 `public`
- 目的：允许 `FreeRootNode.updateUIContext` 访问该字段进行条目转移

#### 2. `CallbackTransformer.ets` — FreeRootNode.updateUIContext + UIContext 延迟获取

- 新增 `FreeRootNode.updateUIContext(oldContext: UIContext, newContext: UIContext)`：
  - 从旧 `DetachedRootEntryManager` 取出 detachedRoots_/freezedRoots_ 条目
  - 转移到新 `DetachedRootEntryManager`
  - 更新 `this.context = newContext`
- 修改 `transformFromCustomBuilder`：将 `const context = UIContextUtil.getOrCreateCurrentUIContext()` 从方法外层移到返回的闭包内部

### 受影响文件

- `arkui-ohos/src/base/UIContextImpl.ets`
- `arkui-ohos/src/CallbackTransformer.ets`

### 验证方式

- SPEC-003: 迁移后冻结功能正常
- SPEC-006: 纯静态 UI 组件迁移正常
