/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "form_renderer_dispatcher_impl.h"

#include "form_renderer.h"
#include "form_renderer_hilog.h"

namespace OHOS {
namespace Ace {
FormRendererDispatcherImpl::FormRendererDispatcherImpl(
    const std::shared_ptr<UIContent> uiContent,
    const std::shared_ptr<FormRenderer> formRenderer,
    std::weak_ptr<OHOS::AppExecFwk::EventHandler> eventHandler)
    : uiContent_(uiContent), formRenderer_(formRenderer), eventHandler_(eventHandler)
{}

void FormRendererDispatcherImpl::DispatchPointerEvent(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent)
{
    auto handler = eventHandler_.lock();
    if (!handler) {
        HILOG_ERROR("eventHandler is nullptr");
        return;
    }

    handler->PostTask([=]() {
        auto uiContent = uiContent_.lock();
        if (!uiContent) {
            HILOG_ERROR("uiContent is nullptr");
            return;
        }

        uiContent->ProcessPointerEvent(pointerEvent);
    });
}

bool FormRendererDispatcherImpl::IsAllowUpdate()
{
    return allowUpdate_;
}

void FormRendererDispatcherImpl::SetAllowUpdate(bool allowUpdate)
{
    allowUpdate_ = allowUpdate;
}

void FormRendererDispatcherImpl::DispatchSurfaceChangeEvent(float width, float height)
{
    auto handler = eventHandler_.lock();
    if (!handler) {
        HILOG_ERROR("eventHandler is nullptr");
        return;
    }

    handler->PostTask([=]() {
        auto uiContent = uiContent_.lock();
        if (!uiContent) {
            HILOG_ERROR("uiContent is nullptr");
            return;
        }
        uiContent->SetFormWidth(width);
        uiContent->SetFormHeight(height);
        uiContent->OnFormSurfaceChange(width, height);
    });

    auto formRenderer = formRenderer_.lock();
    if (!formRenderer) {
        HILOG_ERROR("formRenderer is nullptr");
        return;
    }
    formRenderer->OnSurfaceChange(width, height);
}
} // namespace Ace
} // namespace OHOS
