# Span Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `Span`

## 定位

Span 是 ArkUI 文本类的基础文本片段组件，作为 `Text`/`RichEditor` 的子节点声明一段带独立字体/装饰/行级样式的行内文本。Span 不独立布局或绘制，由父级 Text/RichEditor 的段落管线（`MultipleParagraphLayoutAlgorithm` + `Paragraph`）消费其 `SpanItem` 数据模型统一排版。

Span 类（FuncID 05-09-06）共含 Span/ImageSpan/SymbolSpan/ContainerSpan 四个片段组件，本文档为其中的基础文本 Span。行为事实以 SDK 声明、源码实现、测试和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| SpanNode 节点（UINode+BaseSpan） | `frameworks/core/components_ng/pattern/text/span_node.h` | `SpanNode`（tag `V2::SPAN_ETS_TAG`）、`SpanItem` 数据模型、`BaseSpan` 基类 |
| SpanItem 数据模型 | `frameworks/core/components_ng/pattern/text/span_node.h` | 持有 `FontStyle`/`TextLineStyle` unique_ptr + `lpxFlags_` + TLV 序列化 |
| 样式结构 | `frameworks/core/components_ng/pattern/text/text_styles.h` | `FontStyle`、`TextLineStyle` 属性组定义 |
| Model façade | `frameworks/core/components_ng/pattern/text/span_model.h`、`span_model_ng.h`、`span_model_static.h` | `SpanModel`/`SpanModelNG`/`SpanModelStatic` 创建与属性下发 |
| 属性访问器宏 | `frameworks/core/components_ng/pattern/text/span_node.h` | `DEFINE_SPAN_FONT_STYLE_ITEM`/`DEFINE_SPAN_TEXT_LINE_STYLE_ITEM` 生成类型化属性访问器并触发 `RequestTextFlushDirty` |
| 父级布局消费 | `frameworks/core/components_ng/pattern/text/multiple_paragraph_layout_algorithm.h`、`text_layout_algorithm.h` | 父级消费 `std::list<RefPtr<SpanItem>>` 构建 Paragraph |
| 段落绘制 | `frameworks/core/components_ng/render/paragraph.h`、`render/frameworks/core/components_ng/render/adapter/txt_paragraph.h` | `Paragraph`/`TxtParagraph` 抽象，span 文本经此绘制 |
| C API 生成实现 | `frameworks/core/interfaces/native/implementation/span_modifier.cpp` | `SpanModifier::ConstructImpl` → `SpanModelNG::CreateSpanNode` |
| C API node 层 | `frameworks/core/interfaces/native/node/node_span_modifier.h`、`node_span_modifier.cpp` | `NodeModifier::GetSpanModifier()`/`GetCJUISpanModifier()` |
| C API 枚举 | `interfaces/native/native_node.h` | `ARKUI_NODE_SPAN`、`NODE_SPAN_*` 属性枚举 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/span.d.ts` | 动态 `SpanInterface`、`SpanAttribute`、`TextBackgroundStyle`、`BaseSpan<T>` 声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/span.static.d.ets` | 静态 `Span` 组件、`SpanAttribute` 属性声明 |
| Modifier (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/SpanModifier.d.ts` | `SpanModifier extends SpanAttribute implements AttributeModifier<SpanAttribute>` |
| Modifier (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/SpanModifier.static.d.ets` | 静态 Modifier 声明 |
| CAPI / NDK | `interfaces/native/native_node.h` | `ARKUI_NODE_SPAN` 节点类型 + `NODE_SPAN_*` 属性枚举 |

API 检索建议：

- 属性声明：在 SDK 文件搜索 `SpanAttribute` 与具体属性名（`fontColor`/`fontSize`/`fontStyle`/`fontWeight`/`fontFamily`/`decoration`/`letterSpacing`/`textCase`/`lineHeight`/`textShadow`/`textBackgroundStyle`/`baselineOffset`/`fontVariations`）。
- 事件支持：Span 仅支持 `onClick`（含 `distanceThreshold` overload）与 `onHover`；不支持 `onTouch`/`onKeyEvent`/`onGesture`。
- 版本演进：dynamic 自 API 7，lineHeight @since 10，textShadow/textBackgroundStyle/baselineOffset @since 11，fontWeight/letterSpacing 参数形态 @since 20，font(fontConfigs) @since 24，fontVariations @since 26；static 全量 @since 23。

### API 解析实现路径

Span 组件**尚未进行组件化改造**，属性解析采用 JSView + 直连 C-API 双路径，编译产物在主 `libace_compatible.z.so` 中。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JSView（声明式组件） | `frameworks/bridge/declarative_frontend/jsview/js_span.cpp` | `JSSpan::SetXxx()` → `SpanModel::GetInstance()->SetXxx()` |
| node_modifier 层 | `frameworks/core/interfaces/native/node/node_span_modifier.cpp` | C++ 属性 Set/Reset/Get，由 C API 共用 |
| C API（NDK）生成实现 | `frameworks/core/interfaces/native/implementation/span_modifier.cpp` | `SpanModifier::ConstructImpl` → `SpanModelNG::CreateSpanNode`；非动态模块桩 |
| 前端 Modifier（ArkTS 侧） | `frameworks/bridge/declarative_frontend/ark_modifier/src/span_modifier.ts` | ArkTS `SpanModifier` 类定义 |

Span 无独立 `arkts_native_span_bridge`（ArkTS-native 属性经 JSView 路径）；C-API 实现为真实代码（非动态模块桩），直接调用 `SpanModelNG`。


### 外部依赖入口

Span 无独立布局/渲染层，外部依赖经父级 Text/RichEditor 段落管线承载：

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 排版/段落构建 | `frameworks/core/components_ng/pattern/text/multiple_paragraph_layout_algorithm.*` | `foundation/graphic/graphic_2d` | `frameworks/text/interface/export/rosen_text/export/rosen_text/typography*.h` | Span 文本经父级 Paragraph 排版 |
| 绘制 | `frameworks/core/components_ng/render/adapter/txt_paragraph.*` | `foundation/graphic/graphic_2d` | `frameworks/text/interface/export/rosen_text/export/rosen_text/typography*.h` | TxtParagraph 适配层绘制 span 文本 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/text/` | `span_test_ng.cpp`、`span_node_test_ng.cpp`、`span_accessibility_test_ng.cpp`、`span_color_mode_test_ng.cpp`、`span_sub_test_ng.cpp` 等 Span 行为回归 |
| Spec 功能域 | `specs/05-ui-components/09-text-components/06-span-components/` | Span 类功能域设计与验收契约 |
| Spec 总索引 | `specs/index.md` | `05-09-06 Span类` 功能域注册入口 |
| Context registry | `docs/context_registry.json` | Span 的 KB、Spec、源码、API、测试统一路由 |

### 相关 Spec

Span 类功能域：`specs/05-ui-components/09-text-components/06-span-components/`

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-01 | Span 文本片段组件 | `Feat-01-span-text-spec.md` |
| Feat-02 | ImageSpan 图片片段组件 | `Feat-02-image-span-spec.md` |
| Feat-03 | SymbolSpan 符号片段组件 | `Feat-03-symbol-span-spec.md` |
| Feat-04 | ContainerSpan 容器片段组件 | `Feat-04-container-span-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| Span 不渲染内容 | 父级是否为 `Text`/`RichEditor`（span 不可独立布局）；`MultipleParagraphLayoutAlgorithm` 是否消费 SpanItem |
| 字体/装饰/行高属性不生效 | SDK `SpanAttribute` 属性、`SpanModelNG` 属性写入、`FontStyle`/`TextLineStyle` 属性组 |
| 属性变更未触发重排 | `DEFINE_SPAN_FONT_STYLE_ITEM` 宏、`RequestTextFlushDirty`、`BaseSpan::MarkTextDirty` 传播链 |
| onClick/onHover 不触发 | Span 仅支持这两种通用事件；onTouch/onKeyEvent/onGesture 不支持 |
| SpanModifier 属性不下发 | `span_modifier.ts` 前端 Modifier、`span_modifier.cpp` C-API 生成实现 |

## 调试入口

- 创建链路：从 `JSSpan::Create` → `SpanModelNG::Create` → `SpanNode` 节点与 `SpanItem` 装配。
- 属性链路：从 SDK 属性名定位 `SpanModelNG::SetXxx`，再看 `SpanItem` 的 `FontStyle`/`TextLineStyle` 字段与 `RequestTextFlushDirty` 标记。
- 布局链路：从 `MultipleParagraphLayoutAlgorithm::UpdateParagraphBySpan` 确认 SpanItem 列表消费与 Paragraph 构建。
- 回归验证：优先运行 `test/unittest/core/pattern/text/` 下 `span_*_test_ng.cpp` 定向用例。

## 相关主题

- `Text`：[docs/kb/components/basic/text.md](text.md)
- `ImageSpan`：[docs/kb/components/basic/image-span.md](image-span.md)
- `SymbolSpan`：[docs/kb/components/basic/symbol-span.md](symbol-span.md)
- `ContainerSpan`：[docs/kb/components/basic/container-span.md](container-span.md)