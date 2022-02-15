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

#include "drag_window_ohos.h"
#include "base/log/log_wrapper.h"

namespace OHOS::Ace {
RefPtr<DragWindow> DragWindow::CreateDragWindow(const std::string& windowName, int32_t x, int32_t y, uint32_t width,
    uint32_t height)
{
    OHOS::sptr<OHOS::Rosen::WindowOption> option = new OHOS::Rosen::WindowOption();
    option->SetWindowRect({ x, y, width, height });
    option->SetWindowType(OHOS::Rosen::WindowType::WINDOW_TYPE_DRAGGING_EFFECT);
    option->SetWindowMode(OHOS::Rosen::WindowMode::WINDOW_MODE_FLOATING);
    OHOS::sptr<OHOS::Rosen::Window> dragWindow = OHOS::Rosen::Window::Create(windowName, option);
    if (!dragWindow) {
        LOGE("create drag window failed.");
        return nullptr;
    }

    OHOS::Rosen::WMError ret = dragWindow->Show();
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        LOGE("DragWindow::CreateDragWindow, drag window Show() failed, ret: %d", ret);
    }

    return AceType::MakeRefPtr<DragWindowOhos>(dragWindow);
}


void DragWindowOhos::MoveTo(int32_t x, int32_t y) const
{
    if (!dragWindow_) {
        LOGE("DragWindowOhos::MoveTo, the drag window is null.");
        return;
    }

    OHOS::Rosen::WMError ret = dragWindow_->MoveTo(x, y);
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        LOGE("DragWindow::MoveTo, drag window move failed, ret: %d", ret);
        return;
    }

    ret = dragWindow_->Show();
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        LOGE("DragWindow::CreateDragWindow, drag window Show() failed, ret: %d", ret);
    }
}

void DragWindowOhos::Destory() const
{
    if (!dragWindow_) {
        LOGE("DragWindowOhos::Destory, the drag window is null.");
        return;
    }

    OHOS::Rosen::WMError ret = dragWindow_->Destroy();
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        LOGE("DragWindow::Destory, drag window destroy failed, ret: %d", ret);
    }
}
} // namespace OHOS::Ace
