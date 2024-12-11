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

#include "core/interfaces/native/implementation/layout_manager_peer_impl.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const std::string g_message = "message";

class LayoutManagerAccessorTest : public AccessorTestCtorBase<GENERATED_ArkUILayoutManagerAccessor,
    &GENERATED_ArkUIAccessors::getLayoutManagerAccessor, LayoutManagerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestCtorBase::SetUp();
        peer_->handler = new LayoutInfoInterface();
    }
    LayoutManagerPeer* CreatePeerInstance() override
    {
        return accessor_->ctor();
    }
};
/**
 * @tc.name: getLineCountTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LayoutManagerAccessorTest, getLineCountTest, TestSize.Level1)
{
    ASSERT_NE(accessor_, nullptr);
    ASSERT_NE(peer_, nullptr);
    auto value = accessor_->getLineCount(peer_);
    ASSERT_EQ(value, 0);
    value = accessor_->getLineCount(nullptr);
    ASSERT_EQ(value, 0);
}

/**
 * @tc.name: GetGlyphPositionAtCoordinate
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LayoutManagerAccessorTest, DISABLED_GetGlyphPositionAtCoordinate, TestSize.Level1)
{
    Ark_Number valueX = Converter::ArkValue<Ark_Number>(33);
    Ark_Number valueY = Converter::ArkValue<Ark_Number>(55);
    ASSERT_NE(accessor_->getGlyphPositionAtCoordinate(peer_, &valueX, &valueY), nullptr);
}

/**
 * @tc.name: GetLineMetrics
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LayoutManagerAccessorTest, DISABLED_GetLineMetrics, TestSize.Level1)
{
    Ark_Number lineNumber = Converter::ArkValue<Ark_Number>(55);
    ASSERT_NE(accessor_->getLineMetrics(peer_, &lineNumber), nullptr);
}

/**
 * @tc.name: GetRectsForRange
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LayoutManagerAccessorTest, DISABLED_GetRectsForRange, TestSize.Level1)
{
    ASSERT_NE(accessor_, nullptr);
    ASSERT_NE(peer_, nullptr);

    Ark_TextRange range {
        .start = Converter::ArkValue<Opt_Number>(5),
        .end = Converter::ArkValue<Opt_Number>(7)
    };
    Ark_RectWidthStyle valueX = Converter::ArkValue<Ark_RectWidthStyle>(ARK_RECT_WIDTH_STYLE_MAX);
    Ark_RectHeightStyle valueY = Converter::ArkValue<Ark_RectHeightStyle>(ARK_RECT_HEIGHT_STYLE_STRUT);
    accessor_->getRectsForRange(peer_, &range, valueX, valueY);
}
}

} // namespace OHOS::Ace::NG