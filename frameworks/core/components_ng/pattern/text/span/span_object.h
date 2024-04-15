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
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"

namespace OHOS::Ace {

class AttachmentImage {};

enum class SpanType { Font = 0, Decoration, BaselineOffset, LetterSpacing, TextShadow = 4, Gesture = 100 };

enum class SpanOperation {
    ADD = 0,
    REMOVE,
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
    int32_t GetStartIndex() const;
    int32_t GetEndIndex() const;
    void UpdateStartIndex(int32_t startIndex);
    void UpdateEndIndex(int32_t endIndex);
    int32_t GetLength() const;
    std::optional<std::pair<int32_t, int32_t>> GetIntersectionInterval(std::pair<int32_t, int32_t> interval) const;
    virtual std::string ToString() const = 0;

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
    explicit DecorationSpan(TextDecoration type, std::optional<Color> color);
    DecorationSpan(TextDecoration type, std::optional<Color> color, int32_t start, int32_t end);
    TextDecoration GetTextDecorationType() const;
    std::optional<Color> GetColor() const;
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

private:
    void AddSpanStyle(const RefPtr<NG::SpanItem>& spanItem) const;
    static void RemoveSpanStyle(const RefPtr<NG::SpanItem>& spanItem);

    GestureStyle gestureInfo_;
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
    static RefPtr<SpanBase> CreateDefaultSpan();

private:
    void AddSpanStyle(const RefPtr<NG::SpanItem>& spanItem) const;
    static void RemoveSpanStyle(const RefPtr<NG::SpanItem>& spanItem);

    std::optional<std::vector<Shadow>> textShadow_ = std::nullopt;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SPAN_SPAN_OBJECT_H