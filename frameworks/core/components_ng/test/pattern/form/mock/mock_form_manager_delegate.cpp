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

#include "core/components/form/resource/form_manager_delegate.h"

namespace OHOS::Ace {
FormManagerDelegate::~FormManagerDelegate() = default;

void FormManagerDelegate::ReleasePlatformResource() {}

void FormManagerDelegate::Stop() {}

void FormManagerDelegate::UnregisterEvent() {}

void FormManagerDelegate::AddForm(const WeakPtr<PipelineBase>& context, const RequestFormInfo& info) {}

std::string FormManagerDelegate::ConvertRequestInfo(const RequestFormInfo& info) const
{
    std::stringstream paramStream;
    return paramStream.str();
}

void FormManagerDelegate::CreatePlatformResource(const WeakPtr<PipelineBase>& context, const RequestFormInfo& info) {}

void FormManagerDelegate::AddFormAcquireCallback(const OnFormAcquiredCallback& callback) {}

void FormManagerDelegate::AddFormUpdateCallback(const OnFormUpdateCallback& callback) {}

void FormManagerDelegate::AddFormErrorCallback(const OnFormErrorCallback& callback) {}

void FormManagerDelegate::AddFormUninstallCallback(const OnFormUninstallCallback& callback) {}

void FormManagerDelegate::AddUnTrustFormCallback(const UnTrustFormCallback& callback) {}

void FormManagerDelegate::OnActionEvent(const std::string& action) {}

void FormManagerDelegate::SetFormUtils(const std::shared_ptr<FormUtils>& formUtils)
{
    if (formUtils) {
        formUtils_ = formUtils;
    }
}

void FormManagerDelegate::AddRenderDelegate() {}

void FormManagerDelegate::RegisterRenderDelegateEvent() {}

void FormManagerDelegate::AddFormSurfaceNodeCallback(const OnFormSurfaceNodeCallback &callback) {}

void FormManagerDelegate::AddActionEventHandle(const ActionEventHandle &callback) {}

void FormManagerDelegate::SetAllowUpdate(bool allowUpdate) {}

void FormManagerDelegate::DispatchPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent) {}

void FormManagerDelegate::NotifySurfaceChange(float width, float height) {}

void FormManagerDelegate::AddFormSurfaceChangeCallback(OnFormSurfaceChangeCallback &&callback) {}

void FormManagerDelegate::AddSnapshotCallback(SnapshotCallback&& callback) {}

void FormManagerDelegate::ResetForm() {}

void FormManagerDelegate::ReleaseForm() {}
} // namespace OHOS::Ace
