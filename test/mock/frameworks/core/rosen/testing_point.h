/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_POINT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_POINT_H

namespace OHOS::Ace::Testing {
class TestingPoint {
public:
    TestingPoint() = default;
    virtual ~TestingPoint() = default;

    TestingPoint(const TestingPoint& point) : x_(point.x_), y_(point.y_) {}

    TestingPoint(float xP, float yP) : x_(xP), y_(yP) {}

    virtual float GetX() const
    {
        return x_;
    }

    virtual float GetY() const
    {
        return y_;
    }

    virtual void SetX(float xP)
    {
        x_ = xP;
    }

    virtual void SetY(float yP)
    {
        y_ = yP;
    }

    virtual TestingPoint& operator+=(const TestingPoint& /* other */)
    {
        return *this;
    }

    virtual TestingPoint& operator-=(const TestingPoint& /* other */)
    {
        return *this;
    }

    virtual TestingPoint& operator*=(float /* scale */)
    {
        return *this;
    }

    virtual TestingPoint& operator/=(float /* divisor */)
    {
        return *this;
    }

    friend bool operator==(const TestingPoint& p1, const TestingPoint& p2)
    {
        return false;
    }

private:
    float x_;
    float y_;
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_POINT_H
