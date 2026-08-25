# 文本通用属性 Context

> 文档版本：v2.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `TextCommonAttributes`

## 定位

文本通用属性域范围严格对齐 `text_common.d.ts` 共享类型文件所声明的文本样式类型，仅覆盖该文件中的样式类型；核心字体属性 API（fontSize/fontColor/fontStyle/fontFamily/fontWeight 直接方法）声明于各组件 `*.d.ts`，属组件级规格（参见 05-09-04 Text 组件规格），不在本域。

覆盖类型：`DecorationStyleResult`(decoration)、`FontSettingOptions`/`FontConfigs`/`FontWeightConfigs`(字体权重配置)、`FontVariation`(字体变体)、`LineSpacingOptions`(行间距)、`SuperscriptStyle`(上下标)、`TextDirection`(文本方向)、`ShaderStyle` 类层级(文本着色器)、`IncrementalUpdatePolicy`(渲染增量更新)，及边界类型(`TextVerticalAlign`/`MaxLinesOptions`/`StrokeJoinStyle`/`ContentTransition` 等)。

具体行为、默认值、逐组件适用性矩阵、互斥规则与兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 共享属性存储（FontStyle/TextLineStyle 属性组，含 TextDecoration*/LineThicknessScale/FontVariations 等） | `frameworks/core/components_ng/pattern/text/text_layout_property.h` | 本域类型的核心数据结构，组内任一项变更触发 `propNeedReCreateParagraph_` |
| 渲染转换层（FontWeight vs VariableFontWeight 互斥 + EnableDeviceFontWeightCategory 三态 + decoration 位 OR 合并 + px 转换） | `frameworks/core/components/font/constants_converter.cpp` | `ConvertTxtStyle`/`ConvertTxtTextDecoration` 是真正决策点 |
| 主题默认值合并 | `frameworks/core/components_ng/pattern/text/text_styles.cpp` | `CreateTextStyleUsingTheme` |
| 主题默认值定义 | `frameworks/core/components/text/text_theme.h`、`text_theme.cpp` | legacy 主题默认值 |
| Span 并行存储 | `frameworks/core/components_ng/pattern/span/span_node.cpp` | DEFINE_SPAN_FONT_STYLE_ITEM + 字体加载回调 |
| TextField 并行存储 | `frameworks/core/components_ng/pattern/text_field/text_field_layout_property.h` | FontStyle 组 |
| C-API 转换分发 | `interfaces/native/node/style_modifier.cpp` | SetTextTextDecoration/SetSpanFont/SetSpanFontWeight |
| C-API 枚举定义 | `interfaces/native/native_node.h` | NODE_TEXT_DECORATION/NODE_SPAN_FONT/FONT_WEIGHT 等 |
| Option-object C-API | `interfaces/native/node_attributes/text.h` | OH_ArkUI_FontConfigs/OH_ArkUI_FontWeightConfigs (@since 24) |
| 样式字符串 C-API | `interfaces/native/native_styled_string_descriptor.h`、`interfaces/native/node/span_style_native_impl.cpp` | OH_ArkUI_DecorationStyle_*/OH_ArkUI_TextStyle_SetFont* (@since 24) |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| 共享文本类型（**本域范围依据**） | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/text_common.d.ts` | DecorationStyleResult/FontSettingOptions/FontConfigs/FontWeightConfigs/FontVariation/LineSpacingOptions/SuperscriptStyle/TextDirection/ShaderStyle 类层级/IncrementalUpdatePolicy |
| StyledString TextStyle 载体 | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/styled_string.d.ts` | 段落级样式：消费 `superscript?`/`textDirection?`/`shaderStyle?`/`fontVariations?` |
| 组件 attribute 方法 | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/text.d.ts`、`search.d.ts`、`rich_editor.d.ts`、`symbolglyph.d.ts` | lineSpacing(@since 12/20)/shaderStyle(@since 20)/textDirection(@since 22/23)/fontVariations(@since 26)/incrementalUpdatePolicy(@since 26) |
| C-API NDK | `interfaces/native/native_node.h` | NODE_TEXT_DECORATION(133)/NODE_SPAN_FONT(2003)/NODE_SPAN_FONT_WEIGHT(2004) |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|-----------|-------------------------------|------|
| 排版引擎 | `constants_converter.cpp` | `graphic_2d` | `rosen/modules/2d_engine/rosen_text/` | Typography 段落排版；`FontVariation` 类型重导出自 `@ohos.graphics.text` |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/text/` | decoration/fontWeight 配置/fontVariation 属性 |
| 单元测试 | `test/unittest/capi/accessors/` | C-API decoration/span font modifier 测试 |

### 相关 Spec

| Spec 域 | 路径 |
|---------|------|
| 功能域 design | `specs/04-common-capability/03-common-attributes/11-text-common-attributes/design.md` |
| Feat-01 文本装饰 DecorationStyleResult | `specs/04-common-capability/03-common-attributes/11-text-common-attributes/Feat-02-text-decoration-case-spec.md`（原 Feat-02，decoration 部分） |
| Feat-02 字体权重配置 FontWeightConfigs | `specs/04-common-capability/03-common-attributes/11-text-common-attributes/Feat-01-core-font-attributes-spec.md`（原 Feat-01，options 对象部分）+ `Feat-05-adaptive-font-scaling-spec.md`（原 Feat-05，enableVariableFontWeight/enableDeviceFontWeightCategory 部分） |
| Feat-03 字体变体 FontVariation | `specs/04-common-capability/03-common-attributes/11-text-common-attributes/Feat-04-text-shadow-opentype-spec.md`（原 Feat-04，fontVariations 部分） |
| Feat-04 行间距 LineSpacingOptions（待补录） | `specs/04-common-capability/03-common-attributes/11-text-common-attributes/design.md` |
| Feat-05 上下标 SuperscriptStyle（待补录） | `specs/04-common-capability/03-common-attributes/11-text-common-attributes/design.md` |
| Feat-06 文本方向 TextDirection（待补录） | `specs/04-common-capability/03-common-attributes/11-text-common-attributes/design.md` |
| Feat-07 文本着色器 ShaderStyle（待补录） | `specs/04-common-capability/03-common-attributes/11-text-common-attributes/design.md` |
| Feat-08 增量更新策略 IncrementalUpdatePolicy（待补录） | `specs/04-common-capability/03-common-attributes/11-text-common-attributes/design.md` |
| Feat-09 边界类型（待归类补录） | `specs/04-common-capability/03-common-attributes/11-text-common-attributes/design.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| `FontWeightConfigs.enableDeviceFontWeightCategory` SDK 默认 true vs C++ 三态不一致 | `constants_converter.cpp` 的 `ConvertTxtStyle`；SDK 层 text_common.d.ts 默认 true，C++ FontStyle 为 std::optional 三态，跨层读取须注意 |
| `FontVariation` 类型来源 | text_common.d.ts 重导出自 `@ohos.graphics.text`；fontVariations(@since 26) 优先级 > fontWeight |
| `lineSpacing` 与 `lineHeight` 区别 | lineSpacing 是行间额外距 + `LineSpacingOptions.onlyBetweenLines`（@since 20，true 不在首末行加距）；lineHeight 是行高绝对值（属组件级，不在本域） |
| 渐变色文本如何设置 | 非 fontColor 重载，经独立 `shaderStyle(shader)` attribute（@since 20）；`ShaderStyle` 类层级 LinearGradientStyle/RadialGradientStyle/ColorShaderStyle |
| 上下标如何设置 | `SuperscriptStyle`（@since 20）非 Text 组件直接 attribute，经 StyledString `TextStyle.superscript`（styled_string.d.ts）消费 |
| 文本布局方向（BiDi） | `TextDirection`（@since 22/23）经 `SearchAttribute.textDirection()`/RichEditor/TextStyle 暴露，DEFAULT 跟随组件布局，AUTO 跟随内容书写方向；区别于 common.d.ts 的布局 `Direction` |
| decoration thicknessScale 内部 vs 公开 | lineThicknessScale 是 C++ 内部存储字段名（FontStyle::LineThicknessScale），公开表面为 thicknessScale 字段（DecorationStyleInterface/DecorationStyleResult） |
| C-API decoration SPAN 忽略 thickness、负值处理三路不同 | `style_modifier.cpp` 的 `SetTextTextDecoration`；SPAN 硬编 1.0，TEXT/SP thickness @since 22/23 |
| 核心字体属性（fontSize/fontColor 等）路由 | 不在本域，属组件级规格（05-09-04 Text 组件规格） |

## 调试入口

- 类型变更不触发段落重建：检查 `TextLayoutProperty::FontStyle` 组的 `ACE_DEFINE_TEXT_PROPERTY_ITEM_WITH_GROUP` 宏是否设置 `propNeedReCreateParagraph_ = true`
- C-API 静默 no-op：`style_modifier.cpp` 的 `CheckIfAttributeLegal` 非节点严格，不支持节点类型返回 NO_ERROR 而非 106102

## 相关主题

- `Text` 组件（`docs/kb/components/basic/text.md`）— 核心字体属性 API（fontSize/fontColor 等）属组件级规格
- `FontRegistration`（字体注册）— fontFamily 注册与加载管线
