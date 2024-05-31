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

#include <optional>

#include "gtest/gtest.h"

#include "base/geometry/dimension.h"

#define protected public
#define private public
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/indexer/indexer_layout_property.h"
#include "core/components_ng/pattern/indexer/indexer_model_ng.h"
#include "core/components_ng/pattern/indexer/indexer_paint_property.h"
#include "core/components_ng/pattern/indexer/indexer_pattern.h"
#include "core/components_ng/pattern/indexer/indexer_theme.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
std::vector<std::string> CREATE_ARRAY = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
    "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
std::vector<std::string> CREATE_ARRAY_1 = { "A", "B", "C", "D", "E", "F", "G", "H", "I"};
std::vector<std::string> CREATE_ARRAY_2 = { "#", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L"};
} // namespace

class IndexerModelTestNg : public TestNG {
public:
    void TearDown() override;
    void GetInstance();
    void Create(const std::function<void(IndexerModelNG)>& callback = nullptr,
        std::vector<std::string> arrayValue = CREATE_ARRAY, int32_t selected = 0);
    float GetFirstChildOffsetY();
    AssertionResult Selected(int32_t expectSelected);
    void MoveIndex(GestureEvent gestureEvent);
    AssertionResult Touch(TouchType touchType, float locationY, int32_t expectSelected);
    RefPtr<FrameNode> frameNode_;
    RefPtr<IndexerPattern> pattern_;
    RefPtr<IndexerEventHub> eventHub_;
    RefPtr<IndexerLayoutProperty> layoutProperty_;
    RefPtr<IndexerPaintProperty> paintProperty_;
    RefPtr<IndexerAccessibilityProperty> accessibilityProperty_;
};

void IndexerModelTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    paintProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void IndexerModelTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<IndexerPattern>();
    eventHub_ = frameNode_->GetEventHub<IndexerEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<IndexerLayoutProperty>();
    paintProperty_ = frameNode_->GetPaintProperty<IndexerPaintProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<IndexerAccessibilityProperty>();
}

void IndexerModelTestNg::Create(
    const std::function<void(IndexerModelNG)>& callback, std::vector<std::string> arrayValue, int32_t selected)
{
    IndexerModelNG model;
    model.Create(arrayValue, selected);
    if (callback) {
        callback(model);
    }
    GetInstance();
    FlushLayoutTask(frameNode_);
}

float IndexerModelTestNg::GetFirstChildOffsetY()
{
    if (pattern_->itemCount_ > 0) {
        return GetChildRect(frameNode_, 0).GetY();
    }
    return 0.f;
}

AssertionResult IndexerModelTestNg::Selected(int32_t expectSelected)
{
    return IsEqual(pattern_->GetSelected(), expectSelected);
}

void IndexerModelTestNg::MoveIndex(GestureEvent gestureEvent)
{
    auto start = pattern_->panEvent_->GetActionStartEventFunc();
    auto update = pattern_->panEvent_->GetActionUpdateEventFunc();
    start(gestureEvent);
    update(gestureEvent);
}

AssertionResult IndexerModelTestNg::Touch(TouchType touchType, float locationY, int32_t expectSelected)
{
    float firstOffsetY = GetFirstChildOffsetY();
    TouchEventInfo touchEventInfo = CreateTouchEventInfo(touchType, Offset(0.f, locationY + firstOffsetY));
    auto touchFuc = pattern_->touchListener_->GetTouchEventCallback();
    touchFuc(touchEventInfo);
    return Selected(expectSelected);
}

/**
 * @tc.name: OnModifyDone009
 * @tc.desc: Test OnModifyDone when autocollapse is open, and mode is 7+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone009, TestSize.Level1)
{
    Create([](IndexerModelNG model) {
        model.SetAutoCollapse(true);
        model.SetItemSize(Dimension(6, DimensionUnit::FP));
    }, CREATE_ARRAY, 0);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = 24.f;
    indexerLayoutAlgorithm->actualHeight_ = 160.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);

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

    EXPECT_EQ(pattern_->autoCollapse_, true);
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
 * @tc.desc: Test OnModifyDone when autocollapse is open, and mode is 7+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0010, TestSize.Level1)
{
    Create([](IndexerModelNG model) {
        model.SetAutoCollapse(true);
        model.SetItemSize(Dimension(6, DimensionUnit::PX));
    }, CREATE_ARRAY, 0);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = 24.f;
    indexerLayoutAlgorithm->actualHeight_ = 160.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
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

    EXPECT_EQ(pattern_->autoCollapse_, true);
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
 * @tc.desc: Test OnModifyDone when autocollapse is open, and mode is 7+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0011, TestSize.Level1)
{
    Create([](IndexerModelNG model) {
        model.SetAutoCollapse(true);
        model.SetItemSize(Dimension(6, DimensionUnit::PERCENT));
    }, CREATE_ARRAY, 0);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = 24.f;
    indexerLayoutAlgorithm->actualHeight_ = 160.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);

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

    EXPECT_EQ(pattern_->autoCollapse_, true);
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
 * @tc.desc: Test OnModifyDone when autocollapse is open, and mode is 7+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0012, TestSize.Level1)
{
    Create([](IndexerModelNG model) {
        model.SetAutoCollapse(true);
        model.SetItemSize(Dimension(6, DimensionUnit::LPX));
    }, CREATE_ARRAY, 0);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = 24.f;
    indexerLayoutAlgorithm->actualHeight_ = 160.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);

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

    EXPECT_EQ(pattern_->autoCollapse_, true);
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
 * @tc.desc: Test OnModifyDone when autocollapse is open, and mode is 7+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0013, TestSize.Level1)
{
    Create([](IndexerModelNG model) {
        model.SetAutoCollapse(true);
        model.SetItemSize(Dimension(9, DimensionUnit::VP));
    }, CREATE_ARRAY, 0);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = 24.f;
    indexerLayoutAlgorithm->actualHeight_ = 95.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);

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

    EXPECT_EQ(pattern_->autoCollapse_, true);
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
 * @tc.desc: Test OnModifyDone when autocollapse is open, and mode is 7+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0014, TestSize.Level1)
{
    Create([](IndexerModelNG model) {
        model.SetAutoCollapse(true);
        model.SetItemSize(Dimension(9, DimensionUnit::FP));
    }, CREATE_ARRAY, 0);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = 24.f;
    indexerLayoutAlgorithm->actualHeight_ = 160.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);

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

    EXPECT_EQ(pattern_->autoCollapse_, true);
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
 * @tc.desc: Test OnModifyDone when autocollapse is open, and mode is 7+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0015, TestSize.Level1)
{
    Create([](IndexerModelNG model) {
        model.SetAutoCollapse(true);
        model.SetItemSize(Dimension(9, DimensionUnit::PX));
    }, CREATE_ARRAY, 0);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = 24.f;
    indexerLayoutAlgorithm->actualHeight_ = 160.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);

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

    EXPECT_EQ(pattern_->autoCollapse_, true);
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
 * @tc.desc: Test OnModifyDone when autocollapse is open, and mode is 7+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0016, TestSize.Level1)
{
    Create([](IndexerModelNG model) {
        model.SetAutoCollapse(true);
        model.SetItemSize(Dimension(9, DimensionUnit::PERCENT));
    }, CREATE_ARRAY, 0);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = 24.f;
    indexerLayoutAlgorithm->actualHeight_ = 160.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);

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

    EXPECT_EQ(pattern_->autoCollapse_, true);
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
 * @tc.desc: Test OnModifyDone when autocollapse is open, and mode is 7+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0017, TestSize.Level1)
{
    Create([](IndexerModelNG model) {
        model.SetAutoCollapse(true);
        model.SetItemSize(Dimension(9, DimensionUnit::LPX));
    }, CREATE_ARRAY, 0);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = 24.f;
    indexerLayoutAlgorithm->actualHeight_ = 160.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);

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

    EXPECT_EQ(pattern_->autoCollapse_, true);
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
 * @tc.desc: Test OnModifyDone when autocollapse is open, and mode is 7+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0018, TestSize.Level1)
{
    Create([](IndexerModelNG model) {
        model.SetAutoCollapse(true);
        model.SetItemSize(Dimension(9, DimensionUnit::NONE));
    }, CREATE_ARRAY, 0);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = 24.f;
    indexerLayoutAlgorithm->actualHeight_ = 160.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
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
    EXPECT_EQ(pattern_->autoCollapse_, true);
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
 * @tc.desc: Test OnModifyDone when autocollapse is open, and arrayValue size is more than 9,
 *           pattern height is enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0019, TestSize.Level1)
{
    Create([](IndexerModelNG model) {
        model.SetAutoCollapse(true);
        model.SetItemSize(Dimension(10, DimensionUnit::PX));
    }, CREATE_ARRAY_1, 0);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = 24.f;
    indexerLayoutAlgorithm->actualHeight_ = 150.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);

    EXPECT_EQ(pattern_->autoCollapse_, true);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY_1.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), CREATE_ARRAY_1.size());
    for (auto value : pattern_->arrayValue_) {
        EXPECT_EQ(value.second, false);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);
}

/**
 * @tc.name: OnModifyDone0020
 * @tc.desc: Test OnModifyDone when autocollapse is open, and arrayValue size is more than 9,
 *           pattern height is enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0020, TestSize.Level1)
{
    Create([](IndexerModelNG model) {
        model.SetAutoCollapse(true);
        model.SetItemSize(Dimension(10, DimensionUnit::VP));
    }, CREATE_ARRAY_1, 0);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = 24.f;
    indexerLayoutAlgorithm->actualHeight_ = 150.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);

    EXPECT_EQ(pattern_->autoCollapse_, true);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY_1.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), CREATE_ARRAY_1.size());
    for (auto value : pattern_->arrayValue_) {
        EXPECT_EQ(value.second, false);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);
}

/**
 * @tc.name: OnModifyDone0021
 * @tc.desc: Test OnModifyDone when autocollapse is open, and arrayValue size is more than 9,
 *           pattern height is enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0021, TestSize.Level1)
{
    Create([](IndexerModelNG model) {
        model.SetAutoCollapse(true);
        model.SetItemSize(Dimension(10, DimensionUnit::FP));
    }, CREATE_ARRAY_1, 0);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = 24.f;
    indexerLayoutAlgorithm->actualHeight_ = 150.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);

    EXPECT_EQ(pattern_->autoCollapse_, true);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY_1.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), CREATE_ARRAY_1.size());
    for (auto value : pattern_->arrayValue_) {
        EXPECT_EQ(value.second, false);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);
}

/**
 * @tc.name: OnModifyDone0022
 * @tc.desc: Test OnModifyDone when autocollapse is open, and arrayValue size is more than 9,
 *           pattern height is enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0022, TestSize.Level1)
{
    Create([](IndexerModelNG model) {
        model.SetAutoCollapse(true);
        model.SetItemSize(Dimension(10, DimensionUnit::PERCENT));
    }, CREATE_ARRAY_1, 0);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = 24.f;
    indexerLayoutAlgorithm->actualHeight_ = 150.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);

    EXPECT_EQ(pattern_->autoCollapse_, true);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY_1.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), CREATE_ARRAY_1.size());
    for (auto value : pattern_->arrayValue_) {
        EXPECT_EQ(value.second, false);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);
}

/**
 * @tc.name: OnModifyDone0023
 * @tc.desc: Test OnModifyDone when autocollapse is open, and arrayValue size is more than 9,
 *           pattern height is enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0023, TestSize.Level1)
{
    Create([](IndexerModelNG model) {
        model.SetAutoCollapse(true);
        model.SetItemSize(Dimension(10, DimensionUnit::PERCENT));
    }, CREATE_ARRAY_1, 0);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = 24.f;
    indexerLayoutAlgorithm->actualHeight_ = 150.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);

    EXPECT_EQ(pattern_->autoCollapse_, true);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY_1.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), CREATE_ARRAY_1.size());
    for (auto value : pattern_->arrayValue_) {
        EXPECT_EQ(value.second, false);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);
}

/**
 * @tc.name: OnModifyDone0024
 * @tc.desc: Test OnModifyDone when autocollapse is open, and arrayValue size is more than 9,
 *           pattern height is enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0024, TestSize.Level1)
{
    Create([](IndexerModelNG model) {
        model.SetAutoCollapse(true);
        model.SetItemSize(Dimension(10, DimensionUnit::NONE));
    }, CREATE_ARRAY_1, 0);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = 24.f;
    indexerLayoutAlgorithm->actualHeight_ = 150.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);

    EXPECT_EQ(pattern_->autoCollapse_, true);
    EXPECT_EQ(pattern_->fullArrayValue_.size(), CREATE_ARRAY_1.size());
    EXPECT_EQ(pattern_->arrayValue_.size(), CREATE_ARRAY_1.size());
    for (auto value : pattern_->arrayValue_) {
        EXPECT_EQ(value.second, false);
    }
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);
}

/**
 * @tc.name: OnModifyDone0025
 * @tc.desc: Test OnModifyDone when autocollapse is open, and arrayValue size is more than 9,
 *           pattern height is not enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0025, TestSize.Level1)
{
    Create([](IndexerModelNG model) {
        model.SetAutoCollapse(true);
        model.SetItemSize(Dimension(10, DimensionUnit::PX));
    }, CREATE_ARRAY_2, 0);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = 24.f;
    indexerLayoutAlgorithm->actualHeight_ = 100.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);

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

    EXPECT_EQ(pattern_->autoCollapse_, true);
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
 * @tc.desc: Test OnModifyDone when autocollapse is open, and arrayValue size is more than 9,
 *           pattern height is not enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0026, TestSize.Level1)
{
    Create([](IndexerModelNG model) {
        model.SetAutoCollapse(true);
        model.SetItemSize(Dimension(10, DimensionUnit::PX));
    }, CREATE_ARRAY_2, 0);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = 24.f;
    indexerLayoutAlgorithm->actualHeight_ = 100.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);

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

    EXPECT_EQ(pattern_->autoCollapse_, true);
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
 * @tc.desc: Test OnModifyDone when autocollapse is open, and arrayValue size is more than 9,
 *           pattern height is not enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0027, TestSize.Level1)
{
    Create([](IndexerModelNG model) {
        model.SetAutoCollapse(true);
        model.SetItemSize(Dimension(10, DimensionUnit::PERCENT));
    }, CREATE_ARRAY_2, 0);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = 24.f;
    indexerLayoutAlgorithm->actualHeight_ = 100.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);

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

    EXPECT_EQ(pattern_->autoCollapse_, true);
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
 * @tc.desc: Test OnModifyDone when autocollapse is open, and arrayValue size is more than 9,
 *           pattern height is not enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0028, TestSize.Level1)
{
    Create([](IndexerModelNG model) {
        model.SetAutoCollapse(true);
        model.SetItemSize(Dimension(10, DimensionUnit::NONE));
    }, CREATE_ARRAY_2, 0);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = 24.f;
    indexerLayoutAlgorithm->actualHeight_ = 100.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);

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

    EXPECT_EQ(pattern_->autoCollapse_, true);
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
 * @tc.desc: Test OnModifyDone when autocollapse is open, and arrayValue size is more than 9,
 *           pattern height is not enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0029, TestSize.Level1)
{
    Create([](IndexerModelNG model) {
        model.SetAutoCollapse(true);
        model.SetItemSize(Dimension(10, DimensionUnit::LPX));
    }, CREATE_ARRAY_2, 0);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = 24.f;
    indexerLayoutAlgorithm->actualHeight_ = 100.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);

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

    EXPECT_EQ(pattern_->autoCollapse_, true);
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
 * @tc.desc: Test OnModifyDone when autocollapse is open, and arrayValue size is more than 9,
 *           pattern height is not enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerModelTestNg, OnModifyDone0030, TestSize.Level1)
{
    Create([](IndexerModelNG model) {
        model.SetAutoCollapse(true);
        model.SetItemSize(Dimension(10, DimensionUnit::FP));
    }, CREATE_ARRAY_2, 0);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    RefPtr<IndexerLayoutAlgorithm> indexerLayoutAlgorithm = AceType::MakeRefPtr<IndexerLayoutAlgorithm>(0);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(indexerLayoutAlgorithm);
    indexerLayoutAlgorithm->itemSizeRender_ = 24.f;
    indexerLayoutAlgorithm->actualHeight_ = 100.f;
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);

    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = false;
    dirtySwapConfig.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);

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

    EXPECT_EQ(pattern_->autoCollapse_, true);
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
    Create([](IndexerModelNG model) {
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
    }, CREATE_ARRAY, 0);

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
    EXPECT_EQ(layoutProperty_->GetUsingPopupValue(), true);
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
    Create([](IndexerModelNG model) {
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
    }, CREATE_ARRAY, 0);

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
    EXPECT_EQ(layoutProperty_->GetUsingPopupValue(), true);
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
    Create([](IndexerModelNG model) {
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
    }, CREATE_ARRAY, 0);

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
    EXPECT_EQ(layoutProperty_->GetUsingPopupValue(), true);
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
    Create([](IndexerModelNG model) {
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
    }, CREATE_ARRAY, 0);

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
    EXPECT_EQ(layoutProperty_->GetUsingPopupValue(), true);
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
    Create([](IndexerModelNG model) {
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
    }, CREATE_ARRAY, 0);

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
    EXPECT_EQ(layoutProperty_->GetUsingPopupValue(), true);
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
    Create([](IndexerModelNG model) {
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
    }, CREATE_ARRAY, 0);

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
    EXPECT_EQ(layoutProperty_->GetUsingPopupValue(), true);
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
    Create([](IndexerModelNG model) {
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
    }, CREATE_ARRAY, 0);

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
    EXPECT_EQ(layoutProperty_->GetUsingPopupValue(), true);
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
    Create([](IndexerModelNG model) {
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
    }, CREATE_ARRAY, 0);

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
    EXPECT_EQ(layoutProperty_->GetUsingPopupValue(), true);
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
    Create([](IndexerModelNG model) {
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
    }, CREATE_ARRAY, 0);

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
    EXPECT_EQ(layoutProperty_->GetUsingPopupValue(), true);
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
    Create([](IndexerModelNG model) {
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
    }, CREATE_ARRAY, 0);

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
    EXPECT_EQ(layoutProperty_->GetUsingPopupValue(), true);
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
    Create([](IndexerModelNG model) {
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
    }, CREATE_ARRAY, 0);

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
    EXPECT_EQ(layoutProperty_->GetUsingPopupValue(), true);
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
    Create([](IndexerModelNG model) {
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
    }, CREATE_ARRAY, 0);

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
    EXPECT_EQ(layoutProperty_->GetUsingPopupValue(), true);
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
    Create([](IndexerModelNG model) {
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
    }, CREATE_ARRAY, 0);

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
    EXPECT_EQ(layoutProperty_->GetUsingPopupValue(), true);
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
    Create([](IndexerModelNG model) {
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
    }, CREATE_ARRAY, 0);

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
    EXPECT_EQ(layoutProperty_->GetUsingPopupValue(), true);
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
    Create([](IndexerModelNG model) {
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
    }, CREATE_ARRAY, 0);

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
    EXPECT_EQ(layoutProperty_->GetUsingPopupValue(), true);
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
    Create([](IndexerModelNG model) {
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
    }, CREATE_ARRAY, 0);

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
    EXPECT_EQ(layoutProperty_->GetUsingPopupValue(), true);
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
