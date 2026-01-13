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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_LIST_LIST_ITEM_COMPATIBLE_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_LIST_LIST_ITEM_COMPATIBLE_MODIFIER_H

#include <string>

namespace OHOS::Ace {
class RRect;
class RenderListItem;
class Component;
class ListItemComponent;
template<class T>
class RefPtr;
namespace V2 {
class ListItemComponent;
}
} // namespace OHOS::Ace

struct ArkUIListItemCompatibleModifier {
    OHOS::Ace::RRect (*getRRect)(OHOS::Ace::RefPtr<OHOS::Ace::RenderListItem> renderListItem);
    void (*runCardTransitionAnimation)(OHOS::Ace::RefPtr<OHOS::Ace::RenderListItem> renderListItem, double shiftHeight);
    void (*stopCardTransitionAnimation)(OHOS::Ace::RefPtr<OHOS::Ace::RenderListItem> renderListItem);
    OHOS::Ace::RefPtr<OHOS::Ace::ListItemComponent> (*getListItemComponent)(
        const std::string& type, const OHOS::Ace::RefPtr<OHOS::Ace::Component>& child);
    OHOS::Ace::RefPtr<OHOS::Ace::ListItemComponent> (*getListItem)(OHOS::Ace::RefPtr<OHOS::Ace::Component> listItem);
    double (*getPositionInList)(OHOS::Ace::RefPtr<OHOS::Ace::RenderListItem> renderListItem);
    OHOS::Ace::RefPtr<OHOS::Ace::V2::ListItemComponent> (*makeV2ListItemComponent)();
    OHOS::Ace::RefPtr<OHOS::Ace::V2::ListItemComponent> (*getV2ListItemComponent)(
        OHOS::Ace::RefPtr<OHOS::Ace::Component> component);
    bool (*instanceOfV2ListItemComponent)(OHOS::Ace::RefPtr<OHOS::Ace::Component> component);
};

#endif // FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_LIST_LIST_ITEM_COMPATIBLE_MODIFIER_H