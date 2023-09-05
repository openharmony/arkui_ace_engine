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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SIDE_BAR_SIDE_BAR_CONTAINER_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SIDE_BAR_SIDE_BAR_CONTAINER_LAYOUT_ALGORITHM_H

#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_layout_property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SideBarContainerLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(SideBarContainerLayoutAlgorithm, LayoutAlgorithm);

public:
    SideBarContainerLayoutAlgorithm() = default;
    ~SideBarContainerLayoutAlgorithm() override = default;

    void OnReset() override {}
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    void SetCurrentOffset(float offset)
    {
        currentOffset_ = offset;
    }

    void SetSideBarStatus(SideBarStatus sideBarStatus)
    {
        sideBarStatus_ = sideBarStatus;
    }

    SideBarStatus GetSideBarStatus() const
    {
        return sideBarStatus_;
    }

    void SetRealSideBarWidth(Dimension realSideBarWidth)
    {
        realSideBarWidthDimension_ = realSideBarWidth;
    }

    Dimension GetRealSideBarWidth() const
    {
        return realSideBarWidthDimension_;
    }

    void SetRealDividerWidth(float realDividerWidth)
    {
        realDividerWidth_ = realDividerWidth;
    }

    float GetRealDividerWidth() const
    {
        return realDividerWidth_;
    }

    void SetNeedInitRealSideBarWidth(bool needInitRealSideBarWidth)
    {
        needInitRealSideBarWidth_ = needInitRealSideBarWidth;
    }

    void SetRealSideBarHeight(float realSideBarHeight)
    {
        realSideBarHeight_ = realSideBarHeight;
    }

    float GetRealSideBarHeight() const
    {
        return realSideBarHeight_;
    }

    OffsetF GetSideBarOffset() const
    {
        return sideBarOffset_;
    }

    SideBarContainerType GetSideBarContainerType() const
    {
        return type_;
    }

    void SetSideBarContainerType(SideBarContainerType type)
    {
        type_ = type;
    }

    void SetControlButtonClick(bool value)
    {
        isControlButtonClick_ = value;
    }

    Dimension GetAdjustMaxSideBarWidth() const
    {
        return adjustMaxSideBarWidth_;
    }

    Dimension GetAdjustMinSideBarWidth() const
    {
        return adjustMinSideBarWidth_;
    }

    void SetMinSideBarWidth(float minSideBarWidth)
    {
        minSideBarWidth_ = minSideBarWidth;
    }

    void SetMaxSideBarWidth(float maxSideBarWidth)
    {
        maxSideBarWidth_ = maxSideBarWidth;
    }

    void SetMinContentWidth(float minContentWidth)
    {
        minContentWidth_ = minContentWidth;
    }

    void SetTypeUpdateWidth(float typeUpdateWidth)
    {
        typeUpdateWidth_ = typeUpdateWidth;
    }

    void SetPattern(const WeakPtr<Pattern>& pattern)
    {
        pattern_ = pattern;
    }

    void SetControlImageWidth(const Dimension& width)
    {
        controlImageWidth_ = width;
    }

    void SetControlImageHeight(const Dimension& height)
    {
        controlImageHeight_ = height;
    }

    void SetPreSideBarWidth(Dimension value)
    {
        preSideBarWidth_ = value;
    }

    Dimension GetPreSideBarWidth() const
    {
        return preSideBarWidth_;
    }

    bool GetAutoHide() const
    {
        return autoHide_;
    }

private:
    void MeasureControlButton(const RefPtr<SideBarContainerLayoutProperty>& layoutProperty,
        const RefPtr<LayoutWrapper>& buttonLayoutWrapper, float parentWidth);
    void MeasureSideBar(const RefPtr<SideBarContainerLayoutProperty>& layoutProperty,
        const RefPtr<LayoutWrapper>& sideBarLayoutWrapper);
    void MeasureSideBarContent(const RefPtr<SideBarContainerLayoutProperty>& layoutProperty,
        const RefPtr<LayoutWrapper>& contentLayoutWrapper, float parentWidth);
    void MeasureDivider(const RefPtr<SideBarContainerLayoutProperty>& layoutProperty,
        const RefPtr<LayoutWrapper>& dividerLayoutWrapper, float parentWidth);
    void LayoutControlButton(LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& buttonLayoutWrapper);
    void LayoutSideBar(LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& sideBarLayoutWrapper);
    void LayoutSideBarContent(LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& contentLayoutWrapper);
    void LayoutDivider(LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& dividerLayoutWrapper);
    void InitRealSideBarWidth(LayoutWrapper* layoutWrapper, float parentWidth);
    void AutoMode(const RefPtr<SideBarContainerLayoutProperty>& layoutProperty, float parentWidth);
    void AutoChangeSideBarWidth(const RefPtr<SideBarContainerLayoutProperty>& layoutProperty, float parentWidth);
    void UpdateDefaultValueByVersion();
    SideBarPosition GetSideBarPositionWithRtl(const RefPtr<SideBarContainerLayoutProperty>& layoutProperty);
    void AdjustMinAndMaxSideBarWidth(LayoutWrapper* layoutWrapper);
    RefPtr<LayoutWrapper> GetSideBarLayoutWrapper(LayoutWrapper* layoutWrapper) const;
    void GetAllPropertyValue(const RefPtr<SideBarContainerLayoutProperty>& layoutProperty, float parentWidth);
    void InitSideBarWidth(float parentWidth);
    void MeasureRealSideBarWidth(float parentWidth);
    void MeasureTypeUpdateWidth();
    void MeasureRealPropertyValue(bool setMinSideBarWidth, bool setMaxSideBarWidth, bool setSideBarWidth,
        bool setMinContentWidth, float paretWidth);

    float currentOffset_ = 0.0f;
    float realSideBarWidth_ = -1.0f;
    float realSideBarHeight_ = 0.0f;
    float realDividerWidth_ = 0.0f;
    float minContentWidth_ = -1.0f;
    float minSideBarWidth_ = -1.0f;
    float maxSideBarWidth_ = -1.0f;

    float defaultRealSideBarWidth_ = 0.0f;
    float defaultMinSideBarWidth_ = 0.0f;
    float defaultMaxSideBarWidth_ = 0.0f;
    float defaultMinContentWidth_ = 0.0f;
    float typeUpdateWidth_ = 0.0f;
    WeakPtr<Pattern> pattern_;
    SideBarStatus sideBarStatus_ = SideBarStatus::SHOW;
    bool needInitRealSideBarWidth_ = true;
    OffsetF sideBarOffset_;
    SideBarContainerType type_ = SideBarContainerType::EMBED;
    bool isControlButtonClick_ = false;
    bool autoHide_ = false;

    Dimension adjustMaxSideBarWidth_;
    Dimension adjustMinSideBarWidth_;
    Dimension controlImageWidth_;
    Dimension controlImageHeight_;
    Dimension realSideBarWidthDimension_;
    Dimension preSideBarWidth_;

    ACE_DISALLOW_COPY_AND_MOVE(SideBarContainerLayoutAlgorithm);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SIDE_BAR_SIDE_BAR_CONTAINER_LAYOUT_ALGORITHM_H
