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

#include "core/components_ng/pattern/union_container/union_container_pattern.h"

#include "core/components_ng/render/adapter/rosen_render_context.h"

namespace OHOS::Ace::NG {
void UnionContainerPattern::SetSpacing(const CalcDimension& spacing)
{
    if (spacing.IsNegative() || spacing.Unit() == DimensionUnit::PERCENT) {
        spacing_ = CalcDimension();
    } else {
        spacing_ = spacing;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto rosenRenderContext = AceType::DynamicCast<NG::RosenRenderContext>(renderContext);
    CHECK_NULL_VOID(rosenRenderContext);
    auto spaceInPx = spacing.ConvertToPx();
    if (NonPositive(spaceInPx) || std::isnan(spaceInPx)) {
        spaceInPx = 0.0f;
    }
    rosenRenderContext->SetUnionSpacing(spaceInPx);
}
} // namespace OHOS::Ace::NG
