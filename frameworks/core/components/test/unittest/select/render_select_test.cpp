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

#include "core/components/select/render_select.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class RenderSelectTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}

    void SetUp() override {}
    void TearDown() override {}
};

class MockRenderSelect final : public RenderSelect {
    DECLARE_ACE_TYPE(MockRenderSelect, RenderSelect);

public:
    MockRenderSelect() = default;
    ~MockRenderSelect() override = default;

    std::size_t GetIndex() const
    {
        return index_;
    }

    void SetIndex(std::size_t index)
    {
        index_ = index;
    }
};

/**
 * @tc.name: RenderSelectContinuation001
 * @tc.desc: Test state transfer of the select component
 * @tc.type: FUNC
 * @tc.require: issueI5NC9F
 */
HWTEST_F(RenderSelectTest, RenderSelectContinuation001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderSelectTest continuation001 start";

    /**
     * @tc.steps: step1. Construct a SelectComponent and set selected item.
     */
    RefPtr<SelectComponent> select = AceType::MakeRefPtr<SelectComponent>();
    RefPtr<TextComponent> tip = AceType::MakeRefPtr<TextComponent>("tip");
    select->SetTipText(tip);
    for (uint32_t i = 0; i < 10; i++) {
        RefPtr<OptionComponent> option = AceType::MakeRefPtr<OptionComponent>();
        if (i == 2) {
            option->SetSelectable(true);
            option->SetSelected(true);
            RefPtr<TextComponent> text = AceType::MakeRefPtr<TextComponent>("test");
            option->SetText(text);
        } else {
            option->SetSelectable(false);
            option->SetSelected(false);
        }
        select->InsertSelectOption(option, i);
    }

    /**
     * @tc.steps: step2. Construct RenderSelect and Update.
     */
    RefPtr<MockRenderSelect> renderSelect = AceType::MakeRefPtr<MockRenderSelect>();
    renderSelect->Update(select);

    /**
     * @tc.steps: step3. Store index state of select component.
     * @tc.expected: step3. The return string is correct.
     */
    std::string info = renderSelect->ProvideRestoreInfo();
    std::string expectStateResult = "2";
    EXPECT_EQ(info, expectStateResult);

    /**
     * @tc.steps: step4. Restore index state of select component.
     * @tc.expected: step4. The index state is correct.
     */
    renderSelect->SetRestoreInfo(expectStateResult);
    renderSelect->Update(select);
    EXPECT_EQ(renderSelect->GetIndex(), 2);

    /**
     * @tc.steps: step5. Second Update doesn't restore the state.
     * @tc.expected: step5. The stored string is empty.
     */
    renderSelect->Update(select);
    EXPECT_TRUE(renderSelect->GetRestoreInfo().empty());

    /**
     * @tc.steps: step6. Restore index state of no text item.
     * @tc.expected: step6. The index state is correct.
     */

    renderSelect->SetRestoreInfo("3");
    renderSelect->Update(select);
    EXPECT_EQ(renderSelect->GetIndex(), 3);

    GTEST_LOG_(INFO) << "RenderSelectTest continuation001 stop";
}

} // namespace OHOS::Ace
