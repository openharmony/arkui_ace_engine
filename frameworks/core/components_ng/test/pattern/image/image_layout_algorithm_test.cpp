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
#define private public
#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/image/image_layout_algorithm.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double IMAGE_COMPONENTSIZE_WIDTH = 400.0;
constexpr double IMAGE_COMPONENTSIZE_HEIGHT = 500.0;
constexpr double IMAGE_COMPONENT_MAXSIZE_WIDTH = 600.0;
constexpr double IMAGE_COMPONENT_MAXSIZE_HEIGHT = 700.0;
constexpr double IMAGE_SOURCESIZE_WIDTH = 300.0;
constexpr double IMAGE_SOURCESIZE_HEIGHT = 300.0;
constexpr double ALT_SOURCESIZE_WIDTH = 100.0;
constexpr double ALT_SOURCESIZE_HEIGHT = 200.0;
constexpr Dimension IMAGE_SOURCEINFO_WIDTH = Dimension(IMAGE_SOURCESIZE_WIDTH);
constexpr Dimension IMAGE_SOURCEINFO_HEIGHT = Dimension(IMAGE_SOURCESIZE_HEIGHT);
constexpr Dimension ALT_SOURCEINFO_WIDTH = Dimension(ALT_SOURCESIZE_WIDTH);
constexpr Dimension ALT_SOURCEINFO_HEIGHT = Dimension(ALT_SOURCESIZE_HEIGHT);
const std::string IMAGE_SRC_URL = "common/srcexample.jpg";
const std::string ALT_SRC_URL = "common/altexample.jpg";
} // namespace

class ImageLayoutAlgorithmTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void ImageLayoutAlgorithmTest::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void ImageLayoutAlgorithmTest::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: ImageLayout001
 * @tc.desc: Verify that ImageComponent can resize with selfSize, whether has src or alt.
 * @tc.type: FUNC
 */
HWTEST_F(ImageLayoutAlgorithmTest, ImageLayout001, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    LayoutWrapper layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(loadingCtx != nullptr);
    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(altloadingCtx != nullptr);
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).width(400).height(500)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm1 != nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size1 != std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image().width(400).height(500).Alt(ALT_SRC_URL)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm2 != nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size2 != std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image().width(400).height(500).Alt(ALT_SRC_URL)
    */
    auto imageLayoutAlgorithm3 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm3 != nullptr);
    auto size3 = imageLayoutAlgorithm3->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size3 != std::nullopt);
    EXPECT_EQ(size3.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout002
 * @tc.desc: Verify that Image which has no SelfSize can resize with ContainerSize.
 * @tc.type: FUNC
 */
HWTEST_F(ImageLayoutAlgorithmTest, ImageLayout002, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    imageLayoutProperty->UpdateFitOriginalSize(true);
    LayoutWrapper layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(loadingCtx != nullptr);
    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(altloadingCtx != nullptr);
    LayoutConstraintF layoutConstraintSize;
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).fitOriginalSize(true)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm1 != nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size1 != std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Alt(ALT_SRC_URL).fitOriginalSize(true)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm2 != nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size2 != std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout003
 * @tc.desc: Verify that, when there is no srcImage, ImageComponent which has no SelfSize can resize with AltImageSize .
 * @tc.type: FUNC
 */
HWTEST_F(ImageLayoutAlgorithmTest, ImageLayout003, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    imageLayoutProperty->UpdateFitOriginalSize(true);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode != nullptr);
    LayoutWrapper layoutWrapper(nullptr, geometryNode, imageLayoutProperty);
    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(altloadingCtx != nullptr);
    auto imageLayoutAlgorithm = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm != nullptr);
    /**
    //     corresponding ets code:
    //         Image().Alt(ALT_SRC_URL).fitOriginalSize(true)
    */
    LayoutConstraintF layoutConstraintSize;
    auto size = imageLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size != std::nullopt);
    EXPECT_EQ(size.value(), SizeF(ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout004
 * @tc.desc: Verify that, when ImageComponent is set one side, another can resize with ImageSize and its aspectRatio,
 *           whether there is an Alt or not.
 * @tc.type: FUNC
 */
HWTEST_F(ImageLayoutAlgorithmTest, ImageLayout004, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    LayoutWrapper layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(loadingCtx != nullptr);
    double aspectRatio = Size::CalcRatio(SizeF(IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT));

    LayoutConstraintF layoutConstraintSize1;
    layoutConstraintSize1.selfIdealSize.SetWidth(IMAGE_COMPONENTSIZE_WIDTH);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Width(400)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm1 != nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize1, &layoutWrapper);
    EXPECT_TRUE(size1 != std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_WIDTH / aspectRatio));

    LayoutConstraintF layoutConstraintSize2;
    layoutConstraintSize2.selfIdealSize.SetHeight(IMAGE_COMPONENTSIZE_HEIGHT);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Height(500)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm2 != nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize2, &layoutWrapper);
    EXPECT_TRUE(size2 != std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(IMAGE_COMPONENTSIZE_HEIGHT * aspectRatio, IMAGE_COMPONENTSIZE_HEIGHT));

    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    LayoutConstraintF layoutConstraintSize3;
    layoutConstraintSize3.selfIdealSize.SetWidth(IMAGE_COMPONENTSIZE_WIDTH);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Width(400).Alt(ALT_SRC_URL)
    */
    auto imageLayoutAlgorithm3 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm3 != nullptr);
    auto size3 = imageLayoutAlgorithm3->MeasureContent(layoutConstraintSize1, &layoutWrapper);
    EXPECT_TRUE(size3 != std::nullopt);
    EXPECT_EQ(size3.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_WIDTH / aspectRatio));

    LayoutConstraintF layoutConstraintSize4;
    layoutConstraintSize4.selfIdealSize.SetHeight(IMAGE_COMPONENTSIZE_HEIGHT);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Height(500).Alt(ALT_SRC_URL)
    */
    auto imageLayoutAlgorithm4 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm4 != nullptr);
    auto size4 = imageLayoutAlgorithm4->MeasureContent(layoutConstraintSize2, &layoutWrapper);
    EXPECT_TRUE(size4 != std::nullopt);
    EXPECT_EQ(size4.value(), SizeF(IMAGE_COMPONENTSIZE_HEIGHT * aspectRatio, IMAGE_COMPONENTSIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout005
 * @tc.desc: Verify that, when there is not a srcImage and ImageComponent is set one side, and another size can resize
 *           with AltImageSize and its aspectRatio.
 * @tc.type: FUNC
 */
HWTEST_F(ImageLayoutAlgorithmTest, ImageLayout005, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    LayoutWrapper layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(altloadingCtx != nullptr);
    double aspectRatio = Size::CalcRatio(SizeF(ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_HEIGHT));

    LayoutConstraintF layoutConstraintSize1;
    layoutConstraintSize1.selfIdealSize.SetWidth(IMAGE_COMPONENTSIZE_WIDTH);
    /**
    //     corresponding ets code:
    //         Image().Width(400).Alt(ALT_SRC_URL)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm1 != nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize1, &layoutWrapper);
    EXPECT_TRUE(size1 != std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_WIDTH / aspectRatio));

    LayoutConstraintF layoutConstraintSize2;
    layoutConstraintSize2.selfIdealSize.SetHeight(IMAGE_COMPONENTSIZE_HEIGHT);
    /**
    //     corresponding ets code:
    //         Image().Height(500).Alt(ALT_SRC_URL)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm2 != nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize2, &layoutWrapper);
    EXPECT_TRUE(size2 != std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(IMAGE_COMPONENTSIZE_HEIGHT * aspectRatio, IMAGE_COMPONENTSIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout006
 * @tc.desc: Verify that if fitOriginSize is false, ImageComponent can resize with selfSize,
 *           whether there is src or alt.
 * @tc.type: FUNC
 */
HWTEST_F(ImageLayoutAlgorithmTest, ImageLayout006, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    imageLayoutProperty->UpdateFitOriginalSize(false);
    LayoutWrapper layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(loadingCtx != nullptr);
    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(altloadingCtx != nullptr);
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).width(400).height(500).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm1 != nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size1 != std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image().width(400).height(500).Alt(ALT_SRC_URL).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm2 != nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size2 != std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image().width(400).height(500).Alt(ALT_SRC_URL).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm3 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm3 != nullptr);
    auto size3 = imageLayoutAlgorithm3->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size3 != std::nullopt);
    EXPECT_EQ(size3.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout007
 * @tc.desc: Verify that if fitOriginSize is false, ImageComponent which has no size can resize with max
 *           LayoutConstraint, whether there is src or alt.
 * @tc.type: FUNC
 */
HWTEST_F(ImageLayoutAlgorithmTest, ImageLayout007, TestSize.Level1)
{
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(loadingCtx != nullptr);
    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(altloadingCtx != nullptr);
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    imageLayoutProperty->UpdateFitOriginalSize(false);
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize.SetWidth(IMAGE_COMPONENT_MAXSIZE_WIDTH);
    layoutConstraintSize.maxSize.SetHeight(IMAGE_COMPONENT_MAXSIZE_HEIGHT);
    imageLayoutProperty->UpdateLayoutConstraint(layoutConstraintSize);
    LayoutWrapper layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    /**
    //     corresponding ets code:
    //          Row.Width(600).Height(700) {
    //              Image(IMAGE_SRC_URL).fitOriginalSize(false)
    //          }
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm1 != nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size1 != std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_COMPONENT_MAXSIZE_WIDTH, IMAGE_COMPONENT_MAXSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //          Row.Width(600).Height(700) {
    //              Image().Alt(ALT_SRC_URL).fitOriginalSize(false)
    //          }
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm2 != nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size2 != std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(IMAGE_COMPONENT_MAXSIZE_WIDTH, IMAGE_COMPONENT_MAXSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //          Row.Width(600).Height(700) {
    //              Image(IMAGE_SRC_URL).Alt(ALT_SRC_URL).fitOriginalSize(false)
    //          }
    */
    auto imageLayoutAlgorithm3 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm3 != nullptr);
    auto size3 = imageLayoutAlgorithm3->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size3 != std::nullopt);
    EXPECT_EQ(size3.value(), SizeF(IMAGE_COMPONENT_MAXSIZE_WIDTH, IMAGE_COMPONENT_MAXSIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout008
 * @tc.desc: Verify that, when ImageComponent is set one side, another can resize with ImageSize and its aspectRatio,
 *           whether there is an Alt or not, although fitOriginSize is false.
 * @tc.type: FUNC
 */
HWTEST_F(ImageLayoutAlgorithmTest, ImageLayout008, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    imageLayoutProperty->UpdateFitOriginalSize(false);
    LayoutWrapper layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(loadingCtx != nullptr);
    double aspectRatio = Size::CalcRatio(SizeF(IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT));

    LayoutConstraintF layoutConstraintSize1;
    layoutConstraintSize1.selfIdealSize.SetWidth(IMAGE_COMPONENTSIZE_WIDTH);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Width(400).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm1 != nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize1, &layoutWrapper);
    EXPECT_TRUE(size1 != std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_WIDTH / aspectRatio));

    LayoutConstraintF layoutConstraintSize2;
    layoutConstraintSize2.selfIdealSize.SetHeight(IMAGE_COMPONENTSIZE_HEIGHT);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Height(500).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm2 != nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize2, &layoutWrapper);
    EXPECT_TRUE(size2 != std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(IMAGE_COMPONENTSIZE_HEIGHT * aspectRatio, IMAGE_COMPONENTSIZE_HEIGHT));

    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    LayoutConstraintF layoutConstraintSize3;
    layoutConstraintSize3.selfIdealSize.SetWidth(IMAGE_COMPONENTSIZE_WIDTH);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Width(400).Alt(ALT_SRC_URL).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm3 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm3 != nullptr);
    auto size3 = imageLayoutAlgorithm3->MeasureContent(layoutConstraintSize1, &layoutWrapper);
    EXPECT_TRUE(size3 != std::nullopt);
    EXPECT_EQ(size3.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_WIDTH / aspectRatio));

    LayoutConstraintF layoutConstraintSize4;
    layoutConstraintSize4.selfIdealSize.SetHeight(IMAGE_COMPONENTSIZE_HEIGHT);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Height(500).Alt(ALT_SRC_URL).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm4 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm4 != nullptr);
    auto size4 = imageLayoutAlgorithm4->MeasureContent(layoutConstraintSize2, &layoutWrapper);
    EXPECT_TRUE(size4 != std::nullopt);
    EXPECT_EQ(size4.value(), SizeF(IMAGE_COMPONENTSIZE_HEIGHT * aspectRatio, IMAGE_COMPONENTSIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout009
 * @tc.desc: Verify that, when there is not a srcImage and ImageComponent is set one side, and another size can resize
 *           with ImageSize and its aspectRatio, although fitOriginalSize is false.
 * @tc.type: FUNC
 */
HWTEST_F(ImageLayoutAlgorithmTest, ImageLayout009, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    imageLayoutProperty->UpdateFitOriginalSize(false);
    LayoutWrapper layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto altloadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(altloadingCtx != nullptr);
    double aspectRatio = Size::CalcRatio(SizeF(ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_HEIGHT));

    LayoutConstraintF layoutConstraintSize1;
    layoutConstraintSize1.selfIdealSize.SetWidth(IMAGE_COMPONENTSIZE_WIDTH);
    /**
    //     corresponding ets code:
    //         Image().Widrh(400).Alt(ALT_SRC_URL).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm1 != nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize1, &layoutWrapper);
    EXPECT_TRUE(size1 != std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_WIDTH / aspectRatio));

    LayoutConstraintF layoutConstraintSize2;
    layoutConstraintSize2.selfIdealSize.SetHeight(IMAGE_COMPONENTSIZE_HEIGHT);
    /**
    //     corresponding ets code:
    //         Image().Height(500).Alt(ALT_SRC_URL).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx);
    EXPECT_TRUE(imageLayoutAlgorithm2 != nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize2, &layoutWrapper);
    EXPECT_TRUE(size2 != std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(IMAGE_COMPONENTSIZE_HEIGHT * aspectRatio, IMAGE_COMPONENTSIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout010
 * @tc.desc: Verify that ImageComponent which has no SelfSize can resize with ImageSize, whether fitOriginalSize is set
 *           default. FitOriginalSize is false by default.
 * @tc.type: FUNC
 */
HWTEST_F(ImageLayoutAlgorithmTest, ImageLayout010, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize.SetWidth(IMAGE_COMPONENT_MAXSIZE_WIDTH);
    layoutConstraintSize.maxSize.SetHeight(IMAGE_COMPONENT_MAXSIZE_HEIGHT);
    imageLayoutProperty->UpdateLayoutConstraint(layoutConstraintSize);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(loadingCtx != nullptr);
    LayoutWrapper layoutWrapper1(nullptr, nullptr, imageLayoutProperty);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm1 != nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize, &layoutWrapper1);
    EXPECT_TRUE(size1 != std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_COMPONENT_MAXSIZE_WIDTH, IMAGE_COMPONENT_MAXSIZE_HEIGHT));

    imageLayoutProperty->UpdateFitOriginalSize(false);
    LayoutWrapper layoutWrapper2(nullptr, nullptr, imageLayoutProperty);
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm2 != nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize, &layoutWrapper2);
    EXPECT_TRUE(size2 != std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(IMAGE_COMPONENT_MAXSIZE_WIDTH, IMAGE_COMPONENT_MAXSIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout011
 * @tc.desc: Verify that ImageComponent which has no SelfSize, and there has no srcImage or altImage, ImageComponent can
 *           not resize its size.
 * @tc.type: FUNC
 */
HWTEST_F(ImageLayoutAlgorithmTest, ImageLayout011, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    LayoutWrapper layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image()
    */
    auto imageLayoutAlgorithm = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm != nullptr);
    auto size = imageLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_FALSE(size == std::nullopt);
}

/**
 * @tc.name: ImageLayoutFunction001
 * @tc.desc: Verify that ImageLayoutAlgorithm's Layout can carry out successfully.
 * @tc.type: FUNC
 */
HWTEST_F(ImageLayoutAlgorithmTest, ImageLayoutFunction001, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode != nullptr);
    LayoutWrapper layoutWrapper(nullptr, geometryNode, imageLayoutProperty);
    /**
     * @tc.cases: case1. layoutWrapper->GetGeometryNode()->GetContent() == nullptr, func will return.
     */
    auto loadingCtx =
        AceType::MakeRefPtr<ImageLoadingContext>(ImageSourceInfo(), LoadNotifier(nullptr, nullptr, nullptr));
    auto imageLayoutAlgorithm = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx, loadingCtx);
    imageLayoutAlgorithm->Layout(&layoutWrapper);
    /**
     * @tc.cases: case2. layoutWrapper->GetGeometryNode()->GetContent() is true, func success.
     */

    geometryNode->SetContentSize(SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    imageLayoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_EQ(loadingCtx->imageFit_, ImageFit::COVER);
    EXPECT_EQ(loadingCtx->autoResize_, true);
    EXPECT_EQ(loadingCtx->dstSize_, SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
}
} // namespace OHOS::Ace::NG
