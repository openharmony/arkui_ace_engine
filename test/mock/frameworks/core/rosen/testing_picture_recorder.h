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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_PICTURE_RECORDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_PICTURE_RECORDER_H

#include <memory>
#include "testing_canvas.h"
#include "testing_picture.h"

namespace OHOS::Ace::Testing {
class TestingPictureRecorder {
public:
    TestingPictureRecorder() = default;
    ~TestingPictureRecorder() = default;
    /*
     *  @brief return the canvas that records the drawing commands.
     */
    std::shared_ptr<TestingCanvas> BeginRecording(float width, float height)
    {
        return std::make_shared<TestingCanvas>();
    }

    /*
     *  @brief Signal that the caller is done recording.
     */
    std::shared_ptr<TestingPicture> FinishRecordingAsPicture()
    {
        return std::make_shared<TestingPicture>();
    }
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_PICTURE_RECORDER_H
