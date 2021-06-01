/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_QUICKJS_FUNCTION_QJS_TOUCH_FUNCTION_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_QUICKJS_FUNCTION_QJS_TOUCH_FUNCTION_H

#include "base/geometry/offset.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/functions/qjs_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/gestures/raw_recognizer.h"

namespace OHOS::Ace::Framework {

class QJSTouchFunction : public QJSFunction {
    DECLARE_ACE_TYPE(QJSTouchFunction, QJSFunction)

public:
    QJSTouchFunction(JSContext* ctx, JSValue jsFunction) : QJSFunction(ctx, JS_UNDEFINED, jsFunction) {}
    ~QJSTouchFunction()
    {
        LOGD("Destroy: QJSTouchFunction");
    };

    virtual void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc) override;
    virtual void ReleaseRT(JSRuntime* rt) override;

    void execute(const TouchCallBackInfo& info);

private:
    JSValue createTouchInfo(const TouchCallBackInfo& touchInfo);
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_QUICKJS_FUNCTION_QJS_TOUCH_FUNCTION_H
