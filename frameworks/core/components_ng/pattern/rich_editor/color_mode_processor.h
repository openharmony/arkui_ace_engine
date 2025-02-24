/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RICH_EDITOR_COLOR_MODE_PROCESSOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RICH_EDITOR_COLOR_MODE_PROCESSOR_H

#include "base/memory/ace_type.h"
#include "base/utils/device_config.h"
#include "core/common/resource/resource_manager.h"

#define COLOR_MODE_LOCK(colorMode) NG::ColorModeProcessor colorModeProcessor(colorMode)

namespace OHOS::Ace::NG {

class ColorModeProcessor {
public:
    ColorModeProcessor();
    ColorModeProcessor(const ColorMode colorMode)
    {
        if (colorMode != ColorMode::COLOR_MODE_UNDEFINED) {
            adapter_ = ResourceManager::GetInstance().GetResourceAdapter();
            CHECK_NULL_VOID(adapter_);
            colorMode_ = adapter_->GetResourceColorMode();
            adapter_->UpdateColorMode(colorMode);
        }
    }
    ~ColorModeProcessor()
    {
        CHECK_NULL_VOID(adapter_);
        if (colorMode_ != ColorMode::COLOR_MODE_UNDEFINED) {
            adapter_->UpdateColorMode(colorMode_);
        }
    }
private:
    RefPtr<ResourceAdapter> adapter_;
    ColorMode colorMode_ = ColorMode::COLOR_MODE_UNDEFINED;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_RICH_EDITOR_COLOR_MODE_PROCESSOR_H
