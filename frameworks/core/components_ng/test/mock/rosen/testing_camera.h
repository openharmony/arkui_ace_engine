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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_CAMERA_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_CAMERA_H

#include "testing_matrix.h"

namespace OHOS::Ace::Testing {
class TestingCamera {
public:
    TestingCamera() = default;
    ~TestingCamera() = default;

    virtual void Save() {}
    virtual void Restore() {}

    virtual void Translate(float xs, float ys, float zs) {}
    virtual void RotateXDegrees(float deg) {}
    virtual void RotateYDegrees(float deg) {}
    virtual void RotateZDegrees(float deg) {}

    virtual void SetCameraPos(float xPos, float yPos, float zPos) {}

    virtual float GetCameraPosX() const
    {
        return 1.0f;
    }

    virtual float GetCameraPosY() const
    {
        return 1.0f;
    }

    virtual float GetCameraPosZ() const
    {
        return 1.0f;
    }

    virtual void ApplyToMatrix(TestingMatrix& matrix) {}
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_CAMERA_H
