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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_DEPTH_COMPONENT_DEPTH_COMPONENT_TEST_BASE_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_DEPTH_COMPONENT_DEPTH_COMPONENT_TEST_BASE_H

#include <utility>

#include "gtest/gtest.h"

// test_ng.h opens `private`/`protected` for the whole TU, so the private helpers
// of DepthComponentPattern (SetupBackgroundImageNode / ApplyBackgroundImageMatrix /
// ComputeTiltShift / GetEffectiveCameraBufferCrop / ...) become directly reachable.
#define private public
#define protected public
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components/common/properties/depth_option.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/depth_component/depth_component_event_hub.h"
#include "core/components_ng/pattern/depth_component/depth_component_layout_algorithm.h"
#include "core/components_ng/pattern/depth_component/depth_component_layout_property.h"
#include "core/components_ng/pattern/depth_component/depth_component_model.h"
#include "core/components_ng/pattern/depth_component/depth_component_paint_method.h"
#include "core/components_ng/pattern/depth_component/depth_component_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/image/image_source_info.h"
#include "core/pipeline/base/element_register.h"
#undef private
#undef protected

namespace OHOS::Ace::NG {
// Background source descriptors used across the suite.
constexpr const char* DEPTH_IMAGE_SRC = "https://example.com/bg.png";
constexpr const char* DEPTH_SVG_SRC = "https://example.com/bg.svg";
constexpr const char* DEPTH_GLTF_PATH = "/data/test/scene.gltf";

// Default sizes mirroring the layout algorithm constants.
constexpr float DEFAULT_DEPTH_COMPONENT_WIDTH = 640.0f;
constexpr float DEFAULT_DEPTH_COMPONENT_HEIGHT = 480.0f;

// Test fixture shared by all DepthComponent TDD files. Inherits the mock
// pipeline/container setup from TestNG and adds DepthComponent-specific helpers.
class DepthComponentTestBase : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

    // Build a DepthComponent FrameNode directly from the model layer (exercises
    // DepthComponentModel::CreateFrameNode). Each call yields a fresh node id.
    static RefPtr<FrameNode> CreateNode(const OHOS::Ace::DepthBackgroundSource& background);
    // Low-level constructor that bypasses the model (for null-pattern scenarios).
    static RefPtr<FrameNode> CreateNodeWithTag(const std::string& tag, int32_t nodeId);

    // Background source factories covering the three DepthBackgroundSource::Type values.
    static OHOS::Ace::DepthBackgroundSource MakeImageSource(const std::string& src = DEPTH_IMAGE_SRC);
    static OHOS::Ace::DepthBackgroundSource MakeSvgSource(const std::string& src = DEPTH_SVG_SRC);
    static OHOS::Ace::DepthBackgroundSource MakeGltfSource(const std::string& path = DEPTH_GLTF_PATH);

    // Camera / light parameter factories.
    static OHOS::Ace::DepthCameraParams MakeCamera(float yFov, bool withCrop);
    static OHOS::Ace::DepthLightParams MakeLight();
    static OHOS::Ace::CameraBufferCrop MakeCrop(int32_t w, int32_t h, float scale, float ox, float oy);

    // Construct a LayoutWrapperNode owned by host for LayoutAlgorithm branch tests.
    // Returns the host frame node + its wrapper pair.
    static std::pair<RefPtr<FrameNode>, RefPtr<LayoutWrapperNode>> CreateMeasureableNode(
        const OHOS::Ace::DepthBackgroundSource& background);
    // Append a measurable child wrapper (used to exercise wrap-content sizing).
    static RefPtr<LayoutWrapperNode> AppendChildWrapper(
        const RefPtr<FrameNode>& host, float width, float height);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_DEPTH_COMPONENT_DEPTH_COMPONENT_TEST_BASE_H
