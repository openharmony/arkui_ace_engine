/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"

#include <algorithm>
#include <cmath>
#include <map>

#include "base/log/dump_log.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_utils.h"
#include "core/event/ace_events.h"
#include "core/event/mouse_event.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline/base/constants.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t ICON_FADE_ANIMATION_DURATION = 150;
constexpr uint32_t INDICATOR_HAS_CHILD = 2;
constexpr int32_t OVERLONG_THIRD_POINT_INDEX = 2;
constexpr Dimension INDICATOR_DRAG_MIN_DISTANCE = 4.0_vp;
constexpr Dimension INDICATOR_DRAG_MAX_DISTANCE = 18.0_vp;
constexpr Dimension INDICATOR_TOUCH_BOTTOM_MAX_DISTANCE = 80.0_vp;
constexpr Dimension DEFAULT_SYMBOL_ITEM_SIZE = 10.0_vp;
constexpr Dimension DEFAULT_SYMBOL_SELECTED_ITEM_SIZE = 10.0_vp;
constexpr int32_t MULTIPLIER = 2;
constexpr int32_t LONG_PRESS_DELAY = 300;
constexpr float HALF_FLOAT = 0.5f;
constexpr float MAX_FONT_SCALE = 2.0f;
constexpr double QUARTER_CIRCLE_ANGLE = 90.0;
constexpr double HALF_CIRCLE_ANGLE = 180.0;
constexpr double THREE_QUARTER_CIRCLE_ANGLE = 270.0;
constexpr double FULL_CIRCLE_ANGLE = 360.0;
constexpr Dimension CONTAINER_BORDER_WIDTH = 24.0_vp;
constexpr float INDICATOR_TOUCH_BOTTOM_MAX_ANGLE = 120.0;
constexpr Color DEFAULT_SYMBOL_ITEM_COLOR = Color(0x33FFFFFF);
constexpr Color DEFAULT_SYMBOL_SELECTED_ITEM_COLOR = Color(0xFFFFFFFF);

OverlongType GetInitOverlongType(int32_t currentIndex, int32_t realItemCount, int32_t maxDisplayCount)
{
    if (realItemCount <= 0 || maxDisplayCount <= 0) {
        return OverlongType::NONE;
    }
    if (currentIndex < 0) {
        currentIndex = 0;
    }
    if (currentIndex < maxDisplayCount - 1 - OVERLONG_THIRD_POINT_INDEX) {
        return OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    }
    int32_t rightFadeBeginIndex = realItemCount - 1 - OVERLONG_THIRD_POINT_INDEX;
    if (currentIndex < rightFadeBeginIndex) {
        return OverlongType::LEFT_FADEOUT_RIGHT_FADEOUT;
    }
    return OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
}

RefPtr<FrameNode> CreateCustomIconContentNode(const IndicatorIconParam& iconParam)
{
    if (iconParam.sourceType == IndicatorIconParam::SourceType::MEDIA) {
        return FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    }
    return FrameNode::CreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
}

bool IsCustomIconContentTagMatched(const RefPtr<FrameNode>& iconNode, const IndicatorIconParam& iconParam)
{
    CHECK_NULL_RETURN(iconNode, false);
    auto expectedTag = iconParam.sourceType == IndicatorIconParam::SourceType::MEDIA ? V2::IMAGE_ETS_TAG :
        V2::SYMBOL_ETS_TAG;
    return iconNode->GetTag() == expectedTag;
}

bool IsCustomIconHoverHit(
    const PointF& hoverPoint, Axis axis, const SizeF& frameSize, float centerX, const SizeF& iconSize)
{
    if (LessOrEqual(iconSize.Width(), 0.0f) || LessOrEqual(iconSize.Height(), 0.0f)) {
        return false;
    }
    PointF localHoverPoint = axis == Axis::HORIZONTAL ? hoverPoint : PointF(hoverPoint.GetY(), hoverPoint.GetX());
    float crossSize = axis == Axis::HORIZONTAL ? frameSize.Height() : frameSize.Width();
    float left = centerX - iconSize.Width() * HALF_FLOAT;
    float right = centerX + iconSize.Width() * HALF_FLOAT;
    float top = (crossSize - iconSize.Height()) * HALF_FLOAT;
    float bottom = top + iconSize.Height();
    return GreatOrEqual(localHoverPoint.GetX(), left) && LessOrEqual(localHoverPoint.GetX(), right) &&
           GreatOrEqual(localHoverPoint.GetY(), top) && LessOrEqual(localHoverPoint.GetY(), bottom);
}

RefPtr<FrameNode> FindWrapperNodeById(const std::map<int32_t, RefPtr<FrameNode>>& wrapperMap, int32_t wrapperId)
{
    for (const auto& [itemIndex, wrapperNode] : wrapperMap) {
        if (wrapperNode && wrapperNode->GetId() == wrapperId) {
            return wrapperNode;
        }
    }
    return nullptr;
}
} // namespace

void SwiperIndicatorPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToBounds(false);
}

void SwiperIndicatorPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    ACE_UINODE_TRACE(host);
    if (GetIndicatorType() == SwiperIndicatorType::DIGIT) {
        auto hasIconState = ClearIndicatorIconState();
        if (hasIconState) {
            host->Clean();
        }
        UpdateDigitalIndicator();
    } else if (UpdateCustomDotIndicatorLayoutFlag()) {
        if (indicatorWrapperNodeByItem_.empty() && !host->GetChildren().empty()) {
            host->Clean();
        }
        UpdateDotIndicatorIconNodes();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    } else {
        ClearIndicatorIconState();
        host->Clean();
    }

    if (dotIndicatorModifier_) {
        dotIndicatorModifier_->StopAnimation();
    }

    InitIndicatorEvent();
}

void SwiperIndicatorPattern::InitIndicatorEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    RegisterIndicatorChangeEvent();

    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (GetIndicatorType() == SwiperIndicatorType::DOT) {
        InitClickEvent(gestureHub);
        InitHoverMouseEvent();
        InitTouchEvent(gestureHub);
        InitLongPressEvent(gestureHub);
        InitFocusEvent();
    } else {
        if (clickEvent_) {
            gestureHub->RemoveClickEvent(clickEvent_);
            clickEvent_ = nullptr;
        }
    }

    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_VOID(swiperPattern);
    swiperIndicatorType_ = swiperPattern->GetIndicatorType();
    auto swiperLayoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    if (swiperLayoutProperty->GetIndicatorTypeValue(SwiperIndicatorType::ARC_DOT) == SwiperIndicatorType::ARC_DOT) {
        InitTouchEvent(gestureHub);
        InitLongPressEvent(gestureHub);
        InitAccessibilityFocusEvent();
    }
}

void SwiperIndicatorPattern::UpdateDigitalIndicator()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    RefPtr<FrameNode> firstTextNode;
    RefPtr<FrameNode> lastTextNode;
    auto layoutProperty = host->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (host->GetChildren().size() == INDICATOR_HAS_CHILD) {
        firstTextNode = DynamicCast<FrameNode>(host->GetFirstChild());
        lastTextNode = DynamicCast<FrameNode>(host->GetLastChild());
    } else {
        host->Clean();
        firstTextNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        lastTextNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    }
    UpdateTextContent(layoutProperty, firstTextNode, lastTextNode);
    host->AddChild(firstTextNode);
    host->AddChild(lastTextNode);
}

std::shared_ptr<SwiperParameters> SwiperIndicatorPattern::ObtainSwiperParameters() const
{
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_RETURN(swiperPattern, nullptr);
    return swiperPattern->GetSwiperParameters();
}

Color SwiperIndicatorPattern::GetDefaultSymbolColor(bool isSelected) const
{
    return isSelected ? DEFAULT_SYMBOL_SELECTED_ITEM_COLOR : DEFAULT_SYMBOL_ITEM_COLOR;
}

bool SwiperIndicatorPattern::UpdateCustomDotIndicatorLayoutFlag()
{
    auto params = ObtainSwiperParameters();
    hasCustomDotIndicatorLayout_ =
        GetIndicatorType() == SwiperIndicatorType::DOT && params && !params->indicatorIconMap.empty();
    return hasCustomDotIndicatorLayout_;
}

LinearVector<float> SwiperIndicatorPattern::GetCustomIconCenterX() const
{
    if (!NeedCustomDotIndicatorLayout()) {
        return {};
    }
    LinearVector<float> centers;
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_RETURN(swiperPattern, centers);
    auto isOverlong = swiperPattern->GetMaxDisplayCount() > 0;
    if (isOverlong && overlongDotIndicatorModifier_) {
        centers = overlongDotIndicatorModifier_->GetVisibleAnimationStartCenterXOrCurrent();
    } else if (dotIndicatorModifier_) {
        centers = dotIndicatorModifier_->GetBlackPointCenterX();
    } 
    auto expectedCount = swiperPattern->GetMaxDisplayCount() > 0 ? swiperPattern->GetMaxDisplayCount()
                                                                   : DisplayIndicatorTotalCount();
    auto result = centers.size() >= static_cast<size_t>(expectedCount) ? centers : LinearVector<float>();
    return result;
}

std::optional<int32_t> SwiperIndicatorPattern::GetCustomIconVisibleIndex(int32_t itemIndex) const
{
    if (!NeedCustomDotIndicatorLayout()) {
        return std::nullopt;
    }
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_RETURN(swiperPattern, std::nullopt);
    auto isRtl = swiperPattern->IsHorizontalAndRightToLeft();
    auto toVisualSlot = [isRtl](const std::optional<int32_t>& slot, int32_t visibleCount) -> std::optional<int32_t> {
        if (!slot.has_value()) {
            return std::nullopt;
        }
        if (slot.value() < 0 || slot.value() >= visibleCount) {
            return std::nullopt;
        }
        if (!isRtl) {
            return slot;
        }
        return visibleCount - 1 - slot.value();
    };
    auto maxDisplayCount = swiperPattern->GetMaxDisplayCount();
    if (maxDisplayCount <= 0) {
        return toVisualSlot(itemIndex, DisplayIndicatorTotalCount());
    }
    if (overlongDotIndicatorModifier_) {
        if (overlongDotIndicatorModifier_->IsDraggingIndicator()) {
            auto currentIndex = swiperPattern->GetLoopIndex(swiperPattern->GetCurrentIndex());
            auto realItemCount = swiperPattern->RealTotalCount();
            auto overlongType = overlongDotIndicatorModifier_->GetCurrentOverlongType();
            auto slot = OverlengthDotIndicatorModifier::CalcSlotForPage(
                itemIndex, currentIndex, realItemCount, maxDisplayCount, overlongType);
            return toVisualSlot(slot, maxDisplayCount);
        }
        return toVisualSlot(overlongDotIndicatorModifier_->GetSlotForPage(itemIndex), maxDisplayCount);
    }
    auto currentIndex = swiperPattern->GetLoopIndex(swiperPattern->GetCurrentFirstIndex());
    auto realItemCount = swiperPattern->RealTotalCount();
    auto fallbackType = GetInitOverlongType(currentIndex, realItemCount, maxDisplayCount);
    auto slot = OverlengthDotIndicatorModifier::CalcSlotForPage(
        itemIndex, currentIndex, realItemCount, maxDisplayCount, fallbackType);
    return toVisualSlot(slot, maxDisplayCount);
}

bool SwiperIndicatorPattern::HasValidCustomIconAtIndex(int32_t itemIndex) const
{
    auto params = ObtainSwiperParameters();
    CHECK_NULL_RETURN(params, false);
    auto iconIter = params->indicatorIconMap.find(itemIndex);
    if (iconIter == params->indicatorIconMap.end()) {
        return false;
    }
    const auto& iconParam = iconIter->second;
    if (iconParam.sourceType == IndicatorIconParam::SourceType::NONE) {
        return false;
    }
    if (iconParam.sourceType == IndicatorIconParam::SourceType::SYMBOL) {
        return iconParam.symbolApply != nullptr;
    }
    if (iconParam.sourceType == IndicatorIconParam::SourceType::MEDIA) {
        return !iconParam.iconSrc.empty();
    }
    return true;
}

int32_t SwiperIndicatorPattern::GetStableCustomIconSelectedPageIndex(const RefPtr<SwiperPattern>& swiperPattern) const
{
    CHECK_NULL_RETURN(swiperPattern, 0);
    auto indicatorCount = swiperPattern->DisplayIndicatorTotalCount();
    auto sourceIndex = swiperPattern->GetLoopIndex(swiperPattern->GetCurrentIndex());
    auto firstIndex = swiperPattern->GetLoopIndex(swiperPattern->GetCurrentFirstIndex());
    auto displayCount = swiperPattern->GetDisplayCount();
    if (!swiperPattern->IsAutoLinear() && swiperPattern->IsSwipeByGroup() && displayCount != 0) {
        sourceIndex /= displayCount;
        firstIndex /= displayCount;
    }
    auto normalizeIndex = [indicatorCount](int32_t index) {
        if (index < 0) {
            return indicatorCount - 1;
        }
        if (index >= indicatorCount) {
            return 0;
        }
        return index;
    };
    sourceIndex = normalizeIndex(sourceIndex);
    firstIndex = normalizeIndex(firstIndex);
    auto actualTurnPageRate = (!swiperPattern->IsAutoLinear() && swiperPattern->IsSwipeByGroup()) ?
        swiperPattern->GetGroupTurnPageRate() : swiperPattern->GetTurnPageRate();
    auto isPageTransitionRunning = swiperPattern->IsTouchDown() || !NearZero(actualTurnPageRate);
    auto involvedCustomIcon = HasValidCustomIconAtIndex(sourceIndex) || HasValidCustomIconAtIndex(firstIndex);
    auto keepSourceIndexSelected = isPageTransitionRunning && sourceIndex != firstIndex && involvedCustomIcon;
    return keepSourceIndexSelected ? sourceIndex : firstIndex;
}

bool SwiperIndicatorPattern::IsCustomIconSelected(int32_t itemIndex) const
{
    if (!NeedCustomDotIndicatorLayout()) {
        return false;
    }
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_RETURN(swiperPattern, false);
    auto currentIndex = GetStableCustomIconSelectedPageIndex(swiperPattern);
    return itemIndex == currentIndex;
}

void SwiperIndicatorPattern::UpdateDotIndicatorIconNode(const RefPtr<FrameNode>& iconNode, int32_t itemIndex)
{
    CHECK_NULL_VOID(iconNode);
    auto params = ObtainSwiperParameters();
    CHECK_NULL_VOID(params);
    auto iconIter = params->indicatorIconMap.find(itemIndex);
    if (iconIter == params->indicatorIconMap.end()) {
        return;
    }
    auto indicatorNode = GetHost();
    CHECK_NULL_VOID(indicatorNode);
    auto paintProperty = indicatorNode->GetPaintProperty<DotIndicatorPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto theme = indicatorNode->GetTheme<SwiperIndicatorTheme>(true);
    CHECK_NULL_VOID(theme);
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_VOID(swiperPattern);
    auto isSelected = IsCustomIconSelected(itemIndex);
    auto itemWidth = paintProperty->GetItemWidthValue(theme->GetSize()).ConvertToPx();
    auto itemHeight = paintProperty->GetItemHeightValue(theme->GetSize()).ConvertToPx();
    auto selectedWidth = paintProperty->GetSelectedItemWidthValue(theme->GetSize()).ConvertToPx();
    auto selectedHeight = paintProperty->GetSelectedItemHeightValue(theme->GetSize()).ConvertToPx();
    if (iconIter->second.sourceType == IndicatorIconParam::SourceType::SYMBOL ||
        iconIter->second.sourceType == IndicatorIconParam::SourceType::MEDIA) {
        auto paramsByUser = params->parametersByUser;
        if (paramsByUser.find("itemWidth") == paramsByUser.end()) {
            itemWidth = DEFAULT_SYMBOL_ITEM_SIZE.ConvertToPx();
        }
        if (paramsByUser.find("itemHeight") == paramsByUser.end()) {
            itemHeight = DEFAULT_SYMBOL_ITEM_SIZE.ConvertToPx();
        }
        if (paramsByUser.find("selectedItemWidth") == paramsByUser.end()) {
            selectedWidth = DEFAULT_SYMBOL_SELECTED_ITEM_SIZE.ConvertToPx();
        }
        if (paramsByUser.find("selectedItemHeight") == paramsByUser.end()) {
            selectedHeight = DEFAULT_SYMBOL_SELECTED_ITEM_SIZE.ConvertToPx();
        }
    }
    auto containerWidth = isSelected ? selectedWidth : itemWidth;
    auto containerHeight = isSelected ? selectedHeight : itemHeight;
    auto indicatorScale = theme->GetIndicatorScale();
    if (IsPressed() || IsHover()) {
        containerWidth *= indicatorScale;
        containerHeight *= indicatorScale;
    }
    bool isIconHover = false;
    if (IsHover()) {
        auto visibleIndex = GetCustomIconVisibleIndex(itemIndex);
        auto centers = GetCustomIconCenterX();
        auto geometryNode = indicatorNode->GetGeometryNode();
        auto axis = swiperPattern->GetDirection();
        if (visibleIndex.has_value() && geometryNode &&
            visibleIndex.value() >= 0 &&
            static_cast<size_t>(visibleIndex.value()) < centers.size()) {
            isIconHover = IsCustomIconHoverHit(
                hoverPoint_, axis, geometryNode->GetFrameSize(),
                centers[visibleIndex.value()], SizeF(containerWidth, containerHeight));
        }
    }
    if (isIconHover) {
        containerWidth *= indicatorScale;
        containerHeight *= indicatorScale;
    }
    auto fontSize = std::min(containerWidth, containerHeight);
    auto idealSize = CalcSize(
        CalcLength(containerWidth, DimensionUnit::PX), CalcLength(containerHeight, DimensionUnit::PX));
    if (iconIter->second.sourceType == IndicatorIconParam::SourceType::SYMBOL) {
        CHECK_NULL_VOID(iconIter->second.symbolApply);
        auto layoutProperty = iconNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        layoutProperty->UpdateTextAlign(TextAlign::CENTER);
        layoutProperty->UpdateMaxLines(1);
        layoutProperty->UpdateSymbolColorList({ GetDefaultSymbolColor(isSelected) });
        iconIter->second.symbolApply(AceType::WeakClaim(AceType::RawPtr(iconNode)));
        layoutProperty->UpdateLineHeight(Dimension(fontSize, DimensionUnit::PX));
        layoutProperty->UpdateFontSize(Dimension(fontSize, DimensionUnit::PX));
        layoutProperty->UpdateUserDefinedIdealSize(idealSize);
        iconNode->MarkModifyDone();
        iconNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT | PROPERTY_UPDATE_RENDER);
        return;
    }
    if (iconIter->second.sourceType == IndicatorIconParam::SourceType::MEDIA) {
        auto layoutProperty = iconNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        layoutProperty->UpdateImageSourceInfo(
            ImageSourceInfo(iconIter->second.iconSrc, iconIter->second.bundleName, iconIter->second.moduleName));
        layoutProperty->UpdateUserDefinedIdealSize(idealSize);
        iconNode->MarkModifyDone();
        iconNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT | PROPERTY_UPDATE_RENDER);
    }
}
void SwiperIndicatorPattern::UpdateDotIndicatorIconNodes()
{
    CHECK_NE_VOID(NeedCustomDotIndicatorLayout(), true);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto params = ObtainSwiperParameters();
    CHECK_NULL_VOID(params);
    std::map<int32_t, int32_t> visibleIndexes;
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_VOID(swiperPattern);
    auto maxDisplayCount = swiperPattern->GetMaxDisplayCount();
    auto itemCount = maxDisplayCount > 0 ? maxDisplayCount : DisplayIndicatorTotalCount();
    auto realItemCount = swiperPattern->RealTotalCount();
    for (const auto& [itemIndex, iconParam] : params->indicatorIconMap) {
        if (itemIndex < 0 || itemIndex >= realItemCount ||
            iconParam.sourceType == IndicatorIconParam::SourceType::NONE) {
            continue;
        }
        if (iconParam.sourceType == IndicatorIconParam::SourceType::SYMBOL && !iconParam.symbolApply) {
            continue;
        }
        if (iconParam.sourceType == IndicatorIconParam::SourceType::MEDIA && iconParam.iconSrc.empty()) {
            continue;
        }
        auto visibleIndex = GetCustomIconVisibleIndex(itemIndex);
        if (!visibleIndex.has_value() || visibleIndex.value() < 0 || visibleIndex.value() >= itemCount) {
            continue;
        }
        visibleIndexes.emplace(visibleIndex.value(), itemIndex);
    }
    std::map<int32_t, ActiveCustomIconInfo> previousInfoByItem;
    for (const auto& info : activeCustomIconInfos_) {
        previousInfoByItem[info.itemIndex] = info;
    }
    indicatorIconIndexes_.clear();
    activeCustomIconInfos_.clear();
    indicatorIconIndexes_.reserve(visibleIndexes.size());
    activeCustomIconInfos_.reserve(visibleIndexes.size());
    std::vector<RefPtr<FrameNode>> fadeInList;
    pendingFadeInSlots_.clear();
    for (const auto& [visibleIndex, itemIndex] : visibleIndexes) {
        auto iconIter = params->indicatorIconMap.find(itemIndex);
        if (iconIter == params->indicatorIconMap.end()) {
            continue;
        }
        RefPtr<FrameNode> wrapperNode;
        auto wrapperIter = indicatorWrapperNodeByItem_.find(itemIndex);
        if (wrapperIter != indicatorWrapperNodeByItem_.end()) {
            wrapperNode = wrapperIter->second;
        }
        bool wasVisible = previousInfoByItem.find(itemIndex) != previousInfoByItem.end();
        if (!wrapperNode) {
            wrapperNode = FrameNode::CreateFrameNode(V2::STACK_ETS_TAG,
                ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StackPattern>());
            CHECK_NULL_VOID(wrapperNode);
            host->AddChild(wrapperNode);
            indicatorWrapperNodeByItem_[itemIndex] = wrapperNode;
        }
        auto iconNode = AceType::DynamicCast<FrameNode>(wrapperNode->GetFirstChild());
        bool recreateContent = !IsCustomIconContentTagMatched(iconNode, iconIter->second);
        if (recreateContent) {
            if (iconNode) {
                wrapperNode->RemoveChild(iconNode);
            }
            iconNode = CreateCustomIconContentNode(iconIter->second);
            CHECK_NULL_VOID(iconNode);
            wrapperNode->AddChild(iconNode);
        }
        bool needFadeIn = !wasVisible || recreateContent;
        wrapperNode->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
        UpdateDotIndicatorIconNode(iconNode, itemIndex);
        if (needFadeIn) {
            fadeInList.push_back(wrapperNode);
            pendingFadeInSlots_.emplace_back(visibleIndex);
        } else {
            auto renderContext = wrapperNode->GetRenderContext();
            if (renderContext) {
                renderContext->UpdateOpacity(1.0f);
            }
        }
        indicatorIconIndexes_.emplace_back(visibleIndex);
        activeCustomIconInfos_.push_back({ itemIndex, visibleIndex, wrapperNode->GetId() });
        previousInfoByItem.erase(itemIndex);
    }
    for (const auto& [itemIndex, previousInfo] : previousInfoByItem) {
        auto wrapperNode = FindWrapperNodeById(indicatorWrapperNodeByItem_, previousInfo.wrapperId);
        if (!wrapperNode) {
            continue;
        }
        wrapperNode->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
    }
    if (dotIndicatorModifier_) {
        dotIndicatorModifier_->SetCustomIconIndexes(indicatorIconIndexes_);
    }
    if (overlongDotIndicatorModifier_) {
        overlongDotIndicatorModifier_->SetCustomIconIndexes(indicatorIconIndexes_);
        if (!fadeInList.empty()) {
            ScheduleBatchFadeAnimation(fadeInList);
        }
    }
}

void SwiperIndicatorPattern::ScheduleBatchFadeAnimation(const std::vector<RefPtr<FrameNode>>& fadeInList)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    for (const auto& wrapperNode : fadeInList) {
        auto renderContext = wrapperNode->GetRenderContext();
        if (renderContext) {
            renderContext->UpdateOpacity(0.0f);
        }
    }
    auto fadeInSlots = pendingFadeInSlots_;
    bool hasFadeSlots = !fadeInSlots.empty();
    if (overlongDotIndicatorModifier_) {
        overlongDotIndicatorModifier_->SetIndicatorIconFadeInSlots(fadeInSlots);
        overlongDotIndicatorModifier_->SetIndicatorIconOpacity(hasFadeSlots ? 1.0f : 0.0f);
    }
    pipeline->AddAfterLayoutTask(
        [weakPattern = WeakClaim(this), fadeInList, hasFadeSlots]() {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->PlayBatchFadeAnimation(fadeInList, hasFadeSlots);
        });
}

void SwiperIndicatorPattern::PlayBatchFadeAnimation(
    const std::vector<RefPtr<FrameNode>>& fadeInList, bool hasFadeSlots)
{
    if (fadeInList.empty()) {
        return;
    }
    AnimationOption option;
    option.SetDuration(ICON_FADE_ANIMATION_DURATION);
    option.SetCurve(Curves::SHARP);
    auto finishCallback = [weakPattern = WeakClaim(this)]() {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->overlongDotIndicatorModifier_) {
            pattern->overlongDotIndicatorModifier_->SetIndicatorIconFadeInSlots({});
        }
    };
    AnimationUtils::StartAnimation(option,
        [weakPattern = WeakClaim(this), fadeInList, hasFadeSlots]() {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            for (const auto& wrapperNode : fadeInList) {
                if (!wrapperNode) {
                    continue;
                }
                auto renderContext = wrapperNode->GetRenderContext();
                if (renderContext) {
                    renderContext->UpdateOpacity(1.0f);
                }
            }
            if (pattern->overlongDotIndicatorModifier_ && hasFadeSlots) {
                pattern->overlongDotIndicatorModifier_->SetIndicatorIconOpacity(0.0f);
            }
        },
        finishCallback);
}

void SwiperIndicatorPattern::RefreshCustomIconNodesForOverlongTransition()
{
    if (!NeedCustomDotIndicatorLayout()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    UpdateDotIndicatorIconNodes();
    MarkCustomIconLayoutDirty();
}

void SwiperIndicatorPattern::RegisterIndicatorChangeEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    RefPtr<SwiperPattern> swiperPattern = GetSwiperPattern();
    CHECK_NULL_VOID(swiperPattern);

    auto swiperEventHub = swiperPattern->GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);

    swiperEventHub->SetIndicatorOnChange(
        [weak = AceType::WeakClaim(RawPtr(host)), context = AceType::WeakClaim(this)]() {
            auto indicator = weak.Upgrade();
            CHECK_NULL_VOID(indicator);
            auto pipeline = indicator->GetContext();
            CHECK_NULL_VOID(pipeline);
            auto textContext = context.Upgrade();
            if (textContext && textContext->NeedCustomDotIndicatorLayout()) {
                textContext->RefreshCustomIconNodesForOverlongTransition();
            }
            pipeline->AddAfterLayoutTask([weak, context]() {
                auto indicator = weak.Upgrade();
                CHECK_NULL_VOID(indicator);
                auto textContext = context.Upgrade();
                CHECK_NULL_VOID(textContext);
                if (textContext->GetIndicatorType() == SwiperIndicatorType::DIGIT) {
                    RefPtr<FrameNode> firstTextNode;
                    RefPtr<FrameNode> lastTextNode;
                    auto layoutProperty = indicator->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
                    firstTextNode = DynamicCast<FrameNode>(indicator->GetFirstChild());
                    lastTextNode = DynamicCast<FrameNode>(indicator->GetLastChild());
                    textContext->UpdateTextContent(layoutProperty, firstTextNode, lastTextNode);
                }
                indicator->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
            });
            pipeline->RequestFrame();
        });
    swiperEventHub->SetIndicatorIndexChangeEvent(
        [weak = AceType::WeakClaim(RawPtr(host)), context = AceType::WeakClaim(this)](int32_t index) {
        auto indicator = weak.Upgrade();
        CHECK_NULL_VOID(indicator);
        auto pipeline = indicator->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto pattern = context.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->FireIndicatorIndexChangeEvent(index);
    });
}

void SwiperIndicatorPattern::UpdateFocusable() const
{
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto focusable = swiperPattern->TotalCount() != 0;

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetFocusable(focusable);

    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    auto level = focusable ? "auto" : "no";
    accessibilityProperty->SetAccessibilityLevel(level);
}

void SwiperIndicatorPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto swiperTheme = host->GetTheme<SwiperIndicatorTheme>(true);
    CHECK_NULL_VOID(swiperTheme);
    auto maxDisplayCount = swiperPattern->GetMaxDisplayCount() > 0 ? swiperPattern->GetMaxDisplayCount()
                                                                   : swiperPattern->TotalCount();
    auto paintProperty = host->GetPaintProperty<DotIndicatorPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto itemWidth = paintProperty->GetItemWidthValue(swiperTheme->GetSize()).ConvertToPx();
    auto normalHeight = paintProperty->GetItemHeightValue(swiperTheme->GetSize()).ConvertToPx();
    auto selectedItemWidth = paintProperty->GetSelectedItemWidthValue(swiperTheme->GetSize()).ConvertToPx();
    auto selectedItemHeight = paintProperty->GetSelectedItemHeightValue(swiperTheme->GetSize()).ConvertToPx();
    auto itemHeight = normalHeight > selectedItemHeight ? normalHeight : selectedItemHeight;
    auto isCustomSize = paintProperty->GetIsCustomSizeValue(false);
    auto allPointDiameterSum = isCustomSize ? itemWidth * static_cast<float>(maxDisplayCount - 1) + selectedItemWidth :
        itemWidth * static_cast<float>(maxDisplayCount + 1);
    auto indicatorHeightPadding = swiperTheme->GetIndicatorBgHeight().ConvertToPx();
    Dimension indicatorDotItemSpace =
        paintProperty->GetSpaceValue(swiperTheme->GetIndicatorDotItemSpace());
    auto allPointSpaceSum = static_cast<float>(indicatorDotItemSpace.ConvertToPx()) * (maxDisplayCount - 1);
    auto paddingSide = swiperTheme->GetIndicatorPaddingDot().ConvertToPx();
    auto focusPadding = swiperTheme->GetIndicatorFocusedPadding().ConvertToPx();
    auto width = allPointDiameterSum + allPointSpaceSum + MULTIPLIER * (paddingSide + focusPadding);
    auto height = itemHeight + MULTIPLIER * indicatorHeightPadding + MULTIPLIER * focusPadding;
    auto axis = swiperPattern->GetDirection();
    if (axis == Axis::VERTICAL) {
        std::swap(width, height);
    }
    auto swiperSize = geometryNode->GetFrameSize();
    auto widthSize = swiperSize.Width() + MULTIPLIER * focusPadding;
    auto heightSize = swiperSize.Height() + MULTIPLIER * focusPadding;
    auto widthDiff = (widthSize - width) / MULTIPLIER;
    auto heightDiff = (heightSize - height) / MULTIPLIER;
    paintRect.SetRect({ widthDiff - focusPadding, heightDiff - focusPadding, width, height });
    auto radius = axis == Axis::HORIZONTAL ? height : width;
    auto realRadius = static_cast<float>(radius + focusPadding);
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, realRadius, realRadius);
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS, realRadius, realRadius);
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS, realRadius, realRadius);
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS, realRadius, realRadius);
}

void SwiperIndicatorPattern::InitFocusEvent()
{
    if (focusEventInitialized_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto focusTask = [weak = WeakClaim(this)](FocusReason reason) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleFocusEvent();
    };
    focusHub->SetOnFocusInternal(focusTask);
    auto blurTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleBlurEvent();
    };
    focusHub->SetOnBlurInternal(blurTask);
    auto getInnerPaintRectCallback = [wp = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = wp.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->GetInnerFocusPaintRect(paintRect);
    };
    focusHub->SetInnerFocusPaintRectCallback(getInnerPaintRectCallback);
    focusEventInitialized_ = true;
}

void SwiperIndicatorPattern::HandleFocusEvent()
{
    CHECK_NULL_VOID(dotIndicatorModifier_);
    AddIsFocusActiveUpdateEvent();
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    if (pipeline->GetIsFocusActive()) {
        OnIsFocusActiveUpdate(true);
    }
}

void SwiperIndicatorPattern::HandleBlurEvent()
{
    CHECK_NULL_VOID(dotIndicatorModifier_);
    RemoveIsFocusActiveUpdateEvent();
    OnIsFocusActiveUpdate(false);
}

void SwiperIndicatorPattern::AddIsFocusActiveUpdateEvent()
{
    if (!isFocusActiveUpdateEvent_) {
        isFocusActiveUpdateEvent_ = [weak = WeakClaim(this)](bool isFocusAcitve) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnIsFocusActiveUpdate(isFocusAcitve);
        };
    }
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddIsFocusActiveUpdateEvent(GetHost(), isFocusActiveUpdateEvent_);
}

void SwiperIndicatorPattern::RemoveIsFocusActiveUpdateEvent()
{
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveIsFocusActiveUpdateEvent(GetHost());
}

void SwiperIndicatorPattern::OnIsFocusActiveUpdate(bool isFocusAcitve)
{
    CHECK_NULL_VOID(dotIndicatorModifier_);
    dotIndicatorModifier_->SetIsFocused(isFocusAcitve);
}

bool SwiperIndicatorPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    UpdateFocusable();

    if (swiperIndicatorType_ == SwiperIndicatorType::ARC_DOT) {
        return SetArcIndicatorHotRegion(dirty, config);
    }
    if (config.frameSizeChange && NeedCustomDotIndicatorLayout()) {
        UpdateDotIndicatorIconNodes();
    }
    CHECK_NULL_RETURN(config.frameSizeChange, false);
    return true;
}

void SwiperIndicatorPattern::InitClickEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!clickEvent_);
    auto clickTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleClick(info);
    };
    clickEvent_ = MakeRefPtr<ClickEvent>(std::move(clickTask));
    gestureHub->AddClickEvent(clickEvent_);
}

void SwiperIndicatorPattern::HandleClick(const GestureEvent& info)
{
    if (info.GetSourceDevice() == SourceType::KEYBOARD) {
        return;
    }

    if (info.GetSourceDevice() == SourceType::MOUSE) {
        isClicked_ = true;
        HandleMouseClick(info);
    } else {
        HandleTouchClick(info);
    }
}

void SwiperIndicatorPattern::HandleMouseClick(const GestureEvent& /* info */)
{
    if (isRepeatClicked_) {
        return;
    }
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    if (swiperPattern->GetMaxDisplayCount() > 0) {
        return;
    }
    GetMouseClickIndex();
    CHECK_NULL_VOID(mouseClickIndex_);
    SwipeTo(mouseClickIndex_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SwiperIndicatorPattern::HandleTouchClick(const GestureEvent& info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<DotIndicatorPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto theme = host->GetTheme<SwiperIndicatorTheme>(true);
    CHECK_NULL_VOID(theme);
    auto itemWidth = paintProperty->GetItemWidthValue(theme->GetSize()).ConvertToPx();
    auto selectedItemWidth = paintProperty->GetSelectedItemWidthValue(theme->GetSize()).ConvertToPx();
    if (Negative(itemWidth) || Negative(selectedItemWidth)) {
        itemWidth = theme->GetSize().ConvertToPx();
        selectedItemWidth = theme->GetSize().ConvertToPx();
    }

    auto isRtl = IsHorizontalAndRightToLeft();
    auto currentIndex = GetTouchCurrentIndex();
    auto margin = HandleTouchClickMargin();
    Dimension indicatorDotItemSpace =
        paintProperty->GetSpaceValue(theme->GetIndicatorDotItemSpace());
    auto lengthBeforeCurrentIndex = margin + theme->GetIndicatorPaddingDot().ConvertToPx() +
                                    (indicatorDotItemSpace.ConvertToPx() + itemWidth) * currentIndex;
    auto lengthWithCurrentIndex = lengthBeforeCurrentIndex + selectedItemWidth;
    auto axis = GetDirection();
    auto mainClickOffset = axis == Axis::HORIZONTAL ? info.GetLocalLocation().GetX() : info.GetLocalLocation().GetY();
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    if (swiperPattern->GetMaxDisplayCount() > 0 && overlongDotIndicatorModifier_) {
        auto bounds = overlongDotIndicatorModifier_->GetVisualBounds();
        lengthBeforeCurrentIndex = bounds.first;
        lengthWithCurrentIndex = bounds.second;
    }
    if (mainClickOffset < lengthBeforeCurrentIndex) {
        isRtl ? ShowNext() : ShowPrevious();
    } else if (mainClickOffset > lengthWithCurrentIndex) {
        isRtl ? ShowPrevious() : ShowNext();
    }
}

void SwiperIndicatorPattern::InitHoverMouseEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);

    auto hoverTask = [weak = WeakClaim(this)](bool isHover, HoverInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern && info.GetSourceDevice() != SourceType::TOUCH) {
            pattern->HandleHoverEvent(isHover);
        }
    };

    if (!hoverEvent_) {
        hoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverTask));
        inputHub->AddOnHoverEvent(hoverEvent_);
    }

    auto mouseEvent = [weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleMouseEvent(info);
        }
    };
    if (mouseEvent_) {
        inputHub->RemoveOnMouseEvent(mouseEvent_);
    }
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseEvent));
    inputHub->AddOnMouseEvent(mouseEvent_);
}

void SwiperIndicatorPattern::HandleMouseEvent(const MouseInfo& info)
{
    if (info.GetSourceDevice() == SourceType::TOUCH) {
        return;
    }
    auto mouseOffsetX = static_cast<float>(info.GetLocalLocation().GetX());
    auto mouseOffsetY = static_cast<float>(info.GetLocalLocation().GetY());
    auto mouseAction = info.GetAction();
    if ((mouseAction == MouseAction::PRESS || mouseAction == MouseAction::RELEASE) &&
        isClicked_ && NearEqual(hoverPoint_, PointF(mouseOffsetX, mouseOffsetY))) {
        isRepeatClicked_ = true;
        return;
    }
    isClicked_ = false;
    isRepeatClicked_ = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    PointF oldHoverPoint = hoverPoint_;
    hoverPoint_.SetX(mouseOffsetX);
    hoverPoint_.SetY(mouseOffsetY);

    if (NeedCustomDotIndicatorLayout() && isHover_ && !NearEqual(oldHoverPoint, hoverPoint_)) {
        RefreshCustomIconNodesForOverlongTransition();
    }

    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SwiperIndicatorPattern::HandleHoverEvent(bool isHover)
{
    if (isHover_ == isHover) {
        return;
    }

    isHover_ = isHover;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto swiperNode = GetSwiperNode();
    if (swiperNode) {
        auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
        CHECK_NULL_VOID(swiperPattern);
        auto swiperLayoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
        CHECK_NULL_VOID(swiperLayoutProperty);
        if (swiperLayoutProperty->GetHoverShowValue(false)) {
            swiperPattern->ArrowHover(isHover_, HOVER_INDICATOR);
        }
    }

    RefreshCustomIconNodesForOverlongTransition();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SwiperIndicatorPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (touchEvent_) {
        return;
    }

    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleTouchEvent(info);
        }
    };

    if (touchEvent_) {
        gestureHub->RemoveTouchEvent(touchEvent_);
    }
    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchEvent_);

    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto stopAnimationCb = [weak = WeakClaim(this)](bool ifImmediately) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            if (pattern->dotIndicatorModifier_) {
                pattern->dotIndicatorModifier_->StopAnimation(ifImmediately);
            }

            if (pattern->overlongDotIndicatorModifier_) {
                pattern->overlongDotIndicatorModifier_->StopAnimation(ifImmediately);
            }
        }
    };
    swiperPattern->SetStopIndicatorAnimationCb(stopAnimationCb);

    auto updateOverlongForceStopPageRateCb = [weak = WeakClaim(this)](float forceStopPageRate) {
        auto pattern = weak.Upgrade();
        if (pattern && pattern->overlongDotIndicatorModifier_) {
            pattern->overlongDotIndicatorModifier_->SetForceStopPageRate(forceStopPageRate);
        }
    };
    swiperPattern->SetUpdateOverlongForceStopPageRateCb(updateOverlongForceStopPageRateCb);
}

void SwiperIndicatorPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    if (info.GetTouches().empty()) {
        return;
    }
    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
        HandleDragEnd(0);
        HandleTouchUp();
    }
    if (isPressed_) {
        HandleLongDragUpdate(info.GetTouches().front());
    }
}

void SwiperIndicatorPattern::HandleTouchDown()
{
    isPressed_ = true;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    RefreshCustomIconNodesForOverlongTransition();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SwiperIndicatorPattern::HandleTouchUp()
{
    isPressed_ = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    RefreshCustomIconNodesForOverlongTransition();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SwiperIndicatorPattern::MarkCustomIconLayoutDirty()
{
    if (!NeedCustomDotIndicatorLayout()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

std::pair<int32_t, int32_t> SwiperIndicatorPattern::CalMouseClickIndexStartAndEnd(
    int32_t itemCount, int32_t currentIndex)
{
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_RETURN(swiperPattern, std::make_pair(0, 0));
    int32_t loopCount = SwiperIndicatorUtils::CalcLoopCount(currentIndex, itemCount);
    int32_t start = currentIndex >= 0 ? loopCount * itemCount : -(loopCount + 1) * itemCount;
    int32_t end = currentIndex >= 0 ? (loopCount + 1) * itemCount : -loopCount * itemCount;
    if (IsHorizontalAndRightToLeft()) {
        end = currentIndex >= 0 ? loopCount * itemCount - 1 : -(loopCount + 1) * itemCount - 1;
        start = currentIndex >= 0 ? (loopCount + 1) * itemCount - 1 : -loopCount * itemCount - 1;
        if (!swiperPattern->IsAutoLinear() && swiperPattern->IsSwipeByGroup()) {
            start += (1 - swiperPattern->GetDisplayCount());
        }
    }
    return { start, end };
}

void SwiperIndicatorPattern::GetMouseClickIndex()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto theme = host->GetTheme<SwiperIndicatorTheme>(true);
    CHECK_NULL_VOID(theme);
    auto paintProperty = host->GetPaintProperty<DotIndicatorPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    float itemWidthValue = static_cast<float>(paintProperty->GetItemWidthValue(theme->GetSize()).ConvertToPx());
    float itemHeightValue = static_cast<float>(paintProperty->GetItemHeightValue(theme->GetSize()).ConvertToPx());
    float selectedItemWidthValue =
        static_cast<float>(paintProperty->GetSelectedItemWidthValue(theme->GetSize()).ConvertToPx() * 2);
    paintProperty->GetIsCustomSizeValue(false) ? selectedItemWidthValue *= 0.5f : selectedItemWidthValue;
    // diameter calculation
    double indicatorScale = theme->GetIndicatorScale();
    float itemWidth = itemWidthValue * indicatorScale;
    float itemHeight = itemHeightValue * indicatorScale;
    float selectedItemWidth = selectedItemWidthValue * indicatorScale;
    Dimension indicatorDotItemSpace =
        paintProperty->GetSpaceValue(theme->GetIndicatorDotItemSpace());
    float space = static_cast<float>(indicatorDotItemSpace.ConvertToPx());
    int32_t currentIndex = GetCurrentShownIndex();
    auto [itemCount, step] = CalculateStepAndItemCount();
    auto frameSize = host->GetGeometryNode()->GetFrameSize();
    auto axis = GetDirection();
    float centerX = static_cast<float>((theme->GetIndicatorPaddingDot()).ConvertToPx());
    float centerY = ((axis == Axis::HORIZONTAL ? frameSize.Height() : frameSize.Width()) - itemHeight) * 0.5f;
    PointF hoverPoint = axis == Axis::HORIZONTAL ? hoverPoint_ : PointF(hoverPoint_.GetY(), hoverPoint_.GetX());

    auto [start, end] = CalMouseClickIndexStartAndEnd(itemCount, currentIndex);
    for (int32_t i = start; (start > end ? i > end : i < end); start > end ? i -= step : i += step) {
        if (hoverPoint.GetX() >= centerX && hoverPoint.GetX() <= centerX + itemWidth &&
            hoverPoint.GetY() >= centerY && hoverPoint.GetY() <= centerY + itemHeight) {
            mouseClickIndex_ = i;
            break;
        }
        if (i != currentIndex) {
            centerX += itemWidth + space;
        } else {
            centerX += selectedItemWidth + space;
        }
    }
}

void SwiperIndicatorPattern::UpdateTextContent(const RefPtr<SwiperIndicatorLayoutProperty>& layoutProperty,
    const RefPtr<FrameNode>& firstTextNode, const RefPtr<FrameNode>& lastTextNode)
{
    CHECK_NULL_VOID(layoutProperty);
    CHECK_NULL_VOID(firstTextNode);
    CHECK_NULL_VOID(lastTextNode);
    auto theme = firstTextNode->GetTheme<SwiperIndicatorTheme>(true);
    CHECK_NULL_VOID(theme);
    firstTextNode->SetInternal();
    lastTextNode->SetInternal();
    auto firstTextLayoutProperty = firstTextNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(firstTextLayoutProperty);
    auto selectedFontColor =
        layoutProperty->GetSelectedFontColorValue(theme->GetDigitalIndicatorTextStyle().GetTextColor());
    auto selectedFontSize =
        layoutProperty->GetSelectedFontSizeValue(theme->GetDigitalIndicatorTextStyle().GetFontSize());
    if (!selectedFontSize.IsValid()) {
        selectedFontSize = theme->GetDigitalIndicatorTextStyle().GetFontSize();
    }
    auto selectedFontWeight =
        layoutProperty->GetSelectedFontWeightValue(theme->GetDigitalIndicatorTextStyle().GetFontWeight());
    firstTextLayoutProperty->UpdateTextColor(selectedFontColor);
    firstTextLayoutProperty->UpdateFontSize(selectedFontSize);
    firstTextLayoutProperty->UpdateFontWeight(selectedFontWeight);
    firstTextLayoutProperty->UpdateMaxFontScale(MAX_FONT_SCALE);
    UpdateTextContentSub(layoutProperty, firstTextNode, lastTextNode);
}

int32_t SwiperIndicatorPattern::GetDisplayCurrentIndex() const
{
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_RETURN(swiperNode, 0);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, 0);
    CHECK_NULL_RETURN(swiperPattern->RealTotalCount(), 0);
    auto swiperLayoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, 0);
    auto currentIndex = swiperPattern->GetCurrentFirstIndex() + 1;
    if (currentIndex > swiperPattern->RealTotalCount()) {
        currentIndex = 1;
    } else if (swiperLayoutProperty->HasIndex()) {
        currentIndex = GetInitialIndex() + 1;
        if (currentIndex > swiperPattern->RealTotalCount()) {
            currentIndex = 1;
        }
    }

    return currentIndex;
}

int32_t SwiperIndicatorPattern::GetInitialIndex() const
{
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_RETURN(swiperNode, 0);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, 0);
    auto swiperLayoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, 0);
    auto currentIndex = swiperLayoutProperty->GetIndex().value_or(0);
    if (swiperPattern->IsSwipeByGroup()) {
        currentIndex = SwiperUtils::ComputePageIndex(currentIndex, swiperPattern->GetDisplayCount());
    }

    return currentIndex;
}

void SwiperIndicatorPattern::UpdateTextContentSub(const RefPtr<SwiperIndicatorLayoutProperty>& layoutProperty,
    const RefPtr<FrameNode>& firstTextNode, const RefPtr<FrameNode>& lastTextNode)
{
    CHECK_NULL_VOID(layoutProperty);
    CHECK_NULL_VOID(firstTextNode);
    CHECK_NULL_VOID(lastTextNode);
    auto theme = firstTextNode->GetTheme<SwiperIndicatorTheme>(true);
    CHECK_NULL_VOID(theme);
    auto firstTextLayoutProperty = firstTextNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(firstTextLayoutProperty);
    auto lastTextLayoutProperty = lastTextNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(lastTextLayoutProperty);
    lastTextLayoutProperty->UpdateLayoutDirection(GetNonAutoLayoutDirection());
   
    std::string firstContent = "";
    std::string lastContent = "";
    GetTextContentSub(firstContent, lastContent);
    firstTextLayoutProperty->UpdateContent(firstContent);
    auto fontColor = layoutProperty->GetFontColorValue(theme->GetDigitalIndicatorTextStyle().GetTextColor());
    auto fontSize = layoutProperty->GetFontSizeValue(theme->GetDigitalIndicatorTextStyle().GetFontSize());
    if (!fontSize.IsValid()) {
        fontSize = theme->GetDigitalIndicatorTextStyle().GetFontSize();
    }
    auto fontWeight = layoutProperty->GetFontWeightValue(theme->GetDigitalIndicatorTextStyle().GetFontWeight());
    lastTextLayoutProperty->UpdateTextColor(fontColor);
    lastTextLayoutProperty->UpdateFontSize(fontSize);
    lastTextLayoutProperty->UpdateFontWeight(fontWeight);
    lastTextLayoutProperty->UpdateContent(lastContent);
    lastTextLayoutProperty->UpdateMaxFontScale(MAX_FONT_SCALE);
    firstTextNode->MarkModifyDone();
    firstTextNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    lastTextNode->MarkModifyDone();
    lastTextNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void SwiperIndicatorPattern::HandleDragStart(const GestureEvent& info)
{
    dragStartPoint_ =
        PointF(static_cast<float>(info.GetLocalLocation().GetX()), static_cast<float>(info.GetLocalLocation().GetY()));
    UpadateStartAngle();
}

void SwiperIndicatorPattern::HandleDragEnd(double dragVelocity)
{
    if (!isPressed_) {
        return;
    }
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto gestureState = swiperPattern->GetGestureState();
    swiperPattern->SetTurnPageRate(swiperPattern->IsHorizontalAndRightToLeft() ? -1.0f : 0.0f);
    swiperPattern->SetGroupTurnPageRate(swiperPattern->IsHorizontalAndRightToLeft() ? -1.0f : 0.0f);
    if (swiperPattern->GetMaxDisplayCount() > 0) {
        if (gestureState == GestureState::GESTURE_STATE_FOLLOW_LEFT) {
            swiperPattern->SetGestureState(GestureState::GESTURE_STATE_RELEASE_LEFT);
        } else if (gestureState == GestureState::GESTURE_STATE_FOLLOW_RIGHT) {
            swiperPattern->SetGestureState(GestureState::GESTURE_STATE_RELEASE_RIGHT);
        } else {
            swiperPattern->SetGestureState(GestureState::GESTURE_STATE_NONE);
        }
        CHECK_NULL_VOID(overlongDotIndicatorModifier_);
        overlongDotIndicatorModifier_->SetIsDraggingIndicator(false);
    }
    if (swiperPattern->IsBindIndicator() && swiperPattern->GetMaxDisplayCount() > 0) {
        swiperPattern->SetTouchDownOnOverlong(false);
    }
    auto swiperPaintProperty = swiperPattern->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(swiperPaintProperty);
    auto autoPlay = swiperPaintProperty->GetAutoPlay().value_or(false);
    if (autoPlay) {
        swiperPattern->SetIndicatorLongPress(false);
        swiperPattern->StartAutoPlay();
    }
    isLongPressed_ = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    touchBottomType_ = TouchBottomType::NONE;
    if (NeedCustomDotIndicatorLayout()) {
        UpdateDotIndicatorIconNodes();
    }
    MarkCustomIconLayoutDirty();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SwiperIndicatorPattern::SetIndicatorInteractive(bool isInteractive)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    if (isInteractive) {
        eventHub->SetEnabled(true);
    } else {
        eventHub->SetEnabled(false);
    }
}

bool SwiperIndicatorPattern::CheckIsTouchBottom(const GestureEvent& info)
{
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_RETURN(swiperNode, false);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, false);
    auto currentIndex = swiperPattern->GetCurrentIndex();
    auto childrenSize = swiperPattern->RealTotalCount();
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, false);
    auto displayCount = swiperLayoutProperty->GetDisplayCount().value_or(1);
    auto isLoop = swiperLayoutProperty->GetLoop().value_or(true);
    auto dragPoint =
        PointF(static_cast<float>(info.GetLocalLocation().GetX()), static_cast<float>(info.GetLocalLocation().GetY()));
    auto offset = dragPoint - dragStartPoint_;
    float touchBottomRate = 0.0;
    float touchOffset = 0.0;
    if (swiperLayoutProperty->GetIndicatorTypeValue(SwiperIndicatorType::ARC_DOT) == SwiperIndicatorType::ARC_DOT) {
        auto center = GetCenterPointF();
        float startAngle = GetAngleWithPoint(center, dragStartPoint_);
        float endAngle = GetEndAngle(center, dragPoint, startAngle);
        touchOffset = startAngle - endAngle;
        touchOffset = GetDirection() == Axis::HORIZONTAL ? touchOffset : -touchOffset;
        touchBottomRate = LessOrEqual(std::abs(touchOffset), INDICATOR_TOUCH_BOTTOM_MAX_ANGLE)
                              ? touchOffset / INDICATOR_TOUCH_BOTTOM_MAX_ANGLE : 1;
    } else {
        touchOffset = GetDirection() == Axis::HORIZONTAL ? offset.GetX() : offset.GetY();
        touchBottomRate = LessOrEqual(std::abs(touchOffset), INDICATOR_TOUCH_BOTTOM_MAX_DISTANCE.ConvertToPx())
                              ? touchOffset / INDICATOR_TOUCH_BOTTOM_MAX_DISTANCE.ConvertToPx() : 1;
    }
    swiperPattern->SetTurnPageRate(0);
    swiperPattern->SetGroupTurnPageRate(0.0f);
    swiperPattern->SetTouchBottomRate(std::abs(touchBottomRate));
    TouchBottomType touchBottomType = TouchBottomType::NONE;
    if ((currentIndex <= 0) && !isLoop) {
        if (Negative(info.GetMainDelta()) || NonPositive(touchOffset)) {
            touchBottomType = TouchBottomType::START;
        }
    }
    if ((currentIndex >= childrenSize - displayCount) && !isLoop) {
        if (Positive(info.GetMainDelta()) || NonNegative(touchOffset)) {
            touchBottomType = TouchBottomType::END;
        }
    }
    auto oldTouchBottomType = touchBottomType_;
    touchBottomType_ = touchBottomType;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    if (touchBottomType_ != oldTouchBottomType) {
        MarkCustomIconLayoutDirty();
    }
    auto dirtyFlag = PROPERTY_UPDATE_RENDER;
    if (touchBottomType_ != TouchBottomType::NONE && NeedCustomDotIndicatorLayout()) {
        dirtyFlag |= PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD;
    }
    host->MarkDirtyNode(dirtyFlag);
    return touchBottomType == TouchBottomType::NONE ? false : true;
}

bool SwiperIndicatorPattern::CheckIsTouchBottom(const TouchLocationInfo& info)
{
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_RETURN(swiperNode, false);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, false);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto currentIndex = swiperPattern->GetCurrentIndex();
    auto childrenSize = swiperPattern->RealTotalCount();

    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, false);
    auto displayCount = swiperLayoutProperty->GetDisplayCount().value_or(1);

    auto dragPoint =
        PointF(static_cast<float>(info.GetLocalLocation().GetX()), static_cast<float>(info.GetLocalLocation().GetY()));
    float touchBottomRate = 0.0;
    float touchOffset = 0.0;
    if (swiperLayoutProperty->GetIndicatorTypeValue(SwiperIndicatorType::ARC_DOT) == SwiperIndicatorType::ARC_DOT) {
        auto center = GetCenterPointF();
        float startAngle = GetAngleWithPoint(center, dragStartPoint_);
        float endAngle = GetEndAngle(center, dragPoint, startAngle);
        touchOffset = startAngle - endAngle;
        touchOffset = swiperPattern->GetDirection() == Axis::HORIZONTAL ? touchOffset : -touchOffset;
        touchBottomRate = LessOrEqual(std::abs(touchOffset), INDICATOR_TOUCH_BOTTOM_MAX_ANGLE)
                              ? touchOffset / INDICATOR_TOUCH_BOTTOM_MAX_ANGLE : 1;
    } else {
        auto offset = dragPoint - dragStartPoint_;
        touchOffset = swiperPattern->GetDirection() == Axis::HORIZONTAL ? offset.GetX() : offset.GetY();
        touchBottomRate = LessOrEqual(std::abs(touchOffset), INDICATOR_TOUCH_BOTTOM_MAX_DISTANCE.ConvertToPx())
                              ? touchOffset / INDICATOR_TOUCH_BOTTOM_MAX_DISTANCE.ConvertToPx() : 1;
    }

    swiperPattern->SetTurnPageRate(swiperPattern->IsHorizontalAndRightToLeft() ? -1.0f : 0.0f);
    swiperPattern->SetGroupTurnPageRate(swiperPattern->IsHorizontalAndRightToLeft() ? -1.0f : 0.0f);
    if (swiperPattern->GetMaxDisplayCount() > 0) {
        swiperPattern->SetGestureState(GestureState::GESTURE_STATE_NONE);
    }
    swiperPattern->SetTouchBottomRate(std::abs(touchBottomRate));
    TouchBottomType touchBottomType = TouchBottomType::NONE;

    if (currentIndex <= 0) {
        if (swiperPattern->IsHorizontalAndRightToLeft()) {
            if (Positive(touchOffset)) {
                touchBottomType = TouchBottomType::END;
            }
        } else {
            if (NonPositive(touchOffset)) {
                touchBottomType = TouchBottomType::START;
            }
        }
    }

    if ((!swiperPattern->IsLoop() && currentIndex >= childrenSize - displayCount) || currentIndex == childrenSize - 1) {
        if (swiperPattern->IsHorizontalAndRightToLeft()) {
            if (NonPositive(touchOffset)) {
                touchBottomType = TouchBottomType::START;
            }
        } else {
            if (Positive(touchOffset)) {
                touchBottomType = TouchBottomType::END;
            }
        }
    }
    auto oldTouchBottomType = touchBottomType_;
    touchBottomType_ = touchBottomType;
    if (touchBottomType_ != oldTouchBottomType) {
        MarkCustomIconLayoutDirty();
    }
    auto dirtyFlag = PROPERTY_UPDATE_RENDER;
    if (touchBottomType_ != TouchBottomType::NONE && NeedCustomDotIndicatorLayout()) {
        dirtyFlag |= PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD;
    }
    host->MarkDirtyNode(dirtyFlag);

    return touchBottomType == TouchBottomType::NONE ? false : true;
}

void SwiperIndicatorPattern::InitLongPressEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!longPressEvent_);
    auto longPressCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleLongPress(info);
    };
    longPressEvent_ = MakeRefPtr<LongPressEvent>(std::move(longPressCallback));

    gestureHub->SetLongPressEvent(longPressEvent_, false, false, LONG_PRESS_DELAY);
}

void SwiperIndicatorPattern::HandleLongPress(GestureEvent& info)
{
    HandleTouchDown();
    HandleDragStart(info);

    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto swiperPaintProperty = swiperPattern->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(swiperPaintProperty);
    auto autoPlay = swiperPaintProperty->GetAutoPlay().value_or(false);
    if (swiperPattern->IsBindIndicator() && swiperPattern->GetMaxDisplayCount() > 0) {
        swiperPattern->SetTouchDownOnOverlong(true);
    }
    if (autoPlay) {
        swiperPattern->SetIndicatorLongPress(true);
        swiperPattern->StopTranslateAnimation();
        swiperPattern->StopSpringAnimation();
        swiperPattern->StopAutoPlay();
    }
    isLongPressed_ = true;
}

double SwiperIndicatorPattern::GetIndicatorDragAngleThreshold(bool isMaxAngle)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    auto theme = host->GetTheme<SwiperIndicatorTheme>(true);
    CHECK_NULL_RETURN(theme, 0.0f);
    if (isMaxAngle) {
        return theme->GetIndicatorDragMaxAngle();
    } else {
        return theme->GetIndicatorDragMinAngle();
    }
}

void SwiperIndicatorPattern::HandleLongDragUpdate(const TouchLocationInfo& info)
{
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    if (swiperPattern->IsIndicatorAnimatorRunning()) {
        return;
    }
    float turnPageRate = 0.0;
    float turnPageRateOffset = 0.0;
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto displayCount = swiperLayoutProperty->GetDisplayCount().value_or(1);
    if (swiperPattern->RealTotalCount() <= displayCount) {
        return;
    }
    if (CheckIsTouchBottom(info)) {
        return;
    }
    auto dragPoint =
        PointF(static_cast<float>(info.GetLocalLocation().GetX()), static_cast<float>(info.GetLocalLocation().GetY()));
    if (swiperIndicatorType_ == SwiperIndicatorType::ARC_DOT) {
        auto center = GetCenterPointF();
        float startAngle = GetAngleWithPoint(center, dragStartPoint_);
        float endAngle = GetEndAngle(center, dragPoint, startAngle);
        turnPageRateOffset = startAngle - endAngle;
        if (LessNotEqual(std::abs(turnPageRateOffset), GetIndicatorDragAngleThreshold(false))) {
            return;
        }
        turnPageRateOffset =
            GetDirection() == Axis::HORIZONTAL ? turnPageRateOffset : -turnPageRateOffset;
        turnPageRate = -(turnPageRateOffset / GetIndicatorDragAngleThreshold(true));
    } else {
        auto offset = dragPoint - dragStartPoint_;
        turnPageRateOffset = GetDirection() == Axis::HORIZONTAL ? offset.GetX() : offset.GetY();
        if (LessNotEqual(std::abs(turnPageRateOffset), INDICATOR_DRAG_MIN_DISTANCE.ConvertToPx())) {
            if (NeedCustomDotIndicatorLayout() && swiperPattern->GetMaxDisplayCount() <= 0) {
                swiperPattern->SetTurnPageRate(swiperPattern->IsHorizontalAndRightToLeft() ? -1.0f : 0.0f);
                swiperPattern->SetGroupTurnPageRate(swiperPattern->IsHorizontalAndRightToLeft() ? -1.0f : 0.0f);
            }
            return;
        }
        turnPageRate = -(turnPageRateOffset / INDICATOR_DRAG_MAX_DISTANCE.ConvertToPx());
        if (swiperPattern->IsHorizontalAndRightToLeft()) {
            turnPageRateOffset = -turnPageRateOffset;
        }
    }
    if (!NeedCustomDotIndicatorLayout() || swiperPattern->GetMaxDisplayCount() > 0) {
        swiperPattern->SetTurnPageRate(turnPageRate);
        swiperPattern->SetGroupTurnPageRate(turnPageRate);
        if (swiperPattern->GetMaxDisplayCount() > 0) {
            GestureState gestureState =
                turnPageRate < 0 ? GestureState::GESTURE_STATE_FOLLOW_RIGHT : GestureState::GESTURE_STATE_FOLLOW_LEFT;
            if (NearZero(turnPageRate)) {
                gestureState = GestureState::GESTURE_STATE_NONE;
            }
            swiperPattern->SetGestureState(gestureState);
            auto host = GetHost();
            if (host) {
                host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
            }
        }
    }
    if (std::abs(turnPageRate) >= 1) {
        int32_t step = (!swiperPattern->IsAutoLinear() && swiperPattern->IsSwipeByGroup()
                            ? swiperPattern->GetDisplayCount()
                            : 1);

        if (IsHorizontalAndRightToLeft() && swiperIndicatorType_ == SwiperIndicatorType::ARC_DOT) {
            step = -step;
        }

        if (Positive(turnPageRateOffset)) {
            swiperPattern->SwipeToWithoutAnimation(swiperPattern->GetCurrentIndex() + step);
        }
        if (NonPositive(turnPageRateOffset)) {
            swiperPattern->SwipeToWithoutAnimation(swiperPattern->GetCurrentIndex() - step);
        }
        dragStartPoint_ = dragPoint;
        UpadateStartAngle();
    }
}

float SwiperIndicatorPattern::HandleTouchClickMargin()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    auto paintProperty = host->GetPaintProperty<DotIndicatorPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, 0.0f);
    auto theme = host->GetTheme<SwiperIndicatorTheme>(true);
    CHECK_NULL_RETURN(theme, 0.0f);
    auto itemWidth = paintProperty->GetItemWidthValue(theme->GetSize()).ConvertToPx();
    auto selectedItemWidth = paintProperty->GetSelectedItemWidthValue(theme->GetSize()).ConvertToPx();
    if (Negative(itemWidth) || Negative(selectedItemWidth)) {
        itemWidth = theme->GetSize().ConvertToPx();
        selectedItemWidth = theme->GetSize().ConvertToPx();
    }

    int32_t itemCount = DisplayIndicatorTotalCount();
    auto allPointDiameterSum = itemWidth * static_cast<float>(itemCount - 1) + selectedItemWidth;
    Dimension indicatorDotItemSpace =
        paintProperty->GetSpaceValue(theme->GetIndicatorDotItemSpace());
    auto allPointSpaceSum = static_cast<float>(indicatorDotItemSpace.ConvertToPx() * (itemCount - 1));
    auto indicatorPadding = static_cast<float>(theme->GetIndicatorPaddingDot().ConvertToPx());
    auto contentWidth = indicatorPadding + allPointDiameterSum + allPointSpaceSum + indicatorPadding;
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0f);
    auto frameSize = geometryNode->GetFrameSize();
    auto axis = GetDirection();
    return ((axis == Axis::HORIZONTAL ? frameSize.Width() : frameSize.Height()) - contentWidth) * 0.5f;
}

void SwiperIndicatorPattern::DumpAdvanceInfo()
{
    isHover_ ? DumpLog::GetInstance().AddDesc("isHover:true") : DumpLog::GetInstance().AddDesc("isHover:false");
    isPressed_ ? DumpLog::GetInstance().AddDesc("isPressed:true") : DumpLog::GetInstance().AddDesc("isPressed:false");
    isClicked_ ? DumpLog::GetInstance().AddDesc("isClicked:true") : DumpLog::GetInstance().AddDesc("isClicked:false");
    isRepeatClicked_ ? DumpLog::GetInstance().AddDesc("isRepeatClicked:true")
                     : DumpLog::GetInstance().AddDesc("isRepeatClicked:false");
    switch (GetIndicatorType()) {
        case SwiperIndicatorType::DOT: {
            DumpLog::GetInstance().AddDesc("SwiperIndicatorType:DOT");
            break;
        }
        case SwiperIndicatorType::DIGIT: {
            DumpLog::GetInstance().AddDesc("SwiperIndicatorType:DIGIT");
            break;
        }
        case SwiperIndicatorType::ARC_DOT: {
            DumpLog::GetInstance().AddDesc("SwiperIndicatorType:ARC_DOT");
            break;
        }
        default: {
            break;
        }
    }
}

OffsetF SwiperIndicatorPattern::CalculateAngleOffset(float centerX, float centerY, float radius, double angle)
{
    double radians = 0.0;
    OffsetF angleOffset;
    if (GreatOrEqual(angle, 0.0) && LessNotEqual(angle, QUARTER_CIRCLE_ANGLE)) {
        radians = std::abs(angle) * ACE_PI / HALF_CIRCLE_ANGLE;
        angleOffset.SetX(centerX + cos(radians) * radius);
        angleOffset.SetY(centerY + sin(radians) * radius);
    } else if (GreatOrEqual(angle, QUARTER_CIRCLE_ANGLE) && LessNotEqual(angle, HALF_CIRCLE_ANGLE)) {
        radians = std::abs(HALF_CIRCLE_ANGLE - angle) * ACE_PI / HALF_CIRCLE_ANGLE;
        angleOffset.SetX(centerX - cos(radians) * radius);
        angleOffset.SetY(centerY + sin(radians) * radius);
    } else if (GreatOrEqual(angle, HALF_CIRCLE_ANGLE) && LessNotEqual(angle, THREE_QUARTER_CIRCLE_ANGLE)) {
        radians = std::abs(angle - HALF_CIRCLE_ANGLE) * ACE_PI / HALF_CIRCLE_ANGLE;
        angleOffset.SetX(centerX - cos(radians) * radius);
        angleOffset.SetY(centerY - sin(radians) * radius);
    } else if (GreatOrEqual(angle, THREE_QUARTER_CIRCLE_ANGLE) && LessNotEqual(angle, FULL_CIRCLE_ANGLE)) {
        radians = std::abs(FULL_CIRCLE_ANGLE - angle) * ACE_PI / HALF_CIRCLE_ANGLE;
        angleOffset.SetX(centerX + cos(radians) * radius);
        angleOffset.SetY(centerY - sin(radians) * radius);
    }
    return angleOffset;
}

OffsetF SwiperIndicatorPattern::CalculateRectLayout(
    double angle, float radius, OffsetF angleOffset, Dimension& width, Dimension& height)
{
    OffsetF hotRegionOffset = angleOffset;
    Dimension oneAngleLength = Dimension(sin(ACE_PI / HALF_CIRCLE_ANGLE) * radius, DimensionUnit::PX);
    // The number 0.5 represents equal division
    if ((GreatOrEqual(angle, QUARTER_CIRCLE_ANGLE * 0.5) &&
            LessNotEqual(angle, QUARTER_CIRCLE_ANGLE * 0.5 + QUARTER_CIRCLE_ANGLE)) ||
        (GreatOrEqual(angle, QUARTER_CIRCLE_ANGLE * 0.5 + HALF_CIRCLE_ANGLE) &&
            LessNotEqual(angle, QUARTER_CIRCLE_ANGLE * 0.5 + THREE_QUARTER_CIRCLE_ANGLE))) {
        hotRegionOffset.SetY(angleOffset.GetY() - CONTAINER_BORDER_WIDTH.ConvertToPx() * 0.5);
        width = oneAngleLength;
        height = CONTAINER_BORDER_WIDTH;
    } else {
        hotRegionOffset.SetX(angleOffset.GetX() - CONTAINER_BORDER_WIDTH.ConvertToPx() * 0.5);
        width = CONTAINER_BORDER_WIDTH;
        height = oneAngleLength;
    }
    return hotRegionOffset;
}

void SwiperIndicatorPattern::ResetDotModifier()
{
    if (!dotIndicatorModifier_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto rsRenderContext = host->GetRenderContext();
    CHECK_NULL_VOID(rsRenderContext);
    rsRenderContext->RemoveContentModifier(dotIndicatorModifier_);
    dotIndicatorModifier_ = nullptr;
}

void SwiperIndicatorPattern::ResetOverlongModifier()
{
    if (!overlongDotIndicatorModifier_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto rsRenderContext = host->GetRenderContext();
    CHECK_NULL_VOID(rsRenderContext);
    rsRenderContext->RemoveContentModifier(overlongDotIndicatorModifier_);
    overlongDotIndicatorModifier_ = nullptr;
}

RefPtr<OverlengthDotIndicatorPaintMethod> SwiperIndicatorPattern::CreateOverlongDotIndicatorPaintMethod(
    RefPtr<SwiperPattern> swiperPattern)
{
    ResetDotModifier();

    if (!overlongDotIndicatorModifier_) {
        auto host = GetHost();
        int32_t id = TokenThemeStorage::INVALID_THEME_SCOPE_ID;
        if (host && host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
            id = host->GetThemeScopeId();
        }
        overlongDotIndicatorModifier_ = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>(id);
    }

    overlongDotIndicatorModifier_->SetAnimationDuration(swiperPattern->GetDuration());
    overlongDotIndicatorModifier_->SetLongPointHeadCurve(
        swiperPattern->GetIndicatorHeadCurve(), swiperPattern->GetMotionVelocity());
    overlongDotIndicatorModifier_->SetUserSetSwiperCurve(swiperPattern->GetCurve());
    overlongDotIndicatorModifier_->SetIsBindIndicator(swiperPattern->IsBindIndicator());
    overlongDotIndicatorModifier_->SetCustomIconIndexes(GetIndicatorIconIndexes());
    overlongDotIndicatorModifier_->SetUseSystemMaterial(UseSystemMaterialForBindIndicator());

    auto swiperLayoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, nullptr);
    auto overlongPaintMethod = MakeRefPtr<OverlengthDotIndicatorPaintMethod>(overlongDotIndicatorModifier_);
    auto paintMethodTemp = DynamicCast<DotIndicatorPaintMethod>(overlongPaintMethod);
    SetDotIndicatorPaintMethodInfo(swiperPattern, paintMethodTemp, swiperLayoutProperty);
    UpdateOverlongPaintMethod(swiperPattern, overlongPaintMethod);

    return overlongPaintMethod;
}

RefPtr<DotIndicatorPaintMethod> SwiperIndicatorPattern::CreateDotIndicatorPaintMethod(
    RefPtr<SwiperPattern> swiperPattern)
{
    ResetOverlongModifier();

    if (!dotIndicatorModifier_) {
        auto host = GetHost();
        int32_t id = TokenThemeStorage::INVALID_THEME_SCOPE_ID;
        if (host && host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
            id = host->GetThemeScopeId();
        }
        dotIndicatorModifier_ = AceType::MakeRefPtr<DotIndicatorModifier>(id);
    }

    dotIndicatorModifier_->SetAnimationDuration(swiperPattern->GetDuration());
    dotIndicatorModifier_->SetLongPointHeadCurve(
        swiperPattern->GetIndicatorHeadCurve(), swiperPattern->GetMotionVelocity());
    dotIndicatorModifier_->SetUserSetSwiperCurve(swiperPattern->GetCurve());
    dotIndicatorModifier_->SetUseSystemMaterial(UseSystemMaterialForBindIndicator());
    auto swiperLayoutProperty = swiperPattern->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, nullptr);
    auto paintMethod = MakeRefPtr<DotIndicatorPaintMethod>(dotIndicatorModifier_);
    SetDotIndicatorPaintMethodInfo(swiperPattern, paintMethod, swiperLayoutProperty);

    dotIndicatorModifier_->SetBoundsRect(CalcBoundsRect());

    return paintMethod;
}

RectF SwiperIndicatorPattern::CalcBoundsRect() const
{
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_RETURN(swiperNode, RectF());
    auto geometryNode = swiperNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, RectF());
    auto host = GetHost();
    CHECK_NULL_RETURN(host, RectF());
    auto indicatorGeometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(indicatorGeometryNode, RectF());
    auto boundsValue = (geometryNode->GetFrameSize().Width() - indicatorGeometryNode->GetFrameSize().Width()) * 0.5f;
    auto boundsRectOriginX = -boundsValue;
    auto boundsRectOriginY = 0.0f;
    auto boundsRectWidth = geometryNode->GetFrameSize().Width();
    auto boundsRectHeight = indicatorGeometryNode->GetFrameSize().Height();
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, RectF());
    if (GetDirection() == Axis::VERTICAL) {
        boundsValue = (geometryNode->GetFrameSize().Height() - indicatorGeometryNode->GetFrameSize().Height()) * 0.5f;
        boundsRectOriginX = 0.0f;
        boundsRectOriginY = -boundsValue;
        boundsRectWidth = indicatorGeometryNode->GetFrameSize().Width();
        boundsRectHeight = geometryNode->GetFrameSize().Height();
    }
    RectF boundsRect(boundsRectOriginX, boundsRectOriginY, boundsRectWidth, boundsRectHeight);

    return boundsRect;
}

void SwiperIndicatorPattern::CheckDragAndUpdate(
    const RefPtr<SwiperPattern>& swiperPattern, int32_t animationStartIndex, int32_t animationEndIndex)
{
    CHECK_NULL_VOID(swiperPattern);

    if (!swiperPattern->IsTouchDownOnOverlong()) {
        return;
    }

    if (NeedCustomDotIndicatorLayout() && overlongDotIndicatorModifier_ &&
        overlongDotIndicatorModifier_->IsDraggingIndicator()) {
        return;
    }

    auto bottomTouchLoop = swiperPattern->GetTouchBottomTypeLoop();
    auto turnPageRateAbs = std::abs(swiperPattern->GetTurnPageRate());
    auto totalCount = swiperPattern->RealTotalCount();
    auto loopDrag = (animationStartIndex == 0 && animationEndIndex == totalCount - 1 && turnPageRateAbs < HALF_FLOAT &&
                        turnPageRateAbs > 0.0f) ||
                    (animationStartIndex == animationEndIndex && animationEndIndex == totalCount - 1 &&
                        turnPageRateAbs > HALF_FLOAT);
    auto nonLoopDrag = bottomTouchLoop == TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE &&
                       ((gestureState_ == GestureState::GESTURE_STATE_FOLLOW_RIGHT && turnPageRateAbs > HALF_FLOAT) ||
                           (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT && turnPageRateAbs < HALF_FLOAT &&
                               turnPageRateAbs > 0.0f));

    if (loopDrag || nonLoopDrag) {
        overlongDotIndicatorModifier_->UpdateCurrentStatus();
        if (NeedCustomDotIndicatorLayout()) {
            UpdateDotIndicatorIconNodes();
            MarkCustomIconLayoutDirty();
        }
    }
}

void SwiperIndicatorPattern::UpdateOverlongPaintMethod(
    const RefPtr<SwiperPattern>& swiperPattern, RefPtr<OverlengthDotIndicatorPaintMethod>& overlongPaintMethod)
{
    auto animationStartIndex = swiperPattern->GetLoopIndex(swiperPattern->GetCurrentIndex());
    auto animationEndIndex = swiperPattern->GetLoopIndex(swiperPattern->GetCurrentFirstIndex());

    auto paintMethodTemp = DynamicCast<DotIndicatorPaintMethod>(overlongPaintMethod);
    bool keepStatus = false;
    bool isSwiperTouchDown = false;
    if (isInFast_ && isInFast_.value()) {
        UpdateOverlongPaintMethodWhenFast(paintMethodTemp, animationStartIndex, animationEndIndex);
    } else {
        if (keepGestureState_) {
            paintMethodTemp->SetGestureState(keepGestureState_.value());
        }
        UpdateOverlongPaintMethodWhenNormal(paintMethodTemp, animationStartIndex, animationEndIndex);
        GetStatusForOverlongPaintMethodWhenNormal(swiperPattern, animationStartIndex, animationEndIndex,
            keepStatus, isSwiperTouchDown);
        if (keepGestureState_) {
            keepStatus = false;
            isSwiperTouchDown = false;
        }
        keepGestureState_.reset();
    }

    CheckDragAndUpdate(swiperPattern, animationStartIndex, animationEndIndex);

    if (!swiperPattern->IsLoop() && animationStartIndex == 0 &&
        gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT) {
        overlongPaintMethod->SetTouchBottomTypeLoop(TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT);
    }

    overlongPaintMethod->SetMaxDisplayCount(swiperPattern->GetMaxDisplayCount());
    overlongPaintMethod->SetKeepStatus(keepStatus);
    overlongPaintMethod->SetAnimationStartIndex(animationStartIndex);
    overlongPaintMethod->SetAnimationEndIndex(animationEndIndex);
    overlongPaintMethod->SetIsBindIndicator(swiperPattern->IsBindIndicator());
    overlongDotIndicatorModifier_->SetIsSwiperTouchDown(isSwiperTouchDown);
    overlongDotIndicatorModifier_->SetBoundsRect(CalcBoundsRect());
    overlongDotIndicatorModifier_->SetIsAutoPlay(swiperPattern->IsAutoPlay());
    changeIndexWithAnimation_.reset();
    jumpIndex_.reset();
    startIndex_.reset();
    isInFast_.reset();
}

void SwiperIndicatorPattern::UpdateOverlongPaintMethodWhenFast(
    const RefPtr<DotIndicatorPaintMethod>& paintMethodTemp,
    int32_t& animationStartIndex, int32_t& animationEndIndex)
{
    animationEndIndex = animationStartIndex;
    animationStartIndex = startIndex_ ? startIndex_.value() : overlongDotIndicatorModifier_->GetAnimationEndIndex();
    keepGestureState_ = paintMethodTemp->GetGestureState();
    paintMethodTemp->SetGestureState(GestureState::GESTURE_STATE_NONE);
    overlongDotIndicatorModifier_->StopAnimation(true);
}

void SwiperIndicatorPattern::UpdateOverlongPaintMethodWhenNormal(
    const RefPtr<DotIndicatorPaintMethod>& paintMethodTemp,
    int32_t& animationStartIndex, int32_t& animationEndIndex)
{
    if (changeIndexWithAnimation_ && !changeIndexWithAnimation_.value()) {
        animationStartIndex =
            startIndex_ ? startIndex_.value() : overlongDotIndicatorModifier_->GetAnimationEndIndex();
        paintMethodTemp->SetGestureState(GestureState::GESTURE_STATE_NONE);
    }

    if (jumpIndex_) {
        paintMethodTemp->SetGestureState(GestureState::GESTURE_STATE_NONE);

        if (!changeIndexWithAnimation_) {
            overlongDotIndicatorModifier_->StopAnimation(true);
            overlongDotIndicatorModifier_->SetCurrentOverlongType(OverlongType::NONE);
        }
    }
}

void SwiperIndicatorPattern::GetStatusForOverlongPaintMethodWhenNormal(const RefPtr<SwiperPattern>& swiperPattern,
    const int32_t& animationStartIndex, const int32_t& animationEndIndex,
    bool& keepStatus, bool& isSwiperTouchDown) const
{
    isSwiperTouchDown = swiperPattern->IsTouchDownOnOverlong();
    auto isSwiperAnimationRunning =
        swiperPattern->IsPropertyAnimationRunning() || swiperPattern->IsTranslateAnimationRunning();
    keepStatus = !isSwiperTouchDown && !isSwiperAnimationRunning && animationStartIndex != animationEndIndex &&
                 !changeIndexWithAnimation_;
    if (!changeIndexWithAnimation_ && gestureState_ == GestureState::GESTURE_STATE_NONE) {
        keepStatus = true;
    }
}

void SwiperIndicatorPattern::ShowPrevious()
{
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_VOID(swiperPattern);
    swiperPattern->ShowPrevious();
}

void SwiperIndicatorPattern::ShowNext()
{
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_VOID(swiperPattern);
    swiperPattern->ShowNext();
}

void SwiperIndicatorPattern::ChangeIndex(int32_t index, bool useAnimation)
{
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_VOID(swiperPattern);
    if (NeedCustomDotIndicatorLayout()) {
        useAnimation = false;
    }
    swiperPattern->ChangeIndex(index, useAnimation);
}

int32_t SwiperIndicatorPattern::GetTouchCurrentIndex() const
{
    return GetCurrentIndex();
}

int32_t SwiperIndicatorPattern::GetCurrentIndex() const
{
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_RETURN(swiperPattern, 0);
    auto currentIndex = swiperPattern->GetCurrentIndex();
    auto isRtl = swiperPattern->IsHorizontalAndRightToLeft();
    auto indicatorCount = swiperPattern->DisplayIndicatorTotalCount();
    auto displayCount = swiperPattern->GetDisplayCount();

    if (!swiperPattern->IsAutoLinear() && swiperPattern->IsSwipeByGroup() && displayCount != 0) {
        currentIndex /= displayCount;
    }

    if (isRtl) {
        currentIndex = indicatorCount - 1 - currentIndex;
    }
    return currentIndex;
}

int32_t SwiperIndicatorPattern::GetCurrentShownIndex() const
{
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_RETURN(swiperPattern, 0);
    return swiperPattern->GetCurrentShownIndex();
}

int32_t SwiperIndicatorPattern::RealTotalCount() const
{
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_RETURN(swiperPattern, 0);
    return swiperPattern->RealTotalCount();
}

int32_t SwiperIndicatorPattern::DisplayIndicatorTotalCount() const
{
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_RETURN(swiperPattern, 0);
    return swiperPattern->DisplayIndicatorTotalCount();
}

Axis SwiperIndicatorPattern::GetDirection() const
{
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_RETURN(swiperPattern, Axis::HORIZONTAL);
    return swiperPattern->GetDirection();
}

bool SwiperIndicatorPattern::IsHorizontalAndRightToLeft() const
{
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_RETURN(swiperPattern, false);
    return swiperPattern->IsHorizontalAndRightToLeft();
}

TextDirection SwiperIndicatorPattern::GetNonAutoLayoutDirection() const
{
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_RETURN(swiperPattern, TextDirection::LTR);
    return swiperPattern->GetNonAutoLayoutDirection();
}

bool SwiperIndicatorPattern::IsLoop() const
{
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_RETURN(swiperPattern, true);
    return swiperPattern->IsLoop();
}

void SwiperIndicatorPattern::GetTextContentSub(std::string& firstContent, std::string& lastContent) const
{
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_VOID(swiperPattern);
    auto currentIndex = GetDisplayCurrentIndex();
    bool isRtl = swiperPattern->GetNonAutoLayoutDirection() == TextDirection::RTL;
    firstContent = isRtl ? std::to_string(swiperPattern->RealTotalCount()) : std::to_string(currentIndex);
    lastContent = isRtl ? std::to_string(currentIndex) + "/" : "/" + std::to_string(swiperPattern->RealTotalCount());
}

void SwiperIndicatorPattern::SwipeTo(std::optional<int32_t> mouseClickIndex)
{
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    if (swiperPattern->IsSwipeByGroup()) {
        auto clickPageIndex = SwiperUtils::ComputePageIndex(mouseClickIndex.value(), swiperPattern->GetDisplayCount());
        mouseClickIndex_ = clickPageIndex;
    }
    swiperPattern->SwipeTo(mouseClickIndex_.value());
}

std::pair<int32_t, int32_t> SwiperIndicatorPattern::CalculateStepAndItemCountDefault() const
{
    int32_t itemCount = RealTotalCount();
    int32_t step = 1;
    return { itemCount, step };
}

std::pair<int32_t, int32_t> SwiperIndicatorPattern::CalculateStepAndItemCount() const
{
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_RETURN(swiperPattern, CalculateStepAndItemCountDefault());
    return swiperPattern->CalculateStepAndItemCount();
}

bool SwiperIndicatorPattern::GetDotCurrentOffset(OffsetF& offset, float indicatorWidth, float indicatorHeight)
{
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, true);
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_RETURN(swiperNode, true);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, true);
    auto indicatorlayoutProperty = frameNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_RETURN(indicatorlayoutProperty, true);

    offset = SwiperIndicatorUtils::CalcIndicatrFrameOffSet(
        swiperLayoutProperty, indicatorlayoutProperty, indicatorWidth, indicatorHeight);
    return true;
}

int32_t SwiperIndicatorPattern::GetLoopIndex(int32_t originalIndex) const
{
    auto realTotalCount = RealTotalCount();
    if (realTotalCount <= 0) {
        return originalIndex;
    }
    auto loopIndex = originalIndex;
    while (loopIndex < 0) {
        loopIndex = loopIndex + realTotalCount;
    }
    if (realTotalCount != 0) {
        loopIndex %= realTotalCount;
    }
    return loopIndex;
}

void SwiperIndicatorPattern::IndicatorOnChange()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddAfterLayoutTask([weak = AceType::WeakClaim(RawPtr(host)), context = AceType::WeakClaim(this)]() {
        auto indicator = weak.Upgrade();
        CHECK_NULL_VOID(indicator);
        auto textContext = context.Upgrade();
        CHECK_NULL_VOID(textContext);
        if (textContext->GetIndicatorType() == SwiperIndicatorType::DIGIT) {
            RefPtr<FrameNode> firstTextNode;
            RefPtr<FrameNode> lastTextNode;
            auto layoutProperty = indicator->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
            firstTextNode = DynamicCast<FrameNode>(indicator->GetFirstChild());
            lastTextNode = DynamicCast<FrameNode>(indicator->GetLastChild());
            textContext->UpdateTextContent(layoutProperty, firstTextNode, lastTextNode);
        }
        indicator->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    });
    pipeline->RequestFrame();
}

bool SwiperIndicatorPattern::GetDigitFrameSize(RefPtr<GeometryNode>& geoNode, SizeF& frameSize) const
{
    CHECK_NULL_RETURN(geoNode, false);
    frameSize = geoNode->GetMarginFrameSize();
    return true;
}

void SwiperIndicatorPattern::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("isHover", isHover_);
    json->Put("isPressed", isPressed_);
    json->Put("isClicked", isClicked_);
    json->Put("isRepeatClicked", isRepeatClicked_);
    switch (GetIndicatorType()) {
        case SwiperIndicatorType::DOT: {
            json->Put("SwiperIndicatorType", "DOT");
            break;
        }
        case SwiperIndicatorType::DIGIT: {
            json->Put("SwiperIndicatorType", "DIGIT");
            break;
        }
        default: {
            break;
        }
    }
}

bool SwiperIndicatorPattern::OnThemeScopeUpdate(int32_t themeScopeId)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    if (!host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
        return false;
    }

    auto swiperTheme = host->GetTheme<SwiperIndicatorTheme>(true);
    CHECK_NULL_RETURN(swiperTheme, false);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    focusHub->SetPaintColor(swiperTheme->GetFocusedColor());
    return false;
}
} // namespace OHOS::Ace::NG
