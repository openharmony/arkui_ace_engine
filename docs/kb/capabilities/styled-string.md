# StyledString Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `StyledString`

## 定位

属性字符串（StyledString）是 ArkUI 的程序化属性字符串对象模型，**非 UI 组件**。它由不可变 `StyledString`（C++ `SpanString`）/可变 `MutableStyledString`（C++ `MutableSpanString`）+ 约 14 个 `*Style` 构建类（C++ `SpanBase` 子类）组成，被 Text/RichEditor/TextField 等宿主消费。纯 `components_ng` 能力，无 legacy 路径。行为事实以 SDK 声明、源码、测试与 Spec 为准。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 数据模型（不可变） | `frameworks/core/components_ng/pattern/text/span/span_string.h/.cpp` | `SpanString`，getString/getStyles/equals/subStyledString/fromHtml/toHtml/EncodeTlv/DecodeTlv/13 ToXxxSpan |
| 数据模型（可变） | `frameworks/core/components_ng/pattern/text/span/mutable_span_string.h/.cpp` | `MutableSpanString`，ReplaceString/InsertString/RemoveString/ReplaceSpan/SetStyle/RemoveSpans/ClearAllSpans/ReplaceSpanString + SpanWatcher |
| Span 类型/对象 | `frameworks/core/components_ng/pattern/text/span/span_object.h/.cpp` | `SpanType` 枚举（Font/Decoration/BaselineOffset/LetterSpacing/TextShadow/LineHeight/BackgroundColor/Url/LineSpacing/HalfLeading/Gesture/ParagraphStyle/Image/CustomSpan/ExtSpan=500）+ `SpanBase` 与 14 子类 |
| 序列化 | `frameworks/core/components_ng/pattern/text/span/tlv_util.h/.cpp` | TLV（Type-Length-Value）编解码，marshalling/unmarshalling 回调 |
| 哈希 | `frameworks/core/components_ng/pattern/text/span/span_group_hash_calculator.h/.cpp` | span-group 哈希 |
| 变更值 | `frameworks/core/components_ng/pattern/text/styled_string_change_value.h` | `StyledStringChangeValue`（range/replacementString/previewText） |
| RichEditor 宿主 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.h` | ~40 styled-string 方法 |
| RichEditor 控制器 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_styled_string_controller.h` | setStyledString/getStyledString/onWillChange/onDidChange |
| Undo/Redo | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_undo_manager.h` | `StyledStringUndoManager` |
| RichEditor 事件 | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_event_hub.h` | Will/DidChange 事件 |
| TextField 占位 | `frameworks/core/components_ng/pattern/text_field/text_field_pattern.h` | `SetPlaceholderStyledString` |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Dynamic（核心契约） | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/styled_string.d.ts` | `StyledString`/`MutableStyledString`/`StyledStringKey`/14 `*Style` 类/`ImageAttachment`/`CustomSpan`/`UserDataSpan` |
| 消费者契约（Controller/Listener/LayoutManager） | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/text_common.d.ts` | `StyledStringController`/`StyledStringChangedListener`/`LayoutManager` |
| Text 消费 | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/text.d.ts` | `TextController.setStyledString/getLayoutManager` |
| RichEditor 消费 | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/rich_editor.d.ts` | `RichEditorStyledStringController`/`fromStyledString`/`toStyledString` |
| C API（drawing-typography） | `interfaces/native/native_styled_string.h` | `OH_ArkUI_StyledString_*` + `ArkUI_TextLayoutManager` |
| C API（对象模型 accessor） | `frameworks/core/interfaces/native/implementation/styled_string_accessor.cpp` | `GetStyledStringAccessor`/`ControllerAccessor` |
| C API peer/converter | `frameworks/core/interfaces/native/implementation/styled_string_peer.h`、`styled_string.h` | `Ark_StyleOptions`/`Ark_SpanStyle`/`Ark_StyledStringKey` 转换 |
| ANI（静态 ArkTS） | `frameworks/core/interfaces/native/ani/styled_string_ani_modifier.h/.cpp` | `GetStyledStringAniModifier()` |
| arkoala 模块 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/ani/native/styled_string/styled_string_module.h/.cpp` | 静态 ArkTS ANI 模块 |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件 / 目标路径 | 说明 |
|----------|----------|-----------|-------------------------------|------|
| 排版引擎 | 宿主 `*_layout_algorithm.cpp` + `js_text_layout.cpp` | `graphic_2d` | `rosen/modules/2d_engine/rosen_text/` | Typography 段落排版/测量（LayoutManager） |
| i18n | `styled_string.d.ts` 消费 | i18n | `@ohos.i18n.d.ts` | locale-aware 数字格式化产 StyledString |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单测（数据模型） | `test/unittest/core/pattern/text/span_string_test_ng.cpp`、`span_string_test_two_ng.cpp`、`span_string_test_three_ng.cpp` | SpanString/MutableSpanString/SpanObject 核心 |
| 单测（Span） | `test/unittest/core/pattern/text/span_test_ng.cpp`、`span_node_test_ng.cpp`、`span_sub_test_ng.cpp` | Span 类型与节点 |
| 单测（宿主集成） | `test/unittest/core/pattern/rich_editor/rich_editor_styled_string_*_test_ng.cpp` | RichEditor styled-string 集成 |
| C-API 单测（drawing） | `test/unittest/native_styled_string_test.cpp` | drawing-typography C-API |
| C-API 单测（accessor） | `test/unittest/capi/accessors/styled_string_accessor_test.cpp`、`mutable_styled_string_accessor_test.cpp` | 对象模型 accessor |

### 相关 Spec

| Spec 域 | 路径 | 状态 |
|---------|------|------|
| 属性字符串长期规格 | `specs/05-ui-components/09-text-components/10-attributed-string/` | active（9 个 Feat：容器/TextStyle/装饰排版/背景超链接/ParagraphStyle/GestureStyle/图片自定义UserData/宿主集成/C-API-ANI） |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 样式未生效/区间错 | `span_object.h` SpanType + `MutableSpanString` ReplaceStyle/SetStyle |
| TLV 序列化失败 | `tlv_util.h` EncodeTlv/DecodeTlv；marshalling 回调 @since 18 |
| HTML 往返异常 | `StyledString.fromHtml`(@since 12)/`toHtml`(@since 14) |
| SpanType 与 SDK `StyledStringKey` 不一致 | 内部多 `LineSpacing=8`/`HalfLeading`/`ExtSpan=500`，见 Spec 兼容性风险表 |
| 桥接扩展（strokeWidth/superscript/fontConfigs/textVerticalAlign/shaderStyle/tailIndents）不在公共 .d.ts | `js_span_object.cpp` JSFontSpan/JSParagraphStyleSpan，见 Spec 风险表 |
| 双 C-API 并存（drawing vs 对象模型） | `native_styled_string.h` vs `styled_string_accessor.cpp`，见 Spec 风险表 |

## 调试入口

Dump：宿主 Pattern dump；SpanString 经 `ToJsonValue`/Span 查询。

## 相关主题

- [Text](../components/basic/text.md)（宿主之一）
- [SymbolGlyph](../components/basic/symbol-glyph.md)（共享 Text 排版）
- [RichEditor](../components/basic/rich-editor.md)（最重宿主，若存在）
