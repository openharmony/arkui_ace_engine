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

#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"

#include <optional>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/dump_log.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/common/agingadapation/aging_adapation_dialog_util.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/scrollable/scrollable.h"
#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"
#include "core/components_ng/pattern/swiper/swiper_event_hub.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"
#include "core/components_ng/pattern/tabs/tabs_controller.h"
#include "core/components_ng/pattern/tabs/tabs_layout_property.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/pattern/tabs/tabs_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "base/perfmonitor/perf_constants.h"
#include "base/perfmonitor/perf_monitor.h"
namespace OHOS::Ace::NG {
namespace {
constexpr int8_t LEFT_GRADIENT = 0;
constexpr int8_t RIGHT_GRADIENT = 1;
constexpr int8_t TOP_GRADIENT = 2;
constexpr int8_t BOTTOM_GRADIENT = 3;
constexpr float HALF_PROGRESS = 0.5f;
constexpr float FULL_PROGRESS = 1.0f;
constexpr float HALF_MASK_RADIUS_RATIO = 0.717f;
constexpr float FULL_MASK_RADIUS_RATIO = 1.414f;
constexpr float INVALID_RATIO = -1.0f;
constexpr uint16_t MASK_ANIMATION_DURATION = 200;
constexpr int8_t MASK_COUNT = 2;
constexpr float FULL_OPACITY = 1.0f;
constexpr float NEAR_FULL_OPACITY = 0.99f;
constexpr float NO_OPACITY = 0.0f;
constexpr float TEXT_COLOR_THREDHOLD = 0.673f;
constexpr int8_t HALF_OF_WIDTH = 2;
constexpr float MAX_FLING_VELOCITY = 4200.0f;

const auto DurationCubicCurve = AceType::MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.1f, 1.0f);
const auto TRANSLATE_CURVE = AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 228.0f, 30.0f);
const auto TRANSLATE_THRESHOLD = 26.0f;
const auto TRANSLATE_FRAME_RATE = 120;
const auto TRANSLATE_FRAME_RATE_RANGE =
    AceType::MakeRefPtr<FrameRateRange>(0, TRANSLATE_FRAME_RATE, TRANSLATE_FRAME_RATE);
const std::string TAB_BAR_PROPERTY_NAME = "tabBar";
const std::string INDICATOR_OFFSET_PROPERTY_NAME = "indicatorOffset";
const std::string INDICATOR_WIDTH_PROPERTY_NAME = "translateWidth";
} // namespace

TabBarPattern::TabBarPattern() = default;

TabBarPattern::~TabBarPattern() = default;

void TabBarPattern::SetController(const RefPtr<SwiperController>& controller)
{
    swiperController_ = controller;
    SetTabBarFinishCallback();
    auto tabsController = AceType::DynamicCast<TabsControllerNG>(swiperController_);
    CHECK_NULL_VOID(tabsController);
    auto weak = WeakClaim(this);
    tabsController->SetStartShowTabBarImpl([weak](int32_t delay) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->StartShowTabBar(delay);
    });
    tabsController->SetCancelShowTabBarImpl([weak]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->CancelShowTabBar();
    });
    tabsController->SetUpdateTabBarHiddenOffsetImpl([weak](float offset) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->UpdateTabBarHiddenOffset(offset);
    });
    tabsController->SetTabBarTranslateImpl([weak](const TranslateOptions& options) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetTabBarTranslate(options, true);
    });
    tabsController->SetTabBarOpacityImpl([weak](float opacity) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetTabBarOpacity(opacity);
    });
}

void TabBarPattern::StartShowTabBar(int32_t delay)
{
    if (axis_ == Axis::VERTICAL || isTabBarShowing_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    auto translate = options.y.ConvertToPx();
    auto size = renderContext->GetPaintRectWithoutTransform().Height();
    if (NearZero(translate) || NearZero(size)) {
        return;
    }

    CancelShowTabBar();
    if (delay == 0 && isTabBarHiding_) {
        // stop hide tab bar and show tab bar immediately.
        StopHideTabBar();
    } else if (delay > 0 && !isTabBarHiding_) {
        auto threshold = Dimension(TRANSLATE_THRESHOLD, DimensionUnit::VP).ConvertToPx();
        if (tabBarState_ == TabBarState::SHOW && LessNotEqual(std::abs(translate), threshold)) {
            // not reach the threshold for hiding tab bar, so show tab bar immediately.
            delay = 0;
        } else if (tabBarState_ == TabBarState::HIDE && LessNotEqual(size - std::abs(translate), threshold)) {
            // not reach the threshold for showing tab bar, so hide tab bar immediately and show tab bar after 2s.
            StartHideTabBar();
        }
    }

    if (delay == 0) {
        StartShowTabBarImmediately();
    }
}

void TabBarPattern::StartShowTabBarImmediately()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    InitTabBarProperty();
    AnimationOption option;
    option.SetCurve(TRANSLATE_CURVE);
    option.SetFrameRateRange(TRANSLATE_FRAME_RATE_RANGE);

    auto options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    auto translate = options.y.ConvertToPx();
    if (NearEqual(translate, userDefinedTranslateY_)) {
        return;
    }
    tabBarProperty_->Set(translate);
    auto propertyCallback = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->tabBarProperty_->Set(pattern->GetUserDefinedTranslateY());
    };
    auto finishCallback = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->isTabBarShowing_ = false;
        pattern->tabBarState_ = TabBarState::SHOW;
    };
    auto pipeline = host->GetContextRefPtr();
    AnimationUtils::Animate(option, propertyCallback, finishCallback, nullptr, pipeline);
    isTabBarShowing_ = true;
}

void TabBarPattern::CancelShowTabBar()
{
    if (showTabBarTask_) {
        showTabBarTask_.Cancel();
        showTabBarTask_.Reset(nullptr);
    }
}

void TabBarPattern::StartHideTabBar()
{
    if (axis_ == Axis::VERTICAL || showTabBarTask_ || isTabBarShowing_ || isTabBarHiding_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    auto translate = options.y.ConvertToPx();
    auto size = renderContext->GetPaintRectWithoutTransform().Height();
    if (GreatOrEqual(std::abs(translate), size) || NearZero(size)) {
        return;
    }

    InitTabBarProperty();
    AnimationOption option;
    option.SetCurve(TRANSLATE_CURVE);
    option.SetFrameRateRange(TRANSLATE_FRAME_RATE_RANGE);

    tabBarProperty_->Set(translate);
    auto propertyCallback = [weak = WeakClaim(this), size]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
        CHECK_NULL_VOID(tabsNode);
        auto tabsLayoutProperty = AceType::DynamicCast<TabsLayoutProperty>(tabsNode->GetLayoutProperty());
        CHECK_NULL_VOID(tabsLayoutProperty);
        auto barPosition = tabsLayoutProperty->GetTabBarPosition().value_or(BarPosition::START);
        if (barPosition == BarPosition::START) {
            pattern->tabBarProperty_->Set(-size);
        } else {
            pattern->tabBarProperty_->Set(size);
        }
    };
    auto finishCallback = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->isTabBarHiding_ = false;
        pattern->tabBarState_ = TabBarState::HIDE;
    };
    auto pipeline = host->GetContextRefPtr();
    AnimationUtils::Animate(option, propertyCallback, finishCallback, nullptr, pipeline);
    isTabBarHiding_ = true;
}

void TabBarPattern::StopHideTabBar()
{
    if (axis_ == Axis::VERTICAL || !isTabBarHiding_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    AnimationOption option;
    option.SetDuration(0);
    option.SetCurve(Curves::LINEAR);
    auto options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    auto translate = options.y.ConvertToPx();
    auto propertyCallback = [weak = WeakClaim(this), translate]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->tabBarProperty_->Set(translate);
    };
    auto pipeline = host->GetContextRefPtr();
    AnimationUtils::Animate(option, propertyCallback, nullptr, nullptr, pipeline);
    isTabBarHiding_ = false;
}

void TabBarPattern::InitTabBarProperty()
{
    if (tabBarProperty_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    auto propertyCallback = [weak = WeakClaim(this)](float value) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);

        pattern->SetTabBarTranslate(TranslateOptions(0.0f, value, 0.0f));
        auto size = renderContext->GetPaintRectWithoutTransform().Height();
        if (NearZero(size)) {
            return;
        }
        pattern->SetTabBarOpacity(1.0f - std::abs(value) / size);
    };
    tabBarProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    renderContext->AttachNodeAnimatableProperty(tabBarProperty_);
}

void TabBarPattern::UpdateTabBarHiddenOffset(float offset)
{
    if (axis_ == Axis::VERTICAL || showTabBarTask_ || isTabBarShowing_ || isTabBarHiding_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_VOID(tabsNode);
    auto tabsLayoutProperty = AceType::DynamicCast<TabsLayoutProperty>(tabsNode->GetLayoutProperty());
    CHECK_NULL_VOID(tabsLayoutProperty);

    auto options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    float preTranslate = options.y.ConvertToPx();
    auto size = renderContext->GetPaintRectWithoutTransform().Height();
    if (NearZero(size)) {
        return;
    }
    auto barPosition = tabsLayoutProperty->GetTabBarPosition().value_or(BarPosition::START);
    auto translate = 0.0f;
    if (barPosition == BarPosition::START) {
        translate = std::clamp(preTranslate - offset, -size, 0.0f);
    } else {
        translate = std::clamp(preTranslate + offset, 0.0f, size);
    }
    SetTabBarTranslate(TranslateOptions(0.0f, translate, 0.0f));
    float opacity = renderContext->GetOpacityValue(1.0f);
    opacity = std::clamp(opacity - offset / size, 0.0f, 1.0f);
    SetTabBarOpacity(opacity);
    auto threshold = Dimension(TRANSLATE_THRESHOLD, DimensionUnit::VP).ConvertToPx();
    if (Positive(offset) && LessNotEqual(std::abs(preTranslate), threshold) &&
        GreatOrEqual(std::abs(translate), threshold)) {
        StartHideTabBar();
    } else if (Negative(offset) && LessNotEqual(size - std::abs(preTranslate), threshold) &&
               GreatOrEqual(size - std::abs(translate), threshold)) {
        StartShowTabBar();
    }
}

void TabBarPattern::SetTabBarTranslate(const TranslateOptions& options, bool isUserDefined)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateTransformTranslate(options);
    if (isUserDefined) {
        userDefinedTranslateY_ = options.y.ConvertToPx();
    }
    auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_VOID(tabsNode);
    auto divider = AceType::DynamicCast<FrameNode>(tabsNode->GetDivider());
    CHECK_NULL_VOID(divider);
    auto dividerRenderContext = divider->GetRenderContext();
    CHECK_NULL_VOID(dividerRenderContext);
    dividerRenderContext->UpdateTransformTranslate(options);
}

void TabBarPattern::SetTabBarOpacity(float opacity)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateOpacity(opacity);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_VOID(tabsNode);
    auto divider = AceType::DynamicCast<FrameNode>(tabsNode->GetDivider());
    CHECK_NULL_VOID(divider);
    auto dividerRenderContext = divider->GetRenderContext();
    CHECK_NULL_VOID(dividerRenderContext);
    dividerRenderContext->UpdateOpacity(opacity);
}

void FindTextAndImageNode(
    const RefPtr<FrameNode>& columnNode, RefPtr<FrameNode>& textNode, RefPtr<FrameNode>& imageNode)
{
    if (columnNode->GetTag() == V2::TEXT_ETS_TAG) {
        textNode = columnNode;
    } else if (columnNode->GetTag() == V2::IMAGE_ETS_TAG || columnNode->GetTag() == V2::SYMBOL_ETS_TAG) {
        imageNode = columnNode;
    } else {
        std::list<RefPtr<UINode>> children = columnNode->GetChildren();
        for (auto child : children) {
            FindTextAndImageNode(AceType::DynamicCast<FrameNode>(child), textNode, imageNode);
        }
    }
}

void TabBarPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetClipToFrame(true);
    if (!host->GetLayoutProperty()->GetSafeAreaExpandOpts()) {
        host->GetLayoutProperty()->UpdateSafeAreaExpandOpts(
            SafeAreaExpandOpts { .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_BOTTOM });
    }
    InitSurfaceChangedCallback();
}

void TabBarPattern::SetTabBarFinishCallback()
{
    CHECK_NULL_VOID(swiperController_);
    swiperController_->SetTabBarFinishCallback([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        // always swipe with physical curve, ignore animationDuration
        pattern->SetSwiperCurve(pattern->GetAnimationCurve(TabBarPhysicalCurve));

        if (pattern->scrollableEvent_) {
            auto scrollable = pattern->scrollableEvent_->GetScrollable();
            if (scrollable) {
                scrollable->StopScrollable();
            }
        }

        pattern->StopTranslateAnimation(true);
        pattern->ResetIndicatorAnimationState();
        auto swiperPattern = pattern->GetSwiperPattern();
        CHECK_NULL_VOID(swiperPattern);
        auto currentIndex = swiperPattern->GetCurrentIndex();
        auto totalCount = swiperPattern->TotalCount();
        if (currentIndex >= totalCount || currentIndex < 0) {
            currentIndex = 0;
        }
        auto layoutProperty = pattern->GetLayoutProperty<TabBarLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        if (layoutProperty->GetIndicatorValue(0) != currentIndex) {
            pattern->UpdateSubTabBoard(currentIndex);
            pattern->UpdateTextColorAndFontWeight(currentIndex);
            pattern->UpdateIndicator(currentIndex);
            pattern->UpdatePaintIndicator(currentIndex, true);
            pattern->SetChangeByClick(false);
        }
    });
}

void TabBarPattern::InitSurfaceChangedCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    if (!HasSurfaceChangedCallback()) {
        auto callbackId = pipeline->RegisterSurfaceChangedCallback(
            [weak = WeakClaim(this)](int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight,
                WindowSizeChangeReason type) {
                auto pattern = weak.Upgrade();
                if (!pattern) {
                    return;
                }

                pattern->windowSizeChangeReason_ = type;
                pattern->prevRootSize_ = std::make_pair(prevWidth, prevHeight);

                if (type == WindowSizeChangeReason::ROTATION) {
                    pattern->StopTranslateAnimation();
                }
            });
        UpdateSurfaceChangedCallbackId(callbackId);
    }
}

void TabBarPattern::OnDetachFromFrameNode(FrameNode* node)
{
    CHECK_NULL_VOID(node);
    auto pipeline = node->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (HasSurfaceChangedCallback()) {
        pipeline->UnregisterSurfaceChangedCallback(surfaceChangedCallbackId_.value_or(-1));
    }
    pipeline->RemoveWindowStateChangedCallback(node->GetId());
}

void TabBarPattern::BeforeCreateLayoutWrapper()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (targetIndex_) {
        targetIndex_ = GetLoopIndex(targetIndex_.value());
    }
    if (isExecuteBuilder_) {
        jumpIndex_ = layoutProperty->GetIndicatorValue(0);
        isExecuteBuilder_ = false;
    }
}

void TabBarPattern::AddTabBarItemClickAndTouchEvent(const RefPtr<FrameNode>& tabBarItem)
{
    CHECK_NULL_VOID(tabBarItem);
    auto tabBarItemId = tabBarItem->GetId();
    if (clickEvents_.find(tabBarItemId) != clickEvents_.end()) {
        return;
    }
    auto eventHub = tabBarItem->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto clickCallback = [weak = WeakClaim(this), tabBarItemId](GestureEvent& info) {
        auto tabBar = weak.Upgrade();
        CHECK_NULL_VOID(tabBar);
        auto host = tabBar->GetHost();
        CHECK_NULL_VOID(host);
        auto index = host->GetChildFlatIndex(tabBarItemId).second;
        tabBar->HandleClick(info.GetSourceDevice(), index);
    };
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback));
    clickEvents_[tabBarItemId] = clickEvent;
    gestureHub->AddClickEvent(clickEvent);

    if (touchEvents_.find(tabBarItemId) != touchEvents_.end()) {
        return;
    }
    auto touchCallback = [weak = WeakClaim(this), tabBarItemId](const TouchEventInfo& info) {
        auto tabBar = weak.Upgrade();
        CHECK_NULL_VOID(tabBar);
        auto host = tabBar->GetHost();
        CHECK_NULL_VOID(host);
        auto index = host->GetChildFlatIndex(tabBarItemId).second;
        for (auto touchInfo : info.GetTouches()) {
            tabBar->HandleTouchEvent(touchInfo.GetTouchType(), index);
        }
    };
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    touchEvents_[tabBarItemId] = touchEvent;
    gestureHub->AddTouchEvent(touchEvent);
}

void TabBarPattern::AddTabBarItemCallBack(const RefPtr<FrameNode>& tabBarItem)
{
    CHECK_NULL_VOID(tabBarItem);
    auto tabBarItemId = tabBarItem->GetId();
    auto columnAccessibilityProperty = tabBarItem->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(columnAccessibilityProperty);
    columnAccessibilityProperty->SetOnAccessibilityFocusCallback([weak = WeakClaim(this), tabBarItemId](bool focus) {
        if (focus) {
            auto tabBar = weak.Upgrade();
            CHECK_NULL_VOID(tabBar);
            auto host = tabBar->GetHost();
            CHECK_NULL_VOID(host);
            auto index = host->GetChildFlatIndex(tabBarItemId).second;
            tabBar->accessibilityFocusIndicator_ = index;
            tabBar->FocusCurrentOffset(index);
        }
    });
}

void TabBarPattern::AddMaskItemClickEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto childCount = host->GetChildren().size() - MASK_COUNT;

    for (int32_t maskIndex = 0; maskIndex < MASK_COUNT; maskIndex++) {
        auto maskNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(childCount + maskIndex));
        CHECK_NULL_VOID(maskNode);
        auto maskNodeId = maskNode->GetId();
        if (clickEvents_.find(maskNodeId) != clickEvents_.end()) {
            continue;
        }

        auto eventHub = maskNode->GetEventHub<EventHub>();
        CHECK_NULL_VOID(eventHub);
        auto gestureHub = eventHub->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        auto clickCallback = [weak = WeakClaim(this), maskIndex](GestureEvent& info) {
            auto tabBar = weak.Upgrade();
            CHECK_NULL_VOID(tabBar);
            auto layoutProperty = tabBar->GetLayoutProperty<TabBarLayoutProperty>();
            CHECK_NULL_VOID(layoutProperty);
            auto index = (maskIndex == 0) ? layoutProperty->GetSelectedMask().value_or(-1) :
                layoutProperty->GetUnselectedMask().value_or(-1);
            if (index >= 0) {
                tabBar->HandleClick(info.GetSourceDevice(), index);
            }
        };
        auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback));
        clickEvents_[maskNodeId] = clickEvent;
        gestureHub->AddClickEvent(clickEvent);
    }
}

void TabBarPattern::InitLongPressEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (longPressEvent_) {
        return;
    }

    auto longPressTask = [weak = WeakClaim(this)](GestureEvent& info) {
        auto tabBar = weak.Upgrade();
        if (tabBar) {
            tabBar->HandleLongPressEvent(info);
        }
    };
    longPressEvent_ = AceType::MakeRefPtr<LongPressEvent>(std::move(longPressTask));
    gestureHub->SetLongPressEvent(longPressEvent_);
}

void TabBarPattern::InitDragEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!dragEvent_);
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto tabBar = weak.Upgrade();
        CHECK_NULL_VOID(tabBar);
        auto index = tabBar->CalculateSelectedIndex(info.GetLocalLocation());
        auto host = tabBar->GetHost();
        CHECK_NULL_VOID(host);
        auto totalCount = host->TotalChildCount() - MASK_COUNT;
        if (tabBar && tabBar->dialogNode_ && index >= 0 && index < totalCount) {
            if (!tabBar->moveIndex_.has_value()) {
                tabBar->moveIndex_ = index;
            }

            if (tabBar->moveIndex_ != index) {
                tabBar->CloseDialog();
                tabBar->moveIndex_ = index;
                tabBar->ShowDialogWithNode(index);
            }
        }
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto tabBar = weak.Upgrade();
        CHECK_NULL_VOID(tabBar);
        auto index = tabBar->CalculateSelectedIndex(info.GetLocalLocation());
        if (tabBar->dialogNode_) {
            tabBar->HandleClick(info.GetSourceDevice(), index);
            tabBar->CloseDialog();
        }
    };
    auto actionCancelTask = [weak = WeakClaim(this)] {
        auto tabBar = weak.Upgrade();
        CHECK_NULL_VOID(tabBar);
        if (tabBar->dialogNode_) {
            tabBar->CloseDialog();
        }
    };
    dragEvent_ = MakeRefPtr<DragEvent>(
        nullptr, std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    PanDirection panDirection = { .type = PanDirection::ALL };
    gestureHub->SetDragEvent(dragEvent_, panDirection, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
}

void TabBarPattern::InitScrollableEvent(
    const RefPtr<TabBarLayoutProperty>& layoutProperty, const RefPtr<GestureEventHub>& gestureHub)
{
    if (layoutProperty->GetTabBarModeValue(TabBarMode::FIXED) == TabBarMode::SCROLLABLE) {
        InitScrollable(gestureHub);
        SetEdgeEffect(gestureHub);
    } else {
        if (scrollableEvent_) {
            gestureHub->RemoveScrollableEvent(scrollableEvent_);
            scrollableEvent_.Reset();
        }
        if (scrollEffect_) {
            gestureHub->RemoveScrollEdgeEffect(scrollEffect_);
            scrollEffect_.Reset();
        }
    }
}

void TabBarPattern::InitScrollable(const RefPtr<GestureEventHub>& gestureHub)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto axis = layoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
    if (axis_ == axis && scrollableEvent_) {
        return;
    }

    axis_ = axis;
    auto task = [weak = WeakClaim(this)](double offset, int32_t source) {
        if (source == SCROLL_FROM_START) {
            return true;
        }
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        if (!pattern->CanScroll()) {
            return false;
        }

        if (pattern->IsOutOfBoundary()) {
            // over scroll in drag update from normal to over scroll or during over scroll.
            auto scrollable = pattern->scrollableEvent_->GetScrollable();
            if (scrollable) {
                scrollable->SetCanOverScroll(true);
            }

            auto host = pattern->GetHost();
            CHECK_NULL_RETURN(host, false);
            auto overScrollInfo = pattern->GetOverScrollInfo(pattern->GetContentSize());
            if (source == SCROLL_FROM_UPDATE) {
                // adjust offset.
                if (overScrollInfo.second != 0.0f) {
                    pattern->canOverScroll_ = true;
                    auto friction = CalculateFriction(std::abs(overScrollInfo.first) / overScrollInfo.second);
                    pattern->UpdateCurrentOffset(static_cast<float>(offset * friction));
                }
                return true;
            }
        }
        if (source != SCROLL_FROM_AXIS) {
            pattern->canOverScroll_ = true;
        }
        pattern->UpdateCurrentOffset(static_cast<float>(offset));
        return true;
    };

    if (scrollableEvent_) {
        gestureHub->RemoveScrollableEvent(scrollableEvent_);
    }

    scrollableEvent_ = MakeRefPtr<ScrollableEvent>(axis);
    auto scrollable = MakeRefPtr<Scrollable>(task, axis);
    scrollable->SetNodeId(host->GetAccessibilityId());
    scrollable->Initialize(host);
    scrollable->SetMaxFlingVelocity(MAX_FLING_VELOCITY);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto springProperty = scrollable->GetSpringProperty();
    renderContext->AttachNodeAnimatableProperty(springProperty);
    auto frictionProperty = scrollable->GetFrictionProperty();
    renderContext->AttachNodeAnimatableProperty(frictionProperty);
    scrollableEvent_->SetScrollable(scrollable);
    gestureHub->AddScrollableEvent(scrollableEvent_);
    scrollableEvent_->GetScrollable()->SetEdgeEffect(EdgeEffect::SPRING);
}

bool TabBarPattern::CanScroll() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    if (layoutProperty->GetTabBarModeValue(TabBarMode::FIXED) == TabBarMode::FIXED) {
        return false;
    }

    if (visibleItemPosition_.empty()) {
        return false;
    }
    auto visibleItemStartIndex = visibleItemPosition_.begin()->first;
    auto visibleItemEndIndex = visibleItemPosition_.rbegin()->first;
    auto visibleItemStartPos = visibleItemPosition_.begin()->second.startPos;
    auto visibleItemEndPos = visibleItemPosition_.rbegin()->second.endPos;
    auto childCount = host->TotalChildCount() - MASK_COUNT;
    auto contentMainSize = GetContentSize().MainSize(layoutProperty->GetAxis().value_or(Axis::HORIZONTAL));
    return visibleItemStartIndex > 0 || LessNotEqual(visibleItemStartPos, scrollMargin_) ||
        visibleItemEndIndex < (childCount - 1) || GreatNotEqual(visibleItemEndPos, contentMainSize - scrollMargin_);
}

std::pair<float, float> TabBarPattern::GetOverScrollInfo(const SizeF& size)
{
    auto overScroll = 0.0f;
    auto mainSize = 0.0f;
    if (visibleItemPosition_.empty()) {
        return std::make_pair(overScroll, mainSize);
    }

    auto visibleItemStartPos = visibleItemPosition_.begin()->second.startPos;
    auto visibleItemEndPos = visibleItemPosition_.rbegin()->second.endPos;
    auto startPos = visibleItemStartPos - scrollMargin_;
    mainSize = size.MainSize(axis_);
    if (Positive(startPos)) {
        overScroll = startPos;
    } else {
        overScroll = mainSize - visibleItemEndPos - scrollMargin_;
    }
    return std::make_pair(overScroll, mainSize);
}

bool TabBarPattern::InsideTabBarRegion(const TouchLocationInfo& locationInfo)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto hotRegion = geometryNode->GetFrameRect();
    auto touchPoint = PointF(static_cast<float>(locationInfo.GetLocalLocation().GetX()),
        static_cast<float>(locationInfo.GetLocalLocation().GetY()));
    return hotRegion.IsInRegion(touchPoint);
}

void TabBarPattern::InitHoverEvent()
{
    if (hoverEvent_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = GetHost()->GetEventHub<EventHub>();
    auto inputHub = eventHub->GetOrCreateInputEventHub();

    auto hoverTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleHoverEvent(isHover);
        }
    };
    hoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverTask));
    inputHub->AddOnHoverEvent(hoverEvent_);
}

void TabBarPattern::InitMouseEvent()
{
    if (mouseEvent_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = GetHost()->GetEventHub<EventHub>();
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    auto mouseTask = [weak = WeakClaim(this)](const MouseInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleMouseEvent(info);
        }
    };
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnMouseEvent(mouseEvent_);
}

void TabBarPattern::HandleMouseEvent(const MouseInfo& info)
{
    if (IsContainsBuilder()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto totalCount = host->TotalChildCount() - MASK_COUNT;
    if (totalCount < 0) {
        return;
    }
    auto index = CalculateSelectedIndex(info.GetLocalLocation());
    if (index < 0 || index >= totalCount) {
        if (hoverIndex_.has_value() && touchingIndex_.empty()) {
            HandleMoveAway(hoverIndex_.value());
        }
        hoverIndex_.reset();
        return;
    }
    auto mouseAction = info.GetAction();
    if (mouseAction == MouseAction::MOVE || mouseAction == MouseAction::WINDOW_ENTER) {
        if (!touchingIndex_.empty()) {
            hoverIndex_ = index;
            return;
        }
        if (!hoverIndex_.has_value()) {
            HandleHoverOnEvent(index);
            hoverIndex_ = index;
            return;
        }
        if (hoverIndex_.value() != index) {
            HandleMoveAway(hoverIndex_.value());
            HandleHoverOnEvent(index);
            hoverIndex_ = index;
            return;
        }
        return;
    }
    if (mouseAction == MouseAction::WINDOW_LEAVE) {
        if (hoverIndex_.has_value()) {
            HandleMoveAway(hoverIndex_.value());
        }
    }
}

void TabBarPattern::HandleHoverEvent(bool isHover)
{
    if (IsContainsBuilder()) {
        return;
    }
    isHover_ = isHover;
    if (!isHover_ && hoverIndex_.has_value()) {
        if (touchingIndex_.empty()) {
            HandleMoveAway(hoverIndex_.value());
        }
        hoverIndex_.reset();
    }
}

void TabBarPattern::HandleHoverOnEvent(int32_t index)
{
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    PlayPressAnimation(index, GetSubTabBarHoverColor(index), AnimationType::HOVER);
}

void TabBarPattern::HandleMoveAway(int32_t index)
{
    Color tabBarItemColor = Color::TRANSPARENT;
    if (tabBarStyle_ == TabBarStyle::SUBTABBATSTYLE && isTabBarFocusActive_ && index == focusIndicator_) {
        tabBarItemColor = tabBarItemFocusBgColor_;
    }
    PlayPressAnimation(index, tabBarItemColor, AnimationType::HOVER);
}

RefPtr<FocusHub> TabBarPattern::GetCurrentFocusNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto layoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    auto indicator = layoutProperty->GetIndicatorValue(0);
    if (tabBarStyle_ == TabBarStyle::BOTTOMTABBATSTYLE || tabBarStyle_ == TabBarStyle::SUBTABBATSTYLE) {
        focusIndicator_ = indicator;
    }
    auto childNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(indicator));
    CHECK_NULL_RETURN(childNode, nullptr);
    auto childFocusHub = childNode->GetFocusHub();
    CHECK_NULL_RETURN(childFocusHub, nullptr);
    childFocusHub->SetFocusDependence(FocusDependence::SELF);
    return childFocusHub;
}

ScopeFocusAlgorithm TabBarPattern::GetScopeFocusAlgorithm()
{
    return ScopeFocusAlgorithm(axis_ == Axis::VERTICAL, isRTL_, ScopeType::FLEX,
        [weak = WeakClaim(this)](
            FocusStep step, const WeakPtr<FocusHub>& currentFocusHub, WeakPtr<FocusHub>& nextFocusHub) -> bool {
            auto pattern = weak.Upgrade();
            CHECK_NULL_RETURN(pattern, false);
            nextFocusHub = pattern->GetNextFocusNode(step);
            if (nextFocusHub.Upgrade()) {
                return true;
            } else {
                return false;
            }
        });
}

WeakPtr<FocusHub> TabBarPattern::GetNextFocusNode(FocusStep step)
{
    auto pipeline = GetContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    if (!pipeline->GetIsFocusActive()) {
        return nullptr;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    CHECK_NULL_RETURN(tabTheme, nullptr);
    auto indicator = 0;
    if (tabBarStyle_ == TabBarStyle::BOTTOMTABBATSTYLE ||
        (tabBarStyle_ == TabBarStyle::SUBTABBATSTYLE && !tabTheme->GetIsChangeFocusTextStyle())) {
        indicator = focusIndicator_;
        auto nextFocusIndicator = GetNextFocusIndicator(indicator, step);
        if (nextFocusIndicator.has_value()) {
            if (ContentWillChange(nextFocusIndicator.value())) {
                indicator = nextFocusIndicator.value();
                focusIndicator_ = indicator;
                FocusCurrentOffset(indicator);
            }
        } else {
            return nullptr;
        }
    } else {
        CHECK_NULL_RETURN(swiperController_, nullptr);
        swiperController_->FinishAnimation();
        auto layoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
        CHECK_NULL_RETURN(layoutProperty, nullptr);
        indicator = layoutProperty->GetIndicatorValue(0);
        auto nextFocusIndicator = GetNextFocusIndicator(indicator, step);
        if (nextFocusIndicator.has_value()) {
            if (ContentWillChange(indicator, nextFocusIndicator.value())) {
                indicator = nextFocusIndicator.value();
                focusIndicator_ = indicator;
                FocusIndexChange(indicator);
            }
        } else {
            return nullptr;
        }
    }

    auto childNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(indicator));
    CHECK_NULL_RETURN(childNode, nullptr);
    auto childFocusHub = childNode->GetFocusHub();
    CHECK_NULL_RETURN(childFocusHub, nullptr);
    childFocusHub->SetFocusDependence(FocusDependence::SELF);
    return AceType::WeakClaim(AceType::RawPtr(childFocusHub));
}

std::optional<int32_t> TabBarPattern::GetNextFocusIndicator(int32_t indicator, FocusStep step)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, std::nullopt);
    if (step == (axis_ == Axis::HORIZONTAL ? (isRTL_ ? FocusStep::RIGHT : FocusStep::LEFT) : FocusStep::UP) ||
        step == FocusStep::SHIFT_TAB) {
        if (indicator <= 0) {
            return std::nullopt;
        }
        indicator -= 1;
    } else if (step == (axis_ == Axis::HORIZONTAL ? (isRTL_ ? FocusStep::LEFT : FocusStep::RIGHT) : FocusStep::DOWN) ||
        step == FocusStep::TAB) {
        if (indicator >= host->TotalChildCount() - MASK_COUNT - 1) {
            return std::nullopt;
        }
        indicator += 1;
    } else if (step == (axis_ == Axis::HORIZONTAL ? FocusStep::LEFT_END : FocusStep::UP_END)) {
        indicator = 0;
    } else if (step == (axis_ == Axis::HORIZONTAL ? FocusStep::RIGHT_END : FocusStep::DOWN_END)) {
        indicator = host->TotalChildCount() - MASK_COUNT - 1;
    } else {
        return std::nullopt;
    }
    return indicator;
}

void TabBarPattern::FocusIndexChange(int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_VOID(tabsNode);
    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabsPattern);

    SetSwiperCurve(GetAnimationCurve(DurationCubicCurve));
    UpdateAnimationDuration();
    auto duration = GetAnimationDuration().value_or(0);
    if (tabsPattern->GetIsCustomAnimation()) {
        OnCustomContentTransition(indicator_, index);
    } else {
        if (duration > 0 && tabsPattern->GetAnimateMode() != TabAnimateMode::NO_ANIMATION) {
            tabContentWillChangeFlag_ = true;
            swiperController_->SwipeTo(index);
            animationTargetIndex_ = index;
        } else {
            swiperController_->SwipeToWithoutAnimation(index);
        }
    }

    UpdateIndicator(index);
    changeByClick_ = true;
    clickRepeat_ = true;
    UpdateTextColorAndFontWeight(index);
    UpdateSubTabBoard(index);
    if (duration > 0 && CanScroll()) {
        targetIndex_ = index;
    } else {
        jumpIndex_ = index;
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void TabBarPattern::FocusCurrentOffset(int32_t index)
{
    auto layoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto barMode = layoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED);
    auto axis = layoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
    auto tabBarNode = GetHost();
    CHECK_NULL_VOID(tabBarNode);
    auto mainSize = GetContentSize().MainSize(axis);

    if (barMode == TabBarMode::SCROLLABLE && !visibleItemPosition_.empty()) {
        auto iter = visibleItemPosition_.find(index);
        if (iter != visibleItemPosition_.end()) {
            auto startPos = iter->second.startPos;
            auto endPos = iter->second.endPos;
            if (GreatOrEqual(startPos, 0.0f) && LessOrEqual(endPos, mainSize)) {
                return;
            }
        }
        focusIndex_ = index;
        tabBarNode->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    }
}

void TabBarPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    AddMaskItemClickEvent();
    InitTurnPageRateEvent();
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(theme);
    InitTabBarProperties(theme);
    UpdateBackBlurStyle(theme);

    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    InitScrollableEvent(layoutProperty, gestureHub);
    InitHoverEvent();
    InitMouseEvent();
    SetSurfaceChangeCallback();
    InitFocusEvent();
    SetAccessibilityAction();
    UpdateSubTabBoard(indicator_);
    UpdateTextColorAndFontWeight(indicator_);
    StopTranslateAnimation();
    StartShowTabBar();
    jumpIndex_ = layoutProperty->GetIndicatorValue(0);

    RemoveTabBarEventCallback();
    AddTabBarEventCallback();
    UpdateChildrenClipEdge();

    axis_ = layoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_VOID(tabsNode);
    auto tabsLayoutProperty = AceType::DynamicCast<TabsLayoutProperty>(tabsNode->GetLayoutProperty());
    CHECK_NULL_VOID(tabsLayoutProperty);
    auto tabsDirection = tabsLayoutProperty->GetNonAutoLayoutDirection();
    auto tabBarDirection = layoutProperty->GetLayoutDirection();
    isRTL_ = tabBarDirection == TextDirection::RTL ||
             (tabBarDirection == TextDirection::AUTO && tabsDirection == TextDirection::RTL);
}

void TabBarPattern::ResetOnForceMeasure(int32_t index)
{
    auto layoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetIndicatorValue(0) != index) {
        jumpIndex_ = index;
        focusIndicator_ = index;
        UpdateSubTabBoard(index);
        UpdateTextColorAndFontWeight(index);
        UpdateIndicator(index);
        UpdatePaintIndicator(index, true);
        HandleBottomTabBarChange(index);
    }
}

void TabBarPattern::UpdateBackBlurStyle(const RefPtr<TabTheme>& tabTheme)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        auto defaultBlurStyle = static_cast<BlurStyle>(tabTheme->GetBottomTabBackgroundBlurStyle());
        if (defaultBlurStyle != BlurStyle::NO_MATERIAL && !renderContext->GetBackBlurStyle().has_value() &&
            !renderContext->GetBackBlurRadius().has_value() && !renderContext->GetBackgroundEffect().has_value()) {
            BlurStyleOption styleOption;
            styleOption.blurStyle = defaultBlurStyle;
            pipelineContext->RemoveWindowFocusChangedCallback(host->GetId());
            renderContext->UpdateBackBlurStyle(styleOption);
        }
    }
}

void TabBarPattern::SetSurfaceChangeCallback()
{
    CHECK_NULL_VOID(swiperController_);
    auto surfaceChangeCallback = [weak = WeakClaim(this)]() {
        auto tabBarPattern = weak.Upgrade();
        CHECK_NULL_VOID(tabBarPattern);
        tabBarPattern->isTouchingSwiper_ = false;
    };
    swiperController_->SetSurfaceChangeCallback(std::move(surfaceChangeCallback));
}

void TabBarPattern::RemoveTabBarEventCallback()
{
    CHECK_NULL_VOID(swiperController_);
    auto removeEventCallback = [weak = WeakClaim(this)]() {
        auto tabBarPattern = weak.Upgrade();
        CHECK_NULL_VOID(tabBarPattern);
        auto host = tabBarPattern->GetHost();
        CHECK_NULL_VOID(host);
        auto hub = host->GetEventHub<EventHub>();
        CHECK_NULL_VOID(hub);
        auto gestureHub = hub->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        if (layoutProperty->GetTabBarModeValue(TabBarMode::FIXED) == TabBarMode::SCROLLABLE) {
            gestureHub->RemoveScrollableEvent(tabBarPattern->scrollableEvent_);
        }
        if (tabBarPattern->tabBarStyle_ == TabBarStyle::BOTTOMTABBATSTYLE) {
            gestureHub->RemoveDragEvent();
            gestureHub->SetLongPressEvent(nullptr);
            tabBarPattern->longPressEvent_ = nullptr;
            tabBarPattern->dragEvent_ = nullptr;
        }
        tabBarPattern->isTouchingSwiper_ = true;
        for (const auto& childNode : host->GetChildren()) {
            CHECK_NULL_VOID(childNode);
            auto frameNode = AceType::DynamicCast<FrameNode>(childNode);
            CHECK_NULL_VOID(frameNode);
            auto childHub = frameNode->GetEventHub<EventHub>();
            CHECK_NULL_VOID(childHub);
            auto childGestureHub = childHub->GetOrCreateGestureEventHub();
            CHECK_NULL_VOID(childGestureHub);
            auto clickIter = tabBarPattern->clickEvents_.find(frameNode->GetId());
            if (clickIter != tabBarPattern->clickEvents_.end()) {
                childGestureHub->RemoveClickEvent(clickIter->second);
            }
            auto touchIter = tabBarPattern->touchEvents_.find(frameNode->GetId());
            if (touchIter != tabBarPattern->touchEvents_.end()) {
                childGestureHub->RemoveTouchEvent(touchIter->second);
            }
        }
    };
    swiperController_->SetRemoveTabBarEventCallback(std::move(removeEventCallback));
}

void TabBarPattern::AddTabBarEventCallback()
{
    CHECK_NULL_VOID(swiperController_);
    auto addEventCallback = [weak = WeakClaim(this)]() {
        auto tabBarPattern = weak.Upgrade();
        CHECK_NULL_VOID(tabBarPattern);
        auto host = tabBarPattern->GetHost();
        CHECK_NULL_VOID(host);
        auto hub = host->GetEventHub<EventHub>();
        CHECK_NULL_VOID(hub);
        auto gestureHub = hub->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        if (layoutProperty->GetTabBarModeValue(TabBarMode::FIXED) == TabBarMode::SCROLLABLE) {
            gestureHub->AddScrollableEvent(tabBarPattern->scrollableEvent_);
        }
        for (const auto& childNode : host->GetChildren()) {
            CHECK_NULL_VOID(childNode);
            auto frameNode = AceType::DynamicCast<FrameNode>(childNode);
            CHECK_NULL_VOID(frameNode);
            auto childHub = frameNode->GetEventHub<EventHub>();
            CHECK_NULL_VOID(childHub);
            auto childGestureHub = childHub->GetOrCreateGestureEventHub();
            CHECK_NULL_VOID(childGestureHub);
            auto clickIter = tabBarPattern->clickEvents_.find(frameNode->GetId());
            if (clickIter != tabBarPattern->clickEvents_.end()) {
                childGestureHub->AddClickEvent(clickIter->second);
            }
            auto touchIter = tabBarPattern->touchEvents_.find(frameNode->GetId());
            if (touchIter != tabBarPattern->touchEvents_.end()) {
                childGestureHub->AddTouchEvent(touchIter->second);
            }
        }
        tabBarPattern->InitLongPressAndDragEvent();
    };
    swiperController_->SetAddTabBarEventCallback(std::move(addEventCallback));
}

void TabBarPattern::UpdateChildrenClipEdge()
{
    auto tabBarNode = GetHost();
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarRenderContext = tabBarNode->GetRenderContext();
    CHECK_NULL_VOID(tabBarRenderContext);
    bool clipEdge = tabBarRenderContext->GetClipEdgeValue(true);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    if (tabTheme->GetIsChangeFocusTextStyle()) {
        clipEdge = false;
    }
    if (clipEdge != clipEdge_) {
        int32_t totalCount = tabBarNode->TotalChildCount() - MASK_COUNT;
        for (int32_t index = 0; index < totalCount; index++) {
            auto childNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(index));
            CHECK_NULL_VOID(childNode);
            auto renderContext = childNode->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateClipEdge(clipEdge);
        }
        clipEdge_ = clipEdge;
    }
}

void TabBarPattern::UpdatePaintIndicator(int32_t indicator, bool needMarkDirty)
{
    auto tabBarNode = GetHost();
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    auto paintProperty = GetPaintProperty<TabBarPaintProperty>();
    if (indicator_ >= static_cast<int32_t>(tabBarStyles_.size()) ||
        indicator < 0 || indicator >= static_cast<int32_t>(tabBarStyles_.size())) {
        return;
    }
    auto layoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (tabBarPattern->IsContainsBuilder() || layoutProperty->GetAxis() == Axis::VERTICAL ||
        tabBarStyles_[indicator] == TabBarStyle::BOTTOMTABBATSTYLE) {
        paintProperty->ResetIndicator();

        if (needMarkDirty) {
            tabBarNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }

        return;
    }

    RectF rect = {};
    if (visibleItemPosition_.find(indicator) != visibleItemPosition_.end()) {
        rect = layoutProperty->GetIndicatorRect(indicator);
        paintProperty->UpdateIndicator(indicator);
    } else {
        paintProperty->ResetIndicator();
    }
    if (!isTouchingSwiper_ || tabBarStyles_[indicator] != TabBarStyle::SUBTABBATSTYLE) {
        currentIndicatorOffset_ = rect.GetX() + rect.Width() / 2;

        if (needMarkDirty) {
            tabBarNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    }
}

bool TabBarPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto tabBarLayoutAlgorithm = DynamicCast<TabBarLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(tabBarLayoutAlgorithm, false);
    currentDelta_ = 0.0f;
    canOverScroll_ = false;
    visibleItemPosition_ = tabBarLayoutAlgorithm->GetVisibleItemPosition();
    scrollMargin_ = tabBarLayoutAlgorithm->GetScrollMargin();
    jumpIndex_ = tabBarLayoutAlgorithm->GetJumpIndex();
    barGridMargin_ = tabBarLayoutAlgorithm->GetBarGridMargin();
    auto layoutProperty = DynamicCast<TabBarLayoutProperty>(dirty->GetLayoutProperty());
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_RETURN(swiperPattern, false);
    int32_t indicator = swiperPattern->IsInFastAnimation() ? indicator_ : swiperPattern->GetCurrentIndex();
    int32_t totalCount = swiperPattern->TotalCount();
    if (indicator > totalCount - 1 || indicator < 0) {
        indicator = 0;
    }
    if (totalCount == 0) {
        isTouchingSwiper_ = false;
    }
    auto pipelineContext = GetContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    if (targetIndex_) {
        TriggerTranslateAnimation(indicator_, targetIndex_.value());
        targetIndex_.reset();
    }

    if (swiperPattern->IsUseCustomAnimation()) {
        UpdateSubTabBoard(indicator);
        UpdatePaintIndicator(indicator, false);
    }
    if ((!swiperPattern->IsUseCustomAnimation() || isFirstLayout_) && !isAnimating_ && !IsMaskAnimationExecuted()) {
        UpdateSubTabBoard(indicator);
        UpdatePaintIndicator(indicator, true);
    }
    isFirstLayout_ = false;
    if (focusIndex_) {
        focusIndex_.reset();
        host->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
    }
    indicator_ = layoutProperty->GetIndicatorValue(0);

    if (windowSizeChangeReason_) {
        if (*windowSizeChangeReason_ == WindowSizeChangeReason::ROTATION && animationTargetIndex_.has_value() &&
            animationTargetIndex_ != indicator) {
            swiperController_->SwipeToWithoutAnimation(animationTargetIndex_.value());
            animationTargetIndex_.reset();
            windowSizeChangeReason_.reset();
        } else if (prevRootSize_.first != PipelineContext::GetCurrentRootWidth() ||
            prevRootSize_.second != PipelineContext::GetCurrentRootHeight()) {
            StopTranslateAnimation();
            jumpIndex_ = indicator_;
            focusIndicator_ = indicator_;
            UpdateSubTabBoard(indicator_);
            UpdateIndicator(indicator_);
            UpdatePaintIndicator(indicator_, true);
            windowSizeChangeReason_.reset();
            host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
        }
    }
    UpdateGradientRegions(!swiperPattern->IsUseCustomAnimation());
    if (!swiperPattern->IsUseCustomAnimation() && isTouchingSwiper_ &&
        layoutProperty->GetTabBarModeValue(TabBarMode::FIXED) == TabBarMode::SCROLLABLE) {
        ApplyTurnPageRateToIndicator(turnPageRate_);
    }
    return false;
}

bool TabBarPattern::CustomizeExpandSafeArea()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_RETURN(tabsNode, false);
    auto tabLayoutProperty = AceType::DynamicCast<TabsLayoutProperty>(tabsNode->GetLayoutProperty());
    CHECK_NULL_RETURN(tabLayoutProperty, false);
    return tabLayoutProperty->GetSafeAreaPaddingProperty() ? true : false;
}

void TabBarPattern::OnSyncGeometryNode(const DirtySwapConfig& config)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_VOID(tabsNode);
    auto tabLayoutProperty = AceType::DynamicCast<TabsLayoutProperty>(tabsNode->GetLayoutProperty());
    CHECK_NULL_VOID(tabLayoutProperty);
    if (!tabLayoutProperty->GetSafeAreaPaddingProperty()) {
        return;
    }
    auto tabBarSize = host->GetGeometryNode()->GetMarginFrameSize();
    auto tabBarOffset = host->GetGeometryNode()->GetMarginFrameOffset();
    auto tabsExpandEdges = tabsNode->GetAccumulatedSafeAreaExpand();
    auto tabBarExpandEdges = host->GetAccumulatedSafeAreaExpand();
    auto tabBarRect = RectF(tabBarOffset.GetX(), tabBarOffset.GetY(), tabBarSize.Width(),
        tabBarSize.Height() + tabsExpandEdges.bottom.value_or(0) + tabBarExpandEdges.bottom.value_or(0));
    auto tabBarRenderContext = host->GetRenderContext();
    CHECK_NULL_VOID(tabBarRenderContext);
    tabBarRenderContext->UpdatePaintRect(tabBarRect);
}

void TabBarPattern::InitLongPressAndDragEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    float scale = pipelineContext->GetFontScale();

    bigScale_ = AgingAdapationDialogUtil::GetDialogBigFontSizeScale();
    largeScale_ = AgingAdapationDialogUtil::GetDialogLargeFontSizeScale();
    maxScale_ = AgingAdapationDialogUtil::GetDialogMaxFontSizeScale();

    if (tabBarStyle_ == TabBarStyle::BOTTOMTABBATSTYLE) {
        if (scale >= bigScale_) {
            InitLongPressEvent(gestureHub);
            InitDragEvent(gestureHub);
        } else {
            gestureHub->RemoveDragEvent();
            gestureHub->SetLongPressEvent(nullptr);
            longPressEvent_ = nullptr;
            dragEvent_ = nullptr;
        }
    }
}

void TabBarPattern::HandleLongPressEvent(const GestureEvent& info)
{
    auto index = CalculateSelectedIndex(info.GetLocalLocation());
    HandleClick(info.GetSourceDevice(), index);
    ShowDialogWithNode(index);
}

void TabBarPattern::ShowDialogWithNode(int32_t index)
{
    auto tabBarNode = GetHost();
    CHECK_NULL_VOID(tabBarNode);
    auto columnNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(index));
    CHECK_NULL_VOID(columnNode);
    RefPtr<FrameNode> imageNode = nullptr;
    RefPtr<FrameNode> textNode = nullptr;
    FindTextAndImageNode(columnNode, textNode, imageNode);
    CHECK_NULL_VOID(imageNode);
    CHECK_NULL_VOID(textNode);

    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto textValue = textLayoutProperty->GetContent();
    if (imageNode->GetTag() == V2::SYMBOL_ETS_TAG) {
        dialogNode_ = AgingAdapationDialogUtil::ShowLongPressDialog(textValue.value_or(u""), imageNode);
    } else {
        auto imageProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageProperty);
        ImageSourceInfo imageSourceInfo = imageProperty->GetImageSourceInfoValue();
        dialogNode_ = AgingAdapationDialogUtil::ShowLongPressDialog(textValue.value_or(u""), imageSourceInfo);
    }
}

void TabBarPattern::CloseDialog()
{
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->CloseDialog(dialogNode_);
    dialogNode_.Reset();
}

void TabBarPattern::HandleClick(SourceType type, int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetTabBarModeValue(TabBarMode::FIXED) == TabBarMode::SCROLLABLE && scrollableEvent_) {
        auto scrollable = scrollableEvent_->GetScrollable();
        if (scrollable) {
            if (IsOutOfBoundary()) {
                return;
            }
            scrollable->StopScrollable();
        }
    }

    auto totalCount = host->TotalChildCount() - MASK_COUNT;
    if (totalCount < 0) {
        return;
    }

    TAG_LOGI(AceLogTag::ACE_TABS, "Clicked tabBarIndex: %{public}d", index);
    if (index < 0 || index >= totalCount || !swiperController_ ||
        indicator_ >= static_cast<int32_t>(tabBarStyles_.size()) ||
        index >= static_cast<int32_t>(tabBarStyles_.size())) {
        return;
    }
    SetSwiperCurve(GetAnimationCurve(DurationCubicCurve));

    TabBarClickEvent(index);
    if (!ContentWillChange(layoutProperty->GetIndicatorValue(0), index)) {
        return;
    }
    if (tabBarStyles_[indicator_] == TabBarStyle::SUBTABBATSTYLE &&
        tabBarStyles_[index] == TabBarStyle::SUBTABBATSTYLE &&
        layoutProperty->GetAxisValue(Axis::HORIZONTAL) == Axis::HORIZONTAL) {
        HandleSubTabBarClick(layoutProperty, index);
        return;
    }
    ClickTo(host, index);
}

void TabBarPattern::ClickTo(const RefPtr<FrameNode>& host, int32_t index)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_VOID(tabsNode);
    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabsPattern);
    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    int32_t indicator = layoutProperty->GetIndicatorValue(0);
    if (!tabsPattern->GetIsCustomAnimation() && indicator == index) {
        return;
    }
    swiperController_->FinishAnimation();
    UpdateAnimationDuration();
    auto duration = GetAnimationDuration().value_or(0);
    if (tabsPattern->GetIsCustomAnimation()) {
        OnCustomContentTransition(indicator, index);
    } else {
        if (duration > 0 && tabsPattern->GetAnimateMode() != TabAnimateMode::NO_ANIMATION) {
            PerfMonitor::GetPerfMonitor()->Start(PerfConstants::APP_TAB_SWITCH, PerfActionType::LAST_UP, "");
            tabContentWillChangeFlag_ = true;
            swiperController_->SwipeTo(index);
            animationTargetIndex_ = index;
        } else {
            swiperController_->SwipeToWithoutAnimation(index);
        }
    }

    UpdateIndicator(index);
    changeByClick_ = true;
    clickRepeat_ = true;
    if (duration > 0 && CanScroll()) {
        targetIndex_ = index;
    } else {
        jumpIndex_ = index;
    }
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    if (tabTheme->GetIsChangeFocusTextStyle()) {
        focusIndicator_ = index;
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void TabBarPattern::HandleBottomTabBarChange(int32_t index)
{
    AnimationUtils::StopAnimation(maskAnimation_);
    auto preIndex = GetImageColorOnIndex().value_or(indicator_);
    if (preIndex == index) {
        return;
    }
    UpdateImageColor(index);
    UpdateSymbolStats(index, preIndex);
    if (preIndex < 0 || preIndex >= static_cast<int32_t>(tabBarStyles_.size()) ||
        index < 0 || index >= static_cast<int32_t>(tabBarStyles_.size())) {
        return;
    }
    if (preIndex != index && (tabBarStyles_[preIndex] == TabBarStyle::BOTTOMTABBATSTYLE ||
                                   tabBarStyles_[index] == TabBarStyle::BOTTOMTABBATSTYLE)) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto childCount = host->TotalChildCount() - MASK_COUNT;
        int32_t selectedIndex = -1;
        int32_t unselectedIndex = -1;
        if (preIndex < childCount && tabBarStyles_[preIndex] == TabBarStyle::BOTTOMTABBATSTYLE && CheckSvg(preIndex)) {
            unselectedIndex = preIndex;
        }
        if (index < childCount && tabBarStyles_[index] == TabBarStyle::BOTTOMTABBATSTYLE && CheckSvg(index)) {
            selectedIndex = index;
        }
        HandleBottomTabBarClick(selectedIndex, unselectedIndex);
    }
}

bool TabBarPattern::CheckSvg(int32_t index) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto columnNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(index));
    CHECK_NULL_RETURN(columnNode && !columnNode->GetChildren().empty(), false);
    auto imageNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
    CHECK_NULL_RETURN(imageNode, false);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, false);
    ImageSourceInfo info;
    auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo().value_or(info);
    return imageSourceInfo.IsSvg();
}

void TabBarPattern::HandleBottomTabBarClick(int32_t selectedIndex, int32_t unselectedIndex)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    std::vector<int32_t> selectedIndexes = {selectedIndex, unselectedIndex};
    OffsetF originalSelectedMaskOffset;
    OffsetF originalUnselectedMaskOffset;
    float selectedImageSize = 0.0f;
    float unselectedImageSize = 0.0f;
    for (int32_t maskIndex = 0; maskIndex < MASK_COUNT; maskIndex++) {
        if (maskIndex == 0) {
            layoutProperty->UpdateSelectedMask(selectedIndex);
        } else {
            layoutProperty->UpdateUnselectedMask(unselectedIndex);
        }
        if (selectedIndexes[maskIndex] < 0) {
            continue;
        }
        GetBottomTabBarImageSizeAndOffset(selectedIndexes, maskIndex, selectedImageSize, unselectedImageSize,
            originalSelectedMaskOffset, originalUnselectedMaskOffset);
    }
    ChangeMask(selectedIndex, selectedImageSize, originalSelectedMaskOffset, NO_OPACITY, HALF_MASK_RADIUS_RATIO, true);
    ChangeMask(unselectedIndex, unselectedImageSize, originalUnselectedMaskOffset, FULL_OPACITY,
        FULL_MASK_RADIUS_RATIO, false);

    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    PlayMaskAnimation(selectedImageSize, originalSelectedMaskOffset, selectedIndex, unselectedImageSize,
        originalUnselectedMaskOffset, unselectedIndex);
}

void TabBarPattern::GetBottomTabBarImageSizeAndOffset(const std::vector<int32_t>& selectedIndexes, int32_t maskIndex,
    float& selectedImageSize, float& unselectedImageSize, OffsetF& originalSelectedMaskOffset,
    OffsetF& originalUnselectedMaskOffset)
{
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto columnNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(selectedIndexes[maskIndex]));
    CHECK_NULL_VOID(columnNode && !columnNode->GetChildren().empty());
    auto imageNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
    CHECK_NULL_VOID(imageNode);
    auto imageGeometryNode = imageNode->GetGeometryNode();
    CHECK_NULL_VOID(imageGeometryNode);
    auto imageOffset = imageGeometryNode->GetFrameOffset();
    auto imageSize = imageGeometryNode->GetFrameSize().Width();
    if (maskIndex == 0) {
        selectedImageSize = imageSize;
    } else {
        unselectedImageSize = imageSize;
    }
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    ImageSourceInfo info;
    auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo().value_or(info);

    auto maskPosition = host->GetChildren().size() - MASK_COUNT;
    if (maskPosition < 0) {
        return;
    }
    auto selectedMaskNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(maskPosition + maskIndex));
    CHECK_NULL_VOID(selectedMaskNode);
    selectedMaskNode->GetLayoutProperty()->UpdateLayoutDirection(TextDirection::LTR);
    if (maskIndex == 0) {
        originalSelectedMaskOffset = imageOffset;
    } else {
        originalUnselectedMaskOffset = imageOffset;
    }
    CHECK_NULL_VOID(!selectedMaskNode->GetChildren().empty());
    auto selectedImageNode = AceType::DynamicCast<FrameNode>(selectedMaskNode->GetChildren().front());
    CHECK_NULL_VOID(selectedImageNode);

    auto selectedImageLayoutProperty = selectedImageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(selectedImageLayoutProperty);
    UpdateBottomTabBarImageColor(selectedIndexes, maskIndex);
    selectedImageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);

    selectedImageNode->MarkModifyDone();
    selectedImageNode->MarkDirtyNode();
    imageNode->MarkModifyDone();
    imageNode->MarkDirtyNode();
}

void TabBarPattern::UpdateBottomTabBarImageColor(const std::vector<int32_t>& selectedIndexes, int32_t maskIndex)
{
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto columnNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(selectedIndexes[maskIndex]));
    CHECK_NULL_VOID(columnNode && !columnNode->GetChildren().empty());
    auto imageNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
    CHECK_NULL_VOID(imageNode);

    auto maskPosition = host->GetChildren().size() - MASK_COUNT;
    if (maskPosition < 0) {
        return;
    }
    auto selectedMaskNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(maskPosition + maskIndex));
    CHECK_NULL_VOID(selectedMaskNode && !selectedMaskNode->GetChildren().empty());
    auto selectedImageNode = AceType::DynamicCast<FrameNode>(selectedMaskNode->GetChildren().front());
    CHECK_NULL_VOID(selectedImageNode);

    auto selectedImagePaintProperty = selectedImageNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(selectedImagePaintProperty);
    auto unselectedImagePaintProperty = imageNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(unselectedImagePaintProperty);
    if (selectedIndexes[maskIndex] >= 0 && selectedIndexes[maskIndex] < static_cast<int32_t>(iconStyles_.size())) {
        if (iconStyles_[selectedIndexes[maskIndex]].selectedColor.has_value()) {
            selectedImagePaintProperty->UpdateSvgFillColor(
                iconStyles_[selectedIndexes[maskIndex]].selectedColor.value());
        } else {
            selectedImagePaintProperty->UpdateSvgFillColor(tabTheme->GetBottomTabIconOn());
        }

        if (iconStyles_[selectedIndexes[maskIndex]].unselectedColor.has_value()) {
            unselectedImagePaintProperty->UpdateSvgFillColor(
                iconStyles_[selectedIndexes[maskIndex]].unselectedColor.value());
        } else {
            unselectedImagePaintProperty->UpdateSvgFillColor(tabTheme->GetBottomTabIconOff());
        }
    }
}

void TabBarPattern::PlayMaskAnimation(float selectedImageSize,
    const OffsetF& originalSelectedMaskOffset, int32_t selectedIndex, float unselectedImageSize,
    const OffsetF& originalUnselectedMaskOffset, int32_t unselectedIndex)
{
    auto curve = AceType::MakeRefPtr<CubicCurve>(0.4f, 0.0f, 0.2f, 1.0f);
    AnimationOption option;
    option.SetDuration(MASK_ANIMATION_DURATION);
    option.SetCurve(curve);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();

    maskAnimation_ = AnimationUtils::StartAnimation(
        option,
        [weak = AceType::WeakClaim(this), selectedIndex, unselectedIndex, selectedImageSize, originalSelectedMaskOffset,
            unselectedImageSize, originalUnselectedMaskOffset, pipeline]() {
            AnimationUtils::AddKeyFrame(
                HALF_PROGRESS,
                [weak, selectedIndex, unselectedIndex, selectedImageSize, originalSelectedMaskOffset,
                    unselectedImageSize, originalUnselectedMaskOffset]() {
                    auto tabBar = weak.Upgrade();
                    if (tabBar) {
                        tabBar->ChangeMask(selectedIndex, selectedImageSize, originalSelectedMaskOffset, FULL_OPACITY,
                            INVALID_RATIO, true);
                        tabBar->ChangeMask(unselectedIndex, unselectedImageSize, originalUnselectedMaskOffset,
                            NEAR_FULL_OPACITY, INVALID_RATIO, false);
                    }
                },
                pipeline);
            AnimationUtils::AddKeyFrame(
                FULL_PROGRESS,
                [weak, selectedIndex, unselectedIndex, selectedImageSize, originalSelectedMaskOffset,
                    unselectedImageSize, originalUnselectedMaskOffset]() {
                    auto tabBar = weak.Upgrade();
                    if (tabBar) {
                        tabBar->ChangeMask(selectedIndex, selectedImageSize, originalSelectedMaskOffset, FULL_OPACITY,
                            FULL_MASK_RADIUS_RATIO, true);
                        tabBar->ChangeMask(unselectedIndex, unselectedImageSize, originalUnselectedMaskOffset,
                            NO_OPACITY, HALF_MASK_RADIUS_RATIO, false);
                    }
                },
                pipeline);
        },
        [weak = AceType::WeakClaim(this), selectedIndex, unselectedIndex]() {
            auto tabBar = weak.Upgrade();
            if (tabBar) {
                auto host = tabBar->GetHost();
                CHECK_NULL_VOID(host);
                MaskAnimationFinish(host, selectedIndex, true);
                MaskAnimationFinish(host, unselectedIndex, false);
            }
        },
        nullptr, pipeline);
}

void TabBarPattern::MaskAnimationFinish(const RefPtr<FrameNode>& host, int32_t selectedIndex,
    bool isSelected)
{
    if (selectedIndex < 0) {
        return;
    }
    auto tabBarLayoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    if (isSelected) {
        tabBarLayoutProperty->UpdateSelectedMask(-1);
    } else {
        tabBarLayoutProperty->UpdateUnselectedMask(-1);
    }

    auto columnNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(selectedIndex));
    CHECK_NULL_VOID(columnNode && !columnNode->GetChildren().empty());
    auto imageNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
    CHECK_NULL_VOID(imageNode);

    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto imagePaintProperty = imageNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(imagePaintProperty);
    ImageSourceInfo info;
    auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo().value_or(info);

    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    auto tabBarPattern = host->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    auto iconStyles = tabBarPattern->GetIconStyle();
    if (selectedIndex >= 0 && selectedIndex < static_cast<int32_t>(iconStyles.size())) {
        if (isSelected) {
            if (iconStyles[selectedIndex].selectedColor.has_value()) {
                imagePaintProperty->UpdateSvgFillColor(iconStyles[selectedIndex].selectedColor.value());
            } else {
                imagePaintProperty->UpdateSvgFillColor(tabTheme->GetBottomTabIconOn());
            }
        } else {
            if (iconStyles[selectedIndex].unselectedColor.has_value()) {
                imagePaintProperty->UpdateSvgFillColor(iconStyles[selectedIndex].unselectedColor.value());
            } else {
                imagePaintProperty->UpdateSvgFillColor(tabTheme->GetBottomTabIconOff());
            }
        }
    }
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);

    host->MarkDirtyNode();
    imageNode->MarkModifyDone();
    imageNode->MarkDirtyNode();
}

void TabBarPattern::ChangeMask(int32_t index, float imageSize, const OffsetF& originalMaskOffset, float opacity,
    float radiusRatio, bool isSelected)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto maskPosition = host->GetChildren().size() - MASK_COUNT;
    if (index < 0 || NearZero(imageSize) || maskPosition < 0) {
        return;
    }

    auto maskNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(maskPosition + !isSelected));
    CHECK_NULL_VOID(maskNode && !maskNode->GetChildren().empty());
    auto maskImageNode = AceType::DynamicCast<FrameNode>(maskNode->GetChildren().front());
    CHECK_NULL_VOID(maskImageNode);
    auto maskImageRenderContext = maskImageNode->GetRenderContext();
    CHECK_NULL_VOID(maskImageRenderContext);

    if (NonNegative(radiusRatio)) {
        auto maskRenderContext = maskNode->GetRenderContext();
        CHECK_NULL_VOID(maskRenderContext);
        auto maskGeometryNode = maskNode->GetGeometryNode();
        CHECK_NULL_VOID(maskGeometryNode);
        auto tabBarNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(index));
        CHECK_NULL_VOID(tabBarNode);
        auto tabBarGeometryNode = tabBarNode->GetGeometryNode();
        CHECK_NULL_VOID(tabBarGeometryNode);

        OffsetF maskOffset = originalMaskOffset;
        maskOffset.AddX(-imageSize * radiusRatio);
        maskOffset.AddY(imageSize * (1.0f - radiusRatio));
        auto tabBarOffset = tabBarGeometryNode->GetMarginFrameOffset();
        maskGeometryNode->SetMarginFrameOffset(maskOffset + tabBarOffset);
        maskGeometryNode->SetFrameSize(SizeF(imageSize * radiusRatio * 2.0f, imageSize * radiusRatio * 2.0f));
        maskRenderContext->SavePaintRect();
        maskRenderContext->SyncGeometryProperties(nullptr);
        BorderRadiusProperty borderRadiusProperty;
        borderRadiusProperty.SetRadius(Dimension(imageSize * radiusRatio));
        maskRenderContext->UpdateBorderRadius(borderRadiusProperty);
        maskImageRenderContext->UpdateOffset(OffsetT<Dimension>(Dimension(imageSize * radiusRatio),
            Dimension(imageSize * (radiusRatio - 1.0f))));
        auto maskImageGeometryNode = maskImageNode->GetGeometryNode();
        CHECK_NULL_VOID(maskImageGeometryNode);
        maskImageGeometryNode->SetFrameSize(SizeF(imageSize, imageSize));
        auto maskImageProperty = maskImageNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(maskImageProperty);
        maskImageProperty->UpdateUserDefinedIdealSize(
            CalcSize(NG::CalcLength(Dimension(imageSize)), NG::CalcLength(Dimension(imageSize))));
        maskImageRenderContext->SetVisible(false);
        maskImageRenderContext->SavePaintRect();
        maskImageRenderContext->SyncGeometryProperties(nullptr);
    }
    maskImageRenderContext->UpdateOpacity(opacity);
}

void TabBarPattern::HandleSubTabBarClick(const RefPtr<TabBarLayoutProperty>& layoutProperty, int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_VOID(tabsFrameNode);
    auto tabsPattern = tabsFrameNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabsPattern);
    int32_t indicator = layoutProperty->GetIndicatorValue(0);
    if (!tabsPattern->GetIsCustomAnimation() && indicator == index) {
        return;
    }
    swiperController_->FinishAnimation();
    UpdateAnimationDuration();
    auto duration = GetAnimationDuration().value_or(0);
    if (tabsPattern->GetIsCustomAnimation()) {
        OnCustomContentTransition(indicator, index);
    } else {
        if (duration> 0 && tabsPattern->GetAnimateMode() != TabAnimateMode::NO_ANIMATION) {
            PerfMonitor::GetPerfMonitor()->Start(PerfConstants::APP_TAB_SWITCH, PerfActionType::LAST_UP, "");
            tabContentWillChangeFlag_ = true;
            swiperController_->SwipeTo(index);
        } else {
            swiperController_->SwipeToWithoutAnimation(index);
        }
    }

    UpdateIndicator(index);
    changeByClick_ = true;
    clickRepeat_ = true;
    if (duration > 0 && CanScroll()) {
        targetIndex_ = index;
    } else if (duration <= 0) {
        jumpIndex_ = index;
    } else {
        TriggerTranslateAnimation(indicator, index);
    }
    swiperStartIndex_ = indicator;
    animationTargetIndex_ = index;
    UpdateTextColorAndFontWeight(index);
    UpdateSubTabBoard(index);
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void TabBarPattern::HandleTouchEvent(TouchType touchType, int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto totalCount = host->TotalChildCount() - MASK_COUNT;
    if (IsContainsBuilder() || totalCount < 0) {
        return;
    }

    if (touchType == TouchType::DOWN && index >= 0 && index < totalCount) {
        HandleTouchDown(index);
        touchingIndex_.insert(index);
        return;
    }

    if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
        HandleTouchUp(index);
        touchingIndex_.erase(index);
    }
}

int32_t TabBarPattern::CalculateSelectedIndex(const Offset& info)
{
    if (visibleItemPosition_.empty()) {
        return -1;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, -1);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, -1);
    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, -1);
    auto axis = layoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
    auto mainSize = geometryNode->GetFrameSize().MainSize(axis);
    auto local = isRTL_ && axis == Axis::HORIZONTAL ? OffsetF(mainSize - info.GetX(), info.GetY())
                                                    : OffsetF(info.GetX(), info.GetY());
    auto leftPadding = GetLeftPadding();
    for (auto& iter : visibleItemPosition_) {
        if (GreatOrEqual(local.GetMainOffset(axis), iter.second.startPos + leftPadding) &&
            LessOrEqual(local.GetMainOffset(axis), iter.second.endPos + leftPadding)) {
            return iter.first;
        }
    }
    return -1;
}

void TabBarPattern::HandleTouchDown(int32_t index)
{
    const auto& removeSwiperEventCallback = swiperController_->GetRemoveSwiperEventCallback();
    if (removeSwiperEventCallback) {
        removeSwiperEventCallback();
    }
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    PlayPressAnimation(index, tabTheme->GetSubTabBarPressedColor(), AnimationType::PRESS);
}

void TabBarPattern::HandleTouchUp(int32_t index)
{
    const auto& addSwiperEventCallback = swiperController_->GetAddSwiperEventCallback();
    if (addSwiperEventCallback) {
        addSwiperEventCallback();
    }
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    if (hoverIndex_.value_or(-1) == index) {
        PlayPressAnimation(index, GetSubTabBarHoverColor(index), AnimationType::HOVERTOPRESS);
        return;
    }
    PlayPressAnimation(index, Color::TRANSPARENT, AnimationType::PRESS);
    if (hoverIndex_.has_value()) {
        PlayPressAnimation(hoverIndex_.value(), GetSubTabBarHoverColor(hoverIndex_.value()), AnimationType::HOVER);
    }
}

void TabBarPattern::PlayPressAnimation(int32_t index, const Color& pressColor, AnimationType animationType)
{
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE) &&
        tabBarStyle_ == TabBarStyle::BOTTOMTABBATSTYLE && animationType == AnimationType::PRESS) {
        return;
    }
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    AnimationOption option = AnimationOption();
    option.SetDuration(animationType == AnimationType::HOVERTOPRESS
                           ? static_cast<int32_t>(tabTheme->GetSubTabBarHoverToPressDuration())
                           : static_cast<int32_t>(tabTheme->GetSubTabBarHoverDuration()));
    option.SetDelay(0);
    option.SetCurve(animationType == AnimationType::PRESS   ? DurationCubicCurve
                    : animationType == AnimationType::HOVER ? Curves::FRICTION
                                                            : Curves::SHARP);
    option.SetFillMode(FillMode::FORWARDS);
    Color color = pressColor;
    auto layoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (index < 0 || index >= static_cast<int32_t>(tabBarStyles_.size()) ||
        index >= static_cast<int32_t>(selectedModes_.size()) ||
        index >= static_cast<int32_t>(indicatorStyles_.size())) {
        return;
    }
    if (color == Color::TRANSPARENT && tabBarStyles_[index] == TabBarStyle::SUBTABBATSTYLE && index == indicator_ &&
        selectedModes_[index] == SelectedMode::BOARD &&
        layoutProperty->GetAxis().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL) {
        color = indicatorStyles_[index].color;
    }
    AnimationUtils::Animate(option, [weak = AceType::WeakClaim(this), selectedIndex = index, color = color]() {
        auto tabBar = weak.Upgrade();
        CHECK_NULL_VOID(tabBar);
        auto host = tabBar->GetHost();
        CHECK_NULL_VOID(host);
        auto columnNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(selectedIndex));
        CHECK_NULL_VOID(columnNode);
        auto renderContext = columnNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        if (selectedIndex < static_cast<int32_t>(tabBar->tabBarStyles_.size()) &&
            tabBar->tabBarStyles_[selectedIndex] != TabBarStyle::SUBTABBATSTYLE) {
            BorderRadiusProperty borderRadiusProperty;
            auto pipelineContext = host->GetContext();
            CHECK_NULL_VOID(pipelineContext);
            auto tabTheme = pipelineContext->GetTheme<TabTheme>();
            CHECK_NULL_VOID(tabTheme);
            borderRadiusProperty.SetRadius(tabTheme->GetFocusIndicatorRadius());
            renderContext->UpdateBorderRadius(borderRadiusProperty);
        }
        renderContext->UpdateBackgroundColor(color);
        columnNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }, [weak = AceType::WeakClaim(this), selectedIndex = index]() {
        auto tabBar = weak.Upgrade();
        CHECK_NULL_VOID(tabBar);
        if (selectedIndex < static_cast<int32_t>(tabBar->tabBarStyles_.size()) &&
            tabBar->tabBarStyles_[selectedIndex] != TabBarStyle::SUBTABBATSTYLE) {
            auto host = tabBar->GetHost();
            CHECK_NULL_VOID(host);
            auto columnNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(selectedIndex));
            CHECK_NULL_VOID(columnNode);
            auto renderContext = columnNode->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->ResetBorderRadius();
            columnNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    }, nullptr, Claim(pipelineContext));
}

void TabBarPattern::OnTabBarIndexChange(int32_t index)
{
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddAfterRenderTask([weak = WeakClaim(this), index]() {
        auto tabBarPattern = weak.Upgrade();
        CHECK_NULL_VOID(tabBarPattern);
        auto tabBarNode = tabBarPattern->GetHost();
        CHECK_NULL_VOID(tabBarNode);
        auto tabBarLayoutProperty = tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>();
        CHECK_NULL_VOID(tabBarLayoutProperty);
        if (!tabBarPattern->IsMaskAnimationByCreate()) {
            tabBarPattern->HandleBottomTabBarChange(index);
        }
        tabBarPattern->SetMaskAnimationByCreate(false);
        tabBarPattern->SetIndicator(index);
        tabBarPattern->UpdateSubTabBoard(index);
        tabBarPattern->UpdatePaintIndicator(index, true);
        tabBarPattern->UpdateTextColorAndFontWeight(index);
        if (!tabBarPattern->GetClickRepeat() || tabBarLayoutProperty->GetIndicator().value_or(0) == index) {
            tabBarPattern->ResetIndicatorAnimationState();
            tabBarPattern->UpdateIndicator(index);
        }
        tabBarPattern->isTouchingSwiper_ = false;
        tabBarPattern->SetClickRepeat(false);
        if (tabBarPattern->GetChangeByClick()) {
            tabBarPattern->SetChangeByClick(false);
            return;
        }
        if (tabBarLayoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED) == TabBarMode::SCROLLABLE) {
            tabBarPattern->UpdateAnimationDuration();
            auto duration = tabBarPattern->GetAnimationDuration().value_or(0);
            if (duration > 0 && tabBarPattern->CanScroll()) {
                tabBarPattern->StopTranslateAnimation();
                tabBarPattern->targetIndex_ = index;
                tabBarNode->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
            } else {
                tabBarPattern->StopTranslateAnimation();
                tabBarPattern->jumpIndex_ = index;
                tabBarNode->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
            }
        }
    });
    pipeline->RequestFrame();
}

void TabBarPattern::UpdateCurrentOffset(float offset)
{
    if (NearZero(offset)) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    currentDelta_ = offset;
    UpdateSubTabBoard(indicator_);
    UpdateIndicator(indicator_);
    UpdatePaintIndicator(indicator_, true);
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void TabBarPattern::UpdateIndicator(int32_t indicator)
{
    auto layoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateIndicator(indicator);
    clickRepeat_ = false;

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    if (focusHub->IsCurrentFocus()) {
        return;
    }
    auto childFocusHub = GetCurrentFocusNode();
    CHECK_NULL_VOID(childFocusHub);
    focusHub->SetLastWeakFocusNode(AceType::WeakClaim(AceType::RawPtr(childFocusHub)));
}

void TabBarPattern::UpdateGradientRegions(bool needMarkDirty)
{
    auto layoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto barMode = layoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED);
    auto axis = layoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
    auto tabBarNode = GetHost();
    CHECK_NULL_VOID(tabBarNode);
    auto childCount = tabBarNode->TotalChildCount() - MASK_COUNT;
    auto mainSize = GetContentSize().MainSize(axis);

    std::fill(gradientRegions_.begin(), gradientRegions_.end(), false);
    if (barMode == TabBarMode::SCROLLABLE && !visibleItemPosition_.empty()) {
        auto visibleItemStartIndex = visibleItemPosition_.begin()->first;
        auto visibleItemEndIndex = visibleItemPosition_.rbegin()->first;
        auto visibleItemStartPos = visibleItemPosition_.begin()->second.startPos;
        auto visibleItemEndPos = visibleItemPosition_.rbegin()->second.endPos;
        if (visibleItemStartIndex > 0 || LessNotEqual(visibleItemStartPos, scrollMargin_)) {
            auto gradientIndex = axis == Axis::HORIZONTAL ? (isRTL_ ? RIGHT_GRADIENT : LEFT_GRADIENT)
                                                          : TOP_GRADIENT;
            gradientRegions_[gradientIndex] = true;
        }
        if (visibleItemEndIndex < childCount - 1 || GreatNotEqual(visibleItemEndPos + scrollMargin_, mainSize)) {
            auto gradientIndex = axis == Axis::HORIZONTAL ? (isRTL_ ? LEFT_GRADIENT : RIGHT_GRADIENT)
                                                          : BOTTOM_GRADIENT;
            gradientRegions_[gradientIndex] = true;
        }
    }

    if (needMarkDirty) {
        tabBarNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void TabBarPattern::UpdateTextColorAndFontWeight(int32_t indicator)
{
    auto tabBarNode = GetHost();
    CHECK_NULL_VOID(tabBarNode);
    auto columnNode = DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(indicator));
    CHECK_NULL_VOID(columnNode);
    int32_t selectedColumnId = 0;
    int32_t focusedColumnId = 0;
    GetColumnId(selectedColumnId, focusedColumnId, indicator);
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    auto tabBarLayoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    auto axis = tabBarLayoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
    int32_t index = 0;
    for (const auto& columnNode : tabBarNode->GetChildren()) {
        CHECK_NULL_VOID(columnNode);
        auto columnId = columnNode->GetId();
        auto iter = tabBarType_.find(columnId);
        if (iter != tabBarType_.end() && iter->second != TabBarParamType::NORMAL) {
            index++;
            continue;
        }
        if (labelStyles_.find(columnId) == labelStyles_.end() || columnNode->GetChildren().empty()) {
            index++;
            continue;
        }
        auto textNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().back());
        CHECK_NULL_VOID(textNode);
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        auto isSelected = columnId == selectedColumnId;
        if (isSelected) {
            UpdateSelectedTextColor(tabTheme, axis, textLayoutProperty, index, columnId);
        } else {
            textLayoutProperty->UpdateTextColor(
                labelStyles_[columnId].unselectedColor.value_or(tabTheme->GetSubTabTextOffColor()));
        }
        UpdateSubTabFocusedTextColor(tabTheme, columnId == focusedColumnId, textLayoutProperty, index, isSelected);
        if (index < static_cast<int32_t>(tabBarStyles_.size()) && tabBarStyles_[index] == TabBarStyle::SUBTABBATSTYLE &&
            !labelStyles_[columnId].fontWeight.has_value()) {
            textLayoutProperty->UpdateFontWeight(isSelected ? FontWeight::MEDIUM : FontWeight::NORMAL);
        }
        textNode->MarkModifyDone();
        textNode->MarkDirtyNode();
        index++;
    }
}

void TabBarPattern::UpdateSelectedTextColor(const RefPtr<TabTheme>& tabTheme, OHOS::Ace::Axis axis,
    RefPtr<TextLayoutProperty> textLayoutProperty, int32_t index, int32_t columnId)
{
    auto selectedColor = index < static_cast<int32_t>(selectedModes_.size()) &&
                                 selectedModes_[index] == SelectedMode::BOARD && axis == Axis::HORIZONTAL
                             ? tabTheme->GetSubTabBoardTextOnColor()
                             : tabTheme->GetSubTabTextOnColor();
    textLayoutProperty->UpdateTextColor(labelStyles_[columnId].selectedColor.value_or(selectedColor));
}

void TabBarPattern::UpdateImageColor(int32_t indicator)
{
    auto tabBarNode = GetHost();
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    if (tabBarPattern->IsContainsBuilder()) {
        return;
    }
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    int32_t index = 0;
    for (const auto& columnNode : tabBarNode->GetChildren()) {
        CHECK_NULL_VOID(columnNode && !columnNode->GetChildren().empty());
        auto imageNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
        CHECK_NULL_VOID(imageNode);
        if (imageNode->GetTag() != V2::IMAGE_ETS_TAG) {
            index++;
            continue;
        }
        auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        auto imagePaintProperty = imageNode->GetPaintProperty<ImageRenderProperty>();
        CHECK_NULL_VOID(imagePaintProperty);
        ImageSourceInfo info;
        auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo().value_or(info);
        if (index >= 0 && index < static_cast<int32_t>(iconStyles_.size())) {
            if (indicator == index) {
                imagePaintProperty->UpdateSvgFillColor(iconStyles_[index].selectedColor.has_value() ?
                    iconStyles_[index].selectedColor.value() : tabTheme->GetBottomTabIconOn());
            } else {
                imagePaintProperty->UpdateSvgFillColor(iconStyles_[index].unselectedColor.has_value() ?
                    iconStyles_[index].unselectedColor.value() : tabTheme->GetBottomTabIconOff());
            }
        }
        imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
        imageNode->MarkModifyDone();
        imageNode->MarkDirtyNode();
        index++;
    }
    SetImageColorOnIndex(indicator);
}

void TabBarPattern::UpdateSymbolStats(int32_t index, int32_t preIndex)
{
    auto tabBarNode = GetHost();
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    if (tabBarPattern->IsContainsBuilder()) {
        return;
    }
    std::vector<int32_t> indexes = {index, preIndex};
    for (uint32_t i = 0; i < indexes.size(); i++) {
        if (indexes[i] < 0 || indexes[i] >= static_cast<int32_t>(symbolArray_.size())) {
            continue;
        }
        auto columnNode = DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(indexes[i]));
        CHECK_NULL_VOID(columnNode && !columnNode->GetChildren().empty());
        auto symbolNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
        CHECK_NULL_VOID(symbolNode);
        if (symbolNode->GetTag() != V2::SYMBOL_ETS_TAG) {
            continue;
        }
        auto symbolLayoutProperty = symbolNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(symbolLayoutProperty);
        TabContentModelNG::UpdateDefaultSymbol(tabTheme, symbolLayoutProperty);
        if (i == 0) {
            symbolLayoutProperty->UpdateSymbolColorList({tabTheme->GetBottomTabSymbolOn()});
            auto modifierOnApply = symbolArray_[indexes[i]].onApply;
            UpdateSymbolApply(symbolNode, symbolLayoutProperty, indexes[i], "selected");
            if (preIndex != -1) {
                TabContentModelNG::UpdateSymbolEffect(symbolLayoutProperty, true);
            }
        } else {
            symbolLayoutProperty->UpdateSymbolColorList({tabTheme->GetBottomTabSymbolOff()});
            UpdateSymbolApply(symbolNode, symbolLayoutProperty, indexes[i], "normal");
        }
        symbolNode->MarkModifyDone();
        symbolNode->MarkDirtyNode();
    }
}

void TabBarPattern::AdjustSymbolStats(int32_t index)
{
    auto tabBarNode = GetHost();
    CHECK_NULL_VOID(tabBarNode);

    for (int32_t i = 0; i < static_cast<int32_t>(tabBarNode->GetChildren().size()); i++) {
        if (i == index) {
            UpdateSymbolStats(index, -1);
            continue;
        }

        UpdateSymbolStats(-1, i);
    }
}

void TabBarPattern::UpdateSymbolApply(const RefPtr<NG::FrameNode>& symbolNode,
    RefPtr<TextLayoutProperty>& symbolProperty, int32_t index, std::string type)
{
    if (index < 0 || index >= static_cast<int32_t>(symbolArray_.size())) {
        return;
    }
    auto modifierOnApply = symbolArray_[index].onApply;
    if (type == "selected" && !symbolArray_[index].selectedFlag) {
        return;
    }
    if (modifierOnApply != nullptr) {
        modifierOnApply(AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(symbolNode)), type);
        TabContentModelNG::UpdateSymbolEffect(symbolProperty, false);
    }
}

void TabBarPattern::UpdateSymbolEffect(int32_t index)
{
    if (index != GetImageColorOnIndex().value_or(indicator_)) {
        return;
    }
    auto tabBarNode = GetHost();
    CHECK_NULL_VOID(tabBarNode);
    auto columnNode = DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(index));
    CHECK_NULL_VOID(columnNode && !columnNode->GetChildren().empty());
    auto symbolNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
    CHECK_NULL_VOID(symbolNode);
    if (symbolNode->GetTag() == V2::SYMBOL_ETS_TAG) {
        auto symbolLayoutProperty = symbolNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(symbolLayoutProperty);
        auto symbolEffectOptions = symbolLayoutProperty->GetSymbolEffectOptionsValue(SymbolEffectOptions());
        symbolEffectOptions.SetIsTxtActive(false);
        symbolLayoutProperty->UpdateSymbolEffectOptions(symbolEffectOptions);
    }
}

void TabBarPattern::UpdateSubTabBoard(int32_t index)
{
    auto layoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto axis = layoutProperty->GetAxis().value_or(Axis::HORIZONTAL);

    if (index < 0 || index >= static_cast<int32_t>(indicatorStyles_.size()) ||
        index >= static_cast<int32_t>(selectedModes_.size())) {
        return;
    }
    auto tabBarNode = GetHost();
    CHECK_NULL_VOID(tabBarNode);
    int32_t selectedColumnId = 0;
    int32_t focusedColumnId = 0;
    GetColumnId(selectedColumnId, focusedColumnId, index);
    auto pipelineContext = tabBarNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    for (auto& iter : visibleItemPosition_) {
        if (iter.first < 0 || iter.first >= static_cast<int32_t>(tabBarStyles_.size())) {
            break;
        }
        auto columnFrameNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(iter.first));
        CHECK_NULL_VOID(columnFrameNode);
        auto renderContext = columnFrameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        if (tabBarStyles_[iter.first] == TabBarStyle::SUBTABBATSTYLE) {
            UpdateSubTabBarItemStyles(columnFrameNode, focusedColumnId, selectedColumnId, axis, index);
            columnFrameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    }
}

SelectedMode TabBarPattern::GetSelectedMode() const
{
    if (indicator_ >= static_cast<int32_t>(selectedModes_.size())) {
        return SelectedMode::INDICATOR;
    } else {
        return selectedModes_[indicator_];
    }
}

bool TabBarPattern::IsContainsBuilder()
{
    return std::any_of(tabBarType_.begin(), tabBarType_.end(), [](const auto& isBuilder) {
        return isBuilder.second == TabBarParamType::CUSTOM_BUILDER ||
               isBuilder.second == TabBarParamType::COMPONENT_CONTENT;
    });
}

void TabBarPattern::PlayTabBarTranslateAnimation(AnimationOption option, float targetCurrentOffset)
{
    auto weak = AceType::WeakClaim(this);
    auto host = GetHost();

    currentOffset_ = 0.0f;
    host->CreateAnimatablePropertyFloat(TAB_BAR_PROPERTY_NAME, 0, [weak](float value) {
        auto tabBarPattern = weak.Upgrade();
        CHECK_NULL_VOID(tabBarPattern);
        tabBarPattern->currentDelta_ = value - tabBarPattern->currentOffset_;
        tabBarPattern->currentOffset_ = value;
        auto host = tabBarPattern->GetHost();
        host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    });
    host->UpdateAnimatablePropertyFloat(TAB_BAR_PROPERTY_NAME, currentOffset_);
    translateAnimationIsRunning_ = true;
    auto pipeline = host->GetContextRefPtr();
    translateAnimation_ = AnimationUtils::StartAnimation(
        option,
        [weakHost = WeakClaim(RawPtr(host)), targetCurrentOffset]() {
            auto host = weakHost.Upgrade();
            CHECK_NULL_VOID(host);
            host->UpdateAnimatablePropertyFloat(TAB_BAR_PROPERTY_NAME, targetCurrentOffset);
        },
        [weak]() {
            auto tabBarPattern = weak.Upgrade();
            CHECK_NULL_VOID(tabBarPattern);
            tabBarPattern->translateAnimationIsRunning_ = false;
        },
        nullptr, pipeline);
}

void TabBarPattern::PlayIndicatorTranslateAnimation(AnimationOption option, RectF originalPaintRect,
    RectF targetPaintRect, float targetOffset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    isAnimating_ = true;
    turnPageRate_ = 0.0f;
    indicatorStartPos_ = originalPaintRect.GetX() + originalPaintRect.Width() / HALF_OF_WIDTH;
    indicatorEndPos_ = targetPaintRect.GetX() + targetPaintRect.Width() / HALF_OF_WIDTH + targetOffset;
    auto propertyName = INDICATOR_OFFSET_PROPERTY_NAME;
    if (NearZero(indicatorEndPos_ - indicatorStartPos_)) {
        indicatorStartPos_ = originalPaintRect.Width();
        indicatorEndPos_ = targetPaintRect.Width();
        propertyName = INDICATOR_WIDTH_PROPERTY_NAME;
    }
    CreateIndicatorTranslateProperty(host, propertyName);

    host->UpdateAnimatablePropertyFloat(propertyName, indicatorStartPos_);
    indicatorAnimationIsRunning_ = true;
    auto pipeline = host->GetContextRefPtr();
    tabbarIndicatorAnimation_ = AnimationUtils::StartAnimation(
        option,
        [weakHost = WeakClaim(RawPtr(host)), propertyName, endPos = indicatorEndPos_]() {
            auto host = weakHost.Upgrade();
            CHECK_NULL_VOID(host);
            host->UpdateAnimatablePropertyFloat(propertyName, endPos);
        },
        [weak = AceType::WeakClaim(this)]() {
            auto tabBarPattern = weak.Upgrade();
            CHECK_NULL_VOID(tabBarPattern);
            tabBarPattern->indicatorAnimationIsRunning_ = false;
        },
        nullptr, pipeline);
}

void TabBarPattern::CreateIndicatorTranslateProperty(const RefPtr<FrameNode>& host, const std::string& propertyName)
{
    if (propertyName == INDICATOR_WIDTH_PROPERTY_NAME) {
        host->CreateAnimatablePropertyFloat(propertyName, 0, [weak = AceType::WeakClaim(this)](float value) {
            auto tabBarPattern = weak.Upgrade();
            CHECK_NULL_VOID(tabBarPattern);
            if (!tabBarPattern->isAnimating_ ||
                NearZero(tabBarPattern->indicatorEndPos_ - tabBarPattern->indicatorStartPos_)) {
                return;
            }
            tabBarPattern->turnPageRate_ = (value - tabBarPattern->indicatorStartPos_) /
                (tabBarPattern->indicatorEndPos_ - tabBarPattern->indicatorStartPos_);
            tabBarPattern->UpdateIndicatorCurrentOffset(0.0f);
        });
    } else if (propertyName == INDICATOR_OFFSET_PROPERTY_NAME) {
        host->CreateAnimatablePropertyFloat(propertyName, 0, [weak = AceType::WeakClaim(this)](float value) {
            auto tabBarPattern = weak.Upgrade();
            CHECK_NULL_VOID(tabBarPattern);
            if (!tabBarPattern->isAnimating_ ||
                NearZero(tabBarPattern->indicatorEndPos_ - tabBarPattern->indicatorStartPos_)) {
                return;
            }
            tabBarPattern->turnPageRate_ = (value - tabBarPattern->indicatorStartPos_) /
                (tabBarPattern->indicatorEndPos_ - tabBarPattern->indicatorStartPos_);
            tabBarPattern->UpdateIndicatorCurrentOffset(
                static_cast<float>(value - tabBarPattern->currentIndicatorOffset_));
        });
    }
}

void TabBarPattern::StopTranslateAnimation(bool isImmediately)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    if (isImmediately) {
        AnimationOption option;
        option.SetDuration(0);
        option.SetCurve(Curves::LINEAR);
        AnimationUtils::Animate(
            option,
            [weak = WeakClaim(this)]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                auto host = pattern->GetHost();
                CHECK_NULL_VOID(host);
                host->UpdateAnimatablePropertyFloat(TAB_BAR_PROPERTY_NAME, pattern->currentOffset_);
            },
            nullptr, nullptr, pipeline);
    } else {
        if (translateAnimation_) {
            AnimationUtils::StopAnimation(translateAnimation_);
        }
    }

    if (tabbarIndicatorAnimation_) {
        AnimationUtils::StopAnimation(tabbarIndicatorAnimation_);
    }

    indicatorAnimationIsRunning_ = false;
    translateAnimationIsRunning_ = false;
    isAnimating_ = false;
}

void TabBarPattern::TriggerTranslateAnimation(int32_t currentIndex, int32_t targetIndex)
{
    auto curve = GetAnimationCurve(DurationCubicCurve);
    StopTranslateAnimation();
    SetSwiperCurve(curve);
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    UpdateAnimationDuration();
    AnimationOption option = AnimationOption();
    option.SetDuration(static_cast<int32_t>(GetAnimationDuration().value_or(
        tabTheme->GetTabContentAnimationDuration())));
    option.SetCurve(curve);
    option.SetFillMode(FillMode::FORWARDS);

    auto targetOffset = 0.0f;
    if (CanScroll()) {
        targetOffset = CalculateTargetOffset(targetIndex);
        PlayTabBarTranslateAnimation(option, targetOffset);
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (std::count(tabBarStyles_.begin(), tabBarStyles_.end(), TabBarStyle::SUBTABBATSTYLE) !=
            static_cast<int32_t>(tabBarStyles_.size()) ||
        layoutProperty->GetAxisValue(Axis::HORIZONTAL) != Axis::HORIZONTAL) {
        return;
    }
    auto paintProperty = host->GetPaintProperty<TabBarPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateIndicator(targetIndex);
    if (!changeByClick_) {
        return;
    }
    auto originalPaintRect = GetOriginalPaintRect(currentIndex);
    auto targetPaintRect = layoutProperty->GetIndicatorRect(targetIndex);
    PlayIndicatorTranslateAnimation(option, originalPaintRect, targetPaintRect, targetOffset);
}

RectF TabBarPattern::GetOriginalPaintRect(int32_t currentIndex)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, RectF());
    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, RectF());
    auto originalPaintRect = layoutProperty->GetIndicatorRect(currentIndex);
    if (!visibleItemPosition_.empty()) {
        auto mainSize = GetContentSize().MainSize(axis_);
        if (currentIndex >= 0 && currentIndex < visibleItemPosition_.begin()->first) {
            if (isRTL_) {
                originalPaintRect.SetLeft(mainSize - visibleItemPosition_.begin()->second.startPos);
            } else {
                originalPaintRect.SetLeft(visibleItemPosition_.begin()->second.startPos - originalPaintRect.Width());
            }
            currentIndicatorOffset_ = originalPaintRect.GetX() + originalPaintRect.Width() / HALF_OF_WIDTH;
        } else if (currentIndex < host->TotalChildCount() - MASK_COUNT &&
            currentIndex > visibleItemPosition_.rbegin()->first) {
            if (isRTL_) {
                originalPaintRect.SetLeft(
                    mainSize - visibleItemPosition_.rbegin()->second.endPos - originalPaintRect.Width());
            } else {
                originalPaintRect.SetLeft(visibleItemPosition_.rbegin()->second.endPos);
            }
            currentIndicatorOffset_ = originalPaintRect.GetX() + originalPaintRect.Width() / HALF_OF_WIDTH;
        }
    }
    return originalPaintRect;
}

float TabBarPattern::CalculateTargetOffset(int32_t targetIndex)
{
    auto targetOffset = 0.0f;
    auto space = GetSpace(targetIndex);
    auto startPos = 0.0f;
    auto endPos = 0.0f;
    auto iter = visibleItemPosition_.find(targetIndex);
    if (iter != visibleItemPosition_.end()) {
        startPos = iter->second.startPos;
        endPos = iter->second.endPos;
    }
    auto frontChildrenMainSize = CalculateFrontChildrenMainSize(targetIndex);
    auto backChildrenMainSize = CalculateBackChildrenMainSize(targetIndex);
    if (Negative(space)) {
        targetOffset = isRTL_ && axis_ == Axis::HORIZONTAL ? (startPos - scrollMargin_)
                                                            : (scrollMargin_ - startPos);
    } else if (LessOrEqual(frontChildrenMainSize, space)) {
        targetOffset = isRTL_ && axis_ == Axis::HORIZONTAL ? (startPos - frontChildrenMainSize)
                                                            : (frontChildrenMainSize - startPos);
    } else if (LessOrEqual(backChildrenMainSize, space)) {
        auto mainSize = GetContentSize().MainSize(axis_);
        targetOffset = isRTL_ && axis_ == Axis::HORIZONTAL ? (backChildrenMainSize - (mainSize - endPos))
                                                            : (mainSize - backChildrenMainSize - endPos);
    } else {
        targetOffset = isRTL_ && axis_ == Axis::HORIZONTAL ? (startPos - space) : (space - startPos);
    }
    return targetOffset;
}

void TabBarPattern::UpdateIndicatorCurrentOffset(float offset)
{
    currentIndicatorOffset_ = currentIndicatorOffset_ + offset;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

RefPtr<NodePaintMethod> TabBarPattern::CreateNodePaintMethod()
{
    if (!tabBarModifier_) {
        tabBarModifier_ = AceType::MakeRefPtr<TabBarModifier>();
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, nullptr);
    auto tabBarRect = geometryNode->GetFrameRect(true);
    Color bgColor = GetTabBarBackgroundColor();
    RectF tabBarItemRect;
    auto layoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    auto paintProperty = GetPaintProperty<TabBarPaintProperty>();
    if (layoutProperty && paintProperty && paintProperty->GetIndicator().has_value()) {
        tabBarItemRect = layoutProperty->GetIndicatorRect(paintProperty->GetIndicator().value());
    }
    IndicatorStyle indicatorStyle;
    OffsetF indicatorOffset = { currentIndicatorOffset_, tabBarItemRect.GetY() };
    GetIndicatorStyle(indicatorStyle, indicatorOffset, tabBarItemRect);
    indicatorOffset.AddX(-indicatorStyle.width.ConvertToPx() / HALF_OF_WIDTH);
    auto hasIndicator = indicator_ < static_cast<int32_t>(selectedModes_.size()) ?
        std::count(selectedModes_.begin(), selectedModes_.end(), SelectedMode::INDICATOR) ==
        static_cast<int32_t>(selectedModes_.size()) && !NearZero(tabBarItemRect.Height()) : 0;
    return MakeRefPtr<TabBarPaintMethod>(tabBarModifier_, tabBarRect, gradientRegions_, bgColor, indicatorStyle,
        indicatorOffset, hasIndicator);
}

Color TabBarPattern::GetTabBarBackgroundColor() const
{
    Color bgColor = Color::WHITE;
    auto tabBarNode = GetHost();
    CHECK_NULL_RETURN(tabBarNode, bgColor);
    auto tabBarCtx = tabBarNode->GetRenderContext();
    CHECK_NULL_RETURN(tabBarCtx, bgColor);
    if (tabBarCtx->GetBackgroundColor()) {
        bgColor = *tabBarCtx->GetBackgroundColor();
    } else {
        auto tabsNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetParent());
        CHECK_NULL_RETURN(tabsNode, bgColor);
        auto tabsCtx = tabsNode->GetRenderContext();
        CHECK_NULL_RETURN(tabsCtx, bgColor);
        if (tabsCtx->GetBackgroundColor()) {
            bgColor = *tabsCtx->GetBackgroundColor();
        } else {
            auto pipeline = tabBarNode->GetContext();
            CHECK_NULL_RETURN(pipeline, bgColor);
            auto tabTheme = pipeline->GetTheme<TabTheme>();
            CHECK_NULL_RETURN(tabTheme, bgColor);
            bgColor = tabTheme->GetBackgroundColor().ChangeAlpha(0xff);
        }
    }
    return bgColor;
}

void TabBarPattern::GetIndicatorStyle(IndicatorStyle& indicatorStyle, OffsetF& indicatorOffset, RectF& tabBarItemRect)
{
    auto paintProperty = GetPaintProperty<TabBarPaintProperty>();
    int32_t showingIndicator = indicator_;
    if (paintProperty && paintProperty->HasIndicator()) {
        showingIndicator = paintProperty->GetIndicatorValue();
    }
    if (showingIndicator < 0 || showingIndicator >= static_cast<int32_t>(indicatorStyles_.size())) {
        return;
    }
    indicatorStyle = indicatorStyles_[showingIndicator];
    if (NonPositive(indicatorStyle.width.Value())) {
        indicatorStyle.width = Dimension(tabBarItemRect.Width());
    }
    if ((!isTouchingSwiper_ && !isAnimating_) || axis_ != Axis::HORIZONTAL) {
        return;
    }
    if (LessOrEqual(turnPageRate_, 0.0f)) {
        turnPageRate_ = 0.0f;
    }
    if (GreatOrEqual(turnPageRate_, 1.0f)) {
        turnPageRate_ = 1.0f;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto totalCount = host->TotalChildCount() - MASK_COUNT;
    if (!IsValidIndex(swiperStartIndex_) || swiperStartIndex_ >= totalCount ||
        swiperStartIndex_ >= static_cast<int32_t>(indicatorStyles_.size())) {
        return;
    }

    auto nextIndex = isTouchingSwiper_ ? swiperStartIndex_ + 1 : animationTargetIndex_.value_or(-1);
    if (!IsValidIndex(nextIndex) || nextIndex >= totalCount ||
        nextIndex >= static_cast<int32_t>(indicatorStyles_.size())) {
        return;
    }
    CalculateIndicatorStyle(swiperStartIndex_, nextIndex, indicatorStyle, indicatorOffset);
}

void TabBarPattern::CalculateIndicatorStyle(
    int32_t startIndex, int32_t nextIndex, IndicatorStyle& indicatorStyle, OffsetF& indicatorOffset)
{
    auto layoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    indicatorStyle = indicatorStyles_[startIndex];
    auto startItemRect = layoutProperty->GetIndicatorRect(startIndex);
    if (NonPositive(indicatorStyle.width.Value())) {
        indicatorStyle.width = Dimension(startItemRect.Width());
    }
    IndicatorStyle nextIndicatorStyle = indicatorStyles_[nextIndex];
    auto nextItemRect = layoutProperty->GetIndicatorRect(nextIndex);
    if (NonPositive(nextIndicatorStyle.width.Value())) {
        nextIndicatorStyle.width = Dimension(nextItemRect.Width());
    }

    indicatorStyle.width = Dimension(indicatorStyle.width.ConvertToPx() +
        (nextIndicatorStyle.width.ConvertToPx() - indicatorStyle.width.ConvertToPx()) * turnPageRate_);
    indicatorStyle.marginTop = Dimension(indicatorStyle.marginTop.ConvertToPx() +
        (nextIndicatorStyle.marginTop.ConvertToPx() - indicatorStyle.marginTop.ConvertToPx()) * turnPageRate_);
    indicatorStyle.height = Dimension(indicatorStyle.height.ConvertToPx() +
        (nextIndicatorStyle.height.ConvertToPx() - indicatorStyle.height.ConvertToPx()) * turnPageRate_);
    LinearColor color = LinearColor(indicatorStyle.color) +
        (LinearColor(nextIndicatorStyle.color) - LinearColor(indicatorStyle.color)) * turnPageRate_;
    indicatorStyle.color = color.ToColor();
    indicatorOffset.SetY(startItemRect.GetY() + (nextItemRect.GetY() - startItemRect.GetY()) * turnPageRate_);
}

float TabBarPattern::GetSpace(int32_t indicator)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    auto childFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(indicator));
    CHECK_NULL_RETURN(childFrameNode, 0.0f);
    auto childGeometryNode = childFrameNode->GetGeometryNode();

    return (GetContentSize().MainSize(axis_) - childGeometryNode->GetMarginFrameSize().MainSize(axis_)) / 2;
}

float TabBarPattern::CalculateFrontChildrenMainSize(int32_t indicator)
{
    float frontChildrenMainSize = scrollMargin_;
    if (visibleItemPosition_.empty()) {
        return frontChildrenMainSize;
    }
    for (auto& iter : visibleItemPosition_) {
        if (iter.first < indicator) {
            frontChildrenMainSize += iter.second.endPos - iter.second.startPos;
        }
    }
    return frontChildrenMainSize;
}

float TabBarPattern::CalculateBackChildrenMainSize(int32_t indicator)
{
    float backChildrenMainSize = scrollMargin_;
    if (visibleItemPosition_.empty()) {
        return backChildrenMainSize;
    }
    for (auto& iter : visibleItemPosition_) {
        if (iter.first > indicator) {
            backChildrenMainSize += iter.second.endPos - iter.second.startPos;
        }
    }
    return backChildrenMainSize;
}

void TabBarPattern::SetEdgeEffect(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(gestureHub);
    if (scrollEffect_) {
        gestureHub->RemoveScrollEdgeEffect(scrollEffect_);
        scrollEffect_.Reset();
    }
    if (!scrollEffect_) {
        auto springEffect = AceType::MakeRefPtr<ScrollSpringEffect>();
        CHECK_NULL_VOID(springEffect);
        springEffect->SetOutBoundaryCallback([weak = AceType::WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_RETURN(pattern, false);
            return pattern->IsAtTop() || pattern->IsAtBottom();
        });
        // add callback to springEdgeEffect
        SetEdgeEffectCallback(springEffect);
        scrollEffect_ = springEffect;
        gestureHub->AddScrollEdgeEffect(axis_, scrollEffect_);
    }
}

void TabBarPattern::SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect)
{
    scrollEffect->SetCurrentPositionCallback([weak = AceType::WeakClaim(this)]() -> double {
        auto tabBar = weak.Upgrade();
        CHECK_NULL_RETURN(tabBar, 0.0);
        if (tabBar->visibleItemPosition_.empty()) {
            return tabBar->scrollMargin_ + tabBar->currentDelta_;
        }
        if (tabBar->isRTL_ && tabBar->axis_ == Axis::HORIZONTAL) {
            return tabBar->GetContentSize().Width() - tabBar->visibleItemPosition_.rbegin()->second.endPos +
                tabBar->currentDelta_;
        } else {
            return tabBar->visibleItemPosition_.begin()->second.startPos + tabBar->currentDelta_;
        }
    });
    auto leadingCallback = [weak = AceType::WeakClaim(this)]() -> double {
        auto tabBar = weak.Upgrade();
        CHECK_NULL_RETURN(tabBar, 0.0);
        if (tabBar->visibleItemPosition_.empty()) {
            return tabBar->GetContentSize().MainSize(tabBar->axis_) - tabBar->scrollMargin_;
        }
        auto visibleChildrenMainSize = tabBar->visibleItemPosition_.rbegin()->second.endPos -
            tabBar->visibleItemPosition_.begin()->second.startPos;
        return tabBar->GetContentSize().MainSize(tabBar->axis_) - visibleChildrenMainSize - tabBar->scrollMargin_;
    };
    auto trailingCallback = [weak = AceType::WeakClaim(this)]() -> double {
        auto tabBar = weak.Upgrade();
        CHECK_NULL_RETURN(tabBar, 0.0);
        return tabBar->scrollMargin_;
    };
    scrollEffect->SetLeadingCallback(leadingCallback);
    scrollEffect->SetTrailingCallback(trailingCallback);
    scrollEffect->SetInitLeadingCallback(leadingCallback);
    scrollEffect->SetInitTrailingCallback(trailingCallback);
}

bool TabBarPattern::IsAtTop() const
{
    if (visibleItemPosition_.empty()) {
        return false;
    }

    auto visibleItemStartIndex = visibleItemPosition_.begin()->first;
    auto visibleItemStartPos = visibleItemPosition_.begin()->second.startPos;
    return visibleItemStartIndex == 0 && GreatOrEqual(visibleItemStartPos, scrollMargin_);
}

bool TabBarPattern::IsAtBottom() const
{
    if (visibleItemPosition_.empty()) {
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);

    auto visibleItemEndIndex = visibleItemPosition_.rbegin()->first;
    auto visibleItemEndPos = visibleItemPosition_.rbegin()->second.endPos;
    auto childCount = host->TotalChildCount() - MASK_COUNT;
    auto mainSize = GetContentSize().MainSize(axis_);
    return visibleItemEndIndex == (childCount - 1) && LessOrEqual(visibleItemEndPos, mainSize - scrollMargin_);
}

bool TabBarPattern::IsOutOfBoundary()
{
    if (visibleItemPosition_.empty()) {
        return false;
    }

    auto visibleItemStartPos = visibleItemPosition_.begin()->second.startPos;
    auto visibleItemEndPos = visibleItemPosition_.rbegin()->second.endPos;
    auto mainSize = GetContentSize().MainSize(axis_);
    bool outOfStart = Positive(visibleItemStartPos - scrollMargin_) &&
        GreatNotEqual(visibleItemEndPos + scrollMargin_, mainSize);
    bool outOfEnd = LessNotEqual(visibleItemEndPos + scrollMargin_, mainSize) &&
        Negative(visibleItemStartPos - scrollMargin_);
    return outOfStart || outOfEnd;
}

void TabBarPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionScrollForward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto tabBarLayoutProperty = pattern->GetLayoutProperty<TabBarLayoutProperty>();
        CHECK_NULL_VOID(tabBarLayoutProperty);
        auto frameNode = pattern->GetHost();
        CHECK_NULL_VOID(frameNode);
        if (tabBarLayoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED) == TabBarMode::SCROLLABLE &&
            frameNode->TotalChildCount() - MASK_COUNT > 1) {
            auto index =
                std::clamp(pattern->accessibilityFocusIndicator_ + 1, 0, frameNode->TotalChildCount() - MASK_COUNT - 1);
            pattern->FocusCurrentOffset(index);
            // AccessibilityEventType::SCROLL_END
        }
    });

    accessibilityProperty->SetActionScrollBackward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto tabBarLayoutProperty = pattern->GetLayoutProperty<TabBarLayoutProperty>();
        CHECK_NULL_VOID(tabBarLayoutProperty);
        auto frameNode = pattern->GetHost();
        CHECK_NULL_VOID(frameNode);
        if (tabBarLayoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED) == TabBarMode::SCROLLABLE &&
           frameNode->TotalChildCount() - MASK_COUNT > 1) {
            auto index =
                std::clamp(pattern->accessibilityFocusIndicator_ - 1, 0, frameNode->TotalChildCount() - MASK_COUNT - 1);
            pattern->FocusCurrentOffset(index);
            // AccessibilityEventType::SCROLL_END
        }
    });
}

std::string TabBarPattern::ProvideRestoreInfo()
{
    auto jsonObj = JsonUtil::Create(true);
    auto tabBarLayoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_RETURN(tabBarLayoutProperty, "");
    jsonObj->Put("Index", tabBarLayoutProperty->GetIndicator().value_or(0));
    return jsonObj->ToString();
}

void TabBarPattern::OnRestoreInfo(const std::string& restoreInfo)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto info = JsonUtil::ParseJsonString(restoreInfo);
    if (!info->IsValid() || !info->IsObject()) {
        return;
    }
    auto jsonIsOn = info->GetValue("Index");
    auto index = jsonIsOn->GetInt();
    auto totalCount = host->TotalChildCount();
    if (index < 0 || index >= totalCount || !swiperController_ ||
        indicator_ >= static_cast<int32_t>(tabBarStyles_.size())) {
        return;
    }
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_VOID(tabsFrameNode);
    auto tabsPattern = tabsFrameNode->GetPattern<TabsPattern>();
    UpdateIndicator(index);
    UpdateAnimationDuration();
    if (GetAnimationDuration().has_value()
        && (!tabsPattern || tabsPattern->GetAnimateMode() != TabAnimateMode::NO_ANIMATION)) {
        swiperController_->SwipeTo(index);
    } else {
        swiperController_->SwipeToWithoutAnimation(index);
    }
}

void TabBarPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    Pattern::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto selectedModes = JsonUtil::CreateArray(true);
    for (const auto& selectedMode : selectedModes_) {
        auto mode = JsonUtil::Create(true);
        mode->Put("mode", selectedMode == SelectedMode::INDICATOR ? "INDICATOR" : "BOARD");
        selectedModes->Put(mode);
    }
    json->PutExtAttr("selectedModes", selectedModes->ToString().c_str(), filter);

    auto indicatorStyles = JsonUtil::CreateArray(true);
    for (const auto& indicatorStyle : indicatorStyles_) {
        auto indicator = JsonUtil::Create(true);
        indicator->Put("color", indicatorStyle.color.ColorToString().c_str());
        indicator->Put("height", indicatorStyle.height.ToString().c_str());
        indicator->Put("width", indicatorStyle.width.ToString().c_str());
        indicator->Put("borderRadius", indicatorStyle.borderRadius.ToString().c_str());
        indicator->Put("marginTop", indicatorStyle.marginTop.ToString().c_str());
        indicatorStyles->Put(indicator);
    }
    json->PutExtAttr("indicatorStyles", indicatorStyles->ToString().c_str(), filter);

    auto tabBarStyles = JsonUtil::CreateArray(true);
    for (const auto& tabBarStyle : tabBarStyles_) {
        auto style = JsonUtil::Create(true);
        style->Put("style", tabBarStyle == TabBarStyle::NOSTYLE          ? "NOSTYLE"
                            : tabBarStyle == TabBarStyle::SUBTABBATSTYLE ? "SUBTABBATSTYLE"
                                                                         : "BOTTOMTABBATSTYLE");
        tabBarStyles->Put(style);
    }
    json->PutExtAttr("tabBarStyles", tabBarStyles->ToString().c_str(), filter);
}

void TabBarPattern::FromJson(const std::unique_ptr<JsonValue>& json)
{
    auto selectedModes = JsonUtil::ParseJsonString(json->GetString("selectedModes"));
    for (int32_t i = 0; i < selectedModes->GetArraySize(); i++) {
        auto selectedMode = selectedModes->GetArrayItem(i);
        auto mode = selectedMode->GetString("mode");
        SetSelectedMode(mode == "INDICATOR" ? SelectedMode::INDICATOR : SelectedMode::BOARD, i);
    }

    auto indicatorStyles = JsonUtil::ParseJsonString(json->GetString("indicatorStyles"));
    for (int32_t i = 0; i < indicatorStyles->GetArraySize(); i++) {
        auto indicatorStyle = indicatorStyles->GetArrayItem(i);
        IndicatorStyle style;
        style.color = Color::ColorFromString(indicatorStyle->GetString("color"));
        style.height = Dimension::FromString(indicatorStyle->GetString("height"));
        style.width = Dimension::FromString(indicatorStyle->GetString("width"));
        style.borderRadius = Dimension::FromString(indicatorStyle->GetString("borderRadius"));
        style.marginTop = Dimension::FromString(indicatorStyle->GetString("marginTop"));
        SetIndicatorStyle(style, i);
    }

    auto tabBarStyles = JsonUtil::ParseJsonString(json->GetString("tabBarStyles"));
    for (int32_t i = 0; i < tabBarStyles->GetArraySize(); i++) {
        auto tabBarStyle = tabBarStyles->GetArrayItem(i);
        auto style = tabBarStyle->GetString("style");
        SetTabBarStyle(style == "NOSTYLE"          ? TabBarStyle::NOSTYLE
                       : style == "SUBTABBATSTYLE" ? TabBarStyle::SUBTABBATSTYLE
                                                   : TabBarStyle::BOTTOMTABBATSTYLE,
            i);
    }

    auto layoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto indicatorValue = layoutProperty->GetIndicatorValue(0);
    UpdateIndicator(indicatorValue);
    UpdatePaintIndicator(indicatorValue, true);
    Pattern::FromJson(json);
}

void TabBarPattern::TabBarClickEvent(int32_t index) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_VOID(tabsNode);
    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabsPattern);
    auto tabBarClickEvent = tabsPattern->GetTabBarClickEvent();
    CHECK_NULL_VOID(tabBarClickEvent);
    auto event = *tabBarClickEvent;
    event(index);
}


void TabBarPattern::OnCustomContentTransition(int32_t fromIndex, int32_t toIndex)
{
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_VOID(swiperPattern);

    swiperPattern->OnCustomContentTransition(toIndex);
}

RefPtr<SwiperPattern> TabBarPattern::GetSwiperPattern() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_RETURN(swiperNode, nullptr);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    return swiperPattern;
}

bool TabBarPattern::CheckSwiperDisable() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, true);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_RETURN(tabsNode, true);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_RETURN(swiperNode, true);
    auto props = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(props, true);
    return props->GetDisableSwipe().value_or(false);
}

void TabBarPattern::SetSwiperCurve(const RefPtr<Curve>& curve) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(swiperPaintProperty);
    swiperPaintProperty->UpdateCurve(curve);
}

void TabBarPattern::ApplyTurnPageRateToIndicator(float turnPageRate)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    auto totalCount = host->TotalChildCount() - MASK_COUNT;
    CHECK_NULL_VOID(layoutProperty);
    swiperStartIndex_ = std::clamp(swiperStartIndex_, 0, totalCount - 1);
    CHECK_NULL_VOID(IsValidIndex(swiperStartIndex_));
    auto index = swiperStartIndex_ + 1;
    if (index >= totalCount || index >= static_cast<int32_t>(tabBarStyles_.size())) {
        swiperStartIndex_--;
        index--;
        turnPageRate = 1.0f;
    }
    if (Negative(turnPageRate)) {
        turnPageRate = 0.0f;
    }
    CHECK_NULL_VOID(IsValidIndex(index));
    if (GreatOrEqual(turnPageRate, 1.0f)) {
        turnPageRate_ = 1.0f;
    } else if (LessOrEqual(turnPageRate, 0.0f)) {
        turnPageRate_ = 0.0f;
    } else {
        if (turnPageRate_ <= TEXT_COLOR_THREDHOLD && turnPageRate > TEXT_COLOR_THREDHOLD) {
            UpdateTextColorAndFontWeight(index);
        } else if (turnPageRate <= 1.0f - TEXT_COLOR_THREDHOLD && turnPageRate_ > 1.0f - TEXT_COLOR_THREDHOLD) {
            UpdateTextColorAndFontWeight(swiperStartIndex_);
        }
        turnPageRate_ = turnPageRate;
    }
    auto originalPaintRect = layoutProperty->GetIndicatorRect(swiperStartIndex_);
    auto targetPaintRect = layoutProperty->GetIndicatorRect(index);
    auto paintRectDiff = std::abs(targetPaintRect.GetX() + targetPaintRect.Width() / 2 - originalPaintRect.GetX() -
                                  originalPaintRect.Width() / 2);

    currentIndicatorOffset_ = originalPaintRect.GetX() + originalPaintRect.Width() / 2 + paintRectDiff * turnPageRate_;
    if (isRTL_) {
        auto originalPaintRect = layoutProperty->GetIndicatorRect(swiperStartIndex_ + 1);
        auto targetPaintRect = layoutProperty->GetIndicatorRect(swiperStartIndex_ >= 0 ? swiperStartIndex_ : 0);
        auto paintRectDiff = std::abs(targetPaintRect.GetX() + targetPaintRect.Width() / HALF_OF_WIDTH -
                                      originalPaintRect.GetX() - originalPaintRect.Width() / HALF_OF_WIDTH);
        currentIndicatorOffset_ =
            originalPaintRect.GetX() + originalPaintRect.Width() / HALF_OF_WIDTH + paintRectDiff * (1 - turnPageRate_);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TabBarPattern::InitTurnPageRateEvent()
{
    SetTurnPageRateCallback();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto eventHub = swiperNode->GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (!animationStartEvent_) {
        AnimationStartEvent animationStartEvent =
            [weak = WeakClaim(this)](int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {
                auto pattern = weak.Upgrade();
                if (pattern) {
                    pattern->HandleBottomTabBarAnimation(targetIndex);
                }
            };
        animationStartEvent_ = std::make_shared<AnimationStartEvent>(std::move(animationStartEvent));
        eventHub->AddAnimationStartEvent(animationStartEvent_);
    }
    if (!animationEndEvent_) {
        AnimationEndEvent animationEndEvent =
            [weak = WeakClaim(this)](int32_t index, const AnimationCallbackInfo& info) {
                PerfMonitor::GetPerfMonitor()->End(PerfConstants::APP_TAB_SWITCH, true);
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                auto host = pattern->GetHost();
                CHECK_NULL_VOID(host);
                if (NearZero(pattern->turnPageRate_) || NearEqual(pattern->turnPageRate_, 1.0f)) {
                    pattern->isTouchingSwiper_ = false;
                    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
                }
                pattern->SetMaskAnimationExecuted(false);
            };
        animationEndEvent_ = std::make_shared<AnimationEndEvent>(std::move(animationEndEvent));
        eventHub->AddAnimationEndEvent(animationEndEvent_);
    }
}

void TabBarPattern::SetTurnPageRateCallback()
{
    CHECK_NULL_VOID(swiperController_);
    auto turnPageRateCallback = [weak = WeakClaim(this)](int32_t swipingIndex, float turnPageRate) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            if (!pattern->CheckSwiperDisable() && pattern->axis_ == Axis::HORIZONTAL && pattern->isTouchingSwiper_) {
                pattern->swiperStartIndex_ = swipingIndex;
                pattern->ApplyTurnPageRateToIndicator(turnPageRate);
            } else if (!pattern->isAnimating_) {
                pattern->turnPageRate_ = 0.0f;
            }
        }
    };
    swiperController_->SetTurnPageRateCallback(std::move(turnPageRateCallback));
}

void TabBarPattern::HandleBottomTabBarAnimation(int32_t index)
{
    auto preIndex = GetImageColorOnIndex().value_or(indicator_);
    if (preIndex < 0 || preIndex >= static_cast<int32_t>(tabBarStyles_.size())
        || index < 0 || index >= static_cast<int32_t>(tabBarStyles_.size())) {
        return;
    }
    if (tabBarStyles_[preIndex] != TabBarStyle::BOTTOMTABBATSTYLE &&
        tabBarStyles_[index] != TabBarStyle::BOTTOMTABBATSTYLE) {
        return;
    }
    if (preIndex != index) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
        CHECK_NULL_VOID(tabsNode);
        auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
        CHECK_NULL_VOID(tabsPattern);
        auto onChangeEvent = tabsPattern->GetChangeEvent();
        if (onChangeEvent) {
            (*onChangeEvent)(preIndex, index);
        }
        auto onIndexChangeEvent = tabsPattern->GetIndexChangeEvent();
        if (onIndexChangeEvent) {
            (*onIndexChangeEvent)(index);
        }
    }
    SetMaskAnimationExecuted(true);
}

SizeF TabBarPattern::GetContentSize() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, SizeF(0.0f, 0.0f));
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, SizeF(0.0f, 0.0f));
    auto contentSize = geometryNode->GetPaddingSize();
    contentSize.MinusWidth(barGridMargin_ * 2); // 2 means left margin and right margin
    return contentSize;
}

float TabBarPattern::GetLeftPadding() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0f);
    if (!geometryNode->GetPadding()) {
        return barGridMargin_;
    }
    return geometryNode->GetPadding()->left.value_or(0.0f) + barGridMargin_;
}

void TabBarPattern::UpdateAnimationDuration()
{
    if (animationDuration_.has_value() && animationDuration_.value() >= 0) {
        return;
    }

    std::optional<int32_t> duration;
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(swiperPaintProperty);
    duration = static_cast<int32_t>(tabTheme->GetTabContentAnimationDuration());
    if ((Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN) &&
        std::count(tabBarStyles_.begin(), tabBarStyles_.end(), TabBarStyle::BOTTOMTABBATSTYLE)) ||
        (!animationDuration_.has_value() && Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN))) {
        duration = 0;
    }
    SetAnimationDuration(duration.value());
    swiperPaintProperty->UpdateDuration(duration.value());
}

void TabBarPattern::DumpAdvanceInfo()
{
    isRTL_ ? DumpLog::GetInstance().AddDesc("isRTL:true") : DumpLog::GetInstance().AddDesc("isRTL:false");
    touching_ ? DumpLog::GetInstance().AddDesc("touching:true") : DumpLog::GetInstance().AddDesc("touching:false");
    isMaskAnimationByCreate_ ? DumpLog::GetInstance().AddDesc("isMaskAnimationByCreate:true")
                             : DumpLog::GetInstance().AddDesc("isMaskAnimationByCreate:false");
    animationCurve_ ? DumpLog::GetInstance().AddDesc("animationCurve:" + animationCurve_->ToString())
                    : DumpLog::GetInstance().AddDesc("animationCurve:null");
    animationDuration_.has_value()
        ? DumpLog::GetInstance().AddDesc("animationDuration:" + std::to_string(animationDuration_.value()))
        : DumpLog::GetInstance().AddDesc("animationDuration:null");
    isTouchingSwiper_ ? DumpLog::GetInstance().AddDesc("isTouchingSwiper:true")
                      : DumpLog::GetInstance().AddDesc("isTouchingSwiper:false");
    isAnimating_ ? DumpLog::GetInstance().AddDesc("isAnimating:true")
                 : DumpLog::GetInstance().AddDesc("isAnimating:false");
    changeByClick_ ? DumpLog::GetInstance().AddDesc("changeByClick:true")
                   : DumpLog::GetInstance().AddDesc("changeByClick:false");
    DumpLog::GetInstance().AddDesc("indicator:" + std::to_string(indicator_));
    DumpLog::GetInstance().AddDesc("swiperStartIndex:" + std::to_string(swiperStartIndex_));
    DumpLog::GetInstance().AddDesc("scrollMargin:" + std::to_string(scrollMargin_));
    std::string regionString = std::string("region:");
    for (auto item : gradientRegions_) {
        item ? regionString.append("true ") : regionString.append("false ");
    }
    DumpLog::GetInstance().AddDesc(regionString);
    switch (axis_) {
        case Axis::NONE: {
            DumpLog::GetInstance().AddDesc("Axis:NONE");
            break;
        }
        case Axis::HORIZONTAL: {
            DumpLog::GetInstance().AddDesc("Axis:HORIZONTAL");
            break;
        }
        case Axis::FREE: {
            DumpLog::GetInstance().AddDesc("Axis:FREE");
            break;
        }
        case Axis::VERTICAL: {
            DumpLog::GetInstance().AddDesc("Axis:VERTICAL");
            break;
        }
        default: {
            break;
        }
    }
}

bool TabBarPattern::ContentWillChange(int32_t comingIndex)
{
    auto swiperPattern = GetSwiperPattern();
    CHECK_NULL_RETURN(swiperPattern, true);
    int32_t currentIndex = swiperPattern->GetCurrentIndex();
    return ContentWillChange(currentIndex, comingIndex);
}

bool TabBarPattern::ContentWillChange(int32_t currentIndex, int32_t comingIndex)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, true);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host->GetParent());
    CHECK_NULL_RETURN(tabsNode, true);
    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_RETURN(tabsPattern, true);
    if (tabsPattern->GetInterceptStatus() && currentIndex != comingIndex) {
        auto ret = tabsPattern->OnContentWillChange(currentIndex, comingIndex);
        return ret.has_value() ? ret.value() : true;
    }
    return true;
}

bool TabBarPattern::IsValidIndex(int32_t index)
{
    if (index < 0 || index >= static_cast<int32_t>(tabBarStyles_.size()) ||
        tabBarStyles_[index] != TabBarStyle::SUBTABBATSTYLE || index >= static_cast<int32_t>(selectedModes_.size()) ||
        selectedModes_[index] != SelectedMode::INDICATOR) {
        return false;
    }
    return true;
}

int32_t TabBarPattern::GetLoopIndex(int32_t originalIndex) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, originalIndex);
    auto totalCount = host->TotalChildCount() - MASK_COUNT;
    if (totalCount <= 0) {
        return originalIndex;
    }
    return originalIndex % totalCount;
}

void TabBarPattern::SetRegionInfo(std::unique_ptr<JsonValue>& json)
{
    std::string regionString = "";
    for (auto item : gradientRegions_) {
        item ? regionString.append("true ") : regionString.append("false ");
    }
    json->Put("region", regionString.c_str());
    switch (axis_) {
        case Axis::NONE: {
            json->Put("Axis", "NONE");
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
        case Axis::VERTICAL: {
            json->Put("Axis", "VERTICAL");
            break;
        }
        default: {
            break;
        }
    }
}

void TabBarPattern::SetAnimationCurve(const RefPtr<Curve>& curve)
{
    animationCurve_ = curve;
}

const RefPtr<Curve> TabBarPattern::GetAnimationCurve(const RefPtr<Curve>& defaultCurve) const
{
    return animationCurve_ ? animationCurve_ : defaultCurve;
}

void TabBarPattern::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("isRTL", isRTL_);
    json->Put("touching", touching_);
    json->Put("isMaskAnimationByCreate", isMaskAnimationByCreate_);
    json->Put("animationCurve", animationCurve_ ? animationCurve_->ToString().c_str() : "null");
    json->Put("animationDuration",
        animationDuration_.has_value() ? std::to_string(animationDuration_.value()).c_str() : "null");
    json->Put("isTouchingSwiper", isTouchingSwiper_);
    json->Put("isAnimating", isAnimating_);
    json->Put("changeByClick", changeByClick_);
    json->Put("indicator", indicator_);
    json->Put("swiperStartIndex", swiperStartIndex_);
    json->Put("scrollMargin", scrollMargin_);
    SetRegionInfo(json);
}

void TabBarPattern::AdjustTabBarInfo()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (static_cast<int32_t>(tabBarItemIds_.size()) <= host->TotalChildCount() - MASK_COUNT) {
        return;
    }

    std::set<int32_t> retainedIndex;
    for (auto i = 0; i < static_cast<int32_t>(tabBarItemIds_.size()); i++) {
        auto itemId = tabBarItemIds_[i];
        if (host->GetChildIndexById(itemId) == -1) {
            continue;
        }

        retainedIndex.insert(i);
    }

    UpdateTabBarInfo<int32_t>(tabBarItemIds_, retainedIndex);
    UpdateTabBarInfo<SelectedMode>(selectedModes_, retainedIndex);
    UpdateTabBarInfo<IndicatorStyle>(indicatorStyles_, retainedIndex);
    UpdateTabBarInfo<TabBarStyle>(tabBarStyles_, retainedIndex);
    UpdateTabBarInfo<IconStyle>(iconStyles_, retainedIndex);
    UpdateTabBarInfo<TabBarSymbol>(symbolArray_, retainedIndex);
}

void TabBarPattern::InitFocusEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
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

    auto getNextFocusNodeFunc = [weak = WeakClaim(this)](
                                    FocusReason reason, FocusIntension intension) -> RefPtr<FocusHub> {
        if (reason != FocusReason::FOCUS_TRAVEL) {
            return nullptr;
        }
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, nullptr);
        return pattern->GetCurrentFocusNode();
    };
    focusHub->SetOnGetNextFocusNodeFunc(getNextFocusNodeFunc);
    focusHub->SetAllowedLoop(false);
}

void TabBarPattern::AddIsFocusActiveUpdateEvent()
{
    if (!isFocusActiveUpdateEvent_) {
        isFocusActiveUpdateEvent_ = [weak = WeakClaim(this)](bool isFocusActive) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->UpdateFocusToSelectedNode(isFocusActive);
            pattern->SetTabBarFocusActive(isFocusActive);
            pattern->UpdateFocusTabBarPageState();
        };
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddIsFocusActiveUpdateEvent(GetHost(), isFocusActiveUpdateEvent_);
}

void TabBarPattern::RemoveIsFocusActiveUpdateEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveIsFocusActiveUpdateEvent(GetHost());
}

void TabBarPattern::UpdateFocusToSelectedNode(bool isFocusActive)
{
    if (!isFocusActive) {
        return;
    }
    auto childFocusNode = GetCurrentFocusNode();
    CHECK_NULL_VOID(childFocusNode);
    if (!childFocusNode->IsCurrentFocus()) {
        childFocusNode->RequestFocusImmediately();
    }
    auto layoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto indicator = layoutProperty->GetIndicatorValue(0);
    FocusCurrentOffset(indicator);
}

void TabBarPattern::UpdateFocusTabBarPageState()
{
    if (tabBarStyle_ == TabBarStyle::SUBTABBATSTYLE) {
        UpdateSubTabBoard(indicator_);
        UpdateTextColorAndFontWeight(indicator_);
    }
}

void TabBarPattern::HandleFocusEvent()
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    AddIsFocusActiveUpdateEvent();
    if (context->GetIsFocusActive()) {
        SetTabBarFocusActive(true);
        UpdateFocusTabBarPageState();
        auto layoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto indicator = layoutProperty->GetIndicatorValue(0);
        FocusCurrentOffset(indicator);
    }
}

void TabBarPattern::HandleBlurEvent()
{
    SetTabBarFocusActive(false);
    RemoveIsFocusActiveUpdateEvent();
    UpdateFocusTabBarPageState();
}

void TabBarPattern::UpdateSubTabFocusedTextColor(const RefPtr<TabTheme>& tabTheme, int32_t isFocusedItem,
    RefPtr<TextLayoutProperty> textLayoutProperty, int32_t index, bool isSelected)
{
    auto layoutProperty = GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto axis = layoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
    bool isBoardWithBg = index < static_cast<int32_t>(selectedModes_.size()) &&
                        selectedModes_[index] == SelectedMode::BOARD && isSelected && axis == Axis::HORIZONTAL;
    bool isFocusWithBg = index < static_cast<int32_t>(tabBarStyles_.size()) && isFocusedItem && isTabBarFocusActive_ &&
                        tabBarStyles_[index] == TabBarStyle::SUBTABBATSTYLE;
    bool needUpdateTextColor = isBoardWithBg || isFocusWithBg;
    if (tabTheme->GetIsChangeFocusTextStyle() && needUpdateTextColor) {
        textLayoutProperty->UpdateTextColor(labelStyles_[index].selectedColor.has_value()
                                                ? labelStyles_[index].selectedColor.value()
                                                : tabTheme->GetSubTabTextFocusedColor());
    }
}

void TabBarPattern::InitTabBarProperties(const RefPtr<TabTheme>& tabTheme)
{
    CHECK_NULL_VOID(tabTheme);

    tabBarItemHoverColor_ = tabTheme->GetSubTabBarHoverColor();
    tabBarItemFocusBgColor_ = tabTheme->GetTabBarFocusedColor();
    tabBarItemDefaultBgColor_ = Color::BLACK.BlendOpacity(0.0f);
}

const Color& TabBarPattern::GetSubTabBarHoverColor(int32_t index) const
{
    return (isTabBarFocusActive_ && index == focusIndicator_ && tabBarStyle_ == TabBarStyle::SUBTABBATSTYLE)
               ? tabBarItemFocusBgColor_
               : tabBarItemHoverColor_;
}

void TabBarPattern::UpdateSubTabBarItemStyles(const RefPtr<FrameNode>& columnNode, int32_t focusedColumnId,
    int32_t selectedColumnId, OHOS::Ace::Axis axis, int32_t index)
{
    CHECK_NULL_VOID(columnNode);
    auto renderContext = columnNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto columnNodeId = columnNode->GetId();
    auto isSelected = columnNodeId == selectedColumnId;
    auto isColumnFocused = columnNodeId == focusedColumnId;

    Color itemColor;
    auto isFocusColorSet = tabBarItemFocusBgColor_ != Color::TRANSPARENT;

    if (!isFocusColorSet) {
        if (selectedModes_[index] == SelectedMode::BOARD && isSelected && axis == Axis::HORIZONTAL) {
            itemColor = indicatorStyles_[index].color;
        } else {
            itemColor = tabBarItemDefaultBgColor_;
        }
        renderContext->UpdateBackgroundColor(itemColor);
        return;
    }
    if (isTabBarFocusActive_) {
        itemColor = isColumnFocused ? tabBarItemFocusBgColor_ : tabBarItemDefaultBgColor_;
        renderContext->UpdateBackgroundColor(itemColor);
        return;
    }
    if (selectedModes_[index] == SelectedMode::BOARD && isSelected && axis == Axis::HORIZONTAL) {
        itemColor = tabBarItemFocusBgColor_;
    } else {
        itemColor = tabBarItemDefaultBgColor_;
    }
    renderContext->UpdateBackgroundColor(itemColor);
}

void TabBarPattern::GetColumnId(int32_t& selectedColumnId, int32_t& focusedColumnId, int32_t indicator) const
{
    auto tabBarNode = GetHost();
    CHECK_NULL_VOID(tabBarNode);
    auto columnNode = DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(indicator));
    CHECK_NULL_VOID(columnNode);
    selectedColumnId = columnNode->GetId();
    auto focusedColumnNode = DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(focusIndicator_));
    CHECK_NULL_VOID(focusedColumnNode);
    focusedColumnId = focusedColumnNode->GetId();
}

template<typename T>
void TabBarPattern::UpdateTabBarInfo(std::vector<T>& info, const std::set<int32_t>& retainedIndex)
{
    std::vector<T> newInfo;
    for (auto index : retainedIndex) {
        if (index >= static_cast<int32_t>(info.size())) {
            continue;
        }

        newInfo.emplace_back(info[index]);
    }

    std::swap(newInfo, info);
}

void TabBarPattern::ChangeIndex(int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto totalCount = host->TotalChildCount() - MASK_COUNT;
    if (NonPositive(totalCount)) {
        return;
    }
    if (index < 0 || index >= totalCount) {
        index = 0;
    }
    HandleClick(SourceType::NONE, index);
}

void TabBarPattern::OnColorModeChange(uint32_t colorMode)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    Pattern::OnColorModeChange(colorMode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    jumpIndex_ = layoutProperty->GetIndicatorValue(0);
}
} // namespace OHOS::Ace::NG
