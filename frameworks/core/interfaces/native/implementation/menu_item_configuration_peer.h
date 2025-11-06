/*
* Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_MENU_ITEM_CONFIGURATION_PEER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_MENU_ITEM_CONFIGURATION_PEER_H

#include "base/memory/ace_type.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "arkoala_api_generated.h"

struct MenuItemConfigurationPeer {
    Ark_Boolean enabled;
    Ark_ContentModifier contentModifier;
    Ark_ResourceStr value;
    Opt_ResourceStr icon;
    Opt_SymbolGlyphModifier symbolIcon;
    Ark_Boolean selected;
    Ark_Int32 index;
    Ark_NativePointer node;
protected:
    MenuItemConfigurationPeer() {}
    ~MenuItemConfigurationPeer() {}
    friend OHOS::Ace::NG::PeerUtils;
};

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_MENU_ITEM_CONFIGURATION_PEER_H