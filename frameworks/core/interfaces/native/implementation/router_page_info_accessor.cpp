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
namespace uiObserver_RouterPageInfoAccessor {
void DestroyPeerImpl(Ark_uiObserver_RouterPageInfo peer)
{
}
Ark_uiObserver_RouterPageInfo ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number GetIndexImpl(Ark_uiObserver_RouterPageInfo peer)
{
    return {};
}
void SetIndexImpl(Ark_uiObserver_RouterPageInfo peer,
                  const Ark_Number* index)
{
}
Ark_String GetNameImpl(Ark_uiObserver_RouterPageInfo peer)
{
    return {};
}
void SetNameImpl(Ark_uiObserver_RouterPageInfo peer,
                 const Ark_String* name)
{
}
Ark_String GetPathImpl(Ark_uiObserver_RouterPageInfo peer)
{
    return {};
}
void SetPathImpl(Ark_uiObserver_RouterPageInfo peer,
                 const Ark_String* path)
{
}
Ark_uiObserver_RouterPageState GetStateImpl(Ark_uiObserver_RouterPageInfo peer)
{
    return {};
}
void SetStateImpl(Ark_uiObserver_RouterPageInfo peer,
                  Ark_uiObserver_RouterPageState state)
{
}
Ark_String GetPageIdImpl(Ark_uiObserver_RouterPageInfo peer)
{
    return {};
}
void SetPageIdImpl(Ark_uiObserver_RouterPageInfo peer,
                   const Ark_String* pageId)
{
}
} // uiObserver_RouterPageInfoAccessor
const GENERATED_ArkUIUiObserver_RouterPageInfoAccessor* GetUiObserver_RouterPageInfoAccessor()
{
    static const GENERATED_ArkUIUiObserver_RouterPageInfoAccessor UiObserver_RouterPageInfoAccessorImpl {
        uiObserver_RouterPageInfoAccessor::DestroyPeerImpl,
        uiObserver_RouterPageInfoAccessor::ConstructImpl,
        uiObserver_RouterPageInfoAccessor::GetFinalizerImpl,
        uiObserver_RouterPageInfoAccessor::GetIndexImpl,
        uiObserver_RouterPageInfoAccessor::SetIndexImpl,
        uiObserver_RouterPageInfoAccessor::GetNameImpl,
        uiObserver_RouterPageInfoAccessor::SetNameImpl,
        uiObserver_RouterPageInfoAccessor::GetPathImpl,
        uiObserver_RouterPageInfoAccessor::SetPathImpl,
        uiObserver_RouterPageInfoAccessor::GetStateImpl,
        uiObserver_RouterPageInfoAccessor::SetStateImpl,
        uiObserver_RouterPageInfoAccessor::GetPageIdImpl,
        uiObserver_RouterPageInfoAccessor::SetPageIdImpl,
    };
    return &UiObserver_RouterPageInfoAccessorImpl;
}

}
