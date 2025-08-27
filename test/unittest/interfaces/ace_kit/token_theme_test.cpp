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

#include "gtest/gtest.h"

#include "ui/view/theme/token_theme.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class TokenThemeTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
    void SetUp() {};
    void TearDown() {};
};

/**
 * @tc.name: ResourceParserTestTest001
 * @tc.desc: Test GetDimension when option is empty
 * @tc.type: Func
 */
HWTEST_F(TokenThemeTest, TokenThemeTest001, TestSize.Level1)
{
    auto tokenTheme = AceType::MakeRefPtr<TokenTheme>(1);
    EXPECT_EQ(tokenTheme->GetId(), 1);
    tokenTheme->SetColorMode(ColorMode::LIGHT);
    EXPECT_EQ(tokenTheme->GetColorMode(), ColorMode::LIGHT);
}

} // namespace OHOS::Ace
