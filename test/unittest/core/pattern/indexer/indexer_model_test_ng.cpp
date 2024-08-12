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

#include "indexer_test_ng.h"
namespace OHOS::Ace::NG {

namespace {
InspectorFilter filter;
std::vector<std::string> CREATE_ARRAY = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
    "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
std::vector<std::string> CREATE_ARRAY_1 = { "A", "B", "C", "D", "E", "F", "G", "H", "I"};
std::vector<std::string> CREATE_ARRAY_2 = { "#", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L"};
} // namespace

class IndexerModelTestNg : public IndexerTestNg {
public:
};

/**
 * @tc.name: OnModifyDone009
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and mode is 7+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone009, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(16, DimensionUnit::FP));
    CreateDone();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemHeight_ = 24.f;
    indexerLayoutAlgorithm->maxContentHeight_ = 160.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    pattern_->OnModifyDone();

    std::vector<std::pair<std::string, bool>> arrayValueRst;
    arrayValueRst.push_back(std::pair("A", false));
    arrayValueRst.push_back(std::pair("B", true));
    arrayValueRst.push_back(std::pair("G", false));
    arrayValueRst.push_back(std::pair("H", true));
    arrayValueRst.push_back(std::pair("M", false));
    arrayValueRst.push_back(std::pair("N", true));
    arrayValueRst.push_back(std::pair("S", false));
    arrayValueRst.push_back(std::pair("T", true));
    arrayValueRst.push_back(std::pair("Z", false));

    EXPECT_TRUE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), arrayValueRst.size());
    for (int32_t index = 0; index < arrayValueRst.size(); index++) {
        EXPECT_EQ(arrayValueRst[index].first, pattern_->arrayValue_[index].first);
        EXPECT_EQ(arrayValueRst[index].second, pattern_->arrayValue_[index].second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
}

/**
 * @tc.name: OnModifyDone0010
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and mode is 7+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0010, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(16, DimensionUnit::PX));
    CreateDone();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemHeight_ = 24.f;
    indexerLayoutAlgorithm->maxContentHeight_ = 160.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    pattern_->OnModifyDone();
    std::vector<std::pair<std::string, bool>> arrayValueRst;
    arrayValueRst.push_back(std::pair("A", false));
    arrayValueRst.push_back(std::pair("B", true));
    arrayValueRst.push_back(std::pair("G", false));
    arrayValueRst.push_back(std::pair("H", true));
    arrayValueRst.push_back(std::pair("M", false));
    arrayValueRst.push_back(std::pair("N", true));
    arrayValueRst.push_back(std::pair("S", false));
    arrayValueRst.push_back(std::pair("T", true));
    arrayValueRst.push_back(std::pair("Z", false));

    EXPECT_TRUE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), arrayValueRst.size());
    for (int32_t index = 0; index < arrayValueRst.size(); index++) {
        EXPECT_EQ(arrayValueRst[index].first, pattern_->arrayValue_[index].first);
        EXPECT_EQ(arrayValueRst[index].second, pattern_->arrayValue_[index].second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
}

/**
 * @tc.name: OnModifyDone0011
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and mode is 7+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0011, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(6, DimensionUnit::PERCENT));
    CreateDone();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemHeight_ = 24.f;
    indexerLayoutAlgorithm->maxContentHeight_ = 160.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    pattern_->OnModifyDone();

    std::vector<std::pair<std::string, bool>> arrayValueRst;
    arrayValueRst.push_back(std::pair("A", false));
    arrayValueRst.push_back(std::pair("B", true));
    arrayValueRst.push_back(std::pair("G", false));
    arrayValueRst.push_back(std::pair("H", true));
    arrayValueRst.push_back(std::pair("M", false));
    arrayValueRst.push_back(std::pair("N", true));
    arrayValueRst.push_back(std::pair("S", false));
    arrayValueRst.push_back(std::pair("T", true));
    arrayValueRst.push_back(std::pair("Z", false));

    EXPECT_TRUE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), arrayValueRst.size());
    for (int32_t index = 0; index < arrayValueRst.size(); index++) {
        EXPECT_EQ(arrayValueRst[index].first, pattern_->arrayValue_[index].first);
        EXPECT_EQ(arrayValueRst[index].second, pattern_->arrayValue_[index].second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
}
/**
 * @tc.name: OnModifyDone0012
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and mode is 7+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0012, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(16, DimensionUnit::LPX));
    CreateDone();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemHeight_ = 24.f;
    indexerLayoutAlgorithm->maxContentHeight_ = 160.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    pattern_->OnModifyDone();

    std::vector<std::pair<std::string, bool>> arrayValueRst;
    arrayValueRst.push_back(std::pair("A", false));
    arrayValueRst.push_back(std::pair("B", true));
    arrayValueRst.push_back(std::pair("G", false));
    arrayValueRst.push_back(std::pair("H", true));
    arrayValueRst.push_back(std::pair("M", false));
    arrayValueRst.push_back(std::pair("N", true));
    arrayValueRst.push_back(std::pair("S", false));
    arrayValueRst.push_back(std::pair("T", true));
    arrayValueRst.push_back(std::pair("Z", false));

    EXPECT_TRUE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), arrayValueRst.size());
    for (int32_t index = 0; index < arrayValueRst.size(); index++) {
        EXPECT_EQ(arrayValueRst[index].first, pattern_->arrayValue_[index].first);
        EXPECT_EQ(arrayValueRst[index].second, pattern_->arrayValue_[index].second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
}

/**
 * @tc.name: OnModifyDone0013
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and mode is 7+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0013, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(9, DimensionUnit::VP));
    CreateDone();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemHeight_ = 24.f;
    indexerLayoutAlgorithm->maxContentHeight_ = 95.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    pattern_->OnModifyDone();

    std::vector<std::pair<std::string, bool>> arrayValueRst;
    arrayValueRst.push_back(std::pair("A", false));
    arrayValueRst.push_back(std::pair("B", true));
    arrayValueRst.push_back(std::pair("G", false));
    arrayValueRst.push_back(std::pair("H", true));
    arrayValueRst.push_back(std::pair("M", false));
    arrayValueRst.push_back(std::pair("N", true));
    arrayValueRst.push_back(std::pair("S", false));
    arrayValueRst.push_back(std::pair("T", true));
    arrayValueRst.push_back(std::pair("Z", false));

    EXPECT_TRUE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), arrayValueRst.size());
    for (int32_t index = 0; index < arrayValueRst.size(); index++) {
        EXPECT_EQ(arrayValueRst[index].first, pattern_->arrayValue_[index].first);
        EXPECT_EQ(arrayValueRst[index].second, pattern_->arrayValue_[index].second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
}

/**
 * @tc.name: OnModifyDone0014
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and mode is 7+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0014, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(19, DimensionUnit::FP));
    CreateDone();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemHeight_ = 24.f;
    indexerLayoutAlgorithm->maxContentHeight_ = 160.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    pattern_->OnModifyDone();

    std::vector<std::pair<std::string, bool>> arrayValueRst;
    arrayValueRst.push_back(std::pair("A", false));
    arrayValueRst.push_back(std::pair("B", true));
    arrayValueRst.push_back(std::pair("G", false));
    arrayValueRst.push_back(std::pair("H", true));
    arrayValueRst.push_back(std::pair("M", false));
    arrayValueRst.push_back(std::pair("N", true));
    arrayValueRst.push_back(std::pair("S", false));
    arrayValueRst.push_back(std::pair("T", true));
    arrayValueRst.push_back(std::pair("Z", false));

    EXPECT_TRUE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), arrayValueRst.size());
    for (int32_t index = 0; index < arrayValueRst.size(); index++) {
        EXPECT_EQ(arrayValueRst[index].first, pattern_->arrayValue_[index].first);
        EXPECT_EQ(arrayValueRst[index].second, pattern_->arrayValue_[index].second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
}

/**
 * @tc.name: OnModifyDone0015
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and mode is 7+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0015, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(19, DimensionUnit::PX));
    CreateDone();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemHeight_ = 24.f;
    indexerLayoutAlgorithm->maxContentHeight_ = 160.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    pattern_->OnModifyDone();

    std::vector<std::pair<std::string, bool>> arrayValueRst;
    arrayValueRst.push_back(std::pair("A", false));
    arrayValueRst.push_back(std::pair("B", true));
    arrayValueRst.push_back(std::pair("G", false));
    arrayValueRst.push_back(std::pair("H", true));
    arrayValueRst.push_back(std::pair("M", false));
    arrayValueRst.push_back(std::pair("N", true));
    arrayValueRst.push_back(std::pair("S", false));
    arrayValueRst.push_back(std::pair("T", true));
    arrayValueRst.push_back(std::pair("Z", false));

    EXPECT_TRUE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), arrayValueRst.size());
    for (int32_t index = 0; index < arrayValueRst.size(); index++) {
        EXPECT_EQ(arrayValueRst[index].first, pattern_->arrayValue_[index].first);
        EXPECT_EQ(arrayValueRst[index].second, pattern_->arrayValue_[index].second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
}

/**
 * @tc.name: OnModifyDone0016
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and mode is 7+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0016, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(9, DimensionUnit::PERCENT));
    CreateDone();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemHeight_ = 24.f;
    indexerLayoutAlgorithm->maxContentHeight_ = 160.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    pattern_->OnModifyDone();

    std::vector<std::pair<std::string, bool>> arrayValueRst;
    arrayValueRst.push_back(std::pair("A", false));
    arrayValueRst.push_back(std::pair("B", true));
    arrayValueRst.push_back(std::pair("G", false));
    arrayValueRst.push_back(std::pair("H", true));
    arrayValueRst.push_back(std::pair("M", false));
    arrayValueRst.push_back(std::pair("N", true));
    arrayValueRst.push_back(std::pair("S", false));
    arrayValueRst.push_back(std::pair("T", true));
    arrayValueRst.push_back(std::pair("Z", false));

    EXPECT_TRUE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), arrayValueRst.size());
    for (int32_t index = 0; index < arrayValueRst.size(); index++) {
        EXPECT_EQ(arrayValueRst[index].first, pattern_->arrayValue_[index].first);
        EXPECT_EQ(arrayValueRst[index].second, pattern_->arrayValue_[index].second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
}
/**
 * @tc.name: OnModifyDone0017
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and mode is 7+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0017, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(19, DimensionUnit::LPX));
    CreateDone();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemHeight_ = 24.f;
    indexerLayoutAlgorithm->maxContentHeight_ = 160.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    pattern_->OnModifyDone();

    std::vector<std::pair<std::string, bool>> arrayValueRst;
    arrayValueRst.push_back(std::pair("A", false));
    arrayValueRst.push_back(std::pair("B", true));
    arrayValueRst.push_back(std::pair("G", false));
    arrayValueRst.push_back(std::pair("H", true));
    arrayValueRst.push_back(std::pair("M", false));
    arrayValueRst.push_back(std::pair("N", true));
    arrayValueRst.push_back(std::pair("S", false));
    arrayValueRst.push_back(std::pair("T", true));
    arrayValueRst.push_back(std::pair("Z", false));

    EXPECT_TRUE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), arrayValueRst.size());
    for (int32_t index = 0; index < arrayValueRst.size(); index++) {
        EXPECT_EQ(arrayValueRst[index].first, pattern_->arrayValue_[index].first);
        EXPECT_EQ(arrayValueRst[index].second, pattern_->arrayValue_[index].second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
}

/**
 * @tc.name: OnModifyDone0018
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and mode is 7+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0018, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(19, DimensionUnit::NONE));
    CreateDone();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemHeight_ = 24.f;
    indexerLayoutAlgorithm->maxContentHeight_ = 160.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    pattern_->OnModifyDone();
    std::vector<std::pair<std::string, bool>> arrayValueRst;
    arrayValueRst.push_back(std::pair("A", false));
    arrayValueRst.push_back(std::pair("B", true));
    arrayValueRst.push_back(std::pair("G", false));
    arrayValueRst.push_back(std::pair("H", true));
    arrayValueRst.push_back(std::pair("M", false));
    arrayValueRst.push_back(std::pair("N", true));
    arrayValueRst.push_back(std::pair("S", false));
    arrayValueRst.push_back(std::pair("T", true));
    arrayValueRst.push_back(std::pair("Z", false));
    EXPECT_TRUE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), arrayValueRst.size());
    for (int32_t index = 0; index < arrayValueRst.size(); index++) {
        EXPECT_EQ(arrayValueRst[index].first, pattern_->arrayValue_[index].first);
        EXPECT_EQ(arrayValueRst[index].second, pattern_->arrayValue_[index].second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
}

/**
 * @tc.name: OnModifyDone0019
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and arrayValue size is more than 9,
 *           pattern height is enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0019, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_1, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(10, DimensionUnit::PX));
    CreateDone();

    EXPECT_FALSE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY_1.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), CREATE_ARRAY_1.size());
    for (auto value : pattern_->arrayValue_) {
        EXPECT_FALSE(value.second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);
}

/**
 * @tc.name: OnModifyDone0020
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and arrayValue size is more than 9,
 *           pattern height is enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0020, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_1, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(10, DimensionUnit::VP));
    CreateDone();

    EXPECT_FALSE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY_1.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), CREATE_ARRAY_1.size());
    for (auto value : pattern_->arrayValue_) {
        EXPECT_FALSE(value.second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);
}

/**
 * @tc.name: OnModifyDone0021
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and arrayValue size is more than 9,
 *           pattern height is enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0021, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_1, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(10, DimensionUnit::FP));
    CreateDone();

    EXPECT_FALSE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY_1.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), CREATE_ARRAY_1.size());
    for (auto value : pattern_->arrayValue_) {
        EXPECT_FALSE(value.second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);
}

/**
 * @tc.name: OnModifyDone0022
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and arrayValue size is more than 9,
 *           pattern height is enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0022, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_1, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(10, DimensionUnit::PERCENT));
    CreateDone();

    EXPECT_FALSE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY_1.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), CREATE_ARRAY_1.size());
    for (auto value : pattern_->arrayValue_) {
        EXPECT_FALSE(value.second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);
}

/**
 * @tc.name: OnModifyDone0023
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and arrayValue size is more than 9,
 *           pattern height is enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0023, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_1, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(10, DimensionUnit::PERCENT));
    CreateDone();

    EXPECT_FALSE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY_1.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), CREATE_ARRAY_1.size());
    for (auto value : pattern_->arrayValue_) {
        EXPECT_FALSE(value.second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);
}

/**
 * @tc.name: OnModifyDone0024
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and arrayValue size is more than 9,
 *           pattern height is enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0024, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_1, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(10, DimensionUnit::NONE));
    CreateDone();

    EXPECT_FALSE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY_1.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), CREATE_ARRAY_1.size());
    for (auto value : pattern_->arrayValue_) {
        EXPECT_FALSE(value.second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);
}

/**
 * @tc.name: OnModifyDone0025
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and arrayValue size is more than 9,
 *           pattern height is not enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0025, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_2, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(10, DimensionUnit::PX));
    CreateDone();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemHeight_ = 24.f;
    indexerLayoutAlgorithm->maxContentHeight_ = 100.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    pattern_->OnModifyDone();

    std::vector<std::pair<std::string, bool>> arrayValueRst;
    arrayValueRst.push_back(std::pair("#", false));
    arrayValueRst.push_back(std::pair("A", false));
    arrayValueRst.push_back(std::pair("B", true));
    arrayValueRst.push_back(std::pair("C", false));
    arrayValueRst.push_back(std::pair("D", true));
    arrayValueRst.push_back(std::pair("F", false));
    arrayValueRst.push_back(std::pair("G", true));
    arrayValueRst.push_back(std::pair("I", false));
    arrayValueRst.push_back(std::pair("J", true));
    arrayValueRst.push_back(std::pair("L", false));

    EXPECT_TRUE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY_2.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), arrayValueRst.size());
    for (int32_t index = 0; index < arrayValueRst.size(); index++) {
        EXPECT_EQ(arrayValueRst[index].first, pattern_->arrayValue_[index].first);
        EXPECT_EQ(arrayValueRst[index].second, pattern_->arrayValue_[index].second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
}

/**
 * @tc.name: OnModifyDone0026
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and arrayValue size is more than 9,
 *           pattern height is not enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0026, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_2, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(10, DimensionUnit::PX));
    CreateDone();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemHeight_ = 24.f;
    indexerLayoutAlgorithm->maxContentHeight_ = 100.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    pattern_->OnModifyDone();

    std::vector<std::pair<std::string, bool>> arrayValueRst;
    arrayValueRst.push_back(std::pair("#", false));
    arrayValueRst.push_back(std::pair("A", false));
    arrayValueRst.push_back(std::pair("B", true));
    arrayValueRst.push_back(std::pair("C", false));
    arrayValueRst.push_back(std::pair("D", true));
    arrayValueRst.push_back(std::pair("F", false));
    arrayValueRst.push_back(std::pair("G", true));
    arrayValueRst.push_back(std::pair("I", false));
    arrayValueRst.push_back(std::pair("J", true));
    arrayValueRst.push_back(std::pair("L", false));

    EXPECT_TRUE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY_2.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), arrayValueRst.size());
    for (int32_t index = 0; index < arrayValueRst.size(); index++) {
        EXPECT_EQ(arrayValueRst[index].first, pattern_->arrayValue_[index].first);
        EXPECT_EQ(arrayValueRst[index].second, pattern_->arrayValue_[index].second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
}

/**
 * @tc.name: OnModifyDone0027
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and arrayValue size is more than 9,
 *           pattern height is not enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0027, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_2, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(10, DimensionUnit::PERCENT));
    CreateDone();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemHeight_ = 24.f;
    indexerLayoutAlgorithm->maxContentHeight_ = 100.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    pattern_->OnModifyDone();

    std::vector<std::pair<std::string, bool>> arrayValueRst;
    arrayValueRst.push_back(std::pair("#", false));
    arrayValueRst.push_back(std::pair("A", false));
    arrayValueRst.push_back(std::pair("B", true));
    arrayValueRst.push_back(std::pair("C", false));
    arrayValueRst.push_back(std::pair("D", true));
    arrayValueRst.push_back(std::pair("F", false));
    arrayValueRst.push_back(std::pair("G", true));
    arrayValueRst.push_back(std::pair("I", false));
    arrayValueRst.push_back(std::pair("J", true));
    arrayValueRst.push_back(std::pair("L", false));

    EXPECT_TRUE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY_2.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), arrayValueRst.size());
    for (int32_t index = 0; index < arrayValueRst.size(); index++) {
        EXPECT_EQ(arrayValueRst[index].first, pattern_->arrayValue_[index].first);
        EXPECT_EQ(arrayValueRst[index].second, pattern_->arrayValue_[index].second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
}

/**
 * @tc.name: OnModifyDone0028
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and arrayValue size is more than 9,
 *           pattern height is not enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0028, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_2, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(10, DimensionUnit::NONE));
    CreateDone();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemHeight_ = 24.f;
    indexerLayoutAlgorithm->maxContentHeight_ = 100.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    pattern_->OnModifyDone();

    std::vector<std::pair<std::string, bool>> arrayValueRst;
    arrayValueRst.push_back(std::pair("#", false));
    arrayValueRst.push_back(std::pair("A", false));
    arrayValueRst.push_back(std::pair("B", true));
    arrayValueRst.push_back(std::pair("C", false));
    arrayValueRst.push_back(std::pair("D", true));
    arrayValueRst.push_back(std::pair("F", false));
    arrayValueRst.push_back(std::pair("G", true));
    arrayValueRst.push_back(std::pair("I", false));
    arrayValueRst.push_back(std::pair("J", true));
    arrayValueRst.push_back(std::pair("L", false));

    EXPECT_TRUE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY_2.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), arrayValueRst.size());
    for (int32_t index = 0; index < arrayValueRst.size(); index++) {
        EXPECT_EQ(arrayValueRst[index].first, pattern_->arrayValue_[index].first);
        EXPECT_EQ(arrayValueRst[index].second, pattern_->arrayValue_[index].second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
}


/**
 * @tc.name: OnModifyDone0029
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and arrayValue size is more than 9,
 *           pattern height is not enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0029, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_2, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(10, DimensionUnit::LPX));
    CreateDone();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemHeight_ = 24.f;
    indexerLayoutAlgorithm->maxContentHeight_ = 100.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    pattern_->OnModifyDone();

    std::vector<std::pair<std::string, bool>> arrayValueRst;
    arrayValueRst.push_back(std::pair("#", false));
    arrayValueRst.push_back(std::pair("A", false));
    arrayValueRst.push_back(std::pair("B", true));
    arrayValueRst.push_back(std::pair("C", false));
    arrayValueRst.push_back(std::pair("D", true));
    arrayValueRst.push_back(std::pair("F", false));
    arrayValueRst.push_back(std::pair("G", true));
    arrayValueRst.push_back(std::pair("I", false));
    arrayValueRst.push_back(std::pair("J", true));
    arrayValueRst.push_back(std::pair("L", false));

    EXPECT_TRUE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY_2.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), arrayValueRst.size());
    for (int32_t index = 0; index < arrayValueRst.size(); index++) {
        EXPECT_EQ(arrayValueRst[index].first, pattern_->arrayValue_[index].first);
        EXPECT_EQ(arrayValueRst[index].second, pattern_->arrayValue_[index].second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
}

/**
 * @tc.name: OnModifyDone0030
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and arrayValue size is more than 9,
 *           pattern height is not enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0030, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_2, 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(10, DimensionUnit::FP));
    CreateDone();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemHeight_ = 24.f;
    indexerLayoutAlgorithm->maxContentHeight_ = 100.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    pattern_->OnModifyDone();

    std::vector<std::pair<std::string, bool>> arrayValueRst;
    arrayValueRst.push_back(std::pair("#", false));
    arrayValueRst.push_back(std::pair("A", false));
    arrayValueRst.push_back(std::pair("B", true));
    arrayValueRst.push_back(std::pair("C", false));
    arrayValueRst.push_back(std::pair("D", true));
    arrayValueRst.push_back(std::pair("F", false));
    arrayValueRst.push_back(std::pair("G", true));
    arrayValueRst.push_back(std::pair("I", false));
    arrayValueRst.push_back(std::pair("J", true));
    arrayValueRst.push_back(std::pair("L", false));

    EXPECT_TRUE(pattern_->autoCollapse_);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY_2.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), arrayValueRst.size());
    for (int32_t index = 0; index < arrayValueRst.size(); index++) {
        EXPECT_EQ(arrayValueRst[index].first, pattern_->arrayValue_[index].first);
        EXPECT_EQ(arrayValueRst[index].second, pattern_->arrayValue_[index].second);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
}

/**
 * @tc.name: IndexerModelNGTest009
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, IndexerModelNGTest009, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetSelectedColor(Color::TRANSPARENT);
    model.SetColor(Color::TRANSPARENT);
    model.SetPopupColor(Color::TRANSPARENT);
    model.SetSelectedBackgroundColor(Color::TRANSPARENT);
    model.SetPopupBackground(Color::TRANSPARENT);
    model.SetUsingPopup(true);
    model.SetItemSize(Dimension(24));
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50));
    model.SetSelected(0);
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::VP));
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::VP));
    model.SetPopupItemBackground(Color::TRANSPARENT);
    model.SetPopupSelectedColor(Color::TRANSPARENT);
    model.SetPopupUnselectedColor(Color::TRANSPARENT);
    model.SetFontSize(Dimension(24));
    model.SetFontWeight(FontWeight::MEDIUM);
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY);
    EXPECT_EQ(layoutProperty_->GetSelectedColorValue(), Color::TRANSPARENT);
    EXPECT_EQ(layoutProperty_->GetColorValue(), Color::TRANSPARENT);
    EXPECT_EQ(layoutProperty_->GetPopupColorValue(), Color::TRANSPARENT);
    EXPECT_EQ(paintProperty_->GetSelectedBackgroundColorValue(), Color::TRANSPARENT);
    EXPECT_EQ(paintProperty_->GetPopupBackgroundValue(), Color::TRANSPARENT);
    EXPECT_TRUE(layoutProperty_->GetUsingPopupValue());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetAlignStyleValue(), AlignStyle::LEFT);
    EXPECT_EQ(layoutProperty_->GetPopupHorizontalSpaceValue(), Dimension(50));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetPopupPositionXValue(), Dimension(-96.f, DimensionUnit::VP));
    EXPECT_EQ(layoutProperty_->GetPopupPositionYValue(), Dimension(48.f, DimensionUnit::VP));
    EXPECT_EQ(paintProperty_->GetPopupItemBackgroundValue(), Color::TRANSPARENT);
    EXPECT_EQ(paintProperty_->GetPopupSelectedColorValue(), Color::TRANSPARENT);
    EXPECT_EQ(paintProperty_->GetPopupUnselectedColorValue(), Color::TRANSPARENT);
    EXPECT_EQ(layoutProperty_->GetFontSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetFontWeightValue(), FontWeight::MEDIUM);
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: IndexerModelNGTest0010
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, IndexerModelNGTest0010, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetSelectedColor(Color::WHITE);
    model.SetColor(Color::WHITE);
    model.SetPopupColor(Color::WHITE);
    model.SetSelectedBackgroundColor(Color::WHITE);
    model.SetPopupBackground(Color::WHITE);
    model.SetUsingPopup(true);
    model.SetItemSize(Dimension(24));
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50));
    model.SetSelected(0);
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::VP));
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::VP));
    model.SetPopupItemBackground(Color::WHITE);
    model.SetPopupSelectedColor(Color::WHITE);
    model.SetPopupUnselectedColor(Color::WHITE);
    model.SetFontSize(Dimension(24));
    model.SetFontWeight(FontWeight::MEDIUM);
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY);
    EXPECT_EQ(layoutProperty_->GetSelectedColorValue(), Color::WHITE);
    EXPECT_EQ(layoutProperty_->GetColorValue(), Color::WHITE);
    EXPECT_EQ(layoutProperty_->GetPopupColorValue(), Color::WHITE);
    EXPECT_EQ(paintProperty_->GetSelectedBackgroundColorValue(), Color::WHITE);
    EXPECT_EQ(paintProperty_->GetPopupBackgroundValue(), Color::WHITE);
    EXPECT_TRUE(layoutProperty_->GetUsingPopupValue());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetAlignStyleValue(), AlignStyle::LEFT);
    EXPECT_EQ(layoutProperty_->GetPopupHorizontalSpaceValue(), Dimension(50));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetPopupPositionXValue(), Dimension(-96.f, DimensionUnit::VP));
    EXPECT_EQ(layoutProperty_->GetPopupPositionYValue(), Dimension(48.f, DimensionUnit::VP));
    EXPECT_EQ(paintProperty_->GetPopupItemBackgroundValue(), Color::WHITE);
    EXPECT_EQ(paintProperty_->GetPopupSelectedColorValue(), Color::WHITE);
    EXPECT_EQ(paintProperty_->GetPopupUnselectedColorValue(), Color::WHITE);
    EXPECT_EQ(layoutProperty_->GetFontSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetFontWeightValue(), FontWeight::MEDIUM);
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: IndexerModelNGTest0011
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, IndexerModelNGTest0011, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetSelectedColor(Color::BLACK);
    model.SetColor(Color::BLACK);
    model.SetPopupColor(Color::BLACK);
    model.SetSelectedBackgroundColor(Color::BLACK);
    model.SetPopupBackground(Color::BLACK);
    model.SetUsingPopup(true);
    model.SetItemSize(Dimension(24));
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50));
    model.SetSelected(0);
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::VP));
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::VP));
    model.SetPopupItemBackground(Color::BLACK);
    model.SetPopupSelectedColor(Color::BLACK);
    model.SetPopupUnselectedColor(Color::BLACK);
    model.SetFontSize(Dimension(24));
    model.SetFontWeight(FontWeight::MEDIUM);
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY);
    EXPECT_EQ(layoutProperty_->GetSelectedColorValue(), Color::BLACK);
    EXPECT_EQ(layoutProperty_->GetColorValue(), Color::BLACK);
    EXPECT_EQ(layoutProperty_->GetPopupColorValue(), Color::BLACK);
    EXPECT_EQ(paintProperty_->GetSelectedBackgroundColorValue(), Color::BLACK);
    EXPECT_EQ(paintProperty_->GetPopupBackgroundValue(), Color::BLACK);
    EXPECT_TRUE(layoutProperty_->GetUsingPopupValue());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetAlignStyleValue(), AlignStyle::LEFT);
    EXPECT_EQ(layoutProperty_->GetPopupHorizontalSpaceValue(), Dimension(50));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetPopupPositionXValue(), Dimension(-96.f, DimensionUnit::VP));
    EXPECT_EQ(layoutProperty_->GetPopupPositionYValue(), Dimension(48.f, DimensionUnit::VP));
    EXPECT_EQ(paintProperty_->GetPopupItemBackgroundValue(), Color::BLACK);
    EXPECT_EQ(paintProperty_->GetPopupSelectedColorValue(), Color::BLACK);
    EXPECT_EQ(paintProperty_->GetPopupUnselectedColorValue(), Color::BLACK);
    EXPECT_EQ(layoutProperty_->GetFontSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetFontWeightValue(), FontWeight::MEDIUM);
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: IndexerModelNGTest0012
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, IndexerModelNGTest0012, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetSelectedColor(Color::RED);
    model.SetColor(Color::RED);
    model.SetPopupColor(Color::RED);
    model.SetSelectedBackgroundColor(Color::RED);
    model.SetPopupBackground(Color::RED);
    model.SetUsingPopup(true);
    model.SetItemSize(Dimension(24));
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50));
    model.SetSelected(0);
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::VP));
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::VP));
    model.SetPopupItemBackground(Color::RED);
    model.SetPopupSelectedColor(Color::RED);
    model.SetPopupUnselectedColor(Color::RED);
    model.SetFontSize(Dimension(24));
    model.SetFontWeight(FontWeight::MEDIUM);
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY);
    EXPECT_EQ(layoutProperty_->GetSelectedColorValue(), Color::RED);
    EXPECT_EQ(layoutProperty_->GetColorValue(), Color::RED);
    EXPECT_EQ(layoutProperty_->GetPopupColorValue(), Color::RED);
    EXPECT_EQ(paintProperty_->GetSelectedBackgroundColorValue(), Color::RED);
    EXPECT_EQ(paintProperty_->GetPopupBackgroundValue(), Color::RED);
    EXPECT_TRUE(layoutProperty_->GetUsingPopupValue());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetAlignStyleValue(), AlignStyle::LEFT);
    EXPECT_EQ(layoutProperty_->GetPopupHorizontalSpaceValue(), Dimension(50));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetPopupPositionXValue(), Dimension(-96.f, DimensionUnit::VP));
    EXPECT_EQ(layoutProperty_->GetPopupPositionYValue(), Dimension(48.f, DimensionUnit::VP));
    EXPECT_EQ(paintProperty_->GetPopupItemBackgroundValue(), Color::RED);
    EXPECT_EQ(paintProperty_->GetPopupSelectedColorValue(), Color::RED);
    EXPECT_EQ(paintProperty_->GetPopupUnselectedColorValue(), Color::RED);
    EXPECT_EQ(layoutProperty_->GetFontSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetFontWeightValue(), FontWeight::MEDIUM);
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: IndexerModelNGTest0013
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, IndexerModelNGTest0013, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetSelectedColor(Color::GREEN);
    model.SetColor(Color::GREEN);
    model.SetPopupColor(Color::GREEN);
    model.SetSelectedBackgroundColor(Color::GREEN);
    model.SetPopupBackground(Color::GREEN);
    model.SetUsingPopup(true);
    model.SetItemSize(Dimension(24));
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50));
    model.SetSelected(0);
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::VP));
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::VP));
    model.SetPopupItemBackground(Color::GREEN);
    model.SetPopupSelectedColor(Color::GREEN);
    model.SetPopupUnselectedColor(Color::GREEN);
    model.SetFontSize(Dimension(24));
    model.SetFontWeight(FontWeight::MEDIUM);
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY);
    EXPECT_EQ(layoutProperty_->GetSelectedColorValue(), Color::GREEN);
    EXPECT_EQ(layoutProperty_->GetColorValue(), Color::GREEN);
    EXPECT_EQ(layoutProperty_->GetPopupColorValue(), Color::GREEN);
    EXPECT_EQ(paintProperty_->GetSelectedBackgroundColorValue(), Color::GREEN);
    EXPECT_EQ(paintProperty_->GetPopupBackgroundValue(), Color::GREEN);
    EXPECT_TRUE(layoutProperty_->GetUsingPopupValue());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetAlignStyleValue(), AlignStyle::LEFT);
    EXPECT_EQ(layoutProperty_->GetPopupHorizontalSpaceValue(), Dimension(50));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetPopupPositionXValue(), Dimension(-96.f, DimensionUnit::VP));
    EXPECT_EQ(layoutProperty_->GetPopupPositionYValue(), Dimension(48.f, DimensionUnit::VP));
    EXPECT_EQ(paintProperty_->GetPopupItemBackgroundValue(), Color::GREEN);
    EXPECT_EQ(paintProperty_->GetPopupSelectedColorValue(), Color::GREEN);
    EXPECT_EQ(paintProperty_->GetPopupUnselectedColorValue(), Color::GREEN);
    EXPECT_EQ(layoutProperty_->GetFontSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetFontWeightValue(), FontWeight::MEDIUM);
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: IndexerModelNGTest0014
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, IndexerModelNGTest0014, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetSelectedColor(Color::BLUE);
    model.SetColor(Color::BLUE);
    model.SetPopupColor(Color::BLUE);
    model.SetSelectedBackgroundColor(Color::BLUE);
    model.SetPopupBackground(Color::BLUE);
    model.SetUsingPopup(true);
    model.SetItemSize(Dimension(24));
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50));
    model.SetSelected(0);
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::VP));
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::VP));
    model.SetPopupItemBackground(Color::BLUE);
    model.SetPopupSelectedColor(Color::BLUE);
    model.SetPopupUnselectedColor(Color::BLUE);
    model.SetFontSize(Dimension(24));
    model.SetFontWeight(FontWeight::MEDIUM);
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY);
    EXPECT_EQ(layoutProperty_->GetSelectedColorValue(), Color::BLUE);
    EXPECT_EQ(layoutProperty_->GetColorValue(), Color::BLUE);
    EXPECT_EQ(layoutProperty_->GetPopupColorValue(), Color::BLUE);
    EXPECT_EQ(paintProperty_->GetSelectedBackgroundColorValue(), Color::BLUE);
    EXPECT_EQ(paintProperty_->GetPopupBackgroundValue(), Color::BLUE);
    EXPECT_TRUE(layoutProperty_->GetUsingPopupValue());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetAlignStyleValue(), AlignStyle::LEFT);
    EXPECT_EQ(layoutProperty_->GetPopupHorizontalSpaceValue(), Dimension(50));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetPopupPositionXValue(), Dimension(-96.f, DimensionUnit::VP));
    EXPECT_EQ(layoutProperty_->GetPopupPositionYValue(), Dimension(48.f, DimensionUnit::VP));
    EXPECT_EQ(paintProperty_->GetPopupItemBackgroundValue(), Color::BLUE);
    EXPECT_EQ(paintProperty_->GetPopupSelectedColorValue(), Color::BLUE);
    EXPECT_EQ(paintProperty_->GetPopupUnselectedColorValue(), Color::BLUE);
    EXPECT_EQ(layoutProperty_->GetFontSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetFontWeightValue(), FontWeight::MEDIUM);
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: IndexerModelNGTest0015
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, IndexerModelNGTest0015, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetSelectedColor(Color::GRAY);
    model.SetColor(Color::GRAY);
    model.SetPopupColor(Color::GRAY);
    model.SetSelectedBackgroundColor(Color::GRAY);
    model.SetPopupBackground(Color::GRAY);
    model.SetUsingPopup(true);
    model.SetItemSize(Dimension(24));
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50));
    model.SetSelected(0);
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::VP));
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::VP));
    model.SetPopupItemBackground(Color::GRAY);
    model.SetPopupSelectedColor(Color::GRAY);
    model.SetPopupUnselectedColor(Color::GRAY);
    model.SetFontSize(Dimension(24));
    model.SetFontWeight(FontWeight::MEDIUM);
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY);
    EXPECT_EQ(layoutProperty_->GetSelectedColorValue(), Color::GRAY);
    EXPECT_EQ(layoutProperty_->GetColorValue(), Color::GRAY);
    EXPECT_EQ(layoutProperty_->GetPopupColorValue(), Color::GRAY);
    EXPECT_EQ(paintProperty_->GetSelectedBackgroundColorValue(), Color::GRAY);
    EXPECT_EQ(paintProperty_->GetPopupBackgroundValue(), Color::GRAY);
    EXPECT_TRUE(layoutProperty_->GetUsingPopupValue());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetAlignStyleValue(), AlignStyle::LEFT);
    EXPECT_EQ(layoutProperty_->GetPopupHorizontalSpaceValue(), Dimension(50));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetPopupPositionXValue(), Dimension(-96.f, DimensionUnit::VP));
    EXPECT_EQ(layoutProperty_->GetPopupPositionYValue(), Dimension(48.f, DimensionUnit::VP));
    EXPECT_EQ(paintProperty_->GetPopupItemBackgroundValue(), Color::GRAY);
    EXPECT_EQ(paintProperty_->GetPopupSelectedColorValue(), Color::GRAY);
    EXPECT_EQ(paintProperty_->GetPopupUnselectedColorValue(), Color::GRAY);
    EXPECT_EQ(layoutProperty_->GetFontSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetFontWeightValue(), FontWeight::MEDIUM);
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: IndexerModelNGTest0016
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, IndexerModelNGTest0016, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetSelectedColor(Color::FOREGROUND);
    model.SetColor(Color::FOREGROUND);
    model.SetPopupColor(Color::FOREGROUND);
    model.SetSelectedBackgroundColor(Color::FOREGROUND);
    model.SetPopupBackground(Color::FOREGROUND);
    model.SetUsingPopup(true);
    model.SetItemSize(Dimension(24));
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50));
    model.SetSelected(0);
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::VP));
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::VP));
    model.SetPopupItemBackground(Color::FOREGROUND);
    model.SetPopupSelectedColor(Color::FOREGROUND);
    model.SetPopupUnselectedColor(Color::FOREGROUND);
    model.SetFontSize(Dimension(24));
    model.SetFontWeight(FontWeight::MEDIUM);
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY);
    EXPECT_EQ(layoutProperty_->GetSelectedColorValue(), Color::FOREGROUND);
    EXPECT_EQ(layoutProperty_->GetColorValue(), Color::FOREGROUND);
    EXPECT_EQ(layoutProperty_->GetPopupColorValue(), Color::FOREGROUND);
    EXPECT_EQ(paintProperty_->GetSelectedBackgroundColorValue(), Color::FOREGROUND);
    EXPECT_EQ(paintProperty_->GetPopupBackgroundValue(), Color::FOREGROUND);
    EXPECT_TRUE(layoutProperty_->GetUsingPopupValue());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetAlignStyleValue(), AlignStyle::LEFT);
    EXPECT_EQ(layoutProperty_->GetPopupHorizontalSpaceValue(), Dimension(50));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetPopupPositionXValue(), Dimension(-96.f, DimensionUnit::VP));
    EXPECT_EQ(layoutProperty_->GetPopupPositionYValue(), Dimension(48.f, DimensionUnit::VP));
    EXPECT_EQ(paintProperty_->GetPopupItemBackgroundValue(), Color::FOREGROUND);
    EXPECT_EQ(paintProperty_->GetPopupSelectedColorValue(), Color::FOREGROUND);
    EXPECT_EQ(paintProperty_->GetPopupUnselectedColorValue(), Color::FOREGROUND);
    EXPECT_EQ(layoutProperty_->GetFontSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetFontWeightValue(), FontWeight::MEDIUM);
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: IndexerModelNGTest0017
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, IndexerModelNGTest0017, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetSelectedColor(Color::TRANSPARENT);
    model.SetColor(Color::TRANSPARENT);
    model.SetPopupColor(Color::TRANSPARENT);
    model.SetSelectedBackgroundColor(Color::TRANSPARENT);
    model.SetPopupBackground(Color::TRANSPARENT);
    model.SetUsingPopup(true);
    model.SetItemSize(Dimension(24));
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50));
    model.SetSelected(0);
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::PX));
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::PX));
    model.SetPopupItemBackground(Color::TRANSPARENT);
    model.SetPopupSelectedColor(Color::TRANSPARENT);
    model.SetPopupUnselectedColor(Color::TRANSPARENT);
    model.SetFontSize(Dimension(24));
    model.SetFontWeight(FontWeight::MEDIUM);
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY);
    EXPECT_EQ(layoutProperty_->GetSelectedColorValue(), Color::TRANSPARENT);
    EXPECT_EQ(layoutProperty_->GetColorValue(), Color::TRANSPARENT);
    EXPECT_EQ(layoutProperty_->GetPopupColorValue(), Color::TRANSPARENT);
    EXPECT_EQ(paintProperty_->GetSelectedBackgroundColorValue(), Color::TRANSPARENT);
    EXPECT_EQ(paintProperty_->GetPopupBackgroundValue(), Color::TRANSPARENT);
    EXPECT_TRUE(layoutProperty_->GetUsingPopupValue());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetAlignStyleValue(), AlignStyle::LEFT);
    EXPECT_EQ(layoutProperty_->GetPopupHorizontalSpaceValue(), Dimension(50));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetPopupPositionXValue(), Dimension(-96.f, DimensionUnit::PX));
    EXPECT_EQ(layoutProperty_->GetPopupPositionYValue(), Dimension(48.f, DimensionUnit::PX));
    EXPECT_EQ(paintProperty_->GetPopupItemBackgroundValue(), Color::TRANSPARENT);
    EXPECT_EQ(paintProperty_->GetPopupSelectedColorValue(), Color::TRANSPARENT);
    EXPECT_EQ(paintProperty_->GetPopupUnselectedColorValue(), Color::TRANSPARENT);
    EXPECT_EQ(layoutProperty_->GetFontSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetFontWeightValue(), FontWeight::MEDIUM);
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: IndexerModelNGTest0018
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, IndexerModelNGTest0018, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetSelectedColor(Color::WHITE);
    model.SetColor(Color::WHITE);
    model.SetPopupColor(Color::WHITE);
    model.SetSelectedBackgroundColor(Color::WHITE);
    model.SetPopupBackground(Color::WHITE);
    model.SetUsingPopup(true);
    model.SetItemSize(Dimension(24));
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50));
    model.SetSelected(0);
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::PX));
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::PX));
    model.SetPopupItemBackground(Color::WHITE);
    model.SetPopupSelectedColor(Color::WHITE);
    model.SetPopupUnselectedColor(Color::WHITE);
    model.SetFontSize(Dimension(24));
    model.SetFontWeight(FontWeight::MEDIUM);
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY);
    EXPECT_EQ(layoutProperty_->GetSelectedColorValue(), Color::WHITE);
    EXPECT_EQ(layoutProperty_->GetColorValue(), Color::WHITE);
    EXPECT_EQ(layoutProperty_->GetPopupColorValue(), Color::WHITE);
    EXPECT_EQ(paintProperty_->GetSelectedBackgroundColorValue(), Color::WHITE);
    EXPECT_EQ(paintProperty_->GetPopupBackgroundValue(), Color::WHITE);
    EXPECT_TRUE(layoutProperty_->GetUsingPopupValue());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetAlignStyleValue(), AlignStyle::LEFT);
    EXPECT_EQ(layoutProperty_->GetPopupHorizontalSpaceValue(), Dimension(50));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetPopupPositionXValue(), Dimension(-96.f, DimensionUnit::PX));
    EXPECT_EQ(layoutProperty_->GetPopupPositionYValue(), Dimension(48.f, DimensionUnit::PX));
    EXPECT_EQ(paintProperty_->GetPopupItemBackgroundValue(), Color::WHITE);
    EXPECT_EQ(paintProperty_->GetPopupSelectedColorValue(), Color::WHITE);
    EXPECT_EQ(paintProperty_->GetPopupUnselectedColorValue(), Color::WHITE);
    EXPECT_EQ(layoutProperty_->GetFontSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetFontWeightValue(), FontWeight::MEDIUM);
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: IndexerModelNGTest0019
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, IndexerModelNGTest0019, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetSelectedColor(Color::BLACK);
    model.SetColor(Color::BLACK);
    model.SetPopupColor(Color::BLACK);
    model.SetSelectedBackgroundColor(Color::BLACK);
    model.SetPopupBackground(Color::BLACK);
    model.SetUsingPopup(true);
    model.SetItemSize(Dimension(24));
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50));
    model.SetSelected(0);
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::PX));
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::PX));
    model.SetPopupItemBackground(Color::BLACK);
    model.SetPopupSelectedColor(Color::BLACK);
    model.SetPopupUnselectedColor(Color::BLACK);
    model.SetFontSize(Dimension(24));
    model.SetFontWeight(FontWeight::MEDIUM);
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY);
    EXPECT_EQ(layoutProperty_->GetSelectedColorValue(), Color::BLACK);
    EXPECT_EQ(layoutProperty_->GetColorValue(), Color::BLACK);
    EXPECT_EQ(layoutProperty_->GetPopupColorValue(), Color::BLACK);
    EXPECT_EQ(paintProperty_->GetSelectedBackgroundColorValue(), Color::BLACK);
    EXPECT_EQ(paintProperty_->GetPopupBackgroundValue(), Color::BLACK);
    EXPECT_TRUE(layoutProperty_->GetUsingPopupValue());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetAlignStyleValue(), AlignStyle::LEFT);
    EXPECT_EQ(layoutProperty_->GetPopupHorizontalSpaceValue(), Dimension(50));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetPopupPositionXValue(), Dimension(-96.f, DimensionUnit::PX));
    EXPECT_EQ(layoutProperty_->GetPopupPositionYValue(), Dimension(48.f, DimensionUnit::PX));
    EXPECT_EQ(paintProperty_->GetPopupItemBackgroundValue(), Color::BLACK);
    EXPECT_EQ(paintProperty_->GetPopupSelectedColorValue(), Color::BLACK);
    EXPECT_EQ(paintProperty_->GetPopupUnselectedColorValue(), Color::BLACK);
    EXPECT_EQ(layoutProperty_->GetFontSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetFontWeightValue(), FontWeight::MEDIUM);
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: IndexerModelNGTest0020
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, IndexerModelNGTest0020, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetSelectedColor(Color::RED);
    model.SetColor(Color::RED);
    model.SetPopupColor(Color::RED);
    model.SetSelectedBackgroundColor(Color::RED);
    model.SetPopupBackground(Color::RED);
    model.SetUsingPopup(true);
    model.SetItemSize(Dimension(24));
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50));
    model.SetSelected(0);
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::PX));
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::PX));
    model.SetPopupItemBackground(Color::RED);
    model.SetPopupSelectedColor(Color::RED);
    model.SetPopupUnselectedColor(Color::RED);
    model.SetFontSize(Dimension(24));
    model.SetFontWeight(FontWeight::MEDIUM);
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY);
    EXPECT_EQ(layoutProperty_->GetSelectedColorValue(), Color::RED);
    EXPECT_EQ(layoutProperty_->GetColorValue(), Color::RED);
    EXPECT_EQ(layoutProperty_->GetPopupColorValue(), Color::RED);
    EXPECT_EQ(paintProperty_->GetSelectedBackgroundColorValue(), Color::RED);
    EXPECT_EQ(paintProperty_->GetPopupBackgroundValue(), Color::RED);
    EXPECT_TRUE(layoutProperty_->GetUsingPopupValue());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetAlignStyleValue(), AlignStyle::LEFT);
    EXPECT_EQ(layoutProperty_->GetPopupHorizontalSpaceValue(), Dimension(50));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetPopupPositionXValue(), Dimension(-96.f, DimensionUnit::PX));
    EXPECT_EQ(layoutProperty_->GetPopupPositionYValue(), Dimension(48.f, DimensionUnit::PX));
    EXPECT_EQ(paintProperty_->GetPopupItemBackgroundValue(), Color::RED);
    EXPECT_EQ(paintProperty_->GetPopupSelectedColorValue(), Color::RED);
    EXPECT_EQ(paintProperty_->GetPopupUnselectedColorValue(), Color::RED);
    EXPECT_EQ(layoutProperty_->GetFontSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetFontWeightValue(), FontWeight::MEDIUM);
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: IndexerModelNGTest0021
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, IndexerModelNGTest0021, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetSelectedColor(Color::GREEN);
    model.SetColor(Color::GREEN);
    model.SetPopupColor(Color::GREEN);
    model.SetSelectedBackgroundColor(Color::GREEN);
    model.SetPopupBackground(Color::GREEN);
    model.SetUsingPopup(true);
    model.SetItemSize(Dimension(24));
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50));
    model.SetSelected(0);
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::FP));
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::FP));
    model.SetPopupItemBackground(Color::GREEN);
    model.SetPopupSelectedColor(Color::GREEN);
    model.SetPopupUnselectedColor(Color::GREEN);
    model.SetFontSize(Dimension(24));
    model.SetFontWeight(FontWeight::MEDIUM);
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY);
    EXPECT_EQ(layoutProperty_->GetSelectedColorValue(), Color::GREEN);
    EXPECT_EQ(layoutProperty_->GetColorValue(), Color::GREEN);
    EXPECT_EQ(layoutProperty_->GetPopupColorValue(), Color::GREEN);
    EXPECT_EQ(paintProperty_->GetSelectedBackgroundColorValue(), Color::GREEN);
    EXPECT_EQ(paintProperty_->GetPopupBackgroundValue(), Color::GREEN);
    EXPECT_TRUE(layoutProperty_->GetUsingPopupValue());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetAlignStyleValue(), AlignStyle::LEFT);
    EXPECT_EQ(layoutProperty_->GetPopupHorizontalSpaceValue(), Dimension(50));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetPopupPositionXValue(), Dimension(-96.f, DimensionUnit::FP));
    EXPECT_EQ(layoutProperty_->GetPopupPositionYValue(), Dimension(48.f, DimensionUnit::FP));
    EXPECT_EQ(paintProperty_->GetPopupItemBackgroundValue(), Color::GREEN);
    EXPECT_EQ(paintProperty_->GetPopupSelectedColorValue(), Color::GREEN);
    EXPECT_EQ(paintProperty_->GetPopupUnselectedColorValue(), Color::GREEN);
    EXPECT_EQ(layoutProperty_->GetFontSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetFontWeightValue(), FontWeight::MEDIUM);
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: IndexerModelNGTest0022
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, IndexerModelNGTest0022, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetSelectedColor(Color::BLUE);
    model.SetColor(Color::BLUE);
    model.SetPopupColor(Color::BLUE);
    model.SetSelectedBackgroundColor(Color::BLUE);
    model.SetPopupBackground(Color::BLUE);
    model.SetUsingPopup(true);
    model.SetItemSize(Dimension(24));
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50));
    model.SetSelected(0);
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::FP));
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::FP));
    model.SetPopupItemBackground(Color::BLUE);
    model.SetPopupSelectedColor(Color::BLUE);
    model.SetPopupUnselectedColor(Color::BLUE);
    model.SetFontSize(Dimension(24));
    model.SetFontWeight(FontWeight::MEDIUM);
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY);
    EXPECT_EQ(layoutProperty_->GetSelectedColorValue(), Color::BLUE);
    EXPECT_EQ(layoutProperty_->GetColorValue(), Color::BLUE);
    EXPECT_EQ(layoutProperty_->GetPopupColorValue(), Color::BLUE);
    EXPECT_EQ(paintProperty_->GetSelectedBackgroundColorValue(), Color::BLUE);
    EXPECT_EQ(paintProperty_->GetPopupBackgroundValue(), Color::BLUE);
    EXPECT_TRUE(layoutProperty_->GetUsingPopupValue());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetAlignStyleValue(), AlignStyle::LEFT);
    EXPECT_EQ(layoutProperty_->GetPopupHorizontalSpaceValue(), Dimension(50));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetPopupPositionXValue(), Dimension(-96.f, DimensionUnit::FP));
    EXPECT_EQ(layoutProperty_->GetPopupPositionYValue(), Dimension(48.f, DimensionUnit::FP));
    EXPECT_EQ(paintProperty_->GetPopupItemBackgroundValue(), Color::BLUE);
    EXPECT_EQ(paintProperty_->GetPopupSelectedColorValue(), Color::BLUE);
    EXPECT_EQ(paintProperty_->GetPopupUnselectedColorValue(), Color::BLUE);
    EXPECT_EQ(layoutProperty_->GetFontSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetFontWeightValue(), FontWeight::MEDIUM);
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: IndexerModelNGTest0023
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, IndexerModelNGTest0023, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetSelectedColor(Color::GRAY);
    model.SetColor(Color::GRAY);
    model.SetPopupColor(Color::GRAY);
    model.SetSelectedBackgroundColor(Color::GRAY);
    model.SetPopupBackground(Color::GRAY);
    model.SetUsingPopup(true);
    model.SetItemSize(Dimension(24));
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50));
    model.SetSelected(0);
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::FP));
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::FP));
    model.SetPopupItemBackground(Color::GRAY);
    model.SetPopupSelectedColor(Color::GRAY);
    model.SetPopupUnselectedColor(Color::GRAY);
    model.SetFontSize(Dimension(24));
    model.SetFontWeight(FontWeight::MEDIUM);
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY);
    EXPECT_EQ(layoutProperty_->GetSelectedColorValue(), Color::GRAY);
    EXPECT_EQ(layoutProperty_->GetColorValue(), Color::GRAY);
    EXPECT_EQ(layoutProperty_->GetPopupColorValue(), Color::GRAY);
    EXPECT_EQ(paintProperty_->GetSelectedBackgroundColorValue(), Color::GRAY);
    EXPECT_EQ(paintProperty_->GetPopupBackgroundValue(), Color::GRAY);
    EXPECT_TRUE(layoutProperty_->GetUsingPopupValue());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetAlignStyleValue(), AlignStyle::LEFT);
    EXPECT_EQ(layoutProperty_->GetPopupHorizontalSpaceValue(), Dimension(50));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetPopupPositionXValue(), Dimension(-96.f, DimensionUnit::FP));
    EXPECT_EQ(layoutProperty_->GetPopupPositionYValue(), Dimension(48.f, DimensionUnit::FP));
    EXPECT_EQ(paintProperty_->GetPopupItemBackgroundValue(), Color::GRAY);
    EXPECT_EQ(paintProperty_->GetPopupSelectedColorValue(), Color::GRAY);
    EXPECT_EQ(paintProperty_->GetPopupUnselectedColorValue(), Color::GRAY);
    EXPECT_EQ(layoutProperty_->GetFontSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetFontWeightValue(), FontWeight::MEDIUM);
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: IndexerModelNGTest0024
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, IndexerModelNGTest0024, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetSelectedColor(Color::FOREGROUND);
    model.SetColor(Color::FOREGROUND);
    model.SetPopupColor(Color::FOREGROUND);
    model.SetSelectedBackgroundColor(Color::FOREGROUND);
    model.SetPopupBackground(Color::FOREGROUND);
    model.SetUsingPopup(true);
    model.SetItemSize(Dimension(24));
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50));
    model.SetSelected(0);
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::FP));
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::FP));
    model.SetPopupItemBackground(Color::FOREGROUND);
    model.SetPopupSelectedColor(Color::FOREGROUND);
    model.SetPopupUnselectedColor(Color::FOREGROUND);
    model.SetFontSize(Dimension(24));
    model.SetFontWeight(FontWeight::MEDIUM);
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), CREATE_ARRAY);
    EXPECT_EQ(layoutProperty_->GetSelectedColorValue(), Color::FOREGROUND);
    EXPECT_EQ(layoutProperty_->GetColorValue(), Color::FOREGROUND);
    EXPECT_EQ(layoutProperty_->GetPopupColorValue(), Color::FOREGROUND);
    EXPECT_EQ(paintProperty_->GetSelectedBackgroundColorValue(), Color::FOREGROUND);
    EXPECT_EQ(paintProperty_->GetPopupBackgroundValue(), Color::FOREGROUND);
    EXPECT_TRUE(layoutProperty_->GetUsingPopupValue());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetAlignStyleValue(), AlignStyle::LEFT);
    EXPECT_EQ(layoutProperty_->GetPopupHorizontalSpaceValue(), Dimension(50));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetPopupPositionXValue(), Dimension(-96.f, DimensionUnit::FP));
    EXPECT_EQ(layoutProperty_->GetPopupPositionYValue(), Dimension(48.f, DimensionUnit::FP));
    EXPECT_EQ(paintProperty_->GetPopupItemBackgroundValue(), Color::FOREGROUND);
    EXPECT_EQ(paintProperty_->GetPopupSelectedColorValue(), Color::FOREGROUND);
    EXPECT_EQ(paintProperty_->GetPopupUnselectedColorValue(), Color::FOREGROUND);
    EXPECT_EQ(layoutProperty_->GetFontSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetFontWeightValue(), FontWeight::MEDIUM);
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}
} // namespace OHOS::Ace::NG
