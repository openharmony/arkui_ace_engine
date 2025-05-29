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
constexpr float TRANSLATE_THRESHOLD = 26.0f;
const auto TRANSLATE_CURVE = AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 228.0f, 30.0f);

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
        auto hub = navDestinationGroupNode->GetOrCreateEventHub<EventHub>();
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

bool GetTitleOrToolBarTranslateAndHeight(const RefPtr<FrameNode>& barNode, float& translate, float& height)
{
    CHECK_NULL_RETURN(barNode, false);
    auto renderContext = barNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    auto options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    translate = options.y.ConvertToPx();
    height = renderContext->GetPaintRectWithoutTransform().Height();
    return true;
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
    if (scrollableProcessor_) {
        scrollableProcessor_->UnbindAllScrollers();
    }
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
    UpdateHideBarProperty();
    ExpandContentSafeAreaIfNeeded();
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
    if (scrollableProcessor_) {
        scrollableProcessor_->UpdateBindingRelation();
    }
    auto renderContext = hostNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    hostNode->UpdateUserSetOpacity(renderContext->GetOpacity().value_or(1.0f));

    CheckIfOrientationChanged();
    CheckIfStatusBarConfigChanged();
    CheckIfNavigationIndicatorConfigChagned();
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
    CHECK_NULL_VOID(hostNode);
    if (hostNode->GetInspectorId().has_value()) {
        name_ = hostNode->GetInspectorIdValue();
    } else {
        name_ = std::to_string(hostNode->GetId());
    }
    auto pathInfo = GetNavPathInfo();
    if (pathInfo) {
        pathInfo->SetName(name_);
    }
}

void NavDestinationPattern::UpdateBackgroundColor()
{
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    if (hostNode->GetRerenderable()) {
        ContainerScope scope(hostNode->GetInstanceId());
        UpdateBackgroundColorIfNeeded(hostNode);
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

    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    if (backButtonNode) {
        auto backButtonLayoutProperty = backButtonNode->GetLayoutProperty();
        CHECK_NULL_VOID(backButtonLayoutProperty);
        backButtonLayoutProperty->UpdateVisibility(
            navDestinationLayoutProperty->GetHideBackButtonValue(false) ? VisibleType::GONE : VisibleType::VISIBLE);
    }
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

    auto navDesIndex = hostNode->GetIndex();
    if (navDesIndex == 0) {
        navDestinationLayoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
        titleBarLayoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    }

    if (currHideTitleBar_.has_value() && currHideTitleBar_.value() != hideTitleBar && hideTitleBar) {
        /**
         * we need reset translate&opacity of titleBar when state change from show to hide. @sa EnableTitleBarSwipe
         */
        NavigationTitleUtil::UpdateTitleOrToolBarTranslateYAndOpacity(hostNode, titleBarNode, 0.0f, true);
    }
    // At the initial state, animation is not required.
    if (!currHideTitleBar_.has_value() || !navDestinationLayoutProperty->GetIsAnimatedTitleBarValue(false)) {
        currHideTitleBar_ = hideTitleBar;
        HideOrShowTitleBarImmediately(hostNode, hideTitleBar);
        return;
    }

    titleBarNode->MarkModifyDone();
    titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);

    // Animation is needed only when the status changed.
    needRunTitleBarAnimation = currHideTitleBar_.value() != hideTitleBar;
    currHideTitleBar_ = hideTitleBar;
}

bool NavDestinationPattern::GetBackButtonState()
{
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, false);
    auto navDestinationLayoutProperty = hostNode->GetLayoutProperty<NavDestinationLayoutProperty>();
    CHECK_NULL_RETURN(navDestinationLayoutProperty, false);

    auto translateState = navDestinationLayoutProperty->GetTitleBarTranslateStateValue(BarTranslateState::NONE);
    if (navDestinationLayoutProperty->GetHideTitleBarValue(false) && translateState == BarTranslateState::NONE) {
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
    if (navDestinationLayoutProperty->GetHideBackButtonValue(false)) {
        showBackButton = false;
    }
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
    pipeline->GetMemoryManager()->AddRecyclePageNode(host);
}

void NavDestinationPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto id = frameNode->GetId();
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(id);
    pipeline->RemoveWindowSizeChangeCallback(id);
    pipeline->GetMemoryManager()->RemoveRecyclePageNode(id);
}

void NavDestinationPattern::DumpInfo()
{
    DumpLog::GetInstance().AddDesc(std::string("name: ").append(name_));
}

bool NavDestinationPattern::OverlayOnBackPressed()
{
    CHECK_NULL_RETURN(overlayManager_, false);
    if (overlayManager_->IsCurrentNodeProcessRemoveOverlay(GetHost(), false)) {
        return overlayManager_->RemoveOverlay(true);
    }
    return false;
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
    if (preWidth_.has_value() && preWidth_.value() != width) {
        AbortBarAnimation();
    }
    preWidth_ = width;
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
    if (type == WindowSizeChangeReason::ROTATION) {
        CloseLongPressDialog();
    }
}

void NavDestinationPattern::CloseLongPressDialog()
{
    auto navDestinationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(GetHost());
    CHECK_NULL_VOID(navDestinationGroupNode);
    auto pipeline = navDestinationGroupNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);

    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationGroupNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    CHECK_NULL_VOID(titleBarPattern);
    auto backButtonDialogNode = titleBarPattern->GetBackButtonDialogNode();
    if (backButtonDialogNode) {
        overlayManager->CloseDialog(backButtonDialogNode);
        titleBarPattern->SetBackButtonDialogNode(nullptr);
    }
    auto menuItemDialogNode = titleBarPattern->GetLargeFontPopUpDialogNode();
    if (menuItemDialogNode) {
        overlayManager->CloseDialog(menuItemDialogNode);
        titleBarPattern->SetLargeFontPopUpDialogNode(nullptr);
    }
}

void NavDestinationPattern::UpdateTitleAndToolBarHiddenOffset(float offset)
{
    CancelShowTitleAndToolBarTask();
    auto nodeBase = AceType::DynamicCast<NavDestinationNodeBase>(GetHost());
    CHECK_NULL_VOID(nodeBase);
    if (EnableTitleBarSwipe(nodeBase)) {
        auto titleBarNode = AceType::DynamicCast<TitleBarNode>(nodeBase->GetTitleBarNode());
        UpdateBarHiddenOffset(nodeBase, titleBarNode, offset, true);
    }
    if (EnableToolBarSwipe(nodeBase)) {
        auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(nodeBase->GetToolBarNode());
        UpdateBarHiddenOffset(nodeBase, toolBarNode, offset, false);
    }
}

void NavDestinationPattern::CancelShowTitleAndToolBarTask()
{
    if (titleBarSwipeContext_.showBarTask) {
        titleBarSwipeContext_.showBarTask.Cancel();
        titleBarSwipeContext_.showBarTask.Reset(nullptr);
    }
    if (toolBarSwipeContext_.showBarTask) {
        toolBarSwipeContext_.showBarTask.Cancel();
        toolBarSwipeContext_.showBarTask.Reset(nullptr);
    }
}

void NavDestinationPattern::ResetTitleAndToolBarState()
{
    auto nodeBase = AceType::DynamicCast<NavDestinationNodeBase>(GetHost());
    CHECK_NULL_VOID(nodeBase);
    if (EnableTitleBarSwipe(nodeBase)) {
        auto titleBarNode = AceType::DynamicCast<TitleBarNode>(nodeBase->GetTitleBarNode());
        ResetBarState(nodeBase, titleBarNode, true);
    }
    if (EnableToolBarSwipe(nodeBase)) {
        auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(nodeBase->GetToolBarNode());
        ResetBarState(nodeBase, toolBarNode, false);
    }
}

void NavDestinationPattern::ResetBarState(const RefPtr<NavDestinationNodeBase>& nodeBase,
    const RefPtr<FrameNode>& barNode, bool isTitle)
{
    CHECK_NULL_VOID(nodeBase);
    CHECK_NULL_VOID(barNode);
    auto& ctx = GetSwipeContext(isTitle);
    if (ctx.isBarHiding || ctx.isBarShowing) {
        return;
    }

    float translate = 0.0f;
    float barHeight = 0.0f;
    if (!GetTitleOrToolBarTranslateAndHeight(barNode, translate, barHeight) || NearZero(barHeight)) {
        return;
    }

    auto threshold = Dimension(TRANSLATE_THRESHOLD, DimensionUnit::VP).ConvertToPx();
    float halfBarHeight = barHeight / 2.0f;
    if (GreatOrEqual(threshold, halfBarHeight)) {
        threshold = halfBarHeight;
    }
    float showAreaHeight = barHeight - std::abs(translate);
    if (GreatNotEqual(showAreaHeight, 0.0f) && LessNotEqual(showAreaHeight, threshold)) {
        /**
         * Scroll to show a small portion of the titleBar&toolBar,
         * but the height of shownArea is less than the threshold,
         * it needs to be restored to the hidden state.
         */
        StartHideOrShowBarInner(nodeBase, barHeight, translate, isTitle, true);
    } else if (GreatOrEqual(showAreaHeight, barHeight - threshold) && LessNotEqual(showAreaHeight, barHeight)) {
        /**
         * Scroll to hide a small portion of the titleBar&toolBar,
         * but the height of hiddenArea is less than the threshold,
         * it needs to be restored to the shown state.
         */
        StartHideOrShowBarInner(nodeBase, barHeight, translate, isTitle, false);
    }
}

bool NavDestinationPattern::EnableTitleBarSwipe(const RefPtr<NavDestinationNodeBase>& nodeBase)
{
    CHECK_NULL_RETURN(nodeBase, false);
    auto property = nodeBase->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    CHECK_NULL_RETURN(property, false);
    return !property->GetHideTitleBarValue(false);
}

bool NavDestinationPattern::EnableToolBarSwipe(const RefPtr<NavDestinationNodeBase>& nodeBase)
{
    CHECK_NULL_RETURN(nodeBase, false);
    auto property = nodeBase->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    CHECK_NULL_RETURN(property, false);
    return !property->GetHideToolBarValue(false);
}

void NavDestinationPattern::UpdateBarHiddenOffset(
    const RefPtr<NavDestinationNodeBase>& nodeBase, const RefPtr<FrameNode>& barNode, float offset, bool isTitle)
{
    CHECK_NULL_VOID(nodeBase);
    CHECK_NULL_VOID(barNode);
    auto& ctx = GetSwipeContext(isTitle);
    if (ctx.isBarShowing || ctx.isBarHiding) {
        return;
    }

    float preTranslate = 0.0f;
    float barHeight = 0.0f;
    if (!GetTitleOrToolBarTranslateAndHeight(barNode, preTranslate, barHeight) || NearZero(barHeight)) {
        return;
    }

    float newTranslate = 0.0f;
    if (isTitle) {
        newTranslate = std::clamp(preTranslate - offset, -barHeight, 0.0f);
    } else {
        newTranslate = std::clamp(preTranslate + offset, 0.0f, barHeight);
    }
    NavigationTitleUtil::UpdateTitleOrToolBarTranslateYAndOpacity(nodeBase, barNode, newTranslate, isTitle);

    auto threshold = Dimension(TRANSLATE_THRESHOLD, DimensionUnit::VP).ConvertToPx();
    float halfBarHeight = barHeight / 2.0f;
    if (GreatOrEqual(threshold, halfBarHeight)) {
        threshold = halfBarHeight;
    }
    if (Positive(offset) && LessNotEqual(std::abs(preTranslate), threshold) &&
        GreatOrEqual(std::abs(newTranslate), threshold)) {
        // When the scrolling up distance exceeds the threshold, it is necessary to start the hide animation.
        StartHideOrShowBarInner(nodeBase, barHeight, newTranslate, isTitle, true);
    } else if (Negative(offset) && LessNotEqual(barHeight - std::abs(preTranslate), threshold) &&
        GreatOrEqual(barHeight - std::abs(newTranslate), threshold)) {
        // When the scrolling down distance exceeds the threshold, it is necessary to start the show animation.
        StartHideOrShowBarInner(nodeBase, barHeight, newTranslate, isTitle, false);
    }
}

void NavDestinationPattern::ShowTitleAndToolBar()
{
    auto nodeBase = AceType::DynamicCast<NavDestinationNodeBase>(GetHost());
    CHECK_NULL_VOID(nodeBase);
    if (EnableTitleBarSwipe(nodeBase)) {
        auto titleBarNode = AceType::DynamicCast<TitleBarNode>(nodeBase->GetTitleBarNode());
        float translate = 0.0f;
        float barHeight = 0.0f;
        if (GetTitleOrToolBarTranslateAndHeight(titleBarNode, translate, barHeight)) {
            if (titleBarSwipeContext_.showBarTask) {
                titleBarSwipeContext_.showBarTask.Cancel();
                titleBarSwipeContext_.showBarTask.Reset(nullptr);
            }
            StopHideBarIfNeeded(translate, true);
            StartHideOrShowBarInner(nodeBase, barHeight, translate, true, false);
        }
    }
    if (EnableToolBarSwipe(nodeBase)) {
        auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(nodeBase->GetToolBarNode());
        float translate = 0.0f;
        float barHeight = 0.0f;
        if (GetTitleOrToolBarTranslateAndHeight(toolBarNode, translate, barHeight)) {
            if (toolBarSwipeContext_.showBarTask) {
                toolBarSwipeContext_.showBarTask.Cancel();
                toolBarSwipeContext_.showBarTask.Reset(nullptr);
            }
            StopHideBarIfNeeded(translate, false);
            StartHideOrShowBarInner(nodeBase, barHeight, translate, false, false);
        }
    }
}

void NavDestinationPattern::StartHideOrShowBarInner(
    const RefPtr<NavDestinationNodeBase>& nodeBase, float barHeight, float curTranslate, bool isTitle, bool isHide)
{
    CHECK_NULL_VOID(nodeBase);
    auto barNode = GetBarNode(nodeBase, isTitle);
    CHECK_NULL_VOID(barNode);

    auto propertyCallback = [weak = WeakClaim(this), barHeight, isTitle, isHide]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto nodeBase = AceType::DynamicCast<NavDestinationNodeBase>(pattern->GetHost());
        CHECK_NULL_VOID(nodeBase);
        auto barNode = pattern->GetBarNode(nodeBase, isTitle);
        CHECK_NULL_VOID(barNode);
        float translate = isHide ? (isTitle ? -barHeight : barHeight) : 0.0f;
        NavigationTitleUtil::UpdateTitleOrToolBarTranslateYAndOpacity(nodeBase, barNode, translate, isTitle);
    };
    auto finishCallback = [weak = WeakClaim(this), isTitle, isHide]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto nodeBase = AceType::DynamicCast<NavDestinationNodeBase>(pattern->GetHost());
        CHECK_NULL_VOID(nodeBase);
        auto barNode = pattern->GetBarNode(nodeBase, isTitle);
        CHECK_NULL_VOID(barNode);
        auto& ctx = pattern->GetSwipeContext(isTitle);
        if (isHide) {
            ctx.isBarHiding = false;
        } else {
            ctx.isBarShowing = false;
        }
    };
    AnimationOption option;
    option.SetCurve(TRANSLATE_CURVE);
    auto& ctx = GetSwipeContext(isTitle);
    if (isHide) {
        ctx.isBarHiding = true;
    } else {
        ctx.isBarShowing = true;
    }
    NavigationTitleUtil::UpdateTitleOrToolBarTranslateYAndOpacity(nodeBase, barNode, curTranslate, isTitle);
    AnimationUtils::Animate(option, propertyCallback, finishCallback);
}

void NavDestinationPattern::StopHideBarIfNeeded(float curTranslate, bool isTitle)
{
    auto& ctx = GetSwipeContext(isTitle);
    if (!ctx.isBarHiding) {
        return;
    }

    auto propertyCallback = [weak = WeakClaim(this), isTitle, curTranslate]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto nodeBase = AceType::DynamicCast<NavDestinationNodeBase>(pattern->GetHost());
        CHECK_NULL_VOID(nodeBase);
        auto barNode = pattern->GetBarNode(nodeBase, isTitle);
        CHECK_NULL_VOID(barNode);
        NavigationTitleUtil::UpdateTitleOrToolBarTranslateYAndOpacity(nodeBase, barNode, curTranslate, isTitle);
    };
    AnimationOption option;
    option.SetDuration(0);
    option.SetCurve(Curves::LINEAR);
    AnimationUtils::Animate(option, propertyCallback);
    ctx.isBarHiding = false;
}

RefPtr<FrameNode> NavDestinationPattern::GetBarNode(const RefPtr<NavDestinationNodeBase>& nodeBase, bool isTitle)
{
    CHECK_NULL_RETURN(nodeBase, nullptr);
    return isTitle ? AceType::DynamicCast<FrameNode>(nodeBase->GetTitleBarNode())
                   : AceType::DynamicCast<FrameNode>(nodeBase->GetToolBarNode());
}

void NavDestinationPattern::OnCoordScrollStart()
{
    auto navDestinationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(GetHost());
    CHECK_NULL_VOID(navDestinationGroupNode);
    auto navDestinationEventHub = navDestinationGroupNode->GetOrCreateEventHub<NavDestinationEventHub>();
    CHECK_NULL_VOID(navDestinationEventHub);
    navDestinationEventHub->FireOnCoordScrollStartAction();
}

float NavDestinationPattern::OnCoordScrollUpdate(float offset, float currentOffset)
{
    auto navDestinationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(GetHost());
    CHECK_NULL_RETURN(navDestinationGroupNode, 0.0f);
    auto navDestinationEventHub = navDestinationGroupNode->GetOrCreateEventHub<NavDestinationEventHub>();
    CHECK_NULL_RETURN(navDestinationEventHub, 0.0f);
    navDestinationEventHub->FireOnCoordScrollUpdateAction(currentOffset);
    return 0.0f;
}

void NavDestinationPattern::OnCoordScrollEnd()
{
    auto navDestinationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(GetHost());
    CHECK_NULL_VOID(navDestinationGroupNode);
    auto navDestinationEventHub = navDestinationGroupNode->GetOrCreateEventHub<NavDestinationEventHub>();
    CHECK_NULL_VOID(navDestinationEventHub);
    navDestinationEventHub->FireOnCoordScrollEndAction();
}

bool NavDestinationPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, false);
    hostNode->AdjustRenderContextIfNeeded();
    return false;
}

void NavDestinationPattern::CheckIfOrientationChanged()
{
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    if (hostNode->GetNavDestinationMode() == NavDestinationMode::DIALOG) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "Setting Orientation is not supported in dialog mode");
        return;
    }

    std::optional<Orientation> curOri = hostNode->GetOrientation();
    std::optional<Orientation> preOri = hostNode->GetPreOrientation();
    if (isFirstTimeCheckOrientation_) {
        isFirstTimeCheckOrientation_ = false;
        hostNode->SetPreOrientation(curOri);
        return;
    }
    if (curOri == preOri) {
        return;
    }
    hostNode->SetPreOrientation(curOri);

    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(navigationNode_.Upgrade());
    CHECK_NULL_VOID(navigationNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    if (!navigationPattern->IsPageLevelConfigEnabled() || !navigationPattern->IsFullPageNavigation()) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "conditions are not met, orientation won't change");
        return;
    }

    if (hostNode->IsOnAnimation()) {
        StopAnimation();
    } else {
        auto context = hostNode->GetContext();
        CHECK_NULL_VOID(context);
        auto windowMgr = context->GetWindowManager();
        CHECK_NULL_VOID(windowMgr);
        windowMgr->SetRequestedOrientation(curOri, true);
    }
}

void NavDestinationPattern::StopAnimation()
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(navigationNode_.Upgrade());
    CHECK_NULL_VOID(navigationNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    navigationPattern->AbortAnimation(navigationNode);
}

void NavDestinationPattern::CheckIfStatusBarConfigChanged()
{
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    if (hostNode->GetNavDestinationMode() == NavDestinationMode::DIALOG) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "enable/disable statusBar is not supported in dialog mode");
        return;
    }

    auto curConfig = hostNode->GetStatusBarConfig();
    auto preConfig = hostNode->GetPreStatusBarConfig();
    if (isFirstTimeCheckStatusBarConfig_) {
        isFirstTimeCheckStatusBarConfig_ = false;
        hostNode->SetPreStatusBarConfig(curConfig);
        return;
    }
    if (curConfig == preConfig) {
        return;
    }
    hostNode->SetPreStatusBarConfig(curConfig);

    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(navigationNode_.Upgrade());
    CHECK_NULL_VOID(navigationNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    if (!navigationPattern->IsPageLevelConfigEnabled() || !navigationPattern->IsFullPageNavigation()) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "conditions are not met, status won't change");
        return;
    }

    auto context = hostNode->GetContext();
    CHECK_NULL_VOID(context);
    auto mgr = context->GetWindowManager();
    CHECK_NULL_VOID(mgr);
    std::optional<bool> enable;
    std::optional<bool> animated;
    if (curConfig.has_value()) {
        enable = curConfig.value().first;
        animated = curConfig.value().second;
    }
    mgr->SetWindowSystemBarEnabled(SystemBarType::STATUS, enable, animated);
}

void NavDestinationPattern::CheckIfNavigationIndicatorConfigChagned()
{
    auto hostNode = AceType::DynamicCast<NavDestinationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    if (hostNode->GetNavDestinationMode() == NavDestinationMode::DIALOG) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "enable/disable navIndicator is not supported in dialog mode");
        return;
    }

    auto curConfig = hostNode->GetNavigationIndicatorConfig();
    auto preConfig = hostNode->GetPreNavigationIndicatorConfig();
    if (isFirstTimeCheckNavigationIndicatorConfig_) {
        isFirstTimeCheckNavigationIndicatorConfig_ = false;
        hostNode->SetPreNavigationIndicatorConfig(curConfig);
        return;
    }
    if (curConfig == preConfig) {
        return;
    }
    hostNode->SetPreNavigationIndicatorConfig(curConfig);

    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(navigationNode_.Upgrade());
    CHECK_NULL_VOID(navigationNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    if (!navigationPattern->IsPageLevelConfigEnabled() || !navigationPattern->IsFullPageNavigation()) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "conditions are not met, navigationIndicator won't change");
        return;
    }

    auto context = hostNode->GetContext();
    CHECK_NULL_VOID(context);
    auto mgr = context->GetWindowManager();
    CHECK_NULL_VOID(mgr);
    std::optional<bool> enable;
    if (curConfig.has_value()) {
        enable = curConfig.value();
    }
    mgr->SetWindowSystemBarEnabled(SystemBarType::NAVIGATION_INDICATOR, enable, std::nullopt);
}
} // namespace OHOS::Ace::NG
