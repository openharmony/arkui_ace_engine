# 需求澄清与基线

## 原始需求

为 `LayoutManager` 的三个接口增加 `encoding` 参数，支持配置 `UTF16` 与 `UTF8` 两种枚举值。枚举不复用 graphics 仓的 `drawing.TextEncoding`，Ace 仓自己增加 `TextEncoding` 枚举。

**涉及接口**（`text_common.d.ts`）：
- `getCharacterPositionAtCoordinate(x, y, encoding?: TextEncoding)`
- `getGlyphRangeForCharacterRange(charRange, encoding?: TextEncoding)`
- `getCharacterRangeForGlyphRange(glyphRange, encoding?: TextEncoding)`

**参考**：`interface_sdk-js/api/@ohos.graphics.text.d.ts` 中同三个接口使用 `drawing.TextEncoding` 枚举。

**背景**：
1. 在此需求前，`getCharacterPositionAtCoordinate` 和 `getGlyphRangeForCharacterRange` 使用默认的 UTF-8 字节偏移编码，导致坐标信息与 `getRectsForRange`（UTF-16 码元计数）无法配套使用。
2. `ParagraphManager::GetGlyphRangeForCharacterRange` 和 `ParagraphManager::GetCharacterRangeForGlyphRange` 代码逻辑混乱且存在 bug，需一并优化。
3. 当 Text 使用属性字符串 + `IncrementalUpdatePolicy::PARAGRAPH_CACHE` 时，`ParagraphUtil::ConstructParagraphSpanGroupForHash`（paragraph_util.cpp:285-314）按 `\n` 拆分多段落，对非末尾段落设置 `needRemoveNewLine=true`（paragraph_util.cpp:303），`SpanItem::GetSpanContent`（span_node.cpp:1281-1293）据此在构建段落时剥离末尾 `\n`，导致字体引擎收到的文本比 `info.end - info.start` 少 1 个字符。但开发者传入的 start/end 是基于原始文本（包含 `\n`）的偏移，`ParagraphManager` 未考虑此差异，导致多段落偏移匹配错位。

## 澄清记录

| 轮次 | 问题 | 回答 | 确认来源 |
|------|------|------|----------|
| 1 | 接口层 text_common.d.ts 是否已有 TextEncoding 枚举？ | 已有（UTF8=0, UTF16=1），动态 API 接口层 d.ts 无需改动 | 代码确认 text_common.d.ts:791-815 |
| 2 | 静态 API textCommon.static.d.ets 是否需要同步？ | 是，需补齐 TextEncoding 枚举和 encoding 参数 | 代码确认 textCommon.static.d.ets:1023-1051 无 encoding |
| 3 | C API (OH_ArkUI_TextLayoutManager_*) 是否需要改签名？ | 否，C API 保持现有签名，内部默认使用 UTF8 | AGENTS.md 硬边界约束 |
| 4 | 枚举值不复用 graphics 仓，Ace 仓自己定义？ | 确认，C++ 层新增 TextEncoding 枚举 | 用户明确要求 |
| 5 | encoding 是否在 ArkUI 内部做 UTF-8/UTF-16 转换？ | 否，TextEncoding 直接透传给 Rosen Typography（已原生支持 encoding 参数），ArkUI 不做内部转换 | 用户修正：Rosen typography.h:176-181 确认 |
| 6 | text_common.d.ts 的 @param encoding JSDoc 是否可引用 getRectsForRange？ | 否，去除 [getRectsForRange] 引用 | 用户修正 |
| 7 | 动态前端运行时是否需要镜像 TextEncoding 枚举？ | 是，需在 `frameworks/bridge/declarative_frontend/engine/jsEnumStyle.js` 补齐 `TextEncoding` 全局枚举对象（`TEXT_ENCODING_UTF8=0`/`TEXT_ENCODING_UTF16=1`，值名与 `text_common.d.ts` 完全一致） | 代码确认：`text_common.d.ts` 中 17 个兄弟 `declare enum` 全部在 `jsEnumStyle.js` 镜像，唯独 `TextEncoding` 缺失；`jsi_declarative_engine.cpp:248, 758, 955, 1784, 3748` 启动时 `PreloadJsEnums` 注入全局；轮次 1 表述"动态 API 接口层无需改动"应限定为"d.ts 声明无需改动"，运行时镜像仍需补齐 |
| 8 | C API 公共头是否复用 graphics 仓 `OH_Drawing_TextEncoding`？ | 否，新增 `ArkUI_TextEncoding` 枚举（`ARKUI_TEXT_ENCODING_UTF8=0`/`ARKUI_TEXT_ENCODING_UTF16=1`）于 `interface_sdk_c/arkui/ace_engine/native/styled_string.h`，ace_engine 内部头 `interfaces/native/native_styled_string.h` 同步声明 | 代码确认：`interface_sdk_c` 已落地（en + zh-cn + libace.ndk.json 三处）；按 OpenHarmony C API 命名规范使用 `ARKUI_` 前缀，避免跨仓枚举依赖；轮次 3 表述"C API 保持现有签名"应限定为"旧函数签名不变"，新 `*WithEncoding` 函数仍需新增 |
| 9 | 动态 API `text_common.d.ts` 是否"已有 TextEncoding 枚举"无需改动？ | 否，原 d.ts 无 `TextEncoding` 枚举也无 `encoding?` 参数；本次需新增 `declare enum TextEncoding`（值名 `TEXT_ENCODING_UTF8`/`TEXT_ENCODING_UTF16`）+ 三接口新增带 `encoding?: TextEncoding` 的方法重载（旧方法 @since 24 保留不变）；en + zh-cn 同步 | 代码确认：`interface_sdk-js` 已落地 diff；轮次 1 表述错误，应更正为"d.ts 无需改动"仅当指 JSDoc 修订，但实际 d.ts 需新增枚举和方法重载 |
| 10 | 公开 SDK 各层枚举值名是否一致？ | 不一致但符合各层命名规范：C++ 内部 `NG::TextEncoding::UTF8/UTF16`（短名）；JS/TS `TextEncoding.TEXT_ENCODING_UTF8/UTF16`（前缀名）；C API `ArkUI_TextEncoding::ARKUI_TEXT_ENCODING_UTF8/UTF16`（`ARKUI_` 前缀名）；三方数值一致（UTF8=0/UTF16=1） | 代码确认三层落地；OpenHarmony 既有惯例（如 `TextAlign` JS=`Start` vs C++=`START`），非本特性引入；运行期通过整数传递和 `static_cast` 完成 |
| 11 | PARAGRAPH_CACHE 多段落 `\n` 剥离场景是否在 encoding 优化中一并修复？ | 是，一并修复。`ConstructParagraphSpanGroupForHash` 对非末尾段落设置 `needRemoveNewLine=true`，`GetSpanContent` 剥离末尾 `\n` 后传入字体引擎。`info.end - info.start`（含 `\n`）大于 `actualRange.first.end`（不含 `\n`），但 `ParagraphManager` 两方法用 `actualRange.first.end` 累积 `charLength`，导致段间偏移错位 1。修复方案：`charLength` 累积改用 `paragraphLength`（含 `\n`），字符边界判定改用 `paragraphLength`，字形空间不变（`\n` 无字形，glyphLength 仍累积 `actualRange.second.end`） | 代码确认：paragraph_util.cpp:300-303 `SetNeedRemoveNewLine`、span_node.cpp:1284-1285 `GetSpanContent` 剥离、text_layout_algorithm.cpp:487-489 `child->length = content.length()` 含 `\n`、paragraph_manager.cpp:288 `charLength += actualRange.first.end` 不含 `\n` |

## 需求基线

### 目标

为 LayoutManager 的 `getCharacterPositionAtCoordinate`、`getGlyphRangeForCharacterRange`、`getCharacterRangeForGlyphRange` 三个接口增加 `encoding` 参数，使开发者可以选择 UTF-16 码元偏移编码，从而与 `getRectsForRange`、选择、光标等 UTF-16 计数 API 配套使用。同时优化 `ParagraphManager` 中两个方法的混乱逻辑并修复 bug。

### 范围（In Scope）

| 层 | 变更内容 | 关键文件 |
|----|----------|----------|
| 动态 API 接口 | d.ts 新增 `declare enum TextEncoding`（`TEXT_ENCODING_UTF8=0`/`TEXT_ENCODING_UTF16=1`）+ 三接口新增带 `encoding?: TextEncoding` 的方法重载（旧方法 @since 24 保留不变）；en + zh-cn 同步 | `interface_sdk-js/api/@internal/component/ets/text_common.d.ts`、`zh-cn/.../text_common.d.ts` |
| 静态 API 接口 | 新增 `export declare enum TextEncoding` + 三接口新增带 `encoding?: TextEncoding` 的方法重载 | `interface_sdk-js/api/arkui/component/textCommon.static.d.ets` |
| C++ 枚举定义 | 新增 `NG::TextEncoding` 枚举（`UTF8=0`/`UTF16=1`，短名），值与 `Drawing::TextEncoding` 一致 | `frameworks/core/components_ng/render/paragraph.h` |
| C API 公共枚举与函数 | 新增 `ArkUI_TextEncoding` 枚举（`ARKUI_TEXT_ENCODING_UTF8=0`/`ARKUI_TEXT_ENCODING_UTF16=1`）+ 三个 `*WithEncoding` 函数；旧函数内部传 `ARKUI_TEXT_ENCODING_UTF8` | `interface_sdk_c/arkui/ace_engine/native/styled_string.h`（en+zh-cn）、`ace_engine/interfaces/native/native_styled_string.h`、`ace_engine/interfaces/native/node/native_node_extented.cpp` |
| C API 符号导出 | 新增三个 `*WithEncoding` 符号 `first_introduced: 26.0.0` | `interface_sdk_c/arkui/ace_engine/native/libace.ndk.json` |
| ParagraphManager | 三方法增加 encoding 参数，**透传**给底层 Paragraph，不做内部转换 + 逻辑优化 | `paragraph_manager.h/.cpp` |
| Paragraph 基类 | 三虚方法增加 encoding 参数 | `paragraph.h` |
| TxtParagraph | 三方法将 Ace TextEncoding `static_cast<Drawing::TextEncoding>` 后传给 Rosen Typography | `txt_paragraph.h/.cpp` |
| LayoutInfoInterface | 三个虚方法增加 encoding 参数 | `layout_info_interface.h` |
| TextPattern | 三个 override 增加 encoding 参数 | `text_pattern.h/.cpp` |
| RichEditorPattern | 三个 override 增加 encoding 参数 | `rich_editor_pattern.h/.cpp` |
| TextModelNG / RichEditorModelNG | 增加 encoding 参数 | `text_model_ng.cpp` / `rich_editor_model_ng.cpp` |
| JS bridge | 解析 encoding 参数并传递 | `js_layout_manager.h/.cpp` |
| 运行时枚举镜像 | +`TextEncoding` 枚举对象（`TEXT_ENCODING_UTF8=0`/`TEXT_ENCODING_UTF16=1`，值名与 d.ts 一致） | `frameworks/bridge/declarative_frontend/engine/jsEnumStyle.js` |
| 静态 modifier bridge | 解析 encoding 参数并传递 | `layout_manager_accessor.cpp` |
| node_text_modifier | 内部调用传默认 encoding=UTF8 | `node_text_modifier.cpp` |
| 单元测试 | 新增 UTF16 encoding 测试 + 逻辑优化回归 | `paragraph_manager_test_ng.cpp` 等 |

### 不涉及（Out of Scope）

| 项 | 理由 |
|----|------|
| C API 旧公共函数签名变更（`@since 24` 函数） | AGENTS.md 硬边界：不经确认不改 `interfaces/native/` 公开 API 签名；新增 `*WithEncoding` 函数承载新参数，旧函数内部传 `ARKUI_TEXT_ENCODING_UTF8` 保持向后兼容 |
| 复用 graphics 仓 `OH_Drawing_TextEncoding` 作为 C API 公开枚举 | 按 OpenHarmony C API 命名规范使用 `ARKUI_` 前缀新增 `ArkUI_TextEncoding` 枚举，避免跨仓枚举依赖（C++ 内部仍 `static_cast<Drawing::TextEncoding>` 透传给 Rosen） |
| `getGlyphPositionAtCoordinate` | 该接口返回的是 glyph 位置，不涉及 character/glyph 编码差异 |

### 验收标准（P0）

- **AC-1**: WHEN 调用 `getCharacterPositionAtCoordinate(x, y, TextEncoding.TEXT_ENCODING_UTF16)` THEN 返回的 position 为 UTF-16 码元偏移，与 `getRectsForRange` 的 UTF-16 计数一致
- **AC-2**: WHEN 调用 `getCharacterPositionAtCoordinate(x, y, TextEncoding.TEXT_ENCODING_UTF8)` 或不传 encoding THEN 返回 UTF-8 字节偏移（向后兼容）
- **AC-3**: WHEN 调用 `getGlyphRangeForCharacterRange(range, TextEncoding.TEXT_ENCODING_UTF16)` THEN 输入 charRange 和返回的 glyphRange/actualCharRange 均为 UTF-16 码元偏移
- **AC-4**: WHEN 调用 `getGlyphRangeForCharacterRange(range, TextEncoding.TEXT_ENCODING_UTF8)` 或不传 encoding THEN 行为与变更前一致（向后兼容）
- **AC-5**: WHEN 调用 `getCharacterRangeForGlyphRange(range, TextEncoding.TEXT_ENCODING_UTF16)` THEN 输入 glyphRange 和返回的 charRange/actualGlyphRange 均为 UTF-16 码元偏移
- **AC-6**: WHEN 调用 `getCharacterRangeForGlyphRange(range, TextEncoding.TEXT_ENCODING_UTF8)` 或不传 encoding THEN 行为与变更前一致（向后兼容）
- **AC-7**: WHEN 段落包含 CJK 字符（如中文占 3 UTF-8 字节、1 UTF-16 码元）且使用 `TEXT_ENCODING_UTF16` encoding THEN 返回范围正确对应 UTF-16 码元计数
- **AC-8**: WHEN 多段落场景下使用任意 encoding THEN 跨段落范围计算正确（修复原 bug：info.start/info.end 为 UTF-16 但被当作 UTF-8 使用）
- **AC-9 (C API)**: WHEN 调用 `OH_ArkUI_TextLayoutManager_GetCharacterPositionAtCoordinateWithEncoding(..., ARKUI_TEXT_ENCODING_UTF16)` THEN 行为与 AC-1 一致；旧函数 `OH_ArkUI_TextLayoutManager_GetCharacterPositionAtCoordinate` 行为与 AC-2 一致（内部传 `ARKUI_TEXT_ENCODING_UTF8`）
- **AC-10**: WHEN Text 使用属性字符串 + `IncrementalUpdatePolicy::PARAGRAPH_CACHE` 且文本含 `\n` 触发 `ConstructParagraphSpanGroupForHash` 拆分多段落 THEN `GetGlyphRangeForCharacterRange` 的 `charLength` 累积包含被剥离的 `\n` 偏移，开发者视角的跨段落 char offset 正确匹配到目标段落（不再错位 1）
- **AC-11**: WHEN 同上场景调用 `GetCharacterRangeForGlyphRange` THEN `charLength` 累积包含被剥离的 `\n` 偏移，返回的 charRange 为开发者视角偏移（含 `\n` 位置），glyphRange 为字体引擎视角偏移（不含 `\n`，glyph 空间连续无间隙）

### 复杂度判定

**标准** — 单仓内多文件变更，涉及接口/桥接/核心三层，但逻辑清晰且已有 UtfUtils 转换工具支持。

## 受影响子系统与仓库

| 仓库 | 路径 | 影响 |
|------|------|------|
| ace_engine | `frameworks/core/components_ng/pattern/text/paragraph_manager.*` | 核心实现 + 逻辑优化 |
| ace_engine | `frameworks/core/components_ng/render/paragraph.h` | 虚方法签名 |
| ace_engine | `frameworks/core/components_ng/render/adapter/txt_paragraph.*` | 实现 |
| ace_engine | `frameworks/core/components_ng/pattern/text/layout_info_interface.h` | 接口 |
| ace_engine | `frameworks/core/components_ng/pattern/text/text_pattern.*` | override |
| ace_engine | `frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.*` | override |
| ace_engine | `frameworks/core/components_ng/pattern/text/text_model_ng.cpp` | Model |
| ace_engine | `frameworks/bridge/declarative_frontend/jsview/js_layout_manager.*` | JS bridge |
| ace_engine | `frameworks/core/interfaces/native/implementation/layout_manager_accessor.cpp` | 静态 bridge |
| ace_engine | `frameworks/core/interfaces/native/node/node_text_modifier.cpp` | modifier |
| ace_engine | `test/unittest/` | 测试 |
| interface_sdk-js | `api/@internal/component/ets/text_common.d.ts` | 动态 API（已完成） |
| interface_sdk-js | `api/arkui/component/textCommon.static.d.ets` | 静态 API |

## 不涉及项确认

| 维度 | 结论 | 理由 |
|------|------|------|
| 无障碍 | N/A | 偏移编码不影响无障碍 |
| 大字体 | N/A | 不影响字号 |
| 深色模式 | N/A | 不感知主题 |
| 多窗口/分屏 | N/A | 不感知窗口 |
| 多用户 | N/A | 不涉及用户数据 |
| 版本升级 | 适用 | API 26 新参数，向前兼容（可选参数） |
| 生态兼容 | 适用 | 新增可选参数不破坏已有 API |

## 基线审批

| 字段 | 值 |
|------|-----|
| 状态 | Baselined |
| 审批人 | Owner |
| 证据 | 当前会话 Owner 明确要求 |
