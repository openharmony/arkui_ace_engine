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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "pan_recognizer_peer.h"
#include "pan_gesture_options_peer.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
using namespace OHOS::Ace::NG::Converter;
namespace PanRecognizerAccessor {
void DestroyPeerImpl(Ark_PanRecognizer peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_PanRecognizer ConstructImpl()
{
    return PeerUtils::CreatePeer<PanRecognizerPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_PanGestureOptions GetPanGestureOptionsImpl(Ark_PanRecognizer peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    auto options = peer->GetPanGestureOptions();
    CHECK_NULL_RETURN(options, nullptr);
    auto panGestureOptionsPeer = PeerUtils::CreatePeer<PanGestureOptionsPeer>();
    panGestureOptionsPeer->handler = options;
    return reinterpret_cast<Ark_PanGestureOptions>(panGestureOptionsPeer);
}
Ark_PanDirection GetDirectionImpl(Ark_PanRecognizer peer)
{
    CHECK_NULL_RETURN(peer, INVALID_ENUM_VAL<Ark_PanDirection>);
    auto direction = peer->GetDirection();
    return ArkValue<Ark_PanDirection>(direction, FC);
}

Ark_Float64 GetDistanceImpl(Ark_PanRecognizer peer)
{
    const auto errValue = ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto distance = peer->GetPanDistance();
    auto context = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(context, errValue);
    auto distance_new = context->ConvertPxToVp(Dimension(distance, DimensionUnit::PX));
    return ArkValue<Ark_Float64>(distance_new);
}
Map_SourceTool_F64 GetDistanceMapImpl(Ark_PanRecognizer peer)
{
    Map_SourceTool_Float64 result = {0, nullptr, nullptr};
    CHECK_NULL_RETURN(peer, result);

    auto recognizer = peer->GetRecognizer().Upgrade();
    CHECK_NULL_RETURN(recognizer, result);
    auto panRecognizer = AceType::DynamicCast<NG::PanRecognizer>(recognizer);
    CHECK_NULL_RETURN(panRecognizer, result);
    auto distanceMap = panRecognizer->GetDistanceMap();
    if (distanceMap.empty()) {
        return result;
    }
    auto context = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(context, result);
    result.size = static_cast<Ark_Int32>(distanceMap.size());
    result.keys = new Ark_SourceTool[result.size];
    result.values = new Ark_Float64[result.size];
    size_t index = 0;
    for (const auto& pair : distanceMap) {
        result.keys[index] = ArkValue<Ark_SourceTool>(pair.first);
        double distanceVp = context->ConvertPxToVp(pair.second);
        result.values[index] = ArkValue<Ark_Float64>(distanceVp);
        index++;
    }
    return result;
}
} // PanRecognizerAccessor
const GENERATED_ArkUIPanRecognizerAccessor* GetPanRecognizerAccessor()
{
    static const GENERATED_ArkUIPanRecognizerAccessor PanRecognizerAccessorImpl {
        PanRecognizerAccessor::DestroyPeerImpl,
        PanRecognizerAccessor::ConstructImpl,
        PanRecognizerAccessor::GetFinalizerImpl,
        PanRecognizerAccessor::GetPanGestureOptionsImpl,
        PanRecognizerAccessor::GetDirectionImpl,
        PanRecognizerAccessor::GetDistanceImpl,
        PanRecognizerAccessor::GetDistanceMapImpl,
    };
    return &PanRecognizerAccessorImpl;
}

}
