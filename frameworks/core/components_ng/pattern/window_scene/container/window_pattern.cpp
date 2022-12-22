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

#include "include/vsync_station.h"
#include "native_engine/native_engine.h"
#include "native_engine/native_value.h"
#include "window_scene_common.h"

#include "core/components_ng/pattern/window_scene/container/window_pattern.h"

namespace OHOS::Ace::NG {

WindowPattern::WindowPattern(
    const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode,
    const std::shared_ptr<AbilityRuntime::Context>& runtimeContext)
    : surfaceNode_(surfaceNode), runtimeContext_(runtimeContext)
{}

Rosen::WSError WindowPattern::SetUIContent(const std::string& contentInfo,
    NativeEngine* engine, NativeValue* storage, bool isDistributed, AppExecFwk::Ability* ability)
{
    // LOGI("SetUIContent contentInfo: %{public}s", contentInfo.c_str());
    // std::unique_ptr<UIContent> uiContent;
    // if (ability != nullptr) {
    //     uiContent = UIContent::Create(ability);
    // } else {
    //     uiContent = UIContent::Create(runtimeContext_.get(), engine);
    // }
    // if (uiContent == nullptr) {
    //     LOGE("fail to SetUIContent id: %{public}u", GetWindowId());
    //     return Rosen::WSError::WS_ERROR_NULLPTR;
    // }
    // // if (!isAppDecorEnable_ || !windowSystemConfig_.isSystemDecorEnable_) {
    // //     WLOGFI("app set decor enable false");
    // //     property_->SetDecorEnable(false);
    // // }
    // if (isDistributed) {
    //     uiContent->Restore(this, contentInfo, storage);
    // } else {
    //     uiContent->Initialize(this, contentInfo, storage);
    // }
    // // make uiContent available after Initialize/Restore
    // uiContent_ = std::move(uiContent);

    // if (state_ == WindowState::STATE_SHOWN) {
    //     UpdateTitleButtonVisibility();
    //     ViewportConfig config;
    //     Rect rect = GetRect();
    //     config.SetSize(rect.Width(), rect.Height());
    //     config.SetPosition(rect.Left(), rect.Top());
    //     // auto display = DisplayManager::GetInstance().GetDisplayById(property_->GetDisplayId());
    //     // if (display == nullptr) {
    //     //     WLOGFE("get display failed displayId:%{public}" PRIu64", window id:%{public}u", property_->GetDisplayId(),
    //     //         property_->GetWindowId());
    //     //     return Rosen::WSError::WS_ERROR_NULLPTR;
    //     // }
    //     // float virtualPixelRatio = display->GetVirtualPixelRatio();
    //     // config.SetDensity(virtualPixelRatio);
    //     uiContent_->UpdateViewportConfig(config, WindowSizeChangeReason::UNDEFINED);
    //     LOGI("notify uiContent window size change end");
    // }
    return Rosen::WSError::WS_OK;
}

void WindowPattern::RequestVsync(const std::shared_ptr<Rosen::VsyncCallback>& vsyncCallback)
{
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    // if (state_ == WindowState::STATE_DESTROYED) {
    //    LOGE("[WM] Receive Vsync Request failed, window is destroyed");
    //     return;
    // }
    Rosen::VsyncStation::GetInstance().RequestVsync(vsyncCallback);
}

} // namespace OHOS::Ace::NG
