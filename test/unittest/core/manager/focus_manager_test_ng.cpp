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

#include <optional>

#include "gtest/gtest.h"
#define private public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/manager/focus/focus_manager.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SIZE_1 = 1;
} // namespace

class FocusManagerTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void FocusManagerTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void FocusManagerTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: FocusManagerTest001
 * @tc.desc: Create FocusManager
 * @tc.type: FUNC
 * @tc.author: catpoison
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FocusManager
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>();
    EXPECT_TRUE(focusManager->focusViewStack_.empty());

    /**
     * @tc.steps: step2. lastFocusView_ is nullptr. GetWeakFocusViewList() is empty.
     */
    EXPECT_FALSE(focusManager->lastFocusView_.Upgrade());
    EXPECT_TRUE(focusManager->GetWeakFocusViewList().empty());
}

/**
 * @tc.name: FocusManagerTest002
 * @tc.desc: FocusViewShow / FocusViewHide / FocusViewClose
 * @tc.type: FUNC
 * @tc.author: catpoison
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FocusManager and a FocusView
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>();

    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, -1, AceType::MakeRefPtr<RootPattern>());
    auto rootFocusHub = rootNode->GetOrCreateFocusHub();

    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    rootNode->AddChild(pageNode);

    /**
     * @tc.steps: step2. Do FocusViewShow. lastFocusView is focusView. GetWeakFocusViewList().size == 1
     */
    focusManager->FocusViewShow(pagePattern);
    EXPECT_EQ(focusManager->lastFocusView_.Upgrade(), pagePattern);
    EXPECT_EQ(focusManager->GetWeakFocusViewList().size(), SIZE_1);

    /**
     * @tc.steps: step3. Do FocusViewHide. lastFocusView is nullptr. GetWeakFocusViewList().size == 1
     */
    focusManager->FocusViewHide(pagePattern);
    EXPECT_EQ(focusManager->lastFocusView_.Upgrade(), nullptr);
    EXPECT_EQ(focusManager->GetWeakFocusViewList().size(), SIZE_1);

    /**
     * @tc.steps: step4. Do FocusViewClose. lastFocusView is nullptr. GetWeakFocusViewList().size == 0
     */
    focusManager->FocusViewShow(pagePattern);
    focusManager->FocusViewClose(pagePattern);
    EXPECT_EQ(focusManager->lastFocusView_.Upgrade(), nullptr);
    EXPECT_TRUE(focusManager->GetWeakFocusViewList().empty());
}

/**
 * @tc.name: FocusManagerTest003
 * @tc.desc: SetRequestFocusCallback / TriggerRequestFocusCallback
 * @tc.type: FUNC
 */
HWTEST_F(FocusManagerTestNg, FocusManagerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a FocusManager.
     */
    auto focusManager = AceType::MakeRefPtr<FocusManager>();

    /**
     * @tc.steps: step2. call SetRequestFocusCallback and TriggerRequestFocusCallback.
     */
    bool flag = false;
    RequestFocusCallback requestFocusCallback = [&flag](NG::RequestFocusResult result) { flag = !flag; };
    focusManager->SetRequestFocusCallback(requestFocusCallback);
    focusManager->TriggerRequestFocusCallback(NG::RequestFocusResult::DEFAULT);
    EXPECT_TRUE(flag);

    /**
     * @tc.steps: step3. TriggerRequestFocusCallback again.
     */
    focusManager->TriggerRequestFocusCallback(NG::RequestFocusResult::DEFAULT);
    EXPECT_TRUE(flag);
}
} // namespace OHOS::Ace::NG
