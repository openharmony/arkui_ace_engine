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
namespace ShapeMaskAccessor {
void DestroyPeerImpl(Ark_ShapeMask peer)
{
}
Ark_ShapeMask CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetRectShapeImpl(Ark_ShapeMask peer,
                      const Ark_Rect* rect)
{
}
void SetRoundRectShapeImpl(Ark_ShapeMask peer,
                           const Ark_RoundRect* roundRect)
{
}
void SetCircleShapeImpl(Ark_ShapeMask peer,
                        const Ark_Circle* circle)
{
}
void SetOvalShapeImpl(Ark_ShapeMask peer,
                      const Ark_Rect* oval)
{
}
void SetCommandPathImpl(Ark_ShapeMask peer,
                        const Ark_CommandPath* path)
{
}
Ark_Number GetFillColorImpl(Ark_ShapeMask peer)
{
    return {};
}
void SetFillColorImpl(Ark_ShapeMask peer,
                      const Ark_Number* fillColor)
{
}
Ark_Number GetStrokeColorImpl(Ark_ShapeMask peer)
{
    return {};
}
void SetStrokeColorImpl(Ark_ShapeMask peer,
                        const Ark_Number* strokeColor)
{
}
Ark_Number GetStrokeWidthImpl(Ark_ShapeMask peer)
{
    return {};
}
void SetStrokeWidthImpl(Ark_ShapeMask peer,
                        const Ark_Number* strokeWidth)
{
}
} // ShapeMaskAccessor
const GENERATED_ArkUIShapeMaskAccessor* GetShapeMaskAccessor()
{
    static const GENERATED_ArkUIShapeMaskAccessor ShapeMaskAccessorImpl {
        ShapeMaskAccessor::DestroyPeerImpl,
        ShapeMaskAccessor::CtorImpl,
        ShapeMaskAccessor::GetFinalizerImpl,
        ShapeMaskAccessor::SetRectShapeImpl,
        ShapeMaskAccessor::SetRoundRectShapeImpl,
        ShapeMaskAccessor::SetCircleShapeImpl,
        ShapeMaskAccessor::SetOvalShapeImpl,
        ShapeMaskAccessor::SetCommandPathImpl,
        ShapeMaskAccessor::GetFillColorImpl,
        ShapeMaskAccessor::SetFillColorImpl,
        ShapeMaskAccessor::GetStrokeColorImpl,
        ShapeMaskAccessor::SetStrokeColorImpl,
        ShapeMaskAccessor::GetStrokeWidthImpl,
        ShapeMaskAccessor::SetStrokeWidthImpl,
    };
    return &ShapeMaskAccessorImpl;
}

}
