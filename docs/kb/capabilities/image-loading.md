# Image Loading Context

> 文档版本：v1.0
> 更新时间：2026-07-24
> 来源：`docs/context_registry.json` 主题 `ImageLoading`

## 定位

图片加载机制是 ArkUI 在图片组件、背景图、DrawableDescriptor 等场景中复用的通用能力，负责图片源识别、数据获取、缓存、解码、状态流转和可绘制对象生成。它不是独立 UI 组件。

本文档只维护稳定的源码、SDK、测试和 Spec 路由。具体支持格式、同步与异步行为、缓存策略、错误信息和生命周期以当前 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| NG 图片加载主目录 | `frameworks/core/components_ng/image_provider/` | 图片数据、图片对象、加载上下文、解码和状态管理入口 |
| 加载上下文 | `frameworks/core/components_ng/image_provider/image_loading_context.cpp`、`frameworks/core/components_ng/image_provider/image_loading_context.h` | 驱动数据加载、CanvasImage 生成和加载结果通知 |
| NG Provider | `frameworks/core/components_ng/image_provider/image_provider.cpp`、`frameworks/core/components_ng/image_provider/image_provider.h` | 图片数据加载和图片对象创建入口 |
| 加载状态 | `frameworks/core/components_ng/image_provider/image_state_manager.cpp`、`frameworks/core/components_ng/image_provider/image_state_manager.h` | 图片加载状态流转入口 |
| 图片对象与解码 | `frameworks/core/components_ng/image_provider/image_object.cpp`、`frameworks/core/components_ng/image_provider/image_decoder.cpp` | 静态图、动态图、PixelMap、SVG 的对象化与解码路由 |
| 图片源描述 | `frameworks/core/image/image_source_info.cpp`、`frameworks/core/image/image_source_info.h` | URI、资源、PixelMap 和其他图片源信息入口 |
| 数据加载器 | `frameworks/core/image/image_loader.cpp`、`frameworks/core/image/image_loader.h` | 文件、网络、资源、Base64、PixelMap 等数据源加载入口 |
| 内存与文件缓存 | `frameworks/core/image/image_cache.cpp`、`frameworks/core/image/image_file_cache.cpp` | 图片对象、图片数据和文件缓存入口 |
| Image 组件接入 | `frameworks/core/components_ng/pattern/image/` | Image 组件创建和持有 ImageLoadingContext 的入口 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic Image API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/image.d.ts` | Image 图片源、加载事件和加载控制声明 |
| Static Image API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/image.static.d.ets` | Static ArkTS Image 声明 |
| Dynamic Image Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/ImageModifier.d.ts` | Dynamic Modifier 图片属性声明 |
| Static Image Modifier | `<OH_ROOT>/interface/sdk-js/api/arkui/ImageModifier.static.d.ets` | Static Modifier 图片属性声明 |
| DrawableDescriptor API | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.drawableDescriptor.d.ts`、`<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.drawableDescriptor.static.d.ets` | DrawableDescriptor 图片源能力入口 |
| Native 节点 API | `interfaces/native/native_node.h` | Image 节点图片源、加载和渲染属性入口 |

API 检索建议：

- 图片源和加载事件：在 Image SDK 文件中搜索 `ImageInterface`、`ImageAttribute`、`onComplete`、`onError`、`onFinish`。
- 加载与缓存：在源码中搜索 `ImageLoadingContext`、`ImageProvider`、`ImageLoader`、`ImageCache`。
- 图片类型分流：在 `image_provider/` 中搜索 `StaticImageObject`、`AnimatedImageObject`、`PixelMapImageObject`、`SvgImageObject`。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 图片解码与 PixelMap | `frameworks/core/components_ng/image_provider/`、`frameworks/core/image/image_loader.cpp` | `foundation/multimedia/image_framework` | `interfaces/innerkits/include/` | ImageSource、PixelMap 和图片解码入口 |
| 图形绘制 | `frameworks/core/components_ng/image_provider/drawing_image_data.cpp`、`frameworks/core/components_ng/render/adapter/` | `foundation/graphic/graphic_2d` | `rosen/modules/2d_graphics/` | 图片数据转换和 CanvasImage 绘制入口 |
| 资源管理 | `frameworks/core/image/image_loader.cpp` | `base/global/resource_management` | `interfaces/inner_api/include/resource_manager.h` | Resource 类型图片数据读取入口 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 图片加载核心测试 | `test/unittest/core/image/` | ImageLoader、ImageProvider、缓存、压缩和图片源解析回归 |
| Image 组件测试 | `test/unittest/core/pattern/image/` | ImageLoadingContext 接入、属性、事件和加载状态回归 |
| NAPI 图片加载测试 | `test/unittest/interfaces/napi/image_loader_test.cpp` | 接口层图片加载回归 |

### 相关 Spec

| Spec | 路径 |
|------|------|
| 设计文档 | `specs/04-common-capability/01-image-loading/01-image-loading-mechanism/design.md` |
| 图片加载机制规格 | `specs/04-common-capability/01-image-loading/01-image-loading-mechanism/Feat-01-image-loading-mechanism-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 图片源未被识别或数据读取失败 | `ImageSourceInfo`、`ImageLoader`、对应数据源 Loader 和 Image SDK 声明 |
| 加载成功但没有生成可绘制对象 | `ImageLoadingContext`、`ImageProvider`、`ImageObject`、`ImageDecoder` |
| 加载状态或回调顺序异常 | `ImageStateManager`、`ImageLoadingContext`、Image 组件事件测试 |
| 缓存未命中或文件缓存异常 | `ImageCache`、`ImageFileCache`、`test/unittest/core/image/` |
| SVG、动态图或 PixelMap 路径异常 | 对应 ImageObject 子类、SVG Context、Image 组件 KB |

## 调试入口

- 先从 `ImageSourceInfo` 确认图片源类型和标识，再进入 `ImageLoader` 查看数据获取路径。
- 数据获取后，从 `ImageProvider` 跟踪 ImageData 到具体 ImageObject 的分流。
- 渲染前问题从 `ImageLoadingContext`、`ImageDecoder` 和 CanvasImage 生成路径定位。
- 缓存问题分别检查 `ImageCache` 与 `ImageFileCache`，不要混淆内存对象缓存和文件缓存。
- 回归验证优先运行 `test/unittest/core/image/`，涉及 Image 组件生命周期时补充 `test/unittest/core/pattern/image/`。

## 相关主题

- `Image`：[docs/kb/components/media/image.md](../components/media/image.md)
- `SVG`：[docs/kb/capabilities/svg.md](svg.md)
- `BackgroundImage`：[docs/kb/capabilities/background-image.md](background-image.md)
- `DrawableDescriptor`：[docs/kb/capabilities/drawable-descriptor.md](drawable-descriptor.md)