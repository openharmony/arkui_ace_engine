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
namespace ChildrenMainSizeAccessor {
void DestroyPeerImpl(Ark_ChildrenMainSize peer)
{
}
Ark_ChildrenMainSize CtorImpl(const Ark_Number* childDefaultSize)
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SpliceImpl(Ark_VMContext vmContext,
                Ark_ChildrenMainSize peer,
                const Ark_Number* start,
                const Opt_Number* deleteCount,
                const Opt_Array_Number* childrenSize)
{
}
void UpdateImpl(Ark_VMContext vmContext,
                Ark_ChildrenMainSize peer,
                const Ark_Number* index,
                const Ark_Number* childSize)
{
}
Ark_Number GetChildDefaultSizeImpl(Ark_ChildrenMainSize peer)
{
    return {};
}
void SetChildDefaultSizeImpl(Ark_ChildrenMainSize peer,
                             const Ark_Number* childDefaultSize)
{
}
} // ChildrenMainSizeAccessor
const GENERATED_ArkUIChildrenMainSizeAccessor* GetChildrenMainSizeAccessor()
{
    static const GENERATED_ArkUIChildrenMainSizeAccessor ChildrenMainSizeAccessorImpl {
        ChildrenMainSizeAccessor::DestroyPeerImpl,
        ChildrenMainSizeAccessor::CtorImpl,
        ChildrenMainSizeAccessor::GetFinalizerImpl,
        ChildrenMainSizeAccessor::SpliceImpl,
        ChildrenMainSizeAccessor::UpdateImpl,
        ChildrenMainSizeAccessor::GetChildDefaultSizeImpl,
        ChildrenMainSizeAccessor::SetChildDefaultSizeImpl,
    };
    return &ChildrenMainSizeAccessorImpl;
}

}
