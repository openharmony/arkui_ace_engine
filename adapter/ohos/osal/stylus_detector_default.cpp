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

#include "core/common/stylus/stylus_detector_default.h"

#include "base/utils/string_utils.h"
namespace OHOS::Ace {

namespace {
const int32_t MAX_COMMAND_INDEX = 5;
const int32_t MAX_PARAMS_SIZE = 3;
const int32_t PARAMS_ENABLE_INDEX = 2;
} // namespace
StylusDetectorDefault* StylusDetectorDefault::GetInstance()
{
    static StylusDetectorDefault instance;
    return &instance;
}

bool StylusDetectorDefault::IsEnable()
{
    return isEnable_;
}

bool StylusDetectorDefault::RegisterStylusInteractionListener(
    const std::string& bundleName, const std::shared_ptr<IStylusDetectorCallback>& callback)
{
    defaultCallback_ = std::move(callback);
    return true;
}

void StylusDetectorDefault::UnRegisterStylusInteractionListener(const std::string& bundleName)
{
    defaultCallback_ = nullptr;
}

bool StylusDetectorDefault::Notify(const NotifyInfo& notifyInfo)
{
    defaultNodeId_ = notifyInfo.componentId;
    LOGI("Stylus default notify receviecis (%{public}d, %{public}d). TargetNode id is %{public}d", notifyInfo.x,
        notifyInfo.y, notifyInfo.componentId);
    return true;
}

void StylusDetectorDefault::ExecuteCommand(const std::vector<std::string>& params)
{
    if (params.size() > MAX_PARAMS_SIZE || params.size() < PARAMS_ENABLE_INDEX) {
        return;
    }
    bool isEnable = true;
    auto commandId = StringUtils::StringToInt(params[1]);
    if (params.size() == MAX_PARAMS_SIZE) {
        isEnable = static_cast<bool>(StringUtils::StringToInt(params[PARAMS_ENABLE_INDEX]));
    }
    if (commandId < 0 || commandId >= MAX_COMMAND_INDEX) {
        return;
    }
    isEnable_ = isEnable;
    auto command = static_cast<CommandType>(commandId);
    if (defaultCallback_) {
        defaultCallback_->OnDetector(command, static_cast<void*>(&defaultText_), nullptr);
    }
}
} // namespace OHOS::Ace