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

#include "core/components/page/page_element.h"

#include "core/common/frontend.h"
#include "core/components/transform/transform_element.h"

namespace OHOS::Ace {

PageElement::PageElement(int32_t pageId, const ComposeId& id) : ComposedElement(id), pageId_(pageId) {}

PageElement::PageElement(int32_t pageId, const ComposeId& cardComposeId, const ComposeId& id)
    : ComposedElement(id), pageId_(pageId), cardComposeId_(cardComposeId) {}

bool PageElement::RequestNextFocus(bool vertical, bool reverse, const Rect& rect)
{
    // Do not precess logic.
    return false;
}

void PageElement::RemoveSharedTransition(const ShareId& shareId)
{
    LOGD("Remove shared transition id:%{public}s", shareId.c_str());
    sharedTransitionElementMap_.erase(shareId);
}

void PageElement::AddSharedTransition(const RefPtr<SharedTransitionElement>& shared)
{
    if (!shared) {
        LOGE("Add shared transition failed. element is null.");
        return;
    }
    LOGD("Add shared transition element id:%{public}s", shared->GetShareId().c_str());
    sharedTransitionElementMap_[shared->GetShareId()] = shared;
}

const PageElement::SharedTransitionMap& PageElement::GetSharedTransitionMap() const
{
    return sharedTransitionElementMap_;
}

void PageElement::SetHidden(bool hidden)
{
    auto render = GetRenderNode();
    if (render) {
        auto parent = render->GetParent().Upgrade();
        if (parent) {
            parent->MarkNeedRender();
        }
        render->SetHidden(hidden);
    }

    for (auto&& [id, callback] : hiddenCallbackMap_) {
        callback(hidden);
    }
}

void PageElement::RemoveCardTransition(int32_t retakeId)
{
    cardTransitionMap_.erase(retakeId);
}

void PageElement::AddCardTransition(const RefPtr<TransformElement>& transform)
{
    if (!transform) {
        LOGE("Add transform transition failed. element is null.");
        return;
    }
    cardTransitionMap_[transform->GetRetakeId()] = transform;
}

const PageElement::CardTransitionMap& PageElement::GetCardTransitionMap() const
{
    return cardTransitionMap_;
}

} // namespace OHOS::Ace