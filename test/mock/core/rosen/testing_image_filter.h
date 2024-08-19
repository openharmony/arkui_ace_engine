/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_IMAGE_FILTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_IMAGE_FILTER_H

#include <memory>

#include "base/geometry/rect.h"
#include "testing_color_filter.h"
#include "testing_enums.h"
#include "testing_image_blur_type.h"
#include "testing_rect.h"
#include "testing_shader_effect.h"

namespace OHOS::Ace::Testing {
static const TestingRect noCropRect(0.0, 0.0, 0.0, 0.0);
enum class FilterType {
    NO_TYPE,
    BLUR,
    COLOR,
    OFFSET,
    ARITHMETIC,
    COMPOSE,
};

class TestingImageFilter {
public:
    typedef float scalar;
    TestingImageFilter() = default;
    ~TestingImageFilter() = default;

    static std::shared_ptr<TestingImageFilter> CreateBlurImageFilter(
        float sigmaX, float sigmaY, TileMode mode, std::shared_ptr<TestingImageFilter> input,
        ImageBlurType imageBlurType = ImageBlurType::GAUSS, const TestingRect& filterRect = noCropRect)
    {
        return std::make_shared<TestingImageFilter>();
    }

    static std::shared_ptr<TestingImageFilter> CreateColorFilterImageFilter(
        const TestingColorFilter& cf, std::shared_ptr<TestingImageFilter> input)
    {
        return std::make_shared<TestingImageFilter>();
    }

    static std::shared_ptr<TestingImageFilter> CreateArithmeticImageFilter(const std::vector<scalar>& coefficients,
        bool enforcePMColor, std::shared_ptr<TestingImageFilter> background,
        std::shared_ptr<TestingImageFilter> foreground)
    {
        return std::make_shared<TestingImageFilter>();
    }

    static std::shared_ptr<TestingImageFilter> CreateOffsetImageFilter(
        scalar dx, scalar dy, std::shared_ptr<TestingImageFilter> input)
    {
        return std::make_shared<TestingImageFilter>();
    }

    static std::shared_ptr<TestingImageFilter> CreateBlendImageFilter(BlendMode mode,
        std::shared_ptr<TestingImageFilter> background, std::shared_ptr<TestingImageFilter> foreground = nullptr)
    {
        return std::make_shared<TestingImageFilter>();
    }

    static std::shared_ptr<TestingImageFilter> CreateShaderImageFilter(
        std::shared_ptr<TestingShaderEffect> shader, const Rect& rect = {})
    {
        return std::make_shared<TestingImageFilter>();
    }
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_IMAGE_FILTER_H
