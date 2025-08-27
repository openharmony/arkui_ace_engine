
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
// foundation/arkui/ace_engine/frameworks/core/components_ng/pattern/slider/slider_custom_content_options.h

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_CUSTOM_CONTENT_OPTIONS_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_CUSTOM_CONTENT_OPTIONS_H

#include <string>

namespace OHOS::Ace::NG {

struct SliderCustomContentOptions {
    std::string accessibilityText = "";
    std::string accessibilityDescription = "";
    std::string accessibilityLevel = "auto";
    bool accessibilityGroup = false;
};

struct SliderPrefixOptions : public SliderCustomContentOptions {};

struct SliderSuffixOptions : public SliderCustomContentOptions {};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_CUSTOM_CONTENT_OPTIONS_H
