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

#include "core/components/container_modal/container_modal_element.h"

namespace OHOS::Ace {
RefPtr<StackElement> ContainerModalElement::GetStackElement() const
{
    return nullptr;
}

RefPtr<OverlayElement> ContainerModalElement::GetOverlayElement() const
{
    return nullptr;
}

RefPtr<StageElement> ContainerModalElement::GetStageElement() const
{
    return nullptr;
}

void ContainerModalElement::ShowTitle(bool isShow)
{
    density_ = 1.0f;
    moveX_ = 0.0f;
    moveY_ = 0.0f;
}

void ContainerModalElement::PerformBuild()
{
}

void ContainerModalElement::FlushReload()
{
}

void ContainerModalElement::Update()
{
}

bool ContainerModalElement::CanShowFloatingTitle()
{
    return false;
}

bool ContainerModalElement::CanHideFloatingTitle()
{
    return false;
}

void ContainerModalElement::ChangeFloatingTitleIcon(bool isFocus)
{
}

void ContainerModalElement::ChangeTitleIcon(bool isFocus)
{
}

void ContainerModalElement::BlurWindow(bool isBlur)
{
}

void ContainerModalElement::WindowFocus(bool isFocus)
{
    windowMode_ = WindowMode::WINDOW_MODE_UNDEFINED;
    windowFocus_ = false;
}

void ContainerModalElement::SetAppBgColor(const Color& color)
{
}

void ContainerModalElement::SetTitleButtonHide(bool hideSplit, bool hideMaximize, bool hideMinimize)
{
}

void ContainerModalElement::SetAppTitle(const std::string& title)
{
}

void ContainerModalElement::SetAppIcon(const RefPtr<PixelMap>& icon)
{
}
} // namespace OHOS::Ace