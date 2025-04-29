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
#include "matrix2d_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace Matrix2DAccessor {
const auto ERROR_VALUE = Converter::ArkValue<Opt_Number>();

void DestroyPeerImpl(Ark_Matrix2D peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_Matrix2D CtorImpl()
{
    return PeerUtils::CreatePeer<Matrix2DPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Matrix2D IdentityImpl(Ark_Matrix2D peer)
{
    CHECK_NULL_RETURN(peer, {});
    peer->Identity();
    return peer;
}
Ark_Matrix2D InvertImpl(Ark_Matrix2D peer)
{
    CHECK_NULL_RETURN(peer, {});
    peer->Invert();
    return peer;
}
Ark_Matrix2D MultiplyImpl(Ark_Matrix2D peer,
                          const Opt_Matrix2D* other)
{
    LOGE("ARKOALA Matrix2DAccessor::MultiplyImpl is not implemented as deprecated.");
    return {};
}
Ark_Matrix2D Rotate0Impl(Ark_Matrix2D peer,
                         const Opt_Number* rx,
                         const Opt_Number* ry)
{
    LOGE("ARKOALA Matrix2DAccessor::Rotate0Impl is not implemented as deprecated.");
    return {};
}
Ark_Matrix2D Rotate1Impl(Ark_Matrix2D peer,
                         const Ark_Number* degree,
                         const Opt_Number* rx,
                         const Opt_Number* ry)
{
    CHECK_NULL_RETURN(peer, {});
    CHECK_NULL_RETURN(degree, {});
    CHECK_NULL_RETURN(rx, {});
    CHECK_NULL_RETURN(ry, {});
    auto angle = static_cast<double>(Converter::Convert<float>(*degree));
    auto optX = Converter::OptConvert<float>(*rx);
    auto optY = Converter::OptConvert<float>(*ry);
    peer->Rotate(angle, optX, optY);
    return peer;
}
Ark_Matrix2D TranslateImpl(Ark_Matrix2D peer,
                           const Opt_Number* tx,
                           const Opt_Number* ty)
{
    CHECK_NULL_RETURN(peer, {});
    CHECK_NULL_RETURN(tx, {});
    CHECK_NULL_RETURN(ty, {});
    auto optX = Converter::OptConvert<float>(*tx);
    auto optY = Converter::OptConvert<float>(*ty);
    peer->Translate(optX, optY);
    return peer;
}
Ark_Matrix2D ScaleImpl(Ark_Matrix2D peer,
                       const Opt_Number* sx,
                       const Opt_Number* sy)
{
    CHECK_NULL_RETURN(peer, {});
    CHECK_NULL_RETURN(sx, {});
    CHECK_NULL_RETURN(sy, {});
    auto optX = Converter::OptConvert<float>(*sx);
    auto optY = Converter::OptConvert<float>(*sy);
    peer->Scale(optX, optY);
    return peer;
}
Opt_Number GetScaleXImpl(Ark_Matrix2D peer)
{
    CHECK_NULL_RETURN(peer, ERROR_VALUE);
    return Converter::ArkValue<Opt_Number>(peer->GetScaleX());
}
void SetScaleXImpl(Ark_Matrix2D peer,
                   const Ark_Number* scaleX)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(scaleX);
    auto sx = static_cast<double>(Converter::Convert<float>(*scaleX));
    peer->SetScaleX(sx);
}
Opt_Number GetRotateYImpl(Ark_Matrix2D peer)
{
    CHECK_NULL_RETURN(peer, ERROR_VALUE);
    return Converter::ArkValue<Opt_Number>(peer->GetRotateY());
}
void SetRotateYImpl(Ark_Matrix2D peer,
                    const Ark_Number* rotateY)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(rotateY);
    auto ry = static_cast<double>(Converter::Convert<float>(*rotateY));
    peer->SetRotateY(ry);
}
Opt_Number GetRotateXImpl(Ark_Matrix2D peer)
{
    CHECK_NULL_RETURN(peer, ERROR_VALUE);
    return Converter::ArkValue<Opt_Number>(peer->GetRotateX());
}
void SetRotateXImpl(Ark_Matrix2D peer,
                    const Ark_Number* rotateX)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(rotateX);
    auto rx = static_cast<double>(Converter::Convert<float>(*rotateX));
    peer->SetRotateX(rx);
}
Opt_Number GetScaleYImpl(Ark_Matrix2D peer)
{
    CHECK_NULL_RETURN(peer, ERROR_VALUE);
    return Converter::ArkValue<Opt_Number>(peer->GetScaleX());
}
void SetScaleYImpl(Ark_Matrix2D peer,
                   const Ark_Number* scaleY)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(scaleY);
    auto sy = static_cast<double>(Converter::Convert<float>(*scaleY));
    peer->SetScaleY(sy);
}
Opt_Number GetTranslateXImpl(Ark_Matrix2D peer)
{
    CHECK_NULL_RETURN(peer, ERROR_VALUE);
    return Converter::ArkValue<Opt_Number>(peer->GetTranslateX());
}
void SetTranslateXImpl(Ark_Matrix2D peer,
                       const Ark_Number* translateX)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(translateX);
    auto tx = static_cast<double>(Converter::Convert<float>(*translateX));
    peer->SetTranslateX(tx);
}
Opt_Number GetTranslateYImpl(Ark_Matrix2D peer)
{
    CHECK_NULL_RETURN(peer, ERROR_VALUE);
    return Converter::ArkValue<Opt_Number>(peer->GetTranslateY());
}
void SetTranslateYImpl(Ark_Matrix2D peer,
                       const Ark_Number* translateY)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(translateY);
    auto ty = static_cast<double>(Converter::Convert<float>(*translateY));
    peer->SetTranslateY(ty);
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
