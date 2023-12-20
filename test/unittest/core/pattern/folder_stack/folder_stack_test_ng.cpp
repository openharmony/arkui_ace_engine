/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "folder_stack_test_ng.h"

#define private public
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"


#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr float ZERO = 0.0f;
const OffsetF ORIGIN_POINT(ZERO, ZERO);
constexpr float STACK_HEIGHT = 120.0f;
constexpr float FULL_SCREEN_WIDTH = 2224.0f;
constexpr float FULL_SCREEN_HEIGHT = 2496.0f;
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);

constexpr float SMALL_ITEM_WIDTH = 100.0f;
constexpr float SMALL_ITEM_HEIGHT = 40.0f;
const SizeF SMALL_ITEM_SIZE(SMALL_ITEM_WIDTH, SMALL_ITEM_HEIGHT);

constexpr float FOLDER_STACK_WIDTH = 400.f;
constexpr float FOLDER_STACK_HEIGHT = 800.f;
const std::vector<std::string> itemId { "A", "B", "C" };
const std::vector<std::string> label {"text1", "text2", "text3", "text4", "text5"};
const std::vector<std::string> nullInspectorIds {"", "", "", "", ""};
const std::vector<std::string> inspectorIds {"A", "B", "B", "C", "D"};
} // namespace

PaddingProperty FolderStackTestNG::CreatePadding(float left, float top, float right, float bottom)
{
    PaddingProperty padding;
    padding.left = CalcLength(left);
    padding.right = CalcLength(right);
    padding.top = CalcLength(top);
    padding.bottom = CalcLength(bottom);
    return padding;
}

RefPtr<UINode> FolderStackTestNG::CreateWithItem(bool enableAnimation, bool autoHalfFold, Alignment align)
{
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(align);
    folderStackModelNG.SetEnableAnimation(enableAnimation);
    folderStackModelNG.SetAutoHalfFold(autoHalfFold);
    {
        BlankModelNG blankModelNG;
        blankModelNG.Create();
        ViewAbstract::SetWidth(CalcLength(SMALL_ITEM_WIDTH));
        ViewAbstract::SetHeight(CalcLength(SMALL_ITEM_HEIGHT));
        PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
        ViewAbstract::SetPadding(noPadding);
        ViewStackProcessor::GetInstance()->Pop();
    }
    auto frameNode = ViewStackProcessor::GetInstance()->Finish();
    return frameNode;
}

void FolderStackTestNG::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textTheme = AceType::MakeRefPtr<TextTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textTheme));
    EXPECT_CALL(*(MockContainer::Current()), GetFrontend()).WillRepeatedly(Return(nullptr));
}

void FolderStackTestNG::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
    MockPipelineContext::TearDown();
}

void FolderStackTestNG::Create(const std::vector<std::string>& itemId,
    const std::function<void(FolderStackModelNG model)>& callback)
{
    FolderStackModelNG model;
    model.Create(itemId);
    ViewAbstract::SetWidth(CalcLength(FOLDER_STACK_WIDTH));
    ViewAbstract::SetHeight(CalcLength(FOLDER_STACK_HEIGHT));
    if (callback) {
        callback(model);
    }
    GetInstance();
    FlushLayoutTask(frameNode_);
}

void FolderStackTestNG::AddChildNodeToGroup(const std::vector<std::string>& label,
    const std::vector<std::string>& inspectorIds)
{
    ASSERT_EQ(label.size(), inspectorIds.size());
    ASSERT_NE(frameNode_, nullptr);
    for (uint32_t index = 0; index < label.size(); ++index) {
        TextModelNG textModel;
        textModel.Create(label[index]);
        RefPtr<UINode> node = ViewStackProcessor::GetInstance()->Finish();
        node->UpdateInspectorId(inspectorIds[index]);
        frameNode_->AddChildToGroup(node);
    }
    FlushLayoutTask(frameNode_);
}

void FolderStackTestNG::SetUp()
{
    mockFolderStackLayoutAlgorithm_ = AceType::MakeRefPtr<MockFolderStackLayoutAlgorithm>();
}

void FolderStackTestNG::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    controlPartsStackNode_ = nullptr;
    hoverNode_ = nullptr;
}

void FolderStackTestNG::GetInstance()
{
    RefPtr<UINode> node = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FolderStackGroupNode>(node);
    frameNode_->layoutAlgorithm_ = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(mockFolderStackLayoutAlgorithm_);
    pattern_ = frameNode_->GetPattern<FolderStackPattern>();
    eventHub_ = frameNode_->GetEventHub<FolderStackEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<FolderStackLayoutProperty>();
    controlPartsStackNode_ =
        AceType::DynamicCast<ControlPartsStackNode>(frameNode_->GetControlPartsStackNode());
    hoverNode_ = AceType::DynamicCast<HoverStackNode>(frameNode_->GetHoverNode());
}


/**
 * @tc.name: FolderStackTestNgTest001
 * @tc.desc: Test folderStack Layout with Alignment
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNG, FolderStackTestNgTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create folderStack and get frameNode.
     */
    Alignment align = Alignment::TOP_LEFT;
    bool enableAnimation = false;
    bool autoHalfFold = false;
    auto frameNode = AceType::DynamicCast<FrameNode>(CreateWithItem(enableAnimation, autoHalfFold, align));
    auto layoutProperty = frameNode->GetLayoutProperty<FolderStackLayoutProperty>();
    auto alignment = layoutProperty->GetPositionProperty()->GetAlignment();
    ASSERT_EQ(alignment, Alignment::TOP_LEFT);
    ASSERT_EQ(layoutProperty->GetEnableAnimation(), false);
    ASSERT_EQ(layoutProperty->GetAutoHalfFold(), false);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: related function is called.
     */
    RefPtr<GeometryNode> geometryNode = frameNode->GetGeometryNode();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto folderStackPattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(folderStackPattern, nullptr);
    auto layoutAlgorithm =
        AceType::DynamicCast<FolderStackLayoutAlgorithm>(folderStackPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(STACK_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);

    /**
     * @tc.steps: step4. use layoutAlgorithm to layout.
     * @tc.expected: check whether the value of geometry frameSize and frameOffset is correct.
     */
    layoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    layoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutWrapper->GetGeometryNode()->GetMarginFrameSize(), SizeF(FULL_SCREEN_WIDTH, STACK_HEIGHT));
    ASSERT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(ZERO, ZERO));
}

/**
 * @tc.name: FolderStackTestNgTest002
 * @tc.desc: Test folderStack Layout with AlignmentContent
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNG, FolderStackTestNgTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create folderStack and get frameNode.
     */
    FolderStackModelNG folderStackModelNG;
    folderStackModelNG.Create();
    folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<FolderStackLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    ASSERT_NE(layoutProperty->GetPositionProperty(), nullptr);
    auto alignmentContent = layoutProperty->GetPositionProperty()->GetAlignment();
    ASSERT_EQ(alignmentContent, Alignment::TOP_LEFT);
    layoutProperty->UpdateLayoutDirection(TextDirection::LTR);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: related function is called.
     */

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto folderStackPattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(folderStackPattern, nullptr);
    auto layoutAlgorithm = folderStackPattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(STACK_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step4. use layoutAlgorithm to layout.
     * @tc.expected: check whether the value of geometry frameSize and frameOffset is correct.
     */
    layoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    layoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    ASSERT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(FULL_SCREEN_WIDTH, STACK_HEIGHT));
    ASSERT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), OffsetF(ZERO, ZERO));
}

/**
 * @tc.name: FolderStackToJsonValue001
 * @tc.desc: Test FolderStackTestNG properties & ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNG, FolderStackToJsonValue001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init FolderStack node with Aniamtion/AutoHalfFold props false, itemId not null.
     */
    Create(itemId, [](FolderStackModelNG model) {
        model.SetEnableAnimation(false);
        model.SetAutoHalfFold(true);
        model.SetAlignment(Alignment::BOTTOM_LEFT);
    });

    /**
     * @tc.steps: step2. Expect ToJsonValue as properties set in step1.
     */
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    std::string str;
    str.assign("[");
    for (auto& id : itemId) {
        str.append(id);
        str.append(", ");
    }
    str = (itemId.size() > 1) ? str.substr(0, str.size() - 1).append("]") : str.append("]");
    EXPECT_EQ(json->GetString("alignContent"), "Alignment.BottomStart");
    EXPECT_EQ(json->GetString("upperItems"), str);
    EXPECT_EQ(json->GetString("enableAnimation"), "false");
    EXPECT_EQ(json->GetString("autoHalfFold"), "true");
}

/**
 * @tc.name: FolderStackToJsonValue002
 * @tc.desc: Test FolderStackTestNG properties & ToJsonValue with default value.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNG, FolderStackToJsonValue002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init FolderStack node with Aniamtion/AutoHalfFold props false, itemId not null.
     */
    Create(std::vector<std::string>(), [](FolderStackModelNG model) {
        model.SetEnableAnimation(false);
    });

    /**
     * @tc.steps: step2. Expect ToJsonValue as properties set in step1.
     */
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_EQ(json->GetString("alignContent"), "Alignment.Center");
    EXPECT_EQ(json->GetString("upperItems"), "[]");
    EXPECT_EQ(json->GetString("enableAnimation"), "false");
}

/**
 * @tc.name: FolderStackGroupNode001
 * @tc.desc: Test FolderStackTestNG properties & ToJsonValue with special value.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNG, FolderStackGroupNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init FolderStack group node, add child node to group.
     */
    Create(std::vector<std::string>(), [](FolderStackModelNG model) {
        model.SetEnableAnimation(false);
    });
    AddChildNodeToGroup(label, nullInspectorIds);

    /**
     * @tc.steps: step2. Init FolderStack group node, add child node to group.
     */
    EXPECT_EQ(controlPartsStackNode_->TotalChildCount(), inspectorIds.size());
    EXPECT_EQ(hoverNode_->TotalChildCount(), 0);
}

/**
 * @tc.name: FolderStackGroupNode002
 * @tc.desc: Test FolderStackTestNG properties & ToJsonValue with special value.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNG, FolderStackGroupNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init FolderStack group node, add child node to group.
     */
    Create(itemId, [](FolderStackModelNG model) {
        model.SetEnableAnimation(false);
    });
    AddChildNodeToGroup(label, inspectorIds);

    /**
     * @tc.steps: step2. Init FolderStack group node, add child node to group.
     */
    EXPECT_EQ(controlPartsStackNode_->TotalChildCount(), 1);
    EXPECT_EQ(hoverNode_->TotalChildCount(), inspectorIds.size() - 1);
}

/**
 * @tc.name: FolderStackEventHub001
 * @tc.desc: Test FolderStackEventHub, expect FolderStackEventHub OnFolderStateChange trigged
 *     when OnFoldStatusChange.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNG, FolderStackEventHub001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init FolderStack, set OnFolderStateChanged callback.
     */
    bool foldStatusStateChanged = false;
    auto onFolderStateChange = [&foldStatusStateChanged](const NG::FolderEventInfo& folderEventInfo) {
        foldStatusStateChanged = true;
    };
    Create(itemId, [&onFolderStateChange](FolderStackModelNG model) {
        model.SetEnableAnimation(false);
        model.SetOnFolderStateChange(std::move(onFolderStateChange));
    });

    /**
     * @tc.steps: step2. Init FolderStack group node, add child node to group.
     */
    eventHub_->OnFolderStateChange(FoldStatus::HALF_FOLD);
    EXPECT_EQ(foldStatusStateChanged, true);
}

/**
 * @tc.name: FolderStackLayoutAlgorithm001
 * @tc.desc: Test FolderStackLayoutAlgorithm measure when isIntoFolderStack_ is false.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNG, FolderStackLayoutAlgorithm001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init FolderStack with null group child item.
     */
    Create(itemId, [](FolderStackModelNG model) {
        model.SetEnableAnimation(false);
    });
    AddChildNodeToGroup(label, inspectorIds);
    /**
     * @tc.steps: step2. test FolderStack GeometryNode frame size after measure.
     */
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize(), SizeF(FOLDER_STACK_WIDTH, FOLDER_STACK_HEIGHT));
    EXPECT_EQ(controlPartsStackNode_->TotalChildCount(), 1);
    EXPECT_EQ(hoverNode_->TotalChildCount(), 4);
}

/**
 * @tc.name: FolderStackLayoutAlgorithm002
 * @tc.desc: Test FolderStackLayoutAlgorithm measure when displayInfo is fullWindow & FoldStatus::HALF_FOLD
 *      & isFoldable & Rotation is ROTATION_90 or Rotation::ROTATION_270 .
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNG, FolderStackLayoutAlgorithm002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init FolderStack with group child item.
     */
    EXPECT_CALL(*mockFolderStackLayoutAlgorithm_, IsFullWindow(_, _)).WillRepeatedly(Return(true));
    auto displayInfo = AceType::MakeRefPtr<DisplayInfo>();
    displayInfo->SetIsFoldable(true);
    displayInfo->SetFoldStatus(FoldStatus::HALF_FOLD);
    displayInfo->SetRotation(Rotation::ROTATION_90);
    EXPECT_CALL(*(MockContainer::Current()), GetDisplayInfo()).WillRepeatedly(Return(displayInfo));
    Create(itemId, [](FolderStackModelNG model) {
        model.SetEnableAnimation(false);
    });
    AddChildNodeToGroup(label, inspectorIds);

    /**
     * @tc.steps: step2. test FolderStack GeometryNode frame size after measure.
     */
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize(), SizeF(FOLDER_STACK_WIDTH, FOLDER_STACK_HEIGHT));
    EXPECT_EQ(controlPartsStackNode_->TotalChildCount(), 1);
    EXPECT_EQ(hoverNode_->TotalChildCount(), 4);
}

/**
 * @tc.name: FolderStackLayoutAlgorithm003
 * @tc.desc: Test FolderStackLayoutAlgorithm layout.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackTestNG, FolderStackLayoutAlgorithm003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init FolderStack with group child item.
     */
    Create(itemId, [](FolderStackModelNG model) {
        model.SetEnableAnimation(false);
        model.SetAlignment(Alignment::BOTTOM_RIGHT);
    });
    AddChildNodeToGroup(label, inspectorIds);
    /**
     * @tc.steps: step2. test ControlPartsStackNode & HoverStackNode alignment property inherited from parent.
     */
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameSize(), SizeF(FOLDER_STACK_WIDTH, FOLDER_STACK_HEIGHT));
    auto controlPartsLayoutProperty =
        AceType::DynamicCast<LayoutProperty>(controlPartsStackNode_->GetLayoutProperty());
    EXPECT_EQ(controlPartsLayoutProperty->GetPositionProperty()->GetAlignment(), Alignment::BOTTOM_RIGHT);
    auto hoverNodeLayoutProperty = AceType::DynamicCast<LayoutProperty>(hoverNode_->GetLayoutProperty());
    EXPECT_EQ(hoverNodeLayoutProperty->GetPositionProperty()->GetAlignment(), Alignment::BOTTOM_RIGHT);
}
} // namespace OHOS::Ace::NG
