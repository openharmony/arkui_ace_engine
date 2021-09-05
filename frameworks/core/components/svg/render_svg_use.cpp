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

#include "frameworks/core/components/svg/render_svg_use.h"

#include "frameworks/core/components/svg/svg_use_component.h"

namespace OHOS::Ace {

void RenderSvgUse::Update(const RefPtr<Component>& component)
{
    const RefPtr<SvgUseComponent> svgUseComponent = AceType::DynamicCast<SvgUseComponent>(component);
    if (!svgUseComponent) {
        LOGW("component is null");
        return;
    }
    x_ = svgUseComponent->GetX();
    y_ = svgUseComponent->GetY();
    RenderSvgBase::SetPresentationAttrs(svgUseComponent->GetDeclaration());
    MarkNeedLayout();
}

void RenderSvgUse::PerformLayout()
{
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("context is null");
        return;
    }
    const auto& child = GetFirstChild();
    if (child) {
        child->Layout(GetLayoutParam());
        SetLayoutSize(child->GetLayoutSize());
    }
}

} // namespace OHOS::Ace
