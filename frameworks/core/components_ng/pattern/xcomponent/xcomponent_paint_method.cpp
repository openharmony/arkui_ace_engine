/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/xcomponent/xcomponent_paint_method.h"

#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"

namespace OHOS::Ace::NG {
CanvasDrawFunction XComponentPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    auto renderContext = paintWrapper->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto surfaceSize = pattern->GetSurfaceSize();
    auto surfaceOffset = pattern->GetSurfaceOffset();
    auto width = surfaceSize.Width();
    auto height = surfaceSize.Height();
    auto offsetX = surfaceOffset.GetX();
    auto offsetY = surfaceOffset.GetY();
    return [weak = WeakClaim(this), width, height, offsetX, offsetY](RSCanvas& canvas) {
        auto painter = weak.Upgrade();
        CHECK_NULL_VOID(painter);
        auto surface = painter->renderSuface_;
        if (surface) {
            surface->DrawBufferForXComponent(canvas, width, height, offsetX, offsetY);
        }
    };
}
} // namespace OHOS::Ace::NG
