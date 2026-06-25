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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXTTIMER_CONTROLLER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXTTIMER_CONTROLLER_H

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "core/common/container_consts.h"
#include "core/components/texttimer/texttimer_controller.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_types.h"

namespace OHOS::Ace::Framework {
class JSTextTimerController final : public Referenced {
public:
    JSTextTimerController() = default;
    ~JSTextTimerController() override = default;

    static void JSBind(panda::Local<panda::ObjectRef> globalObj);
    static void Constructor(const JsiCallbackInfo& info);
    static void Destructor(JSTextTimerController* timerController);

    void Start(const JsiCallbackInfo& info);
    void Pause(const JsiCallbackInfo& info);
    void Reset(const JsiCallbackInfo& info);

    void SetController(const RefPtr<TextTimerController>& controller)
    {
        controller_ = controller;
    }

    RefPtr<TextTimerController> GetController() const
    {
        return controller_;
    }

    void SetInstanceId(int32_t id)
    {
        instanceId_ = id;
    }

private:
    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;
    RefPtr<TextTimerController> controller_;

    ACE_DISALLOW_COPY_AND_MOVE(JSTextTimerController);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXTTIMER_CONTROLLER_H
