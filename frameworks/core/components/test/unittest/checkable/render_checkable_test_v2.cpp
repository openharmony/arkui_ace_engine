/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "base/log/log.h"
#include "core/components/checkable/checkable_component.h"
#include "core/components/checkable/render_checkbox.h"
#include "core/components/checkable/render_radio.h"
#include "core/components/checkable/render_switch.h"


using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
constexpr double TEST_TEXT_SIZE = 200.0;
const RefPtr<ThemeManager> THEME_MANAGER = AceType::MakeRefPtr<ThemeManager>();
} // namespace

class MockRenderSwitch final : public RenderSwitch {
    DECLARE_ACE_TYPE(MockRenderSwitch, RenderSwitch);

public:
    MockRenderSwitch() = default;
    ~MockRenderSwitch() override = default;

    Size CalculateTextSize(const std::string& text, RefPtr<RenderText>& renderText) override
    {
        return Size(TEST_TEXT_SIZE, TEST_TEXT_SIZE);
    }

    void SetChecked(bool checked)
    {
        checked_ = checked;
    }
};

class MockRenderRadio final : public RenderRadio {
    DECLARE_ACE_TYPE(MockRenderRadio, RenderRadio);

public:
    MockRenderRadio() = default;
    ~MockRenderRadio() override = default;

    void SetChecked(bool checked)
    {
        checked_ = checked;
    }

    void SetRadioValue(const std::string& radioValue)
    {
        radioValue_ = radioValue;
    }

    void SetGroupValue(const std::string& groupValue)
    {
        groupValue_ = groupValue;
    }

    const std::string& GetRadioValue() const
    {
        return radioValue_;
    }

    const std::string& GetGroupValue() const
    {
        return groupValue_;
    }
};

class RenderCheckableTestV2 : public testing::Test {
public:
    static void SetUpTestCase()
    {
        GTEST_LOG_(INFO) << "RenderCheckableTestV2 SetUpTestCase";
    }

    static void TearDownTestCase()
    {
        GTEST_LOG_(INFO) << "RenderCheckableTestV2 TearDownTestCase";
    }

    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: RenderCheckableContinuation001
 * @tc.desc: Test state transfer of the checkbox component
 * @tc.type: FUNC
 * @tc.require: issueI5NC9F
 */
HWTEST_F(RenderCheckableTestV2, RenderCheckableContinuation001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderCheckableTestV2 continuation001 start";

    /**
     * @tc.steps: step1. create a checkbox component.
     */
    RefPtr<CheckboxTheme> theme = THEME_MANAGER->GetTheme<CheckboxTheme>();
    RefPtr<CheckboxComponent> checkboxComponent = AceType::MakeRefPtr<CheckboxComponent>(theme);

    /**
     * @tc.steps: step2. Set checked state of checkbox component.
     */
    RefPtr<RenderCheckbox> renderCheckbox = AceType::MakeRefPtr<RenderCheckbox>();
    renderCheckbox->SetChecked(true);

    /**
     * @tc.steps: step3. Store checked state of checkbox component.
     * @tc.expected: step3. The return string is correct.
     */    
    std::string info = renderCheckbox->ProvideRestoreInfo();
    std::string expectStateResult = "1";
    EXPECT_EQ(info, expectStateResult);

    /**
     * @tc.steps: step4. Restore checked state of checkbox component.
     * @tc.expected: step4. The checked state is correct.
     */  
    renderCheckbox->SetRestoreInfo(expectStateResult);
    renderCheckbox->Update(checkboxComponent);
    EXPECT_TRUE(renderCheckbox->GetChecked());

    /**
     * @tc.steps: step5. Second Update doesn't restore the state.
     * @tc.expected: step5. The stored string is empty.
     */ 
    renderCheckbox->Update(checkboxComponent);
    EXPECT_TRUE(renderCheckbox->GetRestoreInfo().empty());

    GTEST_LOG_(INFO) << "RenderCheckableTestV2 continuation001 stop";
}

/**
 * @tc.name: RenderCheckableContinuation002
 * @tc.desc: Test state transfer of the switch component
 * @tc.type: FUNC
 * @tc.require: issueI5NC9F
 */
HWTEST_F(RenderCheckableTestV2, RenderCheckableContinuation002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderCheckableTestV2 continuation002 start";

    /**
     * @tc.steps: step1. create a switch component.
     */
    RefPtr<SwitchTheme> theme = THEME_MANAGER->GetTheme<SwitchTheme>();
    RefPtr<SwitchComponent> switchComponent = AceType::MakeRefPtr<SwitchComponent>(theme);

    /**
     * @tc.steps: step2. Set checked state of switch component.
     */
    RefPtr<MockRenderSwitch> renderSwitch = AceType::MakeRefPtr<MockRenderSwitch>();
    renderSwitch->SetChecked(true);

    /**
     * @tc.steps: step3. Store checked state of switch component.
     * @tc.expected: step3. The return string is correct.
     */    
    std::string info = renderSwitch->ProvideRestoreInfo();
    std::string expectStateResult = "1";
    EXPECT_EQ(info, expectStateResult);

    /**
     * @tc.steps: step4. Restore checked state of switch component.
     * @tc.expected: step4. The checked state is correct.
     */
    renderSwitch->SetRestoreInfo(expectStateResult);
    renderSwitch->Update(switchComponent);
    EXPECT_TRUE(renderSwitch->GetChecked());

    /**
     * @tc.steps: step5. Second Update doesn't restore the state.
     * @tc.expected: step5. The stored string is empty.
     */ 
    renderSwitch->Update(switchComponent);
    EXPECT_TRUE(renderSwitch->GetRestoreInfo().empty());

    GTEST_LOG_(INFO) << "RenderCheckableTestV2 continuation002 stop";
}

/**
 * @tc.name: RenderCheckableContinuation003
 * @tc.desc: Test state transfer of the radio component
 * @tc.type: FUNC
 * @tc.require: issueI5NC9F
 */
HWTEST_F(RenderCheckableTestV2, RenderCheckableContinuation003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderCheckableTestV2 continuation003 start";

    /**
     * @tc.steps: step1. Construct a radio component.
     */
    RefPtr<RadioTheme> theme = THEME_MANAGER->GetTheme<RadioTheme>();
    RefPtr<RadioComponent<std::string>> radioComponent = AceType::MakeRefPtr<RadioComponent<std::string>>(theme);

    /**
     * @tc.steps: step2. Set checked state of radio component.
     */
    RefPtr<MockRenderRadio> renderRadio = AceType::MakeRefPtr<MockRenderRadio>();
    renderRadio->SetChecked(true);
    std::string radioValue = "radio1";
    std::string groupValue = "radio2";
    renderRadio->SetRadioValue(radioValue);
    renderRadio->SetGroupValue(groupValue);

    /**
     * @tc.steps: step3. Store checked state of radio component.
     * @tc.expected: step3. The return string is correct.
     */
    std::string info = renderRadio->ProvideRestoreInfo();
    std::string expectStateResult = "{\"checked\":true,\"radioValue\":\"radio1\",\"groupValue\":\"radio2\"}";
    EXPECT_EQ(info, expectStateResult);

    /**
     * @tc.steps: step4. Restore checked state of radio component.
     * @tc.expected: step4. The checked state is correct.
     */  
    renderRadio->SetRestoreInfo(expectStateResult);
    renderRadio->Update(radioComponent);
    EXPECT_TRUE(renderRadio->GetChecked());
    EXPECT_EQ(renderRadio->GetRadioValue(), radioValue);
    EXPECT_EQ(renderRadio->GetGroupValue(), groupValue);

    /**
     * @tc.steps: step5. Second Update doesn't restore the state.
     * @tc.expected: step5. The stored string is empty.
     */ 
    renderRadio->Update(radioComponent);
    EXPECT_TRUE(renderRadio->GetRestoreInfo().empty());

    /**
     * @tc.steps: step6. Restore state from invalid json string.
     * @tc.expected: step6. The state is unchanged.
     */  
    std::string invalidInfo = "checked\":true,\"radioValue\":\"radio1\",\"groupValue\":\"radio2";
    renderRadio->SetRestoreInfo(invalidInfo);
    renderRadio->Update(radioComponent);
    EXPECT_FALSE(renderRadio->GetChecked());

    GTEST_LOG_(INFO) << "RenderCheckableTestV2 continuation003 stop";
}

} // namespace OHOS::Ace
