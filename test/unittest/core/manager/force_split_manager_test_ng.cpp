/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <optional>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "base/utils/system_properties.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension TEST_WIDTH = 605.0_vp;

RefPtr<ForceSplitManager> GetForceSplitManager()
{
    auto pipeline = MockPipelineContext::GetCurrent();
    return pipeline ? pipeline->GetForceSplitManager() : nullptr;
}
} // namespace

class ForceSplitManagerTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void ForceSplitManagerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void ForceSplitManagerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: UpdateIsInForceSplitMode001
 * @tc.desc: Branch: if (!isForceSplitSupported_) { => true
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ForceSplitManagerTestNg, UpdateIsInForceSplitMode001, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    context->SetIsCurrentInForceSplitMode(false);
    manager->isForceSplitSupported_ = false;
    manager->UpdateIsInForceSplitMode(static_cast<int32_t>(TEST_WIDTH.ConvertToPx()));
    EXPECT_FALSE(context->IsCurrentInForceSplitMode());
}

/**
 * @tc.name: UpdateIsInForceSplitMode002
 * @tc.desc: Branch: if (!isForceSplitSupported_) { => false
 *                   if (isForceSplitEnable_) { => true
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ForceSplitManagerTestNg, UpdateIsInForceSplitMode002, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    auto windowManager = context->GetWindowManager();
    ASSERT_NE(windowManager, nullptr);

    EXPECT_CALL(*container, IsMainWindow).Times(::testing::AtLeast(1)).WillRepeatedly(Return(true));
    SystemProperties::orientation_ = DeviceOrientation::LANDSCAPE;
    auto backupCallback = std::move(windowManager->windowGetModeCallback_);
    windowManager->windowGetModeCallback_ = []() { return WindowMode::WINDOW_MODE_UNDEFINED; };
    context->SetIsCurrentInForceSplitMode(false);
    manager->isForceSplitSupported_ = true;
    manager->isForceSplitEnable_ = true;
    manager->UpdateIsInForceSplitMode(static_cast<int32_t>(TEST_WIDTH.ConvertToPx()));
    EXPECT_TRUE(context->IsCurrentInForceSplitMode());
    windowManager->windowGetModeCallback_ = std::move(backupCallback);
}

/**
 * @tc.name: UpdateIsInForceSplitMode003
 * @tc.desc: Branch: if (!isForceSplitSupported_) { => false
 *                   if (isForceSplitEnable_) { => false
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ForceSplitManagerTestNg, UpdateIsInForceSplitMode003, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    context->SetIsCurrentInForceSplitMode(false);
    manager->isForceSplitSupported_ = true;
    manager->isForceSplitEnable_ = false;
    manager->UpdateIsInForceSplitMode(static_cast<int32_t>(TEST_WIDTH.ConvertToPx()));
    EXPECT_FALSE(context->IsCurrentInForceSplitMode());
}

/**
 * @tc.name: GetIgnoreOrientation001
 * @tc.desc: Branch: if (SystemProperties::GetForceSplitIgnoreOrientationEnabled()) { => true
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ForceSplitManagerTestNg, GetIgnoreOrientation001, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    auto backupProperty = SystemProperties::forceSplitIgnoreOrientationEnabled_;
    SystemProperties::forceSplitIgnoreOrientationEnabled_ = true;
    auto ignore = manager->GetIgnoreOrientation();
    EXPECT_TRUE(ignore);
    SystemProperties::forceSplitIgnoreOrientationEnabled_ = backupProperty;
}

/**
 * @tc.name: GetIgnoreOrientation002
 * @tc.desc: Branch: if (SystemProperties::GetForceSplitIgnoreOrientationEnabled()) { => false
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ForceSplitManagerTestNg, GetIgnoreOrientation002, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto manager = GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    auto backupProperty = SystemProperties::forceSplitIgnoreOrientationEnabled_;
    SystemProperties::forceSplitIgnoreOrientationEnabled_ = false;
    manager->ignoreOrientation_ = false;
    auto ignore = manager->GetIgnoreOrientation();
    EXPECT_FALSE(ignore);

    manager->ignoreOrientation_ = true;
    ignore = manager->GetIgnoreOrientation();
    EXPECT_TRUE(ignore);

    SystemProperties::forceSplitIgnoreOrientationEnabled_ = backupProperty;
}
} // namespace OHOS::Ace::NG
