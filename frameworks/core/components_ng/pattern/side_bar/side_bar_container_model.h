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

using OnSideBarWidthChangeEvent = std::function<void(const Dimension&)>;
class ACE_FORCE_EXPORT SideBarContainerModel {
public:
    static SideBarContainerModel* GetInstance();
    virtual ~SideBarContainerModel() = default;

    virtual void Create();
    virtual void SetSideBarContainerType(SideBarContainerType type);
    virtual void SetShowSideBar(bool isShow);
    virtual void SetShowControlButton(bool showControlButton);
    virtual void ParseAndSetWidth(WidthType widthType, Dimension& width, bool isDoubleBind = false);
    virtual void ParseAndSetWidth(WidthType widthType, const RefPtr<ResourceObject>& resObj) {};
    virtual void ResetResObj(const std::string& key) {}
    virtual void SetSideBarWidth(const Dimension& sideBarWidth, bool isDoubleBind = false);
    virtual void SetMinSideBarWidth(const Dimension& minSideBarWidth);
    virtual void SetMaxSideBarWidth(const Dimension& maxSideBarWidth);
    virtual void SetAutoHide(bool autoHide);
    virtual void SetSideBarPosition(SideBarPosition sideBarPosition);
    virtual void SetControlButtonWidth(const Dimension& width);
    virtual void SetControlButtonHeight(const Dimension& height);
    virtual void SetControlButtonLeft(const Dimension& left);
    virtual void ResetControlButtonLeft() {}
    virtual void SetControlButtonTop(const Dimension& top);
    virtual void SetControlButtonShowIconInfo(
        const std::string& showIconStr, bool isPixelMap, RefPtr<PixelMap> pixMap);
    virtual void SetControlButtonHiddenIconInfo(
        const std::string& hiddenIconStr, bool isPixelMap, RefPtr<PixelMap> pixMap);
    virtual void SetControlButtonSwitchingIconInfo(
        const std::string& switchingIconStr, bool isPixelMap, RefPtr<PixelMap> pixMap);
    virtual void SetControlButtonShowIconInfo(
        const RefPtr<ResourceObject>& showIconResObj, bool isPixelMap, RefPtr<PixelMap> pixMap) {};
    virtual void SetControlButtonHiddenIconInfo(
        const RefPtr<ResourceObject>& reshiddenIconResObjObj, bool isPixelMap, RefPtr<PixelMap> pixMap) {};
    virtual void SetControlButtonSwitchingIconInfo(
        const RefPtr<ResourceObject>& showIconResObj, bool isPixelMap, RefPtr<PixelMap> pixMap) {};
    virtual void ResetControlButtonIconInfo();
    virtual void SetOnChange(std::function<void(const bool)>&& onChange);
    virtual void SetDividerStrokeWidth(const Dimension& strokeWidth);
    virtual void SetDividerColor(const Color& color);
    virtual void SetDividerStartMargin(const Dimension& startMargin);
    virtual void SetDividerEndMargin(const Dimension& endMargin);
    virtual void SetDividerStrokeWidth(const RefPtr<ResourceObject>& strokeWidthResObj) {};
    virtual void SetDividerColor(const RefPtr<ResourceObject>& colorResObj) {};
    virtual void SetDividerStartMargin(const RefPtr<ResourceObject>& startMarginResObj) {};
    virtual void SetDividerEndMargin(const RefPtr<ResourceObject>& endMarginResObj) {};
    virtual void SetOnChangeEvent(std::function<void(const bool)>&& onChangeEvent);
    virtual void SetOnSideBarWidthChangeEvent(OnSideBarWidthChangeEvent&& event);
    virtual void SetMinContentWidth(const Dimension& minContentWidth);
    virtual void SetMinContentWidth(const RefPtr<ResourceObject>& resObj) {};
    virtual void ResetControlButton();

private:
    static std::unique_ptr<SideBarContainerModel> instance_;
    static std::mutex mutex_;

    virtual void MarkNeedInitRealSideBarWidth();
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SIDE_BAR_CONTAINER_MODEL_H
