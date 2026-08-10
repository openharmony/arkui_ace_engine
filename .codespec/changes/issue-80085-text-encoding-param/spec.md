# 特性规格

## 概述

| 字段 | 内容 |
|------|------|
| 特性名称 | LayoutManager encoding 参数支持 |
| 特性编号 | issue-80085 |
| 所属 FuncID | 05-05-01 |
| 优先级 | P0 |
| 目标版本 | API 26 |
| SIG 归属 | ArkUI |
| 状态 | Draft |
| 复杂度 | 标准 |

为 `LayoutManager` 的 `getCharacterPositionAtCoordinate`、`getGlyphRangeForCharacterRange`、`getCharacterRangeForGlyphRange` 三个接口增加 `encoding` 参数，支持 `TextEncoding.UTF8` 和 `TextEncoding.UTF16` 两种枚举值。同时优化 `ParagraphManager` 中两个方法的逻辑并修复 bug。

## 本次变更范围（Delta）

| 类型 | 内容 | 说明 |
|------|------|------|
| ADDED | C++ `NG::TextEncoding` 枚举（`UTF8=0`/`UTF16=1`，短名） | Ace 仓内部 C++ 枚举，值与 `Drawing::TextEncoding` 一致，便于 `static_cast` |
| ADDED | C API `ArkUI_TextEncoding` 枚举（`ARKUI_TEXT_ENCODING_UTF8=0`/`ARKUI_TEXT_ENCODING_UTF16=1`） | 公共 C SDK 头新增，按 `ARKUI_` 前缀命名规范；不复用 graphics 仓 `OH_Drawing_TextEncoding` |
| ADDED | ParagraphManager 三方法增加 encoding 参数 | 透传 encoding 到 Paragraph → TxtParagraph → Rosen Typography |
| MODIFIED | ParagraphManager::GetGlyphRangeForCharacterRange 逻辑重写 | 去除死代码/控制流混乱、encoding 透传、同段单调用优化、**charLength/glyphLength 累积加 strippedNewLineCount 修复 \n 剥离偏移、边界判定用 effectiveCharLength/effectiveGlyphLength** |
| MODIFIED | ParagraphManager::GetCharacterRangeForGlyphRange 逻辑重写 | 同上对称修复、**glyph 边界判定用 effectiveGlyphLength** |
| MODIFIED | ParagraphManager::GetCharacterPositionAtCoordinate 逻辑修复 | **info.start（UTF-16 码元）与 result.position_（开发者 encoding 单位）混用，UTF-8 下错误**；改为循环累积 charLength（actualCharEnd + strippedNewLineCount），fallback 同理 |
| ADDED | Paragraph 基类 + TxtParagraph 三虚方法增加 encoding 参数 | TxtParagraph 将 Ace TextEncoding 转为 Drawing::TextEncoding 透传给 Rosen |
| ADDED | LayoutInfoInterface 三虚方法增加 encoding 参数 | 接口层贯穿 |
| ADDED | TextPattern / RichEditorPattern override 增加 encoding 参数 | Pattern 层贯穿 |
| ADDED | TextModelNG / RichEditorModelNG 增加 encoding 参数 | Model 层贯穿 |
| ADDED | JS bridge 解析 encoding 参数并传递 | js_layout_manager.cpp |
| ADDED | 动态前端运行时枚举镜像 `TextEncoding` 全局对象（值名 `TEXT_ENCODING_UTF8`/`TEXT_ENCODING_UTF16` 与 d.ts 一致） | frameworks/bridge/declarative_frontend/engine/jsEnumStyle.js（编译为 jsEnumStyle.abc，引擎启动时 PreloadJsEnums 注入全局） |
| ADDED | 静态 modifier bridge 解析 encoding 参数并传递 | layout_manager_accessor.cpp |
| ADDED | node_text_modifier 内部默认传 encoding=UTF8 | C API 路径向后兼容 |
| ADDED | C API 新增带 encoding 参数的三个公共函数 | `OH_ArkUI_TextLayoutManager_*WithEncoding` @since 26.0.0，旧函数 @since 24 不变（内部传 `ARKUI_TEXT_ENCODING_UTF8`） |
| ADDED | C API 内部函数指针签名增加 encoding 参数 | arkoala_api.h 中 ArkUITextModifier/ArkUIRichEditorModifier 三函数指针 |
| ADDED | C API 符号导出表新增三个 `*WithEncoding` 符号 | interface_sdk_c/arkui/ace_engine/native/libace.ndk.json `first_introduced: 26.0.0` |
| ADDED | 静态 API textCommon.static.d.ets 新增 `export declare enum TextEncoding` + 三接口带 `encoding?` 方法重载 | 静态前端接口 |
| ADDED | 动态 API text_common.d.ts 新增 `declare enum TextEncoding` + 三接口带 `encoding?: TextEncoding` 方法重载（旧方法 @since 24 保留） | 动态前端接口；en + zh-cn 同步 |
| ADDED | 公共 C SDK 头新增 `ArkUI_TextEncoding` 枚举 + 三 `*WithEncoding` 函数声明 | interface_sdk_c/arkui/ace_engine/native/styled_string.h（en + zh-cn）；ace_engine/interfaces/native/native_styled_string.h 同步 |
| ADDED | 单元测试 | UTF16 encoding 路径 + 逻辑优化回归 |

## 输入文档

- 需求基线: [proposal.md](../proposal.md)
- 设计文档: [design.md](../design.md)
- 参考实现: `@ohos.graphics.text.d.ts` 中 `Paragraph.getCharacterPositionAtCoordinate(x, y, encoding: drawing.TextEncoding)` 等
- SDK 声明: `interface_sdk-js/api/@internal/component/ets/text_common.d.ts`（动态 API：新增 `declare enum TextEncoding` + 三接口方法重载）、`interface_sdk-js/api/arkui/component/textCommon.static.d.ets`（静态 API：新增 `export declare enum TextEncoding` + 三接口方法重载）
- C API 参考: `interface_sdk_c/arkui/ace_engine/native/styled_string.h`（新增 `ArkUI_TextEncoding` 枚举 + 三 `*WithEncoding` 函数 @since 26.0.0；旧函数 @since 24 不变）、`interface_sdk_c/arkui/ace_engine/native/libace.ndk.json`（新增三个符号条目）
- 现有实现: `paragraph_manager.cpp:211-324`、`txt_paragraph.cpp:439-478`、`js_layout_manager.cpp:260-353`、`native_node_extented.cpp:2048-2139`、`node_text_modifier.cpp:2869-2914`

## 用户故事

### US-1: 使用 UTF-16 编码获取字符位置

作为应用开发者，我想要通过 `getCharacterPositionAtCoordinate(x, y, TextEncoding.TEXT_ENCODING_UTF16)` 获取 UTF-16 码元偏移的位置信息，以便与 `getRectsForRange` 的 UTF-16 计数配套使用。

- **AC-1.1**: WHEN 传入 `TextEncoding.TEXT_ENCODING_UTF16` THEN 返回的 position 为 UTF-16 码元偏移
- **AC-1.2**: WHEN 段落包含 CJK 字符且传入 `TextEncoding.TEXT_ENCODING_UTF16` THEN position 正确对应 UTF-16 码元计数（如中文一字 = 1 码元）
- **AC-1.3**: WHEN 不传 encoding 或传入 `TextEncoding.TEXT_ENCODING_UTF8` THEN 返回 UTF-8 字节偏移（向后兼容）

### US-2: 使用 UTF-16 编码获取字形范围

作为应用开发者，我想要通过 `getGlyphRangeForCharacterRange(range, TextEncoding.TEXT_ENCODING_UTF16)` 传入 UTF-16 字符范围，获取 UTF-16 编码的字形范围和实际字符范围。

- **AC-2.1**: WHEN 传入 `TextEncoding.TEXT_ENCODING_UTF16` THEN 输入 charRange 和返回的 glyphRange/actualCharRange 均为 UTF-16 码元偏移
- **AC-2.2**: WHEN 不传 encoding 或传入 `TextEncoding.TEXT_ENCODING_UTF8` THEN 行为与变更前一致
- **AC-2.3**: WHEN 多段落场景下跨段落传入 range THEN 范围计算正确（修复原 bug）

### US-3: 使用 UTF-16 编码获取字符范围

作为应用开发者，我想要通过 `getCharacterRangeForGlyphRange(range, TextEncoding.TEXT_ENCODING_UTF16)` 传入 UTF-16 字形范围，获取 UTF-16 编码的字符范围和实际字形范围。

- **AC-3.1**: WHEN 传入 `TextEncoding.TEXT_ENCODING_UTF16` THEN 输入 glyphRange 和返回的 charRange/actualGlyphRange 均为 UTF-16 码元偏移
- **AC-3.2**: WHEN 不传 encoding 或传入 `TextEncoding.TEXT_ENCODING_UTF8` THEN 行为与变更前一致
- **AC-3.3**: WHEN 多段落场景下跨段落传入 range THEN 范围计算正确（修复原 bug）

### US-4: C API 使用 UTF-16 编码获取偏移和范围

作为 C/C++ 应用开发者，我想要通过 `OH_ArkUI_TextLayoutManager_*WithEncoding` 系列函数传入 `ArkUI_TextEncoding` 参数，使 C API 也能选择 UTF-8 或 UTF-16 编码。

- **AC-4.1**: WHEN 调用 `OH_ArkUI_TextLayoutManager_GetCharacterPositionAtCoordinateWithEncoding` 传入 `ARKUI_TEXT_ENCODING_UTF16` THEN 返回的 position 为 UTF-16 码元偏移
- **AC-4.2**: WHEN 调用 `OH_ArkUI_TextLayoutManager_GetGlyphRangeForCharacterRangeWithEncoding` 传入 `ARKUI_TEXT_ENCODING_UTF16` THEN 输入 charRange 和返回的 glyphRange/actualCharRange 均为 UTF-16 码元偏移
- **AC-4.3**: WHEN 调用 `OH_ArkUI_TextLayoutManager_GetCharacterRangeForGlyphRangeWithEncoding` 传入 `ARKUI_TEXT_ENCODING_UTF16` THEN 输入 glyphRange 和返回的 charRange/actualGlyphRange 均为 UTF-16 码元偏移
- **AC-4.4**: WHEN 调用旧函数（不带 `WithEncoding` 后缀）THEN 行为与变更前一致（内部默认 `ARKUI_TEXT_ENCODING_UTF8`）
- **AC-4.5**: WHEN 传入 `ARKUI_TEXT_ENCODING_UTF8` 到新函数 THEN 行为与旧函数一致

### US-5: PARAGRAPH_CACHE 多段落 `\n` 剥离偏移修复

作为应用开发者，当 Text 使用属性字符串 + `IncrementalUpdatePolicy::PARAGRAPH_CACHE` 且文本含 `\n` 时，我希望 `getGlyphRangeForCharacterRange` 和 `getCharacterRangeForGlyphRange` 的开发者视角偏移正确匹配段落边界，不因 `\n` 被剥离而错位。

- **AC-5.1**: WHEN 文本为 `"😀12345\n不带大概\nahdkjahkl"` 且 `PARAGRAPH_CACHE` 拆分为 3 段 THEN `GetGlyphRangeForCharacterRange` 的 `charLength` 累积包含被剥离的 `\n` 偏移，第 2 段 start offset（含第 1 段 `\n`）正确匹配到第 2 段（不再错位匹配到第 1 段）
- **AC-5.2**: WHEN 同上场景调用 `GetCharacterRangeForGlyphRange` THEN glyph 边界判定含 `\n` 虚拟位置（`effectiveGlyphLength`），落在 `\n` 间隙的 glyph offset 正确匹配段落；返回的 `charRange` 为开发者视角偏移（含 `\n` 位置），`glyphRange` 也含 `\n` 虚拟位置（段间偏移与 char 空间一致）
- **AC-5.3**: WHEN 跨段落查询含 `\n` 的 range THEN `glyphRange` 含 `\n` 对应的虚拟 glyph 位置（段间间隙），`actualCharRange` 不含 `\n` 位置（`\n` 无字形）
- **AC-5.4**: WHEN 开发者 offset（char 或 glyph）恰好落在 `\n` 位置 THEN `std::min` clamp 到段末边界，退化处理为空或退化 range，不崩溃
- **AC-5.5**: WHEN 文本含 CJK 字符 + `\n` 多段落且 `encoding=UTF8` 调用 `GetCharacterPositionAtCoordinate` THEN 返回 position 为 UTF-8 字节偏移（非 UTF-16 码元），点击第 2 段首字符返回的 position 含第 1 段全部 UTF-8 字节（含 `\n` 字节）

## 验收追溯

| AC ID | 关联规则 | 关联 Task | 验证方式 | 证据 |
|-------|----------|-----------|----------|------|
| AC-1.1 ~ AC-1.3 | FR-1, FR-2, BR-1 | TASK-1, TASK-3 | unittest | 待实现 |
| AC-2.1 ~ AC-2.3 | FR-3, FR-4, BR-2, BR-3 | TASK-1, TASK-3 | unittest | 待实现 |
| AC-3.1 ~ AC-3.3 | FR-5, FR-6, BR-2, BR-3 | TASK-1, TASK-3 | unittest | 待实现 |
| AC-4.1 ~ AC-4.5 | FR-7, FR-8, EX-3 | TASK-3 | capi unittest | 待实现 |
| AC-5.1 ~ AC-5.4 | FR-9, FR-10, BR-7, BR-8 | TASK-1 | unittest | 待实现 |
| AC-5.5 | FR-11, BR-9 | TASK-1 | unittest | 待实现 |

## 业务规则

### BR-1: 编码默认值

`encoding` 参数为可选，默认值为 `TextEncoding.UTF8`。不传 encoding 时行为与变更前完全一致。

### BR-2: encoding 透传给 Rosen Typography

Rosen `Typography` 已原生支持 `TextEncoding` 参数（`typography.h:176-181`）：
- `GetCharacterIndexByCoordinate(x, y, TextEncoding)`
- `GetCharacterRangeForGlyphRange(glyphStart, glyphEnd, &actualGlyphRange, TextEncoding)`
- `GetGlyphRangeForCharacterRange(charStart, charEnd, &actualCharRange, TextEncoding)`

Ace 仓不做内部 UTF-8/UTF-16 转换。`TextEncoding` 参数从 JS bridge 一路透传到 `TxtParagraph`，在 `TxtParagraph` 中将 Ace `TextEncoding` 转为 `Drawing::TextEncoding` 后传给 Rosen 库。Rosen 库内部处理编码转换。

`ParagraphManager` 的 `info.start`/`info.end` 为 UTF-16 码元偏移。多段落逻辑中，encoding 透传给每段的 `Paragraph` 方法，由 Rosen 按指定编码解释输入/输出偏移。

### BR-3: 多段落逻辑优化

原 `GetGlyphRangeForCharacterRange` 和 `GetCharacterRangeForGlyphRange` 逻辑混乱：
1. 用 `CHECK_NULL_RETURN` 宏做流程控制（非 null 检查用途，易混淆）
2. 循环后有死代码：用原始 start/end 调 `paragraphs_.back()` 方法（无意义）
3. `paragraphLength = info.end - info.start`（UTF-16）直接传给底层 API，未区分 encoding

优化后：encoding 参数透传给每段 `Paragraph` 方法，由 Rosen 按指定编码解释。去除死代码和混乱控制流，改用清晰的 return 模式。

### BR-4: GetCharacterRangeForGlyphRange 段末参数 bug 修复

原 `paragraph_manager.cpp:304` 中 `GetCharacterRangeForGlyphRange(start - glyphLength, paragraphLength, encoding)` 使用 `paragraphLength`（UTF-16 码元数）作为字形端点，但该参数应为字形索引。正确值应为 `actualRange.second.end`（段落实际字形数）。

对比 `GetGlyphRangeForCharacterRange:258` 已正确使用 `actualRange.first.end`（段落字符端点）。

### BR-5: 同段落合并单次调用优化

当 start 和 end 落在同一段落时，原实现做 2 次目标 Rosen 调用（start→段末 + 段首→end），可合并为 1 次 `GetXxx(localStart, localEnd, encoding)`。同段场景从 3 次 Rosen 调用（1 元数据 + 2 目标）减为 2 次（1 元数据 + 1 目标）。

### BR-6: 元数据查询 glyphEnd 语义一致化

元数据查询 `GetCharacterRangeForGlyphRange(0, paragraphLength, encoding)` 中 `paragraphLength`（UTF-16 码元）仅作为 glyph end 上界传入，Rosen 自动 clamp 到实际字形数。`paragraphLength` 不用于边界判定或累积（BR-7 修复后改用 `actualCharEnd`/`actualGlyphEnd` + `strippedNewLineCount`）。

### BR-7: PARAGRAPH_CACHE 多段落 `\n` 剥离偏移修复

**场景**：当 Text 使用属性字符串 + `IncrementalUpdatePolicy::PARAGRAPH_CACHE` 时，`ParagraphUtil::ConstructParagraphSpanGroupForHash`（`paragraph_util.cpp:285-314`）按 `\n` 拆分多段落，对非末尾段落最后 span 设置 `needRemoveNewLine=true`（`paragraph_util.cpp:303`）。`SpanItem::GetSpanContent`（`span_node.cpp:1281-1293`）据此在构建段落时剥离末尾 `\n`，导致字体引擎收到的文本比 `info.end - info.start` 少 1 个字符。

**根因**：
- `child->length = child->content.length()`（`multiple_paragraph_layout_algorithm.cpp:1072`、`text_layout_algorithm.cpp:487`）含 `\n`
- `spanTextLength += child->length`（同上）含 `\n`
- `info.start`/`info.end` 基于 `spanTextLength`（`text_layout_algorithm.cpp:613-636`、`multiple_paragraph_layout_algorithm.cpp:1040-1041`）含 `\n`
- 但 `ParagraphManager::GetGlyphRangeForCharacterRange`（`paragraph_manager.cpp:288`）和 `GetCharacterRangeForGlyphRange`（`paragraph_manager.cpp:342`）用 `actualRange.first.end`（字体引擎返回的实际字符数，**不含** `\n`）累积 `charLength`
- 开发者传入的 start/end 基于原始文本（含 `\n`），但 `charLength` 不含 `\n`，导致段间偏移错位 1，后续段落匹配到错误段落

**修复**：`charLength` 和 `glyphLength` 累积均加 `strippedNewLineCount`（被剥离的 `\n` 个数）。`\n` 在 UTF-8/UTF-16/glyph 三空间各占 1 位，`strippedNewLineCount` 是单位无关的纯计数。计算方式：**非末尾段固定为 1**（所有分割路径仅在 `\n` 处分割，非末尾段必剥离 1 个 `\n`）；**末尾段固定为 0**（末尾段不剥离 `\n`）。不使用 `paragraphLength`（UTF-16 码元，在 UTF-8 encoding 下与开发者偏移单位不一致）。char 边界判定用 `effectiveCharLength`（= `actualCharEnd + strippedNewLineCount`），glyph 边界判定用 `effectiveGlyphLength`（= `actualGlyphEnd + strippedNewLineCount`），两函数完全对称。传给字体引擎的局部偏移分别 clamp 到 `actualCharEnd`/`actualGlyphEnd`（避免 `\n` 位置越界）。

### BR-8: `\n` 位置的退化处理

当开发者 offset（char 或 glyph）恰好落在被剥离的 `\n` 位置时（local offset = `actualCharEnd` 或 `actualGlyphEnd`），字体引擎无对应字形。处理策略：`std::min(offset, actualCharEnd)` / `std::min(offset, actualGlyphEnd)` 将 local offset clamp 到段末边界，字体引擎返回退化/空 range，不崩溃，不影响非 `\n` 位置的正确性。两函数均需退化处理（glyph 空间也含 `\n` 虚拟位置，`GetCharacterRangeForGlyphRange` 的输入 glyph offset 可落在 `\n` 间隙）。

### BR-9: GetCharacterPositionAtCoordinate `info.start` 单位混用修复

**场景**：`GetCharacterPositionAtCoordinate` 在 y 坐标遍历找到目标段落后，执行 `finalResult.position_ = result.position_ + info.start`。`info.start` 始终为 UTF-16 码元（源自 `spanTextLength` 累积 `child->content.length()`，`child->content` 为 `std::u16string`），但 `result.position_` 的单位取决于 encoding 参数：UTF-16 时为码元，UTF-8 时为字节。

**根因**：
- UTF-16 encoding：`result.position_`（UTF-16 码元）+ `info.start`（UTF-16 码元）= 正确
- UTF-8 encoding：`result.position_`（UTF-8 字节）+ `info.start`（UTF-16 码元）= **单位混用，结果错误**
- 示例：文本 `"你好\n世界"`，点击 Para 1 '世'（local pos=0），`result.position_=0`，`info.start=3`（UTF-16 码元），求和=3，但 UTF-8 正确值为 7（"你好\n" = 6+1 字节）
- fallback（line 258）：`finalResult.position_ = info.end` 同样是 UTF-16 码元，UTF-8 下错误

**修复**：在 y 坐标遍历循环中累积 `charLength`（开发者 encoding 单位），每段累积 `actualCharEnd + strippedNewLineCount`（同 FR-9/FR-10），替代直接用 `info.start`/`info.end`。代价：目标段之前每段多 1 次元数据 Rosen 调用。

## 功能规则

### FR-1: TextEncoding 枚举定义

在 `paragraph.h` 中定义（Ace 仓自定义，不复用 graphics 仓 `drawing.TextEncoding`）：
```cpp
enum class TextEncoding : int32_t { UTF8 = 0, UTF16 = 1 };
```
值与 `Drawing::TextEncoding`（`font_types.h`: UTF8=0, UTF16=1）一致，便于 `static_cast` 转换。

### FR-2: ParagraphManager 三方法透传 encoding

三方法签名增加 `TextEncoding encoding = TextEncoding::UTF8`，将 encoding 透传给 `info.paragraph->GetXxx(..., encoding)`。不在 ParagraphManager 层做 UTF-8/UTF-16 转换。

### FR-3: ParagraphManager::GetGlyphRangeForCharacterRange 逻辑重写

去除末尾死代码（原 `paragraph_manager.cpp:275-279`）、去除 `CHECK_NULL_RETURN` 控制流、改用清晰 flag + break。encoding 透传给每段 `GetGlyphRangeForCharacterRange` 和 `GetCharacterRangeForGlyphRange` 调用。

### FR-4: 去除原 GetGlyphRangeForCharacterRange 末尾死代码

原 `paragraph_manager.cpp:275-279` 在循环后用原始 start/end 调 `paragraphs_.back()` 的方法，属于死代码/错误路径，删除。

### FR-5: ParagraphManager::GetCharacterRangeForGlyphRange 逻辑重写

对称于 FR-3，encoding 透传。删除末尾死代码（原 `paragraph_manager.cpp:319-323`）。

### FR-6: TxtParagraph 将 Ace TextEncoding 转为 Drawing::TextEncoding

`TxtParagraph` 三方法将 Ace `TextEncoding` 参数 `static_cast<Drawing::TextEncoding>` 后传给 Rosen `Typography` 方法。Rosen 库内部处理编码转换。

### FR-7: C API 新增带 encoding 参数的公共函数

在 `interfaces/native/native_styled_string.h` 中新增三个 C API 函数（`@since 26`），签名增加 `OH_Drawing_TextEncoding encoding` 参数：
- `OH_ArkUI_TextLayoutManager_GetCharacterPositionAtCoordinateWithEncoding`
- `OH_ArkUI_TextLayoutManager_GetGlyphRangeForCharacterRangeWithEncoding`
- `OH_ArkUI_TextLayoutManager_GetCharacterRangeForGlyphRangeWithEncoding`

复用 graphics 仓 `OH_Drawing_TextEncoding` 枚举（`drawing_types.h`: UTF8=0, UTF16=1, UTF32=2, GLYPH_ID=3），不新增 C 侧枚举类型。旧函数（@since 24）签名不变，内部默认传 UTF8。

### FR-8: C API 内部函数指针签名增加 encoding 参数

`frameworks/core/interfaces/arkoala/arkoala_api.h` 中 `ArkUITextModifier` 和 `ArkUIRichEditorModifier` 结构体的三处函数指针签名增加 `ArkUI_Int32 encoding` 参数（内部结构体，非公开 API）：
- `getCharacterPositionAtCoordinate(node, dx, dy, encoding)` 
- `getGlyphRangeForCharacterRange(node, start, end, encoding, range)` 
- `getCharacterRangeForGlyphRange(node, start, end, encoding, range)` 

`node_text_modifier.cpp` 和 `rich_editor_dynamic_modifier.cpp` 中三处实现接收 `ArkUI_Int32 encoding`，通过 `static_cast<TextEncoding>(encoding)` 转为 Ace `TextEncoding` 后传给 `TextModelNG`/`RichEditorModelNG`。

`native_node_extented.cpp` 中：旧公共函数调用函数指针时传 `TEXT_ENCODING_UTF8`（即 0）；新公共函数调用函数指针时透传用户指定的 encoding 值。

### FR-9: GetGlyphRangeForCharacterRange `\n` 剥离偏移修复

在 `ParagraphManager::GetGlyphRangeForCharacterRange` 的多段落循环中：

1. **charLength 累积含 `\n`**：`charLength += actualCharEnd + strippedNewLineCount`，替代原 `charLength += actualRange.first.end`（不含 `\n`）。确保 `charLength` 与开发者视角偏移一致。
2. **字符边界判定含 `\n`**：start/end 落段判断用 `effectiveCharLength`（= `actualCharEnd + strippedNewLineCount`），使含 `\n` 的开发者偏移正确匹配到目标段落。
3. **glyphLength 累积含 `\n` 虚拟位置**：`glyphLength += actualGlyphEnd + strippedNewLineCount`，使段间 glyph 偏移与 char 偏移一致。
4. **局部偏移 clamp**：传给字体引擎的 local char offset 用 `std::min(offset, actualCharEnd)` clamp，避免 `\n` 位置越界。
5. **返回值映射**：`charRange` 用 `charLength`（含 `\n`）做全局映射，`glyphRange` 用 `glyphLength`（含 `\n` 虚拟位置）做全局映射。

### FR-10: GetCharacterRangeForGlyphRange `\n` 剥离偏移修复

在 `ParagraphManager::GetCharacterRangeForGlyphRange` 的多段落循环中，对称于 FR-9：

1. **charLength 累积含 `\n`**：`charLength += actualCharEnd + strippedNewLineCount`，同 FR-9。
2. **glyphLength 累积含 `\n` 虚拟位置**：`glyphLength += actualGlyphEnd + strippedNewLineCount`，同 FR-9。
3. **glyph 边界判定含 `\n` 虚拟位置**：start/end 落段判断用 `effectiveGlyphLength`（= `actualGlyphEnd + strippedNewLineCount`），对称于 FR-9 的 char 边界。`GetGlyphRangeForCharacterRange` 返回的 glyphRange 使用 `glyphLength`（含 `\n` 虚拟位置）做全局映射，故输入 `GetCharacterRangeForGlyphRange` 的 glyph offset 也含 `\n` 虚拟位置，边界判定必须包含。
4. **局部偏移 clamp**：传给字体引擎的 local glyph offset 用 `std::min(offset, actualGlyphEnd)` clamp，避免 `\n` 虚拟位置越界。
5. **返回值映射**：`charRange` 用 `charLength`（含 `\n`）做全局映射，`glyphRange` 用 `glyphLength`（含 `\n` 虚拟位置）做全局映射。

### FR-11: GetCharacterPositionAtCoordinate `info.start` 单位混用修复

在 `ParagraphManager::GetCharacterPositionAtCoordinate` 的 y 坐标遍历循环中：

1. **累积 charLength**：遍历段落时累积 `charLength += actualCharEnd + strippedNewLineCount`（开发者 encoding 单位），替代直接用 `info.start`（UTF-16 码元）。
2. **返回值映射**：`finalResult.position_ = result.position_ + charLength`，`result.position_` 与 `charLength` 同为开发者 encoding 单位。
3. **fallback 修复**：原 `finalResult.position_ = info.end`（UTF-16 码元）改为 `finalResult.position_ = charLength + actualCharEnd`（开发者 encoding 单位）。
4. **元数据查询**：遍历时每段调 `ComputeParagraphMetadata` 获取 `actualCharEnd`/`strippedNewLineCount`，代价为目标段之前每段多 1 次 Rosen 元数据调用。

## 异常/豁免规则

### EX-1: encoding 参数无效值

传入不合法的 encoding 值时，按默认 UTF8 处理，不抛异常。

### EX-2: 空段落

`paragraphs_` 为空时返回空 range（`{0,0}` / `{-1,-1}`），行为与原实现一致。

### EX-3: C API 路径

C API `OH_ArkUI_TextLayoutManager_*` 旧函数（@since 24）签名不变，内部调用时使用默认 `TextEncoding::UTF8`，行为与变更前一致。

新增三个带 encoding 参数的 C API 函数（@since 26）：
- `OH_ArkUI_TextLayoutManager_GetCharacterPositionAtCoordinateWithEncoding(layoutManager, dx, dy, OH_Drawing_TextEncoding encoding, outPos)`
- `OH_ArkUI_TextLayoutManager_GetGlyphRangeForCharacterRangeWithEncoding(layoutManager, charRange, OH_Drawing_TextEncoding encoding, outGlyphRange, outActualCharRange)`
- `OH_ArkUI_TextLayoutManager_GetCharacterRangeForGlyphRangeWithEncoding(layoutManager, glyphRange, OH_Drawing_TextEncoding encoding, outCharRange, outActualGlyphRange)`

新函数复用 graphics 仓已定义的 `OH_Drawing_TextEncoding` 枚举（`drawing_types.h`: UTF8=0, UTF16=1, UTF32=2, GLYPH_ID=3），不新增枚举类型。Ace 仓内部将 `OH_Drawing_TextEncoding` 通过 `static_cast<TextEncoding>()` 转为 Ace `TextEncoding` 后透传给 ModelNG。

## 验证映射

| 编号 | 对应规格项 | 验证方式 | 验证重点 |
|------|------------|----------|----------|
| VM-1 | US-1 全 AC | Host unittest | UTF16 偏移正确性，CJK 场景 |
| VM-2 | US-2 全 AC | Host unittest | UTF16 输入/输出正确性，多段落 |
| VM-3 | US-3 全 AC | Host unittest | UTF16 输入/输出正确性，多段落 |
| VM-4 | AC-1.3, AC-2.2, AC-3.2 | Host unittest | UTF8 向后兼容回归 |
| VM-5 | US-4 全 AC (AC-4.*) | CAPI unittest | C API *WithEncoding 函数 UTF16/UTF8 正确性，旧函数向后兼容 |
| VM-6 | US-5 全 AC (AC-5.1~5.4) | Host unittest | PARAGRAPH_CACHE 多段落 `\n` 剥离偏移修复，charLength/glyphLength 均含 `\n`，边界判定用 effectiveCharLength/effectiveGlyphLength |
| VM-7 | AC-5.5 | Host unittest | GetCharacterPositionAtCoordinate UTF-8 下 position 为字节偏移（非 UTF-16 码元），info.start 不再混用 |

## API 变更分析

### 变更 API

| API 名称 | 类型 | 变更内容 | 关联 AC |
|----------|------|----------|---------|
| `getCharacterPositionAtCoordinate(x, y, encoding?)` | Dynamic + Static | 新增可选参数 encoding | AC-1.* |
| `getGlyphRangeForCharacterRange(charRange, encoding?)` | Dynamic + Static | 新增可选参数 encoding | AC-2.* |
| `getCharacterRangeForGlyphRange(glyphRange, encoding?)` | Dynamic + Static | 新增可选参数 encoding | AC-3.* |
| `OH_ArkUI_TextLayoutManager_GetCharacterPositionAtCoordinateWithEncoding(...)` | C API | 新增函数 @since 26 | AC-4.* |
| `OH_ArkUI_TextLayoutManager_GetGlyphRangeForCharacterRangeWithEncoding(...)` | C API | 新增函数 @since 26 | AC-4.* |
| `OH_ArkUI_TextLayoutManager_GetCharacterRangeForGlyphRangeWithEncoding(...)` | C API | 新增函数 @since 26 | AC-4.* |

> 动态 API `.d.ts` 已声明 `@since 26.0.0`。静态 API `.static.d.ets` 需同步补齐。C API 新函数 `@since 26`。

### 新增 API

C API 新增三个带 `OH_Drawing_TextEncoding` 参数的函数（`@since 26`），复用 graphics 仓已定义的 `OH_Drawing_TextEncoding` 枚举。

## 兼容性声明

- **已有 API 行为变更:** 否 — encoding 为可选参数，默认 UTF8，不传时行为不变；C API 旧函数不变
- **配置文件格式变更:** 否
- **数据存储格式变更:** 否
- **最低支持版本:** API 26
- **向后兼容:** encoding 参数可选，不传时 UTF8 行为与变更前一致；C API 旧函数（@since 24）签名和行为不变
- **动态/静态/C API 一致性:** 动态、静态、C API 三通道行为完全一致

## 架构约束

| 关键约束 | 约束说明 | 影响 AC |
|----------|----------|---------|
| C API 旧函数签名不变 | `OH_ArkUI_TextLayoutManager_*`（@since 24）签名不变，内部默认 UTF8；新增 `*WithEncoding` 函数（@since 26） | EX-3, FR-7 |
| C API 复用 graphics 枚举 | C API 使用 `OH_Drawing_TextEncoding`（drawing_types.h），不新增 C 侧枚举 | FR-7 |
| 内部函数指针可改签名 | `arkoala_api.h` 中 `ArkUITextModifier`/`ArkUIRichEditorModifier` 函数指针签名可改（非公开 API） | FR-8 |
| Ace 仓自定义枚举 | 不复用 graphics 仓 `drawing.TextEncoding`；值与 `Drawing::TextEncoding` 一致便于 `static_cast` | FR-1, FR-6 |
| encoding 透传 | TextEncoding 从 JS bridge / C API 透传到 Rosen Typography，不在 ArkUI 内部做 UTF-8/UTF-16 转换 | BR-2, FR-2~8 |

## 非功能性需求

| 类型 | 指标/阈值 | 验证方式 | 证据 |
|------|-----------|----------|------|
| 性能 | UTF-16 转换不引入显著延迟（O(n) 子串转换） | 代码审查 + benchmark | 参考已有 UtfUtils 性能 |
| 可靠性 | 无效 encoding 不崩溃 | unittest | EX-1 覆盖 |
| 正确性 | CJK 字符偏移转换正确 | unittest | AC-1.2, AC-2.1, AC-3.1 |
| 正确性 | C API *WithEncoding 函数 UTF16 正确 | capi unittest | AC-4.1~4.3 |
| 兼容性 | C API 旧函数行为不变 | capi unittest | AC-4.4 |

## 全局特性影响

| 特性 | 适用？ | 结论 | 关联场景 |
|------|--------|------|----------|
| 无障碍 | 否 | 偏移编码不影响无障碍 | N/A |
| 大字体 | 否 | 无文本渲染变更 | N/A |
| 深色模式 | 否 | 不感知主题 | N/A |
| 多窗口/分屏 | 否 | 不感知窗口 | N/A |
| 多用户 | 否 | 不涉及用户数据 | N/A |
| 版本升级 | 是 | API 26 新可选参数 + C API 新函数，向前兼容 | encoding 默认 UTF8；C API 旧函数不变 |
| 生态兼容 | 是 | 新增可选参数/新函数不破坏已有 API | 动态/静态/C API 三通道一致 |

## 行为场景（Gherkin）

```gherkin
Feature: LayoutManager encoding 参数支持
  作为 应用开发者
  我想要 通过 encoding 参数选择 UTF-16 编码
  以便 与 getRectsForRange 等 UTF-16 API 配套使用

  Scenario: UTF-16 编码获取字符位置
    Given 段落文本 "你好world" (UTF-16 码元数=7, UTF-8 字节数=11)
    When 调用 getCharacterPositionAtCoordinate(x, y, TextEncoding.UTF16)
    Then 返回 position 为 UTF-16 码元偏移
    And position 值与 getRectsForRange 的 UTF-16 计数一致

  Scenario: UTF-8 向后兼容
    Given 段落文本 "你好world"
    When 调用 getCharacterPositionAtCoordinate(x, y) 不传 encoding
    Then 返回 position 为 UTF-8 字节偏移
    And 行为与变更前一致

  Scenario: UTF-16 编码跨段落字形范围
    Given 两段段落，第一段 "你好" 第二段 "world"
    When 调用 getGlyphRangeForCharacterRange({start:0, end:7}, TextEncoding.UTF16)
    Then 返回 glyphRange 和 actualCharRange 均为 UTF-16 码元偏移
    And 跨段落范围正确

  Scenario: 修复原多段落 bug
    Given 两段段落包含 CJK 字符
    When 调用 getGlyphRangeForCharacterRange 传任意 encoding
    Then 段落边界使用正确的编码计算（不再将 UTF-16 长度当 UTF-8 使用）

  Scenario: C API UTF-16 编码获取字符位置
    Given 段落文本 "你好world"
    When 调用 OH_ArkUI_TextLayoutManager_GetCharacterPositionAtCoordinateWithEncoding(x, y, TEXT_ENCODING_UTF16)
    Then 返回 position 为 UTF-16 码元偏移

  Scenario: C API 旧函数向后兼容
    Given 段落文本 "你好world"
    When 调用 OH_ArkUI_TextLayoutManager_GetCharacterPositionAtCoordinate(x, y)（旧函数）
    Then 返回 position 为 UTF-8 字节偏移（行为与变更前一致）
```

## Spec 自审清单

- [x] 无"待定""TBD""TODO"等占位符
- [x] 所有 AC 使用 WHEN/THEN 格式，可独立测试
- [x] 范围边界明确（接口 + C++ + 桥接 + 测试）
- [x] 无语义模糊表述
- [x] AC 与业务规则/异常规则交叉一致
- [x] 参考已有实现和 UtfUtils，每条 FR 有对应源码路径
