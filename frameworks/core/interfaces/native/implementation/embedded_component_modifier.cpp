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

#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "want.h"
#endif
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
namespace {
#ifdef WINDOW_SCENE_SUPPORTED
#endif //WINDOW_SCENE_SUPPORTED
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace EmbeddedComponentModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
#ifdef WINDOW_SCENE_SUPPORTED
    return {};
#else
    return {};
#endif // WINDOW_SCENE_SUPPORTED
}
} // EmbeddedComponentModifier
namespace EmbeddedComponentInterfaceModifier {
void SetEmbeddedComponentOptionsImpl(Ark_NativePointer node,
                                     const Ark_Want* loader,
                                     Ark_EmbeddedType type)
{
#ifdef WINDOW_SCENE_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    // need check
    // ViewAbstractModelNG::SetWidth(frameNode, EMBEDDED_COMPONENT_MIN_WIDTH);
    // ViewAbstractModelNG::SetHeight(frameNode, EMBEDDED_COMPONENT_MIN_HEIGHT);
    // ViewAbstractModelNG::SetMinWidth(frameNode, EMBEDDED_COMPONENT_MIN_WIDTH);
    // ViewAbstractModelNG::SetMinHeight(frameNode, EMBEDDED_COMPONENT_MIN_HEIGHT);
    // auto typeOpt = Converter::OptConvert<SessionType>(type);
    // auto sessionType = typeOpt ? typeOpt.value() : DEFAULT_EMBEDDED_SESSION_TYPE;
    // need check
    // UIExtensionModelNG::UpdateEmbeddedFrameNode(frameNode, CreateWant(loader), sessionType);
#endif
}
} // EmbeddedComponentInterfaceModifier
namespace EmbeddedComponentAttributeModifier {
void OnTerminatedImpl(Ark_NativePointer node,
                      const Callback_TerminationInfo_Void* value)
{
#ifdef WINDOW_SCENE_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onTerminated =
        [arkCallback = CallbackHelper(*value)](int32_t code, const RefPtr<WantWrap>& wantWrape) {
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
            LOGE("EmbeddedComponentModifier::OnTerminatedImpl - "
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
        };
    // need check
    // UIExtensionModelNG::SetOnTerminated(frameNode, std::move(onTerminated));
#endif
}
void OnErrorImpl(Ark_NativePointer node,
                 const ErrorCallback* value)
{
#ifdef WINDOW_SCENE_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto instanceId = ContainerScope::CurrentId();
    auto weakNode = AceType::WeakClaim<NG::FrameNode>(frameNode);
    auto onError = [arkCallback = CallbackHelper(*value), instanceId, weakNode](
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
    // need check
    // UIExtensionModelNG::SetOnError(frameNode, std::move(onError));
#endif
}
} // EmbeddedComponentAttributeModifier
const GENERATED_ArkUIEmbeddedComponentModifier* GetEmbeddedComponentModifier()
{
    static const GENERATED_ArkUIEmbeddedComponentModifier ArkUIEmbeddedComponentModifierImpl {
        EmbeddedComponentModifier::ConstructImpl,
        EmbeddedComponentInterfaceModifier::SetEmbeddedComponentOptionsImpl,
        EmbeddedComponentAttributeModifier::OnTerminatedImpl,
        EmbeddedComponentAttributeModifier::OnErrorImpl,
    };
    return &ArkUIEmbeddedComponentModifierImpl;
}

}
