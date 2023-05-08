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
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_layout_property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SideBarContainerLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(SideBarContainerLayoutAlgorithm, LayoutAlgorithm);

public:
    SideBarContainerLayoutAlgorithm() = default;
    ~SideBarContainerLayoutAlgorithm() override = default;

    void OnReset() override {}
    void Measure(FrameNode* frameNode) override;
    void Layout(FrameNode* frameNode) override;

    void SetCurrentOffset(float offset)
    {
        currentOffset_ = offset;
    }

    void SetSideBarStatus(SideBarStatus sideBarStatus)
    {
        sideBarStatus_ = sideBarStatus;
    }

    void SetRealSideBarWidth(float realSideBarWidth)
    {
        realSideBarWidth_ = realSideBarWidth;
    }

    float GetRealSideBarWidth() const
    {
        return realSideBarWidth_;
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

    float GetRealSideBarHeight() const
    {
        return realSideBarHeight_;
    }

    OffsetF GetSideBarOffset() const
    {
        return sideBarOffset_;
    }

private:
    void MeasureControlButton(const RefPtr<SideBarContainerLayoutProperty>& layoutProperty,
        const RefPtr<FrameNode>& button, float parentWidth);
    void MeasureSideBar(const RefPtr<SideBarContainerLayoutProperty>& layoutProperty,
        const RefPtr<FrameNode>& sideBar);
    void MeasureSideBarContent(const RefPtr<SideBarContainerLayoutProperty>& layoutProperty,
        const RefPtr<FrameNode>& content, float parentWidth);
    void MeasureDivider(const RefPtr<SideBarContainerLayoutProperty>& layoutProperty,
        const RefPtr<FrameNode>& divider, float parentWidth);
    void LayoutControlButton(FrameNode* frameNode, const RefPtr<FrameNode>& button);
    void LayoutSideBar(FrameNode* frameNode, const RefPtr<FrameNode>& sideBar);
    void LayoutSideBarContent(FrameNode* frameNode, const RefPtr<FrameNode>& content);
    void LayoutDivider(FrameNode* frameNode, const RefPtr<FrameNode>& divider);
    void InitRealSideBarWidth(FrameNode* frameNode, float parentWidth);

    float currentOffset_ = 0.0f;
    float realSideBarWidth_ = 0.0f;
    float realSideBarHeight_ = 0.0f;
    float realDividerWidth_ = 0.0f;
    SideBarStatus sideBarStatus_ = SideBarStatus::SHOW;
    bool needInitRealSideBarWidth_ = true;
    OffsetF sideBarOffset_;

    ACE_DISALLOW_COPY_AND_MOVE(SideBarContainerLayoutAlgorithm);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SIDE_BAR_SIDE_BAR_CONTAINER_LAYOUT_ALGORITHM_H
