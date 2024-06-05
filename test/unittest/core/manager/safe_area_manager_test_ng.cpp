/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

namespace {
constexpr double DISPLAY_WIDTH = 720;
constexpr double DISPLAY_HEIGHT = 1280;
constexpr double CUTOUT_LEFT_START = 10.0f;
constexpr double CUTOUT_LEFT_END = 30.0f;
constexpr double CUTOUT_RIGHT_START = DISPLAY_WIDTH - 30.0f;
constexpr double CUTOUT_RIGHT_END = DISPLAY_WIDTH - 10.0f;
constexpr double CUTOUT_TOP_START = 20.0f;
constexpr double CUTOUT_TOP_END = 40.0f;
constexpr double CUTOUT_BOTTOM_START = DISPLAY_HEIGHT - 40.0f;
constexpr double CUTOUT_BOTTOM_END = DISPLAY_HEIGHT - 20.0f;
} // namespace

class SafeAreaManagerTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void SafeAreaManagerTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void SafeAreaManagerTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: UpdateCutoutTest
 * @tc.desc: Use UpdateCutoutSafeArea and test.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, UpdateCutoutTest, TestSize.Level1)
{
    /**
     * @tc.steps: call UpdateCutoutSafeArea
     * @tc.expected: cutout regions need to adjacent to edges.
     */

    NG::SafeAreaInsets cutoutArea =
        NG::SafeAreaInsets({ CUTOUT_LEFT_START, CUTOUT_LEFT_END }, { CUTOUT_TOP_START, CUTOUT_TOP_END },
            { CUTOUT_RIGHT_START, CUTOUT_RIGHT_END }, { CUTOUT_BOTTOM_START, CUTOUT_BOTTOM_END });

    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->SetIsLayoutFullScreen(true);
    pipeline->UpdateCutoutSafeArea(cutoutArea);
    auto safeArea = pipeline->GetSafeArea();

    EXPECT_EQ(safeArea.left_.start, 0.0f);
    EXPECT_EQ(safeArea.right_.end, DISPLAY_WIDTH);
    EXPECT_EQ(safeArea.top_.start, 0.0f);
    EXPECT_EQ(safeArea.bottom_.end, DISPLAY_HEIGHT);
}
} // namespace OHOS::Ace::NG