/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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

#include "core/common/ai/data_detector_default.h"

namespace OHOS::Ace {

DataDetectorMgr& DataDetectorMgr::GetInstance()
{
    static DataDetectorMgr instance;
    return instance;
}

DataDetectorMgr::DataDetectorMgr()
{
    auto lib = DataDetectorLoader::Load();
    if (lib == nullptr || (engine_ = lib->CreateDataDetector()) == nullptr) {
        engine_ = DataDetectorInstance(new DataDetectorDefault, [](DataDetectorInterface* e) {
            auto* p = reinterpret_cast<DataDetectorDefault*>(e);
            delete p;
        });
    }
}

bool DataDetectorMgr::IsDataDetectorSupported()
{
    if (engine_) {
        return engine_->IsDataDetectorSupported();
    }
    return false;
}

void DataDetectorMgr::GetAIEntityMenu(TextDataDetectResult& textDataDetectResult)
{
    if (engine_) {
        engine_->GetAIEntityMenu(textDataDetectResult);
    }
}

void DataDetectorMgr::DataDetect(const TextDataDetectInfo& info, const TextDetectResultFunc& resultFunc)
{
    if (!IsDataDetectorSupported()) {
        TextDataDetectResult result;
        result.code = UNSUPPORTED_CODE;
        resultFunc(result);
        return;
    }
    if (engine_) {
        engine_->DataDetect(info, resultFunc);
    }
}

void DataDetectorMgr::AdjustCursorPosition(
    int32_t& caretPos, const std::string& content, TimeStamp& lastAiPosTimeStamp, const TimeStamp& lastClickTimeStamp)
{
    if (engine_) {
        int32_t aiPos = GetCursorPosition(content, caretPos);
        TAG_LOGI(AceLogTag::ACE_TEXTINPUT, "TryGetAiCursorPosition,aiPos is %{public}d", aiPos);

        if (aiPos < 0) {
            return;
        }
        // aiPos should above zero;
        caretPos = aiPos;
        // record the ai position time
        lastAiPosTimeStamp = lastClickTimeStamp;
    }
}

void DataDetectorMgr::AdjustWordSelection(int32_t& caretPos, const std::string& content, int32_t& start, int32_t& end)
{
    if (engine_) {
        std::vector<int8_t> ret = GetWordSelection(content, caretPos);
        start = ret[0];
        end = ret[1];

        TAG_LOGI(AceLogTag::ACE_TEXTINPUT, "get ai selection:%{public}d--%{public}d", start, end);
        if (start < 0 || end < 0) {
            return;
        }
        caretPos = start;
    }
}

std::vector<int8_t> DataDetectorMgr::GetWordSelection(const std::string& text, int8_t offset)
{
    if (engine_) {
        return engine_->GetWordSelection(text, offset);
    }

    return std::vector<int8_t> { -1, -1 };
}

int8_t DataDetectorMgr::GetCursorPosition(const std::string& text, int8_t offset)
{
    if (engine_) {
        return engine_->GetCursorPosition(text, offset);
    }

    return -1;
}
} // namespace OHOS::Ace
