# Inspector Layout Callback Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `InspectorLayoutCallback`

## 定位

Inspector 布局回调是 ArkUI 通过 `@ohos.arkui.inspector` 模块的 `createComponentObserver(id)` 返回 `ComponentObserver`，对其 `on("layout"|"layoutDraw"|"draw"|"drawChildren"|...)` 注册的逐组件布局/绘制事件回调。注册经 NAPI `ComponentObserver` → `JsEngine::RegisterLayoutInspectorCallback`（按 componentId 或 uniqueId），在声明式/NG 前端布局/绘制完成时触发。它区别于 `@ohos.arkui.observer`（04-11-02）的全局无感监听与 NDK 节点布局回调。

本文档只提供稳定的源码、SDK、测试和 Spec 路由。具体回调类型枚举、触发时机、scope 以 SDK 声明、源码和测试为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| NAPI 注册入口 | `interfaces/napi/kits/inspector/js_inspector.cpp` | `JSCreateComponentObserver` 创建 `ComponentObserver` 并 `RegisterLayoutInspectorCallback`（componentId/uniqueId 两路）；`ComponentObserver::Destroy` 注销 |
| ComponentObserver 声明 | `interfaces/napi/kits/inspector/js_inspector.h` | `ComponentObserver` 类；`CalloutType` 枚举（LAYOUT/DRAW/DRAWCHILDREN/.../LAYOUTCHILDREN）；`cbLayoutList_/cbDrawList_/...` napi_ref 列表 |
| JsEngine 抽象接口 | `frameworks/bridge/js_frontend/engine/common/js_engine.h` | `RegisterLayoutInspectorCallback`/`Unregister`（string id 与 uniqueId 两套）、`LayoutInspectorCallback(uniqueId)` |
| JsEngine 分发实现 | `frameworks/bridge/js_frontend/engine/common/js_engine.cpp` | `LayoutInspectorCallback`、`Register/UnregisterLayoutInspectorCallback` 实现 |
| 声明式触发点 | `frameworks/bridge/declarative_frontend/declarative_frontend.cpp` | `jsEngine->LayoutInspectorCallback(componentId)`/`(uniqueId)` 触发 |
| NG 声明式触发 | `frameworks/bridge/declarative_frontend/ng/declarative_frontend_ng.cpp` | 触发 + `delegate_->SetLayoutInspectorCallback(...)` |
| NG 委托存储 | `frameworks/bridge/declarative_frontend/ng/frontend_delegate_declarative_ng.cpp` | `SetLayoutInspectorCallback` 实现 + `layoutInspectorCallback_` 成员 |
| 回调类型定义 | `frameworks/bridge/js_frontend/frontend_delegate_impl.h` | `using LayoutInspectorCallback = std::function<void(const std::string&)>`、`LayoutInspectorUniqueIdCallback` |
| 静态 ArkTS 前端 | `frameworks/bridge/arkts_frontend/arkts_frontend.cpp` | `Register/UnregisterLayoutInspectorCallback`（id 与 uniqueId）、`layoutCallbacks_/uniqueIdLayoutCallbacks_` map |
| ANI ComponentObserver | `interfaces/ets/ani/inspector/src/inspector.cpp` | `CreateComponentObserverForAni`/`DeleteComponentObserver`（静态路径观察者生命周期） |
| ANI ArkTS 定义 | `interfaces/ets/ani/inspector/ets/@ohos.arkui.inspector.ets` | `ComponentObserver` 类 `onLayout/offLayout/onDraw/...` native 声明 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic SDK d.ts | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.inspector.d.ts` | `createComponentObserver`、`ComponentObserver.on("layout"\|...)` 声明（路径以 SDK 仓实际为准） |
| Static SDK d.ets | `<OH_ROOT>/interface/sdk-js/api/arkui/inspector.static.d.ets` | 静态 ArkTS `ComponentObserver` 声明（路径以 SDK 仓实际为准） |
| NAPI 模块 | `interfaces/napi/kits/inspector/js_inspector.cpp` | 模块名 `arkui.inspector`，`createComponentObserver` 为唯一导出 |
| ANI 模块 | `interfaces/ets/ani/inspector/src/inspector.cpp` | 静态 `ComponentObserver` 原生绑定 |
| C API / NDK | 无 | 无独立 C-API；NDK 节点布局回调是另一套（`OH_ArkUI_RegisterLayoutCallbackOnNodeHandle`，见下） |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件/目标路径 | 说明 |
|----------|----------|------------|----------------------------|------|
| NAPI 模块 | `interfaces/napi/kits/inspector/BUILD.gn`（`deps += ["napi_$platform"]`） | `<OH_ROOT>/foundation/arkui/napi` | `napi:ace_napi` | `createComponentObserver` 注册入口，NAPI 绑定层 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| Inspector 核心（含 GetRectangleById） | `test/unittest/core/base/inspector_test_ng.cpp` | NG Inspector 行为回归 |
| SimplifiedInspector | `test/unittest/core/base/simplified_inspector_test_ng.cpp` | 异步采集回归 |
| LayoutInspector 平台测试 | `test/unittest/adapter/ohos/entrance/layout_inspector_test.cpp` | 平台调度层回归 |

> 说明：仓内未见针对 `js_inspector.cpp` 的 `createComponentObserver`/布局回调注册路径的专属 NAPI 单测；建议结合 DevEco/自动化场景验证。

### 相关 Spec

布局回调（inspector）功能域：`specs/04-common-capability/11-component-info/03-inspector-layout-callback/`（功能 ID `04-11-03`，当前 spec_status `pending`：已在 registry 注册，但目录与 Feat 规格尚未创建）。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| `on("layout")` 回调不触发 | `RegisterLayoutInspectorCallback` 的 componentId/uniqueId 分路、`ComponentObserver` 生命周期（`Destroy` 注销时机）、napi_ref 列表 |
| off 后仍触发 | `UnregisterLayoutInspectorCallback` 从 map 移除、`cbLayoutList_` 清理 |
| 静态前端回调丢失 | `arkts_frontend` 的 `layoutCallbacks_/uniqueIdLayoutCallbacks_` map 注册与分发 |
| 与 UIObserver 布局回调混淆 | 本回调是 per-component（`createComponentObserver(id)`）；UIObserver（04-11-02）是全局无感监听 `UIObserver.on("scroll"\|...)` |
| 与 NDK 节点布局回调混淆 | NDK 走 `OH_ArkUI_RegisterLayoutCallbackOnNodeHandle`→`EventHub::SetNDKLayoutCallback`，非 inspector 路径 |
| 与 DFX `LayoutInspector` 混淆 | `frameworks/core/common/layout_inspector.h` 是 DevEco 状态/profiler 工具，非本布局回调 |

## 调试入口

- 注册链路断点：`JSCreateComponentObserver`（js_inspector.cpp）→ `jsEngine->RegisterLayoutInspectorCallback`
- 分发链路断点：`JsEngine::LayoutInspectorCallback`（js_engine.cpp）→ 声明式/NG 触发点
- 回调类型断点：`ComponentObserver` 的 `CalloutType` 分发与各 `cb*List_` 触发
- 静态前端断点：`arkts_frontend.cpp` 的 `Register/Unregister` 与 map 查找

## 相关主题

- 组件树 Inspector：`docs/kb/capabilities/inspector.md`（同属 `@ohos.arkui.inspector` 模块）
- 无感监听：`docs/kb/capabilities/ui-observer.md`（sibling 04-11-02，全局 observer）
