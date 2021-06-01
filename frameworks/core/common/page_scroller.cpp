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

#include "core/common/page_scroller.h"

#include "core/components/scroll/render_scroll.h"
#include "core/components/scroll/scroll_element.h"
#include "core/pipeline/base/composed_element.h"

namespace OHOS::Ace {

void PageScroller::SetClickPosition(const Offset& position)
{
    position_ = position;
}

void PageScroller::MovePage(const RefPtr<StackElement>& stackElement, const Offset& rootRect, double offsetHeight)
{
    if (!stackElement) {
        return;
    }

    const auto& composedElement = AceType::DynamicCast<ComposedElement>(stackElement->GetChildren().front());
    if (!composedElement) {
        return;
    }
    const auto& scrollElement = AceType::DynamicCast<ScrollElement>(composedElement->GetChildren().front());
    if (!scrollElement) {
        return;
    }

    const auto& scroll = AceType::DynamicCast<RenderScroll>(scrollElement->GetRenderNode());
    if (!scroll) {
        return;
    }

    if (GreatNotEqual(position_.GetY(), rootRect.GetY())) {
        hasMove_ = true;
        scroll->SetNeedMove(true);
    }

    if (LessNotEqual(offsetHeight, 0.0) && hasMove_) {
        scroll->SetNeedMove(false);
        hasMove_ = false;
    }
}

}; // namespace OHOS::Ace
