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

#include "gtest/gtest.h"

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/converter_union.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class UnionVisitorTest : public testing::Test {
};

/**
 * @tc.name:
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(UnionVisitorTest, SimpleUnionTest, TestSize.Level1)
{
    static_assert(Converter::UnionLastIndex<Ark_Union_String_Resource> == 1);
    auto test1 = Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>("abc");
    bool calledStr = false;
    bool calledRes = false;
    bool calledVoid = false;
    Converter::VisitUnion(test1,
        [&calledStr](const Ark_String& str) {calledStr = true;},
        [&calledRes](const Ark_Resource& res) {calledRes = true;},
        [&calledVoid]() {calledVoid = true;});
    EXPECT_TRUE(calledStr);
    EXPECT_FALSE(calledRes);
    EXPECT_FALSE(calledVoid);
}

HWTEST_F(UnionVisitorTest, DefaultCaseTest, TestSize.Level1)
{
    using TestType = Ark_Union_arkui_component_enums_Color_String_Resource_ColoringStrategy;
    static_assert(Converter::UnionLastIndex<TestType> == 3);
    auto test1 = Converter::ArkUnion<TestType, Ark_String>("abc");
    bool calledStrategy = false;
    bool calledDef = false;
    bool calledVoid = false;
    Converter::VisitUnion(test1,
        [&calledStrategy](const Ark_ColoringStrategy& str) {calledStrategy = true;},
        [&calledDef](const auto& res) {calledDef = true;},
        [&calledVoid]() {calledVoid = true;});
    EXPECT_TRUE(calledDef);
    EXPECT_FALSE(calledStrategy);
    EXPECT_FALSE(calledVoid);

    auto test2 = Converter::ArkUnion<TestType, Ark_ColoringStrategy>(Ark_ColoringStrategy());
    calledStrategy = false;
    calledDef = false;
    calledVoid = false;
    Converter::VisitUnion(test2,
        [&calledStrategy](const Ark_ColoringStrategy& str) {calledStrategy = true;},
        [&calledDef](const auto& res) {calledDef = true;},
        [&calledVoid]() {calledVoid = true;});
    EXPECT_FALSE(calledDef);
    EXPECT_TRUE(calledStrategy);
    EXPECT_FALSE(calledVoid);
}

HWTEST_F(UnionVisitorTest, EmptyCaseTest, TestSize.Level1)
{
    static_assert(Converter::UnionLastIndex<Ark_Union_String_Resource> == 1);
    auto test1 = Converter::ArkUnion<Ark_Union_String_Resource, Ark_Empty>(nullptr);
    bool calledStr = false;
    bool calledRes = false;
    bool calledVoid = false;
    Converter::VisitUnion(test1,
        [&calledStr](const Ark_String& str) {calledStr = true;},
        [&calledRes](const Ark_Resource& res) {calledRes = true;},
        [&calledVoid]() {calledVoid = true;});
    EXPECT_FALSE(calledStr);
    EXPECT_FALSE(calledRes);
    EXPECT_TRUE(calledVoid);
}

HWTEST_F(UnionVisitorTest, OptUnionTest, TestSize.Level1)
{
    auto test1 = Converter::ArkUnion<Opt_Union_String_Resource, Ark_String>("abc");
    bool calledStr = false;
    bool calledRes = false;
    bool calledVoid = false;
    Converter::VisitUnion(test1,
        [&calledStr](const Ark_String& str) {calledStr = true;},
        [&calledRes](const Ark_Resource& res) {calledRes = true;},
        [&calledVoid]() {calledVoid = true;});
    EXPECT_TRUE(calledStr);
    EXPECT_FALSE(calledRes);
    EXPECT_FALSE(calledVoid);
}

HWTEST_F(UnionVisitorTest, UndefinedOptCaseTest, TestSize.Level1)
{
    static_assert(Converter::UnionLastIndex<Ark_Union_String_Resource> == 1);
    auto test1 = Converter::ArkUnion<Opt_Union_String_Resource>(Ark_Empty());
    bool calledStr = false;
    bool calledRes = false;
    bool calledVoid = false;
    Converter::VisitUnion(test1,
        [&calledStr](const Ark_String& str) {calledStr = true;},
        [&calledRes](const Ark_Resource& res) {calledRes = true;},
        [&calledVoid]() {calledVoid = true;});
    EXPECT_FALSE(calledStr);
    EXPECT_FALSE(calledRes);
    EXPECT_TRUE(calledVoid);
}

} // namespace OHOS::Ace::NG
