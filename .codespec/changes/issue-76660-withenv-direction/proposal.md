# 需求文档 — WithEnv Direction & Framework Refactoring

## 一、原始需求

### 基本信息

| 字段 | 内容 |
|------|------|
| 需求ID | REQ-04-03-01-01 |
| 需求名称 | WithEnv 环境变量框架新增 direction 支持 & 内部重构 |
| 来源 | 需求 Owner 提出 |
| CodeSpec ID | issue-76660-withenv-direction |
| 关联 Issue | https://gitcode.com/openharmony/arkui_ace_engine/issues/76660 |
| 提出人 | TBD |
| 目标发行版本 | TBD |
| 候选 Profile | arkui (arkui/component, arkui/sdk-api) |
| 优先级 | P0 |
| 状态 | Baselined |

### 原始描述

**原始问题：** 对环境变量 Env 能力，基于现有框架能力新增对通用属性 direction 的支持，并且重构现有的朴素 WithEnv 初版框架实现为高性能的最终版。

**关键背景：** WithEnv 初版骨架虽已合入，但设值、查值、更新通知等基础核心能力并未完整规格化，也没有经过科学严密的测试设计和验收。因此 WithEnv 框架能力本身也是本需求的关注点，direction 是第一个用来验证框架完整性的键——两者功能和测试相辅相成。

**痛点：**

| 用户类型 | 当前痛点 | 影响 |
|----------|----------|------|
| 应用开发者 | 无通过环境变量统一控制子树默认 direction 的能力 | 需要逐个组件手动设置 direction，RTL 场景下工作量大且易遗漏 |
| 框架开发者 | WithEnv 初版内部使用暴力朴素爬树和遍历派发更新信息；核心能力未规格化和测试验收 | 性能差、难扩展、代码品味不足，无法支撑后续更多系统环境变量接入，且正确性缺乏保障 |

**期望结果：** 通过 WithEnv 容器的 `.env()` 接口设置 `WritableEnvKey.DIRECTION`，控制子树默认语言方向（行为与通用属性 direction 一致）；通过 `@Env` 装饰器在自定义组件中响应式获取当前上下文的 direction 信息。同时完成 WithEnv 框架设值/查值/更新通知核心能力的规格化和测试验收。

### 背景证据

| 证据类型 | 链接/路径 | 说明 |
|----------|-----------|------|
| API 定义 | `32825.diff` | 更新后的 API 接口定义，包含 SystemEnvKey 体系和 direction 键 |
| 现有实现 | WithEnv 初版骨架（已合入） | 已有 WithEnv 容器和 CustomEnv 机制，但内部实现为朴素版本 |

### 初始范围

**可能包含：**
- `.env()` 方法——通过 `WritableSystemEnvKey` 设置系统环境变量
- `@Env` 装饰器——支持 `SystemEnvKey<T>` 类型参数
- `direction` 键——`WritableEnvKey.DIRECTION`，控制子节点默认语言方向
- WithEnv 内部框架重构（朴素爬树 → 高性能架构）
- API 声明按 `32825.diff` 更新

**明确不包含：**
- `fontScale` 功能实现（仅作为架构扩展性设计考量）
- `ReadonlySystemEnvKey` 具体键的实现（仅 API 占位）
- 跨仓变更

### 初始假设

| 假设 | 类型 | 验证方式 | 状态 |
|------|------|----------|------|
| 现有 WithEnv 初版已有 CustomEnv 机制已交付 | 技术 | 源码核对 | 待验证 |
| `32825.diff` 中的 API 定义为最终版 | 技术 | Owner 确认 | 已确认 |
| direction 行为与通用属性 direction 一致 | 技术 | 源码核对 + 设计分析 | 已确认 |
| `.env()` 设的 direction 为默认值，显式 `.direction()` 优先 | 技术 | Owner 确认 | 已确认 |
| 自定义 env 已交付，重构只牵连不改功能 | 技术 | Owner 确认 | 已确认 |

### 初始分级判断

| 判断项 | 结果 | 依据 |
|--------|------|------|
| 复杂度 | 标准 | 单仓特性，涉及新 Public API + 组件 + 框架内部重构 |
| 涉及仓数量 | 1 | ace_engine |
| 是否涉及 Public/System API | 是 | SystemEnvKey, WritableSystemEnvKey, WritableEnvKey, 更新 Env 装饰器, 更新 WithEnvAttribute |
| 是否涉及安全/性能关键路径 | 是（性能） | 框架重构涉及布局/渲染路径的 env 查值和通知机制 |
| 是否跨 SIG | 否 | — |

### 进入澄清条件

- [x] 原始问题和期望结果已记录
- [x] 需求来源和责任人已明确
- [x] 初始范围和不包含项已记录
- [x] 关键假设和待澄清问题已列出
- [x] 复杂度有判断

---

## 二、澄清记录

### 待澄清问题

| 编号 | 问题 | 为什么需要澄清 | 状态 |
|------|------|----------------|------|
| Q-1 | FuncID / FeatID / 功能域层级 | arkui profile 要求 Owner 确认 | 已澄清 |
| Q-2 | fontScale 是否在本期范围 | 需求提到但语义模糊 | 已澄清 |
| Q-3 | `.env(direction)` 与显式 `.direction()` 的优先级 | 决定 env 的确切语义 | 已澄清 |
| Q-4 | "高性能"的可度量标准 | 需要量化验收条件 | 已澄清 |
| Q-5 | 现有键和 API 兼容性 | 确定不破坏已有功能 | 已澄清 |
| Q-6 | 自定义 env 是否在本期交付 | diff 中有定义但范围不清 | 已澄清 |
| Q-7 | 维测合同 | dump 需求未明确 | 已澄清 |
| Q-8 | 框架核心能力规格化程度 | 初版未规格化和测试验收 | 已澄清 |

### 讨论记录

| 日期 | 参与人 | 讨论主题 | 结论 | 后续动作 |
|------|--------|----------|------|----------|
| 2025-05-25 | Owner | 功能域定位 | FuncID 04-03-01, Feat-01, 通用能力>容器组件>环境变量 | — |
| 2025-05-25 | Owner | fontScale 范围 | 本期不交付，仅作架构扩展性设计考量 | — |
| 2025-05-25 | Owner | env vs 显式优先级 | 显式设置优先，env 只提供默认值 | — |
| 2025-05-25 | Owner | 性能标准 | O(1) 查值和零开销为理想目标，非硬性通过条件，代码审查品评 | — |
| 2025-05-25 | Owner | 现有键和 API | 初版无已有键；API 按 32825.diff 更新 | — |
| 2025-05-25 | Owner | 自定义 env 范围 | 自定义 env 已交付，重构牵连但非新交付 | — |
| 2025-05-25 | Owner | 维测合同 | 可以添加 dump 信息，较为次要 | — |
| 2025-05-25 | Owner | 框架核心能力 | 初版设值/查值/更新通知未规格化和测试验收，框架能力和 direction 共生交付 | — |

### 功能范围确认

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 核心交付包含哪些？ | `.env()` 方法、`@Env(SystemEnvKey<T>)` 装饰器、`direction` 键、框架重构 | Owner | 已确认 |
| 明确不包含哪些？ | fontScale 实现、ReadonlySystemEnvKey 具体键、跨仓变更 | Owner | 已确认 |
| 是否有分期策略？ | 无，一次性交付 | Owner | 已确认 |

### 方案探索

> 标准复杂度必填。框架重构的核心方案选型。

| 编号 | 方案概述 | 优势 | 风险/代价 | 选择结论 |
|------|----------|------|-----------|----------|
| A-1 | **惰性缓存树 + 增量通知**：env 值缓存在节点树上，查值 O(1)；属性变化时沿树增量通知，节点上下树时维护缓存一致性 | 查值快、通知精确、内存可控 | 缓存一致性维护复杂（节点增删、树结构变化） | 推荐 |
| A-2 | **代理节点 + 观察者链**：插入虚拟代理节点持有 env 值，子树通过观察者模式订阅 | 解耦清晰、扩展性好 | 引入额外节点开销、与现有组件树集成复杂 | 备选 |

**取舍理由：** A-1 不引入额外节点，与现有组件树自然集成，对不使用 env 的场景零开销。A-2 虽然解耦更好但代价较高。具体架构决策见 design.md。

### 子系统影响

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 涉及哪些子系统？ | ArkUI（ace_engine 单仓） | Owner | 已确认 |
| 是否需要新增子系统或部件？ | 否 | Owner | 已确认 |

### API 变更评估

| 问题 | 回答 | 确认人 | 状态 |
|------|------|--------|------|
| 是否需要新增 Public API？ | 是 — `SystemEnvKey<T>`, `WritableSystemEnvKey<T>`, `ReadonlySystemEnvKey<T>`, `WritableEnvKey`, 更新 `Env` 签名 | Owner | 已确认 |
| 是否需要新增 System API？ | 否 | — | N/A |
| 是否会废弃已有 API？ | 是 — 旧 `customEnv(key: string, value: any)` 替换为泛型版本，旧 `Env` 签名扩展为联合类型 | Owner | 已确认 |
| 是否需要新增权限声明？ | 否 | — | N/A |

### 兼容性与非功能需求

| 类别 | 核心问题 | 结论 | 确认人 | 状态 |
|------|----------|------|--------|------|
| 兼容性 | 自定义 env 已有功能是否受影响 | 功能行为不变，内部实现因重构可能调整 | Owner | 已确认 |
| 性能 | 不使用 env 时零额外开销（理想目标）；env 场景 O(1) 查值（理想目标） | 作为设计目标和代码审查维度，非硬性通过条件 | Owner | 已确认 |
| 安全 | N/A — 无权限/隐私/加密需求 | — | — | N/A |
| 可靠性 | 属性变化和节点上下树时缓存维护正确性必须保证 | 必须 | Owner | 已确认 |

### 依赖与风险

| 依赖项 | 类型 | 说明 | 状态 |
|--------|------|------|------|
| 32825.diff API 定义 | 编译 | API 声明需按 diff 更新 | 已确认 |

| 风险 | 类型 | 影响 | 缓解措施 | 状态 |
|------|------|------|----------|------|
| 框架重构引入缓存一致性 bug | 技术 | 高 — 可能导致 env 值在节点上下树时错误 | 充分的单元测试覆盖节点增删场景 | 已确认 |
| 重构影响已有 CustomEnv 功能 | 技术 | 中 — 功能行为不应变化但内部实现调整 | 回归测试验证 CustomEnv 行为不变 | 已确认 |

### AC 完整性

- [x] 每个用户故事有验收标准
- [x] AC 全部使用 WHEN/THEN 格式
- [x] 覆盖正常流程、异常流程、边界条件
- [x] AC 可测试、可度量

### 澄清结论

- [x] 功能范围已完全明确
- [x] 子系统影响已识别
- [x] API 变更已评估
- [x] 兼容性和非功能需求已确认
- [x] 依赖和风险已识别且有缓解方案
- [x] 标准及以上复杂度已完成方案探索

**结论:** 通过

---

## 三、需求基线

> 澄清完成后固化。manifest.md 是事实源，此处为审批结论。

### 基线信息

| 字段 | 内容 |
|------|------|
| 基线版本 | v1.0 |
| 基线日期 | 2025-05-25 |
| Owner | TBD |
| 确认人 | TBD |
| 复杂度 | 标准 |
| Profile | arkui (arkui/component, arkui/sdk-api) |
| 目标发行版本 | TBD |
| 版本状态 | proposed |

### 问题陈述

WithEnv 环境变量框架初版采用朴素爬树遍历实现，性能差且难扩展。初版骨架虽已合入，但设值、查值、更新通知等基础核心能力并未完整规格化，也没有经过科学严密的测试设计和验收。本期需要：(1) 新增 direction 环境变量键，使开发者能通过 `.env()` 统一控制子树默认方向；(2) 重构内部框架为高性能、易扩展架构，支撑后续更多系统环境变量接入；(3) 完成 WithEnv 框架设值/查值/更新通知核心能力的规格化设计和测试验收。direction 是第一个验证框架完整性的键，两者功能和测试相辅相成。

### 目标和成功指标

| 目标 | 成功指标 | 验证方式 |
|------|----------|----------|
| 通过 env 设置 direction | `.env(WritableEnvKey.DIRECTION, value)` 能控制子树默认方向 | 组件 unittest + SpecTest |
| @Env 响应式获取 direction | `@Env(WritableEnvKey.DIRECTION)` 装饰的变量随祖先 env 变化而更新 | 组件 unittest |
| 显式设置优先 | 子节点 `.direction()` 覆盖 env 默认值 | 组件 unittest |
| 框架高性能 | 查值非朴素爬树，不使用 env 时零额外开销 | 代码审查 |
| 框架易扩展 | 新增一个系统 env 键（如 fontScale）只需少量代码 | 设计文档 |
| CustomEnv 兼容 | 已有 CustomEnv 功能行为不变 | 回归测试 |
| 框架核心能力规格化 | 设值/查值/更新通知有完整设计、测试覆盖和验收证据 | 设计文档 + unittest |
| Dump 支持 | env 相关信息可 dump（次要优先级） | dump 输出验证 |

### 用户故事与 AC

| Story ID | 用户故事 | 优先级 |
|----------|----------|--------|
| US-1 | 作为应用开发者，我想要通过 WithEnv 容器的 .env() 设置 direction，以便统一控制子树默认语言方向 | P0 |
| US-2 | 作为应用开发者，我想要通过 @Env 装饰器在自定义组件中响应式获取 direction 信息，以便在组件逻辑中使用 | P0 |
| US-3 | 作为应用开发者，我想要在子节点上显式设置 .direction() 覆盖 env 默认值，以便精确控制特定组件的方向 | P0 |
| US-4 | 作为框架开发者，我想要 WithEnv 内部框架高性能且易扩展，以便支撑后续更多系统环境变量接入 | P1 |

| AC编号 | 验收标准 | 类型 | 关联Story |
|--------|----------|------|-----------|
| AC-1 | WHEN 开发者在 WithEnv 容器上设置 `.env(WritableEnvKey.DIRECTION, Direction.Rtl)` THEN 容器内未显式设置 direction 的子节点使用 `Direction.Rtl` 作为默认方向 | 正常 | US-1 |
| AC-2 | WHEN 开发者修改 WithEnv 的 `.env(WritableEnvKey.DIRECTION, Direction.Ltr)` 为 `Direction.Rtl` THEN 已通过 @Env 获取 direction 的自定义组件变量响应式更新为 `Direction.Rtl` | 正常 | US-1, US-2 |
| AC-3 | WHEN 自定义组件使用 `@Env(WritableEnvKey.DIRECTION) directionValue: Direction = Direction.Auto` THEN `directionValue` 等于最近祖先 WithEnv 中设置的 direction 值 | 正常 | US-2 |
| AC-4 | WHEN 自定义组件使用 `@Env(WritableEnvKey.DIRECTION)` 但无 WithEnv 祖先 THEN `directionValue` 保持默认值（组件定义的初始值） | 边界 | US-2 |
| AC-5 | WHEN 子节点显式设置 `.direction(Direction.Ltr)` 而 WithEnv 设置 `.env(WritableEnvKey.DIRECTION, Direction.Rtl)` THEN 子节点使用 `Direction.Ltr` | 正常 | US-3 |
| AC-6 | WHEN WithEnv 容器内嵌套另一个 WithEnv 且内层设置不同的 direction THEN 内层容器内的子节点使用内层的 direction 值 | 正常 | US-1 |
| AC-7 | WHEN 不使用 WithEnv 组件的页面执行组件创建/布局/渲染 THEN 路径上无 env 相关的额外函数调用、分支判断或内存分配 | 边界 | US-4 |
| AC-8 | WHEN 子节点查询 env 值 THEN 查值时间复杂度优于 O(n) 爬树遍历 | 正常 | US-4 |
| AC-9 | WHEN 节点在组件树中挂载/卸载/移动 THEN env 缓存正确维护，无泄漏或脏数据 | 正常 | US-4 |
| AC-10 | WHEN 重构完成后 THEN 已有 CustomEnv/CustomEnvKey/customEnv 功能行为不变 | 正常 | US-4 |

### 范围边界

**包含：**
- `WritableSystemEnvKey<T>` / `WritableEnvKey.DIRECTION` 系统环境变量键体系
- `@Env` 装饰器支持 `SystemEnvKey<T>` 类型参数
- `WithEnvAttribute.env()` 方法
- WithEnv 内部框架重构（朴素爬树 → 高性能架构）
- API 声明按 `32825.diff` 更新
- 自定义 env 因重构的连带适配

**不包含：**
- `fontScale` 功能实现（仅架构扩展性设计考量）
- `ReadonlySystemEnvKey` 具体键实现（仅 API 占位）
- 跨仓变更

### 影响范围

| 子系统 | 仓库 | 模块/路径 | 当前职责 | 影响类型 | Owner |
|--------|------|-----------|----------|----------|-------|
| ArkUI | ace_engine | WithEnv 组件 pattern | 容器组件，持有 env 值 | 修改 | TBD |
| ArkUI | ace_engine | @Env 装饰器运行时 | 装饰器，注入 env 值到组件变量 | 修改 | TBD |
| ArkUI | ace_engine | env 查值/通知框架内部 | 朴素爬树遍历实现 | 重写 | TBD |
| ArkUI | ace_engine | SDK API 声明 (.d.ts) | WithEnv 和 common 类型声明 | 修改 | TBD |

### API 变更项清单

| API 名称 | 变更类型 | 开放范围 | 概要说明 |
|----------|----------|----------|----------|
| `SystemEnvKey<T>` | 新增 | Public | 系统环境变量键基类 |
| `WritableSystemEnvKey<T>` | 新增 | Public | 可写系统环境变量键 |
| `ReadonlySystemEnvKey<T>` | 新增 | Public | 只读系统环境变量键（占位） |
| `WritableEnvKey` | 新增 | Public | 系统环境变量键集合，含 DIRECTION 和 FONT_SCALE |
| `CustomEnvKey<S>` | 新增 | Public | 自定义环境变量键（已有实现，API 按新签名更新） |
| `Env` | 修改 | Public | 签名从 `EnvDecorator` 扩展为接受 `SystemEnvKey<T> \| SystemProperties` |
| `CustomEnv` | 修改 | Public | 签名从 `(string)` 改为 `(CustomEnvKey<T>)` |
| `WithEnvAttribute.env()` | 新增 | Public | 系统环境变量设置方法 |
| `WithEnvAttribute.customEnv()` | 修改 | Public | 签名从 `(string, any)` 改为 `(CustomEnvKey<T>, T)` |

### 不涉及项确认

| 维度 | 涉及？ | 依据 | 若涉及，进入哪个下游文档 |
|------|--------|------|--------------------------|
| 性能 | 是 | 框架重构目标为高性能，涉及布局/渲染路径 | design.md |
| 安全与权限 | N/A | 无权限/隐私/加密需求 | — |
| 兼容性 | 是 | 自定义 env 已有功能需保持兼容 | spec.md |
| API/SDK | 是 | 新增和修改 Public API | design.md, spec.md |
| IPC/跨进程 | N/A | 单进程内组件树操作 | — |
| 构建与部件 | N/A | 无新部件或构建系统变更 | — |
| 国际化/无障碍 | 是 | direction 直接关联国际化（RTL/LTR） | spec.md |
| 数据迁移 | N/A | 无持久化数据 | — |

### 变更控制

| 变更类型 | 触发条件 | 处理规则 |
|----------|----------|----------|
| 范围新增 | 新增用户故事或仓/模块 | 重新评估复杂度和设计影响 |
| AC 变更 | 修改可观察行为或错误码 | 重新审批基线和 Spec |
| API 变更 | 新增/修改 Public/System API | 触发设计审批 |
| 非功能指标变更 | 性能/兼容性阈值变化 | 重新确认测试计划 |
| 目标版本变更 | 交付版本调整 | 更新 manifest.target_release |

### 进入设计/Spec 条件

- [x] 所有 P0/P1 用户故事有 AC
- [x] 每条 AC 可测试、可度量
- [x] 范围内/外已确认
- [ ] `manifest.target_release` 已确认或明确 TBD — 当前 TBD
- [x] `manifest.profile` 已确认
- [x] 涉及仓、模块、SIG 已识别
- [x] 不涉及项已标记 N/A
- [x] 变更控制规则已确认

**基线结论:** 通过
