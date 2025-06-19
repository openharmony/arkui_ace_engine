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
#include "core/event/touch_event.h"

namespace OHOS::Ace {
FormManagerDelegate::~FormManagerDelegate() = default;

void FormManagerDelegate::ReleasePlatformResource() {}

void FormManagerDelegate::Stop() {}

void FormManagerDelegate::UnregisterEvent() {}

#if OHOS_STANDARD_SYSTEM
void FormManagerDelegate::AddForm(const WeakPtr<PipelineBase>& context, const RequestFormInfo& info,
    const AppExecFwk::FormInfo& formInfo) {}
#else
void FormManagerDelegate::AddForm(const WeakPtr<PipelineBase>& context, const RequestFormInfo& info) {}
#endif

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

void FormManagerDelegate::SetRSUIContext(std::shared_ptr<Rosen::RSUIContext> &rsUIContext) {}

void FormManagerDelegate::SetFormUtils(const std::shared_ptr<FormUtils>& formUtils)
{
    if (formUtils) {
        formUtils_ = formUtils;
    }
}

void FormManagerDelegate::AddRenderDelegate() {}

void FormManagerDelegate::RegisterRenderDelegateEvent() {}

void FormManagerDelegate::AddFormSurfaceNodeCallback(const OnFormSurfaceNodeCallback& callback) {}

void FormManagerDelegate::AddActionEventHandle(const ActionEventHandle& callback) {}

void FormManagerDelegate::SetAllowUpdate(bool allowUpdate) {}

void FormManagerDelegate::DispatchPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent,
    SerializedGesture& serializedGesture) {}

void FormManagerDelegate::NotifySurfaceChange(float width, float height, float borderWidth) {}

void FormManagerDelegate::AddFormSurfaceChangeCallback(OnFormSurfaceChangeCallback&& callback) {}

void FormManagerDelegate::AddFormSurfaceDetachCallback(OnFormSurfaceDetachCallback&& callback) {}

void FormManagerDelegate::AddFormLinkInfoUpdateCallback(OnFormLinkInfoUpdateCallback&& callback) {}

void FormManagerDelegate::AddGetRectRelativeToWindowCallback(OnGetRectRelativeToWindowCallback&& callback) {}

void FormManagerDelegate::AddSnapshotCallback(SnapshotCallback&& callback) {}

void FormManagerDelegate::AddEnableFormCallback(EnableFormCallback&& callback) {}

void FormManagerDelegate::AddLockFormCallback(LockFormCallback&& callback) {}

void FormManagerDelegate::ResetForm() {}

void FormManagerDelegate::ReleaseForm() {}

void FormManagerDelegate::ReleaseRenderer() {}

void FormManagerDelegate::OnFormLinkInfoUpdate(const std::vector<std::string>& formLinkInfos) {}

void FormManagerDelegate::OnGetRectRelativeToWindow(AccessibilityParentRectInfo& parentRectInfo) {}

void FormManagerDelegate::SetObscured(bool isObscured) {}

void FormManagerDelegate::OnAccessibilityChildTreeRegister(
    uint32_t windowId, int32_t treeId, int64_t accessibilityId) {}
void FormManagerDelegate::OnAccessibilityChildTreeDeregister() {}
void FormManagerDelegate::OnAccessibilityDumpChildInfo(
    const std::vector<std::string>& params, std::vector<std::string>& info) {}
void FormManagerDelegate::OnAccessibilityTransferHoverEvent(float pointX, float pointY, int32_t sourceType,
    int32_t eventType, int64_t timeMs) {}
void FormManagerDelegate::NotifyFormDump(const std::vector<std::string>& params,
    std::vector<std::string>& info) {}
void FormManagerDelegate::HandleCachedClickEvents() {}

#if OHOS_STANDARD_SYSTEM
bool FormManagerDelegate::GetFormInfo(const std::string& bundleName, const std::string& moduleName,
    const std::string& cardName, AppExecFwk::FormInfo& formInfo)
{
    return true;
}

void FormManagerDelegate::SetParamForWant(const RequestFormInfo& info) {}
void FormManagerDelegate::SetParamForWant(const RequestFormInfo& info, const AppExecFwk::FormInfo& formInfo) {}
#endif

bool FormManagerDelegate::CheckFormBundleForbidden(const std::string& bundleName)
{
    return false;
}

bool FormManagerDelegate::IsFormBundleExempt(int64_t formId)
{
    return true;
}

bool FormManagerDelegate::IsFormBundleProtected(const std::string &bundleName, int64_t formId)
{
    return false;
}

void FormManagerDelegate::AddFormUpdateDoneCallback(UpdateFormDoneCallback&& callback) {}

void FormManagerDelegate::OnFormUpdateDone(const int64_t formId) {}
} // namespace OHOS::Ace
