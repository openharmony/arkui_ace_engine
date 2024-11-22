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

#include "frameworks/core/components_ng/render/adapter/rosen_window.h"

namespace OHOS::Ace::NG {
RosenWindow::RosenWindow(const OHOS::sptr<OHOS::Rosen::Window>& window, RefPtr<TaskExecutor> taskExecutor, int32_t id)
    : rsWindow_(window), taskExecutor_(taskExecutor), id_(id) {}

void RosenWindow::Init() {}

void RosenWindow::FlushFrameRate(int32_t rate, int32_t animatorExpectedFrameRate, int32_t rateType) {}

void RosenWindow::SetUiDvsyncSwitch(bool dvsyncSwitch) {}

void RosenWindow::RequestFrame() {}

void RosenWindow::OnShow() {}

void RosenWindow::OnHide() {}

void RosenWindow::Destroy() {}

void RosenWindow::SetDrawTextAsBitmap(bool useBitmap) {}

void RosenWindow::SetRootFrameNode(const RefPtr<NG::FrameNode>& root) {}

void RosenWindow::RecordFrameTime(uint64_t timeStamp, const std::string& name) {}

void RosenWindow::FlushTasks() {}

float RosenWindow::GetRefreshRate() const
{
    return 0;
}

void RosenWindow::SetKeepScreenOn(bool keepScreenOn) {}

int64_t RosenWindow::GetVSyncPeriod() const
{
    return 0;
}

std::string RosenWindow::GetWindowName() const
{
    return "";
}

void RosenWindow::OnVsync(uint64_t nanoTimestamp, uint32_t frameCount) {}

uint32_t RosenWindow::GetStatusBarHeight() const
{
    return 0;
}

void RosenWindow::NotifyExtensionTimeout(int32_t errorCode) {}

} // namespace OHOS::Ace::NG
