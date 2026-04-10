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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_PEN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_PEN_H

#include <memory>

#include "testing_color.h"
#include "testing_enums.h"
#include "testing_filter.h"
#include "testing_path_effect.h"
#include "testing_shader_effect.h"

namespace OHOS::Ace::Testing {
class TestingPen {
public:
    enum class CapStyle {
        FLAT_CAP,
        SQUARE_CAP,
        ROUND_CAP,
    };

    enum class JoinStyle {
        MITER_JOIN,
        ROUND_JOIN,
        BEVEL_JOIN,
    };

    TestingPen() = default;
    ~TestingPen() = default;

    virtual void SetAntiAlias(bool aa) {}
    virtual void SetBlendMode(BlendMode mode) {}
    virtual void SetWidth(float width) {}
    virtual void SetCapStyle(CapStyle cap) {}
    virtual void SetColor(const TestingColor& color) {}
    virtual void SetColor(int color) {}
    virtual void SetFilter(const TestingFilter& filter) {}
    virtual void SetShaderEffect(std::shared_ptr<TestingShaderEffect> /* effect */) {}
    virtual void SetPathEffect(std::shared_ptr<TestingPathEffect> /* effect */) {}
    virtual void SetJoinStyle(JoinStyle js) {}
    virtual void SetMiterLimit(float limit) {}
    virtual void SetAlpha(uint32_t alpha) {}
    virtual void SetAlphaF(float alpha) {}
    virtual void Reset() {}
    virtual std::shared_ptr<TestingShaderEffect> GetShaderEffect()
    {
        return std::make_shared<TestingShaderEffect>();
    }

    virtual float GetWidth()
    {
        return .0f;
    }

    virtual TestingFilter GetFilter()
    {
        TestingFilter filter = {};
        return filter;
    }
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_PEN_H
