# SymbolSpan Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `SymbolSpan`

## 定位

SymbolSpan 是 ArkUI 文本类的符号字形片段组件，作为 `Text`/`RichEditor` 的子节点在文本行内插入符号资源。SymbolSpan 复用 `SpanNode`（设 `spanItemType = SYMBOL`）并填充 `SymbolStyle`，不存在独立 `SymbolSpanNode`。SymbolSpan 无任何通用事件支持，也无独立 NDK 节点类型。

SymbolSpan 属于 Span 类（FuncID 05-09-06）。行为事实以 SDK 声明、源码实现、测试和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| SpanNode（SYMBOL 类型） | `frameworks/core/components_ng/pattern/text/span_node.h` | `SpanNode` 设 `spanItemType = SYMBOL`，持有 `SymbolStyle` |
| SymbolStyle 结构 | `frameworks/core/components_ng/pattern/text/text_styles.h` | `SymbolStyle`（SymbolSourceInfo/颜色列表/渲染策略/动效策略等） |
| Model façade | `frameworks/core/components_ng/pattern/text/span/symbol_span_model.h`、`symbol_span_model_ng.h`、`symbol_span_model_static.h` | `SymbolSpanModel`/`SymbolSpanModelNG`/`SymbolSpanModelStatic` |
| 符号 pattern（同族非 span） | `frameworks/core/components_ng/pattern/symbol/` | `SymbolModel`/`SymbolEffectOptions`/`SymbolSourceInfo`/`SymbolType`，被 `SymbolStyle` 复用 |
| ArkTS-native Bridge | `frameworks/core/components_ng/pattern/text/span/bridge/symbol_span/arkts_native_symbol_span_bridge.cpp` | `SymbolSpanBridge::JsCreate`/`SetFontColor`/`SetFontSize`/`SetFontWeight`/`SetEffectStrategy`/`SetRenderingStrategy` |
| 动态模块 | `frameworks/core/components_ng/pattern/text/span/bridge/symbol_span/symbol_span_dynamic_module.cpp` | `SymbolSpanDynamicModule`，模块名 "span"，`libarkui_span.z.so` |
| C API 生成桩 | `frameworks/core/interfaces/native/implementation/symbol_span_modifier.cpp` | 桩：经 `DynamicModuleHelper::GetDynamicModule("SymbolSpan")` 加载 |
| C API node 层 | `frameworks/core/interfaces/native/node/node_symbol_span_modifier.h`、`node_symbol_span_modifier.cpp` | `NodeModifier::GetSymbolSpanModifier()` |
| 符号效果 accessors | `frameworks/core/interfaces/native/implementation/` | `appear/disappear/bounce/hierarchical/pulse/replace/scale_symbol_effect_accessor.cpp` 等八种符号效果 C-API accessor |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic API | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/symbol_span.d.ts` | 动态 `SymbolSpanInterface`、`SymbolSpanAttribute`（extends CommonMethod）声明 |
| Static API | `<OH_ROOT>/interface/sdk-js/api/arkui/component/symbolSpan.static.d.ets` | 静态 `SymbolSpanAttribute`（独立 interface，不继承 CommonMethod） |
| Modifier (Dynamic) | `<OH_ROOT>/interface/sdk-js/api/arkui/SymbolSpanModifier.d.ts` | `SymbolSpanModifier extends SymbolSpanAttribute`，constructor `(src?: Resource)` |
| Modifier (Static) | `<OH_ROOT>/interface/sdk-js/api/arkui/SymbolSpanModifier.static.d.ets` | 静态 Modifier 声明 |
| CAPI / NDK | 无独立 NDK 节点类型 | `ARKUI_NODE_SYMBOL_SPAN` 不存在；SymbolSpan 仅经 ArkTS 组件或 styled-string 暴露 |

API 检索建议：

- 属性声明：搜索 `SymbolSpanAttribute` 与属性名（`fontSize`/`fontColor`/`fontWeight`/`effectStrategy`/`renderingStrategy`）。
- 事件：SymbolSpan **不支持任何通用事件**（onClick/onHover/onTouch 均不支持）。
- 版本演进：dynamic 自 API 11，fontColor @crossplatform @since 20，fontWeight(ResourceStr, fontWeightConfigs) @since 26；static 全量 @since 23。
- Static/Dynamic 继承分野：static `SymbolSpanAttribute` 不继承 `CommonMethod`（无通用属性/事件）；dynamic 继承 `CommonMethod` 但文档明确通用事件不支持。

### API 解析实现路径

SymbolSpan 已部分组件化：创建走 ArkTS direct component（非 JSView），ArkTS-native 属性与 C-API 经动态模块 "span" 承载。

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| 前端 TS 定义 | `frameworks/bridge/declarative_frontend/ark_direct_component/src/arksymbolspan.ts` | `JSSymbolSpan` / `ArkSymbolSpanComponent`，调用 `getUINativeModule().symbolSpan.*` |
| 统一 Bridge（ArkTS-native） | `frameworks/core/components_ng/pattern/text/span/bridge/symbol_span/arkts_native_symbol_span_bridge.cpp` | `SymbolSpanBridge::JsCreate` → `SymbolSpanModelNG::Create(unicode)` |
| Dynamic Modifier | `frameworks/core/components_ng/pattern/text/span/bridge/symbol_span/symbol_span_dynamic_modifier.cpp` | 运行时加载的动态属性路径 |
| Static Modifier | `frameworks/core/components_ng/pattern/text/span/bridge/symbol_span/symbol_span_static_modifier.cpp` | 静态编译路径（非穿戴形态） |
| Dynamic Module | `frameworks/core/components_ng/pattern/text/span/bridge/symbol_span/symbol_span_dynamic_module.cpp` | `SymbolSpanDynamicModule`，模块名 "span"，`libarkui_span.z.so` 入口 |
| node_modifier 委托层 | `frameworks/core/interfaces/native/node/node_symbol_span_modifier.cpp` | 经 `DynamicModuleHelper` 转发到动态模块 |
| C API（NDK）生成桩 | `frameworks/core/interfaces/native/implementation/symbol_span_modifier.cpp` | 桩实现，加载 `GetDynamicModule("SymbolSpan")` |
| 前端 Modifier（ArkTS 侧） | `frameworks/bridge/declarative_frontend/ark_modifier/src/symbol_span_modifier.ts` | ArkTS `SymbolSpanModifier` 类定义 |

独立 so 名称：`libarkui_span.z.so`（与 ImageSpan 共享 "span" 动态模块）。SymbolSpan 无独立 NDK 节点类型。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|------------|--------------------------------|------|
| 排版/段落构建 | `frameworks/core/components_ng/pattern/text/multiple_paragraph_layout_algorithm.*` | `foundation/graphic/graphic_2d` | `frameworks/text/interface/export/rosen_text/export/rosen_text/typography*.h` | SymbolSpan 经父级 Paragraph 排版 |
| 符号字体/字形 | `frameworks/core/components_ng/pattern/symbol/` | `foundation/graphic/graphic_2d` | `rosen/modules/2d_engine/rosen_text/` | 符号资源解析与字形渲染 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/text/` | `span_*_test_ng.cpp` 覆盖 SymbolSpan 节点/属性行为 |
| Spec 功能域 | `specs/05-ui-components/09-text-components/06-span-components/` | Span 类功能域设计与验收契约 |
| Spec 总索引 | `specs/index.md` | `05-09-06 Span类` 功能域注册入口 |
| Context registry | `docs/context_registry.json` | SymbolSpan 的 KB、Spec、源码、API、测试统一路由 |

### 相关 Spec

Span 类功能域：`specs/05-ui-components/09-text-components/06-span-components/`

| Feat | 主题 | 文件 |
|------|------|------|
| Feat-03 | SymbolSpan 符号片段组件 | `Feat-03-symbol-span-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| SymbolSpan 不渲染 | 父级是否为 `Text`/`RichEditor`；符号 Resource 是否合法（非法资源不渲染不崩溃） |
| 符号颜色/字号/字重不生效 | `SymbolSpanModelNG::SetFontColor`/`SetFontSize`/`SetFontWeight`、`SymbolStyle` 字段 |
| 渲染/动效策略不生效 | `SymbolSpanModelNG::SetSymbolRenderingStrategy`/`SetSymbolEffect`、SDK `SymbolRenderingStrategy`/`SymbolEffectStrategy` |
| onClick/onHover 等事件无效 | SymbolSpan 不支持任何通用事件（文档明确） |
| NDK 无法创建 SymbolSpan | SymbolSpan 无独立 NDK 节点类型；需经 styled-string 或 ArkTS 组件 |
| 动态模块加载失败 | `symbol_span_dynamic_module.cpp`、`DynamicModuleHelper::GetDynamicModule("SymbolSpan")` |

## 调试入口

- 创建链路：从 `arksymbolspan.ts` → `getUINativeModule().symbolSpan.jsCreate` → `SymbolSpanBridge::JsCreate` → `SymbolSpanModelNG::Create(unicode)` → `SpanNode`(SYMBOL) + `SymbolStyle`。
- 属性链路：ArkTS-native 经 `SymbolSpanBridge::SetXxx` → `SymbolSpanModelNG::SetXxx`。
- 布局链路：`SpanNode` 的 `SpanItem` 被父级 `MultipleParagraphLayoutAlgorithm` 消费。
- 回归验证：`test/unittest/core/pattern/text/` 下 `span_*_test_ng.cpp`。

## 相关主题

- `Text`：`docs/kb/components/basic/text.md`
- `Span`：`docs/kb/components/basic/span.md`
- `ImageSpan`：`docs/kb/components/basic/image-span.md`
- `ContainerSpan`：`docs/kb/components/basic/container-span.md`
- `SymbolGlyph`（独立符号组件，非 span）：`docs/kb/components/basic/`