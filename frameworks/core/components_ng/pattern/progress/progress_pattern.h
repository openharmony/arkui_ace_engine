/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_PATTERN_H

#include <optional>
#include <string>

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/shadow.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/progress/progress_accessibility_property.h"
#include "core/components_ng/pattern/progress/progress_layout_algorithm.h"
#include "core/components_ng/pattern/progress/progress_layout_property.h"
#include "core/components_ng/pattern/progress/progress_modifier.h"
#include "core/components_ng/pattern/progress/progress_paint_method.h"
#include "core/components_ng/pattern/progress/progress_paint_property.h"

namespace OHOS::Ace::NG {
class InspectorFilter;
using ProgressMakeCallback = std::function<RefPtr<FrameNode>(const ProgressConfiguration& config)>;
// ProgressPattern is the base class for progress render node to perform paint progress.
class ProgressPattern : public Pattern {
    DECLARE_ACE_TYPE(ProgressPattern, Pattern);

public:
    ProgressPattern() = default;
    ~ProgressPattern() override = default;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        auto progressLayoutProperty = GetLayoutProperty<ProgressLayoutProperty>();
        CHECK_NULL_RETURN(progressLayoutProperty, nullptr);
        progressType_ = progressLayoutProperty->GetType().value_or(ProgressType::LINEAR);
        if (!progressModifier_) {
            ProgressAnimatableProperty progressAnimatableProperty {};
            InitAnimatableProperty(progressAnimatableProperty);
            progressModifier_ = AceType::MakeRefPtr<ProgressModifier>(GetHost(), progressAnimatableProperty);
        }
        bool isRtl = progressLayoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
        if (isRightToLeft_ != isRtl) {
            isRightToLeft_ = isRtl;
        }
        progressModifier_->SetIsRightToLeft(isRightToLeft_);
        progressModifier_->SetVisible(visibilityProp_);
        progressModifier_->SetUseContentModifier(UseContentModifier());
        if ((progressLayoutProperty->GetType() == ProgressType::RING ||
                progressLayoutProperty->GetType() == ProgressType::SCALE) &&
            progressLayoutProperty->GetPaddingProperty()) {
            const auto& padding = progressLayoutProperty->GetPaddingProperty();
            auto leftPadding = padding->left.value_or(CalcLength(0.0_vp)).GetDimension();
            progressModifier_->SetRingProgressLeftPadding(leftPadding);
        }
        return MakeRefPtr<ProgressPaintMethod>(progressType_, strokeWidth_, progressModifier_, isUserInitiatedColor_);
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<ProgressLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<ProgressLayoutAlgorithm>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<ProgressPaintProperty>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<ProgressAccessibilityProperty>();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, true, FocusStyleType::CUSTOM_REGION };
    }

    void SetTextFromUser(bool value)
    {
        isTextFromUser_ = value;
    }

    bool IsTextFromUser()
    {
        return isTextFromUser_;
    }

    void OnVisibleChange(bool isVisible) override;

    void SetBuilderFunc(ProgressMakeCallback&& makeFunc)
    {
        if (!makeFunc) {
            makeFunc_ = std::nullopt;
            OnModifyDone();
            return;
        }
        makeFunc_ = std::move(makeFunc);
    }

    bool UseContentModifier() const
    {
        return contentModifierNode_ != nullptr;
    }

    RefPtr<FrameNode> GetContentModifierNode()
    {
        return contentModifierNode_;
    }

    Gradient convertGradient(Color color)
    {
        Gradient gradient;
        GradientColor gradientColorEnd;
        GradientColor gradientColorStart;
        gradientColorEnd.SetLinearColor(LinearColor(color));
        gradientColorStart.SetLinearColor(LinearColor(color));
        gradientColorEnd.SetDimension(Dimension(0.0));
        gradient.AddColor(gradientColorEnd);
        gradientColorStart.SetDimension(Dimension(1.0));
        gradient.AddColor(gradientColorStart);
        return gradient;
    }

    void OnAccessibilityEvent();

    void SetUserInitiatedColor(bool value)
    {
        isUserInitiatedColor_ = value;
    }

    void SetUserInitiatedBgColor(bool value)
    {
        isUserInitiatedBgColor_ = value;
    }

    void IsModifierInitiatedColor(bool value)
    {
        isModifierInitiatedColor_ = value;
    }

    void IsModifierInitiatedBgColor(bool value)
    {
        isModifierInitiatedBgColor_ = value;
    }

    bool IsEnableMatchParent() override
    {
        return true;
    }

    bool IsEnableFix() override
    {
        return true;
    }

    bool OnThemeScopeUpdate(int32_t themeScopeId) override;
    void UpdateGradientColor(const NG::Gradient& gradient, bool isFirstLoad);
    void UpdateColor(const Color& color, bool isFirstLoad);
    void OnColorModeChange(uint32_t colorMode) override;

private:
    void InitAnimatableProperty(ProgressAnimatableProperty& progressAnimatableProperty);
    void InitColorProperty(ProgressAnimatableProperty& progressAnimatableProperty,
        const RefPtr<ProgressTheme>& progressTheme, const RefPtr<ProgressPaintProperty>& paintProperty);
    void CalculateStrokeWidth(const SizeF& contentSize);
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnAttachToFrameNode() override;
    void OnModifyDone() override;
    void DumpInfo() override;
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;
    void DumpSimplifyInfo(std::shared_ptr<JsonValue>& json) override {}
    void OnLanguageConfigurationUpdate() override;
    void InitTouchEvent();
    void RemoveTouchEvent();
    void OnPress(const TouchEventInfo& info);
    void InitFocusEvent();
    void HandleFocusEvent();
    void HandleBlurEvent();
    void SetFocusStyle();
    void ClearFocusStyle();
    void AddIsFocusActiveUpdateEvent();
    void RemoveIsFocusActiveUpdateEvent();
    void InitHoverEvent();
    void RemoveHoverEvent();
    void OnHover(bool isHover);
    void SetTextColor(const Color& color);
    void HandleEnabled();
    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    void GetInnerFocusPaintRect(RoundRect& paintRect);
    void ToJsonValueForRingStyleOptions(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void ToJsonValueForLinearStyleOptions(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void ToJsonValueForCapsuleStyleOptions(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    float GetBorderRadiusValues() const;
    static std::string ConvertProgressStatusToString(const ProgressStatus status);
    void OnSensitiveStyleChange(bool isSensitive) override;
    void ObscureText(bool isSensitive);
    void FireBuilder();
    void ReportProgressEvent();
    void OnColorConfigurationUpdate() override;
    RefPtr<FrameNode> BuildContentModifierNode();
    std::optional<ProgressMakeCallback> makeFunc_;
    RefPtr<FrameNode> contentModifierNode_;

    float strokeWidth_ = Dimension(4.0_vp).ConvertToPx();
    RefPtr<ProgressModifier> progressModifier_;
    RefPtr<TouchEventImpl> touchListener_;
    RefPtr<InputEvent> hoverEvent_;
    std::function<void(bool)> isFocusActiveUpdateEvent_;
    float capsuleFocusScale_ = 1.0f;
    ShadowStyle focusShadowStyle_ = ShadowStyle::None;
    bool isFocusScaleSet_ = false;
    bool isFocusTextColorSet_ = false;
    bool isFocusShadowSet_ = false;
    Color defaultTextColor_;
    Color focusedTextColor_;
    std::optional<Color> backgroundColorOptional_;
    std::optional<Color> selectColorOptional_;
    std::optional<Color> borderColorOptional_;
    Color fontColor_;
    double value_ = 0.0;
    bool initFlag_ = false;
    ProgressType progressType_ = ProgressType::LINEAR;
    bool isTextFromUser_ = false;
    bool visibilityProp_ = true;
    bool isRightToLeft_ = false;
    bool isUserInitiatedColor_ = false;
    bool isUserInitiatedBgColor_ = false;
    bool isModifierInitiatedColor_ = false;
    bool isModifierInitiatedBgColor_ = false;
    double reportLastValue_ = 0.0f;
    ACE_DISALLOW_COPY_AND_MOVE(ProgressPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_PATTERN_H
