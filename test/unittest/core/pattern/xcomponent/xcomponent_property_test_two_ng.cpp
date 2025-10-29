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

#include <cstddef>
#include <optional>
#include <unistd.h>
#include <vector>

#include "gtest/gtest.h"
#include "base/geometry/ng/size_t.h"

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
const std::string CHECK_KEY = "HI";
const std::string XCOMPONENT_ID = "xcomponent";
const std::string XCOMPONENT_LIBRARY_NAME = "native_render";
const std::string XCOMPONENT_LIBRARY_NAME_NEW = "native_render_new";
const std::string XCOMPONENT_SO_PATH = "com.example.xcomponentmultihap/entry";
const std::string SURFACE_ID = "2430951489577";
constexpr XComponentType XCOMPONENT_SURFACE_TYPE_VALUE = XComponentType::SURFACE;
constexpr XComponentType XCOMPONENT_COMPONENT_TYPE_VALUE = XComponentType::COMPONENT;
constexpr XComponentType XCOMPONENT_TEXTURE_TYPE_VALUE = XComponentType::TEXTURE;
constexpr XComponentType XCOMPONENT_NODE_TYPE_VALUE = XComponentType::NODE;
const float MAX_WIDTH = 400.0f;
const float MAX_HEIGHT = 400.0f;
const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
const RenderFit RENDER_FIT = RenderFit::BOTTOM_RIGHT;
TestProperty testProperty;
} // namespace

class XComponentPropertyTestTwoNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    static RefPtr<FrameNode> CreateXComponentNode(TestProperty& testProperty);
};

void XComponentPropertyTestTwoNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    testProperty.xcId = XCOMPONENT_ID;
    testProperty.libraryName = XCOMPONENT_LIBRARY_NAME;
    testProperty.soPath = XCOMPONENT_SO_PATH;
}

void XComponentPropertyTestTwoNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> XComponentPropertyTestTwoNg::CreateXComponentNode(TestProperty& testProperty)
{
    auto xcId = testProperty.xcId;
    auto xcType = testProperty.xcType.value();
    auto libraryName = testProperty.libraryName;
    auto xcomponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG().Create(xcId, xcType, libraryName, xcomponentController);

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
 * @tc.name: XComponentModelNGTest038
 * @tc.desc: Test XComponentModelNG SetImageAIOptions, type = XComponentType::SURFACE
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestTwoNg, XComponentModelNGTest038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ComponentController.
     *            case: type = XComponentType::SURFACE
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_SURFACE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);
    /**
     * @tc.steps: step2. call SetImageAIOptions
     * @tc.expected: pattern->imageAnalyzerManager_ != nullptr
     */
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    xComponent.SetImageAIOptions(nullptr);
    EXPECT_NE(pattern->imageAnalyzerManager_, nullptr);
}

/**
 * @tc.name: XComponentModelNGTest039
 * @tc.desc: Test XComponentModelNG SetImageAIOptions, type = XComponentType::COMPONENT
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestTwoNg, XComponentModelNGTest039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ComponentController.
     *            case: type = XComponentType::COMPONENT
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_COMPONENT_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);

    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);
    /**
     * @tc.steps: step2. call SetImageAIOptions
     * @tc.expected: pattern->imageAnalyzerManager_ == nullptr
     */
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    xComponent.SetImageAIOptions(nullptr);
    EXPECT_EQ(pattern->imageAnalyzerManager_, nullptr);
}

/**
 * @tc.name: XComponentModelNGTest040
 * @tc.desc: Test XComponentModelNG SetImageAIOptions, type = XComponentType::NODE
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestTwoNg, XComponentModelNGTest040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ComponentController.
     *            case: type = XComponentType::NODE
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_NODE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);

    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);
    /**
     * @tc.steps: step2. call SetImageAIOptions
     * @tc.expected: pattern->imageAnalyzerManager_ == nullptr
     */
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    xComponent.SetImageAIOptions(nullptr);
    EXPECT_EQ(pattern->imageAnalyzerManager_, nullptr);
}

/**
 * @tc.name: XComponentModelNGTest041
 * @tc.desc: Test XComponentModelNG SetXComponentLibraryname
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestTwoNg, XComponentModelNGTest041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a XComponentModelNG
     */
    const std::shared_ptr<InnerXComponentController> xComponentController;
    XComponentModelNG xComponent;
    /**
     * @tc.steps: step2. call Create and SetSoPath
     *            case: id == XCOMPONENT_ID
     * @tc.expected: the properties are expected
     */
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_SURFACE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);

    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);
    /**
     * @tc.steps: step3. call SetXComponentLibraryname
     *            case: libraryname == XCOMPONENT_LIBRARY_NAME_NEW
     * @tc.expected: result == XCOMPONENT_LIBRARY_NAME_NEW
     */
    XComponentModelNG::SetXComponentLibraryname(Referenced::RawPtr(frameNode), XCOMPONENT_LIBRARY_NAME_NEW);
    auto result = xComponent.GetLibraryName();
    EXPECT_EQ(result, XCOMPONENT_LIBRARY_NAME_NEW);
}

/**
 * @tc.name: XComponentModelNGLifeCycleCallbackTest043
 * @tc.desc: Test XComponentModelNG controller lifecycle callback, type = XComponentType::COMPONENT
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestTwoNg, XComponentModelNGLifeCycleCallbackTest043, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set surface life cycle callback
     */
    std::string onSurfaceCreatedSurfaceId = "";
    std::string onSurfaceChangedSurfaceId = "";
    std::string onSurfaceDestroyedSurfaceId = "";
    auto onSurfaceCreated = [&onSurfaceCreatedSurfaceId](const std::string& surfaceId, const std::string& xcId) {
        onSurfaceCreatedSurfaceId = surfaceId;
    };
    auto onSurfaceChanged = [&onSurfaceChangedSurfaceId](const std::string& surfaceId, const RectF& /* rect */) {
        onSurfaceChangedSurfaceId = surfaceId;
    };
    auto onSurfaceDestroyed = [&onSurfaceDestroyedSurfaceId](const std::string& surfaceId, const std::string& xcId) {
        onSurfaceDestroyedSurfaceId = surfaceId;
    };
    /**
     * @tc.steps: step2. call CreateFrameNode
     *            case: type = XComponentType::COMPONENT
     * @tc.expected: xcomponent frameNode create successfully
     */
    const std::shared_ptr<InnerXComponentController> xComponentController;
    XComponentModelNG xComponent;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        xComponent.CreateFrameNode(nodeId, XCOMPONENT_ID, XCOMPONENT_COMPONENT_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME);
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);
    /**
     * @tc.steps: step3. call SetControllerOnCreated, SetControllerOnChanged and SetControllerOnDestroyed
     * @tc.expected: onSurfaceCreated & onSurfaceChanged has not called
     */
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->surfaceId_ = SURFACE_ID;
    XComponentModelNG::SetControllerOnCreated(Referenced::RawPtr(frameNode), std::move(onSurfaceCreated));
    XComponentModelNG::SetControllerOnChanged(Referenced::RawPtr(frameNode), std::move(onSurfaceChanged));
    XComponentModelNG::SetControllerOnDestroyed(Referenced::RawPtr(frameNode), std::move(onSurfaceDestroyed));
    DirtySwapConfig config;
    auto xComponentLayoutAlgorithm = AceType::MakeRefPtr<XComponentLayoutAlgorithm>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(MAX_SIZE);
    geometryNode->SetContentSize(MAX_SIZE);
    frameNode->geometryNode_ = geometryNode;
    pattern->BeforeSyncGeometryProperties(config);
    EXPECT_STREQ("", onSurfaceCreatedSurfaceId.c_str());
    EXPECT_STREQ("", onSurfaceChangedSurfaceId.c_str());
    /**
     * @tc.steps: step4. call OnDetachFromFrameNode
     * @tc.expected: onSurfaceDestroyed has not called
     */
    pattern->OnDetachFromFrameNode(AceType::RawPtr(frameNode));
    EXPECT_STREQ("", onSurfaceDestroyedSurfaceId.c_str());
}

/**
 * @tc.name: XComponentModelNGLifeCycleCallbackTest044
 * @tc.desc: Test XComponentModelNG controller lifecycle callback, type = XComponentType::NODE
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestTwoNg, XComponentModelNGLifeCycleCallbackTest044, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set surface life cycle callback
     */
    std::string onSurfaceCreatedSurfaceId = "";
    std::string onSurfaceChangedSurfaceId = "";
    std::string onSurfaceDestroyedSurfaceId = "";
    auto onSurfaceCreated = [&onSurfaceCreatedSurfaceId](const std::string& surfaceId, const std::string& xcId) {
        onSurfaceCreatedSurfaceId = surfaceId;
    };
    auto onSurfaceChanged = [&onSurfaceChangedSurfaceId](const std::string& surfaceId, const RectF& /* rect */) {
        onSurfaceChangedSurfaceId = surfaceId;
    };
    auto onSurfaceDestroyed = [&onSurfaceDestroyedSurfaceId](const std::string& surfaceId, const std::string& xcId) {
        onSurfaceDestroyedSurfaceId = surfaceId;
    };
    /**
     * @tc.steps: step2. call CreateFrameNode
     *            case: type = XComponentType::NODE
     * @tc.expected: xcomponent frameNode create successfully
     */
    const std::shared_ptr<InnerXComponentController> xComponentController;
    XComponentModelNG xComponent;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        xComponent.CreateFrameNode(nodeId, XCOMPONENT_ID, XCOMPONENT_NODE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME);
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);
    /**
     * @tc.steps: step3. call SetControllerOnCreated, SetControllerOnChanged and SetControllerOnDestroyed
     * @tc.expected: onSurfaceCreated & onSurfaceChanged has not called
     */
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    pattern->surfaceId_ = SURFACE_ID;
    XComponentModelNG::SetControllerOnCreated(Referenced::RawPtr(frameNode), std::move(onSurfaceCreated));
    XComponentModelNG::SetControllerOnChanged(Referenced::RawPtr(frameNode), std::move(onSurfaceChanged));
    XComponentModelNG::SetControllerOnDestroyed(Referenced::RawPtr(frameNode), std::move(onSurfaceDestroyed));
    DirtySwapConfig config;
    auto xComponentLayoutAlgorithm = AceType::MakeRefPtr<XComponentLayoutAlgorithm>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(MAX_SIZE);
    geometryNode->SetContentSize(MAX_SIZE);
    frameNode->geometryNode_ = geometryNode;
    pattern->BeforeSyncGeometryProperties(config);
    EXPECT_STREQ("", onSurfaceCreatedSurfaceId.c_str());
    EXPECT_STREQ("", onSurfaceChangedSurfaceId.c_str());
    /**
     * @tc.steps: step4. call OnDetachFromFrameNode
     * @tc.expected: onSurfaceDestroyed has not called
     */
    pattern->OnDetachFromFrameNode(AceType::RawPtr(frameNode));
    EXPECT_STREQ("", onSurfaceDestroyedSurfaceId.c_str());
}

/**
 * @tc.name: XComponentModelNGDetachCallbackTest045
 * @tc.desc: Test XComponentModelNG SetDetachCallback callback
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestTwoNg, XComponentModelNGDetachCallbackTest045, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set onDetach callback
     */
    std::string onDetachKey;
    auto onDetach = [&onDetachKey](const std::string& /* xcomponentId */) { onDetachKey = CHECK_KEY; };

    /**
     * @tc.steps: step2. construct a XComponentModelNG
     */
    const std::shared_ptr<InnerXComponentController> xComponentController;
    XComponentModelNG xComponent;

    /**
     * @tc.steps: step3. call Create, SetSoPath and SetDetachCallback
     *            case: type = XComponentType::NODE
     * @tc.expected: the properties are expected
     */
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_NODE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);
    XComponentModelNG::SetDetachCallback(Referenced::RawPtr(frameNode), std::move(onDetach));
    /**
     * @tc.steps: step4. call FireDetachEvent
     * @tc.expected: onDetachKey != CHECK_KEY
     */
    auto xComponentEventHub = frameNode->GetEventHub<XComponentEventHub>();
    ASSERT_TRUE(xComponentEventHub);
    xComponentEventHub->FireDetachEvent(XCOMPONENT_ID);
    EXPECT_FALSE(onDetachKey == CHECK_KEY);
    /**
     * @tc.steps: step5. call SetXComponentType
     *            case: type = XComponentType::COMPONENT
     * @tc.expected: onDetachKey != CHECK_KEY
     */
    onDetachKey.clear();
    XComponentModelNG::SetXComponentType(Referenced::RawPtr(frameNode), XCOMPONENT_COMPONENT_TYPE_VALUE);
    XComponentModelNG::SetDetachCallback(Referenced::RawPtr(frameNode), std::move(onDetach));
    xComponentEventHub->FireDetachEvent(XCOMPONENT_ID);
    EXPECT_FALSE(onDetachKey == CHECK_KEY);
    /**
     * @tc.steps: step6. call SetXComponentType
     *            case: type = XComponentType::SURFACE
     * @tc.expected: onDetachKey == CHECK_KEY
     */
    onDetachKey.clear();
    XComponentModelNG::SetXComponentType(Referenced::RawPtr(frameNode), XCOMPONENT_SURFACE_TYPE_VALUE);
    XComponentModelNG::SetDetachCallback(Referenced::RawPtr(frameNode), std::move(onDetach));
    xComponentEventHub->FireDetachEvent(XCOMPONENT_ID);
    EXPECT_TRUE(onDetachKey == CHECK_KEY);
}

/**
 * @tc.name: XComponentModelNGTest046
 * @tc.desc: Test XComponentModelNG SetImageAIOptions, type = XComponentType::SURFACE
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestTwoNg, XComponentModelNGTest046, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ComponentController.
     *            case: type = XComponentType::SURFACE
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_SURFACE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);

    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);
    /**
     * @tc.steps: step2. call SetImageAIOptions
     * @tc.expected: pattern->imageAnalyzerManager_ != nullptr
     */
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    XComponentModelNG::SetImageAIOptions(Referenced::RawPtr(frameNode), nullptr);
    EXPECT_NE(pattern->imageAnalyzerManager_, nullptr);
}

/**
 * @tc.name: XComponentModelNGTest047
 * @tc.desc: Test XComponentModelNG SetImageAIOptions, type = XComponentType::COMPONENT
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestTwoNg, XComponentModelNGTest047, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ComponentController.
     *            case: type = XComponentType::COMPONENT
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_COMPONENT_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);

    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);
    /**
     * @tc.steps: step2. call SetImageAIOptions
     * @tc.expected: pattern->imageAnalyzerManager_ == nullptr
     */
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    XComponentModelNG::SetImageAIOptions(Referenced::RawPtr(frameNode), nullptr);
    EXPECT_EQ(pattern->imageAnalyzerManager_, nullptr);
}

/**
 * @tc.name: XComponentModelNGTest048
 * @tc.desc: Test XComponentModelNG SetImageAIOptions, type = XComponentType::NODE
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestTwoNg, XComponentModelNGTest048, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ComponentController.
     *            case: type = XComponentType::NODE
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_NODE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);
    /**
     * @tc.steps: step2. call SetImageAIOptions
     * @tc.expected: pattern->imageAnalyzerManager_ == nullptr
     */
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    XComponentModelNG::SetImageAIOptions(Referenced::RawPtr(frameNode), nullptr);
    EXPECT_EQ(pattern->imageAnalyzerManager_, nullptr);
}

/**
 * @tc.name: XComponentModelNGTest049
 * @tc.desc: Test XComponentModelNG SetRenderFit, type = XComponentType::SURFACE
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestTwoNg, XComponentModelNGTest049, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ComponentController.
     *            case: type = XComponentType::SURFACE
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_SURFACE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);
    /**
     * @tc.steps: step2. call SetRenderFit
     *            case: renderFit == RenderFit::BOTTOM_RIGHT
     * @tc.expected: handlingSurfaceRenderContext_->SetRenderFit(renderFit) is called
     */
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->handlingSurfaceRenderContext_),
        SetRenderFit(RENDER_FIT)).Times(1).WillOnce(Return()).RetiresOnSaturation();
    xComponent.SetRenderFit(RENDER_FIT);
    EXPECT_CALL(*AceType::DynamicCast<MockRenderContext>(pattern->handlingSurfaceRenderContext_),
        SetRenderFit(RENDER_FIT)).Times(1).WillOnce(Return()).RetiresOnSaturation();
    XComponentModelNG::SetRenderFit(Referenced::RawPtr(frameNode), RENDER_FIT);
}

/**
 * @tc.name: XComponentModelNGTest050
 * @tc.desc: Test XComponentModelNG SetRenderFit, type != XComponentType::SURFACE
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestTwoNg, XComponentModelNGTest050, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ComponentController.
     *            case: type = XComponentType::TEXTURE
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_TEXTURE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);
    /**
     * @tc.steps: step2. call SetRenderFit
     *            case: renderFit == RenderFit::BOTTOM_RIGHT
     * @tc.expected: handlingSurfaceRenderContext_->SetRenderFit(renderFit) is not called
     */
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(pattern);
    xComponent.SetRenderFit(RENDER_FIT);
    EXPECT_EQ(pattern->handlingSurfaceRenderContext_, nullptr);
}

/**
 * @tc.name: XComponentModelNGTest051
 * @tc.desc: Test XComponentModelNG SetPattern
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestTwoNg, XComponentModelNGTest051, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ComponentController.
     *            case: type = XComponentType::SURFACE
     * @tc.expected: xcomponent frameNode create successfully
     */
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_SURFACE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::XCOMPONENT_ETS_TAG);
    /**
     * @tc.steps: step2. call SetPattern when pattern is null and isOpaque is true
     * @tc.expected: isOpaque in pattern is false
     */
    auto pattern = frameNode->GetPattern<XComponentPattern>();
    xComponentController->isOpaque_ = true;
    ASSERT_TRUE(pattern);
    xComponentController->SetPattern(nullptr);
    EXPECT_FALSE(pattern->isOpaque_);
    /**
     * @tc.steps: step3. call SetPattern when pattern is not null and isOpaque is true
     * @tc.expected: isOpaque in pattern is true
     */
    ASSERT_TRUE(pattern);
    xComponentController->SetPattern(pattern);
    EXPECT_TRUE(pattern->isOpaque_);
}

/**
 * @tc.name: XComponentNodeTypeToStringTest
 * @tc.desc: Test XComponentNodeTypeToString Func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestTwoNg, XComponentNodeTypeToStringTest, TestSize.Level1)
{
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_TEXTURE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(frameNode);
    auto xComponentPattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(xComponentPattern);
    EXPECT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    EXPECT_EQ(xComponentPattern->XComponentNodeTypeToString(XComponentNodeType::TYPE_NODE), "type_node");
    EXPECT_EQ(xComponentPattern->XComponentNodeTypeToString(XComponentNodeType::UNKNOWN), "unknown");
    EXPECT_EQ(xComponentPattern->XComponentNodeTypeToString(XComponentNodeType::CNODE), "cnode");
    EXPECT_EQ(xComponentPattern->XComponentNodeTypeToString(XComponentNodeType::DECLARATIVE_NODE), "declarative_node");
    EXPECT_EQ(xComponentPattern->XComponentNodeTypeToString(static_cast<XComponentNodeType>(5)), "unknown");
}

/**
 * @tc.name: OnAccessibilityChildTreeRegisterTest001
 * @tc.desc: Test OnAccessibilityChildTreeRegister Func.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestTwoNg, OnAccessibilityChildTreeRegisterTest001, TestSize.Level1)
{
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_TEXTURE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(frameNode);
    auto xComponentPattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(xComponentPattern);
    EXPECT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    EXPECT_FALSE(xComponentPattern->OnAccessibilityChildTreeRegister(1, 0));
}

/**
 * @tc.name: OnAccessibilityChildTreeRegisterTest002
 * @tc.desc: Test OnAccessibilityChildTreeRegister Func set accessibilityProvider_ != nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentPropertyTestTwoNg, OnAccessibilityChildTreeRegisterTest002, TestSize.Level1)
{
    auto xComponentController = std::make_shared<XComponentControllerNG>();
    XComponentModelNG xComponent;
    xComponent.Create(XCOMPONENT_ID, XCOMPONENT_TEXTURE_TYPE_VALUE, XCOMPONENT_LIBRARY_NAME, xComponentController);
    xComponent.SetSoPath(XCOMPONENT_SO_PATH);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_TRUE(frameNode);
    auto xComponentPattern = frameNode->GetPattern<XComponentPattern>();
    ASSERT_TRUE(xComponentPattern);
    EXPECT_EQ(frameNode->GetTag(), V2::XCOMPONENT_ETS_TAG);
    xComponentPattern->accessibilityProvider_ = AceType::MakeRefPtr<XComponentAccessibilityProvider>(xComponentPattern);
    EXPECT_FALSE(xComponentPattern->OnAccessibilityChildTreeRegister(1, 0));
}
} // namespace OHOS::Ace::NG
