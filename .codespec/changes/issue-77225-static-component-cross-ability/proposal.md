# Proposal — 静态自定义组件支持跨 Ability 实例迁移

> **状态**: Baselined
> **复杂度**: 标准（单仓）
> **API 版本**: 26.0.0
> **FuncID**: 03-03-01 | **FeatID**: Feat-01
> **创建日期**: 2026-06-11

---

## 1. 原始需求

从 API 版本 26.0.0 开始，静态 ArkTS 自定义组件（`'use static'` + `@Component` / `@ComponentV2` 装饰）支持跨 UIAbility 迁移。开发者通过 `BuilderNode` + `NodeController` + `FrameNode` 机制，将自定义组件从一个 UIAbility 的组件树转移到另一个 UIAbility 的组件树后，组件的 `UIContext`、组件冻结功能、`@State`/`@Watch` 回调、`@Local`/`@Monitor` 回调等均能正确更新到新 UIAbility 实例，组件在新实例中可正常工作。

### 核心迁移流程

1. 在 UIAbility A 中通过 `BuilderNode` 创建自定义组件并挂载到 `NodeContainer`
2. 将 `BuilderNode` 从 UIAbility A 的组件树移除（`removeChild`）
3. 拉起 UIAbility B（`startAbility`）
4. 将同一个 `BuilderNode` 重新挂载到 UIAbility B 的 `NodeContainer`（`appendChild`）
5. 迁移完成后，自定义组件在新 UIAbility B 中正常工作

---

## 2. 澄清记录

### 澄清轮次

| 轮次 | 问题 | 回答 |
|------|------|------|
| Q1 | 复杂度级别？是否涉及 ace_engine 之外的仓库？ | 标准（单仓），仅 ace_engine 仓改动 |
| Q2 | 用户故事划分是否准确？（原 US-1~US-5） | 需微调：增加 US-6（冻结功能独立 Story） |
| Q3 | 仅静态组件还是包含动态组件？ | 仅静态组件（`'use static'`） |
| Q4 | 迁移范围是否仅限单进程？ | 仅单进程内 UIAbility 切换 |
| Q5 | 获取 UIContext ID 的 API 名称？ | `getUIContext().getId()`（非 `getInstanceId()`） |

### 知识源检索日志

- **AGENTS.md**: 已读取，记录关键约束（不修改公共 API、优先 components_ng 等）
- **Profile 检查**: `.claude/ohos-sdd/profiles/` 目录不存在，无命中 Profile
- **KB 检索**: 待 Stage 2 前补充（需检索 `docs/kb_search.py` 关于 static component、UIContext、BuilderNode 相关知识库条目）

---

## 3. 需求基线

### 3.1 范围定义

**一句话概述**: 静态自定义组件（`'use static'` + `@Component`/`@ComponentV2`）在同一进程内跨 UIAbility 实例迁移后，UIContext 及所有状态管理机制正确更新到新 UIAbility。

**范围含**:

| 维度 | 内容 |
|------|------|
| UIContext 更新 | 迁移后 `getUIContext().getId()` 返回新 Ability 的 ID |
| 状态管理 V1 | `@State` UI 刷新、`@Watch` 回调、`@Link`/`@Prop`/`@Provide`/`@Consume` 状态同步 |
| 状态管理 V2 | `@Local` UI 刷新、`@Monitor` 回调、`@Provider`/`@Consumer` 状态共享、`@Param` 传值、`@Event` 回调 |
| 子组件递归传播 | 父组件迁移时，子组件和孙组件的 UIContext 均更新 |
| 冻结功能 | 迁移后组件的冻结功能在新 UIAbility 中正常生效（冻结时不可见/不响应，解冻后恢复） |
| 组件复用 | `@Reusable`/`@ReusableV2` 迁移后 `aboutToRecycle`/`aboutToReuse` 回调正常触发 |
| 幂等保护 | 源 ID === 目标 ID 时，不触发迁移逻辑，无副作用 |
| 异常安全 | 子组件被 GC 回收后迁移父组件不崩溃 |

**不含**:

| 维度 | 说明 |
|------|------|
| 动态组件迁移 | 仅支持 `'use static'` 声明的静态组件 |
| 跨进程迁移 | 不支持 IPC/跨进程，仅单进程内 UIAbility 切换 |
| 焦点/动画状态迁移 | 不在范围内 |
| 组件树序列化/反序列化 | 组件树复用现有机制，不涉及序列化 |
| 新增/修改 Public API | 所有接口均为平台已有接口，不涉及接口签名变更或新增 |
| @Watch checkThread 校验迁移 | 当前版本不涉及 |

### 3.2 涉及子系统

| 子系统 | 仓库 | 说明 |
|--------|------|------|
| 静态组件框架 | ace_engine | `@Component`/`@ComponentV2` 组件生命周期与 UIContext 绑定 |
| 状态管理 V1 | ace_engine | `@State`/`@Watch`/`@Link`/`@Prop` 等状态变量管理 |
| 状态管理 V2 | ace_engine | `@Local`/`@Monitor`/`@Provider`/`@Consumer`/`@Param`/`@Event` |
| BuilderNode/FrameNode | ace_engine | 节点构建器与帧节点的跨 Ability 挂载/卸载 |
| 组件冻结 | ace_engine | 冻结功能的启用/禁用逻辑 |
| 组件复用 | ace_engine | `@Reusable`/`@ReusableV2` 回收/复用生命周期 |

### 3.3 复杂度判定

**标准（单仓特性）**：变更集中在 `ace_engine` 单仓，涉及多个子系统但均在同一仓内，不涉及新增/修改 Public API，不需要跨 SIG 协调。

### 3.4 前置知识：迁移相关 Public API（非本次新增）

以下接口均为平台已有接口，本次需求不涉及新增或修改：

| 接口 | 说明 |
|------|------|
| `BuilderNode(uiContext)` | 创建节点构建器，绑定到指定 UIAbility 的 UIContext |
| `BuilderNode.build(wrappedBuilder)` | 使用 @Builder 函数构建自定义组件内容 |
| `BuilderNode.getFrameNode()` | 获取 BuilderNode 对应的 FrameNode |
| `BuilderNode.dispose()` | 销毁 BuilderNode 及其子节点 |
| `FrameNode.appendChild(node)` | 将子节点挂载到当前节点 |
| `FrameNode.removeChild(node)` | 将子节点从当前节点移除 |
| `NodeController.makeNode(uiContext)` | 创建根 FrameNode，跨 Ability 时 uiContext 为新 Ability 的 |
| `NodeContainer(controller)` | 占位容器组件 |
| `getUIContext()` | 获取当前组件关联的 UIContext |
| `UIContext.getId()` | 获取 UIContext 所属 UIAbility 的实例 ID |
| `UIContext.getHostContext()` | 获取宿主上下文 |
| `wrapBuilder(builder)` | 包装 @Builder 函数供 BuilderNode 使用 |
| `startAbility(want)` | 拉起新的 UIAbility |

---

## 4. 用户故事与验收标准

### US-1: @Component 单组件迁移后 UIContext 和状态管理正常

> 作为开发者，我迁移 `@Component` 单组件到新 UIAbility 后，UIContext 和 @State/@Watch 正常工作。

| AC | 验收标准 (WHEN/THEN) | 优先级 |
|----|----------------------|--------|
| AC-1.1 | **WHEN** 将自定义组件从 UIAbility A 迁移到 UIAbility B 后，**THEN** 调用 `getUIContext().getId()` 返回 UIAbility B 的 ID | P0 |
| AC-1.2 | **WHEN** 将自定义组件迁移到 UIAbility B 后修改 `@State` 变量，**THEN** UI 正常刷新（Text 组件内容更新） | P0 |
| AC-1.3 | **WHEN** 将自定义组件迁移到 UIAbility B 后修改 `@State` 变量，**THEN** `@Watch` 回调正常执行 | P0 |

### US-2: 多层子组件迁移后 UIContext 正确传播

> 作为开发者，我迁移含多层子组件的组件树后，所有子组件 UIContext 正确传播。

| AC | 验收标准 (WHEN/THEN) | 优先级 |
|----|----------------------|--------|
| AC-2.1 | **WHEN** 将含父-子-孙三层组件树的父组件迁移到 UIAbility B 后，**THEN** 父、子、孙组件的 `getUIContext().getId()` 均返回 UIAbility B 的 ID | P0 |

### US-3: 同 UIAbility 内操作无副作用

> 作为开发者，我在同一 UIAbility 内操作组件时，行为无副作用。

| AC | 验收标准 (WHEN/THEN) | 优先级 |
|----|----------------------|--------|
| AC-3.1 | **WHEN** 组件首次在 UIAbility A 中创建并挂载时（ID 未变化），**THEN** `@Watch` 回调正常触发、UI 正常渲染，无异常行为 | P0 |
| AC-3.2 | **WHEN** 组件已在 UIAbility B 中，再次调用 `makeNode` 传入相同 UIAbility 的 UIContext（ID 相同），**THEN** 组件行为无变化、无副作用 | P0 |
| AC-3.3 | **WHEN** 将没有子组件的自定义组件迁移到 UIAbility B 后，**THEN** `getUIContext().getId()` 返回新 ID，UI 正常渲染 | P0 |

### US-4: @ComponentV2 迁移后状态管理 V2 正常

> 作为开发者，我迁移 `@ComponentV2` 组件后，状态管理 V2 全部机制正常。

| AC | 验收标准 (WHEN/THEN) | 优先级 |
|----|----------------------|--------|
| AC-4.1 | **WHEN** 将 `@ComponentV2` 装饰的自定义组件迁移到 UIAbility B 后，**THEN** `getUIContext().getId()` 返回 UIAbility B 的 ID | P0 |
| AC-4.2 | **WHEN** 将 `@ComponentV2` 组件迁移到 UIAbility B 后修改 `@Local` 变量，**THEN** UI 正常刷新 | P0 |
| AC-4.3 | **WHEN** 将 `@ComponentV2` 组件迁移到 UIAbility B 后修改 `@Local` 变量，**THEN** `@Monitor` 回调正常执行 | P0 |
| AC-4.4 | **WHEN** 将使用 `@Provider`/`@Consumer` 跨组件状态共享的 `@ComponentV2` 组件迁移到 UIAbility B 后修改 Provider 状态，**THEN** Consumer 正确同步 | P0 |
| AC-4.5 | **WHEN** 将使用 `@Param`/`@Event` 的 `@ComponentV2` 子组件迁移到 UIAbility B 后，**THEN** 父组件通过 `@Param` 传值正常生效，子组件通过 `@Event` 回调正常触发 | P1 |

### US-5: @Reusable/@ReusableV2 迁移后生命周期正常

> 作为开发者，我迁移 `@Reusable`/`@ReusableV2` 组件后，回收/复用生命周期正常。

| AC | 验收标准 (WHEN/THEN) | 优先级 |
|----|----------------------|--------|
| AC-5.1 | **WHEN** 将使用 `@Reusable` 装饰的自定义组件迁移到 UIAbility B 后触发组件回收，**THEN** `aboutToRecycle` 回调正常触发 | P0 |
| AC-5.2 | **WHEN** 将使用 `@Reusable` 装饰的自定义组件迁移到 UIAbility B 后触发组件复用，**THEN** `aboutToReuse` 回调正常触发且 `getUIContext().getId()` 返回 UIAbility B 的 ID | P0 |
| AC-5.3 | **WHEN** 将使用 `@ReusableV2` 装饰的 `@ComponentV2` 组件迁移到 UIAbility B 后触发回收和复用，**THEN** `aboutToRecycle` 和 `aboutToReuse` 回调正常触发 | P1 |

### US-6: 迁移后冻结功能正常

> 作为开发者，迁移后自定义组件冻结功能能够正常生效。

| AC | 验收标准 (WHEN/THEN) | 优先级 |
|----|----------------------|--------|
| AC-6.1 | **WHEN** 将使用了冻结功能的自定义组件迁移到 UIAbility B 后，**THEN** 组件的冻结功能在新 UIAbility 中正常生效 | P0 |
| AC-6.2 | **WHEN** 将含子组件使用冻结功能的父组件迁移到 UIAbility B 后，**THEN** 子组件的冻结功能在新 UIAbility 中正常生效 | P1 |

### 验收标准汇总

| 优先级 | 数量 | AC 编号 |
|--------|------|---------|
| P0 | 13 | AC-1.1~1.3, AC-2.1, AC-3.1~3.3, AC-4.1~4.4, AC-5.1~5.2, AC-6.1 |
| P1 | 4 | AC-4.5, AC-5.3, AC-6.2 |
| **合计** | **17** | |

---

## 5. 功能规则 (FR)

### FR-1: 迁移触发规则

| 规则 ID | 描述 |
|--------|------|
| FR-1.1 | 自定义组件通过 `FrameNode.removeChild` 从 UIAbility A 移除后，再通过 `FrameNode.appendChild` 挂载到 UIAbility B 时，触发跨 Ability 迁移逻辑 |
| FR-1.2 | 组件首次创建并 `appendChild` 挂载到自身 UIAbility 时，不触发迁移更新（源 ID === 目标 ID） |
| FR-1.3 | 跨 Ability 迁移时（源 ID ≠ 目标 ID），触发完整迁移逻辑 |

### FR-2: 状态更新规则

| 规则 ID | 描述 |
|--------|------|
| FR-2.1 | 迁移后，`getUIContext()` 返回的 UIContext 为新 UIAbility 的 UIContext，`getId()` 返回新 UIAbility 的 ID |
| FR-2.2 | 迁移后，`@State` 变量修改仍能驱动 UI 刷新、`@Watch` 回调仍能正常触发 |
| FR-2.3 | 迁移时，子组件递归传播：父组件迁移会传播到所有子组件和孙组件，均更新 UIContext |
| FR-2.4 | 迁移后，组件的冻结功能在新 UIAbility 中正常生效：冻结的组件不可见且不响应状态更新，解冻后恢复可见并正确渲染 |

### FR-3: 幂等保护规则

| 规则 ID | 描述 |
|--------|------|
| FR-3.1 | 幂等保护：当组件当前 UIContext 的 ID 与新 ID 相同时，跳过 UIContext、子组件传播更新 |

### FR-4: 范围规则

| 规则 ID | 描述 |
|--------|------|
| FR-4.1 | `@ComponentV2` 装饰的自定义组件同样支持跨 Ability 迁移 |

### FR-5: 状态管理 V2 规则

| 规则 ID | 描述 |
|--------|------|
| FR-5.1 | `@ComponentV2` 组件迁移后，`@Local` 变量修改仍能驱动 UI 刷新、`@Monitor` 回调仍能正常触发 |
| FR-5.2 | `@ComponentV2` 组件迁移后，`@Provider`/`@Consumer` 跨组件状态共享机制正常工作 |
| FR-5.3 | `@ComponentV2` 组件迁移后，`@Param` 传值和 `@Event` 回调正常工作 |

### FR-6: 组件复用规则

| 规则 ID | 描述 |
|--------|------|
| FR-6.1 | `@Reusable`/`@ReusableV2` 组件迁移后，`aboutToRecycle` 回调正常触发 |
| FR-6.2 | `@Reusable`/`@ReusableV2` 组件迁移后，`aboutToReuse` 回调正常触发，且 `getUIContext().getId()` 返回新 UIAbility 的 ID |

---

## 6. 异常/豁免规则 (ER)

| 规则 ID | 场景 | 处理方式 |
|--------|------|---------|
| ER-1 | 子组件已被 GC 回收，迁移时弱引用返回 undefined | 安全跳过该子组件，继续处理下一个子组件，不影响父组件迁移 |
| ER-2 | 自定义组件不含任何状态变量（纯静态 UI 组件） | 迁移后 UI 正常渲染，不影响其他逻辑 |

---

## 7. 术语表

| 术语 | 定义 |
|------|------|
| UIAbility | OpenHarmony 应用的 UI 能力单元，拥有独立的 Window 和 UIContext |
| UIContext | UIAbility 的 UI 上下文，提供资源、主题、分辨率等能力 |
| ID (instanceId) | UIAbility 实例的唯一标识，可通过 `UIContext.getId()` 获取 |
| BuilderNode | 节点构建器，用于创建和管理自定义组件节点 |
| FrameNode | 帧节点，组件树中的基本节点单元 |
| NodeController | 节点控制器，管理 FrameNode 的生命周期 |
| NodeContainer | 占位容器组件，绑定 NodeController 显示节点内容 |
| 组件冻结 | 组件的冻结功能，冻结后组件不可见且不响应状态更新，解冻后恢复可见并正确渲染 |
| @State | 状态变量装饰器（V1），状态变化驱动 UI 刷新 |
| @Watch | 状态监听装饰器（V1），监听状态变量变化并触发回调 |
| @ComponentV2 | V2 版自定义组件装饰器，配合状态管理 V2 使用 |
| @Local | 本地状态变量装饰器（V2），状态变化驱动 UI 刷新 |
| @Monitor | 状态变化监听装饰器（V2），监听状态变量变化并触发回调 |
| @Param | 组件参数装饰器（V2），父组件向子组件传值 |
| @Event | 事件回调装饰器（V2），子组件向父组件发送事件 |
| @Provider / @Consumer | 跨组件状态共享装饰器（V2），Provider 提供状态，Consumer 消费状态 |
| @Reusable | 组件复用装饰器（V1），标记组件可被回收复用，触发 aboutToRecycle/aboutToReuse 生命周期 |
| @ReusableV2 | 组件复用装饰器（V2），标记 @ComponentV2 组件可被回收复用 |
| wrapBuilder | 包装函数，将 @Builder 函数转换为 BuilderNode 可用的 WrappedBuilder |

---

## 基线结论

> **状态**: Baselined — 用户已批准（2026-06-11）

以上需求基线涵盖 6 个用户故事、17 个验收标准（13 P0 + 4 P1）、14 条功能规则、2 条异常规则。
范围明确限于静态组件、单进程内、ace_engine 单仓，不涉及新增/修改 Public API。

**Stage 1 进入条件检查**:

- [x] 范围和排除项已明确
- [x] 涉及子系统/仓已识别（ace_engine 单仓）
- [x] 复杂度级别已判断（标准）
- [x] 每个 P0/P1 AC 以 WHEN/THEN 格式写出且可测试
