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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_RECT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_RECT_H

namespace OHOS::Ace::Testing {
class TestingRect {
public:
    TestingRect() = default;
    virtual ~TestingRect() = default;

    TestingRect(const TestingRect& rect) = default;

    TestingRect(const float left, const float top, const float right, const float bottom)
        : left_(left), right_(right), top_(top), bottom_(bottom)
    {}

    virtual bool IsValid() const
    {
        return true;
    }

    virtual float GetLeft() const
    {
        return left_;
    }

    virtual float GetTop() const
    {
        return top_;
    }

    virtual float GetRight() const
    {
        return right_;
    }

    virtual float GetBottom() const
    {
        return bottom_;
    }

    virtual float GetWidth() const
    {
        return left_ - right_;
    }

    virtual float GetHeight() const
    {
        return bottom_ - top_;
    }

    virtual void SetLeft(float pos) {}
    virtual void SetTop(float pos) {}
    virtual void SetRight(float pos) {}
    virtual void SetBottom(float pos) {}
    virtual void Offset(float dx, float dy) {}

    bool Join(const TestingRect& other)
    {
        return true;
    }

private:
    float left_;
    float right_;
    float top_;
    float bottom_;
};

} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_RECT_H
