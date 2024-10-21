/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/navigation/navdestination_pattern_base.h"

#include "core/components_ng/pattern/navigation/navdestination_node_base.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_ANIMATION_DURATION = 500;
} // namespace

void NavDestinationPatternBase::SetTitleBarStyle(const std::optional<BarStyle>& barStyle)
{
    if (titleBarStyle_ != barStyle) {
        if (barStyle.value_or(BarStyle::STANDARD) == BarStyle::SAFE_AREA_PADDING ||
            titleBarStyle_.value_or(BarStyle::STANDARD) == BarStyle::SAFE_AREA_PADDING) {
            safeAreaPaddingChanged_ = true;
        }
        titleBarStyle_ = barStyle;
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    }
}

void NavDestinationPatternBase::SetToolBarStyle(const std::optional<BarStyle>& barStyle)
{
    if (toolBarStyle_ != barStyle) {
        if (barStyle.value_or(BarStyle::STANDARD) == BarStyle::SAFE_AREA_PADDING ||
            toolBarStyle_.value_or(BarStyle::STANDARD) == BarStyle::SAFE_AREA_PADDING) {
            safeAreaPaddingChanged_ = true;
        }
        toolBarStyle_ = barStyle;
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    }
}

bool NavDestinationPatternBase::UpdateBarSafeAreaPadding()
{
    if (!safeAreaPaddingChanged_) {
        return false;
    }
    safeAreaPaddingChanged_ = false;
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(GetHost());
    CHECK_NULL_RETURN(navBarNode, false);
    auto contentNode = AceType::DynamicCast<FrameNode>(navBarNode->GetContentNode());
    CHECK_NULL_RETURN(contentNode, false);
    auto contentLayoutProperty = contentNode->GetLayoutProperty();
    CHECK_NULL_RETURN(contentLayoutProperty, false);

    Dimension paddingTop = 0.0_vp;
    if (titleBarStyle_.value_or(BarStyle::STANDARD) == BarStyle::SAFE_AREA_PADDING) {
        paddingTop = GetTitleBarHeightBeforeMeasure();
    }
    Dimension paddingBottom = 0.0_vp;
    if (toolBarStyle_.value_or(BarStyle::STANDARD) == BarStyle::SAFE_AREA_PADDING && !isHideToolbar_) {
        paddingBottom = NavigationGetTheme()->GetHeight();
    }
    PaddingProperty paddingProperty;
    paddingProperty.left = CalcLength(0.0_vp);
    paddingProperty.right = CalcLength(0.0_vp);
    paddingProperty.top = CalcLength(paddingTop);
    paddingProperty.bottom = CalcLength(paddingBottom);

    contentLayoutProperty->UpdateSafeAreaPadding(paddingProperty);
    return true;
}

void NavDestinationPatternBase::HandleTitleBarAndToolBarAnimation(const RefPtr<NavDestinationNodeBase>& navNodeBase,
    bool needRunTitleBarAnimation, bool needRunToolBarAnimation)
{
    // take care of init and start animation action
    if (!needRunToolBarAnimation && !needRunTitleBarAnimation) {
        return;
    }

    auto navBarLayoutProperty = navNodeBase->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    InitStateBeforeAnimation(
        navNodeBase, needRunTitleBarAnimation, needRunToolBarAnimation);

    StartAnimation(needRunTitleBarAnimation, navBarLayoutProperty->GetHideTitleBarValue(false), needRunToolBarAnimation,
        navBarLayoutProperty->GetHideToolBarValue(false));
}

void NavDestinationPatternBase::InitStateBeforeAnimation(const RefPtr<NavDestinationNodeBase>& hostNode,
    bool needRunTitleBarAnimation, bool needRunToolBarAnimation)
{
    CHECK_NULL_VOID(hostNode);
    auto navBarPattern = hostNode->GetPattern<NavDestinationPatternBase>();
    CHECK_NULL_VOID(navBarPattern);
    auto context = hostNode->GetContext();
    CHECK_NULL_VOID(context);
    auto navBarLayoutProperty = hostNode->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    auto showTitleBar = !navBarLayoutProperty->GetHideTitleBarValue(false) && needRunTitleBarAnimation;
    auto showToolBar = !navBarLayoutProperty->GetHideToolBarValue(false) && needRunToolBarAnimation;

    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty();

    auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(hostNode->GetToolBarNode());
    auto toolBarLayoutProperty = toolBarNode->GetLayoutProperty();
    auto toolBarDividerNode = AceType::DynamicCast<FrameNode>(hostNode->GetToolBarDividerNode());

    if ((!showTitleBar || navBarPattern->GetTitleBarAnimationCount() > 0) &&
        (!showToolBar || navBarPattern->GetToolBarAnimationCount() > 0)) {
        return;
    }

    if (showTitleBar && IsNoTitleBarInAnimation(navBarPattern)) {
        navBarPattern->SetForceMeasureTitleBar(true);
        UpdateTitleBarProperty(navBarLayoutProperty, false, hostNode);
    }
    if (showToolBar && IsNoToolBarInAnimation(navBarPattern)) {
        navBarPattern->SetForceMeasureToolBar(true);
        UpdateToolBarAndDividerProperty(navBarLayoutProperty, false, hostNode);
    }

    hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    context->FlushUITasks();

    if (showTitleBar && titleBarNode && IsNoTitleBarInAnimation(navBarPattern)) {
        navBarPattern->SetForceMeasureTitleBar(false);
        UpdateTitleBarTranslateAndOpacity(true, titleBarNode, navBarPattern->GetTitleBarHeight());
    }
    if (showToolBar && toolBarNode && toolBarDividerNode &&
        IsNoToolBarInAnimation(navBarPattern)) {
        navBarPattern->SetForceMeasureToolBar(false);
        UpdateToolBarAndDividerTranslateAndOpacity(true, toolBarNode,
            navBarPattern->GetToolBarHeight(), toolBarDividerNode, navBarPattern->GetToolBarDividerHeight());
    }
}

bool NavDestinationPatternBase::IsNoTitleBarInAnimation(const RefPtr<NavDestinationPatternBase>& navBarPattern)
{
    if (navBarPattern->GetTitleBarAnimationCount() == 0) {
        return true;
    }
    return false;
}

bool NavDestinationPatternBase::IsNoToolBarInAnimation(const RefPtr<NavDestinationPatternBase>& navBarPattern)
{
    if (navBarPattern->GetToolBarAnimationCount() == 0) {
        return true;
    }
    return false;
}

void NavDestinationPatternBase::UpdateTitleBarProperty(const RefPtr<LayoutProperty>& navBarLayoutProperty, bool hide,
    const RefPtr<NavDestinationNodeBase>& hostNode)
{
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    if (hide) {
        titleBarLayoutProperty->UpdateVisibility(VisibleType::GONE);
        titleBarNode->SetJSViewActive(false);
    } else {
        titleBarLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
        titleBarNode->SetJSViewActive(true);
        auto&& opts = navBarLayoutProperty->GetSafeAreaExpandOpts();
        if (opts) {
            titleBarLayoutProperty->UpdateSafeAreaExpandOpts(*opts);
        }
    }
}

void NavDestinationPatternBase::UpdateTitleBarTranslateAndOpacity(
    bool hide, const RefPtr<TitleBarNode>& titleBarNode, float titleBarHeight)
{
    if (titleBarNode) {
        auto renderContext = titleBarNode->GetRenderContext();
        if (renderContext) {
            auto offset = renderContext->GetTranslateXYProperty();
            offset.SetY(hide ? -titleBarHeight : 0.0f);
            renderContext->UpdateTranslateInXY(offset);
            renderContext->UpdateOpacity(hide ? 0.0f : 1.0f);
        }
    }
}

void NavDestinationPatternBase::UpdateToolBarAndDividerProperty(const RefPtr<LayoutProperty>& navBarLayoutProperty,
    bool hide, const RefPtr<NavDestinationNodeBase>& hostNode)
{
    auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(hostNode->GetToolBarNode());
    CHECK_NULL_VOID(toolBarNode);
    auto toolBarLayoutProperty = toolBarNode->GetLayoutProperty();
    CHECK_NULL_VOID(toolBarLayoutProperty);
    auto toolBarDividerNode = AceType::DynamicCast<FrameNode>(hostNode->GetToolBarDividerNode());
    RefPtr<LayoutProperty> toolBarDividerLayoutProperty = nullptr;
    if (toolBarDividerNode) {
        toolBarDividerLayoutProperty = toolBarDividerNode->GetLayoutProperty();
    }
    if (hide || !toolBarNode->HasValidContent()) {
        toolBarLayoutProperty->UpdateVisibility(VisibleType::GONE);
        toolBarNode->SetActive(false);
        if (toolBarDividerLayoutProperty) {
            toolBarDividerLayoutProperty->UpdateVisibility(VisibleType::GONE);
        }
    } else {
        toolBarLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
        toolBarNode->SetActive(true);
        if (toolBarDividerLayoutProperty) {
            toolBarDividerLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
        }

        auto&& opts = navBarLayoutProperty->GetSafeAreaExpandOpts();
        if (opts) {
            toolBarLayoutProperty->UpdateSafeAreaExpandOpts(*opts);
        }
    }
}

void NavDestinationPatternBase::UpdateToolBarAndDividerTranslateAndOpacity(bool hide,
    const RefPtr<NavToolbarNode>& toolBarNode, float toolBarHeight, const RefPtr<FrameNode>& toolbarDividerNode,
    float toolBarDividerHeight)
{
    float opacity = hide ? 0.0f : 1.0f;
    float offsetY = hide ? (toolBarHeight + toolBarDividerHeight) : 0;
    if (toolBarNode) {
        auto renderContext = toolBarNode->GetRenderContext();
        if (renderContext) {
            renderContext->UpdateTranslateInXY({ 0.0f, offsetY });
            renderContext->UpdateOpacity(opacity);
        }
    }
    if (toolbarDividerNode) {
        auto dividerContext = toolbarDividerNode->GetRenderContext();
        if (dividerContext) {
            dividerContext->UpdateTranslateInXY({ 0.0f, offsetY });
            dividerContext->UpdateOpacity(opacity);
        }
    }
}

void NavDestinationPatternBase::HideOrShowTitleBarImmediately(const RefPtr<NavDestinationNodeBase>& hostNode, bool hide)
{
    auto navBarPattern = hostNode->GetPattern<NavDestinationPatternBase>();
    CHECK_NULL_VOID(navBarPattern);
    auto navBarLayoutProperty = hostNode->GetLayoutProperty();
    CHECK_NULL_VOID(navBarLayoutProperty);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    UpdateTitleBarProperty(navBarLayoutProperty, hide, hostNode);
    UpdateTitleBarTranslateAndOpacity(hide, titleBarNode, navBarPattern->GetTitleBarHeight());
    titleBarNode->MarkModifyDone();
    titleBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

void NavDestinationPatternBase::HideOrShowToolBarImmediately(const RefPtr<NavDestinationNodeBase>& hostNode, bool hide)
{
    auto navDestinationPatternBase = hostNode->GetPattern<NavDestinationPatternBase>();
    CHECK_NULL_VOID(navDestinationPatternBase);
    auto navBarLayoutProperty = hostNode->GetLayoutProperty();
    CHECK_NULL_VOID(navBarLayoutProperty);
    auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(hostNode->GetToolBarNode());
    CHECK_NULL_VOID(toolBarNode);
    auto toolBarDividerNode = AceType::DynamicCast<FrameNode>(hostNode->GetToolBarDividerNode());
    UpdateToolBarAndDividerProperty(navBarLayoutProperty, hide, hostNode);
    UpdateToolBarAndDividerTranslateAndOpacity(hide, toolBarNode, GetToolBarHeight(),
        toolBarDividerNode, GetToolBarDividerHeight());
    toolBarNode->MarkModifyDone();
    toolBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

void NavDestinationPatternBase::StartAnimation(
    bool needRunTitleBarAnimation, bool hideTitle, bool needRunToolBarAnimation, bool hideTool)
{
    auto propertyCallback = [needRunTitleBarAnimation, hideTitle, needRunToolBarAnimation, hideTool,
                                weakPattern = AceType::WeakClaim(this)]() {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(pattern->GetHost());
        CHECK_NULL_VOID(navBarNode);
        auto context = navBarNode->GetContext();
        CHECK_NULL_VOID(context);
        auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
        auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(navBarNode->GetToolBarNode());
        auto toolBarDividerNode = AceType::DynamicCast<FrameNode>(navBarNode->GetToolBarDividerNode());
        if (needRunTitleBarAnimation && titleBarNode) {
            if (hideTitle) {
                pattern->SetForceMeasureTitleBar(true);
            }
        }
        if (needRunToolBarAnimation && toolBarNode) {
            if (hideTool) {
                pattern->SetForceMeasureToolBar(true);
            }
        }

        navBarNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        context->FlushUITasks();

        if (needRunTitleBarAnimation && titleBarNode) {
            pattern->UpdateTitleBarTranslateAndOpacity(hideTitle, titleBarNode, pattern->GetTitleBarHeight());
        }
        if (needRunToolBarAnimation && toolBarNode) {
            pattern->UpdateToolBarAndDividerTranslateAndOpacity(hideTool, toolBarNode, pattern->GetToolBarHeight(),
                toolBarDividerNode, pattern->GetToolBarDividerHeight());
        }
    };
    auto finishCallback = [needRunTitleBarAnimation, needRunToolBarAnimation,
                              weakPattern = AceType::WeakClaim(this)]() {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (needRunTitleBarAnimation) {
            pattern->OnTitleBarAnimationFinish();
        }
        if (needRunToolBarAnimation) {
            pattern->OnToolBarAnimationFinish();
        }
    };

    AnimationOption option;
    option.SetCurve(Curves::FAST_OUT_SLOW_IN);
    option.SetDuration(DEFAULT_ANIMATION_DURATION);
    HandleStartAnimation(needRunTitleBarAnimation, needRunToolBarAnimation);
    AnimationUtils::StartAnimation(option, propertyCallback, finishCallback);
}

void NavDestinationPatternBase::HandleStartAnimation(bool needRunTitleBarAnimation, bool needRunToolBarAnimation)
{
    if (needRunTitleBarAnimation) {
        OnTitleBarAnimationStart();
    }
    if (needRunToolBarAnimation) {
        OnToolBarAnimationStart();
    }
}

void NavDestinationPatternBase::OnTitleBarAnimationFinish()
{
    titleBarAnimationCount_--;
    if (titleBarAnimationCount_ > 0) {
        return;
    }

    SetForceMeasureTitleBar(false);
    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(GetHost());
    CHECK_NULL_VOID(navBarNode);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    CHECK_NULL_VOID(navBarLayoutProperty);
    HideOrShowTitleBarImmediately(navBarNode, navBarLayoutProperty->GetHideTitleBarValue(false));
}

void NavDestinationPatternBase::OnToolBarAnimationFinish()
{
    toolBarAnimationCount_--;
    if (toolBarAnimationCount_ > 0) {
        return;
    }

    SetForceMeasureToolBar(false);
    auto nodeBase = AceType::DynamicCast<NavDestinationNodeBase>(GetHost());
    CHECK_NULL_VOID(nodeBase);
    auto propertyBase = nodeBase->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    CHECK_NULL_VOID(propertyBase);
    HideOrShowToolBarImmediately(nodeBase, propertyBase->GetHideToolBarValue(false));
}
} // namespace OHOS::Ace::NG