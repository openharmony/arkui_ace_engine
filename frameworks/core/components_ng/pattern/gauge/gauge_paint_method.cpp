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
    gaugeModifier_->UpdateValue();
}

void GaugePaintMethod::SetBoundsRect()
{
    CHECK_NULL_VOID(gaugeModifier_);
    auto gaugePattern = DynamicCast<GaugePattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(gaugePattern);
    auto host = gaugePattern->GetHost();
    CHECK_NULL_VOID(host);
    auto hostGeometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(hostGeometryNode);
    auto paintProperty = host->GetPaintProperty<GaugePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    GaugeShadowOptions shadowOptions;
    if (paintProperty->HasShadowOptions()) {
        shadowOptions = paintProperty->GetShadowOptionsValue();
    }
    auto frameSize = hostGeometryNode->GetFrameSize();
    float x = std::min<float>(shadowOptions.offsetX - shadowOptions.radius, boundsRect_.GetX());
    float y = std::min<float>(shadowOptions.offsetY - shadowOptions.radius, boundsRect_.GetY());
    float width = std::max<float>(
        { boundsRect_.Width(), boundsRect_.GetX() + boundsRect_.Width() - x,
        shadowOptions.offsetX - x + frameSize.Width() + shadowOptions.radius * 2.0f,
        std::abs(shadowOptions.offsetX) + frameSize.Width() + shadowOptions.radius * 2.0f }
    );
    float height = std::max<float>(
        { boundsRect_.Height(), boundsRect_.GetY() + boundsRect_.Height() - y,
        shadowOptions.offsetY - y + frameSize.Height() + shadowOptions.radius * 2.0f,
        std::abs(shadowOptions.offsetY) + frameSize.Height() + shadowOptions.radius * 2.0f }
    );
    boundsRect_.SetRect(x, y, width, height);
    gaugeModifier_->SetBoundsRect(boundsRect_);
}
} // namespace OHOS::Ace::NG
