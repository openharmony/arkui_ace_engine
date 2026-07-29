# Component Reuse Framework Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `ComponentReuseFramework`

## 定位

组件复用框架（FuncID `04-19-01`）是 ArkUI **引擎侧 C++ 复用基础设施**，覆盖 UINode 复用生命周期、可复用节点判定、reuseId 节点池、`RecycleDummyNode` 包装与 opt-out，以及 `@since26` 公开复用池 API（`ReusePoolOwnership` / `IReusePool` / `preRender` / `ReusableMemOptStrategy`）。

它与 TS `@Reusable`/`@ReusableV2` 装饰器层（前端层 `07-03-03`）分工：本域管**引擎 C++ 框架**，TS state-mgmt 层管 `@Reusable` 池。注意**引擎 C++ `RecycleManager`（pipeline-owned）≠ TS `RecycleManager`**，两者同名但不同层。具体行为、默认值以源码实现、SDK 声明、测试和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| UINode 复用生命周期 virtual | `frameworks/core/components_ng/base/ui_node.h`、`ui_node.cpp` | `OnRecycle` / `OnReuse`（递归默认实现，子类可覆写）、`IsReusableNode`（四标志 OR）、`AllowReusableV2Descendant`、`ProcessIsInDestroyingForReuseableNode` |
| CustomNodeBase 回调槽与驱动 | `frameworks/core/components_ng/pattern/custom/custom_node_base.h`、`custom_node_base.cpp` | 回调槽、`FireRecycleSelf` / `FireRecycleRenderFunc` / `FireClearAllRecycleFunc`、reuseId、LifeCycleEvent |
| C++ RecycleManager（pipeline-owned） | `frameworks/core/components_ng/pattern/recycle_view/recycle_manager.h`、`recycle_manager.cpp` | 回收期 config 记录 + 复用 replay（静态门面 Push/Pop/Notify） |
| RecycleDummyNode 包装与 opt-out | `frameworks/core/components_ng/pattern/recycle_view/recycle_dummy_node.h`、`recycle_dummy_node.cpp` | 包装可回收 CustomNode、`disableRecycle_` opt-out、析构 `FireRecycleSelf` |
| reuseId 节点池 | `frameworks/core/components_ng/syntax/lazy_for_each_builder.h` | `recyclableNodeSet_` 双层 map、`RecordRecyclableNode` / `ReleaseExpiringNode` |
| 共享基类 | `frameworks/core/components_ng/syntax/for_each_base_node.h` | `ForEachBaseNode::DisableRecycle`（递归 opt-out） |
| Model 门控 | `frameworks/core/components_ng/base/view_partial_update_model_ng.cpp` | CustomNode 构造 + `@ReusableV2` 门控（`AllowReusableV2Descendant`） |
| JS 桥接 / hooks | `frameworks/bridge/declarative_frontend/jsview/js_view.cpp`、`js_view_functions.cpp` | `CreateRecycle` / `TryReleaseExpiringNode`、`__*__Internal` hooks |
| C-API / ANI 命令式复用桥 | `frameworks/core/interfaces/native/implementation/frame_node_extender_accessor.cpp`（Reuse/Recycle）、`frameworks/core/interfaces/native/ani/custom_node_ani_modifier.cpp` | 命令式节点 `OnReuse` / `OnRecycle` |
| 全局复用池（TS-only） | `frameworks/bridge/declarative_frontend/state_mgmt/` 下 `puv2_globalreuse.ts`、`puv2_view_base.ts`、`v2_change_observation.ts` | `__ReusePool__Internal`（TS-only，无 C++ 类）、preRender `setTimeout`、maxCount 同步强制 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| @since26 公开池 API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/customComponent.static.d.ets`、`<OH_ROOT>/interface/sdk-js/api/.../StateManagement.d.ts` | `ReusePoolOwnership`、`@Component/@ComponentV2.reusePool`、`poolAccepts`、`CustomComponentContext.getReusePool`、`IReusePool` / `IReusableInfo` / `preRender`、`ReusableMemOptStrategy` |
| 前端装饰器（07-03-03） | `<OH_ROOT>/interface/sdk-js` 中 `@Reusable` / `@ReusableV2` | TS @Reusable 池（本域仅作边界引用） |

API 检索建议：在 SDK 中搜索 `ReusePoolOwnership`、`IReusePool`、`preRender`、`ReusableMemOptStrategy`、`memoryOptimizationStrategy`。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| UT | `test/unittest/core/pattern/custom/`、`test/unittest/core/pattern/custom_node_ext/` | CustomNodeBase / RecycleManager / CustomNode 复用行为 |
| TS 单测 | state-mgmt 单测（`__ReusePool__Internal` / preRender / maxCount） | 全局池逻辑 |
| XTS | `test/xts` | 端到端复用与内存优化 |
| Spec 功能域 | `specs/04-common-capability/19-component-reuse/01-component-reuse-framework/` | 设计与验收契约 |
| Spec 总索引 | `specs/index.md` | `04-19-01` 功能域注册入口 |

### 相关 Spec

组件复用框架功能域：

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | UINode 复用生命周期与可复用节点判定（基线） | `Feat-01-uinode-reuse-lifecycle-and-reusable-node-judgment-spec.md` |
| Feat-02 | reuseId 节点池与 engine↔TS 桥接 | `Feat-02-reuseid-node-pool-and-engine-ts-bridge-spec.md` |
| Feat-03 | RecycleDummyNode 与 DisableRecycle 机制 | `Feat-03-recycle-dummy-node-and-disable-recycle-spec.md` |
| Feat-04 | 公开复用池 API 与内存优化 @since26 | `Feat-04-public-reuse-pool-api-and-memory-optimization-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 引擎 `RecycleManager` 与 TS `RecycleManager` 混淆 | `recycle_manager.*`（C++ pipeline-owned）vs TS state-mgmt 层；详见 Spec 风险标注 |
| `OnRecycle`/`OnReuse` 是否递归子节点 | `ui_node.cpp`（递归默认实现）+ 子类覆写（如 NodeContainerNode 不递归，详见 05-16-01） |
| 哪些节点可入复用池 | `ui_node.h` `IsReusableNode`（`isCNode_`/`isArkTsFrameNode_`/`isRootBuilderNode_`/`isArkTsRenderNode_` 四标志 OR） |
| Repeat 模板内 `@ReusableV2` 不生效 | `view_partial_update_model_ng.cpp` `AllowReusableV2Descendant` + Repeat `SetAllowReusableV2Descendant(false)` |
| `preRender` / maxCount 行为与 SDK 文档措辞差异 | `puv2_globalreuse.ts`（`setTimeout` / 同步 reject）；详见 Spec Feat-04 风险标注 |
| LazyForEach / Repeat 离屏节点如何入引擎池 | `lazy_for_each_builder.h` `recyclableNodeSet_`；详见 07-05-02 / 07-05-03 |

## 调试入口

- 回收链路：`RecycleDummyNode` 析构 → `FireRecycleSelf` → `UINode::OnRecycle` + `RecycleManager::Push` + TS 回调。
- 复用链路：`FireRecycleRenderFunc` → `RecycleManager::Pop`（replay config）+ re-render + `OnReuse`。
- config 延迟交付：`PipelineContext` → `RecycleManager::NotifyConfigurationChange`。
- DFX：hidump → `CustomNode::DumpInfo` → TS `onDumpInfo` → 全局池 `getDumpInfo`。

## 相关主题

- NodeContainer（复用覆写不调基类）：`docs/kb/components/custom-node/node_container.md`
- LazyForEach：`docs/kb/syntax/lazy_for_each.md`
- Repeat：`docs/kb/syntax/repeat.md`
- 渲染控制语法共享框架：`docs/kb/syntax/render_control.md`
