/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_SHOULD_BUILT_IN_RECOGNIZER_PARALLEL_WITH_FUNCTION_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_SHOULD_BUILT_IN_RECOGNIZER_PARALLEL_WITH_FUNCTION_H

#include "frameworks/bridge/declarative_frontend/engine/functions/js_gesture_recognizer.h"

namespace OHOS::Ace::Framework {
class JsShouldBuiltInRecognizerParallelWithFunction : public JsFunction {
    DECLARE_ACE_TYPE(JsShouldBuiltInRecognizerParallelWithFunction, JsFunction);

public:
    explicit JsShouldBuiltInRecognizerParallelWithFunction(const JSRef<JSFunc>& jsFunction)
        : JsFunction(JSRef<JSObject>(), jsFunction)
    {}

    ~JsShouldBuiltInRecognizerParallelWithFunction() override = default;

    void Execute()
    {
        ExecuteJS();
    }

    RefPtr<NG::NGGestureRecognizer> Execute(
        const RefPtr<NG::NGGestureRecognizer>& current, const std::vector<RefPtr<NG::NGGestureRecognizer>>& others);
    static JSRef<JSObject> CreateRecognizerObject(const RefPtr<NG::NGGestureRecognizer>& target);
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_SHOULD_BUILT_IN_RECOGNIZER_PARALLEL_WITH_FUNCTION_H
