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
#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_MOCK_DATA_DETECTOR_MGR_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_MOCK_DATA_DETECTOR_MGR_H

#include "core/common/ai/data_detector_mgr.h"
#include "gmock/gmock.h"
namespace OHOS::Ace {
class ACE_EXPORT MockDataDetectorMgr : public DataDetectorMgr {
public:
    MOCK_METHOD2(GetCursorPosition,  int8_t (const std::string& text, int8_t offset));
    MOCK_METHOD2(GetWordSelection,  std::vector<int8_t> (const std::string& text, int8_t offset));
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_MOCK_DATA_DETECTOR_MGR_H
