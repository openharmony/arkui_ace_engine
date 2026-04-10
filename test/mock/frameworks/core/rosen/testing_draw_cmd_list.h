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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_DRAW_CMD_LIST_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_DRAW_CMD_LIST_H

#include <cstdint>

#include "testing_canvas.h"
#include "testing_rect.h"
namespace OHOS::Ace::Testing {
enum class TestingHybridRenderType : uint32_t {
    NONE,
    TEXT,
    SVG,
    HMSYMBOL,
    CANVAS,
    TYPE_MAX
};

class TestingDrawCmdList {
public:
    TestingDrawCmdList() = default;
    virtual ~TestingDrawCmdList() = default;

    int32_t GetWidth() const
    {
        return width_;
    }

    int32_t GetHeight() const
    {
        return height_;
    }

    void SetWidth(int32_t width)
    {
        width_ = width;
    }

    void SetHeight(int32_t height)
    {
        height_ = height;
    }

    bool IsEmpty() const
    {
        return false;
    }

    size_t GetOpItemSize() const
    {
        return 0;
    }

    void Playback(TestingCanvas& canvas, const TestingRect* rect = nullptr) {}

    void SetHybridRenderType(Testing::TestingHybridRenderType HybridRenderType) {}

private:
    int32_t width_ = 0;
    int32_t height_ = 0;
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_DRAW_CMD_LIST_H
