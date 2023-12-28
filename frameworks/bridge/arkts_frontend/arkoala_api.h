/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ARKOALA_API_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ARKOALA_API_H

#define ARKUI_FULL_API_VERSION 62
// When changing ARKUI_BASIC_API_VERSION, ARKUI_FULL_API_VERSION must be
// increased as well.
#define ARKUI_BASIC_API_VERSION 3
#define ARKUI_GRAPHICS_API_VERSION 3

enum ArkUIAPIVariantKind {
    Basic = 1,
    Full = 2,
    Graphics = 3,
    Count = Graphics + 1,
};

typedef int Arkoala_Bool;
typedef int Arkoala_Int32;
typedef unsigned int Arkoala_Uint32;
typedef long long Arkoala_Int64;
typedef float Arkoala_Float32;
typedef double Arkoala_Float64;
typedef const char* Arkoala_CharPtr;

// Several opaque struct declarations.
struct _ArkUIVMContext;
struct _ArkUIVMObject;
struct _ArkUINode;
struct _ArkUICanvas;
struct _ArkUIPaint;
struct _ArkUIFont;
struct _ArkUIXComponentController;

typedef _ArkUINode* ArkUINodeHandle;
typedef _ArkUIVMContext* ArkUIVMContext;
typedef _ArkUIVMObject* ArkUIVMObject;
typedef _ArkUICanvas* ArkUICanvasHandle;
typedef _ArkUIPaint* ArkUIPaintHandle;
typedef _ArkUIFont* ArkUIFontHandle;
typedef _ArkUIXComponentController* ArkUIXComponentControllerHandle;

enum ArkUIAPIEventKind {
    Invalid = 0,
    SinglePointerInput = 1,
    MultiPointerInput = 2,
    Callback = 3,
    ComponentAsyncEvent = 4,
    TextInput = 5,
    GestureAsyncEvent = 6
};

enum ArkUIAPIComponentAsyncEventSubKind {
    OnAppear = 0,
    OnDisappear = 1,
    SwiperChange = 2,
    TabsChange = 3,
    VisibleAreaChange = 4,
    OnClick = 5,
    OnScrollIndex = 6,
    OnNavigatorClick = 7,
    ListScroll = 8,
    ListScrollIndex = 9,
    ListScrollStart = 10,
    ListScrollStop = 11,
    OnWebLoadIntercept = 12,
    OnToggleChange = 13,
    OnTextInputEditChange = 14,
    OnTextInputSubmit = 15,
    OnTextInputChange = 16,
    OnSliderChange = 17,
    SwiperAnimationStart = 18,
    SwiperAnimationEnd = 19,
    SwiperGestureSwipe = 20,
    OnAreaChange = 21,
    OnHover = 22,
    OnBlur = 23,
    OnKeyEvent = 24,
    OnMouse = 25,
    CanvasReady = 26,
    OnImageComplete = 27,
    OnImageError = 28,
    RefreshStateChange = 29,
    OnRefreshing = 30,
    OnRadioChange = 31,
    GridScroll = 32,
    GridScrollStart = 33,
    GridScrollStop = 34,
    OnSideBarChange = 35,
    OnXComponentLoad = 36,
    OnXComponentDestroy = 37,
};

enum ArkUIAPIGestureAsyncEventSubKind {
    OnAction = 0,
    OnActionStart = 1,
    OnActionUpdate = 2,
    OnActionEnd = 3,
    OnActionCancel = 4
};

union ArkUIAPIValue {
    Arkoala_Int32 i32;
    Arkoala_Int64 i64;
    Arkoala_Float32 f32;
    Arkoala_Float64 f64;
};

enum ArkUIAPIValueKind {
    ValueKind_Int32 = 0,
    ValueKind_Float32 = 1,
    ValueKind_Int64 = 2,
    ValueKind_Float64 = 3,
};

enum ArkUIAPIEventCallbackType { Void = 0, Int32 = 1, Float32 = 2, Int32Array = 3, Float32Array = 4 };

enum ArkUIAPINodeFlags {
    None = 0,
    CustomMeasure = 1 << 0,
    CustomLayout = 1 << 1,
    CustomDraw = 1 << 2,
};

enum ArkUIAPICustomOp { Measure = 1, Layout = 2, Draw = 3 };

enum ArkUIVMKind {
    VM_JS = 1,
    VM_STS = 2,
};

// Current implementation assumes that each argument is 4 bytes,
// fix decodeEvent() in TS if it will change.
union ArkUIAPIEventCallbackArg {
    Arkoala_Int32 i32;
    Arkoala_Uint32 u32;
    Arkoala_Float32 f32;
};

struct ArkUIAPIEventSinglePointer {
    Arkoala_Int32 x;
    Arkoala_Int32 y;
    Arkoala_Int32 state; // 0 - down, 1 - up, 2 - move
};

#define ARKUI_MULTIPOINTER_ARGS_COUNT 10

struct ArkUIAPIEventMultiPointer {
    Arkoala_Int32 count;
    Arkoala_Int32 xs[ARKUI_MULTIPOINTER_ARGS_COUNT];
    Arkoala_Int32 ys[ARKUI_MULTIPOINTER_ARGS_COUNT];
    Arkoala_Int32 state[ARKUI_MULTIPOINTER_ARGS_COUNT];
};

struct ArkUIAPIEventTextInput {
    Arkoala_Int32 nativeStringLow;
    Arkoala_Int32 nativeStringHigh;
};

#define ARKUI_CALLBACK_ARGS_COUNT 10

struct ArkUIAPIEventCallback {
    Arkoala_Int32 id;
    Arkoala_Int32 numArgs;
    Arkoala_Int32 continuationId;
    ArkUIAPIEventCallbackArg args[ARKUI_CALLBACK_ARGS_COUNT];
};

#define ARKUI_ASYNC_EVENT_ARGS_COUNT 12

struct ArkUIAPIEventComponentAsyncEvent {
    Arkoala_Int32 subKind;
    Arkoala_Int32 data[ARKUI_ASYNC_EVENT_ARGS_COUNT];
};

struct ArkUIAPIEventGestureAsyncEvent {
    Arkoala_Int32 subKind;
    Arkoala_Int32 repeat;
    Arkoala_Int32 x;
    Arkoala_Int32 y;
    Arkoala_Int32 angle;
    Arkoala_Int32 scale;
    Arkoala_Int32 pinchCenterX;
    Arkoala_Int32 pinchCenterY;
    Arkoala_Int32 speed;
    Arkoala_Int32 timestamp;
    Arkoala_Int32 source;
    Arkoala_Int32 pressure;
    Arkoala_Int32 tiltX;
    Arkoala_Int32 tiltY;
    Arkoala_Int32 sourceTool;
    Arkoala_Int32 velocityX;
    Arkoala_Int32 velocityY;
    Arkoala_Int32 velocity;
};

struct ArkUIAPIEvent {
    Arkoala_Int32 kind; // Actually ArkUINodeAPIEventKind, but use int for fixed
                        // binary layout.
    Arkoala_Int32 nodeId;
    union {
        ArkUIAPIEventSinglePointer singlePointer;
        ArkUIAPIEventMultiPointer multiPointer;
        ArkUIAPIEventCallback callback;
        ArkUIAPIEventComponentAsyncEvent componentAsyncEvent;
        ArkUIAPIEventTextInput textInputEvent;
        ArkUIAPIEventGestureAsyncEvent gestureAsyncEvent;
    };
};

struct ArkUIAPIAnimationSpec {
    Arkoala_Int32 duration;
    Arkoala_Int32 delay;
    Arkoala_Int32 valueKind; // of ArkUIAPIValueKind
    ArkUIAPIValue initial;
    ArkUIAPIValue target;
};

struct ArkUIAPICallbackMethod {
    Arkoala_Int32 (*CallInt)(
        ArkUIVMContext vmContext, Arkoala_Int32 methodId, Arkoala_Int32 numArgs, ArkUIAPIEventCallbackArg* args);
};

struct ArkUIBorderOptions {
    Arkoala_Float32* widthValues;
    Arkoala_Int32* widthUnits;
    Arkoala_Int32* colors;
    Arkoala_Float32* radiusValues;
    Arkoala_Int32* radiusUnits;
    Arkoala_Int32* styles;
};

struct ArkUICommonModifierAPI {
    void (*setWidth)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*resetWidth)(ArkUINodeHandle node);

    void (*setHeight)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*resetHeight)(ArkUINodeHandle node);

    void (*setOpacity)(ArkUINodeHandle node, Arkoala_Float32 value);
    void (*resetOpacity)(ArkUINodeHandle node);

    void (*setLinearGradient)(ArkUINodeHandle node, Arkoala_Float32 angle, Arkoala_Int32 direction, Arkoala_Bool repeat,
        const Arkoala_Int32* colors, const Arkoala_Float32* positions);
    void (*resetLinearGradient)(ArkUINodeHandle node);

    void (*setPadding)(ArkUINodeHandle node, const Arkoala_Float32* values, const Arkoala_Int32* units);
    void (*resetPadding)(ArkUINodeHandle node);

    void (*setMargin)(ArkUINodeHandle node, const Arkoala_Float32* values, const Arkoala_Int32* units);
    void (*resetMargin)(ArkUINodeHandle node);

    void (*setBorderRadius)(ArkUINodeHandle node, const Arkoala_Float32* values, const Arkoala_Int32* units);
    void (*resetBorderRadius)(ArkUINodeHandle node);

    void (*setBorderColor)(ArkUINodeHandle node, const Arkoala_Int32* colors, Arkoala_Int32 length);
    void (*resetBorderColor)(ArkUINodeHandle node);

    void (*setZIndex)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*resetZIndex)(ArkUINodeHandle node);

    void (*setVisibility)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*resetVisibility)(ArkUINodeHandle node);

    void (*setBackgroundColor)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*resetBackgroundColor)(ArkUINodeHandle node);

    void (*setBorder)(ArkUINodeHandle node, ArkUIBorderOptions* options);
    void (*resetBorder)(ArkUINodeHandle node);

    void (*setClip)(ArkUINodeHandle node, Arkoala_Bool clip);
    void (*resetClip)(ArkUINodeHandle node);

    void (*setBackgroundImage)(ArkUINodeHandle node, Arkoala_CharPtr src, Arkoala_Int32 repeat);
    void (*setBackgroundImageResource)(ArkUINodeHandle node, Arkoala_Int32 id, Arkoala_Int32 type, Arkoala_CharPtr name,
        Arkoala_CharPtr bundleName, Arkoala_CharPtr moduleName, Arkoala_Int32 repeat);
    void (*resetBackgroundImage)(ArkUINodeHandle node);

    void (*setBackgroundImageSize)(ArkUINodeHandle node, Arkoala_Bool flag, const Arkoala_Float32* values);
    void (*resetBackgroundImageSize)(ArkUINodeHandle node);

    /**
     * notify the node to send async appear event back
     */
    void (*notifyComponentAsyncEvent)(ArkUINodeHandle nodePtr, Arkoala_Int32 subKind);
    void (*notifyResetComponentAsyncEvent)(ArkUINodeHandle nodePtr, Arkoala_Int32 subKind);

    void (*setScaleOptions)(ArkUINodeHandle node, Arkoala_Float32* values, Arkoala_Int32 length);
    void (*setTranslateOptions)(ArkUINodeHandle node, Arkoala_Float32* values, Arkoala_Int32 length);
    void (*setRotateOptions)(ArkUINodeHandle node, Arkoala_Float32* values, Arkoala_Int32 length);
    void (*setTransform)(ArkUINodeHandle node, Arkoala_Float32* matrix, Arkoala_Int32 length);
    void (*setVisibleAreaChangeRatios)(ArkUINodeHandle node, Arkoala_Float32* values, Arkoala_Int32 length);

    void (*setAlign)(ArkUINodeHandle node, Arkoala_Int32 value);

    void (*setAspectRatio)(ArkUINodeHandle node, Arkoala_Float32 value);
    void (*setTransition)(ArkUINodeHandle node, Arkoala_Int32 type, Arkoala_Float32 opacity, Arkoala_Float32* translate,
        Arkoala_Float32* scale, Arkoala_Float32* rotate);
    void (*setChainedTransition)(ArkUINodeHandle node, Arkoala_Float32* appearPtr, Arkoala_Float32* disappearPtr,
        Arkoala_Int32 appearLen, Arkoala_Int32 disappearLen);
    void (*setHitTestBehavior)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setFlexGrow)(ArkUINodeHandle node, Arkoala_Float32 value);
    void (*setFlexShrink)(ArkUINodeHandle node, Arkoala_Float32 value);
    void (*setPosition)(ArkUINodeHandle node, Arkoala_Float32* values, Arkoala_Int32 length);
    void (*setMarkAnchor)(ArkUINodeHandle node, Arkoala_Float32* values, Arkoala_Int32 length);
    void (*setOffset)(ArkUINodeHandle node, Arkoala_Float32* values, Arkoala_Int32 length);
    void (*setEnabled)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*setShadow)(ArkUINodeHandle node, Arkoala_Float32 radius, Arkoala_Int32 color, Arkoala_Float32 offsetX,
        Arkoala_Float32 offsetY);
    void (*setLayoutWeight)(ArkUINodeHandle node, Arkoala_Float32 layoutValue);
    void (*setFocusable)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*setGeometryTransition)(ArkUINodeHandle node, Arkoala_CharPtr value);
    void (*setDraggable)(ArkUINodeHandle node, Arkoala_Bool flag);
    void (*setKey)(ArkUINodeHandle node, Arkoala_CharPtr value);
    void (*setId)(ArkUINodeHandle node, Arkoala_CharPtr value);

    void (*setResponseRegion)(ArkUINodeHandle node, Arkoala_Float32* rectangles, Arkoala_Int32 length);
    void (*resetResponseRegion)(ArkUINodeHandle node);
    void (*setConstraintSize)(ArkUINodeHandle node, Arkoala_Int32 minWValue, Arkoala_Int32 minWUnit,
        Arkoala_Int32 minHValue, Arkoala_Int32 minHUnit, Arkoala_Int32 maxWValue, Arkoala_Int32 maxWUnit,
        Arkoala_Int32 maxHValue, Arkoala_Int32 maxHUnit);
    void (*setGridSpan)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setGridOffset)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setHoverEffect)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setSizeType)(ArkUINodeHandle node, Arkoala_Int32 type, Arkoala_Int32 span, Arkoala_Int32 offset);
    void (*setSizeTypeNumber)(ArkUINodeHandle node, Arkoala_Int32 type, Arkoala_Int32 value);
    void (*setDefaultFocus)(ArkUINodeHandle node, Arkoala_Bool flag);
    void (*setBackgroundImagePosition)(ArkUINodeHandle node, Arkoala_Float32* values, Arkoala_Int32 length);
    void (*setBackgroundBlurStyle)(ArkUINodeHandle node, Arkoala_Int32 value, Arkoala_Int32 colorMode,
        Arkoala_Int32 adaptiveColor, Arkoala_Float32 scale);
    void (*setForegroundBlurStyle)(ArkUINodeHandle node, Arkoala_Int32 value, Arkoala_Int32 colorMode,
        Arkoala_Int32 adaptiveColor, Arkoala_Float32 scale);
};

struct ArkUIShapedCommonModifierAPI {
    void (*setFill)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setStroke)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setFillOpacity)(ArkUINodeHandle node, Arkoala_Float32 value);
    void (*setStrokeOpacity)(ArkUINodeHandle node, Arkoala_Float32 value);
    void (*setStrokeWidth)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setStrokeDashArray)(ArkUINodeHandle node, Arkoala_Float32* value, Arkoala_Int32* unit,
        Arkoala_Int32 valueLength, Arkoala_Int32 unitLength);
    void (*setAntiAlias)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*setStrokeDashOffset)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setStrokeMiterLimit)(ArkUINodeHandle node, Arkoala_Float32 value);
    void (*setStrokeLineCap)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setStrokeLineJoin)(ArkUINodeHandle node, Arkoala_Int32 value);
};
struct ArkUILineModifierAPI {
    void (*setStartPoint)(
        ArkUINodeHandle node, Arkoala_Float32 xValue, Arkoala_Int32 xUnit, Arkoala_Float32 yValue, Arkoala_Int32 yUnit);
    void (*setEndPoint)(
        ArkUINodeHandle node, Arkoala_Float32 xValue, Arkoala_Int32 xUnit, Arkoala_Float32 yValue, Arkoala_Int32 yUnit);
};

struct ArkUIPathModifierAPI {
    void (*setPathCommands)(ArkUINodeHandle node, Arkoala_CharPtr commands);
};

struct ArkUIPolygonModifierAPI {
    void (*setPoints)(ArkUINodeHandle node, Arkoala_Float32* points, Arkoala_Int32 length, Arkoala_Bool isPolygon);
};

struct ArkUIRectModifierAPI {
    void (*setRadiusWidth)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setRadiusHeight)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setRadius)(ArkUINodeHandle node, Arkoala_Float32* points, Arkoala_Int32 length);
};

struct ArkUIShapeModifierAPI {
    void (*setViewPort)(ArkUINodeHandle node, Arkoala_Float32* ports, Arkoala_Int32 length);
    void (*setMesh)(ArkUINodeHandle node, Arkoala_Float32* meshPoints, Arkoala_Int32 length, Arkoala_Int32 column,
        Arkoala_Int32 row);
};
struct ArkUITextModifierAPI {
    void (*setTextLabel)(ArkUINodeHandle node, Arkoala_CharPtr label);
    void (*resetTextLabel)(ArkUINodeHandle node);

    void (*setTextBaselineOffset)(ArkUINodeHandle nodePtr, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*resetTextBaselineOffset)(ArkUINodeHandle nodePtr);

    void (*setTextOverflow)(ArkUINodeHandle nodePtr, Arkoala_Int32 value);
    void (*resetTextOverflow)(ArkUINodeHandle nodePtr);

    void (*setTextFontSize)(ArkUINodeHandle nodePtr, Arkoala_Float32 number, Arkoala_Int32 unit);
    void (*resetTextFontSize)(ArkUINodeHandle nodePtr);

    void (*setTextMinFontSize)(ArkUINodeHandle nodePtr, Arkoala_Float32 number, Arkoala_Int32 unit);
    void (*resetTextMinFontSize)(ArkUINodeHandle nodePtr);

    void (*setTextMaxFontSize)(ArkUINodeHandle nodePtr, Arkoala_Float32 number, Arkoala_Int32 unit);
    void (*resetTextMaxFontSize)(ArkUINodeHandle nodePtr);

    void (*setTextFontColor)(ArkUINodeHandle nodePtr, Arkoala_Int32 color);
    void (*resetTextFontColor)(ArkUINodeHandle nodePtr);

    void (*setTextFontWeight)(ArkUINodeHandle nodePtr, Arkoala_Int32 value);
    void (*resetTextFontWeight)(ArkUINodeHandle nodePtr);

    void (*setTextLineHeight)(ArkUINodeHandle nodePtr, Arkoala_Float32 number, Arkoala_Int32 unit);
    void (*resetTextLineHeight)(ArkUINodeHandle nodePtr);

    void (*setTextAlign)(ArkUINodeHandle nodePtr, Arkoala_Int32 value);
    void (*resetTextAlign)(ArkUINodeHandle nodePtr);

    void (*setTextMaxLines)(ArkUINodeHandle nodePtr, Arkoala_Int32 value);
    void (*resetTextMaxLines)(ArkUINodeHandle nodePtr);

    void (*setTextDraggable)(ArkUINodeHandle node, Arkoala_Bool value);

    void (*setFontFamily)(ArkUINodeHandle node, Arkoala_CharPtr value);
    void (*setHeightAdaptivePolicy)(ArkUINodeHandle nodePtr, Arkoala_Int32 value);
    void (*setTextLetterSpacing)(ArkUINodeHandle nodePtr, Arkoala_Float32 number, Arkoala_Int32 unit);
    void (*setTextCase)(ArkUINodeHandle nodePtr, Arkoala_Int32 value);
    void (*setTextIndent)(ArkUINodeHandle nodePtr, Arkoala_Float32 number, Arkoala_Int32 unit);
};

struct ArkUIButtonModifierAPI {
    void (*setButtonLabel)(ArkUINodeHandle node, Arkoala_CharPtr label);
    void (*resetButtonLabel)(ArkUINodeHandle node);
    void (*setButtonType)(ArkUINodeHandle node, Arkoala_Int32 type);
    void (*setButtonFontSize)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setButtonFontWeight)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setButtonFontFamily)(ArkUINodeHandle node, Arkoala_CharPtr value);
};

struct ArkUIImageModifierAPI {
    void (*setImageSrc)(ArkUINodeHandle node, Arkoala_CharPtr label);
    void (*resetImageSrc)(ArkUINodeHandle node);
    void (*setImageObjectFit)(ArkUINodeHandle node, Arkoala_Int32 label);
    void (*resetImageObjectFit)(ArkUINodeHandle node);
    void (*setImageAlt)(ArkUINodeHandle node, Arkoala_CharPtr src);
    void (*resetImageAlt)(ArkUINodeHandle node);
    void (*setImageObjectRepeat)(ArkUINodeHandle nodePtr, Arkoala_Int32 value);
    void (*resetImageObjectRepeat)(ArkUINodeHandle nodePtr);
    void (*setImageResource)(ArkUINodeHandle node, Arkoala_Int32 id, Arkoala_Int32 type, Arkoala_CharPtr name,
        Arkoala_CharPtr bundleName, Arkoala_CharPtr moduleName);
    void (*setImageAltResource)(ArkUINodeHandle node, Arkoala_Int32 id, Arkoala_Int32 type, Arkoala_CharPtr name,
        Arkoala_CharPtr bundleName, Arkoala_CharPtr moduleName);
    void (*setImageAutoResize)(ArkUINodeHandle node, Arkoala_Bool flag);
    void (*setImageFillColor)(ArkUINodeHandle node, Arkoala_Int32 color);
};

struct ArkUIColumnModifierAPI {
    void (*setColumnOptions)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*resetColumnOptions)(ArkUINodeHandle node);
    void (*setColumnAlignItems)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*resetColumnAlignItems)(ArkUINodeHandle node);
    void (*setColumnJustifyContent)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*resetColumnJustifyContent)(ArkUINodeHandle node);
};

struct ArkUIRowModifierAPI {
    void (*setRowOptions)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*resetRowOptions)(ArkUINodeHandle node);
    void (*setRowAlignItems)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*resetRowAlignItems)(ArkUINodeHandle node);
    void (*setRowJustifyContent)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*resetRowJustifyContent)(ArkUINodeHandle node);
};

struct ArkUIDividerModifierAPI {
    void (*setDividerVertical)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*resetDividerVertical)(ArkUINodeHandle node);
    void (*setDividerColor)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*resetDividerColor)(ArkUINodeHandle node);
    void (*setDividerStrokeWidth)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*resetDividerStrokeWidth)(ArkUINodeHandle node);
    void (*setDividerLineCap)(ArkUINodeHandle node, Arkoala_Int32 value);
};

struct ArkUIFlexModifierAPI {
    void (*setFlexOptions)(ArkUINodeHandle node, Arkoala_Int32* options, Arkoala_Int32 length);
};

struct ArkUIListModifierAPI {
    void (*setListScrollBar)(ArkUINodeHandle node, Arkoala_Int32 bar);
    void (*resetListScrollBar)(ArkUINodeHandle node);
    void (*setListOptions)(ArkUINodeHandle node, Arkoala_Float32 space, Arkoala_Int32 unit, Arkoala_Int32 initialIndex);
    void (*resetListOptions)(ArkUINodeHandle node);
    void (*setListDirection)(ArkUINodeHandle node, Arkoala_Int32 direction);
    void (*resetListDirection)(ArkUINodeHandle node);
    void (*setListAlignListItem)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setListScrollSnapAlign)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setListDivider)(ArkUINodeHandle node, Arkoala_Float32* strokeWidth, Arkoala_Int32 color,
        Arkoala_Float32* startMargin, Arkoala_Float32* endMargin);
    void (*setListEdgeEffect)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setListSticky)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setChainAnimationOptions)(ArkUINodeHandle node, Arkoala_Float32* option, Arkoala_Int32 effect);
};

struct ArkUIListItemGroupModifierAPI {
    void (*setListItemGroupDivider)(ArkUINodeHandle node, Arkoala_Float32* strokeWidth, Arkoala_Int32 color,
        Arkoala_Float32* startMargin, Arkoala_Float32* endMargin);
    void (*setListItemGroupStyle)(ArkUINodeHandle node, Arkoala_Int32 style);
};

struct ArkUISwiperModifierAPI {
    void (*setAutoPlay)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*setShowIndicator)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*setInterval)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setLoop)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*setVertical)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*setSwiperCurve)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*resetSwiperCurve)(ArkUINodeHandle node);
    void (*setSwiperItemSpace)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*resetSwiperItemSpace)(ArkUINodeHandle node);
    void (*setIndicatorStyle)(
        ArkUINodeHandle node, Arkoala_Float32* values, Arkoala_Int32* units, Arkoala_Bool mask, Arkoala_Int32* colors);
    void (*setSwiperIndex)(ArkUINodeHandle node, Arkoala_Int32 index);
    void (*setSwiperDuration)(ArkUINodeHandle node, Arkoala_Int32 index);
    void (*setCachedCount)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setDisableSwipe)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*setSwiperEffectMode)(ArkUINodeHandle node, Arkoala_Int32 value);
};

struct ArkUISwiperControllerModifierAPI {
    ArkUINodeHandle (*getSwiperController)(ArkUINodeHandle node);
    void (*setShowNext)(ArkUINodeHandle node);
    void (*setShowPrevious)(ArkUINodeHandle node);
};

struct ArkUIStackModifierAPI {
    void (*setStackContentAlign)(ArkUINodeHandle node, Arkoala_Int32 alignment);
    void (*resetStackContentAlign)(ArkUINodeHandle node);
};
struct ArkUINavigatorModifierAPI {
    // navigator
    void (*setNavigatorType)(ArkUINodeHandle node, Arkoala_Int32 type);
    void (*resetNavigatorType)(ArkUINodeHandle node);

    void (*setNavigatorTarget)(ArkUINodeHandle node, Arkoala_CharPtr target);
    void (*resetNavigatorTarget)(ArkUINodeHandle node);
};
struct ArkUIVideoModifierAPI {
    // video
    void (*setVideoAutoPlay)(ArkUINodeHandle node, Arkoala_Bool autoPlay);
    void (*resetVideoAutoPlay)(ArkUINodeHandle node);

    void (*setVideoControls)(ArkUINodeHandle node, Arkoala_Bool controls);
    void (*resetVideoControls)(ArkUINodeHandle node);

    void (*setVideoObjectFit)(ArkUINodeHandle node, Arkoala_Int32 objectFit);
    void (*resetVideoObjectFit)(ArkUINodeHandle node);

    void (*setVideoLoop)(ArkUINodeHandle node, Arkoala_Bool loop);
    void (*resetVideoLoop)(ArkUINodeHandle node);

    void (*setVideoMute)(ArkUINodeHandle node, Arkoala_Bool mute);
    void (*resetVideoMute)(ArkUINodeHandle node);

    void (*setVideoOptions)(ArkUINodeHandle node, Arkoala_CharPtr src);
    void (*resetVideoOptions)(ArkUINodeHandle node);
    void (*setVideoSrcResource)(ArkUINodeHandle node, Arkoala_Int32 id, Arkoala_Int32 type, Arkoala_CharPtr name,
        Arkoala_CharPtr bundleName, Arkoala_CharPtr moduleName);
};

struct ArkUIVideoControllerModifierAPI {
    ArkUINodeHandle (*getVideoController)(ArkUINodeHandle node);
    void (*setVideoStart)(ArkUINodeHandle node);
    void (*setVideoStop)(ArkUINodeHandle node);
    void (*setVideoPause)(ArkUINodeHandle node);
};

struct ArkUIGridModifierAPI {
    void (*setGridColumnsTemplate)(ArkUINodeHandle node, Arkoala_CharPtr temp);
    void (*resetGridColumnsTemplate)(ArkUINodeHandle node);
    void (*setGridColumnsGap)(ArkUINodeHandle node, Arkoala_Float32 gap, Arkoala_Int32 unit);
    void (*resetGridColumnsGap)(ArkUINodeHandle node);
    void (*setGridRowsGap)(ArkUINodeHandle node, Arkoala_Float32 gap, Arkoala_Int32 unit);
    void (*resetGridRowsGap)(ArkUINodeHandle node);
    void (*setGridScrollBar)(ArkUINodeHandle node, Arkoala_Int32 bar);
    void (*resetGridScrollBar)(ArkUINodeHandle node);
    void (*setGridRowsTemplate)(ArkUINodeHandle node, Arkoala_CharPtr temp);
    void (*resetGridRowsTemplate)(ArkUINodeHandle node);
    void (*setGridCachedCount)(ArkUINodeHandle node, Arkoala_Int32 value);
};

struct ArkUIGridItemModifierAPI {
    void (*setGridItemColumnStart)(ArkUINodeHandle node, Arkoala_Int32 start);
    void (*resetGridItemColumnStart)(ArkUINodeHandle node);
    void (*setGridItemColumnEnd)(ArkUINodeHandle node, Arkoala_Int32 end);
    void (*resetGridItemColumnEnd)(ArkUINodeHandle node);
};

struct ArkUIScrollModifierAPI {
    void (*setScrollScrollBar)(ArkUINodeHandle node, Arkoala_Int32 state);
    void (*resetScrollScrollBar)(ArkUINodeHandle node);
};

struct ArkUIScrollBarModifierAPI {
    void (*setScrollBarDirection)(ArkUINodeHandle node, Arkoala_Int32 direction);
    void (*resetScrollBarDirection)(ArkUINodeHandle node);
    void (*setScrollBarState)(ArkUINodeHandle node, Arkoala_Int32 state);
    void (*resetScrollBarState)(ArkUINodeHandle node);
    void (*setScrollBarScroller)(ArkUINodeHandle node, ArkUINodeHandle controller);
};

struct ArkUIScrollerModifierAPI {
    ArkUINodeHandle (*getScroller)(ArkUINodeHandle node, ArkUINodeHandle proxy);
    ArkUINodeHandle (*getScrollerProxy)(ArkUINodeHandle node);
    void (*setScrollToIndex)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*scrollBy)(ArkUINodeHandle node, Arkoala_Float32* values, Arkoala_Int32* units);
    void (*getCurrentOffset)(ArkUINodeHandle controlle, Arkoala_Float32* out);
};

struct ArkUITabsModifierAPI {
    void (*setTabsBarPosition)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setTabsVertical)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*setTabsScrollable)(ArkUINodeHandle node, Arkoala_Bool value);
};

struct ArkUITabContentModifierAPI {
    void (*setTabContentBuilder)(ArkUINodeHandle node, Arkoala_Int32 methodId);
    void (*setTabContentLabel)(ArkUINodeHandle node, Arkoala_CharPtr label);
};

struct ArkUITabsControllerModifierAPI {
    ArkUINodeHandle (*getTabsController)(ArkUINodeHandle node);
};

struct ArkUIGestureModifierAPI {
    void (*tapGestureAsyncEvent)(ArkUINodeHandle nodePtr, Arkoala_Int32 mask, Arkoala_Int32 priority,
        Arkoala_Int32 count, Arkoala_Int32 fingers);
    void (*longPressGestureAsyncEvent)(ArkUINodeHandle nodePtr, Arkoala_Int32 mask, Arkoala_Int32 priority,
        Arkoala_Int32 fingers, Arkoala_Int32 repeat, Arkoala_Int32 duration, Arkoala_Int32* event);
    void (*panGestureAsyncEvent)(ArkUINodeHandle nodePtr, Arkoala_Int32 mask, Arkoala_Int32 priority,
        Arkoala_Int32 fingers, Arkoala_Int32 direction, Arkoala_Int32 distance, Arkoala_Int32* event);
    void (*pinchGestureAsyncEvent)(ArkUINodeHandle nodePtr, Arkoala_Int32 mask, Arkoala_Int32 priority,
        Arkoala_Int32 fingers, Arkoala_Int32 distance, Arkoala_Int32* event);
    void (*groupGestureAsyncEvent)(ArkUINodeHandle nodePtr, Arkoala_Int32 mode, Arkoala_Int32* event);
    void (*notifyResetGestureAsyncEvent)(ArkUINodeHandle nodePtr, Arkoala_Int32 subKind);
};

struct ArkUISliderModifierAPI {
    void (*setSliderOptionValue)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setSliderOptionValueMin)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setSliderOptionValueMax)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setSliderOptionStep)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setSliderOptionStyle)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setSliderOptionDirection)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setSliderOptionReverse)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*setSliderShowSteps)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*setBlockColor)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setTrackColor)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setSelectedColor)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setTrackThickness)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setSliderBlockSize)(ArkUINodeHandle node, Arkoala_Float32* value);
};

struct ArkUIProgressModifierAPI {
    void (*setProgressValue)(ArkUINodeHandle node, Arkoala_Float32 value);
    void (*setProgressColor)(
        ArkUINodeHandle node, Arkoala_Int32* colors, Arkoala_Float32* offsets, Arkoala_Int32 length);
    void (*setProgressInit)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Float32 total, Arkoala_Int32 type);
    void (*setProgressStyleOptions)(ArkUINodeHandle node, Arkoala_Float32* value);
    void (*setCapsuleStyleOptions)(
        ArkUINodeHandle node, Arkoala_Float32* value, Arkoala_CharPtr content, Arkoala_CharPtr fontFamily);
    void (*setRingStyleOptions)(ArkUINodeHandle node, Arkoala_Float32* value);
    void (*setLinearStyleOptions)(ArkUINodeHandle node, Arkoala_Float32* value);
    void (*setEclipseStyleOptions)(ArkUINodeHandle node, Arkoala_Bool value);
};

struct ArkUINavDestinationModifierAPI {
    void (*setHideTitleBar)(ArkUINodeHandle node, Arkoala_Bool value);
};

struct ArkUITextAreaModifierAPI {
    void (*setTextAreaFontColor)(ArkUINodeHandle node, Arkoala_Int32 color);
    void (*setTextAreaFontSize)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setTextAreaMaxLength)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setTextAreaShowCounter)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*setTextAreaTextAlign)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setTextAreaMaxLines)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setTextAreaPlaceholder)(ArkUINodeHandle node, Arkoala_CharPtr value);
    void (*setTextAreaText)(ArkUINodeHandle node, Arkoala_CharPtr value);
};

struct ArkUITextInputModifierAPI {
    ArkUINodeHandle (*getTextInputController)(ArkUINodeHandle node);
    void (*setTextInputPlaceholderString)(ArkUINodeHandle node, Arkoala_CharPtr value);
    void (*setTextInputPlaceholderResource)(ArkUINodeHandle node, Arkoala_Int32 id, Arkoala_Int32 type,
        Arkoala_CharPtr name, Arkoala_CharPtr bundleName, Arkoala_CharPtr moduleName);
    void (*setTextInputTextString)(ArkUINodeHandle node, Arkoala_CharPtr value);
    void (*setTextInputTextResource)(ArkUINodeHandle node, Arkoala_Int32 id, Arkoala_Int32 type, Arkoala_CharPtr name,
        Arkoala_CharPtr bundleName, Arkoala_CharPtr moduleName);
    void (*setTextInputFontSize)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 units);
    void (*setTextInputFontWeight)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setTextInputAlignment)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setTextInputMaxLines)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setTextInputFontColor)(ArkUINodeHandle node, Arkoala_Int32 color);
    void (*setTextInputFontFamily)(ArkUINodeHandle node, Arkoala_CharPtr value);
};

struct ArkUIWebModifierAPI {
    ArkUINodeHandle (*getWebController)(ArkUINodeHandle node);
    ArkUINodeHandle (*getWebviewController)(ArkUINodeHandle node);
    void (*setWebOptions)(ArkUINodeHandle node, Arkoala_CharPtr value);
    void (*setWebSrcResources)(ArkUINodeHandle node, Arkoala_Int32 id, Arkoala_Int32 type, Arkoala_CharPtr name,
        Arkoala_CharPtr bundleName, Arkoala_CharPtr moduleName);
    void (*setWebMixedMode)(ArkUINodeHandle node, Arkoala_Int32 value);
};

struct ArkUIBlankModifierAPI {};

struct ArkUICheckboxModifierAPI {
    void (*setCheckboxSelect)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*setCheckboxMark)(ArkUINodeHandle node, Arkoala_Int32 color, Arkoala_Float32 sizeValue,
        Arkoala_Int32 sizeUnit, Arkoala_Float32 strokeWidthValue, Arkoala_Int32 strokeWidthUnit);
    void (*setCheckboxSelectedColor)(ArkUINodeHandle node, Arkoala_Int32 color);
    void (*setCheckboxUnselectedColor)(ArkUINodeHandle node, Arkoala_Int32 color);
    void (*setCheckboxName)(ArkUINodeHandle node, Arkoala_CharPtr value);
    void (*setCheckboxGroup)(ArkUINodeHandle node, Arkoala_CharPtr value);
};

struct ArkUICheckboxGroupModifierAPI {
    void (*setCheckboxGroupSelectAll)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*setCheckboxGroupName)(ArkUINodeHandle node, Arkoala_CharPtr value);
};

struct ArkUIMenuModifierAPI {
    void (*setMenuFontColor)(ArkUINodeHandle node, int color);
    void (*setMenuFontSize)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setMenuFont)(ArkUINodeHandle node, Arkoala_Float32* fontSize, Arkoala_Int32 fontWeight,
        Arkoala_Int32 fontStyle, Arkoala_CharPtr fontFamily);
};

struct ArkUIMenuItemModifierAPI {
    void (*setMenuItemContent)(ArkUINodeHandle node, const char* value);
    void (*setMenuItemContentFont)(ArkUINodeHandle node, Arkoala_Float32* fontSize, Arkoala_Int32 fontWeight,
        Arkoala_Int32 fontStyle, Arkoala_CharPtr fontFamily);
    void (*setMenuItemContentFontColor)(ArkUINodeHandle node, Arkoala_Int32 color);
    void (*setMenuItemLabelFont)(ArkUINodeHandle node, Arkoala_Float32* fontSize, Arkoala_Int32 fontWeight,
        Arkoala_Int32 fontStyle, Arkoala_CharPtr fontFamily);
    void (*setMenuItemLabelFontColor)(ArkUINodeHandle node, Arkoala_Int32 color);
    void (*setMenuItemLabelInfo)(ArkUINodeHandle node, Arkoala_CharPtr value);
};

struct ArkUIMenuItemGroupModifierAPI {
    void (*setMenuItemGroupHeader)(ArkUINodeHandle node, Arkoala_CharPtr value);
    void (*setMenuItemGroupFooter)(ArkUINodeHandle node, Arkoala_CharPtr value);
};

struct ArkUIToggleModifierAPI {
    void (*setToggleOptions)(ArkUINodeHandle node, Arkoala_Int32 type, Arkoala_Bool isOn);
    void (*setToggleSelectedColor)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setSwitchPointColor)(ArkUINodeHandle node, Arkoala_Int32 value);
};

struct ArkUINavigationModifierAPI {
    void (*setHideBackButton)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*setHideNavBar)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*setHideNavigationTitleBar)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*setHideToolBar)(ArkUINodeHandle node, Arkoala_Bool value);

    void (*setNavigationMode)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setNavBarPosition)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setNavBarWidth)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setTitleMode)(ArkUINodeHandle node, Arkoala_Int32 value);
};

struct ArkUIGaugeModifierAPI {
    void (*setGaugeStrokeWidth)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setGaugeStartAngle)(ArkUINodeHandle node, Arkoala_Float32 value);
    void (*setGaugeValue)(ArkUINodeHandle node, Arkoala_Float32 value);
};

struct ArkUIBadgeModifierAPI {
    void (*setBadgeParameters)(ArkUINodeHandle node, Arkoala_Int32* intValue, Arkoala_Float32* floatValue);
    void (*setBadgeValue)(ArkUINodeHandle node, Arkoala_CharPtr value);
    void (*setBadgeCount)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setBadgeMaxCount)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setBadgeFontWeight)(ArkUINodeHandle node, Arkoala_Int32 value);
};

struct ArkUIRefreshModifierAPI {
    void (*setRefreshFriction)(ArkUINodeHandle node, Arkoala_Int32 value);
};

struct ArkUIHyperlinkModifierAPI {
    void (*setHyperlinkAddress)(ArkUINodeHandle node, Arkoala_CharPtr value);
    void (*setHyperlinkContent)(ArkUINodeHandle node, Arkoala_CharPtr value);
};

struct ArkUIAlphabetIndexerModifierAPI {
    void (*selectIndexerColor)(ArkUINodeHandle node, Arkoala_Int32 color);
    void (*setIndexerPopupColor)(ArkUINodeHandle node, Arkoala_Int32 color);
    void (*selectIndexerBackgroundColor)(ArkUINodeHandle node, Arkoala_Int32 color);
    void (*setIndexerPopupBackground)(ArkUINodeHandle node, Arkoala_Int32 color);
    void (*selectIndexerFont)(ArkUINodeHandle node, Arkoala_Float32* fontSize, Arkoala_Int32 fontWeight,
        Arkoala_Int32 fontStyle, Arkoala_CharPtr fontFamily);
    void (*setIndexerPopupFont)(ArkUINodeHandle node, Arkoala_Float32* fontSize, Arkoala_Int32 fontWeight,
        Arkoala_Int32 fontStyle, Arkoala_CharPtr fontFamily);
    void (*setAlphabetIndexerInit)(
        ArkUINodeHandle node, Arkoala_CharPtr* array, Arkoala_Int32 selected, Arkoala_Int32 length);
};

struct ArkUILoadingProgressModifierAPI {
    void (*setLoadingProgressColor)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setLoadingProgressEnableLoading)(ArkUINodeHandle node, Arkoala_Bool value);
};

struct ArkUIImageAnimatorModifierAPI {
    void (*setImageAnimatorImages)(ArkUINodeHandle node, Arkoala_CharPtr* src, Arkoala_Int32 srcLength,
        Arkoala_Float32* info, Arkoala_Int32 length);

    void (*setImageAnimatorDuration)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setImageAnimatorFillMode)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setImageAnimatorFixedSize)(ArkUINodeHandle node, Arkoala_Bool value);

    void (*setImageAnimatorIteration)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setImageAnimatorIsReverse)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*setImageAnimatorState)(ArkUINodeHandle node, Arkoala_Int32 value);
};

struct ArkUIRatingModifierAPI {
    void (*setRatingValue)(ArkUINodeHandle node, Arkoala_Float32 ratingScore, Arkoala_Bool indicator);
    void (*setRatingStars)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setRatingStarStyle)(ArkUINodeHandle node, Arkoala_CharPtr backgroundUri, Arkoala_CharPtr foregroundUri,
        Arkoala_CharPtr secondaryUri);
};

struct ArkUISearchModifierAPI {
    void (*setSearchValue)(
        ArkUINodeHandle node, Arkoala_CharPtr value, Arkoala_CharPtr placeholder, Arkoala_CharPtr icon);
    void (*setSearchPlaceholderFont)(ArkUINodeHandle node, Arkoala_Float32* fontSize, Arkoala_Int32 fontWeight,
        Arkoala_Int32 fontStyle, Arkoala_CharPtr fontFamily);
    void (*setSearchTextAlign)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setSearchTextFont)(ArkUINodeHandle node, Arkoala_Float32* fontSize, Arkoala_Int32 fontWeight,
        Arkoala_Int32 fontStyle, Arkoala_CharPtr fontFamily);
};

struct ArkUISearchControllerModifierAPI {
    ArkUINodeHandle (*getSearchController)(ArkUINodeHandle node);
    void (*setSearchCaretPosition)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setSearchStopEditing)(ArkUINodeHandle node);
};

struct ArkUITextClockModifierAPI {
    void (*setTextClockFormat)(ArkUINodeHandle node, Arkoala_CharPtr value);
    void (*setTimeZoneOffset)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setTextClockFontColor)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setTextClockFontSize)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setTextClockFontStyle)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setTextClockFontWeight)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setTextClockFontFamily)(ArkUINodeHandle node, Arkoala_CharPtr value);
};

struct ArkUITextClockControllerModifierAPI {
    ArkUINodeHandle (*getTextClockController)(ArkUINodeHandle node);
    void (*setTextClockStart)(ArkUINodeHandle node);
    void (*setTextClockStop)(ArkUINodeHandle node);
};

struct ArkUITextPickerModifierAPI {
    void (*setDisappearTextStyle)(ArkUINodeHandle node, Arkoala_Int32 color, Arkoala_Float32* fontSize,
        Arkoala_Int32 fontWeight, Arkoala_Int32 fontStyle, Arkoala_CharPtr fontFamily);
    void (*setTextPickerTextStyle)(ArkUINodeHandle node, Arkoala_Int32 color, Arkoala_Float32* fontSize,
        Arkoala_Int32 fontWeight, Arkoala_Int32 fontStyle, Arkoala_CharPtr fontFamily);
    void (*setSelectedTextStyle)(ArkUINodeHandle node, Arkoala_Int32 color, Arkoala_Float32* fontSize,
        Arkoala_Int32 fontWeight, Arkoala_Int32 fontStyle, Arkoala_CharPtr fontFamily);
    void (*setTextPickerRange)(
        ArkUINodeHandle node, Arkoala_CharPtr* iconArray, Arkoala_CharPtr* textArray, Arkoala_Int32 length);
    void (*setTextPickerSelected)(ArkUINodeHandle node, Arkoala_Int32* selected, Arkoala_Int32 length);
    void (*setTextPickerValue)(ArkUINodeHandle node, Arkoala_CharPtr* values, Arkoala_Int32 length);
};

struct ArkUITextTimerModifierAPI {
    void (*setTextTimerFormat)(ArkUINodeHandle node, Arkoala_CharPtr value);
    void (*setTextTimerOptions)(ArkUINodeHandle node, Arkoala_Bool isCountDown, Arkoala_Int32 count);
    void (*setTextTimerFontColor)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setTextTimerFontSize)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setTextTimerFontStyle)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setTextTimerFontWeight)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setTextTimerFontFamily)(ArkUINodeHandle node, Arkoala_CharPtr value);
};

struct ArkUITextTimerControllerModifierAPI {
    ArkUINodeHandle (*getTextTimerController)(ArkUINodeHandle node);
    void (*setTextTimerStart)(ArkUINodeHandle node);
    void (*setTextTimerPause)(ArkUINodeHandle node);
    void (*setTextTimerReset)(ArkUINodeHandle node);
};
struct ArkUIMarqueeModifierAPI {
    void (*setMarqueeValue)(ArkUINodeHandle node, Arkoala_CharPtr value, Arkoala_Bool playerStatus,
        Arkoala_Float32 scrollAmount, Arkoala_Int32 loop, Arkoala_Bool direction);
};

struct ArkUISpanModifierAPI {
    void (*setSpanFont)(ArkUINodeHandle node, Arkoala_Float32* fontSize, Arkoala_Int32 fontWeight,
        Arkoala_Int32 fontStyle, Arkoala_CharPtr fontFamily);
    void (*setSpanLetterSpacing)(ArkUINodeHandle node, Arkoala_Float32* space);
    void (*setSpanTextCase)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setSpanLabel)(ArkUINodeHandle node, Arkoala_CharPtr value);
};

struct ArkUISelectModifierAPI {
    void (*setSelectArrowPosition)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setSelectSpace)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setSelectParam)(ArkUINodeHandle node, Arkoala_CharPtr* array, Arkoala_Int32 length);
};

/** Common for all API variants.*/
struct ArkUIAnyAPI {
    Arkoala_Int32 version;
    void (*setCallbackMethod)(ArkUIAPICallbackMethod* method);
};

struct ArkUIGridColModifierAPI {
    void (*setGridColSpan)(ArkUINodeHandle node, const Arkoala_Int32* span, Arkoala_Int32 length);
    void (*setGridColOffset)(ArkUINodeHandle node, const Arkoala_Int32* offset, Arkoala_Int32 length);
    void (*setGridColOrder)(ArkUINodeHandle node, const Arkoala_Int32* order, Arkoala_Int32 length);
};

struct ArkUIGridRowModifierAPI {
    void (*setGridRowColumns)(ArkUINodeHandle node, const Arkoala_Int32* column, Arkoala_Int32 length);
    void (*setGridRowDirection)(ArkUINodeHandle node, const Arkoala_Int32 value);
    void (*setGridRowGutter)(ArkUINodeHandle node, const Arkoala_Float32* gutterValue, const Arkoala_Int32* gutterUnit,
        Arkoala_Int32 valueLength, Arkoala_Int32 unitLength);
    void (*setGridRowBreakpoints)(ArkUINodeHandle node, const Arkoala_Float32* Value, const Arkoala_Int32* unit,
        Arkoala_Int32 valueLength, Arkoala_Int32 unitLength, Arkoala_Int32 reference);
};

struct ArkUIRadioModifierAPI {
    void (*setRadioChecked)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*setRadioGroup)(ArkUINodeHandle node, Arkoala_CharPtr group, Arkoala_CharPtr value);
};

struct ArkUIPatternLockControllerModifierAPI {
    ArkUINodeHandle (*getPatternLockController)(ArkUINodeHandle node);
    void (*setPatternLockReset)(ArkUINodeHandle node);
};

struct ArkUIPatternLockModifierAPI {
    void (*setPatternLockSideLength)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setPatternLockCircleRadius)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setPatternLockSelectedColor)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setPatternLockRegularColor)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setPatternLockActiveColor)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setPatternLockPathColor)(ArkUINodeHandle node, Arkoala_Int32 value);
    void (*setPatternLockPathStrokeWidth)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setPatternLockAutoReset)(ArkUINodeHandle node, Arkoala_Bool value);
};
struct ArkUIRichEditorModifierAPI {};

struct ArkUIRichEditorControllerModifierAPI {
    ArkUINodeHandle (*getRichEditorController)(ArkUINodeHandle node);
};

struct ArkUIDataPanelModifierAPI {
    void (*setDataPanelCloseEffect)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*setDataPanelStrokeWidth)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setDataPanelTrackShadow)(ArkUINodeHandle node, Arkoala_Float32* shadow, Arkoala_Int32 length,
        Arkoala_Int32* colorLength, Arkoala_Int32* colors, Arkoala_Float32* offsets);
    void (*setDataPanelTrackShadowDisable)(ArkUINodeHandle node);
    void (*setDataPanelInit)(
        ArkUINodeHandle node, Arkoala_Int32* data, Arkoala_Int32 length, Arkoala_Int32 max, Arkoala_Int32 type);
    void (*setDataPanelValueColors)(ArkUINodeHandle node, Arkoala_Int32 length, Arkoala_Int32* colorLength,
        Arkoala_Int32* colors, Arkoala_Float32* offsets);
};

struct ArkUIQRCodeModifierAPI {
    void (*setQRCodeColor)(ArkUINodeHandle node, Arkoala_Int32 color);
    void (*setQRCodeValue)(ArkUINodeHandle node, Arkoala_CharPtr value);
};

struct ArkUITextAreaControllerModifierAPI {
    ArkUINodeHandle (*getTextAreaController)(ArkUINodeHandle node);
};

struct ArkUICanvasRenderingContext2DModifierAPI {
    ArkUINodeHandle (*getCanvasRenderingContext2D)(ArkUINodeHandle node);
};

struct ArkUIUtilsModifierAPI {
    Arkoala_Float32 (*getDensity)(Arkoala_Int32 deviceId);
    Arkoala_Float32 (*getFontScale)(Arkoala_Int32 deviceId);
    Arkoala_Float32 (*getDesignWidthScale)(Arkoala_Int32 deviceId);
};

struct ArkUISideBarModifierAPI {
    void (*setShowSideBar)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*setControlButton)(ArkUINodeHandle node, Arkoala_Float32* position, Arkoala_Int32 positionArrayLength,
        Arkoala_CharPtr* showIcon, Arkoala_Int32 showArrayLength, Arkoala_CharPtr* hiddenIcon,
        Arkoala_Int32 hiddenArrayLength, Arkoala_CharPtr* switchingIcon, Arkoala_Int32 switchingArrayLength);
    void (*setShowControlButton)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*setSideBarWidth)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setMinSideBarWidth)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setMaxSideBarWidth)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setAutoHide)(ArkUINodeHandle node, Arkoala_Bool value);
    void (*setSideBarPosition)(ArkUINodeHandle node, Arkoala_Int32 unit);
    void (*setSideBarDivider)(ArkUINodeHandle node, Arkoala_Float32* strokeWidth, Arkoala_Int32 color,
        Arkoala_Float32* startMargin, Arkoala_Float32* endMargin);
    void (*setMinContentWidth)(ArkUINodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
};

struct ArkUIXComponentModifierAPI {
    // loadXComponent() returns VM-specific handle produced by
    // ArkNativeEngine::LoadModuleByName(). vmKind parameters allows to
    // differentiate which VM shall be used to load. Embedder code must use kind
    // matching VM we're embedding into. errorCallbackId is invoked if operation
    // cannot be completed.
    ArkUIVMObject (*loadXComponent)(ArkUIVMContext vmContext, ArkUINodeHandle node, ArkUIVMKind vmKind,
        Arkoala_CharPtr libraryName, Arkoala_Int32 errorCallbackId);
    void (*setXComponentOptions)(
        ArkUINodeHandle node, Arkoala_CharPtr id, Arkoala_CharPtr type, Arkoala_CharPtr libraryName);
    Arkoala_CharPtr (*getXComponentSurfaceId)(ArkUIXComponentControllerHandle controller);
    void (*setXComponentSurfaceSize)(
        ArkUIXComponentControllerHandle controller, Arkoala_Int32 surfaceWidth, Arkoala_Int32 surfaceHeight);
    ArkUIXComponentControllerHandle (*getXComponentController)(ArkUINodeHandle node);
};

struct ArkUIBasicAPI {
    /// Tree operations.
    ArkUINodeHandle (*createNode)(Arkoala_CharPtr type, Arkoala_Int32 id, Arkoala_Int32 flags);
    void (*disposeNode)(ArkUINodeHandle node);
    // Returned pointer is valid only till node is alive.
    Arkoala_CharPtr (*getName)(ArkUINodeHandle node);
    Arkoala_Int32 (*getId)(ArkUINodeHandle node);
    void (*dump)(ArkUINodeHandle node);
    void (*addChild)(ArkUINodeHandle parent, ArkUINodeHandle child);
    void (*removeChild)(ArkUINodeHandle parent, ArkUINodeHandle child);
    void (*insertChildAfter)(ArkUINodeHandle parent, ArkUINodeHandle child, ArkUINodeHandle sibling);
    // Returned pointer is valid only till node is alive.
    Arkoala_CharPtr (*getAttribute)(ArkUINodeHandle node, Arkoala_CharPtr attribute);
    void (*setAttribute)(ArkUINodeHandle node, Arkoala_CharPtr attribute, Arkoala_CharPtr value);
    void (*resetAttribute)(ArkUINodeHandle node, Arkoala_CharPtr attribute);
    void (*setChildTotalCount)(ArkUINodeHandle node, Arkoala_Int32 totalCount);
    // Commit attributes updates for node.
    void (*applyModifierFinish)(ArkUINodeHandle nodePtr);

    /// Custom layout and rendering.
    void (*setCustomCallback)(ArkUINodeHandle node, Arkoala_Int32 callbackId);

    Arkoala_Int32 (*measureLayoutAndDraw)(ArkUIVMContext vmContext, ArkUINodeHandle node);
    Arkoala_Int32 (*measureNode)(ArkUIVMContext vmContext, ArkUINodeHandle node, Arkoala_Float32* data);
    Arkoala_Int32 (*layoutNode)(ArkUIVMContext vmContext, ArkUINodeHandle node, Arkoala_Float32* data);
    Arkoala_Int32 (*drawNode)(ArkUIVMContext vmContext, ArkUINodeHandle node, Arkoala_Float32* data);

    void (*setMeasureWidth)(ArkUINodeHandle node, Arkoala_Float32 value);
    Arkoala_Float32 (*getMeasureWidth)(ArkUINodeHandle node);
    void (*setMeasureHeight)(ArkUINodeHandle node, Arkoala_Float32 value);
    Arkoala_Float32 (*getMeasureHeight)(ArkUINodeHandle node);
    void (*setX)(ArkUINodeHandle node, Arkoala_Float32 value);
    void (*setY)(ArkUINodeHandle node, Arkoala_Float32 value);

    /// List/grid index tracking.
    Arkoala_Int32 (*indexerChecker)(ArkUIVMContext context, ArkUINodeHandle node);
    void (*setRangeUpdater)(ArkUINodeHandle node, Arkoala_Int32 updaterId);
    void (*setLazyItemIndexer)(ArkUIVMContext vmContext, ArkUINodeHandle node, Arkoala_Int32 indexerId);

    /// Vsync support.
    Arkoala_Int32 (*setVsyncCallback)(ArkUIVMContext vmContext, Arkoala_Int32 device, Arkoala_Int32 callbackId);
    void (*unblockVsyncWait)(ArkUIVMContext vmContext, Arkoala_Int32 device);

    /// Events.
    /**
     * Returns != 0 if an event was received,
     * fills in supplied buffer in such a case.
     * Must not block, blocking is performed by
     * ArkoalaHostApi.waitForVsync().
     */
    Arkoala_Int32 (*checkEvent)(ArkUIAPIEvent* event);
    /**
     * Add an event to the event queue, so that
     * it will be picked up later by checkEvent().
     */
    void (*sendEvent)(ArkUIAPIEvent* event);

    /// Continuations on native side.
    void (*callContinuation)(Arkoala_Int32 continuationId, Arkoala_Int32 argCount, ArkUIAPIEventCallbackArg* args);
};

struct ArkUIAnimationAPI {
    Arkoala_Int32 (*startAnimation)(const ArkUIAPIAnimationSpec* spec, Arkoala_Int32 callbackId);
    void (*openImplicitAnimation)(
        ArkUIVMContext vmContext, Arkoala_Int32 curve, Arkoala_Float32* options, Arkoala_Int32 callbackId);
    void (*closeImplicitAnimation)();
};

struct ArkUINavigationAPI {
    void (*popPageToIndex)(Arkoala_Int32 index);
    void (*setNavDestinationBackPressed)(ArkUIVMContext vmContext, ArkUINodeHandle node, Arkoala_Int32 indexerId);
};

/**
 * An API to control an implementation. When making changes modifying binary
 * layout, i.e. adding new events - increase ARKUI_API_VERSION above for binary
 * layout checks.
 */
struct ArkUINodeAPI {
    Arkoala_Int32 version;
    void (*setCallbackMethod)(ArkUIAPICallbackMethod* method);

    const ArkUIBasicAPI* (*getBasicAPI)();
    const ArkUIAnimationAPI* (*getAnimationAPI)();
    const ArkUINavigationAPI* (*getNavigationAPI)();
    const ArkUICommonModifierAPI* (*getCommonModifier)();
    const ArkUIButtonModifierAPI* (*getButtonModifier)();
    const ArkUITextModifierAPI* (*getTextModifier)();
    const ArkUIImageModifierAPI* (*getImageModifier)();
    const ArkUISwiperModifierAPI* (*getSwiperModifier)();
    const ArkUIStackModifierAPI* (*getStackModifier)();
    const ArkUINavigatorModifierAPI* (*getNavigatorModifier)();
    const ArkUIVideoModifierAPI* (*getVideoModifier)();
    const ArkUIVideoControllerModifierAPI* (*getVideoControllerModifier)();
    const ArkUIColumnModifierAPI* (*getColumnModifier)();
    const ArkUIRowModifierAPI* (*getRowModifier)();
    const ArkUIDividerModifierAPI* (*getDividerModifier)();
    const ArkUIFlexModifierAPI* (*getFlexModifier)();
    const ArkUIListModifierAPI* (*getListModifier)();
    const ArkUIGridModifierAPI* (*getGridModifier)();
    const ArkUIGridItemModifierAPI* (*getGridItemModifier)();
    const ArkUIScrollModifierAPI* (*getScrollModifier)();
    const ArkUIScrollBarModifierAPI* (*getScrollBarModifier)();
    const ArkUIScrollerModifierAPI* (*getScrollerModifier)();
    const ArkUITabsModifierAPI* (*getTabsModifier)();
    const ArkUITabContentModifierAPI* (*getTabContentModifier)();
    const ArkUITabsControllerModifierAPI* (*getTabsControllerModifier)();
    const ArkUISwiperControllerModifierAPI* (*getSwiperControllerModifier)();
    const ArkUIGestureModifierAPI* (*getGestureModifier)();
    const ArkUISliderModifierAPI* (*getSliderModifier)();
    const ArkUIProgressModifierAPI* (*getProgressModifier)();
    const ArkUINavDestinationModifierAPI* (*getNavDestinationModifier)();
    const ArkUITextAreaModifierAPI* (*getTextAreaModifier)();
    const ArkUITextInputModifierAPI* (*getTextInputModifier)();
    const ArkUIWebModifierAPI* (*getWebModifier)();
    const ArkUIToggleModifierAPI* (*getToggleModifier)();
    const ArkUIBlankModifierAPI* (*getBlankModifier)();
    const ArkUICheckboxModifierAPI* (*getCheckboxModifier)();
    const ArkUICheckboxGroupModifierAPI* (*getCheckboxGroupModifier)();
    const ArkUIMenuModifierAPI* (*getMenuModifier)();
    const ArkUIMenuItemModifierAPI* (*getMenuItemModifier)();
    const ArkUIMenuItemGroupModifierAPI* (*getMenuItemGroupModifier)();
    const ArkUIAlphabetIndexerModifierAPI* (*getAlphabetIndexerModifier)();
    const ArkUIListItemGroupModifierAPI* (*getListItemGroupModifier)();
    const ArkUINavigationModifierAPI* (*getNavigationModifier)();
    const ArkUIGaugeModifierAPI* (*getGaugeModifier)();
    const ArkUIBadgeModifierAPI* (*getBadgeModifier)();
    const ArkUIRefreshModifierAPI* (*getRefreshModifier)();
    const ArkUIHyperlinkModifierAPI* (*getHyperlinkModifier)();
    const ArkUILoadingProgressModifierAPI* (*getLoadingProgressModifier)();
    const ArkUIImageAnimatorModifierAPI* (*getImageAnimatorModifier)();
    const ArkUIRatingModifierAPI* (*getRatingModifier)();
    const ArkUISearchModifierAPI* (*getSearchModifier)();
    const ArkUISearchControllerModifierAPI* (*getSearchControllerModifier)();
    const ArkUITextClockModifierAPI* (*getTextClockModifier)();
    const ArkUITextClockControllerModifierAPI* (*getTextClockControllerModifier)();
    const ArkUITextPickerModifierAPI* (*getTextPickerModifier)();
    const ArkUITextTimerModifierAPI* (*getTextTimerModifier)();
    const ArkUITextTimerControllerModifierAPI* (*getTextTimerControllerModifier)();
    const ArkUISpanModifierAPI* (*getSpanModifier)();
    const ArkUISelectModifierAPI* (*getSelectModifier)();
    const ArkUIMarqueeModifierAPI* (*getMarqueeModifier)();
    const ArkUIGridColModifierAPI* (*getGridColModifier)();
    const ArkUIGridRowModifierAPI* (*getGridRowModifier)();
    const ArkUIRadioModifierAPI* (*getRadioModifier)();
    const ArkUIRichEditorModifierAPI* (*getRichEditorModifier)();
    const ArkUIRichEditorControllerModifierAPI* (*getRichEditorControllerModifier)();
    const ArkUIDataPanelModifierAPI* (*getDataPanelModifier)();
    const ArkUIQRCodeModifierAPI* (*getQRCodeModifier)();
    const ArkUITextAreaControllerModifierAPI* (*getTextAreaControllerModifier)();
    const ArkUICanvasRenderingContext2DModifierAPI* (*getCanvasRenderingContext2DModifier)();
    const ArkUIPatternLockControllerModifierAPI* (*getPatternLockControllerModifier)();
    const ArkUIPatternLockModifierAPI* (*getPatternLockModifier)();
    const ArkUIShapedCommonModifierAPI* (*getShapedCommonModifier)();
    const ArkUILineModifierAPI* (*getLineModifier)();
    const ArkUIPathModifierAPI* (*getPathModifier)();
    const ArkUIPolygonModifierAPI* (*getPolygonModifier)();
    const ArkUIRectModifierAPI* (*getRectModifier)();
    const ArkUIShapeModifierAPI* (*getShapeModifier)();
    const ArkUIUtilsModifierAPI* (*getUtilsModifier)();
    const ArkUISideBarModifierAPI* (*getSideBarModifier)();
    const ArkUIXComponentModifierAPI* (*getXComponentModifier)();
};

struct ArkUIBasicNodeAPI {
    Arkoala_Int32 version;
    void (*setCallbackMethod)(ArkUIAPICallbackMethod* method);
    const ArkUIBasicAPI* (*getBasicModifier)();
};

struct ArkUIGraphicsCanvasAPI {
    void (*finalize)(ArkUICanvasHandle canvas);

    void (*drawPoint)(ArkUICanvasHandle canvas, Arkoala_Float32 x, Arkoala_Float32 y, ArkUIPaintHandle paint);
    void (*drawPoints)(ArkUICanvasHandle canvas, Arkoala_Int32 mode, Arkoala_Float32* coords, Arkoala_Int32 count,
        ArkUIPaintHandle paint);
    void (*drawLine)(ArkUICanvasHandle canvas, Arkoala_Float32 x0, Arkoala_Float32 y0, Arkoala_Float32 x1,
        Arkoala_Float32 y1, ArkUIPaintHandle paint);
    void (*drawArc)(ArkUICanvasHandle canvas, Arkoala_Float32 left, Arkoala_Float32 top, Arkoala_Float32 right,
        Arkoala_Float32 bottom, Arkoala_Float32 startAngle, Arkoala_Float32 sweepAngle, Arkoala_Bool includeCenter,
        ArkUIPaintHandle paint);
    void (*drawRect)(ArkUICanvasHandle canvas, Arkoala_Float32 left, Arkoala_Float32 top, Arkoala_Float32 right,
        Arkoala_Float32 bottom, ArkUIPaintHandle paint);
    void (*drawOval)(ArkUICanvasHandle canvas, Arkoala_Float32 left, Arkoala_Float32 top, Arkoala_Float32 right,
        Arkoala_Float32 bottom, ArkUIPaintHandle paint);
    void (*drawCircle)(ArkUICanvasHandle canvas, Arkoala_Float32 x, Arkoala_Float32 y, Arkoala_Float32 radius,
        ArkUIPaintHandle paintPtr);
    void (*drawRRect)(ArkUICanvasHandle canvas, Arkoala_Float32 left, Arkoala_Float32 top, Arkoala_Float32 right,
        Arkoala_Float32 bottom, Arkoala_Float32* jradii, Arkoala_Int32 jradiiSize, ArkUIPaintHandle paintPtr);
    void (*drawDRRect)(ArkUICanvasHandle canvas, Arkoala_Float32 ol, Arkoala_Float32 ot, Arkoala_Float32 oright,
        Arkoala_Float32 ob, Arkoala_Float32* ojradii, Arkoala_Int32 ojradiiSize, Arkoala_Float32 il, Arkoala_Float32 it,
        Arkoala_Float32 ir, Arkoala_Float32 ib, Arkoala_Float32* ijradii, Arkoala_Int32 ijradiiSize,
        ArkUIPaintHandle paint);
    void (*drawString)(ArkUICanvasHandle canvas, Arkoala_CharPtr string, Arkoala_Float32 x, Arkoala_Float32 y,
        ArkUIFontHandle font, ArkUIPaintHandle paint);
};

struct ArkUIGraphicsPaintAPI {
    ArkUIPaintHandle (*make)();
    void (*finalize)(ArkUIPaintHandle handle);

    void (*setColor)(ArkUIPaintHandle paint, Arkoala_Int32 color);
    Arkoala_Int32 (*getColor)(ArkUIPaintHandle paint);
    void (*setAlpha)(ArkUIPaintHandle paint, Arkoala_Float32 alpha);
    Arkoala_Float32 (*getAlpha)(ArkUIPaintHandle paint);
};

struct ArkUIGraphicsFontAPI {
    ArkUIFontHandle (*makeDefault)();
    void (*finalize)(ArkUIPaintHandle handle);
};

struct ArkUIGraphicsAPI {
    Arkoala_Int32 version;
    void (*setCallbackMethod)(ArkUIAPICallbackMethod* method);

    /**
     * Graphics.
     */
    const ArkUIGraphicsCanvasAPI* (*getCanvasAPI)();
    const ArkUIGraphicsPaintAPI* (*getPaintAPI)();
    const ArkUIGraphicsFontAPI* (*getFontAPI)();
};

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ARKOALA_API_H