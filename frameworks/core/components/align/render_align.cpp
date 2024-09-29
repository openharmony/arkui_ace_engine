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

#include "core/components/align/render_align.h"

#include "core/components/align/align_component.h"

namespace OHOS::Ace {

RefPtr<RenderNode> RenderAlign::Create()
{
    return AceType::MakeRefPtr<RenderAlign>();
}

void RenderAlign::Update(const RefPtr<Component>& component)
{
    const RefPtr<AlignComponent> align = AceType::DynamicCast<AlignComponent>(component);
    if (align && ((align->GetAlignment() != alignment_) || !hasUpdated_)) {
        hasUpdated_ = true;
        alignment_ = align->GetAlignment();
        MarkNeedLayout();
    }
}

void RenderAlign::PerformLayout()
{
    const std::list<RefPtr<RenderNode>>& children = GetChildren();
    if (!children.empty()) {
        const auto& child = children.front();
        const LayoutParam& alignInnerLayout = GetLayoutParam();
        child->Layout(alignInnerLayout);
        if (!alignInnerLayout.GetMaxSize().IsInfinite()) {
            SetLayoutSize(alignInnerLayout.GetMaxSize());
        } else {
            SetLayoutSize(child->GetLayoutSize());
        }
        child->SetPosition(Alignment::GetAlignPosition(GetLayoutSize(), child->GetLayoutSize(), alignment_));
    }
}

} // namespace OHOS::Ace
