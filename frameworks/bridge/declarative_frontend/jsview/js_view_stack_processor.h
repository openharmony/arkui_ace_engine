/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_STACK_PROCESSOR_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_STACK_PROCESSOR_H

#include <map>

#include "bridge/declarative_frontend/engine/bindings_defines.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "core/components/common/properties/state_attributes.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::Framework {

class JSViewStackProcessor {
public:
    JSViewStackProcessor() = default;
    ~JSViewStackProcessor() = default;

    static void JSBind(BindingTarget globalObj);
    static VisualState StringToVisualState(const std::string& stateString);

    static ElementIdType JsAllocateNewElmetIdForNextComponent()
    {
        return ElementRegister::GetInstance()->MakeUniqueId();
    }

    static void JsStartGetAccessRecordingFor(ElementIdType elmtId);

    static int32_t JsGetElmtIdToAccountFor();

    static void JsSetElmtIdToAccountFor(ElementIdType elmtId);

    static void JsStopGetAccessRecording();

    static void JsImplicitPopBeforeContinue();

    /**
     * Returns a globally unique id from ElementRegister
     * JS signatire: MakeUniqueId() : number
     */
    static void JSMakeUniqueId(const JSCallbackInfo& info);

    static void SetViewMap(const std::string& viewId, const JSRef<JSObject>& jsView)
    {
        if (viewMap_.find(viewId) != viewMap_.end()) {
            LOGW("jsView already exists for viewId: %{public}s", viewId.c_str());
            return;
        }

        viewMap_.emplace(viewId, jsView);
    }

    static JSRef<JSObject> GetViewById(const std::string viewId)
    {
        auto it = viewMap_.find(viewId);
        if (it == viewMap_.end()) {
            LOGW("get view failed with viewId:%{public}s", viewId.c_str());
            return JSRef<JSObject>::New();
        }
        LOGI("get view success with viewId:%{public}s", viewId.c_str());
        return it->second;
    }

    /**
     * return true of current Container uses new Pipeline
     */
    static bool JsUsesNewPipeline();

    /**
     * return the API version specified in the manifest.json
    */
    static int32_t JsGetApiVersion();

    /**
     * Gets framenode and pushes to VSP.
    */
    static void JsGetAndPushFrameNode(const JSCallbackInfo& info);

    /*
     * move deleted elmtIds from C+ ElementRegistry to this component.
     * JS caller must allocate empty Array<number> and provide as param
     */
    static void JsMoveDeletedElmtIds(const JSCallbackInfo& info);

    /*
    * Orders a frame request and registers a callback on next vsync
    */
    static void JSScheduleUpdateOnNextVSync(const JSCallbackInfo& info);

    /**
     * Send state info profiler when state var changed
     * Used in V2.
     */
    static void JsSendStateInfo(const std::string& stateInfo);

#ifdef ACE_STATIC
    static void JsPush(const JSCallbackInfo& info);
    
    static void JsPop();
#endif

    static void JsPushPrebuildCompCmd(const JSCallbackInfo& info);

    static bool JsCheckIsPrebuildTimeout();

private:
    static void JSVisualState(const JSCallbackInfo& info);
    static std::map<std::string, JSRef<JSObject>> viewMap_;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_STACK_PROCESSOR_H
