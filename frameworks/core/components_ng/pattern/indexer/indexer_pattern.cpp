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

#include "core/components_ng/pattern/indexer/indexer_pattern.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/popup_param.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/indexer/indexer_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/indexer/indexer_theme.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/list/list_item_layout_property.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_model.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_v2/list/list_properties.h"
#include "core/event/mouse_event.h"
#include "core/gestures/gesture_info.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void IndexerPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto layoutProperty = host->GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetArrayValue().has_value()) {
        arrayValue_ = layoutProperty->GetArrayValue().value();
        itemCount_ = static_cast<int32_t>(arrayValue_.size());
    }

    if (layoutProperty->GetSelected().has_value() &&
        (selected_ != layoutProperty->GetSelected().value() || !initialized_)) {
        auto propSelect = layoutProperty->GetSelected().value();
        selected_ = (propSelect >= 0 && propSelect < itemCount_) ? propSelect : 0;
        ResetStatus();
        ApplyIndexChanged(initialized_);
        initialized_ = true;
    }

    auto gesture = host->GetOrCreateGestureEventHub();
    if (gesture) {
        InitPanEvent(gesture);
    }
    InitInputEvent();
    if (!touchListener_) {
        CHECK_NULL_VOID(gesture);
        auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
            auto indexerPattern = weak.Upgrade();
            CHECK_NULL_VOID(indexerPattern);
            if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
                indexerPattern->OnTouchDown(info);
            } else if (info.GetTouches().front().GetTouchType() == TouchType::UP) {
                indexerPattern->OnTouchUp(info);
            }
        };
        touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
        gesture->AddTouchEvent(touchListener_);
    }
    InitOnKeyEvent();
}

bool IndexerPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto indexerLayoutAlgorithm = DynamicCast<IndexerLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(indexerLayoutAlgorithm, false);
    itemSizeRender_ = indexerLayoutAlgorithm->GetItemSizeRender();
    return true;
}

void IndexerPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (panEvent_) {
        return;
    }
    auto onActionStart = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            if (info.GetInputEventType() == InputEventType::AXIS) {
                return;
            }
            pattern->MoveIndexByOffset(info.GetLocalLocation());
        }
    };

    auto onActionUpdate = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        if (info.GetInputEventType() == InputEventType::AXIS) {
            if (GreatNotEqual(info.GetMainDelta(), 0.0)) {
                pattern->MoveIndexByStep(-1);
            } else if (LessNotEqual(info.GetMainDelta(), 0.0)) {
                pattern->MoveIndexByStep(1);
            }
        } else {
            pattern->MoveIndexByOffset(info.GetLocalLocation());
        }
    };

    auto onActionEnd = [weak = WeakClaim(this)](const GestureEvent& info) {};

    auto onActionCancel = [weak = WeakClaim(this)]() {};

    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(onActionStart), std::move(onActionUpdate), std::move(onActionEnd), std::move(onActionCancel));
    gestureHub->AddPanEvent(panEvent_, panDirection, 1, 0.0);
}

void IndexerPattern::OnHover(bool isHover)
{
    isHover_ = isHover;
    isTouch_ = false;
    ApplyIndexChanged(false);
}

void IndexerPattern::OnChildHover(int32_t index, bool isHover)
{
    childHoverIndex_ = isHover ? index : -1;
    auto refreshBubble = false;
    if (selected_ != childFocusIndex_) {
        selected_ = childFocusIndex_;
        refreshBubble = true;
    }
    ApplyIndexChanged(refreshBubble);
}

void IndexerPattern::InitInputEvent()
{
    if (isInputEventRegisted_) {
        return;
    }
    isInputEventRegisted_ = true;
    InitCurrentInputEvent();
    InitChildInputEvent();
}

void IndexerPattern::InitCurrentInputEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hoverCallback = [weak = WeakClaim(this)](bool isHovered) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnHover(isHovered);
    };
    auto hoverEvent = MakeRefPtr<InputEvent>(hoverCallback);
    auto inputGesture = host->GetOrCreateInputEventHub();
    inputGesture->AddOnHoverEvent(hoverEvent);
}

void IndexerPattern::InitChildInputEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    for (int32_t i = 0; i < itemCount_; i++) {
        auto child = DynamicCast<FrameNode>(host->GetChildAtIndex(i));
        CHECK_NULL_VOID(child);
        auto childHoverCallback = [weak = WeakClaim(this), index = i](bool isHovered) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnChildHover(index, isHovered);
        };
        auto childOnHoverEvent = MakeRefPtr<InputEvent>(childHoverCallback);
        auto childInputEventHub = child->GetOrCreateInputEventHub();
        childInputEventHub->AddOnHoverEvent(childOnHoverEvent);
    };
}

void IndexerPattern::OnTouchDown(const TouchEventInfo& info)
{
    MoveIndexByOffset(info.GetTouches().front().GetLocalLocation());
}

void IndexerPattern::OnTouchUp(const TouchEventInfo& info)
{
    childPressIndex_ = -1;
    auto nextSelectIndex = GetSelectChildIndex(info.GetTouches().front().GetLocalLocation());
    auto refreshBubble = false;
    if (nextSelectIndex != selected_) {
        selected_ = nextSelectIndex;
        refreshBubble = true;
        ResetStatus();
    }
    ApplyIndexChanged(refreshBubble);
}

void IndexerPattern::MoveIndexByOffset(const Offset& offset)
{
    if (itemSizeRender_ <= 0) {
        return;
    }
    if (itemCount_ <= 0) {
        LOGE("AlphabetIndexer arrayValue size is less than 0");
        return;
    }
    auto nextSelectIndex = GetSelectChildIndex(offset);
    if (nextSelectIndex == childPressIndex_) {
        return;
    }
    childPressIndex_ = nextSelectIndex;
    auto refreshBubble = false;
    if (selected_ != childPressIndex_) {
        selected_ = childPressIndex_;
        refreshBubble = true;
    }
    childFocusIndex_ = -1;
    childHoverIndex_ = -1;
    ApplyIndexChanged(refreshBubble);
}

int32_t IndexerPattern::GetSelectChildIndex(const Offset& offset)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, -1);
    auto layoutProperty = host->GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, -1);

    auto size = SizeF(itemSizeRender_, itemSizeRender_ * static_cast<float>(itemCount_));
    auto padding = layoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto top = padding.top.value_or(0.0f);
    auto nextSelectIndex = static_cast<int32_t>((offset.GetY() - top) / itemSizeRender_);
    nextSelectIndex = std::clamp(nextSelectIndex, 0, itemCount_ - 1);
    return nextSelectIndex;
}

bool IndexerPattern::KeyIndexByStep(int32_t step)
{
    auto nextSected = GetSkipChildIndex(step);
    if (childFocusIndex_ == nextSected || nextSected == -1) {
        return false;
    }
    childFocusIndex_ = nextSected;
    auto refreshBubble = false;
    if (nextSected >= 0) {
        selected_ = nextSected;
        refreshBubble = true;
    }
    childPressIndex_ = -1;
    childHoverIndex_ = -1;
    ApplyIndexChanged(refreshBubble);
    return nextSected >= 0;
}

int32_t IndexerPattern::GetSkipChildIndex(int32_t step)
{
    auto nextSelected = selected_ + step;
    if (nextSelected < 0 || nextSelected >= itemCount_) {
        return -1;
    }
    return nextSelected;
}

bool IndexerPattern::MoveIndexByStep(int32_t step)
{
    auto nextSected = GetSkipChildIndex(step);
    if (selected_ == nextSected || nextSected == -1) {
        return false;
    }
    selected_ = nextSected;
    ResetStatus();
    ApplyIndexChanged(true);
    return nextSected >= 0;
}

bool IndexerPattern::MoveIndexBySearch(const std::string& searchStr)
{
    auto nextSelectIndex = GetFocusChildIndex(searchStr);
    if (selected_ == nextSelectIndex || nextSelectIndex == -1) {
        return false;
    }
    selected_ = nextSelectIndex;
    childFocusIndex_ = nextSelectIndex;
    childHoverIndex_ = -1;
    childPressIndex_ = -1;
    ApplyIndexChanged(true);
    return nextSelectIndex >= 0;
}

int32_t IndexerPattern::GetFocusChildIndex(const std::string& searchStr)
{
    int32_t nextSelectIndex = -1;
    for (auto i = selected_ + 1; i < itemCount_; ++i) {
        const auto& indexValue = arrayValue_.at(i);
        if (searchStr.length() > indexValue.length()) {
            continue;
        }
        if (strcasecmp(indexValue.substr(0, searchStr.length()).c_str(), searchStr.c_str()) == 0) {
            nextSelectIndex = i;
            break;
        }
    }
    if (nextSelectIndex >= 0 && nextSelectIndex < itemCount_) {
        return nextSelectIndex;
    }
    for (auto i = 0; i < selected_; ++i) {
        const auto& indexValue = arrayValue_.at(i);
        if (searchStr.length() > indexValue.length()) {
            continue;
        }
        if (strcasecmp(indexValue.substr(0, searchStr.length()).c_str(), searchStr.c_str()) == 0) {
            nextSelectIndex = i;
            break;
        }
    }
    if (nextSelectIndex >= 0 && nextSelectIndex < itemCount_) {
        return nextSelectIndex;
    }
    return -1;
}

void IndexerPattern::ResetStatus()
{
    childHoverIndex_ = -1;
    childFocusIndex_ = -1;
    childPressIndex_ = -1;
}

void IndexerPattern::OnSelectChanged()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto indexerEventHub = host->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(indexerEventHub);
    auto onSelected = indexerEventHub->GetOnSelected();
    if (onSelected && (selected_ >= 0) && (selected_ < itemCount_)) {
        onSelected(selected_);
    }
}

void IndexerPattern::ApplyIndexChanged(bool selectChanged)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto indexerEventHub = host->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(indexerEventHub);
    auto paintProperty = host->GetPaintProperty<IndexerPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    auto currentRenderContext = host->GetRenderContext();
    CHECK_NULL_VOID(currentRenderContext);
    auto paddingLeft = CalcLength(Dimension(INDEXER_PADDING_LEFT, DimensionUnit::VP).ConvertToPx());
    auto paddingTop = CalcLength(Dimension(INDEXER_PADDING_TOP, DimensionUnit::VP).ConvertToPx());
    layoutProperty->UpdatePadding({ paddingLeft, paddingLeft, paddingTop, paddingTop });
    if (isHover_) {
        currentRenderContext->BlendBgColor(
            indexerTheme->GetSlipHoverBackgroundColor().ChangeOpacity(IndexerTheme::SLIP_BACKGROUND_OPACITY));
    } else {
        currentRenderContext->ResetBlendBgColor();
    }
    int32_t index = 0;
    auto childrenNode = host->GetChildren();
    for (auto& iter : childrenNode) {
        auto childNode = AceType::DynamicCast<FrameNode>(iter);
        auto nodeLayoutProperty = childNode->GetLayoutProperty<TextLayoutProperty>();
        auto childRenderContext = childNode->GetRenderContext();
        if (index == childHoverIndex_ || index == childPressIndex_) {
            auto radiusSize = indexerTheme->GetHoverRadiusSize();
            childRenderContext->UpdateBorderRadius({ radiusSize, radiusSize, radiusSize, radiusSize });
            childRenderContext->BlendBgColor(indexerTheme->GetHoverBgAreaColor());
            nodeLayoutProperty->UpdateTextColor(indexerTheme->GetHoverTextColor());
        } else if (index == childFocusIndex_ || index == selected_) {
            if (index == childFocusIndex_) {
                auto borderWidth = indexerTheme->GetFocusBgOutlineSize();
                nodeLayoutProperty->UpdateBorderWidth({ borderWidth, borderWidth, borderWidth, borderWidth });
                auto borderColor = indexerTheme->GetFocusBgOutlineColor();
                childRenderContext->UpdateBorderColor({ borderColor, borderColor, borderColor, borderColor });
            } else {
                Dimension borderWidth;
                nodeLayoutProperty->UpdateBorderWidth({ borderWidth, borderWidth, borderWidth, borderWidth });
                childRenderContext->ResetBlendBorderColor();
            }
            nodeLayoutProperty->UpdateTextColor(
                layoutProperty->GetSelectedColor().value_or(indexerTheme->GetSelectedTextColor()));
            childRenderContext->BlendBgColor(
                paintProperty->GetSelectedBackgroundColor().value_or(indexerTheme->GetSeclectedBackgroundColor()));
            auto radius = indexerTheme->GetHoverRadiusSize();
            childRenderContext->UpdateBorderRadius({ radius, radius, radius, radius });
            auto selectedFont = layoutProperty->GetSelectedFont().value_or(indexerTheme->GetSelectTextStyle());
            nodeLayoutProperty->UpdateFontSize(selectedFont.GetFontSize());
            auto fontWeight = selectedFont.GetFontWeight();
            nodeLayoutProperty->UpdateFontWeight(fontWeight);
            childRenderContext->SetClipToBounds(true);
            childNode->MarkModifyDone();
            index++;
            continue;
        } else {
            childRenderContext->ResetBlendBgColor();
            Dimension radiusZeroSize;
            childRenderContext->UpdateBorderRadius({ radiusZeroSize, radiusZeroSize, radiusZeroSize, radiusZeroSize });
            nodeLayoutProperty->UpdateTextColor(
                layoutProperty->GetColor().value_or(indexerTheme->GetDefaultTextColor()));
        }
        Dimension borderWidth;
        nodeLayoutProperty->UpdateBorderWidth({ borderWidth, borderWidth, borderWidth, borderWidth });
        childRenderContext->ResetBlendBorderColor();
        nodeLayoutProperty->UpdateFontSize(
            layoutProperty->GetFont().value_or(indexerTheme->GetDefaultTextStyle()).GetFontSize());
        nodeLayoutProperty->UpdateFontWeight(
            layoutProperty->GetFont().value_or(indexerTheme->GetDefaultTextStyle()).GetFontWeight());
        childNode->MarkModifyDone();
        index++;
    }
    if (selectChanged) {
        OnSelectChanged();
        ShowBubble();
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}
void IndexerPattern::ShowBubble()
{
    if (!NeedShowBubble()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto customNode = InitBubbleView();
    CHECK_NULL_VOID(customNode);
    SetPositionOfPopupNode(customNode);
    customNode->MarkModifyDone();
    customNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    overlayManager->ShowIndexerPopup(host->GetId(), customNode);
    removePopupNode_ = true;
    AddPopupTouchListener(customNode);
    BeginBubbleAnimation(customNode);
}

void IndexerPattern::SetPositionOfPopupNode(RefPtr<FrameNode>& customNode)
{
    CHECK_NULL_VOID(customNode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto indexerItemSize = Dimension(INDEXER_ITEM_SIZE, DimensionUnit::VP);
    auto itemSize = layoutProperty->GetItemSize().value_or(indexerItemSize);
    auto padding = layoutProperty->CreatePaddingAndBorder();
    auto indexerWidth = itemSize.ConvertToPx() + padding.left.value_or(0) + padding.right.value_or(0);
    auto layoutConstraint = layoutProperty->GetLayoutConstraint();
    if (layoutConstraint.has_value() && layoutConstraint->selfIdealSize.Width().has_value() &&
        (layoutConstraint->selfIdealSize.Width().value() > indexerWidth)) {
        indexerWidth = layoutConstraint->selfIdealSize.Width().value();
    }
    auto alignMent = layoutProperty->GetAlignStyle().value_or(NG::AlignStyle::RIGHT);
    auto userDefinePositionX = layoutProperty->GetPopupPositionX().value_or(NG::BUBBLE_POSITION_X);
    auto userDefinePositionY = layoutProperty->GetPopupPositionY().value_or(NG::BUBBLE_POSITION_Y);
    auto zeroPositionX = host->GetOffsetRelativeToWindow().GetX() + indexerWidth / 2;
    auto zeroPosiitonY = host->GetOffsetRelativeToWindow().GetY();
    auto renderContext = customNode->GetRenderContext();
    if (alignMent == NG::AlignStyle::LEFT) {
        renderContext->UpdatePosition(OffsetT<Dimension>(
            Dimension(zeroPositionX + userDefinePositionX), Dimension(zeroPosiitonY + userDefinePositionY)));
    } else {
        auto bubbleSize = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
        renderContext->UpdatePosition(OffsetT<Dimension>(Dimension(zeroPositionX - bubbleSize - userDefinePositionX),
            Dimension(zeroPosiitonY + userDefinePositionY)));
    }
}

RefPtr<FrameNode> IndexerPattern::InitBubbleView()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_RETURN(indexerTheme, nullptr);
    auto layoutProperty = host->GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    auto popupTextColor = layoutProperty->GetPopupColor().value_or(indexerTheme->GetPopupTextColor());
    auto popupTextFont = layoutProperty->GetPopupFont().value_or(indexerTheme->GetPopupTextStyle());
    auto paintProperty = host->GetPaintProperty<IndexerPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, nullptr);
    auto popupBackground = paintProperty->GetPopupBackground().value_or(indexerTheme->GetPopupBackgroundColor());
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    CHECK_NULL_RETURN(columnNode, nullptr);

    auto letterNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(letterNode, nullptr);
    auto letterLayoutProperty = letterNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(letterLayoutProperty, nullptr);
    letterLayoutProperty->UpdateContent(arrayValue_[selected_]);
    auto bubbleSize = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    letterLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(bubbleSize), CalcLength(bubbleSize)));
    auto fontSize = popupTextFont.GetFontSize();
    letterLayoutProperty->UpdateFontSize(fontSize);
    auto fontWeight = popupTextFont.GetFontWeight();
    letterLayoutProperty->UpdateFontWeight(fontWeight);
    letterLayoutProperty->UpdateTextColor(popupTextColor);
    letterLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    auto textPadding = Dimension(IndexerTheme::TEXT_PADDING_LEFT, DimensionUnit::VP).ConvertToPx();
    letterLayoutProperty->UpdatePadding(
        { CalcLength(textPadding), CalcLength(textPadding), CalcLength(0), CalcLength(0) });
    auto letterNodeRenderContext = letterNode->GetRenderContext();
    letterNodeRenderContext->UpdateBackgroundColor(popupBackground);
    letterNodeRenderContext->SetClipToBounds(true);
    columnNode->AddChild(letterNode);
    letterNode->MarkModifyDone();

    auto listNode = FrameNode::CreateFrameNode(
        V2::LIST_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ListPattern>());
    CHECK_NULL_RETURN(listNode, nullptr);
    auto indexerEventHub = host->GetEventHub<IndexerEventHub>();
    auto popListData = indexerEventHub->GetOnRequestPopupData();
    auto currentListData = popListData ? popListData(selected_) : std::vector<std::string>();
    auto popupSize = currentListData.size();
    auto listActualSize = popupSize < INDEXER_BUBBLE_MAXSIZE ? popupSize : INDEXER_BUBBLE_MAXSIZE;
    auto listLayoutProperty = listNode->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_RETURN(listLayoutProperty, nullptr);
    listLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(bubbleSize), CalcLength(bubbleSize * listActualSize)));
    auto borderWidthZero = Dimension();
    if (!currentListData.empty()) {
        letterLayoutProperty->UpdateBorderWidth(
            { borderWidthZero, borderWidthZero, borderWidthZero, Dimension(INDEXER_LIST_DIVIDER) });
        auto boderColor = BorderColorProperty();
        boderColor.bottomColor = indexerTheme->GetPopupSeparateColor();
        letterNodeRenderContext->UpdateBorderColor(boderColor);
        InitBubbleList(currentListData, listNode, indexerTheme);
    }
    auto divider = V2::ItemDivider();
    divider.strokeWidth = Dimension(INDEXER_LIST_DIVIDER);
    divider.color = indexerTheme->GetPopupSeparateColor();
    listLayoutProperty->UpdateDivider(divider);
    listLayoutProperty->UpdateListDirection(Axis::VERTICAL);
    columnNode->AddChild(listNode);
    listNode->MarkModifyDone();
    auto columnLayoutProperty = columnNode->GetLayoutProperty<LinearLayoutProperty>();
    auto columnCalcSize = CalcSize(CalcLength(bubbleSize), CalcLength(bubbleSize * (listActualSize + 1)));
    columnLayoutProperty->UpdateUserDefinedIdealSize(columnCalcSize);
    columnLayoutProperty->UpdateBorderWidth({ borderWidthZero, borderWidthZero, borderWidthZero, borderWidthZero });
    auto columnRenderContext = columnNode->GetRenderContext();
    columnRenderContext->UpdateBackgroundColor(indexerTheme->GetPopupBackgroundColor());
    auto radius = Dimension(BUBBLE_BOX_RADIUS, DimensionUnit::VP);
    columnRenderContext->UpdateBorderRadius({ radius, radius, radius, radius });
    columnRenderContext->UpdateBackShadow(ShadowConfig::DefaultShadowL);
    columnRenderContext->SetClipToBounds(true);
    return columnNode;
}

void IndexerPattern::InitBubbleList(
    std::vector<std::string>& currentListData, RefPtr<FrameNode>& listNode, RefPtr<IndexerTheme>& indexerTheme)
{
    CHECK_NULL_VOID(listNode);
    CHECK_NULL_VOID(indexerTheme);
    auto bubbleSize = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    for (uint32_t i = 0; i < currentListData.size(); i++) {
        auto listItemNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ListItemPattern>(nullptr));
        auto textNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        textLayoutProperty->UpdateContent(currentListData.at(i));
        textLayoutProperty->UpdateTextColor(indexerTheme->GetDefaultTextColor());
        textLayoutProperty->UpdateFontSize(indexerTheme->GetPopupTextSize());
        textLayoutProperty->UpdateFontWeight(indexerTheme->GetPopupTextStyle().GetFontWeight());
        textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
        textLayoutProperty->UpdateAlignment(Alignment::CENTER);
        listItemNode->AddChild(textNode);
        textNode->MarkModifyDone();
        auto listItemProperty = listItemNode->GetLayoutProperty<ListItemLayoutProperty>();
        listItemProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(bubbleSize), CalcLength(bubbleSize)));
        listItemProperty->UpdateAlignment(Alignment::CENTER);
        AddListItemClickListener(listItemNode, i);
        listNode->AddChild(listItemNode);
        listItemNode->MarkModifyDone();
    }
    auto listRenderContext = listNode->GetRenderContext();
    listRenderContext->SetClipToBounds(true);
}

void IndexerPattern::ChangeListItemsBgColor(int32_t clickIndex)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto popupNode = overlayManager->GetIndexerPopup(host->GetId());
    CHECK_NULL_VOID(popupNode);
    auto listNode = popupNode->GetLastChild();
    auto currentIndex = 0;
    for (auto child : listNode->GetChildren()) {
        auto listItemNode = DynamicCast<FrameNode>(child);
        auto listItemProperty = listItemNode->GetLayoutProperty<ListItemLayoutProperty>();
        auto listItemContext = listItemNode->GetRenderContext();
        if (currentIndex == clickIndex) {
            listItemContext->UpdateBackgroundColor(Color(POPUP_LISTITEM_CLICKED_BG));
        } else {
            listItemContext->UpdateBackgroundColor(Color::TRANSPARENT);
        }
        listItemNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        currentIndex++;
    }
}

void IndexerPattern::AddPopupTouchListener(RefPtr<FrameNode> popupNode)
{
    CHECK_NULL_VOID(popupNode);
    auto gesture = popupNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto indexerPattern = weak.Upgrade();
        CHECK_NULL_VOID(indexerPattern);
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            indexerPattern->OnPopupTouchDown(info);
        }
    };
    gesture->AddTouchEvent(MakeRefPtr<TouchEventImpl>(std::move(touchCallback)));
}

void IndexerPattern::AddListItemClickListener(RefPtr<FrameNode>& listItemNode, int32_t index)
{
    CHECK_NULL_VOID(listItemNode);
    auto gestureHub = listItemNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto clickEventFunc = [weak = WeakClaim(this), index](GestureEvent& gestureEvent) {
        auto indexerPattern = weak.Upgrade();
        CHECK_NULL_VOID(indexerPattern);
        indexerPattern->OnListItemClick(index);
    };
    gestureHub->SetUserOnClick(std::move(clickEventFunc));
}

void IndexerPattern::OnListItemClick(int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto indexerEventHub = host->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(indexerEventHub);
    auto onPopupSelected = indexerEventHub->GetOnPopupSelected();
    if (onPopupSelected) {
        onPopupSelected(index);
    }
    ChangeListItemsBgColor(index);
}

void IndexerPattern::OnPopupTouchDown(const TouchEventInfo& info)
{
    removePopupNode_ = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto popupNode = overlayManager->GetIndexerPopup(host->GetId());
    CHECK_NULL_VOID(popupNode);
    auto popupRenderContext = popupNode->GetRenderContext();
    popupRenderContext->UpdateOpacity(1.0);
}

bool IndexerPattern::NeedShowBubble()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto usePopup = layoutProperty->GetUsingPopup().value_or(false);
    return usePopup && IfSelectIndexValid();
}

bool IndexerPattern::IfSelectIndexValid()
{
    return (selected_ >= 0 && selected_ < static_cast<int32_t>(arrayValue_.size()));
}

void IndexerPattern::InitOnKeyEvent()
{
    if (isKeyEventRegisted_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN_NOLOG(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    isKeyEventRegisted_ = true;
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

bool IndexerPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if (event.code == KeyCode::KEY_DPAD_UP) {
        return KeyIndexByStep(-1);
    }
    if (event.code == KeyCode::KEY_DPAD_DOWN) {
        return KeyIndexByStep(1);
    }
    if (!event.IsCombinationKey() && (event.IsLetterKey() || event.IsNumberKey())) {
        return MoveIndexBySearch(event.ConvertCodeToString());
    }
    OnKeyEventDisapear();
    return false;
}

void IndexerPattern::OnKeyEventDisapear()
{
    ResetStatus();
    ApplyIndexChanged(false);
}

void IndexerPattern::BeginBubbleAnimation(RefPtr<FrameNode> animationNode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(animationNode);
    auto renderContext = animationNode->GetRenderContext();
    AnimationOption animationOption;
    animationOption.SetDuration(INDEXER_BUBBLE_ANIMATION_DURATION);
    animationOption.SetCurve(Curves::DECELE);
    animationOption.SetOnFinishEvent([targetId = host->GetId(), popnodeId = animationNode->GetId(),
                                         id = Container::CurrentId(), weak = WeakClaim(this)] {
        ContainerScope scope(id);
        auto indexerPattern = weak.Upgrade();
        CHECK_NULL_VOID(indexerPattern);
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto overlayManager = context->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        auto popupNode = overlayManager->GetIndexerPopup(targetId);
        CHECK_NULL_VOID(popupNode);
        if (!indexerPattern->removePopupNode_ || popupNode->GetId() != popnodeId) {
            return;
        }
        overlayManager->EraseIndexerPopup(targetId);
    });
    renderContext->OpacityAnimation(animationOption, 1.0f, 0.0f);
}
} // namespace OHOS::Ace::NG