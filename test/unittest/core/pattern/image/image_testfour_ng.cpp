/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "image_base.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class ImageTestFourNg : public ImageBases {
public:
};

/**
 * @tc.name:  ImageModelNGTest001
 * @tc.desc: Test ResetImage method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest001, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    imageModelNG.ResetImage();
}

/**
 * @tc.name:  ImageModelNGTest002
 * @tc.desc: Test SetInitialPixelMap method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest002, TestSize.Level1)
{
    RefPtr<PixelMap> pixMap = nullptr;
    ImageModelNG::SetInitialPixelMap(nullptr, pixMap);
}

/**
 * @tc.name:  ImageModelNGTest003
 * @tc.desc: Test SetBorder method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest003, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    auto border = std::make_shared<Border>();
    imageModelNG.SetBorder(*border);
}

/**
 * @tc.name:  ImageModelNGTest004
 * @tc.desc: Test SetBlur method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest004, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    double dValue = 1.1;
    imageModelNG.SetBlur(dValue);
}

/**
 * @tc.name:  ImageModelNGTest005
 * @tc.desc: Test IsSrcSvgImage method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest005, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    bool bl = imageModelNG.IsSrcSvgImage();
    EXPECT_FALSE(bl);
}

/**
 * @tc.name:  ImageModelNGTest006
 * @tc.desc: Test SetOnDragStart method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest006, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    imageModelNG.SetOnDragStart(nullptr);
}

/**
 * @tc.name:  ImageModelNGTest007
 * @tc.desc: Test SetOnDragEnter method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest007, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    imageModelNG.SetOnDragEnter(nullptr);
}

/**
 * @tc.name:  ImageModelNGTest008
 * @tc.desc: Test SetOnDragLeave method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest008, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    imageModelNG.SetOnDragLeave(nullptr);
}

/**
 * @tc.name:  ImageModelNGTest009
 * @tc.desc: Test SetOnDragMove method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest009, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    imageModelNG.SetOnDragMove(nullptr);
}

/**
 * @tc.name:  ImageModelNGTest010
 * @tc.desc: Test SetOnDrop method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest010, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    imageModelNG.SetOnDrop(nullptr);
}

/**
 * @tc.name:  ImageModelNGTest011
 * @tc.desc: Test UpdateDragItemInfo method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest011, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    auto dragItemInfo = std::make_shared<DragItemInfo>();
    bool bl = imageModelNG.UpdateDragItemInfo(*dragItemInfo);
    EXPECT_FALSE(bl);
}

/**
 * @tc.name:  ImageModelNGTest012
 * @tc.desc: Test SetPixelMap method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest012, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    imageModelNG.SetPixelMap(nullptr, nullptr);
}

/**
 * @tc.name:  ImageModelNGTest013
 * @tc.desc: Test SetPixelMapArray method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest013, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    imageModelNG.SetPixelMapArray(nullptr, nullptr);
}

/**
 * @tc.name:  ImageModelNGTest014
 * @tc.desc: Test SetResource method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest014, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    imageModelNG.SetResource(nullptr, nullptr);
}

/**
 * @tc.name:  ImageModelNGTest015
 * @tc.desc: Test SetResizableSlice method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest015, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    auto slice = std::make_shared<ImageResizableSlice>();
    imageModelNG.SetResizableSlice(*slice);
}

/**
 * @tc.name:  ImageModelNGTest016
 * @tc.desc: Test SetResizableSlice method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest016, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    auto slice = std::make_shared<ImageResizableSlice>();
    imageModelNG.SetResizableSlice(nullptr, *slice);
}

/**
 * @tc.name:  ImageModelNGTest017
 * @tc.desc: Test SetResizableLattice method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest017, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    RefPtr<DrawingLattice> lattice;
    imageModelNG.SetResizableLattice(lattice);
}

/**
 * @tc.name:  ImageModelNGTest018
 * @tc.desc: Test SetResizableLattice method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest018, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    RefPtr<DrawingLattice> lattice;
    imageModelNG.SetResizableLattice(nullptr, lattice);
}

/**
 * @tc.name:  ImageModelNGTest019
 * @tc.desc: Test ResetResizableLattice method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest019, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    imageModelNG.ResetResizableLattice();
}

/**
 * @tc.name:  ImageModelNGTest020
 * @tc.desc: Test ResetResizableLattice method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest020, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    imageModelNG.ResetResizableLattice(nullptr);
}

/**
 * @tc.name:  ImageModelNGTest021
 * @tc.desc: Test SetAltResource method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest021, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    imageModelNG.SetAltResource(nullptr, nullptr);
}

/**
 * @tc.name:  ImageModelNGTest022
 * @tc.desc: Test SetAltPixelMap method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest022, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    imageModelNG.SetAltPixelMap(nullptr, nullptr);
}

/**
 * @tc.name:  ImageModelNGTest023
 * @tc.desc: Test EnableAnalyzer method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest023, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    imageModelNG.EnableAnalyzer(true);
}

/**
 * @tc.name:  ImageModelNGTest024
 * @tc.desc: Test SetImageAnalyzerConfig method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest024, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    auto config = std::make_shared<ImageAnalyzerConfig>();
    imageModelNG.SetImageAnalyzerConfig(*config);
}

/**
 * @tc.name:  ImageModelNGTest025
 * @tc.desc: Test SetImageAnalyzerConfig method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest025, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    imageModelNG.SetImageAnalyzerConfig(nullptr);
}

/**
 * @tc.name:  ImageModelNGTest026
 * @tc.desc: Test SetImageAnalyzerConfig method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest026, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    imageModelNG.SetImageAnalyzerConfig(nullptr, nullptr);
}

/**
 * @tc.name:  ImageModelNGTest027
 * @tc.desc: Test SetImageAIOptions method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest027, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    imageModelNG.SetImageAIOptions(nullptr);
}

/**
 * @tc.name:  ImageModelNGTest028
 * @tc.desc: Test IsSrcSvgImage method.
 * @tc.type: FUNC
 */
HWTEST_F(ImageTestFourNg, ImageModelNGTest028, TestSize.Level1)
{
    ImageModelNG imageModelNG;
    bool bl = imageModelNG.IsSrcSvgImage(nullptr);
    EXPECT_FALSE(bl);
}
} // namespace OHOS::Ace::NG