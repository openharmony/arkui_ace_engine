/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "base/memory/referenced.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/canvas/canvas_pattern.h"
#include "drawing_rendering_context_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {

DrawingRenderingContextPeerImpl::DrawingRenderingContextPeerImpl()
{
    SetInstanceId(Ace::Container::CurrentIdSafely());
}
void DrawingRenderingContextPeerImpl::SetOptions(const std::optional<CanvasUnit>& optUnit)
{
    if (optUnit && optUnit.value() == CanvasUnit::PX) {
        SetUnit(CanvasUnit::PX);
    }
}
void DrawingRenderingContextPeerImpl::SetInvalidate()
{
    auto customPaintPattern = AceType::DynamicCast<NG::CanvasPattern>(canvasPattern_);
    CHECK_NULL_VOID(customPaintPattern);
    customPaintPattern->SetInvalidate();
}
SizeF DrawingRenderingContextPeerImpl::GetSize()
{
    auto width = size_.Width().value_or(0.0);
    auto height = size_.Height().value_or(0.0);
    return SizeF(width, height);
}
std::shared_ptr<RSCanvas> DrawingRenderingContextPeerImpl::GetCanvas() const
{
    return rsCanvas_;
}
void DrawingRenderingContextPeerImpl::SetRSCanvasCallback(RefPtr<AceType>& canvasPattern)
{
    std::function<void(RSCanvas*, double, double)> callback =
        [wp = WeakClaim(this)](RSCanvas* canvas, double width, double height) {
        auto context = wp.Upgrade();
        CHECK_NULL_VOID(context);
        double density = context->GetDensity();
        if (density == 0) {
            return;
        }
        height /= density;
        width /= density;
        context->size_.SetHeight(height);
        context->size_.SetWidth(width);
        context->rsCanvas_ = std::shared_ptr<RSCanvas>(canvas);
    };
    auto customPaintPattern = AceType::DynamicCast<NG::CanvasPattern>(canvasPattern);
    if (customPaintPattern) {
        customPaintPattern->SetRSCanvasCallback(callback);
    }
}
} // namespace OHOS::Ace::NG::GeneratedModifier
