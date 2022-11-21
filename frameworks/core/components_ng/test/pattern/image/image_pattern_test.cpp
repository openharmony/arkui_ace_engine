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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {

const Color SVG_FILL_COLOR_DEFAULT = Color::BLUE;
const std::string IMAGE_SRC_URL = "file://data/data/com.example.test/res/example.svg";
const std::string ALT_SRC_URL = "file://data/data/com.example.test/res/exampleAlt.jpg";

} // namespace

class ImagePatternTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    static RefPtr<FrameNode> CreateImageNode();
};

void ImagePatternTest::SetUpTestCase() {}
void ImagePatternTest::TearDownTestCase() {}
void ImagePatternTest::SetUp() {}
void ImagePatternTest::TearDown() {}
RefPtr<FrameNode> ImagePatternTest::CreateImageNode()
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    image.Create(IMAGE_SRC_URL, false, pixMap);
    image.SetAlt(ALT_SRC_URL);
    image.SetImageFill(SVG_FILL_COLOR_DEFAULT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    return frameNode;
}

/**
 * @tc.name: ImagePatternCreator001
 * @tc.desc: Create ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTest, ImagePatternCreator001, TestSize.Level1)
{
    auto frameNode = ImagePatternTest::CreateImageNode();
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_TRUE(imagePattern != nullptr);
}

} // namespace OHOS::Ace::NG
