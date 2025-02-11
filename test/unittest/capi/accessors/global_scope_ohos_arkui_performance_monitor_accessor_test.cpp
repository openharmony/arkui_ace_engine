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

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using ::testing::NiceMock;

namespace {
// const auto DEFAULT_COLORS_SIZE = 2;
// std::vector < std::tuple<float, std::string, double, Color>> gradientTestPlan = {
//     { 0.50f, "#FFFFFFFF", 0.5, Color::WHITE },
//     { 12.34f, "#FF000000", 0.00, Color::TRANSPARENT },
//     { -56.73f, "#FF0000FF", 0.00, Color::TRANSPARENT },
//     { 0.50f, "invalid color", 0.00, Color::TRANSPARENT },
//     { 0.50f, "", 0.00, Color::TRANSPARENT },
// };
} // namespace

class GlobalScope_ohos_arkui_performanceMonitorAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIGlobalScope_ohos_arkui_performanceMonitorAccessor,
          &GENERATED_ArkUIAccessors::getGlobalScope_ohos_arkui_performanceMonitorAccessor,
          GlobalScope_ohos_arkui_performanceMonitorPeer> {
public:
    void SetUp(void) override
    {
        ASSERT_NE(this->accessor_->ctor, nullptr);
        this->peer_ = static_cast<GlobalScope_ohos_arkui_performanceMonitorPeer*>(this->accessor_->ctor());
        ASSERT_EQ(this->peer_, nullptr);

        printf("perfMonitor: test setup\n");
    }
};

/**
 * @tc.name: beginTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScope_ohos_arkui_performanceMonitorAccessorTest, beginTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->begin, nullptr);

    std::printf("perfMonitor: start\n");
    
}


HWTEST_F(GlobalScope_ohos_arkui_performanceMonitorAccessorTest, beginTest2, TestSize.Level1)
{

int*p = nullptr;
*p = 0;
    
}

} // namespace OHOS::Ace::NG
