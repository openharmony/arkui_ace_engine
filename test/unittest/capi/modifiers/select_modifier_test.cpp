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

#include "core/components/select/select_theme.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/components_ng/pattern/select/select_pattern.h"

#include "core/interfaces/arkoala/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
using ArkBlurStyleTest = std::pair<Ark_BlurStyle, std::string>;

const std::vector<ArkBlurStyleTest> BLUR_STYLE_TEST_PLAN = {
    { ARK_BLUR_STYLE_THIN, "BlurStyle.Thin" },
    { ARK_BLUR_STYLE_REGULAR, "BlurStyle.Regular" },
    { ARK_BLUR_STYLE_THICK, "BlurStyle.Thick" },
    { ARK_BLUR_STYLE_BACKGROUND_THIN, "BlurStyle.BACKGROUND_THIN" },
    { ARK_BLUR_STYLE_BACKGROUND_REGULAR, "BlurStyle.BACKGROUND_REGULAR" },
    { ARK_BLUR_STYLE_BACKGROUND_THICK, "BlurStyle.BACKGROUND_THICK" },
    { ARK_BLUR_STYLE_BACKGROUND_ULTRA_THICK, "BlurStyle.BACKGROUND_ULTRA_THICK" },
    { ARK_BLUR_STYLE_NONE, "BlurStyle.NONE" },
    { ARK_BLUR_STYLE_COMPONENT_ULTRA_THIN, "BlurStyle.COMPONENT_ULTRA_THIN" },
    { ARK_BLUR_STYLE_COMPONENT_THIN, "BlurStyle.COMPONENT_THIN" },
    { ARK_BLUR_STYLE_COMPONENT_REGULAR, "BlurStyle.COMPONENT_REGULAR" },
    { ARK_BLUR_STYLE_COMPONENT_THICK, "BlurStyle.COMPONENT_THICK" },
    { ARK_BLUR_STYLE_COMPONENT_ULTRA_THICK, "BlurStyle.COMPONENT_ULTRA_THICK" }
};
} // namespace

class SelectModifierTest : public ModifierTestBase<GENERATED_ArkUISelectModifier,
    &GENERATED_ArkUINodeModifiers::getSelectModifier, GENERATED_ARKUI_SELECT> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupThemeStyle("select_pattern");

        SetupTheme<SelectTheme>();
        SetupTheme<TextTheme>();
    }

    void SetUp(void) override
    {
        ModifierTestBase::SetUp();
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        if (frameNode) {
            SelectParam param = { .text = "Option1" };
            SelectModelNG::InitSelect(frameNode, { param });
            auto selectPattern = frameNode->GetPatternPtr<SelectPattern>();
            std::vector<RefPtr<FrameNode>> options = selectPattern->GetOptions();
            options[0]->GetPattern()->OnModifyDone(); // Init selectTheme
        }
    }
};

/**
 * @tc.name: setControlSizeTest
 * @tc.desc: Test setControlSize function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setControlSizeTest, TestSize.Level1)
{
    const auto propName("controlSize");
    ASSERT_NE(modifier_->setControlSize, nullptr);

    modifier_->setControlSize(node_, ARK_CONTROL_SIZE_NORMAL);
    auto checkVal1 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal1, "ControlSize.NORMAL");

    modifier_->setControlSize(node_, ARK_CONTROL_SIZE_SMALL);
    auto checkVal2 = GetStringAttribute(node_, propName);
    EXPECT_EQ(checkVal2, "ControlSize.SMALL");
}

/**
 * @tc.name: setMenuBackgroundBlurStyleTest
 * @tc.desc: Test setMenuBackgroundBlurStyle function
 * @tc.type: FUNC
 */
HWTEST_F(SelectModifierTest, setMenuBackgroundBlurStyleTest, TestSize.Level1)
{
    const auto propName("menuBackgroundBlurStyle");
    ASSERT_NE(modifier_->setMenuBackgroundBlurStyle, nullptr);

    for (auto blurStyle: BLUR_STYLE_TEST_PLAN) {
        modifier_->setMenuBackgroundBlurStyle(node_, blurStyle.first);
        auto checkVal = GetStringAttribute(node_, propName);
        EXPECT_EQ(checkVal, blurStyle.second);
    }
}

} // namespace OHOS::Ace::NG
