/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/navigation/navigation_pattern.h"

#include <algorithm>
#include <unordered_set>

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "base/log/dump_log.h"
#include "base/log/event_report.h"
#include "base/perfmonitor/perf_constants.h"
#include "base/ressched/ressched_report.h"
#include "base/utils/system_properties.h"
#include "core/common/ime/input_method_manager.h"
#include "core/common/force_split/force_split_utils.h"
#include "core/components_ng/manager/avoid_info/avoid_info_manager.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_content_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_drag_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_model_data.h"
#include "core/components_ng/pattern/navigation/navigation_title_util.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/stage/page_node.h"
#include "core/components_ng/property/measure_utils.h"

#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"
#endif
namespace OHOS::Ace::NG {

constexpr int32_t NAVIMODE_CHANGE_ANIMATION_DURATION = 250;
constexpr int32_t OPACITY_ANIMATION_DURATION_APPEAR = 150;
constexpr int32_t OPACITY_ANIMATION_DURATION_DISAPPEAR = 250;
constexpr int32_t EMPTY_DESTINATION_CHILD_SIZE = 1;
constexpr Dimension DEFAULT_DRAG_REGION = 12.0_vp;
constexpr Dimension DEFAULT_DRAG_BAR_HOT_ZONE = 12.0_vp;
constexpr float DEFAULT_HALF = 2.0f;
const Color MASK_COLOR = Color::FromARGB(25, 0, 0, 0);
constexpr int32_t PAGE_NODES = 1000;
constexpr int32_t PAGE_DEPTH = 300;
constexpr int32_t HALF_POSITION = 50;
constexpr int32_t END_POSITION = 100;
constexpr Dimension DRAG_BAR_RADIUS = 6.0_vp;
constexpr Dimension DRAG_BAR_BLUR_RADIUS = 20.0_vp;
constexpr Dimension DRAG_BAR_ITEM_RADIUS = 1.0_vp;
constexpr int32_t SECOND_ZINDEX_VALUE = 2;
constexpr int32_t INVALID_ANIMATION_ID = -1;
constexpr int32_t FULL_CIRCLE_ANGLE = 360;

namespace {
constexpr int32_t MODE_SWITCH_ANIMATION_DURATION = 500; // ms
const RefPtr<CubicCurve> MODE_SWITCH_CURVE = AceType::MakeRefPtr<CubicCurve>(0.2f, 0.2f, 0.1f, 1.0f);
constexpr Dimension SPLIT_THRESHOLD_WIDTH = 600.0_vp;

const char* DeviceOrientationToString(DeviceOrientation ori)
{
    switch (ori) {
        case DeviceOrientation::PORTRAIT:
            return "PORTRAIT";
        case DeviceOrientation::LANDSCAPE:
            return "LANDSCAPE";
        case DeviceOrientation::ORIENTATION_UNDEFINED:
            return "ORIENTATION_UNDEFINED";
        default:
            return "UNKNOWN";
    }
}

int32_t ConvertDisplayOrientationToRotationAngle(DisplayOrientation ori)
{
    switch (ori) {
        case DisplayOrientation::PORTRAIT: // corresponding to Orientation::PORTRAIT
            return ROTATION_0;
        case DisplayOrientation::LANDSCAPE_INVERTED: // corresponding to Orientation::LANDSCAPE
            return ROTATION_90;
        case DisplayOrientation::PORTRAIT_INVERTED: // corresponding to Orientation::PORTRAIT_INVERTED
            return ROTATION_180;
        case DisplayOrientation::LANDSCAPE: // corresponding to Orientation::LANDSCAPE_INVETED
            return ROTATION_270;
        default:
            return ROTATION_0;
    }
}

GradientColor CreatePercentGradientColor(int32_t percent, Color color)
{
    NG::GradientColor gredient = GradientColor(color);
    gredient.SetDimension(CalcDimension(percent, DimensionUnit::PERCENT));
    return gredient;
}

void ReplaceNodeWithPlaceHolder(
    const RefPtr<FrameNode>& navContentNode, const RefPtr<NavDestinationGroupNode>& node, bool needSetPhVisible)
{
    CHECK_NULL_VOID(navContentNode);
    CHECK_NULL_VOID(node);
    auto phNode = node->GetOrCreatePlaceHolder();
    if (!phNode) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "failed to create placeHolder for destNode[%{public}d]", node->GetId());
        return;
    }
    node->SetIsShowInPrimaryPartition(true);
    node->SetJSViewActive(true);
    auto property = node->GetLayoutProperty();
    if (property) {
        property->UpdateVisibility(VisibleType::VISIBLE);
    }
    auto phProperty = phNode->GetLayoutProperty();
    if (phProperty) {
        phProperty->UpdateVisibility(needSetPhVisible ? VisibleType::VISIBLE : VisibleType::INVISIBLE);
    }

    auto childIndex = navContentNode->GetChildIndex(node);
    if (childIndex < 0) {
        return;
    }
    phNode->SetIndex(node->GetIndex());
    navContentNode->RemoveChildSilently(node);
    navContentNode->AddChild(phNode, childIndex, true);
    navContentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void RestoreNodeFromPlaceHolder(const RefPtr<FrameNode>& primaryContentNode,
    const RefPtr<FrameNode>& navContentNode, const RefPtr<NavDestinationGroupNode>& node)
{
    CHECK_NULL_VOID(primaryContentNode);
    CHECK_NULL_VOID(navContentNode);
    CHECK_NULL_VOID(node);
    node->SetIsShowInPrimaryPartition(false);
    auto phNode = node->GetOrCreatePlaceHolder();
    CHECK_NULL_VOID(phNode);
    auto childIndex = navContentNode->GetChildIndex(phNode);
    if (childIndex < 0) {
        return;
    }

    node->SetIndex(phNode->GetIndex());
    primaryContentNode->RemoveChildSilently(node);
    primaryContentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    navContentNode->RemoveChildSilently(phNode);
    navContentNode->AddChild(node, childIndex, true);
    navContentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    node->SetJSViewActive(true);
    auto property = node->GetLayoutProperty();
    CHECK_NULL_VOID(property);
    property->UpdateVisibility(VisibleType::VISIBLE);
}

void ReorderPrimaryNodes(const RefPtr<FrameNode>& primaryContentNode,
    const std::vector<WeakPtr<NavDestinationGroupNode>>& nodes)
{
    int32_t slot = 0;
    for (const auto& weakNode : nodes) {
        auto node = weakNode.Upgrade();
        CHECK_NULL_CONTINUE(node);
        auto childIndex = primaryContentNode->GetChildIndex(node);
        if (childIndex < 0) {
            node->MountToParent(primaryContentNode, slot, true);
        } else if (slot != childIndex) {
            node->MovePosition(slot);
        }
        slot++;
    }
}

void BuildNavDestinationInfoFromContext(const std::string& navigationId, NavDestinationState state,
    const RefPtr<NavDestinationContext>& context, bool isFrom, std::optional<NavDestinationInfo>& info)
{
    if (!context) {
        info.reset();
        return;
    }

    int32_t index = isFrom ? context->GetPreIndex() : context->GetIndex();
    std::string navDestinationId = std::to_string(context->GetNavDestinationId());
    std::string name;
    napi_value param = nullptr;
    auto pathInfo = context->GetNavPathInfo();
    if (pathInfo) {
        name = pathInfo->GetName();
        param = pathInfo->GetParamObj();
    }
    NavDestinationMode mode = context->GetMode();
    int32_t uniqueId = context->GetUniqueId();
    info = std::make_optional<NavDestinationInfo>(navigationId, name, state, index, param,
        navDestinationId, mode, uniqueId);
}

void LogCustomAnimationStart(const RefPtr<NavDestinationGroupNode>& preTopDestination,
    const RefPtr<NavDestinationGroupNode>& newTopNavDestination, NavigationOperation operation)
{
    RefPtr<NavDestinationPattern> prePattern =
        preTopDestination ? preTopDestination->GetPattern<NavDestinationPattern>() : nullptr;
    RefPtr<NavDestinationPattern> newPattern =
        newTopNavDestination ? newTopNavDestination->GetPattern<NavDestinationPattern>() : nullptr;
    TAG_LOGI(AceLogTag::ACE_NAVIGATION,
        "custom animation start: operation: %{public}d, pre name: %{public}s, id: %{public}s."
        "top name: %{public}s, id: %{public}s",
        operation, prePattern ? prePattern->GetName().c_str() : "null",
        prePattern ? std::to_string(prePattern->GetNavDestinationId()).c_str() : "null",
        newPattern ? newPattern->GetName().c_str() : "null",
        newPattern ? std::to_string(newPattern->GetNavDestinationId()).c_str() : "null");
}

int32_t TriggerNavDestinationTransition(const RefPtr<NavDestinationGroupNode>& navDestination,
    NavigationOperation operation, bool isEnter)
{
    CHECK_NULL_RETURN(navDestination, INVALID_ANIMATION_ID);
    return navDestination->DoTransition(operation, isEnter);
}
} // namespace

NavigationPattern::NavigationPattern()
{
    navigationController_ = std::make_shared<InnerNavigationController>(WeakClaim(this), Container::CurrentId());
}

RefPtr<RenderContext> NavigationPattern::GetTitleBarRenderContext()
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, nullptr);
    auto layoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    auto contentNode = AceType::DynamicCast<FrameNode>(hostNode->GetContentNode());
    CHECK_NULL_RETURN(contentNode, nullptr);
    if (contentNode->FindChildNodeOfClass<NavDestinationGroupNode>()) {
        auto navBarOrHomeDestNode =
            AceType::DynamicCast<NavDestinationNodeBase>(hostNode->GetNavBarOrHomeDestinationNode());
        CHECK_NULL_RETURN(navBarOrHomeDestNode, nullptr);
        auto renderContext = navBarOrHomeDestNode->GetRenderContext();
        return renderContext;
    } else {
        auto renderContext = contentNode->GetRenderContext();
        return renderContext;
    }
}

void NavigationPattern::DoAnimation(NavigationMode usrNavigationMode)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto layoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    layoutProperty->UpdateNavigationMode(navigationMode_);
    hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    AnimationOption option = AnimationOption();
    option.SetDuration(NAVIMODE_CHANGE_ANIMATION_DURATION);
    option.SetCurve(Curves::FRICTION);
    option.SetFillMode(FillMode::FORWARDS);
    AnimationOption optionAlpha = AnimationOption();
    optionAlpha.SetCurve(Curves::SHARP);
    optionAlpha.SetFillMode(FillMode::FORWARDS);
    auto renderContext = GetTitleBarRenderContext();
    CHECK_NULL_VOID(renderContext);

    std::function<void()> finishCallback = [optionAlpha, renderContext, hostNode]() {
        renderContext->OpacityAnimation(optionAlpha, 0, 1);
        hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };

    context->OpenImplicitAnimation(option, option.GetCurve(), finishCallback);
    layoutProperty->UpdateNavigationMode(usrNavigationMode);
    hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    context->FlushUITasks();
    if (usrNavigationMode == NavigationMode::STACK || navigationMode_ == NavigationMode::SPLIT) {
        optionAlpha.SetDuration(OPACITY_ANIMATION_DURATION_DISAPPEAR);
        renderContext->OpacityAnimation(optionAlpha, 1, 0);
    } else if (usrNavigationMode == NavigationMode::SPLIT || navigationMode_ == NavigationMode::STACK) {
        optionAlpha.SetDuration(OPACITY_ANIMATION_DURATION_APPEAR);
        renderContext->OpacityAnimation(optionAlpha, 0, 1);
    }
    context->CloseImplicitAnimation();
    navigationMode_ = usrNavigationMode;
}

void NavigationPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto id = host->GetId();
    context->AddWindowStateChangedCallback(id);
    context->AddWindowSizeChangeCallback(id);

    auto theme = NavigationGetTheme();
    if (theme && theme->GetNavBarUnfocusEffectEnable()) {
        context->AddWindowFocusChangedCallback(id);
    }
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_ALL, .edges = SAFE_AREA_EDGE_ALL };
        host->GetLayoutProperty()->UpdateSafeAreaExpandOpts(opts);
    }
    auto manager = context->GetNavigationManager();
    CHECK_NULL_VOID(manager);
    if (manager->IsForceSplitSupported()) {
        RegisterForceSplitListener(context, id);
    }
}

void NavigationPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto id = frameNode->GetId();
    context->RemoveWindowStateChangedCallback(id);
    context->RemoveWindowSizeChangeCallback(id);
    auto manager = context->GetNavigationManager();
    CHECK_NULL_VOID(manager);
    if (manager->IsForceSplitSupported()) {
        UnregisterForceSplitListener(context, id);
    }
}


void NavigationPattern::DoNavbarHideAnimation(const RefPtr<NavigationGroupNode>& hostNode)
{
    AnimationOption option;
    option.SetCurve(MODE_SWITCH_CURVE);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetDuration(MODE_SWITCH_ANIMATION_DURATION);
    AnimationUtils::Animate(option, [weakHost = WeakPtr<NavigationGroupNode>(hostNode)]() {
        auto hostNode = weakHost.Upgrade();
        CHECK_NULL_VOID(hostNode);
        auto layoutProperty = AceType::DynamicCast<NavigationLayoutProperty>(hostNode->GetLayoutProperty());
        CHECK_NULL_VOID(layoutProperty);
        bool hideNavBar = layoutProperty->GetHideNavBarValue(false);
        auto navBarOrHomeDestNode =
            AceType::DynamicCast<NavDestinationNodeBase>(hostNode->GetNavBarOrHomeDestinationNode());
        CHECK_NULL_VOID(navBarOrHomeDestNode);
        auto navBarLayoutProperty = navBarOrHomeDestNode->GetLayoutProperty();
        CHECK_NULL_VOID(navBarLayoutProperty);
        navBarLayoutProperty->UpdateVisibility(hideNavBar ? VisibleType::INVISIBLE : VisibleType::VISIBLE, true);
        hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        hostNode->GetContext()->FlushUITasks();
    });
}

void NavigationPattern::InitDragBarEvent()
{
    auto dragBarNode = AceType::DynamicCast<FrameNode>(GetDragBarNode());
    CHECK_NULL_VOID(dragBarNode);
    auto dragGestureHub = dragBarNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(dragGestureHub);
    InitDragBarPanEvent(dragGestureHub);
    InitTouchEvent(dragGestureHub);

    // clear divider hover and pan event
    auto dividerNode = GetDividerNode();
    CHECK_NULL_VOID(dividerNode);
    auto dividerGestureHub = dividerNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(dividerGestureHub);
    auto dividerInputHub = dividerNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(dividerInputHub);
    if (hoverEvent_) {
        dividerInputHub->RemoveOnHoverEvent(hoverEvent_);
        hoverEvent_.Reset();
    }
    if (panEvent_) {
        dividerGestureHub->RemovePanEvent(panEvent_);
        panEvent_.Reset();
    }
}

void NavigationPattern::ClearDragBarEvent()
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto dragBarNode = AceType::DynamicCast<FrameNode>(GetDragBarNode());
    CHECK_NULL_VOID(dragBarNode);
    auto dragGestureHub = dragBarNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(dragGestureHub);

    // clear drag bar touch and pan event
    if (touchEvent_) {
        dragGestureHub->RemoveTouchEvent(touchEvent_);
        touchEvent_.Reset();
    }
    if (dragBarPanEvent_) {
        dragGestureHub->RemovePanEvent(dragBarPanEvent_);
        dragBarPanEvent_.Reset();
    }

    hostNode->RemoveChild(dragBarNode);
    hostNode->SetDragBarNode(nullptr);
}

void NavigationPattern::BuildDragBar()
{
    if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TEN)) {
        return;
    }
    if (enableDragBar_) {
        if (GetDragBarNode()) {
            // if dragBar is already in navigation, do nothing
            return;
        }
        // create drag bar and init drag bar gesture event
        auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
        CHECK_NULL_VOID(hostNode);
        CreateDragBarNode(hostNode);
        InitDragBarEvent();
        return;
    }
    auto dividerNode = GetDividerNode();
    CHECK_NULL_VOID(dividerNode);
    auto dividerGestureHub = dividerNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(dividerGestureHub);
    auto dividerInputHub = dividerNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(dividerInputHub);
    InitDividerPanEvent(dividerGestureHub);
    InitDividerMouseEvent(dividerInputHub);
    if (GetDragBarNode()) {
        // clear drag bar gesture event and remove dragBar
        ClearDragBarEvent();
    }
}

bool NavigationPattern::CreateHomeDestination(RefPtr<UINode>& customNode, RefPtr<NavDestinationGroupNode>& homeDest)
{
    CHECK_NULL_RETURN(navigationStack_, false);
    auto host = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    do {
        if (parentNode_.Upgrade() || !host) {
            break;
        }
        auto context = host->GetContext();
        // Avoid the loading problem of atomicservice on the home page
        if ((context && !context->GetInstallationFree()) || !context) {
            break;
        }
        RefPtr<UINode> parentCustomNode;
        auto curNode = host->GetParent();
        while (curNode) {
            auto curTag = curNode->GetTag();
            if (curTag == V2::JS_VIEW_ETS_TAG) {
                parentCustomNode = curNode;
                break;
            }
            curNode = curNode->GetParent();
        }
        auto pattern = host->GetPattern<NavigationPattern>();
        if (pattern && parentCustomNode) {
            pattern->SetParentCustomNode(parentCustomNode);
        }
    } while (false);
    RefPtr<UINode> node;
    if (!navigationStack_->CreateHomeDestination(parentNode_, node)) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "failed to create home NavDestination");
        return false;
    }
    CHECK_NULL_RETURN(node, false);
    node->SetFreeze(true, true);
    auto destNode = AceType::DynamicCast<NavDestinationGroupNode>(
        NavigationGroupNode::GetNavDestinationNode(node));
    CHECK_NULL_RETURN(destNode, false);
    destNode->SetIsHomeDestination(true);
    // set navigation id
    auto destPattern = AceType::DynamicCast<NavDestinationPattern>(destNode->GetPattern());
    if (host && destPattern) {
        destPattern->SetNavigationNode(host);
        destPattern->SetNavigationId(host->GetInspectorId().value_or(""));
    }
    customNode = node;
    homeDest = destNode;
    return true;
}

void NavigationPattern::OnModifyDone()
{
    // !!! Do not add operations about NavPathStack here, see @SyncWithJsStackIfNeeded
    Pattern::OnModifyDone();
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    hostNode->CreateHomeDestinationIfNeeded();
    auto navBarOrHomeDesteNode =
        AceType::DynamicCast<NavDestinationNodeBase>(hostNode->GetNavBarOrHomeDestinationNode());
    if (navBarOrHomeDesteNode) {
        navBarOrHomeDesteNode->MarkModifyDone();
    }
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navBarOrHomeDesteNode);
    isRightToLeft_ = AceApplicationInfo::GetInstance().IsRightToLeft();

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    BuildDragBar();

    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto curNavBarPosition = layoutProperty->GetNavBarPositionValue(NavBarPosition::START);
    if (preNavBarPosition_.has_value() && preNavBarPosition_.value() != curNavBarPosition) {
        MarkAllNavDestinationDirtyIfNeeded(hostNode);
    }
    preNavBarPosition_ = curNavBarPosition;

    auto&& opts = layoutProperty->GetSafeAreaExpandOpts();
    if (opts) {
        uint8_t ignoreExpandKeyboard = 0x11;
        SafeAreaExpandOpts optsExceptKeyboard = { .type = opts->type & ignoreExpandKeyboard,
            .edges = opts->edges };
        if (navBarNode) {
            navBarNode->GetLayoutProperty()->UpdateSafeAreaExpandOpts(optsExceptKeyboard);
            navBarNode->MarkModifyDone();
        }

        auto navigationContentNode = AceType::DynamicCast<FrameNode>(hostNode->GetContentNode());
        CHECK_NULL_VOID(navigationContentNode);
        navigationContentNode->GetLayoutProperty()->UpdateSafeAreaExpandOpts(optsExceptKeyboard);
        navigationContentNode->MarkModifyDone();

        auto dividerNode = AceType::DynamicCast<FrameNode>(hostNode->GetDividerNode());
        CHECK_NULL_VOID(dividerNode);
        dividerNode->GetLayoutProperty()->UpdateSafeAreaExpandOpts(optsExceptKeyboard);
        dividerNode->MarkModifyDone();
    }

    bool enableModeChangeAnimation = layoutProperty->GetEnableModeChangeAnimation().value_or(true);
    if (enableModeChangeAnimation && GetNavigationMode() == NavigationMode::SPLIT && GetNavBarVisibilityChange()) {
        DoNavbarHideAnimation(hostNode);
    }

    if (!HandleIntent(false)) {
        // AddRecoverableNavigation function will check inside whether current navigation can be recovered
        pipeline->GetNavigationManager()->AddRecoverableNavigation(hostNode->GetCurId(), hostNode);
        RestoreJsStackIfNeeded();
    }
    UpdateToobarFocusColor();
    UpdateDividerBackgroundColor();
    NavigationModifyDoneToolBarManager();
}

void NavigationPattern::SetSystemBarStyle(const RefPtr<SystemBarStyle>& style)
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

    // The systemBarStyle may only take effect when navigation fills the entire page.
    if (!isFullPageNavigation_) {
        return;
    }

    // When there is NavDestination in the stack, the systemBarStyle set for Navigation does not take effect.
    do {
        if (!navigationStack_) {
            break;
        }
        auto topPath = navigationStack_->GetTopNavPath();
        if (!topPath.has_value()) {
            break;
        }
        auto topNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(topPath->second));
        if (topNavDestination) {
            return;
        }
    } while (false);

    /**
     * When developers provide a valid style to systemBarStyle, we should set the style to window;
     * when 'undefined' was provided, we should restore the style.
     */
    if (currStyle_.value() != nullptr) {
        windowManager->SetSystemBarStyle(currStyle_.value());
    } else {
        TryRestoreSystemBarStyle(windowManager);
    }
}

void NavigationPattern::OnAttachToMainTree()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    InitPageNode(host);
    InitFoldState();
    RegisterAvoidInfoChangeListener(host);
}

void NavigationPattern::InitFoldState()
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    container->InitIsFoldable();
    if (container->IsFoldable()) {
        currentFoldStatus_ = container->GetCurrentFoldStatus();
    }
}

void NavigationPattern::OnDetachFromMainTree()
{
    isFullPageNavigation_ = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    UnregisterAvoidInfoChangeListener(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_VOID(windowManager);
    TryRestoreSystemBarStyle(windowManager);
    backupStyle_.reset();
    currStyle_.reset();
    pageNode_ = nullptr;
}

bool NavigationPattern::IsTopNavDestination(const RefPtr<UINode>& node) const
{
    CHECK_NULL_RETURN(node, false);
    CHECK_NULL_RETURN(navigationStack_, false);
    auto topPath = navigationStack_->GetTopNavPath();
    RefPtr<NavDestinationGroupNode> destination = nullptr;
    if (!topPath.has_value()) {
        auto host = AceType::DynamicCast<NavigationGroupNode>(GetHost());
        CHECK_NULL_RETURN(host, false);
        destination = AceType::DynamicCast<NavDestinationGroupNode>(host->GetHomeDestinationNode());
    } else {
        destination = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(topPath->second));
    }
    return destination == node;
}

bool NavigationPattern::JudgeFoldStateChangeAndUpdateState()
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto foldStatus = container->GetCurrentFoldStatus();
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "newFoldStatus: %{public}d, currentFoldStatus: %{public}d.",
        static_cast<int32_t>(foldStatus), static_cast<int32_t>(currentFoldStatus_));
    if (foldStatus != currentFoldStatus_) {
        currentFoldStatus_ = foldStatus;
        return true;
    }
    return false;
}

void NavigationPattern::UpdateIsFullPageNavigation(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frame = geometryNode->GetFrameRect();
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_VOID(windowManager);

    bool isFullPage = false;
    auto pageNode = pageNode_.Upgrade();
    if (pageNode) {
        auto pageNodeGeometryNode = pageNode->GetGeometryNode();
        if (pageNodeGeometryNode) {
            auto pageFrame = pageNodeGeometryNode->GetFrameRect();
            isFullPage = pageFrame.GetSize().Width() <= frame.GetSize().Width() &&
                pageFrame.GetSize().Height() <= frame.GetSize().Height();
        }
    }
    pageNode = nullptr;

    if (isFullPage == isFullPageNavigation_) {
        return;
    }

    isFullPageNavigation_ = isFullPage;
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "Navigation[%{public}d] change to %{public}s",
        host->GetId(), isFullPageNavigation_ ? "FullPage" : "PartialPage");
    MarkAllNavDestinationDirtyIfNeeded(host);
    UpdatePageLevelConfigForSizeChanged();
    UpdateSystemBarStyleOnFullPageStateChange(windowManager);
    if (isFullPageNavigation_) {
        RegisterPageVisibilityChangeCallback();
    }
}

void NavigationPattern::UpdateSystemBarStyleOnFullPageStateChange(const RefPtr<WindowManager>& windowManager)
{
    // full page -> partial page
    if (!isFullPageNavigation_) {
        TryRestoreSystemBarStyle(windowManager);
        return;
    }

    // partial page -> full page
    auto topPath = navigationStack_->GetTopNavPath();
    UpdateSystemBarStyleWithTopNavPath(windowManager, topPath);
}

void NavigationPattern::UpdateSystemBarStyleOnTopNavPathChange(
    const std::optional<std::pair<std::string, RefPtr<UINode>>>& newTopNavPath)
{
    if (!isFullPageNavigation_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_VOID(windowManager);
    UpdateSystemBarStyleWithTopNavPath(windowManager, newTopNavPath);
}

void NavigationPattern::UpdateSystemBarStyleWithTopNavPath(const RefPtr<WindowManager>& windowManager,
    const std::optional<std::pair<std::string, RefPtr<UINode>>>& topNavPath)
{
    if (ApplyTopNavPathSystemBarStyleOrRestore(windowManager, topNavPath)) {
        return;
    }

    if (currStyle_.has_value() && currStyle_.value() != nullptr) {
        windowManager->SetSystemBarStyle(currStyle_.value());
    } else {
        TryRestoreSystemBarStyle(windowManager);
    }
}

void NavigationPattern::TryRestoreSystemBarStyle(const RefPtr<WindowManager>& windowManager)
{
    if (backupStyle_.has_value()) {
        windowManager->SetSystemBarStyle(backupStyle_.value());
    }
}

void NavigationPattern::UpdateSystemBarStyleOnPageVisibilityChange(bool show)
{
    if (!isFullPageNavigation_) {
        return;
    }

    CHECK_NULL_VOID(navigationStack_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_VOID(windowManager);
    if (show) {
        // page containing Navigation, hide -> show
        auto topPath = navigationStack_->GetTopNavPath();
        UpdateSystemBarStyleWithTopNavPath(windowManager, topPath);
    } else {
        // page containing Navigation, show -> hide
        TryRestoreSystemBarStyle(windowManager);
    }
}

void NavigationPattern::RegisterPageVisibilityChangeCallback()
{
    auto pageNode = pageNode_.Upgrade();
    CHECK_NULL_VOID(pageNode);
    RefPtr<PagePattern> pagePattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    auto callback = [weak = WeakClaim(this)](bool show) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        // we need update the "systemBarStyle" at the beginning of the transition animation on the router page
        pattern->UpdateSystemBarStyleOnPageVisibilityChange(show);
    };
    pagePattern->SetPageVisibilityChangeCallback(std::move(callback));
}

bool NavigationPattern::ApplyTopNavPathSystemBarStyleOrRestore(
    const RefPtr<WindowManager>& windowManager,
    const std::optional<std::pair<std::string, RefPtr<UINode>>>& topNavPath)
{
    RefPtr<NavDestinationGroupNode> topDestNode = nullptr;
    if (topNavPath.has_value()) {
        topDestNode = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(topNavPath.value().second));
    } else {
        auto host = AceType::DynamicCast<NavigationGroupNode>(GetHost());
        CHECK_NULL_RETURN(host, false);
        topDestNode = AceType::DynamicCast<NavDestinationGroupNode>(host->GetHomeDestinationNode());
    }
    if (!topDestNode) {
        return false;
    }

    auto navDestinationPattern = topDestNode->GetPattern<NavDestinationPattern>();
    if (!navDestinationPattern) {
        return false;
    }
    /**
     * Backup is only performed when the developer sets the "systemBarStyle" attribute,
     * and the entire Navigation is only backed up once.
     * Therefore, when developer only set the "systemBarStyle" attribute to NavDestination, we need to
     * save the attribute to Navigation.
     */
    auto backupFromNavDestination = navDestinationPattern->GetBackupStyle();
    if (!backupStyle_.has_value() && backupFromNavDestination.has_value()) {
        backupStyle_ = backupFromNavDestination;
    }

    auto destCurrStyle = navDestinationPattern->GetCurrentStyle();
    if (destCurrStyle.has_value() && destCurrStyle.value() != nullptr) {
        windowManager->SetSystemBarStyle(destCurrStyle.value());
    } else {
        TryRestoreSystemBarStyle(windowManager);
    }
    return true;
}

void NavigationPattern::InitPageNode(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(host);
    auto parent = host->GetParent();
    CHECK_NULL_VOID(parent);
    RefPtr<FrameNode> pageNode = nullptr;
    while (parent) {
        if (parent->GetTag() == V2::PAGE_ETS_TAG) {
            pageNode = AceType::DynamicCast<FrameNode>(parent);
            break;
        }
        parent = parent->GetParent();
    }
    if (!pageNode) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "Failed to find PageNode of Navigation");
    } else {
        pageNode_ = WeakPtr<FrameNode>(pageNode);
    }
}

void NavigationPattern::OnLanguageConfigurationUpdate()
{
    bool isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (isRightToLeft != isRightToLeft_) {
        auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
        CHECK_NULL_VOID(hostNode);
        hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        isRightToLeft_ = isRightToLeft;
    }
}

int32_t NavigationPattern::GetFirstNewStandardDestinationIndex(const NavPathList& preList, const NavPathList& curList)
{
    struct Hash {
        size_t operator()(const RefPtr<UINode>& node) const
        {
            return node->GetId();
        }
    };
    std::unordered_set<RefPtr<UINode>, Hash> preNodeSet;
    for (const auto& pair : preList) {
        CHECK_NULL_CONTINUE(pair.second);
        preNodeSet.emplace(pair.second);
    }
    int32_t firstNewNodeIndex = -1;
    for (int32_t index = 0; index < static_cast<int32_t>(curList.size()); index++) {
        const auto& uiNode = curList[index].second;
        if (preNodeSet.find(uiNode) != preNodeSet.end()) {
            continue;
        }
        auto node = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(uiNode));
        CHECK_NULL_CONTINUE(node);
        if (node->GetNavDestinationMode() == NavDestinationMode::STANDARD) {
            firstNewNodeIndex = index;
        }
        break;
    }
    return firstNewNodeIndex;
}

void NavigationPattern::ClearSecondaryNodesIfNeeded(NavPathList&& preList)
{
    /**
     * When the following conditions are met:
     * 1. The homeNode exists
     * 2. homeNode is in focus
     * 3. After stack synchronization, the homeNode remains in the stack
     * 4. The latest top NavDestination does not exist in the previous stack
     * 5. The first newly added NavDestination must be of type STANDARD
     *
     * This will trigger the following logic:
     * The NavDestination between the homeNode and the first newly added STANDARD NavDestination will be removed.
     */
    auto homeNode = homeNode_.Upgrade();
    if (!forceSplitSuccess_ || !homeNodeTouched_) {
        return;
    }
    if (!forceSplitUseNavBar_ && !homeNode) {
        return;
    }
    const auto& curList = navigationStack_->GetAllNavDestinationNodes();
    if (curList.empty()) {
        return;
    }
    const auto& curTopNode = curList.back().second;
    auto it = std::find_if(preList.begin(), preList.end(), [&curTopNode](const auto& pair) {
            return pair.second == curTopNode;
        });
    if (it != preList.end()) {
        return;
    }

    std::vector<int32_t> removeIndexes;
    bool foundHomeNode = false;
    int32_t firstNewStandardNodeIndex = GetFirstNewStandardDestinationIndex(preList, curList);
    for (int32_t index = firstNewStandardNodeIndex - 1; index >= 0; --index) {
        auto node = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(curList[index].second));
        CHECK_NULL_CONTINUE(node);
        if (!forceSplitUseNavBar_ && node == homeNode) {
            foundHomeNode = true;
            break;
        }
        removeIndexes.push_back(index);
    }
    if (!forceSplitUseNavBar_ && !foundHomeNode) {
        return;
    }
    if (removeIndexes.empty()) {
        return;
    }

    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "Remove secondary NavDestinationNodes, count:%{public}d",
        static_cast<int32_t>(removeIndexes.size()));
    std::reverse(removeIndexes.begin(), removeIndexes.end());
    navigationStack_->RemoveByIndexes(removeIndexes);
    /**
     * Because calling RemoveByIndexes here will remark the need for stack synchronization for the next VSync signal,
     * but we have already done it proactively, so we will reset the needSyncWithJsStack_ flag here.
     */
    needSyncWithJsStack_ = false;
    UpdateNavPathList();
}

bool NavigationPattern::IsForceSplitSupported(const RefPtr<PipelineContext>& context)
{
    CHECK_NULL_RETURN(context, false);
    auto manager = context->GetNavigationManager();
    CHECK_NULL_RETURN(manager, false);
    return manager->IsForceSplitSupported();
}

void NavigationPattern::SyncWithJsStackIfNeeded()
{
    if (!needSyncWithJsStack_) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION,
            "not need SyncWithJsStack, needSyncWithJsStack_ %{public}d", needSyncWithJsStack_);
        return;
    }
    CHECK_NULL_VOID(navigationStack_);
    needSyncWithJsStack_ = false;
    if (!isFinishInteractiveAnimation_) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION,
            "not need SyncWithJsStack, interactive animation: %{public}d", isFinishInteractiveAnimation_);
        return;
    }
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    TAG_LOGI(AceLogTag::ACE_NAVIGATION,
        "sync with js stack, id: %{public}s, UINodeId: %{public}d, preStackSize: %{public}d, newStackSize: %{public}d",
        hostNode->GetCurId().c_str(), hostNode->GetId(), navigationStack_->PreSize(),
        static_cast<int32_t>(navigationStack_->GetAllPathName().size()));
    GetVisibleNodes(true, preVisibleNodes_);
    if (runningTransitionCount_ <= 0) {
        isTransitionAnimationAborted_ = false;
    }
    preTopNavPath_ = navigationStack_->GetPreTopNavPath();
    preStackSize_ = navigationStack_->PreSize();
    preContext_ = nullptr;
    if (preTopNavPath_.has_value()) {
        auto preDestination = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(preTopNavPath_->second));
        if (preDestination) {
            auto pattern = AceType::DynamicCast<NavDestinationPattern>(preDestination->GetPattern());
            preContext_ = pattern->GetNavDestinationContext();
            if (preContext_) {
                preContext_->SetPreIndex(preStackSize_ - 1);
            }
        }
    }
    if (isCustomAnimation_) {
        navigationStack_->UpdateRecoveryList();
    }
    navigationStack_->SavePreNavList();
    NavPathList preList;
    auto context = hostNode->GetContextRefPtr();
    if (IsForceSplitSupported(context)) {
        preList = navigationStack_->GetPreNavPathList();
        prePrimaryNodes_ = primaryNodes_;
    }
    UpdateNavPathList();
    auto newTopNavPath = navigationStack_->GetTopNavPath();
    auto replaceValue = navigationStack_->GetReplaceValue();
    if (preTopNavPath_ != newTopNavPath || replaceValue == 1) {
        isReplace_ = replaceValue != 0;
        UpdateIsAnimation(preTopNavPath_);
        lastPreIndex_ = 0;
        if (preTopNavPath_.has_value()) {
            lastPreIndex_ = navigationStack_->FindIndex(preTopNavPath_->first, preTopNavPath_->second, true);
        }
        FireInterceptionEvent(true, newTopNavPath);
        if (needSyncWithJsStack_) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "sync with js stack in before interception");
            UpdateNavPathList();
            needSyncWithJsStack_ = false;
        }
    }
    if (IsForceSplitSupported(context)) {
        ClearSecondaryNodesIfNeeded(std::move(preList));
    }
    RefreshNavDestination();
}

void NavigationPattern::RecognizeHomePageIfNeeded()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    if (!IsForceSplitSupported(context)) {
        return;
    }
    const auto& curList = navigationStack_->GetAllNavDestinationNodes();
    std::vector<RefPtr<NavDestinationGroupNode>> allDestNodes;
    for (const auto& pair : curList) {
        auto node = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(pair.second));
        CHECK_NULL_CONTINUE(node);
        allDestNodes.push_back(node);
    }

    auto homeNode = homeNode_.Upgrade();
    if (homeNode) {
        bool homeNodeExistInCurStack = false;
        for (const auto& node : allDestNodes) {
            if (node == homeNode) {
                homeNodeExistInCurStack = true;
                break;
            }
        }
        if (!homeNodeExistInCurStack) {
            homeNode = nullptr;
            homeNode_ = nullptr;
        }
    }
    if (homeNode) {
        return;
    }

    for (const auto& node : allDestNodes) {
        if (ForceSplitUtils::IsNavDestinationHomePage(node)) {
            node->SetNavDestinationType(NavDestinationType::HOME);
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "Recognize dest[%{public}d] as HomePage", node->GetId());
            homeNode_ = WeakPtr(node);
            break;
        }
    }
}

void NavigationPattern::UpdateNavPathList()
{
    CHECK_NULL_VOID(navigationStack_);
    auto pathNames = navigationStack_->GetAllPathName();
    auto indexes = navigationStack_->GetAllPathIndex();
    topFromSingletonMoved_ = navigationStack_->IsTopFromSingletonMoved();
    navigationStack_->ResetSingletonMoved();
    navigationStack_->InitNavPathIndex(pathNames);
    auto cacheNodes = navigationStack_->GetAllCacheNodes();
    NavPathList navPathList;
    int32_t pathListSize = static_cast<int32_t>(pathNames.size());
    isCurTopNewInstance_ = false;
    // lastRecoveredStandardIndex will be only used in recovery case
    int32_t lastRecoveredStandardIndex = 0;
    int32_t removeSize = 0; // push destination failed size
    bool isCurForceSetList = false;
    for (int32_t index = 0; index < pathListSize; ++index) {
        auto pathName = pathNames[index];
        RefPtr<UINode> uiNode = nullptr;
        int32_t arrayIndex = index - removeSize;
        if (navigationStack_->IsFromRecovery(arrayIndex)) {
            if (navigationStack_->GetRecoveredDestinationMode(arrayIndex) ==
                static_cast<int32_t>(NavDestinationMode::STANDARD)) {
                lastRecoveredStandardIndex = arrayIndex;
            }
            navPathList.emplace_back(std::make_pair(pathName, uiNode));
            // only create recovery node when it is at top
            if (index == pathListSize - 1) {
                removeSize += GenerateUINodeFromRecovery(lastRecoveredStandardIndex, navPathList);
            }
            continue;
        }
        auto pathIndex = indexes[index];
        if (navigationStack_->NeedBuildNewInstance(arrayIndex)) {
            navigationStack_->SetNeedBuildNewInstance(arrayIndex, false);
            // if marked NEW_INSTANCE when push/replace in frontend, build a new instance anyway
            if (!GenerateUINodeByIndex(arrayIndex, uiNode)) {
                removeSize++;
                continue;
            }
            navPathList.emplace_back(std::make_pair(pathName, uiNode));
            if (index == pathListSize - 1) {
                isCurTopNewInstance_ = true;
            }
            continue;
        }
        bool isPageForceSet = navigationStack_->GetIsForceSet(arrayIndex);
        if (isPageForceSet) {
            isCurForceSetList = true;
        }
        auto navDestinationId = navigationStack_->GetNavDestinationIdInt(arrayIndex);
        if (index == pathListSize - 1 && addByNavRouter_) {
            addByNavRouter_ = false;
            uiNode = navigationStack_->Get();
        } else if (isCurForceSetList) {
            if (navDestinationId != -1) {
                uiNode = FindNavDestinationNodeInPreList(navDestinationId);
            }
        } else {
            uiNode = navigationStack_->Get(pathIndex);
        }
        if (uiNode) {
            TAG_LOGD(AceLogTag::ACE_NAVIGATION, "find in list, navigation stack reserve node, "
                "old index: %{public}d, index: %{public}d, removeSize: %{public}d, name: %{public}s.",
                pathIndex, index, removeSize, pathName.c_str());
            /**
             * If we call the function pushPath/pushDestination with singleton mode(
             * LaunchMode == MOVE_TO_TOP_SINGLETON/POP_TO_SINGLETON), and the top NavDestination of stack
             * is the NavDestination which we need to push(NavDestination's name == NavPathInfo's name),
             * then wee need to update the NavDestination's parameters.
             */
            navigationStack_->UpdatePathInfoIfNeeded(uiNode, arrayIndex);
            auto navDestinationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(
                NavigationGroupNode::GetNavDestinationNode(uiNode));
            if (navDestinationGroupNode && navDestinationGroupNode->GetCanReused()) {
                navigationStack_->ResetIsForceSetFlag(arrayIndex);
                navPathList.emplace_back(std::make_pair(pathName, uiNode));
                continue;
            }
        }
        uiNode = navigationStack_->GetFromCacheNode(cacheNodes, pathName);
        if (uiNode) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "find in cached node, navigation stack reserve node, "
                "index: %{public}d, removeSize: %{public}d, name: %{public}s.", index, removeSize, pathName.c_str());
            navPathList.emplace_back(std::make_pair(pathName, uiNode));
            navigationStack_->RemoveCacheNode(cacheNodes, pathName, uiNode);
            auto navDestination =
                DynamicCast<NavDestinationGroupNode>(NavigationGroupNode::GetNavDestinationNode(uiNode));
            if (navDestination) {
                navDestination->SetInCurrentStack(true);
                auto eventHub = navDestination->GetOrCreateEventHub<EventHub>();
                CHECK_NULL_VOID(eventHub);
                eventHub->SetEnabledInternal(true);
                navigationStack_->ResetIsForceSetFlag(arrayIndex);
            }
            continue;
        }
        if (isPageForceSet) {
            navPathList.emplace_back(std::make_pair(pathName, uiNode));
            continue;
        }
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "find in nowhere, navigation stack create new node, "
            "index: %{public}d, removeSize: %{public}d, name: %{public}s.", index, removeSize, pathName.c_str());
        if (!GenerateUINodeByIndex(arrayIndex, uiNode)) {
            std::string replacedName = "";
            int32_t replacedIndex = -1;
            if (navigationStack_->CheckIsReplacedDestination(arrayIndex, replacedName, replacedIndex)) {
                navigationStack_->SetRecoveryFromReplaceDestination(arrayIndex, false);
                pathNames[index] = replacedName;
                indexes[index] = replacedIndex;
                index--;
                continue;
            }
            removeSize++;
            continue;
        }
        navPathList.emplace_back(std::make_pair(pathName, uiNode));
    }
    if (isCurForceSetList) {
        GenerateLastStandardPage(navPathList);
    }
    navigationStack_->SetNavPathList(navPathList);
    navigationStack_->SetIsCurForceSetList(isCurForceSetList);
}

void NavigationPattern::RefreshNavDestination()
{
    isChanged_ = false;
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto preTopNavPath = std::move(preTopNavPath_);
    auto preLastStandardIndex = hostNode->GetLastStandardIndex();
    auto& navPathList = navigationStack_->GetAllNavDestinationNodes();
    hostNode->UpdateNavDestinationNodeWithoutMarkDirty(
        preTopNavPath.has_value() ? preTopNavPath->second : nullptr, navigationModeChange_);
    auto newTopNavPath = navigationStack_->GetTopNavPath();
#if defined(ENABLE_NAV_SPLIT_MODE)
    isBackPage_ = newTopNavPath.has_value() ?
        navigationStack_->isLastListContains(newTopNavPath->first, newTopNavPath->second) : false;
#endif
    if (topFromSingletonMoved_) {
        FireOnNewParam(newTopNavPath.has_value() ? newTopNavPath->second : nullptr);
    }
    CheckTopNavPathChange(preTopNavPath, newTopNavPath, preLastStandardIndex);

    // close keyboard
#if defined(ENABLE_STANDARD_INPUT)
    RefPtr<FrameNode> targetNode = newTopNavPath.has_value() ? AceType::DynamicCast<FrameNode>(
            NavigationGroupNode::GetNavDestinationNode(newTopNavPath->second)) :
            AceType::DynamicCast<FrameNode>(hostNode->GetNavBarOrHomeDestinationNode());
    if (isChanged_ && GetIsFocusable(targetNode)) {
        InputMethodManager::GetInstance()->CloseKeyboard();
    }
#endif

#if defined(ENABLE_NAV_SPLIT_MODE)
    navigationStack_->SetLastNavPathList(navPathList);
#endif

    /* if first navDestination is removed, the new one will be refreshed */
    if (!navPathList.empty()) {
        auto firstNavDesNode = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(navPathList.front().second));
        CHECK_NULL_VOID(firstNavDesNode);
        firstNavDesNode->MarkModifyDone();
    }

    std::string navDestinationName = newTopNavPath.has_value() ? newTopNavPath->first : "";
    pipeline->AddPredictTask([weak = WeakClaim(this), weakNode = WeakPtr<FrameNode>(hostNode),
        navDestinationName](int64_t deadline, bool canUseLongPredictTask) {
            auto navigationPattern = weak.Upgrade();
            CHECK_NULL_VOID(navigationPattern);
            auto navigationNode = weakNode.Upgrade();
            CHECK_NULL_VOID(navigationNode);
            int32_t count = 0;
            int32_t depth = 0;
            navigationNode->GetPageNodeCountAndDepth(&count, &depth);
            navigationPattern->PerformanceEventReport(count, depth, navDestinationName);
        });
}

void NavigationPattern::UpdateColorModeForNodes(
    const std::optional<std::pair<std::string, RefPtr<UINode>>>& newTopNavPath)
{
    if (SystemProperties::ConfigChangePerform()) {
        auto& allStackNode = navigationStack_->GetAllNavDestinationNodes();
        auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
        CHECK_NULL_VOID(hostNode);
        auto lastIndex = hostNode->GetLastStandardIndex();
        lastIndex = lastIndex < 0 ? 0 : lastIndex;
        auto pipelineContext = hostNode->GetContext();
        CHECK_NULL_VOID(pipelineContext);
        auto colorMode = pipelineContext->GetColorMode() == ColorMode::DARK ? true : false;
        for (auto index = lastIndex; index < static_cast<int32_t>(allStackNode.size()); index++) {
            auto node = allStackNode[index].second;
            if (node && node->CheckIsDarkMode() == colorMode) {
                continue;
            }
            pipelineContext->SetIsSystemColorChange(false);
            node->SetRerenderable(true);
            node->NotifyColorModeChange(colorMode);
        }
        if (!newTopNavPath.has_value()) {
            auto nodeBase = AceType::DynamicCast<NavDestinationNodeBase>(hostNode->GetNavBarOrHomeDestinationNode());
            CHECK_NULL_VOID(nodeBase);
            if (nodeBase->CheckIsDarkMode() == colorMode) {
                return;
            }
            pipelineContext->SetIsSystemColorChange(false);
            nodeBase->SetRerenderable(true);
            nodeBase->NotifyColorModeChange(colorMode);
        }
    }
}

void NavigationPattern::ProcessSameTopNavPath()
{
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "page is not change. don't transition");
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto currentProxy = GetTopNavigationProxy();
    if (currentProxy) {
        currentProxy->SetIsSuccess(false);
    }

    auto pipeline = hostNode->GetContextRefPtr();
    bool isForceSplitSupported = IsForceSplitSupported(pipeline);
    std::set<RefPtr<NavDestinationGroupNode>> filterNodes;
    if (isForceSplitSupported) {
        AppendFilterNodesForWillHideLifecycle(filterNodes);
    }
    hostNode->FireHideNodeChange(NavDestinationLifecycle::ON_WILL_HIDE);
    if (isForceSplitSupported) {
        NotifyPrePrimaryNodesOnWillHide(std::move(filterNodes));
        filterNodes.clear();
        AppendFilterNodesForWillShowLifecycle(filterNodes);
        NotifyCurPrimaryNodesOnWillShow(std::move(filterNodes));
    }
    NotifyDialogChange(NavDestinationLifecycle::ON_WILL_SHOW, true);
    CHECK_NULL_VOID(pipeline);
    pipeline->AddAfterLayoutTask([weakPattern = WeakClaim(this), isForceSplitSupported]() {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto hostNode = AceType::DynamicCast<NavigationGroupNode>(pattern->GetHost());
        CHECK_NULL_VOID(hostNode);
        hostNode->FireHideNodeChange(NavDestinationLifecycle::ON_HIDE);
        if (isForceSplitSupported) {
            pattern->FirePreTopPrimaryNodeInactiveIfNeeded();
            pattern->FirePrePrimaryNodesOnHide();
        }

        std::set<RefPtr<NavDestinationGroupNode>> filterNodes;
        if (isForceSplitSupported) {
            pattern->AppendFilterNodesFromHideNodes(filterNodes);
        }
        hostNode->FireHideNodeChange(NavDestinationLifecycle::ON_WILL_DISAPPEAR);
        if (isForceSplitSupported) {
            pattern->FirePrePrimaryNodesOnWillDisappear(std::move(filterNodes));
            pattern->FirePrimaryNodesOnShowAndActive();
        }

        pattern->NotifyDialogChange(NavDestinationLifecycle::ON_SHOW, true);
        hostNode->RemoveDialogDestination();

        if (isForceSplitSupported) {
            pattern->prePrimaryNodes_.clear();
            pattern->primaryNodesToBeRemoved_.clear();
            pattern->RemoveRedundantPrimaryNavDestination();
        }
    });
    ClearRecoveryList();
}

void NavigationPattern::CheckTopNavPathChange(
    const std::optional<std::pair<std::string, RefPtr<UINode>>>& preTopNavPath,
    const std::optional<std::pair<std::string, RefPtr<UINode>>>& newTopNavPath,
    int32_t preLastStandardIndex)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    if (preTopNavPath != newTopNavPath) {
        UpdateSystemBarStyleOnTopNavPathChange(newTopNavPath);
    }
    auto replaceValue = navigationStack_->GetReplaceValue();
    if (preTopNavPath == newTopNavPath) {
        ProcessSameTopNavPath();
        return;
    }

    isChanged_ = true;
    UpdateIsAnimation(preTopNavPath);
    isReplace_ = replaceValue != 0;
    if (replaceValue == 1) {
        const int32_t replaceAnimation = 2;
        navigationStack_->UpdateReplaceValue(replaceAnimation);
    }
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    // close the text selection menu before transition.
    auto selectOverlayManager = context->GetSelectOverlayManager();
    if (selectOverlayManager) {
        selectOverlayManager->ResetSelectionAndDestroySelectOverlay();
    }
    // fire onHidden and lostFocus event
    RefPtr<NavDestinationGroupNode> preTopNavDestination;
    int32_t lastPreIndex = -1;
    bool isPopPage = false;
    if (preTopNavPath.has_value()) {
        // pre page is not in the current stack
        lastPreIndex = navigationStack_->FindIndex(preTopNavPath->first, preTopNavPath->second, true);
        isPopPage |= lastPreIndex == -1;
        preTopNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(preTopNavPath->second));
    }
    if (isCurTopNewInstance_) {
        isPopPage = false;
    }
    RefPtr<NavDestinationGroupNode> newTopNavDestination;
    UpdateColorModeForNodes(newTopNavPath);
    if (newTopNavPath.has_value()) {
        newTopNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(newTopNavPath->second));
        do {
            if (!newTopNavDestination) {
                break;
            }
            if (!GetIsFocusable(newTopNavDestination)) {
                break;
            }
            auto navDestinationPattern = newTopNavDestination->GetPattern<NavDestinationPattern>();
            auto navDestinationFocusView = AceType::DynamicCast<FocusView>(navDestinationPattern);
            CHECK_NULL_VOID(navDestinationFocusView);
            if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TWELVE)) {
                navDestinationFocusView->SetIsViewRootScopeFocused(false);
            }
            navDestinationFocusView->FocusViewShow();
        } while (0);
    } else {
        // back to navBar or HomeDestination case
        auto navBarOrHomeDestNode =
            AceType::DynamicCast<NavDestinationNodeBase>(hostNode->GetNavBarOrHomeDestinationNode());
        CHECK_NULL_VOID(navBarOrHomeDestNode);
        navBarOrHomeDestNode->SetNodeFreeze(false);
        auto navigationLayoutProperty = AceType::DynamicCast<NavigationLayoutProperty>(hostNode->GetLayoutProperty());
        if (!navigationLayoutProperty->GetHideNavBarValue(false)) {
            navBarOrHomeDestNode->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
            navBarOrHomeDestNode->SetJSViewActive(true);
        }
        ProcessPageShowEvent();
        navBarOrHomeDestNode->GetOrCreateEventHub<EventHub>()->SetEnabledInternal(true);
        if (GetIsFocusable(navBarOrHomeDestNode)) {
            auto navBarOrHomeDestFocusView = navBarOrHomeDestNode->GetPattern<FocusView>();
            CHECK_NULL_VOID(navBarOrHomeDestFocusView);
            if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TWELVE)) {
                navBarOrHomeDestFocusView->SetIsViewRootScopeFocused(false);
            }
            navBarOrHomeDestFocusView->FocusViewShow();
        }
    }
    bool isShow = false;
    bool isDialog =
        (preTopNavDestination && preTopNavDestination->GetNavDestinationMode() == NavDestinationMode::DIALOG) ||
        (newTopNavDestination && newTopNavDestination->GetNavDestinationMode() == NavDestinationMode::DIALOG);
    if (preTopNavDestination && isDialog) {
        auto lastStandardIndex = hostNode->GetLastStandardIndex();
        isShow = (lastPreIndex != -1) && (lastPreIndex >= lastStandardIndex);
        hostNode->SetNeedSetInvisible(lastStandardIndex >= 0);
        if (lastStandardIndex < 0) {
            auto navBarOrHomeDestNode = AceType::DynamicCast<FrameNode>(hostNode->GetNavBarOrHomeDestinationNode());
            auto layoutProperty = navBarOrHomeDestNode->GetLayoutProperty();
            layoutProperty->UpdateVisibility(VisibleType::VISIBLE, true);
            navBarOrHomeDestNode->SetJSViewActive(true);
        }
    }
    bool disableAllAnimation = navigationStack_->GetDisableAnimation();
    bool animated = navigationStack_->GetAnimatedValue();
    TAG_LOGI(AceLogTag::ACE_NAVIGATION,
        "transition start, disableAllAnimation: %{public}d, animated: %{public}d, isPopPage: %{public}d, isDialog: "
        "%{public}d, isReplace: %{public}d, isCustomAnimation: %{public}d",
        disableAllAnimation, animated, isPopPage, isDialog, isReplace_, isCustomAnimation_);
    if (disableAllAnimation || !animated) {
        // transition without animation need to run before layout for geometryTransition.
        StartTransition(preTopNavDestination, newTopNavDestination, false, isPopPage, isShow);
        navigationStack_->UpdateAnimatedValue(true);
        hostNode->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
        return;
    }
    if (isDialog && !isCustomAnimation_) {
        bool isNeedAnimation =
            AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_THIRTEEN) ?
            true : false;
        StartTransition(preTopNavDestination, newTopNavDestination, isNeedAnimation, isPopPage, isShow);
        hostNode->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
        return;
    }

    // before the animation of navDes replacing, update the zIndex of the previous navDes node
    UpdatePreNavDesZIndex(preTopNavDestination, newTopNavDestination, preLastStandardIndex);
    // transition with animation need to run after layout task
    StartTransition(preTopNavDestination, newTopNavDestination, true, isPopPage, isShow);
    hostNode->GetLayoutProperty()->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
}

int32_t NavigationPattern::FireNavDestinationStateChange(NavDestinationLifecycle lifecycle)
{
    const auto& navDestinationNodes = navigationStack_->GetAllNavDestinationNodes();
    auto errIndex = static_cast<int32_t>(navDestinationNodes.size());
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, errIndex);
    NotifyDialogChange(lifecycle, true);
    return hostNode->GetLastStandardIndex();
}

void NavigationPattern::FireNavigationStateChange(const RefPtr<UINode>& node, bool isShow)
{
    if (isShow) {
        NavigationPattern::FireNavigationLifecycleChange(node, NavDestinationLifecycle::ON_SHOW);
        return;
    }
    NavigationPattern::FireNavigationLifecycleChange(node, NavDestinationLifecycle::ON_HIDE);
}

bool NavigationPattern::CheckParentDestinationIsOnhide(const RefPtr<NavDestinationGroupNode>& destinationNode)
{
    CHECK_NULL_RETURN(destinationNode, false);
    auto destinationNodePattern = destinationNode->GetPattern<NavDestinationPattern>();
    CHECK_NULL_RETURN(destinationNodePattern, false);
    return !destinationNodePattern->GetIsOnShow();
}

bool NavigationPattern::CheckParentDestinationInactive()
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, false);
    auto parentDestination = hostNode->GetParentDestinationNode().Upgrade();
    CHECK_NULL_RETURN(parentDestination, false);
    auto pattern = parentDestination->GetPattern<NavDestinationPattern>();
    CHECK_NULL_RETURN(pattern, false);
    return !pattern->IsActive();
}

bool NavigationPattern::CheckDestinationIsPush(const RefPtr<NavDestinationGroupNode>& destinationNode)
{
    CHECK_NULL_RETURN(destinationNode, false);
    return destinationNode->GetIndex() != -1 || destinationNode->GetNavDestinationCustomNode();
}

bool NavigationPattern::CheckIfNeedHideOrShowPrimaryNodes(
    const RefPtr<NavigationPattern>& pattern, int32_t lastStandardIndex)
{
    CHECK_NULL_RETURN(pattern, false);
    if (!pattern->GetHomeNode()) {
        return false;
    }
    auto primaryNodes = pattern->GetPrimaryNodes();
    if (primaryNodes.empty()) {
        return false;
    }
    auto firstNode = primaryNodes[0].Upgrade();
    CHECK_NULL_RETURN(firstNode, false);
    auto homeIndex = firstNode->GetIndex();
    if (homeIndex >= lastStandardIndex) {
        return false;
    }
    return true;
}

void NavigationPattern::FireNavigationInner(const RefPtr<UINode>& node, bool isOnShow)
{
    CHECK_NULL_VOID(node);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(node);
    if (!navigationNode) {
        NavigationPattern::FireNavigationChange(node, isOnShow, false);
        return;
    }
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    CHECK_NULL_VOID(navigationPattern->navigationStack_);
    const auto& navDestinationNodes = navigationPattern->navigationStack_->GetAllNavDestinationNodes();
    auto lastStandardIndex = navigationNode->GetLastStandardIndex();
    int32_t standardIndex = lastStandardIndex >= 0 ? lastStandardIndex : 0;
    int32_t start = standardIndex;
    int32_t end = navigationPattern->navigationStack_->Size();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    bool needHideOrShowPrimaryNodes = CheckIfNeedHideOrShowPrimaryNodes(navigationPattern, lastStandardIndex);

    if (isOnShow) {
        if (overlayManager && overlayManager->HasModalPage()) {
            return;
        }
        if (needHideOrShowPrimaryNodes) {
            navigationPattern->FirePrimaryNodesLifecycle(NavDestinationLifecycle::ON_SHOW);
        }
        navigationPattern->FireHomeDestinationLifeCycleIfNeeded(
            NavDestinationLifecycle::ON_SHOW, false, NavDestinationActiveReason::APP_STATE_CHANGE);
        navigationPattern->FireHomeDestinationLifeCycleIfNeeded(
            NavDestinationLifecycle::ON_ACTIVE, false, NavDestinationActiveReason::APP_STATE_CHANGE);
        for (int32_t index = start; index < end; index++) {
            const auto& curPath = navDestinationNodes[index];
            auto curDestination = AceType::DynamicCast<NavDestinationGroupNode>(
                navigationNode->GetNavDestinationNode(curPath.second));
            if (!curDestination || !curDestination->GetLayoutProperty()) {
                continue;
            }
            auto navDestinationPattern = curDestination->GetPattern<NavDestinationPattern>();
            CHECK_NULL_VOID(navDestinationPattern);
            auto property = curDestination->GetLayoutProperty();
            if (property->GetVisibilityValue(VisibleType::VISIBLE) != VisibleType::VISIBLE ||
                !curDestination->IsActive() || navDestinationPattern->GetIsOnShow() == isOnShow) {
                continue;
            }
            auto eventHub = curDestination->GetOrCreateEventHub<NavDestinationEventHub>();
            CHECK_NULL_VOID(eventHub);
            auto param = Recorder::EventRecorder::Get().IsPageParamRecordEnable() ?
                navigationPattern->navigationStack_->GetRouteParam() : "";
            eventHub->FireOnShownEvent(navDestinationPattern->GetName(), param);
            navDestinationPattern->SetIsOnShow(true);
            NavigationPattern::FireNavigationChange(curDestination, true, false);
            NavigationPattern::NotifyPerfMonitorPageMsg(navDestinationPattern->GetName());
        }
        return;
    }
    for (int32_t index = end - 1; index >= 0 && index >= start; index--) {
        const auto& curPath = navDestinationNodes[index];
        auto curDestination = AceType::DynamicCast<NavDestinationGroupNode>(
            navigationNode->GetNavDestinationNode(curPath.second));
        if (!curDestination || !curDestination->GetLayoutProperty()) {
            continue;
        }
        auto navDestinationPattern = curDestination->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(navDestinationPattern);
        auto property = curDestination->GetLayoutProperty();
        if (property->GetVisibilityValue(VisibleType::VISIBLE) != VisibleType::VISIBLE ||
            !curDestination->IsActive() || navDestinationPattern->GetIsOnShow() == isOnShow) {
            continue;
        }
        auto eventHub = curDestination->GetOrCreateEventHub<NavDestinationEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireOnHiddenEvent(navDestinationPattern->GetName());
        navDestinationPattern->SetIsOnShow(false);
        NavigationPattern::FireNavigationChange(curDestination, false, false);
    }
    navigationPattern->FireHomeDestinationLifeCycleIfNeeded(
        NavDestinationLifecycle::ON_INACTIVE, false, NavDestinationActiveReason::APP_STATE_CHANGE);
    navigationPattern->FireHomeDestinationLifeCycleIfNeeded(
        NavDestinationLifecycle::ON_HIDE, false, NavDestinationActiveReason::APP_STATE_CHANGE);
    if (needHideOrShowPrimaryNodes) {
        navigationPattern->FirePrimaryNodesLifecycle(NavDestinationLifecycle::ON_HIDE);
    }
}

void NavigationPattern::FireNavigationChange(const RefPtr<UINode>& node, bool isOnShow, bool isFirst)
{
    CHECK_NULL_VOID(node);
    if (isFirst) {
        FireNavigationInner(node, isOnShow);
        return;
    }
    const auto children = node->GetChildren(true);
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        auto& child = *iter;
        FireNavigationInner(child, isOnShow);
    }
}

void NavigationPattern::FireNavigationLifecycleChange(const RefPtr<UINode>& node, NavDestinationLifecycle lifecycle)
{
    CHECK_NULL_VOID(node);
    const auto children = node->GetChildren(true);
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        auto& child = *iter;
        auto navigation = AceType::DynamicCast<NavigationGroupNode>(child);
        if (navigation) {
            auto destinationNode = navigation->GetParentDestinationNode().Upgrade();
            if ((lifecycle == NavDestinationLifecycle::ON_SHOW) && CheckParentDestinationIsOnhide(destinationNode) &&
                CheckDestinationIsPush(destinationNode)) {
                TAG_LOGI(AceLogTag::ACE_NAVIGATION, "navigation parent is onhide");
                continue;
            }
            auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigation->GetPattern());
            CHECK_NULL_VOID(navigationPattern);
            navigationPattern->FireNavDestinationStateChange(lifecycle);
        } else {
            NavigationPattern::FireNavigationLifecycleChange(child, lifecycle);
        }
    }
}

void NavigationPattern::NotifyPageHide(const std::string& pageName)
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pageUrlChecker = container->GetPageUrlChecker();
    CHECK_NULL_VOID(pageUrlChecker);
    pageUrlChecker->NotifyPageHide(pageName);
}

void NavigationPattern::NotifyPageShow(const std::string& pageName)
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pageUrlChecker = container->GetPageUrlChecker();
    CHECK_NULL_VOID(pageUrlChecker);
    pageUrlChecker->NotifyPageShow(pageName);
    if (PerfMonitor::GetPerfMonitor() != nullptr) {
        PerfMonitor::GetPerfMonitor()->SetPageName(pageName);
    }
}

void NavigationPattern::ProcessPageShowEvent()
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto context = hostNode->GetContext();
    CHECK_NULL_VOID(context);
    auto stageManager = context->GetStageManager();
    if (stageManager) {
        RefPtr<FrameNode> pageNode = stageManager->GetLastPage();
        CHECK_NULL_VOID(pageNode);
        auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
        CHECK_NULL_VOID(pagePattern);
        auto pageInfo = pagePattern->GetPageInfo();
        CHECK_NULL_VOID(pageInfo);
        NotifyPageShow(pageInfo->GetPageUrl());
    }
}

void NavigationPattern::ReplaceAnimation(const RefPtr<NavDestinationGroupNode>& preTopNavDestination,
    const RefPtr<NavDestinationGroupNode>& newTopNavDestination)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(navigationNode);
    auto navBarOrHomeDestNode =
        AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarOrHomeDestinationNode());
    CHECK_NULL_VOID(navBarOrHomeDestNode);
    bool preUseCustomTransition = TriggerNavDestinationTransition(
        (preTopNavDestination ? preTopNavDestination :
        AceType::DynamicCast<NavDestinationGroupNode>(navBarOrHomeDestNode)),
        NavigationOperation::REPLACE, false) != INVALID_ANIMATION_ID;
    TriggerNavDestinationTransition(newTopNavDestination, NavigationOperation::REPLACE, true);
    if (newTopNavDestination && preTopNavDestination && !preUseCustomTransition) {
        navigationNode->DealNavigationExit(preTopNavDestination, false, false);
    } else if (newTopNavDestination && navigationMode_ == NavigationMode::STACK) {
        navigationNode->DealNavigationExit(navBarOrHomeDestNode, true, false);
    }
    navigationNode->RemoveDialogDestination();
    auto id = navigationNode->GetTopDestination() ? navigationNode->GetTopDestination()->GetAccessibilityId() : -1;
    navigationNode->OnAccessibilityEvent(
        AccessibilityEventType::PAGE_CHANGE, id, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_INVALID);
    navigationStack_->UpdateReplaceValue(0);

    auto context = navigationNode->GetContext();
    CHECK_NULL_VOID(context);
    OnStartOneTransitionAnimation();
    context->AddAfterLayoutTask([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnFinishOneTransitionAnimation();
    });
}

void NavigationPattern::TransitionWithOutAnimation(RefPtr<NavDestinationGroupNode> preTopNavDestination,
    RefPtr<NavDestinationGroupNode> newTopNavDestination, bool isPopPage, bool needVisible)
{
    ClearRecoveryList();
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(navigationNode);
    auto navBarOrHomeDestNode =
        AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarOrHomeDestinationNode());
    CHECK_NULL_VOID(navBarOrHomeDestNode);

    // replace
    auto replaceVal = navigationStack_->GetReplaceValue();
    if (replaceVal != 0) {
        ReplaceAnimation(preTopNavDestination, newTopNavDestination);
        return;
    }

    auto context = navigationNode->GetContext();
    CHECK_NULL_VOID(context);
    OnStartOneTransitionAnimation();
    context->AddAfterLayoutTask([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnFinishOneTransitionAnimation();
    });

    // navDestination push/pop navDestination
    if (newTopNavDestination && preTopNavDestination) {
        if (isPopPage) {
            newTopNavDestination->SetTransitionType(PageTransitionType::ENTER_POP);
            preTopNavDestination->CleanContent(false, true);
            auto parent = preTopNavDestination->GetParent();
            CHECK_NULL_VOID(parent);
            parent->RemoveChild(preTopNavDestination, true);
            parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        } else {
            preTopNavDestination->GetRenderContext()->RemoveClipWithRRect();
            preTopNavDestination->SetTransitionType(PageTransitionType::EXIT_PUSH);
            newTopNavDestination->SetTransitionType(PageTransitionType::ENTER_PUSH);
            if (forceSplitSuccess_ &&
                (preTopNavDestination->IsShowInPrimaryPartition() ||
                newTopNavDestination->IsShowInPrimaryPartition())) {
                needVisible = true;
            }
            DealTransitionVisibility(preTopNavDestination, needVisible, false);
            if (preTopNavDestination->NeedRemoveInPush()) {
                preTopNavDestination->CleanContent(false, true);
                auto parent = preTopNavDestination->GetParent();
                CHECK_NULL_VOID(parent);
                parent->RemoveChild(preTopNavDestination, true);
                parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            }
        }
        navigationNode->RemoveDialogDestination();
        auto id = navigationNode->GetTopDestination() ? navigationNode->GetTopDestination()->GetAccessibilityId() : -1;
        navigationNode->OnAccessibilityEvent(
            AccessibilityEventType::PAGE_CHANGE, id, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_INVALID);
        return;
    }

    // navBar or HomeDestination push navDestination
    if (newTopNavDestination && newTopNavDestination->GetNavDestinationMode() == NavDestinationMode::STANDARD) {
        newTopNavDestination->SetTransitionType(PageTransitionType::ENTER_PUSH);
        // current mode is stack, set navBar or HomeDestination invisible
        if (navigationMode_ == NavigationMode::STACK && navBarOrHomeDestNode) {
            navBarOrHomeDestNode->SetTransitionType(PageTransitionType::EXIT_PUSH);
            DealTransitionVisibility(navBarOrHomeDestNode, false, true);
        }
        // if current mode is auto, need set navBar need set invisible true
        navigationNode->SetNeedSetInvisible(true);
    }

    // navDestination pop to navBar or HomeDestination
    if (preTopNavDestination) {
        preTopNavDestination->CleanContent(false, true);
        auto parent = preTopNavDestination->GetParent();
        CHECK_NULL_VOID(parent);
        parent->RemoveChild(preTopNavDestination, true);
        navigationNode->SetNeedSetInvisible(false);
        if (navBarOrHomeDestNode) {
            navBarOrHomeDestNode->SetTransitionType(PageTransitionType::ENTER_POP);
        }
        parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    navigationNode->RemoveDialogDestination();
    auto id = navigationNode->GetTopDestination() ? navigationNode->GetTopDestination()->GetAccessibilityId() : -1;
    navigationNode->OnAccessibilityEvent(
        AccessibilityEventType::PAGE_CHANGE, id, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_INVALID);
}

void NavigationPattern::TransitionWithAnimation(RefPtr<NavDestinationGroupNode> preTopNavDestination,
    RefPtr<NavDestinationGroupNode> newTopNavDestination, bool isPopPage, bool isNeedVisible)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(navigationNode);
    auto layoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetHideNavBarValue(false) && (!newTopNavDestination || !preTopNavDestination)) {
        // hide navBarNode and need to do animation with navBarNode
        if (preTopNavDestination) {
            // remove preTopNavDestination node in pop
            auto parent = preTopNavDestination->GetParent();
            CHECK_NULL_VOID(parent);
            preTopNavDestination->CleanContent();
            parent->RemoveChild(preTopNavDestination);
            parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
        navigationNode->RemoveDialogDestination();
        ClearRecoveryList();
        OnStartOneTransitionAnimation();
        OnFinishOneTransitionAnimation();
        return;
    }
    if (isCustomAnimation_ && TriggerCustomAnimation(preTopNavDestination, newTopNavDestination, isPopPage)) {
        auto operation = NavigationOperation::REPLACE;
        if (navigationStack_->GetReplaceValue() == 0) {
            operation = isPopPage ? NavigationOperation::POP : NavigationOperation::PUSH;
        }
        auto homeDestination =
            AceType::DynamicCast<NavDestinationGroupNode>(navigationNode->GetNavBarOrHomeDestinationNode());
        if (!preTopNavDestination) {
            preTopNavDestination = homeDestination;
        } else if (!newTopNavDestination) {
            newTopNavDestination = homeDestination;
        }
        TriggerNavDestinationTransition(preTopNavDestination, operation, false);
        TriggerNavDestinationTransition(newTopNavDestination, operation, true);
        return;
    }
    StartDefaultAnimation(preTopNavDestination, newTopNavDestination, isPopPage, isNeedVisible);
}

void NavigationPattern::DialogAnimation(const RefPtr<NavDestinationGroupNode>& preTopNavDestination,
    const RefPtr<NavDestinationGroupNode>& newTopNavDestination, bool isPopPage, bool isNeedVisible)
{
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_THIRTEEN)) {
        TransitionWithDialogAnimation(preTopNavDestination, newTopNavDestination, isPopPage);
    } else {
        TransitionWithOutAnimation(preTopNavDestination, newTopNavDestination, isPopPage, isNeedVisible);
    }
}

void NavigationPattern::StartDefaultAnimation(const RefPtr<NavDestinationGroupNode>& preTopNavDestination,
    const RefPtr<NavDestinationGroupNode>& newTopNavDestination, bool isPopPage, bool isNeedVisible)
{
    auto currentProxy = GetTopNavigationProxy();
    if (currentProxy) {
        currentProxy->SetIsFinished(true);
    }
    ClearRecoveryList();
    bool isPreDialog = preTopNavDestination &&
        preTopNavDestination->GetNavDestinationMode() == NavDestinationMode::DIALOG;
    bool isNewDialog = newTopNavDestination &&
        newTopNavDestination->GetNavDestinationMode() == NavDestinationMode::DIALOG;
    if (isPreDialog || isNewDialog) {
        DialogAnimation(preTopNavDestination, newTopNavDestination, isPopPage, isNeedVisible);
        return;
    }
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(navigationNode);
    auto navBarOrHomeDestNode =
        AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarOrHomeDestinationNode());
    CHECK_NULL_VOID(navBarOrHomeDestNode);
    // replace
    auto replaceValue = navigationStack_->GetReplaceValue();
    if (replaceValue != 0) {
        if (newTopNavDestination && preTopNavDestination) {
            navigationNode->TransitionWithReplace(preTopNavDestination, newTopNavDestination, false);
        } else if (newTopNavDestination && navigationMode_ == NavigationMode::STACK) {
            navigationNode->TransitionWithReplace(navBarOrHomeDestNode, newTopNavDestination, true);
        }
        navigationStack_->UpdateReplaceValue(0);
        return;
    }
    // navDestination push/pop navDestination
    if (newTopNavDestination && preTopNavDestination) {
        if (isPopPage) {
            navigationNode->TransitionWithPop(preTopNavDestination, newTopNavDestination);
        } else {
            navigationNode->TransitionWithPush(preTopNavDestination, newTopNavDestination);
        }
        return;
    }
    // navBar or HomeDestination push navDestination
    if (newTopNavDestination) {
        navigationNode->TransitionWithPush(navBarOrHomeDestNode, newTopNavDestination, true);
        return;
    }
    // navDestination pop to navBar or HomeDestination
    if (preTopNavDestination) {
        if (navigationMode_ == NavigationMode::SPLIT) {
            navigationNode->TransitionWithPop(preTopNavDestination, nullptr);
        }
        if (navigationMode_ == NavigationMode::STACK) {
            navigationNode->TransitionWithPop(preTopNavDestination, navBarOrHomeDestNode, true);
        }
    }
}

void NavigationPattern::OnVisibleChange(bool isVisible)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto eventHub = hostNode->GetOrCreateEventHub<NavigationEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireNavBarStateChangeEvent(isVisible);
}

void NavigationPattern::OnNavBarStateChange(bool modeChange)
{
    auto layoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto visibilityValue = layoutProperty->GetVisibilityValue(VisibleType::VISIBLE);
    if (visibilityValue != VisibleType::VISIBLE) {
        return;
    }

    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto eventHub = hostNode->GetOrCreateEventHub<NavigationEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto currentNavigationMode = GetNavigationMode();

    auto lastStandardIndex = hostNode->GetLastStandardIndex();
    if (modeChange) {
        bool navbarIsHidden = (currentNavigationMode == NavigationMode::STACK && lastStandardIndex >= 0) ||
                              layoutProperty->GetHideNavBar().value_or(false);
        eventHub->FireNavBarStateChangeEvent(!navbarIsHidden);
        SetNavBarVisibilityChange(false);
        return;
    }

    if (GetNavBarVisibilityChange()) {
        if (!layoutProperty->GetHideNavBarValue(false)) {
            eventHub->FireNavBarStateChangeEvent(true);
        } else {
            eventHub->FireNavBarStateChangeEvent(false);
        }
        SetNavBarVisibilityChange(false);
        return;
    }

    if (currentNavigationMode == NavigationMode::STACK) {
        bool navbarIsHidden = (lastStandardIndex >= 0) || layoutProperty->GetHideNavBar().value_or(false);
        eventHub->FireNavBarStateChangeEvent(!navbarIsHidden);
    }
}

void NavigationPattern::OnNavigationModeChange(bool modeChange)
{
    if (!modeChange) {
        return;
    }
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto eventHub = hostNode->GetOrCreateEventHub<NavigationEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireNavigationModeChangeEvent(navigationMode_);
    // fire navigation stack navigation mode change event
    navigationStack_->FireNavigationModeChange(navigationMode_);
}

bool NavigationPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, false);
    UpdateIsFullPageNavigation(hostNode);
    if (navigationModeChange_) {
        if (NavigationMode::STACK == navigationMode_) {
            // Set focus on navDestination when mode changes to STACK
            RefreshFocusToDestination();
        }
        AbortAnimation(hostNode);
    }
    auto context = PipelineContext::GetCurrentContext();
    if (context) {
        context->GetTaskExecutor()->PostTask(
            [weak = WeakClaim(this), navigationStackWeak = WeakPtr<NavigationStack>(navigationStack_),
                navigationWeak = WeakPtr<NavigationGroupNode>(hostNode)] {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                auto navigationGroupNode = navigationWeak.Upgrade();
                CHECK_NULL_VOID(navigationGroupNode);
                auto navigationLayoutProperty =
                    AceType::DynamicCast<NavigationLayoutProperty>(navigationGroupNode->GetLayoutProperty());
                CHECK_NULL_VOID(navigationLayoutProperty);
                auto navigationStack = navigationStackWeak.Upgrade();
                CHECK_NULL_VOID(navigationStack);
                auto curTopNavPath = navigationStack->GetTopNavPath();
                if (curTopNavPath.has_value()) {
                    // considering backButton visibility
                    auto curTopNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(
                        NavigationGroupNode::GetNavDestinationNode(curTopNavPath->second));
                    pattern->UpdateContextRect(curTopNavDestination, navigationGroupNode);
                }
                // considering navBar/HomeDestination visibility
                auto navBarOrHomeDestNode =
                    AceType::DynamicCast<NavDestinationNodeBase>(navigationGroupNode->GetNavBarOrHomeDestinationNode());
                CHECK_NULL_VOID(navBarOrHomeDestNode);
                auto navBarOrHomeDestLayoutProperty =
                    navBarOrHomeDestNode->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
                CHECK_NULL_VOID(navBarOrHomeDestLayoutProperty);
                auto lastStandardIndex = navigationGroupNode->GetLastStandardIndex();
                bool isSetInvisible = navigationGroupNode->GetNeedSetInvisible() && navigationStack->Size() != 0 &&
                    lastStandardIndex >= 0;
                if (navigationLayoutProperty->GetHideNavBar().value_or(false) ||
                    (pattern->GetNavigationMode() == NavigationMode::STACK && isSetInvisible)) {
                    navBarOrHomeDestLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
                    navBarOrHomeDestNode->SetJSViewActive(false);
                } else {
                    navBarOrHomeDestNode->GetRenderContext()->UpdateOpacity(1.0f);
                    navBarOrHomeDestLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
                    navBarOrHomeDestNode->SetJSViewActive(true);
                }
                auto navigationContentNode = AceType::DynamicCast<FrameNode>(navigationGroupNode->GetContentNode());
                CHECK_NULL_VOID(navigationContentNode);
                auto navDestinationNode =
                    AceType::DynamicCast<NavDestinationGroupNode>(navigationContentNode->GetLastChild());
                CHECK_NULL_VOID(navDestinationNode);
                auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
                auto navDestinationFocusHub = navDestinationNode->GetFocusHub();
                CHECK_NULL_VOID(navDestinationFocusHub);
                auto defaultFocusHub = navDestinationFocusHub->GetChildFocusNodeByType(FocusNodeType::DEFAULT);
                if (!defaultFocusHub && navDestinationNode->GetChildren(true).size() <= EMPTY_DESTINATION_CHILD_SIZE &&
                    navDestinationPattern->GetBackButtonState()) {
                    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
                    CHECK_NULL_VOID(titleBarNode);
                    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
                    backButtonNode->GetOrCreateFocusHub()->SetIsDefaultFocus(true);
                    auto navigation = pattern->GetHost();
                    CHECK_NULL_VOID(navigation);
                    auto navigationFocusHub = navigation->GetFocusHub();
                    CHECK_NULL_VOID(navigationFocusHub);
                    auto navDestinationFocusView = navDestinationNode->GetPattern<FocusView>();
                    if (navigationFocusHub->IsCurrentFocus() && navDestinationFocusView) {
                        if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TWELVE)) {
                            navDestinationFocusView->SetIsViewRootScopeFocused(false);
                        }
                        navDestinationFocusView->FocusViewShow();
                    }
                }
            },
            TaskExecutor::TaskType::UI, "ArkUINavigationDirtyLayoutWrapperSwap",
            TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
    }
    auto navigationLayoutProperty = AceType::DynamicCast<NavigationLayoutProperty>(hostNode->GetLayoutProperty());
    CHECK_NULL_RETURN(navigationLayoutProperty, false);
    UpdateTitleModeChangeEventHub(hostNode);
    FireNavBarWidthChangeEvent(dirty);
    AddDragBarHotZoneRect();
    AddDividerHotZoneRect();
    ifNeedInit_ = false;
    return false;
}

void NavigationPattern::AbortAnimation(RefPtr<NavigationGroupNode>& hostNode)
{
    TAG_LOGD(AceLogTag::ACE_NAVIGATION, "Aborting navigation animations");
    if (runningTransitionCount_ > 0) {
        isTransitionAnimationAborted_ = true;
    }
    if (!hostNode->GetPushAnimations().empty()) {
        auto pushAnimations = hostNode->GetPushAnimations();
        for (const auto& animation : pushAnimations) {
            if (animation) {
                AnimationUtils::StopAnimation(animation);
            }
        }
    }
    if (!hostNode->GetPopAnimations().empty()) {
        auto popAnimations = hostNode->GetPopAnimations();
        for (const auto& animation : popAnimations) {
            if (animation) {
                AnimationUtils::StopAnimation(animation);
            }
        }
    }
    hostNode->CleanPushAnimations();
    hostNode->CleanPopAnimations();
}

void NavigationPattern::UpdateContextRect(
    const RefPtr<NavDestinationGroupNode>& curDestination, const RefPtr<NavigationGroupNode>& hostNode)
{
    CHECK_NULL_VOID(curDestination);
    CHECK_NULL_VOID(hostNode);
    auto navBarOrHomeDestNode =
        AceType::DynamicCast<NavDestinationNodeBase>(hostNode->GetNavBarOrHomeDestinationNode());
    CHECK_NULL_VOID(navBarOrHomeDestNode);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(hostNode->GetPattern());
    CHECK_NULL_VOID(navigationPattern);

    if (navigationPattern->GetNavigationMode() == NavigationMode::STACK) {
        curDestination->GetRenderContext()->SetActualForegroundColor(Color::TRANSPARENT);
        return;
    }
    auto navigationLayoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(navigationLayoutProperty);
    auto navBarOrHomeDestProperty = navBarOrHomeDestNode->GetLayoutProperty();
    navBarOrHomeDestProperty->UpdateVisibility(VisibleType::VISIBLE);
    navBarOrHomeDestNode->SetJSViewActive(true);
    if (!curDestination->IsOnAnimation()) {
        curDestination->GetRenderContext()->UpdateTranslateInXY(OffsetF { 0.0f, 0.0f });
        curDestination->GetRenderContext()->SetActualForegroundColor(Color::TRANSPARENT);
        navBarOrHomeDestNode->GetOrCreateEventHub<EventHub>()->SetEnabledInternal(true);
        auto titleBarNode = DynamicCast<TitleBarNode>(navBarOrHomeDestNode->GetTitleBarNode());
        CHECK_NULL_VOID(titleBarNode);
        auto titleNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle());
        CHECK_NULL_VOID(titleNode);
        titleNode->GetRenderContext()->UpdateTranslateInXY(OffsetF { 0.0f, 0.0f });
    }
}

bool NavigationPattern::UpdateTitleModeChangeEventHub(const RefPtr<NavigationGroupNode>& hostNode)
{
    // HomeDestination's title couldn't change titleMode.
    auto navBarNode = AceType::DynamicCast<NavBarNode>(hostNode->GetNavBarNode());
    CHECK_NULL_RETURN(navBarNode, false);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_RETURN(titleBarNode, false);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_RETURN(titleBarLayoutProperty, false);
    auto eventHub = hostNode->GetOrCreateEventHub<NavigationEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    if (titleBarLayoutProperty->GetTitleModeValue(NavigationTitleMode::FREE) == NavigationTitleMode::FREE) {
        auto titleBarPattern = AceType::DynamicCast<TitleBarPattern>(titleBarNode->GetPattern());
        CHECK_NULL_RETURN(titleBarPattern, false);
        NavigationTitleMode titleMode = titleBarPattern->GetNavigationTitleMode();
        if (titleMode != NavigationTitleMode::FREE && titleMode_ != titleMode) {
            NavigationTitleModeChangeEvent navigationTitleModeChange(titleMode == NavigationTitleMode::MINI);
            eventHub->FireChangeEvent(&navigationTitleModeChange);
            titleMode_ = titleMode;
        }
    }
    return true;
}

void NavigationPattern::FireNavBarWidthChangeEvent(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    auto frameWidth = frameSize.Width();
    auto navigationLayoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(navigationLayoutProperty);
    auto userSetDimensionUnit = navigationLayoutProperty->GetNavBarWidthValue(DEFAULT_NAV_BAR_WIDTH).Unit();
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutAlgorithm = layoutWrapper->GetLayoutAlgorithm();
    CHECK_NULL_VOID(layoutAlgorithm);
    auto navigationLayoutAlgorithm = AceType::DynamicCast<NavigationLayoutAlgorithm>(
        layoutAlgorithm->GetLayoutAlgorithm());
    CHECK_NULL_VOID(navigationLayoutAlgorithm);
    auto realBavBarWidth = navigationLayoutAlgorithm->GetRealNavBarWidth();
    auto realNavBarWidthDimension = Dimension(realBavBarWidth, DimensionUnit::PX);
    Dimension usrSetUnitWidth = Dimension(0.0, userSetDimensionUnit);
    if (!NearZero(frameWidth)) {
        usrSetUnitWidth = DimensionUnit::PERCENT == userSetDimensionUnit ?
            Dimension(realBavBarWidth / frameWidth, DimensionUnit::PERCENT) :
            Dimension(realNavBarWidthDimension.GetNativeValue(userSetDimensionUnit), userSetDimensionUnit);
    }
    auto dividerWidth = static_cast<float>(DIVIDER_WIDTH.ConvertToPx());
    initNavBarWidth_ = realBavBarWidth;
    SetNavigationWidthToolBarManager(realBavBarWidth, frameWidth - realBavBarWidth - dividerWidth, dividerWidth);
    auto eventHub = host->GetEventHub<NavigationEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireNavBarWidthChangeEvent(usrSetUnitWidth);
}

int32_t NavigationPattern::GenerateUINodeFromRecovery(int32_t lastStandardIndex, NavPathList& navPathList)
{
    /**
     * In case several pages at the top of stack are dialog pages.
     * We need to recovery node until a standard page created.
     * And the creation process should be bottom-up to satisfy the order of life-cycle.
     */
    int32_t jsStackSize = static_cast<int32_t>(navPathList.size());
    int32_t removeSize = 0;
    for (int32_t index = lastStandardIndex; index < jsStackSize; ++ index) {
        if (navPathList[index].second || !navigationStack_->IsFromRecovery(index)) {
            continue;
        }
        if (!GenerateUINodeByIndex(index - removeSize, navPathList[index].second)) {
            removeSize++;
            continue;
        }
        navigationStack_->SetFromRecovery(index, false);
        auto navdestination = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(navPathList[index].second));
        navdestination->SetNeedAppearFromRecovery(true);
    }
    return removeSize;
}

bool NavigationPattern::GenerateUINodeByIndex(int32_t index, RefPtr<UINode>& node)
{
    auto host = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    do {
        if (parentNode_.Upgrade() || !host) {
            break;
        }
        auto context = host->GetContext();
        // Avoid the loading problem of atomicservice on the home page
        if ((context && !context->GetInstallationFree()) || !context) {
            break;
        }
        RefPtr<UINode> parentCustomNode;
        auto curNode = host->GetParent();
        while (curNode) {
            auto curTag = curNode->GetTag();
            if (curTag == V2::JS_VIEW_ETS_TAG) {
                parentCustomNode = curNode;
                break;
            }
            curNode = curNode->GetParent();
        }
        auto pattern = host->GetPattern<NavigationPattern>();
        if (pattern && parentCustomNode) {
            pattern->SetParentCustomNode(parentCustomNode);
        }
    } while (false);
    bool isCreate = navigationStack_->CreateNodeByIndex(index, parentNode_, node);
    if (node) {
        node->SetFreeze(true, true);
    }
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(
        NavigationGroupNode::GetNavDestinationNode(node));
    CHECK_NULL_RETURN(navDestinationNode, isCreate);
    auto onStart = [weakPattern = WeakClaim(this)]() {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnStartOneTransitionAnimation();
    };
    auto onFinish = [weakPattern = WeakClaim(this)]() {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnFinishOneTransitionAnimation();
    };
    navDestinationNode->SetOnStartTransitionAnimationCallback(std::move(onStart));
    navDestinationNode->SetOnFinishTransitionAnimationCallback(std::move(onFinish));
    // set navigation id
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    auto navDestinationPattern = AceType::DynamicCast<NavDestinationPattern>(navDestinationNode->GetPattern());
    if (navigationNode && navDestinationPattern) {
        navDestinationPattern->SetNavigationNode(navigationNode);
        navDestinationPattern->SetNavigationId(navigationNode->GetInspectorId().value_or(""));
    }
    auto eventHub = navDestinationNode->GetOrCreateEventHub<NavDestinationEventHub>();
    CHECK_NULL_RETURN(eventHub, isCreate);
    eventHub->FireOnWillAppear();
    return isCreate;
}

void NavigationPattern::InitDividerMouseEvent(const RefPtr<InputEventHub>& inputHub)
{
    CHECK_NULL_VOID(inputHub);
    CHECK_NULL_VOID(!hoverEvent_);

    auto hoverTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->OnHover(isHover);
        }
    };
    hoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverTask));
    inputHub->AddOnHoverEvent(hoverEvent_);
}

void NavigationPattern::HandleDragStart()
{
    preNavBarWidth_ = realNavBarWidth_;
    if (!isDividerDraggable_) {
        return;
    }
    isInDividerDrag_ = true;
    if (!enableDragBar_) {
        SetMouseStyle(MouseFormat::RESIZE_LEFT_RIGHT);
    }
}

void NavigationPattern::HandleDragUpdate(float xOffset)
{
    auto navigationLayoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(navigationLayoutProperty);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameWidth = geometryNode->GetFrameSize().Width();
    auto constraint = navigationLayoutProperty->GetLayoutConstraint();
    auto parentSize = CreateIdealSize(constraint.value(), Axis::HORIZONTAL, MeasureType::MATCH_PARENT);
    float minNavBarWidthPx = minNavBarWidthValue_.ConvertToPxWithSize(parentSize.Width().value_or(0.0f));
    float maxNavBarWidthPx = maxNavBarWidthValue_.ConvertToPxWithSize(parentSize.Width().value_or(0.0f));
    float minContentWidthPx = minContentWidthValue_.ConvertToPxWithSize(parentSize.Width().value_or(0.0f));
    auto dividerWidth = static_cast<float>(DIVIDER_WIDTH.ConvertToPx());

    auto navigationPosition = navigationLayoutProperty->GetNavBarPosition().value_or(NavBarPosition::START);
    bool isNavBarStart = navigationPosition == NavBarPosition::START;
    auto navBarLine = isRightToLeft_ ? preNavBarWidth_ + (isNavBarStart ? -xOffset : xOffset)
                                     : preNavBarWidth_ + (isNavBarStart ? xOffset : -xOffset);

    if (maxNavBarWidthPx + dividerWidth + minContentWidthPx > frameWidth) {
        maxNavBarWidthPx = frameWidth - minContentWidthPx - dividerWidth;
    }
    navBarLine = std::min(navBarLine, maxNavBarWidthPx);

    if (userSetMinContentFlag_ && !userSetNavBarRangeFlag_) {
        if (minContentWidthPx >= frameWidth) {
            realNavBarWidth_ = 0.0f;
        } else if (navBarLine + dividerWidth + minContentWidthPx <= frameWidth) {
            realNavBarWidth_ = navBarLine;
        } else {
            realNavBarWidth_ = frameWidth - minContentWidthPx - dividerWidth;
        }
    } else {
        realDividerWidth_ = dividerWidth;
        float remainingSpace = frameWidth - navBarLine - dividerWidth;
        if (remainingSpace >= minContentWidthPx) {
            realNavBarWidth_ = navBarLine;
        } else if (remainingSpace < minContentWidthPx && navBarLine > minNavBarWidthPx) {
            realNavBarWidth_ = frameWidth - minContentWidthPx - dividerWidth;
        } else {
            realNavBarWidth_ = minNavBarWidthPx;
        }
    }
    realNavBarWidth_ = std::max(std::min(std::min(realNavBarWidth_, frameWidth), maxNavBarWidthPx), minNavBarWidthPx);
    SetNavigationWidthToolBarManager(
        realNavBarWidth_, frameWidth - realNavBarWidth_ - realDividerWidth_, realDividerWidth_);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

void NavigationPattern::HandleDragEnd()
{
    preNavBarWidth_ = realNavBarWidth_;
    if (!isDividerDraggable_) {
        return;
    }
    isInDividerDrag_ = false;
    SetMouseStyle(MouseFormat::DEFAULT);
}

void NavigationPattern::InitDividerPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!panEvent_);
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragStart();
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragUpdate(static_cast<float>(info.GetOffsetX()));
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragEnd();
    };
    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragEnd();
    };
    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    PanDirection panDirection = { .type = PanDirection::HORIZONTAL };
    PanDistanceMap distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE.ConvertToPx() },
        { SourceTool::PEN, DEFAULT_PEN_PAN_DISTANCE.ConvertToPx() } };
    gestureHub->AddPanEvent(panEvent_, panDirection, DEFAULT_PAN_FINGER, distanceMap);
}

void NavigationPattern::InitDragBarPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!dragBarPanEvent_);
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragStart();
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragUpdate(static_cast<float>(info.GetOffsetX()));
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragEnd();
    };
    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragEnd();
    };
    dragBarPanEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    PanDirection panDirection = { .type = PanDirection::HORIZONTAL };
    PanDistanceMap distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE.ConvertToPx() },
        { SourceTool::PEN, DEFAULT_PEN_PAN_DISTANCE.ConvertToPx() } };
    gestureHub->AddPanEvent(dragBarPanEvent_, panDirection, DEFAULT_PAN_FINGER, distanceMap);
}

void NavigationPattern::OnHover(bool isHover)
{
    if (isInDividerDrag_) {
        return;
    }
    auto layoutProperty = GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto userSetMinNavBarWidthValue = layoutProperty->GetMinNavBarWidthValue(Dimension(0.0));
    auto userSetMaxNavBarWidthValue = layoutProperty->GetMaxNavBarWidthValue(Dimension(0.0));
    bool navBarWidthRangeEqual = userSetMinNavBarWidthValue.Value() >= userSetMaxNavBarWidthValue.Value();
    if ((userSetNavBarWidthFlag_ && !userSetNavBarRangeFlag_) || (userSetNavBarRangeFlag_ && navBarWidthRangeEqual)) {
        isDividerDraggable_ = false;
        return;
    }
    isDividerDraggable_ = true;
    MouseFormat format = isHover ? MouseFormat::RESIZE_LEFT_RIGHT : MouseFormat::DEFAULT;
    SetMouseStyle(format);
}

RefPtr<FrameNode> NavigationPattern::GetNavigationNode() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto navigationNode = AceType::DynamicCast<FrameNode>(host);
    CHECK_NULL_RETURN(navigationNode, nullptr);
    return host;
}

RefPtr<FrameNode> NavigationPattern::GetNavBarNode() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(host);
    CHECK_NULL_RETURN(navigationNode, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(navigationNode->GetNavBarNode());
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode;
}

RefPtr<FrameNode> NavigationPattern::GetNavBarNodeOrHomeDestination() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(host);
    CHECK_NULL_RETURN(navigationNode, nullptr);
    return AceType::DynamicCast<FrameNode>(navigationNode->GetNavBarOrHomeDestinationNode());
}

RefPtr<FrameNode> NavigationPattern::GetContentNode() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(host);
    CHECK_NULL_RETURN(navigationNode, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(navigationNode->GetContentNode());
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode;
}

RefPtr<FrameNode> NavigationPattern::GetDividerNode() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(host);
    CHECK_NULL_RETURN(navigationNode, nullptr);
    auto dividerFrameNode = AceType::DynamicCast<FrameNode>(navigationNode->GetDividerNode());
    CHECK_NULL_RETURN(dividerFrameNode, nullptr);
    return dividerFrameNode;
}

RefPtr<FrameNode> NavigationPattern::GetDragBarNode() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(host);
    CHECK_NULL_RETURN(navigationNode, nullptr);
    auto dragBarNode = AceType::DynamicCast<FrameNode>(navigationNode->GetDragBarNode());
    CHECK_NULL_RETURN(dragBarNode, nullptr);
    return dragBarNode;
}

void NavigationPattern::BeforeSyncGeometryProperties(const DirtySwapConfig& /* config */)
{
    AddDividerHotZoneRect();
}

void NavigationPattern::AddDividerHotZoneRect()
{
    if (NearZero(realDividerWidth_)) {
        return;
    }
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto navBarOrHomeDestNode = AceType::DynamicCast<FrameNode>(hostNode->GetNavBarOrHomeDestinationNode());
    CHECK_NULL_VOID(navBarOrHomeDestNode);
    auto geometryNode = navBarOrHomeDestNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    OffsetF hotZoneOffset;
    hotZoneOffset.SetX(-DEFAULT_DIVIDER_HOT_ZONE_HORIZONTAL_PADDING.ConvertToPx());
    hotZoneOffset.SetY(DEFAULT_DIVIDER_START_MARGIN.ConvertToPx());
    SizeF hotZoneSize;
    hotZoneSize.SetWidth(realDividerWidth_ + DIVIDER_HOT_ZONE_HORIZONTAL_PADDING_NUM *
                                                 DEFAULT_DIVIDER_HOT_ZONE_HORIZONTAL_PADDING.ConvertToPx());
    hotZoneSize.SetHeight(geometryNode->GetFrameSize().Height());
    DimensionRect hotZoneRegion;
    auto paintHeight = GetPaintRectHeight(navBarOrHomeDestNode);
    if (navigationMode_ == NavigationMode::STACK || enableDragBar_) {
        hotZoneRegion.SetSize(DimensionSize(Dimension(0.0f), Dimension(0.0f)));
    } else {
        hotZoneRegion.SetSize(DimensionSize(
            Dimension(hotZoneSize.Width()), Dimension(NearZero(paintHeight) ? hotZoneSize.Height() : paintHeight)));
    }
    hotZoneRegion.SetOffset(DimensionOffset(Dimension(hotZoneOffset.GetX()), Dimension(hotZoneOffset.GetY())));

    std::vector<DimensionRect> mouseRegion;
    mouseRegion.emplace_back(hotZoneRegion);

    auto dividerFrameNode = GetDividerNode();
    CHECK_NULL_VOID(dividerFrameNode);
    auto dividerGestureHub = dividerFrameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(dividerGestureHub);
    dividerGestureHub->SetMouseResponseRegion(mouseRegion);

    auto dragRectOffset = geometryNode->GetMarginFrameOffset();
    dragRectOffset.SetX(-DEFAULT_DRAG_REGION.ConvertToPx());
    dragRect_.SetOffset(dragRectOffset);
    if (navigationMode_ == NavigationMode::STACK || enableDragBar_) {
        dragRect_.SetSize(SizeF(0.0f, 0.0f));
    } else {
        dragRect_.SetSize(SizeF(DEFAULT_DRAG_REGION.ConvertToPx() * DEFAULT_HALF + realDividerWidth_,
            NearZero(paintHeight) ? geometryNode->GetFrameSize().Height() : paintHeight));
    }

    std::vector<DimensionRect> responseRegion;
    DimensionOffset responseOffset(dragRectOffset);
    DimensionRect responseRect(Dimension(dragRect_.Width(), DimensionUnit::PX),
        Dimension(dragRect_.Height(), DimensionUnit::PX), responseOffset);
    responseRegion.emplace_back(responseRect);
    dividerGestureHub->SetResponseRegion(responseRegion);
}

void NavigationPattern::AddDragBarHotZoneRect()
{
    if (NearZero(realDividerWidth_)) {
        return;
    }
    auto dargBarNode = GetDragBarNode();
    CHECK_NULL_VOID(dargBarNode);
    auto geometryNode = dargBarNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto dragBarGestureHub = dargBarNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(dragBarGestureHub);
    
    auto dragRectOffset = geometryNode->GetMarginFrameOffset();
    dragRectOffset.SetX(-DEFAULT_DRAG_BAR_HOT_ZONE.ConvertToPx());
    dragRectOffset.SetY(0.0f);
    dragBarRect_.SetOffset(dragRectOffset);
    if (navigationMode_ == NavigationMode::STACK) {
        dragBarRect_.SetSize(SizeF(0.0f, 0.0f));
    } else {
        dragBarRect_.SetSize(SizeF(DEFAULT_DRAG_BAR_HOT_ZONE.ConvertToPx() * DEFAULT_HALF +
            geometryNode->GetFrameSize().Width(), geometryNode->GetFrameSize().Height()));
    }
    std::vector<DimensionRect> responseRegion;
    DimensionOffset responseOffset(dragRectOffset);
    DimensionRect responseRect(Dimension(dragBarRect_.Width(), DimensionUnit::PX),
        Dimension(dragBarRect_.Height(), DimensionUnit::PX), responseOffset);
    responseRegion.emplace_back(responseRect);
    dragBarGestureHub->SetResponseRegion(responseRegion);
}

void NavigationPattern::NotifyDialogChange(NavDestinationLifecycle lifecycle, bool isFromStandardIndex)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    const auto& navDestinationNodes = navigationStack_->GetAllNavDestinationNodes();
    int32_t lastStandardIndex = hostNode->GetLastStandardIndex();
    int32_t standardIndex = lastStandardIndex >= 0 ? lastStandardIndex : 0;
    int32_t start = isFromStandardIndex ? standardIndex : 0;
    int32_t end = isFromStandardIndex ? navigationStack_->Size() : standardIndex;
    bool isShow = (lifecycle == NavDestinationLifecycle::ON_SHOW)
        || (lifecycle == NavDestinationLifecycle::ON_WILL_SHOW);
    if (isShow) {
        for (int32_t index = start; index < end; index++) {
            NotifyDestinationLifecycle(navDestinationNodes[index].second, lifecycle);
        }
    } else {
        for (int32_t index = end - 1; index >= 0 && index >= start; index--) {
            NotifyDestinationLifecycle(navDestinationNodes[index].second, lifecycle);
        }
    }
}

void NavigationPattern::DumpInfo()
{
    if (!navigationStack_) {
        return;
    }
    DumpLog::GetInstance().AddDesc(std::string("size").append(std::to_string(navigationStack_->Size())));
}

bool NavigationPattern::TriggerCustomAnimation(RefPtr<NavDestinationGroupNode> preTopNavDestination,
    RefPtr<NavDestinationGroupNode> newTopNavDestination, bool isPopPage)
{
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "will trigger navigation custom animation");
    if ((!preTopNavDestination && !newTopNavDestination) || !onTransition_) {
        return false;
    }
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, false);
    hostNode->SetIsOnAnimation(true);
    if (!newTopNavDestination) {
        // pop animation with top navDestination, recover navBar visible tag
        hostNode->SetNeedSetInvisible(false);
    }
    auto proxy = AceType::MakeRefPtr<NavigationTransitionProxy>();
    auto homeDestination = AceType::DynamicCast<NavDestinationGroupNode>(hostNode->GetNavBarOrHomeDestinationNode());
    proxy->SetPreDestination(preTopNavDestination ? preTopNavDestination : homeDestination);
    proxy->SetTopDestination(newTopNavDestination ? newTopNavDestination : homeDestination);
    auto proxyId = proxy->GetProxyId();
    proxyList_.emplace_back(proxy);
    auto navigationTransition = ExecuteTransition(preTopNavDestination, newTopNavDestination, isPopPage);
    if (!navigationTransition.isValid) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "custom transition value is invalid, do default animation");
        RemoveProxyById(proxyId);
        return false;
    }
    ExecuteAddAnimation(preTopNavDestination, newTopNavDestination, isPopPage, proxy, navigationTransition);
    ACE_SCOPED_TRACE_COMMERCIAL("Navigation page custom transition start");
    if (navigationTransition.interactive) {
        PerfMonitor::GetPerfMonitor()->Start(PerfConstants::ABILITY_OR_PAGE_SWITCH_INTERACTIVE,
            PerfActionType::FIRST_MOVE, "");
        std::function<void()> onFinish = [weakNavigation = WeakClaim(this),
                                  weakPreNavDestination = WeakPtr<NavDestinationGroupNode>(preTopNavDestination),
                                  weakNewNavDestination = WeakPtr<NavDestinationGroupNode>(newTopNavDestination),
                                  isPopPage, proxyId]() {
            auto pattern = weakNavigation.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto proxy = pattern->GetProxyById(proxyId);
            if (proxy == nullptr) {
                return;
            }
            if (!proxy->GetInteractive()) {
                pattern->RemoveProxyById(proxyId);
                return;
            }
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "interactive animation is finish: %{public}d", proxy->GetIsSuccess());
            pattern->isFinishInteractiveAnimation_ = true;
            auto preDestination = weakPreNavDestination.Upgrade();
            auto topDestination = weakNewNavDestination.Upgrade();
            proxy->SetIsFinished(true);
            // this flag will be update in cancelTransition or finishTransition
            ACE_SCOPED_TRACE_COMMERCIAL("navigation page custom transition end");
            PerfMonitor::GetPerfMonitor()->End(PerfConstants::ABILITY_OR_PAGE_SWITCH_INTERACTIVE, true);
            if (proxy->GetIsSuccess()) {
                pattern->ClearRecoveryList();
                pattern->OnCustomAnimationFinish(preDestination, topDestination, isPopPage);
            } else {
                // fire page cancel transition
                TAG_LOGI(AceLogTag::ACE_NAVIGATION, "interactive animation canceled");
                pattern->RecoveryToLastStack(preDestination, topDestination);
                pattern->SyncWithJsStackIfNeeded();
            }
            proxy->FireEndCallback();
            pattern->RemoveProxyById(proxyId);
        };
        auto finishCallback = [onFinishCb = std::move(onFinish), weakNavigation = WeakClaim(this)]() {
            auto pattern = weakNavigation.Upgrade();
            if (onFinishCb) {
                onFinishCb();
            }
            CHECK_NULL_VOID(pattern);
            pattern->OnFinishOneTransitionAnimation();
        };
        auto pipelineContext = hostNode->GetContext();
        CHECK_NULL_RETURN(pipelineContext, false);
        auto navigationManager = pipelineContext->GetNavigationManager();
        CHECK_NULL_RETURN(navigationManager, false);
        navigationManager->SetInteractive(hostNode->GetId());
        proxy->SetInteractiveAnimation(AnimationUtils::CreateInteractiveAnimation(
            nullptr, finishCallback), finishCallback);
        navigationTransition.transition(proxy);
        isFinishInteractiveAnimation_ = false;
        navigationManager->FinishInteractiveAnimation();
        OnStartOneTransitionAnimation();
        proxy->StartAnimation();
    } else {
        PerfMonitor::GetPerfMonitor()->Start(PerfConstants::ABILITY_OR_PAGE_SWITCH, PerfActionType::LAST_UP, "");
        ClearRecoveryList();
        OnStartOneTransitionAnimation();
        navigationTransition.transition(proxy);
        // enable render group for text node during custom animation to reduce
        // unnecessary redrawing
        if (isPopPage && preTopNavDestination) {
            preTopNavDestination->UpdateTextNodeListAsRenderGroup(isPopPage, proxy);
        }
        if (!isPopPage && newTopNavDestination) {
            newTopNavDestination->UpdateTextNodeListAsRenderGroup(isPopPage, proxy);
        }
    }

    RefPtr<EventHub> eventHub;
    if (!preTopNavDestination && navigationMode_ == NavigationMode::STACK) {
        auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
        CHECK_NULL_RETURN(hostNode, true);
        auto navBarOrHomeDestNode = AceType::DynamicCast<FrameNode>(hostNode->GetNavBarOrHomeDestinationNode());
        CHECK_NULL_RETURN(navBarOrHomeDestNode, true);
        eventHub = navBarOrHomeDestNode->GetOrCreateEventHub<EventHub>();
    }
    if (preTopNavDestination) {
        eventHub = preTopNavDestination->GetOrCreateEventHub<EventHub>();
    }
    CHECK_NULL_RETURN(eventHub, true);
    eventHub->SetEnabledInternal(false);
    return true;
}

void NavigationPattern::OnCustomAnimationFinish(const RefPtr<NavDestinationGroupNode>& preTopNavDestination,
    const RefPtr<NavDestinationGroupNode>& newTopNavDestination, bool isPopPage)
{
    // preTopNavDestination or newTopNavDestination maybe is HomeNavDestination!!!
    if (!preTopNavDestination && !newTopNavDestination) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "preDestination and topDestination is invalid");
        return;
    }
    ACE_SCOPED_TRACE_COMMERCIAL("Navigation page custom transition end");
    PerfMonitor::GetPerfMonitor()->End(PerfConstants::ABILITY_OR_PAGE_SWITCH, true);
    auto replaceValue = navigationStack_->GetReplaceValue();
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto homeDest = AceType::DynamicCast<NavDestinationGroupNode>(hostNode->GetHomeDestinationNode());
    bool preIsHomeDest = homeDest && preTopNavDestination == homeDest;
    hostNode->SetIsOnAnimation(false);
    auto id = hostNode->GetTopDestination() ? hostNode->GetTopDestination()->GetAccessibilityId() : -1;
    hostNode->OnAccessibilityEvent(
        AccessibilityEventType::PAGE_CHANGE, id, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_INVALID);
    do {
        if (replaceValue != 0) {
            if (preTopNavDestination) {
                preTopNavDestination->SetIsOnAnimation(false);
            }
            if (newTopNavDestination) {
                newTopNavDestination->SetIsOnAnimation(false);
            }
            hostNode->DealNavigationExit(preTopNavDestination, (preTopNavDestination == nullptr || preIsHomeDest));
            navigationStack_->UpdateReplaceValue(0);
            break;
        }
        if ((newTopNavDestination && preTopNavDestination && isPopPage) ||
            (preTopNavDestination && !newTopNavDestination)) {
            PageTransitionType preNodeTransitionType = preTopNavDestination->GetTransitionType();
            if (preNodeTransitionType != PageTransitionType::EXIT_POP) {
                TAG_LOGI(AceLogTag::ACE_NAVIGATION, "previous destination node is executing another transition");
                return;
            }
            preTopNavDestination->SetIsOnAnimation(false);
            if (newTopNavDestination && newTopNavDestination->GetTransitionType() == PageTransitionType::ENTER_POP) {
                newTopNavDestination->SetIsOnAnimation(false);
            }
            auto preDestinationPattern = preTopNavDestination->GetPattern<NavDestinationPattern>();
            CHECK_NULL_VOID(preDestinationPattern);
            auto shallowBuilder = preDestinationPattern->GetShallowBuilder();
            if (shallowBuilder && !preIsHomeDest) {
                shallowBuilder->MarkIsExecuteDeepRenderDone(false);
            }
            if (!preIsHomeDest) {
                auto parent = preTopNavDestination->GetParent();
                CHECK_NULL_VOID(parent);
                parent->RemoveChild(preTopNavDestination);
                parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            }
            break;
        }
        if ((newTopNavDestination && preTopNavDestination && !isPopPage) ||
            (!preTopNavDestination && newTopNavDestination && navigationMode_ == NavigationMode::STACK)) {
            hostNode->SetNeedSetInvisible(true);
            RefPtr<FrameNode> node;
            PageTransitionType preNodeTransitionType;
            if (preTopNavDestination) {
                preNodeTransitionType = preTopNavDestination->GetTransitionType();
                node = preTopNavDestination;
            } else {
                // pre destination is nullptr, preNode is navBarNode or HomeDestination
                auto navBarOrHomeDestNode =
                    AceType::DynamicCast<NavDestinationNodeBase>(hostNode->GetNavBarOrHomeDestinationNode());
                CHECK_NULL_VOID(navBarOrHomeDestNode);
                preNodeTransitionType = navBarOrHomeDestNode->GetTransitionType();
                node = navBarOrHomeDestNode;
                CHECK_NULL_VOID(node);
            }
            if (newTopNavDestination && newTopNavDestination->GetTransitionType() == PageTransitionType::ENTER_PUSH) {
                newTopNavDestination->SetIsOnAnimation(false);
            }
            if (preNodeTransitionType != PageTransitionType::EXIT_PUSH) {
                TAG_LOGI(AceLogTag::ACE_NAVIGATION, "previous destination node is executing another transition");
                return;
            }
            if (preTopNavDestination) {
                preTopNavDestination->SetIsOnAnimation(false);
            }
            // recover event hub
            auto eventHub = node->GetOrCreateEventHub<EventHub>();
            if (eventHub) {
                eventHub->SetEnabledInternal(true);
            }
            bool isDialog = newTopNavDestination->GetNavDestinationMode() == NavDestinationMode::DIALOG;
            if (isDialog) {
                return;
            }
            if (preIsHomeDest && navigationMode_ == NavigationMode::SPLIT) {
                return;
            }
            auto property = node->GetLayoutProperty();
            property->UpdateVisibility(VisibleType::INVISIBLE);
            node->SetJSViewActive(false);
            if (!preTopNavDestination) {
                hostNode->NotifyPageHide();
            }
        }
    } while (0);
    hostNode->RemoveDialogDestination();
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->MarkNeedFlushMouseEvent();
}

NavigationTransition NavigationPattern::ExecuteTransition(const RefPtr<NavDestinationGroupNode>& preTopDestination,
    const RefPtr<NavDestinationGroupNode>& newTopNavDestination, bool isPopPage)
{
    NavigationTransition navigationTransition;
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, navigationTransition);
    NavigationOperation operation;
    auto currentProxy = GetTopNavigationProxy();
    auto preInfo = currentProxy->GetPreDestinationContext();
    auto topInfo = currentProxy->GetTopDestinationContext();
    auto replaceValue = navigationStack_->GetReplaceValue();
    RefPtr<NavDestinationGroupNode> realPreTopDest = nullptr;
    RefPtr<NavDestinationGroupNode> realNewTopDest = nullptr;
    if (replaceValue != 0) {
        operation = NavigationOperation::REPLACE;
    } else if (!preTopDestination) {
        operation = NavigationOperation::PUSH;
        // if animated with navBarNode/HomeDestination, recover navBar/HomeDestination visibility
        hostNode->SetNeedSetInvisible(false);
    } else {
        operation = (!newTopNavDestination || isPopPage) ? NavigationOperation::POP : NavigationOperation::PUSH;
    }
    /* set transition animation flag fro navBarNode or navDestinationNode */
    if (operation == NavigationOperation::PUSH) {
        if (preTopDestination != nullptr) {
            preTopDestination->SetTransitionType(PageTransitionType::EXIT_PUSH);
            realPreTopDest = preTopDestination;
        } else {
            // preTopDestination is nullptr, previous node is navBar or HomeDestination
            auto navBarOrHomeDestNode =
                AceType::DynamicCast<NavDestinationNodeBase>(hostNode->GetNavBarOrHomeDestinationNode());
            CHECK_NULL_RETURN(navBarOrHomeDestNode, navigationTransition);
            navBarOrHomeDestNode->SetTransitionType(PageTransitionType::EXIT_PUSH);
            realPreTopDest = AceType::DynamicCast<NavDestinationGroupNode>(navBarOrHomeDestNode);
        }
        if (newTopNavDestination != nullptr) {
            newTopNavDestination->SetTransitionType(PageTransitionType::ENTER_PUSH);
            realNewTopDest = newTopNavDestination;
        }
    }
    if (operation == NavigationOperation::POP) {
        if (preTopDestination != nullptr) {
            preTopDestination->SetTransitionType(PageTransitionType::EXIT_POP);
            realPreTopDest = preTopDestination;
        }
        if (newTopNavDestination != nullptr) {
            newTopNavDestination->SetTransitionType(PageTransitionType::ENTER_POP);
            realNewTopDest = newTopNavDestination;
        } else {
            // newTopNavDestination is nullptr, current node is navBar or HomeDestination
            auto navBarOrHomeDestNode =
                AceType::DynamicCast<NavDestinationNodeBase>(hostNode->GetNavBarOrHomeDestinationNode());
            CHECK_NULL_RETURN(navBarOrHomeDestNode, navigationTransition);
            navBarOrHomeDestNode->SetTransitionType(PageTransitionType::ENTER_POP);
            realNewTopDest = AceType::DynamicCast<NavDestinationGroupNode>(navBarOrHomeDestNode);
        }
    }
    LogCustomAnimationStart(realPreTopDest, realNewTopDest, operation);
    return onTransition_(preInfo, topInfo, operation);
}

void NavigationPattern::OnColorConfigurationUpdate()
{
    UpdateDividerBackgroundColor();

    auto dragBarNode = GetDragBarNode();
    CHECK_NULL_VOID(dragBarNode);
    auto dragPattern = dragBarNode->GetPattern<NavigationDragBarPattern>();
    CHECK_NULL_VOID(dragPattern);
    dragPattern->UpdateDefaultColor();
}

void NavigationPattern::UpdateDividerBackgroundColor()
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(navigationGroupNode);
    auto dividerNode = GetDividerNode();
    CHECK_NULL_VOID(dividerNode);
    auto theme = NavigationGetTheme(navigationGroupNode->GetThemeScopeId());
    CHECK_NULL_VOID(theme);
    dividerNode->GetRenderContext()->UpdateBackgroundColor(theme->GetNavigationDividerColor());
    dividerNode->MarkDirtyNode();
}

void NavigationPattern::UpdateToobarFocusColor()
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(navigationGroupNode);
    auto navBarOrHomeDestNode =
        AceType::DynamicCast<NavDestinationNodeBase>(navigationGroupNode->GetNavBarOrHomeDestinationNode());
    CHECK_NULL_VOID(navBarOrHomeDestNode);
    auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(navBarOrHomeDestNode->GetPreToolBarNode());
    CHECK_NULL_VOID(toolBarNode);
    auto containerNode = AceType::DynamicCast<FrameNode>(toolBarNode->GetToolbarContainerNode());
    CHECK_NULL_VOID(containerNode);
    auto toolBarItemNodes = containerNode->GetChildren();
    auto theme = NavigationGetTheme(navigationGroupNode->GetThemeScopeId());
    CHECK_NULL_VOID(theme);
    for (auto& toolBarItemNode : toolBarItemNodes) {
        auto buttonNode = AceType::DynamicCast<FrameNode>(toolBarItemNode);
        CHECK_NULL_VOID(buttonNode);
        auto buttonPattern = AceType::DynamicCast<ButtonPattern>(buttonNode->GetPattern());
        CHECK_NULL_VOID(buttonPattern);
        buttonPattern->SetFocusBorderColor(theme->GetToolBarItemFocusColor());
        auto focusHub = buttonNode->GetFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusHub->SetPaintColor(theme->GetToolBarItemFocusColor());
    }
}

bool NavigationPattern::OnThemeScopeUpdate(int32_t themeScopeId)
{
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(navigationGroupNode, false);
    auto navBarOrHomeDestNode =
        AceType::DynamicCast<NavDestinationNodeBase>(navigationGroupNode->GetNavBarOrHomeDestinationNode());
    CHECK_NULL_RETURN(navBarOrHomeDestNode, false);

    auto dividerNode = AceType::DynamicCast<FrameNode>(navBarOrHomeDestNode->GetToolBarDividerNode());
    CHECK_NULL_RETURN(dividerNode, false);

    auto theme = NavigationGetTheme(themeScopeId);
    CHECK_NULL_RETURN(theme, false);

    auto dividerRenderProperty = dividerNode->GetPaintProperty<DividerRenderProperty>();
    CHECK_NULL_RETURN(dividerRenderProperty, false);
    dividerRenderProperty->UpdateDividerColor(theme->GetToolBarDividerColor());

    navigationGroupNode->MarkModifyDone();
    return false;
}

void NavigationPattern::UpdatePreNavDesZIndex(const RefPtr<FrameNode> &preTopNavDestination,
    const RefPtr<FrameNode> &newTopNavDestination, int32_t preLastStandardIndex)
{
    auto replaceVal = navigationStack_->GetReplaceValue();
    if (replaceVal != 0 && preTopNavDestination && newTopNavDestination) {
        auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
        CHECK_NULL_VOID(hostNode);
        auto navigationContentNode = AceType::DynamicCast<FrameNode>(hostNode->GetContentNode());
        CHECK_NULL_VOID(navigationContentNode);
        auto newDesNodeContext = newTopNavDestination->GetRenderContext();
        CHECK_NULL_VOID(newDesNodeContext);
        std::optional<int32_t> newNodeZIndex = newDesNodeContext->GetZIndex();
        int32_t standardIndex = newNodeZIndex.value_or(0) - 1;
        auto hideNodes = hostNode->GetHideNodes();
        for (auto iter = hideNodes.begin(); iter != hideNodes.end(); ++iter) {
            // if navdestination nodes is not need removed, default zIndex is satisfied, don't need change
            if (!iter->second) {
                continue;
            }
            auto navDestination = iter->first;
            if (!navDestination) {
                continue;
            }
            auto navDestinationContext = navDestination->GetRenderContext();
            if (!navDestinationContext) {
                continue;
            }
            // get navDestination index in hideNodes, use navdestination index in pre navigation stack
            int32_t hideNodesIndex =
                static_cast<int32_t>(hideNodes.size()) - (navDestination->GetIndex() - preLastStandardIndex);
            navDestinationContext->UpdateZIndex(standardIndex - hideNodesIndex);
        }
        auto preDesNodeContext = preTopNavDestination->GetRenderContext();
        CHECK_NULL_VOID(preDesNodeContext);
        preDesNodeContext->UpdateZIndex(standardIndex);
        navigationContentNode->RebuildRenderContextTree();
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->RequestFrame();
    }
}

void NavigationPattern::SetNavigationStack(const RefPtr<NavigationStack>& navigationStack)
{
    if (navigationStack_) {
        navigationStack_->SetOnStateChangedCallback(nullptr);
    }
    navigationStack_ = navigationStack;
    if (navigationStack_) {
        navigationStack_->SetNavigationNode(GetHost());
        WeakPtr<NavigationPattern> weakPattern = WeakClaim(this);
        auto id = Container::CurrentId();
        auto callback = [weakPattern, id]() {
            ContainerScope scope(id);
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (pattern->NeedSyncWithJsStackMarked()) {
                return;
            }
            pattern->MarkNeedSyncWithJsStack();
            auto context = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(context);
            context->AddBuildFinishCallBack([weakPattern]() {
                auto pattern = weakPattern.Upgrade();
                CHECK_NULL_VOID(pattern);
                pattern->SyncWithJsStackIfNeeded();
                auto host = pattern->GetHost();
                CHECK_NULL_VOID(host);
                host->MarkDirtyNode();
            });
            context->RequestFrame();
        };
        navigationStack_->SetOnStateChangedCallback(callback);
    }
}

RefPtr<NavigationPattern> NavigationPattern::GetParentNavigationPattern()
{
    RefPtr<UINode> node = GetHost();
    CHECK_NULL_RETURN(node, nullptr);
    node = node->GetParent();
    while (node) {
        if (node->GetTag() == V2::NAVIGATION_VIEW_ETS_TAG) {
            break;
        }
        node = node->GetParent();
    }
    auto groupNode = AceType::DynamicCast<NavigationGroupNode>(node);
    CHECK_NULL_RETURN(groupNode, nullptr);
    return AceType::DynamicCast<NavigationPattern>(groupNode->GetPattern());
}

void NavigationPattern::AttachNavigationStackToParent()
{
    CHECK_NULL_VOID(navigationStack_);
    auto parentPattern = GetParentNavigationPattern();
    CHECK_NULL_VOID(parentPattern);
    auto parentStack = parentPattern->GetNavigationStack();
    if (parentStack) {
        navigationStack_->OnAttachToParent(parentStack);
    }
}

void NavigationPattern::DetachNavigationStackFromParent()
{
    if (navigationStack_) {
        navigationStack_->OnDetachFromParent();
    }
}

void NavigationPattern::DealTransitionVisibility(const RefPtr<FrameNode>& node, bool isVisible, bool isNavBar)
{
    auto renderContext = node->GetRenderContext();
    if (!renderContext->HasDisappearTransition()) {
        auto layoutProperty = node->GetLayoutProperty();
        layoutProperty->UpdateVisibility(isVisible ? VisibleType::VISIBLE : VisibleType::INVISIBLE);
        node->SetJSViewActive(isVisible);
        return;
    }
    auto layoutProperty = node->GetLayoutProperty();
    layoutProperty->UpdateVisibility(isVisible ? VisibleType::VISIBLE : VisibleType::INVISIBLE, true);
    renderContext->SetTransitionOutCallback([
        weakNode = WeakPtr<FrameNode>(node), isVisible] {
        auto curNode = weakNode.Upgrade();
        CHECK_NULL_VOID(curNode);
        auto nodeBase = AceType::DynamicCast<NavDestinationNodeBase>(curNode);
        if (nodeBase && nodeBase->GetTransitionType() != PageTransitionType::EXIT_PUSH) {
            return;
        }
        curNode->SetJSViewActive(isVisible);
    });
}

void NavigationPattern::AddToDumpManager()
{
    auto node = GetHost();
    auto context = PipelineContext::GetCurrentContext();
    if (!node || !context) {
        return;
    }
    auto mgr = context->GetNavigationManager();
    if (!mgr) {
        return;
    }
    auto callback = [weakPattern = WeakClaim(this)](int depth) {
        auto pattern = weakPattern.Upgrade();
        if (!pattern) {
            return;
        }
        const auto& stack = pattern->GetNavigationStack();
        if (!stack) {
            return;
        }
        auto infos = stack->DumpStackInfo();
    };
    mgr->AddNavigationDumpCallback(node->GetId(), node->GetDepth(), callback);
}

void NavigationPattern::RemoveFromDumpManager()
{
    auto node = GetHost();
    auto context = PipelineContext::GetCurrentContext();
    if (!node || !context) {
        return;
    }
    auto mgr = context->GetNavigationManager();
    if (mgr) {
        mgr->RemoveNavigationDumpCallback(node->GetId(), node->GetDepth());
    }
}

void NavigationPattern::FireInterceptionEvent(bool isBefore,
    const std::optional<std::pair<std::string, RefPtr<UINode>>>& newTopPath)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    RefPtr<NavDestinationContext> to;
    if (newTopPath.has_value()) {
        auto topDestination =
            AceType::DynamicCast<NavDestinationGroupNode>(hostNode->GetNavDestinationNode(newTopPath->second));
        if (topDestination) {
            auto pattern = AceType::DynamicCast<NavDestinationPattern>(topDestination->GetPattern());
            to = pattern->GetNavDestinationContext();
        }
    }
    NavigationOperation operation;
    if (isReplace_ != 0) {
        operation = NavigationOperation::REPLACE;
    } else {
        operation = lastPreIndex_ == -1 ? NavigationOperation::POP : NavigationOperation::PUSH;
    }
    auto layoutProperty = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    // mode is split and stack size is one,don't need to do animation.
    if ((layoutProperty->GetUsrNavigationModeValue(NavigationMode::AUTO) == NavigationMode::SPLIT
        || navigationMode_ == NavigationMode::SPLIT) && !preContext_) {
        isAnimated_ = false;
    }
    navigationStack_->FireNavigationInterception(isBefore, preContext_, to, operation,
        isAnimated_);

    if (!isBefore) {
        NotifyNavDestinationSwitch(preContext_, to, operation);
    }
}

void NavigationPattern::UpdateIsAnimation(const std::optional<std::pair<std::string, RefPtr<UINode>>>& preTopNavPath)
{
    auto disAbleAnimation = navigationStack_->GetDisableAnimation();
    auto animated = navigationStack_->GetAnimatedValue();
    // current animation flag is false
    if (disAbleAnimation || !animated) {
        isAnimated_ = false;
        return;
    }
    // check is dialog mode
    bool isDialog = false;
    if (preTopNavPath.has_value()) {
        auto preDestination = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(preTopNavPath->second));
        if (preDestination) {
            isDialog = isDialog || (preDestination->GetNavDestinationMode() == NavDestinationMode::DIALOG);
        }
    }
    auto topNode = navigationStack_->Get();
    if (topNode) {
        auto newTopDestination = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(topNode));
        if (newTopDestination) {
            isDialog = isDialog || (newTopDestination->GetNavDestinationMode() == NavDestinationMode::DIALOG);
        }
    }
    if (!isDialog) {
        isAnimated_ = true;
        return;
    }
    isAnimated_ = isCustomAnimation_;
}

RefPtr<NavDestinationContext> NavigationPattern::GetHomeDestinationContext()
{
    auto host = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(host, nullptr);
    auto homeDest = AceType::DynamicCast<NavDestinationGroupNode>(host->GetHomeDestinationNode());
    CHECK_NULL_RETURN(homeDest, nullptr);
    auto homePattern = homeDest->GetPattern<NavDestinationPattern>();
    CHECK_NULL_RETURN(homePattern, nullptr);
    return homePattern->GetNavDestinationContext();
}

void NavigationPattern::NotifyNavDestinationSwitch(RefPtr<NavDestinationContext> from,
    RefPtr<NavDestinationContext> to, NavigationOperation operation)
{
    auto host = GetHost();
    auto NavdestinationSwitchFunc =
        UIObserverHandler::GetInstance().GetHandleNavDestinationSwitchFunc();
    if (!host || !NavdestinationSwitchFunc) {
        return;
    }

    bool useHomeDest = false;
    if (!from) {
        from = GetHomeDestinationContext();
        useHomeDest = from != nullptr;
    } else if (!to) {
        to = GetHomeDestinationContext();
    }
    std::string navigationId = host->GetInspectorIdValue("");
    std::optional<NavDestinationInfo> fromInfo;
    std::optional<NavDestinationInfo> toInfo;
    RefPtr<NavPathInfo> pathInfo = nullptr;
    if (from) {
        pathInfo = from->GetNavPathInfo();
    } else if (to) {
        pathInfo = to->GetNavPathInfo();
    }
    if (pathInfo) {
        pathInfo->OpenScope();
    }
    auto state = NavDestinationState::ON_HIDDEN;
    auto context = host->GetContextRefPtr();
    if (((IsForceSplitSupported(context) && forceSplitSuccess_) || useHomeDest) && from) {
        auto pattern = from->GetNavDestinationPattern();
        if (pattern && pattern->GetIsOnShow()) {
            state = NavDestinationState::ON_SHOWN;
        }
    }
    BuildNavDestinationInfoFromContext(navigationId, state, from, true, fromInfo);
    BuildNavDestinationInfoFromContext(navigationId, NavDestinationState::ON_SHOWN, to, false, toInfo);
    UIObserverHandler::GetInstance().NotifyNavDestinationSwitch(
        std::move(fromInfo), std::move(toInfo), operation);
    if (pathInfo) {
        pathInfo->CloseScope();
    }
}

void NavigationPattern::AppendFilterNodesFromHideNodes(std::set<RefPtr<NavDestinationGroupNode>>& filterNodes)
{
    auto host = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(host);
    const auto& hideNodes = host->GetHideNodes();
    for (const auto& pair : hideNodes) {
        CHECK_NULL_CONTINUE(pair.first);
        filterNodes.emplace(pair.first);
    }
}

void NavigationPattern::AppendFilterNodesForWillHideLifecycle(std::set<RefPtr<NavDestinationGroupNode>>& filterNodes)
{
    AppendFilterNodesFromHideNodes(filterNodes);
    for (auto& weakNode : primaryNodes_) {
        auto node = weakNode.Upgrade();
        CHECK_NULL_CONTINUE(node);
        filterNodes.emplace(node);
    }
}

void NavigationPattern::NotifyPrePrimaryNodesOnWillHide(std::set<RefPtr<NavDestinationGroupNode>>&& filterNodes)
{
    if (!forceSplitSuccess_ || forceSplitUseNavBar_) {
        return;
    }

    for (auto it = prePrimaryNodes_.rbegin(); it != prePrimaryNodes_.rend(); ++it) {
        auto node = it->Upgrade();
        CHECK_NULL_CONTINUE(node);
        auto pattern = node->GetPattern<NavDestinationPattern>();
        CHECK_NULL_CONTINUE(pattern);
        if (filterNodes.find(node) != filterNodes.end()) {
            continue;
        }
        if (!pattern->GetIsOnShow()) {
            continue;
        }
        NotifyDestinationLifecycle(node, NavDestinationLifecycle::ON_WILL_HIDE);
    }
}

void NavigationPattern::AppendFilterNodesForWillShowLifecycle(std::set<RefPtr<NavDestinationGroupNode>>& filterNodes)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    const auto& navDestinationNodes = navigationStack_->GetAllNavDestinationNodes();
    int32_t lastStandardIndex = hostNode->GetLastStandardIndex();
    int32_t standardIndex = lastStandardIndex >= 0 ? lastStandardIndex : 0;
    int32_t end = navigationStack_->Size();
    for (int32_t index = standardIndex; index < end; index++) {
        const auto& uiNode = navDestinationNodes[index].second;
        auto destNode = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(uiNode));
        filterNodes.emplace(destNode);
    }
}

void NavigationPattern::NotifyCurPrimaryNodesOnWillShow(std::set<RefPtr<NavDestinationGroupNode>>&& filterNodes)
{
    if (!forceSplitSuccess_ || forceSplitUseNavBar_) {
        return;
    }

    for (auto it = primaryNodes_.begin(); it != primaryNodes_.end(); ++it) {
        auto node = it->Upgrade();
        CHECK_NULL_CONTINUE(node);
        auto pattern = node->GetPattern<NavDestinationPattern>();
        CHECK_NULL_CONTINUE(pattern);
        if (filterNodes.find(node) != filterNodes.end()) {
            continue;
        }
        if (pattern->GetIsOnShow()) {
            continue;
        }
        NotifyDestinationLifecycle(node, NavDestinationLifecycle::ON_WILL_SHOW);
    }
}

bool NavigationPattern::CheckIfNoNeedAnimationForForceSplit(const RefPtr<NavDestinationGroupNode>& preDestination,
    const RefPtr<NavDestinationGroupNode>& topDestination)
{
    if (!forceSplitSuccess_) {
        return false;
    }
    if (forceSplitUseNavBar_) {
        return !preDestination || !topDestination;
    }
    return (preDestination && preDestination->IsShowInPrimaryPartition()) ||
        (topDestination && topDestination->IsShowInPrimaryPartition());
}

void NavigationPattern::FireHomeDestinationLifecycleForTransition(NavDestinationLifecycle lifecycle)
{
    auto host = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto homeDest = AceType::DynamicCast<NavDestinationGroupNode>(host->GetHomeDestinationNode());
    CHECK_NULL_VOID(homeDest);
    auto homePattern = homeDest->GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(homePattern);
    if (navigationMode_ != NavigationMode::STACK) {
        return;
    }
    auto lastStandardIndex = host->GetLastStandardIndex();
    auto preLastStandardIndex = host->GetPreLastStandardIndex();
    const auto& preNodes = GetAllNavDestinationNodesPrev();
    const auto& curNodes = GetAllNavDestinationNodes();
    if (lifecycle == NavDestinationLifecycle::ON_WILL_SHOW || lifecycle == NavDestinationLifecycle::ON_SHOW) {
        if (preLastStandardIndex >= 0 && lastStandardIndex < 0 && !homePattern->GetIsOnShow()) {
            NotifyDestinationLifecycle(homeDest, lifecycle);
        }
    } else if (lifecycle == NavDestinationLifecycle::ON_ACTIVE) {
        if (!preNodes.empty() && curNodes.empty() && !homePattern->IsActive()) {
            NotifyDestinationLifecycle(
                homeDest, NavDestinationLifecycle::ON_ACTIVE, NavDestinationActiveReason::TRANSITION);
        }
    } else if (lifecycle == NavDestinationLifecycle::ON_INACTIVE) {
        if (preNodes.empty() && !curNodes.empty() && homePattern->IsActive()) {
            NotifyDestinationLifecycle(
                homeDest, NavDestinationLifecycle::ON_INACTIVE, NavDestinationActiveReason::TRANSITION);
        }
    } else if (lifecycle == NavDestinationLifecycle::ON_WILL_HIDE || lifecycle == NavDestinationLifecycle::ON_HIDE) {
        if (preLastStandardIndex < 0 && lastStandardIndex >= 0 && homePattern->GetIsOnShow()) {
            NotifyDestinationLifecycle(homeDest, lifecycle);
        }
    }
}

bool NavigationPattern::GetHomeDestinationName(const RefPtr<FrameNode>& hostNode, std::string& name)
{
    auto host = AceType::DynamicCast<NavigationGroupNode>(hostNode);
    CHECK_NULL_RETURN(host, false);
    auto homeDest = AceType::DynamicCast<NavDestinationGroupNode>(host->GetHomeDestinationNode());
    CHECK_NULL_RETURN(homeDest, false);
    auto homePattern = homeDest->GetPattern<NavDestinationPattern>();
    CHECK_NULL_RETURN(homePattern, false);
    name = homePattern->GetName();
    return true;
}

void NavigationPattern::StartTransition(const RefPtr<NavDestinationGroupNode>& preDestination,
    const RefPtr<NavDestinationGroupNode>& topDestination,
    bool isAnimated, bool isPopPage, bool isNeedVisible)
{
    std::string fromPathInfo;
    std::string toPathInfo;
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    bool isNotNeedAnimation = !isAnimated;
#if defined(ENABLE_NAV_SPLIT_MODE)
    isNotNeedAnimation = !isAnimated ||
        (navigationMode_ == NavigationMode::SPLIT && navigationStack_->Size() <= 1 &&
            !isBackPage_ && !isCustomAnimation_);
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "StartTransition navigationMode_:%{public}d isNotNeedAnimation:%{public}d",
        navigationMode_, isNotNeedAnimation);
#endif
    if (CheckIfNoNeedAnimationForForceSplit(preDestination, topDestination)) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "StartTransition don't need animation in forceSplit mode");
        isNotNeedAnimation = true;
    }

    std::string fromNavDestinationName = "";
    std::string toNavDestinationName = "";
    if (preDestination) {
        fromPathInfo = preDestination->GetNavDestinationPathInfo();
        auto preDestinationPattern = preDestination->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(preDestinationPattern);
        fromNavDestinationName = preDestinationPattern->GetName();
        fromPathInfo += ", navDesitinationName: " + fromNavDestinationName;
        if ((isPopPage || preDestination->NeedRemoveInPush()) && isNotNeedAnimation) {
            /**
             * when transition without animation, 'pop' and 'push with remove' need to post
             * afterLayoutTask to delay old top's onDisappear. So set this flag to 'false'
             */
            preDestination->SetIsAnimated(false);
        }
    } else if (GetHomeDestinationName(hostNode, fromNavDestinationName)) {
        fromPathInfo += ", navDesitinationName: " + fromNavDestinationName;
    } else {
        fromPathInfo = hostNode->GetNavigationPathInfo();
    }
    if (topDestination) {
        toPathInfo = topDestination->GetNavDestinationPathInfo();
        auto topDestinationPattern = topDestination->GetPattern<NavDestinationPattern>();
        CHECK_NULL_VOID(topDestinationPattern);
        toNavDestinationName = topDestinationPattern->GetName();
        toPathInfo += ", navDesitinationName: " + toNavDestinationName;
    } else if (GetHomeDestinationName(hostNode, toNavDestinationName)) {
        toPathInfo += ", navDesitinationName: " + toNavDestinationName;
    } else {
        toPathInfo = hostNode->GetNavigationPathInfo();
    }
    ACE_SCOPED_TRACE_COMMERCIAL("NavDestination Page from %s to %s", fromPathInfo.c_str(), toPathInfo.c_str());
    if (PerfMonitor::GetPerfMonitor() != nullptr) {
        PerfMonitor::GetPerfMonitor()->SetPageName(toNavDestinationName);
    }
    ResSchedReport::GetInstance().HandlePageTransition(fromNavDestinationName, toNavDestinationName, "navigation");
    UiSessionManager::GetInstance()->OnRouterChange(toPathInfo.c_str(), "navigationPathChange");
    // fire onWillHide
    if (!isPopPage && !preDestination && navigationMode_ == NavigationMode::STACK) {
        // NavBar/HomeNavDestination will be covered in STACK mode
        auto navBarOrHomeDestNode = AceType::DynamicCast<FrameNode>(hostNode->GetNavBarOrHomeDestinationNode());
        ProcessAutoSave(navBarOrHomeDestNode);
    }
    std::set<RefPtr<NavDestinationGroupNode>> filterNodes;
    if (isPopPage || IsDestinationNeedHideInPush(hostNode, preDestination)) {
        NotifyDestinationLifecycle(preDestination, NavDestinationLifecycle::ON_WILL_HIDE);
        filterNodes.emplace(preDestination);
    }
    AppendFilterNodesForWillHideLifecycle(filterNodes);
    hostNode->FireHideNodeChange(NavDestinationLifecycle::ON_WILL_HIDE);
    NotifyPrePrimaryNodesOnWillHide(std::move(filterNodes));

    FireHomeDestinationLifecycleForTransition(NavDestinationLifecycle::ON_WILL_HIDE);

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto navigationManager = pipeline->GetNavigationManager();
    navigationManager->FireNavigationUpdateCallback();
    auto overlayManager = pipeline->GetOverlayManager();
    if (overlayManager) {
        overlayManager->RemoveAllModalInOverlay(false);
    }
    FireHomeDestinationLifecycleForTransition(NavDestinationLifecycle::ON_WILL_SHOW);

    if (topDestination) {
        filterNodes.clear();
        AppendFilterNodesForWillShowLifecycle(filterNodes);
        NotifyCurPrimaryNodesOnWillShow(std::move(filterNodes));

        NotifyDialogChange(NavDestinationLifecycle::ON_WILL_SHOW, true);
        topDestination->SetNodeFreeze(false);
    }
    if (preDestination) {
        preDestination->SetNodeFreeze(false);
    }
    UpdatePageViewportConfigIfNeeded(preDestination, topDestination);
    pipeline->AddAfterLayoutTask([weakPattern = WeakClaim(this)]() {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HideSystemBarIfNeeded();
    });
    if (isNotNeedAnimation) {
        FireShowAndHideLifecycle(preDestination, topDestination, isPopPage, false);
        TransitionWithOutAnimation(preDestination, topDestination, isPopPage, isNeedVisible);
        prePrimaryNodes_.clear();
        primaryNodesToBeRemoved_.clear();
        RemoveRedundantPrimaryNavDestination();
        return;
    }

    pipeline->AddAfterLayoutTask([weakNavigation = WeakClaim(this),
        weakPreDestination = WeakPtr<NavDestinationGroupNode>(preDestination),
        weakTopDestination = WeakPtr<NavDestinationGroupNode>(topDestination),
        isPopPage, isNeedVisible]() {
        auto navigationPattern = AceType::DynamicCast<NavigationPattern>(weakNavigation.Upgrade());
        CHECK_NULL_VOID(navigationPattern);
        auto preDestination = weakPreDestination.Upgrade();
        auto topDestination = weakTopDestination.Upgrade();

        auto forceSplitSuccess = navigationPattern->IsForceSplitSuccess();
        auto forceSplitUseNavBar = navigationPattern->IsForceSplitUseNavBar();
        if (forceSplitSuccess && !forceSplitUseNavBar &&
            ((preDestination && preDestination->GetNavDestinationType() == NavDestinationType::HOME) ||
            (topDestination && topDestination->GetNavDestinationType() == NavDestinationType::HOME))) {
            navigationPattern->FireShowAndHideLifecycle(preDestination, topDestination, isPopPage, false);
            navigationPattern->TransitionWithOutAnimation(preDestination, topDestination, isPopPage, isNeedVisible);
            navigationPattern->prePrimaryNodes_.clear();
            navigationPattern->primaryNodesToBeRemoved_.clear();
            navigationPattern->RemoveRedundantPrimaryNavDestination();
            return;
        }

        navigationPattern->FireShowAndHideLifecycle(preDestination, topDestination, isPopPage, true);
        navigationPattern->TransitionWithAnimation(preDestination, topDestination, isPopPage, isNeedVisible);
        navigationPattern->prePrimaryNodes_.clear();
        navigationPattern->primaryNodesToBeRemoved_.clear();
        navigationPattern->RemoveRedundantPrimaryNavDestination();
    });
}

void NavigationPattern::ProcessAutoSave(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    if (!node->NeedRequestAutoSave()) {
        return;
    }
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    container->RequestAutoSave(node);
}

void NavigationPattern::NotifyDestinationLifecycle(const RefPtr<UINode>& uiNode,
    NavDestinationLifecycle lifecycle, NavDestinationActiveReason reason)
{
    auto curDestination =
        AceType::DynamicCast<NavDestinationGroupNode>(NavigationGroupNode::GetNavDestinationNode(uiNode));
    CHECK_NULL_VOID(curDestination);
    auto eventHub = curDestination->GetOrCreateEventHub<NavDestinationEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (lifecycle == NavDestinationLifecycle::ON_WILL_DISAPPEAR) {
        NavigationPattern::FireNavigationLifecycleChange(curDestination, lifecycle);
        eventHub->FireOnWillDisAppear();
        return;
    }
    auto navDestinationPattern = curDestination->GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(navDestinationPattern);
    if (lifecycle == NavDestinationLifecycle::ON_INACTIVE) {
        FireOnInactiveLifecycle(curDestination, reason);
        return;
    }
    if (lifecycle == NavDestinationLifecycle::ON_ACTIVE) {
        FireOnActiveLifecycle(curDestination, reason);
        return;
    }
    if ((navDestinationPattern->GetIsOnShow() && (lifecycle == NavDestinationLifecycle::ON_SHOW ||
            lifecycle == NavDestinationLifecycle::ON_WILL_SHOW)) ||
        (!navDestinationPattern->GetIsOnShow() && (lifecycle == NavDestinationLifecycle::ON_HIDE ||
            lifecycle == NavDestinationLifecycle::ON_WILL_HIDE))) {
        return;
    }
    if (lifecycle == NavDestinationLifecycle::ON_WILL_SHOW) {
        eventHub->FireOnWillShow();
        NavigationPattern::FireNavigationLifecycleChange(curDestination, lifecycle);
        return;
    }
    if (lifecycle == NavDestinationLifecycle::ON_SHOW) {
        FireOnShowLifecycle(curDestination);
        return;
    }
    NavigationPattern::FireNavigationLifecycleChange(curDestination, lifecycle);
    if (lifecycle == NavDestinationLifecycle::ON_WILL_HIDE) {
        eventHub->FireOnWillHide();
        return;
    }
    if (lifecycle == NavDestinationLifecycle::ON_HIDE) {
        eventHub->FireOnHiddenEvent(navDestinationPattern->GetName());
        NotifyPageHide(navDestinationPattern->GetName());
        navDestinationPattern->SetIsOnShow(false);
    }
}

void NavigationPattern::FireOnShowLifecycle(const RefPtr<NavDestinationGroupNode>& curDestination)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(navigationNode);
    auto parentDestinationNode = navigationNode->GetParentDestinationNode().Upgrade();
    if (CheckParentDestinationIsOnhide(parentDestinationNode) && CheckDestinationIsPush(parentDestinationNode)) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "parentDestinationNode is onhide");
        return;
    }
    auto param = Recorder::EventRecorder::Get().IsPageParamRecordEnable() ? navigationStack_->GetRouteParam() : "";
    auto eventHub = curDestination->GetOrCreateEventHub<NavDestinationEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto navDestinationPattern = curDestination->GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(navDestinationPattern);
    eventHub->FireOnShownEvent(navDestinationPattern->GetName(), param);
    NotifyPageShow(navDestinationPattern->GetName());
    navDestinationPattern->SetIsOnShow(true);
    NavigationPattern::FireNavigationLifecycleChange(curDestination, NavDestinationLifecycle::ON_SHOW);
}

void NavigationPattern::FireOnActiveLifecycle(const RefPtr<NavDestinationGroupNode>& curDestination,
    NavDestinationActiveReason reason)
{
    auto navDestinationPattern = curDestination->GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(navDestinationPattern);
    if (navDestinationPattern->IsActive() || CheckParentDestinationInactive()) {
        return;
    }
    auto eventHub = curDestination->GetOrCreateEventHub<NavDestinationEventHub>();
    CHECK_NULL_VOID(eventHub);
    navDestinationPattern->SetIsActive(true);
    eventHub->FireOnActive(static_cast<int32_t>(reason));
    NavigationPattern::FireNavigationLifecycle(curDestination, NavDestinationLifecycle::ON_ACTIVE, reason);
}

void NavigationPattern::FireOnInactiveLifecycle(const RefPtr<NavDestinationGroupNode>& curDestination,
    NavDestinationActiveReason reason)
{
    auto navDestinationPattern = curDestination->GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(navDestinationPattern);
    if (!navDestinationPattern->IsActive()) {
        return;
    }
    auto eventHub = curDestination->GetOrCreateEventHub<NavDestinationEventHub>();
    CHECK_NULL_VOID(eventHub);
    navDestinationPattern->SetIsActive(false);
    NavigationPattern::FireNavigationLifecycle(curDestination, NavDestinationLifecycle::ON_INACTIVE, reason);
    eventHub->FireOnInactive(static_cast<int32_t>(reason));
}

std::unique_ptr<JsonValue> NavigationPattern::GetNavdestinationJsonArray()
{
    auto allNavdestinationInfo = JsonUtil::CreateArray(true);
    const auto& navdestinationNodes = GetAllNavDestinationNodes();
    for (auto iter : navdestinationNodes) {
        auto navdestinationInfo = JsonUtil::Create(true);
        auto navdestinationNode =
            AceType::DynamicCast<NavDestinationGroupNode>(NavigationGroupNode::GetNavDestinationNode(iter.second));
        if (!navdestinationNode) {
            continue;
        }
        if (!navdestinationNode->CanRecovery()) {
            continue;
        }
        auto navdestinationPattern = navdestinationNode->GetPattern<NavDestinationPattern>();
        if (!navdestinationPattern) {
            continue;
        }
        auto name = navdestinationPattern->GetName();
        auto param = navigationStack_->GetStringifyParamByIndex(navdestinationNode->GetIndex());
        auto mode = static_cast<int32_t>(navdestinationNode->GetNavDestinationMode());
        navdestinationInfo->Put("name", name.c_str());
        navdestinationInfo->Put("param", param.c_str());
        navdestinationInfo->Put("mode", mode);
        allNavdestinationInfo->Put(navdestinationInfo);
    }
    return allNavdestinationInfo;
}

std::unique_ptr<JsonValue> NavigationPattern::GetTopNavdestinationJson(bool needParam)
{
    auto topNavdestinationJson = JsonUtil::Create(true);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, topNavdestinationJson);
    auto topNavDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(
        NavigationGroupNode::GetNavDestinationNode(GetNavDestinationNode()));
    if (!topNavDestinationNode) {
        return topNavdestinationJson;
    }
    auto navdestinationPattern = topNavDestinationNode->GetPattern<NavDestinationPattern>();
    if (!navdestinationPattern) {
        return topNavdestinationJson;
    }
    auto name = navdestinationPattern->GetName();
    auto mode = static_cast<int32_t>(topNavDestinationNode->GetNavDestinationMode());
    topNavdestinationJson->Put("name", name.c_str());
    topNavdestinationJson->Put("mode", mode);
    topNavdestinationJson->Put("navigationId", hostNode->GetCurId().c_str());
    std::string param = "";
    if (needParam) {
        param = navdestinationPattern->GetSerializedParam();
        topNavdestinationJson->Put("param", param.c_str());
    }
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "get top navDestinationInfo success, name: %{public}s, mode: %{public}d, "
        "navigationId: %{public}s, hasParam? %{public}s", name.c_str(), mode, hostNode->GetCurId().c_str(),
        param.empty() ? "no" : "yes");
    return topNavdestinationJson;
}

void NavigationPattern::RestoreJsStackIfNeeded()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto navigationManager = pipeline->GetNavigationManager();
    CHECK_NULL_VOID(navigationManager);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto navdestinationsInfo = navigationManager->GetNavigationRecoveryInfo(hostNode->GetCurId());
    if (navdestinationsInfo.empty()) {
        return;
    }
    navigationStack_->SetPathArray(navdestinationsInfo);
}

void NavigationPattern::PerformanceEventReport(int32_t nodeCount, int32_t depth, const std::string& navDestinationName)
{
    if (nodeCount >= PAGE_NODES) {
        EventReport::ReportPageNodeOverflow(navDestinationName, nodeCount, PAGE_NODES);
    }
    if (depth >= PAGE_DEPTH) {
        EventReport::ReportPageDepthOverflow(navDestinationName, depth, PAGE_DEPTH);
    }
}

bool NavigationPattern::IsTopPrimaryNode(const RefPtr<NavDestinationGroupNode>& node)
{
    return forceSplitSuccess_ && !forceSplitUseNavBar_ &&
        !primaryNodes_.empty() && node == primaryNodes_.back().Upgrade();
}

void NavigationPattern::FireShowAndHideLifecycle(const RefPtr<NavDestinationGroupNode>& preDestination,
    const RefPtr<NavDestinationGroupNode>& topDestination, bool isPopPage, bool isAnimated)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    // don't move position hide lifecycle is from top to end
    if (preDestination) {
        if (!IsTopPrimaryNode(preDestination)) {
            NotifyDestinationLifecycle(preDestination, NavDestinationLifecycle::ON_INACTIVE);
        }
        if (isPopPage || IsDestinationNeedHideInPush(hostNode, preDestination)) {
            // fire preTop Destination lifecycle
            NotifyDestinationLifecycle(preDestination, NavDestinationLifecycle::ON_HIDE);
        }
    }
    // fire remove navDestination and invisible navDestination lifecycle for pop or clear
    hostNode->FireHideNodeChange(NavDestinationLifecycle::ON_HIDE);
    FireHomeDestinationLifecycleForTransition(NavDestinationLifecycle::ON_INACTIVE);
    FireHomeDestinationLifecycleForTransition(NavDestinationLifecycle::ON_HIDE);
    FirePreTopPrimaryNodeInactiveIfNeeded();
    FirePrePrimaryNodesOnHide();
    std::set<RefPtr<NavDestinationGroupNode>> filterNodes;
    if (isPopPage || (preDestination && preDestination->NeedRemoveInPush())) {
        // fire removed preDestination lifecycle for pop many times or clear
        filterNodes.emplace(preDestination);
        NotifyDestinationLifecycle(preDestination, NavDestinationLifecycle::ON_WILL_DISAPPEAR);
    }
    AppendFilterNodesFromHideNodes(filterNodes);
    // fire removed navDestination lifecycle
    hostNode->FireHideNodeChange(NavDestinationLifecycle::ON_WILL_DISAPPEAR);
    FirePrePrimaryNodesOnWillDisappear(std::move(filterNodes));
    FirePrimaryNodesOnShowAndActive();
    FireHomeDestinationLifecycleForTransition(NavDestinationLifecycle::ON_SHOW);
    FireHomeDestinationLifecycleForTransition(NavDestinationLifecycle::ON_ACTIVE);
    if (!isAnimated) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->AddAfterLayoutTask([weakNavigation = WeakClaim(this),
            weakTopDestination = WeakPtr<NavDestinationGroupNode>(topDestination)]() {
            auto navigation = weakNavigation.Upgrade();
            CHECK_NULL_VOID(navigation);
            auto topDestination = weakTopDestination.Upgrade();
            navigation->NotifyDialogChange(NavDestinationLifecycle::ON_SHOW, true);
            navigation->NotifyDestinationLifecycle(topDestination, NavDestinationLifecycle::ON_ACTIVE);
        });
    } else {
        NotifyDialogChange(NavDestinationLifecycle::ON_SHOW, true);
        NotifyDestinationLifecycle(topDestination, NavDestinationLifecycle::ON_ACTIVE);
    }
    FireInterceptionEvent(false, navigationStack_->GetTopNavPath());
}

void NavigationPattern::OnWindowSizeChanged(int32_t  /*width*/, int32_t  /*height*/, WindowSizeChangeReason type)
{
    if (WindowSizeChangeReason::ROTATION == type) {
        auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
        CHECK_NULL_VOID(hostNode);
        AbortAnimation(hostNode);
        CloseLongPressDialog();
    }
}

void NavigationPattern::OnWindowHide()
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto navigationPattern = hostNode->GetPattern<NavigationPattern>();
    CHECK_NULL_VOID(navigationPattern);
    navigationPattern->SyncWithJsStackIfNeeded();
}

void NavigationPattern::NotifyPerfMonitorPageMsg(const std::string& pageName)
{
    auto container = Container::Current();
    if (container != nullptr && PerfMonitor::GetPerfMonitor() != nullptr) {
        std::string bundleName = container->GetBundleName();
        PerfMonitor::GetPerfMonitor()->ReportPageShowMsg("", bundleName, pageName);
    }
}

void NavigationPattern::RefreshFocusToDestination()
{
    auto newTopNavPath = navigationStack_->GetTopNavPath();
    if (!newTopNavPath.has_value()) {
        return;
    }
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto navBarOrHomeDestNode = AceType::DynamicCast<FrameNode>(hostNode->GetNavBarOrHomeDestinationNode());
    CHECK_NULL_VOID(navBarOrHomeDestNode);
    auto navBarOrHomeDestFocus = navBarOrHomeDestNode->GetFocusHub();
    CHECK_NULL_VOID(navBarOrHomeDestFocus);
    if (!navBarOrHomeDestFocus->IsCurrentFocus()) {
        return;
    }
    auto newTopNavDestination = AceType::DynamicCast<NavDestinationGroupNode>(
        NavigationGroupNode::GetNavDestinationNode(newTopNavPath->second));
    CHECK_NULL_VOID(newTopNavDestination);
    if (!GetIsFocusable(newTopNavDestination)) {
        return;
    }
    auto navDestinationFocusView = newTopNavDestination->GetPattern<FocusView>();
    CHECK_NULL_VOID(navDestinationFocusView);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        navDestinationFocusView->SetIsViewRootScopeFocused(false);
    }
    navDestinationFocusView->FocusViewShow();
}

void NavigationPattern::RecoveryToLastStack(
    const RefPtr<NavDestinationGroupNode>& preTopDestination,
    const RefPtr<NavDestinationGroupNode>& newTopDestination)
{
    if (preTopDestination) {
        preTopDestination->SetIsOnAnimation(false);
        preTopDestination->SetInCurrentStack(true);
    }
    if (newTopDestination) {
        newTopDestination->SetIsOnAnimation(false);
    }
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    hostNode->CleanHideNodes();
    CHECK_NULL_VOID(navigationStack_);
    navigationStack_->SetNavPathList(navigationStack_->GetRecoveryList());

    // update cached node
    auto destinationNodes = navigationStack_->GetAllNavDestinationNodes();
    for (uint32_t index = 0; index < destinationNodes.size(); index++) {
        auto childNode = destinationNodes[index];
        if (!childNode.second) {
            continue;
        }
        auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(childNode.second));
        if (!navDestinationNode) {
            continue;
        }
        // update pre cache node to cache node list
        auto cacheNode = navigationStack_->GetFromCacheNode(childNode.first);
        if (cacheNode && cacheNode == childNode.second) {
            navigationStack_->AddCacheNode(childNode.first, childNode.second);
        }
    }
    hostNode->UpdateNavDestinationNodeWithoutMarkDirty(nullptr, navigationModeChange_);

    // recover lifecycle state before transition
    NotifyDestinationLifecycle(preTopDestination, NavDestinationLifecycle::ON_INACTIVE);
    hostNode->FireHideNodeChange(NavDestinationLifecycle::ON_HIDE);
    hostNode->FireHideNodeChange(NavDestinationLifecycle::ON_WILL_DISAPPEAR);
    NotifyDialogChange(NavDestinationLifecycle::ON_SHOW, true);
    NotifyDestinationLifecycle(newTopDestination, NavDestinationLifecycle::ON_ACTIVE);
    hostNode->RemoveDialogDestination(false, true);
    hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);

    // update name index
    navigationStack_->RecoveryNavigationStack();
    ACE_SCOPED_TRACE_COMMERCIAL("Navigation page transition end");
    PerfMonitor::GetPerfMonitor()->End(PerfConstants::ABILITY_OR_PAGE_SWITCH, true);
    hostNode->SetIsOnAnimation(false);
    auto id = hostNode->GetTopDestination() ? hostNode->GetTopDestination()->GetAccessibilityId() : -1;
    hostNode->OnAccessibilityEvent(
        AccessibilityEventType::PAGE_CHANGE, id, WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_INVALID);
}

bool NavigationPattern::ExecuteAddAnimation(RefPtr<NavDestinationGroupNode> preTopNavDestination,
    RefPtr<NavDestinationGroupNode> newTopNavDestination,
    bool isPopPage, const RefPtr<NavigationTransitionProxy>& proxy,
    NavigationTransition navigationTransition)
{
    // custom animation return undefined,finish this transition
    if (!navigationTransition.isValid) {
        proxy->SetIsSuccess(false);
        proxy->SetIsFinished(true);
        return false;
    }
    auto host = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    RefPtr<NavDestinationGroupNode> homeDestination = host ?
        AceType::DynamicCast<NavDestinationGroupNode>(host->GetHomeDestinationNode()) : nullptr;
    if (!preTopNavDestination) {
        preTopNavDestination = homeDestination;
    } else if (!newTopNavDestination) {
        newTopNavDestination = homeDestination;
    }
    if (preTopNavDestination) {
        preTopNavDestination->SetIsOnAnimation(true);
        if (!isPopPage) {
            auto renderContext = preTopNavDestination->GetRenderContext();
            CHECK_NULL_RETURN(renderContext, false);
            renderContext->RemoveClipWithRRect();
        }
    }
    if (newTopNavDestination) {
        newTopNavDestination->SetIsOnAnimation(true);
    }
    auto proxyId = proxy->GetProxyId();
    proxy->SetInteractive(navigationTransition.interactive);
    // set on transition end callback
    proxy->SetEndCallback(std::move(navigationTransition.endCallback));
    std::function<void()> onFinish = [weakNavigation = WeakClaim(this),
                     weakPreNavDestination = WeakPtr<NavDestinationGroupNode>(preTopNavDestination),
                     weakNewNavDestination = WeakPtr<NavDestinationGroupNode>(newTopNavDestination),
                     isPopPage, proxyId]() {
        auto pattern = weakNavigation.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto proxy = pattern->GetProxyById(proxyId);
        auto preDestination = weakPreNavDestination.Upgrade();
        auto topDestination = weakNewNavDestination.Upgrade();
        // disable render group for text node after the custom animation
        if (isPopPage && preDestination) {
            preDestination->ReleaseTextNodeList();
        }
        if (!isPopPage && topDestination) {
            topDestination->ReleaseTextNodeList();
        }
        // to avoid call finishTransition many times
        if (proxy == nullptr) {
            TAG_LOGW(AceLogTag::ACE_NAVIGATION, "custom animation proxy is empty or is finished");
            return;
        }
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "custom animation finish end");
        proxy->SetIsFinished(true);
        // update pre navigation stack
        ACE_SCOPED_TRACE_COMMERCIAL("navigation page custom transition end");
        PerfMonitor::GetPerfMonitor()->End(PerfConstants::ABILITY_OR_PAGE_SWITCH, true);
        pattern->ClearRecoveryList();
        pattern->OnCustomAnimationFinish(preDestination, topDestination, isPopPage);
        pattern->RemoveProxyById(proxyId);
    };
    auto finishWrapper = [onFinishCb = std::move(onFinish), weakNavigation = WeakClaim(this)]() {
        auto pattern = weakNavigation.Upgrade();
        if (onFinishCb) {
            onFinishCb();
        }
        CHECK_NULL_VOID(pattern);
        pattern->OnFinishOneTransitionAnimation();
    };
    proxy->SetFinishTransitionEvent(finishWrapper);
    // add timeout callback
    auto timeout = navigationTransition.timeout;
    auto hostNode = GetHost();
    CHECK_NULL_RETURN(hostNode, false);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
    if (timeout < 0) {
        return true;
    }
    // deal timeout callback
    taskExecutor->PostDelayedTask(
        [weakProxy = WeakPtr<NavigationTransitionProxy>(proxy)] {
            auto transitionProxy = weakProxy.Upgrade();
            CHECK_NULL_VOID(transitionProxy);
            transitionProxy->FireFinishCallback();
        },
        TaskExecutor::TaskType::UI, timeout, "ArkUINavigationTransitionProxyFinish");
    return true;
}

bool NavigationPattern::GetIsFocusable(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, false);
    auto focusHub = hostNode->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    if (!focusHub->IsFocusableWholePath()) {
        return false;
    }
    auto currentFocusHub = frameNode->GetFocusHub();
    CHECK_NULL_RETURN(currentFocusHub, false);
    return currentFocusHub->IsFocusableNode();
}

bool NavigationPattern::IsLastStdChange()
{
    // check whether last std navdestination id is changed, change return true, not change return false
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(navigationNode, false);
    auto& navPathList = navigationStack_->GetAllNavDestinationNodes();
    auto& preNavPathList = navigationStack_->GetAllNavDestinationNodesPrev();
    auto lastStdIndex = navigationNode->GetLastStandardIndex();
    auto preLastStdIndex = navigationNode->GetPreLastStandardIndex();
    if (preLastStdIndex == -1 && lastStdIndex == -1) {
        return false;
    }
    if (preLastStdIndex != -1 && lastStdIndex != -1) {
        // check new and pre std navdestination id changed or not
        auto preStd = NavigationGroupNode::GetNavDestinationNode(preNavPathList[preLastStdIndex].second.Upgrade());
        auto newStd = NavigationGroupNode::GetNavDestinationNode(navPathList[lastStdIndex].second);
        if (preStd && newStd) {
            return preStd != newStd;
        }
    }
    return true;
}

void NavigationPattern::FollowStdNavdestinationAnimation(const RefPtr<NavDestinationGroupNode>& preTopNavDestination,
    const RefPtr<NavDestinationGroupNode>& newTopNavDestination, bool isPopPage)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(navigationNode);
    if (preTopNavDestination && newTopNavDestination) {
        if (isPopPage) {
            navigationNode->TransitionWithDialogPop(preTopNavDestination, newTopNavDestination);
        } else {
            navigationNode->TransitionWithDialogPush(preTopNavDestination, newTopNavDestination);
        }
        return;
    }
    if (newTopNavDestination && navigationMode_ == NavigationMode::STACK) {
        auto navBarOrHomeDestNode =
            AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarOrHomeDestinationNode());
        CHECK_NULL_VOID(navBarOrHomeDestNode);
        navigationNode->TransitionWithDialogPush(navBarOrHomeDestNode, newTopNavDestination, true);
        return;
    }
    if (preTopNavDestination) {
        if (navigationMode_ == NavigationMode::SPLIT) {
            navigationNode->TransitionWithDialogPop(preTopNavDestination, nullptr);
        }
        if (navigationMode_ == NavigationMode::STACK) {
            auto navBarOrHomeDestNode =
                AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarOrHomeDestinationNode());
            CHECK_NULL_VOID(navBarOrHomeDestNode);
            navigationNode->TransitionWithDialogPop(preTopNavDestination, navBarOrHomeDestNode, true);
        }
    }
}

void NavigationPattern::TransitionWithDialogAnimation(const RefPtr<NavDestinationGroupNode>& preTopNavDestination,
    const RefPtr<NavDestinationGroupNode>& newTopNavDestination, bool isPopPage)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(navigationNode);

    // if last standard id is not changed and new top navdestination is standard
    if (!isPopPage && !IsLastStdChange() && newTopNavDestination &&
        newTopNavDestination->GetNavDestinationMode() == NavDestinationMode::STANDARD) {
        return;
    }
    auto replaceVal = navigationStack_->GetReplaceValue();
    if (replaceVal != 0) {
        ReplaceAnimation(preTopNavDestination, newTopNavDestination);
        return;
    }
    // last std id is not change, but new dialogs came into stack and upward animation
    if (!IsLastStdChange()) {
        if (isPopPage) {
            navigationNode->StartDialogtransition(preTopNavDestination, newTopNavDestination, false);
        } else {
            if (!preTopNavDestination && navigationMode_ == NavigationMode::SPLIT) {
                // if split mode and push one dialog at the first time, no animation
                return;
            }
            navigationNode->StartDialogtransition(preTopNavDestination, newTopNavDestination, true);
        }
        return;
    }
    FollowStdNavdestinationAnimation(preTopNavDestination, newTopNavDestination, isPopPage);
}

void NavigationPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    if (!navigationStack_) {
        return;
    }
    json->Put("size", std::to_string(navigationStack_->Size()).c_str());
}

void NavigationPattern::CreateDragBarNode(const RefPtr<NavigationGroupNode>& navigationGroupNode)
{
    auto dragBarNode = FrameNode::GetOrCreateFrameNode("DragBar", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavigationDragBarPattern>(); });
    auto dragBarLayoutProperty = dragBarNode->GetLayoutProperty();
    CHECK_NULL_VOID(dragBarLayoutProperty);
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    auto renderContext = dragBarNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackBlurRadius(DRAG_BAR_BLUR_RADIUS);
    renderContext->UpdateBorderRadius(BorderRadiusProperty(DRAG_BAR_RADIUS));
    renderContext->UpdateZIndex(1);
    dragBarNode->MarkModifyDone();
    auto dragBarItem = CreateDragBarItemNode();
    dragBarItem->MountToParent(dragBarNode);
    dragBarNode->MountToParent(navigationGroupNode);
    navigationGroupNode->SetDragBarNode(dragBarNode);

    auto dragBarPattern = dragBarNode->GetPattern<NavigationDragBarPattern>();
    CHECK_NULL_VOID(dragBarPattern);
    dragBarPattern->UpdateDefaultColor();
}

RefPtr<FrameNode> NavigationPattern::CreateDragBarItemNode()
{
    auto dragBarItemNode = FrameNode::GetOrCreateFrameNode("DragBarItem",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    auto dragBarItemLayoutProperty = dragBarItemNode->GetLayoutProperty();
    CHECK_NULL_RETURN(dragBarItemLayoutProperty, nullptr);
    dragBarItemLayoutProperty->UpdateAlignment(Alignment::CENTER);
    auto renderContext = dragBarItemNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    renderContext->UpdateZIndex(SECOND_ZINDEX_VALUE);
    renderContext->UpdateBorderRadius(BorderRadiusProperty(DRAG_BAR_ITEM_RADIUS));
    dragBarItemNode->MarkModifyDone();
    return dragBarItemNode;
}

RefPtr<NavigationTransitionProxy> NavigationPattern::GetProxyById(uint64_t id) const
{
    for (auto proxy : proxyList_) {
        if (proxy && proxy->GetProxyId() == id) {
            return proxy;
        }
    }
    return nullptr;
}
    
void NavigationPattern::RemoveProxyById(uint64_t id)
{
    for (auto it = proxyList_.begin(); it != proxyList_.end(); ++it) {
        if (*it && (*it)->GetProxyId() == id) {
            it = proxyList_.erase(it);
            return;
        }
    }
}

void NavigationPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (touchEvent_) {
        return;
    }
    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleTouchEvent(info);
    };
    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchEvent_);
}

void NavigationPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType == TouchType::DOWN) {
        HandleTouchDown();
    }
    if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
        HandleTouchUp();
    }
}

void NavigationPattern::HandleTouchDown()
{
    auto dragBarNode = GetDragBarNode();
    CHECK_NULL_VOID(dragBarNode);
    auto dragPattern = dragBarNode->GetPattern<NavigationDragBarPattern>();
    CHECK_NULL_VOID(dragPattern);
    dragPattern->UpdateActiveColor();

    auto dividerNode = GetDividerNode();
    CHECK_NULL_VOID(dividerNode);
    auto dividerRenderContext = dividerNode->GetRenderContext();
    CHECK_NULL_VOID(dividerRenderContext);
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::LINEAR);
    gradient.AddColor(CreatePercentGradientColor(0, theme->GetDviderLightBlueColor()));
    gradient.AddColor(CreatePercentGradientColor(HALF_POSITION, theme->GetDviderDarkBlueColor()));
    gradient.AddColor(CreatePercentGradientColor(END_POSITION, theme->GetDviderLightBlueColor()));
    dividerRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    dividerRenderContext->UpdateLinearGradient(gradient);
}

void NavigationPattern::HandleTouchUp()
{
    auto dragBarNode = GetDragBarNode();
    CHECK_NULL_VOID(dragBarNode);
    auto dragPattern = dragBarNode->GetPattern<NavigationDragBarPattern>();
    CHECK_NULL_VOID(dragPattern);
    dragPattern->UpdateDefaultColor();

    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    auto dividerNode = GetDividerNode();
    CHECK_NULL_VOID(dividerNode);
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::LINEAR);
    gradient.AddColor(CreatePercentGradientColor(0, Color::TRANSPARENT));
    dividerNode->GetRenderContext()->UpdateLinearGradient(gradient);
    dividerNode->GetRenderContext()->UpdateBackgroundColor(theme->GetNavigationDividerColor());
}

void NavigationPattern::CheckContentNeedMeasure(const RefPtr<FrameNode>& node)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(node);
    CHECK_NULL_VOID(navigationNode);
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(navigationLayoutProperty);
    if (!NavigationLayoutAlgorithm::IsAutoHeight(navigationLayoutProperty)) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "Navigation height is auto, content need to measure after pushAnimation ends");
    auto contentNode = navigationNode->GetContentNode();
    CHECK_NULL_VOID(contentNode);
    contentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void NavigationPattern::CloseLongPressDialog()
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);

    auto navBarOrHomeDestNode =
        AceType::DynamicCast<NavDestinationNodeBase>(hostNode->GetNavBarOrHomeDestinationNode());
    CHECK_NULL_VOID(navBarOrHomeDestNode);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarOrHomeDestNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarPattern = AceType::DynamicCast<TitleBarPattern>(titleBarNode->GetPattern());
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

    auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(navBarOrHomeDestNode->GetToolBarNode());
    CHECK_NULL_VOID(toolBarNode);
    auto toolBarPattern = AceType::DynamicCast<NavToolbarPattern>(toolBarNode->GetPattern());
    CHECK_NULL_VOID(toolBarPattern);
    auto toolBarItemDialogNode = toolBarPattern->GetDialogNode();
    if (toolBarItemDialogNode) {
        overlayManager->CloseDialog(toolBarItemDialogNode);
        toolBarPattern->SetToolBarItemDialogNode(nullptr);
    }
}

bool NavigationPattern::FindInCurStack(const RefPtr<FrameNode>& navDestinationNode)
{
    const auto& navdestinationNodes = GetAllNavDestinationNodes();
    for (auto navdestination : navdestinationNodes) {
        if (navDestinationNode == NavigationGroupNode::GetNavDestinationNode(navdestination.second)) {
            return true;
        }
    }
    return false;
}

void NavigationPattern::SetMouseStyle(MouseFormat format)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto frameNodeId = host->GetId();
    int32_t windowId = static_cast<int32_t>(pipeline->GetFocusWindowId());
#ifdef WINDOW_SCENE_SUPPORTED
    windowId = static_cast<int32_t>(WindowSceneHelper::GetFocusSystemWindowId(host));
#endif
    pipeline->SetMouseStyleHoldNode(frameNodeId);
    pipeline->ChangeMouseStyle(frameNodeId, format, windowId);
    pipeline->FreeMouseStyleHoldNode(frameNodeId);
}

void NavigationPattern::OnAvoidInfoChange(const ContainerModalAvoidInfo& info)
{
    if (!isFullPageNavigation_) {
        return;
    }
    MarkAllNavDestinationDirtyIfNeeded(GetHost(), true);
}

void NavigationPattern::RegisterAvoidInfoChangeListener(const RefPtr<FrameNode>& hostNode)
{
    CHECK_NULL_VOID(hostNode);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto mgr = pipeline->GetAvoidInfoManager();
    CHECK_NULL_VOID(mgr);
    mgr->AddAvoidInfoListener(WeakClaim(this));
}

void NavigationPattern::UnregisterAvoidInfoChangeListener(const RefPtr<FrameNode>& hostNode)
{
    CHECK_NULL_VOID(hostNode);
    auto pipeline = hostNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto mgr = pipeline->GetAvoidInfoManager();
    CHECK_NULL_VOID(mgr);
    mgr->RemoveAvoidInfoListener(WeakClaim(this));
}

void NavigationPattern::MarkAllNavDestinationDirtyIfNeeded(const RefPtr<FrameNode>& hostNode, bool skipCheck)
{
    auto groupNode = AceType::DynamicCast<NavigationGroupNode>(hostNode);
    CHECK_NULL_VOID(groupNode);
    if (!skipCheck) {
        auto pipeline = groupNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto avoidInfoMgr = pipeline->GetAvoidInfoManager();
        CHECK_NULL_VOID(avoidInfoMgr);
        if (!avoidInfoMgr->NeedAvoidContainerModal()) {
            return;
        }
    }

    auto contentNode = AceType::DynamicCast<FrameNode>(groupNode->GetContentNode());
    CHECK_NULL_VOID(contentNode);
    auto& childrens = contentNode->GetChildren();
    for (auto& child : childrens) {
        auto navDestination = AceType::DynamicCast<NavDestinationGroupNode>(child);
        if (!navDestination) {
            continue;
        }
        if (!navDestination->IsVisible()) {
            navDestination->SetNeedForceMeasure(true);
            continue;
        }
        navDestination->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestination->GetTitleBarNode());
        if (titleBarNode) {
            titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
    }
}

void NavigationPattern::FireNavigationLifecycle(const RefPtr<UINode>& uiNode, NavDestinationLifecycle lifecycle,
    NavDestinationActiveReason reason)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(uiNode);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto navigationManager = context->GetNavigationManager();
    CHECK_NULL_VOID(navigationManager);
    auto navigationIds = navigationManager->FindNavigationInTargetParent(frameNode->GetId());
    for (auto navigationId: navigationIds) {
        auto navigation = AceType::DynamicCast<NavigationGroupNode>(
            FrameNode::GetFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, navigationId));
        if (!navigation) {
            continue;
        }
        auto pattern = navigation->GetPattern<NavigationPattern>();
        if (!pattern) {
            continue;
        }
        auto navigationStack = pattern->GetNavigationStack();
        if (navigationStack) {
            pattern->NotifyDestinationLifecycle(AceType::DynamicCast<NavDestinationGroupNode>(
                NavigationGroupNode::GetNavDestinationNode(navigationStack->Get())), lifecycle, reason);
        }
    }
}

void NavigationPattern::GenerateLastStandardPage(NavPathList& navPathList)
{
    int64_t lastPageIndex = static_cast<int64_t>(navPathList.size()) - 1;
    // if top page is nullptr or is dialog node, we need to generate node util standard page is found.
    while (lastPageIndex >= 0 &&
        (navPathList[lastPageIndex].second == nullptr || !IsStandardPage(navPathList[lastPageIndex].second))) {
        auto pageNode = navPathList[lastPageIndex].second;
        // existed dialog node is no need to generate
        bool isExistedNode = (pageNode != nullptr);
        if (!pageNode && !GenerateUINodeByIndex(lastPageIndex, pageNode)) {
            std::string replacedName;
            int32_t replacedIndex = -1;
            if (navigationStack_->CheckIsReplacedDestination(lastPageIndex, replacedName, replacedIndex)) {
                navigationStack_->SetRecoveryFromReplaceDestination(lastPageIndex, false);
                continue;
            }
            navPathList.erase(navPathList.begin() + lastPageIndex);
            lastPageIndex--;
            continue;
        }
        navPathList[lastPageIndex].second = pageNode;
        auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(pageNode));
        if (!isExistedNode && navDestinationNode && navigationStack_->GetIsForceSet(lastPageIndex)) {
            navigationStack_->ResetIsForceSetFlag(lastPageIndex);
        }
        if (navDestinationNode && navDestinationNode->GetNavDestinationMode() == NavDestinationMode::STANDARD) {
            break;
        }
        lastPageIndex--;
    }
}

bool NavigationPattern::IsStandardPage(const RefPtr<UINode>& uiNode) const
{
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(
        NavigationGroupNode::GetNavDestinationNode(uiNode));
    CHECK_NULL_RETURN(navDestinationNode, false);
    return navDestinationNode->GetNavDestinationMode() == NavDestinationMode::STANDARD;
}

RefPtr<UINode> NavigationPattern::FindNavDestinationNodeInPreList(const uint64_t navDestinationId) const
{
    CHECK_NULL_RETURN(navigationStack_, nullptr);
    auto preNavDestinationList = navigationStack_->GetPreNavPathList();
    for (auto preNavDestinationInfo : preNavDestinationList) {
        auto preNavDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(preNavDestinationInfo.second));
        CHECK_NULL_CONTINUE(preNavDestinationNode);
        auto pattern = preNavDestinationNode->GetPattern<NavDestinationPattern>();
        CHECK_NULL_CONTINUE(pattern);
        auto preId = pattern->GetNavDestinationId();
        if (preId == navDestinationId) {
            return preNavDestinationInfo.second;
        }
    }
    return nullptr;
}

void NavigationPattern::ClearRecoveryList()
{
    if (!isFinishInteractiveAnimation_) {
        return;
    }
    CHECK_NULL_VOID(navigationStack_);
    navigationStack_->ClearRecoveryList();
}

void NavigationPattern::FireOnNewParam(const RefPtr<UINode>& uiNode)
{
    CHECK_NULL_VOID(uiNode);
    auto navDestination = DynamicCast<NavDestinationGroupNode>(NavigationGroupNode::GetNavDestinationNode(uiNode));
    CHECK_NULL_VOID(navDestination);
    auto navDestinationPattern = navDestination->GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(navDestinationPattern);
    auto navPathInfo = navDestinationPattern->GetNavPathInfo();
    CHECK_NULL_VOID(navPathInfo);
    auto eventHub = navDestination->GetOrCreateEventHub<NavDestinationEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnNewParam(navPathInfo->GetParamObj());
}

void NavigationPattern::GetVisibleNodes(bool isPre, std::vector<WeakPtr<NavDestinationNodeBase>>& visibleNodes)
{
    visibleNodes.clear();
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(navigationNode);
    CHECK_NULL_VOID(navigationStack_);
    const auto& pathList = isPre ?
        navigationStack_->GetPreNavPathList() : navigationStack_->GetAllNavDestinationNodes();
    int32_t lastStandardIndex = navigationNode->GetLastStandardIndex();
    if (lastStandardIndex < 0) {
        auto navBarOrHomeDest =
            AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarOrHomeDestinationNode());
        if (navBarOrHomeDest) {
            visibleNodes.push_back(WeakPtr(navBarOrHomeDest));
        }
        lastStandardIndex = 0;
    }
    for (int32_t idx = lastStandardIndex; idx < static_cast<int32_t>(pathList.size()); ++idx) {
        auto node = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(pathList[idx].second));
        if (!node) {
            continue;
        }
        visibleNodes.push_back(WeakPtr(node));
    }
}

std::optional<int32_t> NavigationPattern::CalcRotateAngleWithDisplayOrientation(
    DisplayOrientation curOri, DisplayOrientation targetOri)
{
    if (curOri == targetOri) {
        return std::nullopt;
    }
    if (!IsValidDisplayOrientation(curOri) || !IsValidDisplayOrientation(targetOri)) {
        return std::nullopt;
    }

    auto curAngle = ConvertDisplayOrientationToRotationAngle(curOri);
    auto targetAngle = ConvertDisplayOrientationToRotationAngle(targetOri);
    int32_t rotationAngle = targetAngle - curAngle;
    if (rotationAngle < 0) {
        rotationAngle += FULL_CIRCLE_ANGLE;
    }
    rotationAngle = rotationAngle % FULL_CIRCLE_ANGLE;
    return rotationAngle;
}

void NavigationPattern::UpdatePageViewportConfigIfNeeded(const RefPtr<NavDestinationGroupNode>& preTopDestination,
    const RefPtr<NavDestinationGroupNode>& topDestination)
{
    if (!IsPageLevelConfigEnabled()) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "conditions are not met, don't update PageViewportConfig");
        return;
    }

    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(navigationNode);
    auto context = navigationNode->GetContext();
    CHECK_NULL_VOID(context);
    auto container = Container::GetContainer(context->GetInstanceId());
    CHECK_NULL_VOID(container);
    auto manager = context->GetWindowManager();
    CHECK_NULL_VOID(manager);

    std::vector<WeakPtr<NavDestinationNodeBase>> newVisibleNodes;
    GetVisibleNodes(false, newVisibleNodes);
    if (preVisibleNodes_.empty() || newVisibleNodes.empty()) {
        return;
    }

    auto preFirstVisibleNode = preVisibleNodes_[0].Upgrade();
    auto curFirstVisibleNode = newVisibleNodes[0].Upgrade();
    if (!preFirstVisibleNode || !curFirstVisibleNode || preFirstVisibleNode == curFirstVisibleNode) {
        return;
    }

    auto preNodeOri = preFirstVisibleNode->GetOrientation();
    auto curNodeOri = curFirstVisibleNode->GetOrientation();
    if (curNodeOri == preNodeOri) {
        return;
    }

    auto statusBarConfig = curFirstVisibleNode->GetStatusBarConfig();
    auto navIndicatorConfig = curFirstVisibleNode->GetNavigationIndicatorConfig();
    std::optional<bool> enableStatusBar;
    std::optional<bool> statusBarAnimated;
    if (statusBarConfig.has_value()) {
        enableStatusBar = statusBarConfig.value().first;
        statusBarAnimated = statusBarConfig.value().second;
    }
    std::optional<bool> enableNavIndicator;
    if (navIndicatorConfig.has_value()) {
        enableNavIndicator = navIndicatorConfig.value();
    }
    auto currConfig = manager->GetCurrentViewportConfig();
    auto config = manager->GetTargetViewportConfig(curNodeOri, enableStatusBar, statusBarAnimated, enableNavIndicator);
    if (!currConfig || !config) {
        return;
    }

    auto curDisplayOrientation = container->GetCurrentDisplayOrientation();
    auto targetDisplayOrientation = config->GetOrientation();
    auto angle = CalcRotateAngleWithDisplayOrientation(curDisplayOrientation, targetDisplayOrientation);
    if (!angle.has_value()) {
        return;
    }

    auto pageNode = AceType::DynamicCast<PageNode>(pageNode_.Upgrade());
    if (pageNode) {
        auto pageConfig = pageNode->GetPageViewportConfig();
        if (!pageConfig) {
            pageNode->SetPageViewportConfig(currConfig->Clone());
        }
    }
    if (!viewportConfig_) {
        SetPageViewportConfig(currConfig->Clone());
    }

    for (auto& weakNode : preVisibleNodes_) {
        auto node = weakNode.Upgrade();
        CHECK_NULL_CONTINUE(node);
        auto preConfig = node->GetPageViewportConfig();
        if (!preConfig) {
            node->SetPageViewportConfig(currConfig->Clone());
            node->SetPageRotateAngle(ROTATION_0);
        }
    }
    for (auto& weakNode : newVisibleNodes) {
        auto node = weakNode.Upgrade();
        CHECK_NULL_CONTINUE(node);
        node->SetPageViewportConfig(config->Clone());
        node->SetPageRotateAngle(angle);
        node->SetIsRotated(false);
    }
}

bool NavigationPattern::IsPageLevelConfigEnabled(bool considerSize)
{
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_NINETEEN)) {
        return false;
    }

    if (!IsEquivalentToStackMode()) {
        return false;
    }
    if (considerSize && !isFullPageNavigation_) {
        return false;
    }
    if (pageNode_.Upgrade() == nullptr) {
        return false;
    }

    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(navigationNode, false);
    auto context = navigationNode->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto manager = context->GetWindowManager();
    CHECK_NULL_RETURN(manager, false);
    auto container = Container::GetContainer(context->GetInstanceId());
    CHECK_NULL_RETURN(container, false);
    if (manager->IsPcOrPadFreeMultiWindowMode() || container->IsUIExtensionWindow()) {
        return false;
    }

    return container->IsMainWindow() && manager->IsFullScreenWindow();
}

void NavigationPattern::OnStartOneTransitionAnimation()
{
    runningTransitionCount_++;
}

void NavigationPattern::OnFinishOneTransitionAnimation()
{
    runningTransitionCount_--;
    if (runningTransitionCount_ == 0) {
        OnAllTransitionAnimationFinish();
    }
}

void NavigationPattern::GetAllNodes(
    std::vector<WeakPtr<NavDestinationNodeBase>>& invisibleNodes,
    std::vector<WeakPtr<NavDestinationNodeBase>>& visibleNodes)
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(navigationNode);
    auto stackNodes = GetAllNavDestinationNodes();
    int32_t lastStandardIndex = navigationNode->GetLastStandardIndex();
    auto navBarOrHomeDest =
        AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarOrHomeDestinationNode());
    if (navBarOrHomeDest) {
        if (lastStandardIndex < 0) {
            visibleNodes.push_back(navBarOrHomeDest);
        } else {
            invisibleNodes.push_back(navBarOrHomeDest);
        }
    }
    for (int32_t idx = 0; idx < static_cast<int32_t>(stackNodes.size()); ++idx) {
        auto node = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(stackNodes[idx].second));
        if (!node) {
            continue;
        }
        if (idx < lastStandardIndex) {
            invisibleNodes.push_back(node);
        } else {
            visibleNodes.push_back(node);
        }
    }
}

void NavigationPattern::OnAllTransitionAnimationFinish()
{
    bool animationAborted = isTransitionAnimationAborted_;
    isTransitionAnimationAborted_ = false;
    if (!IsPageLevelConfigEnabled()) {
        ClearPageAndNavigationConfig();
        return;
    }

    ShowOrRestoreSystemBarIfNeeded();
    std::vector<WeakPtr<NavDestinationNodeBase>> invisibleNodes;
    std::vector<WeakPtr<NavDestinationNodeBase>> visibleNodes;
    GetAllNodes(invisibleNodes, visibleNodes);
    for (auto& weakNode : invisibleNodes) {
        auto node = weakNode.Upgrade();
        CHECK_NULL_CONTINUE(node);
        node->RestoreRenderContext();
    }

    if (visibleNodes.empty()) {
        ClearPageAndNavigationConfig();
        return;
    }
    auto firstVisibleNode = visibleNodes[0].Upgrade();
    CHECK_NULL_VOID(firstVisibleNode);
    auto context = firstVisibleNode->GetContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto navigationMgr = context->GetNavigationManager();
    CHECK_NULL_VOID(navigationMgr);
    auto windowMgr = context->GetWindowManager();
    CHECK_NULL_VOID(windowMgr);
    auto targetOrientation = firstVisibleNode->GetOrientation();
    auto restoreTask = [nodes = std::move(visibleNodes), weakPattern = WeakClaim(this), animationAborted]() {
        ACE_SCOPED_TRACE("NavigationPattern restoreTask");
        for (auto& weakNode : nodes) {
            auto node = weakNode.Upgrade();
            CHECK_NULL_CONTINUE(node);
            node->RestoreRenderContext();
        }

        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->ClearPageAndNavigationConfig();
        if (!animationAborted) {
            return;
        }
        auto pageNode = pattern->GetNavBasePageNode();
        CHECK_NULL_VOID(pageNode);
        auto geometryNode = pageNode->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        geometryNode->ResetParentLayoutConstraint();
    };

    navigationMgr->AddBeforeOrientationChangeTask(std::move(restoreTask));
    windowMgr->SetRequestedOrientation(targetOrientation, false);
}

void NavigationPattern::UpdatePageLevelConfigForSizeChanged()
{
    if (!IsPageLevelConfigEnabled(false)) {
        return;
    }
    if (runningTransitionCount_ > 0) {
        if (isFullPageNavigation_) {
            return;
        }
        // full page -> partial page
        std::vector<WeakPtr<NavDestinationNodeBase>> invisibleNodes;
        std::vector<WeakPtr<NavDestinationNodeBase>> visibleNodes;
        GetAllNodes(invisibleNodes, visibleNodes);
        for (auto& weakNode : invisibleNodes) {
            auto node = weakNode.Upgrade();
            CHECK_NULL_CONTINUE(node);
            node->RestoreRenderContext();
        }
        for (auto& weakNode : visibleNodes) {
            auto node = weakNode.Upgrade();
            CHECK_NULL_CONTINUE(node);
            node->RestoreRenderContext();
            node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
        return;
    }

    UpdatePageLevelConfigForSizeChangedWhenNoAnimation();
}

void NavigationPattern::UpdatePageLevelConfigForSizeChangedWhenNoAnimation()
{
    auto lastNode = GetLastStandardNodeOrNavBar();
    if (!lastNode) {
        return;
    }

    auto context = lastNode->GetContext();
    CHECK_NULL_VOID(context);
    auto mgr = context->GetWindowManager();
    CHECK_NULL_VOID(mgr);

    auto statusBarConfig = lastNode->GetStatusBarConfig();
    std::optional<bool> enableStatusBar;
    std::optional<bool> statusBarAnimated;
    if (isFullPageNavigation_ && statusBarConfig.has_value()) {
        enableStatusBar = statusBarConfig.value().first;
        statusBarAnimated = statusBarConfig.value().second;
    }
    mgr->SetWindowSystemBarEnabled(SystemBarType::STATUS, enableStatusBar, statusBarAnimated);

    auto navIndicatorConfig = lastNode->GetNavigationIndicatorConfig();
    std::optional<bool> enableNavIndicator;
    if (isFullPageNavigation_ && navIndicatorConfig.has_value()) {
        enableNavIndicator = navIndicatorConfig.value();
    }
    mgr->SetWindowSystemBarEnabled(SystemBarType::NAVIGATION_INDICATOR, enableNavIndicator, std::nullopt);

    auto host = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto homeDest = AceType::DynamicCast<NavDestinationNodeBase>(host->GetHomeDestinationNode());
    if (lastNode != homeDest) {
        return;
    }
    auto windowMgr = context->GetWindowManager();
    CHECK_NULL_VOID(windowMgr);
    context->AddAfterLayoutTask([weakNode = WeakPtr(lastNode), weakMgr = WeakPtr(windowMgr)]() {
        auto node = weakNode.Upgrade();
        CHECK_NULL_VOID(node);
        auto manager = weakMgr.Upgrade();
        CHECK_NULL_VOID(manager);
        auto orientation = node->GetOrientation();
        manager->SetRequestedOrientation(orientation, false);
    });
}

RefPtr<NavDestinationNodeBase> NavigationPattern::GetLastStandardNodeOrNavBar()
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(navigationNode, nullptr);
    auto stackNodes = GetAllNavDestinationNodes();
    int32_t lastStandardIndex = navigationNode->GetLastStandardIndex();
    if (lastStandardIndex < 0) {
        return AceType::DynamicCast<NavDestinationNodeBase>(navigationNode->GetNavBarOrHomeDestinationNode());
    } else if (lastStandardIndex < static_cast<int32_t>(stackNodes.size())) {
        return AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(stackNodes[lastStandardIndex].second));
    } else {
        return nullptr;
    }
}

void NavigationPattern::HideSystemBarIfNeeded()
{
    if (!IsPageLevelConfigEnabled()) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "conditions are not met, don't enable/disable SystemBar");
        return;
    }

    auto lastNode = GetLastStandardNodeOrNavBar();
    if (!lastNode || !lastNode->IsSizeMatchNavigation()) {
        return;
    }
    auto context = lastNode->GetContext();
    CHECK_NULL_VOID(context);
    auto mgr = context->GetWindowManager();
    CHECK_NULL_VOID(mgr);

    auto statusBarConfig = lastNode->GetStatusBarConfig();
    if (statusBarConfig.has_value() && !statusBarConfig.value().first) {
        mgr->SetWindowSystemBarEnabled(SystemBarType::STATUS, false, statusBarConfig.value().second);
    }
    auto navIndicatorConfig = lastNode->GetNavigationIndicatorConfig();
    if (navIndicatorConfig.has_value() && !navIndicatorConfig.value()) {
        mgr->SetWindowSystemBarEnabled(SystemBarType::NAVIGATION_INDICATOR, false, false);
    }
}

void NavigationPattern::ShowOrRestoreSystemBarIfNeeded()
{
    if (!IsPageLevelConfigEnabled()) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "conditions are not met, don't enable/disable SystemBar");
        return;
    }

    auto lastNode = GetLastStandardNodeOrNavBar();
    if (!lastNode) {
        return;
    }
    auto context = lastNode->GetContext();
    CHECK_NULL_VOID(context);
    auto mgr = context->GetWindowManager();
    CHECK_NULL_VOID(mgr);

    auto statusBarConfig = lastNode->GetStatusBarConfig();
    if (statusBarConfig.has_value()) {
        if (statusBarConfig.value().first) {
            // If NavDestination explicitly sets the statusBar to be enabled, then we enable the statusBar.
            std::optional<bool> enableStatusBar = true;
            std::optional<bool> animatedStatusBar = statusBarConfig.value().second;
            mgr->SetWindowSystemBarEnabled(SystemBarType::STATUS, enableStatusBar, animatedStatusBar);
        }
    } else {
        /**
         * Otherwise, Arkui informs the window subsystem that the page-level configuration of the statusBar
         * is no longer effective (after which the window decides whether to display the statuBar)
         */
        mgr->SetWindowSystemBarEnabled(SystemBarType::STATUS, std::nullopt, std::nullopt);
    }
    auto navIndicatorConfig = lastNode->GetNavigationIndicatorConfig();
    if (navIndicatorConfig.has_value()) {
        if (navIndicatorConfig.value()) {
            /**
             * If NavDestination explicitly sets the navigationIndicator to be enabled,
             * then we enable the navigationIndicator.
             */
            std::optional<bool> enableNavIndicator = true;
            mgr->SetWindowSystemBarEnabled(SystemBarType::NAVIGATION_INDICATOR, enableNavIndicator, std::nullopt);
        }
    } else {
        /**
         * Otherwise, Arkui informs the window subsystem that the page-level configuration of the navigationIndicator
         * is no longer effective (after which the window decides whether to display the navigationIndicator)
         */
        mgr->SetWindowSystemBarEnabled(SystemBarType::NAVIGATION_INDICATOR, std::nullopt, std::nullopt);
    }
}

bool NavigationPattern::IsEquivalentToStackMode()
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(navigationNode, false);
    auto property = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_RETURN(property, false);
    auto userNavMode = property->GetUsrNavigationModeValue(NavigationMode::AUTO);
    auto hideNavBar = property->GetHideNavBarValue(false);
    if (userNavMode == NavigationMode::STACK || hideNavBar) {
        return true;
    }
    auto homeDest = AceType::DynamicCast<FrameNode>(navigationNode->GetHomeDestinationNode());
    if (homeDest) {
        return navigationMode_ == NavigationMode::STACK;
    }
    auto navBarNode = AceType::DynamicCast<FrameNode>(navigationNode->GetNavBarNode());
    CHECK_NULL_RETURN(navBarNode, false);
    auto navBarProperty = navBarNode->GetLayoutProperty();
    CHECK_NULL_RETURN(navBarProperty, false);
    auto geometry = navBarNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometry, false);
    auto visibility = navBarProperty->GetVisibilityValue(VisibleType::VISIBLE);
    auto size = geometry->GetFrameSize();
    return visibility != VisibleType::VISIBLE || NearEqual(size.Width(), 0.0f) || NearEqual(size.Height(), 0.0f);
}

bool NavigationPattern::CustomizeExpandSafeArea()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    return RunCustomizeExpandIfNeeded(host);
}

void NavigationPattern::SetPageViewportConfig(const RefPtr<PageViewportConfig>& config)
{
    CustomSafeAreaExpander::SetPageViewportConfig(config);
    auto host = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(host);
    do {
        auto contentNode = AceType::DynamicCast<FrameNode>(host->GetContentNode());
        CHECK_NULL_BREAK(contentNode);
        auto contentPattern = contentNode->GetPattern<NavigationContentPattern>();
        CHECK_NULL_BREAK(contentPattern);
        contentPattern->SetPageViewportConfig(config ? config->Clone() : nullptr);
    } while (false);
}

void NavigationPattern::ClearPageAndNavigationConfig()
{
    auto pageNode = AceType::DynamicCast<PageNode>(pageNode_.Upgrade());
    if (pageNode) {
        pageNode->SetPageViewportConfig(nullptr);
    }
    SetPageViewportConfig(nullptr);
}

void NavigationPattern::UpdateNavigationStatus()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameWidth = geometryNode->GetFrameSize().Width();
    auto dividerWidth = static_cast<float>(DIVIDER_WIDTH.ConvertToPx());
    SetNavigationWidthToolBarManager(initNavBarWidth_, frameWidth - initNavBarWidth_ - dividerWidth, dividerWidth);
}

void NavigationPattern::SetNavigationWidthToolBarManager(float navBarWidth, float navDestWidth, float dividerWidth)
{
    CHECK_NULL_VOID(toolbarManager_);
    toolbarManager_->SetNavigationNode(GetNavigationNode());
    auto navBarInfo = toolbarManager_->GetNavBarInfo();
    if (!NearEqual(navBarWidth, navBarInfo.width)) {
        navBarInfo.isShow = true;
        navBarInfo.width = navBarWidth;
        toolbarManager_->SetHasNavBar(true);
        toolbarManager_->SetNavBarInfo(navBarInfo);
        toolbarManager_->SetNavBarNode(GetNavBarNodeOrHomeDestination());
    }
    auto navDestInfo = toolbarManager_->GetNavDestInfo();
    if (!NearEqual(navDestWidth, navDestInfo.width)) {
        navDestInfo.isShow = true;
        navDestInfo.width = navDestWidth;
        toolbarManager_->SetHasNavDest(true);
        toolbarManager_->SetNavDestInfo(navDestInfo);
        toolbarManager_->SetNavDestNode(GetContentNode());
    }
    auto dividerInfo = toolbarManager_->GetNavBarDividerInfo();
    if (!NearEqual(dividerWidth, dividerInfo.width)) {
        dividerInfo.width = dividerWidth;
        toolbarManager_->SetNavBarDividerInfo(dividerInfo);
        toolbarManager_->SetNavBarDividerNode(GetDividerNode());
    }
}

void NavigationPattern::NavigationModifyDoneToolBarManager()
{
    CHECK_NULL_VOID(toolbarManager_);
    toolbarManager_->OnToolBarManagerModifyDone();
}

void NavigationPattern::SetToolbarManagerNavigationMode(NavigationMode mode)
{
    CHECK_NULL_VOID(toolbarManager_);
    auto navigationMode = toolbarManager_->GetNavigationMode();
    if (navigationMode != mode) {
        toolbarManager_->SetNavigationMode(mode);
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "update navigationMode successful, new mode: %{public}d",
            static_cast<int>(mode));
    }
}

bool NavigationPattern::HandleIntent(bool needTransition)
{
    auto host = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto navigationManager = context->GetNavigationManager();
    CHECK_NULL_RETURN(navigationManager, false);
    auto navigationIntentInfo = navigationManager->GetNavigationIntentInfo();
    if (!navigationIntentInfo.has_value()) {
        return false;
    }
    if (navigationIntentInfo.value().navigationInspectorId != host->GetCurId()) {
        return false;
    }
    navigationManager->ResetNavigationIntentInfo();
    // add the intentInfo into navPathStack
    navigationStack_->PushIntentNavDestination(navigationIntentInfo.value().navDestinationName,
        navigationIntentInfo.value().param, needTransition && !navigationIntentInfo.value().isColdStart);
    return true;
}

void NavigationPattern::RegisterForceSplitListener(PipelineContext* context, int32_t nodeId)
{
    CHECK_NULL_VOID(context);
    auto mgr = context->GetNavigationManager();
    CHECK_NULL_VOID(mgr);
    auto listener = [weakPattern = WeakClaim(this)]() {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto hostNode = pattern->GetHost();
        CHECK_NULL_VOID(hostNode);
        hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };
    mgr->AddForceSplitListener(nodeId, std::move(listener));
}

void NavigationPattern::UnregisterForceSplitListener(PipelineContext* context, int32_t nodeId)
{
    CHECK_NULL_VOID(context);
    auto mgr = context->GetNavigationManager();
    CHECK_NULL_VOID(mgr);
    mgr->RemoveForceSplitListener(nodeId);
}

void NavigationPattern::TryForceSplitIfNeeded(const SizeF& frameSize)
{
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    auto context = hostNode->GetContext();
    CHECK_NULL_VOID(context);
    auto navManager = context->GetNavigationManager();
    CHECK_NULL_VOID(navManager);
    if (!navManager->IsForceSplitSupported()) {
        return;
    }

    auto container = Container::GetContainer(context->GetInstanceId());
    CHECK_NULL_VOID(container);
    auto windowManager = context->GetWindowManager();
    CHECK_NULL_VOID(windowManager);
    auto property = hostNode->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_VOID(property);
    bool forceSplitSuccess = false;
    bool forceSplitUseNavBar = false;
    if (navManager->IsForceSplitEnable()) {
        /**
         * The force split mode must meet the following conditions to take effect:
         *   1. Belonging to the main window of the application
         *   2. Belonging to the main page of the application (excluding container model, popups, etc.)
         *   3. The application is in landscape mode
         *   4. The application is not in split screen mode
         *   5. Navigation width greater than 600vp
         *   6. It belongs to the outermost Navigation within the page
         */
        bool isMainWindow = container->IsMainWindow();
        bool isInAppMainPage = pageNode_.Upgrade() != nullptr;
        auto thresholdWidth = SPLIT_THRESHOLD_WIDTH.ConvertToPx();
        auto dipScale = context->GetDipScale();
        auto orientation = SystemProperties::GetDeviceOrientation();
        auto windowMode = windowManager->GetWindowMode();
        bool isInSplitScreenMode = windowMode == WindowMode::WINDOW_MODE_SPLIT_PRIMARY ||
            windowMode == WindowMode::WINDOW_MODE_SPLIT_SECONDARY;
        bool isOuterMostNav = navManager->IsOuterMostNavigation(hostNode->GetId(), hostNode->GetDepth());
        forceSplitSuccess = isMainWindow && isInAppMainPage && isOuterMostNav &&
            orientation == DeviceOrientation::LANDSCAPE && thresholdWidth < frameSize.Width() && !isInSplitScreenMode;
        /**
         * When NavBar is not hidden and its width is greater than 0,
         * it is considered that there is content in NavBar, and NavBar is used as the homepage
         */
        bool navBarHasContent = !property->GetHideNavBarValue(false) &&
            (!userSetNavBarWidthFlag_ || GreatNotEqual(initNavBarWidthValue_.Value(), 0)) &&
            (GreatNotEqual(property->GetMaxNavBarWidthValue(DEFAULT_NAV_BAR_WIDTH).Value(), 0));
        forceSplitUseNavBar = forceSplitSuccess && navBarHasContent;
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "calc splitMode, isMainWindow:%{public}d, isInAppMainPage:%{public}d, "
            "isInSplitScreenMode:%{public}d, isOuterMostNav:%{public}d, orientation: %{public}s, dipScale: %{public}f, "
            "thresholdWidth: %{public}f, curWidth: %{public}f, navBarHasContent:%{public}d, "
            "forceSplitSuccess:%{public}d, forceSplitUseNavBar:%{public}d", isMainWindow, isInAppMainPage,
            isInSplitScreenMode, isOuterMostNav, DeviceOrientationToString(orientation), dipScale, thresholdWidth,
            frameSize.Width(), navBarHasContent, forceSplitSuccess, forceSplitUseNavBar);
    }
    if (forceSplitSuccess == forceSplitSuccess_ && forceSplitUseNavBar_ == forceSplitUseNavBar) {
        return;
    }
    forceSplitSuccess_ = forceSplitSuccess;
    forceSplitUseNavBar_ = forceSplitUseNavBar;
    SwapNavDestinationAndPlaceHolder(true);
}

void NavigationPattern::SwapNavDestinationAndPlaceHolder(bool needFireLifecycle)
{
    if (forceSplitSuccess_ && !forceSplitUseNavBar_) {
        // switch to ForceSplit mode(use NavDestination as homepage)
        AdjustNodeForDestForceSplit(needFireLifecycle);
    } else {
        // switch to Non-forceSplit mode or ForceSplit mode but use NavBar as homepage.
        AdjustNodeForNonDestForceSplit(needFireLifecycle);
    }
}

void NavigationPattern::CalcNavDestinationNodeIndex(std::vector<RefPtr<NavDestinationGroupNode>>& destNodes,
    int32_t& homeNodeIndex, int32_t& lastStandardIndex)
{
    homeNodeIndex = -1;
    lastStandardIndex = -1;
    auto homeNode = homeNode_.Upgrade();
    const auto& stackNodePairs = GetAllNavDestinationNodes();
    for (int32_t idx = 0; idx < static_cast<int32_t>(stackNodePairs.size()); ++idx) {
        auto node = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(stackNodePairs[idx].second));
        CHECK_NULL_CONTINUE(node);
        auto curIdx = static_cast<int32_t>(destNodes.size());
        if (node == homeNode) {
            homeNodeIndex = curIdx;
        }
        if (node->GetNavDestinationMode() == NavDestinationMode::STANDARD) {
            lastStandardIndex = curIdx;
        }
        destNodes.push_back(node);
    }
}

void NavigationPattern::AdjustNodeForDestForceSplit(bool needFireLifecycle)
{
    auto host = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto navBar = host->GetNavBarNode();
    CHECK_NULL_VOID(navBar);
    auto navContentNode = AceType::DynamicCast<FrameNode>(host->GetContentNode());
    CHECK_NULL_VOID(navContentNode);
    auto primaryContentNode = AceType::DynamicCast<FrameNode>(host->GetPrimaryContentNode());
    CHECK_NULL_VOID(primaryContentNode);

    auto prePrimaryNodes = primaryNodes_;
    primaryNodes_.clear();
    int32_t homeNodeIndex = -1;
    int32_t lastStandardIndex = -1;
    std::vector<RefPtr<NavDestinationGroupNode>> destNodes;
    CalcNavDestinationNodeIndex(destNodes, homeNodeIndex, lastStandardIndex);
    if (destNodes.empty() || homeNodeIndex > lastStandardIndex) {
        return;
    }

    AdjustPrimaryAndPlaceHolderPosition(primaryContentNode, navContentNode,
        destNodes, homeNodeIndex, lastStandardIndex);

    ReorderPrimaryNodes(primaryContentNode, primaryNodes_);

    if (needFireLifecycle) {
        FirePrimaryNodesLifecycle(NavDestinationLifecycle::ON_SHOW);
    }
    if (primaryNodes_.empty()) {
        host->AddChild(navBar);
    } else {
        host->RemoveChild(navBar);
    }

    UpdatePrimaryContentIfNeeded(primaryContentNode, prePrimaryNodes);
}

void NavigationPattern::AdjustPrimaryAndPlaceHolderPosition(
    const RefPtr<FrameNode>& primaryContentNode, const RefPtr<FrameNode>& navContentNode,
    const std::vector<RefPtr<NavDestinationGroupNode>>& destNodes, int32_t homeNodeIndex, int32_t lastStandardIndex)
{
    bool hasPlaceHolderVisible = false;
    if (homeNodeIndex < 0 || homeNodeIndex == lastStandardIndex) {
        for (int32_t index = static_cast<int32_t>(destNodes.size()) - 1; index >= 0; --index) {
            auto node = destNodes[index];
            if (index >= lastStandardIndex) {
                ReplaceNodeWithPlaceHolder(navContentNode, node, !hasPlaceHolderVisible);
                hasPlaceHolderVisible = true;
                primaryNodes_.insert(primaryNodes_.begin(), node);
            } else {
                RestoreNodeFromPlaceHolder(primaryContentNode, navContentNode, node);
            }
        }
        return;
    }

    // homeNodeIndex < lastStandardIndex
    bool meetNextStandard = false;
    for (int32_t index = 0; index < static_cast<int32_t>(destNodes.size()); ++index) {
        auto node = destNodes[index];
        if (index < homeNodeIndex || index >= lastStandardIndex) {
            RestoreNodeFromPlaceHolder(primaryContentNode, navContentNode, node);
            continue;
        }
        if (index == homeNodeIndex) {
            ReplaceNodeWithPlaceHolder(navContentNode, node, false);
            primaryNodes_.push_back(node);
            continue;
        }
        if (node->GetNavDestinationMode() == NavDestinationMode::STANDARD) {
            meetNextStandard = true;
        }
        if (!meetNextStandard) {
            ReplaceNodeWithPlaceHolder(navContentNode, node, false);
            primaryNodes_.push_back(node);
        } else {
            RestoreNodeFromPlaceHolder(primaryContentNode, navContentNode, node);
        }
    }
}

void NavigationPattern::UpdatePrimaryContentIfNeeded(const RefPtr<FrameNode>& primaryContentNode,
    const std::vector<WeakPtr<NavDestinationGroupNode>>& prePrimaryNodes)
{
    CHECK_NULL_VOID(primaryContentNode);
    auto property = primaryContentNode->GetLayoutProperty();
    CHECK_NULL_VOID(property);
    property->UpdateVisibility(primaryNodes_.empty() ? VisibleType::INVISIBLE : VisibleType::VISIBLE);

    bool needMarkDirty = false;
    if (prePrimaryNodes.size() != primaryNodes_.size()) {
        needMarkDirty = true;
    } else {
        for (size_t idx = 0; idx < prePrimaryNodes.size(); ++idx) {
            auto preNode = prePrimaryNodes[idx].Upgrade();
            auto curNode = primaryNodes_[idx].Upgrade();
            if (preNode != curNode) {
                needMarkDirty = true;
                break;
            }
        }
    }
    if (needMarkDirty) {
        primaryContentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        primaryContentNode->MarkNeedSyncRenderTree();
    }
}

void NavigationPattern::AdjustNodeForNonDestForceSplit(bool needFireLifecycle)
{
    auto host = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto navBar = host->GetNavBarNode();
    CHECK_NULL_VOID(navBar);
    auto navContentNode = AceType::DynamicCast<FrameNode>(host->GetContentNode());
    CHECK_NULL_VOID(navContentNode);
    auto primaryContentNode = AceType::DynamicCast<FrameNode>(host->GetPrimaryContentNode());
    CHECK_NULL_VOID(primaryContentNode);

    if (needFireLifecycle) {
        FirePrimaryNodesLifecycle(NavDestinationLifecycle::ON_HIDE);
    }
    const auto& stackNodePairs = GetAllNavDestinationNodes();
    primaryNodes_.clear();
    for (int32_t index = (int32_t)(stackNodePairs.size() - 1); index >= 0; index--) {
        auto node = AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(stackNodePairs[index].second));
        CHECK_NULL_CONTINUE(node);
        RestoreNodeFromPlaceHolder(primaryContentNode, navContentNode, node);
    }
    host->AddChild(navBar);
}

bool NavigationPattern::IsDestinationNeedHideInPush(
    const RefPtr<NavigationGroupNode>& hostNode, const RefPtr<NavDestinationGroupNode>& destNode) const
{
    CHECK_NULL_RETURN(hostNode, false);
    CHECK_NULL_RETURN(destNode, false);
    if (destNode->NeedRemoveInPush()) {
        return true;
    }
    if (destNode->GetIndex() >= hostNode->GetLastStandardIndex()) {
        return false;
    }
    if (destNode->IsShowInPrimaryPartition()) {
        return false;
    }
    return true;
}

void NavigationPattern::FirePrimaryNodesLifecycle(NavDestinationLifecycle lifecycle)
{
    if (lifecycle != NavDestinationLifecycle::ON_SHOW && lifecycle != NavDestinationLifecycle::ON_HIDE) {
        return;
    }
    auto navigation = DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(navigation);
    auto homeNode = homeNode_.Upgrade();
    CHECK_NULL_VOID(homeNode);
    if (homeNode->GetIndex() >= navigation->GetLastStandardIndex()) {
        return;
    }
    std::vector<WeakPtr<NavDestinationGroupNode>> primaryNodes;
    if (lifecycle == NavDestinationLifecycle::ON_SHOW) {
        primaryNodes = primaryNodes_;
        for (size_t idx = 0; idx < primaryNodes.size(); ++idx) {
            auto node = primaryNodes[idx].Upgrade();
            CHECK_NULL_CONTINUE(node);
            auto pattern = node->GetPattern<NavDestinationPattern>();
            CHECK_NULL_CONTINUE(pattern);
            if (!pattern->GetIsOnShow()) {
                NotifyDestinationLifecycle(node, NavDestinationLifecycle::ON_SHOW);
                pattern->SetIsOnShow(true);
            }
            if (idx == primaryNodes.size() - 1 && !pattern->IsActive()) {
                NotifyDestinationLifecycle(node,
                    NavDestinationLifecycle::ON_ACTIVE, NavDestinationActiveReason::TRANSITION);
                pattern->SetIsActive(true);
            }
        }
        return;
    }

    std::copy(primaryNodes_.rbegin(), primaryNodes_.rend(), std::back_inserter(primaryNodes));
    for (size_t idx = 0; idx < primaryNodes.size(); ++idx) {
        auto node = primaryNodes[idx].Upgrade();
        CHECK_NULL_CONTINUE(node);
        auto pattern = node->GetPattern<NavDestinationPattern>();
        CHECK_NULL_CONTINUE(pattern);
        if (idx == 0 && pattern->IsActive()) {
            NotifyDestinationLifecycle(node,
                NavDestinationLifecycle::ON_INACTIVE, NavDestinationActiveReason::TRANSITION);
            pattern->SetIsActive(false);
        }
        if (pattern->GetIsOnShow()) {
            NotifyDestinationLifecycle(node, NavDestinationLifecycle::ON_HIDE);
            pattern->SetIsOnShow(false);
        }
    }
}

bool NavigationPattern::IsPrimaryNode(const RefPtr<NavDestinationGroupNode>& destNode) const
{
    return std::find_if(primaryNodes_.begin(), primaryNodes_.end(),
        [destNode](WeakPtr<NavDestinationGroupNode> primaryNode) {
            return destNode == primaryNode.Upgrade();
        }) != primaryNodes_.end();
}

void NavigationPattern::FirePreTopPrimaryNodeInactiveIfNeeded()
{
    if (prePrimaryNodes_.empty()) {
        return;
    }
    auto preTopPrimaryNode = prePrimaryNodes_.back().Upgrade();
    CHECK_NULL_VOID(preTopPrimaryNode);
    if (!preTopPrimaryNode->IsActive()) {
        return;
    }
    RefPtr<NavDestinationGroupNode> topPrimaryNode = nullptr;
    if (!primaryNodes_.empty()) {
        topPrimaryNode = primaryNodes_.back().Upgrade();
    }
    RefPtr<NavDestinationGroupNode> topNode = nullptr;
    if (navigationStack_) {
        const auto& nodeList = navigationStack_->GetAllNavDestinationNodes();
        topNode = nodeList.empty() ? nullptr : AceType::DynamicCast<NavDestinationGroupNode>(
            NavigationGroupNode::GetNavDestinationNode(nodeList.back().second));
    }
    if (preTopPrimaryNode != topPrimaryNode && preTopPrimaryNode != topNode) {
        NotifyDestinationLifecycle(preTopPrimaryNode,
            NavDestinationLifecycle::ON_INACTIVE, NavDestinationActiveReason::TRANSITION);
    }
}

void NavigationPattern::FirePrePrimaryNodesOnHide()
{
    std::vector<RefPtr<NavDestinationGroupNode>> nodeNeedToHide;
    for (auto it = prePrimaryNodes_.rbegin(); it != prePrimaryNodes_.rend(); ++it) {
        auto node = it->Upgrade();
        CHECK_NULL_CONTINUE(node);
        auto pattern = node->GetPattern<NavDestinationPattern>();
        CHECK_NULL_CONTINUE(pattern);
        if (!node->IsShowInPrimaryPartition() && pattern->GetIsOnShow()) {
            NotifyDestinationLifecycle(node, NavDestinationLifecycle::ON_HIDE);
        }
    }

    for (auto& primaryNode : primaryNodesToBeRemoved_) {
        CHECK_NULL_CONTINUE(primaryNode);
        auto pattern = primaryNode->GetPattern<NavDestinationPattern>();
        CHECK_NULL_CONTINUE(pattern);
        if (!pattern->GetIsOnShow()) {
            continue;
        }
        NotifyDestinationLifecycle(primaryNode, NavDestinationLifecycle::ON_HIDE);
    }
}

void NavigationPattern::FirePrePrimaryNodesOnWillDisappear(std::set<RefPtr<NavDestinationGroupNode>>&& filterNodes)
{
    for (auto& primaryNode : primaryNodesToBeRemoved_) {
        CHECK_NULL_CONTINUE(primaryNode);
        if (filterNodes.find(primaryNode) != filterNodes.end()) {
            continue;
        }
        NotifyDestinationLifecycle(primaryNode, NavDestinationLifecycle::ON_WILL_DISAPPEAR);
    }
}

void NavigationPattern::FirePrimaryNodesOnShowAndActive()
{
    RefPtr<NavDestinationGroupNode> topNode = nullptr;
    for (auto it = primaryNodes_.begin(); it != primaryNodes_.end(); ++it) {
        auto node = it->Upgrade();
        CHECK_NULL_CONTINUE(node);
        auto pattern = node->GetPattern<NavDestinationPattern>();
        CHECK_NULL_CONTINUE(pattern);
        if (!pattern->GetIsOnShow()) {
            NotifyDestinationLifecycle(node, NavDestinationLifecycle::ON_SHOW);
        }
        topNode = node;
    }
    CHECK_NULL_VOID(topNode);
    auto pattern = topNode->GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(pattern);
    if (!pattern->IsActive()) {
        NotifyDestinationLifecycle(topNode, NavDestinationLifecycle::ON_ACTIVE, NavDestinationActiveReason::TRANSITION);
    }
}

void NavigationPattern::RemoveRedundantPrimaryNavDestination()
{
    auto host = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto primaryContentNode = host->GetPrimaryContentNode();
    CHECK_NULL_VOID(primaryContentNode);
    bool hasRemoveNode = false;
    while (primaryContentNode->GetChildren().size() > primaryNodes_.size()) {
        auto lastNode = AceType::DynamicCast<NavDestinationGroupNode>(primaryContentNode->GetLastChild());
        CHECK_NULL_CONTINUE(lastNode);
        lastNode->CleanContent();
        primaryContentNode->RemoveChild(lastNode, true);
        hasRemoveNode = true;
    }
    if (hasRemoveNode) {
        primaryContentNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
        primaryContentNode->MarkNeedSyncRenderTree();
    }
}

bool NavigationPattern::IsHomeDestinationVisible()
{
    auto host = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_RETURN(host, false);
    auto property = host->GetLayoutProperty<NavigationLayoutProperty>();
    CHECK_NULL_RETURN(property, false);
    if (property->GetHideNavBarValue(false)) {
        return false;
    }
    if (navigationMode_ == NavigationMode::STACK) {
        CHECK_NULL_RETURN(navigationStack_, false);
        return navigationStack_->Empty();
    }
    return navigationMode_ == NavigationMode::SPLIT;
}

bool NavigationPattern::ShouldFireHomeDestiationLifecycle(NavDestinationLifecycle lifecycle,
    const RefPtr<NavDestinationPattern>& destPattern, int32_t lastStandardIndex,
    int32_t curStackSize, bool isModeChange)
{
    if (isModeChange || navigationMode_ == NavigationMode::SPLIT) {
        switch (lifecycle) {
            case NavDestinationLifecycle::ON_SHOW:
                return !destPattern->GetIsOnShow();
            case NavDestinationLifecycle::ON_ACTIVE:
                return !destPattern->IsActive();
            case NavDestinationLifecycle::ON_INACTIVE:
                return destPattern->IsActive();
            case NavDestinationLifecycle::ON_HIDE:
                return destPattern->GetIsOnShow();
            default:
                return false;
        }
    }
    if (navigationMode_ == NavigationMode::STACK) {
        switch (lifecycle) {
            case NavDestinationLifecycle::ON_SHOW:
                return lastStandardIndex < 0 && !destPattern->GetIsOnShow();
            case NavDestinationLifecycle::ON_ACTIVE:
                return curStackSize == 0 && !destPattern->IsActive();
            case NavDestinationLifecycle::ON_INACTIVE:
                return curStackSize == 0 && destPattern->IsActive();
            case NavDestinationLifecycle::ON_HIDE:
                return lastStandardIndex < 0 && destPattern->GetIsOnShow();
            default:
                return false;
        }
    }
    return false;
}

void NavigationPattern::FireHomeDestinationLifeCycleIfNeeded(
    NavDestinationLifecycle lifecycle, bool isModeChange, NavDestinationActiveReason reason)
{
    auto host = AceType::DynamicCast<NavigationGroupNode>(GetHost());
    CHECK_NULL_VOID(host);
    auto destNode = AceType::DynamicCast<NavDestinationGroupNode>(host->GetHomeDestinationNode());
    CHECK_NULL_VOID(destNode);
    auto destPattern = destNode->GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(destPattern);
    auto lastStandardIndex = host->GetLastStandardIndex();
    int32_t curStackSize = static_cast<int32_t>(GetAllNavDestinationNodes().size());
    if (!ShouldFireHomeDestiationLifecycle(lifecycle, destPattern, lastStandardIndex, curStackSize, isModeChange)) {
        return;
    }
    NotifyDestinationLifecycle(destNode, lifecycle, reason);
}
} // namespace OHOS::Ace::NG
