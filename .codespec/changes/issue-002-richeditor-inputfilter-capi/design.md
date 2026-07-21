# 设计文档

> 固化关键设计决策、约束、风险和取舍。

## 概述

| 属性 | 值 |
|------|-----|
| Feature | RichEditor CAPI inputFilter & onInputFilterError |
| 设计编号 | DES-002 |
| 复杂度 | 标准 |
| 状态 | Draft |

## 输入文档

| 文档 | 路径 | 状态 |
|------|------|------|
| Requirement | proposal.md | Approved (基线 v1.0) |

## Define → Specify 衔接表

| Define 输出 | Specify 读取 | 传递方式 |
|-------------|-------------|----------|
| 3 个用户故事 (US-1/US-2/US-3) | spec.md 用户故事 + AC | 直接引用 |
| 12 条 AC | spec.md AC 表 + 规则表 | 直接引用 |
| API 变更项 (2 枚举) | spec.md API 变更分析 | 直接引用 |
| 方案 A-1 (共享提取) | design.md 设计决策 D-1 | 方案确认 |
| 生效约束 (spanString) | design.md 约束 C-1, spec.md 规则 | 条件映射 |
| 过滤优先级 (inputFilter→maxLength) | design.md 约束 C-2, spec.md 规则 R-5 | 顺序映射 |
| 6 层调用链 | design.md 全链路设计 | 层级映射 |

---

## 关键设计决策

### D-1: 过滤工具复用方式 — 提取共享函数（方案 A-1）

| 项 | 内容 |
|----|------|
| 决策 | 提取 FilterWithRegex 为共享自由函数，位于 `frameworks/core/components_ng/pattern/text_field/text_filter_utils.h/.cpp` |
| 理由 | 架构整洁、零逻辑重复、长期可维护；核心逻辑仅 6 行（行317-323），提取成本低 |
| 取舍 | 放弃方案 A-2 (inline复制) 的最小侵入优势，接受新增 2 个文件的成本 |
| 影响文件 | 新建 text_filter_utils.h/.cpp；修改 content_controller.cpp 改用共享调用 |
| 关联 AC | AC-1, AC-5, AC-7 |
| 跨组件依赖 | **不引入新依赖**：RichEditor 已有 12 处 `#include` 引用 text_field 模块（text_field_model.h, text_field_event_hub.h, text_keyboard_common_type.h, text_field_manager.h 等），新增 text_filter_utils.h 引用仅增加 1 处，不构成新的跨组件依赖 |

**提取范围与修改明细：**

| # | 来源文件 | 行号 | 函数/代码 | 操作 | 目标 |
|---|----------|------|-----------|------|------|
| 1 | content_controller.cpp | 30-64 | `namespace {}` 匿名块内 ContentToWstring(L41) + ContentToU16string(L53) | **迁移+删除原定义** | text_filter_utils.cpp (公开函数，TextFilterUtils namespace) |
| 2 | content_controller.cpp | 289-308 | `ContentController::RemoveErrorTextFromValue` 定义 | **迁移+删除原定义** | text_filter_utils.cpp (公开函数，TextFilterUtils namespace) |
| 3 | content_controller.cpp | 314-324 | `ContentController::FilterWithRegex` 定义 | **改为 wrapper**：保留声明，实现改为 `return TextFilterUtils::FilterWithRegex(filter, result)` | content_controller.cpp (wrapper 保留) |
| 4 | content_controller.cpp | 317-322 | FilterWithRegex 内部对 ContentToWstring/ContentToU16string/RemoveErrorTextFromValue 的 4 处调用 | 随 FilterWithRegex 整体迁移，wrapper 内不再直接调用 | text_filter_utils.cpp |
| 5 | content_controller.cpp | 403 | `FilterWithRegex(filter, result)` 调用 | **不变**：仍通过 ContentController::FilterWithRegex wrapper 间接调用 | content_controller.cpp (无需改动) |
| 6 | content_controller.h | 103 | `static std::u16string RemoveErrorTextFromValue(...)` 声明 | **删除**：迁移到 text_filter_utils.h | text_filter_utils.h |
| 7 | content_controller.h | 104 | `static std::u16string FilterWithRegex(...)` 声明 | **保留**：wrapper 仍需声明 | content_controller.h (无需改动) |
| 8 | text_field/BUILD.gn | 19 | sources 列表中 `"content_controller.cpp"` 之后 | **新增** `"text_filter_utils.cpp"` | BUILD.gn |

**不受影响的代码：**
- `frameworks/compatible/components/text_field/render_text_field.cpp/h` 中的 FilterWithRegex/RemoveErrorTextFromValue：使用 `std::string` 签名，与 NG 版本(`std::u16string`)完全不同，独立实现，无需改动
- `ContentController::FilterWithEvent` (L392-411)：调用 FilterWithRegex (L403) 不变，wrapper 链路通畅
- 所有 UT（ContentController002 等）：间接调用链不变，测试结果不变

### D-2: 枚举编号策略 — 紧跟现有最大值追加

| 项 | 内容 |
|----|------|
| 决策 | 属性枚举 `NODE_TEXT_EDITOR_INPUT_FILTER = 22031`（紧跟 22030）；事件枚举 `NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR = 22009`（紧跟 22008）；arkoala 事件子类型 `ON_RICH_EDITOR_ON_INPUT_FILTER_ERROR = 67009`（紧跟 67008） |
| 理由 | 枚举值按 scope 基数 + 偏移量计算，追加在现有最大值之后可避免编号冲突 |
| 取舍 | 不在中间插入，避免破坏编号连续性和函数指针数组索引 |
| 影响文件 | native_node.h, arkoala_api.h |
| 关联 AC | AC-1, AC-4 |

### D-3: 事件数据构造 — 使用 TEXT_INPUT kind 而非 RICH_EDITOR（含方案对比）

| 项 | 内容 |
|----|------|
| 决策 | onInputFilterError 事件内部构造使用 `event.kind = ARKUI_TEXT_INPUT` + `event.textInputEvent.subKind = ON_RICH_EDITOR_ON_INPUT_FILTER_ERROR(67009)` + `event.textInputEvent.nativeStringPtr = utf8Str.c_str()` |
| 理由 | 见下方"CAPI 事件提取机制约束"和"方案对比"详细说明 |
| 取舍 | 最终选择方案 B（复用 TEXT_INPUT kind + 补充文档注释），语义上 kind 值与组件类型不完全一致，但 subKind 已完全区分事件归属，对用户层 API 无影响 |
| 影响文件 | rich_editor_dynamic_modifier.cpp (事件构造 lambda), native_node.h (枚举注释) |
| 关联 AC | AC-5 |

#### CAPI 事件提取机制约束

CAPI 事件系统有两层结构：**内部层 ArkUINodeEvent** 和 **公共层 ArkUI_NodeEvent**。事件流转链路：

```
构造端: event.kind=X → event.unionMember=data → SendArkUISyncEvent
  ↓
分发端: HandleInnerNodeEvent → GetNativeNodeEventType(从kind决定读哪个union成员获取subKind)
       → ConvertEvent(kind→category映射)
  ↓
提取端: GetStringAsyncEvent → 校验category==STRING_ASYNC_EVENT → 从origin->textInputEvent.nativeStringPtr读取pStr
```

约束链关键证据：

| 约束 | 说明 | 源码 |
|------|------|------|
| `ArkUIEventCategory` 中不存在 RICH_EDITOR 类别 | 枚举值范围0-24，无 RichEditor 专属 kind 值 | arkoala_api.h L1511-L1536 |
| 字符串提取唯一通道 | `GetStringAsyncEvent` 强制校验 `category==NODE_EVENT_CATEGORY_STRING_ASYNC_EVENT`，否则返回 nullptr | event_converter.cpp L1392-L1409 |
| `textInputEvent` 是唯一承载字符串指针的 union 成员 | `nativeStringPtr` 存字符串；`componentAsyncEvent.data[]` 只存数值 | arkoala_api.h L1913-L1918 vs L1939-L1943 |
| TEXT_INPUT → STRING_ASYNC_EVENT 是唯一通往 GetStringAsyncEvent 的映射 | 其他 kind 映射到不同 category，均无法被 GetStringAsyncEvent 接受 | event_converter.cpp L913-L1031 |
| kind 决定 subKind 的读取方式 | kind=TEXT_INPUT 时从 textInputEvent.subKind 读取 | node_model.cpp L804-L873 |

RichEditor 现有事件的 kind 使用情况：

| 事件 | kind | union 成员 | 提取方式 | 能传字符串？ |
|------|------|-----------|---------|-------------|
| onSubmit | COMPONENT_ASYNC_EVENT(4) | componentAsyncEvent | GetNodeComponentEvent | 否 |
| onReady | COMPONENT_ASYNC_EVENT(4) | componentAsyncEvent | GetNodeComponentEvent | 否 |
| onEditingChange | COMPONENT_ASYNC_EVENT(4) | componentAsyncEvent | GetNodeComponentEvent | 否 |
| onPaste | MIXED_EVENT(11) | mixedEvent | GetStringValue | 是（但需专用提取） |
| onWillChange | TEXT_EDITOR_CHANGE_EVENT(23) | textEditorChangeEvent | — | 否 |
| onDidChange | COMPONENT_ASYNC_EVENT(4) | componentAsyncEvent | GetNodeComponentEvent | 否 |

#### 方案对比

| 方案 | 做法 | 优势 | 风险/代价 | 推荐？ |
|------|------|------|-----------|--------|
| **A: 新增 RICH_EDITOR kind** | 在 `ArkUIEventCategory` 新增枚举值(如25)，在 `ArkUINodeEvent` union 新增/复用成员，在 `ConvertEvent` 新增映射(RICH_EDITOR→STRING_ASYNC_EVENT)，在 `GetNativeNodeEventType` 新增 kind 分支，在 `GetStringAsyncEvent` 新增 category 校验 | 语义最一致 | **ABI 变更**：union 增加成员改变结构体大小/布局，影响所有使用该结构体的代码；枚举值新增影响所有 switch(kind) 分支；属于 Public API 变更，违反 AGENTS.md 约束 | **不推荐**（代价远大于收益） |
| **B: 复用 TEXT_INPUT kind + 补充文档注释** | 保持 kind=TEXT_INPUT，在 native_node.h 枚举注释中明确"RichEditor 的字符串事件也使用 TEXT_INPUT kind，通过 subKind 区分组件类型"；subKind 值(67009)已完全区分事件归属 | 最小改动、无 ABI 风险；用户使用 GetStringAsyncEvent 的体验与 TextInput 完全一致；subKind 区分组件归属(ON_RICH_EDITOR_ON_INPUT_FILTER_ERROR vs ON_TEXT_INPUT_INPUT_FILTER_ERROR)，不混淆 | 语义不完全一致（kind 值与组件类型不对应，仅存在于内部层） | **推荐（最终选择）** |
| **C: 使用 MIXED_EVENT kind** | 参考 onPaste 做法，用 kind=MIXED_EVENT + mixedEvent 传字符串，通过 GetStringValue 提取 | kind 值不与 TextInput 关联 | 提取方式与 TextInput 的 GetStringAsyncEvent 不一致，用户需使用不同的提取函数；需在 ConvertEvent 中为 ON_RICH_EDITOR_ON_INPUT_FILTER_ERROR 添加 MIXED_EVENT 映射分支；实现更复杂 | **不推荐**（提取方式不一致） |

#### 选择方案 B 的理由

1. `subKind` 已完全区分组件归属：`ON_RICH_EDITOR_ON_INPUT_FILTER_ERROR(67009)` vs `ON_TEXT_INPUT_INPUT_FILTER_ERROR(1007)`，不存在混淆
2. 用户使用 `GetStringAsyncEvent` 提取的体验与 TextInput 完全一致，API 行为统一
3. 不引入 ABI 变更，不违反 AGENTS.md 约束
4. kind=TEXT_INPUT 的"语义不一致"仅存在于内部层（开发者不感知），对用户层 API 无影响

### D-4: X-macro 属性路由追加策略

| 项 | 内容 |
|----|------|
| 决策 | 在 `rich_editor_properties.def` 末尾追加 `X(1, 1, 1, RichEditorInputFilter)` 条目 |
| 理由 | X-macro 驱动属性路由，追加条目自动展开为 setter/getter/resetter 函数指针数组条目 |
| 取舍 | 新增条目必须紧跟末尾，否则会破坏现有条目的 subTypeId 索引计算 |
| 影响文件 | rich_editor_properties.def, style_modifier.cpp (自动展开) |
| 关联 AC | AC-1, AC-2, AC-3 |

### D-5: Pattern 层过滤插入点位置

| 项 | 内容 |
|----|------|
| 决策 | 过滤逻辑在 ProcessInsertValue (行6840) 和 InsertValueInStyledString (行451) 中，ProcessTextTruncationOperation 之前插入 `FilterWithInputFilter(text)` |
| 理由 | 过滤优先级为 inputFilter → maxLength，必须在截断之前执行过滤；这与 TextInput 的 FilterWithEvent → maxLength 顺序一致 |
| 取舍 | 过滤仅作用于传入的 `text`/`subValue` 变量（插入值），不对全量内容做二次过滤（RichEditor 无 ContentController 两阶段机制） |
| 影响文件 | rich_editor_pattern.cpp |
| 关联 AC | AC-7, AC-9 |

### D-6: 正则变更时全量重新过滤（静默执行，与 TextInput 一致）

| 项 | 内容 |
|----|------|
| 决策 | inputFilter 正则变更时，通过属性变更回调触发 `FilterInitializeText()`，对已有内容做全量重新过滤；静默执行（不触发 onWillChange 确认），与 TextInput 的行为一致 |
| 理由 | (1) TextInput/TextArea 在正则变更时通过 `FilterInitializeText` → `FilterValue` 对全量内容静默重新过滤（text_field_pattern.cpp L4808-4848, L13860-13867），不触发 onWillChange（`isFilterChanged_` 在 SetInputFilter 时未被设为 true）；(2) RichEditor 应与 TextInput 保持行为一致 |
| 取舍 | 放弃 onWillChange 用户确认机制（与 TextInput 的静默过滤保持一致），代价是正则变更时内容变更不可被用户拒绝；但这是 TextInput 已有的行为模式 |
| 影响文件 | rich_editor_pattern.cpp (属性变更回调 + FilterInitializeText), rich_editor_model_ng.cpp (SetInputFilter 实现调整) |
| 关联 AC | AC-12 |

---

## RichEditor StyledString 结构与机制

### 双层 Span 体系

RichEditor 的 StyledString 采用**双层 Span 索引体系**，两层作用和边界规则不同：

| 层 | 类 | 作用 | 边界规则 | 存储位置 |
|----|-----|------|----------|---------|
| **SpanItem 层** | `SpanItem` | 文本**内容分片**（用于分段渲染） | **以 `\n` 为边界**，每个 SpanItem 不跨行 | `SpanString::spans_` (list) |
| **SpanBase 层** | `FontSpan`, `DecorationSpan` 等 18 种 | 文本**样式标注**（用于样式计算） | **不以 `\n` 为边界**，可跨越多行 | `SpanString::spansMap_` (map<SpanType, list>) |

核心存储结构（span_string.h L138-140）：
```cpp
std::u16string text_;                                                   // 底层纯文本
std::unordered_map<SpanType, std::list<RefPtr<SpanBase>>> spansMap_;    // 样式Span按类型分组存储
std::list<RefPtr<NG::SpanItem>> spans_;                                 // 文本内容分片SpanItem列表
```

### SpanBase 范围定义

所有 SpanBase 的范围通过 `start_` + `end_` 定义（span_object.h L160-161），采用**左闭右开**区间 `[start, end)`。

SpanBase 子类清单（18 种，均定义于 span_object.h）：

| SpanBase 子类 | SpanType 枚举 | 核心属性 | 可跨越 `\n`？ |
|---------------|--------------|----------|-------------|
| FontSpan | Font(0) | fontColor/fontSize/fontWeight/fontStyle | 是 |
| DecorationSpan | Decoration(1) | types/color/style | 是 |
| BaselineOffsetSpan | BaselineOffset(2) | baselineOffset | 是 |
| LetterSpacingSpan | LetterSpacing(3) | letterSpacing | 是 |
| TextShadowSpan | TextShadow(4) | textShadow | 是 |
| LineHeightSpan | LineHeight(5) | lineHeight | 是 |
| BackgroundColorSpan | BackgroundColor(6) | textBackgroundStyle + groupId | 是 |
| UrlSpan | Url(7) | urlAddress | 是 |
| LineSpacingSpan | LineSpacing(8) | lineSpacing | 是 |
| HalfLeadingSpan | HalfLeading(9) | halfLeading | 是 |
| GestureSpan | Gesture(100) | gestureInfo(onClick/onLongPress/onTouch) | 是 |
| ParagraphStyleSpan | ParagraphStyle(200) | paragraphStyle(align/maxLines/wordBreak等) | 是（语义上以 `\n` 为自然边界） |
| ImageSpan | Image(300) | imageOptions | 否（占1字符位，不参与合并） |
| CustomSpan | CustomSpan(400) | onMeasure/onDraw | 否（占1字符位，不参与合并） |
| ExtSpan | ExtSpan(500) | userData | 是 |

### SpanItem 与 SpanBase 的交互机制

当文本内容变更时（插入/删除），SpanString 的 `ReplaceString` 方法（mutable_span_string.cpp L246-266）统一处理两层 Span：

```
ReplaceString(start, length, other)
  ① SetString(text.substr(0,start) + other + text.substr(end))    → 更新底层纯文本
  ② ApplyReplaceStringToSpans(start, length, other, op)           → 处理 SpanItem
  ③ ApplyReplaceStringToSpanBase(start, length, other, op)        → 处理 SpanBase
  ④ UpdateSpansWithOffset(start, otherLength - length)            → SpanItem 偏移修正
  ⑤ UpdateSpanMapWithOffset(start, otherLength - length)          → SpanBase 偏移修正
  ⑥ SplitSpansByNewLine()                                          → SpanItem 按 \n 重新分裂
  ⑦ KeepSpansOrder()                                                → SpanBase 排序+合并
```

### 正则变更全量重新过滤的 Span 处理机制

RichEditor 在正则变更时调用 `FilterInitializeText()`，对已有内容做全量重新过滤。过滤流程：

```
① styledString_->GetU16string() → 获取全量纯文本
② TextFilterUtils::FilterWithRegex(regex, text) → 一次性正则过滤，返回被拒字符列表
③ 逐个被拒字符位置，调用 styledString_->RemoveString(pos, len) → Span 自动处理
④ FireOnInputFilterError → 通知被拒内容
⑤ RemoveString 内置机制自动完成所有 Span 修正（无需额外处理）
```

#### SpanItem 层过滤场景（5 种）

| 场景 | 触发条件 | 处理方式 | 源码 |
|------|----------|----------|------|
| 完全被删除范围包含 | SpanItem interval 完全在 [start, end) 内 | `spans_.erase(it)` 直接删除 | mutable_span_string.cpp L155-157 |
| 被删除范围从中间切开 | SpanItem interval 跨越 [start, end)（spanStart < intersection.first && intersection.second < spanEnd） | 分裂为左右两段 SpanItem：左段 content 截断到 start，右段 GetSameStyleSpanItem 继承样式 | mutable_span_string.cpp L159-168 |
| 左端与删除范围重叠 | 删除范围覆盖 SpanItem 左端 | 截断 SpanItem content 的前段，interval.second = start | mutable_span_string.cpp L170-178 |
| 右端与删除范围重叠 | 删除范围覆盖 SpanItem 右端 | 截断 SpanItem content 的后段，interval.first = end | mutable_span_string.cpp L179-182 |
| 无重叠但位于删除范围之后 | SpanItem 不与删除范围交集 | 不直接处理，但 UpdateSpansWithOffset 会修正 interval 偏移 | mutable_span_string.cpp L262 |

每次 RemoveString 后，`SplitSpansByNewLine()` 会对所有 SpanItem 按新的 `\n` 位置重新分裂，确保每个 SpanItem 不跨行。

#### SpanBase 层过滤场景（5 种）

| 场景 | 触发条件 | 处理方式 | 源码 |
|------|----------|----------|------|
| 完全被删除范围包含 | intersection == spanStart && intersection == spanEnd | `spans.erase(it)` 直接删除 | mutable_span_string.cpp L224-227 |
| 被删除范围从中间切开 | spanStart < intersection.first && intersection.second < spanEnd（op==REMOVE） | 分裂为左右两段 SubSpan：左段 UpdateEndIndex(start)，右段 GetSubSpan(end, spanEnd) | mutable_span_string.cpp L228-234 |
| 左端与删除范围重叠 | intersection.first == spanStart（左端对齐） | UpdateEndIndex(start) 截断右端，或 UpdateStartIndex(intersection.second) 前移 start | mutable_span_string.cpp L236-241 |
| 右端与删除范围重叠 | intersection.first > spanStart | UpdateEndIndex(newEnd) 截断到删除范围起始位置 | mutable_span_string.cpp L237-238 |
| 无重叠但位于删除范围之后 | SpanBase 不与删除范围交集 | 不直接处理，但 UpdateSpanMapWithOffset 会修正 start_/end_ 偏移 | mutable_span_string.cpp L263 |

每次 RemoveString 后，`KeepSpansOrder()` 对每种 SpanType 调用 `SortSpans` + `MergeIntervals`：相邻两个 SpanBase 如果满足 `a.end >= b.start && a.IsAttributesEqual(b)`，则自动合并（span_string.cpp L434-453）。Image 和 CustomSpan 不参与合并。

#### `\n` 字符被过滤时的段落合并行为

正则变更全量过滤时，`\n` 字符是否被正则拒绝会影响段落合并：

| 场景 | `\n` 是否被拒 | 过滤结果 | 段落行为 |
|------|-------------|----------|----------|
| `\n` 被保留 | 正则允许 `\n`（如 `^[a-zA-Z\n]*$`） | `\n` 不被删除 | 段落边界保留，段落不会合并 |
| `\n` 被拒绝 | 正则拒绝 `\n`（如 `^[0-9]*$`） | `\n` 被删除 | RemoveString 删除 `\n` 后，`SplitSpansByNewLine` 重新分裂 SpanItem，原段落2自动升级为段落1 |
| 段落内字符被拒但 `\n` 保留 | `\n` 在白名单内 | 段落内非白名单字符被删除 | 段落变为空行（只有 `\n`），SpanItem 只剩 `\n` |

**关键结论：全量重新过滤对 SpanItem 和 SpanBase 不需要任何额外处理**。`RemoveString` 的内置机制已覆盖所有重叠场景 + 偏移修正 + SpanItem 按行分裂 + SpanBase 自动合并。

---

## 架构约束

| ID | 约束 | 来源 | 影响范围 | 验证方式 |
|----|------|------|----------|----------|
| C-1 | inputFilter 仅在 isSpanStringMode_ 下生效（含单行和多行模式）；isSpanStringMode_ 通过构造函数参数一次性设置，运行期不变；与 TextInput/TextArea 无模式限制不同，RichEditor 仅 spanString 模式生效 | 需求澄清 Q-1 + 代码验证(rich_editor_pattern.h L255) + 规格变更(取消isSingleLineMode_限制) | FilterWithInputFilter 实现 | 代码条件检查 |
| C-2 | 过滤优先级: inputFilter → maxLength（先过滤再截断）；与 TextInput 的 FilterValue 第二阶段一致，但与 PreprocessString 第一阶段不同（PreprocessString 先截断再过滤），差异可接受 | 需求澄清 Q-4 + 代码验证(content_controller.cpp L66-99 vs L257-287) | ProcessInsertValue/InsertValueInStyledString 插入点顺序 | 代码位置确认 |
| C-3 | 遵循 AGENTS.md 约束：不修改 Public API 签名/语义/错误码 | AGENTS.md | 全链路 | 代码 review |
| C-4 | 遵循 C API X-macro 属性路由模式 | design.md D-4 | .def + style_modifier | 条目追加位置 |
| C-5 | 事件数据提取使用 OH_ArkUI_NodeEvent_GetStringAsyncEvent | C API 事件机制 | event_converter + lambda 构造 | 代码 review |
| C-6 | 属性设置和事件注册必须分两次独立调用（CAPI 单体设计） | C API 设计哲学 | 架构整体 | 接口设计 |
| C-7 | inputFilter 过滤必须在所有内容回调之前执行，回调拿到的值是过滤+截断后的值 | 参考文档3.3回调关系分析 | FilterWithInputFilter 插入点位置 | 代码位置确认(过滤在 aboutToIMEInput/onWillChange 等回调之前) |
| C-8 | RichEditor 无两阶段过滤机制（仅过滤插入值，不对全量做二次过滤），与 TextInput 的 PreprocessString+FilterValue 差异是可接受的；但正则变更时需对已有内容做全量重新过滤 | 参考文档3.2两重过滤机制 + 规格变更(新增属性变更重新过滤) | design.md D-5 + D-6 | 过滤仅作用于 text/subValue 变量；正则变更时全量重新过滤 |
| C-9 | inputFilter 正则变更时，对已有内容做全量重新过滤（静默执行，不触发 onWillChange 确认），与 TextInput 的行为一致；被拒字符通过 onInputFilterError 回调通知 | 规格变更(新增AC-12) + TextInput FilterInitializeText机制参考(text_field_pattern.cpp L4808-4848, L13860-13867，isFilterChanged_在SetInputFilter时未被设为true) | FilterInitializeText 实现 | 代码逻辑验证 |

---

## 调用链设计

### 属性设置链

```
nodeAPI->setAttribute(node, NODE_TEXT_EDITOR_INPUT_FILTER, {.string="^[a-z]*$"})
  → style_modifier.cpp: SetRichEditorAttribute[索引31] → SetRichEditorInputFilter
    → getRichEditorModifier()->setRichEditorInputFilter(nodeHandle, "^[a-z]*$")
      → rich_editor_dynamic_modifier.cpp: SetRichEditorInputFilter
        → RichEditorModelNG::SetInputFilter(frameNode, "^[a-z]*$")
          → RichEditorLayoutProperty::UpdateInputFilter("^[a-z]*$")
```

### 事件注册链

```
nodeAPI->registerNodeEvent(node, NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR, targetId, userData)
  → node_model.cpp: RegisterNodeEvent
    → ConvertOriginEventType(NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR) → ON_RICH_EDITOR_ON_INPUT_FILTER_ERROR(67009)
      → registerNodeAsyncEvent → NotifyComponentAsyncEvent
        → 67009/1000=67(ARKUI_RICH_EDITOR), 67009%1000=9
          → GetEventSetHandler[9] → SetOnRichEditorInputFilterError
            → RichEditorModelNG::SetOnInputFilterError(frameNode, lambda)
              → RichEditorEventHub::SetOnInputFilterError(lambda)
```

### 过滤触发链

```
rich_editor_pattern.cpp: ProcessInsertValue(L6840)
  → FilterWithInputFilter(text)
    → 检查 isSpanStringMode_
    → 从 RichEditorLayoutProperty 读取 InputFilter 正则
    → text_filter_utils::FilterWithRegex(filter, text) → 提取非法字符
    → 有非法字符 → RichEditorEventHub::FireOnInputFilterError(errorU16Str)
      → lambda 构造 ArkUINodeEvent{kind=TEXT_INPUT, subKind=67009, nativeStringPtr=errorUtf8}
        → SendArkUISyncEvent → CAPI eventReceiver
          → OH_ArkUI_NodeEvent_GetStringAsyncEvent → .pStr
    → 移除非法字符后 text 被修改
  → ProcessTextTruncationOperation(text)  // maxLength 截断
```

---

## 受影响文件全量清单

- interfaces/native/native_node.h — 修改：追加 NODE_TEXT_EDITOR_INPUT_FILTER(22031) + NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR(22009) 枚举值
- interfaces/native/node/rich_editor_properties.def — 修改：末尾追加 X(1,1,1,RichEditorInputFilter) 条目
- interfaces/native/node/style_modifier.cpp — 修改：X-macro 自动展开，新增 Set/Get/ResetRichEditorInputFilter 函数
- frameworks/core/interfaces/arkoala/arkoala_api.h — 修改：追加 ON_RICH_EDITOR_ON_INPUT_FILTER_ERROR(67009) 子类型枚举 + 5 个 Modifier 函数指针(set/get/reset InputFilter + set/reset OnInputFilterError)
- frameworks/core/components_ng/pattern/rich_editor/bridge/rich_editor_dynamic_modifier.cpp — 修改：新增 5 个桥接实现函数 + GetEventSetHandler 数组追加索引9 + GetEventResetHandler 数组追加索引9 + GetRichEditorDynamicModifier 初始化追加 5 个赋值
- interfaces/native/node/event_converter.cpp — 修改：ConvertOriginEventType + ConvertToNodeEventType + IsStringEvent 追加
- frameworks/core/components_ng/pattern/rich_editor/rich_editor_model.h — 修改：追加 5 个虚方法
- frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.h — 修改：追加 5 个 override + 5 个 static 声明
- frameworks/core/components_ng/pattern/rich_editor/rich_editor_model_ng.cpp — 修改：实现上述 10 个方法
- frameworks/core/components_ng/pattern/rich_editor/rich_editor_layout_property.h — 修改：追加 ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(InputFilter, std::string, PROPERTY_UPDATE_MEASURE)
- frameworks/core/components_ng/pattern/rich_editor/rich_editor_layout_property.cpp — 修改：属性实现（ACE宏自动生成，确认无需手动代码）
- frameworks/core/components_ng/pattern/rich_editor/rich_editor_event_hub.h — 修改：追加 SetOnInputFilterError / FireOnInputFilterError / ResetOnInputFilterError 声明 + onInputFilterError_ 私有成员
- frameworks/core/components_ng/pattern/rich_editor/rich_editor_event_hub.cpp — 修改：实现上述 3 个方法
- frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.h — 修改：追加 FilterWithInputFilter + FilterInitializeText 私有方法声明
- frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.cpp — 修改：实现 FilterWithInputFilter + FilterInitializeText + 2 处插入点(ProcessInsertValue L6840前 + InsertValueInStyledString L451前) + SetInputFilter 属性变更回调
- frameworks/core/components_ng/pattern/text_field/text_filter_utils.h — 新建：TextFilterUtils namespace 下 FilterWithRegex + ContentToWstring + ContentToU16string + RemoveErrorTextFromValue 函数声明
- frameworks/core/components_ng/pattern/text_field/text_filter_utils.cpp — 新建：上述 4 个函数实现（从 content_controller.cpp 迁移）
- frameworks/core/components_ng/pattern/text_field/content_controller.h — 修改：删除 RemoveErrorTextFromValue 静态成员声明(L103)；保留 FilterWithRegex 声明(L104) 作为 wrapper
- frameworks/core/components_ng/pattern/text_field/content_controller.cpp — 修改：(1)删除匿名namespace块内 ContentToWstring(L41)/ContentToU16string(L53) 定义；(2)删除 RemoveErrorTextFromValue 定义(L289-308)；(3)FilterWithRegex 定义(L314-324) 改为 wrapper 调用 TextFilterUtils::FilterWithRegex
- frameworks/core/components_ng/pattern/text_field/BUILD.gn — 修改：sources 列表中 content_controller.cpp 之后新增 text_filter_utils.cpp

---

## 风险与缓解

| 风险 | 类型 | 影响 | 缓解措施 | 残余风险 |
|------|------|------|----------|----------|
| R-1: FilterWithRegex 提取后 TextField 行为回归 | 技术 | 高 | 单元测试覆盖 + content_controller.cpp 仅改调用方式不改逻辑 | 低 |
| R-2: RichEditor 过滤逻辑与 TextInput 差异（无两阶段机制） | 技术 | 中 | Pattern 层仅过滤插入值；正则变更时全量重新过滤 | 低（已对齐需求） |
| R-3: 事件 kind 使用 TEXT_INPUT 而非 RICH_EDITOR | 设计 | 低 | 这是 C API 事件提取机制的既有约束，TextInput 同样如此 | 低（可接受） |
| R-4: X-macro 追加位置错误导致 subTypeId 索引偏移 | 技术 | 高 | 严格在末尾追加，且枚举值与 .def 条目序号对应 | 低 |
| R-5: 枚举值与未来新增属性冲突 | 技术 | 低 | 22031/22009 紧跟当前最大值，后续新增继续追加即可 | 低 |
| R-6: 正则变更时静默全量重新过滤（无 onWillChange 确认，与 TextInput 一致） | 设计 | 低 | 与 TextInput 行为保持一致，用户无法拒绝正则变更后的内容修改 | 低（已对齐 TextInput） |
| R-7: 多行模式下过滤逻辑的插入路径差异 | 技术 | 中 | isSpanStringMode_ 导致 ProcessInsertValue 和 InsertValueInStyledString 两条路径，需分别插入过滤 | 低（两条路径均已标注） |

---

## 设计自审清单

- [x] 无"待定""TBD"占位符
- [x] 所有设计决策有取舍理由
- [x] 架构约束有来源和验证方式
- [x] 受影响文件清单完整（21 文件）
- [x] 风险有缓解措施和残余风险评估
- [x] 调用链设计覆盖属性设置、事件注册、过滤触发三条链路
- [x] 与 proposal 基线一致（方案 A-1、生效约束、过滤优先级）
- [x] 回调与 inputFilter 关系已约束（C-7：过滤在回调之前；C-8：无两阶段机制差异已声明）
- [x] onSubmit 特殊处理已在 spec AC-11 中声明（不触发 NEW_LINE 分支）
- [x] 正则变更全量重新过滤机制已设计（D-6 + C-9），静默执行与 TextInput 一致
- [x] 多行模式支持已纳入（C-1 仅 isSpanStringMode_，含单行和多行）
- [x] 与 TextInput 差异已声明（C-8 单阶段过滤 vs 两阶段；正则变更静默过滤一致）
