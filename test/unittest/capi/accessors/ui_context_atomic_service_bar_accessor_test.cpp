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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class UIContextAtomicServiceBarAccessorTest :
    public StaticAccessorTest<GENERATED_ArkUIUIContextAtomicServiceBarAccessor,
    &GENERATED_ArkUIAccessors::getUIContextAtomicServiceBarAccessor> {
};

/**
 * @tc.name: getBarRect
 * @tc.desc: Test GetAppBarRect
 * @tc.type: FUNC
 */
HWTEST_F(UIContextAtomicServiceBarAccessorTest, getBarRect, TestSize.Level1)
{
    ASSERT_NE(accessor_->getBarRect, nullptr);

    // Convert frame check
    Ark_Frame src = {100.0, 200.0, 300.0, 400.0};
    RectF result = Converter::Convert<RectF>(src);
    ASSERT_EQ(result.GetX(), 100.0);
    ASSERT_EQ(result.GetY(), 200.0);
    ASSERT_EQ(result.Width(), 300.0);
    ASSERT_EQ(result.Height(), 400.0);

    auto appBar = AceType::MakeRefPtr<AppBarView>();
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetAppBar(appBar);

    auto baseRect = appBar->GetAppBarRect();
    ASSERT_TRUE(baseRect.has_value());
    auto rect = Converter::OptConvert<RectF>(accessor_->getBarRect());
    ASSERT_TRUE(rect.has_value());
    EXPECT_EQ(rect.value(), baseRect.value());
}

}