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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_RECORDING_CANVAS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_RECORDING_CANVAS_H

#include <memory>

#include "test/mock/core/rosen/testing_draw_cmd_list.h"
namespace OHOS::Ace::Testing {
class TestingRecordingCanvas : public TestingCanvas {
public:
    TestingRecordingCanvas() = default;
    TestingRecordingCanvas(int32_t width, int32_t weight, bool addDrawOpImmediate = true) {}
    ~TestingRecordingCanvas() = default;
    std::shared_ptr<TestingDrawCmdList> GetDrawCmdList() const
    {
        return nullptr;
    }

    void Clear() const {}

    void SetIsCustomTextType(bool isCustomTextType)
    {
        isCustomTextType_ = isCustomTextType;
    }

private:
    bool isCustomTextType_ = false;
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_RECORDING_CANVAS_H
