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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CALLBACK_HELPER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CALLBACK_HELPER_H

#pragma once

#include <type_traits>
#include "core/pipeline_ng/pipeline_context.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#include "core/interfaces/native/utility/callback_keeper.h"
#include "core/interfaces/native/common/extension_companion_node.h"

namespace OHOS::Ace::NG {

namespace GeneratedApiImpl {
    ExtensionCompanionNode* GetCompanion(Ark_NodeHandle nodePtr);
}

template<typename CallbackType,
    std::enable_if_t<std::is_same_v<decltype(CallbackType().resource), Ark_CallbackResource>, bool> = true,
    std::enable_if_t<std::is_function_v<std::remove_pointer_t<decltype(CallbackType().call)>>, bool> = true
>
class CallbackHelper {
public:
    CallbackHelper() = default;

    CallbackHelper(const CallbackType &callback, Ark_VMContext vmcontext)
        : callback_(callback), vmContext_(vmcontext)
    {
        if (callback_.resource.hold) {
            (*callback_.resource.hold)(callback_.resource.resourceId);
        }
    }
    CallbackHelper(const CallbackHelper &other): callback_(other.callback_), vmContext_(other.vmContext_)
    {
        if (callback_.resource.hold) {
            (*callback_.resource.hold)(callback_.resource.resourceId);
        }
    }
    CallbackHelper(const CallbackType &callback, const FrameNode* frameNode = nullptr)
        : CallbackHelper<CallbackType>(callback, GetVMContext(frameNode)) {}
    ~CallbackHelper()
    {
        if (callback_.resource.release) {
            (*callback_.resource.release)(callback_.resource.resourceId);
        }
    }

    template<typename... Params>
    void Invoke(Params&&... args) const
    {
        if (callback_.call) {
            (*callback_.call)(callback_.resource.resourceId, std::forward<Params>(args)...);
        }
    }

    template <typename... Params>
    void InvokeSync(Params&&... args) const
    {
        if (callback_.callSync) {
            (*callback_.callSync)(vmContext_, callback_.resource.resourceId, std::forward<Params>(args)...);
        }
    }

    template <typename ResultType, typename ObtainResultCallbackType, typename... Params>
    ResultType InvokeWithObtainResult(Params&&... args) const
    {
        ResultType retValue {};
        auto handler = [&retValue](const void *valuePtr) {
            retValue = *(reinterpret_cast<const ResultType *>(valuePtr));
        };
        CallbackKeeper::InvokeWithResultHandler<ResultType, ObtainResultCallbackType>(
            handler, *this, std::forward<Params>(args)...
        );
        return retValue;
    }

    bool IsValid() const
    {
        return callback_.call != nullptr;
    }

    bool operator == (const CallbackHelper<CallbackType> &other) const
    {
        return callback_.call == other.callback_.call;
    }

    static Ark_VMContext GetVMContext(const FrameNode *frameNode)
    {
        if (frameNode) {
            if (auto pipeline = frameNode->GetContext(); pipeline) {
                auto rootPtr = reinterpret_cast<Ark_NodeHandle>(pipeline->GetRootElement().GetRawPtr());
                if (auto companionNode = GeneratedApiImpl::GetCompanion(rootPtr); companionNode) {
                    return companionNode->GetVMContext();
                }
            }
        }
        return nullptr;
    }
protected:
    CallbackType callback_  = {
        .resource = {.hold = nullptr, .release = nullptr},
        .call = nullptr
    };
    Ark_VMContext vmContext_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CALLBACK_HELPER_H
