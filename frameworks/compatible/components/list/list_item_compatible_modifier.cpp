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

#include "compatible/components/list/list_item_compatible_modifier.h"

#include "compatible/components/list/list_item_component.h"
#include "compatible/components/list/render_list_item.h"
#include "compatible/components/list_v2/list_item_component.h"

namespace OHOS::Ace::ListItemCompatibleModifier {
namespace {
OHOS::Ace::RRect GetRRect(OHOS::Ace::RefPtr<OHOS::Ace::RenderListItem> renderListItem)
{
    return renderListItem->GetRRect();
}
void RunCardTransitionAnimation(OHOS::Ace::RefPtr<OHOS::Ace::RenderListItem> renderListItem, double shiftHeight)
{
    renderListItem->RunCardTransitionAnimation(shiftHeight);
}
void StopCardTransitionAnimation(OHOS::Ace::RefPtr<OHOS::Ace::RenderListItem> renderListItem)
{
    renderListItem->StopCardTransitionAnimation();
}
OHOS::Ace::RefPtr<OHOS::Ace::ListItemComponent> GetListItemComponent(
    const std::string& type, const OHOS::Ace::RefPtr<OHOS::Ace::Component>& child)
{
    return AceType::MakeRefPtr<OHOS::Ace::ListItemComponent>(type, child);
}
OHOS::Ace::RefPtr<OHOS::Ace::ListItemComponent> GetListItem(OHOS::Ace::RefPtr<OHOS::Ace::Component> listItem)
{
    auto listItemComponent = AceType::DynamicCast<OHOS::Ace::ListItemComponent>(listItem);
    return listItemComponent->GetListItem(listItem);
}
double GetPositionInList(OHOS::Ace::RefPtr<OHOS::Ace::RenderListItem> renderListItem)
{
    return renderListItem->GetPositionInList();
}
OHOS::Ace::RefPtr<OHOS::Ace::V2::ListItemComponent> MakeV2ListItemComponent()
{
    return AceType::MakeRefPtr<OHOS::Ace::V2::ListItemComponent>();
}
OHOS::Ace::RefPtr<OHOS::Ace::V2::ListItemComponent> GetV2ListItemComponent(
    OHOS::Ace::RefPtr<OHOS::Ace::Component> component)
{
    return AceType::DynamicCast<OHOS::Ace::V2::ListItemComponent>(component);
}
bool InstanceOfV2ListItemComponent(OHOS::Ace::RefPtr<OHOS::Ace::Component> component)
{
    return AceType::InstanceOf<OHOS::Ace::V2::ListItemComponent>(component);
}
}
const ArkUIListItemCompatibleModifier* GetListItemCompatibleModifier()
{
    static const ArkUIListItemCompatibleModifier instance = {
        .getRRect = GetRRect,
        .runCardTransitionAnimation = RunCardTransitionAnimation,
        .stopCardTransitionAnimation = StopCardTransitionAnimation,
        .getListItemComponent = GetListItemComponent,
        .getListItem = GetListItem,
        .getPositionInList = GetPositionInList,
        .makeV2ListItemComponent = MakeV2ListItemComponent,
        .getV2ListItemComponent = GetV2ListItemComponent,
        .instanceOfV2ListItemComponent = InstanceOfV2ListItemComponent,
    };
    return &instance;
}
} // OHOS::Ace::ListItemCompatibleModifier