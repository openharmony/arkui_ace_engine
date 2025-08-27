/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/window_scene/helper/starting_window_layout_helper.h"

#include <algorithm>

#include "adapter/ohos/entrance/ace_view_ohos.h"
#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/window_scene/scene/system_window_scene.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "session/host/include/session.h"
#include "session_manager/include/scene_session_manager.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension FIXED_TOP_SAFE_AREA_HEIGHT_VP = 36.0_vp;
constexpr Dimension FIXED_BOTTOM_SAFE_AREA_HEIGHT_VP = 28.0_vp;
constexpr Dimension FIXED_BRAND_HORIZONTAL_MARGIN_VP = 24.0_vp;
constexpr Dimension MIN_BRAND_AREA_HEIGHT_VP = 100.0_vp;
constexpr Dimension MAX_BRAND_CONTENT_WIDTH_VP = 400.0_vp;
constexpr Dimension MIN_BRAND_CONTENT_HEIGHT_VP = 80.0_vp;
constexpr float UPPER_AREA_CONTAINER_HEIGHT_PERCENT = 0.7f;
constexpr float BRAND_CONTAINER_HEIGHT_PERCENT = 0.3f;
constexpr float BRAND_CONTENT_HEIGHT_PERCENT = 0.4f;
constexpr float ILLUSTRATION_CONTENT_SIZE_PERCENT = 0.8f;
constexpr float FULL_PERCENT = 1.0f;
constexpr float ZERO_FACTOR = 0.0f;
constexpr float HALF_FACTOR = 0.5f;
constexpr float DOUBLE_FACTOR = 2.0f;
const std::vector<std::pair<float, std::string>> WIDTH_BREAKPOINTS_VP = {
    { 320.0f, "XSmall" },
    { 600.0f, "Small" },
    { 840.0f, "Medium" },
    { 1440.0f, "Large" },
    { FLT_MAX, "XLarge" },
};
const std::vector<std::pair<float, std::string>> ASPECT_RATIO_BREAKPOINTS = {
    { 0.8f, "Landscape" },
    { 1.2f, "Square" },
    { FLT_MAX, "Portrait" },
};

std::string BuildLayoutKey(float widthVp, float aspectRatio)
{
    std::string key = "-";
    for (const auto& p : WIDTH_BREAKPOINTS_VP) {
        if (LessOrEqual(widthVp, p.first)) {
            key = p.second + key;
            break;
        }
    }
    for (const auto& p : ASPECT_RATIO_BREAKPOINTS) {
        if (LessOrEqual(aspectRatio, p.first)) {
            key += p.second;
            break;
        }
    }
    return key;
}

const std::map<std::string, ImageFit> STRING_TO_IMAGEFIT_MAP = {
    { "Contain", ImageFit::CONTAIN },
    { "Cover", ImageFit::COVER },
    { "Auto", ImageFit::FITWIDTH },  // same as the mapping of image pattern
    { "Fill", ImageFit::FILL },
    { "ScaleDown", ImageFit::SCALE_DOWN },
    { "None", ImageFit::NONE },
};

const std::map<std::string, LayoutParams> LAYOUT_RULES_MAP = {
    { "XSmall-Landscape", { 128.0_vp } },
    { "XSmall-Square", { 128.0_vp } },
    { "XSmall-Portrait", { 128.0_vp } },
    { "Small-Landscape", { 128.0_vp } },
    { "Small-Square", { 128.0_vp } },
    { "Small-Portrait", { 192.0_vp } },
    { "Medium-Landscape", { 192.0_vp } },
    { "Medium-Square", { 256.0_vp } },
    { "Medium-Portrait", { 256.0_vp } },
    { "Large-Landscape", { 256.0_vp } },
    { "Large-Square", { 256.0_vp } },
    { "Large-Portrait", { 256.0_vp } },
    { "XLarge-Landscape", { 256.0_vp } },
    { "XLarge-Square", { 256.0_vp } },
    { "XLarge-Portrait", { 256.0_vp } },
};
} // namespace

RefPtr<FrameNode> CreateUpperAreaNode(const ImageSourceInfo& imageSource)
{
    auto upperAreaNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(upperAreaNode, nullptr);
    auto upperAreaLayoutProperty = upperAreaNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(upperAreaLayoutProperty, nullptr);
    upperAreaLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    upperAreaLayoutProperty->UpdateImageSourceInfo(imageSource);
    upperAreaLayoutProperty->UpdateImageFit(ImageFit::SCALE_DOWN);
    upperAreaNode->MarkModifyDone();
    return upperAreaNode;
}

RefPtr<FrameNode> CreateBrandNode(const ImageSourceInfo& brandImageSource)
{
    auto brandNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(brandNode, nullptr);
    auto brandLayoutProperty = brandNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(brandLayoutProperty, nullptr);
    brandLayoutProperty->UpdateImageSourceInfo(brandImageSource);
    brandLayoutProperty->UpdateImageFit(ImageFit::SCALE_DOWN);
    brandNode->MarkModifyDone();
    return brandNode;
}

RefPtr<FrameNode> CreateBackgroundImageNode(
    const std::string& imageFit, const ImageSourceInfo& bgImageSource)
{
    auto bgImgNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(bgImgNode, nullptr);
    auto bgImgLayoutProperty = bgImgNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(bgImgLayoutProperty, nullptr);
    bgImgLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    bgImgLayoutProperty->UpdateImageSourceInfo(bgImageSource);
    auto imageFitType = ImageFit::COVER;
    if (STRING_TO_IMAGEFIT_MAP.find(imageFit) != STRING_TO_IMAGEFIT_MAP.end()) {
        imageFitType = STRING_TO_IMAGEFIT_MAP.at(imageFit);
    }
    bgImgLayoutProperty->UpdateImageFit(imageFitType);
    bgImgNode->MarkModifyDone();
    return bgImgNode;
}

RefPtr<FrameNode> StartingWindowLayoutHelper::CreateStartingWindowNode(
    const Rosen::StartingWindowInfo& startingWindowInfo, const std::string& bundleName, const std::string& moduleName)
{
    startingWindowInfo_ = startingWindowInfo;
    // -root node of starting window
    auto startingWindow = FrameNode::CreateFrameNode(
        V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StackPattern>());
    CHECK_NULL_RETURN(startingWindow, nullptr);
    auto startingWindowLayoutProperty = startingWindow->GetLayoutProperty<StackLayoutProperty>();
    CHECK_NULL_RETURN(startingWindowLayoutProperty, nullptr);
    startingWindowLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    startingWindow->GetRenderContext()->UpdateBackgroundColor(Color(startingWindowInfo_.backgroundColor_));
    startingWindow->SetHitTestMode(HitTestMode::HTMNONE);

    if (!startingWindowInfo_.backgroundImagePath_.empty()) {
        auto bgImgNode = CreateBackgroundImageNode(startingWindowInfo_.backgroundImageFit_,
            ImageSourceInfo(startingWindowInfo_.backgroundImagePath_, bundleName, moduleName));
        startingWindow->AddChild(bgImgNode);
    }

    // --full size container
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    CHECK_NULL_RETURN(columnNode, nullptr);
    auto columnLayoutProps = columnNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(columnLayoutProps, nullptr);
    columnLayoutProps->UpdateMeasureType(MeasureType::MATCH_PARENT);
    
    auto upperAreaNode = CreateUpperAreaNode(ImageSourceInfo(
        startingWindowInfo_.iconPath_.empty() ? startingWindowInfo_.illustrationPath_ : startingWindowInfo_.iconPath_,
        bundleName, moduleName));
    CHECK_NULL_RETURN(upperAreaNode, nullptr);
    columnNode->AddChild(upperAreaNode);
    auto brandNode = CreateBrandNode(ImageSourceInfo(startingWindowInfo_.brandingPath_, bundleName, moduleName));
    CHECK_NULL_RETURN(brandNode, nullptr);
    columnNode->AddChild(brandNode);
    columnNode->MarkModifyDone();

    startingWindow->AddChild(columnNode);
    startingWindow->MarkModifyDone();
    upperAreaNode_ = upperAreaNode;
    brandNode_ = brandNode;
    return startingWindow;
}

void StartingWindowLayoutHelper::MeasureUpperAreaNode(
    const SizeF& parentSize, const RefPtr<FrameNode> upperAreaNode, bool needHideBrand)
{
    auto upperAreaLayoutProperty = upperAreaNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(upperAreaLayoutProperty);
    float upperHeightPercent = needHideBrand ? FULL_PERCENT : UPPER_AREA_CONTAINER_HEIGHT_PERCENT;
    float upperContentSizePx = std::min(parentSize.Height() * HALF_FACTOR, parentSize.Width()) *
        ILLUSTRATION_CONTENT_SIZE_PERCENT;
    if (!startingWindowInfo_.iconPath_.empty()) {
        upperAreaLayoutProperty->UpdateImageFit(ImageFit::CONTAIN);
        CHECK_EQUAL_VOID(NearZero(parentSize.Width()), true);
        auto key = BuildLayoutKey(Dimension(parentSize.Width(), DimensionUnit::PX).ConvertToVp(),
            parentSize.Height() / parentSize.Width());
        if (LAYOUT_RULES_MAP.find(key) != LAYOUT_RULES_MAP.end()) {
            upperContentSizePx = LAYOUT_RULES_MAP.at(key).iconSize.ConvertToPx();
        }
    }
    float totalSafeAreaHeightPx = FIXED_TOP_SAFE_AREA_HEIGHT_VP.ConvertToPx() +
        (needHideBrand ? FIXED_BOTTOM_SAFE_AREA_HEIGHT_VP.ConvertToPx() : ZERO_FACTOR);
    float upperContainerHeightPx = parentSize.Height() * upperHeightPercent - totalSafeAreaHeightPx;
    float upperContentVerticalMarginPx = (upperContainerHeightPx - upperContentSizePx) * HALF_FACTOR;
    MarginProperty upperContentMargin = {
        .top = CalcLength(Dimension(
            upperContentVerticalMarginPx + FIXED_TOP_SAFE_AREA_HEIGHT_VP.ConvertToPx(), DimensionUnit::PX)),
        .bottom = CalcLength(Dimension(upperContentVerticalMarginPx, DimensionUnit::PX)),
    };
    upperAreaLayoutProperty->UpdateMargin(upperContentMargin);
    upperAreaLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(
        CalcLength(Dimension(upperContentSizePx, DimensionUnit::PX)),
        CalcLength(Dimension(upperContentSizePx, DimensionUnit::PX))));
}

void StartingWindowLayoutHelper::MeasureChildNode(const SizeF& parentSize)
{
    auto upperAreaNode = upperAreaNode_.Upgrade();
    CHECK_NULL_VOID(upperAreaNode);
    auto brandNode = brandNode_.Upgrade();
    CHECK_NULL_VOID(brandNode);
    bool needHideBrand = LessOrEqual(parentSize.Height() * BRAND_CONTAINER_HEIGHT_PERCENT,
        MIN_BRAND_AREA_HEIGHT_VP.ConvertToPx());
    MeasureUpperAreaNode(parentSize, upperAreaNode, needHideBrand);

    auto brandLayoutProperty = brandNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(brandLayoutProperty);
    if (needHideBrand) {
        brandLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE, true);
        return;
    }
    brandLayoutProperty->UpdateVisibility(VisibleType::VISIBLE, true);
    float brandWidthPx = std::min(parentSize.Width() - FIXED_BRAND_HORIZONTAL_MARGIN_VP.ConvertToPx() * DOUBLE_FACTOR,
        MAX_BRAND_CONTENT_WIDTH_VP.ConvertToPx());
    float brandContainerHeightPx = parentSize.Height() * BRAND_CONTAINER_HEIGHT_PERCENT -
        FIXED_BOTTOM_SAFE_AREA_HEIGHT_VP.ConvertToPx();
    float brandHeightPx = std::max(brandContainerHeightPx * BRAND_CONTENT_HEIGHT_PERCENT,
        static_cast<float>(MIN_BRAND_CONTENT_HEIGHT_VP.ConvertToPx()));
    float brandVerticalMarginPx = (brandContainerHeightPx - brandHeightPx) * HALF_FACTOR;
    float brandHorizontalMarginPx = (parentSize.Width() - brandWidthPx) * HALF_FACTOR;
    MarginProperty brandMargin = {
        .left = CalcLength(Dimension(brandHorizontalMarginPx, DimensionUnit::PX)),
        .right = CalcLength(Dimension(brandHorizontalMarginPx, DimensionUnit::PX)),
        .top = CalcLength(Dimension(brandVerticalMarginPx, DimensionUnit::PX)),
        .bottom = CalcLength(Dimension(brandVerticalMarginPx + FIXED_BOTTOM_SAFE_AREA_HEIGHT_VP.ConvertToPx(),
            DimensionUnit::PX)),
    };
    brandLayoutProperty->UpdateMargin(brandMargin);
    brandLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(
        CalcLength(Dimension(brandWidthPx, DimensionUnit::PX)),
        CalcLength(Dimension(brandHeightPx, DimensionUnit::PX))));
}
} // namespace OHOS::Ace::NG
