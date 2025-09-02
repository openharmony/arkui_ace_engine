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

#include "core/components_ng/pattern/folder_stack/folder_stack_layout_algorithm.h"

#include "base/log/event_report.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float OFFSET_VALUE = 1.0f;
constexpr float OFFSET_DIVISOR = 2.0f;
} // namespace

FolderStackLayoutAlgorithm::FolderStackLayoutAlgorithm() = default;

void FolderStackLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto folderStackLayoutProperty =
        AceType::DynamicCast<FolderStackLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(folderStackLayoutProperty);
    auto hostNode = AceType::DynamicCast<FolderStackGroupNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto align = Alignment::CENTER;
    if (folderStackLayoutProperty->GetPositionProperty()) {
        align = folderStackLayoutProperty->GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER);
    }
    if (!isIntoFolderStack_) {
        auto childLayoutProperty = AceType::DynamicCast<StackLayoutProperty>(layoutWrapper->GetLayoutProperty());
        if (childLayoutProperty && childLayoutProperty->GetPositionProperty()) {
            childLayoutProperty->GetPositionProperty()->UpdateAlignment(align);
        }
        StackLayoutAlgorithm::Layout(layoutWrapper);
        return;
    }
    LayoutHoverStack(layoutWrapper, hostNode, folderStackLayoutProperty);
    LayoutControlPartsStack(layoutWrapper, hostNode, folderStackLayoutProperty);
}

void FolderStackLayoutAlgorithm::LayoutHoverStack(LayoutWrapper* layoutWrapper,
    const RefPtr<FolderStackGroupNode>& hostNode, const RefPtr<FolderStackLayoutProperty>& folderStackLayoutProperty)
{
    auto folderStackGeometryNode = layoutWrapper->GetGeometryNode();
    auto size = folderStackGeometryNode->GetFrameSize();
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    auto layoutDirection = layoutProperty->GetLayoutDirection();
    if (layoutDirection == TextDirection::AUTO) {
        layoutDirection = AceApplicationInfo::GetInstance().IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR;
    }
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0);
    auto top = padding.top.value_or(0);
    auto paddingOffset = OffsetF(left, top);
    auto align = Alignment::CENTER;
    if (folderStackLayoutProperty->GetPositionProperty()) {
        align = folderStackLayoutProperty->GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER);
    }
    auto hoverNode = hostNode->GetHoverNode();
    auto index = hostNode->GetChildIndexById(hoverNode->GetId());
    auto hoverStackWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    auto geometryNode = hoverStackWrapper->GetGeometryNode();
    auto hoverStackOffset = OffsetT<float>(0.0f, 0.0f);
    geometryNode->SetMarginFrameOffset(hoverStackOffset);
    auto hoverSize = geometryNode->GetFrameSize();
    for (auto&& child : hoverStackWrapper->GetAllChildrenWithBuild()) {
        auto translate =
            CalculateStackAlignment(hoverSize, child->GetGeometryNode()->GetMarginFrameSize(), align) + paddingOffset;
        if (layoutDirection == TextDirection::RTL) {
            translate.SetX(
                hoverSize.Width() - translate.GetX() - child->GetGeometryNode()->GetMarginFrameSize().Width());
        }
        child->GetGeometryNode()->SetMarginFrameOffset(translate);
    }
    hoverStackWrapper->Layout();
}

void FolderStackLayoutAlgorithm::LayoutControlPartsStack(LayoutWrapper* layoutWrapper,
    const RefPtr<FolderStackGroupNode>& hostNode, const RefPtr<FolderStackLayoutProperty>& folderStackLayoutProperty)
{
    auto folderStackGeometryNode = layoutWrapper->GetGeometryNode();
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutDirection = layoutProperty->GetLayoutDirection();
    if (layoutDirection == TextDirection::AUTO) {
        layoutDirection = AceApplicationInfo::GetInstance().IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR;
    }

    auto align = Alignment::CENTER;
    if (folderStackLayoutProperty->GetPositionProperty()) {
        align = folderStackLayoutProperty->GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER);
    }
    auto controlPartsStackNode = hostNode->GetControlPartsStackNode();
    auto index = hostNode->GetChildIndexById(controlPartsStackNode->GetId());
    auto controlPartsStackWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    auto geometryNode = controlPartsStackWrapper->GetGeometryNode();
    auto controlPartsStackRect = GetControlPartsStackRect();
    geometryNode->SetMarginFrameOffset(controlPartsStackRect);
    
    controlPartsStackWrapper->Layout();
}

void FolderStackLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto hostNode = AceType::DynamicCast<FolderStackGroupNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto pattern = layoutWrapper->GetHostNode()->GetPattern<FolderStackPattern>();
    CHECK_NULL_VOID(pattern);
    const auto& layoutProperty = DynamicCast<FolderStackLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    const auto& layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    auto size = CreateIdealSizeByPercentRef(layoutConstraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT)
                    .ConvertToSizeT();
    layoutWrapper->GetGeometryNode()->SetFrameSize(size);
    isIntoFolderStack_ = IsIntoFolderStack(size, layoutProperty, layoutWrapper);
    AdjustNodeTree(hostNode);
    OnHoverStatusChange(layoutWrapper);
    if (!isIntoFolderStack_) {
        MeasureByStack(hostNode, layoutWrapper);
        pattern->SetNeedCallBack(false);
        return;
    }
    if (!pattern->GetNeedCallBack()) {
        pattern->SetNeedCallBack(true);
        auto displayInfo = pattern->GetDisplayInfo();
        if (displayInfo) {
            FolderEventInfo event(displayInfo->GetFoldStatus());
            auto eventHub = layoutWrapper->GetHostNode()->GetEventHub<FolderStackEventHub>();
            if (eventHub) {
                eventHub->OnFolderStateChange(event);
            }
        }
    }
    RangeCalculation(hostNode, layoutProperty, size);
    MeasureHoverStack(layoutWrapper, hostNode, layoutProperty, size);
    MeasureControlPartsStack(layoutWrapper, hostNode, layoutProperty, size);
}

void FolderStackLayoutAlgorithm::MeasureHoverStack(LayoutWrapper* layoutWrapper,
    const RefPtr<FolderStackGroupNode>& hostNode, const RefPtr<FolderStackLayoutProperty>& foldStackLayoutProperty,
    const SizeF& size)
{
    auto hoverNode = hostNode->GetHoverNode();
    CHECK_NULL_VOID(hoverNode);
    auto index = hostNode->GetChildIndexById(hoverNode->GetId());
    auto hoverWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(hoverWrapper);
    auto constraint = foldStackLayoutProperty->CreateChildConstraint();
    constraint.selfIdealSize = OptionalSizeF(size.Width(), preHoverStackHeight_);
    hoverWrapper->Measure(constraint);
}

void FolderStackLayoutAlgorithm::MeasureControlPartsStack(LayoutWrapper* layoutWrapper,
    const RefPtr<FolderStackGroupNode>& hostNode, const RefPtr<FolderStackLayoutProperty>& foldStackLayoutProperty,
    const SizeF& size)
{
    auto controlPartsStackNode = hostNode->GetControlPartsStackNode();
    CHECK_NULL_VOID(controlPartsStackNode);
    auto index = hostNode->GetChildIndexById(controlPartsStackNode->GetId());
    auto controlPartsWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(controlPartsWrapper);
    auto constraint = foldStackLayoutProperty->CreateChildConstraint();
    constraint.selfIdealSize = OptionalSizeF(size.Width(), preControlPartsStackHeight_);
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    PaddingProperty controlPartsPadding;
    controlPartsPadding.left = CalcLength(padding.left.value_or(0));
    controlPartsPadding.right = CalcLength(padding.right.value_or(0));
    controlPartsPadding.top = CalcLength(padding.top.value_or(0));
    controlPartsPadding.bottom = CalcLength(padding.bottom.value_or(0));
    const auto& controlPartsLayoutProperty = controlPartsWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(controlPartsLayoutProperty);
    controlPartsLayoutProperty->UpdatePadding(controlPartsPadding);
    controlPartsWrapper->Measure(constraint);
}

void FolderStackLayoutAlgorithm::RangeCalculation(const RefPtr<FolderStackGroupNode>& hostNode,
    const RefPtr<FolderStackLayoutProperty>& folderStackLayoutProperty, const SizeF& size)
{
    int32_t creaseY = 0;
    int32_t creaseHeight = 0;
    const auto& constraint = folderStackLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto safeArea = pipeline->GetSafeArea();
    int32_t length = static_cast<int32_t>(safeArea.top_.Length());
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto displayInfo = container->GetDisplayInfo();
    CHECK_NULL_VOID(displayInfo);
    auto foldCreaseRects = displayInfo->GetCurrentFoldCreaseRegion();
    if (!foldCreaseRects.empty()) {
        auto foldCrease = foldCreaseRects.front();
        creaseY = static_cast<int32_t>(foldCrease.Bottom() - foldCrease.Height());
        creaseHeight = static_cast<int32_t>(foldCrease.Height());
    }
    preHoverStackHeight_ = static_cast<float>(creaseY - length);
    preControlPartsStackHeight_ = static_cast<float>(size.Height() - creaseHeight - preHoverStackHeight_);
    controlPartsStackRect_ = OffsetF(0.0f, creaseY - length + creaseHeight);
}

bool FolderStackLayoutAlgorithm::IsFullWindow(
    SizeF& frameSize, const RefPtr<FolderStackLayoutProperty>& foldStackLayoutProperty, LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, false);
    auto parent = AceType::DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_RETURN(parent, false);
    const auto& parentLayoutProperty = parent->GetLayoutProperty();
    CHECK_NULL_RETURN(parentLayoutProperty, false);
    auto padding = parentLayoutProperty->CreatePaddingAndBorder();
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto windowManager = pipeline->GetWindowManager();
    auto safeArea = pipeline->GetSafeArea();
    CHECK_NULL_RETURN(windowManager, false);
    auto windowMode = windowManager->GetWindowMode();
    auto realWidth = frameSize.Width() + padding.Width();
    auto realHeight = frameSize.Height() + padding.Height();
    auto rootWidth = pipeline->GetRootWidth();
    auto rootHeight = pipeline->GetRootHeight();
    SizeF fullScreen = { rootWidth - safeArea.left_.Length() - safeArea.right_.Length(),
        rootHeight - safeArea.top_.Length() - safeArea.bottom_.Length() };
    if (CheckExpandConstraintFullScreen(
        foldStackLayoutProperty, realWidth, realHeight, safeArea, windowMode, fullScreen)) {
        return true;
    }
    if (!NearEqual(realWidth, rootWidth - safeArea.left_.Length() - safeArea.right_.Length()) ||
        !NearEqual(realHeight, rootHeight - safeArea.top_.Length() - safeArea.bottom_.Length()) ||
        windowMode != WindowMode::WINDOW_MODE_FULLSCREEN) {
        return false;
    }
    return true;
}

bool FolderStackLayoutAlgorithm::CheckExpandConstraintFullScreen(
    const RefPtr<FolderStackLayoutProperty>& foldStackLayoutProperty, const float& realWidth, const float& realHeight,
    const SafeAreaInsets& safeArea, WindowMode windowMode, SizeF fullScreen)
{
    CHECK_NULL_RETURN(foldStackLayoutProperty, false);
    if (foldStackLayoutProperty->IsExpandConstraintNeeded()) {
        return false;
    }
    const auto& ignoreOpts = foldStackLayoutProperty->GenIgnoreOpts();
    if (ignoreOpts.edges & NG::LAYOUT_SAFE_AREA_EDGE_TOP) {
        fullScreen.AddHeight(safeArea.top_.Length());
    }
    if (ignoreOpts.edges & NG::LAYOUT_SAFE_AREA_EDGE_START) {
        fullScreen.AddWidth(safeArea.left_.Length());
    }
    if (ignoreOpts.edges & NG::LAYOUT_SAFE_AREA_EDGE_BOTTOM) {
        fullScreen.AddHeight(safeArea.bottom_.Length());
    }
    if (ignoreOpts.edges & NG::LAYOUT_SAFE_AREA_EDGE_END) {
        fullScreen.AddWidth(safeArea.right_.Length());
    }
    if (NearEqual(realWidth, fullScreen.Width()) && NearEqual(realHeight, fullScreen.Height()) &&
        windowMode == WindowMode::WINDOW_MODE_FULLSCREEN) {
        return true;
    }
    return false;
}

void FolderStackLayoutAlgorithm::AdjustNodeTree(const RefPtr<FolderStackGroupNode>& hostNode)
{
    auto hoverNode = hostNode->GetHoverNode();
    auto controlPartsStackNode = hostNode->GetControlPartsStackNode();
    auto isChangeItemId = hostNode->GetIsChangeItemId();
    if (isChangeItemId) {
        hostNode->SetIsChangeItemId(false);
    } else if ((!isIntoFolderStack_ && hoverNode->GetChildren().size() == 0) ||
        (isIntoFolderStack_ && hoverNode->GetChildren().size() > 0)) {
        return;
    }
    hoverNode->Clean();
    controlPartsStackNode->Clean();
    if (!isIntoFolderStack_) {
        for (auto& childNode : hostNode->GetChildNode()) {
            controlPartsStackNode->AddChild(childNode);
        }
    } else {
        auto itemId = hostNode->GetItemId();
        for (auto& childNode : hostNode->GetChildNode()) {
            if (std::count(itemId.begin(), itemId.end(), childNode->GetInspectorId())) {
                hoverNode->AddChild(childNode);
            } else {
                controlPartsStackNode->AddChild(childNode);
            }
        }
    }
}

NG::OffsetF FolderStackLayoutAlgorithm::CalculateStackAlignment(
    const NG::SizeF& parentSize, const NG::SizeF& childSize, const Alignment& alignment)
{
    NG::OffsetF offset;
    offset.SetX((OFFSET_VALUE + alignment.GetHorizontal()) * (parentSize.Width() - childSize.Width()) / OFFSET_DIVISOR);
    offset.SetY((OFFSET_VALUE + alignment.GetVertical()) * (parentSize.Height() - childSize.Height()) / OFFSET_DIVISOR);
    return offset;
}

bool FolderStackLayoutAlgorithm::IsIntoFolderStack(
    SizeF& frameSize, const RefPtr<FolderStackLayoutProperty>& foldStackLayoutProperty, LayoutWrapper* layoutWrapper)
{
    auto pattern = layoutWrapper->GetHostNode()->GetPattern<FolderStackPattern>();
    CHECK_NULL_RETURN(pattern, false);
    CHECK_NULL_RETURN(!pattern->HasFoldStatusDelayTask(), false);
    auto displayInfo = pattern->GetDisplayInfo();
    if (!displayInfo) {
        auto container = Container::Current();
        CHECK_NULL_RETURN(container, false);
        displayInfo = container->GetDisplayInfo();
    }
    CHECK_NULL_RETURN(displayInfo, false);
    bool isFullWindow = IsFullWindow(frameSize, foldStackLayoutProperty, layoutWrapper);
    bool isFoldable = OHOS::Ace::SystemProperties::IsBigFoldProduct();
    auto foldStatus = displayInfo->GetFoldStatus();
    auto rotation = displayInfo->GetRotation();
    auto isLandscape = rotation == Rotation::ROTATION_90 || rotation == Rotation::ROTATION_270;
    TAG_LOGI(AceLogTag::ACE_FOLDER_STACK,
        "folderStack state isFullWindow:%{public}d, isFoldable:%{public}d, "
        "foldStatus:%{public}d, isLandscape:%{public}d",
        isFullWindow, isFoldable, foldStatus, isLandscape);
    return isFullWindow && isFoldable && foldStatus == FoldStatus::HALF_FOLD && isLandscape;
}

void FolderStackLayoutAlgorithm::OnHoverStatusChange(LayoutWrapper* layoutWrapper)
{
    auto pattern = layoutWrapper->GetHostNode()->GetPattern<FolderStackPattern>();
    CHECK_NULL_VOID(pattern);
    if (isIntoFolderStack_ == pattern->IsInHoverMode() || !OHOS::Ace::SystemProperties::IsBigFoldProduct()) {
        return;
    }
    auto eventHub = layoutWrapper->GetHostNode()->GetEventHub<FolderStackEventHub>();
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_VOID(windowManager);
    auto windowMode = windowManager->GetWindowMode();
    auto displayInfo = pattern->GetDisplayInfo();
    FolderEventInfo hoverChangeEvent(
        displayInfo->GetFoldStatus(), isIntoFolderStack_, displayInfo->GetRotation(), windowMode);
    if (eventHub) {
        eventHub->OnHoverStatusChange(std::move(hoverChangeEvent));
        TAG_LOGI(AceLogTag::ACE_FOLDER_STACK,
            "hoverStatus change callback FoldStatus:%{public}d, isHoverMode:%{public}d, "
            "appRotation:%{public}d, windowMode:%{public}d",
            displayInfo->GetFoldStatus(), isIntoFolderStack_, displayInfo->GetRotation(), windowMode);
    }
    auto nowTime = std::time(0);
    auto lastTime = pattern->GetLastTime();
    auto inHoverTime = isIntoFolderStack_ ? 0 : static_cast<int32_t>(nowTime) - static_cast<int32_t>(lastTime);
    EventReport::ReportHoverStatusChange(static_cast<int32_t>(displayInfo->GetFoldStatus()), inHoverTime,
        isIntoFolderStack_, static_cast<int32_t>(displayInfo->GetRotation()), static_cast<int32_t>(windowMode));
    pattern->SetLastTime(nowTime);
}

void FolderStackLayoutAlgorithm::MeasureByStack(
    const RefPtr<FolderStackGroupNode>& hostNode, LayoutWrapper* layoutWrapper)
{
    PaddingProperty padding { .left = CalcLength(0.0f),
        .right = CalcLength(0.0f),
        .top = CalcLength(0.0f),
        .bottom = CalcLength(0.0f),
        .start = std::nullopt,
        .end = std::nullopt };
    auto controlPartsStackNode = hostNode->GetControlPartsStackNode();
    CHECK_NULL_VOID(controlPartsStackNode);
    auto index = hostNode->GetChildIndexById(controlPartsStackNode->GetId());
    auto controlPartsWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(controlPartsWrapper);
    const auto& controlPartsLayoutProperty = controlPartsWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(controlPartsLayoutProperty);
    controlPartsLayoutProperty->UpdatePadding(padding);
    MatchParentWhenChildrenMatch(layoutWrapper, controlPartsWrapper);
    StackLayoutAlgorithm::Measure(layoutWrapper);
    auto hoverNode = hostNode->GetHoverNode();
    CHECK_NULL_VOID(hoverNode);
    auto hoverIndex = hostNode->GetChildIndexById(hoverNode->GetId());
    auto hoverStackWrapper = layoutWrapper->GetOrCreateChildByIndex(hoverIndex);
    CHECK_NULL_VOID(hoverStackWrapper);
    auto geometryNode = hoverStackWrapper->GetGeometryNode();
    geometryNode->SetFrameSize(controlPartsWrapper->GetGeometryNode()->GetFrameSize());
}


void FolderStackLayoutAlgorithm::MatchParentWhenChildrenMatch(
    LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& controlPartsLayoutWrapper)
{
    CHECK_NULL_VOID(controlPartsLayoutWrapper);
    const auto& controlPartsLayoutProperty = controlPartsLayoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(controlPartsLayoutProperty);
    controlPartsLayoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    controlPartsLayoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, false);
    for (auto&& child : controlPartsLayoutWrapper->GetAllChildrenWithBuild()) {
        auto childLayoutProperty = child->GetLayoutProperty();
        CHECK_NULL_CONTINUE(childLayoutProperty);
        auto layoutPolicy = childLayoutProperty->GetLayoutPolicyProperty();
        if (layoutPolicy.has_value() && layoutPolicy->IsMatch()) {
            if (layoutPolicy->IsWidthMatch()) {
                controlPartsLayoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
            }
            if (layoutPolicy->IsHeightMatch()) {
                controlPartsLayoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
            }
        }
    }
}
} // namespace OHOS::Ace::NG
