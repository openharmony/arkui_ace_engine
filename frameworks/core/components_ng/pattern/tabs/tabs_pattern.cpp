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

#include "core/components_ng/pattern/tabs/tabs_pattern.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components/common/layout/constants.h"
#include "core/components/tab_bar/tabs_event.h"
#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/tabs/tab_bar_layout_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_paint_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_node.h"
#include "core/components_ng/pattern/tabs/tabs_layout_property.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t CHILDREN_MIN_SIZE = 2;
constexpr char APP_TABS_NO_ANIMATION_SWITCH[] = "APP_TABS_NO_ANIMATION_SWITCH";
} // namespace

void TabsPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
    // expand to navigation bar by default
    host->GetLayoutProperty()->UpdateSafeAreaExpandOpts(
        { .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_BOTTOM });
}

void TabsPattern::SetOnChangeEvent(std::function<void(const BaseEventInfo*)>&& event)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    ChangeEventWithPreIndex changeEvent([weak = WeakClaim(this), jsEvent = std::move(event)](
                                            int32_t preIndex, int32_t currentIndex) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto tabsNode = AceType::DynamicCast<TabsNode>(pattern->GetHost());
        CHECK_NULL_VOID(tabsNode);
        auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
        CHECK_NULL_VOID(tabBarNode);
        auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
        CHECK_NULL_VOID(tabBarPattern);
        if (tabBarPattern->IsMaskAnimationExecuted()) {
            return;
        }
        auto tabsLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
        CHECK_NULL_VOID(tabsLayoutProperty);
        tabsLayoutProperty->UpdateIndex(currentIndex);
        tabBarPattern->OnTabBarIndexChange(currentIndex);
        pattern->FireTabContentStateCallback(preIndex, currentIndex);

        /* js callback */
        if (jsEvent && tabsNode->IsOnMainTree()) {
            pattern->RecordChangeEvent(currentIndex);
            auto context = tabsNode->GetContext();
            CHECK_NULL_VOID(context);
            TAG_LOGI(
                AceLogTag::ACE_TABS, "onChange preIndex:%{public}d, currentIndex:%{public}d", preIndex, currentIndex);
            context->AddAfterLayoutTask(
                [currentIndex, jsEvent]() {
                    TabContentChangeEvent eventInfo(currentIndex);
                    jsEvent(&eventInfo);
                }, true);
        }
        pattern->ReportComponentChangeEvent(currentIndex);
    });

    if (onChangeEvent_) {
        (*onChangeEvent_).swap(changeEvent);
    } else {
        onChangeEvent_ = std::make_shared<ChangeEventWithPreIndex>(changeEvent);
        auto eventHub = swiperNode->GetOrCreateEventHub<SwiperEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->AddOnChangeEventWithPreIndex(onChangeEvent_);
    }
}

void TabsPattern::FireTabContentStateCallback(int32_t oldIndex, int32_t nextIndex) const
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    std::string id = tabsNode->GetInspectorId().value_or("");
    int32_t uniqueId = tabsNode->GetId();
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    auto oldTabContent = AceType::DynamicCast<TabContentNode>(swiperNode->GetChildByIndex(oldIndex));
    if (oldTabContent) {
        std::string oldTabContentId = oldTabContent->GetInspectorId().value_or("");
        int32_t oldTabContentUniqueId = oldTabContent->GetId();
        TabContentInfo oldTabContentInfo(oldTabContentId, oldTabContentUniqueId, TabContentState::ON_HIDE, oldIndex,
            id, uniqueId);
        UIObserverHandler::GetInstance().NotifyTabContentStateUpdate(oldTabContentInfo);
    }

    auto nextTabContent = AceType::DynamicCast<TabContentNode>(swiperNode->GetChildByIndex(nextIndex));
    if (nextTabContent) {
        std::string nextTabContentId = nextTabContent->GetInspectorId().value_or("");
        int32_t nextTabContentUniqueId = nextTabContent->GetId();
        TabContentInfo nextTabContentInfo(nextTabContentId, nextTabContentUniqueId, TabContentState::ON_SHOW, nextIndex,
            id, uniqueId);
        UIObserverHandler::GetInstance().NotifyTabContentStateUpdate(nextTabContentInfo);
    }
}

void TabsPattern::RecordChangeEvent(int32_t index)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
        auto inspectorId = tabsNode->GetInspectorId().value_or("");
        auto tabBarText = GetTabBarTextByIndex(index);
        Recorder::EventParamsBuilder builder;
        builder.SetId(inspectorId)
            .SetType(tabsNode->GetTag())
            .SetIndex(index)
            .SetText(tabBarText)
            .SetHost(tabsNode)
            .SetDescription(tabsNode->GetAutoEventParamValue(""));
        Recorder::EventRecorder::Get().OnChange(std::move(builder));
        if (!inspectorId.empty()) {
            Recorder::NodeDataCache::Get().PutMultiple(tabsNode, inspectorId, tabBarText, index);
        }
    }
}

std::string TabsPattern::GetTabBarTextByIndex(int32_t index) const
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_RETURN(tabsNode, "");
    auto tabBar = tabsNode->GetTabBar();
    CHECK_NULL_RETURN(tabBar, "");
    auto tabBarItem = tabBar->GetChildAtIndex(index);
    CHECK_NULL_RETURN(tabBarItem, "");
    auto node = AceType::DynamicCast<FrameNode>(tabBarItem);
    CHECK_NULL_RETURN(node, "");
    return node->GetAccessibilityProperty<NG::AccessibilityProperty>()->GetGroupText(true);
}

void TabsPattern::SetOnTabBarClickEvent(std::function<void(const BaseEventInfo*)>&& event)
{
    ChangeEvent tabBarClickEvent([jsEvent = std::move(event)](int32_t index) {
        /* js callback */
        if (jsEvent) {
            TabContentChangeEvent eventInfo(index);
            jsEvent(&eventInfo);
        }
    });

    if (onTabBarClickEvent_) {
        (*onTabBarClickEvent_).swap(tabBarClickEvent);
    } else {
        onTabBarClickEvent_ = std::make_shared<ChangeEvent>(tabBarClickEvent);
    }
}

void TabsPattern::SetAnimationStartEvent(AnimationStartEvent&& event)
{
    if (animationStartEvent_) {
        (*animationStartEvent_).swap(event);
    } else {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto tabsNode = AceType::DynamicCast<TabsNode>(host);
        CHECK_NULL_VOID(tabsNode);
        auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
        CHECK_NULL_VOID(swiperNode);
        auto eventHub = swiperNode->GetOrCreateEventHub<SwiperEventHub>();
        CHECK_NULL_VOID(eventHub);
        animationStartEvent_ = std::make_shared<AnimationStartEvent>(std::move(event));
        eventHub->AddAnimationStartEvent(animationStartEvent_);
    }
}

void TabsPattern::SetAnimationEndEvent(AnimationEndEvent&& event)
{
    if (animationEndEvent_) {
        (*animationEndEvent_).swap(event);
    } else {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto tabsNode = AceType::DynamicCast<TabsNode>(host);
        CHECK_NULL_VOID(tabsNode);
        auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
        CHECK_NULL_VOID(swiperNode);
        auto eventHub = swiperNode->GetOrCreateEventHub<SwiperEventHub>();
        CHECK_NULL_VOID(eventHub);
        animationEndEvent_ = std::make_shared<AnimationEndEvent>(std::move(event));
        eventHub->AddAnimationEndEvent(animationEndEvent_);
    }
}

void TabsPattern::SetOnSelectedEvent(std::function<void(const BaseEventInfo*)>&& event)
{
    ChangeEvent selectedEvent([jsEvent = std::move(event)](int32_t index) {
        /* js callback */
        if (jsEvent) {
            TabContentChangeEvent eventInfo(index);
            jsEvent(&eventInfo);
        }
    });
    if (selectedEvent_) {
        (*selectedEvent_).swap(selectedEvent);
    } else {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto tabsNode = AceType::DynamicCast<TabsNode>(host);
        CHECK_NULL_VOID(tabsNode);
        auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
        CHECK_NULL_VOID(swiperNode);
        auto eventHub = swiperNode->GetOrCreateEventHub<SwiperEventHub>();
        CHECK_NULL_VOID(eventHub);
        selectedEvent_ = std::make_shared<ChangeEvent>(std::move(selectedEvent));
        eventHub->AddOnSlectedEvent(selectedEvent_);
    }
}

void TabsPattern::OnUpdateShowDivider()
{
    auto host = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TabsLayoutProperty>();
    TabsItemDivider defaultDivider;
    auto divider = layoutProperty->GetDivider().value_or(defaultDivider);
    auto children = host->GetChildren();
    if (children.size() < CHILDREN_MIN_SIZE) {
        return;
    }

    auto dividerFrameNode = AceType::DynamicCast<FrameNode>(host->GetDivider());
    CHECK_NULL_VOID(dividerFrameNode);
    auto dividerRenderProperty = dividerFrameNode->GetPaintProperty<DividerRenderProperty>();
    CHECK_NULL_VOID(dividerRenderProperty);
    dividerRenderProperty->UpdateDividerColor(divider.color);

    auto dividerLayoutProperty = dividerFrameNode->GetLayoutProperty<DividerLayoutProperty>();
    CHECK_NULL_VOID(dividerLayoutProperty);
    dividerLayoutProperty->UpdateStrokeWidth(divider.strokeWidth);
    dividerFrameNode->MarkModifyDone();
}

void TabsPattern::UpdateSwiperDisableSwipe(bool disableSwipe)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto props = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(props);
    props->UpdateDisableSwipe(disableSwipe);
    swiperPattern->UpdateSwiperPanEvent(disableSwipe);
    swiperPattern->SetSwiperEventCallback(disableSwipe);
}

void TabsPattern::SetSwiperPaddingAndBorder()
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto layoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    swiperPattern->SetTabsPaddingAndBorder(layoutProperty->CreatePaddingAndBorder());
}

void TabsPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    UpdateSwiperDisableSwipe(isCustomAnimation_ ? true : isDisableSwipe_);
    SetSwiperPaddingAndBorder();
    InitFocusEvent();
    InitAccessibilityZIndex();

    if (onChangeEvent_) {
        return;
    }
    SetOnChangeEvent(nullptr);
    OnUpdateShowDivider();
}

void TabsPattern::OnAfterModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inspectorId = host->GetInspectorId().value_or("");
    if (inspectorId.empty()) {
        return;
    }
    auto property = GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_VOID(property);
    auto index = property->GetIndexValue(0);
    auto tabBarText = GetTabBarTextByIndex(index);
    Recorder::NodeDataCache::Get().PutMultiple(host, inspectorId, tabBarText, index);
}

void TabsPattern::SetOnIndexChangeEvent(std::function<void(const BaseEventInfo*)>&& event)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    ChangeEvent changeEvent([weak = WeakClaim(this), jsEvent = std::move(event)](int32_t index) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto tabsNode = AceType::DynamicCast<TabsNode>(pattern->GetHost());
        CHECK_NULL_VOID(tabsNode);
        auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
        CHECK_NULL_VOID(tabBarNode);
        auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
        CHECK_NULL_VOID(tabBarPattern);
        if (tabBarPattern->IsMaskAnimationExecuted()) {
            return;
        }

        /* js callback */
        if (jsEvent) {
            TabContentChangeEvent eventInfo(index);
            jsEvent(&eventInfo);
        }
    });

    if (onIndexChangeEvent_) {
        (*onIndexChangeEvent_).swap(changeEvent);
    } else {
        onIndexChangeEvent_ = std::make_shared<ChangeEvent>(changeEvent);
        auto eventHub = swiperNode->GetOrCreateEventHub<SwiperEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->AddOnChangeEvent(onIndexChangeEvent_);
    }
}

std::string TabsPattern::ProvideRestoreInfo()
{
    auto jsonObj = JsonUtil::Create(true);
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_RETURN(tabsNode, "");
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_RETURN(tabBarNode, "");
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_RETURN(tabBarPattern, "");
    return tabBarPattern->ProvideRestoreInfo();
}

void TabsPattern::OnRestoreInfo(const std::string& restoreInfo)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    auto info = JsonUtil::ParseJsonString(restoreInfo);
    if (!info->IsValid() || !info->IsObject()) {
        return;
    }
    auto jsonIsOn = info->GetValue("Index");
    swiperLayoutProperty->UpdateIndex(jsonIsOn->GetInt());

    swiperPattern->OnRestoreInfo(restoreInfo);
    tabBarPattern->OnRestoreInfo(restoreInfo);
}

void TabsPattern::AddInnerOnGestureRecognizerJudgeBegin(GestureRecognizerJudgeFunc&& gestureRecognizerJudgeFunc)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto targetComponent = swiperNode->GetTargetComponent().Upgrade();
    CHECK_NULL_VOID(targetComponent);
    targetComponent->SetOnGestureRecognizerJudgeBegin(std::move(gestureRecognizerJudgeFunc));
    targetComponent->SetInnerNodeGestureRecognizerJudge(true);
}

void TabsPattern::RecoverInnerOnGestureRecognizerJudgeBegin()
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto targetComponent = swiperNode->GetTargetComponent().Upgrade();
    CHECK_NULL_VOID(targetComponent);
    targetComponent->SetOnGestureRecognizerJudgeBegin(nullptr);
    targetComponent->SetInnerNodeGestureRecognizerJudge(false);
}

ScopeFocusAlgorithm TabsPattern::GetScopeFocusAlgorithm()
{
    auto property = GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_RETURN(property, {});
    bool isVertical = true;
    if (property->GetAxis().has_value()) {
        isVertical = property->GetAxis().value() == Axis::HORIZONTAL;
    }
    return ScopeFocusAlgorithm(isVertical, true, ScopeType::OTHERS,
        [wp = WeakClaim(this)](
            FocusStep step, const WeakPtr<FocusHub>& currFocusNode, WeakPtr<FocusHub>& nextFocusNode) -> bool {
            auto tabs = wp.Upgrade();
            if (tabs) {
                nextFocusNode = tabs->GetNextFocusNode(step, currFocusNode);
            }
            return nextFocusNode.Upgrade() != currFocusNode.Upgrade();
        });
}

WeakPtr<FocusHub> TabsPattern::GetNextFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode)
{
    auto curFocusNode = currentFocusNode.Upgrade();
    CHECK_NULL_RETURN(curFocusNode, nullptr);

    auto property = GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_RETURN(property, nullptr);
    auto axis = property->GetAxis().value_or(Axis::HORIZONTAL);
    auto tabBarPosition = property->GetTabBarPosition().value_or(BarPosition::START);
    auto isRTL = property->GetNonAutoLayoutDirection() == TextDirection::RTL;

    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_RETURN(tabBarNode, nullptr);
    auto tabBarFocusNode = tabBarNode->GetFocusHub();
    CHECK_NULL_RETURN(tabBarFocusNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_RETURN(swiperNode, nullptr);
    auto swiperFocusNode = swiperNode->GetFocusHub();
    CHECK_NULL_RETURN(swiperFocusNode, nullptr);

    if (curFocusNode->GetFrameName() == V2::TAB_BAR_ETS_TAG) {
        if (tabBarPosition == BarPosition::START) {
            if (step == FocusStep::TAB || (axis == Axis::HORIZONTAL && step == FocusStep::DOWN) ||
                (axis == Axis::VERTICAL && (isRTL ? step == FocusStep::LEFT : step == FocusStep::RIGHT))) {
                return AceType::WeakClaim(AceType::RawPtr(swiperFocusNode));
            }
        } else {
            if (step == FocusStep::SHIFT_TAB || (axis == Axis::HORIZONTAL && step == FocusStep::UP) ||
                (axis == Axis::VERTICAL && (isRTL ? step == FocusStep::RIGHT : step == FocusStep::LEFT))) {
                return AceType::WeakClaim(AceType::RawPtr(swiperFocusNode));
            }
        }
    } else if (curFocusNode->GetFrameName() == V2::SWIPER_ETS_TAG) {
        if (tabBarPosition == BarPosition::START) {
            if (step == FocusStep::SHIFT_TAB || (axis == Axis::HORIZONTAL && step == FocusStep::UP) ||
                (axis == Axis::VERTICAL && (isRTL ? step == FocusStep::RIGHT : step == FocusStep::LEFT))) {
                return AceType::WeakClaim(AceType::RawPtr(tabBarFocusNode));
            }
        } else {
            if (step == FocusStep::TAB || (axis == Axis::HORIZONTAL && step == FocusStep::DOWN) ||
                (axis == Axis::VERTICAL && (isRTL ? step == FocusStep::LEFT : step == FocusStep::RIGHT))) {
                return AceType::WeakClaim(AceType::RawPtr(tabBarFocusNode));
            }
        }
        if (step == FocusStep::LEFT_END || step == FocusStep::RIGHT_END || step == FocusStep::UP_END ||
            step == FocusStep::DOWN_END) {
            return AceType::WeakClaim(AceType::RawPtr(swiperFocusNode));
        }
    }
    return nullptr;
}

void TabsPattern::InitFocusEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);

    auto getNextFocusNodeFunc = [weak = WeakClaim(this)](
                                    FocusReason reason, FocusIntension intension) -> RefPtr<FocusHub> {
        if (reason != FocusReason::FOCUS_TRAVEL) {
            return nullptr;
        }
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, nullptr);
        return pattern->GetCurrentFocusNode(intension);
    };
    focusHub->SetOnGetNextFocusNodeFunc(getNextFocusNodeFunc);
}

RefPtr<FocusHub> TabsPattern::GetCurrentFocusNode(FocusIntension intension)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_RETURN(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_RETURN(tabBarNode, nullptr);
    auto tabBarFocusHub = tabBarNode->GetFocusHub();
    CHECK_NULL_RETURN(tabBarFocusHub, nullptr);
    if (!tabBarFocusHub->GetFocusable()) {
        return nullptr;
    }
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_RETURN(swiperNode, nullptr);
    auto swiperFocusHub = swiperNode->GetFocusHub();
    CHECK_NULL_RETURN(swiperFocusHub, nullptr);

    auto property = GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_RETURN(property, nullptr);
    auto axis = property->GetAxis().value_or(Axis::HORIZONTAL);
    auto barPosition = property->GetTabBarPosition().value_or(BarPosition::START);
    auto isRTL = property->GetNonAutoLayoutDirection() == TextDirection::RTL;

    auto focusFirstNodeIntension = intension == FocusIntension::TAB || intension == FocusIntension::SELECT ||
                                   intension == FocusIntension::HOME;
    auto focusLastNodeIntension = intension == FocusIntension::SHIFT_TAB || intension == FocusIntension::END;
    auto firstFocusHub = barPosition == BarPosition::START ? tabBarFocusHub : swiperFocusHub;
    auto lastFocusHub = barPosition == BarPosition::START ? swiperFocusHub : tabBarFocusHub;
    if (focusFirstNodeIntension) {
        return firstFocusHub;
    } else if (focusLastNodeIntension) {
        return lastFocusHub;
    } else if (axis == Axis::HORIZONTAL) {
        if (intension == FocusIntension::DOWN || intension == FocusIntension::LEFT ||
            intension == FocusIntension::RIGHT) {
            return firstFocusHub;
        } else if (intension == FocusIntension::UP) {
            return lastFocusHub;
        }
    } else {
        if (intension == FocusIntension::DOWN || intension == FocusIntension::UP) {
            return firstFocusHub;
        } else if (intension == FocusIntension::LEFT) {
            return (isRTL ? barPosition == BarPosition::END : barPosition == BarPosition::START) ? swiperFocusHub
                                                                                                 : tabBarFocusHub;
        } else if (intension == FocusIntension::RIGHT) {
            return (isRTL ? barPosition == BarPosition::END : barPosition == BarPosition::START) ? tabBarFocusHub
                                                                                                 : swiperFocusHub;
        }
    }
    return nullptr;
}

void TabsPattern::InitAccessibilityZIndex()
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    auto tabsLayoutProperty = GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_VOID(tabsLayoutProperty);
    BarPosition barPosition = tabsLayoutProperty->GetTabBarPositionValue(BarPosition::START);
    if (barPosition != barPosition_) {
        auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
        CHECK_NULL_VOID(swiperNode);
        auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
        CHECK_NULL_VOID(tabBarNode);
        auto swiperAccessibilityProperty = swiperNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
        CHECK_NULL_VOID(swiperAccessibilityProperty);
        auto tabBarAccessibilityProperty = tabBarNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
        CHECK_NULL_VOID(tabBarAccessibilityProperty);
        if (barPosition == BarPosition::START) {
            swiperAccessibilityProperty->SetAccessibilityZIndex(1);
            tabBarAccessibilityProperty->SetAccessibilityZIndex(0);
        } else {
            swiperAccessibilityProperty->SetAccessibilityZIndex(0);
            tabBarAccessibilityProperty->SetAccessibilityZIndex(1);
        }
        barPosition_ = barPosition;
    }
}

void TabsPattern::BeforeCreateLayoutWrapper()
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto tabsLayoutProperty = GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_VOID(tabsLayoutProperty);
    UpdateIndex(tabsNode, tabBarNode, swiperNode, tabsLayoutProperty);

    if (isInit_) {
        auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
        CHECK_NULL_VOID(swiperPattern);
        swiperPattern->SetOnHiddenChangeForParent();
        auto parent = tabsNode->GetAncestorNodeOfFrame(false);
        CHECK_NULL_VOID(parent);
        while (parent && parent->GetTag() != V2::NAVDESTINATION_VIEW_ETS_TAG) {
            parent = parent->GetAncestorNodeOfFrame(false);
        }
        if (!parent) {
            auto willShowIndex = tabsLayoutProperty->GetIndex().value_or(0);
            swiperPattern->FireSelectedEvent(-1, willShowIndex);
            swiperPattern->FireWillShowEvent(willShowIndex);
        }
        isInit_ = false;
    }

    auto childrenUpdated = swiperNode->GetChildrenUpdated() != -1;
    if (childrenUpdated) {
        HandleChildrenUpdated(swiperNode, tabBarNode);

        auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
        CHECK_NULL_VOID(tabBarPattern);
        auto index = tabsLayoutProperty->GetIndexValue(0);
        auto tabContentNum = swiperNode->TotalChildCount();
        if (index >= tabContentNum) {
            index = 0;
        }
        UpdateSelectedState(swiperNode, tabBarPattern, tabsLayoutProperty, index);
    }
}

void TabsPattern::UpdateIndex(const RefPtr<FrameNode>& tabsNode, const RefPtr<FrameNode>& tabBarNode,
    const RefPtr<FrameNode>& swiperNode, const RefPtr<TabsLayoutProperty>& tabsLayoutProperty)
{
    if (!tabsLayoutProperty->GetIndexSetByUser().has_value()) {
        return;
    }
    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    CHECK_NULL_VOID(tabsPattern);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    auto indexSetByUser = tabsLayoutProperty->GetIndexSetByUser().value();
    auto index = indexSetByUser;
    tabsLayoutProperty->ResetIndexSetByUser();
    auto tabContentNum = swiperNode->TotalChildCount();
    if (index >= tabContentNum) {
        index = 0;
    }
    if (!tabsLayoutProperty->GetIndex().has_value()) {
        UpdateSelectedState(swiperNode, tabBarPattern, tabsLayoutProperty, index);
        tabsLayoutProperty->UpdateIndex(indexSetByUser < 0 ? 0 : indexSetByUser);
    } else {
        auto preIndex = tabsLayoutProperty->GetIndex().value();
        if (preIndex == index || index < 0) {
            return;
        }
        if (tabsPattern->GetInterceptStatus()) {
            auto ret = tabsPattern->OnContentWillChange(preIndex, index);
            if (ret.has_value() && !ret.value()) {
                return;
            }
        }
        AceAsyncTraceBeginCommercial(0, APP_TABS_NO_ANIMATION_SWITCH);
        tabBarPattern->SetMaskAnimationByCreate(true);
        UpdateSelectedState(swiperNode, tabBarPattern, tabsLayoutProperty, index);
    }
}

void TabsPattern::SetAnimateMode(TabAnimateMode mode)
{
    animateMode_ = mode;
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    swiperPattern->SetJumpAnimationMode(mode);
}

/**
 * @brief Handles the update of children in the TabsPattern component.
 *
 * This function is responsible for updating the children of the TabsPattern component,
 * specifically the swiperNode and tabBarNode. It performs the following steps:
 * 1. Creates a map of tabBarItems using the tabBarItemNodes from the tabBarNode.
 * 2. Traverses the tree of UINodes starting from the swiperNode using a stack.
 * 3. For each UINode, if it is an instance of TabContentNode, it retrieves the corresponding
 *    tabBarItem from the tabBarItems map and moves it to position 0.
 * 4. Continues traversing the tree by pushing the children of the current UINode onto the stack.
 *
 * @param swiperNode The FrameNode representing the swiper component.
 * @param tabBarNode The FrameNode representing the tab bar component.
 */
void TabsPattern::HandleChildrenUpdated(const RefPtr<FrameNode>& swiperNode, const RefPtr<FrameNode>& tabBarNode)
{
    std::map<int32_t, RefPtr<FrameNode>> tabBarItems;
    for (const auto& tabBarItemNode : tabBarNode->GetChildren()) {
        CHECK_NULL_VOID(tabBarItemNode);
        auto tabBarItemFrameNode = AceType::DynamicCast<FrameNode>(tabBarItemNode);
        tabBarItems[tabBarItemFrameNode->GetId()] = tabBarItemFrameNode;
    }
    std::stack<RefPtr<UINode>> stack;
    stack.push(swiperNode);
    while (!stack.empty()) {
        auto parent = stack.top();
        stack.pop();
        if (AceType::InstanceOf<TabContentNode>(parent)) {
            auto tabContentNode = AceType::DynamicCast<TabContentNode>(parent);
            auto tabBarItem = tabBarItems[tabContentNode->GetTabBarItemId()];
            CHECK_NULL_VOID(tabBarItem);
            tabBarItem->MovePosition(0);
            continue;
        }
        for (const auto& child : parent->GetChildren()) {
            stack.push(child);
        }
    }

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    tabBarPattern->AdjustTabBarInfo();
}

/**
 * @brief Update selected state.
 *
 * This function is responsible for updating the indicator, text color, font weight, image color,
 * and index of the tab bar and swiper nodes when updating children or creating a tab.
 *
 * @param swiperNode The node representing the swiper.
 * @param tabBarPattern The pattern for the tab bar.
 * @param tabsLayoutProperty The layout property for the tabs.
 * @param index The index of the tab being created.
 */
void TabsPattern::UpdateSelectedState(const RefPtr<FrameNode>& swiperNode, const RefPtr<TabBarPattern>& tabBarPattern,
    const RefPtr<TabsLayoutProperty>& tabsLayoutProperty, int index)
{
    if (index < 0) {
        index = 0;
    }
    tabBarPattern->UpdateIndicator(index);
    tabBarPattern->ResetIndicatorAnimationState();
    tabBarPattern->UpdateSubTabBoard(index);
    tabBarPattern->UpdateTextColorAndFontWeight(index);
    tabBarPattern->AdjustSymbolStats(index);
    tabBarPattern->UpdateImageColor(index);
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    if (!swiperPattern->IsInFastAnimation()) {
        auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
        CHECK_NULL_VOID(swiperLayoutProperty);
        swiperLayoutProperty->UpdateIndex(index);
    }
    tabsLayoutProperty->UpdateIndex(index);
}

void TabsPattern::SetOnUnselectedEvent(std::function<void(const BaseEventInfo*)>&& event)
{
    ChangeEvent unselectedEvent([jsEvent = std::move(event)](int32_t index) {
        /* js callback */
        if (jsEvent) {
            TabContentChangeEvent eventInfo(index);
            jsEvent(&eventInfo);
        }
    });
    if (unselectedEvent_) {
        (*unselectedEvent_).swap(unselectedEvent);
    } else {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto tabsNode = AceType::DynamicCast<TabsNode>(host);
        CHECK_NULL_VOID(tabsNode);
        auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
        CHECK_NULL_VOID(swiperNode);
        auto eventHub = swiperNode->GetOrCreateEventHub<SwiperEventHub>();
        CHECK_NULL_VOID(eventHub);
        unselectedEvent_ = std::make_shared<ChangeEvent>(std::move(unselectedEvent));
        eventHub->AddOnUnselectedEvent(unselectedEvent_);
    }
}

void TabsPattern::ReportComponentChangeEvent(int32_t currentIndex)
{
    if (!UiSessionManager::GetInstance()->IsHasReportObject()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto params = JsonUtil::Create();
    CHECK_NULL_VOID(params);
    params->Put("index", currentIndex);
    auto json = JsonUtil::Create();
    CHECK_NULL_VOID(json);
    json->Put("cmd", "onTabBarClick");
    json->Put("params", params);

    auto result = JsonUtil::Create();
    CHECK_NULL_VOID(result);
    auto nodeId = host->GetId();
    result->Put("nodeId", nodeId);
    result->Put("event", json);
    UiSessionManager::GetInstance()->ReportComponentChangeEvent("result", result->ToString());
}

bool TabsPattern::GetTargetIndex(const std::string& command, int32_t& targetIndex)
{
    auto json = JsonUtil::ParseJsonString(command);
    if (!json || !json->IsValid() || !json->IsObject()) {
        return false;
    }

    if (json->GetString("cmd") != "changeIndex") {
        TAG_LOGW(AceLogTag::ACE_TABS, "Invalid command");
        return false;
    }

    auto paramJson = json->GetValue("params");
    if (!paramJson || !paramJson->IsObject()) {
        return false;
    }

    targetIndex = paramJson->GetInt("index");
    return true;
}

int32_t TabsPattern::OnInjectionEvent(const std::string& command)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, RET_FAILED);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host);
    CHECK_NULL_RETURN(tabsNode, RET_FAILED);
    int32_t targetIndex = 0;
    if (!GetTargetIndex(command, targetIndex)) {
        return RET_FAILED;
    }
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_RETURN(tabBarNode, RET_FAILED);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_RETURN(tabBarPattern, RET_FAILED);
    tabBarPattern->ChangeIndex(targetIndex);
    return RET_SUCCESS;
}

void TabsPattern::OnColorModeChange(uint32_t colorMode)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    Pattern::OnColorModeChange(colorMode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host);
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TabTheme>();
    CHECK_NULL_VOID(theme);
    auto tabsLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_VOID(tabsLayoutProperty);

    if (!tabsLayoutProperty->HasDividerColorSetByUser() ||
        (tabsLayoutProperty->HasDividerColorSetByUser() && !tabsLayoutProperty->GetDividerColorSetByUserValue())) {
        auto currentDivider = tabsLayoutProperty->GetDivider().value_or(TabsItemDivider());
        currentDivider.color = theme->GetDividerColor();
        auto dividerFrameNode = AceType::DynamicCast<FrameNode>(tabsNode->GetDivider());
        CHECK_NULL_VOID(dividerFrameNode);
        auto dividerRenderProperty = dividerFrameNode->GetPaintProperty<DividerRenderProperty>();
        CHECK_NULL_VOID(dividerRenderProperty);
        dividerRenderProperty->UpdateDividerColor(currentDivider.color);
    }
    auto tabBarRenderContext = tabBarNode->GetRenderContext();
    CHECK_NULL_VOID(tabBarRenderContext);
    if (!tabsLayoutProperty->HasBarBackgroundColorSetByUser() ||
        (tabsLayoutProperty->HasBarBackgroundColorSetByUser() &&
            !tabsLayoutProperty->GetBarBackgroundColorSetByUserValue())) {
        Color backgroundColor = Color::BLACK.BlendOpacity(0.0f);
        tabBarRenderContext->UpdateBackgroundColor(backgroundColor);
    }
    tabBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}
} // namespace OHOS::Ace::NG
