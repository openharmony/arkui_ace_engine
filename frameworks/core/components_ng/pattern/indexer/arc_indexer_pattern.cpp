/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/indexer/arc_indexer_pattern.h"

#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_model.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float STR_DOT_ROTATE_ANGLE = 90;
constexpr int32_t ANIMATION_DURATION_20 = 20;
}
void ArcIndexerPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<ArcIndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto itemCountChanged = false;
    bool autoCollapseModeChanged = true;
    if (!isNewHeightCalculated_) {
        auto autoCollapse = layoutProperty->GetAutoCollapse().value_or(false);
        autoCollapseModeChanged = autoCollapse != autoCollapse_;
        autoCollapse_ = autoCollapse;

        auto newArray = layoutProperty->GetArrayValue().value_or(std::vector<std::string>());
        bool arrayValueChanged = newArray.size() != fullArrayValue_.size() || newArray != fullArrayValue_;
        if (arrayValueChanged || autoCollapseModeChanged) {
            currectCollapsingMode_ = ArcIndexerCollapsingMode::INVALID;
        }
        fullArrayValue_ = newArray;
    }
    fullCount_ = fullArrayValue_.size();
    if (fullCount_ > 0) {
        if (autoCollapse_) {
            sharpItemCount_ = fullArrayValue_.at(0) == StringUtils::Str16ToStr8(ARC_INDEXER_STR_SHARP) ? 1 : 0;
            CollapseArrayValue();
        } else {
            sharpItemCount_ = 0;
            BuildFullArrayValue();
        }
        itemCountChanged = (itemCount_ != static_cast<int32_t>(arcArrayValue_.size()));
        itemCount_ = static_cast<int32_t>(arcArrayValue_.size());
    } else {
        sharpItemCount_ = 0;
        itemCountChanged = (itemCount_ != 0);
        itemCount_ = 0;
        arcArrayValue_.clear();
    }
    BuildArrayValueItems();
    bool removeBubble = false;
    auto usePopup = layoutProperty->GetUsingPopup().value_or(false);
    if (isPopup_ != usePopup) {
        isPopup_ = usePopup;
        removeBubble = !isPopup_;
    }

    // Remove bubble if auto-collapse mode switched on/off or if items count changed
    bool isChange = autoCollapseModeChanged || itemCountChanged;
    removeBubble |= isChange;
    if (removeBubble) {
        RemoveBubble();
    }

    auto propSelect = layoutProperty->GetSelected().value();
    if (propSelect < 0 || propSelect >= itemCount_) {
        propSelect = 0;
        layoutProperty->UpdateSelected(propSelect);
    }

    if (propSelect != selected_) {
        selected_ = propSelect;
        selectChanged_ = true;
        ResetStatus();
    } else if (!isNewHeightCalculated_) {
        selectChanged_ = false;
    }
    isNewHeightCalculated_ = false;
    auto itemSize =
        layoutProperty->GetItemSize().value_or(Dimension(ARC_INDEXER_ITEM_SIZE, DimensionUnit::VP)).ConvertToPx();
    lastItemSize_ = itemSize;
    auto needMarkDirty = (layoutProperty->GetPropertyChangeFlag() == PROPERTY_UPDATE_NORMAL);
    ApplyIndexChanged(needMarkDirty, initialized_ && selectChanged_, false);
    auto gesture = host->GetOrCreateGestureEventHub();
    if (gesture) {
        InitPanEvent(gesture);
    }
    if (!touchListener_) {
        CHECK_NULL_VOID(gesture);
        auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
            auto offset = info.GetTouches().front().GetLocalLocation();
            auto indexerPattern = weak.Upgrade();
            CHECK_NULL_VOID(indexerPattern);
            if (!indexerPattern->AtArcHotArea(offset)) {
                return;
            }
            if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
                indexerPattern->isTouch_ = true;
                indexerPattern->OnTouchDown(info);
            } else if (info.GetTouches().front().GetTouchType() == TouchType::UP) {
                indexerPattern->isTouch_ = false;
                indexerPattern->OnTouchUp(info);
            }
        };
        touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
        gesture->AddTouchEvent(touchListener_);
    }
    SetAccessibilityAction();
}

bool ArcIndexerPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<ArcIndexerLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);
    auto size = layoutAlgorithm->GetArcSize();
    if (arcIndexerSize_ != size && autoCollapse_) {
        arcIndexerSize_ = size;
        isNewHeightCalculated_ = true;
        auto hostNode = dirty->GetHostNode();
        StartCollapseDelayTask(hostNode, ARC_INDEXER_COLLAPSE_WAIT_DURATION);
    }
    strokeWidth_ = lastItemSize_;
    arcCenter_ = layoutAlgorithm->GetArcCenter();
    startAngle_ = layoutAlgorithm->GetStartAngle();
    sweepAngle_ = layoutAlgorithm->GetSweepAngle();
    arcRadius_ = layoutAlgorithm->GetArcRadius();
    stepAngle_ = layoutAlgorithm->GetstepAngle();
    itemRadius_ = layoutAlgorithm->GetitemRadius();
    return true;
}

void ArcIndexerPattern::BuildArrayValueItems()
{
    int32_t indexerSize = static_cast<int32_t>(arcArrayValue_.size());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<ArcIndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto children = host->GetChildren();
    auto lastChildCount = static_cast<int32_t>(children.size());
    if (layoutProperty->GetIsPopupValue(false)) {
        lastChildCount -= 1;
    }
    if (indexerSize != lastChildCount) {
        host->Clean();
        layoutProperty->UpdateIsPopup(false);
        for (int32_t index = 0; index < indexerSize; index++) {
            auto indexerChildNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_VOID(indexerChildNode);
            host->AddChild(indexerChildNode);
        }
    }
    std::vector<std::string> arrayValueStrs;
    for (auto indexerItem : arcArrayValue_) {
        arrayValueStrs.push_back(indexerItem.first);
    }
    layoutProperty->UpdateArrayValue(arrayValueStrs);
}

void ArcIndexerPattern::BuildFullArrayValue()
{
    arcArrayValue_.clear();
    size_t indexSize = fullArrayValue_.size() > ARC_INDEXER_ITEM_MAX_COUNT-1 ?
                       ARC_INDEXER_ITEM_MAX_COUNT-1 : fullArrayValue_.size();
    size_t startIndex = (indexSize > 29) ? (indexSize - 29) : 0;
    for (size_t i = startIndex; i < indexSize; ++i) {
        arcArrayValue_.push_back(std::pair(fullArrayValue_.at(i), ArcIndexerBarState::INVALID));
    }

    if (fullCount_ + sharpItemCount_ > ARC_INDEXER_COLLAPSE_ITEM_COUNT) {
        arcArrayValue_.push_back(
            std::pair(StringUtils::Str16ToStr8(ARC_INDEXER_STR_COLLAPSED), ArcIndexerBarState::COLLAPSED));
    }
}

void ArcIndexerPattern::CollapseArrayValue()
{
    if (fullCount_  <= ARC_INDEXER_COLLAPSE_ITEM_COUNT ||
        currectCollapsingMode_ == ArcIndexerCollapsingMode::NONE) {
        BuildFullArrayValue();
    } else {
        ApplyFourPlusOneMode();
    }
}

void ArcIndexerPattern::ApplyFourPlusOneMode()
{
    arcArrayValue_.clear();
    for (int32_t groupIndex = 0; groupIndex < ARC_INDEXER_COLLAPSE_ITEM_COUNT; groupIndex++) {
        arcArrayValue_.push_back(std::pair(fullArrayValue_.at(groupIndex), ArcIndexerBarState::INVALID));
    }
    arcArrayValue_.push_back(
        std::pair(StringUtils::Str16ToStr8(ARC_INDEXER_STR_EXPANDED), ArcIndexerBarState::EXPANDED));
}

void ArcIndexerPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
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
        CHECK_NULL_VOID(pattern);
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

    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(onActionStart), std::move(onActionUpdate), nullptr, nullptr);
    gestureHub->AddPanEvent(panEvent_, panDirection, 1, 0.0_vp);
    gestureHub->SetOnGestureJudgeNativeBegin([weak = WeakClaim(this)](const RefPtr<NG::GestureInfo>& gestureInfo,
                                                 const std::shared_ptr<BaseGestureEvent>& info) -> GestureJudgeResult {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, GestureJudgeResult::CONTINUE);
        auto localLocation = info->GetFingerList().begin()->localLocation_;
        if (pattern->AtArcHotArea(localLocation)) {
            return GestureJudgeResult::CONTINUE;
        }
        return GestureJudgeResult::REJECT;
    });
}

void ArcIndexerPattern::OnTouchDown(const TouchEventInfo& info)
{
    if (itemCount_ <= 0) {
        return;
    }
    auto offset = info.GetTouches().front().GetLocalLocation();
    MoveIndexByOffset(offset);
}

void ArcIndexerPattern::OnTouchUp(const TouchEventInfo& info)
{
    if (itemCount_ <= 0) {
        return;
    }
    if (childPressIndex_ > -1) {
        ArcIndexerPressOutAnimation();
    }
    childPressIndex_ = -1;
    ResetStatus();
    ApplyIndexChanged(true, true, true);
    OnSelect(true);
}

void ArcIndexerPattern::MoveIndexByOffset(const Offset& offset)
{
    if (itemCount_ <= 0) {
        return;
    }
    auto nextSelectIndex = GetSelectChildIndex(offset);
    if (nextSelectIndex == itemCount_) {
        return;
    }
    if (arcArrayValue_[nextSelectIndex].second != ArcIndexerBarState::INVALID) {
        isNewHeightCalculated_ = true;
        if (arcArrayValue_[nextSelectIndex].second == ArcIndexerBarState::COLLAPSED && autoCollapse_) {
            currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
            lastCollapsingMode_ = ArcIndexerCollapsingMode::NONE;
            ArcCollapedAnimation(ARC_INDEXER_COLLAPSE_ITEM_COUNT);
            IndexNodeCollapsedAnimation();
        } else {
            currectCollapsingMode_ = ArcIndexerCollapsingMode::NONE;
            lastCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
            ArcExpandedAnimation(fullArrayValue_.size() - 1);
            auto host = GetHost();
            host->MarkModifyDone();
            host->MarkDirtyNode();
        }
        return;
    }
    if (nextSelectIndex == childPressIndex_) {
        return;
    }
    childPressIndex_ = nextSelectIndex;
    selected_ = nextSelectIndex;
    lastSelected_ = nextSelectIndex;
    FireOnSelect(selected_, true);
    if (childPressIndex_ >= 0) {
        ArcIndexerPressInAnimation();
    }
    childFocusIndex_ = -1;
    ApplyIndexChanged(true, true);
}

void ArcIndexerPattern::IndexNodeCollapsedAnimation()
{
    if (!atomicAnimateOp_) {
        return;
    }
    atomicAnimateOp_ = false;
    InitCollapsedProperty();
    AnimationOption option;
    option.SetCurve(Curves::FRICTION);
    option.SetDuration(ARC_INDEXER_COLLAPED_DURATION);
    option.SetIteration(1);
    auto total = fullArrayValue_.size();
    float from = stepAngle_ * total;
    collapsedAnimateIndex_ = total;
    collapsedProperty_->Set(from);
    float to = stepAngle_ * (ARC_INDEXER_COLLAPSE_ITEM_COUNT + 1);
    AnimationUtils::Animate(
        option,
        [weak = AceType::WeakClaim(this), to]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->collapsedProperty_->Set(to);
        },
        [id = Container::CurrentId(), weak = AceType::WeakClaim(this)]() {
            ContainerScope scope(id);
            auto pattern = weak.Upgrade();
            auto host = pattern->GetHost();
            host->MarkModifyDone();
            host->MarkDirtyNode();
            pattern->atomicAnimateOp_ = true;
        });
    lastCollapsingMode_ = currectCollapsingMode_;
}

void ArcIndexerPattern::IndexNodeExpandedAnimation()
{
    if (!atomicAnimateOp_) {
        return;
    }
    atomicAnimateOp_ = false;
    InitExpandedProperty();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto total = host->GetTotalChildCount();
    AnimationOption option;
    option.SetCurve(Curves::FRICTION);
    option.SetDuration(ARC_INDEXER_EXPANDED_DURATION);
    option.SetIteration(1);
    float from = stepAngle_ * ARC_INDEXER_COLLAPSE_ITEM_COUNT;
    expandedAnimateIndex_ = ARC_INDEXER_COLLAPSE_ITEM_COUNT;
    expandedProperty_->Set(from);
    float to = stepAngle_ * total;
    AnimationUtils::Animate(
        option,
        [weak = AceType::WeakClaim(this), to]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->expandedProperty_->Set(to);
        },
        [weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            pattern->atomicAnimateOp_ = true;
        });
    lastCollapsingMode_ = currectCollapsingMode_;
}

void ArcIndexerPattern::StartIndexerNodeDisappearAnimation(int32_t nodeIndex)
{
    auto host = GetHost();
    auto total = fullArrayValue_.size();
    if (nodeIndex > total) {
        return;
    }
    auto child = host->GetChildByIndex(nodeIndex);
    CHECK_NULL_VOID(child);
    auto childNode = child->GetHostNode();
    CHECK_NULL_VOID(childNode);

    AnimationOption option;
    option.SetCurve(Curves::FRICTION);
    option.SetDuration(ANIMATION_DURATION_20);
    AnimationUtils::Animate(
        option,
        [childNode, id = Container::CurrentId(), weak = AceType::WeakClaim(this)]() {
            ContainerScope scope(id);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->SetIndexerNodeOpacity(childNode, 0.0f);
        });
}

int32_t ArcIndexerPattern::GetSelectChildIndex(const Offset& offset)
{
    float indexAngle = GetPositionAngle(offset);
    int32_t index = 0;
    for (int32_t i = 0; i < itemCount_; i++) {
        auto iAngle = startAngle_ + stepAngle_ * (i - HALF);
        if (GreatOrEqual(indexAngle, iAngle) && LessNotEqual(indexAngle, iAngle + stepAngle_)) {
            break;
        }
        index++;
    }
    return std::clamp(index, 0, itemCount_);
}

void ArcIndexerPattern::ResetStatus()
{
    childFocusIndex_ = -1;
    childPressIndex_ = -1;
}

void ArcIndexerPattern::OnSelect(bool changed)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    FireOnSelect(selected_, false);
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

void ArcIndexerPattern::ApplyIndexChanged(bool isTextNodeInTree, bool selectChanged, bool fromTouchUp,
    bool indexerSizeChanged)
{
    initialized_ = true;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<ArcIndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto paintProperty = host->GetPaintProperty<ArcIndexerPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    int32_t index = 0;
    auto total = host->GetTotalChildCount();
    if (layoutProperty->GetIsPopupValue(false)) {
        total -= 1;
    }
    auto indexerRenderContext = host->GetRenderContext();
    CHECK_NULL_VOID(indexerRenderContext);
    auto indexerRadius = Dimension(arcRadius_, DimensionUnit::VP);
    indexerRenderContext->UpdateBorderRadius({ indexerRadius, indexerRadius, indexerRadius, indexerRadius });
    indexerRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    for (int32_t i = 0; i < total; i++) {
        auto child = host->GetChildByIndex(i);
        CHECK_NULL_VOID(child);
        auto childNode = child->GetHostNode();
        UpdateChildBoundary(childNode);
        auto nodeLayoutProperty = childNode->GetLayoutProperty<TextLayoutProperty>();
        auto childRenderContext = childNode->GetRenderContext();
        childRenderContext->SetClipToBounds(true);

        if (arcArrayValue_[index].second != ArcIndexerBarState::INVALID) {
            float itemAngle = CalcArcItemAngle(i) + STR_DOT_ROTATE_ANGLE;
            childRenderContext->UpdateTransformRotate(Vector5F(0.0f, 0.0f, 1.0f, itemAngle, 0.0f));
            nodeLayoutProperty->UpdateTextColor(Color(ARC_INDEXER_STR_DOT_COLOR));
        } else {
            nodeLayoutProperty->UpdateTextColor(
                layoutProperty->GetColor().value_or(indexerTheme->GetDefaultTextColor()));
        }
        auto radiusSize =  Dimension(lastItemSize_ * HALF);
        childRenderContext->UpdateBorderRadius({ radiusSize, radiusSize, radiusSize, radiusSize });
        auto nodeStr = autoCollapse_ && (arcArrayValue_[index].second != ArcIndexerBarState::INVALID) ?
            (arcArrayValue_[index].second == ArcIndexerBarState::COLLAPSED ?
            StringUtils::Str16ToStr8(ARC_INDEXER_STR_COLLAPSED) :
            StringUtils::Str16ToStr8(ARC_INDEXER_STR_EXPANDED)) : arcArrayValue_[index].first;
        if (index == childPressIndex_) {
            childRenderContext->UpdateBackgroundColor(indexerTheme->GetPressedBgAreaColor());
        } else if (index == childFocusIndex_ || index == selected_) {
            nodeLayoutProperty->UpdateContent(nodeStr);
            nodeLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
            nodeLayoutProperty->UpdateAlignment(Alignment::CENTER);
            if (index == childFocusIndex_) {
                childRenderContext->UpdateBackgroundColor(
                    paintProperty->GetSelectedBackgroundColor().value_or(indexerTheme->GetSeclectedBackgroundColor()));
            } else {
                if (!fromTouchUp || animateSelected_ == lastSelected_) {
                    childRenderContext->UpdateBackgroundColor(paintProperty->GetSelectedBackgroundColor().value_or(
                        indexerTheme->GetSeclectedBackgroundColor()));
                }
                childRenderContext->ResetBlendBorderColor();
            }
            nodeLayoutProperty->UpdateTextColor(
                layoutProperty->GetSelectedColor().value_or(indexerTheme->GetSelectedTextColor()));
            auto selectedFont = layoutProperty->GetSelectedFont().value_or(indexerTheme->GetSelectTextStyle());
            nodeLayoutProperty->UpdateFontSize(selectedFont.GetFontSize());
            auto fontWeight = selectedFont.GetFontWeight();
            nodeLayoutProperty->UpdateFontWeight(fontWeight);
            nodeLayoutProperty->UpdateFontFamily(selectedFont.GetFontFamilies());
            nodeLayoutProperty->UpdateItalicFontStyle(selectedFont.GetFontStyle());
            childNode->MarkModifyDone();
            if (isTextNodeInTree) {
                childNode->MarkDirtyNode();
            }
            index++;
            AccessibilityEventType type = AccessibilityEventType::SELECTED;
            host->OnAccessibilityEvent(type);
            auto textAccessibilityProperty = childNode->GetAccessibilityProperty<TextAccessibilityProperty>();
            if (textAccessibilityProperty) {
                textAccessibilityProperty->SetSelected(true);
            }
            continue;
        } else {
            if (!fromTouchUp || animateSelected_ == lastSelected_ || index != lastSelected_) {
                childRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
            }
        }
        Dimension borderWidth;
        nodeLayoutProperty->UpdateContent(nodeStr);
        nodeLayoutProperty->UpdateMaxLines(1);
        nodeLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
        nodeLayoutProperty->UpdateEllipsisMode(EllipsisMode::TAIL);
        nodeLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
        nodeLayoutProperty->UpdateAlignment(Alignment::CENTER);
        nodeLayoutProperty->UpdateBorderWidth({ borderWidth, borderWidth, borderWidth, borderWidth });
        childRenderContext->ResetBlendBorderColor();
        auto defaultFont = layoutProperty->GetFont().value_or(indexerTheme->GetDefaultTextStyle());
        nodeLayoutProperty->UpdateFontSize(defaultFont.GetFontSize());
        nodeLayoutProperty->UpdateFontWeight(defaultFont.GetFontWeight());
        nodeLayoutProperty->UpdateFontFamily(defaultFont.GetFontFamilies());
        nodeLayoutProperty->UpdateItalicFontStyle(defaultFont.GetFontStyle());
        nodeLayoutProperty->UpdateTextColor(layoutProperty->GetColor().value_or(indexerTheme->GetDefaultTextColor()));
        auto textAccessibilityProperty = childNode->GetAccessibilityProperty<TextAccessibilityProperty>();
        if (textAccessibilityProperty) {
            textAccessibilityProperty->SetSelected(false);
        }
        if (!fromTouchUp && currectCollapsingMode_ == ArcIndexerCollapsingMode::NONE &&
            currectCollapsingMode_ != lastCollapsingMode_) {
            UpdateIndexerNodeOpacityByIdx(childRenderContext, index);
        }
        index++;
        childNode->MarkModifyDone();
        if (isTextNodeInTree) childNode->MarkDirtyNode();
    }
    if (!fromTouchUp && currectCollapsingMode_ == ArcIndexerCollapsingMode::NONE
        && currectCollapsingMode_ != lastCollapsingMode_) {
        IndexNodeExpandedAnimation();
    }
    if (selectChanged) {
        ShowBubble();
    }
}

void ArcIndexerPattern::InitExpandedProperty()
{
    if (expandedProperty_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto expandedAngleCallback = [weak = AceType::WeakClaim(this)](float angle) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        int32_t index = floor(angle / pattern->stepAngle_);
        for (int32_t i = pattern->expandedAnimateIndex_; i <= index; i++) {
            pattern->StartIndexerNodeAppearAnimation(i);
        }
        pattern->expandedAnimateIndex_ = index + 1;
    };
    expandedProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(expandedAngleCallback));
    renderContext->AttachNodeAnimatableProperty(expandedProperty_);
}

void ArcIndexerPattern::InitCollapsedProperty()
{
    if (collapsedProperty_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto collapsedAngleCallback = [weak = AceType::WeakClaim(this)](float angle) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        int32_t index = floor(angle / pattern->stepAngle_);
        for (int32_t i = pattern->collapsedAnimateIndex_; i >= index; i--) {
            pattern->StartIndexerNodeDisappearAnimation(i);
        }
        pattern->collapsedAnimateIndex_ = index - 1;
    };
    collapsedProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(collapsedAngleCallback));
    renderContext->AttachNodeAnimatableProperty(collapsedProperty_);
}

void ArcIndexerPattern::UpdateIndexerNodeOpacityByIdx(RefPtr<RenderContext>& context, int32_t index)
{
    if (index <= ARC_INDEXER_COLLAPSE_ITEM_COUNT || currectCollapsingMode_ == lastCollapsingMode_) {
        return;
    }
    switch (currectCollapsingMode_) {
        case ArcIndexerCollapsingMode::NONE:
            context->UpdateOpacity(0.0f);
            break;
        case ArcIndexerCollapsingMode::FOUR:
        case ArcIndexerCollapsingMode::INVALID:
        default:
            break;
    }
}

void ArcIndexerPattern::StartIndexerNodeAppearAnimation(int32_t nodeIndex)
{
    auto host = GetHost();
    auto total = fullArrayValue_.size();
    if (nodeIndex > total) {
        return;
    }
    auto child = host->GetChildByIndex(nodeIndex);
    CHECK_NULL_VOID(child);
    auto childNode = child->GetHostNode();
    CHECK_NULL_VOID(childNode);

    AnimationOption option;
    option.SetCurve(Curves::FRICTION);
    option.SetDuration(ANIMATION_DURATION_20);
    AnimationUtils::Animate(
        option,
        [childNode, id = Container::CurrentId(), weak = AceType::WeakClaim(this)]() {
            ContainerScope scope(id);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->SetIndexerNodeOpacity(childNode, 1.0f);
        });
}

void ArcIndexerPattern::SetIndexerNodeOpacity(const RefPtr<FrameNode>& itemNode, float ratio)
{
    auto rendercontext = itemNode->GetRenderContext();
    CHECK_NULL_VOID(rendercontext);
    rendercontext->UpdateOpacity(ratio);
}

void ArcIndexerPattern::ShowBubble()
{
    if (!NeedShowBubble() || itemCount_ < 1) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<ArcIndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!popupNode_) {
        popupNode_ = CreatePopupNode();
        UpdatePopupOpacity(0.0f);
    }
    if (!layoutProperty->GetIsPopupValue(false)) {
        popupNode_->MountToParent(host);
        layoutProperty->UpdateIsPopup(true);
    }
    UpdateBubbleView();
    delayTask_.Cancel();
    StartBubbleAppearAnimation();
    if (!isTouch_) {
        StartDelayTask(ARC_INDEXER_BUBBLE_ENTER_DURATION + ARC_INDEXER_BUBBLE_WAIT_DURATION);
    }
}

RefPtr<FrameNode> ArcIndexerPattern::CreatePopupNode()
{
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    CHECK_NULL_RETURN(columnNode, nullptr);

    auto letterNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(letterNode, nullptr);
    auto letterStackNode = FrameNode::CreateFrameNode(
        V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StackPattern>());
    CHECK_NULL_RETURN(letterStackNode, nullptr);
    letterStackNode->AddChild(letterNode);
    columnNode->AddChild(letterStackNode);
    return columnNode;
}

void ArcIndexerPattern::UpdateBubbleView()
{
    CHECK_NULL_VOID(popupNode_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto currentListData = std::vector<std::string>();
    UpdateBubbleLetterView(false, currentListData);
    auto columnRenderContext = popupNode_->GetRenderContext();
    CHECK_NULL_VOID(columnRenderContext);
    auto radius = Dimension(ARC_BUBBLE_RADIUS, DimensionUnit::VP);
    columnRenderContext->UpdateBorderRadius({ radius, radius, radius, radius });
    columnRenderContext->UpdateBackShadow(Shadow::CreateShadow(ShadowStyle::OuterDefaultLG));

    UpdateBubbleBackgroundView();
    columnRenderContext->SetClipToBounds(true);
    popupNode_->MarkModifyDone();
    popupNode_->MarkDirtyNode();
}

void ArcIndexerPattern::UpdateBubbleBackgroundView()
{
    CHECK_NULL_VOID(popupNode_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<ArcIndexerPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    BlurStyleOption styleOption;
    if (paintProperty->GetPopupBackgroundBlurStyle().has_value()) {
        styleOption = paintProperty->GetPopupBackgroundBlurStyle().value();
    } else {
        styleOption.blurStyle = BlurStyle::COMPONENT_REGULAR;
    }
    auto bubbleRenderContext = popupNode_->GetRenderContext();
    CHECK_NULL_VOID(bubbleRenderContext);
    bubbleRenderContext->UpdateBackBlurStyle(styleOption);
    bubbleRenderContext->UpdateBackgroundColor(
        paintProperty->GetPopupBackground().value_or(indexerTheme->GetPopupBackgroundColor()));
}

void ArcIndexerPattern::UpdateBubbleLetterView(bool showDivider, std::vector<std::string>& currentListData)
{
    CHECK_NULL_VOID(popupNode_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    auto paintProperty = host->GetPaintProperty<ArcIndexerPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto layoutProperty = host->GetLayoutProperty<ArcIndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto letterNode = GetLetterNode();
    CHECK_NULL_VOID(letterNode);
    UpdateBubbleLetterStackAndLetterTextView();
    auto letterNodeRenderContext = letterNode->GetRenderContext();
    CHECK_NULL_VOID(letterNodeRenderContext);
    auto radius = Dimension(ARC_BUBBLE_RADIUS, DimensionUnit::VP);
    letterNodeRenderContext->UpdateBorderRadius({ radius, radius, radius, radius });
    letterNodeRenderContext->UpdateBackgroundColor(
        paintProperty->GetPopupBackground().value_or(indexerTheme->GetPopupBackgroundColor()));
    auto letterStackNode = DynamicCast<FrameNode>(popupNode_->GetFirstChild());
    CHECK_NULL_VOID(letterStackNode);
    auto letterStackLayoutProperty = letterStackNode->GetLayoutProperty<StackLayoutProperty>();
    CHECK_NULL_VOID(letterStackLayoutProperty);
    auto letterStackRenderContext = letterStackNode->GetRenderContext();
    CHECK_NULL_VOID(letterStackRenderContext);
    letterStackRenderContext->UpdateBorderRadius({ radius, radius, radius, radius });
    letterStackRenderContext->UpdateBackgroundColor(
        paintProperty->GetPopupBackground().value_or(indexerTheme->GetPopupBackgroundColor()));
    auto letterStackSize = Dimension(ARC_BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    letterStackLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(letterStackSize), CalcLength(letterStackSize)));

    letterNodeRenderContext->SetClipToBounds(true);
    letterStackRenderContext->SetClipToBounds(true);
    letterNode->MarkModifyDone();
    letterNode->MarkDirtyNode();
    letterStackNode->MarkModifyDone();
    letterStackNode->MarkDirtyNode();
}

void ArcIndexerPattern::UpdateBubbleLetterStackAndLetterTextView()
{
    CHECK_NULL_VOID(popupNode_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    auto layoutProperty = host->GetLayoutProperty<ArcIndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto letterNode = GetLetterNode();
    CHECK_NULL_VOID(letterNode);
    auto letterLayoutProperty = letterNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(letterLayoutProperty);

    auto contenStr = arcArrayValue_[childPressIndex_ >= 0 ? childPressIndex_ : selected_].first;
    letterLayoutProperty->UpdateContent(contenStr);
    auto popupTextFont = layoutProperty->GetPopupFont().value_or(indexerTheme->GetPopupTextStyle());
    letterLayoutProperty->UpdateMaxLines(ARC_INDEXER_BUBBLE_MAX_TEXT_LINE);
    letterLayoutProperty->UpdateFontSize(popupTextFont.GetFontSize());
    letterLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    letterLayoutProperty->UpdateEllipsisMode(EllipsisMode::TAIL);
    letterLayoutProperty->UpdateAdaptMaxFontSize(popupTextFont.GetFontSize());
    auto minFontSize = Dimension(popupTextFont.GetFontSize().ConvertToFp() - 3.0f, DimensionUnit::FP);
    minFontSize = minFontSize < Dimension(1.0) ? Dimension(1.0) : minFontSize;
    letterLayoutProperty->UpdateAdaptMinFontSize(minFontSize);
    letterLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);
    letterLayoutProperty->UpdateFontWeight(popupTextFont.GetFontWeight());
    letterLayoutProperty->UpdateFontFamily(popupTextFont.GetFontFamilies());
    letterLayoutProperty->UpdateItalicFontStyle(popupTextFont.GetFontStyle());
    letterLayoutProperty->UpdateTextColor(layoutProperty->GetPopupColor().value_or(indexerTheme->GetPopupTextColor()));
    letterLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    letterLayoutProperty->UpdateAlignment(Alignment::CENTER);

    auto textPadding = Dimension(ARC_INDEXER_PADDING_LEFT, DimensionUnit::VP).ConvertToPx();
    letterLayoutProperty->UpdatePadding(
        { CalcLength(textPadding), CalcLength(textPadding), CalcLength(textPadding), CalcLength(textPadding) });

    auto BubbleSize = Dimension(ARC_BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    letterLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(BubbleSize), CalcLength(BubbleSize)));
}

RefPtr<FrameNode> ArcIndexerPattern::GetLetterNode()
{
    CHECK_NULL_RETURN(popupNode_, nullptr);
    return DynamicCast<FrameNode>(popupNode_->GetFirstChild()->GetFirstChild());
}

bool ArcIndexerPattern::NeedShowBubble()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty<ArcIndexerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto usePopup = layoutProperty->GetUsingPopup().value_or(false);
    return usePopup && IfSelectIndexValid();
}

bool ArcIndexerPattern::IfSelectIndexValid()
{
    int32_t maxValidIndex = arcArrayValue_.size();
    if (maxValidIndex > ARC_INDEXER_COLLAPSE_ITEM_COUNT) {
        maxValidIndex -= 1;
    }
    return (selected_ >= 0 && selected_ < maxValidIndex);
}

void ArcIndexerPattern::ArcExpandedAnimation(int32_t nextIndex)
{
    AnimationOption option;
    option.SetDuration(ARC_INDEXER_EXPANDED_DURATION);
    option.SetCurve(Curves::FRICTION);
    float nextAngle = CalcArcItemAngle(nextIndex);
    nextAngle += stepAngle_ * (ARC_INDEXER_COLLAPSE_ITEM_COUNT + 1) * HALF;
    if (NearEqual(nextAngle + stepAngle_, FULL_CIRCLE_ANGLE)) {
        nextAngle = FULL_CIRCLE_ANGLE;
    }
    AnimationUtils::Animate(option, [&, nextAngle, id = Container::CurrentId()]() {
        ContainerScope scope(id);
        contentModifier_->SetSweepAngle(nextAngle);
    });
}

void ArcIndexerPattern::ArcCollapedAnimation(int32_t nextIndex)
{
    AnimationOption option;
    option.SetDuration(ARC_INDEXER_COLLAPED_DURATION);
    option.SetCurve(Curves::FRICTION);
    float nextAngle = CalcArcItemAngle(nextIndex);
    nextAngle += stepAngle_ * (ARC_INDEXER_COLLAPSE_ITEM_COUNT + 1) * HALF;
    AnimationUtils::Animate(option, [&, nextAngle, id = Container::CurrentId()]() {
        ContainerScope scope(id);
        contentModifier_->SetSweepAngle(nextAngle);
    });
}

void ArcIndexerPattern::ArcIndexerPressInAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    AnimationOption option;
    option.SetDuration(ARC_INDEXER_PRESS_IN_DURATION);
    option.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(option, [renderContext, id = Container::CurrentId()]() {
        ContainerScope scope(id);
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
        CHECK_NULL_VOID(indexerTheme);
        renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    });
}

void ArcIndexerPattern::ArcIndexerPressOutAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    AnimationOption option;
    option.SetDuration(ARC_INDEXER_PRESS_OUT_DURATION);
    option.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(option, [renderContext, id = Container::CurrentId()]() {
        ContainerScope scope(id);
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
        CHECK_NULL_VOID(indexerTheme);
        renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    });
}

void ArcIndexerPattern::StartBubbleAppearAnimation()
{
    animationId_ = GenerateAnimationId();
    UpdatePopupVisibility(VisibleType::VISIBLE);
    AnimationOption option;
    option.SetCurve(Curves::SHARP);
    option.SetDuration(ARC_INDEXER_BUBBLE_ENTER_DURATION);
    AnimationUtils::Animate(
        option,
        [id = Container::CurrentId(), weak = AceType::WeakClaim(this)]() {
            ContainerScope scope(id);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->UpdatePopupOpacity(1.0f);
        });
}

void ArcIndexerPattern::StartDelayTask(uint32_t duration)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    CHECK_NULL_VOID(context->GetTaskExecutor());
    delayTask_.Reset([weak = AceType::WeakClaim(this)] {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->StartBubbleDisappearAnimation();
        });
    context->GetTaskExecutor()->PostDelayedTask(
        delayTask_, TaskExecutor::TaskType::UI, duration, "ArkUIAlphabetArcIndexerBubbleDisappear");
}

void ArcIndexerPattern::StartBubbleDisappearAnimation()
{
    AnimationOption option;
    option.SetCurve(Curves::SHARP);
    option.SetDuration(ARC_INDEXER_BUBBLE_EXIT_DURATION);
    AnimationUtils::Animate(
        option,
        [id = Container::CurrentId(), weak = AceType::WeakClaim(this)]() {
            ContainerScope scope(id);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->UpdatePopupOpacity(0.0f);
        },
        [id = Container::CurrentId(), weak = AceType::WeakClaim(this)]() {
            ContainerScope scope(id);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            CHECK_NULL_VOID(pattern->popupNode_);
            auto rendercontext = pattern->popupNode_->GetRenderContext();
            CHECK_NULL_VOID(rendercontext);
            if (NearZero(rendercontext->GetOpacityValue(0.0f))) {
                pattern->UpdatePopupVisibility(VisibleType::GONE);
            }
        });
}

void ArcIndexerPattern::FireOnSelect(int32_t selectIndex, bool fromPress)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto indexerEventHub = host->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(indexerEventHub);
    auto actualIndex = autoCollapse_ ?
            selected_ > 0 ?
                std::find(fullArrayValue_.begin(), fullArrayValue_.end(),
                    arcArrayValue_.at(selected_).first) - fullArrayValue_.begin() :
                selected_ :
        selectIndex;
    if (fromPress || lastIndexFromPress_ == fromPress || lastFireSelectIndex_ != selectIndex) {
        auto onChangeEvent = indexerEventHub->GetChangeEvent();
        if (onChangeEvent && (selected_ >= 0) && (selected_ < itemCount_)) {
            onChangeEvent(selected_);
        }
        auto onCreatChangeEvent = indexerEventHub->GetCreatChangeEvent();
        if (onCreatChangeEvent && (selected_ >= 0) && (selected_ < itemCount_)) {
            onCreatChangeEvent(selected_);
        }
        auto onSelected = indexerEventHub->GetOnSelected();
        if (onSelected && (selectIndex >= 0) && (selectIndex < itemCount_)) {
            onSelected(actualIndex); // fire onSelected with an item's index from original array
        }
    }
    lastFireSelectIndex_ = selectIndex;
    lastIndexFromPress_ = fromPress;
}

bool ArcIndexerPattern::IsMeasureBoundary() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty<ArcIndexerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return CheckMeasureSelfFlag(layoutProperty->GetPropertyChangeFlag());
}

void ArcIndexerPattern::UpdateChildBoundary(RefPtr<FrameNode>& frameNode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<ArcIndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    CHECK_NULL_VOID(frameNode);
    auto pattern = DynamicCast<TextPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pattern);
    auto isMeasureBoundary = layoutProperty->GetPropertyChangeFlag() ==  PROPERTY_UPDATE_NORMAL;
    pattern->SetIsMeasureBoundary(isMeasureBoundary);
}

void ArcIndexerPattern::DumpInfo()
{
    auto layoutProperty = GetLayoutProperty<ArcIndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto itemSize = layoutProperty->GetItemSize();
    DumpLog::GetInstance().AddDesc(
        std::string("Offset: ").append(itemSize.has_value() ? itemSize.value().ToString() : "undefined"));
}

float ArcIndexerPattern::CalcArcItemAngle(int32_t index)
{
    float itemAngle = 0.0f;
    itemAngle = startAngle_ + stepAngle_ * index;
    return itemAngle;
}

float ArcIndexerPattern::GetPositionAngle(const Offset& position)
{
    float deltaY = position.GetY() - arcCenter_.GetY();
    float deltaX = position.GetX() - arcCenter_.GetX();
    float posAngle = atan2f(deltaY, deltaX) * HALF_CIRCLE_ANGLE / M_PI;
    if (deltaY < 0) {
        posAngle += FULL_CIRCLE_ANGLE;
    }
    if (posAngle < startAngle_) {
        posAngle += FULL_CIRCLE_ANGLE;
    }
    if (posAngle > FULL_CIRCLE_ANGLE + startAngle_ - stepAngle_ * HALF) {
        posAngle -= FULL_CIRCLE_ANGLE;
    }
    return posAngle;
}

bool ArcIndexerPattern::AtArcHotArea(const Offset& position)
{
    float indexAngle = GetPositionAngle(position);
    if (GreatNotEqual(indexAngle, sweepAngle_ + startAngle_ + stepAngle_ * HALF) ||
        LessNotEqual(indexAngle, startAngle_ - stepAngle_ * HALF)) {
        return false;
    }

    auto deltaX = position.GetX() - arcCenter_.GetX();
    auto deltaY = position.GetY() - arcCenter_.GetY();
    auto distance = sqrtf(deltaX * deltaX + deltaY * deltaY);
    if (GreatOrEqual(distance, arcRadius_ - itemRadius_ * DOUBLE) &&
        LessOrEqual(distance, arcRadius_ + itemRadius_)) {
        return true;
    }
    return false;
}
} // namespace OHOS::Ace::NG
