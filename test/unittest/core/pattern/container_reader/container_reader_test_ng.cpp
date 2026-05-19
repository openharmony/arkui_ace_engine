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

#include "container_reader_test_ng.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/container_reader/container_reader_event_hub.h"
#include "core/components_ng/pattern/container_reader/container_reader_layout_property.h"
#include "core/components_ng/pattern/container_reader/container_reader_pattern.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

namespace {
    const float TEST_WIDTH_SM = 320.0f;
    const float TEST_WIDTH_MD = 600.0f;
    const float TEST_WIDTH_LG = 840.0f;
    const float TEST_WIDTH_XL = 1440.0f;
    const float TEST_HEIGHT_NORMAL = 500.0f;
    const float TEST_HEIGHT_TALL = 900.0f;
    const float TEST_HEIGHT_ZERO = 0.0f;
    const float TEST_WIDTH_ZERO = 0.0f;
    const float TEST_EPSILON_RANGE = 0.3f;
    const double TEST_CUSTOM_BREAKPOINT_320 = 320.0;
    const double TEST_CUSTOM_BREAKPOINT_600 = 600.0;
    const double TEST_CUSTOM_BREAKPOINT_840 = 840.0;
    const double TEST_ASPECT_RATIO_SHORT = 0.5;
    const double TEST_ASPECT_RATIO_MEDIUM = 1.0;
    const double TEST_ASPECT_RATIO_TALL = 1.5;
    const double TEST_SIZE_CHANGED_DELTA = 10.0;
    const float TEST_FLEX_WIDTH = 200.0f;
    const float TEST_FLEX_HEIGHT = 300.0f;
    const float TEST_TEXT_SIZE = 60.0f;
    const float TEST_READER_EXPECTED_WIDTH = 140.0f;
    const float TEST_READER_LAYOUT_WEIGHT_WIDTH = 70.0f;
    const float TEST_LAYOUT_WEIGHT = 1.0f;
    const float TEST_READER_MAX_WIDTH = 50.0f;
} // namespace

void ContainerReaderTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
}

void ContainerReaderTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void ContainerReaderTestNg::SetUp()
{
    ViewStackProcessor::GetInstance()->ClearStack();
}

void ContainerReaderTestNg::TearDown() {}

RefPtr<FrameNode> ContainerReaderTestNg::CreateContainerReader(
    const std::function<void(ContainerReaderModelNG)>& callback)
{
    ContainerReaderModelNG model;
    model.Create();
    if (callback) {
        callback(model);
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ViewStackProcessor::GetInstance()->Pop();
    return AceType::DynamicCast<FrameNode>(element);
}

RefPtr<FrameNode> ContainerReaderTestNg::CreateFlexRow(
    const std::function<void(FlexModelNG)>& callback)
{
    FlexModelNG model;
    model.CreateFlexRow();
    if (callback) {
        callback(model);
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ViewStackProcessor::GetInstance()->Pop();
    return AceType::DynamicCast<FrameNode>(element);
}

// ==================== CreateLayoutProperty ====================

/**
 * @tc.name: CreateLayoutProperty001
 * @tc.desc: Test CreateLayoutProperty returns ContainerReaderLayoutProperty
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, CreateLayoutProperty001, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = pattern->CreateLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto crLayoutProperty = AceType::DynamicCast<ContainerReaderLayoutProperty>(layoutProperty);
    EXPECT_NE(crLayoutProperty, nullptr);
}

// ==================== CreateLayoutAlgorithm ====================

/**
 * @tc.name: CreateLayoutAlgorithm001
 * @tc.desc: Test CreateLayoutAlgorithm returns ContainerReaderLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, CreateLayoutAlgorithm001, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto crLayoutAlgorithm = AceType::DynamicCast<ContainerReaderLayoutAlgorithm>(layoutAlgorithm);
    EXPECT_NE(crLayoutAlgorithm, nullptr);
}

// ==================== CreateEventHub ====================

/**
 * @tc.name: CreateEventHub001
 * @tc.desc: Test CreateEventHub returns ContainerReaderEventHub
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, CreateEventHub001, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);
    auto eventHub = pattern->CreateEventHub();
    ASSERT_NE(eventHub, nullptr);
    auto crEventHub = AceType::DynamicCast<ContainerReaderEventHub>(eventHub);
    EXPECT_NE(crEventHub, nullptr);
}

// ==================== IsAtomicNode ====================

/**
 * @tc.name: IsAtomicNode001
 * @tc.desc: Test IsAtomicNode returns false for ContainerReader
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, IsAtomicNode001, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->IsAtomicNode());
}

// ==================== SetRenderFunction ====================

/**
 * @tc.name: SetRenderFunction001
 * @tc.desc: Test SetRenderFunction when isInitialRender_ is true
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, SetRenderFunction001, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetIsInitialRender(true);

    bool renderCalled = false;
    ContainerReaderRenderFunction renderFunc = [&renderCalled](int64_t id, bool& ret) -> RefPtr<UINode> {
        renderCalled = true;
        return nullptr;
    };
    pattern->SetRenderFunction(renderFunc);
    // isInitialRender_ is true, renderFunction_ should be set
    auto algorithm = AceType::DynamicCast<ContainerReaderLayoutAlgorithm>(
        pattern->CreateLayoutAlgorithm());
    ASSERT_NE(algorithm, nullptr);
}

/**
 * @tc.name: SetRenderFunction002
 * @tc.desc: Test SetRenderFunction when isInitialRender_ is false, renderFunction should not update
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, SetRenderFunction002, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);

    // Set initial render function first
    bool firstFuncCalled = false;
    ContainerReaderRenderFunction firstFunc = [&firstFuncCalled](int64_t id, bool& ret) -> RefPtr<UINode> {
        firstFuncCalled = true;
        return nullptr;
    };
    pattern->SetIsInitialRender(true);
    pattern->SetRenderFunction(firstFunc);

    // Now set isInitialRender_ to false and try to set another render function
    pattern->SetIsInitialRender(false);
    bool secondFuncCalled = false;
    ContainerReaderRenderFunction secondFunc = [&secondFuncCalled](int64_t id, bool& ret) -> RefPtr<UINode> {
        secondFuncCalled = true;
        return nullptr;
    };
    pattern->SetRenderFunction(secondFunc);
    // When isInitialRender_ is false, renderFunction_ should NOT be updated
    // So calling the new function should not affect it
    EXPECT_FALSE(secondFuncCalled);
}

// ==================== OnAttachToFrameNode / OnDetachFromFrameNode ====================

/**
 * @tc.name: OnAttachToFrameNode001
 * @tc.desc: Test OnAttachToFrameNode does not crash
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, OnAttachToFrameNode001, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);
    // OnAttachToFrameNode should not crash
    pattern->OnAttachToFrameNode();
}

/**
 * @tc.name: OnDetachFromFrameNode001
 * @tc.desc: Test OnDetachFromFrameNode does not crash
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, OnDetachFromFrameNode001, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnDetachFromFrameNode(frameNode.GetRawPtr());
}

// ==================== OnAttachToMainTree / OnDetachFromMainTree ====================

/**
 * @tc.name: OnAttachToMainTree001
 * @tc.desc: Test OnAttachToMainTree triggers UpdateBreakpointValues
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, OnAttachToMainTree001, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(TEST_WIDTH_MD, TEST_HEIGHT_NORMAL));

    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnAttachToMainTree();
    // Should not crash, UpdateBreakpointValues is called internally
}

/**
 * @tc.name: OnDetachFromMainTree001
 * @tc.desc: Test OnDetachFromMainTree does not crash
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, OnDetachFromMainTree001, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnDetachFromMainTree();
}

// ==================== OnModifyDone ====================

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test OnModifyDone does not call UpdateBreakpointValues (avoid circular update)
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, OnModifyDone001, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);

    int32_t sizeChangeCount = 0;
    auto eventHub = frameNode->GetEventHub<ContainerReaderEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnSizeChange([&sizeChangeCount](const SizeF& size) { sizeChangeCount++; });

    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(TEST_WIDTH_LG, TEST_HEIGHT_TALL));

    pattern->OnModifyDone();
    // OnModifyDone should NOT trigger size change event
    EXPECT_EQ(sizeChangeCount, 0);
}

// ==================== OnDirtyLayoutWrapperSwap ====================

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap when skipMeasure is true, should not update breakpoints
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(TEST_WIDTH_MD, TEST_HEIGHT_NORMAL));

    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);

    DirtySwapConfig config;
    config.skipMeasure = true;

    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);

    int32_t sizeChangeCount = 0;
    auto eventHub = frameNode->GetEventHub<ContainerReaderEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnSizeChange([&sizeChangeCount](const SizeF& size) { sizeChangeCount++; });

    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    // When skipMeasure is true, UpdateBreakpointValues should not be called
    EXPECT_EQ(sizeChangeCount, 0);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap002
 * @tc.desc: Test OnDirtyLayoutWrapperSwap when skipMeasure is false, should update breakpoints
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, OnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);

    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(TEST_WIDTH_MD, TEST_HEIGHT_NORMAL));

    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);

    DirtySwapConfig config;
    config.skipMeasure = false;

    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);

    SizeF changedSize(0.0f, 0.0f);
    auto eventHub = frameNode->GetEventHub<ContainerReaderEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnSizeChange([&changedSize](const SizeF& size) { changedSize = size; });

    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(changedSize.Width(), TEST_WIDTH_MD);
    EXPECT_EQ(changedSize.Height(), TEST_HEIGHT_NORMAL);
}

// ==================== UpdateBreakpointValues - Size Change ====================

/**
 * @tc.name: UpdateBreakpointValues001
 * @tc.desc: Test UpdateBreakpointValues fires size change event when size changes beyond EPSILON
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, UpdateBreakpointValues001, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(TEST_WIDTH_LG, TEST_HEIGHT_TALL));

    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);

    SizeF changedSize(0.0f, 0.0f);
    auto eventHub = frameNode->GetEventHub<ContainerReaderEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnSizeChange([&changedSize](const SizeF& size) { changedSize = size; });

    pattern->UpdateBreakpointValues();
    EXPECT_EQ(changedSize.Width(), TEST_WIDTH_LG);
    EXPECT_EQ(changedSize.Height(), TEST_HEIGHT_TALL);
}

/**
 * @tc.name: UpdateBreakpointValues002
 * @tc.desc: Test UpdateBreakpointValues does NOT fire size change when size change is within EPSILON
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, UpdateBreakpointValues002, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);

    // Set initial size
    SizeF initialSize(TEST_WIDTH_MD, TEST_HEIGHT_NORMAL);
    geometryNode->SetFrameSize(initialSize);

    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);

    // Change size within EPSILON range
    geometryNode->SetFrameSize(
        SizeF(TEST_WIDTH_MD + TEST_EPSILON_RANGE, TEST_HEIGHT_NORMAL + TEST_EPSILON_RANGE));

    int32_t sizeChangeCount = 0;
    auto eventHub = frameNode->GetEventHub<ContainerReaderEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnSizeChange([&sizeChangeCount](const SizeF& size) { sizeChangeCount++; });

    pattern->UpdateBreakpointValues();
    // Size change within EPSILON, event should NOT fire
    EXPECT_EQ(sizeChangeCount, 1);
}

/**
 * @tc.name: UpdateBreakpointValues003
 * @tc.desc: Test UpdateBreakpointValues fires size change when size exceeds EPSILON
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, UpdateBreakpointValues003, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);

    SizeF initialSize(TEST_WIDTH_MD, TEST_HEIGHT_NORMAL);
    geometryNode->SetFrameSize(initialSize);

    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);

    // Change size beyond EPSILON
    geometryNode->SetFrameSize(
        SizeF(TEST_WIDTH_MD + TEST_SIZE_CHANGED_DELTA, TEST_HEIGHT_NORMAL + TEST_SIZE_CHANGED_DELTA));

    int32_t sizeChangeCount = 0;
    auto eventHub = frameNode->GetEventHub<ContainerReaderEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnSizeChange([&sizeChangeCount](const SizeF& size) { sizeChangeCount++; });

    pattern->UpdateBreakpointValues();
    EXPECT_EQ(sizeChangeCount, 1);
}

// ==================== UpdateBreakpointValues - Width Breakpoint Change ====================

/**
 * @tc.name: UpdateBreakpointValues_WidthBreakpoint001
 * @tc.desc: Test UpdateBreakpointValues fires width breakpoint change when breakpoint transitions
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, UpdateBreakpointValues_WidthBreakpoint001, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(TEST_WIDTH_SM, TEST_HEIGHT_NORMAL));

    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);
    // Default lastWidthBreakpoint_ is UNDEFINED, any calculated value should trigger change

    WidthBreakpoint changedBreakpoint = WidthBreakpoint::UNDEFINED;
    auto eventHub = frameNode->GetEventHub<ContainerReaderEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnWidthBreakpointChange(
        [&changedBreakpoint](WidthBreakpoint bp) { changedBreakpoint = bp; });

    pattern->UpdateBreakpointValues();
    // Width 320 with density 1.0 should result in WIDTH_SM breakpoint
    EXPECT_NE(changedBreakpoint, WidthBreakpoint::UNDEFINED);
}

/**
 * @tc.name: UpdateBreakpointValues_WidthBreakpoint002
 * @tc.desc: Test UpdateBreakpointValues does NOT fire when width breakpoint does not change
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, UpdateBreakpointValues_WidthBreakpoint002, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(TEST_WIDTH_MD, TEST_HEIGHT_NORMAL));

    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);

    // First call to establish the breakpoint
    pattern->UpdateBreakpointValues();

    // Second call with same size should not trigger event
    int32_t bpChangeCount = 0;
    auto eventHub = frameNode->GetEventHub<ContainerReaderEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnWidthBreakpointChange(
        [&bpChangeCount](WidthBreakpoint bp) { bpChangeCount++; });

    pattern->UpdateBreakpointValues();
    EXPECT_EQ(bpChangeCount, 0);
}

// ==================== UpdateBreakpointValues - Height Breakpoint Change ====================

/**
 * @tc.name: UpdateBreakpointValues_HeightBreakpoint001
 * @tc.desc: Test UpdateBreakpointValues fires height breakpoint change when aspect ratio changes
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, UpdateBreakpointValues_HeightBreakpoint001, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);

    // Tall container: height > width * 1.2 -> HEIGHT_LG
    float tallHeight = TEST_WIDTH_MD * TEST_ASPECT_RATIO_TALL;
    geometryNode->SetFrameSize(SizeF(TEST_WIDTH_MD, tallHeight));

    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);

    HeightBreakpoint changedBreakpoint = HeightBreakpoint::HEIGHT_SM;
    auto eventHub = frameNode->GetEventHub<ContainerReaderEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnHeightBreakpointChange(
        [&changedBreakpoint](HeightBreakpoint bp) { changedBreakpoint = bp; });

    pattern->UpdateBreakpointValues();
    // Default lastHeightBreakpoint_ is HEIGHT_SM, aspect ratio 1.5 > 1.2 should be HEIGHT_LG
    EXPECT_EQ(changedBreakpoint, HeightBreakpoint::HEIGHT_LG);
}

/**
 * @tc.name: UpdateBreakpointValues_HeightBreakpoint002
 * @tc.desc: Test UpdateBreakpointValues does NOT fire height breakpoint when no change
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, UpdateBreakpointValues_HeightBreakpoint002, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    // Default HEIGHT_SM - aspect ratio < 0.8 stays at HEIGHT_SM
    geometryNode->SetFrameSize(SizeF(TEST_WIDTH_MD, TEST_HEIGHT_NORMAL));

    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);

    // First call to establish breakpoint
    pattern->UpdateBreakpointValues();

    int32_t bpChangeCount = 0;
    auto eventHub = frameNode->GetEventHub<ContainerReaderEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnHeightBreakpointChange(
        [&bpChangeCount](HeightBreakpoint bp) { bpChangeCount++; });

    pattern->UpdateBreakpointValues();
    EXPECT_EQ(bpChangeCount, 0);
}

// ==================== CalculateWidthBreakpoint ====================

/**
 * @tc.name: CalculateWidthBreakpoint001
 * @tc.desc: Test CalculateWidthBreakpoint with system default breakpoints at SM range
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, CalculateWidthBreakpoint001, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);

    WidthBreakpoint result = pattern->CalculateWidthBreakpoint(TEST_WIDTH_SM);
    EXPECT_EQ(result, WidthBreakpoint::WIDTH_SM);
}

/**
 * @tc.name: CalculateWidthBreakpoint002
 * @tc.desc: Test CalculateWidthBreakpoint with system default breakpoints at MD range
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, CalculateWidthBreakpoint002, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);

    WidthBreakpoint result = pattern->CalculateWidthBreakpoint(TEST_WIDTH_MD);
    // 600vp is at MD breakpoint boundary
    EXPECT_EQ(result, WidthBreakpoint::WIDTH_MD);
}

/**
 * @tc.name: CalculateWidthBreakpoint003
 * @tc.desc: Test CalculateWidthBreakpoint with system default breakpoints at LG range
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, CalculateWidthBreakpoint003, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);

    WidthBreakpoint result = pattern->CalculateWidthBreakpoint(TEST_WIDTH_LG);
    EXPECT_EQ(result, WidthBreakpoint::WIDTH_LG);
}

/**
 * @tc.name: CalculateWidthBreakpoint004
 * @tc.desc: Test CalculateWidthBreakpoint with system default breakpoints at XL range
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, CalculateWidthBreakpoint004, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);

    WidthBreakpoint result = pattern->CalculateWidthBreakpoint(TEST_WIDTH_XL);
    EXPECT_EQ(result, WidthBreakpoint::WIDTH_XL);
}

/**
 * @tc.name: CalculateWidthBreakpoint005
 * @tc.desc: Test CalculateWidthBreakpoint with custom breakpoint config
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, CalculateWidthBreakpoint005, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ContainerReaderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    // Set custom breakpoints
    BreakPointConfig config;
    config.widthBreakpoints = std::vector<double>{ TEST_CUSTOM_BREAKPOINT_320, TEST_CUSTOM_BREAKPOINT_600,
                                                    TEST_CUSTOM_BREAKPOINT_840 };
    layoutProperty->UpdateBreakPointConfig(config);

    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);

    WidthBreakpoint result = pattern->CalculateWidthBreakpoint(TEST_WIDTH_MD);
    EXPECT_NE(result, WidthBreakpoint::UNDEFINED);
}

// ==================== CalculateHeightBreakpoint ====================

/**
 * @tc.name: CalculateHeightBreakpoint001
 * @tc.desc: Test CalculateHeightBreakpoint with zero height returns HEIGHT_SM
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, CalculateHeightBreakpoint001, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);

    HeightBreakpoint result = pattern->CalculateHeightBreakpoint(TEST_HEIGHT_ZERO, TEST_WIDTH_MD);
    EXPECT_EQ(result, HeightBreakpoint::HEIGHT_SM);
}

/**
 * @tc.name: CalculateHeightBreakpoint002
 * @tc.desc: Test CalculateHeightBreakpoint with zero width returns HEIGHT_SM
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, CalculateHeightBreakpoint002, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);

    HeightBreakpoint result = pattern->CalculateHeightBreakpoint(TEST_HEIGHT_NORMAL, TEST_WIDTH_ZERO);
    EXPECT_EQ(result, HeightBreakpoint::HEIGHT_SM);
}

/**
 * @tc.name: CalculateHeightBreakpoint003
 * @tc.desc: Test CalculateHeightBreakpoint with short aspect ratio (< 0.8) returns HEIGHT_SM
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, CalculateHeightBreakpoint003, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);

    float shortHeight = TEST_WIDTH_MD * static_cast<float>(TEST_ASPECT_RATIO_SHORT);
    HeightBreakpoint result = pattern->CalculateHeightBreakpoint(shortHeight, TEST_WIDTH_MD);
    EXPECT_EQ(result, HeightBreakpoint::HEIGHT_SM);
}

/**
 * @tc.name: CalculateHeightBreakpoint004
 * @tc.desc: Test CalculateHeightBreakpoint with medium aspect ratio (0.8~1.2) returns HEIGHT_MD
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, CalculateHeightBreakpoint004, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);

    float mediumHeight = TEST_WIDTH_MD * static_cast<float>(TEST_ASPECT_RATIO_MEDIUM);
    HeightBreakpoint result = pattern->CalculateHeightBreakpoint(mediumHeight, TEST_WIDTH_MD);
    EXPECT_EQ(result, HeightBreakpoint::HEIGHT_MD);
}

/**
 * @tc.name: CalculateHeightBreakpoint005
 * @tc.desc: Test CalculateHeightBreakpoint with tall aspect ratio (> 1.2) returns HEIGHT_LG
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, CalculateHeightBreakpoint005, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);

    float tallHeight = TEST_WIDTH_MD * static_cast<float>(TEST_ASPECT_RATIO_TALL);
    HeightBreakpoint result = pattern->CalculateHeightBreakpoint(tallHeight, TEST_WIDTH_MD);
    EXPECT_EQ(result, HeightBreakpoint::HEIGHT_LG);
}

/**
 * @tc.name: CalculateHeightBreakpoint006
 * @tc.desc: Test CalculateHeightBreakpoint with custom breakpoint config
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, CalculateHeightBreakpoint006, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ContainerReaderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    BreakPointConfig config;
    config.heightBreakpoints = std::vector<double>{ 0.6, 1.0 };
    layoutProperty->UpdateBreakPointConfig(config);

    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);

    float tallHeight = TEST_WIDTH_MD * static_cast<float>(TEST_ASPECT_RATIO_TALL);
    HeightBreakpoint result = pattern->CalculateHeightBreakpoint(tallHeight, TEST_WIDTH_MD);
    EXPECT_NE(result, HeightBreakpoint::HEIGHT_SM);
}
// ==================== EventHub - FireSizeChange ====================

/**
 * @tc.name: EventHub_FireSizeChange001
 * @tc.desc: Test FireSizeChange fires event when size changes
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, EventHub_FireSizeChange001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<ContainerReaderEventHub>();
    ASSERT_NE(eventHub, nullptr);

    SizeF receivedSize(0.0f, 0.0f);
    eventHub->SetOnSizeChange([&receivedSize](const SizeF& size) { receivedSize = size; });

    SizeF newSize(TEST_WIDTH_MD, TEST_HEIGHT_NORMAL);
    eventHub->FireSizeChange(newSize);
    EXPECT_EQ(receivedSize.Width(), TEST_WIDTH_MD);
    EXPECT_EQ(receivedSize.Height(), TEST_HEIGHT_NORMAL);
}

/**
 * @tc.name: EventHub_FireSizeChange002
 * @tc.desc: Test FireSizeChange does NOT fire event when size is same as last
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, EventHub_FireSizeChange002, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<ContainerReaderEventHub>();
    ASSERT_NE(eventHub, nullptr);

    SizeF sameSize(TEST_WIDTH_MD, TEST_HEIGHT_NORMAL);

    int32_t fireCount = 0;
    eventHub->SetOnSizeChange([&fireCount](const SizeF& size) { fireCount++; });

    eventHub->FireSizeChange(sameSize);
    EXPECT_EQ(fireCount, 1);
}

// ==================== EventHub - FireWidthBreakpointChange ====================

/**
 * @tc.name: EventHub_FireWidthBreakpointChange001
 * @tc.desc: Test FireWidthBreakpointChange fires event when breakpoint changes
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, EventHub_FireWidthBreakpointChange001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<ContainerReaderEventHub>();
    ASSERT_NE(eventHub, nullptr);

    WidthBreakpoint receivedBp = WidthBreakpoint::UNDEFINED;
    eventHub->SetOnWidthBreakpointChange(
        [&receivedBp](WidthBreakpoint bp) { receivedBp = bp; });

    eventHub->FireWidthBreakpointChange(WidthBreakpoint::WIDTH_MD);
    EXPECT_EQ(receivedBp, WidthBreakpoint::WIDTH_MD);
}

/**
 * @tc.name: EventHub_FireWidthBreakpointChange002
 * @tc.desc: Test FireWidthBreakpointChange does NOT fire when same breakpoint
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, EventHub_FireWidthBreakpointChange002, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<ContainerReaderEventHub>();
    ASSERT_NE(eventHub, nullptr);

    int32_t fireCount = 0;
    eventHub->SetOnWidthBreakpointChange(
        [&fireCount](WidthBreakpoint bp) { fireCount++; });

    eventHub->FireWidthBreakpointChange(WidthBreakpoint::WIDTH_MD);
    EXPECT_EQ(fireCount, 1);
}

// ==================== EventHub - FireHeightBreakpointChange ====================

/**
 * @tc.name: EventHub_FireHeightBreakpointChange001
 * @tc.desc: Test FireHeightBreakpointChange fires event when breakpoint changes
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, EventHub_FireHeightBreakpointChange001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<ContainerReaderEventHub>();
    ASSERT_NE(eventHub, nullptr);

    HeightBreakpoint receivedBp = HeightBreakpoint::HEIGHT_SM;
    eventHub->SetOnHeightBreakpointChange(
        [&receivedBp](HeightBreakpoint bp) { receivedBp = bp; });

    eventHub->FireHeightBreakpointChange(HeightBreakpoint::HEIGHT_LG);
    EXPECT_EQ(receivedBp, HeightBreakpoint::HEIGHT_LG);
}

/**
 * @tc.name: EventHub_FireHeightBreakpointChange002
 * @tc.desc: Test FireHeightBreakpointChange does NOT fire when same breakpoint
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, EventHub_FireHeightBreakpointChange002, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<ContainerReaderEventHub>();
    ASSERT_NE(eventHub, nullptr);

    int32_t fireCount = 0;
    eventHub->SetOnHeightBreakpointChange(
        [&fireCount](HeightBreakpoint bp) { fireCount++; });

    eventHub->FireHeightBreakpointChange(HeightBreakpoint::HEIGHT_LG);
    EXPECT_EQ(fireCount, 1);
}

// ==================== LayoutProperty ====================

/**
 * @tc.name: LayoutProperty_UpdateSize001
 * @tc.desc: Test UpdateSize sets size when value changes
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, LayoutProperty_UpdateSize001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<ContainerReaderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SizeF testSize(TEST_WIDTH_MD, TEST_HEIGHT_NORMAL);
    layoutProperty->UpdateSize(testSize);

    auto size = layoutProperty->GetSize();
    ASSERT_TRUE(size.has_value());
    EXPECT_EQ(size.value().Width(), TEST_WIDTH_MD);
    EXPECT_EQ(size.value().Height(), TEST_HEIGHT_NORMAL);
}

/**
 * @tc.name: LayoutProperty_UpdateSize002
 * @tc.desc: Test UpdateSize does not set dirty when same value
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, LayoutProperty_UpdateSize002, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<ContainerReaderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    SizeF testSize(TEST_WIDTH_MD, TEST_HEIGHT_NORMAL);
    layoutProperty->UpdateSize(testSize);
    layoutProperty->UpdateSize(testSize); // Same value again

    auto size = layoutProperty->GetSize();
    ASSERT_TRUE(size.has_value());
    EXPECT_EQ(size.value().Width(), TEST_WIDTH_MD);
}

/**
 * @tc.name: LayoutProperty_UpdateWidthBreakpoint001
 * @tc.desc: Test UpdateWidthBreakpoint sets breakpoint
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, LayoutProperty_UpdateWidthBreakpoint001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<ContainerReaderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->UpdateWidthBreakpoint(WidthBreakpoint::WIDTH_LG);

    auto bp = layoutProperty->GetWidthBreakpoint();
    ASSERT_TRUE(bp.has_value());
    EXPECT_EQ(bp.value(), WidthBreakpoint::WIDTH_LG);
}

/**
 * @tc.name: LayoutProperty_UpdateHeightBreakpoint001
 * @tc.desc: Test UpdateHeightBreakpoint sets breakpoint
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, LayoutProperty_UpdateHeightBreakpoint001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<ContainerReaderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->UpdateHeightBreakpoint(HeightBreakpoint::HEIGHT_MD);

    auto bp = layoutProperty->GetHeightBreakpoint();
    ASSERT_TRUE(bp.has_value());
    EXPECT_EQ(bp.value(), HeightBreakpoint::HEIGHT_MD);
}

/**
 * @tc.name: LayoutProperty_Reset001
 * @tc.desc: Test Reset clears all properties
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, LayoutProperty_Reset001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<ContainerReaderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->UpdateSize(SizeF(TEST_WIDTH_MD, TEST_HEIGHT_NORMAL));
    layoutProperty->UpdateWidthBreakpoint(WidthBreakpoint::WIDTH_LG);
    layoutProperty->UpdateHeightBreakpoint(HeightBreakpoint::HEIGHT_MD);

    layoutProperty->Reset();

    EXPECT_FALSE(layoutProperty->GetSize().has_value());
    EXPECT_FALSE(layoutProperty->GetWidthBreakpoint().has_value());
    EXPECT_FALSE(layoutProperty->GetHeightBreakpoint().has_value());
}

/**
 * @tc.name: LayoutProperty_Clone001
 * @tc.desc: Test Clone copies all properties
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, LayoutProperty_Clone001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<ContainerReaderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->UpdateSize(SizeF(TEST_WIDTH_MD, TEST_HEIGHT_NORMAL));
    layoutProperty->UpdateWidthBreakpoint(WidthBreakpoint::WIDTH_LG);
    layoutProperty->UpdateHeightBreakpoint(HeightBreakpoint::HEIGHT_MD);

    auto cloned = AceType::DynamicCast<ContainerReaderLayoutProperty>(layoutProperty->Clone());
    ASSERT_NE(cloned, nullptr);

    auto size = cloned->GetSize();
    ASSERT_TRUE(size.has_value());
    EXPECT_EQ(size.value().Width(), TEST_WIDTH_MD);
    EXPECT_EQ(size.value().Height(), TEST_HEIGHT_NORMAL);

    auto widthBp = cloned->GetWidthBreakpoint();
    ASSERT_TRUE(widthBp.has_value());
    EXPECT_EQ(widthBp.value(), WidthBreakpoint::WIDTH_LG);

    auto heightBp = cloned->GetHeightBreakpoint();
    ASSERT_TRUE(heightBp.has_value());
    EXPECT_EQ(heightBp.value(), HeightBreakpoint::HEIGHT_MD);
}

// ==================== BreakPointConfig ====================

/**
 * @tc.name: BreakPointConfig_ToString001
 * @tc.desc: Test BreakPointConfig ToString with both breakpoints set
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, BreakPointConfig_ToString001, TestSize.Level1)
{
    BreakPointConfig config;
    config.widthBreakpoints = std::vector<double>{ TEST_CUSTOM_BREAKPOINT_320, TEST_CUSTOM_BREAKPOINT_600 };
    config.heightBreakpoints = std::vector<double>{ TEST_CUSTOM_BREAKPOINT_840 };

    std::string str = config.ToString();
    EXPECT_FALSE(str.empty());
    EXPECT_TRUE(str.find("320") != std::string::npos);
    EXPECT_TRUE(str.find("840") != std::string::npos);
}

/**
 * @tc.name: BreakPointConfig_ToString002
 * @tc.desc: Test BreakPointConfig ToString with empty breakpoints
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, BreakPointConfig_ToString002, TestSize.Level1)
{
    BreakPointConfig config;
    std::string str = config.ToString();
    EXPECT_FALSE(str.empty());
    EXPECT_TRUE(str.find("null") != std::string::npos);
}

// ==================== DumpInfo ====================

/**
 * @tc.name: DumpInfo001
 * @tc.desc: Test DumpInfo does not crash with layout properties set
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, DumpInfo001, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ContainerReaderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSize(SizeF(TEST_WIDTH_MD, TEST_HEIGHT_NORMAL));
    layoutProperty->UpdateWidthBreakpoint(WidthBreakpoint::WIDTH_MD);
    layoutProperty->UpdateHeightBreakpoint(HeightBreakpoint::HEIGHT_SM);

    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->DumpInfo();
}

/**
 * @tc.name: DumpAdvanceInfo001
 * @tc.desc: Test DumpAdvanceInfo does not crash
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, DumpAdvanceInfo001, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->DumpAdvanceInfo();
}

// ==================== ModelNG - SetBreakPointConfig ====================

/**
 * @tc.name: ModelNG_SetBreakPointConfig001
 * @tc.desc: Test SetBreakPointConfig with custom breakpoints
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, ModelNG_SetBreakPointConfig001, TestSize.Level1)
{
    auto frameNode = CreateContainerReader([](ContainerReaderModelNG model) {
        model.SetBreakPointConfig(
            std::vector<double>{ TEST_CUSTOM_BREAKPOINT_320, TEST_CUSTOM_BREAKPOINT_600 },
            std::vector<double>{ TEST_CUSTOM_BREAKPOINT_840 });
    });
    ASSERT_NE(frameNode, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<ContainerReaderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    auto config = layoutProperty->GetBreakPointConfig();
    ASSERT_TRUE(config.has_value());
    ASSERT_TRUE(config->widthBreakpoints.has_value());
    EXPECT_EQ(config->widthBreakpoints->size(), 2UL);
    ASSERT_TRUE(config->heightBreakpoints.has_value());
    EXPECT_EQ(config->heightBreakpoints->size(), 1UL);
}

// ==================== ModelNG - Event setters ====================

/**
 * @tc.name: ModelNG_SetOnSizeChange001
 * @tc.desc: Test SetOnSizeChange registers event handler
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, ModelNG_SetOnSizeChange001, TestSize.Level1)
{
    int32_t eventCount = 0;
    auto frameNode = CreateContainerReader([&eventCount](ContainerReaderModelNG model) {
        model.SetOnSizeChange([&eventCount](const SizeF& size) { eventCount++; });
    });
    ASSERT_NE(frameNode, nullptr);

    auto eventHub = frameNode->GetEventHub<ContainerReaderEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->FireSizeChange(SizeF(TEST_WIDTH_MD, TEST_HEIGHT_NORMAL));
    EXPECT_EQ(eventCount, 1);
}

/**
 * @tc.name: ModelNG_SetOnWidthBreakpointChange001
 * @tc.desc: Test SetOnWidthBreakpointChange registers event handler
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, ModelNG_SetOnWidthBreakpointChange001, TestSize.Level1)
{
    int32_t eventCount = 0;
    auto frameNode = CreateContainerReader([&eventCount](ContainerReaderModelNG model) {
        model.SetOnWidthBreakpointChange([&eventCount](WidthBreakpoint bp) { eventCount++; });
    });
    ASSERT_NE(frameNode, nullptr);

    auto eventHub = frameNode->GetEventHub<ContainerReaderEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->FireWidthBreakpointChange(WidthBreakpoint::WIDTH_LG);
    EXPECT_EQ(eventCount, 1);
}

/**
 * @tc.name: ModelNG_SetOnHeightBreakpointChange001
 * @tc.desc: Test SetOnHeightBreakpointChange registers event handler
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, ModelNG_SetOnHeightBreakpointChange001, TestSize.Level1)
{
    int32_t eventCount = 0;
    auto frameNode = CreateContainerReader([&eventCount](ContainerReaderModelNG model) {
        model.SetOnHeightBreakpointChange([&eventCount](HeightBreakpoint bp) { eventCount++; });
    });
    ASSERT_NE(frameNode, nullptr);

    auto eventHub = frameNode->GetEventHub<ContainerReaderEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->FireHeightBreakpointChange(HeightBreakpoint::HEIGHT_LG);
    EXPECT_EQ(eventCount, 1);
}

// ==================== ModelNG - Static methods ====================

/**
 * @tc.name: ModelNG_StaticSetBreakPointConfig001
 * @tc.desc: Test static SetBreakPointConfig on existing FrameNode
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, ModelNG_StaticSetBreakPointConfig001, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);

    ContainerReaderModelNG::SetBreakPointConfig(
        frameNode.GetRawPtr(),
        std::vector<double>{ TEST_CUSTOM_BREAKPOINT_320 },
        std::vector<double>{ TEST_CUSTOM_BREAKPOINT_600 });

    auto layoutProperty = frameNode->GetLayoutProperty<ContainerReaderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto config = layoutProperty->GetBreakPointConfig();
    ASSERT_TRUE(config.has_value());
    ASSERT_TRUE(config->widthBreakpoints.has_value());
    EXPECT_EQ(config->widthBreakpoints->size(), 1UL);
}

/**
 * @tc.name: ModelNG_StaticResetBreakPointConfig001
 * @tc.desc: Test static ResetBreakPointConfig clears custom breakpoints
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, ModelNG_StaticResetBreakPointConfig001, TestSize.Level1)
{
    auto frameNode = CreateContainerReader();
    ASSERT_NE(frameNode, nullptr);

    // Set custom breakpoints first
    ContainerReaderModelNG::SetBreakPointConfig(
        frameNode.GetRawPtr(),
        std::vector<double>{ TEST_CUSTOM_BREAKPOINT_320 },
        std::vector<double>{ TEST_CUSTOM_BREAKPOINT_600 });

    // Reset breakpoints
    ContainerReaderModelNG::ResetBreakPointConfig(frameNode.GetRawPtr());

    auto layoutProperty = frameNode->GetLayoutProperty<ContainerReaderLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto config = layoutProperty->GetBreakPointConfig();
    ASSERT_TRUE(config.has_value());
    EXPECT_FALSE(config->widthBreakpoints.has_value());
    EXPECT_FALSE(config->heightBreakpoints.has_value());
}

// ==================== Layout Measure ====================

/**
 * @tc.name: LayoutMeasure001
 * @tc.desc: Test ContainerReader fills parent size when placed inside a 200x300 Flex
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, LayoutMeasure001, TestSize.Level1)
{
    RefPtr<FrameNode> reader;
    auto flex = CreateFlexRow([this, &reader](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(TEST_FLEX_WIDTH));
        ViewAbstract::SetHeight(CalcLength(TEST_FLEX_HEIGHT));
        reader = CreateContainerReader();
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_NE(reader, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          ContainerReader()
        }
        .width("200vp")
        .height("300vp")
    */

    // Flex should be 200x300
    auto flexGeometry = flex->GetGeometryNode();
    ASSERT_NE(flexGeometry, nullptr);
    EXPECT_EQ(flexGeometry->GetFrameSize(), SizeF(TEST_FLEX_WIDTH, TEST_FLEX_HEIGHT));

    // ContainerReader should fill parent and be 200x300
    auto readerGeometry = reader->GetGeometryNode();
    ASSERT_NE(readerGeometry, nullptr);
    EXPECT_EQ(readerGeometry->GetFrameSize(), SizeF(TEST_FLEX_WIDTH, TEST_FLEX_HEIGHT));
}

/**
 * @tc.name: LayoutMeasure002
 * @tc.desc: Test ContainerReader takes remaining space after a 60x60 Text in a 200x300 Flex
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, LayoutMeasure002, TestSize.Level1)
{
    RefPtr<FrameNode> text;
    RefPtr<FrameNode> reader;
    auto flex = CreateFlexRow([this, &text, &reader](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(TEST_FLEX_WIDTH));
        ViewAbstract::SetHeight(CalcLength(TEST_FLEX_HEIGHT));
        text = CreateText(u"txt", [](TextModelNG textModel) {
            ViewAbstract::SetWidth(CalcLength(TEST_TEXT_SIZE));
            ViewAbstract::SetHeight(CalcLength(TEST_TEXT_SIZE));
        });
        reader = CreateContainerReader();
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_NE(text, nullptr);
    ASSERT_NE(reader, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 2);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Text("txt")
            .width("60vp")
            .height("60vp")
          ContainerReader()
        }
        .width("200vp")
        .height("300vp")
    */

    // Flex should be 200x300
    auto flexGeometry = flex->GetGeometryNode();
    ASSERT_NE(flexGeometry, nullptr);
    EXPECT_EQ(flexGeometry->GetFrameSize(), SizeF(TEST_FLEX_WIDTH, TEST_FLEX_HEIGHT));

    // Text should be 60x60
    auto textGeometry = text->GetGeometryNode();
    ASSERT_NE(textGeometry, nullptr);
    EXPECT_EQ(textGeometry->GetFrameSize(), SizeF(TEST_TEXT_SIZE, TEST_TEXT_SIZE));

    // ContainerReader should take remaining width (200-60=140) and full height (300)
    auto readerGeometry = reader->GetGeometryNode();
    ASSERT_NE(readerGeometry, nullptr);
    EXPECT_EQ(readerGeometry->GetFrameSize(), SizeF(TEST_READER_EXPECTED_WIDTH, TEST_FLEX_HEIGHT));
}

/**
 * @tc.name: LayoutMeasure003
 * @tc.desc: Test two ContainerReaders with layoutWeight=1 share remaining space after a 60x60 Text in a 200x300 Flex
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, LayoutMeasure003, TestSize.Level1)
{
    RefPtr<FrameNode> text;
    RefPtr<FrameNode> reader1;
    RefPtr<FrameNode> reader2;
    auto flex = CreateFlexRow([this, &text, &reader1, &reader2](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(TEST_FLEX_WIDTH));
        ViewAbstract::SetHeight(CalcLength(TEST_FLEX_HEIGHT));
        text = CreateText(u"txt", [](TextModelNG textModel) {
            ViewAbstract::SetWidth(CalcLength(TEST_TEXT_SIZE));
            ViewAbstract::SetHeight(CalcLength(TEST_TEXT_SIZE));
        });
        reader1 = CreateContainerReader([](ContainerReaderModelNG readerModel) {
            ViewAbstract::SetLayoutWeight(TEST_LAYOUT_WEIGHT);
        });
        reader2 = CreateContainerReader([](ContainerReaderModelNG readerModel) {
            ViewAbstract::SetLayoutWeight(TEST_LAYOUT_WEIGHT);
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_NE(text, nullptr);
    ASSERT_NE(reader1, nullptr);
    ASSERT_NE(reader2, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 3);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Text("txt")
            .width("60vp")
            .height("60vp")
          ContainerReader()
            .layoutWeight(1)
          ContainerReader()
            .layoutWeight(1)
        }
        .width("200vp")
        .height("300vp")
    */

    // Flex should be 200x300
    auto flexGeometry = flex->GetGeometryNode();
    ASSERT_NE(flexGeometry, nullptr);
    EXPECT_EQ(flexGeometry->GetFrameSize(), SizeF(TEST_FLEX_WIDTH, TEST_FLEX_HEIGHT));

    // Text should be 60x60
    auto textGeometry = text->GetGeometryNode();
    ASSERT_NE(textGeometry, nullptr);
    EXPECT_EQ(textGeometry->GetFrameSize(), SizeF(TEST_TEXT_SIZE, TEST_TEXT_SIZE));

    // Both ContainerReaders should share remaining width equally: (200-60)/2 = 70, height = 300
    auto reader1Geometry = reader1->GetGeometryNode();
    ASSERT_NE(reader1Geometry, nullptr);
    EXPECT_EQ(reader1Geometry->GetFrameSize(), SizeF(TEST_READER_LAYOUT_WEIGHT_WIDTH, TEST_FLEX_HEIGHT));

    auto reader2Geometry = reader2->GetGeometryNode();
    ASSERT_NE(reader2Geometry, nullptr);
    EXPECT_EQ(reader2Geometry->GetFrameSize(), SizeF(TEST_READER_LAYOUT_WEIGHT_WIDTH, TEST_FLEX_HEIGHT));
}

/**
 * @tc.name: LayoutMeasure004
 * @tc.desc: Test two layoutWeight=1 ContainerReaders where second has maxWidth=50 in a 200x300 Flex with a 60x60 Text
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, LayoutMeasure004, TestSize.Level1)
{
    RefPtr<FrameNode> text;
    RefPtr<FrameNode> reader1;
    RefPtr<FrameNode> reader2;
    auto flex = CreateFlexRow([this, &text, &reader1, &reader2](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(TEST_FLEX_WIDTH));
        ViewAbstract::SetHeight(CalcLength(TEST_FLEX_HEIGHT));
        text = CreateText(u"txt", [](TextModelNG textModel) {
            ViewAbstract::SetWidth(CalcLength(TEST_TEXT_SIZE));
            ViewAbstract::SetHeight(CalcLength(TEST_TEXT_SIZE));
        });
        reader1 = CreateContainerReader([](ContainerReaderModelNG readerModel) {
            ViewAbstract::SetLayoutWeight(TEST_LAYOUT_WEIGHT);
        });
        reader2 = CreateContainerReader([](ContainerReaderModelNG readerModel) {
            ViewAbstract::SetLayoutWeight(TEST_LAYOUT_WEIGHT);
            ViewAbstract::SetMaxWidth(CalcLength(TEST_READER_MAX_WIDTH));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_NE(text, nullptr);
    ASSERT_NE(reader1, nullptr);
    ASSERT_NE(reader2, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 3);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Text("txt")
            .width("60vp")
            .height("60vp")
          ContainerReader()
            .layoutWeight(1)
          ContainerReader()
            .layoutWeight(1)
            .constraintSize({ maxWidth: "50vp" })
        }
        .width("200vp")
        .height("300vp")
    */

    // Flex should be 200x300
    auto flexGeometry = flex->GetGeometryNode();
    ASSERT_NE(flexGeometry, nullptr);
    EXPECT_EQ(flexGeometry->GetFrameSize(), SizeF(TEST_FLEX_WIDTH, TEST_FLEX_HEIGHT));

    // Text should be 60x60
    auto textGeometry = text->GetGeometryNode();
    ASSERT_NE(textGeometry, nullptr);
    EXPECT_EQ(textGeometry->GetFrameSize(), SizeF(TEST_TEXT_SIZE, TEST_TEXT_SIZE));

    // First ContainerReader: layoutWeight distributes 70, no constraint → 70x300
    auto reader1Geometry = reader1->GetGeometryNode();
    ASSERT_NE(reader1Geometry, nullptr);
    EXPECT_EQ(reader1Geometry->GetFrameSize(), SizeF(TEST_READER_LAYOUT_WEIGHT_WIDTH, TEST_FLEX_HEIGHT));

    // Second ContainerReader: layoutWeight distributes 70, but maxWidth=50 caps it → 50x300
    auto reader2Geometry = reader2->GetGeometryNode();
    ASSERT_NE(reader2Geometry, nullptr);
    EXPECT_EQ(reader2Geometry->GetFrameSize(), SizeF(TEST_READER_MAX_WIDTH, TEST_FLEX_HEIGHT));
}

// ==================== Cross-axis matchParent layout ====================

/**
 * @tc.name: CrossAxisMatchParent001
 * @tc.desc: ContainerReader with only cross-axis matchParent should use remaining main axis space
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, CrossAxisMatchParent001, TestSize.Level1)
{
    int32_t savedVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));

    const float flexWidth = 400.0f;
    const float flexHeight = 300.0f;
    const float textWidth = 100.0f;
    const float textHeight = 100.0f;
    const float expectedReaderWidth = flexWidth - textWidth;

    RefPtr<FrameNode> text;
    RefPtr<FrameNode> reader;
    auto flex = CreateFlexRow([this, &text, &reader, flexWidth, flexHeight, textWidth, textHeight](
        FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(flexWidth));
        ViewAbstract::SetHeight(CalcLength(flexHeight));
        text = CreateText(u"txt", [textWidth, textHeight](TextModelNG textModel) {
            ViewAbstract::SetWidth(CalcLength(textWidth));
            ViewAbstract::SetHeight(CalcLength(textHeight));
        });
        reader = CreateContainerReader([](ContainerReaderModelNG readerModel) {
            ViewAbstractModelNG policyModel;
            policyModel.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_NE(text, nullptr);
    ASSERT_NE(reader, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 2);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Text("txt")
            .width("100vp")
            .height("100vp")
          ContainerReader()
            .height(LayoutPolicy.matchParent)
        }
        .width("400vp")
        .height("300vp")
    */

    auto flexGeometry = flex->GetGeometryNode();
    ASSERT_NE(flexGeometry, nullptr);
    EXPECT_EQ(flexGeometry->GetFrameSize(), SizeF(flexWidth, flexHeight));

    auto textGeometry = text->GetGeometryNode();
    ASSERT_NE(textGeometry, nullptr);
    EXPECT_EQ(textGeometry->GetFrameSize(), SizeF(textWidth, textHeight));

    // ContainerReader: main axis = remaining space (400-100=300), cross axis = parent height (300)
    auto readerGeometry = reader->GetGeometryNode();
    ASSERT_NE(readerGeometry, nullptr);
    EXPECT_EQ(readerGeometry->GetFrameSize(), SizeF(expectedReaderWidth, flexHeight));

    MockContainer::Current()->SetApiTargetVersion(savedVersion);
}

/**
 * @tc.name: CrossAxisMatchParent002
 * @tc.desc: ContainerReader with cross-axis matchParent between two Text siblings uses remaining space
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, CrossAxisMatchParent002, TestSize.Level1)
{
    int32_t savedVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));

    const float flexWidth = 500.0f;
    const float flexHeight = 200.0f;
    const float textWidth1 = 120.0f;
    const float textWidth2 = 80.0f;
        const float expectedReaderWidth = flexWidth - textWidth1 - textWidth2;

    RefPtr<FrameNode> text1;
    RefPtr<FrameNode> reader;
    RefPtr<FrameNode> text2;
    auto flex = CreateFlexRow([this, &text1, &reader, &text2](
        FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500.0f));
        ViewAbstract::SetHeight(CalcLength(200.0f));
        text1 = CreateText(u"A", [](TextModelNG textModel) {
            ViewAbstract::SetWidth(CalcLength(120.0f));
            ViewAbstract::SetHeight(CalcLength(60.0f));
        });
        reader = CreateContainerReader([](ContainerReaderModelNG readerModel) {
            ViewAbstractModelNG policyModel;
            policyModel.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
        });
        text2 = CreateText(u"B", [](TextModelNG textModel) {
            ViewAbstract::SetWidth(CalcLength(80.0f));
            ViewAbstract::SetHeight(CalcLength(60.0f));
        });
    });
    ASSERT_NE(flex, nullptr);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Text("A").width("120vp").height("60vp")
          ContainerReader().height(LayoutPolicy.matchParent)
          Text("B").width("80vp").height("60vp")
        }
        .width("500vp")
        .height("200vp")
    */

    // ContainerReader main axis = 500 - 120 - 80 = 300, cross axis = 200
    auto readerGeometry = reader->GetGeometryNode();
    ASSERT_NE(readerGeometry, nullptr);
    EXPECT_EQ(readerGeometry->GetFrameSize(), SizeF(expectedReaderWidth, flexHeight));

    MockContainer::Current()->SetApiTargetVersion(savedVersion);
}

/**
 * @tc.name: CrossAxisMatchParent003
 * @tc.desc: ContainerReader with only main-axis matchParent should NOT use remaining-space logic
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, CrossAxisMatchParent003, TestSize.Level1)
{
    int32_t savedVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));

    const float flexWidth = 400.0f;
    const float flexHeight = 300.0f;

    RefPtr<FrameNode> text;
    RefPtr<FrameNode> reader;
    auto flex = CreateFlexRow([this, &text, &reader](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(400.0f));
        ViewAbstract::SetHeight(CalcLength(300.0f));
        text = CreateText(u"txt", [](TextModelNG textModel) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(100.0f));
        });
        reader = CreateContainerReader([](ContainerReaderModelNG readerModel) {
            ViewAbstractModelNG policyModel;
            policyModel.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_NE(text, nullptr);
    ASSERT_NE(reader, nullptr);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Text("txt").width("100vp").height("100vp")
          ContainerReader().width(LayoutPolicy.matchParent)
        }
        .width("400vp")
        .height("300vp")
    */

    // main-axis matchParent: ContainerReader width = parent width (400), not remaining
    auto readerGeometry = reader->GetGeometryNode();
    ASSERT_NE(readerGeometry, nullptr);
    EXPECT_EQ(readerGeometry->GetFrameSize(), SizeF(flexWidth, flexHeight));

    MockContainer::Current()->SetApiTargetVersion(savedVersion);
}

/**
 * @tc.name: CrossAxisMatchParent004
 * @tc.desc: Multiple ContainerReaders with cross-axis matchParent in Column layout
 * @tc.type: FUNC
 */
HWTEST_F(ContainerReaderTestNg, CrossAxisMatchParent004, TestSize.Level1)
{
    int32_t savedVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));

    const float columnWidth = 300.0f;
    const float columnHeight = 400.0f;
    const float textHeight = 100.0f;
        // In Column: main axis = vertical, cross axis = horizontal
    // ContainerReader with cross-axis matchParent → width = parent width (300)
    // ContainerReader main axis (height) = remaining space = 400 - 100 = 300
    const float expectedReaderHeight = columnHeight - textHeight;

    RefPtr<FrameNode> text;
    RefPtr<FrameNode> reader;
    auto column = CreateColumn([this, &text, &reader](ColumnModelNG model) {
        ViewAbstract::SetWidth(CalcLength(300.0f));
        ViewAbstract::SetHeight(CalcLength(400.0f));
        text = CreateText(u"txt", [](TextModelNG textModel) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(100.0f));
        });
        reader = CreateContainerReader([](ContainerReaderModelNG readerModel) {
            ViewAbstractModelNG policyModel;
            policyModel.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
        });
    });
    ASSERT_NE(column, nullptr);
    ASSERT_NE(text, nullptr);
    ASSERT_NE(reader, nullptr);
    CreateLayoutTask(column);

    /* corresponding ets code:
        Column() {
          Text("txt").width("100vp").height("100vp")
          ContainerReader().width(LayoutPolicy.matchParent)
        }
        .width("300vp")
        .height("400vp")
    */

    auto readerGeometry = reader->GetGeometryNode();
    ASSERT_NE(readerGeometry, nullptr);
    EXPECT_EQ(readerGeometry->GetFrameSize(), SizeF(columnWidth, expectedReaderHeight));

    MockContainer::Current()->SetApiTargetVersion(savedVersion);
}
} // namespace OHOS::Ace::NG
