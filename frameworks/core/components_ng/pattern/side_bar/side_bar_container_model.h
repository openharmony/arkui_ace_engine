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

class ACE_FORCE_EXPORT SideBarContainerModel {
public:
    static SideBarContainerModel* GetInstance();
    virtual ~SideBarContainerModel() = default;

    virtual void Create() = 0;
    virtual void SetSideBarContainerType(SideBarContainerType type) = 0;
    virtual void SetShowSideBar(bool isShow) = 0;
    virtual void SetShowControlButton(bool showControlButton) = 0;
    virtual void ParseAndSetWidth(WidthType widthType, Dimension& width) = 0;
    virtual void SetSideBarWidth(const Dimension& sideBarWidth) = 0;
    virtual void SetMinSideBarWidth(const Dimension& minSideBarWidth) = 0;
    virtual void SetMaxSideBarWidth(const Dimension& maxSideBarWidth) = 0;
    virtual void SetAutoHide(bool autoHide) = 0;
    virtual void SetSideBarPosition(SideBarPosition sideBarPosition) = 0;
    virtual void SetControlButtonWidth(const Dimension& width) = 0;
    virtual void SetControlButtonHeight(const Dimension& height) = 0;
    virtual void SetControlButtonLeft(const Dimension& left) = 0;
    virtual void ResetControlButtonLeft() {}
    virtual void SetControlButtonTop(const Dimension& top) = 0;
    virtual void SetControlButtonShowIconInfo(
        const std::string& showIconStr, bool isPixelMap, RefPtr<PixelMap> pixMap) = 0;
    virtual void SetControlButtonHiddenIconInfo(
        const std::string& hiddenIconStr, bool isPixelMap, RefPtr<PixelMap> pixMap) = 0;
    virtual void SetControlButtonSwitchingIconInfo(
        const std::string& switchingIconStr, bool isPixelMap, RefPtr<PixelMap> pixMap) = 0;
    virtual void ResetControlButtonIconInfo() = 0;
    virtual void SetOnChange(std::function<void(const bool)>&& onChange) = 0;
    virtual void SetDividerStrokeWidth(const Dimension& strokeWidth) = 0;
    virtual void SetDividerColor(const Color& color) = 0;
    virtual void SetDividerStartMargin(const Dimension& startMargin) = 0;
    virtual void SetDividerEndMargin(const Dimension& endMargin) = 0;
    virtual void SetOnChangeEvent(std::function<void(const bool)>&& onChangeEvent) = 0;
    virtual void SetMinContentWidth(const Dimension& minContentWidth) = 0;
    virtual void ResetControlButton() = 0;

private:
    static std::unique_ptr<SideBarContainerModel> instance_;
    static std::mutex mutex_;

    virtual void MarkNeedInitRealSideBarWidth() = 0;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SIDE_BAR_CONTAINER_MODEL_H
