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

#include "core/components_ng/pattern/dialog/dialog_layout_algorithm.h"

#include "base/geometry/dimension_offset.h"
#include "base/geometry/ng/point_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/device_config.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/common/properties/placement.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/dialog/dialog_layout_property.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
namespace {

// Using UX spec: Constrain max height within 4/5 of screen height.
// TODO: move these values to theme.
constexpr double DIALOG_HEIGHT_RATIO = 0.8;
constexpr double DIALOG_HEIGHT_RATIO_FOR_LANDSCAPE = 0.9;
constexpr double DIALOG_HEIGHT_RATIO_FOR_CAR = 0.95;
constexpr Dimension listPaddingHeight = 48.0_vp;

} // namespace

void DialogLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto dialogProp = AceType::DynamicCast<DialogLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto customSize = dialogProp->GetUseCustomStyle().value_or(false);
    gridCount_ = dialogProp->GetGridCount().value_or(-1);
    const auto& layoutConstraint = dialogProp->GetLayoutConstraint();
    const auto& parentIdealSize = layoutConstraint->parentIdealSize;
    OptionalSizeF realSize;
    // dialog size fit screen.
    realSize.UpdateIllegalSizeWithCheck(parentIdealSize);
    layoutWrapper->GetGeometryNode()->SetFrameSize(realSize.ConvertToSizeT());
    layoutWrapper->GetGeometryNode()->SetContentSize(realSize.ConvertToSizeT());
    // update child layout constraint
    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.UpdateMaxSizeWithCheck(layoutConstraint->maxSize);
    // constraint child size unless developer is using customStyle
    if (!customSize) {
        ComputeInnerLayoutParam(childLayoutConstraint);
    }
    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.empty()) {
        return;
    }
    auto child = children.front();
    // childSize_ and childOffset_ is used in Layout.
    child->Measure(childLayoutConstraint);

    // scroll for alert
    AnalysisHeightOfChild(layoutWrapper);
}

void DialogLayoutAlgorithm::AnalysisHeightOfChild(LayoutWrapper* layoutWrapper)
{
    float scrollHeight = 0.0f;
    float listHeight = 0.0f;
    float restHeight = 0.0f;
    float restWidth = 0.0f;
    RefPtr<LayoutWrapper> scroll;
    RefPtr<LayoutWrapper> list;
    for (const auto& children : layoutWrapper->GetAllChildrenWithBuild()) {
        restWidth = children->GetGeometryNode()->GetMarginFrameSize().Width();
        restHeight = children->GetGeometryNode()->GetMarginFrameSize().Height();
        for (const auto& grandson : children->GetAllChildrenWithBuild()) {
            if (grandson->GetHostTag() == V2::SCROLL_ETS_TAG) {
                scroll = grandson;
                scrollHeight = grandson->GetGeometryNode()->GetMarginFrameSize().Height();
            } else if (grandson->GetHostTag() == V2::LIST_ETS_TAG) {
                list = grandson;
                listHeight = grandson->GetGeometryNode()->GetMarginFrameSize().Height();
            } else {
                restHeight -= grandson->GetGeometryNode()->GetMarginFrameSize().Height();
            }
        }
    }

    if (scroll != nullptr && list != nullptr) {
        Distribute(scrollHeight, listHeight, restHeight);
        auto childConstraint = CreateDialogChildConstraint(layoutWrapper, scrollHeight, restWidth);
        scroll->Measure(childConstraint);
        childConstraint =
            CreateDialogChildConstraint(layoutWrapper, listHeight + listPaddingHeight.ConvertToPx(), restWidth);
        list->Measure(childConstraint);
    } else {
        if (scroll != nullptr) {
            auto childConstraint =
                CreateDialogChildConstraint(layoutWrapper, std::min(restHeight, scrollHeight), restWidth);
            scroll->Measure(childConstraint);
        }
        if (list != nullptr) {
            auto childConstraint = CreateDialogChildConstraint(
                layoutWrapper, std::min(restHeight, listHeight + (float)listPaddingHeight.ConvertToPx()), restWidth);
            list->Measure(childConstraint);
        }
    }
}

void DialogLayoutAlgorithm::Distribute(float& scrollHeight, float& listHeight, float restHeight)
{
    if (scrollHeight + listHeight > restHeight) {
        if (scrollHeight > restHeight / 2.0 && listHeight > restHeight / 2.0) {
            scrollHeight = restHeight / 2.0;
            listHeight = restHeight / 2.0;
        } else if (scrollHeight > restHeight / 2.0) {
            scrollHeight = restHeight - listHeight;
        } else {
            listHeight = restHeight - scrollHeight;
        }
    }
}

LayoutConstraintF DialogLayoutAlgorithm::CreateDialogChildConstraint(
    LayoutWrapper* layoutWrapper, float Height, float Width)
{
    auto childConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childConstraint.maxSize.SetHeight(Height);
    childConstraint.percentReference.SetHeight(Height);
    childConstraint.maxSize.SetWidth(Width);
    childConstraint.percentReference.SetWidth(Width);
    return childConstraint;
}

void DialogLayoutAlgorithm::ComputeInnerLayoutParam(LayoutConstraintF& innerLayout)
{
    auto maxSize = innerLayout.maxSize;
    // Set different layout param for different devices
    // TODO: need to use theme json to replace this function.
    // get grid size type based on the screen where the dialog locate
    auto gridSizeType = ScreenSystemManager::GetInstance().GetSize(maxSize.Width());
    RefPtr<GridColumnInfo> columnInfo;
    if (SystemProperties::GetDeviceType() == DeviceType::CAR) {
        columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::CAR_DIALOG);
    } else {
        columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::DIALOG);
    }
    columnInfo->GetParent()->BuildColumnWidth(maxSize.Width());
    auto width = GetMaxWidthBasedOnGridType(columnInfo, gridSizeType, SystemProperties::GetDeviceType());
    if (SystemProperties::GetDeviceType() == DeviceType::WATCH) {
        innerLayout.minSize = SizeF(width, 0.0);
        innerLayout.maxSize = SizeF(width, maxSize.Height());
    } else if (SystemProperties::GetDeviceType() == DeviceType::PHONE) {
        if (SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE) {
            innerLayout.minSize = SizeF(width, 0.0);
            innerLayout.maxSize = SizeF(width, maxSize.Height() * DIALOG_HEIGHT_RATIO_FOR_LANDSCAPE);
        } else {
            innerLayout.minSize = SizeF(width, 0.0);
            innerLayout.maxSize = SizeF(width, maxSize.Height() * DIALOG_HEIGHT_RATIO);
        }
    } else if (SystemProperties::GetDeviceType() == DeviceType::CAR) {
        innerLayout.minSize = SizeF(width, 0.0);
        innerLayout.maxSize = SizeF(width, maxSize.Height() * DIALOG_HEIGHT_RATIO_FOR_CAR);
    } else {
        innerLayout.minSize = SizeF(width, 0.0);
        innerLayout.maxSize = SizeF(width, maxSize.Height() * DIALOG_HEIGHT_RATIO);
    }
    // update percentRef
    innerLayout.percentReference = innerLayout.maxSize;
}

double DialogLayoutAlgorithm::GetMaxWidthBasedOnGridType(
    const RefPtr<GridColumnInfo>& info, GridSizeType type, DeviceType deviceType)
{
    auto parentColumns = info->GetParent()->GetColumns();
    if (gridCount_ >= 0) {
        return info->GetWidth(std::min(gridCount_, parentColumns));
    }

    int32_t deviceColumns;
    if (deviceType == DeviceType::WATCH) {
        if (type == GridSizeType::SM) {
            deviceColumns = 3;
        } else if (type == GridSizeType::MD) {
            deviceColumns = 4;
        } else if (type == GridSizeType::LG) {
            deviceColumns = 5;
        } else {
            LOGD("GetMaxWidthBasedOnGridType is undefined");
            deviceColumns = 5;
        }
    } else if (deviceType == DeviceType::PHONE) {
        if (type == GridSizeType::SM) {
            deviceColumns = 4;
        } else if (type == GridSizeType::MD) {
            deviceColumns = 5;
        } else if (type == GridSizeType::LG) {
            deviceColumns = 6;
        } else {
            LOGD("GetMaxWidthBasedOnGridType is undefined");
            deviceColumns = 6;
        }
    } else if (deviceType == DeviceType::CAR) {
        if (type == GridSizeType::SM) {
            deviceColumns = 4;
        } else if (type == GridSizeType::MD) {
            deviceColumns = 6;
        } else if (type == GridSizeType::LG) {
            deviceColumns = 8;
        } else {
            LOGD("GetMaxWidthBasedOnGridType is undefined");
            deviceColumns = 8;
        }
    } else {
        if (type == GridSizeType::SM) {
            deviceColumns = 2;
        } else if (type == GridSizeType::MD) {
            deviceColumns = 3;
        } else if (type == GridSizeType::LG) {
            deviceColumns = 4;
        } else {
            LOGD("GetMaxWidthBasedOnGridType is undefined");
            deviceColumns = 4;
        }
    }
    return info->GetWidth(std::min(deviceColumns, parentColumns));
}

void DialogLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto dialogProp = DynamicCast<DialogLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(dialogProp);
    dialogOffset_ = dialogProp->GetDialogOffset().value_or(DimensionOffset());
    alignment_ = dialogProp->GetDialogAlignment().value_or(DialogAlignment::DEFAULT);
    auto selfSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.empty()) {
        return;
    }
    auto child = children.front();
    auto childSize = child->GetGeometryNode()->GetMarginFrameSize();
    topLeftPoint_ = ComputeChildPosition(childSize, dialogProp, selfSize);
    UpdateTouchRegion();
    child->GetGeometryNode()->SetMarginFrameOffset(topLeftPoint_);
    child->Layout();
    if (dialogProp->GetShowInSubWindowValue(false)) {
        std::vector<Rect> rects;
        auto rect = Rect(0.0f, 0.0f, selfSize.Width(), selfSize.Height());
        rects.emplace_back(rect);
        SubwindowManager::GetInstance()->SetHotAreas(rects);
    }
}

OffsetF DialogLayoutAlgorithm::ComputeChildPosition(
    const SizeF& childSize, const RefPtr<DialogLayoutProperty>& prop, const SizeF& selfSize) const
{
    OffsetF topLeftPoint;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, OffsetF());
    auto dialogTheme = pipelineContext->GetTheme<DialogTheme>();
    const auto& layoutConstraint = prop->GetLayoutConstraint();
    CHECK_NULL_RETURN(dialogTheme, OffsetF());
    auto dialogOffsetX =
        ConvertToPx(CalcLength(dialogOffset_.GetX()), layoutConstraint->scaleProperty, selfSize.Width());
    auto dialogOffsetY =
        ConvertToPx(CalcLength(dialogOffset_.GetY()), layoutConstraint->scaleProperty, selfSize.Height());
    OffsetF dialogOffset = OffsetF(dialogOffsetX.value_or(0.0), dialogOffsetY.value_or(0.0));
    if (SetAlignmentSwitch(layoutConstraint->maxSize, childSize, topLeftPoint)) {
        return topLeftPoint + dialogOffset;
    }
    topLeftPoint = OffsetF(layoutConstraint->maxSize.Width() - childSize.Width(),
                       layoutConstraint->maxSize.Height() - childSize.Height()) /
                   2.0;
    return topLeftPoint + dialogOffset;
}

bool DialogLayoutAlgorithm::SetAlignmentSwitch(
    const SizeF& maxSize, const SizeF& childSize, OffsetF& topLeftPoint) const
{
    if (alignment_ != DialogAlignment::DEFAULT) {
        switch (alignment_) {
            case DialogAlignment::TOP:
                topLeftPoint = OffsetF((maxSize.Width() - childSize.Width()) / 2.0, 0.0);
                break;
            case DialogAlignment::CENTER:
                topLeftPoint =
                    OffsetF(maxSize.Width() - childSize.Width(), maxSize.Height() - childSize.Height()) / 2.0;
                break;
            case DialogAlignment::BOTTOM:
                topLeftPoint =
                    OffsetF((maxSize.Width() - childSize.Width()) / 2.0, maxSize.Height() - childSize.Height());
                break;
            case DialogAlignment::TOP_START:
                topLeftPoint = OffsetF(0.0, 0.0);
                break;
            case DialogAlignment::TOP_END:
                topLeftPoint = OffsetF(maxSize.Width() - childSize.Width(), 0.0);
                break;
            case DialogAlignment::CENTER_START:
                topLeftPoint = OffsetF(0.0, maxSize.Height() - childSize.Height()) / 2.0;
                break;
            case DialogAlignment::CENTER_END:
                topLeftPoint =
                    OffsetF(maxSize.Width() - childSize.Width(), (maxSize.Height() - childSize.Height()) / 2.0);
                break;
            case DialogAlignment::BOTTOM_START:
                topLeftPoint = OffsetF(0.0, maxSize.Height() - childSize.Height());
                break;
            case DialogAlignment::BOTTOM_END:
                topLeftPoint = OffsetF(maxSize.Width() - childSize.Width(), maxSize.Height() - childSize.Height());
                break;
            default:
                topLeftPoint =
                    OffsetF(maxSize.Width() - childSize.Width(), maxSize.Height() - childSize.Height()) / 2.0;
                break;
        }
        return true;
    }
    return false;
}

void DialogLayoutAlgorithm::UpdateTouchRegion()
{
    // TODO: update touch region is not completed.
}

} // namespace OHOS::Ace::NG
