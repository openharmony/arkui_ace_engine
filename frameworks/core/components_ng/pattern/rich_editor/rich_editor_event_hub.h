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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_EVENT_HUB_H

#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_selection.h"

namespace OHOS::Ace::NG {
class TextInsertValueInfo {
public:
    TextInsertValueInfo() = default;
    ~TextInsertValueInfo() = default;
    void SetSpanIndex(int32_t spanIndex)
    {
        spanIndex_ = spanIndex;
    }

    int32_t GetSpanIndex() const
    {
        return spanIndex_;
    }

    void SetOffsetInSpan(int32_t offsetInSpan)
    {
        offsetInSpan_ = offsetInSpan;
    }

    int32_t GetOffsetInSpan() const
    {
        return offsetInSpan_;
    }

private:
    int32_t spanIndex_ = 0;
    int32_t offsetInSpan_ = 0;
};

class RichEditorInsertValue : public BaseEventInfo {
    DECLARE_ACE_TYPE(RichEditorInsertValue, BaseEventInfo)
public:
    RichEditorInsertValue() : BaseEventInfo("RichEditorInsertValue") {}
    ~RichEditorInsertValue() override = default;
    void SetInsertOffset(int32_t insertOffset);
    int32_t GetInsertOffset() const;
    void SetInsertValue(const std::string& insertValue);
    const std::string& GetInsertValue() const;

private:
    int32_t insertOffset_;
    std::string insertValue_;
};

enum class SpanResultType { TEXT, IMAGE };

class RichEditorAbstractSpanResult {
public:
    RichEditorAbstractSpanResult() = default;
    ~RichEditorAbstractSpanResult() = default;
    void SetSpanIndex(int32_t spanIndex);
    int32_t GetSpanIndex() const;
    void SetSpanRangeStart(int32_t spanRangeStart);
    int32_t GetSpanRangeStart() const;
    void SetSpanRangeEnd(int32_t spanRangeEnd);
    int32_t GetSpanRangeEnd() const;
    void SetSpanType(SpanResultType spanType);
    SpanResultType GetType() const;
    void SetOffsetInSpan(int32_t offsetInSpan);
    int32_t OffsetInSpan() const;
    void SetEraseLength(int32_t eraseLength);
    int32_t GetEraseLength() const;
    void SetValue(const std::string& value);
    const std::string& GetValue() const;
    void SetFontColor(const std::string& fontColor);
    const std::string& GetFontColor() const;
    void SetFontSize(double fontSize);
    double GetFontSize() const;
    void SetFontWeight(int32_t fontWeigth);
    int32_t GetFontWeight() const;
    void SetFontFamily(const std::string& fontFamily);
    const std::string& GetFontFamily() const;
    void SetTextDecoration(TextDecoration textDecoration);
    TextDecoration GetTextDecoration() const;
    void SetColor(const std::string& color);
    const std::string& GetColor() const;
    void SetValuePixelMap(const RefPtr<PixelMap>& valuePixelMap);
    const RefPtr<PixelMap>& GetValuePixelMap() const;
    void SetValueResourceStr(const std::string valueResourceStr);
    const std::string& GetValueResourceStr() const;
    void SetSizeWidth(int32_t width);
    int32_t GetSizeWidth() const;
    void SetSizeHeight(int32_t height);
    int32_t GetSizeHeight() const;
    void SetVerticalAlign(VerticalAlign verticalAlign);
    VerticalAlign GetVerticalAlign() const;
    void SetImageFit(ImageFit objectFit);
    ImageFit GetObjectFit() const;

    void SetFontStyle(FontStyle fontStyle)
    {
        fontStyle_ = fontStyle;
    }

    FontStyle GetFontStyle() const
    {
        return fontStyle_;
    }

private:
    int32_t spanIndex_ = 0;
    int32_t spanRangeStart_ = 0;
    int32_t spanRangeEnd_ = 0;
    SpanResultType spanType_;
    int32_t offsetInSpan_ = 0;
    int32_t eraseLength_ = 0;
    std::string value_;
    std::string fontColor_;
    double fontSize_ = 0.0;
    FontStyle fontStyle_;
    int32_t fontWeigth_ = 0;
    std::string fontFamily_;
    TextDecoration textDecoration_;
    std::string color_;
    RefPtr<PixelMap> valuePixelMap_;
    std::string valueResourceStr_;
    int32_t width_ = 0;
    int32_t height_ = 0;
    VerticalAlign verticalAlign_;
    ImageFit objectFit_;
};

enum class RichEditorDeleteDirection { BACKWARD = 0, FORWARD };

class RichEditorDeleteValue : public BaseEventInfo {
    DECLARE_ACE_TYPE(RichEditorDeleteValue, BaseEventInfo)
public:
    RichEditorDeleteValue() : BaseEventInfo("RichEditorDeleteValue") {}
    ~RichEditorDeleteValue() = default;
    void SetOffset(int32_t offset);
    int32_t GetOffset() const;
    void SetRichEditorDeleteDirection(RichEditorDeleteDirection direction);
    RichEditorDeleteDirection GetRichEditorDeleteDirection() const;
    void SetLength(int32_t length);
    int32_t GetLength() const;
    void SetRichEditorDeleteSpans(const RichEditorAbstractSpanResult& deleteSpan);
    const std::list<RichEditorAbstractSpanResult>& GetRichEditorDeleteSpans() const;

private:
    int32_t offset_ = 0;
    RichEditorDeleteDirection direction_;
    int32_t length_ = 0;
    std::list<RichEditorAbstractSpanResult> richEditorDeleteSpans_;
};

class RichEditorEventHub : public EventHub {
    DECLARE_ACE_TYPE(RichEditorEventHub, EventHub)

public:
    RichEditorEventHub() = default;
    ~RichEditorEventHub() override = default;
    void SetOnReady(std::function<void()>&& func);
    void FireOnReady();
    void SetAboutToIMEInput(std::function<bool(const RichEditorInsertValue&)>&& func);
    bool FireAboutToIMEInput(const RichEditorInsertValue& info);
    void SetOnIMEInputComplete(std::function<void(const RichEditorAbstractSpanResult&)>&& func);
    void FireOnIMEInputComplete(const RichEditorAbstractSpanResult& info);
    void SetAboutToDelete(std::function<bool(const RichEditorDeleteValue&)>&& func);
    bool FireAboutToDelete(const RichEditorDeleteValue& info);
    void SetOnDeleteComplete(std::function<void()>&& func);
    void FireOndeleteComplete();
    std::string GetDragExtraParams(const std::string& extraInfo, const Point& point, DragEventType type) override;

    void SetOnSelect(std::function<void(const BaseEventInfo*)>&& func)
    {
        onSelect_ = std::move(func);
    }

    void FireOnSelect(BaseEventInfo* value)
    {
        if (onSelect_) {
            onSelect_(value);
        }
    }

    void SetTimestamp(long long timestamp)
    {
        timestamp_ = timestamp;
    }

private:
    long long timestamp_;
    std::function<void()> onReady_;
    std::function<void(const BaseEventInfo*)> onSelect_;
    std::function<bool(const RichEditorInsertValue&)> aboutToIMEInput_;
    std::function<void(const RichEditorAbstractSpanResult&)> onIMEIputComplete_;
    std::function<bool(const RichEditorDeleteValue&)> aboutToDelete_;
    std::function<void()> onDeleteComplete_;
    ACE_DISALLOW_COPY_AND_MOVE(RichEditorEventHub);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_EVENT_HUB_H
