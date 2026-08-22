# LazyForEach Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `LazyForEach`

## 定位

`LazyForEach`（FuncID `07-05-02`）是 ArkUI 懒加载循环渲染语法，面向 List / Grid / Swiper 等大数据量容器，通过按需构建 + 预缓存 + 回收服务长列表性能。它通过 `IDataSource` 契约获取数据，经 `LazyForEachNode` + `LazyForEachBuilder`（三级缓存）+ `LazyLayoutWrapperBuilder`（有序访问适配）驱动渲染。

三入口共用 NG 内核：dynamic ArkTS（`JSLazyForEach`）、static Arkoala（ANI `ConstructLazyForEachNode`）、C-API NodeAdapter（`node_adapter_impl.cpp`）。key 契约是正确性关键：默认 key 仅按序号，重排/交换/删除场景需内容型 `keyGenerator`。具体行为、默认值、错误码以对应 SDK 声明、源码实现、测试和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| JS 桥接（dynamic 入口） | `frameworks/bridge/declarative_frontend/jsview/js_lazy_foreach.cpp` | `JSLazyForEach::Create`：参数校验 / keyGenFunc 构造 / options 解析 / 管线选择 |
| JS 执行器 | `frameworks/bridge/declarative_frontend/jsview/js_lazy_foreach_builder.h`、`js_lazy_foreach_actuator.h` | `JSLazyForEachBuilder` 驱动 ViewStack 构建子树；dataSource 四方法提取 / 监听器代理 |
| Model 工厂 | `frameworks/core/components_ng/syntax/lazy_for_each_model_ng.h`、legacy `LazyForEachModelImpl` | `Create` / `OnMove` / `SetItemDragHandler` |
| 语法节点 | `frameworks/core/components_ng/syntax/lazy_for_each_node.cpp`、`.h` | 按需 `GetFrameChildByIndex` / `BuildAllChildren` / `DoSetActiveChildRange` / `RecycleItems` / `PostIdleTask` / 数据变更 `OnData*` / `OnDatasetChange` |
| 缓存 / 差分引擎 | `frameworks/core/components_ng/syntax/lazy_for_each_builder.cpp`、`.h` | 三级缓存（`cachedItems_` / `expiringItem_` / build）、key 冲突、`Operate*` 差分、渐进释放 |
| 布局适配 | `frameworks/core/components_ng/syntax/lazy_layout_wrapper_builder.cpp`、`.h` | 有序 ±1 访问、Swiper 虚拟索引、`OnExpandChildLayoutWrapper` |
| ANI 静态入口 | `frameworks/core/interfaces/native/ani/lazy_for_each_node_ani_modifier.h` | `ConstructLazyForEachNode` → `ArkoalaLazyNode`（static 独立路径） |
| C-API / NodeAdapter | `frameworks/core/interfaces/native/node/node_adapter_impl.cpp` | → `CreateLazyForEachNode`（API26 门控自动注册监听器） |
| 数据源契约 | `frameworks/core/components_v2/foreach/lazy_foreach_component.h` | `V2::DataChangeListener` / `V2::Operation`（单条 + 批量契约） |
| 全局工具 / metadata | `frameworks/core/components_ng/syntax/lazy_for_each_utils.cpp`、`.h`、`adapter/ohos/entrance/ui_content_impl.cpp` | `enableRepeatAnimation` / `enableCustomComponentFreeze` 全局标志 |
| 共享基类 | `frameworks/core/components_ng/syntax/for_each_base_node.h` | `ForEachBaseNode`：onMove / drag / `DisableRecycle`（详见 07-05-01） |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic SDK | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/lazy_for_each.d.ts` | `LazyForEach(dataSource, itemGenerator, keyGenerator?)`（`@since7`，`@since12` 返回 `LazyForEachAttribute`，options `@since26`） |
| Static SDK | `<OH_ROOT>/interface/sdk-js/api/arkui/component/lazyForEach.static.d.ets` | `@since23`，`@since26 staticonly` 选项设置 |
| 数据源 / 监听器 | 同上 d.ts / `.d.ets` | `IDataSource`（totalCount/getData/register/unregister）、`DataChangeListener`（单条 `@since8` + `onDatasetChange` `@since12`）、`DataOperation*`、`LazyForEachOptions`（`@since26`） |

API 检索建议：在 SDK 中搜索 `LazyForEach`、`IDataSource`、`DataChangeListener`、`onDatasetChange`、`LazyForEachOptions`、`LazyForEachReleaseStrategy`。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| UT | `test/unittest/core/syntax/lazy_for_each_model_test_ng.cpp` | 构造 / 参数校验 / 派发 |
| UT | `test/unittest/core/syntax/lazy_for_each_builder_syntax_test_ng.cpp`、`lazy_for_each_builder_syntax_test_ng_2.cpp`、`lazy_for_each_builder_syntax_test_ng_advanced.cpp` | 三级缓存 / key 契约 / active range / pre-build |
| UT | `test/unittest/core/syntax/lazy_for_each_syntax_test_ng.cpp`、`lazy_for_each_syntax_test_ng_2.cpp` | Node 行为（recycle / idle / 数据变更标记） |
| UT | `test/unittest/core/syntax/lazy_for_each_utils_test_ng.cpp` | 全局工具 |
| UT（C-API/Arkoala） | `test/unittest/core/syntax/arkoala_lazy_test_ng.cpp`、`arkoala_lazy_test_ng_advanced.cpp`、`arkoala_lazy_two_test_ng.cpp`、`arkoala_lazy_test_ng_ai.cpp` | static 范式路径 |
| Benchmark | `test/benchmark`（长列表滚动） | 帧率 / 内存 |
| XTS | `test/xts` | dynamic/static 双范式端到端 |
| Spec 功能域 | `specs/07-frontend/05-render-control/02-lazy-foreach/` | 设计与验收契约 |
| Spec 总索引 | `specs/index.md` | `07-05-02` 功能域注册入口 |

### 相关 Spec

LazyForEach 功能域：

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | LazyForEach 核心语法与按需渲染（基线） | `Feat-01-lazy-foreach-core-syntax-and-on-demand-rendering-spec.md` |
| Feat-02 | 数据源契约与单条变更通知 | `Feat-02-data-source-contract-and-single-change-notification-spec.md` |
| Feat-03 | 批量数据集变更 onDatasetChange | `Feat-03-ondatasetchange-bulk-operations-spec.md` |
| Feat-04 | 选项策略与内存/冻结优化 | `Feat-04-options-strategy-memory-and-freeze-optimization-spec.md` |
| Feat-05 | 拖拽排序 onMove | `Feat-05-onmove-drag-reorder-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 重排 / 交换 / 删除后渲染错位 | 默认 key 仅按序号（`viewId-index`），重排场景须提供内容型 `keyGenerator` |
| 重复 key 静默丢弃 | `lazy_for_each_builder.cpp` `try_emplace` 失败处（`Use repeat key` 告警，`ACE_LAZY_FOREACH`），不抛异常 |
| 残缺 dataSource 无报错 | `js_lazy_foreach_actuator.h`（注册期不校验四方法，调用期静默降级：缺 totalCount→0、缺 getData→空） |
| `onDatasetChange` 与单条 API 冲突 | `js_data_change_listener.h` 粘性互斥守卫（混用 `ERROR_CODE_PARAM_INVALID`，仅约束 JS 桥接） |
| 同回调 RELOAD 短路其余 op | `lazy_for_each_builder.cpp` `OnDatasetChange`（RELOAD 立即 return，其余 op 失效） |
| ArkTS 无条件注册监听器 vs C-API API26 门控 | `lazy_for_each_node.cpp`（`GetOrCreateLazyForEachNode` vs `CreateLazyForEachNode`） |
| onMove 拖拽排序不可用 | `lazy_for_each_node.cpp` `InitDragManager`（仅 List/Grid 直接父） |

## 调试入口

- 按需生成链路：父容器 `GetFrameChildByIndex` → Node → `LazyForEachBuilder.GetChildByIndex`（三级缓存查找）→ `OnGetChildByIndex` 实构建。
- 预构建链路：`PostIdleTask` → `AddPredictTask`(deadline) → `PreBuild` + `RemovingExpiringItem`。
- 数据变更链路：dataSource → `JSDataChangeListener` 代理 → Node `OnData*` / `OnDatasetChange` → Builder `Operate*` → `PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT` + `MarkNeedSyncRenderTree(true)`。
- 多入口：dynamic（`IsCurrentUseNewPipeline`）/ static（ANI）/ C-API（NodeAdapter）共用 NG `LazyForEachNode` / `LazyForEachBuilder`。

## 相关主题

- [Repeat：[docs/kb/syntax/repeat.md](repeat.md)](repeat.md)
- [渲染控制语法（ForEach / if-else / 共享基类）：[docs/kb/syntax/render-control.md](render-control.md)](render-control.md)
- [NodeAdapter（复用 LazyForEach 管线）：[docs/kb/capabilities/node-adapter.md](../capabilities/node-adapter.md)](../capabilities/node-adapter.md)
- [组件复用框架：[docs/kb/architecture/component-reuse-framework.md](../architecture/component-reuse-framework.md)](../architecture/component-reuse-framework.md)
- [渲染树同步](../architecture/render-tree-sync.md) — LazyForEach 数据变更后 MarkNeedSyncRenderTree 触发渲染树同步