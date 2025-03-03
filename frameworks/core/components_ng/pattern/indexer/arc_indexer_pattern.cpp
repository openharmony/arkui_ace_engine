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
#include "core/components_ng/pattern/image/image_layout_property.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float STR_DOT_ROTATE_ANGLE = 90.0;
constexpr int32_t ANIMATION_DURATION_20 = 20;
constexpr char BUTTON_ROLE[] = "Button";
}

void ArcIndexerPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<ArcIndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    bool autoCollapseModeChanged = true;
    InitArrayValue(autoCollapseModeChanged);
    auto itemSize =
        layoutProperty->GetItemSize().value_or(Dimension(ARC_INDEXER_ITEM_SIZE, DimensionUnit::VP)).ConvertToPx();
    lastItemSize_ = itemSize;
    auto needMarkDirty = (layoutProperty->GetPropertyChangeFlag() == PROPERTY_UPDATE_NORMAL);
    ApplyIndexChanged(needMarkDirty, initialized_ && selectChanged_, false);
    InitTouchEvent ();
    SetAccessibilityAction();
    InitializeAccessibility();
}

void ArcIndexerPattern::InitArrayValue(bool& autoCollapseModeChanged)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<ArcIndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!isNewHeightCalculated_) {
        auto autoCollapse = layoutProperty->GetAutoCollapse().value_or(true);
        autoCollapseModeChanged = autoCollapse != autoCollapse_;
        autoCollapse_ = autoCollapse;
        auto newArray = layoutProperty->GetArrayValue().value_or(std::vector<std::string>());
        bool arrayValueChanged = newArray.size() != fullArrayValue_.size() || newArray != fullArrayValue_;
        if (arrayValueChanged || autoCollapseModeChanged) {
            lastCollapsingMode_ = currectCollapsingMode_;
            if (autoCollapse_ && newArray.size() > ARC_INDEXER_COLLAPSE_ITEM_COUNT) {
                currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
            } else {
                currectCollapsingMode_ = ArcIndexerCollapsingMode::NONE;
            }
        }
        fullArrayValue_ = newArray;
        fullCount_ = static_cast<int32_t>(fullArrayValue_.size());
    }
    auto propSelect = layoutProperty->GetSelected().value();
    if (propSelect < 0) {
        propSelect = 0;
        layoutProperty->UpdateSelected(propSelect);
    }
    if (fullCount_ > 0 && propSelect >= fullCount_) {
        propSelect = fullCount_ - 1;
        layoutProperty->UpdateSelected(propSelect);
    }
    if (propSelect != selected_) {
        selectChanged_ = true;
        if (selected_ + startIndex_ == propSelect) {
            selectChanged_ = false;
        }
        selected_ = propSelect;
        ResetStatus();
    } else if (propSelect == selected_ && propSelect == 0) {
        selectChanged_ = true;
    }
    if (isNewHeightCalculated_) {
        selectChanged_ = false;
    }
    isNewHeightCalculated_ = false;
    ResetArrayValue(autoCollapseModeChanged);
}

void ArcIndexerPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->DeregisterAccessibilitySAObserverCallback(frameNode->GetAccessibilityId());
}

class ArcIndexerAccessibilitySAObserverCallback : public AccessibilitySAObserverCallback {
public:
    ArcIndexerAccessibilitySAObserverCallback(
        const WeakPtr<ArcIndexerPattern>& weakPattern, int64_t accessibilityId)
        : AccessibilitySAObserverCallback(accessibilityId), weakPattern_(weakPattern)
    {}

    ~ArcIndexerAccessibilitySAObserverCallback() override = default;

    bool OnState(bool state) override
    {
        auto indexerPattern = weakPattern_.Upgrade();
        CHECK_NULL_RETURN(indexerPattern, false);
        if (state) {
            indexerPattern->InitAccessibilityClickEvent();
            indexerPattern->SetIsScreenReaderOn(true);
        } else {
            indexerPattern->RemoveAccessibilityClickEvent();
            indexerPattern->SetIsScreenReaderOn(false);
        }
        return true;
    }
private:
    WeakPtr<ArcIndexerPattern> weakPattern_;
};

void ArcIndexerPattern::RemoveAccessibilityClickEvent()
{
    if (collapsedNode_.Upgrade() != nullptr) {
        auto collapsedNode = collapsedNode_.Upgrade();
        CHECK_NULL_VOID(collapsedNode);
        auto collapsedGesture = collapsedNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(collapsedGesture);
        if (collapsedClickListener_) {
            collapsedGesture->RemoveClickEvent(collapsedClickListener_);
            collapsedClickListener_ = nullptr;
        }
    }
    if (expandedNode_.Upgrade() != nullptr) {
        auto expandedNode = expandedNode_.Upgrade();
        CHECK_NULL_VOID(expandedNode);
        auto expandedNodGesture = expandedNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(expandedNodGesture);
        if (expandedClickListener_) {
            expandedNodGesture->RemoveClickEvent(expandedClickListener_);
            expandedClickListener_ = nullptr;
        }
    }
}

void ArcIndexerPattern::InitAccessibilityClickEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    if (collapsedNode_.Upgrade() != nullptr) {
        auto collapsedNode = collapsedNode_.Upgrade();
        CHECK_NULL_VOID(collapsedNode);
        auto textAccessibilityProperty = collapsedNode->GetAccessibilityProperty<TextAccessibilityProperty>();
        CHECK_NULL_VOID(textAccessibilityProperty);
        textAccessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::YES_STR);
        textAccessibilityProperty->SetAccessibilityText(indexerTheme->GetAccessibilityCollapse());
        textAccessibilityProperty->SetAccessibilityRole(BUTTON_ROLE);
        auto collapsedGesture = collapsedNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(collapsedGesture);
        auto collapsedclickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->FireAccessbilityCollapsed();
        };
        collapsedClickListener_ = MakeRefPtr<ClickEvent>(std::move(collapsedclickCallback));
        collapsedGesture->AddClickEvent(collapsedClickListener_);
    }
    if (expandedNode_.Upgrade() != nullptr) {
        auto expandedNode = expandedNode_.Upgrade();
        CHECK_NULL_VOID(expandedNode);
        auto textAccessibilityProperty = expandedNode->GetAccessibilityProperty<TextAccessibilityProperty>();
        CHECK_NULL_VOID(textAccessibilityProperty);
        textAccessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::YES_STR);
        textAccessibilityProperty->SetAccessibilityText(indexerTheme->GetAccessibilityExpand());
        textAccessibilityProperty->SetAccessibilityRole(BUTTON_ROLE);
        auto expandedNodGesture = expandedNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(expandedNodGesture);
        auto expandedCallback = [weak = WeakClaim(this)](GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->FireAccessbilityExpanded();
        };
        expandedClickListener_ = MakeRefPtr<ClickEvent>(std::move(expandedCallback));
        expandedNodGesture->AddClickEvent(expandedClickListener_);
    }
}

void ArcIndexerPattern::InitializeAccessibility()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilitySAObserverCallback_ = std::make_shared<ArcIndexerAccessibilitySAObserverCallback>(
        WeakClaim(this), host->GetAccessibilityId());
    accessibilityManager->RegisterAccessibilitySAObserverCallback(host->GetAccessibilityId(),
        accessibilitySAObserverCallback_);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetAccessibilityGroup(true);
}

void ArcIndexerPattern::FireAccessbilityExpanded()
{
    isClickActionFire_ = true;
    isNewHeightCalculated_ = true;
    lastCollapsingMode_ = currectCollapsingMode_;
    currectCollapsingMode_ = ArcIndexerCollapsingMode::NONE;
    ArcExpandedAnimation(fullArrayValue_.size() - 1);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkModifyDone();
    host->MarkDirtyNode();
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    host->OnAccessibilityEvent(AccessibilityEventType::ANNOUNCE_FOR_ACCESSIBILITY,
        indexerTheme->GetAccessibilityExpanded());
}

void ArcIndexerPattern::FireAccessbilityCollapsed()
{
    isClickActionFire_ = true;
    isNewHeightCalculated_ = true;
    lastCollapsingMode_ = currectCollapsingMode_;
    currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
    ArcCollapedAnimation(ARC_INDEXER_COLLAPSE_ITEM_COUNT);
    IndexNodeCollapsedAnimation();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    host->OnAccessibilityEvent(AccessibilityEventType::ANNOUNCE_FOR_ACCESSIBILITY,
        indexerTheme->GetAccessibilityCollapsed());
}

void ArcIndexerPattern::FireAccessibilityIndexChanged(bool selectChanged, bool fromTouchUp)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    if (fromTouchUp) {
        AccessibilityEventType type = AccessibilityEventType::SELECTED;
        host->OnAccessibilityEvent(type);
    }
    if (selectChanged) {
        ShowBubble(selectChanged);
        if (!fromTouchUp) {
            accessibilityProperty->SetAccessibilityText(GetChildNodeContent(selected_));
            host->OnAccessibilityEvent(AccessibilityEventType::TEXT_CHANGE);
        }
    }
}

void ArcIndexerPattern::ResetArrayValue(bool isModeChanged)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<ArcIndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto itemCountChanged = false;
    fullCount_ = static_cast<int32_t>(fullArrayValue_.size());
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
    bool isChange = isModeChanged || itemCountChanged;
    removeBubble |= isChange;
    if (removeBubble) {
        RemoveBubble();
    }
}

void ArcIndexerPattern::InitTouchEvent ()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
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
            if (!indexerPattern->AtArcHotArea(offset) || !indexerPattern->atomicAnimateOp_) {
                indexerPattern->isTouch_ = false;
                indexerPattern->StartDelayTask(ARC_INDEXER_BUBBLE_ENTER_DURATION + ARC_INDEXER_BUBBLE_WAIT_DURATION);
                return;
            }
            auto touchType = info.GetTouches().front().GetTouchType();
            if (touchType == TouchType::DOWN) {
                indexerPattern->isTouch_ = true;
                indexerPattern->OnTouchDown(info);
            } else if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
                indexerPattern->isTouch_ = false;
                indexerPattern->OnTouchUp(info);
            }
        };
        touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
        gesture->AddTouchEvent(touchListener_);
    }
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
    strokeWidth_ = lastItemSize_;
    arcCenter_ = layoutAlgorithm->GetArcCenter();
    startAngle_ = layoutAlgorithm->GetStartAngle();
    sweepAngle_ = layoutAlgorithm->GetSweepAngle();
    arcRadius_ = layoutAlgorithm->GetArcRadius();
    itemRadius_ = layoutAlgorithm->GetitemRadius();
    auto size = layoutAlgorithm->GetArcSize();
    auto stepAngle = layoutAlgorithm->GetstepAngle();
    if ((arcIndexerSize_ != size && autoCollapse_) || (stepAngle_ != stepAngle)) {
        arcIndexerSize_ = size;
        stepAngle_ = stepAngle;
        isNewHeightCalculated_ = true;
        auto hostNode = dirty->GetHostNode();
        StartCollapseDelayTask(hostNode, ARC_INDEXER_COLLAPSE_WAIT_DURATION);
    } else {
        initialized_ = true;
    }

    return true;
}

RefPtr<FrameNode> ArcIndexerPattern::BuildIcon()
{
    CHECK_EQUAL_RETURN(arcArrayValue_.size(), 0, nullptr);
    int32_t indexerSize = static_cast<int32_t>(arcArrayValue_.size() - 1);
    auto icon = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(icon, nullptr);
    ImageSourceInfo imageSourceInfo;
    if (arcArrayValue_[indexerSize].second == ArcIndexerBarState::COLLAPSED) {
        imageSourceInfo.SetResourceId(InternalResource::ResourceId::IC_PUBLIC_ARROW_LEFT_SVG);
    } else if (arcArrayValue_[indexerSize].second == ArcIndexerBarState::EXPANDED) {
        imageSourceInfo.SetResourceId(InternalResource::ResourceId::IC_PUBLIC_ARROW_RIGHT_SVG);
    }
    imageSourceInfo.SetFillColor(Color(ARC_INDEXER_STR_DOT_COLOR));
    auto iconLayoutProperty = icon->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(iconLayoutProperty, nullptr);
    iconLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    // size
    iconLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(lastItemSize_), CalcLength(lastItemSize_)));
    auto iconPadding = Dimension(2.0f, DimensionUnit::VP).ConvertToPx(); // set icon padding 2.0f
    iconLayoutProperty->UpdatePadding({ CalcLength(iconPadding), CalcLength(iconPadding), CalcLength(iconPadding),
        CalcLength(iconPadding), CalcLength(iconPadding), CalcLength(iconPadding) });

    icon->MarkModifyDone();
    icon->MarkDirtyNode();
    return icon;
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
    bool hasIconNode = false;
    if (layoutProperty->GetIsPopupValue(false)) {
        lastChildCount -= 1;
    }
    auto autoCollapse = layoutProperty->GetAutoCollapse().value_or(true);
    if (indexerSize != lastChildCount) {
        host->Clean();
        layoutProperty->UpdateIsPopup(false);
        if (autoCollapse && (indexerSize > ARC_INDEXER_COLLAPSE_ITEM_COUNT)) {
            indexerSize -= 1;
            hasIconNode = true;
        }
        for (int32_t index = 0; index < indexerSize; index++) {
            auto indexerChildNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_VOID(indexerChildNode);
            host->AddChild(indexerChildNode);
        }
        if (hasIconNode) {
            auto icon = BuildIcon();
            CHECK_NULL_VOID(icon);
            host->AddChild(icon);
        }
    }
    std::vector<std::string> arrayValueStrs;
    auto it = arcArrayValue_.begin();
    while (it != arcArrayValue_.end()) {
        if (hasIconNode && (it == arcArrayValue_.end() - 1)) {
            break;
        }
        arrayValueStrs.push_back(it->first);
        ++it;
    }
    layoutProperty->UpdateActualArrayValue(arrayValueStrs);
}

void ArcIndexerPattern::BuildFullArrayValue()
{
    arcArrayValue_.clear();
    int32_t startIndex = 0;
    auto arraySize = (fullCount_ > ARC_INDEXER_ITEM_MAX_COUNT) ? ARC_INDEXER_ITEM_MAX_COUNT : fullCount_;
    if (!autoCollapse_ && arraySize == ARC_INDEXER_ITEM_MAX_COUNT) {
        arraySize = arraySize + 1;
    }
    for (int32_t i = startIndex; i < startIndex + arraySize; ++i) {
        if (i >= 0 && i < static_cast<int32_t>(fullArrayValue_.size())) {
            arcArrayValue_.push_back(std::pair(fullArrayValue_.at(i), ArcIndexerBarState::INVALID));
        }
    }
    if (autoCollapse_ && arraySize > ARC_INDEXER_COLLAPSE_ITEM_COUNT) {
        arcArrayValue_.push_back(
            std::pair(StringUtils::Str16ToStr8(ARC_INDEXER_STR_COLLAPSED), ArcIndexerBarState::COLLAPSED));
    }
}

void ArcIndexerPattern::CollapseArrayValue()
{
    if (fullCount_ <= ARC_INDEXER_COLLAPSE_ITEM_COUNT ||
        currectCollapsingMode_ == ArcIndexerCollapsingMode::NONE) {
        BuildFullArrayValue();
    } else {
        ApplyFourPlusOneMode();
    }
}

void ArcIndexerPattern::UpdateStartAndEndIndexByTouch()
{
    focusIndex_ = selected_;
    if (!autoCollapse_) {
        return;
    }
    if (currectCollapsingMode_ == ArcIndexerCollapsingMode::FOUR) {
        return;
    }
    if (fullCount_ <= ARC_INDEXER_COLLAPSE_ITEM_COUNT) {
        startIndex_ = 0;
        endIndex_ = fullCount_ - 1;
    } else {
        startIndex_ = selected_;
        if (selected_ > fullCount_ - ARC_INDEXER_COLLAPSE_ITEM_COUNT) {
            startIndex_ = fullCount_ - ARC_INDEXER_COLLAPSE_ITEM_COUNT;
        }
        if (startIndex_ > ARC_INDEXER_ITEM_MAX_COUNT - ARC_INDEXER_COLLAPSE_ITEM_COUNT) {
            startIndex_ = ARC_INDEXER_ITEM_MAX_COUNT - ARC_INDEXER_COLLAPSE_ITEM_COUNT;
        }
        endIndex_ = startIndex_ + ARC_INDEXER_COLLAPSE_ITEM_COUNT;
    }
    focusIndex_ = selected_ - startIndex_;
}

void ArcIndexerPattern::UpdateStartAndEndIndexbySelected()
{
    focusIndex_ = selected_;
    if (!autoCollapse_) {
        return;
    }
    auto arraySize = (fullCount_ > ARC_INDEXER_ITEM_MAX_COUNT) ? ARC_INDEXER_ITEM_MAX_COUNT : fullCount_;
    if (currectCollapsingMode_ == ArcIndexerCollapsingMode::FOUR) {
        focusIndex_ = selected_ - startIndex_;
        if (endIndex_ > arraySize) {
            endIndex_ = arraySize;
        }
        if (selected_ >= startIndex_ && selected_ < endIndex_) {
            selected_ -= startIndex_;
            focusIndex_ = selected_;
        } else if (selected_ >= endIndex_ - 1) {
            endIndex_ = selected_ + 1;
            if (endIndex_ > arraySize) {
                endIndex_ = arraySize;
            }
            startIndex_ = endIndex_ - ARC_INDEXER_COLLAPSE_ITEM_COUNT;
            selected_ = ARC_INDEXER_COLLAPSE_ITEM_COUNT - 1;
            focusIndex_ =  ARC_INDEXER_COLLAPSE_ITEM_COUNT - 1;
        } else if (selected_ < startIndex_) {
            startIndex_ = selected_;
            if (startIndex_ < 0) {
                startIndex_ = 0;
            }
            selected_ = 0;
            focusIndex_ = 0;
            endIndex_ = startIndex_ + ARC_INDEXER_COLLAPSE_ITEM_COUNT;
        }
    } else {
        focusIndex_ = selected_;
    }
}

void ArcIndexerPattern::ApplyFourPlusOneMode()
{
    UpdateStartAndEndIndexbySelected();
    arcArrayValue_.clear();
    for (int32_t index = startIndex_; index < endIndex_; index++) {
        if (index >= 0 && index < static_cast<int32_t>(fullArrayValue_.size())) {
            arcArrayValue_.push_back(std::pair(fullArrayValue_.at(index), ArcIndexerBarState::INVALID));
        }
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
        CHECK_NULL_VOID(pattern);
        if (!pattern->atomicAnimateOp_ || info.GetInputEventType() == InputEventType::AXIS) {
            return;
        }
        pattern->MoveIndexByOffset(info.GetLocalLocation());
    };

    auto onActionUpdate = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->atomicAnimateOp_) {
            return;
        }
        if (info.GetInputEventType() == InputEventType::AXIS) {
            return;
        }
        pattern->MoveIndexByOffset(info.GetLocalLocation());
    };

    auto onActionEnd = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->StartDelayTask(ARC_INDEXER_BUBBLE_ENTER_DURATION + ARC_INDEXER_BUBBLE_WAIT_DURATION);
    };

    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(onActionStart), std::move(onActionUpdate), std::move(onActionEnd), nullptr);
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
    OnSelect();
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
        selectChanged_ = false;
        isNewHeightCalculated_ = true;
        lastCollapsingMode_ = currectCollapsingMode_;
        if (arcArrayValue_[nextSelectIndex].second == ArcIndexerBarState::COLLAPSED && autoCollapse_) {
            currectCollapsingMode_ = ArcIndexerCollapsingMode::FOUR;
            ArcCollapedAnimation(ARC_INDEXER_COLLAPSE_ITEM_COUNT);
            IndexNodeCollapsedAnimation();
        } else {
            currectCollapsingMode_ = ArcIndexerCollapsingMode::NONE;
            auto arraySize = (fullCount_ > ARC_INDEXER_ITEM_MAX_COUNT) ? ARC_INDEXER_ITEM_MAX_COUNT : fullCount_;
            ArcExpandedAnimation(arraySize - 1);
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
    UpdateStartAndEndIndexByTouch();
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
    collapsedAnimateIndex_ = static_cast<int32_t>(total);
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
            auto expandedNode = pattern->expandedNode_.Upgrade();
            CHECK_NULL_VOID(expandedNode);
            expandedNode->OnAccessibilityEvent(AccessibilityEventType::REQUEST_FOCUS);
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
            auto collapsedNode = pattern->collapsedNode_.Upgrade();
            CHECK_NULL_VOID(collapsedNode);
            collapsedNode->OnAccessibilityEvent(AccessibilityEventType::REQUEST_FOCUS);
        });
    lastCollapsingMode_ = currectCollapsingMode_;
}

void ArcIndexerPattern::StartIndexerNodeDisappearAnimation(int32_t nodeIndex)
{
    auto host = GetHost();
    auto total = fullArrayValue_.size();
    if (nodeIndex > static_cast<int32_t>(total)) {
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

void ArcIndexerPattern::OnSelect()
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

int32_t ArcIndexerPattern::GetFocusIndex(int32_t selected)
{
    int32_t focusIndex = focusIndex_;
    if (currectCollapsingMode_ == ArcIndexerCollapsingMode::NONE) {
        focusIndex = selected;
    }
    return focusIndex;
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
    int32_t index = 0;
    auto total = host->GetTotalChildCount();
    if (layoutProperty->GetIsPopupValue(false)) {
        total -= 1;
    }
    UpdateIndexerRender();
    int32_t focusIndex = GetFocusIndex(selected_);
    auto radiusSize =  Dimension(lastItemSize_ * HALF);
    bool isSetIndexStyle = false;
    for (int32_t i = 0; i < total; i++) {
        auto child = host->GetChildByIndex(i);
        CHECK_NULL_VOID(child);
        auto childNode = child->GetHostNode();
        CHECK_NULL_VOID(childNode);
        UpdateChildNodeStyle(index);
        auto childRenderContext = childNode->GetRenderContext();
        CHECK_NULL_VOID(childRenderContext);
        childRenderContext->UpdateBorderRadius({ radiusSize, radiusSize, radiusSize, radiusSize });
        auto nodeStr = GetChildNodeContent(index);
        SetChildNodeStyle(index, nodeStr, fromTouchUp);
        if (!isSetIndexStyle && (index == childPressIndex_ || index == childFocusIndex_ || index == focusIndex)) {
            isSetIndexStyle = true;
            SetFocusIndexStyle(index, nodeStr, isTextNodeInTree);
        } else {
            if (!fromTouchUp || animateSelected_ == lastSelected_ || index != lastSelected_) {
                childRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
            }
        }
        index++;
        childNode->MarkModifyDone();
        if (isTextNodeInTree) childNode->MarkDirtyNode();
    }
    if (!fromTouchUp && currectCollapsingMode_ == ArcIndexerCollapsingMode::NONE
        && currectCollapsingMode_ != lastCollapsingMode_) {
        IndexNodeExpandedAnimation();
    }
    FireAccessibilityIndexChanged(selectChanged, fromTouchUp);
}

void ArcIndexerPattern::UpdateIndexerRender()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto indexerRenderContext = host->GetRenderContext();
    CHECK_NULL_VOID(indexerRenderContext);
    auto indexerRadius = Dimension(arcRadius_, DimensionUnit::VP);
    indexerRenderContext->UpdateBorderRadius({ indexerRadius, indexerRadius, indexerRadius, indexerRadius });
    indexerRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
}

std::string ArcIndexerPattern::GetChildNodeContent(int32_t index)
{
    index = std::clamp(index, 0, static_cast<int32_t>(arcArrayValue_.size()) - 1);
    auto nodeStr = autoCollapse_ && (arcArrayValue_[index].second != ArcIndexerBarState::INVALID) ?
        (arcArrayValue_[index].second == ArcIndexerBarState::COLLAPSED ?
        StringUtils::Str16ToStr8(ARC_INDEXER_STR_COLLAPSED) :
        StringUtils::Str16ToStr8(ARC_INDEXER_STR_EXPANDED)) : arcArrayValue_[index].first;
    return nodeStr;
}

void ArcIndexerPattern::UpdateChildNodeStyle(int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<ArcIndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto child = host->GetChildByIndex(index);
    CHECK_NULL_VOID(child);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    auto childNode = child->GetHostNode();
    CHECK_NULL_VOID(childNode);
    UpdateChildBoundary(childNode);
    auto childRenderContext = childNode->GetRenderContext();
    CHECK_NULL_VOID(childRenderContext);
    childRenderContext->SetClipToBounds(true);
    if (arcArrayValue_[index].second != ArcIndexerBarState::INVALID) {
        float itemAngle = CalcArcItemAngle(index) + STR_DOT_ROTATE_ANGLE;
        childRenderContext->UpdateTransformRotate(Vector5F(0.0f, 0.0f, 1.0f, itemAngle, 0.0f));
    } else {
        auto nodeLayoutProperty = childNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(nodeLayoutProperty);
        nodeLayoutProperty->UpdateTextColor(
            layoutProperty->GetColor().value_or(indexerTheme->GetDefaultTextColor()));
    }
}

void ArcIndexerPattern::SetChildNodeAccessibility(const RefPtr<FrameNode>& childNode, const std::string &nodeStr)
{
    CHECK_NULL_VOID(childNode);
    auto textAccessibilityProperty = childNode->GetAccessibilityProperty<TextAccessibilityProperty>();
    if (textAccessibilityProperty) {
        textAccessibilityProperty->SetSelected(false);
        if (StringUtils::Str16ToStr8(ARC_INDEXER_STR_EXPANDED) == nodeStr) {
            expandedNode_ = childNode;
            if (AceApplicationInfo::GetInstance().IsAccessibilityEnabled() || isScreenReaderOn_) {
                InitAccessibilityClickEvent();
            }
        }
        if (StringUtils::Str16ToStr8(ARC_INDEXER_STR_COLLAPSED) == nodeStr) {
            collapsedNode_ = childNode;
            if (AceApplicationInfo::GetInstance().IsAccessibilityEnabled() || isScreenReaderOn_) {
                InitAccessibilityClickEvent();
            }
        }
    }
}

void ArcIndexerPattern::SetChildNodeStyle(int32_t index, const std::string &nodeStr, bool fromTouchUp)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<ArcIndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    auto child = host->GetChildByIndex(index);
    CHECK_NULL_VOID(child);
    auto childNode = child->GetHostNode();
    CHECK_NULL_VOID(childNode);
    auto childRenderContext = childNode->GetRenderContext();
    CHECK_NULL_VOID(childRenderContext);
    UpdateChildBoundary(childNode);
    if (StringUtils::Str16ToStr8(ARC_INDEXER_STR_EXPANDED) != nodeStr &&
        StringUtils::Str16ToStr8(ARC_INDEXER_STR_COLLAPSED) != nodeStr) {
        auto nodeLayoutProperty = childNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(nodeLayoutProperty);
        Dimension borderWidth;
        nodeLayoutProperty->UpdateContent(nodeStr);
        nodeLayoutProperty->UpdateMaxLines(1);
        nodeLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
        nodeLayoutProperty->UpdateEllipsisMode(EllipsisMode::TAIL);
        nodeLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
        nodeLayoutProperty->UpdateAlignment(Alignment::CENTER);
        nodeLayoutProperty->UpdateBorderWidth(
            { borderWidth, borderWidth, borderWidth, borderWidth, borderWidth, borderWidth });
        childRenderContext->ResetBlendBorderColor();
        auto defaultFont = layoutProperty->GetFont().value_or(indexerTheme->GetDefaultTextStyle());
        nodeLayoutProperty->UpdateFontSize(defaultFont.GetFontSize());
        nodeLayoutProperty->UpdateFontWeight(defaultFont.GetFontWeight());
        nodeLayoutProperty->UpdateFontFamily(defaultFont.GetFontFamilies());
        nodeLayoutProperty->UpdateItalicFontStyle(defaultFont.GetFontStyle());
    }
    SetChildNodeAccessibility(childNode, nodeStr);
    if (!fromTouchUp && currectCollapsingMode_ == ArcIndexerCollapsingMode::NONE &&
        currectCollapsingMode_ != lastCollapsingMode_) {
        UpdateIndexerNodeOpacityByIdx(childRenderContext, index);
    }
}

void ArcIndexerPattern::SetFocusIndexStyle(int32_t index, const std::string &nodeStr, bool isTextNodeInTree)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto child = host->GetChildByIndex(index);
    CHECK_NULL_VOID(child);
    auto layoutProperty = host->GetLayoutProperty<ArcIndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto childNode = child->GetHostNode();
    CHECK_NULL_VOID(childNode);
    auto paintProperty = host->GetPaintProperty<ArcIndexerPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    UpdateChildBoundary(childNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto indexerTheme = pipeline->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    auto childRenderContext = childNode->GetRenderContext();
    CHECK_NULL_VOID(childRenderContext);
    auto nodeLayoutProperty = childNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(nodeLayoutProperty);
    nodeLayoutProperty->UpdateContent(nodeStr);
    nodeLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    nodeLayoutProperty->UpdateAlignment(Alignment::CENTER);
    childRenderContext->UpdateBackgroundColor(
        paintProperty->GetSelectedBackgroundColor().value_or(indexerTheme->GetSelectedBackgroundColorArc()));
    if (index != childFocusIndex_) {
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
    if (isClickActionFire_ || index == 0) {
        isClickActionFire_ = false;
        return;
    }
    auto textAccessibilityProperty = childNode->GetAccessibilityProperty<TextAccessibilityProperty>();
    if (textAccessibilityProperty) {
        textAccessibilityProperty->SetSelected(true);
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
        default:
            break;
    }
}

void ArcIndexerPattern::StartIndexerNodeAppearAnimation(int32_t nodeIndex)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto total = fullArrayValue_.size();
    if (nodeIndex > static_cast<int32_t>(total)) {
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

void ArcIndexerPattern::ShowBubble(bool isShow)
{
    CHECK_EQUAL_VOID(isShow, false);
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
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    return textNode;
}

void ArcIndexerPattern::UpdateBubbleView()
{
    CHECK_NULL_VOID(popupNode_);
    auto currentListData = std::vector<std::string>();
    UpdateBubbleLetterView(false, currentListData);
    auto textRenderContext = popupNode_->GetRenderContext();
    CHECK_NULL_VOID(textRenderContext);
    auto radius = Dimension(ARC_BUBBLE_BOX_RADIUS, DimensionUnit::VP);
    textRenderContext->UpdateBorderRadius({ radius, radius, radius, radius });
    textRenderContext->UpdateBackShadow(Shadow::CreateShadow(ShadowStyle::OuterDefaultLG));

    UpdateBubbleBackgroundView();
    textRenderContext->SetClipToBounds(true);
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
    CHECK_NULL_VOID(indexerTheme);
    auto bubbleRenderContext = popupNode_->GetRenderContext();
    CHECK_NULL_VOID(bubbleRenderContext);
    if (paintProperty->GetPopupBackgroundBlurStyle().has_value()) {
        BlurStyleOption styleOption = paintProperty->GetPopupBackgroundBlurStyle().value();
        bubbleRenderContext->UpdateBackBlurStyle(styleOption);
    }
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
    auto radius = Dimension(ARC_BUBBLE_BOX_RADIUS, DimensionUnit::VP);
    letterNodeRenderContext->UpdateBorderRadius({ radius, radius, radius, radius });
    letterNodeRenderContext->UpdateBackgroundColor(
        paintProperty->GetPopupBackground().value_or(indexerTheme->GetPopupBackgroundColor()));
    letterNodeRenderContext->SetClipToBounds(true);
    letterNode->MarkModifyDone();
    letterNode->MarkDirtyNode();
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

    int32_t focusIndex = GetFocusIndex(selected_);
    auto contenStr = arcArrayValue_[childPressIndex_ >= 0 ? childPressIndex_ : focusIndex].first;
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
    letterLayoutProperty->UpdatePadding({ CalcLength(textPadding), CalcLength(textPadding), CalcLength(textPadding),
        CalcLength(textPadding), CalcLength(textPadding), CalcLength(textPadding) });

    auto BubbleSize = Dimension(ARC_BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    letterLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(BubbleSize), CalcLength(BubbleSize)));
}

RefPtr<FrameNode> ArcIndexerPattern::GetLetterNode()
{
    CHECK_NULL_RETURN(popupNode_, nullptr);
    return DynamicCast<FrameNode>(popupNode_);
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
    auto arraySize = (fullCount_ > ARC_INDEXER_ITEM_MAX_COUNT) ? ARC_INDEXER_ITEM_MAX_COUNT : fullCount_;
    return (selected_ >= 0 && selected_ < arraySize);
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

int32_t ArcIndexerPattern::GetActualIndex(int32_t selectIndex)
{
    int32_t actualIndex = selectIndex;
    if (!autoCollapse_) {
        return actualIndex;
    }
    auto arcIndex = selected_;
    if (arcIndex > 0) {
        arcIndex = std::find(fullArrayValue_.begin(), fullArrayValue_.end(), arcArrayValue_.at(arcIndex).first) -
                   fullArrayValue_.begin();
    } else if (arcIndex == 0) {
        arcIndex = startIndex_;
    }
    return arcIndex;
}

void ArcIndexerPattern::FireOnSelect(int32_t selectIndex, bool fromPress)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto indexerEventHub = host->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(indexerEventHub);
    auto actualIndex = selectIndex;
    if (fromPress) {
        actualIndex = GetActualIndex(selectIndex);
    }
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
    auto isMeasureBoundary = layoutProperty->GetPropertyChangeFlag() ==  PROPERTY_UPDATE_NORMAL;
    if (frameNode->GetHostTag() == V2::TEXT_ETS_TAG) {
        auto pattern = DynamicCast<TextPattern>(frameNode->GetPattern());
        CHECK_NULL_VOID(pattern);
        pattern->SetIsMeasureBoundary(isMeasureBoundary);
    }
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
    if (AceApplicationInfo::GetInstance().IsAccessibilityEnabled() || isScreenReaderOn_) {
        return true;
    }
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
