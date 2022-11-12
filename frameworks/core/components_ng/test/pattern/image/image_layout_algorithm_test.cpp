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

#include <optional>

#include "gtest/gtest.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/image/image_layout_algorithm.h"

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
const Dimension IMAGE_SOURCEINFO_WIDTH = Dimension(IMAGE_SOURCESIZE_WIDTH);
const Dimension IMAGE_SOURCEINFO_HEIGHT = Dimension(IMAGE_SOURCESIZE_HEIGHT);
const Dimension ALT_SOURCEINFO_WIDTH = Dimension(ALT_SOURCESIZE_WIDTH);
const Dimension ALT_SOURCEINFO_HEIGHT = Dimension(ALT_SOURCESIZE_HEIGHT);
const std::string IMAGE_SRC_URL = "common/srcexample.jpg";
const std::string ALT_SRC_URL = "common/altexample.jpg";

} // namespace

class ImageLayoutAlgorithmTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void ImageLayoutAlgorithmTest::SetUpTestCase() {}
void ImageLayoutAlgorithmTest::TearDownTestCase() {}
void ImageLayoutAlgorithmTest::SetUp() {}
void ImageLayoutAlgorithmTest::TearDown() {}

class ACE_EXPORT ImageLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(ImageLayoutProperty, LayoutProperty);

public:
    ImageLayoutProperty() = default;
    ~ImageLayoutProperty() override = default;
    static std::optional<LayoutConstraintF> GetLayoutConstraint()
    {
        LayoutConstraintF layoutParentConstraint;
        layoutParentConstraint.UpdateMaxSizeWithCheck(
            SizeF(IMAGE_COMPONENT_MAXSIZE_WIDTH, IMAGE_COMPONENT_MAXSIZE_HEIGHT));
        return std::make_optional<LayoutConstraintF>(layoutParentConstraint);
    }
    void SetFitOriginalSize(bool fitOriginalSize)
    {
        fitOriginalSize_.emplace(fitOriginalSize);
    }
    std::optional<bool> GetFitOriginalSize() const
    {
        return fitOriginalSize_;
    }

    void Clone(RefPtr<LayoutProperty> layoutProperty) const override {}
    RefPtr<LayoutProperty> Clone() const override
    {
        return nullptr;
    }

    void Reset() override {}

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override {}

private:
    std::optional<bool> fitOriginalSize_ = true;
    ACE_DISALLOW_COPY_AND_MOVE(ImageLayoutProperty);
};

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
    auto loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(loadingCtx_ != nullptr);
    auto altloadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(altloadingCtx_ != nullptr);
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).width(400).height(500)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx_, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm1 != nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size1 != std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image().width(400).height(500).Alt(ALT_SRC_URL)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx_);
    EXPECT_TRUE(imageLayoutAlgorithm2 != nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size2 != std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image().width(400).height(500).Alt(ALT_SRC_URL)
    */
    auto imageLayoutAlgorithm3 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx_, altloadingCtx_);
    EXPECT_TRUE(imageLayoutAlgorithm3 != nullptr);
    auto size3 = imageLayoutAlgorithm3->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size3 != std::nullopt);
    EXPECT_EQ(size3.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
}

/**
 * @tc.name: ImageLayout002
 * @tc.desc: Verify that ImageComponent which has no SelfSize can resize with ImageSize, whether there is an Alt or not.
 * @tc.type: FUNC
 */
HWTEST_F(ImageLayoutAlgorithmTest, ImageLayout002, TestSize.Level1)
{
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    EXPECT_TRUE(imageLayoutProperty != nullptr);
    LayoutWrapper layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(loadingCtx_ != nullptr);
    auto altloadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(altloadingCtx_ != nullptr);
    LayoutConstraintF layoutConstraintSize;
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx_, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm1 != nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size1 != std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_SOURCESIZE_WIDTH, IMAGE_SOURCESIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).Alt(ALT_SRC_URL)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx_, altloadingCtx_);
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
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_TRUE(geometryNode != nullptr);
    LayoutWrapper layoutWrapper(nullptr, geometryNode, imageLayoutProperty);
    auto altloadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(altloadingCtx_ != nullptr);
    auto imageLayoutAlgorithm = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx_);
    EXPECT_TRUE(imageLayoutAlgorithm != nullptr);
    /**
    //     corresponding ets code:
    //         Image().Alt(ALT_SRC_URL)
    */
    LayoutConstraintF layoutConstraintSize;
    auto size = imageLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size != std::nullopt);
    EXPECT_EQ(size.value(), SizeF(ALT_SOURCESIZE_WIDTH, ALT_SOURCESIZE_HEIGHT));
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
    imageLayoutProperty->SetFitOriginalSize(false);
    LayoutWrapper layoutWrapper(nullptr, nullptr, imageLayoutProperty);
    auto loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(loadingCtx_ != nullptr);
    auto altloadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(ALT_SRC_URL, ALT_SOURCEINFO_WIDTH, ALT_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(altloadingCtx_ != nullptr);
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image(IMAGE_SRC_URL).width(400).height(500).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm1 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx_, nullptr);
    EXPECT_TRUE(imageLayoutAlgorithm1 != nullptr);
    auto size1 = imageLayoutAlgorithm1->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size1 != std::nullopt);
    EXPECT_EQ(size1.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image().width(400).height(500).Alt(ALT_SRC_URL).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm2 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(nullptr, altloadingCtx_);
    EXPECT_TRUE(imageLayoutAlgorithm2 != nullptr);
    auto size2 = imageLayoutAlgorithm2->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size2 != std::nullopt);
    EXPECT_EQ(size2.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
    /**
    //     corresponding ets code:
    //         Image().width(400).height(500).Alt(ALT_SRC_URL).fitOriginalSize(false)
    */
    auto imageLayoutAlgorithm3 = AceType::MakeRefPtr<ImageLayoutAlgorithm>(loadingCtx_, altloadingCtx_);
    EXPECT_TRUE(imageLayoutAlgorithm3 != nullptr);
    auto size3 = imageLayoutAlgorithm3->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_TRUE(size3 != std::nullopt);
    EXPECT_EQ(size3.value(), SizeF(IMAGE_COMPONENTSIZE_WIDTH, IMAGE_COMPONENTSIZE_HEIGHT));
}

} // namespace OHOS::Ace::NG
