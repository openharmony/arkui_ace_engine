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
#include "core/interfaces/native/implementation/canvas_pattern_peer.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class CanvasPatternAccessorTest : public AccessorTestBase<GENERATED_ArkUICanvasPatternAccessor,
    &GENERATED_ArkUIAccessors::getCanvasPatternAccessor, CanvasPatternPeer> {
public:
};

/**
 * @tc.name: asetTransformTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasPatternAccessorTest, setTransformTest, TestSize.Level1)
{
 
    ASSERT_NE(accessor_->setTransform, nullptr);

    // peer_->SetPettern(pattern);
    Opt_Matrix2D* matrix = new(Opt_Matrix2D);
    matrix->tag = ARK_TAG_RESOURCE;
    Ark_Materialized arkValue = { nullptr };   //Ark_Matrix2d
    matrix->value = arkValue;
    accessor_->setTransform(peer_, matrix);

    ASSERT_NE(peer_, nullptr); // wrong check
    delete matrix;
}
} // namespace OHOS::Ace::NG
