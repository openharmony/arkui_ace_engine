/*
 * Copyright (c) 2022-2026 Huawei Device Co., Ltd.
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

#include <mutex>
#include <vector>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_default.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/components_ng/pattern/mock_picker_haptic_impl.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "adapter/ohos/entrance/picker/picker_haptic_factory.h"
#include "base/json/json_util.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/picker/picker_theme.h"
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

class DatePickerWindowFullscreenTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void DatePickerWindowFullscreenTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DatePickerWindowFullscreenTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void DatePickerWindowFullscreenTest::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
            if (type == PickerTheme::TypeId()) {
                return MockThemeDefault::GetPickerTheme();
            }
            return nullptr;
        });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> {
            if (type == PickerTheme::TypeId()) {
                return MockThemeDefault::GetPickerTheme();
            }
            return nullptr;
        });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void DatePickerWindowFullscreenTest::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: DatePickerIsWindowFullscreen001
 * @tc.desc: Test IsWindowFullscreen returns false by default
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerWindowFullscreenTest, DatePickerIsWindowFullscreen001, TestSize.Level1)
{
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    ASSERT_NE(datePickerNode, nullptr);

    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);

    bool isFullscreen = datePickerPattern->IsWindowFullscreen();
    EXPECT_TRUE(isFullscreen);
}

/**
 * @tc.name: DatePickerOnWindowSizeChanged001
 * @tc.desc: Test OnWindowSizeChanged with SPLIT_TO_FULL reason
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerWindowFullscreenTest, DatePickerOnWindowSizeChanged001, TestSize.Level1)
{
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    ASSERT_NE(datePickerNode, nullptr);

    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);

    EXPECT_TRUE(datePickerPattern->IsWindowFullscreen());

    datePickerPattern->OnWindowSizeChanged(TEST_WIDTH, TEST_HEIGHT, WindowSizeChangeReason::SPLIT_TO_FULL);

    EXPECT_TRUE(datePickerPattern->IsWindowFullscreen());
}

/**
 * @tc.name: DatePickerOnWindowSizeChanged002
 * @tc.desc: Test OnWindowSizeChanged with FLOATING_TO_FULL reason
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerWindowFullscreenTest, DatePickerOnWindowSizeChanged002, TestSize.Level1)
{
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    ASSERT_NE(datePickerNode, nullptr);

    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);

    EXPECT_TRUE(datePickerPattern->IsWindowFullscreen());

    datePickerPattern->OnWindowSizeChanged(TEST_WIDTH, TEST_HEIGHT, WindowSizeChangeReason::FLOATING_TO_FULL);

    EXPECT_TRUE(datePickerPattern->IsWindowFullscreen());
}

/**
 * @tc.name: DatePickerOnWindowSizeChanged003
 * @tc.desc: Test OnWindowSizeChanged with FULL_TO_SPLIT reason
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerWindowFullscreenTest, DatePickerOnWindowSizeChanged003, TestSize.Level1)
{
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    ASSERT_NE(datePickerNode, nullptr);

    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);

    datePickerPattern->OnWindowSizeChanged(TEST_WIDTH, TEST_HEIGHT, WindowSizeChangeReason::SPLIT_TO_FULL);
    EXPECT_TRUE(datePickerPattern->IsWindowFullscreen());

    datePickerPattern->OnWindowSizeChanged(TEST_WIDTH, TEST_HEIGHT, WindowSizeChangeReason::FULL_TO_SPLIT);

    EXPECT_FALSE(datePickerPattern->IsWindowFullscreen());
}

/**
 * @tc.name: DatePickerOnWindowSizeChanged004
 * @tc.desc: Test OnWindowSizeChanged with FULL_TO_FLOATING reason
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerWindowFullscreenTest, DatePickerOnWindowSizeChanged004, TestSize.Level1)
{
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    ASSERT_NE(datePickerNode, nullptr);

    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);

    datePickerPattern->OnWindowSizeChanged(TEST_WIDTH, TEST_HEIGHT, WindowSizeChangeReason::FLOATING_TO_FULL);
    EXPECT_TRUE(datePickerPattern->IsWindowFullscreen());

    datePickerPattern->OnWindowSizeChanged(TEST_WIDTH, TEST_HEIGHT, WindowSizeChangeReason::FULL_TO_FLOATING);

    EXPECT_FALSE(datePickerPattern->IsWindowFullscreen());
}

/**
 * @tc.name: DatePickerOnWindowSizeChanged005
 * @tc.desc: Test OnWindowSizeChanged with default reason (no change)
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerWindowFullscreenTest, DatePickerOnWindowSizeChanged005, TestSize.Level1)
{
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    ASSERT_NE(datePickerNode, nullptr);

    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);

    EXPECT_TRUE(datePickerPattern->IsWindowFullscreen());

    datePickerPattern->OnWindowSizeChanged(TEST_WIDTH, TEST_HEIGHT, WindowSizeChangeReason::UNDEFINED);

    EXPECT_TRUE(datePickerPattern->IsWindowFullscreen());
}

/**
 * @tc.name: DatePickerOnWindowSizeChanged006
 * @tc.desc: Test OnWindowSizeChanged with ROTATION reason (no change)
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerWindowFullscreenTest, DatePickerOnWindowSizeChanged006, TestSize.Level1)
{
    auto datePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    ASSERT_NE(datePickerNode, nullptr);

    auto datePickerPattern = datePickerNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);

    EXPECT_TRUE(datePickerPattern->IsWindowFullscreen());

    datePickerPattern->OnWindowSizeChanged(TEST_WIDTH, TEST_HEIGHT, WindowSizeChangeReason::ROTATION);

    EXPECT_TRUE(datePickerPattern->IsWindowFullscreen());
}

} // namespace OHOS::Ace::NG
