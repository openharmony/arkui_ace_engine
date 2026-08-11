/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/tabs/bridge/tabs_custom_modifier.h"

#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
const char TAB_BAR_ETS_TAG[] = "TabBar";
ArkUINodeHandle CreateTabsFrameNode(ArkUI_Int32 nodeId)
{
    auto frameNode = TabsModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

ArkUINodeHandle CreateTabBarFrameNode(ArkUI_Int32 nodeId)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        TAB_BAR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabBarPattern>(); });
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

ArkUI_Int32 GetTabBarItemTypeCustom(ArkUINodeHandle node, ArkUI_Int32 tabBarItemId)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, static_cast<ArkUI_Int32>(TabBarParamType::NORMAL));
    auto pattern = frameNode->GetPattern<TabBarPattern>();
    CHECK_NULL_RETURN(pattern, static_cast<ArkUI_Int32>(TabBarParamType::NORMAL));
    return static_cast<ArkUI_Int32>(pattern->GetTabBarItemType(tabBarItemId));
}

void SetTabBarItemsChangeEventCustom(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* event = reinterpret_cast<OnTabBarItemsChangeEvent*>(callback);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(event);
    auto pattern = frameNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnTabBarItemsChangeEvent(std::move(*event));
}

void SetShouldPlayMaskAnimationCustom(ArkUINodeHandle node, ArkUI_Bool shouldPlay)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TabBarPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetShouldPlayMaskAnimation(shouldPlay);
}

ArkUI_Int32 GetTabBarItemSizeCustom(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    auto pattern = frameNode->GetPattern<TabBarPattern>();
    CHECK_NULL_RETURN(pattern, 0);
    return static_cast<ArkUI_Int32>(pattern->GetTabBarItemSize());
}

void SetTabsBarBackgroundBlurStyle(ArkUINodeHandle node, void* styleOption)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* blurStyle = reinterpret_cast<BlurStyleOption*>(styleOption);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(blurStyle);
    TabsModelNG::SetBarBackgroundBlurStyle(frameNode, *blurStyle);
}

void SetTabsBarBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetBarBackgroundColor(frameNode, Color(color));
}

void SetTabsBarBackgroundEffect(ArkUINodeHandle node, void* effectOption)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* effect = reinterpret_cast<EffectOption*>(effectOption);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(effect);
    TabsModelNG::SetBarBackgroundEffect(frameNode, *effect);
}

void SetTabsTabBarWidth(ArkUINodeHandle node, void* tabBarWidth)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* width = reinterpret_cast<Dimension*>(tabBarWidth);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(width);
    TabsModelNG::SetTabBarWidth(frameNode, *width);
}

void SetTabsTabBarHeight(ArkUINodeHandle node, void* tabBarHeight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* height = reinterpret_cast<Dimension*>(tabBarHeight);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(height);
    TabsModelNG::SetTabBarHeight(frameNode, *height);
}

void SetTabsDivider(ArkUINodeHandle node, void* divider)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* tabsDivider = reinterpret_cast<TabsItemDivider*>(divider);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(tabsDivider);
    TabsModelNG::SetDivider(frameNode, *tabsDivider);
}

void SetTabsEffectNodeOption(ArkUINodeHandle node, void* option)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* effectNodeOption = reinterpret_cast<TabsEffectNodeOption*>(option);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(effectNodeOption);
    TabsModelNG::SetEffectNodeOption(frameNode, *effectNodeOption);
}

void SetTabsTabBarMode(ArkUINodeHandle node, ArkUI_Int32 tabBarMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabsModelNG::SetTabBarMode(frameNode, static_cast<TabBarMode>(tabBarMode));
}

void SetTabsScrollableBarModeOptions(ArkUINodeHandle node, void* option)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* scrollableOption = reinterpret_cast<ScrollableBarModeOptions*>(option);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(scrollableOption);
    TabsModelNG::SetScrollableBarModeOptions(frameNode, *scrollableOption);
}

void SetTabsOnChangeCustom(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* event = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(event);
    TabsModelNG::SetOnChange(frameNode, std::move(*event));
}

void SetTabsOnTabBarClickCustom(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* event = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(event);
    TabsModelNG::SetOnTabBarClick(frameNode, std::move(*event));
}

void SetTabsOnGestureSwipeCustom(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* event = reinterpret_cast<GestureSwipeEvent*>(callback);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(event);
    TabsModelNG::SetOnGestureSwipe(frameNode, std::move(*event));
}

void SetTabsOnAnimationStartCustom(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* event = reinterpret_cast<AnimationStartEvent*>(callback);
    CHECK_NULL_VOID(event);
    TabsModelNG::SetOnAnimationStart(frameNode, std::move(*event));
}

void HandleBarWidthCustom(ArkUINodeHandle node, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
    TabsModelNG::HandleBarWidth(frameNode, resObj);
}

void HandleBarHeightCustom(ArkUINodeHandle node, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
    TabsModelNG::HandleBarHeight(frameNode, resObj);
}

void HandleDividerStrokeWidthCustom(ArkUINodeHandle node, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
    TabsModelNG::HandleDividerStrokeWidth(frameNode, resObj);
}

void HandleDividerColorCustom(ArkUINodeHandle node, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
    TabsModelNG::HandleDividerColor(frameNode, resObj);
}

void HandleDividerStartMarginCustom(ArkUINodeHandle node, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
    TabsModelNG::HandleDividerStartMargin(frameNode, resObj);
}

void HandleDividerEndMarginCustom(ArkUINodeHandle node, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
    TabsModelNG::HandleDividerEndMargin(frameNode, resObj);
}

void HandleScrollableBarMarginCustom(ArkUINodeHandle node, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
    TabsModelNG::HandleScrollableBarMargin(frameNode, resObj);
}

void HandleBarGridGutterCustom(ArkUINodeHandle node, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
    TabsModelNG::HandleBarGridGutter(frameNode, resObj);
}

void HandleBackgroundBlurStyleInactiveColorCustom(ArkUINodeHandle node, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
    TabsModelNG::HandleBackgroundBlurStyleInactiveColor(frameNode, resObj);
}

void HandleBarBackgroundColorCustom(ArkUINodeHandle node, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
    TabsModelNG::HandleBarBackgroundColor(frameNode, resObj);
}

void HandleBackgroundEffectInactiveColorCustom(ArkUINodeHandle node, void* resObjPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
    TabsModelNG::HandleBackgroundEffectInactiveColor(frameNode, resObj);
}
} // namespace

namespace NodeModifier {
const ArkUITabsCustomModifier* GetTabsCustomModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUITabsCustomModifier modifier = {
        .createFrameNode = CreateTabsFrameNode,
        .createTabBarFrameNode = CreateTabBarFrameNode,
        .getTabBarItemType = GetTabBarItemTypeCustom,
        .setTabBarItemsChangeEvent = SetTabBarItemsChangeEventCustom,
        .setShouldPlayMaskAnimation = SetShouldPlayMaskAnimationCustom,
        .getTabBarItemSize = GetTabBarItemSizeCustom,
        .setBarBackgroundBlurStyle = SetTabsBarBackgroundBlurStyle,
        .setBarBackgroundColor = SetTabsBarBackgroundColor,
        .setBarBackgroundEffect = SetTabsBarBackgroundEffect,
        .setTabBarWidth = SetTabsTabBarWidth,
        .setTabBarHeight = SetTabsTabBarHeight,
        .setDivider = SetTabsDivider,
        .setEffectNodeOption = SetTabsEffectNodeOption,
        .setTabBarMode = SetTabsTabBarMode,
        .setScrollableBarModeOptions = SetTabsScrollableBarModeOptions,
        .setOnChange = SetTabsOnChangeCustom,
        .setOnTabBarClick = SetTabsOnTabBarClickCustom,
        .setOnGestureSwipe = SetTabsOnGestureSwipeCustom,
        .setOnAnimationStart = SetTabsOnAnimationStartCustom,
        .handleBarWidth = HandleBarWidthCustom,
        .handleBarHeight = HandleBarHeightCustom,
        .handleDividerStrokeWidth = HandleDividerStrokeWidthCustom,
        .handleDividerColor = HandleDividerColorCustom,
        .handleDividerStartMargin = HandleDividerStartMarginCustom,
        .handleDividerEndMargin = HandleDividerEndMarginCustom,
        .handleScrollableBarMargin = HandleScrollableBarMarginCustom,
        .handleBarGridGutter = HandleBarGridGutterCustom,
        .handleBackgroundBlurStyleInactiveColor = HandleBackgroundBlurStyleInactiveColorCustom,
        .handleBarBackgroundColor = HandleBarBackgroundColorCustom,
        .handleBackgroundEffectInactiveColor = HandleBackgroundEffectInactiveColorCustom,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
