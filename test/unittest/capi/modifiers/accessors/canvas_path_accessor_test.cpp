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

#include "gmock/gmock.h"

#include "accessor_test_base.h"
#include "frameworks/base/utils/utils.h"
#include "node_api.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/canvas_gradient_peer.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using ::testing::NiceMock;

namespace {
const auto DEFAULT_COLORS_SIZE = 2;
std::vector < std::tuple<float, std::string, double, Color>> gradientTestPlan = {
    { 0.50f, "#FFFFFFFF", 0.5, Color::WHITE },
    { 12.34f, "#FF000000", 0.00, Color::TRANSPARENT },
    { -56.73f, "#FF0000FF", 0.00, Color::TRANSPARENT },
    { 0.50f, "invalid color", 0.00, Color::TRANSPARENT },
    { 0.50f, "", 0.00, Color::TRANSPARENT },
};
} // namespace

class CanvasGradientAccessorTest : public AccessorTestBase<GENERATED_ArkUICanvasGradientAccessor,
    &GENERATED_ArkUIAccessors::getCanvasGradientAccessor, CanvasGradientPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        canvasGradient_ = std::make_shared<OHOS::Ace::Gradient>();
        ASSERT_NE(canvasGradient_, nullptr);
        ASSERT_NE(peer_, nullptr);
        peer_->SetGradient(canvasGradient_);
    }
    void TearDown() override
    {
        canvasGradient_ = nullptr;
    }
    std::shared_ptr<OHOS::Ace::Gradient> canvasGradient_ = nullptr;
};

/**
 * @tc.name: addColorStopTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasGradientAccessorTest, addColorStopTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->addColorStop, nullptr);
    std::shared_ptr<OHOS::Ace::Gradient> gradient = peer_->GetGradient();
    for (const auto& [offset, color, expectedOffset, expectedColor] : gradientTestPlan) {
        Ark_Number arkOffset = Converter::ArkValue<Ark_Number>(offset);
        Ark_String arkColor = Converter::ArkValue<Ark_String>(color);
        auto color = Converter::ArkUnion<Ark_Union_String_ColorMetrics, Ark_String>(arkColor);
        gradient->ClearColors();
        accessor_->addColorStop(peer_, &arkOffset, &color);
        auto colors = gradient->GetColors();
        EXPECT_EQ(colors.size(), DEFAULT_COLORS_SIZE);
        for (const auto& color : gradient->GetColors()) {
            EXPECT_TRUE(LessOrEqualCustomPrecision(color.GetDimension().Value(), expectedOffset));
            EXPECT_EQ(color.GetColor().ToString(), expectedColor.ToString());
        }
    }
}
} // namespace OHOS::Ace::NG
