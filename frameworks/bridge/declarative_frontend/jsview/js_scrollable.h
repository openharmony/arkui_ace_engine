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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SCROLLABLE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SCROLLABLE_H

#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"

namespace OHOS::Ace::Framework {
class JSScrollable {
public:
    static EdgeEffect ParseEdgeEffect(const JSRef<JSVal>& jsValue, EdgeEffect defaultValue);
    static bool ParseAlwaysEnable(const JSRef<JSVal>& jsValue, bool defaultValue);
    static EffectEdge ParseEffectEdge(const JSRef<JSVal>& jsValue);
    static DisplayMode ParseDisplayMode(const JSCallbackInfo& info, DisplayMode defaultValue);
    static std::string ParseBarColor(const JSCallbackInfo& info);
    static std::string ParseBarWidth(const JSCallbackInfo& info);

    static void JsClip(const JSCallbackInfo& info);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SCROLLABLE_H
