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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_EVENT_HUB_H

#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/rich_editor/selection_info.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text/text_model.h"
#include "core/common/ime/text_range.h"
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

    std::string ToString() const
    {
        return "spanIndex_: " + std::to_string(spanIndex_) + ", offsetInSpan_" + std::to_string(offsetInSpan_);
    }

private:
    int32_t spanIndex_ = 0;
    int32_t offsetInSpan_ = 0;
};

class ACE_FORCE_EXPORT RichEditorInsertValue : public BaseEventInfo {
    DECLARE_ACE_TYPE(RichEditorInsertValue, BaseEventInfo);
public:
    RichEditorInsertValue() : BaseEventInfo("RichEditorInsertValue") {}
    ~RichEditorInsertValue() override = default;
    void SetInsertOffset(int32_t insertOffset);
    int32_t GetInsertOffset() const;
    void SetInsertValue(const std::u16string& insertValue);
    void SetPreviewText(const std::u16string& previewText);
    const std::u16string& GetInsertValue() const;
    const std::u16string& GetPreviewText() const;

private:
    int32_t insertOffset_ = 0;
    std::u16string insertValue_;
    std::u16string previewText_;
};

enum class SpanResultType { TEXT, IMAGE, SYMBOL };

class ACE_FORCE_EXPORT RichEditorAbstractSpanResult {
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
    void SetValue(const std::u16string& value);
    const std::u16string& GetValue() const;
    void SetPreviewText(const std::u16string& previewText);
    const std::u16string& GetPreviewText() const;
    void SetFontColor(const std::string& fontColor);
    const std::string& GetFontColor() const;
    void SetFontFeature(const FONT_FEATURES_LIST& fontFeature);
    const FONT_FEATURES_LIST& GetFontFeatures() const;
    void SetFontSize(double fontSize);
    double GetFontSize() const;
    void SetValueResource(const RefPtr<ResourceObject>&);
    const RefPtr<ResourceObject> GetValueResource() const;
    void SetValueString(const std::string& valueString);
    const std::string GetValueString() const;
    void SetSymbolSpanStyle(const SymbolSpanStyle& symbolSpanStyle);
    const SymbolSpanStyle GetSymbolSpanStyle() const;
    void SetLineHeight(double lineHeight);
    double GetLineHeight() const;
    void SetHalfLeading(bool halfLeading);
    bool GetHalfLeading() const;
    void SetLetterspacing(double letterSpacing);
    double GetLetterspacing() const;
    void SetTextStyle(TextStyleResult textStyle);
    TextStyleResult GetTextStyle() const;
    void SetFontWeight(int32_t fontWeigth);
    int32_t GetFontWeight() const;
    void SetFontFamily(const std::string& fontFamily);
    const std::string& GetFontFamily() const;
    void SetTextDecoration(TextDecoration textDecoration);
    TextDecoration GetTextDecoration() const;
    void SetColor(const std::string& color);
    const std::string& GetColor() const;
    void SetTextDecorationStyle(TextDecorationStyle textDecorationStyle);
    TextDecorationStyle GetTextDecorationStyle() const;
    void SetLineThicknessScale(float thicknessScale);
    float GetLineThicknessScale() const;
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
    void SetUrlAddress(const std::u16string& urlAddress);
    const std::u16string& GetUrlAddress() const;
    void SetBorderRadius(const std::string& borderRadius)
    {
        borderRadius_ = borderRadius;
    }
    const std::string& GetBorderRadius() const
    {
        return borderRadius_;
    }
    void SetMargin(const std::string& margin)
    {
        margin_ = margin;
    }
    const std::string& GetMargin() const
    {
        return margin_;
    }
    void SetFontStyle(OHOS::Ace::FontStyle fontStyle)
    {
        fontStyle_ = fontStyle;
    }

    OHOS::Ace::FontStyle GetFontStyle() const
    {
        return fontStyle_;
    }

private:
    TextStyleResult textStyle_;
    double lineHeight_ = 0.0;
    bool halfLeading_ = false;
    double letterSpacing_ = 0.0;
    int32_t spanIndex_ = 0;
    int32_t spanRangeStart_ = 0;
    int32_t spanRangeEnd_ = 0;
    SpanResultType spanType_;
    int32_t offsetInSpan_ = 0;
    int32_t eraseLength_ = 0;
    std::u16string value_;
    std::u16string previewText_;
    std::u16string urlAddress_;
    std::string fontColor_;
    FONT_FEATURES_LIST fontFeature_;
    double fontSize_ = 0.0;
    OHOS::Ace::FontStyle fontStyle_;
    int32_t fontWeigth_ = 0;
    std::string fontFamily_;
    TextDecoration textDecoration_;
    std::string color_;
    TextDecorationStyle textDecorationStyle_;
    float lineThicknessScale_ = 1.0f;
    RefPtr<PixelMap> valuePixelMap_;
    std::string valueResourceStr_;
    int32_t width_ = 0;
    int32_t height_ = 0;
    VerticalAlign verticalAlign_;
    ImageFit objectFit_;
    std::string borderRadius_;
    std::string margin_;
    std::string valueString_;
    SymbolSpanStyle symbolSpanStyle_;
    RefPtr<ResourceObject> valueResource_;
};

enum class RichEditorDeleteDirection { BACKWARD = 0, FORWARD };

class ACE_FORCE_EXPORT RichEditorDeleteValue : public BaseEventInfo {
    DECLARE_ACE_TYPE(RichEditorDeleteValue, BaseEventInfo);
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
    void ResetRichEditorDeleteSpans();
    const std::list<RichEditorAbstractSpanResult>& GetRichEditorDeleteSpans() const;

private:
    int32_t offset_ = 0;
    RichEditorDeleteDirection direction_ = RichEditorDeleteDirection::BACKWARD;
    int32_t length_ = 0;
    std::list<RichEditorAbstractSpanResult> richEditorDeleteSpans_;
};

class ACE_FORCE_EXPORT RichEditorChangeValue : public BaseEventInfo {
    DECLARE_ACE_TYPE(RichEditorChangeValue, BaseEventInfo);
#ifndef ACE_UNITTEST
private:
#else
public:
#endif
    RichEditorChangeValue() : BaseEventInfo("RichEditorChangeValue") {}
public:
    RichEditorChangeValue(TextChangeReason reason) : RichEditorChangeValue()
    {
        changeReason_ = reason;
    }
    ~RichEditorChangeValue() = default;

    void SetRichEditorOriginalSpans(const RichEditorAbstractSpanResult& span);
    const std::vector<RichEditorAbstractSpanResult>& GetRichEditorOriginalSpans() const;

    void SetRichEditorReplacedSpans(const RichEditorAbstractSpanResult& span);
    const std::vector<RichEditorAbstractSpanResult>& GetRichEditorReplacedSpans() const;

    void SetRichEditorReplacedImageSpans(const RichEditorAbstractSpanResult& span);
    const std::vector<RichEditorAbstractSpanResult>& GetRichEditorReplacedImageSpans() const;

    void SetRichEditorReplacedSymbolSpans(const RichEditorAbstractSpanResult& span);
    const std::vector<RichEditorAbstractSpanResult>& GetRichEditorReplacedSymbolSpans() const;

    void SetRangeBefore(const TextRange& rangeBefore);
    TextRange GetRangeBefore() const;

    void SetRangeAfter(const TextRange& rangeAfter);
    TextRange GetRangeAfter() const;

    TextChangeReason GetChangeReason() const;

    void reset()
    {
        originalSpans_.clear();
        replacedSpans_.clear();
        replacedImageSpans_.clear();
        replacedSymbolSpans_.clear();
        rangeBefore_ = TextRange();
        rangeAfter_ = TextRange();
        changeReason_ = TextChangeReason::UNKNOWN;
    }

private:
    std::vector<RichEditorAbstractSpanResult> originalSpans_;
    std::vector<RichEditorAbstractSpanResult> replacedSpans_;
    std::vector<RichEditorAbstractSpanResult> replacedImageSpans_;
    std::vector<RichEditorAbstractSpanResult> replacedSymbolSpans_;
    TextRange rangeBefore_;
    TextRange rangeAfter_;
    TextChangeReason changeReason_ = TextChangeReason::UNKNOWN;
};

class StyledStringChangeValue : public BaseEventInfo {
    DECLARE_ACE_TYPE(StyledStringChangeValue, BaseEventInfo);
public:
    StyledStringChangeValue() : BaseEventInfo("StyledStringChangeValue") {}
    ~StyledStringChangeValue() = default;

    void SetRangeBefore(const TextRange& range);
    TextRange GetRangeBefore() const;

    void SetRangeAfter(const TextRange& range);
    TextRange GetRangeAfter() const;

    void SetReplacementString(const RefPtr<SpanStringBase>& styledString);
    const RefPtr<SpanStringBase> GetReplacementString() const;

    void SetPreviewText(const RefPtr<SpanStringBase>& previewText);
    const RefPtr<SpanStringBase> GetPreviewText() const;

private:
    TextRange rangeBefore_;
    TextRange rangeAfter_;
    RefPtr<SpanStringBase> replacementString_;
    RefPtr<SpanStringBase> previewText_;
};

class RichEditorEventHub : public EventHub {
    DECLARE_ACE_TYPE(RichEditorEventHub, EventHub);

public:
    RichEditorEventHub() = default;
    ~RichEditorEventHub() override = default;
    void SetOnReady(std::function<void()>&& func);
    void FireOnReady();
    void SetAboutToIMEInput(std::function<bool(const RichEditorInsertValue&)>&& func);
    bool FireAboutToIMEInput(const RichEditorInsertValue& info);
    void SetOnIMEInputComplete(std::function<void(const RichEditorAbstractSpanResult&)>&& func);
    void SetOnDidIMEInput(std::function<void(const TextRange&)>&& func);
    void FireOnIMEInputComplete(const RichEditorAbstractSpanResult& info);
    void FireOnDidIMEInput(const TextRange& info);
    void SetAboutToDelete(std::function<bool(const RichEditorDeleteValue&)>&& func);
    bool FireAboutToDelete(const RichEditorDeleteValue& info);
    void SetOnDeleteComplete(std::function<void()>&& func);
    void FireOnDeleteComplete();
    std::string GetDragExtraParams(const std::string& extraInfo, const Point& point, DragEventType type) override;
    void SetOnEditingChange(std::function<void(const bool&)> && func);
    void FireOnEditingChange(bool isEditing);
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

    void SetOnSelectionChange(std::function<void(const BaseEventInfo*)>&& func)
    {
        OnSelectionChange_ = std::move(func);
    }

    void FireOnSelectionChange(BaseEventInfo* value)
    {
        if (OnSelectionChange_) {
            OnSelectionChange_(value);
        }
    }

    void SetTimestamp(long long timestamp)
    {
        timestamp_ = timestamp;
    }

    void SetOnPaste(std::function<void(NG::TextCommonEvent&)>&& func)
    {
        onPaste_ = std::move(func);
    }

    void FireOnPaste(NG::TextCommonEvent& value)
    {
        if (onPaste_) {
            onPaste_(value);
        }
    }

    void SetOnSubmit(std::function<void(int32_t, NG::TextFieldCommonEvent&)>&& func)
    {
        onSubmit_ = std::move(func);
    }

    void FireOnSubmit(int32_t value, NG::TextFieldCommonEvent& event)
    {
        if (onSubmit_) {
            onSubmit_(value, event);
        }
    }

    void SetOnWillChange(std::function<bool(const RichEditorChangeValue&)> && func);
    bool FireOnWillChange(const RichEditorChangeValue& info);
    bool HasOnWillChange() const;
    void SetOnDidChange(std::function<void(const RichEditorChangeValue&)> && func);
    void FireOnDidChange(const RichEditorChangeValue& range);
    bool HasOnDidChange() const;
    void SetOnCut(std::function<void(NG::TextCommonEvent&)> && func);
    void FireOnCut(NG::TextCommonEvent& value);
    void SetOnCopy(std::function<void(NG::TextCommonEvent&)> && func);
    void FireOnCopy(NG::TextCommonEvent& value);
    void SetOnShare(std::function<void(NG::TextCommonEvent&)>&& func);
    void FireOnShare(NG::TextCommonEvent& value);
    void SetOnStyledStringWillChange(std::function<bool(const StyledStringChangeValue&)> && func);
    bool FireOnStyledStringWillChange(const StyledStringChangeValue& info);
    bool HasOnStyledStringWillChange() const;
    void SetOnStyledStringDidChange(std::function<void(const StyledStringChangeValue&)> && func);
    void FireOnStyledStringDidChange(const StyledStringChangeValue& info);
    bool HasOnStyledStringDidChange() const;

private:
    long long timestamp_ = 0;
    std::function<void(NG::TextCommonEvent&)> onPaste_;
    std::function<void()> onReady_;
    std::function<void(const BaseEventInfo*)> onSelect_;
    std::function<void(const BaseEventInfo*)> OnSelectionChange_;
    std::function<bool(const RichEditorInsertValue&)> aboutToIMEInput_;
    std::function<void(const RichEditorAbstractSpanResult&)> onIMEInputComplete_;
    std::function<void(const TextRange&)> onDidIMEInput_;
    std::function<bool(const RichEditorDeleteValue&)> aboutToDelete_;
    std::function<void()> onDeleteComplete_;
    std::function<void(const bool&)> onEditingChange_;
    std::function<void(int32_t, NG::TextFieldCommonEvent&)> onSubmit_;
    std::function<bool(const RichEditorChangeValue&)> onWillChange_;
    std::function<void(const RichEditorChangeValue&)> onDidChange_;
    std::function<void(NG::TextCommonEvent&)> onCut_;
    std::function<void(NG::TextCommonEvent&)> onCopy_;
    std::function<void(NG::TextCommonEvent&)> onShare_;
    std::function<bool(const StyledStringChangeValue&)> onStyledStringWillChange_;
    std::function<void(const StyledStringChangeValue&)> onStyledStringDidChange_;
    ACE_DISALLOW_COPY_AND_MOVE(RichEditorEventHub);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_EVENT_HUB_H
