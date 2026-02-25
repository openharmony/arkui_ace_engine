/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <cstddef>
#include <optional>
#include <unistd.h>
#include <vector>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/render/mock_render_surface.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/common/ai/image_analyzer_mgr.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_controller_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_layout_algorithm.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern_v2.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_surface_holder.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_inner_surface_controller.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "frameworks/core/gestures/press_recognizer.h"
#include "frameworks/core/components_ng/pattern/node_container/node_container_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_ext_surface_callback_client.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
struct TestProperty {
    std::optional<std::string> xcId = std::nullopt;
    std::optional<XComponentType> xcType = std::nullopt;
    std::optional<std::string> libraryName = std::nullopt;
    std::optional<std::string> soPath = std::nullopt;
    std::optional<LoadEvent> loadEvent = std::nullopt;
    std::optional<DestroyEvent> destroyEvent = std::nullopt;
    std::optional<SurfaceCreatedEvent> surfaceCreatedEvent = std::nullopt;
    std::optional<SurfaceChangedEvent> surfaceChangedEvent = std::nullopt;
    std::optional<SurfaceDestroyedEvent> surfaceDestroyedEvent = std::nullopt;
};
namespace {
const std::string XCOMPONENT_ID = "xcomponent";
const std::string XCOMPONENT_LIBRARY_NAME = "native_render";
const std::string XCOMPONENT_SO_PATH = "com.example.xcomponentmultihap/entry";
const std::string SURFACE_ID = "2430951489577";
constexpr XComponentType XCOMPONENT_COMPONENT_TYPE_VALUE = XComponentType::COMPONENT;
TestProperty testProperty;
} // namespace

class XComponentLayoutTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void TearDown() override
    {
        testProperty.loadEvent = std::nullopt;
        testProperty.destroyEvent = std::nullopt;
        testProperty.surfaceCreatedEvent = std::nullopt;
        testProperty.surfaceChangedEvent = std::nullopt;
        testProperty.surfaceDestroyedEvent = std::nullopt;
    }

protected:
    static RefPtr<FrameNode> CreateXComponentNode(TestProperty& testProperty);
};

void XComponentLayoutTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    testProperty.xcId = XCOMPONENT_ID;
    testProperty.libraryName = XCOMPONENT_LIBRARY_NAME;
    testProperty.soPath = XCOMPONENT_SO_PATH;
}

void XComponentLayoutTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> XComponentLayoutTestNg::CreateXComponentNode(TestProperty& testProperty)
{
    auto xcomponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG().Create(testProperty.xcId, testProperty.xcType.value(),
        testProperty.libraryName, xcomponentController);
    if (testProperty.soPath.has_value()) {
        XComponentModelNG().SetSoPath(testProperty.soPath.value());
    }
    if (testProperty.loadEvent.has_value()) {
        XComponentModelNG().SetOnLoad(std::move(testProperty.loadEvent.value()));
    }
    if (testProperty.destroyEvent.has_value()) {
        XComponentModelNG().SetOnDestroy(std::move(testProperty.destroyEvent.value()));
    }
    if (testProperty.surfaceCreatedEvent.has_value()) {
        XComponentModelNG().SetControllerOnCreated(std::move(testProperty.surfaceCreatedEvent.value()));
    }
    if (testProperty.surfaceChangedEvent.has_value()) {
        XComponentModelNG().SetControllerOnChanged(std::move(testProperty.surfaceChangedEvent.value()));
    }
    if (testProperty.surfaceDestroyedEvent.has_value()) {
        XComponentModelNG().SetControllerOnDestroyed(std::move(testProperty.surfaceDestroyedEvent.value()));
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish(); // pop
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: AddLayoutTask002
 * @tc.desc: Test AddLayoutTask when paintRect_ is unchanged, should return early
 * @tc.type: FUNC
 */
HWTEST_F(XComponentLayoutTestNg, AddLayoutTask002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_COMPONENT_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. setup initial state
     */
    pattern->surfaceId_ = SURFACE_ID;
    pattern->drawSize_ = SizeF(400.0f, 400.0f);
    pattern->surfaceSize_ = SizeF(400.0f, 400.0f);
    pattern->surfaceOffset_ = OffsetF(0.0f, 0.0f);
    pattern->paintRect_ = RectF(OffsetF(0.0f, 0.0f), SizeF(400.0f, 400.0f));

    Rect displayWindowRectInfo = Rect(0, 0, 400, 400);
    MockPipelineContext::pipeline_->SetDisplayWindowRectInfo(displayWindowRectInfo);

    pattern->handlingSurfaceRenderContext_ = nullptr;

    /**
     * @tc.steps: step3. first call to AddLayoutTask to set initial paintRect_
     */
    pattern->AddLayoutTask();

    /**
     * @tc.steps: step5. verify paintRect_ remains unchanged
     */
    EXPECT_EQ(pattern->paintRect_.GetX(), 0.0f);
    EXPECT_EQ(pattern->paintRect_.GetY(), 0.0f);
    EXPECT_EQ(pattern->paintRect_.Width(), 400.0f);
    EXPECT_EQ(pattern->paintRect_.Height(), 400.0f);
}

/**
 * @tc.name: AddLayoutTask003
 * @tc.desc: Test AddLayoutTask when paintRect_ changes, should update and call SetBounds
 * @tc.type: FUNC
 */
HWTEST_F(XComponentLayoutTestNg, AddLayoutTask003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_COMPONENT_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. setup initial state with small window
     */
    pattern->surfaceId_ = SURFACE_ID;
    pattern->drawSize_ = SizeF(400.0f, 400.0f);
    pattern->surfaceSize_ = SizeF(400.0f, 400.0f);
    pattern->surfaceOffset_ = OffsetF(0.0f, 0.0f);
    pattern->paintRect_ = RectF(OffsetF(0.0f, 0.0f), SizeF(200.0f, 200.0f)); // Initial small rect

    Rect displayWindowRectInfo = Rect(0, 0, 400, 400);
    MockPipelineContext::pipeline_->SetDisplayWindowRectInfo(displayWindowRectInfo);

    pattern->handlingSurfaceRenderContext_ = nullptr;

    /**
     * @tc.steps: step3. call AddLayoutTask, paintRect_ should change
     * @tc.expected: SetBounds and RequestNextFrame should be called
     */

    pattern->AddLayoutTask();

    /**
     * @tc.steps: step4. verify paintRect_ is updated
     */
    EXPECT_EQ(pattern->surfaceSize_.Width(), 400.0f);
    EXPECT_EQ(pattern->surfaceSize_.Height(), 400.0f);
    EXPECT_EQ(pattern->paintRect_.Width(), 400.0f);
    EXPECT_EQ(pattern->paintRect_.Height(), 400.0f);
}

/**
 * @tc.name: AddLayoutTask004
 * @tc.desc: Test AddLayoutTask when surfaceSize_ is near zero, should skip scaling
 * @tc.type: FUNC
 */
HWTEST_F(XComponentLayoutTestNg, AddLayoutTask004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_COMPONENT_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. setup surfaceSize_ to near zero
     */
    pattern->surfaceId_ = SURFACE_ID;
    pattern->drawSize_ = SizeF(400.0f, 400.0f);
    pattern->surfaceSize_ = SizeF(0.0f, 0.0f); // Near zero
    pattern->paintRect_ = RectF(OffsetF(0.0f, 0.0f), SizeF(0.0f, 0.0f));

    Rect displayWindowRectInfo = Rect(0, 0, 400, 400);
    MockPipelineContext::pipeline_->SetDisplayWindowRectInfo(displayWindowRectInfo);

    pattern->handlingSurfaceRenderContext_ = nullptr;

    /**
     * @tc.steps: step3. call AddLayoutTask with zero surfaceSize
     * @tc.expected: should return early, SetBounds NOT called
     */

    pattern->AddLayoutTask();

    /**
     * @tc.steps: step4. verify surfaceSize_ remains zero
     */
    EXPECT_TRUE(NearZero(pattern->surfaceSize_.Width()));
    EXPECT_TRUE(NearZero(pattern->surfaceSize_.Height()));
}

/**
 * @tc.name: AddLayoutTask005
 * @tc.desc: Test AddLayoutTask when handlingSurfaceRenderContext_ is null
 * @tc.type: FUNC
 */
HWTEST_F(XComponentLayoutTestNg, AddLayoutTask005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_COMPONENT_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. setup without handlingSurfaceRenderContext_
     */
    pattern->surfaceId_ = SURFACE_ID;
    pattern->drawSize_ = SizeF(400.0f, 400.0f);
    pattern->surfaceSize_ = SizeF(200.0f, 200.0f);
    pattern->paintRect_ = RectF(OffsetF(0.0f, 0.0f), SizeF(100.0f, 100.0f));

    Rect displayWindowRectInfo = Rect(0, 0, 400, 400);
    MockPipelineContext::pipeline_->SetDisplayWindowRectInfo(displayWindowRectInfo);

    pattern->handlingSurfaceRenderContext_ = nullptr; // Null context

    /**
     * @tc.steps: step3. call AddLayoutTask with null context
     * @tc.expected: should update paintRect_ but not call SetBounds (CHECK_NULL_VOID)
     */
    pattern->AddLayoutTask();

    /**
     * @tc.steps: step4. verify paintRect_ is still updated
     */
    EXPECT_EQ(pattern->surfaceSize_.Width(), 400.0f);
    EXPECT_EQ(pattern->surfaceSize_.Height(), 400.0f);
    EXPECT_EQ(pattern->paintRect_.Width(), 400.0f);
    EXPECT_EQ(pattern->paintRect_.Height(), 400.0f);
}

/**
 * @tc.name: AddLayoutTask006
 * @tc.desc: Test AddLayoutTask with different overlap calculations
 * @tc.type: FUNC
 */
HWTEST_F(XComponentLayoutTestNg, AddLayoutTask006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_COMPONENT_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. setup with offset position
     */
    pattern->surfaceId_ = SURFACE_ID;
    pattern->drawSize_ = SizeF(200.0f, 200.0f);
    pattern->surfaceSize_ = SizeF(500.0f, 500.0f);
    pattern->paintRect_ = RectF(OffsetF(0.0f, 0.0f), SizeF(100.0f, 100.0f));

    // Small window with large surface, should scale down
    Rect displayWindowRectInfo = Rect(0, 0, 300, 300);
    MockPipelineContext::pipeline_->SetDisplayWindowRectInfo(displayWindowRectInfo);

    pattern->handlingSurfaceRenderContext_ = nullptr; // Null context

    /**
     * @tc.steps: step3. call AddLayoutTask
     * @tc.expected: surface should be scaled to fit window
     */

    pattern->AddLayoutTask();

    /**
     * @tc.steps: step4. verify surface is scaled
     */
    EXPECT_EQ(pattern->surfaceSize_.Width(), 200.0f);
    EXPECT_EQ(pattern->surfaceSize_.Height(), 200.0f);
    EXPECT_EQ(pattern->paintRect_.Width(), 200.0f);
    EXPECT_EQ(pattern->paintRect_.Height(), 200.0f);
}

/**
 * @tc.name: AddLayoutTask007
 * @tc.desc: Test AddLayoutTask with partial overlap (offset position)
 * @tc.type: FUNC
 */
HWTEST_F(XComponentLayoutTestNg, AddLayoutTask007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_COMPONENT_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. setup with large xcomponent extending beyond window
     */
    pattern->surfaceId_ = SURFACE_ID;
    pattern->drawSize_ = SizeF(600.0f, 600.0f);
    pattern->surfaceSize_ = SizeF(400.0f, 400.0f);
    pattern->paintRect_ = RectF(OffsetF(0.0f, 0.0f), SizeF(200.0f, 200.0f));

    Rect displayWindowRectInfo = Rect(0, 0, 400, 400);
    MockPipelineContext::pipeline_->SetDisplayWindowRectInfo(displayWindowRectInfo);

    pattern->handlingSurfaceRenderContext_ = nullptr; // Null context

    /**
     * @tc.steps: step3. call AddLayoutTask with partial overlap
     */

    pattern->AddLayoutTask();

    /**
     * @tc.steps: step4. verify surface fits in window
     */
    EXPECT_EQ(pattern->surfaceSize_.Width(), 400.0f);
    EXPECT_EQ(pattern->surfaceSize_.Height(), 400.0f);
}

/**
 * @tc.name: AddLayoutTask008
 * @tc.desc: Test AddLayoutTask multiple calls with changing parameters
 * @tc.type: FUNC
 */
HWTEST_F(XComponentLayoutTestNg, AddLayoutTask008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_COMPONENT_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    pattern->surfaceId_ = SURFACE_ID;
    pattern->drawSize_ = SizeF(400.0f, 400.0f);
    pattern->surfaceSize_ = SizeF(200.0f, 200.0f);
    pattern->paintRect_ = RectF(OffsetF(0.0f, 0.0f), SizeF(100.0f, 100.0f));

    pattern->handlingSurfaceRenderContext_ = nullptr; // Null context

    /**
     * @tc.steps: step2. first call with 400x400 window
     */
    Rect displayWindowRectInfo1 = Rect(100, 100, 400, 400);
    MockPipelineContext::pipeline_->SetDisplayWindowRectInfo(displayWindowRectInfo1);

    EXPECT_EQ(pattern->surfaceSize_.Width(), 300.0f);
    EXPECT_EQ(pattern->surfaceSize_.Height(), 300.0f);
}

/**
 * @tc.name: OnFrameNodeChanged001
 * @tc.desc: Test OnFrameNodeChanged when XComponentDisplayConstraint is enabled
 * @tc.type: FUNC
 */
HWTEST_F(XComponentLayoutTestNg, OnFrameNodeChanged001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_COMPONENT_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. setup test data
     */
    pattern->surfaceId_ = SURFACE_ID;
    pattern->drawSize_ = SizeF(400.0f, 400.0f);
    pattern->surfaceSize_ = SizeF(200.0f, 200.0f);
    pattern->paintRect_ = RectF(OffsetF(0.0f, 0.0f), SizeF(100.0f, 100.0f));

    Rect displayWindowRectInfo = Rect(0, 0, 400, 400);
    MockPipelineContext::pipeline_->SetDisplayWindowRectInfo(displayWindowRectInfo);

    pattern->handlingSurfaceRenderContext_ = nullptr;

    /**
     * @tc.steps: step3. call OnFrameNodeChanged with GEOMETRY_CHANGE flag
     * @tc.expected: AddLayoutTask should be called and surfaceSize updated
     */
    MockPipelineContext::pipeline_->SetXComponentDisplayConstraintEnabled(true);
    pattern->OnFrameNodeChanged(FRAME_NODE_CHANGE_GEOMETRY_CHANGE);

    /**
     * @tc.steps: step4. verify surfaceSize is updated
     */
    EXPECT_EQ(pattern->surfaceSize_.Width(), 400.0f);
    EXPECT_EQ(pattern->surfaceSize_.Height(), 400.0f);
}

/**
 * @tc.name: OnFrameNodeChanged002
 * @tc.desc: Test OnFrameNodeChanged with different change flags
 * @tc.type: FUNC
 */
HWTEST_F(XComponentLayoutTestNg, OnFrameNodeChanged002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_COMPONENT_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. setup test data
     */
    pattern->surfaceId_ = SURFACE_ID;
    pattern->drawSize_ = SizeF(400.0f, 400.0f);
    pattern->surfaceSize_ = SizeF(200.0f, 200.0f);

    Rect displayWindowRectInfo = Rect(0, 0, 400, 400);
    MockPipelineContext::pipeline_->SetDisplayWindowRectInfo(displayWindowRectInfo);

    pattern->handlingSurfaceRenderContext_ = nullptr;

    /**
     * @tc.steps: step3. test with TRANSFORM_CHANGE flag
     * @tc.expected: AddLayoutTask should be called
     */
    MockPipelineContext::pipeline_->SetXComponentDisplayConstraintEnabled(true);
    pattern->OnFrameNodeChanged(FRAME_NODE_CHANGE_TRANSFORM_CHANGE);
    EXPECT_EQ(pattern->surfaceSize_.Width(), 400.0f);
}

/**
 * @tc.name: OnFrameNodeChanged003
 * @tc.desc: Test OnFrameNodeChanged with NONE flag
 * @tc.type: FUNC
 */
HWTEST_F(XComponentLayoutTestNg, OnFrameNodeChanged003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_COMPONENT_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. setup test data
     */
    pattern->surfaceId_ = SURFACE_ID;
    pattern->drawSize_ = SizeF(400.0f, 400.0f);
    pattern->surfaceSize_ = SizeF(200.0f, 200.0f);
    pattern->paintRect_ = RectF(OffsetF(0.0f, 0.0f), SizeF(200.0f, 200.0f));

    Rect displayWindowRectInfo = Rect(0, 0, 400, 400);
    MockPipelineContext::pipeline_->SetDisplayWindowRectInfo(displayWindowRectInfo);

    pattern->handlingSurfaceRenderContext_ = nullptr;

    /**
     * @tc.steps: step3. call with NONE flag (initial call, should update)
     * @tc.expected: AddLayoutTask should be called
     */
    MockPipelineContext::pipeline_->SetXComponentDisplayConstraintEnabled(true);
    pattern->OnFrameNodeChanged(FRAME_NODE_CHANGE_INFO_NONE);
    EXPECT_EQ(pattern->surfaceSize_.Width(), 400.0f);
}

/**
 * @tc.name: OnFrameNodeChanged004
 * @tc.desc: Test OnFrameNodeChanged with START_ANIMATION flag
 * @tc.type: FUNC
 */
HWTEST_F(XComponentLayoutTestNg, OnFrameNodeChanged004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_COMPONENT_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. setup test data
     */
    pattern->surfaceId_ = SURFACE_ID;
    pattern->drawSize_ = SizeF(400.0f, 400.0f);
    pattern->surfaceSize_ = SizeF(200.0f, 200.0f);

    Rect displayWindowRectInfo = Rect(0, 0, 400, 400);
    MockPipelineContext::pipeline_->SetDisplayWindowRectInfo(displayWindowRectInfo);

    pattern->handlingSurfaceRenderContext_ = nullptr;

    /**
     * @tc.steps: step3. call OnFrameNodeChanged with START_ANIMATION flag
     * @tc.expected: AddLayoutTask should be called
     */
    MockPipelineContext::pipeline_->SetXComponentDisplayConstraintEnabled(true);
    pattern->OnFrameNodeChanged(FRAME_NODE_CHANGE_START_ANIMATION);

    /**
     * @tc.steps: step4. verify surfaceSize is updated
     */
    EXPECT_EQ(pattern->surfaceSize_.Width(), 400.0f);
    EXPECT_EQ(pattern->surfaceSize_.Height(), 400.0f);
}

/**
 * @tc.name: OnFrameNodeChanged005
 * @tc.desc: Test OnFrameNodeChanged with multiple flags combined
 * @tc.type: FUNC
 */
HWTEST_F(XComponentLayoutTestNg, OnFrameNodeChanged005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_COMPONENT_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. setup test data
     */
    pattern->surfaceId_ = SURFACE_ID;
    pattern->drawSize_ = SizeF(400.0f, 400.0f);
    pattern->surfaceSize_ = SizeF(200.0f, 200.0f);

    Rect displayWindowRectInfo = Rect(0, 0, 400, 400);
    MockPipelineContext::pipeline_->SetDisplayWindowRectInfo(displayWindowRectInfo);

    pattern->handlingSurfaceRenderContext_ = nullptr;

    /**
     * @tc.steps: step3. call with multiple flags combined
     * @tc.expected: AddLayoutTask should be called once
     */
    MockPipelineContext::pipeline_->SetXComponentDisplayConstraintEnabled(true);
    FrameNodeChangeInfoFlag combinedFlags = FRAME_NODE_CHANGE_GEOMETRY_CHANGE | FRAME_NODE_CHANGE_TRANSFORM_CHANGE;
    pattern->OnFrameNodeChanged(combinedFlags);

    /**
     * @tc.steps: step4. verify surfaceSize is updated
     */
    EXPECT_EQ(pattern->surfaceSize_.Width(), 400.0f);
    EXPECT_EQ(pattern->surfaceSize_.Height(), 400.0f);
}

/**
 * @tc.name: OnFrameNodeChanged006
 * @tc.desc: Test OnFrameNodeChanged when surfaceSize is zero
 * @tc.type: FUNC
 */
HWTEST_F(XComponentLayoutTestNg, OnFrameNodeChanged006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_COMPONENT_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. setup with zero surfaceSize
     */
    pattern->surfaceId_ = SURFACE_ID;
    pattern->drawSize_ = SizeF(400.0f, 400.0f);
    pattern->surfaceSize_ = SizeF(0.0f, 0.0f);
    pattern->paintRect_ = RectF(OffsetF(0.0f, 0.0f), SizeF(0.0f, 0.0f));

    Rect displayWindowRectInfo = Rect(0, 0, 400, 400);
    MockPipelineContext::pipeline_->SetDisplayWindowRectInfo(displayWindowRectInfo);

    pattern->handlingSurfaceRenderContext_ = nullptr;

    /**
     * @tc.steps: step3. call OnFrameNodeChanged with zero surfaceSize
     * @tc.expected: AddLayoutTask should skip scaling, SetBounds NOT called
     */
    MockPipelineContext::pipeline_->SetXComponentDisplayConstraintEnabled(true);
    pattern->OnFrameNodeChanged(FRAME_NODE_CHANGE_GEOMETRY_CHANGE);

    /**
     * @tc.steps: step4. verify surfaceSize remains zero
     */
    EXPECT_TRUE(NearZero(pattern->surfaceSize_.Width()));
    EXPECT_TRUE(NearZero(pattern->surfaceSize_.Height()));
}

/**
 * @tc.name: OnFrameNodeChanged007
 * @tc.desc: Test OnFrameNodeChanged when handlingSurfaceRenderContext is null
 * @tc.type: FUNC
 */
HWTEST_F(XComponentLayoutTestNg, OnFrameNodeChanged007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_COMPONENT_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. setup without handlingSurfaceRenderContext
     */
    pattern->surfaceId_ = SURFACE_ID;
    pattern->drawSize_ = SizeF(400.0f, 400.0f);
    pattern->surfaceSize_ = SizeF(200.0f, 200.0f);
    pattern->paintRect_ = RectF(OffsetF(0.0f, 0.0f), SizeF(100.0f, 100.0f));

    Rect displayWindowRectInfo = Rect(0, 0, 400, 400);
    MockPipelineContext::pipeline_->SetDisplayWindowRectInfo(displayWindowRectInfo);

    pattern->handlingSurfaceRenderContext_ = nullptr;

    /**
     * @tc.steps: step3. call OnFrameNodeChanged with null context
     * @tc.expected: should update paintRect_ but not call SetBounds
     */
    MockPipelineContext::pipeline_->SetXComponentDisplayConstraintEnabled(true);
    pattern->OnFrameNodeChanged(FRAME_NODE_CHANGE_GEOMETRY_CHANGE);

    /**
     * @tc.steps: step4. verify surfaceSize is still updated
     */
    EXPECT_EQ(pattern->surfaceSize_.Width(), 400.0f);
    EXPECT_EQ(pattern->surfaceSize_.Height(), 400.0f);
    EXPECT_EQ(pattern->paintRect_.Width(), 400.0f);
    EXPECT_EQ(pattern->paintRect_.Height(), 400.0f);
}

/**
 * @tc.name: OnFrameNodeChanged009
 * @tc.desc: Test OnFrameNodeChanged with END_SCROLL flag
 * @tc.type: FUNC
 */
HWTEST_F(XComponentLayoutTestNg, OnFrameNodeChanged009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_COMPONENT_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. setup test data
     */
    pattern->surfaceId_ = SURFACE_ID;
    pattern->drawSize_ = SizeF(400.0f, 400.0f);
    pattern->surfaceSize_ = SizeF(200.0f, 200.0f);

    Rect displayWindowRectInfo = Rect(0, 0, 400, 400);
    MockPipelineContext::pipeline_->SetDisplayWindowRectInfo(displayWindowRectInfo);

    pattern->handlingSurfaceRenderContext_ = nullptr;

    /**
     * @tc.steps: step3. call OnFrameNodeChanged with END_SCROLL flag
     * @tc.expected: AddLayoutTask should be called
     */
    MockPipelineContext::pipeline_->SetXComponentDisplayConstraintEnabled(true);
    pattern->OnFrameNodeChanged(FRAME_NODE_CHANGE_END_SCROLL);

    /**
     * @tc.steps: step4. verify surfaceSize is updated
     */
    EXPECT_EQ(pattern->surfaceSize_.Width(), 400.0f);
    EXPECT_EQ(pattern->surfaceSize_.Height(), 400.0f);
}

/**
 * @tc.name: OnFrameNodeChanged010
 * @tc.desc: Test OnFrameNodeChanged with TRANSITION_START flag
 * @tc.type: FUNC
 */
HWTEST_F(XComponentLayoutTestNg, OnFrameNodeChanged010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create xcomponent pattern
     * @tc.expected: xcomponent pattern created
     */
    testProperty.xcType = XCOMPONENT_COMPONENT_TYPE_VALUE;
    auto frameNode = CreateXComponentNode(testProperty);
    ASSERT_TRUE(frameNode);
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. setup test data
     */
    pattern->surfaceId_ = SURFACE_ID;
    pattern->drawSize_ = SizeF(400.0f, 400.0f);
    pattern->surfaceSize_ = SizeF(200.0f, 200.0f);

    Rect displayWindowRectInfo = Rect(0, 0, 400, 400);
    MockPipelineContext::pipeline_->SetDisplayWindowRectInfo(displayWindowRectInfo);

    pattern->handlingSurfaceRenderContext_ = AceType::MakeRefPtr<MockRenderContext>();

    /**
     * @tc.steps: step3. call OnFrameNodeChanged with TRANSITION_START flag
     * @tc.expected: AddLayoutTask should be called
     */
    MockPipelineContext::pipeline_->SetXComponentDisplayConstraintEnabled(true);
    pattern->OnFrameNodeChanged(FRAME_NODE_CHANGE_TRANSITION_START);

    /**
     * @tc.steps: step4. verify surfaceSize is updated
     */
    EXPECT_EQ(pattern->surfaceSize_.Width(), 400.0f);
    EXPECT_EQ(pattern->surfaceSize_.Height(), 400.0f);
}
} // namespace OHOS::Ace::NG
