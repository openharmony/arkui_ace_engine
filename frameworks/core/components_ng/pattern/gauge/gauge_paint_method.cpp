/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/gauge/gauge_paint_method.h"

#include "core/components_ng/pattern/gauge/gauge_pattern.h"

namespace OHOS::Ace::NG {
void GaugePaintMethod::UpdateForegroundModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(gaugeModifier_);
    auto gaugePattern = DynamicCast<GaugePattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(gaugePattern);
    auto host = gaugePattern->GetHost();
    CHECK_NULL_VOID(host);
    auto hostGeometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(hostGeometryNode);
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<GaugePaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    GaugeShadowOptions shadowOptions;
    if (paintProperty->HasShadowOptions()) {
        shadowOptions = paintProperty->GetShadowOptionsValue();
    }
    RectF boundsRect(hostGeometryNode->GetFrameOffset().GetX() - std::abs(shadowOptions.offsetX) - shadowOptions.radius,
        hostGeometryNode->GetFrameOffset().GetY() - std::abs(shadowOptions.offsetY) - shadowOptions.radius,
        hostGeometryNode->GetFrameSize().Width() + std::abs(shadowOptions.offsetX) + shadowOptions.radius,
        hostGeometryNode->GetFrameSize().Height() + std::abs(shadowOptions.offsetY) + shadowOptions.radius);
    gaugeModifier_->SetBoundsRect(boundsRect);
    gaugeModifier_->UpdateValue();
}
} // namespace OHOS::Ace::NG
