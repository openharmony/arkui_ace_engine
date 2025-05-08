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

#include "web_ani_modifier.h"

#include "base/log/log.h"
#include "core/components_ng/base/frame_node.h"
#ifdef WEB_SUPPORTED
#include "core/components_ng/pattern/web/web_model_ng.h"
#endif

namespace OHOS::Ace::NG {

void SetWebOptions(ArkUINodeHandle node,
    std::function<void(int32_t)>&& onNWebId,
    std::function<void(const std::string&)>&& onHapPath)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    WebModelNG::SetWebIdCallback(frameNode, std::move(onNWebId));
    WebModelNG::SetHapPathCallback(frameNode, std::move(onHapPath));
#endif // WEB_SUPPORTED
}

const ArkUIAniWebModifier* GetWebAniModifier()
{
    static const ArkUIAniWebModifier impl = {
        .setWebOptions = OHOS::Ace::NG::SetWebOptions
    };
    return &impl;
}

} // namespace OHOS::Ace::NG