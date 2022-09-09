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

#include "core/components/image/image_component.h"
#include "core/components/test/unittest/mock/mock_render_common.h"
#define private public
#define protected public
#include "core/components/text_overlay/text_overlay_component.h"
#include "core/components/text_overlay/text_overlay_manager.h"
#include "core/components/image/render_image.h"
#undef private
#undef protected
#include "gtest/gtest.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
const double SMALL_LENGTH = 200.0;
const double LARGE_LENGTH = 400.0;
class MockRenderImageForColorFilter final : public RenderImage {
    DECLARE_ACE_TYPE(MockRenderImageForColorFilter, RenderImage);

public:
    MockRenderImageForColorFilter() = default;
    ~MockRenderImageForColorFilter() = default;

    Size Measure() override
    {
        return Size(LARGE_LENGTH, LARGE_LENGTH);
    }

    void ShowTextOverlay(const Offset& showOffset) override
    {
        return;
    }

    virtual void RegisterCallbacksToOverlay() override
    {
        return;
    }

    Offset GetHandleOffset(int32_t extend) override
    {
        Offset offset;
        return offset;
    }

    std::string GetSelectedContent() const override
    {
        return "";
    }
};

class RenderImageColorFilterTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

    RefPtr<PipelineContext> mockContext_;
    RefPtr<RenderImage> renderImage_;
};

void RenderImageColorFilterTest::SetUpTestCase() {}
void RenderImageColorFilterTest::TearDownTestCase() {}

void RenderImageColorFilterTest::SetUp()
{
    mockContext_ = MockRenderCommon::GetMockContext();
    renderImage_ = AceType::MakeRefPtr<MockRenderImageForColorFilter>();
    renderImage_->Attach(mockContext_);
}

void RenderImageColorFilterTest::TearDown()
{
    mockContext_ = nullptr;
    renderImage_ = nullptr;
}

/**
 * @tc.name: colorfilter001
 * @tc.desc: Verify that renderimage can normally obtain the data of the primary color matrix
 * @tc.type: FUNC
 * @tc.require: issueI5NC61
 */
HWTEST_F(RenderImageColorFilterTest, colorfilter001, TestSize.Level1)
{
    std::vector<float> colorfilter = { 1.0, 0.0, 0.0, 0.0, 0.0,
                                       0.0, 1.0, 0.0, 0.0, 0.0,
                                       0.0, 0.0, 1.0, 0.0, 0.0,
                                       0.0, 0.0, 0.0, 1.0, 0.0 };

    RefPtr<ImageComponent> imageComponent = AceType::MakeRefPtr<ImageComponent>("");
    imageComponent->SetWidth(Dimension(LARGE_LENGTH));
    imageComponent->SetHeight(Dimension(SMALL_LENGTH));
    imageComponent->SetColorFilterMatrix(colorfilter);
    ASSERT_EQ(imageComponent->GetColorFilterMatrix().size(), 20);
    renderImage_->Update(imageComponent);

    ASSERT_EQ(renderImage_->colorfilter_.size(), 20);
    for (int i = 0; i < 20; i++) {
        ASSERT_FLOAT_EQ(colorfilter.at(i), renderImage_->colorfilter_.at(i));
    }
}

/**
 * @tc.name: colorfilter002
 * @tc.desc: Verify that renderimage can normally obtain the data of the green color matrix
 * @tc.type: FUNC
 * @tc.require: issueI5NC61
 */
HWTEST_F(RenderImageColorFilterTest, colorfilter002, TestSize.Level1)
{
    std::vector<float> colorfilter = { 0.0, 0.0, 0.0, 0.0, 0.0,
                                       0.0, 1.0, 0.0, 0.0, 0.0,
                                       0.0, 0.0, 0.0, 0.0, 0.0,
                                       0.0, 0.0, 0.0, 0.0, 0.0 };

    RefPtr<ImageComponent> imageComponent = AceType::MakeRefPtr<ImageComponent>("");
    imageComponent->SetWidth(Dimension(LARGE_LENGTH));
    imageComponent->SetHeight(Dimension(SMALL_LENGTH));
    imageComponent->SetColorFilterMatrix(colorfilter);
    ASSERT_EQ(imageComponent->GetColorFilterMatrix().size(), 20);
    renderImage_->Update(imageComponent);

    ASSERT_EQ(renderImage_->colorfilter_.size(), 20);
    for (int i = 0; i < 20; i++) {
        ASSERT_FLOAT_EQ(colorfilter.at(i), renderImage_->colorfilter_.at(i));
    }
}

/**
 * @tc.name: colorfilter003
 * @tc.desc: Verify that renderimage can normally obtain the data of the blue color matrix
 * @tc.type: FUNC
 * @tc.require: issueI5NC61
 */
HWTEST_F(RenderImageColorFilterTest, colorfilter003, TestSize.Level1)
{
    std::vector<float> colorfilter = { 0.0, 0.0, 0.0, 0.0, 0.0,
                                       0.0, 0.0, 0.0, 0.0, 0.0,
                                       0.0, 0.0, 1.0, 0.0, 0.0,
                                       0.0, 0.0, 0.0, 0.0, 0.0 };

    RefPtr<ImageComponent> imageComponent = AceType::MakeRefPtr<ImageComponent>("");
    imageComponent->SetWidth(Dimension(LARGE_LENGTH));
    imageComponent->SetHeight(Dimension(SMALL_LENGTH));
    imageComponent->SetColorFilterMatrix(colorfilter);
    ASSERT_EQ(imageComponent->GetColorFilterMatrix().size(), 20);
    renderImage_->Update(imageComponent);

    ASSERT_EQ(renderImage_->colorfilter_.size(), 20);
    for (int i = 0; i < 20; i++) {
        ASSERT_FLOAT_EQ(colorfilter.at(i), renderImage_->colorfilter_.at(i));
    }
}

/**
 * @tc.name: colorfilter004
 * @tc.desc: Verify that renderimage cannot obtain abnormal matrix data
 * @tc.type: FUNC
 * @tc.require: issueI5MX66
 */
HWTEST_F(RenderImageColorFilterTest, colorfilter004, TestSize.Level1)
{
    std::vector<float> colorfilter = { 0.0, 0.0, 0.0, 0.0, 0.0,
                                       0.0, 0.0, 0.0, 0.0, 0.0,
                                       0.0, 0.0, 1.0, 0.0, 0.0,
                                       0.0, 0.0, 0.0, 0.0 };

    RefPtr<ImageComponent> imageComponent = AceType::MakeRefPtr<ImageComponent>("");
    imageComponent->SetWidth(Dimension(LARGE_LENGTH));
    imageComponent->SetHeight(Dimension(SMALL_LENGTH));
    imageComponent->SetColorFilterMatrix(colorfilter);
    renderImage_->Update(imageComponent);

    ASSERT_TRUE(renderImage_->colorfilter_.empty());
}

/**
 * @tc.name: colorfilter005
 * @tc.desc: Verify that renderimage cannot obtain abnormal matrix data
 * @tc.type: FUNC
 * @tc.require: issueI5MX66
 */
HWTEST_F(RenderImageColorFilterTest, colorfilter005, TestSize.Level1)
{
    std::vector<float> colorfilter = { 0.0, 0.0, 0.0, 0.0, 0.0,
                                       0.0, 0.0, 0.0, 0.0, 0.0,
                                       0.0, 0.0, 1.0, 0.0, 0.0,
                                       0.0, 0.0, 0.0, 0.0, 0.0,
                                       1.0 };

    RefPtr<ImageComponent> imageComponent = AceType::MakeRefPtr<ImageComponent>("");
    imageComponent->SetWidth(Dimension(LARGE_LENGTH));
    imageComponent->SetHeight(Dimension(SMALL_LENGTH));
    imageComponent->SetColorFilterMatrix(colorfilter);
    renderImage_->Update(imageComponent);
    ASSERT_TRUE(renderImage_->colorfilter_.empty());
}
} // namespace OHOS::Ace
