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

#ifndef FOUNDATION_ACE_ACE_ENGINE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JSVIEW_JS_TABS_CONTROLLER_H
#define FOUNDATION_ACE_ACE_ENGINE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JSVIEW_JS_TABS_CONTROLLER_H

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/engine/bindings_defines.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "core/components/tab_bar/tab_controller.h"
#include "core/components_ng/pattern/tabs/tabs_controller.h"

namespace OHOS::Ace::Framework {

class JSTabsController : public Referenced {
public:
    JSTabsController();
    ~JSTabsController() override = default;

    static void JSBind(BindingTarget globalObj);
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSTabsController* controller);
    static RefPtr<TabController> CreateController();

    void ChangeIndex(int32_t index);

    void PreloadItems(const JSCallbackInfo& args);

    void SetTabBarTranslate(const JSCallbackInfo& args);

    void SetTabBarOpacity(const JSCallbackInfo& args);

    const RefPtr<TabController>& GetController() const
    {
        return controller_;
    }

    void SetTabsController(const RefPtr<NG::TabsControllerNG>& tabsController)
    {
        tabsController_ = tabsController;
    }

    const RefPtr<NG::TabsControllerNG>& GetTabsController() const
    {
        return tabsController_;
    }

    void SetInstanceId(int32_t id)
    {
        instanceId_ = id;
    }

private:
    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;
    RefPtr<TabController> controller_;
    RefPtr<NG::TabsControllerNG> tabsController_; // used by ng structure

    ACE_DISALLOW_COPY_AND_MOVE(JSTabsController);
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_ACE_ENGINE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JSVIEW_JS_TABS_CONTROLLER_H
