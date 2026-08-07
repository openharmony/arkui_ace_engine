# TASK-1: 核心层 — TextEncoding 枚举 + 透传 + 逻辑重写

## 目标

定义 TextEncoding 枚举，为 ParagraphManager/Paragraph/TxtParagraph 三方法增加 encoding 参数，**透传**给 Rosen Typography（不做 ArkUI 内部 UTF-8/UTF-16 转换），重写 GetGlyphRangeForCharacterRange 和 GetCharacterRangeForGlyphRange 逻辑。

## 受影响文件

- `frameworks/core/components_ng/render/paragraph.h` — TextEncoding 枚举 + 三虚方法 encoding 参数
- `frameworks/core/components_ng/render/adapter/txt_paragraph.h` — override 签名
- `frameworks/core/components_ng/render/adapter/txt_paragraph.cpp` — `static_cast<Drawing::TextEncoding>` 透传给 Rosen
- `frameworks/core/components_ng/pattern/text/paragraph_manager.h` — 三方法签名 +encoding（无需转换工具）
- `frameworks/core/components_ng/pattern/text/paragraph_manager.cpp` — 透传 encoding + 逻辑重写
- `test/mock/frameworks/core/components_ng/render/mock_paragraph.h` — mock 签名更新

## 实现要点

1. 在 `paragraph.h` 定义 `enum class TextEncoding : int32_t { UTF8 = 0, UTF16 = 1 }`
2. Paragraph 基类三虚方法增加 `TextEncoding encoding = TextEncoding::UTF8`（默认参数）
3. TxtParagraph 三 override 方法：
   - `GetCharacterPositionAtCoordinate`：调 `paragrah->GetCharacterIndexByCoordinate(x, y, static_cast<Drawing::TextEncoding>(encoding))`
   - `GetGlyphRangeForCharacterRange`：调 `paragrah->GetGlyphRangeForCharacterRange(start, end, &boundary, static_cast<Drawing::TextEncoding>(encoding))`
   - `GetCharacterRangeForGlyphRange`：调 `paragrah->GetCharacterRangeForGlyphRange(start, end, &boundary, static_cast<Drawing::TextEncoding>(encoding))`
4. ParagraphManager 三方法增加 encoding 参数，透传给 `info.paragraph->GetXxx(..., encoding)`
5. GetGlyphRangeForCharacterRange 逻辑重写：去除 `CHECK_NULL_RETURN` 控制流、去除末尾死代码、改用 flag+return、encoding 透传给所有底层调用、**同段落合并单次调用**（start 和 end 在同一段时从 2 次目标调用减为 1 次）
6. GetCharacterRangeForGlyphRange 逻辑重写：对称于上述，同段落合并单次调用
7. **PARAGRAPH_CACHE `\n` 剥离偏移修复**（BR-7, FR-9, FR-10）：
   - 提取 `ParagraphMetadata` helper（匿名 namespace），含 `actualCharEnd`/`actualGlyphEnd`/`strippedNewLineCount`/`effectiveCharLength`/`effectiveGlyphLength`/`isLastParagraph`
   - `strippedNewLineCount = isLastParagraph ? 0 : 1`（不使用 `paragraphLength`）
   - `charLength` 累积改为 `actualCharEnd + strippedNewLineCount`，`glyphLength` 累积改为 `actualGlyphEnd + strippedNewLineCount`
   - char 边界判定用 `effectiveCharLength`，glyph 边界判定用 `effectiveGlyphLength`，两函数对称
   - 局部偏移分别 clamp 到 `actualCharEnd`/`actualGlyphEnd`（`std::min`），避免 `\n` 位置越界
   - 消除 `idx` 变量，改用 `std::next(it) == paragraphs_.end()` 判断末尾段
8. mock_paragraph.h 更新 MOCK_METHOD 签名（MOCK_METHOD2/3）
9. **GetCharacterPositionAtCoordinate `info.start` 单位混用修复**（BR-9, FR-11）：
   - 在 y 坐标遍历循环中累积 `charLength`（`actualCharEnd + strippedNewLineCount`），替代直接用 `info.start`/`info.end`
   - `finalResult.position_ = result.position_ + charLength`（同为开发者 encoding 单位）
   - fallback `finalResult.position_ = charLength + actualCharEnd`，替代 `info.end`
   - 每段调 `ComputeParagraphMetadata` 获取元数据，代价为目标段之前每段多 1 次 Rosen 调用
   - 消除 `idx` 变量，改用 `std::next(it) == paragraphs_.end()`
10. **不需要** `Utf16OffsetToUtf8`/`Utf8OffsetToUtf16` 转换工具
11. **不需要** include `utf_helper.h`

## 关键依据

Rosen `Typography`（`typography.h:176-181`）已原生支持 `TextEncoding`：
```cpp
virtual IndexAndAffinity GetCharacterIndexByCoordinate(double x, double y,
    TextEncoding encodeType = TextEncoding::UTF8) const = 0;
virtual Boundary GetCharacterRangeForGlyphRange(size_t glyphStart, size_t glyphEnd,
    Boundary* actualGlyphRange, TextEncoding encodeType = TextEncoding::UTF8) const = 0;
virtual Boundary GetGlyphRangeForCharacterRange(size_t charStart, size_t charEnd,
    Boundary* actualCharRange, TextEncoding encodeType = TextEncoding::UTF8) const = 0;
```

## 验证

- Host unittest 编译通过
- 现有 paragraph_manager_test_ng.cpp 编译通过（因默认参数，无需改调用方）
- **PARAGRAPH_CACHE `\n` 剥离偏移回归测试**：
  - 构造 3 段落（`"😀12345\n"` / `"不带大概\n"` / `"ahdkjahkl"`），info.end-info.start 含 `\n` 但字体引擎文本不含 `\n`
  - `GetGlyphRangeForCharacterRange` 跨段查询（如 char [5, 10]）：charLength 累积含 `\n`，offset 8 正确匹配 Para 2（不再错位到 Para 1）
  - `GetCharacterRangeForGlyphRange` 往返一致：glyph [5, 9] → char [5, 10]
  - `\n` 位置退化处理：char offset 落在 `\n` 位置返回空/退化 range，不崩溃
- **GetCharacterPositionAtCoordinate UTF-8 偏移回归**：
  - 构造 2 段落（`"你好\n"` / `"世界"`），encoding=UTF8
  - 点击 Para 1 '世'：返回 position = 7（UTF-8 字节，"你好\n" = 6+1），不是 3（UTF-16 码元）
  - 消除 `idx` 变量，使用 `std::next(it) == paragraphs_.end()`
