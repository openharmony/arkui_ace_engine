/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SIDE_BAR_CONTAINER_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SIDE_BAR_CONTAINER_MODEL_STATIC_H

#include "core/components_ng/pattern/side_bar/side_bar_container_pattern.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SideBarContainerModelStatic {
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetSideBarContainerType(FrameNode* frameNode, const std::optional<SideBarContainerType>& type);
    static void SetSideBarWidth(FrameNode* frameNode, const std::optional<Dimension>& sideBarWidth);
    static void SetMinSideBarWidth(FrameNode* frameNode, const std::optional<Dimension>& minSideBarWidth);
    static void SetControlButtonWidth(FrameNode* frameNode, const std::optional<Dimension>& width);
    static void SetControlButtonHeight(FrameNode* frameNode, const std::optional<Dimension>& height);
    static void SetControlButtonLeft(FrameNode* frameNode, const Dimension& left);
    static void SetControlButtonTop(FrameNode* frameNode, const Dimension& top);
    static void SetControlButtonShowIconInfo(
        FrameNode* frameNode, const std::string& showIconStr, bool isPixelMap, RefPtr<PixelMap> pixMap);
    static void SetControlButtonHiddenIconInfo(
        FrameNode* frameNode, const std::string& hiddenIconStr, bool isPixelMap, RefPtr<PixelMap> pixMap);
    static void SetControlButtonSwitchingIconInfo(
        FrameNode* frameNode, const std::string& switchingIconStr, bool isPixelMap, RefPtr<PixelMap> pixMap);
    static void SetShowControlButton(FrameNode* frameNode, bool showControlButton);
    static void SetAutoHide(FrameNode* frameNode, bool autoHide);
    static void SetMaxSideBarWidth(FrameNode* frameNode, const std::optional<Dimension>& maxSideBarWidth);
    static void SetMinContentWidth(FrameNode* frameNode, const std::optional<Dimension>& minContentWidth);
    static void SetSideBarPosition(FrameNode* frameNode, const std::optional<SideBarPosition>& sideBarPosition);
    static void SetShowSideBar(FrameNode* frameNode, bool isShow);

    static void SetDividerStrokeWidth(FrameNode* frameNode, const std::optional<Dimension>& strokeWidth);
    static void SetDividerColor(FrameNode* frameNode, const Color& color);
    static void SetDividerStartMargin(FrameNode* frameNode, const Dimension& startMargin);
    static void SetDividerEndMargin(FrameNode* frameNode, const Dimension& endMargin);
    static void SetOnChange(FrameNode* frameNode, std::function<void(const bool)>&& onChange);
    static void SetOnChangeEvent(FrameNode* frameNode, std::function<void(const bool)>&& onChangeEvent);
    static void ResetControlButtonLeft(FrameNode* frameNode);
    static void ResetControlButtonIconInfo(FrameNode* frameNode);
private:
    static bool IsDoubleBindBlock(const RefPtr<SideBarContainerPattern>& sideBarContainerPattern);
    static void MarkNeedInitRealSideBarWidth(FrameNode* frameNode);
    static bool sideBarWidthDoubleBind_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SIDE_BAR_CONTAINER_MODEL_STATIC_H
