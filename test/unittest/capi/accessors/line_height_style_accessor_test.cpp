/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "frameworks/core/interfaces/native/implementation/length_metrics_peer.h"
#include "core/interfaces/native/implementation/line_height_style_peer.h"
#include "accessor_test_base.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

static constexpr int TEST_HEIGHT = 100;

class LineHeightStyleAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUILineHeightStyleAccessor,
        &GENERATED_ArkUIAccessors::getLineHeightStyleAccessor, LineHeightStylePeer> {
public:
    void* CreatePeerInstance() override
    {
        auto metrics = Converter::ArkValue<Ark_LengthMetrics>(Dimension(TEST_HEIGHT));
        return accessor_->construct(&metrics);
    }
};

/**
 * @tc.name: getLineHeightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(LineHeightStyleAccessorTest, getLineHeightTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getLineHeight, nullptr);
    auto retHeight = accessor_->getLineHeight(peer_);
    int ret = Converter::Convert<int>(retHeight);
    EXPECT_EQ(ret, TEST_HEIGHT);
}

} // namespace OHOS::Ace::NG