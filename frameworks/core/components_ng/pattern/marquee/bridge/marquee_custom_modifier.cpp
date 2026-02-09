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

#include "core/components_ng/pattern/marquee/bridge/marquee_custom_modifier.h"

#include "core/components_ng/pattern/marquee/marquee_model_ng.h"

namespace OHOS::Ace::NG {

void SetMarqueeFrameRateRange(FrameNode* frameNode, const RefPtr<FrameRateRange>& rateRange,
    MarqueeDynamicSyncSceneType type)
{
    MarqueeModelNG::SetMarqueeFrameRateRange(frameNode, rateRange, type);
}

namespace CustomModifier {
const ArkUIMarqueeCustomModifier* GetMarqueeCustomModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIMarqueeCustomModifier modifier = {
        .setMarqueeFrameRateRange = SetMarqueeFrameRateRange,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace CustomModifier
} // namespace OHOS::Ace::NG
