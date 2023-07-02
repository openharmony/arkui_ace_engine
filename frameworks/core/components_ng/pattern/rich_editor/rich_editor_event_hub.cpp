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
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_event_hub.h"

namespace OHOS::Ace::NG {
void RichEditorInsertValue::SetInsertOffset(int32_t insertOffset)
{
    insertOffset_ = insertOffset;
}

int32_t RichEditorInsertValue::GetInsertOffset() const
{
    return insertOffset_;
}

void RichEditorInsertValue::SetInsertValue(const std::string& insertValue)
{
    insertValue_ = insertValue;
}

const std::string& RichEditorInsertValue::GetInsertValue() const
{
    return insertValue_;
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

void RichEditorAbstractSpanResult::SetValue(const std::string& value)
{
    value_ = value;
}

const std::string& RichEditorAbstractSpanResult::GetValue() const
{
    return value_;
}

void RichEditorAbstractSpanResult::SetFontColor(const std::string& fontColor)
{
    fontColor_ = fontColor;
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

void RichEditorAbstractSpanResult::SetFontStyle(FontStyle fontStyle)
{
    fontStyle_ = fontStyle;
}

FontStyle RichEditorAbstractSpanResult::GetFontStyle() const
{
    return fontStyle_;
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

const std::list<RichEditorAbstractSpanResult>& RichEditorDeleteValue::GetRichEditorDeleteSpans() const
{
    return richEditorDeleteSpans_;
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
        host->PostTask([host]() { host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); });
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
    onIMEIputComplete_ = std::move(func);
}

void RichEditorEventHub::FireOnIMEInputComplete(const RichEditorAbstractSpanResult& info)
{
    if (onIMEIputComplete_)
        onIMEIputComplete_(info);
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
void RichEditorEventHub::FireOndeleteComplete()
{
    if (onDeleteComplete_)
        onDeleteComplete_();
}
} // namespace OHOS::Ace::NG
