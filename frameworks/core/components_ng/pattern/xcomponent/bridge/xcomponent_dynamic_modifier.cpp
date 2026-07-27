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
#include "core/components_ng/pattern/xcomponent/bridge/xcomponent_dynamic_modifier.h"

#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"
#ifdef XCOMPONENT_SUPPORTED
#ifndef CROSS_PLATFORM
#include "core/components_ng/pattern/xcomponent/bridge/xcomponent_model_impl.h"
#include "frameworks/bridge/declarative_frontend/jsview/models/view_abstract_model_impl.h"
#endif
#endif
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/common/container.h"
#include "core/components/xcomponent/xcomponent_component.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_controller_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern_v2.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_resolution_config.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/native/node/node_xcomponent_modifier.h"
#include "frameworks/core/common/resource/resource_parse_utils.h"
#include "frameworks/core/components_ng/pattern/xcomponent/bridge/arkts_native_xcomponent_bridge.h"

namespace OHOS::Ace::NG {
namespace {
const uint32_t ERROR_UINT_CODE = -1;
thread_local std::string g_strValue;
constexpr int32_t INVALID_HDR_TYPE = -1;
constexpr char XCOMPONENT_ETS_TAG[] = "XComponent";
constexpr int32_t INVERT_SIMPLE_PARAM_SIZE = 1;
constexpr int32_t INVERT_OPTION_PARAM_SIZE = 4;
constexpr int32_t BG_POSITION_PARAM_SIZE = 2;
constexpr double MAX_OPACITY = 1.0;
constexpr int32_t INDEX_HDR_RED = 0;
constexpr int32_t INDEX_HDR_GREEN = 1;
constexpr int32_t INDEX_HDR_BLUE = 2;
constexpr int32_t INDEX_HDR_ALPHA = 3;
constexpr int32_t INDEX_HDR_HEAD_ROOM = 4;
constexpr int32_t INDEX_BG_POS_X = 0;
constexpr int32_t INDEX_BG_POS_Y = 1;
constexpr int32_t INDEX_INVERT_LOW = 0;
constexpr int32_t INDEX_INVERT_HIGH = 1;
constexpr int32_t INDEX_INVERT_THRESHOLD = 2;
constexpr int32_t INDEX_INVERT_THRESHOLD_RANGE = 3;
constexpr int32_t INDEX_STRETCH_LEFT = 0;
constexpr int32_t INDEX_STRETCH_TOP = 1;
constexpr int32_t INDEX_STRETCH_RIGHT = 2;
constexpr int32_t INDEX_STRETCH_BOTTOM = 3;
constexpr int32_t STRETCH_PARAM_SIZE = 4;

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

#ifdef XCOMPONENT_SUPPORTED
#ifndef CROSS_PLATFORM
Framework::XComponentModelImpl* GetModelImpl()
{
    static Framework::XComponentModelImpl impl;
    return &impl;
}

Framework::ViewAbstractModelImpl* GetViewAbstractModelImpl()
{
    static Framework::ViewAbstractModelImpl instance;
    return &instance;
}

void SetXComponentEnableAnalyzerImpl(ArkUINodeHandle /*node*/, ArkUI_Bool enable)
{
    GetModelImpl()->EnableAnalyzer(enable);
}

void ResetXComponentEnableAnalyzerImpl(ArkUINodeHandle /*node*/)
{
    GetModelImpl()->EnableAnalyzer(false);
}

void SetXComponentBackgroundColorImpl(ArkUINodeHandle /*node*/, uint32_t color, ArkUI_Bool /*isJsView*/)
{
    auto type = GetModelImpl()->GetType();
    if (!XComponentModel::IsBackGroundColorAvailable(type)) {
        return;
    }
    GetViewAbstractModelImpl()->SetBackgroundColor(Color(color));
}

void SetXComponentBackgroundColorWithColorSpaceImpl(
    ArkUINodeHandle /*node*/, uint32_t color, ArkUI_Int32 colorSpace, ArkUI_Bool /*isJsView*/)
{
    auto type = GetModelImpl()->GetType();
    if (!XComponentModel::IsBackGroundColorAvailable(type)) {
        return;
    }
    Color backgroundColor { color };
    if (ColorSpace::DISPLAY_P3 == colorSpace) {
        backgroundColor.SetColorSpace(ColorSpace::DISPLAY_P3);
    } else {
        backgroundColor.SetColorSpace(ColorSpace::SRGB);
    }
    GetViewAbstractModelImpl()->SetBackgroundColor(backgroundColor);
}

void SetXComponentBackgroundColorForHDRImpl(ArkUINodeHandle /*node*/, ArkUI_Int32 colorSpace,
    const ArkUI_Float32* hdrValues, void* bgColorRawPtr, ArkUI_Bool /*isJsView*/)
{
    auto type = GetModelImpl()->GetType();
    if (!XComponentModel::IsBackGroundColorAvailable(type)) {
        return;
    }
    CHECK_NULL_VOID(hdrValues);
    Color backgroundColor = Color::FromFloat(hdrValues[INDEX_HDR_RED], hdrValues[INDEX_HDR_GREEN],
        hdrValues[INDEX_HDR_BLUE], hdrValues[INDEX_HDR_ALPHA], hdrValues[INDEX_HDR_HEAD_ROOM]);
    if (ColorSpace::DISPLAY_P3 == colorSpace) {
        backgroundColor.SetColorSpace(ColorSpace::DISPLAY_P3);
    } else if (ColorSpace::BT2020 == colorSpace) {
        backgroundColor.SetColorSpace(ColorSpace::BT2020);
    } else {
        backgroundColor.SetColorSpace(ColorSpace::SRGB);
    }
    if (!SystemProperties::ConfigChangePerform() || !bgColorRawPtr) {
        GetViewAbstractModelImpl()->SetBackgroundColor(backgroundColor);
    } else {
        auto* bgColor = reinterpret_cast<ResourceObject*>(bgColorRawPtr);
        auto backgroundColorResObj = AceType::Claim(bgColor);
        GetViewAbstractModelImpl()->SetBackgroundColor(backgroundColor);
        // Note: Resource object is handled via SetBackgroundColor, no separate resource API for Impl
    }
}

void ResetXComponentBackgroundColorImpl(ArkUINodeHandle /*node*/, ArkUI_Bool /*isJsView*/)
{
    auto type = GetModelImpl()->GetType();
    if (!XComponentModel::IsBackGroundColorAvailable(type)) {
        return;
    }
    GetViewAbstractModelImpl()->SetBackgroundColor(
        (type == XComponentType::SURFACE) ? Color::BLACK : Color::TRANSPARENT);
}

void SetXComponentBackgroundImageImpl(ArkUINodeHandle /*node*/, ArkUI_CharPtr src, ArkUI_CharPtr bundle,
    ArkUI_CharPtr module, void* bgImageRawPtr, void* theme)
{
    std::string srcStr(src);
    std::string bundleStr(bundle);
    std::string moduleStr(module);
    auto* themeRaw = reinterpret_cast<OHOS::Ace::ThemeConstants*>(theme);
    auto themeConstant = AceType::Claim(themeRaw);
    GetViewAbstractModelImpl()->SetBackgroundImage(ImageSourceInfo { srcStr, bundleStr, moduleStr }, themeConstant);
}

void SetBackgroundImageSyncModeImpl(ArkUINodeHandle node, ArkUI_Bool syncMode) {}

void SetBackgroundImagePixelMapByPixelMapPtrImpl(ArkUINodeHandle node, void* pixelMapPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<PixelMap> pixelmap = PixelMap::CreatePixelMap(pixelMapPtr);
    GetViewAbstractModelImpl()->SetBackgroundImage(OHOS::Ace::ImageSourceInfo { pixelmap }, nullptr);
}

void SetBackgroundImageRepeatImpl(ArkUINodeHandle /*node*/, ArkUI_Int32 repeatIndex)
{
    auto repeat = static_cast<ImageRepeat>(repeatIndex);
    GetViewAbstractModelImpl()->SetBackgroundImageRepeat(repeat);
}

void SetBackgroundImageSizeImpl(ArkUINodeHandle /*node*/, ArkUI_Float32 valueWidth, ArkUI_Float32 valueHeight,
    ArkUI_Int32 typeWidth, ArkUI_Int32 typeHeight, void* /*bgImageSizeWidthRawPtr*/, void* /*bgImageSizeHeightRawPtr*/)
{
    BackgroundImageSize bgImgSize;
    bgImgSize.SetSizeTypeX(static_cast<OHOS::Ace::BackgroundImageSizeType>(typeWidth));
    bgImgSize.SetSizeValueX(valueWidth);
    bgImgSize.SetSizeTypeY(static_cast<OHOS::Ace::BackgroundImageSizeType>(typeHeight));
    bgImgSize.SetSizeValueY(valueHeight);
    GetViewAbstractModelImpl()->SetBackgroundImageSize(bgImgSize);
}

void ResetBackgroundImageSizeImpl(ArkUINodeHandle /*node*/)
{
    BackgroundImageSize bgImgSize;
    bgImgSize.SetSizeTypeX(BackgroundImageSizeType::AUTO);
    bgImgSize.SetSizeTypeY(BackgroundImageSizeType::AUTO);
    GetViewAbstractModelImpl()->SetBackgroundImageSize(bgImgSize);
}

void SetBackgroundImagePositionImpl(ArkUINodeHandle /*node*/, const ArkUI_Float32* values, const ArkUI_Int32* types,
    ArkUI_Bool isAlign, ArkUI_Int32 size, void* /*bgImageXRawPtr*/, void* /*bgImageYRawPtr*/)
{
    BackgroundImagePosition bgImgPosition;
    if (size >= BG_POSITION_PARAM_SIZE) {
        DimensionUnit typeX = static_cast<OHOS::Ace::DimensionUnit>(types[INDEX_BG_POS_X]);
        DimensionUnit typeY = static_cast<OHOS::Ace::DimensionUnit>(types[INDEX_BG_POS_Y]);
        bgImgPosition.SetSizeX(AnimatableDimension(values[INDEX_BG_POS_X], typeX));
        bgImgPosition.SetSizeY(AnimatableDimension(values[INDEX_BG_POS_Y], typeY));
    }
    bgImgPosition.SetIsAlign(isAlign);
    GetViewAbstractModelImpl()->SetBackgroundImagePosition(bgImgPosition);
}

void ResetBackgroundImagePositionImpl(ArkUINodeHandle /*node*/)
{
    BackgroundImagePosition bgImgPosition;
    bgImgPosition.SetSizeX(AnimatableDimension(0.0, DimensionUnit::PX));
    bgImgPosition.SetSizeY(AnimatableDimension(0.0, DimensionUnit::PX));
    GetViewAbstractModelImpl()->SetBackgroundImagePosition(bgImgPosition);
}

void SetBlurImpl(ArkUINodeHandle /*node*/, ArkUI_Float32 value, const ArkUI_Float32* blurValues,
    ArkUI_Int32 blurValuesSize, ArkUI_Bool disableSystemAdaptation)
{
    ArkUI_Float32 blur = 0.0f;
    BlurOption blurOption;
    blurOption.grayscale.assign(blurValues, blurValues + blurValuesSize);
    if (value > 0) {
        blur = value;
    }
    CalcDimension dimensionBlur(blur, DimensionUnit::PX);
    SysOptions sysOptions;
    sysOptions.disableSystemAdaptation = disableSystemAdaptation;
    GetViewAbstractModelImpl()->SetFrontBlur(dimensionBlur, blurOption, sysOptions);
}

void ResetBlurImpl(ArkUINodeHandle /*node*/)
{
    CalcDimension dimensionBlur(0.0, DimensionUnit::PX);
    BlurOption blurOption;
    SysOptions sysOptions;
    GetViewAbstractModelImpl()->SetFrontBlur(dimensionBlur, blurOption, sysOptions);
}

void SetBackdropBlurImpl(ArkUINodeHandle /*node*/, ArkUI_Float32 value, const ArkUI_Float32* blurValues,
    ArkUI_Int32 blurValuesSize, ArkUI_Bool disableSystemAdaptation)
{
    ArkUI_Float32 blur = 0.0f;
    BlurOption blurOption;
    blurOption.grayscale.assign(blurValues, blurValues + blurValuesSize);
    if (value > 0) {
        blur = value;
    }
    CalcDimension dimensionBlur(blur, DimensionUnit::PX);
    SysOptions sysOptions;
    sysOptions.disableSystemAdaptation = disableSystemAdaptation;
    GetViewAbstractModelImpl()->SetBackdropBlur(dimensionBlur, blurOption, sysOptions);
}

void ResetBackdropBlurImpl(ArkUINodeHandle /*node*/)
{
    CalcDimension dimensionBlur(0.0, DimensionUnit::PX);
    BlurOption blurOption;
    SysOptions sysOptions;
    GetViewAbstractModelImpl()->SetBackdropBlur(dimensionBlur, blurOption, sysOptions);
}

void SetBrightnessImpl(ArkUINodeHandle /*node*/, ArkUI_Float64 brightness, ArkUI_Int32 unit)
{
    CalcDimension value = CalcDimension(brightness, static_cast<DimensionUnit>(unit));
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    GetViewAbstractModelImpl()->SetBrightness(value);
}

void ResetBrightnessImpl(ArkUINodeHandle /*node*/)
{
    CalcDimension value(1.0, DimensionUnit::VP);
    GetViewAbstractModelImpl()->SetBrightness(value);
}

void SetSaturateImpl(ArkUINodeHandle /*node*/, ArkUI_Float32 saturate, ArkUI_Int32 unit)
{
    CalcDimension value = CalcDimension(saturate, static_cast<DimensionUnit>(unit));
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    GetViewAbstractModelImpl()->SetSaturate(value);
}

void ResetSaturateImpl(ArkUINodeHandle /*node*/)
{
    CalcDimension value(1.0, DimensionUnit::VP);
    GetViewAbstractModelImpl()->SetSaturate(value);
}

void SetContrastImpl(ArkUINodeHandle /*node*/, ArkUI_Float64 contrast, ArkUI_Int32 unit)
{
    CalcDimension value = CalcDimension(contrast, static_cast<DimensionUnit>(unit));
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    GetViewAbstractModelImpl()->SetContrast(value);
}

void ResetContrastImpl(ArkUINodeHandle /*node*/)
{
    CalcDimension value(1.0, DimensionUnit::VP);
    GetViewAbstractModelImpl()->SetContrast(value);
}

void SetInvertImpl(ArkUINodeHandle /*node*/, ArkUI_Float32* invert, ArkUI_Int32 length)
{
    InvertVariant invertVariant;
    if (length == INVERT_OPTION_PARAM_SIZE) {
        InvertOption option;
        option.low_ = invert[INDEX_INVERT_LOW];
        option.high_ = invert[INDEX_INVERT_HIGH];
        option.threshold_ = invert[INDEX_INVERT_THRESHOLD];
        option.thresholdRange_ = invert[INDEX_INVERT_THRESHOLD_RANGE];
        invertVariant = option;
    } else if (length == INVERT_SIMPLE_PARAM_SIZE) {
        invertVariant = std::clamp(static_cast<float>(invert[INDEX_INVERT_LOW]), 0.0f, 1.0f);
    }
    GetViewAbstractModelImpl()->SetInvert(invertVariant);
}

void ResetInvertImpl(ArkUINodeHandle /*node*/)
{
    InvertVariant invert = 0.0f;
    GetViewAbstractModelImpl()->SetInvert(invert);
}

void SetSepiaImpl(ArkUINodeHandle /*node*/, ArkUI_Float32 sepia)
{
    CalcDimension value = CalcDimension(sepia, DimensionUnit::VP);
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    GetViewAbstractModelImpl()->SetSepia(value);
}

void ResetSepiaImpl(ArkUINodeHandle /*node*/)
{
    CalcDimension value(0.0, DimensionUnit::VP);
    GetViewAbstractModelImpl()->SetSepia(value);
}

void SetHueRotateImpl(ArkUINodeHandle /*node*/, ArkUI_Float32 deg)
{
    GetViewAbstractModelImpl()->SetHueRotate(deg);
}

void ResetHueRotateImpl(ArkUINodeHandle /*node*/)
{
    GetViewAbstractModelImpl()->SetHueRotate(0.0);
}

void SetSphericalEffectImpl(ArkUINodeHandle /*node*/, ArkUI_Float64 radio)
{
    GetViewAbstractModelImpl()->SetSphericalEffect(std::clamp(radio, 0.0, 1.0));
}

void ResetSphericalEffectImpl(ArkUINodeHandle /*node*/)
{
    GetViewAbstractModelImpl()->SetSphericalEffect(0.0);
}

void SetLightUpEffectImpl(ArkUINodeHandle /*node*/, ArkUI_Float32 radio)
{
    GetViewAbstractModelImpl()->SetLightUpEffect(std::clamp(radio, 0.0f, 1.0f));
}

void ResetLightUpEffectImpl(ArkUINodeHandle /*node*/)
{
    GetViewAbstractModelImpl()->SetLightUpEffect(1.0);
}

void SetColorBlendImpl(ArkUINodeHandle /*node*/, uint32_t color, void* /*colorBlendRawPtr*/)
{
    auto finalColor = Color(color);
    GetViewAbstractModelImpl()->SetColorBlend(finalColor);
}

void ResetColorBlendImpl(ArkUINodeHandle /*node*/)
{
    GetViewAbstractModelImpl()->SetColorBlend(Color::TRANSPARENT);
}

void SetPixelStretchEffectImpl(ArkUINodeHandle /*node*/, const ArkUI_Float32* values, const ArkUI_Int32* units,
    ArkUI_Int32 length, void* /*rawPtr*/)
{
    if (length != STRETCH_PARAM_SIZE) {
        return;
    }
    Dimension left(values[INDEX_STRETCH_LEFT], static_cast<DimensionUnit>(units[INDEX_STRETCH_LEFT]));
    Dimension top(values[INDEX_STRETCH_TOP], static_cast<DimensionUnit>(units[INDEX_STRETCH_TOP]));
    Dimension right(values[INDEX_STRETCH_RIGHT], static_cast<DimensionUnit>(units[INDEX_STRETCH_RIGHT]));
    Dimension bottom(values[INDEX_STRETCH_BOTTOM], static_cast<DimensionUnit>(units[INDEX_STRETCH_BOTTOM]));
    bool illegalInput = false;
    if (left.Unit() == DimensionUnit::PERCENT || right.Unit() == DimensionUnit::PERCENT ||
        top.Unit() == DimensionUnit::PERCENT || bottom.Unit() == DimensionUnit::PERCENT) {
        if ((NearEqual(left.Value(), 0.0) || left.Unit() == DimensionUnit::PERCENT) &&
            (NearEqual(top.Value(), 0.0) || top.Unit() == DimensionUnit::PERCENT) &&
            (NearEqual(right.Value(), 0.0) || right.Unit() == DimensionUnit::PERCENT) &&
            (NearEqual(bottom.Value(), 0.0) || bottom.Unit() == DimensionUnit::PERCENT)) {
            left.SetUnit(DimensionUnit::PERCENT);
            top.SetUnit(DimensionUnit::PERCENT);
            right.SetUnit(DimensionUnit::PERCENT);
            bottom.SetUnit(DimensionUnit::PERCENT);
        } else {
            illegalInput = true;
        }
    }
    PixStretchEffectOption option;
    if ((left.IsNonNegative() && top.IsNonNegative() && right.IsNonNegative() && bottom.IsNonNegative()) ||
        (left.IsNonPositive() && top.IsNonPositive() && right.IsNonPositive() && bottom.IsNonPositive())) {
        option.left = left;
        option.top = top;
        option.right = right;
        option.bottom = bottom;
    } else {
        illegalInput = true;
    }
    if (illegalInput) {
        option.ResetValue();
    }
    GetViewAbstractModelImpl()->SetPixelStretchEffect(option);
}

void ResetPixelStretchEffectImpl(ArkUINodeHandle /*node*/)
{
    PixStretchEffectOption option;
    option.ResetValue();
    GetViewAbstractModelImpl()->SetPixelStretchEffect(option);
}

void SetLinearGradientBlurImpl(ArkUINodeHandle /*node*/, void* /*blurPara*/) {}

void ResetLinearGradientBlurImpl(ArkUINodeHandle /*node*/) {}

void DisableOnAttachImpl(ArkUINodeHandle /*node*/) {}

void DisableOnDetachImpl(ArkUINodeHandle /*node*/) {}

void DisableOnClickImpl(ArkUINodeHandle /*node*/) {}

void DisableOnTouchImpl(ArkUINodeHandle /*node*/) {}

void DisableOnKeyEventImpl(ArkUINodeHandle /*node*/) {}

void DisableOnMouseImpl(ArkUINodeHandle /*node*/) {}

void DisableOnHoverImpl(ArkUINodeHandle /*node*/) {}

void DisableOnFocusImpl(ArkUINodeHandle /*node*/) {}

void DisableOnBlurImpl(ArkUINodeHandle /*node*/) {}

void SetXComponentOpacityImpl(ArkUINodeHandle /*node*/, ArkUI_Float32 opacity)
{
    auto type = GetModelImpl()->GetType();
    if (type == XComponentType::SURFACE || type == XComponentType::COMPONENT) {
        return;
    }
    if ((LessNotEqual(opacity, 0.0)) || opacity > MAX_OPACITY) {
        opacity = static_cast<ArkUI_Float32>(MAX_OPACITY);
    }
    GetViewAbstractModelImpl()->SetOpacity(opacity);
}

void ResetXComponentOpacityImpl(ArkUINodeHandle /*node*/)
{
    auto type = GetModelImpl()->GetType();
    if (type == XComponentType::SURFACE || type == XComponentType::COMPONENT) {
        return;
    }
    GetViewAbstractModelImpl()->SetOpacity(static_cast<ArkUI_Float32>(MAX_OPACITY));
}

void SetXComponentEnableSecureImpl(ArkUINodeHandle /*node*/, ArkUI_Bool enable)
{
    GetModelImpl()->EnableSecure(enable);
}

void ResetXComponentEnableSecureImpl(ArkUINodeHandle /*node*/)
{
    GetModelImpl()->EnableSecure(false);
}

void SetXComponentHdrBrightnessImpl(ArkUINodeHandle /*node*/, ArkUI_Float32 hdrBrightness, ArkUI_Int32 hdrtype)
{
    GetModelImpl()->HdrBrightness(hdrBrightness, static_cast<OHOS::Ace::HdrType>(hdrtype));
}

void ResetXComponentHdrBrightnessImpl(ArkUINodeHandle /*node*/)
{
    GetModelImpl()->HdrBrightness(1.0f);
}

void SetXComponentEnableTransparentLayerImpl(ArkUINodeHandle /*node*/, ArkUI_Bool enable)
{
    GetModelImpl()->EnableTransparentLayer(enable);
}

void ResetXComponentEnableTransparentLayerImpl(ArkUINodeHandle /*node*/)
{
    GetModelImpl()->EnableTransparentLayer(false);
}

void SetXComponentRenderFitImpl(ArkUINodeHandle /*node*/, ArkUI_Int32 renderFitNumber)
{
    auto renderFit = RenderFit::RESIZE_FILL;
    if (renderFitNumber >= static_cast<int32_t>(RenderFit::CENTER) &&
        renderFitNumber <= static_cast<int32_t>(RenderFit::RESIZE_COVER_BOTTOM_RIGHT)) {
        renderFit = static_cast<RenderFit>(renderFitNumber);
    }
    auto type = GetModelImpl()->GetType();
    if (type == XComponentType::COMPONENT || type == XComponentType::NODE) {
        return;
    }
    if (type == XComponentType::TEXTURE) {
        GetViewAbstractModelImpl()->SetRenderFit(renderFit);
        return;
    }
    GetModelImpl()->SetRenderFit(renderFit);
}

void ResetXComponentRenderFitImpl(ArkUINodeHandle /*node*/)
{
    auto type = GetModelImpl()->GetType();
    if (type == XComponentType::COMPONENT || type == XComponentType::NODE) {
        return;
    }
    if (type == XComponentType::TEXTURE) {
        GetViewAbstractModelImpl()->SetRenderFit(RenderFit::RESIZE_FILL);
        return;
    }
    GetModelImpl()->SetRenderFit(RenderFit::RESIZE_FILL);
}

void SetXComponentOnLoadImpl(ArkUINodeHandle /*node*/, void* callback)
{
    if (callback) {
        auto onLoad = reinterpret_cast<LoadEvent*>(callback);
        GetModelImpl()->SetOnLoad(std::move(*onLoad));
    }
}

void SetXComponentOnDestroyImpl(ArkUINodeHandle /*node*/, void* callback)
{
    if (callback) {
        auto onDestroy = reinterpret_cast<DestroyEvent*>(callback);
        GetModelImpl()->SetOnDestroy(std::move(*onDestroy));
    }
}

void SetXComponentControllerOnCreatedImpl(ArkUINodeHandle /*node*/, void* callback)
{
    if (callback) {
        auto onCreated = reinterpret_cast<std::function<void(const std::string&, const std::string&)>*>(callback);
        GetModelImpl()->SetControllerOnCreated(std::move(*onCreated));
    }
}

void SetXComponentControllerOnChangedImpl(ArkUINodeHandle /*node*/, void* callback)
{
    if (callback) {
        auto onChanged = reinterpret_cast<std::function<void(const std::string&, const NG::RectF&)>*>(callback);
        GetModelImpl()->SetControllerOnChanged(std::move(*onChanged));
    }
}

void SetXComponentControllerOnDestroyedImpl(ArkUINodeHandle /*node*/, void* callback)
{
    if (callback) {
        auto onDestroyed = reinterpret_cast<std::function<void(const std::string&, const std::string&)>*>(callback);
        GetModelImpl()->SetControllerOnDestroyed(std::move(*onDestroyed));
    }
}

void SetXComponentSoPathImpl(ArkUI_CharPtr soPath)
{
    if (soPath) {
        GetModelImpl()->SetSoPath(std::string(soPath));
    }
}

ArkUI_Bool IsCommonEventAvailableImpl(ArkUINodeHandle /*node*/)
{
    auto type = GetModelImpl()->GetType();
    auto libraryName = GetModelImpl()->GetLibraryName();
    return static_cast<ArkUI_Bool>(XComponentModel::IsCommonEventAvailable(type, libraryName));
}

void SetXComponentScreenIdImpl(ArkUI_Uint64 screenId)
{
    GetModelImpl()->SetScreenId(screenId);
}

void SetXComponentBlendModeImpl(ArkUINodeHandle /*node*/, ArkUI_Int32 blendMode, ArkUI_Int32 blendApplyTypeValue)
{
    GetViewAbstractModelImpl()->SetBlendMode(static_cast<BlendMode>(blendMode));
    GetViewAbstractModelImpl()->SetBlendApplyType(static_cast<BlendApplyType>(blendApplyTypeValue));
}

void ResetXComponentBlendModeImpl(ArkUINodeHandle node)
{
    GetViewAbstractModelImpl()->SetBlendMode(BlendMode::NONE);
}

void SetXComponentBlendApplyTypeImpl(ArkUINodeHandle /*node*/, ArkUI_Int32 blendApplyTypeValue)
{
    GetViewAbstractModelImpl()->SetBlendApplyType(static_cast<BlendApplyType>(blendApplyTypeValue));
}

void CreateWithOpacityResourceObjImpl(ArkUINodeHandle node, void* opacityResObj) {}
#endif
#endif

void SetXComponentEnableAnalyzer(ArkUINodeHandle node, ArkUI_Bool enable)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::EnableAnalyzer(frameNode, enable);
}

void ResetXComponentEnableAnalyzer(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::EnableAnalyzer(frameNode, false);
}

void SetXComponentBackgroundColor(ArkUINodeHandle node, uint32_t color, ArkUI_Bool isJsView = false)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto type = XComponentModelNG::GetType(frameNode);
    if (!XComponentModel::IsBackGroundColorAvailable(type)) {
        return;
    }
    if (isJsView) {
        ViewAbstract::SetBackgroundColor(Color(color));
    } else {
        ViewAbstract::SetBackgroundColor(frameNode, Color(color));
    }
}

void SetXComponentBackgroundColorWithColorSpace(
    ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_Int32 colorSpace, ArkUI_Bool isJsView = false)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto type = XComponentModelNG::GetType(frameNode);
    if (!XComponentModel::IsBackGroundColorAvailable(type)) {
        return;
    }
    Color backgroundColor { color };
    if (ColorSpace::DISPLAY_P3 == colorSpace) {
        backgroundColor.SetColorSpace(ColorSpace::DISPLAY_P3);
    } else {
        backgroundColor.SetColorSpace(ColorSpace::SRGB);
    }
    if (isJsView) {
        ViewAbstract::SetBackgroundColor(backgroundColor);
    } else {
        ViewAbstract::SetBackgroundColor(frameNode, backgroundColor);
    }
}

void SetXComponentBackgroundColorForHDR(ArkUINodeHandle node, ArkUI_Int32 colorSpace, const ArkUI_Float32* hdrValues,
    void* bgColorRawPtr, ArkUI_Bool isJsView = false)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto type = XComponentModelNG::GetType(frameNode);
    if (!XComponentModel::IsBackGroundColorAvailable(type)) {
        return;
    }
    CHECK_NULL_VOID(hdrValues);
    Color backgroundColor = Color::FromFloat(hdrValues[INDEX_HDR_RED], hdrValues[INDEX_HDR_GREEN],
        hdrValues[INDEX_HDR_BLUE], hdrValues[INDEX_HDR_ALPHA], hdrValues[INDEX_HDR_HEAD_ROOM]);
    if (ColorSpace::DISPLAY_P3 == colorSpace) {
        backgroundColor.SetColorSpace(ColorSpace::DISPLAY_P3);
    } else if (ColorSpace::BT2020 == colorSpace) {
        backgroundColor.SetColorSpace(ColorSpace::BT2020);
    } else {
        backgroundColor.SetColorSpace(ColorSpace::SRGB);
    }
    if (!SystemProperties::ConfigChangePerform() || !bgColorRawPtr) {
        if (isJsView) {
            ViewAbstract::SetBackgroundColor(backgroundColor);
        } else {
            ViewAbstract::SetBackgroundColor(frameNode, backgroundColor);
        }
    } else {
        auto* bgColor = reinterpret_cast<ResourceObject*>(bgColorRawPtr);
        auto backgroundColorResObj = AceType::Claim(bgColor);
        ViewAbstract::SetBackgroundColor(frameNode, backgroundColor, backgroundColorResObj);
    }
}

void ResetXComponentBackgroundColor(ArkUINodeHandle node, ArkUI_Bool isJsView = false)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto type = XComponentModelNG::GetType(frameNode);
    if (!XComponentModel::IsBackGroundColorAvailable(type)) {
        return;
    }
    auto color = (type == XComponentType::SURFACE) ? Color::BLACK : Color::TRANSPARENT;
    if (isJsView) {
        ViewAbstract::SetBackgroundColor(color);
    } else {
        ViewAbstract::SetBackgroundColor(frameNode, color);
    }
}

void SetBackgroundImage(ArkUINodeHandle node, ArkUI_CharPtr src, ArkUI_CharPtr bundle, ArkUI_CharPtr module,
    void* bgImageRawPtr, void* theme)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string srcStr(src);
    std::string bundleStr(bundle);
    std::string moduleStr(module);
    if (!SystemProperties::ConfigChangePerform() || !bgImageRawPtr) {
        ViewAbstract::SetBackgroundImage(frameNode, OHOS::Ace::ImageSourceInfo { srcStr, bundleStr, moduleStr });
    } else {
        auto* bgImage = reinterpret_cast<ResourceObject*>(bgImageRawPtr);
        auto backgroundImageResObj = AceType::Claim(bgImage);
        ViewAbstract::SetBackgroundImage(
            frameNode, OHOS::Ace::ImageSourceInfo { srcStr, bundleStr, moduleStr }, backgroundImageResObj);
    }
}

void SetBackgroundImageSyncMode(ArkUINodeHandle node, ArkUI_Bool syncMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetBackgroundImageSyncMode(frameNode, syncMode);
}

void SetBackgroundImagePixelMapByPixelMapPtr(ArkUINodeHandle node, void* pixelMapPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<PixelMap> pixelmap = PixelMap::CreatePixelMap(pixelMapPtr);
    ViewAbstract::SetBackgroundImage(frameNode, OHOS::Ace::ImageSourceInfo { pixelmap });
}

void SetBackgroundImageRepeat(ArkUINodeHandle node, ArkUI_Int32 repeatIndex)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto repeat = static_cast<ImageRepeat>(repeatIndex);
    if (repeat >= OHOS::Ace::ImageRepeat::NO_REPEAT && repeat <= OHOS::Ace::ImageRepeat::REPEAT) {
        ViewAbstract::SetBackgroundImageRepeat(frameNode, repeat);
    } else {
        ViewAbstract::SetBackgroundImageRepeat(frameNode, OHOS::Ace::ImageRepeat::NO_REPEAT);
    }
}

void ClearResObj(ArkUINodeHandle node, ArkUI_CharPtr resObjName)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    std::string resObjNameStr(resObjName);
    ViewAbstract::ClearResObj(frameNode, resObjNameStr);
}

void SetBackgroundImageSize(ArkUINodeHandle node, ArkUI_Float32 valueWidth, ArkUI_Float32 valueHeight,
    ArkUI_Int32 typeWidth, ArkUI_Int32 typeHeight, void* bgImageSizeWidthRawPtr, void* bgImageSizeHeightRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BackgroundImageSize bgImgSize;
    bgImgSize.SetSizeTypeX(static_cast<OHOS::Ace::BackgroundImageSizeType>(typeWidth));
    bgImgSize.SetSizeValueX(valueWidth);
    bgImgSize.SetSizeTypeY(static_cast<OHOS::Ace::BackgroundImageSizeType>(typeHeight));
    bgImgSize.SetSizeValueY(valueHeight);
    if (bgImageSizeWidthRawPtr) {
        auto* resObj = reinterpret_cast<ResourceObject*>(bgImageSizeWidthRawPtr);
        ViewAbstract::SetBackgroundImageSizeUpdateFunc(bgImgSize, AceType::Claim(resObj), "width");
    }
    if (bgImageSizeHeightRawPtr) {
        auto* resObj = reinterpret_cast<ResourceObject*>(bgImageSizeHeightRawPtr);
        ViewAbstract::SetBackgroundImageSizeUpdateFunc(bgImgSize, AceType::Claim(resObj), "height");
    }
    ViewAbstract::SetBackgroundImageSize(frameNode, bgImgSize);
}

void ResetBackgroundImageSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BackgroundImageSize bgImgSize;
    bgImgSize.SetSizeTypeX(BackgroundImageSizeType::AUTO);
    bgImgSize.SetSizeTypeY(BackgroundImageSizeType::AUTO);
    ViewAbstract::SetBackgroundImageSize(frameNode, bgImgSize);
}

void SetBackgroundImagePosition(ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* types,
    ArkUI_Bool isAlign, ArkUI_Int32 size, void* bgImageXRawPtr, void* bgImageYRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BackgroundImagePosition bgImgPosition;
    if (bgImageXRawPtr) {
        auto* resObj = reinterpret_cast<ResourceObject*>(bgImageXRawPtr);
        bgImgPosition.AddResource("backgroundImagePositionX", AceType::Claim(resObj),
            [](const RefPtr<ResourceObject>& resObj, BackgroundImagePosition& position) {
                CalcDimension dimension;
                ResourceParseUtils::ParseResDimensionVp(resObj, dimension);
                position.SetSizeX(AnimatableDimension(dimension.Value(), DimensionUnit::PX));
            });
    }
    if (bgImageYRawPtr) {
        auto* resObj = reinterpret_cast<ResourceObject*>(bgImageYRawPtr);
        bgImgPosition.AddResource("backgroundImagePositionY", AceType::Claim(resObj),
            [](const RefPtr<ResourceObject>& resObj, BackgroundImagePosition& position) {
                CalcDimension dimension;
                ResourceParseUtils::ParseResDimensionVp(resObj, dimension);
                position.SetSizeY(AnimatableDimension(dimension.Value(), DimensionUnit::PX));
            });
    }
    if (size >= BG_POSITION_PARAM_SIZE) {
        DimensionUnit typeX = static_cast<OHOS::Ace::DimensionUnit>(types[INDEX_BG_POS_X]);
        DimensionUnit typeY = static_cast<OHOS::Ace::DimensionUnit>(types[INDEX_BG_POS_Y]);
        bgImgPosition.SetSizeX(AnimatableDimension(values[INDEX_BG_POS_X], typeX));
        bgImgPosition.SetSizeY(AnimatableDimension(values[INDEX_BG_POS_Y], typeY));
    }
    bgImgPosition.SetIsAlign(isAlign);
    ViewAbstract::SetBackgroundImagePosition(frameNode, bgImgPosition);
}

void ResetBackgroundImagePosition(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BackgroundImagePosition bgImgPosition;
    bgImgPosition.SetSizeX(AnimatableDimension(0.0, DimensionUnit::PX));
    bgImgPosition.SetSizeY(AnimatableDimension(0.0, DimensionUnit::PX));
    ViewAbstract::SetBackgroundImagePosition(frameNode, bgImgPosition, true);
}

void SetBlur(ArkUINodeHandle node, ArkUI_Float32 value, const ArkUI_Float32* blurValues, ArkUI_Int32 blurValuesSize,
    ArkUI_Bool disableSystemAdaptation)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ArkUI_Float32 blur = 0.0f;
    BlurOption blurOption;
    blurOption.grayscale.assign(blurValues, blurValues + blurValuesSize);
    if (value > 0) {
        blur = value;
    }
    CalcDimension dimensionBlur(blur, DimensionUnit::PX);
    SysOptions sysOptions;
    sysOptions.disableSystemAdaptation = disableSystemAdaptation;
    ViewAbstract::SetFrontBlur(frameNode, dimensionBlur, blurOption, sysOptions);
}

void ResetBlur(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension dimensionBlur(0.0, DimensionUnit::PX);
    BlurOption blurOption;
    SysOptions sysOptions;
    ViewAbstract::SetFrontBlur(frameNode, dimensionBlur, blurOption, sysOptions);
}

void SetBackdropBlur(ArkUINodeHandle node, ArkUI_Float32 value, const ArkUI_Float32* blurValues,
    ArkUI_Int32 blurValuesSize, ArkUI_Bool disableSystemAdaptation)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ArkUI_Float32 blur = 0.0f;
    BlurOption blurOption;
    blurOption.grayscale.assign(blurValues, blurValues + blurValuesSize);
    if (value > 0) {
        blur = value;
    }
    CalcDimension dimensionBlur(blur, DimensionUnit::PX);
    SysOptions sysOptions;
    sysOptions.disableSystemAdaptation = disableSystemAdaptation;
    ViewAbstract::SetBackdropBlur(frameNode, dimensionBlur, blurOption, sysOptions);
}

void ResetBackdropBlur(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension dimensionBlur(0.0, DimensionUnit::PX);
    BlurOption blurOption;
    SysOptions sysOptions;
    ViewAbstract::SetBackdropBlur(frameNode, dimensionBlur, blurOption, sysOptions);
}

void SetBrightness(ArkUINodeHandle node, ArkUI_Float64 brightness, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value = CalcDimension(brightness, static_cast<DimensionUnit>(unit));
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    ViewAbstract::SetBrightness(frameNode, value);
}

void ResetBrightness(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value(1.0, DimensionUnit::VP);
    ViewAbstract::SetBrightness(frameNode, value);
}

void SetSaturate(ArkUINodeHandle node, ArkUI_Float32 saturate, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value = CalcDimension(saturate, static_cast<DimensionUnit>(unit));
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    ViewAbstract::SetSaturate(frameNode, value);
}

void ResetSaturate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value(1.0, DimensionUnit::VP);
    ViewAbstract::SetSaturate(frameNode, value);
}

void SetContrast(ArkUINodeHandle node, ArkUI_Float64 contrast, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value = CalcDimension(contrast, static_cast<DimensionUnit>(unit));
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    ViewAbstract::SetContrast(frameNode, value);
}

void ResetContrast(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value(1.0, DimensionUnit::VP);
    ViewAbstract::SetContrast(frameNode, value);
}

void SetInvert(ArkUINodeHandle node, ArkUI_Float32* invert, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    InvertVariant invertVariant;
    if (length == INVERT_OPTION_PARAM_SIZE) {
        InvertOption option;
        option.low_ = invert[INDEX_INVERT_LOW];
        option.high_ = invert[INDEX_INVERT_HIGH];
        option.threshold_ = invert[INDEX_INVERT_THRESHOLD];
        option.thresholdRange_ = invert[INDEX_INVERT_THRESHOLD_RANGE];
        invertVariant = option;
    } else if (length == INVERT_SIMPLE_PARAM_SIZE) {
        invertVariant = std::clamp(static_cast<float>(invert[INDEX_INVERT_LOW]), 0.0f, 1.0f);
    }
    ViewAbstract::SetInvert(frameNode, invertVariant);
}

void ResetInvert(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    InvertVariant invert = 0.0f;
    ViewAbstract::SetInvert(frameNode, invert);
}

void SetSepia(ArkUINodeHandle node, ArkUI_Float32 sepia)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value = CalcDimension(sepia, DimensionUnit::VP);
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    ViewAbstract::SetSepia(frameNode, value);
}

void ResetSepia(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension value(0.0, DimensionUnit::VP);
    ViewAbstract::SetSepia(frameNode, value);
}

void SetHueRotate(ArkUINodeHandle node, ArkUI_Float32 deg)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetHueRotate(frameNode, deg);
}

void ResetHueRotate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetHueRotate(frameNode, 0.0);
}

void SetSphericalEffect(ArkUINodeHandle node, ArkUI_Float64 radio)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetSphericalEffect(frameNode, std::clamp(radio, 0.0, 1.0));
}

void ResetSphericalEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetSphericalEffect(frameNode, 0.0);
}

void SetLightUpEffect(ArkUINodeHandle node, ArkUI_Float32 radio)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetLightUpEffect(frameNode, std::clamp(radio, 0.0f, 1.0f));
}

void ResetLightUpEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetLightUpEffect(frameNode, 1.0);
}

void SetColorBlend(ArkUINodeHandle node, uint32_t color, void* colorBlendRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto finalColor = Color(color);
    if (!SystemProperties::ConfigChangePerform()) {
        ViewAbstract::SetColorBlend(frameNode, finalColor);
        return;
    }
    ViewAbstractModelNG::RemoveResObj(frameNode, "viewAbstract.colorBlend");
    RefPtr<ResourceObject> colorBlendResObj;
    if (!colorBlendRawPtr) {
        ResourceParseUtils::CompleteResourceObjectFromColor(
            colorBlendResObj, finalColor, ResourceParseUtils::MakeNativeNodeInfo(frameNode));
    } else {
        colorBlendResObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorBlendRawPtr));
    }
    ViewAbstract::SetColorBlend(frameNode, finalColor, colorBlendResObj);
}

void ResetColorBlend(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelNG::RemoveResObj(frameNode, "viewAbstract.colorBlend");
    ViewAbstract::SetColorBlend(frameNode, Color::TRANSPARENT);
}

void SetPixelStretchEffect(
    ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 length, void* rawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (length != STRETCH_PARAM_SIZE) {
        return;
    }
    ViewAbstractModelNG::RemoveResObj(frameNode, "pixelStretchEffect");
    Dimension left(values[INDEX_STRETCH_LEFT], static_cast<DimensionUnit>(units[INDEX_STRETCH_LEFT]));
    Dimension top(values[INDEX_STRETCH_TOP], static_cast<DimensionUnit>(units[INDEX_STRETCH_TOP]));
    Dimension right(values[INDEX_STRETCH_RIGHT], static_cast<DimensionUnit>(units[INDEX_STRETCH_RIGHT]));
    Dimension bottom(values[INDEX_STRETCH_BOTTOM], static_cast<DimensionUnit>(units[INDEX_STRETCH_BOTTOM]));
    bool illegalInput = false;
    if (left.Unit() == DimensionUnit::PERCENT || right.Unit() == DimensionUnit::PERCENT ||
        top.Unit() == DimensionUnit::PERCENT || bottom.Unit() == DimensionUnit::PERCENT) {
        if ((NearEqual(left.Value(), 0.0) || left.Unit() == DimensionUnit::PERCENT) &&
            (NearEqual(top.Value(), 0.0) || top.Unit() == DimensionUnit::PERCENT) &&
            (NearEqual(right.Value(), 0.0) || right.Unit() == DimensionUnit::PERCENT) &&
            (NearEqual(bottom.Value(), 0.0) || bottom.Unit() == DimensionUnit::PERCENT)) {
            left.SetUnit(DimensionUnit::PERCENT);
            top.SetUnit(DimensionUnit::PERCENT);
            right.SetUnit(DimensionUnit::PERCENT);
            bottom.SetUnit(DimensionUnit::PERCENT);
        } else {
            illegalInput = true;
        }
    }
    PixStretchEffectOption option;
    if ((left.IsNonNegative() && top.IsNonNegative() && right.IsNonNegative() && bottom.IsNonNegative()) ||
        (left.IsNonPositive() && top.IsNonPositive() && right.IsNonPositive() && bottom.IsNonPositive())) {
        option.left = left;
        option.top = top;
        option.right = right;
        option.bottom = bottom;
    } else {
        illegalInput = true;
    }
    if (illegalInput) {
        option.ResetValue();
    }
    ViewAbstract::SetPixelStretchEffect(frameNode, option);
}

void ResetPixelStretchEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelNG::RemoveResObj(frameNode, "pixelStretchEffect");
    PixStretchEffectOption option;
    option.ResetValue();
    ViewAbstract::SetPixelStretchEffect(frameNode, option);
}

void SetLinearGradientBlur(ArkUINodeHandle node, void* blurPara)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* blurParaPtr = reinterpret_cast<NG::LinearGradientBlurPara*>(blurPara);
    ViewAbstract::SetLinearGradientBlur(frameNode, *blurParaPtr);
}

void ResetLinearGradientBlur(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension dimensionBlur(0.0, DimensionUnit::PX);
    std::vector<std::pair<float, float>> fractionStops;
    NG::LinearGradientBlurPara blurPara(dimensionBlur, fractionStops, GradientDirection::BOTTOM);
    ViewAbstract::SetLinearGradientBlur(frameNode, blurPara);
}

void DisableOnAttach(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnAttach(frameNode);
}

void DisableOnDetach(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnDetach(frameNode);
}

void DisableOnClick(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnClick(frameNode);
}

void DisableOnTouch(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnTouch(frameNode);
}

void DisableOnKeyEvent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnKeyEvent(frameNode);
}

void DisableOnMouse(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnMouse(frameNode);
}

void DisableOnHover(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnHover(frameNode);
}

void DisableOnFocus(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnFocus(frameNode);
}

void DisableOnBlur(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::DisableOnBlur(frameNode);
}

void SetXComponentOpacity(ArkUINodeHandle node, ArkUI_Float32 opacity)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto type = XComponentModelNG::GetType(frameNode);
    if (type == XComponentType::SURFACE || type == XComponentType::COMPONENT) {
        return;
    }
    if ((LessNotEqual(opacity, 0.0)) || opacity > MAX_OPACITY) {
        opacity = static_cast<ArkUI_Float32>(MAX_OPACITY);
    }
    ViewAbstract::SetOpacity(frameNode, opacity);
}

void ResetXComponentOpacity(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto type = XComponentModelNG::GetType(frameNode);
    if (type == XComponentType::SURFACE || type == XComponentType::COMPONENT) {
        return;
    }
    ViewAbstract::SetOpacity(frameNode, 1.0f);
}

void SetXComponentId(ArkUINodeHandle node, const char* id)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::SetXComponentId(frameNode, id);
}

void SetXComponentType(ArkUINodeHandle node, uint32_t type)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::SetXComponentType(frameNode, static_cast<XComponentType>(type));
}

void SetXComponentSurfaceSize(ArkUINodeHandle node, uint32_t width, uint32_t height)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::SetXComponentSurfaceSize(frameNode, width, height);
}

ArkUI_CharPtr GetXComponentId(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    g_strValue = XComponentModelNG::GetXComponentId(frameNode);
    return g_strValue.c_str();
}

ArkUI_Int32 GetXComponentType(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return static_cast<ArkUI_Int32>(XComponentModelNG::GetType(frameNode));
}

ArkUI_Uint32 GetXComponentSurfaceWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return XComponentModelNG::GetXComponentSurfaceWidth(frameNode);
}

ArkUI_Uint32 GetXComponentSurfaceHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return XComponentModelNG::GetXComponentSurfaceHeight(frameNode);
}

void* GetNativeXComponent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto xcPattern = frameNode->GetPattern<XComponentPattern>();
    CHECK_NULL_RETURN(xcPattern, nullptr);
    if (xcPattern->HasGotSurfaceHolder() || xcPattern->IsNativeXComponentDisabled()) {
        return nullptr;
    }
    auto pair = xcPattern->GetNativeXComponent();
    xcPattern->SetHasGotNativeXComponent(true);
    return reinterpret_cast<void*>(pair.second.lock().get());
}

void SetXComponentLibraryname(ArkUINodeHandle node, const char* libraryname)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::SetXComponentLibraryname(frameNode, libraryname);
}

void SetImageAIOptions(ArkUINodeHandle node, void* options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::SetImageAIOptions(frameNode, options);
}

void InitXComponent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::InitXComponent(frameNode);
}

void CreateCJXComponent(ArkUI_CharPtr id, ArkUI_Int32 type, ArkUI_CharPtr /* libraryName */, void* controller)
{
    auto* xcomponentController = reinterpret_cast<std::shared_ptr<InnerXComponentController>*>(controller);
    CHECK_NULL_VOID(xcomponentController);
    CHECK_NULL_VOID(*xcomponentController);
    std::optional<std::string> idOpt = id ? std::optional<std::string>(id) : std::nullopt;
    std::optional<std::string> libraryNameOpt = std::nullopt;
    static XComponentModelNG model;
    model.Create(idOpt, static_cast<XComponentType>(type), libraryNameOpt, *xcomponentController);
}

void SetCJXComponentControllerOnCreated(ArkUINodeHandle node, ArkUI_Int64 controllerId,
    void (*callback)(ArkUI_Int64 controllerId, ArkUI_CharPtr surfaceId, ArkUI_CharPtr xcomponentId))
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    auto targetNode = AceType::WeakClaim(frameNode);
    auto onSurfaceCreated = [targetNode, controllerId, callback](
                                const std::string& surfaceId, const std::string& xcomponentId) {
        PipelineContext::SetCallBackNode(targetNode);
        callback(controllerId, surfaceId.c_str(), xcomponentId.c_str());
    };
    XComponentModelNG::SetControllerOnCreated(frameNode, std::move(onSurfaceCreated));
}

void SetCJXComponentControllerOnChanged(ArkUINodeHandle node, ArkUI_Int64 controllerId,
    void (*callback)(ArkUI_Int64 controllerId, ArkUI_CharPtr surfaceId, ArkUI_Float32 left, ArkUI_Float32 top,
        ArkUI_Float32 width, ArkUI_Float32 height))
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    auto targetNode = AceType::WeakClaim(frameNode);
    auto onSurfaceChanged = [targetNode, controllerId, callback](const std::string& surfaceId, const RectF& rect) {
        PipelineContext::SetCallBackNode(targetNode);
        callback(controllerId, surfaceId.c_str(), rect.Left(), rect.Top(), rect.Width(), rect.Height());
    };
    XComponentModelNG::SetControllerOnChanged(frameNode, std::move(onSurfaceChanged));
}

void SetCJXComponentControllerOnDestroyed(ArkUINodeHandle node, ArkUI_Int64 controllerId,
    void (*callback)(ArkUI_Int64 controllerId, ArkUI_CharPtr surfaceId, ArkUI_CharPtr xcomponentId))
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    auto targetNode = AceType::WeakClaim(frameNode);
    auto onSurfaceDestroyed = [targetNode, controllerId, callback](
                                  const std::string& surfaceId, const std::string& xcomponentId) {
        PipelineContext::SetCallBackNode(targetNode);
        callback(controllerId, surfaceId.c_str(), xcomponentId.c_str());
    };
    XComponentModelNG::SetControllerOnDestroyed(frameNode, std::move(onSurfaceDestroyed));
}

void SetXComponentEnableSecure(ArkUINodeHandle node, ArkUI_Bool enable)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::EnableSecure(frameNode, enable);
}

void ResetXComponentEnableSecure(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::EnableSecure(frameNode, false);
}

void SetXComponentHdrBrightness(ArkUINodeHandle node, ArkUI_Float32 hdrBrightness, ArkUI_Int32 hdrType)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (hdrType == INVALID_HDR_TYPE) {
        XComponentModelNG::HdrBrightness(frameNode, hdrBrightness);
        return;
    }
    XComponentModelNG::HdrBrightness(frameNode, hdrBrightness, static_cast<HdrType>(hdrType));
}

void ResetXComponentHdrBrightness(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::HdrBrightness(frameNode, 1.0f);
}

void SetXComponentEnableTransparentLayer(ArkUINodeHandle node, ArkUI_Bool enable)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::EnableTransparentLayer(frameNode, enable);
}

void ResetXComponentEnableTransparentLayer(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::EnableTransparentLayer(frameNode, false);
}

void SetXComponentRenderFit(ArkUINodeHandle node, ArkUI_Int32 renderFitNumber)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto renderFit = RenderFit::RESIZE_FILL;
    if (renderFitNumber >= static_cast<int32_t>(RenderFit::CENTER) &&
        renderFitNumber <= static_cast<int32_t>(RenderFit::RESIZE_COVER_BOTTOM_RIGHT)) {
        renderFit = static_cast<RenderFit>(renderFitNumber);
    }
    auto type = XComponentModelNG::GetType(frameNode);
    if (type == XComponentType::COMPONENT || type == XComponentType::NODE) {
        return;
    }
    if (type == XComponentType::TEXTURE) {
        ViewAbstract::SetRenderFit(frameNode, renderFit);
        return;
    }
    XComponentModelNG::SetRenderFit(frameNode, renderFit);
}

void ResetXComponentRenderFit(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto type = XComponentModelNG::GetXComponentType(frameNode);
    if (type == XComponentType::COMPONENT || type == XComponentType::NODE) {
        return;
    }
    if (type == XComponentType::TEXTURE) {
        ViewAbstract::SetRenderFit(frameNode, RenderFit::RESIZE_FILL);
        return;
    }
    XComponentModelNG::SetRenderFit(frameNode, RenderFit::RESIZE_FILL);
}

ArkUI_Int32 GetXComponentRenderFit(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, static_cast<ArkUI_Int32>(RenderFit::RESIZE_FILL));
    auto type = XComponentModelNG::GetXComponentType(frameNode);
    if (type == XComponentType::TEXTURE) {
        return static_cast<ArkUI_Int32>(ViewAbstract::GetRenderFit(frameNode));
    }
    return static_cast<ArkUI_Int32>(XComponentModelNG::GetSurfaceRenderFit(frameNode));
}

void SetXComponentSurfaceRect(
    ArkUINodeHandle node, ArkUI_Int32 offsetX, ArkUI_Int32 offsetY, ArkUI_Int32 surfaceWidth, ArkUI_Int32 surfaceHeight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (surfaceWidth <= 0 || surfaceHeight <= 0) {
        return;
    }
    XComponentModelNG::SetXComponentSurfaceRect(frameNode, static_cast<float>(offsetX), static_cast<float>(offsetY),
        static_cast<float>(surfaceWidth), static_cast<float>(surfaceHeight));
}

void GetXComponentSurfaceRect(ArkUINodeHandle node, ArkUI_Int32& offsetX, ArkUI_Int32& offsetY,
    ArkUI_Int32& surfaceWidth, ArkUI_Int32& surfaceHeight)
{
    float surfaceRectOffsetX = 0.0f;
    float surfaceRectOffsetY = 0.0f;
    float surfaceRectWidth = 0.0f;
    float surfaceRectHeight = 0.0f;
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::GetXComponentSurfaceRect(
        frameNode, surfaceRectOffsetX, surfaceRectOffsetY, surfaceRectWidth, surfaceRectHeight);
    offsetX = static_cast<ArkUI_Int32>(surfaceRectOffsetX);
    offsetY = static_cast<ArkUI_Int32>(surfaceRectOffsetY);
    surfaceWidth = static_cast<ArkUI_Int32>(surfaceRectWidth);
    surfaceHeight = static_cast<ArkUI_Int32>(surfaceRectHeight);
}

void ResetXComponentSurfaceRect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    float width = ViewAbstract::GetWidth(frameNode).GetNativeValue(static_cast<DimensionUnit>(0));
    float height = ViewAbstract::GetHeight(frameNode).GetNativeValue(static_cast<DimensionUnit>(0));
    XComponentModelNG::SetXComponentSurfaceRect(frameNode, 0.0f, 0.0f, width, height);
}

ArkUI_Bool GetXComponentEnableAnalyzer(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    auto type = XComponentModelNG::GetType(frameNode);
    if (type != XComponentType::SURFACE && type != XComponentType::TEXTURE) {
        return false;
    }
    ArkUI_Bool isEnable = XComponentModelNG::GetXComponentEnableAnalyzer(frameNode);
    return isEnable;
}

void StartImageAnalyzer(ArkUINodeHandle node, void* arkuiNode, void* userData, XComponentAnalyzerCallback callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto xcPattern = frameNode->GetPattern<XComponentPattern>();
    CHECK_NULL_VOID(xcPattern);
    std::function<void(int32_t)> nativeAnalyzerCallback = [arkuiNode, userData, callback](int32_t statusCode) {
        if (callback) {
            callback(arkuiNode, statusCode, userData);
        }
    };
    xcPattern->NativeStartImageAnalyzer(nativeAnalyzerCallback);
}

void StopImageAnalyzer(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto xcPattern = frameNode->GetPattern<XComponentPattern>();
    CHECK_NULL_VOID(xcPattern);
    xcPattern->StopImageAnalyzer();
}

void* CreateSurfaceHolder(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto xcPattern = frameNode->GetPattern<XComponentPatternV2>();
    CHECK_NULL_RETURN(xcPattern, nullptr);
    if (xcPattern->IsCreateSurfaceHolderForbidden()) {
        return nullptr;
    }
    OH_ArkUI_SurfaceHolder* surfaceHolder = xcPattern->GetSurfaceHolder();
    if (surfaceHolder == nullptr) {
        surfaceHolder = new OH_ArkUI_SurfaceHolder();
        xcPattern->SetSurfaceHolder(surfaceHolder);
    }
    return reinterpret_cast<void*>(surfaceHolder);
}

void Dispose(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto xcPattern = frameNode->GetPattern<XComponentPatternV2>();
    CHECK_NULL_VOID(xcPattern);
    xcPattern->SetSurfaceHolder(nullptr);
}

ArkUI_Int32 SetAutoInitialize(ArkUINodeHandle node, ArkUI_Bool autoInitialize)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    auto xcPattern = frameNode->GetPattern<XComponentPatternV2>();
    CHECK_NULL_RETURN(xcPattern, ERROR_CODE_PARAM_INVALID);
    auto nodeType = xcPattern->GetXComponentNodeType();
    if (nodeType != XComponentNodeType::TYPE_NODE && nodeType != XComponentNodeType::CNODE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return xcPattern->SetAutoInitialize(autoInitialize);
}

ArkUI_Int32 Initialize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    auto xcPattern = frameNode->GetPattern<XComponentPatternV2>();
    CHECK_NULL_RETURN(xcPattern, ERROR_CODE_PARAM_INVALID);
    auto nodeType = xcPattern->GetXComponentNodeType();
    if (nodeType != XComponentNodeType::TYPE_NODE && nodeType != XComponentNodeType::CNODE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return xcPattern->Initialize();
}

ArkUI_Int32 IsInitialized(ArkUINodeHandle node, ArkUI_Bool* isInitialized)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    auto xcPattern = frameNode->GetPattern<XComponentPatternV2>();
    CHECK_NULL_RETURN(xcPattern, ERROR_CODE_PARAM_INVALID);
    auto nodeType = xcPattern->GetXComponentNodeType();
    if (nodeType != XComponentNodeType::TYPE_NODE && nodeType != XComponentNodeType::CNODE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    bool value;
    auto res = xcPattern->IsInitialized(value);
    *isInitialized = value;
    return res;
}

ArkUI_Int32 Finalize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    auto xcPattern = frameNode->GetPattern<XComponentPatternV2>();
    CHECK_NULL_RETURN(xcPattern, ERROR_CODE_PARAM_INVALID);
    auto nodeType = xcPattern->GetXComponentNodeType();
    if (nodeType != XComponentNodeType::TYPE_NODE && nodeType != XComponentNodeType::CNODE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return xcPattern->Finalize();
}

ArkUI_Bool GetXComponentIsBindNative(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    auto xcPattern = frameNode->GetPattern<XComponentPattern>();
    CHECK_NULL_RETURN(xcPattern, false);
    return static_cast<ArkUI_Bool>(xcPattern->IsBindNative());
}

ArkUI_Int32 SetExpectedFrameRateRange(ArkUINodeHandle node, ArkUI_Int32 min, ArkUI_Int32 max, ArkUI_Int32 expected)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    if (!(min <= max && expected >= min && expected <= max)) {
        LOGE("Xcomponent Expeted FrameRateRange Error.");
        return ERROR_CODE_PARAM_INVALID;
    }
    return XComponentModelNG::SetExpectedRateRange(frameNode, min, max, expected);
}

ArkUI_Int32 RegisterOnFrameCallback(ArkUINodeHandle node, void (*callback)(void*, uint64_t, uint64_t), void* arkuiNode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    return XComponentModelNG::SetOnFrameCallback(frameNode, callback, arkuiNode);
}

ArkUI_Int32 UnregisterOnFrameCallback(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    return XComponentModelNG::UnregisterOnFrameCallback(frameNode);
}

ArkUI_Int32 SetNeedSoftKeyboard(ArkUINodeHandle node, bool needSoftKeyboard)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    return XComponentModelNG::SetNeedSoftKeyboard(frameNode, needSoftKeyboard);
}

void* CreateAccessibilityProvider(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    return XComponentModelNG::CreateAccessibilityProvider(frameNode);
}

void DisposeAccessibilityProvider(void* provider)
{
    XComponentModelNG::DisposeAccessibilityProvider(reinterpret_cast<ArkUI_AccessibilityProvider*>(provider));
}

void SetXComponentOnLoad(ArkUINodeHandle node, void* callback)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onLoad = reinterpret_cast<LoadEvent*>(callback);
        XComponentModelNG::SetOnLoad(frameNode, std::move(*onLoad));
    }
}

void SetXComponentOnDestroy(ArkUINodeHandle node, void* callback)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onDestroy = reinterpret_cast<DestroyEvent*>(callback);
        XComponentModelNG::SetOnDestroy(frameNode, std::move(*onDestroy));
    }
}

void SetXComponentControllerOnCreated(ArkUINodeHandle node, void* callback)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onCreated = reinterpret_cast<std::function<void(const std::string&, const std::string&)>*>(callback);
        XComponentModelNG::SetControllerOnCreated(frameNode, std::move(*onCreated));
    }
}

void SetXComponentControllerOnChanged(ArkUINodeHandle node, void* callback)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onChanged = reinterpret_cast<std::function<void(const std::string&, const NG::RectF&)>*>(callback);
        XComponentModelNG::SetControllerOnChanged(frameNode, std::move(*onChanged));
    }
}

void SetXComponentControllerOnDestroyed(ArkUINodeHandle node, void* callback)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onDestroyed = reinterpret_cast<std::function<void(const std::string&, const std::string&)>*>(callback);
        XComponentModelNG::SetControllerOnDestroyed(frameNode, std::move(*onDestroyed));
    }
}

ArkUI_Bool IsCommonEventAvailable(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, false);
    auto type = XComponentModelNG::GetType(frameNode);
    auto xcPattern = frameNode->GetPattern<XComponentPattern>();
    CHECK_NULL_RETURN(xcPattern, false);
    auto libraryName = xcPattern->GetLibraryName();
    return static_cast<ArkUI_Bool>(XComponentModel::IsCommonEventAvailable(type, libraryName));
}

void CreateXComponent(ArkUI_Int32 type)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_UINODE_TRACE(nodeId);
    ACE_LAYOUT_SCOPED_TRACE("Create[%sNative][self:%d]", XCOMPONENT_ETS_TAG, nodeId);
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(XCOMPONENT_ETS_TAG, nodeId, [type = static_cast<XComponentType>(type)]() {
            return AceType::MakeRefPtr<XComponentPatternV2>(type, XComponentNodeType::DECLARATIVE_NODE);
        });
    stack->Push(frameNode);
    auto node = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(node);
    auto castXComponentLayoutProperty = node->GetLayoutPropertyPtr<XComponentLayoutProperty>();
    if (castXComponentLayoutProperty) {
        castXComponentLayoutProperty->UpdateXComponentType(static_cast<XComponentType>(type));
    }
}

void CreateXComponentWithParam(ArkUI_CharPtr id, ArkUI_Int32 type, ArkUI_CharPtr libraryName, void* controller)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_UINODE_TRACE(nodeId);
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", XCOMPONENT_ETS_TAG, nodeId);
    auto xcomponentType = static_cast<XComponentType>(type);
    auto xcomponentController =
        controller ? *reinterpret_cast<std::shared_ptr<InnerXComponentController>*>(controller) : nullptr;
    auto frameNode = FrameNode::GetOrCreateFrameNode(XCOMPONENT_ETS_TAG, nodeId,
        [id = id ? std::optional<std::string>(std::string(id)) : std::nullopt, xcomponentType,
            libraryName = libraryName ? std::optional<std::string>(std::string(libraryName)) : std::nullopt,
            xcomponentController]() {
            return AceType::MakeRefPtr<XComponentPattern>(id, xcomponentType, libraryName, xcomponentController);
        });
    stack->Push(frameNode);
    auto node = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(node);
    auto castXComponentLayoutProperty = node->GetLayoutPropertyPtr<XComponentLayoutProperty>();
    if (castXComponentLayoutProperty) {
        castXComponentLayoutProperty->UpdateXComponentType(xcomponentType);
    }
}

void SetXComponentDetachCallback(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* detachCallback = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
    XComponentModelNG::SetDetachCallback(frameNode, std::move(*detachCallback));
}

void SetXComponentSoPath(ArkUI_CharPtr soPath)
{
    if (soPath) {
        auto* frameNode = reinterpret_cast<FrameNode*>(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        CHECK_NULL_VOID(frameNode);
        auto xcPattern = frameNode->GetPattern<XComponentPattern>();
        CHECK_NULL_VOID(xcPattern);
        xcPattern->SetSoPath(std::string(soPath));
    }
}

void SetXComponentScreenId(ArkUI_Uint64 screenId)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::SetScreenId(frameNode, screenId);
}

void SetXComponentBlendMode(ArkUINodeHandle node, ArkUI_Int32 blendMode, ArkUI_Int32 blendApplyTypeValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetBlendMode(frameNode, static_cast<BlendMode>(blendMode));
    ViewAbstract::SetBlendApplyType(frameNode, static_cast<BlendApplyType>(blendApplyTypeValue));
}

void ResetXComponentBlendMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetBlendMode(frameNode, BlendMode::NONE);
}

void SetXComponentBlendApplyType(ArkUINodeHandle node, ArkUI_Int32 blendApplyTypeValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetBlendApplyType(frameNode, static_cast<BlendApplyType>(blendApplyTypeValue));
}

void CreateWithOpacityResourceObj(ArkUINodeHandle node, void* opacityResObj)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* opacityResObjPtr = reinterpret_cast<ResourceObject*>(opacityResObj);
    ViewAbstract::CreateWithOpacityResourceObj(frameNode, AceType::Claim(opacityResObjPtr));
}

void* CreateFrameNode(
    ArkUI_Int32 nodeId, const char* id, ArkUI_Int32 type, const char* libraryName, bool hasLibraryName)
{
    std::optional<std::string> libraryNameOpt;
    if (hasLibraryName) {
        libraryNameOpt = libraryName ? std::optional<std::string>(libraryName) : std::optional<std::string>("");
    }
    auto frameNode = XComponentModelNG::CreateFrameNode(
        nodeId, id ? std::string(id) : std::string(), static_cast<XComponentType>(type), libraryNameOpt);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void* CreateTypeNode(ArkUI_Int32 nodeId, void* params)
{
    auto* xcParams = reinterpret_cast<ArkUI_XComponent_Params*>(params);
    CHECK_NULL_RETURN(xcParams, nullptr);
    auto frameNode = XComponentModelNG::CreateTypeNode(nodeId, xcParams);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

const char* GetLibraryName(FrameNode* frameNode, bool* hasLibraryName)
{
    CHECK_NULL_RETURN(hasLibraryName, "");
    *hasLibraryName = false;
    CHECK_NULL_RETURN(frameNode, "");
    auto xcPattern = frameNode->GetPattern<XComponentPattern>();
    CHECK_NULL_RETURN(xcPattern, "");
    const auto& libraryName = xcPattern->GetLibraryName();
    if (!libraryName.has_value()) {
        return "";
    }
    *hasLibraryName = true;
    g_strValue = libraryName.value();
    return g_strValue.c_str();
}

const char* GetSoPath(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, "");
    auto xcPattern = frameNode->GetPattern<XComponentPattern>();
    CHECK_NULL_RETURN(xcPattern, "");
    g_strValue = xcPattern->GetSoPath().value_or("");
    return g_strValue.c_str();
}

ArkUI_Int32 GetXComponentType(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, static_cast<ArkUI_Int32>(XComponentType::UNKNOWN));
    auto xcPattern = frameNode->GetPattern<XComponentPattern>();
    CHECK_NULL_RETURN(xcPattern, static_cast<ArkUI_Int32>(XComponentType::UNKNOWN));
    return static_cast<ArkUI_Int32>(xcPattern->GetType());
}

void* GetNativeXComponent(FrameNode* frameNode, const char* componentId)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto xcPattern = frameNode->GetPattern<XComponentPattern>();
    CHECK_NULL_RETURN(xcPattern, nullptr);
    auto pair = xcPattern->GetNativeXComponent();
    auto nativeXComponent = pair.second.lock();
    CHECK_NULL_RETURN(nativeXComponent, nullptr);
    CHECK_NULL_RETURN(pair.first, nullptr);
    pair.first->SetXComponentId(componentId ? componentId : "");
    return nativeXComponent.get();
}

void InitExternalEventCallbacks(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto xcPattern = frameNode->GetPattern<XComponentPattern>();
    CHECK_NULL_VOID(xcPattern);
    xcPattern->SetExpectedRateRangeInit();
    xcPattern->OnFrameEventInit();
    xcPattern->UnregisterOnFrameEventInit();
}

void NativeXComponentInit(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto xcPattern = frameNode->GetPattern<XComponentPattern>();
    CHECK_NULL_VOID(xcPattern);
    xcPattern->NativeXComponentInit();
}

void SetImageAIOptionsByFrameNode(FrameNode* frameNode, void* options)
{
    SetImageAIOptions(reinterpret_cast<ArkUINodeHandle>(frameNode), options);
}

void GetApsSdrRatio(const char* packageName, ArkUI_Int32 indexForUsingClient, float apsSdrRatio)
{
    XComponentResolutionConfig::GetInstance().GetApsSdrRatio(
        packageName ? packageName : "", indexForUsingClient, apsSdrRatio);
}

void SetNodeRenderParams(FrameNode* frameNode, ArkUI_Int32 renderType, const char* surfaceId)
{
    CHECK_NULL_VOID(frameNode);
    auto xcPattern = frameNode->GetPattern<XComponentPattern>();
    CHECK_NULL_VOID(xcPattern);
    xcPattern->SetRenderType(static_cast<NodeRenderType>(renderType));
    xcPattern->SetExportTextureSurfaceId(surfaceId ? surfaceId : "");
}

void InitNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto xcPattern = frameNode->GetPattern<XComponentPattern>();
    CHECK_NULL_VOID(xcPattern);
    xcPattern->XComponentSizeInit();
    xcPattern->SetXcomponentInit(true);
}

bool ChangeRenderType(FrameNode* frameNode, ArkUI_Int32 renderType)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto xcPattern = frameNode->GetPattern<XComponentPattern>();
    CHECK_NULL_RETURN(xcPattern, false);
    return xcPattern->ChangeRenderType(static_cast<NodeRenderType>(renderType));
}

void CreateController(std::shared_ptr<OHOS::Ace::InnerXComponentController>* controller)
{
    CHECK_NULL_VOID(controller);
#ifdef XCOMPONENT_SUPPORTED
    *controller = std::make_shared<XComponentControllerNG>();
#endif
}

void LegacyNativeXComponentInit(void* taskPool, void* nativeXComponent, void* nativeXComponentImpl)
{
#ifndef CROSS_PLATFORM
#ifdef XCOMPONENT_SUPPORTED
    auto* pool = reinterpret_cast<XComponentTaskPool*>(taskPool);
    CHECK_NULL_VOID(pool);
    auto* component = reinterpret_cast<OH_NativeXComponent*>(nativeXComponent);
    auto* componentImpl = reinterpret_cast<NativeXComponentImpl*>(nativeXComponentImpl);
    CHECK_NULL_VOID(component);
    CHECK_NULL_VOID(componentImpl);
    pool->NativeXComponentInit(component, AceType::WeakClaim(componentImpl));
#endif
#endif
}

void ParseParams(void* runtimeCallInfo, ArkUI_Params& params)
{
    auto* runtimeCallInfoPtr = reinterpret_cast<ArkUIRuntimeCallInfo*>(runtimeCallInfo);
    XComponentBridge::ParseParams(runtimeCallInfoPtr, params);
}

void SetControllerCallback(void* runtimeCallInfo, ArkUINodeHandle* node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* runtimeCallInfoPtr = reinterpret_cast<ArkUIRuntimeCallInfo*>(runtimeCallInfo);
    XComponentBridge::SetControllerCallback(runtimeCallInfoPtr, frameNode);
}
} // namespace

namespace NodeModifier {
const ArkUIXComponentModifier* GetXComponentDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifdef XCOMPONENT_SUPPORTED
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIXComponentModifier modifier = {
            .setXComponentEnableAnalyzer = SetXComponentEnableAnalyzerImpl,
            .resetXComponentEnableAnalyzer = ResetXComponentEnableAnalyzerImpl,
            .setXComponentBackgroundColor = SetXComponentBackgroundColorImpl,
            .setXComponentBackgroundColorWithColorSpace = SetXComponentBackgroundColorWithColorSpaceImpl,
            .setXComponentBackgroundColorForHDR = SetXComponentBackgroundColorForHDRImpl,
            .resetXComponentBackgroundColor = ResetXComponentBackgroundColorImpl,
            .setBackgroundImage = SetXComponentBackgroundImageImpl,
            .setBackgroundImageSyncMode = SetBackgroundImageSyncModeImpl,
            .setBackgroundImagePixelMapByPixelMapPtr = SetBackgroundImagePixelMapByPixelMapPtrImpl,
            .setBackgroundImageRepeat = SetBackgroundImageRepeatImpl,
            .clearResObj = ClearResObj,
            .setBackgroundImageSize = SetBackgroundImageSizeImpl,
            .resetBackgroundImageSize = ResetBackgroundImageSizeImpl,
            .setBackgroundImagePosition = SetBackgroundImagePositionImpl,
            .resetBackgroundImagePosition = ResetBackgroundImagePositionImpl,
            .setXComponentOpacity = SetXComponentOpacityImpl,
            .resetXComponentOpacity = ResetXComponentOpacityImpl,
            .setBlur = SetBlurImpl,
            .resetBlur = ResetBlurImpl,
            .setBackdropBlur = SetBackdropBlurImpl,
            .resetBackdropBlur = ResetBackdropBlurImpl,
            .setBrightness = SetBrightnessImpl,
            .resetBrightness = ResetBrightnessImpl,
            .setSaturate = SetSaturateImpl,
            .resetSaturate = ResetSaturateImpl,
            .setContrast = SetContrastImpl,
            .resetContrast = ResetContrastImpl,
            .setInvert = SetInvertImpl,
            .resetInvert = ResetInvertImpl,
            .setSepia = SetSepiaImpl,
            .resetSepia = ResetSepiaImpl,
            .setHueRotate = SetHueRotateImpl,
            .resetHueRotate = ResetHueRotateImpl,
            .setSphericalEffect = SetSphericalEffectImpl,
            .resetSphericalEffect = ResetSphericalEffectImpl,
            .setLightUpEffect = SetLightUpEffectImpl,
            .resetLightUpEffect = ResetLightUpEffectImpl,
            .setColorBlend = SetColorBlendImpl,
            .resetColorBlend = ResetColorBlendImpl,
            .setPixelStretchEffect = SetPixelStretchEffectImpl,
            .resetPixelStretchEffect = ResetPixelStretchEffectImpl,
            .setLinearGradientBlur = SetLinearGradientBlurImpl,
            .resetLinearGradientBlur = ResetLinearGradientBlurImpl,
            .disableOnAttach = DisableOnAttachImpl,
            .disableOnDetach = DisableOnDetachImpl,
            .disableOnClick = DisableOnClickImpl,
            .disableOnTouch = DisableOnTouchImpl,
            .disableOnKeyEvent = DisableOnKeyEventImpl,
            .disableOnMouse = DisableOnMouseImpl,
            .disableOnHover = DisableOnHoverImpl,
            .disableOnFocus = DisableOnFocusImpl,
            .disableOnBlur = DisableOnBlurImpl,
            .setXComponentId = nullptr,
            .setXComponentType = nullptr,
            .setXComponentSurfaceSize = nullptr,
            .getXComponentId = nullptr,
            .getXComponentType = nullptr,
            .getXComponentSurfaceWidth = nullptr,
            .getXComponentSurfaceHeight = nullptr,
            .getNativeXComponent = nullptr,
            .setXComponentLibraryname = nullptr,
            .setImageAIOptions = nullptr,
            .initXComponent = nullptr,
            .setXComponentEnableSecure = SetXComponentEnableSecureImpl,
            .resetXComponentEnableSecure = ResetXComponentEnableSecureImpl,
            .setXComponentHdrBrightness = SetXComponentHdrBrightnessImpl,
            .resetXComponentHdrBrightness = ResetXComponentHdrBrightnessImpl,
            .setXComponentEnableTransparentLayer = SetXComponentEnableTransparentLayerImpl,
            .resetXComponentEnableTransparentLayer = ResetXComponentEnableTransparentLayerImpl,
            .setXComponentRenderFit = SetXComponentRenderFitImpl,
            .resetXComponentRenderFit = ResetXComponentRenderFitImpl,
            .getXComponentRenderFit = nullptr,
            .setXComponentSurfaceRect = nullptr,
            .getXComponentSurfaceRect = nullptr,
            .resetXComponentSurfaceRect = nullptr,
            .getXComponentEnableAnalyzer = nullptr,
            .startImageAnalyzer = nullptr,
            .stopImageAnalyzer = nullptr,
            .createSurfaceHolder = nullptr,
            .dispose = nullptr,
            .setAutoInitialize = nullptr,
            .initialize = nullptr,
            .isInitialized = nullptr,
            .finalize = nullptr,
            .getXComponentIsBindNative = nullptr,
            .setExpectedFrameRateRange = nullptr,
            .registerOnFrameCallback = nullptr,
            .unregisterOnFrameCallback = nullptr,
            .setNeedSoftKeyboard = nullptr,
            .createAccessibilityProvider = nullptr,
            .disposeAccessibilityProvider = nullptr,
            .setXComponentOnLoad = SetXComponentOnLoadImpl,
            .setXComponentOnDestroy = SetXComponentOnDestroyImpl,
            .setXComponentControllerOnCreated = SetXComponentControllerOnCreatedImpl,
            .setXComponentControllerOnChanged = SetXComponentControllerOnChangedImpl,
            .setXComponentControllerOnDestroyed = SetXComponentControllerOnDestroyedImpl,
            .isCommonEventAvailable = IsCommonEventAvailableImpl,
            .createXComponent = CreateXComponent,
            .createXComponentWithParam = CreateXComponentWithParam,
            .setXComponentDetachCallback = SetXComponentDetachCallback,
            .setXComponentSoPath = SetXComponentSoPathImpl,
            .setXComponentScreenId = SetXComponentScreenIdImpl,
            .setXComponentBlendMode = SetXComponentBlendModeImpl,
            .resetXComponentBlendMode = ResetXComponentBlendModeImpl,
            .setXComponentBlendApplyType = SetXComponentBlendApplyTypeImpl,
            .createWithOpacityResourceObj = CreateWithOpacityResourceObjImpl,
            .parseParams = ParseParams,
            .setControllerCallback = SetControllerCallback,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
#endif
#endif
    }

    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIXComponentModifier modifier = {
        .setXComponentEnableAnalyzer = SetXComponentEnableAnalyzer,
        .resetXComponentEnableAnalyzer = ResetXComponentEnableAnalyzer,
        .setXComponentBackgroundColor = SetXComponentBackgroundColor,
        .setXComponentBackgroundColorWithColorSpace = SetXComponentBackgroundColorWithColorSpace,
        .setXComponentBackgroundColorForHDR = SetXComponentBackgroundColorForHDR,
        .resetXComponentBackgroundColor = ResetXComponentBackgroundColor,
        .setBackgroundImage = SetBackgroundImage,
        .setBackgroundImageSyncMode = SetBackgroundImageSyncMode,
        .setBackgroundImagePixelMapByPixelMapPtr = SetBackgroundImagePixelMapByPixelMapPtr,
        .setBackgroundImageRepeat = SetBackgroundImageRepeat,
        .clearResObj = ClearResObj,
        .setBackgroundImageSize = SetBackgroundImageSize,
        .resetBackgroundImageSize = ResetBackgroundImageSize,
        .setBackgroundImagePosition = SetBackgroundImagePosition,
        .resetBackgroundImagePosition = ResetBackgroundImagePosition,
        .setXComponentOpacity = SetXComponentOpacity,
        .resetXComponentOpacity = ResetXComponentOpacity,
        .setBlur = SetBlur,
        .resetBlur = ResetBlur,
        .setBackdropBlur = SetBackdropBlur,
        .resetBackdropBlur = ResetBackdropBlur,
        .setBrightness = SetBrightness,
        .resetBrightness = ResetBrightness,
        .setSaturate = SetSaturate,
        .resetSaturate = ResetSaturate,
        .setContrast = SetContrast,
        .resetContrast = ResetContrast,
        .setInvert = SetInvert,
        .resetInvert = ResetInvert,
        .setSepia = SetSepia,
        .resetSepia = ResetSepia,
        .setHueRotate = SetHueRotate,
        .resetHueRotate = ResetHueRotate,
        .setSphericalEffect = SetSphericalEffect,
        .resetSphericalEffect = ResetSphericalEffect,
        .setLightUpEffect = SetLightUpEffect,
        .resetLightUpEffect = ResetLightUpEffect,
        .setColorBlend = SetColorBlend,
        .resetColorBlend = ResetColorBlend,
        .setPixelStretchEffect = SetPixelStretchEffect,
        .resetPixelStretchEffect = ResetPixelStretchEffect,
        .setLinearGradientBlur = SetLinearGradientBlur,
        .resetLinearGradientBlur = ResetLinearGradientBlur,
        .disableOnAttach = DisableOnAttach,
        .disableOnDetach = DisableOnDetach,
        .disableOnClick = DisableOnClick,
        .disableOnTouch = DisableOnTouch,
        .disableOnKeyEvent = DisableOnKeyEvent,
        .disableOnMouse = DisableOnMouse,
        .disableOnHover = DisableOnHover,
        .disableOnFocus = DisableOnFocus,
        .disableOnBlur = DisableOnBlur,
        .setXComponentId = SetXComponentId,
        .setXComponentType = SetXComponentType,
        .setXComponentSurfaceSize = SetXComponentSurfaceSize,
        .getXComponentId = GetXComponentId,
        .getXComponentType = GetXComponentType,
        .getXComponentSurfaceWidth = GetXComponentSurfaceWidth,
        .getXComponentSurfaceHeight = GetXComponentSurfaceHeight,
        .getNativeXComponent = GetNativeXComponent,
        .setXComponentLibraryname = SetXComponentLibraryname,
        .setImageAIOptions = SetImageAIOptions,
        .initXComponent = InitXComponent,
        .setXComponentEnableSecure = SetXComponentEnableSecure,
        .resetXComponentEnableSecure = ResetXComponentEnableSecure,
        .setXComponentHdrBrightness = SetXComponentHdrBrightness,
        .resetXComponentHdrBrightness = ResetXComponentHdrBrightness,
        .setXComponentEnableTransparentLayer = SetXComponentEnableTransparentLayer,
        .resetXComponentEnableTransparentLayer = ResetXComponentEnableTransparentLayer,
        .setXComponentRenderFit = SetXComponentRenderFit,
        .resetXComponentRenderFit = ResetXComponentRenderFit,
        .getXComponentRenderFit = GetXComponentRenderFit,
        .setXComponentSurfaceRect = SetXComponentSurfaceRect,
        .getXComponentSurfaceRect = GetXComponentSurfaceRect,
        .resetXComponentSurfaceRect = ResetXComponentSurfaceRect,
        .getXComponentEnableAnalyzer = GetXComponentEnableAnalyzer,
        .startImageAnalyzer = StartImageAnalyzer,
        .stopImageAnalyzer = StopImageAnalyzer,
        .createSurfaceHolder = CreateSurfaceHolder,
        .dispose = Dispose,
        .setAutoInitialize = SetAutoInitialize,
        .initialize = Initialize,
        .isInitialized = IsInitialized,
        .finalize = Finalize,
        .getXComponentIsBindNative = GetXComponentIsBindNative,
        .setExpectedFrameRateRange = SetExpectedFrameRateRange,
        .registerOnFrameCallback = RegisterOnFrameCallback,
        .unregisterOnFrameCallback = UnregisterOnFrameCallback,
        .setNeedSoftKeyboard = SetNeedSoftKeyboard,
        .createAccessibilityProvider = CreateAccessibilityProvider,
        .disposeAccessibilityProvider = DisposeAccessibilityProvider,
        .setXComponentOnLoad = SetXComponentOnLoad,
        .setXComponentOnDestroy = SetXComponentOnDestroy,
        .setXComponentControllerOnCreated = SetXComponentControllerOnCreated,
        .setXComponentControllerOnChanged = SetXComponentControllerOnChanged,
        .setXComponentControllerOnDestroyed = SetXComponentControllerOnDestroyed,
        .isCommonEventAvailable = IsCommonEventAvailable,
        .createXComponent = CreateXComponent,
        .createXComponentWithParam = CreateXComponentWithParam,
        .setXComponentDetachCallback = SetXComponentDetachCallback,
        .setXComponentSoPath = SetXComponentSoPath,
        .setXComponentScreenId = SetXComponentScreenId,
        .setXComponentBlendMode = SetXComponentBlendMode,
        .resetXComponentBlendMode = ResetXComponentBlendMode,
        .setXComponentBlendApplyType = SetXComponentBlendApplyType,
        .createWithOpacityResourceObj = CreateWithOpacityResourceObj,
        .parseParams = ParseParams,
        .setControllerCallback = SetControllerCallback,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUIXComponentModifier* GetCJUIXComponentDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIXComponentModifier modifier = {
        .loadXComponent = nullptr,
        .setXComponentOptions = nullptr,
        .getXComponentSurfaceId = nullptr,
        .getXComponentController = nullptr,
        .setXComponentBackgroundColor = SetXComponentBackgroundColor,
        .setXComponentBackgroundColorWithColorSpace = SetXComponentBackgroundColorWithColorSpace,
        .resetXComponentBackgroundColor = ResetXComponentBackgroundColor,
        .setXComponentOpacity = SetXComponentOpacity,
        .resetXComponentOpacity = ResetXComponentOpacity,
        .setXComponentId = SetXComponentId,
        .setXComponentType = SetXComponentType,
        .setXComponentSurfaceSize = SetXComponentSurfaceSize,
        .getXComponentId = GetXComponentId,
        .getXComponentType = GetXComponentType,
        .getXComponentSurfaceWidth = GetXComponentSurfaceWidth,
        .getXComponentSurfaceHeight = GetXComponentSurfaceHeight,
        .getNativeXComponent = GetNativeXComponent,
        .setXComponentLibraryname = SetXComponentLibraryname,
        .setImageAIOptions = SetImageAIOptions,
        .createXComponent = CreateCJXComponent,
        .setControllerOnCreated = SetCJXComponentControllerOnCreated,
        .setControllerOnChanged = SetCJXComponentControllerOnChanged,
        .setControllerOnDestroyed = SetCJXComponentControllerOnDestroyed,
        .setXComponentEnableSecure = SetXComponentEnableSecure,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const ArkUIXComponentCustomModifier* GetXComponentDynamicCustomModifier()
{
    static const ArkUIXComponentCustomModifier modifier = {
        .createFrameNode = CreateFrameNode,
        .createTypeNode = CreateTypeNode,
        .getLibraryName = GetLibraryName,
        .getSoPath = GetSoPath,
        .getXComponentType = GetXComponentType,
        .getNativeXComponent = GetNativeXComponent,
        .initExternalEventCallbacks = InitExternalEventCallbacks,
        .nativeXComponentInit = NativeXComponentInit,
        .setImageAIOptions = SetImageAIOptionsByFrameNode,
        .getApsSdrRatio = GetApsSdrRatio,
        .setNodeRenderParams = SetNodeRenderParams,
        .initNode = InitNode,
        .changeRenderType = ChangeRenderType,
        .createController = CreateController,
        .legacyNativeXComponentInit = LegacyNativeXComponentInit,
    };
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
