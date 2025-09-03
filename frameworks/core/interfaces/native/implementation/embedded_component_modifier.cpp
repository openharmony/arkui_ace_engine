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

namespace OHOS::Ace::NG::GeneratedModifier {
namespace EmbeddedComponentModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
#ifdef WINDOW_SCENE_SUPPORTED
    auto frameNode = UIExtensionModelNG::CreateEmbeddedFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
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
#ifdef WRONG_GEN
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelNG::SetWidth(frameNode, EMBEDDED_COMPONENT_MIN_WIDTH);
    ViewAbstractModelNG::SetHeight(frameNode, EMBEDDED_COMPONENT_MIN_HEIGHT);
    ViewAbstractModelNG::SetMinWidth(frameNode, EMBEDDED_COMPONENT_MIN_WIDTH);
    ViewAbstractModelNG::SetMinHeight(frameNode, EMBEDDED_COMPONENT_MIN_HEIGHT);
    auto typeOpt = Converter::OptConvert<SessionType>(type);
    auto sessionType = typeOpt ? typeOpt.value() : DEFAULT_EMBEDDED_SESSION_TYPE;
    UIExtensionModelNG::UpdateEmbeddedFrameNode(frameNode, CreateWant(loader), sessionType);
#endif
#endif
}
} // EmbeddedComponentInterfaceModifier
namespace EmbeddedComponentAttributeModifier {
void OnTerminatedImpl(Ark_NativePointer node,
                      const Opt_Callback_TerminationInfo_Void* value)
{
}
void OnErrorImpl(Ark_NativePointer node,
                 const Opt_ErrorCallback* value)
{
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
