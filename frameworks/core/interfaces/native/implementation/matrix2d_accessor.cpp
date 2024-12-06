/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "matrix2d_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace Matrix2DAccessor {
void DestroyPeerImpl(Matrix2DPeer* peer)
{
    if (peer) {
        delete peer;
    }
}
Matrix2DPeer* CtorImpl()
{
    return new Matrix2DPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_NativePointer IdentityImpl(Matrix2DPeer* peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    Matrix2D::Identity(peer->transform);
    LOGE("ARKOALA Matrix2DAccessor::IdentityImpl return type Ark_NativePointer "
        "should be replaced with a Matrix2DPeer pointer type.");
    return reinterpret_cast<Ark_NativePointer>(peer);
}
Ark_NativePointer InvertImpl(Matrix2DPeer* peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    bool retValue = NG::Matrix2D::Invert(peer->transform);
    if (!retValue) {
        peer->transform.scaleX = NAN;
        peer->transform.scaleY = NAN;
        peer->transform.skewX = NAN;
        peer->transform.skewY = NAN;
        peer->transform.translateX = NAN;
        peer->transform.translateY = NAN;
    }
    return reinterpret_cast<Ark_NativePointer>(peer);
}
Ark_NativePointer MultiplyImpl(Matrix2DPeer* peer,
                               const Opt_Matrix2D* other)
{
    LOGE("ARKOALA Matrix2DAccessor::MultiplyImpl is not implemented as deprecated.");
    return 0;
}
Ark_NativePointer Rotate0Impl(Matrix2DPeer* peer,
                              const Opt_Number* rx,
                              const Opt_Number* ry)
{
    LOGE("ARKOALA Matrix2DAccessor::Rotate0Impl is not implemented as deprecated.");
    return 0;
}
Ark_NativePointer Rotate1Impl(Matrix2DPeer* peer,
                              const Ark_Number* degree,
                              const Opt_Number* rx,
                              const Opt_Number* ry)
{
    LOGE("ARKOALA Matrix2DAccessor::Rotate1Impl is not implemented as deprecated.");
    return 0;
}
Ark_NativePointer TranslateImpl(Matrix2DPeer* peer,
                                const Opt_Number* tx,
                                const Opt_Number* ty)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(tx, nullptr);
    CHECK_NULL_RETURN(ty, nullptr);
    auto optX = Converter::OptConvert<float>(*tx);
    auto optY = Converter::OptConvert<float>(*ty);
    double transX = static_cast<double>(optX.has_value() ? *optX : 0);
    double transY = static_cast<double>(optY.has_value() ? *optY : 0);
    double density = peer->GetDensity();
    transX *= density;
    transY *= density;
    NG::Matrix2D::Translate(peer->transform, transX, transY);
    LOGE("ARKOALA Matrix2DAccessor::TranslateImpl return type Ark_NativePointer "
        "should be replaced with a Matrix2DPeer pointer type.");
    return reinterpret_cast<Ark_NativePointer>(peer);
}
Ark_NativePointer ScaleImpl(Matrix2DPeer* peer,
                            const Opt_Number* sx,
                            const Opt_Number* sy)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(sx, nullptr);
    CHECK_NULL_RETURN(sy, nullptr);
    auto optX = Converter::OptConvert<float>(*sx);
    auto optY = Converter::OptConvert<float>(*sy);
    double scaleX = static_cast<double>(optX.has_value() ? *optX : 1);
    double scaleY = static_cast<double>(optY.has_value() ? *optY : 1);
    NG::Matrix2D::Scale(peer->transform, scaleX, scaleY);
    LOGE("ARKOALA Matrix2DAccessor::ScaleImpl return type Ark_NativePointer "
        "should be replaced with a Matrix2DPeer type.");
    return reinterpret_cast<Ark_NativePointer>(peer);
}
Ark_Int32 GetScaleXImpl(Matrix2DPeer* peer)
{
    CHECK_NULL_RETURN(peer, 0);
    LOGE("ARKOALA Matrix2DAccessor::GetScaleXImpl return type Ark_Int32 "
        "should be replaced with a Ark_Number type.");
    return Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(peer->transform.scaleX));
}
void SetScaleXImpl(Matrix2DPeer* peer,
                   const Ark_Number* scaleX)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(scaleX);
    auto opt = Converter::OptConvert<float>(*scaleX);
    CHECK_NULL_VOID(opt);
    peer->transform.scaleX = static_cast<double>(*opt);
}
Ark_Int32 GetRotateYImpl(Matrix2DPeer* peer)
{
    CHECK_NULL_RETURN(peer, 0);
    LOGE("ARKOALA Matrix2DAccessor::GetRotateYImpl return type Ark_Int32 "
        "should be replaced with a Ark_Number type.");
    return Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(peer->transform.skewY));
}
void SetRotateYImpl(Matrix2DPeer* peer,
                    const Ark_Number* rotateY)
{
}
Ark_Int32 GetRotateXImpl(Matrix2DPeer* peer)
{
    CHECK_NULL_RETURN(peer, 0);
    LOGE("ARKOALA Matrix2DAccessor::GetRotateXImpl return type Ark_Int32 "
        "should be replaced with a Ark_Number type.");
    return Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(peer->transform.skewX));
}
void SetRotateXImpl(Matrix2DPeer* peer,
                    const Ark_Number* rotateX)
{
}
Ark_Int32 GetScaleYImpl(Matrix2DPeer* peer)
{
    CHECK_NULL_RETURN(peer, 0);
    LOGE("ARKOALA Matrix2DAccessor::GetScaleYImpl return type Ark_Int32 "
        "should be replaced with a Ark_Number type.");
    return Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(peer->transform.scaleY));
}
void SetScaleYImpl(Matrix2DPeer* peer,
                   const Ark_Number* scaleY)
{
}
Ark_Int32 GetTranslateXImpl(Matrix2DPeer* peer)
{
    CHECK_NULL_RETURN(peer, 0);
    LOGE("ARKOALA Matrix2DAccessor::GetTranslateXImpl return type Ark_Int32 "
        "should be replaced with a Ark_Number type.");
    return Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(peer->transform.translateX));
}
void SetTranslateXImpl(Matrix2DPeer* peer,
                       const Ark_Number* translateX)
{
}
Ark_Int32 GetTranslateYImpl(Matrix2DPeer* peer)
{
    CHECK_NULL_RETURN(peer, 0);
    LOGE("ARKOALA Matrix2DAccessor::GetTranslateYImpl return type Ark_Int32 "
        "should be replaced with a Ark_Number type.");
    return Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(peer->transform.translateY));
}
void SetTranslateYImpl(Matrix2DPeer* peer,
                       const Ark_Number* translateY)
{
}
} // Matrix2DAccessor
const GENERATED_ArkUIMatrix2DAccessor* GetMatrix2DAccessor()
{
    static const GENERATED_ArkUIMatrix2DAccessor Matrix2DAccessorImpl {
        Matrix2DAccessor::DestroyPeerImpl,
        Matrix2DAccessor::CtorImpl,
        Matrix2DAccessor::GetFinalizerImpl,
        Matrix2DAccessor::IdentityImpl,
        Matrix2DAccessor::InvertImpl,
        Matrix2DAccessor::MultiplyImpl,
        Matrix2DAccessor::Rotate0Impl,
        Matrix2DAccessor::Rotate1Impl,
        Matrix2DAccessor::TranslateImpl,
        Matrix2DAccessor::ScaleImpl,
        Matrix2DAccessor::GetScaleXImpl,
        Matrix2DAccessor::SetScaleXImpl,
        Matrix2DAccessor::GetRotateYImpl,
        Matrix2DAccessor::SetRotateYImpl,
        Matrix2DAccessor::GetRotateXImpl,
        Matrix2DAccessor::SetRotateXImpl,
        Matrix2DAccessor::GetScaleYImpl,
        Matrix2DAccessor::SetScaleYImpl,
        Matrix2DAccessor::GetTranslateXImpl,
        Matrix2DAccessor::SetTranslateXImpl,
        Matrix2DAccessor::GetTranslateYImpl,
        Matrix2DAccessor::SetTranslateYImpl,
    };
    return &Matrix2DAccessorImpl;
}

}
