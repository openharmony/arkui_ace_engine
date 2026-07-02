# Image Context

> 文档版本：v1.0
> 更新时间：2026-06-27
> 来源：`docs/context_registry.json` 主题 `Image`

## 定位

Image 是 ArkUI 的图片显示组件，面向应用侧提供图片加载、解码、渲染、缓存、动画播放、降级占位、内存管理等能力。支持网络图片、本地文件、应用资源、Base64、PixelMap 等多种数据源，以及 JPEG/PNG/WebP/GIF/SVG/HDR 等多种格式。

Image 组件采用异步加载流水线架构，核心流程为：属性配置 → 加载（后台线程）→ 数据就绪 → 布局同步 → 解码（后台线程）→ 渲染。图片加载基础设施由 `image_provider` 子系统提供，组件层通过 `ImageLoadingContext` 驱动状态机完成加载协调。

本文档用于快速定位 Image 相关源码、SDK 声明、测试和规格文档。具体行为、默认值、边界条件和兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| Pattern 生命周期、加载触发、事件分发 | `frameworks/core/components_ng/pattern/image/image_pattern.cpp` | Image 组件核心行为实现入口 |
| Pattern 类型和接口声明 | `frameworks/core/components_ng/pattern/image/image_pattern.h` | `ImagePattern` 类型、加载上下文管理、可见性优化、动画控制、内存管理接口 |
| ArkTS Dynamic Model | `frameworks/core/components_ng/pattern/image/image_model_ng.cpp` | 动态前端 Image 创建和属性写入入口 |
| ArkTS Static Model | `frameworks/core/components_ng/pattern/image/image_model_static.cpp` | 静态前端 Image 属性写入入口 |
| Model 抽象 | `frameworks/core/components_ng/pattern/image/image_model.h` | Image Model 抽象接口声明 |
| 布局算法 | `frameworks/core/components_ng/pattern/image/image_layout_algorithm.cpp` | 图片测量、ImageFit 计算、srcRect/dstRect 裁剪 |
| 布局属性 | `frameworks/core/components_ng/pattern/image/image_layout_property.h` | ImageSourceInfo、ImageFit、AutoResize、Alt 等布局属性声明 |
| 渲染属性 | `frameworks/core/components_ng/pattern/image/image_render_property.h` | ColorFilter、Repeat、Interpolation、HDR 等渲染属性声明 |
| 事件中心 | `frameworks/core/components_ng/pattern/image/image_event_hub.h` | onComplete、onError、onFinish 等事件回调存储 |
| 内容绘制 | `frameworks/core/components_ng/pattern/image/image_content_modifier.*` | 图片绘制 modifier 和渲染逻辑入口 |
| 覆盖层绘制 | `frameworks/core/components_ng/pattern/image/image_overlay_modifier.*` | 图片覆盖层（如 alt 状态提示）渲染 |
| 绘制方法 | `frameworks/core/components_ng/pattern/image/image_paint_method.*` | 图片绘制方法和配置构建 |
| DFX 诊断 | `frameworks/core/components_ng/pattern/image/image_dfx.*` | 图片加载性能追踪和诊断数据 |
| 属性定义 | `frameworks/core/components_ng/pattern/image/image_properties.h` | Image 相关枚举和属性类型定义 |
| 多线程加载 | `frameworks/core/components_ng/pattern/image/image_pattern_multi_thread.cpp` | 多线程图片加载路径 |
| 加载上下文和状态机 | `frameworks/core/components_ng/image_provider/image_loading_context.*` | 加载状态机管理、回调协调、线程切换 |
| 图片提供者 | `frameworks/core/components_ng/image_provider/image_provider.*` | 图片操作静态工厂、加载器选择、缓存管理 |
| 状态管理器 | `frameworks/core/components_ng/image_provider/image_state_manager.*` | 加载状态转换定义 |
| ImageObject 抽象 | `frameworks/core/components_ng/image_provider/image_object.*` | 图片对象基类和数据封装 |
| 静态图片对象 | `frameworks/core/components_ng/image_provider/static_image_object.*` | 静态图片（JPEG/PNG/WebP 等）对象实现 |
| 动画图片对象 | `frameworks/core/components_ng/image_provider/animated_image_object.*` | GIF/动画 WebP 图片对象实现 |
| SVG 图片对象 | `frameworks/core/components_ng/image_provider/svg_image_object.*` | SVG 图片对象实现 |
| PixelMap 图片对象 | `frameworks/core/components_ng/image_provider/pixel_map_image_object.*` | PixelMap 数据源图片对象实现 |
| 解码器 | `frameworks/core/components_ng/image_provider/image_decoder.*` | 图片解码逻辑 |
| 图片数据 | `frameworks/core/components_ng/image_provider/image_data.*` | 图片数据抽象 |
| Drawing 图片数据 | `frameworks/core/components_ng/image_provider/image_utils.*` | 图片工具方法（线程调度等） |
| 加载器基类 | `frameworks/core/image/image_loader.*` | 各源类型加载器基类和注册 |
| 图片源信息 | `frameworks/core/image/image_source_info.*` | 图片源 URI、类型、Key 等信息定义 |
| 图片缓存 | `frameworks/core/image/image_cache.*` | 图片对象缓存、LRU 淘汰 |
| 图片文件缓存 | `frameworks/core/image/image_file_cache.*` | 下载图片的文件缓存 |
| 图片压缩 | `frameworks/core/image/image_compressor.*` | 图片压缩和格式转换工具 |
| CanvasImage 抽象 | `frameworks/core/components_ng/render/canvas_image.h` | 图片渲染抽象接口 |
| PixelMap 渲染适配 | `frameworks/core/components_ng/render/adapter/pixelmap_image.*` | PixelMap 到 CanvasImage 的渲染适配 |
| Drawing 渲染适配 | `frameworks/core/components_ng/render/adapter/drawing_image.*` | Drawing 图片渲染适配 |
| 动画图渲染适配 | `frameworks/core/components_ng/render/adapter/animated_image.*` | 动画图片渲染适配 |
| SVG 渲染适配 | `frameworks/core/components_ng/render/adapter/svg_canvas_image.*` | SVG 图片渲染适配 |
| 绘制工具 | `frameworks/core/components_ng/render/adapter/image_painter_utils.*` | 图片绘制通用工具 |
| C API 枚举 | `interfaces/native/native_node.h` | `NODE_IMAGE_*` 属性和事件枚举 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/image.d.ts` | 动态 ArkTS `ImageInterface`、`ImageAttribute` 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/image.static.d.ets` | 静态 ArkTS Image 组件和属性声明 |
| Modifier API (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/ImageModifier.d.ts` | 动态 Modifier 声明 |
| Modifier API (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/ImageModifier.static.d.ets` | 静态 Modifier 声明 |
| CAPI / NDK | `interfaces/native/native_node.h` | Image C API 属性 `NODE_IMAGE_*` 和事件枚举 |

API 检索建议：

- 属性声明：在 SDK 文件中搜索 `ImageAttribute` 和具体属性名。
- 构造参数：在 SDK 文件中搜索 `ImageInterface`、`ImageOptions` 或 `Image(`。
- Modifier：在 `ImageModifier*.d.ts` / `ImageModifier*.d.ets` 中确认声明。
- C API：在 `interfaces/native/native_node.h` 中搜索 `NODE_IMAGE_`。

### API 解析实现路径

Image 组件**尚未进行组件化改造**，属性解析仍采用双路径架构，编译产物在主 `libace_compatible.z.so` 中。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| **JSView（声明式组件）** | `frameworks/bridge/declarative_frontend/jsview/js_image.cpp` | `JSImage::SetXxx()` → `ImageModel::GetInstance()->SetXxx()` |
| **ArkTS Bridge（动态属性 / Modifier / FrameNode 命令式）** | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_image_bridge.cpp` | `ImageBridge::SetXxx()` → `node_image_modifier` → `ImageModelNG::SetXxx(frameNode, ...)` |
| **node_modifier 层** | `frameworks/core/interfaces/native/node/node_image_modifier.cpp` | C++ 属性 Set/Reset/Get 函数，由 bridge 和 C API 共用 |
| **C API（NDK）** | `frameworks/core/interfaces/native/node/node_image_modifier.cpp` + `interfaces/native/node/style_modifier.cpp` | Image 无专属 `image_native_impl.*`；`NODE_IMAGE_*` 枚举通过通用 node_model/style_modifier 框架分发到 `node_image_modifier` |
| **前端 Modifier（ArkTS 侧）** | `frameworks/bridge/declarative_frontend/ark_modifier/src/image_modifier.ts` | ArkTS `ImageModifier` 类定义 |

组件化改造参考：`./组件化重构通用方案.md`。改造后上述 JSView 和 Bridge 双路径将统一到 `pattern/image/bridge/arkts_native_image_bridge.cpp`，并输出独立 so。

### 外部依赖入口

外部仓路径以 OpenHarmony 根目录为基准。

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 图片解码框架 | `frameworks/core/components_ng/image_provider/image_decoder.*`、`frameworks/core/image/image_loader.*` | `foundation/multimedia/image_framework` | `interfaces/innerkits/include/pixel_map.h`、`interfaces/innerkits/include/image_source.h` | 图片解码、PixelMap 创建、格式识别等图片基础能力入口 |
| 图形绘制 | `frameworks/core/components_ng/render/canvas_image.h`、`frameworks/core/components_ng/render/adapter/drawing_image.*` | `foundation/graphic/graphic_2d` | `rosen/modules/2d_graphics/include/draw/*` | Canvas、Brush、Image 等绘制类型入口 |
| Rosen / RenderService | `frameworks/core/components_ng/render/adapter/pixelmap_image.*` | `foundation/graphic/graphic_2d` | `rosen/modules/render_service_client/core/*` | 渲染上下文和 GPU 纹理上传入口 |
| NDK PixelMap | `interfaces/native/BUILD.gn` | `foundation/multimedia/image_framework` | `interfaces/innerkits:image_native`、`interfaces/innerkits:image_external_config` | C API 层 PixelMap 和 ImageSource 的 NDK 依赖 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/image/` | Pattern、布局、事件、加载、动画、内存回调、边界等 Image 行为回归 |
| Spec 功能域 | `specs/05-ui-components/08-image-components/01-image/` | Image 功能域设计和验收契约 |
| Spec 总索引 | `specs/index.md` | `05-08-01 Image` 功能域注册入口 |
| Context registry | `docs/context_registry.json` | Image 的 KB、Spec、源码、API、测试统一路由 |

### 相关 Spec

Image 功能域：`specs/05-ui-components/08-image-components/01-image/`

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | 图片核心显示 | `Feat-01-image-core-display-spec.md` |
| Feat-02 | 图片颜色效果 | `Feat-02-image-color-effects-spec.md` |
| Feat-03 | 图片高级能力 | `Feat-03-image-advanced-spec.md` |
| Feat-04 | 图片事件 | `Feat-04-image-events-spec.md` |
| Feat-05 | 图片基础和内存优化 | `Feat-05-image-base-memory-opt-spec.md` |

相关通用能力 Spec：

| 主题 | 路径 |
|------|------|
| 图片加载机制 | `specs/04-common-capability/01-image-loading/01-image-loading-mechanism/` |
| SVG 解析 | `specs/04-common-capability/01-image-loading/02-svg-parsing/` |
| DrawableDescriptor | `specs/04-common-capability/01-image-loading/03-drawable-descriptor/` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 图片加载后不显示 | Model 创建入口、`ImageLayoutProperty` 源信息属性、布局算法入口 |
| 图片加载缓慢 | `image_cache.*`、`image_file_cache.*`、`image_provider.*` 缓存和加载链路、Feat-05 |
| 内存占用高 | `ImagePattern` 可见性回收和内存回调、`image_loading_context.*` 自动调整大小逻辑、Feat-05 |
| ImageFit 裁剪或留白异常 | 布局算法中 srcRect/dstRect 计算、SDK `ImageAttribute` fit 属性声明、Feat-01 |
| Alt / 占位图 / 降级不生效 | `ImagePattern` 降级链路（altLoadingCtx_、altErrorCtx_）、SDK alt 属性声明 |
| GIF/WebP 动画不播放或卡顿 | `animated_image_object.*`、`animated_image.*` 渲染适配、可见性暂停恢复逻辑 |
| SVG 渲染异常 | `svg_image_object.*`、`svg_canvas_image.*`、SVG 解析 Spec |
| onComplete/onError 不触发 | SDK 事件声明、`ImageEventHub`、C API `NODE_IMAGE_ON_COMPLETE`/`NODE_IMAGE_ON_ERROR`、Feat-04 |
| HDR 图片显示异常 | `ImageRenderProperty` HDR 属性、SDK DynamicRangeMode 声明、Feat-03 |
| 颜色滤镜/染色不生效 | `ImageRenderProperty` ColorFilter/FillColor 属性、SDK 属性声明、Feat-02 |
| 网络图片下载失败 | `frameworks/core/image/image_loader.*` 网络加载器、图片文件缓存 |

## 调试入口

- 创建链路：从 Model 创建入口确认 Image 节点和 Pattern 是否建立，检查 ImageSourceInfo 是否有效。
- 加载链路：从 `ImagePattern::OnModifyDone` → `LoadImageDataIfNeed` → `ImageLoadingContext::LoadImageData` 跟踪加载触发和状态转换。
- 布局链路：从布局算法入口确认约束、ImageFit 计算和 srcRect/dstRect 输出。
- 解码链路：从 `ImageLoadingContext::MakeCanvasImage` → `ImageDecoder::Decode` 检查解码尺寸和格式。
- 渲染链路：从 `ImageContentModifier::Draw` → `CanvasImage::DrawToRSCanvas` 确认绘制参数。
- DFX 追踪：`image_dfx.*` 提供加载耗时、尺寸、源类型等诊断数据。
- 回归验证：优先运行 `test/unittest/core/pattern/image/` 下的定向用例。

## 相关主题

- `ImageAnimator`：`docs/pattern/image_animator/Image_Animator_Knowledge_Base.md`
- 图片加载机制（通用能力）：`specs/04-common-capability/01-image-loading/01-image-loading-mechanism/`
- API 范式：`docs/api/ArkUI_API_Paradigm_Knowledge_Base_CN.md`
