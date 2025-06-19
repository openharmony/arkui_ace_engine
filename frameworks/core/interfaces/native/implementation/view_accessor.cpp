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

struct ViewPeer {};

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ViewAccessor {
void DestroyPeerImpl(Ark_View peer)
{
}
Ark_View CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_CustomObject CreateImpl(Ark_View peer,
                            const Ark_CustomObject* value)
{
    return {};
}
} // ViewAccessor
const GENERATED_ArkUIViewAccessor* GetViewAccessor()
{
    static const GENERATED_ArkUIViewAccessor ViewAccessorImpl {
        ViewAccessor::DestroyPeerImpl,
        ViewAccessor::CtorImpl,
        ViewAccessor::GetFinalizerImpl,
        ViewAccessor::CreateImpl,
    };
    return &ViewAccessorImpl;
}

struct ViewPeer {
    virtual ~ViewPeer() = default;
};
}
