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

#include "core/components_ng/token_theme/token_theme_storage.h"
#include "ui/view/theme/token_theme.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class TokenThemeTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
    void SetUp() override
    {
        auto storage = NG::TokenThemeStorage::GetInstance();
        storage->CacheClear();
        storage->RemoveThemeScope(THEME_SCOPE_ID_1, false);
        storage->RemoveThemeScope(THEME_SCOPE_ID_2, false);
        storage->RemoveThemeScope(MISSING_THEME_SCOPE_ID, false);
    }

    void TearDown() override
    {
        auto storage = NG::TokenThemeStorage::GetInstance();
        storage->CacheClear();
        storage->RemoveThemeScope(THEME_SCOPE_ID_1, false);
        storage->RemoveThemeScope(THEME_SCOPE_ID_2, false);
        storage->RemoveThemeScope(MISSING_THEME_SCOPE_ID, false);
    }

protected:
    static constexpr int32_t THEME_ID_1 = 1001;
    static constexpr int32_t THEME_ID_2 = 1002;
    static constexpr int32_t MISSING_THEME_ID = 1999;
    static constexpr int32_t THEME_SCOPE_ID_1 = 2001;
    static constexpr int32_t THEME_SCOPE_ID_2 = 2002;
    static constexpr int32_t MISSING_THEME_SCOPE_ID = 2999;
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

/**
 * @tc.name: TokenThemeStorageGetThemeMiss001
 * @tc.desc: Verify querying a missing theme scope does not create side effects.
 * @tc.type: Func
 */
HWTEST_F(TokenThemeTest, TokenThemeStorageGetThemeMiss001, TestSize.Level1)
{
    auto storage = NG::TokenThemeStorage::GetInstance();

    const auto& missedTheme = storage->GetTheme(MISSING_THEME_SCOPE_ID);
    EXPECT_FALSE(missedTheme);

    auto tokenTheme = AceType::MakeRefPtr<TokenTheme>(THEME_ID_1);
    storage->CacheSet(tokenTheme);
    storage->StoreThemeScope(THEME_SCOPE_ID_1, THEME_ID_1);

    const auto& hitTheme = storage->GetTheme(THEME_SCOPE_ID_1);
    EXPECT_EQ(hitTheme, tokenTheme);
}

/**
 * @tc.name: TokenThemeStorageRemoveThemeScopeMiss001
 * @tc.desc: Verify removing a missing theme scope does not remove cached themes.
 * @tc.type: Func
 */
HWTEST_F(TokenThemeTest, TokenThemeStorageRemoveThemeScopeMiss001, TestSize.Level1)
{
    auto storage = NG::TokenThemeStorage::GetInstance();

    auto tokenTheme = AceType::MakeRefPtr<TokenTheme>(THEME_ID_1);
    storage->CacheSet(tokenTheme);
    storage->RemoveThemeScope(MISSING_THEME_SCOPE_ID, true);

    const auto& cachedTheme = storage->CacheGet(THEME_ID_1);
    EXPECT_EQ(cachedTheme, tokenTheme);
}

/**
 * @tc.name: TokenThemeStorageCacheGetMiss001
 * @tc.desc: Verify querying a missing theme id returns empty without affecting later cache access.
 * @tc.type: Func
 */
HWTEST_F(TokenThemeTest, TokenThemeStorageCacheGetMiss001, TestSize.Level1)
{
    auto storage = NG::TokenThemeStorage::GetInstance();

    const auto& missedTheme = storage->CacheGet(MISSING_THEME_ID);
    EXPECT_FALSE(missedTheme);

    auto tokenTheme = AceType::MakeRefPtr<TokenTheme>(THEME_ID_1);
    storage->CacheSet(tokenTheme);

    const auto& cachedTheme = storage->CacheGet(THEME_ID_1);
    EXPECT_EQ(cachedTheme, tokenTheme);
}

/**
 * @tc.name: TokenThemeStorageRemoveThemeScopeHit001
 * @tc.desc: Verify removing an existing theme scope still removes the mapped token cache entry.
 * @tc.type: Func
 */
HWTEST_F(TokenThemeTest, TokenThemeStorageRemoveThemeScopeHit001, TestSize.Level1)
{
    auto storage = NG::TokenThemeStorage::GetInstance();

    auto removedTheme = AceType::MakeRefPtr<TokenTheme>(THEME_ID_1);
    auto reservedTheme = AceType::MakeRefPtr<TokenTheme>(THEME_ID_2);
    storage->CacheSet(removedTheme);
    storage->CacheSet(reservedTheme);
    storage->StoreThemeScope(THEME_SCOPE_ID_1, THEME_ID_1);

    storage->RemoveThemeScope(THEME_SCOPE_ID_1, true);

    EXPECT_FALSE(storage->GetTheme(THEME_SCOPE_ID_1));
    EXPECT_FALSE(storage->CacheGet(THEME_ID_1));
    EXPECT_EQ(storage->CacheGet(THEME_ID_2), reservedTheme);
}

} // namespace OHOS::Ace
