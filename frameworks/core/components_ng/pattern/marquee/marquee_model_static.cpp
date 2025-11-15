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

#include "core/components_ng/pattern/marquee/marquee_model_static.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/marquee/marquee_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {


void MarqueeModelStatic::SetScrollAmount(FrameNode* frameNode, const std::optional<double>& scrollAmount)
{
    if (scrollAmount.has_value()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(MarqueePaintProperty, ScrollAmount, scrollAmount.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(MarqueePaintProperty, ScrollAmount, PROPERTY_UPDATE_RENDER, frameNode);
    }
}
}