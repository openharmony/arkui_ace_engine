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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_SLIDING_PANEL_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_SLIDING_PANEL_LAYOUT_ALGORITHM_H

#include <cstdint>
#include <optional>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SlidingPanelLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(SlidingPanelLayoutAlgorithm, LayoutAlgorithm);

public:
    SlidingPanelLayoutAlgorithm() = default;
    ~SlidingPanelLayoutAlgorithm() override = default;

    void OnReset() override {}
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    void SetCurrentOffset(float offset)
    {
        currentOffset_ = offset;
    }

    float GetCurrentOffset() const
    {
        return currentOffset_;
    }

    void SetIsFirstLayout(bool isFirstLayout)
    {
        isFirstLayout_ = isFirstLayout;
    }

    bool GetIsFirstLayout() const
    {
        return isFirstLayout_;
    }

    Dimension GetFullHeight()
    {
        return fullHeight_;
    }

    Dimension GetHalfHeight()
    {
        return halfHeight_;
    }

    Dimension GetMiniHeight()
    {
        return miniHeight_;
    }

    CalcDimension GetCustomHeight()
    {
        return customHeight_;
    }

    void SetInvisibleFlag(bool invisibleFlag)
    {
        invisibleFlag_ = invisibleFlag;
    }

    float GetMaxWidth() const
    {
        return maxWidth_;
    }

private:
    RefPtr<LayoutWrapper> GetNodeLayoutWrapperByTag(LayoutWrapper* layoutWrapper, const std::string& tagName) const;
    void MeasureCloseIcon(
        const RefPtr<LayoutWrapper>& closeIconWrapper, const RefPtr<LayoutProperty>& layoutProperty) const;
    float GetMaxWidthByScreenSizeType(const SizeF& maxSize, const SizeF& idealSize) const;

    float currentOffset_ = 0.0f;
    bool isFirstLayout_ = true;
    Dimension fullHeight_;
    Dimension halfHeight_;
    Dimension miniHeight_;
    CalcDimension customHeight_;
    bool invisibleFlag_ = false;
    float maxWidth_ = 0.0f;
    SizeF idealSize_;

    ACE_DISALLOW_COPY_AND_MOVE(SlidingPanelLayoutAlgorithm);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PANEL_SLIDING_PANEL_LAYOUT_ALGORITHM_H