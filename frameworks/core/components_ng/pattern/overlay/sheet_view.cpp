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

#include "base/i18n/localization.h"
#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_paint_property.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_property.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"
#include "core/components_ng/pattern/sheet/sheet_mask_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SHEET_DETENTS_TWO = 2;
constexpr int32_t SHEET_DETENTS_THREE = 3;
constexpr Dimension WINDOW_RADIUS = 16.0_vp;
} // namespace
RefPtr<FrameNode> SheetView::CreateSheetPage(int32_t targetId, std::string targetTag, RefPtr<UINode> builder,
    RefPtr<FrameNode> titleBuilder, std::function<void(const std::string&)>&& callback, NG::SheetStyle& sheetStyle)
{
    // create sheet node
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::SHEET_PAGE_TAG, targetId);
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(targetId, targetTag, std::move(callback)));
    sheetNode->SetDragHitTestBlock(true);
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(sheetLayoutProperty, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, nullptr);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    auto eventConfirmHub = sheetNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(eventConfirmHub, nullptr);
    eventConfirmHub->AddClickEvent(AceType::MakeRefPtr<NG::ClickEvent>(
        [](const GestureEvent& /* info */) { TAG_LOGD(AceLogTag::ACE_SHEET, "The sheet hits the click event."); }));
    sheetPattern->UpdateSheetType();
    auto operationColumn = CreateOperationColumnNode(titleBuilder, sheetStyle, sheetNode);
    CHECK_NULL_RETURN(operationColumn, nullptr);
    operationColumn->MountToParent(sheetNode);
    sheetPattern->SetTitleBuilderNode(WeakPtr<FrameNode>(operationColumn));
    auto scrollNode = CreateScrollNode(sheetStyle);
    CHECK_NULL_RETURN(scrollNode, nullptr);
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scrollNode));
    builder->MountToParent(scrollNode);

    auto layoutProperty = scrollNode->GetLayoutProperty<ScrollLayoutProperty>();
    scrollNode->MountToParent(sheetNode);
    layoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    CreateCloseIconButtonNode(sheetNode, sheetStyle);
    sheetNode->MarkModifyDone();
    return sheetNode;
}

RefPtr<FrameNode> SheetView::CreateOperationColumnNode(
    RefPtr<FrameNode> titleBuilder, NG::SheetStyle& sheetStyle, RefPtr<FrameNode> sheetNode)
{
    auto operationColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    CHECK_NULL_RETURN(operationColumn, nullptr);
    auto layoutProps = operationColumn->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(layoutProps, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_RETURN(sheetTheme, nullptr);
    auto sheetDragBarHeight = sheetTheme->GetSheetDragBarHeight();
    MarginProperty margin;
    margin.right = CalcLength(sheetTheme->GetTitleTextHorizMargin());
    margin.left = CalcLength(sheetTheme->GetTitleTextHorizMargin());
    layoutProps->UpdateMargin(margin);

    layoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS);
    if (sheetStyle.isTitleBuilder.has_value() && pipeline->GetFontScale() == sheetTheme->GetSheetNormalScale()) {
        layoutProps->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(
            sheetTheme->GetOperationAreaHeight() - sheetTheme->GetSheetTitleAreaMargin())));
        if (sheetStyle.sheetTitle.has_value() && sheetStyle.sheetSubtitle.has_value()) {
            layoutProps->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(
                SHEET_OPERATION_AREA_HEIGHT_DOUBLE - sheetTheme->GetSheetTitleAreaMargin())));
        }
    }
    CreateDragBarNode(titleBuilder, operationColumn, sheetStyle, sheetNode, sheetDragBarHeight);
    return operationColumn;
}

void SheetView::CreateDragBarNode(const RefPtr<FrameNode>& titleBuilder, const RefPtr<FrameNode>& operationColumn,
    NG::SheetStyle& sheetStyle, const RefPtr<FrameNode>& sheetNode, Dimension sheetDragBarHeight)
{
    auto dragBarNode = FrameNode::GetOrCreateFrameNode("SheetDragBar", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SheetDragBarPattern>(); });
    auto dragBarLayoutProperty = dragBarNode->GetLayoutProperty();
    CHECK_NULL_VOID(dragBarLayoutProperty);
    dragBarLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SHEET_DRAG_BAR_WIDTH), CalcLength(sheetDragBarHeight)));
    dragBarLayoutProperty->UpdateAlignment(Alignment::CENTER);
    auto showDragIndicator = sheetStyle.showDragBar.value_or(true);
    auto isSingleDetents = true;
    if (sheetStyle.detents.size() == SHEET_DETENTS_TWO) {
        isSingleDetents = sheetStyle.detents[0] == sheetStyle.detents[1];
    } else if (sheetStyle.detents.size() == SHEET_DETENTS_THREE) {
        isSingleDetents = sheetStyle.detents[0] == sheetStyle.detents[1] &&
                          sheetStyle.detents[1] == sheetStyle.detents[SHEET_DETENTS_TWO];
    }

    // 1. showDragBar && not single detents && sheet in bottom style (only bottom style can show drag bar)
    // 2. has SystemTitleBar
    // need set drag bar invisible to occupy place
    CHECK_NULL_VOID(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    if ((!isSingleDetents && showDragIndicator && sheetPattern->IsSheetBottomStyle())
        || sheetStyle.isTitleBuilder.has_value()) {
        dragBarLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
    } else {
        dragBarLayoutProperty->UpdateVisibility(VisibleType::GONE);
    }

    dragBarNode->MountToParent(operationColumn);
    dragBarNode->MarkModifyDone();

    if (sheetStyle.isTitleBuilder.has_value()) {
        auto titleColumn = BuildTitleColumn(sheetNode, sheetStyle);
        if (titleColumn) {
            if ((titleBuilder) && (sheetStyle.isTitleBuilder.value())) {
                titleColumn->AddChild(titleBuilder);
                titleBuilder->MarkModifyDone();
            }
            titleColumn->MountToParent(operationColumn);
            titleColumn->GetRenderContext()->SetClipToBounds(true);
            titleColumn->GetRenderContext()->UpdateClipEdge(true);
        }
    }
}

void SheetView::CreateCloseIconButtonNode(RefPtr<FrameNode> sheetNode, NG::SheetStyle& sheetStyle)
{
    if (!Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        return;
    }
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_VOID(buttonNode);
    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    buttonNode->GetRenderContext()->UpdateBackgroundColor(sheetTheme->GetCloseIconColor());
    buttonLayoutProperty->UpdateType(ButtonType::NORMAL);
    BorderRadiusProperty borderRaduis;
    borderRaduis.SetRadius(sheetTheme->GetCloseIconRadius());
    buttonLayoutProperty->UpdateBorderRadius(borderRaduis);
    buttonLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SHEET_CLOSE_ICON_WIDTH), CalcLength(SHEET_CLOSE_ICON_HEIGHT)));
    buttonLayoutProperty->UpdateVisibility(VisibleType::GONE);
    auto eventConfirmHub = buttonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(eventConfirmHub);
    auto clickCallback = [weak = AceType::WeakClaim(AceType::RawPtr(sheetNode))](const GestureEvent& /* info */) {
        auto sheet = weak.Upgrade();
        CHECK_NULL_VOID(sheet);
        auto sheetPattern = sheet->GetPattern<SheetPresentationPattern>();
        CHECK_NULL_VOID(sheetPattern);
        sheetPattern->SheetInteractiveDismiss(BindSheetDismissReason::CLOSE_BUTTON);
    };
    eventConfirmHub->AddClickEvent(AceType::MakeRefPtr<NG::ClickEvent>(clickCallback));
    // make the close button focusable when press tab
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetFocusDependence(FocusDependence::SELF);
    buttonNode->MarkModifyDone();

    CreateCloseIconNode(buttonNode);
    buttonNode->MountToParent(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->SetCloseButtonNode(WeakPtr<FrameNode>(buttonNode));

    // set accessibilityProperty to sheet close button
    auto accessibilityProperty = buttonNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    std::string message  = Localization::GetInstance()->GetEntryLetters("sheet.close");
    accessibilityProperty->SetAccessibilityText(message);
}

void SheetView::CreateCloseIconNode(RefPtr<FrameNode> buttonNode)
{
    auto pipeline = buttonNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    RefPtr<FrameNode> iconNode;

    // when api >= 12, use symbol format image, else use image format.
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE) &&
        SystemProperties::IsNeedSymbol()) {
        iconNode = FrameNode::CreateFrameNode(
            V2::SYMBOL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_VOID(iconNode);
        auto symbolLayoutProperty = iconNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(symbolLayoutProperty);
        uint32_t symbolId = sheetTheme->GetCloseIconSource();
        symbolLayoutProperty->UpdateSymbolSourceInfo(SymbolSourceInfo{symbolId});
        symbolLayoutProperty->UpdateFontSize(sheetTheme->GetCloseIconWidth());
        symbolLayoutProperty->UpdateSymbolColorList({sheetTheme->GetCloseIconSymbolColor()});
    } else {
        iconNode = FrameNode::CreateFrameNode(
            V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
        CHECK_NULL_VOID(iconNode);
        auto imageLayoutProperty = iconNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        imageLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(SHEET_CLOSE_ICON_IMAGE_HEIGHT), CalcLength(SHEET_CLOSE_ICON_IMAGE_HEIGHT)));
        imageLayoutProperty->UpdateImageFit(ImageFit::FILL);
        ImageSourceInfo imageSourceInfo;
        imageSourceInfo.SetResourceId(InternalResource::ResourceId::IC_CANCEL_SVG);
        imageSourceInfo.SetFillColor(sheetTheme->GetCloseIconImageColor());
        imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    }
    iconNode->MarkModifyDone();
    buttonNode->AddChild(iconNode);
}

RefPtr<FrameNode> SheetView::CreateScrollNode(const NG::SheetStyle& sheetStyle)
{
    auto scroll = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
    CHECK_NULL_RETURN(scroll, nullptr);
    auto props = scroll->GetLayoutProperty<ScrollLayoutProperty>();
    CHECK_NULL_RETURN(props, nullptr);
    props->UpdateScrollEnabled(true);
    props->UpdateAxis(Axis::VERTICAL);
    auto paintProps = scroll->GetPaintProperty<ScrollablePaintProperty>();
    CHECK_NULL_RETURN(paintProps, nullptr);
    paintProps->UpdateScrollBarMode(DisplayMode::OFF);
    auto pattern = scroll->GetPattern<ScrollablePattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    if (sheetStyle.sheetEffectEdge.has_value() && sheetStyle.sheetEffectEdge.value() == NG::SheetEffectEdge::NONE) {
        pattern->SetEdgeEffect(EdgeEffect::NONE, false);
    } else {
        pattern->SetEdgeEffect(EdgeEffect::SPRING,
            false, static_cast<EffectEdge>(sheetStyle.sheetEffectEdge.value_or(NG::SheetEffectEdge::ALL)));
    }
    pattern->SetScrollToSafeAreaHelper(false);
    props->UpdateAlignment(Alignment::TOP_CENTER);
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        NestedScrollOptions nestedOpt = {
            .forward = NestedScrollMode::PARENT_FIRST,
            .backward = NestedScrollMode::SELF_FIRST,
        };
        pattern->SetNestedScroll(nestedOpt);
    }
    scroll->MarkModifyDone();
    return scroll;
}

RefPtr<FrameNode> SheetView::BuildMainTitle(RefPtr<FrameNode> sheetNode, NG::SheetStyle& sheetStyle)
{
    auto pattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto titleId = pattern->GetTitleId();
    pattern->SetTitleId(titleId);
    auto sheetTitle = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, titleId, AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(sheetTitle, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_RETURN(sheetTheme, nullptr);
    auto titleProp = sheetTitle->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(titleProp, nullptr);
    auto titleTextFontSize = sheetTheme->GetTitleTextFontSize();
    auto sheetTitleFontWeight = sheetTheme->GetSheetTitleFontWeight();
    titleTextFontSize.SetUnit(DimensionUnit::FP);
    titleProp->UpdateMaxLines(SHEET_TITLE_MAX_LINES);
    titleProp->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    titleProp->UpdateAdaptMaxFontSize(titleTextFontSize);
    titleProp->UpdateAdaptMinFontSize(titleTextFontSize);
    if (sheetStyle.sheetTitle.has_value()) {
        titleProp->UpdateContent(sheetStyle.sheetTitle.value());
    }
    titleProp->UpdateMaxFontScale(sheetTheme->GetSheetMaxAgingScale());
    titleProp->UpdateFontSize(titleTextFontSize);
    titleProp->UpdateFontWeight(sheetTitleFontWeight);
    titleProp->UpdateTextColor(sheetTheme->GetTitleTextFontColor());

    auto titleRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(titleRow, nullptr);
    auto titleRowProps = titleRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(titleRowProps, nullptr);
    titleRowProps->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    titleRowProps->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    sheetTitle->MountToParent(titleRow);
    sheetTitle->MarkModifyDone();
    return titleRow;
}

RefPtr<FrameNode> SheetView::BuildSubTitle(RefPtr<FrameNode> sheetNode, NG::SheetStyle& sheetStyle)
{
    CHECK_NULL_RETURN(sheetNode, nullptr);
    auto pattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto subtitleId = pattern->GetSubtitleId();
    pattern->SetSubtitleId(subtitleId);
    auto sheetSubtitle = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, subtitleId, AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(sheetSubtitle, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_RETURN(sheetTheme, nullptr);
    auto titleProp = AceType::DynamicCast<TextLayoutProperty>(sheetSubtitle->GetLayoutProperty());
    CHECK_NULL_RETURN(titleProp, nullptr);
    auto titleTextFontSize = sheetTheme->GetSubtitleTextFontSize();
    titleTextFontSize.SetUnit(DimensionUnit::VP);
    titleProp->UpdateMaxLines(SHEET_TITLE_MAX_LINES);
    titleProp->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    titleProp->UpdateAdaptMaxFontSize(titleTextFontSize);
    titleProp->UpdateAdaptMinFontSize(titleTextFontSize);
    if (sheetStyle.sheetSubtitle.has_value()) {
        titleProp->UpdateContent(sheetStyle.sheetSubtitle.value());
    }
    titleProp->UpdateFontSize(titleTextFontSize);
    titleProp->UpdateTextColor(sheetTheme->GetSubtitleTextFontColor());
    PaddingProperty titlePadding;
    titlePadding.top = CalcLength(sheetTheme->GetSubtitleTextMargin());
    titleProp->UpdatePadding(titlePadding);

    auto subtitleRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));
    CHECK_NULL_RETURN(subtitleRow, nullptr);
    auto subtitleRowProps = subtitleRow->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(subtitleRowProps, nullptr);
    subtitleRowProps->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    subtitleRowProps->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    sheetSubtitle->MountToParent(subtitleRow);
    sheetSubtitle->MarkModifyDone();
    return subtitleRow;
}

void SheetView::SetTitleColumnMinSize(RefPtr<LayoutProperty> layoutProperty, const NG::SheetStyle& sheetStyle)
{
    if (sheetStyle.sheetTitle.has_value()) {
        layoutProperty->UpdateCalcMinSize(CalcSize(std::nullopt, CalcLength(SHEET_OPERATION_AREA_HEIGHT)));
        if (sheetStyle.sheetSubtitle.has_value()) {
            layoutProperty->UpdateCalcMinSize(CalcSize(
                std::nullopt, CalcLength(SHEET_OPERATION_AREA_HEIGHT_DOUBLE - SHEET_DOUBLE_TITLE_BOTTON_MARGIN)));
        }
    }
}

RefPtr<FrameNode> SheetView::CreateSheetMaskShowInSubwindow(const RefPtr<FrameNode>& sheetPageNode,
    const RefPtr<FrameNode>& sheetWrapperNode, const RefPtr<FrameNode>& targetNode, NG::SheetStyle& sheetStyle)
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    if (!container->IsSubContainer()) {
        return nullptr;
    }
    // create and mount sheetWrapperNode
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    CHECK_NULL_RETURN(sheetWrapperPattern, nullptr);
    auto maskNode = FrameNode::CreateFrameNode("SheetMask", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetMaskPattern>(targetNode->GetId(), targetNode->GetTag()));
    CHECK_NULL_RETURN(maskNode, nullptr);
    if (sheetWrapperPattern->ShowInUEC()) {
        auto maskRenderContext = maskNode->GetRenderContext();
        CHECK_NULL_RETURN(maskRenderContext, nullptr);
        BorderRadiusProperty borderRadius;
        borderRadius.SetRadius(WINDOW_RADIUS);
        maskRenderContext->UpdateBorderRadius(borderRadius);
        maskNode->MountToParent(sheetWrapperNode);
    } else {
        auto subwindowId = sheetWrapperPattern->GetSubWindowId();
        auto mainWindowId = SubwindowManager::GetInstance()->GetParentContainerId(subwindowId);
        auto mainWindowContext = PipelineContext::GetContextByContainerId(mainWindowId);
        CHECK_NULL_RETURN(mainWindowContext, nullptr);
        auto overlayManager = mainWindowContext->GetOverlayManager();
        CHECK_NULL_RETURN(overlayManager, nullptr);
        auto mainWindowRoot = overlayManager->GetRootNode().Upgrade();
        CHECK_NULL_RETURN(mainWindowRoot, nullptr);
        overlayManager->MountToParentWithService(mainWindowRoot, maskNode);
        mainWindowRoot->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    TAG_LOGI(AceLogTag::ACE_SHEET, "show in subwindow mount sheet page node");
    sheetPageNode->MountToParent(sheetWrapperNode);
    sheetWrapperPattern->SetSheetMaskNode(maskNode);
    sheetWrapperPattern->SetSheetPageNode(sheetPageNode);
    return maskNode;
}

RefPtr<FrameNode> SheetView::BuildTitleColumn(RefPtr<FrameNode> sheetNode, NG::SheetStyle& sheetStyle)
{
    auto titleColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    CHECK_NULL_RETURN(titleColumn, nullptr);
    auto layoutProperty = titleColumn->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    SetTitleColumnMinSize(layoutProperty, sheetStyle);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_RETURN(sheetTheme, nullptr);
    layoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS);
    bool isTitleCustombuilder = sheetStyle.isTitleBuilder.has_value() && sheetStyle.isTitleBuilder.value();
    if (pipeline->GetFontScale() == sheetTheme->GetSheetNormalScale() || isTitleCustombuilder) {
        layoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(std::nullopt, CalcLength(sheetTheme->GetOperationAreaHeight())));
    }
    MarginProperty margin;
    margin.top = CalcLength(sheetTheme->GetSheetTitleAreaMargin());
    margin.bottom = CalcLength(SHEET_DOUBLE_TITLE_BOTTON_MARGIN);
    layoutProperty->UpdateMargin(margin);
    auto columnProps = titleColumn->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(columnProps, nullptr);
    columnProps->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    if (sheetStyle.sheetTitle.has_value()) {
        auto titleRow = BuildMainTitle(sheetNode, sheetStyle);
        CHECK_NULL_RETURN(titleRow, nullptr);
        titleRow->MountToParent(titleColumn);
        MarginProperty titleMargin;
        titleMargin.top = CalcLength(sheetTheme->GetTitleTopPadding());
        auto titleProp = titleRow->GetLayoutProperty();
        CHECK_NULL_RETURN(titleProp, nullptr);
        titleProp->UpdateMargin(titleMargin);
        if (sheetStyle.sheetSubtitle.has_value()) {
            auto subtitleRow = BuildSubTitle(sheetNode, sheetStyle);
            CHECK_NULL_RETURN(subtitleRow, nullptr);
            subtitleRow->MountToParent(titleColumn);
            if (pipeline->GetFontScale() == sheetTheme->GetSheetNormalScale()) {
                layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(
                    SHEET_OPERATION_AREA_HEIGHT_DOUBLE - SHEET_DOUBLE_TITLE_BOTTON_MARGIN)));
            }
        }
    } else if (sheetStyle.isTitleBuilder.has_value()) {
        auto isCustomBuilder = sheetStyle.isTitleBuilder.value();
		
        // When title is custombuilder, set FlexAlign to CENTER.
        if (isCustomBuilder) {
            columnProps->UpdateMainAxisAlign(FlexAlign::CENTER);
        }
    }
    return titleColumn;
}
} // namespace OHOS::Ace::NG
