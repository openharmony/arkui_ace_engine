/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components/panel/sliding_events.h"

namespace OHOS::Ace {

std::string SlidingPanelSizeChangeEvent::ToJSONString() const
{
    auto jsonResult = JsonUtil::Create(true);
    jsonResult->Put("height", height_);
    jsonResult->Put("width", width_);
    auto result = JsonUtil::Create(true);
    result->Put("size", jsonResult);
    std::string modeStr;
    if (mode_ == PanelMode::FULL) {
        modeStr = "full";
    } else if (mode_ == PanelMode::HALF) {
        modeStr = "half";
    } else {
        modeStr = "mini";
    }
    result->Put("mode", modeStr.c_str());

    return std::string(R"("sizechange",)").append(result->ToString());
}

} // namespace OHOS::Ace
