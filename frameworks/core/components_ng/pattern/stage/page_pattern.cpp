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
#include "base/perfmonitor/perf_monitor.h"
#include "base/utils/utils.h"
#include "core/animation/animator.h"
#include "core/common/container.h"
#include "core/components/common/properties/alignment.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
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
            LOGD("add id:%{public}s", id.c_str());
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
    host->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    host->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_LEFT);
}

bool PagePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& /*wrapper*/, const DirtySwapConfig& /*config*/)
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

bool PagePattern::TriggerPageTransition(PageTransitionType type, const std::function<void()>& onFinish)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    if (pageTransitionFunc_) {
        pageTransitionFunc_();
    }
    auto effect = FindPageTransitionEffect(type);
    pageTransitionFinish_ = std::make_shared<std::function<void()>>(onFinish);
    auto wrappedOnFinish = [weak = WeakClaim(this), sharedFinish = pageTransitionFinish_]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        if (sharedFinish == pattern->pageTransitionFinish_) {
            // ensure this is exactly the finish callback saved in pagePattern,
            // otherwise means new pageTransition started
            pattern->FirePageTransitionFinish();
        }
    };
    if (effect && effect->GetUserCallback()) {
        if (!controller_) {
            controller_ = CREATE_ANIMATOR(PipelineContext::GetCurrentContext());
        }
        if (!controller_->IsStopped()) {
            controller_->Finish();
        }
        controller_->ClearInterpolators();
        RouteType routeType = (type == PageTransitionType::ENTER_POP || type == PageTransitionType::EXIT_POP)
                                  ? RouteType::POP
                                  : RouteType::PUSH;
        auto floatAnimation = AceType::MakeRefPtr<CurveAnimation<float>>(0.0f, 1.0f, effect->GetCurve());
        floatAnimation->AddListener(
            [routeType, handler = effect->GetUserCallback(), weak = WeakClaim(this)](const float& progress) {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                handler(routeType, progress);
            });
        if (effect->GetDelay() >= 0) {
            controller_->SetStartDelay(effect->GetDelay());
        }
        controller_->SetDuration(effect->GetDuration());
        controller_->AddInterpolator(floatAnimation);
        controller_->AddStopListener(wrappedOnFinish);
        controller_->Forward();
        return renderContext->TriggerPageTransition(type, nullptr);
    }
    return renderContext->TriggerPageTransition(type, wrappedOnFinish);
}

void PagePattern::ProcessHideState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->SetActive(false);
    host->OnVisibleChange(false);
    host->GetLayoutProperty()->UpdateVisibility(VisibleType::INVISIBLE);
    auto parent = host->GetAncestorNodeOfFrame();
    CHECK_NULL_VOID(parent);
    parent->MarkNeedSyncRenderTree();
    parent->RebuildRenderContextTree();
}

void PagePattern::ProcessShowState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->SetActive(true);
    host->OnVisibleChange(true);
    host->GetLayoutProperty()->UpdateVisibility(VisibleType::VISIBLE);
    auto parent = host->GetAncestorNodeOfFrame();
    CHECK_NULL_VOID(parent);
    parent->MarkNeedSyncRenderTree();
    parent->RebuildRenderContextTree();
}

void PagePattern::OnShow()
{
    // Do not invoke onPageShow unless the initialRender function has been executed.
    CHECK_NULL_VOID_NOLOG(isRenderDone_);
    CHECK_NULL_VOID_NOLOG(!isOnShow_);
    auto container = Container::Current();
    if (!container || !container->WindowIsShow()) {
        LOGW("no need to trigger onPageShow callback when not in the foreground");
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->SetJSViewActive(true);
    isOnShow_ = true;
    JankFrameReport::StartRecord(pageInfo_->GetPageUrl());
    PerfMonitor::GetPerfMonitor()->SetPageUrl(pageInfo_->GetPageUrl());
    if (onPageShow_) {
        onPageShow_();
    }
}

void PagePattern::OnHide()
{
    CHECK_NULL_VOID_NOLOG(isOnShow_);
    JankFrameReport::FlushRecord();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->SetJSViewActive(false);
    isOnShow_ = false;
    if (onPageHide_) {
        onPageHide_();
    }
}

void PagePattern::BuildSharedTransitionMap()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    sharedTransitionMap_.clear();
    IterativeAddToSharedMap(host, sharedTransitionMap_);
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
    if (controller_ && !controller_->IsStopped()) {
        controller_->Finish();
        return;
    }
    FirePageTransitionFinish();
}

void PagePattern::BeforeCreateLayoutWrapper()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    // SafeArea already applied to AppBar
    if (pipeline->GetInstallationFree()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto safeArea = pipeline->GetSafeArea();
    auto props = host->GetLayoutProperty();
    if (safeArea.IsValid() || props->GetSafeAreaInsets()) {
        props->UpdateSafeAreaInsets(safeArea);
    }
}
} // namespace OHOS::Ace::NG
