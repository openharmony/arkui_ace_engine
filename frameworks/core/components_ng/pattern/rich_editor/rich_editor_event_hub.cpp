/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/rich_editor/rich_editor_event_hub.h"
#include "base/utils/utf_helper.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"

namespace OHOS::Ace::NG {
void RichEditorInsertValue::SetInsertOffset(int32_t insertOffset)
{
    insertOffset_ = insertOffset;
}

int32_t RichEditorInsertValue::GetInsertOffset() const
{
    return insertOffset_;
}

void RichEditorInsertValue::SetInsertValue(const std::u16string& insertValue)
{
    insertValue_ = insertValue;
}

void RichEditorInsertValue::SetPreviewText(const std::u16string& previewText)
{
    previewText_ = previewText;
}

const std::u16string& RichEditorInsertValue::GetInsertValue() const
{
    return insertValue_;
}

const std::u16string& RichEditorInsertValue::GetPreviewText() const
{
    return previewText_;
}

void RichEditorAbstractSpanResult::SetSpanIndex(int32_t spanIndex)
{
    spanIndex_ = spanIndex;
}

int32_t RichEditorAbstractSpanResult::GetSpanIndex() const
{
    return spanIndex_;
}

void RichEditorAbstractSpanResult::SetSpanRangeStart(int32_t spanRangeStart)
{
    spanRangeStart_ = spanRangeStart;
}

int32_t RichEditorAbstractSpanResult::GetSpanRangeStart() const
{
    return spanRangeStart_;
}

void RichEditorAbstractSpanResult::SetSpanRangeEnd(int32_t spanRangeEnd)
{
    spanRangeEnd_ = spanRangeEnd;
}

int32_t RichEditorAbstractSpanResult::GetSpanRangeEnd() const
{
    return spanRangeEnd_;
}

void RichEditorAbstractSpanResult::SetSpanType(SpanResultType spanType)
{
    spanType_ = spanType;
}

SpanResultType RichEditorAbstractSpanResult::GetType() const
{
    return spanType_;
}

void RichEditorAbstractSpanResult::SetOffsetInSpan(int32_t offsetInSpan)
{
    offsetInSpan_ = offsetInSpan;
}

int32_t RichEditorAbstractSpanResult::OffsetInSpan() const
{
    return offsetInSpan_;
}

void RichEditorAbstractSpanResult::SetEraseLength(int32_t eraseLength)
{
    eraseLength_ = eraseLength;
}

int32_t RichEditorAbstractSpanResult::GetEraseLength() const
{
    return eraseLength_;
}

void RichEditorAbstractSpanResult::SetValue(const std::u16string& value)
{
    value_ = value;
}

const std::u16string& RichEditorAbstractSpanResult::GetValue() const
{
    return value_;
}

void RichEditorAbstractSpanResult::SetPreviewText(const std::u16string& previewText)
{
    previewText_ = previewText;
}

const std::u16string& RichEditorAbstractSpanResult::GetPreviewText() const
{
    return previewText_;
}

void RichEditorAbstractSpanResult::SetFontColor(const std::string& fontColor)
{
    fontColor_ = fontColor;
}

void RichEditorAbstractSpanResult::SetFontFeature(const FONT_FEATURES_LIST& fontFeature)
{
    fontFeature_ = fontFeature;
}

const FONT_FEATURES_LIST& RichEditorAbstractSpanResult::GetFontFeatures() const
{
    return fontFeature_;
}

void RichEditorAbstractSpanResult::SetTextStyle(TextStyleResult textStyle)
{
    textStyle_ = textStyle;
}

TextStyleResult RichEditorAbstractSpanResult::GetTextStyle() const
{
    return textStyle_;
}

void RichEditorAbstractSpanResult::SetLineHeight(double lineHeight)
{
    lineHeight_ = lineHeight;
}

double RichEditorAbstractSpanResult::GetLineHeight() const
{
    return lineHeight_;
}

void RichEditorAbstractSpanResult::SetHalfLeading(bool halfLeading)
{
    halfLeading_ = halfLeading;
}

bool RichEditorAbstractSpanResult::GetHalfLeading() const
{
    return halfLeading_;
}

void RichEditorAbstractSpanResult::SetLetterspacing(double letterSpacing)
{
    letterSpacing_ = letterSpacing;
}

double RichEditorAbstractSpanResult::GetLetterspacing() const
{
    return letterSpacing_;
}

const std::string& RichEditorAbstractSpanResult::GetFontColor() const
{
    return fontColor_;
}

void RichEditorAbstractSpanResult::SetFontSize(double fontSize)
{
    fontSize_ = fontSize;
}

double RichEditorAbstractSpanResult::GetFontSize() const
{
    return fontSize_;
}

void RichEditorAbstractSpanResult::SetValueResource(const RefPtr<ResourceObject>& valueResource)
{
    valueResource_ = valueResource;
}

const RefPtr<ResourceObject> RichEditorAbstractSpanResult::GetValueResource() const
{
    return valueResource_;
}

void RichEditorAbstractSpanResult::SetValueString(const std::string& valueString)
{
    valueString_ = valueString;
}

const std::string RichEditorAbstractSpanResult::GetValueString() const
{
    return valueString_;
}

void RichEditorAbstractSpanResult::SetSymbolSpanStyle(const SymbolSpanStyle& symbolSpanStyle)
{
    symbolSpanStyle_ = symbolSpanStyle;
}

const SymbolSpanStyle RichEditorAbstractSpanResult::GetSymbolSpanStyle() const
{
    return symbolSpanStyle_;
}

void RichEditorAbstractSpanResult::SetFontWeight(int32_t fontWeigth)
{
    fontWeigth_ = fontWeigth;
}

int32_t RichEditorAbstractSpanResult::GetFontWeight() const
{
    return fontWeigth_;
}

void RichEditorAbstractSpanResult::SetFontFamily(const std::string& fontFamily)
{
    fontFamily_ = fontFamily;
}

const std::string& RichEditorAbstractSpanResult::GetFontFamily() const
{
    return fontFamily_;
}

void RichEditorAbstractSpanResult::SetTextDecoration(TextDecoration textDecoration)
{
    textDecoration_ = textDecoration;
}

TextDecoration RichEditorAbstractSpanResult::GetTextDecoration() const
{
    return textDecoration_;
}

void RichEditorAbstractSpanResult::SetColor(const std::string& color)
{
    color_ = color;
}

const std::string& RichEditorAbstractSpanResult::GetColor() const
{
    return color_;
}

void RichEditorAbstractSpanResult::SetTextDecorationStyle(TextDecorationStyle textDecorationStyle)
{
    textDecorationStyle_ = textDecorationStyle;
}

TextDecorationStyle RichEditorAbstractSpanResult::GetTextDecorationStyle() const
{
    return textDecorationStyle_;
}

void RichEditorAbstractSpanResult::SetLineThicknessScale(float thicknessScale)
{
    lineThicknessScale_ = thicknessScale;
}

float RichEditorAbstractSpanResult::GetLineThicknessScale() const
{
    return lineThicknessScale_;
}

void RichEditorAbstractSpanResult::SetValuePixelMap(const RefPtr<PixelMap>& valuePixelMap)
{
    valuePixelMap_ = valuePixelMap;
}

const RefPtr<PixelMap>& RichEditorAbstractSpanResult::GetValuePixelMap() const
{
    return valuePixelMap_;
}

void RichEditorAbstractSpanResult::SetValueResourceStr(const std::string valueResourceStr)
{
    valueResourceStr_ = valueResourceStr;
}

const std::string& RichEditorAbstractSpanResult::GetValueResourceStr() const
{
    return valueResourceStr_;
}

void RichEditorAbstractSpanResult::SetSizeWidth(int32_t width)
{
    width_ = width;
}

int32_t RichEditorAbstractSpanResult::GetSizeWidth() const
{
    return width_;
}

void RichEditorAbstractSpanResult::SetSizeHeight(int32_t height)
{
    height_ = height;
}

int32_t RichEditorAbstractSpanResult::GetSizeHeight() const
{
    return height_;
}

void RichEditorAbstractSpanResult::SetVerticalAlign(VerticalAlign verticalAlign)
{
    verticalAlign_ = verticalAlign;
}

VerticalAlign RichEditorAbstractSpanResult::GetVerticalAlign() const
{
    return verticalAlign_;
}

void RichEditorAbstractSpanResult::SetImageFit(ImageFit objectFit)
{
    objectFit_ = objectFit;
}

ImageFit RichEditorAbstractSpanResult::GetObjectFit() const
{
    return objectFit_;
}

void RichEditorAbstractSpanResult::SetUrlAddress(const std::u16string& urlAddress)
{
    urlAddress_ = urlAddress;
}

const std::u16string& RichEditorAbstractSpanResult::GetUrlAddress() const
{
    return urlAddress_;
}

void RichEditorDeleteValue::SetOffset(int32_t offset)
{
    offset_ = offset;
}

int32_t RichEditorDeleteValue::GetOffset() const
{
    return offset_;
}

void RichEditorDeleteValue::SetRichEditorDeleteDirection(RichEditorDeleteDirection direction)
{
    direction_ = direction;
}

RichEditorDeleteDirection RichEditorDeleteValue::GetRichEditorDeleteDirection() const
{
    return direction_;
}

void RichEditorDeleteValue::SetLength(int32_t length)
{
    length_ = length;
}

int32_t RichEditorDeleteValue::GetLength() const
{
    return length_;
}

void RichEditorDeleteValue::SetRichEditorDeleteSpans(const RichEditorAbstractSpanResult& deleteSpan)
{
    richEditorDeleteSpans_.emplace_back(deleteSpan);
}

void RichEditorDeleteValue::ResetRichEditorDeleteSpans()
{
    richEditorDeleteSpans_.clear();
}

const std::list<RichEditorAbstractSpanResult>& RichEditorDeleteValue::GetRichEditorDeleteSpans() const
{
    return richEditorDeleteSpans_;
}

void RichEditorChangeValue::SetRichEditorOriginalSpans(const RichEditorAbstractSpanResult& span)
{
    originalSpans_.emplace_back(span);
}

const std::vector<RichEditorAbstractSpanResult>& RichEditorChangeValue::GetRichEditorOriginalSpans() const
{
    return originalSpans_;
}

void RichEditorChangeValue::SetRichEditorReplacedSpans(const RichEditorAbstractSpanResult& span)
{
    replacedSpans_.emplace_back(span);
}

const std::vector<RichEditorAbstractSpanResult>& RichEditorChangeValue::GetRichEditorReplacedSpans() const
{
    return replacedSpans_;
}

void RichEditorChangeValue::SetRichEditorReplacedImageSpans(const RichEditorAbstractSpanResult& span)
{
    replacedImageSpans_.emplace_back(span);
}

const std::vector<RichEditorAbstractSpanResult>& RichEditorChangeValue::GetRichEditorReplacedImageSpans() const
{
    return replacedImageSpans_;
}

void RichEditorChangeValue::SetRichEditorReplacedSymbolSpans(const RichEditorAbstractSpanResult& span)
{
    replacedSymbolSpans_.emplace_back(span);
}

const std::vector<RichEditorAbstractSpanResult>& RichEditorChangeValue::GetRichEditorReplacedSymbolSpans() const
{
    return replacedSymbolSpans_;
}

void RichEditorChangeValue::SetRangeBefore(const TextRange& rangeBefore)
{
    rangeBefore_ = rangeBefore;
}

TextRange RichEditorChangeValue::GetRangeBefore() const
{
    return rangeBefore_;
}

void RichEditorChangeValue::SetRangeAfter(const TextRange& rangeAfter)
{
    rangeAfter_ = rangeAfter;
}

TextRange RichEditorChangeValue::GetRangeAfter() const
{
    return rangeAfter_;
}

TextChangeReason RichEditorChangeValue::GetChangeReason() const
{
    return changeReason_;
}

void StyledStringChangeValue::SetRangeBefore(const TextRange& range)
{
    rangeBefore_ = range;
}

TextRange StyledStringChangeValue::GetRangeBefore() const
{
    return rangeBefore_;
}

void StyledStringChangeValue::SetRangeAfter(const TextRange& range)
{
    rangeAfter_ = range;
}

TextRange StyledStringChangeValue::GetRangeAfter() const
{
    return rangeAfter_;
}

void StyledStringChangeValue::SetReplacementString(const RefPtr<SpanStringBase>& styledString)
{
    replacementString_ = styledString;
}

const RefPtr<SpanStringBase> StyledStringChangeValue::GetReplacementString() const
{
    return replacementString_;
}

void StyledStringChangeValue::SetPreviewText(const RefPtr<SpanStringBase>& previewText)
{
    previewText_ = previewText;
}

const RefPtr<SpanStringBase> StyledStringChangeValue::GetPreviewText() const
{
    return previewText_;
}

void RichEditorEventHub::SetOnReady(std::function<void()>&& func)
{
    onReady_ = std::move(func);
}

void RichEditorEventHub::FireOnReady()
{
    if (onReady_) {
        onReady_();
        auto host = GetFrameNode();
        CHECK_NULL_VOID(host);
        auto* context = host->GetContext();
        CHECK_NULL_VOID(context);
        context->AddAfterRenderTask([host]() { host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); });
    }
}

void RichEditorEventHub::SetAboutToIMEInput(std::function<bool(const RichEditorInsertValue&)>&& func)
{
    aboutToIMEInput_ = std::move(func);
}

bool RichEditorEventHub::FireAboutToIMEInput(const RichEditorInsertValue& info)
{
    return aboutToIMEInput_ ? aboutToIMEInput_(info) : true;
}

void RichEditorEventHub::SetOnIMEInputComplete(std::function<void(const RichEditorAbstractSpanResult&)>&& func)
{
    onIMEInputComplete_ = std::move(func);
}

void RichEditorEventHub::FireOnIMEInputComplete(const RichEditorAbstractSpanResult& info)
{
    if (onIMEInputComplete_)
        onIMEInputComplete_(info);
}

void RichEditorEventHub::SetOnDidIMEInput(std::function<void(const TextRange&)>&& func)
{
    onDidIMEInput_ = std::move(func);
}

void RichEditorEventHub::FireOnDidIMEInput(const TextRange& range)
{
    if (onDidIMEInput_)
        onDidIMEInput_(range);
}

void RichEditorEventHub::SetAboutToDelete(std::function<bool(const RichEditorDeleteValue&)>&& func)
{
    aboutToDelete_ = std::move(func);
}

bool RichEditorEventHub::FireAboutToDelete(const RichEditorDeleteValue& info)
{
    return aboutToDelete_ ? aboutToDelete_(info) : true;
}

void RichEditorEventHub::SetOnDeleteComplete(std::function<void()>&& func)
{
    onDeleteComplete_ = std::move(func);
}
void RichEditorEventHub::FireOnDeleteComplete()
{
    if (onDeleteComplete_) {
        onDeleteComplete_();
        UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "Radio.onChange");
    }
}

std::string RichEditorEventHub::GetDragExtraParams(const std::string& extraInfo, const Point& point, DragEventType type)
{
    auto host = GetFrameNode();
    CHECK_NULL_RETURN(host, extraInfo);
    auto pattern = host->GetPattern<RichEditorPattern>();
    CHECK_NULL_RETURN(host, extraInfo);

    auto json = JsonUtil::Create(true);
    if (type == DragEventType::DROP && timestamp_ != 0 && pattern->GetTimestamp() == timestamp_) {
        json->Put("isInComponent", true);
        timestamp_ = 0;
    }
    if (!extraInfo.empty()) {
        json->Put("extraInfo", extraInfo.c_str());
    }
    return json->ToString();
}

void RichEditorEventHub::SetOnEditingChange(std::function<void(const bool&)>&& func)
{
    onEditingChange_ = std::move(func);
}

void RichEditorEventHub::FireOnEditingChange(bool isEditing)
{
    if (onEditingChange_) {
        onEditingChange_(isEditing);
    }
}

void RichEditorEventHub::SetOnWillChange(std::function<bool(const RichEditorChangeValue&)>&& func)
{
    onWillChange_ = std::move(func);
}

bool RichEditorEventHub::FireOnWillChange(const RichEditorChangeValue& info)
{
    return onWillChange_ ? onWillChange_(info) : true;
}

bool RichEditorEventHub::HasOnWillChange() const
{
    return static_cast<bool>(onWillChange_);
}

void RichEditorEventHub::SetOnDidChange(std::function<void(const RichEditorChangeValue&)>&& func)
{
    onDidChange_ = std::move(func);
}

void RichEditorEventHub::FireOnDidChange(const RichEditorChangeValue& changeValue)
{
    if (onDidChange_) {
        onDidChange_(changeValue);
    }
}

bool RichEditorEventHub::HasOnDidChange() const
{
    auto host = GetFrameNode();
    CHECK_NULL_RETURN(host, false);
    auto pattern = host->GetPattern<RichEditorPattern>();
    CHECK_NULL_RETURN(pattern, false);
    pattern->SetContentChange(true);
    return static_cast<bool>(onDidChange_);
}

void RichEditorEventHub::SetOnCut(std::function<void(NG::TextCommonEvent&)>&& func)
{
    onCut_ = std::move(func);
}

void RichEditorEventHub::FireOnCut(NG::TextCommonEvent& value)
{
    if (onCut_) {
        onCut_(value);
    }
}

void RichEditorEventHub::SetOnCopy(std::function<void(NG::TextCommonEvent&)>&& func)
{
    onCopy_ = std::move(func);
}

void RichEditorEventHub::FireOnCopy(NG::TextCommonEvent& value)
{
    if (onCopy_) {
        onCopy_(value);
    }
}

void RichEditorEventHub::SetOnShare(std::function<void(NG::TextCommonEvent&)>&& func)
{
    onShare_ = std::move(func);
}

void RichEditorEventHub::FireOnShare(NG::TextCommonEvent& value)
{
    if (onShare_) {
        onShare_(value);
    }
}

void RichEditorEventHub::SetOnStyledStringWillChange(std::function<bool(const StyledStringChangeValue&)> && func)
{
    onStyledStringWillChange_ = std::move(func);
}

bool RichEditorEventHub::FireOnStyledStringWillChange(const StyledStringChangeValue& info)
{
    return onStyledStringWillChange_ ? onStyledStringWillChange_(info) : true;
}

bool RichEditorEventHub::HasOnStyledStringWillChange() const
{
    return static_cast<bool>(onStyledStringWillChange_);
}

void RichEditorEventHub::SetOnStyledStringDidChange(std::function<void(const StyledStringChangeValue&)> && func)
{
    onStyledStringDidChange_ = std::move(func);
}

void RichEditorEventHub::FireOnStyledStringDidChange(const StyledStringChangeValue& info)
{
    onStyledStringDidChange_(info);
}

bool RichEditorEventHub::HasOnStyledStringDidChange() const
{
    return static_cast<bool>(onStyledStringDidChange_);
}
} // namespace OHOS::Ace::NG
