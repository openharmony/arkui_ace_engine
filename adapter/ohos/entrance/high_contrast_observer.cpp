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

#include "adapter/ohos/entrance/high_contrast_observer.h"

namespace OHOS::Ace::Platform {
void HighContrastObserver::OnConfigChanged(const AccessibilityConfig::CONFIG_ID id,
    const AccessibilityConfig::ConfigValue& value)
{
    if (first_) {
        first_ = false;
        return;
    }
    auto container = aceContainer_.Upgrade();
    if (container == nullptr) {
        return;
    }
    auto pipelineContext = container->GetPipelineContext();
    auto fontManager = pipelineContext == nullptr ? nullptr : pipelineContext->GetFontManager();
    if (fontManager != nullptr) {
        fontManager->UpdateHybridRenderNodes();
    }
}
} // namespace OHOS::Ace::Platform
