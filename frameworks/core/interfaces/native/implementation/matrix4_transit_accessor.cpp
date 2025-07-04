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
namespace matrix4_Matrix4TransitAccessor {
void DestroyPeerImpl(Ark_matrix4_Matrix4Transit peer)
{
}
Ark_matrix4_Matrix4Transit ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_matrix4_Matrix4Transit CopyImpl(Ark_matrix4_Matrix4Transit peer)
{
    return {};
}
Ark_matrix4_Matrix4Transit InvertImpl(Ark_matrix4_Matrix4Transit peer)
{
    return {};
}
Ark_matrix4_Matrix4Transit CombineImpl(Ark_matrix4_Matrix4Transit peer,
                                       Ark_matrix4_Matrix4Transit options)
{
    return {};
}
Ark_matrix4_Matrix4Transit TranslateImpl(Ark_matrix4_Matrix4Transit peer,
                                         const Ark_TranslateOptions* options)
{
    return {};
}
Ark_matrix4_Matrix4Transit ScaleImpl(Ark_matrix4_Matrix4Transit peer,
                                     const Ark_ScaleOptions* options)
{
    return {};
}
Ark_matrix4_Matrix4Transit SkewImpl(Ark_matrix4_Matrix4Transit peer,
                                    const Ark_Number* x,
                                    const Ark_Number* y)
{
    return {};
}
Ark_matrix4_Matrix4Transit RotateImpl(Ark_matrix4_Matrix4Transit peer,
                                      const Ark_RotateOptions* options)
{
    return {};
}
Ark_matrix4_Matrix4TransformPoint TransformPointImpl(Ark_matrix4_Matrix4Transit peer,
                                                     const Ark_matrix4_Matrix4TransformPoint* options)
{
    return {};
}
Ark_matrix4_Matrix4Transit SetPolyToPolyImpl(Ark_matrix4_Matrix4Transit peer,
                                             const Ark_matrix4_PolyToPolyOptions* options)
{
    return {};
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
