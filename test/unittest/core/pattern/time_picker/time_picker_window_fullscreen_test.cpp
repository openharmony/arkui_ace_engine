/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

#include <cstdint>
#include <functional>
#include <optional>
#include <utility>

#include "gtest/gtest-message.h"
#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_default.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components/theme/icon_theme.h"
#include "core/components/button/button_theme.h"
#include "core/components/dialog/dialog_theme.h"

#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr int32_t TEST_WIDTH = 800;
constexpr int32_t TEST_HEIGHT = 600;
} // namespace

class TimePickerWindowFullscreenTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;

    RefPtr<Theme> GetThemeByType(ThemeType type);

    RefPtr<IconTheme> iconThem_;
    RefPtr<DialogTheme> dialogTheme_;
    RefPtr<PickerTheme> pickerThem_;
    RefPtr<ButtonTheme> buttonTheme_;
};

void TimePickerWindowFullscreenTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void TimePickerWindowFullscreenTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TimePickerWindowFullscreenTest::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly([this](ThemeType type) -> RefPtr<Theme> { return GetThemeByType(type); });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([this](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> {
            return GetThemeByType(type);
        });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TimePickerWindowFullscreenTest::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

RefPtr<Theme> TimePickerWindowFullscreenTest::GetThemeByType(ThemeType type)
{
    if (type == IconTheme::TypeId()) {
        return AceType::MakeRefPtr<IconTheme>();
    } else if (type == DialogTheme::TypeId()) {
        return AceType::MakeRefPtr<DialogTheme>();
    } else if (type == PickerTheme::TypeId()) {
        return MockThemeDefault::GetPickerTheme();
    } else if (type == ButtonTheme::TypeId()) {
        return AceType::MakeRefPtr<ButtonTheme>();
    } else {
        return nullptr;
    }
}

/**
 * @tc.name: TimePickerIsWindowFullscreen001
 * @tc.desc: Test IsWindowFullscreen returns false by default
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerWindowFullscreenTest, TimePickerIsWindowTimeFullscreen001, TestSize.Level1)
{
    auto timePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TIME_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TimePickerRowPattern>(); });
    ASSERT_NE(timePickerNode, nullptr);

    auto timePickerPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerPattern, nullptr);

    bool isFullscreen = timePickerPattern->IsWindowFullscreen();
    EXPECT_TRUE(isFullscreen);
}

/**
 * @tc.name: TimePickerOnWindowSizeChanged001
 * @tc.desc: Test OnWindowSizeChanged with SPLIT_TO_FULL reason
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerWindowFullscreenTest, TimePickerOnWindowSizeChanged001, TestSize.Level1)
{
    auto timePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TIME_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TimePickerRowPattern>(); });
    ASSERT_NE(timePickerNode, nullptr);

    auto timePickerPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerPattern, nullptr);

    EXPECT_TRUE(timePickerPattern->IsWindowFullscreen());

    timePickerPattern->OnWindowSizeChanged(TEST_WIDTH, TEST_HEIGHT, WindowSizeChangeReason::SPLIT_TO_FULL);

    EXPECT_TRUE(timePickerPattern->IsWindowFullscreen());
}

/**
 * @tc.name: TimePickerOnWindowSizeChanged002
 * @tc.desc: Test OnWindowSizeChanged with FLOATING_TO_FULL reason
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerWindowFullscreenTest, TimePickerOnWindowSizeChanged002, TestSize.Level1)
{
    auto timePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TIME_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TimePickerRowPattern>(); });
    ASSERT_NE(timePickerNode, nullptr);

    auto timePickerPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerPattern, nullptr);

    EXPECT_TRUE(timePickerPattern->IsWindowFullscreen());

    timePickerPattern->OnWindowSizeChanged(TEST_WIDTH, TEST_HEIGHT, WindowSizeChangeReason::FLOATING_TO_FULL);

    EXPECT_TRUE(timePickerPattern->IsWindowFullscreen());
}

/**
 * @tc.name: TimePickerOnWindowSizeChanged003
 * @tc.desc: Test OnWindowSizeChanged with FULL_TO_SPLIT reason
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerWindowFullscreenTest, TimePickerOnWindowSizeChanged003, TestSize.Level1)
{
    auto timePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TIME_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TimePickerRowPattern>(); });
    ASSERT_NE(timePickerNode, nullptr);

    auto timePickerPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerPattern, nullptr);

    timePickerPattern->OnWindowSizeChanged(TEST_WIDTH, TEST_HEIGHT, WindowSizeChangeReason::SPLIT_TO_FULL);
    EXPECT_TRUE(timePickerPattern->IsWindowFullscreen());

    timePickerPattern->OnWindowSizeChanged(TEST_WIDTH, TEST_HEIGHT, WindowSizeChangeReason::FULL_TO_SPLIT);

    EXPECT_FALSE(timePickerPattern->IsWindowFullscreen());
}

/**
 * @tc.name: TimePickerOnWindowSizeChanged004
 * @tc.desc: Test OnWindowSizeChanged with FULL_TO_FLOATING reason
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerWindowFullscreenTest, TimePickerOnWindowSizeChanged004, TestSize.Level1)
{
    auto timePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TIME_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TimePickerRowPattern>(); });
    ASSERT_NE(timePickerNode, nullptr);

    auto timePickerPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerPattern, nullptr);

    timePickerPattern->OnWindowSizeChanged(TEST_WIDTH, TEST_HEIGHT, WindowSizeChangeReason::FLOATING_TO_FULL);
    EXPECT_TRUE(timePickerPattern->IsWindowFullscreen());

    timePickerPattern->OnWindowSizeChanged(TEST_WIDTH, TEST_HEIGHT, WindowSizeChangeReason::FULL_TO_FLOATING);

    EXPECT_FALSE(timePickerPattern->IsWindowFullscreen());
}

/**
 * @tc.name: TimePickerOnWindowSizeChanged005
 * @tc.desc: Test OnWindowSizeChanged with default reason (no change)
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerWindowFullscreenTest, TimePickerOnWindowSizeChanged005, TestSize.Level1)
{
    auto timePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TIME_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TimePickerRowPattern>(); });
    ASSERT_NE(timePickerNode, nullptr);

    auto timePickerPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerPattern, nullptr);

    EXPECT_TRUE(timePickerPattern->IsWindowFullscreen());

    timePickerPattern->OnWindowSizeChanged(TEST_WIDTH, TEST_HEIGHT, WindowSizeChangeReason::UNDEFINED);

    EXPECT_TRUE(timePickerPattern->IsWindowFullscreen());
}

/**
 * @tc.name: TimePickerOnWindowSizeChanged006
 * @tc.desc: Test OnWindowSizeChanged with ROTATION reason (no change)
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerWindowFullscreenTest, TimePickerOnWindowSizeChanged006, TestSize.Level1)
{
    auto timePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TIME_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TimePickerRowPattern>(); });
    ASSERT_NE(timePickerNode, nullptr);

    auto timePickerPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerPattern, nullptr);

    EXPECT_TRUE(timePickerPattern->IsWindowFullscreen());

    timePickerPattern->OnWindowSizeChanged(TEST_WIDTH, TEST_HEIGHT, WindowSizeChangeReason::ROTATION);

    EXPECT_TRUE(timePickerPattern->IsWindowFullscreen());
}

} // namespace OHOS::Ace::NG
