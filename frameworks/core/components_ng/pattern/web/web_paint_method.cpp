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

#include "core/components_ng/pattern/web/web_paint_method.h"
#include "surface_utils.h"
#include "render_service_client/core/ui/rs_surface_node.h"
#include "core/components_ng/render/adapter/rosen_render_surface.h"
namespace OHOS::Ace::NG {
CanvasDrawFunction WebPaintMethod::GetForegroundDrawFunction(PaintWrapper* paintWrapper)
{
    return [weak = WeakClaim(this)](RSCanvas& canvas) {
        auto painter = weak.Upgrade();
        CHECK_NULL_VOID(painter);
        auto surface = DynamicCast<NG::RosenRenderSurface>(painter->renderSuface_);
        if (surface) {
            surface->DrawBuffer();
        }
    };
}
} // namespace OHOS::Ace::NG