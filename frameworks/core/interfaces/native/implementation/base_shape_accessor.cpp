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
namespace BaseShapeAccessor {
void DestroyPeerImpl(Ark_BaseShape peer)
{
}
Ark_BaseShape CtorImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_BaseShape WidthImpl(Ark_BaseShape peer,
                        const Ark_Length* width)
{
    return {};
}
Ark_BaseShape HeightImpl(Ark_BaseShape peer,
                         const Ark_Length* height)
{
    return {};
}
Ark_BaseShape SizeImpl(Ark_BaseShape peer,
                       const Ark_SizeOptions* size)
{
    return {};
}
} // BaseShapeAccessor
const GENERATED_ArkUIBaseShapeAccessor* GetBaseShapeAccessor()
{
    static const GENERATED_ArkUIBaseShapeAccessor BaseShapeAccessorImpl {
        BaseShapeAccessor::DestroyPeerImpl,
        BaseShapeAccessor::CtorImpl,
        BaseShapeAccessor::GetFinalizerImpl,
        BaseShapeAccessor::WidthImpl,
        BaseShapeAccessor::HeightImpl,
        BaseShapeAccessor::SizeImpl,
    };
    return &BaseShapeAccessorImpl;
}

}
