# 基础属性 Context

> 文档版本：v4.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `basic-attributes`

## 定位

基础属性是所有 ArkUI 组件共享的通用属性集合，归属 Func-04-03-03，覆盖组件标识与显隐、背景设置、渲染与复用、浮层和焦点属性。它连接应用侧 Common API、前端参数解析和 ViewAbstract 属性写入；不同属性族分别进入 UINode/ElementRegister、LayoutProperty、RenderContext、FrameNode 子节点或 FocusHub，并非全部由同一状态链路消费。backdropBlur 与 backgroundImage 系属性分别跨域出现在视效属性（Func-04-03-02）和背景图片通用属性（Func-04-03-10）；stateStyles 与 attributeModifier 归属样式属性域（Func-04-03-07）。

本页仅提供路由入口，属性语义、API 版本、边界条件和兼容性应以当前 SDK、源码、测试及 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| NG 公共属性写入 | `frameworks/core/components_ng/base/view_abstract.cpp`、`frameworks/core/components_ng/base/view_abstract_model_ng.cpp` | id/visibility/zIndex/obscured/backgroundColor/backgroundImage/overlay/renderGroup/freeze/focusBox 等动态版写入入口 |
| Static 公共属性写入 | `frameworks/core/components_ng/base/view_abstract_model_static.cpp` | 静态 ArkTS 基础属性写入入口 |
| 渲染属性承载 | `frameworks/core/components_ng/render/render_context.h`、`frameworks/core/components_ng/render/render_context.cpp` | visibility/zIndex/obscured/backgroundColor/blur/brightness/freeze/renderGroup 等属性存储与回调 |
| 布局属性（visibility） | `frameworks/core/components_ng/layout/layout_property.h`、`frameworks/core/components_ng/layout/layout_property.cpp` | visibility 进入布局约束的存储入口；不要将 visibility 误判为仅由 RenderContext 消费 |
| id 查找与注册 | `frameworks/core/pipeline/base/element_register.h` | ElementRegister inspectorIdMap_ 存储 id → FrameNode 映射 |
| FrameNode 属性存储 | `frameworks/core/components_ng/base/frame_node.h`、`frameworks/core/components_ng/base/frame_node.cpp` | renderGroup/reuseId/id/uniqueId/restoreId 存储；overlayNode_/background(CustomBuilder) 子节点挂载 |
| 焦点属性 | `frameworks/core/components_ng/event/focus_hub.h`、`frameworks/core/components_ng/event/focus_hub.cpp` | FocusHub：focusable/tabIndex/defaultFocus/focusScopeId 等存储与判断；nextFocus/onFocus/onBlur/onKeyEvent 焦点导航与事件分发 |
| reuseId 组件复用 | `frameworks/core/components_ng/base/inspector/filter_declaration.cpp` | 回收池匹配 |
| Rosen 渲染适配 | `frameworks/core/components_ng/render/adapter/rosen_render_context.cpp` | 基础属性到 RSNode 的适配入口 |
| Dynamic JSView 解析 | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | Common 属性的声明式 JS/ArkTS 动态参数解析入口 |
| ArkTS Common Bridge | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.cpp` | AttributeModifier 和 FrameNode 动态属性解析入口 |
| Common node modifier | `frameworks/core/interfaces/native/node/node_common_modifier.cpp` | Common Bridge 到 ViewAbstract/ModelNG 的 native 属性入口 |
| Static Common modifier | `frameworks/core/interfaces/native/implementation/common_method_modifier.cpp` | Static ArkTS Common 属性的类型转换及 ViewAbstract/Static Model 写入入口 |
| Native 属性分发 | `interfaces/native/node/style_modifier.cpp`、`interfaces/native/native_node.h` | Node C API 通用属性枚举与分发入口；按具体属性枚举确认公开范围 |

按属性族检索：

| 属性族 | 建议检索词 |
|--------|------------|
| 组件标识 | `SetId`、`inspectorIdMap_`、`uniqueId`、`restoreId`、`inspectorLabel` |
| 显隐与层级 | `Visibility`、`VisibleType`、`SetZIndex`、`ObscuredReasons` |
| 背景设置 | `BackgroundColor`、`BackgroundImage`、`BackgroundBlurStyle`、`BackdropBlur`、`BackgroundEffect`、`BackgroundBrightness` |
| 渲染与复用 | `RenderGroup`、`RenderFit`、`Freeze`、`UseEffect`、`ReuseId`、`ExcludeFromRenderGroup` |
| 浮层 | `Overlay`、`OverlayOptions`、`overlayNode_` |
| 焦点 | `Focusable`、`TabIndex`、`DefaultFocus`、`FocusScopeId`、`NextFocus`、`FocusBox`、`FocusHub` |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic Common API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | CommonAttribute 中的标识、显隐、背景、渲染、浮层和焦点属性声明 |
| Static Common API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | 静态 ArkTS Common 属性声明 |
| Dynamic Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.d.ts` | Dynamic Modifier 类型入口；具体基础属性声明仍需回到 CommonAttribute 核实 |
| Static Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.static.d.ets` | Static Modifier 类型入口 |
| Node C API | `interfaces/native/native_node.h`、`interfaces/native/node/style_modifier.cpp` | 公开通用属性枚举及设置、重置、查询分发；逐属性确认是否公开 |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|-----------|-------------------------------|------|
| 图形渲染 | `frameworks/core/components_ng/render/adapter/rosen_render_context.cpp` | `graphic_2d` | `render_service_client/core/ui/rs_node.h`、`render_service_base/include/property/rs_properties_def.h` | 基础属性渲染通过 RSNode 下发 |
| 图片框架 | `frameworks/core/components_ng/image_provider/image_loading_context.h`、`adapter/ohos/osal/pixel_map_ohos.h` | `multimedia_image_framework` | `interfaces/innerkits/include/Media::PixelMap` | backgroundImage 解码链路 |
| 窗口管理 | `frameworks/core/components_ng/event/focus_hub.cpp` | `window_manager` | Subwindow 焦点路由 | 焦点管理与 UIExtension 焦点路由 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|---------|------|
| ViewAbstract 测试 | `test/unittest/core/base/` | 按 `ViewAbstract` 和具体属性名检索公共属性写入测试 |
| 焦点属性测试 | `test/unittest/core/event/` | FocusHub 焦点导航与事件分发测试 |
| Common C modifier 测试 | `test/unittest/capi/modifiers/` | 按 `common_method_modifier` 和具体属性名检索 native modifier 回归 |
| Context registry | `docs/context_registry.json` | `basic-attributes` 的 KB、Spec、源码、API 和测试统一路由 |

### 相关 Spec

基础属性功能域：`specs/04-common-capability/03-common-attributes/03-basic-attributes/`（功能 ID `04-03-03`）。

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | 组件标识与显隐 | `Feat-01-component-id-visibility-spec.md` |
| Feat-02 | 背景设置 | `Feat-02-background-setting-spec.md` |
| Feat-03 | 渲染与复用 | `Feat-03-render-reuse-spec.md` |
| Feat-04 | 浮层 | `Feat-04-overlay-spec.md` |
| Feat-05 | 焦点属性 | `Feat-05-focus-attribute-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| id 注册与查找异常 | `element_register.h` — inspectorIdMap_；SDK id 声明 |
| visibility 各值布局差异 | `layout_property.h` — visibility 进入 LayoutProperty 约束链路；`render_context.h` |
| obscured 截图/录屏区域屏蔽 | `render_context.h` |
| background(CustomBuilder) 与 backgroundColor 双机制 | `view_abstract.cpp`、`frame_node.cpp` — 区分 RenderContext 存储 vs 子节点挂载 |
| 模糊属性互斥覆盖 | `render_context.h` — backdropBlur/backgroundBlurStyle/backgroundEffect 共享存储位 |
| backgroundColor 资源解析 | `render_context.h` |
| freeze 与 SetNodeFreeze 区别 | `render_context.h` — UpdateFreeze vs `frame_node.cpp` — SetNodeFreeze |
| renderGroup 子树脏聚合 | `frame_node.cpp` |
| excludeFromRenderGroup 排除子树 | `view_abstract.cpp` |
| reuseId 组件复用 | `filter_declaration.cpp` |
| overlay 多次调用或重置 | `view_abstract.cpp` — SetOverlay |
| focusable 默认值因组件类型不同 | `focus_hub.h` — 各 Pattern 的 GetDefaultFocusable() |
| Dynamic 与 Static 行为不一致 | 分别核对 Dynamic JSView/Common Bridge、Static Common modifier/Static Model 和对应 SDK 声明，不从另一范式推断 |
| C API 找不到对应属性 | 在 `native_node.h` 按具体枚举检索；ArkTS Common 属性不保证均有公开 Node C API |

## 调试入口

- 从具体 SDK 属性名定位 Dynamic/Static 声明，再进入对应前端解析入口。
- 在 ViewAbstract/Model 写入点确认值进入 `LayoutProperty`（visibility）、`RenderContext`（backgroundColor/zIndex/freeze 等）还是 `FocusHub`（焦点属性）。
- 背景属性问题同时确认是否进入 RenderContext 存储 vs FrameNode 子节点挂载（CustomBuilder）。
- 焦点问题同时核对 FocusHub 的 supportedStates_ 与 currentState_ 位掩码。
- 回归优先运行 `test/unittest/core/base/` 和 `test/unittest/capi/modifiers/` 中对应属性用例。

## 相关主题

- [布局属性](layout-attributes.md)
- [视效属性](visual-effect-attributes.md)
- [背景图片通用属性](background-image.md)
- [样式属性](style-attributes.md)
- [图片加载](image-loading.md)
- [DrawableDescriptor](drawable-descriptor.md)
- [渲染管线](../architecture/basic-render-pipeline.md)