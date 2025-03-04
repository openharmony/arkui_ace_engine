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
namespace GlobalScope_ohos_fontAccessor {
void DestroyPeerImpl(Ark_GlobalScope_ohos_font peer)
{
}
Ark_GlobalScope_ohos_font CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void RegisterFontImpl(const Ark_FontOptions* options)
{
}
Array_String GetSystemFontListImpl()
{
    return {};
}
} // GlobalScope_ohos_fontAccessor
const GENERATED_ArkUIGlobalScope_ohos_fontAccessor* GetGlobalScope_ohos_fontAccessor()
{
    static const GENERATED_ArkUIGlobalScope_ohos_fontAccessor GlobalScope_ohos_fontAccessorImpl {
        GlobalScope_ohos_fontAccessor::DestroyPeerImpl,
        GlobalScope_ohos_fontAccessor::CtorImpl,
        GlobalScope_ohos_fontAccessor::GetFinalizerImpl,
        GlobalScope_ohos_fontAccessor::RegisterFontImpl,
        GlobalScope_ohos_fontAccessor::GetSystemFontListImpl,
    };
    return &GlobalScope_ohos_fontAccessorImpl;
}

}
