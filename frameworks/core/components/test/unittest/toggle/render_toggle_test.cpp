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
#include "core/components/toggle/render_toggle.h"
#include "core/components/toggle/toggle_component.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class RenderToggleTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void RenderToggleTest::SetUpTestCase() {}
void RenderToggleTest::TearDownTestCase() {}
void RenderToggleTest::SetUp() {}
void RenderToggleTest::TearDown() {}

class MockRenderToggle final : public RenderToggle {
    DECLARE_ACE_TYPE(MockRenderToggle, RenderToggle);

public:
    MockRenderToggle() = default;
    ~MockRenderToggle() override = default;

private:
    Size Measure() override;
};

Size MockRenderToggle::Measure()
{
    Size toggleSize;
    return toggleSize;
}

/**
 * @tc.name: RenderToggleTest001
 * @tc.desc: Test state transfer of the toggle component
 * @tc.type: FUNC
 * @tc.require: issueI5NC9F
 */
HWTEST_F(RenderToggleTest, RenderToggleTest001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderToggleTest RenderToggleTest001 start";

    /**
     * @tc.steps: step1. Construct a ToggleComponent.
     */
    RefPtr<ToggleComponent> toggleComponent = AceType::MakeRefPtr<ToggleComponent>();

    /**
     * @tc.steps: step2. Set state to ToggleComponent.
     */
    RefPtr<MockRenderToggle> renderToggle = AceType::MakeRefPtr<MockRenderToggle>();
    toggleComponent->SetCheckedState(true);

    /**
     * @tc.steps: step3. Store state of toggle component.
     * @tc.expected: step3. The return string is correct.
     */
    renderToggle->Update(toggleComponent);
    std::string info = renderToggle->ProvideRestoreInfo();
    std::string expectStateResult = "{\"checked\":true,\"isPressed\":false}";
    EXPECT_EQ(info, expectStateResult);
    /**
     * @tc.steps: step4. Restore state of toggle component.
     * @tc.expected: step4. The state is correct.
     */  
    renderToggle->SetRestoreInfo(expectStateResult);
    renderToggle->Update(toggleComponent);
    EXPECT_TRUE(toggleComponent->GetCheckedState());
    
    /**
     * @tc.steps: step5. Second Update doesn't restore the state.
     * @tc.expected: step5. The stored string is empty.
     */ 
    renderToggle->Update(toggleComponent);
    EXPECT_TRUE(renderToggle->GetRestoreInfo().empty());

    /**
     * @tc.steps: step6. Restore state from invalid json string.
     * @tc.expected: step6. The state is unchanged.
     */  
    std::string invalidInfo = "checked\":false,\"isPressed\":false";
    renderToggle->SetRestoreInfo(invalidInfo);
    renderToggle->Update(toggleComponent);
    EXPECT_TRUE(toggleComponent->GetCheckedState());

    GTEST_LOG_(INFO) << "RenderToggleTest RenderToggleTest001 stop";
}

} // namespace OHOS::Ace
