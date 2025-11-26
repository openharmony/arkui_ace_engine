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
#if !defined(PREVIEW) && !defined(ARKUI_CAPI_UNITTEST)
#include "core/components_ng/syntax/static/detached_free_root_proxy_node.h"
#endif // !defined(PREVIEW) && !defined(ARKUI_CAPI_UNITTEST)
#include "core/pipeline_ng/pipeline_context.h"
#include "core/interfaces/native/common/extension_companion_node.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#include "core/interfaces/native/utility/callback_keeper.h"
#include "core/interfaces/native/utility/converter.h"

namespace OHOS::Ace::NG {

namespace {
#if !defined(PREVIEW) && !defined(ARKUI_CAPI_UNITTEST)
RefPtr<OHOS::Ace::NG::DetachedFreeRootProxyNode> CreateProxyNode(const RefPtr<UINode>& uiNode)
{
    CHECK_NULL_RETURN(uiNode, nullptr);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto instanceId = container->GetInstanceId();
    auto proxyNode = AceType::MakeRefPtr<DetachedFreeRootProxyNode>(instanceId);
    CHECK_NULL_RETURN(proxyNode, nullptr);
    proxyNode->AddChild(uiNode);
    return proxyNode;
}
#endif // !defined(PREVIEW) && !defined(ARKUI_CAPI_UNITTEST)
}

namespace GeneratedApiImpl {
    ExtensionCompanionNode* GetCompanion(Ark_NodeHandle nodePtr);
}

template<typename CallbackType,
    std::enable_if_t<std::is_same_v<decltype(CallbackType().resource), Ark_CallbackResource>, bool> = true,
    std::enable_if_t<std::is_function_v<std::remove_pointer_t<decltype(CallbackType().call)>>, bool> = true
>
class CallbackHelper : public virtual Referenced {
public:
    CallbackHelper() = default;

    CallbackHelper(const CallbackType &callback, Ark_VMContext vmcontext)
        : callback_(callback)
    {
        if (callback_.resource.hold) {
            (*callback_.resource.hold)(callback_.resource.resourceId);
        }
    }
    CallbackHelper(const CallbackHelper &other): callback_(other.callback_)
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
            Ark_VMContext vmContext = GetVMContext();
#if !defined(PREVIEW) && !defined(ARKUI_CAPI_UNITTEST)
            if (vmContext == nullptr) {
                LOGF_ABORT("InvokeSync VMContext is null.");
            }
#endif
            (*callback_.callSync)(vmContext, callback_.resource.resourceId, std::forward<Params>(args)...);
        }
    }

    // this works for primitive ArkResultType types only - enum/Ark_NativePtr/structs_without_any_pointers
    template <typename ArkResultType, typename ContinuationType, typename... Params>
    ArkResultType InvokeWithObtainResult(Params&&... args) const
    {
        static_assert(!std::is_class_v<ArkResultType>,
            "Can't return complex type. Use other Invoke functions or process result within custom callback!");
        ArkResultType retValue {};
        auto handler = [&retValue](ArkResultType value) {
            retValue = value;
        };
        auto continuation = CallbackKeeper::Claim<ContinuationType>(std::move(handler));
        InvokeSync(std::forward<Params>(args)..., continuation.ArkValue());
        return retValue;
    }

    // use for callbacks that return other callbacks (e.g. drag start which returns a builder callback)
    template <typename ArkResultType, typename ContinuationType, typename... Params>
    std::unique_ptr<CallbackHelper<ArkResultType>> InvokeWithObtainCallback(Params&&... args) const
    {
        std::unique_ptr<CallbackHelper<ArkResultType>> retValue = nullptr;
        auto handler = [&retValue](ArkResultType value) {
            retValue = std::make_unique<CallbackHelper<ArkResultType>>(value);
        };
        auto continuation = CallbackKeeper::Claim<ContinuationType>(std::move(handler));
        InvokeSync(std::forward<Params>(args)..., continuation.ArkValue());
        return std::move(retValue);
    }

    template <typename ResultType, typename ArkResultType, typename ContinuationType, typename... Params>
    ResultType InvokeWithConvertResult(Params&&... args) const
    {
        ResultType retValue {};
        auto handler = [&retValue](ArkResultType value) {
            retValue = Converter::Convert<ResultType>(value);
        };
        auto continuation = CallbackKeeper::Claim<ContinuationType>(std::move(handler));
        InvokeSync(std::forward<Params>(args)..., continuation.ArkValue());
        return retValue;
    }

    template <typename ResultType, typename ArkResultType, typename ContinuationType, typename... Params>
    std::optional<ResultType> InvokeWithOptConvertResult(Params&&... args) const
    {
        std::optional<ResultType> retValueOpt = std::nullopt;
        auto handler = [&retValueOpt](ArkResultType value) {
            retValueOpt = Converter::OptConvert<ResultType>(value);
        };
        auto continuation = CallbackKeeper::Claim<ContinuationType>(std::move(handler));
        InvokeSync(std::forward<Params>(args)..., continuation.ArkValue());
        return retValueOpt;
    }

    template<typename... Params>
    RefPtr<UINode> BuildSync(Params&&... args) const
    {
        auto node = Referenced::Claim(reinterpret_cast<UINode*>(
            InvokeWithObtainResult<Ark_NativePointer, Callback_Pointer_Void>(std::forward<Params>(args)...)));
#if !defined(PREVIEW) && !defined(ARKUI_CAPI_UNITTEST)
            return CreateProxyNode(node);
#else
            return node;
#endif // !defined(PREVIEW) && !defined(ARKUI_CAPI_UNITTEST)
    }

    template <typename... Params>
    void BuildAsync(const std::function<void(const RefPtr<UINode>&)>&& builderHandler, Params&&... args) const
    {
        auto handler =
            [builderHandler = std::move(builderHandler)](Ark_NativePointer retValue) {
            CHECK_NULL_VOID(builderHandler);
            auto node = Referenced::Claim(reinterpret_cast<UINode*>(retValue));
            CHECK_NULL_VOID(node);
#if !defined(PREVIEW) && !defined(ARKUI_CAPI_UNITTEST)
            builderHandler(CreateProxyNode(node));
#else
            builderHandler(node);
#endif // !defined(PREVIEW) && !defined(ARKUI_CAPI_UNITTEST)
        };
        auto continuation = CallbackKeeper::Claim<Callback_Pointer_Void>(std::move(handler));
        Invoke(std::forward<Params>(args)..., continuation.ArkValue());
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
        auto container = Container::CurrentSafely();
        CHECK_NULL_RETURN(container, nullptr);
        auto frontEnd = container->GetFrontend();
        CHECK_NULL_RETURN(frontEnd, nullptr);
        if (!frontEnd->GetEnv() && container->GetSubFrontend()) {
            frontEnd = container->GetSubFrontend(); // return ArktsFrontend when 1.1 hybrid 1.2
        }
        return Ark_VMContext(frontEnd->GetEnv());
    }

    const CallbackType& GetCallback()
    {
        return callback_;
    }
protected:
    CallbackType callback_  = {
        .resource = {.hold = nullptr, .release = nullptr},
        .call = nullptr,
        .callSync = nullptr
    };
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CALLBACK_HELPER_H
