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
class MockRenderImageCopy final : public RenderImage {
    DECLARE_ACE_TYPE(MockRenderImageCopy, RenderImage);

public:
    MockRenderImageCopy() = default;
    ~MockRenderImageCopy() = default;

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

class RenderImageCopyTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

    RefPtr<PipelineContext> mockContext_;
    RefPtr<RenderImage> renderImage_;
};

void RenderImageCopyTest::SetUpTestCase() {}
void RenderImageCopyTest::TearDownTestCase() {}

void RenderImageCopyTest::SetUp()
{
    mockContext_ = MockRenderCommon::GetMockContext();
    renderImage_ = AceType::MakeRefPtr<MockRenderImageCopy>();
    renderImage_->Attach(mockContext_);
}

void RenderImageCopyTest::TearDown()
{
    mockContext_ = nullptr;
    renderImage_ = nullptr;
}

/**
 * @tc.name: copyOptions001
 * @tc.desc: Set copyoptions none to image
 * @tc.type: FUNC
 * @tc.require: issueI5JQ1R
 */
HWTEST_F(RenderImageCopyTest, copyOptions001, TestSize.Level1)
{
    RefPtr<ImageComponent> imageComponent = AceType::MakeRefPtr<ImageComponent>("");
    imageComponent->SetWidth(Dimension(LARGE_LENGTH));
    imageComponent->SetHeight(Dimension(SMALL_LENGTH));
    imageComponent->SetCopyOption(CopyOptions::None);
    renderImage_->Update(imageComponent);
    ASSERT_EQ(imageComponent->GetCopyOption(), CopyOptions::None);
}

/**
 * @tc.name: copyOptions002
 * @tc.desc: Set copyoptions local to image
 * @tc.type: FUNC
 * @tc.require: issueI5JQ1R
 */
HWTEST_F(RenderImageCopyTest, copyOptions002, TestSize.Level1)
{
    RefPtr<ImageComponent> imageComponent = AceType::MakeRefPtr<ImageComponent>("");
    imageComponent->SetWidth(Dimension(LARGE_LENGTH));
    imageComponent->SetHeight(Dimension(SMALL_LENGTH));
    imageComponent->SetCopyOption(CopyOptions::Local);
    renderImage_->Update(imageComponent);
    ASSERT_EQ(imageComponent->GetCopyOption(), CopyOptions::Local);
}
} // namespace OHOS::Ace
