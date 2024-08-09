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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_SIDE_BAR_CONTAINER_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_SIDE_BAR_CONTAINER_MODEL_IMPL_H

#include "bridge/declarative_frontend/jsview/js_stack.h"
#include "core/components/side_bar/side_bar_container_component.h"
#include "core/components_ng/pattern/side_bar/side_bar_container_model.h"

namespace OHOS::Ace::Framework {
class ACE_EXPORT SideBarContainerModelImpl : public SideBarContainerModel {
public:
    void Create() override {}
    void SetSideBarContainerType(SideBarContainerType type) override;
    void SetShowSideBar(bool isShow) override;
    void SetShowControlButton(bool showControlButton) override;
    void ParseAndSetWidth(WidthType widthType, Dimension& width) override;
    void SetSideBarWidth(const Dimension& sideBarWidth) override;
    void SetMinSideBarWidth(const Dimension& minSideBarWidth) override;
    void SetMaxSideBarWidth(const Dimension& maxSideBarWidth) override;
    void SetAutoHide(bool autoHide) override;
    void SetSideBarPosition(SideBarPosition sideBarPosition) override;
    void SetControlButtonWidth(const Dimension& width) override;
    void SetControlButtonHeight(const Dimension& height) override;
    void SetControlButtonLeft(const Dimension& left) override;
    void SetControlButtonTop(const Dimension& top) override;
    void SetControlButtonShowIconInfo(
        const std::string& showIconStr, bool isPixelMap, RefPtr<PixelMap> pixMap) override;
    void SetControlButtonHiddenIconInfo(
        const std::string& hiddenIconStr, bool isPixelMap, RefPtr<PixelMap> pixMap) override;
    void SetControlButtonSwitchingIconInfo(
        const std::string& switchingIconStr, bool isPixelMap, RefPtr<PixelMap> pixMap) override;
    void ResetControlButtonIconInfo() override;
    void SetOnChange(std::function<void(const bool)>&& onChange) override;
    void SetDividerStrokeWidth(const Dimension& strokeWidth) override;
    void SetDividerColor(const Color& color) override;
    void SetDividerStartMargin(const Dimension& startMargin) override;
    void SetDividerEndMargin(const Dimension& endMargin) override;
    void SetOnChangeEvent(std::function<void(const bool)>&& onChange) override {};
    void SetMinContentWidth(const Dimension& minContentWidth) override;
    void ResetControlButton() override;

private:
    void MarkNeedInitRealSideBarWidth() override;
};
} // namespace OHOS::Ace::Framework
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SIDE_BAR_CONTAINER_MODEL_IMPL_H
