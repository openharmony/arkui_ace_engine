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
#include "core/components_ng/pattern/image/image_event_hub.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/pattern/image_animator/image_animator_pattern.h"
#include "core/components_ng/pattern/image_animator/image_animator_view.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr Animator::Status STATUS_DEFAULT = Animator::Status::IDLE;
constexpr Animator::Status STATUS_START = Animator::Status::RUNNING;
constexpr int32_t DURATION_DEFAULT = 1000;
constexpr int32_t ITERATION_DEFAULT = 1;
constexpr FillMode FILLMODE_DEFAULT = FillMode::FORWARDS;
constexpr int32_t PREDECODE_DEFAULT = 0;
constexpr bool ISREVERSE_DEFAULT = false;
constexpr bool FIXEDSIZE_DEFAULT = true;

constexpr Dimension IMAGE_WIDTH = 170.0_vp;
constexpr Dimension IMAGE_HEIGHT = 120.0_vp;
constexpr Dimension IMAGE_TOP = 0.0_vp;
constexpr Dimension IMAGE_LEFT = 0.0_vp;
constexpr int32_t IMAGE_DURATION = 500;
const std::string IMAGE_SRC_URL = "file://data/data/com.example.test/res/example.jpg";

const std::string STATUS_IDLE_STR = "AnimationStatus.Initial";
const std::string FILLMODE_FORWARDS_STR = "FillMode.Forwards";
} // namespace

class ImageAnimatorViewTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void ImageAnimatorViewTestNg::SetUpTestCase() {}
void ImageAnimatorViewTestNg::TearDownTestCase() {}
void ImageAnimatorViewTestNg::SetUp() {}
void ImageAnimatorViewTestNg::TearDown() {}

/**
 * @tc.name: ImageAnimator001
 * @tc.desc: Create ImageAnimator.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorViewTestNg, ImageAnimator001, TestSize.Level1)
{
    ImageAnimatorView imageAnimatorView;
    imageAnimatorView.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ANIMATOR_ETS_TAG);
    auto childNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    EXPECT_TRUE(childNode != nullptr && childNode->GetTag() == V2::IMAGE_ETS_TAG);
    auto imageLayoutProperty = childNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
}

/**
 * @tc.name: ImageAnimator002
 * @tc.desc: Set ImageAnimator attributes into ImageAnimatorPattern and get them.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorViewTestNg, ImageAnimator002, TestSize.Level1)
{
    ImageAnimatorView imageAnimatorView;
    imageAnimatorView.Create();

    imageAnimatorView.SetStatus(STATUS_DEFAULT);
    imageAnimatorView.SetDuration(DURATION_DEFAULT);
    imageAnimatorView.SetIteration(ITERATION_DEFAULT);
    imageAnimatorView.SetFillMode(FILLMODE_DEFAULT);
    imageAnimatorView.SetPreDecode(PREDECODE_DEFAULT);
    imageAnimatorView.SetIsReverse(ISREVERSE_DEFAULT);
    imageAnimatorView.SetFixedSize(FIXEDSIZE_DEFAULT);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ANIMATOR_ETS_TAG);
    RefPtr<ImageAnimatorPattern> imageAnimatorPattern =
        AceType::DynamicCast<OHOS::Ace::NG::ImageAnimatorPattern>(frameNode->GetPattern());
    EXPECT_TRUE(imageAnimatorPattern != nullptr);
    auto jsonValue = JsonUtil::Create(true);
    imageAnimatorPattern->ToJsonValue(jsonValue);
    EXPECT_EQ(jsonValue->GetValue("state")->GetString().c_str(), STATUS_IDLE_STR);
    EXPECT_EQ(jsonValue->GetValue("duration")->GetString().c_str(), std::to_string(DURATION_DEFAULT));
    EXPECT_EQ(jsonValue->GetValue("iterations")->GetString().c_str(), std::to_string(ITERATION_DEFAULT));
    EXPECT_EQ(jsonValue->GetValue("fillMode")->GetString().c_str(), FILLMODE_FORWARDS_STR);
    EXPECT_EQ(jsonValue->GetValue("reverse")->GetString(), std::string(ISREVERSE_DEFAULT ? "true" : "false"));
    EXPECT_EQ(jsonValue->GetValue("fixedSize")->GetString(), std::string(FIXEDSIZE_DEFAULT ? "true" : "false"));
}

/**
 * @tc.name: ImageAnimator003
 * @tc.desc: Set Image into ImageAnimator and get its attributes.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorViewTestNg, ImageAnimator003, TestSize.Level1)
{
    ImageAnimatorView imageAnimatorView;
    imageAnimatorView.Create();

    ImageProperties imageProperties;
    imageProperties.src = IMAGE_SRC_URL;
    imageProperties.width = IMAGE_WIDTH;
    imageProperties.height = IMAGE_HEIGHT;
    imageProperties.top = IMAGE_TOP;
    imageProperties.left = IMAGE_LEFT;
    imageProperties.duration = IMAGE_DURATION;
    std::vector<ImageProperties> images;
    images.push_back(imageProperties);
    imageAnimatorView.SetImages(std::move(images));

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ANIMATOR_ETS_TAG);
    RefPtr<ImageAnimatorPattern> imageAnimatorPattern =
        AceType::DynamicCast<OHOS::Ace::NG::ImageAnimatorPattern>(frameNode->GetPattern());
    EXPECT_TRUE(imageAnimatorPattern != nullptr);
    auto jsonValue = JsonUtil::Create(true);
    imageAnimatorPattern->ToJsonValue(jsonValue);
    std::string imagesStr = jsonValue->GetValue("images")->GetString();

    auto imageArray = JsonUtil::CreateArray(true);
    auto imageItem = JsonUtil::Create(true);
    imageItem->Put("src", IMAGE_SRC_URL.c_str());
    imageItem->Put("left", IMAGE_LEFT.ToString().c_str());
    imageItem->Put("top", IMAGE_TOP.ToString().c_str());
    imageItem->Put("width", IMAGE_WIDTH.ToString().c_str());
    imageItem->Put("height", IMAGE_HEIGHT.ToString().c_str());
    imageItem->Put("duration", std::to_string(IMAGE_DURATION).c_str());
    imageArray->Put(imageItem);
    EXPECT_EQ(imagesStr, imageArray->ToString());
    LOGW("ZRJ:imagesStr:%{public}s", imagesStr.c_str());
}

/**
 * @tc.name: ImageAnimator004
 * @tc.desc: Set StartEvent into ImageAnimatorPattern and run it.
 * @tc.type: FUNC
 */
HWTEST_F(ImageAnimatorViewTestNg, ImageAnimator004, TestSize.Level1)
{
    ImageAnimatorView imageAnimatorView;
    imageAnimatorView.Create();
    ImageProperties imageProperties;
    imageProperties.src = IMAGE_SRC_URL;
    imageProperties.width = IMAGE_WIDTH;
    imageProperties.height = IMAGE_HEIGHT;
    imageProperties.top = IMAGE_TOP;
    imageProperties.left = IMAGE_LEFT;
    imageProperties.duration = IMAGE_DURATION;
    std::vector<ImageProperties> images;
    images.push_back(imageProperties);
    imageAnimatorView.SetImages(std::move(images));
    imageAnimatorView.SetStatus(STATUS_START);
    imageAnimatorView.SetIsReverse(ISREVERSE_DEFAULT);
    imageAnimatorView.SetIteration(ITERATION_DEFAULT);
    bool startFlag = false;
    auto startEvent = [&startFlag]() { startFlag = !startFlag; };
    imageAnimatorView.SetImageAnimatorEvent(startEvent, AnimatorEventType::ON_START);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_TRUE(frameNode != nullptr && frameNode->GetTag() == V2::IMAGE_ANIMATOR_ETS_TAG);
    auto eventHub = frameNode->GetEventHub<NG::ImageAnimatorEventHub>();
    EXPECT_TRUE(eventHub != nullptr);
    RefPtr<ImageAnimatorPattern> imageAnimatorPattern =
        AceType::DynamicCast<OHOS::Ace::NG::ImageAnimatorPattern>(frameNode->GetPattern());
    EXPECT_TRUE(imageAnimatorPattern != nullptr);
    imageAnimatorPattern->AttachToFrameNode(frameNode);
    imageAnimatorPattern->OnModifyDone();
    EXPECT_TRUE(startFlag);
}
} // namespace OHOS::Ace::NG