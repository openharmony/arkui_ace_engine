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
#include "node_api.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "core/interfaces/native/implementation/canvas_gradient_peer.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using ::testing::NiceMock;

namespace {
struct MockCanvasGradientPeer : public CanvasGradientPeer {
    MockCanvasGradientPeer() = default;
    ~MockCanvasGradientPeer() override = default;
    MOCK_METHOD(void, AddColorStop, (const float&, const Color&), (override));
};
std::vector < std::tuple<float, std::string, float, Color>> GRADIENT_TEST_PLAN = {
    { 0.50f, "#FFFFFFFF", 0.5f, Color::WHITE },
    { 12.34f, "#FF000000", 12.34f, Color::BLACK },
    { -56.73f, "#FF0000FF", -56.73f, Color::BLUE },
    { 0.50f, "invalid color", -1.0f, Color::TRANSPARENT },
    { 0.00f, "#FF0000FF", -1.0f, Color::TRANSPARENT },
    { 0.50f, "", -1.0f, Color::TRANSPARENT },
    { 0.00f, "", -1.0f, Color::TRANSPARENT },
};
} // namespace

class CanvasGradientAccessorTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        ASSERT_NE(accessor_, nullptr);
        ASSERT_NE(accessor_->ctor, nullptr);
        finalyzer_ = reinterpret_cast<void (*)(MockCanvasGradientPeer *)>(accessor_->getFinalizer());
        ASSERT_NE(accessor_->getFinalizer, nullptr);
    }
    virtual void SetUp()
    {
        ASSERT_NE(finalyzer_, nullptr);
    }
    virtual void TearDown()
    {
        FinalizePeer();
    }
    void FinalizePeer()
    {
        if (peer_) {
            ASSERT_NE(finalyzer_, nullptr);
            finalyzer_(peer_);
            peer_ = nullptr;
        }
    }
private:
    inline static const GENERATED_ArkUIFullNodeAPI *fullAPI_
        = reinterpret_cast<const GENERATED_ArkUIFullNodeAPI *>(
            GENERATED_GetArkAnyAPI(GENERATED_Ark_APIVariantKind::GENERATED_FULL, GENERATED_ARKUI_FULL_API_VERSION)
        );
public:
    inline static const GENERATED_ArkUICanvasGradientAccessor *accessor_ =
        fullAPI_->getAccessors()->getCanvasGradientAccessor();
    inline static void (*finalyzer_)(MockCanvasGradientPeer *) = nullptr;
    MockCanvasGradientPeer *peer_ = nullptr;
};

/**
 * @tc.name: addColorStopTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasGradientAccessorTest, addColorStopTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->addColorStop, nullptr);
    NiceMock<MockCanvasGradientPeer>*  peer_ = new NiceMock<MockCanvasGradientPeer>();
    ASSERT_NE(peer_, nullptr);

    for (const auto& [offset, color, expectedOffset, expectedColor] : GRADIENT_TEST_PLAN) {
        Ark_Number arkOffset = Converter::ArkValue<Ark_Number>(offset);
        Ark_String arkColor = Converter::ArkValue<Ark_String>(color);

        EXPECT_CALL(*peer_, AddColorStop(expectedOffset, expectedColor)).Times(1);
        if (NearZero(offset) && color.length() == 0) {
            accessor_->addColorStop(peer_, nullptr, nullptr);
        } else if (NearZero(offset)) {
            accessor_->addColorStop(peer_, nullptr, &arkColor);
        } else if (color.length() == 0) {
            accessor_->addColorStop(peer_, &arkOffset, nullptr);
        } else {
            accessor_->addColorStop(peer_, &arkOffset, &arkColor);
        }
    }
    delete(peer_);
}
} // namespace OHOS::Ace::NG
