/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/menu/navigation_menu_layout_algorithm.h"

#include "base/geometry/ng/offset_t.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void NavigationMenuLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto props = AceType::DynamicCast<MenuLayoutProperty>(layoutWrapper->GetLayoutProperty());
    LOGD("MenuLayout: clickPosition = %{public}f, %{public}f", position_.GetX(), position_.GetY());
    CHECK_NULL_VOID(props);

    float x = HorizontalLayout(size, position_.GetX());
    float y = VerticalLayout(size, position_.GetY());
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto outPadding = static_cast<float>(theme->GetOutPadding().ConvertToPx());
    auto child = layoutWrapper->GetOrCreateChildByIndex(0, false);
    float offsetX = 0.0;
    if (child) {
        offsetX = child->GetGeometryNode()->GetFrameSize().Width() + outPadding * 2;
    }
    layoutWrapper->GetGeometryNode()->SetMarginFrameOffset(NG::OffsetF(x - offsetX, y));

    // translate each option by the height of previous options
    OffsetF translate(outPadding, outPadding);
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        LOGD("layout child at offset: %{public}f, %{public}f", translate.GetX(), translate.GetY());
        child->GetGeometryNode()->SetMarginFrameOffset(translate);
        child->Layout();
        translate += OffsetF(0, child->GetGeometryNode()->GetFrameSize().Height());
    }
}

} // namespace OHOS::Ace::NG
