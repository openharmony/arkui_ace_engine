# 特性规格 — WithEnv direction 与作用域生命周期

> 本文只固化开发者可观察行为、Public API 契约和验收标准。内部对象、注册表、回调安装、上下树时序与风险见 `design.md`。

## 概述

| 属性 | 值 |
|------|-----|
| 特性名称 | WithEnv direction 与 Env/CustomEnv 作用域生命周期 |
| 特性编号 | FEAT-04-03-01-01 |
| 所属 Epic | 无 |
| 优先级 | P0 |
| 目标版本 | 未规划版本 |
| SIG 归属 | SIG_ArkUI |
| 状态 | Review |
| 复杂度 | 标准 |

## 本次变更范围（Delta）

| 类型 | 内容 | 说明 |
|------|------|------|
| ADDED | `WritableEnvKey.DIRECTION` 与 `WithEnvAttribute.env()` | WithEnv 可向局部子树提供 direction 默认值 |
| ADDED | `@Env(WritableEnvKey.DIRECTION)` | 自定义组件可读取并响应最近 WithEnv 的 direction |
| ADDED | 已读取 Env/CustomEnv 的上下树恢复语义 | 下树恢复默认值，再挂树按新祖先链重新解析 |
| MODIFIED | `@Env` 参数范围、`CustomEnvKey<T>`、`@CustomEnv` 与 `customEnv<T>()` | 引入强类型 key；CustomEnv 初始化默认值必须独立保留 |
| REMOVED | 无 | 本期不移除运行时能力 |

## 输入文档

| 文档 | 路径 | 状态 |
|------|------|------|
| Requirement | `proposal.md` | Baselined；2026-08-05 补充生命周期与默认值边界 |

## 用户故事

### US-1：为局部子树设置默认 direction

**作为** ArkTS 应用开发者，**我想要** 在 WithEnv 上设置 direction，**以便** 统一控制局部子树的默认布局方向。

| AC编号 | 验收标准 | 类型 |
|--------|----------|------|
| AC-1.1 | WHEN WithEnv 设置 `Direction.Rtl` 且后代未显式设置 direction，THEN 后代使用 RTL 作为默认布局方向 | 正常 |
| AC-1.2 | WHEN WithEnv 设置 `Direction.Ltr` 且后代未显式设置 direction，THEN 后代使用 LTR 作为默认布局方向 | 正常 |
| AC-1.3 | WHEN WithEnv 设置 `Direction.Auto`，THEN 后代保留 Auto 语义，并继续按既有全局方向规则解析非 Auto 结果 | 边界 |
| AC-1.4 | WHEN 后代不存在定义 direction 的 WithEnv 祖先，THEN 后代不获得局部 env direction，并沿用既有 Auto/全局方向规则 | 边界 |

### US-2：在自定义组件中读取 direction

**作为** ArkTS 自定义组件开发者，**我想要** 使用 `@Env(WritableEnvKey.DIRECTION)`，**以便** 让组件逻辑响应当前局部方向。

| AC编号 | 验收标准 | 类型 |
|--------|----------|------|
| AC-2.1 | WHEN 组件首次读取 `@Env(WritableEnvKey.DIRECTION)` 且最近 WithEnv 定义了 direction，THEN 变量得到最近祖先值 | 正常 |
| AC-2.2 | WHEN 已读取该变量后，当前生效的 WithEnv 将 direction 从 LTR 更新为 RTL，THEN 变量及其绑定 UI 更新为 RTL | 正常 |
| AC-2.3 | WHEN 组件首次读取该变量且没有定义 direction 的 WithEnv 祖先，THEN 变量得到本特性定义的 direction 默认值 `Auto` | 边界 |
| AC-2.4 | WHEN 组件代码给 `@Env` 变量赋值，THEN 运行时拒绝赋值并报告只读错误 | 异常 |

### US-3：保持 direction 覆盖与嵌套规则

**作为** ArkTS 应用开发者，**我想要** 显式 direction 和嵌套 WithEnv 具有确定优先级，**以便** 在统一默认值下仍能精确覆盖局部节点。

| AC编号 | 验收标准 | 类型 |
|--------|----------|------|
| AC-3.1 | WHEN 节点显式设置 LTR 而最近 WithEnv 设置 RTL，THEN 节点使用 LTR | 正常 |
| AC-3.2 | WHEN 节点显式设置 RTL 而最近 WithEnv 设置 LTR，THEN 节点使用 RTL | 正常 |
| AC-3.3 | WHEN 内外两层 WithEnv 定义同一 direction key，THEN 内层后代使用最近的内层值，外层同 key 更新不越过内层覆盖 | 边界 |
| AC-3.4 | WHEN direction 影响线性焦点遍历，THEN 焦点遍历使用节点最终解析出的布局方向 | 回归 |

### US-4：组件上下树时按当前作用域恢复

**作为** 使用 BuilderNode、语法节点复用或组件重挂载的开发者，**我想要** Env/CustomEnv 始终对应组件当前树位置，**以便** 避免离屏旧值和旧作用域更新。

| AC编号 | 验收标准 | 类型 |
|--------|----------|------|
| AC-4.1 | WHEN 已读取 WithEnv 覆盖值的组件进入 detached/off-main-tree 状态，THEN direction Env 恢复 `Auto`，CustomEnv 恢复组件初始化时保存的本地默认值，并对实际值变化执行正常状态通知 | 恢复 |
| AC-4.2 | WHEN 组件从 WithEnv A 下树后再挂入 WithEnv B，THEN 可观察顺序为“离屏默认值”后“B 的最近祖先值”，且后续只响应 B 的有效作用域更新 | 恢复 |
| AC-4.3 | WHEN 组件只声明但从未读取相关 Env/CustomEnv，THEN 首次挂树、下树和再次挂树均不提前初始化变量，不触发 Watch 或绑定 UI 更新 | 兼容 |
| AC-4.4 | WHEN 组件在 detached/off-main-tree 状态首次读取相关变量，THEN 此次读取获得默认值；随后挂入定义对应 key 的 WithEnv 子树时，已初始化变量更新为最近祖先值 | 恢复 |
| AC-4.5 | WHEN CustomEnv 当前 WithEnv 覆盖值变化或组件离开该作用域，THEN WithEnv 覆盖不得覆盖或丢弃组件声明的本地默认值 | 兼容 |
| AC-4.6 | WHEN 组件含多个已读取的 Env/CustomEnv key 且一次上下树导致多个值变化，THEN 每个实际变化变量分别通知其观察者一次，不因多个 key 的连续查值而重复触发 tree-state 更新 | 兼容 |

## 规则定义

| 规则ID | 类型 | 触发条件 | 预期行为 | 边界/约束 | 关联AC |
|--------|------|----------|----------|-----------|--------|
| R-1 | 行为 | WithEnv 以合法 direction 值调用 `.env()` | 未显式 direction 的后代使用该值作为局部默认值 | 仅影响当前 WithEnv 子树 | AC-1.1, AC-1.2, AC-1.3 |
| R-2 | 边界 | 节点显式 direction、WithEnv direction 与全局方向同时存在 | 按“显式值 > 最近 WithEnv 值 > 既有 Auto/全局规则”解析 | `Auto` 不等于强制 LTR 或 RTL | AC-1.3, AC-1.4, AC-3.1, AC-3.2 |
| R-3 | 行为 | 组件首次读取 direct-query direction Env | 返回当前最近祖先值；无值时返回 `Auto` | 本期只定义 direction 的默认值 | AC-2.1, AC-2.3 |
| R-4 | 行为 | 当前生效的 WithEnv 更新已读取 key | 对应变量与绑定 UI 响应更新 | 内层同 key 覆盖阻断外层更新 | AC-2.2, AC-3.3 |
| R-5 | 异常 | 调用方给 `@Env` 或初始化完成后的 `@CustomEnv` 赋值 | 拒绝赋值并报告只读错误 | CustomEnv 的组件字段初始化不视为运行期赋值 | AC-2.4, AC-4.5 |
| R-6 | 恢复 | 已读取变量的组件下树 | Env/CustomEnv 恢复各自默认值 | detached/off-main-tree 不继承旧 WithEnv | AC-4.1, AC-4.2 |
| R-7 | 边界 | 变量仅声明、尚未首次读取 | 生命周期变化不初始化该变量 | 无查值、Watch、绑定 UI 更新 | AC-4.3 |
| R-8 | 恢复 | 离屏首次读取后挂树 | 先返回默认值，挂树后校正为新祖先链值 | 只处理已经初始化的变量 | AC-4.4 |
| R-9 | 行为 | CustomEnv 字段完成组件初始化 | 独立保存本地默认值，后续 WithEnv 覆盖只改变当前值 | 默认值可为 falsey 或 `undefined` | AC-4.1, AC-4.5 |
| R-10 | 行为 | 一次 tree-state 变化改变多个已初始化变量 | 每个实际变化变量各通知一次，不产生额外重复 tree-state 更新 | 不合并不同变量的 Watch 语义 | AC-4.6 |
| R-11 | 边界 | direction key 被移除 | 布局查询回到既有 Auto/全局规则 | 已缓存装饰器变量的 key-remove 行为沿用既有更新协议，不由本次生命周期修正重新定义 | AC-1.4 |

## 验收追溯

| AC | 关联规则 | 关联 Task | 验证方式 | 证据 |
|----|----------|-----------|----------|------|
| AC-1.1～AC-1.4 | R-1, R-2, R-11 | TASK-001 | 组件 unittest + ArkTS/HAP | `evidence/reviews/spec-compliance.md` |
| AC-2.1～AC-2.4 | R-3, R-4, R-5 | TASK-001 | 组件 unittest + ArkTS/HAP | `evidence/reviews/spec-compliance.md` |
| AC-3.1～AC-3.4 | R-2, R-4 | TASK-001 | 组件 unittest + 焦点回归 | `evidence/reviews/spec-compliance.md` |
| AC-4.1～AC-4.6 | R-6～R-10 | TASK-001 | C++ 生命周期 unittest + ArkTS/HAP | `evidence/reviews/spec-compliance.md` |

## 验证映射

| 编号 | 对应规格项 | 验证方式 | 验证重点 |
|------|------------|----------|----------|
| VM-1 | R-1, R-2 / AC-1.*, AC-3.* | 组件 unittest | direction 优先级、嵌套屏蔽、无祖先回退 |
| VM-2 | R-3～R-5 / AC-2.* | ArkTS/HAP + bridge 定向验证 | 首次读取、更新、只读错误 |
| VM-3 | R-6～R-9 / AC-4.1～AC-4.5 | C++ 生命周期 unittest + ArkTS/HAP | detach 默认值、reparent、新作用域重绑、懒初始化 |
| VM-4 | R-10 / AC-4.6 | ArkTS/HAP 状态观察 | 多 key Watch 独立且无重复 tree-state 更新 |

## API 变更分析

### 新增 API

| API 名称 | 开放范围 | 入参概要 | 返回值 | 错误码范围 | 功能描述 | 关联 AC |
|----------|----------|----------|--------|------------|----------|---------|
| `SystemEnvKey<T>` / `WritableSystemEnvKey<T>` / `ReadonlySystemEnvKey<T>` | Public | key 标识 | key 对象 | N/A | 系统环境变量 key 类型体系 | AC-1.1, AC-2.1 |
| `WritableEnvKey.DIRECTION` | Public | N/A | `WritableSystemEnvKey<Direction>` | N/A | direction 系统 env key | AC-1.1, AC-2.1 |
| `WithEnvAttribute.env<T>()` | Public | 可写 key 与同类型 value | `WithEnvAttribute` | N/A | 设置子树系统 env，支持链式调用 | AC-1.1～AC-1.3 |
| `CustomEnvKey.create<T>()` | Public | N/A | `CustomEnvKey<T>` | N/A | 创建强类型自定义 env key | AC-4.5 |

### 变更/废弃 API

| API 名称 | 变更类型 | 影响场景 | 迁移指引 | 关联 AC |
|----------|----------|----------|----------|---------|
| `Env(...)` | 扩展 | 新增接受 `SystemEnvKey<T>` | 既有 `SystemProperties` 用法保持；direction 使用 `WritableEnvKey.DIRECTION` | AC-2.1～AC-2.4 |
| `CustomEnv(...)` | 签名变更 | string key 调用方 | 改为传入 `CustomEnvKey<T>` | AC-4.5 |
| `WithEnvAttribute.customEnv(...)` | 签名变更 | string key 与 `any` value 调用方 | 改为 `customEnv<T>(CustomEnvKey<T>, T)` | AC-4.5 |

## 接口规格

### `WithEnvAttribute.env<T>(key, value)`

| 属性 | 值 |
|------|-----|
| 返回值 | `WithEnvAttribute`，可继续链式调用 |
| 开放范围 | Public |
| 错误码 | N/A |
| 关联 AC | AC-1.1～AC-1.4 |

| 参数 | 类型 | 必填 | 默认值 | 约束条件 |
|------|------|------|--------|---------|
| key | `WritableSystemEnvKey<T>` | 是 | 无 | 本期可验收的系统 key 为 `WritableEnvKey.DIRECTION` |
| value | `T` | 是 | 无 | direction 取 `Direction.Ltr/Rtl/Auto` |

### `@Env(WritableEnvKey.DIRECTION)`

| 属性 | 值 |
|------|-----|
| 返回值 | 只读的当前 direction 值 |
| 开放范围 | Public |
| 错误码 | 运行期赋值报告只读错误 |
| 关联 AC | AC-2.1～AC-2.4, AC-4.1～AC-4.4 |

| # | 触发条件 | 预期行为 | 关联 AC |
|---|----------|----------|---------|
| 1 | 有定义 direction 的最近 WithEnv | 首次读取返回该值并响应后续有效作用域更新 | AC-2.1, AC-2.2 |
| 2 | 无定义 direction 的 WithEnv | 返回 `Auto` | AC-2.3 |
| 3 | 下树或挂入新作用域 | 下树恢复 `Auto`，挂树后校正为新作用域值 | AC-4.1, AC-4.2, AC-4.4 |

## 兼容性声明

- **已有 API 行为变更：** 是。CustomEnv string key 调用方式迁移为 `CustomEnvKey<T>`；`@Env` 扩展系统 key。
- **初始化兼容：** 仅声明未读取的 Env/CustomEnv 仍保持懒初始化，普通首次挂树不得产生新增 Watch 或 UI 更新。
- **默认值边界：** 本期只定义 direction=`Auto`；fontScale 默认值和用户可见生命周期不在本期规格中。
- **配置文件格式变更：** 否。
- **数据存储格式变更：** 否。
- **最低支持版本 / `@since`：** 由 SDK 声明发布流程确定，本文不虚构版本号。

## 架构约束

| 关键约束 | 约束说明 | 影响 AC |
|----------|----------|---------|
| 当前树作用域唯一有效 | detached/off-main-tree 组件不继承旧 WithEnv；再挂树只认新祖先链 | AC-4.1, AC-4.2, AC-4.4 |
| 声明与初始化分离 | decorator metadata 不能等同于变量已读取 | AC-4.3, AC-4.4 |
| 默认值所有权分离 | CustomEnv 本地默认值不能被当前 WithEnv 覆盖值替换 | AC-4.1, AC-4.5 |

## 非功能性需求

| 类型 | 指标/阈值 | 验证方式 | 证据 |
|------|-----------|----------|------|
| 性能 | 本期无用户可感知的量化阈值；未使用相关 decorator 的组件不得进入前端 tree-state 处理 | 代码审查 + 生命周期 unittest | `review.md` |
| 可靠性 | 同/跨 PipelineContext reparent 后不保留旧作用域依赖；销毁路径不崩溃 | 生命周期 unittest | `evidence/reviews/spec-compliance.md` |
| 可测试性 | 每条 P0/P1 AC 均映射到 native 或 ArkTS/HAP 验证 | 追溯审查 | `execution-plan.md` |

缓存 O(1)、精准通知替代全部 DFS、dump 支持属于后续演进目标，不是本期验收条件。

## 多设备适配声明

| 设备类型 | 行为差异 | 规格/约束 | 验证方式 | 证据 |
|----------|----------|-----------|----------|------|
| 手机、平板、折叠屏及其他 ArkUI 设备 | 无差异 | 相同组件树作用域与 direction 优先级 | 组件 unittest；设备专项验证按发布计划补充 | `execution-plan.md` |

## 全局特性影响

| 特性 | 适用？ | 结论 | 关联场景 |
|------|--------|------|----------|
| 无障碍 | 否 | 不修改语义树或朗读规则 | N/A |
| 大字体 | N/A | fontScale 不在本期规格 | N/A |
| 深色模式 | 否 | 不修改主题/颜色 | N/A |
| 多窗口/分屏 | 否 | 不新增差异行为 | N/A |
| 多用户 | 否 | 无持久化或用户数据 | N/A |
| 版本升级 | 是 | CustomEnv string key 调用方需按 API 声明迁移 | AC-4.5 |
| 生态兼容 | 是 | 维持未读取变量的懒初始化和既有 direction 显式覆盖 | AC-3.1, AC-3.2, AC-4.3 |

## Spec 自审清单

- [x] 所有 AC 使用 WHEN/THEN 格式且可独立测试
- [x] 规则统一使用 R 编号，不混用 FR/BR/ER/RC
- [x] Spec 不包含内部类名、方法名、注册表或调用时序
- [x] 每个 AC 至少关联一条规则，每条规则至少关联一个 AC
- [x] direction 默认值明确为 `Auto`，未定义 fontScale 默认值
- [x] 已实现、待验证和后续演进没有混写为同一验收结论

## context-references

```yaml
context-queries:
  - repo: "openharmony/arkui_ace_engine"
    query: "WithEnv direction Env CustomEnv detach reparent lifecycle"
```

**关键文档：** `proposal.md`、`design.md`、`execution-plan.md`、`review.md`。
