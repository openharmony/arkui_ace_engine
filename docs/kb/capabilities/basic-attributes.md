# 基础属性 Context

> 文档版本：v2.1
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `basic-attributes`

## 定位

基础属性是所有 ArkUI 组件共享的通用属性集合，归属 Func-04-03-03。覆盖组件标识（id/key/restoreId/uniqueId/inspectorLabel）、显隐控制（visibility/zIndex/obscured/allowForceDark/clickDistance/enableClickSoundEffect）、背景设置（backgroundColor/backgroundImage/backgroundImageSize/backgroundImagePosition/backgroundBlurStyle/backdropBlur/backgroundEffect/backgroundBrightness/backgroundImageResizable/background(CustomBuilder)）、渲染控制（renderGroup/renderFit/freeze/useEffect/reuseId/reuse/excludeFromRenderGroup）、浮层叠加（overlay + OverlayOptions）、焦点属性（focusable/tabIndex/defaultFocus/groupDefaultFocus/focusOnTouch/tabStop/focusBox/nextFocus/focusScopeId/focusScopePriority/onFocus/onBlur/onKeyEvent）。

状态效果（stateStyles/hoverEffect/clickEffect）和动态属性设置（attributeModifier）已迁移至 Func-04-03-07 样式属性域，见 [style-attributes](style-attributes.md)。

行为事实来自 SDK 声明、源码实现和测试；本页仅提供路由入口，不重复 Spec 规格内容。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|-------|---------|------|
| 组件标识与显隐 | `frameworks/core/components_ng/base/view_abstract.h/cpp` | id/visibility/zIndex/obscured 设置入口 |
| id 查找 | `frameworks/core/pipeline/base/element_register.h` | ElementRegister inspectorIdMap_ 存储 id → FrameNode 映射 |
| 背景属性 | `frameworks/core/components_ng/render/render_context.h/cpp` | backgroundColor/backgroundImage/blur/brightness/freeze/visibility/zIndex/obscured 存储与回调 |
| 浮层挂载 | `frameworks/core/components_ng/base/frame_node.h/cpp` | overlayNode_ / background(CustomBuilder) 子节点挂载 |
| 渲染控制 | `frameworks/core/components_ng/base/frame_node.h/cpp` | renderGroup/reuseId/id/uniqueId/restoreId 存储 |
| RS 渲染桥接 | `frameworks/core/components_ng/render/adapter/rosen_render_context.cpp` | 背景绘制 / visibility / zIndex / obscured / freeze / renderGroup → RSNode |
| 焦点属性 | `frameworks/core/components_ng/event/focus_hub.h/cpp` | focusable/tabIndex/defaultFocus/groupDefaultFocus/focusOnTouch/tabStop/focusScopeId/focusScopePriority |
| 焦点导航 | `frameworks/core/components_ng/event/focus_hub.h/cpp` | nextFocus/onFocus/onBlur/onKeyEvent 焦点事件分发 |
| focusBox | `frameworks/core/components_ng/base/view_abstract.h/cpp` | focusBox 自定义焦点框样式 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|---------|------|
| ArkTS 声明式 | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | JsVisibility/JsBackgroundColor/JsOverlay/JsRenderGroup/JsFocus 等 |
| C API 属性枚举 | `interfaces/native/native_node.h` | NODE_VISIBILITY / NODE_Z_INDEX / NODE_BACKGROUND_COLOR / NODE_OBSCURED / NODE_RENDER_GROUP / NODE_RENDER_FIT / NODE_OVERLAY / NODE_FOCUSABLE / NODE_TAB_INDEX / NODE_DEFAULT_FOCUS / NODE_GROUP_DEFAULT_FOCUS / NODE_FOCUS_ON_TOUCH / NODE_FOCUS_SCOPE_ID / NODE_FOCUS_SCOPE_PRIORITY |
| C API 桥接 | `interfaces/native/node/style_modifier.cpp` | 通用属性 C-API → ViewAbstract 转换 |
| SDK 类型声明 | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | CommonMethod<T> 基础属性签名 |

### 接口实现路径总览

| 范式 | 入口文件 | 实例路由守卫 | 说明 |
|------|----------|--------------|------|
| 动态版 | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | `withInstanceId(instanceId_)` | JsVisibility/JsBackgroundColor/JsOverlay/JsRenderGroup/JsFocus 等；属性 setter 通过 ViewStackProcessor 写入 ViewAbstract |
| 静态版 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/` | `Sync_InstanceId(instanceId_)` + `Restore_InstanceId()` | 静态版属性通过 Arkoala 生成代码直接调用 ViewAbstract |
| C-API | `interfaces/native/node/style_modifier.cpp` | `ArkUI_ContextHandle.id → ContainerScope` | 通用属性 C-API → ViewAbstract 转换；NODE_VISIBILITY/NODE_Z_INDEX/NODE_BACKGROUND_COLOR 等 |
| Kit 层 | `interfaces/inner_api/ace_kit/include/ui/view/ui_context.h` | `PipelineContext::Current()` | Kit 层薄包装 PipelineContext |

**关键前端差异**：

- 焦点属性：动态版通过 JsFocus 系列 setter，静态版通过 Arkoala 生成代码；C-API 通过 NODE_FOCUSABLE/NODE_TAB_INDEX 等枚举
- overlay：动态版通过 JsOverlay，静态版通过生成代码；C-API 通过 NODE_OVERLAY
- backgroundImage：动态版通过 JsBackgroundImage，静态版通过生成代码；C-API 暂无直接 backgroundImage 枚举

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|-----------|-------------------------------|------|
| 图形渲染 | `frameworks/core/components_ng/render/adapter/rosen_render_context.cpp` | `graphic_2d` | `render_service_client/core/ui/rs_node.h`、`render_service_base/include/property/rs_properties_def.h` | backgroundColor / visibility / zIndex / obscured / freeze / renderGroup / backgroundImage 全部通过 RSNode 下发；UIEffect (BrightnessBlender / FilterRadiusGradientBlurPara / RSMask) 用于模糊与特效 |
| 图片框架 | `frameworks/core/components_ng/image_provider/image_loading_context.h`、`adapter/ohos/osal/pixel_map_ohos.h` | `multimedia_image_framework` | `interfaces/innerkits/include/Media::PixelMap` | backgroundImage 解码链路：ImageLoadingContext → CanvasImage → PixelMapOhos → Media::PixelMap；SurfaceCapture 回调使用 Media::PixelMap |
| Skia（间接） | `frameworks/core/components_ng/render/adapter/rosen_render_context.cpp` | `skia`（通过 graphic_2d 间接依赖） | `include/utils/SkParsePath.h` | SkParsePath 用于 SVG 路径解析；Skia 由 graphic_2d 统一引入 |
| DFX 性能度量 | `frameworks/core/components_ng/base/view_abstract.cpp` | `hiviewdfx` | `base/hiviewdfx/histogram_wrapper.h` | HistogramWrapper 用于属性设置性能度量上报 |
| 窗口管理 | `frameworks/core/components_ng/base/view_abstract.cpp`（通过 SubwindowManager）、`frameworks/core/components_ng/event/focus_hub.cpp`（通过 SubwindowManager） | `window_manager` | SubwindowManager 用于 overlay/dialog 弹窗上下文；focus 焦点管理通过 Subwindow 焦点路由 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|---------|------|
| 属性单测 | `test/unittest/core/pattern/` | visibility/renderGroup 等属性行为测试 |
| C API 单测 | `test/unittest/ace_engine/C-API-Main/components/` | C-API 基础属性 modifier 测试 |

### 相关 Spec

| Spec | 路径 | 状态 |
|------|------|------|
| Feat-01 组件标识与显隐 | `specs/04-common-capability/03-common-attributes/03-basic-attributes/Feat-01-component-id-visibility-spec.md` | Baselined |
| Feat-02 背景设置 | `specs/04-common-capability/03-common-attributes/03-basic-attributes/Feat-02-background-setting-spec.md` | Baselined |
| Feat-03 渲染与复用 | `specs/04-common-capability/03-common-attributes/03-basic-attributes/Feat-03-render-reuse-spec.md` | Baselined |
| Feat-04 浮层 | `specs/04-common-capability/03-common-attributes/03-basic-attributes/Feat-04-overlay-spec.md` | Baselined |
| Feat-05 焦点属性 | `specs/04-common-capability/03-common-attributes/03-basic-attributes/Feat-05-focus-attribute-spec.md` | Baselined |
| 基础属性设计文档 | `specs/04-common-capability/03-common-attributes/03-basic-attributes/design.md` | Baselined |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| id 空字符串也会注册到 inspectorIdMap_ | `element_register.cpp` — AddFrameNodeByInspectorId 无空字符串检查，空 id 会被注册但 Inspector 查询时无实际意义 |
| id 冲突时多个节点共存于 inspectorIdMap_ list | `element_register.cpp` — 同 id 使用 push_back 添加到 list，不覆盖前注册；查询返回最后一个有效节点 |
| visibility=None 不占空间 vs Hidden 保留空间 | `view_abstract.cpp` SetVisibility → `render_context.h` UpdateVisibility → `frame_node.cpp` visibility 布局决策 |
| background(CustomBuilder) 与 backgroundColor 双机制 | `view_abstract.cpp` SetBackgroundStyle → 区分 RenderContext 存储 vs 子节点挂载 |
| 三模糊互斥覆盖 | backdropBlur / backgroundBlurStyle / backgroundEffect 设置时互斥覆盖前一个 |
| backgroundColor 不可解析资源 → TRANSPARENT | `render_context.h` OnBackgroundColorUpdate — 资源解析失败回退 TRANSPARENT |
| backgroundBrightness rate=0 不生效 | `render_context.h` — rate 参数需 > 0 |
| obscured 截图/录屏区域屏蔽 | `render_context.h` UpdateObscuredReasons → `rosen_render_context.cpp` OnObscuredReasonsUpdate |
| freeze 仅设置 rsNode 属性 | `view_abstract.cpp` SetFreeze → `render_context.h` UpdateFreeze → `rosen_render_context.cpp` OnFreezeUpdate → rsNode_->SetFreeze；与 FrameNode::SetNodeFreeze 无关 |
| renderGroup 子树脏聚合 | `frame_node.cpp` renderGroup 标记 → RS 层 MarkNodeGroup |
| excludeFromRenderGroup 排除子树 | `view_abstract.cpp` SetExcludeFromRenderGroup → RS 层节点标记 |
| reuseId 组件复用 | `lazy_for_each_builder.cpp` recyclableNodeSet_ 回收池匹配 |
| overlay 多次调用覆盖前一次 | `view_abstract.cpp` SetOverlay — 后调用覆盖前调用 |
| overlay(undefined) 重置 | `view_abstract.cpp` SetOverlay(undefined) → 移除 overlayNode_ |
| focusable 默认值因组件类型不同 | `focus_hub.h` — 各 Pattern 的 GetDefaultFocusable() 返回值不同 |

## 调试入口

- Inspector 中 id/uniqueId/visibility/zIndex/obscured 可通过 `SimplifiedInspector` dump 查看
- 背景属性渲染可通过 RS 层 `SetBackgroundColor/SetFilter/DrawImage` 调试日志定位
- freeze 效果通过 RS 层 `SetFreeze` 调用确认生效状态
- renderGroup 聚合效果通过脏标记传播链路验证
- 焦点属性可通过 FocusHub::DumpFocusTree 查看焦点链和焦点树

## 相关主题

- [style-attributes](style-attributes.md) — 样式属性 (stateStyles/hoverEffect/clickEffect/attributeModifier)
- [layout-attributes](layout-attributes.md) — 布局属性 (width/height/position 等)
- [background-image](background-image.md) — 背景图片解码链路 (backgroundImage/backgroundImageSize/Position)
- [image-loading](image-loading.md) — 图片加载 (ImageLoadingContext/CanvasImage/PixelMapOhos)
- [drawable-descriptor](drawable_descriptor.md) — DrawableDescriptor 图片资源
- 渲染管线：`docs/kb/architecture/basic-render-pipeline.md` — RS 层渲染下发 (visibility/zIndex/renderGroup/freeze)
