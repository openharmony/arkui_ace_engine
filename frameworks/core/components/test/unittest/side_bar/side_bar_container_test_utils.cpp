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

#include "core/components/test/unittest/side_bar/side_bar_container_test_utils.h"

#include "core/components/box/box_component.h"
#include "core/components/display/display_component.h"

namespace OHOS::Ace {
RefPtr<RenderBox> SideBarContainerTestUtils::CreateRenderBox(double width, double height)
{
    RefPtr<RenderBox> renderBox = AceType::MakeRefPtr<MockRenderBox>();
    RefPtr<BoxComponent> boxComponent = AceType::MakeRefPtr<BoxComponent>();
    boxComponent->SetWidth(width);
    boxComponent->SetHeight(height);
    renderBox->Update(boxComponent);
    return renderBox;
}

RefPtr<RenderDisplay> SideBarContainerTestUtils::CreateRenderDisplay()
{
    RefPtr<MockRenderDisplay> renderDisplay = AceType::MakeRefPtr<MockRenderDisplay>();
    RefPtr<BoxComponent> boxComponent = AceType::MakeRefPtr<BoxComponent>();
    RefPtr<DisplayComponent> displayComponent = AceType::MakeRefPtr<DisplayComponent>(boxComponent);
    renderDisplay->Update(displayComponent);
    return renderDisplay;
}
} // namespace OHOS::Ace