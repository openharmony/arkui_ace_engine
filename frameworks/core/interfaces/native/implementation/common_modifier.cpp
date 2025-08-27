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
#include "core/components_ng/pattern/common_view/common_view_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CommonModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = CommonViewModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_LEFT);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // CommonModifier
namespace CommonInterfaceModifier {
void SetCommonOptionsImpl(Ark_NativePointer node)
{
    // do nothing
}
} // CommonInterfaceModifier
const GENERATED_ArkUICommonModifier* GetCommonModifier()
{
    static const GENERATED_ArkUICommonModifier ArkUICommonModifierImpl {
        CommonModifier::ConstructImpl,
        CommonInterfaceModifier::SetCommonOptionsImpl,
    };
    return &ArkUICommonModifierImpl;
}

}
