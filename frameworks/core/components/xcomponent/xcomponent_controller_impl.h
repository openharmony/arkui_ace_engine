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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_XCOMPONENT_CONTROLLER_IMPL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_XCOMPONENT_CONTROLLER_IMPL_H

#include "interfaces/inner_api/xcomponent_controller/xcomponent_controller.h"

#include "core/components_ng/pattern/xcomponent/inner_xcomponent_controller.h"

namespace OHOS::Ace {
class XComponentControllerImpl : public InnerXComponentController {
public:
    XComponentControllerImpl() = default;
    ~XComponentControllerImpl() override = default;

    XComponentControllerErrorCode GetGlobalPosition(float& /* offsetX */, float& /* offsetY */) override
    {
        return XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }

    XComponentControllerErrorCode GetSize(float& /* width */, float& /* height */) override
    {
        return XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }

    XComponentControllerErrorCode SetExtController(
        std::shared_ptr<XComponentController> /* xcomponentController */) override
    {
        return XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }

    XComponentControllerErrorCode ResetExtController(
        std::shared_ptr<XComponentController> /* xcomponentController */) override
    {
        return XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_XCOMPONENT_CONTROLLER_IMPL_H
