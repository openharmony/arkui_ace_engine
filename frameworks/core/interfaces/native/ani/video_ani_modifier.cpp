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

#include "video_ani_modifier.h"

#include "base/log/log.h"
#include "base/json/json_util.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/video/video_model_static.h"

namespace OHOS::Ace::NG {

void SetVideoOnError(ArkUINodeHandle node, std::function<void(const std::string&)>&& onError)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(onError);
    VideoModelStatic::SetOnError(frameNode, std::move(onError));
}

void ParseVideoError(const std::string& jsonStr, int32_t& code, std::string& message)
{
    auto data = JsonUtil::ParseJsonString(jsonStr);
    CHECK_NULL_VOID(data);
    auto codeVal = data->GetValue("code");
    auto messageVal = data->GetValue("message");
    CHECK_NULL_VOID(codeVal);
    CHECK_NULL_VOID(messageVal);
    code = codeVal->GetInt();
    message = messageVal->GetString();
}

const ArkUIAniVideoModifier* GetVideoAniModifier()
{
    static const ArkUIAniVideoModifier impl = {
        .setOnError = OHOS::Ace::NG::SetVideoOnError,
        .parseVideoError = OHOS::Ace::NG::ParseVideoError,
    };
    return &impl;
}

} // namespace OHOS::Ace::NG
