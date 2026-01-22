/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_BRIDGE_MENU_ITEM_GROUP_ARKTS_NATIVE_MENU_ITEM_GROUP_BRIDGE_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_BRIDGE_MENU_ITEM_GROUP_ARKTS_NATIVE_MENU_ITEM_GROUP_BRIDGE_H

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"

namespace OHOS::Ace::NG {
class MenuItemGroupBridge {
public:
    static ArkUINativeModuleValue CreateMenuItemGroup(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetMenuItemGroupHeader(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetMenuItemGroupFooter(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static void RegisterMenuItemGroupAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
};
} // namespace OHOS::Ace::NG

#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_BRIDGE_MENU_ITEM_GROUP_ARKTS_NATIVE_MENU_ITEM_GROUP_BRIDGE_H