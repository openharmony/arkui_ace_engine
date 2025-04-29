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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TIME_PICKER_TIME_PICKER_COLUMN_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TIME_PICKER_TIME_PICKER_COLUMN_LAYOUT_ALGORITHM_H

#include "base/i18n/localization.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_algorithm.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT TimePickerColumnLayoutAlgorithm : public LinearLayoutAlgorithm {
    DECLARE_ACE_TYPE(TimePickerColumnLayoutAlgorithm, LinearLayoutAlgorithm);

public:
    TimePickerColumnLayoutAlgorithm() = default;
    ~TimePickerColumnLayoutAlgorithm() override = default;

    void OnReset() override {}

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;
    void MeasureText(LayoutWrapper* layoutWrapper, const SizeF& size);
    void ChangeAmPmTextStyle(uint32_t index, uint32_t showOptionCount, const SizeF& size,
        const RefPtr<LayoutWrapper>& childLayoutWrapper, LayoutWrapper* layoutWrapper);

    void SetHour24(bool value)
    {
        hour24_ = value;
    }

    bool GetHour24() const
    {
        return hour24_;
    }
    std::vector<int32_t> GetCurrentOffset() const
    {
        return currentOffset_;
    }

    void SetCurrentOffset(const std::vector<int32_t>& currentOffset)
    {
        currentOffset_ = currentOffset;
    }

private:
    float pickerItemHeight_ = 0.0f;
    std::vector<int32_t> currentOffset_;
    float dividerSpacingFontScale_ = 1.0f;
    float gradientFontScale_ = 1.0f;
    const Dimension AdjustFontSizeScale(const Dimension& fontSizeValue, double fontScale);
    bool NeedAdaptForAging();
    float ReCalcItemHeightScale(const Dimension& userSetHeight, bool isDividerSpacing = true);
    bool hour24_ = SystemProperties::Is24HourClock();
    void InitGradient(const float& gradientPercent, const RefPtr<FrameNode> blendNode,
        const RefPtr<FrameNode> columnNode);
    float GetPickerMaxHeight(
        const std::optional<LayoutConstraintF>& layoutConstraint, const RefPtr<FrameNode>& pickerNode);
    ACE_DISALLOW_COPY_AND_MOVE(TimePickerColumnLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TIME_PICKER_TIME_PICKER_COLUMN_LAYOUT_ALGORITHM_H
