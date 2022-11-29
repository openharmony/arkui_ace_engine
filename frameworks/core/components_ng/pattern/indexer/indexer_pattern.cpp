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
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/indexer/indexer_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/indexer/indexer_theme.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_model.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/property.h"
#include "core/event/mouse_event.h"
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

    if (layoutProperty->GetSelected().has_value() && storeSelected_ != layoutProperty->GetSelected().value()) {
        storeSelected_ = layoutProperty->GetSelected().value();
        selected_ = storeSelected_;
        ResetStatus();
        if (storeSelected_ >= itemCount_) {
            storeSelected_ = 0;
            selected_ = 0;
        }
        ApplyIndexChanged();
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
    isInitialized_ = indexerLayoutAlgorithm->GetIsInitialized();
    selected_ = indexerLayoutAlgorithm->GetSelected();
    itemSizeRender_ = indexerLayoutAlgorithm->GetItemSizeRender();
    ResetStatus();
    return false;
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
            pattern->MoveIndexByOffset(info.GetLocalLocation(), false);
        }
    };

    auto onActionUpdate = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (info.GetInputEventType() == InputEventType::AXIS) {
            if (GreatNotEqual(info.GetMainDelta(), 0.0)) {
                pattern->MoveIndexByStep(-1);
            } else if (LessNotEqual(info.GetMainDelta(), 0.0)) {
                pattern->MoveIndexByStep(1);
            }
        } else {
            pattern->MoveIndexByOffset(info.GetLocalLocation(), false);
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
    ApplyIndexChanged();
}

void IndexerPattern::OnChildHover(int32_t index, bool isHover)
{
    if (isHover) {
        childHoverIndex_ = index;
    } else {
        childHoverIndex_ = -1;
    }
    ApplyIndexChanged();
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
    if (nextSelectIndex != selected_) {
        selected_ = nextSelectIndex;
        ResetStatus();
    }
    ApplyIndexChanged();
}

void IndexerPattern::MoveIndexByOffset(const Offset& offset, bool isRepeatCalled)
{
    LOGD("Move index by offset: (%{public}f,%{public}f). isRepeatCalled is %{public}d", offset.GetX(), offset.GetY(),
        isRepeatCalled);
    if (itemSizeRender_ <= 0) {
        return;
    }
    if (itemCount_ <= 0) {
        LOGE("AlphabetIndexer arrayValue size is less than 0");
        return;
    }
    auto nextSelectIndex = GetSelectChildIndex(offset);
    if (!isRepeatCalled && nextSelectIndex == childPressIndex_) {
        return;
    }
    childPressIndex_ = nextSelectIndex;
    childFocusIndex_ = -1;
    childHoverIndex_ = -1;
    LOGD("Move to index: %{public}d", childPressIndex_);
    ApplyIndexChanged();
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
    childFocusIndex_ = nextSected;
    if (nextSected >= 0) {
        selected_ = nextSected;
    }
    childPressIndex_ = -1;
    childHoverIndex_ = -1;
    ApplyIndexChanged();
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
    if (nextSected >= 0) {
        selected_ = nextSected;
    }
    ResetStatus();
    ApplyIndexChanged();
    return nextSected >= 0;
}

bool IndexerPattern::MoveIndexBySearch(const std::string& searchStr)
{
    auto nextSelectIndex = GetFocusChildIndex(searchStr);
    if (nextSelectIndex >= 0) {
        selected_ = nextSelectIndex;
    }

    childFocusIndex_ = nextSelectIndex;
    childHoverIndex_ = -1;
    childPressIndex_ = -1;
    ApplyIndexChanged();
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
void IndexerPattern::ApplyIndexChanged()
{
    if (selected_ >= itemCount_ || selected_ < 0) {
        selected_ = 0;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto indexerEventHub = host->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(indexerEventHub);
    auto paintProperty = host->GetPaintProperty<IndexerPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto onSelected = indexerEventHub->GetOnSelected();
    if (onSelected && (selected_ >= 0) && (selected_ < itemCount_)) {
        onSelected(selected_);
    }

    auto onRequestPopupData = indexerEventHub->GetOnRequestPopupData();
    std::optional<std::vector<std::string>> popupData;
    if (onRequestPopupData && (selected_ >= 0) && (selected_ < itemCount_)) {
        popupData = onRequestPopupData(selected_);
    }
    auto onPopupSelected = indexerEventHub->GetOnPopupSelected();
    if (onPopupSelected && (selected_ >= 0) && (selected_ < itemCount_)) {
        onPopupSelected(selected_);
    }

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    auto currentRenderContext = host->GetRenderContext();
    CHECK_NULL_VOID(currentRenderContext);
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
        if (index == childFocusIndex_ || index == selected_) {
            auto childRenderContext = childNode->GetRenderContext();
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
        } else if (index == itemCount_) {
            if (isInitialized_ && layoutProperty->GetUsingPopup().value_or(false)) {
                auto popupColor = layoutProperty->GetPopupColor().value_or(indexerTheme->GetPopupTextColor());
                auto popupBackground =
                    paintProperty->GetPopupBackground().value_or(indexerTheme->GetPopupBackgroundColor());
                auto popupFont = layoutProperty->GetPopupFont().value_or(indexerTheme->GetPopupTextStyle());
                std::vector<std::string> arrayValueSelected = {};
                std::vector<std::string> popupDataValue;
                if (!popupData.has_value() || !popupData->data()) {
                    popupDataValue = {};
                } else {
                    popupDataValue = popupData.value();
                }
                popupDataValue.insert(popupDataValue.begin(), arrayValue_[selected_]);
                popupSize_ =
                    (popupDataValue.size() < INDEXER_BUBBLE_MAXSIZE ? popupDataValue.size() : INDEXER_BUBBLE_MAXSIZE);
                auto listNode = AceType::DynamicCast<FrameNode>(iter);
                auto listLayoutproperty = listNode->GetLayoutProperty<ListLayoutProperty>();
                listLayoutproperty->UpdateListItemAlign(V2::ListItemAlign::CENTER);
                listNode->Clean();
                int32_t popupDataIndex = 0;
                for (const auto& data : popupDataValue) {
                    auto textNode =
                        FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<TextPattern>());
                    auto textNodeLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
                    textNodeLayoutProperty->UpdateContent(data);
                    if (popupDataIndex == 0) {
                        textNodeLayoutProperty->UpdateTextColor(popupColor);
                    } else {
                        textNodeLayoutProperty->UpdateTextColor(
                            layoutProperty->GetSelectedColor().value_or(indexerTheme->GetDefaultTextColor()));
                    }
                    auto textPaddingLeft = Dimension(IndexerTheme::TEXT_PADDING_LEFT, DimensionUnit::VP).ConvertToPx();
                    auto textPaddingTop = Dimension(IndexerTheme::TEXT_PADDING_TOP, DimensionUnit::VP).ConvertToPx();
                    textNodeLayoutProperty->UpdatePadding({ CalcLength(textPaddingLeft), CalcLength(textPaddingLeft),
                        CalcLength(textPaddingTop), CalcLength(textPaddingTop) });
                    auto fontSize = popupFont.GetFontSize();
                    textNodeLayoutProperty->UpdateFontSize(fontSize);
                    auto fontWeight = popupFont.GetFontWeight();
                    textNodeLayoutProperty->UpdateFontWeight(fontWeight);
                    textNodeLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
                    auto textNodeRenderContext = textNode->GetRenderContext();
                    textNodeRenderContext->UpdateBackgroundColor(popupBackground);
                    Dimension radius;
                    radius.SetValue(Dimension(BUBBLE_BOX_RADIUS, DimensionUnit::VP).ConvertToPx());
                    Dimension randiusZero;
                    if (popupDataValue.size() == 1) {
                        textNodeRenderContext->UpdateBorderRadius({ radius, radius, radius, radius });
                    } else {
                        if (popupDataIndex == 0) {
                            textNodeRenderContext->UpdateBorderRadius({ radius, radius, randiusZero, randiusZero });
                        } else if (popupDataIndex == (popupSize_ - 1)) {
                            textNodeRenderContext->UpdateBorderRadius({ randiusZero, randiusZero, radius, radius });
                        }
                    }
                    textNode->MarkModifyDone();
                    auto listItemNode = FrameNode::GetOrCreateFrameNode(
                        V2::LIST_ITEM_ETS_TAG, -1, []() { return AceType::MakeRefPtr<ListItemPattern>(nullptr); });
                    listItemNode->AddChild(textNode);
                    listItemNode->MarkModifyDone();
                    listNode->AddChild(listItemNode);
                    popupDataIndex++;
                }
                auto listRenderContext = listNode->GetRenderContext();
                listRenderContext->UpdateBackShadow(ShadowConfig::DefaultShadowL);
                Dimension radius;
                radius.SetValue(Dimension(BUBBLE_BOX_RADIUS, DimensionUnit::VP).ConvertToPx());
                listRenderContext->UpdateBorderRadius({ radius, radius, radius, radius });
                listNode->MarkModifyDone();
                listNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
                BeginBubbleAnimation(listNode);
            }
        } else {
            auto childRenderContext = childNode->GetRenderContext();
            CHECK_NULL_VOID(childRenderContext);
            if (index == childHoverIndex_ || index == childPressIndex_) {
                auto radiusSize = indexerTheme->GetHoverRadiusSize();
                childRenderContext->UpdateBorderRadius({ radiusSize, radiusSize, radiusSize, radiusSize });
                childRenderContext->BlendBgColor(indexerTheme->GetHoverBgAreaColor());
                nodeLayoutProperty->UpdateTextColor(indexerTheme->GetHoverTextColor());
            } else {
                childRenderContext->ResetBlendBgColor();
                Dimension radiusZeroSize;
                childRenderContext->UpdateBorderRadius(
                    { radiusZeroSize, radiusZeroSize, radiusZeroSize, radiusZeroSize });
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
        }
        index++;
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
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
        CHECK_NULL_RETURN(pattern, false);
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
    ApplyIndexChanged();
}

void IndexerPattern::BeginBubbleAnimation(RefPtr<FrameNode> animationNode)
{
    auto renderContext = animationNode->GetRenderContext();
    AnimationOption animationOption;
    animationOption.SetDuration(INDEXER_BUBBLE_ANIMATION_DURATION);
    animationOption.SetCurve(Curves::DECELE);
    renderContext->OpacityAnimation(animationOption, 1.0f, 0.0f);
}
} // namespace OHOS::Ace::NG
