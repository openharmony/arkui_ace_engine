/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/semi_modal/semi_modal_element.h"

namespace OHOS::Ace {
void SemiModalElement::AnimateToFullWindow(int32_t duration)
{
}

const Color& SemiModalElement::GetBackgroundColor() const
{
    static Color color;
    return color;
}

bool SemiModalElement::IsFullWindow() const
{
    return fullWindow_;
}

void SemiModalElement::SetFullWindow(bool fullWindow)
{
    fullWindow_ = fullWindow;
}

void SemiModalElement::UpdateSystemBarHeight(double statusBar, double navigationBar)
{
}

void SemiModalElement::UpdateStatusBarHeight(const RefPtr<Element>& column, double height)
{
}

void SemiModalElement::UpdateNavigationBarHeight(const RefPtr<Element>& column, double height)
{
}

RefPtr<OverlayElement> SemiModalElement::GetOverlayElement() const
{
    return nullptr;
}

RefPtr<StageElement> SemiModalElement::GetStageElement() const
{
    return nullptr;
}

void SemiModalElement::AnimateToExitApp() const
{
}
} // namespace OHOS::Ace