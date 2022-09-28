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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SIDE_BAR_CONTAINER_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SIDE_BAR_CONTAINER_VIEW_H

#include <optional>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_event_hub.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SideBarContainerView {
public:
    static void Create();
    static void Pop();
    static void SetSideBarContainerType(SideBarContainerType type);
    static void SetShowSideBar(bool isShow);
    static void SetShowControlButton(bool showControlButton);
    static void SetSideBarWidth(const Dimension& sideBarWidth);
    static void SetMinSideBarWidth(const Dimension& minSideBarWidth);
    static void SetMaxSideBarWidth(const Dimension& maxSideBarWidth);
    static void SetAutoHide(bool autoHide);
    static void SetSideBarPosition(SideBarPosition sideBarPosition);
    static void SetControlButtonWidth(const Dimension& width);
    static void SetControlButtonHeight(const Dimension& height);
    static void SetControlButtonLeft(const Dimension& left);
    static void SetControlButtonTop(const Dimension& top);
    static void SetControlButtonShowIconStr(const std::string& showIconStr);
    static void SetControlButtonHiddenIconStr(const std::string& hiddenIconStr);
    static void SetControlButtonSwitchingIconStr(const std::string& switchingIconStr);
    static void SetOnChange(ChangeEvent&& onChange);

private:
    static void CreateAndMountControlButton(const RefPtr<FrameNode>& parentNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SIDE_BAR_CONTAINER_VIEW_H
