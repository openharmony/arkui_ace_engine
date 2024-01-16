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

#include "core/components_ng/pattern/xcomponent/xcomponent_controller_ng.h"

#include "base/log/log_wrapper.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"

namespace OHOS::Ace::NG {
XComponentControllerErrorCode XComponentControllerNG::GetGlobalPosition(float& offsetX, float& offsetY)
{
    auto pattern = pattern_.Upgrade();
    if (!pattern) {
        return XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    if (pattern->GetType() != XComponentType::SURFACE) {
        return XCOMPONENT_CONTROLLER_TYPE_ERROR;
    }
    auto globalPostion = pattern->GetOffsetRelativeToWindow();
    offsetX = globalPostion.GetX();
    offsetY = globalPostion.GetY();
    return XCOMPONENT_CONTROLLER_NO_ERROR;
}

XComponentControllerErrorCode XComponentControllerNG::GetSize(float& width, float& height)
{
    auto pattern = pattern_.Upgrade();
    if (!pattern) {
        return XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    if (pattern->GetType() != XComponentType::SURFACE) {
        return XCOMPONENT_CONTROLLER_TYPE_ERROR;
    }
    auto drawSize = pattern->GetDrawSize();
    width = drawSize.Width();
    height = drawSize.Height();
    return XCOMPONENT_CONTROLLER_NO_ERROR;
}

XComponentControllerErrorCode XComponentControllerNG::SetExtController(
    std::shared_ptr<XComponentController> xcomponentController)
{
    auto pattern = pattern_.Upgrade();
    if (!pattern) {
        return XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    if (pattern->GetType() != XComponentType::SURFACE) {
        return XCOMPONENT_CONTROLLER_TYPE_ERROR;
    }
    auto extController = std::static_pointer_cast<NG::XComponentControllerNG>(xcomponentController);
    if (!extController) {
        return XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    auto extPattern = extController->GetPattern();
    if (!extPattern) {
        return XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    if (extPattern->GetType() != XComponentType::SURFACE) {
        return XCOMPONENT_CONTROLLER_TYPE_ERROR;
    }
    return pattern->SetExtController(extPattern);
}

XComponentControllerErrorCode XComponentControllerNG::ResetExtController(
    std::shared_ptr<XComponentController> xcomponentController)
{
    auto pattern = pattern_.Upgrade();
    if (!pattern) {
        return XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    if (pattern->GetType() != XComponentType::SURFACE) {
        return XCOMPONENT_CONTROLLER_TYPE_ERROR;
    }
    auto extController = std::static_pointer_cast<NG::XComponentControllerNG>(xcomponentController);
    auto extPattern = extController->GetPattern();
    if (!extPattern) {
        return XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    if (extPattern->GetType() != XComponentType::SURFACE) {
        return XCOMPONENT_CONTROLLER_TYPE_ERROR;
    }
    return pattern->ResetExtController(extPattern);
}

void XComponentControllerNG::SetPattern(const RefPtr<XComponentPattern>& pattern)
{
    pattern_ = pattern;
}

RefPtr<XComponentPattern> XComponentControllerNG::GetPattern()
{
    return pattern_.Upgrade();
}
} // namespace OHOS::Ace::NG
