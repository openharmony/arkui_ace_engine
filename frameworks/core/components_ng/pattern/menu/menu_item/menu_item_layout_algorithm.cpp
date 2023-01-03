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

#include "core/components_ng/pattern/menu/menu_item/menu_item_layout_algorithm.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/option/option_theme.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace::NG {
void MenuItemLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    verInterval_ = VERTICAL_INTERVAL_PHONE.ConvertToPx();
    horInterval_ = HORIZONTAL_INTERVAL_PHONE.ConvertToPx();
    auto props = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(props);
    auto layoutConstraint = props->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);

    float maxRowWidth = layoutConstraint->maxSize.Width() - horInterval_ * 2.0;
    // measure row
    auto childConstraint = props->CreateChildConstraint();
    childConstraint.maxSize.SetWidth(maxRowWidth);
    childConstraint.percentReference.SetWidth(maxRowWidth);

    if (layoutConstraint->selfIdealSize.Width().has_value()) {
        childConstraint.selfIdealSize.SetWidth(layoutConstraint->selfIdealSize.Width().value() - horInterval_ * 2.0);
    }

    auto row = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(row);

    row->Measure(childConstraint);

    // set self size based on row size;
    auto rowSize = row->GetGeometryNode()->GetFrameSize();
    SizeF size(rowSize.Width() + horInterval_ * 2.0, rowSize.Height() + verInterval_ * 2.0);
    LOGD("menuItem frame size set to %{public}f x %{public}f", size.Width(), size.Height());
    layoutWrapper->GetGeometryNode()->SetFrameSize(size);
}

void MenuItemLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto row = layoutWrapper->GetOrCreateChildByIndex(0);
    row->GetGeometryNode()->SetMarginFrameOffset(OffsetF(horInterval_, verInterval_));
    row->Layout();
}
} // namespace OHOS::Ace::NG