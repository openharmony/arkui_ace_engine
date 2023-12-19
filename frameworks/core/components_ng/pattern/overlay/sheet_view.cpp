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
#include "core/components/common/layout/constants.h"
#include "core/components/drag_bar/drag_bar_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_paint_property.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_property.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> SheetView::CreateSheetPage(int32_t targetId, std::string targetTag, RefPtr<FrameNode> builder,
    RefPtr<FrameNode> titleBuilder, std::function<void(const std::string&)>&& callback, NG::SheetStyle& sheetStyle)
{
    // create sheet node
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::SHEET_PAGE_TAG, targetId);
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(targetId, targetTag, std::move(callback)));
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(sheetLayoutProperty, nullptr);
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    auto operationColumn = CreateOperationColumnNode(titleBuilder, sheetStyle, sheetNode);
    CHECK_NULL_RETURN(operationColumn, nullptr);
    operationColumn->MountToParent(sheetNode);
    auto scrollNode = CreateScrollNode();
    CHECK_NULL_RETURN(scrollNode, nullptr);
    builder->MountToParent(scrollNode);

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto inset = pipeline->GetSafeArea();
    auto layoutProperty = scrollNode->GetLayoutProperty<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollContentEndOffset(inset.bottom_.Length());
    scrollNode->MountToParent(sheetNode);
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
    MarginProperty margin;
    margin.right = CalcLength(sheetTheme->GetTitleTextMargin());
    margin.left = CalcLength(sheetTheme->GetTitleTextMargin());
    layoutProps->UpdateMargin(margin);

    layoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS);
    if (sheetStyle.isTitleBuilder.has_value()) {
        layoutProps->UpdateUserDefinedIdealSize(
            CalcSize(std::nullopt, CalcLength(SHEET_OPERATION_AREA_HEIGHT - SHEET_TITLE_AERA_MARGIN)));
        if (sheetStyle.sheetTitle.has_value() && sheetStyle.sheetSubtitle.has_value()) {
            layoutProps->UpdateUserDefinedIdealSize(
                CalcSize(std::nullopt, CalcLength(SHEET_OPERATION_AREA_HEIGHT_DOUBLE - SHEET_TITLE_AERA_MARGIN)));
        }
    }

    auto dragBarNode = FrameNode::GetOrCreateFrameNode("SheetDragBar", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<SheetDragBarPattern>(); });
    auto dragBarLayoutProperty = dragBarNode->GetLayoutProperty();
    CHECK_NULL_RETURN(dragBarLayoutProperty, nullptr);
    dragBarLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SHEET_DRAG_BAR_WIDTH), CalcLength(SHEET_DRAG_BAR_HEIGHT)));
    dragBarLayoutProperty->UpdateAlignment(Alignment::CENTER);
    dragBarLayoutProperty->UpdateVisibility(VisibleType::GONE);

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
    return operationColumn;
}

void SheetView::CreateCloseIconButtonNode(RefPtr<FrameNode> sheetNode, NG::SheetStyle& sheetStyle)
{
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
    buttonLayoutProperty->UpdateBorderRadius(
        { SHEET_CLOSE_ICON_RADIUS, SHEET_CLOSE_ICON_RADIUS, SHEET_CLOSE_ICON_RADIUS, SHEET_CLOSE_ICON_RADIUS });
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
        sheetPattern->SheetInteractiveDismiss(false);
    };
    eventConfirmHub->AddClickEvent(AceType::MakeRefPtr<NG::ClickEvent>(clickCallback));
    buttonNode->MarkModifyDone();

    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    imageLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SHEET_CLOSE_ICON_IMAGE_HEIGHT), CalcLength(SHEET_CLOSE_ICON_IMAGE_HEIGHT)));
    imageLayoutProperty->UpdateImageFit(ImageFit::FILL);
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetResourceId(InternalResource::ResourceId::IC_CANCEL_SVG);
    imageSourceInfo.SetFillColor(sheetTheme->GetCloseIconImageColor());
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    imageNode->MarkModifyDone();

    buttonNode->AddChild(imageNode);
    buttonNode->MountToParent(sheetNode);
}

RefPtr<FrameNode> SheetView::CreateScrollNode()
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
    pattern->SetEdgeEffect(EdgeEffect::SPRING, pattern->GetAlwaysEnabled());
    auto layoutProps = scroll->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProps, nullptr);
    layoutProps->UpdateAlignment(Alignment::TOP_CENTER);
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
    titleProp->UpdateMaxLines(1);
    titleProp->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    titleProp->UpdateAdaptMaxFontSize(sheetTheme->GetTitleTextFontSize());
    titleProp->UpdateAdaptMinFontSize(sheetTheme->GetTitleTextFontSize());
    if (sheetStyle.sheetTitle.has_value()) {
        titleProp->UpdateContent(sheetStyle.sheetTitle.value());
    }
    titleProp->UpdateFontSize(sheetTheme->GetTitleTextFontSize());
    titleProp->UpdateFontWeight(FontWeight::BOLD);
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
    titleProp->UpdateMaxLines(1);
    titleProp->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    titleProp->UpdateAdaptMaxFontSize(sheetTheme->GetSubtitleTextFontSize());
    titleProp->UpdateAdaptMinFontSize(sheetTheme->GetSubtitleTextFontSize());
    if (sheetStyle.sheetSubtitle.has_value()) {
        titleProp->UpdateContent(sheetStyle.sheetSubtitle.value());
    }
    titleProp->UpdateFontSize(sheetTheme->GetSubtitleTextFontSize());
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

RefPtr<FrameNode> SheetView::BuildTitleColumn(RefPtr<FrameNode> sheetNode, NG::SheetStyle& sheetStyle)
{
    auto titleColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    CHECK_NULL_RETURN(titleColumn, nullptr);
    auto layoutProperty = titleColumn->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    layoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS);
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(SHEET_OPERATION_AREA_HEIGHT)));
    MarginProperty margin;
    margin.top = CalcLength(SHEET_TITLE_AERA_MARGIN);
    layoutProperty->UpdateMargin(margin);
    PaddingProperty padding;
    padding.right = CalcLength(SHEET_CLOSE_ICON_TITLE_SPACE + SHEET_CLOSE_ICON_WIDTH);
    layoutProperty->UpdatePadding(padding);
    auto columnProps = titleColumn->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(columnProps, nullptr);
    columnProps->UpdateMainAxisAlign(FlexAlign::CENTER);
    columnProps->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    if (sheetStyle.sheetTitle.has_value()) {
        auto titleRow = BuildMainTitle(sheetNode, sheetStyle);
        CHECK_NULL_RETURN(titleRow, nullptr);
        titleRow->MountToParent(titleColumn);
        if (sheetStyle.sheetSubtitle.has_value()) {
            auto subtitleRow = BuildSubTitle(sheetNode, sheetStyle);
            CHECK_NULL_RETURN(subtitleRow, nullptr);
            subtitleRow->MountToParent(titleColumn);
            layoutProperty->UpdateUserDefinedIdealSize(
                CalcSize(std::nullopt, CalcLength(SHEET_OPERATION_AREA_HEIGHT_DOUBLE - SHEET_DRAG_BAR_HEIGHT)));
            MarginProperty margin;
            margin.bottom = CalcLength(SHEET_DOUBLE_TITLE_BOTTON_PADDING);
            layoutProperty->UpdateMargin(margin);
            MarginProperty titleMargin;
            titleMargin.top = CalcLength(SHEET_DOUBLE_TITLE_TOP_PADDING + SHEET_TITLE_AERA_MARGIN);
            auto titleProp = titleRow->GetLayoutProperty();
            CHECK_NULL_RETURN(titleProp, nullptr);
            titleProp->UpdateMargin(titleMargin);
        }
    }
    return titleColumn;
}
} // namespace OHOS::Ace::NG
