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
namespace LayoutableAccessor {
void DestroyPeerImpl(Ark_Layoutable peer)
{
}
Ark_Layoutable ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void LayoutImpl(Ark_Layoutable peer,
                const Ark_Position* position)
{
}
Ark_DirectionalEdgesT GetMarginImpl(Ark_Layoutable peer)
{
    return {};
}
Ark_DirectionalEdgesT GetPaddingImpl(Ark_Layoutable peer)
{
    return {};
}
Ark_DirectionalEdgesT GetBorderWidthImpl(Ark_Layoutable peer)
{
    return {};
}
Ark_MeasureResult GetMeasureResultImpl(Ark_Layoutable peer)
{
    return {};
}
void SetMeasureResultImpl(Ark_Layoutable peer,
                          const Ark_MeasureResult* measureResult)
{
}
Opt_Number GetUniqueIdImpl(Ark_Layoutable peer)
{
    return {};
}
void SetUniqueIdImpl(Ark_Layoutable peer,
                     const Opt_Number* uniqueId)
{
}
} // LayoutableAccessor
const GENERATED_ArkUILayoutableAccessor* GetLayoutableAccessor()
{
    static const GENERATED_ArkUILayoutableAccessor LayoutableAccessorImpl {
        LayoutableAccessor::DestroyPeerImpl,
        LayoutableAccessor::ConstructImpl,
        LayoutableAccessor::GetFinalizerImpl,
        LayoutableAccessor::LayoutImpl,
        LayoutableAccessor::GetMarginImpl,
        LayoutableAccessor::GetPaddingImpl,
        LayoutableAccessor::GetBorderWidthImpl,
        LayoutableAccessor::GetMeasureResultImpl,
        LayoutableAccessor::SetMeasureResultImpl,
        LayoutableAccessor::GetUniqueIdImpl,
        LayoutableAccessor::SetUniqueIdImpl,
    };
    return &LayoutableAccessorImpl;
}

}
