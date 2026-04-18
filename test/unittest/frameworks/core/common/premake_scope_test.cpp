/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/common/premake_scope.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

class PreMakeScopeTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
    }
    static void TearDownTestSuite()
    {
    }
    void SetUp() override
    {
    }
    void TearDown() override
    {
    }
};

HWTEST_F(PreMakeScopeTest, IsPreMakeTest001, TestSize.Level1)
{
    EXPECT_FALSE(PreMakeScope::IsPreMake());
}

HWTEST_F(PreMakeScopeTest, IsPreMakeTest002, TestSize.Level1)
{
    {
        PreMakeScope scope;
        EXPECT_TRUE(PreMakeScope::IsPreMake());
    }
    EXPECT_FALSE(PreMakeScope::IsPreMake());
}

HWTEST_F(PreMakeScopeTest, IsPreMakeTest003, TestSize.Level1)
{
    {
        PreMakeScope scope1;
        EXPECT_TRUE(PreMakeScope::IsPreMake());
        EXPECT_EQ(PreMakeScope::count(), 1);
        {
            PreMakeScope scope2;
            EXPECT_TRUE(PreMakeScope::IsPreMake());
            EXPECT_EQ(PreMakeScope::count(), 2);
        }
        EXPECT_TRUE(PreMakeScope::IsPreMake());
        EXPECT_EQ(PreMakeScope::count(), 1);
    }
    EXPECT_FALSE(PreMakeScope::IsPreMake());
    EXPECT_EQ(PreMakeScope::count(), 0);
}

HWTEST_F(PreMakeScopeTest, ConstructorDefaultTest001, TestSize.Level1)
{
    EXPECT_EQ(PreMakeScope::count(), 0);
    {
        PreMakeScope scope;
        EXPECT_TRUE(PreMakeScope::IsPreMake());
        EXPECT_EQ(PreMakeScope::count(), 1);
    }
    EXPECT_FALSE(PreMakeScope::IsPreMake());
    EXPECT_EQ(PreMakeScope::count(), 0);
}

HWTEST_F(PreMakeScopeTest, ConstructorWithTrueTest001, TestSize.Level1)
{
    EXPECT_EQ(PreMakeScope::count(), 0);
    {
        PreMakeScope scope(true);
        EXPECT_TRUE(PreMakeScope::IsPreMake());
        EXPECT_EQ(PreMakeScope::count(), 1);
    }
    EXPECT_FALSE(PreMakeScope::IsPreMake());
    EXPECT_EQ(PreMakeScope::count(), 0);
}

HWTEST_F(PreMakeScopeTest, ConstructorWithFalseTest001, TestSize.Level1)
{
    EXPECT_EQ(PreMakeScope::count(), 0);
    {
        PreMakeScope scope(false);
        EXPECT_FALSE(PreMakeScope::IsPreMake());
        EXPECT_EQ(PreMakeScope::count(), 0);
    }
    EXPECT_FALSE(PreMakeScope::IsPreMake());
    EXPECT_EQ(PreMakeScope::count(), 0);
}

HWTEST_F(PreMakeScopeTest, ConstructorWithFalseTest002, TestSize.Level1)
{
    {
        PreMakeScope scope1;
        EXPECT_EQ(PreMakeScope::count(), 1);
        {
            PreMakeScope scope2(false);
            EXPECT_EQ(PreMakeScope::count(), 1);
        }
        EXPECT_EQ(PreMakeScope::count(), 1);
    }
    EXPECT_EQ(PreMakeScope::count(), 0);
}

HWTEST_F(PreMakeScopeTest, NestedScopeTest001, TestSize.Level1)
{
    EXPECT_EQ(PreMakeScope::count(), 0);
    {
        PreMakeScope scope1;
        EXPECT_EQ(PreMakeScope::count(), 1);
        {
            PreMakeScope scope2;
            EXPECT_EQ(PreMakeScope::count(), 2);
            {
                PreMakeScope scope3;
                EXPECT_EQ(PreMakeScope::count(), 3);
            }
            EXPECT_EQ(PreMakeScope::count(), 2);
        }
        EXPECT_EQ(PreMakeScope::count(), 1);
    }
    EXPECT_EQ(PreMakeScope::count(), 0);
}

HWTEST_F(PreMakeScopeTest, NestedScopeTest002, TestSize.Level1)
{
    EXPECT_EQ(PreMakeScope::count(), 0);
    {
        PreMakeScope scope1(true);
        EXPECT_EQ(PreMakeScope::count(), 1);
        {
            PreMakeScope scope2(true);
            EXPECT_EQ(PreMakeScope::count(), 2);
            {
                PreMakeScope scope3(true);
                EXPECT_EQ(PreMakeScope::count(), 3);
            }
            EXPECT_EQ(PreMakeScope::count(), 2);
        }
        EXPECT_EQ(PreMakeScope::count(), 1);
    }
    EXPECT_EQ(PreMakeScope::count(), 0);
}

HWTEST_F(PreMakeScopeTest, MixedConstructorTest001, TestSize.Level1)
{
    EXPECT_EQ(PreMakeScope::count(), 0);
    {
        PreMakeScope scope1;
        EXPECT_EQ(PreMakeScope::count(), 1);
        {
            PreMakeScope scope2(true);
            EXPECT_EQ(PreMakeScope::count(), 2);
        }
        EXPECT_EQ(PreMakeScope::count(), 1);
        {
            PreMakeScope scope3(false);
            EXPECT_EQ(PreMakeScope::count(), 1);
        }
        EXPECT_EQ(PreMakeScope::count(), 1);
    }
    EXPECT_EQ(PreMakeScope::count(), 0);
}

HWTEST_F(PreMakeScopeTest, CountTest001, TestSize.Level1)
{
    EXPECT_EQ(PreMakeScope::count(), 0);
}

HWTEST_F(PreMakeScopeTest, CountTest002, TestSize.Level1)
{
    PreMakeScope scope1;
    EXPECT_EQ(PreMakeScope::count(), 1);
    PreMakeScope scope2;
    EXPECT_EQ(PreMakeScope::count(), 2);
    PreMakeScope scope3;
    EXPECT_EQ(PreMakeScope::count(), 3);
}

HWTEST_F(PreMakeScopeTest, DestructorTest001, TestSize.Level1)
{
    PreMakeScope* scope = new PreMakeScope();
    EXPECT_EQ(PreMakeScope::count(), 1);
    delete scope;
    EXPECT_EQ(PreMakeScope::count(), 0);
}

HWTEST_F(PreMakeScopeTest, DestructorTest002, TestSize.Level1)
{
    PreMakeScope* scope = new PreMakeScope(true);
    EXPECT_EQ(PreMakeScope::count(), 1);
    delete scope;
    EXPECT_EQ(PreMakeScope::count(), 0);
}

HWTEST_F(PreMakeScopeTest, DestructorTest003, TestSize.Level1)
{
    PreMakeScope* scope = new PreMakeScope(false);
    EXPECT_EQ(PreMakeScope::count(), 0);
    delete scope;
    EXPECT_EQ(PreMakeScope::count(), 0);
}

HWTEST_F(PreMakeScopeTest, MultipleCreateDestroyTest001, TestSize.Level1)
{
    for (int i = 0; i < 5; i++) {
        PreMakeScope scope;
        EXPECT_TRUE(PreMakeScope::IsPreMake());
    }
    EXPECT_FALSE(PreMakeScope::IsPreMake());
}

HWTEST_F(PreMakeScopeTest, MultipleCreateDestroyTest002, TestSize.Level1)
{
    for (int i = 0; i < 5; i++) {
        PreMakeScope scope(true);
        EXPECT_TRUE(PreMakeScope::IsPreMake());
    }
    EXPECT_FALSE(PreMakeScope::IsPreMake());
}

HWTEST_F(PreMakeScopeTest, MultipleCreateDestroyTest003, TestSize.Level1)
{
    for (int i = 0; i < 5; i++) {
        PreMakeScope scope(false);
        EXPECT_FALSE(PreMakeScope::IsPreMake());
    }
    EXPECT_FALSE(PreMakeScope::IsPreMake());
}

HWTEST_F(PreMakeScopeTest, IsPreMakeAndCountConsistencyTest001, TestSize.Level1)
{
    {
        PreMakeScope scope;
        EXPECT_TRUE(PreMakeScope::IsPreMake());
        EXPECT_GT(PreMakeScope::count(), 0);
    }
    EXPECT_FALSE(PreMakeScope::IsPreMake());
    EXPECT_EQ(PreMakeScope::count(), 0);
}

HWTEST_F(PreMakeScopeTest, IsPreMakeAndCountConsistencyTest002, TestSize.Level1)
{
    {
        PreMakeScope scope1;
        PreMakeScope scope2;
        PreMakeScope scope3;
        EXPECT_TRUE(PreMakeScope::IsPreMake());
        EXPECT_EQ(PreMakeScope::count(), 3);
    }
    EXPECT_FALSE(PreMakeScope::IsPreMake());
    EXPECT_EQ(PreMakeScope::count(), 0);
}

HWTEST_F(PreMakeScopeTest, EdgeCaseTest001, TestSize.Level1)
{
    {
        PreMakeScope scope1;
        EXPECT_EQ(PreMakeScope::count(), 1);
        PreMakeScope scope2(false);
        EXPECT_EQ(PreMakeScope::count(), 1);
        PreMakeScope scope3(false);
        EXPECT_EQ(PreMakeScope::count(), 1);
        PreMakeScope scope4(true);
        EXPECT_EQ(PreMakeScope::count(), 2);
    }
    EXPECT_EQ(PreMakeScope::count(), 0);
}

HWTEST_F(PreMakeScopeTest, EdgeCaseTest002, TestSize.Level1)
{
    {
        PreMakeScope scope1(false);
        EXPECT_EQ(PreMakeScope::count(), 0);
        PreMakeScope scope2;
        EXPECT_EQ(PreMakeScope::count(), 1);
    }
    EXPECT_EQ(PreMakeScope::count(), 0);
}

HWTEST_F(PreMakeScopeTest, StressTest001, TestSize.Level1)
{
    std::vector<PreMakeScope*> scopes;
    for (int i = 0; i < 10; i++) {
        scopes.push_back(new PreMakeScope());
        EXPECT_EQ(PreMakeScope::count(), i + 1);
    }
    for (int i = 0; i < 10; i++) {
        delete scopes[i];
        EXPECT_EQ(PreMakeScope::count(), 10 - i - 1);
    }
    EXPECT_EQ(PreMakeScope::count(), 0);
}

HWTEST_F(PreMakeScopeTest, StressTest002, TestSize.Level1)
{
    std::vector<PreMakeScope*> scopes;
    for (int i = 0; i < 10; i++) {
        scopes.push_back(new PreMakeScope(true));
        EXPECT_EQ(PreMakeScope::count(), i + 1);
    }
    for (int i = 0; i < 10; i++) {
        delete scopes[i];
        EXPECT_EQ(PreMakeScope::count(), 10 - i - 1);
    }
    EXPECT_EQ(PreMakeScope::count(), 0);
}

HWTEST_F(PreMakeScopeTest, StressTest003, TestSize.Level1)
{
    std::vector<PreMakeScope*> scopes;
    for (int i = 0; i < 10; i++) {
        scopes.push_back(new PreMakeScope(false));
        EXPECT_EQ(PreMakeScope::count(), 0);
    }
    for (int i = 0; i < 10; i++) {
        delete scopes[i];
    }
    EXPECT_EQ(PreMakeScope::count(), 0);
}

HWTEST_F(PreMakeScopeTest, ScopeLifetimeTest001, TestSize.Level1)
{
    {
        PreMakeScope outerScope;
        EXPECT_TRUE(PreMakeScope::IsPreMake());
        {
            PreMakeScope innerScope;
            EXPECT_TRUE(PreMakeScope::IsPreMake());
        }
        EXPECT_TRUE(PreMakeScope::IsPreMake());
    }
    EXPECT_FALSE(PreMakeScope::IsPreMake());
}

HWTEST_F(PreMakeScopeTest, ScopeLifetimeTest002, TestSize.Level1)
{
    {
        PreMakeScope outerScope(true);
        EXPECT_TRUE(PreMakeScope::IsPreMake());
        {
            PreMakeScope innerScope(true);
            EXPECT_TRUE(PreMakeScope::IsPreMake());
        }
        EXPECT_TRUE(PreMakeScope::IsPreMake());
    }
    EXPECT_FALSE(PreMakeScope::IsPreMake());
}

HWTEST_F(PreMakeScopeTest, ScopeLifetimeTest003, TestSize.Level1)
{
    {
        PreMakeScope outerScope(false);
        EXPECT_FALSE(PreMakeScope::IsPreMake());
        {
            PreMakeScope innerScope(false);
            EXPECT_FALSE(PreMakeScope::IsPreMake());
        }
        EXPECT_FALSE(PreMakeScope::IsPreMake());
    }
    EXPECT_FALSE(PreMakeScope::IsPreMake());
}

HWTEST_F(PreMakeScopeTest, ComplexNestedTest001, TestSize.Level1)
{
    {
        PreMakeScope s1;
        EXPECT_EQ(PreMakeScope::count(), 1);
        {
            PreMakeScope s2(true);
            EXPECT_EQ(PreMakeScope::count(), 2);
            {
                PreMakeScope s3;
                EXPECT_EQ(PreMakeScope::count(), 3);
                {
                    PreMakeScope s4(false);
                    EXPECT_EQ(PreMakeScope::count(), 3);
                    {
                        PreMakeScope s5(true);
                        EXPECT_EQ(PreMakeScope::count(), 4);
                    }
                    EXPECT_EQ(PreMakeScope::count(), 3);
                }
                EXPECT_EQ(PreMakeScope::count(), 3);
            }
            EXPECT_EQ(PreMakeScope::count(), 2);
        }
        EXPECT_EQ(PreMakeScope::count(), 1);
    }
    EXPECT_EQ(PreMakeScope::count(), 0);
}
} // namespace OHOS::Ace