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
#include "test/mock/core/common/mock_data_detector_mgr.h"
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
    std::function<void(const std::string&)> onClickMenu, const RefPtr<NG::FrameNode>& targetNode)
{
    return true;
}

void DataDetectorMgr::ResponseBestMatchItem(const std::map<std::string, std::string>& paramaters, const AISpan& aiSpan)
{}

std::function<void(const AAFwk::WantParams&)> DataDetectorMgr::GetOnReceive(
    const RefPtr<NG::FrameNode>& uiExtNode, NG::RectF aiRect,
    std::function<void(const std::string&)> onClickMenu, const RefPtr<NG::FrameNode>& targetNode)
{
    return [](const AAFwk::WantParams& wantParams) {};
}

void DataDetectorMgr::AdjustCursorPosition(
    int32_t& caretPos, const std::string& content, TimeStamp& lastAiPosTimeStamp, const TimeStamp& lastClickTimeStamp)
{
    caretPos = GetCursorPosition(content, caretPos);
}

void DataDetectorMgr::AdjustWordSelection(int32_t& caretPos, const std::string& content, int32_t& start, int32_t& end)
{
    auto ret = GetWordSelection(content, caretPos);
    start = ret[0];
    end = ret[1];
}

std::vector<int8_t> DataDetectorMgr::GetWordSelection(const std::string& text, int8_t offset)
{
    return std::vector<int8_t> { -1, -1 };
}

int8_t DataDetectorMgr::GetCursorPosition(const std::string& text, int8_t offset)
{
    return -1;
}
} // namespace OHOS::Ace
