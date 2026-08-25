# @Monitor 传 undefined 误判为 Options 模式 Issue Context

> 文档版本：v1.2
> 更新时间：2026-08-10
> 来源：`docs/context_registry.json` 主题 `MonitorUndefinedOptionsGuard`
> 关联功能域：07-02-04

## 问题概述

状态管理 V2 的 `@Monitor` 装饰器在工厂函数解析首参时，仅用 `typeof === 'string'` 区分「字符串路径」与「选项对象」两种调用形式。当首参为 `undefined`（无参装饰器 `@Monitor()`、转译器展开、显式 `@Monitor(undefined)`）时，代码无条件落入 options 对象分支，执行 `(undefined as MonitorDecoratorOptions).enableWildcard`。装饰器工厂在**类定义期**（模块加载/类装饰阶段）即被调用，`undefined` 上读取属性直接抛出 `TypeError: Cannot read properties of undefined (reading 'enableWildcard')`，该异常在工厂内未捕获，向上传播成为 **JSCrash**。

注意：`??` 兜底无法挽救——属性**访问**动作本身先于 `??` 求值抛出，工厂在返回装饰器函数之前就崩溃，根本到不了后续的 `Symbol` 注册逻辑。

典型表现：
- 类定义/模块加载阶段 JSCrash，错误信息为 `Cannot read properties of undefined (reading 'enableWildcard')`
- 使用 `@Monitor()` 无参、`@Monitor(undefined)` 或被转译器展开为传 `undefined` 的写法时必现
- 崩溃发生在装饰器工厂调用期（类装饰），而非组件渲染或回调触发期

## 关联模块

| kind | role | name | evidence | confidence |
|------|------|------|----------|------------|
| architecture | symptom_surface | V2 装饰器（`@Monitor`） | 类定义期 JSCrash：`Cannot read properties of undefined (reading 'enableWildcard')` | verified |
| architecture | root_cause_owner | `Monitor` 工厂函数（`v2_decorators.ts`） | 参数分支仅判 `typeof === 'string'`，非 string 一律进 options 分支 | verified |
| architecture | fix_location | `Monitor` 工厂函数 options 分支（`v2_decorators.ts`） | commit 3e4088eabce diff：加 `typeof === 'object'` 真值守卫 | verified |

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| 参数类型分支不完整 | 装饰器工厂仅用 `typeof === 'string'` 做二分，非 string 一律落入 options 分支 | `@Monitor(undefined)`、转译器把无参装饰器展开后传入 `undefined` |
| 缺少对象真值守卫 | 进入 options 分支前未校验参数为 truthy 且为 object | `null`、`undefined`、原始值（number/boolean）被强转为 options 模式 |
| 类型断言掩盖运行时类型 | `(optionsOrFirstPath as MonitorDecoratorOptions).enableWildcard` 仅编译期断言，TS 擦除类型后访问 `undefined` 属性 | 运行时 `undefined.enableWildcard` 直接执行 |

## 排查路径

### 快速判断

1. **首要信号**：类定义/模块加载阶段 JSCrash，错误为 `Cannot read properties of undefined (reading 'enableWildcard')` —— 命中即可定性为本问题
2. 确认 `@Monitor` 调用形式：是否有无参 / 传 `undefined` / 传 `null` 的写法（含代码生成器、转译器展开结果）
3. 确认崩溃发生在装饰器工厂调用期（类装饰阶段），而非组件渲染或回调触发期
4. 在 `v2_decorators.ts` 的 `Monitor` 工厂函数中确认 options 分支是否有 `typeof === 'object'` 真值守卫

### 详细排查

#### 误入 options 模式 排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 在 `v2_decorators.ts` 搜索 `function Monitor(` 定位工厂函数 | 签名为 `(optionsOrFirstPath: MonitorDecoratorOptions \| string, path?, ...pathN)` | 确认签名未变 |
| 2 | 查看首个 `if (typeof optionsOrFirstPath === 'string')` 之后的 `else` 分支 | 修复后应嵌套 `if (optionsOrFirstPath && typeof optionsOrFirstPath === 'object')` 守卫 | 若 `else` 内直接置 `monitorWithOptionsMode = true`，为缺陷版本 |
| 3 | 确认 `enableWildcard` 读取是否在守卫内 | 仅守卫内访问 `.enableWildcard` | 守卫外读取则 `undefined`/`null` 仍触发属性访问 |

关键代码定位（按符号名，行号随重构漂移）：
- `Monitor` 工厂函数：`frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_decorators.ts`
- 类型分支点：`if (typeof optionsOrFirstPath === 'string')` 及其 `else`
- 修复守卫：`if (optionsOrFirstPath && typeof optionsOrFirstPath === 'object')`
- 崩溃点（缺陷版本）：守卫外的 `(optionsOrFirstPath as MonitorDecoratorOptions).enableWildcard` 求值，`undefined`/`null` 在此抛 TypeError
- Symbol key 派生（崩溃后不会到达，仅作路由参考）：`MonitorV2.MONITOR_WITH_OPTIONS_PREFIX + className`（options 模式）对比 `MonitorV2.MONITOR_ORIG_PREFIX + className`（原始模式）

#### 通配符行为偏离 排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 确认 `enableWildcard` 默认值 | options 模式默认 `true`，原始模式 `false` | `undefined` 误判后被当作 `true`，路径通配语义错乱 |
| 2 | 检查 `MonitorFunctionInfo` 元组第二元素 | options 模式存 `[monitorFunc, enableWildcard]`，原始模式存裸函数 | 误判模式下元组结构不匹配，`MonitorV2` 取通配符标志拿到错误值 |

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 修复/缓解变更 | 关系证据 |
|----------|----------|---------------|---------------|----------|
| 参数类型分支不完整 + 缺少对象真值守卫 | 在 `else` 分支内增加 `if (optionsOrFirstPath && typeof optionsOrFirstPath === 'object')` 守卫，仅 object 真值才进入 options 模式 | `v2_decorators.ts` 的 `Monitor` 工厂函数：`monitorWithOptionsMode`/`enableWildcard` 赋值移入守卫内 | 3e4088eabce (fixed) | commit diff：`else` 分支从无条件赋值改为带 `typeof === 'object'` 守卫的嵌套 `if` |

修复前（缺陷版本）options 分支无条件置 `monitorWithOptionsMode = true` 并读取 `.enableWildcard`；修复后仅当 `optionsOrFirstPath && typeof optionsOrFirstPath === 'object'` 才进入 options 模式，`undefined`/`null` 保持默认 `monitorWithOptionsMode = false`，走原始字符串路径注册。

## 关联变更

| 变更编号 | 变更简述 | 根因类别 | 变更关系 | 证据 | 确信度 |
|----------|----------|----------|----------|------|--------|
| CHG-01 | `Monitor` 工厂函数 options 分支增加 `typeof === 'object'` 真值守卫 | 参数类型分支不完整 + 缺少对象真值守卫 | fixed | commit 3e4088eabce diff | verified |

关联 issue：[#77341](https://gitcode.com/openharmony/arkui_ace_engine/issues/77341)（已关闭，master）
合并 MR：!85660

> 覆盖范围：当前仅覆盖「首参类型分支不完整」单一根因类别，对应 issue #77341 单一案例。装饰器其他参数边界（如 `path` 为非字符串、`...pathN` 含非字符串）后续补充。

## 预防措施

- 装饰器工厂函数对联合类型参数做分支时，必须用显式 `typeof` + 真值守卫覆盖所有可能类型分支，不能只判 `=== 'string'` 后让其余类型落入对象分支
- 对 `as` 类型断言后的属性访问，应在断言前增加运行时类型守卫（`typeof === 'object' && value !== null`），避免擦除类型后访问 `undefined`/`null` 属性
- 新增 `@Monitor` 调用形式或扩展 `MonitorDecoratorOptions` 字段时，补充针对 `undefined`/`null`/原始值的单测
- 代码审查重点：装饰器工厂参数分支是否对称覆盖联合类型每一支，非目标分支是否真正 no-op

## 相关主题

- `docs/kb/frontend/state_management/v2_decorators.md`：V2 装饰器总览，`@Monitor` 行映射表与源码入口
- `docs/kb/frontend/state_management/v2_core.md`：V2 核心逻辑，`ObserveV2` 单例与依赖图
- 功能域 `07-02-04`（状态管理 V2 组件内状态管理）
