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

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace Matrix2DModifier {
Ark_NativePointer CtorImpl()
{
    return 0;
}
Ark_NativePointer GetFinalizerImpl()
{
    return 0;
}
Ark_NativePointer IdentityImpl(Matrix2DPeer* peer)
{
    return 0;
}
Ark_NativePointer InvertImpl(Matrix2DPeer* peer)
{
    return 0;
}
Ark_NativePointer MultiplyImpl(Matrix2DPeer* peer, const Opt_Matrix2D* other)
{
    return 0;
}
Ark_NativePointer Rotate0Impl(Matrix2DPeer* peer, const Opt_Number* rx, const Opt_Number* ry)
{
    return 0;
}
Ark_NativePointer Rotate1Impl(Matrix2DPeer* peer, const Ark_Number* degree, const Opt_Number* rx, const Opt_Number* ry)
{
    return 0;
}
Ark_NativePointer TranslateImpl(Matrix2DPeer* peer, const Opt_Number* tx, const Opt_Number* ty)
{
    return 0;
}
Ark_NativePointer ScaleImpl(Matrix2DPeer* peer, const Opt_Number* sx, const Opt_Number* sy)
{
    return 0;
}
Ark_Int32 GetScaleXImpl(Matrix2DPeer* peer)
{
    return 0;
}
void SetScaleXImpl(Matrix2DPeer* peer, const Ark_Number* scaleX)
{
}
Ark_Int32 GetRotateYImpl(Matrix2DPeer* peer)
{
    return 0;
}
void SetRotateYImpl(Matrix2DPeer* peer, const Ark_Number* rotateY)
{
}
Ark_Int32 GetRotateXImpl(Matrix2DPeer* peer)
{
    return 0;
}
void SetRotateXImpl(Matrix2DPeer* peer, const Ark_Number* rotateX)
{
}
Ark_Int32 GetScaleYImpl(Matrix2DPeer* peer)
{
    return 0;
}
void SetScaleYImpl(Matrix2DPeer* peer, const Ark_Number* scaleY)
{
}
Ark_Int32 GetTranslateXImpl(Matrix2DPeer* peer)
{
    return 0;
}
void SetTranslateXImpl(Matrix2DPeer* peer, const Ark_Number* translateX)
{
}
Ark_Int32 GetTranslateYImpl(Matrix2DPeer* peer)
{
    return 0;
}
void SetTranslateYImpl(Matrix2DPeer* peer, const Ark_Number* translateY)
{
}
} // Matrix2DModifier
const GENERATED_ArkUIMatrix2DAccessor* GetMatrix2DAccessor()
{
    static const GENERATED_ArkUIMatrix2DAccessor Matrix2DAccessorImpl {
        Matrix2DModifier::CtorImpl,
        Matrix2DModifier::GetFinalizerImpl,
        Matrix2DModifier::IdentityImpl,
        Matrix2DModifier::InvertImpl,
        Matrix2DModifier::MultiplyImpl,
        Matrix2DModifier::Rotate0Impl,
        Matrix2DModifier::Rotate1Impl,
        Matrix2DModifier::TranslateImpl,
        Matrix2DModifier::ScaleImpl,
        Matrix2DModifier::GetScaleXImpl,
        Matrix2DModifier::SetScaleXImpl,
        Matrix2DModifier::GetRotateYImpl,
        Matrix2DModifier::SetRotateYImpl,
        Matrix2DModifier::GetRotateXImpl,
        Matrix2DModifier::SetRotateXImpl,
        Matrix2DModifier::GetScaleYImpl,
        Matrix2DModifier::SetScaleYImpl,
        Matrix2DModifier::GetTranslateXImpl,
        Matrix2DModifier::SetTranslateXImpl,
        Matrix2DModifier::GetTranslateYImpl,
        Matrix2DModifier::SetTranslateYImpl,
    };
    return &Matrix2DAccessorImpl;
}

}
