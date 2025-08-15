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

#include "core/components_ng/pattern/menu/multi_menu_layout_algorithm.h"

#include "base/subwindow/subwindow_manager.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_node.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {
struct SelectOverlayRightClickMenuLayoutHelper {
    static void AdjustLayoutConstraints(
        LayoutConstraintF& constrainMinWidth, const RefPtr<LayoutWrapper>& child, LayoutWrapper* layoutWrapper)
    {
        auto host = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(host);
        auto scrollNode = host->GetParentFrameNode();
        CHECK_NULL_VOID(scrollNode);
        auto outterMenuNode = scrollNode->GetParentFrameNode();
        CHECK_NULL_VOID(outterMenuNode);
        auto outterMenuPattern = outterMenuNode->GetPattern<MenuPattern>();
        CHECK_NULL_VOID(outterMenuPattern);
        auto menuWrapperNode = outterMenuNode->GetParentFrameNode();
        CHECK_NULL_VOID(menuWrapperNode);
        auto childLayoutProperty = child->GetLayoutProperty();
        CHECK_NULL_VOID(childLayoutProperty);
        if (menuWrapperNode->GetInspectorIdValue("") != SelectOverlayRrightClickMenuWrapper ||
            !outterMenuPattern->IsSelectOverlayRightClickMenu() ||
            child->GetHostTag() != V2::RELATIVE_CONTAINER_ETS_TAG) {
            return;
        }
        childLayoutProperty->UpdateUserDefinedIdealSize(
            { CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(0.0, DimensionUnit::AUTO) });
        constrainMinWidth.percentReference.SetWidth(constrainMinWidth.selfIdealSize.Width().value_or(0.0f));
        auto row = child->GetChildByIndex(0);
        CHECK_NULL_VOID(row);
        auto layoutProperty = row->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateUserDefinedIdealSize(
            { CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(1.0, DimensionUnit::AUTO) });
        auto pasteButtonRow = child->GetChildByIndex(1);
        CHECK_NULL_VOID(pasteButtonRow);
        auto pasteButton = pasteButtonRow->GetChildByIndex(0);
        CHECK_NULL_VOID(pasteButton);
        auto pasteButtonLayoutProperty = pasteButton->GetLayoutProperty();
        CHECK_NULL_VOID(pasteButtonLayoutProperty);
        pasteButtonLayoutProperty->UpdateUserDefinedIdealSize(
            { CalcLength(1.0, DimensionUnit::PERCENT), CalcLength(1.0, DimensionUnit::PERCENT) });
    }

    static void AdjustLayoutConstraintsAutoWidth(const RefPtr<LayoutWrapper>& child, LayoutWrapper* layoutWrapper)
    {
        auto host = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(host);
        auto scrollNode = host->GetParentFrameNode();
        CHECK_NULL_VOID(scrollNode);
        auto outterMenuNode = scrollNode->GetParentFrameNode();
        CHECK_NULL_VOID(outterMenuNode);
        auto outterMenuPattern = outterMenuNode->GetPattern<MenuPattern>();
        CHECK_NULL_VOID(outterMenuPattern);
        auto menuWrapperNode = outterMenuNode->GetParentFrameNode();
        CHECK_NULL_VOID(menuWrapperNode);
        auto childLayoutProperty = child->GetLayoutProperty();
        CHECK_NULL_VOID(childLayoutProperty);
        if (menuWrapperNode->GetInspectorIdValue("") != SelectOverlayRrightClickMenuWrapper ||
            !outterMenuPattern->IsSelectOverlayRightClickMenu() ||
            child->GetHostTag() != V2::RELATIVE_CONTAINER_ETS_TAG) {
            return;
        }
        childLayoutProperty->UpdateUserDefinedIdealSize(
            { CalcLength(0.0, DimensionUnit::AUTO), CalcLength(0.0, DimensionUnit::AUTO) });
        auto row = child->GetChildByIndex(0);
        CHECK_NULL_VOID(row);
        auto layoutProperty = row->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateUserDefinedIdealSize(
            { CalcLength(0.0, DimensionUnit::AUTO), CalcLength(0.0, DimensionUnit::AUTO) });
        auto pasteButtonRow = child->GetChildByIndex(1);
        CHECK_NULL_VOID(pasteButtonRow);
        auto pasteButton = pasteButtonRow->GetChildByIndex(0);
        CHECK_NULL_VOID(pasteButton);
        auto pasteButtonLayoutProperty = pasteButton->GetLayoutProperty();
        CHECK_NULL_VOID(pasteButtonLayoutProperty);
        pasteButtonLayoutProperty->UpdateUserDefinedIdealSize(
            { CalcLength(0.0, DimensionUnit::AUTO), CalcLength(0.0, DimensionUnit::AUTO) });
    }
};
} // namespace

bool UpdateColumnWidth(const RefPtr<FrameNode>& frameNode, const RefPtr<GridColumnInfo>& columnInfo)
{
    CHECK_NULL_RETURN(frameNode && columnInfo, false);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    if (Positive(pipeline->GetRootWidth())) {
        return false;
    }

    auto currentId = Container::CurrentId();
    CHECK_NULL_RETURN(currentId >= MIN_SUBCONTAINER_ID, false);
    auto subwindowManager = SubwindowManager::GetInstance();
    CHECK_NULL_RETURN(subwindowManager, false);
    auto subwindow = subwindowManager->GetSubwindowByType(pipeline->GetInstanceId(), SubwindowType::TYPE_MENU);
    CHECK_NULL_RETURN(subwindow, false);
    auto width = subwindow->GetRect().Width();
    CHECK_NULL_RETURN(Positive(width), false);
    auto parent = columnInfo->GetParent();
    CHECK_NULL_RETURN(parent, false);
    parent->BuildColumnWidth(width);
    return true;
}

void MultiMenuLayoutAlgorithm::RemoveParentRestrictionsForFixIdeal(
    const LayoutWrapper* layoutWrapper, LayoutConstraintF& childConstraint)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto menuPattern = host->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutPolicyProperty = layoutProperty->GetLayoutPolicyProperty();
    if (menuPattern->IsEnabledContentForFixIdeal() && layoutPolicyProperty.has_value()) {
        auto& layoutPolicy = layoutPolicyProperty.value();
        if (layoutPolicy.IsWidthFix()) {
            childConstraint.maxSize.SetWidth(std::numeric_limits<float>::infinity());
        }
        if (layoutPolicy.IsHeightFix()) {
            childConstraint.maxSize.SetHeight(std::numeric_limits<float>::infinity());
        }
    }
}

void MultiMenuLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    auto childConstraint = layoutProperty->CreateChildConstraint();
    childConstraint.maxSize.SetWidth(layoutConstraint->maxSize.Width());
    RemoveParentRestrictionsForFixIdeal(layoutWrapper, childConstraint);
    // constraint max size minus padding
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    auto node = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(node);
    auto pattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(pattern);
    if (!pattern->IsEmbedded()) {
        MinusPaddingToSize(padding, childConstraint.maxSize);
    } else {
        const auto& safeAreaPadding = layoutProperty->GetOrCreateSafeAreaPadding();
        MinusPaddingToSize(safeAreaPadding, childConstraint.maxSize);
        UpdateEmbeddedPercentReference(layoutWrapper, childConstraint, layoutConstraint);
    }
    if (layoutConstraint->selfIdealSize.Width().has_value()) {
        // when Menu is set self ideal width, make children node adaptively fill up.
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            if (LessNotEqual(layoutConstraint->selfIdealSize.Width().value(), MIN_MENU_WIDTH.ConvertToPx())) {
                RefPtr<GridColumnInfo> columnInfo;
                columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::MENU);
                CHECK_NULL_VOID(columnInfo);
                auto columnParent = columnInfo->GetParent();
                CHECK_NULL_VOID(columnParent);
                columnParent->BuildColumnWidth();
                auto minWidth = static_cast<float>(columnInfo->GetWidth(MENU_MIN_GRID_COUNTS));
                layoutConstraint->selfIdealSize.SetWidth(minWidth);

                UpdateMenuDefaultConstraintByDevice(pattern, childConstraint, padding.Width(), layoutConstraint, true);
            }
        }
        auto idealWidth =
            std::max(layoutConstraint->minSize.Width(),
                std::min(layoutConstraint->maxSize.Width(), layoutConstraint->selfIdealSize.Width().value())) -
            padding.Width();
        childConstraint.selfIdealSize.SetWidth(idealWidth);
    } else {
        // constraint min width base on grid column
        auto columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::MENU);
        CHECK_NULL_VOID(columnInfo);
        auto columnParent = columnInfo->GetParent();
        CHECK_NULL_VOID(columnParent);
        if (!UpdateSelectOverlayMenuMinWidth(pattern, columnInfo) && !UpdateColumnWidth(node, columnInfo)) {
            columnParent->BuildColumnWidth();
        }
        auto minWidth = static_cast<float>(columnInfo->GetWidth()) - padding.Width();
        childConstraint.minSize.SetWidth(minWidth);

        UpdateMenuDefaultConstraintByDevice(pattern, childConstraint, padding.Width(), layoutConstraint, false);
    }
    // Calculate max width of menu items
    UpdateConstraintBaseOnMenuItems(layoutWrapper, childConstraint);
    UpdateSelfSize(layoutWrapper, childConstraint, layoutConstraint);
}

void MultiMenuLayoutAlgorithm::UpdateMenuDefaultConstraintByDevice(const RefPtr<MenuPattern>& pattern,
    LayoutConstraintF& childConstraint, float paddingWidth, std::optional<LayoutConstraintF>& layoutConstraint,
    bool idealSizeHasVal)
{
    CHECK_NULL_VOID(pattern);

    // only 2in1 device has restrictions on the menu width in API13
    CHECK_NULL_VOID(Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_THIRTEEN));
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto expandDisplay = theme->GetExpandDisplay();
    CHECK_NULL_VOID(expandDisplay);

    auto mainMenuPattern = pattern->GetMainMenuPattern();
    CHECK_NULL_VOID(mainMenuPattern);
    if (!mainMenuPattern->IsContextMenu() && !mainMenuPattern->IsMenu() &&
        !mainMenuPattern->IsSelectOverlayRightClickMenu()) {
        return;
    }

    if (idealSizeHasVal) {
        layoutConstraint->selfIdealSize.SetWidth(theme->GetMenuDefaultWidth().ConvertToPx());
    } else {
        childConstraint.minSize.SetWidth(theme->GetMenuDefaultWidth().ConvertToPx() - paddingWidth);
    }
}

void MultiMenuLayoutAlgorithm::UpdateChildPositionWidthIgnoreLayoutSafeArea(
    const RefPtr<LayoutWrapper>& childLayoutWrapper, OffsetF& translate, bool isEmbed, OffsetF& embedCorrect)
{
    CHECK_NULL_VOID(childLayoutWrapper);
    auto childNode = childLayoutWrapper->GetHostNode();
    CHECK_NULL_VOID(childNode);
    auto property = childNode->GetLayoutProperty();
    CHECK_NULL_VOID(property);
    if (!property->IsIgnoreOptsValid()) {
        return;
    };
    auto saeCorrect = translate;
    IgnoreLayoutSafeAreaOpts& opts = *(property->GetIgnoreLayoutSafeAreaOpts());
    auto sae = childNode->GetAccumulatedSafeAreaExpand(false, opts);
    auto offsetX = sae.left.value_or(0.0f);
    auto offsetY = sae.top.value_or(0.0f);
    if (isEmbed) {
        if (sae.left.has_value())
            offsetX += embedCorrect.GetX();
        if (sae.top.has_value())
            offsetY += embedCorrect.GetY();
    }
    OffsetF saeTrans = OffsetF(offsetX, offsetY);
    saeCorrect -= saeTrans;
    childLayoutWrapper->GetGeometryNode()->SetMarginFrameOffset(saeCorrect);
    translate.AddY(-offsetY);
}

void MultiMenuLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    BoxLayoutAlgorithm::PerformLayout(layoutWrapper);

    auto node = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(node);
    auto pipeline = node->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto pattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(pattern);
    OffsetF translate(0.0f, 0.0f);
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    auto outPadding = static_cast<float>(theme->GetMenuPadding().ConvertToPx());
    if (!pattern->IsEmbedded()) {
        translate.AddX(padding.left.value_or(outPadding));
        translate.AddY(padding.top.value_or(outPadding));
    }
    // translate each option by the height of previous options
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->GetGeometryNode()->SetMarginFrameOffset(translate);
        child->Layout();
        translate.AddY(child->GetGeometryNode()->GetMarginFrameSize().Height());
    }
}

void MultiMenuLayoutAlgorithm::UpdateEmbeddedPercentReference(LayoutWrapper* layoutWrapper,
    LayoutConstraintF& childConstraint, std::optional<LayoutConstraintF>& layoutConstraint)
{
    // Set percent reference for embedded menu the same as for parent menu item
    auto node = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(node);
    auto parentNode = AceType::DynamicCast<FrameNode>(node->GetParent());
    CHECK_NULL_VOID(parentNode);
    auto parentProperty = parentNode->GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(parentProperty);
    auto parentConstraint = parentProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(parentConstraint);
    auto parentPercentReference = parentConstraint->percentReference.Height();
    layoutConstraint->percentReference.SetHeight(parentPercentReference);

    auto props = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(props);
    const auto& calcConstraint = props->GetCalcLayoutConstraint();
    if (calcConstraint && calcConstraint->selfIdealSize.has_value() &&
        calcConstraint->selfIdealSize.value().Height().has_value()) {
        ScaleProperty scaleProperty;
        if (layoutWrapper->GetGeometryNode() && layoutWrapper->GetGeometryNode()->GetParentLayoutConstraint()) {
            scaleProperty = layoutWrapper->GetGeometryNode()->GetParentLayoutConstraint()->scaleProperty;
        } else {
            scaleProperty = layoutConstraint->scaleProperty;
        }
        userHeight_ = ConvertToPx(calcConstraint->selfIdealSize.value().Height()->GetDimension(),
            scaleProperty, layoutConstraint->percentReference.Height()).value_or(0.0f);
    }

    // Update embedded menu items percent reference dependent of the submenu constraint
    if (GreatNotEqual(userHeight_, 0.0f)) {
        childConstraint.percentReference.SetHeight(userHeight_);
    } else {
        childConstraint.percentReference.SetHeight(parentPercentReference);
    }
}

void MultiMenuLayoutAlgorithm::MarkChildForDelayedMeasurement(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    layoutPolicyChildren_.clear();
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        auto childLayoutProperty = child->GetLayoutProperty();
        CHECK_NULL_CONTINUE(childLayoutProperty);
        auto layoutPolicy = childLayoutProperty->GetLayoutPolicyProperty();
        if (layoutPolicy.has_value()) {
            auto widthLayoutPolicy = layoutPolicy.value().widthLayoutPolicy_;
            auto heightLayoutPolicy = layoutPolicy.value().heightLayoutPolicy_;
            if (widthLayoutPolicy.value_or(LayoutCalPolicy::NO_MATCH) != LayoutCalPolicy::NO_MATCH ||
                heightLayoutPolicy.value_or(LayoutCalPolicy::NO_MATCH) != LayoutCalPolicy::NO_MATCH) {
                layoutPolicyChildren_.emplace_back(child);
            }
        }
    }
}

void MultiMenuLayoutAlgorithm::MeasureAdaptiveLayoutChildren(
    LayoutWrapper* layoutWrapper, const LayoutConstraintF& childConstraint)
{
    MarkChildForDelayedMeasurement(layoutWrapper);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(pattern);
    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto safeAreaPadding = layoutProperty->GetOrCreateSafeAreaPadding();
    if (!pattern->IsEmbedded()) {
        MinusPaddingToNonNegativeSize(padding, frameSize);
    } else {
        MinusPaddingToNonNegativeSize(safeAreaPadding, frameSize);
    }

    for (const auto& child : layoutPolicyChildren_) {
        auto childNode = child->GetHostNode();
        auto resetLayoutConstraint = ResetLayoutConstraintMinWidth(child, childConstraint);
        SelectOverlayRightClickMenuLayoutHelper::AdjustLayoutConstraints(resetLayoutConstraint, child, layoutWrapper);
        if (pattern->IsEmbedded() && (resetLayoutConstraint.minSize.Width() > resetLayoutConstraint.maxSize.Width())) {
            resetLayoutConstraint.minSize.SetWidth(resetLayoutConstraint.maxSize.Width());
        }
        resetLayoutConstraint.parentIdealSize.SetSize(frameSize);
        if (childNode && childNode->GetLayoutProperty() && childNode->GetLayoutProperty()->IsExpandConstraintNeeded()) {
            child->GetGeometryNode()->SetParentLayoutConstraint(resetLayoutConstraint);
        }
    }
}

void MultiMenuLayoutAlgorithm::UpdateSelfSize(LayoutWrapper* layoutWrapper, LayoutConstraintF& childConstraint,
    std::optional<LayoutConstraintF>& layoutConstraint)
{
    auto node = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(node);
    auto pattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(pattern);

    float contentHeight = 0.0f;
    float contentWidth = childConstraint.selfIdealSize.Width().value_or(0.0f);
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        if (!child) {
            TAG_LOGW(AceLogTag::ACE_MENU, "child is null in MultiMenu");
            continue;
        }
        auto resetLayoutConstraint = ResetLayoutConstraintMinWidth(child, childConstraint);
        SelectOverlayRightClickMenuLayoutHelper::AdjustLayoutConstraints(
            resetLayoutConstraint, child, layoutWrapper);
        if (pattern->IsEmbedded() && (resetLayoutConstraint.minSize.Width() > resetLayoutConstraint.maxSize.Width())) {
            resetLayoutConstraint.minSize.SetWidth(resetLayoutConstraint.maxSize.Width());
        }
        child->Measure(resetLayoutConstraint);
        auto childGeometryNode = child->GetGeometryNode();
        CHECK_NULL_VOID(childGeometryNode);
        auto childHeight = childGeometryNode->GetMarginFrameSize().Height();
        if (pattern->IsEmbedded()) {
            childHeight = std::max(childHeight, childGeometryNode->GetContentSize().Height());
        }
        contentHeight += childHeight;
    }
    layoutWrapper->GetGeometryNode()->SetContentSize(SizeF(contentWidth, contentHeight));
    BoxLayoutAlgorithm::PerformMeasureSelf(layoutWrapper);

    // Stack or Embedded submenu must follow parent width
    if (pattern->IsStackSubmenu() || pattern->IsEmbedded()) {
        auto idealSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
        auto width = layoutConstraint->maxSize.Width();
        idealSize.SetWidth(width);
        if (pattern->IsEmbedded()) {
            auto idealHeight = GreatNotEqual(userHeight_, 0.0f) ? userHeight_ : contentHeight;
            idealSize.SetHeight(idealHeight);
        }
        layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
    } else if (layoutConstraint->selfIdealSize.Width().has_value()) {
        auto idealWidth = std::max(layoutConstraint->minSize.Width(),
            std::min(layoutConstraint->maxSize.Width(), layoutConstraint->selfIdealSize.Width().value()));
        auto idealSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
        idealSize.SetWidth(idealWidth);
        layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
    }
    if (pattern->IsEnableChildrenMatchParent()) {
        MeasureAdaptiveLayoutChildren(layoutWrapper, childConstraint);
    }
}

void MultiMenuLayoutAlgorithm::UpdateConstraintBaseOnMenuItems(
    LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint)
{
    // multiMenu children are menuItem or menuItemGroup, constrain width is same as the menu
    auto maxChildrenWidth = GetChildrenMaxWidth(layoutWrapper, constraint);
    constraint.selfIdealSize.SetWidth(maxChildrenWidth);
}

float MultiMenuLayoutAlgorithm::GetChildrenMaxWidth(
    LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint)
{
    float maxWidth = 0.0f;
    auto node = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(node, maxWidth);
    auto pattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(pattern, maxWidth);
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        auto childConstraint = ResetLayoutConstraintMinWidth(child, layoutConstraint);
        if (pattern->IsEmbedded() && (childConstraint.minSize.Width() > childConstraint.maxSize.Width())) {
            childConstraint.minSize.SetWidth(childConstraint.maxSize.Width());
        }
        SelectOverlayRightClickMenuLayoutHelper::AdjustLayoutConstraintsAutoWidth(child, layoutWrapper);
        auto childLayoutProperty = child->GetLayoutProperty();
        if (childLayoutProperty) {
            auto layoutPolicy = childLayoutProperty->GetLayoutPolicyProperty();
            if (layoutPolicy->IsMatch()) {
                continue;
            }
        }
        child->Measure(childConstraint);
        auto childSize = child->GetGeometryNode()->GetMarginFrameSize();
        maxWidth = std::max(maxWidth, childSize.Width());
    }
    return maxWidth;
}

LayoutConstraintF MultiMenuLayoutAlgorithm::ResetLayoutConstraintMinWidth(
    const RefPtr<LayoutWrapper>& child, const LayoutConstraintF& layoutConstraint)
{
    auto childLayoutProps = child->GetLayoutProperty();
    CHECK_NULL_RETURN(childLayoutProps, layoutConstraint);
    auto childConstraint = layoutConstraint;
    const auto& calcConstraint = childLayoutProps->GetCalcLayoutConstraint();
    if (calcConstraint && calcConstraint->selfIdealSize.has_value() &&
        calcConstraint->selfIdealSize.value().Width().has_value()) {
        childConstraint.minSize.Reset();
    }
    return childConstraint;
}

bool MultiMenuLayoutAlgorithm::UpdateSelectOverlayMenuMinWidth(
    const RefPtr<MenuPattern>& pattern, const RefPtr<GridColumnInfo>& columnInfo)
{
    CHECK_NULL_RETURN(pattern, false);
    auto mainMenuPattern = pattern->GetMainMenuPattern();
    CHECK_NULL_RETURN(mainMenuPattern, false);
    CHECK_NULL_RETURN(mainMenuPattern->IsSelectOverlayRightClickMenu(), false);
    auto menuWrapper = pattern->GetMenuWrapper();
    CHECK_NULL_RETURN(menuWrapper, false);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(menuWrapperPattern, false);
    CHECK_NULL_RETURN(menuWrapperPattern->GetIsSelectOverlaySubWindowWrapper(), false);
    auto mainWindowContainerId = menuWrapperPattern->GetContainerId();
    auto container = Container::GetContainer(mainWindowContainerId);
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(pipelineContext, false);
    auto displayWindowRect = pipelineContext->GetDisplayWindowRectInfo();
    auto mainWindowWidth = displayWindowRect.Width();
    if (Positive(mainWindowWidth)) {
        auto parent = columnInfo->GetParent();
        CHECK_NULL_RETURN(parent, false);
        parent->BuildColumnWidth(mainWindowWidth);
        TAG_LOGD(
            AceLogTag::ACE_MENU, "Update select overlay right click menu min width with main window width constraint.");
        return true;
    }
    return false;
}
} // namespace OHOS::Ace::NG
