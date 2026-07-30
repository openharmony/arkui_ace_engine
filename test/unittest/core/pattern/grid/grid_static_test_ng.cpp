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
#include "grid_test_ng.h"

#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/grid/grid_model_static.h"
#include "core/components_ng/pattern/grid/grid_utils.h"

namespace OHOS::Ace::NG {

class GridModelStaticTestNg : public GridTestNg {};

/**
 * @tc.name: SetCachedCount
 * @tc.desc: Test SetCachedCount
 * @tc.type: FUNC
 */
HWTEST_F(GridModelStaticTestNg, SetCachedCount, TestSize.Level1)
{
    CreateGrid();
    std::optional<int32_t> cachedCount = 10;
    GridModelStatic::SetCachedCount(AceType::RawPtr(frameNode_), cachedCount);
    ASSERT_NE(layoutProperty_, nullptr);
    auto ret = layoutProperty_->GetCachedCountValue(0);
    EXPECT_EQ(ret, cachedCount.value());

    cachedCount.reset();
    GridModelStatic::SetCachedCount(AceType::RawPtr(frameNode_), cachedCount);
    EXPECT_FALSE(layoutProperty_->GetCachedCount().has_value());
}

/**
 * @tc.name: SetShowCached
 * @tc.desc: Test SetShowCached
 * @tc.type: FUNC
 */
HWTEST_F(GridModelStaticTestNg, SetShowCached, TestSize.Level1)
{
    CreateGrid();
    std::optional<bool> show = true;
    GridModelStatic::SetShowCached(AceType::RawPtr(frameNode_), show);
    ASSERT_NE(layoutProperty_, nullptr);
    auto ret = layoutProperty_->GetShowCachedItemsValue(false);
    EXPECT_EQ(ret, show.value());

    show.reset();
    GridModelStatic::SetShowCached(AceType::RawPtr(frameNode_), show);
    EXPECT_FALSE(layoutProperty_->GetShowCachedItems().has_value());
}

/**
 * @tc.name: SetMinCount
 * @tc.desc: Test SetMinCount
 * @tc.type: FUNC
 */
HWTEST_F(GridModelStaticTestNg, SetMinCount, TestSize.Level1)
{
    CreateGrid();
    std::optional<int32_t> minCount = true;
    GridModelStatic::SetMinCount(AceType::RawPtr(frameNode_), minCount);
    ASSERT_NE(layoutProperty_, nullptr);
    auto ret = layoutProperty_->GetMinCountValue(0);
    EXPECT_EQ(ret, minCount.value());

    minCount = -1;
    GridModelStatic::SetMinCount(AceType::RawPtr(frameNode_), minCount);
    EXPECT_FALSE(layoutProperty_->GetMinCount().has_value());

    minCount.reset();
    GridModelStatic::SetMinCount(AceType::RawPtr(frameNode_), minCount);
    EXPECT_FALSE(layoutProperty_->GetMinCount().has_value());
}

/**
 * @tc.name: SetCellLength
 * @tc.desc: Test SetCellLength
 * @tc.type: FUNC
 */
HWTEST_F(GridModelStaticTestNg, SetCellLength, TestSize.Level1)
{
    CreateGrid();
    std::optional<int32_t> cellLength = 1;
    GridModelStatic::SetCellLength(AceType::RawPtr(frameNode_), cellLength);
    ASSERT_NE(layoutProperty_, nullptr);
    auto ret = layoutProperty_->GetCellLengthValue(0);
    EXPECT_EQ(ret, cellLength.value());

    cellLength.reset();
    GridModelStatic::SetCellLength(AceType::RawPtr(frameNode_), cellLength);
    EXPECT_FALSE(layoutProperty_->GetCellLength().has_value());
}


/**
 * @tc.name: SetRowsTemplate
 * @tc.desc: Test SetRowsTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridModelStaticTestNg, SetRowsTemplate, TestSize.Level1)
{
    CreateGrid();
    std::optional<std::string> rowsTemplate = "1fr";
    GridModelStatic::SetRowsTemplate(AceType::RawPtr(frameNode_), rowsTemplate);
    ASSERT_NE(layoutProperty_, nullptr);
    auto ret = layoutProperty_->GetRowsTemplateValue("");
    EXPECT_EQ(ret, rowsTemplate.value());

    rowsTemplate.reset();
    GridModelStatic::SetRowsTemplate(AceType::RawPtr(frameNode_), rowsTemplate);
    EXPECT_FALSE(layoutProperty_->GetRowsTemplate().has_value());
}

/**
 * @tc.name: SetColumnsTemplate
 * @tc.desc: Test SetColumnsTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridModelStaticTestNg, SetColumnsTemplate, TestSize.Level1)
{
    CreateGrid();
    std::optional<std::string> columnsTemplate = "1fr";
    GridModelStatic::SetColumnsTemplate(AceType::RawPtr(frameNode_), columnsTemplate);
    ASSERT_NE(layoutProperty_, nullptr);
    auto ret = layoutProperty_->GetColumnsTemplateValue("");
    EXPECT_EQ(ret, columnsTemplate.value());

    columnsTemplate.reset();
    GridModelStatic::SetColumnsTemplate(AceType::RawPtr(frameNode_), columnsTemplate);
    EXPECT_FALSE(layoutProperty_->GetColumnsTemplate().has_value());
}

/**
 * @tc.name: SetEditable
 * @tc.desc: Test SetEditable
 * @tc.type: FUNC
 */
HWTEST_F(GridModelStaticTestNg, SetEditable, TestSize.Level1)
{
    CreateGrid();
    std::optional<bool> editable = true;
    GridModelStatic::SetEditable(AceType::RawPtr(frameNode_), editable);
    ASSERT_NE(layoutProperty_, nullptr);
    auto ret = layoutProperty_->GetEditableValue(false);
    EXPECT_EQ(ret, editable.value());

    editable.reset();
    GridModelStatic::SetEditable(AceType::RawPtr(frameNode_), editable);
    EXPECT_FALSE(layoutProperty_->GetEditable().has_value());
}

/**
 * @tc.name: SetMaxCount
 * @tc.desc: Test SetMaxCount
 * @tc.type: FUNC
 */
HWTEST_F(GridModelStaticTestNg, SetMaxCount, TestSize.Level1)
{
    CreateGrid();
    std::optional<int32_t> maxCount = 1;
    GridModelStatic::SetMaxCount(AceType::RawPtr(frameNode_), maxCount);
    ASSERT_NE(layoutProperty_, nullptr);
    auto ret = layoutProperty_->GetMaxCountValue(0);
    EXPECT_EQ(ret, maxCount.value());

    maxCount = -1;
    GridModelStatic::SetMaxCount(AceType::RawPtr(frameNode_), maxCount);
    EXPECT_FALSE(layoutProperty_->GetMaxCount().has_value());

    maxCount.reset();
    GridModelStatic::SetMaxCount(AceType::RawPtr(frameNode_), maxCount);
    EXPECT_FALSE(layoutProperty_->GetMaxCount().has_value());
}

/**
 * @tc.name: SetScrollEnabled
 * @tc.desc: Test SetScrollEnabled
 * @tc.type: FUNC
 */
HWTEST_F(GridModelStaticTestNg, SetScrollEnabled, TestSize.Level1)
{
    CreateGrid();
    std::optional<bool> scrollEnabled = true;
    GridModelStatic::SetScrollEnabled(AceType::RawPtr(frameNode_), scrollEnabled);
    ASSERT_NE(layoutProperty_, nullptr);
    auto ret = layoutProperty_->GetScrollEnabledValue(false);
    EXPECT_EQ(ret, scrollEnabled.value());

    scrollEnabled.reset();
    GridModelStatic::SetScrollEnabled(AceType::RawPtr(frameNode_), scrollEnabled);
    EXPECT_FALSE(layoutProperty_->GetScrollEnabled().has_value());
}

/**
 * @tc.name: SetColumnsGap
 * @tc.desc: Test SetColumnsGap
 * @tc.type: FUNC
 */
HWTEST_F(GridModelStaticTestNg, SetColumnsGap, TestSize.Level1)
{
    CreateGrid();
    std::optional<Dimension> columnsGap = Dimension(20);
    GridModelStatic::SetColumnsGap(AceType::RawPtr(frameNode_), columnsGap);
    ASSERT_NE(layoutProperty_, nullptr);
    auto ret = layoutProperty_->GetColumnsGapValue();
    EXPECT_EQ(ret, columnsGap.value());

    columnsGap.reset();
    GridModelStatic::SetColumnsGap(AceType::RawPtr(frameNode_), columnsGap);
    EXPECT_FALSE(layoutProperty_->GetColumnsGap().has_value());
}

/**
 * @tc.name: SetRowsGap
 * @tc.desc: Test SetRowsGap
 * @tc.type: FUNC
 */
HWTEST_F(GridModelStaticTestNg, SetRowsGap, TestSize.Level1)
{
    CreateGrid();
    std::optional<Dimension> rowsGap = Dimension(20);
    GridModelStatic::SetRowsGap(AceType::RawPtr(frameNode_), rowsGap);
    ASSERT_NE(layoutProperty_, nullptr);
    auto ret = layoutProperty_->GetRowsGapValue();
    EXPECT_EQ(ret, rowsGap.value());

    rowsGap.reset();
    GridModelStatic::SetRowsGap(AceType::RawPtr(frameNode_), rowsGap);
    EXPECT_FALSE(layoutProperty_->GetRowsGap().has_value());
}
} // namespace OHOS::Ace::NG
