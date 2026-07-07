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

#ifndef FOUNDATION_ACE_ACE_ENGINE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JSVIEW_JS_TABS_CONTROLLER_BINDING_H
#define FOUNDATION_ACE_ACE_ENGINE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JSVIEW_JS_TABS_CONTROLLER_BINDING_H

#include "bridge/declarative_frontend/engine/js_types.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_tabs_controller.h"
#include "bridge/declarative_frontend/engine/bindings_defines.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "core/components_ng/pattern/tabs/tabs_controller.h"

namespace OHOS::Ace::Framework {
class JSTabsControllerBinding final : public JSTabsController {
public:
    static void JSBind(BindingTarget globalObj);
    static void Constructor(const JSCallbackInfo& args);

    void PreloadItems(const JSCallbackInfo& args);
    void SetTabBarTranslate(const JSCallbackInfo& args);
    void SetTabBarOpacity(const JSCallbackInfo& args);
};
} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_ACE_ENGINE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JSVIEW_JS_TABS_CONTROLLER_BINDING_H
