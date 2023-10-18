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

#include "base/test/mock/mock_asset_manager.h"
#include "core/components/test/unittest/mock/mock_render_common.h"
#define private public
#define protected public
#include "bridge/card_frontend/card_frontend_declarative.h"
#undef private
#undef protected
#include "base/test/mock/mock_task_executor.h"
#include "bridge/common/utils/utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::Framework {
class CardFrontendDeclarativeTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void CardFrontendDeclarativeTest::SetUpTestCase() {}
void CardFrontendDeclarativeTest::TearDownTestCase() {}
void CardFrontendDeclarativeTest::SetUp() {}
void CardFrontendDeclarativeTest::TearDown() {}

/**
 * @tc.name: Initialize001
 * @tc.desc: Test card frontend declarative Initialize method.
 * @tc.type: FUNC
 */
HWTEST_F(CardFrontendDeclarativeTest, Initialize001, TestSize.Level1)
{
    auto cardFrontend = AceType::MakeRefPtr<CardFrontendDeclarative>();
    auto taskExecutor = Referenced::MakeRefPtr<MockTaskExecutor>();
    cardFrontend->Initialize(FrontendType::JS_CARD, taskExecutor);
    ASSERT_NE(cardFrontend->taskExecutor_, nullptr);
    ASSERT_NE(cardFrontend->delegate_, nullptr);
    ASSERT_NE(cardFrontend->manifestParser_, nullptr);
    ASSERT_EQ(cardFrontend->type_, FrontendType::JS_CARD);
}

/**
 * @tc.name: GetPageRouterManager001
 * @tc.desc: Test card frontend declarative GetPageRouterManager method.
 * @tc.type: FUNC
 */
HWTEST_F(CardFrontendDeclarativeTest, GetPageRouterManager001, TestSize.Level1)
{
    auto cardFrontend = AceType::MakeRefPtr<CardFrontendDeclarative>();
    auto taskExecutor = Referenced::MakeRefPtr<MockTaskExecutor>();
    cardFrontend->Initialize(FrontendType::JS_CARD, taskExecutor);
    ASSERT_NE(cardFrontend->taskExecutor_, nullptr);
    ASSERT_NE(cardFrontend->delegate_, nullptr);
    ASSERT_NE(cardFrontend->manifestParser_, nullptr);
    ASSERT_EQ(cardFrontend->type_, FrontendType::JS_CARD);
    auto manager = cardFrontend->GetPageRouterManager();
    ASSERT_NE(manager, nullptr);
}

/**
 * @tc.name: Destroy001
 * @tc.desc: Test card frontend declarative Destroy method.
 * @tc.type: FUNC
 */
HWTEST_F(CardFrontendDeclarativeTest, Destroy001, TestSize.Level1)
{
    auto cardFrontend = AceType::MakeRefPtr<CardFrontendDeclarative>();
    auto taskExecutor = Referenced::MakeRefPtr<MockTaskExecutor>();
    cardFrontend->Initialize(FrontendType::JS_CARD, taskExecutor);
    ASSERT_NE(cardFrontend->taskExecutor_, nullptr);
    ASSERT_NE(cardFrontend->delegate_, nullptr);
    ASSERT_NE(cardFrontend->manifestParser_, nullptr);
    ASSERT_EQ(cardFrontend->type_, FrontendType::JS_CARD);
    cardFrontend->Destroy();
    ASSERT_EQ(cardFrontend->delegate_, nullptr);
    ASSERT_EQ(cardFrontend->eventHandler_, nullptr);
}

/**
 * @tc.name: AttachPipelineContext001
 * @tc.desc: Test card frontend declarative AttachPipelineContext method.
 * @tc.type: FUNC
 */
HWTEST_F(CardFrontendDeclarativeTest, AttachPipelineContext001, TestSize.Level1)
{
    auto cardFrontend = AceType::MakeRefPtr<CardFrontendDeclarative>();
    auto taskExecutor = Referenced::MakeRefPtr<MockTaskExecutor>();
    cardFrontend->Initialize(FrontendType::JS_CARD, taskExecutor);
    ASSERT_NE(cardFrontend->taskExecutor_, nullptr);
    ASSERT_NE(cardFrontend->delegate_, nullptr);
    ASSERT_NE(cardFrontend->manifestParser_, nullptr);
    ASSERT_EQ(cardFrontend->type_, FrontendType::JS_CARD);
    auto pipeline = MockRenderCommon::GetMockContext();
    cardFrontend->AttachPipelineContext(pipeline);
    ASSERT_EQ(cardFrontend->eventHandler_, nullptr);
    cardFrontend->AttachPipelineContext(nullptr);
    ASSERT_EQ(cardFrontend->eventHandler_, nullptr);
}

/**
 * @tc.name: SetAssetManager001
 * @tc.desc: Test card frontend declarative SetAssetManager method.
 * @tc.type: FUNC
 */
HWTEST_F(CardFrontendDeclarativeTest, SetAssetManager001, TestSize.Level1)
{
    auto cardFrontend = AceType::MakeRefPtr<CardFrontendDeclarative>();
    auto taskExecutor = Referenced::MakeRefPtr<MockTaskExecutor>();
    cardFrontend->Initialize(FrontendType::JS_CARD, taskExecutor);
    ASSERT_NE(cardFrontend->taskExecutor_, nullptr);
    ASSERT_NE(cardFrontend->delegate_, nullptr);
    ASSERT_NE(cardFrontend->manifestParser_, nullptr);
    ASSERT_EQ(cardFrontend->type_, FrontendType::JS_CARD);
    auto assetManager = Referenced::MakeRefPtr<MockAssetManager>();
    cardFrontend->SetAssetManager(assetManager);
    ASSERT_NE(cardFrontend->assetManager_, nullptr);
}

/**
 * @tc.name: RunPage001
 * @tc.desc: Test card frontend declarative RunPage method.
 * @tc.type: FUNC
 */
HWTEST_F(CardFrontendDeclarativeTest, RunPage001, TestSize.Level1)
{
    auto cardFrontend = AceType::MakeRefPtr<CardFrontendDeclarative>();
    auto taskExecutor = Referenced::MakeRefPtr<MockTaskExecutor>();
    cardFrontend->Initialize(FrontendType::JS_CARD, taskExecutor);
    ASSERT_NE(cardFrontend->taskExecutor_, nullptr);
    ASSERT_NE(cardFrontend->delegate_, nullptr);
    ASSERT_NE(cardFrontend->manifestParser_, nullptr);
    ASSERT_EQ(cardFrontend->type_, FrontendType::JS_CARD);
    cardFrontend->RunPage("", "");
    cardFrontend->RunPage("test", "test");
    cardFrontend->RunPage("", "test");
    cardFrontend->RunPage("test", "");
    ASSERT_NE(cardFrontend->taskExecutor_, nullptr);
    ASSERT_NE(cardFrontend->delegate_, nullptr);
    ASSERT_NE(cardFrontend->manifestParser_, nullptr);
    ASSERT_EQ(cardFrontend->type_, FrontendType::JS_CARD);
}

/**
 * @tc.name: UpdateData001
 * @tc.desc: Test card frontend declarative UpdateData method.
 * @tc.type: FUNC
 */
HWTEST_F(CardFrontendDeclarativeTest, UpdateData001, TestSize.Level1)
{
    auto cardFrontend = AceType::MakeRefPtr<CardFrontendDeclarative>();
    auto taskExecutor = Referenced::MakeRefPtr<MockTaskExecutor>();
    cardFrontend->Initialize(FrontendType::JS_CARD, taskExecutor);
    ASSERT_NE(cardFrontend->taskExecutor_, nullptr);
    ASSERT_NE(cardFrontend->delegate_, nullptr);
    ASSERT_NE(cardFrontend->manifestParser_, nullptr);
    ASSERT_EQ(cardFrontend->type_, FrontendType::JS_CARD);
    cardFrontend->UpdateData("");
    cardFrontend->UpdateData("test");
    ASSERT_NE(cardFrontend->taskExecutor_, nullptr);
    ASSERT_NE(cardFrontend->delegate_, nullptr);
    ASSERT_NE(cardFrontend->manifestParser_, nullptr);
    ASSERT_EQ(cardFrontend->type_, FrontendType::JS_CARD);
}

/**
 * @tc.name: UpdatePageData001
 * @tc.desc: Test card frontend declarative UpdatePageData method.
 * @tc.type: FUNC
 */
HWTEST_F(CardFrontendDeclarativeTest, UpdatePageData001, TestSize.Level1)
{
    auto cardFrontend = AceType::MakeRefPtr<CardFrontendDeclarative>();
    auto taskExecutor = Referenced::MakeRefPtr<MockTaskExecutor>();
    cardFrontend->Initialize(FrontendType::JS_CARD, taskExecutor);
    ASSERT_NE(cardFrontend->taskExecutor_, nullptr);
    ASSERT_NE(cardFrontend->delegate_, nullptr);
    ASSERT_NE(cardFrontend->manifestParser_, nullptr);
    ASSERT_EQ(cardFrontend->type_, FrontendType::JS_CARD);
    cardFrontend->UpdatePageData("");
    cardFrontend->UpdatePageData("test");
    cardFrontend->delegate_ = nullptr;
    cardFrontend->parseJsCard_ = nullptr;
    cardFrontend->UpdatePageData("test");
    ASSERT_EQ(cardFrontend->delegate_, nullptr);
    ASSERT_EQ(cardFrontend->parseJsCard_, nullptr);
}

/**
 * @tc.name: SetColorMode001
 * @tc.desc: Test card frontend declarative SetColorMode method.
 * @tc.type: FUNC
 */
HWTEST_F(CardFrontendDeclarativeTest, SetColorMode001, TestSize.Level1)
{
    auto cardFrontend = AceType::MakeRefPtr<CardFrontendDeclarative>();
    auto taskExecutor = Referenced::MakeRefPtr<MockTaskExecutor>();
    cardFrontend->Initialize(FrontendType::JS_CARD, taskExecutor);
    ASSERT_NE(cardFrontend->taskExecutor_, nullptr);
    ASSERT_NE(cardFrontend->delegate_, nullptr);
    ASSERT_NE(cardFrontend->manifestParser_, nullptr);
    ASSERT_EQ(cardFrontend->type_, FrontendType::JS_CARD);
    cardFrontend->SetColorMode(ColorMode::LIGHT);
    ASSERT_EQ(cardFrontend->colorMode_, ColorMode::LIGHT);
}

/**
 * @tc.name: OnSurfaceChanged001
 * @tc.desc: Test card frontend declarative OnSurfaceChanged method.
 * @tc.type: FUNC
 */
HWTEST_F(CardFrontendDeclarativeTest, OnSurfaceChanged001, TestSize.Level1)
{
    auto cardFrontend = AceType::MakeRefPtr<CardFrontendDeclarative>();
    auto taskExecutor = Referenced::MakeRefPtr<MockTaskExecutor>();
    cardFrontend->Initialize(FrontendType::JS_CARD, taskExecutor);
    ASSERT_NE(cardFrontend->taskExecutor_, nullptr);
    ASSERT_NE(cardFrontend->delegate_, nullptr);
    ASSERT_NE(cardFrontend->manifestParser_, nullptr);
    ASSERT_EQ(cardFrontend->type_, FrontendType::JS_CARD);
    cardFrontend->OnSurfaceChanged(0, 0);
    cardFrontend->OnSurfaceChanged(100, 100);
    cardFrontend->OnSurfaceChanged(-100, -100);
    ASSERT_NE(cardFrontend->taskExecutor_, nullptr);
    ASSERT_NE(cardFrontend->delegate_, nullptr);
    ASSERT_NE(cardFrontend->manifestParser_, nullptr);
    ASSERT_EQ(cardFrontend->type_, FrontendType::JS_CARD);
}

/**
 * @tc.name: HandleSurfaceChanged001
 * @tc.desc: Test card frontend declarative HandleSurfaceChanged method.
 * @tc.type: FUNC
 */
HWTEST_F(CardFrontendDeclarativeTest, HandleSurfaceChanged001, TestSize.Level1)
{
    auto cardFrontend = AceType::MakeRefPtr<CardFrontendDeclarative>();
    auto taskExecutor = Referenced::MakeRefPtr<MockTaskExecutor>();
    cardFrontend->Initialize(FrontendType::JS_CARD, taskExecutor);
    ASSERT_NE(cardFrontend->taskExecutor_, nullptr);
    ASSERT_NE(cardFrontend->delegate_, nullptr);
    ASSERT_NE(cardFrontend->manifestParser_, nullptr);
    ASSERT_EQ(cardFrontend->type_, FrontendType::JS_CARD);
    cardFrontend->HandleSurfaceChanged(0, 0);
    cardFrontend->HandleSurfaceChanged(100, 100);
    cardFrontend->HandleSurfaceChanged(-100, -100);
    ASSERT_NE(cardFrontend->taskExecutor_, nullptr);
    ASSERT_NE(cardFrontend->delegate_, nullptr);
    ASSERT_NE(cardFrontend->manifestParser_, nullptr);
    ASSERT_EQ(cardFrontend->type_, FrontendType::JS_CARD);
}

/**
 * @tc.name: OnMediaFeatureUpdate001
 * @tc.desc: Test card frontend declarative OnMediaFeatureUpdate method.
 * @tc.type: FUNC
 */
HWTEST_F(CardFrontendDeclarativeTest, OnMediaFeatureUpdate001, TestSize.Level1)
{
    auto cardFrontend = AceType::MakeRefPtr<CardFrontendDeclarative>();
    auto taskExecutor = Referenced::MakeRefPtr<MockTaskExecutor>();
    cardFrontend->Initialize(FrontendType::JS_CARD, taskExecutor);
    ASSERT_NE(cardFrontend->taskExecutor_, nullptr);
    ASSERT_NE(cardFrontend->delegate_, nullptr);
    ASSERT_NE(cardFrontend->manifestParser_, nullptr);
    ASSERT_EQ(cardFrontend->type_, FrontendType::JS_CARD);
    cardFrontend->OnMediaFeatureUpdate();
    ASSERT_NE(cardFrontend->taskExecutor_, nullptr);
    ASSERT_NE(cardFrontend->delegate_, nullptr);
    ASSERT_NE(cardFrontend->manifestParser_, nullptr);
    ASSERT_EQ(cardFrontend->type_, FrontendType::JS_CARD);
}
} // namespace OHOS::Ace::Framework