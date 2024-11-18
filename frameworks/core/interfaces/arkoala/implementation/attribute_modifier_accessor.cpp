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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace AttributeModifierAccessor {
AttributeModifierPeer* CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return 0;
}
void ApplyNormalAttributeImpl(AttributeModifierPeer* peer,
                              const Ark_CustomObject* instance)
{
}
void ApplyPressedAttributeImpl(AttributeModifierPeer* peer,
                               const Ark_CustomObject* instance)
{
}
void ApplyFocusedAttributeImpl(AttributeModifierPeer* peer,
                               const Ark_CustomObject* instance)
{
}
void ApplyDisabledAttributeImpl(AttributeModifierPeer* peer,
                                const Ark_CustomObject* instance)
{
}
void ApplySelectedAttributeImpl(AttributeModifierPeer* peer,
                                const Ark_CustomObject* instance)
{
}
} // AttributeModifierAccessor
const GENERATED_ArkUIAttributeModifierAccessor* GetAttributeModifierAccessor()
{
    static const GENERATED_ArkUIAttributeModifierAccessor AttributeModifierAccessorImpl {
        AttributeModifierAccessor::CtorImpl,
        AttributeModifierAccessor::GetFinalizerImpl,
        AttributeModifierAccessor::ApplyNormalAttributeImpl,
        AttributeModifierAccessor::ApplyPressedAttributeImpl,
        AttributeModifierAccessor::ApplyFocusedAttributeImpl,
        AttributeModifierAccessor::ApplyDisabledAttributeImpl,
        AttributeModifierAccessor::ApplySelectedAttributeImpl,
    };
    return &AttributeModifierAccessorImpl;
}

}
