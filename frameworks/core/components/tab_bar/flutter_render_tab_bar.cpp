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

#include "core/components/tab_bar/flutter_render_tab_bar.h"

#include "core/components/flex/render_flex.h"
#include "core/pipeline/base/flutter_render_context.h"

namespace OHOS::Ace {

using namespace Flutter;

RenderLayer FlutterRenderTabBar::GetRenderLayer()
{
    if (!layer_) {
        layer_ = AceType::MakeRefPtr<ClipLayer>(
            0.0, GetLayoutSize().Width(), 0.0, GetLayoutSize().Height(), Clip::HARD_EDGE);
    }
    return AceType::RawPtr(layer_);
}

void FlutterRenderTabBar::Paint(RenderContext& context, const Offset& offset)
{
    auto tabsRenderNode = FindTabsNode();
    CHECK_NULL_VOID(tabsRenderNode);
    auto tabsLayoutSize = tabsRenderNode->GetLayoutSize();
    double left = 0.0;
    double top = 0.0;
    if (tabsLayoutSize.Width() < GetLayoutSize().Width()) {
        left = (GetLayoutSize().Width() - tabsLayoutSize.Width()) / 2;
    }
    if (GetLayoutSize().Height() > tabsLayoutSize.Height()) {
        top = (GetLayoutSize().Height() - tabsLayoutSize.Height()) / 2;
    }
    layer_->SetClip(left, left + tabsLayoutSize.Width(), top, top + tabsLayoutSize.Height(), Clip::HARD_EDGE);
    RenderTabBar::Paint(context, offset);
}

RefPtr<RenderNode> FlutterRenderTabBar::FindTabsNode()
{
    int32_t count = 0;
    RefPtr<RenderNode> parent = GetParent().Upgrade();
    while (parent) {
        if (count > 3) {
            return nullptr;
        }
        if (AceType::InstanceOf<RenderFlex>(parent)) {
            return AceType::DynamicCast<RenderNode>(parent);
        }
        count++;
        parent = parent->GetParent().Upgrade();
    }
    return nullptr;
}

} // namespace OHOS::Ace
