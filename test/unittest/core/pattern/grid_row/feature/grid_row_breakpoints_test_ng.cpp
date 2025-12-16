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
#include "test/unittest/core/pattern/grid_row/grid_row_base_test_ng.h"
#include "core/components_v2/grid_layout/grid_container_utils.h"

namespace OHOS::Ace::NG {
namespace {
    constexpr double DEFAULT_CHILD_HEIGHT = 30.0f;
} // namespace
class GridRowBreakPointsTestNG : public GridRowBaseTestNG {
};

/**
 * @tc.name: OnBreakpointChangeTest01
 * @tc.desc: Test OnBreakpointChange
 * @tc.type: FUNC
 */
HWTEST_F(GridRowBreakPointsTestNG, OnBreakpointChangeTest01, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create GridRow
     */
    auto gridRow = CreateGridRow([this](GridRowModelNG model) {
        V2::BreakPoints breakpoints;
        breakpoints.reference = V2::BreakPointsReference::ComponentSize;
        breakpoints.breakpoints.assign({ "100px", "200px", "300px", "400px", "500px" });
        ViewAbstract::SetWidth(CalcLength(10));
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, BreakPoints, breakpoints);
    });
    auto eventHub = gridRow->GetEventHub<GridRowEventHub>();
    bool eventTriggerFlag = false;
    auto layoutProperty = gridRow->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    /**
     * @tc.steps: step2. Set OnBreakpointChange callback
     * @tc.expected: breakpoint is changed to xs
     */
    eventHub->SetOnBreakpointChange([&eventTriggerFlag, expectSize = std::string("xs")](const std::string& size) {
        eventTriggerFlag = true;
        EXPECT_EQ(size, expectSize);
    });
    CreateMeasureLayoutTask(gridRow);
    EXPECT_TRUE(eventTriggerFlag);
    eventTriggerFlag = false;
    /**
     * @tc.expected: breakpoint is changed to sm
     */
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(100), CalcLength(DEFAULT_CHILD_HEIGHT)));
    eventHub->SetOnBreakpointChange([&eventTriggerFlag, expectSize = std::string("sm")](const std::string& size) {
        eventTriggerFlag = true;
        EXPECT_EQ(size, expectSize);
    });
    CreateMeasureLayoutTask(gridRow);
    EXPECT_TRUE(eventTriggerFlag);
    eventTriggerFlag = false;
    /**
     * @tc.expected: breakpoint is changed to md
     */
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(200), CalcLength(DEFAULT_CHILD_HEIGHT)));
    eventHub->SetOnBreakpointChange([&eventTriggerFlag, expectSize = std::string("md")](const std::string& size) {
        eventTriggerFlag = true;
        EXPECT_EQ(size, expectSize);
    });
    CreateMeasureLayoutTask(gridRow);
    EXPECT_TRUE(eventTriggerFlag);
}

/**
 * @tc.name: OnBreakpointChangeTest02
 * @tc.desc: Test OnBreakpointChange
 * @tc.type: FUNC
 */
HWTEST_F(GridRowBreakPointsTestNG, OnBreakpointChangeTest02, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create GridRow
     */
    auto gridRow = CreateGridRow([this](GridRowModelNG model) {
        V2::BreakPoints breakpoints;
        breakpoints.reference = V2::BreakPointsReference::ComponentSize;
        breakpoints.breakpoints.assign({ "100px", "200px", "300px", "400px", "500px" });
        ViewAbstract::SetWidth(CalcLength(300));
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, BreakPoints, breakpoints);
    });
    auto eventHub = gridRow->GetEventHub<GridRowEventHub>();
    bool eventTriggerFlag = false;
    auto layoutProperty = gridRow->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    /**
     * @tc.steps: step2. Set OnBreakpointChange callback
     * @tc.expected: breakpoint is changed to lg
     */
    eventHub->SetOnBreakpointChange([&eventTriggerFlag, expectSize = std::string("lg")](const std::string& size) {
        eventTriggerFlag = true;
        EXPECT_EQ(size, expectSize);
    });
    CreateMeasureLayoutTask(gridRow);
    EXPECT_TRUE(eventTriggerFlag);
    eventTriggerFlag = false;
    /**
     * @tc.expected: breakpoint is changed to xl
     */
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(400), CalcLength(DEFAULT_CHILD_HEIGHT)));
    eventHub->SetOnBreakpointChange([&eventTriggerFlag, expectSize = std::string("xl")](const std::string& size) {
        eventTriggerFlag = true;
        EXPECT_EQ(size, expectSize);
    });
    CreateMeasureLayoutTask(gridRow);
    EXPECT_TRUE(eventTriggerFlag);
    eventTriggerFlag = false;
    /**
     * @tc.expected: breakpoint is changed to xxl
     */
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(500), CalcLength(DEFAULT_CHILD_HEIGHT)));
    eventHub->SetOnBreakpointChange([&eventTriggerFlag, expectSize = std::string("xxl")](const std::string& size) {
        eventTriggerFlag = true;
        EXPECT_EQ(size, expectSize);
    });
    CreateMeasureLayoutTask(gridRow);
    EXPECT_TRUE(eventTriggerFlag);
}

/**
 * @tc.name: OnBreakpointChangeTest03
 * @tc.desc: Test OnBreakpointChange
 * @tc.type: FUNC
 */
HWTEST_F(GridRowBreakPointsTestNG, OnBreakpointChangeTest03, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create GridRow
     */
    auto gridRow = CreateGridRow([this](GridRowModelNG model) {
        V2::BreakPoints breakpoints;
        breakpoints.reference = V2::BreakPointsReference::ComponentSize;
        breakpoints.breakpoints.assign({ "100px", "200px", "300px" });
        ViewAbstract::SetWidth(CalcLength(400));
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, BreakPoints, breakpoints);
    });
    auto eventHub = gridRow->GetEventHub<GridRowEventHub>();
    bool eventTriggerFlag = false;
    auto layoutProperty = gridRow->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    /**
     * @tc.steps: step2. Set OnBreakpointChange callback
     * @tc.expected: breakpoint is changed to lg
     */
    eventHub->SetOnBreakpointChange([&eventTriggerFlag, expectSize = std::string("lg")](const std::string& size) {
        eventTriggerFlag = true;
        EXPECT_EQ(size, expectSize);
    });
    CreateMeasureLayoutTask(gridRow);
    EXPECT_TRUE(eventTriggerFlag);
    eventTriggerFlag = false;
    /**
     * @tc.expected: breakpoint is changed to xl
     */
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(250), CalcLength(DEFAULT_CHILD_HEIGHT)));
    eventHub->SetOnBreakpointChange([&eventTriggerFlag, expectSize = std::string("md")](const std::string& size) {
        eventTriggerFlag = true;
        EXPECT_EQ(size, expectSize);
    });
    CreateMeasureLayoutTask(gridRow);
    EXPECT_TRUE(eventTriggerFlag);
    eventTriggerFlag = false;
    /**
     * @tc.expected: breakpoint is changed to xxl
     */
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(150), CalcLength(DEFAULT_CHILD_HEIGHT)));
    eventHub->SetOnBreakpointChange([&eventTriggerFlag, expectSize = std::string("sm")](const std::string& size) {
        eventTriggerFlag = true;
        EXPECT_EQ(size, expectSize);
    });
    CreateMeasureLayoutTask(gridRow);
    EXPECT_TRUE(eventTriggerFlag);
}

/**
* @tc.name  : ProcessGridSizeType_ShouldReturnUndefined_WhenPipelineIsNull
* @tc.number: ProcessGridSizeType_Test_001
* @tc.desc  : Test case to verify that ProcessGridSizeType returns UNDEFINED when pipeline is null
*/
HWTEST_F(GridRowBreakPointsTestNG, ProcessGridSizeType_ShouldReturnUndefined_WhenPipelineIsNull, TestSize.Level0) {
    V2::BreakPoints breakpoints;
    breakpoints.reference = V2::BreakPointsReference::WindowSize;
    Size size;
    WindowMode mode = WindowMode::WINDOW_MODE_FLOATING;
    RefPtr<PipelineBase> pipeline = nullptr;
    V2::GridSizeType result = V2::GridContainerUtils::ProcessGridSizeType(breakpoints, size, mode, pipeline);

    EXPECT_EQ(result, V2::GridSizeType::UNDEFINED);
}

/**
* @tc.name  : ProcessGridSizeType_ShouldReturnCorrectType_WhenReferenceIsNotWindowSize
* @tc.number: ProcessGridSizeType_Test_004
* @tc.desc  : Test ProcessGridSizeType returns the correct GridSizeType when reference is not WindowSize
*/
HWTEST_F(GridRowBreakPointsTestNG, ProcessGridSizeType_WhenReferenceIsNotWindowSize, TestSize.Level0) {
    V2::BreakPoints breakpoints;
    breakpoints.reference = V2::BreakPointsReference::ComponentSize;
    Size size(1000, 1000);
    WindowMode mode = WindowMode::WINDOW_MODE_FULLSCREEN;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    V2::GridSizeType result = V2::GridContainerUtils::ProcessGridSizeType(breakpoints, size, mode, pipeline);
    // Assuming CalcBreakPoint returns 3 for windowWidth = 1000
    EXPECT_EQ(result, V2::GridSizeType::LG);
}

/**
 * @tc.name: ProcessGridSizeType_WindowSize01
 * @tc.desc: Test ProcessGridSizeType Return XS When Window Size is 319
 * @tc.type: FUNC
 */
HWTEST_F(GridRowBreakPointsTestNG, ProcessGridSizeType_WindowSize01, TestSize.Level0)
{
    V2::BreakPoints breakpoints;
    breakpoints.reference = V2::BreakPointsReference::WindowSize;
    Size size(1000, 1000);
    WindowMode mode = WindowMode::WINDOW_MODE_FULLSCREEN;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    Rect displayWindowRectInfo = Rect(0, 0, 319, 1000);
    pipeline->SetDisplayWindowRectInfo(displayWindowRectInfo);
    auto container = AceType::DynamicCast<Container>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion((int32_t)PlatformVersion::VERSION_TWENTY);
    EXPECT_TRUE(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY));
    V2::GridSizeType result = V2::GridContainerUtils::ProcessGridSizeType(breakpoints, size, mode, pipeline);
    EXPECT_EQ(result, V2::GridSizeType::XS);
}


/**
 * @tc.name: ProcessGridSizeType_WindowSize02
 * @tc.desc: Test ProcessGridSizeType Return SM When Window Size is 320
 * @tc.type: FUNC
 */
HWTEST_F(GridRowBreakPointsTestNG, ProcessGridSizeType_WindowSize02, TestSize.Level0)
{
    V2::BreakPoints breakpoints;
    breakpoints.reference = V2::BreakPointsReference::WindowSize;
    Size size(1000, 1000);
    WindowMode mode = WindowMode::WINDOW_MODE_FULLSCREEN;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    Rect displayWindowRectInfo = Rect(0, 0, 320, 1000);
    pipeline->SetDisplayWindowRectInfo(displayWindowRectInfo);
    auto container = AceType::DynamicCast<Container>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion((int32_t)PlatformVersion::VERSION_TWENTY);
    EXPECT_TRUE(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY));
    V2::GridSizeType result = V2::GridContainerUtils::ProcessGridSizeType(breakpoints, size, mode, pipeline);
    EXPECT_EQ(result, V2::GridSizeType::SM);
}

/**
 * @tc.name: ProcessGridSizeType_WindowSize03
 * @tc.desc: Test ProcessGridSizeType Return SM When Window Size is 321
 * @tc.type: FUNC
 */
HWTEST_F(GridRowBreakPointsTestNG, ProcessGridSizeType_WindowSize03, TestSize.Level0)
{
    V2::BreakPoints breakpoints;
    breakpoints.reference = V2::BreakPointsReference::WindowSize;
    Size size(1000, 1000);
    WindowMode mode = WindowMode::WINDOW_MODE_FULLSCREEN;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    Rect displayWindowRectInfo = Rect(0, 0, 321, 1000);
    pipeline->SetDisplayWindowRectInfo(displayWindowRectInfo);
    auto container = AceType::DynamicCast<Container>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion((int32_t)PlatformVersion::VERSION_TWENTY);
    EXPECT_TRUE(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY));
    V2::GridSizeType result = V2::GridContainerUtils::ProcessGridSizeType(breakpoints, size, mode, pipeline);
    EXPECT_EQ(result, V2::GridSizeType::SM);
}

/**
 * @tc.name: ProcessGridSizeType_WindowSize04
 * @tc.desc: Test ProcessGridSizeType Return SM When Window Size is 599
 * @tc.type: FUNC
 */
HWTEST_F(GridRowBreakPointsTestNG, ProcessGridSizeType_WindowSize04, TestSize.Level0)
{
    V2::BreakPoints breakpoints;
    breakpoints.reference = V2::BreakPointsReference::WindowSize;
    Size size(1000, 1000);
    WindowMode mode = WindowMode::WINDOW_MODE_FULLSCREEN;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    Rect displayWindowRectInfo = Rect(0, 0, 599, 1000);
    pipeline->SetDisplayWindowRectInfo(displayWindowRectInfo);
    auto container = AceType::DynamicCast<Container>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion((int32_t)PlatformVersion::VERSION_TWENTY);
    EXPECT_TRUE(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY));
    V2::GridSizeType result = V2::GridContainerUtils::ProcessGridSizeType(breakpoints, size, mode, pipeline);
    EXPECT_EQ(result, V2::GridSizeType::SM);
}

/**
 * @tc.name: ProcessGridSizeType_WindowSize05
 * @tc.desc: Test ProcessGridSizeType Return MD When Window Size is 600
 * @tc.type: FUNC
 */
HWTEST_F(GridRowBreakPointsTestNG, ProcessGridSizeType_WindowSize05, TestSize.Level0)
{
    V2::BreakPoints breakpoints;
    breakpoints.reference = V2::BreakPointsReference::WindowSize;
    Size size(1000, 1000);
    WindowMode mode = WindowMode::WINDOW_MODE_FULLSCREEN;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    Rect displayWindowRectInfo = Rect(0, 0, 600, 1000);
    pipeline->SetDisplayWindowRectInfo(displayWindowRectInfo);
    auto container = AceType::DynamicCast<Container>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion((int32_t)PlatformVersion::VERSION_TWENTY);
    EXPECT_TRUE(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY));
    V2::GridSizeType result = V2::GridContainerUtils::ProcessGridSizeType(breakpoints, size, mode, pipeline);
    // Assuming CalcBreakPoint returns 3 for windowWidth = 601
    EXPECT_EQ(result, V2::GridSizeType::MD);
}

/**
 * @tc.name: ProcessGridSizeType_WindowSize06
 * @tc.desc: Test ProcessGridSizeType Return MD When Window Size is 601
 * @tc.type: FUNC
 */
HWTEST_F(GridRowBreakPointsTestNG, ProcessGridSizeType_WindowSize06, TestSize.Level0)
{
    V2::BreakPoints breakpoints;
    breakpoints.reference = V2::BreakPointsReference::WindowSize;
    Size size(1000, 1000);
    WindowMode mode = WindowMode::WINDOW_MODE_FULLSCREEN;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    Rect displayWindowRectInfo = Rect(0, 0, 601, 1000);
    pipeline->SetDisplayWindowRectInfo(displayWindowRectInfo);
    auto container = AceType::DynamicCast<Container>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion((int32_t)PlatformVersion::VERSION_TWENTY);
    EXPECT_TRUE(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY));
    V2::GridSizeType result = V2::GridContainerUtils::ProcessGridSizeType(breakpoints, size, mode, pipeline);
    EXPECT_EQ(result, V2::GridSizeType::MD);
}

/**
 * @tc.name: ProcessGridSizeType_WindowSize07
 * @tc.desc: Test ProcessGridSizeType Return MD When Window Size is 839
 * @tc.type: FUNC
 */
HWTEST_F(GridRowBreakPointsTestNG, ProcessGridSizeType_WindowSize07, TestSize.Level0)
{
    V2::BreakPoints breakpoints;
    breakpoints.reference = V2::BreakPointsReference::WindowSize;
    Size size(1000, 1000);
    WindowMode mode = WindowMode::WINDOW_MODE_FULLSCREEN;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    Rect displayWindowRectInfo = Rect(0, 0, 839, 1000);
    pipeline->SetDisplayWindowRectInfo(displayWindowRectInfo);
    auto container = AceType::DynamicCast<Container>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion((int32_t)PlatformVersion::VERSION_TWENTY);
    EXPECT_TRUE(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY));
    V2::GridSizeType result = V2::GridContainerUtils::ProcessGridSizeType(breakpoints, size, mode, pipeline);
    EXPECT_EQ(result, V2::GridSizeType::MD);
}

/**
 * @tc.name: ProcessGridSizeType_WindowSize08
 * @tc.desc: Test ProcessGridSizeType Return LG When Window Size is 840
 * @tc.type: FUNC
 */
HWTEST_F(GridRowBreakPointsTestNG, ProcessGridSizeType_WindowSize08, TestSize.Level0)
{
    V2::BreakPoints breakpoints;
    breakpoints.reference = V2::BreakPointsReference::WindowSize;
    Size size(1000, 1000);
    WindowMode mode = WindowMode::WINDOW_MODE_FULLSCREEN;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    Rect displayWindowRectInfo = Rect(0, 0, 840, 1000);
    pipeline->SetDisplayWindowRectInfo(displayWindowRectInfo);
    auto container = AceType::DynamicCast<Container>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion((int32_t)PlatformVersion::VERSION_TWENTY);
    EXPECT_TRUE(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY));
    V2::GridSizeType result = V2::GridContainerUtils::ProcessGridSizeType(breakpoints, size, mode, pipeline);
    EXPECT_EQ(result, V2::GridSizeType::LG);
}

/**
 * @tc.name: ProcessGridSizeType_WindowSize09
 * @tc.desc: Test ProcessGridSizeType Return LG When Window Size is 841
 * @tc.type: FUNC
 */
HWTEST_F(GridRowBreakPointsTestNG, ProcessGridSizeType_WindowSize09, TestSize.Level0)
{
    V2::BreakPoints breakpoints;
    breakpoints.reference = V2::BreakPointsReference::WindowSize;
    Size size(1000, 1000);
    WindowMode mode = WindowMode::WINDOW_MODE_FULLSCREEN;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    Rect displayWindowRectInfo = Rect(0, 0, 841, 1000);
    pipeline->SetDisplayWindowRectInfo(displayWindowRectInfo);
    auto container = AceType::DynamicCast<Container>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion((int32_t)PlatformVersion::VERSION_TWENTY);
    EXPECT_TRUE(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY));
    V2::GridSizeType result = V2::GridContainerUtils::ProcessGridSizeType(breakpoints, size, mode, pipeline);
    /**
     * @tc.expected: breakpoint is lg
     */
    EXPECT_EQ(result, V2::GridSizeType::LG);
}

/**
 * @tc.name: ProcessGridSizeType_WindowSize_SelfDefine_01
 * @tc.desc: Test ProcessGridSizeType Return XL When Window Size is 500 And
 *           breakpoints.assign({ "100vp", "200vp","300vp", "400vp", "600vp" })
 * @tc.type: FUNC
 */
HWTEST_F(GridRowBreakPointsTestNG, ProcessGridSizeType_WindowSize_SelfDefine_01, TestSize.Level0)
{
    V2::BreakPoints breakpoints;
    breakpoints.reference = V2::BreakPointsReference::WindowSize;
    breakpoints.breakpoints.assign({ "100px", "200px", "300px", "400px", "600px" });
    breakpoints.userDefine = true;
    Size size(1000, 1000);
    WindowMode mode = WindowMode::WINDOW_MODE_FULLSCREEN;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    Rect displayWindowRectInfo = Rect(0, 0, 500, 1000);
    pipeline->SetDisplayWindowRectInfo(displayWindowRectInfo);
    auto container = AceType::DynamicCast<Container>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion((int32_t)PlatformVersion::VERSION_TWENTY);
    EXPECT_TRUE(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY));
    V2::GridSizeType result = V2::GridContainerUtils::ProcessGridSizeType(breakpoints, size, mode, pipeline);
    /**
     * @tc.expected: breakpoint is xl
     */
    EXPECT_EQ(result, V2::GridSizeType::XL);
}

/**
 * @tc.name: ProcessGridSizeTypeNULLPipelineContext
 * @tc.desc: Test ProcessGridSizeType will not crash when the pipeline context is NULL
 * @tc.type: FUNC
 */
HWTEST_F(GridRowBreakPointsTestNG, ProcessGridSizeTypeNULLPipelineContext, TestSize.Level0)
{
    V2::BreakPoints breakpoints;
    WindowMode mode = WindowMode::WINDOW_MODE_FULLSCREEN;
    Size size(1000, 1000);
    V2::GridSizeType result = V2::GridContainerUtils::ProcessGridSizeType(breakpoints, size, mode, nullptr);
    /**
     * @tc.expected: breakpoint is changed to UNDEFINED when the pipeline context is NULL
     */
    EXPECT_EQ(result, V2::GridSizeType::UNDEFINED);
}
} // namespace OHOS::Ace::NG
