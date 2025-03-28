/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "base/log/dump_log.h"
#include "base/memory/ace_type.h"
#include "bridge/common/utils/utils.h"
#include "core/animation/animator.h"
#include "core/common/container.h"
#include "core/common/font_manager.h"
#include "core/common/vibrator/vibrator_utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/popup_param.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/indexer/indexer_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/indexer/indexer_theme.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/list/list_event_hub.h"
#include "core/components_ng/pattern/list/list_item_layout_property.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_layout_property.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
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
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TOTAL_NUMBER = 1000;
constexpr double PERCENT_100 = 100.0;
constexpr int32_t MODE_SEVEN = 6; // items is divided into 6 groups in (7 + #) mode
constexpr int32_t MODE_FIVE = 4; // items is divided into 4 groups in (5 + #) mode
}
void IndexerPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    enableHapticFeedback_ = layoutProperty->GetEnableHapticFeedback().value_or(true);
    bool autoCollapseModeChanged = true;
    bool itemCountChanged = false;
    InitArrayValue(autoCollapseModeChanged, itemCountChanged);
    ReportSelectEvent();
    BuildArrayValueItems();
    bool removeBubble = false;
    auto usePopup = layoutProperty->GetUsingPopup().value_or(false);
    if (isPopup_ != usePopup) {
        isPopup_ = usePopup;
        removeBubble = !isPopup_;
    }
    // Remove bubble if auto-collapse mode switched on/off or if items count changed
    removeBubble = removeBubble || autoCollapseModeChanged || itemCountChanged;
    if (removeBubble) {
        RemoveBubble();
    }

    isNewHeightCalculated_ = false;
    auto itemSize =
        layoutProperty->GetItemSize().value_or(Dimension(INDEXER_ITEM_SIZE, DimensionUnit::VP)).ConvertToPx();
    auto indexerSizeChanged = (itemCountChanged || !NearEqual(itemSize, lastItemSize_));
    lastItemSize_ = itemSize;
    auto needMarkDirty = (layoutProperty->GetPropertyChangeFlag() == PROPERTY_UPDATE_NORMAL);
    ApplyIndexChanged(needMarkDirty, initialized_ && selectChanged_, false, indexerSizeChanged);
    auto gesture = host->GetOrCreateGestureEventHub();
    if (gesture) {
        InitPanEvent(gesture);
        InitTouchEvent(gesture);
    }
    InitInputEvent();
    InitOnKeyEvent();
    SetAccessibilityAction();
}

void IndexerPattern::InitArrayValue(bool& autoCollapseModeChanged, bool& itemCountChanged)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto autoCollapse = layoutProperty->GetAutoCollapse().value_or(true);
    if (!isNewHeightCalculated_) {
        autoCollapseModeChanged = autoCollapse != lastAutoCollapse_;
        lastAutoCollapse_ = autoCollapse;
        auto newArray = layoutProperty->GetArrayValue().value_or(std::vector<std::string>());
        bool arrayValueChanged = newArray.size() != fullArrayValue_.size() || newArray != fullArrayValue_;
        if (arrayValueChanged || autoCollapseModeChanged) {
            lastCollapsingMode_ = IndexerCollapsingMode::INVALID;
        }
        fullArrayValue_ = newArray;
    }
    auto propSelect = layoutProperty->GetSelected().value();
    if (fullArrayValue_.size() > 0) {
        if (autoCollapse) {
            sharpItemCount_ = fullArrayValue_.at(0) == StringUtils::Str16ToStr8(INDEXER_STR_SHARP) ? 1 : 0;
            CollapseArrayValue();
            if ((lastCollapsingMode_ == IndexerCollapsingMode::SEVEN ||
                    lastCollapsingMode_ == IndexerCollapsingMode::FIVE) && (propSelect > sharpItemCount_)) {
                propSelect = GetAutoCollapseIndex(propSelect);
            } else {
                collapsedIndex_ = 0;
            }
        } else {
            sharpItemCount_ = 0;
            BuildFullArrayValue();
        }
        itemCountChanged = (itemCount_ != static_cast<int32_t>(arrayValue_.size()));
        itemCount_ = static_cast<int32_t>(arrayValue_.size());
    } else {
        sharpItemCount_ = 0;
        itemCountChanged = (itemCount_ != 0);
        itemCount_ = 0;
        collapsedIndex_ = 0;
        arrayValue_.clear();
        collapsedItemNums_.clear();
    }
    if (propSelect != selected_ || collapsedIndex_ != lastCollapsedIndex_) {
        selected_ = propSelect;
        lastCollapsedIndex_ = collapsedIndex_;
        selectChanged_ = true;
        ResetStatus();
    } else if (!isNewHeightCalculated_) {
        selectChanged_ = false;
    }
}

void IndexerPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (!touchListener_) {
        CHECK_NULL_VOID(gestureHub);
        auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
            auto indexerPattern = weak.Upgrade();
            CHECK_NULL_VOID(indexerPattern);
            if (info.GetTouches().empty()) {
                return;
            }
            TouchType touchType = info.GetTouches().front().GetTouchType();
            if (touchType == TouchType::DOWN) {
                indexerPattern->isTouch_ = true;
                indexerPattern->OnTouchDown(info);
            } else if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
                indexerPattern->isTouch_ = false;
                indexerPattern->OnTouchUp(info);
            }
        };
        touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
        gestureHub->AddTouchEvent(touchListener_);
    }
}

bool IndexerPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        initialized_ = true;
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto indexerLayoutAlgorithm = DynamicCast<IndexerLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(indexerLayoutAlgorithm, false);
    itemHeight_ = indexerLayoutAlgorithm->GetItemHeight();
    auto height = indexerLayoutAlgorithm->GetMaxContentHeight();
    if (maxContentHeight_ != height && lastAutoCollapse_) {
        maxContentHeight_ = height;
        isNewHeightCalculated_ = true;
        auto hostNode = dirty->GetHostNode();
        StartCollapseDelayTask(hostNode, INDEXER_COLLAPSE_WAIT_DURATION);
    } else {
        initialized_ = true;
    }
    return true;
}

void IndexerPattern::BuildArrayValueItems()
{
    int32_t indexerSize = static_cast<int32_t>(arrayValue_.size());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<IndexerLayoutProperty>();
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
            InitChildInputEvent(indexerChildNode, index);
            host->AddChild(indexerChildNode);
        }
    }
    std::vector<std::string> arrayValueStrs;
    for (auto indexerItem : arrayValue_) {
        arrayValueStrs.push_back(indexerItem.first);
    }
    layoutProperty->UpdateActualArrayValue(arrayValueStrs);
}

void IndexerPattern::BuildFullArrayValue()
{
    arrayValue_.clear();
    collapsedItemNums_.clear();
    autoCollapse_ = false;
    collapsedIndex_ = 0;
    for (auto indexerLetter : fullArrayValue_) {
        arrayValue_.push_back(std::pair(indexerLetter, false));
        collapsedItemNums_.push_back(1);
    }
}

void IndexerPattern::CollapseArrayValue()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto itemSize =
        layoutProperty->GetItemSize().value_or(Dimension(INDEXER_ITEM_SIZE, DimensionUnit::VP)).ConvertToVp();
    int32_t maxItemsCount = 0;
    auto height = Dimension(maxContentHeight_, DimensionUnit::PX).ConvertToVp();
    if (height > 0 && itemSize > 0) {
        maxItemsCount = static_cast<int32_t>(height / itemSize);
    }
    int32_t fullArraySize = static_cast<int32_t>(fullArrayValue_.size());
    if (NearZero(height) || maxItemsCount >= fullArraySize ||
        fullArraySize - sharpItemCount_ <= INDEXER_NINE_CHARACTERS_CHECK) {
        if (lastCollapsingMode_ != IndexerCollapsingMode::NONE) {
            lastCollapsingMode_ = IndexerCollapsingMode::NONE;
            BuildFullArrayValue();
        }
    } else if (fullArraySize - sharpItemCount_ <= INDEXER_THIRTEEN_CHARACTERS_CHECK) {
        if (lastCollapsingMode_ != IndexerCollapsingMode::FIVE) {
            lastCollapsingMode_ = IndexerCollapsingMode::FIVE;
            ApplyFivePlusOneMode(fullArraySize);
        }
    } else {
        // 13 here is count of visible items in 7 + 1 mode (i.e. 7 characters 6 dots and # item if exists)
        if (maxItemsCount >= INDEXER_THIRTEEN_CHARACTERS_CHECK + sharpItemCount_) {
            if (lastCollapsingMode_ != IndexerCollapsingMode::SEVEN) {
                lastCollapsingMode_ = IndexerCollapsingMode::SEVEN;
                ApplySevenPlusOneMode(fullArraySize);
            }
        } else {
            if (lastCollapsingMode_ != IndexerCollapsingMode::FIVE) {
                lastCollapsingMode_ = IndexerCollapsingMode::FIVE;
                ApplyFivePlusOneMode(fullArraySize);
            }
        }
    }
}

void IndexerPattern::ApplySevenPlusOneMode(int32_t fullArraySize)
{
    // 7 + # mode
    // minimum items in one group (totally 6 groups) including
    // visible character in the group and excluding the first always visible item
    auto cmin = static_cast<int32_t>((fullArraySize - 1 - sharpItemCount_) / 6);
    auto gmax = (fullArraySize - 1 - sharpItemCount_) - cmin * 6; // number of groups with maximum items count
    auto cmax = cmin + 1; // maximum items in one group including visible character in the group
    auto gmin = 6 - gmax; // number of groups with minimum items count

    arrayValue_.clear();
    collapsedItemNums_.clear();
    arrayValue_.push_back(std::pair(fullArrayValue_.at(0), false)); // push the first item
    collapsedItemNums_.push_back(1);
    if (sharpItemCount_ > 0) {
        arrayValue_.push_back(std::pair(fullArrayValue_.at(1), false)); // push the second item if the first is #
        collapsedItemNums_.push_back(1);
    }

    auto lastPushedIndex = sharpItemCount_;

    for (int32_t groupIndex = 0; groupIndex < gmin; groupIndex++) { // push groups of minimum items count
        int32_t firstIndex = lastPushedIndex + 1;
        int32_t lastIndex = firstIndex + cmin - 1;
        arrayValue_.push_back(std::pair(fullArrayValue_.at(firstIndex), true));
        arrayValue_.push_back(std::pair(fullArrayValue_.at(lastIndex), false));
        collapsedItemNums_.push_back(cmin - 1);
        collapsedItemNums_.push_back(1);
        lastPushedIndex = lastIndex;
    }

    for (int32_t groupIndex = 0; groupIndex < gmax; groupIndex++) { // push groups of maximum items count
        int32_t firstIndex = lastPushedIndex + 1;
        int32_t lastIndex = firstIndex + cmax - 1;
        arrayValue_.push_back(std::pair(fullArrayValue_.at(firstIndex), true));
        arrayValue_.push_back(std::pair(fullArrayValue_.at(lastIndex), false));
        collapsedItemNums_.push_back(cmax - 1);
        collapsedItemNums_.push_back(1);
        lastPushedIndex = lastIndex;
    }
    autoCollapse_ = true;
}

void IndexerPattern::ApplyFivePlusOneMode(int32_t fullArraySize)
{
    // 5 + # mode
    // minimum items in one group (totally 4 groups) including
    // visible character in the group and excluding the first always visible item and # item if exists
    auto cmin = static_cast<int32_t>((fullArraySize - 1 - sharpItemCount_) / 4);
    auto gmax = (fullArraySize - 1 - sharpItemCount_) - cmin * 4; // number of groups with maximum items count
    auto cmax = cmin + 1; // maximum items in one group including visible character in the group
    auto gmin = 4 - gmax; // number of groups with minimum items count

    arrayValue_.clear();
    collapsedItemNums_.clear();
    arrayValue_.push_back(std::pair(fullArrayValue_.at(0), false)); // push the first item
    collapsedItemNums_.push_back(1);
    if (sharpItemCount_ > 0) {
        arrayValue_.push_back(std::pair(fullArrayValue_.at(1), false)); // push the second item if the first is #
        collapsedItemNums_.push_back(1);
    }

    auto lastPushedIndex = sharpItemCount_;

    for (int32_t groupIndex = 0; groupIndex < gmin; groupIndex++) { // push groups of minimum items count
        int32_t firstIndex = lastPushedIndex + 1;
        int32_t lastIndex = firstIndex + cmin - 1;
        arrayValue_.push_back(std::pair(fullArrayValue_.at(firstIndex), true));
        arrayValue_.push_back(std::pair(fullArrayValue_.at(lastIndex), false));
        collapsedItemNums_.push_back(cmin - 1);
        collapsedItemNums_.push_back(1);
        lastPushedIndex = lastIndex;
    }

    for (int32_t groupIndex = 0; groupIndex < gmax; groupIndex++) { // push groups of maximum items count
        int32_t firstIndex = lastPushedIndex + 1;
        int32_t lastIndex = firstIndex + cmax - 1;
        arrayValue_.push_back(std::pair(fullArrayValue_.at(firstIndex), true));
        arrayValue_.push_back(std::pair(fullArrayValue_.at(lastIndex), false));
        collapsedItemNums_.push_back(cmax - 1);
        collapsedItemNums_.push_back(1);
        lastPushedIndex = lastIndex;
    }
    autoCollapse_ = true;
}

int32_t IndexerPattern::GetAutoCollapseIndex(int32_t propSelect)
{
    int32_t fullArraySize = static_cast<int32_t>(fullArrayValue_.size());
    int32_t index = sharpItemCount_;
    int32_t mode = MODE_FIVE;
    propSelect -= sharpItemCount_;
    if (lastCollapsingMode_ == IndexerCollapsingMode::SEVEN) {
        mode = MODE_SEVEN;
    }
    // minimum items in one group including
    // visible character in the group and excluding the first always visible item and # item if exists
    auto cmin = static_cast<int32_t>((fullArraySize - 1 - sharpItemCount_) / mode);
    auto gmax = (fullArraySize - 1 - sharpItemCount_) - cmin * mode; // number of groups with maximum items count
    auto cmax = cmin + 1; // maximum items in one group including visible character in the group
    auto gmin = mode - gmax; // number of groups with minimum items count
    if (propSelect > gmin * cmin) {
        index += gmin * 2; // one group includes two index
        propSelect -= gmin * cmin;
        index += propSelect / cmax * 2 + (propSelect % cmax == 0 ? 0 : 1);
        collapsedIndex_ = propSelect % cmax == 0 ? 0 : (propSelect % cmax - 1);
    } else {
        index += propSelect / cmin * 2 + (propSelect % cmin == 0 ? 0 : 1);
        collapsedIndex_ = propSelect % cmin == 0 ? 0 : (propSelect % cmin - 1);
    }
    return  index;
}

int32_t IndexerPattern::GetActualIndex(int32_t index)
{
    auto actualIndex = autoCollapse_ && index > 0 && index < itemCount_ ?
                        static_cast<int32_t>(std::find(fullArrayValue_.begin(), fullArrayValue_.end(),
                        arrayValue_.at(index).first) - fullArrayValue_.begin()) : index;
    int32_t fullArraySize = static_cast<int32_t>(fullArrayValue_.size());
    return std::clamp(actualIndex + collapsedIndex_, 0, fullArraySize > 0 ? fullArraySize - 1 : 0);
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
    gestureHub->AddPanEvent(panEvent_, panDirection, 1, DEFAULT_PAN_DISTANCE);
}

void IndexerPattern::OnHover(bool isHover)
{
    if (itemCount_ <= 0) {
        return;
    }
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
    ApplyIndexChanged(true, false);
}

void IndexerPattern::OnChildHover(int32_t index, bool isHover)
{
    childHoverIndex_ = isHover ? index : -1;
    ApplyIndexChanged(true, childHoverIndex_ >= 0 && childHoverIndex_ < itemCount_);
}

void IndexerPattern::OnPopupHover(bool isHover)
{
    isPopupHover_ = isHover;
    if (isHover) {
        delayTask_.Cancel();
        StartBubbleAppearAnimation();
    } else {
        StartDelayTask(INDEXER_BUBBLE_ENTER_DURATION + INDEXER_BUBBLE_WAIT_DURATION);
    }
}

void IndexerPattern::InitInputEvent()
{
    if (isInputEventRegisted_) {
        return;
    }
    isInputEventRegisted_ = true;
    InitCurrentInputEvent();
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

void IndexerPattern::InitChildInputEvent(RefPtr<FrameNode>& itemNode, int32_t childIndex)
{
    CHECK_NULL_VOID(itemNode);
    auto childHoverCallback = [weak = WeakClaim(this), index = childIndex](bool isHovered) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnChildHover(index, isHovered);
    };
    auto childOnHoverEvent = MakeRefPtr<InputEvent>(childHoverCallback);
    auto childInputEventHub = itemNode->GetOrCreateInputEventHub();
    childInputEventHub->AddOnHoverEvent(childOnHoverEvent);
}

void IndexerPattern::InitPopupInputEvent()
{
    CHECK_NULL_VOID(popupNode_);
    auto popupHoverCallback = [weak = WeakClaim(this)](bool isHovered) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnPopupHover(isHovered);
    };
    auto popupOnHoverEvent = MakeRefPtr<InputEvent>(popupHoverCallback);
    auto popupInputEventHub = popupNode_->GetOrCreateInputEventHub();
    popupInputEventHub->AddOnHoverEvent(popupOnHoverEvent);
}

void IndexerPattern::InitPopupPanEvent()
{
    CHECK_NULL_VOID(popupNode_);
    auto gestureHub = popupNode_->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    PanDirection panDirection;
    panDirection.type = PanDirection::ALL;
    auto panEvent = MakeRefPtr<PanEvent>(nullptr, nullptr, nullptr, nullptr);
    gestureHub->AddPanEvent(panEvent, panDirection, 1, DEFAULT_PAN_DISTANCE);
}

void IndexerPattern::OnTouchDown(const TouchEventInfo& info)
{
    TAG_LOGI(AceLogTag::ACE_ALPHABET_INDEXER, "touch down at alphabetIndexer");
    if (itemCount_ <= 0 || info.GetTouches().empty()) {
        return;
    }
    MoveIndexByOffset(info.GetTouches().front().GetLocalLocation(), true);
}

void IndexerPattern::OnTouchUp(const TouchEventInfo& info)
{
    TAG_LOGI(AceLogTag::ACE_ALPHABET_INDEXER, "leave up from alphabetIndexer");
    if (itemCount_ <= 0) {
        return;
    }
    childPressIndex_ = -1;
    if (isHover_) {
        IndexerPressOutAnimation();
    }
    ResetStatus();
    ApplyIndexChanged(true, false, true);
    ItemSelectedChangedAnimation();
    StartDelayTask();
}

void IndexerPattern::MoveIndexByOffset(const Offset& offset, bool isTouch)
{
    if (itemHeight_ <= 0 || itemCount_ <= 0) {
        return;
    }
    auto nextSelectIndex = GetSelectChildIndex(offset, isTouch);
    if ((nextSelectIndex == childPressIndex_&& collapsedIndex_ == lastCollapsedIndex_) || nextSelectIndex == -1) {
        return;
    }
    childPressIndex_ = nextSelectIndex;
    selected_ = nextSelectIndex;
    FireOnSelect(selected_, true);
    selectedChangedForHaptic_ = lastSelected_ != selected_ || collapsedIndex_ != lastCollapsedIndex_;
    lastSelected_ = nextSelectIndex;
    lastCollapsedIndex_ = collapsedIndex_;
    if (isHover_ && childPressIndex_ >= 0) {
        IndexerPressInAnimation();
    }
    childFocusIndex_ = -1;
    childHoverIndex_ = -1;
    ApplyIndexChanged(true, true);
}

int32_t IndexerPattern::GetSelectChildIndex(const Offset& offset, bool isTouch)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, -1);
    auto layoutProperty = host->GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, -1);
    int32_t index = 0;
    int32_t arraySize = static_cast<int32_t>(collapsedItemNums_.size());
    for (auto child : host->GetChildren()) {
        auto childNode = DynamicCast<FrameNode>(child);
        CHECK_NULL_RETURN(childNode, -1);
        auto geometryNode = childNode->GetGeometryNode();
        CHECK_NULL_RETURN(geometryNode, -1);
        auto childOffset = geometryNode->GetFrameOffset();
        if (index == 0 && LessNotEqual(offset.GetY(), childOffset.GetY())) {
            return -1;
        }
        if (GreatOrEqual(offset.GetY(), childOffset.GetY()) &&
            LessNotEqual(offset.GetY(), childOffset.GetY() + itemHeight_)) {
                if (isTouch) {
                    collapsedIndex_ = 0;
                } else if (arraySize > 0) {
                    float yOffset = offset.GetY() - childOffset.GetY();
                    int32_t itemIndex = std::clamp(index, 0, arraySize - 1);
                    int32_t itemNum = collapsedItemNums_[itemIndex] < 1 ? 1 : collapsedItemNums_[itemIndex];
                    float itemHeight = itemHeight_ / itemNum;
                    collapsedIndex_ = NearZero(itemHeight) ? 0 : floor(yOffset / itemHeight);
                }
            break;
        }
        index++;
    }
    return index < itemCount_ ? index : -1;
}

bool IndexerPattern::KeyIndexByStep(int32_t step)
{
    auto nextSelected = GetSkipChildIndex(step);
    if (nextSelected == -1) {
        OnKeyEventDisappear();
        return false;
    } else if (childFocusIndex_ == nextSelected) {
        return false;
    }
    childFocusIndex_ = nextSelected;
    auto refreshBubble = nextSelected >= 0 && nextSelected < itemCount_;
    if (refreshBubble) {
        selected_ = nextSelected;
        selectedChangedForHaptic_ = lastSelected_ != selected_;
        lastSelected_ = nextSelected;
    }
    childPressIndex_ = -1;
    childHoverIndex_ = -1;
    collapsedIndex_ = 0;
    ApplyIndexChanged(true, refreshBubble);
    OnSelect();
    return nextSelected >= 0;
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
    auto nextSelected = GetSkipChildIndex(step);
    if (selected_ == nextSelected || nextSelected == -1) {
        return false;
    }
    selected_ = nextSelected;
    collapsedIndex_ = 0;
    ResetStatus();
    ApplyIndexChanged(true, true);
    OnSelect();
    return nextSelected >= 0;
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
    collapsedIndex_ = 0;
    ApplyIndexChanged(true, true);
    OnSelect();
    return nextSelectIndex >= 0;
}

int32_t IndexerPattern::GetFocusChildIndex(const std::string& searchStr)
{
    int32_t nextSelectIndex = -1;
    for (auto i = selected_ + 1; i < itemCount_; ++i) {
        const auto& indexValue = arrayValue_.at(i).first;
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
        const auto& indexValue = arrayValue_.at(i).first;
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
    popupClickedIndex_ = -1;
}

void IndexerPattern::OnSelect()
{
    FireOnSelect(selected_, false);
    ItemSelectedChangedAnimation();
}

void IndexerPattern::ItemSelectedChangedAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
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
    selectedChangedForHaptic_ = lastSelected_ != selected_;
    lastSelected_ = selected_;
}

void IndexerPattern::ApplyIndexChanged(
    bool isTextNodeInTree, bool selectChanged, bool fromTouchUp, bool indexerSizeChanged)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetAdaptiveWidthValue(false)) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    }
    auto paintProperty = host->GetPaintProperty<IndexerPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto indexerRenderContext = host->GetRenderContext();
        CHECK_NULL_VOID(indexerRenderContext);
        if (paintProperty->GetIndexerBorderRadius().has_value()) {
            auto indexerRadius = paintProperty->GetIndexerBorderRadiusValue();
            indexerRenderContext->UpdateBorderRadius({ indexerRadius, indexerRadius, indexerRadius, indexerRadius });
        } else {
            auto indexerRadius = Dimension(INDEXER_DEFAULT_RADIUS, DimensionUnit::VP);
            indexerRenderContext->UpdateBorderRadius({ indexerRadius, indexerRadius, indexerRadius, indexerRadius });
        }
    }
    UpdateChildTextStyle(layoutProperty, paintProperty, isTextNodeInTree, fromTouchUp);

    if (fromTouchUp) {
        AccessibilityEventType type = AccessibilityEventType::SELECTED;
        host->OnAccessibilityEvent(type);
    }
    if (selectChanged) {
        host->OnAccessibilityEvent(AccessibilityEventType::TEXT_CHANGE);
        if (enableHapticFeedback_ && selectedChangedForHaptic_ && !fromTouchUp) {
            VibratorUtils::StartVibraFeedback();
        }
        ShowBubble();
    }
}

void IndexerPattern::UpdateChildTextStyle(RefPtr<IndexerLayoutProperty>& layoutProperty,
    RefPtr<IndexerPaintProperty>& paintProperty, bool isTextNodeInTree, bool fromTouchUp)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(layoutProperty);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto indexerTheme = pipelineContext->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    TextStyle unselectedFontStyle, selectedFontStyle;
    UpdateFontStyle(layoutProperty, indexerTheme, unselectedFontStyle, selectedFontStyle);
    Color unselectedTextColor = layoutProperty->GetColor().value_or(indexerTheme->GetDefaultTextColor());
    auto total = host->GetTotalChildCount();
    if (layoutProperty->GetIsPopupValue(false)) total -= 1;
    for (int32_t index = 0; index < total; index++) {
        auto childNode = host->GetChildByIndex(index)->GetHostNode();
        CHECK_NULL_VOID(childNode);
        UpdateChildBoundary(childNode);
        auto textRenderContext = childNode->GetRenderContext();
        CHECK_NULL_VOID(textRenderContext);
        textRenderContext->SetClipToBounds(true);
        Color textColor = unselectedTextColor;
        TextStyle fontStyle = unselectedFontStyle;
        Dimension borderWidth;
        if (index == childHoverIndex_ || index == childPressIndex_) {
            UpdateHoverAndPressStyle(paintProperty, textRenderContext, indexerTheme, index);
        } else if (index == childFocusIndex_ || index == selected_) {
            if (index == childFocusIndex_) borderWidth = indexerTheme->GetFocusBgOutlineSize();
            textColor = layoutProperty->GetSelectedColor().value_or(indexerTheme->GetSelectedTextColor());
            fontStyle = selectedFontStyle;
            UpdateFocusAndSelectedStyle(paintProperty, textRenderContext, indexerTheme, index, fromTouchUp);
        } else {
            UpdateNormalStyle(textRenderContext, index, fromTouchUp);
        }

        UpdateTextLayoutProperty(childNode, index, borderWidth, fontStyle, textColor);
        childNode->MarkModifyDone();
        if (isTextNodeInTree) childNode->MarkDirtyNode();
        auto textAccessibilityProperty = childNode->GetAccessibilityProperty<TextAccessibilityProperty>();
        if (textAccessibilityProperty) textAccessibilityProperty->SetSelected(index == selected_);
    }
}

void IndexerPattern::UpdateFontStyle(RefPtr<IndexerLayoutProperty>& layoutProperty, RefPtr<IndexerTheme>& indexerTheme,
    TextStyle& unselectedFontStyle, TextStyle& selectedFontStyle)
{
    CHECK_NULL_VOID(layoutProperty);
    CHECK_NULL_VOID(indexerTheme);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
#ifndef ACE_UNITTEST
    auto fontManager = pipelineContext->GetFontManager();
    CHECK_NULL_VOID(fontManager);
    const std::vector<std::string> customFonts = Framework::ConvertStrToFontFamilies(fontManager->GetAppCustomFont());
#else
    const std::vector<std::string> customFonts;
#endif
    unselectedFontStyle = layoutProperty->GetFont().value_or(indexerTheme->GetDefaultTextStyle());
    if ((!layoutProperty->GetFont().has_value() || layoutProperty->GetFont().value().GetFontFamilies().empty()) &&
        !customFonts.empty()) {
        unselectedFontStyle.SetFontFamilies(customFonts);
    }
    selectedFontStyle = layoutProperty->GetSelectedFont().value_or(indexerTheme->GetSelectTextStyle());
    if ((!layoutProperty->GetSelectedFont().has_value() ||
            layoutProperty->GetSelectedFont().value().GetFontFamilies().empty()) &&
        !customFonts.empty()) {
        selectedFontStyle.SetFontFamilies(customFonts);
    }
}

void IndexerPattern::UpdateHoverAndPressStyle(RefPtr<IndexerPaintProperty>& paintProperty,
    RefPtr<RenderContext>& textRenderContext, RefPtr<IndexerTheme>& indexerTheme, int32_t index) const
{
    CHECK_NULL_VOID(textRenderContext);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        CHECK_NULL_VOID(paintProperty);
        auto radiusSize = paintProperty->GetItemBorderRadius().has_value()
                              ? paintProperty->GetItemBorderRadiusValue()
                              : Dimension(INDEXER_ITEM_DEFAULT_RADIUS, DimensionUnit::VP);
        textRenderContext->UpdateBorderRadius({ radiusSize, radiusSize, radiusSize, radiusSize });
        textRenderContext->UpdateBackgroundColor(
            index == childHoverIndex_ ? indexerTheme->GetHoverBgAreaColor() : indexerTheme->GetPressedBgAreaColor());
    } else {
        CHECK_NULL_VOID(indexerTheme);
        auto radiusSize = indexerTheme->GetHoverRadiusSize();
        textRenderContext->UpdateBorderRadius({ radiusSize, radiusSize, radiusSize, radiusSize });
        textRenderContext->UpdateBackgroundColor(indexerTheme->GetHoverBgAreaColor());
    }
}

void IndexerPattern::UpdateFocusAndSelectedStyle(RefPtr<IndexerPaintProperty>& paintProperty,
    RefPtr<RenderContext>& textRenderContext, RefPtr<IndexerTheme>& indexerTheme, int32_t index, bool fromTouchUp) const
{
    CHECK_NULL_VOID(textRenderContext);
    CHECK_NULL_VOID(paintProperty);
    CHECK_NULL_VOID(indexerTheme);
    if (index == childFocusIndex_) {
        auto borderColor = indexerTheme->GetFocusBgOutlineColor();
        textRenderContext->UpdateBorderColor(
            { borderColor, borderColor, borderColor, borderColor, std::nullopt, std::nullopt });
        textRenderContext->UpdateBackgroundColor(
            paintProperty->GetSelectedBackgroundColor().value_or(indexerTheme->GetSelectedBackgroundColor()));
    } else if (!fromTouchUp || animateSelected_ == lastSelected_) {
        textRenderContext->UpdateBackgroundColor(paintProperty->GetSelectedBackgroundColor().value_or(
            indexerTheme->GetSelectedBackgroundColor()));
    }
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto radius = paintProperty->GetItemBorderRadius().has_value()
                            ? paintProperty->GetItemBorderRadiusValue()
                            : Dimension(INDEXER_ITEM_DEFAULT_RADIUS, DimensionUnit::VP);
        textRenderContext->UpdateBorderRadius({ radius, radius, radius, radius });
    } else {
        auto radius = indexerTheme->GetHoverRadiusSize();
        textRenderContext->UpdateBorderRadius({ radius, radius, radius, radius });
    }
}

void IndexerPattern::UpdateNormalStyle(RefPtr<RenderContext>& textRenderContext, int32_t index, bool fromTouchUp) const
{
    CHECK_NULL_VOID(textRenderContext);
    if (!fromTouchUp || animateSelected_ == lastSelected_ || index != lastSelected_) {
        textRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    }
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto radiusDefaultSize = Dimension(INDEXER_ITEM_DEFAULT_RADIUS, DimensionUnit::VP);
        textRenderContext->UpdateBorderRadius({ radiusDefaultSize, radiusDefaultSize,
            radiusDefaultSize, radiusDefaultSize });
    } else {
        Dimension radiusZeroSize;
        textRenderContext->UpdateBorderRadius(
            { radiusZeroSize, radiusZeroSize, radiusZeroSize, radiusZeroSize });
    }
}

void IndexerPattern::UpdateTextLayoutProperty(
    RefPtr<FrameNode>& textNode, int32_t index, Dimension& borderWidth, TextStyle& fontStyle, Color& textColor) const
{
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto nodeStr = autoCollapse_ && arrayValue_[index].second ?
            StringUtils::Str16ToStr8(INDEXER_STR_DOT) : arrayValue_[index].first;
    textLayoutProperty->UpdateContent(nodeStr);
    textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    textLayoutProperty->UpdateAlignment(Alignment::CENTER);
    textLayoutProperty->UpdateMinFontScale(1.0f);
    textLayoutProperty->UpdateMaxFontScale(1.0f);
    textLayoutProperty->UpdateMaxLines(1);
    textLayoutProperty->UpdateBorderWidth(
        { borderWidth, borderWidth, borderWidth, borderWidth, std::nullopt, std::nullopt });
    textLayoutProperty->UpdateFontSize(fontStyle.GetFontSize());
    textLayoutProperty->UpdateFontFamily(fontStyle.GetFontFamilies());
    textLayoutProperty->UpdateFontWeight(fontStyle.GetFontWeight());
    textLayoutProperty->UpdateItalicFontStyle(fontStyle.GetFontStyle());
    textLayoutProperty->UpdateTextColor(textColor);
}

void IndexerPattern::ShowBubble()
{
    if (!NeedShowBubble() || itemCount_ < 1) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!popupNode_) {
        popupNode_ = CreatePopupNode();
        AddPopupTouchListener(popupNode_);
        InitPopupInputEvent();
        InitPopupPanEvent();
        UpdatePopupOpacity(0.0f);
    }
    if (!layoutProperty->GetIsPopupValue(false)) {
        popupNode_->MountToParent(host);
        layoutProperty->UpdateIsPopup(true);
    }
    std::vector<std::string> currentListData = std::vector<std::string>();
    UpdateBubbleList(currentListData);
    UpdateBubbleView(currentListData);
    UpdateBubbleSize(currentListData);
    delayTask_.Cancel();
    StartBubbleAppearAnimation();
    if (!isTouch_) {
        StartDelayTask(INDEXER_BUBBLE_ENTER_DURATION + INDEXER_BUBBLE_WAIT_DURATION);
    }
}

RefPtr<FrameNode> IndexerPattern::CreatePopupNode()
{
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    CHECK_NULL_RETURN(columnNode, nullptr);

    if (!autoCollapse_) {
        auto letterNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_RETURN(letterNode, nullptr);
        auto letterStackNode = FrameNode::CreateFrameNode(
            V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StackPattern>());
        CHECK_NULL_RETURN(letterStackNode, nullptr);
        letterStackNode->AddChild(letterNode);
        columnNode->AddChild(letterStackNode);
    }
    auto listNode = FrameNode::CreateFrameNode(
        V2::LIST_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ListPattern>());
    CHECK_NULL_RETURN(listNode, nullptr);
    auto listStackNode = FrameNode::CreateFrameNode(
        V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StackPattern>());
    CHECK_NULL_RETURN(listStackNode, nullptr);
    listStackNode->AddChild(listNode);
    columnNode->AddChild(listStackNode);
    return columnNode;
}

void IndexerPattern::UpdateBubbleList(std::vector<std::string>& currentListData)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto indexerEventHub = host->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(indexerEventHub);
    auto popListData = indexerEventHub->GetOnRequestPopupData();
    CHECK_NULL_VOID(popListData);
    auto actualIndex = GetActualIndex(selected_);
    currentListData = popListData(actualIndex);
}

void IndexerPattern::UpdateBubbleView(std::vector<std::string>& currentListData)
{
    CHECK_NULL_VOID(popupNode_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto columnLayoutProperty = popupNode_->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(columnLayoutProperty);
    UpdateBubbleListView(currentListData);
    UpdateBubbleLetterView(!currentListData.empty(), currentListData);
    auto columnRenderContext = popupNode_->GetRenderContext();
    CHECK_NULL_VOID(columnRenderContext);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto columnPadding = Dimension(BUBBLE_DIVIDER_SIZE, DimensionUnit::VP).ConvertToPx();
        columnLayoutProperty->UpdatePadding(
            { CalcLength(0), CalcLength(0), CalcLength(columnPadding), CalcLength(0), std::nullopt, std::nullopt });
        auto paintProperty = host->GetPaintProperty<IndexerPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        if (paintProperty->GetPopupBorderRadius().has_value()) {
            auto radius = paintProperty->GetPopupBorderRadiusValue();
            columnRenderContext->UpdateBorderRadius({ radius, radius, radius, radius });
        } else {
            auto radius = Dimension(BUBBLE_RADIUS, DimensionUnit::VP);
            columnRenderContext->UpdateBorderRadius({ radius, radius, radius, radius });
        }
        Shadow shadow = GetPopupShadow();
        columnRenderContext->UpdateBackShadow(shadow);
    } else {
        auto radius = Dimension(BUBBLE_BOX_RADIUS, DimensionUnit::VP);
        columnRenderContext->UpdateBorderRadius({ radius, radius, radius, radius });
        columnRenderContext->UpdateBackShadow(Shadow::CreateShadow(ShadowStyle::OuterDefaultMD));
    }
    UpdateBubbleBackgroundView();
    columnRenderContext->SetClipToBounds(true);
    popupNode_->MarkModifyDone();
    popupNode_->MarkDirtyNode();
}

Shadow IndexerPattern::GetPopupShadow()
{
    Shadow shadow;
    auto pipelineContext = GetContext();
    CHECK_NULL_RETURN(pipelineContext, shadow);
    auto colorMode = pipelineContext->GetColorMode();
    auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
    CHECK_NULL_RETURN(shadowTheme, shadow);
    shadow = shadowTheme->GetShadow(ShadowStyle::OuterDefaultLG, colorMode);
    return shadow;
}

void IndexerPattern::UpdateBubbleBackgroundView()
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        CHECK_NULL_VOID(popupNode_);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto paintProperty = host->GetPaintProperty<IndexerPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        auto pipelineContext = host->GetContext();
        CHECK_NULL_VOID(pipelineContext);
        auto indexerTheme = pipelineContext->GetTheme<IndexerTheme>();
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
}

void IndexerPattern::UpdateBubbleSize(std::vector<std::string>& currentListData)
{
    CHECK_NULL_VOID(popupNode_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto columnLayoutProperty = popupNode_->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(columnLayoutProperty);
    auto popupSize = autoCollapse_ ? currentListData.size() + 1 : currentListData.size();
    auto bubbleSize = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    auto columnCalcOffset = autoCollapse_ ? 0 : 1;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto maxItemsSize = autoCollapse_ ? INDEXER_BUBBLE_MAXSIZE_COLLAPSED_API_TWELVE : INDEXER_BUBBLE_MAXSIZE;
        auto bubbleHeight = Dimension(BUBBLE_ITEM_SIZE, DimensionUnit::VP).ConvertToPx();
        auto bubbleDivider = Dimension(BUBBLE_DIVIDER_SIZE, DimensionUnit::VP).ConvertToPx();
        auto columnCalcSize = CalcSize();
        if (popupSize <= maxItemsSize) {
            columnCalcSize = CalcSize(CalcLength(bubbleSize),
                CalcLength((bubbleHeight + bubbleDivider) * (static_cast<int32_t>(popupSize) + columnCalcOffset) +
                           bubbleDivider));
        } else {
            columnCalcSize = CalcSize(CalcLength(bubbleSize),
                CalcLength(Dimension(
                    autoCollapse_ ? BUBBLE_COLLAPSE_COLUMN_MAX_SIZE : BUBBLE_COLUMN_MAX_SIZE, DimensionUnit::VP)
                                .ConvertToPx()));
        }
        columnLayoutProperty->UpdateUserDefinedIdealSize(columnCalcSize);
    } else {
        auto maxItemsSize = autoCollapse_ ? INDEXER_BUBBLE_MAXSIZE_COLLAPSED : INDEXER_BUBBLE_MAXSIZE;
        auto listActualSize = popupSize < maxItemsSize ? popupSize : maxItemsSize;
        auto columnCalcSize = CalcSize(
            CalcLength(bubbleSize),
            CalcLength(bubbleSize * (static_cast<int32_t>(listActualSize) + columnCalcOffset)));
        columnLayoutProperty->UpdateUserDefinedIdealSize(columnCalcSize);
    }
    popupNode_->MarkDirtyNode();
}

void IndexerPattern::UpdateBubbleLetterView(bool showDivider, std::vector<std::string>& currentListData)
{
    CHECK_NULL_VOID(popupNode_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto indexerTheme = pipelineContext->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    auto paintProperty = host->GetPaintProperty<IndexerPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto layoutProperty = host->GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto letterNode = GetLetterNode();
    CHECK_NULL_VOID(letterNode);
    UpdateBubbleLetterStackAndLetterTextView();
    auto letterLayoutProperty = letterNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(letterLayoutProperty);
    auto letterNodeRenderContext = letterNode->GetRenderContext();
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto bubbleSize = Dimension(BUBBLE_ITEM_SIZE, DimensionUnit::VP).ConvertToPx();
        letterLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(bubbleSize), CalcLength(bubbleSize)));
        auto letterContext = letterNode->GetRenderContext();
        CHECK_NULL_VOID(letterContext);
        auto radius = paintProperty->GetPopupItemBorderRadius().has_value()
                            ? paintProperty->GetPopupItemBorderRadiusValue()
                            : Dimension(BUBBLE_ITEM_RADIUS, DimensionUnit::VP);
        letterContext->UpdateBorderRadius({ radius, radius, radius, radius });
        letterNodeRenderContext->UpdateBackgroundColor(paintProperty->GetPopupTitleBackground().value_or(
            currentListData.size() > 0 ? indexerTheme->GetPopupTitleBackground() : Color(POPUP_TITLE_BG_COLOR_SINGLE)));
    } else {
        auto bubbleSize = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
        letterLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(bubbleSize), CalcLength(bubbleSize)));
        letterNodeRenderContext->UpdateBackgroundColor(
            paintProperty->GetPopupBackground().value_or(indexerTheme->GetPopupBackgroundColor()));
        auto zeroWidth = Dimension();
        if (showDivider) {
            letterLayoutProperty->UpdateBorderWidth(
                { zeroWidth, zeroWidth, zeroWidth, Dimension(INDEXER_LIST_DIVIDER), std::nullopt, std::nullopt });
            auto borderColor = BorderColorProperty();
            borderColor.bottomColor = indexerTheme->GetPopupSeparateColor();
            letterNodeRenderContext->UpdateBorderColor(borderColor);
        } else {
            letterLayoutProperty->UpdateBorderWidth(
                { zeroWidth, zeroWidth, zeroWidth, zeroWidth, std::nullopt, std::nullopt });
        }
    }
    letterNodeRenderContext->SetClipToBounds(true);
    letterNode->MarkModifyDone();
    letterNode->MarkDirtyNode();
}

void IndexerPattern::UpdateBubbleLetterStackAndLetterTextView()
{
    CHECK_NULL_VOID(popupNode_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto indexerTheme = pipelineContext->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    auto fontManager = pipelineContext->GetFontManager();
    CHECK_NULL_VOID(fontManager);
    auto layoutProperty = host->GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto letterNode = GetLetterNode();
    CHECK_NULL_VOID(letterNode);
    auto letterLayoutProperty = letterNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(letterLayoutProperty);
    letterLayoutProperty->UpdateContent(fullArrayValue_[GetActualIndex(selected_)]);
    auto popupTextFont = layoutProperty->GetPopupFont().value_or(indexerTheme->GetPopupTextStyle());
    if ((!layoutProperty->GetPopupFont().has_value() ||
            layoutProperty->GetPopupFont().value().GetFontFamilies().empty()) &&
        fontManager->IsUseAppCustomFont()) {
        popupTextFont.SetFontFamilies(Framework::ConvertStrToFontFamilies(fontManager->GetAppCustomFont()));
    }
    letterLayoutProperty->UpdateMaxLines(1);
    letterLayoutProperty->UpdateFontSize(popupTextFont.GetFontSize());
    letterLayoutProperty->UpdateFontWeight(popupTextFont.GetFontWeight());
    letterLayoutProperty->UpdateFontFamily(popupTextFont.GetFontFamilies());
    letterLayoutProperty->UpdateItalicFontStyle(popupTextFont.GetFontStyle());
    letterLayoutProperty->UpdateTextColor(layoutProperty->GetPopupColor().value_or(indexerTheme->GetPopupTextColor()));
    letterLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    letterLayoutProperty->UpdateAlignment(Alignment::CENTER);
    letterLayoutProperty->UpdateMinFontScale(1.0f);
    letterLayoutProperty->UpdateMaxFontScale(1.0f);
    auto textPadding = Dimension(IndexerTheme::TEXT_PADDING_LEFT, DimensionUnit::VP).ConvertToPx();
    letterLayoutProperty->UpdatePadding(
        { CalcLength(textPadding), CalcLength(textPadding), CalcLength(0), CalcLength(0), std::nullopt, std::nullopt });

    if (!autoCollapse_ && Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto letterStackNode = DynamicCast<FrameNode>(popupNode_->GetFirstChild());
        CHECK_NULL_VOID(letterStackNode);
        auto letterStackLayoutProperty = letterStackNode->GetLayoutProperty<StackLayoutProperty>();
        CHECK_NULL_VOID(letterStackLayoutProperty);
        auto letterStackWidth = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
        auto letterStackHeight = Dimension(BUBBLE_ITEM_SIZE + BUBBLE_DIVIDER_SIZE, DimensionUnit::VP).ConvertToPx();
        letterStackLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(letterStackWidth), CalcLength(letterStackHeight)));
        auto letterStackPadding = Dimension(BUBBLE_DIVIDER_SIZE, DimensionUnit::VP).ConvertToPx();
        letterStackLayoutProperty->UpdatePadding({ CalcLength(letterStackPadding), CalcLength(letterStackPadding),
            CalcLength(0), CalcLength(letterStackPadding), std::nullopt, std::nullopt });
    }
}

RefPtr<FrameNode> IndexerPattern::GetLetterNode()
{
    CHECK_NULL_RETURN(popupNode_, nullptr);
    return autoCollapse_ ? GetAutoCollapseLetterNode()
                            : DynamicCast<FrameNode>(popupNode_->GetFirstChild()->GetFirstChild());
}

RefPtr<FrameNode> IndexerPattern::GetAutoCollapseLetterNode()
{
    CHECK_NULL_RETURN(popupNode_, nullptr);
    return DynamicCast<FrameNode>(popupNode_->GetLastChild()->GetFirstChild()->GetFirstChild()->GetFirstChild());
}

void IndexerPattern::UpdateBubbleListView(std::vector<std::string>& currentListData)
{
    CHECK_NULL_VOID(popupNode_);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        CreateBubbleListView(currentListData);
    }
    auto listNode = DynamicCast<FrameNode>(popupNode_->GetLastChild()->GetFirstChild());
    CHECK_NULL_VOID(listNode);
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto indexerTheme = pipelineContext->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    auto listPattern = DynamicCast<ListPattern>(listNode->GetPattern());
    listPattern->SetNeedLinked(false);
    auto listLayoutProperty = listNode->GetLayoutProperty<ListLayoutProperty>();
    CHECK_NULL_VOID(listLayoutProperty);
    UpdateBubbleListSize(currentListData);
    auto popupSize = autoCollapse_ ? currentListData.size() + 1 : currentListData.size();
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto maxItemsSize = autoCollapse_ ? INDEXER_BUBBLE_MAXSIZE_COLLAPSED_API_TWELVE : INDEXER_BUBBLE_MAXSIZE;
        auto listPadding = Dimension(BUBBLE_DIVIDER_SIZE, DimensionUnit::VP).ConvertToPx();
        listLayoutProperty->UpdatePadding({ CalcLength(listPadding), CalcLength(listPadding), CalcLength(0),
            CalcLength(0), std::nullopt, std::nullopt });
        UpdatePopupListGradientView(popupSize, maxItemsSize);
    }
    if (!currentListData.empty() || autoCollapse_) {
        UpdateBubbleListItem(currentListData, listNode, indexerTheme);
    } else {
        listNode->Clean();
    }
    auto divider = V2::ItemDivider();
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        divider.strokeWidth = Dimension(BUBBLE_DIVIDER_SIZE, DimensionUnit::VP);
    } else {
        divider.strokeWidth = Dimension(INDEXER_LIST_DIVIDER, DimensionUnit::PX);
        divider.color = indexerTheme->GetPopupSeparateColor();
    }
    listLayoutProperty->UpdateDivider(divider);
    listLayoutProperty->UpdateListDirection(Axis::VERTICAL);
    auto listPaintProperty = listNode->GetPaintProperty<ScrollablePaintProperty>();
    CHECK_NULL_VOID(listPaintProperty);
    listPaintProperty->UpdateScrollBarMode(DisplayMode::OFF);
    auto listRenderContext = listNode->GetRenderContext();
    CHECK_NULL_VOID(listRenderContext);
    listRenderContext->SetClipToBounds(true);
    listNode->MarkModifyDone();
    listNode->MarkDirtyNode();
}

void IndexerPattern::UpdateBubbleListSize(std::vector<std::string>& currentListData)
{
    CHECK_NULL_VOID(popupNode_);
    currentPopupIndex_ = childPressIndex_ >= 0 ? childPressIndex_ : selected_;
    auto popupSize = autoCollapse_ ? currentListData.size() + 1 : currentListData.size();
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto maxItemsSize = autoCollapse_ ? INDEXER_BUBBLE_MAXSIZE_COLLAPSED_API_TWELVE : INDEXER_BUBBLE_MAXSIZE;
        auto listActualSize = popupSize < maxItemsSize ? popupSize : maxItemsSize;
        lastPopupIndex_ = currentPopupIndex_;
        lastPopupSize_ = listActualSize;
        auto stackNode = DynamicCast<FrameNode>(popupNode_->GetLastChild());
        CHECK_NULL_VOID(stackNode);
        auto stackLayoutProperty = stackNode->GetLayoutProperty<StackLayoutProperty>();
        CHECK_NULL_VOID(stackLayoutProperty);
        auto listCalcSize = CalcBubbleListSize(popupSize, maxItemsSize);
        stackLayoutProperty->UpdateUserDefinedIdealSize(listCalcSize);
        auto listNode =  DynamicCast<FrameNode>(stackNode->GetFirstChild());
        CHECK_NULL_VOID(listNode);
        auto listLayoutProperty = listNode->GetLayoutProperty<ListLayoutProperty>();
        CHECK_NULL_VOID(listLayoutProperty);
        listLayoutProperty->UpdateUserDefinedIdealSize(listCalcSize);
    } else {
        auto maxItemsSize = autoCollapse_ ? INDEXER_BUBBLE_MAXSIZE_COLLAPSED : INDEXER_BUBBLE_MAXSIZE;
        auto listActualSize = popupSize < maxItemsSize ? popupSize : maxItemsSize;
        if (listActualSize != lastPopupSize_ || lastPopupIndex_ != currentPopupIndex_) {
            lastPopupIndex_ = currentPopupIndex_;
            CreateBubbleListView(currentListData);
            lastPopupSize_ = listActualSize;
        }
        auto bubbleSize = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
        auto listNode = DynamicCast<FrameNode>(popupNode_->GetLastChild()->GetFirstChild());
        CHECK_NULL_VOID(listNode);
        auto listLayoutProperty = listNode->GetLayoutProperty<ListLayoutProperty>();
        CHECK_NULL_VOID(listLayoutProperty);
        listLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(bubbleSize), CalcLength(bubbleSize * listActualSize)));
    }
}

void IndexerPattern::CreateBubbleListView(std::vector<std::string>& currentListData)
{
    CHECK_NULL_VOID(popupNode_);
    auto listNode = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)
                        ? FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                            AceType::MakeRefPtr<ListPattern>())
                        : DynamicCast<FrameNode>(popupNode_->GetLastChild()->GetFirstChild());
    CHECK_NULL_VOID(listNode);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto stackNode = DynamicCast<FrameNode>(popupNode_->GetLastChild());
        CHECK_NULL_VOID(stackNode);
        stackNode->Clean();
    } else {
        listNode->Clean();
    }

    if (autoCollapse_) {
        auto letterNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        CHECK_NULL_VOID(letterNode);
        auto listItemNode =
            FrameNode::CreateFrameNode(V2::LIST_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE));
        listItemNode->AddChild(letterNode);
        listNode->AddChild(listItemNode);
    }

    for (uint32_t i = 0; i < currentListData.size(); i++) {
        auto listItemNode =
            FrameNode::CreateFrameNode(V2::LIST_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE));
        auto textNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        listItemNode->AddChild(textNode);
        AddListItemClickListener(listItemNode, i);
        listNode->AddChild(listItemNode);
    }
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto stackNode = DynamicCast<FrameNode>(popupNode_->GetLastChild());
        CHECK_NULL_VOID(stackNode);
        stackNode->AddChild(listNode);
    }
}

void IndexerPattern::UpdatePopupListGradientView(int32_t popupSize, int32_t maxItemsSize)
{
    CHECK_NULL_VOID(popupNode_);
    auto listNode = DynamicCast<FrameNode>(popupNode_->GetLastChild()->GetFirstChild());
    CHECK_NULL_VOID(listNode);
    if (popupSize > maxItemsSize) {
        DrawPopupListGradient(PopupListGradientStatus::BOTTOM);
        auto listEventHub = listNode->GetEventHub<ListEventHub>();
        CHECK_NULL_VOID(listEventHub);
        auto onScroll = [weak = WeakClaim(this)](Dimension offset, ScrollState state) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto popupNode = pattern->popupNode_;
            CHECK_NULL_VOID(popupNode);
            auto listNode = DynamicCast<FrameNode>(popupNode->GetLastChild()->GetFirstChild());
            CHECK_NULL_VOID(listNode);
            auto listPattern = listNode->GetPattern<ListPattern>();
            CHECK_NULL_VOID(listPattern);
            if (listPattern->IsAtTop()) {
                pattern->DrawPopupListGradient(PopupListGradientStatus::BOTTOM);
                return;
            } else if (listPattern->IsAtBottom()) {
                pattern->DrawPopupListGradient(PopupListGradientStatus::TOP);
                return;
            } else {
                pattern->DrawPopupListGradient(PopupListGradientStatus::BOTH);
                return;
            }
        };
        listEventHub->SetOnScroll(onScroll);
    } else {
        DrawPopupListGradient(PopupListGradientStatus::NONE);
    }
}

void IndexerPattern::DrawPopupListGradient(PopupListGradientStatus gradientStatus)
{
    CHECK_NULL_VOID(popupNode_);
    auto stackNode = DynamicCast<FrameNode>(popupNode_->GetLastChild());
    CHECK_NULL_VOID(stackNode);
    auto listNode = DynamicCast<FrameNode>(stackNode->GetFirstChild());
    auto listRenderContext = listNode->GetRenderContext();
    CHECK_NULL_VOID(listRenderContext);
    auto stackRenderContext = stackNode->GetRenderContext();
    CHECK_NULL_VOID(stackRenderContext);
    auto listStackHeight = autoCollapse_ ? BUBBLE_COLLAPSE_COLUMN_MAX_SIZE : BUBBLE_COLUMN_MAX_SIZE;
    auto gradientPercent = static_cast<float>(GRADIENT_COVER_HEIGHT / listStackHeight) ;
    NG::Gradient coverGradient;
    coverGradient.CreateGradientWithType(NG::GradientType::LINEAR);
    switch (gradientStatus) {
        case PopupListGradientStatus::TOP:
            coverGradient.AddColor(CreatePercentGradientColor(0, Color::TRANSPARENT));
            coverGradient.AddColor(CreatePercentGradientColor(gradientPercent, Color::WHITE));
            coverGradient.AddColor(CreatePercentGradientColor(1, Color::WHITE));
            break;
        case PopupListGradientStatus::BOTTOM:
            coverGradient.AddColor(CreatePercentGradientColor(0, Color::WHITE));
            coverGradient.AddColor(CreatePercentGradientColor(1 - gradientPercent, Color::WHITE));
            coverGradient.AddColor(CreatePercentGradientColor(1, Color::TRANSPARENT));
            break;
        case PopupListGradientStatus::BOTH:
            coverGradient.AddColor(CreatePercentGradientColor(0, Color::TRANSPARENT));
            coverGradient.AddColor(CreatePercentGradientColor(gradientPercent, Color::WHITE));
            coverGradient.AddColor(CreatePercentGradientColor(1 - gradientPercent, Color::WHITE));
            coverGradient.AddColor(CreatePercentGradientColor(1, Color::TRANSPARENT));
            break;
        case PopupListGradientStatus::NONE:
        default:
            coverGradient.AddColor(CreatePercentGradientColor(0, Color::WHITE));
            coverGradient.AddColor(CreatePercentGradientColor(1, Color::WHITE));
            break;
    }
    listRenderContext->UpdateBackBlendMode(BlendMode::SRC_IN);
    listRenderContext->UpdateBackBlendApplyType(BlendApplyType::OFFSCREEN);
    stackRenderContext->UpdateLinearGradient(coverGradient);
    stackRenderContext->UpdateBackBlendMode(BlendMode::SRC_OVER);
    stackRenderContext->UpdateBackBlendApplyType(BlendApplyType::OFFSCREEN);
}

GradientColor IndexerPattern::CreatePercentGradientColor(float percent, Color color)
{
    NG::GradientColor gredient = GradientColor(color);
    gredient.SetDimension(CalcDimension(percent * PERCENT_100, DimensionUnit::PERCENT));
    return gredient;
}

CalcSize IndexerPattern::CalcBubbleListSize(int32_t popupSize, int32_t maxItemsSize)
{
    auto bubbleSize = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    auto bubbleHeight = Dimension(BUBBLE_ITEM_SIZE, DimensionUnit::VP).ConvertToPx();
    auto bubbleDivider = Dimension(BUBBLE_DIVIDER_SIZE, DimensionUnit::VP).ConvertToPx();
    auto listCalcSize = CalcSize();
    if (popupSize <= maxItemsSize) {
        listCalcSize = CalcSize(
            CalcLength(bubbleSize),
            CalcLength((bubbleHeight + bubbleDivider) * static_cast<int32_t>(popupSize) - bubbleDivider));
    } else {
        if (autoCollapse_) {
            listCalcSize = CalcSize(
                CalcLength(bubbleSize),
                CalcLength(Dimension(BUBBLE_COLLAPSE_LIST_MAX_SIZE, DimensionUnit::VP).ConvertToPx()));
        } else {
            listCalcSize = CalcSize(
                CalcLength(bubbleSize),
                CalcLength(Dimension(BUBBLE_LIST_MAX_SIZE, DimensionUnit::VP).ConvertToPx()));
        }
    }
    return listCalcSize;
}

void IndexerPattern::UpdateBubbleListItem(
    std::vector<std::string>& currentListData, const RefPtr<FrameNode>& listNode, RefPtr<IndexerTheme>& indexerTheme)
{
    CHECK_NULL_VOID(listNode);
    CHECK_NULL_VOID(indexerTheme);
    auto layoutProperty = GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto paintProperty = GetPaintProperty<IndexerPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto popupSelectedTextColor =
        paintProperty->GetPopupSelectedColor().value_or(indexerTheme->GetPopupSelectedTextColor());
    auto popupUnselectedTextColor =
        paintProperty->GetPopupUnselectedColor().value_or(indexerTheme->GetPopupUnselectedTextColor());
    auto popupItemTextFontSize =
        layoutProperty->GetFontSize().value_or(indexerTheme->GetPopupTextStyle().GetFontSize());
    auto popupItemTextFontWeight =
        layoutProperty->GetFontWeight().value_or(indexerTheme->GetPopupTextStyle().GetFontWeight());
    auto bubbleSize = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)
                          ? Dimension(BUBBLE_ITEM_SIZE, DimensionUnit::VP).ConvertToPx()
                          : Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    for (uint32_t i = 0; i < currentListData.size(); i++) {
        auto childIndexOffset = autoCollapse_ ? 1 : 0;
        auto listItemNode = DynamicCast<FrameNode>(listNode->GetChildAtIndex(i + childIndexOffset));
        CHECK_NULL_VOID(listItemNode);
        auto listItemProperty = listItemNode->GetLayoutProperty<ListItemLayoutProperty>();
        CHECK_NULL_VOID(listItemProperty);
        listItemProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(bubbleSize), CalcLength(bubbleSize)));
        listItemProperty->UpdateAlignment(Alignment::CENTER);
        auto listItemContext = listItemNode->GetRenderContext();
        CHECK_NULL_VOID(listItemContext);
        auto textNode = DynamicCast<FrameNode>(listItemNode->GetFirstChild());
        CHECK_NULL_VOID(textNode);
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateContent(currentListData.at(i));
        textLayoutProperty->UpdateFontSize(popupItemTextFontSize);
        textLayoutProperty->UpdateFontWeight(popupItemTextFontWeight);
        textLayoutProperty->UpdateMaxLines(1);
        textLayoutProperty->UpdateTextColor(
            static_cast<int32_t>(i) == popupClickedIndex_ ? popupSelectedTextColor : popupUnselectedTextColor);
        textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
        textLayoutProperty->UpdateAlignment(Alignment::CENTER);
        textLayoutProperty->UpdateMinFontScale(1.0f);
        textLayoutProperty->UpdateMaxFontScale(1.0f);
        UpdateBubbleListItemContext(listNode, indexerTheme, i);
        UpdateBubbleListItemMarkModify(textNode, listItemNode);
    }
}

void IndexerPattern::UpdateBubbleListItemContext(
    const RefPtr<FrameNode>& listNode, RefPtr<IndexerTheme>& indexerTheme, uint32_t pos)
{
    CHECK_NULL_VOID(listNode);
    auto layoutProperty = GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto paintProperty = GetPaintProperty<IndexerPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto childIndexOffset = autoCollapse_ ? 1 : 0;
    auto listItemNode = DynamicCast<FrameNode>(listNode->GetChildAtIndex(pos + childIndexOffset));
    CHECK_NULL_VOID(listItemNode);
    auto listItemContext = listItemNode->GetRenderContext();
    CHECK_NULL_VOID(listItemContext);
    auto popupItemBackground =
            paintProperty->GetPopupItemBackground().value_or(indexerTheme->GetPopupUnclickedBgAreaColor());
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto popupItemRadius = paintProperty->GetPopupItemBorderRadius().has_value()
                                    ? paintProperty->GetPopupItemBorderRadiusValue()
                                    : Dimension(BUBBLE_ITEM_RADIUS, DimensionUnit::VP);
        listItemContext->UpdateBorderRadius({ popupItemRadius, popupItemRadius, popupItemRadius, popupItemRadius });
        listItemContext->UpdateBackgroundColor(static_cast<int32_t>(pos) == popupClickedIndex_
                                                   ? (indexerTheme->GetPopupClickedBgAreaColor())
                                                   : popupItemBackground);
    } else {
        listItemContext->UpdateBackgroundColor(
            static_cast<int32_t>(pos) == popupClickedIndex_ ? Color(POPUP_LISTITEM_CLICKED_BG) : popupItemBackground);
    }
}

void IndexerPattern::UpdateBubbleListItemMarkModify(RefPtr<FrameNode>& textNode, RefPtr<FrameNode>& listItemNode)
{
    textNode->MarkModifyDone();
    textNode->MarkDirtyNode();
    listItemNode->MarkModifyDone();
    listItemNode->MarkDirtyNode();
}

void IndexerPattern::ChangeListItemsSelectedStyle(int32_t clickIndex)
{
    popupClickedIndex_ = clickIndex;
    auto host = GetHost();
    CHECK_NULL_VOID(popupNode_);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto indexerTheme = pipelineContext->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    auto paintProperty = host->GetPaintProperty<IndexerPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto popupSelectedTextColor =
        paintProperty->GetPopupSelectedColor().value_or(indexerTheme->GetPopupSelectedTextColor());
    auto popupUnselectedTextColor =
        paintProperty->GetPopupUnselectedColor().value_or(indexerTheme->GetPopupUnselectedTextColor());
    auto popupItemBackground =
        paintProperty->GetPopupItemBackground().value_or(indexerTheme->GetPopupUnclickedBgAreaColor());
    auto listNode = popupNode_->GetLastChild()->GetFirstChild();
    auto currentIndex = 0;
    for (auto child : listNode->GetChildren()) {
        if (autoCollapse_ && listNode->GetChildIndex(child) == 0) continue;
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
            textLayoutProperty->UpdateTextColor(popupSelectedTextColor);
            listItemContext->UpdateBackgroundColor(
                Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)
                    ? indexerTheme->GetPopupClickedBgAreaColor()
                    : Color(POPUP_LISTITEM_CLICKED_BG));
        } else {
            textLayoutProperty->UpdateTextColor(popupUnselectedTextColor);
            listItemContext->UpdateBackgroundColor(popupItemBackground);
        }
        textNode->MarkModifyDone();
        textNode->MarkDirtyNode();
        listItemNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        currentIndex++;
    }
}

void IndexerPattern::AddPopupTouchListener(RefPtr<FrameNode> popupNode)
{
    CHECK_NULL_VOID(popupNode);
    auto gesture = popupNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchCallback = [weak = WeakClaim(this)](TouchEventInfo& info) {
        auto indexerPattern = weak.Upgrade();
        CHECK_NULL_VOID(indexerPattern);
        info.SetStopPropagation(true);
        if (info.GetTouches().empty()) {
            return;
        }
        auto touchType = info.GetTouches().front().GetTouchType();
        if (touchType == TouchType::DOWN) {
            indexerPattern->isTouch_ = true;
            indexerPattern->OnPopupTouchDown(info);
        } else if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
            indexerPattern->isTouch_ = false;
            if (!indexerPattern->isPopupHover_) {
                indexerPattern->StartDelayTask();
            }
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
        if (info.GetTouches().empty()) {
            return;
        }
        TouchType touchType = info.GetTouches().front().GetTouchType();
        if (touchType == TouchType::DOWN) {
            indexerPattern->OnListItemClick(index);
        } else if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
            indexerPattern->ClearClickStatus();
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
    ReportPoupSelectEvent();
    if (onPopupSelected) {
        onPopupSelected(index);
        UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "onPopupSelected");
    }
    ChangeListItemsSelectedStyle(index);
}

void IndexerPattern::ClearClickStatus()
{
    ChangeListItemsSelectedStyle(-1);
}

void IndexerPattern::OnPopupTouchDown(const TouchEventInfo& info)
{
    if (NeedShowPopupView()) {
        delayTask_.Cancel();
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
    OnKeyEventDisappear();
    return false;
}

void IndexerPattern::OnKeyEventDisappear()
{
    ResetStatus();
    ApplyIndexChanged(true, false);
}

void IndexerPattern::ItemSelectedInAnimation(RefPtr<FrameNode>& itemNode)
{
    CHECK_NULL_VOID(itemNode);
    auto renderContext = itemNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto indexerTheme = pipelineContext->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    auto paintProperty = host->GetPaintProperty<IndexerPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    Color selectedBackgroundColor =
        paintProperty->GetSelectedBackgroundColor().value_or(indexerTheme->GetSelectedBackgroundColor());
    AnimationOption option;
    option.SetDuration(INDEXER_SELECT_DURATION);
    option.SetCurve(Curves::LINEAR);
    AnimationUtils::Animate(option, [renderContext, id = Container::CurrentId(), selectedBackgroundColor]() {
        ContainerScope scope(id);
        renderContext->UpdateBackgroundColor(selectedBackgroundColor);
    });
}

void IndexerPattern::ItemSelectedOutAnimation(RefPtr<FrameNode>& itemNode)
{
    CHECK_NULL_VOID(itemNode);
    auto renderContext = itemNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    AnimationOption option;
    option.SetDuration(INDEXER_SELECT_DURATION);
    option.SetCurve(Curves::LINEAR);
    AnimationUtils::Animate(option, [renderContext, id = Container::CurrentId()]() {
        ContainerScope scope(id);
        renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    });
}

void IndexerPattern::IndexerHoverInAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto indexerTheme = pipelineContext->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    Color slipHoverBackgroundColor = indexerTheme->GetSlipHoverBackgroundColor();
    AnimationOption option;
    option.SetDuration(INDEXER_HOVER_IN_DURATION);
    option.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(option, [renderContext, id = Container::CurrentId(), slipHoverBackgroundColor]() {
        ContainerScope scope(id);
        renderContext->UpdateBackgroundColor(slipHoverBackgroundColor);
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
        renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    });
}

void IndexerPattern::IndexerPressInAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto indexerTheme = pipelineContext->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    Color backgroundColor = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)
                                ? indexerTheme->GetSlipPressedBackgroundColor()
                                : indexerTheme->GetSlipHoverBackgroundColor();
    AnimationOption option;
    option.SetDuration(INDEXER_PRESS_IN_DURATION);
    option.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(option, [renderContext, id = Container::CurrentId(), backgroundColor]() {
        ContainerScope scope(id);
        renderContext->UpdateBackgroundColor(backgroundColor);
    });
}

void IndexerPattern::IndexerPressOutAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto indexerTheme = pipelineContext->GetTheme<IndexerTheme>();
    CHECK_NULL_VOID(indexerTheme);
    Color backgroundColor = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)
                                ? indexerTheme->GetSlipPressedBackgroundColor()
                                : indexerTheme->GetSlipHoverBackgroundColor();
    AnimationOption option;
    option.SetDuration(INDEXER_PRESS_OUT_DURATION);
    option.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(option, [renderContext, id = Container::CurrentId(), backgroundColor]() {
        ContainerScope scope(id);
        renderContext->UpdateBackgroundColor(backgroundColor);
    });
}

void IndexerPattern::StartBubbleAppearAnimation()
{
    animationId_ = GenerateAnimationId();
    UpdatePopupVisibility(VisibleType::VISIBLE);
    AnimationOption option;
    option.SetCurve(Curves::SHARP);
    option.SetDuration(INDEXER_BUBBLE_ENTER_DURATION);
    AnimationUtils::Animate(
        option,
        [id = Container::CurrentId(), weak = AceType::WeakClaim(this)]() {
            ContainerScope scope(id);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->UpdatePopupOpacity(1.0f);
        });
}

void IndexerPattern::StartDelayTask(uint32_t duration)
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
        delayTask_, TaskExecutor::TaskType::UI, duration, "ArkUIAlphabetIndexerBubbleDisappear");
}

void IndexerPattern::StartCollapseDelayTask(RefPtr<FrameNode>& hostNode, uint32_t duration)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    CHECK_NULL_VOID(context->GetTaskExecutor());
    delayCollapseTask_.Reset([node = WeakClaim(RawPtr(hostNode))]() {
        auto hostNode = node.Upgrade();
        CHECK_NULL_VOID(hostNode);
        hostNode->MarkModifyDone();
        hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    });
    context->GetTaskExecutor()->PostDelayedTask(
        delayCollapseTask_, TaskExecutor::TaskType::UI, duration, "ArkUIAlphabetIndexerCollapse");
}

void IndexerPattern::StartBubbleDisappearAnimation()
{
    AnimationOption option;
    option.SetCurve(Curves::SHARP);
    option.SetDuration(INDEXER_BUBBLE_EXIT_DURATION);
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
            auto renderContext = pattern->popupNode_->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            if (NearZero(renderContext->GetOpacityValue(0.0f))) {
                pattern->UpdatePopupVisibility(VisibleType::GONE);
            }
        });
}

void IndexerPattern::UpdatePopupOpacity(float ratio)
{
    CHECK_NULL_VOID(popupNode_);
    auto renderContext = popupNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateOpacity(ratio);
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

void IndexerPattern::FireOnSelect(int32_t selectIndex, bool fromPress)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto indexerEventHub = host->GetEventHub<IndexerEventHub>();
    CHECK_NULL_VOID(indexerEventHub);
    int32_t actualIndex = GetActualIndex(selectIndex);
    if (fromPress || lastIndexFromPress_ == fromPress || lastFireSelectIndex_ != selectIndex) {
        auto onChangeEvent = indexerEventHub->GetChangeEvent();
        if (onChangeEvent && (selected_ >= 0) && (selected_ < itemCount_)) {
            onChangeEvent(actualIndex);
        }
        auto onCreatChangeEvent = indexerEventHub->GetCreatChangeEvent();
        if (onCreatChangeEvent && (selected_ >= 0) && (selected_ < itemCount_)) {
            onCreatChangeEvent(actualIndex);
        }
        auto onSelected = indexerEventHub->GetOnSelected();
        if ((selectIndex >= 0) && (selectIndex < itemCount_)) {
            if (onSelected) {
                TAG_LOGD(AceLogTag::ACE_ALPHABET_INDEXER, "item %{public}d is selected", actualIndex);
                onSelected(actualIndex); // fire onSelected with an item's index from original array
            }
            UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "Indexer.onSelected");
            TAG_LOGI(AceLogTag::ACE_ALPHABET_INDEXER,
                "nodeId:[%{public}d] Indexer reportComponentChangeEvent onSelected", GetHost()->GetId());
        }
    }
    selectedChangedForHaptic_ = lastFireSelectIndex_ != selected_;
    lastFireSelectIndex_ = selectIndex;
    lastIndexFromPress_ = fromPress;
}

void IndexerPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto childrenNode = host->GetChildren();
    for (auto& iter : childrenNode) {
        auto textNode = DynamicCast<NG::FrameNode>(iter);
        CHECK_NULL_VOID(textNode);
        auto accessibilityProperty = textNode->GetAccessibilityProperty<AccessibilityProperty>();
        CHECK_NULL_VOID(accessibilityProperty);
        SetActionSelect(textNode, accessibilityProperty);
        SetActionClearSelection(textNode, accessibilityProperty);
    }
}

void IndexerPattern::SetActionSelect(RefPtr<FrameNode>& textNode, RefPtr<AccessibilityProperty>& accessibilityProperty)
{
    CHECK_NULL_VOID(textNode);
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionSelect(
        [weakPtr = WeakClaim(this), node = WeakClaim(RawPtr(textNode))]() {
            const auto& indexerPattern = weakPtr.Upgrade();
            CHECK_NULL_VOID(indexerPattern);
            auto host = indexerPattern->GetHost();
            CHECK_NULL_VOID(host);
            auto childrenNode = host->GetChildren();
            const auto& frameNode = node.Upgrade();
            CHECK_NULL_VOID(frameNode);
            auto index = 0;
            auto nodeId = frameNode->GetAccessibilityId();
            for (auto& child : childrenNode) {
                if (child->GetAccessibilityId() == nodeId) {
                    break;
                }
                index++;
            }
            indexerPattern->selected_ = index;
            indexerPattern->ResetStatus();
            indexerPattern->ApplyIndexChanged(true, true, true);
            indexerPattern->OnSelect();
        });
}

void IndexerPattern::SetActionClearSelection(
    RefPtr<FrameNode>& textNode, RefPtr<AccessibilityProperty>& accessibilityProperty)
{
    CHECK_NULL_VOID(textNode);
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionClearSelection(
        [weakPtr = WeakClaim(this), node = WeakClaim(RawPtr(textNode))] {
            const auto& indexerPattern = weakPtr.Upgrade();
            CHECK_NULL_VOID(indexerPattern);
            auto host = indexerPattern->GetHost();
            CHECK_NULL_VOID(host);
            auto childrenNode = host->GetChildren();
            const auto& frameNode = node.Upgrade();
            CHECK_NULL_VOID(frameNode);
            auto index = 0;
            auto nodeId = frameNode->GetAccessibilityId();
            for (auto& child : childrenNode) {
                if (child->GetAccessibilityId() == nodeId) {
                    break;
                }
                index++;
            }
            if (indexerPattern->selected_ != index) {
                return;
            }
            indexerPattern->selected_ = 0;
            indexerPattern->ResetStatus();
            indexerPattern->ApplyIndexChanged(true, false);
            indexerPattern->OnSelect();
        });
}

void IndexerPattern::RemoveBubble()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->RemoveChild(popupNode_);
    auto layoutProperty = host->GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateIsPopup(false);
    popupNode_ = nullptr;
    lastPopupIndex_ = -1;
}

bool IndexerPattern::IsMeasureBoundary() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return CheckMeasureSelfFlag(layoutProperty->GetPropertyChangeFlag());
}

void IndexerPattern::UpdateChildBoundary(RefPtr<FrameNode>& frameNode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    CHECK_NULL_VOID(frameNode);
    auto pattern = DynamicCast<TextPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pattern);
    auto isMeasureBoundary = layoutProperty->GetPropertyChangeFlag() ==  PROPERTY_UPDATE_NORMAL;
    pattern->SetIsMeasureBoundary(isMeasureBoundary);
}

void IndexerPattern::DumpInfo()
{
    auto layoutProperty = GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    DumpLog::GetInstance().AddDesc(
        "AlignStyle: ", static_cast<int32_t>(layoutProperty->GetAlignStyleValue(AlignStyle::END)));
    auto offset = layoutProperty->GetPopupHorizontalSpace();
    DumpLog::GetInstance().AddDesc("Offset: ", offset.has_value() ? offset.value().ToString() : "undefined");
    DumpLog::GetInstance().AddDesc("PopupPositionX: ",
        layoutProperty->GetPopupPositionXValue(Dimension(NG::BUBBLE_POSITION_X, DimensionUnit::VP)).ToString());
    DumpLog::GetInstance().AddDesc("PopupPositionY: ",
        layoutProperty->GetPopupPositionYValue(Dimension(NG::BUBBLE_POSITION_Y, DimensionUnit::VP)).ToString());
    DumpLog::GetInstance().AddDesc("AutoCollapse: ", autoCollapse_ ? "true" : "false");
    DumpLog::GetInstance().AddDesc("IsPopup: ", isPopup_ ? "true" : "false");
    DumpLog::GetInstance().AddDesc(std::string("EnableHapticFeedback: ").append(std::to_string(enableHapticFeedback_)));
    DumpLog::GetInstance().AddDesc("ItemSize: ", lastItemSize_);
    DumpLog::GetInstance().AddDesc("ItemHeight: ", itemHeight_);
    DumpLog::GetInstance().AddDesc("ActualItemCount: ", itemCount_);
    DumpLog::GetInstance().AddDesc("FullItemCount: ", static_cast<int32_t>(fullArrayValue_.size()));
    DumpLog::GetInstance().AddDesc("MaxContentHeight: ", maxContentHeight_);
}

void IndexerPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    auto layoutProperty = GetLayoutProperty<IndexerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    json->Put("AlignStyle", static_cast<int32_t>(layoutProperty->GetAlignStyleValue(AlignStyle::END)));

    auto offset = layoutProperty->GetPopupHorizontalSpace();
    json->Put("Offset", offset.has_value() ? offset.value().ToString().c_str() : "undefined");
    json->Put("PopupPositionX",
        layoutProperty->GetPopupPositionXValue(Dimension(NG::BUBBLE_POSITION_X, DimensionUnit::VP)).ToString().c_str());
    json->Put("PopupPositionY",
        layoutProperty->GetPopupPositionYValue(Dimension(NG::BUBBLE_POSITION_Y, DimensionUnit::VP)).ToString().c_str());
    json->Put("AutoCollapse", autoCollapse_ ? "true" : "false");
    json->Put("IsPopup", isPopup_ ? "true" : "false");
    json->Put("EnableHapticFeedback", std::to_string(enableHapticFeedback_).c_str());
    json->Put("ItemSize", lastItemSize_);
    json->Put("ItemHeight", itemHeight_);
    json->Put("ActualItemCount", itemCount_);
    json->Put("FullItemCount", static_cast<int32_t>(fullArrayValue_.size()));
    json->Put("MaxContentHeight", maxContentHeight_);
}

void IndexerPattern::ReportSelectEvent()
{
    if (initialized_ && selectChanged_) {
        UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "Indexer.onSelected");
        TAG_LOGI(AceLogTag::ACE_ALPHABET_INDEXER, "nodeId:[%{public}d] Indexer reportComponentChangeEvent onSelected",
            GetHost()->GetId());
    }
}

void IndexerPattern::ReportPoupSelectEvent()
{
    UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "Indexer.onPopupSelect");
    TAG_LOGI(AceLogTag::ACE_ALPHABET_INDEXER, "nodeId:[%{public}d] Indexer reportComponentChangeEvent onPopupSelect",
        GetHost()->GetId());
}
} // namespace OHOS::Ace::NG
