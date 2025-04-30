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
namespace Matrix4TransitAccessor {
void DestroyPeerImpl(Ark_Matrix4Transit peer)
{
}
Ark_Matrix4Transit CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Matrix4Transit CopyImpl(Ark_Matrix4Transit peer)
{
    return {};
}
Ark_Matrix4Transit InvertImpl(Ark_Matrix4Transit peer)
{
    return {};
}
Ark_Matrix4Transit CombineImpl(Ark_Matrix4Transit peer,
                               Ark_Matrix4Transit options)
{
    return {};
}
Ark_Matrix4Transit TranslateImpl(Ark_Matrix4Transit peer,
                                 const Ark_TranslateOption* options)
{
    return {};
}
Ark_Matrix4Transit ScaleImpl(Ark_Matrix4Transit peer,
                             const Ark_ScaleOption* options)
{
    return {};
}
Ark_Matrix4Transit SkewImpl(Ark_Matrix4Transit peer,
                            const Ark_Number* x,
                            const Ark_Number* y)
{
    return {};
}
Ark_Matrix4Transit RotateImpl(Ark_Matrix4Transit peer,
                              const Ark_RotateOption* options)
{
    return {};
}
Ark_Tuple_Number_Number TransformPointImpl(Ark_Matrix4Transit peer,
                                           const Ark_Tuple_Number_Number* options)
{
    return {};
}
Ark_Matrix4Transit SetPolyToPolyImpl(Ark_Matrix4Transit peer,
                                     const Ark_PolyToPolyOptions* options)
{
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

struct Matrix4TransitPeer {
    virtual ~Matrix4TransitPeer() = default;
};
}
