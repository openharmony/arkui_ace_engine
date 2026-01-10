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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_WATER_FLOW_SECTIONS_BINDING_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_WATER_FLOW_SECTIONS_BINDING_H

#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_water_flow_sections.h"
#include "core/components_ng/pattern/waterflow/water_flow_sections.h"

namespace OHOS::Ace::Framework {
class JSWaterFlowSectionsBinding : public JSWaterFlowSections {
public:
    JSWaterFlowSectionsBinding() = default;
    ~JSWaterFlowSectionsBinding() = default;
    static bool ParseSectionOptions(
        const JSCallbackInfo& args, const JSRef<JSVal>& jsValue, NG::WaterFlowSections::Section& section);
    static void JSBind(BindingTarget globalObj);
    static void SetNativeWaterFlowSection(JSRef<JSObject> jsSection, JSRef<JSObject> nativeSection);

    void OnSectionChanged(const JSCallbackInfo& info);

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSWaterFlowSectionsBinding);
    static void Constructor(const JSCallbackInfo& info);
    static void Destructor(JSWaterFlowSections* section);
};
} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_WATER_FLOW_SECTIONS_BINDING_H