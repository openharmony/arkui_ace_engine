# LazyForEach 预加载节点反复创建 Issue Context

> 文档版本：v1.0
> 更新时间：2026-09-20
> 来源：`docs/context_registry.json` 主题 `LazyForEachPrebuildNodeRepeatCreation`
> 关联功能域：`07-05-02`

## 问题概述

LazyForEach 预加载（PreBuild）子项时若单帧超时，会把未完成项推迟到后续帧续建；续建时每次都会重新执行键值生成函数并按新算出的 key 查找上一帧的缓存。若 `keyGenerator` 含随机数、时间戳等易变输入，续建时 key 发生漂移导致缓存一直未命中，于是重新创建新节点；若再次超时则重复该循环，表现为预加载节点被反复创建、CPU/内存浪费、预加载长时间不收敛。

典型表现：
- 预加载区间内同一 index 的节点被反复创建、上一帧半成品节点被丢弃
- HiTrace 中同一 index 的 `Builder:BuildLazyItem` 跨多帧重复出现且伴随 `isTimeout[1]`
- 空闲/滚动预加载阶段 CPU 占用异常，`cachedCount` 预加载始终建不完

## 关联模块

| kind | role | name | evidence | confidence |
|------|------|------|----------|------------|
| component | symptom_surface | LazyForEach 预加载链路（LazyForEachNode predict task + LazyForEachBuilder::PreBuild/CacheItem） | `frameworks/core/components_ng/syntax/lazy_for_each_node`，`frameworks/core/components_ng/syntax/lazy_for_each_builder` | verified |
| architecture | root_cause_owner | 键值生成函数 keyGenFunc_（应用侧 keyGenerator 含随机值/时间戳等易变输入） | `frameworks/bridge/declarative_frontend/jsview/js_lazy_foreach`，`frameworks/bridge/declarative_frontend/jsview/js_lazy_foreach_builder` | verified |
| capability | fix_location | 应用侧 keyGenerator 稳定化（业务代码修复，引擎无变更） | `frameworks/bridge/declarative_frontend/jsview/js_lazy_foreach`（keyGenerator 注入位置） | verified |

## 根因分类

| 根因类别 | 触发条件 | 典型场景 |
|----------|----------|----------|
| keyGenerator 返回不稳定 key | 键值生成函数使用随机数、时间戳、自增序列等每次调用都变化的输入，且预加载单帧超时被推迟到后续帧续建 | 长列表大数据量子项 + `cachedCount` 预加载，子项构建耗时超过 predict deadline，key 含 `Math.random()`/`Date.now()` |

## 排查路径

### 快速判断

1. 确认 `LazyForEach` 是否显式传入了 `keyGenerator`。
2. 检查该函数返回值是否包含随机数、时间戳、自增计数等每次调用会变化的量（同一数据多次调用应返回同一 key）。
3. 在 HiTrace 中观察同一 index 的 `Builder:BuildLazyItem` 是否跨帧重复出现且 `isTimeout` 为 1。
4. 确认问题只出现在预加载（空闲/滚动触发缓存预构建）阶段，而可见区主链路（`GetChildByIndex`）行为正常。

### 详细排查

#### keyGenerator 不稳定排查

| 步骤 | 操作 | 预期结果 | 失败则 |
|------|------|----------|--------|
| 1 | 对同一 index 连续调用两次 `keyGenerator(data, index)` 并比对返回值 | 两次返回值相同 | 命中本根因：key 漂移 |
| 2 | 抓取 HiTrace 查看 `Builder:BuildLazyItem index[x] isTimeout[1]` 后续帧是否再次出现同 index | 超时后下一帧续建一次即完成 | 同 index 反复出现 → 续建缓存未命中 |
| 3 | 临时替换为稳定 key（如纯业务 id）复测 | 反复创建消失 | 检查是否还有其余易变输入来源 |
| 4 | 核对旧半成品节点是否经 `LoadCacheByKey` 走 `DetachFromMainTree` 丢弃 | 节点数不持续增长但创建持续发生 | 若节点数也增长，另行排查释放链路 |

关键代码定位：
- `frameworks/core/components_ng/syntax/lazy_for_each_node`：`PostIdleTask` 注册 predict 任务；`PreBuild` 未完成时再次 `PostIdleTask(POST_IDLE_TASK)` 推迟到后续帧
- `frameworks/core/components_ng/syntax/lazy_for_each_builder`：`CacheItem` 内 `RenderCustomChild(deadline)` 超时置位 `isTimeout`
- `frameworks/core/components_ng/syntax/lazy_for_each_builder`：超时记录 `preBuildingIndex_`；下帧 `ProcessPreBuildingIndex` 优先续建
- `frameworks/core/components_ng/syntax/lazy_for_each_builder`：超时分支 `expiringItem_.swap(cache)`，半成品节点以旧 key 存入 `expiringItem_`
- `frameworks/bridge/declarative_frontend/jsview/js_lazy_foreach_builder`：`OnGetChildByIndex` 每次重算 `keyGenFunc_` 并按 key 查缓存（预加载路径 `lazy_for_each_builder` 固定走此旧接口）
- `frameworks/bridge/declarative_frontend/jsview/js_lazy_foreach_builder`：缓存未命中后 `itemGenFunc_->Call` 重新创建子树
- `frameworks/bridge/declarative_frontend/jsview/js_lazy_foreach_builder`：对比项——可见区新接口 `OnGetChildByIndexNew` 优先复用 `cachedItems_` 已存 key，无此保护的是预加载路径

## 修复方案

| 根因类别 | 修复策略 | 关键代码改动点 | 修复/缓解变更 | 关系证据 |
|----------|----------|---------------|---------------|----------|
| keyGenerator 返回不稳定 key | 键值生成函数只依赖稳定业务字段（如数据 id），移除随机数/时间戳/自增等易变输入；无内容型 key 需求时可省略 `keyGenerator` 走默认序号 key | 应用侧 `keyGenerator` 实现（引擎无需变更） | 当前实现 | `js_lazy_foreach`（keyGenerator 注入位置） |

## 关联变更

| 变更编号 | 变更简述 | 根因类别 | 变更关系 | 证据 | 确信度 |
|----------|----------|----------|----------|------|--------|
| CHG-01 | 预加载超时续建机制：predict task 超时后 `PostIdleTask` 推迟下一帧、`preBuildingIndex_` 记录续建项 | keyGenerator 返回不稳定 key | related | `lazy_for_each_node`，`lazy_for_each_builder` | verified |
| CHG-02 | 预加载续建入口 `OnGetChildByIndex` 每次重新执行 keyGenFunc_ 并按 key 匹配缓存，key 漂移即未命中重建 | keyGenerator 返回不稳定 key | related | `js_lazy_foreach_builder` | verified |

## 预防措施

- `keyGenerator` 必须是纯函数：同一 `(data, index)` 输入多次调用返回相同 key，禁止使用 `Math.random()`、`Date.now()`、自增计数器等易变输入。
- 长列表场景优先使用数据侧稳定唯一 id 作为 key。
- 预加载反复不收敛时优先排查 key 稳定性，再排查子项构建耗时。
- 测试中对 `keyGenerator` 做幂等性断言（同输入调用两次比对结果）。

## 相关主题

- `docs/kb/syntax/lazy-for-each.md`（LazyForEach 代码型 KB：key 契约、三级缓存、pre-build）
- `docs/kb/issues/rendering/repeat-render-data-duplicate.md`（Repeat 生命周期错配导致数据重复）
- `specs/07-frontend/05-render-control/02-lazy-foreach/`
