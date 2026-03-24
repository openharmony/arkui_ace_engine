/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/gauge/gauge_layout_property.h"
#include "core/components_ng/pattern/gauge/gauge_paint_property.h"
#include "core/components_ng/pattern/gauge/gauge_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/syntax/with_theme_node.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t THEME_SCOPE_ID = 10001;
const Color THEME_INDICATOR_COLOR = Color::RED;
const Color THEME_INDICATOR_BORDER_COLOR = Color::BLUE;

class TestGaugeTheme : public GaugeTheme {
    DECLARE_ACE_TYPE(TestGaugeTheme, GaugeTheme);

public:
    TestGaugeTheme() = default;
    ~TestGaugeTheme() override = default;

    void SetIndicatorColor(const Color& color)
    {
        indicatorColor_ = color;
    }

    void SetIndicatorBorderColor(const Color& color)
    {
        indicatorBorderColor_ = color;
    }
};
} // namespace

class GaugeWithThemeTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void GaugeWithThemeTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
}

void GaugeWithThemeTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void GaugeWithThemeTestNg::SetUp()
{
    TestNG::SetUp();
}

void GaugeWithThemeTestNg::TearDown()
{
    TestNG::TearDown();
}

/**
 * @tc.name: OnThemeScopeUpdate001
 * @tc.desc: Test GaugePattern OnThemeScopeUpdate marks node dirty and updates theme colors
 * @tc.type: FUNC
 */
HWTEST_F(GaugeWithThemeTestNg, OnThemeScopeUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create WithTheme node and Gauge node.
     */
    auto withThemeNode = WithThemeNode::CreateWithThemeNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(withThemeNode, nullptr);
    withThemeNode->SetThemeScopeId(THEME_SCOPE_ID);

    auto frameNode = FrameNode::CreateFrameNode(
        V2::GAUGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<GaugePattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MountToParent(withThemeNode);

    auto pattern = frameNode->GetPattern<GaugePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Setup Mock Theme for the scope with specific indicator color.
     */
    auto pipeline = MockPipelineContext::GetCurrent();
    pipeline->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(themeManager);

    // Setup MockContainer and link it to our mock pipeline
    MockContainer::SetUp(pipeline);
    auto container = MockContainer::Current();
    if (container) {
        container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    }

    // Attach node to main tree with pipeline context
    frameNode->AttachToMainTree(true, pipeline.GetRawPtr());

    auto gaugeTheme = AceType::MakeRefPtr<TestGaugeTheme>();
    gaugeTheme->SetIndicatorColor(THEME_INDICATOR_COLOR);
    gaugeTheme->SetIndicatorBorderColor(THEME_INDICATOR_BORDER_COLOR);

    // Use the actual scope ID from the node to avoid mismatch
    auto actualScopeId = frameNode->GetThemeScopeId();
    EXPECT_CALL(
        *themeManager, GetTheme(testing::_, testing::AnyOf(testing::Eq(THEME_SCOPE_ID), testing::Eq(actualScopeId))))
        .WillRepeatedly(testing::Return(gaugeTheme));

    /**
     * @tc.steps: step3. Trigger theme scope update.
     */
    // Clear any existing flags first
    frameNode->GetPaintProperty<GaugePaintProperty>()->CleanDirty();
    bool updateResult = pattern->OnThemeScopeUpdate(actualScopeId);
    EXPECT_TRUE(updateResult);

    /**
     * @tc.expected: Gauge node is marked dirty for render and theme color is updated.
     */
    auto paintProperty = frameNode->GetPaintProperty<GaugePaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_TRUE(paintProperty->GetPropertyChangeFlag() & PROPERTY_UPDATE_RENDER);

    auto fetchedTheme = pipeline->GetTheme<GaugeTheme>(actualScopeId);
    ASSERT_NE(fetchedTheme, nullptr);
    EXPECT_EQ(fetchedTheme->GetIndicatorColor(), THEME_INDICATOR_COLOR);
    EXPECT_EQ(fetchedTheme->GetIndicatorBorderColor(), THEME_INDICATOR_BORDER_COLOR);
}

} // namespace OHOS::Ace::NG