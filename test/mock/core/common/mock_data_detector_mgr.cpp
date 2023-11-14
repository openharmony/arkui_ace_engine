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

#include "core/common/ai/data_detector_mgr.h"
namespace OHOS::Ace {
DataDetectorMgr& DataDetectorMgr::GetInstance()
{
    static DataDetectorMgr instance;
    return instance;
}

DataDetectorMgr::DataDetectorMgr() {}

bool DataDetectorMgr::IsDataDetectorSupported()
{
    return false;
}

void DataDetectorMgr::DataDetect(const TextDataDetectInfo& info, const TextDetectResultFunc& func) {}

RefPtr<NG::FrameNode> DataDetectorMgr::CreateUIExtensionMenu(
    const std::map<std::string, std::string>& paramaters, std::function<void(const std::string&)> onClickMenu)
{
    return nullptr;
}

bool DataDetectorMgr::ShowUIExtensionMenu(const std::map<std::string, std::string>& paramaters, NG::RectF safeArea,
    std::function<void(const std::string&)> onClickMenu, std::vector<std::string> aiMenuOptions,
    const RefPtr<NG::FrameNode>& targetNode)
{
    return false;
}
} // namespace OHOS::Ace
