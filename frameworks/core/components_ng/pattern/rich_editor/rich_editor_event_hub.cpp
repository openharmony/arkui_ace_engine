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
int32_t RichEditorInsertValue::GetInsertOffset() const
{
    return insertOffset_;
}

const std::string& RichEditorInsertValue::GetInsertValue() const
{
    return insertValue_;
}

int32_t RichEditorAbstractSpanResult::GetSpanIndex() const
{
    return spanIndex_;
}

int32_t RichEditorAbstractSpanResult::GetSpanRangeStart() const
{
    return spanRangeStart_;
}

int32_t RichEditorAbstractSpanResult::GetSpanRangeEnd() const
{
    return spanRangeEnd_;
}

SpanResultType RichEditorAbstractSpanResult::GetType() const
{
    return spanType_;
}

int32_t RichEditorAbstractSpanResult::OffsetInSpan() const
{
    return offsetInSpan_;
}

int32_t RichEditorAbstractSpanResult::GetEraseLength() const
{
    return eraseLength_;
}

const std::string& RichEditorAbstractSpanResult::GetValue() const
{
    return value_;
}

const std::string& RichEditorAbstractSpanResult::GetFontColor() const
{
    return fontColor_;
}

double RichEditorAbstractSpanResult::GetFontSize() const
{
    return fontSize_;
}

Ace::FontStyle RichEditorAbstractSpanResult::GetFontStyle() const
{
    return fontStyle_;
}

int32_t RichEditorAbstractSpanResult::GetFontWeight() const
{
    return fontWeigth_;
}

const std::string& RichEditorAbstractSpanResult::GetFontFamily() const
{
    return fontFamily_;
}

TextDecoration RichEditorAbstractSpanResult::GetTextDecoration() const
{
    return textDecoration_;
}

const std::string& RichEditorAbstractSpanResult::GetColor() const
{
    return color_;
}

const RefPtr<PixelMap>& RichEditorAbstractSpanResult::GetValuePixelMap() const
{
    return valuePixelMap_;
}

const std::string& RichEditorAbstractSpanResult::GetValueResourceStr() const
{
    return valueResourceStr_;
}

int32_t RichEditorAbstractSpanResult::GetSizeWidth() const
{
    return width_;
}

int32_t RichEditorAbstractSpanResult::GetSizeHeight() const
{
    return height_;
}

VerticalAlign RichEditorAbstractSpanResult::GetVerticalAlign() const
{
    return verticalAlign_;
}

ImageFit RichEditorAbstractSpanResult::GetObjectFit() const
{
    return objectFit_;
}

int32_t RichEditorDeleteValue::GetOffset() const
{
    return offset_;
}

RichEditorDeleteDirection RichEditorDeleteValue::GetRichEditorDeleteDirection() const
{
    return direction_;
}

int32_t RichEditorDeleteValue::GetLength() const
{
    return length_;
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
