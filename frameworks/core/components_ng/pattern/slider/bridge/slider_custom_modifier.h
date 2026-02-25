/*
* Copyright (c) 2026 Huawei Device Co., Ltd.
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_BRIDGE_SLIDER_CUSTOM_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_BRIDGE_SLIDER_CUSTOM_MODIFIER_H
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "interfaces/inner_api/ace_kit/include/ui/properties/ng/measure_property.h"

namespace OHOS::Ace::NG {
class FrameNode;
struct ArkUISliderCustomModifier {
    RefPtr<FrameNode> (*createSliderFrameNode)(int32_t nodeId);
    void (*sliderPatternUpdateValue)(RefPtr<FrameNode>& node, float value);
    void (*sliderLayoutPropertyUpdatePadding)(RefPtr<FrameNode>& node, PaddingProperty value);
    void (*sliderLayoutPropertyUpdateLayoutWeight)(RefPtr<FrameNode>& node, float value);
    void (*sliderEventHubSetOnChange)(RefPtr<FrameNode>& node, void* callback);
    void (*sliderPaintPropertyUpdateMin)(RefPtr<FrameNode>& node, float value);
    void (*sliderPaintPropertyUpdateMax)(RefPtr<FrameNode>& node, float value);
    void (*sliderPaintPropertyUpdateSelectGradientColor)(RefPtr<FrameNode>& node, uint32_t color);
    void (*sliderPaintPropertyUpdateSelectIsResourceColor)(RefPtr<FrameNode>& node, bool value);
    void (*sliderPaintPropertyUpdateTrackBackgroundColor)(RefPtr<FrameNode>& node, uint32_t color);
    void (*sliderPaintPropertyUpdateTrackBackgroundIsResourceColor)(RefPtr<FrameNode>& node, bool value);
    void (*sliderPaintPropertyUpdateValue)(RefPtr<FrameNode>& node, float value);
};
namespace CustomModifier {
const ArkUISliderCustomModifier* GetSliderCustomModifier();
} // namespace CustomModifier
} // OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_BRIDGE_SLIDER_CUSTOM_MODIFIER_H