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

#include <optional>

#include "gtest/gtest.h"
#include "test/mock/base/mock_drag_window.h"
#include "test/mock/base/mock_pixel_map.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_interaction_interface.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/subwindow/subwindow_manager.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/manager/drag_drop/drag_drop_controller_func_wrapper.h"
#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"
#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"
#include "core/components_ng/manager/drag_drop/utils/drag_animation_helper.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
RefPtr<DragWindow> MOCK_DRAG_WINDOW;
constexpr float WIDTH = 400.0f;
constexpr float HEIGHT = 400.0f;
constexpr int32_t RESERVED_DEVICEID = 0xAAAAAAFF;
constexpr int32_t POINTEREVENT_DEFAULT_X = 100;
constexpr int32_t POINTEREVENT_DEFAULT_Y = 100;
const OffsetF COORDINATE_OFFSET(WIDTH, HEIGHT);
} // namespace

class DragControllerFuncWrapperTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void DragControllerFuncWrapperTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp(NG::PipelineContext::GetCurrentContext());
    MOCK_DRAG_WINDOW = DragWindow::CreateDragWindow("", 0, 0, 0, 0);
}

void DragControllerFuncWrapperTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
    MOCK_DRAG_WINDOW = nullptr;
}

/**
 * @tc.name: DragDropControllerFuncWrapperTest001
 * @tc.desc: Test GetUpdateDragMovePosition afther UpdateDragMovePosition. Position is equal to OffsetF() because
 * lastDragMovePosition_ is equal to OffsetF().
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragControllerFuncWrapperTestNg, DragControllerFuncWrapperTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set the update drag move position
     */
    int32_t containerId = 100;

    auto pipelineContext = PipelineContext::GetContextByContainerId(containerId);
    ASSERT_NE(pipelineContext, nullptr);
    auto manager = pipelineContext->GetDragDropManager();
    OffsetF position(10.0f, 20.0f);
    manager->UpdateDragMovePosition(position, false);

    /**
     * @tc.steps: step2. call GetUpdateDragMovePosition
     * @tc.expected: step2. drag move position is equal to OffsetF().
     */
    auto offset = NG::DragControllerFuncWrapper::GetUpdateDragMovePosition(containerId);
    EXPECT_EQ(offset, NG::OffsetF());
}

/**
 * @tc.name: DragDropControllerFuncWrapperTest002
 * @tc.desc: Test ResetContextMenuDragPosition. Position is equal to OffsetF().
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragControllerFuncWrapperTestNg, DragControllerFuncWrapperTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set the update drag move position
     */
    int32_t containerId = 100;

    auto pipelineContext = PipelineContext::GetContextByContainerId(containerId);
    ASSERT_NE(pipelineContext, nullptr);
    auto manager = pipelineContext->GetDragDropManager();
    ASSERT_NE(manager, nullptr);
    OffsetF position(10.0f, 20.0f);
    manager->UpdateDragMovePosition(position, false);

    /**
     * @tc.steps: step2. call ResetContextMenuDragPosition
     * @tc.expected: step2. drag move position is equal to OffsetF().
     */
    NG::DragControllerFuncWrapper::ResetContextMenuDragPosition(containerId);
    auto offset = manager->GetUpdateDragMovePosition();
    EXPECT_EQ(offset, NG::OffsetF());
}

/**
 * @tc.name: DragDropControllerFuncWrapperTest003
 * @tc.desc: Test GetOriginNodeOffset when hasTouchPoint is true or false.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragControllerFuncWrapperTestNg, DragControllerFuncWrapperTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare darg data and asyncCtxData.
     */
    int32_t containerId = 100;
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(containerId, MockContainer::container_);
    bool hasTouchPoint = true;
    DragPointerEvent dragPointerEvent(100, 100, 0, 0);
    NG::DragPreviewOption previewOption;
    DimensionOffset touchPoint = DimensionOffset(10.0_vp, 10.0_vp);
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMapList;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> refPixelMap = PixelMap::CreatePixelMap(voidPtr);

    NG::PreparedInfoForDrag data = { false, 10, 0.5f, false, NG::OffsetF(),
        NG::DragControllerFuncWrapper::GetUpdateDragMovePosition(containerId), refPixelMap };
    NG::PreparedAsyncCtxForAnimate asyncCtxData = { containerId, hasTouchPoint, dragPointerEvent, previewOption,
        touchPoint, pixelMapList };

    /**
     * @tc.steps: step2. call GetOriginNodeOffset when hasTouchPoint is true.
     * @tc.expected: step2. originNodeOffset is equal to NG::OffsetF(90, 90).
     */
    auto pointPosition =
        NG::DragDropFuncWrapper::GetPointRelativeToMainWindow(asyncCtxData.dragPointerEvent.GetPoint());
    auto touchPointOffset = NG::DragControllerFuncWrapper::GetTouchPointOffset(data, asyncCtxData);
    EXPECT_EQ(touchPointOffset, NG::OffsetF(10, 10));
    auto pixelMapScaledOffset =
        NG::DragControllerFuncWrapper::GetPixelMapScaledOffset(pointPosition, data, asyncCtxData);
    EXPECT_EQ(pixelMapScaledOffset, NG::OffsetF(90, 90));
    auto originNodeOffset = NG::DragControllerFuncWrapper::GetOriginNodeOffset(data, asyncCtxData);
    EXPECT_EQ(originNodeOffset, NG::OffsetF(90, 90));

    /**
     * @tc.steps: step3. call GetOriginNodeOffset when hasTouchPoint is false.
     * @tc.expected: step3. originNodeOffset is equal to NG::OffsetF(100, 100).
     */
    hasTouchPoint = false;
    asyncCtxData = { containerId, hasTouchPoint, dragPointerEvent, previewOption, touchPoint, pixelMapList };
    touchPointOffset = NG::DragControllerFuncWrapper::GetTouchPointOffset(data, asyncCtxData);
    EXPECT_EQ(touchPointOffset, NG::OffsetF(-0, -0));
    pixelMapScaledOffset = NG::DragControllerFuncWrapper::GetPixelMapScaledOffset(pointPosition, data, asyncCtxData);
    EXPECT_EQ(pixelMapScaledOffset, NG::OffsetF(100, 100));
    originNodeOffset = NG::DragControllerFuncWrapper::GetOriginNodeOffset(data, asyncCtxData);
    EXPECT_EQ(originNodeOffset, NG::OffsetF(100, 100));
}

/**
 * @tc.name: DragDropControllerFuncWrapperTest004
 * @tc.desc: Test UpdatePreviewPositionAndScale. ImageContext's ClickEffectLevelValue can be updated to LIGHT.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragControllerFuncWrapperTestNg, DragControllerFuncWrapperTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare darg data, asyncCtxData and Invoke CreatePreviewNode function.
     * @tc.expected: step1. ImageNode is not null.
     */
    int32_t containerId = 100;
    bool hasTouchPoint = true;
    DragPointerEvent dragPointerEvent(100, 100);
    NG::DragPreviewOption previewOption;
    DimensionOffset touchPoint = DimensionOffset(10.0_vp, 10.0_vp);
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMapList;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> refPixelMap = PixelMap::CreatePixelMap(voidPtr);

    NG::PreparedInfoForDrag data = { false, 10, 0.5f, false, NG::OffsetF(),
        NG::DragControllerFuncWrapper::GetUpdateDragMovePosition(containerId), refPixelMap };
    NG::PreparedAsyncCtxForAnimate asyncCtxData = { containerId, hasTouchPoint, dragPointerEvent, previewOption,
        touchPoint, pixelMapList };
    RefPtr<FrameNode> imageNode = nullptr;
    NG::DragControllerFuncWrapper::CreatePreviewNode(imageNode, data, asyncCtxData);
    ASSERT_NE(imageNode, nullptr);

    /**
     * @tc.steps: step2. Call UpdatePreviewPositionAndScale function.
     * @tc.expected: step2. GetClickEffectLevelValue is correct.
     */
    auto frameOffset = NG::DragControllerFuncWrapper::GetOriginNodeOffset(data, asyncCtxData);
    NG::DragControllerFuncWrapper::UpdatePreviewPositionAndScale(imageNode, frameOffset, data.previewScale);
    auto imageContext = imageNode->GetRenderContext();
    auto clickEffectInfo = imageContext->GetClickEffectLevelValue();
    EXPECT_EQ(clickEffectInfo.level, ClickEffectLevel::LIGHT);
}

/**
 * @tc.name: DragDropControllerFuncWrapperTest005
 * @tc.desc: Test GetOrCreateGatherNode. GatherNode can be created when pixelMapList size > 1.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragControllerFuncWrapperTestNg, DragControllerFuncWrapperTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create OverlayManager.
     * @tc.expected: step1. OverlayManager is not null.
     */
    int32_t containerId = 100;
    auto pipelineContext = PipelineContext::GetContextByContainerId(containerId);
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    /**
     * @tc.steps: step2. Prepare darg data and asyncCtxData.
     */
    bool hasTouchPoint = true;
    DragPointerEvent dragPointerEvent(100, 100);
    NG::DragPreviewOption previewOption;
    previewOption.options.opacity = 0.3f;
    DimensionOffset touchPoint = DimensionOffset(10.0_vp, 10.0_vp);
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMapList;
    void* voidPtr = static_cast<void*>(new char[1]);
    RefPtr<PixelMap> refPixelMap = PixelMap::CreatePixelMap(voidPtr);

    NG::PreparedInfoForDrag data = { false, 10, 0.5f, false, NG::OffsetF(),
        NG::DragControllerFuncWrapper::GetUpdateDragMovePosition(containerId), refPixelMap };
    NG::PreparedAsyncCtxForAnimate asyncCtxData = { containerId, hasTouchPoint, dragPointerEvent, previewOption,
        touchPoint, pixelMapList };

    /**
     * @tc.steps: step3. Call GetOrCreateGatherNode function when pixelMapList size <= 1.
     * @tc.expected: step3. gatherNode is equal to nullptr and childrenInfo size is equal to 0.
     */
    std::vector<GatherNodeChildInfo> childrenInfo;
    auto gatherNode =
        NG::DragControllerFuncWrapper::GetOrCreateGatherNode(overlayManager, childrenInfo, data, asyncCtxData);
    EXPECT_EQ(gatherNode, nullptr);
    EXPECT_EQ(childrenInfo.size(), 0);
}

/**
 * @tc.name: DragDropControllerFuncWrapperTest006
 * @tc.desc: Test UpdatePreviewAttr. ImageContext's opacity can be updated when has opacity value.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragControllerFuncWrapperTestNg, DragControllerFuncWrapperTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare darg data and asyncCtxData and Invoke CreatePreviewNode function.
     * @tc.expected: step1. ImageNode is not null.
     */
    int32_t containerId = 100;
    bool hasTouchPoint = true;
    DragPointerEvent dragPointerEvent(100, 100);
    NG::DragPreviewOption previewOption;
    previewOption.options.opacity = 0.3f;
    DimensionOffset touchPoint = DimensionOffset(10.0_vp, 10.0_vp);
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMapList;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> refPixelMap = PixelMap::CreatePixelMap(voidPtr);

    NG::PreparedInfoForDrag data = { false, 10, 0.5f, false, NG::OffsetF(),
        NG::DragControllerFuncWrapper::GetUpdateDragMovePosition(containerId), refPixelMap };
    NG::PreparedAsyncCtxForAnimate asyncCtxData = { containerId, hasTouchPoint, dragPointerEvent, previewOption,
        touchPoint, pixelMapList };
    RefPtr<FrameNode> imageNode = nullptr;
    NG::DragControllerFuncWrapper::CreatePreviewNode(imageNode, data, asyncCtxData);
    ASSERT_NE(imageNode, nullptr);

    /**
     * @tc.steps: step2. Call UpdatePreviewAttr function when has opacity value.
     * @tc.expected: step2. opacityValue is equal to 0.3f.
     */
    NG::DragControllerFuncWrapper::UpdatePreviewAttr(imageNode, asyncCtxData.dragPreviewOption);
    auto imageContext = imageNode->GetRenderContext();
    auto opacityValue = imageContext->GetOpacityValue();
    EXPECT_EQ(opacityValue, 0.3f);
}

/**
 * @tc.name: DragDropControllerFuncWrapperTest007
 * @tc.desc: Test UpdateGatherAnimatePosition function. GatherNodeChildInfo's imageNode can be updated.
 * @tc.type: FUNC
 */
HWTEST_F(DragControllerFuncWrapperTestNg, DragControllerFuncWrapperTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create imageNode.
     * @tc.expected: step1. imageNode is not null.
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> refPixelMap = PixelMap::CreatePixelMap(voidPtr);
    auto imageNode = DragAnimationHelper::CreateImageNode(refPixelMap);
    ASSERT_NE(imageNode, nullptr);
    auto renderContext = imageNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step1. Call UpdateGatherAnimatePosition with gatherNodeChildInfo.
     * @tc.expected: step1. renderContext's position value is equal to targetOffset.
     */
    std::vector<GatherNodeChildInfo> gatherNodeChildInfo(1);
    gatherNodeChildInfo[0].imageNode = imageNode;
    auto tempOffset = OffsetT<Dimension>(Dimension(0.0f), Dimension(0.0f));
    auto targetOffset = OffsetT<Dimension>(Dimension(COORDINATE_OFFSET.GetX()), Dimension(COORDINATE_OFFSET.GetY()));
    EXPECT_EQ(renderContext->GetPositionValue(tempOffset), tempOffset);
    NG::DragControllerFuncWrapper::UpdateGatherAnimatePosition(
        gatherNodeChildInfo, { COORDINATE_OFFSET.GetX(), COORDINATE_OFFSET.GetY() });
    EXPECT_EQ(renderContext->GetPositionValue(tempOffset), targetOffset);
}

/**
 * @tc.name: DragDropControllerFuncWrapperTest008
 * @tc.desc: Test MountPixelMap function. PixelMap can be mount to root node success.
 * @tc.type: FUNC
 */
HWTEST_F(DragControllerFuncWrapperTestNg, DragControllerFuncWrapperTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare darg data, imageNode, textNode, pipeline and overlayManager.
     * @tc.expected: step1. imageNode, textNode, pipeline and overlayManager is not null.
     */
    int32_t containerId = 100;
    bool hasTouchPoint = true;
    DragPointerEvent dragPointerEvent(100, 100);
    NG::DragPreviewOption previewOption;
    previewOption.options.opacity = 0.3f;
    DimensionOffset touchPoint = DimensionOffset(10.0_vp, 10.0_vp);
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMapList;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> refPixelMap = PixelMap::CreatePixelMap(voidPtr);

    NG::PreparedInfoForDrag data = { false, 10, 0.5f, false, NG::OffsetF(),
        NG::DragControllerFuncWrapper::GetUpdateDragMovePosition(containerId), refPixelMap };
    NG::PreparedAsyncCtxForAnimate asyncCtxData = { containerId, hasTouchPoint, dragPointerEvent, previewOption,
        touchPoint, pixelMapList };
    RefPtr<FrameNode> imageNode = nullptr;
    NG::DragControllerFuncWrapper::CreatePreviewNode(imageNode, data, asyncCtxData);
    ASSERT_NE(imageNode, nullptr);
    auto textNode = NG::DragAnimationHelper::CreateBadgeTextNode(data.badgeNumber);
    ASSERT_NE(textNode, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto overlayManager = pipeline->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    /**
     * @tc.steps: step2. Call MountPixelMap function.
     * @tc.expected: step2. MountPixelMapToRootNode success, overlayManager's hasPixelMap is true.
     */
    NG::DragControllerFuncWrapper::MountPixelMap(overlayManager, data, imageNode, textNode, true);
    EXPECT_EQ(overlayManager->GetHasDragPixelMap(), true);

    /**
     * @tc.steps: step3. Call MountPixelMap function when imageNode isPreviewNeedScale is true.
     * @tc.expected: step3. imageNode's IsPreviewNeedScale is true, and TranslateOptions x value is 0.0f.
     */
    imageNode->GetGeometryNode()->SetFrameWidth(WIDTH);
    EXPECT_EQ(imageNode->IsPreviewNeedScale(), true);
    NG::DragControllerFuncWrapper::MountPixelMap(overlayManager, data, imageNode, textNode, true);
    auto imageContext = imageNode->GetRenderContext();
    EXPECT_TRUE(imageContext->GetTransformTranslate().has_value());
    TranslateOptions result = imageContext->GetTransformTranslate().value();
    TranslateOptions expectValue { 0.0f, 0.0f, 0.0f };
    EXPECT_EQ(result.x.CalcValue(), expectValue.x.CalcValue());
}

/**
 * @tc.name: DragDropControllerFuncWrapperTest009
 * @tc.desc: Test UpdateBadgeTextNodePosition function.
 * @tc.type: FUNC
 */
HWTEST_F(DragControllerFuncWrapperTestNg, DragControllerFuncWrapperTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare darg data, imageNode, textNode, pipeline and overlayManager.
     * @tc.expected: step1. imageNode, textNode, pipeline and overlayManager is not null.
     */
    int32_t containerId = 100;
    bool hasTouchPoint = true;
    DragPointerEvent dragPointerEvent(100, 100);
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(containerId, MockContainer::container_);
    NG::DragPreviewOption previewOption;
    previewOption.options.opacity = 0.3f;
    DimensionOffset touchPoint = DimensionOffset(10.0_vp, 10.0_vp);
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMapList;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> refPixelMap = PixelMap::CreatePixelMap(voidPtr);

    NG::PreparedInfoForDrag data = { false, 10, 0.5f, false, NG::OffsetF(),
        NG::DragControllerFuncWrapper::GetUpdateDragMovePosition(containerId), refPixelMap };
    NG::PreparedAsyncCtxForAnimate asyncCtxData = { containerId, hasTouchPoint, dragPointerEvent, previewOption,
        touchPoint, pixelMapList };
    auto textNode = NG::DragAnimationHelper::CreateBadgeTextNode(data.badgeNumber);
    ASSERT_NE(textNode, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto overlayManager = pipeline->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    /**
     * @tc.steps: step2. Call UpdateBadgeTextNodePosition function.
     * @tc.expected: step2. TranslateOptions x value is 0.0f.
     */
    NG::DragControllerFuncWrapper::UpdateBadgeTextNodePosition(
        textNode, data, asyncCtxData, data.dragPreviewOffsetToScreen);
    auto imageContext = textNode->GetRenderContext();
    TranslateOptions result = imageContext->GetTransformTranslate().value();
    TranslateOptions expectValue { 0.0f, 0.0f, 0.0f };
    EXPECT_EQ(result.x.CalcValue(), expectValue.x.CalcValue());
}

/**
 * @tc.name: DragDropControllerFuncWrapperTest010
 * @tc.desc: Test TransDragWindowToDragFwk function. DragDropManager's isDragFwkShow_ will be true afther
 * TransDragWindowToDragFwk.
 * @tc.type: FUNC
 */
HWTEST_F(DragControllerFuncWrapperTestNg, DragControllerFuncWrapperTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dragDropManager.
     * @tc.expected: step1. dragDropManager is not null.
     */
    int32_t containerId = 100;
    auto pipelineContext = PipelineContext::GetContextByContainerId(containerId);
    ASSERT_NE(pipelineContext, nullptr);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. Call TransDragWindowToDragFwk function.
     * @tc.expected: step2. dragDropManager->isDragFwkShow_ is true
     */
    dragDropManager->SetDragFwkShow(false);
    NG::DragControllerFuncWrapper::TransDragWindowToDragFwk(containerId);
    EXPECT_TRUE(dragDropManager->IsDragFwkShow());
}

/**
 * @tc.name: DragDropControllerFuncWrapperTest011
 * @tc.desc: Test CalcDragMoveOffset function. DragMoveOffset can be calculated correctly.
 * @tc.type: FUNC
 */
HWTEST_F(DragControllerFuncWrapperTestNg, DragControllerFuncWrapperTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dragDropManager.
     * @tc.expected: step1. dragDropManager is not null.
     */
    int32_t containerId = 100;
    auto pipelineContext = PipelineContext::GetContextByContainerId(containerId);
    ASSERT_NE(pipelineContext, nullptr);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. Call CalcDragMoveOffset when dragPreviewInfo's originOffset is OffsetF(20, 20).
     * @tc.expected: step2. CalcDragMoveOffset offset is equal to Offset(10, 10).
     */
    DragDropManager::DragPreviewInfo dragPreviewInfo;
    dragPreviewInfo.originOffset = OffsetF(20, 20);
    dragDropManager->SetDragPreviewInfo(dragPreviewInfo);
    auto offset = NG::DragControllerFuncWrapper::CalcDragMoveOffset(30, 30);
    EXPECT_EQ(offset, Offset(10, 10));
}

/**
 * @tc.name: DragDropControllerFuncWrapperTest0012
 * @tc.desc: Test TryDoDragStartAnimation.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragControllerFuncWrapperTestNg, DragControllerFuncWrapperTest0012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pipelineContext.
     * @tc.expected: step1. pipelineContext is not null.
     */
    int32_t containerId = 100;
    auto pipelineContext = PipelineContext::GetContextByContainerId(containerId);
    ASSERT_NE(pipelineContext, nullptr);
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    ASSERT_NE(pipeline, nullptr);

    /**
     * @tc.steps: step2. Prepare darg data and asyncCtxData.
     */
    bool hasTouchPoint = true;
    DragPointerEvent dragPointerEvent(100, 100);
    NG::DragPreviewOption previewOption;
    previewOption.options.opacity = 0.3f;
    DimensionOffset touchPoint = DimensionOffset(10.0_vp, 10.0_vp);
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMapList;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> refPixelMap = PixelMap::CreatePixelMap(voidPtr);

    NG::PreparedInfoForDrag data = { false, 10, 0.5f, false, NG::OffsetF(),
        NG::DragControllerFuncWrapper::GetUpdateDragMovePosition(containerId), refPixelMap };
    NG::PreparedAsyncCtxForAnimate asyncCtxData = { containerId, hasTouchPoint, dragPointerEvent, previewOption,
        touchPoint, pixelMapList };

    /**
     * @tc.steps: step2. Invoke SubWindowShow function.
     * @tc.expected: step2. subWindow is null.
     */
    pipelineContext = AceType::DynamicCast<NG::PipelineContext>(pipeline);
    ASSERT_NE(pipelineContext, nullptr);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    dragDropManager->SetIsShowBadgeAnimation(true);
    EXPECT_EQ(dragDropManager->IsShowBadgeAnimation(), true);
    RefPtr<Subwindow> subWindow = nullptr;
    {
        auto mainPipeline = PipelineContext::GetMainPipelineContext();
        subWindow = SubwindowManager::GetInstance()->ShowPreviewNG((pipelineContext != mainPipeline));
    }
    EXPECT_EQ(subWindow, nullptr);

    /**
     * @tc.steps: step3. Call TryDoDragStartAnimation function.
     * @tc.expected: step3. returnValue is equal to false.
     */
    auto returnValue = NG::DragControllerFuncWrapper::TryDoDragStartAnimation(subWindow, data, asyncCtxData);
    EXPECT_EQ(returnValue, false);
}

/**
 * @tc.name: DragDropControllerFuncWrapperTest0013
 * @tc.desc: Test DoDragStartAnimation.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragControllerFuncWrapperTestNg, DragControllerFuncWrapperTest0013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create overlayManager.
     * @tc.expected: step1. overlayManager is not null.
     */
    int32_t containerId = 100;
    auto pipelineContext = PipelineContext::GetContextByContainerId(containerId);
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. Prepare darg data and asyncCtxData.
     */
    bool hasTouchPoint = true;
    DragPointerEvent dragPointerEvent(100, 100, 100, 100, 100, 100);
    NG::DragPreviewOption previewOption;
    previewOption.options.opacity = 0.3f;
    DimensionOffset touchPoint = DimensionOffset(10.0_vp, 10.0_vp);
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMapList;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> refPixelMap = PixelMap::CreatePixelMap(voidPtr);

    NG::PreparedInfoForDrag data = { false, 10, 0.5f, false, NG::OffsetF(),
        NG::DragControllerFuncWrapper::GetUpdateDragMovePosition(containerId), refPixelMap };
    NG::PreparedAsyncCtxForAnimate asyncCtxData = { containerId, hasTouchPoint, dragPointerEvent, previewOption,
        touchPoint, pixelMapList };
    asyncCtxData.dragPointerEvent.deviceId = RESERVED_DEVICEID;

    /**
     * @tc.steps: step3. Call DoDragStartAnimation function deviceId == RESERVED_DEVICEID.
     * @tc.expected: step3. dragDropManager->isDragFwkShow_ is true.
     */
    NG::DragControllerFuncWrapper::DoDragStartAnimation(overlayManager, data, asyncCtxData);
    EXPECT_TRUE(dragDropManager->IsDragFwkShow());

    /**
     * @tc.steps: step4. Call DoDragStartAnimation function deviceId != RESERVED_DEVICEID.
     * @tc.expected: step4. dragDropManager->isStartAnimationFinished_ is true
     */
    asyncCtxData.dragPointerEvent.deviceId = 0;
    NG::DragControllerFuncWrapper::DoDragStartAnimation(overlayManager, data, asyncCtxData);
    EXPECT_FALSE(dragDropManager->IsPullMoveReceivedForCurrentDrag());
    EXPECT_EQ(dragDropManager->GetCurrentAnimationCnt(), 0);
    EXPECT_EQ(dragDropManager->GetAllAnimationCnt(), 0);
    EXPECT_EQ(dragDropManager->GetDragAnimationPointerEvent().windowX, 100);
    EXPECT_TRUE(dragDropManager->IsStartAnimationFInished());
}

/**
 * @tc.name: DragDropControllerFuncWrapperTest0014
 * @tc.desc: Test GetDragPreviewInfo.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragControllerFuncWrapperTestNg, DragControllerFuncWrapperTest0014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create overlayManager.
     * @tc.expected: step1. overlayManager is not null.
     */
    int32_t containerId = 100;
    auto pipelineContext = PipelineContext::GetContextByContainerId(containerId);
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto dragDropManager = pipelineContext->GetDragDropManager();
    ASSERT_NE(dragDropManager, nullptr);

    /**
     * @tc.steps: step2. Call GetDragPreviewInfo function.
     * @tc.expected: step2. DragDropManager->dragPreviewInfo.imageNode is nullptr.
     */
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(containerId, MockContainer::container_);
    overlayManager->SetHasPixelMap(true);
    NG::DragControllerFuncWrapper::GetDragPreviewInfo(overlayManager, containerId);
    auto imageNode = overlayManager->GetDragPixelMapContentNode();
    EXPECT_NE(imageNode, nullptr);
    EXPECT_NE(dragDropManager->GetDragPreviewInfo().imageNode, nullptr);
}

/**
 * @tc.name: DragDropControllerFuncWrapperTest0015
 * @tc.desc: Test GetScaleInfo.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragControllerFuncWrapperTestNg, DragControllerFuncWrapperTest0015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call GetScaleInfo function.
     * @tc.expected: step1. isNeedScale is true and sacle is not 1.0f.
     */
    int32_t containerId = 100;
    AceEngine& aceEngine = AceEngine::Get();
    aceEngine.AddContainer(containerId, MockContainer::container_);
    auto scaleData = NG::DragControllerFuncWrapper::GetScaleInfo(containerId, WIDTH, HEIGHT);
    EXPECT_NE(scaleData, nullptr);
    EXPECT_NE(scaleData->isNeedScale, false);
    EXPECT_NE(scaleData->scale, 1.0f);
}

/**
 * @tc.name: DragDropControllerFuncWrapperTest016
 * @tc.desc: Test GetTouchPointOffset when DimensionUnit is PERCENT.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragControllerFuncWrapperTestNg, DragDropControllerFuncWrapperTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare darg data and asyncCtxData.
     */
    int32_t containerId = 100;
    bool hasTouchPoint = true;
    DragPointerEvent dragPointerEvent(100, 100);
    NG::DragPreviewOption previewOption;
    auto touchPointX = Dimension(0.1, DimensionUnit::PERCENT);
    auto touchPointY = Dimension(0.1, DimensionUnit::PERCENT);
    DimensionOffset touchPoint = DimensionOffset(touchPointX, touchPointY);
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMapList;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> refPixelMap = PixelMap::CreatePixelMap(voidPtr);

    NG::PreparedInfoForDrag data = { false, 10, 0.5f, false, NG::OffsetF(),
        NG::DragControllerFuncWrapper::GetUpdateDragMovePosition(containerId), refPixelMap };
    NG::PreparedAsyncCtxForAnimate asyncCtxData = { containerId, hasTouchPoint, dragPointerEvent, previewOption,
        touchPoint, pixelMapList };

    /**
     * @tc.steps: step2. call GetTouchPointOffset.
     * @tc.expected: step2. touchPointOffset is equal to NG::OffsetF(0, 0).
     */
    auto touchPointOffset = NG::DragControllerFuncWrapper::GetTouchPointOffset(data, asyncCtxData);
    EXPECT_EQ(touchPointOffset, NG::OffsetF(0, 0));
}

/**
 * @tc.name: DragDropControllerFuncWrapperTest017
 * @tc.desc: Test UpdatePreviewAttr. ImageContext's opacity can be updated when has opacity value.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragControllerFuncWrapperTestNg, DragControllerFuncWrapperTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare darg data and asyncCtxData and Invoke CreatePreviewNode function.
     * @tc.expected: step1. ImageNode is not null.
     */
    int32_t containerId = 100;
    bool hasTouchPoint = true;
    DragPointerEvent dragPointerEvent(100, 100);
    NG::DragPreviewOption previewOption;
    previewOption.options.opacity = 0.3f;
    previewOption.options.shadow = DragDropFuncWrapper::GetDefaultShadow();
    previewOption.options.borderRadius = DragDropFuncWrapper::GetDefaultBorderRadius();
    previewOption.options.blurbgEffect.backGroundEffect = EffectOption();
    previewOption.options.blurbgEffect.backGroundEffect.radius.SetValue(1.0F);
    DimensionOffset touchPoint = DimensionOffset(10.0_vp, 10.0_vp);
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMapList;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> refPixelMap = PixelMap::CreatePixelMap(voidPtr);

    NG::PreparedInfoForDrag data = { false, 10, 0.5f, false, NG::OffsetF(),
        NG::DragControllerFuncWrapper::GetUpdateDragMovePosition(containerId), refPixelMap };
    NG::PreparedAsyncCtxForAnimate asyncCtxData = { containerId, hasTouchPoint, dragPointerEvent, previewOption,
        touchPoint, pixelMapList };
    RefPtr<FrameNode> imageNode = nullptr;
    NG::DragControllerFuncWrapper::CreatePreviewNode(imageNode, data, asyncCtxData);
    ASSERT_NE(imageNode, nullptr);

    /**
     * @tc.steps: step2. Call UpdatePreviewAttr function when has opacity value.
     * @tc.expected: step2. opacityValue is equal to 0.3f.
     */
    NG::DragControllerFuncWrapper::UpdatePreviewAttr(imageNode, asyncCtxData.dragPreviewOption);
    auto imageContext = imageNode->GetRenderContext();
    ASSERT_NE(imageContext, nullptr);
    auto opacityValue = imageContext->GetOpacityValue();
    EXPECT_EQ(opacityValue, 0.3f);
}

/**
 * @tc.name: DragDropControllerFuncWrapperTest018
 * @tc.desc: Test UpdatePreviewPositionAndScale when scale is 0.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragControllerFuncWrapperTestNg, DragControllerFuncWrapperTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare darg data, asyncCtxData and Invoke CreatePreviewNode function.
     * @tc.expected: step1. ImageNode is not null.
     */
    int32_t containerId = 100;
    bool hasTouchPoint = true;
    DragPointerEvent dragPointerEvent(100, 100);
    NG::DragPreviewOption previewOption;
    DimensionOffset touchPoint = DimensionOffset(10.0_vp, 10.0_vp);
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMapList;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> refPixelMap = PixelMap::CreatePixelMap(voidPtr);

    NG::PreparedInfoForDrag data = { false, 10, 0.0f, false, NG::OffsetF(),
        NG::DragControllerFuncWrapper::GetUpdateDragMovePosition(containerId), refPixelMap };
    NG::PreparedAsyncCtxForAnimate asyncCtxData = { containerId, hasTouchPoint, dragPointerEvent, previewOption,
        touchPoint, pixelMapList };
    RefPtr<FrameNode> imageNode = nullptr;
    NG::DragControllerFuncWrapper::CreatePreviewNode(imageNode, data, asyncCtxData);
    ASSERT_NE(imageNode, nullptr);

    /**
     * @tc.steps: step2. Call UpdatePreviewPositionAndScale function.
     * @tc.expected: step2. GetClickEffectLevelValue is correct.
     */
    auto frameOffset = NG::DragControllerFuncWrapper::GetOriginNodeOffset(data, asyncCtxData);
    NG::DragControllerFuncWrapper::UpdatePreviewPositionAndScale(imageNode, frameOffset, data.previewScale);
    auto imageContext = imageNode->GetRenderContext();
    ASSERT_NE(imageContext, nullptr);
    auto clickEffectInfo = imageContext->GetClickEffectLevelValue();
    EXPECT_EQ(clickEffectInfo.level, ClickEffectLevel::LIGHT);
}

/**
 * @tc.name: DragDropControllerFuncWrapperTest020
 * @tc.desc: Test MountPixelMap function. isDragPixelMap is false.
 * @tc.type: FUNC
 */
HWTEST_F(DragControllerFuncWrapperTestNg, DragControllerFuncWrapperTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare darg data, imageNode, textNode, pipeline and overlayManager.
     * @tc.expected: step1. imageNode, textNode, pipeline and overlayManager is not null.
     */
    int32_t containerId = 100;
    bool hasTouchPoint = true;
    DragPointerEvent dragPointerEvent(100, 100);
    NG::DragPreviewOption previewOption;
    previewOption.options.opacity = 0.3f;
    DimensionOffset touchPoint = DimensionOffset(10.0_vp, 10.0_vp);
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMapList;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> refPixelMap = PixelMap::CreatePixelMap(voidPtr);

    NG::PreparedInfoForDrag data = { false, 10, 0.5f, false, NG::OffsetF(),
        NG::DragControllerFuncWrapper::GetUpdateDragMovePosition(containerId), refPixelMap };
    NG::PreparedAsyncCtxForAnimate asyncCtxData = { containerId, hasTouchPoint, dragPointerEvent, previewOption,
        touchPoint, pixelMapList };
    RefPtr<FrameNode> imageNode = nullptr;
    NG::DragControllerFuncWrapper::CreatePreviewNode(imageNode, data, asyncCtxData);
    ASSERT_NE(imageNode, nullptr);
    auto textNode = NG::DragAnimationHelper::CreateBadgeTextNode(data.badgeNumber);
    ASSERT_NE(textNode, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto overlayManager = pipeline->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);

    /**
     * @tc.steps: step2. Call MountPixelMap function.
     * @tc.expected: step2. MountPixelMapToRootNode success, overlayManager's hasPixelMap is true.
     */
    NG::DragControllerFuncWrapper::MountPixelMap(overlayManager, data, imageNode, textNode, false);
    EXPECT_EQ(overlayManager->GetHasPixelMap(), true);

    /**
     * @tc.steps: step3. Call MountPixelMap function when textNode is nullptr.
     * @tc.expected: step3. MountPixelMapToRootNode success, overlayManager's GetHasDragPixelMap is true
     */
    NG::DragControllerFuncWrapper::MountPixelMap(overlayManager, data, imageNode, nullptr, true);
    EXPECT_EQ(overlayManager->GetHasDragPixelMap(), true);
}

/**
 * @tc.name: DragDropControllerFuncWrapperTest021
 * @tc.desc: Test UpdateBadgeTextNodePosition function.
 * @tc.type: FUNC
 */
HWTEST_F(DragControllerFuncWrapperTestNg, DragControllerFuncWrapperTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare darg data, imageNode, textNode, pipeline and overlayManager.
     * @tc.expected: step1. imageNode, textNode, pipeline and overlayManager is not null.
     */
    int32_t containerId = 100;
    bool hasTouchPoint = true;
    DragPointerEvent dragPointerEvent(100, 100);
    NG::DragPreviewOption previewOption;
    previewOption.options.opacity = 0.3f;
    DimensionOffset touchPoint = DimensionOffset(10.0_vp, 10.0_vp);
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMapList;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> refPixelMap = PixelMap::CreatePixelMap(voidPtr);

    NG::PreparedInfoForDrag data = { false, 1, 0.5f, false, NG::OffsetF(),
        NG::DragControllerFuncWrapper::GetUpdateDragMovePosition(containerId), refPixelMap };
    NG::PreparedAsyncCtxForAnimate asyncCtxData = { containerId, hasTouchPoint, dragPointerEvent, previewOption,
        touchPoint, pixelMapList };

    /**
     * @tc.steps: step2. Call UpdateBadgeTextNodePosition function when badgeNumber is 1.
     * @tc.expected: step2. TranslateOptions x value is 0.0f.
     */
    NG::DragControllerFuncWrapper::UpdateBadgeTextNodePosition(
        nullptr, data, asyncCtxData, data.dragPreviewOffsetToScreen);
    EXPECT_EQ(data.badgeNumber, 1);
}

/**
 * @tc.name: DragControllerFuncWrapperTest022
 * @tc.desc: Test CreateGatherNode.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(DragControllerFuncWrapperTestNg, DragControllerFuncWrapperTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Prepare darg data and asyncCtxData.
     */
    int32_t containerId = 100;
    bool hasTouchPoint = true;
    DragPointerEvent dragPointerEvent(POINTEREVENT_DEFAULT_X, POINTEREVENT_DEFAULT_Y);
    NG::DragPreviewOption previewOption;
    previewOption.options.opacity = 0.3f;
    DimensionOffset touchPoint = DimensionOffset(10.0_vp, 10.0_vp);
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMapList;
    std::unique_ptr<char[]> buffer = std::make_unique<char[]>(1);
    void* voidPtr = buffer.get();
    RefPtr<PixelMap> refPixelMap = PixelMap::CreatePixelMap(voidPtr);

    NG::PreparedInfoForDrag data = { false, 10, 0.5f, false, NG::OffsetF(),
        NG::DragControllerFuncWrapper::GetUpdateDragMovePosition(containerId), refPixelMap };
    NG::PreparedAsyncCtxForAnimate asyncCtxData = { containerId, hasTouchPoint, dragPointerEvent, previewOption,
        touchPoint, pixelMapList };

    /**
     * @tc.steps: step2. Call CreateGatherNode function when pixelMapList size <= 1.
     * @tc.expected: step2. gatherNode is not equal to nullptr and childrenInfo size is equal to 0.
     */
    std::vector<GatherNodeChildInfo> childrenInfo;
    auto gatherNode = NG::DragControllerFuncWrapper::CreateGatherNode(childrenInfo, data, asyncCtxData);
    EXPECT_NE(gatherNode, nullptr);
    EXPECT_EQ(childrenInfo.size(), 0);

    /**
     * @tc.steps: step3. Call CreateGatherNode function when pixelMapList size > 1 and pixelMap is null.
     * @tc.expected: step3. gatherNode is equal to nullptr and childrenInfo size is equal to 0.
     */
    asyncCtxData.pixelMapList.push_back(nullptr);
    asyncCtxData.pixelMapList.push_back(nullptr);
    asyncCtxData.pixelMapList.push_back(nullptr);
    gatherNode = NG::DragControllerFuncWrapper::CreateGatherNode(childrenInfo, data, asyncCtxData);
    EXPECT_EQ(gatherNode, nullptr);
    EXPECT_EQ(childrenInfo.size(), 0);
}
} // namespace OHOS::Ace::NG