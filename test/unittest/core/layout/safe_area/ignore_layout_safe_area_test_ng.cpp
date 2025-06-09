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

#include "test/unittest/core/layout/safe_area/ignore_layout_safe_area_test_ng.h"
#include "ui/properties/safe_area_insets.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
/**
 * @tc.name: TestOperatorEqual
 * @tc.desc: Test the operator== of IgnoreLayoutSafeAreaOpts.
 * @tc.type: FUNC
 */
HWTEST_F(IgnoreLayoutSafeAreaOptsTestNg, TestOperatorEqual, TestSize.Level1)
{
    IgnoreLayoutSafeAreaOpts opts1 = {
        .type = LAYOUT_SAFE_AREA_TYPE_KEYBOARD,
        .edges = LAYOUT_SAFE_AREA_EDGE_START,
        .rawEdges = LAYOUT_SAFE_AREA_EDGE_START
    };
    IgnoreLayoutSafeAreaOpts opts2 = {
        .type = LAYOUT_SAFE_AREA_TYPE_KEYBOARD,
        .edges = LAYOUT_SAFE_AREA_EDGE_START,
        .rawEdges = LAYOUT_SAFE_AREA_EDGE_END
    };
    IgnoreLayoutSafeAreaOpts opts3 = {
        .type = LAYOUT_SAFE_AREA_TYPE_KEYBOARD,
        .edges = LAYOUT_SAFE_AREA_EDGE_END,
        .rawEdges = LAYOUT_SAFE_AREA_EDGE_START
    };
    EXPECT_EQ(opts1==opts2, true);
    EXPECT_EQ(opts1==opts3, false);
}

/**
 * @tc.name: TestNeedUpdateWithCheck
 * @tc.desc: Test NeedUpdateWithCheck
 * @tc.type: FUNC
 */
HWTEST_F(IgnoreLayoutSafeAreaOptsTestNg, TestNeedUpdateWithCheck, TestSize.Level1)
{
    IgnoreLayoutSafeAreaOpts opts = {
        .type = LAYOUT_SAFE_AREA_TYPE_KEYBOARD,
        .edges = LAYOUT_SAFE_AREA_EDGE_START,
        .rawEdges = LAYOUT_SAFE_AREA_EDGE_START
    };
    IgnoreLayoutSafeAreaOpts other1 = {
        .type = LAYOUT_SAFE_AREA_TYPE_KEYBOARD,
        .edges = LAYOUT_SAFE_AREA_EDGE_START,
        .rawEdges = LAYOUT_SAFE_AREA_EDGE_END
    };
    IgnoreLayoutSafeAreaOpts other2 = {
        .type = LAYOUT_SAFE_AREA_TYPE_KEYBOARD,
        .edges = LAYOUT_SAFE_AREA_EDGE_END,
        .rawEdges = LAYOUT_SAFE_AREA_EDGE_START
    };
    EXPECT_EQ(opts.NeedUpdateWithCheck(other1), true);
    EXPECT_EQ(opts.NeedUpdateWithCheck(other2), false);
}

/**
 * @tc.name: TestOperatorNotEqual
 * @tc.desc: Test the operator!= of IgnoreLayoutSafeAreaOpts.
 * @tc.type: FUNC
 */
HWTEST_F(IgnoreLayoutSafeAreaOptsTestNg, TestOperatorNotEqual, TestSize.Level1)
{
    IgnoreLayoutSafeAreaOpts opts1 = {
        .type = LAYOUT_SAFE_AREA_TYPE_KEYBOARD,
        .edges = LAYOUT_SAFE_AREA_EDGE_START,
        .rawEdges = LAYOUT_SAFE_AREA_EDGE_START
    };
    IgnoreLayoutSafeAreaOpts opts2 = {
        .type = LAYOUT_SAFE_AREA_TYPE_KEYBOARD,
        .edges = LAYOUT_SAFE_AREA_EDGE_START,
        .rawEdges = LAYOUT_SAFE_AREA_EDGE_END
    };
    IgnoreLayoutSafeAreaOpts opts3 = {
        .type = LAYOUT_SAFE_AREA_TYPE_KEYBOARD,
        .edges = LAYOUT_SAFE_AREA_EDGE_END,
        .rawEdges = LAYOUT_SAFE_AREA_EDGE_START
    };
    EXPECT_EQ(opts1!=opts2, false);
    EXPECT_EQ(opts1!=opts3, true);
}

/**
 * @tc.name: TestNeedIgnoreLayoutSafeArea
 * @tc.desc: Test NeedIgnoreLayoutSafeArea
 * @tc.type: FUNC
 */
HWTEST_F(IgnoreLayoutSafeAreaOptsTestNg, TestNeedIgnoreLayoutSafeArea, TestSize.Level1)
{
    IgnoreLayoutSafeAreaOpts opts1 = {
        .type = LAYOUT_SAFE_AREA_TYPE_KEYBOARD,
        .edges = LAYOUT_SAFE_AREA_EDGE_START,
        .rawEdges = LAYOUT_SAFE_AREA_EDGE_START
    };
    IgnoreLayoutSafeAreaOpts opts2;
    EXPECT_EQ(opts1.NeedIgnoreLayoutSafeArea(), true);
    EXPECT_EQ(opts2.NeedIgnoreLayoutSafeArea(), false);
}

/**
 * @tc.name: TestIsTrivial
 * @tc.desc: Test IsTrivial
 * @tc.type: FUNC
 */
HWTEST_F(IgnoreLayoutSafeAreaOptsTestNg, TestIsTrivial, TestSize.Level1)
{
    IgnoreLayoutSafeAreaOpts opts1 = {
        .type = LAYOUT_SAFE_AREA_TYPE_SYSTEM
    };
    IgnoreLayoutSafeAreaOpts opts2 = {
        .type = LAYOUT_SAFE_AREA_TYPE_KEYBOARD
    };
    EXPECT_EQ(opts1.IsTrivial(), true);
    EXPECT_EQ(opts2.IsTrivial(), false);
}

/**
 * @tc.name: TestTypeAndEdgeToMask
 * @tc.desc: Test TypeToMask and EdgeToMask
 * @tc.type: FUNC
 */
HWTEST_F(IgnoreLayoutSafeAreaOptsTestNg, TestTypeAndEdgeToMask, TestSize.Level1)
{
    EXPECT_EQ(IgnoreLayoutSafeAreaOpts::TypeToMask(uint32_t(1)), NG::LAYOUT_SAFE_AREA_TYPE_KEYBOARD);
    EXPECT_EQ(IgnoreLayoutSafeAreaOpts::TypeToMask(uint32_t(3)), 0);
    EXPECT_EQ(IgnoreLayoutSafeAreaOpts::EdgeToMask(uint32_t(4)), NG::LAYOUT_SAFE_AREA_EDGE_VERTICAL);
    EXPECT_EQ(IgnoreLayoutSafeAreaOpts::EdgeToMask(uint32_t(8)), 0);
}
} // namespace OHOS::Ace::NG