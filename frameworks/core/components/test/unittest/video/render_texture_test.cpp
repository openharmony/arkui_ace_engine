/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/test/unittest/video/texture_test_utils.h"
#include "core/components/video/render_texture.h"
#include "core/components/video/texture_component.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {

const int64_t TEXTURE_ID_DEFAULT = 1;

const uint32_t VIDEO_WIDTH_SMALL_PORTRAIT = 576;
const uint32_t VIDEO_HEIGHT_SMALL_PORTRAIT = 704;
const uint32_t VIDEO_WIDTH_SMALL_LANDSCAPE = 704;
const uint32_t VIDEO_HEIGHT_SMALL_LANDSCAPE = 576;

const uint32_t VIDEO_WIDTH_LARGE_PORTRAIT = 1080;
const uint32_t VIDEO_HEIGHT_LARGE_PORTRAIT = 1920;
const uint32_t VIDEO_WIDTH_LARGE_LANDSCAPE = 1920;
const uint32_t VIDEO_HEIGHT_LARGE_LANDSCAPE = 1080;

const Size AREA_SMALL_PORTRAIT = Size(720.0, 1280.0);

} // namespace

class RenderTextureTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: RenderTextureTest009
 * @tc.desc: Verify the video display area with fill fit when the horizontal video is on the vertical screen,
 *           and the video resolution is smaller than the screen resolution.
 * @tc.type: FUNC
 * @tc.require: AR000DAR0T
 * @tc.author: HeSu
 */
HWTEST_F(RenderTextureTest, RenderTextureTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct TextureComponent.
     * @tc.expected: step1. properties set correctly.
     */
    RefPtr<TextureComponent> component = AceType::MakeRefPtr<TextureComponent>();
    component->SetTextureId(TEXTURE_ID_DEFAULT);
    component->SetSrcWidth(VIDEO_WIDTH_SMALL_PORTRAIT);
    component->SetSrcHeight(VIDEO_HEIGHT_SMALL_PORTRAIT);
    component->SetFit(ImageFit::FILL);

    /**
     * @tc.steps: step2. construct RenderTexture, update it with component.
     * @tc.expected: step2. properties is set correctly.
     */
    RefPtr<MockRenderTexture> renderTexture = AceType::MakeRefPtr<MockRenderTexture>();
    renderTexture->Update(component);

    /**
     * @tc.steps: step3. Verify that the properties are calculated correctly.
     * @tc.expected: step3. Image offset and Size are calculated correctly.
     */
    LayoutParam layoutParam;
    layoutParam.SetMaxSize(AREA_SMALL_PORTRAIT);
    renderTexture->SetLayoutParam(layoutParam);
    renderTexture->PerformLayout();

    Offset imageOffset(0, 0);
    Size imageSize(720, 1280);

    ASSERT_TRUE(IsNearEqual(renderTexture->GetImageOffset(), imageOffset));
    ASSERT_TRUE(IsNearEqual(renderTexture->GetImageSize(), imageSize));
}

/**
 * @tc.name: RenderTextureTest010
 * @tc.desc: Verify the video display area with fill fit when the vertical video is on the vertical screen,
 *           and the video resolution is smaller than the screen resolution.
 * @tc.type: FUNC
 * @tc.require: AR000DAR0T
 * @tc.author: HeSu
 */
HWTEST_F(RenderTextureTest, RenderTextureTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct TextureComponent.
     * @tc.expected: step1. properties set correctly.
     */
    RefPtr<TextureComponent> component = AceType::MakeRefPtr<TextureComponent>();
    component->SetTextureId(TEXTURE_ID_DEFAULT);
    component->SetSrcWidth(VIDEO_WIDTH_SMALL_LANDSCAPE);
    component->SetSrcHeight(VIDEO_HEIGHT_SMALL_LANDSCAPE);
    component->SetFit(ImageFit::FILL);

    /**
     * @tc.steps: step2. construct RenderTexture, update it with component.
     * @tc.expected: step2. properties is set correctly.
     */
    RefPtr<MockRenderTexture> renderTexture = AceType::MakeRefPtr<MockRenderTexture>();
    renderTexture->Update(component);

    /**
     * @tc.steps: step3. Verify that the properties are calculated correctly.
     * @tc.expected: step3. Image offset and Size are calculated correctly.
     */
    LayoutParam layoutParam;
    layoutParam.SetMaxSize(AREA_SMALL_PORTRAIT);
    renderTexture->SetLayoutParam(layoutParam);
    renderTexture->PerformLayout();

    Offset imageOffset(0, 0);
    Size imageSize(720, 1280);

    ASSERT_TRUE(IsNearEqual(renderTexture->GetImageOffset(), imageOffset));
    ASSERT_TRUE(IsNearEqual(renderTexture->GetImageSize(), imageSize));
}

/**
 * @tc.name: RenderTextureTest011
 * @tc.desc: Verify the video display area with fill fit when the horizontal video is on the vertical screen,
 *           and the video resolution is greater than the screen resolution.
 * @tc.type: FUNC
 * @tc.require: AR000DAR0T
 * @tc.author: HeSu
 */
HWTEST_F(RenderTextureTest, RenderTextureTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct TextureComponent.
     * @tc.expected: step1. properties set correctly.
     */
    RefPtr<TextureComponent> component = AceType::MakeRefPtr<TextureComponent>();
    component->SetTextureId(TEXTURE_ID_DEFAULT);
    component->SetSrcWidth(VIDEO_WIDTH_LARGE_PORTRAIT);
    component->SetSrcHeight(VIDEO_HEIGHT_LARGE_PORTRAIT);
    component->SetFit(ImageFit::FILL);

    /**
     * @tc.steps: step2. construct RenderTexture, update it with component.
     * @tc.expected: step2. properties is set correctly.
     */
    RefPtr<MockRenderTexture> renderTexture = AceType::MakeRefPtr<MockRenderTexture>();
    renderTexture->Update(component);

    /**
     * @tc.steps: step3. Verify that the properties are calculated correctly.
     * @tc.expected: step3. Image offset and Size are calculated correctly.
     */
    LayoutParam layoutParam;
    layoutParam.SetMaxSize(AREA_SMALL_PORTRAIT);
    renderTexture->SetLayoutParam(layoutParam);
    renderTexture->PerformLayout();

    Offset imageOffset(0, 0);
    Size imageSize(720, 1280);

    ASSERT_TRUE(IsNearEqual(renderTexture->GetImageOffset(), imageOffset));
    ASSERT_TRUE(IsNearEqual(renderTexture->GetImageSize(), imageSize));
}

/**
 * @tc.name: RenderTextureTest012
 * @tc.desc: Verify the video display area with fill fit when the vertical video is on the vertical screen,
 *           and the video resolution is greater than the screen resolution.
 * @tc.type: FUNC
 * @tc.require: AR000DAR0T
 * @tc.author: HeSu
 */
HWTEST_F(RenderTextureTest, RenderTextureTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct TextureComponent.
     * @tc.expected: step1. properties set correctly.
     */
    RefPtr<TextureComponent> component = AceType::MakeRefPtr<TextureComponent>();
    component->SetTextureId(TEXTURE_ID_DEFAULT);
    component->SetSrcWidth(VIDEO_WIDTH_LARGE_LANDSCAPE);
    component->SetSrcHeight(VIDEO_HEIGHT_LARGE_LANDSCAPE);
    component->SetFit(ImageFit::FILL);

    /**
     * @tc.steps: step2. construct RenderTexture, update it with component.
     * @tc.expected: step2. properties is set correctly.
     */
    RefPtr<MockRenderTexture> renderTexture = AceType::MakeRefPtr<MockRenderTexture>();
    renderTexture->Update(component);

    /**
     * @tc.steps: step3. Verify that the properties are calculated correctly.
     * @tc.expected: step3. Image offset and Size are calculated correctly.
     */
    LayoutParam layoutParam;
    layoutParam.SetMaxSize(AREA_SMALL_PORTRAIT);
    renderTexture->SetLayoutParam(layoutParam);
    renderTexture->PerformLayout();

    Offset imageOffset(0, 0);
    Size imageSize(720, 1280);

    ASSERT_TRUE(IsNearEqual(renderTexture->GetImageOffset(), imageOffset));
    ASSERT_TRUE(IsNearEqual(renderTexture->GetImageSize(), imageSize));
}

} // namespace OHOS::Ace