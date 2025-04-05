/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

#include "base/geometry/axis.h"
#include "base/geometry/point.h"
#include "base/log/dump_log.h"
#include "base/perfmonitor/perf_constants.h"
#include "base/perfmonitor/perf_monitor.h"
#include "base/ressched/ressched_report.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/common/recorder/event_definition.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/manager/select_overlay/select_overlay_scroll_notifier.h"
#include "core/components_ng/pattern/scroll/effect/scroll_fade_effect.h"
#include "core/components_ng/pattern/scroll/scroll_event_hub.h"
#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"
#include "core/components_ng/pattern/scrollable/scrollable.h"
#include "core/components_ng/pattern/scrollable/scrollable_event_hub.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/syntax/for_each_node.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_node.h"
#include "core/pipeline_ng/pipeline_context.h"

#ifdef ARKUI_CIRCLE_FEATURE
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar_overlay_modifier.h"
#endif // ARKUI_CIRCLE_FEATURE

namespace OHOS::Ace::NG {
namespace {
constexpr Color SELECT_FILL_COLOR = Color(0x1A000000);
constexpr Color SELECT_STROKE_COLOR = Color(0x33FFFFFF);
constexpr float CUSTOM_ANIMATION_DURATION = 1000.0;
constexpr uint32_t MILLOS_PER_NANO_SECONDS = 1000 * 1000 * 1000;
constexpr uint64_t MIN_DIFF_VSYNC = 1000 * 1000; // min is 1ms
constexpr uint32_t MAX_VSYNC_DIFF_TIME = 100 * 1000 * 1000; //max 100ms
constexpr uint32_t DEFAULT_VSYNC_DIFF_TIME = 16 * 1000 * 1000; // default is 16 ms
constexpr uint32_t EVENTS_FIRED_INFO_COUNT = 50;
constexpr uint32_t SCROLLABLE_FRAME_INFO_COUNT = 50;
constexpr Dimension LIST_FADINGEDGE = 32.0_vp;
constexpr double ARC_INITWIDTH_VAL = 4.0;
#ifdef ARKUI_CIRCLE_FEATURE
constexpr double ARC_INITWIDTH_HALF_VAL = 2.0;
#endif
const std::string SCROLLABLE_DRAG_SCENE = "scrollable_drag_scene";
const std::string SCROLL_BAR_DRAG_SCENE = "scrollBar_drag_scene";
const std::string SCROLLABLE_MOTION_SCENE = "scrollable_motion_scene";
const std::string SCROLLABLE_MULTI_TASK_SCENE = "scrollable_multi_task_scene";
const std::string SCROLL_IN_HOTZONE_SCENE = "scroll_in_hotzone_scene";
const std::string CUSTOM_SCROLL_BAR_SCENE = "custom_scroll_bar_scene";
} // namespace
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

ScrollablePattern::ScrollablePattern() = default;

ScrollablePattern::ScrollablePattern(EdgeEffect edgeEffect, bool alwaysEnabled)
    : edgeEffect_(edgeEffect), edgeEffectAlwaysEnabled_(alwaysEnabled)
{}

ScrollablePattern::~ScrollablePattern()
{
    if (AnimateRunning()) {
        PerfMonitor::GetPerfMonitor()->End(PerfConstants::SCROLLER_ANIMATION, false);
        auto scrollable = GetScrollable();
        if (scrollable) {
            auto nodeId = scrollable->GetNodeId();
            auto nodeTag = scrollable->GetNodeTag();
            AceAsyncTraceEnd(nodeId,
                (SCROLLER_FIX_VELOCITY_ANIMATION + std::to_string(nodeId) + std::string(" ") + nodeTag).c_str());
            AceAsyncTraceEndCommercial(
                nodeId, (TRAILING_ANIMATION + std::to_string(nodeId) + std::string(" ") + nodeTag).c_str());
        }
    }
    if (scrollBarProxy_) {
        scrollBarProxy_->UnRegisterNestScrollableNode(AceType::WeakClaim(this));
    }
}

RefPtr<PaintProperty> ScrollablePattern::CreatePaintProperty()
{
    auto defaultDisplayMode = GetDefaultScrollBarDisplayMode();
    auto property = MakeRefPtr<ScrollablePaintProperty>();
    property->UpdateScrollBarMode(defaultDisplayMode);
    return property;
}

void ScrollablePattern::CreateAnalyzerOverlay(const RefPtr<FrameNode> node)
{
    auto builderFunc = []() -> RefPtr<UINode> {
        auto uiNode = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        return uiNode;
    };
    auto overlayNode = AceType::DynamicCast<FrameNode>(builderFunc());
    CHECK_NULL_VOID(overlayNode);
    node->SetOverlayNode(overlayNode);
    overlayNode->SetParent(AceType::WeakClaim(AceType::RawPtr(node)));
    overlayNode->SetActive(true);
    overlayNode->SetHitTestMode(HitTestMode::HTMTRANSPARENT);
    auto overlayProperty = AceType::DynamicCast<LayoutProperty>(overlayNode->GetLayoutProperty());
    CHECK_NULL_VOID(overlayProperty);
    overlayProperty->SetIsOverlayNode(true);
    overlayProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    overlayProperty->UpdateAlignment(Alignment::TOP_LEFT);
    auto overlayOffsetX = std::make_optional<Dimension>(Dimension::FromString("0px"));
    auto overlayOffsetY = std::make_optional<Dimension>(Dimension::FromString("0px"));
    overlayProperty->SetOverlayOffset(overlayOffsetX, overlayOffsetY);
    auto focusHub = overlayNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetFocusable(false);
    overlayNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ScrollablePattern::UpdateFadingEdge(const RefPtr<ScrollablePaintMethod>& paint)
{
    if (NearZero(GetMainContentSize())) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto overlayNode = host->GetOverlayNode();
    CHECK_NULL_VOID(overlayNode);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameRect();
    auto overlayRenderContext = overlayNode->GetRenderContext();
    CHECK_NULL_VOID(overlayRenderContext);
    auto fadeFrameSize = GetAxis() == Axis::HORIZONTAL ? frameSize.Width() : frameSize.Height();
    if (fadeFrameSize == 0) {
        return;
    }
    auto paintProperty = GetPaintProperty<ScrollablePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    bool defaultFadingEdge = paintProperty->GetDefaultFadingEdge().value_or(false);
    bool hasFadingEdge = paintProperty->GetFadingEdge().value_or(defaultFadingEdge);
    if (!hasFadingEdge) {
        paint->SetOverlayRenderContext(overlayRenderContext);
        paint->SetFadingInfo(false, false, prevHasFadingEdge_);
        prevHasFadingEdge_ = hasFadingEdge;
        return;
    }
    prevHasFadingEdge_ = hasFadingEdge;
    auto isFadingTop = !IsAtTop();
    auto isFadingBottom = IsFadingBottom();
    float paddingBeforeContent = 0.0f;
    float paddingAfterContent = 0.0f;
    auto& padding = geometryNode->GetPadding();
    if (padding) {
        paddingBeforeContent = GetAxis() == Axis::HORIZONTAL ? *padding->left : *padding->top;
        paddingAfterContent = GetAxis() == Axis::HORIZONTAL ? *padding->right : *padding->bottom;
    }
    startPercent_ = (paddingBeforeContent) / fadeFrameSize;
    endPercent_ = (fadeFrameSize - paddingAfterContent) / fadeFrameSize;
    paint->SetOverlayRenderContext(overlayRenderContext);
    UpdateFadeInfo(isFadingTop, isFadingBottom, fadeFrameSize, paint);
}

void ScrollablePattern::UpdateFadeInfo(
    bool isFadingTop, bool isFadingBottom, float fadeFrameSize, const RefPtr<ScrollablePaintMethod>& paint)
{
    if (fadeFrameSize == 0) {
        return;
    }
    float percentFading = 0.0f;
    auto paintProperty = GetPaintProperty<ScrollablePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto fadingEdgeLength = paintProperty->GetFadingEdgeLength().value_or(LIST_FADINGEDGE);
    if (fadingEdgeLength.Unit() == DimensionUnit::PERCENT) {
        percentFading = fadingEdgeLength.Value() / 100.0f; // One hundred percent
    } else {
        percentFading = fadingEdgeLength.ConvertToPx() / fadeFrameSize;
    }
    paint->SetFadingInfo(isFadingTop, isFadingBottom, true, (percentFading > 0.5f ? 0.5f : percentFading),
        startPercent_, endPercent_); // 0.5: Half
}

void ScrollablePattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    if (edgeEffect_ == EdgeEffect::SPRING) {
        json->PutExtAttr("edgeEffect", "EdgeEffect.Spring", filter);
    } else if (edgeEffect_ == EdgeEffect::FADE) {
        json->PutExtAttr("edgeEffect", "EdgeEffect.Fade", filter);
    } else {
        json->PutExtAttr("edgeEffect", "EdgeEffect.None", filter);
    }
    json->PutExtAttr("flingSpeedLimit",
        Dimension(maxFlingVelocity_, DimensionUnit::VP).ToString().c_str(), filter);
    auto JsonEdgeEffectOptions = JsonUtil::Create(true);
    JsonEdgeEffectOptions->Put("alwaysEnabled", GetAlwaysEnabled());
    if (effectEdge_ == EffectEdge::START) {
        JsonEdgeEffectOptions->Put("effectEdge", "EffectEdge.Start");
    } else if (effectEdge_ == EffectEdge::END) {
        JsonEdgeEffectOptions->Put("effectEdge", "EffectEdge.End");
    } else {
        JsonEdgeEffectOptions->Put("effectEdge", "EffectEdge.All");
    }
    json->PutExtAttr("edgeEffectOptions", JsonEdgeEffectOptions, filter);

    auto nestedScrollOptions = JsonUtil::Create(true);
    auto nestedScroll = GetNestedScroll();
    nestedScrollOptions->Put("scrollForward", nestedScroll.GetNestedScrollModeStr(nestedScroll.forward).c_str());
    nestedScrollOptions->Put("scrollBackward", nestedScroll.GetNestedScrollModeStr(nestedScroll.backward).c_str());
    json->PutExtAttr("nestedScroll", nestedScrollOptions, filter);
    if (NearEqual(GetFriction(), -1.0) && scrollableEvent_) {
        auto scrollable = scrollableEvent_->GetScrollable();
        CHECK_NULL_VOID(scrollable);
        json->PutExtAttr("friction", scrollable->GetFriction(), filter);
    } else {
        json->PutExtAttr("friction", GetFriction(), filter);
    }
}

void ScrollablePattern::SetAxis(Axis axis)
{
    if (axis_ == axis) {
        return;
    }
    axis_ = axis;
    SetParentScrollable();
    if (scrollBar_) {
        auto positionMode = GetPositionMode();
        scrollBar_->SetPositionMode(positionMode);
        if (scrollBarOverlayModifier_) {
            scrollBarOverlayModifier_->SetPositionMode(positionMode);
        }
    }
    if (useDefaultBackToTop_) {
        ResetBackToTop();
    }
    auto gestureHub = GetGestureHub();
    CHECK_NULL_VOID(gestureHub);
    if (scrollableEvent_) {
        gestureHub->RemoveScrollableEvent(scrollableEvent_);
        scrollableEvent_->SetAxis(axis);
        gestureHub->AddScrollableEvent(scrollableEvent_);
    }
    if (scrollEffect_) {
        gestureHub->RemoveScrollEdgeEffect(scrollEffect_);
        gestureHub->AddScrollEdgeEffect(GetAxis(), scrollEffect_);
    }
}

RefPtr<GestureEventHub> ScrollablePattern::GetGestureHub()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(hub, nullptr);
    return hub->GetOrCreateGestureEventHub();
}

RefPtr<InputEventHub> ScrollablePattern::GetInputHub()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(hub, nullptr);
    return hub->GetOrCreateInputEventHub();
}

bool ScrollablePattern::OnScrollCallback(float offset, int32_t source)
{
    if (source == SCROLL_FROM_START) {
        FireOnScrollStart();
        return true;
    }
    SuggestOpIncGroup(true);
    return UpdateCurrentOffset(offset, source);
}

void ScrollablePattern::ProcessNavBarReactOnStart()
{
    CHECK_NULL_VOID(navBarPattern_);
    navBarPattern_->OnCoordScrollStart();
}

float ScrollablePattern::ProcessNavBarReactOnUpdate(float offset)
{
    CHECK_NULL_RETURN(navBarPattern_, false);
    auto currentOffset = GetTotalOffset();
    return navBarPattern_->OnCoordScrollUpdate(offset, currentOffset);
}

void ScrollablePattern::ProcessNavBarReactOnEnd()
{
    CHECK_NULL_VOID(navBarPattern_);
    navBarPattern_->OnCoordScrollEnd();
}

bool ScrollablePattern::OnScrollPosition(double& offset, int32_t source)
{
    auto isSearchRefresh = GetIsSearchRefresh();
    if (needLinked_) {
        bool isAtTop = IsAtTop();
        auto isAtTopAndPositive = (isAtTop && Positive(offset));
        auto refreshCoordinateMode = RefreshCoordinationMode::UNKNOWN;
        auto modalSheetCoordinationMode = ModalSheetCoordinationMode::UNKNOWN;
        if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            modalSheetCoordinationMode = CoordinateWithSheet(offset, source, isAtTopAndPositive);
        }
        if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE) ||
            !isSearchRefresh) {
            refreshCoordinateMode = CoordinateWithRefresh(offset, source, isAtTopAndPositive);
        }
        auto navigationInCoordination = CoordinateWithNavigation(offset, source, isAtTop);
        if ((refreshCoordinateMode == RefreshCoordinationMode::REFRESH_SCROLL) || navigationInCoordination ||
            (modalSheetCoordinationMode == ModalSheetCoordinationMode::SHEET_SCROLL)) {
            return false;
        }
    }

    if (source == SCROLL_FROM_START) {
        SetParentScrollable();
        StopScrollBarAnimatorByProxy();
        AbortScrollAnimator();
    } else if (!AnimateStoped()) {
        return false;
    }
    return true;
}

namespace {
inline bool FromDrag(int32_t source)
{
    return source == SCROLL_FROM_UPDATE || source == SCROLL_FROM_AXIS;
}
} // namespace

bool ScrollablePattern::NeedSplitScroll(OverScrollOffset& overOffsets, int32_t source)
{
    return GreatNotEqual(overOffsets.start, 0.0) && refreshCoordination_ && refreshCoordination_->InCoordination() &&
           !isRefreshInReactive_ &&
           (FromDrag(source) || source == SCROLL_FROM_ANIMATION_SPRING ||
               source == SCROLL_FROM_ANIMATION) &&
           axis_ == Axis::VERTICAL;
}

RefreshCoordinationMode ScrollablePattern::CoordinateWithRefresh(double& offset, int32_t source, bool isAtTop)
{
    // use first scroll update to trigger scrollStart. Ignore SCROLL_FROM_START.
    if (source == SCROLL_FROM_START) {
        return RefreshCoordinationMode::UNKNOWN;
    }
    if (!refreshCoordination_) {
        CreateRefreshCoordination();
    }
    auto overOffsets = GetOverScrollOffset(offset);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) && !IsAtTop() && Positive(offset) &&
        NeedSplitScroll(overOffsets, source)) {
        offset = offset - overOffsets.start;
        OnScrollCallback(offset, source);
        isRefreshInReactive_ = true;
        refreshCoordination_->OnScrollStart(FromDrag(source), GetVelocity());
    }
    bool hasScrollSpace = Positive(offset) || (Negative(offset) && refreshCoordination_->IsRefreshInScroll());
    if (IsAtTop() && hasScrollSpace &&
        (FromDrag(source) || source == SCROLL_FROM_ANIMATION) &&
        !isRefreshInReactive_ && (axis_ == Axis::VERTICAL)) {
        isRefreshInReactive_ = true;
        refreshCoordination_->OnScrollStart(FromDrag(source), GetVelocity());
    }
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN) &&
        refreshCoordination_->InCoordination() && source != SCROLL_FROM_UPDATE &&
        source != SCROLL_FROM_AXIS && isRefreshInReactive_) {
        isRefreshInReactive_ = false;
        refreshCoordination_->OnScrollEnd(GetVelocity());
    }
    auto mode = RefreshCoordinationMode::UNKNOWN;
    if (refreshCoordination_->InCoordination() && isRefreshInReactive_) {
        if (!refreshCoordination_->OnScroll(
                GreatNotEqual(overOffsets.start, 0.0) ? overOffsets.start : offset, GetVelocity())) {
            isRefreshInReactive_ = false;
        }
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            mode = RefreshCoordinationMode::REFRESH_SCROLL;
        } else {
            if (scrollEffect_ && scrollEffect_->IsSpringEffect()) {
                mode = RefreshCoordinationMode::SCROLLABLE_SCROLL;
            } else {
                mode = RefreshCoordinationMode::REFRESH_SCROLL;
            }
        }
    }
    return mode;
}

ModalSheetCoordinationMode ScrollablePattern::CoordinateWithSheet(double& offset, int32_t source, bool isAtTop)
{
    auto coordinationMode = ModalSheetCoordinationMode::UNKNOWN;
    if (source == SCROLL_FROM_START) {
        isSheetInReactive_ = false;

        if (!sheetPattern_) {
            GetParentModalSheet();
        }
    }
    auto overOffsets = GetOverScrollOffset(offset);
    if (IsAtTop() && (source == SCROLL_FROM_UPDATE) && !isSheetInReactive_ && (axis_ == Axis::VERTICAL)) {
        isSheetInReactive_ = true;
        if (sheetPattern_) {
            sheetPattern_->OnCoordScrollStart();
        }
    }
    if (sheetPattern_ && isSheetInReactive_) {
        if (!sheetPattern_->OnCoordScrollUpdate(GreatNotEqual(overOffsets.start, 0.0) ? overOffsets.start : offset)) {
            isSheetInReactive_ = false;
            coordinationMode = ModalSheetCoordinationMode::SCROLLABLE_SCROLL;
        } else {
            coordinationMode = ModalSheetCoordinationMode::SHEET_SCROLL;
        }
    }
    return coordinationMode;
}

bool ScrollablePattern::CoordinateWithNavigation(double& offset, int32_t source, bool isAtTop)
{
    if (source == SCROLL_FROM_START) {
        GetParentNavigation();
        CHECK_NULL_RETURN(navBarPattern_, false);
        if (isAtTop && Positive(offset)) {
            // Starting coordinating scroll at the beginning of scrolling.
            isReactInParentMovement_ = true;
            ProcessNavBarReactOnStart();
        }
        return false;
    }

    CHECK_NULL_RETURN(navBarPattern_ && navBarPattern_->NeedCoordWithScroll(), false);

    float diff = navBarPattern_->GetTitleBarHeightLessThanMaxBarHeight();
    auto overOffsets = GetOverScrollOffset(offset + std::max(diff, 0.0f));
    overOffsets.start = Positive(offset) ? std::min(offset, overOffsets.start) : overOffsets.start;
    float offsetRemain = 0.0f;
    float offsetCoordinate = offset;

    if (!isReactInParentMovement_ && NeedCoordinateScrollWithNavigation(offset, source, overOffsets)) {
        // Starting coordinating scroll during sliding or flipping.
        isReactInParentMovement_ = true;
        ProcessNavBarReactOnStart();
    }

    if (isReactInParentMovement_) {
        if (Positive(offset)) {
            offsetRemain = offset - overOffsets.start;
            offsetCoordinate = overOffsets.start;
        }
        float handledByNav = ProcessNavBarReactOnUpdate(offsetCoordinate);
        if (NearEqual(handledByNav, offsetCoordinate) && !NearZero(offset)) {
            // All offsets are handled by Navigation, list cannot scroll over.
            SetCanOverScroll(false);
            offset = offsetRemain;
        } else {
            offset = offsetRemain + (offsetCoordinate - handledByNav);
        }
        if (Negative(diff) && Negative(offset)) {
            offset = overOffsets.start;
        }

        if (Negative(offset) && (source == SCROLL_FROM_ANIMATION_SPRING || !navBarPattern_->CanCoordScrollUp(offset))) {
            // When rebounding form scrolling over, trigger the ProcessNavBarReactOnEnd callback.
            isReactInParentMovement_ = false;
            ProcessNavBarReactOnEnd();
        }
    }

    return false;
}

void ScrollablePattern::SetUiDvsyncSwitch(bool on)
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    if (on && inScrollingStatus_) {
        inScrollingStatus_ = false;
        context->SetUiDvsyncSwitch(true);
        switchOnStatus_ = true;
    } else if (!on && switchOnStatus_) {
        context->SetUiDvsyncSwitch(false);
        switchOnStatus_ = false;
    }
}

void ScrollablePattern::OnScrollEnd()
{
    // Previous: Sets ScrollablePattern::OnScrollEnd to Scrollable->scrollEndCallback_
    // Scrollable calls scrollEndCallback_ in HandleOverScroll

    // Now: HandleOverScroll moved to ScrollablePattern and renamed HandleScrollVelocity, directly
    // calls OnScrollEnd in ScrollablePattern
    if (refreshCoordination_) {
        isRefreshInReactive_ = false;
        refreshCoordination_->OnScrollEnd(GetVelocity());
    }
    if (isSheetInReactive_) {
        isSheetInReactive_ = false;
        if (sheetPattern_) {
            sheetPattern_->OnCoordScrollEnd(GetVelocity());
        }
    }
    if (isReactInParentMovement_) {
        isReactInParentMovement_ = false;
        ProcessNavBarReactOnEnd();
    }
    if (isAnimationStop_) {
        SetUiDvsyncSwitch(false);
    }
    if (scrollStop_) {
        scrollAbort_ = false;
    }
    OnScrollEndCallback();
    SelectOverlayScrollNotifier::NotifyOnScrollEnd(WeakClaim(this));
}

void ScrollablePattern::AddScrollEvent()
{
    auto gestureHub = GetGestureHub();
    CHECK_NULL_VOID(gestureHub);
    if (scrollableEvent_) {
        gestureHub->RemoveScrollableEvent(scrollableEvent_);
    }
    auto scrollable = CreateScrollable();
    scrollableEvent_ = MakeRefPtr<ScrollableEvent>(GetAxis());
    scrollableEvent_->SetScrollable(scrollable);
    scrollableEvent_->SetAnimateVelocityCallback([weakScroll = AceType::WeakClaim(this)]() -> double {
        auto pattern = weakScroll.Upgrade();
        CHECK_NULL_RETURN(pattern, 0.0f);
        float nestedVelocity = pattern->GetNestedScrollVelocity();
        if (std::abs(nestedVelocity) > std::abs(pattern->GetCurrentVelocity())) {
            return nestedVelocity;
        }
        return pattern->GetCurrentVelocity();
    });
    gestureHub->AddScrollableEvent(scrollableEvent_);
    InitTouchEvent(gestureHub);
    RegisterWindowStateChangedCallback();
    if (!clickRecognizer_) {
        InitScrollBarClickEvent();
    }
    InitRatio();
    if (useDefaultBackToTop_) {
        ResetBackToTop();
    }
}

void ScrollablePattern::SetHandleScrollCallback(const RefPtr<Scrollable>& scrollable)
{
    // move HandleScroll and HandleOverScroll to ScrollablePattern by setting callbacks to scrollable
    CHECK_NULL_VOID(scrollable);
    auto handleScroll = [weak = AceType::WeakClaim(this)](
                            float offset, int32_t source, NestedState state) -> ScrollResult {
        auto pattern = weak.Upgrade();
        if (pattern) {
            return pattern->HandleScroll(offset, source, state, pattern->GetVelocity());
        }
        return {};
    };
    scrollable->SetHandleScrollCallback(std::move(handleScroll));
}

void ScrollablePattern::SetOverScrollCallback(const RefPtr<Scrollable>& scrollable)
{
    CHECK_NULL_VOID(scrollable);
    scrollable->SetOverScrollCallback([weak = WeakClaim(this)](float velocity) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->HandleOverScroll(velocity);
    });
}

void ScrollablePattern::SetIsReverseCallback(const RefPtr<Scrollable>& scrollable)
{
    CHECK_NULL_VOID(scrollable);
    scrollable->SetIsReverseCallback([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->IsReverse();
    });
}

void ScrollablePattern::SetOnScrollStartRec(const RefPtr<Scrollable>& scrollable)
{
    CHECK_NULL_VOID(scrollable);
    auto scrollStart = [weak = WeakClaim(this)](float position) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->FireAndCleanScrollingListener();
        pattern->OnScrollStartRecursiveInner(weak, position, pattern->GetVelocity());
    };
    scrollable->SetOnScrollStartRec(std::move(scrollStart));
}

void ScrollablePattern::SetOnScrollEndRec(const RefPtr<Scrollable>& scrollable)
{
    CHECK_NULL_VOID(scrollable);
    auto scrollEndRec = [weak = WeakClaim(this)](const std::optional<float>& velocity) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnScrollEndRecursiveInner(velocity);
    };
    scrollable->SetOnScrollEndRec(std::move(scrollEndRec));
}

void ScrollablePattern::SetScrollEndCallback(const RefPtr<Scrollable>& scrollable)
{
    CHECK_NULL_VOID(scrollable);
    auto scrollEnd = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnScrollEnd();
    };
    scrollable->SetScrollEndCallback(std::move(scrollEnd));
}

void ScrollablePattern::SetRemainVelocityCallback(const RefPtr<Scrollable>& scrollable)
{
    CHECK_NULL_VOID(scrollable);
    auto RemainVelocityToChild = [weak = WeakClaim(this)](float remainVelocity) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        auto child = pattern->GetScrollOriginChild();
        if (child) {
            child->RemainVelocityToChild(remainVelocity);
            return true;
        }
        return false;
    };
    scrollable->SetRemainVelocityCallback(std::move(RemainVelocityToChild));
}

void ScrollablePattern::SetDragEndCallback(const RefPtr<Scrollable>& scrollable)
{
    CHECK_NULL_VOID(scrollable);
    auto dragEnd = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnScrollDragEndRecursive();
    };
    scrollable->SetDragEndCallback(std::move(dragEnd));
}

void ScrollablePattern::SetStartSnapAnimationCallback(const RefPtr<Scrollable>& scrollable)
{
    CHECK_NULL_VOID(scrollable);
    auto startSnapAnimationCallback = [weak = WeakClaim(this)](SnapAnimationOptions snapAnimationOptions) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->StartSnapAnimation(snapAnimationOptions);
    };
    scrollable->SetStartSnapAnimationCallback(std::move(startSnapAnimationCallback));
}

void ScrollablePattern::SetNeedScrollSnapToSideCallback(const RefPtr<Scrollable>& scrollable)
{
    CHECK_NULL_VOID(scrollable);
    auto needScrollSnapToSideCallback = [weak = WeakClaim(this)](float delta) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->NeedScrollSnapToSide(delta);
    };
    scrollable->SetNeedScrollSnapToSideCallback(std::move(needScrollSnapToSideCallback));
}

void ScrollablePattern::SetDragFRCSceneCallback(const RefPtr<Scrollable>& scrollable)
{
    CHECK_NULL_VOID(scrollable);
    auto dragFRCSceneCallback = [weak = WeakClaim(this)](double velocity, SceneStatus sceneStatus) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (sceneStatus == NG::SceneStatus::START) {
            pattern->inScrollingStatus_ = true;
            pattern->SetUiDvsyncSwitch(false);
        } else if (sceneStatus == NG::SceneStatus::END) {
            pattern->SetUiDvsyncSwitch(true);
        }
        return pattern->NotifyFRCSceneInfo(SCROLLABLE_DRAG_SCENE, velocity, sceneStatus);
    };
    scrollable->SetDragFRCSceneCallback(std::move(dragFRCSceneCallback));
}

void ScrollablePattern::SetOnContinuousSliding(const RefPtr<Scrollable>& scrollable)
{
    CHECK_NULL_VOID(scrollable);
    scrollable->SetOnContinuousSliding([weak = WeakClaim(this)]() -> double {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, 0.0);
        return pattern->GetMainContentSize();
    });
}

void ScrollablePattern::SetGetSnapTypeCallback(const RefPtr<Scrollable>& scrollable)
{
    CHECK_NULL_VOID(scrollable);
    scrollable->SetGetSnapTypeCallback([weak = WeakClaim(this)]() -> SnapType {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, SnapType::NONE_SNAP);
        return pattern->GetSnapType();
    });
}

RefPtr<Scrollable> ScrollablePattern::CreateScrollable()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto scrollCallback = [weak = WeakClaim(this)](double offset, int32_t source) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->HandleScrollImpl(static_cast<float>(offset), source);
    };
    auto scrollable = MakeRefPtr<Scrollable>(std::move(scrollCallback), GetAxis());
    scrollable->SetNodeId(host->GetAccessibilityId());
    scrollable->SetNodeTag(host->GetTag());
    scrollable->Initialize(host);
    SetHandleScrollCallback(scrollable);
    SetOverScrollCallback(scrollable);
    SetIsReverseCallback(scrollable);
    SetOnScrollStartRec(scrollable);
    SetOnScrollEndRec(scrollable);
    SetScrollEndCallback(scrollable);
    SetRemainVelocityCallback(scrollable);
    SetDragEndCallback(scrollable);
    SetStartSnapAnimationCallback(scrollable);
    SetNeedScrollSnapToSideCallback(scrollable);
    SetDragFRCSceneCallback(scrollable);
    SetOnContinuousSliding(scrollable);
    SetGetSnapTypeCallback(scrollable);
    if (!NearZero(velocityScale_)) {
        scrollable->SetUnstaticVelocityScale(velocityScale_);
    }
    scrollable->SetMaxFlingVelocity(maxFlingVelocity_);
    if (friction_ != -1) {
        scrollable->SetUnstaticFriction(friction_);
    }
#ifdef SUPPORT_DIGITAL_CROWN
    scrollable->ListenDigitalCrownEvent(host);
#endif
    return scrollable;
}

void ScrollablePattern::InitRatio()
{
    CHECK_NULL_VOID(scrollableEvent_);
    auto scrollable = scrollableEvent_->GetScrollable();
    CHECK_NULL_VOID(scrollable);
    if (!ratio_.has_value()) {
        ratio_ = scrollable->GetRatio();
    }
}

void ScrollablePattern::StopScrollAnimation()
{
    StopScrollable();
}

void ScrollablePattern::OnTouchDown(const TouchEventInfo& info)
{
    if (GetNestedScrolling() && !NearZero(GetNestedScrollVelocity())) {
        auto child = GetScrollOriginChild();
        CHECK_NULL_VOID(child);
        child->StopScrollAnimation();
    }
    if (isBackToTopRunning_) {
        StopAnimate();
        isBackToTopRunning_ = false;
    }
}

void ScrollablePattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    // use TouchEvent to receive next touch down event to stop animation.
    if (touchEvent_) {
        return;
    }
    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->FireObserverOnTouch(info);
        CHECK_NULL_VOID(pattern->scrollableEvent_);
        auto scrollable = pattern->scrollableEvent_->GetScrollable();
        CHECK_NULL_VOID(scrollable);
        switch (info.GetTouches().front().GetTouchType()) {
            case TouchType::DOWN:
                scrollable->HandleTouchDown();
                pattern->OnTouchDown(info);
                break;
            case TouchType::UP:
                scrollable->HandleTouchUp();
                break;
            case TouchType::CANCEL:
                scrollable->HandleTouchCancel();
                break;
            default:
                break;
        }
    };
    if (touchEvent_) {
        gestureHub->RemoveTouchEvent(touchEvent_);
    }
    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchEvent_);
}

void ScrollablePattern::RegisterWindowStateChangedCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    context->AddWindowStateChangedCallback(host->GetId());
}

void ScrollablePattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    UnRegister2DragDropManager(frameNode);
    auto context = frameNode->GetContextWithCheck();
    CHECK_NULL_VOID(context);
    context->RemoveWindowStateChangedCallback(frameNode->GetId());
}

void ScrollablePattern::OnWindowHide()
{
    CHECK_NULL_VOID(scrollableEvent_);
    auto scrollable = scrollableEvent_->GetScrollable();
    CHECK_NULL_VOID(scrollable);
    scrollable->StopFrictionAnimation();
}

void ScrollablePattern::SetEdgeEffect(EdgeEffect edgeEffect)
{
    auto gestureHub = GetGestureHub();
    CHECK_NULL_VOID(gestureHub);
    if (scrollEffect_ && (edgeEffect != scrollEffect_->GetEdgeEffect())) {
        gestureHub->RemoveScrollEdgeEffect(scrollEffect_);
        scrollEffect_.Reset();
    }
    if (edgeEffect == EdgeEffect::SPRING && !scrollEffect_) {
        auto springEffect = AceType::MakeRefPtr<ScrollSpringEffect>();
        CHECK_NULL_VOID(springEffect);
        springEffect->SetOutBoundaryCallback([weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_RETURN(pattern, false);
            return pattern->OutBoundaryCallback();
        });
        // add callback to springEdgeEffect
        SetEdgeEffectCallback(springEffect);
        scrollEffect_ = springEffect;
        gestureHub->AddScrollEdgeEffect(GetAxis(), scrollEffect_);
    }
    if (edgeEffect == EdgeEffect::FADE && !scrollEffect_) {
        auto fadeEdgeEffect = AceType::MakeRefPtr<ScrollFadeEffect>(Color::GRAY);
        CHECK_NULL_VOID(fadeEdgeEffect);
        fadeEdgeEffect->SetHandleOverScrollCallback([weakScroll = AceType::WeakClaim(this)]() -> void {
            auto pattern = weakScroll.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        });
        SetEdgeEffectCallback(fadeEdgeEffect);
        fadeEdgeEffect->InitialEdgeEffect();
        scrollEffect_ = fadeEdgeEffect;
        gestureHub->AddScrollEdgeEffect(GetAxis(), scrollEffect_);
    }
    CHECK_NULL_VOID(scrollableEvent_);
    auto scrollable = scrollableEvent_->GetScrollable();
    CHECK_NULL_VOID(scrollable);
    scrollable->SetEdgeEffect(edgeEffect);
    if (edgeEffect != EdgeEffect::SPRING) {
        scrollable->StopSpringAnimation(true);
    }
}

void ScrollablePattern::HandleFadeEffect(float offset, int32_t source, const SizeF& size,
    bool isNotPositiveScrollableDistance)
{
    auto isScrollFromUpdate = source == SCROLL_FROM_UPDATE;
    scrollEffect_->HandleOverScroll(GetAxis(), IsReverse() ? offset : -offset,
        size, isScrollFromUpdate, isNotPositiveScrollableDistance);
}

bool ScrollablePattern::CanFadeEffect(float offset, bool isAtTop, bool isAtBottom) const
{
    return (isAtTop && Positive(offset) && GetEffectEdge() != EffectEdge::END) ||
           (isAtBottom && Negative(offset) && GetEffectEdge() != EffectEdge::START);
}

bool ScrollablePattern::HandleEdgeEffect(float offset, int32_t source, const SizeF& size)
{
    bool isAtTop = IsAtTop();
    bool isAtBottom = IsAtBottom(true);
    bool isNotPositiveScrollableDistance = isAtTop && isAtBottom;
    // check edgeEffect is not springEffect
    if (scrollEffect_ && scrollEffect_->IsFadeEffect() &&
        (source == SCROLL_FROM_UPDATE || source == SCROLL_FROM_ANIMATION)) { // handle edge effect
        if (CanFadeEffect(offset, isAtTop, isAtBottom)) {
            HandleFadeEffect(offset, source, size, isNotPositiveScrollableDistance);
        }
    }
    if (!(scrollEffect_ && (scrollEffect_->IsSpringEffect() && HasEdgeEffect(offset)) &&
        (source == SCROLL_FROM_UPDATE || source == SCROLL_FROM_ANIMATION ||
        source == SCROLL_FROM_ANIMATION_SPRING || source == SCROLL_FROM_CROWN ||
        (source == SCROLL_FROM_ANIMATION_CONTROLLER && animateCanOverScroll_)))) {
        if (isAtTop && Positive(offset)) {
            animateOverScroll_ = false;
            return false;
        }
        if (isAtBottom && Negative(offset)) {
            animateOverScroll_ = false;
            return false;
        }
    }
    animateOverScroll_ = (source == SCROLL_FROM_ANIMATION_CONTROLLER) && (isAtTop || isAtBottom);
    isAnimateOverScroll_ = (source == SCROLL_FROM_ANIMATION_CONTROLLER) && animateCanOverScroll_ &&
                            ((isAtTop && Positive(offset)) || (isAtBottom && Negative(offset)));
    return true;
}

void ScrollablePattern::RegisterScrollBarEventTask()
{
    CHECK_NULL_VOID(scrollBar_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    scrollBar_->SetAxis(axis_);
    scrollBar_->SetMarkNeedRenderFunc([weak = AceType::WeakClaim(AceType::RawPtr(host))]() {
        auto host = weak.Upgrade();
        CHECK_NULL_VOID(host);
        host->MarkNeedRenderOnly();
    });
    auto scrollCallback = [weak = WeakClaim(this)](double offset, int32_t source, bool isMouseWheelScroll) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        auto scrollable = pattern->GetScrollable();
        if (isMouseWheelScroll && scrollable) {
            scrollable->ProcessAxisUpdateEvent(offset, true);
            return true;
        }
        return pattern->OnScrollCallback(static_cast<float>(offset), source);
    };
    scrollBar_->SetScrollPositionCallback(std::move(scrollCallback));
    auto scrollEnd = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnScrollEnd();
    };
    scrollBar_->SetScrollEndCallback(std::move(scrollEnd));
    auto startSnapAnimationCallback = [weak = WeakClaim(this)](SnapAnimationOptions snapAnimationOptions) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->StartSnapAnimation(snapAnimationOptions);
    };
    scrollBar_->SetStartSnapAnimationCallback(std::move(startSnapAnimationCallback));
    auto scrollPageCallback = [weak = WeakClaim(this)](bool reverse, bool smooth) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->ScrollPage(reverse, smooth);
    };
    scrollBar_->SetScrollPageCallback(std::move(scrollPageCallback));

    auto dragFRCSceneCallback = [weak = WeakClaim(this)](double velocity, SceneStatus sceneStatus) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        return pattern->NotifyFRCSceneInfo(SCROLL_BAR_DRAG_SCENE, velocity, sceneStatus);
    };
    scrollBar_->SetDragFRCSceneCallback(std::move(dragFRCSceneCallback));
    InitScrollBarGestureEvent();
    InitScrollBarMouseEvent();
}

void ScrollablePattern::InitScrollBarGestureEvent()
{
    auto gestureHub = GetGestureHub();
    CHECK_NULL_VOID(gestureHub);
    auto inputHub = GetInputHub();
    CHECK_NULL_VOID(inputHub);
    scrollBar_->SetGestureEvent();
    scrollBar_->SetMouseEvent();
    scrollBar_->SetHoverEvent();
    gestureHub->AddTouchEvent(scrollBar_->GetTouchEvent());
    inputHub->AddOnMouseEvent(scrollBar_->GetMouseEvent());
    inputHub->AddOnHoverEvent(scrollBar_->GetHoverEvent());
    CHECK_NULL_VOID(scrollableEvent_);
    scrollableEvent_->SetInBarRegionCallback(
        [weak = AceType::WeakClaim(AceType::RawPtr(scrollBar_))](const PointF& point, SourceType source) {
            auto scrollBar = weak.Upgrade();
            CHECK_NULL_RETURN(scrollBar, false);
            if (source == SourceType::MOUSE) {
                return scrollBar->InBarHoverRegion(Point(point.GetX(), point.GetY()));
            }
            return scrollBar->InBarTouchRegion(Point(point.GetX(), point.GetY()));
        });
    scrollableEvent_->SetBarCollectTouchTargetCallback(
        [weak = AceType::WeakClaim(AceType::RawPtr(scrollBar_))](const OffsetF& coordinateOffset,
            const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result, const RefPtr<FrameNode>& frameNode,
            const RefPtr<TargetComponent>& targetComponent, ResponseLinkResult& responseLinkResult) {
            auto scrollBar = weak.Upgrade();
            CHECK_NULL_VOID(scrollBar);
            scrollBar->OnCollectTouchTarget(
                coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult);
        });
    scrollableEvent_->SetBarCollectClickAndLongPressTargetCallback(
        [weak = AceType::WeakClaim(AceType::RawPtr(scrollBar_)), this](const OffsetF& coordinateOffset,
            const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result, const RefPtr<FrameNode>& frameNode,
            const RefPtr<TargetComponent>& targetComponent, ResponseLinkResult& responseLinkResult) {
            auto scrollBar = weak.Upgrade();
            CHECK_NULL_VOID(scrollBar);
            scrollBar->OnCollectLongPressTarget(
                coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult);
            OnCollectClickTarget(
                coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult);
        });
    scrollableEvent_->SetInBarRectRegionCallback(
        [weak = AceType::WeakClaim(AceType::RawPtr(scrollBar_))](const PointF& point, SourceType source) {
            auto scrollBar = weak.Upgrade();
            CHECK_NULL_RETURN(scrollBar, false);
            return scrollBar->InBarRectRegion(Point(point.GetX(), point.GetY()));
        });
}

RefPtr<ScrollBar> ScrollablePattern::CreateScrollBar()
{
#ifdef ARKUI_CIRCLE_FEATURE
    if (isRoundScroll_) {
        return AceType::MakeRefPtr<ArcScrollBar>();
    }
#endif
    return AceType::MakeRefPtr<ScrollBar>();
}

void ScrollablePattern::SetScrollBar(DisplayMode displayMode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (displayMode == DisplayMode::OFF) {
        if (scrollBar_) {
            auto gestureHub = GetGestureHub();
            if (gestureHub) {
                gestureHub->RemoveTouchEvent(scrollBar_->GetTouchEvent());
            }
            scrollBar_.Reset();
            if (scrollBarOverlayModifier_) {
                scrollBarOverlayModifier_->SetOpacity(0);
            }
        }
        return;
    }
    DisplayMode oldDisplayMode = DisplayMode::OFF;
    if (!scrollBar_) {
        scrollBar_ = CreateScrollBar();
        CHECK_NULL_VOID(scrollBar_);
        RegisterScrollBarEventTask();
    } else {
        oldDisplayMode = scrollBar_->GetDisplayMode();
    }
    // set the scroll bar style
    auto positionMode = GetPositionMode();
    scrollBar_->SetPositionMode(positionMode);
    if (scrollBarOverlayModifier_) {
        scrollBarOverlayModifier_->SetPositionMode(positionMode);
    }

    if (oldDisplayMode != displayMode) {
        scrollBar_->SetDisplayMode(displayMode);
        if (scrollBarOverlayModifier_ && scrollBar_->IsScrollable()) {
            scrollBarOverlayModifier_->SetOpacity(UINT8_MAX);
        }
        scrollBar_->ScheduleDisappearDelayTask();
        if (isInitialized_ && !host->CheckNeedForceMeasureAndLayout()) {
            UpdateScrollBarOffset();
        }
    }
    UpdateBorderRadius();
}

void ScrollablePattern::UpdateBorderRadius()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (renderContext->HasBorderRadius()) {
        auto borderRadius = renderContext->GetBorderRadius().value();
        if (!(borderRadius == scrollBar_->GetHostBorderRadius())) {
            scrollBar_->SetHostBorderRadius(borderRadius);
            scrollBar_->CalcReservedHeight();
        }
    }
}

void ScrollablePattern::SetScrollBar(const std::unique_ptr<ScrollBarProperty>& property)
{
    if (!property) {
        SetScrollBar(DisplayMode::AUTO);
        return;
    }
    auto displayMode = property->GetScrollBarMode().value_or(DisplayMode::AUTO);
    SetScrollBar(displayMode);
    if (scrollBar_) {
        auto barWidth = property->GetScrollBarWidth();
        if (barWidth) {
            scrollBar_->SetActiveWidth(barWidth.value());
            scrollBar_->SetTouchWidth(barWidth.value());
            if (isRoundScroll_) {
                scrollBar_->SetNormalWidth(Dimension(ARC_INITWIDTH_VAL));
                scrollBar_->SetInactiveWidth(Dimension(ARC_INITWIDTH_VAL));
#ifdef ARKUI_CIRCLE_FEATURE
                scrollBar_->SetActiveBackgroundWidth(barWidth.value());
                scrollBar_->SetActiveScrollBarWidth(barWidth.value() - Dimension(ARC_INITWIDTH_HALF_VAL));
#endif
            } else {
                scrollBar_->SetInactiveWidth(barWidth.value());
                scrollBar_->SetNormalWidth(barWidth.value());
            }
            scrollBar_->SetIsUserNormalWidth(true);
        } else {
            scrollBar_->SetIsUserNormalWidth(false);
        }
        auto barColor = property->GetScrollBarColor();
        if (barColor) {
            scrollBar_->SetForegroundColor(barColor.value());
        }
    }
}

void ScrollablePattern::UpdateScrollBarRegion(float offset, float estimatedHeight, Size viewPort, Offset viewOffset)
{
    // inner scrollbar, viewOffset is padding offset
    if (scrollBar_) {
        bool scrollable = IsScrollable();
        if (scrollBar_->IsScrollable() != scrollable) {
            scrollBar_->SetScrollable(scrollable);
            if (scrollBarOverlayModifier_) {
                scrollBarOverlayModifier_->SetOpacity(scrollable ? UINT8_MAX : 0);
                scrollBarOverlayModifier_->SetScrollable(scrollable);
            }
            if (scrollable) {
                scrollBar_->ScheduleDisappearDelayTask();
            }
        }
        Offset scrollOffset = { offset, offset }; // fit for w/h switched.
        UpdateBorderRadius();
        scrollBar_->SetReverse(IsReverse());
        scrollBar_->UpdateScrollBarRegion(viewOffset, viewPort, scrollOffset, estimatedHeight, GetScrollSource());
        scrollBar_->MarkNeedRender();
        CreateScrollBarOverlayModifier();
    }

    // outer scrollbar
    if (scrollBarProxy_) {
        auto height = (GetAxis() == Axis::VERTICAL ? viewPort.Height() : viewPort.Width());
        auto estimatedHeightItem = estimatedHeight - height;
        estimatedHeight_ = (estimatedHeightItem < 0 ? 0 : estimatedHeightItem);
        barOffset_ = -offset;
        scrollBarProxy_->NotifyScrollBar(scrollSource_);
    }

    for (auto nestbar : nestScrollBarProxy_) {
        auto scrollBarProxy = nestbar.Upgrade();
        if (!scrollBarProxy) {
            continue;
        }
        scrollBarProxy->NotifyScrollBar(scrollSource_);
    }
}

void ScrollablePattern::ScrollEndCallback(bool nestedScroll, float velocity)
{
    if (nestedScroll) {
        OnScrollEndRecursiveInner(velocity);
    } else {
        OnScrollEnd();
    }
}

void ScrollablePattern::SetScrollBarProxy(const RefPtr<ScrollBarProxy>& scrollBarProxy)
{
    CHECK_NULL_VOID(scrollBarProxy);
    auto scrollFunction = [weak = WeakClaim(this)](double offset, int32_t source, bool nestedScroll,
        bool isMouseWheelScroll) {
        if (source != SCROLL_FROM_START) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_RETURN(pattern && pattern->GetAxis() != Axis::NONE, false);
            auto scrollable = pattern->GetScrollable();
            if (isMouseWheelScroll && scrollable) {
                scrollable->ProcessAxisUpdateEvent(offset, true);
                return true;
            }
            if (!nestedScroll) {
                return pattern->UpdateCurrentOffset(offset, source);
            }
            pattern->HandleScroll(offset, source, NestedState::GESTURE, 0.0f);
        }
        return true;
    };
    auto scrollStartCallback = [weak = WeakClaim(this)](double offset, int32_t source, bool nestedScroll) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        pattern->StopScrollableAndAnimate();
        // no source == SCROLL_FROM_START for ScrollBar
        if (nestedScroll) {
            pattern->OnScrollStartRecursiveInner(weak, offset, pattern->GetVelocity());
        } else {
            pattern->OnScrollStartCallback();
        }
        return pattern->OnScrollCallback(static_cast<float>(offset), source);
    };
    auto scrollEndCallback = [weak = WeakClaim(this)](bool nestedScroll) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->ScrollEndCallback(nestedScroll, pattern->GetVelocity());
    };
    auto startSnapAnimationCallback = [weak = WeakClaim(this)](SnapAnimationOptions snapAnimationOptions) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->StartSnapAnimation(snapAnimationOptions);
    };
    auto scrollbarFRcallback = [weak = WeakClaim(this)](double velocity, SceneStatus sceneStatus) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        return pattern->NotifyFRCSceneInfo(CUSTOM_SCROLL_BAR_SCENE, velocity, sceneStatus);
    };
    auto scrollPageCallback = [weak = WeakClaim(this)](bool reverse, bool smooth) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        return pattern->ScrollPage(reverse, smooth);
    };
    ScrollableNodeInfo nodeInfo = { AceType::WeakClaim(this), std::move(scrollFunction), std::move(scrollStartCallback),
        std::move(scrollEndCallback), std::move(startSnapAnimationCallback), std::move(scrollbarFRcallback),
        std::move(scrollPageCallback) };
    scrollBarProxy->RegisterScrollableNode(nodeInfo);
    scrollBarProxy_ = scrollBarProxy;
}

RefPtr<ScrollBarOverlayModifier> ScrollablePattern::CreateOverlayModifier()
{
#ifdef ARKUI_CIRCLE_FEATURE
    if (isRoundScroll_ && scrollBar_) {
        auto arcScrollBarOverlayModifier = AceType::MakeRefPtr<ArcScrollBarOverlayModifier>();
        auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar_);
        if (arcScrollBar) {
            arcScrollBarOverlayModifier->SetPositionMode(arcScrollBar->GetPositionMode());
            arcScrollBarOverlayModifier->SetArcRect(arcScrollBar->GetArcActiveRect());
            arcScrollBarOverlayModifier->SetBackgroundArcRect(arcScrollBar->GetArcBarRect());
        }
        return arcScrollBarOverlayModifier;
    }
#endif
    return AceType::MakeRefPtr<ScrollBarOverlayModifier>();
}

void ScrollablePattern::CreateScrollBarOverlayModifier()
{
    CHECK_NULL_VOID(scrollBar_ && scrollBar_->NeedPaint());
    CHECK_NULL_VOID(!scrollBarOverlayModifier_);
    scrollBarOverlayModifier_ = CreateOverlayModifier();
    CHECK_NULL_VOID(scrollBarOverlayModifier_);
    scrollBarOverlayModifier_->SetRect(scrollBar_->GetActiveRect());
    scrollBarOverlayModifier_->SetPositionMode(scrollBar_->GetPositionMode());
    SetOnHiddenChangeForParent();
}

void ScrollablePattern::HandleScrollBarOutBoundary(float scrollBarOutBoundaryExtent)
{
    scrollBarOutBoundaryExtent_ = scrollBarOutBoundaryExtent;
    CHECK_NULL_VOID(scrollBar_ && scrollBar_->NeedScrollBar());
    scrollBar_->SetOutBoundary(std::abs(scrollBarOutBoundaryExtent_));
}

void ScrollablePattern::SetFriction(double friction)
{
    if (LessOrEqual(friction, 0.0)) {
        friction =
            Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN) ? API11_FRICTION : FRICTION;
        friction =
            Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) ? API12_FRICTION : friction;
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_THIRTEEN)) {
            auto context = GetContext();
            CHECK_NULL_VOID(context);
            auto scrollableTheme = context->GetTheme<ScrollableTheme>();
            friction = scrollableTheme->GetFriction();
        }
    }
    friction_ = friction;
    CHECK_NULL_VOID(scrollableEvent_);
    auto scrollable = scrollableEvent_->GetScrollable();
    scrollable->SetUnstaticFriction(friction_);
}

void ScrollablePattern::SetVelocityScale(double scale)
{
    if (LessOrEqual(scale, 0.0)) {
        scale = Container::GreatOrEqualAPITargetVersion(
            PlatformVersion::VERSION_ELEVEN) ? NEW_VELOCITY_SCALE : VELOCITY_SCALE;
    }
    velocityScale_ = scale;
    CHECK_NULL_VOID(scrollableEvent_);
    auto scrollable = scrollableEvent_->GetScrollable();
    scrollable->SetUnstaticVelocityScale(velocityScale_);
}

void ScrollablePattern::SetMaxFlingVelocity(double max)
{
    if (LessOrEqual(max, 0.0f)) {
        max = MAX_VELOCITY;
    }
    maxFlingVelocity_ = max;
    CHECK_NULL_VOID(scrollableEvent_);
    auto scrollable = scrollableEvent_->GetScrollable();
    scrollable->SetMaxFlingVelocity(max);
}

void ScrollablePattern::GetParentNavigation()
{
    if (navBarPattern_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if ((host->GetTag() != V2::LIST_ETS_TAG) && (host->GetTag() != V2::GRID_ETS_TAG) &&
        (host->GetTag() != V2::SCROLL_ETS_TAG) && (host->GetTag() != V2::ARC_LIST_ETS_TAG)) {
        return;
    }
    for (auto parent = host->GetParent(); parent != nullptr; parent = parent->GetParent()) {
        RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(parent);
        if (!frameNode) {
            continue;
        }
        if ((frameNode->GetTag() == V2::LIST_ETS_TAG) || (frameNode->GetTag() == V2::GRID_ETS_TAG) ||
            (frameNode->GetTag() == V2::SCROLL_ETS_TAG) || (frameNode->GetTag() == V2::ARC_LIST_ETS_TAG)) {
            break;
        }
        navBarPattern_ = frameNode->GetPattern<NavDestinationPatternBase>();
        if (!navBarPattern_) {
            continue;
        }
        return;
    }
    navBarPattern_ = nullptr;
    return;
}

void ScrollablePattern::GetParentModalSheet()
{
    if (sheetPattern_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    if (host->GetTag() != V2::SCROLL_ETS_TAG) {
        return;
    }

    for (auto parent = host->GetParent(); parent != nullptr; parent = parent->GetParent()) {
        RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(parent);
        if (!frameNode) {
            continue;
        }
        sheetPattern_ = frameNode->GetPattern<SheetPresentationPattern>();
        if (!sheetPattern_) {
            continue;
        }
        return;
    }
    return;
}

void ScrollablePattern::StopAnimate()
{
    if (!IsScrollableStopped()) {
        StopScrollable();
    }
    if (animator_ && !animator_->IsStopped()) {
        animator_->Stop();
    }
    if (!isAnimationStop_) {
        StopAnimation(springAnimation_);
        StopAnimation(curveAnimation_);
    }
    if (scrollBar_) {
        scrollBar_->StopFlingAnimation();
    }
}

void ScrollablePattern::ScrollTo(float position)
{
    StopAnimate();
    UpdateCurrentOffset(GetTotalOffset() - position, SCROLL_FROM_JUMP);
}

void ScrollablePattern::AnimateTo(
    float position, float duration, const RefPtr<Curve>& curve, bool smooth, bool canOverScroll, bool useTotalOffset)
{
    StopScrollableAndAnimate();
    if (NearEqual(position, GetTotalOffset())) {
        return;
    }
    finalPosition_ = position;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (smooth) {
        if (!useTotalOffset) {
            lastPosition_ = GetTotalOffset();
        }
        PlaySpringAnimation(position, DEFAULT_SCROLL_TO_VELOCITY, DEFAULT_SCROLL_TO_MASS, DEFAULT_SCROLL_TO_STIFFNESS,
            DEFAULT_SCROLL_TO_DAMPING, useTotalOffset);
    } else {
        PlayCurveAnimation(position, duration, curve, canOverScroll);
    }
    if (!GetIsDragging()) {
        FireOnScrollStart();
    }
    PerfMonitor::GetPerfMonitor()->EndCommercial(PerfConstants::APP_LIST_FLING, false);
    PerfMonitor::GetPerfMonitor()->Start(PerfConstants::SCROLLER_ANIMATION, PerfActionType::FIRST_MOVE, "");
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RequestFrame();
}

void ScrollablePattern::OnAnimateFinish()
{
    useTotalOffset_ = true;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (isAnimationStop_) {
        SetUiDvsyncSwitch(false);
        PerfMonitor::GetPerfMonitor()->End(PerfConstants::SCROLLER_ANIMATION, false);
    }
    if (animateToTraceFlag_) {
        animateToTraceFlag_ = false;
        AceAsyncTraceEndCommercial(host->GetAccessibilityId(),
            (TRAILING_ANIMATION + std::to_string(host->GetAccessibilityId()) + std::string(" ") + host->GetTag())
                .c_str());
    }
    NotifyFRCSceneInfo(SCROLLABLE_MULTI_TASK_SCENE, GetCurrentVelocity(), SceneStatus::END);
    isBackToTopRunning_ = false;
}

void ScrollablePattern::PlaySpringAnimation(float position, float velocity, float mass, float stiffness, float damping,
                                            bool useTotalOffset)
{
    if (!springOffsetProperty_) {
        InitSpringOffsetProperty();
        CHECK_NULL_VOID(springOffsetProperty_);
    }

    AnimationOption option;
    auto curve = AceType::MakeRefPtr<InterpolatingSpring>(velocity, mass, stiffness, damping);
    InitOption(option, CUSTOM_ANIMATION_DURATION, curve);
    isAnimationStop_ = false;
    useTotalOffset_ = useTotalOffset;
    AnimationUtils::ExecuteWithoutAnimation([weak = AceType::WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->springOffsetProperty_->Set(pattern->GetTotalOffset());
    });
    springAnimation_ = AnimationUtils::StartAnimation(
        option,
        [weak = AceType::WeakClaim(this), position]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->SetUiDvsyncSwitch(true);
            pattern->springOffsetProperty_->Set(position);
        },
        [weak = AceType::WeakClaim(this), id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnAnimateFinish();
            pattern->SetScrollEdgeType(ScrollEdgeType::SCROLL_NONE);
    });
    NotifyFRCSceneInfo(SCROLLABLE_MULTI_TASK_SCENE, GetCurrentVelocity(), SceneStatus::START);
}

void ScrollablePattern::PlayCurveAnimation(
    float position, float duration, const RefPtr<Curve>& curve, bool canOverScroll)
{
    AnimationOption option;
    InitOption(option, duration, curve);
    if (!curveOffsetProperty_) {
        InitCurveOffsetProperty();
        CHECK_NULL_VOID(curveOffsetProperty_);
    }
    isAnimationStop_ = false;
    SetAnimateCanOverScroll(canOverScroll);
    curveOffsetProperty_->Set(GetTotalOffset());
    curveAnimation_ = AnimationUtils::StartAnimation(
        option,
        [weak = AceType::WeakClaim(this), position]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->SetUiDvsyncSwitch(true);
            pattern->curveOffsetProperty_->Set(position);
        },
        [weak = AceType::WeakClaim(this), id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnAnimateFinish();
        });
    NotifyFRCSceneInfo(SCROLLABLE_MULTI_TASK_SCENE, GetCurrentVelocity(), SceneStatus::START);
}

float ScrollablePattern::GetScrollDelta(float offset, bool& stopAnimation)
{
    auto context = GetContext();
    CHECK_NULL_RETURN(context, 0.0f);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    uint64_t currentVsync = context->GetVsyncTime();
    uint64_t diff = currentVsync - lastVsyncTime_;
    if (diff < MAX_VSYNC_DIFF_TIME && diff > MIN_DIFF_VSYNC) {
        currentVelocity_ = (offset - lastPosition_) / diff * MILLOS_PER_NANO_SECONDS;
        NotifyFRCSceneInfo(SCROLLABLE_MULTI_TASK_SCENE, currentVelocity_, SceneStatus::RUNNING);
    }
    stopAnimation = NearEqual(finalPosition_, offset, SPRING_ACCURACY);
    if (stopAnimation) {
        offset = finalPosition_;
    }
    if (NearEqual(offset, lastPosition_, 1.0) && !animateToTraceFlag_) {
        animateToTraceFlag_ = true;
        auto id = host->GetAccessibilityId();
        AceAsyncTraceBeginCommercial(id, (TRAILING_ANIMATION + std::to_string(id) + std::string(" ") +
            host->GetTag()).c_str());
    }
    auto delta = useTotalOffset_ ? GetTotalOffset() - offset : lastPosition_ - offset;
    lastVsyncTime_ = currentVsync;
    lastPosition_ = offset;
    return delta;
}

void ScrollablePattern::InitSpringOffsetProperty()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto propertyCallback = [weak = AceType::WeakClaim(this)](float offset) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->isAnimationStop_) {
            return;
        }
        bool stopAnimation = false;
        auto delta = pattern->GetScrollDelta(offset, stopAnimation);
        auto source = SCROLL_FROM_ANIMATION_CONTROLLER;
        if (pattern->GetLastSnapTargetIndex().has_value()) {
            source = SCROLL_FROM_ANIMATION;
        }
        if (pattern->isBackToTopRunning_) {
            source = SCROLL_FROM_STATUSBAR;
        }
        if (!pattern->UpdateCurrentOffset(delta, source) || stopAnimation) {
            pattern->StopAnimation(pattern->springAnimation_);
        }
    };
    springOffsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    renderContext->AttachNodeAnimatableProperty(springOffsetProperty_);
}

void ScrollablePattern::InitCurveOffsetProperty()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto propertyCallback = [weak = AceType::WeakClaim(this)](float offset) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->isAnimationStop_) {
            return;
        }
        bool stopAnimation = false;
        auto delta = pattern->GetScrollDelta(offset, stopAnimation);
        if (!pattern->UpdateCurrentOffset(delta, SCROLL_FROM_ANIMATION_CONTROLLER) ||
            stopAnimation || pattern->isAnimateOverScroll_) {
            if (pattern->isAnimateOverScroll_) {
                pattern->isAnimateOverScroll_ = false;
                pattern->isScrollToOverAnimation_  = true;
                auto pauseVelocity = -pattern->currentVelocity_;
                auto context = pattern->GetContext();
                CHECK_NULL_VOID(context);
                context->MarkNeedFlushAnimationStartTime();
                pattern->PauseAnimation(pattern->curveAnimation_);
                pattern->HandleOverScroll(pauseVelocity);
            } else if (stopAnimation ||
                       (pattern->IsAtTop() && LessOrEqual(pattern->finalPosition_, pattern->GetTotalOffset())) ||
                       (pattern->IsAtBottom() && GreatOrEqual(pattern->finalPosition_, pattern->GetTotalOffset()))) {
                pattern->StopAnimation(pattern->curveAnimation_);
            }
        }
    };
    curveOffsetProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    renderContext->AttachNodeAnimatableProperty(curveOffsetProperty_);
}

void ScrollablePattern::InitOption(AnimationOption &option, float duration, const RefPtr<Curve>& curve)
{
    if (!curve) {
        option.SetCurve(Curves::EASE); // default curve
    } else {
        option.SetCurve(curve);
    }
    if (duration > 0) {
        option.SetDuration(duration);
    } else {
        option.SetDuration(CUSTOM_ANIMATION_DURATION);
    }
}

void ScrollablePattern::StopAnimation(std::shared_ptr<AnimationUtils::Animation> animation)
{
    SetAnimateCanOverScroll(false);
    isAnimationStop_ = true;
    currentVelocity_ = 0.0;
    if (!animation) {
        return;
    }
    AnimationUtils::StopAnimation(animation);
    OnAnimateStop();
}

void ScrollablePattern::PauseAnimation(std::shared_ptr<AnimationUtils::Animation> animation)
{
    SetAnimateCanOverScroll(false);
    isAnimationStop_ = true;
    currentVelocity_ = 0.0;
    if (!animation) {
        return;
    }
    AnimationUtils::StopAnimation(animation);
}

void ScrollablePattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToBounds(true);
    host->GetRenderContext()->UpdateClipEdge(true);
}

void ScrollablePattern::UninitMouseEvent()
{
    if (!boxSelectPanEvent_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->RemovePanEvent(boxSelectPanEvent_);
    boxSelectPanEvent_.Reset();
    ClearMultiSelect();
    ClearInvisibleItemsSelectedStatus();
    isMouseEventInit_ = false;
}

void ScrollablePattern::InitMouseEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (!boxSelectPanEvent_) {
        auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleDragStart(info);
        };

        auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleDragUpdate(info);
        };

        auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleDragEnd();
        };
        GestureEventNoParameter actionCancelTask = [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleDragEnd();
        };
        boxSelectPanEvent_ = MakeRefPtr<PanEvent>(std::move(actionStartTask), std::move(actionUpdateTask),
            std::move(actionEndTask), std::move(actionCancelTask));
    }
    PanDirection panDirection = { .type = PanDirection::ALL };
    gestureHub->AddPanEvent(boxSelectPanEvent_, panDirection, 1, DEFAULT_PAN_DISTANCE);
    gestureHub->SetPanEventType(GestureTypeName::BOXSELECT);
    gestureHub->SetExcludedAxisForPanEvent(true);
    gestureHub->SetOnGestureJudgeNativeBegin([](const RefPtr<NG::GestureInfo>& gestureInfo,
                                                 const std::shared_ptr<BaseGestureEvent>& info) -> GestureJudgeResult {
        if (gestureInfo->GetType() == GestureTypeName::BOXSELECT &&
            gestureInfo->GetInputEventType() != InputEventType::MOUSE_BUTTON) {
            return GestureJudgeResult::REJECT;
        }
        return GestureJudgeResult::CONTINUE;
    });
    isMouseEventInit_ = true;
}

void ScrollablePattern::HandleDragStart(const GestureEvent& info)
{
    TAG_LOGI(AceLogTag::ACE_SCROLLABLE, "Box select start");
    auto mouseOffsetX = static_cast<float>(info.GetRawGlobalLocation().GetX());
    auto mouseOffsetY = static_cast<float>(info.GetRawGlobalLocation().GetY());
    mouseOffsetX -= info.GetOffsetX();
    mouseOffsetY -= info.GetOffsetY();
    SuggestOpIncGroup(true);
    if (!IsItemSelected(static_cast<float>(info.GetGlobalLocation().GetX()) - info.GetOffsetX(),
        static_cast<float>(info.GetGlobalLocation().GetY()) - info.GetOffsetY())) {
        ClearMultiSelect();
        ClearInvisibleItemsSelectedStatus();
        mouseStartOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
        lastMouseStart_ = mouseStartOffset_;
        mouseEndOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
        mousePressOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
        totalOffsetOfMousePressed_ = mousePressOffset_.GetMainOffset(axis_) + GetTotalOffset();
        canMultiSelect_ = true;
    }
    mousePressed_ = true;
}

void ScrollablePattern::HandleDragUpdate(const GestureEvent& info)
{
    auto mouseOffsetX = static_cast<float>(info.GetRawGlobalLocation().GetX());
    auto mouseOffsetY = static_cast<float>(info.GetRawGlobalLocation().GetY());
    if (!mousePressed_ || !canMultiSelect_) {
        return;
    }
    if (info.GetInputEventType() != InputEventType::MOUSE_BUTTON) {
        HandleDragEnd();
        return;
    }
    lastMouseMove_ = info;
    auto delta = OffsetF(mouseOffsetX, mouseOffsetY) - mousePressOffset_;
    if (Offset(delta.GetX(), delta.GetY()).GetDistance() > DEFAULT_PAN_DISTANCE.ConvertToPx()) {
        mouseEndOffset_ = OffsetF(mouseOffsetX, mouseOffsetY);
        // avoid large select zone
        LimitMouseEndOffset();
        auto selectedZone = ComputeSelectedZone(mouseStartOffset_, mouseEndOffset_);
        MultiSelectWithoutKeyboard(selectedZone);
        HandleInvisibleItemsSelectedStatus(selectedZone);
    }
    SelectWithScroll();
}

void ScrollablePattern::HandleDragEnd()
{
    TAG_LOGI(AceLogTag::ACE_SCROLLABLE, "Box select end");
    mouseStartOffset_.Reset();
    lastMouseStart_.Reset();
    mouseEndOffset_.Reset();
    mousePressed_ = false;
    canMultiSelect_ = false;
    ClearSelectedZone();
    itemToBeSelected_.clear();
    lastMouseMove_.SetLocalLocation(Offset::Zero());
}
void ScrollablePattern::ClearInvisibleItemsSelectedStatus()
{
    for (auto& item : itemToBeSelected_) {
        item.second.FireSelectChangeEvent(false);
    }
    itemToBeSelected_.clear();
}

void ScrollablePattern::HandleInvisibleItemsSelectedStatus(const RectF& selectedZone)
{
    auto newRect = selectedZone;
    auto startMainOffset = mouseStartOffset_.GetMainOffset(axis_);
    auto endMainOffset = mouseEndOffset_.GetMainOffset(axis_);
    SelectDirection oldDirection = selectDirection_;
    if (LessNotEqual(startMainOffset, endMainOffset)) {
        selectDirection_ = SELECT_DOWN;
        if (axis_ == Axis::VERTICAL) {
            newRect.SetOffset(OffsetF(selectedZone.Left(), totalOffsetOfMousePressed_));
        } else {
            newRect.SetOffset(OffsetF(totalOffsetOfMousePressed_, selectedZone.Top()));
        }
    } else {
        selectDirection_ = SELECT_UP;
        if (axis_ == Axis::VERTICAL) {
            newRect.SetOffset(
                OffsetF(selectedZone.Left(), totalOffsetOfMousePressed_ - (startMainOffset - endMainOffset)));
        } else {
            newRect.SetOffset(
                OffsetF(totalOffsetOfMousePressed_ - (startMainOffset - endMainOffset), selectedZone.Top()));
        }
    }
    oldDirection = oldDirection == SELECT_NONE ? selectDirection_ : oldDirection;

    for (auto& item : itemToBeSelected_) {
        item.second.FireSelectChangeEvent(newRect.IsIntersectWith(item.second.rect));
    }

    if (oldDirection != selectDirection_) {
        itemToBeSelected_.clear();
    }
}

void ScrollablePattern::SelectWithScroll()
{
    if (!IsScrollable()) {
        return;
    }
    auto offset = GetOutOfScrollableOffset();
    if (NearZero(offset)) {
        return;
    }

    if (AnimateRunning()) {
        return;
    }

    if (!isAnimationStop_) {
        StopAnimation(springAnimation_);
        StopAnimation(curveAnimation_);
    }

    if (!animator_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetContextRefPtr();
        CHECK_NULL_VOID(context);
        animator_ = CREATE_ANIMATOR(context);
        animator_->AddStopListener([weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnAnimateStop();
        });
    } else if (!animator_->IsStopped()) {
        scrollAbort_ = true;
        animator_->Stop();
    }

    if (!selectMotion_) {
        selectMotion_ = AceType::MakeRefPtr<SelectMotion>(offset, [weak = WeakClaim(this)]() -> bool {
            auto pattern = weak.Upgrade();
            CHECK_NULL_RETURN(pattern, true);
            return pattern->ShouldSelectScrollBeStopped();
        });
        selectMotion_->AddListener([weakScroll = AceType::WeakClaim(this)](double offset) {
            auto pattern = weakScroll.Upgrade();
            CHECK_NULL_VOID(pattern);
            offset = pattern->GetOffsetWithLimit(offset);
            pattern->UpdateCurrentOffset(offset, SCROLL_FROM_AXIS);
            pattern->UpdateMouseStart(offset);
        });
    } else {
        selectMotion_->Reset(offset);
    }

    animator_->PlayMotion(selectMotion_);

    FireOnScrollStart();
}

void ScrollablePattern::ClearSelectedZone()
{
    DrawSelectedZone(RectF());
    selectScrollOffset_ = 0.0f;
}

RectF ScrollablePattern::ComputeSelectedZone(const OffsetF& startOffset, const OffsetF& endOffset)
{
    RectF selectedZone;
    if (startOffset.GetX() <= endOffset.GetX()) {
        if (startOffset.GetY() <= endOffset.GetY()) {
            // bottom right
            selectedZone = RectF(startOffset.GetX(), startOffset.GetY(), endOffset.GetX() - startOffset.GetX(),
                endOffset.GetY() - startOffset.GetY());
        } else {
            // top right
            selectedZone = RectF(startOffset.GetX(), endOffset.GetY(), endOffset.GetX() - startOffset.GetX(),
                startOffset.GetY() - endOffset.GetY());
        }
    } else {
        if (startOffset.GetY() <= endOffset.GetY()) {
            // bottom left
            selectedZone = RectF(endOffset.GetX(), startOffset.GetY(), startOffset.GetX() - endOffset.GetX(),
                endOffset.GetY() - startOffset.GetY());
        } else {
            // top left
            selectedZone = RectF(endOffset.GetX(), endOffset.GetY(), startOffset.GetX() - endOffset.GetX(),
                startOffset.GetY() - endOffset.GetY());
        }
    }

    return selectedZone;
}

void ScrollablePattern::DrawSelectedZone(const RectF& selectedZone)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hostContext = host->GetRenderContext();
    CHECK_NULL_VOID(hostContext);
    hostContext->UpdateMouseSelectWithRect(selectedZone, SELECT_FILL_COLOR, SELECT_STROKE_COLOR);
}

void ScrollablePattern::MarkSelectedItems()
{
    if (multiSelectable_ && mousePressed_) {
        UpdateMouseStartOffset();
        auto selectedZone = ComputeSelectedZone(mouseStartOffset_, mouseEndOffset_);
        if (!selectedZone.IsEmpty()) {
            MultiSelectWithoutKeyboard(selectedZone);
            HandleInvisibleItemsSelectedStatus(selectedZone);
        }
    }
}

bool ScrollablePattern::ShouldSelectScrollBeStopped()
{
    if (!mousePressed_) {
        return true;
    }
    auto offset = GetOutOfScrollableOffset();
    if (NearZero(offset)) {
        return true;
    }

    if (selectMotion_) {
        selectMotion_->Reset(offset);
    }
    return false;
};

void ScrollablePattern::UpdateMouseStart(float offset)
{
    selectScrollOffset_ += offset;
}

float ScrollablePattern::GetOutOfScrollableOffset() const
{
    auto offset = 0.0f;
    auto mouseMainOffset = static_cast<float>(
        axis_ == Axis::VERTICAL ? lastMouseMove_.GetLocalLocation().GetY() : lastMouseMove_.GetLocalLocation().GetX());
    auto hostSize = GetHostFrameSize();
    CHECK_NULL_RETURN(hostSize.has_value(), offset);
    auto mainTop = 0.0f;
    auto mainBottom = hostSize->MainSize(axis_);
    if (GreatOrEqual(mouseMainOffset, mainTop) && LessOrEqual(mouseMainOffset, mainBottom)) {
        return offset;
    }
    if (GreatNotEqual(mouseMainOffset, mainBottom)) {
        if (IsAtBottom()) {
            return offset;
        }
        offset = mainBottom - mouseMainOffset;
    }
    if (LessNotEqual(mouseMainOffset, mainTop)) {
        if (IsAtTop()) {
            return offset;
        }
        offset = mainTop - mouseMainOffset;
    }
    return offset;
}

// avoid start position move when offset is bigger then item height
float ScrollablePattern::GetOffsetWithLimit(float offset) const
{
    if (Positive(offset)) {
        auto totalOffset = GetTotalOffset();
        return std::min(totalOffset, offset);
    } else if (Negative(offset)) {
        auto frameNode = GetHost();
        CHECK_NULL_RETURN(frameNode, true);
        auto hostSize = frameNode->GetGeometryNode()->GetFrameSize();
        auto remainHeight = GetTotalHeight() - GetTotalOffset() - hostSize.MainSize(axis_);
        return std::max(offset, -remainHeight);
    }
    return 0;
}

void ScrollablePattern::LimitMouseEndOffset()
{
    float limitedMainOffset = -1.0f;
    float limitedCrossOffset = -1.0f;
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto hostSize = frameNode->GetGeometryNode()->GetFrameSize();
    auto mainSize = hostSize.MainSize(axis_);
    auto crossSize = hostSize.CrossSize(axis_);
    auto mainOffset = mouseEndOffset_.GetMainOffset(axis_);
    auto crossOffset = mouseEndOffset_.GetCrossOffset(axis_);
    if (LessNotEqual(mainOffset, 0.0f)) {
        limitedMainOffset = 0.0f;
    }
    if (GreatNotEqual(mainOffset, mainSize)) {
        limitedMainOffset = mainSize;
    }
    if (LessNotEqual(crossOffset, 0.0f)) {
        limitedCrossOffset = 0.0f;
    }
    if (GreatNotEqual(crossOffset, crossSize)) {
        limitedCrossOffset = crossSize;
    }

    if (axis_ == Axis::VERTICAL) {
        mouseEndOffset_.SetX(LessNotEqual(limitedCrossOffset, 0.0f) ? mouseEndOffset_.GetX() : limitedCrossOffset);
        mouseEndOffset_.SetY(LessNotEqual(limitedMainOffset, 0.0f) ? mouseEndOffset_.GetY() : limitedMainOffset);
    } else {
        mouseEndOffset_.SetX(LessNotEqual(limitedMainOffset, 0.0f) ? mouseEndOffset_.GetX() : limitedMainOffset);
        mouseEndOffset_.SetY(LessNotEqual(limitedCrossOffset, 0.0f) ? mouseEndOffset_.GetY() : limitedCrossOffset);
    }
}

void ScrollablePattern::UpdateMouseStartOffset()
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    uint64_t currentVsync = context->GetVsyncTime();
    if (currentVsync > lastVsyncTime_) {
        if (axis_ == Axis::VERTICAL) {
            mouseStartOffset_.AddY(selectScrollOffset_);
        } else {
            mouseStartOffset_.AddX(selectScrollOffset_);
        }
        selectScrollOffset_ = 0.0f;
    }
    lastVsyncTime_ = currentVsync;
}

bool ScrollablePattern::HandleScrollImpl(float offset, int32_t source)
{
    // Previous: Set HandleScrollImpl to Scrollable->callback_
    // Scrollable::HandleScroll calls callback_ through UpdateScrollPosition

    // Now: HandleScroll moved to ScrollablePattern, directly call HandleScrollImpl in
    // ScrollablePattern::HandleScroll
    double overOffset = offset;
    if (!OnScrollPosition(overOffset, source)) {
        return false;
    }
    auto result = OnScrollCallback(overOffset, source);
    SelectOverlayScrollNotifier::NotifyOnScrollCallback(WeakClaim(this), overOffset, source);
    return result;
}

void ScrollablePattern::NotifyMoved(bool value)
{
    CHECK_NULL_VOID(scrollableEvent_);
    auto&& scroll = scrollableEvent_->GetScrollable();
    if (scroll) {
        scroll->SetMoved(value);
    }
}

void ScrollablePattern::ProcessSpringEffect(float velocity, bool needRestart)
{
    CHECK_NULL_VOID(InstanceOf<ScrollSpringEffect>(scrollEffect_));
    auto isOutOfBoundary = OutBoundaryCallback();
    if (!isOutOfBoundary && !GetCanOverScroll()) {
        OnScrollEndRecursiveInner(velocity);
        return;
    }
    CHECK_NULL_VOID(scrollableEvent_);
    auto scrollable = scrollableEvent_->GetScrollable();
    // HandleTouchUp may be triggered before HandleDragEnd when scrollable nested scrollable,
    // so need to update spring motion.
    if (needRestart || !(scrollable && scrollable->IsSpringMotionRunning())) {
        StopScrollable();
        scrollEffect_->ProcessScrollOver(velocity);
    } else {
        scrollEffect_->ProcessSpringUpdate();
    }
}

void ScrollablePattern::SetCanOverScroll(bool val)
{
    CHECK_NULL_VOID(scrollableEvent_);
    auto&& scrollable = scrollableEvent_->GetScrollable();
    if (scrollable) {
        scrollable->SetCanOverScroll(val);
    }
}

bool ScrollablePattern::GetCanOverScroll() const
{
    CHECK_NULL_RETURN(scrollableEvent_, true);
    auto&& scrollable = scrollableEvent_->GetScrollable();
    if (scrollable) {
        return scrollable->CanOverScroll();
    }
    return true;
}

EdgeEffect ScrollablePattern::GetEdgeEffect() const
{
    return edgeEffect_;
}

ScrollState ScrollablePattern::GetScrollState() const
{
    return ScrollablePattern::GetScrollState(scrollSource_);
}

ScrollState ScrollablePattern::GetScrollState(int32_t scrollSource)
{
    // with event
    if (scrollSource == SCROLL_FROM_UPDATE || scrollSource == SCROLL_FROM_AXIS || scrollSource == SCROLL_FROM_BAR ||
        scrollSource == SCROLL_FROM_CROWN) {
        return ScrollState::SCROLL;
    }
    // without event
    if (scrollSource == SCROLL_FROM_ANIMATION || scrollSource == SCROLL_FROM_ANIMATION_SPRING ||
        scrollSource == SCROLL_FROM_ANIMATION_CONTROLLER || scrollSource == SCROLL_FROM_BAR_FLING) {
        return ScrollState::FLING;
    }
    // SCROLL_FROM_NONE, SCROLL_FROM_JUMP, SCROLL_FROM_CHILD, SCROLL_FROM_FOCUS_JUMP, SCROLL_FROM_ROTATE,
    // SCROLL_FROM_INDEXER, SCROLL_FROM_START
    return ScrollState::IDLE;
}

ScrollSource ScrollablePattern::ConvertScrollSource(int32_t source)
{
    // static linear map must be sorted by key.
    static const LinearEnumMapNode<int32_t, ScrollSource> scrollSourceMap[] = {
        { SCROLL_FROM_UPDATE, ScrollSource::DRAG },
        { SCROLL_FROM_ANIMATION, ScrollSource::FLING },
        { SCROLL_FROM_JUMP, ScrollSource::SCROLLER },
        { SCROLL_FROM_ANIMATION_SPRING, ScrollSource::EDGE_EFFECT },
        { SCROLL_FROM_BAR, ScrollSource::SCROLL_BAR },
        { SCROLL_FROM_FOCUS_JUMP, ScrollSource::OTHER_USER_INPUT },
        { SCROLL_FROM_AXIS, ScrollSource::OTHER_USER_INPUT },
        { SCROLL_FROM_ANIMATION_CONTROLLER, ScrollSource::SCROLLER_ANIMATION },
        { SCROLL_FROM_BAR_FLING, ScrollSource::SCROLL_BAR_FLING },
        { SCROLL_FROM_CROWN, ScrollSource::OTHER_USER_INPUT },
        { SCROLL_FROM_STATUSBAR, ScrollSource::OTHER_USER_INPUT },
    };
    ScrollSource sourceType = ScrollSource::OTHER_USER_INPUT;
    int64_t idx = BinarySearchFindIndex(scrollSourceMap, ArraySize(scrollSourceMap), source);
    if (idx >= 0) {
        sourceType = scrollSourceMap[idx].value;
    }
    return sourceType;
}

ScrollResult ScrollablePattern::HandleScrollParentFirst(float& offset, int32_t source, NestedState state)
{
    auto parent = GetNestedScrollParent();
    ScrollState scrollState = source == SCROLL_FROM_ANIMATION ? ScrollState::FLING : ScrollState::SCROLL;
    if (state == NestedState::CHILD_OVER_SCROLL) {
        if (!HasEdgeEffect(offset)) {
            return parent->HandleScroll(offset, source, NestedState::CHILD_OVER_SCROLL, GetVelocity());
        }
        ExecuteScrollFrameBegin(offset, scrollState);
        return { 0, true };
    }
    auto result = parent->HandleScroll(offset, source, NestedState::CHILD_SCROLL, GetVelocity());
    offset = result.remain;
    if (NearZero(offset)) {
        SetCanOverScroll(!InstanceOf<ScrollablePattern>(parent));
        return { 0, false };
    }
    float allOffset = offset;
    ExecuteScrollFrameBegin(offset, scrollState);
    auto remainOffset = std::abs(offset) < std::abs(allOffset) ? allOffset - offset : 0;
    auto overOffsets = GetOverScrollOffset(offset);
    auto overOffset = offset > 0 ? overOffsets.start : overOffsets.end;
    remainOffset += overOffset;
    if (NearZero(remainOffset)) {
        SetCanOverScroll(false);
        return { 0, false };
    }
    if (state == NestedState::CHILD_SCROLL) {
        offset -= overOffset;
        SetCanOverScroll(false);
        return { remainOffset, !NearZero(overOffset) };
    }
    bool parentEdgeEffect = false;
    if (!HasEdgeEffect(offset)) {
        result = parent->HandleScroll(remainOffset, source, NestedState::CHILD_OVER_SCROLL, GetVelocity());
        if (NearZero(result.remain)) {
            offset -= overOffset;
            parentEdgeEffect = NearZero(offset) && result.reachEdge;
        }
    }
    SetCanOverScroll((!NearZero(overOffset) && HasEdgeEffect(offset)) || parentEdgeEffect);
    return { 0, GetCanOverScroll() };
}

ScrollResult ScrollablePattern::HandleScrollSelfFirst(float& offset, int32_t source, NestedState state)
{
    auto parent = GetNestedScrollParent();
    ScrollState scrollState = source == SCROLL_FROM_ANIMATION ? ScrollState::FLING : ScrollState::SCROLL;
    if (state == NestedState::CHILD_OVER_SCROLL) {
        auto result = parent->HandleScroll(offset, source, NestedState::CHILD_OVER_SCROLL, GetVelocity());
        if (NearZero(result.remain)) {
            offset = 0;
            return result;
        }
        ExecuteScrollFrameBegin(offset, scrollState);
        if (!HasEdgeEffect(offset)) {
            return result;
        }
        return { 0, true };
    }
    float allOffset = offset;
    ExecuteScrollFrameBegin(offset, scrollState);
    auto remainOffset = std::abs(offset) < std::abs(allOffset) ? allOffset - offset : 0;
    auto overOffsets = GetOverScrollOffset(offset);
    auto overOffset = offset > 0 ? overOffsets.start : overOffsets.end;
    if (NearZero(overOffset) && NearZero(remainOffset)) {
        SetCanOverScroll(false);
        return { 0, false };
    }
    offset -= overOffset;
    auto result = parent->HandleScroll(overOffset + remainOffset, source, NestedState::CHILD_SCROLL, GetVelocity());
    if (NearZero(result.remain)) {
        SetCanOverScroll(!InstanceOf<ScrollablePattern>(parent));
        return { 0, false };
    }
    if (state == NestedState::CHILD_SCROLL) {
        SetCanOverScroll(false);
        return result;
    }
    // triggering overScroll, parent always handle it first
    auto overRes = parent->HandleScroll(result.remain, source, NestedState::CHILD_OVER_SCROLL, GetVelocity());
    offset += LessNotEqual(std::abs(overOffset), std::abs(result.remain)) ? overOffset : overRes.remain;
    bool parentEdgeEffect = result.reachEdge && NearZero(offset);
    SetCanOverScroll((!NearZero(overOffset) && HasEdgeEffect(offset)) || parentEdgeEffect);
    return { 0, GetCanOverScroll() };
}

ScrollResult ScrollablePattern::HandleScrollSelfOnly(float& offset, int32_t source, NestedState state)
{
    float allOffset = offset;
    ScrollState scrollState = source == SCROLL_FROM_ANIMATION ? ScrollState::FLING : ScrollState::SCROLL;
    ExecuteScrollFrameBegin(offset, scrollState);
    auto remainOffset = allOffset - offset;
    auto overOffsets = GetOverScrollOffset(offset);
    auto overOffset = (offset > 0) ? overOffsets.start : overOffsets.end;
    remainOffset += overOffset;
    if (NearZero(remainOffset)) {
        SetCanOverScroll(false);
        return { 0, false };
    }
    bool canOverScroll = false;
    if (state == NestedState::CHILD_SCROLL) {
        offset -= overOffset;
    } else if (state == NestedState::GESTURE) {
        canOverScroll = !NearZero(overOffset) && HasEdgeEffect(offset);
    } else if (HasEdgeEffect(offset, true)) {
        remainOffset = 0;
    }
    SetCanOverScroll(canOverScroll);
    return { remainOffset, !NearZero(overOffset) };
}

bool ScrollablePattern::HasEdgeEffect(float offset, bool isWithRefresh) const
{
    if (GetEdgeEffect() != EdgeEffect::NONE && GetEffectEdge() == EffectEdge::ALL) {
        return true;
    }
    auto overOffsets = GetOverScrollOffset(offset);
    auto overOffset = offset > 0 ? overOffsets.start : overOffsets.end;
    bool hasEdgeEffect =
        (GetEdgeEffect() != EdgeEffect::NONE) && ((NonNegative(overOffset) && GetEffectEdge() != EffectEdge::END) ||
                                                     (NonPositive(overOffset) && GetEffectEdge() != EffectEdge::START));
    return isWithRefresh
               ? (hasEdgeEffect || (Positive(offset) && refreshCoordination_ && refreshCoordination_->InCoordination()))
               : hasEdgeEffect;
}

ScrollResult ScrollablePattern::HandleScrollParallel(float& offset, int32_t source, NestedState state)
{
    auto remainOffset = 0.0;
    auto parent = GetNestedScrollParent();
    ScrollState scrollState = source == SCROLL_FROM_ANIMATION ? ScrollState::FLING : ScrollState::SCROLL;
    if (state == NestedState::CHILD_OVER_SCROLL) {
        if (GetEdgeEffect() == EdgeEffect::NONE) {
            auto result = parent->HandleScroll(offset, source, NestedState::CHILD_OVER_SCROLL, GetVelocity());
            remainOffset = result.remain;
            offset = 0;
        } else {
            ExecuteScrollFrameBegin(offset, scrollState);
        }
        return { remainOffset, true };
    }

    bool canOverScroll = false;
    float parentOffset = offset;
    ExecuteScrollFrameBegin(offset, scrollState);
    auto result = parent->HandleScroll(parentOffset, source, NestedState::CHILD_SCROLL, GetVelocity());

    auto overOffsets = GetOverScrollOffset(offset);
    auto overOffset = offset > 0 ? overOffsets.start : overOffsets.end;
    if (!NearZero(overOffset) && result.reachEdge) {
        if (state == NestedState::CHILD_SCROLL) {
            remainOffset = overOffset;
            offset = offset - overOffset;
        } else if (GetEdgeEffect() == EdgeEffect::NONE) {
            parent->HandleScroll(result.remain, source, NestedState::CHILD_OVER_SCROLL, GetVelocity());
            canOverScroll = true;
            offset = offset - overOffset;
        } else {
            canOverScroll = true;
        }
    } else if (!NearZero(overOffset)) {
        offset = offset - overOffset;
    }
    SetCanOverScroll(canOverScroll);
    return { remainOffset, !NearZero(overOffset) && result.reachEdge };
}

bool ScrollablePattern::HandleOutBoundary(float& offset, int32_t source, NestedState state, ScrollResult& result)
{
    if (state != NestedState::GESTURE && state != NestedState::CHILD_CHECK_OVER_SCROLL) {
        return false;
    }
    auto overOffsets = GetOverScrollOffset(offset);
    auto backOverOffset = Negative(offset) ? overOffsets.start : overOffsets.end;
    float selfOffset = 0.0f;
    if (!NearZero(backOverOffset)) {
        selfOffset = backOverOffset;
        offset -= backOverOffset;
        HandleScrollImpl(selfOffset, source);
    }
    auto parent = GetNestedScrollParent();
    if (!NearZero(offset) && parent) {
        auto res = parent->HandleScroll(offset, source, NestedState::CHILD_CHECK_OVER_SCROLL, GetVelocity());
        offset = res.remain;
    }
    if (state == NestedState::CHILD_CHECK_OVER_SCROLL) {
        result = { offset, true };
        offset = 0.0f;
    }
    return NearZero(offset);
}

ScrollResult ScrollablePattern::HandleScroll(float offset, int32_t source, NestedState state, float velocity)
{
    ScrollResult result = { 0, false };
    auto host = GetHost();
    CHECK_NULL_RETURN(host, result);
    auto nestedScroll = GetNestedScroll();
    auto parent = GetNestedScrollParent();
    auto initOffset = offset;
    if (NearZero(offset)) {
        ScrollState scrollState = source == SCROLL_FROM_ANIMATION ? ScrollState::FLING : ScrollState::SCROLL;
        ExecuteScrollFrameBegin(offset, scrollState);
    } else if (!HandleOutBoundary(offset, source, state, result)) {
        if (parent && !IsScrollSnap() &&
                ((offset < 0 && nestedScroll.forward == NestedScrollMode::PARENT_FIRST) ||
                    (offset > 0 && nestedScroll.backward == NestedScrollMode::PARENT_FIRST))) {
            result = HandleScrollParentFirst(offset, source, state);
        } else if (parent && ((offset < 0 && nestedScroll.forward == NestedScrollMode::SELF_FIRST) ||
                                (offset > 0 && nestedScroll.backward == NestedScrollMode::SELF_FIRST))) {
            result = HandleScrollSelfFirst(offset, source, state);
        } else if (parent && ((offset < 0 && nestedScroll.forward == NestedScrollMode::PARALLEL) ||
                                (offset > 0 && nestedScroll.backward == NestedScrollMode::PARALLEL))) {
            result = HandleScrollParallel(offset, source, state);
        } else {
            result = HandleScrollSelfOnly(offset, source, state);
        }
    } else if (state == NestedState::CHILD_CHECK_OVER_SCROLL) {
        return result;
    }
    ACE_SCOPED_TRACE("HandleScroll, initOffset:%f, processedOffset:%f, "
                     "source:%d, nestedState:%d, canOverScroll:%u, id:%d, tag:%s",
        initOffset, offset, source, state, GetCanOverScroll(),
        static_cast<int32_t>(host->GetAccessibilityId()), host->GetTag().c_str());
    UpdateNestedScrollVelocity(offset, state);
    bool moved = HandleScrollImpl(offset, source);
    if (!moved && source == SCROLL_FROM_AXIS) {
        SetScrollableCurrentPos(-GetTotalOffset());
    }
    NotifyMoved(moved);
    return result;
}

bool ScrollablePattern::HandleScrollVelocity(float velocity,  const RefPtr<NestableScrollContainer>& child)
{
    // if scrollable try to over scroll when it is at the boundary,
    // scrollable does not start fling animation.
    SetNestedScrolling(false);
    SetScrollOriginChild(AceType::WeakClaim(AceType::RawPtr(child)));
    auto edgeEffect = GetEdgeEffect();
    auto needFlingAtEdge = !(((IsAtTop() && Positive(velocity)) || (IsAtBottom() && Negative(velocity))));
    auto isOutOfBoundary = OutBoundaryCallback();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    ACE_SCOPED_TRACE("HandleScrollVelocity, IsOutOfBoundary:%u, needFlingAtEdge:%u, edgeEffect:%d, IsAtTop:%u, "
                     "IsAtBottom:%u, velocity:%f, id:%d, tag:%s",
        isOutOfBoundary, needFlingAtEdge, edgeEffect, IsAtTop(), IsAtBottom(), velocity,
        static_cast<int32_t>(host->GetAccessibilityId()), host->GetTag().c_str());
    if (!isOutOfBoundary && needFlingAtEdge) {
        // trigger scroll animation if edge not reached
        if (scrollableEvent_ && scrollableEvent_->GetScrollable()) {
            scrollableEvent_->GetScrollable()->StartScrollAnimation(0.0f, velocity);
            return true;
        }
        return false;
    }
    SetCanOverScroll(true);
    return HandleOverScroll(velocity) || GetEdgeEffect() == EdgeEffect::FADE;
}

void ScrollablePattern::RemainVelocityToChild(float remainVelocity)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    ACE_SCOPED_TRACE("RemainVelocityToChild, remainVelocity:%f id:%d, tag:%s",
        remainVelocity, static_cast<int32_t>(host->GetAccessibilityId()), host->GetTag().c_str());
    Fling(remainVelocity);
}

bool ScrollablePattern::HandleScrollableOverScroll(float velocity)
{
    bool result = false;
    for (auto ancestor = GetNestedScrollParent(); ancestor != nullptr; ancestor = ancestor->GetNestedScrollParent()) {
        if (ancestor->NestedScrollOutOfBoundary()) {
            result = ancestor->HandleScrollVelocity(velocity, Claim(this));
            break;
        }
        auto ancestorNestedScroll = ancestor->GetNestedScroll();
        if (!ancestorNestedScroll.NeedParent()) {
            break;
        }
    }
    if (result) {
        OnScrollEndRecursiveInner(velocity);
        return true;
    }
    return false;
}

bool ScrollablePattern::CanSpringOverScroll() const
{
    switch (effectEdge_) {
        case EffectEdge::ALL:
            return true;
        case EffectEdge::START:
            return IsAtTopWithDelta();
        case EffectEdge::END:
            return IsAtBottomWithDelta();
    }
    return true;
}

bool ScrollablePattern::HandleOverScroll(float velocity)
{
    auto parent = GetNestedScrollParent();
    auto nestedScroll = GetNestedScroll();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto isOutOfBoundary = IsOutOfBoundary();
    ACE_SCOPED_TRACE("HandleOverScroll, IsOutOfBoundary:%u, id:%d, tag:%s", isOutOfBoundary,
        static_cast<int32_t>(host->GetAccessibilityId()), host->GetTag().c_str());
    auto needSpringEffect = GetEdgeEffect() == EdgeEffect::SPRING && CanSpringOverScroll();
    if (!parent || !nestedScroll.NeedParent(velocity < 0) || isOutOfBoundary) {
        if (needSpringEffect && AnimateStoped()) {
            // trigger onScrollEnd later, when spring animation finishes
            ProcessSpringEffect(velocity, true);
            return true;
        }
        OnScrollEndRecursiveInner(velocity);
        return false;
    }
    if (InstanceOf<ScrollablePattern>(parent) && HandleScrollableOverScroll(velocity)) {
        // Triggers ancestor spring animation that out of boundary, and after ancestor returns to the boundary,
        // triggers child RemainVelocityToChild
        return true;
    }
    // parent handle over scroll first
    if ((velocity < 0 && (nestedScroll.forward == NestedScrollMode::SELF_FIRST)) ||
        (velocity > 0 && (nestedScroll.backward == NestedScrollMode::SELF_FIRST)) ||
        (!InstanceOf<ScrollablePattern>(parent) && !isOutOfBoundary)) {
        if (parent->HandleScrollVelocity(velocity)) {
            OnScrollEnd();
            return true;
        }
        if (needSpringEffect) {
            ProcessSpringEffect(velocity);
            return true;
        }
    }

    // self handle over scroll first
    if (needSpringEffect) {
        ProcessSpringEffect(velocity);
        return true;
    }
    if (GetEdgeEffect() == EdgeEffect::FADE) {
        OnScrollEndRecursiveInner(velocity);
        return false;
    }
    OnScrollEnd();
    return parent->HandleScrollVelocity(velocity);
}

void ScrollablePattern::ExecuteScrollFrameBegin(float& mainDelta, ScrollState state)
{
    auto context = GetContext();
    auto eventHub = GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto scrollFrameBeginCallback = eventHub->GetOnScrollFrameBegin();
    auto onJSFrameNodeScrollFrameBegin = eventHub->GetJSFrameNodeOnScrollFrameBegin();
    if (!context) {
        return;
    }

    auto offset = Dimension(mainDelta / context->GetDipScale(), DimensionUnit::VP);
    ScrollFrameResult scrollRes { .offset = -offset };
    if (scrollFrameBeginCallback) {
        scrollRes = scrollFrameBeginCallback(scrollRes.offset, state);
    }
    if (onJSFrameNodeScrollFrameBegin) {
        scrollRes = onJSFrameNodeScrollFrameBegin(scrollRes.offset, state);
    }

    mainDelta = -context->NormalizeToPx(scrollRes.offset);
}

void ScrollablePattern::OnScrollStartRecursive(WeakPtr<NestableScrollContainer> child, float position, float velocity)
{
    OnScrollStartRecursiveInner(child, position, velocity);
    SetNestedScrolling(true);
    SetScrollOriginChild(child);
}

void ScrollablePattern::OnScrollStartRecursiveInner(
    WeakPtr<NestableScrollContainer> child, float position, float velocity)
{
    SetIsNestedInterrupt(false);
    HandleScrollImpl(position, SCROLL_FROM_START);
    auto parent = GetNestedScrollParent();
    auto nestedScroll = GetNestedScroll();
    if (parent && nestedScroll.NeedParent()) {
        parent->OnScrollStartRecursive(child, position, GetVelocity());
    }
}

void ScrollablePattern::OnScrollEndRecursive(const std::optional<float>& velocity)
{
    if (!IsScrollableStopped() && !GetNestedScrolling()) {
        return;
    }
    OnScrollEndRecursiveInner(velocity);
    SetNestedScrolling(false);
    CheckRestartSpring(false);
}

void ScrollablePattern::SetNestedScrolling(bool nestedScrolling)
{
    CHECK_NULL_VOID(scrollableEvent_);
    auto scrollable = scrollableEvent_->GetScrollable();
    CHECK_NULL_VOID(scrollable);
    scrollable->SetNestedScrolling(nestedScrolling);
    // Sliding the touchPad is an axis event, and the parent of the nested scroll cannot respond to TouchDown,
    // so the scrollable animation stops when the nested scroll scroll start.
    if (nestedScrolling) {
        scrollable->StopScrollable();
    }
}

void ScrollablePattern::OnScrollEndRecursiveInner(const std::optional<float>& velocity)
{
    OnScrollEnd();
    auto parent = GetNestedScrollParent();
    auto nestedScroll = GetNestedScroll();
    if (!isScrollToOverAnimation_ && parent && (nestedScroll.NeedParent() || GetIsNestedInterrupt())) {
        parent->OnScrollEndRecursive(velocity);
    }
    isScrollToOverAnimation_ = false;
    SetIsNestedInterrupt(false);
}

void ScrollablePattern::OnScrollDragEndRecursive()
{
    auto parent = GetNestedScrollParent();
    auto nestedScroll = GetNestedScroll();
    if (parent && nestedScroll.NeedParent()) {
        parent->OnScrollDragEndRecursive();
    }
    CheckRestartSpring(false, false);
}

float ScrollablePattern::GetVelocity() const
{
    float velocity = 0.0f;
    CHECK_NULL_RETURN(scrollableEvent_, velocity);
    auto scrollable = scrollableEvent_->GetScrollable();
    CHECK_NULL_RETURN(scrollable, velocity);
    velocity = scrollable->GetCurrentVelocity();
    return velocity;
}

void ScrollablePattern::RegisterScrollingListener(const RefPtr<ScrollingListener> listener)
{
    CHECK_NULL_VOID(listener);
    scrollingListener_.emplace_back(listener);
}

void ScrollablePattern::FireAndCleanScrollingListener()
{
    for (auto listener : scrollingListener_) {
        CHECK_NULL_VOID(listener);
        listener->NotifyScrollingEvent();
    }
    scrollingListener_.clear();
}

void ScrollablePattern::CleanScrollingListener()
{
    scrollingListener_.clear();
}

float ScrollablePattern::GetMainContentSize() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0);
    return geometryNode->GetPaddingSize().MainSize(axis_);
}

void ScrollablePattern::SetBackToTop(bool backToTop)
{
    if (backToTop_ == backToTop) {
        return;
    }
    auto* eventProxy = StatusBarEventProxy::GetInstance();
    if (!eventProxy) {
        TAG_LOGI(AceLogTag::ACE_SCROLLABLE, "StatusBarEventProxy is null");
        return;
    }
    backToTop_ = backToTop;
    if (backToTop_) {
        eventProxy->Register(WeakClaim(this));
    } else {
        eventProxy->UnRegister(WeakClaim(this));
    }
}

void ScrollablePattern::ResetBackToTop()
{
    bool backToTop =
        GetAxis() == Axis::VERTICAL && Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN);
    SetBackToTop(backToTop);
}

void ScrollablePattern::OnStatusBarClick()
{
    if (!backToTop_) {
        return;
    }

    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!pipeline->GetOnShow() || !host->IsActive() || !pipeline->IsWindowFocused()) {
        return;
    }

    bool isActive = true;
    // If any of the parent components is not active while traversing the parent components, do not scroll to the top.
    for (auto parent = host->GetParent(); parent != nullptr; parent = parent->GetParent()) {
        RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(parent);
        if (!frameNode) {
            continue;
        }
        if (!frameNode->IsActive() || !frameNode->IsVisible()) {
            isActive = false;
            break;
        }
    }
    if (!isActive) {
        return;
    }

    isBackToTopRunning_ = true; // set stop animation flag when click status bar.
    AnimateTo(0 - GetContentStartOffset(), -1, nullptr, true);
}

void ScrollablePattern::ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    ACE_SCOPED_TRACE("ScrollToEdge scrollEdgeType:%zu, id:%d, tag:%s", scrollEdgeType,
        static_cast<int32_t>(host->GetAccessibilityId()), host->GetTag().c_str());
    if (scrollEdgeType == ScrollEdgeType::SCROLL_TOP) {
        ScrollToIndex(0, false, ScrollAlign::START);
    } else if (scrollEdgeType == ScrollEdgeType::SCROLL_BOTTOM) {
        // use LAST_ITEM for children count changed after scrollEdge(Edge.Bottom) and before layout
        ScrollToIndex(LAST_ITEM, false, ScrollAlign::END);
    }
}

void ScrollablePattern::Fling(double flingVelocity)
{
    StopScrollableAndAnimate();
    CHECK_NULL_VOID(scrollableEvent_);
    auto scrollable = scrollableEvent_->GetScrollable();
    CHECK_NULL_VOID(scrollable);
    if (IsOutOfBoundary()) {
        scrollable->HandleOverScroll(flingVelocity);
    } else {
        OnScrollStartRecursiveInner(WeakClaim(this), 0.f, flingVelocity);
        scrollable->StartScrollAnimation(0.0f, flingVelocity);
    }
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RequestFrame();
}

void ScrollablePattern::NotifyFRCSceneInfo(const std::string& scene, double velocity, SceneStatus sceneStatus)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->AddFRCSceneInfo(scene, velocity, sceneStatus);
}

void ScrollablePattern::FireOnScrollStart()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(hub);
    SuggestOpIncGroup(true);
    if (scrollStop_ && !GetScrollAbort()) {
        OnScrollStop(hub->GetOnScrollStop(), hub->GetJSFrameNodeOnScrollStop());
    }
    RecordScrollEvent(Recorder::EventType::SCROLL_START);
    UIObserverHandler::GetInstance().NotifyScrollEventStateChange(
        AceType::WeakClaim(this), ScrollEventType::SCROLL_START);
    PerfMonitor::GetPerfMonitor()->StartCommercial(PerfConstants::APP_LIST_FLING, PerfActionType::FIRST_MOVE, "");
    if (GetScrollAbort()) {
        ACE_SCOPED_TRACE("ScrollAbort, no OnScrollStart, id:%d, tag:%s",
            static_cast<int32_t>(host->GetAccessibilityId()), host->GetTag().c_str());
        return;
    }
    auto scrollBar = GetScrollBar();
    if (scrollBar) {
        scrollBar->PlayScrollBarAppearAnimation();
    }
    StopScrollBarAnimatorByProxy();
    host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_START);
    isScrolling_ = true;
    FireObserverOnScrollStart();
    auto onScrollStart = hub->GetOnScrollStart();
    auto onJSFrameNodeScrollStart = hub->GetJSFrameNodeOnScrollStart();
    CHECK_NULL_VOID(onScrollStart || onJSFrameNodeScrollStart);
    ACE_SCOPED_TRACE(
        "OnScrollStart, id:%d, tag:%s", static_cast<int32_t>(host->GetAccessibilityId()), host->GetTag().c_str());
    if (onScrollStart) {
        onScrollStart();
    }
    if (onJSFrameNodeScrollStart) {
        onJSFrameNodeScrollStart();
    }
    AddEventsFiredInfo(ScrollableEventType::ON_SCROLL_START);
}

void ScrollablePattern::OnScrollStartCallback()
{
    FireOnScrollStart();
};

void ScrollablePattern::FireOnScroll(float finalOffset, OnScrollEvent& onScroll) const
{
    auto offsetPX = Dimension(finalOffset);
    auto offsetVP = Dimension(offsetPX.ConvertToVp(), DimensionUnit::VP);
    auto scrollState = GetScrollState();
    bool isTriggered = false;
    if (!NearZero(finalOffset)) {
        onScroll(offsetVP, scrollState);
        isTriggered = true;
    }
    if (scrollStop_ && !GetScrollAbort()) {
        if (scrollState != ScrollState::IDLE || !isTriggered) {
            onScroll(0.0_vp, ScrollState::IDLE);
        }
    }
}

void ScrollablePattern::FireObserverOnTouch(const TouchEventInfo& info)
{
    CHECK_NULL_VOID(positionController_);
    auto touchInfo = info;
    auto observer = positionController_->GetObserver();
    if (observer.onTouchEvent) {
        (*observer.onTouchEvent)(touchInfo);
    }
    auto obsMgr = positionController_->GetObserverManager();
    if (obsMgr) {
        obsMgr->HandleOnTouchEvent(touchInfo);
    }
}

void ScrollablePattern::FireObserverOnReachStart()
{
    CHECK_NULL_VOID(positionController_);
    auto observer = positionController_->GetObserver();
    if (observer.onReachStartEvent) {
        observer.onReachStartEvent();
    }
    auto obsMgr = positionController_->GetObserverManager();
    if (obsMgr) {
        obsMgr->HandleOnReachEvent(false);
    }
}

void ScrollablePattern::FireObserverOnReachEnd()
{
    CHECK_NULL_VOID(positionController_);
    auto observer = positionController_->GetObserver();
    if (observer.onReachEndEvent) {
        observer.onReachEndEvent();
    }
    auto obsMgr = positionController_->GetObserverManager();
    if (obsMgr) {
        obsMgr->HandleOnReachEvent(true);
    }
}

void ScrollablePattern::FireObserverOnScrollStart()
{
    CHECK_NULL_VOID(positionController_);
    auto observer = positionController_->GetObserver();
    if (observer.onScrollStartEvent) {
        observer.onScrollStartEvent();
    }
    auto obsMgr = positionController_->GetObserverManager();
    if (obsMgr) {
        obsMgr->HandleOnScrollStartEvent();
    }
}

void ScrollablePattern::FireObserverOnScrollStop()
{
    CHECK_NULL_VOID(positionController_);
    auto observer = positionController_->GetObserver();
    if (observer.onScrollStopEvent) {
        observer.onScrollStopEvent();
    }
    auto obsMgr = positionController_->GetObserverManager();
    if (obsMgr) {
        obsMgr->HandleOnScrollStopEvent();
    }
}

void ScrollablePattern::FireObserverOnDidScroll(float finalOffset)
{
    OnScrollEvent onScroll = [weak = WeakClaim(this)](Dimension dimension, ScrollState state) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern && pattern->positionController_);
        auto source = pattern->ConvertScrollSource(pattern->scrollSource_);
        bool isAtTop = pattern->IsAtTop();
        bool isAtBottom = pattern->IsAtBottom();
        auto observer = pattern->positionController_->GetObserver();
        if (observer.onDidScrollEvent) {
            observer.onDidScrollEvent(dimension, source, isAtTop, isAtBottom);
        }
        auto obsMgr = pattern->positionController_->GetObserverManager();
        if (obsMgr) {
            obsMgr->HandleOnDidScrollEvent(dimension, source, isAtTop, isAtBottom);
        }
    };
    FireOnScroll(finalOffset, onScroll);
}

void ScrollablePattern::SuggestOpIncGroup(bool flag)
{
    if (!SystemProperties::IsOpIncEnable()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (host->GetSuggestOpIncActivatedOnce()) {
        return;
    }
    flag = flag && isVertical();
    if (flag) {
        ACE_SCOPED_TRACE("SuggestOpIncGroup %s", host->GetHostTag().c_str());
        auto parent = host->GetAncestorNodeOfFrame(false);
        CHECK_NULL_VOID(parent);
        parent->SetSuggestOpIncActivatedOnce();
        // get 1st layer
        std::string path("\\>");
        host->FindSuggestOpIncNode(path, host->GetGeometryNode()->GetFrameSize(), 0);
    }
}

void ScrollablePattern::OnScrollStop(
    const OnScrollStopEvent& onScrollStop, const OnScrollStopEvent& onJSFrameNodeScrollStop)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!scrollStop_) {
        return;
    }
    auto pipeline = host->GetContext();
    RecordScrollEvent(Recorder::EventType::SCROLL_STOP);
    UIObserverHandler::GetInstance().NotifyScrollEventStateChange(
        AceType::WeakClaim(this), ScrollEventType::SCROLL_STOP);
    if (!GetScrollAbort()) {
        if (host != nullptr) {
            host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
        }
        isScrolling_ = false;
        FireObserverOnScrollStop();
        FireOnScrollStop(onScrollStop, onJSFrameNodeScrollStop);
        auto scrollBar = GetScrollBar();
        if (scrollBar) {
            scrollBar->ScheduleDisappearDelayTask();
        }
        StartScrollBarAnimatorByProxy();
        if (pipeline && pipeline->GetTaskExecutor() && pipeline->GetTHPExtraManager()) {
            auto taskExecutor = pipeline->GetTaskExecutor();
            const uint32_t delay = 100; // 100: ms
            taskExecutor->RemoveTask(TaskExecutor::TaskType::UI, "NotifyResponseRegionChanged");
            auto task = [weak = WeakClaim(pipeline)]() {
                auto pipeline = weak.Upgrade();
                CHECK_NULL_VOID(pipeline);
                pipeline->NotifyResponseRegionChanged(pipeline->GetRootElement());
            };
            taskExecutor->PostDelayedTask(task, TaskExecutor::TaskType::UI, delay, "NotifyResponseRegionChanged");
        }
        SetUiDvsyncSwitch(false);
    } else {
        ACE_SCOPED_TRACE("ScrollAbort, no OnScrollStop, id:%d, tag:%s",
            static_cast<int32_t>(host->GetAccessibilityId()), host->GetTag().c_str());
    }
    if (pipeline) {
        pipeline->GetFocusManager()->SetNeedTriggerScroll(false);
    }
    PerfMonitor::GetPerfMonitor()->EndCommercial(PerfConstants::APP_LIST_FLING, false);
    AceAsyncTraceEndCommercial(host->GetAccessibilityId(),
        (TRAILING_ANIMATION + std::to_string(host->GetAccessibilityId()) + std::string(" ") + host->GetTag()).c_str());
    scrollStop_ = false;
    SetScrollAbort(false);
}

void ScrollablePattern::FireOnScrollStop(const OnScrollStopEvent& onScrollStop,
    const OnScrollStopEvent& onJSFrameNodeScrollStop)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    ACE_SCOPED_TRACE("OnScrollStop, id:%d, tag:%s", static_cast<int32_t>(host->GetAccessibilityId()),
        host->GetTag().c_str());
    if (onScrollStop) {
        onScrollStop();
    }
    if (onJSFrameNodeScrollStop) {
        onJSFrameNodeScrollStop();
    }
    AddEventsFiredInfo(ScrollableEventType::ON_SCROLL_STOP);
    SetScrollSource(SCROLL_FROM_NONE);
    ResetLastSnapTargetIndex();
    ResetScrollableSnapDirection();
}

void ScrollablePattern::RecordScrollEvent(Recorder::EventType eventType)
{
    if (!Recorder::EventRecorder::Get().IsRecordEnable(Recorder::EventCategory::CATEGORY_SCROLL)) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto offset = GetTotalOffset();
    Recorder::EventParamsBuilder builder;
    builder.SetEventCategory(Recorder::EventCategory::CATEGORY_SCROLL)
        .SetEventType(eventType)
        .SetId(host->GetInspectorIdValue(""))
        .SetType(host->GetHostTag())
        .SetHost(host)
        .SetExtra(Recorder::KEY_CURRENT_OFFSET, std::to_string(offset))
        .SetDescription(host->GetAutoEventParamValue(""));
    if (eventType == Recorder::EventType::SCROLL_START) {
        scrollStartOffset_ = GetTotalOffset();
    } else if (eventType == Recorder::EventType::SCROLL_STOP) {
        auto distance = offset - scrollStartOffset_;
        builder.SetExtra(Recorder::KEY_DISTANCE, std::to_string(distance));
    }
    Recorder::EventRecorder::Get().OnEvent(std::move(builder));
}

float ScrollablePattern::FireOnWillScroll(float offset) const
{
    auto eventHub = GetEventHub<ScrollableEventHub>();
    CHECK_NULL_RETURN(eventHub, offset);
    auto onScroll = eventHub->GetOnWillScroll();
    auto onJSFrameNodeScroll = eventHub->GetJSFrameNodeOnWillScroll();
    CHECK_NULL_RETURN(onScroll || onJSFrameNodeScroll, offset);
    auto offsetPX = Dimension(offset);
    auto offsetVP = Dimension(offsetPX.ConvertToVp(), DimensionUnit::VP);
    ScrollFrameResult scrollRes = { .offset = offsetVP};
    if (onScroll) {
        scrollRes = onScroll(scrollRes.offset, GetScrollState(), ConvertScrollSource(scrollSource_));
    }
    if (onJSFrameNodeScroll) {
        scrollRes =  onJSFrameNodeScroll(scrollRes.offset, GetScrollState(), ConvertScrollSource(scrollSource_));
    }
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(context, offset);
    return context->NormalizeToPx(scrollRes.offset);
}

/**
 * @description: Register with the drag drop manager
 * @return None
 */
void ScrollablePattern::Register2DragDropManager()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    DragPreviewOption dragPreviewOption = host->GetDragPreviewOption();
    bool enableEdgeAutoScroll = dragPreviewOption.enableEdgeAutoScroll;
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    if (enableEdgeAutoScroll) {
        dragDropManager->RegisterDragStatusListener(host->GetId(), AceType::WeakClaim(AceType::RawPtr(host)));
    } else {
        StopHotzoneScroll();
        dragDropManager->UnRegisterDragStatusListener(host->GetId());
    }
}

/**
 * @description: Determine whether it is in the hot zone, then
 * 1.Gives the rolling direction according to the location of the hot zone
 * 2.Gives the distance from the edge of the hot zone from the drag point
 * @param {PointF&} point The drag point
 * @return The distance from the edge of the hot zone from the drag point.scroll up:Offset percent is positive, scroll
 * down:Offset percent is  negative
 */
float ScrollablePattern::IsInHotZone(const PointF& point)
{
    auto host = GetHost();
    auto offset = 0.f;
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.f);

    auto wholeRect = geometryNode->GetFrameRect();
    wholeRect.SetOffset(host->GetTransformRelativeOffset());
    auto hotZoneHeightPX = HOT_ZONE_HEIGHT_VP_DIM.ConvertToPx();
    auto hotZoneWidthPX = HOT_ZONE_WIDTH_VP_DIM.ConvertToPx();
    if (isVertical()) {
        // create top hot zone,it is a rectangle
        auto topHotzone = wholeRect;
        topHotzone.SetHeight(hotZoneHeightPX);

        // create bottom hot zone,it is a rectangle
        auto bottomHotzone = wholeRect;
        auto bottomZoneEdgeY = wholeRect.GetY() + wholeRect.Height();
        bottomHotzone.SetTop(bottomZoneEdgeY - hotZoneHeightPX);
        bottomHotzone.SetHeight(hotZoneHeightPX);

        // Determines whether the drag point is within the hot zone,
        // then gives the scroll component movement direction according to which hot zone the point is in
        // top or bottom hot zone
        if (topHotzone.IsInRegion(point)) {
            offset = hotZoneHeightPX - point.GetY() + topHotzone.GetY();
            if (!NearZero(hotZoneHeightPX)) {
                return offset / hotZoneHeightPX;
            }
        } else if (bottomHotzone.IsInRegion(point)) {
            offset = bottomZoneEdgeY - point.GetY() - hotZoneHeightPX;
            if (!NearZero(hotZoneHeightPX)) {
                return offset / hotZoneHeightPX;
            }
        }
    } else {
        auto leftHotzone = wholeRect;

        // create left hot zone,it is a rectangle
        leftHotzone.SetWidth(hotZoneWidthPX);

        // create right hot zone,it is a rectangle
        auto rightHotzone = wholeRect;
        rightHotzone.SetWidth(hotZoneWidthPX);
        auto rightZoneEdgeX = wholeRect.GetX() + wholeRect.Width();
        rightHotzone.SetLeft(rightZoneEdgeX - hotZoneWidthPX);

        // Determines whether the drag point is within the hot zone,
        // gives the scroll component movement direction according to which hot zone the point is in
        // left or right hot zone
        if (leftHotzone.IsInRegion(point)) {
            offset = hotZoneWidthPX - point.GetX() + wholeRect.GetX();
            if (!NearZero(hotZoneWidthPX)) {
                return offset / hotZoneWidthPX;
            }
        } else if (rightHotzone.IsInRegion(point)) {
            offset = rightZoneEdgeX - point.GetX() - hotZoneWidthPX;
            if (!NearZero(hotZoneWidthPX)) {
                return offset / hotZoneWidthPX;
            }
        }
    }

    return 0.f;
}

/**
 * @description: Determines whether the scroll component is in the vertical direction
 * @return True,If the scrolling component is vertical
 */
bool ScrollablePattern::isVertical() const
{
    return axis_ == Axis::VERTICAL;
}

/**
 * @description: scroll up or down
 * @param {float} offsetPct offset percent.When scrolling in the vertical or horizontal direction, there is a distance
 * between the drag point and the outer edge of the hot zone, and the percentage represents the proportion of this
 * distance to the height or width of the hot zone
 * @return None
 */
void ScrollablePattern::HotZoneScroll(const float offsetPct)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host && IsScrollable() && !NearZero(offsetPct));

    // There are three types of situations to consider.
    // 1. Enter the hot zone for the first time.
    // 2. When the drag point leaves the hot zone, it enters the hot zone again
    // 3. When the drag point moves within the hot zone, the hot zone offset changes
    CHECK_NULL_VOID(!NearEqual(lastHonezoneOffsetPct_, offsetPct));

    if (AnimateRunning()) {
        // Variable speed rolling
        // When the drag point is in the hot zone, and the hot zone offset changes.
        // Then need to modify the offset percent
        if (velocityMotion_) {
            velocityMotion_->Reset(offsetPct);
        }
        return;
    }

    if (!animator_) {
        auto context = host->GetContextRefPtr();
        CHECK_NULL_VOID(context);
        animator_ = CREATE_ANIMATOR(context);
        animator_->AddStopListener([weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->AddHotZoneSenceInterface(SceneStatus::END);
            pattern->OnAnimateStop();
        });
        animator_->AddStartListener([weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->AddHotZoneSenceInterface(SceneStatus::START);
        });
    }

    if (!velocityMotion_) {
        // Enter the hot zone for the first time.
        velocityMotion_ = AceType::MakeRefPtr<BezierVariableVelocityMotion>(
            offsetPct, [weak = WeakClaim(this)](float offset) -> bool {
                auto pattern = weak.Upgrade();
                CHECK_NULL_RETURN(pattern, true);
                // Stop scrolling when reach the bottom or top
                return ((LessNotEqual(offset, 0) && pattern->IsAtBottom()) ||
                    (GreatNotEqual(offset, 0) && pattern->IsAtTop()));
            });
        velocityMotion_->AddListener([weakScroll = AceType::WeakClaim(this)](double offset) {
            // Get the distance component need to roll from BezierVariableVelocityMotion
            // Roll up: negative value, Roll up: positive value
            auto pattern = weakScroll.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->UpdateCurrentOffset(offset, SCROLL_FROM_AXIS);
            pattern->UpdateMouseStart(offset);
            pattern->AddHotZoneSenceInterface(SceneStatus::RUNNING);
            if (pattern->hotZoneScrollCallback_) {
                pattern->hotZoneScrollCallback_();
            }
        });
        velocityMotion_->ReInit(offsetPct);
    } else {
        // When the drag point leaves the hot zone, it enters the hot zone again.Then need to reset offset percent.
        velocityMotion_->ReInit(offsetPct);
    }
    // Save the last offset percent
    lastHonezoneOffsetPct_ = offsetPct;
    animator_->PlayMotion(velocityMotion_);
    FireOnScrollStart();
}

/**
 * @description: When the drag point leaves the hot zone, stop the animation.
 * @return None
 */
void ScrollablePattern::StopHotzoneScroll()
{
    if (!AnimateStoped()) {
        animator_->Stop();
    }
}

/**
 * @description: Handle drag and drop events
 * When a drag point enters or moves over a component, determine whether it is within the hot zone.
 * When leave the component, stop scrolling
 * @param {DragEventType&} dragEventType Drag the event type
 * @param {NotifyDragEvent&} notifyDragEvent Drag event
 * @return None
 */
void ScrollablePattern::HandleHotZone(
    const DragEventType& dragEventType, const RefPtr<NotifyDragEvent>& notifyDragEvent)
{
    // The starting version of the auto-scroll feature is 11
    CHECK_NULL_VOID(Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN));
    PointF point(static_cast<float>(notifyDragEvent->GetX()), static_cast<float>(notifyDragEvent->GetY()));
    switch (dragEventType) {
        case DragEventType::ENTER: {
            HandleMoveEventInComp(point);
            break;
        }
        case DragEventType::MOVE: {
            HandleMoveEventInComp(point);
            break;
        }
        case DragEventType::DROP:
        case DragEventType::LEAVE: {
            HandleLeaveHotzoneEvent();
            break;
        }
        default:
            break;
    }
}

/**
 * @description:When a drag point is inside the scroll component, it is necessary to handle the events of each moving
 * point
 * @param {PointF&} point the drag point
 * @return None
 */
void ScrollablePattern::HandleMoveEventInComp(const PointF& point)
{
    float offsetPct = IsInHotZone(point);
    if ((Positive(offsetPct) && !IsAtTop()) || (Negative(offsetPct) && !IsAtBottom())) {
        // The drag point enters the hot zone
        HotZoneScroll(offsetPct);
    } else {
        // Although it entered the rolling component, it is not in the rolling component hot zone.Then stop
        // scrolling
        HandleLeaveHotzoneEvent();
    }
}

/**
 * @description:When the drag point is not in the hot zone, need to stop scrolling, if it exists.
 * This function is executed multiple times
 * @return None
 */
void ScrollablePattern::HandleLeaveHotzoneEvent()
{
    // Stop scrolling up and down
    StopHotzoneScroll();
}

/**
 * @description: This is the entry point for handling drag events
 * @return None
 */
void ScrollablePattern::HandleOnDragStatusCallback(
    const DragEventType& dragEventType, const RefPtr<NotifyDragEvent>& notifyDragEvent)
{
    HandleHotZone(dragEventType, notifyDragEvent);
}

/**
 * @description: Cancel registration with the drag drop manager
 * @return None
 */
void ScrollablePattern::UnRegister2DragDropManager(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->UnRegisterDragStatusListener(frameNode->GetId());
}

bool ScrollablePattern::NeedCoordinateScrollWithNavigation(
    double offset, int32_t source, const OverScrollOffset& overOffsets)
{
    if (!navBarPattern_) {
        return false;
    }
    return (GreatNotEqual(overOffsets.start, 0.0) || navBarPattern_->CanCoordScrollUp(offset)) &&
           (axis_ == Axis::VERTICAL) && (source != SCROLL_FROM_ANIMATION_SPRING);
}

void ScrollablePattern::AddHotZoneSenceInterface(SceneStatus scene)
{
    CHECK_NULL_VOID(velocityMotion_);
    auto velocity = velocityMotion_->GetCurrentVelocity();
    NotifyFRCSceneInfo(SCROLL_IN_HOTZONE_SCENE, velocity, scene);
}

void ScrollablePattern::OnCollectClickTarget(const OffsetF& coordinateOffset,
    const GetEventTargetImpl& getEventTargetImpl, TouchTestResult& result, const RefPtr<FrameNode>& frameNode,
    const RefPtr<TargetComponent>& targetComponent, ResponseLinkResult& responseLinkResult)
{
    CHECK_NULL_VOID(GetScrollBar());
    if (clickRecognizer_) {
        clickRecognizer_->SetCoordinateOffset(Offset(coordinateOffset.GetX(), coordinateOffset.GetY()));
        clickRecognizer_->SetGetEventTargetImpl(getEventTargetImpl);
        clickRecognizer_->SetNodeId(frameNode->GetId());
        clickRecognizer_->AttachFrameNode(frameNode);
        clickRecognizer_->SetTargetComponent(targetComponent);
        clickRecognizer_->SetIsSystemGesture(true);
        clickRecognizer_->SetRecognizerType(GestureTypeName::CLICK);
        clickRecognizer_->SetSysGestureJudge(
            [weak = AceType::WeakClaim(AceType::RawPtr(scrollBar_)), this](const RefPtr<GestureInfo>& gestureInfo,
                const std::shared_ptr<BaseGestureEvent>&) -> GestureJudgeResult {
                const auto& inputEventType = gestureInfo->GetInputEventType();
                TAG_LOGI(AceLogTag::ACE_SCROLL_BAR, "input event type:%{public}d", inputEventType);
                auto scrollBar = weak.Upgrade();
                CHECK_NULL_RETURN(scrollBar, GestureJudgeResult::REJECT);
                Point point(locationInfo_.GetX(), locationInfo_.GetY());
                if (inputEventType == InputEventType::MOUSE_BUTTON && scrollBar->InBarRectRegion(point)) {
                    return GestureJudgeResult::CONTINUE;
                }
                return GestureJudgeResult::REJECT;
            });
        result.emplace_front(clickRecognizer_);
        responseLinkResult.emplace_back(clickRecognizer_);
    }
}

void ScrollablePattern::InitScrollBarClickEvent()
{
    clickRecognizer_ = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer_->SetOnClick([weakBar = AceType::WeakClaim(this)](const ClickInfo&) {
        auto scrollBar = weakBar.Upgrade();
        if (scrollBar) {
            scrollBar->HandleClickEvent();
        }
    });
}

void ScrollablePattern::HandleClickEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(GetScrollBar());
    Point point(locationInfo_.GetX(), locationInfo_.GetY());
    bool reverse = false;
    if (scrollBar_->AnalysisUpOrDown(point, reverse) && isMousePressed_) {
        ScrollPage(reverse, true);
    }
}

void ScrollablePattern::ScrollPage(bool reverse, bool smooth, AccessibilityScrollType scrollType)
{
    float distance = reverse ? GetMainContentSize() : -GetMainContentSize();
    if (scrollType == AccessibilityScrollType::SCROLL_HALF) {
        distance = distance / 2.f;
    }
    if (smooth) {
        float position = -GetTotalOffset() + distance;
        AnimateTo(-position, -1, nullptr, true, false, false);
    } else {
        StopAnimate();
        UpdateCurrentOffset(distance, SCROLL_FROM_JUMP);
    }
}

void ScrollablePattern::InitScrollBarMouseEvent()
{
    CHECK_NULL_VOID(!mouseEvent_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inputHub = GetInputHub();
    CHECK_NULL_VOID(inputHub);
    auto mouseTask = [weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (info.GetButton() == MouseButton::LEFT_BUTTON &&
            (info.GetAction() == MouseAction::PRESS || info.GetAction() == MouseAction::MOVE)) {
            pattern->isMousePressed_ = true;
        } else {
            pattern->isMousePressed_ = false;
        }
        pattern->locationInfo_ = info.GetLocalLocation();
    };
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnMouseEvent(mouseEvent_);
}

void ScrollablePattern::PrintOffsetLog(AceLogTag tag, int32_t id, double finalOffset)
{
    if (SystemProperties::GetDebugOffsetLogEnabled() && !NearZero(finalOffset)) {
        TAG_LOGD(tag, "Scrollable id:%{public}d, scrollSource:%{public}d, scrollOffset:%{public}f",
            id, scrollSource_, finalOffset);
    }
}

PositionMode ScrollablePattern::GetPositionMode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, PositionMode::RIGHT);
    auto positionMode = PositionMode::RIGHT;
    if (axis_ == Axis::HORIZONTAL) {
        positionMode = PositionMode::BOTTOM;
    } else {
        auto isRtl = host->GetLayoutProperty()->GetNonAutoLayoutDirection() == TextDirection::RTL;
        if (isRtl) {
            positionMode = PositionMode::LEFT;
        }
    }
    return positionMode;
}

void ScrollablePattern::ScrollAtFixedVelocity(float velocity)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (AnimateRunning()) {
        StopAnimate();
    }

    if (!animator_) {
        auto context = host->GetContextRefPtr();
        CHECK_NULL_VOID(context);
        animator_ = CREATE_ANIMATOR(context);
        animator_->AddStopListener([weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnAnimateStop();
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            AceAsyncTraceEnd(host->GetAccessibilityId(),
                (SCROLLER_FIX_VELOCITY_ANIMATION + std::to_string(host->GetAccessibilityId()) + std::string(" ") +
                    host->GetTag()).c_str());
        });
    }

    if (!fixedVelocityMotion_) {
        fixedVelocityMotion_ = AceType::MakeRefPtr<VelocityMotion>([weak = WeakClaim(this)](float offset) -> bool {
            auto pattern = weak.Upgrade();
            CHECK_NULL_RETURN(pattern, true);
            if (LessNotEqual(offset, 0) && pattern->IsAtBottom()) {
                // Stop scrolling when reach the bottom
                pattern->fixedVelocityMotion_->Init();
                return true;
            } else if (GreatNotEqual(offset, 0) && pattern->IsAtTop()) {
                // Stop scrolling when reach the top
                pattern->fixedVelocityMotion_->Init();
                return true;
            }
            return false;
        });
        fixedVelocityMotion_->AddListener([weakScroll = AceType::WeakClaim(this)](double offset) {
            auto pattern = weakScroll.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->UpdateCurrentOffset(offset, SCROLL_FROM_ANIMATION_CONTROLLER);
        });
        fixedVelocityMotion_->SetVelocity(velocity);
    } else {
        fixedVelocityMotion_->Init();
        fixedVelocityMotion_->SetVelocity(velocity);
    }
    AceAsyncTraceBegin(
        host->GetAccessibilityId(), (SCROLLER_FIX_VELOCITY_ANIMATION + std::to_string(host->GetAccessibilityId()) +
                                        std::string(" ") + host->GetTag()).c_str());
    animator_->PlayMotion(fixedVelocityMotion_);
    FireOnScrollStart();
}

void ScrollablePattern::CheckRestartSpring(bool sizeDiminished, bool needNestedScrolling)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto edgeEffect = GetScrollEdgeEffect();
    if (!edgeEffect || !edgeEffect->IsSpringEffect()) {
        return;
    }
    // Check if need update Spring when itemTotalSize diminishes.
    if (IsScrollableSpringMotionRunning() && sizeDiminished) {
        ACE_SCOPED_TRACE("CheckRestartSpring, do ProcessSpringUpdate, id:%d, tag:%s",
            static_cast<int32_t>(host->GetAccessibilityId()), host->GetTag().c_str());
        edgeEffect->ProcessSpringUpdate();
        return;
    }
    if (AnimateRunning() || !IsOutOfBoundary()) {
        return;
    }
    if (needNestedScrolling && !ScrollableIdle()) {
        return;
    }
    if (!needNestedScrolling && !IsScrollableAnimationNotRunning()) {
        return;
    }
    FireOnScrollStart();
    ACE_SCOPED_TRACE("CheckRestartSpring, do ProcessScrollOver, id:%d, tag:%s",
        static_cast<int32_t>(host->GetAccessibilityId()), host->GetTag().c_str());
    edgeEffect->ProcessScrollOver(0);
}

void ScrollablePattern::AddEventsFiredInfo(ScrollableEventType eventType)
{
    if (eventsFiredInfos_.size() >= EVENTS_FIRED_INFO_COUNT) {
        eventsFiredInfos_.pop_front();
    }
    eventsFiredInfos_.push_back(ScrollableEventsFiredInfo({
        .eventFiredTime_ = GetSysTimestamp(),
        .eventType_ = eventType,
        .scrollSource_ = scrollSource_,
    }));
}

void ScrollablePattern::AddScrollableFrameInfo(int32_t scrollSource)
{
    if (scrollableFrameInfos_.size() >= SCROLLABLE_FRAME_INFO_COUNT) {
        scrollableFrameInfos_.pop_front();
    }
    uint32_t canOverScrollInfo = IsScrollableSpringEffect();
    canOverScrollInfo = (canOverScrollInfo << 1) | IsScrollable();
    canOverScrollInfo = (canOverScrollInfo << 1) | ScrollableIdle();
    canOverScrollInfo = (canOverScrollInfo << 1) | animateOverScroll_;
    canOverScrollInfo = (canOverScrollInfo << 1) | animateCanOverScroll_;
    scrollableFrameInfos_.push_back(ScrollableFrameInfo({
        .scrollStateTime_ = GetSysTimestamp(),
        .scrollState_ = scrollSource,
        .canOverScroll_ = lastCanOverScroll_,
        .canOverScrollInfo_ = canOverScrollInfo,
    }));
}

void ScrollablePattern::GetEdgeEffectDumpInfo()
{
    switch (edgeEffect_) {
        case EdgeEffect::NONE: {
            DumpLog::GetInstance().AddDesc("edgeEffect: NONE");
            break;
        }
        case EdgeEffect::SPRING: {
            DumpLog::GetInstance().AddDesc("edgeEffect: SPRING");
            break;
        }
        case EdgeEffect::FADE: {
            DumpLog::GetInstance().AddDesc("edgeEffect: FADE");
            break;
        }
        default: {
            break;
        }
    }
}

void ScrollablePattern::GetAxisDumpInfo()
{
    switch (axis_) {
        case Axis::NONE: {
            DumpLog::GetInstance().AddDesc("Axis: NONE");
            break;
        }
        case Axis::VERTICAL: {
            DumpLog::GetInstance().AddDesc("Axis: VERTICAL");
            break;
        }
        case Axis::HORIZONTAL: {
            DumpLog::GetInstance().AddDesc("Axis: HORIZONTAL");
            break;
        }
        case Axis::FREE: {
            DumpLog::GetInstance().AddDesc("Axis: FREE");
            break;
        }
        default: {
            break;
        }
    }
}

void ScrollablePattern::GetPanDirectionDumpInfo()
{
    switch (GetScrollablePanDirection()) {
        case Axis::NONE: {
            DumpLog::GetInstance().AddDesc("ScrollablePanDirection:NONE");
            break;
        }
        case Axis::VERTICAL: {
            DumpLog::GetInstance().AddDesc("ScrollablePanDirection:VERTICAL");
            break;
        }
        case Axis::HORIZONTAL: {
            DumpLog::GetInstance().AddDesc("ScrollablePanDirection:HORIZONTAL");
            break;
        }
        case Axis::FREE: {
            DumpLog::GetInstance().AddDesc("ScrollablePanDirection:FREE");
            break;
        }
        default: {
            DumpLog::GetInstance().AddDesc("ScrollablePanDirection is null");
            break;
        }
    }
}

void ScrollablePattern::GetPaintPropertyDumpInfo()
{
    auto paintProperty = GetPaintProperty<ScrollablePaintProperty>();
    if (paintProperty) {
        switch (paintProperty->GetScrollBarMode().value_or(DisplayMode::OFF)) {
            case DisplayMode::OFF: {
                DumpLog::GetInstance().AddDesc("innerScrollBarState: OFF");
                break;
            }
            case DisplayMode::AUTO: {
                DumpLog::GetInstance().AddDesc("innerScrollBarState: AUTO");
                break;
            }
            case DisplayMode::ON: {
                DumpLog::GetInstance().AddDesc("innerScrollBarState: ON");
                break;
            }
            default: {
                break;
            }
        }
        auto scrollBarWidth = paintProperty->GetScrollBarWidth();
        scrollBarWidth.has_value() ? DumpLog::GetInstance().AddDesc(std::string("scrollBarWidth: ")
            .append(paintProperty->GetScrollBarWidth().value().ToString()))
            : DumpLog::GetInstance().AddDesc("scrollBarWidth: None");
    }
}

void ScrollablePattern::GetEventDumpInfo()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(hub);
    auto onScrollStart = hub->GetOnScrollStart();
    onScrollStart ? DumpLog::GetInstance().AddDesc("hasOnScrollStart: true")
                  : DumpLog::GetInstance().AddDesc("hasOnScrollStart: false");
    auto onJSFrameNodeScrollStart = hub->GetJSFrameNodeOnScrollStart();
    onJSFrameNodeScrollStart ? DumpLog::GetInstance().AddDesc("hasFrameNodeOnScrollStart: true")
                             : DumpLog::GetInstance().AddDesc("hasFrameNodeOnScrollStart: false");
    auto onScrollStop = hub->GetOnScrollStop();
    onScrollStop ? DumpLog::GetInstance().AddDesc("hasOnScrollStop: true")
                 : DumpLog::GetInstance().AddDesc("hasOnScrollStop: false");
    auto onJSFrameNodeScrollStop = hub->GetJSFrameNodeOnScrollStop();
    onJSFrameNodeScrollStop ? DumpLog::GetInstance().AddDesc("hasFrameNodeOnScrollStop: true")
                            : DumpLog::GetInstance().AddDesc("hasFrameNodeOnScrollStop: false");
    auto scrollHub = host->GetEventHub<ScrollEventHub>();
    if (scrollHub) {
        auto onWillScroll = scrollHub->GetOnWillScrollEvent();
        onWillScroll ? DumpLog::GetInstance().AddDesc("hasOnWillScroll: true")
                     : DumpLog::GetInstance().AddDesc("hasOnWillScroll: false");
        auto onJSFrameNodeScrollWillScroll = scrollHub->GetJSFrameNodeOnScrollWillScroll();
        onJSFrameNodeScrollWillScroll ? DumpLog::GetInstance().AddDesc("hasFrameNodeOnWillScroll: true")
                                      : DumpLog::GetInstance().AddDesc("hasFrameNodeOnWillScroll: false");
        auto onDidScroll = scrollHub->GetOnDidScrollEvent();
        onDidScroll ? DumpLog::GetInstance().AddDesc("hasOnDidScroll: true")
                    : DumpLog::GetInstance().AddDesc("hasOnDidScroll: false");
        auto onJSFrameNodeScrollDidScroll = scrollHub->GetJSFrameNodeOnScrollDidScroll();
        onJSFrameNodeScrollDidScroll ? DumpLog::GetInstance().AddDesc("hasFrameNodeOnDidScroll: true")
                                     : DumpLog::GetInstance().AddDesc("hasFrameNodeOnDidScroll: false");
    } else {
        auto onWillScroll = hub->GetOnWillScroll();
        onWillScroll ? DumpLog::GetInstance().AddDesc("hasOnWillScroll: true")
                     : DumpLog::GetInstance().AddDesc("hasOnWillScroll: false");
        auto onJSFrameNodeWillScroll = hub->GetJSFrameNodeOnWillScroll();
        onJSFrameNodeWillScroll ? DumpLog::GetInstance().AddDesc("hasFrameNodeOnWillScroll: true")
                                : DumpLog::GetInstance().AddDesc("hasFrameNodeOnWillScroll: false");
        auto onDidScroll = hub->GetOnDidScroll();
        onDidScroll ? DumpLog::GetInstance().AddDesc("hasOnDidScroll: true")
                    : DumpLog::GetInstance().AddDesc("hasOnDidScroll: false");
        auto onJSFrameNodeDidScroll = hub->GetJSFrameNodeOnDidScroll();
        onJSFrameNodeDidScroll ? DumpLog::GetInstance().AddDesc("hasFrameNodeOnDidScroll: true")
                               : DumpLog::GetInstance().AddDesc("hasFrameNodeOnDidScroll: false");
    }
    auto onScrollFrameBegin = hub->GetOnScrollFrameBegin();
    onScrollFrameBegin ? DumpLog::GetInstance().AddDesc("hasOnScrollFrameBegin: true")
                       : DumpLog::GetInstance().AddDesc("hasOnScrollFrameBegin: false");
    auto onJSFrameNodeScrollFrameBegin = hub->GetJSFrameNodeOnScrollFrameBegin();
    onJSFrameNodeScrollFrameBegin ? DumpLog::GetInstance().AddDesc("hasFrameNodeOnScrollFrameBegin: true")
                                  : DumpLog::GetInstance().AddDesc("hasFrameNodeOnScrollFrameBegin: false");
    auto onReachStart = hub->GetOnReachStart();
    onReachStart ? DumpLog::GetInstance().AddDesc("hasOnReachStart: true")
                 : DumpLog::GetInstance().AddDesc("hasOnReachStart: false");
    auto onJSFrameNodeReachStart = hub->GetJSFrameNodeOnReachStart();
    onJSFrameNodeReachStart ? DumpLog::GetInstance().AddDesc("hasFrameNodeOnReachStart: true")
                            : DumpLog::GetInstance().AddDesc("hasFrameNodeOnReachStart: false");
    auto onReachEnd = hub->GetOnReachEnd();
    onReachEnd ? DumpLog::GetInstance().AddDesc("hasOnReachEnd: true")
               : DumpLog::GetInstance().AddDesc("hasOnReachEnd: false");
    auto onJSFrameNodeReachEnd = hub->GetJSFrameNodeOnReachEnd();
    onJSFrameNodeReachEnd ? DumpLog::GetInstance().AddDesc("hasFrameNodeOnReachEnd: true")
                          : DumpLog::GetInstance().AddDesc("hasFrameNodeOnReachEnd: false");
}

void ScrollablePattern::DumpAdvanceInfo()
{
    GetEdgeEffectDumpInfo();
    edgeEffectAlwaysEnabled_ ? DumpLog::GetInstance().AddDesc("edgeEffectAlwaysEnabled: true")
                             : DumpLog::GetInstance().AddDesc("edgeEffectAlwaysEnabled: false");
    IsScrollable() ? DumpLog::GetInstance().AddDesc("isScrollable: true")
                   : DumpLog::GetInstance().AddDesc("isScrollable: false");
    GetEventDumpInfo();
    DumpLog::GetInstance().AddDesc(GetNestedScroll().ToString().c_str());
    GetIsSearchRefresh() ? DumpLog::GetInstance().AddDesc(std::string("isSearchRefresh: true"))
                         : DumpLog::GetInstance().AddDesc(std::string("isSearchRefresh: false"));
    GetIsFixedNestedScrollMode() ? DumpLog::GetInstance().AddDesc(std::string("isFixedNestedScrollMode: true"))
                                 : DumpLog::GetInstance().AddDesc(std::string("isFixedNestedScrollMode: false"));
    auto parent = GetNestedScrollParent();
    parent && parent->GetHost() ? DumpLog::GetInstance().AddDesc(std::string("nestedScrollParent id: ")
                                                                     .append(std::to_string(parent->GetHost()->GetId()))
                                                                     .append(" tag: ")
                                                                     .append(parent->GetHost()->GetTag()))
                                : DumpLog::GetInstance().AddDesc("nestedScrollParent is null");
    GetAxisDumpInfo();
    GetPanDirectionDumpInfo();
    GetPaintPropertyDumpInfo();
    GetScrollEnabled() ? DumpLog::GetInstance().AddDesc("enableScrollInteraction: true")
                       : DumpLog::GetInstance().AddDesc("enableScrollInteraction: false");
    DumpLog::GetInstance().AddDesc(std::string("friction: ").append(std::to_string(friction_)));
    DumpLog::GetInstance().AddDesc(std::string("flingSpeedLimit: ").append(std::to_string(GetMaxFlingVelocity())));
    DumpLog::GetInstance().AddDesc("==========================eventsFiredInfos==============================");
    for (const auto& info : eventsFiredInfos_) {
        DumpLog::GetInstance().AddDesc(info.ToString());
    }
    DumpLog::GetInstance().AddDesc("==========================eventsFiredInfos==============================");
    DumpLog::GetInstance().AddDesc("==========================scrollableFrameInfos==========================");
    for (const auto& info : scrollableFrameInfos_) {
        DumpLog::GetInstance().AddDesc(info.ToString());
    }
    DumpLog::GetInstance().AddDesc("==========================scrollableFrameInfos==========================");
    DumpLog::GetInstance().AddDesc("==========================inner ScrollBar===============================");
    if (scrollBar_) {
        scrollBar_->DumpAdvanceInfo();
    } else {
        DumpLog::GetInstance().AddDesc("inner ScrollBar is null");
    }
    DumpLog::GetInstance().AddDesc("==========================inner ScrollBar===============================");
}

void ScrollablePattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionScrollForward([weakPtr = WeakClaim(this)](AccessibilityScrollType scrollType) {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        ACE_SCOPED_TRACE("accessibility action, scroll forward, isScrollable:%u, scrollType:%d, id:%d, tag:%s",
            pattern->IsScrollable(), scrollType, static_cast<int32_t>(host->GetAccessibilityId()),
            host->GetTag().c_str());
        CHECK_NULL_VOID(pattern->IsScrollable());
        pattern->ScrollPage(false, true, scrollType);
    });

    accessibilityProperty->SetActionScrollBackward([weakPtr = WeakClaim(this)](AccessibilityScrollType scrollType) {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        ACE_SCOPED_TRACE("accessibility action, scroll backward, isScrollable:%u, scrollType:%d, id:%d, tag:%s",
            pattern->IsScrollable(), scrollType, static_cast<int32_t>(host->GetAccessibilityId()),
            host->GetTag().c_str());
        CHECK_NULL_VOID(pattern->IsScrollable());
        pattern->ScrollPage(true, true, scrollType);
    });
}

void ScrollablePattern::GetPaintPropertyDumpInfo(std::unique_ptr<JsonValue>& json)
{
    auto paintProperty = GetPaintProperty<ScrollablePaintProperty>();
    if (paintProperty) {
        switch (paintProperty->GetScrollBarMode().value_or(DisplayMode::OFF)) {
            case DisplayMode::OFF: {
                json->Put("innerScrollBarState", "OFF");
                break;
            }
            case DisplayMode::AUTO: {
                json->Put("innerScrollBarState", "AUTO");
                break;
            }
            case DisplayMode::ON: {
                json->Put("innerScrollBarState", "ON");
                break;
            }
            default: {
                break;
            }
        }
        auto scrollBarWidth = paintProperty->GetScrollBarWidth();
        json->Put("scrollBarWidth",
            scrollBarWidth.has_value() ? paintProperty->GetScrollBarWidth().value().ToString().c_str() : "None");
    }
}

void ScrollablePattern::GetAxisDumpInfo(std::unique_ptr<JsonValue>& json)
{
    switch (axis_) {
        case Axis::NONE: {
            json->Put("Axis", "NONE");
            break;
        }
        case Axis::VERTICAL: {
            json->Put("Axis", "VERTICAL");
            break;
        }
        case Axis::HORIZONTAL: {
            json->Put("Axis", "HORIZONTAL");
            break;
        }
        case Axis::FREE: {
            json->Put("Axis", "FREE");
            break;
        }
        default: {
            break;
        }
    }
}

void ScrollablePattern::GetPanDirectionDumpInfo(std::unique_ptr<JsonValue>& json)
{
    switch (GetScrollablePanDirection()) {
        case Axis::NONE: {
            json->Put("ScrollablePanDirection", "NONE");
            break;
        }
        case Axis::VERTICAL: {
            json->Put("ScrollablePanDirection", "VERTICAL");
            break;
        }
        case Axis::HORIZONTAL: {
            json->Put("ScrollablePanDirection", "HORIZONTAL");
            break;
        }
        case Axis::FREE: {
            json->Put("ScrollablePanDirection", "FREE");
            break;
        }
        default: {
            json->Put("ScrollablePanDirection", "null");
            break;
        }
    }
}

void ScrollablePattern::GetEventDumpInfo(std::unique_ptr<JsonValue>& json)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(hub);
    auto onScrollStart = hub->GetOnScrollStart();
    json->Put("hasOnScrollStart", onScrollStart ? "true" : "false");
    auto onJSFrameNodeScrollStart = hub->GetJSFrameNodeOnScrollStart();
    json->Put("hasFrameNodeOnScrollStart", onJSFrameNodeScrollStart ? "true" : "false");
    auto onScrollStop = hub->GetOnScrollStop();
    json->Put("hasOnScrollStop", onScrollStop ? "true" : "false");
    auto onJSFrameNodeScrollStop = hub->GetJSFrameNodeOnScrollStop();
    json->Put("hasFrameNodeOnScrollStop", onJSFrameNodeScrollStop ? "true" : "false");

    auto scrollHub = host->GetEventHub<ScrollEventHub>();
    if (scrollHub) {
        auto onWillScroll = scrollHub->GetOnWillScrollEvent();
        json->Put("hasOnWillScroll", onWillScroll ? "true" : "false");
        auto onJSFrameNodeScrollWillScroll = scrollHub->GetJSFrameNodeOnScrollWillScroll();
        json->Put("hasFrameNodeOnWillScroll", onJSFrameNodeScrollWillScroll ? "true" : "false");

        auto onDidScroll = scrollHub->GetOnDidScrollEvent();
        json->Put("hasOnDidScroll", onDidScroll ? "true" : "false");
        auto onJSFrameNodeScrollDidScroll = scrollHub->GetJSFrameNodeOnScrollDidScroll();
        json->Put("hasFrameNodeOnDidScroll", onJSFrameNodeScrollDidScroll ? "true" : "false");
    } else {
        auto onWillScroll = hub->GetOnWillScroll();
        json->Put("hasOnWillScroll", onWillScroll ? "true" : "false");
        auto onJSFrameNodeWillScroll = hub->GetJSFrameNodeOnWillScroll();
        json->Put("hasFrameNodeOnWillScroll", onJSFrameNodeWillScroll ? "true" : "false");

        auto onDidScroll = hub->GetOnDidScroll();
        json->Put("hasOnDidScroll", onDidScroll ? "true" : "false");
        auto onJSFrameNodeDidScroll = hub->GetJSFrameNodeOnDidScroll();
        json->Put("hasFrameNodeOnDidScroll", onJSFrameNodeDidScroll ? "true" : "false");
    }
    auto onScrollFrameBegin = hub->GetOnScrollFrameBegin();
    json->Put("hasOnScrollFrameBegin", onScrollFrameBegin ? "true" : "false");
    auto onJSFrameNodeScrollFrameBegin = hub->GetJSFrameNodeOnScrollFrameBegin();
    json->Put("hasFrameNodeOnScrollFrameBegin", onJSFrameNodeScrollFrameBegin ? "true" : "false");

    auto onReachStart = hub->GetOnReachStart();
    json->Put("hasOnReachStart", onReachStart ? "true" : "false");
    auto onJSFrameNodeReachStart = hub->GetJSFrameNodeOnReachStart();
    json->Put("hasFrameNodeOnReachStart", onJSFrameNodeReachStart ? "true" : "false");

    auto onReachEnd = hub->GetOnReachEnd();
    json->Put("hasOnReachEnd", onReachEnd ? "true" : "false");
    auto onJSFrameNodeReachEnd = hub->GetJSFrameNodeOnReachEnd();
    json->Put("hasFrameNodeOnReachEnd", onJSFrameNodeReachEnd ? "true" : "false");
}

void ScrollablePattern::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    GetEdgeEffectDumpInfo(json);
    json->Put("edgeEffectAlwaysEnabled", edgeEffectAlwaysEnabled_);
    json->Put("isScrollable", IsScrollable());
    GetEventDumpInfo(json);
    json->Put("NestedScroll", GetNestedScroll().ToString().c_str());
    json->Put("isSearchRefresh", GetIsSearchRefresh());
    json->Put("isFixedNestedScrollMode", GetIsFixedNestedScrollMode());
    auto parent = GetNestedScrollParent();
    if (parent && parent->GetHost()) {
        std::unique_ptr<JsonValue> children = JsonUtil::Create(true);
        children->Put("id", parent->GetHost()->GetId());
        children->Put("tag", parent->GetHost()->GetTag().c_str());
        json->Put("nestedScrollParent", children);
    } else {
        json->Put("nestedScrollParent", "null");
    }
    GetAxisDumpInfo(json);
    GetPanDirectionDumpInfo(json);
    GetPaintPropertyDumpInfo(json);
    json->Put("enableScrollInteraction", GetScrollEnabled());
    json->Put("friction", friction_);
    json->Put("flingSpeedLimit", std::to_string(GetMaxFlingVelocity()).c_str());
    json->Put("eventsFiredInfos", friction_);
    std::unique_ptr<JsonValue> children = JsonUtil::CreateArray(true);
    for (const auto& info : eventsFiredInfos_) {
        std::unique_ptr<JsonValue> child = JsonUtil::Create(true);
        info.ToJson(child);
        children->Put(child);
    }
    json->Put("eventsFiredInfos", children);
    std::unique_ptr<JsonValue> childreninfo = JsonUtil::Create(true);
    for (const auto& info : scrollableFrameInfos_) {
        std::unique_ptr<JsonValue> child = JsonUtil::Create(true);
        info.ToJson(child);
        childreninfo->Put(child);
    }
    json->Put("scrollableFrameInfos", childreninfo);
    if (scrollBar_) {
        scrollBar_->DumpAdvanceInfo(json);
    } else {
        json->Put("inner ScrollBar", "null");
    }
}

void ScrollablePattern::GetEdgeEffectDumpInfo(std::unique_ptr<JsonValue>& json)
{
    switch (edgeEffect_) {
        case EdgeEffect::NONE: {
            json->Put("edgeEffect", "NONE");
            break;
        }
        case EdgeEffect::SPRING: {
            json->Put("edgeEffect", "SPRING");
            break;
        }
        case EdgeEffect::FADE: {
            json->Put("edgeEffect", "FADE");
            break;
        }
        default: {
            break;
        }
    }
}

void ScrollablePattern::AddNestScrollBarProxy(const WeakPtr<ScrollBarProxy>& scrollBarProxy)
{
    if (std::find(nestScrollBarProxy_.begin(), nestScrollBarProxy_.end(), scrollBarProxy) !=
        nestScrollBarProxy_.end()) {
        return;
    }
    nestScrollBarProxy_.emplace_back(scrollBarProxy);
}

void ScrollablePattern::DeleteNestScrollBarProxy(const WeakPtr<ScrollBarProxy>& scrollBarProxy)
{
    auto iter = std::find(nestScrollBarProxy_.begin(), nestScrollBarProxy_.end(), scrollBarProxy);
    if (iter != nestScrollBarProxy_.end()) {
        nestScrollBarProxy_.erase(iter);
    }
}

void ScrollablePattern::SetParentNestedScroll(RefPtr<ScrollablePattern>& parentPattern)
{
    CHECK_NULL_VOID(parentPattern);
    auto parentScrollBarProxy = parentPattern->GetScrollBarProxy();
    auto scrollBarProxy = scrollBarProxy_;
    CHECK_NULL_VOID(scrollBarProxy);
    if (!parentScrollBarProxy) {
        auto proxy = AceType::MakeRefPtr<ScrollBarProxy>();
        parentPattern->SetScrollBarProxy(proxy);
        auto parentNodeInfo = proxy->GetScrollableNodeInfo();
        scrollBarProxy->RegisterNestScrollableNode(parentNodeInfo);
        parentPattern->AddNestScrollBarProxy(scrollBarProxy);
    } else {
        auto parentNodeInfo = parentScrollBarProxy->GetScrollableNodeInfo();
        scrollBarProxy->RegisterNestScrollableNode(parentNodeInfo);
        parentPattern->AddNestScrollBarProxy(scrollBarProxy);
    }
}

void ScrollablePattern::SearchAndSetParentNestedScroll(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto scrollBarAxis = GetAxis();
    for (auto parent = node->GetParent(); parent != nullptr; parent = parent->GetParent()) {
        RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(parent);
        if (!frameNode) {
            continue;
        }
        auto parentPattern = frameNode->GetPattern<NestableScrollContainer>();
        if (!parentPattern) {
            continue;
        }

        if (AceType::InstanceOf<SwiperPattern>(parentPattern)) {
            auto swiper = AceType::DynamicCast<SwiperPattern>(parentPattern);
            CHECK_NULL_VOID(swiper);
            auto direction = swiper->GetDirection();
            CHECK_EQUAL_VOID(scrollBarAxis, direction);
        }
        auto ScrollPattern = AceType::DynamicCast<ScrollablePattern>(parentPattern);
        SetParentNestedScroll(ScrollPattern);
    }
}

void ScrollablePattern::OnAttachToMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto scrollBarProxy = scrollBarProxy_;
    CHECK_NULL_VOID(scrollBarProxy);
    auto enableNestScroll = scrollBarProxy->IsNestScroller();
    if (enableNestScroll) {
        SearchAndSetParentNestedScroll(host);
    }
}

void ScrollablePattern::UnsetParentNestedScroll(RefPtr<ScrollablePattern>& parentPattern)
{
    CHECK_NULL_VOID(parentPattern);
    auto parentScrollBarProxy = parentPattern->GetScrollBarProxy();
    CHECK_NULL_VOID(parentScrollBarProxy);
    auto scrollBarProxy = scrollBarProxy_;
    CHECK_NULL_VOID(scrollBarProxy);
    auto parentNodeInfo = parentScrollBarProxy->GetScrollableNodeInfo();
    auto pattern = parentNodeInfo.scrollableNode.Upgrade();
    CHECK_NULL_VOID(pattern);
    scrollBarProxy->UnRegisterNestScrollableNode(pattern);
    parentPattern->DeleteNestScrollBarProxy(scrollBarProxy);
}

void ScrollablePattern::SearchAndUnsetParentNestedScroll(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto scrollBarAxis = GetAxis();
    for (auto parent = node->GetParent(); parent != nullptr; parent = parent->GetParent()) {
        RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(parent);
        if (!frameNode) {
            continue;
        }

        auto parentPattern = frameNode->GetPattern<NestableScrollContainer>();
        if (!parentPattern) {
            continue;
        }

        if (AceType::InstanceOf<SwiperPattern>(parentPattern)) {
            auto swiper = AceType::DynamicCast<SwiperPattern>(parentPattern);
            CHECK_NULL_VOID(swiper);
            auto direction = swiper->GetDirection();
            CHECK_EQUAL_VOID(scrollBarAxis, direction);
        }

        auto ScrollPattern = AceType::DynamicCast<ScrollablePattern>(parentPattern);
        UnsetParentNestedScroll(ScrollPattern);
    }
}

void ScrollablePattern::CheckScrollBarOff()
{
    auto paintProperty = GetPaintProperty<ScrollablePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto displayMode = paintProperty->GetScrollBarMode().value_or(GetDefaultScrollBarDisplayMode());
    if (displayMode == DisplayMode::OFF) {
        SetScrollBar(DisplayMode::OFF);
    }
}

void ScrollablePattern::UpdateNestedScrollVelocity(float offset, NestedState state)
{
    if (state == NestedState::GESTURE) {
        return;
    }
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    uint64_t currentVsync = pipeline->GetVsyncTime();
    uint64_t diff = currentVsync - nestedScrollTimestamp_;
    if (diff >= MAX_VSYNC_DIFF_TIME || diff <= MIN_DIFF_VSYNC) {
        diff = DEFAULT_VSYNC_DIFF_TIME;
    }
    nestedScrollVelocity_ = (offset / diff) * MILLOS_PER_NANO_SECONDS;
    nestedScrollTimestamp_ = currentVsync;
}

float ScrollablePattern::GetNestedScrollVelocity()
{
    if (NearZero(nestedScrollVelocity_)) {
        return 0.0f;
    }
    uint64_t currentVsync = static_cast<uint64_t>(GetSysTimestamp());
    uint64_t diff = currentVsync > nestedScrollTimestamp_ ? currentVsync - nestedScrollTimestamp_ : 0;
    if (diff >= MAX_VSYNC_DIFF_TIME) {
        nestedScrollVelocity_ = 0.0f;
    }
    return nestedScrollVelocity_;
}

void ScrollablePattern::OnColorConfigurationUpdate()
{
    CHECK_NULL_VOID(scrollBar_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<ScrollablePaintProperty>();
    if (paintProperty) {
        auto barColor = paintProperty->GetScrollBarColor();
        if (barColor) {
            scrollBar_->SetForegroundColor(barColor.value());
            return;
        }
    }
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<ScrollBarTheme>();
    CHECK_NULL_VOID(theme);
    scrollBar_->SetForegroundColor(theme->GetForegroundColor());
    scrollBar_->SetBackgroundColor(theme->GetBackgroundColor());
}

SizeF ScrollablePattern::GetViewSizeMinusPadding()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, SizeF());
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, SizeF());
    auto padding = layoutProperty->CreatePaddingAndBorder();
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, SizeF());
    auto viewSize = geometryNode->GetFrameSize();
    MinusPaddingToSize(padding, viewSize);
    return viewSize;
}

void ScrollablePattern::StopScrollableAndAnimate()
{
    if (!IsScrollableStopped()) {
        scrollAbort_ = true;
        StopScrollable();
    }
    if (!isAnimationStop_) {
        scrollAbort_ = true;
        StopAnimation(springAnimation_);
        StopAnimation(curveAnimation_);
    }
    if (animator_ && !animator_->IsStopped()) {
        scrollAbort_ = true;
        animator_->Stop();
    }
}

void ScrollablePattern::GetRepeatCountInfo(
    RefPtr<UINode> node, int32_t& repeatDifference, int32_t& firstRepeatCount, int32_t& totalChildCount)
{
    CHECK_NULL_VOID(node);
    auto& children = node->GetChildren();
    for (const auto& child : children) {
        if (AceType::InstanceOf<RepeatVirtualScroll2Node>(child)) {
            auto repeat2 = AceType::DynamicCast<RepeatVirtualScroll2Node>(child);
            auto repeatRealCount = repeat2->FrameCount();
            auto repeatVirtualCount = repeat2->GetTotalCount();
            if (repeatVirtualCount > static_cast<uint32_t>(repeatRealCount) && firstRepeatCount == 0) {
                firstRepeatCount = totalChildCount + repeatRealCount;
            }
            repeatDifference += repeatVirtualCount - repeatRealCount;
            totalChildCount += repeatRealCount;
        } else if (AceType::InstanceOf<FrameNode>(child) || AceType::InstanceOf<LazyForEachNode>(child) ||
                   AceType::InstanceOf<RepeatVirtualScrollNode>(child) || AceType::InstanceOf<ForEachNode>(child) ||
                   AceType::InstanceOf<CustomNode>(child)) {
            totalChildCount += child->FrameCount();
        } else {
            GetRepeatCountInfo(child, repeatDifference, firstRepeatCount, totalChildCount);
        }
    }
}

#ifdef SUPPORT_DIGITAL_CROWN
void ScrollablePattern::SetDigitalCrownEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto scrollableEvent = GetScrollableEvent();
    CHECK_NULL_VOID(scrollableEvent);
    auto scrollableControler = scrollableEvent->GetScrollable();
    CHECK_NULL_VOID(scrollableControler);
    scrollableControler->ListenDigitalCrownEvent(host);
    scrollableControler->SetDigitalCrownSensitivity(crownSensitivity_);
}

void ScrollablePattern::SetDigitalCrownSensitivity(CrownSensitivity sensitivity)
{
    crownSensitivity_ = sensitivity;
}
#endif
void ScrollablePattern::SetOnHiddenChangeForParent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto parent = host->GetAncestorNodeOfFrame(false);
    CHECK_NULL_VOID(parent);
    while (parent) {
        if (parent->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
            break;
        }
        parent = parent->GetAncestorNodeOfFrame(false);
    }
    if (parent && parent->GetTag() == V2::NAVDESTINATION_VIEW_ETS_TAG) {
        auto navDestinationPattern = parent->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(navDestinationPattern);
        auto navDestinationEventHub = navDestinationPattern->GetEventHub<NavDestinationEventHub>();
        CHECK_NULL_VOID(navDestinationEventHub);
        auto onHiddenChange = [weak = WeakClaim(this)](bool isShow) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto scrollBarOverlayModifier = pattern->GetScrollBarOverlayModifier();
            CHECK_NULL_VOID(scrollBarOverlayModifier);
            scrollBarOverlayModifier->SetNavDestinationShow(isShow);
        };
        navDestinationEventHub->AddOnHiddenChange(host->GetId(), std::move(onHiddenChange));
    }
}

bool ScrollablePattern::IsRestrictBoundary()
{
    return !scrollEffect_ || scrollEffect_->IsRestrictBoundary();
}

bool ScrollablePattern::IsScrollableSpringEffect() const
{
    CHECK_NULL_RETURN(scrollEffect_, false);
    return scrollEffect_->IsSpringEffect();
}

const RefPtr<ScrollEdgeEffect>& ScrollablePattern::GetScrollEdgeEffect() const
{
    return scrollEffect_;
}

void ScrollablePattern::MarkScrollBarProxyDirty()
{
    if (scrollBarProxy_) {
        scrollBarProxy_->MarkScrollBarDirty();
    }
}
} // namespace OHOS::Ace::NG
