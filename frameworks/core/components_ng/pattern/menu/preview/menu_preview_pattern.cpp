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

#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"

#include "core/animation/animation_pub.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t PIXELMAP_ANIMATION_DURATION = 300;
constexpr float PIXELMAP_ANIMATION_SCALE = 1.0f;
constexpr Dimension CONTAINER_OUTER_RADIUS = 16.0_vp;
} // namespace
void MenuPreviewPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
}

bool MenuPreviewPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetRenderContext();
    CHECK_NULL_RETURN(context, false);
    context->UpdateBackgroundColor(Color::WHITE);
    context->SetClipToBounds(true);
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(CONTAINER_OUTER_RADIUS);
    context->UpdateBorderRadius(borderRadius);
    AnimationOption option;
    option.SetDuration(PIXELMAP_ANIMATION_DURATION);
    option.SetCurve(Curves::SHARP);

    AnimationUtils::Animate(
        option,
        [context]() mutable {
            context->UpdateTransformScale(VectorF(PIXELMAP_ANIMATION_SCALE, PIXELMAP_ANIMATION_SCALE));
        },
        option.GetOnFinishEvent());
    return false;
}
} // namespace OHOS::Ace::NG
