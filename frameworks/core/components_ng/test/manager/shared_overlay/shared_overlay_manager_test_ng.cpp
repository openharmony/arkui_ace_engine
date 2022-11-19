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
#include "third_party/googletest/googletest/include/gtest/gtest.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "frameworks/core/components_ng/pattern/pattern.h"

#define private public
#include "frameworks/core/components_ng/manager/shared_overlay/shared_overlay_manager.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
bool OHOS::Ace::SystemProperties::GetDebugEnabled()
{
    return false;
}
} // namespace OHOS::Ace
namespace OHOS::Ace::NG {
namespace {
const std::string ROOT_TAG = "root";
const std::string SRC_TAG = "src";
const std::string DEST_TAG = "dest";
} // namespace

class SharedOverlayManagerTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};

protected:
};

/**
 * @tc.name: SharedOverlayManagerTest001
 * @tc.desc: xxx
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SharedOverlayManagerTestNg, SharedOverlayManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a SharedOverlayManager
     */
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto sharedOverlayManager = AceType::MakeRefPtr<SharedOverlayManager>(root);

    /**
     * @tc.steps: step2. construct two frameNodes which type is Page and pageInfo is default config
     */
    auto srcPageInfo = AceType::MakeRefPtr<PageInfo>();
    auto destPageInfo = AceType::MakeRefPtr<PageInfo>();
    auto pageSrc = AceType::MakeRefPtr<FrameNode>(SRC_TAG, -1, AceType::MakeRefPtr<PagePattern>(srcPageInfo));
    auto pageDest = AceType::MakeRefPtr<FrameNode>(DEST_TAG, -1, AceType::MakeRefPtr<PagePattern>(destPageInfo));

    /**
     * @tc.steps: step3. call StartSharedTransition
     * @tc.expected: step3. effects_ is empty for page has no sharedTransitionEffect
     */
    sharedOverlayManager->StartSharedTransition(pageSrc, pageDest);
    EXPECT_EQ(sharedOverlayManager->effects_.size(), 0);
}
} // namespace OHOS::Ace::NG
