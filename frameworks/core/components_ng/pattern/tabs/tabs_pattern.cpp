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

#include "core/components_ng/pattern/tabs/tabs_pattern.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components/common/layout/constants.h"
#include "core/components/tab_bar/tabs_event.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/swiper/swiper_event_hub.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/tabs/tab_bar_layout_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_paint_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t CHILDREN_MIN_SIZE = 2;
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
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    ChangeEvent changeEvent([weak = WeakClaim(this), tabBarNode, tabBarPattern, jsEvent = std::move(event)](
                                int32_t index) {
        if (tabBarPattern->IsMaskAnimationExecuted()) {
            return;
        }
        auto tabsNode = AceType::DynamicCast<TabsNode>(tabBarNode->GetParent());
        CHECK_NULL_VOID(tabsNode);
        auto tabsLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
        CHECK_NULL_VOID(tabsLayoutProperty);
        tabsLayoutProperty->UpdateIndex(index);
        tabBarPattern->SetIsAnimating(false);
        auto tabBarLayoutProperty = tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>();
        CHECK_NULL_VOID(tabBarLayoutProperty);
        if (!tabBarPattern->IsMaskAnimationByCreate()) {
            tabBarPattern->HandleBottomTabBarChange(index);
        }
        tabBarPattern->SetMaskAnimationByCreate(false);
        tabBarPattern->SetIndicator(index);
        tabBarPattern->UpdateIndicator(index);
        tabBarPattern->UpdateTextColor(index);
        if (tabBarLayoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED) == TabBarMode::SCROLLABLE) {
            if (tabBarPattern->GetTabBarStyle() == TabBarStyle::SUBTABBATSTYLE &&
                tabBarLayoutProperty->GetAxisValue(Axis::HORIZONTAL) == Axis::HORIZONTAL) {
                if (!tabBarPattern->GetChangeByClick()) {
                    tabBarPattern->PlayTabBarTranslateAnimation(index);
                    tabBarNode->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
                } else {
                    tabBarPattern->SetChangeByClick(false);
                }
            } else {
                tabBarNode->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
            }
        }
        /* js callback */
        if (jsEvent && tabsNode->IsOnMainTree()) {
            TabContentChangeEvent eventInfo(index);
            jsEvent(&eventInfo);

            if (!Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
                return;
            }
            auto inspectorId = tabsNode->GetInspectorId().value_or("");
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto tabBarText = pattern->GetTabBarTextByIndex(index);
            Recorder::EventParamsBuilder builder;
            builder.SetId(inspectorId).SetType(tabsNode->GetTag()).SetIndex(index).SetText(tabBarText);
            Recorder::EventRecorder::Get().OnChange(std::move(builder));
            if (!inspectorId.empty()) {
                Recorder::NodeDataCache::Get().PutMultiple(inspectorId, tabBarText, index);
            }
        }
    });

    if (onChangeEvent_) {
        (*onChangeEvent_).swap(changeEvent);
    } else {
        onChangeEvent_ = std::make_shared<ChangeEvent>(changeEvent);
        auto eventHub = swiperNode->GetEventHub<SwiperEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->AddOnChangeEvent(onChangeEvent_);
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
    return node->GetAccessibilityProperty<NG::AccessibilityProperty>()->GetAccessibilityText(true);
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
        animationEndEvent_ = std::make_shared<AnimationEndEvent>(std::move(event));
        eventHub->AddAnimationEndEvent(animationEndEvent_);
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
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(swiperPaintProperty);
    swiperPaintProperty->UpdateDisableSwipe(disableSwipe);
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
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
        CHECK_NULL_VOID(tabsNode);
        auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
        CHECK_NULL_VOID(tabBarNode);
        auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
        CHECK_NULL_VOID(tabBarPattern);
        auto tabBarRenderContext = tabBarNode->GetRenderContext();
        CHECK_NULL_VOID(tabBarRenderContext);
        auto tabBarPaintProperty = tabBarPattern->GetPaintProperty<TabBarPaintProperty>();
        CHECK_NULL_VOID(tabBarPaintProperty);
        BlurStyleOption styleOption;
        styleOption.blurStyle = BlurStyle::NO_MATERIAL;
        if (!tabBarPaintProperty->GetBarBackgroundColor().has_value() ||
            tabBarPaintProperty->GetBarBackgroundColor().value() == Color::TRANSPARENT) {
            styleOption.blurStyle = BlurStyle::COMPONENT_THICK;
        }
        tabBarRenderContext->UpdateBackBlurStyle(styleOption);
    }

    UpdateSwiperDisableSwipe(isCustomAnimation_ ? true : isDisableSwipe_);
    SetSwiperPaddingAndBorder();

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
    Recorder::NodeDataCache::Get().PutMultiple(inspectorId, tabBarText, index);
}

void TabsPattern::SetOnIndexChangeEvent(std::function<void(const BaseEventInfo*)>&& event)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    ChangeEvent changeEvent([tabBarPattern, jsEvent = std::move(event)](int32_t index) {
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
            FocusStep step, const WeakPtr<FocusHub>& currFocusNode, WeakPtr<FocusHub>& nextFocusNode) {
            auto tabs = wp.Upgrade();
            if (tabs) {
                nextFocusNode = tabs->GetNextFocusNode(step, currFocusNode);
            }
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

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_RETURN(tabBarPattern, nullptr);
    tabBarPattern->SetFirstFocus(true);

    if (curFocusNode->GetFrameName() == V2::TAB_BAR_ETS_TAG &&
        ((tabBarPosition == BarPosition::START && axis == Axis::HORIZONTAL && step == FocusStep::DOWN) ||
        (tabBarPosition == BarPosition::START && axis == Axis::VERTICAL && step == FocusStep::RIGHT) ||
        (tabBarPosition == BarPosition::END && axis == Axis::HORIZONTAL && step == FocusStep::UP) ||
        (tabBarPosition == BarPosition::END && axis == Axis::VERTICAL && step == FocusStep::LEFT))) {
        return AceType::WeakClaim(AceType::RawPtr(swiperFocusNode));
    }
    if (curFocusNode->GetFrameName() == V2::SWIPER_ETS_TAG) {
        if ((tabBarPosition == BarPosition::START && axis == Axis::HORIZONTAL && step == FocusStep::UP) ||
            (tabBarPosition == BarPosition::START && axis == Axis::VERTICAL && step == FocusStep::LEFT) ||
            (tabBarPosition == BarPosition::END && axis == Axis::HORIZONTAL && step == FocusStep::DOWN) ||
            (tabBarPosition == BarPosition::END && axis == Axis::VERTICAL && step == FocusStep::RIGHT)) {
            return AceType::WeakClaim(AceType::RawPtr(tabBarFocusNode));
        }
        if (step == FocusStep::LEFT_END || step == FocusStep::RIGHT_END || step == FocusStep::UP_END ||
            step == FocusStep::DOWN_END) {
            return AceType::WeakClaim(AceType::RawPtr(swiperFocusNode));
        }
    }
    return nullptr;
}

void TabsPattern::BeforeCreateLayoutWrapper()
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);
    auto tabContentNum = swiperNode->TotalChildCount();
    auto tabsLayoutProperty = GetLayoutProperty<TabsLayoutProperty>();
    CHECK_NULL_VOID(tabsLayoutProperty);
    auto index = tabsLayoutProperty->GetIndex().value_or(0);
    if (index > tabContentNum - 1) {
        index = 0;
    }

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    CHECK_NULL_VOID(tabBarNode);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(tabBarPattern);
    if (!tabBarPattern->IsMaskAnimationByCreate()) {
        return;
    }
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    CHECK_NULL_VOID(tabBarLayoutProperty);
    tabBarLayoutProperty->UpdateIndicator(index);
    tabBarPattern->UpdateTextColor(index);
    tabBarPattern->UpdateImageColor(index);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    swiperLayoutProperty->UpdateIndex(index);
    tabsLayoutProperty->UpdateIndex(index);
}
} // namespace OHOS::Ace::NG
