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
#include "core/components_ng/render/adapter/matrix2d.h"
#include "core/interfaces/native/implementation/matrix4_transit_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "frameworks/core/components_ng/render/adapter/matrix_util.h"

namespace OHOS::Ace {
void AssignArkValue(Ark_matrix4_Matrix4TransformPoint& dst, const Point& src)
{
    dst.value0 = NG::Converter::ArkValue<Ark_Number>(src.GetX());
    dst.value1 = NG::Converter::ArkValue<Ark_Number>(src.GetY());
}
namespace NG::Converter {
template<>
Point Convert(const Ark_matrix4_Matrix4TransformPoint& src)
{
    auto x = Converter::Convert<double>(src.value0);
    auto y = Converter::Convert<double>(src.value1);
    return Point(x, y);
}
} // namespace NG::Converter
} // namespace OHOS::Ace

namespace OHOS::Ace::NG::GeneratedModifier {
namespace matrix4_Matrix4TransitAccessor {
void DestroyPeerImpl(Ark_matrix4_Matrix4Transit peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_matrix4_Matrix4Transit ConstructImpl()
{
    return PeerUtils::CreatePeer<matrix4_Matrix4TransitPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_matrix4_Matrix4Transit CopyImpl(Ark_matrix4_Matrix4Transit peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    auto result = PeerUtils::CreatePeer<matrix4_Matrix4TransitPeer>();
    result->matrix = peer->matrix;
    return result;
}
Ark_matrix4_Matrix4Transit InvertImpl(Ark_matrix4_Matrix4Transit peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    peer->matrix = Matrix4::Invert(peer->matrix);
    return peer;
}
Ark_matrix4_Matrix4Transit CombineImpl(Ark_matrix4_Matrix4Transit peer,
                                       Ark_matrix4_Matrix4Transit options)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(options, peer);
    peer->matrix = options->matrix * peer->matrix;
    return peer;
}
Ark_matrix4_Matrix4Transit TranslateImpl(Ark_matrix4_Matrix4Transit peer,
                                         const Ark_TranslateOptions* options)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(options, peer);
    auto x = Converter::ConvertOrDefault<double>(options->x, 0.0);
    auto y = Converter::ConvertOrDefault<double>(options->y, 0.0);
    auto z = Converter::ConvertOrDefault<double>(options->z, 0.0);
    peer->matrix = Matrix4::CreateTranslate(x, y, z) * peer->matrix;
    return peer;
}
Ark_matrix4_Matrix4Transit ScaleImpl(Ark_matrix4_Matrix4Transit peer,
                                     const Ark_ScaleOptions* options)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(options, peer);
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

    peer->matrix = scaleMatrix * peer->matrix;
    return peer;
}
Ark_matrix4_Matrix4Transit SkewImpl(Ark_matrix4_Matrix4Transit peer,
                                    const Ark_Number* x,
                                    const Ark_Number* y)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(x && y, peer);
    auto convX = Converter::Convert<double>(*x);
    auto convY = Converter::Convert<double>(*y);

    peer->matrix = Matrix4::CreateFactorSkew(convX, convY) * peer->matrix;
    return peer;
}
Ark_matrix4_Matrix4Transit RotateImpl(Ark_matrix4_Matrix4Transit peer,
                                      const Ark_RotateOptions* options)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(options, peer);

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
    peer->matrix = rotateMatrix * peer->matrix;

    return peer;
}
Ark_matrix4_Matrix4TransformPoint TransformPointImpl(Ark_matrix4_Matrix4Transit peer,
                                                     const Ark_matrix4_Matrix4TransformPoint* options)
{
    CHECK_NULL_RETURN(peer && options, {});
    auto point = Converter::Convert<Point>(*options);
    Point target = peer->matrix * point;
    return Converter::ArkValue<Ark_matrix4_Matrix4TransformPoint>(target);
}
Ark_matrix4_Matrix4Transit SetPolyToPolyImpl(Ark_matrix4_Matrix4Transit peer,
                                             const Ark_matrix4_PolyToPolyOptions* options)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(options, peer);
    auto result = PeerUtils::CreatePeer<matrix4_Matrix4TransitPeer>();

    const auto srcPoint = Converter::Convert<std::vector<PointT<int32_t>>>(options->src);
    const auto dstPoint = Converter::Convert<std::vector<PointT<int32_t>>>(options->dst);
    const auto srcSize = static_cast<int32_t>(srcPoint.size());
    const auto dstSize = static_cast<int32_t>(dstPoint.size());
    const auto srcIndex = Converter::ConvertOrDefault<int32_t>(options->srcIndex, 0);
    const auto dstIndex = Converter::ConvertOrDefault<int32_t>(options->dstIndex, 0);
    const auto pointCount = Converter::ConvertOrDefault<int32_t>(options->pointCount, srcSize / 2);

    if (pointCount <= 0 || pointCount > srcSize || pointCount > dstSize) {
        LOGE("setpPolyToPoly pointCount out of range pointCount:%{public}d, src size:%{public}d, dst size:%{public}d",
            pointCount, srcSize, dstSize);
        return result;
    }
    if (srcIndex < 0 || (pointCount + srcIndex) > srcSize) {
        LOGE("setpPolyToPoly srcIndex out of range srcIndex:%{public}d, pointCount:%{public}d, src size%{public}d",
            srcIndex, pointCount, srcSize);
        return result;
    }
    if (dstIndex < 0 || (pointCount + dstIndex) > dstSize) {
        LOGE("setpPolyToPoly dstIndex out of range dstIndex:%{public}d, pointCount:%{public}d, dst size%{public}d",
            dstIndex, pointCount, dstSize);
        return result;
    }

    std::vector<PointT<int32_t>> totalPoint;
    int srcLastIndex = pointCount + srcIndex;
    for (int i = srcIndex; i < srcLastIndex; i++) {
        totalPoint.push_back(srcPoint[i]);
    }
    int dstLastIndex = pointCount + dstIndex;
    for (int i = dstIndex; i < dstLastIndex; i++) {
        totalPoint.push_back(dstPoint[i]);
    }
    result->matrix = OHOS::Ace::NG::MatrixUtil::SetMatrixPolyToPoly(peer->matrix, totalPoint);

    return result;
}
} // matrix4_Matrix4TransitAccessor
const GENERATED_ArkUIMatrix4_Matrix4TransitAccessor* GetMatrix4_Matrix4TransitAccessor()
{
    static const GENERATED_ArkUIMatrix4_Matrix4TransitAccessor Matrix4_Matrix4TransitAccessorImpl {
        matrix4_Matrix4TransitAccessor::DestroyPeerImpl,
        matrix4_Matrix4TransitAccessor::ConstructImpl,
        matrix4_Matrix4TransitAccessor::GetFinalizerImpl,
        matrix4_Matrix4TransitAccessor::CopyImpl,
        matrix4_Matrix4TransitAccessor::InvertImpl,
        matrix4_Matrix4TransitAccessor::CombineImpl,
        matrix4_Matrix4TransitAccessor::TranslateImpl,
        matrix4_Matrix4TransitAccessor::ScaleImpl,
        matrix4_Matrix4TransitAccessor::SkewImpl,
        matrix4_Matrix4TransitAccessor::RotateImpl,
        matrix4_Matrix4TransitAccessor::TransformPointImpl,
        matrix4_Matrix4TransitAccessor::SetPolyToPolyImpl,
    };
    return &Matrix4_Matrix4TransitAccessorImpl;
}

}
