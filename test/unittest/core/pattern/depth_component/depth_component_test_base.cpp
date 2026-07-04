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

#include "depth_component_test_base.h"

namespace OHOS::Ace::NG {

void DepthComponentTestBase::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
}

void DepthComponentTestBase::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

RefPtr<FrameNode> DepthComponentTestBase::CreateNode(const OHOS::Ace::DepthBackgroundSource& background)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    return DepthComponentModel::CreateFrameNode(nodeId, background);
}

RefPtr<FrameNode> DepthComponentTestBase::CreateNodeWithTag(const std::string& tag, int32_t nodeId)
{
    return FrameNode::CreateFrameNode(tag, nodeId, AceType::MakeRefPtr<DepthComponentPattern>());
}

OHOS::Ace::DepthBackgroundSource DepthComponentTestBase::MakeImageSource(const std::string& src)
{
    return OHOS::Ace::DepthBackgroundSource::CreateImage(
        ImageSourceInfo(src, "com.test.bundle", "entry"), src, "com.test.bundle", "entry");
}

OHOS::Ace::DepthBackgroundSource DepthComponentTestBase::MakeSvgSource(const std::string& src)
{
    return OHOS::Ace::DepthBackgroundSource::CreateImage(
        ImageSourceInfo(src, "com.test.bundle", "entry"), src, "com.test.bundle", "entry");
}

OHOS::Ace::DepthBackgroundSource DepthComponentTestBase::MakeGltfSource(const std::string& path)
{
    return OHOS::Ace::DepthBackgroundSource::CreateGltf(path, path, "com.test.bundle", "entry");
}

OHOS::Ace::DepthCameraParams DepthComponentTestBase::MakeCamera(float yFov, bool withCrop)
{
    OHOS::Ace::DepthCameraParams camera;
    camera.position = OHOS::Ace::DepthVector3 { 0.0f, 0.0f, 5.0f };
    camera.quaternion = OHOS::Ace::DepthVector4 { 0.0f, 0.0f, 0.0f, 1.0f };
    camera.yFov = yFov;
    camera.zNear = 0.1f;
    camera.zFar = 100.0f;
    if (withCrop) {
        camera.cameraBufferCrop = MakeCrop(200, 200, 0.5f, 10.0f, 20.0f);
    }
    return camera;
}

OHOS::Ace::DepthLightParams DepthComponentTestBase::MakeLight()
{
    OHOS::Ace::DepthLightParams light;
    light.direction = OHOS::Ace::DepthVector3 { 0.0f, 0.0f, -1.0f };
    light.color = OHOS::Ace::DepthColorRGB { 255, 255, 255 };
    light.intensity = 1.0f;
    return light;
}

OHOS::Ace::CameraBufferCrop DepthComponentTestBase::MakeCrop(int32_t w, int32_t h, float scale, float ox, float oy)
{
    OHOS::Ace::CameraBufferCrop crop;
    crop.bufferWidth = w;
    crop.bufferHeight = h;
    crop.cropScale = scale;
    crop.cropOffset = OHOS::Ace::CropOffset { ox, oy };
    return crop;
}

std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> DepthComponentTestBase::CreateMeasureableNode(
    const OHOS::Ace::DepthBackgroundSource& background)
{
    auto host = CreateNode(background);
    EXPECT_NE(host, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->Reset();
    RefPtr<LayoutWrapperNode> wrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(host, geometryNode, host->GetLayoutProperty());
    auto pattern = host->GetPattern<DepthComponentPattern>();
    EXPECT_NE(pattern, nullptr);
    wrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(pattern->CreateLayoutAlgorithm()));
    LayoutConstraintF constraint;
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    constraint.percentReference = SizeF(1000.0f, 1000.0f);
    wrapper->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    wrapper->GetLayoutProperty()->UpdateContentConstraint();
    return { host, wrapper };
}

RefPtr<LayoutWrapperNode> DepthComponentTestBase::AppendChildWrapper(
    const RefPtr<FrameNode>& host, float width, float height)
{
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto child = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, childId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    EXPECT_NE(child, nullptr);
    host->AddChild(child);
    auto childGeo = AceType::MakeRefPtr<GeometryNode>();
    childGeo->Reset();
    childGeo->SetFrameSize(SizeF(width, height));
    RefPtr<LayoutWrapperNode> childWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(child, childGeo, child->GetLayoutProperty());
    auto childPattern = child->GetPattern<ImagePattern>();
    if (childPattern) {
        childWrapper->SetLayoutAlgorithm(
            AceType::MakeRefPtr<LayoutAlgorithmWrapper>(childPattern->CreateLayoutAlgorithm()));
    }
    return childWrapper;
}
} // namespace OHOS::Ace::NG
