/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
            ProgressAnimatableProperty progressAnimatableProperty{};
            InitAnimatableProperty(progressAnimatableProperty);
            progressModifier_ = AceType::MakeRefPtr<ProgressModifier>(progressAnimatableProperty);
        }
        bool isRtl = progressLayoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
        if (isRightToLeft_ != isRtl) {
            isRightToLeft_ = isRtl;
        }
        progressModifier_->SetIsRightToLeft(isRightToLeft_);
        progressModifier_->SetVisible(visibilityProp_);
        progressModifier_->SetUseContentModifier(UseContentModifier());
        return MakeRefPtr<ProgressPaintMethod>(progressType_, strokeWidth_, progressModifier_);
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

private:
    void InitAnimatableProperty(ProgressAnimatableProperty& progressAnimatableProperty);
    void CalculateStrokeWidth(const SizeF& contentSize);
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnAttachToFrameNode() override;
    void OnModifyDone() override;
    void DumpInfo() override;
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;
    void DumpSimplifyInfo(std::unique_ptr<JsonValue>& json) override {}
    void OnLanguageConfigurationUpdate() override;
    void InitTouchEvent();
    void RemoveTouchEvent();
    void OnPress(const TouchEventInfo& info);
    void HandleEnabled();
    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    void GetInnerFocusPaintRect(RoundRect& paintRect);
    void ToJsonValueForRingStyleOptions(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void ToJsonValueForLinearStyleOptions(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    static std::string ConvertProgressStatusToString(const ProgressStatus status);
    void OnSensitiveStyleChange(bool isSensitive) override;
    void ObscureText(bool isSensitive);
    void FireBuilder();
    RefPtr<FrameNode> BuildContentModifierNode();
    std::optional<ProgressMakeCallback> makeFunc_;
    RefPtr<FrameNode> contentModifierNode_;

    float strokeWidth_ = Dimension(4.0_vp).ConvertToPx();
    RefPtr<ProgressModifier> progressModifier_;
    RefPtr<TouchEventImpl> touchListener_;
    Color backgroundColor_;
    Color selectColor_;
    Color borderColor_;
    Color fontColor_;
    double value_ = 0.0;
    bool initFlag_ = false;
    ProgressType progressType_ = ProgressType::LINEAR;
    bool isTextFromUser_ = false;
    bool visibilityProp_ = true;
    bool isRightToLeft_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(ProgressPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_PATTERN_H
