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
#include "gtest/gtest.h"

#define protected public
#define private public

#include "core/components_ng/image_provider/image_provider.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class ImageProviderTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

void ImageProviderTestNg::SetUpTestCase()
{
}

void ImageProviderTestNg::TearDownTestCase() {}

void ImageProviderTestNg::SetUp() {}

void ImageProviderTestNg::TearDown() {}

/**
 * @tc.name: ImageProviderTestNg001
 * @tc.desc: Test ImageProvider WrapTaskAndPostTo with null std::function
 * @tc.type: FUNC
 */
HWTEST_F(ImageProviderTestNg, ImageProviderTestNg001, TestSize.Level1)
{
    ImageProvider::WrapTaskAndPostToBackground(nullptr);
}

} // namespace OHOS::Ace::NG