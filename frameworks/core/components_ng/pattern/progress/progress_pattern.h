/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "base/log/log_wrapper.h"
#include "core/components/common/layout/constants.h"
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
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
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
        ProgressType progressType_ = progressLayoutProperty->GetType().value_or(ProgressType::LINEAR);
        if (!progressModifier_) {
            progressModifier_ = AceType::MakeRefPtr<ProgressModifier>();
        }
        progressModifier_->SetVisible(visibilityProp_);
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

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override;

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

private:
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnAttachToFrameNode() override;
    void OnModifyDone() override;
    void InitTouchEvent();
    void RemoveTouchEvent();
    void OnPress(const TouchEventInfo& info);
    void HandleEnabled();
    void InitOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    void GetInnerFocusPaintRect(RoundRect& paintRect);
    void ToJsonValueForRingStyleOptions(std::unique_ptr<JsonValue>& json) const;
    void ToJsonValueForLinearStyleOptions(std::unique_ptr<JsonValue>& json) const;
    static std::string ConvertProgressStatusToString(const ProgressStatus status);

    double strokeWidth_ = 2;
    RefPtr<ProgressModifier> progressModifier_;
    RefPtr<TouchEventImpl> touchListener_;
    Color backgroundColor_;
    Color selectColor_;
    Color borderColor_;
    Color fontColor_;
    bool isTextFromUser_ = false;
    bool visibilityProp_ = true;

    ACE_DISALLOW_COPY_AND_MOVE(ProgressPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_PATTERN_H
