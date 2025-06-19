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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_WATER_FLOW_SECTIONS_ACCESSOR_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_WATER_FLOW_SECTIONS_ACCESSOR_PEER_IMPL_H

#include "base/utils/utils.h"
#include "core/common/container_consts.h"
#include "core/components_ng/pattern/waterflow/water_flow_sections.h"

struct WaterFlowSectionsPeer {
    OHOS::Ace::RefPtr<OHOS::Ace::NG::WaterFlowSections> GetController() const
    {
        return controller_;
    }

    void SetController(const OHOS::Ace::RefPtr<OHOS::Ace::NG::WaterFlowSections>& controller)
    {
        controller_ = controller;
    }
private:
    OHOS::Ace::RefPtr<OHOS::Ace::NG::WaterFlowSections> controller_;
};
#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_WATER_FLOW_SECTIONS_ACCESSOR_PEER_IMPL_H