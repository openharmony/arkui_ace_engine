/*
 * Copyright (c) 2021-2026 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SWIPER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SWIPER_H

#include "base/memory/referenced.h"
#include "core/components_ng/pattern/swiper/bridge/swiper_controller_modifier_api.h"

namespace OHOS::Ace::Framework {

class JSSwiperControllerBinding;

class JSSwiperController : public Referenced {
public:
    JSSwiperController() = default;
    ~JSSwiperController() override = default;

    void SetControllerHandle(const RefPtr<AceType>& controller)
    {
        controller_ = controller;
    }

    const RefPtr<AceType>& GetControllerHandle() const
    {
        return controller_;
    }

    void SetInstanceId(int32_t id)
    {
        instanceId_ = id;
    }

private:
    friend class JSSwiperControllerBinding;
    int32_t instanceId_ = -1;
    RefPtr<AceType> controller_;

    ACE_DISALLOW_COPY_AND_MOVE(JSSwiperController);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SWIPER_H
