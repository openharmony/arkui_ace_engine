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
namespace PathShapeAccessor {
void DestroyPeerImpl(Ark_PathShape peer)
{
}
Ark_PathShape CtorImpl(const Opt_PathShapeOptions* options)
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_PathShape OffsetImpl(Ark_PathShape peer,
                         const Ark_Position* offset)
{
    return {};
}
Ark_PathShape FillImpl(Ark_PathShape peer,
                       const Ark_ResourceColor* color)
{
    return {};
}
Ark_PathShape PositionImpl(Ark_PathShape peer,
                           const Ark_Position* position)
{
    return {};
}
Ark_PathShape CommandsImpl(Ark_PathShape peer,
                           const Ark_String* commands)
{
    return {};
}
} // PathShapeAccessor
const GENERATED_ArkUIPathShapeAccessor* GetPathShapeAccessor()
{
    static const GENERATED_ArkUIPathShapeAccessor PathShapeAccessorImpl {
        PathShapeAccessor::DestroyPeerImpl,
        PathShapeAccessor::CtorImpl,
        PathShapeAccessor::GetFinalizerImpl,
        PathShapeAccessor::OffsetImpl,
        PathShapeAccessor::FillImpl,
        PathShapeAccessor::PositionImpl,
        PathShapeAccessor::CommandsImpl,
    };
    return &PathShapeAccessorImpl;
}

}
