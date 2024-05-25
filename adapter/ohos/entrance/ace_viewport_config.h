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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_ADAPTER_OHOS_ENTRANCE_ACE_VIEWPORT_CONFIG_H
#define FOUNDATION_ARKUI_ACE_ENGINE_ADAPTER_OHOS_ENTRANCE_ACE_VIEWPORT_CONFIG_H

#include "wm/window.h"
#include "interfaces/inner_api/ace/viewport_config.h"

namespace OHOS::Ace {
struct AceViewportConfig {
    AceViewportConfig() = default;
    AceViewportConfig(ViewportConfig cfg, OHOS::Rosen::WindowSizeChangeReason reason,
        std::shared_ptr<OHOS::Rosen::RSTransaction> rsTransaction)
        : config_(cfg), reason_(reason), rsTransaction_(rsTransaction) {}

    bool operator==(const AceViewportConfig &other) const
    {
        return config_.Width() == other.config_.Width() &&
               config_.Height() == other.config_.Height() &&
               config_.Left() == other.config_.Left() &&
               config_.Top() == other.config_.Top() &&
               config_.Density() == other.config_.Density() &&
               config_.Orientation() == other.config_.Orientation() &&
               reason_ == other.reason_ &&
               rsTransaction_ == other.rsTransaction_;
    }

    bool operator!=(const AceViewportConfig &other) const
    {
        return config_.Width() != other.config_.Width() ||
               config_.Height() != other.config_.Height() ||
               config_.Left() != other.config_.Left() ||
               config_.Top() != other.config_.Top() ||
               config_.Density() != other.config_.Density() ||
               config_.Orientation() != other.config_.Orientation() ||
               reason_ != other.reason_ ||
               rsTransaction_ != other.rsTransaction_;
    }

    ViewportConfig config_;
    OHOS::Rosen::WindowSizeChangeReason reason_;
    std::shared_ptr<OHOS::Rosen::RSTransaction> rsTransaction_;
}; // AceViewportConfig

} // OHOS::Ace
#endif // FOUNDATION_ARKUI_ACE_ENGINE_ADAPTER_OHOS_ENTRANCE_ACE_VIEWPORT_CONFIG_H
