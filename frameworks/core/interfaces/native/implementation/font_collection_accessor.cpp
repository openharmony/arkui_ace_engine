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
namespace text_FontCollectionAccessor {
void DestroyPeerImpl(Ark_text_FontCollection peer)
{
}
Ark_text_FontCollection ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_text_FontCollection GetGlobalInstanceImpl()
{
    return {};
}
void LoadFontSyncImpl(Ark_text_FontCollection peer,
                      const Ark_String* name,
                      const Ark_Union_String_Resource* path)
{
}
void LoadFontImpl(Ark_VMContext vmContext,
                  Ark_AsyncWorkerPtr asyncWorker,
                  Ark_text_FontCollection peer,
                  const Ark_String* name,
                  const Ark_Union_String_Resource* path,
                  const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
}
void ClearCachesImpl(Ark_text_FontCollection peer)
{
}
} // text_FontCollectionAccessor
const GENERATED_ArkUIText_FontCollectionAccessor* GetText_FontCollectionAccessor()
{
    static const GENERATED_ArkUIText_FontCollectionAccessor Text_FontCollectionAccessorImpl {
        text_FontCollectionAccessor::DestroyPeerImpl,
        text_FontCollectionAccessor::ConstructImpl,
        text_FontCollectionAccessor::GetFinalizerImpl,
        text_FontCollectionAccessor::GetGlobalInstanceImpl,
        text_FontCollectionAccessor::LoadFontSyncImpl,
        text_FontCollectionAccessor::LoadFontImpl,
        text_FontCollectionAccessor::ClearCachesImpl,
    };
    return &Text_FontCollectionAccessorImpl;
}

}
