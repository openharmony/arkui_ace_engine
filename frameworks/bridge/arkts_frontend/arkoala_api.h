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

#define ARKUI_FULL_API_VERSION 55
#define ARKUI_BASIC_API_VERSION 1
#define ARKUI_GRAPHICS_API_VERSION 2

enum ArkUIAPIVariantKind {
    Basic = 1,
    Full = 2,
    Graphics = 3,
    Count = Graphics + 1,
};

typedef void* NodeHandle;
typedef void* ArkUIAPIVMContext;
typedef void* ArkUICanvasHandle;
typedef void* ArkUIPaintHandle;
typedef void* ArkUIFontHandle;
typedef int Arkoala_Bool;
typedef int Arkoala_Int32;
typedef unsigned int Arkoala_Uint32;
typedef long long Arkoala_Int64;
typedef float Arkoala_Float32;
typedef double Arkoala_Float64;
typedef const char* Arkoala_CharPtr;

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

// TODO: Current implementation assumes that each argument is 4 bytes,
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

#define ARKOALA_MAX_MULTIPOINTER_ARGS_COUNT 10

struct ArkUIAPIEventMultiPointer {
    Arkoala_Int32 count;
    Arkoala_Int32 xs[ARKOALA_MAX_MULTIPOINTER_ARGS_COUNT];
    Arkoala_Int32 ys[ARKOALA_MAX_MULTIPOINTER_ARGS_COUNT];
    Arkoala_Int32 state[ARKOALA_MAX_MULTIPOINTER_ARGS_COUNT];
};

struct ArkUIAPIEventTextInput {
    Arkoala_Int32 nativeStringLow;
    Arkoala_Int32 nativeStringHigh;
};

// Change version if changing these constants.
#define ARKOALA_MAX_CALLBACK_ARGS_COUNT 10
#define ARKOALA_MAX_ASYNC_EVENT_ARGS_COUNT 12

struct ArkUIAPIEventCallback {
    Arkoala_Int32 id;
    Arkoala_Int32 numArgs;
    Arkoala_Int32 continuationId;
    ArkUIAPIEventCallbackArg args[ARKOALA_MAX_CALLBACK_ARGS_COUNT];
};

struct ArkUIAPIEventComponentAsyncEvent {
    Arkoala_Int32 subKind;
    Arkoala_Int32 data[ARKOALA_MAX_ASYNC_EVENT_ARGS_COUNT];
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
    Arkoala_Int32 kind; // Actually ArkUINodeAPIEventKind, but use int for fixed binary layout.
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
    // TODO: more fields !
};

struct ArkUIAPICallbackMethod {
    Arkoala_Int32 (*CallInt)(
        ArkUIAPIVMContext vmContext, Arkoala_Int32 methodId, Arkoala_Int32 numArgs, ArkUIAPIEventCallbackArg* args);
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
    void (*setWidth)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*resetWidth)(NodeHandle node);

    void (*setHeight)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*resetHeight)(NodeHandle node);

    void (*setOpacity)(NodeHandle node, Arkoala_Float32 value);
    void (*resetOpacity)(NodeHandle node);

    void (*setLinearGradient)(NodeHandle node, Arkoala_Float32 angle, Arkoala_Int32 direction, Arkoala_Bool repeat,
        const Arkoala_Int32* colors, const Arkoala_Float32* positions);
    void (*resetLinearGradient)(NodeHandle node);

    void (*setPadding)(NodeHandle node, const Arkoala_Float32* values, const Arkoala_Int32* units);
    void (*resetPadding)(NodeHandle node);

    void (*setMargin)(NodeHandle node, const Arkoala_Float32* values, const Arkoala_Int32* units);
    void (*resetMargin)(NodeHandle node);

    void (*setBorderRadius)(NodeHandle node, const Arkoala_Float32* values, const Arkoala_Int32* units);
    void (*resetBorderRadius)(NodeHandle node);

    void (*setBorderColor)(NodeHandle node, const Arkoala_Int32* colors, Arkoala_Int32 length);
    void (*resetBorderColor)(NodeHandle node);

    void (*setZIndex)(NodeHandle node, Arkoala_Int32 value);
    void (*resetZIndex)(NodeHandle node);

    void (*setVisibility)(NodeHandle node, Arkoala_Int32 value);
    void (*resetVisibility)(NodeHandle node);

    void (*setBackgroundColor)(NodeHandle node, Arkoala_Int32 value);
    void (*resetBackgroundColor)(NodeHandle node);

    void (*setBorder)(NodeHandle node, ArkUIBorderOptions* options);
    void (*resetBorder)(NodeHandle node);

    void (*setClip)(NodeHandle node, Arkoala_Bool clip);
    void (*resetClip)(NodeHandle node);

    void (*setBackgroundImage)(NodeHandle node, Arkoala_CharPtr src, Arkoala_Int32 repeat);
    void (*setBackgroundImageResource)(NodeHandle node, Arkoala_Int32 id, Arkoala_Int32 type, Arkoala_CharPtr name,
        Arkoala_CharPtr bundleName, Arkoala_CharPtr moduleName, Arkoala_Int32 repeat);
    void (*resetBackgroundImage)(NodeHandle node);

    void (*setBackgroundImageSize)(NodeHandle node, Arkoala_Bool flag, const Arkoala_Float32* values);
    void (*resetBackgroundImageSize)(NodeHandle node);

    /**
     * notify the node to send async appear event back
     */
    void (*notifyComponentAsyncEvent)(NodeHandle nodePtr, Arkoala_Int32 subKind);
    void (*notifyResetComponentAsyncEvent)(NodeHandle nodePtr, Arkoala_Int32 subKind);

    void (*setScaleOptions)(NodeHandle node, Arkoala_Float32* values, Arkoala_Int32 length);
    void (*setTranslateOptions)(NodeHandle node, Arkoala_Float32* values, Arkoala_Int32 length);
    void (*setRotateOptions)(NodeHandle node, Arkoala_Float32* values, Arkoala_Int32 length);
    void (*setTransform)(NodeHandle node, Arkoala_Float32* matrix, Arkoala_Int32 length);
    void (*setVisibleAreaChangeRatios)(NodeHandle node, Arkoala_Float32* values, Arkoala_Int32 length);

    void (*setAlign)(NodeHandle node, Arkoala_Int32 value);

    void (*setAspectRatio)(NodeHandle node, Arkoala_Float32 value);
    void (*setTransition)(NodeHandle node, Arkoala_Int32 type, Arkoala_Float32 opacity, Arkoala_Float32* translate,
        Arkoala_Float32* scale, Arkoala_Float32* rotate);
    void (*setChainedTransition)(NodeHandle node, Arkoala_Float32* appearPtr, Arkoala_Float32* disappearPtr,
        Arkoala_Int32 appearLen, Arkoala_Int32 disappearLen);
    void (*setHitTestBehavior)(NodeHandle node, Arkoala_Int32 value);
    void (*setFlexGrow)(NodeHandle node, Arkoala_Float32 value);
    void (*setFlexShrink)(NodeHandle node, Arkoala_Float32 value);
    void (*setPosition)(NodeHandle node, Arkoala_Float32* values, Arkoala_Int32 length);
    void (*setMarkAnchor)(NodeHandle node, Arkoala_Float32* values, Arkoala_Int32 length);
    void (*setOffset)(NodeHandle node, Arkoala_Float32* values, Arkoala_Int32 length);
    void (*setEnabled)(NodeHandle node, Arkoala_Bool value);
    void (*setShadow)(
        NodeHandle node, Arkoala_Float32 radius, Arkoala_Int32 color, Arkoala_Float32 offsetX, Arkoala_Float32 offsetY);
    void (*setLayoutWeight)(NodeHandle node, Arkoala_Float32 layoutValue);
    void (*setFocusable)(NodeHandle node, Arkoala_Bool value);
    void (*setGeometryTransition)(NodeHandle node, Arkoala_CharPtr value);
    void (*setDraggable)(NodeHandle node, Arkoala_Bool flag);
    void (*setKey)(NodeHandle node, Arkoala_CharPtr value);
    void (*setId)(NodeHandle node, Arkoala_CharPtr value);

    void (*setResponseRegion)(NodeHandle node, Arkoala_Float32* rectangles, Arkoala_Int32 length);
    void (*resetResponseRegion)(NodeHandle node);
    void (*setConstraintSize)(NodeHandle node, Arkoala_Int32 minWValue, Arkoala_Int32 minWUnit, Arkoala_Int32 minHValue,
        Arkoala_Int32 minHUnit, Arkoala_Int32 maxWValue, Arkoala_Int32 maxWUnit, Arkoala_Int32 maxHValue,
        Arkoala_Int32 maxHUnit);
    void (*setGridSpan)(NodeHandle node, Arkoala_Int32 value);
    void (*setGridOffset)(NodeHandle node, Arkoala_Int32 value);
    void (*setHoverEffect)(NodeHandle node, Arkoala_Int32 value);
    void (*setSizeType)(NodeHandle node, Arkoala_Int32 type, Arkoala_Int32 span, Arkoala_Int32 offset);
    void (*setSizeTypeNumber)(NodeHandle node, Arkoala_Int32 type, Arkoala_Int32 value);
    void (*setDefaultFocus)(NodeHandle node, Arkoala_Bool flag);
};

struct ArkUIShapedCommonModifierAPI {
    void (*setFill)(NodeHandle node, Arkoala_Int32 value);
    void (*setStroke)(NodeHandle node, Arkoala_Int32 value);
    void (*setFillOpacity)(NodeHandle node, Arkoala_Float32 value);
    void (*setStrokeOpacity)(NodeHandle node, Arkoala_Float32 value);
    void (*setStrokeWidth)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setStrokeDashArray)(NodeHandle node, Arkoala_Float32* value, Arkoala_Int32* unit, Arkoala_Int32 valueLength,
        Arkoala_Int32 unitLength);
    void (*setAntiAlias)(NodeHandle node, Arkoala_Bool value);
    void (*setStrokeDashOffset)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setStrokeMiterLimit)(NodeHandle node, Arkoala_Float32 value);
    void (*setStrokeLineCap)(NodeHandle node, Arkoala_Int32 value);
    void (*setStrokeLineJoin)(NodeHandle node, Arkoala_Int32 value);
};
struct ArkUILineModifierAPI {
    void (*setStartPoint)(
        NodeHandle node, Arkoala_Float32 xValue, Arkoala_Int32 xUnit, Arkoala_Float32 yValue, Arkoala_Int32 yUnit);
    void (*setEndPoint)(
        NodeHandle node, Arkoala_Float32 xValue, Arkoala_Int32 xUnit, Arkoala_Float32 yValue, Arkoala_Int32 yUnit);
};

struct ArkUIPathModifierAPI {
    void (*setPathCommands)(NodeHandle node, Arkoala_CharPtr commands);
};

struct ArkUIPolygonModifierAPI {
    void (*setPoints)(NodeHandle node, Arkoala_Float32* points, Arkoala_Int32 length, Arkoala_Bool isPolygon);
};

struct ArkUIRectModifierAPI {
    void (*setRadiusWidth)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setRadiusHeight)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setRadius)(NodeHandle node, Arkoala_Float32* points, Arkoala_Int32 length);
};

struct ArkUIShapeModifierAPI {
    void (*setViewPort)(NodeHandle node, Arkoala_Float32* ports, Arkoala_Int32 length);
    void (*setMesh)(
        NodeHandle node, Arkoala_Float32* meshPoints, Arkoala_Int32 length, Arkoala_Int32 column, Arkoala_Int32 row);
};
struct ArkUITextModifierAPI {
    void (*setTextLabel)(NodeHandle node, Arkoala_CharPtr label);
    void (*resetTextLabel)(NodeHandle node);

    void (*setTextBaselineOffset)(NodeHandle nodePtr, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*resetTextBaselineOffset)(NodeHandle nodePtr);

    void (*setTextOverflow)(NodeHandle nodePtr, Arkoala_Int32 value);
    void (*resetTextOverflow)(NodeHandle nodePtr);

    void (*setTextFontSize)(NodeHandle nodePtr, Arkoala_Float32 number, Arkoala_Int32 unit);
    void (*resetTextFontSize)(NodeHandle nodePtr);

    void (*setTextMinFontSize)(NodeHandle nodePtr, Arkoala_Float32 number, Arkoala_Int32 unit);
    void (*resetTextMinFontSize)(NodeHandle nodePtr);

    void (*setTextMaxFontSize)(NodeHandle nodePtr, Arkoala_Float32 number, Arkoala_Int32 unit);
    void (*resetTextMaxFontSize)(NodeHandle nodePtr);

    void (*setTextFontColor)(NodeHandle nodePtr, Arkoala_Int32 color);
    void (*resetTextFontColor)(NodeHandle nodePtr);

    void (*setTextFontWeight)(NodeHandle nodePtr, Arkoala_Int32 value);
    void (*resetTextFontWeight)(NodeHandle nodePtr);

    void (*setTextLineHeight)(NodeHandle nodePtr, Arkoala_Float32 number, Arkoala_Int32 unit);
    void (*resetTextLineHeight)(NodeHandle nodePtr);

    void (*setTextAlign)(NodeHandle nodePtr, Arkoala_Int32 value);
    void (*resetTextAlign)(NodeHandle nodePtr);

    void (*setTextMaxLines)(NodeHandle nodePtr, Arkoala_Int32 value);
    void (*resetTextMaxLines)(NodeHandle nodePtr);

    void (*setTextDraggable)(NodeHandle node, Arkoala_Bool value);

    void (*setFontFamily)(NodeHandle node, Arkoala_CharPtr value);
    void (*setHeightAdaptivePolicy)(NodeHandle nodePtr, Arkoala_Int32 value);
    void (*setTextLetterSpacing)(NodeHandle nodePtr, Arkoala_Float32 number, Arkoala_Int32 unit);
    void (*setTextCase)(NodeHandle nodePtr, Arkoala_Int32 value);
    void (*setTextIndent)(NodeHandle nodePtr, Arkoala_Float32 number, Arkoala_Int32 unit);
};

struct ArkUIButtonModifierAPI {
    void (*setButtonLabel)(NodeHandle node, Arkoala_CharPtr label);
    void (*resetButtonLabel)(NodeHandle node);
    void (*setButtonType)(NodeHandle node, Arkoala_Int32 type);
    void (*setButtonFontSize)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setButtonFontWeight)(NodeHandle node, Arkoala_Int32 value);
    void (*setButtonFontFamily)(NodeHandle node, Arkoala_CharPtr value);
};

struct ArkUIImageModifierAPI {
    void (*setImageSrc)(NodeHandle node, Arkoala_CharPtr label);
    void (*resetImageSrc)(NodeHandle node);
    void (*setImageObjectFit)(NodeHandle node, Arkoala_Int32 label);
    void (*resetImageObjectFit)(NodeHandle node);
    void (*setImageAlt)(NodeHandle node, Arkoala_CharPtr src);
    void (*resetImageAlt)(NodeHandle node);
    void (*setImageObjectRepeat)(NodeHandle nodePtr, Arkoala_Int32 value);
    void (*resetImageObjectRepeat)(NodeHandle nodePtr);
    void (*setImageResource)(NodeHandle node, Arkoala_Int32 id, Arkoala_Int32 type, Arkoala_CharPtr name,
        Arkoala_CharPtr bundleName, Arkoala_CharPtr moduleName);
    void (*setImageAltResource)(NodeHandle node, Arkoala_Int32 id, Arkoala_Int32 type, Arkoala_CharPtr name,
        Arkoala_CharPtr bundleName, Arkoala_CharPtr moduleName);
    void (*setImageAutoResize)(NodeHandle node, Arkoala_Bool flag);
    void (*setImageFillColor)(NodeHandle node, Arkoala_Int32 color);
};

struct ArkUIColumnModifierAPI {
    void (*setColumnOptions)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*resetColumnOptions)(NodeHandle node);
    void (*setColumnAlignItems)(NodeHandle node, Arkoala_Int32 value);
    void (*resetColumnAlignItems)(NodeHandle node);
    void (*setColumnJustifyContent)(NodeHandle node, Arkoala_Int32 value);
    void (*resetColumnJustifyContent)(NodeHandle node);
};

struct ArkUIRowModifierAPI {
    void (*setRowOptions)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*resetRowOptions)(NodeHandle node);
    void (*setRowAlignItems)(NodeHandle node, Arkoala_Int32 value);
    void (*resetRowAlignItems)(NodeHandle node);
    void (*setRowJustifyContent)(NodeHandle node, Arkoala_Int32 value);
    void (*resetRowJustifyContent)(NodeHandle node);
};

struct ArkUIDividerModifierAPI {
    void (*setDividerVertical)(NodeHandle node, Arkoala_Bool value);
    void (*resetDividerVertical)(NodeHandle node);
    void (*setDividerColor)(NodeHandle node, Arkoala_Int32 value);
    void (*resetDividerColor)(NodeHandle node);
    void (*setDividerStrokeWidth)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*resetDividerStrokeWidth)(NodeHandle node);
    void (*setDividerLineCap)(NodeHandle node, Arkoala_Int32 value);
};

struct ArkUIFlexModifierAPI {
    void (*setFlexOptions)(NodeHandle node, Arkoala_Int32* options, Arkoala_Int32 length);
};

struct ArkUIListModifierAPI {
    void (*setListScrollBar)(NodeHandle node, Arkoala_Int32 bar);
    void (*resetListScrollBar)(NodeHandle node);
    void (*setListOptions)(NodeHandle node, Arkoala_Float32 space, Arkoala_Int32 unit, Arkoala_Int32 initialIndex);
    void (*resetListOptions)(NodeHandle node);
    void (*setListDirection)(NodeHandle node, Arkoala_Int32 direction);
    void (*resetListDirection)(NodeHandle node);
    void (*setListAlignListItem)(NodeHandle node, Arkoala_Int32 value);
    void (*setListScrollSnapAlign)(NodeHandle node, Arkoala_Int32 value);
    void (*setListDivider)(NodeHandle node, Arkoala_Float32* strokeWidth, Arkoala_Int32 color,
        Arkoala_Float32* startMargin, Arkoala_Float32* endMargin);
    void (*setListEdgeEffect)(NodeHandle node, Arkoala_Int32 value);
    void (*setListSticky)(NodeHandle node, Arkoala_Int32 value);
    void (*setChainAnimationOptions)(NodeHandle node, Arkoala_Float32* option, Arkoala_Int32 effect);
};

struct ArkUIListItemGroupModifierAPI {
    void (*setListItemGroupDivider)(NodeHandle node, Arkoala_Float32* strokeWidth, Arkoala_Int32 color,
        Arkoala_Float32* startMargin, Arkoala_Float32* endMargin);
    void (*setListItemGroupStyle)(NodeHandle node, Arkoala_Int32 style);
};

struct ArkUISwiperModifierAPI {
    void (*setAutoPlay)(NodeHandle node, Arkoala_Bool value);
    void (*setShowIndicator)(NodeHandle node, Arkoala_Bool value);
    void (*setInterval)(NodeHandle node, Arkoala_Int32 value);
    void (*setLoop)(NodeHandle node, Arkoala_Bool value);
    void (*setVertical)(NodeHandle node, Arkoala_Bool value);
    void (*setSwiperCurve)(NodeHandle node, Arkoala_Int32 value);
    void (*resetSwiperCurve)(NodeHandle node);
    void (*setSwiperItemSpace)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*resetSwiperItemSpace)(NodeHandle node);
    void (*setIndicatorStyle)(
        NodeHandle node, Arkoala_Float32* values, Arkoala_Int32* units, Arkoala_Bool mask, Arkoala_Int32* colors);
    void (*setSwiperIndex)(NodeHandle node, Arkoala_Int32 index);
    void (*setSwiperDuration)(NodeHandle node, Arkoala_Int32 index);
    void (*setCachedCount)(NodeHandle node, Arkoala_Int32 value);
    void (*setDisableSwipe)(NodeHandle node, Arkoala_Bool value);
    void (*setSwiperEffectMode)(NodeHandle node, Arkoala_Int32 value);
};

struct ArkUISwiperControllerModifierAPI {
    NodeHandle (*getSwiperController)(NodeHandle node);
    void (*setShowNext)(NodeHandle node);
    void (*setShowPrevious)(NodeHandle node);
};

struct ArkUIStackModifierAPI {
    void (*setStackContentAlign)(NodeHandle node, Arkoala_Int32 alignment);
    void (*resetStackContentAlign)(NodeHandle node);
};
struct ArkUINavigatorModifierAPI {
    // navigator
    void (*setNavigatorType)(NodeHandle node, Arkoala_Int32 type);
    void (*resetNavigatorType)(NodeHandle node);

    void (*setNavigatorTarget)(NodeHandle node, Arkoala_CharPtr target);
    void (*resetNavigatorTarget)(NodeHandle node);
};
struct ArkUIVideoModifierAPI {
    // video
    void (*setVideoAutoPlay)(NodeHandle node, Arkoala_Bool autoPlay);
    void (*resetVideoAutoPlay)(NodeHandle node);

    void (*setVideoControls)(NodeHandle node, Arkoala_Bool controls);
    void (*resetVideoControls)(NodeHandle node);

    void (*setVideoObjectFit)(NodeHandle node, Arkoala_Int32 objectFit);
    void (*resetVideoObjectFit)(NodeHandle node);

    void (*setVideoLoop)(NodeHandle node, Arkoala_Bool loop);
    void (*resetVideoLoop)(NodeHandle node);

    void (*setVideoMute)(NodeHandle node, Arkoala_Bool mute);
    void (*resetVideoMute)(NodeHandle node);

    void (*setVideoOptions)(NodeHandle node, Arkoala_CharPtr src);
    void (*resetVideoOptions)(NodeHandle node);
    void (*setVideoSrcResource)(NodeHandle node, Arkoala_Int32 id, Arkoala_Int32 type, Arkoala_CharPtr name,
        Arkoala_CharPtr bundleName, Arkoala_CharPtr moduleName);
};

struct ArkUIVideoControllerModifierAPI {
    NodeHandle (*getVideoController)(NodeHandle node);
    void (*setVideoStart)(NodeHandle node);
    void (*setVideoStop)(NodeHandle node);
    void (*setVideoPause)(NodeHandle node);
};

struct ArkUIGridModifierAPI {
    void (*setGridColumnsTemplate)(NodeHandle node, Arkoala_CharPtr temp);
    void (*resetGridColumnsTemplate)(NodeHandle node);
    void (*setGridColumnsGap)(NodeHandle node, Arkoala_Float32 gap, Arkoala_Int32 unit);
    void (*resetGridColumnsGap)(NodeHandle node);
    void (*setGridRowsGap)(NodeHandle node, Arkoala_Float32 gap, Arkoala_Int32 unit);
    void (*resetGridRowsGap)(NodeHandle node);
    void (*setGridScrollBar)(NodeHandle node, Arkoala_Int32 bar);
    void (*resetGridScrollBar)(NodeHandle node);
    void (*setGridRowsTemplate)(NodeHandle node, Arkoala_CharPtr temp);
    void (*resetGridRowsTemplate)(NodeHandle node);
    void (*setGridCachedCount)(NodeHandle node, Arkoala_Int32 value);
};

struct ArkUIGridItemModifierAPI {
    void (*setGridItemColumnStart)(NodeHandle node, Arkoala_Int32 start);
    void (*resetGridItemColumnStart)(NodeHandle node);
    void (*setGridItemColumnEnd)(NodeHandle node, Arkoala_Int32 end);
    void (*resetGridItemColumnEnd)(NodeHandle node);
};

struct ArkUIScrollModifierAPI {
    void (*setScrollScrollBar)(NodeHandle node, Arkoala_Int32 state);
    void (*resetScrollScrollBar)(NodeHandle node);
};

struct ArkUIScrollBarModifierAPI {
    void (*setScrollBarDirection)(NodeHandle node, Arkoala_Int32 direction);
    void (*resetScrollBarDirection)(NodeHandle node);
    void (*setScrollBarState)(NodeHandle node, Arkoala_Int32 state);
    void (*resetScrollBarState)(NodeHandle node);
    void (*setScrollBarScroller)(NodeHandle node, NodeHandle controller);
};

struct ArkUIScrollerModifierAPI {
    NodeHandle (*getScroller)(NodeHandle node);
    void (*bindScroller)(NodeHandle node, NodeHandle scroller);
    void (*setScrollToIndex)(NodeHandle node, Arkoala_Int32 value);
    void (*scrollBy)(NodeHandle node, Arkoala_Float32* values, Arkoala_Int32* units);
    void (*getCurrentOffset)(NodeHandle controlle, Arkoala_Float32* out);
};

struct ArkUITabsModifierAPI {
    void (*setTabsBarPosition)(NodeHandle node, Arkoala_Int32 value);
    void (*setTabsVertical)(NodeHandle node, Arkoala_Bool value);
    void (*setTabsScrollable)(NodeHandle node, Arkoala_Bool value);
};

struct ArkUITabContentModifierAPI {
    void (*setTabContentBuilder)(NodeHandle node, Arkoala_Int32 methodId);
    void (*setTabContentLabel)(NodeHandle node, Arkoala_CharPtr label);
};

struct ArkUITabsControllerModifierAPI {
    NodeHandle (*getTabsController)(NodeHandle node);
};

struct ArkUIGestureModifierAPI {
    void (*tapGestureAsyncEvent)(
        NodeHandle nodePtr, Arkoala_Int32 mask, Arkoala_Int32 priority, Arkoala_Int32 count, Arkoala_Int32 fingers);
    void (*longPressGestureAsyncEvent)(NodeHandle nodePtr, Arkoala_Int32 mask, Arkoala_Int32 priority,
        Arkoala_Int32 fingers, Arkoala_Int32 repeat, Arkoala_Int32 duration, Arkoala_Int32* event);
    void (*panGestureAsyncEvent)(NodeHandle nodePtr, Arkoala_Int32 mask, Arkoala_Int32 priority, Arkoala_Int32 fingers,
        Arkoala_Int32 direction, Arkoala_Int32 distance, Arkoala_Int32* event);
    void (*pinchGestureAsyncEvent)(NodeHandle nodePtr, Arkoala_Int32 mask, Arkoala_Int32 priority,
        Arkoala_Int32 fingers, Arkoala_Int32 distance, Arkoala_Int32* event);
    void (*groupGestureAsyncEvent)(NodeHandle nodePtr, Arkoala_Int32 mode, Arkoala_Int32* event);
    void (*notifyResetGestureAsyncEvent)(NodeHandle nodePtr, Arkoala_Int32 subKind);
};

struct ArkUISliderModifierAPI {
    void (*setSliderOptionValue)(NodeHandle node, Arkoala_Int32 value);
    void (*setSliderOptionValueMin)(NodeHandle node, Arkoala_Int32 value);
    void (*setSliderOptionValueMax)(NodeHandle node, Arkoala_Int32 value);
    void (*setSliderOptionStep)(NodeHandle node, Arkoala_Int32 value);
    void (*setSliderOptionStyle)(NodeHandle node, Arkoala_Int32 value);
    void (*setSliderOptionDirection)(NodeHandle node, Arkoala_Int32 value);
    void (*setSliderOptionReverse)(NodeHandle node, Arkoala_Bool value);
    void (*setSliderShowSteps)(NodeHandle node, Arkoala_Bool value);
    void (*setBlockColor)(NodeHandle node, Arkoala_Int32 value);
    void (*setTrackColor)(NodeHandle node, Arkoala_Int32 value);
    void (*setSelectedColor)(NodeHandle node, Arkoala_Int32 value);
    void (*setTrackThickness)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setSliderBlockSize)(NodeHandle node, Arkoala_Float32* value);
};

struct ArkUIProgressModifierAPI {
    void (*setProgressValue)(NodeHandle node, Arkoala_Float32 value);
    void (*setProgressColor)(NodeHandle node, Arkoala_Int32* colors, Arkoala_Float32* offsets, Arkoala_Int32 length);
    void (*setProgressInit)(NodeHandle node, Arkoala_Float32 value, Arkoala_Float32 total, Arkoala_Int32 type);
    void (*setProgressStyleOptions)(NodeHandle node, Arkoala_Float32* value);
    void (*setCapsuleStyleOptions)(
        NodeHandle node, Arkoala_Float32* value, Arkoala_CharPtr content, Arkoala_CharPtr fontFamily);
    void (*setRingStyleOptions)(NodeHandle node, Arkoala_Float32* value);
    void (*setLinearStyleOptions)(NodeHandle node, Arkoala_Float32* value);
    void (*setEclipseStyleOptions)(NodeHandle node, Arkoala_Bool value);
};

struct ArkUINavDestinationModifierAPI {
    void (*setHideTitleBar)(NodeHandle node, Arkoala_Bool value);
};

struct ArkUITextAreaModifierAPI {
    void (*setTextAreaFontColor)(NodeHandle node, Arkoala_Int32 color);
    void (*setTextAreaFontSize)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setTextAreaMaxLength)(NodeHandle node, Arkoala_Int32 value);
    void (*setTextAreaShowCounter)(NodeHandle node, Arkoala_Bool value);
    void (*setTextAreaTextAlign)(NodeHandle node, Arkoala_Int32 value);
    void (*setTextAreaMaxLines)(NodeHandle node, Arkoala_Int32 value);
    void (*setTextAreaPlaceholder)(NodeHandle node, Arkoala_CharPtr value);
    void (*setTextAreaText)(NodeHandle node, Arkoala_CharPtr value);
};

struct ArkUITextInputModifierAPI {
    NodeHandle (*getTextInputController)(NodeHandle node);
    void (*setTextInputPlaceholderString)(NodeHandle node, Arkoala_CharPtr value);
    void (*setTextInputPlaceholderResource)(NodeHandle node, Arkoala_Int32 id, Arkoala_Int32 type, Arkoala_CharPtr name,
        Arkoala_CharPtr bundleName, Arkoala_CharPtr moduleName);
    void (*setTextInputTextString)(NodeHandle node, Arkoala_CharPtr value);
    void (*setTextInputTextResource)(NodeHandle node, Arkoala_Int32 id, Arkoala_Int32 type, Arkoala_CharPtr name,
        Arkoala_CharPtr bundleName, Arkoala_CharPtr moduleName);
    void (*setTextInputFontSize)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 units);
    void (*setTextInputFontWeight)(NodeHandle node, Arkoala_Int32 value);
    void (*setTextInputAlignment)(NodeHandle node, Arkoala_Int32 value);
    void (*setTextInputMaxLines)(NodeHandle node, Arkoala_Int32 value);
    void (*setTextInputFontColor)(NodeHandle node, Arkoala_Int32 color);
    void (*setTextInputFontFamily)(NodeHandle node, Arkoala_CharPtr value);
};

struct ArkUIWebModifierAPI {
    NodeHandle (*getWebController)(NodeHandle node);
    NodeHandle (*getWebviewController)(NodeHandle node);
    void (*setWebOptions)(NodeHandle node, Arkoala_CharPtr value);
    void (*setWebSrcResources)(NodeHandle node, Arkoala_Int32 id, Arkoala_Int32 type, Arkoala_CharPtr name,
        Arkoala_CharPtr bundleName, Arkoala_CharPtr moduleName);
    void (*setWebMixedMode)(NodeHandle node, Arkoala_Int32 value);
};

struct ArkUIBlankModifierAPI {};

struct ArkUICheckboxModifierAPI {
    void (*setCheckboxSelect)(NodeHandle node, Arkoala_Bool value);
    void (*setCheckboxMark)(NodeHandle node, Arkoala_Int32 color, Arkoala_Float32 sizeValue, Arkoala_Int32 sizeUnit,
        Arkoala_Float32 strokeWidthValue, Arkoala_Int32 strokeWidthUnit);
    void (*setCheckboxSelectedColor)(NodeHandle node, Arkoala_Int32 color);
    void (*setCheckboxUnselectedColor)(NodeHandle node, Arkoala_Int32 color);
    void (*setCheckboxName)(NodeHandle node, Arkoala_CharPtr value);
    void (*setCheckboxGroup)(NodeHandle node, Arkoala_CharPtr value);
};

struct ArkUICheckboxGroupModifierAPI {
    void (*setCheckboxGroupSelectAll)(NodeHandle node, Arkoala_Bool value);
    void (*setCheckboxGroupName)(NodeHandle node, Arkoala_CharPtr value);
};

struct ArkUIMenuModifierAPI {
    void (*setMenuFontColor)(NodeHandle node, int color);
    void (*setMenuFontSize)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setMenuFont)(NodeHandle node, Arkoala_Float32* fontSize, Arkoala_Int32 fontWeight, Arkoala_Int32 fontStyle,
        Arkoala_CharPtr fontFamily);
};

struct ArkUIMenuItemModifierAPI {
    void (*setMenuItemContent)(NodeHandle node, const char* value);
    void (*setMenuItemContentFont)(NodeHandle node, Arkoala_Float32* fontSize, Arkoala_Int32 fontWeight,
        Arkoala_Int32 fontStyle, Arkoala_CharPtr fontFamily);
    void (*setMenuItemContentFontColor)(NodeHandle node, Arkoala_Int32 color);
    void (*setMenuItemLabelFont)(NodeHandle node, Arkoala_Float32* fontSize, Arkoala_Int32 fontWeight,
        Arkoala_Int32 fontStyle, Arkoala_CharPtr fontFamily);
    void (*setMenuItemLabelFontColor)(NodeHandle node, Arkoala_Int32 color);
    void (*setMenuItemLabelInfo)(NodeHandle node, Arkoala_CharPtr value);
};

struct ArkUIMenuItemGroupModifierAPI {
    void (*setMenuItemGroupHeader)(NodeHandle node, Arkoala_CharPtr value);
    void (*setMenuItemGroupFooter)(NodeHandle node, Arkoala_CharPtr value);
};

struct ArkUIToggleModifierAPI {
    void (*setToggleOptions)(NodeHandle node, Arkoala_Int32 type, Arkoala_Bool isOn);
    void (*setToggleSelectedColor)(NodeHandle node, Arkoala_Int32 value);
    void (*setSwitchPointColor)(NodeHandle node, Arkoala_Int32 value);
};

struct ArkUINavigationModifierAPI {
    void (*setHideBackButton)(NodeHandle node, Arkoala_Bool value);
    void (*setHideNavBar)(NodeHandle node, Arkoala_Bool value);
    void (*setHideNavigationTitleBar)(NodeHandle node, Arkoala_Bool value);
    void (*setHideToolBar)(NodeHandle node, Arkoala_Bool value);

    void (*setNavigationMode)(NodeHandle node, Arkoala_Int32 value);
    void (*setNavBarPosition)(NodeHandle node, Arkoala_Int32 value);
    void (*setNavBarWidth)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setTitleMode)(NodeHandle node, Arkoala_Int32 value);
};

struct ArkUIGaugeModifierAPI {
    void (*setGaugeStrokeWidth)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setGaugeStartAngle)(NodeHandle node, Arkoala_Float32 value);
    void (*setGaugeValue)(NodeHandle node, Arkoala_Float32 value);
};

struct ArkUIBadgeModifierAPI {
    void (*setBadgeParameters)(NodeHandle node, Arkoala_Int32* intValue, Arkoala_Float32* floatValue);
    void (*setBadgeValue)(NodeHandle node, Arkoala_CharPtr value);
    void (*setBadgeCount)(NodeHandle node, Arkoala_Int32 value);
    void (*setBadgeMaxCount)(NodeHandle node, Arkoala_Int32 value);
    void (*setBadgeFontWeight)(NodeHandle node, Arkoala_Int32 value);
};

struct ArkUIRefreshModifierAPI {
    void (*setRefreshFriction)(NodeHandle node, Arkoala_Int32 value);
};

struct ArkUIHyperlinkModifierAPI {
    void (*setHyperlinkAddress)(NodeHandle node, Arkoala_CharPtr value);
    void (*setHyperlinkContent)(NodeHandle node, Arkoala_CharPtr value);
};

struct ArkUIAlphabetIndexerModifierAPI {
    void (*selectIndexerColor)(NodeHandle node, Arkoala_Int32 color);
    void (*setIndexerPopupColor)(NodeHandle node, Arkoala_Int32 color);
    void (*selectIndexerBackgroundColor)(NodeHandle node, Arkoala_Int32 color);
    void (*setIndexerPopupBackground)(NodeHandle node, Arkoala_Int32 color);
    void (*selectIndexerFont)(NodeHandle node, Arkoala_Float32* fontSize, Arkoala_Int32 fontWeight,
        Arkoala_Int32 fontStyle, Arkoala_CharPtr fontFamily);
    void (*setIndexerPopupFont)(NodeHandle node, Arkoala_Float32* fontSize, Arkoala_Int32 fontWeight,
        Arkoala_Int32 fontStyle, Arkoala_CharPtr fontFamily);
    void (*setAlphabetIndexerInit)(
        NodeHandle node, Arkoala_CharPtr* array, Arkoala_Int32 selected, Arkoala_Int32 length);
};

struct ArkUILoadingProgressModifierAPI {
    void (*setLoadingProgressColor)(NodeHandle node, Arkoala_Int32 value);
    void (*setLoadingProgressEnableLoading)(NodeHandle node, Arkoala_Bool value);
};

struct ArkUIImageAnimatorModifierAPI {
    void (*setImageAnimatorImages)(
        NodeHandle node, Arkoala_CharPtr* src, Arkoala_Int32 srcLength, Arkoala_Float32* info, Arkoala_Int32 length);

    void (*setImageAnimatorDuration)(NodeHandle node, Arkoala_Int32 value);
    void (*setImageAnimatorFillMode)(NodeHandle node, Arkoala_Int32 value);
    void (*setImageAnimatorFixedSize)(NodeHandle node, Arkoala_Bool value);

    void (*setImageAnimatorIteration)(NodeHandle node, Arkoala_Int32 value);
    void (*setImageAnimatorIsReverse)(NodeHandle node, Arkoala_Bool value);
    void (*setImageAnimatorState)(NodeHandle node, Arkoala_Int32 value);
};

struct ArkUIRatingModifierAPI {
    void (*setRatingValue)(NodeHandle node, Arkoala_Float32 ratingScore, Arkoala_Bool indicator);
    void (*setRatingStars)(NodeHandle node, Arkoala_Int32 value);
    void (*setRatingStarStyle)(
        NodeHandle node, Arkoala_CharPtr backgroundUri, Arkoala_CharPtr foregroundUri, Arkoala_CharPtr secondaryUri);
};

struct ArkUISearchModifierAPI {
    void (*setSearchValue)(NodeHandle node, Arkoala_CharPtr value, Arkoala_CharPtr placeholder, Arkoala_CharPtr icon);
    void (*setSearchPlaceholderFont)(NodeHandle node, Arkoala_Float32* fontSize, Arkoala_Int32 fontWeight,
        Arkoala_Int32 fontStyle, Arkoala_CharPtr fontFamily);
    void (*setSearchTextAlign)(NodeHandle node, Arkoala_Int32 value);
    void (*setSearchTextFont)(NodeHandle node, Arkoala_Float32* fontSize, Arkoala_Int32 fontWeight,
        Arkoala_Int32 fontStyle, Arkoala_CharPtr fontFamily);
};

struct ArkUISearchControllerModifierAPI {
    NodeHandle (*getSearchController)(NodeHandle node);
    void (*setSearchCaretPosition)(NodeHandle node, Arkoala_Int32 value);
    void (*setSearchStopEditing)(NodeHandle node);
};

struct ArkUITextClockModifierAPI {
    void (*setTextClockFormat)(NodeHandle node, Arkoala_CharPtr value);
    void (*setTimeZoneOffset)(NodeHandle node, Arkoala_Int32 value);
    void (*setTextClockFontColor)(NodeHandle node, Arkoala_Int32 value);
    void (*setTextClockFontSize)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setTextClockFontStyle)(NodeHandle node, Arkoala_Int32 value);
    void (*setTextClockFontWeight)(NodeHandle node, Arkoala_Int32 value);
    void (*setTextClockFontFamily)(NodeHandle node, Arkoala_CharPtr value);
};

struct ArkUITextClockControllerModifierAPI {
    NodeHandle (*getTextClockController)(NodeHandle node);
    void (*setTextClockStart)(NodeHandle node);
    void (*setTextClockStop)(NodeHandle node);
};

struct ArkUITextPickerModifierAPI {
    void (*setDisappearTextStyle)(NodeHandle node, Arkoala_Int32 color, Arkoala_Float32* fontSize,
        Arkoala_Int32 fontWeight, Arkoala_Int32 fontStyle, Arkoala_CharPtr fontFamily);
    void (*setTextPickerTextStyle)(NodeHandle node, Arkoala_Int32 color, Arkoala_Float32* fontSize,
        Arkoala_Int32 fontWeight, Arkoala_Int32 fontStyle, Arkoala_CharPtr fontFamily);
    void (*setSelectedTextStyle)(NodeHandle node, Arkoala_Int32 color, Arkoala_Float32* fontSize,
        Arkoala_Int32 fontWeight, Arkoala_Int32 fontStyle, Arkoala_CharPtr fontFamily);
    void (*setTextPickerRange)(
        NodeHandle node, Arkoala_CharPtr* iconArray, Arkoala_CharPtr* textArray, Arkoala_Int32 length);
    void (*setTextPickerSelected)(NodeHandle node, Arkoala_Int32* selected, Arkoala_Int32 length);
    void (*setTextPickerValue)(NodeHandle node, Arkoala_CharPtr* values, Arkoala_Int32 length);
};

struct ArkUITextTimerModifierAPI {
    void (*setTextTimerFormat)(NodeHandle node, Arkoala_CharPtr value);
    void (*setTextTimerOptions)(NodeHandle node, Arkoala_Bool isCountDown, Arkoala_Int32 count);
    void (*setTextTimerFontColor)(NodeHandle node, Arkoala_Int32 value);
    void (*setTextTimerFontSize)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setTextTimerFontStyle)(NodeHandle node, Arkoala_Int32 value);
    void (*setTextTimerFontWeight)(NodeHandle node, Arkoala_Int32 value);
    void (*setTextTimerFontFamily)(NodeHandle node, Arkoala_CharPtr value);
};

struct ArkUITextTimerControllerModifierAPI {
    NodeHandle (*getTextTimerController)(NodeHandle node);
    void (*setTextTimerStart)(NodeHandle node);
    void (*setTextTimerPause)(NodeHandle node);
    void (*setTextTimerReset)(NodeHandle node);
};
struct ArkUIMarqueeModifierAPI {
    void (*setMarqueeValue)(NodeHandle node, Arkoala_CharPtr value, Arkoala_Bool playerStatus,
        Arkoala_Float32 scrollAmount, Arkoala_Int32 loop, Arkoala_Bool direction);
};

struct ArkUISpanModifierAPI {
    void (*setSpanFont)(NodeHandle node, Arkoala_Float32* fontSize, Arkoala_Int32 fontWeight, Arkoala_Int32 fontStyle,
        Arkoala_CharPtr fontFamily);
    void (*setSpanLetterSpacing)(NodeHandle node, Arkoala_Float32* space);
    void (*setSpanTextCase)(NodeHandle node, Arkoala_Int32 value);
    void (*setSpanLabel)(NodeHandle node, Arkoala_CharPtr value);
};

struct ArkUISelectModifierAPI {
    void (*setSelectArrowPosition)(NodeHandle node, Arkoala_Int32 value);
    void (*setSelectSpace)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setSelectParam)(NodeHandle node, Arkoala_CharPtr* array, Arkoala_Int32 length);
};

/** Common for all API variants.*/
struct ArkUIAnyAPI {
    Arkoala_Int32 version;
    void (*setCallbackMethod)(ArkUIAPICallbackMethod* method);
};

struct ArkUIGridColModifierAPI {
    void (*setGridColSpan)(NodeHandle node, const Arkoala_Int32* span, Arkoala_Int32 length);
    void (*setGridColOffset)(NodeHandle node, const Arkoala_Int32* offset, Arkoala_Int32 length);
    void (*setGridColOrder)(NodeHandle node, const Arkoala_Int32* order, Arkoala_Int32 length);
};

struct ArkUIGridRowModifierAPI {
    void (*setGridRowColumns)(NodeHandle node, const Arkoala_Int32* column, Arkoala_Int32 length);
    void (*setGridRowDirection)(NodeHandle node, const Arkoala_Int32 value);
    void (*setGridRowGutter)(NodeHandle node, const Arkoala_Float32* gutterValue, const Arkoala_Int32* gutterUnit,
        Arkoala_Int32 valueLength, Arkoala_Int32 unitLength);
    void (*setGridRowBreakpoints)(NodeHandle node, const Arkoala_Float32* Value, const Arkoala_Int32* unit,
        Arkoala_Int32 valueLength, Arkoala_Int32 unitLength, Arkoala_Int32 reference);
};

struct ArkUIRadioModifierAPI {
    void (*setRadioChecked)(NodeHandle node, Arkoala_Bool value);
    void (*setRadioGroup)(NodeHandle node, Arkoala_CharPtr group, Arkoala_CharPtr value);
};

struct ArkUIPatternLockControllerModifierAPI {
    NodeHandle (*getPatternLockController)(NodeHandle node);
    void (*setPatternLockReset)(NodeHandle node);
};

struct ArkUIPatternLockModifierAPI {
    void (*setPatternLockSideLength)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setPatternLockCircleRadius)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setPatternLockSelectedColor)(NodeHandle node, Arkoala_Int32 value);
    void (*setPatternLockRegularColor)(NodeHandle node, Arkoala_Int32 value);
    void (*setPatternLockActiveColor)(NodeHandle node, Arkoala_Int32 value);
    void (*setPatternLockPathColor)(NodeHandle node, Arkoala_Int32 value);
    void (*setPatternLockPathStrokeWidth)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setPatternLockAutoReset)(NodeHandle node, Arkoala_Bool value);
};
struct ArkUIRichEditorModifierAPI {};

struct ArkUIRichEditorControllerModifierAPI {
    NodeHandle (*getRichEditorController)(NodeHandle node);
};

struct ArkUIDataPanelModifierAPI {
    void (*setDataPanelCloseEffect)(NodeHandle node, Arkoala_Bool value);
    void (*setDataPanelStrokeWidth)(NodeHandle node, Arkoala_Float32 value, Arkoala_Int32 unit);
    void (*setDataPanelTrackShadow)(NodeHandle node, Arkoala_Float32* shadow, Arkoala_Int32 length,
        Arkoala_Int32* colorLength, Arkoala_Int32* colors, Arkoala_Float32* offsets);
    void (*setDataPanelTrackShadowDisable)(NodeHandle node);
    void (*setDataPanelInit)(
        NodeHandle node, Arkoala_Int32* data, Arkoala_Int32 length, Arkoala_Int32 max, Arkoala_Int32 type);
    void (*setDataPanelValueColors)(NodeHandle node, Arkoala_Int32 length, Arkoala_Int32* colorLength,
        Arkoala_Int32* colors, Arkoala_Float32* offsets);
};

struct ArkUIQRCodeModifierAPI {
    void (*setQRCodeColor)(NodeHandle node, Arkoala_Int32 color);
    void (*setQRCodeValue)(NodeHandle node, Arkoala_CharPtr value);
};

struct ArkUITextAreaControllerModifierAPI {
    NodeHandle (*getTextAreaController)(NodeHandle node);
};

/**
 * An API to control an implementation. When making changes modifying binary layout,
 * i.e. adding new events - increase ARKUI_API_VERSION above for binary layout checks.
 */
struct ArkUINodeAPI {
    Arkoala_Int32 version;
    void (*setCallbackMethod)(ArkUIAPICallbackMethod* method);
    /**
     * Tree manipulations.
     */
    NodeHandle (*createNode)(Arkoala_CharPtr type, Arkoala_Int32 id, Arkoala_Int32 flags);
    void (*disposeNode)(NodeHandle node);
    // Returned pointer is valid only till node is alive.
    Arkoala_CharPtr (*getName)(NodeHandle node);
    Arkoala_Int32 (*getId)(NodeHandle node);
    void (*dump)(NodeHandle node);
    void (*addChild)(NodeHandle parent, NodeHandle child);
    void (*removeChild)(NodeHandle parent, NodeHandle child);
    void (*insertChildAfter)(NodeHandle parent, NodeHandle child, NodeHandle sibling);

    void (*setCustomCallback)(NodeHandle node, Arkoala_Int32 callbackId);
    Arkoala_Int32 (*measureLayoutAndDraw)(ArkUIAPIVMContext vmContext, NodeHandle node);
    Arkoala_Int32 (*measureNode)(ArkUIAPIVMContext vmContext, NodeHandle node, Arkoala_Float32* data);
    Arkoala_Int32 (*layoutNode)(ArkUIAPIVMContext vmContext, NodeHandle node, Arkoala_Float32* data);
    Arkoala_Int32 (*drawNode)(ArkUIAPIVMContext vmContext, NodeHandle node, Arkoala_Float32* data);

    void (*popPageToIndex)(Arkoala_Int32 index);
    void (*setRangeUpdater)(NodeHandle node, Arkoala_Int32 updaterId);
    void (*setLazyItemIndexer)(ArkUIAPIVMContext vmContext, NodeHandle node, Arkoala_Int32 indexerId);
    void (*setNavDestinationBackPressed)(ArkUIAPIVMContext vmContext, NodeHandle node, Arkoala_Int32 indexerId);
    void (*setChildTotalCount)(NodeHandle node, Arkoala_Int32 totalCount);

    // TODO: better typed API.
    void (*setAttribute)(NodeHandle node, Arkoala_CharPtr attribute, Arkoala_CharPtr value);
    // Returned pointer is valid only till node is alive.
    Arkoala_CharPtr (*getAttribute)(NodeHandle node, Arkoala_CharPtr attribute);
    void (*resetAttribute)(NodeHandle node, Arkoala_CharPtr attribute);

    Arkoala_Int32 (*indexerChecker)(ArkUIAPIVMContext context, NodeHandle node);

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

    void (*callContinuation)(Arkoala_Int32 continuationId, Arkoala_Int32 argCount, ArkUIAPIEventCallbackArg* args);
    Arkoala_Int32 (*startAnimation)(const ArkUIAPIAnimationSpec* spec, Arkoala_Int32 callbackId);

    Arkoala_Int32 (*setVsyncCallback)(ArkUIAPIVMContext vmContext, Arkoala_Int32 device, Arkoala_Int32 callbackId);
    void (*unblockVsyncWait)(ArkUIAPIVMContext vmContext, Arkoala_Int32 device);

    /**
     * notify update style finish for native backend.
     */
    void (*applyModifierFinish)(NodeHandle nodePtr);

    // animation
    void (*openImplicitAnimation)(
        ArkUIAPIVMContext vmContext, Arkoala_Int32 curve, Arkoala_Float32* options, Arkoala_Int32 callbackId);
    void (*closeImplicitAnimation)();

    // attributes function
    ArkUICommonModifierAPI (*getCommonModifier)();
    ArkUIButtonModifierAPI (*getButtonModifier)();
    ArkUITextModifierAPI (*getTextModifier)();
    ArkUIImageModifierAPI (*getImageModifier)();
    ArkUISwiperModifierAPI (*getSwiperModifier)();
    ArkUIStackModifierAPI (*getStackModifier)();
    ArkUINavigatorModifierAPI (*getNavigatorModifier)();
    ArkUIVideoModifierAPI (*getVideoModifier)();
    ArkUIVideoControllerModifierAPI (*getVideoControllerModifier)();
    ArkUIColumnModifierAPI (*getColumnModifier)();
    ArkUIRowModifierAPI (*getRowModifier)();
    ArkUIDividerModifierAPI (*getDividerModifier)();
    ArkUIFlexModifierAPI (*getFlexModifier)();
    ArkUIListModifierAPI (*getListModifier)();
    ArkUIGridModifierAPI (*getGridModifier)();
    ArkUIGridItemModifierAPI (*getGridItemModifier)();
    ArkUIScrollModifierAPI (*getScrollModifier)();
    ArkUIScrollBarModifierAPI (*getScrollBarModifier)();
    ArkUIScrollerModifierAPI (*getScrollerModifier)();
    ArkUITabsModifierAPI (*getTabsModifier)();
    ArkUITabContentModifierAPI (*getTabContentModifier)();
    ArkUITabsControllerModifierAPI (*getTabsControllerModifier)();
    ArkUISwiperControllerModifierAPI (*getSwiperControllerModifier)();
    ArkUIGestureModifierAPI (*getGestureModifier)();
    ArkUISliderModifierAPI (*getSliderModifier)();
    ArkUIProgressModifierAPI (*getProgressModifier)();
    ArkUINavDestinationModifierAPI (*getNavDestinationModifier)();
    ArkUITextAreaModifierAPI (*getTextAreaModifier)();
    ArkUITextInputModifierAPI (*getTextInputModifier)();
    ArkUIWebModifierAPI (*getWebModifier)();
    ArkUIToggleModifierAPI (*getToggleModifier)();
    ArkUIBlankModifierAPI (*getBlankModifier)();
    ArkUICheckboxModifierAPI (*getCheckboxModifier)();
    ArkUICheckboxGroupModifierAPI (*getCheckboxGroupModifier)();
    ArkUIMenuModifierAPI (*getMenuModifier)();
    ArkUIMenuItemModifierAPI (*getMenuItemModifier)();
    ArkUIMenuItemGroupModifierAPI (*getMenuItemGroupModifier)();
    ArkUIAlphabetIndexerModifierAPI (*getAlphabetIndexerModifier)();
    ArkUIListItemGroupModifierAPI (*getListItemGroupModifier)();
    ArkUINavigationModifierAPI (*getNavigationModifier)();
    ArkUIGaugeModifierAPI (*getGaugeModifier)();
    ArkUIBadgeModifierAPI (*getBadgeModifier)();
    ArkUIRefreshModifierAPI (*getRefreshModifier)();
    ArkUIHyperlinkModifierAPI (*getHyperlinkModifier)();
    ArkUILoadingProgressModifierAPI (*getLoadingProgressModifier)();
    ArkUIImageAnimatorModifierAPI (*getImageAnimatorModifier)();
    ArkUIRatingModifierAPI (*getRatingModifier)();
    ArkUISearchModifierAPI (*getSearchModifier)();
    ArkUISearchControllerModifierAPI (*getSearchControllerModifier)();
    ArkUITextClockModifierAPI (*getTextClockModifier)();
    ArkUITextClockControllerModifierAPI (*getTextClockControllerModifier)();
    ArkUITextPickerModifierAPI (*getTextPickerModifier)();
    ArkUITextTimerModifierAPI (*getTextTimerModifier)();
    ArkUITextTimerControllerModifierAPI (*getTextTimerControllerModifier)();
    ArkUISpanModifierAPI (*getSpanModifier)();
    ArkUISelectModifierAPI (*getSelectModifier)();
    ArkUIMarqueeModifierAPI (*getMarqueeModifier)();
    ArkUIGridColModifierAPI (*getGridColModifier)();
    ArkUIGridRowModifierAPI (*getGridRowModifier)();
    ArkUIRadioModifierAPI (*getRadioModifier)();
    ArkUIRichEditorModifierAPI (*getRichEditorModifier)();
    ArkUIRichEditorControllerModifierAPI (*getRichEditorControllerModifier)();
    ArkUIDataPanelModifierAPI (*getDataPanelModifier)();
    ArkUIQRCodeModifierAPI (*getQRCodeModifier)();
    ArkUITextAreaControllerModifierAPI (*getTextAreaControllerModifier)();
    ArkUIPatternLockControllerModifierAPI (*getPatternLockControllerModifier)();
    ArkUIPatternLockModifierAPI (*getPatternLockModifier)();
    ArkUIShapedCommonModifierAPI (*getShapedCommonModifier)();
    ArkUILineModifierAPI (*getLineModifier)();
    ArkUIPathModifierAPI (*getPathModifier)();
    ArkUIPolygonModifierAPI (*getPolygonModifier)();
    ArkUIRectModifierAPI (*getRectModifier)();
    ArkUIShapeModifierAPI (*getShapeModifier)();
};

struct ArkUIBasicNodeAPI {
    Arkoala_Int32 version;
    void (*setCallbackMethod)(ArkUIAPICallbackMethod* method);
    /**
     * Tree manipulations.
     */
    NodeHandle (*createNode)(Arkoala_CharPtr type, Arkoala_Int32 id, Arkoala_Int32 flags);
    void (*disposeNode)(NodeHandle node);
    // Returned pointer is valid only till node is alive.
    Arkoala_CharPtr (*getName)(NodeHandle node);
    Arkoala_Int32 (*getId)(NodeHandle node);
    void (*dump)(NodeHandle node);
    void (*addChild)(NodeHandle parent, NodeHandle child);
    void (*removeChild)(NodeHandle parent, NodeHandle child);
    void (*insertChildAfter)(NodeHandle parent, NodeHandle child, NodeHandle sibling);

    void (*setAttribute)(NodeHandle node, Arkoala_CharPtr attribute, Arkoala_CharPtr value);
    // Returned pointer is valid only till node is alive.
    Arkoala_CharPtr (*getAttribute)(NodeHandle node, Arkoala_CharPtr attribute);
    void (*resetAttribute)(NodeHandle node, Arkoala_CharPtr attribute);
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

    void (*drawCircle)(ArkUICanvasHandle canvas, Arkoala_Float32 x, Arkoala_Float32 x, Arkoala_Float32 y,
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
