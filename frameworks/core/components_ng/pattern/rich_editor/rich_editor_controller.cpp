/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/pattern/rich_editor/rich_editor_controller.h"

#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
namespace OHOS::Ace::NG {
void RichEditorController::SetPattern(const WeakPtr<RichEditorPattern>& pattern)
{
    pattern_ = pattern;
}

int32_t RichEditorController::AddImageSpan(const ImageSpanOptions& options)
{
    auto richEditorPattern = pattern_.Upgrade();
    int32_t spanIndex = 0;
    if (richEditorPattern) {
        spanIndex = richEditorPattern->AddImageSpan(options);
    }
    return spanIndex;
}

int32_t RichEditorController::AddTextSpan(const TextSpanOptions& options)
{
    auto richEditorPattern = pattern_.Upgrade();
    int32_t spanIndex = 0;
    if (richEditorPattern) {
        spanIndex = richEditorPattern->AddTextSpan(options);
    }
    return spanIndex;
}

int32_t RichEditorController::GetCaretOffset()
{
    int32_t position = -1;
    auto richEditorPattern = pattern_.Upgrade();
    position = richEditorPattern->GetCaretPosition();
    return position;
}

bool RichEditorController::SetCaretOffset(int32_t caretPosition)
{
    auto richEditorPattern = pattern_.Upgrade();
    if (richEditorPattern) {
        return richEditorPattern->SetCaretOffset(caretPosition);
    }
    return false;
}

void RichEditorController::UpdateSpanStyle(
    int32_t start, int32_t end, TextStyle textStyle, ImageSpanAttribute imageStyle)
{
    auto richEditorPattern = pattern_.Upgrade();
    CHECK_NULL_VOID(richEditorPattern);
    auto length = richEditorPattern->GetTextContentLength();
    start = std::max(0, start);
    if (end < 0 || end > length) {
        end = length;
    }
    if (start > end) {
        std::swap(start, end);
    }
    if (start > length || end < 0 || start == end) {
        LOGI("params error , return");
        return;
    }
    richEditorPattern->SetUpdateSpanStyle(updateSpanStyle_);
    richEditorPattern->UpdateSpanStyle(start, end, textStyle, imageStyle);
}

void RichEditorController::SetTypingStyle(struct UpdateSpanStyle& typingStyle, TextStyle textStyle)
{
    auto richEditorPattern = AceType::DynamicCast<RichEditorPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(richEditorPattern);
    richEditorPattern->SetTypingStyle(typingStyle, textStyle);
}

void RichEditorController::SetUpdateSpanStyle(struct UpdateSpanStyle updateSpanStyle)
{
    updateSpanStyle_ = updateSpanStyle;
}

RichEditorSelection RichEditorController::GetSpansInfo(int32_t start, int32_t end)
{
    RichEditorSelection value;
    auto richEditorPattern = pattern_.Upgrade();
    if (richEditorPattern) {
        value = richEditorPattern->GetSpansInfo(start, end, GetSpansMethod::GETSPANS);
    }
    return value;
}

void RichEditorController::DeleteSpans(const RangeOptions& options)
{
    auto richEditorPattern = pattern_.Upgrade();
    if (richEditorPattern) {
        richEditorPattern->DeleteSpans(options);
    }
}

void RichEditorController::CloseSelectionMenu()
{
    auto richEditorPattern = pattern_.Upgrade();
    if (richEditorPattern) {
        richEditorPattern->CloseSelectionMenu();
    }
}

void RichEditorController::UpdateParagraphStyle(int32_t start, int32_t end, const struct UpdateParagraphStyle &style)
{
    auto richEditorPattern = pattern_.Upgrade();
    if (richEditorPattern) {
        richEditorPattern->UpdateParagraphStyle(start, end, style);
    }
}
std::vector<ParagraphInfo> RichEditorController::GetParagraphsInfo(int32_t start, int32_t end)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, {});
    return pattern->GetParagraphInfo(start, end);
}
} // namespace OHOS::Ace::NG
