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
#include "core/components_ng/pattern/data_panel/data_panel_pattern.h"

#include "base/utils/utils.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/data_panel/data_panel_layout_algorithm.h"
#include "core/components_ng/pattern/data_panel/data_panel_paint_property.h"
#include "core/components_ng/render/animation_utils.h"

namespace OHOS::Ace::NG {

void DataPanelPattern::OnAttachToFrameNode() {}

bool DataPanelPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool /*skipLayout*/)
{
    if (skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    return true;
}

RefPtr<NodePaintMethod> DataPanelPattern::CreateNodePaintMethod()
{
    if (!dataPanelModifier_) {
        dataPanelModifier_ = AceType::MakeRefPtr<DataPanelModifier>();
    }
    auto paintMethod = MakeRefPtr<DataPanelPaintMethod>(dataPanelModifier_);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, paintMethod);
    auto paintProperty = host->GetPaintProperty<DataPanelPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, paintMethod);
    auto geometryNode = host->GetGeometryNode();
    auto frameSize = geometryNode->GetFrameSize();
    DataPanelShadow shadowOption;
    if (paintProperty->HasShadowOption()) {
        shadowOption = paintProperty->GetShadowOptionValue();
    }
    auto oldBoundsRect = dataPanelModifier_->GetBoundsRect();
    float x = std::min<float>(shadowOption.offsetX - shadowOption.radius, oldBoundsRect->GetX());
    float y = std::min<float>(shadowOption.offsetY - shadowOption.radius, oldBoundsRect->GetY());
    float width = std::max<float>(
        { oldBoundsRect->Width(), oldBoundsRect->GetX() + oldBoundsRect->Width() - x,
        shadowOption.offsetX - x + frameSize.Width() + shadowOption.radius * 2.0f,
        std::abs(shadowOption.offsetX) + frameSize.Width() + shadowOption.radius * 2.0f }
    );
    float height = std::max<float>(
        { oldBoundsRect->Height(), oldBoundsRect->GetY() + oldBoundsRect->Height() - y,
        shadowOption.offsetY - y + frameSize.Height() + shadowOption.radius * 2.0f,
        std::abs(shadowOption.offsetY) + frameSize.Height() + shadowOption.radius * 2.0f }
    );
    RectF boundsRect(x, y, width, height);
    dataPanelModifier_->SetBoundsRect(boundsRect);
    return paintMethod;
}

void DataPanelPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetPositionProperty()) {
        layoutProperty->UpdateAlignment(
            layoutProperty->GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER));
    } else {
        layoutProperty->UpdateAlignment(Alignment::CENTER);
    }
}

} // namespace OHOS::Ace::NG
