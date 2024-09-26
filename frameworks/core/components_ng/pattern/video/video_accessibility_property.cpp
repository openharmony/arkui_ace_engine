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

#include "core/components_ng/pattern/video/video_accessibility_property.h"

#include "core/components_ng/pattern/video/video_full_screen_node.h"
#include "core/components_ng/pattern/video/video_full_screen_pattern.h"

namespace OHOS::Ace::NG {
std::string VideoAccessibilityProperty::GetText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto videoLayoutProperty = frameNode->GetLayoutProperty<VideoLayoutProperty>();
    CHECK_NULL_RETURN(videoLayoutProperty, "");
    return videoLayoutProperty->GetVideoSourceValue(VideoSourceInfo()).GetSrc();
}

AccessibilityValue VideoAccessibilityProperty::GetAccessibilityValue() const
{
    AccessibilityValue result;
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, result);
    auto pattern = frameNode->GetPattern<VideoPattern>();
    CHECK_NULL_RETURN(pattern, result);
    if (pattern->IsFullScreen()) {
        auto fullScreenNode = AceType::DynamicCast<VideoFullScreenNode>(pattern->GetFullScreenNode());
        CHECK_NULL_RETURN(fullScreenNode, result);
        auto fullScreenPattern = AceType::DynamicCast<VideoFullScreenPattern>(fullScreenNode->GetPattern());
        CHECK_NULL_RETURN(fullScreenNode, result);
        result.max = fullScreenPattern->GetDuration();
        result.current = fullScreenPattern->GetCurrentPos();
        return result;
    }
    result.max = pattern->GetDuration();
    result.current = pattern->GetCurrentPos();
    return result;
}
} // namespace OHOS::Ace::NG
