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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_INDICATOR_LINEAR_INDICATOR_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_INDICATOR_LINEAR_INDICATOR_PATTERN_H

#include "core/components_ng/pattern/linear_indicator/linear_indicator_controller.h"
#include "core/components_ng/pattern/linear_indicator/linear_indicator_layout_property.h"
#include "core/components_ng/pattern/linear_indicator/linear_indicator_theme.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

class LinearIndicatorPattern : public LinearLayoutPattern {
    DECLARE_ACE_TYPE(LinearIndicatorPattern, LinearLayoutPattern);

public:
    LinearIndicatorPattern();

    ~LinearIndicatorPattern() override;

    const RefPtr<LinearIndicatorController>& GetController() const
    {
        return controller_;
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override;

    void DumpInfo() override;
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;
    void DumpSimplifyInfo(std::shared_ptr<JsonValue>& json) override {}

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override;

private:
    void OnModifyDone() override;
    void UpdateProgressNode();

    bool IsChangeLayoutPropertyAndUpdate(RefPtr<LinearIndicatorLayoutProperty> layoutProperty);
    void UpdateProgressNodeAtIndex(std::size_t index);
    void AddProgressNode();

    std::size_t GetProgressSize();
    RefPtr<FrameNode> GetProgressNode(int32_t index);

    void RegisterVisibleChange();
    void VisibleChange(bool visible);

    bool CalcProgressWidth(float& progressWidth);

    OHOS::Ace::RefPtr<LinearIndicatorTheme> theme_;

    Dimension strokeWidth_;
    Dimension strokeRadius_;
    Color trackBackgroundColor_;
    Color trackColor_;
    TextDirection direction_;

    RefPtr<LinearIndicatorController> controller_;
    bool hasVisibleChangeRegistered_;
    bool isVisibleChangePause_;

    ACE_DISALLOW_COPY_AND_MOVE(LinearIndicatorPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_INDICATOR_LINEAR_INDICATOR_PATTERN_H
