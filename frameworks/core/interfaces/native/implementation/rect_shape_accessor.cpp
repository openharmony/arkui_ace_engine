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
namespace RectShapeAccessor {
void DestroyPeerImpl(Ark_RectShape peer)
{
}
Ark_RectShape CtorImpl(const Opt_Union_RectShapeOptions_RoundRectShapeOptions* options)
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_RectShape OffsetImpl(Ark_RectShape peer,
                         const Ark_Position* offset)
{
    return {};
}
Ark_RectShape FillImpl(Ark_RectShape peer,
                       const Ark_ResourceColor* color)
{
    return {};
}
Ark_RectShape PositionImpl(Ark_RectShape peer,
                           const Ark_Position* position)
{
    return {};
}
Ark_RectShape WidthImpl(Ark_RectShape peer,
                        const Ark_Length* width)
{
    return {};
}
Ark_RectShape HeightImpl(Ark_RectShape peer,
                         const Ark_Length* height)
{
    return {};
}
Ark_RectShape SizeImpl(Ark_RectShape peer,
                       const Ark_SizeOptions* size)
{
    return {};
}
Ark_RectShape RadiusWidthImpl(Ark_RectShape peer,
                              const Ark_Union_Number_String* rWidth)
{
    return {};
}
Ark_RectShape RadiusHeightImpl(Ark_RectShape peer,
                               const Ark_Union_Number_String* rHeight)
{
    return {};
}
Ark_RectShape RadiusImpl(Ark_RectShape peer,
                         const Ark_Union_Number_String_Array_Union_Number_String* radius)
{
    return {};
}
} // RectShapeAccessor
const GENERATED_ArkUIRectShapeAccessor* GetRectShapeAccessor()
{
    static const GENERATED_ArkUIRectShapeAccessor RectShapeAccessorImpl {
        RectShapeAccessor::DestroyPeerImpl,
        RectShapeAccessor::CtorImpl,
        RectShapeAccessor::GetFinalizerImpl,
        RectShapeAccessor::OffsetImpl,
        RectShapeAccessor::FillImpl,
        RectShapeAccessor::PositionImpl,
        RectShapeAccessor::WidthImpl,
        RectShapeAccessor::HeightImpl,
        RectShapeAccessor::SizeImpl,
        RectShapeAccessor::RadiusWidthImpl,
        RectShapeAccessor::RadiusHeightImpl,
        RectShapeAccessor::RadiusImpl,
    };
    return &RectShapeAccessorImpl;
}

}
