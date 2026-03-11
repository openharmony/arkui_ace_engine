/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "movingphoto_test_min.h"

using namespace testing;

namespace OHOS::Ace::NG {

TestProperty MovingPhotoTestBase::testProperty_;

void MovingPhotoTestBase::SetUpTestSuite()
{
    testProperty_.imageSrc = MOVINGPHOTO_IMAGE_SRC;
    testProperty_.muted = MUTED_VALUE;
    testProperty_.objectFit = MOVINGPHOTO_IMAGE_FIT;

    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    MockPipelineContext::GetCurrent()->rootNode_ = FrameNode::CreateFrameNodeWithTree(
        V2::ROOT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<RootPattern>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<VideoTheme>()));
    MockImageAnalyzerManager::SetUp();
}

void MovingPhotoTestBase::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void MovingPhotoTestBase::SetUp()
{
    ViewStackProcessor::GetInstance()->ClearStack();
}

RefPtr<FrameNode> MovingPhotoTestBase::CreateMovingPhotoNode(TestProperty& testProperty_)
{
    if (testProperty_.movingPhotoController.has_value()) {
        MovingPhotoModelNG().Create(testProperty_.movingPhotoController.value());
    } else {
        auto movingPhotoController = AceType::MakeRefPtr<MovingPhotoController>();
        MovingPhotoModelNG().Create(movingPhotoController);
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto movingPhotoPattern = AceType::DynamicCast<MovingPhotoPattern>(frameNode->GetPattern());
    CHECK_NULL_RETURN(movingPhotoPattern, nullptr);
    EXPECT_CALL(*(AceType::DynamicCast<MockMediaPlayer>(movingPhotoPattern->mediaPlayer_)), IsMediaPlayerValid())
        .WillRepeatedly(Return(true));
    if (testProperty_.imageSrc.has_value()) {
        MovingPhotoModelNG().SetImageSrc(testProperty_.imageSrc.value());
    }
    if (testProperty_.muted.has_value()) {
        MovingPhotoModelNG().SetMuted(testProperty_.muted.value());
    }
    if (testProperty_.objectFit.has_value()) {
        MovingPhotoModelNG().SetObjectFit(testProperty_.objectFit.value());
    }
    auto element = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    return AceType::Claim(element);
}

} // namespace OHOS::Ace::NG
