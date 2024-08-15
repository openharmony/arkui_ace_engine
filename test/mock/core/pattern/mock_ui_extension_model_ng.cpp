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

#include "base/want/want_wrap.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> UIExtensionModelNG::Create(const std::string& bundleName, const std::string& abilityName,
    const std::map<std::string, std::string>& params, std::function<void(int32_t)>&& onRelease,
    std::function<void(int32_t, const std::string&, const std::string&)>&& onError)
{
    return nullptr;
}

void UIExtensionModelNG::Create(const RefPtr<OHOS::Ace::WantWrap>& wantWrap, bool transferringCaller) {}

void UIExtensionModelNG::Create(const RefPtr<OHOS::Ace::WantWrap>& wantWrap, SessionType sessionType) {}

void UIExtensionModelNG::Create() {}

void UIExtensionModelNG::InitializeDynamicComponent(const RefPtr<NG::FrameNode>& frameNode, const std::string& hapPath,
    const std::string& abcPath, const std::string& entryPoint, void* runtime)
{}

void UIExtensionModelNG::InitializeIsolatedComponent(
    const RefPtr<NG::FrameNode>& frameNode, const RefPtr<OHOS::Ace::WantWrap>& wantWrap, void* runtime)
{}

void UIExtensionModelNG::SetOnSizeChanged(std::function<void(int32_t, int32_t)>&& onSizeChanged) {}

void UIExtensionModelNG::SetOnRelease(std::function<void(int32_t)>&& onRelease) {}

void UIExtensionModelNG::SetOnResult(std::function<void(int32_t, const AAFwk::Want&)>&& onResult) {}

void UIExtensionModelNG::SetOnReceive(std::function<void(const AAFwk::WantParams&)>&& onReceive) {}

void UIExtensionModelNG::SetOnRemoteReady(std::function<void(const RefPtr<UIExtensionProxy>&)>&& onRemoteReady) {}

void UIExtensionModelNG::SetOnError(
    std::function<void(int32_t code, const std::string& name, const std::string& message)>&& onError)
{}

void UIExtensionModelNG::SetPlatformOnError(
    std::function<void(int32_t code, const std::string& name, const std::string& message)>&& onError)
{}
} // namespace OHOS::Ace::NG
