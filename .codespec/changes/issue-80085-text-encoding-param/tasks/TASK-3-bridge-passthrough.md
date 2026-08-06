# TASK-3: 桥接层 — JS bridge + Pattern + Model + accessor + C API 贯穿

## 目标

将 encoding 参数从 JS/ArkTS 桥接层和 C API 公共函数贯穿到 ParagraphManager。

## 受影响文件

### JS/ArkTS 桥接层
- `frameworks/core/components_ng/pattern/text/layout_info_interface.h` — 三虚方法 +encoding
- `frameworks/core/components_ng/pattern/text/text_pattern.h/.cpp` — 三 override
- `frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.h/.cpp` — 三 override
- `frameworks/core/components_ng/pattern/text/text_model_ng.cpp` — +encoding
- `frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.cpp` — +encoding
- `frameworks/bridge/declarative_frontend/jsview/js_layout_manager.cpp` — 解析 encoding
- `frameworks/bridge/declarative_frontend/engine/jsEnumStyle.js` — +`TextEncoding` 枚举镜像（`TEXT_ENCODING_UTF8=0`/`TEXT_ENCODING_UTF16=1`，值名与 `text_common.d.ts` 一致），供 ArkTS 应用代码运行期引用
- `frameworks/core/interfaces/native/implementation/layout_manager_accessor.cpp` — 解析 encoding
- `frameworks/core/interfaces/native/utility/converter.h` — AssignCast 声明
- `frameworks/core/interfaces/native/utility/converter_enums.cpp` — AssignCast 实现

### C API 层（ace_engine 内部头与实现）
- `interfaces/native/native_styled_string.h` — 新增 `ArkUI_TextEncoding` 枚举 + 三 `*WithEncoding` 函数声明 @since 26，与 `interface_sdk_c` 公共头保持一致
- `interfaces/native/node/native_node_extented.cpp` — 新增三 `*WithEncoding` 实现（参数 `ArkUI_TextEncoding`）；旧函数传 `ARKUI_TEXT_ENCODING_UTF8`（替换原 `TEXT_ENCODING_UTF8`）
- `frameworks/core/interfaces/arkoala/arkoala_api.h` — ArkUITextModifier/ArkUIRichEditorModifier 三函数指针 +encoding
- `frameworks/core/interfaces/native/node/node_text_modifier.cpp` — 三函数签名 +encoding，传给 TextModelNG
- `frameworks/core/components_ng/pattern/rich_editor/bridge/rich_editor_dynamic_modifier.cpp` — 三函数签名 +encoding，传给 RichEditorModelNG

### C API 层（公共 SDK 头与符号表 — interface_sdk_c 仓）
- `interface_sdk_c/arkui/ace_engine/native/styled_string.h` — 新增 `ArkUI_TextEncoding` 枚举 + 三 `*WithEncoding` 函数声明 @since 26.0.0（en）
- `interface_sdk_c/zh-cn/arkui/ace_engine/native/styled_string.h` — 同上中文版
- `interface_sdk_c/arkui/ace_engine/native/libace.ndk.json` — 新增三 `*WithEncoding` 符号条目 `first_introduced: 26.0.0`

## 实现要点

### JS/ArkTS 桥接层

1. LayoutInfoInterface 三虚方法增加 `TextEncoding encoding = TextEncoding::UTF8`
2. TextPattern/RichEditorPattern override 同步签名并传递给 pManager_/paragraphs_
3. TextModelNG/RichEditorModelNG 增加 encoding 参数传递（默认 UTF8）
4. JSLayoutManager 从 args 解析 encoding（args[2] 或 args[1]）
5. LayoutManagerAccessor 解析 `Opt_TextEncoding` 参数传给 handler
6. Converter 新增 `AssignCast(std::optional<TextEncoding>&, const Ark_TextEncoding&)` 特化
7. `jsEnumStyle.js` 新增 `TextEncoding` 全局枚举镜像（值名 `TEXT_ENCODING_UTF8`/`TEXT_ENCODING_UTF16` 与 `text_common.d.ts` 一致），引擎启动时经 `PreloadJsEnums` 注入全局，使应用代码 `TextEncoding.TEXT_ENCODING_UTF8/UTF16` 在运行期可解析

### C API 层

8. `interface_sdk_c/.../styled_string.h`（en + zh-cn）新增 `ArkUI_TextEncoding` 枚举（`ARKUI_TEXT_ENCODING_UTF8=0`/`ARKUI_TEXT_ENCODING_UTF16=1`）+ 三 `*WithEncoding` 函数声明 @since 26.0.0；ace_engine `interfaces/native/native_styled_string.h` 同步声明
9. `interface_sdk_c/.../libace.ndk.json` 新增三 `*WithEncoding` 符号条目 `first_introduced: 26.0.0`
10. `arkoala_api.h` 中 `ArkUITextModifier`/`ArkUIRichEditorModifier` 三函数指针签名增加 `ArkUI_Int32 encoding`
11. `node_text_modifier.cpp` 三实现函数签名增加 `ArkUI_Int32 encoding`，`static_cast<TextEncoding>` 后传给 TextModelNG
12. `rich_editor_dynamic_modifier.cpp` 三实现函数签名增加 `ArkUI_Int32 encoding`，`static_cast<TextEncoding>` 后传给 RichEditorModelNG
13. `native_node_extented.cpp` 新增三个 `*WithEncoding` 公共函数（参数 `ArkUI_TextEncoding`），透传 encoding 给函数指针；旧函数调用函数指针时传 `ARKUI_TEXT_ENCODING_UTF8`（替换原 `TEXT_ENCODING_UTF8`，避免依赖 graphics 仓枚举）

### 验证

- Host unittest 编译通过
- 现有测试编译通过（因默认参数）
- C API unittest：`*WithEncoding` 函数 UTF16/UTF8 正确性 + 旧函数向后兼容
- 完整 ace_engine 构建 + `linux_unittest_capi` 构建
- 验证 ace_engine 内部头与 interface_sdk_c 公共头中 `ArkUI_TextEncoding` 枚举定义一致
