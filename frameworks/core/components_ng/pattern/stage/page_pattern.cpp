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

#include "core/components_ng/pattern/stage/page_pattern.h"

#include "base/log/jank_frame_report.h"
#include "base/perfmonitor/perf_constants.h"
#include "base/perfmonitor/perf_monitor.h"
#include "core/components_ng/base/observer_handler.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/ng/entry_page_info.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t INVALID_PAGE_INDEX = -1;
const int32_t MASK_DURATION = 350;
constexpr int32_t DEFAULT_ANIMATION_DURATION = 450;
std::string KEY_PAGE_TRANSITION_PROPERTY = "pageTransitionProperty";
constexpr float REMOVE_CLIP_SIZE = 10000.0f;
constexpr double HALF = 0.5;
constexpr double PARENT_PAGE_OFFSET = 0.2;
constexpr int32_t RELEASE_JSCHILD_DELAY_TIME = 50;
const Color MASK_COLOR = Color::FromARGB(25, 0, 0, 0);
const Color DEFAULT_MASK_COLOR = Color::FromARGB(0, 0, 0, 0);

void IterativeAddToSharedMap(const RefPtr<UINode>& node, SharedTransitionMap& map)
{
    const auto& children = node->GetChildren();
    for (const auto& child : children) {
        auto frameChild = AceType::DynamicCast<FrameNode>(child);
        if (!frameChild) {
            IterativeAddToSharedMap(child, map);
            continue;
        }
        auto id = frameChild->GetRenderContext()->GetShareId();
        if (!id.empty()) {
            map[id] = frameChild;
        }
        IterativeAddToSharedMap(frameChild, map);
    }
}
} // namespace

void PagePattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    MeasureType measureType = MeasureType::MATCH_PARENT;
    auto container = Container::Current();
    if (container && container->IsDynamicRender()) {
        measureType = MeasureType::MATCH_CONTENT;
    }
    host->GetLayoutProperty()->UpdateMeasureType(measureType);
    host->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_LEFT);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddWindowSizeChangeCallback(host->GetId());
    pipelineContext->GetMemoryManager()->AddRecyclePageNode(host);
}

bool PagePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& wrapper, const DirtySwapConfig& /* config */)
{
    if (isFirstLoad_) {
        isFirstLoad_ = false;
        if (firstBuildCallback_) {
            firstBuildCallback_();
            firstBuildCallback_ = nullptr;
        }
    }
    return false;
}

void PagePattern::BeforeSyncGeometryProperties(const DirtySwapConfig& config)
{
    if (config.skipLayout || config.skipMeasure) {
        return;
    }
    CHECK_NULL_VOID(dynamicPageSizeCallback_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto node = host->GetGeometryNode();
    CHECK_NULL_VOID(node);
    dynamicPageSizeCallback_(node->GetFrameSize());
}

void PagePattern::TriggerPageTransition(const std::function<void()>& onFinish, PageTransitionType type)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (pageTransitionFunc_) {
        pageTransitionFunc_();
    }
    pageTransitionFinish_ = std::make_shared<std::function<void()>>(onFinish);
    auto wrappedOnFinish = [weak = WeakClaim(this), sharedFinish = pageTransitionFinish_, type]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (type == PageTransitionType::ENTER_PUSH || type == PageTransitionType::ENTER_POP) {
            ACE_SCOPED_TRACE_COMMERCIAL("Router Page Transition End");
            PerfMonitor::GetPerfMonitor()->End(PerfConstants::ABILITY_OR_PAGE_SWITCH, true);
        }
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        if (sharedFinish == pattern->pageTransitionFinish_) {
            // ensure this is exactly the finish callback saved in pagePattern,
            // otherwise means new pageTransition started
            pattern->FirePageTransitionFinish();
            host->DeleteAnimatablePropertyFloat(KEY_PAGE_TRANSITION_PROPERTY);
        }
    };
    auto effect = FindPageTransitionEffect(type);
    if (effect && effect->GetUserCallback()) {
        AnimationUtils::StopAnimation(currCustomAnimation_);
        host->DeleteAnimatablePropertyFloat(KEY_PAGE_TRANSITION_PROPERTY);
        RouteType routeType = (type == PageTransitionType::ENTER_POP || type == PageTransitionType::EXIT_POP)
                                  ? RouteType::POP
                                  : RouteType::PUSH;
        host->CreateAnimatablePropertyFloat(KEY_PAGE_TRANSITION_PROPERTY, 0.0f,
            [routeType, handler = effect->GetUserCallback()](const float& progress) { handler(routeType, progress); });
        auto handler = effect->GetUserCallback();
        handler(routeType, 0.0f);
        AnimationOption option(effect->GetCurve(), effect->GetDuration());
        option.SetDelay(effect->GetDelay());
        option.SetOnFinishEvent(wrappedOnFinish);
        currCustomAnimation_ = AnimationUtils::StartAnimation(option, [weakPage = WeakPtr<FrameNode>(host)]() {
            auto pageNode = weakPage.Upgrade();
            CHECK_NULL_VOID(pageNode);
            pageNode->UpdateAnimatablePropertyFloat(KEY_PAGE_TRANSITION_PROPERTY, 1.0f);
        }, option.GetOnFinishEvent());
        TriggerDefaultTransition(nullptr, type);
        return;
    }
    TriggerDefaultTransition(wrappedOnFinish, type);
}

bool PagePattern::ProcessAutoSave(const std::function<void()>& onFinish,
    const std::function<void()>& onUIExtNodeBindingCompleted)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    if (!host->NeedRequestAutoSave()) {
        return false;
    }
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    return container->RequestAutoSave(host, onFinish, onUIExtNodeBindingCompleted);
}

void PagePattern::ProcessHideState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->SetActive(false);
    host->NotifyVisibleChange(VisibleType::VISIBLE, VisibleType::INVISIBLE);
    host->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
    auto parent = host->GetAncestorNodeOfFrame(false);
    CHECK_NULL_VOID(parent);
    parent->MarkNeedSyncRenderTree();
    parent->RebuildRenderContextTree();
}

void PagePattern::ProcessShowState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->SetActive(true);
    host->NotifyVisibleChange(VisibleType::INVISIBLE, VisibleType::VISIBLE);
    host->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
    auto parent = host->GetAncestorNodeOfFrame(false);
    CHECK_NULL_VOID(parent);
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto manager = context->GetSafeAreaManager();
    if (manager) {
        auto safeArea = manager->GetSafeArea();
        auto parentGlobalOffset = host->GetParentGlobalOffsetDuringLayout();
        auto frame = host->GetPaintRectWithTransform() + parentGlobalOffset;
        // if page's frameRect not fit current safeArea, need layout page again
        if (!NearEqual(frame.GetY(), safeArea.top_.end)) {
            host->MarkDirtyNode(manager->KeyboardSafeAreaEnabled() ? PROPERTY_UPDATE_LAYOUT : PROPERTY_UPDATE_MEASURE);
        }
        if (!NearEqual(frame.GetY() + frame.Height(), safeArea.bottom_.start)) {
            host->MarkDirtyNode(manager->KeyboardSafeAreaEnabled() ? PROPERTY_UPDATE_LAYOUT : PROPERTY_UPDATE_MEASURE);
        }
    }
    parent->MarkNeedSyncRenderTree();
    parent->RebuildRenderContextTree();
}

void PagePattern::OnAttachToMainTree()
{
#if defined(ENABLE_SPLIT_MODE)
    if (!needFireObserver_) {
        return;
    }
#endif
    int32_t index = INVALID_PAGE_INDEX;
    auto delegate = EngineHelper::GetCurrentDelegate();
    if (delegate) {
        index = delegate->GetCurrentPageIndex();
        GetPageInfo()->SetPageIndex(index);
    }
    state_ = RouterPageState::ABOUT_TO_APPEAR;
    UIObserverHandler::GetInstance().NotifyRouterPageStateChange(GetPageInfo(), state_);
}

void PagePattern::OnDetachFromMainTree()
{
#if defined(ENABLE_SPLIT_MODE)
    if (!needFireObserver_) {
        return;
    }
#endif
    state_ = RouterPageState::ABOUT_TO_DISAPPEAR;
    UIObserverHandler::GetInstance().NotifyRouterPageStateChange(GetPageInfo(), state_);
}

void PagePattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->RemoveWindowSizeChangeCallback(frameNode->GetId());
    pipelineContext->GetMemoryManager()->RemoveRecyclePageNode(frameNode->GetId());
}

void PagePattern::OnWindowSizeChanged(int32_t /*width*/, int32_t /*height*/, WindowSizeChangeReason /*type*/)
{
    if (!isPageInTransition_) {
        return;
    }
    auto page = GetHost();
    CHECK_NULL_VOID(page);
    auto renderContext = page->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->RemoveClipWithRRect();
}

void PagePattern::OnShow(bool isFromWindow)
{
    // Do not invoke onPageShow unless the initialRender function has been executed.
    CHECK_NULL_VOID(isRenderDone_);
    CHECK_NULL_VOID(!isOnShow_);
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto container = Container::Current();
    if (!container || !container->WindowIsShow()) {
        LOGW("no need to trigger onPageShow callback when not in the foreground");
        return;
    }
    NotifyPerfMonitorPageMsg(pageInfo_->GetFullPath(), container->GetBundleName());
    if (pageInfo_) {
        context->FirePageChanged(pageInfo_->GetPageId(), true);
        NotifyNavigationLifecycle(true, isFromWindow);
    }
    UpdatePageParam();
    isOnShow_ = true;
#if defined(ENABLE_SPLIT_MODE)
    if (needFireObserver_) {
        state_ = RouterPageState::ON_PAGE_SHOW;
        UIObserverHandler::GetInstance().NotifyRouterPageStateChange(GetPageInfo(), state_);
    }
#else
    state_ = RouterPageState::ON_PAGE_SHOW;
    UIObserverHandler::GetInstance().NotifyRouterPageStateChange(GetPageInfo(), state_);
#endif
    JankFrameReport::GetInstance().StartRecord(pageInfo_->GetFullPath());
    auto pageUrlChecker = container->GetPageUrlChecker();
    if (pageUrlChecker != nullptr) {
        pageUrlChecker->NotifyPageShow(pageInfo_->GetPageUrl());
    }
    if (visibilityChangeCallback_) {
        visibilityChangeCallback_(true);
    }
    if (onPageShow_) {
        onPageShow_();
    }
    if (!onHiddenChange_.empty()) {
        FireOnHiddenChange(true);
    }
    RecordPageEvent(true);
}

void PagePattern::RecordPageEvent(bool isShow)
{
    if (!Recorder::EventRecorder::Get().IsPageRecordEnable()) {
        return;
    }
    auto entryPageInfo = DynamicCast<EntryPageInfo>(pageInfo_);
    if (isShow) {
        std::string param;
        if (entryPageInfo) {
            param = Recorder::EventRecorder::Get().IsPageParamRecordEnable() ? entryPageInfo->GetPageParams() : "";
            entryPageInfo->SetShowTime(GetCurrentTimestamp());
        }
        Recorder::EventRecorder::Get().OnPageShow(
            pageInfo_->GetPageUrl(), param, pageInfo_->GetRouteName().value_or(""));
    } else {
        int64_t duration = 0;
        if (entryPageInfo && entryPageInfo->GetShowTime() > 0) {
            duration = GetCurrentTimestamp() - entryPageInfo->GetShowTime();
        }
        Recorder::EventRecorder::Get().OnPageHide(
            pageInfo_->GetPageUrl(), duration, pageInfo_->GetRouteName().value_or(""));
    }
}

void PagePattern::OnHide(bool isFromWindow)
{
    CHECK_NULL_VOID(isOnShow_);
    JankFrameReport::GetInstance().FlushRecord();
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (pageInfo_) {
        NotifyNavigationLifecycle(false, isFromWindow);
        context->FirePageChanged(pageInfo_->GetPageId(), false);
    }
    host->SetJSViewActive(false);
    isOnShow_ = false;
    host->SetAccessibilityVisible(false);
#if defined(ENABLE_SPLIT_MODE)
    if (needFireObserver_) {
        state_ = RouterPageState::ON_PAGE_HIDE;
        UIObserverHandler::GetInstance().NotifyRouterPageStateChange(GetPageInfo(), state_);
    }
#else
    state_ = RouterPageState::ON_PAGE_HIDE;
    UIObserverHandler::GetInstance().NotifyRouterPageStateChange(GetPageInfo(), state_);
#endif
    auto container = Container::Current();
    if (container) {
        auto pageUrlChecker = container->GetPageUrlChecker();
        // ArkTSCard container no SetPageUrlChecker
        if (pageUrlChecker != nullptr) {
            pageUrlChecker->NotifyPageHide(pageInfo_->GetPageUrl());
        }
    }
    if (visibilityChangeCallback_) {
        visibilityChangeCallback_(false);
    }
    if (onPageHide_) {
        onPageHide_();
    }
    if (!onHiddenChange_.empty()) {
        FireOnHiddenChange(false);
    }
    RecordPageEvent(false);
}

bool PagePattern::OnBackPressed()
{
    if (RemoveOverlay()) {
        TAG_LOGI(AceLogTag::ACE_OVERLAY, "page removes it's overlay when on backpressed");
        return true;
    }
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN) && isPageInTransition_) {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "page is in transition");
        return true;
    }
    // if in page transition, do not set to ON_BACK_PRESS
#if defined(ENABLE_SPLIT_MODE)
    if (needFireObserver_) {
        state_ = RouterPageState::ON_BACK_PRESS;
        UIObserverHandler::GetInstance().NotifyRouterPageStateChange(GetPageInfo(), state_);
    }
#else
    state_ = RouterPageState::ON_BACK_PRESS;
    UIObserverHandler::GetInstance().NotifyRouterPageStateChange(GetPageInfo(), state_);
#endif
    if (onBackPressed_) {
        bool result = onBackPressed_();
        CheckIsNeedForceExitWindow(result);
        return result;
    }
    return false;
}

void PagePattern::BuildSharedTransitionMap()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    sharedTransitionMap_.clear();
    IterativeAddToSharedMap(host, sharedTransitionMap_);
}

void PagePattern::CheckIsNeedForceExitWindow(bool result)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    if (!context->GetInstallationFree() || !result) {
        // if is not atommic service and result is false, don't process.
        return;
    }
    auto stageManager = context->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    int32_t pageSize =
        stageManager->GetStageNode() ? static_cast<int32_t>(stageManager->GetStageNode()->GetChildren().size()) : 0;
    if (pageSize != 1) {
        return;
    }
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    if (container->IsUIExtensionWindow()) {
        container->TerminateUIExtension();
    } else {
        auto windowManager = context->GetWindowManager();
        CHECK_NULL_VOID(windowManager);
        windowManager->WindowPerformBack();
    }
    TAG_LOGI(AceLogTag::ACE_ROUTER, "page onbackpress intercepted, exit window.");
}

void PagePattern::ReloadPage()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto customNode = DynamicCast<CustomNodeBase>(host->GetFirstChild());
    CHECK_NULL_VOID(customNode);
    customNode->FireReloadFunction(true);
}

RefPtr<PageTransitionEffect> PagePattern::FindPageTransitionEffect(PageTransitionType type)
{
    RefPtr<PageTransitionEffect> result;
    for (auto iter = pageTransitionEffects_.rbegin(); iter != pageTransitionEffects_.rend(); ++iter) {
        auto effect = *iter;
        if (effect->CanFit(type)) {
            result = effect;
            break;
        }
    }
    return result;
}

void PagePattern::ClearPageTransitionEffect()
{
    pageTransitionEffects_.clear();
}

RefPtr<PageTransitionEffect> PagePattern::GetTopTransition() const
{
    return pageTransitionEffects_.empty() ? nullptr : pageTransitionEffects_.back();
}

void PagePattern::AddPageTransition(const RefPtr<PageTransitionEffect>& effect)
{
    pageTransitionEffects_.emplace_back(effect);
}

void PagePattern::AddJsAnimator(const std::string& animatorId, const RefPtr<Framework::AnimatorInfo>& animatorInfo)
{
    CHECK_NULL_VOID(animatorInfo);
    auto animator = animatorInfo->GetAnimator();
    CHECK_NULL_VOID(animator);
    animator->AttachScheduler(PipelineContext::GetCurrentContext());
    jsAnimatorMap_[animatorId] = animatorInfo;
}

RefPtr<Framework::AnimatorInfo> PagePattern::GetJsAnimator(const std::string& animatorId)
{
    auto iter = jsAnimatorMap_.find(animatorId);
    if (iter != jsAnimatorMap_.end()) {
        return iter->second;
    }
    return nullptr;
}

void PagePattern::SetFirstBuildCallback(std::function<void()>&& buildCallback)
{
    if (isFirstLoad_) {
        firstBuildCallback_ = std::move(buildCallback);
    } else if (buildCallback) {
        buildCallback();
    }
}

void PagePattern::FirePageTransitionFinish()
{
    if (pageTransitionFinish_) {
        auto onFinish = *pageTransitionFinish_;
        pageTransitionFinish_ = nullptr;
        if (onFinish) {
            onFinish();
        }
    }
}

void PagePattern::StopPageTransition()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto property = host->GetAnimatablePropertyFloat(KEY_PAGE_TRANSITION_PROPERTY);
    if (property) {
        FirePageTransitionFinish();
        return;
    }
    AnimationOption option(Curves::LINEAR, 0);
    AnimationUtils::Animate(
        option, [host]() { host->UpdateAnimatablePropertyFloat(KEY_PAGE_TRANSITION_PROPERTY, 0.0f); });
    host->DeleteAnimatablePropertyFloat(KEY_PAGE_TRANSITION_PROPERTY);
    FirePageTransitionFinish();
}

void PagePattern::BeforeCreateLayoutWrapper()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    // SafeArea already applied to AppBar (AtomicServicePattern)
    if (pipeline->GetInstallationFree()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        ACE_SCOPED_TRACE("[%s][self:%d] SafeArea already applied to AppBar", host->GetTag().c_str(), host->GetId());
        return;
    }
    ContentRootPattern::BeforeCreateLayoutWrapper();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto&& insets = host->GetLayoutProperty()->GetSafeAreaInsets();
    CHECK_NULL_VOID(insets);
    auto manager = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(manager);
}

bool PagePattern::AvoidKeyboard() const
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    CHECK_NULL_RETURN(safeAreaManager, false);
    return safeAreaManager->KeyboardSafeAreaEnabled();
}

bool PagePattern::RemoveOverlay()
{
    CHECK_NULL_RETURN(overlayManager_, false);
    if (overlayManager_->IsCurrentNodeProcessRemoveOverlay(GetHost(), false)) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipeline, false);
        auto taskExecutor = pipeline->GetTaskExecutor();
        CHECK_NULL_RETURN(taskExecutor, false);
        return overlayManager_->RemoveOverlay(true);
    }
    return false;
}

bool PagePattern::IsNeedCallbackBackPressed()
{
    CHECK_NULL_RETURN(overlayManager_, false);
    return overlayManager_->IsCurrentNodeProcessRemoveOverlay(GetHost(), true);
}

void PagePattern::NotifyPerfMonitorPageMsg(const std::string& pageUrl, const std::string& bundleName)
{
    if (PerfMonitor::GetPerfMonitor() != nullptr) {
        PerfMonitor::GetPerfMonitor()->SetPageUrl(pageUrl);
        // The page contains only page url but not the page name
        PerfMonitor::GetPerfMonitor()->SetPageName("");
        PerfMonitor::GetPerfMonitor()->ReportPageShowMsg(pageUrl, bundleName, "");
    }
}

void PagePattern::MarkDirtyOverlay()
{
    CHECK_NULL_VOID(overlayManager_);
    overlayManager_->MarkDirtyOverlay();
}

void PagePattern::InitTransitionIn(const RefPtr<PageTransitionEffect>& effect, PageTransitionType type)
{
    CHECK_NULL_VOID(effect);
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto renderContext = hostNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    const auto& scaleOptions = effect->GetScaleEffect();
    const auto& translateOptions = effect->GetTranslateEffect();
    renderContext->UpdateTransformCenter(DimensionOffset(scaleOptions->centerX, scaleOptions->centerY));
    renderContext->UpdateTransformScale(VectorF(scaleOptions->xScale, scaleOptions->yScale));
    renderContext->UpdateTransformTranslate(translateOptions.value());
    renderContext->UpdateOpacity(effect->GetOpacityEffect().value());
    renderContext->ClipWithRRect(effect->GetPageTransitionRectF().value(), RadiusF(EdgeF(0.0f, 0.0f)));
}

void PagePattern::InitTransitionOut(const RefPtr<PageTransitionEffect> & effect, PageTransitionType type)
{
    CHECK_NULL_VOID(effect);
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto renderContext = hostNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    const auto& scaleOptions = effect->GetScaleEffect();
    renderContext->UpdateTransformCenter(DimensionOffset(scaleOptions->centerX, scaleOptions->centerY));
    renderContext->UpdateTransformScale(VectorF(1.0f, 1.0f));
    renderContext->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
    renderContext->UpdateOpacity(1.0);
    renderContext->ClipWithRRect(effect->GetDefaultPageTransitionRectF().value(), RadiusF(EdgeF(0.0f, 0.0f)));
}

RefPtr<PageTransitionEffect> PagePattern::GetDefaultPageTransition(PageTransitionType type)
{
    auto hostNode = GetHost();
    CHECK_NULL_RETURN(hostNode, nullptr);
    auto renderContext = hostNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    auto resultEffect = AceType::MakeRefPtr<PageTransitionEffect>(type, PageTransitionOption());
    resultEffect->SetScaleEffect(ScaleOptions(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct));
    TranslateOptions translate;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto safeAreaInsets = pipelineContext->GetSafeAreaWithoutProcess();
    auto statusHeight = static_cast<float>(safeAreaInsets.top_.Length());
    auto rect = renderContext->GetPaintRectWithoutTransform();
    RectF defaultPageTransitionRectF = RectF(0.0f, -statusHeight, rect.Width(), REMOVE_CLIP_SIZE);
    resultEffect->SetDefaultPageTransitionRectF(defaultPageTransitionRectF);
    switch (type) {
        case PageTransitionType::ENTER_PUSH:
        case PageTransitionType::EXIT_POP:
            UpdateEnterPushEffect(resultEffect, statusHeight);
            break;
        case PageTransitionType::ENTER_POP:
            UpdateDefaultEnterPopEffect(resultEffect, statusHeight);
            break;
        case PageTransitionType::EXIT_PUSH:
            UpdateExitPushEffect(resultEffect, statusHeight);
            break;
        default:
            break;
    }
    resultEffect->SetOpacityEffect(1);
    return resultEffect;
}

void PagePattern::UpdateDefaultEnterPopEffect(RefPtr<PageTransitionEffect>& effect, float statusHeight)
{
    CHECK_NULL_VOID(effect);
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto renderContext = hostNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto rect = renderContext->GetPaintRectWithoutTransform();
    effect->SetInitialBackgroundColor(MASK_COLOR);
    effect->SetBackgroundColor(DEFAULT_MASK_COLOR);
    TranslateOptions translate;
    RectF pageTransitionRectF;
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        pageTransitionRectF =
            RectF(rect.Width() * HALF, -statusHeight, rect.Width() * HALF, REMOVE_CLIP_SIZE);
        translate.x = Dimension(rect.Width() * HALF);
    } else {
        pageTransitionRectF =
            RectF(0.0f, -statusHeight, rect.Width() * PARENT_PAGE_OFFSET, REMOVE_CLIP_SIZE);
        translate.x = Dimension(-rect.Width() * PARENT_PAGE_OFFSET);
    }
    effect->SetPageTransitionRectF(pageTransitionRectF);
    effect->SetTranslateEffect(translate);
}

void PagePattern::UpdateEnterPushEffect(RefPtr<PageTransitionEffect>& effect, float statusHeight)
{
    CHECK_NULL_VOID(effect);
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto renderContext = hostNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto rect = renderContext->GetPaintRectWithoutTransform();
    effect->SetInitialBackgroundColor(DEFAULT_MASK_COLOR);
    effect->SetBackgroundColor(DEFAULT_MASK_COLOR);
    TranslateOptions translate;
    RectF pageTransitionRectF;
    RectF defaultPageTransitionRectF = RectF(0.0f, -statusHeight, rect.Width(), REMOVE_CLIP_SIZE);
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        pageTransitionRectF =
            RectF(0.0f, -statusHeight, rect.Width() * PARENT_PAGE_OFFSET, REMOVE_CLIP_SIZE);
        translate.x = Dimension(-rect.Width() * PARENT_PAGE_OFFSET);
    } else {
        pageTransitionRectF =
            RectF(rect.Width() * HALF, -statusHeight, rect.Width() * HALF, REMOVE_CLIP_SIZE);
        defaultPageTransitionRectF = RectF(0.0f, -statusHeight, rect.Width(), REMOVE_CLIP_SIZE);
        translate.x = Dimension(rect.Width() * HALF);
    }
    effect->SetDefaultPageTransitionRectF(defaultPageTransitionRectF);
    effect->SetPageTransitionRectF(pageTransitionRectF);
    effect->SetTranslateEffect(translate);
}

void PagePattern::UpdateExitPushEffect(RefPtr<PageTransitionEffect>& effect, float statusHeight)
{
    CHECK_NULL_VOID(effect);
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto renderContext = hostNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto rect = renderContext->GetPaintRectWithoutTransform();
    effect->SetInitialBackgroundColor(DEFAULT_MASK_COLOR);
    effect->SetBackgroundColor(MASK_COLOR);
    TranslateOptions translate;
    RectF pageTransitionRectF;
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        pageTransitionRectF =
            RectF(rect.Width() * HALF, -statusHeight, rect.Width() * HALF, REMOVE_CLIP_SIZE);
        translate.x = Dimension(rect.Width() * HALF);
    } else {
        pageTransitionRectF =
            RectF(0.0f, -statusHeight, rect.Width() * PARENT_PAGE_OFFSET, REMOVE_CLIP_SIZE);
        translate.x = Dimension(-rect.Width() * PARENT_PAGE_OFFSET);
    }
    effect->SetPageTransitionRectF(pageTransitionRectF);
    effect->SetTranslateEffect(translate);
}

void PagePattern::TransitionInFinish(const RefPtr<PageTransitionEffect>& effect, PageTransitionType type)
{
    CHECK_NULL_VOID(effect);
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto renderContext = hostNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateTransformScale(VectorF(1.0f, 1.0f));
    renderContext->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
    renderContext->UpdateOpacity(1.0);
    renderContext->ClipWithRRect(effect->GetDefaultPageTransitionRectF().value(), RadiusF(EdgeF(0.0f, 0.0f)));
}

void PagePattern::TransitionOutFinish(const RefPtr<PageTransitionEffect>& effect, PageTransitionType type)
{
    CHECK_NULL_VOID(effect);
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto renderContext = hostNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    const auto& scaleOptions = effect->GetScaleEffect();
    const auto& translateOptions = effect->GetTranslateEffect();
    renderContext->UpdateTransformScale(VectorF(scaleOptions->xScale, scaleOptions->yScale));
    renderContext->UpdateTransformTranslate(translateOptions.value());
    renderContext->UpdateOpacity(effect->GetOpacityEffect().value());
    renderContext->ClipWithRRect(effect->GetPageTransitionRectF().value(), RadiusF(EdgeF(0.0f, 0.0f)));
}

void PagePattern::MaskAnimation(const Color& initialBackgroundColor, const Color& backgroundColor)
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto renderContext = hostNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    AnimationOption maskOption;
    maskOption.SetCurve(Curves::FRICTION);
    maskOption.SetDuration(MASK_DURATION);
    renderContext->SetActualForegroundColor(initialBackgroundColor);
    AnimationUtils::OpenImplicitAnimation(maskOption, maskOption.GetCurve(), nullptr);
    renderContext->SetActualForegroundColor(backgroundColor);
    AnimationUtils::CloseImplicitAnimation();
}

RefPtr<PageTransitionEffect> PagePattern::GetPageTransitionEffect(const RefPtr<PageTransitionEffect>& transition)
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, nullptr);
    auto renderContext = hostNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    auto resultEffect = AceType::MakeRefPtr<PageTransitionEffect>(
        transition->GetPageTransitionType(), transition->GetPageTransitionOption());
    resultEffect->SetScaleEffect(
        transition->GetScaleEffect().value_or(ScaleOptions(1.0f, 1.0f, 1.0f, 0.5_pct, 0.5_pct)));
    TranslateOptions translate;
    auto rect = renderContext->GetPaintRectWithoutTransform();
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto safeAreaInsets = context->GetSafeAreaWithoutProcess();
    auto statusHeight = static_cast<float>(safeAreaInsets.top_.Length());
    RectF defaultPageTransitionRectF = RectF(0.0f, -statusHeight, rect.Width(), REMOVE_CLIP_SIZE);
    // slide and translate, only one can be effective
    if (transition->GetSlideEffect().has_value()) {
        SlideTransitionEffect(transition->GetSlideEffect().value(), rect, translate);
    } else if (transition->GetTranslateEffect().has_value()) {
        const auto& translateOptions = transition->GetTranslateEffect();
        translate.x = Dimension(translateOptions->x.ConvertToPxWithSize(rect.Width()));
        translate.y = Dimension(translateOptions->y.ConvertToPxWithSize(rect.Height()));
        translate.z = Dimension(translateOptions->z.ConvertToPx());
    }
    resultEffect->SetTranslateEffect(translate);
    resultEffect->SetOpacityEffect(transition->GetOpacityEffect().value_or(1));
    resultEffect->SetPageTransitionRectF(RectF(0.0f, -statusHeight, rect.Width(), REMOVE_CLIP_SIZE));
    resultEffect->SetDefaultPageTransitionRectF(defaultPageTransitionRectF);
    resultEffect->SetInitialBackgroundColor(DEFAULT_MASK_COLOR);
    resultEffect->SetBackgroundColor(DEFAULT_MASK_COLOR);
    return resultEffect;
}

void PagePattern::SlideTransitionEffect(const SlideEffect& effect, const RectF& rect, TranslateOptions& translate)
{
    switch (effect) {
        case SlideEffect::LEFT:
            translate.x = Dimension(-rect.Width());
            break;
        case SlideEffect::RIGHT:
            translate.x = Dimension(rect.Width());
            break;
        case SlideEffect::BOTTOM:
            translate.y = Dimension(rect.Height());
            break;
        case SlideEffect::TOP:
            translate.y = Dimension(-rect.Height());
            break;
        case SlideEffect::START:
            if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
                translate.x = Dimension(rect.Width());
                break;
            }
            translate.x = Dimension(-rect.Width());
            break;
        case SlideEffect::END:
            if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
                translate.x = Dimension(-rect.Width());
                break;
            }
            translate.x = Dimension(rect.Width());
            break;
        default:
            break;
    }
}

void PagePattern::ResetPageTransitionEffect()
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto renderContext = hostNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateTransformTranslate({0.0f, 0.0f, 0.0f});
    renderContext->RemoveClipWithRRect();
    MaskAnimation(DEFAULT_MASK_COLOR, DEFAULT_MASK_COLOR);
}

void PagePattern::RemoveJsChildImmediately(const RefPtr<FrameNode>& page, PageTransitionType transactionType)
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        return;
    }

    if (transactionType != PageTransitionType::EXIT_POP) {
        return;
    }

    auto effect = FindPageTransitionEffect(transactionType);
    if (effect && effect->GetUserCallback()) {
        return;
    }

    if (page->HasSkipNode()) {
        return;
    }

    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostDelayedTask(
        [weak = WeakPtr<FrameNode>(page)]() {
            auto page = weak.Upgrade();
            CHECK_NULL_VOID(page);
            page->SetDestroying();
        }, TaskExecutor::TaskType::UI, RELEASE_JSCHILD_DELAY_TIME, "ArkUIRemoveJsChild");
}

void PagePattern::FinishOutPage(const int32_t animationId, PageTransitionType type)
{
    auto outPage = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(outPage);
    outPage->SetNodeFreeze(false);
    if (animationId_ != animationId) {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "animation id is different");
        return;
    }
    outPage->GetEventHub<EventHub>()->SetEnabled(true);
    if (type != PageTransitionType::EXIT_PUSH && type != PageTransitionType::EXIT_POP) {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "current transition type is invalid");
        return;
    }
    TAG_LOGI(AceLogTag::ACE_ROUTER, "%{public}s finish out page transition.", GetPageUrl().c_str());
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        FocusViewHide();
    }

    if (outPage->IsInDestroying()) {
        outPage->SetDestroying(false, false);
    }
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    if (type == PageTransitionType::EXIT_POP || isNeedRemove_) {
        auto stageNode = outPage->GetParent();
        CHECK_NULL_VOID(stageNode);
        stageNode->RemoveChild(outPage);
        stageNode->RebuildRenderContextTree();
        context->RequestFrame();
        return;
    }
    isPageInTransition_ = false;
    ProcessHideState();
    context->MarkNeedFlushMouseEvent();
    auto stageManager = context->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    stageManager->SetStageInTrasition(false);
    ResetPageTransitionEffect();
}

void PagePattern::FinishInPage(const int32_t animationId, PageTransitionType type)
{
    auto inPage = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(inPage);
    inPage->SetNodeFreeze(false);
    if (animationId_ != animationId) {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "animation id in inPage is invalid");
        return;
    }
    inPage->GetEventHub<EventHub>()->SetEnabled(true);
    if (type != PageTransitionType::ENTER_PUSH && type != PageTransitionType::ENTER_POP) {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "inPage transition type is invalid");
        return;
    }
    TAG_LOGI(AceLogTag::ACE_ROUTER, "%{public}s finish inPage transition.", GetPageUrl().c_str());
    isPageInTransition_ = false;
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        FocusViewShow();
    }
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->MarkNeedFlushMouseEvent();
    ResetPageTransitionEffect();
    auto stageManager = context->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    stageManager->SetStageInTrasition(false);
}

void PagePattern::TriggerDefaultTransition(const std::function<void()>& onFinish, PageTransitionType type)
{
    bool transitionIn = true;
    if (type == PageTransitionType::ENTER_PUSH || type == PageTransitionType::ENTER_POP) {
        transitionIn = true;
    } else if (type == PageTransitionType::EXIT_PUSH || type == PageTransitionType::EXIT_POP) {
        transitionIn = false;
    } else {
        return;
    }
    auto transition = FindPageTransitionEffect(type);
    RefPtr<PageTransitionEffect> effect;
    AnimationOption option;
    UpdateAnimationOption(transition, effect, option, type);
    option.SetOnFinishEvent(onFinish);
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto pipelineContext = hostNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    if (transitionIn) {
        InitTransitionIn(effect, type);
        auto animation = AnimationUtils::StartAnimation(option, [weakPattern = WeakClaim(this), effect, type]() {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->TransitionInFinish(effect, type);
        }, option.GetOnFinishEvent());
        stageManager->AddAnimation(animation, type == PageTransitionType::ENTER_PUSH);
        MaskAnimation(effect->GetInitialBackgroundColor().value(), effect->GetBackgroundColor().value());
        return;
    }
    InitTransitionOut(effect, type);
    auto animation = AnimationUtils::StartAnimation(option, [weakPattern = WeakClaim(this), effect, type]() {
        auto pagePattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pagePattern);
        pagePattern->TransitionOutFinish(effect, type);
    }, option.GetOnFinishEvent());
    stageManager->AddAnimation(animation, type == PageTransitionType::ENTER_POP);
    MaskAnimation(effect->GetInitialBackgroundColor().value(), effect->GetBackgroundColor().value());
}

void PagePattern::UpdateAnimationOption(const RefPtr<PageTransitionEffect>& transition,
    RefPtr<PageTransitionEffect>& effect, AnimationOption& option, PageTransitionType type)
{
    if (transition) {
        effect = GetPageTransitionEffect(transition);
        option.SetCurve(transition->GetCurve());
        option.SetDuration(transition->GetDuration());
        option.SetDelay(transition->GetDelay());
        return;
    }
    effect = GetDefaultPageTransition(type);
    const RefPtr<InterpolatingSpring> springCurve =
        AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 342.0f, 37.0f);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        CHECK_NULL_VOID(pipeline);
        auto appTheme = pipeline->GetTheme<AppTheme>();
        CHECK_NULL_VOID(appTheme);
        float defaultAmplitudeRatio = appTheme->GetPageTransitionAmplitudeRatio();
        springCurve->UpdateMinimumAmplitudeRatio(defaultAmplitudeRatio);
    }
    option.SetCurve(springCurve);
    option.SetDuration(DEFAULT_ANIMATION_DURATION);
#ifdef QUICK_PUSH_TRANSITION
    if (pipeline) {
        const int32_t nanoToMilliSeconds = 1000000;
        const int32_t minTransitionDuration = DEFAULT_ANIMATION_DURATION / 2;
        const int32_t frameDelayTime = 32;
        int32_t startDelayTime =
            static_cast<int32_t>(pipeline->GetTimeFromExternalTimer() - pipeline->GetLastTouchTime()) /
            nanoToMilliSeconds;
        startDelayTime = std::max(0, startDelayTime);
        int32_t delayedDuration = DEFAULT_ANIMATION_DURATION > startDelayTime
                                      ? DEFAULT_ANIMATION_DURATION - startDelayTime
                                      : DEFAULT_ANIMATION_DURATION;
        delayedDuration = std::max(minTransitionDuration, delayedDuration - frameDelayTime);
        LOGI("Use quick push delayedDuration:%{public}d", delayedDuration);
        option.SetDuration(delayedDuration);
    }
#endif
}

void PagePattern::NotifyNavigationLifecycle(bool isShow, bool isFromWindow)
{
    auto hostNode = AceType::DynamicCast<FrameNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto context = hostNode->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto navigationManager = context->GetNavigationManager();
    CHECK_NULL_VOID(navigationManager);
    NavDestinationActiveReason activeReason = isFromWindow ? NavDestinationActiveReason::APP_STATE_CHANGE
        : NavDestinationActiveReason::TRANSITION;
    NavDestinationLifecycle lifecycle = isShow ? NavDestinationLifecycle::ON_ACTIVE
        : NavDestinationLifecycle::ON_INACTIVE;
    navigationManager->FireNavigationLifecycle(hostNode, static_cast<int32_t>(lifecycle),
        static_cast<int32_t>(activeReason));
}
} // namespace OHOS::Ace::NG
