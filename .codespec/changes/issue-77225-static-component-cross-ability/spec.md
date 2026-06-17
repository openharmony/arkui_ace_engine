# Spec

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | 静态自定义组件支持跨 Ability 实例迁移 |
| 特性编号 | Feat-01 |
| 优先级 | P0 |
| 复杂度 | 标准（单仓） |
| 目标版本 | API 26.0.0 |

## 输入文档

| 文档 | 路径 |
|------|------|
| 需求基线 | `.codespec/changes/issue-77225-static-component-cross-ability/proposal.md` |
| 架构设计 | `.codespec/changes/issue-77225-static-component-cross-ability/design.md` |

> 需求基线、不涉及项、受影响子系统与仓库详见 proposal.md，本文档不重复摘录。design.md 与本文档并行产出，互不依赖。

## 用户故事或场景

### US-1: @Component 单组件迁移后 UIContext 和状态管理 V1 正常

**作为** 开发者, **我想要** 迁移 `@Component` 单组件到新 UIAbility 后 UIContext 和 @State/@Watch 正常工作, **以便** 组件在新 UIAbility 实例中可用。

**验收标准：**

> 使用 WHEN/THEN 格式。WHEN 描述精确的触发条件（含输入值），THEN 描述可观测的系统行为（含输出值/错误码），验证映射表须给出对应的验证方式。避免"正确处理"等模糊表述。
- **AC-1.1:** WHEN 将自定义组件从 UIAbility A（instanceId=X）通过 removeChild 移除后，再通过 appendChild 挂载到 UIAbility B（instanceId=Y，Y≠X），THEN 调用 `getUIContext().getId()` 返回值等于 Y
- **AC-1.2:** WHEN 将含 `@State message: string = 'hello'` 的自定义组件迁移到 UIAbility B 后执行 `this.message = 'world'`，THEN Text 组件渲染内容从 `[hello]` 更新为 `[world]`
- **AC-1.3:** WHEN 将含 `@State @Watch('onChanged') message` 的自定义组件迁移到 UIAbility B 后修改 message，THEN `onChanged` 回调执行且回调内 `getUIContext().getId()` 返回 UIAbility B 的 ID

### US-2: 多层子组件迁移后 UIContext 正确传播

**作为** 开发者, **我想要** 迁移含多层子组件的组件树后所有子组件 UIContext 正确传播, **以便** 复杂组件树在新 UIAbility 中完整可用。

**验收标准：**
- **AC-2.1:** WHEN 将含父-子-孙三层 @Component 组件树的父组件从 UIAbility A 迁移到 UIAbility B 后，THEN 父组件的 `getUIContext().getId()` 返回 B 的 ID，子组件的 `getUIContext().getId()` 返回 B 的 ID，孙组件的 `getUIContext().getId()` 返回 B 的 ID

### US-3: 同 UIAbility 内操作无副作用

**作为** 开发者, **我想要** 在同一 UIAbility 内操作组件时行为无副作用, **以便** 迁移逻辑不影响正常使用场景。

**验收标准：**
- **AC-3.1:** WHEN 组件首次在 UIAbility A（instanceId=X）中通过 `BuilderNode.build()` + `appendChild` 创建并挂载（源 ID === 目标 ID），THEN `@Watch` 回调正常触发、UI 正常渲染，hilog 无异常日志
- **AC-3.2:** WHEN 组件已在 UIAbility B（instanceId=Y）中，再次调用 `NodeController.makeNode(UIContext_Y)` 传入相同 UIAbility 的 UIContext（源 ID === 目标 ID），THEN 组件行为无变化，无额外 UIContext 更新日志
- **AC-3.3:** WHEN 将没有子组件的叶节点 @Component 自定义组件从 UIAbility A 迁移到 UIAbility B 后，THEN `getUIContext().getId()` 返回 B 的 ID，Text 组件渲染正常

### US-4: @ComponentV2 迁移后状态管理 V2 正常

**作为** 开发者, **我想要** 迁移 `@ComponentV2` 组件后状态管理 V2 全部机制正常, **以便** V2 装饰器在新 UIAbility 中完整可用。

**验收标准：**
- **AC-4.1:** WHEN 将 `@ComponentV2` 装饰的自定义组件从 UIAbility A 迁移到 UIAbility B 后，THEN `getUIContext().getId()` 返回 B 的 ID
- **AC-4.2:** WHEN 将含 `@Local message: string = 'hello'` 的 `@ComponentV2` 组件迁移到 UIAbility B 后执行 `this.message = 'world'`，THEN Text 组件渲染内容更新为 `world`
- **AC-4.3:** WHEN 将含 `@Local message` + `@Monitor(['message'])` 的 `@ComponentV2` 组件迁移到 UIAbility B 后修改 message，THEN `@Monitor` 回调执行且回调内 `getUIContext().getId()` 返回 B 的 ID
- **AC-4.4:** WHEN 将使用 `@Provider('theme') theme: string = 'dark'` + `@Consumer('theme')` 的 `@ComponentV2` 组件迁移到 UIAbility B 后执行 `this.theme = 'light'`，THEN Consumer 组件的 theme 值同步更新为 `light`，Text 渲染为 `Consumer theme: light`
- **AC-4.5:** WHEN 将使用 `@Param count: number` + `@Event onCountChange: (val: number) => void` 的 `@ComponentV2` 子组件迁移到 UIAbility B 后，THEN 父组件通过 `@Param` 传入的 count 值在子组件中正确显示，子组件调用 `this.onCountChange(1)` 后父组件 `parentCount` 从 0 变为 1

### US-5: @Reusable/@ReusableV2 迁移后生命周期正常

**作为** 开发者, **我想要** 迁移 `@Reusable`/`@ReusableV2` 组件后回收/复用生命周期正常, **以便** 组件复用机制在新 UIAbility 中工作。

**验收标准：**
- **AC-5.1:** WHEN 将 `@Reusable` + `@Component` 自定义组件迁移到 UIAbility B 后触发 removeChild（组件回收），THEN `aboutToRecycle()` 回调执行且 hilog 输出 `recycleCount` 递增
- **AC-5.2:** WHEN 将 `@Reusable` + `@Component` 自定义组件迁移到 UIAbility B 并回收后，通过 appendChild 重新添加（组件复用），THEN `aboutToReuse()` 回调执行且回调内 `getUIContext().getId()` 返回 B 的 ID
- **AC-5.3:** WHEN 将 `@ReusableV2` + `@ComponentV2` 组件迁移到 UIAbility B 后触发 removeChild（回收）再 appendChild（复用），THEN `aboutToRecycle()` 和 `aboutToReuse()` 回调均执行

### US-6: 迁移后冻结功能正常

**作为** 开发者, **我想要** 迁移后自定义组件冻结功能能够正常生效, **以便** 冻结/解冻行为在新 UIAbility 中与迁移前一致。

**验收标准：**
- **AC-6.1:** WHEN 将使用冻结功能的自定义组件迁移到 UIAbility B 后，将组件设为不可见（触发冻结），THEN 冻结期间修改 `@Local` 变量时 `@Monitor` 不触发、UI 不更新；恢复可见（解冻）后组件正确渲染最新状态
- **AC-6.2:** WHEN 将含冻结子组件的父组件迁移到 UIAbility B 后，THEN 子组件的冻结功能在新 UIAbility 中正常生效（冻结/解冻行为正确）

## 业务规则

| 规则 ID | 规则描述 | 约束条件 | 关联 AC |
|---------|----------|----------|---------|
| FR-1.1 | 通过 `FrameNode.removeChild` 从 UIAbility A 移除后，再通过 `FrameNode.appendChild` 挂载到 UIAbility B 时触发跨 Ability 迁移逻辑 | removeChild 和 appendChild 必须是配对操作 | AC-1.1 |
| FR-1.2 | 首次创建并 `appendChild` 挂载到自身 UIAbility 时不触发迁移更新 | 源 ID === 目标 ID | AC-3.1, AC-3.2 |
| FR-1.3 | 跨 Ability 迁移时（源 ID ≠ 目标 ID）触发完整迁移逻辑 | 仅限 `'use static'` 静态组件 | AC-1.1, AC-3.3 |
| FR-2.1 | 迁移后 `getUIContext()` 返回新 UIAbility 的 UIContext，`getId()` 返回新 UIAbility 的 ID | — | AC-1.1, AC-4.1 |
| FR-2.2 | 迁移后 `@State` 变量修改仍能驱动 UI 刷新、`@Watch` 回调仍能正常触发 | 组件必须含 V1 状态变量 | AC-1.2, AC-1.3 |
| FR-2.3 | 迁移时子组件递归传播：父组件迁移传播到所有子组件和孙组件均更新 UIContext | 递归遍历 DFS，弱引用访问子节点 | AC-2.1 |
| FR-2.4 | 迁移后组件冻结功能在新 UIAbility 中正常生效 | 冻结/解冻行为与迁移前一致 | AC-6.1, AC-6.2 |
| FR-3.1 | 幂等保护：组件当前 ID 与新 ID 相同时跳过 UIContext 和子组件传播更新 | — | AC-3.1, AC-3.2 |
| FR-4.1 | `@ComponentV2` 装饰的自定义组件同样支持跨 Ability 迁移 | — | AC-4.1~4.5 |
| FR-5.1 | `@ComponentV2` 迁移后 `@Local` 驱动 UI 刷新、`@Monitor` 回调正常触发 | — | AC-4.2, AC-4.3 |
| FR-5.2 | `@ComponentV2` 迁移后 `@Provider`/`@Consumer` 状态共享正常 | Provider 和 Consumer 在同一迁移子树内 | AC-4.4 |
| FR-5.3 | `@ComponentV2` 迁移后 `@Param` 传值和 `@Event` 回调正常 | 父子组件在同一迁移子树内 | AC-4.5 |
| FR-6.1 | `@Reusable`/`@ReusableV2` 迁移后 `aboutToRecycle` 回调正常触发 | — | AC-5.1, AC-5.3 |
| FR-6.2 | `@Reusable`/`@ReusableV2` 迁移后 `aboutToReuse` 回调正常触发且回调内 ID 为新 Ability 的 ID | — | AC-5.2, AC-5.3 |

## 异常与边界规则

> 超时操作必须给出精确阈值（ms/s），不可写"待定义"。跨进程字段必须给出精确限制（字节数/长度）。

| 编号 | 场景 | 触发条件 | 系统行为 | 关联 AC |
|------|------|----------|----------|---------|
| EX-1 | 子组件已被 GC 回收 | 迁移时递归遍历子树，弱引用返回 undefined（子组件已被 GC 回收） | 安全跳过该子节点，继续处理下一个子节点，不影响父组件迁移完成；hilog 输出警告日志 | AC-2.1 |
| EX-2 | 纯静态 UI 组件（无状态变量） | 迁移的组件不含 `@State`/`@Local`/`@Watch`/`@Monitor` 等任何状态装饰器 | 仅更新 UIContext 引用，不执行状态绑定更新；迁移后 UI 正常渲染 | AC-3.3 |

## 错误码定义

> 本特性为框架内部行为增强，不新增/修改错误码。迁移失败时组件保持原有 UIContext 不变，不产生新的错误码。

N/A

## 接口变更分析

### 新增接口

无新增接口。

### 变更/废弃接口

无变更/废弃接口。

## 兼容性声明

- **已有 API 行为变更:** 否。所有 Public API 行为不变，本次仅增强框架内部迁移逻辑。
- **配置文件格式变更:** 否。
- **数据存储格式变更:** 否。

## 验证映射

| AC | 关联规则 | 验证方式 | 证据 |
|----|----------|----------|------|
| AC-1.1 | FR-2.1, FR-1.3 | 前端 E2E：创建组件在 Ability A，迁移到 Ability B，hilog 断言 `getId()` 返回 B 的 ID | SPEC-001 |
| AC-1.2 | FR-2.2 | 前端 E2E：迁移后修改 @State，hilog 断言 Text 内容更新 | SPEC-002 |
| AC-1.3 | FR-2.2 | 前端 E2E：迁移后修改 @State，hilog 断言 @Watch 回调触发且 count 递增 | SPEC-002 |
| AC-2.1 | FR-2.3 | 前端 E2E：三层组件树迁移，hilog 断言三层 aboutToAppear 的 ID 均为 B | SPEC-004 |
| AC-3.1 | FR-3.1 | 前端 E2E：首次挂载，hilog 断言 @Watch 正常、无异常日志 | SPEC-005 |
| AC-3.2 | FR-3.1 | 前端 E2E：同 Ability 重复 makeNode，hilog 断言无额外更新 | SPEC-005 |
| AC-3.3 | FR-1.3 | 前端 E2E：叶节点组件迁移，hilog 断言 ID 变更且 UI 正常 | SPEC-004 |
| AC-4.1 | FR-4.1, FR-5.1 | 前端 E2E：@ComponentV2 迁移后 hilog 断言 getId() 为 B 的 ID | SPEC-007 |
| AC-4.2 | FR-5.1 | 前端 E2E：迁移后修改 @Local，hilog 断言 Text 更新 | SPEC-007 |
| AC-4.3 | FR-5.1 | 前端 E2E：迁移后修改 @Local，hilog 断言 @Monitor 触发 | SPEC-007 |
| AC-4.4 | FR-5.2 | 前端 E2E：@Provider/@Consumer 迁移后修改 Provider，hilog 断言 Consumer 同步 | SPEC-007 |
| AC-4.5 | FR-5.3 | 前端 E2E：@Param/@Event 迁移后触发 Event，hilog 断言父组件回调执行 | SPEC-007 |
| AC-5.1 | FR-6.1 | 前端 E2E：@Reusable 迁移后回收，hilog 断言 aboutToRecycle 触发 | SPEC-008 |
| AC-5.2 | FR-6.2 | 前端 E2E：@Reusable 迁移后复用，hilog 断言 aboutToReuse 触发且 ID 为 B | SPEC-008 |
| AC-5.3 | FR-6.2 | 前端 E2E：@ReusableV2 迁移后回收+复用，hilog 断言两个回调触发 | SPEC-008 |
| AC-6.1 | FR-2.4 | 前端 E2E：冻结功能迁移后冻结/解冻，hilog 断言 @Monitor 不触发/恢复 | SPEC-003 |
| AC-6.2 | FR-2.4 | 前端 E2E：含冻结子组件迁移，hilog 断言子组件冻结正常 | SPEC-003 |

## 代码映射

| AC 编号 | 预期实现模块/文件 | 实际实现文件 | 关联 Task | 验证状态（Pass/Fail/Blocked） |
|---------|------------------|-------------|-----------|---------|
| AC-1.1 | `arkui-ohos/src/ArkComponentRoot.ets`（Env+Switch 闭包合并） | `arkui-ohos/src/ArkComponentRoot.ets` | TASK-01 | Pass |
| AC-1.1 | `arkui-ohos/src/component/customComponent.ets`（UIContext 更新） | `arkui-ohos/src/component/customComponent.ets` | TASK-01 | Pass |
| AC-1.2 | `arkui-ohos/src/ArkComponentRoot.ets`（Env 通路复用，@State/@Watch 通过 Env 重注册自动生效） | `arkui-ohos/src/ArkComponentRoot.ets` | TASK-01 | Pass |
| AC-1.3 | `arkui-ohos/src/ArkComponentRoot.ets`（Env 通路复用，@State/@Watch 通过 Env 重注册自动生效） | `arkui-ohos/src/ArkComponentRoot.ets` | TASK-01 | Pass |
| AC-2.1 | `arkui-ohos/src/component/extendableComponent.ets`（递归传播） | `arkui-ohos/src/component/extendableComponent.ets` | TASK-01 | Pass |
| AC-3.1 | `arkui-ohos/src/ArkComponentRoot.ets`（两层幂等保护） | `arkui-ohos/src/ArkComponentRoot.ets` | TASK-01 | Pass |
| AC-3.2 | `arkui-ohos/src/ArkComponentRoot.ets`（两层幂等保护） | `arkui-ohos/src/ArkComponentRoot.ets` | TASK-01 | Pass |
| AC-3.3 | `arkui-ohos/src/component/extendableComponent.ets`（叶节点传播，childrenWeakRefMap_ 为空时安全跳过） | `arkui-ohos/src/component/extendableComponent.ets` | TASK-01 | Pass |
| AC-4.1 | `arkui-ohos/src/ArkComponentRoot.ets`（Env+Switch 闭包合并，@ComponentV2 复用同一通路） | `arkui-ohos/src/ArkComponentRoot.ets` | TASK-01 | Pass |
| AC-4.2 | `arkui-ohos/src/ArkComponentRoot.ets`（Env 通路复用，@Local/@Monitor 通过 Env 重注册自动生效） | `arkui-ohos/src/ArkComponentRoot.ets` | TASK-01 | Pass |
| AC-4.3 | `arkui-ohos/src/ArkComponentRoot.ets`（同 AC-4.2） | `arkui-ohos/src/ArkComponentRoot.ets` | TASK-01 | Pass |
| AC-4.4 | `arkui-ohos/src/ArkComponentRoot.ets`（同 AC-4.2） | `arkui-ohos/src/ArkComponentRoot.ets` | TASK-01 | Pass |
| AC-4.5 | `arkui-ohos/src/ArkComponentRoot.ets`（同 AC-4.2） | `arkui-ohos/src/ArkComponentRoot.ets` | TASK-01 | Pass |
| AC-5.1 | `arkui-ohos/src/ArkComponentRoot.ets`（Env 通路复用，@Reusable 生命周期通过 Env 重注册自动生效） | `arkui-ohos/src/ArkComponentRoot.ets` | TASK-01 | Pass |
| AC-5.2 | `arkui-ohos/src/ArkComponentRoot.ets`（同 AC-5.1） | `arkui-ohos/src/ArkComponentRoot.ets` | TASK-01 | Pass |
| AC-5.3 | `arkui-ohos/src/ArkComponentRoot.ets`（同 AC-5.1） | `arkui-ohos/src/ArkComponentRoot.ets` | TASK-01 | Pass |
| AC-6.1 | `arkui-ohos/src/CallbackTransformer.ets` + `arkui-ohos/src/component/staticComponents.ets`（FreeRootNode 条目转移） | `arkui-ohos/src/CallbackTransformer.ets`, `arkui-ohos/src/component/staticComponents.ets` | TASK-01, TASK-02 | Pass |
| AC-6.2 | `arkui-ohos/src/CallbackTransformer.ets` + `arkui-ohos/src/component/staticComponents.ets`（FreeRootNode 条目转移） | `arkui-ohos/src/CallbackTransformer.ets`, `arkui-ohos/src/component/staticComponents.ets` | TASK-01, TASK-02 | Pass |

---

## 附录 A：行为场景（Gherkin）

### SPEC-001: 跨 Ability 迁移后 UIContext 更新

```gherkin
Feature: UIContext 更新
  作为开发者
  我想要迁移后组件的 UIContext 正确更新
  以便组件在新 UIAbility 中正常工作

  Scenario: 完整迁移后 UIContext 更新 (SPEC-001-S01)
    Given 在 UIAbility A 中创建 BuilderNode 并构建自定义组件
    And 组件已通过 appendChild 挂载到 UIAbility A 的 NodeContainer
    When 组件从 UIAbility A 移除 (removeChild)
    And 拉起 UIAbility B (startAbility)
    And 组件通过 appendChild 挂载到 UIAbility B 的 NodeContainer
    Then 调用 getUIContext().getId() 返回 UIAbility B 的 ID
    And 组件 UI 正常渲染

  Scenario: 未挂载即迁移 (SPEC-001-S02)
    Given 在 UIAbility A 中创建 BuilderNode 并构建自定义组件（未 appendChild）
    When 拉起 UIAbility B
    And 组件通过 appendChild 直接挂载到 UIAbility B 的 NodeContainer
    Then 调用 getUIContext().getId() 返回 UIAbility B 的 ID
    And 组件 UI 正常渲染
```

### SPEC-002: 跨 Ability 迁移后 @State 和 @Watch 正常工作

```gherkin
Feature: @State/@Watch 迁移
  作为开发者
  我想要迁移后 @State 驱动 UI 刷新和 @Watch 回调正常
  以便状态管理在新 UIAbility 中正常

  Scenario: 迁移前后修改 @State (SPEC-002-S01)
    Given 组件含 @State @Watch('onChanged') message = 'hello'
    And 组件在 UIAbility A 中已挂载
    When 修改 message = 'hello world'（@Watch count=1）
    And 迁移组件到 UIAbility B
    And 修改 message = 'hello world world'（迁移后首次修改）
    Then @Watch count=2，回调中 instanceId 为 B 的 ID
    And Text 显示 "message: hello world world"

  Scenario: 迁移后首次修改 @State (SPEC-002-S02)
    Given 组件含 @State @Watch message = 'hello'
    And 组件从 UIAbility A 迁移到 UIAbility B
    When 在 UIAbility B 中修改 message（首次修改）
    Then @Watch count=1，回调中 instanceId 为 B 的 ID
    And UI 正常刷新
```

### SPEC-003: 跨 Ability 迁移后组件冻结功能正常

```gherkin
Feature: 冻结功能迁移
  作为开发者
  我想要迁移后组件冻结功能正常生效
  以便冻结/解冻行为在新 UIAbility 中一致

  Scenario: 迁移后冻结/解冻 (SPEC-003-S01)
    Given @ComponentV2 组件含 @Local message 和 @Monitor
    And 组件从 UIAbility A 迁移到 UIAbility B
    When 将组件设为不可见（触发冻结）
    Then @Monitor 不触发，UI 不更新
    When 将组件恢复可见（触发解冻）
    Then 组件恢复正确渲染，状态更新生效

  Scenario: 迁移前后冻结行为对比 (SPEC-003-S02)
    Given 同上
    When 分别在迁移前后执行相同的冻结/解冻操作
    Then 两次行为完全一致

  Scenario: 含冻结子组件的父组件迁移 (SPEC-003-S03)
    Given 父组件含使用冻结功能的子组件
    And 父组件从 UIAbility A 迁移到 UIAbility B
    Then 子组件冻结功能在新 UIAbility 中正常生效
```

### SPEC-004: 子组件递归传播

```gherkin
Feature: 子组件递归传播
  作为开发者
  我想要迁移父组件后所有子组件的 UIContext 正确更新
  以便多层组件树在新 UIAbility 中完整可用

  Scenario: 三层组件树迁移 (SPEC-004-S01)
    Given 含父-子-孙三层组件树的父组件在 UIAbility A 中
    When 迁移到 UIAbility B
    Then 父组件 getUIContext().getId() 返回 B 的 ID
    And 子组件 getUIContext().getId() 返回 B 的 ID
    And 孙组件 getUIContext().getId() 返回 B 的 ID

  Scenario: 叶节点组件迁移 (SPEC-004-S02)
    Given 无子组件的叶节点自定义组件
    When 迁移到 UIAbility B
    Then getUIContext().getId() 返回 B 的 ID
    And 无异常
```

### SPEC-005: 幂等保护

```gherkin
Feature: 幂等保护
  作为开发者
  我想要同 Ability 内操作组件时无副作用
  以便迁移逻辑不影响正常使用

  Scenario: 首次挂载不触发迁移 (SPEC-005-S01)
    Given 在 UIAbility A 中创建自定义组件
    When 首次 appendChild 挂载到 UIAbility A 的 NodeContainer
    Then @Watch 正常触发，UI 正常渲染
    And 无异常行为

  Scenario: 同 Ability 重复挂载无副作用 (SPEC-005-S02)
    Given 组件已在 UIAbility A 中挂载
    When removeChild 后再次 appendChild（同一 UIAbility）
    Then 组件行为无变化，无副作用
```

### SPEC-006: 异常安全

```gherkin
Feature: 异常安全
  作为开发者
  我想要迁移时遇到异常不崩溃
  以便系统稳定性不受影响

  Scenario: 子组件 GC 后迁移父组件 (SPEC-006-S01)
    Given 父组件含可被 GC 回收的子组件
    When 子组件被移除并触发 GC
    And 迁移父组件到 UIAbility B
    Then 父组件 UIContext 正确更新
    And 无崩溃，无异常

  Scenario: 纯静态 UI 组件迁移 (SPEC-006-S02)
    Given 不含任何状态变量的纯静态 UI 组件
    When 迁移到 UIAbility B
    Then UI 正常渲染，无异常
```

### SPEC-007: @ComponentV2 跨 Ability 迁移

```gherkin
Feature: 状态管理 V2 迁移
  作为开发者
  我想要 @ComponentV2 组件迁移后全部 V2 机制正常
  以便状态管理 V2 在新 UIAbility 中完整可用

  Scenario: @Local + @Monitor 迁移 (SPEC-007-S01/S02)
    Given @ComponentV2 组件含 @Local message 和 @Monitor
    And 组件从 UIAbility A 迁移到 UIAbility B
    When 修改 @Local message
    Then @Monitor 回调正常触发
    And getUIContext().getId() 返回 B 的 ID
    And UI 正常刷新

  Scenario: @Provider/@Consumer 迁移 (SPEC-007-S03)
    Given @ComponentV2 组件使用 @Provider/@Consumer 共享状态
    And 组件从 UIAbility A 迁移到 UIAbility B
    When 修改 Provider 状态
    Then Consumer 正确同步
    And UI 正确显示

  Scenario: @Param/@Event 迁移 (SPEC-007-S04)
    Given @ComponentV2 父子组件使用 @Param/@Event
    And 组件从 UIAbility A 迁移到 UIAbility B
    When 子组件触发 @Event
    Then 父组件回调正常触发
    And @Param 传值正确
```

### SPEC-008: 组件复用迁移

```gherkin
Feature: 组件复用迁移
  作为开发者
  我想要 @Reusable/@ReusableV2 组件迁移后生命周期正常
  以便回收/复用在新 UIAbility 中正常

  Scenario: @Reusable 迁移后回收 (SPEC-008-S01)
    Given @Reusable 组件从 UIAbility A 迁移到 UIAbility B
    When 在 UIAbility B 中触发组件回收（removeChild）
    Then aboutToRecycle 回调正常触发
    And 回调中 getUIContext().getId() 返回 B 的 ID

  Scenario: @Reusable 迁移后复用 (SPEC-008-S02)
    Given @Reusable 组件在 UIAbility B 中已被回收
    When 重新 add 触发复用
    Then aboutToReuse 回调正常触发
    And 回调中 getUIContext().getId() 返回 B 的 ID

  Scenario: @ReusableV2 迁移后回收和复用 (SPEC-008-S03)
    Given @ReusableV2 + @ComponentV2 组件从 UIAbility A 迁移到 UIAbility B
    When 在 UIAbility B 中触发回收和复用
    Then aboutToRecycle 和 aboutToReuse 回调正常触发
    And 回调中 ID 为 B 的 ID
```

---

## 附录 B：参考代码

> 以下提供端到端示例代码，用于 E2E 测试验证。每个 SPEC 包含 4 个文件：NodeController、Component、Index（Ability A）、ExtraIndex（Ability B）。所有 SPEC 共享 UIAbility 生命周期文件。

### UIAbility 生命周期文件（所有 SPEC 通用）

`EntryAbility.ets`（UIAbility A）：
```typescript
import UIAbility from '@ohos.app.ability.UIAbility';
import AbilityConstant from '@ohos.app.ability.AbilityConstant';
import Want from '@ohos.app.ability.Want';
import window from '@ohos.window';
import { BusinessError } from '@ohos.base';
import hilog from '@ohos.hilog';

export default class EntryAbility extends UIAbility {
  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {
    hilog.info(0x0000, 'testTag', 'EntryAbility onCreate');
  }
  onWindowStageCreate(windowStage: window.WindowStage): void {
    hilog.info(0x0000, 'testTag', 'EntryAbility onWindowStageCreate');
    windowStage.loadContent('pages/Index', (err: BusinessError<void> | null): void => {
      if (err && err.code) {
        hilog.info(0x0000, 'testTag', 'loadContent error');
        return;
      }
      hilog.info(0x0000, 'testTag', 'loadContent ok');
    });
  }
}
```

`ExtraAbility.ets`（UIAbility B）：
```typescript
import UIAbility from '@ohos.app.ability.UIAbility';
import AbilityConstant from '@ohos.app.ability.AbilityConstant';
import Want from '@ohos.app.ability.Want';
import window from '@ohos.window';
import { BusinessError } from '@ohos.base';
import hilog from '@ohos.hilog';

export default class ExtraAbility extends UIAbility {
  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {
    hilog.info(0x0000, 'testTag', 'ExtraAbility onCreate');
  }
  onWindowStageCreate(windowStage: window.WindowStage): void {
    hilog.info(0x0000, 'testTag', 'ExtraAbility onWindowStageCreate');
    windowStage.loadContent('extraability/ExtraIndex', (err: BusinessError<void> | null): void => {
      if (err && err.code) {
        hilog.info(0x0000, 'testTag', 'loadContent error');
        return;
      }
      hilog.info(0x0000, 'testTag', 'loadContent ok');
    });
  }
}
```

### SPEC-001 参考代码

`pages/NodeController_Spec001.ets`：
```typescript
'use static'
import { BuilderNode, FrameNode, NodeController, UIContext, wrapBuilder } from '@kit.ArkUI';
import hilog from '@ohos.hilog';

const DOMAIN = 0x0000;
const TAG = 'Spec001';
let globalBuilderNode: BuilderNode | undefined = undefined;

export class NodeController001 extends NodeController {
  private rootNode: FrameNode | null = null;
  private uiContext: UIContext | null = null;

  makeNode(uiContext: UIContext): FrameNode | null {
    this.rootNode = new FrameNode(uiContext);
    this.uiContext = uiContext;
    hilog.info(DOMAIN, TAG, `makeNode called, instanceId = ${uiContext.getId()}`);
    return this.rootNode;
  }

  addBuilderNode(): void {
    if (!globalBuilderNode && this.uiContext) {
      globalBuilderNode = new BuilderNode<undefined>(this.uiContext as UIContext);
      globalBuilderNode!.build(wrapBuilder(buildComponent001));
      hilog.info(DOMAIN, TAG,
        `BuilderNode created with instanceId = ${this.uiContext.getId()}`);
    }
    if (this.rootNode && globalBuilderNode) {
      this.rootNode!.appendChild(globalBuilderNode!.getFrameNode()!);
      hilog.info(DOMAIN, TAG, 'appendChild done');
    }
  }

  removeBuilderNode(): void {
    if (this.rootNode && globalBuilderNode) {
      this.rootNode!.removeChild(globalBuilderNode!.getFrameNode()!);
      hilog.info(DOMAIN, TAG, 'removeChild done');
    }
  }

  disposeNode(): void {
    if (this.rootNode && globalBuilderNode) {
      globalBuilderNode!.dispose();
      globalBuilderNode = undefined;
      hilog.info(DOMAIN, TAG, 'dispose done');
    }
  }
}

import { buildComponent001 } from './Component_Spec001';
```

`pages/Component_Spec001.ets`：
```typescript
'use static'
import { Builder, Component, State, Text, Column, ColumnOptions } from '@kit.ArkUI';
import hilog from '@ohos.hilog';

const DOMAIN = 0x0000;
const TAG = 'Spec001';

@Builder
export function buildComponent001() {
  Column() {
    Spec001Component()
  }
}

@Component
export struct Spec001Component {
  @State label: string = 'hello';

  aboutToAppear(): void {
    const id = this.getUIContext().getId();
    hilog.info(DOMAIN, TAG, `aboutToAppear, instanceId = ${id}, label = ${this.label}`);
  }

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Text(`[${TAG}] label: ${this.label}`)
    }
  }
}
```

`pages/Index.ets`（UIAbility A 入口）：
```typescript
'use static'
import { Entry, Component, Column, Text, Button, NodeContainer, ColumnOptions } from '@kit.ArkUI';
import { NodeController001 } from './NodeController_Spec001';
import hilog from '@ohos.hilog';
import common from '@ohos.app.ability.common';
import Want from '@ohos.app.ability.Want';

const DOMAIN = 0x0000;

@Entry
@Component
struct Index {
  private nodeController: NodeController001 = new NodeController001();

  startExtraAbility() {
    const want: Want = {
      bundleName: 'com.example.customcomponentcross',
      abilityName: 'ExtraAbility'
    };
    const context = this.getUIContext()?.getHostContext() as common.UIAbilityContext;
    context!.startAbility(want);
    hilog.info(DOMAIN, 'Index', 'startExtraAbility sent');
  }

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Text('AbilityA - Index')
      Button('1. add node to tree')
        .width(250)
        .onClick(() => { this.nodeController.addBuilderNode(); })
      Button('2. remove node from tree')
        .width(250)
        .onClick(() => { this.nodeController.removeBuilderNode(); })
      Button('3. start ExtraAbility')
        .width(250)
        .onClick(() => { this.startExtraAbility(); })
      NodeContainer(this.nodeController)
        .backgroundColor('#FFEEF0')
    }
    .width('100%')
    .height('100%')
  }
}
```

`extraability/ExtraIndex.ets`（UIAbility B 入口）：
```typescript
'use static'
import { Entry, Component, Column, Text, Button, NodeContainer, ColumnOptions } from '@kit.ArkUI';
import { NodeController001 } from '../pages/NodeController_Spec001';
import hilog from '@ohos.hilog';

const DOMAIN = 0x0000;

@Entry
@Component
struct ExtraIndex {
  private nodeController: NodeController001 = new NodeController001();

  aboutToAppear(): void {
    hilog.info(DOMAIN, 'ExtraIndex',
      `aboutToAppear, current instanceId = ${this.getUIContext().getId()}`);
  }

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Text('AbilityB - ExtraIndex')
      Button('4. add node to tree (re-attach)')
        .width(280)
        .onClick(() => { this.nodeController.addBuilderNode(); })
      Button('5. verify instanceId')
        .width(280)
        .onClick(() => {
          const currentId = this.getUIContext().getId();
          hilog.info(DOMAIN, 'ExtraIndex',
            `verify: current Ability instanceId = ${currentId}`);
        })
      Button('6. remove node')
        .width(280)
        .onClick(() => { this.nodeController.removeBuilderNode(); })
      Button('7. dispose node')
        .width(280)
        .onClick(() => { this.nodeController.disposeNode(); })
      NodeContainer(this.nodeController)
        .backgroundColor('#E0F0E0')
    }
    .width('100%')
    .height('100%')
  }
}
```

**SPEC-001 操作步骤**：

| 步骤 | 操作 | 预期日志 |
|------|------|---------|
| 1 | AbilityA: 点击 "add node to tree" | `BuilderNode created with instanceId = <A>`；`aboutToAppear, instanceId = <A>`；`appendChild done` |
| 2 | 点击 "remove node from tree" | `removeChild done` |
| 3 | 点击 "start ExtraAbility" | AbilityB 页面出现 |
| 4 | AbilityB: 点击 "add node to tree (re-attach)" | `makeNode called, instanceId = <B>`；`appendChild done` |
| 5 | 点击 "verify instanceId" | `verify: current Ability instanceId = <B>` |
| **断言** | 对比步骤1和步骤4 | aboutToAppear 中 ID 从 `<A>` 变为 `<B>` |

> 以下 SPEC-002~008 中，Index.ets（UIAbility A 入口）和 ExtraIndex.ets（UIAbility B 入口）结构与 SPEC-001 相同，仅替换 NodeController 导入路径，故每个 SPEC 仅提供 NodeController 和 Component 两个差异文件。

### SPEC-002 参考代码

`pages/NodeController_Spec002.ets`：
```typescript
'use static'
import { BuilderNode, FrameNode, NodeController, UIContext, wrapBuilder } from '@kit.ArkUI';
import hilog from '@ohos.hilog';

const DOMAIN = 0x0000;
const TAG = 'Spec002';
let globalBuilderNode: BuilderNode | undefined = undefined;

export class NodeController002 extends NodeController {
  private rootNode: FrameNode | null = null;
  private uiContext: UIContext | null = null;

  makeNode(uiContext: UIContext): FrameNode | null {
    this.rootNode = new FrameNode(uiContext);
    this.uiContext = uiContext;
    hilog.info(DOMAIN, TAG, `makeNode, instanceId = ${uiContext.getId()}`);
    return this.rootNode;
  }

  addBuilderNode(): void {
    if (!globalBuilderNode && this.uiContext) {
      globalBuilderNode = new BuilderNode<undefined>(this.uiContext as UIContext);
      globalBuilderNode!.build(wrapBuilder(buildComponent002));
    }
    if (this.rootNode && globalBuilderNode) {
      this.rootNode!.appendChild(globalBuilderNode!.getFrameNode()!);
    }
  }

  removeBuilderNode(): void {
    if (this.rootNode && globalBuilderNode) {
      this.rootNode!.removeChild(globalBuilderNode!.getFrameNode()!);
    }
  }

  disposeNode(): void {
    if (globalBuilderNode) {
      globalBuilderNode!.dispose();
      globalBuilderNode = undefined;
    }
  }
}

import { buildComponent002 } from './Component_Spec002';
```

`pages/Component_Spec002.ets`：
```typescript
'use static'
import { Builder, Component, State, Watch, Text, Button, Column, ColumnOptions } from '@kit.ArkUI';
import hilog from '@ohos.hilog';

const DOMAIN = 0x0000;
const TAG = 'Spec002';

@Builder
export function buildComponent002() {
  Column() {
    Spec002Component()
  }
}

@Component
export struct Spec002Component {
  @State @Watch('onMessageChanged') message: string = 'hello';
  private watchCallCount: number = 0;

  onMessageChanged(propertyName: string): void {
    this.watchCallCount++;
    hilog.info(DOMAIN, TAG,
      `@Watch fired: count=${this.watchCallCount}, property=${propertyName}, value=${this.message}, instanceId=${this.getUIContext().getId()}`);
  }

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Text(`message: ${this.message}`)
        .fontSize(20)
      Button('change message')
        .onClick(() => {
          this.message += ' world';
          hilog.info(DOMAIN, TAG,
            `onClick: message changed to "${this.message}", instanceId=${this.getUIContext().getId()}`);
        })
    }
  }
}
```

**SPEC-002 操作步骤**：

| 步骤 | 操作 | 预期日志 |
|------|------|---------|
| 1 | AbilityA: 点击 add → 点击 "change message" | `@Watch fired: count=1, value=hello world, instanceId=<A>`；Text 显示 `message: hello world` |
| 2 | AbilityA: 点击 remove → 点击 start ExtraAbility | AbilityB 页面出现 |
| 3 | AbilityB: 点击 add (re-attach) | `makeNode, instanceId=<B>`；Text 显示 `message: hello world`（状态保留） |
| 4 | AbilityB: 点击 "change message" | `@Watch fired: count=2, value=hello world world, instanceId=<B>`；Text 更新 |
| **断言** | 对比步骤1和步骤4 | @Watch 回调在迁移后正常触发（count 递增），ID 变为 B，UI Text 同步更新 |

### SPEC-003 参考代码

`pages/NodeController_Spec003.ets`：
```typescript
'use static'
import { BuilderNode, FrameNode, NodeController, UIContext, wrapBuilder } from '@kit.ArkUI';
import hilog from '@ohos.hilog';

const DOMAIN = 0x0000;
const TAG = 'Spec003';
let globalBuilderNode: BuilderNode | undefined = undefined;

export class NodeController003 extends NodeController {
  private rootNode: FrameNode | null = null;
  private uiContext: UIContext | null = null;

  makeNode(uiContext: UIContext): FrameNode | null {
    this.rootNode = new FrameNode(uiContext);
    this.uiContext = uiContext;
    hilog.info(DOMAIN, TAG, `makeNode, instanceId = ${uiContext.getId()}`);
    return this.rootNode;
  }

  addBuilderNode(): void {
    if (!globalBuilderNode && this.uiContext) {
      globalBuilderNode = new BuilderNode<undefined>(this.uiContext as UIContext);
      globalBuilderNode!.build(wrapBuilder(buildComponent003));
    }
    if (this.rootNode && globalBuilderNode) {
      this.rootNode!.appendChild(globalBuilderNode!.getFrameNode()!);
    }
  }

  removeBuilderNode(): void {
    if (this.rootNode && globalBuilderNode) {
      this.rootNode!.removeChild(globalBuilderNode!.getFrameNode()!);
    }
  }

  disposeNode(): void {
    if (globalBuilderNode) {
      globalBuilderNode!.dispose();
      globalBuilderNode = undefined;
    }
  }
}

import { buildComponent003 } from './Component_Spec003';
```

`pages/Component_Spec003.ets`：
```typescript
'use static'
import { Builder, ComponentV2, Local, Monitor, IMonitor, Text, Button,
         Column, ColumnOptions } from '@kit.ArkUI';
import hilog from '@ohos.hilog';

const DOMAIN = 0x0000;
const TAG = 'Spec003';

@Builder
export function buildComponent003() {
  Column() {
    FreezableComponent()
  }
}

@ComponentV2
export struct FreezableComponent {
  @Local message: string = 'hello';
  private updateCount: number = 0;

  @Monitor(['message'])
  onMessageChanged(monitor: IMonitor): void {
    this.updateCount++;
    hilog.info(DOMAIN, TAG,
      `@Monitor fired: count=${this.updateCount}, value=${this.message}, instanceId=${this.getUIContext().getId()}`);
  }

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Text(`freeze-test: ${this.message}`)
        .fontSize(20)
      Button('change message')
        .onClick(() => {
          this.message += ' x';
          hilog.info(DOMAIN, TAG, `onClick: message="${this.message}"`);
        })
    }
  }
}
```

**SPEC-003 操作步骤**：

| 步骤 | 操作 | 预期日志 |
|------|------|---------|
| 1 | AbilityA: add → 点击 "change message" | @Monitor 触发；Text 更新为 `freeze-test: hello x` |
| 2 | AbilityA: remove → start ExtraAbility | |
| 3 | AbilityB: add (re-attach) | 组件挂载成功，Text 仍显示 `freeze-test: hello x` |
| 4 | AbilityB: 将组件设为不可见（触发冻结） | 组件进入冻结状态 |
| 5 | 冻结期间点击 "change message" | @Monitor 不触发，UI 不更新 |
| 6 | 将组件恢复可见（触发解冻） | 解冻后组件恢复正确渲染，状态更新生效 |
| **断言** | 对比步骤4-6 | 冻结时 @Monitor 不触发、UI 不更新；解冻后恢复正常——行为与迁移前一致 |

### SPEC-004 参考代码

`pages/NodeController_Spec004.ets`：
```typescript
'use static'
import { BuilderNode, FrameNode, NodeController, UIContext, wrapBuilder } from '@kit.ArkUI';
import hilog from '@ohos.hilog';

const DOMAIN = 0x0000;
const TAG = 'Spec004';
let globalBuilderNode: BuilderNode | undefined = undefined;

export class NodeController004 extends NodeController {
  private rootNode: FrameNode | null = null;
  private uiContext: UIContext | null = null;

  makeNode(uiContext: UIContext): FrameNode | null {
    this.rootNode = new FrameNode(uiContext);
    this.uiContext = uiContext;
    hilog.info(DOMAIN, TAG, `makeNode, instanceId = ${uiContext.getId()}`);
    return this.rootNode;
  }

  addBuilderNode(): void {
    if (!globalBuilderNode && this.uiContext) {
      globalBuilderNode = new BuilderNode<undefined>(this.uiContext as UIContext);
      globalBuilderNode!.build(wrapBuilder(buildComponent004));
    }
    if (this.rootNode && globalBuilderNode) {
      this.rootNode!.appendChild(globalBuilderNode!.getFrameNode()!);
    }
  }

  removeBuilderNode(): void {
    if (this.rootNode && globalBuilderNode) {
      this.rootNode!.removeChild(globalBuilderNode!.getFrameNode()!);
    }
  }

  disposeNode(): void {
    if (globalBuilderNode) {
      globalBuilderNode!.dispose();
      globalBuilderNode = undefined;
    }
  }
}

import { buildComponent004 } from './Component_Spec004';
```

`pages/Component_Spec004.ets`：
```typescript
'use static'
import { Builder, Component, Text, Column, ColumnOptions } from '@kit.ArkUI';
import hilog from '@ohos.hilog';

const DOMAIN = 0x0000;
const TAG = 'Spec004';

@Component
struct GrandChildComponent {
  aboutToAppear(): void {
    hilog.info(DOMAIN, TAG,
      `GrandChild aboutToAppear, instanceId = ${this.getUIContext().getId()}`);
  }

  build() {
    Text('GrandChild')
  }
}

@Component
struct ChildComponent {
  aboutToAppear(): void {
    hilog.info(DOMAIN, TAG,
      `Child aboutToAppear, instanceId = ${this.getUIContext().getId()}`);
  }

  build() {
    Column() {
      Text('Child')
      GrandChildComponent()
    }
  }
}

@Component
struct ParentComponent {
  aboutToAppear(): void {
    hilog.info(DOMAIN, TAG,
      `Parent aboutToAppear, instanceId = ${this.getUIContext().getId()}`);
  }

  build() {
    Column() {
      Text('Parent')
      ChildComponent()
    }
  }
}

@Builder
export function buildComponent004() {
  Column() {
    ParentComponent()
  }
}
```

**SPEC-004 操作步骤**：

| 步骤 | 操作 | 预期日志 |
|------|------|---------|
| 1 | AbilityA: add | `Parent aboutToAppear, instanceId = <A>`；`Child aboutToAppear, instanceId = <A>`；`GrandChild aboutToAppear, instanceId = <A>` |
| 2 | AbilityA: remove → start ExtraAbility | |
| 3 | AbilityB: add (re-attach) | `Parent aboutToAppear, instanceId = <B>`；`Child aboutToAppear, instanceId = <B>`；`GrandChild aboutToAppear, instanceId = <B>` |
| **断言** | 对比步骤1和步骤3 | 父、子、孙三层组件 ID 全部从 `<A>` 变为 `<B>` |

### SPEC-005 参考代码

SPEC-005 使用 SPEC-001 相同的组件代码（`NodeController001` + `Spec001Component`），区别在于操作步骤。

**场景 S01（首次挂载）**：

| 步骤 | 操作 | 预期日志 |
|------|------|---------|
| 1 | AbilityA: 点击 add（首次挂载，instanceId 相同） | aboutToAppear 正常触发，@Watch 正常触发，UI 正常渲染，无异常 |

**断言**：首次创建挂载到自身 Ability 不触发跨 Ability 迁移逻辑，行为正常。

**场景 S02（同 Ability 重复挂载）**：

| 步骤 | 操作 | 预期日志 |
|------|------|---------|
| 1 | AbilityA: add → remove → 再次 add（同一个 Ability） | 组件行为无变化，无副作用日志 |

**断言**：removeChild 再 appendChild 到同一 Ability，instanceId 相同，无额外更新。

### SPEC-006 参考代码

`pages/Component_Spec006.ets`：
```typescript
'use static'
import { Builder, Component, State, Text, Button, Column, ColumnOptions } from '@kit.ArkUI';
import hilog from '@ohos.hilog';

const DOMAIN = 0x0000;
const TAG = 'Spec006';

@Component
struct DisposableChild {
  aboutToAppear(): void {
    hilog.info(DOMAIN, TAG, `Child aboutToAppear`);
  }

  aboutToDisappear(): void {
    hilog.info(DOMAIN, TAG, `Child aboutToDisappear`);
  }

  build() {
    Text('I am child')
  }
}

@Component
struct ParentWithDisposableChild {
  @State showChild: boolean = true;

  aboutToAppear(): void {
    hilog.info(DOMAIN, TAG,
      `Parent aboutToAppear, instanceId = ${this.getUIContext().getId()}`);
  }

  build() {
    Column() {
      Text('Parent')
      if (this.showChild) {
        DisposableChild()
      }
      Button('dispose child')
        .onClick(() => {
          this.showChild = false;
          hilog.info(DOMAIN, TAG, 'child removed from tree');
        })
    }
  }
}

@Component
struct StaticComponent {
  aboutToAppear(): void {
    hilog.info(DOMAIN, TAG,
      `StaticComponent aboutToAppear, instanceId = ${this.getUIContext().getId()}`);
  }

  build() {
    Column() {
      Text('Static UI - no state')
    }
  }
}

@Builder
export function buildComponent006_S01() {
  Column() { ParentWithDisposableChild() }
}

@Builder
export function buildComponent006_S02() {
  Column() { StaticComponent() }
}
```

> NodeController 同 SPEC-001 模式，分别引用 `buildComponent006_S01` 和 `buildComponent006_S02`。

**SPEC-006 操作步骤**：

| 步骤 | 操作 | 预期日志 |
|------|------|---------|
| **S01（子组件 GC 后迁移）** | | |
| 1 | AbilityA: add → 点击 "dispose child" | `Child aboutToDisappear`；`child removed from tree` |
| 2 | AbilityA: remove → start ExtraAbility → AbilityB: add | `Parent aboutToAppear, instanceId = <B>`；无崩溃、无异常 |
| **断言** | | 子组件被回收后迁移父组件成功，父组件 UIContext 正确更新 |
| | | |
| **S02（纯静态组件迁移）** | | |
| 1 | AbilityA: add → remove → start ExtraAbility → AbilityB: add | `StaticComponent aboutToAppear, instanceId = <B>`；UI 正常渲染 |

### SPEC-007 参考代码

`pages/NodeController_Spec007.ets`：
```typescript
'use static'
import { BuilderNode, FrameNode, NodeController, UIContext, wrapBuilder } from '@kit.ArkUI';
import hilog from '@ohos.hilog';

const DOMAIN = 0x0000;
const TAG = 'Spec007';
let globalBuilderNode: BuilderNode | undefined = undefined;

export class NodeController007 extends NodeController {
  private rootNode: FrameNode | null = null;
  private uiContext: UIContext | null = null;

  makeNode(uiContext: UIContext): FrameNode | null {
    this.rootNode = new FrameNode(uiContext);
    this.uiContext = uiContext;
    hilog.info(DOMAIN, TAG, `makeNode, instanceId = ${uiContext.getId()}`);
    return this.rootNode;
  }

  addBuilderNode(): void {
    if (!globalBuilderNode && this.uiContext) {
      globalBuilderNode = new BuilderNode<undefined>(this.uiContext as UIContext);
      globalBuilderNode!.build(wrapBuilder(buildComponent007));
    }
    if (this.rootNode && globalBuilderNode) {
      this.rootNode!.appendChild(globalBuilderNode!.getFrameNode()!);
    }
  }

  removeBuilderNode(): void {
    if (this.rootNode && globalBuilderNode) {
      this.rootNode!.removeChild(globalBuilderNode!.getFrameNode()!);
    }
  }

  disposeNode(): void {
    if (globalBuilderNode) {
      globalBuilderNode!.dispose();
      globalBuilderNode = undefined;
    }
  }
}

import { buildComponent007 } from './Component_Spec007';
```

`pages/Component_Spec007.ets`：
```typescript
'use static'
import { Builder, ComponentV2, Local, Monitor, IMonitor, Param, Event,
         Provider, Consumer, Text, Button, Column, ColumnOptions } from '@kit.ArkUI';
import hilog from '@ohos.hilog';

const DOMAIN = 0x0000;
const TAG = 'Spec007';

@ComponentV2
struct V2BasicComponent {
  @Local message: string = 'hello';
  private monitorCount: number = 0;

  @Monitor(['message'])
  onMessageChanged(monitor: IMonitor): void {
    this.monitorCount++;
    hilog.info(DOMAIN, TAG,
      `@Monitor fired: count=${this.monitorCount}, value=${this.message}, instanceId=${this.getUIContext().getId()}`);
  }

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Text(`V2 message: ${this.message}`)
      Button('change message')
        .onClick(() => {
          this.message += ' world';
        })
    }
  }
}

@ComponentV2
struct V2ConsumerChild {
  @Consumer('sharedTheme') theme: string = '';

  aboutToAppear(): void {
    hilog.info(DOMAIN, TAG,
      `ConsumerChild aboutToAppear, theme=${this.theme}, instanceId=${this.getUIContext().getId()}`);
  }

  build() {
    Text(`Consumer theme: ${this.theme}`)
  }
}

@ComponentV2
struct V2ProviderParent {
  @Provider('sharedTheme') theme: string = 'dark';

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Text(`Provider theme: ${this.theme}`)
      V2ConsumerChild()
      Button('toggle theme')
        .onClick(() => {
          this.theme = this.theme === 'dark' ? 'light' : 'dark';
          hilog.info(DOMAIN, TAG, `Provider changed to: ${this.theme}`);
        })
    }
  }
}

@ComponentV2
struct V2ParamEventChild {
  @Param count: number = 0;
  @Event onCountChange: (val: number) => void = () => {};

  aboutToAppear(): void {
    hilog.info(DOMAIN, TAG,
      `ParamEventChild aboutToAppear, count=${this.count}, instanceId=${this.getUIContext().getId()}`);
  }

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Text(`Child count: ${this.count}`)
      Button('increment + emit event')
        .onClick(() => {
          this.onCountChange(this.count + 1);
          hilog.info(DOMAIN, TAG, `Event emitted: ${this.count + 1}`);
        })
    }
  }
}

@ComponentV2
struct V2ParamEventParent {
  @Local parentCount: number = 0;

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Text(`Parent count: ${this.parentCount}`)
      V2ParamEventChild({
        count: this.parentCount,
        onCountChange: (val: number) => {
          this.parentCount = val;
          hilog.info(DOMAIN, TAG,
            `Parent received event, parentCount=${this.parentCount}`);
        }
      })
    }
  }
}

@ComponentV2
struct V2RootComponent {
  @Local activeTab: number = 0;

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Text(`V2 Root, instanceId = ${this.getUIContext().getId()}`)

      Button('Tab: @Local+@Monitor')
        .onClick(() => { this.activeTab = 0; })
      Button('Tab: @Provider+@Consumer')
        .onClick(() => { this.activeTab = 1; })
      Button('Tab: @Param+@Event')
        .onClick(() => { this.activeTab = 2; })

      if (this.activeTab === 0) {
        V2BasicComponent()
      } else if (this.activeTab === 1) {
        V2ProviderParent()
      } else {
        V2ParamEventParent()
      }
    }
  }
}

@Builder
export function buildComponent007() {
  Column() {
    V2RootComponent()
  }
}
```

**SPEC-007 操作步骤**：

| 步骤 | 操作 | 预期日志 |
|------|------|---------|
| **S01/S02: @Local + @Monitor** | | |
| 1 | AbilityA: add → 切到 Tab0 → 点击 "change message" | @Monitor 触发（count=1），Text 更新 |
| 2 | 迁移到 AbilityB → add → 点击 "change message" | @Monitor 触发（count=2），ID 为 B，Text 更新 |
| **S03: @Provider + @Consumer** | | |
| 1 | AbilityA: add → 切到 Tab1 → 点击 "toggle theme" | Provider 变为 `light`，Consumer 显示 `Consumer theme: light` |
| 2 | 迁移到 AbilityB → add → 点击 "toggle theme" | Provider 变为 `dark`，Consumer 同步显示，ID 为 B |
| **S04: @Param + @Event** | | |
| 1 | AbilityA: add → 切到 Tab2 → 点击 "increment + emit event" | Parent count 变为 1，Child count 显示 1 |
| 2 | 迁移到 AbilityB → add → 点击 "increment + emit event" | Parent count 变为 2，@Event 回调正常触发，ID 为 B |

### SPEC-008 参考代码

`pages/NodeController_Spec008.ets`：
```typescript
'use static'
import { BuilderNode, FrameNode, NodeController, UIContext, wrapBuilder } from '@kit.ArkUI';
import hilog from '@ohos.hilog';

const DOMAIN = 0x0000;
const TAG = 'Spec008';
let globalBuilderNode: BuilderNode | undefined = undefined;

export class NodeController008 extends NodeController {
  private rootNode: FrameNode | null = null;
  private uiContext: UIContext | null = null;

  makeNode(uiContext: UIContext): FrameNode | null {
    this.rootNode = new FrameNode(uiContext);
    this.uiContext = uiContext;
    hilog.info(DOMAIN, TAG, `makeNode, instanceId = ${uiContext.getId()}`);
    return this.rootNode;
  }

  addBuilderNode(): void {
    if (!globalBuilderNode && this.uiContext) {
      globalBuilderNode = new BuilderNode<undefined>(this.uiContext as UIContext);
      globalBuilderNode!.build(wrapBuilder(buildComponent008));
    }
    if (this.rootNode && globalBuilderNode) {
      this.rootNode!.appendChild(globalBuilderNode!.getFrameNode()!);
    }
  }

  removeBuilderNode(): void {
    if (this.rootNode && globalBuilderNode) {
      this.rootNode!.removeChild(globalBuilderNode!.getFrameNode()!);
    }
  }

  disposeNode(): void {
    if (globalBuilderNode) {
      globalBuilderNode!.dispose();
      globalBuilderNode = undefined;
    }
  }
}

import { buildComponent008 } from './Component_Spec008';
```

`pages/Component_Spec008.ets`：
```typescript
'use static'
import { Builder, Reusable, ComponentV2, ReusableV2, Local, Monitor, IMonitor,
         State, Watch, Text, Button, Column, ColumnOptions, ReuseObject } from '@kit.ArkUI';
import hilog from '@ohos.hilog';

const DOMAIN = 0x0000;
const TAG = 'Spec008';

@Reusable
@Component
struct ReusableV1Component {
  @State message: string = 'hello';
  private recycleCount: number = 0;
  private reuseCount: number = 0;

  aboutToRecycle(): void {
    this.recycleCount++;
    hilog.info(DOMAIN, TAG,
      `V1 aboutToRecycle: recycleCount=${this.recycleCount}, message=${this.message}, instanceId=${this.getUIContext().getId()}`);
  }

  aboutToReuse(reuseObj: ReuseObject): void {
    this.reuseCount++;
    hilog.info(DOMAIN, TAG,
      `V1 aboutToReuse: reuseCount=${this.reuseCount}, instanceId=${this.getUIContext().getId()}`);
  }

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Text(`V1 reusable: ${this.message}`)
        .fontSize(20)
      Button('change message')
        .onClick(() => {
          this.message += ' x';
        })
    }
  }
}

@ReusableV2
@ComponentV2
struct ReusableV2Component {
  @Local message: string = 'hello';
  private recycleCount: number = 0;
  private reuseCount: number = 0;

  aboutToRecycle(): void {
    this.recycleCount++;
    hilog.info(DOMAIN, TAG,
      `V2 aboutToRecycle: recycleCount=${this.recycleCount}, message=${this.message}, instanceId=${this.getUIContext().getId()}`);
  }

  aboutToReuse(): void {
    this.reuseCount++;
    hilog.info(DOMAIN, TAG,
      `V2 aboutToReuse: reuseCount=${this.reuseCount}, instanceId=${this.getUIContext().getId()}`);
  }

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Text(`V2 reusable: ${this.message}`)
        .fontSize(20)
      Button('change message')
        .onClick(() => {
          this.message += ' y';
        })
    }
  }
}

@ComponentV2
struct ReusableRootComponent {
  @Local activeTab: number = 0;

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Text(`Reusable Root, instanceId = ${this.getUIContext().getId()}`)
      Button('Tab: @Reusable V1')
        .onClick(() => { this.activeTab = 0; })
      Button('Tab: @ReusableV2 V2')
        .onClick(() => { this.activeTab = 1; })

      if (this.activeTab === 0) {
        ReusableV1Component()
      } else {
        ReusableV2Component()
      }
    }
  }
}

@Builder
export function buildComponent008() {
  Column() {
    ReusableRootComponent()
  }
}
```

**SPEC-008 操作步骤**：

| 步骤 | 操作 | 预期日志 |
|------|------|---------|
| **V1 @Reusable 场景** | | |
| 1 | AbilityA: add → 切到 Tab0（V1 组件） | 组件正常渲染 |
| 2 | AbilityA: remove（触发回收） | `V1 aboutToRecycle: recycleCount=1, instanceId=<A>` |
| 3 | AbilityA: start ExtraAbility → AbilityB: add（re-attach） | 组件重新挂载 |
| 4 | AbilityB: remove（迁移后触发回收） | `V1 aboutToRecycle: recycleCount=2, instanceId=<B>` |
| 5 | AbilityB: 重新 add（触发复用） | `V1 aboutToReuse: reuseCount=1, instanceId=<B>` |
| **断言** | | 迁移后 aboutToRecycle/aboutToReuse 正常触发，instanceId 为 B 的 ID |
| | | |
| **V2 @ReusableV2 场景** | | |
| 1 | AbilityA: add → 切到 Tab1（V2 组件）→ remove → AbilityB: add | 组件重新挂载 |
| 2 | AbilityB: remove（迁移后触发回收） | `V2 aboutToRecycle: ..., instanceId=<B>` |
| 3 | AbilityB: 重新 add（触发复用） | `V2 aboutToReuse: ..., instanceId=<B>` |
| **断言** | | V2 组件迁移后回收/复用生命周期正常 |

## 术语表

| 术语 | 定义 |
|------|------|
| UIAbility | OpenHarmony 应用的 UI 能力单元，拥有独立的 Window 和 UIContext |
| UIContext | UIAbility 的 UI 上下文，提供资源、主题、分辨率等能力 |
| ID (instanceId) | UIAbility 实例的唯一标识，可通过 `UIContext.getId()` 获取 |
| BuilderNode | 节点构建器，用于创建和管理自定义组件节点 |
| FrameNode | 帧节点，组件树中的基本节点单元 |
| NodeController | 节点控制器，管理 FrameNode 的生命周期 |
| NodeContainer | 占位容器组件，绑定 NodeController 显示节点内容 |
| 组件冻结 | 组件的冻结功能，冻结后不可见且不响应状态更新，解冻后恢复 |
| @State | 状态变量装饰器（V1），状态变化驱动 UI 刷新 |
| @Watch | 状态监听装饰器（V1），监听状态变量变化并触发回调 |
| @ComponentV2 | V2 版自定义组件装饰器 |
| @Local | 本地状态变量装饰器（V2） |
| @Monitor | 状态变化监听装饰器（V2） |
| @Param | 组件参数装饰器（V2） |
| @Event | 事件回调装饰器（V2） |
| @Provider / @Consumer | 跨组件状态共享装饰器（V2） |
| @Reusable | 组件复用装饰器（V1） |
| @ReusableV2 | 组件复用装饰器（V2） |
| wrapBuilder | 包装函数，将 @Builder 函数转换为 WrappedBuilder |
