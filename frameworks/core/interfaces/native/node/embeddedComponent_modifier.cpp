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
#include "core/interfaces/native/node/embeddedComponent_modifier.h"

#include "interfaces/native/node/embeddedComponent_option.h"
#include "want_manager.h"

#include "bridge/common/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_adapter.h"

namespace OHOS::Ace::NG {
namespace {
using onErrorFuncType = void (*)(int32_t code, const char* name, const char* message);
using onTerminatedFuncType = void (*)(int32_t code, AbilityBase_Want* want);

void SetEmbeddedComponentWant(ArkUINodeHandle node, AbilityBase_Want* cwant)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    AbilityBase_Want cWant = *cwant;
    AAFwk::Want want;
    auto errCode = AAFwk::CWantManager::TransformToWant(cWant, true, want);
    if (errCode != ABILITY_BASE_ERROR_CODE_NO_ERROR) {
        TAG_LOGE(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "Set EmbeddedComponent want failed, error code is %{public}d",
            errCode);
        return;
    }
    UIExtensionAdapter::SetEmbeddedComponentWant(frameNode, want);
}

void SetEmbeddedComponentOption(ArkUINodeHandle node, ArkUIEmbeddedComponentItemHandle option)
{
    CHECK_NULL_VOID(option);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (option->onError) {
        auto onError = [option](int32_t code, const std::string& name, const std::string& message) {
            if (option == nullptr || option->onError == nullptr) {
                TAG_LOGE(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "option is null, set EmbeddedComponent onError failed");
                return;
            }
            onErrorFuncType func = reinterpret_cast<onErrorFuncType>(option->onError);
            if (func == nullptr) {
                TAG_LOGE(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "func is null, set EmbeddedComponent onError failed");
                return;
            }
            func(code, name.c_str(), message.c_str());
        };
        UIExtensionAdapter::SetEmbeddedComponentOnError(frameNode, std::move(onError));
    }

    if (option->onTerminated) {
        auto onTerminated = [option](int32_t code, const RefPtr<WantWrap>& wantWrap) {
            if (option == nullptr || option->onTerminated == nullptr) {
                TAG_LOGE(
                    AceLogTag::ACE_UIEXTENSIONCOMPONENT, "option is null, set EmbeddedComponent onTerminated failed");
                return;
            }
            AbilityBase_Want want;
            onTerminatedFuncType func = reinterpret_cast<onTerminatedFuncType>(option->onTerminated);
            if (func == nullptr) {
                TAG_LOGE(
                    AceLogTag::ACE_UIEXTENSIONCOMPONENT, "func is null, set EmbeddedComponent onTerminated failed");
                return;
            }
            func(code, &want);
        };
        UIExtensionAdapter::SetEmbeddedComponentOnTerminated(frameNode, std::move(onTerminated));
    }
}
} // namespace

namespace NodeModifier {
const ArkUIEmbeddedComponentModifier* GetEmbeddedComponentModifier()
{
    static const ArkUIEmbeddedComponentModifier modifier = {
        .setEmbeddedComponentWant = SetEmbeddedComponentWant,
        .setEmbeddedComponentOption = SetEmbeddedComponentOption,
    };

    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG