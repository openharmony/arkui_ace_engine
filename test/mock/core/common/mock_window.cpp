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

#include "core/common/window.h"

namespace OHOS::Ace {
Window::Window(std::unique_ptr<PlatformWindow> platformWindow) : platformWindow_(std::move(platformWindow)) {}

void Window::OnVsync(uint64_t nanoTimestamp, uint64_t frameCount) {}

void Window::RequestFrame() {}

void Window::SetRootRenderNode(const RefPtr<RenderNode>& root) {}

void Window::SetVsyncCallback(AceVsyncCallback&& callback) {}

void Window::SetUiDvsyncSwitch(bool dvsyncSwitch) {}
} // namespace OHOS::Ace
