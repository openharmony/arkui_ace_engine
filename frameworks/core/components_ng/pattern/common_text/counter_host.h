/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not this file except in compliance with the License.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COMMON_TEXT_COUNTER_HOST_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COMMON_TEXT_COUNTER_HOST_H

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/radius.h"
#include "core/components/common/properties/text_enums.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace::NG {

// Forward declarations to minimize include dependencies in this interface header.
class FrameNode;
class RenderContext;
class TextInputResponseArea;

class ICounterHost : public virtual AceType {
public:
    ~ICounterHost() override = default;

    virtual bool GetShowCounterStyleValue() const = 0;
    virtual void SetShowCounterStyleValue(bool value) = 0;

    virtual bool IsShowCounterEnabled() const = 0;
    virtual uint32_t GetRealMaxLength() const = 0;
    virtual bool HasMaxLength() const = 0;
    virtual uint32_t GetTextLength() const = 0;
    virtual std::string GetTextValue() const = 0;
    virtual bool HasFocus() const = 0;

    virtual bool GetShowCounterValue() const = 0;
    virtual int32_t GetCounterType() const { return -1; }
    virtual bool GetShowHighlightBorder() const { return true; }
    virtual bool HasCounterTextColor() const { return false; }
    virtual Color GetCounterTextColor() const { return Color::BLACK; }
    virtual bool HasCounterTextOverflowColor() const { return false; }
    virtual Color GetCounterTextOverflowColor() const { return Color::RED; }

    virtual bool HasMaxFontScale() const { return false; }
    virtual float GetMaxFontScale() const { return 1.0f; }
    virtual bool HasMinFontScale() const { return false; }
    virtual float GetMinFontScale() const { return 1.0f; }
    virtual float GetFontScaleFromEnv(const RefPtr<FrameNode>& host) const { return 1.0f; }

    virtual bool IsUnderlineMode() const { return false; }
    virtual bool IsShowError() const { return false; }
    virtual bool IsUnderlineAndButtonMode() const { return false; }
    virtual bool IsTextAreaOnCounter() const { return false; }
    virtual bool IsNormalInlineState() const { return false; }
    virtual bool IsShowPasswordIcon() const { return false; }
    virtual TextDirection GetLayoutDirection() const { return TextDirection::LTR; }
    virtual TextDirection GetNonAutoLayoutDirection() const { return TextDirection::LTR; }

    virtual float GetPaddingLeft() const { return 0.0f; }
    virtual float GetPaddingRight() const { return 0.0f; }
    virtual float GetPaddingBottom() const { return 0.0f; }

    virtual std::vector<RefPtr<TextInputResponseArea>> GetAllResponseArea() const { return {}; }

    virtual std::optional<MarginProperty> GetMarginProperty() const { return std::nullopt; }
    virtual void UpdateMargin(const MarginProperty& margin) = 0;

    virtual bool HasMarginByUser() const { return false; }
    virtual MarginProperty GetMarginByUserValue() const { return MarginProperty(); }

    virtual void UpdateInnerBorderWidth(float width) = 0;
    virtual void UpdateInnerBorderColor(const Color& color) = 0;
    virtual bool HasBorderWidthFlagByUser() const = 0;
    virtual BorderWidthProperty GetBorderWidthFlagByUserValue() const = 0;
    virtual bool HasBorderColorFlagByUser() const = 0;
    virtual BorderColorProperty GetBorderColorFlagByUserValue() const = 0;
    virtual bool HasBorderRadiusFlagByUser() const = 0;
    virtual BorderRadiusProperty GetBorderRadiusFlagByUserValue() const = 0;
    virtual void UpdateBorderColor(const BorderColorProperty& color) = 0;
    virtual void SetThemeBorderAttr() = 0;

    virtual void SetUnderlineColor(const Color& color) {}
    virtual void SetUnderlineWidth(float width) {}
    virtual void ApplyUnderlineTheme() {}
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COMMON_TEXT_COUNTER_HOST_H
