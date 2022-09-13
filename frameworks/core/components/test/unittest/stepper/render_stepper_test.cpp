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
#include "core/components/test/unittest/mock/mock_render_common.h"
#include "core/components/stepper/render_stepper.h"
#include "core/components/test/unittest/mock/mock_render_stepper.h"
#include "base/i18n/localization.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class RenderStepperTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

void RenderStepperTest::SetUpTestCase()
{
    GTEST_LOG_(INFO) << "RenderStepperTest SetUpTestCase";
}

void  RenderStepperTest::TearDownTestCase()
{
    GTEST_LOG_(INFO) << "RenderStepperTest TearDownTestCase";
}

void  RenderStepperTest::SetUp() {}
void  RenderStepperTest::TearDown() {}

/**
 * @tc.name: LoadDefaultButtonStatus001
 * @tc.desc: Test LoadDefaultButtonStatus for RTL
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderStepperTest, LoadDefaultButtonStatus001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderStepperTest LoadDefaultButtonStatus001 start";
    
    /**
     * @tc.steps: step1. Construct StepperComponent and set text direction.
     */
    std::list<RefPtr<Component>> componentChildren;
    for (uint32_t i = 0; i < 1; i++) {
        RefPtr<StepperComponent> item = AceType::MakeRefPtr<StepperComponent>();
        componentChildren.emplace_back(item);
    }
    RefPtr<StepperComponent> stepperComponent = AceType::MakeRefPtr<StepperComponent>(componentChildren);
    stepperComponent->SetTextDirection(TextDirection::RTL);
    stepperComponent->SetIndex(0);
    std::vector<StepperLabels> stepperLabels;
    for (uint32_t i = 0; i < 1; i++) {
        StepperLabels labelItem;
        stepperLabels.emplace_back(labelItem);
    }
    stepperComponent->SetStepperLabels(stepperLabels);
    RefPtr<MockRenderStepper> renderStepper = AceType::MakeRefPtr<MockRenderStepper>();
    auto mockContext = MockRenderCommon::GetMockContext();
    renderStepper->Attach(mockContext);

    /**
     * @tc.steps: step2. Run Update interface.
     * @tc.expected: step2. The index is correct.
     */
    Localization::GetInstance()->SetLocale("en", "US", "", "", "en-US");
    renderStepper->Update(stepperComponent);
    EXPECT_EQ(renderStepper->GetCurrentIndex(), 0);

    GTEST_LOG_(INFO) << "RenderStepperTest LoadDefaultButtonStatus001 stop";
}

/**
 * @tc.name: LoadDefaultButtonStatus002
 * @tc.desc: Test LoadDefaultButtonStatus for RTL
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderStepperTest, LoadDefaultButtonStatus002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderStepperTest LoadDefaultButtonStatus002 start";
    
    /**
     * @tc.steps: step1. Construct StepperComponent and set text direction.
     */
    std::list<RefPtr<Component>> componentChildren;
    for (uint32_t i = 0; i < 2; i++) {
        RefPtr<StepperComponent> item = AceType::MakeRefPtr<StepperComponent>();
        componentChildren.emplace_back(item);
    }
    RefPtr<StepperComponent> stepperComponent = AceType::MakeRefPtr<StepperComponent>(componentChildren);
    stepperComponent->SetTextDirection(TextDirection::RTL);
    stepperComponent->SetIndex(0);
    std::vector<StepperLabels> stepperLabels;
    for (uint32_t i = 0; i < 2; i++) {
        StepperLabels labelItem;
        stepperLabels.emplace_back(labelItem);
    }
    stepperComponent->SetStepperLabels(stepperLabels);
    RefPtr<MockRenderStepper> renderStepper = AceType::MakeRefPtr<MockRenderStepper>();
    auto mockContext = MockRenderCommon::GetMockContext();
    renderStepper->Attach(mockContext);

    /**
     * @tc.steps: step2. Run Update interface.
     * @tc.expected: step2. The index is correct.
     */
    Localization::GetInstance()->SetLocale("en", "US", "", "", "en-US");
    renderStepper->Update(stepperComponent);
    EXPECT_EQ(renderStepper->GetCurrentIndex(), 0);

    GTEST_LOG_(INFO) << "RenderStepperTest LoadDefaultButtonStatus002 stop";
}

/**
 * @tc.name: LoadDefaultButtonStatus003
 * @tc.desc: Test LoadDefaultButtonStatus for RTL
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderStepperTest, LoadDefaultButtonStatus003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderStepperTest LoadDefaultButtonStatus003 start";
    
    /**
     * @tc.steps: step1. Construct StepperComponent and set text direction.
     */
    std::list<RefPtr<Component>> componentChildren;
    for (uint32_t i = 0; i < 2; i++) {
        RefPtr<StepperComponent> item = AceType::MakeRefPtr<StepperComponent>();
        componentChildren.emplace_back(item);
    }
    RefPtr<StepperComponent> stepperComponent = AceType::MakeRefPtr<StepperComponent>(componentChildren);
    stepperComponent->SetTextDirection(TextDirection::RTL);
    stepperComponent->SetIndex(1);
    std::vector<StepperLabels> stepperLabels;
    for (uint32_t i = 0; i < 2; i++) {
        StepperLabels labelItem;
        stepperLabels.emplace_back(labelItem);
    }
    stepperComponent->SetStepperLabels(stepperLabels);
    RefPtr<MockRenderStepper> renderStepper = AceType::MakeRefPtr<MockRenderStepper>();
    auto mockContext = MockRenderCommon::GetMockContext();
    renderStepper->Attach(mockContext);

    /**
     * @tc.steps: step2. Run Update interface.
     * @tc.expected: step2. The index is correct.
     */
    Localization::GetInstance()->SetLocale("en", "US", "", "", "en-US");
    renderStepper->Update(stepperComponent);
    EXPECT_EQ(renderStepper->GetCurrentIndex(), 1);

    GTEST_LOG_(INFO) << "RenderStepperTest LoadDefaultButtonStatus003 stop";
}

/**
 * @tc.name: LoadDefaultButtonStatus004
 * @tc.desc: Test LoadDefaultButtonStatus
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderStepperTest, LoadDefaultButtonStatus004, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderStepperTest LoadDefaultButtonStatus004 start";
    
    /**
     * @tc.steps: step1. Construct StepperComponent and set text direction.
     */
    std::list<RefPtr<Component>> componentChildren;
    for (uint32_t i = 0; i < 5; i++) {
        RefPtr<StepperComponent> item = AceType::MakeRefPtr<StepperComponent>();
        componentChildren.emplace_back(item);
    }
    RefPtr<StepperComponent> stepperComponent = AceType::MakeRefPtr<StepperComponent>(componentChildren);
    stepperComponent->SetTextDirection(TextDirection::RTL);
    stepperComponent->SetIndex(2);
    std::vector<StepperLabels> stepperLabels;
    for (uint32_t i = 0; i < 5; i++) {
        StepperLabels labelItem;
        stepperLabels.emplace_back(labelItem);
    }
    stepperComponent->SetStepperLabels(stepperLabels);
    RefPtr<MockRenderStepper> renderStepper = AceType::MakeRefPtr<MockRenderStepper>();
    auto mockContext = MockRenderCommon::GetMockContext();
    renderStepper->Attach(mockContext);

    /**
     * @tc.steps: step2. Run Update interface.
     * @tc.expected: step2. The index is correct.
     */
    Localization::GetInstance()->SetLocale("en", "US", "", "", "en-US");
    renderStepper->Update(stepperComponent);
    EXPECT_EQ(renderStepper->GetCurrentIndex(), 2);

    GTEST_LOG_(INFO) << "RenderStepperTest LoadDefaultButtonStatus004 stop";
}

/**
 * @tc.name: LoadDefaultButtonStatus005
 * @tc.desc: Test LoadDefaultButtonStatus for LTR
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderStepperTest, LoadDefaultButtonStatus005, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderStepperTest LoadDefaultButtonStatus005 start";
    
    /**
     * @tc.steps: step1. Construct StepperComponent and set text direction.
     */
    std::list<RefPtr<Component>> componentChildren;
    for (uint32_t i = 0; i < 1; i++) {
        RefPtr<StepperComponent> item = AceType::MakeRefPtr<StepperComponent>();
        componentChildren.emplace_back(item);
    }
    RefPtr<StepperComponent> stepperComponent = AceType::MakeRefPtr<StepperComponent>(componentChildren);
    stepperComponent->SetTextDirection(TextDirection::LTR);
    stepperComponent->SetIndex(0);
    std::vector<StepperLabels> stepperLabels;
    for (uint32_t i = 0; i < 1; i++) {
        StepperLabels labelItem;
        stepperLabels.emplace_back(labelItem);
    }
    stepperComponent->SetStepperLabels(stepperLabels);
    RefPtr<MockRenderStepper> renderStepper = AceType::MakeRefPtr<MockRenderStepper>();
    auto mockContext = MockRenderCommon::GetMockContext();
    renderStepper->Attach(mockContext);

    /**
     * @tc.steps: step2. Run Update interface.
     * @tc.expected: step2. The index is correct.
     */
    Localization::GetInstance()->SetLocale("en", "US", "", "", "en-US");
    renderStepper->Update(stepperComponent);
    EXPECT_EQ(renderStepper->GetCurrentIndex(), 0);

    GTEST_LOG_(INFO) << "RenderStepperTest LoadDefaultButtonStatus005 stop";
}

/**
 * @tc.name: LoadDefaultButtonStatus006
 * @tc.desc: Test LoadDefaultButtonStatus for LTR
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderStepperTest, LoadDefaultButtonStatus006, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderStepperTest LoadDefaultButtonStatus006 start";
    
    /**
     * @tc.steps: step1. Construct StepperComponent and set text direction.
     */
    std::list<RefPtr<Component>> componentChildren;
    for (uint32_t i = 0; i < 2; i++) {
        RefPtr<StepperComponent> item = AceType::MakeRefPtr<StepperComponent>();
        componentChildren.emplace_back(item);
    }
    RefPtr<StepperComponent> stepperComponent = AceType::MakeRefPtr<StepperComponent>(componentChildren);
    stepperComponent->SetTextDirection(TextDirection::LTR);
    stepperComponent->SetIndex(0);
    std::vector<StepperLabels> stepperLabels;
    for (uint32_t i = 0; i < 2; i++) {
        StepperLabels labelItem;
        stepperLabels.emplace_back(labelItem);
    }
    stepperComponent->SetStepperLabels(stepperLabels);
    RefPtr<MockRenderStepper> renderStepper = AceType::MakeRefPtr<MockRenderStepper>();
    auto mockContext = MockRenderCommon::GetMockContext();
    renderStepper->Attach(mockContext);

    /**
     * @tc.steps: step2. Run Update interface.
     * @tc.expected: step2. The index is correct.
     */
    Localization::GetInstance()->SetLocale("en", "US", "", "", "en-US");
    renderStepper->Update(stepperComponent);
    EXPECT_EQ(renderStepper->GetCurrentIndex(), 0);

    GTEST_LOG_(INFO) << "RenderStepperTest LoadDefaultButtonStatus006 stop";
}

/**
 * @tc.name: LoadDefaultButtonStatus007
 * @tc.desc: Test LoadDefaultButtonStatus for LTR
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderStepperTest, LoadDefaultButtonStatus007, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderStepperTest LoadDefaultButtonStatus007 start";
    
    /**
     * @tc.steps: step1. Construct StepperComponent and set text direction.
     */
    std::list<RefPtr<Component>> componentChildren;
    for (uint32_t i = 0; i < 2; i++) {
        RefPtr<StepperComponent> item = AceType::MakeRefPtr<StepperComponent>();
        componentChildren.emplace_back(item);
    }
    RefPtr<StepperComponent> stepperComponent = AceType::MakeRefPtr<StepperComponent>(componentChildren);
    stepperComponent->SetTextDirection(TextDirection::LTR);
    stepperComponent->SetIndex(1);
    std::vector<StepperLabels> stepperLabels;
    for (uint32_t i = 0; i < 2; i++) {
        StepperLabels labelItem;
        stepperLabels.emplace_back(labelItem);
    }
    stepperComponent->SetStepperLabels(stepperLabels);
    RefPtr<MockRenderStepper> renderStepper = AceType::MakeRefPtr<MockRenderStepper>();
    auto mockContext = MockRenderCommon::GetMockContext();
    renderStepper->Attach(mockContext);

    /**
     * @tc.steps: step2. Run Update interface.
     * @tc.expected: step2. The index is correct.
     */
    Localization::GetInstance()->SetLocale("en", "US", "", "", "en-US");
    renderStepper->Update(stepperComponent);
    EXPECT_EQ(renderStepper->GetCurrentIndex(), 1);

    GTEST_LOG_(INFO) << "RenderStepperTest LoadDefaultButtonStatus007 stop";
}

/**
 * @tc.name: LoadDefaultButtonStatus008
 * @tc.desc: Test LoadDefaultButtonStatus for LTR
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderStepperTest, LoadDefaultButtonStatus008, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderStepperTest LoadDefaultButtonStatus008 start";
    
    /**
     * @tc.steps: step1. Construct StepperComponent and set text direction.
     */
    std::list<RefPtr<Component>> componentChildren;
    for (uint32_t i = 0; i < 5; i++) {
        RefPtr<StepperComponent> item = AceType::MakeRefPtr<StepperComponent>();
        componentChildren.emplace_back(item);
    }
    RefPtr<StepperComponent> stepperComponent = AceType::MakeRefPtr<StepperComponent>(componentChildren);
    stepperComponent->SetTextDirection(TextDirection::LTR);
    stepperComponent->SetIndex(2);
    std::vector<StepperLabels> stepperLabels;
    for (uint32_t i = 0; i < 5; i++) {
        StepperLabels labelItem;
        stepperLabels.emplace_back(labelItem);
    }
    stepperComponent->SetStepperLabels(stepperLabels);
    RefPtr<MockRenderStepper> renderStepper = AceType::MakeRefPtr<MockRenderStepper>();
    auto mockContext = MockRenderCommon::GetMockContext();
    renderStepper->Attach(mockContext);

    /**
     * @tc.steps: step2. Run Update interface.
     * @tc.expected: step2. The index is correct.
     */
    Localization::GetInstance()->SetLocale("en", "US", "", "", "en-US");
    renderStepper->Update(stepperComponent);
    EXPECT_EQ(renderStepper->GetCurrentIndex(), 2);

    GTEST_LOG_(INFO) << "RenderStepperTest LoadDefaultButtonStatus008 stop";
}

/**
 * @tc.name: GetPrevIndex001
 * @tc.desc: Test GetPrevIndex
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderStepperTest, GetPrevIndex001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderStepperTest GetPrevIndex001 start";

    /**
     * @tc.steps: step1. Construct StepperComponent and set left buttonStatus NORMAL.
     */
    ControlPanelData data;
    data.buttonStatus = StepperButtonStatus::NORMAL;
    RefPtr<MockRenderStepper> renderStepper = AceType::MakeRefPtr<MockRenderStepper>();
    renderStepper->SetLeftButtonData(data);

    /**
     * @tc.steps: step2. Set reverse true.
     */
    renderStepper->SetNeedReverse(true);

    /**
     * @tc.steps: step3. Set current index -1 and total item count 1.
     */
    renderStepper->SetCurrentIndex(-1);
    renderStepper->SetTotalItemCount(1);

    /**
     * @tc.steps: step4. Run HandleButtonClick interface by param true.
     * @tc.expected: step4. The index is 0.
     */
    renderStepper->HandleButtonClick(true);
    EXPECT_EQ(renderStepper->GetCurrentIndex(), 0);

    GTEST_LOG_(INFO) << "RenderStepperTest GetPrevIndex001 stop";
}

/**
 * @tc.name: GetPrevIndex002
 * @tc.desc: Test GetPrevIndex
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderStepperTest, GetPrevIndex002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderStepperTest GetPrevIndex002 start";

    /**
     * @tc.steps: step1. Construct StepperComponent and set left buttonStatus NORMAL.
     */
    ControlPanelData data;
    data.buttonStatus = StepperButtonStatus::NORMAL;
    RefPtr<MockRenderStepper> renderStepper = AceType::MakeRefPtr<MockRenderStepper>();
    renderStepper->SetLeftButtonData(data);

    /**
     * @tc.steps: step2. Set reverse true.
     */
    renderStepper->SetNeedReverse(true);

    /**
     * @tc.steps: step3. Set current index 1 and total item count 0.
     */
    renderStepper->SetCurrentIndex(1);
    renderStepper->SetTotalItemCount(0);

    /**
     * @tc.steps: step4. Run HandleButtonClick interface by param true.
     * @tc.expected: step4. The index is 0.
     */
    renderStepper->HandleButtonClick(true);
    EXPECT_EQ(renderStepper->GetCurrentIndex(), 0);

    GTEST_LOG_(INFO) << "RenderStepperTest GetPrevIndex002 stop";
}

/**
 * @tc.name: GetPrevIndex003
 * @tc.desc: Test GetPrevIndex
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderStepperTest, GetPrevIndex003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderStepperTest GetPrevIndex003 start";

    /**
     * @tc.steps: step1. Construct StepperComponent and set reverse false.
     */
    RefPtr<MockRenderStepper> renderStepper = AceType::MakeRefPtr<MockRenderStepper>();
    renderStepper->SetNeedReverse(false);

    /**
     * @tc.steps: step2. Set current index 2 and total item count 5.
     */
    renderStepper->SetCurrentIndex(2);
    renderStepper->SetTotalItemCount(5);

    /**
     * @tc.steps: step3. Run HandleButtonClick interface by param true.
     * @tc.expected: step3. The index is 0.
     */
    renderStepper->HandleButtonClick(true);
    EXPECT_EQ(renderStepper->GetCurrentIndex(), 1);

    GTEST_LOG_(INFO) << "RenderStepperTest GetPrevIndex003 stop";
}

/**
 * @tc.name: GetPrevIndex004
 * @tc.desc: Test GetPrevIndex
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderStepperTest, GetPrevIndex004, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderStepperTest GetPrevIndex004 start";

    /**
     * @tc.steps: step1. Construct StepperComponent and set reverse false.
     */
    RefPtr<MockRenderStepper> renderStepper = AceType::MakeRefPtr<MockRenderStepper>();
    renderStepper->SetNeedReverse(false);

    /**
     * @tc.steps: step2. Set current index 0 and total item count 5.
     */
    renderStepper->SetCurrentIndex(0);
    renderStepper->SetTotalItemCount(5);

    /**
     * @tc.steps: step3. Run HandleButtonClick interface by param true.
     * @tc.expected: step3. The index is 0.
     */
    renderStepper->HandleButtonClick(true);
    EXPECT_EQ(renderStepper->GetCurrentIndex(), 0);

    GTEST_LOG_(INFO) << "RenderStepperTest GetPrevIndex004 stop";
}

/**
 * @tc.name: GetNextIndex001
 * @tc.desc: Test GetNextIndex
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderStepperTest, GetNextIndex001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderStepperTest GetNextIndex001 start";

    /**
     * @tc.steps: step1. Construct StepperComponent and set right buttonStatus NORMAL.
     */
    ControlPanelData data;
    data.buttonStatus = StepperButtonStatus::NORMAL;
    RefPtr<MockRenderStepper> renderStepper = AceType::MakeRefPtr<MockRenderStepper>();
    renderStepper->SetRightButtonData(data);

    /**
     * @tc.steps: step2. Set reverse true.
     */
    renderStepper->SetNeedReverse(true);

    /**
     * @tc.steps: step3. Set current index 0 and total item count 1.
     */
    renderStepper->SetCurrentIndex(0);
    renderStepper->SetTotalItemCount(1);

    /**
     * @tc.steps: step4. Run HandleButtonClick interface by param false.
     * @tc.expected: step4. The index is 0.
     */
    renderStepper->HandleButtonClick(false);
    EXPECT_EQ(renderStepper->GetCurrentIndex(), 0);

    GTEST_LOG_(INFO) << "RenderStepperTest GetNextIndex001 stop";
}

/**
 * @tc.name: GetNextIndex002
 * @tc.desc: Test GetNextIndex
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderStepperTest, GetNextIndex002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderStepperTest GetNextIndex002 start";

    /**
     * @tc.steps: step1. Construct StepperComponent.
     */
    RefPtr<MockRenderStepper> renderStepper = AceType::MakeRefPtr<MockRenderStepper>();

    /**
     * @tc.steps: step2. Set reverse false.
     */
    renderStepper->SetNeedReverse(false);

    /**
     * @tc.steps: step3. Set current index 2 and total item count 2.
     */
    renderStepper->SetCurrentIndex(2);
    renderStepper->SetTotalItemCount(2);

    /**
     * @tc.steps: step4. Run HandleButtonClick interface by param false.
     * @tc.expected: step4. The index is 1.
     */
    renderStepper->HandleButtonClick(false);
    EXPECT_EQ(renderStepper->GetCurrentIndex(), 1);

    GTEST_LOG_(INFO) << "RenderStepperTest GetNextIndex002 stop";
}

/**
 * @tc.name: HandleClick001
 * @tc.desc: Test HandleClick
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderStepperTest, HandleClick001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderStepperTest HandleClick001 start";

    /**
     * @tc.steps: step1. Construct StepperComponent.
     */
    RefPtr<MockRenderStepper> renderStepper = AceType::MakeRefPtr<MockRenderStepper>();

    /**
     * @tc.steps: step2. Set  Left and Right Button Data.
     */
    ControlPanelData data;
    Rect rect(-50.0, -50.0, 100.0, 100.0);
    data.displayRender = AceType::MakeRefPtr<RenderDisplay>();
    data.displayRender->SetPaintRect(rect);
    renderStepper->SetLeftButtonData(data);
    renderStepper->SetRightButtonData(data);

    /**
     * @tc.steps: step3. Set reverse true.
     */
    renderStepper->SetNeedReverse(true);

    /**
     * @tc.steps: step3. Set current index 0 and total item count 2.
     */
    renderStepper->SetCurrentIndex(0);
    renderStepper->SetTotalItemCount(2);

    /**
     * @tc.steps: step4. Run HandleClick function.
     * @tc.expected: step4. The index is 0.
     */
    ClickInfo clickInfo(0);
    renderStepper->MockHandleClick(clickInfo);
    EXPECT_EQ(renderStepper->GetCurrentIndex(), 0);
    GTEST_LOG_(INFO) << "RenderStepperTest HandleClick001 stop";
}

/**
 * @tc.name: HandleClick002
 * @tc.desc: Test HandleClick
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderStepperTest, HandleClick002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderStepperTest HandleClick002 start";

    /**
     * @tc.steps: step1. Construct StepperComponent.
     */
    RefPtr<MockRenderStepper> renderStepper = AceType::MakeRefPtr<MockRenderStepper>();

    /**
     * @tc.steps: step2. Set Left and Right Button Data.
     */
    ControlPanelData data;
    Rect rect(-50.0, -50.0, 100.0, 100.0);
    data.displayRender = AceType::MakeRefPtr<RenderDisplay>();
    data.displayRender->SetPaintRect(rect);
    renderStepper->SetLeftButtonData(data);
    renderStepper->SetRightButtonData(data);

    /**
     * @tc.steps: step3. Set reverse false.
     */
    renderStepper->SetNeedReverse(false);

    /**
     * @tc.steps: step3. Set current index 0 and total item count 2.
     */
    renderStepper->SetCurrentIndex(0);
    renderStepper->SetTotalItemCount(2);

    /**
     * @tc.steps: step4. Run HandleClick function.
     * @tc.expected: step4. The index is 0.
     */
    ClickInfo clickInfo(0);
    renderStepper->MockHandleClick(clickInfo);
    EXPECT_EQ(renderStepper->GetCurrentIndex(), 1);
    GTEST_LOG_(INFO) << "RenderStepperTest HandleClick002 stop";
}

/**
 * @tc.name: HandleLeftButtonClick001
 * @tc.desc: Test HandleLeftButtonClick
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderStepperTest, HandleLeftButtonClick001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderStepperTest HandleLeftButtonClick001 start";

    /**
     * @tc.steps: step1. Construct StepperComponent and set left buttonStatus NORMAL.
     */
    RefPtr<MockRenderStepper> renderStepper = AceType::MakeRefPtr<MockRenderStepper>();
    ControlPanelData data;
    data.buttonStatus = StepperButtonStatus::NORMAL;
    renderStepper->SetLeftButtonData(data);

    /**
     * @tc.steps: step2. Set reverse true.
     */
    renderStepper->SetNeedReverse(true);

    /**
     * @tc.steps: step3. Set current index 0 and total item count 2.
     */
    renderStepper->SetCurrentIndex(0);
    renderStepper->SetTotalItemCount(2);

    /**
     * @tc.steps: step4. Run HandleButtonClick interface by param true.
     * @tc.expected: step4. The index is 1.
     */
    renderStepper->HandleButtonClick(true);
    EXPECT_EQ(renderStepper->GetCurrentIndex(), 1);

    GTEST_LOG_(INFO) << "RenderStepperTest HandleLeftButtonClick001 stop";
}

/**
 * @tc.name: HandleLeftButtonClick002
 * @tc.desc: Test HandleLeftButtonClick
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderStepperTest, HandleLeftButtonClick002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderStepperTest HandleLeftButtonClick002 start";

    /**
     * @tc.steps: step1. Construct StepperComponent and set left buttonStatus NORMAL.
     */
    RefPtr<MockRenderStepper> renderStepper = AceType::MakeRefPtr<MockRenderStepper>();
    ControlPanelData data;
    data.buttonStatus = StepperButtonStatus::NORMAL;
    renderStepper->SetLeftButtonData(data);

    /**
     * @tc.steps: step2. Set reverse true.
     */
    renderStepper->SetNeedReverse(true);

    /**
     * @tc.steps: step3. Set current index 1 and total item count 2.
     */
    renderStepper->SetCurrentIndex(1);
    renderStepper->SetTotalItemCount(2);

    /**
     * @tc.steps: step4. Run HandleButtonClick interface by param true.
     * @tc.expected: step4. The index is 1.
     */
    renderStepper->HandleButtonClick(true);
    EXPECT_EQ(renderStepper->GetCurrentIndex(), 1);

    GTEST_LOG_(INFO) << "RenderStepperTest HandleLeftButtonClick002 stop";
}

/**
 * @tc.name: HandleLeftButtonClick003
 * @tc.desc: Test HandleLeftButtonClick
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderStepperTest, HandleLeftButtonClick003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderStepperTest HandleLeftButtonClick003 start";

    /**
     * @tc.steps: step1. Construct StepperComponent and set left buttonStatus SKIP.
     */
    RefPtr<MockRenderStepper> renderStepper = AceType::MakeRefPtr<MockRenderStepper>();
    ControlPanelData data;
    data.buttonStatus = StepperButtonStatus::SKIP;
    renderStepper->SetLeftButtonData(data);

    /**
     * @tc.steps: step2. Set reverse true.
     */
    renderStepper->SetNeedReverse(true);

    /**
     * @tc.steps: step3. Set current index 0 and total item count 2.
     */
    renderStepper->SetCurrentIndex(0);
    renderStepper->SetTotalItemCount(2);

    /**
     * @tc.steps: step4. Run HandleButtonClick interface by param true.
     * @tc.expected: step4. The index is 0.
     */
    renderStepper->HandleButtonClick(true);
    EXPECT_EQ(renderStepper->GetCurrentIndex(), 0);

    GTEST_LOG_(INFO) << "RenderStepperTest HandleLeftButtonClick003 stop";
}

/**
 * @tc.name: HandleLeftButtonClick004
 * @tc.desc: Test HandleLeftButtonClick
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderStepperTest, HandleLeftButtonClick004, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderStepperTest HandleLeftButtonClick004 start";

    /**
     * @tc.steps: step1. Construct StepperComponent and set left buttonStatus DISABLED.
     */
    RefPtr<MockRenderStepper> renderStepper = AceType::MakeRefPtr<MockRenderStepper>();
    ControlPanelData data;
    data.buttonStatus = StepperButtonStatus::DISABLED;
    renderStepper->SetLeftButtonData(data);

    /**
     * @tc.steps: step2. Set reverse true.
     */
    renderStepper->SetNeedReverse(true);

    /**
     * @tc.steps: step3. Set current index 0 and total item count 2.
     */
    renderStepper->SetCurrentIndex(0);
    renderStepper->SetTotalItemCount(2);

    /**
     * @tc.steps: step4. Run HandleButtonClick interface by param true.
     * @tc.expected: step4. The index is 0.
     */
    renderStepper->HandleButtonClick(true);
    EXPECT_EQ(renderStepper->GetCurrentIndex(), 0);

    GTEST_LOG_(INFO) << "RenderStepperTest HandleLeftButtonClick004 stop";
}

/**
 * @tc.name: HandleLeftButtonClick005
 * @tc.desc: Test HandleLeftButtonClick
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderStepperTest, HandleLeftButtonClick005, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderStepperTest HandleLeftButtonClick005 start";

    /**
     * @tc.steps: step1. Construct StepperComponent and set left buttonStatus WAITING.
     */
    RefPtr<MockRenderStepper> renderStepper = AceType::MakeRefPtr<MockRenderStepper>();
    ControlPanelData data;
    data.buttonStatus = StepperButtonStatus::WAITING;
    renderStepper->SetLeftButtonData(data);

    /**
     * @tc.steps: step2. Set reverse true.
     */
    renderStepper->SetNeedReverse(true);

    /**
     * @tc.steps: step3. Set current index 0 and total item count 2.
     */
    renderStepper->SetCurrentIndex(0);
    renderStepper->SetTotalItemCount(2);

    /**
     * @tc.steps: step4. Run HandleButtonClick interface by param true.
     * @tc.expected: step4. The index is 0.
     */
    renderStepper->HandleButtonClick(true);
    EXPECT_EQ(renderStepper->GetCurrentIndex(), 0);

    GTEST_LOG_(INFO) << "RenderStepperTest HandleLeftButtonClick005 stop";
}

} // namespace OHOS::Ace
