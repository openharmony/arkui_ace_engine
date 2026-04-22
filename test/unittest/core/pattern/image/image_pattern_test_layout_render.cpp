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

/**
 * @file image_pattern_test_layout_render.cpp
 * @brief TDD test coverage for ImagePattern layout and rendering
 */

#include "image_base.h"

namespace OHOS::Ace::NG {

class ImagePatternLayoutRenderTestNg : public ImageBases {};

HWTEST_F(ImagePatternLayoutRenderTestNg, CreateNodePaintMethod001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    pattern->image_ = nullptr;
    auto paintMethod = pattern->CreateNodePaintMethod();
}

HWTEST_F(ImagePatternLayoutRenderTestNg, CreateNodePaintMethod002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    pattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->image_->SetPaintConfig(ImagePaintConfig());
    auto paintMethod = pattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod, nullptr);
    auto imagePaintMethod = AceType::DynamicCast<ImagePaintMethod>(paintMethod);
    EXPECT_NE(imagePaintMethod, nullptr);
}

HWTEST_F(ImagePatternLayoutRenderTestNg, CreateNodePaintMethod003, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    pattern->image_ = nullptr;
    pattern->altImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    pattern->altImage_->SetPaintConfig(ImagePaintConfig());
    auto paintMethod = pattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod, nullptr);
}

HWTEST_F(ImagePatternLayoutRenderTestNg, CheckIfNeedLayout001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    auto needLayout = pattern->CheckIfNeedLayout();
    EXPECT_TRUE(needLayout);
}

} // namespace OHOS::Ace::NG