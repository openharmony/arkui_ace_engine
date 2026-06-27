# 架构设计 — WithEnv Direction & Framework Refactoring

## 设计元数据

| 字段 | 内容 |
|------|------|
| Design ID | DESIGN-04-03-01-01 |
| 关联需求 | proposal.md (REQ-04-03-01-01) |
| 目标 Feature | Feat-01 |
| CodeSpec ID | issue-76660-withenv-direction |
| 关联 Issue | https://gitcode.com/openharmony/arkui_ace_engine/issues/76660 |
| 复杂度 | 标准 |
| 目标版本 | TBD |
| Owner | TBD |
| 状态 | Implemented (partial — ADR-1/2/3 deferred) |

## 需求基线

| 项 | 补充说明 |
|----|----------|
| 交付范围 | `.env()` + `@Env(SystemEnvKey<T>)` + direction 键 + 框架重构 |
| 性能目标 | 不使用 env 零开销（理想）；env 查值优于 O(n) 爬树（理想） |
| 兼容性 | CustomEnv 已有功能行为不变 |
| 优先级 | env direction 为默认值，显式 `.direction()` 优先 |
| 框架规格化 | 设值/查值/更新通知核心能力需完整设计和测试验收 |

## 上下文和现状

### 涉及仓和模块

| 仓 | 模块 | 当前职责 | 影响 |
|----|------|----------|------|
| ace_engine | `frameworks/core/components_ng/syntax/with_env_node.*` | WithEnv UINode，持有 env 属性 maps | 重构 |
| ace_engine | `frameworks/core/pipeline_ng/environment_manager.*` | 环境变量管理器，爬树查值 + DFS 通知 | 重构 |
| ace_engine | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_decorators.ts` | @Env/@CustomEnv 装饰器 | 修改（@Env 支持 SystemEnvKey） |
| ace_engine | `frameworks/bridge/declarative_frontend/ark_with_env/src/WithEnv.ts` | WithEnv TS SDK 层 | 修改（新增 .env() 签名） |
| ace_engine | `frameworks/bridge/declarative_frontend/jsview/js_with_env.*` | WithEnv JS bridge | 修改 |
| ace_engine | `frameworks/core/components_ng/layout/layout_property.*` | 布局属性，含 direction | 修改（direction env 集成） |
| ace_engine | API 声明文件（`32825.diff`） | Public API 类型声明 | 新增/修改 |
| ace_engine | `test/unittest/core/syntax/with_env_syntax_test_ng.cpp` | 现有测试 | 扩展 |

### 当前架构问题

1. **O(n) 爬树查值**：`FindWithEnvNodeInternal()` 从查询节点逐级向上遍历父节点，每次查询重复爬树
2. **DFS 全量通知**：`NotifyValueChanged()` 对子树做深度优先遍历，不区分是否注册了依赖
3. **无解析缓存**：每次查值都重新爬树，无缓存
4. **direction 无父子继承**：当前 direction 是 per-component 的，无树级传播机制

## 架构设计

### 核心设计决策

#### ADR-1: 查值机制 — 带缓存的 EnvironmentManager 解析

> **实现状态：Deferred** — 首期保持原始 O(n) 爬树方案，缓存优化作为后续迭代。理由：功能正确性优先；缓存失效逻辑复杂度高。

**决策：** 在 EnvironmentManager 中引入解析缓存，查值 O(1)。

**方案：**
- 解析缓存：`unordered_map<int32_t /*nodeId*/, unordered_map<string /*key*/, ResolvedEntry>>`
- `ResolvedEntry` 包含：`WeakPtr<WithEnvNode> source, value, version`
- 首次查值爬树找到最近 WithEnvNode，缓存结果
- 后续查值直接命中缓存

**取舍理由：** 不给每个 FrameNode 添加 env 字段（避免影响不使用 env 的节点），而是将缓存集中在 EnvironmentManager 中。只有实际查询过 env 的节点才有缓存条目。

#### ADR-2: 通知机制 — 依赖驱动的精准通知

> **实现状态：Deferred** — 首期保持 DFS 通知方案。DependentRegistry 已存在但仅用于依赖注册，未替代 DFS 遍历。

**决策：** 替换 DFS 全量通知为依赖注册表驱动的精准通知。

**方案：**
- 利用现有 `DependentRegistry`（`nodeId → DependentEntry{weak, keys}`）
- `NotifyValueChanged()` 时只遍历该 key 的注册依赖者
- 通知方式：触发依赖者的重新渲染（markDirty），而非 DFS 回调

**取舍理由：** 现有 DependentRegistry 已有正确的数据结构，只需将通知逻辑从 DFS 改为依赖查找。精准通知避免了对无关节点的打扰。

#### ADR-3: 缓存一致性 — 脏标记懒检查

> **实现状态：Deferred** — 与 ADR-1 缓存一起延迟。无缓存则无脏标记需求。

**决策：** 基于脏标记的懒检查 + WithEnvNode 生命周期感知。

**方案：**
- `ResolvedEntry` 包含 `dirty_` 布尔标记和 `source` WeakPtr
- 当 WithEnvNode 的 env 值变化时，通过依赖注册表找到受影响的缓存条目，标记为 `dirty_`
- 查值时检查：`source` 是否仍有效 + `dirty_` 是否为 false
- `dirty_` 为 true 或 `source` 失效时，重新爬树解析并更新缓存，清除脏标记
- 节点卸载：WeakPtr 自然失效，下次查值触发重新解析
- 节点挂载/移动：无需主动通知，新位置首次查值时自然建立正确缓存

**取舍理由：** 脏标记比版本号更直观——布尔检查即可判定缓存是否可用。脏标记在通知时顺便设置（已有遍历依赖注册表的流程），不引入额外开销。避免在节点 mount/unmount 时主动遍历所有缓存条目。

#### ADR-4: Direction 集成 — 三级优先级解析

> **实现状态：Implemented** — `GetLayoutDirection()` 实现（方法名从 `GetEffectiveLayoutDirection()` 简化）。新增 `layout_direction_env.cpp` 和 `PipelineContext::ResolveDirectionFromEnv()`。

**决策：** direction 的解析优先级：显式设置 > env 默认值 > 全局 AUTO。

**方案：**
- 在 `LayoutProperty` 的 direction 解析中增加 env 层
- 解析链路：
  1. `layoutDirection_` 有值（显式设置） → 使用该值
  2. `layoutDirection_` 为 nullopt → 查询 env DIRECTION
  3. env 有值 → 使用 env 值
  4. env 无值 → 使用 `AceApplicationInfo::IsRightToLeft()` 的 AUTO 解析
- 修改 `GetNonAutoLayoutDirection()` 或新增 `GetEffectiveLayoutDirection()` 方法，接受 env 查询回调

**取舍理由：** 不修改 `TextDirection` 枚举本身，而是在解析层增加 env 来源。最小化对现有 direction 消费方的影响——它们继续调用 `GetNonAutoLayoutDirection()` 或新方法即可。

#### ADR-5: 扩展性设计 — SystemEnvKey 注册表

> **实现状态：Implemented (TS layer)** — `system_env.ts` 创建 SystemEnvKey/WritableSystemEnvKey/ReadonlySystemEnvKey 体系和 WritableEnvKey 静态类（含 DIRECTION + FONT_SCALE）。

**决策：** 每个系统 env 键用 string key 标识，通过静态注册表管理。

**方案：**
- `WritableEnvKey` 的每个键（如 DIRECTION, FONT_SCALE）有唯一 string key（如 `"Direction"`, `"FontScale"`）
- WithEnvNode 的系统 env 存储使用 `unordered_map<string, EnvironmentQueryResult>`
- 新增系统键只需：定义 string key + 在 TS/JS 层声明 + 在 C++ 层注册
- 键的值类型由 `EnvironmentQueryResult` 统一承载

**取舍理由：** 统一的存储格式降低新增键的代码量。type-safe 的泛型在 TS 层保证，C++ 层用统一的 `EnvironmentQueryResult` 承载不同类型值。

### 对象关系

```
PipelineContext
  └── EnvironmentManager (singleton per context)
        ├── valueCache_: map<nodeId, map<key, ResolvedEntry>>   // 解析缓存
        ├── depRegistry_: map<nodeId, DependentEntry>            // 依赖注册
        └── NotifyDependents(key)                                // 精准通知

WithEnvNode : UINode
  ├── systemEnvProperties_: map<string, EnvironmentQueryResult>  // 系统 env 值
  ├── customEnvProperties_: unordered_map<string, std::any>      // 自定义 env 值
  └── (无需额外字段——脏标记在缓存条目上)

FrameNode
  └── LayoutProperty
        └── layoutDirection_: optional<TextDirection>             // 显式 direction
              ↓ (nullopt 时)
              env DIRECTION 查询 → EnvironmentManager → 解析缓存/爬树
              ↓ (env 也无值)
              AceApplicationInfo::IsRightToLeft()                 // 全局 AUTO
```

### 设值/查值/更新通知流程

#### 设值（.env() 调用链）

```
TS: WithEnv.env(WritableEnvKey.DIRECTION, Direction.Rtl)
  → JS: JSWithEnv::SetEnvProperty(key, value)
    → C++: WithEnvModelNG::SetEnvProperty(key, value)
      → WithEnvNode::SetEnvProperty(key, value)
        → 更新 systemEnvProperties_[key]
        → EnvironmentManager::OnEnvValueChanged(nodeId, key)
          → 遍历 depRegistry_ 中注册了此 key 的依赖者
          → 对每个有效依赖者：标记缓存条目 dirty_ = true + markDirty + FireOnEnvUpdate
```

#### 查值（@Env 读取 / direction 解析）

```
C++: EnvironmentManager::QueryEnvValue(nodeId, key)
  → 检查 valueCache_[nodeId][key]
    → 命中且 source 有效且 dirty_ == false → 返回缓存值 (O(1))
    → 未命中或脏/失效 → 爬树解析
      → FindWithEnvNodeInternal(node) 找最近 WithEnvNode
      → ReadScopeValue(withEnvNode, key)
      → 缓存结果到 valueCache_[nodeId][key]
      → 注册依赖到 depRegistry_
      → 返回值

TS: @Env(WritableEnvKey.DIRECTION) directionValue
  → EnvV2.registerEnv() → 查询 EnvironmentManager → 返回值
```

#### 更新通知（env 值变化时）

```
EnvironmentManager::OnEnvValueChanged(withEnvNodeId, key)
  → 遍历 depRegistry_，找到注册了此 key 的依赖者
  → 对每个有效依赖者：
    → 使 valueCache_[dependentId][key] 失效
    → markDirty(dependentFrameNode)
    → 触发 re-render / re-layout
```

### Direction Env 到布局的集成路径

```
FrameNode 需要解析 direction（布局/绘制阶段）
  → LayoutProperty::GetEffectiveLayoutDirection(envQueryFn)
    → if layoutDirection_.has_value() → return layoutDirection_.value()
    → auto envDir = envQueryFn(nodeId, "Direction")
    → if envDir.has_value() → return envDir.value()
    → return GetNonAutoLayoutDirection()  // 全局 AUTO
```

**关键集成点：**
- `LayoutProperty` 新增 `GetEffectiveLayoutDirection()` 方法
- 布局算法（Flex、LazyColumn 等）调用新方法替代 `GetNonAutoLayoutDirection()`
- `Pattern::CheckLocalized()` 调用新方法
- @Env 装饰器通过 `EnvV2.registerEnv()` 读取值到组件变量

### API 映射（SDK → 运行时）

| SDK API | TS Bridge | C++ 运行时 |
|---------|-----------|-----------|
| `WritableSystemEnvKey<T>` | — | string key 标识（如 `"Direction"`） |
| `WritableEnvKey.DIRECTION` | — | C++ key `"Direction"`, value `TextDirection` |
| `.env(key, value)` | `JSWithEnv::SetEnvProperty` | `WithEnvNode::SetEnvProperty` |
| `.customEnv(key, value)` | `JSWithEnv::SetCustomEnvProperty` | `WithEnvNode::SetCustomEnvProperty` |
| `@Env(WritableEnvKey.DIRECTION)` | `EnvV2.registerEnv()` | `EnvironmentManager::QueryEnvValue` |
| `@CustomEnv(key)` | `findCustomValueByKey()` | `EnvironmentManager::ResolveOwnerScopeAndValue` |

### TS/JS 层变更

**WithEnv.ts（SDK 层）：**
- `WithEnvAttribute.env<T>(key: WritableSystemEnvKey<T>, value: T)` — 新增
- `WithEnvAttribute.customEnv<T>(key: CustomEnvKey<T>, value: T)` — 签名变更

**v2_decorators.ts（装饰器层）：**
- `@Env` — 扩展参数类型支持 `SystemEnvKey<T>`（除现有 `SystemProperties`）
- `@CustomEnv` — 参数类型从 `string` 改为 `CustomEnvKey<T>`

### Performance & Memory Budget

| 场景 | 预期 | 衡量方式 |
|------|------|----------|
| 不使用 WithEnv 的页面 | 零额外开销 | 无 env 相关分支/函数调用/内存分配 |
| 首次 env 查值 | O(d) 爬树，d 为树深度 | 缓存建立 |
| 后续 env 查值 | O(1) 缓存命中 | 无爬树 |
| env 值变化通知 | O(k) k 为依赖者数量 | 精准通知，非 DFS |
| 缓存内存 | O(n*k) n 为查值节点数，k 为键数 | 懒分配，仅查值时创建 |
| 缓存失效 | 懒检查，WeakPtr + dirty flag | 无主动遍历开销 |

### Build 影响

| 影响项 | 说明 |
|--------|------|
| BUILD.gn | 无新增编译目标，现有目标内修改源文件 |
| bundle.json | 无变更 |
| 新增依赖 | 无 |

### Dump 支持

在 WithEnvNode 的 dump 方法中输出当前 env 属性值（次要优先级）。环境变量信息包含键名、类型和当前值。

## 验证路径

| 验证类型 | 覆盖范围 | 方式 |
|----------|----------|------|
| 组件 unittest | 节点创建、属性存取、查值缓存、通知 | test/unittest/core/syntax/with_env_*_test_ng.cpp |
| 集成测试 | direction env → 布局效果 | 组件 unittest + SpecTest |
| SpecTest | direction env 影响子节点布局方向 | Host Preview Inspector 断言 |
| 回归测试 | CustomEnv 功能不变 | 现有 CustomEnv 测试 |
| 性能验证 | 缓存命中/精准通知 | 代码审查 |
