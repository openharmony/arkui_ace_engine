/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LAYOUTABLE_VIEW_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LAYOUTABLE_VIEW_H

#include "frameworks/bridge/declarative_frontend/jsview/js_pan_handler.h"
#include "frameworks/core/pipeline/base/component.h"

namespace OHOS::Ace::Framework {

class JSLayoutableView {
public:
    static void JsPixelRound(const JSCallbackInfo& info);
    static void JsChainWeight(const JSCallbackInfo& info);
private:
    static void ParsePixelRoundOfStart(const JSRef<JSObject>& object, uint16_t& value);
    static void ParsePixelRoundOfTop(const JSRef<JSObject>& object, uint16_t& value);
    static void ParsePixelRoundOfEnd(const JSRef<JSObject>& object, uint16_t& value);
    static void ParsePixelRoundOfBottom(const JSRef<JSObject>& object, uint16_t& value);
}; // class JSLayoutableView
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LAYOUTABLE_VIEW_H