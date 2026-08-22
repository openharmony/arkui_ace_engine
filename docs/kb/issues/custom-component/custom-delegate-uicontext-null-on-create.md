# CustomDelegate 创建时 UIContext 为空 Issue Context

> 文档版本：v1.0
> 更新时间：2026-08-10
> 来源：`docs/context_registry.json` 主题 `CustomDelegateUIContextNullOnCreate`
> 关联功能域：04-12-01、07-03-01

## 问题概述

静态前端（ArkTS Frontend / arkoala）自定义组件代理 `CustomDelegate` 在构造时直接赋值 `this.uiContext = uiContext`，未对入参做 null 兜底。多个创建入口（`createInstance`、`Reusable`、`ContentSlot` 等链路）经 `data?.uiContext` 取上下文，当 `data` 未携带 `uiContext`（data 为空或字段缺失）时，传入 `undefined`，`CustomDelegate.uiContext` 保持 `undefined`。后续 `getUIContext()`（`return this.uiContext!`）返回 `undefined`，所有依赖 UIContext 的操作（资源访问、动画、节点创建等）触发空指针异常。

典型表现：
- 静态前端创建自定义组件时崩溃，错误指向访问 `undefined` UIContext 相关 API
- `Reusable` / `ContentSlot` / `BuilderNode` 等代码型创建链路在未显式传 UIContext 时必现
- 崩溃点不在 `CustomDelegate` 构造本身，而在其后续 `getUIContext()` 的消费方

## 关联模块

| kind | role | name | evidence | confidence |
|------|------|------|----------|------------|
| architecture | symptom_surface | `CustomDelegate` 创建链路（`createInstance` / `ContentSlot` / `Reusable`） | `const uiContext = data?.uiContext;` 在 `data` 无该字段时为 undefined | verified |
| architecture | root_cause_owner | `CustomDelegate` 构造函数（`customComponent.ets`） | 旧代码 `this.uiContext = uiContext;` 无 null 兜底 | verified |
| capability | fix_location | `CustomDelegate` 构造函数 + `UIContextUtil`（`customComponent.ets` / `UIContextUtil.ets`） | commit 72066c94b12 diff：改为 `uiContext ?? UIContextUtil.getOrCreateCurrentUIContext()` | verified |
| capability | dependency | `UIContextUtil.getOrCreateCurrentUIContext()` | `base/UIContextUtil.ets` 提供当前线程/UI 实例的 UIContext 获取/创建 | verified |

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| 构造入参无 null 兜底 | `CustomDelegate` 构造直接赋值，不校验 uiContext 是否为 nullish | 调用方经 `data?.uiContext` 取值，`data` 为空或无 `uiContext` 字段时传入 undefined |
| 非空断言掩盖运行时空值 | `getUIContext()` 用 `return this.uiContext!` 非空断言，TS 编译期放行、运行期 uiContext 实际为 undefined | 消费方信任 `getUIContext()` 返回非空，直接调用其方法导致空指针 |
| 创建入口未统一注入 UIContext | 多条创建链路（`createInstance`、`ContentSlot`、`Reusable`）各自从 `data?.uiContext` 取值，未保证字段一定存在 | 上层调用未填充 `data.uiContext`，或使用默认 `data` 时字段缺失 |

## 排查路径

### 快速判断

1. **首要信号**：静态前端（arkoala）创建自定义组件时崩溃，栈帧指向 `CustomDelegate` 或其 `getUIContext()` 的消费方
2. 确认创建入口是否显式传入 UIContext：检查 `createInstance` / `ContentSlot` / `Reusable` 调用处的 `data.uiContext`
3. 在 `customComponent.ets` 的 `CustomDelegate` 构造函数确认是否有 `?? UIContextUtil.getOrCreateCurrentUIContext()` 兜底
4. 确认崩溃是否在 `getUIContext()` 返回后调用其方法时发生（非空断言 `!` 放行后的运行时空值）

### 详细排查

#### 入参 null 兜底缺失 排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 在 `customComponent.ets` 搜索 `class CustomDelegate` 定位构造函数 | 构造签名为 `(uiContext: UIContext \| undefined, instance, styles)` | 确认类未改名 |
| 2 | 查看 `this.uiContext = uiContext` 赋值 | 修复后应为 `this.uiContext = uiContext ?? UIContextUtil.getOrCreateCurrentUIContext();` | 若直接赋值无兜底，为缺陷版本 |
| 3 | 确认 `UIContextUtil` import 是否存在 | `import { UIContextUtil } from '../base/UIContextUtil';` | 缺失 import 则兜底调用失败 |

关键代码定位（按符号名，行号随重构漂移）：
- `CustomDelegate` 构造函数：`frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/component/customComponent.ets`
- 赋值点（修复后）：`this.uiContext = uiContext ?? UIContextUtil.getOrCreateCurrentUIContext();`
- 取值入口：`getUIContext()` 返回 `this.uiContext!`（非空断言，修复前在 uiContext 为 undefined 时放行运行时空值）
- 创建链路入口：`createInstance` / `ContentSlot` / `Reusable` 中 `const uiContext = data?.uiContext;` → `new CustomDelegate(uiContext, ...)`
- 兜底实现：`UIContextUtil.getOrCreateCurrentUIContext()`（`frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/base/UIContextUtil.ets`）

#### 创建入口未注入 UIContext 排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 搜索 `data?.uiContext` 出现位置 | 每处都应保证 `data` 非空且含 `uiContext`，或下游有兜底 | 找到无兜底直接传入 `CustomDelegate` 的链路 |
| 2 | 检查上层调用是否填充 `data.uiContext` | 显式创建场景应注入 UIContext | 上层未注入则依赖 `CustomDelegate` 兜底 |

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 修复/缓解变更 | 关系证据 |
|----------|----------|---------------|---------------|----------|
| 构造入参无 null 兜底 | `CustomDelegate` 构造函数对 uiContext 做 nullish 兜底，缺失时取当前 UI 实例的 UIContext | `customComponent.ets` `CustomDelegate` 构造：`this.uiContext = uiContext ?? UIContextUtil.getOrCreateCurrentUIContext();` + 新增 `UIContextUtil` import | 72066c94b12 (fixed) | commit diff：`this.uiContext = uiContext;` → 追加 `?? UIContextUtil.getOrCreateCurrentUIContext()` |

修复在 `CustomDelegate`（消费侧）统一兜底，而非在每个创建入口强制注入 UIContext。这样无论 `data?.uiContext` 是否为空，`getUIContext()` 都能返回有效 UIContext，消除下游空指针。

## 关联变更

| 变更编号 | 变更简述 | 根因类别 | 变更关系 | 证据 | 确信度 |
|----------|----------|----------|----------|------|--------|
| CHG-01 | `CustomDelegate` 构造对 uiContext 加 `?? UIContextUtil.getOrCreateCurrentUIContext()` 兜底 + 新增 import | 构造入参无 null 兜底 | fixed | commit 72066c94b12 diff | verified |

关联 issue：[#77922](https://gitcode.com/openharmony/arkui_ace_engine/issues/77922)（已关闭，master）

> 覆盖范围：当前仅覆盖「CustomDelegate 构造入参无 null 兜底」单一根因类别，对应 issue #77922 单一案例。其他静态前端 UIContext 注入链路（`BuilderNode`、`NodeAdapter` 等）的空值边界后续补充。

## 预防措施

- 持有 UIContext 的字段在构造时必须对入参做 nullish 兜底（`?? getOrCreateCurrentUIContext()`），不可直接赋值
- 对返回 UIContext 的 getter 慎用非空断言 `!`：要么保证赋值链路必非空，要么返回 `UIContext | undefined` 让消费方显式处理
- 新增自定义组件创建入口时，梳理 `data.uiContext` 的来源，缺失时依赖 `CustomDelegate` 兜底或上层强制注入
- 代码审查重点：静态前端（arkoala）中所有 `data?.uiContext` → 传入构造/工厂的链路，确认下游对 undefined 有兜底

## 相关主题

- [docs/kb/issues/lifecycle/uicontext-instance-id-leak.md](../lifecycle/uicontext-instance-id-leak.md)：UIContext 实例 ID 泄漏（同属 UIContext 域）
- [docs/kb/capabilities/ui-context.md](../../capabilities/ui-context.md)：UIContext 代码型 KB
- 功能域 `04-12-01`（UIContext 接口）、`07-03-01`（自定义组件生命周期）