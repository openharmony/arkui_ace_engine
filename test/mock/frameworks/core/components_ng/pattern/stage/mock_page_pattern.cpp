/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/pattern/stage/page_pattern.h"

namespace OHOS::Ace::NG {
void PagePattern::OnAttachToFrameNode() {}

void PagePattern::BeforeCreateLayoutWrapper() {}

bool PagePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& wrapper, const DirtySwapConfig& config)
{
    (void)wrapper;
    (void)config;
    return false;
}

void PagePattern::BeforeSyncGeometryProperties(const DirtySwapConfig& config)
{
    (void)config;
}

void PagePattern::FirePageTransitionStart() {}

void PagePattern::FirePageTransitionFinish() {}

void PagePattern::OnAttachToMainTree() {}

void PagePattern::OnDetachFromMainTree() {}

void PagePattern::ContentChangeByDetaching(PipelineContext* pipeline)
{
    (void)pipeline;
}

bool PagePattern::AvoidKeyboard() const
{
    return false;
}

void PagePattern::NotifyPerfMonitorPageMsg(const std::string& pageUrl, const std::string& bundleName)
{
    (void)pageUrl;
    (void)bundleName;
}

RefPtr<PageTransitionEffect> PagePattern::GetPageTransitionEffect(const RefPtr<PageTransitionEffect>& transition)
{
    return transition;
}

void PagePattern::SlideTransitionEffect(const SlideEffect& effect, const RectF& rect, TranslateOptions& translate)
{
    (void)effect;
    (void)rect;
    (void)translate;
}

void PagePattern::UpdateDefaultEnterPopEffect(RefPtr<PageTransitionEffect>& effect, float statusHeight)
{
    (void)effect;
    (void)statusHeight;
}

void PagePattern::UpdateEnterPushEffect(RefPtr<PageTransitionEffect>& effect, float statusHeight)
{
    (void)effect;
    (void)statusHeight;
}

void PagePattern::UpdateExitPushEffect(RefPtr<PageTransitionEffect>& effect, float statusHeight)
{
    (void)effect;
    (void)statusHeight;
}

void PagePattern::UpdateAnimationOption(const RefPtr<PageTransitionEffect>& transition,
    RefPtr<PageTransitionEffect>& effect, AnimationOption& option, PageTransitionType type)
{
    (void)transition;
    (void)effect;
    (void)option;
    (void)type;
}

void PagePattern::TriggerDefaultTransition(const std::function<void()>& onFinish, PageTransitionType type)
{
    (void)type;
    if (onFinish) {
        onFinish();
    }
}

void PagePattern::MaskAnimation(const Color& initialBackgroundColor, const Color& backgroundColor)
{
    (void)initialBackgroundColor;
    (void)backgroundColor;
}

void PagePattern::NotifyNavigationLifecycle(bool isShow, bool isFromWindow)
{
    (void)isShow;
    (void)isFromWindow;
}

void PagePattern::RecordPageEvent(bool isShow)
{
    (void)isShow;
}

void PagePattern::SetPageIndexForStatic() {}

void PagePattern::NotifyRouterPageSizeChange() {}

void PagePattern::OnVisibleChange(bool isVisible)
{
    (void)isVisible;
}

void PagePattern::OnShow(bool isFromWindow)
{
    (void)isFromWindow;
}

void PagePattern::OnHide(bool isFromWindow)
{
    (void)isFromWindow;
}

bool PagePattern::OnBackPressed()
{
    return false;
}

RefPtr<PageTransitionEffect> PagePattern::FindPageTransitionEffect(PageTransitionType type)
{
    (void)type;
    return nullptr;
}

void PagePattern::ClearPageTransitionEffect() {}

RefPtr<PageTransitionEffect> PagePattern::GetTopTransition() const
{
    return nullptr;
}

void PagePattern::AddPageTransition(const RefPtr<PageTransitionEffect>& effect)
{
    (void)effect;
}

ScopeFocusAlgorithm PagePattern::GetScopeFocusAlgorithm()
{
    return {};
}

WeakPtr<FocusHub> PagePattern::GetNextFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode)
{
    (void)step;
    (void)currentFocusNode;
    return {};
}

void PagePattern::AddJsAnimator(const std::string& animatorId, const RefPtr<Framework::AnimatorInfo>& animatorInfo)
{
    (void)animatorId;
    (void)animatorInfo;
}

RefPtr<Framework::AnimatorInfo> PagePattern::GetJsAnimator(const std::string& animatorId)
{
    (void)animatorId;
    return nullptr;
}

void PagePattern::BuildSharedTransitionMap() {}

void PagePattern::ReloadPage() {}

void PagePattern::SetFirstBuildCallback(std::function<void()>&& buildCallback)
{
    firstBuildCallback_ = std::move(buildCallback);
}

void PagePattern::ProcessHideState() {}

void PagePattern::ProcessShowState() {}

bool PagePattern::ProcessAutoSave(const std::function<void()>& onFinish,
    const std::function<void()>& onUIExtNodeBindingCompleted)
{
    (void)onUIExtNodeBindingCompleted;
    if (onFinish) {
        onFinish();
    }
    return false;
}

void PagePattern::StopPageTransition() {}

bool PagePattern::RemoveOverlay()
{
    return false;
}

void PagePattern::MarkDirtyOverlay() {}

void PagePattern::InitTransitionIn(const RefPtr<PageTransitionEffect>& effect, PageTransitionType type)
{
    (void)effect;
    (void)type;
}

void PagePattern::InitTransitionOut(const RefPtr<PageTransitionEffect>& effect, PageTransitionType type)
{
    (void)effect;
    (void)type;
}

void PagePattern::TransitionInFinish(const RefPtr<PageTransitionEffect>& effect, PageTransitionType type)
{
    (void)effect;
    (void)type;
}

void PagePattern::TransitionOutFinish(const RefPtr<PageTransitionEffect>& effect, PageTransitionType type)
{
    (void)effect;
    (void)type;
}

void PagePattern::FinishOutPage(const int32_t animationId, PageTransitionType type)
{
    (void)animationId;
    (void)type;
}

void PagePattern::FinishInPage(const int32_t animationId, PageTransitionType type)
{
    (void)animationId;
    (void)type;
}

RefPtr<PageTransitionEffect> PagePattern::GetDefaultPageTransition(PageTransitionType type)
{
    (void)type;
    return nullptr;
}

void PagePattern::ResetPageTransitionEffect() {}

void PagePattern::TriggerPageTransition(const std::function<void()>& onFinish, PageTransitionType type)
{
    (void)type;
    if (onFinish) {
        onFinish();
    }
}

void PagePattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    (void)frameNode;
}

void PagePattern::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    (void)width;
    (void)height;
    (void)type;
}

void PagePattern::RemoveJsChildImmediately(const RefPtr<FrameNode>& page, PageTransitionType transactionType)
{
    (void)page;
    (void)transactionType;
}

bool PagePattern::IsNeedCallbackBackPressed()
{
    return false;
}
} // namespace OHOS::Ace::NG
