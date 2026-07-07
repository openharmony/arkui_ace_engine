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
#include "core/components_ng/pattern/tabs/bridge/tabs_controller_modifier_api.h"

namespace OHOS::Ace::Framework {

constexpr int32_t INSTANCE_ID_UNDEFINED = -1;

class ACE_FORCE_EXPORT JSTabsController : public Referenced {
public:
    JSTabsController();
    ~JSTabsController() override = default;

    static void Destructor(JSTabsController* controller);
    static RefPtr<AceType> CreateController();

    void ChangeIndex(int32_t index);

    const RefPtr<AceType>& GetController() const
    {
        return controller_;
    }

    void SetControllerHandle(const RefPtr<AceType>& handle);

    const RefPtr<AceType>& GetControllerHandle() const
    {
        return controllerHandle_;
    }

    void SetInstanceId(int32_t id)
    {
        instanceId_ = id;
    }

    void SetOnChangeImpl(const std::function<void(int32_t)>& onChangeImpl);

    void StartShowTabBar(int32_t delay = 0);

    void CancelShowTabBar();

    void UpdateTabBarHiddenOffset(float offset);

private:
    friend class JSTabsControllerBinding;
    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;
    RefPtr<AceType> controller_;
    RefPtr<AceType> controllerHandle_;
    std::function<void(int32_t)> onChangeImpl_;

    ACE_DISALLOW_COPY_AND_MOVE(JSTabsController);
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_ACE_ENGINE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JSVIEW_JS_TABS_CONTROLLER_H
