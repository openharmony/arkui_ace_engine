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

#include "core/components_v2/list/list_item_element.h"
#include "core/components_v2/list/render_list_item.h"

namespace OHOS::Ace::V2 {

RefPtr<RenderNode> ListItemElement::CreateRenderNode()
{
    auto renderListItem = AceType::DynamicCast<RenderListItem>(RenderElement::CreateRenderNode());
    if (!renderListItem) {
        LOGE("Failed to create render node for list element");
        return nullptr;
    }
    renderListItem->RegisterGetChildCallback(
        [weak = AceType::WeakClaim(this)] (ListItemChildType type) -> RefPtr<RenderNode> {
            auto element = weak.Upgrade();
            if (!element) {
                return nullptr;
            }
            if (type == ListItemChildType::ITEM_CHILD) {
                return element->itemChild_ ? element->itemChild_->GetRenderNode() : nullptr;
            }
            if (type == ListItemChildType::SWIPER_START) {
                return element->swiperStartElement_ ? element->swiperStartElement_->GetRenderNode() : nullptr;
            }
            if (type == ListItemChildType::SWIPER_END) {
                return element->swiperEndElement_ ? element->swiperEndElement_->GetRenderNode() : nullptr;
            }
            return nullptr;
        }
    );
    return renderListItem;
}

void ListItemElement::PerformBuild()
{
    auto listItemComponent = AceType::DynamicCast<ListItemComponent>(component_);
    if (!listItemComponent) {
        return;
    }
    itemChild_ = UpdateChild(itemChild_, listItemComponent->GetChild());
    if (swiperStartElement_ || listItemComponent->GetSwiperStartComponent()) {
        swiperStartElement_ = UpdateChild(swiperStartElement_, listItemComponent->GetSwiperStartComponent());
    }
    if (swiperEndElement_ || listItemComponent->GetSwiperEndComponent()) {
        swiperEndElement_ = UpdateChild(swiperEndElement_, listItemComponent->GetSwiperEndComponent());
    }
}
} // namespace OHOS::Ace::V2
