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

#include <securec.h>
#include <cstring>

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

void TransformToCWantElement(AbilityBase_Element& element, AAFwk::Want want)
{
    element.bundleName = new char[want.GetElement().GetBundleName().length() + 1];
    element.moduleName = new char[want.GetElement().GetModuleName().length() + 1];
    element.abilityName = new char[want.GetElement().GetAbilityName().length() + 1];
    if (strcpy_s(element.bundleName, want.GetElement().GetBundleName().length() + 1,
        want.GetElement().GetBundleName().c_str()) != 0) {
        return;
    }
    if (strcpy_s(element.moduleName, want.GetElement().GetModuleName().length() + 1,
        want.GetElement().GetModuleName().c_str()) != 0) {
        return;
    }
    if (strcpy_s(element.abilityName, want.GetElement().GetAbilityName().length() + 1,
        want.GetElement().GetAbilityName().c_str()) != 0) {
        return;
    }
}

void DestoryCWantElement(AbilityBase_Element& element)
{
    if (element.bundleName) {
        delete[] element.bundleName;
    }
    if (element.moduleName) {
        delete[] element.moduleName;
    }
    if (element.abilityName) {
        delete[] element.abilityName;
    }
}

void SetEmbeddedComponentOnError(FrameNode* frameNode, ArkUIEmbeddedComponentOptionHandle option)
{
    if (option->onError == nullptr) {
        return;
    }

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

void SetEmbeddedComponentOnTerminated(FrameNode* frameNode, ArkUIEmbeddedComponentOptionHandle option)
{
    if (option->onTerminated == nullptr) {
        return;
    }

    auto onTerminated = [option](int32_t code, const RefPtr<WantWrap>& wantWrap) {
        if (option == nullptr || option->onTerminated == nullptr) {
            TAG_LOGE(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "option is null, set EmbeddedComponent onTerminated failed");
            return;
        }

        onTerminatedFuncType func = reinterpret_cast<onTerminatedFuncType>(option->onTerminated);
        if (func == nullptr) {
            TAG_LOGE(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "func is null, set EmbeddedComponent onTerminated failed");
            return;
        }

        if (wantWrap) {
            AbilityBase_Want cwant;
            auto errCode = AAFwk::CWantManager::TransformToCWantWithoutElement(wantWrap->GetWant(), false, cwant);
            if (errCode != ABILITY_BASE_ERROR_CODE_NO_ERROR) {
                TAG_LOGE(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
                    "Get EmbeddedComponent cWant failed, error code is %{public}d", errCode);
                return;
            }

            AbilityBase_Element element;
            TransformToCWantElement(element, wantWrap->GetWant());
            cwant.element = element;
            func(code, &cwant);
            DestoryCWantElement(element);
        } else {
            func(code, nullptr);
        }
    };

    UIExtensionAdapter::SetEmbeddedComponentOnTerminated(frameNode, std::move(onTerminated));
}

void SetEmbeddedComponentOption(ArkUINodeHandle node, ArkUIEmbeddedComponentOptionHandle option)
{
    if (option == nullptr) {
        return;
    }

    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    if (frameNode == nullptr) {
        return;
    }

    SetEmbeddedComponentOnError(frameNode, option);
    SetEmbeddedComponentOnTerminated(frameNode, option);
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