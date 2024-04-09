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
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"

namespace OHOS::Ace {

enum class SpanType { Font = 0, Decoration, Background, Gesture, Image, None };

enum class SpanOperation {
    ADD = 0,
    REMOVE,
};

class SpanWatcher : public virtual AceType {
    DECLARE_ACE_TYPE(SpanWatcher, AceType);

public:
    virtual void UpdateSpanItems(std::list<RefPtr<NG::SpanItem>>&& spanItems) = 0;
    virtual void DeleteImageSpans(const std::vector<int32_t>& deleteImageId) = 0;
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

class ImageSpan : public SpanBase {
    DECLARE_ACE_TYPE(ImageSpan, SpanBase);
public:
    explicit ImageSpan(const NG::ImageSpanOptions& options);
    bool IsAttributesEqual(const RefPtr<SpanBase>& other) const override;
    RefPtr<SpanBase> GetSubSpan(int32_t start, int32_t end) override;
    SpanType GetSpanType() const override;
    void ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem, SpanOperation operation) const override;
    std::string ToString() const override;

    const NG::ImageSpanOptions& GetImageSpanOptions();
    const std::optional<NG::ImageSpanAttribute>& GetImageAttribute() const;

private:
    NG::ImageSpanOptions imageOptions_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SPAN_SPAN_OBJECT_H