/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_INDICATOR_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_INDICATOR_H

#include <functional>

#include "base/memory/referenced.h"
#include "core/components_ng/pattern/swiper_indicator/bridge/indicator_controller_modifier_api.h"
#include "base/utils/utils.h"
#include "core/common/container_consts.h"

namespace OHOS::Ace::Framework {
class JSIndicatorControllerBinding;

class ACE_FORCE_EXPORT JSIndicatorController : public Referenced {
public:
    JSIndicatorController();
    ~JSIndicatorController() override = default;

    void SetControllerHandle(const RefPtr<AceType>& controller, const RefPtr<AceType>& indicatorNode);
    void ResetSwiperNode();
    std::function<void()> SetSwiperNodeBySwiper(const RefPtr<AceType>& node);
    RefPtr<AceType> GetControllerBase() const;

    void SetInstanceId(int32_t id)
    {
        instanceId_ = id;
    }

private:
    friend class JSIndicatorControllerBinding;
    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;
    RefPtr<AceType> controllerHandle_;
    ACE_DISALLOW_COPY_AND_MOVE(JSIndicatorController);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_INDICATOR_H
