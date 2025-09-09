/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_NG_H

#include <optional>
#include <utility>

#include "base/geometry/dimension_offset.h"
#include "base/geometry/ng/vector.h"
#include "base/geometry/offset.h"
#include "base/geometry/rect.h"
#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/position_param.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/border_image.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/overlay_property.h"
#include "core/components_ng/property/property.h"
#include "core/image/image_source_info.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
class SpanString;
}
namespace OHOS::Ace::NG {
constexpr int32_t MAT4_ZERO = 0;
constexpr int32_t MAT4_ONE = 1;
constexpr int32_t MAT4_TWO = 2;
constexpr int32_t MAT4_THREE = 3;
constexpr int32_t MAT4_FOUR = 4;
constexpr int32_t MAT4_FIVE = 5;
constexpr int32_t MAT4_SIX = 6;
constexpr int32_t MAT4_SEVEN = 7;
constexpr int32_t MAT4_EIGHT = 8;
constexpr int32_t MAT4_NINE = 9;
constexpr int32_t MAT4_TEN = 10;
constexpr int32_t MAT4_ELEVEN = 11;
constexpr int32_t MAT4_TWELVE = 12;
constexpr int32_t MAT4_THIRTEEN = 13;
constexpr int32_t MAT4_FOURTEEN = 14;
constexpr int32_t MAT4_FIFTEEN = 15;

class ACE_FORCE_EXPORT ViewAbstractModelNG : public ViewAbstractModel {
public:
    ~ViewAbstractModelNG() override = default;

    void CreateWithForegroundColorResourceObj(const RefPtr<ResourceObject>& resObj) override
    {
        ViewAbstract::CreateWithForegroundColorResourceObj(resObj);
    }
    void CreateWithOuterBorderColorResourceObj(const RefPtr<ResourceObject>& resObj) override
    {
        ViewAbstract::CreateWithOuterBorderColorResourceObj(resObj);
    }
    void CreateWithOuterBorderRadiusResourceObj(const RefPtr<ResourceObject>& resObj) override
    {
        ViewAbstract::CreateWithOuterBorderRadiusResourceObj(resObj);
    }
    void CreateWithLightColorResourceObj(const RefPtr<ResourceObject>& resObj) override
    {
        ViewAbstract::CreateWithLightColorResourceObj(resObj);
    }
    void CreateWithOuterBorderWidthResourceObj(const RefPtr<ResourceObject>& resObj) override
    {
        ViewAbstract::CreateWithOuterBorderWidthResourceObj(resObj);
    }
    void SetWidth(const CalcDimension& width) override
    {
        if (width.Unit() == DimensionUnit::CALC) {
            ViewAbstract::SetWidth(NG::CalcLength(width.CalcValue()));
        } else {
            ViewAbstract::SetWidth(NG::CalcLength(width));
        }
    }

    void SetWidth(const RefPtr<ResourceObject>& resObj) override
    {
        ViewAbstract::SetWidth(resObj);
    }

    void SetHeight(const CalcDimension& height) override
    {
        if (height.Unit() == DimensionUnit::CALC) {
            ViewAbstract::SetHeight(NG::CalcLength(height.CalcValue()));
        } else {
            ViewAbstract::SetHeight(NG::CalcLength(height));
        }
    }

    void UpdateLayoutPolicyProperty(const LayoutCalPolicy layoutPolicy, bool isWidth) override
    {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_VOID(frameNode);
        auto layoutProperty = frameNode->GetLayoutProperty();
        if (layoutProperty) {
            layoutProperty->UpdateLayoutPolicyProperty(layoutPolicy, isWidth);
        }
    }

    void SetHeight(const RefPtr<ResourceObject>& resObj) override
    {
        ViewAbstract::SetHeight(resObj);
    }

    void ClearWidthOrHeight(bool isWidth) override
    {
        ViewAbstract::ClearWidthOrHeight(isWidth);
    }
    void ResetMinSize(bool resetWidth) override
    {
        ViewAbstract::ResetMinSize(resetWidth);
    }
    void ResetMaxSize(bool resetWidth) override
    {
        ViewAbstract::ResetMaxSize(resetWidth);
    }

    void SetMinWidth(const CalcDimension& minWidth) override
    {
        if (minWidth.Unit() == DimensionUnit::CALC) {
            ViewAbstract::SetMinWidth(NG::CalcLength(minWidth.CalcValue()));
        } else {
            ViewAbstract::SetMinWidth(NG::CalcLength(minWidth));
        }
    }

    void SetMinWidth(const RefPtr<ResourceObject>& resObj) override
    {
        ViewAbstract::SetMinWidth(resObj);
    }

    void SetMinHeight(const CalcDimension& minHeight) override
    {
        if (minHeight.Unit() == DimensionUnit::CALC) {
            ViewAbstract::SetMinHeight(NG::CalcLength(minHeight.CalcValue()));
        } else {
            ViewAbstract::SetMinHeight(NG::CalcLength(minHeight));
        }
    }

    void SetMinHeight(const RefPtr<ResourceObject>& resObj) override
    {
        ViewAbstract::SetMinHeight(resObj);
    }

    void SetMaxWidth(const CalcDimension& maxWidth) override
    {
        if (maxWidth.Unit() == DimensionUnit::CALC) {
            ViewAbstract::SetMaxWidth(NG::CalcLength(maxWidth.CalcValue()));
        } else {
            ViewAbstract::SetMaxWidth(NG::CalcLength(maxWidth));
        }
    }

    void SetMaxWidth(const RefPtr<ResourceObject>& resObj) override
    {
        ViewAbstract::SetMaxWidth(resObj);
    }

    void SetMaxHeight(const CalcDimension& maxHeight) override
    {
        if (maxHeight.Unit() == DimensionUnit::CALC) {
            ViewAbstract::SetMaxHeight(NG::CalcLength(maxHeight.CalcValue()));
        } else {
            ViewAbstract::SetMaxHeight(NG::CalcLength(maxHeight));
        }
    }

    void SetMaxHeight(const RefPtr<ResourceObject>& resObj) override
    {
        ViewAbstract::SetMaxHeight(resObj);
    }

    void SetBackgroundColor(const Color& color) override
    {
        ViewAbstract::SetBackgroundColor(color);
    }

    void SetBackgroundColorWithResourceObj(const Color& color, const RefPtr<ResourceObject>& resObj) override
    {
        ViewAbstract::SetBackgroundColorWithResourceObj(color, resObj);
    }

    void SetBackgroundImage(const ImageSourceInfo& src, RefPtr<ThemeConstants> themeConstant) override
    {
        ViewAbstract::SetBackgroundImage(src);
    }

    void SetBackgroundImageWithResourceObj(
        const RefPtr<ResourceObject>& resObj, const ImageSourceInfo& src, RefPtr<ThemeConstants> themeConstant) override
    {
        ViewAbstract::SetBackgroundImageWithResourceObj(resObj, src);
    }

    void SetBackgroundImageRepeat(const ImageRepeat& imageRepeat) override
    {
        ViewAbstract::SetBackgroundImageRepeat(imageRepeat);
    }

    void SetBackgroundImageSyncMode(bool syncMode) override
    {
        ViewAbstract::SetBackgroundImageSyncMode(syncMode);
    }

    void SetBackgroundImageSize(BackgroundImageSize& bgImgSize) override
    {
        ViewAbstract::SetBackgroundImageSize(bgImgSize);
    }

    void SetBackgroundImageSizeUpdateFunc(
        BackgroundImageSize& bgImgSize, const RefPtr<ResourceObject>& resObj, const std::string direction) override
    {
        ViewAbstract::SetBackgroundImageSizeUpdateFunc(bgImgSize, resObj, direction);
    }

    void SetBackgroundImagePosition(BackgroundImagePosition& bgImgPosition) override
    {
        ViewAbstract::SetBackgroundImagePosition(bgImgPosition);
    }

    void ClearResObj(const std::string resObjName) override
    {
        ViewAbstract::ClearResObj(resObjName);
    }

    void SetBackgroundBlurStyle(const BlurStyleOption& bgBlurStyle, const SysOptions& sysOptions) override
    {
        ViewAbstract::SetBackgroundBlurStyle(bgBlurStyle, sysOptions);
    }

    void SetBackgroundEffect(const EffectOption& effectOption, const SysOptions& sysOptions) override
    {
        ViewAbstract::SetBackgroundEffect(effectOption, sysOptions);
    }

    void SetBackgroundImageResizableSlice(ImageResizableSlice& slice) override
    {
        ViewAbstract::SetBackgroundImageResizableSlice(slice);
    }

    void SetForegroundBlurStyle(const BlurStyleOption& fgBlurStyle, const SysOptions& sysOptions) override
    {
        ViewAbstract::SetForegroundBlurStyle(fgBlurStyle, sysOptions);
    }

    void SetSphericalEffect(double radio) override
    {
        ViewAbstract::SetSphericalEffect(radio);
    }
    void SetPixelStretchEffect(PixStretchEffectOption& option) override
    {
        ViewAbstract::SetPixelStretchEffect(option);
    }
    void SetLightUpEffect(double radio) override
    {
        ViewAbstract::SetLightUpEffect(radio);
    }

    void SetDisallowDropForcedly(bool isDisallowDropForcedly) override
    {
        ViewAbstract::SetDisallowDropForcedly(isDisallowDropForcedly);
    }

    void SetVisualEffect(const OHOS::Rosen::VisualEffect* visualEffect) override
    {
        ViewAbstract::SetVisualEffect(visualEffect);
    }

    void SetBackgroundFilter(const OHOS::Rosen::Filter* backgroundFilter) override
    {
        ViewAbstract::SetBackgroundFilter(backgroundFilter);
    }

    void SetForegroundFilter(const OHOS::Rosen::Filter* foregroundFilter) override
    {
        ViewAbstract::SetForegroundFilter(foregroundFilter);
    }

    void SetCompositingFilter(const OHOS::Rosen::Filter* compositingFilter) override
    {
        ViewAbstract::SetCompositingFilter(compositingFilter);
    }

    void SetPadding(const CalcDimension& value) override
    {
        if (value.Unit() == DimensionUnit::CALC) {
            // padding must great or equal zero.
            ViewAbstract::SetPadding(
                NG::CalcLength(value.IsNonNegative() ? value.CalcValue() : CalcDimension().CalcValue()));
        } else {
            // padding must great or equal zero.
            ViewAbstract::SetPadding(NG::CalcLength(value.IsNonNegative() ? value : CalcDimension()));
        }
    }

    void SetPaddings(const std::optional<CalcDimension>& top, const std::optional<CalcDimension>& bottom,
        const std::optional<CalcDimension>& left, const std::optional<CalcDimension>& right) override
    {
        NG::PaddingProperty paddings = NG::ConvertToCalcPaddingProperty(top, bottom, left, right);
        ViewAbstract::SetPadding(paddings);
    }

    void SetPaddings(const NG::PaddingProperty& paddings) override
    {
        ViewAbstract::SetPadding(paddings);
    }

    void SetPadding(const RefPtr<ResourceObject>& resObj) override
    {
        ViewAbstract::SetPadding(resObj);
    }

    void ResetSafeAreaPadding() override
    {
        ViewAbstract::ResetSafeAreaPadding();
    }

    void SetSafeAreaPadding(const CalcDimension& value) override
    {
        if (value.Unit() == DimensionUnit::CALC) {
            ViewAbstract::SetSafeAreaPadding(NG::CalcLength(value.CalcValue()));
        } else {
            // padding must great or equal zero.
            ViewAbstract::SetSafeAreaPadding(NG::CalcLength(value.IsNonNegative() ? value : CalcDimension()));
        }
    }

    void SetSafeAreaPaddings(const NG::PaddingProperty& paddings) override
    {
        ViewAbstract::SetSafeAreaPadding(paddings);
    }

    void SetSafeAreaPaddings(const std::optional<CalcDimension>& top, const std::optional<CalcDimension>& bottom,
        const std::optional<CalcDimension>& left, const std::optional<CalcDimension>& right) override
    {
        NG::PaddingProperty paddings = NG::ConvertToCalcPaddingProperty(top, bottom, left, right);
        ViewAbstract::SetSafeAreaPadding(paddings);
    }

    void SetMargin(const CalcDimension& value) override
    {
        if (value.Unit() == DimensionUnit::CALC) {
            ViewAbstract::SetMargin(NG::CalcLength(value.CalcValue()));
        } else {
            ViewAbstract::SetMargin(NG::CalcLength(value));
        }
    }

    void SetMargins(const std::optional<CalcDimension>& top, const std::optional<CalcDimension>& bottom,
        const std::optional<CalcDimension>& left, const std::optional<CalcDimension>& right) override
    {
        NG::MarginProperty margins;
        if (top.has_value()) {
            if (top.value().Unit() == DimensionUnit::CALC) {
                margins.top = NG::CalcLength(top.value().CalcValue());
            } else {
                margins.top = NG::CalcLength(top.value());
            }
        }
        if (bottom.has_value()) {
            if (bottom.value().Unit() == DimensionUnit::CALC) {
                margins.bottom = NG::CalcLength(bottom.value().CalcValue());
            } else {
                margins.bottom = NG::CalcLength(bottom.value());
            }
        }
        if (left.has_value()) {
            if (left.value().Unit() == DimensionUnit::CALC) {
                margins.left = NG::CalcLength(left.value().CalcValue());
            } else {
                margins.left = NG::CalcLength(left.value());
            }
        }
        if (right.has_value()) {
            if (right.value().Unit() == DimensionUnit::CALC) {
                margins.right = NG::CalcLength(right.value().CalcValue());
            } else {
                margins.right = NG::CalcLength(right.value());
            }
        }
        ViewAbstract::SetMargin(margins);
    }

    void SetMargins(const NG::MarginProperty& margins) override
    {
        ViewAbstract::SetMargin(margins);
    }

    void SetMargin(const RefPtr<ResourceObject>& resObj) override
    {
        ViewAbstract::SetMargin(resObj);
    }

    void SetBorderRadius(const Dimension& value) override
    {
        ViewAbstract::SetBorderRadius(value);
    }

    void SetBorderRadius(const std::optional<Dimension>& radiusTopLeft, const std::optional<Dimension>& radiusTopRight,
        const std::optional<Dimension>& radiusBottomLeft, const std::optional<Dimension>& radiusBottomRight) override
    {
        NG::BorderRadiusProperty borderRadius;
        borderRadius.radiusTopLeft = radiusTopLeft;
        borderRadius.radiusTopRight = radiusTopRight;
        borderRadius.radiusBottomLeft = radiusBottomLeft;
        borderRadius.radiusBottomRight = radiusBottomRight;
        borderRadius.multiValued = true;
        ViewAbstract::SetBorderRadius(borderRadius);
    }

    void SetBorderRadius(const NG::BorderRadiusProperty& borderRadius) override
    {
        ViewAbstract::SetBorderRadius(borderRadius);
    }

    void SetBorderRadius(const RefPtr<ResourceObject>& resobj) override
    {
        ViewAbstract::SetBorderRadius(resobj);
    }

    void SetBorderColor(const Color& value) override
    {
        ViewAbstract::SetBorderColor(value);
    }
    void SetBorderColor(const std::optional<Color>& colorLeft, const std::optional<Color>& colorRight,
        const std::optional<Color>& colorTop, const std::optional<Color>& colorBottom) override
    {
        NG::BorderColorProperty borderColors;
        borderColors.leftColor = colorLeft;
        borderColors.rightColor = colorRight;
        borderColors.topColor = colorTop;
        borderColors.bottomColor = colorBottom;
        borderColors.multiValued = true;
        ViewAbstract::SetBorderColor(borderColors);
    }

    void SetBorderColor(const NG::BorderColorProperty& borderColors) override
    {
        ViewAbstract::SetBorderColor(borderColors);
    }

    void SetBorderColor(const RefPtr<ResourceObject>& resobj) override
    {
        ViewAbstract::SetBorderColor(resobj);
    }

    void SetBorderWidth(const Dimension& value) override
    {
        ViewAbstract::SetBorderWidth(value);
    }

    void SetBorderWidth(const std::optional<Dimension>& left, const std::optional<Dimension>& right,
        const std::optional<Dimension>& top, const std::optional<Dimension>& bottom) override
    {
        NG::BorderWidthProperty borderWidth;
        borderWidth.leftDimen = left;
        borderWidth.rightDimen = right;
        borderWidth.topDimen = top;
        borderWidth.bottomDimen = bottom;
        borderWidth.multiValued = true;
        ViewAbstract::SetBorderWidth(borderWidth);
    }

    void SetBorderWidth(const std::optional<Dimension>& start, const std::optional<Dimension>& end,
        const std::optional<Dimension>& top, const std::optional<Dimension>& bottom, bool isLocalized) override
    {
        if (!isLocalized) {
            return;
        }
        NG::BorderWidthProperty borderWidth {
            .topDimen = top, .bottomDimen = bottom, .startDimen = start, .endDimen = end, .multiValued = true
        };
        ViewAbstract::SetBorderWidth(borderWidth);
    }

    void SetBorderWidth(const RefPtr<ResourceObject>& resobj) override
    {
        ViewAbstract::SetBorderWidth(resobj);
    }

    void SetBorderWidth(const NG::BorderWidthProperty& value) override
    {
        ViewAbstract::SetBorderWidth(value);
    }

    void SetBorderStyle(const BorderStyle& value) override
    {
        ViewAbstract::SetBorderStyle(value);
    }

    void SetBorderStyle(const std::optional<BorderStyle>& styleLeft, const std::optional<BorderStyle>& styleRight,
        const std::optional<BorderStyle>& styleTop, const std::optional<BorderStyle>& styleBottom) override
    {
        NG::BorderStyleProperty borderStyles;
        borderStyles.styleLeft = styleLeft.value_or(BorderStyle::SOLID);
        borderStyles.styleRight = styleRight.value_or(BorderStyle::SOLID);
        borderStyles.styleTop = styleTop.value_or(BorderStyle::SOLID);
        borderStyles.styleBottom = styleBottom.value_or(BorderStyle::SOLID);
        borderStyles.multiValued = true;
        ViewAbstract::SetBorderStyle(borderStyles);
    }

    void SetDashGap(const Dimension& value) override
    {
        ViewAbstract::SetDashGap(value);
    }

    void SetDashGap(const std::optional<Dimension>& left, const std::optional<Dimension>& right,
        const std::optional<Dimension>& top, const std::optional<Dimension>& bottom) override
    {
        NG::BorderWidthProperty dashGap;
        dashGap.leftDimen = left;
        dashGap.rightDimen = right;
        dashGap.topDimen = top;
        dashGap.bottomDimen = bottom;
        dashGap.multiValued = true;
        ViewAbstract::SetDashGap(dashGap);
    }

    void SetDashGap(const NG::BorderWidthProperty& value) override
    {
        ViewAbstract::SetDashGap(value);
    }

    void SetDashWidth(const Dimension& value) override
    {
        ViewAbstract::SetDashWidth(value);
    }

    void SetDashWidth(const std::optional<Dimension>& left, const std::optional<Dimension>& right,
        const std::optional<Dimension>& top, const std::optional<Dimension>& bottom) override
    {
        NG::BorderWidthProperty dashWidth;
        dashWidth.leftDimen = left;
        dashWidth.rightDimen = right;
        dashWidth.topDimen = top;
        dashWidth.bottomDimen = bottom;
        dashWidth.multiValued = true;
        ViewAbstract::SetDashWidth(dashWidth);
    }

    void SetDashWidth(const NG::BorderWidthProperty& value) override
    {
        ViewAbstract::SetDashWidth(value);
    }

    void SetOuterBorderRadius(const Dimension& value) override
    {
        ViewAbstract::SetOuterBorderRadius(value);
    }

    void SetOuterBorderRadius(const std::optional<Dimension>& radiusTopLeft,
        const std::optional<Dimension>& radiusTopRight, const std::optional<Dimension>& radiusBottomLeft,
        const std::optional<Dimension>& radiusBottomRight) override
    {
        NG::BorderRadiusProperty borderRadius;
        borderRadius.radiusTopLeft = radiusTopLeft;
        borderRadius.radiusTopRight = radiusTopRight;
        borderRadius.radiusBottomLeft = radiusBottomLeft;
        borderRadius.radiusBottomRight = radiusBottomRight;
        borderRadius.multiValued = true;
        ViewAbstract::SetOuterBorderRadius(borderRadius);
    }

    void SetOuterBorderRadius(const NG::BorderRadiusProperty& borderRadius) override
    {
        ViewAbstract::SetOuterBorderRadius(borderRadius);
    }

    void SetOuterBorderColor(const Color& value) override
    {
        ViewAbstract::SetOuterBorderColor(value);
    }
    void SetOuterBorderColor(const std::optional<Color>& colorLeft, const std::optional<Color>& colorRight,
        const std::optional<Color>& colorTop, const std::optional<Color>& colorBottom) override
    {
        NG::BorderColorProperty borderColors;
        borderColors.leftColor = colorLeft;
        borderColors.rightColor = colorRight;
        borderColors.topColor = colorTop;
        borderColors.bottomColor = colorBottom;
        borderColors.multiValued = true;
        ViewAbstract::SetOuterBorderColor(borderColors);
    }

    void SetOuterBorderColor(const NG::BorderColorProperty& borderColors) override
    {
        ViewAbstract::SetOuterBorderColor(borderColors);
    }

    void SetOuterBorderWidth(const Dimension& value) override
    {
        ViewAbstract::SetOuterBorderWidth(value);
    }

    void SetOuterBorderWidthNew(const NG::BorderWidthProperty& property) override
    {
        ViewAbstract::SetOuterBorderWidth(property);
    }

    void SetOuterBorderWidth(const std::optional<Dimension>& left, const std::optional<Dimension>& right,
        const std::optional<Dimension>& top, const std::optional<Dimension>& bottom) override
    {
        NG::BorderWidthProperty borderWidth;
        borderWidth.leftDimen = left;
        borderWidth.rightDimen = right;
        borderWidth.topDimen = top;
        borderWidth.bottomDimen = bottom;
        borderWidth.multiValued = true;
        ViewAbstract::SetOuterBorderWidth(borderWidth);
    }

    void SetOuterBorderStyle(const BorderStyle& value) override
    {
        ViewAbstract::SetOuterBorderStyle(value);
    }

    void SetOuterBorderStyle(const std::optional<BorderStyle>& styleLeft, const std::optional<BorderStyle>& styleRight,
        const std::optional<BorderStyle>& styleTop, const std::optional<BorderStyle>& styleBottom) override
    {
        NG::BorderStyleProperty borderStyles;
        borderStyles.styleLeft = styleLeft.value_or(BorderStyle::SOLID);
        borderStyles.styleRight = styleRight.value_or(BorderStyle::SOLID);
        borderStyles.styleTop = styleTop.value_or(BorderStyle::SOLID);
        borderStyles.styleBottom = styleBottom.value_or(BorderStyle::SOLID);
        borderStyles.multiValued = true;
        ViewAbstract::SetOuterBorderStyle(borderStyles);
    }

    void SetBorderImage(const RefPtr<BorderImage>& borderImage, uint8_t bitset) override
    {
        CHECK_NULL_VOID(borderImage);
        if (bitset & BorderImage::SOURCE_BIT) {
            ViewAbstract::SetBorderImageSource(
                borderImage->GetSrc(), borderImage->GetBundleName(), borderImage->GetModuleName());
        }
        if (bitset & BorderImage::OUTSET_BIT) {
            ViewAbstract::SetHasBorderImageOutset(true);
        }
        if (bitset & BorderImage::SLICE_BIT) {
            ViewAbstract::SetHasBorderImageSlice(true);
        }
        if (bitset & BorderImage::REPEAT_BIT) {
            ViewAbstract::SetHasBorderImageRepeat(true);
        }
        if (bitset & BorderImage::WIDTH_BIT) {
            ViewAbstract::SetHasBorderImageWidth(true);
        }
        ViewAbstract::SetBorderImage(borderImage);
    }

    void SetBorderImageGradient(const NG::Gradient& gradient) override
    {
        ViewAbstract::SetBorderImageGradient(gradient);
    }

    void SetLayoutPriority(int32_t priority) override {}

    void SetLayoutWeight(float value) override
    {
        ViewAbstract::SetLayoutWeight(value);
    }

    void SetChainWeight(const ChainWeightPair& value) override
    {
        ViewAbstract::SetChainWeight(value);
    }

    void SetPixelRound(uint16_t value) override
    {
        ViewAbstract::SetPixelRound(value);
    }

    void SetLayoutDirection(TextDirection value) override
    {
        ViewAbstract::SetLayoutDirection(value);
    }

    void SetAspectRatio(float ratio) override
    {
        ViewAbstract::SetAspectRatio(ratio);
    }

    void ResetAspectRatio() override
    {
        ViewAbstract::ResetAspectRatio();
    }

    void SetAlign(const Alignment& alignment) override
    {
        ViewAbstract::SetAlign(alignment);
    }

    void SetAlign(const std::string& localizedAlignment) override
    {
        ViewAbstract::SetAlign(localizedAlignment);
    }

    void SetLayoutGravity(const Alignment& alignment) override
    {
        ViewAbstract::SetLayoutGravity(alignment);
    }

    void SetIsMirrorable(const bool& isMirrorable) override
    {
        ViewAbstract::SetIsMirrorable(isMirrorable);
    }

    void SetAlignRules(const std::map<AlignDirection, AlignRule>& alignRules) override
    {
        ViewAbstract::SetAlignRules(alignRules);
    }

    void SetChainStyle(const ChainInfo& chainInfo) override
    {
        ViewAbstract::SetChainStyle(chainInfo);
    }

    void SetBias(const BiasPair& biasPair) override
    {
        ViewAbstract::SetBias(biasPair);
    }

    void SetUseAlign(
        AlignDeclarationPtr declaration, AlignDeclaration::Edge edge, const std::optional<Dimension>& offset) override
    {}

    void SetGrid(std::optional<uint32_t> span, std::optional<int32_t> offset,
        GridSizeType type = GridSizeType::UNDEFINED) override
    {
        ViewAbstract::SetGrid(span, offset, type);
    }

    void SetZIndex(int32_t value) override
    {
        ViewAbstract::SetZIndex(value);
    }

    void SetPosition(const Dimension& x, const Dimension& y) override
    {
        ViewAbstract::SetPosition({ x, y });
    }

    void SetPosition(const Dimension& x, const Dimension& y,
        const RefPtr<ResourceObject>& xresObj, const RefPtr<ResourceObject>& yresObj) override
    {
        ViewAbstract::SetPosition(x, y, xresObj, yresObj);
    }

    void SetPositionEdges(const EdgesParam& value) override
    {
        ViewAbstract::SetPositionEdges(value);
    }

    void ResetPosition() override
    {
        ViewAbstract::ResetPosition();
    }

    void SetOffset(const Dimension& x, const Dimension& y) override
    {
        ViewAbstract::SetOffset({ x, y });
    }

    void SetOffset(const Dimension& x, const Dimension& y,
        const RefPtr<ResourceObject>& xresObj, const RefPtr<ResourceObject>& yresObj) override
    {
        ViewAbstract::SetOffset(x, y, xresObj, yresObj);
    }

    void SetOffsetEdges(const EdgesParam& value) override
    {
        ViewAbstract::SetOffsetEdges(value);
    }

    void MarkAnchor(const Dimension& x, const Dimension& y) override
    {
        ViewAbstract::MarkAnchor({ x, y });
    }

    void MarkAnchor(const Dimension& x, const Dimension& y,
        const RefPtr<ResourceObject>& xresObj, const RefPtr<ResourceObject>& yresObj) override
    {
        ViewAbstract::MarkAnchor(x, y, xresObj, yresObj);
    }

    void SetScale(float x, float y, float z) override;

    void SetPivot(const Dimension& x, const Dimension& y, const Dimension& z) override;

    void SetTranslate(const Dimension& x, const Dimension& y, const Dimension& z) override
    {
        ViewAbstract::SetTranslate(TranslateOptions(x, y, z));
    }

    void SetRotate(float x, float y, float z, float angle, float perspective = 0.0f) override
    {
        ViewAbstract::SetRotate(NG::Vector5F(x, y, z, angle, perspective));
    }

    void SetRotateAngle(float x, float y, float z, float perspective) override
    {
        ViewAbstract::SetRotateAngle(NG::Vector4F(x, y, z, perspective));
    }

    void SetTransformMatrix(const std::vector<float>& matrix) override
    {
        NG::ViewAbstract::SetTransformMatrix(
            Matrix4(matrix[0], matrix[4], matrix[8], matrix[12], matrix[1], matrix[5], matrix[9], matrix[13], matrix[2],
                matrix[6], matrix[10], matrix[14], matrix[3], matrix[7], matrix[11], matrix[15]));
    }

    void SetTransform3DMatrix(const std::vector<float>& matrix) override
    {
        NG::ViewAbstract::SetTransform3DMatrix(Matrix4(matrix[MAT4_ZERO], matrix[MAT4_FOUR], matrix[MAT4_EIGHT],
            matrix[MAT4_TWELVE], matrix[MAT4_ONE], matrix[MAT4_FIVE], matrix[MAT4_NINE], matrix[MAT4_THIRTEEN],
            matrix[MAT4_TWO], matrix[MAT4_SIX], matrix[MAT4_TEN], matrix[MAT4_FOURTEEN], matrix[MAT4_THREE],
            matrix[MAT4_SEVEN], matrix[MAT4_ELEVEN], matrix[MAT4_FIFTEEN]));
    }

    void SetOpacity(double opacity, bool passThrough = false) override
    {
        ViewAbstract::SetOpacity(opacity);
    }

    void CreateWithOpacityResourceObj(const RefPtr<ResourceObject>& resobj) override
    {
        ViewAbstract::CreateWithOpacityResourceObj(resobj);
    }

    void SetTransition(const NG::TransitionOptions& transitionOptions, bool passThrough = false) override
    {
        ViewAbstract::SetTransition(transitionOptions);
    }

    void CleanTransition() override
    {
        ViewAbstract::CleanTransition();
    }

    void SetChainedTransition(const RefPtr<NG::ChainedTransitionEffect>& effect,
        NG::TransitionFinishCallback&& finishCallback = nullptr) override
    {
        ViewAbstract::SetChainedTransition(effect, std::move(finishCallback));
    }

    void SetOverlay(const std::string& text, std::function<void()>&& buildFunc,
        const RefPtr<NG::FrameNode>& contentNode, const std::optional<Alignment>& align,
        const std::optional<Dimension>& offsetX, const std::optional<Dimension>& offsetY, NG::OverlayType type) override
    {
        if (type == NG::OverlayType::BUILDER) {
            ViewAbstract::SetOverlayBuilder(std::move(buildFunc), align, offsetX, offsetY);
        } else if (type == NG::OverlayType::COMPONENT_CONTENT) {
            ViewAbstract::SetOverlayComponentContent(contentNode, align, offsetX, offsetY);
        } else {
            NG::OverlayOptions overlay;
            overlay.content = text;
            overlay.align = align.value_or(Alignment::TOP_LEFT);
            if (offsetX.has_value()) {
                overlay.x = offsetX.value();
            }
            if (offsetY.has_value()) {
                overlay.y = offsetY.value();
            }
            ViewAbstract::SetOverlay(overlay);
            if (type == NG::OverlayType::RESET) {
                ViewAbstract::SetOverlayBuilder(nullptr, align, offsetX, offsetY);
            }
        }
    }

    void SetVisibility(VisibleType visible, std::function<void(int32_t)>&& changeEventFunc) override
    {
        ViewAbstract::SetVisibility(visible);
    }

    void SetSharedTransition(const std::string& shareId, const std::shared_ptr<SharedTransitionOption>& option) override
    {
        ViewAbstract::SetSharedTransition(shareId, option);
    }

    void SetGeometryTransition(const std::string& id,
        bool followWithoutTransition = false, bool doRegisterSharedTransition = true) override
    {
        ViewAbstract::SetGeometryTransition(id, followWithoutTransition, doRegisterSharedTransition);
    }

    void SetMotionPath(const MotionPathOption& option) override
    {
        ViewAbstract::SetMotionPath(option);
    }

    void SetRenderGroup(bool isRenderGroup) override
    {
        ViewAbstract::SetRenderGroup(isRenderGroup);
    }

    void SetRenderFit(RenderFit renderFit) override
    {
        ViewAbstract::SetRenderFit(renderFit);
    }

    void SetFlexBasis(const Dimension& value) override
    {
        ViewAbstract::SetFlexBasis(value);
    }

    void SetAlignSelf(FlexAlign value) override
    {
        ViewAbstract::SetAlignSelf(value);
    }

    void SetFlexShrink(float value) override
    {
        ViewAbstract::SetFlexShrink(value);
    }

    void ResetFlexShrink() override
    {
        ViewAbstract::ResetFlexShrink();
    }

    void SetFlexGrow(float value) override
    {
        ViewAbstract::SetFlexGrow(value);
    }

    void SetDisplayIndex(int32_t value) override
    {
        ViewAbstract::SetDisplayIndex(value);
    }

    void SetLinearGradient(const NG::Gradient& gradient) override
    {
        ViewAbstract::SetLinearGradient(gradient);
    }

    void SetSweepGradient(const NG::Gradient& gradient) override
    {
        ViewAbstract::SetSweepGradient(gradient);
    }

    void SetRadialGradient(const NG::Gradient& gradient) override
    {
        ViewAbstract::SetRadialGradient(gradient);
    }

    void SetClipShape(const RefPtr<BasicShape>& basicShape) override
    {
        ViewAbstract::SetClipShape(basicShape);
    }

    void SetClipEdge(bool isClip) override
    {
        ViewAbstract::SetClipEdge(isClip);
    }

    void SetMask(const RefPtr<BasicShape>& shape) override
    {
        ViewAbstract::SetMask(shape);
    }

    void SetProgressMask(const RefPtr<NG::ProgressMaskProperty>& progress) override
    {
        ViewAbstract::SetProgressMask(progress);
    }

    void SetBackdropBlur(const Dimension& radius, const BlurOption& blurOption, const SysOptions& sysOptions) override
    {
        ViewAbstract::SetBackdropBlur(radius, blurOption, sysOptions);
    }

    void SetLinearGradientBlur(NG::LinearGradientBlurPara blurPara) override
    {
        ViewAbstract::SetLinearGradientBlur(blurPara);
    }

    void SetDynamicDim(float DimDegree) override
    {
        ViewAbstract::SetDynamicDim(DimDegree);
    }
    void SetDynamicLightUp(float rate, float lightUpDegree) override
    {
        ViewAbstract::SetDynamicLightUp(rate, lightUpDegree);
    }

    void SetBgDynamicBrightness(const BrightnessOption& brightnessOption) override
    {
        ViewAbstract::SetBgDynamicBrightness(brightnessOption);
    }

    void SetFgDynamicBrightness(const BrightnessOption& brightnessOption) override
    {
        ViewAbstract::SetFgDynamicBrightness(brightnessOption);
    }

    void SetBlender(const OHOS::Rosen::Blender* blender) override
    {
        ViewAbstract::SetBlender(blender);
    }

    void SetFrontBlur(const Dimension& radius, const BlurOption& blurOption, const SysOptions& sysOptions) override
    {
        ViewAbstract::SetFrontBlur(radius, blurOption, sysOptions);
    }

    void SetMotionBlur(const MotionBlurOption& motionBlurOption) override
    {
        ViewAbstract::SetMotionBlur(motionBlurOption);
    }

    void SetBackShadow(const std::vector<Shadow>& shadows) override
    {
        if (!shadows.empty()) {
            ViewAbstract::SetBackShadow(shadows[0]);
        }
    }

    void SetBlendMode(BlendMode blendMode) override
    {
        ViewAbstract::SetBlendMode(blendMode);
    }

    void SetBlendApplyType(BlendApplyType blendApplyType) override
    {
        ViewAbstract::SetBlendApplyType(blendApplyType);
    }

    void SetColorBlend(const Color& value) override
    {
        ViewAbstract::SetColorBlend(value);
    }

    void CreateWithColorBlendResourceObj(const RefPtr<ResourceObject>& resobj) override
    {
        ViewAbstract::CreateWithColorBlendResourceObj(resobj);
    }

    void SetWindowBlur(float progress, WindowBlurStyle blurStyle) override {}

    void SetBrightness(const Dimension& value) override
    {
        ViewAbstract::SetBrightness(value);
    }

    void SetGrayScale(const Dimension& value) override
    {
        ViewAbstract::SetGrayScale(value);
    }

    void SetContrast(const Dimension& value) override
    {
        ViewAbstract::SetContrast(value);
    }

    void SetSaturate(const Dimension& value) override
    {
        ViewAbstract::SetSaturate(value);
    }

    void SetSepia(const Dimension& value) override
    {
        ViewAbstract::SetSepia(value);
    }

    void SetInvert(const InvertVariant& value) override
    {
        ViewAbstract::SetInvert(value);
    }

    void SetSystemBarEffect(bool systemBarEffect) override
    {
        ViewAbstract::SetSystemBarEffect(systemBarEffect);
    }

    void SetHueRotate(float value) override
    {
        ViewAbstract::SetHueRotate(value);
    }

    void SetUseEffect(bool useEffect, EffectType effectType) override
    {
        ViewAbstract::SetUseEffect(useEffect, effectType);
    }

    void SetUseShadowBatching(bool useShadowBatching) override
    {
        ViewAbstract::SetUseShadowBatching(useShadowBatching);
    }

    void SetFreeze(bool freeze) override
    {
        ViewAbstract::SetFreeze(freeze);
    }

    void SetClickEffectLevel(const ClickEffectLevel& level, float scaleValue) override
    {
        ViewAbstract::SetClickEffectLevel(level, scaleValue);
    }

    void SetOnClick(GestureEventFunc&& tapEventFunc, ClickEventFunc&& clickEventFunc, double distanceThreshold) override
    {
        ViewAbstract::SetOnClick(std::move(tapEventFunc), distanceThreshold);
    }

    void SetOnClick(GestureEventFunc&& tapEventFunc, ClickEventFunc&& clickEventFunc,
        Dimension distanceThreshold) override
    {
        ViewAbstract::SetOnClick(std::move(tapEventFunc), distanceThreshold);
    }

    void SetOnGestureJudgeBegin(NG::GestureJudgeFunc&& gestureJudgeFunc) override
    {
        ViewAbstract::SetOnGestureJudgeBegin(std::move(gestureJudgeFunc));
    }

    void SetOnTouchIntercept(NG::TouchInterceptFunc&& touchInterceptFunc) override
    {
        ViewAbstract::SetOnTouchIntercept(std::move(touchInterceptFunc));
    }

    void SetShouldBuiltInRecognizerParallelWith(
        NG::ShouldBuiltInRecognizerParallelWithFunc&& shouldBuiltInRecognizerParallelWithFunc) override
    {
        ViewAbstract::SetShouldBuiltInRecognizerParallelWith(std::move(shouldBuiltInRecognizerParallelWithFunc));
    }

    void SetOnGestureRecognizerJudgeBegin(
        NG::GestureRecognizerJudgeFunc&& gestureRecognizerJudgeFunc, bool exposeInnerGestureFlag) override
    {
        ViewAbstract::SetOnGestureRecognizerJudgeBegin(std::move(gestureRecognizerJudgeFunc), exposeInnerGestureFlag);
    }

    void SetOnTouchTestDone(NG::TouchTestDoneCallback&& touchTestDoneCallback) override
    {
        ViewAbstract::SetOnTouchTestDone(std::move(touchTestDoneCallback));
    }

    void SetOnTouch(TouchEventFunc&& touchEventFunc) override
    {
        ViewAbstract::SetOnTouch(std::move(touchEventFunc));
    }

    void SetOnKeyEvent(OnKeyConsumeFunc&& onKeyCallback) override
    {
        ViewAbstract::SetOnKeyEvent(std::move(onKeyCallback));
    }

#ifdef SUPPORT_DIGITAL_CROWN
    void SetOnCrownEvent(OnCrownCallbackFunc&& onCrownCallback) override
    {
        ViewAbstract::SetOnCrownEvent(std::move(onCrownCallback));
    }
#endif
    void SetOnKeyPreIme(OnKeyConsumeFunc&& onKeyCallback) override
    {
        auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusHub->SetOnKeyPreIme(std::move(onKeyCallback));
    }

    void SetOnKeyEventDispatch(OnKeyEventDispatchFunc&& onKeyCallback) override
    {
        ViewAbstract::SetOnKeyEventDispatch(std::move(onKeyCallback));
    }

    static void SetOnKeyPreIme(FrameNode* frameNode, OnKeyConsumeFunc&& onKeyCallback)
    {
        auto focusHub = frameNode->GetOrCreateFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusHub->SetOnKeyPreIme(std::move(onKeyCallback));
    }

    void SetOnMouse(OnMouseEventFunc&& onMouseEventFunc) override
    {
        ViewAbstract::SetOnMouse(std::move(onMouseEventFunc));
    }

    void SetOnAxisEvent(OnAxisEventFunc&& onAxisEventFunc) override
    {
        ViewAbstract::SetOnAxisEvent(std::move(onAxisEventFunc));
    }

    void SetOnHover(OnHoverFunc&& onHoverEventFunc) override
    {
        ViewAbstract::SetOnHover(std::move(onHoverEventFunc));
    }

    void SetOnHoverMove(OnHoverMoveFunc&& onHoverMoveEventFunc) override
    {
        ViewAbstract::SetOnHoverMove(std::move(onHoverMoveEventFunc));
    }

    void SetOnAccessibilityHover(OnAccessibilityHoverFunc&& onAccessibilityHoverEventFunc) override
    {
        ViewAbstract::SetOnAccessibilityHover(std::move(onAccessibilityHoverEventFunc));
    }

    void SetOnDelete(std::function<void()>&& onDeleteCallback) override {}

    void SetOnAppear(std::function<void()>&& onAppearCallback) override
    {
        ViewAbstract::SetOnAppear(std::move(onAppearCallback));
    }

    void SetOnAttach(std::function<void()>&& onAttachCallback) override
    {
        ViewAbstract::SetOnAttach(std::move(onAttachCallback));
    }

    void SetOnDisAppear(std::function<void()>&& onDisAppearCallback) override
    {
        ViewAbstract::SetOnDisappear(std::move(onDisAppearCallback));
    }

    void SetOnDetach(std::function<void()>&& onDetachCallback) override
    {
        ViewAbstract::SetOnDetach(std::move(onDetachCallback));
    }

    void SetOnAccessibility(std::function<void(const std::string&)>&& onAccessibilityCallback) override {}

    void SetOnRemoteMessage(RemoteCallback&& onRemoteCallback) override {}

    void SetOnFocusMove(std::function<void(int32_t)>&& onFocusMoveCallback) override {}

    void SetOnFocus(OnFocusFunc&& onFocusCallback) override
    {
        ViewAbstract::SetOnFocus(std::move(onFocusCallback));
    }

    void SetOnBlur(OnBlurFunc&& onBlurCallback) override
    {
        ViewAbstract::SetOnBlur(std::move(onBlurCallback));
    }

    void SetOnFocusAxisEvent(OnFocusAxisEventFunc&& onFocusAxisCallback) override
    {
        ViewAbstract::SetOnFocusAxisEvent(std::move(onFocusAxisCallback));
    }

    void SetDraggable(bool draggable) override
    {
        ViewAbstract::SetDraggable(draggable);
    }

    void SetDragPreviewOptions(const DragPreviewOption& previewOption) override
    {
        ViewAbstract::SetDragPreviewOptions(previewOption);
    }

    void SetOnDragStart(NG::OnDragStartFunc&& onDragStart) override
    {
        auto dragStart = [dragStartFunc = std::move(onDragStart)](const RefPtr<OHOS::Ace::DragEvent>& event,
                             const std::string& extraParams) -> DragDropInfo {
            auto dragInfo = dragStartFunc(event, extraParams);
            DragDropInfo info;
            info.extraInfo = dragInfo.extraInfo;
            info.pixelMap = dragInfo.pixelMap;
            info.customNode = AceType::DynamicCast<UINode>(dragInfo.node);
            return info;
        };
        ViewAbstract::SetOnDragStart(std::move(dragStart));
    }

    static void SetOnDragStart(FrameNode* frameNode, NG::OnDragStartFunc&& onDragStart)
    {
        auto dragStart = [dragStartFunc = std::move(onDragStart)](const RefPtr<OHOS::Ace::DragEvent>& event,
                             const std::string& extraParams) -> DragDropInfo {
            auto dragInfo = dragStartFunc(event, extraParams);
            DragDropInfo info;
            info.extraInfo = dragInfo.extraInfo;
            info.pixelMap = dragInfo.pixelMap;
            info.customNode = AceType::DynamicCast<UINode>(dragInfo.node);
            return info;
        };
        ViewAbstract::SetOnDragStart(frameNode, std::move(dragStart));
    }

    void SetOnPreDrag(NG::OnPreDragFunc&& onPreDrag) override
    {
        ViewAbstract::SetOnPreDrag(std::move(onPreDrag));
    }

    void SetOnDragEnter(NG::OnDragDropFunc&& onDragEnter) override
    {
        ViewAbstract::SetOnDragEnter(std::move(onDragEnter));
    }

    void SetOnDragSpringLoading(NG::OnDragDropSpringLoadingFunc&& onDragSpringLoading) override
    {
        ViewAbstract::SetOnDragSpringLoading(std::move(onDragSpringLoading));
    }

    void SetOnDragSpringLoadingConfiguration(
        const RefPtr<DragSpringLoadingConfiguration>& dragSpringLoadingConfiguration) override
    {
        ViewAbstract::SetOnDragSpringLoadingConfiguration(std::move(dragSpringLoadingConfiguration));
    }

    void SetOnDragEnd(OnNewDragFunc&& onDragEnd) override
    {
        ViewAbstract::SetOnDragEnd(std::move(onDragEnd));
    }

    void SetOnDragLeave(NG::OnDragDropFunc&& onDragLeave) override
    {
        ViewAbstract::SetOnDragLeave(std::move(onDragLeave));
    }

    void SetOnDragMove(NG::OnDragDropFunc&& onDragMove) override
    {
        ViewAbstract::SetOnDragMove(std::move(onDragMove));
    }

    void SetAllowDrop(const std::set<std::string>& allowDrop) override
    {
        ViewAbstract::SetAllowDrop(allowDrop);
    }

    void SetDrawModifier(const RefPtr<NG::DrawModifier>& drawModifier) override
    {
        ViewAbstract::SetDrawModifier(drawModifier);
    }

    void SetDragPreview(const NG::DragDropInfo& info) override
    {
        ViewAbstract::SetDragPreview(info);
    }

    void SetOnVisibleChange(std::function<void(bool, double)>&& onVisibleChange, const std::vector<double>& ratios,
        bool isOutOfBoundsAllowed) override
    {
        ViewAbstract::SetOnVisibleChange(std::move(onVisibleChange), ratios, isOutOfBoundsAllowed);
    }

    void SetOnVisibleAreaApproximateChange(const std::function<void(bool, double)>&& onVisibleChange,
        const std::vector<double>& ratioList, int32_t expectedUpdateInterval) override
    {
        ViewAbstract::SetOnVisibleAreaApproximateChange(std::move(onVisibleChange), ratioList, expectedUpdateInterval);
    }

    void SetOnAreaChanged(
        std::function<void(const Rect& oldRect, const Offset& oldOrigin, const Rect& rect, const Offset& origin)>&&
            onAreaChanged) override
    {
        auto areaChangeCallback = [areaChangeFunc = std::move(onAreaChanged)](const RectF& oldRect,
                                      const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {
            areaChangeFunc(Rect(oldRect.GetX(), oldRect.GetY(), oldRect.Width(), oldRect.Height()),
                Offset(oldOrigin.GetX(), oldOrigin.GetY()), Rect(rect.GetX(), rect.GetY(), rect.Width(), rect.Height()),
                Offset(origin.GetX(), origin.GetY()));
        };
        ViewAbstract::SetOnAreaChanged(std::move(areaChangeCallback));
    }

    void SetOnSizeChanged(
        std::function<void(const RectF& oldRect, const RectF& rect)>&& onSizeChanged) override
    {
        ViewAbstract::SetOnSizeChanged(std::move(onSizeChanged));
    }

    void* GetFrameNode() override
    {
        return ViewAbstract::GetFrameNode();
    }

    void SetOnDrop(NG::OnDragDropFunc&& onDrop) override
    {
        ViewAbstract::SetOnDrop(std::move(onDrop));
    }

    void SetResponseRegion(const std::vector<DimensionRect>& responseRegion) override
    {
        ViewAbstract::SetResponseRegion(responseRegion);
    }

    void SetMouseResponseRegion(const std::vector<DimensionRect>& responseRegion) override
    {
        ViewAbstract::SetMouseResponseRegion(responseRegion);
    }

    void SetEnabled(bool enabled) override
    {
        ViewAbstract::SetEnabled(enabled);
    }

    void SetTouchable(bool touchable) override
    {
        ViewAbstract::SetTouchable(touchable);
    }

    void SetMonopolizeEvents(bool monopolizeEvents) override
    {
        ViewAbstract::SetMonopolizeEvents(monopolizeEvents);
    }

    void SetFocusable(bool focusable) override
    {
        ViewAbstract::SetFocusable(focusable);
    }

    void SetTabStop(bool tabStop) override
    {
        ViewAbstract::SetTabStop(tabStop);
    }

    void SetFocusNode(bool focus) override {}

    void SetTabIndex(int32_t index) override
    {
        ViewAbstract::SetTabIndex(index);
    }

    void SetNextFocus(NG::FocusIntension key, std::string& nextFocus) override
    {
        ViewAbstract::SetNextFocus(key, nextFocus);
    }

    void ResetNextFocus() override
    {
        ViewAbstract::ResetNextFocus();
    }

    void SetFocusOnTouch(bool isSet) override
    {
        ViewAbstract::SetFocusOnTouch(isSet);
    }

    void SetDefaultFocus(bool isSet) override
    {
        ViewAbstract::SetDefaultFocus(isSet);
    }

    void SetGroupDefaultFocus(bool isSet) override
    {
        ViewAbstract::SetGroupDefaultFocus(isSet);
    }

    void SetFocusBoxStyle(const NG::FocusBoxStyle& style) override
    {
        ViewAbstract::SetFocusBoxStyle(style);
    }

    void SetFocusBoxStyleUpdateFunc(
        NG::FocusBoxStyle& style, const RefPtr<ResourceObject>& resObj, const std::string& property) override
    {
        ViewAbstract::SetFocusBoxStyleUpdateFunc(style, resObj, property);
    }

    void SetInspectorId(const std::string& inspectorId) override
    {
        ViewAbstract::SetInspectorId(inspectorId);
    }

    void SetAutoEventParam(const std::string& param) override
    {
        ViewAbstract::SetAutoEventParam(param);
    }

    void SetRestoreId(int32_t restoreId) override
    {
        ViewAbstract::SetRestoreId(restoreId);
    }

    void SetDebugLine(const std::string& line) override
    {
        ViewAbstract::SetDebugLine(line);
    }

    void SetHoverEffect(HoverEffectType hoverEffect) override
    {
        ViewAbstract::SetHoverEffect(hoverEffect);
    }

    void SetHitTestMode(NG::HitTestMode hitTestMode) override
    {
        ViewAbstract::SetHitTestMode(hitTestMode);
    }

    void SetOnTouchTestFunc(NG::OnChildTouchTestFunc&& onChildTouchTest) override
    {
        ViewAbstract::SetOnTouchTestFunc(std::move(onChildTouchTest));
    }
    void SetKeyboardShortcut(const std::string& value, const std::vector<ModifierKey>& keys,
        std::function<void()>&& onKeyboardShortcutAction) override
    {
        ViewAbstract::SetKeyboardShortcut(value, keys, std::move(onKeyboardShortcutAction));
    }

    void SetObscured(const std::vector<ObscuredReasons>& reasons) override
    {
        ViewAbstract::SetObscured(reasons);
    }

    void SetPrivacySensitive(bool flag) override
    {
        ViewAbstract::SetPrivacySensitive(flag);
    }

    void BindPopup(const RefPtr<PopupParam>& param, const RefPtr<AceType>& customNode) override
    {
        auto targetNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        ViewAbstract::BindPopup(param, AceType::Claim(targetNode), AceType::DynamicCast<UINode>(customNode));
    }

    void BindTips(const RefPtr<PopupParam>& param, const RefPtr<OHOS::Ace::SpanString>& spanString) override
    {
        auto targetNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        ViewAbstract::BindTips(param, AceType::Claim(targetNode), spanString);
    }

    int32_t OpenPopup(const RefPtr<PopupParam>& param, const RefPtr<NG::UINode>& customNode) override
    {
        return ViewAbstract::OpenPopup(param, customNode);
    }
    int32_t UpdatePopup(const RefPtr<PopupParam>& param, const RefPtr<UINode>& customNode) override
    {
        return ViewAbstract::UpdatePopup(param, customNode);
    }
    int32_t ClosePopup(const RefPtr<UINode>& customNode) override
    {
        return ViewAbstract::ClosePopup(customNode);
    }

    int32_t GetPopupParam(RefPtr<PopupParam>& param, const RefPtr<NG::UINode>& customNode) override
    {
        return ViewAbstract::GetPopupParam(param, customNode);
    }

    void DismissDialog() override
    {
        ViewAbstract::DismissDialog();
    }

    void DismissPopup() override
    {
        ViewAbstract::DismissPopup();
    }

    void SetToolbarBuilder(std::function<void()>&& buildFunc) override;

    void BindBackground(std::function<void()>&& buildFunc, const Alignment& align) override;
    void SetBackground(std::function<void()>&& buildFunc) override;
    void SetBackgroundAlign(const Alignment& align) override
    {
        NG::ViewAbstract::SetBackgroundAlign(align);
    }
    void SetCustomBackgroundColor(const Color& color) override;
    void SetCustomBackgroundColorWithResourceObj(const Color& color, const RefPtr<ResourceObject>& resObj) override
    {
        NG::ViewAbstract::SetCustomBackgroundColorWithResourceObj(color, resObj);
    }
    void SetBackgroundIgnoresLayoutSafeAreaEdges(const uint32_t edges) override;
    void SetIsTransitionBackground(bool val) override
    {
        NG::ViewAbstract::SetIsTransitionBackground(val);
    }
    void SetIsBuilderBackground(bool val) override
    {
        NG::ViewAbstract::SetIsBuilderBackground(val);
    }

    int32_t OpenMenu(NG::MenuParam& menuParam, const RefPtr<NG::UINode>& customNode, const int32_t& targetId) override
    {
        return ViewAbstract::OpenMenu(menuParam, customNode, targetId);
    }
    int32_t UpdateMenu(const NG::MenuParam& menuParam, const RefPtr<NG::UINode>& customNode) override
    {
        return ViewAbstract::UpdateMenu(menuParam, customNode);
    }
    int32_t CloseMenu(const RefPtr<UINode>& customNode) override
    {
        return ViewAbstract::CloseMenu(customNode);
    }

    void BindMenuGesture(
        std::vector<NG::OptionParam>&& params, std::function<void()>&& buildFunc, const MenuParam& menuParam);

    static void BindMenuTouch(FrameNode* targetNode, const RefPtr<GestureEventHub>& gestrueHub);

    void BindMenu(
        std::vector<NG::OptionParam>&& params, std::function<void()>&& buildFunc, const MenuParam& menuParam) override;

    void BindContextMenu(ResponseType type, std::function<void()>& buildFunc, const MenuParam& menuParam,
        std::function<void()>& previewBuildFunc) override;

    void BindDragWithContextMenuParams(const NG::MenuParam& menuParam) override;

    void BindContentCover(bool isShow, std::function<void(const std::string&)>&& callback,
        std::function<void()>&& buildFunc, NG::ModalStyle& modalStyle, std::function<void()>&& onAppear,
        std::function<void()>&& onDisappear, std::function<void()>&& onWillAppear,
        std::function<void()>&& onWillDisappear, const NG::ContentCoverParam& contentCoverParam) override;

    void BindSheet(bool isShow, std::function<void(const std::string&)>&& callback, std::function<void()>&& buildFunc,
        std::function<void()>&& titleBuildFunc, NG::SheetStyle& sheetStyle, std::function<void()>&& onAppear,
        std::function<void()>&& onDisappear, std::function<void()>&& shouldDismiss,
        std::function<void(const int32_t info)>&& onWillDismiss,
        std::function<void()>&& onWillAppear, std::function<void()>&& onWillDisappear,
        std::function<void(const float)>&& onHeightDidChange,
        std::function<void(const float)>&& onDetentsDidChange,
        std::function<void(const float)>&& onWidthDidChange,
        std::function<void(const float)>&& onTypeDidChange, std::function<void()>&& sheetSpringBack) override;
    RefPtr<PipelineContext> GetSheetContext(NG::SheetStyle& sheetStyle);
    void DismissSheet() override;
    void DismissContentCover() override;
    void SheetSpringBack() override;

    void NotifyDragStartRequest(DragStartRequestStatus dragStatus) override
    {
        ViewAbstract::NotifyDragStartRequest(dragStatus);
    }

    virtual void CreateWithResourceObj(const RefPtr<NG::FrameNode>& frameNode,
        const RefPtr<ResourceObject>& resourceObj, const PopupOptionsType& type) override;
    static std::string PopupTypeStr(const PopupType& type);
    static void UpdateColor(const RefPtr<NG::FrameNode>& frameNode, const PopupType& type, const Color& color);
    static void CreateWithColorResourceObj(
        const RefPtr<NG::FrameNode>& frameNode, const RefPtr<ResourceObject>& ColorResObj, const PopupType& type);
    static void CreateWithBoolResourceObj(
        const RefPtr<NG::FrameNode>& frameNode, const RefPtr<ResourceObject>& maskResObj);
    static std::string PopupOptionTypeStr(const PopupOptionsType& type);
    static void ParseOptionsDimension(const RefPtr<NG::FrameNode>& frameNode,
        const RefPtr<ResourceObject>& dimensionResObj, const PopupOptionsType& type, CalcDimension& dimension);
    static void CreateWithDimensionResourceObj(const RefPtr<NG::FrameNode>& frameNode,
        const RefPtr<ResourceObject>& dimensionResObj, const PopupOptionsType& type);
    virtual void CreateWithResourceObj(const RefPtr<NG::FrameNode>& frameNode,
        const RefPtr<ResourceObject>& resourceObj, const PopupType& type) override;
    virtual void CreateWithResourceObj(
        const RefPtr<NG::FrameNode>& frameNode, const RefPtr<ResourceObject>& resourceObj) override;
    void SetAccessibilityGroup(bool accessible) override;
    void SetAccessibilityText(const std::string& text) override;
    void SetAccessibilityTextHint(const std::string& text) override;
    void SetAccessibilityDescription(const std::string& description) override;
    void SetAccessibilityImportance(const std::string& importance) override;
    void SetAccessibilityVirtualNode(std::function<void()>&& buildFunc) override;
    void SetAccessibilitySelected(bool selected, bool resetValue) override;
    void SetAccessibilityChecked(bool checked, bool resetValue) override;
    void SetAccessibilityRole(const std::string& role, bool resetValue) override;
    void SetOnAccessibilityFocus(NG::OnAccessibilityFocusCallbackImpl&& onAccessibilityFocusCallbackImpl) override;
    void SetOnAccessibilityActionIntercept(
        NG::ActionAccessibilityActionIntercept&& onActionAccessibilityActionIntercept) override;
    void SetOnAccessibilityHoverTransparent(TouchEventFunc&& touchEventFunc) override;
    void SetAccessibilityTextPreferred(bool accessibilityTextPreferred) override;
    void SetAccessibilityNextFocusId(const std::string& nextFocusId) override;
    void ResetOnAccessibilityFocus() override;
    void SetAccessibilityDefaultFocus(bool isFocus) override;
    void SetAccessibilityUseSamePage(const std::string& pageMode) override;
    void SetAccessibilityScrollTriggerable(bool triggerable, bool resetValue) override;
    void SetAccessibilityFocusDrawLevel(int32_t drawLevel) override;
    void RemoveResObj(const std::string& key) override
    {
        ViewAbstract::RemoveResObj(key);
    }
    void SetForegroundColor(const Color& color) override
    {
        ViewAbstract::SetForegroundColor(color);
    }

    void SetForegroundColorStrategy(const ForegroundColorStrategy& strategy) override
    {
        ViewAbstract::SetForegroundColorStrategy(strategy);
    }

    void SetForegroundEffect(float radius) override
    {
        ViewAbstract::SetForegroundEffect(radius);
    }

    void DisableOnClick() override
    {
        ViewAbstract::DisableOnClick();
    }

    void DisableOnTouch() override
    {
        ViewAbstract::DisableOnTouch();
    }

    void DisableOnKeyEvent() override
    {
        ViewAbstract::DisableOnKeyEvent();
    }

#ifdef SUPPORT_DIGITAL_CROWN
    void DisableOnCrownEvent() override
    {
        ViewAbstract::DisableOnCrownEvent();
    }
#endif

    void DisableOnKeyPreIme() override
    {
        auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusHub->ClearOnKeyPreIme();
    }

    void DisableOnKeyEventDispatch() override
    {
        ViewAbstract::DisableOnKeyEventDispatch();
    }

    static void DisableOnKeyPreIme(FrameNode* frameNode)
    {
        auto focusHub = frameNode->GetOrCreateFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusHub->ClearOnKeyPreIme();
    }

    void DisableOnHover() override
    {
        ViewAbstract::DisableOnHover();
    }

    void DisableOnHoverMove() override
    {
        ViewAbstract::DisableOnHoverMove();
    }

    void DisableOnAccessibilityHover() override
    {
        ViewAbstract::DisableOnAccessibilityHover();
    }

    void DisableOnMouse() override
    {
        ViewAbstract::DisableOnMouse();
    }

    void DisableOnAxisEvent() override
    {
        ViewAbstract::DisableOnAxisEvent();
    }

    void DisableOnAppear() override
    {
        ViewAbstract::DisableOnAppear();
    }

    void DisableOnDisAppear() override
    {
        ViewAbstract::DisableOnDisAppear();
    }

    void DisableOnAttach() override
    {
        ViewAbstract::DisableOnAttach();
    }

    void DisableOnDetach() override
    {
        ViewAbstract::DisableOnDetach();
    }

    void DisableOnAreaChange() override
    {
        ViewAbstract::DisableOnAreaChange();
    }

    void DisableOnFocus() override
    {
        ViewAbstract::DisableOnFocus();
    }

    void DisableOnBlur() override
    {
        ViewAbstract::DisableOnBlur();
    }

    void DisableOnFocusAxisEvent() override
    {
        ViewAbstract::DisableOnFocusAxisEvent();
    }

    static void DisableOnFocusAxisEvent(FrameNode* frameNode)
    {
        auto focusHub = frameNode->GetOrCreateFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusHub->ClearOnFocusAxisCallback();
    }

    static void SetAccessibilityText(FrameNode* frameNode, const std::string& text);
    static void SetAccessibilityTextHint(FrameNode* frameNode, const std::string& text);

    void SetLightPosition(
        const CalcDimension& positionX, const CalcDimension& positionY, const CalcDimension& positionZ) override
    {
        ViewAbstract::SetLightPosition(positionX, positionY, positionZ);
    }

    void SetLightPosition(const NG::TranslateOptions& options) override
    {
        ViewAbstract::SetLightPosition(options);
    }
    
    void SetLightIntensity(const float value) override
    {
        ViewAbstract::SetLightIntensity(value);
    }

    void SetLightColor(const Color& value) override
    {
        ViewAbstract::SetLightColor(value);
    }

    void SetLightIlluminated(const uint32_t value) override
    {
        ViewAbstract::SetLightIlluminated(value);
    }

    void SetIlluminatedBorderWidth(const Dimension& value) override
    {
        ViewAbstract::SetIlluminatedBorderWidth(value);
    }

    void SetBloom(const float value) override
    {
        ViewAbstract::SetBloom(value);
    }

    void SetDragEventStrictReportingEnabled(bool dragEventStrictReportingEnabled) override
    {
        ViewAbstract::SetDragEventStrictReportingEnabled(dragEventStrictReportingEnabled);
    }

    void EnableDropDisallowedBadge(bool enableDisallowStatusShowing) override
    {
        ViewAbstract::EnableDropDisallowedBadge(enableDisallowStatusShowing);
    }

    int32_t CancelDataLoading(const std::string& key) override
    {
        return ViewAbstract::CancelDataLoading(key);
    }

    void SetDisableDataPrefetch(bool disableDataPrefetch) override
    {
        return ViewAbstract::SetDisableDataPrefetch(disableDataPrefetch);
    }

    void SetFocusScopeId(const std::string& focusScopeId, bool isGroup, bool arrowKeyStepOut) override
    {
        ViewAbstract::SetFocusScopeId(focusScopeId, isGroup, arrowKeyStepOut);
    }

    void SetFocusScopePriority(const std::string& focusScopeId, const uint32_t focusPriority) override
    {
        ViewAbstract::SetFocusScopePriority(focusScopeId, focusPriority);
    }

    void ResetResObj(const std::string& key) override
    {
        ViewAbstract::ResetResObj(key);
    }

    static void SetAccessibilityGroup(FrameNode* frameNode, bool accessible);
    static void SetUseShadowBatching(FrameNode* frameNode, bool useShadowBatching)
    {
        ViewAbstract::SetUseShadowBatching(frameNode, useShadowBatching);
    }
    static void SetBlendMode(FrameNode* frameNode, BlendMode blendMode)
    {
        ViewAbstract::SetBlendMode(frameNode, blendMode);
    }
    static void SetBlendApplyType(FrameNode* frameNode, BlendApplyType blendApplyType)
    {
        ViewAbstract::SetBlendApplyType(frameNode, blendApplyType);
    }
    static void SetBlender(FrameNode* frameNode, const OHOS::Rosen::Blender* blender)
    {
        ViewAbstract::SetBlender(blender);
    }
    static void SetMonopolizeEvents(FrameNode* frameNode, bool monopolizeEvents)
    {
        ViewAbstract::SetMonopolizeEvents(frameNode, monopolizeEvents);
    }

    static void SetAccessibilityImportance(FrameNode* frameNode, const std::string& importance);
    static void SetAccessibilityDescription(FrameNode* frameNode, const std::string& description);
    static void SetAccessibilitySelected(FrameNode* frameNode, bool selected, bool resetValue);
    static void SetAccessibilityChecked(FrameNode* frameNode, bool checked, bool resetValue);
    static void SetAccessibilityTextPreferred(FrameNode* frameNode, bool accessibilityTextPreferred);
    static void SetAccessibilityRole(FrameNode* frameNode, const std::string& role, bool resetValue);
    static void SetOnAccessibilityFocus(
        FrameNode* frameNode, NG::OnAccessibilityFocusCallbackImpl&& onAccessibilityFocusCallbackImpl);
    static void SetOnAccessibilityActionIntercept(
        FrameNode* frameNode, NG::ActionAccessibilityActionIntercept&& onActionAccessibilityActionIntercept);
    static void SetOnAccessibilityHoverTransparent(FrameNode* frameNode, TouchEventFunc&& touchEventFunc);
    static void ResetOnAccessibilityFocus(FrameNode* frameNode);
    static void SetAccessibilityNextFocusId(FrameNode* frameNode, const std::string& nextFocusId);
    static void SetAccessibilityDefaultFocus(FrameNode* frameNode, bool isFocus);
    static void SetAccessibilityUseSamePage(FrameNode* frameNode, const std::string& pageMode);
    static void SetAccessibilityScrollTriggerable(FrameNode* frameNode, bool triggerable, bool resetValue);
    static void SetAccessibilityFocusDrawLevel(FrameNode* frameNode, int32_t drawLevel);
    static void RegisterRadiusesResObj(
        const std::string& key, NG::BorderRadiusProperty& borderRadius, const RefPtr<ResourceObject>& resObj);
    static void RegisterLocationPropsEdgesResObj(
        const std::string& key, EdgesParam& edges, const RefPtr<ResourceObject>& resObj);
    static void RegisterEdgesWidthResObj(
        const std::string& key, NG::BorderWidthProperty& borderWidth, const RefPtr<ResourceObject>& resObj);
    static void RegisterEdgeMarginsResObj(
        const std::string& key, NG::MarginProperty& margins, const RefPtr<ResourceObject>& resObj);
    static void RegisterLocalizedBorderColor(
        const std::string& key, NG::BorderColorProperty& borderColors, const RefPtr<ResourceObject>& resObj);
    static void SetKeyboardShortcut(FrameNode* frameNode, const std::string& value,
        const std::vector<ModifierKey>& keys, std::function<void()>&& onKeyboardShortcutAction)
    {
        ViewAbstract::SetKeyboardShortcut(frameNode, value, keys, std::move(onKeyboardShortcutAction));
    }

    static void ClearWidthOrHeight(FrameNode* frameNode, bool isWidth)
    {
        ViewAbstract::ClearWidthOrHeight(frameNode, isWidth);
    }

    static bool GetAccessibilityGroup(FrameNode* frameNode);
    static std::string GetAccessibilityText(FrameNode* frameNode);
    static std::string GetAccessibilityDescription(FrameNode* frameNode);
    static std::string GetAccessibilityImportance(FrameNode* frameNode);
    static bool CheckSkipMenuShow(const RefPtr<FrameNode>& targetNode);
    static void SetFreeze(FrameNode* frameNode, bool freeze)
    {
        ViewAbstract::SetFreeze(frameNode, freeze);
    }
    static void SetVisualEffect(FrameNode* frameNode, const OHOS::Rosen::VisualEffect* visualEffect)
    {
        ViewAbstract::SetVisualEffect(frameNode, visualEffect);
    }
    static void SetBackgroundFilter(FrameNode* frameNode, const OHOS::Rosen::Filter* backgroundFilter)
    {
        ViewAbstract::SetBackgroundFilter(frameNode, backgroundFilter);
    }
    static void SetForegroundFilter(FrameNode* frameNode, const OHOS::Rosen::Filter* foregroundFilter)
    {
        ViewAbstract::SetForegroundFilter(frameNode, foregroundFilter);
    }
    static void SetCompositingFilter(FrameNode* frameNode, const OHOS::Rosen::Filter* compositingFilter)
    {
        ViewAbstract::SetCompositingFilter(frameNode, compositingFilter);
    }
    static void RemoveResObj(FrameNode* frameNode, const std::string& key);

private:
    bool CheckMenuIsShow(const MenuParam& menuParam, int32_t targetId, const RefPtr<FrameNode>& targetNode);
    void RegisterContextMenuKeyEvent(
        const RefPtr<FrameNode>& targetNode, std::function<void()>&& buildFunc, const MenuParam& menuParam);

    void CreateAnimatablePropertyFloat(
        const std::string& propertyName, float value, const std::function<void(float)>& onCallbackEvent) override
    {
        ViewAbstract::CreateAnimatablePropertyFloat(propertyName, value, onCallbackEvent);
    }

    void UpdateAnimatablePropertyFloat(const std::string& propertyName, float value) override
    {
        ViewAbstract::UpdateAnimatablePropertyFloat(propertyName, value);
    }

    void CreateAnimatableArithmeticProperty(const std::string& propertyName, RefPtr<CustomAnimatableArithmetic>& value,
        std::function<void(const RefPtr<CustomAnimatableArithmetic>&)>& onCallbackEvent) override
    {
        ViewAbstract::CreateAnimatableArithmeticProperty(propertyName, value, onCallbackEvent);
    }

    void UpdateAnimatableArithmeticProperty(
        const std::string& propertyName, RefPtr<CustomAnimatableArithmetic>& value) override
    {
        ViewAbstract::UpdateAnimatableArithmeticProperty(propertyName, value);
    }

    void UpdateSafeAreaExpandOpts(const SafeAreaExpandOpts& opts) override
    {
        ViewAbstract::UpdateSafeAreaExpandOpts(opts);
    }

    void UpdateIgnoreLayoutSafeAreaOpts(const IgnoreLayoutSafeAreaOpts& opts) override
    {
        ViewAbstract::UpdateIgnoreLayoutSafeAreaOpts(opts);
    }

    void SetPositionLocalizedEdges(bool needLocalized) override
    {
        ViewAbstract::SetPositionLocalizedEdges(needLocalized);
    }

    void SetMarkAnchorStart(Dimension& markAnchorStart) override
    {
        ViewAbstract::SetMarkAnchorStart(markAnchorStart);
    }

    void ResetMarkAnchorStart() override
    {
        ViewAbstract::ResetMarkAnchorStart();
    }

    void SetOffsetLocalizedEdges(bool needLocalized) override
    {
        ViewAbstract::SetOffsetLocalizedEdges(needLocalized);
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_NG_H
