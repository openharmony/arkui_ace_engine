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
 
#include "gtest/gtest.h"
#include "ui/properties/color.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS {
namespace Ace {

class ColorPlaceholderTest : public testing::Test {};

/**
 * @tc.name: ColorPlaceholderFactory
 * @tc.desc: Verify factory creates placeholder color.
 * @tc.type: FUNC
 */
HWTEST_F(ColorPlaceholderTest, ColorPlaceholderFactory, TestSize.Level1)
{
    Color c(ColorPlaceholder::BACKGROUND_CONTRAST);
    EXPECT_TRUE(c.IsPlaceholder());
    EXPECT_EQ(c.GetPlaceholder(), ColorPlaceholder::BACKGROUND_CONTRAST);
    auto s = c.ToString();
    EXPECT_NE(s.find("PH:BackgroundContrast"), std::string::npos);
}

} // namespace Ace
} // namespace OHOS
