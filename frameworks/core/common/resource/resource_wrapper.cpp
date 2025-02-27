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

#include "core/common/container.h"
#include "core/common/resource/resource_wrapper.h"

namespace OHOS::Ace {
ResourceWrapper::ResourceWrapper(
    RefPtr<ThemeConstants>& themeConstants, RefPtr<ResourceAdapter>& resourceAdapter, ColorMode colorMode)
    : themeConstants_(themeConstants), resourceAdapter_(resourceAdapter), localColorMode_(colorMode)
{
    if (resourceAdapter && colorMode != ColorMode::COLOR_MODE_UNDEFINED) {
        resourceAdapter->UpdateColorMode(colorMode);
    }
};

ResourceWrapper::~ResourceWrapper()
{
    if (localColorMode_ != ColorMode::COLOR_MODE_UNDEFINED) {
        resourceAdapter_->UpdateColorMode(Container::CurrentColorMode());
    }
}
} // namespace OHOS::Ace
