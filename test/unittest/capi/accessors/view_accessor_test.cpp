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

#include "accessor_test_base.h"
#include "gmock/gmock.h"

#include "core/interfaces/native/implementation/view_peer_impl.h"
#include "core/interfaces/native/utility/peer_utils.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class ViewAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIViewAccessor,
    &GENERATED_ArkUIAccessors::getViewAccessor, ViewPeer> {
public:
    void DisposeNode(Ark_NodeHandle &node)
    {
        auto basicAPI = reinterpret_cast<const GENERATED_ArkUIBasicNodeAPI *>(
            GENERATED_GetArkAnyAPI(GENERATED_Ark_APIVariantKind::GENERATED_BASIC,
            GENERATED_ARKUI_BASIC_NODE_API_VERSION)
        );
        if (basicAPI) {
            basicAPI->disposeNode(node);
        }
        node = nullptr;
    }
};

/**
 * @tc.name: createTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ViewAccessorTest, ViewAccessorCreateTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->create, nullptr);
    auto newNode = accessor_->create(nullptr, nullptr);
    EXPECT_NE(newNode, nullptr);
    auto nodeHandle = reinterpret_cast<Ark_NodeHandle>(newNode);
    DisposeNode(nodeHandle);
}
} //  namespace OHOS::Ace::NG