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

#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"

namespace OHOS::Ace::NG {
void ContainerModalPattern::ShowTitle(bool /* isShow */, bool hasDeco)
{
    hasDeco_ = hasDeco;
    windowMode_ = WindowMode::WINDOW_MODE_FULLSCREEN;
    moveX_ = 1.0;
    moveY_ = 1.0;
}

void ContainerModalPattern::InitContainerEvent() {}

void ContainerModalPattern::OnWindowFocused() {}

void ContainerModalPattern::OnWindowUnfocused() {}

void ContainerModalPattern::WindowFocus(bool isFocus)
{
    isFocus_ = isFocus;
}

void ContainerModalPattern::ChangeTitle(const RefPtr<FrameNode>& titleNode, bool isFocus) {}

void ContainerModalPattern::ChangeFloatingTitle(const RefPtr<FrameNode>& floatingNode, bool isFocus) {}

void ContainerModalPattern::ChangeTitleButtonIcon(
    const RefPtr<FrameNode>& buttonNode, InternalResource::ResourceId icon, bool isFocus)
{}

bool ContainerModalPattern::CanShowFloatingTitle()
{
    return true;
}

void ContainerModalPattern::SetAppTitle(const std::string& title)
{
    moveX_ = 1.0;
}

void ContainerModalPattern::SetAppIcon(const RefPtr<PixelMap>& icon)
{
    moveX_ = 1.0;
}

void ContainerModalPattern::SetContainerButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize)
{
    hideSplitButton_ = hideSplit;
}

void ContainerModalPattern::SetCloseButtonStatus(bool isEnabled) {}
} // namespace OHOS::Ace::NG
