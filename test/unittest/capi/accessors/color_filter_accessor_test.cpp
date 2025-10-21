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
#include "accessor_test_base.h"
#include "test/unittest/capi/accessors/accessor_test_fixtures.h"
#include "core/interfaces/native/implementation/color_filter_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
const std::vector<float> EMPTY_VECTOR = {};
const std::vector<float> INVALID_MATRIX_LESS = {
    1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0
};
const std::vector<float> INVALID_MATRIX_MORE = {
    1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0
};
const std::vector<float> VALID_MATRIX = {
    1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0
};
const std::vector<float> VALID_MATRIX_0 = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
const std::vector<float> VALID_MATRIX_1 = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

ArkArrayHolder<Array_Float64> EMPTY_HOLDER(EMPTY_VECTOR);
ArkArrayHolder<Array_Float64> INVALID_HOLDER_0(INVALID_MATRIX_LESS);
ArkArrayHolder<Array_Float64> INVALID_HOLDER_1(INVALID_MATRIX_MORE);
ArkArrayHolder<Array_Float64> VALID_HOLDER_0(VALID_MATRIX_0);
ArkArrayHolder<Array_Float64> VALID_HOLDER_1(VALID_MATRIX_1);
ArkArrayHolder<Array_Float64> VALID_HOLDER_2(VALID_MATRIX);

const std::vector<std::tuple<std::string, Array_Float64, std::vector<float>>> floatMatrixTest {
    { "EMPTY_VECTOR", ArkValue<Array_Float64>(EMPTY_HOLDER.ArkValue()), EMPTY_VECTOR },
    { "VALID_HOLDER_0", ArkValue<Array_Float64>(VALID_HOLDER_0.ArkValue()), VALID_MATRIX_0 },
    { "INVALID_HOLDER_0", ArkValue<Array_Float64>(INVALID_HOLDER_0.ArkValue()), EMPTY_VECTOR },
    { "VALID_HOLDER_1", ArkValue<Array_Float64>(VALID_HOLDER_1.ArkValue()), VALID_MATRIX_1 },
    { "INVALID_HOLDER_1", ArkValue<Array_Float64>(INVALID_HOLDER_1.ArkValue()), EMPTY_VECTOR },
    { "VALID_HOLDER_2", ArkValue<Array_Float64>(VALID_HOLDER_2.ArkValue()), VALID_MATRIX }
};
} // namespace

class ColorFilterAccessorTest : public AccessorTestCtorBase<GENERATED_ArkUIColorFilterAccessor,
                                    &GENERATED_ArkUIAccessors::getColorFilterAccessor, ColorFilterPeer> {
public:
    void* CreatePeerInstance() override
    {
        auto value = EMPTY_HOLDER.ArkValue();
        return this->accessor_->construct(&value);
    }
};

/**
 * @tc.name: CtorTestRectShapeOptions
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColorFilterAccessorTest, CtorTest, TestSize.Level1)
{
    EXPECT_EQ(peer_->GetColorFilterMatrix(), EMPTY_VECTOR);
    for (auto& [name, value, expected] : floatMatrixTest) {
        this->accessor_->destroyPeer(peer_);
        peer_ = this->accessor_->construct(&value);
        ASSERT_TRUE(peer_);
        EXPECT_EQ(peer_->GetColorFilterMatrix(), expected) << "Value is: " << name;
    }
}
} // namespace OHOS::Ace::NG