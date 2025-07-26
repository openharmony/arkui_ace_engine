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

struct PixelMapMockPeer {};

namespace OHOS::Ace::NG::GeneratedModifier {
namespace PixelMapMockAccessor {
void DestroyPeerImpl(Ark_PixelMapMock peer)
{
    delete peer;
}
Ark_PixelMapMock CtorImpl()
{
    return new PixelMapMockPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void ReleaseImpl(Ark_PixelMapMock peer)
{
    // do nothing
}
} // PixelMapMockAccessor
const GENERATED_ArkUIPixelMapMockAccessor* GetPixelMapMockAccessor()
{
    static const GENERATED_ArkUIPixelMapMockAccessor PixelMapMockAccessorImpl {
        PixelMapMockAccessor::DestroyPeerImpl,
        PixelMapMockAccessor::CtorImpl,
        PixelMapMockAccessor::GetFinalizerImpl,
        PixelMapMockAccessor::ReleaseImpl,
    };
    return &PixelMapMockAccessorImpl;
}

}
