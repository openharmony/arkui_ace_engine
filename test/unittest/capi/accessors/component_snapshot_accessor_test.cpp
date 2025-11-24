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
#include "test/unittest/capi/stubs/mock_component_snapshot.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

static const auto CONTEXT_ID = 123;

class ComponentSnapshotAccessorTest :
    public StaticAccessorTest<GENERATED_ArkUIGlobalScope_ohos_arkui_componentSnapshotAccessor,
    &GENERATED_ArkUIAccessors::getGlobalScope_ohos_arkui_componentSnapshotAccessor> {
};

/**
 * @tc.name: getMethodTest
 * @tc.desc: Check the functionality of get
 * @tc.type: FUNC
 */
HWTEST_F(ComponentSnapshotAccessorTest, getMethodTest, TestSize.Level1)
{
    static bool called = false;
    ASSERT_NE(accessor_->get, nullptr);
    Ark_String id = Converter::ArkValue<Ark_String>("Button.1");
    auto callback = [](const Ark_Int32 resourceId, const Ark_image_PixelMap result) {
        called = (result != nullptr);
    };
    auto func = Converter::ArkValue<AsyncCallback_image_PixelMap_Void>(callback, CONTEXT_ID);
    Opt_SnapshotOptions options {
        .value.scale = Converter::ArkValue<Opt_Number>(1.0),
        .value.waitUntilRenderFinished = Converter::ArkValue<Opt_Boolean>(false) };
    accessor_->get(&id, &func, &options);
    EXPECT_TRUE(called);
}

} // namespace OHOS::Ace::NG
