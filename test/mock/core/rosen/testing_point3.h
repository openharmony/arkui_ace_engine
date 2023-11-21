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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_POINT3_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_POINT3_H

namespace OHOS::Ace::Testing {
class TestingPoint3 {
public:
    TestingPoint3() = default;
    virtual ~TestingPoint3() = default;

    TestingPoint3(const TestingPoint3& point) : x_(point.x_), y_(point.y_), z_(point.z_) {}

    TestingPoint3(float xP, float yP, float zP) : x_(xP), y_(yP), z_(zP) {}

    virtual float GetX() const
    {
        return x_;
    }

    virtual float GetY() const
    {
        return y_;
    }

    virtual float GetZ() const
    {
        return z_;
    }

    virtual void SetX(float xP)
    {
        x_ = xP;
    }

    virtual void SetY(float yP)
    {
        y_ = yP;
    }

    virtual void SetZ(float zP)
    {
        z_ = zP;
    }

private:
    float x_ = 0.0f;
    float y_ = 0.0f;
    float z_ = 0.0f;
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_POINT3H