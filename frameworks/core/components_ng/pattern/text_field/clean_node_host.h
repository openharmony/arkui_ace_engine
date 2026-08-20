/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_CLEAN_NODE_HOST_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_CLEAN_NODE_HOST_H

#include <functional>
#include <optional>
#include <string>

#include "base/geometry/calc_dimension.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"

namespace OHOS::Ace::NG {
class FrameNode;

// Abstract host interface for CleanNodeResponseArea to decouple from concrete pattern types.
// Enables both TextFieldPattern and RichEditorPattern to reuse CleanNodeResponseArea.
class ICleanNodeHost : public virtual AceType {
    DECLARE_ACE_TYPE(ICleanNodeHost, AceType);

public:
    ~ICleanNodeHost() override = default;

    // Returns true when the cancel button should be considered.
    virtual bool IsShowCancelButtonMode() const = 0;

    // Full clear chain triggered by clicking the cancel node (clear + close select + caret + focus).
    virtual void HandleCleanNodeClicked() = 0;

    // Content state used by the three-state display logic (CONSTANT/INVISIBLE/INPUT).
    virtual bool IsContentEmpty() const = 0;

    // Dragging state used as a guard in OnCleanNodeClicked.
    virtual bool IsDragging() const = 0;

    // Guards focus request in OnCleanNodeClicked when user-set text is present.
    virtual bool HasUserAccessibilityText() const = 0;

    // Returns the host FrameNode for theme/context access (TextFieldTheme is shared).
    virtual RefPtr<FrameNode> GetHost() const = 0;

    // Property getters for the cancel button.
    virtual CalcDimension GetCancelIconSize() const = 0;
    virtual Color GetCancelIconColor() const = 0;
    virtual std::string GetCancelIconSrc() const = 0;
    virtual std::string GetBundleName() const = 0;
    virtual std::string GetModuleName() const = 0;
    virtual bool GetIsShowSymbol() const = 0;
    virtual std::optional<CleanNodeStyle> GetCleanNodeStyle() const = 0;
    virtual std::function<void(WeakPtr<FrameNode>)> GetCancelIconSymbol() const = 0;

    // Has*() semantics for conditional property updates (checks if explicitly set).
    virtual bool HasCancelIconSize() const = 0;
    virtual bool HasCancelIconColor() const = 0;
    virtual bool HasCancelIconSrc() const = 0;
    virtual bool HasBundleName() const = 0;
    virtual bool HasModuleName() const = 0;

    // Disabled state for cancel button color theming.
    virtual bool GetIsDisabled() const = 0;

    // Font scale getters for icon size calculation (defined separately in TextFieldLayoutProperty
    // and TextLayoutProperty, so must be interface-ized for cross-pattern reuse).
    virtual std::optional<float> GetCancelMaxFontScale() const = 0;
    virtual std::optional<float> GetCancelMinFontScale() const = 0;
    virtual bool HasCancelMaxFontScale() const = 0;
    virtual bool HasCancelMinFontScale() const = 0;
};

// CRTP base providing default implementations of the layout-property bridge methods.
// Derived must support GetLayoutProperty<LayoutPropertyT>() (e.g., inherit from Pattern).
// LayoutPropertyT must provide the cancel-button property accessors
// (e.g., GetIconSizeValue, HasIconSize, GetMaxFontScale, etc.).
//
// Usage:
//   class TextFieldPattern : public CleanNodeHostBase<TextFieldPattern, TextFieldLayoutProperty> {};
//   class RichEditorPattern : public CleanNodeHostBase<RichEditorPattern, RichEditorLayoutProperty> {};
template<typename Derived, typename LayoutPropertyT>
class CleanNodeHostBase : public ICleanNodeHost {
public:
    CalcDimension GetCancelIconSize() const override
    {
        auto layoutProperty = static_cast<const Derived*>(this)->template GetLayoutProperty<LayoutPropertyT>();
        CHECK_NULL_RETURN(layoutProperty, CalcDimension());
        return layoutProperty->GetIconSizeValue(CalcDimension());
    }

    Color GetCancelIconColor() const override
    {
        auto layoutProperty = static_cast<const Derived*>(this)->template GetLayoutProperty<LayoutPropertyT>();
        CHECK_NULL_RETURN(layoutProperty, Color());
        return layoutProperty->GetIconColorValue(Color());
    }

    std::string GetCancelIconSrc() const override
    {
        auto layoutProperty = static_cast<const Derived*>(this)->template GetLayoutProperty<LayoutPropertyT>();
        CHECK_NULL_RETURN(layoutProperty, std::string());
        return layoutProperty->GetIconSrcValue(std::string());
    }

    std::string GetBundleName() const override
    {
        auto layoutProperty = static_cast<const Derived*>(this)->template GetLayoutProperty<LayoutPropertyT>();
        CHECK_NULL_RETURN(layoutProperty, std::string());
        return layoutProperty->GetBundleNameValue(std::string());
    }

    std::string GetModuleName() const override
    {
        auto layoutProperty = static_cast<const Derived*>(this)->template GetLayoutProperty<LayoutPropertyT>();
        CHECK_NULL_RETURN(layoutProperty, std::string());
        return layoutProperty->GetModuleNameValue(std::string());
    }

    bool GetIsShowSymbol() const override
    {
        auto layoutProperty = static_cast<const Derived*>(this)->template GetLayoutProperty<LayoutPropertyT>();
        CHECK_NULL_RETURN(layoutProperty, false);
        return layoutProperty->GetIsShowSymbolValue(true);
    }

    std::optional<CleanNodeStyle> GetCleanNodeStyle() const override
    {
        auto layoutProperty = static_cast<const Derived*>(this)->template GetLayoutProperty<LayoutPropertyT>();
        CHECK_NULL_RETURN(layoutProperty, std::nullopt);
        return layoutProperty->GetCleanNodeStyleValue(CleanNodeStyle::INPUT);
    }

    std::function<void(WeakPtr<FrameNode>)> GetCancelIconSymbol() const override
    {
        auto layoutProperty = static_cast<const Derived*>(this)->template GetLayoutProperty<LayoutPropertyT>();
        CHECK_NULL_RETURN(layoutProperty, std::function<void(WeakPtr<FrameNode>)>());
        return layoutProperty->GetCancelIconSymbol();
    }

    bool HasCancelIconSize() const override
    {
        auto layoutProperty = static_cast<const Derived*>(this)->template GetLayoutProperty<LayoutPropertyT>();
        CHECK_NULL_RETURN(layoutProperty, false);
        return layoutProperty->HasIconSize();
    }

    bool HasCancelIconColor() const override
    {
        auto layoutProperty = static_cast<const Derived*>(this)->template GetLayoutProperty<LayoutPropertyT>();
        CHECK_NULL_RETURN(layoutProperty, false);
        return layoutProperty->HasIconColor();
    }

    bool HasCancelIconSrc() const override
    {
        auto layoutProperty = static_cast<const Derived*>(this)->template GetLayoutProperty<LayoutPropertyT>();
        CHECK_NULL_RETURN(layoutProperty, false);
        return layoutProperty->HasIconSrc();
    }

    bool HasBundleName() const override
    {
        auto layoutProperty = static_cast<const Derived*>(this)->template GetLayoutProperty<LayoutPropertyT>();
        CHECK_NULL_RETURN(layoutProperty, false);
        return layoutProperty->HasBundleName();
    }

    bool HasModuleName() const override
    {
        auto layoutProperty = static_cast<const Derived*>(this)->template GetLayoutProperty<LayoutPropertyT>();
        CHECK_NULL_RETURN(layoutProperty, false);
        return layoutProperty->HasModuleName();
    }

    bool GetIsDisabled() const override
    {
        auto layoutProperty = static_cast<const Derived*>(this)->template GetLayoutProperty<LayoutPropertyT>();
        CHECK_NULL_RETURN(layoutProperty, false);
        return layoutProperty->GetIsDisabledValue(false);
    }

    std::optional<float> GetCancelMaxFontScale() const override
    {
        auto layoutProperty = static_cast<const Derived*>(this)->template GetLayoutProperty<LayoutPropertyT>();
        CHECK_NULL_RETURN(layoutProperty, std::nullopt);
        return layoutProperty->GetMaxFontScale();
    }

    std::optional<float> GetCancelMinFontScale() const override
    {
        auto layoutProperty = static_cast<const Derived*>(this)->template GetLayoutProperty<LayoutPropertyT>();
        CHECK_NULL_RETURN(layoutProperty, std::nullopt);
        return layoutProperty->GetMinFontScale();
    }

    bool HasCancelMaxFontScale() const override
    {
        auto layoutProperty = static_cast<const Derived*>(this)->template GetLayoutProperty<LayoutPropertyT>();
        CHECK_NULL_RETURN(layoutProperty, false);
        return layoutProperty->HasMaxFontScale();
    }

    bool HasCancelMinFontScale() const override
    {
        auto layoutProperty = static_cast<const Derived*>(this)->template GetLayoutProperty<LayoutPropertyT>();
        CHECK_NULL_RETURN(layoutProperty, false);
        return layoutProperty->HasMinFontScale();
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_CLEAN_NODE_HOST_H
