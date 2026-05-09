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

#include <optional>
#include <utility>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "core/components_ng/pattern/shape/circle_paint_method.h"
#include "core/components_ng/render/paint_wrapper.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
class CircleHdrTestRenderContext final : public RenderContext {
    DECLARE_ACE_TYPE(CircleHdrTestRenderContext, RenderContext);
public:
    void SetHDRColorHeadRoom(float headRoom) override
    {
        ++hdrHeadRoomCallCount_;
        lastHdrHeadRoom_ = headRoom;
    }

    int32_t hdrHeadRoomCallCount_ = 0;
    float lastHdrHeadRoom_ = 0.0f;
};
} // namespace

class CircleHdrRuntimeTestNg : public testing::Test {
public:
};

/**
 * @tc.name: CirclePaintMethodHeadRoom001
 * @tc.desc: Verify fill/stroke headroom propagation branches in CirclePaintMethod.
 * @tc.type: FUNC
 */
HWTEST_F(CircleHdrRuntimeTestNg, CirclePaintMethodHeadRoom001, TestSize.Level0)
{
    constexpr float width = 200.0f;
    constexpr float height = 300.0f;
    constexpr float fillHeadRoom = 2.0f;
    constexpr float strokeHeadRoom = 3.0f;

    auto makeWrapper = [&](const Color& fillColor, const std::optional<Color>& strokeColor) {
        auto testRenderContext = AceType::MakeRefPtr<CircleHdrTestRenderContext>();
        auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
        geometryNode->SetContentSize(SizeF(width, height));
        auto shapePaintProperty = AceType::MakeRefPtr<ShapePaintProperty>();
        shapePaintProperty->UpdateFill(fillColor);
        if (strokeColor.has_value()) {
            shapePaintProperty->UpdateStroke(strokeColor.value());
        }
        auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(testRenderContext, geometryNode, shapePaintProperty);
        return std::make_pair(testRenderContext, paintWrapper);
    };

    {
        auto [testRenderContext, paintWrapper] =
            makeWrapper(Color::FromFloat(0.8f, 0.6f, 0.4f, 1.0f, fillHeadRoom), std::nullopt);
        CirclePaintMethod paintMethod;
        auto drawFunction = paintMethod.GetContentDrawFunction(AceType::RawPtr(paintWrapper));
        EXPECT_NE(drawFunction, nullptr);
        EXPECT_EQ(testRenderContext->hdrHeadRoomCallCount_, 1);
        EXPECT_FLOAT_EQ(testRenderContext->lastHdrHeadRoom_, fillHeadRoom);
    }

    {
        Color bt2020Color(0xFF112233);
        bt2020Color.SetColorSpace(ColorSpace::BT2020);
        auto [testRenderContext, paintWrapper] = makeWrapper(
            bt2020Color, Color::FromFloat(1.0f, 0.0f, 0.0f, 1.0f, strokeHeadRoom));
        CirclePaintMethod paintMethod;
        auto drawFunction = paintMethod.GetContentDrawFunction(AceType::RawPtr(paintWrapper));
        EXPECT_NE(drawFunction, nullptr);
        EXPECT_EQ(testRenderContext->hdrHeadRoomCallCount_, 2);
        EXPECT_FLOAT_EQ(testRenderContext->lastHdrHeadRoom_, strokeHeadRoom);
    }

    {
        auto [testRenderContext, paintWrapper] = makeWrapper(Color::BLACK, Color::RED);
        CirclePaintMethod paintMethod;
        auto drawFunction = paintMethod.GetContentDrawFunction(AceType::RawPtr(paintWrapper));
        EXPECT_NE(drawFunction, nullptr);
        EXPECT_EQ(testRenderContext->hdrHeadRoomCallCount_, 1);
        EXPECT_FLOAT_EQ(testRenderContext->lastHdrHeadRoom_, 1.0f);
    }
}
} // namespace OHOS::Ace::NG
