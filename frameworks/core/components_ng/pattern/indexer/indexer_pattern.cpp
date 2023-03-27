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
#include "core/animation/animator.h"
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
namespace {
constexpr int32_t TOTAL_NUMBER = 1000;
}
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
    auto propSelect = layoutProperty->GetSelected().value();
    propSelect = (propSelect >= 0 && propSelect < itemCount_) ? propSelect : 0;
    auto selectChanged = false;
    if (propSelect != lastSelectProp_) {
        selected_ = propSelect;
        lastSelectProp_ = propSelect;
        selectChanged = true;
        ResetStatus();
    }
    ApplyIndexChanged(initialized_ && selectChanged);
    initialized_ = true;

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
    if (isHover_ == isHover) {
        return;
    }
    isHover_ = isHover;
    isTouch_ = false;
    if (isHover_) {
        IndexerHoverInAnimation();
    } else {
        IndexerHoverOutAnimation();
    }
    ApplyIndexChanged(false);
}

void IndexerPattern::OnChildHover(int32_t index, bool isHover)
{
    childHoverIndex_ = isHover ? index : -1;
    ApplyIndexChanged(childHoverIndex_ >= 0 && childHoverIndex_ < itemCount_);
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
    if (isHover_) {
        IndexerPressOutAnimation();
    }
    auto nextSelectIndex = GetSelectChildIndex(info.GetTouches().front().GetLocalLocation());
    auto refreshBubble = false;
    selected_ = nextSelectIndex;
    refreshBubble = true;
    ResetStatus();
    ApplyIndexChanged(refreshBubble, true);
    OnSelect(refreshBubble);
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
    selected_ = nextSelectIndex;
    lastSelected_ = nextSelectIndex;
    if (isHover_ && childPressIndex_ >= 0) {
        IndexerPressInAnimation();
    }
    childFocusIndex_ = -1;
    childHoverIndex_ = -1;
    ApplyIndexChanged(true);
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
    auto refreshBubble = nextSected >= 0 && nextSected < itemCount_;
    if (refreshBubble) {
        selected_ = nextSected;
        lastSelected_ = nextSected;
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

void IndexerPattern::OnSelect(bool changed)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto indexerEventHub = host->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(indexerEventHub);
    auto onSelected = indexerEventHub->GetOnSelected();
    if (onSelected && (selected_ >= 0) && (selected_ < itemCount_)) {
        onSelected(selected_);
    }
    animateSelected_ = selected_;
    if (animateSelected_ >= 0) {
        auto selectedFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(animateSelected_));
        CHECK_NULL_VOID(selectedFrameNode);
        ItemSelectedInAnimation(selectedFrameNode);
    }
    if (lastSelected_ >= 0 && lastSelected_ != animateSelected_) {
        auto lastFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(lastSelected_));
        CHECK_NULL_VOID(lastFrameNode);
        ItemSelectedOutAnimation(lastFrameNode);
    }
    lastSelected_ = selected_;
}

void IndexerPattern::ApplyIndexChanged(bool selectChanged, bool fromTouchUp)
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
    int32_t index = 0;
    auto childrenNode = host->GetChildren();
    for (auto& iter : childrenNode) {
        auto childNode = AceType::DynamicCast<FrameNode>(iter);
        auto nodeLayoutProperty = childNode->GetLayoutProperty<TextLayoutProperty>();
        nodeLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
        auto childRenderContext = childNode->GetRenderContext();
        if (index == childHoverIndex_ || index == childPressIndex_) {
            auto radiusSize = indexerTheme->GetHoverRadiusSize();
            childRenderContext->UpdateBorderRadius({ radiusSize, radiusSize, radiusSize, radiusSize });
            childRenderContext->UpdateBackgroundColor(indexerTheme->GetHoverBgAreaColor());
        } else if (index == childFocusIndex_ || index == selected_) {
            if (index == childFocusIndex_) {
                auto borderWidth = indexerTheme->GetFocusBgOutlineSize();
                nodeLayoutProperty->UpdateBorderWidth({ borderWidth, borderWidth, borderWidth, borderWidth });
                auto borderColor = indexerTheme->GetFocusBgOutlineColor();
                childRenderContext->UpdateBorderColor({ borderColor, borderColor, borderColor, borderColor });
                childRenderContext->UpdateBackgroundColor(
                    paintProperty->GetSelectedBackgroundColor().value_or(indexerTheme->GetSeclectedBackgroundColor()));
            } else {
                Dimension borderWidth;
                nodeLayoutProperty->UpdateBorderWidth({ borderWidth, borderWidth, borderWidth, borderWidth });
                if (!fromTouchUp || animateSelected_ == lastSelected_) {
                    childRenderContext->UpdateBackgroundColor(paintProperty->GetSelectedBackgroundColor().value_or(
                        indexerTheme->GetSeclectedBackgroundColor()));
                }
                childRenderContext->ResetBlendBorderColor();
            }
            nodeLayoutProperty->UpdateTextColor(
                layoutProperty->GetSelectedColor().value_or(indexerTheme->GetSelectedTextColor()));
            auto radius = indexerTheme->GetHoverRadiusSize();
            childRenderContext->UpdateBorderRadius({ radius, radius, radius, radius });
            auto selectedFont = layoutProperty->GetSelectedFont().value_or(indexerTheme->GetSelectTextStyle());
            nodeLayoutProperty->UpdateFontSize(selectedFont.GetFontSize());
            auto fontWeight = selectedFont.GetFontWeight();
            nodeLayoutProperty->UpdateFontWeight(fontWeight);
            nodeLayoutProperty->UpdateFontFamily(selectedFont.GetFontFamilies());
            nodeLayoutProperty->UpdateItalicFontStyle(selectedFont.GetFontStyle());
            childRenderContext->SetClipToBounds(true);
            childNode->MarkModifyDone();
            index++;
            continue;
        } else {
            if (!fromTouchUp || animateSelected_ == lastSelected_ || index != lastSelected_) {
                childRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
            }
            Dimension radiusZeroSize;
            childRenderContext->UpdateBorderRadius({ radiusZeroSize, radiusZeroSize, radiusZeroSize, radiusZeroSize });
        }
        Dimension borderWidth;
        nodeLayoutProperty->UpdateBorderWidth({ borderWidth, borderWidth, borderWidth, borderWidth });
        childRenderContext->ResetBlendBorderColor();
        auto defaultFont = layoutProperty->GetFont().value_or(indexerTheme->GetDefaultTextStyle());
        nodeLayoutProperty->UpdateFontSize(defaultFont.GetFontSize());
        nodeLayoutProperty->UpdateFontWeight(defaultFont.GetFontWeight());
        nodeLayoutProperty->UpdateFontFamily(defaultFont.GetFontFamilies());
        nodeLayoutProperty->UpdateItalicFontStyle(defaultFont.GetFontStyle());
        nodeLayoutProperty->UpdateTextColor(layoutProperty->GetColor().value_or(indexerTheme->GetDefaultTextColor()));
        childNode->MarkModifyDone();
        index++;
    }
    if (selectChanged || NeedShowPopupView()) {
        ShowBubble();
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
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
    if (!popupNode_) {
        popupNode_ = CreatePopupNode();
        AddPopupTouchListener(popupNode_);
        UpdatePopupOpacity(0.0f);
        overlayManager->ShowIndexerPopup(host->GetId(), popupNode_);
    }
    UpdateBubbleView();
    StartBubbleAppearAnimation();
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
    auto userDefinePositionX =
        layoutProperty->GetPopupPositionX().value_or(Dimension(NG::BUBBLE_POSITION_X, DimensionUnit::VP)).ConvertToPx();
    auto userDefinePositionY =
        layoutProperty->GetPopupPositionY().value_or(Dimension(NG::BUBBLE_POSITION_Y, DimensionUnit::VP)).ConvertToPx();
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

RefPtr<FrameNode> IndexerPattern::CreatePopupNode()
{
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    CHECK_NULL_RETURN(columnNode, nullptr);
    auto letterNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(letterNode, nullptr);
    columnNode->AddChild(letterNode);
    auto listNode = FrameNode::CreateFrameNode(
        V2::LIST_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ListPattern>());
    CHECK_NULL_RETURN(listNode, nullptr);
    columnNode->AddChild(listNode);
    return columnNode;
}

void IndexerPattern::UpdateBubbleView()
{
    CHECK_NULL_VOID(popupNode_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto columnLayoutProperty = popupNode_->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(columnLayoutProperty);
    auto indexerEventHub = host->GetEventHub<IndexerEventHub>();
    auto popListData = indexerEventHub->GetOnRequestPopupData();
    auto currentListData =
        popListData ? popListData(childPressIndex_ >= 0 ? childPressIndex_ : selected_) : std::vector<std::string>();
    UpdateBubbleLetterView(!currentListData.empty());
    UpdateBubbleListView(currentListData);
    auto columnRenderContext = popupNode_->GetRenderContext();
    CHECK_NULL_VOID(columnRenderContext);
    auto radius = Dimension(BUBBLE_BOX_RADIUS, DimensionUnit::VP);
    columnRenderContext->UpdateBorderRadius({ radius, radius, radius, radius });
    columnRenderContext->UpdateBackShadow(ShadowConfig::DefaultShadowL);
    columnRenderContext->SetClipToBounds(true);
    SetPositionOfPopupNode(popupNode_);
    popupNode_->MarkModifyDone();
    popupNode_->MarkDirtyNode();
}

void IndexerPattern::UpdateBubbleSize()
{
    CHECK_NULL_VOID(popupNode_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto columnLayoutProperty = popupNode_->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(columnLayoutProperty);
    auto indexerEventHub = host->GetEventHub<IndexerEventHub>();
    auto popListData = indexerEventHub->GetOnRequestPopupData();
    auto currentListData =
        popListData ? popListData(childPressIndex_ >= 0 ? childPressIndex_ : selected_) : std::vector<std::string>();
    auto popupSize = currentListData.size();
    auto listActualSize = popupSize < INDEXER_BUBBLE_MAXSIZE ? popupSize : INDEXER_BUBBLE_MAXSIZE;
    auto bubbleSize = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    auto columnCalcSize = CalcSize(CalcLength(bubbleSize), CalcLength(bubbleSize * (listActualSize + 1)));
    columnLayoutProperty->UpdateUserDefinedIdealSize(columnCalcSize);
    popupNode_->MarkDirtyNode();
}

void IndexerPattern::UpdateBubbleLetterView(bool showDivider)
{
    CHECK_NULL_VOID(popupNode_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    auto layoutProperty = host->GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto paintProperty = host->GetPaintProperty<IndexerPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto letterNode = DynamicCast<FrameNode>(popupNode_->GetFirstChild());
    CHECK_NULL_VOID(letterNode);
    auto letterLayoutProperty = letterNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(letterLayoutProperty);
    letterLayoutProperty->UpdateContent(arrayValue_[childPressIndex_ >= 0 ? childPressIndex_ : selected_]);
    auto bubbleSize = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    letterLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(bubbleSize), CalcLength(bubbleSize)));
    auto popupTextFont = layoutProperty->GetPopupFont().value_or(indexerTheme->GetPopupTextStyle());
    letterLayoutProperty->UpdateFontSize(popupTextFont.GetFontSize());
    letterLayoutProperty->UpdateFontWeight(popupTextFont.GetFontWeight());
    letterLayoutProperty->UpdateFontFamily(popupTextFont.GetFontFamilies());
    letterLayoutProperty->UpdateItalicFontStyle(popupTextFont.GetFontStyle());
    letterLayoutProperty->UpdateTextColor(layoutProperty->GetPopupColor().value_or(indexerTheme->GetPopupTextColor()));
    letterLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    auto textPadding = Dimension(IndexerTheme::TEXT_PADDING_LEFT, DimensionUnit::VP).ConvertToPx();
    letterLayoutProperty->UpdatePadding(
        { CalcLength(textPadding), CalcLength(textPadding), CalcLength(0), CalcLength(0) });
    auto letterNodeRenderContext = letterNode->GetRenderContext();
    letterNodeRenderContext->UpdateBackgroundColor(
        paintProperty->GetPopupBackground().value_or(indexerTheme->GetPopupBackgroundColor()));
    letterNodeRenderContext->SetClipToBounds(true);
    auto borderWidthZero = Dimension();
    if (showDivider) {
        letterLayoutProperty->UpdateBorderWidth(
            { borderWidthZero, borderWidthZero, borderWidthZero, Dimension(INDEXER_LIST_DIVIDER) });
        auto boderColor = BorderColorProperty();
        boderColor.bottomColor = indexerTheme->GetPopupSeparateColor();
        letterNodeRenderContext->UpdateBorderColor(boderColor);
    } else {
        letterLayoutProperty->UpdateBorderWidth({ borderWidthZero, borderWidthZero, borderWidthZero, borderWidthZero });
    }
    letterNode->MarkModifyDone();
    letterNode->MarkDirtyNode();
}

void IndexerPattern::UpdateBubbleListView(std::vector<std::string>& currentListData)
{
    CHECK_NULL_VOID(popupNode_);
    auto listNode = DynamicCast<FrameNode>(popupNode_->GetLastChild());
    CHECK_NULL_VOID(listNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    currentPopupIndex_ = childPressIndex_ >= 0 ? childPressIndex_ : selected_;
    if (lastPopupIndex_ != currentPopupIndex_) {
        lastPopupIndex_ = currentPopupIndex_;
        CreateBubbleListView(currentListData);
    }
    auto popupSize = currentListData.size();
    auto listActualSize = popupSize < INDEXER_BUBBLE_MAXSIZE ? popupSize : INDEXER_BUBBLE_MAXSIZE;
    auto listLayoutProperty = listNode->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_VOID(listLayoutProperty);
    auto bubbleSize = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    listLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(bubbleSize), CalcLength(bubbleSize * listActualSize)));
    if (!currentListData.empty()) {
        UpdateBubbleListItem(currentListData, listNode, indexerTheme);
    } else {
        listNode->Clean();
    }
    auto divider = V2::ItemDivider();
    divider.strokeWidth = Dimension(INDEXER_LIST_DIVIDER, DimensionUnit::VP);
    divider.color = indexerTheme->GetPopupSeparateColor();
    listLayoutProperty->UpdateDivider(divider);
    listLayoutProperty->UpdateListDirection(Axis::VERTICAL);
    auto listRenderContext = listNode->GetRenderContext();
    CHECK_NULL_VOID(listRenderContext);
    listRenderContext->SetClipToBounds(true);
    listNode->MarkModifyDone();
    listNode->MarkDirtyNode();
}

void IndexerPattern::CreateBubbleListView(std::vector<std::string>& currentListData)
{
    CHECK_NULL_VOID(popupNode_);
    auto listNode = DynamicCast<FrameNode>(popupNode_->GetLastChild());
    CHECK_NULL_VOID(listNode);
    listNode->Clean();
    for (uint32_t i = 0; i < currentListData.size(); i++) {
        auto listItemNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ListItemPattern>(nullptr));
        auto textNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        listItemNode->AddChild(textNode);
        listNode->AddChild(listItemNode);
    }
}

void IndexerPattern::UpdateBubbleListItem(
    std::vector<std::string>& currentListData, const RefPtr<FrameNode>& listNode, RefPtr<IndexerTheme>& indexerTheme)
{
    CHECK_NULL_VOID(listNode);
    CHECK_NULL_VOID(indexerTheme);
    auto bubbleSize = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    for (uint32_t i = 0; i < currentListData.size(); i++) {
        auto listItemNode = DynamicCast<FrameNode>(listNode->GetChildAtIndex(i));
        CHECK_NULL_VOID(listItemNode);
        auto textNode = DynamicCast<FrameNode>(listItemNode->GetFirstChild());
        CHECK_NULL_VOID(textNode);
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateContent(currentListData.at(i));
        textLayoutProperty->UpdateTextColor(indexerTheme->GetPopupDefaultColor());
        textLayoutProperty->UpdateFontSize(indexerTheme->GetPopupTextSize());
        textLayoutProperty->UpdateFontWeight(indexerTheme->GetPopupTextStyle().GetFontWeight());
        textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
        textLayoutProperty->UpdateAlignment(Alignment::CENTER);
        textNode->MarkModifyDone();
        auto listItemProperty = listItemNode->GetLayoutProperty<ListItemLayoutProperty>();
        listItemProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(bubbleSize), CalcLength(bubbleSize)));
        listItemProperty->UpdateAlignment(Alignment::CENTER);
        AddListItemClickListener(listItemNode, i);
        listItemNode->MarkModifyDone();
    }
}

void IndexerPattern::ChangeListItemsSelectedStyle(int32_t clickIndex)
{
    auto host = GetHost();
    CHECK_NULL_VOID(popupNode_);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    auto listNode = popupNode_->GetLastChild();
    auto currentIndex = 0;
    for (auto child : listNode->GetChildren()) {
        auto listItemNode = DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(listItemNode);
        auto listItemProperty = listItemNode->GetLayoutProperty<ListItemLayoutProperty>();
        CHECK_NULL_VOID(listItemProperty);
        auto listItemContext = listItemNode->GetRenderContext();
        CHECK_NULL_VOID(listItemContext);
        auto textNode = DynamicCast<FrameNode>(listItemNode->GetFirstChild());
        CHECK_NULL_VOID(textNode);
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        if (currentIndex == clickIndex) {
            textLayoutProperty->UpdateTextColor(indexerTheme->GetPopupTextColor());
            listItemContext->UpdateBackgroundColor(Color(POPUP_LISTITEM_CLICKED_BG));
        } else {
            textLayoutProperty->UpdateTextColor(indexerTheme->GetPopupDefaultColor());
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
    auto touchCallback = [weak = WeakClaim(this), index](const TouchEventInfo& info) {
        auto indexerPattern = weak.Upgrade();
        CHECK_NULL_VOID(indexerPattern);
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            indexerPattern->OnListItemClick(index);
        }
    };
    gestureHub->AddTouchEvent(MakeRefPtr<TouchEventImpl>(std::move(touchCallback)));
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
    ChangeListItemsSelectedStyle(index);
}

void IndexerPattern::OnPopupTouchDown(const TouchEventInfo& info)
{
    if (NeedShowPopupView()) {
        StartBubbleAppearAnimation();
    }
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

void IndexerPattern::ItemSelectedInAnimation(RefPtr<FrameNode>& itemNode)
{
    CHECK_NULL_VOID(itemNode);
    auto rendercontext = itemNode->GetRenderContext();
    CHECK_NULL_VOID(rendercontext);
    AnimationOption option;
    option.SetDuration(INDEXER_SELECT_DURATION);
    option.SetCurve(Curves::LINEAR);
    AnimationUtils::Animate(option, [rendercontext, id = Container::CurrentId(), weak = WeakClaim(this)]() {
        ContainerScope scope(id);
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
        CHECK_NULL_VOID(indexerTheme);
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto paintProperty = host->GetPaintProperty<IndexerPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        rendercontext->UpdateBackgroundColor(
            paintProperty->GetSelectedBackgroundColor().value_or(indexerTheme->GetSeclectedBackgroundColor()));
    });
}

void IndexerPattern::ItemSelectedOutAnimation(RefPtr<FrameNode>& itemNode)
{
    CHECK_NULL_VOID(itemNode);
    auto rendercontext = itemNode->GetRenderContext();
    CHECK_NULL_VOID(rendercontext);
    AnimationOption option;
    option.SetDuration(INDEXER_SELECT_DURATION);
    option.SetCurve(Curves::LINEAR);
    AnimationUtils::Animate(option, [rendercontext, id = Container::CurrentId()]() {
        ContainerScope scope(id);
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
        CHECK_NULL_VOID(indexerTheme);
        rendercontext->UpdateBackgroundColor(Color::TRANSPARENT);
    });
}

void IndexerPattern::IndexerHoverInAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    AnimationOption option;
    option.SetDuration(INDEXER_HOVER_IN_DURATION);
    option.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(option, [renderContext, id = Container::CurrentId()]() {
        ContainerScope scope(id);
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
        CHECK_NULL_VOID(indexerTheme);
        renderContext->UpdateBackgroundColor(
            indexerTheme->GetSlipHoverBackgroundColor().ChangeOpacity(IndexerTheme::SLIP_BACKGROUND_OPACITY));
    });
}

void IndexerPattern::IndexerHoverOutAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    AnimationOption option;
    option.SetDuration(INDEXER_HOVER_OUT_DURATION);
    option.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(option, [renderContext, id = Container::CurrentId()]() {
        ContainerScope scope(id);
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
        CHECK_NULL_VOID(indexerTheme);
        renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    });
}

void IndexerPattern::IndexerPressInAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    AnimationOption option;
    option.SetDuration(INDEXER_PRESS_IN_DURATION);
    option.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(option, [renderContext, id = Container::CurrentId()]() {
        ContainerScope scope(id);
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
        CHECK_NULL_VOID(indexerTheme);
        renderContext->UpdateBackgroundColor(
            indexerTheme->GetSlipHoverBackgroundColor().ChangeOpacity(IndexerTheme::SLIP_PRESS_BACKGROUND_OPACITY));
    });
}

void IndexerPattern::IndexerPressOutAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    AnimationOption option;
    option.SetDuration(INDEXER_PRESS_OUT_DURATION);
    option.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(option, [renderContext, id = Container::CurrentId()]() {
        ContainerScope scope(id);
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
        CHECK_NULL_VOID(indexerTheme);
        renderContext->UpdateBackgroundColor(
            indexerTheme->GetSlipHoverBackgroundColor().ChangeOpacity(IndexerTheme::SLIP_BACKGROUND_OPACITY));
    });
}

void IndexerPattern::StartBubbleAppearAnimation()
{
    animationId_ = GenerateAnimationId();
    UpdatePopupVisibility(VisibleType::VISIBLE);
    AnimationOption option;
    option.SetCurve(Curves::SHARP);
    option.SetDuration(INDEXER_BUBBLE_APPEAR_DURATION);
    auto startTimeRatio = 1.0f * INDEXER_BUBBLE_ENTER_DURATION / INDEXER_BUBBLE_APPEAR_DURATION;
    auto middleTimeRatio =
        1.0f * (INDEXER_BUBBLE_WAIT_DURATION + INDEXER_BUBBLE_ENTER_DURATION) / INDEXER_BUBBLE_APPEAR_DURATION;
    AnimationUtils::OpenImplicitAnimation(option, Curves::SHARP,
        [id = Container::CurrentId(), weak = AceType::WeakClaim(this), animationId = animationId_]() {
            ContainerScope scope(id);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (pattern->animationId_ == animationId) {
                pattern->UpdatePopupVisibility(VisibleType::GONE);
            }
        });
    AnimationUtils::AddKeyFrame(
        startTimeRatio, Curves::SHARP, [id = Container::CurrentId(), weak = AceType::WeakClaim(this)]() {
            ContainerScope scope(id);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->UpdatePopupOpacity(1.0f);
            pattern->UpdateBubbleSize();
        });
    AnimationUtils::AddKeyFrame(
        middleTimeRatio, Curves::LINEAR, [id = Container::CurrentId(), weak = AceType::WeakClaim(this)]() {
            ContainerScope scope(id);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->UpdatePopupOpacity(1.0f);
        });
    AnimationUtils::AddKeyFrame(1.0f, Curves::SHARP, [id = Container::CurrentId(), weak = AceType::WeakClaim(this)]() {
        ContainerScope scope(id);
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->UpdatePopupOpacity(0.0f);
    });
    AnimationUtils::CloseImplicitAnimation();
}

void IndexerPattern::UpdatePopupOpacity(float ratio)
{
    CHECK_NULL_VOID(popupNode_);
    auto rendercontext = popupNode_->GetRenderContext();
    CHECK_NULL_VOID(rendercontext);
    rendercontext->UpdateOpacity(ratio);
}

void IndexerPattern::UpdatePopupVisibility(VisibleType visible)
{
    CHECK_NULL_VOID(popupNode_);
    auto layoutProperty = popupNode_->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto currentVisibility = layoutProperty->GetVisibility().value_or(VisibleType::VISIBLE);
    if (currentVisibility != visible) {
        layoutProperty->UpdateVisibility(visible);
        popupNode_->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    }
}

bool IndexerPattern::NeedShowPopupView()
{
    CHECK_NULL_RETURN(popupNode_, false);
    auto layoutProperty = popupNode_->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetVisibility().value_or(VisibleType::VISIBLE) == VisibleType::VISIBLE;
}

int32_t IndexerPattern::GenerateAnimationId()
{
    return (++animationId_) % TOTAL_NUMBER;
}
} // namespace OHOS::Ace::NG
