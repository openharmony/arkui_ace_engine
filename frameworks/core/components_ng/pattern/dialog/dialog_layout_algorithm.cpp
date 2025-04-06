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

#include "base/subwindow/subwindow_manager.h"
#include "core/common/ace_engine.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/text/text_layout_algorithm.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {

// Using UX spec: Constrain max height within 4/5 of screen height.
constexpr double DIALOG_HEIGHT_RATIO = 0.8;
constexpr double DIALOG_HEIGHT_RATIO_FOR_LANDSCAPE = 0.9;
constexpr double DIALOG_HEIGHT_RATIO_FOR_CAR = 0.95;
constexpr Dimension DIALOG_MIN_HEIGHT = 70.0_vp;
constexpr Dimension FULLSCREEN = 100.0_pct;
constexpr Dimension MULTIPLE_DIALOG_OFFSET_X = 48.0_vp;
constexpr Dimension MULTIPLE_DIALOG_OFFSET_Y = 48.0_vp;
constexpr Dimension SUBWINDOW_DIALOG_DEFAULT_WIDTH = 400.0_vp;
constexpr Dimension AVOID_LIMIT_PADDING = 8.0_vp;
constexpr double EXPAND_DISPLAY_WINDOW_HEIGHT_RATIO = 0.67;
constexpr double EXPAND_DISPLAY_DIALOG_HEIGHT_RATIO = 0.9;
constexpr double HALF = 2.0;
constexpr double LANDSCAPE_DIALOG_WIDTH_RATIO = 0.75;
constexpr Dimension SCROLL_MIN_HEIGHT_SUITOLD = 100.0_vp;
constexpr int32_t TEXT_ALIGN_CONTENT_CENTER = 1;
constexpr int32_t EXTRA_MASK_NODE_INDEX = 1;
} // namespace

void DialogLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(dialogTheme);
    auto dialogProp = AceType::DynamicCast<DialogLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(dialogProp);
    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(hostNode);
    auto dialogPattern = hostNode->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(dialogPattern);
    auto parent = hostNode->GetParent();
    expandDisplay_ = dialogTheme->GetExpandDisplay() || dialogPattern->IsShowInFreeMultiWindow();
    keyboardAvoidMode_ = dialogPattern->GetDialogProperties().keyboardAvoidMode;
    keyboardAvoidDistance_ = dialogPattern->GetDialogProperties().keyboardAvoidDistance;
    isUIExtensionSubWindow_ = dialogPattern->IsUIExtensionSubWindow();
    hostWindowRect_ = dialogPattern->GetHostWindowRect();
    customSize_ = dialogProp->GetUseCustomStyle().value_or(false);
    gridCount_ = dialogProp->GetGridCount().value_or(-1);
    isShowInSubWindow_ = dialogProp->GetShowInSubWindowValue(false);
    isModal_ = dialogProp->GetIsModal().value_or(true);
    hasAddMaskNode_ = (dialogPattern->GetDialogProperties().maskTransitionEffect != nullptr ||
                       dialogPattern->GetDialogProperties().dialogTransitionEffect != nullptr) &&
                       isModal_ && !isShowInSubWindow_;
    auto enableHoverMode = dialogProp->GetEnableHoverMode().value_or(false);
    hoverModeArea_ = dialogProp->GetHoverModeArea().value_or(HoverModeAreaType::BOTTOM_SCREEN);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    auto keyboardInsert = safeAreaManager->GetKeyboardInset();
    isKeyBoardShow_ = keyboardInsert.IsValid();
    isHoverMode_ = enableHoverMode ? pipeline->IsHalfFoldHoverStatus() : false;
    if (dialogPattern->IsWaterfallWindowMode()) {
        TAG_LOGI(AceLogTag::ACE_DIALOG, "enableHoverMode for waterfallMode, isShowInSubWindow: %{public}d",
            isShowInSubWindow_);
        isHoverMode_ = true;
        hoverModeArea_ = HoverModeAreaType::TOP_SCREEN;
    }

    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_VOID(windowManager);
    dialogPattern->UpdateFontScale();
    isSuitOldMeasure_ = dialogPattern->GetIsSuitOldMeasure();
    auto dialogContext = dialogPattern->GetContext();
    CHECK_NULL_VOID(dialogContext);
    isSuitableForElderly_ = (dialogPattern->GetIsSuitableForAging() || dialogPattern->GetCustomNode()) &&
                            windowManager->GetWindowMode() != WindowMode::WINDOW_MODE_FLOATING &&
                            GreatOrEqual(dialogContext->GetFontScale(), 1.75f);
    auto isPickerDialog = dialogPattern->GetIsPickerDialog();
    if (isPickerDialog || customSize_) {
        isSuitableForElderly_ = false;
    }
    if (isSuitableForElderly_ || GreatOrEqual(dialogContext->GetFontScale(), 1.75f)) {
        dialogPattern->UpdateDeviceOrientation(SystemProperties::GetDeviceOrientation());
    }
    UpdateSafeArea(hostNode);
    isShowInFloatingWindow_ = dialogPattern->IsShowInFloatingWindow();
    ResizeDialogSubwindow(dialogPattern->IsShowInFreeMultiWindow(), isShowInSubWindow_, isShowInFloatingWindow_);
    const auto& layoutConstraint = dialogProp->GetLayoutConstraint();
    const auto& parentIdealSize = layoutConstraint->parentIdealSize;
    OptionalSizeF realSize;
    // dialog size fit screen.
    realSize.UpdateIllegalSizeWithCheck(parentIdealSize);
    embeddedDialogOffsetY_ = 0.0f;
    stackRootDialogOffsetY_ = 0.0f;
    if (IsEmbeddedDialog(hostNode)) {
        if (!realSize.IsValid()) {
            realSize.UpdateIllegalSizeWithCheck(layoutConstraint->maxSize);
        }
        if (dialogPattern->GetDialogProperties().dialogImmersiveMode == ImmersiveMode::EXTEND) {
            SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_SYSTEM,
                .edges = SAFE_AREA_EDGE_TOP | SAFE_AREA_EDGE_BOTTOM };
            dialogProp->UpdateSafeAreaExpandOpts(opts);
        }
        embeddedDialogOffsetY_ = GetEmbeddedDialogOffsetY(hostNode);
    } else {
        stackRootDialogOffsetY_ = GetStackRootDialogOffsetY(hostNode);
    }
    layoutWrapper->GetGeometryNode()->SetFrameSize(realSize.ConvertToSizeT());
    layoutWrapper->GetGeometryNode()->SetContentSize(realSize.ConvertToSizeT());
    // update child layout constraint
    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.empty()) {
        return;
    }
    auto child = children.front();
    // constraint child size unless developer is using customStyle
    if (!customSize_) {
        auto maxSize = layoutConstraint->maxSize;
        if (isSuitOldMeasure_) {
            maxSize.SetWidth(pipeline->GetRootWidth());
            maxSize.SetHeight(pipeline->GetRootHeight());
        }
        UpdateChildMaxSizeHeight(maxSize);
        childLayoutConstraint.UpdateMaxSizeWithCheck(maxSize);
        ComputeInnerLayoutParam(childLayoutConstraint, dialogProp);
        UpdateChildLayoutConstraint(dialogProp, childLayoutConstraint, child);
    }

    if (isSuitableForElderly_ && SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE) {
        childLayoutConstraint.maxSize.SetWidth(LANDSCAPE_DIALOG_WIDTH_RATIO * pipeline->GetRootWidth());
    }
    // childSize_ and childOffset_ is used in Layout.
    child->Measure(childLayoutConstraint);
    if (!layoutWrapper->GetHostNode()->GetPattern<DialogPattern>()->GetCustomNode()) {
        if (isSuitOldMeasure_) {
            dialogMaxHeight_ = childLayoutConstraint.maxSize.Height();
        }
        AnalysisHeightOfChild(layoutWrapper);
    }
}

void DialogLayoutAlgorithm::ResizeDialogSubwindow(
    bool expandDisplay, bool isShowInSubWindow, bool isShowInFloatingWindow)
{
    if (expandDisplay && isShowInSubWindow && isShowInFloatingWindow) {
        auto currentId = Container::CurrentId();
        auto subWindow = SubwindowManager::GetInstance()->GetSubwindowByType(currentId, SubwindowType::TYPE_DIALOG);
        CHECK_NULL_VOID(subWindow);
        subWindow->ResizeDialogSubwindow();
    }
}

void DialogLayoutAlgorithm::UpdateChildMaxSizeHeight(SizeT<float>& maxSize)
{
    if (!isHoverMode_) {
        maxSize.MinusPadding(0, 0, safeAreaInsets_.top_.Length(), 0);
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE) && LessNotEqual(gridCount_, 0)) {
            maxSize.MinusPadding(0, 0, 0, safeAreaInsets_.bottom_.Length());
        }
        return;
    }
    alignBottomScreen_ = !isKeyBoardShow_ && hoverModeArea_ == HoverModeAreaType::BOTTOM_SCREEN;
    if (alignBottomScreen_) {
        maxSize.MinusPadding(0, 0, foldCreaseRect.Bottom(), safeAreaInsets_.bottom_.Length());
        return;
    }
    maxSize.SetHeight(foldCreaseRect.Top() - safeAreaInsets_.top_.Length());
}

void DialogLayoutAlgorithm::UpdateChildLayoutConstraint(const RefPtr<DialogLayoutProperty>& dialogProp,
    LayoutConstraintF& childLayoutConstraint, RefPtr<LayoutWrapper>& childLayoutWrapper)
{
    auto childLayoutProperty = childLayoutWrapper->GetLayoutProperty();
    auto dialogWidth = dialogProp->GetWidth().value_or(Dimension(-1, DimensionUnit::VP));
    auto dialogHeight = dialogProp->GetHeight().value_or(Dimension(-1, DimensionUnit::VP));
    if (NonNegative(dialogHeight.Value())) {
        childLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(dialogHeight)));
    }
    if (NonNegative(dialogWidth.Value())) {
        childLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(dialogWidth), std::nullopt));
    }
    childLayoutConstraint.UpdateMaxSizeWithCheck(SizeF(
        dialogWidth.ConvertToPxWithSize(childLayoutConstraint.maxSize.Width()),
        dialogHeight.ConvertToPxWithSize(childLayoutConstraint.maxSize.Height())));
}

void DialogLayoutAlgorithm::AnalysisHeightOfChild(LayoutWrapper* layoutWrapper)
{
    float scrollHeight = 0.0f;
    float listHeight = 0.0f;
    float restHeight = 0.0f;
    float restWidth = 0.0f;
    RefPtr<LayoutWrapper> scroll;
    RefPtr<LayoutWrapper> list;
    auto child = layoutWrapper->GetAllChildrenWithBuild().front();
    CHECK_NULL_VOID(child);
    restWidth = child->GetLayoutProperty()->GetContentLayoutConstraint()->maxSize.Width();
    restHeight = child->GetLayoutProperty()->GetContentLayoutConstraint()->maxSize.Height();
    for (const auto& grandson : child->GetAllChildrenWithBuild()) {
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

    if (scroll != nullptr) {
        AnalysisLayoutOfContent(layoutWrapper, scroll);
    }

    if (scroll != nullptr && list != nullptr) {
        Distribute(scrollHeight, listHeight, restHeight);
        auto childConstraint = CreateDialogChildConstraint(layoutWrapper, scrollHeight, restWidth);
        scroll->Measure(childConstraint);
        childConstraint = CreateDialogChildConstraint(layoutWrapper, listHeight, restWidth);
        list->Measure(childConstraint);
    } else {
        if (scroll != nullptr) {
            auto childConstraint =
                CreateDialogChildConstraint(layoutWrapper, std::min(restHeight, scrollHeight), restWidth);
            UpdateIsScrollHeightNegative(layoutWrapper, std::min(restHeight, scrollHeight));
            scroll->Measure(childConstraint);
        }
        if (list != nullptr) {
            auto childConstraint =
                CreateDialogChildConstraint(layoutWrapper, std::min(restHeight, listHeight), restWidth);
            list->Measure(childConstraint);
        }
    }
}

void DialogLayoutAlgorithm::AnalysisLayoutOfContent(LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& scroll)
{
    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(hostNode);
    auto dialogPattern = hostNode->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(dialogPattern);
    auto text = scroll->GetAllChildrenWithBuild().front();
    CHECK_NULL_VOID(text);
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(text->GetLayoutProperty());
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateWordBreak(dialogPattern->GetDialogProperties().wordBreak);
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(text->GetLayoutAlgorithm());
    CHECK_NULL_VOID(layoutAlgorithmWrapper);
    auto textLayoutAlgorithm = DynamicCast<TextLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(textLayoutAlgorithm);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto dialogTheme = pipelineContext->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(dialogTheme);
    auto scrollPropery = scroll->GetLayoutProperty();
    CHECK_NULL_VOID(scrollPropery);
    if ((dialogPattern->GetTitle().empty() && dialogPattern->GetSubtitle().empty()) ||
        dialogTheme->GetTextAlignContent() == TEXT_ALIGN_CONTENT_CENTER) {
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) &&
            GreatNotEqual(textLayoutAlgorithm->GetLineCount(), 1)) {
            scrollPropery->UpdateAlignment(Alignment::CENTER_LEFT);
        } else {
            scrollPropery->UpdateAlignment(Alignment::CENTER);
        }
    } else {
        scrollPropery->UpdateAlignment(Alignment::CENTER_LEFT);
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

bool DialogLayoutAlgorithm::ComputeInnerLayoutSizeParam(LayoutConstraintF& innerLayout,
    const RefPtr<DialogLayoutProperty>& dialogProp)
{
    // when width is valid, gridCount_ is -1
    if (GreatOrEqual(gridCount_, 0)) {
        return false;
    }
    CHECK_NULL_RETURN(Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE), false);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_RETURN(dialogTheme, false);

    auto maxSize = innerLayout.maxSize;
    auto width =
        maxSize.Width() - dialogTheme->GetMarginLeft().ConvertToPx() - dialogTheme->GetMarginRight().ConvertToPx();
    auto defaultMaxWidth = dialogTheme->GetContainerMaxWidth().ConvertToPx();
    width = defaultMaxWidth < width ? defaultMaxWidth : width;
    if (dialogProp->GetWidth().has_value()) {
        auto dialogWidth = dialogProp->GetWidth().value_or(Dimension(-1, DimensionUnit::VP));
        auto widthVal = dialogWidth.Unit() == DimensionUnit::PERCENT ? maxSize.Width() : dialogWidth.ConvertToPx();
        if (Positive(widthVal)) {
            width = widthVal;
        }
    }

    auto defaultMinHeight = DIALOG_MIN_HEIGHT.ConvertToPx();
    auto defaultMaxHeight = IsGetExpandDisplayValidHeight() ? expandDisplayValidHeight_ : maxSize.Height();
    innerLayout.minSize = SizeF(width, defaultMinHeight);
    double ratioHeight = dialogTheme->GetDialogRatioHeight();
    innerLayout.maxSize = SizeF(width, defaultMaxHeight * ratioHeight);

    if (dialogProp->GetHeight().has_value()) {
        auto dialogHeight = dialogProp->GetHeight().value_or(Dimension(-1, DimensionUnit::VP));
        // covert user input height to px
        auto realHeight = dialogHeight.Unit() == DimensionUnit::PERCENT ?
            dialogHeight.ConvertToPxWithSize(defaultMaxHeight) : dialogHeight.ConvertToPx();
        // percent and abs height default max value
        auto height = dialogHeight.Unit() == DimensionUnit::PERCENT ? defaultMaxHeight : realHeight;
        // abnormal height proc
        if (NonPositive(realHeight)) {
            height = defaultMaxHeight * ratioHeight;
        }
        innerLayout.minSize = SizeF(width, 0.0);
        innerLayout.maxSize = SizeF(width, height);
    }
    if (isSuitableForElderly_) {
        if (SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE) {
            innerLayout.minSize = SizeF(width, 0.0);
            innerLayout.maxSize.SetWidth(pipeline->GetRootWidth() * LANDSCAPE_DIALOG_WIDTH_RATIO);
        }
    }
    // update percentRef
    innerLayout.percentReference = innerLayout.maxSize;
    return true;
}

bool DialogLayoutAlgorithm::IsGetExpandDisplayValidHeight()
{
    CHECK_NULL_RETURN(expandDisplay_ && isShowInSubWindow_, false);
    auto pipelineContext = GetCurrentPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto expandDisplayValidHeight = pipelineContext->GetDisplayAvailableRect().Height();
    if (Positive(expandDisplayValidHeight)) {
        expandDisplayValidHeight_ = expandDisplayValidHeight;
        return true;
    }
    return false;
}

RefPtr<PipelineContext> DialogLayoutAlgorithm::GetCurrentPipelineContext()
{
    auto containerId = Container::CurrentId();
    RefPtr<PipelineContext> context;
    if (containerId >= MIN_SUBCONTAINER_ID) {
        auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(containerId);
        auto parentContainer = AceEngine::Get().GetContainer(parentContainerId);
        CHECK_NULL_RETURN(parentContainer, nullptr);
        context = DynamicCast<PipelineContext>(parentContainer->GetPipelineContext());
    } else {
        context = PipelineContext::GetCurrentContext();
    }
    return context;
}

void DialogLayoutAlgorithm::ComputeInnerLayoutParam(LayoutConstraintF& innerLayout,
    const RefPtr<DialogLayoutProperty>& dialogProp)
{
    CHECK_EQUAL_VOID(ComputeInnerLayoutSizeParam(innerLayout, dialogProp), true);
    auto maxSize = innerLayout.maxSize;
    // Set different layout param for different devices
    // need to use theme json to replace this function.
    // get grid size type based on the screen where the dialog locate
    auto gridSizeType = ScreenSystemManager::GetInstance().GetSize(maxSize.Width());
    RefPtr<GridColumnInfo> columnInfo;
    if (SystemProperties::GetDeviceType() == DeviceType::CAR) {
        columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::CAR_DIALOG);
    } else {
        columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::DIALOG);
    }
    columnInfo->GetParent()->BuildColumnWidth(maxSize.Width());
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto width = GetMaxWidthBasedOnGridType(columnInfo, gridSizeType, SystemProperties::GetDeviceType());
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        width =
            SUBWINDOW_DIALOG_DEFAULT_WIDTH.ConvertToPx() < width ? SUBWINDOW_DIALOG_DEFAULT_WIDTH.ConvertToPx() : width;
    }
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
    if (isSuitableForElderly_) {
        if (SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE) {
            innerLayout.minSize = SizeF(width, 0.0);
            innerLayout.maxSize.SetWidth(pipelineContext->GetRootWidth() * LANDSCAPE_DIALOG_WIDTH_RATIO);
        }
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

    return info->GetWidth(std::min(GetDeviceColumns(type, deviceType), parentColumns));
}

int32_t DialogLayoutAlgorithm::GetDeviceColumns(GridSizeType type, DeviceType deviceType)
{
    int32_t deviceColumns;
    if (deviceType == DeviceType::WATCH) {
        if (type == GridSizeType::SM) {
            deviceColumns = 3; // 3: the number of deviceColumns
        } else if (type == GridSizeType::MD) {
            deviceColumns = 4; // 4: the number of deviceColumns
        } else {
            deviceColumns = 5; // 5: the number of deviceColumns
        }
    } else if (deviceType == DeviceType::PHONE) {
        if (type == GridSizeType::SM) {
            deviceColumns = 4; // 4: the number of deviceColumns
        } else if (type == GridSizeType::MD) {
            deviceColumns = 5; // 5: the number of deviceColumns
        } else {
            deviceColumns = 6; // 6: the number of deviceColumns
        }
    } else if (deviceType == DeviceType::CAR) {
        if (type == GridSizeType::SM) {
            deviceColumns = 4; // 4: the number of deviceColumns
        } else if (type == GridSizeType::MD) {
            deviceColumns = 6; // 6: the number of deviceColumns
        } else {
            deviceColumns = 8; // 8: the number of deviceColumns
        }
    } else if (deviceType == DeviceType::TABLET && type == GridSizeType::MD &&
               Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        deviceColumns = 5; // 5: the number of deviceColumns
    } else {
        if (type == GridSizeType::SM) {
            deviceColumns = 2;
        } else if (type == GridSizeType::MD) {
            deviceColumns = 3;
        } else {
            deviceColumns = 4;
        }
    }
    return deviceColumns;
}

void DialogLayoutAlgorithm::ClipCustomMaskNode(const RefPtr<FrameNode>& dialog, const RectF& rect)
{
    auto maskNode = AceType::DynamicCast<FrameNode>(dialog->GetChildByIndex(1));
    CHECK_NULL_VOID(maskNode);
    auto ctx = maskNode->GetRenderContext();
    CHECK_NULL_VOID(ctx);
    ctx->ClipWithRect(rect);
    ctx->UpdateClipEdge(true);
}

void DialogLayoutAlgorithm::ProcessMaskRect(
    std::optional<DimensionRect> maskRect, const RefPtr<FrameNode>& dialog, bool isMask)
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
    auto isMaskFullScreen =
        rect == RectF(0.0, 0.0, PipelineContext::GetCurrentRootWidth(), PipelineContext::GetCurrentRootHeight());
    auto clipMask = isModal_ && isMask && !isMaskFullScreen;
    if (!isShowInSubWindow_ && clipMask) {
        if (hasAddMaskNode_) {
            ClipCustomMaskNode(dialog, rect);
        } else {
            dialogContext->ClipWithRect(rect);
            dialogContext->UpdateClipEdge(true);
        }
    }
    if (isUIExtensionSubWindow_ && isModal_) {
        ClipUIExtensionSubWindowContent(dialog);
    }
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    std::vector<DimensionRect> mouseResponseRegion;
    mouseResponseRegion.emplace_back(width, height, offset);
    gestureHub->SetMouseResponseRegion(mouseResponseRegion);
    gestureHub->SetResponseRegion(mouseResponseRegion);
}

std::optional<DimensionRect> DialogLayoutAlgorithm::GetMaskRect(const RefPtr<FrameNode>& dialog)
{
    std::optional<DimensionRect> maskRect;
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    CHECK_NULL_RETURN(dialogPattern, maskRect);
    maskRect = dialogPattern->GetDialogProperties().maskRect;
    if (!isUIExtensionSubWindow_) {
        return maskRect;
    }

    if (expandDisplay_ && hostWindowRect_.GetSize().IsPositive()) {
        auto offset = DimensionOffset(Dimension(hostWindowRect_.GetX()), Dimension(hostWindowRect_.GetY()));
        maskRect = DimensionRect(Dimension(hostWindowRect_.Width()), Dimension(hostWindowRect_.Height()), offset);
    } else {
        maskRect = DimensionRect(CalcDimension(1, DimensionUnit::PERCENT), CalcDimension(1, DimensionUnit::PERCENT),
            DimensionOffset(CalcDimension(0, DimensionUnit::VP), CalcDimension(0, DimensionUnit::VP)));
    }
    return maskRect;
}

void DialogLayoutAlgorithm::UpdateCustomMaskNodeLayout(const RefPtr<FrameNode>& dialog)
{
    auto maskNodePtr = dialog->GetChildByIndex(1);
    CHECK_NULL_VOID(maskNodePtr);
    auto maskNode = AceType::DynamicCast<FrameNode>(maskNodePtr);
    CHECK_NULL_VOID(maskNode);
    auto maskNodeLayoutProp = maskNode->GetLayoutProperty();
    CHECK_NULL_VOID(maskNodeLayoutProp);
    auto maskGeometryNode = maskNode->GetGeometryNode();
    CHECK_NULL_VOID(maskGeometryNode);
    maskNodeLayoutProp->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(1.0, DimensionUnit::PERCENT)));
    maskGeometryNode->SetFrameOffset(OffsetF(0, 0));
    maskNode->Measure(dialog->GetLayoutConstraint());
    maskNode->Layout();
}

void DialogLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto dialogProp = DynamicCast<DialogLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(dialogProp);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto dialogTheme = pipelineContext->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(dialogTheme);
    ParseSubwindowId(dialogProp);
    auto selfSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    const auto& children = layoutWrapper->GetAllChildrenWithBuild();
    if (children.empty()) {
        return;
    }
    auto dialogPattern = frameNode->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(dialogPattern);
    if (isModal_ && dialogPattern->GetDialogProperties().maskRect.has_value()) {
        std::optional<DimensionRect> maskRect = GetMaskRect(frameNode);
        ProcessMaskRect(maskRect, frameNode, true);
    }
    if (hasAddMaskNode_) {
        UpdateCustomMaskNodeLayout(frameNode);
    }
    auto child = children.front();
    auto childSize = child->GetGeometryNode()->GetMarginFrameSize();
    dialogChildSize_ = childSize;
    // is PcDevice MultipleDialog Offset to the bottom right
    if (dialogTheme->GetMultipleDialogDisplay() != "stack" && !dialogProp->GetIsModal().value_or(true) &&
        dialogProp->GetShowInSubWindowValue(false)) {
        auto pipeline = frameNode->GetContextRefPtr();
        auto currentId = pipeline ? pipeline->GetInstanceId() : Container::CurrentIdSafely();
        auto subWindow = SubwindowManager::GetInstance()->GetSubwindowByType(currentId, SubwindowType::TYPE_DIALOG);
        CHECK_NULL_VOID(subWindow);
        auto subOverlayManager = subWindow->GetOverlayManager();
        CHECK_NULL_VOID(subOverlayManager);
        MultipleDialog(dialogProp, childSize, selfSize, subOverlayManager);
    }
    dialogOffset_ = dialogProp->GetDialogOffset().value_or(DimensionOffset());
    alignment_ = dialogProp->GetDialogAlignment().value_or(DialogAlignment::DEFAULT);
    topLeftPoint_ = ComputeChildPosition(childSize, dialogProp, selfSize);
    auto isNonUIExtensionSubwindow = isShowInSubWindow_ && !isUIExtensionSubWindow_;
    if ((!isModal_ || isNonUIExtensionSubwindow) && !dialogProp->GetIsSceneBoardDialog().value_or(false)) {
        ProcessMaskRect(
            DimensionRect(Dimension(childSize.Width()), Dimension(childSize.Height()), DimensionOffset(topLeftPoint_)),
            frameNode);
    }
    child->GetGeometryNode()->SetMarginFrameOffset(topLeftPoint_);
    AdjustHeightForKeyboard(layoutWrapper, child);
    child->Layout();
    SetSubWindowHotarea(dialogProp, childSize, selfSize, frameNode->GetId());
}

void DialogLayoutAlgorithm::ParseSubwindowId(const RefPtr<DialogLayoutProperty>& dialogProp)
{
    CHECK_NULL_VOID(dialogProp);
    if (!dialogProp->GetShowInSubWindowValue(false)) {
        return;
    }

    subWindowId_ = Container::CurrentId();
    auto dialogNode = dialogProp->GetHost();
    CHECK_NULL_VOID(dialogNode);
    auto pipeline = dialogNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    subWindowId_ = pipeline->GetInstanceId();
}

void DialogLayoutAlgorithm::AdjustHeightForKeyboard(LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& child)
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE) || !child || !resizeFlag_ ||
        keyboardAvoidMode_ == KeyboardAvoidMode::NONE) {
        return;
    }
    auto childLayoutProperty = child->GetLayoutProperty();
    auto dialogProp = DynamicCast<DialogLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(childLayoutProperty);
    CHECK_NULL_VOID(dialogProp);
    auto childConstraint =
        CreateDialogChildConstraint(layoutWrapper, dialogChildSize_.Height(), dialogChildSize_.Width());
    auto dialogHeight = Dimension(dialogChildSize_.Height(), DimensionUnit::PX);
    auto dialogWidth = Dimension(dialogChildSize_.Width(), DimensionUnit::PX);
    if (!customSize_ && dialogProp->GetWidth().has_value()) {
        childLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(dialogWidth), std::nullopt));
    }
    if (!customSize_ && dialogProp->GetHeight().has_value()) {
        childLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(dialogHeight)));
    }
    child->Measure(childConstraint);
    child->GetGeometryNode()->SetFrameSize(dialogChildSize_);
    auto renderContext = child->GetHostNode()->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetClipToFrame(true);
    renderContext->UpdateClipEdge(true);
}

void DialogLayoutAlgorithm::SetSubWindowHotarea(
    const RefPtr<DialogLayoutProperty>& dialogProp, SizeF childSize, SizeF selfSize, int32_t frameNodeId)
{
    if (!dialogProp->GetShowInSubWindowValue(false)) {
        return;
    }

    std::vector<Rect> rects;
    Rect rect;
    if (!dialogProp->GetIsSceneBoardDialog().value_or(false)) {
        rect = Rect(topLeftPoint_.GetX(), topLeftPoint_.GetY(), childSize.Width(), childSize.Height());
    } else {
        rect = Rect(0.0f, 0.0f, selfSize.Width(), selfSize.Height());
    }
    if (isUIExtensionSubWindow_ && isModal_) {
        if (expandDisplay_) {
            auto isValid = hostWindowRect_.GetSize().IsPositive();
            auto hostOffset = Offset(hostWindowRect_.GetX(), hostWindowRect_.GetY());
            auto hostSize = Size(hostWindowRect_.Width(), hostWindowRect_.Height());
            rect = isValid ? Rect(hostOffset, hostSize) : Rect(0.0f, 0.0f, selfSize.Width(), selfSize.Height());
            auto contentRect = Rect(topLeftPoint_.GetX(), topLeftPoint_.GetY(), childSize.Width(), childSize.Height());
            rects.emplace_back(contentRect);
        } else {
            rect = Rect(0.0f, 0.0f, selfSize.Width(), selfSize.Height());
        }
    }
    rects.emplace_back(rect);
    SubwindowManager::GetInstance()->SetHotAreas(rects, SubwindowType::TYPE_DIALOG, frameNodeId, subWindowId_);
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
    auto isHostWindowAlign = isUIExtensionSubWindow_ && expandDisplay_ && hostWindowRect_.GetSize().IsPositive();
    auto maxSize = isHostWindowAlign ? hostWindowRect_.GetSize() : layoutConstraint->maxSize;
    if (!SetAlignmentSwitch(maxSize, childSize, topLeftPoint)) {
        topLeftPoint = OffsetF(maxSize.Width() - childSize.Width(), maxSize.Height() - childSize.Height()) / HALF;
    }
    if (isHostWindowAlign) {
        topLeftPoint += hostWindowRect_.GetOffset();
    }
    const auto& expandSafeAreaOpts = prop->GetSafeAreaExpandOpts();
    bool needAvoidKeyboard = true;
    if ((expandSafeAreaOpts && (expandSafeAreaOpts->type & SAFE_AREA_TYPE_KEYBOARD)) ||
        keyboardAvoidMode_ == KeyboardAvoidMode::NONE) {
        needAvoidKeyboard = false;
    }
    return AdjustChildPosition(topLeftPoint, dialogOffset, childSize, needAvoidKeyboard);
}

bool DialogLayoutAlgorithm::IsAlignmentByWholeScreen()
{
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        return false;
    }

    switch (alignment_) {
        case DialogAlignment::TOP:
        case DialogAlignment::TOP_START:
        case DialogAlignment::TOP_END:
        case DialogAlignment::BOTTOM:
        case DialogAlignment::BOTTOM_START:
        case DialogAlignment::BOTTOM_END:
            return false;
        case DialogAlignment::CENTER:
        case DialogAlignment::CENTER_START:
        case DialogAlignment::CENTER_END:
        default:
            return true;
    }
}

void DialogLayoutAlgorithm::CaculateMaxSize(SizeF& maxSize)
{
    auto halfScreenHeight = maxSize.Height() / HALF;
    if (!customSize_ && isHoverMode_) {
        maxSize.SetHeight(halfScreenHeight);
    }
    if (!customSize_ && !IsAlignmentByWholeScreen()) {
        if (isHoverMode_ && hoverModeArea_ == HoverModeAreaType::TOP_SCREEN) {
            maxSize.SetHeight(foldCreaseRect.Top());
            return;
        }
        maxSize.MinusHeight(safeAreaBottomLength_);
    }
}

bool DialogLayoutAlgorithm::SetAlignmentSwitch(SizeF& maxSize, const SizeF& childSize, OffsetF& topLeftPoint)
{
    auto halfScreenHeight = maxSize.Height() / HALF;
    CaculateMaxSize(maxSize);
    if (alignment_ != DialogAlignment::DEFAULT || Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        switch (alignment_) {
            case DialogAlignment::TOP:
                topLeftPoint = OffsetF((maxSize.Width() - childSize.Width()) / HALF, 0.0);
                break;
            case DialogAlignment::CENTER:
                topLeftPoint =
                    OffsetF(maxSize.Width() - childSize.Width(), maxSize.Height() - childSize.Height()) / HALF;
                break;
            case DialogAlignment::BOTTOM:
                topLeftPoint =
                    OffsetF((maxSize.Width() - childSize.Width()) / HALF, maxSize.Height() - childSize.Height());
                break;
            case DialogAlignment::TOP_START:
                topLeftPoint = OffsetF(0.0, 0.0);
                break;
            case DialogAlignment::TOP_END:
                topLeftPoint = OffsetF(maxSize.Width() - childSize.Width(), 0.0);
                break;
            case DialogAlignment::CENTER_START:
                topLeftPoint = OffsetF(0.0, maxSize.Height() - childSize.Height()) / HALF;
                break;
            case DialogAlignment::CENTER_END:
                topLeftPoint =
                    OffsetF(maxSize.Width() - childSize.Width(), (maxSize.Height() - childSize.Height()) / HALF);
                break;
            case DialogAlignment::BOTTOM_START:
                topLeftPoint = OffsetF(0.0, maxSize.Height() - childSize.Height());
                break;
            case DialogAlignment::BOTTOM_END:
                topLeftPoint = OffsetF(maxSize.Width() - childSize.Width(), maxSize.Height() - childSize.Height());
                break;
            default:
                topLeftPoint =
                    OffsetF(maxSize.Width() - childSize.Width(), maxSize.Height() - childSize.Height()) / HALF;
                break;
        }
        if (alignBottomScreen_) {
            topLeftPoint.SetY(topLeftPoint.GetY() + halfScreenHeight);
        }
        return true;
    }

    return SetAlignmentSwitchLessThanAPITwelve(maxSize, childSize, topLeftPoint);
}

bool DialogLayoutAlgorithm::SetAlignmentSwitchLessThanAPITwelve(const SizeF& maxSize, const SizeF& childSize,
    OffsetF& topLeftPoint)
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto displayInfo = container->GetDisplayInfo();
    CHECK_NULL_RETURN(displayInfo, false);
    auto foldStatus = displayInfo->GetFoldStatus();
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) && displayInfo->GetIsFoldable() &&
        (foldStatus == FoldStatus::EXPAND || foldStatus == FoldStatus::HALF_FOLD)) {
        topLeftPoint = OffsetF(maxSize.Width() - childSize.Width(), maxSize.Height() - childSize.Height()) / HALF;
        return true;
    }

    bool version10OrLarger = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN);
    if (version10OrLarger && SystemProperties::GetDeviceType() == DeviceType::PHONE) {
        if (SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE) {
            topLeftPoint = OffsetF(maxSize.Width() - childSize.Width(), maxSize.Height() - childSize.Height()) / HALF;
            return true;
        }
        if (SystemProperties::GetDeviceOrientation() == DeviceOrientation::PORTRAIT) {
            topLeftPoint = OffsetF((maxSize.Width() - childSize.Width()) / HALF,
                std::max(maxSize.Height() - childSize.Height() - GetPaddingBottom(), 0.0));
            return true;
        }
    }
    return false;
}

void DialogLayoutAlgorithm::UpdateTouchRegion()
{
    //update touch region is not completed.
}

double DialogLayoutAlgorithm::GetPaddingBottom() const
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, 0);
    auto dialogTheme = pipelineContext->GetTheme<DialogTheme>();
    CHECK_NULL_RETURN(dialogTheme, 0);
    auto bottom = dialogTheme->GetDefaultDialogMarginBottom();
    if (keyboardAvoidDistance_.has_value()) {
        return pipelineContext->NormalizeToPx(keyboardAvoidDistance_.value());
    } else {
        return pipelineContext->NormalizeToPx(bottom);
    }
}

OffsetF DialogLayoutAlgorithm::AdjustChildPosition(
    OffsetF& topLeftPoint, const OffsetF& dialogOffset, const SizeF& childSize, bool needAvoidKeyboard)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, topLeftPoint + dialogOffset);
    if (!customSize_ && LessNotEqual(topLeftPoint.GetY() + embeddedDialogOffsetY_, safeAreaInsets_.top_.end)) {
        topLeftPoint.SetY(safeAreaInsets_.top_.end);
    }
    if (alignBottomScreen_) {
        bool alignTop = alignment_ == DialogAlignment::TOP || alignment_ == DialogAlignment::TOP_START ||
            alignment_ == DialogAlignment::TOP_END;
        if (topLeftPoint.GetY() < foldCreaseRect.Bottom() || alignTop) {
            topLeftPoint.SetY(foldCreaseRect.Bottom());
        }
    }
    auto childOffset = topLeftPoint + dialogOffset;
    auto manager = pipelineContext->GetSafeAreaManager();
    auto keyboardInsert = manager->GetKeyboardInset();
    auto childBottom = childOffset.GetY() + childSize.Height() + embeddedDialogOffsetY_ + stackRootDialogOffsetY_;
    auto paddingBottom = static_cast<float>(GetPaddingBottom());
    if (needAvoidKeyboard && keyboardInsert.Length() > 0 && childBottom > (keyboardInsert.start - paddingBottom)) {
        auto limitPos = std::min(childOffset.GetY(),
            static_cast<float>(safeAreaInsets_.top_.Length() + AVOID_LIMIT_PADDING.ConvertToPx()));
        childOffset.SetY(childOffset.GetY() - (childBottom - (keyboardInsert.start - paddingBottom)));

        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) && childOffset.GetY() < limitPos) {
            resizeFlag_ = true;
            dialogChildSize_ = childSize;
            if (limitPos - childOffset.GetY() > dialogChildSize_.Height()) {
                dialogChildSize_.MinusHeight(dialogChildSize_.Height());
            } else {
                dialogChildSize_.MinusHeight(limitPos - childOffset.GetY());
            }
            childOffset.SetY(limitPos);
        }
    }
    return childOffset;
}

void DialogLayoutAlgorithm::UpdateSafeArea(const RefPtr<FrameNode>& frameNode)
{
    auto container = Container::Current();
    auto currentId = Container::CurrentId();
    CHECK_NULL_VOID(container);
    if (container->IsSubContainer()) {
        currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
        container = AceEngine::Get().GetContainer(currentId);
        CHECK_NULL_VOID(container);
        ContainerScope scope(currentId);
    }
    safeAreaInsets_ = OverlayManager::GetSafeAreaInsets(frameNode);
    if (!IsEmbeddedDialog(frameNode)) {
        safeAreaBottomLength_ = safeAreaInsets_.bottom_.Length();
    }
    if (isHoverMode_) {
        auto displayInfo = container->GetDisplayInfo();
        CHECK_NULL_VOID(displayInfo);
        auto foldCreaseRects = displayInfo->GetCurrentFoldCreaseRegion();
        if (!foldCreaseRects.empty()) {
            foldCreaseRect = foldCreaseRects.front();
        }
    }
    TAG_LOGI(AceLogTag::ACE_DIALOG, "safeAreaInsets: %{public}s", safeAreaInsets_.ToString().c_str());
}

void DialogLayoutAlgorithm::ClipUIExtensionSubWindowContent(const RefPtr<FrameNode>& dialog)
{
    CHECK_NULL_VOID(dialog);
    auto isFullScreen =
        IsGetExpandDisplayValidHeight() && NearEqual(expandDisplayValidHeight_, hostWindowRect_.Height());
    auto maskNodePtr = dialog->GetChildByIndex(EXTRA_MASK_NODE_INDEX);
    CHECK_NULL_VOID(maskNodePtr);
    auto maskNode = AceType::DynamicCast<FrameNode>(maskNodePtr);
    CHECK_NULL_VOID(maskNode);
    auto maskNodeLayoutProp = maskNode->GetLayoutProperty();
    CHECK_NULL_VOID(maskNodeLayoutProp);
    auto maskGeometryNode = maskNode->GetGeometryNode();
    CHECK_NULL_VOID(maskGeometryNode);
    if (expandDisplay_) {
        maskNodeLayoutProp->ClearUserDefinedIdealSize(true, true);
        SizeF realSize;
        realSize.SetWidth(hostWindowRect_.Width());
        realSize.SetHeight(hostWindowRect_.Height());
        maskGeometryNode->SetFrameSize(realSize);
        OffsetF offset;
        offset.SetX(hostWindowRect_.GetX());
        offset.SetY(hostWindowRect_.GetY());
        maskGeometryNode->SetFrameOffset(offset);
        if (!isFullScreen) {
            auto maskNodeContext = maskNode->GetRenderContext();
            CHECK_NULL_VOID(maskNodeContext);
            maskNodeContext->UpdateBorderRadius(NG::BorderRadiusPropertyT<Dimension>(CONTAINER_OUTER_RADIUS));
        }
    } else {
        maskNodeLayoutProp->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(1.0, DimensionUnit::PERCENT)));
        maskGeometryNode->SetFrameOffset(OffsetF(0, 0));
        maskNode->Measure(dialog->GetLayoutConstraint());
    }
    maskNode->Layout();
}

void DialogLayoutAlgorithm::UpdateIsScrollHeightNegative(LayoutWrapper* layoutWrapper, float height)
{
    if (height < SCROLL_MIN_HEIGHT_SUITOLD.ConvertToPx()) {
        const auto& children = layoutWrapper->GetAllChildrenWithBuild();
        auto child = children.front();
        auto childSize = child->GetGeometryNode()->GetMarginFrameSize();
        if (childSize.Height() == dialogMaxHeight_ && childSize.Height() > 0) {
            auto hostNode = layoutWrapper->GetHostNode();
            CHECK_NULL_VOID(hostNode);
            auto dialogPattern = hostNode->GetPattern<DialogPattern>();
            CHECK_NULL_VOID(dialogPattern);
            dialogPattern->SetIsScrollHeightNegative(true);
        }
    }
}

bool DialogLayoutAlgorithm::IsEmbeddedDialog(const RefPtr<FrameNode>& frameNode)
{
    auto parent = frameNode->GetParent();
    if (parent && (parent->GetTag() == V2::PAGE_ETS_TAG || parent->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG)) {
        return true;
    }
    return false;
}
 
float DialogLayoutAlgorithm::GetEmbeddedDialogOffsetY(const RefPtr<FrameNode>& frameNode)
{
    auto parent = AceType::DynamicCast<FrameNode>(frameNode->GetParent());
    CHECK_NULL_RETURN(parent, 0.0f);
    if (parent->GetTag() == V2::PAGE_ETS_TAG) {
        return parent->GetOffsetRelativeToWindow().GetY();
    }
    if (parent->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
        return parent->GetGeometryNode()->GetParentAdjust().GetY();
    }
    return 0.0f;
}

float DialogLayoutAlgorithm::GetStackRootDialogOffsetY(const RefPtr<FrameNode>& frameNode)
{
    auto parent = AceType::DynamicCast<FrameNode>(frameNode->GetParent());
    CHECK_NULL_RETURN(parent, 0.0f);
    if (parent->GetTag() == V2::STACK_ETS_TAG && expandDisplay_ == true) {
        return parent->GetOffsetRelativeToWindow().GetY();
    }
    return 0.0f;
}
} // namespace OHOS::Ace::NG
