# Background Image Context

> 文档版本：v1.0
> 更新时间：2026-07-24
> 来源：`docs/context_registry.json` 主题 `BackgroundImage`

## 定位

背景图片是 ArkUI 通用属性能力，覆盖背景图源、重复方式、尺寸、位置、同步加载和可拉伸区域等入口。属性经 CommonMethod 前端解析后写入 ViewAbstract 和 RenderContext，并复用图片加载与绘制能力。

本文档只维护属性解析、Native 接口、渲染上下文、测试和 Spec 路由。参数约束、组合规则、默认行为和版本差异以 SDK、源码、测试与 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Dynamic JSView 解析 | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | CommonMethod 背景图片属性的 JS 参数解析入口 |
| Dynamic ArkTS Bridge | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.cpp` | ArkTS 动态属性到 common modifier 的解析入口 |
| 属性写入 | `frameworks/core/components_ng/base/view_abstract.cpp`、`frameworks/core/components_ng/base/view_abstract.h` | 背景图源、重复、尺寸、位置和可拉伸区域写入入口 |
| 渲染属性承载 | `frameworks/core/components_ng/render/render_context.cpp`、`frameworks/core/components_ng/render/render_context.h` | 背景图片相关 RenderContext 属性入口 |
| Rosen 渲染适配 | `frameworks/core/components_ng/render/adapter/rosen_render_context.cpp` | 背景图片属性到图形节点的适配入口 |
| node_modifier | `frameworks/core/interfaces/native/node/node_common_modifier.cpp` | Bridge 和 Native 路径共用的 Set/Reset/Get 委托层 |
| Native Style API | `interfaces/native/node/style_modifier.cpp` | ArkUI AttributeItem 到 common modifier 的入口 |
| Native 枚举 | `interfaces/native/native_node.h` | 背景图片相关通用属性枚举 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic Common API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `backgroundImage`、`backgroundImageSize`、`backgroundImagePosition`、`backgroundImageResizable` 声明 |
| Static Common API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/common.static.d.ets` | Static ArkTS 通用背景图片属性声明 |
| Dynamic Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.d.ts` | Dynamic Modifier 属性入口 |
| Static Common Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/CommonModifier.static.d.ets` | Static Modifier 属性入口 |
| Native 节点 API | `interfaces/native/native_node.h` | 通用背景图片属性枚举和数据约定入口 |

API 检索建议：在 SDK 与 Native 头文件中搜索 `backgroundImage`、`backgroundImageSize`、`backgroundImagePosition`、`backgroundImageResizable`、`NODE_BACKGROUND_IMAGE`。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 图片解码与 PixelMap | `frameworks/core/components_ng/render/`、`frameworks/core/image/` | `foundation/multimedia/image_framework` | `interfaces/innerkits/include/` | 背景图片数据和 PixelMap 处理入口 |
| 图形渲染 | `frameworks/core/components_ng/render/adapter/rosen_render_context.cpp` | `foundation/graphic/graphic_2d` | `rosen/modules/render_service_client/`、`rosen/modules/2d_graphics/` | 背景图片绘制和图形节点属性入口 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| ViewAbstract 测试 | `test/unittest/core/base/view_abstract_test_ng.cpp`、`test/unittest/core/base/view_abstract_test_five_ng.cpp`、`test/unittest/core/base/view_abstract_model_static_test_two_ng.cpp` | 背景图源、尺寸、位置和可拉伸区域属性回归 |
| RenderContext 测试 | `test/unittest/core/render/render_property_test_ng.cpp`、`test/unittest/core/rosen/rosen_render_context_test.cpp` | 渲染属性与 Rosen 适配回归 |
| Native modifier 测试 | `test/unittest/capi/modifiers/common_method_modifier_test.cpp`、`test/unittest/capi/modifiers/generated/common_method_modifier_test_1.cpp` | Common Native 属性解析和 Set/Reset/Get 回归 |

### 相关 Spec

| Spec | 路径 |
|------|------|
| 设计文档 | `specs/04-common-capability/03-common-attributes/10-image-related-attributes/design.md` |
| 背景图片属性规格 | `specs/04-common-capability/03-common-attributes/10-image-related-attributes/Feat-01-background-image-attributes-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 背景图片源未生效 | Common SDK 声明、JSView/ArkTS Bridge、`ViewAbstract::SetBackgroundImage` 所在文件 |
| repeat、size 或 position 结果异常 | 对应 SDK 类型、ViewAbstract 写入、RenderContext 属性与测试 |
| 可拉伸区域异常 | `backgroundImageResizable` 声明、ViewAbstract slice 写入、Native modifier 测试 |
| ArkTS 与 Native 设置结果不一致 | `arkts_native_common_bridge.cpp`、`node_common_modifier.cpp`、`style_modifier.cpp` |
| 图片已加载但未正确绘制 | 图片加载机制 KB、RosenRenderContext 背景图适配和渲染测试 |

## 调试入口

- Dynamic API 从 `js_view_abstract.cpp` 或 `arkts_native_common_bridge.cpp` 进入参数解析。
- 属性写入统一从 `ViewAbstract` 跟到 `RenderContext` 的 Background 属性组。
- Native 属性从 `style_modifier.cpp` 跟到 `node_common_modifier.cpp`，再进入 ViewAbstract。
- 图片数据问题转到图片加载机制，绘制问题转到 `rosen_render_context.cpp`。
- 回归验证优先运行 ViewAbstract、RenderContext 和 common modifier 相关用例。

## 相关主题

- `ImageLoading`：[docs/kb/capabilities/image-loading.md](image-loading.md)
- `Image`：[docs/kb/components/media/image.md](../components/media/image.md)
- `LayoutAttributes`：[docs/kb/capabilities/layout-attributes.md](layout-attributes.md)
