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
namespace EllipseShapeAccessor {
void DestroyPeerImpl(Ark_EllipseShape peer)
{
}
Ark_EllipseShape CtorImpl(const Opt_ShapeSize* options)
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_EllipseShape OffsetImpl(Ark_EllipseShape peer,
                            const Ark_Position* offset)
{
    return {};
}
Ark_EllipseShape FillImpl(Ark_EllipseShape peer,
                          const Ark_ResourceColor* color)
{
    return {};
}
Ark_EllipseShape PositionImpl(Ark_EllipseShape peer,
                              const Ark_Position* position)
{
    return {};
}
Ark_EllipseShape WidthImpl(Ark_EllipseShape peer,
                           const Ark_Length* width)
{
    return {};
}
Ark_EllipseShape HeightImpl(Ark_EllipseShape peer,
                            const Ark_Length* height)
{
    return {};
}
Ark_EllipseShape SizeImpl(Ark_EllipseShape peer,
                          const Ark_SizeOptions* size)
{
    return {};
}
} // EllipseShapeAccessor
const GENERATED_ArkUIEllipseShapeAccessor* GetEllipseShapeAccessor()
{
    static const GENERATED_ArkUIEllipseShapeAccessor EllipseShapeAccessorImpl {
        EllipseShapeAccessor::DestroyPeerImpl,
        EllipseShapeAccessor::CtorImpl,
        EllipseShapeAccessor::GetFinalizerImpl,
        EllipseShapeAccessor::OffsetImpl,
        EllipseShapeAccessor::FillImpl,
        EllipseShapeAccessor::PositionImpl,
        EllipseShapeAccessor::WidthImpl,
        EllipseShapeAccessor::HeightImpl,
        EllipseShapeAccessor::SizeImpl,
    };
    return &EllipseShapeAccessorImpl;
}

}
