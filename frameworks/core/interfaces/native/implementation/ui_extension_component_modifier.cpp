/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"
#include "core/interfaces/native/implementation/ui_extension_proxy_peer.h"
#include "want.h"
#endif //WINDOW_SCENE_SUPPORTED
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
namespace {
#ifdef WINDOW_SCENE_SUPPORTED
#ifdef WRONG_GEN
AAFwk::Want CreateWant(const Ark_Want* want)
{
    AAFwk::Want aaFwkWant;
    CHECK_NULL_RETURN(want, aaFwkWant);
    auto bundleName = Converter::OptConvert<std::string>(want->bundleName);
    auto abilityName = Converter::OptConvert<std::string>(want->abilityName);
    auto deviceId = Converter::OptConvert<std::string>(want->deviceId);
    auto moduleName = Converter::OptConvert<std::string>(want->moduleName);
    aaFwkWant.SetElementName(
        deviceId.value_or(""), bundleName.value_or(""), abilityName.value_or(""), moduleName.value_or(""));
    auto uri = Converter::OptConvert<std::string>(want->uri);
    if (uri) {
        aaFwkWant.SetUri(uri.value());
    }
    auto type = Converter::OptConvert<std::string>(want->type);
    if (type) {
        aaFwkWant.SetType(type.value());
    }
    auto flags = Converter::OptConvert<int32_t>(want->flags);
    if (flags) {
        aaFwkWant.SetFlags(flags.value());
    }
    auto action = Converter::OptConvert<std::string>(want->action);
    if (action) {
        aaFwkWant.SetAction(action.value());
    }
    LOGE("CreateWant - 'want->parameters' is not supported");
    auto entitiesArray = Converter::OptConvert<Array_String>(want->entities);
    if (entitiesArray) {
        auto entities = Converter::Convert<std::vector<std::string>>(entitiesArray.value());
        aaFwkWant.SetEntities(entities);
    }
    return aaFwkWant;
}
#endif
#endif //WINDOW_SCENE_SUPPORTED
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
#ifdef WINDOW_SCENE_SUPPORTED
const GENERATED_ArkUIUIExtensionProxyAccessor* GetUIExtensionProxyAccessor();
#endif //WINDOW_SCENE_SUPPORTED
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace UIExtensionComponentModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
#ifdef WINDOW_SCENE_SUPPORTED
    auto frameNode = UIExtensionModelNG::CreateFrameNode(id);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
#else
    return {};
#endif //WINDOW_SCENE_SUPPORTED
}
} // UIExtensionComponentModifier
namespace UIExtensionComponentInterfaceModifier {
void SetUIExtensionComponentOptionsImpl(Ark_NativePointer node,
                                        const Ark_Want* want,
                                        const Opt_UIExtensionOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(want);
    bool isTransferringCaller = false;
    bool densityDpi = false;
    auto extensionOptionOpt = Converter::OptConvert<Ark_UIExtensionOptions>(*options);
    if (extensionOptionOpt) {
        auto extensionOption = extensionOptionOpt.value();
        LOGE("UIExtensionComponentInterfaceModifier::SetUIExtensionComponentOptionsImpl - "
            "'UIExtensionOptions::areaChangePlaceholder' is not supported");
        LOGE("UIExtensionComponentInterfaceModifier::SetUIExtensionComponentOptionsImpl - "
            "'UIExtensionOptions::placeholder' is not supported");
        auto isTransferringCallerOpt = Converter::OptConvert<bool>(extensionOption.isTransferringCaller);
        if (isTransferringCallerOpt) {
            isTransferringCaller = isTransferringCallerOpt.value();
        }
        auto dpiFollowStrategy = Converter::OptConvert<Ark_DpiFollowStrategy>(extensionOption.dpiFollowStrategy);
        if (dpiFollowStrategy) {
            densityDpi = (dpiFollowStrategy.value() == ARK_DPI_FOLLOW_STRATEGY_FOLLOW_HOST_DPI) ? true : false;
        }
    }
#ifdef WINDOW_SCENE_SUPPORTED
#ifdef WRONG_GEN
    UIExtensionModelNG::UpdateWant(frameNode, CreateWant(want), isTransferringCaller, densityDpi);
#endif
#endif //WINDOW_SCENE_SUPPORTED
}
} // UIExtensionComponentInterfaceModifier
namespace UIExtensionComponentAttributeModifier {
void OnRemoteReadyImpl(Ark_NativePointer node,
                       const Opt_Callback_UIExtensionProxy_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
#ifdef WINDOW_SCENE_SUPPORTED
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onRemoteReady =
        [arkCallback = CallbackHelper(*optValue)](const RefPtr<UIExtensionProxy>& proxy) {
            auto accessor = GetUIExtensionProxyAccessor();
            CHECK_NULL_VOID(accessor);
            auto peer = accessor->ctor();
            CHECK_NULL_VOID(peer);
            auto uiExtensionProxyPeerPtr = reinterpret_cast<UIExtensionProxyPeer*>(peer);
            uiExtensionProxyPeerPtr->SetProxy(proxy);
            arkCallback.Invoke(peer);
        };
    UIExtensionModelNG::SetOnRemoteReady(frameNode, std::move(onRemoteReady));
#endif //WINDOW_SCENE_SUPPORTED
}
void OnReceiveImpl(Ark_NativePointer node,
                   const Opt_Callback_Map_String_Object_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("UIExtensionComponentInterfaceModifier::OnReceiveImpl - is not supported");
}
void OnResultImpl(Ark_NativePointer node,
                  const Opt_Callback_Literal_Number_code__want_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
#ifdef WINDOW_SCENE_SUPPORTED
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onResult =
        [arkCallback = CallbackHelper(*optValue)](int32_t code, const AAFwk::Want& want) {
#ifdef WRONG_GEN
            Ark_Want arkWant;
            auto bundleName = want.GetBundle();
            arkWant.bundleName = Converter::ArkValue<Opt_String>(bundleName);
            auto abilityName = want.GetElement().GetAbilityName();
            arkWant.abilityName = Converter::ArkValue<Opt_String>(abilityName);
            auto deviceId = want.GetDeviceId();
            arkWant.deviceId = Converter::ArkValue<Opt_String>(deviceId);
            auto uri = want.GetUriString();
            arkWant.uri = Converter::ArkValue<Opt_String>(uri);
            auto type = want.GetType();
            arkWant.type = Converter::ArkValue<Opt_String>(type);
            auto flags = static_cast<int32_t>(want.GetFlags());
            arkWant.flags = Converter::ArkValue<Opt_Number>(flags);
            auto action = want.GetAction();
            arkWant.action = Converter::ArkValue<Opt_String>(action);
            LOGE("UIExtensionComponentInterfaceModifier::OnResultImpl - "
                "Ark_Want::parameters is not supported");
            auto entities = want.GetEntities();
            Converter::ArkArrayHolder<Array_String> stringHolder(entities);
            Array_String stringArrayValues = stringHolder.ArkValue();
            arkWant.entities = Converter::ArkValue<Opt_Array_String>(stringArrayValues);
            auto moduleName = want.GetModuleName();
            arkWant.moduleName = Converter::ArkValue<Opt_String>(moduleName);

            Ark_Literal_Number_code__want parameter;
            parameter.code = Converter::ArkValue<Ark_Number>(code);
            parameter.want = Converter::ArkValue<Opt_Want>(arkWant);
            arkCallback.Invoke(parameter);
#endif
        };
    UIExtensionModelNG::SetOnResult(frameNode, std::move(onResult));
#endif //WINDOW_SCENE_SUPPORTED
}
void OnReleaseImpl(Ark_NativePointer node,
                   const Opt_Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
#ifdef WINDOW_SCENE_SUPPORTED
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onRelease =
        [arkCallback = CallbackHelper(*optValue)](int32_t index) {
            Ark_Number arkIndex = Converter::ArkValue<Ark_Number>(index);
            arkCallback.Invoke(arkIndex);
        };
    UIExtensionModelNG::SetOnRelease(frameNode, std::move(onRelease));
#endif //WINDOW_SCENE_SUPPORTED
}
void OnErrorImpl(Ark_NativePointer node,
                 const Opt_ErrorCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
#ifdef WINDOW_SCENE_SUPPORTED
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto instanceId = ContainerScope::CurrentId();
    auto weakNode = AceType::WeakClaim<NG::FrameNode>(frameNode);
    auto onError = [arkCallback = CallbackHelper(*optValue), instanceId, weakNode](
        int32_t code, const std::string& name, const std::string& message) {
        ContainerScope scope(instanceId);
        auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(weakNode);
        arkCallback.Invoke(Ark_BusinessError{
            .name  = Converter::ArkValue<Ark_String>(name, Converter::FC),
            .message = Converter::ArkValue<Ark_String>(message, Converter::FC),
            .code = Converter::ArkValue<Ark_Number>(code)});
    };
    UIExtensionModelNG::SetOnError(frameNode, std::move(onError));
#endif //WINDOW_SCENE_SUPPORTED
}
void OnTerminatedImpl(Ark_NativePointer node,
                      const Opt_Callback_TerminationInfo_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
#ifdef WINDOW_SCENE_SUPPORTED
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onTerminated =
        [arkCallback = CallbackHelper(*optValue)](int32_t code, const RefPtr<WantWrap>& wantWrape) {
#ifdef WRONG_GEN
            auto want = wantWrape->GetWant();
            Ark_Want arkWant;
            auto bundleName = want.GetBundle();
            arkWant.bundleName = Converter::ArkValue<Opt_String>(bundleName);
            auto abilityName = want.GetElement().GetAbilityName();
            arkWant.abilityName = Converter::ArkValue<Opt_String>(abilityName);
            auto deviceId = want.GetDeviceId();
            arkWant.deviceId = Converter::ArkValue<Opt_String>(deviceId);
            auto uri = want.GetUriString();
            arkWant.uri = Converter::ArkValue<Opt_String>(uri);
            auto type = want.GetType();
            arkWant.type = Converter::ArkValue<Opt_String>(type);
            auto flags = static_cast<int32_t>(want.GetFlags());
            arkWant.flags = Converter::ArkValue<Opt_Number>(flags);
            auto action = want.GetAction();
            arkWant.action = Converter::ArkValue<Opt_String>(action);
            LOGE("UIExtensionComponentInterfaceModifier::OnTerminatedImpl - "
                "Ark_Want::parameters is not supported");
            auto entities = want.GetEntities();
            Converter::ArkArrayHolder<Array_String> stringHolder(entities);
            Array_String stringArrayValues = stringHolder.ArkValue();
            arkWant.entities = Converter::ArkValue<Opt_Array_String>(stringArrayValues);
            auto moduleName = want.GetModuleName();
            arkWant.moduleName = Converter::ArkValue<Opt_String>(moduleName);

            Ark_TerminationInfo terminatedInfo;
            terminatedInfo.code = Converter::ArkValue<Ark_Number>(code);
            terminatedInfo.want = Converter::ArkValue<Opt_Want>(arkWant);
            arkCallback.Invoke(terminatedInfo);
#endif
        };
    UIExtensionModelNG::SetOnTerminated(frameNode, std::move(onTerminated));
#endif //WINDOW_SCENE_SUPPORTED
}
void OnDrawReadyImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
} // UIExtensionComponentAttributeModifier
const GENERATED_ArkUIUIExtensionComponentModifier* GetUIExtensionComponentModifier()
{
    static const GENERATED_ArkUIUIExtensionComponentModifier ArkUIUIExtensionComponentModifierImpl {
        UIExtensionComponentModifier::ConstructImpl,
        UIExtensionComponentInterfaceModifier::SetUIExtensionComponentOptionsImpl,
        UIExtensionComponentAttributeModifier::OnRemoteReadyImpl,
        UIExtensionComponentAttributeModifier::OnReceiveImpl,
        UIExtensionComponentAttributeModifier::OnResultImpl,
        UIExtensionComponentAttributeModifier::OnReleaseImpl,
        UIExtensionComponentAttributeModifier::OnErrorImpl,
        UIExtensionComponentAttributeModifier::OnTerminatedImpl,
        UIExtensionComponentAttributeModifier::OnDrawReadyImpl,
    };
    return &ArkUIUIExtensionComponentModifierImpl;
}

}
