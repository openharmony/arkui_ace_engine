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

#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_item.h"

namespace OHOS::Ace::NG {
RefPtr<ScrollableItem> ScrollableItem::GetOrCreateScrollableItem(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto node = ElementRegister::GetInstance()->GetSpecificItemById<ScrollableItem>(nodeId);
    if (node) {
        if (node->GetTag() == tag) {
            return node;
        }
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
        auto parent = node->GetParent();
        if (parent) {
            parent->RemoveChild(node);
        }
    }

    auto pattern = patternCreator ? patternCreator() : AceType::MakeRefPtr<Pattern>();
    node = AceType::MakeRefPtr<ScrollableItem>(tag, nodeId, pattern, false);
    node->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(node);
    return node;
}

// return true to release the ScrollableItem
// return false to deallocate the ScrollableItem
bool ScrollableItem::MaybeRelease()
{
    if (!SystemProperties::GetEnableScrollableItemPool()) {
        return true;
    }
    deleter_(this);
    return maybeRelease_;
}

} // namespace OHOS::Ace::NG
