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
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/rosen/testing_bitmap.h"
#include "test/mock/core/rosen/testing_canvas.h"

#include "core/components_ng/pattern/model/model_adapter_wrapper.h"
#include "core/components_ng/pattern/model/model_layout_algorithm.h"
#include "core/components_ng/pattern/model/model_light.h"
#include "core/components_ng/pattern/model/model_paint_property.h"
#include "core/components_ng/pattern/model/model_paint_method.h"
#include "core/components_ng/pattern/model/model_pattern.h"
#include "core/components_ng/pattern/model/model_position.h"
#include "core/components_ng/pattern/model/model_property.h"
#include "core/components_ng/pattern/model/model_touch_handler.h"
#include "core/components_ng/pattern/model/model_view.h"
#include "core/components_ng/pattern/model/model_view_ng.h"

#include "scene_adapter/intf_scene_adapter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    uint32_t testKey = UINT32_MAX / 2;
    std::string testPath = "/data/local";
    constexpr int32_t PLATFORM_VERSION_11 = 11;
    Render3D::SurfaceType testSurfaceType = OHOS::Render3D::SurfaceType::SURFACE_WINDOW;
    ModelViewContext testContext { "moudleTest", "moudleTest", testSurfaceType };
}

class TestSceneAdapter : public Render3D::ISceneAdapter {
    bool LoadPluginsAndInit()
    {
        return true;
    }
    std::shared_ptr<Render3D::TextureLayer> CreateTextureLayer()
    {
        return std::make_shared<Render3D::TextureLayer>();
    }
    void OnWindowChange(const Render3D::WindowChangeInfo& windowChangeInfo)
    {
        return;
    }
    void RenderFrame(bool needsSyncPaint = false)
    {
        return;
    }
    void Deinit()
    {
        return;
    }
    bool NeedsRepaint()
    {
        return true;
    }
};

class ModelTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
private:
    ModelViewNG modelViewNG;
};

void ModelTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void ModelTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: ModelViewNgTest001
 * @tc.desc: Test Without Setting Property
 * @tc.type: FUNC
 */
HWTEST_F(ModelTestNg, ModelViewNgTest001, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_11);
    
    // Create ModelViewNG
    modelViewNG.Create(testContext);

    // Get ModelPaintProperty
    auto modelPaintProperty = modelViewNG.frameNode_.Upgrade()->GetPaintProperty<ModelPaintProperty>();
    ASSERT_NE(modelPaintProperty, nullptr);

    // Get ModelPattern
    auto modelPattern = modelViewNG.frameNode_.Upgrade()->GetPattern<ModelPattern>();
    ASSERT_NE(modelPattern, nullptr);

    modelPattern->modelAdapter_->OnPaint3D(modelPaintProperty);

    // ToJsonValue Before Set Values
    const InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    modelPattern->ToJsonValue(json, filter);

    // ImageTexturePath and ShaderInputBuffers
    modelPattern->modelAdapter_->sceneAdapter_ = std::make_shared<TestSceneAdapter>();
    ASSERT_NE(modelPattern->modelAdapter_->sceneAdapter_, nullptr);
    modelPattern->modelAdapter_->UpdateImageTexturePaths(modelPaintProperty);
    modelPattern->modelAdapter_->UpdateShaderInputBuffers(modelPaintProperty);
    modelPattern->modelAdapter_->sceneAdapter_.reset();
    ASSERT_EQ(modelPattern->modelAdapter_->sceneAdapter_, nullptr);
    modelPattern->modelAdapter_->UpdateImageTexturePaths(modelPaintProperty);
    modelPattern->modelAdapter_->UpdateShaderInputBuffers(modelPaintProperty);

    // ShaderInputBuffer
    // Buffer test begin
    std::shared_ptr<OHOS::Render3D::ShaderInputBuffer> buffer = nullptr;
    buffer = std::make_shared<OHOS::Render3D::ShaderInputBuffer>();
    int length = 3; // 3: buffer length

    ASSERT_TRUE(buffer->Alloc(length));
    for (uint32_t i = 0; i < static_cast<uint32_t>(length); i++) {
        buffer->Update(1, i);
    }
    modelViewNG.AddShaderInputBuffer(buffer);
    EXPECT_EQ(modelPaintProperty->GetModelShaderInputBufferValue(), buffer);
    modelPattern->modelAdapter_->UpdateShaderInputBuffers(modelPaintProperty);
    EXPECT_EQ(modelViewNG.GetShaderInputBuffer(), modelPaintProperty->propModelShaderInputBuffer_);
    // Buffer test end

    // CustomRender
    modelPattern->modelAdapter_->UpdateCustomRender(modelPaintProperty);
    auto desc = std::make_shared<Render3D::CustomRenderDescriptor>("/data/local", true);
    modelViewNG.AddCustomRender(desc);
    EXPECT_EQ(modelPaintProperty->GetModelCustomRenderValue(), desc);
    modelPattern->modelAdapter_->UpdateCustomRender(modelPaintProperty);

    // AddShaderImageTexture
    // Case 1:: frameNode != nullptr
    modelViewNG.AddShaderImageTexture("/data/local");
    // Add Same Path
    modelViewNG.AddShaderImageTexture("/data/local");
    EXPECT_EQ(modelPaintProperty->GetModelImageTexturePathsValue().back(), "/data/local");
    modelViewNG.AddShaderImageTexture("/data/local1");

    // case 2 frameNode == nullptr
    modelViewNG.frameNode_.Reset();
    modelViewNG.AddShaderImageTexture("/data/local2");
    EXPECT_EQ(modelPaintProperty->GetModelImageTexturePathsValue().size(), 2);
    modelViewNG.GetShaderInputBuffer();

    modelViewNG.AddCustomRender(desc);
    desc.reset();
    modelViewNG.AddCustomRender(desc);
    modelPattern->modelAdapter_->UpdateCustomRender(modelPaintProperty);
}

/**
 * @tc.name: ModelViewNgTest002
 * @tc.desc: Test ModelAdapterWrapper Functions and SceneAdapter == nullptr
 * @tc.type: FUNC
 */
HWTEST_F(ModelTestNg, ModelViewNgTest002, TestSize.Level1)
{
    // Get FrameNode
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();

    // Get ModelPaintProperty
    auto modelPaintProperty = frameNode->GetPaintProperty<ModelPaintProperty>();
    ASSERT_NE(modelPaintProperty, nullptr);

    // Get ModelPattern
    auto modelPattern = frameNode->GetPattern<ModelPattern>();
    ASSERT_NE(modelPattern, nullptr);

    std::shared_ptr<OHOS::Render3D::ShaderInputBuffer> buffer = nullptr;
    buffer = std::make_shared<OHOS::Render3D::ShaderInputBuffer>();
    int length = 3; // 3: buffer length

    ASSERT_TRUE(buffer->Alloc(length));
    for (uint32_t i = 0; i < static_cast<uint32_t>(length); i++) {
        buffer->Update(1, i);
    }
    FrameNode* frameNode1 = nullptr;
    modelViewNG.AddShaderInputBuffer(frameNode1, buffer);

    // Create SceneAdapter
    modelPattern->modelAdapter_->sceneAdapter_ = std::make_shared<TestSceneAdapter>();
    ASSERT_NE(modelPattern->modelAdapter_->sceneAdapter_, nullptr);

    RefPtr<RenderContext> context;
    modelPattern->modelAdapter_->OnAttachToFrameNode(context);
    modelPattern->modelAdapter_->Deinit();
    Render3D::PointerEvent event;
    modelPattern->modelAdapter_->HandleCameraMove(event);
    modelPattern->modelAdapter_->DrawFrame();
    Render3D::WindowChangeInfo windowChangeInfo {};
    modelPattern->modelAdapter_->OnDirtyLayoutWrapperSwap(windowChangeInfo);
    modelPattern->modelAdapter_->CreateTextureLayer();
    modelPattern->modelAdapter_->CreateWidgetAdapter();
    modelPattern->modelAdapter_->UnloadSceneAndBackground();
    modelPattern->modelAdapter_->UpdateScene(modelPaintProperty);
    modelPattern->modelAdapter_->UpdateEnviroment(modelPaintProperty);
    modelPattern->modelAdapter_->UpdateCustomRender(modelPaintProperty);
    modelPattern->modelAdapter_->UpdateShaderPath(modelPaintProperty);

    modelPattern->modelAdapter_->sceneAdapter_.reset();
    ASSERT_EQ(modelPattern->modelAdapter_->sceneAdapter_, nullptr);
}

/**
 * @tc.name: ModelViewNgTest003
 * @tc.desc: Test ModelViewNG Functions
 * @tc.type: FUNC
 */
HWTEST_F(ModelTestNg, ModelViewNgTest003, TestSize.Level1)
{
    // Get FrameNode
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();

    // Get ModelPaintProperty
    auto modelPaintProperty = frameNode->GetPaintProperty<ModelPaintProperty>();
    ASSERT_NE(modelPaintProperty, nullptr);

    // Get ModelPattern
    auto modelPattern = frameNode->GetPattern<ModelPattern>();
    ASSERT_NE(modelPattern, nullptr);

    // Environment
    modelPattern->modelAdapter_->UpdateEnviroment(modelPaintProperty);
    modelViewNG.SetBackground(testPath);
    EXPECT_EQ(modelPaintProperty->GetModelBackgroundValue(), testPath);
    modelPattern->modelAdapter_->UpdateEnviroment(modelPaintProperty);

    // ModelSource
    modelPattern->modelAdapter_->UpdateScene(modelPaintProperty);
    modelViewNG.SetModelSource(testPath);
    EXPECT_EQ(modelPaintProperty->GetModelSourceValue(), testPath);
    modelPattern->modelAdapter_->UpdateScene(modelPaintProperty);

    // RenderWidth and RenderHeight
    // Case 1 : Value < 0.0f
    CalcDimension value;
    value.SetValue(-1.0f);
    modelViewNG.SetRenderWidth(value);
    value.SetValue(-1.0f);
    modelViewNG.SetRenderHeight(value);

    // Case 2 : Value > 0.0f
    value.SetValue(1.0f);
    modelViewNG.SetRenderWidth(value);
    EXPECT_EQ(modelPaintProperty->GetRenderWidthValue(), 1.0f);
    modelViewNG.SetRenderHeight(value);
    EXPECT_EQ(modelPaintProperty->GetRenderHeightValue(), 1.0f);

    // Shader
    modelPattern->modelAdapter_->UpdateShaderPath(modelPaintProperty);
    modelViewNG.SetShader(testPath);
    EXPECT_EQ(modelPaintProperty->GetShaderPathValue(), testPath);
    modelPattern->modelAdapter_->UpdateShaderPath(modelPaintProperty);

    // HandleCameraMove
    modelViewNG.SetHandleCameraMove(false);
    EXPECT_EQ(modelPaintProperty->GetModelCameraMoveValue(), false);

    // RenderFrameRate
    modelViewNG.SetRenderFrameRate(1.0f);
    EXPECT_EQ(modelPaintProperty->GetRenderFrameRateValue(), 1.0f);
}

/**
 * @tc.name: ModelViewNgTest004
 * @tc.desc: Test ModelPattern Functions
 * @tc.type: FUNC
 */
HWTEST_F(ModelTestNg, ModelViewNgTest004, TestSize.Level1)
{
    // Get FrameNode
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();

    // Get ModelPattern
    auto modelPattern = frameNode->GetPattern<ModelPattern>();
    ASSERT_NE(modelPattern, nullptr);

    // Get ModelPaintProperty
    auto modelPaintProperty = frameNode->GetPaintProperty<ModelPaintProperty>();
    ASSERT_NE(modelPaintProperty, nullptr);

    // OnPaint3D
    // Case 1 : needsSynsPaint_ = true
    modelPattern->modelAdapter_->OnPaint3D(modelPaintProperty);
    // Case 2 : needsSynsPaint_ = false
    modelPattern->modelAdapter_->OnPaint3D(modelPaintProperty);
    modelPattern->modelAdapter_->OnPaintFinish();

    // HdleCameraMove
    Render3D::PointerEvent event;
    modelPattern->modelAdapter_->HandleCameraMove(event);

    // OnAttachToFrameNode
    modelPattern->modelAdapter_->UnloadSceneAndBackground();
    modelPattern->modelAdapter_->widgetAdapter_.reset();
    modelPattern->modelAdapter_->textureLayer_.reset();
    EXPECT_EQ(modelPattern->modelAdapter_->widgetAdapter_, nullptr);
    EXPECT_EQ(modelPattern->modelAdapter_->textureLayer_, nullptr);
    modelPattern->OnAttachToFrameNode();
    modelPattern->modelAdapter_->OnPaint3D(modelPaintProperty);
    EXPECT_NE(modelPattern->modelAdapter_->widgetAdapter_, nullptr);
    EXPECT_NE(modelPattern->modelAdapter_->textureLayer_, nullptr);

    TouchEventInfo touchEventInfo("onTouch");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.touchType_ = TouchType::MOVE;
    touchLocationInfo.localLocation_ = Offset(1.0f, 1.0f);
    touchEventInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo));
    modelPattern->HandleTouchEvent(touchEventInfo);
    EXPECT_NE(modelPattern->CreateNodePaintMethod(), nullptr);

    // OnModifyDone
    modelPattern->OnModifyDone();
    EXPECT_NE(modelPattern->modelAdapter_, nullptr);

    // OnDirtyLayoutWrapperSwap
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetContentSize(SizeF(100.0f, 100.0f));
    geometryNode->SetContentOffset(OffsetF(0.0f, 0.0f));
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(static_cast<WeakPtr<FrameNode>>(frameNode), geometryNode, nullptr);
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->skipMeasureContent_ = std::make_optional(true);
    DirtySwapConfig config;
    EXPECT_FALSE(modelPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
    config.skipMeasure = true;
    EXPECT_FALSE(modelPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
    config.skipLayout = true;
    EXPECT_FALSE(modelPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));

    // MarkDirtyNode
    modelPattern->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

    // OnRebuildFrame
    modelPattern->OnRebuildFrame();
    EXPECT_NE(modelPattern->modelAdapter_->textureLayer_, nullptr);

    // NeedsRepaint
    modelPattern->modelAdapter_->needsRepaint_ = true;
    EXPECT_TRUE(modelPattern->NeedsRepaint());
}

/**
 * @tc.name: ModelViewNgTest005
 * @tc.desc: Test Util Functions
 * @tc.type: FUNC
 */
HWTEST_F(ModelTestNg, ModelViewNgTest005, TestSize.Level1)
{
    // Get FrameNode
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    // Get ModelPattern
    auto modelPattern = frameNode->GetPattern<ModelPattern>();
    ASSERT_NE(modelPattern, nullptr);

    // Get ModelPaintProperty
    auto modelPaintProperty = frameNode->GetPaintProperty<ModelPaintProperty>();
    ASSERT_NE(modelPaintProperty, nullptr);

    // SetHapInfo
    Render3D::HapInfo hapinfo = modelPattern->modelAdapter_->SetHapInfo();
    EXPECT_EQ(hapinfo.hapPath_, "");
    EXPECT_EQ(hapinfo.bundleName_, "");
    EXPECT_EQ(hapinfo.moduleName_, "");

    const InspectorFilter filter1;
    auto json1 = JsonUtil::Create(true);
    modelPattern->ToJsonValue(json1, filter1);
    ASSERT_NE(json1, nullptr);
    EXPECT_EQ(json1->GetString("renderWidth"), "1.000000");
    EXPECT_EQ(json1->GetString("renderHeight"), "1.000000");
    EXPECT_EQ(json1->GetString("shaderInputBuffer"), "1.000000 1.000000 1.000000 ");
    EXPECT_EQ(json1->GetString("shaderImageTexture"), "/data/local /data/local1 ");
    EXPECT_EQ(json1->GetString("modelType"), "ModelType.SURFACE");
    EXPECT_EQ(json1->GetString("environment"), testPath);
    EXPECT_EQ(json1->GetString("customRender"), testPath);
    EXPECT_EQ(json1->GetString("shader"), testPath);
    EXPECT_EQ(json1->GetString("scene"), testPath);

    modelPattern->modelAdapter_->surfaceType_ = Render3D::SurfaceType::SURFACE_TEXTURE;
    const InspectorFilter filter2;
    auto json2 = JsonUtil::Create(true);
    modelPattern->ToJsonValue(json2, filter2);

    modelPattern->modelAdapter_->surfaceType_ = Render3D::SurfaceType::UNDEFINE;
    const InspectorFilter filter3;
    auto json3 = JsonUtil::Create(true);
    modelPattern->ToJsonValue(json3, filter3);

    modelPattern->modelAdapter_->surfaceType_ = Render3D::SurfaceType::SURFACE_BUFFER;
    const InspectorFilter filter4;
    auto json4 = JsonUtil::Create(true);
    modelPattern->ToJsonValue(json4, filter4);

    auto ftr = modelPattern->modelAdapter_->Deinit();
    if (ftr.valid()) {
        ftr.get();
    }
    Render3D::GraphicsTask::GetInstance().Stop();
}

/**
 * @tc.name: ModelViewNgTest006
 * @tc.desc: Test ModelTouchHandler Functions
 * @tc.type: FUNC
 */
HWTEST_F(ModelTestNg, ModelViewNgTest006, TestSize.Level1)
{
    ModelTouchHandler modelTouchHandler;
    TouchEventInfo touchEventInfo("onTouch");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.touchType_ = TouchType::DOWN;
    touchLocationInfo.localLocation_ = Offset(1.0f, 1.0f);
    touchEventInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo));
    EXPECT_EQ(modelTouchHandler.HandleTouchEvent(touchEventInfo, 1, 1), false);

    touchEventInfo.changedTouches_.clear();
    touchLocationInfo.touchType_ = TouchType::MOVE;
    touchEventInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo));
    EXPECT_EQ(modelTouchHandler.HandleTouchEvent(touchEventInfo, 1, 1), false);

    modelTouchHandler.isHandleCameraMove_ = false;
    touchEventInfo.changedTouches_.clear();
    touchLocationInfo.touchType_ = TouchType::UP;
    touchEventInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo));
    EXPECT_EQ(modelTouchHandler.HandleTouchEvent(touchEventInfo, 1, 1), false);

    touchEventInfo.changedTouches_.clear();
    touchLocationInfo.touchType_ = TouchType::CANCEL;
    touchEventInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo));
    EXPECT_EQ(modelTouchHandler.HandleTouchEvent(touchEventInfo, 1, 1), true);

    touchEventInfo.changedTouches_.clear();
    touchLocationInfo.touchType_ = TouchType::UNKNOWN;
    touchEventInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo));
    EXPECT_EQ(modelTouchHandler.HandleTouchEvent(touchEventInfo, 1, 1), true);
    EXPECT_EQ(modelTouchHandler.HandleTouchEvent(touchEventInfo, 1, 0), true);
    EXPECT_EQ(modelTouchHandler.HandleTouchEvent(touchEventInfo, 0, 0), true);
}
} // namespace OHOS::Ace::NG

