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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_ON_SIZE_CHANGE_FUNCTION_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_ON_SIZE_CHANGE_FUNCTION_H

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/offset.h"
#include "base/geometry/rect.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/gestures/drag_recognizer.h"

namespace OHOS::Ace::Framework {

class JsOnSizeChangeFunction : public JsFunction {
    DECLARE_ACE_TYPE(JsOnSizeChangeFunction, JsFunction);

public:
    explicit JsOnSizeChangeFunction(const JSRef<JSFunc>& jsFunction) : JsFunction(jsFunction) {}
    ~JsOnSizeChangeFunction() override = default;
    void Execute()
    {
        ExecuteJS();
    }
    void Execute(const NG::RectF& oldRect, const NG::RectF& rect);
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_ON_SIZE_CHANGE_FUNCTION_H
