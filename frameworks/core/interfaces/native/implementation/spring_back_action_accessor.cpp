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

#include "arkoala_api_generated.h"
#include "spring_back_action_peer.h"

#include "core/components_ng/base/view_abstract_model_static.h"
#include "core/interfaces/native/utility/converter.h"

SpringBackActionPeer g_springBackPeer = {};

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SpringBackActionAccessor {
void DestroyPeerImpl(Ark_SpringBackAction peer)
{
}
Ark_SpringBackAction ConstructImpl()
{
    return &g_springBackPeer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SpringBackImpl(Ark_SpringBackAction peer)
{
    ViewAbstractModelStatic::SheetSpringBackStatic();
}
} // SpringBackActionAccessor
const GENERATED_ArkUISpringBackActionAccessor* GetSpringBackActionAccessor()
{
    static const GENERATED_ArkUISpringBackActionAccessor SpringBackActionAccessorImpl {
        SpringBackActionAccessor::DestroyPeerImpl,
        SpringBackActionAccessor::ConstructImpl,
        SpringBackActionAccessor::GetFinalizerImpl,
        SpringBackActionAccessor::SpringBackImpl,
    };
    return &SpringBackActionAccessorImpl;
}

}
