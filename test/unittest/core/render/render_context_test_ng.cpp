/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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
#include "gmock/gmock.h"

#include "base/utils/utils.h"
#define protected public
#define private public
#include "core/components_ng/render/render_context.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
std::string srcimages = "test";
constexpr char TAG_ROOT[] = "root";
const std::string MATRIX_STRING1 = "1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,";
const std::string MATRIX_STRING2 = "0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,";
const float VALUE = 1.0f;
const float MAXVALUE = 200.0f;
const Color RED = Color(0xffff0000);
const Color BLACK = Color(0xff000000);
const Color WHITE = Color(0xffffffff);

constexpr Dimension ZERO_TEST {0.0f, DimensionUnit::PX};
constexpr Dimension LEFT_TEST {10.0f, DimensionUnit::PX};
constexpr Dimension TOP_TEST {20.0f, DimensionUnit::PX};
constexpr Dimension RIGHT_TEST {30.0f, DimensionUnit::PX};
constexpr Dimension BOTTOM_TEST {40.0f, DimensionUnit::PX};

RefPtr<NG::ProgressMaskProperty> CreateProgressMaskProperty()
{
    RefPtr<NG::ProgressMaskProperty> progressMaskProperty = AceType::MakeRefPtr<NG::ProgressMaskProperty>();
    progressMaskProperty->SetMaxValue(MAXVALUE);
    progressMaskProperty->SetColor(RED);
    progressMaskProperty->SetValue(VALUE);
    return progressMaskProperty;
};

void MakeProperty(NG::RenderContext& renderContext)
{
    renderContext.propBorder_ = std::make_unique<NG::BorderProperty>();
    renderContext.propBdImage_ = std::make_unique<NG::BorderImageProperty>();
    renderContext.propOverlay_ = std::make_unique<NG::OverlayProperty>();
    renderContext.propPositionProperty_ = std::make_unique<NG::RenderPositionProperty>();
    renderContext.propBackground_ = std::make_unique<NG::BackgroundProperty>();
    renderContext.propGraphics_ = std::make_unique<NG::GraphicsProperty>();
    renderContext.propGradient_ = std::make_unique<NG::GradientProperty>();
    renderContext.propTransform_ = std::make_unique<NG::TransformProperty>();
    renderContext.propClip_ = std::make_unique<NG::ClipProperty>();
};
}

class RenderContextTestNg : public testing::Test {};

/**
 * @tc.name: RenderContextTest001
 * @tc.desc: Test cast to RenderContextTestNg
 * @tc.type: FUNC
 */
HWTEST_F(RenderContextTestNg, RenderContextTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object renderContext.
     */
    NG::RenderContext renderContext;
    auto requestFrame = []() {
        srcimages = "common/images/mmm.jpg";
    };

    /**
     * @tc.steps: step2. callback SetRequestFrame.
     * @tc.expected: step2. The renderContext.requestFrame_ is not null.
     */
    renderContext.SetRequestFrame(requestFrame);
    EXPECT_EQ(srcimages, "test");
    ASSERT_NE(renderContext.requestFrame_, nullptr);
}

/**
 * @tc.name: RenderContextTest002
 * @tc.desc: Test cast to RenderContextTestNg
 * @tc.type: FUNC
 */
HWTEST_F(RenderContextTestNg, RenderContextTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object renderContext.
     */
    NG::RenderContext renderContext;
    auto requestFrame = []() {
        srcimages = "common/images/mmm.jpg";
    };

    /**
     * @tc.steps: step2. callback RequestNextFrame.
     * @tc.expected: step2. The renderContext.requestFrame_ is null.
     */
    renderContext.RequestNextFrame();
    EXPECT_EQ(srcimages, "test");
    EXPECT_EQ(renderContext.requestFrame_, nullptr);

    /**
     * @tc.steps: step3. callback RequestNextFrame.
     * @tc.expected: step3. The renderContext.requestFrame_ is not null.
     */
    renderContext.SetRequestFrame(requestFrame);
    renderContext.RequestNextFrame();
    EXPECT_EQ(srcimages, "common/images/mmm.jpg");
    ASSERT_NE(renderContext.requestFrame_, nullptr);
}

/**
 * @tc.name: RenderContextTest003
 * @tc.desc: Test cast to RenderContextTestNg
 * @tc.type: FUNC
 */
HWTEST_F(RenderContextTestNg, RenderContextTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object renderContext.
     */
    NG::RenderContext renderContext;
    auto rowFrameNode =
        NG::FrameNode::CreateFrameNode(TAG_ROOT, 0, AceType::MakeRefPtr<NG::LinearLayoutPattern>(false));

    /**
     * @tc.steps: step2. callback GetHost.
     * @tc.expected: step2. expected result is null.
     */
    RefPtr<NG::FrameNode> result = renderContext.GetHost();
    EXPECT_EQ(result, nullptr);

    /**
     * @tc.steps: step2. callback SetHostNode.
     * @tc.expected: step2. The renderContext.host_ = rowFrameNode.
     * @tc.expected: step2. The renderContext.host_.Upgrade() is not null.
     */
    renderContext.SetHostNode(rowFrameNode);
    EXPECT_EQ(renderContext.host_, rowFrameNode);
    ASSERT_NE(renderContext.host_.Upgrade(), nullptr);

    /**
     * @tc.steps: step3. callback GetHost.
     * @tc.expected: step3. expected results is not null.
     */
    RefPtr<NG::FrameNode> results = renderContext.GetHost();
    ASSERT_NE(results, nullptr);
}

/**
 * @tc.name: RenderContextTest004
 * @tc.desc: Test cast to RenderContextTestNg
 * @tc.type: FUNC
 */
HWTEST_F(RenderContextTestNg, RenderContextTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object renderContext.
     */
    NG::RenderContext renderContext;

    /**
     * @tc.steps: step2. callback ToJsonValue.push propTransformMatrix_ is null.
     * @tc.steps: step2. push propProgressMask_ is null.push propPixelStretchEffect_ is null.
     */
    auto json = JsonUtil::Create(true);
    renderContext.ToJsonValue(json);

    /**
     * @tc.expected: Return expected results..
     */
    EXPECT_EQ(json->GetString("total"), "");
    EXPECT_EQ(json->GetString("updateProgress"), "");
    EXPECT_EQ(json->GetString("updateColor"), "");
    EXPECT_EQ(json->GetValue("pixelStretchEffect")->GetString("left"), ZERO_TEST.ToString());
    EXPECT_EQ(json->GetValue("pixelStretchEffect")->GetString("right"), ZERO_TEST.ToString());
    EXPECT_EQ(json->GetValue("pixelStretchEffect")->GetString("top"), ZERO_TEST.ToString());
    EXPECT_EQ(json->GetValue("pixelStretchEffect")->GetString("bottom"), ZERO_TEST.ToString());
    EXPECT_EQ(json->GetString("backgroundColor"), "#00000000");
    EXPECT_EQ(json->GetString("foregroundColor"), "#00000001");
    EXPECT_EQ(json->GetString("transform"), "");
}

/**
 * @tc.name: RenderContextTest005
 * @tc.desc: Test cast to RenderContextTestNg
 * @tc.type: FUNC
 */
HWTEST_F(RenderContextTestNg, RenderContextTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object renderContext.
     */
    NG::RenderContext renderContext;
    auto json = JsonUtil::Create(true);

    /**
     * @tc.steps: step2. callback ToJsonValue.push propProgressMask_ is not null.
     */
    MakeProperty(renderContext);
    renderContext.propProgressMask_ = CreateProgressMaskProperty();
    renderContext.ToJsonValue(json);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(json->GetString("total"), "");
    EXPECT_EQ(json->GetString("updateProgress"), "");
    EXPECT_EQ(json->GetString("updateColor"), "#FFFF0000");
}

/**
 * @tc.name: RenderContextTest006
 * @tc.desc: Test cast to RenderContextTestNg
 * @tc.type: FUNC
 */
HWTEST_F(RenderContextTestNg, RenderContextTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object renderContext.
     */
    NG::RenderContext renderContext;
    auto json = JsonUtil::Create(true);

    PixStretchEffectOption pixStretchEffectOption;
    pixStretchEffectOption.bottom = BOTTOM_TEST;
    pixStretchEffectOption.left = LEFT_TEST;
    pixStretchEffectOption.right= RIGHT_TEST;
    pixStretchEffectOption.top = TOP_TEST;

    /**
     * @tc.steps: step2. callback ToJsonValue.push propPixelStretchEffect_ is not null.
     */
    MakeProperty(renderContext);
    renderContext.propPixelStretchEffect_ = std::move(pixStretchEffectOption);
    renderContext.ToJsonValue(json);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(json->GetValue("pixelStretchEffect")->GetString("left"), LEFT_TEST.ToString());
    EXPECT_EQ(json->GetValue("pixelStretchEffect")->GetString("right"), RIGHT_TEST.ToString());
    EXPECT_EQ(json->GetValue("pixelStretchEffect")->GetString("top"), TOP_TEST.ToString());
    EXPECT_EQ(json->GetValue("pixelStretchEffect")->GetString("bottom"), BOTTOM_TEST.ToString());
}

/**
 * @tc.name: RenderContextTest007
 * @tc.desc: Test cast to RenderContextTestNg
 * @tc.type: FUNC
 */
HWTEST_F(RenderContextTestNg, RenderContextTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object renderContext.
     */
    NG::RenderContext renderContext;
    auto json = JsonUtil::Create(true);

    /**
     * @tc.steps: step2. callback ToJsonValue.push propBackgroundColor_ is BLACK.
     * @tc.steps: step2. push propForegroundColor_ is WHITE.
     */
    MakeProperty(renderContext);
    renderContext.propBackgroundColor_ = BLACK;
    renderContext.propForegroundColor_ = WHITE;
    renderContext.ToJsonValue(json);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(json->GetString("backgroundColor"), "#FF000000");
    EXPECT_EQ(json->GetString("foregroundColor"), "#FFFFFFFF");
}

/**
 * @tc.name: RenderContextTest008
 * @tc.desc: Test cast to RenderContextTestNg
 * @tc.type: FUNC
 */
HWTEST_F(RenderContextTestNg, RenderContextTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object renderContext.
     */
    NG::RenderContext renderContext;
    auto json = JsonUtil::Create(true);

    /**
     * @tc.steps: step2. callback ToJsonValue.push propTransformMatrix_ is CreateIdentity.
     */
    MakeProperty(renderContext);
    renderContext.propTransformMatrix_ = Matrix4::CreateIdentity();;
    renderContext.ToJsonValue(json);

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(json->GetValue("transform")->GetString("type"), "matrix");
    EXPECT_EQ(json->GetValue("transform")->GetString("matrix"), MATRIX_STRING1 + MATRIX_STRING2);
}
} // namespace OHOS::Ace
