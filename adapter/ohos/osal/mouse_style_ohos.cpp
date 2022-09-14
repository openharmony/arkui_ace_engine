/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "mouse_style_ohos.h"

#include "input_manager.h"
#include "struct_multimodal.h"

#include "base/log/log_wrapper.h"

namespace OHOS::Ace {

RefPtr<MouseStyle> MouseStyle::CreateMouseStyle()
{
    return AceType::MakeRefPtr<MouseStyleOhos>();
}

bool MouseStyleOhos::SetPointerStyle(int32_t windowId, MouseFormat pointerStyle) const
{
    auto inputManager = MMI::InputManager::GetInstance();
    if (inputManager == nullptr) {
        LOGE("InputManager instance is valid");
        return false;
    }
    int32_t MMIPointStyle = 0;
    switch (pointerStyle) {
        case MouseFormat::WEST_EAST:
            MMIPointStyle = MMI::WEST_EAST;
            break;
        case MouseFormat::NORTH_SOUTH:
            MMIPointStyle = MMI::NORTH_SOUTH;
            break;
        case MouseFormat::HAND_POINTING:
            MMIPointStyle = MMI::HAND_POINTING;
            break;
        case MouseFormat::TEXT_CURSOR:
            MMIPointStyle = MMI::TEXT_CURSOR;
            break;
        default:
            MMIPointStyle = MMI::DEFAULT;
    }
    int32_t setResult = inputManager->SetPointerStyle(windowId, MMIPointStyle);
    if (setResult == -1) {
        LOGE("SetPointerStyle result is false");
        return false;
    }
    return true;
}

int32_t MouseStyleOhos::GetPointerStyle(int32_t windowId, int32_t& pointerStyle) const
{
    auto inputManager = MMI::InputManager::GetInstance();
    if (inputManager == nullptr) {
        LOGE("InputManager instance is valid");
        return -1;
    }
    int32_t getResult = inputManager->GetPointerStyle(windowId, pointerStyle);
    if (getResult == -1) {
        LOGE("GetPointerStyle result is false");
        return -1;
    }
    return getResult;
}

} // namespace OHOS::Ace