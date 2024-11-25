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
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace Matrix2DAccessor {
Matrix2DPeer* CtorImpl()
{
    return nullptr;
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
Ark_NativePointer MultiplyImpl(Matrix2DPeer* peer,
                               const Opt_Matrix2D* other)
{
    return 0;
}
Ark_NativePointer Rotate0Impl(Matrix2DPeer* peer,
                              const Opt_Number* rx,
                              const Opt_Number* ry)
{
    return 0;
}
Ark_NativePointer Rotate1Impl(Matrix2DPeer* peer,
                              const Ark_Number* degree,
                              const Opt_Number* rx,
                              const Opt_Number* ry)
{
    return 0;
}
Ark_NativePointer TranslateImpl(Matrix2DPeer* peer,
                                const Opt_Number* tx,
                                const Opt_Number* ty)
{
    return 0;
}
Ark_NativePointer ScaleImpl(Matrix2DPeer* peer,
                            const Opt_Number* sx,
                            const Opt_Number* sy)
{
    return 0;
}
Ark_Int32 GetScaleXImpl(Matrix2DPeer* peer)
{
    return 0;
}
void SetScaleXImpl(Matrix2DPeer* peer,
                   const Ark_Number* scaleX)
{
}
Ark_Int32 GetRotateYImpl(Matrix2DPeer* peer)
{
    return 0;
}
void SetRotateYImpl(Matrix2DPeer* peer,
                    const Ark_Number* rotateY)
{
}
Ark_Int32 GetRotateXImpl(Matrix2DPeer* peer)
{
    return 0;
}
void SetRotateXImpl(Matrix2DPeer* peer,
                    const Ark_Number* rotateX)
{
}
Ark_Int32 GetScaleYImpl(Matrix2DPeer* peer)
{
    return 0;
}
void SetScaleYImpl(Matrix2DPeer* peer,
                   const Ark_Number* scaleY)
{
}
Ark_Int32 GetTranslateXImpl(Matrix2DPeer* peer)
{
    return 0;
}
void SetTranslateXImpl(Matrix2DPeer* peer,
                       const Ark_Number* translateX)
{
}
Ark_Int32 GetTranslateYImpl(Matrix2DPeer* peer)
{
    return 0;
}
void SetTranslateYImpl(Matrix2DPeer* peer,
                       const Ark_Number* translateY)
{
}
} // Matrix2DAccessor
const GENERATED_ArkUIMatrix2DAccessor* GetMatrix2DAccessor()
{
    static const GENERATED_ArkUIMatrix2DAccessor Matrix2DAccessorImpl {
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
