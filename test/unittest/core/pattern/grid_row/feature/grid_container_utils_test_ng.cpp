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
#include "test/unittest/core/pattern/grid_row/grid_row_base_test_ng.h"
#include "core/components_v2/grid_layout/grid_container_utils.h"
#include "test/mock/base/mock_system_properties.h"

namespace OHOS::Ace::NG {
class GridContainerUtilsTestNG : public GridRowBaseTestNG {
};

/**
 * @tc.name: InheritGridRowOption01
 * @tc.desc: Test InheritGridRowOption()
 * @tc.type: FUNC
 */
HWTEST_F(GridContainerUtilsTestNG, InheritGridRowOption01, TestSize.Level0)
{
    auto gridContainerSize = AceType::MakeRefPtr<V2::GridContainerSize>();
    std::optional<int32_t> containerSizeArray[V2::MAX_NUMBER_BREAKPOINT];
    containerSizeArray[2] = 4;
    V2::GridContainerUtils::InheritGridRowOption(gridContainerSize, containerSizeArray);
    auto expectedResult = AceType::MakeRefPtr<V2::GridContainerSize>();
    expectedResult->xs = 12;
    expectedResult->sm = 12;
    expectedResult->md = 4;
    expectedResult->lg = 4;
    expectedResult->xl = 4;
    expectedResult->xxl = 4;
    EXPECT_EQ(gridContainerSize->ToString(), expectedResult->ToString());
}

/**
 * @tc.name: InheritGridRowOption02
 * @tc.desc: Test InheritGridRowOption
 * @tc.type: FUNC
 */
HWTEST_F(GridContainerUtilsTestNG, InheritGridRowOption02, TestSize.Level0)
{
    auto gridContainerSize = AceType::MakeRefPtr<V2::GridContainerSize>();
    std::optional<int32_t> containerSizeArray[V2::MAX_NUMBER_BREAKPOINT];
    containerSizeArray[0] = 4;
    containerSizeArray[3] = 8;
    V2::GridContainerUtils::InheritGridRowOption(gridContainerSize, containerSizeArray);
    auto expectedResult = AceType::MakeRefPtr<V2::GridContainerSize>();
    expectedResult->xs = 4;
    expectedResult->sm = 4;
    expectedResult->md = 4;
    expectedResult->lg = 8;
    expectedResult->xl = 8;
    expectedResult->xxl = 8;
    EXPECT_EQ(gridContainerSize->ToString(), expectedResult->ToString());
}

/**
 * @tc.name: InheritGridColumnsTest01
 * @tc.desc: Test InheritGridColumns()
 * @tc.type: FUNC
 */
HWTEST_F(GridContainerUtilsTestNG, InheritGridColumnsTest01, TestSize.Level0)
{
    auto gridContainerSize = AceType::MakeRefPtr<V2::GridContainerSize>();
    std::optional<int32_t> containerSizeArray[V2::MAX_NUMBER_BREAKPOINT];
    auto expectedResult = AceType::MakeRefPtr<V2::GridContainerSize>();
    /**
     * @tc.steps: step1. containerSizeArray[5] = 9,
                         which means the developer initializes gridrow's columns property as {xxl:9}.
     * @tc.expected: gridContainerSize has 9 columns for each breakpoint.
     */
    containerSizeArray[5] = 9;
    V2::GridContainerUtils::InheritGridColumns(gridContainerSize, containerSizeArray);
    expectedResult->xs = 9;
    expectedResult->sm = 9;
    expectedResult->md = 9;
    expectedResult->lg = 9;
    expectedResult->xl = 9;
    expectedResult->xxl = 9;
    EXPECT_EQ(gridContainerSize->ToString(), expectedResult->ToString());
}

/**
 * @tc.name: InheritGridColumnsTest02
 * @tc.desc: Test InheritGridColumns()
 * @tc.type: FUNC
 */
HWTEST_F(GridContainerUtilsTestNG, InheritGridColumnsTest02, TestSize.Level0)
{
    auto gridContainerSize = AceType::MakeRefPtr<V2::GridContainerSize>();
    std::optional<int32_t> containerSizeArray[V2::MAX_NUMBER_BREAKPOINT];
    auto expectedResult = AceType::MakeRefPtr<V2::GridContainerSize>();
    containerSizeArray[0] = 4;
    containerSizeArray[5] = 9;
    V2::GridContainerUtils::InheritGridColumns(gridContainerSize, containerSizeArray);
    expectedResult->xs = 4;
    expectedResult->sm = 4;
    expectedResult->md = 4;
    expectedResult->lg = 4;
    expectedResult->xl = 4;
    expectedResult->xxl = 9;
    EXPECT_EQ(gridContainerSize->ToString(), expectedResult->ToString());
}

/**
 * @tc.name: InheritGridColumnsTest02
 * @tc.desc: Test InheritGridColumns()
 * @tc.type: FUNC
 */
HWTEST_F(GridContainerUtilsTestNG, InheritGridColumnsTest03, TestSize.Level0)
{
    auto gridContainerSize = AceType::MakeRefPtr<V2::GridContainerSize>();
    std::optional<int32_t> containerSizeArray[V2::MAX_NUMBER_BREAKPOINT];
    auto expectedResult = AceType::MakeRefPtr<V2::GridContainerSize>();
    containerSizeArray[2] = 4;
    containerSizeArray[3] = 9;
    V2::GridContainerUtils::InheritGridColumns(gridContainerSize, containerSizeArray);
    expectedResult->xs = 4;
    expectedResult->sm = 4;
    expectedResult->md = 4;
    expectedResult->lg = 9;
    expectedResult->xl = 9;
    expectedResult->xxl = 9;
    EXPECT_EQ(gridContainerSize->ToString(), expectedResult->ToString());
}

/**
 * @tc.name: SaveGridRowGutterOptionxResObjXsSmMdTest
 * @tc.desc: Test SaveGridRowGutterOptionxResObjXsSmMd()
 * @tc.type: FUNC
 */
HWTEST_F(GridContainerUtilsTestNG, SaveGridRowGutterOptionxResObjXsSmMdTest, TestSize.Level0)
{
    g_isConfigChangePerform = true;
    auto gutter = AceType::MakeRefPtr<V2::Gutter>();
    RefPtr<ResourceObject> gutterSizeArrayResObj[V2::MAX_NUMBER_BREAKPOINT];
    gutterSizeArrayResObj[0] = AceType::MakeRefPtr<ResourceObject>();
    V2::GridContainerUtils::SaveGridRowGutterOptionxResObjXsSmMd(gutter, gutterSizeArrayResObj);
    EXPECT_TRUE(gutter->resMap_.find("gridrow.gutter.xXs") != gutter->resMap_.end());

    gutterSizeArrayResObj[1] = AceType::MakeRefPtr<ResourceObject>();
    V2::GridContainerUtils::SaveGridRowGutterOptionxResObjXsSmMd(gutter, gutterSizeArrayResObj);
    EXPECT_TRUE(gutter->resMap_.find("gridrow.gutter.xSm") != gutter->resMap_.end());

    gutterSizeArrayResObj[2] = AceType::MakeRefPtr<ResourceObject>();
    V2::GridContainerUtils::SaveGridRowGutterOptionxResObjXsSmMd(gutter, gutterSizeArrayResObj);
    EXPECT_TRUE(gutter->resMap_.find("gridrow.gutter.xMd") != gutter->resMap_.end());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SaveGridRowGutterOptionxResObjLgXlXXlTest
 * @tc.desc: Test SaveGridRowGutterOptionxResObjLgXlXXl()
 * @tc.type: FUNC
 */
HWTEST_F(GridContainerUtilsTestNG, SaveGridRowGutterOptionxResObjLgXlXXlTest, TestSize.Level0)
{
    g_isConfigChangePerform = true;
    auto gutter = AceType::MakeRefPtr<V2::Gutter>();
    RefPtr<ResourceObject> gutterSizeArrayResObj[V2::MAX_NUMBER_BREAKPOINT];
    gutterSizeArrayResObj[3] = AceType::MakeRefPtr<ResourceObject>();
    V2::GridContainerUtils::SaveGridRowGutterOptionxResObjLgXlXXl(gutter, gutterSizeArrayResObj);
    EXPECT_TRUE(gutter->resMap_.find("gridrow.gutter.xLg") != gutter->resMap_.end());

    gutterSizeArrayResObj[4] = AceType::MakeRefPtr<ResourceObject>();
    V2::GridContainerUtils::SaveGridRowGutterOptionxResObjLgXlXXl(gutter, gutterSizeArrayResObj);
    EXPECT_TRUE(gutter->resMap_.find("gridrow.gutter.xXl") != gutter->resMap_.end());

    gutterSizeArrayResObj[5] = AceType::MakeRefPtr<ResourceObject>();
    V2::GridContainerUtils::SaveGridRowGutterOptionxResObjLgXlXXl(gutter, gutterSizeArrayResObj);
    EXPECT_TRUE(gutter->resMap_.find("gridrow.gutter.xXXl") != gutter->resMap_.end());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SaveGridRowGutterOptionyResObjXsSmMdTest
 * @tc.desc: Test SaveGridRowGutterOptionyResObjXsSmMd()
 * @tc.type: FUNC
 */
HWTEST_F(GridContainerUtilsTestNG, SaveGridRowGutterOptionyResObjXsSmMdTest, TestSize.Level0)
{
    g_isConfigChangePerform = true;
    auto gutter = AceType::MakeRefPtr<V2::Gutter>();
    RefPtr<ResourceObject> gutterSizeArrayResObj[V2::MAX_NUMBER_BREAKPOINT];
    gutterSizeArrayResObj[0] = AceType::MakeRefPtr<ResourceObject>();
    V2::GridContainerUtils::SaveGridRowGutterOptionyResObjXsSmMd(gutter, gutterSizeArrayResObj);
    EXPECT_TRUE(gutter->resMap_.find("gridrow.gutter.yXs") != gutter->resMap_.end());

    gutterSizeArrayResObj[1] = AceType::MakeRefPtr<ResourceObject>();
    V2::GridContainerUtils::SaveGridRowGutterOptionyResObjXsSmMd(gutter, gutterSizeArrayResObj);
    EXPECT_TRUE(gutter->resMap_.find("gridrow.gutter.ySm") != gutter->resMap_.end());

    gutterSizeArrayResObj[2] = AceType::MakeRefPtr<ResourceObject>();
    V2::GridContainerUtils::SaveGridRowGutterOptionyResObjXsSmMd(gutter, gutterSizeArrayResObj);
    EXPECT_TRUE(gutter->resMap_.find("gridrow.gutter.yMd") != gutter->resMap_.end());
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SaveGridRowGutterOptionyResObjLgXlXXlTest
 * @tc.desc: Test SaveGridRowGutterOptionyResObjLgXlXXlTest()
 * @tc.type: FUNC
 */
HWTEST_F(GridContainerUtilsTestNG, SaveGridRowGutterOptionyResObjLgXlXXlTest, TestSize.Level0)
{
    g_isConfigChangePerform = true;
    auto gutter = AceType::MakeRefPtr<V2::Gutter>();
    RefPtr<ResourceObject> gutterSizeArrayResObj[V2::MAX_NUMBER_BREAKPOINT];
    gutterSizeArrayResObj[3] = AceType::MakeRefPtr<ResourceObject>();
    V2::GridContainerUtils::SaveGridRowGutterOptionyResObjLgXlXXl(gutter, gutterSizeArrayResObj);
    EXPECT_TRUE(gutter->resMap_.find("gridrow.gutter.yLg") != gutter->resMap_.end());

    gutterSizeArrayResObj[4] = AceType::MakeRefPtr<ResourceObject>();
    V2::GridContainerUtils::SaveGridRowGutterOptionyResObjLgXlXXl(gutter, gutterSizeArrayResObj);
    EXPECT_TRUE(gutter->resMap_.find("gridrow.gutter.yXl") != gutter->resMap_.end());

    gutterSizeArrayResObj[5] = AceType::MakeRefPtr<ResourceObject>();
    V2::GridContainerUtils::SaveGridRowGutterOptionyResObjLgXlXXl(gutter, gutterSizeArrayResObj);
    EXPECT_TRUE(gutter->resMap_.find("gridrow.gutter.yXXl") != gutter->resMap_.end());
    g_isConfigChangePerform = false;
}
} // namespace OHOS::Ace::NG
