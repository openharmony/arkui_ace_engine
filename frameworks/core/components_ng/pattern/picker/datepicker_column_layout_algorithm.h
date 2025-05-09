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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATE_PICKER_DATE_PICKER_COLUMN_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATE_PICKER_DATE_PICKER_COLUMN_LAYOUT_ALGORITHM_H

#include "core/components/picker/picker_theme.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_algorithm.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT DatePickerColumnLayoutAlgorithm : public LinearLayoutAlgorithm {
    DECLARE_ACE_TYPE(DatePickerColumnLayoutAlgorithm, LinearLayoutAlgorithm);

public:
    DatePickerColumnLayoutAlgorithm() = default;
    ~DatePickerColumnLayoutAlgorithm() override = default;

    void OnReset() override {}

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;
    void MeasureText(LayoutWrapper* layoutWrapper, const SizeF& size);
    void ChangeTextStyle(uint32_t index, uint32_t showOptionCount, const SizeF& size,
        const RefPtr<LayoutWrapper>& childLayoutWrapper, LayoutWrapper* layoutWrapper);

    std::vector<int32_t> GetCurrentOffset() const
    {
        return currentOffset_;
    }

    void SetCurrentOffset(const std::vector<int32_t>& currentOffset)
    {
        currentOffset_ = currentOffset;
    }

private:
    void InitGradient(const float& gradientPercent, const RefPtr<FrameNode> blendNode,
        const RefPtr<FrameNode> columnNode);
    const Dimension AdjustFontSizeScale(const Dimension& fontSizeValue, double fontScale);
    bool NeedAdaptForAging();
    float ReCalcItemHeightScale(const Dimension& userSetHeight, bool isDividerSpacing = true);
    void MeasureText(LayoutWrapper* layoutWrapper, const RefPtr<PickerTheme>& pickerTheme, const SizeF& size);

    float pickerItemHeight_ = 0.0f;
    float dividerSpacingFontScale_ = 1.0f;
    float gradientFontScale_ = 1.0f;
    std::vector<int32_t> currentOffset_;

    ACE_DISALLOW_COPY_AND_MOVE(DatePickerColumnLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATE_PICKER_DATE_PICKER_COLUMN_LAYOUT_ALGORITHM_H
