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

#include "core/components_ng/pattern/stage/force_split/parallel_page_pattern.h"

#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/pattern/stage/force_split/parallel_stage_manager.h"
#include "core/components_ng/pattern/stage/force_split/parallel_stage_pattern.h"

namespace OHOS::Ace::NG {

void ParallelPagePattern::OnShow(bool isAppStateChange)
{
    if (IsShowOrHideAllowed()) {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "page show");
        PagePattern::OnShow(isAppStateChange);
    }
}

void ParallelPagePattern::OnHide(bool isAppStateChange)
{
    if (IsShowOrHideAllowed()) {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "page hide");
        PagePattern::OnHide(isAppStateChange);
    }
}

bool ParallelPagePattern::IsShowOrHideAllowed()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto stageManager = AceType::DynamicCast<ParallelStageManager>(pipeline->GetStageManager());
    CHECK_NULL_RETURN(stageManager, false);
    auto forceSplitMgr = pipeline->GetForceSplitManager();
    CHECK_NULL_RETURN(forceSplitMgr, false);
    if (SystemProperties::GetDeviceType() != DeviceType::TABLET &&
        SystemProperties::GetDeviceType() != DeviceType::TWO_IN_ONE &&
        !forceSplitMgr->IsForceSplitEnable(true)) {
        return true;
    }
    return stageManager->IsInStageOperation();
}

void ParallelPagePattern::InitOnTouchEvent()
{
    if (touchListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto stageManager = AceType::DynamicCast<ParallelStageManager>(pipeline->GetStageManager());
        CHECK_NULL_VOID(stageManager);
        if (RouterPageType::PRIMARY_PAGE == pattern->GetPageType()) {
            stageManager->SetPrimaryPageTouched(true);
        } else {
            stageManager->SetPrimaryPageTouched(false);
        }
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchListener_);
}

void ParallelPagePattern::RemoveOnTouchEvent()
{
    if (!touchListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    gesture->RemoveTouchEvent(touchListener_);
    touchListener_ = nullptr;
}

void ParallelPagePattern::BeforeCreateLayoutWrapper()
{
    PagePattern::BeforeCreateLayoutWrapper();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    // SafeArea already applied to AppBar (AtomicServicePattern)
    if (context->GetInstallationFree()) {
        return;
    }
    RefPtr<FrameNode> stageNode = AceType::DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_VOID(stageNode);
    auto stagePattern = stageNode->GetPattern<ParallelStagePattern>();
    CHECK_NULL_VOID(stagePattern);
    if (!stagePattern->GetIsSplit()) {
        return;
    }
    auto primaryPage = stagePattern->GetPrimaryPage();
    if (!primaryPage) {
        return;
    }

    auto props = host->GetLayoutProperty();
    CHECK_NULL_VOID(props);
    const auto& safeArea = props->GetSafeAreaInsets();
    CHECK_NULL_VOID(safeArea);
    SafeAreaInsets newSafeArea(*safeArea);

    if (type_ == RouterPageType::PRIMARY_PAGE) {
        newSafeArea.right_.end = newSafeArea.right_.start;
    } else {
        newSafeArea.left_.start = newSafeArea.left_.end;
    }
    props->UpdateSafeAreaInsets(newSafeArea);
}

void ParallelPagePattern::OnAttachToMainTree()
{
    if (type_ == RouterPageType::RELATED_PAGE || type_ == RouterPageType::PLACEHOLDER_PAGE) {
#if defined(ENABLE_SPLIT_MODE)
        if (!needFireObserver_) {
            return;
        }
#endif
        auto info = GetPageInfo();
        CHECK_NULL_VOID(info);
        // index of router page start from 1.
        info->SetPageIndex(-1);
        if (needNotifyRelatedPageAboutToAppear_) {
            needNotifyRelatedPageAboutToAppear_ = false;
            state_ = RouterPageState::ABOUT_TO_APPEAR;
            UIObserverHandler::GetInstance().NotifyRouterPageStateChange(GetPageInfo(), state_, currentPageSize_);
        }
        return;
    }
    PagePattern::OnAttachToMainTree();
}

void ParallelPagePattern::NotifyAboutToDisappear()
{
    needNotifyRelatedPageAboutToAppear_ = true;
    state_ = RouterPageState::ABOUT_TO_DISAPPEAR;
    UIObserverHandler::GetInstance().NotifyRouterPageStateChange(GetPageInfo(), state_, currentPageSize_);
}

void ParallelPagePattern::OnDetachFromMainTree()
{
    if (type_ == RouterPageType::RELATED_PAGE || type_ == RouterPageType::PLACEHOLDER_PAGE) {
        if (needNotifyRelatedPageAboutToDisappear_) {
            needNotifyRelatedPageAboutToDisappear_ = false;
            state_ = RouterPageState::ABOUT_TO_DISAPPEAR;
            UIObserverHandler::GetInstance().NotifyRouterPageStateChange(GetPageInfo(), state_, currentPageSize_);
        }
        return;
    }
    PagePattern::OnDetachFromMainTree();
}
} // namespace OHOS::Ace::NG
