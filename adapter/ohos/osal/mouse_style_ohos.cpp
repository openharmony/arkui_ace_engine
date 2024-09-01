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

#include "core/common/container.h"

namespace OHOS::Ace {

RefPtr<MouseStyle> MouseStyle::CreateMouseStyle()
{
    return AceType::MakeRefPtr<MouseStyleOhos>();
}

bool MouseStyleOhos::SetPointerStyle(int32_t windowId, MouseFormat pointerStyle) const
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto isUIExtension = container->IsUIExtensionWindow() && pointerStyle != MouseFormat::DEFAULT;
    auto inputManager = MMI::InputManager::GetInstance();
    CHECK_NULL_RETURN(inputManager, false);
    static const LinearEnumMapNode<MouseFormat, int32_t> mouseFormatMap[] = {
        { MouseFormat::DEFAULT, MMI::DEFAULT },
        { MouseFormat::EAST, MMI::EAST },
        { MouseFormat::WEST, MMI::WEST },
        { MouseFormat::SOUTH, MMI::SOUTH },
        { MouseFormat::NORTH, MMI::NORTH },
        { MouseFormat::WEST_EAST, MMI::WEST_EAST },
        { MouseFormat::NORTH_SOUTH, MMI::NORTH_SOUTH },
        { MouseFormat::NORTH_EAST, MMI::NORTH_EAST },
        { MouseFormat::NORTH_WEST, MMI::NORTH_WEST },
        { MouseFormat::SOUTH_EAST, MMI::SOUTH_EAST },
        { MouseFormat::SOUTH_WEST, MMI::SOUTH_WEST },
        { MouseFormat::NORTH_EAST_SOUTH_WEST, MMI::NORTH_EAST_SOUTH_WEST },
        { MouseFormat::NORTH_WEST_SOUTH_EAST, MMI::NORTH_WEST_SOUTH_EAST },
        { MouseFormat::CROSS, MMI::CROSS },
        { MouseFormat::CURSOR_COPY, MMI::CURSOR_COPY },
        { MouseFormat::CURSOR_FORBID, MMI::CURSOR_FORBID },
        { MouseFormat::COLOR_SUCKER, MMI::COLOR_SUCKER },
        { MouseFormat::HAND_GRABBING, MMI::HAND_GRABBING },
        { MouseFormat::HAND_OPEN, MMI::HAND_OPEN },
        { MouseFormat::HAND_POINTING, MMI::HAND_POINTING },
        { MouseFormat::HELP, MMI::HELP },
        { MouseFormat::CURSOR_MOVE, MMI::CURSOR_MOVE },
        { MouseFormat::RESIZE_LEFT_RIGHT, MMI::RESIZE_LEFT_RIGHT },
        { MouseFormat::RESIZE_UP_DOWN, MMI::RESIZE_UP_DOWN },
        { MouseFormat::SCREENSHOT_CHOOSE, MMI::SCREENSHOT_CHOOSE },
        { MouseFormat::SCREENSHOT_CURSOR, MMI::SCREENSHOT_CURSOR },
        { MouseFormat::TEXT_CURSOR, MMI::TEXT_CURSOR },
        { MouseFormat::ZOOM_IN, MMI::ZOOM_IN },
        { MouseFormat::ZOOM_OUT, MMI::ZOOM_OUT },
        { MouseFormat::MIDDLE_BTN_EAST, MMI::MIDDLE_BTN_EAST },
        { MouseFormat::MIDDLE_BTN_WEST, MMI::MIDDLE_BTN_WEST },
        { MouseFormat::MIDDLE_BTN_SOUTH, MMI::MIDDLE_BTN_SOUTH },
        { MouseFormat::MIDDLE_BTN_NORTH, MMI::MIDDLE_BTN_NORTH },
        { MouseFormat::MIDDLE_BTN_NORTH_SOUTH, MMI::MIDDLE_BTN_NORTH_SOUTH },
        { MouseFormat::MIDDLE_BTN_NORTH_EAST, MMI::MIDDLE_BTN_NORTH_EAST },
        { MouseFormat::MIDDLE_BTN_NORTH_WEST, MMI::MIDDLE_BTN_NORTH_WEST },
        { MouseFormat::MIDDLE_BTN_SOUTH_EAST, MMI::MIDDLE_BTN_SOUTH_EAST },
        { MouseFormat::MIDDLE_BTN_SOUTH_WEST, MMI::MIDDLE_BTN_SOUTH_WEST },
        { MouseFormat::MIDDLE_BTN_NORTH_SOUTH_WEST_EAST, MMI::MIDDLE_BTN_NORTH_SOUTH_WEST_EAST },
        { MouseFormat::HORIZONTAL_TEXT_CURSOR, MMI::HORIZONTAL_TEXT_CURSOR },
        { MouseFormat::CURSOR_CROSS, MMI::CURSOR_CROSS },
        { MouseFormat::CURSOR_CIRCLE, MMI::CURSOR_CIRCLE },
        { MouseFormat::LOADING, MMI::LOADING },
        { MouseFormat::RUNNING, MMI::RUNNING },
    };
    int32_t MMIPointStyle = MMI::DEFAULT;
    int64_t idx = BinarySearchFindIndex(mouseFormatMap, ArraySize(mouseFormatMap), pointerStyle);
    if (idx >= 0) {
        MMIPointStyle = mouseFormatMap[idx].value;
    }
    MMI::PointerStyle style;
    style.id = MMIPointStyle;
    TAG_LOGI(AceLogTag::ACE_MOUSE, "SetPointerStyle windowId=%{public}d style=%{public}d isUIExtension=%{public}d",
        windowId, static_cast<int32_t>(pointerStyle), isUIExtension);
    int32_t setResult = inputManager->SetPointerStyle(windowId, style, isUIExtension);
    if (setResult == -1) {
        LOGW("SetPointerStyle result is false");
        return false;
    }
    return true;
}

int32_t MouseStyleOhos::GetPointerStyle(int32_t windowId, int32_t& pointerStyle) const
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, -1);
    auto isUIExtension = container->IsUIExtensionWindow();
    auto inputManager = MMI::InputManager::GetInstance();
    CHECK_NULL_RETURN(inputManager, -1);
    MMI::PointerStyle style;
    int32_t getResult = inputManager->GetPointerStyle(windowId, style, isUIExtension);
    if (getResult == -1) {
        LOGW("GetPointerStyle result is false");
        return -1;
    }
    pointerStyle = style.id;
    return getResult;
}

bool MouseStyleOhos::ChangePointerStyle(int32_t windowId, MouseFormat mouseFormat) const
{
    int32_t curPointerStyle = -1;
    if (GetPointerStyle(windowId, curPointerStyle) == -1) {
        LOGW("ChangePointerStyle: GetPointerStyle return failed");
        return false;
    }
    if (curPointerStyle == static_cast<int32_t>(mouseFormat)) {
        return true;
    }

    return SetPointerStyle(windowId, mouseFormat);
}

void MouseStyleOhos::SetMouseIcon(
    int32_t windowId, MouseFormat pointerStyle, std::shared_ptr<Media::PixelMap> pixelMap) const
{
    auto inputManager = MMI::InputManager::GetInstance();
    if (pointerStyle == MouseFormat::CONTEXT_MENU) {
        inputManager->SetPointerVisible(true);
        inputManager->SetMouseIcon(windowId, static_cast<void*>(pixelMap.get()));
    } else if (pointerStyle == MouseFormat::ALIAS) {
        inputManager->SetMouseIcon(windowId, static_cast<void*>(pixelMap.get()));
        inputManager->SetPointerVisible(true);
    }
}

void MouseStyleOhos::SetCustomCursor(
    int32_t windowId, int32_t focusX, int32_t focusY, std::shared_ptr<Media::PixelMap> pixelMap) const
{
    auto inputManager = MMI::InputManager::GetInstance();
    CHECK_NULL_VOID(inputManager);
    CHECK_NULL_VOID(pixelMap);

    int32_t status = inputManager->SetCustomCursor(windowId, static_cast<void*>(pixelMap.get()), focusX, focusY);
    if (status != 0) {
        TAG_LOGE(AceLogTag::ACE_WEB, "set custom cursor failed %{public}u", status);
        return;
    }
    inputManager->SetPointerVisible(true);
}

void MouseStyleOhos::SetPointerVisible(MouseFormat pointerStyle) const
{
    auto inputManager = MMI::InputManager::GetInstance();
    if (pointerStyle != MouseFormat::CURSOR_NONE) {
        inputManager->SetPointerVisible(true);
    } else {
        inputManager->SetPointerVisible(false);
    }
}
} // namespace OHOS::Ace