/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/navrouter/navdestination_model_static.h"

#include "base/i18n/localization.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/pattern/navigation/navdestination_content_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navigation/navigation_toolbar_util.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "frameworks/base/system_bar/system_bar_style.h"

namespace OHOS::Ace::NG {
namespace {
void CreateToolBarNode(const RefPtr<NavDestinationGroupNode>& navDestinationNode)
{
    if (navDestinationNode->GetToolBarNode()) {
        return;
    }
    int32_t toolBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::TOOL_BAR_ETS_TAG, toolBarNodeId);
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(
        V2::TOOL_BAR_ETS_TAG, toolBarNodeId, []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    toolBarNode->MarkModifyDone();
    auto property = toolBarNode->GetLayoutProperty();
    CHECK_NULL_VOID(property);
    property->UpdateVisibility(VisibleType::GONE);
    navDestinationNode->AddChild(toolBarNode);
    navDestinationNode->SetToolBarNode(toolBarNode);
    navDestinationNode->SetPreToolBarNode(toolBarNode);
    navDestinationNode->UpdatePrevToolBarIsCustom(false);
}

void CreateSymbolBackButton(RefPtr<FrameNode>& backButtonNode, RefPtr<TitleBarNode>& titleBarNode)
{
    auto symbolNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_VOID(symbolNode);
    auto symbolProperty = symbolNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(symbolProperty);
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    symbolProperty->UpdateSymbolSourceInfo(SymbolSourceInfo(theme->GetBackSymbolId()));
    symbolNode->MountToParent(backButtonNode);
    auto iconColor = theme->GetIconColor();
    symbolProperty->UpdateSymbolColorList({ iconColor });
    symbolNode->MarkDirtyNode();
    backButtonNode->MarkModifyDone();
}

void CreateImageBackButton(RefPtr<FrameNode>& backButtonNode, RefPtr<TitleBarNode>& titleBarNode)
{
    auto backButtonImageNode = FrameNode::CreateFrameNode(V2::BACK_BUTTON_IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_VOID(backButtonImageNode);

    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetResourceId(theme->GetBackResourceId());
    auto backButtonImageLayoutProperty = backButtonImageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(backButtonImageLayoutProperty);
    backButtonImageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    backButtonImageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    auto imageRenderProperty = backButtonImageNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(imageRenderProperty);
    imageRenderProperty->UpdateMatchTextDirection(true);
    backButtonNode->AddChild(backButtonImageNode);
    backButtonImageNode->MarkModifyDone();
    backButtonNode->MarkModifyDone();
}
} // namespace

void NavDestinationModelStatic::SetBackButtonIcon(FrameNode* frameNode,
    const std::function<void(WeakPtr<NG::FrameNode>)>& iconSymbol, const std::string& src,
    const ImageOption& imageOption, RefPtr<PixelMap>& pixMap, const std::vector<std::string>& nameList,
    bool userDefinedAccessibilityText, const std::string& backButtonAccessibilityText)
{
    CHECK_NULL_VOID(frameNode);
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    CHECK_NULL_VOID(navDestinationNode);

    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    ImageSourceInfo imageSourceInfo(src, nameList[0], nameList[1]);
    titleBarLayoutProperty->UpdateImageSource(imageSourceInfo);
    titleBarLayoutProperty->UpdateNoPixMap(imageOption.noPixMap);
    titleBarLayoutProperty->UpdatePixelMap(pixMap);
    titleBarLayoutProperty->SetBackIconSymbol(iconSymbol);
    titleBarLayoutProperty->UpdateIsValidImage(imageOption.isValidImage);
    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    CHECK_NULL_VOID(backButtonNode);
    if (userDefinedAccessibilityText) {
        NavigationTitleUtil::SetAccessibility(backButtonNode, backButtonAccessibilityText);
    } else {
        std::string message = Localization::GetInstance()->GetEntryLetters("navigation.back");
        NavigationTitleUtil::SetAccessibility(backButtonNode, message);
    }
}

void NavDestinationModelStatic::SetMenuItems(FrameNode* frameNode, std::vector<NG::BarItem>&& menuItems)
{
    auto navDestinationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    CHECK_NULL_VOID(navDestinationGroupNode);
    // if previous menu is custom, just remove it and create new menu, otherwise update old menu
    if (navDestinationGroupNode->GetPrevMenuIsCustom().value_or(false)) {
        navDestinationGroupNode->UpdateMenuNodeOperation(ChildNodeOperation::REPLACE);
    } else {
        if (navDestinationGroupNode->GetMenu()) {
            navDestinationGroupNode->UpdateMenuNodeOperation(ChildNodeOperation::REPLACE);
        } else {
            navDestinationGroupNode->UpdateMenuNodeOperation(ChildNodeOperation::ADD);
        }
    }
    auto navDestinationPattern = navDestinationGroupNode->GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(navDestinationPattern);
    navDestinationPattern->SetTitleBarMenuItems(menuItems);
    navDestinationPattern->SetMenuNodeId(ElementRegister::GetInstance()->MakeUniqueId());
    navDestinationPattern->SetLandscapeMenuNodeId(ElementRegister::GetInstance()->MakeUniqueId());
    navDestinationGroupNode->UpdatePrevMenuIsCustom(false);
}

void NavDestinationModelStatic::SetSystemTransitionType(FrameNode* frameNode, NG::NavigationSystemTransitionType type)
{
    auto navDestinationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    CHECK_NULL_VOID(navDestinationGroupNode);
    navDestinationGroupNode->SetSystemTransitionType(type);
}

void NavDestinationModelStatic::SetOnActive(FrameNode* frameNode, std::function<void(int32_t)>&& onActive)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<NavDestinationEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnActive(onActive);
}

void NavDestinationModelStatic::SetOnInactive(FrameNode* frameNode, std::function<void(int32_t)>&& onInactive)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<NavDestinationEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnInactive(onInactive);
}

void NavDestinationModelStatic::SetMenuOptions(FrameNode* frameNode, NavigationMenuOptions&& opt)
{
    CHECK_NULL_VOID(frameNode);
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    CHECK_NULL_VOID(navDestinationNode);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(navDestinationPattern);
    navDestinationPattern->SetMenuOptions(opt);
}

void NavDestinationModelStatic::CreateBackButton(const RefPtr<NavDestinationGroupNode>& navDestinationNode)
{
    int32_t titleBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::TITLE_BAR_ETS_TAG, titleBarNodeId);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        V2::TITLE_BAR_ETS_TAG, titleBarNodeId, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->AddChild(titleBarNode);
    navDestinationNode->SetTitleBarNode(titleBarNode);

    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    int32_t backButtonNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto backButtonNode =
        FrameNode::CreateFrameNode(V2::BACK_BUTTON_ETS_TAG, backButtonNodeId, AceType::MakeRefPtr<ButtonPattern>());
    auto focusHub = backButtonNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetFocusDependence(FocusDependence::SELF);
    auto buttonPattern = backButtonNode->GetPattern<ButtonPattern>();
    CHECK_NULL_VOID(buttonPattern);
    buttonPattern->SetSkipColorConfigurationUpdate();
    buttonPattern->setComponentButtonType(ComponentButtonType::NAVIGATION);
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        buttonPattern->SetBlendColor(theme->GetBackgroundPressedColor(), theme->GetBackgroundHoverColor());
        buttonPattern->SetFocusBorderColor(theme->GetBackgroundFocusOutlineColor());
        buttonPattern->SetFocusBorderWidth(theme->GetBackgroundFocusOutlineWeight());
    }

    // read navdestination back button
    std::string message = Localization::GetInstance()->GetEntryLetters("navigation.back");
    NavigationTitleUtil::SetAccessibility(backButtonNode, message);

    titleBarNode->AddChild(backButtonNode);
    titleBarNode->SetBackButton(backButtonNode);
    auto backButtonLayoutProperty = backButtonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(backButtonLayoutProperty);
    auto renderContext = backButtonNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    backButtonLayoutProperty->UpdateType(ButtonType::NORMAL);
    backButtonLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);

    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        backButtonLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(theme->GetIconBackgroundWidth()), CalcLength(theme->GetIconBackgroundHeight())));
        backButtonLayoutProperty->UpdateBorderRadius(BorderRadiusProperty(theme->GetCornerRadius()));
        renderContext->UpdateBackgroundColor(theme->GetCompBackgroundColor());
        PaddingProperty padding;
        padding.SetEdges(CalcLength(MENU_BUTTON_PADDING));
        backButtonLayoutProperty->UpdatePadding(padding);
    } else {
        backButtonLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(BACK_BUTTON_SIZE), CalcLength(BACK_BUTTON_SIZE)));
        backButtonLayoutProperty->UpdateBorderRadius(BorderRadiusProperty(BUTTON_RADIUS_SIZE));
        renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
        PaddingProperty padding;
        padding.SetEdges(CalcLength(BUTTON_PADDING));
        backButtonLayoutProperty->UpdatePadding(padding);
    }

    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE) &&
        SystemProperties::IsNeedSymbol()) {
        CreateSymbolBackButton(backButtonNode, titleBarNode);
    } else {
        CreateImageBackButton(backButtonNode, titleBarNode);
    }
}

void NavDestinationModelStatic::CreateImageButton(const RefPtr<NavDestinationGroupNode>& navDestinationNode)
{
    int32_t titleBarNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::TITLE_BAR_ETS_TAG, titleBarNodeId);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        V2::TITLE_BAR_ETS_TAG, titleBarNodeId, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->AddChild(titleBarNode);
    navDestinationNode->SetTitleBarNode(titleBarNode);

    int32_t backButtonNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto backButtonNode =
        FrameNode::CreateFrameNode(V2::BACK_BUTTON_ETS_TAG, backButtonNodeId, AceType::MakeRefPtr<ImagePattern>());
    auto focusHub = backButtonNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetFocusDependence(FocusDependence::SELF);
    titleBarNode->AddChild(backButtonNode);
    titleBarNode->SetBackButton(backButtonNode);

    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetResourceId(theme->GetBackResourceId());
    auto backButtonLayoutProperty = backButtonNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(backButtonLayoutProperty);
    backButtonLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    auto imageRenderProperty = backButtonNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(imageRenderProperty);
    imageRenderProperty->UpdateMatchTextDirection(true);
    backButtonNode->MarkModifyDone();
}

RefPtr<FrameNode> NavDestinationModelStatic::CreateFrameNode(int32_t nodeId, std::function<void()>&& deepRenderFunc)
{
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId);
    auto deepRender = [nodeId, deepRenderFunc = std::move(deepRenderFunc)]() -> RefPtr<UINode> {
        CHECK_NULL_RETURN(deepRenderFunc, nullptr);
        auto parent = AceType::DynamicCast<UINode>(FrameNode::GetFrameNode(V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId));
        auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(parent);
        if (navDestinationNode && navDestinationNode->GetContentNode()) {
            parent = navDestinationNode->GetContentNode();
        }
        if (deepRenderFunc) {
            ScopedViewStackProcessor scopedViewStackProcessor;
            ViewStackProcessor::GetInstance()->Push(parent);
            deepRenderFunc();
            ViewStackProcessor::GetInstance()->PopContainer();
            ViewStackProcessor::GetInstance()->Finish();
        }
        return parent;
    };
    auto ctx = AceType::MakeRefPtr<NG::NavDestinationContext>();
    auto navPathInfo = AceType::MakeRefPtr<NavPathInfo>();
    ctx->SetNavPathInfo(navPathInfo);
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId,
        [shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(std::move(deepRender)), ctx]() {
            auto pattern = AceType::MakeRefPtr<NavDestinationPattern>(shallowBuilder);
            pattern->SetNavDestinationContext(ctx);
            return pattern;
        });
    ctx->SetUniqueId(navDestinationNode->GetId());
    if (!navDestinationNode->GetTitleBarNode()) {
        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
            CreateImageButton(navDestinationNode);
        } else {
            CreateBackButton(navDestinationNode);
        }
        auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
        if (titleBarNode) {
            auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
            CHECK_NULL_RETURN(titleBarLayoutProperty, navDestinationNode);
            titleBarLayoutProperty->UpdateTitleBarParentType(TitleBarParentType::NAV_DESTINATION);
        }
    }
    // content node
    if (!navDestinationNode->GetContentNode()) {
        int32_t contentNodeId = ElementRegister::GetInstance()->MakeUniqueId();
        ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::NAVDESTINATION_CONTENT_ETS_TAG, contentNodeId);
        auto contentNode = FrameNode::GetOrCreateFrameNode(V2::NAVDESTINATION_CONTENT_ETS_TAG, contentNodeId,
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        navDestinationNode->AddChild(contentNode);
        navDestinationNode->SetContentNode(contentNode);
    }
    CreateToolBarNode(navDestinationNode);
    return navDestinationNode;
}

void NavDestinationModelStatic::SetHideTitleBar(FrameNode* frameNode, bool hideTitleBar, bool animated)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavDestinationLayoutProperty, HideTitleBar, hideTitleBar, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(NavDestinationLayoutProperty, IsAnimatedTitleBar, animated, frameNode);
}

void NavDestinationModelStatic::SetOnShown(FrameNode* frameNode, std::function<void()>&& onShow)
{
    CHECK_NULL_VOID(frameNode);
    auto navDestinationEventHub = AceType::DynamicCast<NavDestinationEventHub>(frameNode->GetEventHub<EventHub>());
    CHECK_NULL_VOID(navDestinationEventHub);
    navDestinationEventHub->SetOnShown(onShow);
}

void NavDestinationModelStatic::SetOnHidden(FrameNode* frameNode, std::function<void()>&& onHidden)
{
    CHECK_NULL_VOID(frameNode);
    auto navDestinationEventHub = AceType::DynamicCast<NavDestinationEventHub>(frameNode->GetEventHub<EventHub>());
    CHECK_NULL_VOID(navDestinationEventHub);
    navDestinationEventHub->SetOnHidden(onHidden);
}

void NavDestinationModelStatic::SetOnBackPressed(FrameNode* frameNode, std::function<bool()>&& onBackPressed)
{
    CHECK_NULL_VOID(frameNode);
    auto navDestinationEventHub = AceType::DynamicCast<NavDestinationEventHub>(frameNode->GetEventHub<EventHub>());
    CHECK_NULL_VOID(navDestinationEventHub);
    navDestinationEventHub->SetOnBackPressed(onBackPressed);
}

void NavDestinationModelStatic::SetNavDestinationMode(
    FrameNode* frameNode, const std::optional<NavDestinationMode>& mode)
{
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    CHECK_NULL_VOID(navDestinationNode);
    navDestinationNode->SetNavDestinationMode(mode.value_or(NavDestinationMode::STANDARD));
}

void NavDestinationModelStatic::SetOnReady(
    FrameNode* frameNode, std::function<void(RefPtr<NavDestinationContext>)>&& onReady)
{
    CHECK_NULL_VOID(frameNode);
    auto navDestinationEventHub = AceType::DynamicCast<NavDestinationEventHub>(frameNode->GetEventHub<EventHub>());
    CHECK_NULL_VOID(navDestinationEventHub);
    navDestinationEventHub->SetOnReady(onReady);
}

void NavDestinationModelStatic::SetOnWillAppear(FrameNode* frameNode, std::function<void()>&& willAppear)
{
    CHECK_NULL_VOID(frameNode);
    auto navDestinationEventHub = AceType::DynamicCast<NavDestinationEventHub>(frameNode->GetEventHub<EventHub>());
    CHECK_NULL_VOID(navDestinationEventHub);
    navDestinationEventHub->SetOnWillAppear(willAppear);
}

void NavDestinationModelStatic::SetOnWillDisAppear(FrameNode* frameNode, std::function<void()>&& willDisAppear)
{
    CHECK_NULL_VOID(frameNode);
    auto navDestinationEventHub = AceType::DynamicCast<NavDestinationEventHub>(frameNode->GetEventHub<EventHub>());
    CHECK_NULL_VOID(navDestinationEventHub);
    navDestinationEventHub->SetOnWillDisAppear(willDisAppear);
}

void NavDestinationModelStatic::SetOnWillShow(FrameNode* frameNode, std::function<void()>&& willShow)
{
    CHECK_NULL_VOID(frameNode);
    auto navDestinationEventHub = AceType::DynamicCast<NavDestinationEventHub>(frameNode->GetEventHub<EventHub>());
    CHECK_NULL_VOID(navDestinationEventHub);
    navDestinationEventHub->SetOnWillShow(willShow);
}

void NavDestinationModelStatic::SetOnWillHide(FrameNode* frameNode, std::function<void()>&& willHide)
{
    CHECK_NULL_VOID(frameNode);
    auto navDestinationEventHub = AceType::DynamicCast<NavDestinationEventHub>(frameNode->GetEventHub<EventHub>());
    CHECK_NULL_VOID(navDestinationEventHub);
    navDestinationEventHub->SetOnWillHide(willHide);
}

void NavDestinationModelStatic::SetRecoverable(FrameNode* frameNode, const std::optional<bool>& recoverable)
{
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    CHECK_NULL_VOID(navDestinationNode);
    navDestinationNode->SetRecoverable(recoverable.value_or(true));
}

void NavDestinationModelStatic::SetTitlebarOptions(FrameNode* frameNode, NavigationTitlebarOptions&& opt)
{
    CHECK_NULL_VOID(frameNode);
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    CHECK_NULL_VOID(navDestinationNode);
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(navDestinationPattern);
    navDestinationPattern->SetTitleBarStyle(opt.brOptions.barStyle);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    titleBarPattern->SetTitlebarOptions(opt);
}

void NavDestinationModelStatic::ParseCommonTitle(FrameNode* frameNode, const NG::NavigationTitleInfo& titleInfo)
{
    if (!titleInfo.hasSubTitle && !titleInfo.hasMainTitle) {
        return;
    }
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    CHECK_NULL_VOID(navDestinationNode);

    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    if (navDestinationNode->GetPrevTitleIsCustomValue(false)) {
        // remove custom title if any.
        titleBarNode->RemoveChild(titleBarNode->GetTitle());
        titleBarNode->SetTitle(nullptr);
        auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
        CHECK_NULL_VOID(titleBarLayoutProperty);
        // reset custom title height if any.
        if (titleBarLayoutProperty->HasTitleHeight()) {
            titleBarLayoutProperty->ResetTitleHeight();
        }
    }
    navDestinationNode->UpdatePrevTitleIsCustom(false);

    auto theme = NavigationGetTheme();
    // create or update main title
    NavigationTitleUtil::CreateOrUpdateDestinationMainTitle(titleBarNode, titleInfo);

    // create or update subtitle
    NavigationTitleUtil::CreateOrUpdateDestinationSubtitle(titleBarNode, titleInfo);
    return;
}

void NavDestinationModelStatic::SetHideToolBar(FrameNode* frameNode, bool hideToolBar, bool animated)
{
    CHECK_NULL_VOID(frameNode);
    auto navDestinationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    CHECK_NULL_VOID(navDestinationGroupNode);
    auto navDestinationLayoutProperty = navDestinationGroupNode->GetLayoutPropertyPtr<NavDestinationLayoutProperty>();
    CHECK_NULL_VOID(navDestinationLayoutProperty);
    navDestinationLayoutProperty->UpdateHideToolBar(hideToolBar);
    navDestinationLayoutProperty->UpdateIsAnimatedToolBar(animated);
}

void NavDestinationModelStatic::SetIgnoreLayoutSafeArea(FrameNode* frameNode, const NG::IgnoreLayoutSafeAreaOpts& opts)
{
    auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    CHECK_NULL_VOID(navDestination);
    auto navdestinationLayoutProperty = navDestination->GetLayoutProperty<NavDestinationLayoutProperty>();
    CHECK_NULL_VOID(navdestinationLayoutProperty);
    navdestinationLayoutProperty->UpdateIgnoreLayoutSafeAreaOpts(opts);
}

void NavDestinationModelStatic::SetToolbarConfiguration(FrameNode* frameNode, 
    std::vector<NG::BarItem>&& toolBarItems)
{
    CHECK_NULL_VOID(frameNode);
    auto navdestinationGroupNode =
        AceType::DynamicCast<NavDestinationGroupNode>(Referenced::Claim<FrameNode>(frameNode));
    CHECK_NULL_VOID(navdestinationGroupNode);
    bool enabled = false;
    auto hub = navdestinationGroupNode->GetEventHub<EventHub>();
    if (hub) {
        enabled = hub->IsEnabled();
    }
    FieldProperty fieldProperty;
    fieldProperty.parentId = navdestinationGroupNode->GetInspectorId().value_or("");
    fieldProperty.field = NG::DES_FIELD;
    NavigationToolbarUtil::SetToolbarConfiguration(
        navdestinationGroupNode, std::move(toolBarItems), enabled, fieldProperty);
}

void NavDestinationModelStatic::SetToolBarOptions(FrameNode* frameNode, NavigationToolbarOptions&& opt)
{
    CHECK_NULL_VOID(frameNode);
    auto navdestinationGroupNode =
        AceType::DynamicCast<NavDestinationGroupNode>(Referenced::Claim<FrameNode>(frameNode));
    CHECK_NULL_VOID(navdestinationGroupNode);
    NavigationToolbarUtil::SetToolbarOptions(navdestinationGroupNode, std::move(opt));
}

void NavDestinationModelStatic::SetToolbarMorebuttonOptions(FrameNode* frameNode, MoreButtonOptions&& opt)
{
    CHECK_NULL_VOID(frameNode);
    auto navdestinationGroupNode =
        AceType::DynamicCast<NavDestinationGroupNode>(Referenced::Claim<FrameNode>(frameNode));
    CHECK_NULL_VOID(navdestinationGroupNode);
    NavigationToolbarUtil::SetToolbarMoreButtonOptions(navdestinationGroupNode, std::move(opt));
}

void NavDestinationModelStatic::SetCustomMenu(FrameNode* frameNode, const RefPtr<UINode>& customNode)
{
    CHECK_NULL_VOID(frameNode);
    auto navDestinationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    CHECK_NULL_VOID(navDestinationGroupNode);
    // if previous menu exists, remove it if their ids are not the same
    // if previous node is not custom, their ids must not be the same
    if (navDestinationGroupNode->GetMenu()) {
        if (customNode->GetId() == navDestinationGroupNode->GetMenu()->GetId()) {
            navDestinationGroupNode->UpdateMenuNodeOperation(ChildNodeOperation::NONE);
            return;
        }
        navDestinationGroupNode->SetMenu(customNode);
        navDestinationGroupNode->UpdatePrevMenuIsCustom(true);
        navDestinationGroupNode->UpdateMenuNodeOperation(ChildNodeOperation::REPLACE);
        navDestinationGroupNode->MarkDirtyNode();
        navDestinationGroupNode->MarkModifyDone();
        return;
    }
    navDestinationGroupNode->SetMenu(customNode);
    navDestinationGroupNode->UpdatePrevMenuIsCustom(true);
    navDestinationGroupNode->UpdateMenuNodeOperation(ChildNodeOperation::ADD);
    navDestinationGroupNode->MarkDirtyNode();
    navDestinationGroupNode->MarkModifyDone();
}

void NavDestinationModelStatic::SetCustomTitle(FrameNode* frameNode, const RefPtr<UINode>& customNode)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(customNode);
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    CHECK_NULL_VOID(navDestinationNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    if (!navDestinationNode->GetPrevTitleIsCustomValue(false)) {
        titleBarNode->RemoveChild(titleBarNode->GetTitle());
        titleBarNode->RemoveChild(titleBarNode->GetSubtitle());
        titleBarNode->SetTitle(nullptr);
        titleBarNode->SetSubtitle(nullptr);
    }
    navDestinationNode->UpdatePrevTitleIsCustom(true);
    auto currentTitle = titleBarNode->GetTitle();
    if (currentTitle && customNode->GetId() == currentTitle->GetId()) {
        // do nothing
        return;
    }
    // update custom title
    titleBarNode->RemoveChild(currentTitle);
    titleBarNode->SetTitle(customNode);
    titleBarNode->AddChild(customNode);
    titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void NavDestinationModelStatic::SetCustomToolBar(FrameNode* frameNode, const RefPtr<UINode>& customNode)
{
    auto navDestinationGroupNode =
        AceType::DynamicCast<NavDestinationGroupNode>(Referenced::Claim<FrameNode>(frameNode));
    CHECK_NULL_VOID(navDestinationGroupNode);
    NavigationToolbarUtil::SetCustomToolBar(navDestinationGroupNode, customNode);
}

void NavDestinationModelStatic::SetTitleHeight(FrameNode* frameNode, const Dimension& titleHeight, bool isValid)
{
    auto navDestinationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    CHECK_NULL_VOID(navDestinationGroupNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationGroupNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    if (isValid) {
        titleBarLayoutProperty->UpdateTitleHeight(titleHeight);
    } else {
        titleBarLayoutProperty->ResetTitleHeight();
    }
}
} // namespace OHOS::Ace::NG