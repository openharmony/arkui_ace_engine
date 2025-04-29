/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "list_test_ng.h"
#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {

void ListItemGroupPatternTestNg::SetUp() {}

void ListItemGroupPatternTestNg::TearDown() {}

/**
 * @tc.name: GetStartListItemIndex001
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    RefPtr<NG::UINode> footerNode;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::IN_FOOTER_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.footerMainSize_ = 0.0f;
    listItemGroupPattern.AddFooter(footerNode);
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex002
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex002, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    RefPtr<NG::UINode> footerNode;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::IN_FOOTER_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.footerMainSize_ = 1.0f;
    listItemGroupPattern.AddFooter(footerNode);
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_EQ(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex003
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex003, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::IN_HEADER_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.itemDisplayStartIndex_ = 0;
    listItemGroupPattern.startHeaderPos_ = 1.0;
    listItemGroupPattern.headerMainSize_ = 1.0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_EQ(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex004
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex004, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::IN_HEADER_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.itemDisplayStartIndex_ = -1;
    listItemGroupPattern.startHeaderPos_ = -1.0;
    listItemGroupPattern.headerMainSize_ = -1.0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex005
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex005, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::IN_HEADER_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.itemDisplayStartIndex_ = 0;
    listItemGroupPattern.startHeaderPos_ = -1.0;
    listItemGroupPattern.headerMainSize_ = -1.0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex006
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex006, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::IN_HEADER_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.itemDisplayStartIndex_ = -1;
    listItemGroupPattern.startHeaderPos_ = 5.0;
    listItemGroupPattern.headerMainSize_ = -1.0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex007
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex007, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::IN_HEADER_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.itemDisplayStartIndex_ = -1;
    listItemGroupPattern.startHeaderPos_ = -5.0;
    listItemGroupPattern.headerMainSize_ = 1.0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex008
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex008, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::IN_HEADER_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.itemDisplayStartIndex_ = 0;
    listItemGroupPattern.startHeaderPos_ = 5.0;
    listItemGroupPattern.headerMainSize_ = -1.0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex009
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex009, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::IN_HEADER_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.itemDisplayStartIndex_ = 0;
    listItemGroupPattern.startHeaderPos_ = -5.0;
    listItemGroupPattern.headerMainSize_ = 1.0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex010
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex010, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::IN_HEADER_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.itemDisplayStartIndex_ = -1;
    listItemGroupPattern.startHeaderPos_ = 1.0;
    listItemGroupPattern.headerMainSize_ = 1.0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex011
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex011, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::NONE_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.headerMainSize_ = 0.0;
    listItemGroupPattern.footerMainSize_ = 0.0;
    listItemGroupPattern.itemTotalCount_ = 0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_EQ(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex012
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex012, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::NONE_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.headerMainSize_ = 1.0;
    listItemGroupPattern.footerMainSize_ = 1.0;
    listItemGroupPattern.itemTotalCount_ = -1;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex013
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex013, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::NONE_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.headerMainSize_ = 0;
    listItemGroupPattern.footerMainSize_ = 1.0;
    listItemGroupPattern.itemTotalCount_ = -1;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex014
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex014, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::NONE_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.headerMainSize_ = 1.0;
    listItemGroupPattern.footerMainSize_ = 0;
    listItemGroupPattern.itemTotalCount_ = -1;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex015
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex015, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::NONE_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.headerMainSize_ = 1.0;
    listItemGroupPattern.footerMainSize_ = 1.0;
    listItemGroupPattern.itemTotalCount_ = 0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex016
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex016, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::NONE_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.headerMainSize_ = 1.0;
    listItemGroupPattern.footerMainSize_ = 0.0;
    listItemGroupPattern.itemTotalCount_ = 0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex017
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex017, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::NONE_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.headerMainSize_ = 0.0;
    listItemGroupPattern.footerMainSize_ = 1.0;
    listItemGroupPattern.itemTotalCount_ = 0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex018
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex018, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::NONE_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.headerMainSize_ = 0.0;
    listItemGroupPattern.footerMainSize_ = 0.0;
    listItemGroupPattern.itemTotalCount_ = -1;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}
} // namespace OHOS::Ace::NG