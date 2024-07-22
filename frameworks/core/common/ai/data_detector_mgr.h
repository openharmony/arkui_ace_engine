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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_DATA_DETECTOR_MGR_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_DATA_DETECTOR_MGR_H

#include "data_detector_loader.h"

#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace {
class ACE_EXPORT DataDetectorMgr : public DataDetectorInterface {
public:
    static DataDetectorMgr& GetInstance();

    bool IsDataDetectorSupported() override;
    void GetAIEntityMenu(TextDataDetectResult& textDataDetectResult) override;
    void DataDetect(const TextDataDetectInfo& info, const TextDetectResultFunc& resultFunc) override;

    void AdjustCursorPosition(int32_t& caretPos, const std::string& content, TimeStamp& lastAiPosTimeStamp,
        const TimeStamp& lastClickTimeStamp);
    void AdjustWordSelection(int32_t& caretPos, const std::string& content, int32_t& start, int32_t& end);

    int8_t GetCursorPosition(const std::string& text, int8_t offset) override;
    std::vector<int8_t> GetWordSelection(const std::string& text, int8_t offset) override;

protected:
    ~DataDetectorMgr() = default;

private:
    DataDetectorMgr();
    DataDetectorInstance engine_ = nullptr;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_DATA_DETECTOR_MGR_H
