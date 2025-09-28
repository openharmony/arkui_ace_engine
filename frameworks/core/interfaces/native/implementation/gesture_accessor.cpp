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

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GestureAccessor {
void DestroyPeerImpl(Ark_Gesture peer)
{
}
Ark_Gesture ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void TagImpl(Ark_Gesture peer,
             const Ark_String* tag)
{
}
void AllowedTypesImpl(Ark_Gesture peer,
                      const Array_SourceTool* types)
{
}
} // GestureAccessor
const GENERATED_ArkUIGestureAccessor* GetGestureAccessor()
{
    static const GENERATED_ArkUIGestureAccessor GestureAccessorImpl {
        GestureAccessor::DestroyPeerImpl,
        GestureAccessor::ConstructImpl,
        GestureAccessor::GetFinalizerImpl,
        GestureAccessor::TagImpl,
        GestureAccessor::AllowedTypesImpl,
    };
    return &GestureAccessorImpl;
}

}
