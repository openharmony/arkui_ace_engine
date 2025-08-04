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
namespace drawing_RoundRectAccessor {
void DestroyPeerImpl(Ark_drawing_RoundRect peer)
{
}
Ark_drawing_RoundRect ConstructImpl(const Ark_common2D_Rect* rect,
                                    const Ark_Number* xRadii,
                                    const Ark_Number* yRadii)
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetCornerImpl(Ark_drawing_RoundRect peer,
                   Ark_drawing_CornerPos pos,
                   const Ark_Number* x,
                   const Ark_Number* y)
{
}
Ark_common2D_Point GetCornerImpl(Ark_drawing_RoundRect peer,
                                 Ark_drawing_CornerPos pos)
{
    return {};
}
void OffsetImpl(Ark_drawing_RoundRect peer,
                const Ark_Number* dx,
                const Ark_Number* dy)
{
}
} // drawing_RoundRectAccessor
const GENERATED_ArkUIDrawing_RoundRectAccessor* GetDrawing_RoundRectAccessor()
{
    static const GENERATED_ArkUIDrawing_RoundRectAccessor Drawing_RoundRectAccessorImpl {
        drawing_RoundRectAccessor::DestroyPeerImpl,
        drawing_RoundRectAccessor::ConstructImpl,
        drawing_RoundRectAccessor::GetFinalizerImpl,
        drawing_RoundRectAccessor::SetCornerImpl,
        drawing_RoundRectAccessor::GetCornerImpl,
        drawing_RoundRectAccessor::OffsetImpl,
    };
    return &Drawing_RoundRectAccessorImpl;
}

}
