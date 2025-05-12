/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_GESTURE_JUDGE_FUNCTION_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_GESTURE_JUDGE_FUNCTION_H

#include <cstdint>
#include <memory>

#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/gestures/base_gesture_event.h"
#include "core/gestures/gesture_info.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"

namespace OHOS::Ace::Framework {
class JsGestureJudgeFunction : public JsFunction {
    DECLARE_ACE_TYPE(JsGestureJudgeFunction, JsFunction)

public:
    explicit JsGestureJudgeFunction(const JSRef<JSFunc>& jsFunction) : JsFunction(JSRef<JSObject>(), jsFunction) {}

    ~JsGestureJudgeFunction() override = default;

    void Execute() override
    {
        ExecuteJS();
    }

    GestureJudgeResult Execute(
        const RefPtr<NG::GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info);

    GestureJudgeResult Execute(const std::shared_ptr<BaseGestureEvent>& info,
        const RefPtr<NG::NGGestureRecognizer>& current, const std::list<RefPtr<NG::NGGestureRecognizer>>& others);

private:
    JSRef<JSObject> CreateFingerInfo(const FingerInfo& fingerInfo);
    JSRef<JSObject> CreateEventTargetObject(const std::shared_ptr<BaseGestureEvent>& info);
    void SetUniqueAttributes(
        JSRef<JSObject>& obj, GestureTypeName typeName, const std::shared_ptr<BaseGestureEvent>& info);
    JSRef<JSObject> CreateGestureEventObject(const std::shared_ptr<BaseGestureEvent>& info, GestureTypeName typeName);
    JSRef<JSObject> CreateFingerInfosObject(const std::shared_ptr<BaseGestureEvent>& info, JSRef<JSObject>& obj);
    void ParsePanGestureEvent(JSRef<JSObject>& obj, const std::shared_ptr<BaseGestureEvent>& info);
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_GESTURE_JUDGE_FUNCTION_H
