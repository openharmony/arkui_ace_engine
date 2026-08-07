# 执行计划

> 变更 ID: issue-80085-text-encoding-param

## Task 拆分

| Task ID | 目标 | 受影响文件 | 依赖 |
|---------|------|------------|------|
| TASK-1 | 核心层: TextEncoding 枚举 + ParagraphManager encoding 参数 + 转换工具 + 逻辑重写 + Paragraph/TxtParagraph 虚方法 | paragraph_manager.h/.cpp, paragraph.h, txt_paragraph.h/.cpp, mock_paragraph.h | 无 |
| TASK-2 | 接口层: 静态 API textCommon.static.d.ets + 动态 API text_common.d.ts 补齐 TextEncoding 枚举 + encoding 参数（en + zh-cn） | textCommon.static.d.ets, text_common.d.ts, zh-cn/text_common.d.ts | TASK-1 |
| TASK-3 | 桥接层: JS bridge + LayoutInfoInterface + Pattern + Model + 静态 accessor + C API 公共函数/内部函数指针/实现 + 运行时枚举镜像 | layout_info_interface.h, text_pattern.*, rich_editor_pattern.*, text_model_ng.cpp, rich_editor_model_ng.cpp, js_layout_manager.*, layout_manager_accessor.cpp, node_text_modifier.cpp, rich_editor_dynamic_modifier.cpp, arkoala_api.h, native_node_extented.cpp, native_styled_string.h, jsEnumStyle.js | TASK-1 |
| TASK-3b | C SDK 公共头与符号表: interface_sdk_c 新增 ArkUI_TextEncoding 枚举 + 三 *WithEncoding 函数 + libace.ndk.json 符号注册（en + zh-cn） | interface_sdk_c/arkui/ace_engine/native/styled_string.h, zh-cn/.../styled_string.h, libace.ndk.json | TASK-1 |
| TASK-4 | 编译验证 + 测试 | unittest + ace_engine 构建 | TASK-1~3 |

## 实施顺序

```
TASK-1 (Core: enum + ParagraphManager + Paragraph/TxtParagraph)
  ├── TASK-2 (Static + Dynamic API interface: textCommon.static.d.ets + text_common.d.ts)
  ├── TASK-3 (Bridge: JS + Pattern + Model + accessor + jsEnumStyle)
  └── TASK-3b (C SDK public header + libace.ndk.json)
        └── TASK-4 (Build + Test)
```

## 预计变更量

| 层 | 新增/修改行数 | 说明 |
|----|----------|------|
| paragraph.h | +10 | `NG::TextEncoding` 枚举（短名 UTF8/UTF16）+ 三虚方法 +encoding 参数 |
| txt_paragraph.h | +3 | 三方法签名 |
| txt_paragraph.cpp | +6 | 三方法签名 + `static_cast<Drawing::TextEncoding>` |
| mock_paragraph.h | +3 | mock 签名更新 |
| paragraph_manager.h | +6 | 三方法签名 +encoding（无需转换工具声明） |
| paragraph_manager.cpp | +100/-50 | 三方法透传 encoding + 逻辑重写 + **\n 剥离偏移修复（GetGlyphRangeForCharRange/GetCharRangeForGlyphRange/GetCharacterPositionAtCoordinate 三函数均修复）** + ParagraphMetadata helper + 局部偏移 clamp |
| layout_info_interface.h | +6 | 三虚方法 +encoding |
| text_pattern.h/.cpp | +6 | 三 override +encoding |
| rich_editor_pattern.h/.cpp | +6 | 三 override +encoding |
| text_model_ng.h/.cpp | +6 | +encoding 传递 |
| rich_editor_model_ng.h/.cpp | +6 | +encoding 传递 |
| js_layout_manager.cpp | +30 | 解析 encoding 参数 |
| jsEnumStyle.js | +5 | `TextEncoding` 枚举镜像（`TEXT_ENCODING_UTF8=0`/`TEXT_ENCODING_UTF16=1`，值名与 d.ts 一致），供 ArkTS 运行期引用 |
| layout_manager_accessor.cpp | +15 | 解析 encoding 参数 |
| node_text_modifier.cpp | +12 | 三函数签名 +encoding，`static_cast<TextEncoding>` 传给 TextModelNG |
| rich_editor_dynamic_modifier.cpp | +12 | 三函数签名 +encoding，`static_cast<TextEncoding>` 传给 RichEditorModelNG |
| arkoala_api.h | +6 | ArkUITextModifier/ArkUIRichEditorModifier 三函数指针 +`ArkUI_Int32 encoding` |
| native_node_extented.cpp | +60/-3 | 新增三 `*WithEncoding` 公共函数（参数 `ArkUI_TextEncoding`）；旧函数内部传 `ARKUI_TEXT_ENCODING_UTF8`（替换原 `TEXT_ENCODING_UTF8`） |
| native_styled_string.h (ace_engine) | +50 | 新增 `ArkUI_TextEncoding` 枚举 + 三 `*WithEncoding` 函数声明 @since 26（与 interface_sdk_c 公共头保持一致） |
| styled_string.h (interface_sdk_c, en) | +60 | 新增 `ArkUI_TextEncoding` 枚举 + 三 `*WithEncoding` 函数声明 @since 26.0.0 |
| styled_string.h (interface_sdk_c, zh-cn) | +60 | 同上中文版 |
| libace.ndk.json | +12 | 新增三 `*WithEncoding` 符号条目 `first_introduced: 26.0.0` |
| text_common.d.ts (en) | +60 | 新增 `declare enum TextEncoding`（`TEXT_ENCODING_UTF8/UTF16`）+ 三接口带 `encoding?: TextEncoding` 方法重载 |
| text_common.d.ts (zh-cn) | +60 | 同上中文版 |
| textCommon.static.d.ets | +60 | `export declare enum TextEncoding` + 三接口带 `encoding?: TextEncoding` 方法重载 |
| paragraph_manager_test_ng.cpp | +25 | mock 签名更新 + **PARAGRAPH_CACHE \n 剥离偏移回归测试 + GetCharacterPositionAtCoordinate UTF-8 偏移回归** |
| capi_*_test | +40 | C API `*WithEncoding` UTF16/UTF8 测试（使用 `ARKUI_TEXT_ENCODING_*` 值） |
| **合计** | **~665** | |
