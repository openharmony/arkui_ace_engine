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
#include "core/components_ng/pattern/navigation/navigation_title_util.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_ANIMATION_DURATION = 500;
} // namespace

void NavDestinationPatternBase::SetTitleBarStyle(const std::optional<BarStyle>& barStyle)
{
    if (titleBarStyle_ != barStyle) {
        // Mark need update safeAreaPadding when it is enabled or disabled.
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
        // Mark need update safeAreaPadding when it is enabled or disabled.
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

void NavDestinationPatternBase::UpdateLayoutPropertyBeforeAnimation(const RefPtr<NavDestinationNodeBase>& navNodeBase,
    bool needRunTitleBarAnimation, bool needRunToolBarAnimation, bool hideTitleBar, bool hideToolBar)
{
    CHECK_NULL_VOID(navNodeBase);
    auto property = navNodeBase->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    CHECK_NULL_VOID(property);
    if (needRunTitleBarAnimation && titleBarAnimationCount_ == 0) {
        property->UpdateTitleBarTranslateState(hideTitleBar ?
            BarTranslateState::TRANSLATE_ZERO : BarTranslateState::TRANSLATE_HEIGHT);
        if (!hideTitleBar) {
            UpdateTitleBarProperty(property, false, navNodeBase);
        }
    }
    if (needRunToolBarAnimation && toolBarAnimationCount_ == 0) {
        property->UpdateToolBarTranslateState(hideToolBar ?
            BarTranslateState::TRANSLATE_ZERO : BarTranslateState::TRANSLATE_HEIGHT);
        if (!hideToolBar) {
            UpdateToolBarAndDividerProperty(property, false, navNodeBase);
        }
    }
}

void NavDestinationPatternBase::HandleTitleBarAndToolBarAnimation(const RefPtr<NavDestinationNodeBase>& navNodeBase,
    bool needRunTitleBarAnimation, bool needRunToolBarAnimation)
{
    if (!(needRunToolBarAnimation || needRunTitleBarAnimation)) {
        return;
    }

    CHECK_NULL_VOID(navNodeBase);
    auto pipeline = navNodeBase->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto property = navNodeBase->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    CHECK_NULL_VOID(property);
    bool hideTitleBar = property->GetHideTitleBarValue(false);
    bool hideToolBar = property->GetHideToolBarValue(false);
    UpdateLayoutPropertyBeforeAnimation(navNodeBase, needRunTitleBarAnimation,
        needRunToolBarAnimation, hideTitleBar, hideToolBar);

    auto task = [weakPattern = WeakClaim(this), needRunTitleBarAnimation, needRunToolBarAnimation,
        hideTitleBar, hideToolBar]() mutable {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto node = AceType::DynamicCast<NavDestinationNodeBase>(pattern->GetHost());
        CHECK_NULL_VOID(node);
        auto property = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
        CHECK_NULL_VOID(property);
        if (pattern->IsNeedHideToolBarForNavWidth()) {
            property->ResetToolBarTranslateState();
            needRunToolBarAnimation = false;
        }
        if (!(needRunToolBarAnimation || needRunTitleBarAnimation)) {
            return;
        }

        auto titleBarNode = AceType::DynamicCast<TitleBarNode>(node->GetTitleBarNode());
        if (needRunTitleBarAnimation && !hideTitleBar && titleBarNode && pattern->GetTitleBarAnimationCount() == 0) {
            pattern->UpdateTitleBarTranslateAndOpacity(true, titleBarNode, pattern->GetTitleBarHeight());
        }
        auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(node->GetToolBarNode());
        auto toolBarDividerNode = AceType::DynamicCast<FrameNode>(node->GetToolBarDividerNode());
        if (needRunToolBarAnimation && !hideToolBar && toolBarNode && pattern->GetToolBarAnimationCount() == 0) {
            pattern->UpdateToolBarAndDividerTranslateAndOpacity(true, toolBarNode,
                pattern->GetToolBarHeight(), toolBarDividerNode, pattern->GetToolBarDividerHeight());
        }

        pattern->StartAnimation(needRunTitleBarAnimation, hideTitleBar, needRunToolBarAnimation, hideToolBar);
    };
    pipeline->AddAfterLayoutTask(std::move(task));
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

void NavDestinationPatternBase::BarAnimationPropertyCallback(
    bool needRunTitleBarAnimation, bool hideTitle, bool needRunToolBarAnimation, bool hideTool)
{
    auto node = AceType::DynamicCast<NavDestinationNodeBase>(GetHost());
    CHECK_NULL_VOID(node);
    auto property = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    CHECK_NULL_VOID(property);
    auto context = node->GetContext();
    CHECK_NULL_VOID(context);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(node->GetTitleBarNode());
    auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(node->GetToolBarNode());
    auto toolBarDividerNode = AceType::DynamicCast<FrameNode>(node->GetToolBarDividerNode());
    if (needRunTitleBarAnimation && titleBarNode) {
        property->UpdateTitleBarTranslateState(hideTitle ?
            BarTranslateState::TRANSLATE_HEIGHT : BarTranslateState::TRANSLATE_ZERO);
    }
    if (needRunToolBarAnimation && toolBarNode) {
        property->UpdateToolBarTranslateState(hideTool ?
            BarTranslateState::TRANSLATE_HEIGHT : BarTranslateState::TRANSLATE_ZERO);
    }
    node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    context->FlushUITasks();
    if (needRunTitleBarAnimation && titleBarNode) {
        UpdateTitleBarTranslateAndOpacity(hideTitle, titleBarNode, GetTitleBarHeight());
    }
    if (needRunToolBarAnimation && toolBarNode) {
        UpdateToolBarAndDividerTranslateAndOpacity(hideTool, toolBarNode, GetToolBarHeight(),
            toolBarDividerNode, GetToolBarDividerHeight());
    }
}

void NavDestinationPatternBase::BarAnimationFinishCallback(
    bool needRunTitleBarAnimation, bool needRunToolBarAnimation, int32_t animationId)
{
    if (needRunTitleBarAnimation) {
        OnTitleBarAnimationFinish();
    }
    if (needRunToolBarAnimation) {
        OnToolBarAnimationFinish();
    }
    RemoveAnimation(animationId);
}

void NavDestinationPatternBase::StartAnimation(
    bool needRunTitleBarAnimation, bool hideTitle, bool needRunToolBarAnimation, bool hideTool)
{
    auto propertyCallback = [needRunTitleBarAnimation, hideTitle, needRunToolBarAnimation, hideTool,
                                weakPattern = AceType::WeakClaim(this)]() {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->BarAnimationPropertyCallback(needRunTitleBarAnimation, hideTitle, needRunToolBarAnimation, hideTool);
    };
    auto finishCallback = [needRunTitleBarAnimation, needRunToolBarAnimation,
                              weakPattern = AceType::WeakClaim(this), animationId = nextBarAnimationId_]() {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->BarAnimationFinishCallback(needRunTitleBarAnimation, needRunToolBarAnimation, animationId);
    };

    AnimationOption option;
    option.SetCurve(Curves::FAST_OUT_SLOW_IN);
    option.SetDuration(DEFAULT_ANIMATION_DURATION);
    if (needRunTitleBarAnimation) {
        OnTitleBarAnimationStart();
    }
    if (needRunToolBarAnimation) {
        OnToolBarAnimationStart();
    }
    auto animation = AnimationUtils::StartAnimation(option, propertyCallback, finishCallback);
    barAnimations_.emplace(nextBarAnimationId_, animation);
    nextBarAnimationId_++;
}

void NavDestinationPatternBase::OnTitleBarAnimationFinish()
{
    titleBarAnimationCount_--;
    if (titleBarAnimationCount_ > 0) {
        return;
    }

    auto node = AceType::DynamicCast<NavDestinationNodeBase>(GetHost());
    CHECK_NULL_VOID(node);
    auto property = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    CHECK_NULL_VOID(property);
    property->ResetTitleBarTranslateState();
    HideOrShowTitleBarImmediately(node, property->GetHideTitleBarValue(false));
}

void NavDestinationPatternBase::OnToolBarAnimationFinish()
{
    toolBarAnimationCount_--;
    if (toolBarAnimationCount_ > 0) {
        return;
    }

    auto node = AceType::DynamicCast<NavDestinationNodeBase>(GetHost());
    CHECK_NULL_VOID(node);
    auto property = node->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    CHECK_NULL_VOID(property);
    property->ResetToolBarTranslateState();
    HideOrShowToolBarImmediately(node, property->GetHideToolBarValue(false));
}

void NavDestinationPatternBase::AbortBarAnimation()
{
    auto barAnimations = barAnimations_;
    for (const auto& pair : barAnimations) {
        if (pair.second) {
            AnimationUtils::StopAnimation(pair.second);
        }
    }
    barAnimations_.clear();
}

void NavDestinationPatternBase::RemoveAnimation(int32_t id)
{
    auto it = barAnimations_.find(id);
    if (it != barAnimations_.end()) {
        barAnimations_.erase(it);
    }
}

void NavDestinationPatternBase::UpdateHideBarProperty()
{
    auto hostNode = GetHost();
    CHECK_NULL_VOID(hostNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    CHECK_NULL_VOID(layoutProperty);
    /**
     *  Mark need update safeAreaPadding when usr-set visibility of safe-area-padding-mode titleBar changed.
     *  The same goes for toolBar.
     */
    if ((titleBarStyle_.value_or(BarStyle::STANDARD) == BarStyle::SAFE_AREA_PADDING &&
        isHideTitlebar_ != layoutProperty->GetHideTitleBarValue(false)) ||
        (toolBarStyle_.value_or(BarStyle::STANDARD) == BarStyle::SAFE_AREA_PADDING &&
        isHideToolbar_ != layoutProperty->GetHideToolBarValue(false))) {
        safeAreaPaddingChanged_ = true;
    }
    isHideToolbar_ = layoutProperty->GetHideToolBarValue(false);
    isHideTitlebar_ = layoutProperty->GetHideTitleBarValue(false);
}

void NavDestinationPatternBase::ExpandContentSafeAreaIfNeeded()
{
    auto hostNode = DynamicCast<NavDestinationNodeBase>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto layoutProperty = hostNode->GetLayoutProperty<NavDestinationLayoutPropertyBase>();
    CHECK_NULL_VOID(layoutProperty);
    auto&& opts = layoutProperty->GetSafeAreaExpandOpts();
    auto contentNode = AceType::DynamicCast<FrameNode>(hostNode->GetContentNode());
    if (opts && contentNode) {
        contentNode->GetLayoutProperty()->UpdateSafeAreaExpandOpts(*opts);
        contentNode->MarkModifyDone();
    }
}

void NavDestinationPatternBase::MarkSafeAreaPaddingChangedWithCheckTitleBar(float titleBarHeight)
{
    auto hostNode = DynamicCast<NavDestinationNodeBase>(GetHost());
    CHECK_NULL_VOID(hostNode);
    if (titleBarStyle_.value_or(BarStyle::STANDARD) != BarStyle::SAFE_AREA_PADDING) {
        return;
    }
    /**
     *  Mark need update safeAreaPadding when the height of safe-area-padding-title changed.
     *  For example, when titleMode of navigation changed or when free-mode-title is dragged.
     */
    if (!NearEqual(titleBarHeight, titleBarHeight_)) {
        safeAreaPaddingChanged_ = true;
        return;
    }
    /**
     *  Mark need update safeAreaPadding when titleBar onHover mode updated.
     */
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(hostNode->GetTitleBarNode());
    if (titleBarNode && NavigationTitleUtil::CalculateTitlebarOffset(titleBarNode) != titleBarOffsetY_) {
        safeAreaPaddingChanged_ = true;
    }
}

bool NavDestinationPatternBase::CustomizeExpandSafeArea()
{
    auto host = AceType::DynamicCast<NavDestinationNodeBase>(GetHost());
    CHECK_NULL_RETURN(host, false);
    return host->CustomizeExpandSafeArea();
}
} // namespace OHOS::Ace::NG