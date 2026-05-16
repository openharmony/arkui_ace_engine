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

#include "interfaces/native/ui_input_event.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/log/ace_checker.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components/common/layout/constants.h"
#include "core/components/tab_bar/tabs_event.h"
#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
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
#include "core/components_ng/pattern/stage/stage_manager.h"
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t CHILDREN_MIN_SIZE = 2;
constexpr char APP_TABS_NO_ANIMATION_SWITCH[] = "APP_TABS_NO_ANIMATION_SWITCH";

constexpr int32_t BG_MASK_INDEX = 1;
constexpr uint32_t DEFAULT_GRADIENT_COLOR_NUM = 21;
constexpr double DEFAULT_GRADIENT_COLOR_RATIO[21] = { 1, 0.99764, 0.9901, 0.97627, 0.95574, 0.92808, 0.89108, 0.84375,
    0.78547, 0.71344, 0.63048, 0.53513, 0.4328, 0.33021, 0.23699, 0.15625, 0.09588, 0.05096, 0.02089, 0.00491, 0 };
constexpr double DEFAULT_GRADIENT_COLOR_DIMENSION[21] = { 0, 5.1, 10.0, 15.1, 20.0, 25.1, 30.0, 35.1, 40.0, 45.1, 50.0,
    55.1, 60.0, 65.1, 70.0, 74.9, 80.0, 85.1, 90.0, 95.1, 100.0 };
constexpr uint32_t RGB_MASK = 0x00FFFFFF;
constexpr uint32_t LEFT_SHIFT_24 = 24;

constexpr uint32_t MASK_COLOR_LIGHT = 0xCCF1F3F5;
constexpr uint32_t MASK_COLOR_DARK = 0x99000000;

const RefPtr<Curve> FOLLOW_HAND_ANIMATION_CURVE = AceType::MakeRefPtr<InterpolatingSpring>(0.0, 1.0, 224.0, 25.0);
constexpr int32_t FOLLOW_HAND_ANIMATION_PART2_DELAY = 150;
} // namespace

void TabsPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tabTheme = host->GetTheme<TabTheme>(true);
    CHECK_NULL_VOID(tabTheme);
    host->GetRenderContext()->SetClipToFrame(!tabTheme->GetIsChangeFocusTextStyle());
    // expand to navigation bar by default
    host->GetLayoutProperty()->UpdateSafeAreaExpandOpts(
        { .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_BOTTOM });
}

void TabsPattern::PerformanceCheckTabChange(
    RefPtr<OHOS::Ace::NG::TabsPattern> pattern, RefPtr<OHOS::Ace::NG::TabsNode> tabsNode, bool currentIndex)
{
    if (!AceChecker::IsPerformanceCheckEnabled()) {
        return;
    }
    int64_t startTime = GetSysTimestamp();
    auto pipeline = pattern->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto stageManager_ = pipeline->GetStageManager();
    CHECK_NULL_VOID(stageManager_);
    auto swiperNode_ = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode_);
    pipeline->AddAfterLayoutTask([weakStage = WeakPtr<StageManager>(stageManager_),
                                     weakNode = WeakPtr<FrameNode>(swiperNode_), startTime, currentIndex]() {
        auto stageManager = weakStage.Upgrade();
        CHECK_NULL_VOID(stageManager);
        auto swiperNode = weakNode.Upgrade();
        CHECK_NULL_VOID(swiperNode);
        auto currentTabContentNode = AceType::DynamicCast<TabContentNode>(swiperNode->GetChildByIndex(currentIndex));
        CHECK_NULL_VOID(currentTabContentNode);
        auto current = AceType::DynamicCast<UINode>(currentTabContentNode);
        while (current) {
            if (current->GetTag() == V2::PAGE_ETS_TAG) {
                break;
            }
            current = current->GetParent();
        }
        CHECK_NULL_VOID(current);
        auto routerPage = AceType::DynamicCast<FrameNode>(current);
        CHECK_NULL_VOID(routerPage);
        auto pagePattern = routerPage->GetPattern<NG::PagePattern>();
        CHECK_NULL_VOID(pagePattern);
        auto pageInfo = pagePattern->GetPageInfo();
        CHECK_NULL_VOID(pageInfo);
        auto pagePath = pageInfo->GetFullPath();
        int64_t endTime = GetSysTimestamp();
        stageManager->PerformanceCheck(routerPage, endTime - startTime, pagePath);
    });
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
        /* TabChange callback */
        pattern->FireTabChangeCallback(preIndex, currentIndex);
        /* TabChange performanceCheck */
        pattern->PerformanceCheckTabChange(pattern, tabsNode, currentIndex);

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
    });

    if (onChangeEvent_) {
        (*onChangeEvent_).swap(changeEvent);
    } else {
        onChangeEvent_ = std::make_shared<ChangeEventWithPreIndex>(changeEvent);
        auto eventHub = swiperNode->GetEventHub<SwiperEventHub>();
        CHECK_NULL_VOID(eventHub);
        auto tabsId = tabsNode->GetId();
        eventHub->SetTabsId(tabsId);
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

/**
 * @brief Fire TabChange event callback.
 *
 * This function is responsible for generating TabChange event data and sending it.
 * The first time must be to send the show state event, and the client will receive
 * the show state event. Then each subsequent transmission, the client will first
 * receive a hide state event, followed by a show state event.
 * It performs the following steps:
 * 1. Based on the TabContent information corresponding to pretIndex, create TabChange
 *    event data in hide state, send it out, and keep the sent information.
 * 2. Based on the TabContent information corresponding to nextIndex, create TabChange
 *    event data in show state, send it out, and keep the sent information.
 *
 * @param preIndex The previous index for TabContent. When sending the first TabChange event,
 *                 the parameter must be -1.
 * @param nextIndex The next index for TabContent.
 */
void TabsPattern::FireTabChangeCallback(int32_t preIndex, int32_t nextIndex)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    std::string id = tabsNode->GetInspectorId().value_or("");
    int32_t uniqueId = tabsNode->GetId();
    auto preTabContent = (preIndex < 0) ? nullptr :
        AceType::DynamicCast<TabContentNode>(swiperNode->GetChildByIndex(static_cast<uint32_t>(preIndex)));
    // The first event cannot be hide state.
    if (preTabContent && lastTabChangeInfo_.has_value() && IsValidFireTabChange(lastTabChangeInfo_, preIndex, false)) {
        std::string preTabContentId = preTabContent->GetInspectorId().value_or("");
        int32_t preTabContentUniqueId = preTabContent->GetId();
        TabContentInfo preTabContentInfo(preTabContentId, preTabContentUniqueId, TabContentState::ON_HIDE,
            preIndex, id, uniqueId);
        if (lastTabChangeInfo_->lastFocusIndex.has_value()) {
            preTabContentInfo.lastIndex = lastTabChangeInfo_->lastFocusIndex;
        }
        UIObserverHandler::GetInstance().NotifyTabChange(preTabContentInfo);
        lastTabChangeInfo_->index = preIndex;
        lastTabChangeInfo_->isShow = false;
    }
    auto nextTabContent = (nextIndex < 0) ? nullptr :
        AceType::DynamicCast<TabContentNode>(swiperNode->GetChildByIndex(static_cast<uint32_t>(nextIndex)));
    if (nextTabContent && IsValidFireTabChange(lastTabChangeInfo_, nextIndex, true)) {
        std::string nextTabContentId = nextTabContent->GetInspectorId().value_or("");
        int32_t nextTabContentUniqueId = nextTabContent->GetId();
        TabContentInfo nextTabContentInfo(nextTabContentId, nextTabContentUniqueId, TabContentState::ON_SHOW,
            nextIndex, id, uniqueId);
        // The first callback to observer, lastIndex has no value
        if (lastTabChangeInfo_.has_value() && lastTabChangeInfo_->lastFocusIndex.has_value()) {
            nextTabContentInfo.lastIndex = lastTabChangeInfo_->lastFocusIndex;
        }
        UIObserverHandler::GetInstance().NotifyTabChange(nextTabContentInfo);
        if (!lastTabChangeInfo_.has_value()) {
            lastTabChangeInfo_ = TabChangeInfo();
        }
        lastTabChangeInfo_->index = nextIndex;
        lastTabChangeInfo_->isShow = true;
        lastTabChangeInfo_->lastFocusIndex = nextIndex;
    }
}

bool TabsPattern::IsValidFireTabChange(const std::optional<TabChangeInfo>& lastTabChangeInfo,
    int32_t index, bool isShow)
{
    if (lastTabChangeInfo.has_value() && lastTabChangeInfo->index == index && lastTabChangeInfo->isShow == isShow) {
        // TabChange event will not be sent when this event is the same as the last one.
        return false;
    }
    return true;
}

/**
 * @brief Check the conditions for sending tabchange.
 *
 * This function depend on the logic of the swiper component.
 *
 * @param isInit The state representing whether the tabs component is in an initialized state.
 * @param targetIndex The index representing the desired index to be displayed.
 * @param currentIndex The index representing the currently displayed index of swiper component.
 * @param preIndex The index representing the previous displayed index of swiper component.
 */
bool TabsPattern::IsNeedFireTabChange(bool isInit,
    int32_t targetIndex, int32_t currentIndex, int32_t preIndex)
{
    if (isInit) {
        // TabChange event needs to be fired during initialization state.
        return true;
    }
    if (targetIndex != currentIndex || currentIndex != preIndex) {
        // TabChange event is fired by the swiper When these three variables are not equal.
        return false;
    }
    return true;
}

void TabsPattern::HandleTabChangeWhenChildrenUpdated(
    bool isInit, int32_t tabContentNum, int32_t targetIndex)
{
    if (tabContentNum <= 0) {
        // Reset when there is no TabContent.
        lastTabChangeInfo_.reset();
        return;
    }
    if (lastTabChangeInfo_.has_value()) {
        // TabChange event can not be fired when TabChange event have been fired.
        return;
    }
    // Only called when tabs initialize or children updated.
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    int32_t currentIndex = swiperPattern->GetCurrentIndex();
    int32_t preIndex = swiperPattern->GetPreIndex();
    if (!IsNeedFireTabChange(isInit, targetIndex, currentIndex, preIndex)) {
        return;
    }
    targetIndex = ((targetIndex >= 0) && (targetIndex < tabContentNum)) ? targetIndex : 0;
    FireTabChangeCallback(-1, targetIndex);
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
        auto eventHub = swiperNode->GetEventHub<SwiperEventHub>();
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
        auto eventHub = swiperNode->GetEventHub<SwiperEventHub>();
        CHECK_NULL_VOID(eventHub);
        auto tabsId = host->GetId();
        eventHub->SetTabsId(tabsId);
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
        auto eventHub = swiperNode->GetEventHub<SwiperEventHub>();
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

    InitFloatingBar();
    OnUpdateShowDivider();

    if (onChangeEvent_) {
        return;
    }
    SetOnChangeEvent(nullptr);
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
        auto eventHub = swiperNode->GetEventHub<SwiperEventHub>();
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
    auto info = JsonUtil::ParseJsonString(restoreInfo);
    if (!info->IsValid() || !info->IsObject()) {
        return;
    }
    auto jsonIsOn = info->GetValue("Index");
    auto tabsLayoutProperty = GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_VOID(tabsLayoutProperty);
    CHECK_NULL_VOID(jsonIsOn);
    tabsLayoutProperty->UpdateIndexSetByUser(jsonIsOn->GetInt());
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
            HandleTabChangeWhenChildrenUpdated(true, swiperNode->TotalChildCount(), willShowIndex);
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
        HandleTabChangeWhenChildrenUpdated(false, tabContentNum, index);
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
        auto prevIndex = tabsLayoutProperty->GetIndex().value_or(0);
        if (prevIndex != index && index >= 0) {
            swiperPattern->SetCustomAnimationPrevIndex(prevIndex);
        }
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
        auto eventHub = swiperNode->GetEventHub<SwiperEventHub>();
        CHECK_NULL_VOID(eventHub);
        unselectedEvent_ = std::make_shared<ChangeEvent>(std::move(unselectedEvent));
        eventHub->AddOnUnselectedEvent(unselectedEvent_);
    }
}

void TabsPattern::SetOnContentDidScroll(ContentDidScrollEvent&& onContentDidScroll)
{
    onContentDidScroll_ = std::make_shared<ContentDidScrollEvent>(onContentDidScroll);

    auto toSwiperCallback = [weakThis = WeakPtr<TabsPattern>(AceType::Claim(this))](
                                int32_t selectedIndex, int32_t index, float position, float mainAxisLength) mutable {
        auto tabsPattern = weakThis.Upgrade();
        CHECK_NULL_VOID(tabsPattern);
        auto host = tabsPattern->GetHost();
        CHECK_NULL_VOID(host);
        auto tabsNode = AceType::DynamicCast<TabsNode>(host);
        CHECK_NULL_VOID(tabsNode);
        auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
        CHECK_NULL_VOID(swiperNode);
        auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
        CHECK_NULL_VOID(swiperPattern);
        auto swiperController = swiperPattern->GetSwiperController();
        CHECK_NULL_VOID(swiperController);
        const auto& turnPageRateCallback = swiperController->GetTurnPageRateCallback();
        if (swiperPattern->IsTranslateAnimationRunning() && turnPageRateCallback) {
            auto swipingIndexAndRate = swiperPattern->GetIndicatorProgress();
            if (!NearZero(swipingIndexAndRate.second)) {
                turnPageRateCallback(swipingIndexAndRate.first, swipingIndexAndRate.second);
            }
        }
        auto event = *tabsPattern->onContentDidScroll_;
        if (event) {
            event(selectedIndex, index, position, mainAxisLength);
        }
    };

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host);
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(swiperPattern);
    swiperPattern->SetOnContentDidScroll(std::move(toSwiperCallback));
}

void TabsPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host);
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto theme = host->GetTheme<TabTheme>(true);
    CHECK_NULL_VOID(theme);
    auto tabsLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_VOID(tabsLayoutProperty);
    if (!tabsLayoutProperty->HasDividerColorSetByUser() || !tabsLayoutProperty->GetDividerColorSetByUserValue()) {
        auto currentDivider = tabsLayoutProperty->GetDivider().value_or(TabsItemDivider());
        currentDivider.color = theme->GetDividerColor();
        tabsLayoutProperty->UpdateDivider(currentDivider);
        auto dividerFrameNode = AceType::DynamicCast<FrameNode>(tabsNode->GetDivider());
        CHECK_NULL_VOID(dividerFrameNode);
        auto dividerRenderProperty = dividerFrameNode->GetPaintProperty<DividerRenderProperty>();
        CHECK_NULL_VOID(dividerRenderProperty);
        dividerRenderProperty->UpdateDividerColor(currentDivider.color);
    }
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
    auto theme = host->GetTheme<TabTheme>(true);
    CHECK_NULL_VOID(theme);
    auto tabsLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_VOID(tabsLayoutProperty);

    if (!tabsLayoutProperty->HasDividerColorSetByUser() || !tabsLayoutProperty->GetDividerColorSetByUserValue()) {
        auto currentDivider = tabsLayoutProperty->GetDivider().value_or(TabsItemDivider());
        currentDivider.color = theme->GetDividerColor();
        auto dividerFrameNode = AceType::DynamicCast<FrameNode>(tabsNode->GetDivider());
        CHECK_NULL_VOID(dividerFrameNode);
        auto dividerRenderProperty = dividerFrameNode->GetPaintProperty<DividerRenderProperty>();
        CHECK_NULL_VOID(dividerRenderProperty);
        dividerRenderProperty->UpdateDividerColor(currentDivider.color);
    }
    UpdateTabBarOverlap(tabsLayoutProperty);
    UpdateBgMaskNode();
    tabBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

bool TabsPattern::OnThemeScopeUpdate(int32_t themeScopeId)
{
    auto host = GetHost();
    if (!host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
        return false;
    }

    auto tabsNode = AceType::DynamicCast<TabsNode>(host);
    CHECK_NULL_RETURN(tabsNode, false);
    auto theme = host->GetTheme<TabTheme>(true);
    CHECK_NULL_RETURN(theme, false);
    auto tabsLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_RETURN(tabsLayoutProperty, false);
    if (!tabsLayoutProperty->HasDividerColorSetByUser() || !tabsLayoutProperty->GetDividerColorSetByUserValue()) {
        auto currentDivider = tabsLayoutProperty->GetDivider().value_or(TabsItemDivider());
        currentDivider.color = theme->GetDividerColor();
        auto dividerFrameNode = AceType::DynamicCast<FrameNode>(tabsNode->GetDivider());
        CHECK_NULL_RETURN(dividerFrameNode, false);
        auto dividerRenderProperty = dividerFrameNode->GetPaintProperty<DividerRenderProperty>();
        CHECK_NULL_RETURN(dividerRenderProperty, false);
        dividerRenderProperty->UpdateDividerColor(currentDivider.color);
    }
    UpdateBgMaskNode();
    return false;
}

void TabsPattern::UpdateTabBarOverlap(const RefPtr<TabsLayoutProperty>& tabsLayoutProperty)
{
    CHECK_NULL_VOID(tabsLayoutProperty);
    if (!tabsLayoutProperty->HasBarOverlap()) {
        return;
    }
    bool barOverlap = tabsLayoutProperty->GetBarOverlapValue();
    BlurStyleOption styleOption;
    if (barOverlap) {
        styleOption.blurStyle = BlurStyle::COMPONENT_THICK;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host);
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto target = tabBarNode->GetRenderContext();
    if (target) {
        target->UpdateBackBlurStyle(styleOption);
    }
}

bool TabsPattern::GetTargetIndex(const std::string& command, int32_t& targetIndex)
{
    auto json = JsonUtil::ParseJsonString(command);
    if (!json || !json->IsValid() || !json->IsObject()) {
        return false;
    }
    auto cmdValue = json->GetString("cmd");
    if (cmdValue != "changeIndex") {
        TAG_LOGW(AceLogTag::ACE_TABS, "Invalid command");
        return false;
    }

    auto paramJson = json->GetValue("params");
    if (!paramJson || !paramJson->IsObject()) {
        return false;
    }
    if (!paramJson->Contains("index") || !paramJson->GetValue("index")->IsString()) {
        TAG_LOGE(AceLogTag::ACE_TABS, "Invalid or missing index parameter");
        return false;
    }
    auto originIndex = paramJson->GetString("index");
    targetIndex = StringUtils::StringToInt(originIndex);
    return true;
}

int32_t TabsPattern::OnInjectionEvent(const std::string& command)
{
    int32_t targetIndex = 0;
    if (!GetTargetIndex(command, targetIndex)) {
        return RET_FAILED;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, RET_FAILED);
    auto tabsNode = AceType::DynamicCast<TabsNode>(host);
    CHECK_NULL_RETURN(tabsNode, RET_FAILED);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_RETURN(tabBarNode, RET_FAILED);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_RETURN(tabBarPattern, RET_FAILED);
    tabBarPattern->ChangeIndex(targetIndex);
    return RET_SUCCESS;
}
 	 
void TabsPattern::DumpInfo()
{
    DumpLog::GetInstance().AddDesc(std::string("isBindonContentDidScroll: ")
            .append((onContentDidScroll_ && *onContentDidScroll_) ? "true" : "false"));
}

RefPtr<LayoutAlgorithm> TabsPattern::CreateLayoutAlgorithm()
{
    ACE_UINODE_TRACE(GetHost());
    auto algo = MakeRefPtr<TabsLayoutAlgorithm>();

    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_RETURN(tabsNode, algo);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_RETURN(tabBarNode, algo);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_RETURN(tabBarPattern, algo);

    algo->SetBarItemSize(tabBarPattern->GetChildrenSize());
    algo->SetItemIndex(tabsNode->GetItemIndex());
    algo->SetIsFloatingBar(isFloatingBar_);
    algo->SetLastFloatingBar(lastFloatingBar_);
    return algo;
}

void TabsPattern::InitFloatingBar()
{
    auto property = GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_VOID(property);
    bool isBarOverlap = property->GetBarOverlap().value_or(false);
    bool isHorizontal = property->GetAxis().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL;
    bool isBarPositionEnd = property->GetTabBarPosition().value_or(BarPosition::START) == BarPosition::END;
    bool isFloatingStyle = property->HasBarFloatingStyle();

    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    lastFloatingBar_ = isFloatingBar_;
    if (isBarOverlap && isHorizontal && isBarPositionEnd && isFloatingStyle) {
        isFloatingBar_ = true;
        if (!tabsNode->HasBackgroundMaskNode()) {
            auto backgroundMaskNode = FrameNode::GetOrCreateFrameNode(V2::TABS_BACKGROUND_MASK_ETS_TAG,
                tabsNode->GetBackgroundMaskId(), []() { return AceType::MakeRefPtr<StackPattern>(); });
            backgroundMaskNode->MountToParent(tabsNode, BG_MASK_INDEX);
            backgroundMaskNode->SetHitTestMode(HitTestMode::HTMNONE);
            ItemIndex itemIndex = { 0, 1, 2, 3, 4 };
            tabsNode->SetItemIndex(itemIndex);
        }
        UpdateBgMaskNode();

        InitTouchEvent();
        ApplySystemMaterial();
    } else {
        if (tabsNode->HasBackgroundMaskNode()) {
            auto backgroundMaskNode = AceType::DynamicCast<FrameNode>(tabsNode->GetBackgroundMask());
            CHECK_NULL_VOID(backgroundMaskNode);
            backgroundMaskNode->SetActive(false);
        }
        isFloatingBar_ = false;
        if (floatingBarPosition_ != FloatingBarPosition::CENTER) {
            ResetTabBarFollowHandPosition();
        }
        ResetSystemMaterial();
    }
    if (isFloatingBar_ != lastFloatingBar_) {
        tabsNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void TabsPattern::UpdateBgMaskNode()
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    if (!tabsNode->HasBackgroundMaskNode()) {
        return;
    }
    auto backgroundMaskNode = AceType::DynamicCast<FrameNode>(tabsNode->GetBackgroundMask());
    CHECK_NULL_VOID(backgroundMaskNode);
    auto stackRenderContext = backgroundMaskNode->GetRenderContext();
    CHECK_NULL_VOID(stackRenderContext);
    auto property = GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_VOID(property);
    auto style = property->GetBarFloatingStyle();
    Color baseColor(MASK_COLOR_LIGHT);
    if (style.has_value() && style->maskColor.has_value()) {
        baseColor = style->maskColor.value();
    } else {
        auto context = GetContext();
        if (context && context->GetColorMode() == ColorMode::DARK) {
            baseColor = Color(MASK_COLOR_DARK);
        } else if (tabsNode->GetLocalColorMode() == ColorMode::DARK) {
            baseColor = Color(MASK_COLOR_DARK);
        }
    }

    Gradient gradient;
    gradient.CreateGradientWithType(GradientType::LINEAR);
    gradient.SetDirection(GradientDirection::TOP);

    for (uint32_t index = 0; index < DEFAULT_GRADIENT_COLOR_NUM; ++index) {
        double ratio = DEFAULT_GRADIENT_COLOR_RATIO[index];
        Color stepColor = Color(
            static_cast<uint32_t>(baseColor.GetAlpha() * ratio) << LEFT_SHIFT_24 | (baseColor.GetValue() & RGB_MASK));
        gradient.AddColor(CreatePercentGradientColor(DEFAULT_GRADIENT_COLOR_DIMENSION[index], stepColor));
    }

    stackRenderContext->UpdateLinearGradient(gradient);
}

GradientColor TabsPattern::CreatePercentGradientColor(float percent, Color color)
{
    NG::GradientColor gredient = GradientColor(color);
    gredient.SetDimension(CalcDimension(percent, DimensionUnit::PERCENT));
    return gredient;
}

void TabsPattern::InitTouchEvent()
{
    auto property = GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_VOID(property);
    auto style = property->GetBarFloatingStyle();
    if (!style.has_value() || !style->adaptToHandedness.value_or(false)) {
        if (floatingBarPosition_ != FloatingBarPosition::CENTER) {
            ResetTabBarFollowHandPosition();
        }
        return;
    }
    if (touchListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnTouchEvent(info);
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchListener_);
}

void TabsPattern::OnAttachToMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto id = host->GetId();
    context->AddWindowSizeChangeCallback(id);
}

void TabsPattern::OnDetachFromMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    if (gesture && touchListener_) {
        gesture->RemoveTouchEvent(touchListener_);
    }
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto id = host->GetId();
    context->RemoveWindowSizeChangeCallback(id);
}

void TabsPattern::OnTouchEvent(const TouchEventInfo& info)
{
    auto touchEvent = info.ConvertToTouchEvent();
    if (info.GetTouches().empty()) {
        return;
    }
    auto locationInfo = info.GetTouches().front();
    auto touchType = locationInfo.GetTouchType();
    if (touchType != TouchType::UP) {
        return;
    }
    FloatingBarPosition expectedPosition = FloatingBarPosition::CENTER;
    auto operatingHand = info.GetOperatingHand();
    if (operatingHand == ARKUI_EVENT_HAND_LEFT) {
        expectedPosition = FloatingBarPosition::LEFT;
    } else if (operatingHand == ARKUI_EVENT_HAND_RIGHT) {
        expectedPosition = FloatingBarPosition::RIGHT;
    } else if (operatingHand == ARKUI_EVENT_HAND_NONE) {
        return;
    }
    if (floatingBarPosition_ == expectedPosition) {
        return;
    }
    // Once it switches to the left-hand or right-hand posture, it will not return to the center position.
    if (floatingBarPosition_ != FloatingBarPosition::CENTER && expectedPosition == FloatingBarPosition::CENTER) {
        return;
    }
    floatingBarPosition_ = expectedPosition;
    FollowHandAnimation();
}

void TabsPattern::ResetTabBarFollowHandPosition()
{
    if (!isFloatingBar_ && !lastFloatingBar_) {
        return;
    }
    auto animations = std::move(floatTabBarFollowHandAnimations_);
    for (auto& animation : animations) {
        if (animation) {
            AnimationUtils::StopAnimation(animation);
        }
    }
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    auto tabBar = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBar);
    auto renderContext = tabBar->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    floatingBarPosition_ = FloatingBarPosition::CENTER;
    renderContext->UpdateTransformScale({ 1.0f, 1.0f });
    renderContext->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
}

void TabsPattern::OnWindowSizeChanged(int32_t /*width*/, int32_t /*height*/, WindowSizeChangeReason type)
{
    if (WindowSizeChangeReason::ROTATION != type) {
        return;
    }
    ResetTabBarFollowHandPosition();
}

void TabsPattern::HandleOnTouchScaleAnimation()
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    auto tabsGeometry = tabsNode->GetGeometryNode();
    CHECK_NULL_VOID(tabsGeometry);
    auto tabsWidth = tabsGeometry->GetFrameSize().Width();
    auto tabBar = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBar);
    auto tabBarGeometry = tabBar->GetGeometryNode();
    CHECK_NULL_VOID(tabBarGeometry);
    auto tabBarWidth = tabBarGeometry->GetFrameSize().Width();
    auto oriTranslateX =
        std::max(0.0f, ((tabsWidth / 2.0f) - (tabBarWidth / 2.0f) - floatingBarMargin_.value_or(0.0f)));
    auto GetTranslateX = [this, oriTranslateX]() {
        switch (floatingBarPosition_) {
            case FloatingBarPosition::CENTER:
                return 0.0f;
            case FloatingBarPosition::LEFT:
                return -oriTranslateX;
            case FloatingBarPosition::RIGHT:
                return oriTranslateX;
            default:
                return 0.0f;
        }
    };
    auto translateX = GetTranslateX();
    auto tabBarRenderContext = tabBar->GetRenderContext();
    CHECK_NULL_VOID(tabBarRenderContext);
    tabBarRenderContext->UpdateTransformScale({ 1.15f, 0.85f });
    tabBarRenderContext->UpdateTransformTranslate({ translateX, 0.0f, 0.0f });
}

void TabsPattern::HandleOnTouchDelayScaleAnimation()
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    auto tabBar = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBar);
    auto tabBarRenderContext = tabBar->GetRenderContext();
    CHECK_NULL_VOID(tabBarRenderContext);
    tabBarRenderContext->UpdateTransformScale({ 1.0f, 1.0f });
}

void TabsPattern::OnFollowHandAnimationFinish()
{
    floatTabBarFollowHandAnimationCount_--;
    if (floatTabBarFollowHandAnimationCount_ > 0) {
        return;
    }
    floatTabBarFollowHandAnimationCount_ = 0;
    floatTabBarFollowHandAnimations_.clear();
}

void TabsPattern::InitTabBarTransformAttributeIfNeeded()
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    auto tabBar = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBar);
    auto renderContext = tabBar->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (!renderContext->HasTransformScale()) {
        renderContext->UpdateTransformScale({ 1.0f, 1.0f });
    }
    if (!renderContext->HasTransformTranslate()) {
        renderContext->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
    }
}

void TabsPattern::FollowHandAnimation()
{
    auto property = GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_VOID(property);
    auto style = property->GetBarFloatingStyle();
    if (!style.has_value() || !style->adaptToHandedness.value_or(false)) {
        return;
    }
    // Tab width greater than 600vp is required to fllow hand.
    if (!floatingBarMargin_.has_value()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto CreateTouchAnimation = [weak = AceType::WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleOnTouchScaleAnimation();
    };
    auto CreateTouchAnimationNext = [weak = AceType::WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleOnTouchDelayScaleAnimation();
    };
    auto finishCallback = [weak = AceType::WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnFollowHandAnimationFinish();
    };
    AnimationOption options;
    options.SetCurve(FOLLOW_HAND_ANIMATION_CURVE);
    options.SetOnFinishEvent(finishCallback);
    AnimationOption optionsNext = options;
    optionsNext.SetDelay(FOLLOW_HAND_ANIMATION_PART2_DELAY);
    floatTabBarFollowHandAnimationCount_++;
    floatTabBarFollowHandAnimations_.clear();
    InitTabBarTransformAttributeIfNeeded();
    auto step1Animation =
        AnimationUtils::StartAnimation(options, CreateTouchAnimation, options.GetOnFinishEvent(), nullptr, context);
    floatTabBarFollowHandAnimations_.push_back(step1Animation);
    floatTabBarFollowHandAnimationCount_++;
    auto step2Animation = AnimationUtils::StartAnimation(
        optionsNext, CreateTouchAnimationNext, optionsNext.GetOnFinishEvent(), nullptr, context);
    floatTabBarFollowHandAnimations_.push_back(step2Animation);
}

void TabsPattern::ApplySystemMaterial()
{
    auto property = GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_VOID(property);
    auto style = property->GetBarFloatingStyle();
    if (!style.has_value()) {
        return;
    }
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    auto tabBar = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBar);
    auto renderContext = tabBar->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto tabBarPattern = tabBar->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    auto uiMaterial = style->systemMaterial;
    if (uiMaterial) {
        tabBarPattern->SetUseNewMaterial(true);
        renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
        ViewAbstract::SetSystemMaterial(AceType::RawPtr(tabBar), uiMaterial.GetRawPtr());
    } else {
        tabBarPattern->SetUseNewMaterial(false);
        ViewAbstract::SetSystemMaterial(AceType::RawPtr(tabBar), nullptr);
    }
}

void TabsPattern::ResetSystemMaterial()
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    auto tabBar = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBar);
    auto tabBarPattern = tabBar->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    tabBarPattern->SetUseNewMaterial(false);
    ViewAbstract::SetSystemMaterial(AceType::RawPtr(tabBar), nullptr);
}
} // namespace OHOS::Ace::NG
