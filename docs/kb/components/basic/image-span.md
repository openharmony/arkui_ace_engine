# ImageSpan Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `ImageSpan`

## 定位

ImageSpan 是 ArkUI 文本类的图片片段组件，作为 `Text`/`RichEditor` 的子节点在文本行内插入图片。ImageSpanNode 复用 `FrameNode` + `ImagePattern`（不存在独立 `ImageSpanPattern`），图像布局经 `ImageLayoutAlgorithm` 测量内在尺寸，父级 `Paragraph::AddPlaceholder` 在段落中预留占位符槽位后由 `ImagePaintMethod` 绘制。

ImageSpan 属于 Span 类（FuncID 05-09-06）。行为事实以 SDK 声明、源码实现、测试和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| ImageSpanNode（FrameNode+ImagePattern） | `frameworks/core/components_ng/pattern/text/span_node.h` | `ImageSpanNode`、`ImageSpanItem`（spanItemType=IMAGE） |
| ImageSpanView 静态 façade | `frameworks/core/components_ng/pattern/text/span/image_span_view.h`、`image_span_view.cpp` | 无独立 Model 类，`ImageSpanView` 承担创建与属性下发 |
| Static façade | `frameworks/core/components_ng/pattern/text/span/image_span_view_static.h`、`image_span_view_static.cpp` | C-API static modifier 用的 `std::optional` 变体 |
| 样式结构 | `frameworks/core/components_ng/pattern/text/text_styles.h` | `ImageSpanOptions`、`ImageSpanAttribute`、`ImageSpanSize` |
| 图片布局 | `frameworks/core/components_ng/pattern/image/image_layout_algorithm.h` | ImageLayoutAlgorithm 测量图像内在尺寸 |
| 图片绘制 | `frameworks/core/components_ng/pattern/image/image_paint_method.h` | ImagePaintMethod 在占位符槽位内绘制 |
| 占位符槽位 | `frameworks/core/components_ng/render/paragraph.h`、`render/frameworks/core/components_ng/render/adapter/txt_paragraph.h` | `Paragraph::AddPlaceholder` 预留槽位 |
| ArkTS-native Bridge | `frameworks/core/components_ng/pattern/text/span/bridge/image_span/arkts_native_image_span_bridge.cpp` | `ImageSpanBridge` 注册 Create/SetXxx/Reset |
| 动态模块 | `frameworks/core/components_ng/pattern/text/span/bridge/image_span/image_span_dynamic_module.cpp` | `ImageSpanDynamicModule`，模块名 "span"，输出 `libarkui_span.z.so` |
| C API 生成桩 | `frameworks/core/interfaces/native/implementation/image_span_modifier.cpp` | 桩：经 `DynamicModuleHelper::GetDynamicModule("ImageSpan")` 加载动态模块 |
| C API node 层 | `frameworks/core/interfaces/native/node/node_image_span_modifier.h`、`node_image_span_modifier.cpp` | `NodeModifier::GetImageSpanModifier()` |
| C API 枚举 | `interfaces/native/native_node.h` | `ARKUI_NODE_IMAGE_SPAN`、`NODE_IMAGE_SPAN_*` 属性枚举 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/image_span.d.ts` | 动态 `ImageSpanInterface`、`ImageSpanAttribute`、`ImageCompleteCallback`、`ImageLoadResult` 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/imageSpan.static.d.ets` | 静态 `ImageSpan` 组件属性声明 |
| Modifier (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/ImageSpanModifier.d.ts` | `ImageSpanModifier extends ImageSpanAttribute implements AttributeModifier` |
| Modifier (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/ImageSpanModifier.static.d.ets` | 静态 Modifier 声明 |
| CAPI / NDK | `interfaces/native/native_node.h` | `ARKUI_NODE_IMAGE_SPAN` + `NODE_IMAGE_SPAN_SRC`/`VERTICAL_ALIGNMENT`/`ALT`/`BASELINE_OFFSET`/`COLOR_FILTER`/`SUPPORT_SVG2` 枚举 |

API 检索建议：

- 属性声明：搜索 `ImageSpanAttribute` 与属性名（`verticalAlign`/`objectFit`/`colorFilter`/`alt`/`supportSvg2`/`textBackgroundStyle`/`baselineOffset`）。
- 事件：`onComplete`/`onError`（@since 12 dynamic / 23 static）；通用事件仅继承 `onClick`/`onHover`。
- 版本演进：dynamic 自 API 10，colorFilter @since 14，alt/onComplete/onError @since 12，supportSvg2 @since 22；static 全量 @since 23，supportSvg2 @since 24。
- NDK 仅暴露六属性枚举（SRC/VERTICAL_ALIGNMENT/ALT/BASELINE_OFFSET/COLOR_FILTER/SUPPORT_SVG2）；`objectFit`/`onComplete`/`onError`/`borderRadius` 不经 NDK `NODE_IMAGE_SPAN_*` 暴露。

### API 解析实现路径

ImageSpan 已部分组件化：创建仍走 JSView，但 ArkTS-native 属性与 C-API 经动态模块 "span" 承载。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式创建） | `frameworks/bridge/declarative_frontend/jsview/js_image.cpp` | `JSImage::CreateImageSpan()` → `CreateImage(info, isImageSpan=true)` → `ImageModel` |
| 统一 Bridge（ArkTS-native 属性） | `frameworks/core/components_ng/pattern/text/span/bridge/image_span/arkts_native_image_span_bridge.cpp` | `ImageSpanBridge::SetXxx()` → `ImageSpanView::SetXxx()` |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/text/span/bridge/image_span/image_span_dynamic_modifier.cpp` | 运行时加载的动态属性路径 |
| Static Modifier | `frameworks/core/components_ng/pattern/text/span/bridge/image_span/image_span_static_modifier.cpp` | 静态编译路径（非穿戴形态） |
| Dynamic Module | `frameworks/core/components_ng/pattern/text/span/bridge/image_span/image_span_dynamic_module.cpp` | `ImageSpanDynamicModule : DynamicModule`，模块名 "span"，`libarkui_span.z.so` 入口 |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/node_image_span_modifier.cpp` | 经 `DynamicModuleHelper` 转发到动态模块 |
| C API（NDK）生成桩 | `frameworks/core/interfaces/native/implementation/image_span_modifier.cpp` | 桩实现，加载 `GetDynamicModule("ImageSpan")` |
| 前端 Modifier（ArkTS 侧） | `frameworks/bridge/declarative_frontend/ark_modifier/src/image_span_modifier.ts` | ArkTS `ImageSpanModifier` 类定义 |

独立 so 名称：`libarkui_span.z.so`（与 SymbolSpan 共享 "span" 动态模块）。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 图片/PixelMap | `frameworks/core/components_ng/render/adapter/pixelmap_image.*`、`pattern/image/image_layout_algorithm.*` | `foundation/multimedia/image_framework` | `interfaces/innerkits/include/pixel_map.h` | ImageSpan 图像源解码与 PixelMap 承载 |
| 排版/占位符 | `frameworks/core/components_ng/render/paragraph.h`、`render/adapter/txt_paragraph.*` | `foundation/graphic/graphic_2d` | `frameworks/text/interface/export/rosen_text/export/rosen_text/typography*.h` | `Paragraph::AddPlaceholder` 预留图像占位符槽位 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/text/` | `span_*_test_ng.cpp` 覆盖 ImageSpan 节点/属性行为 |
| Spec 功能域 | `specs/05-ui-components/09-text-components/06-span-components/` | Span 类功能域设计与验收契约 |
| Spec 总索引 | `specs/index.md` | `05-09-06 Span类` 功能域注册入口 |
| Context registry | `docs/context_registry.json` | ImageSpan 的 KB、Spec、源码、API、测试统一路由 |

### 相关 Spec

Span 类功能域：`specs/05-ui-components/09-text-components/06-span-components/`

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-02 | ImageSpan 图片片段组件 | `Feat-02-image-span-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| ImageSpan 不渲染 | 父级是否为 `Text`/`RichEditor`；`Paragraph::AddPlaceholder` 是否预留槽位 |
| 图片不显示或尺寸异常 | `ImageSpanView::SetSrc`/`SetObjectFit`、`ImageLayoutAlgorithm` 测量、`ImageSpanOptions` 尺寸 |
| 对齐/缩放不符预期 | `ImageSpanView::SetVerticalAlign`/`SetObjectFit`、SDK `ImageSpanAlignment`/`ImageFit` |
| onComplete/onError 不触发 | SDK 事件声明、`ImageSpanView::SetOnComplete`/`SetOnError`、@since 12 |
| NDK 设属性无效 | `NODE_IMAGE_SPAN_*` 仅六属性枚举；objectFit/onComplete/onError 不经 NDK |
| 动态模块加载失败 | `image_span_dynamic_module.cpp`、`DynamicModuleHelper::GetDynamicModule("ImageSpan")` |

## 调试入口

- 创建链路：从 `JSImage::CreateImageSpan` → `CreateImage(isImageSpan=true)` → `ImageSpanNode`（FrameNode+ImagePattern）+ `ImageSpanItem`。
- 属性链路：ArkTS-native 经 `ImageSpanBridge` → `ImageSpanView::SetXxx`；C-API 经动态模块委托。
- 布局链路：`ImageLayoutAlgorithm` 测量图像尺寸 → `Paragraph::AddPlaceholder` 预留槽位 → `ImagePaintMethod` 绘制。
- 回归验证：`test/unittest/core/pattern/text/` 下 `span_*_test_ng.cpp`。

## 相关主题

- `Text`：[docs/kb/components/basic/text.md](text.md)
- `Span`：[docs/kb/components/basic/span.md](span.md)
- `SymbolSpan`：[docs/kb/components/basic/symbol-span.md](symbol-span.md)
- `ContainerSpan`：[docs/kb/components/basic/container-span.md](container-span.md)
- `Image`（ImagePattern 复用源）：`docs/kb/components/media/`