# State Management — C++ 绑定与宿主节点 Context

> 文档版本：v1.0
> 更新时间：2026-07-13
> 来源：`docs/context_registry.json` 主题 `StateMgmtCppBindings`

## 定位

C++ 绑定层是状态管理 TS 库（`stateMgmt.abc`）与 ArkUI 引擎之间的双向桥接，仅服务于**动态前端**（declarative_frontend / ArkTS1.1）。TS→C++ 通过 `JSBind` 注册的全局对象（`NativeViewPartialUpdate`、`ViewStackProcessor`、`NativeLocalStorage`、`Storage`、`EnvironmentSetting`、`StateMgmtProfiler` 等）；C++→TS 通过 `CallStateMgmt*` 系列反向调用（空闲清理、状态信息查询）。关键设计：**V1 和 V2 共用同一个 C++ 后端**（`JSViewPartialUpdate` → `CustomNode`），仅通过 `isV2_` 标志区分。V2 的响应式装饰器是纯 TS 实现，C++ 不参与 V2 的观察逻辑。宿主节点 `CustomNode` 是 `@Component`/`@ComponentV2` 在 C++ 侧的承载者，`ElementRegister` 负责全局 elmtId 分配与回收跟踪，`ViewStackProcessor` 管理组件创建栈。

本文档用于快速定位 C++ 绑定相关源码和测试入口。TS 侧的状态管理实现见其他子页面。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 字节码载入 | `frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.cpp` | `_binary_stateMgmt_abc_start` — 引擎初始化时注入 `stateMgmt.abc` |
| C++→TS 反向调用 | `frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.cpp` | `CallStateMgmtCleanUpIdleTaskFunc`（空闲清理）、`CallGetStateMgmtInfo`（状态查询）、`OpenStateMgmtInterop` |
| NG 视图绑定聚合 | `frameworks/bridge/declarative_frontend/engine/jsi/jsi_view_register_impl_ng.cpp` | `JsBindViews` — 聚合 ViewStackProcessor、NativeView*、LocalStorage、Profiler、Storage、Environment 绑定 |
| V1+V2 共享视图后端 | `frameworks/bridge/declarative_frontend/jsview/js_view.cpp`、`js_view.h` | `JSViewPartialUpdate::JSBind`（"NativeViewPartialUpdate"）、`isV2_` 区分标志 |
| 生命周期分发核心 | `frameworks/bridge/declarative_frontend/jsview/js_view_functions.h`、`.cpp` | `ViewFunctions`（约 40 个 `JSWeak<JSFunc>`）、`InitViewFunctions`、`ExecuteRender`/`ExecuteRerender`/`ExecuteAboutToBeDeleted`/`ExecuteRecycle`/`ExecuteAboutToReuse`/`ExecuteSetActive`/`ExecuteOnDumpInfo` |
| ViewStackProcessor 绑定 | `frameworks/bridge/declarative_frontend/jsview/js_view_stack_processor.cpp` | `JSViewStackProcessor::JSBind` — elmtId 分配、accessRecording |
| LocalStorage 绑定 | `frameworks/bridge/declarative_frontend/jsview/js_local_storage.cpp`、`.h` | `JSLocalStorage`（`storages_` 为 thread_local，按 containerId 多实例） |
| PersistentStorage 绑定 | `frameworks/bridge/declarative_frontend/jsview/js_persistent.cpp`、`.h` | `JSPersistent::JSBind`（"Storage"）→ `StorageProxy` |
| Environment 绑定 | `frameworks/bridge/declarative_frontend/jsview/js_environment.cpp`、`.h` | `JSEnvironment::JSBind`（"EnvironmentSetting"）— V1 设备环境 |
| Profiler 绑定（V1 遗留） | `frameworks/bridge/declarative_frontend/jsview/js_state_mgmt_profiler.cpp`、`.h` | `JSStateMgmtProfiler : public AceType` |
| Histogram 绑定 | `frameworks/bridge/declarative_frontend/jsview/js_state_mgmt_histogram.cpp`、`.h` | `JSStateMgmtHistogram` |
| 自定义节点宿主 | `frameworks/core/components_ng/pattern/custom/custom_node.cpp`、`.h` | `CustomNode`（多继承 `UINode` + `CustomNodeBase`）— `@Component`/`@ComponentV2` 宿主，`Render(deadline)` 支持多帧预建 |
| 宿主基类 | `frameworks/core/components_ng/pattern/custom/custom_node_base.cpp`、`.h` | `CustomNodeBase` + `isV2_` — 约 20 个 `std::function` 生命周期回调、`reusableMemOptStrategy_`、析构保证 appear/destroy 配对 |
| 自定义节点 Pattern | `frameworks/core/components_ng/pattern/custom/custom_node_pattern.cpp`、`.h` | `CustomNodePattern : public Pattern` |
| 自定义节点布局 | `frameworks/core/components_ng/pattern/custom/custom_node_layout_algorithm.h`、`custom_node_static.*` | 自定义节点布局算法与静态变体 |
| 视图创建桥接 | `frameworks/core/components_ng/base/view_partial_update_model_ng.cpp` | `ViewPartialUpdateModelNG::CreateNode` — `JSViewPartialUpdate` ↔ `CustomNode` 桥 |
| 元素注册表 | `frameworks/core/pipeline/base/element_register.cpp`、`.h` | `ElementRegister`（pimpl `ElementRegisterImpl`）— 全局 elmtId→UINode 映射、`MakeUniqueId`、`RemoveItem`/`RemoveItemSilently`、移除集 |
| 视图栈处理器 | `frameworks/core/components_ng/base/view_stack_processor.cpp`、`.h` | `ViewStackProcessor`（`elementsStack_`）、`ScopedViewStackProcessor`（RAII 线程局部实例切换）、`InteropViewStackProcessor` |
| 管线集成 | `frameworks/core/pipeline_ng/pipeline_context.cpp` | `OnIdle`、`CallStateMgmtCleanUpIdleTaskFunc`、`GetStateMgmtInfo`、`RecordStateMgmtNode`、`MAX_FRAME_COUNT_WITHOUT_JS_UNREGISTRATION = 100` |
| Frontend 反向调用接口 | `frameworks/core/common/frontend.h` | `CallStateMgmtCleanUpIdleTaskFunc`、`CallGetStateMgmtInfo`、`OpenStateMgmtInterop` 虚函数声明 |
| 性能监控 | `frameworks/base/log/ace_performance_monitor.h` | `RecordStateMgmtNode(count)`、`stateMgmtNodeNum_` |

### 关键机制锚点

| 机制 | 源码位置 |
|------|----------|
| `stateMgmt.abc` 载入时机 | `jsi_declarative_engine.cpp` 引擎初始化阶段 |
| 反向调用 JS 函数缓存 | `uiNodeCleanUpIdleFunc_`/`getStateMgmtInfoFunc_` 首次调用时缓存 |
| 已删除元素全链路同步 | C++ `ElementRegister::RemoveItem` 加移除集 → TS `ViewStackProcessor.moveDeletedElmtIds` → `UINodeRegisterProxy.unregisterElmtIdsFromIViews` |
| `ViewFunctions` 生命周期分发 | `js_view_functions.cpp` `InitViewFunctions`、`ExecuteRender`、`ExecuteRerender`、`ExecuteAboutToBeDeleted`、`ExecuteRecycle`、`ExecuteAboutToReuse`、`ExecuteSetActive`、`ExecuteOnDumpInfo` |
| 析构 appear/destroy 配对 | `custom_node_base.cpp` `~CustomNodeBase` — 若 appear 未触发则补触发 `appearFunc_` |
| `RemoveItem` vs `RemoveItemSilently` | 前者加入移除集（供 TS 同步），后者跳过（用于复用重注册） |
| V1/V2 共用后端的差异点 | `js_view.h` `isV2_` — V2 专属：`AllowReusableV2Descendant`、内存优化、复用语义 |
| `JSLocalStorage.storages_` thread_local | 多容器（多实例/卡片）各自维护 containerId→Storage |
| CustomNode↔TSView 双向弱引用 | TS 持有 NativeViewPartialUpdate → CustomNode；CustomNode 的 `std::function` 持有 TS 闭包弱引用 |
| Inspector dump 数据流转 | `CustomNode::DumpInfo` → TS `onDumpInspector` → JSON → C++ `DumpDecoratorInfo` 解析 |
| 复用时 CustomNode 行为 | `FireRecycleSelf`（交 RecycleManager）、`FireOnReuseFunc` + `FireRecycleRenderFunc`（重置） |
| 强制清理阈值 | `MAX_FRAME_COUNT_WITHOUT_JS_UNREGISTRATION = 100`（`pipeline_context.cpp`）防 JS 侧 OOM |

### API 入口

C++ 绑定层为引擎内部接口，不对外暴露 SDK 声明。状态管理对外 API 全部经 TS 装饰器与 `@ohos.arkui.StateManagement` 模块（见总览）。

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| NAPI / Dynamic / Static / CAPI | 不涉及 | C++ 绑定是内部 JSI 层，无独立对外 API |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 间接覆盖 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/v1_tests/`、`v2_tests/`、`common_tests/` | C++ 绑定经 V1/V2 组件测试间接覆盖 |
| Context registry | `docs/context_registry.json` | 主题 `StateMgmtCppBindings` |

### 相关 Spec

| FuncID | Spec 域 | 状态 |
|--------|---------|------|
| `07-02-01` | `specs/07-frontend/02-state-management/01-v1-component-state` | Baselined（Feat-09 elmtId 同步与 C++ 宿主集成） |
## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| V1/V2 共用 backend 的差异点 | 全部由 `isV2_` 控制（`js_view.h`）；V2 专属 `AllowReusableV2Descendant`、内存优化、复用语义 |
| `moveDeletedElmtIds` 同步原理 | C++ `ElementRegister::RemoveItem` 加移除集 → TS 取出 → `unregisterElmtIdsFromIViews` |
| `stateMgmt.abc` 何时载入 | 引擎初始化阶段（`jsi_declarative_engine.cpp`） |
| `JSLocalStorage.storages_` 为何 thread_local | 多容器（多实例/卡片）各自维护 containerId→Storage |
| CustomNode 与 PUV2ViewBase 谁持有谁 | 双向弱引用，详见「关键机制锚点」 |
| Inspector dump 数据流转 | `CustomNode::DumpInfo` → TS `onDumpInspector` → JSON → C++ 解析 |
| 复用时 CustomNode 发生什么 | `FireRecycleSelf` 交池；复用 `FireOnReuseFunc` + `FireRecycleRenderFunc` 重置 |
| JS 侧 OOM / elmtId 泄漏 | `MAX_FRAME_COUNT_WITHOUT_JS_UNREGISTRATION = 100` 强制清理；检查 `RemoveItem`/`RemoveItemSilently` 用法 |
| `JSStateMgmtProfiler` vs `stateMgmtProfiler` | 前者 V1 遗留 C++ 类，后者现代注入式（经 `JsStateProfilerResgiter`） |
| `NOT_IMPLEMENT` BusinessError | 静态运行时未注册 Interop 回调（见 Interop 子页面） |

## 调试入口

- **hidump**：`hidumper -s WindowManagerService -a "-dumpAll -r"`、`-viewHierarchy`、`-stateVariables -viewId=N`、`-dirtyElementIds`、`-inactiveComponents`、`-profiler`、`RecyclePool`。
- **dump 入口**：`CustomNode::DumpInfo`（C++）↔ `onDumpInspector`（TS）。
- **断点建议**：`CallStateMgmtCleanUpIdleTaskFunc`、`CallGetStateMgmtInfo`、`CustomNode::Render`、`ElementRegister::RemoveItem`/`MakeUniqueId`、`ViewStackProcessor` 栈操作。
- **反向调用排查**：确认 `uiNodeCleanUpIdleFunc_`/`getStateMgmtInfoFunc_` 是否已缓存（首次调用后才建立）。

## 相关主题

- 总览：`docs/kb/frontend/state-management.md`
- 基础设施（TS 侧 `UINodeRegisterProxy`/`stateMgmtProfiler`）：`docs/kb/frontend/state_management/infrastructure.md`
- [自定义组件机制（`CustomNode` 生命周期/复用）：`docs/kb/frontend/state_management/custom-component.md`](custom-component.md)
- V1/V2 核心：`docs/kb/frontend/state_management/v1-core.md`、`v2-core.md`
- 存储体系（`JSLocalStorage`/`JSPersistent`/`JSEnvironment`）：`docs/kb/frontend/state_management/storage.md`
- Interop 桥接（动态/静态前端互操作）：`docs/kb/frontend/state_management/interop-bridge.md`