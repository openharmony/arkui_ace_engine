# UIObserver Context

> 文档版本：v1.0
> 更新时间：2026-07-27
> 来源：`docs/context_registry.json` 主题 `UIObserver`

## 定位

UIObserver（无感监听）是 ArkUI 引擎的 UI 生命周期和状态变化事件监听基础设施，通过 `@ohos.arkui.observer` namespace 和 `UIContext.getUIObserver()` 实例方法提供 Navigation/Router/Scroll/Tab/Gesture/NodeRender 等 23+ on() API 的无感监听注册与通知分发。核心架构为 UIObserverHandler 单例 + HandleFunc 惰性注册 + NAPI/ANI 双桥接路径。

本文档只提供稳定的源码、SDK、测试和 Spec 路由。具体 on/off 语义、枚举值行为、scope 分级应回到当前源码、测试和 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| UIObserverHandler 单例 | `frameworks/core/components_ng/base/observer_handler.h` | 核心分发器；HandleFunc 惰性注册（NAPI func_ + ANI funcForAni_ 双指针）；所有 Info 类型定义（NavDestinationInfo/ScrollEventInfo/RouterPageInfoNG/TabContentInfo 等） |
| UIObserverHandler 实现 | `frameworks/core/components_ng/base/observer_handler.cpp` | Notify*/Get*/SetHandleFunc 实现；双指针分发逻辑 |
| NodeRenderStatusMonitor | `frameworks/core/components_ng/base/node_render_status_monitor.h` | 逐节点渲染状态监听（ABOUT_TO_RENDER_IN/OUT）；最多 64 节点；PipelineContext 懒创建 |
| ScrollerObserverManager | `frameworks/core/components_ng/pattern/scrollable/scroller_observer_manager.h` | Scroll 组件内部事件分发（touch/reach/scroll start/stop/did-scroll） |
| NAPI 桥接 UIObserver | `interfaces/napi/kits/observer/ui_observer.h` | UIObserver 静态类；scoped 监听器存储 map；Register/UnRegister/Handle 方法 |
| NAPI 桥接 ObserverListener | `interfaces/napi/kits/observer/ui_observer_listener.h` | UIObserverListener；封装 napi_ref；On* 回调方法 |
| NAPI 桥接 ObserverProcess | `interfaces/napi/kits/observer/js_ui_observer.h` | ObserverProcess；on/off type 字符串 → Process*Register 分发 |
| NAPI 手势监听 | `interfaces/napi/kits/observer/gesture/gesture_observer.h` | GestureObserver；全局手势监听 AddGlobalGestureListener/RemoveGlobalGestureListener |
| ANI 桥接 UiObserver | `interfaces/ets/ani/observer/src/observer.cpp` | UiObserver 实例（per UIContext）；ANI 路径注册/Handle/分发；ani_ref 回调 |
| ANI ArkTS 定义 | `interfaces/ets/ani/observer/ets/@ohos.arkui.observer.ets` | ArkTS 侧 UIObserver 类定义；native on/off 方法声明 |
| IDL 定义 | `frameworks/bridge/arkts_frontend/arkoala_generator/arkui_extra_idl/arkui-uicontext-uiobserver.idl` | UIObserverGestureEventOps IDL 接口；手势 observer ops |
| Inner API UIEventObserver | `interfaces/inner_api/ace/ui_event_observer.h` | UIEventObserver 抽象接口；外部模块注册/NotifyUIEvent |
| Inner API UIEventFunc | `interfaces/inner_api/ace/ui_event_func.cpp` | UIEventFunc 动态加载 OHOS_ACE_Register/UnregisterUIEventObserver 符号 |
| Adapter UIEvent | `adapter/ohos/entrance/ui_event_impl.cpp` | OHOS 实现；dlopen libha_ace_engine.z.so 注册外部 observer |
| C API NavDestination | `frameworks/core/interfaces/native/node/nav_destination_modifier.h` | NavDestination C API modifier |
| CJ FFI 桥接 | `frameworks/bridge/cj_frontend/interfaces/cj_ffi/observer/observer.h` | CJObserver；Cangjie FFI 桥接（scroll + tab 事件） |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic SDK d.ts | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.observer.d.ts` | uiObserver namespace on/off 函数签名 |
| Static SDK d.ets | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.observer.static.d.ets` | ANI 路径 UIObserver 类 API |
| ANI ArkTS ETS | `interfaces/ets/ani/observer/ets/@ohos.arkui.observer.ets` | ArkTS 侧 UIObserver native 方法声明 |
| C API | `interfaces/native/native_node.h` | NavDestinationInfo query 等 C API 函数声明 |
| IDL | `frameworks/bridge/arkts_frontend/arkoala_generator/arkui_extra_idl/arkui-uicontext-uiobserver.idl` | UIObserverGestureEventOps IDL 接口 |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件/目标路径 | 说明 |
|----------|----------|------------|----------------------------|------|
| NAPI | `interfaces/napi/kits/observer/BUILD.gn` | ace_napi | `napi:ace_napi` | NAPI 绑定层（编译依赖） |
| HiLog | `interfaces/napi/kits/observer/BUILD.gn` | `base/hiviewdfx/hilog` | `hilog:libhilog` | 日志（条件编译 use_hilog） |
| ANI | `interfaces/ets/ani/observer/BUILD.gn` | `arkcompiler/runtime_core` | `runtime_core:ani` | ANI 运行时接口（编译依赖） |
| HA Client（hiviewdfx） | `adapter/ohos/entrance/ui_event_impl.cpp` (dlopen) | `base/hiviewdfx/hiappevent` (推测) | `libha_ace_engine.z.so` | UIEvent 外部 observer 注册；dlopen 动态加载 Register/UnregisterUIEventObserver 符号 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| UIObserverHandler 核心 | `test/unittest/core/base/observer_test_ng.cpp` | 31+ 测试；NavDestinationInfo/ScrollEvent/DensityChange/NavDestinationSwitch/WillClick/DidClick/PanGesture/TextChangeEvent/WindowSizeBreakpoint/GlobalGestureListener |
| Mock ObserverHandler | `test/mock/frameworks/core/components_ng/base/mock_observer_handler.cpp` | Pipeline 测试替身 |
| Swiper Observer | `test/unittest/core/pattern/swiper/swiper_ui_observer_test_ng.cpp` | SwiperContentInfo/GetShownItemInfo |
| C API NavDestination | `test/unittest/capi/modifiers/nav_destination_modifier_test.cpp` | NavDestination C API modifier |
| UIEventFunc/Observer | `test/unittest/interfaces/ui_event_test.cpp` | Register/UnregisterUIEventObserver |
| EventRecorder | `test/unittest/core/common/recorder/event_controller_test.cpp` | EventController（使用 UIEventObserver） |
| NodeRenderStatusMonitor | `test/unittest/core/base/node_render_status_monitor_test_ng.cpp` | 逐节点渲染状态监听 |

### 相关 Spec

无感监听功能域：`specs/04-common-capability/11-component-info/02-observer/`（功能 ID `04-11-02`）。

| 文档 | 稳定路径 | 覆盖范围 |
|------|----------|----------|
| 核心架构规格 | `specs/04-common-capability/11-component-info/02-observer/Feat-01-observer-core-architecture-spec.md` | UIObserverHandler 单例、HandleFunc 惰性注册、NAPI/ANI 双桥接 |
| 全接口覆盖规格 | `specs/04-common-capability/11-component-info/02-observer/Feat-02-observer-api-full-coverage-spec.md` | 23+ on() API 完整接口规格 |
| 设计文档 | `specs/04-common-capability/11-component-info/02-observer/design.md` | 整体架构设计、ADR、调用链分析 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| on() 注册后回调不触发 | UIObserverHandler HandleFunc 惰性注册布尔标志、scoped key 匹配 |
| off() 后回调仍触发 | UIObserverListener 从 scoped map 移除逻辑、instanceId 分区 |
| NavDestinationInfo state 值不符合预期 | NavDestinationState 枚举扩展（10 值 + ON_BACKPRESS=100 跳号） |
| 多 UIContext 监听器互相干扰 | instanceId 分区 key 管理、NAPI static map vs ANI per-instance map |
| NodeRenderState 注册超限（>64） | NodeRenderStatusMonitor MAX_NODE_RENDER_STATE_LISTENERS 限制 |
| 全局手势监听 ANI/NAPI 路径不对称 | UIObserverHandler GlobalGestureListenerStorage static map（ANI 使用独立存储） |
| UIEvent 外部 observer 不注册 | dlopen libha_ace_engine.z.so 加载、OHOS_ACE_RegisterUIEventObserver 符号导出 |

## 调试入口

- UIObserverHandler HandleFunc 断点：SetHandle*Func 惰性注册、Notify* 双指针分发
- NAPI 桥接断点：ObserverProcess::ProcessRegister → UIObserver::Register*Callback
- ANI 桥接断点：UiObserver::Register* → std::call_once HandleFunc 设置
- NodeRenderStatusMonitor 断点：WalkThroughAncestorForStateListener 遍历、IsVisible/IsActive/IsOnMainTree 判定
- UIEventFunc 断点：dlopen/dlsym 符号加载、RegisterUIEventObserver 调用

## 相关主题

- UI 上下文：`docs/kb/capabilities/ui-context.md`（UIContext.getUIObserver() 入口）
- 日志：`docs/kb/architecture/dfx/logging.md`（HiLog 条件编译依赖）
- Trace 打点：`docs/kb/architecture/dfx/trace.md`（UIEventObserver 与 EventRecorder 交叉）
- [UIContext 实例 ID 泄漏](../issues/lifecycle/uicontext-instance-id-leak.md) — JS 前端历史配对问题（已修复）与 UIObserver 实例路由排查