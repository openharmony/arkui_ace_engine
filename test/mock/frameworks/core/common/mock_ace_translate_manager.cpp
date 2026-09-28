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
#include <cstdint>

#include "base/utils/macros.h"
#include "core/common/ace_translate_manager.h"
#include "core/components_ng/pattern/page_translate/page_translate_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace {
void UiTranslateManagerImpl::AddPixelMap(int32_t nodeId, RefPtr<PixelMap> pixelMap) {}

void UiTranslateManagerImpl::GetAllPixelMap(RefPtr<NG::FrameNode> node) {}

// Keep registry behavior aligned with ace_translate_manager.cpp; external services are stubbed below.
void UiTranslateManagerImpl::AddTranslateListener(const WeakPtr<NG::FrameNode> node)
{
    auto frame = node.Upgrade();
    CHECK_NULL_VOID(frame);
    auto carrier = AceType::DynamicCast<NG::PageTranslateNode>(frame->GetPattern());
    CHECK_NULL_VOID(carrier);
    auto id = carrier->GetPageTranslateNodeId();
    CHECK_NULL_VOID(id >= 0);
    listenerMap_[id] = { node, WeakPtr<NG::PageTranslateNode>(carrier) };
}

void UiTranslateManagerImpl::RemoveTranslateListener(int32_t nodeId)
{
    listenerMap_.erase(nodeId);
}

void UiTranslateManagerImpl::ForEachArkUITranslateFrameNode(
    const std::function<void(const WeakPtr<NG::FrameNode>&)>& callback) const
{
    CHECK_NULL_VOID(callback);
    for (const auto& listener : listenerMap_) {
        // Host component tests do not link the platform WebPattern implementation.
        auto frame = listener.second.frameNode.Upgrade();
        if (frame && frame->GetTag() == V2::WEB_ETS_TAG) {
            continue;
        }
        callback(listener.second.frameNode);
    }
}

void UiTranslateManagerImpl::GetWebViewCurrentLanguage() {}
void UiTranslateManagerImpl::GetTranslateText(std::string, bool) {}
void UiTranslateManagerImpl::GetPageTranslateText(int32_t, const std::string&) {}
void UiTranslateManagerImpl::StartPageTranslate(int32_t, const std::string&) {}
void UiTranslateManagerImpl::EndPageTranslate(int32_t) {}
void UiTranslateManagerImpl::ResetPageTranslate(int32_t) {}
void UiTranslateManagerImpl::SendPageTranslateResult(const std::vector<TranslateResult>&) {}
void UiTranslateManagerImpl::SendTranslateResult(int32_t, std::vector<std::string>, std::vector<int32_t>) {}
void UiTranslateManagerImpl::ResetTranslate(int32_t) {}
void UiTranslateManagerImpl::SendTranslateResult(int32_t, std::string) {}
void UiTranslateManagerImpl::ClearMap() {}
void UiTranslateManagerImpl::PostToUI(const std::function<void()>&) {}
} // namespace OHOS::Ace
