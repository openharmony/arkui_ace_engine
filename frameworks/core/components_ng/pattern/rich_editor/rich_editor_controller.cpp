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
int32_t RichEditorController::AddImageSpan(const ImageSpanOptions& options)
{
    auto richEditorPattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(richEditorPattern, 0);
    return richEditorPattern->AddImageSpan(options);
}

int32_t RichEditorController::AddTextSpan(const TextSpanOptions& options)
{
    auto richEditorPattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(richEditorPattern, 0);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "textLength=%{public}d, offset=%{public}d",
        static_cast<int32_t>(options.value.length()), options.offset.value_or(-1));
    return richEditorPattern->AddTextSpan(options);
}

int32_t RichEditorController::AddSymbolSpan(const SymbolSpanOptions& options)
{
    auto richEditorPattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(richEditorPattern, 0);
    return richEditorPattern->AddSymbolSpan(options);
}

int32_t RichEditorController::AddPlaceholderSpan(const RefPtr<UINode>& customNode, const SpanOptionBase& options)
{
    auto richEditorPattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(richEditorPattern, 0);
    return richEditorPattern->AddPlaceholderSpan(customNode, options);
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
        return;
    }
    richEditorPattern->SetUpdateSpanStyle(updateSpanStyle_);
    richEditorPattern->UpdateSpanStyle(start, end, textStyle, imageStyle);
    richEditorPattern->TriggerAvoidOnCaretChange();
}

void RichEditorController::SetUpdateSpanStyle(struct UpdateSpanStyle updateSpanStyle)
{
    updateSpanStyle_ = updateSpanStyle;
}

SelectionInfo RichEditorController::GetSpansInfo(int32_t start, int32_t end)
{
    auto richEditorPattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(richEditorPattern, {});
    ACE_SCOPED_TRACE("RichEditorControllerGetSpansInfo");
    return richEditorPattern->GetSpansInfo(start, end, GetSpansMethod::GETSPANS);
}

SelectionInfo RichEditorController::GetSelectionSpansInfo()
{
    auto richEditorPattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(richEditorPattern, {});

    auto start = std::max(richEditorPattern->GetTextSelector().GetTextStart(), 0);
    auto end = std::max(richEditorPattern->GetTextSelector().GetTextEnd(), 0);
    if (start == end) {
        start = richEditorPattern->GetCaretPosition();
        end = richEditorPattern->GetCaretPosition();
    }
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "GetSelection, start, range=[%{public}d,%{public}d]", start, end);
    SelectionInfo value = richEditorPattern->GetSpansInfo(start, end, GetSpansMethod::GETSPANS);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "GetSelection end");
    return value;
}

void RichEditorController::DeleteSpans(const RangeOptions& options)
{
    auto richEditorPattern = pattern_.Upgrade();
    CHECK_NULL_VOID(richEditorPattern);
    richEditorPattern->DeleteSpans(options);
}

void RichEditorController::UpdateParagraphStyle(int32_t start, int32_t end, const struct UpdateParagraphStyle& style)
{
    auto richEditorPattern = pattern_.Upgrade();
    CHECK_NULL_VOID(richEditorPattern);
    richEditorPattern->UpdateParagraphStyle(start, end, style);
    richEditorPattern->TriggerAvoidOnCaretChange();
}
std::vector<ParagraphInfo> RichEditorController::GetParagraphsInfo(int32_t start, int32_t end)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, {});
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "GetParagraphsInfo, start, range=[%{public}d,%{public}d]", start, end);
    auto paragraphInfo = pattern->GetParagraphInfo(start, end);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "GetParagraphsInfo, end");
    return paragraphInfo;
}

RefPtr<SpanStringBase> RichEditorController::ToStyledString(int32_t start, int32_t end)
{
    auto richEditorPattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(richEditorPattern, nullptr);
    return richEditorPattern->ToStyledString(start, end);
}

SelectionInfo RichEditorController::FromStyledString(RefPtr<SpanStringBase> spanStringBase)
{
    auto richEditorPattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(richEditorPattern, SelectionInfo());
    auto spanString = AceType::DynamicCast<SpanString>(spanStringBase);
    CHECK_NULL_RETURN(spanString, SelectionInfo());
    return richEditorPattern->FromStyledString(spanString);
}

} // namespace OHOS::Ace::NG
