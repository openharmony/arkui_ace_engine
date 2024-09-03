/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components_v2/indexer/indexer_element.h"

namespace OHOS::Ace::V2 {
void IndexerElement::PerformBuild()
{
    RefPtr<IndexerComponent> indexer = AceType::DynamicCast<IndexerComponent>(component_);
    if (indexer) {
        LOGI("[indexer] PerformBuild: Build Indexer");
        ComponentGroupElement::PerformBuild();
    }
}

bool IndexerElement::IndexMoveUp()
{
    RefPtr<RenderIndexer> renderIndexer = AceType::DynamicCast<RenderIndexer>(renderNode_);
    int32_t index = renderIndexer->GetFocusIndex();
    auto prevItem = prevFocusedItem_.Upgrade();
    if (prevItem) {
        prevItem->SetFocused(false);
    }
    index -= 1;
    if (index < 0) {
        renderIndexer->SetFocusIndex(-1);
        renderIndexer->ClearFocusAnimation();
        return false;
    }
    auto indexerItem = renderIndexer->GetSpecificItem(index);
    if (!indexerItem) {
        return false;
    }

    indexerItem->SetFocused(true);
    renderIndexer->HandleFocusAnimation(indexerItem->GetLayoutSize(), indexerItem->GetGlobalOffset());
    renderIndexer->MoveSectionWithIndexer(index);
    renderIndexer->SetFocusIndex(index);
    prevFocusedItem_ = indexerItem;
    return true;
}

bool IndexerElement::IndexMoveDown()
{
    RefPtr<RenderIndexer> renderIndexer = AceType::DynamicCast<RenderIndexer>(renderNode_);
    int32_t index = renderIndexer->GetFocusIndex();
    auto prevItem = prevFocusedItem_.Upgrade();
    if (prevItem) {
        prevItem->SetFocused(false);
    }
    index += 1;
    auto indexerItem = renderIndexer->GetSpecificItem(index);
    if (!indexerItem) {
        renderIndexer->ClearFocusAnimation();
        return false;
    }
    
    indexerItem->SetFocused(true);
    renderIndexer->HandleFocusAnimation(indexerItem->GetLayoutSize(), indexerItem->GetGlobalOffset());
    renderIndexer->MoveSectionWithIndexer(index);
    renderIndexer->SetFocusIndex(index);
    prevFocusedItem_ = indexerItem;
    return true;
}

bool IndexerElement::OnKeyEvent(const KeyEvent& keyEvent)
{
    if (keyEvent.action != KeyAction::DOWN) {
        return false;
    }
    if (keyEvent.code == KeyCode::KEY_DPAD_UP) {
        return IndexMoveUp();
    } else if (keyEvent.code == KeyCode::KEY_DPAD_DOWN) {
        return IndexMoveDown();
    } else if (keyEvent.code == KeyCode::KEY_ENTER || keyEvent.code == KeyCode::KEY_NUMPAD_ENTER) {
        RefPtr<RenderIndexer> renderIndexer = AceType::DynamicCast<RenderIndexer>(renderNode_);
        int32_t index = renderIndexer->GetFocusIndex();
        if (index > -1) {
            renderIndexer->MoveSectionWithIndexer(index);
            return true;
        }
        return false;
    } else {
        return false;
    }
}
} // namespace OHOS::Ace::V2