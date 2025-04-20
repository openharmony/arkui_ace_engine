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

#include "adapter/ohos/entrance/dynamic_component/dynamic_component_renderer_impl.h"

namespace OHOS::Ace::NG {

RefPtr<DynamicComponentRenderer> DynamicComponentRendererImpl::DynamicComponentRenderer::Create(
    const RefPtr<FrameNode>& host, void* runtime, const IsolatedInfo& isolatedInfo)
{
    return AceType::MakeRefPtr<DynamicComponentRendererImpl>(host, runtime, isolatedInfo);
}

DynamicComponentRendererImpl::DynamicComponentRendererImpl(
    const RefPtr<FrameNode>& host, void* runtime, const IsolatedInfo& isolatedInfo)
    : isolatedInfo_(isolatedInfo)
{
    host_ = WeakPtr(host);
    runtime_ = reinterpret_cast<NativeEngine*>(runtime);
}

void DynamicComponentRendererImpl::SetAdaptiveSize(bool adaptiveWidth, bool adaptiveHeight) {}

void DynamicComponentRendererImpl::CreateContent() {}

void DynamicComponentRendererImpl::DestroyContent() {}

void DynamicComponentRendererImpl::UpdateViewportConfig(const SizeF& size, float density,
    int32_t orientation, AnimationOption animationOpt, const OffsetF& offset) {}

void DynamicComponentRendererImpl::TransferPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent) {}

bool DynamicComponentRendererImpl::TransferKeyEvent(const KeyEvent& event)
{
    return true;
}

void DynamicComponentRendererImpl::SetUIContentType(UIContentType uIContentType) {}

bool DynamicComponentRendererImpl::IsRestrictedWorkerThread() { return false; }

bool DynamicComponentRendererImpl::HasWorkerUsing(void *worker) { return false; }

void DynamicComponentRendererImpl::AddWorkerUsing(void *worker) {}

void DynamicComponentRendererImpl::DeleteWorkerUsing(void *worker) {}

void DynamicComponentRendererImpl::CreateIsolatedContent() {}

void DynamicComponentRendererImpl::CreateDynamicContent() {}

void DynamicComponentRendererImpl::TransferAccessibilityChildTreeRegister(
    uint32_t windowId, int32_t treeId, int64_t accessibilityId) {}

void DynamicComponentRendererImpl::TransferAccessibilityChildTreeDeregister() {}

void DynamicComponentRendererImpl::TransferAccessibilityDumpChildInfo(
    const std::vector<std::string>& params, std::vector<std::string>& info) {}

void DynamicComponentRendererImpl::SetUIContentJsContext() {}

void DynamicComponentRendererImpl::TransferFocusState(bool isFocus) {}

void DynamicComponentRendererImpl::TransferFocusActiveEvent(bool isFocus) {}

void DynamicComponentRendererImpl::SearchElementInfoByAccessibilityId(int64_t elementId, int32_t mode,
    int64_t baseParent, std::list<Accessibility::AccessibilityElementInfo>& output) {}

void DynamicComponentRendererImpl::SearchElementInfosByText(int64_t elementId, const std::string& text,
    int64_t baseParent, std::list<Accessibility::AccessibilityElementInfo>& output) {}

void DynamicComponentRendererImpl::FindFocusedElementInfo(int64_t elementId, int32_t focusType, int64_t baseParent,
    Accessibility::AccessibilityElementInfo& output) {}

void DynamicComponentRendererImpl::FocusMoveSearch(int64_t elementId, int32_t direction, int64_t baseParent,
    Accessibility::AccessibilityElementInfo& output) {}

bool DynamicComponentRendererImpl::NotifyExecuteAction(int64_t elementId,
    const std::map<std::string, std::string>& actionArguments, int32_t action, int64_t offset)
{
    return true;
}

void DynamicComponentRendererImpl::TransferAccessibilityHoverEvent(float pointX, float pointY, int32_t sourceType,
    int32_t eventType, int64_t timeMs) {}

void DynamicComponentRendererImpl::InitializeDynamicAccessibility() {}

void DynamicComponentRendererImpl::UpdateParentOffsetToWindow(const OffsetF& offset) {}

void DynamicComponentRendererImpl::Dump(RendererDumpInfo &rendererDumpInfo) {}

void DynamicComponentRendererImpl::NotifyUieDump(const std::vector<std::string>& params,
    std::vector<std::string>& info) {}

void DynamicComponentRendererImpl::SetBackgroundTransparent(bool backgroundTransparent) {}

bool DynamicComponentRendererImpl::GetBackgroundTransparent() const
{
    return true;
}

bool DynamicComponentRendererImpl::CheckWorkerMaxConstraint()
{
    return true;
}

void DynamicComponentRendererImpl::OnDestroyContent() {}

void DynamicComponentRendererImpl::AfterDestroyContent() {}

void DynamicComponentRendererImpl::NotifyForeground() {}

void DynamicComponentRendererImpl::NotifyBackground() {}
} // namespace OHOS::Ace::NG