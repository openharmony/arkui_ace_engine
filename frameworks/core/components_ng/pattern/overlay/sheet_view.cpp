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

#include "core/components_ng/pattern/overlay/sheet_view.h"

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/utils/utils.h"
#include "core/pipeline/base/element_register.h"
#include "core/components/common/layout/constants.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_paint_property.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_property.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> SheetView::CreateSheetPage(int32_t targetId, RefPtr<FrameNode> builder,
    std::function<void(const std::string&)>&& callback, NG::SheetStyle& sheetStyle)
{
    // create sheet node
    auto sheetNode = FrameNode::CreateFrameNode("SheetPage", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(targetId, std::move(callback)));
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    sheetLayoutProperty->UpdateCrossAxisAlign(FlexAlign::CENTER);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    if (sheetStyle.sheetMode.has_value() && sheetStyle.sheetMode == SheetMode::AUTO) {
        sheetLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS);
    }

    // create drag bar
    bool isShow = sheetStyle.showDragBar.value_or(true);
    auto dragBarNode = FrameNode::GetOrCreateFrameNode("SheetDragBar", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SheetDragBarPattern>(); });
    auto dragBarLayoutProperty = dragBarNode->GetLayoutProperty();
    CHECK_NULL_RETURN(dragBarLayoutProperty, nullptr);
    dragBarLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SHEET_DRAG_BAR_WIDTH), CalcLength(SHEET_DRAG_BAR_HEIGHT)));
    dragBarLayoutProperty->UpdateAlignment(Alignment::CENTER);
    dragBarLayoutProperty->UpdateVisibility(isShow ? VisibleType::VISIBLE : VisibleType::GONE);
    dragBarNode->MountToParent(sheetNode, 0);
    dragBarNode->MarkModifyDone();
    sheetNode->AddChild(builder);
    sheetNode->MarkModifyDone();
    return sheetNode;
}
} // namespace::OHOS::Ace::NG
