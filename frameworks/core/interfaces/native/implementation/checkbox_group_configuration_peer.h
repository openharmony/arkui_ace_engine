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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_CHECKBOX_GROUP_CONFIGURATION_PEER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_CHECKBOX_GROUP_CONFIGURATION_PEER_H

#include "base/memory/ace_type.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/components_ng/base/symbol_modifier.h"
#include "arkoala_api_generated.h"

struct CheckBoxGroupConfigurationPeer {
    bool enabled_ = false;
    std::string name_ = "";
    Ark_SelectStatus status_ = {};
    Ark_ContentModifier contentModifier_ = {};
    Ark_NativePointer node_ = {};
    Callback_Boolean_Void triggerChange_;
protected:
    CheckBoxGroupConfigurationPeer() {}
    ~CheckBoxGroupConfigurationPeer() {}
    friend OHOS::Ace::NG::PeerUtils;
};

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_CHECKBOX_GROUP_CONFIGURATION_PEER_H