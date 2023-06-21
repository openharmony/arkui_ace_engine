/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SIDE_BAR_CONTAINER_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SIDE_BAR_CONTAINER_MODEL_H

#include <optional>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_event_hub.h"

namespace OHOS::Ace {
enum class WidthType : uint32_t {
    SIDEBAR_WIDTH = 0,
    MIN_SIDEBAR_WIDTH,
    MAX_SIDEBAR_WIDTH,
};

class ACE_EXPORT SideBarContainerModel {
public:
    static SideBarContainerModel* GetInstance();
    virtual ~SideBarContainerModel() = default;

    virtual void Create();
    virtual void Pop();
    virtual void SetSideBarContainerType(SideBarContainerType type);
    virtual void SetShowSideBar(bool isShow);
    virtual void SetShowControlButton(bool showControlButton);
    virtual void ParseAndSetWidth(WidthType widthType, Dimension& width);
    virtual void SetSideBarWidth(const Dimension& sideBarWidth);
    virtual void SetMinSideBarWidth(const Dimension& minSideBarWidth);
    virtual void SetMaxSideBarWidth(const Dimension& maxSideBarWidth);
    virtual void SetAutoHide(bool autoHide);
    virtual void SetSideBarPosition(SideBarPosition sideBarPosition);
    virtual void SetControlButtonWidth(const Dimension& width);
    virtual void SetControlButtonHeight(const Dimension& height);
    virtual void SetControlButtonLeft(const Dimension& left);
    virtual void SetControlButtonTop(const Dimension& top);
    virtual void SetControlButtonShowIconStr(const std::string& showIconStr);
    virtual void SetControlButtonHiddenIconStr(const std::string& hiddenIconStr);
    virtual void SetControlButtonSwitchingIconStr(const std::string& switchingIconStr);
    virtual void SetOnChange(std::function<void(const bool)>&& onChange);
    virtual void SetDividerStrokeWidth(const Dimension& strokeWidth);
    virtual void SetDividerColor(const Color& color);
    virtual void SetDividerStartMargin(const Dimension& startMargin);
    virtual void SetDividerEndMargin(const Dimension& endMargin);
    virtual void SetOnChangeEvent(std::function<void(const bool)>&& onChangeEvent);
    virtual void SetMinContentWidth(const Dimension& minContentWidth);

private:
    static std::unique_ptr<SideBarContainerModel> instance_;
    static std::mutex mutex_;

    virtual void CreateAndMountControlButton(const RefPtr<NG::FrameNode>& parentNode);
    virtual void CreateAndMountDivider(const RefPtr<NG::FrameNode>& parentNode);
    virtual void InitSideBarContentEvent(const RefPtr<NG::FrameNode>& parentNode,
        const RefPtr<NG::FrameNode>& sideBarContentFrameNode);
    virtual void MarkNeedInitRealSideBarWidth();
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SIDE_BAR_CONTAINER_MODEL_H
