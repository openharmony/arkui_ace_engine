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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_media_player.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/render/mock_render_surface.h"
#include "test/mock/core/common/mock_image_analyzer_manager.h"
#include "test/mock/base/mock_pixel_map.h"
#include "test/mock/base/mock_task_executor.h"
#include "base/geometry/ng/size_t.h"
#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "base/resource/internal_resource.h"
#include "core/common/ai/image_analyzer_mgr.h"
#include "core/components/common/layout/constants.h"
#include "core/components/video/video_theme.h"
#include "core/components/video/video_utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/drag_event.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/image/image_source_info.h"

#include "component_ext/movingphoto/movingphoto_styles.h"
#include "component_ext/movingphoto/movingphoto_pattern.h"
#include "component_ext/movingphoto/movingphoto_node.h"
#include "component_ext/movingphoto/movingphoto_model_ng.h"
#include "component_ext/movingphoto/movingphoto_layout_property.h"
#include "component_ext/movingphoto/movingphoto_layout_algorithm.h"
#include "component_ext/movingphoto/movingphoto_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
struct TestProperty {
    std::optional<std::string> imageSrc;
    std::optional<bool> muted;
    std::optional<ImageFit> objectFit;
    std::optional<RefPtr<MovingPhotoController>> movingPhotoController;
};
namespace {
    constexpr bool MUTED_VALUE = false;
    constexpr ImageFit MOVINGPHOTO_IMAGE_FIT = ImageFit::COVER;
    constexpr uint32_t MOVINGPHOTO_CHILDREN_NUM = 2;
    const std::string MOVINGPHOTO_IMAGE_SRC = "common/video.mp4";
    constexpr float MAX_WIDTH = 400.0f;
    constexpr float MAX_HEIGHT = 400.0f;
    constexpr float MP_WIDTH = 300.0f;
    constexpr float MOVINGPHOTO_HEIGHT = 300.0f;
    constexpr float SCREEN_WIDTH_SMALL = 500.0f;
    constexpr float SCREEN_HEIGHT_SMALL = 1000.0f;
    const SizeF MAX_SIZE(MAX_WIDTH, MAX_HEIGHT);
    const SizeF MOVINGPHOTO_SIZE(MP_WIDTH, MOVINGPHOTO_HEIGHT);
    constexpr int32_t SLIDER_INDEX = 2;
    constexpr int32_t MOVINGPHOTO_NODE_ID_1 = 1;
    constexpr int32_t MOVINGPHOTO_NODE_ID_2 = 2;
    TestProperty g_testProperty;
}

class MovingphotoTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp();
    void TearDown() {}

protected:
    static RefPtr<FrameNode> CreateMovingPhotoNode(TestProperty& g_testProperty);
};

void MovingphotoTestNg::SetUpTestSuite()
{
    g_testProperty.imageSrc = MOVINGPHOTO_IMAGE_SRC;
    g_testProperty.muted = MUTED_VALUE;
    g_testProperty.objectFit = MOVINGPHOTO_IMAGE_FIT;
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    MockPipelineContext::GetCurrent()->rootNode_ = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    MockImageAnalyzerManager::SetUp();
}

void MovingphotoTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void MovingphotoTestNg::SetUp()
{
    ViewStackProcessor::GetInstance()->ClearStack();
}

RefPtr<FrameNode> MovingphotoTestNg::CreateMovingPhotoNode(TestProperty& g_testProperty)
{
    if (g_testProperty.movingPhotoController.has_value()) {
        MovingPhotoModelNG().Create(g_testProperty.movingPhotoController.value());
    } else {
        auto movingPhotoController = AceType::MakeRefPtr<MovingPhotoController>();
        MovingPhotoModelNG().Create(movingPhotoController);
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto movingPhotoPattern = AceType::DynamicCast<MovingPhotoPattern>(frameNode->GetPattern());
    CHECK_NULL_RETURN(movingPhotoPattern, nullptr);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(movingPhotoPattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(true));
    if (g_testProperty.imageSrc.has_value()) {
        MovingPhotoModelNG().SetImageSrc(g_testProperty.imageSrc.value());
    }
    if (g_testProperty.muted.has_value()) {
        MovingPhotoModelNG().SetMuted(g_testProperty.muted.value());
    }
    if (g_testProperty.objectFit.has_value()) {
        MovingPhotoModelNG().SetObjectFit(g_testProperty.objectFit.value());
    }
    auto element = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    return AceType::Claim(element);
}

/**
 * @tc.name: MovingPhotoModelNgTest001
 * @tc.desc: Create movingPhotoNode.
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoPropertyTest001, TestSize.Level1)
{
    auto frameNode = CreateMovingPhotoNode(g_testProperty);
    EXPECT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::MOVING_PHOTO_ETS_TAG);
}

/**
 * @tc.name: MovingPhotoModelNgTest002
 * @tc.desc: Create movingPhotoNode, and set its properties
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoPropertyTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto
     * @tc.expected: step1. Create MovingPhoto successfully
     */
    MovingPhotoModelNG movingphoto;
    auto movingPhotoController = AceType::MakeRefPtr<MovingPhotoController>();
    movingphoto.Create(movingPhotoController);
    auto frameNodeTemp = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    
    CHECK_NULL_VOID(frameNodeTemp);
    auto movingPhotoPatternTemp = AceType::DynamicCast<MovingPhotoPattern>(frameNodeTemp->GetPattern());
    CHECK_NULL_VOID(movingPhotoPatternTemp);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(movingPhotoPatternTemp->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(false));
    
    /**
     * @tc.steps: step2. set movingphoto properties
     * @tc.expected: step2. set movingphoto properties successfully
     */
    movingphoto.SetImageSrc(MOVINGPHOTO_IMAGE_SRC);
    movingphoto.SetMuted(MUTED_VALUE);
    movingphoto.SetObjectFit(MOVINGPHOTO_IMAGE_FIT);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::MOVING_PHOTO_ETS_TAG);
    auto movingPhotoLayoutProperty = frameNode->GetLayoutProperty<MovingPhotoLayoutProperty>();
    ASSERT_NE(movingPhotoLayoutProperty, nullptr);
    auto movingPhotoPattern = frameNode->GetPattern<MovingPhotoPattern>();
    ASSERT_NE(movingPhotoPattern, nullptr);

    EXPECT_EQ(movingPhotoPattern->GetMuted(), MUTED_VALUE);
    EXPECT_EQ(movingPhotoLayoutProperty->GetObjectFitValue(ImageFit::COVER), MOVINGPHOTO_IMAGE_FIT);
}

/**
 * @tc.name: MovingPhotoModelNgTest003
 * @tc.desc: Create movingPhotoNode, and set its callback functions.
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoEventTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto
     * @tc.expected: step1. Create MovingPhoto successfully
     */
    MovingPhotoModelNG movingphoto;
    auto movingPhotoController = AceType::MakeRefPtr<MovingPhotoController>();
    movingphoto.Create(movingPhotoController);

    auto frameNodeTemp = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNodeTemp);
    auto movingPhotoPatternTemp = AceType::DynamicCast<MovingPhotoPattern>(frameNodeTemp->GetPattern());
    CHECK_NULL_VOID(movingPhotoPatternTemp);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(movingPhotoPatternTemp->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(false));

    /**
     * @tc.steps: step2. set movingphoto event
     * @tc.expected: step2. get movingphoto event right
     */
    auto onStartEvent = []() {};
    movingphoto.SetOnStart(onStartEvent);
    auto onFinishEvent = []() {};
    movingphoto.SetOnFinish(onFinishEvent);
    auto onStopEvent = []() {};
    movingphoto.SetOnStop(onStopEvent);
    auto onErrorEvent = []() {};
    movingphoto.SetOnError(onErrorEvent);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::MOVING_PHOTO_ETS_TAG);
    auto movingPhotoEventHub = frameNode->GetEventHub<MovingPhotoEventHub>();
    EXPECT_TRUE(movingPhotoEventHub != nullptr);

    movingPhotoEventHub->FireStartEvent();
    auto onStart_ = movingPhotoEventHub->GetOnStart();
    EXPECT_TRUE(onStart_ != nullptr);
    movingPhotoEventHub->FireFinishEvent();
    auto onFinish_ = movingPhotoEventHub->GetOnFinish();
    EXPECT_TRUE(onFinish_!= nullptr);
    movingPhotoEventHub->FireStopEvent();
    auto onStop_ = movingPhotoEventHub->GetOnStop();
    EXPECT_TRUE(onStop_ != nullptr);
    movingPhotoEventHub->FireErrorEvent();
    auto onError_ = movingPhotoEventHub->GetOnError();
    EXPECT_TRUE(onError_ != nullptr);
}

/**
 * @tc.name: MovingPhotoLayoutAlgorithmTest004
 * @tc.desc: Create movingPhotoNode, and invoke its Algorithm function to calculate the content size
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoLayoutAlgorithmTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto
     * @tc.expected: step1. Create MovingPhoto successfully
     */
    MovingPhotoModelNG movingphoto;
    auto movingPhotoController = AceType::MakeRefPtr<MovingPhotoController>();
    movingphoto.Create(movingPhotoController);

    auto frameNodeTemp = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNodeTemp);
    auto movingPhotoPatternTemp = AceType::DynamicCast<MovingPhotoPattern>(frameNodeTemp->GetPattern());
    CHECK_NULL_VOID(movingPhotoPatternTemp);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(movingPhotoPatternTemp->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(false));

    auto frameNode =AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::MOVING_PHOTO_ETS_TAG);
    auto movingPhotoLayoutProperty = frameNode->GetLayoutProperty<MovingPhotoLayoutProperty>();
    ASSERT_NE(movingPhotoLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. Create LayoutWrapper and set videoLayoutAlgorithm.
     * @tc.expected: step2. Create LayoutWrapper and set videoLayoutAlgorithm successfully
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto movingPhotoPattern = frameNode->GetPattern<MovingPhotoPattern>();
    ASSERT_NE(movingPhotoPattern, nullptr);
    auto movingPhotoLayoutAlgorithm = movingPhotoPattern->CreateLayoutAlgorithm();
    EXPECT_NE(movingPhotoLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(movingPhotoLayoutAlgorithm));

    /**
     * @tc.steps: step3. videoLayoutAlgorithm MeasureContent
     * @tc.expected: step3. videoLayoutAlgorithm MeasureContent successfully
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = MAX_SIZE;
    auto movingPhotoDefaultSize =
        movingPhotoLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper).value_or(SizeF(0.0f, 0.0f));
    EXPECT_EQ(movingPhotoDefaultSize, MAX_SIZE);

    /**
     * @tc.steps: step4. videoLayoutAlgorithm MeasureContent different size
     * @tc.expected: step4. videoLayoutAlgorithm MeasureContent different size successfully
     */
    layoutConstraint.selfIdealSize.SetSize(MOVINGPHOTO_SIZE);
    auto movingPhotoSize1 =
        movingPhotoLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper).value_or(SizeF(0.0f, 0.0f));
    EXPECT_EQ(movingPhotoSize1, MOVINGPHOTO_SIZE);
}

/**
 * @tc.name: MovingPhotoLayoutAlgorithmTest005
 * @tc.desc: test its child/children layout algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoLayoutAlgorithmTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto
     * @tc.expected: step1. Create MovingPhoto successfully
     */
    MovingPhotoModelNG movingphoto;
    auto movingPhotoController = AceType::MakeRefPtr<MovingPhotoController>();
    movingphoto.Create(movingPhotoController);

    auto frameNodeTemp = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNodeTemp);
    auto movingPhotoPatternTemp = AceType::DynamicCast<MovingPhotoPattern>(frameNodeTemp->GetPattern());
    CHECK_NULL_VOID(movingPhotoPatternTemp);

    auto frameNode =AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::MOVING_PHOTO_ETS_TAG);
    auto movingPhotoLayoutProperty = frameNode->GetLayoutProperty<MovingPhotoLayoutProperty>();
    ASSERT_NE(movingPhotoLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. Create LayoutWrapper and set videoLayoutAlgorithm.
     * @tc.expected: step2. Create LayoutWrapper and set videoLayoutAlgorithm successfully
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto movingPhotoPattern = frameNode->GetPattern<MovingPhotoPattern>();
    ASSERT_NE(movingPhotoPattern, nullptr);
    auto movingPhotoLayoutAlgorithm = movingPhotoPattern->CreateLayoutAlgorithm();
    EXPECT_NE(movingPhotoLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(movingPhotoLayoutAlgorithm));

    /**
     * @tc.steps: step3. Set video source size and layout size.
     * @tc.expected: step3. Set video source size and layout size successfully
     */
    LayoutConstraintF layoutConstraint;
    movingPhotoLayoutProperty->UpdateVideoSize(MOVINGPHOTO_SIZE);
    layoutConstraint.selfIdealSize.SetSize(MOVINGPHOTO_SIZE);
    auto movingPhotoSize1 =
        movingPhotoLayoutAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper).value_or(SizeF(0.0f, 0.0f));
    EXPECT_EQ(movingPhotoSize1, MOVINGPHOTO_SIZE);
    layoutWrapper.GetGeometryNode()->SetContentSize(movingPhotoSize1);

    const auto& children = frameNode->GetChildren();
    for (const auto& child : children) {
        auto frameNodeChild = AceType::DynamicCast<FrameNode>(child);
        RefPtr<GeometryNode> geometryNodeChild = AceType::MakeRefPtr<GeometryNode>();
        auto childLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(AceType::WeakClaim(AceType::RawPtr(frameNodeChild)),
                geometryNodeChild, frameNodeChild->GetLayoutProperty());
        layoutWrapper.AppendChild(childLayoutWrapper);
    }
    movingPhotoLayoutAlgorithm->Measure(&layoutWrapper);
    movingPhotoLayoutAlgorithm->Layout(&layoutWrapper);

    auto layoutWrapperChildren = layoutWrapper.GetAllChildrenWithBuild();
    EXPECT_EQ(layoutWrapperChildren.size(), MOVINGPHOTO_CHILDREN_NUM);
    for (auto&& child : layoutWrapperChildren) {
        if (child->GetHostTag() == V2::IMAGE_ETS_TAG) {
            EXPECT_EQ(child->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(0.0, 0.0));
        } else if (child->GetHostTag() == V2::ROW_ETS_TAG) {
            float const controlBarHeight = 0.0;
            EXPECT_EQ(child->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(0.0, MP_WIDTH - controlBarHeight));
        }
    }
}

/**
 * @tc.name:  MovingPhotoPatternTest006
 * @tc.desc: Test OnAttachToFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg,  MovingPhotoPatternTest006, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    
    /**
     * @tc.steps: step1. Create MovingPhoto
     * @tc.expected: step1. Create MovingPhoto successfully
     */
    auto frameNode = CreateMovingPhotoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::MOVING_PHOTO_ETS_TAG);
    auto pattern = frameNode->GetPattern<MovingPhotoPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. check the children size. get video
     */
    auto children = frameNode->GetChildren();
    auto video = frameNode->GetChildAtIndex(0);
    ASSERT_NE(video, nullptr);

    /**
     * @tc.steps: step3. get image
     */
    auto image = frameNode->GetChildAtIndex(1);
    ASSERT_NE(image, nullptr);
}

/**
 * @tc.name: MovingPhotoPatternTest007
 * @tc.desc: Test updateMuted
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoPatternTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto
     * @tc.expected: step1. updateMuted
     */
    auto frameNode = CreateMovingPhotoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::MOVING_PHOTO_ETS_TAG);
    auto pattern = frameNode->GetPattern<MovingPhotoPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. update muted
     * @tc.expected: step2. getMuted status is equeals to expected
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(false));
    pattern->UpdateMuted(MUTED_VALUE);
    EXPECT_EQ(pattern->GetMuted(), MUTED_VALUE);
}

/**
 * @tc.name: MovingPhotoPatternTest008
 * @tc.desc: Test OnMediaPlayerPrepared
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoPatternTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto
     * @tc.expected: step1. Create MovingPhoto successfully
     */
    auto frameNode = CreateMovingPhotoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::MOVING_PHOTO_ETS_TAG);
    auto pattern = frameNode->GetPattern<MovingPhotoPattern>();
    ASSERT_TRUE(pattern);

    // set MovingPhotoEvent
    auto movingPhotoEventHub = frameNode->GetEventHub<MovingPhotoEventHub>();
    ASSERT_TRUE(movingPhotoEventHub);
    auto movingPhotoLayoutProperty = pattern->GetLayoutProperty<MovingPhotoLayoutProperty>();

    /**
     * @tc.steps: step2. Call OnMediaPlayerPrepared
     *            case1: isPrepared_ = true
     * @tc.expected: step2. OnMediaPlayerPrepared will start
     */
    EXPECT_FALSE(pattern->GetPrepared());
    pattern->OnMediaPlayerPrepared();
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(true));
    ASSERT_TRUE(pattern->GetPrepared());
}
/**
 * @tc.name: MovingPhotoPatternTest009
 * @tc.desc: Test start && stop
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoPatternTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhotoNode
     * @tc.expected: step1. Create MovingPhotoNode successfully
     */
    auto frameNode = CreateMovingPhotoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::MOVING_PHOTO_ETS_TAG);
    auto pattern = frameNode->GetPattern<MovingPhotoPattern>();
    ASSERT_TRUE(pattern);
    auto rawChildNum = static_cast<int32_t>(frameNode->GetChildren().size());
    
    /**
     * @tc.steps: step2. MovingPhoto stop
     * @tc.expected: step3. MovingPhoto stop successfully
     */
    auto movingPhotoEventHub = pattern->GetEventHub<MovingPhotoEventHub>();
    ASSERT_TRUE(movingPhotoEventHub);
    pattern->Stop();
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), PrepareAsync())
                    .WillRepeatedly(Return(-1));
    
    /**
     * @tc.steps: step3. movingphoto start
     * @tc.expected: step3. movingphoto event create && get children size
     */
    pattern->Start();
    auto childNum = static_cast<int32_t>(frameNode->GetChildren().size());
    EXPECT_EQ(childNum, rawChildNum);
}

/**
 * @tc.name: MovingPhotoPatternTest010
 * @tc.desc: Test OnResolutionChange
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoPatternTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto
     * @tc.expected: step1. Create MovingPhoto successfully
     */
    auto frameNode = CreateMovingPhotoNode(g_testProperty);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::MOVING_PHOTO_ETS_TAG);
    auto pattern = frameNode->GetPattern<MovingPhotoPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. Call OnResolutionChange
     * @tc.expected: step2. related functions will be called
     */
    pattern->OnResolutionChange();

    auto movingPhotoLayoutProperty = frameNode->GetLayoutProperty<MovingPhotoLayoutProperty>();
    ASSERT_TRUE(movingPhotoLayoutProperty->HasVideoSize());
    EXPECT_EQ(movingPhotoLayoutProperty->GetVideoSizeValue(SizeF(0, 0)).Width(), 100);
    EXPECT_EQ(movingPhotoLayoutProperty->GetVideoSizeValue(SizeF(0, 0)).Height(), 100);
}

/**
 * @tc.name: MovingPhotoPatternTest011
 * @tc.desc: Test MovingPhotoPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoPatternTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a MovingPhoto and get the MovingPhotoPattern.
     * @tc.expected: step1. Create and get successfully.
     */
    MovingPhotoModelNG movingphoto;
    auto movingPhotoController = AceType::MakeRefPtr<MovingPhotoController>();
    movingphoto.Create(movingPhotoController);
    auto frameNode = AceType::Claim<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto movingPhotoPattern = AceType::DynamicCast<MovingPhotoPattern>(frameNode->GetPattern());
    ASSERT_NE(movingPhotoPattern, nullptr);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(movingPhotoPattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(false));

    /**
     * @tc.steps: step2. Set skipMeasure property of drawSwapConfig.
     * @tc.expected: step2. LayoutWrapper swap failed.
     */
    DirtySwapConfig config;
    config.skipMeasure = true;
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto movingPhotoLayoutProperty = frameNode->GetLayoutProperty<MovingPhotoLayoutProperty>();
    ASSERT_NE(movingPhotoLayoutProperty, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, movingPhotoLayoutProperty);
    layoutWrapper->skipMeasureContent_ = true;
    EXPECT_FALSE(movingPhotoPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
    config.skipMeasure = false;
    EXPECT_FALSE(movingPhotoPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));

    /**
     * @tc.steps: step3. Set skipMeasure property of layoutAlgorithm.
     * @tc.expected: step3. LayoutWrapper swap failed.
     */
    config.skipMeasure = true;
    layoutWrapper->skipMeasureContent_ = false;
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(AceType::MakeRefPtr<LayoutAlgorithm>());
    layoutWrapper->layoutAlgorithm_ = layoutAlgorithm;
    layoutWrapper->layoutAlgorithm_->skipMeasure_ = false;
    EXPECT_FALSE(movingPhotoPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));

    /**
     * @tc.steps: step4. Call function while videoSize is null.
     * @tc.expected: step4. LayoutWrapper swap failed.
     */
    geometryNode->SetContentSize(SizeF(SCREEN_WIDTH_SMALL, SCREEN_HEIGHT_SMALL));
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    movingPhotoPattern->renderContextForMediaPlayer_ = mockRenderContext;
    EXPECT_FALSE(movingPhotoPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}

/**
 * @tc.name: MovingPhotoFocusTest013
 * @tc.desc: Create MovingPhoto, and test focus.
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoFocusTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto
     * @tc.expected: step1. Create MovingPhoto successfully
     */
    auto frameNode = CreateMovingPhotoNode(g_testProperty);
    EXPECT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::MOVING_PHOTO_ETS_TAG);
    frameNode->GetOrCreateFocusHub()->currentFocus_ = false;
    auto movingPhotoPattern = frameNode->GetPattern<MovingPhotoPattern>();
    ASSERT_TRUE(movingPhotoPattern);
    /**
     * @tc.steps: step2. GetFocusPattern
     * @tc.expected: step2.  MovingPhoto focusPattern is NODE
     */
    EXPECT_EQ(movingPhotoPattern->GetFocusPattern().focusType_, FocusType::NODE);
}

/**
 * @tc.name: MovingPhotoFocusTest014
 * @tc.desc: Create MovingphotoT, and test focus and children node focus.
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoFocusTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto
     * @tc.expected: step1. Create MovingPhoto successfully
     */
    auto frameNode = CreateMovingPhotoNode(g_testProperty);
    EXPECT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::MOVING_PHOTO_ETS_TAG);
    frameNode->GetOrCreateFocusHub()->currentFocus_ = true;
    auto movingPhotoPattern = frameNode->GetPattern<MovingPhotoPattern>();
    CHECK_NULL_VOID(movingPhotoPattern);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(movingPhotoPattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(true));

    auto movingPhotoLayoutProperty = frameNode->GetLayoutProperty<MovingPhotoLayoutProperty>();
    ASSERT_NE(movingPhotoLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. Create LayoutWrapper and set movingPhotoLayoutAlgorithm.
     * @tc.expected: step2. Create movingPhoto pattern and node successfully.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto movingPhotoAlgorithm = movingPhotoPattern->CreateLayoutAlgorithm();
    ASSERT_NE(movingPhotoAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(movingPhotoAlgorithm));

    /**
     * @tc.steps: step3. Set source size and layout size.
     * @tc.expected: step3. Set successfully.
     */
    LayoutConstraintF layoutConstraint;
    movingPhotoLayoutProperty->UpdateVideoSize(MOVINGPHOTO_SIZE);
    layoutConstraint.selfIdealSize.SetSize(MOVINGPHOTO_SIZE);
    auto videoSize1 =
        movingPhotoAlgorithm->MeasureContent(layoutConstraint, &layoutWrapper).value_or(SizeF(0.0f, 0.0f));
    EXPECT_EQ(videoSize1, SizeF(MP_WIDTH, MOVINGPHOTO_HEIGHT));
    layoutWrapper.GetGeometryNode()->SetContentSize(videoSize1);

    /**
     * @tc.steps: step4. Set the framenode tree, and test the focus.
     * @tc.expected: step4. Test focus on child successfully.
     */
    frameNode->GetOrCreateFocusHub()->RequestFocusImmediately();

    for (const auto& child : frameNode->GetChildren()) {
        if (child->GetTag() == V2::ROW_ETS_TAG) {
            auto slider = AceType::DynamicCast<FrameNode>(child->GetChildAtIndex(SLIDER_INDEX));
            EXPECT_EQ(slider->GetOrCreateFocusHub()->IsFocusable(), true);
            break;
        }
    }
}

/**
 * @tc.name: MovingPhotoNodeTest015
 * @tc.desc: Create movingPhoto.
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoNodeTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create movingPhoto
     * @tc.expected: step1. Create movingPhoto node1 and node2 successfully
     */
    auto movingPhotoController = AceType::MakeRefPtr<MovingPhotoController>();
    auto movingPhotoNode = MovingPhotoNode::GetOrCreateMovingPhotoNode(V2::MOVING_PHOTO_ETS_TAG, MOVINGPHOTO_NODE_ID_1,
        [movingPhotoController]() { return AceType::MakeRefPtr<MovingPhotoPattern>(movingPhotoController); });
    EXPECT_TRUE(movingPhotoNode);
    EXPECT_EQ(movingPhotoNode->GetTag(), V2::MOVING_PHOTO_ETS_TAG);

    auto secondMovingPhotoNode = MovingPhotoNode::GetOrCreateMovingPhotoNode(V2::MOVING_PHOTO_ETS_TAG,
        MOVINGPHOTO_NODE_ID_1, [movingPhotoController]()
        { return AceType::MakeRefPtr<MovingPhotoPattern>(movingPhotoController); });
    EXPECT_TRUE(secondMovingPhotoNode);
    EXPECT_EQ(movingPhotoNode->GetTag(), secondMovingPhotoNode->GetTag());
    EXPECT_EQ(movingPhotoNode->GetId(), secondMovingPhotoNode->GetId());

    /**
     * @tc.steps: step2. Create movingPhoto again
     * @tc.expected: step2. Create movingPhoto node3 successfully
     */
    auto thirdMovingPhotoNode = MovingPhotoNode::GetOrCreateMovingPhotoNode(V2::MOVING_PHOTO_ETS_TAG,
        MOVINGPHOTO_NODE_ID_2,
        [movingPhotoController]() { return AceType::MakeRefPtr<MovingPhotoPattern>(movingPhotoController); });
    EXPECT_TRUE(thirdMovingPhotoNode);
    EXPECT_EQ(movingPhotoNode->GetTag(), thirdMovingPhotoNode->GetTag());
    EXPECT_NE(movingPhotoNode->GetId(), thirdMovingPhotoNode->GetId());
}

/**
 * @tc.name: MovingPhotoPatternEventTest016
 * @tc.desc: Create MovingPhoto and test onvisiblechange event.
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoPatternEventTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Video
     * @tc.expected: step1. Create Video successfully.
     */
    MovingPhotoModelNG movingphoto;
    auto movingPhotoController = AceType::MakeRefPtr<MovingPhotoController>();
    ASSERT_NE(movingPhotoController, nullptr);
    movingphoto.Create(movingPhotoController);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto movingPhotoPattern = AceType::DynamicCast<MovingPhotoPattern>(frameNode->GetPattern());
    ASSERT_NE(movingPhotoPattern, nullptr);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(movingPhotoPattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(false));

    /**
     * @tc.steps: step2. Make MovingPhoto visible
     * @tc.expected: step2. MovingPhoto callback result is false.
     */
    movingPhotoPattern->OnVisibleChange(true);

    /**
     * @tc.steps: step3. Make MovingPhoto visible false
     * @tc.expected: step3. MovingPhoto callback result is true.
     */
    movingPhotoPattern->OnVisibleChange(false);
}

/**
 * @tc.name: MovingPhotoPatternTest017
 * @tc.desc: Test MovingPhotoPattern ResetMediaPlayer.
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoPatternTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto and get MovingPhotoPattern.
     */
    MovingPhotoModelNG movingphoto;
    movingphoto.Create(AceType::MakeRefPtr<MovingPhotoController>());
    auto movingphotoNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(movingphotoNode, nullptr);
    auto movingphotoPattern = movingphotoNode->GetPattern<MovingPhotoPattern>();
    ASSERT_NE(movingphotoPattern, nullptr);

    /**
     * @tc.steps: step2. Call ResetMediaPlayer when mediaPlayer_ in different status.
     * @tc.expected: mediaPlayer_'s functions is called. and PlaybackStatus is PREPARED
     */
    movingphoto.SetImageSrc(MOVINGPHOTO_IMAGE_SRC);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(movingphotoPattern->mediaPlayer_)), SetSource(_, _, _))
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(movingphotoPattern->mediaPlayer_)), PrepareAsync())
        .WillRepeatedly(Return(0));
    movingphotoPattern->ResetMediaPlayer();
    EXPECT_FALSE(movingphotoPattern->GetPrepared());
}

/**
 * @tc.name: MovingPhotoPatternTest018
 * @tc.desc: Test MovingPhotoPattern PrepareSurface.
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoPatternTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto and get MovingPhotoPattern.
     */
    MovingPhotoModelNG movingphoto;
    movingphoto.Create(AceType::MakeRefPtr<MovingPhotoController>());
    auto movingphotoNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(movingphotoNode, nullptr);
    auto movingphotoPattern = movingphotoNode->GetPattern<MovingPhotoPattern>();
    ASSERT_NE(movingphotoPattern, nullptr);

    /**
     * @tc.steps: step2. Call PrepareSurface in different status
     * @tc.expected: SetSurface function is called
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockRenderSurface>(movingphotoPattern->renderSurface_)), IsSurfaceValid())
        .WillRepeatedly(Return(false));
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(movingphotoPattern->mediaPlayer_)), SetSurface())
        .WillRepeatedly(Return(-1));
    movingphotoPattern->PrepareSurface();
    SystemProperties::SetExtSurfaceEnabled(false);
    movingphotoPattern->PrepareSurface();
}

/**
 * @tc.name: MovingPhotoPatternTest019
 * @tc.desc: Test MovingphotoTestNg OnRebuildFrame.
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoPatternTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto and get MovingPhotoPattern.
     */
    MovingPhotoModelNG movingphoto;
    movingphoto.Create(AceType::MakeRefPtr<MovingPhotoController>());
    auto movingphotoNode = AceType::DynamicCast<MovingPhotoNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(movingphotoNode, nullptr);
    auto movingphotoPattern = movingphotoNode->GetPattern<MovingPhotoPattern>();
    ASSERT_NE(movingphotoPattern, nullptr);

    /**
     * @tc.steps: step2. Call OnRebuildFrame while renderSurface_ in different status.
     * @tc.expected: IsSurfaceValid function is called only once.
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockRenderSurface>(movingphotoPattern->renderSurface_)), IsSurfaceValid())
        .Times(1)
        .WillOnce(Return(true));
    movingphotoPattern->OnRebuildFrame();
    movingphotoPattern->renderSurface_ = nullptr;
    movingphotoPattern->OnRebuildFrame();
}

/**
 * @tc.name: MovingPhotoPatternTest020
 * @tc.desc: Test MovingPhotoPattern StartPlayback.
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoPatternTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto and get MovingPhotoPattern.
     */
    MovingPhotoModelNG movingphoto;
    movingphoto.Create(AceType::MakeRefPtr<MovingPhotoController>());
    auto movingphotoNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(movingphotoNode, nullptr);
    auto movingphotoPattern = movingphotoNode->GetPattern<MovingPhotoPattern>();
    ASSERT_NE(movingphotoPattern, nullptr);

    /**
     * @tc.steps: step2. Call StartPlayback.
     * @tc.expected: MovingPhoto start
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(movingphotoPattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(true));
    EXPECT_CALL(*(AceType::DynamicCast<MockRenderSurface>(movingphotoPattern->renderSurface_)), IsSurfaceValid())
        .WillRepeatedly(Return(true));
    movingphotoPattern->isPlayByController_ = false;
    movingphotoPattern->isPrepared_ = true;
    movingphotoPattern->StartPlayback();
    ASSERT_TRUE(movingphotoPattern->GetPlayByController());
}

/**
 * @tc.name: MovingPhotoPatternTest021
 * @tc.desc: Test MovingPhotoPattern AutoPlay.
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoPatternTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto and get MovingPhotoPattern.
     */
    MovingPhotoModelNG movingphoto;
    movingphoto.Create(AceType::MakeRefPtr<MovingPhotoController>());
    auto movingphotoNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(movingphotoNode, nullptr);
    auto movingphotoPattern = movingphotoNode->GetPattern<MovingPhotoPattern>();
    ASSERT_NE(movingphotoPattern, nullptr);

    /**
     * @tc.steps: step2. Call AutoPlay.
     * @tc.expected: MovingPhoto AutoPlay
     */
    PlaybackMode oldHistoryAutoAndRepeatLevel_ = movingphotoPattern->historyAutoAndRepeatLevel_;
    PlaybackMode oldAutoAndRepeatLevel_ = movingphotoPattern->autoAndRepeatLevel_;

    movingphotoPattern->AutoPlay(false);
    EXPECT_EQ(movingphotoPattern->historyAutoAndRepeatLevel_, oldHistoryAutoAndRepeatLevel_);
    EXPECT_EQ(movingphotoPattern->autoAndRepeatLevel_, oldAutoAndRepeatLevel_);

    movingphotoPattern->AutoPlay(true);
    EXPECT_EQ(movingphotoPattern->historyAutoAndRepeatLevel_, PlaybackMode::AUTO);
    EXPECT_EQ(movingphotoPattern->autoAndRepeatLevel_, PlaybackMode::AUTO);
}

/**
 * @tc.name: MovingPhotoPatternTest022
 * @tc.desc: Test MovingPhotoPattern AutoPlayPeriod.
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoPatternTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto and get MovingPhotoPattern.
     */
    MovingPhotoModelNG movingphoto;
    movingphoto.Create(AceType::MakeRefPtr<MovingPhotoController>());
    auto movingphotoNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(movingphotoNode, nullptr);
    auto movingphotoPattern = movingphotoNode->GetPattern<MovingPhotoPattern>();
    ASSERT_NE(movingphotoPattern, nullptr);

    /**
     * @tc.steps: step2. Call AutoPlayPeriod.
     * @tc.expected: MovingPhoto AutoPlayPeriod
     */
    int64_t oldAutoPlayPeriodStartTime_ = movingphotoPattern->autoPlayPeriodStartTime_;
    int64_t oldAutoPlayPeriodEndTime_ = movingphotoPattern->autoPlayPeriodEndTime_;

    movingphotoPattern->AutoPlayPeriod(-100, 500);
    EXPECT_EQ(movingphotoPattern->autoPlayPeriodStartTime_, oldAutoPlayPeriodStartTime_);
    EXPECT_EQ(movingphotoPattern->autoPlayPeriodEndTime_, oldAutoPlayPeriodEndTime_);

    movingphotoPattern->AutoPlayPeriod(100, 5000);
    EXPECT_EQ(movingphotoPattern->autoPlayPeriodStartTime_, 100);
    EXPECT_EQ(movingphotoPattern->autoPlayPeriodEndTime_, 5000);

    movingphotoPattern->AutoPlayPeriod(100, 500);
    EXPECT_EQ(movingphotoPattern->autoPlayPeriodStartTime_, 100);
    EXPECT_EQ(movingphotoPattern->autoPlayPeriodEndTime_, 500);

    movingphotoPattern->AutoPlayPeriod(0, 3000);
    EXPECT_EQ(movingphotoPattern->autoPlayPeriodStartTime_, 0);
    EXPECT_EQ(movingphotoPattern->autoPlayPeriodEndTime_, 3000);
}

/**
 * @tc.name: MovingPhotoPatternTest023
 * @tc.desc: Test MovingPhotoPattern RepeatPlay.
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoPatternTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto and get MovingPhotoPattern.
     */
    MovingPhotoModelNG movingphoto;
    movingphoto.Create(AceType::MakeRefPtr<MovingPhotoController>());
    auto movingphotoNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(movingphotoNode, nullptr);
    auto movingphotoPattern = movingphotoNode->GetPattern<MovingPhotoPattern>();
    ASSERT_NE(movingphotoPattern, nullptr);

    /**
     * @tc.steps: step2. Call RepeatPlay.
     * @tc.expected: MovingPhoto RepeatPlay
     */
    PlaybackMode oldHistoryAutoAndRepeatLevel_ = movingphotoPattern->historyAutoAndRepeatLevel_;
    PlaybackMode oldAutoAndRepeatLevel_ = movingphotoPattern->autoAndRepeatLevel_;

    movingphotoPattern->RepeatPlay(false);
    EXPECT_EQ(movingphotoPattern->historyAutoAndRepeatLevel_, oldHistoryAutoAndRepeatLevel_);
    EXPECT_EQ(movingphotoPattern->autoAndRepeatLevel_, oldAutoAndRepeatLevel_);
    movingphotoPattern->RepeatPlay(true);
    EXPECT_EQ(movingphotoPattern->historyAutoAndRepeatLevel_, PlaybackMode::REPEAT);
    EXPECT_EQ(movingphotoPattern->autoAndRepeatLevel_, PlaybackMode::REPEAT);

    /**
     * @tc.steps: step3. Call RepeatPlay, then call AutoPlay.
     * @tc.expected: MovingPhoto RepeatPlay
     */
    movingphotoPattern->AutoPlay(true);
    EXPECT_EQ(movingphotoPattern->historyAutoAndRepeatLevel_, PlaybackMode::REPEAT);
    EXPECT_EQ(movingphotoPattern->autoAndRepeatLevel_, PlaybackMode::REPEAT);
}

/**
 * @tc.name: MovingPhotoPatternTest024
 * @tc.desc: Test MovingPhotoPattern UpdateCurrentDateModified.
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoPatternTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto and get MovingPhotoPattern.
     */
    MovingPhotoModelNG movingphoto;
    movingphoto.Create(AceType::MakeRefPtr<MovingPhotoController>());
    auto movingphotoNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(movingphotoNode, nullptr);
    auto movingphotoPattern = movingphotoNode->GetPattern<MovingPhotoPattern>();
    ASSERT_NE(movingphotoPattern, nullptr);

    /**
     * @tc.steps: step2. Call UpdateCurrentDateModified.
     * @tc.expected: MovingPhoto UpdateCurrentDateModified
     */
    movingphotoPattern->UpdateCurrentDateModified(100);
    EXPECT_EQ(movingphotoPattern->GetCurrentDateModified(), 100);
    EXPECT_EQ(movingphotoPattern->currentDateModified_, 100);
}

/**
 * @tc.name: ShouldUpdateImageAnalyzer001
 * @tc.desc: Test ShouldUpdateImageAnalyzer
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, ShouldUpdateImageAnalyzer001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto and get MovingPhotoPattern.
     */
    auto frameNode = CreateMovingPhotoNode(g_testProperty);
    EXPECT_TRUE(frameNode);
    MovingPhotoModelNG movingphoto;
    movingphoto.Create(AceType::MakeRefPtr<MovingPhotoController>());
    auto movingphotoNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(movingphotoNode, nullptr);
    auto movingphotoPattern = movingphotoNode->GetPattern<MovingPhotoPattern>();
    ASSERT_NE(movingphotoPattern, nullptr);
    auto movingPhotoLayoutProperty = frameNode->GetLayoutProperty<MovingPhotoLayoutProperty>();
    ASSERT_NE(movingPhotoLayoutProperty, nullptr);
    EXPECT_FALSE(movingphotoPattern->ShouldUpdateImageAnalyzer());
}

/**
 * @tc.name: SetImageAIOptions001
 * @tc.desc: Test SetImageAIOptions
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, SetImageAIOptions001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto and get MovingPhotoPattern.
     */
    MovingPhotoModelNG movingphoto;
    movingphoto.Create(AceType::MakeRefPtr<MovingPhotoController>());
    auto movingphotoNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(movingphotoNode, nullptr);
    auto movingphotoPattern = movingphotoNode->GetPattern<MovingPhotoPattern>();
    ASSERT_NE(movingphotoPattern, nullptr);

    EXPECT_EQ(movingphotoPattern->imageAnalyzerManager_, nullptr);
    movingphotoPattern->SetImageAIOptions(nullptr);
    EXPECT_NE(movingphotoPattern->imageAnalyzerManager_, nullptr);

    movingphotoPattern->EnableAnalyzer(true);
    auto imageAnalyzerManager = movingphotoPattern->imageAnalyzerManager_;
    movingphotoPattern->SetImageAIOptions(nullptr);
    EXPECT_EQ(movingphotoPattern->imageAnalyzerManager_, imageAnalyzerManager);
}

/**
 * @tc.name: StartImageAnalyzer001
 * @tc.desc: Test StartImageAnalyzer
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, StartImageAnalyzer001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto and get MovingPhotoPattern.
     */
    auto frameNode = CreateMovingPhotoNode(g_testProperty);
    EXPECT_TRUE(frameNode);
    MovingPhotoModelNG movingphoto;
    movingphoto.Create(AceType::MakeRefPtr<MovingPhotoController>());
    auto movingphotoNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(movingphotoNode, nullptr);
    auto movingphotoPattern = movingphotoNode->GetPattern<MovingPhotoPattern>();
    ASSERT_NE(movingphotoPattern, nullptr);
    auto movingPhotoLayoutProperty = frameNode->GetLayoutProperty<MovingPhotoLayoutProperty>();
    ASSERT_NE(movingPhotoLayoutProperty, nullptr);

    auto imageAnalyzerManager =
        std::make_shared<MockImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::MOVINGPHOTO);
    imageAnalyzerManager->SetSupportImageAnalyzerFeature(true);
    movingphotoPattern->imageAnalyzerManager_ = imageAnalyzerManager;
    movingphotoPattern->EnableAnalyzer(true);

    movingphotoPattern->StartImageAnalyzer();

    imageAnalyzerManager->SetOverlayCreated(true);

    movingphotoPattern->StartImageAnalyzer();
    EXPECT_TRUE(movingphotoPattern->isEnableAnalyzer_);
}

/**
 * @tc.name: StartUpdateImageAnalyzer001
 * @tc.desc: Test StartUpdateImageAnalyzer
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, StartUpdateImageAnalyzer001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto and get MovingPhotoPattern.
     */
    auto frameNode = CreateMovingPhotoNode(g_testProperty);
    EXPECT_TRUE(frameNode);
    MovingPhotoModelNG movingphoto;
    movingphoto.Create(AceType::MakeRefPtr<MovingPhotoController>());
    auto movingphotoNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(movingphotoNode, nullptr);
    auto movingphotoPattern = movingphotoNode->GetPattern<MovingPhotoPattern>();
    ASSERT_NE(movingphotoPattern, nullptr);

    auto context = frameNode->GetContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();

    auto imageAnalyzerManager =
        std::make_shared<MockImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::MOVINGPHOTO);
    movingphotoPattern->imageAnalyzerManager_ = imageAnalyzerManager;
    movingphotoPattern->EnableAnalyzer(true);

    imageAnalyzerManager->SetOverlayCreated(false);

    movingphotoPattern->StartUpdateImageAnalyzer();
    EXPECT_FALSE(movingphotoPattern->isContentSizeChanged_);

    movingphotoPattern->isContentSizeChanged_ = false;
    imageAnalyzerManager->SetOverlayCreated(true);

    movingphotoPattern->StartUpdateImageAnalyzer();
    EXPECT_TRUE(movingphotoPattern->isContentSizeChanged_);

    movingphotoPattern->isContentSizeChanged_ = true;
    movingphotoPattern->StartUpdateImageAnalyzer();
    EXPECT_TRUE(movingphotoPattern->isContentSizeChanged_);
}

/**
 * @tc.name: UpdateAnalyzerUIConfig001
 * @tc.desc: Test UpdateAnalyzerUIConfig
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, UpdateAnalyzerUIConfig001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto and get MovingPhotoPattern.
     */
    auto frameNode = CreateMovingPhotoNode(g_testProperty);
    EXPECT_TRUE(frameNode);
    MovingPhotoModelNG movingphoto;
    movingphoto.Create(AceType::MakeRefPtr<MovingPhotoController>());
    auto movingphotoNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(movingphotoNode, nullptr);
    auto movingphotoPattern = movingphotoNode->GetPattern<MovingPhotoPattern>();
    ASSERT_NE(movingphotoPattern, nullptr);
    auto movingPhotoLayoutProperty = frameNode->GetLayoutProperty<MovingPhotoLayoutProperty>();
    ASSERT_NE(movingPhotoLayoutProperty, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);

    movingphotoPattern->UpdateAnalyzerUIConfig(geometryNode);

    auto imageAnalyzerManager =
        std::make_shared<MockImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::MOVINGPHOTO);
    imageAnalyzerManager->SetSupportImageAnalyzerFeature(true);
    movingphotoPattern->imageAnalyzerManager_ = imageAnalyzerManager;
    movingphotoPattern->EnableAnalyzer(true);

    movingphotoPattern->UpdateAnalyzerUIConfig(geometryNode);
    EXPECT_TRUE(movingphotoPattern->isEnableAnalyzer_);
}

/**
 * @tc.name: RefreshMovingPhoto001
 * @tc.desc: Test RefreshMovingPhoto
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, RefreshMovingPhoto001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto and get MovingPhotoPattern.
     */
    auto frameNode = CreateMovingPhotoNode(g_testProperty);
    EXPECT_TRUE(frameNode);
    MovingPhotoModelNG movingphoto;
    movingphoto.Create(AceType::MakeRefPtr<MovingPhotoController>());
    auto movingphotoNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(movingphotoNode, nullptr);
    auto movingphotoPattern = movingphotoNode->GetPattern<MovingPhotoPattern>();
    ASSERT_NE(movingphotoPattern, nullptr);
    auto movingPhotoLayoutProperty = frameNode->GetLayoutProperty<MovingPhotoLayoutProperty>();
    ASSERT_NE(movingPhotoLayoutProperty, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);

    movingphotoPattern->RefreshMovingPhoto();

    EXPECT_FALSE(movingphotoPattern->isRefreshMovingPhoto_);
}

/**
 * @tc.name: MovingPhotoPatternTest025
 * @tc.desc: Test setWaterMask
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoPatternTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto
     * @tc.expected: step1. setWaterMask
     */
    auto frameNode = CreateMovingPhotoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::MOVING_PHOTO_ETS_TAG);
    auto pattern = frameNode->GetPattern<MovingPhotoPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. set watermask
     * @tc.expected: step2. get watermask status is equeals to expected
     */
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(pattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(false));
    pattern->SetWaterMask(true);
    EXPECT_EQ(pattern->GetWaterMask(), true);
}
/**
 * @tc.name: MovingPhotoPatternTest026
 * @tc.desc: Test NotifyTransition
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoPatternTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto
     * @tc.expected: step1. Create MovingPhoto
     */
    auto frameNode = CreateMovingPhotoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::MOVING_PHOTO_ETS_TAG);
    auto pattern = frameNode->GetPattern<MovingPhotoPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. NotifyTransition
     * @tc.expected: step2. notifyTransitionFlag_ != 0
     */
    pattern->NotifyTransition();
    EXPECT_EQ(pattern->notifyTransitionFlag_, true);
}

/**
 * @tc.name: MovingPhotoPatternTest027
 * @tc.desc: Test DetachImageNode
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoPatternTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto
     * @tc.expected: step1. Create MovingPhoto
     */
    auto frameNode = CreateMovingPhotoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::MOVING_PHOTO_ETS_TAG);
    auto pattern = frameNode->GetPattern<MovingPhotoPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. DetachFirstImageFromFrameNode
     * @tc.expected: step2. NotifyTransition add temp node
     */
    pattern->NotifyTransition();
    int32_t childCount = frameNode->GetTotalChildCount();
    EXPECT_EQ(childCount, 3);
}

/**
 * @tc.name: MovingPhotoPatternTest028
 * @tc.desc: Test DetachImageNode
 * @tc.type: FUNC
 */
HWTEST_F(MovingphotoTestNg, MovingPhotoPatternTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create MovingPhoto
     * @tc.expected: step1. Create MovingPhoto
     */
    auto frameNode = CreateMovingPhotoNode(g_testProperty);
    ASSERT_TRUE(frameNode);
    EXPECT_EQ(frameNode->GetTag(), V2::MOVING_PHOTO_ETS_TAG);
    auto pattern = frameNode->GetPattern<MovingPhotoPattern>();
    ASSERT_TRUE(pattern);

    /**
     * @tc.steps: step2. DetachFirstImageFromFrameNode
     * @tc.expected: step2. delete first imageNode
     */
    pattern->DetachFirstImageFromFrameNode();
    int32_t childCount = frameNode->GetTotalChildCount();
    EXPECT_EQ(childCount, 1);
}
} //namespace OHOS::Ace::NG
