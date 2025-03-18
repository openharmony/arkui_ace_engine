/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SPAN_SPAN_OBJECT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SPAN_SPAN_OBJECT_H

#include <string>
#include <utility>
#include <vector>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/text/span/tlv_util.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text/text_model.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace {

enum class SpanType {
    Font = 0,
    Decoration,
    BaselineOffset,
    LetterSpacing,
    TextShadow = 4,
    LineHeight = 5,
    BackgroundColor = 6,
    Url = 7,
    HalfLeading = 8,
    Gesture = 100,
    ParagraphStyle = 200,
    Image = 300,
    CustomSpan = 400,
    ExtSpan = 500
};

struct SpanParagraphStyle {
    std::optional<TextAlign> align;
    std::optional<int32_t> maxLines;
    std::optional<WordBreak> wordBreak;
    std::optional<TextOverflow> textOverflow;
    std::optional<NG::LeadingMargin> leadingMargin;
    std::optional<Dimension> textIndent;
    std::optional<Dimension> paragraphSpacing;

    bool Equal(const SpanParagraphStyle& other) const
    {
        auto flag = align == other.align && maxLines == other.maxLines && wordBreak == other.wordBreak &&
                    textOverflow == other.textOverflow && textIndent == other.textIndent &&
                    paragraphSpacing == other.paragraphSpacing;
        if (leadingMargin.has_value() && other.leadingMargin.has_value()) {
            flag &= leadingMargin.value().CheckLeadingMargin(other.leadingMargin.value());
        } else if (!leadingMargin.has_value() && !other.textOverflow.has_value()) {
            flag &= true;
        } else {
            flag &= false;
        }
        return flag;
    }
};

enum class SpanOperation {
    ADD = 0,
    REMOVE,
};

class SpanWatcher : public virtual AceType {
    DECLARE_ACE_TYPE(SpanWatcher, AceType);

public:
    virtual void UpdateSpanItems(const std::list<RefPtr<NG::SpanItem>>& spanItems) = 0;
};

struct GestureStyle {
    std::optional<GestureEventFunc> onClick;
    std::optional<GestureEventFunc> onLongPress;

    bool IsEqual(const GestureStyle& other) const
    {
        return false;
    }
};

class SpanBase : public virtual AceType {
    DECLARE_ACE_TYPE(SpanBase, AceType);

public:
    SpanBase() = default;
    SpanBase(int32_t start, int32_t end) : start_(start), end_(end) {}
    virtual bool IsAttributesEqual(const RefPtr<SpanBase>& other) const = 0;
    virtual RefPtr<SpanBase> GetSubSpan(int32_t start, int32_t end) = 0;
    virtual SpanType GetSpanType() const = 0;
    virtual void ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem, SpanOperation operation) const = 0;
    virtual std::string ToString() const = 0;

    int32_t GetStartIndex() const;
    int32_t GetEndIndex() const;
    void UpdateStartIndex(int32_t startIndex);
    void UpdateEndIndex(int32_t endIndex);
    int32_t GetLength() const;
    std::optional<std::pair<int32_t, int32_t>> GetIntersectionInterval(std::pair<int32_t, int32_t> interval) const;

private:
    int32_t start_ = 0;
    int32_t end_ = 0; // The interval rules are closed on the left and open on the right
};

class FontSpan : public SpanBase {
    DECLARE_ACE_TYPE(FontSpan, SpanBase);

public:
    FontSpan() = default;
    explicit FontSpan(Font font);
    FontSpan(Font font, int32_t start, int32_t end);
    Font GetFont() const;
    RefPtr<SpanBase> GetSubSpan(int32_t start, int32_t end) override;
    bool IsAttributesEqual(const RefPtr<SpanBase>& other) const override;
    SpanType GetSpanType() const override;
    std::string ToString() const override;
    void ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem, SpanOperation operation) const override;
    static RefPtr<SpanBase> CreateDefaultSpan();

private:
    void AddSpanStyle(const RefPtr<NG::SpanItem>& spanItem) const;
    static void RemoveSpanStyle(const RefPtr<NG::SpanItem>& spanItem);

    Font font_;
};

class DecorationSpan : public SpanBase {
    DECLARE_ACE_TYPE(DecorationSpan, SpanBase);

public:
    DecorationSpan() = default;
    explicit DecorationSpan(TextDecoration type, std::optional<Color> color, std::optional<TextDecorationStyle> style);
    DecorationSpan(TextDecoration type, std::optional<Color> color, std::optional<TextDecorationStyle> style,
        int32_t start, int32_t end);
    TextDecoration GetTextDecorationType() const;
    std::optional<Color> GetColor() const;
    std::optional<TextDecorationStyle> GetTextDecorationStyle() const;
    RefPtr<SpanBase> GetSubSpan(int32_t start, int32_t end) override;
    bool IsAttributesEqual(const RefPtr<SpanBase>& other) const override;
    SpanType GetSpanType() const override;
    std::string ToString() const override;
    void ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem, SpanOperation operation) const override;

private:
    void AddDecorationStyle(const RefPtr<NG::SpanItem>& spanItem) const;
    static void RemoveDecorationStyle(const RefPtr<NG::SpanItem>& spanItem);

    TextDecoration type_;
    std::optional<Color> color_;
    std::optional<TextDecorationStyle> style_;
};

class BaselineOffsetSpan : public SpanBase {
    DECLARE_ACE_TYPE(BaselineOffsetSpan, SpanBase);

public:
    BaselineOffsetSpan() = default;
    explicit BaselineOffsetSpan(Dimension baselineOffset);
    BaselineOffsetSpan(Dimension baselineOffset, int32_t start, int32_t end);
    Dimension GetBaselineOffset() const;
    RefPtr<SpanBase> GetSubSpan(int32_t start, int32_t end) override;
    bool IsAttributesEqual(const RefPtr<SpanBase>& other) const override;
    SpanType GetSpanType() const override;
    std::string ToString() const override;
    void ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem, SpanOperation operation) const override;

private:
    void AddBaselineOffsetStyle(const RefPtr<NG::SpanItem>& spanItem) const;
    static void RemoveBaselineOffsetStyle(const RefPtr<NG::SpanItem>& spanItem);
    Dimension baselineOffset_;
};

class LetterSpacingSpan : public SpanBase {
    DECLARE_ACE_TYPE(LetterSpacingSpan, SpanBase);

public:
    LetterSpacingSpan() = default;
    explicit LetterSpacingSpan(Dimension letterSpacing);
    LetterSpacingSpan(Dimension letterSpacing, int32_t start, int32_t end);
    Dimension GetLetterSpacing() const;
    RefPtr<SpanBase> GetSubSpan(int32_t start, int32_t end) override;
    bool IsAttributesEqual(const RefPtr<SpanBase>& other) const override;
    SpanType GetSpanType() const override;
    std::string ToString() const override;
    void ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem, SpanOperation operation) const override;

private:
    void AddLetterSpacingStyle(const RefPtr<NG::SpanItem>& spanItem) const;
    static void RemoveLetterSpacingStyle(const RefPtr<NG::SpanItem>& spanItem);

    Dimension letterSpacing_;
};

class GestureSpan : public SpanBase {
    DECLARE_ACE_TYPE(GestureSpan, SpanBase);

public:
    GestureSpan() = default;
    explicit GestureSpan(GestureStyle gestureInfo);
    ~GestureSpan() override = default;
    GestureSpan(GestureStyle gestureInfo, int32_t start, int32_t end);
    GestureStyle GetGestureStyle() const;
    RefPtr<SpanBase> GetSubSpan(int32_t start, int32_t end) override;
    bool IsAttributesEqual(const RefPtr<SpanBase>& other) const override;
    SpanType GetSpanType() const override;
    std::string ToString() const override;
    void ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem, SpanOperation operation) const override;

    int32_t GetGestureSpanId()
    {
        return gestureSpanId_;
    }

    void SetGestureSpanId(int32_t gestureSpanId)
    {
        gestureSpanId_ = gestureSpanId;
    }

private:
    void AddSpanStyle(const RefPtr<NG::SpanItem>& spanItem) const;
    static void RemoveSpanStyle(const RefPtr<NG::SpanItem>& spanItem);

    GestureStyle gestureInfo_;
    int32_t gestureSpanId_ = -1;
};

class TextShadowSpan : public SpanBase {
    DECLARE_ACE_TYPE(TextShadowSpan, SpanBase);

public:
    TextShadowSpan() = default;
    explicit TextShadowSpan(std::vector<Shadow> font);
    TextShadowSpan(std::vector<Shadow> font, int32_t start, int32_t end);
    std::vector<Shadow> GetTextShadow() const;
    RefPtr<SpanBase> GetSubSpan(int32_t start, int32_t end) override;
    bool IsAttributesEqual(const RefPtr<SpanBase>& other) const override;
    SpanType GetSpanType() const override;
    std::string ToString() const override;
    void ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem, SpanOperation operation) const override;

private:
    void AddSpanStyle(const RefPtr<NG::SpanItem>& spanItem) const;
    static void RemoveSpanStyle(const RefPtr<NG::SpanItem>& spanItem);

    std::optional<std::vector<Shadow>> textShadow_ = std::nullopt;
};
class BackgroundColorSpan : public SpanBase {
    DECLARE_ACE_TYPE(BackgroundColorSpan, SpanBase);

public:
    BackgroundColorSpan() = default;
    explicit BackgroundColorSpan(std::optional<TextBackgroundStyle> textBackgroundStyle_);
    BackgroundColorSpan(std::optional<TextBackgroundStyle> textBackgroundStyle_, int32_t start, int32_t end);
    TextBackgroundStyle GetBackgroundColor() const;
    void SetBackgroundColorGroupId(int32_t groupId);
    RefPtr<SpanBase> GetSubSpan(int32_t start, int32_t end) override;
    bool IsAttributesEqual(const RefPtr<SpanBase>& other) const override;
    SpanType GetSpanType() const override;
    std::string ToString() const override;
    void ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem, SpanOperation operation) const override;

private:
    std::optional<TextBackgroundStyle> textBackgroundStyle_;
    void AddSpanStyle(const RefPtr<NG::SpanItem>& spanItem) const;
    static void RemoveSpanStyle(const RefPtr<NG::SpanItem>& spanItem);
};

class ImageSpan : public SpanBase {
    DECLARE_ACE_TYPE(ImageSpan, SpanBase);

public:
    explicit ImageSpan(const ImageSpanOptions& options);
    ImageSpan(const ImageSpanOptions& options, int32_t position);
    bool IsAttributesEqual(const RefPtr<SpanBase>& other) const override;
    RefPtr<SpanBase> GetSubSpan(int32_t start, int32_t end) override;
    SpanType GetSpanType() const override;
    void ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem, SpanOperation operation) const override;
    std::string ToString() const override;

    const ImageSpanOptions& GetImageSpanOptions();
    const std::optional<ImageSpanAttribute>& GetImageAttribute() const;

private:
    ImageSpanOptions imageOptions_;
};

class CustomSpan : public SpanBase {
    DECLARE_ACE_TYPE(CustomSpan, SpanBase);

public:
    CustomSpan();
    explicit CustomSpan(std::optional<std::function<CustomSpanMetrics(CustomSpanMeasureInfo)>> onMeasure,
        std::optional<std::function<void(NG::DrawingContext&, CustomSpanOptions)>> onDraw);

    explicit CustomSpan(std::optional<std::function<CustomSpanMetrics(CustomSpanMeasureInfo)>> onMeasure,
        std::optional<std::function<void(NG::DrawingContext&, CustomSpanOptions)>> onDraw, int32_t start, int32_t end);
    virtual ~CustomSpan() override = default;
    RefPtr<SpanBase> GetSubSpan(int32_t start, int32_t end) override;
    bool IsAttributesEqual(const RefPtr<SpanBase>& other) const override;
    SpanType GetSpanType() const override;
    void SetOnMeasure(std::function<CustomSpanMetrics(CustomSpanMeasureInfo)> onMeasure);
    void SetOnDraw(std::function<void(NG::DrawingContext&, CustomSpanOptions)> onDraw);
    std::optional<std::function<CustomSpanMetrics(CustomSpanMeasureInfo)>> GetOnMeasure();
    std::optional<std::function<void(NG::DrawingContext&, CustomSpanOptions)>> GetOnDraw();
    std::string ToString() const override;
    void ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem, SpanOperation operation) const override;
    virtual void AddStyledString(const WeakPtr<SpanStringBase>& spanString) {}
    virtual void RemoveStyledString(const WeakPtr<SpanStringBase>& spanString) {}

private:
    std::optional<std::function<CustomSpanMetrics(CustomSpanMeasureInfo)>> onMeasure_;
    std::optional<std::function<void(NG::DrawingContext&, CustomSpanOptions)>> onDraw_;
};

class ParagraphStyleSpan : public SpanBase {
    DECLARE_ACE_TYPE(ParagraphStyleSpan, SpanBase);

public:
    ParagraphStyleSpan() = default;
    explicit ParagraphStyleSpan(SpanParagraphStyle paragraphStyle);
    ParagraphStyleSpan(SpanParagraphStyle paragraphStyle, int32_t start, int32_t end);
    SpanParagraphStyle GetParagraphStyle() const;
    RefPtr<SpanBase> GetSubSpan(int32_t start, int32_t end) override;
    bool IsAttributesEqual(const RefPtr<SpanBase>& other) const override;
    SpanType GetSpanType() const override;
    std::string ToString() const override;
    void ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem, SpanOperation operation) const override;

private:
    void AddParagraphStyle(const RefPtr<NG::SpanItem>& spanItem) const;
    void RemoveParagraphStyle(const RefPtr<NG::SpanItem>& spanItem) const;

    SpanParagraphStyle paragraphStyle_;
};

class LineHeightSpan : public SpanBase {
    DECLARE_ACE_TYPE(LineHeightSpan, SpanBase);

public:
    LineHeightSpan() = default;
    explicit LineHeightSpan(Dimension lineHeight);
    LineHeightSpan(Dimension lineHeight, int32_t start, int32_t end);
    Dimension GetLineHeight() const;
    RefPtr<SpanBase> GetSubSpan(int32_t start, int32_t end) override;
    bool IsAttributesEqual(const RefPtr<SpanBase>& other) const override;
    SpanType GetSpanType() const override;
    std::string ToString() const override;
    void ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem, SpanOperation operation) const override;

private:
    void AddLineHeightStyle(const RefPtr<NG::SpanItem>& spanItem) const;
    void RemoveLineHeightStyle(const RefPtr<NG::SpanItem>& spanItem) const;

    Dimension lineHeight_;
};

class HalfLeadingSpan : public SpanBase {
    DECLARE_ACE_TYPE(HalfLeadingSpan, SpanBase);

public:
    HalfLeadingSpan() = default;
    explicit HalfLeadingSpan(bool halfLeading);
    HalfLeadingSpan(bool halfLeading, int32_t start, int32_t end);
    bool GetHalfLeading() const;
    RefPtr<SpanBase> GetSubSpan(int32_t start, int32_t end) override;
    bool IsAttributesEqual(const RefPtr<SpanBase>& other) const override;
    SpanType GetSpanType() const override;
    std::string ToString() const override;
    void ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem, SpanOperation operation) const override;

private:
    void AddHalfLeadingStyle(const RefPtr<NG::SpanItem>& spanItem) const;
    void RemoveHalfLeadingStyle(const RefPtr<NG::SpanItem>& spanItem) const;

    bool halfLeading_;
};

class ExtSpan : public SpanBase {
    DECLARE_ACE_TYPE(ExtSpan, SpanBase);

public:
    ExtSpan() = default;
    ExtSpan(int32_t start, int32_t end);
    RefPtr<SpanBase> GetSubSpan(int32_t start, int32_t end) override;
    bool IsAttributesEqual(const RefPtr<SpanBase>& other) const override;
    SpanType GetSpanType() const override;
    std::string ToString() const override;
    void ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem, SpanOperation operation) const override {}
};

class UrlSpan : public SpanBase {
    DECLARE_ACE_TYPE(UrlSpan, SpanBase);

public:
    UrlSpan() = default;
    explicit UrlSpan(const std::string& urlAddress);
    UrlSpan(const std::string& urlAddress, int32_t start, int32_t end);
    std::string GetUrlSpanAddress() const;
    RefPtr<SpanBase> GetSubSpan(int32_t start, int32_t end) override;
    bool IsAttributesEqual(const RefPtr<SpanBase>& other) const override;
    SpanType GetSpanType() const override;
    std::string ToString() const override;
    void ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem,
        SpanOperation operation) const override;
private:
    void AddUrlStyle(const RefPtr<NG::SpanItem>& spanItem) const;
    static void RemoveUrlStyle(const RefPtr<NG::SpanItem>& spanItem);
    std::string urlAddress_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SPAN_SPAN_OBJECT_H