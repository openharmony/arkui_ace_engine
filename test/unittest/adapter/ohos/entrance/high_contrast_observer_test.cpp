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

#include "gtest/gtest.h"
#include "adapter/ohos/entrance/high_contrast_observer.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Platform;

namespace OHOS::Ace::NG {
class HighContrastObserverTest : public testing::Test {
public:
    void SetUp() override {};
    void TearDown() override {};
};

/**
 * @tc.name: OnConfigChanged001
 * @tc.desc: Test OnConfigChanged with first_ is true
 * @tc.type: FUNC
 * @tc.require: issueICK0X0
 */
HWTEST_F(HighContrastObserverTest, OnConfigChanged001, TestSize.Level1)
{
    auto highContrastObserver = std::make_shared<HighContrastObserver>(nullptr);
    highContrastObserver->first_ = true;
    AccessibilityConfig::ConfigValue value;
    highContrastObserver->OnConfigChanged(AccessibilityConfig::CONFIG_ID::CONFIG_HIGH_CONTRAST_TEXT, value);
    EXPECT_FALSE(highContrastObserver->first_);
}

/**
 * @tc.name: OnConfigChanged002
 * @tc.desc: Test OnConfigChanged with AceContainer is nullptr
 * @tc.type: FUNC
 * @tc.require: issueICK0X0
 */
HWTEST_F(HighContrastObserverTest, OnConfigChanged002, TestSize.Level1)
{
    auto highContrastObserver = std::make_shared<HighContrastObserver>(nullptr);
    highContrastObserver->first_ = false;
    AccessibilityConfig::ConfigValue value;
    highContrastObserver->OnConfigChanged(AccessibilityConfig::CONFIG_ID::CONFIG_HIGH_CONTRAST_TEXT, value);
    EXPECT_FALSE(highContrastObserver->first_);
}

/**
 * @tc.name: OnConfigChanged003
 * @tc.desc: Test OnConfigChanged with pipelineContext is nullptr
 * @tc.type: FUNC
 * @tc.require: issueICK0X0
 */
HWTEST_F(HighContrastObserverTest, OnConfigChanged003, TestSize.Level1)
{
    int32_t instanceId = 1;
    auto container = AceContainer::GetContainer(instanceId);
    EXPECT_NE(container, nullptr);
    auto highContrastObserver = std::make_shared<HighContrastObserver>(AceType::WeakClaim(container.GetRawPtr()));
    highContrastObserver->first_ = false;
    AccessibilityConfig::ConfigValue value;
    highContrastObserver->OnConfigChanged(AccessibilityConfig::CONFIG_ID::CONFIG_HIGH_CONTRAST_TEXT, value);
    EXPECT_FALSE(highContrastObserver->first_);
}
} // namespace OHOS::Ace::NG