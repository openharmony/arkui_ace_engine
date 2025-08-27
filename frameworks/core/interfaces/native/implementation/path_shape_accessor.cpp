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
#include "path_shape_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace PathShapeAccessor {
void DestroyPeerImpl(Ark_PathShape peer)
{
    delete peer;
}
Ark_PathShape CtorImpl(const Opt_PathShapeOptions* options)
{
    auto peer = new PathShapePeer();
    peer->shape = OHOS::Ace::AceType::MakeRefPtr<Path>();
    CHECK_NULL_RETURN(options, peer);
    auto optOptions = Converter::OptConvert<PathShapeOptions>(*options);
    CHECK_EQUAL_RETURN(optOptions.has_value(), false, peer);
    CHECK_EQUAL_RETURN(optOptions.value().commands.has_value(), false, peer);
    peer->shape->SetValue(optOptions.value().commands.value());
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_PathShape OffsetImpl(Ark_PathShape peer,
                         const Ark_Position* offset)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(peer->shape, peer);
    CHECK_NULL_RETURN(offset, peer);
    peer->shape->SetOffset(Converter::Convert<DimensionOffset>(*offset));
    return peer;
}
Ark_PathShape FillImpl(Ark_PathShape peer,
                       const Ark_ResourceColor* color)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(peer->shape, peer);
    CHECK_NULL_RETURN(color, peer);
    auto optColor = Converter::OptConvert<Color>(*color);
    CHECK_EQUAL_RETURN(optColor.has_value(), false, peer);
    peer->shape->SetColor(optColor.value());
    return peer;
}
Ark_PathShape PositionImpl(Ark_PathShape peer,
                           const Ark_Position* position)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(peer->shape, peer);
    CHECK_NULL_RETURN(position, peer);
    peer->shape->SetPosition(Converter::Convert<DimensionOffset>(*position));
    return peer;
}
Ark_PathShape CommandsImpl(Ark_PathShape peer,
                           const Ark_String* commands)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(peer->shape, peer);
    CHECK_NULL_RETURN(commands, peer);
    auto optOptions = Converter::OptConvert<std::string>(*commands);
    CHECK_EQUAL_RETURN(optOptions.has_value(), false, peer);
    peer->shape->SetValue(optOptions.value());
    return peer;
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
