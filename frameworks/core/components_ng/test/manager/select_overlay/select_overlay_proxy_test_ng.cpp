/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/manager/select_overlay/select_overlay_proxy.h"
#include "frameworks/core/components_ng/pattern/pattern.h"
#include "frameworks/core/components_ng/pattern/select_overlay/select_overlay_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const int32_t NODE_ID = 143;
} // namespace
class SelectOverlayProxyTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};

protected:
};

/**
 * @tc.name: SelectOverlayProxyTest001
 * @tc.desc: just test the environment is ok, the test cases will be designed
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SelectOverlayProxyTestNg, SelectOverlayProxyTest001, TestSize.Level1)
{
    SelectHandleInfo selectHandleInfo;
    auto selectOverlayProxy = AceType::MakeRefPtr<SelectOverlayProxy>(NODE_ID);
    selectOverlayProxy->UpdateFirstSelectHandleInfo(selectHandleInfo);
    EXPECT_EQ(1, 1);
}
} // namespace OHOS::Ace::NG
