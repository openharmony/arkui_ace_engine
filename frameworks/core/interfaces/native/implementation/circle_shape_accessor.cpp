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
namespace CircleShapeAccessor {
void DestroyPeerImpl(Ark_CircleShape peer)
{
}
Ark_CircleShape CtorImpl(const Opt_ShapeSize* options)
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_CircleShape OffsetImpl(Ark_CircleShape peer,
                           const Ark_Position* offset)
{
    return {};
}
Ark_CircleShape FillImpl(Ark_CircleShape peer,
                         const Ark_ResourceColor* color)
{
    return {};
}
Ark_CircleShape PositionImpl(Ark_CircleShape peer,
                             const Ark_Position* position)
{
    return {};
}
Ark_CircleShape WidthImpl(Ark_CircleShape peer,
                          const Ark_Length* width)
{
    return {};
}
Ark_CircleShape HeightImpl(Ark_CircleShape peer,
                           const Ark_Length* height)
{
    return {};
}
Ark_CircleShape SizeImpl(Ark_CircleShape peer,
                         const Ark_SizeOptions* size)
{
    return {};
}
} // CircleShapeAccessor
const GENERATED_ArkUICircleShapeAccessor* GetCircleShapeAccessor()
{
    static const GENERATED_ArkUICircleShapeAccessor CircleShapeAccessorImpl {
        CircleShapeAccessor::DestroyPeerImpl,
        CircleShapeAccessor::CtorImpl,
        CircleShapeAccessor::GetFinalizerImpl,
        CircleShapeAccessor::OffsetImpl,
        CircleShapeAccessor::FillImpl,
        CircleShapeAccessor::PositionImpl,
        CircleShapeAccessor::WidthImpl,
        CircleShapeAccessor::HeightImpl,
        CircleShapeAccessor::SizeImpl,
    };
    return &CircleShapeAccessorImpl;
}

struct CircleShapePeer {
    virtual ~CircleShapePeer() = default;
};
}
