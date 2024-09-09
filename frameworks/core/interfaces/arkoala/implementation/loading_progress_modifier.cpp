/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "arkoala_api.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_model_ng.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "core/interfaces/arkoala/utility/converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LoadingProgressInterfaceModifier {
void SetLoadingProgressOptionsImpl(Ark_NativePointer node)
{
    LOGE("ARKOALA LoadingProgressInterfaceModifier::SetLoadingProgressOptionsImpl -> Method is not implemented");
}
} // LoadingProgressInterfaceModifier
namespace LoadingProgressAttributeModifier {
void ColorImpl(Ark_NativePointer node,
               const ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (auto color = Converter::OptConvert<Color>(*value); color) {
        LoadingProgressModelNG::SetColor(frameNode, color.value());
    }
}
void EnableLoadingImpl(Ark_NativePointer node,
                       Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LoadingProgressModelNG::SetEnableLoading(frameNode, Converter::Convert<bool>(value));
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Ark_CustomObject* modifier)
{
}
} // LoadingProgressAttributeModifier
const GENERATED_ArkUILoadingProgressModifier* GetLoadingProgressModifier()
{
    static const GENERATED_ArkUILoadingProgressModifier ArkUILoadingProgressModifierImpl {
        LoadingProgressInterfaceModifier::SetLoadingProgressOptionsImpl,
        LoadingProgressAttributeModifier::ColorImpl,
        LoadingProgressAttributeModifier::EnableLoadingImpl,
        LoadingProgressAttributeModifier::ContentModifierImpl,
    };
    return &ArkUILoadingProgressModifierImpl;
}

}
