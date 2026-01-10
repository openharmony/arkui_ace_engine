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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_BRIDGE_FLOWITEM_ARKTS_NATIVE_WATER_FLOW_ITEM_BRIDGE_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_BRIDGE_FLOWITEM_ARKTS_NATIVE_WATER_FLOW_ITEM_BRIDGE_H

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"

namespace OHOS::Ace::NG {
class WaterFlowItemBridge {
public:
    static void RegisterWaterFlowItemAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static ArkUINativeModuleValue CreateFlowItem(ArkUIRuntimeCallInfo* runtimeCallInfo);
};
} // namespace OHOS::Ace::NG

#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_BRIDGE_FLOWITEM_ARKTS_NATIVE_WATER_FLOW_ITEM_BRIDGE_H
