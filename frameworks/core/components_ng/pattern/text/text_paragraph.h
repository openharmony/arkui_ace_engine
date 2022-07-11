/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_PARAGRAPH_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_PARAGRAPH_H

#include <memory>
#include <string>
#include <utility>

#include "base/geometry/dimension.h"
#include "core/components_ng/pattern/text/text_styles.h"

#define ACE_DEFINE_PARAGRAPH_PROPERTY(group, name, type) \
public:                                                  \
    bool Update##name(const type& value)                 \
    {                                                    \
        if (!prop##group##_) {                           \
            prop##group##_ = std::make_unique<group>();  \
        }                                                \
        return prop##group##_->Update##name(value);      \
    }                                                    \
    bool Check##name(const type& value) const            \
    {                                                    \
        if (!prop##group##_) {                           \
            return false;                                \
        }                                                \
        return prop##group##_->Get##name() == value;     \
    }

namespace OHOS::Ace::NG {
class TextParagraph {
public:
    TextParagraph() = default;
    TextParagraph(std::string content, const FontStyle& fontStyle, const TextLineStyle& textLineStyle)
        : content_(std::move(content)), propFontStyle_(std::make_unique<FontStyle>(fontStyle)),
          propTextLineStyle_(std::make_unique<TextLineStyle>(textLineStyle))
    {}
    explicit TextParagraph(std::string content) : content_(std::move(content)) {}
    ~TextParagraph() = default;

    TextParagraph(const TextParagraph& value)
    {
        content_ = value.content_;
        if (value.propFontStyle_) {
            propFontStyle_ = std::make_unique<FontStyle>(*value.propFontStyle_);
        }
        if (value.propTextLineStyle_) {
            propTextLineStyle_ = std::make_unique<TextLineStyle>(*value.propTextLineStyle_);
        }
    }

    TextParagraph& operator=(const TextParagraph& value)
    {
        if (this == &value) {
            return *this;
        }
        content_ = value.content_;
        if (value.propFontStyle_) {
            propFontStyle_ = std::make_unique<FontStyle>(*value.propFontStyle_);
        }
        if (value.propTextLineStyle_) {
            propTextLineStyle_ = std::make_unique<TextLineStyle>(*value.propTextLineStyle_);
        }
        return *this;
    }

    void Reset()
    {
        content_.clear();
        propFontStyle_.reset();
        propTextLineStyle_.reset();
    }

    bool UpdateContent(const std::string& value)
    {
        if (content_ == value) {
            return false;
        }
        content_ = value;
        return true;
    }

    bool CheckContent(const std::string& value) const
    {
        return (content_ == value);
    }

    const std::unique_ptr<FontStyle>& GetFontStyle() const
    {
        return propFontStyle_;
    }

    const std::unique_ptr<TextLineStyle>& GetTextLineStyle() const
    {
        return propTextLineStyle_;
    }

    ACE_DEFINE_PARAGRAPH_PROPERTY(FontStyle, FontSize, Dimension);
    ACE_DEFINE_PARAGRAPH_PROPERTY(FontStyle, TextColor, Color);
    ACE_DEFINE_PARAGRAPH_PROPERTY(FontStyle, ItalicFontStyle, ItalicFontStyle);
    ACE_DEFINE_PARAGRAPH_PROPERTY(FontStyle, FontWeight, FontWeight);
    ACE_DEFINE_PARAGRAPH_PROPERTY(FontStyle, FontFamily, std::vector<std::string>);
    ACE_DEFINE_PARAGRAPH_PROPERTY(TextLineStyle, LineHeight, Dimension);
    ACE_DEFINE_PARAGRAPH_PROPERTY(TextLineStyle, TextBaseline, TextBaseline);
    ACE_DEFINE_PARAGRAPH_PROPERTY(TextLineStyle, BaselineOffset, Dimension);
    ACE_DEFINE_PARAGRAPH_PROPERTY(TextLineStyle, TextAlign, TextAlign);
    ACE_DEFINE_PARAGRAPH_PROPERTY(TextLineStyle, MaxLines, uint32_t);

private:
    std::string content_;
    std::unique_ptr<FontStyle> propFontStyle_;
    std::unique_ptr<TextLineStyle> propTextLineStyle_;

    friend class TextLayoutAlgorithm;
    friend class TextPattern;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_TEXT_PARAGRAPH_H