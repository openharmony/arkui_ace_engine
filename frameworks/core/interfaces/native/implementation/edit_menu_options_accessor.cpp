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

struct EditMenuOptionsPeer {};

namespace OHOS::Ace::NG::GeneratedModifier {
namespace EditMenuOptionsAccessor {
void DestroyPeerImpl(Ark_EditMenuOptions peer)
{
}
Ark_EditMenuOptions CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Array_TextMenuItem OnCreateMenuImpl(Ark_EditMenuOptions peer,
                                    const Array_TextMenuItem* menuItems)
{
    return {};
}
Ark_Boolean OnMenuItemClickImpl(Ark_EditMenuOptions peer,
                                const Ark_TextMenuItem* menuItem,
                                const Ark_TextRange* range)
{
    return {};
}
} // EditMenuOptionsAccessor
const GENERATED_ArkUIEditMenuOptionsAccessor* GetEditMenuOptionsAccessor()
{
    static const GENERATED_ArkUIEditMenuOptionsAccessor EditMenuOptionsAccessorImpl {
        EditMenuOptionsAccessor::DestroyPeerImpl,
        EditMenuOptionsAccessor::CtorImpl,
        EditMenuOptionsAccessor::GetFinalizerImpl,
        EditMenuOptionsAccessor::OnCreateMenuImpl,
        EditMenuOptionsAccessor::OnMenuItemClickImpl,
    };
    return &EditMenuOptionsAccessorImpl;
}

struct EditMenuOptionsPeer {
    virtual ~EditMenuOptionsPeer() = default;
};
}
