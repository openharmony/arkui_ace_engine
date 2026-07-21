/*
 * TASK-3: Pattern 过滤逻辑实现 — 2 个文件修改骨架
 * 关联 AC: AC-7, AC-8, AC-9, AC-11, AC-12
 * 参考: content_controller.cpp FilterWithRegex (通过 text_filter_utils 共享函数调用)
 *       rich_editor_pattern.cpp ProcessInsertValue (L6835-6842) + InsertValueInStyledString (L444-453)
 * 关键约束:
 *   design.md C-1: 仅 isSpanStringMode_ 下生效（含单行和多行，无 isSingleLineMode_ 限制）
 *   design.md C-2: 过滤优先级 inputFilter → maxLength
 *   design.md D-5: 过滤插入点在 ProcessTextTruncationOperation 之前
 *   design.md D-1: 使用 text_filter_utils::FilterWithRegex (方案 A-1)
 *   design.md D-6 + C-9: 正则变更时 FilterInitializeText 静默全量重新过滤（与 TextInput 一致，不触发 onWillChange）
 */

// =====================================================================
// 1. frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.h
//    追加 FilterWithInputFilter 私有方法声明
// =====================================================================

    // 追加在 private 段:
    bool FilterWithInputFilter(std::u16string& text);


// =====================================================================
// 2. frameworks/core/components_ng/pattern/rich_editor/rich_editor_pattern.cpp
//    实现 FilterWithInputFilter + 2 处插入点
// =====================================================================

// --- 需新增的 include ---
#include "text_filter_utils.h"  // TASK-0 共享工具

// --- FilterWithInputFilter 实现 ---
bool RichEditorPattern::FilterWithInputFilter(std::u16string& text)
{
    // 约束 C-1: 仅 isSpanStringMode_ 下生效（含单行和多行，无 isSingleLineMode_ 限制）
    // isSpanStringMode_ 继承自 TextPattern (text_pattern.h:667)，构造时一次性设置，运行期不变
    if (!isSpanStringMode_) {
        return true;  // 条件不满足时不执行过滤，但不阻止后续 maxLength 检查
    }

    // 从 LayoutProperty 读取 InputFilter 正则
    auto host = GetHost();
    CHECK_NULL_RETURN(host, true);
    auto layoutProperty = host->GetLayoutProperty<RichEditorLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, true);
    std::string inputFilter = layoutProperty->GetInputFilterValue_or_default("");

    // 约束 R-2/R-7: InputFilter 为空时不执行过滤
    if (inputFilter.empty()) {
        return true;
    }

    // 调用共享过滤工具 (design.md D-1: 方案 A-1)
    std::u16string filterU16 = StringUtils::Str8ToStr16(inputFilter);
    std::u16string errorText = TextFilterUtils::FilterWithRegex(filterU16, text);

    // 有被拒字符时触发 onInputFilterError 回调 (R-3)
    if (!errorText.empty()) {
        auto eventHub = host->GetEventHub<RichEditorEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireOnInputFilterError(errorText);
    }

    return true;  // 过滤完成，允许后续 maxLength 检查
}


// --- 插入点1: ProcessInsertValue (L6840 之前) ---
//    约束 C-2/D-5: inputFilter 在 maxLength 之前执行
//
// 原代码 (L6835-6842):
//   void RichEditorPattern::ProcessInsertValue(const std::u16string& insertValue, ...)
//   {
//       CONTENT_MODIFY_LOCK(this);
//       auto text = insertValue;
//       if (!ProcessTextTruncationOperation(text, shouldCommitInput)) {
//           return;
//       }
//
// 修改为:
//   void RichEditorPattern::ProcessInsertValue(const std::u16string& insertValue, ...)
//   {
//       CONTENT_MODIFY_LOCK(this);
//       auto text = insertValue;
//       // ---- 新增: inputFilter 过滤 (在 maxLength 之前) ----
//       if (!FilterWithInputFilter(text)) {
//           return;
//       }
//       // ---- 新增结束 ----
//       if (!ProcessTextTruncationOperation(text, shouldCommitInput)) {
//           return;
//       }


// --- 插入点2: InsertValueInStyledString (L451 之前) ---
//    属性字符串模式的过滤点
//
// 原代码 (L450-453):
//       auto subValue = insertValue;
//       if (!ProcessTextTruncationOperation(subValue, shouldCommitInput)) {
//           return;
//       }


// =====================================================================
// 3. FilterInitializeText — 正则变更时全量重新过滤 (AC-12)
//    参考: text_field_pattern.cpp FilterInitializeText (L4808-4848)
//    约束: design.md D-6 + C-9 — 静默执行，不触发 onWillChange，与 TextInput 一致
// =====================================================================

// --- rich_editor_pattern.h 追加声明 ---
//     void FilterInitializeText();

// --- rich_editor_pattern.cpp 实现 ---
void RichEditorPattern::FilterInitializeText()
{
    // 约束 C-1: 仅 isSpanStringMode_ 下生效
    if (!isSpanStringMode_ || !styledString_) {
        return;
    }

    // ① 从 LayoutProperty 读取新 InputFilter 正则
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<RichEditorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    std::string inputFilter = layoutProperty->GetInputFilterValue_or_default("");

    // InputFilter 为空时不执行过滤
    if (inputFilter.empty()) {
        return;
    }

    // ② 获取已有 StyledString 全量内容
    std::u16string fullText = styledString_->GetU16string();
    if (fullText.empty()) {
        return;
    }

    // ③ 调用共享过滤工具对全量内容做正则过滤
    std::u16string filterU16 = StringUtils::Str8ToStr16(inputFilter);
    std::u16string errorText = TextFilterUtils::FilterWithRegex(filterU16, fullText);

    // 无被拒字符，无需修改内容
    if (errorText.empty()) {
        return;
    }

    // ④ 逐个被拒字符位置，调用 styledString_->RemoveString 移除
    //    SpanItem/SpanBase 由 RemoveString 内置机制自动处理:
    //    - 5种重叠场景(完全包含/中间切开/左端重叠/右端重叠/无重叠偏移修正)
    //    - SpanItem 按行分裂(SplitSpansByNewLine)
    //    - SpanBase 自动合并(MergeIntervals)
    //    详见 design.md StyledString 章节
    //
    //    注意: 需从后往前删除，避免位置偏移导致后续删除位置错位
    //    FilterWithRegex 返回的 errorText 包含所有被拒字符，
    //    需逐个定位其在 fullText 中的位置
    std::u16string remainingText = styledString_->GetU16string();
    for (int32_t i = static_cast<int32_t>(remainingText.length()) - 1; i >= 0; --i) {
        char16_t ch = remainingText[i];
        // 检查该字符是否被正则拒绝（不在白名单内）
        std::u16string singleChar(1, ch);
        std::u16string singleFilter = filterU16;
        std::u16string singleError = TextFilterUtils::FilterWithRegex(singleFilter, singleChar);
        if (!singleError.empty()) {
            // 该字符被拒，从后往前删除避免偏移
            styledString_->RemoveString(i, 1);
        }
    }

    // ⑤ 被拒字符触发 onInputFilterError 回调 (R-3)
    auto eventHub = host->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnInputFilterError(errorText);

    // ⑥ 与 TextInput 行为一致：不触发 onWillChange（isFilterChanged_ 未设为 true）
    //    静默执行，用户无法拒绝正则变更后的内容修改
}


// =====================================================================
// 4. SetInputFilter 属性变更回调 — 触发 FilterInitializeText
//    参考: text_field_pattern.cpp L13860-13867
// =====================================================================

// 在 rich_editor_model_ng.cpp 的 SetInputFilter 实现中，
// 或在 rich_editor_pattern.cpp 的属性变更回调注册中追加:
//
// 属性变更回调 lambda:
//   {"inputFilter", [wp](RichEditorLayoutProperty* prop, RefPtr<PropertyValueBase> value) {
//       auto pattern = wp.Upgrade();
//       CHECK_NULL_VOID(pattern);
//       auto realValue = AceType::DynamicCast<PropertyValue<std::string>>(value);
//       CHECK_NULL_VOID(realValue);
//       prop->UpdateInputFilter(realValue->value_);
//       pattern->FilterInitializeText();  // 正则变更 → 全量重新过滤
//       // 注意: 不设 isFilterChanged_ = true，不触发 onWillChange
//   }}
//
// 修改为:
//       auto subValue = insertValue;
//       // ---- 新增: inputFilter 过滤 (在 maxLength 之前) ----
//       if (!FilterWithInputFilter(subValue)) {
//           return;
//       }
//       // ---- 新增结束 ----
//       if (!ProcessTextTruncationOperation(subValue, shouldCommitInput)) {
//           return;
//       }
