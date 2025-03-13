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
#include "arkoala_api_generated.h"
#include "core/interfaces/native/implementation/i_curve_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ICurveAccessor {
void DestroyPeerImpl(Ark_ICurve peer)
{
    delete peer;
}
Ark_ICurve CtorImpl()
{
    return new ICurvePeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number InterpolateImpl(Ark_ICurve peer,
                           const Ark_Number* fraction)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer && peer->handler, errValue);
    CHECK_NULL_RETURN(fraction, errValue);
    float time = Converter::Convert<float>(*fraction);
    if (time > 1.0f) {
        time = 1.0f;
    }
    if (time < 0.0f) {
        time = 0.0f;
    }
    return Converter::ArkValue<Ark_Number>(peer->handler->Move(time));
}
} // ICurveAccessor
const GENERATED_ArkUIICurveAccessor* GetICurveAccessor()
{
    static const GENERATED_ArkUIICurveAccessor ICurveAccessorImpl {
        ICurveAccessor::DestroyPeerImpl,
        ICurveAccessor::CtorImpl,
        ICurveAccessor::GetFinalizerImpl,
        ICurveAccessor::InterpolateImpl,
    };
    return &ICurveAccessorImpl;
}

}
