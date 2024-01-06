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
#include "core/common/ace_engine.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/common/container.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/common/properties/placement.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/dialog/dialog_layout_property.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_algorithm.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/render/paragraph.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline/pipeline_base.h"
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
constexpr Dimension FULLSCREEN = 100.0_pct;
constexpr Dimension MULTIPLE_DIALOG_OFFSET_X = 48.0_vp;
constexpr Dimension MULTIPLE_DIALOG_OFFSET_Y = 48.0_vp;
constexpr Dimension SUBWINDOW_DIALOG_DEFAULT_WIDTH = 400.0_vp;
constexpr double EXPAND_DISPLAY_WINDOW_HEIGHT_RATIO = 0.67;
constexpr double EXPAND_DISPLAY_DIALOG_HEIGHT_RATIO = 0.9;
} // namespace

void DialogLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(dialogTheme);
    expandDisplay_ = dialogTheme->GetExpandDisplay();
    auto dialogProp = AceType::DynamicCast<DialogLayoutProperty>(layoutWrapper->GetLayoutProperty());
    customSize_ = dialogProp->GetUseCustomStyle().value_or(false);
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

    // constraint child size unless developer is using customStyle
    if (!customSize_) {
        auto inset = pipeline->GetSafeArea();
        auto maxSize = layoutConstraint->maxSize;
        maxSize.MinusPadding(0, 0, inset.top_.Length(), 0);
        childLayoutConstraint.UpdateMaxSizeWithCheck(maxSize);
        ComputeInnerLayoutParam(childLayoutConstraint);
    }
    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.empty()) {
        return;
    }
    auto child = children.front();
    // childSize_ and childOffset_ is used in Layout.
    child->Measure(childLayoutConstraint);

    if (!layoutWrapper->GetHostNode()->GetPattern<DialogPattern>()->GetCustomNode()) {
        AnalysisHeightOfChild(layoutWrapper);
    }
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

    if (scroll != nullptr) {
        AnalysisLayoutOfContent(layoutWrapper, scroll);
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

void DialogLayoutAlgorithm::AnalysisLayoutOfContent(LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& scroll)
{
    auto text = scroll->GetAllChildrenWithBuild().front();
    CHECK_NULL_VOID(text);
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(text->GetLayoutProperty());
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateWordBreak(WordBreak::BREAK_ALL);
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(text->GetLayoutAlgorithm());
    CHECK_NULL_VOID(layoutAlgorithmWrapper);
    auto textLayoutAlgorithm = DynamicCast<TextLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(textLayoutAlgorithm);
    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(hostNode);
    auto dialogPattern = hostNode->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(dialogPattern);
    if (dialogPattern->GetTitle().empty() && dialogPattern->GetSubtitle().empty()) {
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) &&
            GreatNotEqual(textLayoutAlgorithm->GetLineCount(), 1)) {
            scroll->GetLayoutProperty()->UpdateAlignment(Alignment::CENTER_LEFT);
        } else {
            scroll->GetLayoutProperty()->UpdateAlignment(Alignment::CENTER);
        }
    } else {
        scroll->GetLayoutProperty()->UpdateAlignment(Alignment::CENTER_LEFT);
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
    LayoutWrapper* layoutWrapper, float height, float width)
{
    auto childConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childConstraint.minSize.SetHeight(height);
    childConstraint.maxSize.SetHeight(height);
    childConstraint.percentReference.SetHeight(height);
    childConstraint.minSize.SetWidth(width);
    childConstraint.maxSize.SetWidth(width);
    childConstraint.percentReference.SetWidth(width);
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
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) && expandDisplay_) {
        auto maxHeight = SystemProperties::GetDevicePhysicalHeight() *
            EXPAND_DISPLAY_WINDOW_HEIGHT_RATIO * EXPAND_DISPLAY_DIALOG_HEIGHT_RATIO;
        innerLayout.minSize = SizeF(SUBWINDOW_DIALOG_DEFAULT_WIDTH.ConvertToPx(), 0.0);
        innerLayout.maxSize = SizeF(SUBWINDOW_DIALOG_DEFAULT_WIDTH.ConvertToPx(), maxHeight);
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
            deviceColumns = 4;
        }
    }
    return info->GetWidth(std::min(deviceColumns, parentColumns));
}

void DialogLayoutAlgorithm::ProcessMaskRect(std::optional<DimensionRect> maskRect, const RefPtr<FrameNode>& dialog)
{
    auto dialogContext = dialog->GetRenderContext();
    CHECK_NULL_VOID(dialogContext);
    auto hub = dialog->GetEventHub<DialogEventHub>();
    auto width = maskRect->GetWidth();
    auto height = maskRect->GetHeight();
    auto offset = maskRect->GetOffset();
    if (width.IsNegative()) {
        width = FULLSCREEN;
    }
    if (height.IsNegative()) {
        height = FULLSCREEN;
    }
    auto rootWidth = PipelineContext::GetCurrentRootWidth();
    auto rootHeight = PipelineContext::GetCurrentRootHeight();
    RectF rect = RectF(offset.GetX().ConvertToPxWithSize(rootWidth), offset.GetY().ConvertToPxWithSize(rootHeight),
        width.ConvertToPxWithSize(rootWidth), height.ConvertToPxWithSize(rootHeight));
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    std::vector<DimensionRect> mouseResponseRegion;
    mouseResponseRegion.emplace_back(width, height, offset);
    gestureHub->SetMouseResponseRegion(mouseResponseRegion);
    gestureHub->SetResponseRegion(mouseResponseRegion);
}

void DialogLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    subWindowId_ = SubwindowManager::GetInstance()->GetDialogSubWindowId();
    CHECK_NULL_VOID(layoutWrapper);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto dialogProp = DynamicCast<DialogLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(dialogProp);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto dialogTheme = pipelineContext->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(dialogTheme);
    auto selfSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.empty()) {
        return;
    }
    auto dialogPattern = frameNode->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(dialogPattern);
    if (dialogPattern->GetDialogProperties().maskRect.has_value()) {
        ProcessMaskRect(dialogPattern->GetDialogProperties().maskRect, frameNode);
    }
    auto child = children.front();
    auto childSize = child->GetGeometryNode()->GetMarginFrameSize();
    // is PcDevice MultipleDialog Offset to the bottom right
    if (dialogTheme->GetMultipleDialogDisplay() != "stack" && !dialogProp->GetIsModal().value_or(true) &&
        dialogProp->GetShowInSubWindowValue(false)) {
        auto subWindow = SubwindowManager::GetInstance()->GetSubwindow(subWindowId_);
        CHECK_NULL_VOID(subWindow);
        auto subOverlayManager = subWindow->GetOverlayManager();
        CHECK_NULL_VOID(subOverlayManager);
        MultipleDialog(dialogProp, childSize, selfSize, subOverlayManager);
    }
    dialogOffset_ = dialogProp->GetDialogOffset().value_or(DimensionOffset());
    alignment_ = dialogProp->GetDialogAlignment().value_or(DialogAlignment::DEFAULT);
    topLeftPoint_ = ComputeChildPosition(childSize, dialogProp, selfSize);
    if (!dialogProp->GetIsModal().value_or(true) ||
        (dialogProp->GetIsModal().value_or(true) && dialogProp->GetShowInSubWindowValue(false))) {
        ProcessMaskRect(
            DimensionRect(Dimension(childSize.Width()), Dimension(childSize.Height()), DimensionOffset(topLeftPoint_)),
            frameNode);
    }
    child->GetGeometryNode()->SetMarginFrameOffset(topLeftPoint_);
    child->Layout();
    if (dialogProp->GetShowInSubWindowValue(false)) {
        std::vector<Rect> rects;
        auto rect = Rect(topLeftPoint_.GetX(), topLeftPoint_.GetY(), childSize.Width(), childSize.Height());
        rects.emplace_back(rect);
        SubwindowManager::GetInstance()->SetDialogHotAreas(rects, frameNode->GetId(), subWindowId_);
    }
}

bool DialogLayoutAlgorithm::IsDialogTouchingBoundary(OffsetF topLeftPoint, SizeF childSize, SizeF selfSize)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto safeAreaInsets = pipelineContext->GetSafeArea();
    float bottomSecurity = static_cast<float>(PORTRAIT_BOTTOM_SECURITY.ConvertToPx());
    auto height = safeAreaInsets.bottom_.start == 0 ? selfSize.Height() - bottomSecurity : safeAreaInsets.bottom_.start;
    auto width = selfSize.Width();
    if (topLeftPoint.GetY() + childSize.Height() >= height) {
        touchingBoundaryFlag_ = TouchingBoundaryType::TouchBottomBoundary;
    } else if (topLeftPoint.GetX() + childSize.Width() >= width) {
        touchingBoundaryFlag_ = TouchingBoundaryType::TouchRightBoundary;
    } else {
        touchingBoundaryFlag_ = TouchingBoundaryType::NotTouchBoundary;
        return false;
    }
    return true;
}

void DialogLayoutAlgorithm::MultipleDialog(const RefPtr<DialogLayoutProperty>& dialogProp, const SizeF& childSize,
    const SizeF& selfSize, const RefPtr<OverlayManager> subOverlayManager)
{
    std::map<int32_t, RefPtr<FrameNode>> DialogMap(
        subOverlayManager->GetDialogMap().begin(), subOverlayManager->GetDialogMap().end());
    int dialogMapSize = static_cast<int>(DialogMap.size());
    if (dialogMapSize > 1) {
        auto it = DialogMap.begin();
        for (int i = 1; i < dialogMapSize - 1; i++) {
            it++;
        }
        auto predialogProp = DynamicCast<DialogLayoutProperty>(it->second->GetLayoutProperty());
        auto firstdialogProp = DynamicCast<DialogLayoutProperty>(DialogMap.begin()->second->GetLayoutProperty());
        dialogProp->UpdateDialogOffset(predialogProp->GetDialogOffset().value_or(DimensionOffset()) +
                                       DimensionOffset(MULTIPLE_DIALOG_OFFSET_X, MULTIPLE_DIALOG_OFFSET_Y));
        dialogOffset_ = dialogProp->GetDialogOffset().value_or(DimensionOffset());
        alignment_ = dialogProp->GetDialogAlignment().value_or(DialogAlignment::DEFAULT);
        topLeftPoint_ = ComputeChildPosition(childSize, dialogProp, selfSize);
        if (IsDialogTouchingBoundary(topLeftPoint_, childSize, selfSize)) {
            if (touchingBoundaryFlag_ == TouchingBoundaryType::TouchBottomBoundary) {
                dialogProp->UpdateDialogOffset(
                    DimensionOffset(predialogProp->GetDialogOffset().value_or(DimensionOffset()).GetX(),
                        firstdialogProp->GetDialogOffset().value_or(DimensionOffset()).GetY()));
            } else if (touchingBoundaryFlag_ == TouchingBoundaryType::TouchRightBoundary) {
                dialogProp->UpdateDialogOffset(firstdialogProp->GetDialogOffset().value_or(DimensionOffset()));
            }
        }
    }
}

OffsetF DialogLayoutAlgorithm::ComputeChildPosition(
    const SizeF& childSize, const RefPtr<DialogLayoutProperty>& prop, const SizeF& selfSize)
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
    if (!SetAlignmentSwitch(layoutConstraint->maxSize, childSize, topLeftPoint)) {
        topLeftPoint = OffsetF(layoutConstraint->maxSize.Width() - childSize.Width(),
                           layoutConstraint->maxSize.Height() - childSize.Height()) /
                       2.0;
    }
    const auto& expandSafeAreaOpts = prop->GetSafeAreaExpandOpts();
    bool needAvoidKeyboard = true;
    if (expandSafeAreaOpts && (expandSafeAreaOpts->type | SAFE_AREA_TYPE_KEYBOARD)) {
        needAvoidKeyboard = false;
    }
    return AdjustChildPosition(topLeftPoint, dialogOffset, childSize, needAvoidKeyboard);
}

bool DialogLayoutAlgorithm::SetAlignmentSwitch(const SizeF& maxSize, const SizeF& childSize, OffsetF& topLeftPoint)
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

    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto displayInfo = container->GetDisplayInfo();
    CHECK_NULL_RETURN(displayInfo, false);
    auto foldStatus = displayInfo->GetFoldStatus();
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) && foldStatus == FoldStatus::EXPAND) {
        topLeftPoint = OffsetF(maxSize.Width() - childSize.Width(), maxSize.Height() - childSize.Height()) / 2.0;
        return true;
    }

    bool version10OrLarger = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN);
    if (version10OrLarger && SystemProperties::GetDeviceType() == DeviceType::PHONE) {
        if (SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE) {
            topLeftPoint = OffsetF(maxSize.Width() - childSize.Width(), maxSize.Height() - childSize.Height()) / 2.0;
            return true;
        }
        if (SystemProperties::GetDeviceOrientation() == DeviceOrientation::PORTRAIT) {
            topLeftPoint = OffsetF((maxSize.Width() - childSize.Width()) / 2.0,
                maxSize.Height() - childSize.Height() - GetPaddingBottom());
            return true;
        }
    }
    return false;
}

void DialogLayoutAlgorithm::UpdateTouchRegion()
{
    // TODO: update touch region is not completed.
}

double DialogLayoutAlgorithm::GetPaddingBottom() const
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, 0);
    auto dialogTheme = pipelineContext->GetTheme<DialogTheme>();
    CHECK_NULL_RETURN(dialogTheme, 0);
    auto bottom = dialogTheme->GetDefaultDialogMarginBottom();
    return pipelineContext->NormalizeToPx(bottom);
}

OffsetF DialogLayoutAlgorithm::AdjustChildPosition(
    OffsetF& topLeftPoint, const OffsetF& dialogOffset, const SizeF& childSize, bool needAvoidKeyboard) const
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, topLeftPoint + dialogOffset);
    auto systemInset = pipelineContext->GetSafeArea();
    if (!customSize_ && topLeftPoint.GetY() < systemInset.top_.end) {
        topLeftPoint.SetY(systemInset.top_.end);
    }
    auto childOffset = topLeftPoint + dialogOffset;

    auto manager = pipelineContext->GetSafeAreaManager();
    auto keyboardInsert = manager->GetKeyboardInset();
    auto childBottom = childOffset.GetY() + childSize.Height();
    auto paddingBottom = static_cast<float>(GetPaddingBottom());
    if (needAvoidKeyboard && keyboardInsert.Length() > 0 && childBottom > (keyboardInsert.start - paddingBottom)) {
        childOffset.SetY(childOffset.GetY() - (childBottom - (keyboardInsert.start - paddingBottom)));
    }
    return childOffset;
}
} // namespace OHOS::Ace::NG
