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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/components_ng/pattern/shape/line_model_ng.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace  {
    constexpr auto ATTRIBUTE_WIDTH_NAME = "width";
    constexpr auto ATTRIBUTE_HEIGHT_NAME = "height";
    constexpr auto WIDTH_STR = "111.00vp";
    constexpr auto HEIGHT_STR = "222.00vp";
    constexpr int WIDTH = 111;
    constexpr int HEIGHT = 222;
    constexpr auto DEFAULT_VALUE = "-";
} // namespace

class LineModifierTest : public ModifierTestBase<GENERATED_ArkUILineModifier,
    &GENERATED_ArkUINodeModifiers::getLineModifier, GENERATED_ARKUI_LINE> {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
            auto theme = AceType::MakeRefPtr<CheckboxTheme>();
            return theme;
        });
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
        MockContainer::SetUp();
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
};

Opt_Literal_Union_String_Number_height_width BuildLineOptions(int width, int height)
{
    Ark_Literal_Union_String_Number_height_width options;
    options.width = Converter::ArkUnion<Opt_Union_String_Number, Ark_Number>(width);
    options.height = Converter::ArkUnion<Opt_Union_String_Number, Ark_Number>(height);
    return Converter::ArkValue<Opt_Literal_Union_String_Number_height_width>(options);
}

/**
 * @tc.name: LineModifierDefaultTest
 * @tc.desc: setLineOptions test
 * @tc.type: FUNC
 */
HWTEST_F(LineModifierTest, LineModifierDefaultTest, TestSize.Level1)
{
    std::string strResult;
    strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
    EXPECT_EQ(strResult, DEFAULT_VALUE);
    strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
    EXPECT_EQ(strResult, DEFAULT_VALUE);
}

/**
 * @tc.name: LineModifierSetLineOptionsTest
 * @tc.desc: setLineOptions test
 * @tc.type: FUNC
 */
HWTEST_F(LineModifierTest, LineModifierSetLineOptionsTest, TestSize.Level1)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node_);
    auto options = BuildLineOptions(WIDTH, HEIGHT);
    modifier_->setLineOptions(frameNode, &options);

    std::string strResult;
    strResult = GetStringAttribute(node_, ATTRIBUTE_WIDTH_NAME);
    EXPECT_EQ(strResult, WIDTH_STR);
    strResult = GetStringAttribute(node_, ATTRIBUTE_HEIGHT_NAME);
    EXPECT_EQ(strResult, HEIGHT_STR);
}
} // namespace OHOS::Ace::NG
