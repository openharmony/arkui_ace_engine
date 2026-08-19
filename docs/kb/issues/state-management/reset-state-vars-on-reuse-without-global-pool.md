# 未启用全局复用仍调用 resetStateVarsOnReuse Issue Context

> 文档版本：v1.0
> 更新时间：2026-08-10
> 来源：`docs/context_registry.json` 主题 `ResetStateVarsOnReuseWithoutGlobalPool`
> 关联功能域：07-03-03、04-19-01

## 问题概述

自定义组件复用流程中，`ViewPU.aboutToReuseInternal` 在重用节点时调用开发者可覆写的 `resetStateVarsOnReuse` 钩子来重置状态变量。修复前，调用条件只判断「该钩子是否被子类覆写」，未判断「组件是否真正启用了全局复用池（global reuse）」。当开发者覆写了 `resetStateVarsOnReuse` 但组件并未走全局复用路径（如仅本地 legacy recycle、或根本未启用复用）时，钩子仍被调用，导致状态变量被错误重置，组件复现内容错乱。

典型表现：
- 覆写 `resetStateVarsOnReuse` 后，组件在非全局复用场景下状态被意外清空/重置
- 复用回弹时 UI 显示成初始态而非上一次复用参数对应态
- 仅自定义组件复用（Custom Component Reuse）相关链路触发，非复用渲染不触发

## 关联模块

| kind | role | name | evidence | confidence |
|------|------|------|----------|------------|
| architecture | symptom_surface | `ViewPU` 复用回弹（`aboutToReuseInternal`） | 状态变量在非全局复用场景被重置 | verified |
| architecture | root_cause_owner | `aboutToReuseInternal` 内的钩子调用条件（`pu_view.ts`） | 旧条件仅判 `resetStateVarsOnReuse !== ViewPU.prototype.resetStateVarsOnReuse`，缺全局池判定 | verified |
| architecture | fix_location | `aboutToReuseInternal` 钩子调用条件（`pu_view.ts`） | commit 9a6a1ec7d46 diff：追加 `&& this.getReusePoolInternal()`（主干后续重构为 `__isGlobalPoolActive__Internal`） | verified |
| architecture | dependency | 全局复用池（`ReusePool` / `__getReusePoolInternal__Internal`） | `getOrCreateRecycleNode` 中 `globalPool = __isGlobalPoolActive__Internal ? __getReusePoolInternal__Internal(...) : undefined` | verified |

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| 钩子调用条件不完整 | 只校验「钩子是否覆写」，未校验「复用池是否启用」 | 开发者覆写 `resetStateVarsOnReuse` 但组件走 legacy recycle 或未启用全局复用 |
| 复用路径语义混淆 | 把「自定义组件复用 API 钩子」与「全局复用池机制」耦合，钩子触发不区分来源 | 本地 recycle manager 命中节点时也走了全局复用专属的状态重置逻辑 |

## 排查路径

### 快速判断

1. 确认组件是否覆写了 `resetStateVarsOnReuse`（即 `resetStateVarsOnReuse !== ViewPU.prototype.resetStateVarsOnReuse`）
2. 确认组件复用走哪条路径：全局复用池（`@Reusable` + global pool）、legacy recycle manager、或未启用复用
3. 在 `pu_view.ts` 的 `aboutToReuseInternal` 中确认钩子调用条件是否同时包含「钩子覆写」与「全局池启用」两个判断
4. 观察复用回弹后状态变量是否被异常重置成初始值

### 详细排查

#### 钩子调用条件不完整 排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 在 `pu_view.ts` 搜索 `aboutToReuseInternal` 定位方法 | 方法内有 `__resetStateVarsOnReuse__Internal(params)` 调用 | 确认方法未改名 |
| 2 | 查看该调用的条件表达式 | 修复后应为 `__resetStateVarsOnReuse__Internal !== prototype && __isGlobalPoolActive__Internal`（修复 commit 用 `getReusePoolInternal()`） | 若条件只有「钩子覆写」一项，为缺陷版本 |
| 3 | 确认 `__isGlobalPoolActive__Internal` / `getReusePoolInternal` 的求值 | 全局复用未启用时应为 falsy | 若始终为 truthy，需排查全局池启用判定逻辑 |

关键代码定位（按符号名，行号随重构漂移）：
- `aboutToReuseInternal` 方法：`frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_view.ts`
- 钩子调用条件：`this.__resetStateVarsOnReuse__Internal !== ViewPU.prototype.__resetStateVarsOnReuse__Internal && this.__isGlobalPoolActive__Internal`
- 全局池取用：`getOrCreateRecycleNode` 内 `globalPool = this.__isGlobalPoolActive__Internal ? this.__getReusePoolInternal__Internal(componentClass) : undefined`
- 复用生命周期串：`aboutToReuseInternal` → `__resetStateVarsOnReuse__Internal`（仅全局复用）→ `updateStateVars(params)` → `aboutToReuse(params)` → `LifeCycleEvent.ON_REUSE`

#### 复用路径语义混淆 排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 确认节点来源（`fromGlobalPool` 标志） | 全局池来的节点才应触发全局复用专属钩子 | legacy/local pool 命中节点也触发，说明条件过宽 |
| 2 | 检查 `resetStateVarsOnReuse` 设计语义 | 该钩子应仅服务于全局复用的状态重置 | 若被本地复用误用，需在条件层隔离 |

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 修复/缓解变更 | 关系证据 |
|----------|----------|---------------|---------------|----------|
| 钩子调用条件不完整 | 在 `resetStateVarsOnReuse` 调用条件追加全局复用池启用判定，只有全局复用生效时才调用 | `pu_view.ts` `aboutToReuseInternal` 内钩子调用条件 | 9a6a1ec7d46 (fixed) | commit diff：`this.resetStateVarsOnReuse !== ViewPU.prototype.resetStateVarsOnReuse` → 追加 `&& this.getReusePoolInternal()` |

修复前：仅判 `this.resetStateVarsOnReuse !== ViewPU.prototype.resetStateVarsOnReuse`。
修复后（commit 9a6a1ec7d46）：追加 `&& this.getReusePoolInternal()`。
主干演进：符号重命名为 `__resetStateVarsOnReuse__Internal` / `__isGlobalPoolActive__Internal`，语义一致（仅全局复用启用时调用）。

## 关联变更

| 变更编号 | 变更简述 | 根因类别 | 变更关系 | 证据 | 确信度 |
|----------|----------|----------|----------|------|--------|
| CHG-01 | `aboutToReuseInternal` 中 `resetStateVarsOnReuse` 调用条件追加 `getReusePoolInternal()` 判定 | 钩子调用条件不完整 | fixed | commit 9a6a1ec7d46 diff | verified |
| CHG-02 | 符号重构：`resetStateVarsOnReuse` → `__resetStateVarsOnReuse__Internal`，`getReusePoolInternal` → `__isGlobalPoolActive__Internal` | — | follow_up | 主干当前代码与 commit 9a6a1ec7d46 符号不同，语义一致 | inferred |

关联 issue：[#76803](https://gitcode.com/openharmony/arkui_ace_engine/issues/76803)（已关闭，master）

> 覆盖范围：当前仅覆盖「钩子调用条件不完整」单一根因类别，对应 issue #76803 单一案例。复用路径（global pool / legacy recycle / NodeAdapter）之间钩子边界后续补充。

## 预防措施

- 复用相关钩子（`resetStateVarsOnReuse` / `aboutToReuse` / `aboutToRecycle`）的调用条件必须同时校验「钩子是否覆写」与「对应复用机制是否启用」，不可只判其一
- 新增复用路径时，梳理该路径应触发的钩子集合，避免把全局复用专属逻辑误挂到 legacy/local recycle 路径
- 覆写 `resetStateVarsOnReuse` 的单测应覆盖「全局复用启用」与「未启用」两种场景，验证钩子触发边界
- 代码审查重点：复用钩子调用点是否对复用池类型/启用状态做了门控

## 相关主题

- `docs/kb/architecture/component-reuse-framework.md`：组件复用框架（`RecycleManager` / `RecycleDummyNode` / `ViewPU`）
- `docs/kb/frontend/state_management/custom-component.md`：自定义组件复用机制
- 功能域 `07-03-03`（自定义组件复用）、`04-19-01`（组件复用框架）