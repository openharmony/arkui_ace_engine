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

#include "bridge/declarative_frontend/jsview/models/animator_model_impl.h"

#ifdef USE_ARK_ENGINE
#include "bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"
#endif

namespace OHOS::Ace::Framework {
namespace {
RefPtr<JsAcePage> GetCurrentPage()
{
#ifdef USE_ARK_ENGINE
    auto page = JsiDeclarativeEngineInstance::GetStagingPage(Container::CurrentId());
    return page;
#endif
    return nullptr;
}
} // namespace

void AnimatorModelImpl::Create(const std::string& animatorId)
{
    auto page = GetCurrentPage();
    CHECK_NULL_VOID(page);
    auto animatorInfo = page->GetAnimatorInfo(animatorId);
    if (!animatorInfo) {
        animatorInfo = AceType::MakeRefPtr<AnimatorInfo>();
        auto animator = CREATE_ANIMATOR();
        animatorInfo->SetAnimator(animator);
        page->AddAnimatorInfo(animatorId, animatorInfo);
    }
}

RefPtr<AnimatorInfo> AnimatorModelImpl::GetAnimatorInfo(const std::string& animatorId)
{
    auto page = GetCurrentPage();
    CHECK_NULL_RETURN(page, nullptr);
    auto animatorInfo = page->GetAnimatorInfo(animatorId);
    return animatorInfo;
}

void AnimatorModelImpl::AddEventListener(
    std::function<void()>&& callback, EventOperation operation, const std::string& animatorId)
{
    auto animatorInfo = GetAnimatorInfo(animatorId);
    CHECK_NULL_VOID(animatorInfo);
    auto animator = animatorInfo->GetAnimator();
    CHECK_NULL_VOID(animatorInfo);
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(PipelineBase::GetCurrentContext());
    CHECK_NULL_VOID(pipelineContext);
    WeakPtr<PipelineContext> weakContext = WeakPtr<PipelineContext>(pipelineContext);
    auto eventMarker = callback ? EventMarker(std::move(callback)) : EventMarker();
    switch (operation) {
        case EventOperation::START:
            animator->ClearStartListeners();
            if (!eventMarker.IsEmpty()) {
                animator->AddStartListener(
                    [eventMarker, weakContext] { AceAsyncEvent<void()>::Create(eventMarker, weakContext)(); });
            }
            break;
        case EventOperation::PAUSE:
            animator->ClearPauseListeners();
            if (!eventMarker.IsEmpty()) {
                animator->AddPauseListener(
                    [eventMarker, weakContext] { AceAsyncEvent<void()>::Create(eventMarker, weakContext)(); });
            }
            break;
        case EventOperation::REPEAT:
            animator->ClearRepeatListeners();
            if (!eventMarker.IsEmpty()) {
                animator->AddRepeatListener(
                    [eventMarker, weakContext] { AceAsyncEvent<void()>::Create(eventMarker, weakContext)(); });
            }
            break;
        case EventOperation::CANCEL:
            animator->ClearIdleListeners();
            if (!eventMarker.IsEmpty()) {
                animator->AddIdleListener(
                    [eventMarker, weakContext] { AceAsyncEvent<void()>::Create(eventMarker, weakContext)(); });
            }
            break;
        case EventOperation::FINISH:
            animator->ClearStopListeners();
            if (!eventMarker.IsEmpty()) {
                animator->AddStopListener(
                    [eventMarker, weakContext] { AceAsyncEvent<void()>::Create(eventMarker, weakContext)(); });
            }
            break;
        case EventOperation::NONE:
        default:
            break;
    }
}
} // namespace OHOS::Ace::Framework
