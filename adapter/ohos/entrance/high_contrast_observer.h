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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_CPP_HIGH_CONTRAST_OBSERVER_H
#define FOUNDATION_ACE_ADAPTER_OHOS_CPP_HIGH_CONTRAST_OBSERVER_H

#include <memory>
#include "accessibility_config.h"
#include "adapter/ohos/entrance/ace_container.h"

namespace OHOS::Ace::Platform {
class HighContrastObserver : public AccessibilityConfig::AccessibilityConfigObserver {
public:
    HighContrastObserver(WeakPtr<AceContainer> aceContainer) : aceContainer_(aceContainer) {}

    void OnConfigChanged(const AccessibilityConfig::CONFIG_ID id, const AccessibilityConfig::ConfigValue& value);

private:
    WeakPtr<AceContainer> aceContainer_;
    bool first_ = true;
};
} // namespace OHOS::Ace::Platform
#endif // FOUNDATION_ACE_ADAPTER_OHOS_CPP_HIGH_CONTRAST_OBSERVER_H