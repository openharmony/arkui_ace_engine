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
#include "bridge/card_frontend/card_frontend_delegate.h"
#undef private
#undef protected
#include "bridge/common/utils/utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::Framework {
class CardFrontendDelegateTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void CardFrontendDelegateTest::SetUpTestCase() {}
void CardFrontendDelegateTest::TearDownTestCase() {}
void CardFrontendDelegateTest::SetUp() {}
void CardFrontendDelegateTest::TearDown() {}

/**
 * @tc.name: FireCardEvent001
 * @tc.desc: Test card frontend delegate FireCardEvent method.
 * @tc.type: FUNC
 */
HWTEST_F(CardFrontendDelegateTest, FireCardEvent001, TestSize.Level1)
{
    auto cardFrontendDelegate = AceType::MakeRefPtr<CardFrontendDelegate>();
    EventMarker event;
    cardFrontendDelegate->CreatePage(1, ""), cardFrontendDelegate->FireCardEvent(event, "");
    cardFrontendDelegate->FireCardEvent(event, "test");
    auto page = cardFrontendDelegate->GetPage();
    ASSERT_NE(page, nullptr);
}

/**
 * @tc.name: CreatePage001
 * @tc.desc: Test card frontend delegate CreatePage method.
 * @tc.type: FUNC
 */
HWTEST_F(CardFrontendDelegateTest, CreatePage001, TestSize.Level1)
{
    auto cardFrontendDelegate = AceType::MakeRefPtr<CardFrontendDelegate>();
    cardFrontendDelegate->CreatePage(1, "", nullptr);
    auto page = cardFrontendDelegate->GetPage();
    ASSERT_NE(page, nullptr);
}

/**
 * @tc.name: GetPage001
 * @tc.desc: Test card frontend delegate GetPage method.
 * @tc.type: FUNC
 */
HWTEST_F(CardFrontendDelegateTest, GetPage001, TestSize.Level1)
{
    auto cardFrontendDelegate = AceType::MakeRefPtr<CardFrontendDelegate>();
    cardFrontendDelegate->CreatePage(1, "", nullptr);
    auto page = cardFrontendDelegate->GetPage();
    ASSERT_NE(page, nullptr);
}
} // namespace OHOS::Ace::Framework