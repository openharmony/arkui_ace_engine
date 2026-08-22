# SVG Context

> 文档版本：v1.0
> 更新时间：2026-07-24
> 来源：`docs/context_registry.json` 主题 `SVG`

## 定位

SVG 是 ArkUI 图片加载链路中的矢量图解析与绘制能力，不是单独对外创建的 UI 组件。当前 NG 路径将 SVG 数据解析为 SvgDom 和 SvgNode 树，再通过 SvgImageObject 与 SvgCanvasImage 接入 Image 渲染链路；兼容目录仍保留旧前端相关实现。

本文档只维护稳定路由。元素支持范围、属性解析、引用关系、滤镜、动画和 SVG2 能力以源码、测试与 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| NG SVG 主目录 | `frameworks/core/components_ng/svg/` | SVG DOM、上下文、节点、属性、变换和效果实现 |
| DOM 构建 | `frameworks/core/components_ng/svg/svg_dom.cpp`、`frameworks/core/components_ng/svg/svg_dom.h` | XML DOM 转 SvgNode 树的入口 |
| SVG 上下文 | `frameworks/core/components_ng/svg/svg_context.cpp`、`frameworks/core/components_ng/svg/svg_context.h` | 节点引用、样式和绘制上下文入口 |
| 元素与属性解析 | `frameworks/core/components_ng/svg/parse/` | shape、text、gradient、filter、use、animation 等解析入口 |
| 图片对象接入 | `frameworks/core/components_ng/image_provider/svg_image_object.cpp`、`frameworks/core/components_ng/image_provider/svg_image_object.h` | SVG 图片对象创建及 ImageLoadingContext 接入 |
| 绘制适配 | `frameworks/core/components_ng/render/adapter/svg_canvas_image.cpp`、`frameworks/core/components_ng/render/adapter/svg_canvas_image.h` | SvgDom 到 CanvasImage 的绘制入口 |
| 兼容实现 | `frameworks/compatible/components/svg/` | 旧兼容链路的 SVG 实现入口 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic Image API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/image.d.ts` | 通过 Image 图片源使用 SVG 的公开入口 |
| Static Image API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/image.static.d.ets` | Static ArkTS Image 的 SVG 图片源入口 |
| Dynamic Image Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/ImageModifier.d.ts` | Image Modifier 路径 |
| Static Image Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/ImageModifier.static.d.ets` | Static Modifier 路径 |
| Native 节点 API | `interfaces/native/native_node.h` | Image 节点图片源和 SVG 相关渲染属性入口 |

API 检索建议：

- SVG 图片源：在 Image SDK 中搜索 `ResourceStr`、`ImageContent`、`fillColor`、`supportSvg2`。
- DOM 与节点：在 `frameworks/core/components_ng/svg/` 搜索 `SvgDom`、`SvgContext`、`SvgNode`。
- 元素支持：在 `frameworks/core/components_ng/svg/parse/` 按元素名定位对应类型。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| XML DOM 与矢量绘制基础 | `frameworks/core/components_ng/svg/svg_dom.cpp` | `third_party/skia` | SkDOM、SkStream 及相关图形类型 | SVG XML 解析和底层图形数据入口 |
| 图形绘制 | `frameworks/core/components_ng/svg/`、`frameworks/core/components_ng/render/adapter/svg_canvas_image.cpp` | `foundation/graphic/graphic_2d` | `rosen/modules/2d_graphics/` | SVG 节点绘制、滤镜和 Canvas 适配入口 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| SVG 核心测试 | `test/unittest/core/svg/` | DOM、节点、属性、变换、动画、图形和效果回归 |
| 图片链路 SVG 测试 | `test/unittest/core/image/svg_dom_test_ng.cpp`、`test/unittest/core/image/svg_manager_test_ng.cpp` | SVG 与图片加载链路集成回归 |

### 相关 Spec

SVG 规格目录：`specs/04-common-capability/01-image-loading/02-svg-parsing/`

| Feat | 路径 |
|------|------|
| DOM 解析 | `Feat-01-svg-dom-parsing-spec.md` |
| 坐标、图形与文本 | `Feat-02-svg-coordinate-shape-text-spec.md` |
| 引用与效果 | `Feat-03-svg-reference-effects-spec.md` |
| 动画与图片集成 | `Feat-04-svg-animation-image-integration-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| SVG 数据无法解析 | `SvgDom`、图片数据到 SvgImageObject 的转换、SVG DOM 测试 |
| 某个元素或属性不生效 | `frameworks/core/components_ng/svg/parse/` 中对应元素、`SvgAttributesParser`、相关 Spec |
| gradient、mask、filter 或 use 异常 | `SvgContext`、对应 parse 类型、引用与效果规格 |
| 动画不执行或状态异常 | `svg_animation.*`、`SvgContext`、动画测试与动画规格 |
| SVG 在 Image 中尺寸或填充异常 | `SvgImageObject`、`SvgCanvasImage`、Image 布局与 SVG 图片集成规格 |

## 调试入口

- 从图片源进入 `SvgImageObject`，确认 SVG 数据是否成功创建 SvgDom。
- 解析问题从 `SvgDom` 的 DOM 构建和节点工厂进入，再定位 `parse/` 中对应元素。
- 引用、样式和动画问题优先查看 `SvgContext`。
- 绘制或尺寸问题从 `SvgCanvasImage` 和 Image 渲染适配链路定位。
- 回归验证优先运行 `test/unittest/core/svg/`，图片集成问题补充 `test/unittest/core/image/` 中 SVG 用例。

## 相关主题

- `ImageLoading`：[docs/kb/capabilities/image-loading.md](image-loading.md)
- `Image`：[docs/kb/components/media/image.md](../components/media/image.md)
- `DrawableDescriptor`：[docs/kb/capabilities/drawable-descriptor.md](drawable-descriptor.md)
