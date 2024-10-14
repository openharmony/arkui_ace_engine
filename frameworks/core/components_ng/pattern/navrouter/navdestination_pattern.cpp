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

#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"

#include "base/log/dump_log.h"
#include "core/common/agingadapation/aging_adapation_dialog_theme.h"
#include "core/common/agingadapation/aging_adapation_dialog_util.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navigation/navigation_toolbar_util.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"

namespace OHOS::Ace::NG {
namespace {
std::atomic<uint64_t> g_navDestinationPatternNextAutoGenId = 0;
// titlebar ZINDEX
constexpr static int32_t DEFAULT_TITLEBAR_ZINDEX = 2;

void BuildMenu(const RefPtr<NavDestinationGroupNode>& navDestinationGroupNode, const RefPtr<TitleBarNode>& titleBarNode)
{
    if (navDestinationGroupNode->GetMenuNodeOperationValue(ChildNodeOperation::NONE) == ChildNodeOperation::REPLACE) {
        titleBarNode->RemoveChild(titleBarNode->GetMenu());
        titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    if (navDestinationGroupNode->GetPrevMenuIsCustomValue(false)) {
        if (navDestinationGroupNode->GetMenuNodeOperationValue(ChildNodeOperation::NONE) == ChildNodeOperation::NONE) {
            return;
        }
        titleBarNode->SetMenu(navDestinationGroupNode->GetMenu());
        titleBarNode->AddChild(titleBarNode->GetMenu());
        titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        navDestinationGroupNode->UpdateMenuNodeOperation(ChildNodeOperation::NONE);
    } else {
        navDestinationGroupNode->UpdateMenuNodeOperation(ChildNodeOperation::NONE);
        auto navDestinationPattern = navDestinationGroupNode->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(navDestinationPattern);
        auto titleBarMenuItems = navDestinationPattern->GetTitleBarMenuItems();
        auto toolBarMenuItems = navDestinationPattern->GetToolBarMenuItems();

        bool isButtonEnabled = false;
        auto hub = navDestinationGroupNode->GetEventHub<EventHub>();
        if (hub) {
            isButtonEnabled = hub->IsEnabled();
        }
        if (navDestinationPattern->HasMenuNodeId()) {
            auto menuNode = NavigationTitleUtil::CreateMenuItems(navDestinationPattern->GetMenuNodeId(),
                titleBarMenuItems, navDestinationGroupNode, isButtonEnabled, DES_FIELD,
                titleBarNode->GetInnerParentId(), false);
            CHECK_NULL_VOID(menuNode);
            navDestinationGroupNode->SetMenu(menuNode);
        }

        titleBarMenuItems.insert(titleBarMenuItems.end(), toolBarMenuItems.begin(), toolBarMenuItems.end());
        auto landscapeMenuNode = NavigationTitleUtil::CreateMenuItems(navDestinationPattern->GetLandscapeMenuNodeId(),
            titleBarMenuItems, navDestinationGroupNode, isButtonEnabled, DES_FIELD, titleBarNode->GetInnerParentId(),
            true);
        CHECK_NULL_VOID(landscapeMenuNode);
        navDestinationGroupNode->SetLandscapeMenu(landscapeMenuNode);
    }
}
}

NavDestinationPattern::NavDestinationPattern(const RefPtr<ShallowBuilder>& shallowBuilder)
    : shallowBuilder_(shallowBuilder)
{
    navDestinationId_ = g_navDestinationPatternNextAutoGenId.fetch_add(1);
}

NavDestinationPattern::NavDestinationPattern()
{
    navDestinationId_ = g_navDestinationPatternNextAutoGenId.fetch_add(1);
}

NavDestinationPattern::~NavDestinationPattern()
{
    customNode_ = nullptr;
}

void NavDestinationPattern::OnActive()
{
    Pattern::OnActive();
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto navDestinationContext = hostNode->GetRenderContext();
    CHECK_NULL_VOID(navDestinationContext);
    auto navDestinationLayoutProperty = hostNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    CHECK_NULL_VOID(navDestinationLayoutProperty);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    if (navDestinationLayoutProperty->GetHideTitleBar().value_or(false)) {
        titleBarLayoutProperty->UpdateVisibility(VisibleType::GONE);
    } else {
        titleBarLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    }
    titleBarNode->MarkModifyDone();
}

void NavDestinationPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarRenderContext = titleBarNode->GetRenderContext();
    CHECK_NULL_VOID(titleBarRenderContext);
    titleBarNode->SetInnerParentId(hostNode->GetInspectorId().value_or(""));
    // set the titlebar to float on the top
    titleBarRenderContext->UpdateZIndex(DEFAULT_TITLEBAR_ZINDEX);
    auto navDestinationLayoutProperty = hostNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    CHECK_NULL_VOID(navDestinationLayoutProperty);
    isHideToolbar_ = navDestinationLayoutProperty->GetHideToolBarValue(false);
    isHideTitlebar_ = navDestinationLayoutProperty->GetHideTitleBar().value_or(false);
    bool safeAreaOptSet = UpdateBarSafeAreaPadding();
    auto&& opts = hostNode->GetLayoutProperty()->GetSafeAreaExpandOpts();
    auto navDestinationContentNode = AceType::DynamicCast<FrameNode>(hostNode->GetContentNode());
    if (opts && navDestinationContentNode) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "Navdestination SafArea expand as %{public}s", opts->ToString().c_str());
        navDestinationContentNode->GetLayoutProperty()->UpdateSafeAreaExpandOpts(*opts);
        safeAreaOptSet = true;
    }
    if (safeAreaOptSet) {
        navDestinationContentNode->MarkModifyDone();
    }

    UpdateNameIfNeeded(hostNode);
    UpdateBackgroundColorIfNeeded(hostNode);
    bool needRunTitleBarAnimation = false;
    MountTitleBar(hostNode, needRunTitleBarAnimation);
    bool needRunToolBarAnimation = false;
    NavigationToolbarUtil::MountToolBar(hostNode, needRunToolBarAnimation);
    HandleTitleBarAndToolBarAnimation(hostNode, needRunTitleBarAnimation, needRunToolBarAnimation);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (GreatOrEqual(pipeline->GetFontScale(), AgingAdapationDialogUtil::GetDialogBigFontSizeScale())) {
        auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
        CHECK_NULL_VOID(titleBarPattern);
        auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
        CHECK_NULL_VOID(backButtonNode);
        titleBarPattern->InitBackButtonLongPressEvent(backButtonNode);
    }
}

void NavDestinationPattern::OnLanguageConfigurationUpdate()
{
    if (isRightToLeft_ == AceApplicationInfo::GetInstance().IsRightToLeft()) {
        return;
    }
    isRightToLeft_ = AceApplicationInfo::GetInstance().IsRightToLeft();
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    auto backButtonUINode = titleBarNode->GetBackButton();
    auto backButtonNode = AceType::DynamicCast<FrameNode>(backButtonUINode);
    CHECK_NULL_VOID(backButtonNode);
    auto imageNode = backButtonNode->GetFirstChild();
    CHECK_NULL_VOID(imageNode);
    imageNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void NavDestinationPattern::UpdateNameIfNeeded(RefPtr<NavDestinationGroupNode>& hostNode)
{
    if (!name_.empty()) {
        return;
    }

    if (hostNode->GetInspectorId().has_value()) {
        name_ = hostNode->GetInspectorIdValue();
    } else {
        name_ = std::to_string(GetHost()->GetId());
    }
    auto pathInfo = GetNavPathInfo();
    if (pathInfo) {
        pathInfo->SetName(name_);
    }
}

void NavDestinationPattern::UpdateBackgroundColorIfNeeded(RefPtr<NavDestinationGroupNode>& hostNode)
{
    auto renderContext = hostNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (IsUserDefinedBgColor()) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "User defined Background color: %{public}s",
            renderContext->GetBackgroundColor()->ColorToString().c_str());
        return;
    }
    if (hostNode->GetNavDestinationMode() == NavDestinationMode::DIALOG) {
        renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "Set dialog background color: %{public}s",
            renderContext->GetBackgroundColor()->ColorToString().c_str());
        return;
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    if (!pipelineContext) {
        return;
    }
    auto theme = pipelineContext->GetTheme<AppTheme>();
    if (!theme) {
        return;
    }
    renderContext->UpdateBackgroundColor(theme->GetBackgroundColor());
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "Default background color: %{public}s",
        renderContext->GetBackgroundColor()->ColorToString().c_str());
}

void NavDestinationPattern::MountTitleBar(
    RefPtr<NavDestinationGroupNode>& hostNode, bool& needRunTitleBarAnimation)
{
    needRunTitleBarAnimation = false;
    auto navDestinationLayoutProperty = hostNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    CHECK_NULL_VOID(navDestinationLayoutProperty);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);

    if (navDestinationLayoutProperty->HasNoPixMap()) {
        if (navDestinationLayoutProperty->HasImageSource()) {
            titleBarLayoutProperty->UpdateImageSource(navDestinationLayoutProperty->GetImageSourceValue());
        }
        if (navDestinationLayoutProperty->HasPixelMap()) {
            titleBarLayoutProperty->UpdatePixelMap(navDestinationLayoutProperty->GetPixelMapValue());
        }
        titleBarLayoutProperty->UpdateNoPixMap(navDestinationLayoutProperty->GetNoPixMapValue());
    }
    bool hideTitleBar = navDestinationLayoutProperty->GetHideTitleBarValue(false);
    BuildMenu(hostNode, titleBarNode);
    /**
     * if titlebar is the first time to hide/display,
     * doesn't require animation or isn't currently being animated and the
     * hidden/display status hasn't changed.
     */
    if (!currHideTitleBar_.has_value() ||
        !navDestinationLayoutProperty->GetIsAnimatedTitleBarValue(false) ||
        (titleBarAnimationCount_ <= 0 && currHideTitleBar_.value() == hideTitleBar)) {
        currHideTitleBar_ = hideTitleBar;
        HideOrShowTitleBarImmediately(hostNode, hideTitleBar);
        return;
    }

    auto navDesIndex = hostNode->GetIndex();
    if (navDesIndex == 0) {
        navDestinationLayoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
        titleBarLayoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    }

    titleBarNode->MarkModifyDone();
    titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);

    currHideTitleBar_ = hideTitleBar;
    needRunTitleBarAnimation = true;
}

bool NavDestinationPattern::GetBackButtonState()
{
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, false);
    auto navDestinationLayoutProperty = hostNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    CHECK_NULL_RETURN(navDestinationLayoutProperty, false);
    if (navDestinationLayoutProperty->GetHideTitleBarValue(false) && !ForceMeasureTitleBar()) {
        return false;
    }
    // get navigation node
    auto parent = AceType::DynamicCast<FrameNode>(hostNode->GetParent());
    RefPtr<NavigationGroupNode> navigationNode;
    while (parent && !parent->IsRootNode()) {
        navigationNode = AceType::DynamicCast<NavigationGroupNode>(parent);
        if (navigationNode) {
            break;
        }
        parent = AceType::DynamicCast<FrameNode>(parent->GetParent());
    }
    if (!navigationNode) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "can't find navigation node");
        return false;
    }
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_RETURN(navigationLayoutProperty, false);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    auto stack = pattern->GetNavigationStack();
    auto index = stack->FindIndex(name_, customNode_, true);
    bool showBackButton = true;
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    if (index == 0 && (pattern->GetNavigationMode() == NavigationMode::SPLIT ||
        navigationLayoutProperty->GetHideNavBarValue(false))) {
        showBackButton = false;
    }
    auto isCustomTitle = hostNode->GetPrevTitleIsCustomValue(false);
    if (isCustomTitle) {
        return showBackButton;
    }
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_RETURN(titleBarPattern, showBackButton);
    if (titleBarPattern->IsFontSizeSettedByDeveloper()) {
        return showBackButton;
    }
    auto titleNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle());
    CHECK_NULL_RETURN(titleNode, showBackButton);
    auto theme = NavigationGetTheme();
    CHECK_NULL_RETURN(theme, showBackButton);
    auto textLayoutProperty = titleNode->GetLayoutProperty<TextLayoutProperty>();
    auto currentFontSize = textLayoutProperty->GetAdaptMaxFontSizeValue(Dimension(0.0, DimensionUnit::FP));
    auto targetFontSize = showBackButton ? theme->GetTitleFontSizeMin() : theme->GetTitleFontSize();
    if (targetFontSize == currentFontSize) {
        return showBackButton;
    }
    textLayoutProperty->UpdateAdaptMaxFontSize(targetFontSize);
    textLayoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    return showBackButton;
}

void NavDestinationPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_SYSTEM | SAFE_AREA_TYPE_CUTOUT,
            .edges = SAFE_AREA_EDGE_ALL };
        host->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
    }
    isRightToLeft_ = AceApplicationInfo::GetInstance().IsRightToLeft();
    auto id = host->GetId();
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowStateChangedCallback(id);
    pipeline->AddWindowSizeChangeCallback(id);
}

void NavDestinationPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto id = frameNode->GetId();
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(id);
    pipeline->RemoveWindowSizeChangeCallback(id);
}

void NavDestinationPattern::DumpInfo()
{
    DumpLog::GetInstance().AddDesc(std::string("name: ").append(name_));
}

bool NavDestinationPattern::OverlayOnBackPressed()
{
    CHECK_NULL_RETURN(overlayManager_, false);
    CHECK_EQUAL_RETURN(overlayManager_->IsModalEmpty(), true, false);
    return overlayManager_->RemoveOverlay(true);
}

bool NavDestinationPattern::NeedIgnoreKeyboard()
{
    auto layoutProperty = GetLayoutProperty<NavDestinationLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto& opts = layoutProperty->GetSafeAreaExpandOpts();
    if (opts && (opts->type & SAFE_AREA_TYPE_KEYBOARD) && (opts->edges & SAFE_AREA_EDGE_BOTTOM)) {
        return true;
    }
    return false;
}

void NavDestinationPattern::OnFontScaleConfigurationUpdate()
{
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto titleBarUINode = hostNode->GetTitleBarNode();
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(titleBarUINode);
    CHECK_NULL_VOID(titleBarNode);
    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    CHECK_NULL_VOID(backButtonNode);
    if (LessNotEqual(pipeline->GetFontScale(), AgingAdapationDialogUtil::GetDialogBigFontSizeScale())) {
        auto gestureHub = backButtonNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->SetLongPressEvent(nullptr);
        auto longPressRecognizer = gestureHub->GetLongPressRecognizer();
        CHECK_NULL_VOID(longPressRecognizer);
        longPressRecognizer->SetOnActionEnd(nullptr);
        return;
    }
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    titleBarPattern->InitBackButtonLongPressEvent(backButtonNode);
}

void NavDestinationPattern::SetSystemBarStyle(const RefPtr<SystemBarStyle>& style)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_VOID(windowManager);
    if (!backupStyle_.has_value()) {
        backupStyle_ = windowManager->GetSystemBarStyle();
    }
    currStyle_ = style;
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(navigationNode_.Upgrade());
    CHECK_NULL_VOID(navigationNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    if (navigationPattern->IsFullPageNavigation() && navigationPattern->IsTopNavDestination(host)) {
        if (currStyle_.value() != nullptr) {
            windowManager->SetSystemBarStyle(currStyle_.value());
        } else {
            navigationPattern->TryRestoreSystemBarStyle(windowManager);
        }
    }
}

int32_t NavDestinationPattern::GetTitlebarZIndex() const
{
    return DEFAULT_TITLEBAR_ZINDEX;
}

void NavDestinationPattern::OnWindowHide()
{
    CHECK_NULL_VOID(navDestinationContext_);
    auto navPathInfo = navDestinationContext_->GetNavPathInfo();
    CHECK_NULL_VOID(navPathInfo);
    if (!navPathInfo->GetIsEntry()) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "window lifecycle change to hide, clear navDestination entry tag");
    navPathInfo->SetIsEntry(false);
    auto stack = GetNavigationStack().Upgrade();
    CHECK_NULL_VOID(stack);
    auto index = navDestinationContext_->GetIndex();
    stack->SetIsEntryByIndex(index, false);
}

void NavDestinationPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("name", name_.c_str());
}

void NavDestinationPattern::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    auto navDestinationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(GetHost());
    CHECK_NULL_VOID(navDestinationGroupNode);
    // change menu num in landscape and orientation
    do {
        if (navDestinationGroupNode->GetPrevMenuIsCustomValue(false)) {
            break;
        }
        auto targetNum = SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE ? MAX_MENU_NUM_LARGE
                                                                                                  : MAX_MENU_NUM_SMALL;
        if (targetNum == maxMenuNums_) {
            break;
        }
        maxMenuNums_ = targetNum;
        auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationGroupNode->GetTitleBarNode());
        CHECK_NULL_VOID(titleBarNode);
        BuildMenu(navDestinationGroupNode, titleBarNode);
        titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    } while (0);
}
} // namespace OHOS::Ace::NG
