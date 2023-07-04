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
#include "core/components_ng/pattern/swiper/swiper_pattern.h"

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/tab_bar/tabs_event.h"
#include "core/components_ng/pattern/swiper/swiper_event_hub.h"
#include "core/components_ng/pattern/tabs/tab_bar_layout_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_paint_property.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
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

    ChangeEvent changeEvent([tabBarNode, tabBarPattern, jsEvent = std::move(event)](int32_t index) {
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
        if (tabBarLayoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED) == TabBarMode::FIXED) {
            tabBarPattern->SetIndicator(index);
        }
        tabBarPattern->UpdateIndicator(index);
        tabBarPattern->UpdateTextColor(index);
        if (tabBarLayoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED) == TabBarMode::SCROLLABLE) {
            if (tabBarPattern->GetTabBarStyle() == TabBarStyle::SUBTABBATSTYLE) {
                if (!tabBarPattern->GetChangeByClick()) {
                    tabBarPattern->PlayTabBarTranslateAnimation(index);
                } else {
                    tabBarPattern->SetChangeByClick(false);
                }
            } else {
                tabBarNode->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
            }
        }
        /* js callback */
        if (jsEvent) {
            TabContentChangeEvent eventInfo(index);
            jsEvent(&eventInfo);
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

void TabsPattern::OnUpdateShowDivider()
{
    auto host = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TabsLayoutProperty>();
    TabsItemDivider defaultDivider;
    auto divider = layoutProperty->GetDivider().value_or(defaultDivider);
    auto children = host->GetChildren();
    if (children.size() < CHILDREN_MIN_SIZE) {
        LOGE("OnUpdateShowDivider: children is empty or children's size is less than 2.");
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

void TabsPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    if (onChangeEvent_) {
        return;
    }
    SetOnChangeEvent(nullptr);
    OnUpdateShowDivider();
}

void TabsPattern::SetOnIndexChangeEvent(std::function<void(const BaseEventInfo*)>&& event)
{
    auto tabsNode = AceType::DynamicCast<TabsNode>(GetHost());
    CHECK_NULL_VOID(tabsNode);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    CHECK_NULL_VOID(swiperNode);

    ChangeEvent changeEvent([jsEvent = std::move(event)](int32_t index) {
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
        LOGW("TabsPattern:: restore info is invalid");
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
} // namespace OHOS::Ace::NG
