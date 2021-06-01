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

#include "core/components/flex/render_flex_item.h"

#include "base/utils/utils.h"
#include "core/components/flex/flex_item_component.h"

namespace OHOS::Ace {

RefPtr<RenderNode> RenderFlexItem::Create()
{
    return AceType::MakeRefPtr<RenderFlexItem>();
}

void RenderFlexItem::Update(const RefPtr<Component>& component)
{
    const RefPtr<FlexItemComponent> flexItem = AceType::DynamicCast<FlexItemComponent>(component);
    if (!flexItem) {
        return;
    }
    // check the validity of properties
    if (flexItem->GetFlexShrink() >= 0.0) {
        flexShrink_ = flexItem->GetFlexShrink();
    }
    if (flexItem->GetFlexBasis() >= 0.0) {
        flexBasis_ = flexItem->GetFlexBasis();
    }
    if (flexItem->GetFlexGrow() >= 0.0) {
        flexGrow_ = flexItem->GetFlexGrow();
    }
    canStretch_ = flexItem->GetStretchFlag();
    alignSelf_ = flexItem->GetAlignSelf();
    minWidth_ = flexItem->GetMinWidth();
    minHeight_ = flexItem->GetMinHeight();
    maxWidth_ = flexItem->GetMaxWidth();
    maxHeight_ = flexItem->GetMaxHeight();
    isHidden_ = flexItem->IsHidden();
    MarkNeedLayout();
}

bool RenderFlexItem::MaybeRelease()
{
    auto context = GetContext().Upgrade();
    if (context && context->GetRenderFactory()->GetRenderFlexItemFactory()->Recycle(this)) {
        ClearRenderObject();
        return false;
    }
    return true;
}

void RenderFlexItem::ClearRenderObject()
{
    RenderNode::ClearRenderObject();
    flexGrow_ = 0.0;
    flexShrink_ = 0.0;
    flexBasis_ = 0.0;
    canStretch_ = true;
    minWidth_ = Dimension();
    minHeight_ = Dimension();
    maxWidth_ = Dimension(Size::INFINITE_SIZE);
    maxHeight_ = Dimension(Size::INFINITE_SIZE);
    alignSelf_ = FlexAlign::AUTO;
}

} // namespace OHOS::Ace
