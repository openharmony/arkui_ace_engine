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
#include "core/interfaces/native/implementation/matrix4_transit_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
namespace Converter {
template<>
Point Convert(const Ark_Tuple_Number_Number& src)
{
    auto x = Converter::Convert<double>(src.value0);
    auto y = Converter::Convert<double>(src.value1);
    return Point(x, y);
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace Matrix4TransitAccessor {
void DestroyPeerImpl(Ark_Matrix4Transit peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_Matrix4Transit CtorImpl()
{
    return PeerUtils::CreatePeer<Matrix4TransitPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Matrix4Transit CopyImpl(Ark_Matrix4Transit peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    auto result = PeerUtils::CreatePeer<Matrix4TransitPeer>();
    result->matrix = peer->matrix;
    return result;
}
Ark_Matrix4Transit InvertImpl(Ark_Matrix4Transit peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    auto result = PeerUtils::CreatePeer<Matrix4TransitPeer>();
    result->matrix = Matrix4::Invert(peer->matrix);
    return result;
}
Ark_Matrix4Transit CombineImpl(Ark_Matrix4Transit peer,
                               Ark_Matrix4Transit options)
{
    CHECK_NULL_RETURN(peer && options, nullptr);
    auto result = PeerUtils::CreatePeer<Matrix4TransitPeer>();
    result->matrix = options->matrix * peer->matrix;
    return result;
}
Ark_Matrix4Transit TranslateImpl(Ark_Matrix4Transit peer,
                                 const Ark_TranslateOption* options)
{
    CHECK_NULL_RETURN(peer && options, nullptr);
    auto result = PeerUtils::CreatePeer<Matrix4TransitPeer>();
    auto x = Converter::ConvertOrDefault<double>(options->x, 0.0);
    auto y = Converter::ConvertOrDefault<double>(options->y, 0.0);
    auto z = Converter::ConvertOrDefault<double>(options->z, 0.0);
    result->matrix = Matrix4::CreateTranslate(x, y, z) * peer->matrix;
    return result;
}
Ark_Matrix4Transit ScaleImpl(Ark_Matrix4Transit peer,
                             const Ark_ScaleOption* options)
{
    CHECK_NULL_RETURN(peer && options, nullptr);
    auto x = Converter::ConvertOrDefault<double>(options->x, 1.0);
    auto y = Converter::ConvertOrDefault<double>(options->y, 1.0);
    auto z = Converter::ConvertOrDefault<double>(options->z, 1.0);
    auto centerX = Converter::ConvertOrDefault<double>(options->centerX, 0.0);
    auto centerY = Converter::ConvertOrDefault<double>(options->centerY, 0.0);

    auto scaleMatrix = Matrix4::CreateScale(x, y, z);
    if (!NearZero(centerX) || !NearZero(centerY)) {
        auto translate1 = Matrix4::CreateTranslate(centerX, centerY, 0.0);
        auto translate2 = Matrix4::CreateTranslate(-centerX, -centerY, 0.0);
        scaleMatrix = scaleMatrix * translate2;
        scaleMatrix = translate1 * scaleMatrix;
    }

    auto result = PeerUtils::CreatePeer<Matrix4TransitPeer>();
    result->matrix = scaleMatrix * peer->matrix;
    return result;
}
Ark_Matrix4Transit SkewImpl(Ark_Matrix4Transit peer,
                            const Ark_Number* x,
                            const Ark_Number* y)
{
    CHECK_NULL_RETURN(peer && x && y, nullptr);
    auto convX = Converter::Convert<double>(*x);
    auto convY = Converter::Convert<double>(*y);

    auto result = PeerUtils::CreatePeer<Matrix4TransitPeer>();
    result->matrix = Matrix4::CreateFactorSkew(convX, convY) * peer->matrix;
    return result;
}
Ark_Matrix4Transit RotateImpl(Ark_Matrix4Transit peer,
                              const Ark_RotateOption* options)
{
    CHECK_NULL_RETURN(peer && options, nullptr);
    auto result = PeerUtils::CreatePeer<Matrix4TransitPeer>();

    auto x = Converter::ConvertOrDefault<double>(options->x, 0.0);
    auto y = Converter::ConvertOrDefault<double>(options->y, 0.0);
    auto z = Converter::ConvertOrDefault<double>(options->z, 0.0);
    auto centerX = Converter::ConvertOrDefault<double>(options->centerX, 0.0);
    auto centerY = Converter::ConvertOrDefault<double>(options->centerY, 0.0);
    auto angle = Converter::ConvertOrDefault<double>(options->angle, 0.0);

    auto rotateMatrix = Matrix4::CreateRotate(angle, x, y, z);
    if (!NearZero(centerX) || !NearZero(centerY)) {
        auto translate1 = Matrix4::CreateTranslate(centerX, centerY, 0.0);
        auto translate2 = Matrix4::CreateTranslate(-centerX, -centerY, 0.0);
        rotateMatrix = rotateMatrix * translate2;
        rotateMatrix = translate1 * rotateMatrix;
    }
    result->matrix = rotateMatrix * peer->matrix;

    return result;
}
Ark_Tuple_Number_Number TransformPointImpl(Ark_Matrix4Transit peer,
                                           const Ark_Tuple_Number_Number* options)
{
    CHECK_NULL_RETURN(peer && options, {});
    auto point = Converter::Convert<Point>(*options);
    Point target = peer->matrix * point;
    return Converter::ArkValue<Ark_Tuple_Number_Number>(target);
}
Ark_Matrix4Transit SetPolyToPolyImpl(Ark_Matrix4Transit peer,
                                     const Ark_PolyToPolyOptions* options)
{
    LOGE("Matrix4TransitAccessor.SetPolyToPolyImpl not implemented");
    return {};
}
} // Matrix4TransitAccessor
const GENERATED_ArkUIMatrix4TransitAccessor* GetMatrix4TransitAccessor()
{
    static const GENERATED_ArkUIMatrix4TransitAccessor Matrix4TransitAccessorImpl {
        Matrix4TransitAccessor::DestroyPeerImpl,
        Matrix4TransitAccessor::CtorImpl,
        Matrix4TransitAccessor::GetFinalizerImpl,
        Matrix4TransitAccessor::CopyImpl,
        Matrix4TransitAccessor::InvertImpl,
        Matrix4TransitAccessor::CombineImpl,
        Matrix4TransitAccessor::TranslateImpl,
        Matrix4TransitAccessor::ScaleImpl,
        Matrix4TransitAccessor::SkewImpl,
        Matrix4TransitAccessor::RotateImpl,
        Matrix4TransitAccessor::TransformPointImpl,
        Matrix4TransitAccessor::SetPolyToPolyImpl,
    };
    return &Matrix4TransitAccessorImpl;
}

}
