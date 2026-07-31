# XComponent Context

> 文档版本：v1.0
> 更新时间：2026-07-22
> 来源：`docs/context_registry.json` 主题 `XComponent`

## 定位

XComponent 是 ArkUI 的平台类绘制承载组件，为应用提供独立的 Surface/纹理承载环境，常用于视频渲染、相机预览、游戏、自绘制等需要直接对接图形栈的场景。它提供独立的 `XComponentPattern`（含 V2 与多线程派生）、`XComponentController`、`SurfaceHolder`/`InnerSurfaceController` 管理链路，以及面向 NDK 的经典 `OH_NativeXComponent` C API。Spec 功能域归属 `13-platform-components`。

本文档用于快速定位 XComponent 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 生命周期、Surface/纹理挂载、事件 | `frameworks/core/components_ng/pattern/xcomponent/xcomponent_pattern.cpp` | XComponent 核心行为实现入口 |
| Pattern V2 | `frameworks/core/components_ng/pattern/xcomponent/xcomponent_pattern_v2.cpp` | V2 派生 Pattern |
| 多线程 Pattern | `frameworks/core/components_ng/pattern/xcomponent/xcomponent_pattern_multithread.cpp` | 多线程派生 Pattern |
| ArkTS Dynamic Model | `frameworks/core/components_ng/pattern/xcomponent/xcomponent_model_ng.cpp` | 动态前端 XComponent 创建和属性写入入口 |
| ArkTS Static Model | `frameworks/core/components_ng/pattern/xcomponent/xcomponent_model_static.cpp` | 静态前端 XComponent 创建入口 |
| 控制器（NG） | `frameworks/core/components_ng/pattern/xcomponent/xcomponent_controller_ng.cpp` | XComponentController NG 实现 |
| 内部 Surface 控制器 | `frameworks/core/components_ng/pattern/xcomponent/xcomponent_inner_surface_controller.cpp` | 内部 Surface 生命周期管理 |
| Surface Holder | `frameworks/core/components_ng/pattern/xcomponent/xcomponent_surface_holder.h` | Surface 持有/配置抽象 |
| 属性存储 | `frameworks/core/components_ng/pattern/xcomponent/xcomponent_layout_property.h` | XComponent 布局属性声明 |
| 布局算法 | `frameworks/core/components_ng/pattern/xcomponent/xcomponent_layout_algorithm.cpp` | XComponent 测量与布局 |
| 绘制 | `frameworks/core/components_ng/pattern/xcomponent/xcomponent_paint_method.cpp` | XComponent 绘制入口 |
| 事件存储 | `frameworks/core/components_ng/pattern/xcomponent/xcomponent_event_hub.h` | XComponent 事件回调存储 |
| 无障碍 | `frameworks/core/components_ng/pattern/xcomponent/xcomponent_accessibility_provider.cpp` | XComponent 无障碍 Provider |
| C API 枚举 | `interfaces/native/native_node.h` | `ARKUI_NODE_XCOMPONENT`、`NODE_XCOMPONENT_*` 属性枚举 |
| 经典 NDK | `interfaces/native/native_interface_xcomponent.h` | `OH_NativeXComponent` 经典 C API（`@since 8`） |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/x_component.d.ts` | 动态 ArkTS XComponent 声明（路径以 SDK 仓实际为准） |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/xComponent.static.d.ets` | 静态 ArkTS XComponent 声明（路径以 SDK 仓实际为准） |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/XComponentModifier.d.ts` | 动态 Modifier 声明（路径以 SDK 仓实际为准） |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/XComponentModifier.static.d.ets` | 静态 Modifier 声明（路径以 SDK 仓实际为准） |
| 经典 NDK（OH_NativeXComponent） | `interfaces/native/native_interface_xcomponent.h` | 面向 NDK 的 `OH_NativeXComponent` C API |
| Node C API / NDK | `interfaces/native/native_node.h` | `ARKUI_NODE_XCOMPONENT`、`NODE_XCOMPONENT_*` 节点属性枚举 |

> SDK `.d.ts` / `.d.ets` 声明位于 `interface/sdk-js` 仓（ace_engine 仓内不持有），上述路径为命名约定，落地以 SDK 仓实际文件为准。

API 检索建议：

- 属性声明：在 SDK 文件中搜索 `XComponentInterface`、`XComponentAttribute` 或 `XComponent(`。
- 经典 NDK：在 `native_interface_xcomponent.h` 中搜索 `OH_NativeXComponent_GetXComponentId`、`OH_NativeXComponent_GetSurface`、`OH_NativeXComponent_RegisterCallback`。
- Node C API：在 `interfaces/native/native_node.h` 中搜索 `NODE_XCOMPONENT_`。

### API 解析实现路径

XComponent **尚未完成组件化改造**：无 `pattern/xcomponent/bridge/` 子目录、无独立 `libarkui_xcomponent.z.so`，属性解析采用 JSView + node_modifier 双路径，编译产物在主 `libace_compatible.z.so` 中。`declarative_frontend` 下无独立 `arkts_native_xcomponent_bridge`。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| **JSView（声明式组件）** | `frameworks/bridge/declarative_frontend/jsview/js_xcomponent.cpp` | `JSXComponent::SetXxx()` → `XComponentModel::GetInstance()->SetXxx()` |
| **JSView 控制器** | `frameworks/bridge/declarative_frontend/jsview/js_xcomponent_controller.h` | `JSXComponentController` 控制器声明 |
| **node_modifier 层** | `frameworks/core/interfaces/native/node/node_xcomponent_modifier.cpp` | C++ 属性 Set/Reset/Get，由 C API 共用 |
| **C API（NDK 节点）** | `interfaces/native/native_node.h`、`frameworks/core/interfaces/native/node/node_xcomponent_modifier.cpp` | `ARKUI_NODE_XCOMPONENT`、`NODE_XCOMPONENT_*` 属性分发 |
| **经典 NDK（OH_NativeXComponent）** | `interfaces/native/native_interface_xcomponent.h`、`interfaces/native/native_interface_xcomponent.cpp` | `OH_NativeXComponent_*` C API，独立于节点 C API 的经典入口 |
| **前端 Modifier（ArkTS 侧）** | `frameworks/bridge/declarative_frontend/ark_modifier/src/xcomponent_modifier.ts` | ArkTS `XComponentModifier` 类定义 |
| **Legacy JS 前端 Bridge** | `frameworks/bridge/js_frontend/engine/jsi/jsi_xcomponent_bridge.cpp` | JS 前端（legacy）XComponent 桥接 |

组件化改造参考：`./组件化重构通用方案.md`。改造后上述 JSView 和 Modifier 路径将统一到 `pattern/xcomponent/bridge/arkts_native_xcomponent_bridge.cpp`，并输出独立 so。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/xcomponent/` | Pattern、属性、布局、V2、多线程、HDR、刷新率、控制器、native interface 等 XComponent 行为回归 |
| C API 测试 | `test/unittest/capi/accessors/xcomponent_controller_accessor_test.cpp` | XComponentController accessor（当前在该目录 BUILD.gn 中处于注释禁用状态，未编入） |
| Context registry | `docs/context_registry.json` | XComponent 的 KB、Spec、源码、API、测试统一路由 |

### 相关 Spec

XComponent 功能域：`specs/05-ui-components/13-platform-components/01-xcomponent/`（功能 ID `05-13-01`，当前 spec_status `pending`：已在 registry 注册，但目录与 Feat 规格尚未创建）。

NDK 侧独立功能域：`specs/08-ndk/02-xcomponent-c-api/01-native-xcomponent/`（功能 ID `08-02-01`，spec_status `pending`）。

功能域尚未落地任何 `design.md` 或 `Feat-NN-*-spec.md`。行为结论在 Spec 补齐前应以源码、SDK 声明和测试为事实源。

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Surface 不创建或内容不显示 | `xcomponent_pattern.cpp` 生命周期、`xcomponent_inner_surface_controller.cpp`、`xcomponent_surface_holder.h`、Model 创建入口 |
| V2 / 多线程场景异常 | `xcomponent_pattern_v2.cpp`、`xcomponent_pattern_multithread.cpp` |
| 控制器接口失效 | `xcomponent_controller_ng.cpp`、`inner_xcomponent_controller.h`、`js_xcomponent_controller.h` |
| NDK `OH_NativeXComponent` 回调不触发 | `native_interface_xcomponent.h`、`native_interface_xcomponent.cpp` 回调注册链 |
| 节点 C API 属性不生效 | `node_xcomponent_modifier.cpp`、`native_node.h` 中 `NODE_XCOMPONENT_*` 枚举 |
| 布局/尺寸异常 | `xcomponent_layout_algorithm.cpp`、`xcomponent_layout_property.h` |
| 无障碍桥接异常 | `xcomponent_accessibility_provider.cpp`、`xcomponent_accessibility_session_adapter.cpp` |
| Dynamic 与 Static 表现不一致 | 分别核对 `xcomponent_model_ng.cpp` 与 `xcomponent_model_static.cpp` |

## 调试入口

- 创建链路：从 `XComponentModelNG` 确认节点以 `XComponentPattern`（或 V2/多线程派生）创建，并追踪 Surface/纹理承载建立。
- Surface 链路：从 `xcomponent_inner_surface_controller.cpp`、`xcomponent_surface_holder.h` 追踪 Surface 生命周期与配置。
- 属性链路：从 SDK 属性名定位 JSView 写入或 `node_xcomponent_modifier.cpp` 的 Set/Reset/Get。
- NDK 链路：从 `OH_NativeXComponent_RegisterCallback` 追踪经典 NDK 回调注册与派发。
- 回归验证：运行 `test/unittest/core/pattern/xcomponent/` 下的测试用例。

## 相关主题

- Image：`docs/kb/components/media/image.md`
- ImageAnimator：`docs/kb/components/media/image_animator.md`
- API 范式：`docs/api/ArkUI_API_Paradigm_Knowledge_Base_CN.md`
