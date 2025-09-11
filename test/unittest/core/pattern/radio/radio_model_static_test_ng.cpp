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

#include "test/unittest/core/pattern/test_ng.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "ui/resource/resource_info.h"

#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/radio/radio_model_ng.h"
#include "core/components_ng/pattern/radio/radio_model_static.h"
#include "core/components_ng/pattern/radio/radio_paint_property.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
using RadioBuilderFunc = std::function<void()>;
namespace OHOS::Ace::NG {
namespace {
constexpr bool CHECKED = true;
constexpr Color NORMAL_COLOR = Color(0xff0000ff);
constexpr Dimension HORIZONTAL_PADDING = Dimension(5.0);
constexpr Dimension VERTICAL_PADDING = Dimension(4.0);
constexpr double DEFAULT_WIDTH = 100.0;
constexpr double DEFAULT_HEIGHT = 110.0;
constexpr Dimension DEFAULT_WIDTH_DIMENSION = Dimension(DEFAULT_WIDTH);
constexpr Dimension DEFAULT_HEIGHT_DIMENSION = Dimension(DEFAULT_HEIGHT);
} // namespace

class RadioStaticTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static RadioBuilderFunc RadioBuilder();
};

void RadioStaticTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        auto radioTheme = AceType::MakeRefPtr<RadioTheme>();
        radioTheme->hotZoneHorizontalPadding_ = HORIZONTAL_PADDING;
        radioTheme->hotZoneVerticalPadding_ = VERTICAL_PADDING;
        radioTheme->defaultWidth_ = DEFAULT_WIDTH_DIMENSION;
        radioTheme->defaultHeight_ = DEFAULT_HEIGHT_DIMENSION;
        return radioTheme;
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    MockContainer::SetUp();
}

void RadioStaticTestNg::TearDownTestSuite()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: RadioStaticTestNg001
 * @tc.desc: test radio SetChecked.
 * @tc.type: FUNC
 */
HWTEST_F(RadioStaticTestNg, RadioStaticTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create radio frameNode.
     */
    auto node = RadioModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::RADIO_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create radio paintProperty.
     */
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetChecked.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<bool> radioChecked = std::nullopt;
    RadioModelStatic::SetChecked(frameNode, radioChecked);
    EXPECT_EQ(radioPaintProperty->GetRadioCheck(), std::nullopt);
    radioChecked = CHECKED;
    RadioModelStatic::SetChecked(frameNode, radioChecked);
    EXPECT_EQ(radioPaintProperty->GetRadioCheck(), CHECKED);
}

/**
 * @tc.name: RadioStaticTestNg002
 * @tc.desc: test radio SetCheckedBackgroundColor.
 * @tc.type: FUNC
 */
HWTEST_F(RadioStaticTestNg, RadioStaticTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create radio frameNode.
     */
    auto node = RadioModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::RADIO_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create radio paintProperty.
     */
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetCheckedBackgroundColor.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Color> radioBackgroundColor = std::nullopt;
    RadioModelStatic::SetCheckedBackgroundColor(frameNode, radioBackgroundColor);
    EXPECT_EQ(radioPaintProperty->GetRadioCheckedBackgroundColor(), std::nullopt);
    radioBackgroundColor = NORMAL_COLOR;
    RadioModelStatic::SetCheckedBackgroundColor(frameNode, radioBackgroundColor);
    EXPECT_EQ(radioPaintProperty->GetRadioCheckedBackgroundColorValue(), NORMAL_COLOR);
}

/**
 * @tc.name: RadioStaticTestNg003
 * @tc.desc: test radio SetUncheckedBorderColor.
 * @tc.type: FUNC
 */
HWTEST_F(RadioStaticTestNg, RadioStaticTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create radio frameNode.
     */
    auto node = RadioModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::RADIO_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create radio paintProperty.
     */
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetUncheckedBorderColor.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Color> radioUncheckedBorderColor = std::nullopt;
    RadioModelStatic::SetUncheckedBorderColor(frameNode, radioUncheckedBorderColor);
    EXPECT_EQ(radioPaintProperty->GetRadioUncheckedBorderColor(), std::nullopt);
    radioUncheckedBorderColor = NORMAL_COLOR;
    RadioModelStatic::SetUncheckedBorderColor(frameNode, radioUncheckedBorderColor);
    EXPECT_EQ(radioPaintProperty->GetRadioUncheckedBorderColorValue(), NORMAL_COLOR);
}

/**
 * @tc.name: RadioStaticTestNg004
 * @tc.desc: test radio SetIndicatorColor.
 * @tc.type: FUNC
 */
HWTEST_F(RadioStaticTestNg, RadioStaticTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create radio frameNode.
     */
    auto node = RadioModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::RADIO_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create radio paintProperty.
     */
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetIndicatorColor.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<Color> radioIndicatorColor = std::nullopt;
    RadioModelStatic::SetIndicatorColor(frameNode, radioIndicatorColor);
    EXPECT_EQ(radioPaintProperty->GetRadioIndicatorColor(), std::nullopt);
    radioIndicatorColor = NORMAL_COLOR;
    RadioModelStatic::SetIndicatorColor(frameNode, radioIndicatorColor);
    EXPECT_EQ(radioPaintProperty->GetRadioIndicatorColorValue(), NORMAL_COLOR);
}

/**
 * @tc.name: RadiotaticTestNg005
 * @tc.desc: test radio SetIndicatorColor.
 * @tc.type: FUNC
 */
HWTEST_F(RadioStaticTestNg, RadioStaticTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create radio frameNode.
     */
    auto node = RadioModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->GetTag(), V2::RADIO_ETS_TAG);
    auto frameNode = AceType::RawPtr(node);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. create radio paintProperty.
     */
    auto radioPaintProperty = frameNode->GetPaintProperty<RadioPaintProperty>();
    ASSERT_NE(radioPaintProperty, nullptr);

    /**
     * @tc.steps: step3. test SetRadioIndicatorType.
     * @tc.expected: step3. the property value meet expectations.
     */
    std::optional<int32_t> radioIndicatorType = std::nullopt;
    RadioModelStatic::SetRadioIndicatorType(frameNode, radioIndicatorType);
    EXPECT_EQ(radioPaintProperty->GetRadioIndicator(), std::nullopt);
    radioIndicatorType = static_cast<int32_t>(RadioIndicatorType::DOT);
    RadioModelStatic::SetRadioIndicatorType(frameNode, radioIndicatorType);
    EXPECT_EQ(radioPaintProperty->GetRadioIndicatorValue(), static_cast<int32_t>(RadioIndicatorType::DOT));
}
} // namespace OHOS::Ace::NG