/*
 * TASK-3: Pattern 过滤逻辑实现 — 2 个文件修改骨架
 * 关联 AC: AC-7, AC-8, AC-9, AC-11
 * 参考: content_controller.cpp FilterWithRegex (通过 text_filter_utils 共享函数调用)
 *       rich_editor_pattern.cpp ProcessInsertValue (L6835-6842) + InsertValueInStyledString (L444-453)
 * 关键约束:
 *   design.md C-1: 仅 isSpanStringMode_ && isSingleLineMode_ 下生效
 *   design.md C-2: 过滤优先级 inputFilter → maxLength
 *   design.md D-5: 过滤插入点在 ProcessTextTruncationOperation 之前
 *   design.md D-1: 使用 text_filter_utils::FilterWithRegex (方案 A-1)
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
    // 约束 C-1: 仅 isSpanStringMode_ && isSingleLineMode_ 下生效
    // isSpanStringMode_ 继承自 TextPattern (text_pattern.h:667)
    if (!isSpanStringMode_ || !isSingleLineMode_) {
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
