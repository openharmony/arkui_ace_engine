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

#ifndef OHOS_ACE_FRAMEWORK_CJ_VIEW_ABSTRACT_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_VIEW_ABSTRACT_FFI_H

#include "cj_transitioneffect.h"

#include "bridge/cj_frontend/cppview/view_abstract.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_collection_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/utils.h"
#include "core/common/container.h"
#include "core/components/common/properties/color.h"

using VectorMenuValuePtr = void*;
using VectorStringPtr = void*;
using VectorNativeRectangleHandle = void*;

namespace OHOS::Ace::Framework {

static RefPtr<PipelineBase> GetPipelineContext()
{
    auto currentObj = Container::Current();
    CHECK_NULL_RETURN(currentObj, nullptr);
    return currentObj->GetPipelineContext();
}

template<typename T>
static RefPtr<T> GetTheme()
{
    auto pipelineContext = GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    return themeManager->GetTheme<T>();
}
} // namespace OHOS::Ace::Framework

extern "C" {
struct NativeRectangle {
    double x;
    int32_t xUnit;
    double y;
    int32_t yUnit;
    double width;
    int32_t widthUnit;
    double height;
    int32_t heightUnit;
};

struct CJBindPopupParams {
    char* message;
    bool placementOnTop;
    char* primaryValue;
    void (*primaryAction)();
    char* secondaryValue;
    void (*secondaryAction)();
    void (*onStateChange)(bool);
};

struct CJSheetOptions {
    NativeOptionUInt32 backgroundColor;
    NativeOptionCallBack onAppear;
    NativeOptionCallBack onDisappear;
    NativeOptionCallBack onWillAppear;
    NativeOptionCallBack onWillDisappear;
    NativeOptionInt32 height;
    NativeOptionCArrInt32 detents;
    NativeOptionInt32 preferType;
    NativeOptionBool showClose;
    NativeOptionBool dragBarl;
    NativeOptionInt32 blurStyle;
    NativeOptionUInt32 maskColor;
    NativeOptionCallBack title;
    NativeOptionBool enableOutsideInteractive;
    NativeOptionCallBack shouldDismiss;
};

struct CJBorder {
    double width;
    int32_t widthUnit;
    uint32_t color;
    double radius;
    int32_t radiusUnit;
    int32_t style;
};

struct CJBorderWithId {
    double width;
    int32_t widthUnit;
    int64_t colorId;
    double radius;
    int32_t radiusUnit;
    int32_t style;
};

struct CJEdge {
    double top;
    int32_t topUnit;
    double right;
    int32_t rightUnit;
    double bottom;
    int32_t bottomUnit;
    double left;
    int32_t leftUnit;
};

struct RetDimension {
    double value;
    int32_t unit;
};

struct CJBorderRadius {
    double topLeft;
    int32_t topLeftUnit;
    double topRight;
    int32_t topRightUnit;
    double bottomLeft;
    int32_t bottomLeftUnit;
    double bottomRight;
    int32_t bottomRightUnit;
};

struct CJTranslate {
    double x;
    int32_t xUnit;
    double y;
    int32_t yUnit;
    double z;
    int32_t zUnit;
};

struct CJResponseRegion {
    double x;
    int32_t xUnit;
    double y;
    int32_t yUnit;
    double width;
    int32_t widthUnit;
    double height;
    int32_t heightUnit;
};

struct CJConstraintSize {
    double minWidth;
    int32_t minWidthUnit;
    double maxWidth;
    int32_t maxWidthUnit;
    double minHeight;
    int32_t minHeightUnit;
    double maxHeight;
    int32_t maxHeightUnit;
};

struct CJSetScale {
    float scaleX;
    float scaleY;
    float scaleZ;
    double centerX;
    int32_t centerXUnit;
    double centerY;
    int32_t centerYUnit;
};

struct CJBlurOptions {
    float grayscale[2];
};

struct CJForegroundBlurStyle {
    int32_t colorMode;
    int32_t adaptiveColor;
    CJBlurOptions blurOptions;
};

struct CJAlignRuleOption {
    char* leftAnchor;
    int32_t leftHorizontalAlign;
    char* rightAnchor;
    int32_t rightHorizontalAlign;
    char* middleAnchor;
    int32_t middleHorizontalAlign;
    char* topAnchor;
    int32_t topVerticalAlign;
    char* bottomAnchor;
    int32_t bottomVerticalAlign;
    char* centerAnchor;
    int32_t centerVerticalAlign;
    float* horizontalBias;
    float* verticalBias;
};

CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetWidth(double width, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetHeight(double height, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetSize(
    double width, int32_t widthUnit, double height, int32_t heightUnit);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetResponseRegion(CJResponseRegion value);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetResponseRegionArray(VectorStringPtr vecContent);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetConstraintSize(CJConstraintSize value);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetLayoutPriority(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetLayoutWeight(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetBorder(CJBorder params);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetBorderWidth(double width, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetBorderWidthWithCJEdge(CJEdge params);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetBorderColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetBorderRadius(double radius, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetAllBorderRadius(CJBorderRadius value);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetBorderStyle(int32_t style);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetMargin(double margin, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetMargins(CJEdge params);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetPadding(double padding, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetPaddings(CJEdge params);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetForegroundBlurStyle(int32_t blurStyle);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetForegroundBlurStyleOption(
    int32_t blurStyle, CJForegroundBlurStyle options);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetForegroundColor(char* strategy);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetForegroundResourceColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetBackgroundColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetBackgroundImage(const char* src, int32_t repeat);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetBackgroundImageSizeType(int32_t imageSize);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetBackgroundImageSize(
    double width, int32_t widthUnit, double height, int32_t heightUnit);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetBackgroundImagePositionAlign(int32_t align);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetBackgroundImagePositionXY(
    double x, int32_t xUnit, double y, int32_t yUnit);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetScale(CJSetScale value);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetScaleSingle(float scale);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetScaleX(float scaleVal);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetScaleY(float scaleVal);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetOpacity(double opacity);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractbindSheetParam(bool isShow, void (*builder)(), CJSheetOptions option);

struct CJSetRotate {
    float dx;
    float dy;
    float dz;
    float angle;
    double centerX;
    int32_t centerXUnit;
    double centerY;
    int32_t centerYUnit;
};
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetRotate(CJSetRotate value);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetRotateSingle(float rotateZ);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetRotateX(float rotateVal);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetRotateY(float rotateVal);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetTranslate(CJTranslate value);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetTranslateSingle(double translateValue, int32_t translateUnit);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetTranslateX(double translateValue, int32_t translateUnit);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetTranslateY(double translateValue, int32_t translateUnit);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetTransition();
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractTransition(int64_t id);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetTransform(int64_t id);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetAlign(int32_t value);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetDirection(int32_t dirValue);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetPosition(double x, int32_t xUnit, double y, int32_t yUnit);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetMarkAnchor(double x, int32_t xUnit, double y, int32_t yUnit);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetOffset(double x, int32_t xUnit, double y, int32_t yUnit);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetAlignRules(CJAlignRuleOption option);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetEnabled(bool value);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetAspectRatio(double value);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetDisplayPriority(int32_t value);

struct CJMotionPathOptions {
    char* path;
    double from;
    double to;
    bool rotatable;
};
struct CJSharedTransitionOptions {
    int32_t duration;
    int32_t delay;
    int32_t zIndex;
    char* curve;
    CJMotionPathOptions motionPathOption;
    int32_t type;
};
struct CJGeometryTransitionOptions {
    bool follow = false;
    int32_t hierarchyStrategy;
};

CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetSharedTransition(char* shareId, CJSharedTransitionOptions option);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetGeometryTransition(char* id, CJGeometryTransitionOptions option);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetBlur(double value);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetColorBlend(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetBackdropBlur(double value);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetWindowBlur(float progress, int32_t styleValue);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetShadow(double radius, uint32_t color, double offsetX, double offsetY);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetGrayScale(double value);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetBrightness(double value);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetSaturate(double value);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetContrast(double value);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetInvert(double value);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetSepia(double value);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetHueRotate(float deg);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetFlexBasis(double value, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetFlexGrow(double value);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetFlexShrink(double value);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetAlignSelf(int32_t alignValue);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetZIndex(int32_t zIndex);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetVisibility(int32_t visibility);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetClip(bool isClip);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetClipByShape(int64_t shapeId);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetMaskByShape(int64_t shapeId);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractPop();
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetOverlay(const char* title, int32_t align, double x, double y);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractBindPopup(bool isShow, CJBindPopupParams bindPopupParams);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractKeyShortcutByFuncKey(
    int32_t value, int32_t* keysArray, int64_t size, void (*callback)(void));
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractKeyShortcutByChar(
    const char* value, int32_t* keysArray, int64_t size, void (*callback)(void));

struct CJBindCustomPopup {
    bool isShow;
    void (*builder)();
    int32_t placement;
    uint32_t maskColor;
    uint32_t backgroundColor;
    bool enableArrow;
    bool autoCancel;
    void (*onStateChange)(bool);
};
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractBindCustomPopup(CJBindCustomPopup value);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractBindMenu(
    VectorMenuValuePtr vectorMenuValue, void (*menuActionCallback)(const char*));
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractBindCustomMenu(void (*builder)());
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractBindContextMenu(void (*builder)(), int32_t responseType);
struct CColors {
    uint32_t color;
    double location;
};

struct CArrCColors {
    CColors* header;
    int64_t size;
};

struct LinearGradientParam {
    double* angle;
    int32_t direction;
    CArrCColors colors;
    bool repeating;
};

CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractLinearGradient(LinearGradientParam linearGradientParam);
struct CTupleLength {
    double rowValue;
    int32_t rowUnitType;
    double columnValue;
    int32_t columnUnitType;
};

struct SweepGradientParam {
    CTupleLength center;
    double start;
    double end;
    double rotation;
    CArrCColors colors;
    bool repeating;
};
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSweepGradient(SweepGradientParam sweepGradientParam);

struct RadialGradientParam {
    CTupleLength center;
    double radius;
    int32_t radiusUnit;
    CArrCColors colors;
    bool repeating;
};
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractRadialGradient(RadialGradientParam radialGradientParam);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractRenderFit(int32_t fitMode);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetInspectorKey(const char* key);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractSetId(const char* id);
CJ_EXPORT VectorNativeRectangleHandle FFICJCreateVectorNativeRectangle(int64_t size);
CJ_EXPORT void FFICJVectorNativeRectangleSetElement(
    VectorNativeRectangleHandle vec, int64_t index, NativeRectangle rect);
CJ_EXPORT void FFICJVectorNativeRectangleDelete(VectorNativeRectangleHandle vec);
CJ_EXPORT ExternalString FFIOHOSAceFrameworkGetResourceStr(int64_t id, uint32_t type, const char* param);
CJ_EXPORT ExternalString FFIOHOSAceFrameworkGetResourcePluralStr(
    int64_t id, uint32_t type, int64_t count, const char* plural);
CJ_EXPORT RetDimension FFIOHOSAceFrameworkGetResourceDimension(int64_t id);
CJ_EXPORT uint32_t FFIOHOSAceFrameworkGetResourceColor(int64_t id);
CJ_EXPORT ExternalString FFIOHOSAceFrameworkGetResourceMedia(int64_t id, uint32_t type, const char* param);
CJ_EXPORT uint32_t FFIGetResourceSymbolId(NativeResourceObject obj);
CJ_EXPORT void FfiOHOSAceFrameworkViewAbstractExpandSafeArea(uint32_t types, uint32_t edges);
CJ_EXPORT void FFIOHOSAceFrameworkFocusable(bool isFocusable);
CJ_EXPORT void FFIOHOSAceFrameworkTabIndex(int32_t index);
CJ_EXPORT void FFIOHOSAceFrameworkDefaultFocus(bool isDefaultFocus);
CJ_EXPORT void FFIOHOSAceFrameworkGroupDefaultFocus(bool isGroupDefaultFocus);
CJ_EXPORT void FFIOHOSAceFrameworkFocusOnTouch(bool isFocusOnTouch);
CJ_EXPORT bool FFIOHOSAceFrameworkRequestFocus(const char* inspectorKey);

struct CJFocusBoxStyle {
    bool hasMargin;
    bool hasStrokeColor;
    bool hasStrokeWidth;
    double margin;
    int32_t marginUnit;
    uint32_t strokeColor;
    double strokeWidth;
    int32_t strokeWidthUnit;
};

CJ_EXPORT void FFIOHOSAceFrameworkFocusBox(CJFocusBoxStyle cjStyle);
CJ_EXPORT void FFIOHOSAceFrameworkFocusScopePriority(const char* scopeId, int32_t priority);
CJ_EXPORT void FFIOHOSAceFrameworkFocusScopeId(const char* id, bool isGroup, bool arrowStepOut);
CJ_EXPORT uint32_t FFIOHOSAceFrameworkBlendColor(uint32_t color, uint32_t overlayColor);

CJ_EXPORT void FFISetWidthWithEmpty();
CJ_EXPORT void FFISetHeightWithEmpty();

struct CJContentCoverOptions {
    uint32_t modalTransition;
    NativeOptionUInt32 backgroundColor;
    NativeOptionCallBack onAppear;
    NativeOptionCallBack onDisappear;
    NativeOptionCallBack onWillAppear;
    NativeOptionCallBack onWillDisappear;
};
CJ_EXPORT void FFIOHOSAceFrameworkBindContentCover(bool isShow, void (*builder)(), CJContentCoverOptions options);

CJ_EXPORT ExternalString FFIGetResourceString(NativeResourceObject obj);
CJ_EXPORT ExternalString FFIGetResourceMedia(NativeResourceObject obj);
CJ_EXPORT uint32_t FFIGetResourceColor(NativeResourceObject obj);
CJ_EXPORT RetDimension FFIGetResourceDimension(NativeResourceObject obj);
CJ_EXPORT double FFIGetResourceDouble(NativeResourceObject obj);
CJ_EXPORT int32_t FFIGetResourceInt32(NativeResourceObject obj);
CJ_EXPORT uint32_t FFIGetResourceUInt32(NativeResourceObject obj);
CJ_EXPORT bool FFIGetResourceBool(NativeResourceObject obj);
CJ_EXPORT VectorUInt32Handle FFIGetResourceVectorUInt32(NativeResourceObject obj);
CJ_EXPORT VectorStringHandle FFIGetResourceVectorString(NativeResourceObject obj);
}

namespace OHOS::Ace {
bool ParseCjMedia(int64_t id, ResourceType type, const std::string& params, std::string& result);
bool ParseCjString(int64_t id, ResourceType type, const std::string& params, std::string& result);
bool ParseCjString(int64_t id, ResourceType type, int64_t count, const std::string& plural, std::string& result);
bool ParseCjDimension(int64_t id, Dimension& result);
bool ParseColorById(int64_t id, Color& color);
void ParseCJResponseRegion(CJResponseRegion value, std::vector<DimensionRect>& result);
void ParseVectorStringPtr(VectorStringPtr value, std::vector<DimensionRect>& result);
} // namespace OHOS::Ace

#endif // OHOS_ACE_FRAMEWORK_CJ_VIEW_ABSTRACT_FFI_H
