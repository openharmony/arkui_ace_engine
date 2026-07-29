# 文本通用属性 Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `TextCommonAttributes`

## 定位

文本通用属性是所有文本承载组件（Text/Button/Span/TextInput/TextArea/Search/Marquee/SymbolGlyph/TextClock/TextTimer/SecurityComponent 等）共享的字体、装饰、间距、阴影、自适应缩放等表现层文本样式能力。区别于 05-09-04 Text 组件自身的属性规格，本域聚焦"逐组件声明 + 共享 FontStyle 属性组存储"的通用样式机制。

具体行为、默认值、逐组件适用性矩阵、互斥规则与兼容性说明以对应 SDK 声明、源码实现、测试用例和 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 共享属性存储（FontStyle/TextLineStyle 属性组 + 独立项） | `frameworks/core/components_ng/pattern/text/text_layout_property.h` | 文本通用属性核心数据结构，FontStyle 组任一项变更触发 `propNeedReCreateParagraph_` |
| Text 组件 NG 属性设置入口 | `frameworks/core/components_ng/pattern/text/text_model_ng.cpp` | 字体属性 setter 写入 TextLayoutProperty |
| Text 组件 Static 属性设置入口 | `frameworks/core/components_ng/pattern/text/text_model_static.cpp` | 静态范式 setter |
| Button 独立字体存储 + 同步内部 Text 子节点 | `frameworks/core/components_ng/pattern/button/button_layout_property.h`、`button_model_ng.cpp` | Button 自带默认 FontColor，fontSize 取 Length |
| Marquee 独立字体存储（无 fontStyle） | `frameworks/core/components_ng/pattern/marquee/marquee_layout_property.h`、`marquee_model_ng.cpp` | 无 fontStyle，内部 Text 子节点 |
| Search 字体存储于 TextFieldLayoutProperty | `frameworks/core/components_ng/pattern/search/search_model_ng.cpp` | 经 TextField 子节点委托 |
| SymbolGlyph 直接写 TextLayoutProperty | `frameworks/core/components_ng/pattern/symbol/symbol_model_ng.cpp` | fontColor(Array)/fontSize/fontWeight |
| 渲染转换层（FontWeight vs VariableFontWeight 互斥 + 设备字体权重分类 + px 转换） | `frameworks/core/components/font/constants_converter.cpp` | `ConvertTxtStyle` 是真正的互斥决策点 |
| 主题默认值合并 | `frameworks/core/components_ng/pattern/text/text_styles.cpp` | `CreateTextStyleUsingTheme` |
| 主题默认值定义 | `frameworks/core/components/text/text_theme.h`、`text_theme.cpp` | legacy 主题：FontStyle=NORMAL/FontWeight=NORMAL/TextColor/FontSize |
| 自适应字号算法 | `frameworks/core/components_ng/pattern/text/text_adapt_font_sizer.cpp` | min/max fontSize 配对、3 种 HeightAdaptivePolicy |
| 字符串工具（FontWeight/FontFamily 解析） | `frameworks/core/components/common/properties/text_style.cpp`、`frameworks/bridge/common/utils/utils.h` | ParseFontWeight/ConvertStrToFontFamilies 逗号切分 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| 动态 TextAttribute | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/text.d.ts` | fontColor/fontSize/fontStyle/fontWeight(+变体重载)/fontFamily/decoration/textCase/letterSpacing/lineHeight/baselineOffset/minFontSize/maxFontSize/textShadow/fontFeature/fontVariations/minFontScale/maxFontScale |
| 静态 TextAttribute | `<OH_ROOT>/interface/sdk-js/api/arkui/component/text.static.d.ets` | @since 23 static |
| 共享类型（FontWeight/FontStyle/ResourceColor/FontSettingOptions） | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts`、`enums.d.ts`、`units.d.ts`、`text_common.d.ts` | ResourceColor 实际为 `Color \| number \| string \| Resource`，不含渐变色 |
| C-API 枚举（NODE_FONT_*/NODE_TEXT_*） | `interfaces/native/native_node.h` | NODE_FONT_COLOR/SIZE/STYLE/WEIGHT/FAMILY + NODE_IMMUTABLE_FONT_WEIGHT(@since 15) + NODE_SPAN_FONT/FONT_WEIGHT(@since 24) + NODE_TEXT_DECORATION/CASE/LINE_HEIGHT/LETTER_SPACING/BASELINE_OFFSET/TEXT_SHADOW/FONT_FEATURE/MIN_FONT_SIZE/MAX_FONT_SIZE |
| C-API 转换分发 | `interfaces/native/node/style_modifier.cpp` | SetFontColor/SetFontSize/SetFontStyle/SetFontWeight/SetTextFontFamily + SetImmutableFontWeight + SetSpanFont/SetSpanFontWeight |
| 样式字符串 C-API（@since 24） | `interfaces/native/native_styled_string_descriptor.h`、`interfaces/native/node/span_style_native_impl.cpp` | OH_ArkUI_TextStyle_SetFontColor/Family/Size/Weight/Style |
| Option-object C-API（@since 24） | `interfaces/native/node_attributes/text.h` | OH_ArkUI_FontConfigs/OH_ArkUI_FontWeightConfigs |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|-----------|-------------------------------|------|
| 排版引擎 | `constants_converter.cpp`、`text_layout_algorithm.cpp` | `graphic_2d` | `rosen/modules/2d_engine/rosen_text/` | Typography 段落排版、字形度量 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `test/unittest/core/pattern/text/` | Text 属性设置与段落重建 |
| 单元测试 | `test/unittest/capi/accessors/` | C-API 字体属性 modifier 测试 |

### 相关 Spec

| Spec 域 | 路径 |
|---------|------|
| 功能域 design | `specs/04-common-capability/03-common-attributes/11-text-common-attributes/design.md` |
| Feat-01 核心字体属性 | `specs/04-common-capability/03-common-attributes/11-text-common-attributes/Feat-01-core-font-attributes-spec.md` |
| Feat-02 文本装饰与大小写 | `specs/04-common-capability/03-common-attributes/11-text-common-attributes/Feat-02-text-decoration-case-spec.md` |
| Feat-03 文本间距与度量 | `specs/04-common-capability/03-common-attributes/11-text-common-attributes/Feat-03-text-spacing-metrics-spec.md` |
| Feat-04 文本阴影与 OpenType 特性 | `specs/04-common-capability/03-common-attributes/11-text-common-attributes/Feat-04-text-shadow-opentype-spec.md` |
| Feat-05 自适应字体缩放 | `specs/04-common-capability/03-common-attributes/11-text-common-attributes/Feat-05-adaptive-font-scaling-spec.md` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| fontWeight 静态枚举与 VariableFontWeight 互斥优先级未生效 | `constants_converter.cpp` 的 `ConvertTxtStyle`（运行期决策点），而非 JS 层 setter |
| EnableDeviceFontWeightCategory 三态（未设置/true/false）行为差异 | `constants_converter.cpp`，未设置走静态权重派生路径，显式 true 走设备缩放路径 |
| lineHeightMultiple 与 lineHeight 同时设置仅 multiple 生效 | `constants_converter.cpp`（multiply 覆盖）+ JS/静态/C-API 三层都预设 28px 默认 lineHeight |
| textCase 仅转显示副本不转存储 Content | `text_layout_algorithm.cpp` 拷贝路径 `StringUtils::TransformStrCase` |
| 自适应字号不生效 | `text_adapt_font_sizer.cpp`：min/max 必须配对且 max≥min 且 min>0 |
| C-API NODE_TEXT_TEXT_SHADOW 仅单阴影、fill 未暴露 | 多阴影须用 styled-string `OH_ArkUI_TextShadowStyle`（@since 24） |
| C-API 无 NODE_TEXT_FONT_VARIATIONS | fontVariations 是 ArkTS 独有（@since 26），C-API 暂未补齐 |
| ResourceColor 误用渐变色 | `units.d.ts` 实际定义为 `Color \| number \| string \| Resource`，不含 LinearGradient |

## 调试入口

- 字体属性变更不触发段落重建：检查 `TextLayoutProperty::FontStyle` 组的 `ACE_DEFINE_TEXT_PROPERTY_ITEM_WITH_GROUP` 宏是否设置 `propNeedReCreateParagraph_ = true`
- C-API 静默 no-op：`style_modifier.cpp` 的 `CheckIfAttributeLegal` 非节点严格，不支持节点类型返回 NO_ERROR 而非 106102

## 相关主题

- `Text` 组件（`docs/kb/components/basic/text.md`）— Text 组件自身完整属性规格
- `FontRegistration`（字体注册）— fontFamily 注册与加载管线
