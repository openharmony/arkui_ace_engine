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
#include "core/interfaces/native/common/extension_companion_node.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#include "core/interfaces/native/utility/callback_keeper.h"
#include "core/interfaces/native/utility/converter.h"

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
    CallbackHelper(const CallbackType &callback)
        : CallbackHelper<CallbackType>(callback, GetVMContext()) {}
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

    // this works for primitive ArkResultType types only - enum/Ark_NativePtr/structs_without_any_pointers
    template <typename ArkResultType, typename ContinuationType, typename... Params>
    ArkResultType InvokeWithObtainResult(Params&&... args) const
    {
        ArkResultType retValue {};
        CallbackKeeper::AnyResultHandlerType handler = [&retValue](const void *valuePtr) {
            retValue = *(reinterpret_cast<const ArkResultType *>(valuePtr));
        };
        auto continuation = CallbackKeeper::RegisterReverseCallback<ContinuationType>(handler);
        InvokeSync(std::forward<Params>(args)..., continuation);
        CallbackKeeper::ReleaseReverseCallback(continuation);
        return retValue;
    }

    // use for callbacks that return other callbacks (e.g. drag start which returns a builder callback)
    template <typename ArkResultType, typename ContinuationType, typename... Params>
    std::unique_ptr<CallbackHelper<ArkResultType>> InvokeWithObtainCallback(Params&&... args) const
    {
        std::unique_ptr<CallbackHelper<ArkResultType>> retValue = nullptr;
        CallbackKeeper::AnyResultHandlerType handler = [&retValue](const void *valuePtr) {
            retValue = std::make_unique<CallbackHelper<ArkResultType>>(*(
                reinterpret_cast<const ArkResultType *>(valuePtr)));
        };
        auto continuation = CallbackKeeper::RegisterReverseCallback<ContinuationType>(handler);
        InvokeSync(std::forward<Params>(args)..., continuation);
        CallbackKeeper::ReleaseReverseCallback(continuation);
        return std::move(retValue);
    }

    template <typename ResultType, typename ArkResultType, typename ContinuationType, typename... Params>
    std::optional<ResultType> InvokeWithOptConvertResult(Params&&... args) const
    {
        std::optional<ResultType> retValueOpt = std::nullopt;
        CallbackKeeper::AnyResultHandlerType handler = [&retValueOpt](const void *valuePtr) {
            retValueOpt = Converter::OptConvert<ResultType>(*(reinterpret_cast<const ArkResultType *>(valuePtr)));
        };
        auto continuation = CallbackKeeper::RegisterReverseCallback<ContinuationType>(handler);
        InvokeSync(std::forward<Params>(args)..., continuation);
        CallbackKeeper::ReleaseReverseCallback(continuation);
        return retValueOpt;
    }

    template<typename... Params>
    RefPtr<UINode> BuildSync(Params&&... args) const
    {
        return Referenced::Claim(reinterpret_cast<UINode*>(
            InvokeWithObtainResult<Ark_NativePointer, Callback_Pointer_Void>(std::forward<Params>(args)...)));
    }

    template <typename... Params>
    void BuildAsync(const std::function<void(const RefPtr<UINode>&)>&& builderHandler, Params&&... args) const
    {
        CallbackKeeper::AnyResultHandlerType handler =
            [builderHandler = std::move(builderHandler)](const void *valuePtr) {
            auto retValue = *(reinterpret_cast<const Ark_NativePointer *>(valuePtr));
            auto node = Referenced::Claim(reinterpret_cast<UINode*>(retValue));
            builderHandler(node);
        };
        auto continuation = CallbackKeeper::RegisterReverseCallback<Callback_Pointer_Void>(handler);
        Invoke(std::forward<Params>(args)..., continuation);
        CallbackKeeper::ReleaseReverseCallback(continuation);
    }

    bool IsValid() const
    {
        return callback_.call != nullptr;
    }

    bool operator == (const CallbackHelper<CallbackType> &other) const
    {
        return callback_.call == other.callback_.call &&
            callback_.resource.resourceId == other.callback_.resource.resourceId;
    }

    static Ark_VMContext GetVMContext()
    {
        auto pipeline = PipelineContext::GetCurrentContextSafely();
        CHECK_NULL_RETURN(pipeline, nullptr);
        auto rootNode = pipeline->GetRootElement();
        CHECK_NULL_RETURN(rootNode, nullptr);
        auto rootPtr = reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(rootNode));
        CHECK_NULL_RETURN(rootPtr, nullptr);
        auto companionNode = GeneratedApiImpl::GetCompanion(rootPtr);
        CHECK_NULL_RETURN(companionNode, nullptr);
        return companionNode->GetVMContext();
    }

    const CallbackType GetCallback()
    {
        return callback_;
    }
protected:
    CallbackType callback_  = {
        .resource = {.hold = nullptr, .release = nullptr},
        .call = nullptr,
        .callSync = nullptr
    };
    Ark_VMContext vmContext_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CALLBACK_HELPER_H
