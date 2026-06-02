/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "interfaces/inner_api/ace_kit/src/view/ui_context_impl.h"

#include "iremote_object.h"

#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::Kit {
UIContextImpl::~UIContextImpl() = default;

void UIContextImpl::Reset()
{
    context_ = nullptr;
    overlayManager_ = nullptr;
}

RefPtr<PipelineBase> UIContextImpl::GetPipelineContext()
{
    return nullptr;
}

void UIContextImpl::RunScopeUITaskSync(Task&& task, const std::string& name)
{
    (void)name;
    if (task) {
        task();
    }
}

void UIContextImpl::RunScopeUITask(Task&& task, const std::string& name)
{
    (void)name;
    if (task) {
        task();
    }
}

void UIContextImpl::RunScopeUIDelayedTask(Task&& task, const std::string& name, uint32_t delayTime)
{
    (void)name;
    (void)delayTime;
    if (task) {
        task();
    }
}

void UIContextImpl::OnBackPressed() {}
ColorMode UIContextImpl::GetLocalColorMode() { return ColorMode::LIGHT; }
ColorMode UIContextImpl::GetColorMode() { return ColorMode::LIGHT; }
float UIContextImpl::GetFontScale() { return 1.0f; }
RefPtr<OverlayManager> UIContextImpl::GetOverlayManager() { return nullptr; }
void UIContextImpl::AddAfterLayoutTask(Task&& task, bool isFlushInImplicitAnimationTask)
{
    (void)isFlushInImplicitAnimationTask;
    if (task) {
        task();
    }
}
void UIContextImpl::RequestFrame() {}
int32_t UIContextImpl::GetApiTargetVersion() { return 0; }
bool UIContextImpl::GreatOrEqualTargetAPIVersion(int32_t version)
{
    (void)version;
    return false;
}
int32_t UIContextImpl::GetContainerModalTitleHeight() { return 0; }
int32_t UIContextImpl::GetContainerModalButtonsWidth() { return 0; }
NG::OffsetF UIContextImpl::GetContainerModalButtonsOffset() { return {}; }
void UIContextImpl::RegisterArkUIObjectLifecycleCallback(ArkUIObjectLifecycleCallback&& callback)
{
    (void)callback;
}
void UIContextImpl::UnregisterArkUIObjectLifecycleCallback() {}
sptr<IRemoteObject> UIContextImpl::GetToken() { return nullptr; }
RefPtr<DisplayInfo> UIContextImpl::GetDisplayInfo() { return nullptr; }
WindowMode UIContextImpl::GetWindowMode() { return WindowMode::WINDOW_MODE_UNDEFINED; }
bool UIContextImpl::GetIsMidScene() { return false; }
bool UIContextImpl::IsAccessibilityEnabled() { return false; }
int32_t UIContextImpl::RegisterSurfaceChangedCallback(
    std::function<void(int32_t, int32_t, int32_t, int32_t, WindowSizeChangeReason)>&& callback)
{
    (void)callback;
    return -1;
}
void UIContextImpl::UnregisterSurfaceChangedCallback(int32_t callbackId)
{
    (void)callbackId;
}
int32_t UIContextImpl::RegisterFoldStatusChangedCallback(std::function<void(FoldStatus)>&& callback)
{
    (void)callback;
    return -1;
}
void UIContextImpl::UnRegisterFoldStatusChangedCallback(int32_t callbackId)
{
    (void)callbackId;
}
int32_t UIContextImpl::RegisterRotationEndCallback(std::function<void()>&& callback)
{
    (void)callback;
    return -1;
}
void UIContextImpl::UnregisterRotationEndCallback(int32_t callbackId)
{
    (void)callbackId;
}
void UIContextImpl::AddWindowSizeChangeCallback(int32_t nodeId)
{
    (void)nodeId;
}
} // namespace OHOS::Ace::Kit
