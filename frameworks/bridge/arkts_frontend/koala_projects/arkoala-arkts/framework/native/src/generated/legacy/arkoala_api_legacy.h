/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_API_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_API_H

/*
 * ATTENTION. Keep this file self contained.
 * Make sure it has all necessary type declarations.
 * Do not include anything to this header file.
 */

#ifdef __cplusplus
extern "C" {
#endif

#define ARKUI_FULL_API_VERSION 96
// When changing ARKUI_BASIC_API_VERSION, ARKUI_FULL_API_VERSION must be
// increased as well.
#define ARKUI_NODE_API_VERSION 96

#define ARKUI_BASIC_API_VERSION 8
#define ARKUI_EXTENDED_API_VERSION 8
#define ARKUI_NODE_GRAPHICS_API_VERSION 5
#define ARKUI_NODE_MODIFIERS_API_VERSION 8
#define ARKUI_AUTO_GENERATE_NODE_ID -2
#define ARKUI_MAX_ANCHOR_ID_SIZE 50
enum ArkUIAPIVariantKind {
    BASIC = 1,
    FULL = 2,
    GRAPHICS = 3,
    EXTENDED = 4,
    COUNT = EXTENDED + 1,
};

typedef int ArkUI_Bool;
typedef int ArkUI_Int32;
typedef unsigned int ArkUI_Uint32;
typedef long long ArkUI_Int64;
typedef float ArkUI_Float32;
typedef double ArkUI_Float64;
typedef const char* ArkUI_CharPtr;

// Several opaque struct declarations.
struct _ArkUIVMContext;
struct _ArkUIPipelineContext;
struct _ArkUIVMObject;
struct _ArkUINode;
struct _ArkUICanvas;
struct _ArkUIPaint;
struct _ArkUIFont;
struct _ArkUIXComponentController;
struct _ArkUINodeAdapter;
struct _ArkUINodeContent;
struct ArkUI_WaterFlowSectionOption;

typedef _ArkUINode* ArkUINodeHandle;
typedef _ArkUIVMContext* ArkUIVMContext;
typedef _ArkUIPipelineContext* ArkUIPipelineContext;
typedef _ArkUIVMObject* ArkUIVMObject;
typedef _ArkUICanvas* ArkUICanvasHandle;
typedef _ArkUIPaint* ArkUIPaintHandle;
typedef _ArkUIFont* ArkUIFontHandle;
typedef _ArkUIXComponentController* ArkUIXComponentControllerHandle;
typedef _ArkUINodeAdapter* ArkUINodeAdapterHandle;
typedef _ArkUINodeContent* ArkUINodeContentHandle;

struct ArkUICanvasArcOptions {
    ArkUI_Float32 x;
    ArkUI_Float32 y;
    ArkUI_Float32 radius;
    ArkUI_Float32 startAngle;
    ArkUI_Float32 endAngle;
    ArkUI_Bool counterclockwise;
};
typedef ArkUI_WaterFlowSectionOption* ArkUIWaterFlowSectionOption;

struct ArkUIRect {
    ArkUI_Float32 x;
    ArkUI_Float32 y;
    ArkUI_Float32 width;
    ArkUI_Float32 height;
};

struct ArkUICornerRadius {
    ArkUI_Float32 topLeft;
    ArkUI_Float32 topRight;
    ArkUI_Float32 bottomLeft;
    ArkUI_Float32 bottomRight;
};

typedef struct _ArkUIDialog* ArkUIDialogHandle;

struct ArkUITouchPoint {
    ArkUI_Int32 id;
    ArkUI_Int64 pressedTime;
    ArkUI_Float32 screenX;
    ArkUI_Float32 screenY;
    ArkUI_Float32 windowX;
    ArkUI_Float32 windowY;
    ArkUI_Float32 nodeX;
    ArkUI_Float32 nodeY;
    ArkUI_Float64 pressure;
    ArkUI_Float32 contactAreaWidth;
    ArkUI_Float32 contactAreaHeight;
    ArkUI_Float64 tiltX;
    ArkUI_Float64 tiltY;
    ArkUI_Float32 toolX;
    ArkUI_Float32 toolY;
    ArkUI_Float32 toolWidth;
    ArkUI_Float32 toolHeight;
    ArkUI_Float32 rawX;
    ArkUI_Float32 rawY;
    ArkUI_Int32 toolType;
};

/**
 * @brief 定义手势事件类型。
 *
 * @since 12
 */
typedef enum {
    /** 手势事件触发。 */
    ARKUI_GESTURE_EVENT_ACTION_ACCEPT = 0x01,

    /** 手势事件更新。 */
    ARKUI_GESTURE_EVENT_ACTION_UPDATE = 0x02,

    /** 手势事件结束。 */
    ARKUI_GESTURE_EVENT_ACTION_END = 0x04,

    /** 手势事件取消。 */
    ARKUI_GESTURE_EVENT_ACTION_CANCEL = 0x08,
} ArkUIGestureEventActionType;

struct ArkUIHistoryTouchEvent {
    ArkUI_Int32 action;
    ArkUI_Int32 sourceType;
    ArkUI_Int64 timeStamp;
    ArkUITouchPoint actionTouchPoint;
    ArkUITouchPoint* touchPointes;
    ArkUI_Uint32 touchPointSize;
};

struct ArkUITouchEvent {
    ArkUI_Int32 action;
    /** Time stamp of the current event. */
    ArkUI_Int64 timeStamp;
    ArkUITouchPoint actionTouchPoint;
    ArkUITouchPoint* touchPointes;
    ArkUI_Uint32 touchPointSize;
    ArkUIHistoryTouchEvent* historyEvents;
    ArkUI_Uint32 historySize;
    ArkUI_Int32 sourceType;

    /**
     * @brief Prevents events from bubbling further to the parent node for processing.
     *
     */
    bool stopPropagation;

    /**
     * @brief Blocks the current node's default event handling behavior, allowing events
     * to bubble up further.
     *
     */
    bool preventDefault;

    ArkUI_Int32 subKind; // ArkUIEventSubKind actually
    ArkUI_Int32 interceptResult;
};

struct ArkUIMouseEvent {
    ArkUI_Int32 action;
    ArkUI_Int32 button;
    ArkUI_Int64 timeStamp;
    ArkUITouchPoint actionTouchPoint;
    ArkUI_Int32 subKind;
};

struct ArkUIStringAndFloat {
    ArkUI_Float32 value;
    ArkUI_CharPtr valueStr;
};

struct ArkUIResourceColorType {
    ArkUI_Uint32 number;
    ArkUI_CharPtr string;
};

struct ArkUIIconsStruct {
    ArkUI_CharPtr ShowIconInfo;
    ArkUI_CharPtr HiddenIconInfo;
    ArkUI_CharPtr SwitchingIconInfo;
};

struct ArkUIIconOptionsStruct {
    ArkUI_Float32 value;
    ArkUI_Int32 unit;
    ArkUI_Int32 color;
    ArkUI_CharPtr src;
};

struct ArkUIFontStruct {
    ArkUI_Float32 fontSizeNumber;
    ArkUI_Int32 fontSizeUnit;
    ArkUI_Int32 fontWeight;
    ArkUI_Int32 fontStyle;
    ArkUI_CharPtr* fontFamilies;
    ArkUI_Uint32 familyLength;
};

struct ArkUISearchButtonOptionsStruct {
    ArkUI_CharPtr value;
    ArkUI_Float32 sizeValue;
    ArkUI_Int32 sizeUnit;
    ArkUI_Int32 fontColor;
};

struct ArkUISizeType {
    ArkUI_Float32 value;
    ArkUI_Int32 unit;
    ArkUI_CharPtr string;
};

struct ArkUITextShadowStruct {
    ArkUI_Float32 radius;
    ArkUI_Uint32 type;
    ArkUI_Uint32 color;
    ArkUI_Float32 offsetX;
    ArkUI_Float32 offsetY;
    ArkUI_Uint32 fill;
};

struct ArkUIImagePropertiesStruct {
    ArkUI_CharPtr src;
    ArkUI_Float32 number[4];
    ArkUI_Int32 unit[4];
    char* calc[4];
    ArkUI_Int32 duration;
};

struct ArkUILengthType {
    ArkUI_CharPtr string;
    ArkUI_Float32 number;
    ArkUI_Int32 unit;
};

struct ArkUIResource {
    ArkUI_Int32 id;
    ArkUI_Int32 type;
    ArkUI_CharPtr name;
    ArkUI_CharPtr bundleName;
    ArkUI_CharPtr moduleName;
};

struct ArkUIResourceLength {
    ArkUI_Float32 value;
    ArkUI_Int32 unit;
    ArkUI_CharPtr string;
};
struct ArkUIPasswordIconType {
    ArkUI_CharPtr showResult;
    ArkUI_CharPtr showBundleName;
    ArkUI_CharPtr showModuleName;
    ArkUI_CharPtr hideResult;
    ArkUI_CharPtr hideBundleName;
    ArkUI_CharPtr hideModuleName;
};

struct ArkUIPlaceholderFontType {
    const struct ArkUILengthType* size;
    ArkUI_CharPtr weight;
    ArkUI_CharPtr* fontFamilies;
    ArkUI_Uint32 length;
    ArkUI_Int32 style;
    ArkUI_Int32 weightEnum;
};

struct ArkUIProgressStyle {
    ArkUI_Float32 strokeWidthValue;
    ArkUI_Int32 strokeWidthUnit;
    ArkUI_Float32 borderWidthValue;
    ArkUI_Int32 borderWidthUnit;
    ArkUI_Int32 scaleCount;
    ArkUI_Int32 status;
    ArkUI_Float32 scaleWidthValue;
    ArkUI_Int32 scaleWidthUnit;
    ArkUI_Float32 strokeRadiusValue;
    ArkUI_Int32 strokeRadiusUnit;
    ArkUI_Bool enableSmoothEffect;
    ArkUI_Float32 borderColor;
    ArkUI_CharPtr content;
    ArkUI_Float32 fontColor;
    ArkUI_Bool enableScanEffect;
    ArkUI_Bool shadow;
    ArkUI_Bool showDefaultPercentage;
    ArkUIFontStruct fontInfo;
};

struct ArkUIGradientType {
    const ArkUI_Uint32* color;
    const ArkUILengthType* offset;
    const ArkUI_Float32* weight;
    const ArkUI_Uint32* gradientLength;
    ArkUI_Uint32 length;
    ArkUI_Uint32 type;
};

struct ArkUIDimensionType {
    ArkUI_Float32 value;
    ArkUI_Int32 units;
};

struct ArkUIChainAnimationOptionsType {
    ArkUI_Float32 minSpace;
    ArkUI_Float32 maxSpace;
    ArkUI_Float32 conductivity;
    ArkUI_Float32 intensity;
    ArkUI_Float32 stiffness;
    ArkUI_Float32 damping;
    ArkUI_Int32 edgeEffect;
    ArkUI_Int32 minSpaceUnits;
    ArkUI_Int32 maxSpaceUnits;
};

struct ArkUIClipShapeOptions {
    ArkUI_Int32 type;
    ArkUI_Float32 width;
    ArkUI_Float32 height;
    ArkUI_Float32 radiusWidth;
    ArkUI_Float32 radiusHeight;
    ArkUI_CharPtr commands;
};

struct ArkUIPositionOptions {
    ArkUI_Float32 x;
    ArkUI_Float32 y;
};

struct ArkUICustomShadowOptions {
    ArkUI_Float32 radius;
    ArkUI_Float32 offsetX;
    ArkUI_Float32 offsetY;
    ArkUI_Int32 shadowType;
    ArkUI_Uint32 color;
    ArkUI_Int32 colorStrategy;
    ArkUI_Int32 fill;
};

struct ArkUIMaskOptions {
    ArkUI_Uint32 fill;
    ArkUI_Uint32 strokeColor;
    ArkUI_Float32 strokeWidth;
    ArkUI_Int32 type;
    ArkUI_Float32 width;
    ArkUI_Float32 height;
    ArkUI_Float32 radiusWidth;
    ArkUI_Float32 radiusHeight;
    ArkUI_CharPtr commands;
    ArkUI_Uint32 color;
    ArkUI_Float32 value;
    ArkUI_Float32 maxValue;
};

struct ArkUIConstraintSizeOptions {
    ArkUI_Float32 minWidth;
    ArkUI_Float32 maxWidth;
    ArkUI_Float32 minHeight;
    ArkUI_Float32 maxHeight;
};

struct ArkUIFlexOptions {
    ArkUI_Int32 direction;
    ArkUI_Int32 wrap;
    ArkUI_Int32 justifyContent;
    ArkUI_Int32 alignItems;
    ArkUI_Int32 alignContent;
};

struct ArkUIAnimationOptionType {
    ArkUI_Int32 duration;
    ArkUI_Int32 curve;
    ArkUI_Int32 delay;
    ArkUI_Int32 iteration;
    ArkUI_Int32 playMode;
    ArkUI_Float32 tempo;
};

struct ArkUITransformCenterType {
    ArkUI_Float32 centerX;
    ArkUI_Float32 centerY;
    ArkUI_Float32 centerZ;
};

struct ArkUIOpacityTransitionType {
    ArkUI_Float32 opacity;
    ArkUIAnimationOptionType animation;
};

struct ArkUIRotateTransitionType {
    ArkUI_Float32 xRotation;
    ArkUI_Float32 yRotation;
    ArkUI_Float32 zRotation;
    ArkUI_Float32 angle;
    ArkUI_Float32 perspective;
    ArkUIAnimationOptionType animation;
};

struct ArkUIScaleTransitionType {
    ArkUI_Float32 xScale;
    ArkUI_Float32 yScale;
    ArkUI_Float32 zScale;
    ArkUIAnimationOptionType animation;
};

struct ArkUITranslateTransitionType {
    ArkUI_Float32 xTransition;
    ArkUI_Float32 yTransition;
    ArkUI_Float32 zTransition;
    ArkUIAnimationOptionType animation;
};

struct ArkUIMoveTransitionType {
    ArkUI_Int32 edgeType;
    ArkUIAnimationOptionType animation;
};

struct ArkUIOffsetType {
    ArkUI_Float32 xComponent;
    ArkUI_Float32 yComponent;
};

struct ArkUIAnchorType {
    ArkUI_Float32 xCoordinate;
    ArkUI_Float32 yCoordinate;
};

struct ArkUIAlignRulesType {
    char (*anchorIds)[ARKUI_MAX_ANCHOR_ID_SIZE];
    ArkUI_Int32* alignTypes;
    ArkUI_Int32 anchorCount;
    ArkUI_Float32 biasHorizontalValue;
    ArkUI_Float32 biasVerticalValue;
};

struct ArkUIImageSizeType {
    ArkUI_Float32 xValue;
    ArkUI_Float32 yValue;
    ArkUI_Int32 xType;
    ArkUI_Int32 yType;
};

struct ArkUIScaleType {
    ArkUI_Float32 xValue;
    ArkUI_Float32 yValue;
};

struct ArkUIRotateType {
    ArkUI_Float32 xCoordinate;
    ArkUI_Float32 yCoordinate;
    ArkUI_Float32 zCoordinate;
    ArkUI_Float32 angle;
    ArkUI_Float32 sightDistance;
};

struct ArkUIBlurStyleOptionType {
    ArkUI_Int32 blurStyle;
    ArkUI_Int32 colorMode;
    ArkUI_Int32 adaptiveColor;
    ArkUI_Float32 scale;
};

struct ArkUITextDecorationType {
    ArkUI_Int32 decorationType;
    ArkUI_Uint32 color;
    ArkUI_Int32 style;
};

struct ArkUIFilterColorType {
    ArkUI_Float32* filterArray;
    ArkUI_Int32 filterSize;
};

struct ArkUISelectedDateType {
    ArkUI_Uint32 year;
    ArkUI_Uint32 month;
    ArkUI_Uint32 day;
};

struct ArkUICalendarTextStyleType {
    ArkUI_Uint32 fontColor;
    ArkUI_Float32 fontSize;
    ArkUI_Int32 fontWeight;
};

struct ArkUIEdgeAlignType {
    ArkUI_Int32 alignType;
    ArkUI_Float32 offsetX;
    ArkUI_Float32 offsetY;
};

struct ArkUITextBackgroundStyleOptions {
    ArkUI_Uint32 color;
    ArkUI_Float32 topLeft;
    ArkUI_Float32 topRight;
    ArkUI_Float32 bottomLeft;
    ArkUI_Float32 bottomRight;
};

struct ArkUIWaterFlowNestedScrollOptions {
    ArkUI_Int32 scrollForward;
    ArkUI_Int32 scrollBackward;
};

struct ArkUIBlendModeOptions {
    ArkUI_Int32 blendMode;
    ArkUI_Int32 blendApplyType;
};

enum ArkUINodeType {
    ARKUI_TEXT = 1,
    ARKUI_SPAN,
    ARKUI_IMAGE_SPAN,
    ARKUI_IMAGE,
    ARKUI_TOGGLE,
    ARKUI_LOADING_PROGRESS,
    ARKUI_TEXT_INPUT,
    ARKUI_STACK,
    ARKUI_SCROLL,
    ARKUI_LIST,
    ARKUI_SWIPER,
    ARKUI_TEXTAREA,
    ARKUI_BUTTON,
    ARKUI_PROGRESS,
    ARKUI_CHECKBOX,
    ARKUI_COLUMN,
    ARKUI_ROW,
    ARKUI_FLEX,
    ARKUI_LIST_ITEM,
    ARKUI_TABS,
    ARKUI_NAVIGATOR,
    ARKUI_WEB,
    ARKUI_SLIDER,
    ARKUI_CANVAS,
    ARKUI_RADIO,
    ARKUI_GRID,
    ARKUI_XCOMPONENT,
    ARKUI_SIDEBAR,
    ARKUI_REFRESH,
    ARKUI_ROOT,
    ARKUI_COMPONENT_ROOT,
    ARKUI_LIST_ITEM_GROUP,
    ARKUI_DATE_PICKER,
    ARKUI_TIME_PICKER,
    ARKUI_TEXT_PICKER,
    ARKUI_CALENDAR_PICKER,
    ARKUI_GRID_ITEM,
    ARKUI_CUSTOM,
    ARKUI_NAVIGATION,
    ARKUI_WATER_FLOW,
    ARKUI_FLOW_ITEM,
    ARKUI_RELATIVE_CONTAINER,
    ARKUI_BLANK,
    ARKUI_DIVIDER,
    ARKUI_ALPHABET_INDEXER,
    ARKUI_SEARCH,
    ARKUI_GRID_ROW,
    ARKUI_GRID_COL,
    ARKUI_CIRCLE,
    ARKUI_TAB_CONTENT
};

enum ArkUIEventCategory {
    INVALID = 0,
    SINGLE_POINTER_INPUT = 1,
    MULTI_POINTER_INPUT = 2,
    CALLBACK_EVENT = 3,
    COMPONENT_ASYNC_EVENT = 4,
    TEXT_INPUT = 5,
    GESTURE_ASYNC_EVENT = 6,
    TOUCH_EVENT = 7,
    TEXT_ARRAY = 8,
    MOUSE_INPUT_EVENT = 9,
};

#define ARKUI_MAX_EVENT_NUM 1000

enum ArkUIEventSubKind {
    // common events
    ON_APPEAR = 0,
    ON_DISAPPEAR = 1,
    ON_TOUCH = 2,
    ON_CLICK = 3,
    ON_HOVER = 4,
    ON_BLUR = 5,
    ON_KEY_EVENT = 6,
    ON_MOUSE = 7,
    ON_AREA_CHANGE = 8,
    ON_VISIBLE_AREA_CHANGE = 9,
    ON_GESTURE = 10,
    ON_FOCUS = 11,
    ON_TOUCH_INTERCEPT = 12,
    ON_DETECT_RESULT_UPDATE = ARKUI_MAX_EVENT_NUM * ARKUI_TEXT,
    ON_IMAGE_COMPLETE = ARKUI_MAX_EVENT_NUM * ARKUI_IMAGE,
    ON_IMAGE_ERROR,
    ON_IMAGE_SVG_PLAY_FINISH,
    // components events
    ON_LIST_SCROLL = ARKUI_MAX_EVENT_NUM * ARKUI_LIST,
    ON_LIST_SCROLL_INDEX,
    ON_LIST_SCROLL_START,
    ON_LIST_SCROLL_STOP,
    ON_LIST_SCROLL_FRAME_BEGIN,
    ON_LIST_WILL_SCROLL,
    ON_LIST_DID_SCROLL,
    ON_LIST_REACH_START,
    ON_LIST_REACH_END,

    ON_TOGGLE_CHANGE = ARKUI_MAX_EVENT_NUM * ARKUI_TOGGLE,

    ON_CHECKBOX_CHANGE = ARKUI_MAX_EVENT_NUM * ARKUI_CHECKBOX,

    ON_TEXT_INPUT_EDIT_CHANGE = ARKUI_MAX_EVENT_NUM * ARKUI_TEXT_INPUT,
    ON_TEXT_INPUT_SUBMIT,
    ON_TEXT_INPUT_CHANGE,
    ON_TEXT_INPUT_CUT,
    ON_TEXT_INPUT_PASTE,
    ON_TEXT_INPUT_TEXT_SELECTION_CHANGE,
    ON_TEXT_INPUT_CONTENT_SIZE_CHANGE,
    ON_TEXT_INPUT_INPUT_FILTER_ERROR,
    ON_TEXT_INPUT_CONTENT_SCROLL,

    ON_TEXTAREA_EDIT_CHANGE = ARKUI_MAX_EVENT_NUM * ARKUI_TEXTAREA,
    ON_TEXTAREA_SUBMIT,
    ON_TEXTAREA_CHANGE,
    ON_TEXTAREA_PASTE,
    ON_TEXTAREA_TEXT_SELECTION_CHANGE,
    ON_TEXTAREA_ON_SUBMIT,
    ON_TEXTAREA_CONTENT_SIZE_CHANGE,
    ON_TEXT_AREA_INPUT_FILTER_ERROR,
    ON_TEXT_AREA_CONTENT_SCROLL,

    ON_SWIPER_CHANGE = ARKUI_MAX_EVENT_NUM * ARKUI_SWIPER,
    ON_SWIPER_ANIMATION_START,
    ON_SWIPER_ANIMATION_END,
    ON_SWIPER_GESTURE_SWIPE,

    ON_SCROLL = ARKUI_MAX_EVENT_NUM * ARKUI_SCROLL,
    ON_SCROLL_FRAME_BEGIN,
    ON_SCROLL_WILL_SCROLL,
    ON_SCROLL_DID_SCROLL,
    ON_SCROLL_START,
    ON_SCROLL_STOP,
    ON_SCROLL_EDGE,
    ON_SCROLL_REACH_START,
    ON_SCROLL_REACH_END,

    ON_TABS_CHANGE = ARKUI_MAX_EVENT_NUM * ARKUI_TABS,
    ON_NAVIGATOR_CLICK = ARKUI_MAX_EVENT_NUM * ARKUI_NAVIGATOR,
    ON_WEB_INTERCEPT = ARKUI_MAX_EVENT_NUM * ARKUI_WEB,
    ON_SLIDER_CHANGE = ARKUI_MAX_EVENT_NUM * ARKUI_SLIDER,
    ON_CANVAS_READY = ARKUI_MAX_EVENT_NUM * ARKUI_CANVAS,

    ON_RADIO_CHANGE = ARKUI_MAX_EVENT_NUM * ARKUI_RADIO,

    ON_GRID_SCROLL = ARKUI_MAX_EVENT_NUM * ARKUI_GRID,
    ON_GRID_START,
    ON_GRID_STOP,
    ON_GRID_SCROLL_TO_INDEX,

    ON_SIDEBAR_CHANGE = ARKUI_MAX_EVENT_NUM * ARKUI_SIDEBAR,

    ON_XCOMPONENT_LOAD = ARKUI_MAX_EVENT_NUM * ARKUI_XCOMPONENT,
    ON_XCOMPONENT_DESTROY,

    ON_REFRESH_STATE_CHANGE = ARKUI_MAX_EVENT_NUM * ARKUI_REFRESH,
    ON_REFRESH_REFRESHING,
    ON_DATE_PICKER_DATE_CHANGE = ARKUI_MAX_EVENT_NUM * ARKUI_DATE_PICKER,
    ON_TIME_PICKER_CHANGE = ARKUI_MAX_EVENT_NUM * ARKUI_TIME_PICKER,
    ON_TEXT_PICKER_CHANGE = ARKUI_MAX_EVENT_NUM * ARKUI_TEXT_PICKER,
    ON_CALENDAR_PICKER_CHANGE = ARKUI_MAX_EVENT_NUM * ARKUI_CALENDAR_PICKER,
    ON_WATER_FLOW_WILL_SCROLL = ARKUI_MAX_EVENT_NUM * ARKUI_WATER_FLOW,
    ON_WATER_FLOW_REACH_END,
    ON_WATER_FLOW_DID_SCROLL,
    ON_WATER_FLOW_SCROLL_START,
    ON_WATER_FLOW_SCROLL_STOP,
    ON_WATER_FLOW_SCROLL_FRAME_BEGIN,
    ON_WATER_FLOW_SCROLL_INDEX,
    ON_WATER_FLOW_REACH_START,

    ON_ALPHABET_INDEXER_SELECTED = ARKUI_MAX_EVENT_NUM * ARKUI_ALPHABET_INDEXER,
    ON_ALPHABET_INDEXER_REQUEST_POPUP_DATA,
    ON_ALPHABET_INDEXER_POPUP_SELECTED,
    ON_ALPHABET_INDEXER_CHANGE_EVENT,
    ON_ALPHABET_INDEXER_CREAT_CHANGE_EVENT,

    ON_SEARCH_SUBMIT = ARKUI_MAX_EVENT_NUM * ARKUI_SEARCH,
    ON_SEARCH_CHANGE,
    ON_SEARCH_COPY,
    ON_SEARCH_CUT,
    ON_SEARCH_PASTE,
};

enum ArkUIAPIGestureAsyncEventSubKind {
    ON_ACTION = 0,
    ON_ACTION_START = 1,
    ON_ACTION_UPDATE = 2,
    ON_ACTION_END = 3,
    ON_ACTION_CANCEL = 4
};

union ArkUIAPIValue {
    ArkUI_Int32 i32;
    ArkUI_Int64 i64;
    ArkUI_Float32 f32;
    ArkUI_Float32 f64;
};

enum ArkUIAPIValueKind {
    VALUE_KIND_INT32 = 0,
    VALUE_KIND_FLOAT32 = 1,
    VALUE_KIND_INT64 = 2,
    VALUE_KIND_FLOAT64 = 3,
};

enum ArkUIAPIEventCallbackType {
    VOID_TYPE = 0, // VOID conflicts VOID define in winnt.h
    INT_32 = 1,
    FLOAT_32 = 2,
    INT_32_ARRAY = 3,
    FLOAT_32_ARRAY = 4
};

enum ArkUIAPINodeFlags {
    NONE = 0,
    CUSTOM_MEASURE = 1 << 0,
    CUSTOM_LAYOUT = 1 << 1,
    CUSTOM_DRAW = 1 << 2,
    CUSTOM_FOREGROUND_DRAW = 1 << 3,
    CUSTOM_OVERLAY_DRAW = 1 << 4,
};

enum ArkUIGestureDirection {
    ArkUI_GESTURE_DIRECTION_NONE = 0,
    ArkUI_GESTURE_DIRECTION_LEFT = 1,
    ArkUI_GESTURE_DIRECTION_RIGHT = 2,
    ArkUI_GESTURE_DIRECTION_HORIZONTAL = 3,
    ArkUI_GESTURE_DIRECTION_UP = 4,
    ArkUI_GESTURE_DIRECTION_DOWN = 5,
    ArkUI_GESTURE_DIRECTION_VERTICAL = 12,
    ArkUI_GESTURE_DIRECTION_ALL = 15,
};

enum ArkUISwipeGestureDirection {
    ArkUI_SWIPE_GESTURE_DIRECTION_NONE = 0,
    ArkUI_SWIPE_GESTURE_DIRECTION_HORIZONTAL = 1,
    ArkUI_SWIPE_GESTURE_DIRECTION_VERTICAL = 2,
    ArkUI_SWIPE_GESTURE_DIRECTION_ALL = 3,
};

enum ArkUIAPICustomOp { MEASURE = 1, LAYOUT = 2, DRAW = 3 };

enum ArkUIVMKind {
    VM_JS = 1,
    VM_STS = 2,
};

// Current implementation assumes that each argument is 4 bytes,
// fix decodeEvent() in TS if it will change.
union ArkUIEventCallbackArg {
    ArkUI_Int32 i32;
    ArkUI_Uint32 u32;
    ArkUI_Float32 f32;
};

struct ArkUIAPIEventSinglePointer {
    ArkUI_Int32 x;
    ArkUI_Int32 y;
    ArkUI_Int32 state; // 0 - down, 1 - up, 2 - move
};

#define ARKUI_MULTIPOINTER_ARGS_COUNT 10

struct ArkUIAPIEventMultiPointer {
    ArkUI_Int32 count;
    ArkUI_Int32 xs[ARKUI_MULTIPOINTER_ARGS_COUNT];
    ArkUI_Int32 ys[ARKUI_MULTIPOINTER_ARGS_COUNT];
    ArkUI_Int32 state[ARKUI_MULTIPOINTER_ARGS_COUNT];
};

struct ArkUIAPIEventTextInput {
    // used by c-api, should be the first place.
    ArkUI_Int64 nativeStringPtr;
    ArkUI_Int32 subKind; // ArkUIEventSubKind actually
};

#define ARKUI_CALLBACK_ARGS_COUNT 12

struct ArkUIAPIEventCallback {
    ArkUI_Int32 id;
    ArkUI_Int32 numArgs;
    ArkUI_Int32 continuationId;
    ArkUIEventCallbackArg args[ARKUI_CALLBACK_ARGS_COUNT];
};

#define ARKUI_ASYNC_EVENT_ARGS_COUNT 12

struct ArkUINodeAsyncEvent {
    // used by c-api, should be the first place.
    ArkUIEventCallbackArg data[ARKUI_ASYNC_EVENT_ARGS_COUNT];
    ArkUI_Int32 subKind; // ArkUIEventSubKind actually
};

struct ArkUIAPIEventTextArray {
    ArkUI_Int64 nativeStringArrayPtr;
    ArkUI_Int32 length;
    ArkUI_Int32 subKind; // ArkUIEventSubKind actually
};

struct ArkUIAPIEventGestureAsyncEvent {
    ArkUI_Int32 subKind;
    ArkUI_Int32 repeat;
    ArkUI_Float32 x;
    ArkUI_Float32 y;
    ArkUI_Float32 angle;
    ArkUI_Float32 scale;
    ArkUI_Float32 pinchCenterX;
    ArkUI_Float32 pinchCenterY;
    ArkUI_Int32 speed;
    ArkUI_Int32 timestamp;
    ArkUI_Int32 source;
    ArkUI_Int32 pressure;
    ArkUI_Int32 tiltX;
    ArkUI_Int32 tiltY;
    ArkUI_Int32 sourceTool;
    ArkUI_Float32 velocityX;
    ArkUI_Float32 velocityY;
    ArkUI_Float32 velocity;
    void* rawPointerEvent;
};

struct ArkUINodeEvent {
    ArkUI_Int32 kind; // Actually ArkUIEventCategory.
    ArkUI_Int32 nodeId;
    ArkUI_Int64 extraParam;
    union {
        ArkUIAPIEventSinglePointer singlePointer;
        ArkUIAPIEventMultiPointer multiPointer;
        ArkUIAPIEventCallback callback;
        ArkUINodeAsyncEvent componentAsyncEvent;
        ArkUIAPIEventTextInput textInputEvent;
        ArkUIAPIEventGestureAsyncEvent gestureAsyncEvent;
        ArkUITouchEvent touchEvent;
        ArkUIAPIEventTextArray textArrayEvent;
        ArkUIMouseEvent mouseEvent;
    };
};

struct ArkUIAPIAnimationSpec {
    ArkUI_Int32 duration;
    ArkUI_Int32 delay;
    ArkUI_Int32 valueKind; // of ArkUIAPIValueKind
    ArkUIAPIValue initial;
    ArkUIAPIValue target;
};

struct ArkUIAPICallbackMethod {
    ArkUI_Int32 (*CallInt)(
        ArkUIVMContext vmContext, ArkUI_Int32 methodId, ArkUI_Int32 numArgs, ArkUIEventCallbackArg* args);
};

struct ArkUIBorderOptions {
    ArkUI_Float32* widthValues;
    ArkUI_Int32* widthUnits;
    ArkUI_Int32* colors;
    ArkUI_Float32* radiusValues;
    ArkUI_Int32* radiusUnits;
    ArkUI_Int32* styles;
};

struct ArkUITextFont {
    ArkUI_Int32 fontWeight;
    ArkUI_Float32 fontSize;
    ArkUI_Int32 fontStyle;
    ArkUI_CharPtr fontFamilies;
    ArkUI_Int32 fontSizeUnit;
};

struct ArkUIOverlayOptions {
    ArkUI_Int32 align;
    ArkUI_Float32 x;
    ArkUI_Float32 y;
    ArkUI_CharPtr content;
};

union ArkUIInt32orFloat32 {
    ArkUI_Float32 f32;
    ArkUI_Uint32 u32;
    ArkUI_Int32 i32;
};

struct ArkUIBackgroundImage {
    ArkUI_CharPtr src;
    ArkUI_Int32 repeat;
};

struct ArkUIShowCountOptions {
    ArkUI_Bool open;
    ArkUI_Int32 thresholdPercentage;
    ArkUI_Bool highlightBorder;
};

struct ArkUICustomNodeEvent {
    ArkUI_Int32 kind;
    ArkUI_Int64 extraParam;
    ArkUI_Int64 canvas;
    ArkUI_Int32 data[8];
};

struct ArkUIExpectedFrameRateRange {
    ArkUI_Uint32 min;
    ArkUI_Uint32 max;
    ArkUI_Uint32 expected;
};

struct ArkUIAnimateOption {
    ArkUI_Uint32 duration;
    ArkUI_Float32 tempo;
    ArkUI_Int32 curve;
    ArkUI_Int32 delay;
    ArkUI_Int32 iterations;
    ArkUI_Int32 playMode;
    ArkUIExpectedFrameRateRange* expectedFrameRateRange;
    void* onFinishCallback;
    void* user;
    ArkUI_Int32 finishCallbackType;
};

struct ArkUIContext {
    ArkUI_Int32 id;
};

struct ArkUIGuidelineStyle {
    ArkUI_CharPtr id;
    ArkUI_Int32 direction;
    ArkUI_Float32 start;
    ArkUI_Float32 end;
};

struct ArkUIBarrierStyle {
    ArkUI_CharPtr id;
    ArkUI_Int32 direction;
    ArkUI_CharPtr* referencedId;
    ArkUI_Int32 referencedIdSize;
};
struct ArkUIRadioStyleOption {
    ArkUI_Uint32 checkedBackgroundColor;
    ArkUI_Uint32 uncheckedBorderColor;
    ArkUI_Uint32 indicatorColor;
};

enum ArkUISwiperIndicatorType {
    DOT,
    DIGIT,
};

struct ArkUIOptionalFloat {
    ArkUI_Int32 isSet;
    ArkUI_Float32 value;
};

struct ArkUIOptionalInt {
    ArkUI_Int32 isSet;
    ArkUI_Int32 value;
};

struct ArkUIOptionalUint {
    ArkUI_Int32 isSet;
    ArkUI_Uint32 value;
};

struct ArkUISwiperIndicator {
    ArkUISwiperIndicatorType type;
    ArkUI_Int32 dimUnit;
    ArkUIOptionalFloat dimLeft;
    ArkUIOptionalFloat dimTop;
    ArkUIOptionalFloat dimRight;
    ArkUIOptionalFloat dimBottom;
    ArkUIOptionalFloat itemWidth;
    ArkUIOptionalFloat itemHeight;
    ArkUIOptionalFloat selectedItemWidth;
    ArkUIOptionalFloat selectedItemHeight;
    ArkUIOptionalInt maskValue;
    ArkUIOptionalUint colorValue;
    ArkUIOptionalUint selectedColorValue;
};

struct ArkUICommonModifier {
    void (*setBackgroundColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetBackgroundColor)(ArkUINodeHandle node);
    void (*setWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue);
    void (*resetWidth)(ArkUINodeHandle node);
    void (*setHeight)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue);
    void (*resetHeight)(ArkUINodeHandle node);
    void (*setBorderRadius)(
        ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 length);
    void (*resetBorderRadius)(ArkUINodeHandle node);
    void (*setBorderWidth)(
        ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 length);
    void (*resetBorderWidth)(ArkUINodeHandle node);
    void (*setTransform)(ArkUINodeHandle node, const ArkUI_Float32* matrix, ArkUI_Int32 length);
    void (*resetTransform)(ArkUINodeHandle node);
    void (*setBorderColor)(ArkUINodeHandle node, ArkUI_Uint32 leftColorInt, ArkUI_Uint32 rightColorInt,
        ArkUI_Uint32 topColorInt, ArkUI_Uint32 bottomColorInt);
    void (*resetBorderColor)(ArkUINodeHandle node);
    void (*setPosition)(
        ArkUINodeHandle node, ArkUI_Float32 xValue, ArkUI_Int32 xUnit, ArkUI_Float32 yValue, ArkUI_Int32 yUnit);
    void (*resetPosition)(ArkUINodeHandle node);
    void (*setPositionEdges)(ArkUINodeHandle node, ArkUI_Bool useEdges, const ArkUIStringAndFloat* options);
    void (*resetPositionEdges)(ArkUINodeHandle node);
    void (*setBorderStyle)(ArkUINodeHandle node, const ArkUI_Int32* styles, ArkUI_Int32 length);
    void (*resetBorderStyle)(ArkUINodeHandle node);
    void (*setBackShadow)(ArkUINodeHandle node, const ArkUIInt32orFloat32* shadows, ArkUI_Int32 length);
    void (*resetBackShadow)(ArkUINodeHandle node);
    void (*setHitTestBehavior)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetHitTestBehavior)(ArkUINodeHandle node);
    void (*setZIndex)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetZIndex)(ArkUINodeHandle node);
    void (*setOpacity)(ArkUINodeHandle node, ArkUI_Float32 opacity);
    void (*resetOpacity)(ArkUINodeHandle node);
    void (*setAlign)(ArkUINodeHandle node, ArkUI_Int32 align);
    void (*resetAlign)(ArkUINodeHandle node);
    void (*setBackdropBlur)(
        ArkUINodeHandle node, ArkUI_Float32 value, const ArkUI_Float32* blurValues, ArkUI_Int32 blurValuesSize);
    void (*resetBackdropBlur)(ArkUINodeHandle node);
    void (*setHueRotate)(ArkUINodeHandle node, ArkUI_Float32 deg);
    void (*resetHueRotate)(ArkUINodeHandle node);
    void (*setInvert)(ArkUINodeHandle node, ArkUI_Float32* invert, ArkUI_Int32 length);
    void (*resetInvert)(ArkUINodeHandle node);
    void (*setSepia)(ArkUINodeHandle node, ArkUI_Float32 sepia);
    void (*resetSepia)(ArkUINodeHandle node);
    void (*setSaturate)(ArkUINodeHandle node, ArkUI_Float32 saturate);
    void (*resetSaturate)(ArkUINodeHandle node);
    void (*setColorBlend)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetColorBlend)(ArkUINodeHandle node);
    void (*setGrayscale)(ArkUINodeHandle node, ArkUI_Float32 grayScale);
    void (*resetGrayscale)(ArkUINodeHandle node);
    void (*setContrast)(ArkUINodeHandle node, ArkUI_Float32 contrast);
    void (*resetContrast)(ArkUINodeHandle node);
    void (*setBrightness)(ArkUINodeHandle node, ArkUI_Float32 brightness);
    void (*resetBrightness)(ArkUINodeHandle node);
    void (*setBlur)(
        ArkUINodeHandle node, ArkUI_Float32 value, const ArkUI_Float32* blurValues, ArkUI_Int32 blurValuesSize);
    void (*resetBlur)(ArkUINodeHandle node);
    void (*setLinearGradient)(ArkUINodeHandle node, const ArkUIInt32orFloat32* values, ArkUI_Int32 valuesLength,
        const ArkUIInt32orFloat32* colors, ArkUI_Int32 colorsLength);
    void (*resetLinearGradient)(ArkUINodeHandle node);
    void (*setSweepGradient)(ArkUINodeHandle node, const ArkUIInt32orFloat32* values, ArkUI_Int32 valuesLength,
        const ArkUIInt32orFloat32* colors, ArkUI_Int32 colorsLength);
    void (*resetSweepGradient)(ArkUINodeHandle node);
    void (*setRadialGradient)(ArkUINodeHandle node, const ArkUIInt32orFloat32* values, ArkUI_Int32 valuesLength,
        const ArkUIInt32orFloat32* colors, ArkUI_Int32 colorsLength);
    void (*resetRadialGradient)(ArkUINodeHandle node);
    void (*setOverlay)(
        ArkUINodeHandle node, ArkUI_CharPtr text, const ArkUI_Float32* options, ArkUI_Int32 optionsLength);
    void (*resetOverlay)(ArkUINodeHandle node);
    void (*setBorderImage)(
        ArkUINodeHandle node, ArkUI_CharPtr src, const ArkUIStringAndFloat* options, ArkUI_Int32 optionsLength);
    void (*resetBorderImage)(ArkUINodeHandle node);
    void (*setBorderImageGradient)(ArkUINodeHandle node, const ArkUIInt32orFloat32* values, ArkUI_Int32 valuesLength,
        const ArkUIInt32orFloat32* colors, ArkUI_Int32 colorsLength);
    void (*setForegroundBlurStyle)(ArkUINodeHandle node, ArkUI_Int32* intArray, ArkUI_Float32 scale,
        const ArkUI_Float32* blurValues, ArkUI_Int32 blurValuesSize);
    void (*resetForegroundBlurStyle)(ArkUINodeHandle node);
    void (*setLinearGradientBlur)(ArkUINodeHandle node, ArkUI_Float32 blurRadius, const ArkUI_Float32* stops,
        ArkUI_Uint32 stopsLength, ArkUI_Int32 directionValue);
    void (*resetLinearGradientBlur)(ArkUINodeHandle node);
    void (*setBackgroundBlurStyle)(ArkUINodeHandle node, ArkUI_Int32* intArray, ArkUI_Float32 scale,
        const ArkUI_Float32* blurValues, ArkUI_Int32 blurValuesSize);
    void (*resetBackgroundBlurStyle)(ArkUINodeHandle node);
    void (*setBorder)(ArkUINodeHandle node, const ArkUI_Float32* values, ArkUI_Int32 valuesSize,
        const ArkUI_Uint32* colorAndStyle, ArkUI_Int32 colorAndStyleSize);
    void (*resetBorder)(ArkUINodeHandle node);
    void (*setBackgroundImagePosition)(ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* types,
        ArkUI_Bool isAlign, ArkUI_Int32 size);
    void (*resetBackgroundImagePosition)(ArkUINodeHandle node);
    void (*setBackgroundImageSize)(ArkUINodeHandle node, ArkUI_Float32 valueWidth, ArkUI_Float32 valueHeight,
        ArkUI_Int32 typeWidth, ArkUI_Int32 typeHeight);
    void (*resetBackgroundImageSize)(ArkUINodeHandle node);
    void (*setBackgroundImage)(
        ArkUINodeHandle node, ArkUI_CharPtr src, ArkUI_CharPtr bundle, ArkUI_CharPtr module, ArkUI_Int32 repeatIndex);
    void (*resetBackgroundImage)(ArkUINodeHandle node);
    void (*setTranslate)(
        ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 length);
    void (*resetTranslate)(ArkUINodeHandle node);
    void (*setScale)(ArkUINodeHandle node, const ArkUI_Float32* values, ArkUI_Int32 valLength, const ArkUI_Int32* units,
        ArkUI_Int32 unitLength);
    void (*setScaleWithoutTransformCenter)(ArkUINodeHandle node, const ArkUI_Float32* values, ArkUI_Int32 valLength);
    void (*resetScale)(ArkUINodeHandle node);
    void (*setRotate)(ArkUINodeHandle node, const ArkUI_Float32* values, ArkUI_Int32 valLength,
        const ArkUI_Int32* units, ArkUI_Int32 unitLength);
    void (*setRotateWithoutTransformCenter)(ArkUINodeHandle node, const ArkUI_Float32* values, ArkUI_Int32 valLength);
    void (*resetRotate)(ArkUINodeHandle node);
    void (*setGeometryTransition)(ArkUINodeHandle node, ArkUI_CharPtr id, ArkUI_Bool options);
    void (*resetGeometryTransition)(ArkUINodeHandle node);
    void (*setPixelStretchEffect)(
        ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 length);
    void (*resetPixelStretchEffect)(ArkUINodeHandle node);
    void (*setLightUpEffect)(ArkUINodeHandle node, ArkUI_Float32 radio);
    void (*resetLightUpEffect)(ArkUINodeHandle node);
    void (*setSphericalEffect)(ArkUINodeHandle node, ArkUI_Float32 radio);
    void (*resetSphericalEffect)(ArkUINodeHandle node);
    void (*setRenderGroup)(ArkUINodeHandle node, ArkUI_Bool isRenderGroup);
    void (*resetRenderGroup)(ArkUINodeHandle node);
    void (*setRenderFit)(ArkUINodeHandle node, ArkUI_Int32 renderFit);
    void (*resetRenderFit)(ArkUINodeHandle node);
    void (*setUseEffect)(ArkUINodeHandle node, ArkUI_Bool useEffect);
    void (*resetUseEffect)(ArkUINodeHandle node);
    void (*setForegroundColor)(ArkUINodeHandle node, ArkUI_Bool isColor, ArkUI_Uint32 color);
    void (*resetForegroundColor)(ArkUINodeHandle node);
    void (*setMotionPath)(
        ArkUINodeHandle node, ArkUI_CharPtr path, ArkUI_Float32 from, ArkUI_Float32 to, ArkUI_Bool rotatable);
    void (*resetMotionPath)(ArkUINodeHandle node);
    void (*setMotionBlur)(ArkUINodeHandle node, ArkUI_Float32 radius, ArkUI_Float32 anchorX, ArkUI_Float32 anchorY);
    void (*resetMotionBlur)(ArkUINodeHandle node);
    void (*setGroupDefaultFocus)(ArkUINodeHandle node, ArkUI_Bool groupDefaultFocus);
    void (*resetGroupDefaultFocus)(ArkUINodeHandle node);
    void (*setFocusOnTouch)(ArkUINodeHandle node, ArkUI_Bool focusOnTouch);
    void (*resetFocusOnTouch)(ArkUINodeHandle node);
    void (*setFocusable)(ArkUINodeHandle node, ArkUI_Bool focusable);
    void (*resetFocusable)(ArkUINodeHandle node);
    void (*setTouchable)(ArkUINodeHandle node, ArkUI_Bool touchable);
    void (*resetTouchable)(ArkUINodeHandle node);
    void (*setDefaultFocus)(ArkUINodeHandle node, ArkUI_Bool defaultFocus);
    void (*resetDefaultFocus)(ArkUINodeHandle node);
    void (*setDisplayPriority)(ArkUINodeHandle node, ArkUI_Float32 value);
    void (*resetDisplayPriority)(ArkUINodeHandle node);
    void (*setOffset)(ArkUINodeHandle node, const ArkUI_Float32* number, const ArkUI_Int32* unit);
    void (*setOffsetEdges)(ArkUINodeHandle node, ArkUI_Bool useEdges, const ArkUIStringAndFloat* options);
    void (*resetOffset)(ArkUINodeHandle node);
    void (*setPadding)(ArkUINodeHandle node, const struct ArkUISizeType* top, const struct ArkUISizeType* right,
        const struct ArkUISizeType* bottom, const struct ArkUISizeType* left);
    void (*resetPadding)(ArkUINodeHandle node);
    void (*setMargin)(ArkUINodeHandle node, const struct ArkUISizeType* top, const struct ArkUISizeType* right,
        const struct ArkUISizeType* bottom, const struct ArkUISizeType* left);
    void (*resetMargin)(ArkUINodeHandle node);
    void (*setMarkAnchor)(
        ArkUINodeHandle node, ArkUI_Float32 xValue, ArkUI_Int32 xUnit, ArkUI_Float32 yValue, ArkUI_Int32 yUnit);
    void (*resetMarkAnchor)(ArkUINodeHandle node);
    void (*setVisibility)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetVisibility)(ArkUINodeHandle node);
    void (*setAccessibilityText)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*resetAccessibilityText)(ArkUINodeHandle node);
    void (*setAllowDrop)(ArkUINodeHandle node, ArkUI_CharPtr* value, ArkUI_Int32 length);
    void (*resetAllowDrop)(ArkUINodeHandle node);
    void (*setAccessibilityLevel)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*resetAccessibilityLevel)(ArkUINodeHandle node);
    void (*setDirection)(ArkUINodeHandle node, ArkUI_Int32 direction);
    void (*resetDirection)(ArkUINodeHandle node);
    void (*setLayoutWeight)(ArkUINodeHandle node, ArkUI_Int32 layoutWeight);
    void (*resetLayoutWeight)(ArkUINodeHandle node);
    void (*setMinWidth)(ArkUINodeHandle node, const struct ArkUISizeType* minWidth);
    void (*resetMinWidth)(ArkUINodeHandle node);
    void (*setMaxWidth)(ArkUINodeHandle node, const struct ArkUISizeType* maxWidth);
    void (*resetMaxWidth)(ArkUINodeHandle node);
    void (*setMinHeight)(ArkUINodeHandle node, const struct ArkUISizeType* minHeight);
    void (*resetMinHeight)(ArkUINodeHandle node);
    void (*setMaxHeight)(ArkUINodeHandle node, const struct ArkUISizeType* maxHeight);
    void (*resetMaxHeight)(ArkUINodeHandle node);
    void (*setSize)(ArkUINodeHandle node, const ArkUI_Float32* number, const ArkUI_Int32* unit, ArkUI_CharPtr* calc);
    void (*resetSize)(ArkUINodeHandle node);
    void (*clearWidthOrHeight)(ArkUINodeHandle node, ArkUI_Bool isWidth);
    void (*setAlignSelf)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetAlignSelf)(ArkUINodeHandle node);
    void (*setAspectRatio)(ArkUINodeHandle node, ArkUI_Float32 value);
    void (*resetAspectRatio)(ArkUINodeHandle node);
    void (*setFlexGrow)(ArkUINodeHandle node, ArkUI_Float32 value);
    void (*resetFlexGrow)(ArkUINodeHandle node);
    void (*setFlexShrink)(ArkUINodeHandle node, ArkUI_Float32 value);
    void (*resetFlexShrink)(ArkUINodeHandle node);
    void (*setGridOffset)(ArkUINodeHandle node, ArkUI_Int32 offset);
    void (*resetGridOffset)(ArkUINodeHandle node);
    void (*setGridSpan)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetGridSpan)(ArkUINodeHandle node);
    void (*setExpandSafeArea)(ArkUINodeHandle node, ArkUI_CharPtr typeStr, ArkUI_CharPtr edgesStr);
    void (*resetExpandSafeArea)(ArkUINodeHandle node);
    void (*setFlexBasis)(ArkUINodeHandle node, const struct ArkUIStringAndFloat* flexBasisValue);
    void (*resetFlexBasis)(ArkUINodeHandle node);
    void (*setAlignRules)(ArkUINodeHandle node, char** anchors, const ArkUI_Int32* direction, ArkUI_Int32 length);
    void (*resetAlignRules)(ArkUINodeHandle node);
    void (*setAccessibilityDescription)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*resetAccessibilityDescription)(ArkUINodeHandle node);
    void (*setId)(ArkUINodeHandle node, ArkUI_CharPtr id);
    void (*resetId)(ArkUINodeHandle node);
    void (*setKey)(ArkUINodeHandle node, ArkUI_CharPtr key);
    void (*resetKey)(ArkUINodeHandle node);
    void (*setRestoreId)(ArkUINodeHandle node, ArkUI_Uint32 id);
    void (*resetRestoreId)(ArkUINodeHandle node);
    void (*setTabIndex)(ArkUINodeHandle node, ArkUI_Int32 index);
    void (*resetTabIndex)(ArkUINodeHandle node);
    void (*setObscured)(ArkUINodeHandle node, const ArkUI_Int32* reasons, ArkUI_Int32 length);
    void (*resetObscured)(ArkUINodeHandle node);
    void (*setResponseRegion)(
        ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 length);
    void (*resetResponseRegion)(ArkUINodeHandle node);
    void (*setForegroundEffect)(ArkUINodeHandle node, ArkUI_Float32 radius);
    void (*resetForegroundEffect)(ArkUINodeHandle node);
    void (*setBackgroundEffect)(ArkUINodeHandle node, ArkUI_Float32 radius, ArkUI_Float32 saturation,
        ArkUI_Float32 brightness, ArkUI_Uint32 color, ArkUI_Int32 adaptiveColor, const ArkUI_Float32* blurValues,
        ArkUI_Int32 blurValuesSize);
    void (*resetBackgroundEffect)(ArkUINodeHandle node);
    void (*setBackgroundBrightness)(ArkUINodeHandle node, ArkUI_Float32 rate, ArkUI_Float32 lightUpDegree);
    void (*resetBackgroundBrightness)(ArkUINodeHandle node);
    void (*setBackgroundBrightnessInternal)(ArkUINodeHandle node, ArkUI_Float32 rate, ArkUI_Float32 lightUpDegree,
        ArkUI_Float32 cubicCoeff, ArkUI_Float32 quadCoeff, ArkUI_Float32 saturation, const ArkUI_Float32* posRGBValues,
        ArkUI_Int32 posRGBValuesSize, const ArkUI_Float32* negRGBValues, ArkUI_Int32 negRGBValuesSize,
        ArkUI_Float32 fraction);
    void (*resetBackgroundBrightnessInternal)(ArkUINodeHandle node);
    void (*setForegroundBrightness)(ArkUINodeHandle node, ArkUI_Float32 rate, ArkUI_Float32 lightUpDegree,
        ArkUI_Float32 cubicCoeff, ArkUI_Float32 quadCoeff, ArkUI_Float32 saturation, const ArkUI_Float32* posRGBValues,
        ArkUI_Int32 posRGBValuesSize, const ArkUI_Float32* negRGBValues, ArkUI_Int32 negRGBValuesSize,
        ArkUI_Float32 fraction);
    void (*resetForegroundBrightness)(ArkUINodeHandle node);
    void (*setDragPreviewOptions)(ArkUINodeHandle node, ArkUI_Int32 dragPreviewMode);
    void (*resetDragPreviewOptions)(ArkUINodeHandle node);
    void (*setMouseResponseRegion)(
        ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 length);
    void (*resetMouseResponseRegion)(ArkUINodeHandle node);
    void (*setEnabled)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*resetEnabled)(ArkUINodeHandle node);
    void (*setUseShadowBatching)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*resetUseShadowBatching)(ArkUINodeHandle node);
    void (*setDraggable)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*resetDraggable)(ArkUINodeHandle node);
    void (*setAccessibilityGroup)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*resetAccessibilityGroup)(ArkUINodeHandle node);
    void (*setHoverEffect)(ArkUINodeHandle node, ArkUI_Int32 hoverEffectValue);
    void (*resetHoverEffect)(ArkUINodeHandle node);
    void (*setClickEffect)(ArkUINodeHandle node, ArkUI_Int32 level, ArkUI_Float32 scaleValue);
    void (*resetClickEffect)(ArkUINodeHandle node);
    void (*setKeyBoardShortCut)(
        ArkUINodeHandle node, ArkUI_CharPtr value, const ArkUI_Int32* keysIntArray, ArkUI_Int32 length);
    void (*resetKeyBoardShortCut)(ArkUINodeHandle node);
    void (*setClip)(ArkUINodeHandle node, ArkUI_Int32 isClip);
    void (*setClipShape)(ArkUINodeHandle node, ArkUI_CharPtr type, const ArkUI_Float32* attribute, ArkUI_Int32 length);
    void (*setClipPath)(
        ArkUINodeHandle node, ArkUI_CharPtr type, const ArkUI_Float32* attribute, ArkUI_CharPtr commands);
    void (*resetClip)(ArkUINodeHandle node);
    void (*setTransitionCenter)(ArkUINodeHandle node, ArkUI_Float32 centerX, ArkUI_Int32 centerXUnit,
        ArkUI_Float32 centerY, ArkUI_Int32 centerYUnit, ArkUI_Float32 centerZValue, ArkUI_Int32 centerZUnit);
    void (*setOpacityTransition)(
        ArkUINodeHandle node, ArkUI_Float32 value, const ArkUIAnimationOptionType* opacityOption);
    void (*setRotateTransition)(ArkUINodeHandle node, ArkUI_Float32* arrayValue, ArkUI_Int32 length,
        ArkUI_Float32 perspective, ArkUI_Float32 angle, const ArkUIAnimationOptionType* opacityOption);
    void (*setScaleTransition)(ArkUINodeHandle node, ArkUI_Float32* arrayValue, ArkUI_Int32 length,
        const ArkUIAnimationOptionType* opacityOption);
    void (*setTranslateTransition)(ArkUINodeHandle node, ArkUI_Float32 xValue, ArkUI_Int32 xUnit, ArkUI_Float32 yValue,
        ArkUI_Int32 yUnit, ArkUI_Float32 zValue, ArkUI_Int32 zUnit, const ArkUIAnimationOptionType* opacityOption);
    void (*setMaskShape)(ArkUINodeHandle node, ArkUI_CharPtr type, ArkUI_Uint32 fill, ArkUI_Uint32 stroke,
        ArkUI_Float32 strokeWidth, const ArkUI_Float32* attribute, ArkUI_Int32 length);
    void (*setMaskPath)(ArkUINodeHandle node, ArkUI_CharPtr type, ArkUI_Uint32 fill, ArkUI_Uint32 stroke,
        ArkUI_Float32 strokeWidth, const ArkUI_Float32* attribute, ArkUI_CharPtr commands);
    void (*setProgressMask)(ArkUINodeHandle node, const ArkUI_Float32* attribute, ArkUI_Uint32 color);
    void (*setBlendMode)(ArkUINodeHandle node, ArkUI_Int32 blendMode, ArkUI_Int32 blendApplyTypeValue);
    void (*resetBlendMode)(ArkUINodeHandle node);
    void (*setMonopolizeEvents)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*resetMonopolizeEvents)(ArkUINodeHandle node);
    void (*setConstraintSize)(ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units);
    void (*resetConstraintSize)(ArkUINodeHandle node);
    void (*setOutlineColor)(ArkUINodeHandle node, const ArkUI_Uint32* values, ArkUI_Int32 valuesSize);
    void (*resetOutlineColor)(ArkUINodeHandle node);
    void (*setOutlineRadius)(ArkUINodeHandle node, const ArkUI_Float32* values, ArkUI_Int32 valuesSize);
    void (*resetOutlineRadius)(ArkUINodeHandle node);
    void (*setOutlineWidth)(ArkUINodeHandle node, const ArkUI_Float32* values, ArkUI_Int32 valuesSize);
    void (*resetOutlineWidth)(ArkUINodeHandle node);
    void (*setOutlineStyle)(ArkUINodeHandle node, const ArkUI_Uint32* values, ArkUI_Int32 valuesSize);
    void (*resetOutlineStyle)(ArkUINodeHandle node);
    void (*setOutline)(ArkUINodeHandle node, const ArkUI_Float32* values, ArkUI_Int32 valuesSize,
        const ArkUI_Uint32* colorAndStyle, ArkUI_Int32 colorAndStyleSize);
    void (*resetOutline)(ArkUINodeHandle node);
    ArkUI_Bool (*getFocusable)(ArkUINodeHandle node);
    ArkUI_Bool (*getDefaultFocus)(ArkUINodeHandle node);
    ArkUI_Int32 (*getResponseRegion)(ArkUINodeHandle node, ArkUI_Float32* values);
    ArkUI_CharPtr (*getOverlay)(ArkUINodeHandle node, ArkUIOverlayOptions* options, ArkUI_Int32 unit);
    ArkUI_Bool (*getAccessibilityGroup)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getAccessibilityText)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getAccessibilityDescription)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getAccessibilityLevel)(ArkUINodeHandle node);
    void (*setNeedFocus)(ArkUINodeHandle node, ArkUI_Bool value);
    ArkUI_Bool (*getNeedFocus)(ArkUINodeHandle node);
    ArkUI_Float32 (*getOpacity)(ArkUINodeHandle node);
    void (*getBorderWidth)(ArkUINodeHandle node, ArkUI_Float32* values, ArkUI_Int32 unit);
    void (*getBorderWidthDimension)(ArkUINodeHandle node, ArkUI_Float32* values, ArkUI_Int32* units);
    void (*getBorderRadius)(ArkUINodeHandle node, ArkUI_Float32* values, ArkUI_Int32 unit);
    void (*getBorderColor)(ArkUINodeHandle node, ArkUI_Uint32* values);
    void (*getBorderStyle)(ArkUINodeHandle node, ArkUI_Int32* values);
    ArkUI_Int32 (*getZIndex)(ArkUINodeHandle node);
    ArkUI_Int32 (*getVisibility)(ArkUINodeHandle node);
    ArkUI_Int32 (*getClip)(ArkUINodeHandle node);
    void (*getClipShape)(ArkUINodeHandle node, ArkUIClipShapeOptions* options);
    void (*getTransform)(ArkUINodeHandle node, ArkUI_Float32* values);
    ArkUI_Int32 (*getHitTestBehavior)(ArkUINodeHandle node);
    void (*getPosition)(ArkUINodeHandle node, ArkUIPositionOptions* options, ArkUI_Int32 unit);
    ArkUI_Int32 (*getShadow)(ArkUINodeHandle node);
    void (*getCustomShadow)(ArkUINodeHandle node, ArkUICustomShadowOptions* options);
    ArkUI_Int32 (*getSweepGradient)(
        ArkUINodeHandle node, ArkUI_Float32* values, ArkUI_Uint32* colors, ArkUI_Float32* stops, ArkUI_Int32 unit);
    ArkUI_Int32 (*getRadialGradient)(
        ArkUINodeHandle node, ArkUI_Float32* values, ArkUI_Uint32* colors, ArkUI_Float32* stops, ArkUI_Int32 unit);
    void (*getMask)(ArkUINodeHandle node, ArkUIMaskOptions* options);
    void (*getBlendMode)(ArkUINodeHandle node, ArkUIBlendModeOptions* options);
    ArkUI_Int32 (*getDirection)(ArkUINodeHandle node);
    ArkUI_Int32 (*getAlignSelf)(ArkUINodeHandle node);
    ArkUITransformCenterType (*getTransformCenter)(ArkUINodeHandle node);
    ArkUIOpacityTransitionType (*getOpacityTransition)(ArkUINodeHandle node);
    ArkUIRotateTransitionType (*getRotateTransition)(ArkUINodeHandle node);
    ArkUIScaleTransitionType (*getScaleTransition)(ArkUINodeHandle node);
    ArkUITranslateTransitionType (*getTranslateTransition)(ArkUINodeHandle node);
    ArkUIOffsetType (*getOffset)(ArkUINodeHandle node);
    ArkUIAnchorType (*getMarkAnchor)(ArkUINodeHandle node);
    void (*getAlignRules)(ArkUINodeHandle node, ArkUI_CharPtr* anchors, ArkUI_Int32* direction, ArkUI_Int32 length);
    ArkUIBlurStyleOptionType (*getBackgroundBlurStyle)(ArkUINodeHandle node);
    ArkUIImageSizeType (*getBackgroundImageSize)(ArkUINodeHandle node);
    ArkUI_Int32 (*getBackgroundImageSizeWithStyle)(ArkUINodeHandle node);
    void (*setOutlineWidthFloat)(ArkUINodeHandle node, ArkUI_Float32 left, ArkUI_Float32 top,
        ArkUI_Float32 right, ArkUI_Float32 bottom);
    void (*getOutlineWidthFloat)(ArkUINodeHandle node, ArkUI_Float32* borderWidthVector, ArkUI_Int32 borderWidthSize);
    ArkUI_Int32 (*getDisplayPriority)(ArkUINodeHandle node);
    void (*setAlignRulesWidthType)(ArkUINodeHandle node, const ArkUIAlignRulesType* alignRulesType);
    ArkUI_Float32 (*getLayoutWeight)(ArkUINodeHandle node);
    void (*getScale)(ArkUINodeHandle node, ArkUIScaleType* scaleType);
    void (*getRotate)(ArkUINodeHandle node, ArkUIRotateType* rotateType);
    ArkUI_Float32 (*getBrightness)(ArkUINodeHandle node);
    ArkUI_Float32 (*getSaturate)(ArkUINodeHandle node);
    void (*getBackgroundImagePosition)(ArkUINodeHandle node, ArkUIPositionOptions* position, ArkUI_Int32 unit);
    ArkUI_Float32 (*getFlexGrow)(ArkUINodeHandle node);
    ArkUI_Float32 (*getFlexShrink)(ArkUINodeHandle node);
    ArkUI_Float32 (*getFlexBasis)(ArkUINodeHandle node);
    void (*getConstraintSize)(ArkUINodeHandle node, ArkUIConstraintSizeOptions* options, ArkUI_Int32 unit);
    ArkUI_Float32 (*getGrayScale)(ArkUINodeHandle node);
    ArkUI_Float32 (*getInvert)(ArkUINodeHandle node);
    ArkUI_Float32 (*getSepia)(ArkUINodeHandle node);
    ArkUI_Float32 (*getContrast)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getForegroundColor)(ArkUINodeHandle node);
    ArkUI_Float32 (*getBlur)(ArkUINodeHandle node);
    ArkUI_Int32 (*getLinearGradient)(
        ArkUINodeHandle node, ArkUI_Float32* values, ArkUI_Uint32* colors, ArkUI_Float32* stop);
    ArkUI_Int32 (*getAlign)(ArkUINodeHandle node);
    ArkUI_Float32 (*getWidth)(ArkUINodeHandle node, ArkUI_Int32 unit);
    ArkUI_Float32 (*getHeight)(ArkUINodeHandle node, ArkUI_Int32 unit);
    ArkUI_Uint32 (*getBackgroundColor)(ArkUINodeHandle node);
    void (*getBackgroundImage)(ArkUINodeHandle node, ArkUIBackgroundImage* options);
    void (*getPadding)(ArkUINodeHandle node, ArkUI_Float32* values, ArkUI_Int32 length, ArkUI_Int32 unit);
    void (*getPaddingDimension)(ArkUINodeHandle node, ArkUI_Float32* values, ArkUI_Int32* units);
    void (*getConfigSize)(ArkUINodeHandle node, ArkUI_Float32* values, ArkUI_Int32* units);
    ArkUI_CharPtr (*getKey)(ArkUINodeHandle node);
    ArkUI_Int32 (*getEnabled)(ArkUINodeHandle node);
    void (*getMargin)(ArkUINodeHandle node, ArkUI_Float32* values, ArkUI_Int32 length, ArkUI_Int32 unit);
    void (*getMarginDimension)(ArkUINodeHandle node, ArkUI_Float32* values, ArkUI_Int32* units);
    void (*getTranslate)(ArkUINodeHandle node, ArkUI_Float32* values, ArkUI_Int32 unit);
    void (*setMoveTransition)(ArkUINodeHandle node, ArkUI_Int32 value, const ArkUIAnimationOptionType* opacityOption);
    ArkUIMoveTransitionType (*getMoveTransition)(ArkUINodeHandle node);
    void (*resetMask)(ArkUINodeHandle node);
    ArkUI_Float32 (*getAspectRatio)(ArkUINodeHandle node);
    void (*setBackgroundImageResizable)(ArkUINodeHandle node, ArkUIStringAndFloat* options);
    void (*resetBackgroundImageResizable)(ArkUINodeHandle node);
    void (*setBackgroundImageSizeWithUnit)(ArkUINodeHandle node, ArkUI_Float32 valueWidth, ArkUI_Float32 valueHeight,
        ArkUI_Int32 unit);
    ArkUI_Int32 (*getRenderFit)(ArkUINodeHandle node);
    void (*getOutlineColor)(ArkUINodeHandle node, ArkUI_Uint32* values);
    void (*getSize)(ArkUINodeHandle node, ArkUI_Float32* values, ArkUI_Int32 unit);
    ArkUI_Bool (*getRenderGroup)(ArkUINodeHandle node);
    void (*setOnVisibleAreaChange)(
        ArkUINodeHandle node, ArkUI_Int64 extraParam, ArkUI_Float32* values, ArkUI_Int32 size);
    ArkUI_CharPtr (*getGeometryTransition)(ArkUINodeHandle node, ArkUI_Bool* options);
    void (*setChainStyle)(ArkUINodeHandle node, ArkUI_Int32 direction, ArkUI_Int32 style);
    void (*getChainStyle)(ArkUINodeHandle node, ArkUI_Int32* values);
    void (*resetChainStyle)(ArkUINodeHandle node);
    void (*setBias)(ArkUINodeHandle node, ArkUI_Float32 horizontal, ArkUI_Float32 vertical);
    void (*getBias)(ArkUINodeHandle node, ArkUI_Float32* values);
    void (*resetBias)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getColorBlend)(ArkUINodeHandle node);
    ArkUIBlurStyleOptionType (*getForegroundBlurStyle)(ArkUINodeHandle node);
    void (*resetVisibleAreaChange)(ArkUINodeHandle node);
    void (*resetAreaChange)(ArkUINodeHandle node);
};

struct ArkUICommonShapeModifier {
    void (*setStrokeDashArray)(
        ArkUINodeHandle node, const ArkUI_Float32* dashArray, ArkUI_Int32* dimUnits, ArkUI_Int32 size);
    void (*resetStrokeDashArray)(ArkUINodeHandle node);
    void (*setStrokeMiterLimit)(ArkUINodeHandle node, const ArkUI_Float32 miterLimit);
    void (*resetStrokeMiterLimit)(ArkUINodeHandle node);
    void (*setFillOpacity)(ArkUINodeHandle node, const ArkUI_Float32 fillOpacity);
    void (*resetFillOpacity)(ArkUINodeHandle node);
    void (*setStrokeOpacity)(ArkUINodeHandle node, const ArkUI_Float32 strokeOpacity);
    void (*resetStrokeOpacity)(ArkUINodeHandle node);
    void (*setStrokeWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetStrokeWidth)(ArkUINodeHandle node);
    void (*setAntiAlias)(ArkUINodeHandle node, const ArkUI_Bool antiAlias);
    void (*resetAntiAlias)(ArkUINodeHandle node);
    void (*setStroke)(ArkUINodeHandle node, const ArkUI_Uint32 stroke);
    void (*resetStroke)(ArkUINodeHandle node);
    void (*setFill)(ArkUINodeHandle node, const ArkUI_Uint32 fill);
    void (*resetFill)(ArkUINodeHandle node);
    void (*setStrokeDashOffset)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetStrokeDashOffset)(ArkUINodeHandle node);
    void (*setStrokeLineCap)(ArkUINodeHandle node, ArkUI_Int32 strokeLineCap);
    void (*resetStrokeLineCap)(ArkUINodeHandle node);
    void (*setStrokeLineJoin)(ArkUINodeHandle node, ArkUI_Int32 lineJoinStyle);
    void (*resetStrokeLineJoin)(ArkUINodeHandle node);
    void (*setShapeWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetShapeWidth)(ArkUINodeHandle node);
    void (*setShapeHeight)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetShapeHeight)(ArkUINodeHandle node);
    void (*setShapeForegroundColor)(ArkUINodeHandle node, ArkUI_Int32 isColor, ArkUI_Uint32 color);
    void (*resetShapeForegroundColor)(ArkUINodeHandle node);
};

struct ArkUILineModifier {
    void (*setStartPoint)(ArkUINodeHandle node, const ArkUI_Float32* pointValues, const ArkUI_Int32* pointUnits,
        ArkUI_CharPtr pointStr[]);
    void (*resetStartPoint)(ArkUINodeHandle node);
    void (*setEndPoint)(ArkUINodeHandle node, const ArkUI_Float32* pointValues, const ArkUI_Int32* pointUnits,
        ArkUI_CharPtr pointStr[]);
    void (*resetEndPoint)(ArkUINodeHandle node);
};

struct ArkUIPathModifier {
    void (*setPathCommands)(ArkUINodeHandle node, ArkUI_CharPtr commands);
    void (*resetPathCommands)(ArkUINodeHandle node);
};

struct ArkUIPolygonModifier {
    void (*setPolygonPoints)(
        ArkUINodeHandle node, const ArkUI_Float32* pointX, const ArkUI_Float32* pointY, ArkUI_Int32 length);
    void (*resetPolygonPoints)(ArkUINodeHandle node);
};

struct ArkUIPolylineModifier {
    void (*setPoints)(
        ArkUINodeHandle node, const ArkUI_Float32* pointX, const ArkUI_Float32* pointY, ArkUI_Int32 length);
    void (*resetPoints)(ArkUINodeHandle node);
};

struct ArkUIRectModifier {
    void (*setRectRadiusWidth)(ArkUINodeHandle node, ArkUI_Float32 radiusWidthValue, ArkUI_Int32 radiusWidthUnit);
    void (*resetRectRadiusWidth)(ArkUINodeHandle node);
    void (*setRectRadiusHeight)(ArkUINodeHandle node, ArkUI_Float32 radiusHeightValue, ArkUI_Int32 radiusHeightUnit);
    void (*resetRectRadiusHeight)(ArkUINodeHandle node);
    void (*setRectRadiusWithArray)(ArkUINodeHandle node, ArkUI_Float32* radiusValues, ArkUI_Int32* radiusUnits,
        ArkUI_Uint32* radiusValidPairs, ArkUI_Uint32 radiusValidPairsSize);
    void (*setRectRadiusWithValue)(ArkUINodeHandle node, ArkUI_Float32 radiusValue, ArkUI_Int32 radiusUnit);
    void (*resetRectRadius)(ArkUINodeHandle node);
};

struct ArkUIShapeModifier {
    void (*setShapeViewPort)(ArkUINodeHandle node, const ArkUI_Float32* dimValues, const ArkUI_Int32* dimUnits);
    void (*resetShapeViewPort)(ArkUINodeHandle node);
    void (*setShapeMesh)(ArkUINodeHandle node, const ArkUI_Float32* mesh, ArkUI_Uint32 arrayItemCount,
        ArkUI_Int32 column, ArkUI_Int32 row);
    void (*resetShapeMesh)(ArkUINodeHandle node);
};

struct ArkUITextModifier {
    void (*setContent)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*setFontWeight)(ArkUINodeHandle node, ArkUI_Int32 weight);
    void (*resetFontWeight)(ArkUINodeHandle node);
    void (*setFontStyle)(ArkUINodeHandle node, ArkUI_Uint32 fontStyle);
    void (*resetFontStyle)(ArkUINodeHandle node);
    void (*setTextAlign)(ArkUINodeHandle node, ArkUI_Uint32 testAlign);
    void (*resetTextAlign)(ArkUINodeHandle node);
    void (*setFontColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetFontColor)(ArkUINodeHandle node);
    void (*setTextForegroundColor)(ArkUINodeHandle node, ArkUI_Bool isColor, ArkUI_Uint32 color);
    void (*resetTextForegroundColor)(ArkUINodeHandle node);
    void (*setFontSize)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetFontSize)(ArkUINodeHandle node);
    void (*setTextLineHeight)(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit);
    void (*resetTextLineHeight)(ArkUINodeHandle node);
    void (*setTextOverflow)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetTextOverflow)(ArkUINodeHandle node);
    void (*setTextDecoration)(ArkUINodeHandle node, ArkUI_Int32 decoration, ArkUI_Uint32 color, ArkUI_Int32 style);
    void (*resetTextDecoration)(ArkUINodeHandle node);
    void (*setTextCase)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetTextCase)(ArkUINodeHandle node);
    void (*setTextMaxLines)(ArkUINodeHandle node, ArkUI_Uint32 maxLine);
    void (*resetTextMaxLines)(ArkUINodeHandle node);
    void (*setTextMinFontSize)(ArkUINodeHandle node, const ArkUI_Float32 number, ArkUI_Int32 unit);
    void (*resetTextMinFontSize)(ArkUINodeHandle node);
    void (*setTextDraggable)(ArkUINodeHandle node, ArkUI_Uint32 draggable);
    void (*resetTextDraggable)(ArkUINodeHandle node);
    void (*setTextMaxFontSize)(ArkUINodeHandle node, const ArkUI_Float32 number, ArkUI_Int32 unit);
    void (*resetTextMaxFontSize)(ArkUINodeHandle node);
    void (*setTextFontFamily)(ArkUINodeHandle node, ArkUI_CharPtr* fontFamilies, ArkUI_Uint32 length);
    void (*resetTextFontFamily)(ArkUINodeHandle node);
    void (*setTextCopyOption)(ArkUINodeHandle node, ArkUI_Int32 copyOption);
    void (*resetTextCopyOption)(ArkUINodeHandle node);
    void (*setTextShadow)(ArkUINodeHandle node, struct ArkUITextShadowStruct* shadows, ArkUI_Uint32 length);
    void (*resetTextShadow)(ArkUINodeHandle node);
    void (*setTextHeightAdaptivePolicy)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetTextHeightAdaptivePolicy)(ArkUINodeHandle node);
    void (*setTextIndent)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetTextIndent)(ArkUINodeHandle node);
    void (*setTextBaselineOffset)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetTextBaselineOffset)(ArkUINodeHandle node);
    void (*setTextLetterSpacing)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetTextLetterSpacing)(ArkUINodeHandle node);
    void (*setTextFont)(ArkUINodeHandle node, const struct ArkUIFontStruct* fontInfo);
    void (*resetTextFont)(ArkUINodeHandle node);
    void (*setFontWeightStr)(ArkUINodeHandle node, ArkUI_CharPtr weight);
    void (*setWordBreak)(ArkUINodeHandle node, ArkUI_Uint32 wordBreak);
    void (*resetWordBreak)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getFontFamily)(ArkUINodeHandle node);
    ArkUI_Int32 (*getCopyOption)(ArkUINodeHandle node);
    ArkUI_Int32 (*getHeightAdaptivePolicy)(ArkUINodeHandle node);
    ArkUI_Float32 (*getTextMinFontSize)(ArkUINodeHandle node);
    ArkUI_Float32 (*getTextMaxFontSize)(ArkUINodeHandle node);
    void (*getFont)(ArkUINodeHandle node, ArkUITextFont* font);
    ArkUI_Float32 (*getFontSize)(ArkUINodeHandle node, ArkUI_Int32 unit);
    ArkUI_Int32 (*getFontWeight)(ArkUINodeHandle node);
    ArkUI_Int32 (*getItalicFontStyle)(ArkUINodeHandle node);
    void (*setEllipsisMode)(ArkUINodeHandle node, ArkUI_Uint32 ellipsisMode);
    void (*resetEllipsisMode)(ArkUINodeHandle node);
    void (*setEnableDataDetector)(ArkUINodeHandle node, ArkUI_Uint32 enableDataDetector);
    void (*resetEnableDataDetector)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getTextContent)(ArkUINodeHandle node);
    ArkUI_Float32 (*getTextLineHeight)(ArkUINodeHandle node);
    void (*getTextDecoration)(ArkUINodeHandle node, ArkUITextDecorationType* decoration);
    ArkUI_Int32 (*getTextTextCase)(ArkUINodeHandle node);
    ArkUI_Float32 (*getTextLetterSpacing)(ArkUINodeHandle node);
    ArkUI_Int32 (*getTextMaxLines)(ArkUINodeHandle node);
    ArkUI_Int32 (*getTextAlign)(ArkUINodeHandle node);
    ArkUI_Int32 (*getTextTextOverflow)(ArkUINodeHandle node);
    ArkUI_Float32 (*getTextTextIndent)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getFontColor)(ArkUINodeHandle node);
    ArkUI_Float32 (*getTextBaselineOffset)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getTextShadowsCount)(ArkUINodeHandle node);
    void (*getTextShadows)(ArkUINodeHandle node, ArkUITextShadowStruct* textShadow, ArkUI_Uint32 size);
    ArkUI_Int32 (*getTextWordBreak)(ArkUINodeHandle node);
    ArkUI_Int32 (*getTextEllipsisMode)(ArkUINodeHandle node);
    void (*setTextFontFeature)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*resetTextFontFeature)(ArkUINodeHandle node);
    void (*setTextLineSpacing)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    ArkUI_Float32 (*getTextLineSpacing)(ArkUINodeHandle node);
    void (*resetTextLineSpacing)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getTextFontFeature)(ArkUINodeHandle node);
    ArkUI_Int32 (*getEnableDataDetector)(ArkUINodeHandle node);
    void (*setTextDataDetectorConfig)(ArkUINodeHandle node, ArkUI_Uint32* values, ArkUI_Int32 size);
    ArkUI_Int32 (*getTextDataDetectorConfig)(ArkUINodeHandle node, ArkUI_Int32* values);
    void (*resetTextDataDetectorConfig)(ArkUINodeHandle node);
    void (*setLineBreakStrategy)(ArkUINodeHandle node, ArkUI_Uint32 lineBreakStrategy);
    void (*resetLineBreakStrategy)(ArkUINodeHandle node);
    ArkUI_Int32 (*getTextLineBreakStrategy)(ArkUINodeHandle node);
};

struct ArkUIButtonModifier {
    void (*setButtonLabel)(ArkUINodeHandle node, ArkUI_CharPtr label);
    void (*resetButtonLabel)(ArkUINodeHandle node);
    void (*setButtonType)(ArkUINodeHandle node, ArkUI_Int32 type);
    void (*resetButtonType)(ArkUINodeHandle node);
    void (*setButtonStateEffect)(ArkUINodeHandle node, ArkUI_Bool stateEffect);
    void (*resetButtonStateEffect)(ArkUINodeHandle node);
    void (*setButtonFontColor)(ArkUINodeHandle node, ArkUI_Uint32 fontColor);
    void (*resetButtonFontColor)(ArkUINodeHandle node);
    void (*setButtonFontSize)(ArkUINodeHandle node, ArkUI_Float32 fontSizeValue, ArkUI_Int32 fontSizeUnit);
    void (*resetButtonFontSize)(ArkUINodeHandle node);
    void (*setButtonFontWeight)(ArkUINodeHandle node, ArkUI_CharPtr fontWeight);
    void (*resetButtonFontWeight)(ArkUINodeHandle node);
    void (*setButtonFontStyle)(ArkUINodeHandle node, ArkUI_Int32 fontStyle);
    void (*resetButtonFontStyle)(ArkUINodeHandle node);
    void (*setButtonFontFamily)(ArkUINodeHandle node, ArkUI_CharPtr fontFamily);
    void (*resetButtonFontFamily)(ArkUINodeHandle node);
    void (*setButtonLabelStyle)(ArkUINodeHandle node, ArkUI_CharPtr* stringParameters, const ArkUI_Int32* valueArray,
        const ArkUI_Float32* dimensionArray, const ArkUI_Uint32* dataCountArray);
    void (*resetButtonLabelStyle)(ArkUINodeHandle node);
    void (*setButtonBackgroundColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetButtonBackgroundColor)(ArkUINodeHandle node);
    void (*setButtonBorderRadius)(ArkUINodeHandle node, const ArkUI_Float32* values, ArkUI_Int32 valuesSize);
    void (*resetButtonBorderRadius)(ArkUINodeHandle node);
    void (*setButtonFontWeightEnum)(ArkUINodeHandle node, ArkUI_Int32 fontWeight);
    void (*setButtonSize)(ArkUINodeHandle node, ArkUI_CharPtr widthValue, ArkUI_Int32 widthUnit,
        ArkUI_CharPtr heightValue, ArkUI_Int32 heightUnit);
    void (*resetButtonSize)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getButtonLabel)(ArkUINodeHandle node);
    ArkUI_Float32 (*getButtonFontSize)(ArkUINodeHandle node, ArkUI_Int32 unit);
    ArkUI_Int32 (*getButtonFontWeight)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getButtonFontColor)(ArkUINodeHandle node);
    void (*setButtonRole)(ArkUINodeHandle node, ArkUI_Uint32 buttonRole);
    void (*resetButtonRole)(ArkUINodeHandle node);
    void (*setButtonStyle)(ArkUINodeHandle node, ArkUI_Uint32 buttonStyle);
    void (*resetButtonStyle)(ArkUINodeHandle node);
    void (*setButtonControlSize)(ArkUINodeHandle node, ArkUI_Uint32 controlSize);
    void (*resetButtonControlSize)(ArkUINodeHandle node);
    ArkUI_Int32 (*getButtonType)(ArkUINodeHandle node);
};

struct ArkUIImageModifier {
    void (*setSrc)(ArkUINodeHandle node, ArkUI_CharPtr value);
    // Do we need resetSrc() ?
    void (*setImageShowSrc)(ArkUINodeHandle node, ArkUI_CharPtr src, ArkUI_CharPtr bundleName, ArkUI_CharPtr moduleName,
        ArkUI_Bool isUriPureNumber);
    void (*setImageResource)(ArkUINodeHandle node, const ArkUIResource* resource);
    void (*setCopyOption)(ArkUINodeHandle node, ArkUI_Int32 copyOption);
    void (*resetCopyOption)(ArkUINodeHandle node);
    void (*setAutoResize)(ArkUINodeHandle node, ArkUI_Bool autoResize);
    void (*resetAutoResize)(ArkUINodeHandle node);
    void (*setObjectRepeat)(ArkUINodeHandle node, ArkUI_Int32 imageRepeat);
    void (*resetObjectRepeat)(ArkUINodeHandle node);
    void (*setRenderMode)(ArkUINodeHandle node, ArkUI_Int32 imageRenderMode);
    void (*resetRenderMode)(ArkUINodeHandle node);
    void (*setSyncLoad)(ArkUINodeHandle node, ArkUI_Bool syncLoadValue);
    void (*resetSyncLoad)(ArkUINodeHandle node);
    void (*setObjectFit)(ArkUINodeHandle node, ArkUI_Int32 objectFitNumber);
    void (*resetObjectFit)(ArkUINodeHandle node);
    void (*setFitOriginalSize)(ArkUINodeHandle node, ArkUI_Bool fitOriginalSizeValue);
    void (*resetFitOriginalSize)(ArkUINodeHandle node);
    void (*setSourceSize)(ArkUINodeHandle node, ArkUI_Float32 width, ArkUI_Float32 height);
    void (*resetSourceSize)(ArkUINodeHandle node);
    void (*setMatchTextDirection)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetMatchTextDirection)(ArkUINodeHandle node);
    void (*setFillColor)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetFillColor)(ArkUINodeHandle node);
    void (*setAlt)(ArkUINodeHandle node, ArkUI_CharPtr src, ArkUI_CharPtr bundleName, ArkUI_CharPtr moduleName);
    void (*resetAlt)(ArkUINodeHandle node);
    void (*setImageInterpolation)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetImageInterpolation)(ArkUINodeHandle node);
    void (*setColorFilter)(ArkUINodeHandle node, const ArkUI_Float32* array, ArkUI_Int32 length);
    void (*resetColorFilter)(ArkUINodeHandle node);
    void (*setImageSyncLoad)(ArkUINodeHandle node, ArkUI_Bool syncLoadValue);
    void (*resetImageSyncLoad)(ArkUINodeHandle node);
    void (*setImageObjectFit)(ArkUINodeHandle node, ArkUI_Int32 objectFitNumber);
    void (*resetImageObjectFit)(ArkUINodeHandle node);
    void (*setImageFitOriginalSize)(ArkUINodeHandle node, ArkUI_Bool fitOriginalSizeValue);
    void (*resetImageFitOriginalSize)(ArkUINodeHandle node);
    void (*setImageDraggable)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*resetImageDraggable)(ArkUINodeHandle node);
    void (*setImageBorderRadius)(
        ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 length);
    void (*resetImageBorderRadius)(ArkUINodeHandle node);
    void (*setImageBorder)(ArkUINodeHandle node);
    void (*resetImageBorder)(ArkUINodeHandle node);
    void (*setImageOpacity)(ArkUINodeHandle node, ArkUI_Float32 opacity);
    void (*resetImageOpacity)(ArkUINodeHandle node);
    void (*setEdgeAntialiasing)(ArkUINodeHandle node, ArkUI_Float32 edgeAntialiasing);
    void (*resetEdgeAntialiasing)(ArkUINodeHandle node);
    void (*setResizable)(ArkUINodeHandle node, const ArkUIStringAndFloat* options);
    void (*resetResizable)(ArkUINodeHandle node);
    void (*setDynamicRangeMode)(ArkUINodeHandle node, ArkUI_Int32 dynamicRangeMode);
    void (*resetDynamicRangeMode)(ArkUINodeHandle node);
    void (*setEnhancedImageQuality)(ArkUINodeHandle node, ArkUI_Int32 imageQuality);
    void (*resetEnhancedImageQuality)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getImageSrc)(ArkUINodeHandle node);
    ArkUI_Int32 (*getAutoResize)(ArkUINodeHandle node);
    ArkUI_Int32 (*getObjectRepeat)(ArkUINodeHandle node);
    ArkUI_Int32 (*getObjectFit)(ArkUINodeHandle node);
    ArkUI_Int32 (*getImageInterpolation)(ArkUINodeHandle node);
    void (*getColorFilter)(ArkUINodeHandle node, ArkUIFilterColorType* colorFilter);
    ArkUI_CharPtr (*getAlt)(ArkUINodeHandle node);
    ArkUI_Int32 (*getImageDraggable)(ArkUINodeHandle node);
    ArkUI_Int32 (*getRenderMode)(ArkUINodeHandle node);
    void (*setImageResizable)(ArkUINodeHandle node, ArkUI_Float32 left, ArkUI_Float32 top,
        ArkUI_Float32 right, ArkUI_Float32 bottom);
    void (*getImageResizable)(ArkUINodeHandle node, ArkUI_Float32* arrayValue, ArkUI_Int32 size);
    ArkUI_Int32 (*getFitOriginalSize)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getFillColor)(ArkUINodeHandle node);
};

struct ArkUIColumnModifier {
    void (*setColumnJustifyContent)(ArkUINodeHandle node, ArkUI_Int32 flexAlign);
    void (*resetColumnJustifyContent)(ArkUINodeHandle node);
    void (*setColumnAlignItems)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetColumnAlignItems)(ArkUINodeHandle node);
    ArkUI_Int32 (*getColumnJustifyContent)(ArkUINodeHandle node);
    ArkUI_Int32 (*getColumnAlignItems)(ArkUINodeHandle node);
    void (*setColumnSpace)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetColumnSpace)(ArkUINodeHandle node);
};

struct ArkUIRowModifier {
    void (*setRowJustifyContent)(ArkUINodeHandle node, ArkUI_Int32 flexAlign);
    void (*resetRowJustifyContent)(ArkUINodeHandle node);
    void (*setRowAlignItems)(ArkUINodeHandle node, ArkUI_Int32 verticalAlign);
    void (*resetRowAlignItems)(ArkUINodeHandle node);
    ArkUI_Int32 (*getRowJustifyContent)(ArkUINodeHandle node);
    ArkUI_Int32 (*getRowAlignItems)(ArkUINodeHandle node);
    void (*setRowSpace)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetRowSpace)(ArkUINodeHandle node);
};

struct ArkUIDividerModifier {
    void (*setDividerStrokeWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetDividerStrokeWidth)(ArkUINodeHandle node);
    void (*setDividerLineCap)(ArkUINodeHandle node, ArkUI_Int32 lineCap);
    void (*resetDividerLineCap)(ArkUINodeHandle node);
    void (*setDividerColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetDividerColor)(ArkUINodeHandle node);
    void (*setDividerVertical)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*resetDividerVertical)(ArkUINodeHandle node);
};

struct ArkUIFlexModifier {
    void (*setFlexOptions)(ArkUINodeHandle node, ArkUI_Int32* options, ArkUI_Int32 length);
    void (*resetFlexOptions)(ArkUINodeHandle node);
    void (*getFlexOptions)(ArkUINodeHandle node, ArkUIFlexOptions* options);
};

struct ArkUIListModifier {
    void (*setListLanes)(ArkUINodeHandle node, ArkUI_Int32 lanesNum, const struct ArkUIDimensionType* minLength,
        const struct ArkUIDimensionType* maxLength, const struct ArkUIDimensionType* gutter);
    void (*resetListLanes)(ArkUINodeHandle node);
    void (*setEditMode)(ArkUINodeHandle node, ArkUI_Bool editMode);
    void (*resetEditMode)(ArkUINodeHandle node);
    void (*setMultiSelectable)(ArkUINodeHandle node, ArkUI_Bool selectable);
    void (*resetMultiSelectable)(ArkUINodeHandle node);
    void (*setChainAnimation)(ArkUINodeHandle node, ArkUI_Bool chainAnimation);
    void (*resetChainAnimation)(ArkUINodeHandle node);
    void (*setCachedCount)(ArkUINodeHandle node, ArkUI_Int32 cachedCount);
    void (*resetCachedCount)(ArkUINodeHandle node);
    ArkUI_Int32 (*getEnableScrollInteraction)(ArkUINodeHandle node);
    void (*setEnableScrollInteraction)(ArkUINodeHandle node, ArkUI_Bool enableScrollInteraction);
    void (*resetEnableScrollInteraction)(ArkUINodeHandle node);
    ArkUI_Int32 (*getSticky)(ArkUINodeHandle node);
    void (*setSticky)(ArkUINodeHandle node, ArkUI_Int32 stickyStyle);
    void (*resetSticky)(ArkUINodeHandle node);
    ArkUI_Int32 (*getListEdgeEffect)(ArkUINodeHandle node, ArkUI_Int32* values);
    void (*setListEdgeEffect)(ArkUINodeHandle node, ArkUI_Int32 edgeEffect, ArkUI_Bool alwaysEnabled);
    void (*resetListEdgeEffect)(ArkUINodeHandle node);
    ArkUI_Int32 (*getListDirection)(ArkUINodeHandle node);
    void (*setListDirection)(ArkUINodeHandle node, ArkUI_Int32 axis);
    void (*resetListDirection)(ArkUINodeHandle node);
    ArkUI_Float32 (*getListFriction)(ArkUINodeHandle node);
    void (*setListFriction)(ArkUINodeHandle node, ArkUI_Float32 friction);
    void (*resetListFriction)(ArkUINodeHandle node);
    void (*getListNestedScroll)(ArkUINodeHandle node, ArkUI_Int32* values);
    void (*setListNestedScroll)(ArkUINodeHandle node, ArkUI_Int32 forward, ArkUI_Int32 backward);
    void (*resetListNestedScroll)(ArkUINodeHandle node);
    ArkUI_Int32 (*getListScrollBar)(ArkUINodeHandle node);
    void (*setListScrollBar)(ArkUINodeHandle node, ArkUI_Int32 barState);
    void (*resetListScrollBar)(ArkUINodeHandle node);
    ArkUI_Float32 (*getListScrollBarWidth)(ArkUINodeHandle node);
    void (*setListScrollBarWidth)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*resetListScrollBarWidth)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getListScrollBarColor)(ArkUINodeHandle node);
    void (*setListScrollBarColor)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*resetListScrollBarColor)(ArkUINodeHandle node);
    ArkUI_Int32 (*getAlignListItem)(ArkUINodeHandle node);
    void (*setAlignListItem)(ArkUINodeHandle node, ArkUI_Int32 listItemAlign);
    void (*resetAlignListItem)(ArkUINodeHandle node);
    void (*setScrollSnapAlign)(ArkUINodeHandle node, ArkUI_Int32 scrollSnapAlign);
    void (*resetScrollSnapAlign)(ArkUINodeHandle node);
    void (*setContentStartOffset)(ArkUINodeHandle node, ArkUI_Float32 startOffset);
    void (*resetContentStartOffset)(ArkUINodeHandle node);
    void (*setContentEndOffset)(ArkUINodeHandle node, ArkUI_Float32 endOffset);
    void (*resetContentEndOffset)(ArkUINodeHandle node);
    void (*listSetDivider)(ArkUINodeHandle node, const ArkUI_Uint32 color, const ArkUI_Float32* values,
        const ArkUI_Int32* units, ArkUI_Int32 length);
    void (*listResetDivider)(ArkUINodeHandle node);
    void (*setChainAnimationOptions)(
        ArkUINodeHandle node, const struct ArkUIChainAnimationOptionsType* chainAnimationOptions);
    void (*resetChainAnimationOptions)(ArkUINodeHandle node);
    ArkUI_Float32 (*getListSpace)(ArkUINodeHandle node);
    void (*setListSpace)(ArkUINodeHandle node, ArkUI_Float32 space);
    void (*resetListSpace)(ArkUINodeHandle node);
    void (*setFadingEdge)(ArkUINodeHandle node, ArkUI_Bool fadingEdge);
    void (*resetFadingEdge)(ArkUINodeHandle node);
    ArkUI_Int32 (*setNodeAdapter)(ArkUINodeHandle node, ArkUINodeAdapterHandle handle);
    void (*resetNodeAdapter)(ArkUINodeHandle node);
    ArkUINodeAdapterHandle (*getNodeAdapter)(ArkUINodeHandle node);
    ArkUI_Int32 (*getCachedCount)(ArkUINodeHandle node);
    void (*setScrollToIndex)(ArkUINodeHandle node, ArkUI_Int32 index, ArkUI_Int32 animation, ArkUI_Int32 alignment);
    void (*setScrollBy)(ArkUINodeHandle node, ArkUI_Float64 x, ArkUI_Float64 y);
};

struct ArkUIListItemGroupModifier {
    void (*listItemGroupSetDivider)(ArkUINodeHandle node, ArkUI_Uint32 color, const ArkUI_Float32* values,
        const ArkUI_Int32* units, ArkUI_Int32 length);
    void (*listItemGroupResetDivider)(ArkUINodeHandle node);
    void (*listItemGroupSetHeader)(ArkUINodeHandle node, ArkUINodeHandle header);
    void (*listItemGroupSetFooter)(ArkUINodeHandle node, ArkUINodeHandle footer);
};

struct ArkUIParticleModifier {
    void (*SetDisturbanceField)(ArkUINodeHandle node, const ArkUIInt32orFloat32* valuesArray, ArkUI_Int32 length);
    void (*ResetDisturbanceField)(ArkUINodeHandle node);
    void (*SetEmitter)(ArkUINodeHandle node, const ArkUIInt32orFloat32* valuesArray, ArkUI_Int32 length);
    void (*ResetEmitter)(ArkUINodeHandle node);
};

struct ArkUISwiperModifier {
    void (*setSwiperNextMargin)(ArkUINodeHandle node, ArkUI_Float32 nextMarginValue, ArkUI_Int32 nextMarginUnit);
    void (*resetSwiperNextMargin)(ArkUINodeHandle node);
    void (*setSwiperPrevMargin)(ArkUINodeHandle node, ArkUI_Float32 prevMarginValue, ArkUI_Int32 prevMarginUnit);
    void (*resetSwiperPrevMargin)(ArkUINodeHandle node);
    void (*setSwiperDisplayCount)(ArkUINodeHandle node, ArkUI_CharPtr displayCountChar, ArkUI_CharPtr displayCountType);
    void (*resetSwiperDisplayCount)(ArkUINodeHandle node);
    void (*setSwiperDisplayArrow)(ArkUINodeHandle node, ArkUI_CharPtr displayArrowStr);
    void (*resetSwiperDisplayArrow)(ArkUINodeHandle node);
    void (*setSwiperCurve)(ArkUINodeHandle node, ArkUI_CharPtr curveChar);
    void (*resetSwiperCurve)(ArkUINodeHandle node);
    void (*setSwiperDisableSwipe)(ArkUINodeHandle node, ArkUI_Bool disableSwipe);
    void (*resetSwiperDisableSwipe)(ArkUINodeHandle node);
    void (*setSwiperEffectMode)(ArkUINodeHandle node, ArkUI_Int32 edgeEffect);
    void (*resetSwiperEffectMode)(ArkUINodeHandle node);
    void (*setSwiperCachedCount)(ArkUINodeHandle node, ArkUI_Int32 cachedCount);
    void (*resetSwiperCachedCount)(ArkUINodeHandle node);
    void (*setSwiperDisplayMode)(ArkUINodeHandle node, ArkUI_Int32 displayMode);
    void (*resetSwiperDisplayMode)(ArkUINodeHandle node);
    void (*setSwiperItemSpace)(ArkUINodeHandle node, ArkUI_Float32 itemSpaceValue, ArkUI_Int32 itemSpaceUnit);
    void (*resetSwiperItemSpace)(ArkUINodeHandle node);
    void (*setSwiperVertical)(ArkUINodeHandle node, ArkUI_Bool isVertical);
    void (*resetSwiperVertical)(ArkUINodeHandle node);
    void (*setSwiperLoop)(ArkUINodeHandle node, ArkUI_Bool loop);
    void (*resetSwiperLoop)(ArkUINodeHandle node);
    void (*setSwiperInterval)(ArkUINodeHandle node, ArkUI_Int32 interval);
    void (*resetSwiperInterval)(ArkUINodeHandle node);
    void (*setSwiperAutoPlay)(ArkUINodeHandle node, ArkUI_Bool autoPlay);
    void (*resetSwiperAutoPlay)(ArkUINodeHandle node);
    void (*setSwiperIndex)(ArkUINodeHandle node, ArkUI_Int32 index);
    void (*resetSwiperIndex)(ArkUINodeHandle node);
    void (*setSwiperIndicator)(ArkUINodeHandle node, ArkUI_CharPtr indicatorStr);
    void (*resetSwiperIndicator)(ArkUINodeHandle node);
    void (*setSwiperDuration)(ArkUINodeHandle node, ArkUI_Float32 duration);
    void (*resetSwiperDuration)(ArkUINodeHandle node);
    void (*setSwiperEnabled)(ArkUINodeHandle node, ArkUI_Bool enabled);
    void (*resetSwiperEnabled)(ArkUINodeHandle node);
    ArkUI_Int32 (*getSwiperLoop)(ArkUINodeHandle node);
    ArkUI_Int32 (*getSwiperAutoPlay)(ArkUINodeHandle node);
    ArkUI_Int32 (*getSwiperIndex)(ArkUINodeHandle node);
    ArkUI_Int32 (*getSwiperVertical)(ArkUINodeHandle node);
    ArkUI_Float32 (*getSwiperDuration)(ArkUINodeHandle node);
    ArkUI_Int32 (*getSwiperDisplayCount)(ArkUINodeHandle node);
    ArkUI_Float32 (*getSwiperInterval)(ArkUINodeHandle node);
    ArkUI_Int32 (*getSwiperCurve)(ArkUINodeHandle node);
    ArkUI_Int32 (*getSwiperDisableSwipe)(ArkUINodeHandle node);
    ArkUI_Float32 (*getSwiperItemSpace)(ArkUINodeHandle node);
    ArkUI_Int32 (*getSwiperShowIndicator)(ArkUINodeHandle node);
    ArkUI_Int32 (*getSwiperShowDisplayArrow)(ArkUINodeHandle node);
    ArkUI_Int32 (*getSwiperEffectMode)(ArkUINodeHandle node);
    void (*setIndicatorInteractive)(ArkUINodeHandle node, ArkUI_Bool enabled);
    void (*resetIndicatorInteractive)(ArkUINodeHandle node);
    ArkUI_Int32 (*setNodeAdapter)(ArkUINodeHandle node, ArkUINodeAdapterHandle handle);
    void (*resetNodeAdapter)(ArkUINodeHandle node);
    ArkUINodeAdapterHandle (*getNodeAdapter)(ArkUINodeHandle node);
    ArkUI_Int32 (*getCachedCount)(ArkUINodeHandle node);
    void (*setSwiperNestedScroll)(ArkUINodeHandle node, ArkUI_Int32* value);
    void (*resetSwiperNestedScroll)(ArkUINodeHandle node);
    ArkUI_Int32 (*getSwiperNestedScroll)(ArkUINodeHandle node);
    void (*setSwiperToIndex)(ArkUINodeHandle node, ArkUI_Int32* values);
    ArkUI_Float32 (*getSwiperPrevMargin)(ArkUINodeHandle node, ArkUI_Int32 unit);
    ArkUI_Float32 (*getSwiperNextMargin)(ArkUINodeHandle node, ArkUI_Int32 unit);
    void (*setSwiperIndicatorStyle)(ArkUINodeHandle node, ArkUISwiperIndicator* swiperIndicator);
    void (*getSwiperIndicator)(ArkUINodeHandle node, ArkUISwiperIndicator* swiperIndicator);
};

struct ArkUISwiperControllerModifier {
    ArkUINodeHandle (*getSwiperController)(ArkUINodeHandle node);
    void (*setShowNext)(ArkUINodeHandle node);
    void (*setShowPrevious)(ArkUINodeHandle node);
    void (*changeIndex)(ArkUINodeHandle node, ArkUI_Int32 index, ArkUI_Bool useAnimation);
};

struct ArkUIStackModifier {
    void (*setAlignContent)(ArkUINodeHandle node, ArkUI_Int32 alignment);
    void (*resetAlignContent)(ArkUINodeHandle node);
    ArkUI_Int32 (*getAlignContent)(ArkUINodeHandle node);
};

struct ArkUINavigatorModifier {
    void (*setTarget)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*resetTarget)(ArkUINodeHandle node);
    void (*setType)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetType)(ArkUINodeHandle node);
    void (*setActive)(ArkUINodeHandle node, ArkUI_Bool active);
    void (*resetActive)(ArkUINodeHandle node);
    void (*setParams)(ArkUINodeHandle node, ArkUI_CharPtr args);
    void (*resetParams)(ArkUINodeHandle node);
};

struct ArkUINodeContainerModifier {
    void (*rebuild)(ArkUI_Int32 nodeId);
};

struct ArkUITimepickerModifier {
    ArkUI_CharPtr (*getTimepickerSelected)(ArkUINodeHandle node);
    void (*setTimepickerSelected)(ArkUINodeHandle node, ArkUI_Uint32 hour, ArkUI_Uint32 minute);
    void (*resetTimepickerSelected)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getTimepickerBackgroundColor)(ArkUINodeHandle node);
    void (*setTimepickerBackgroundColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    ArkUI_CharPtr (*getTimepickerDisappearTextStyle)(ArkUINodeHandle node);
    void (*setTimepickerDisappearTextStyle)(
        ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_CharPtr fontInfo, ArkUI_Int32 styleVal);
    ArkUI_CharPtr (*getTimepickerTextStyle)(ArkUINodeHandle node);
    void (*setTimepickerTextStyle)(
        ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_CharPtr fontInfo, ArkUI_Int32 styleVal);
    ArkUI_CharPtr (*getTimepickerSelectedTextStyle)(ArkUINodeHandle node);
    void (*setTimepickerSelectedTextStyle)(
        ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_CharPtr fontInfo, ArkUI_Int32 styleVal);
    void (*resetTimepickerDisappearTextStyle)(ArkUINodeHandle node);
    void (*resetTimepickerTextStyle)(ArkUINodeHandle node);
    void (*resetTimepickerSelectedTextStyle)(ArkUINodeHandle node);
    void (*resetTimepickerBackgroundColor)(ArkUINodeHandle node);
    ArkUI_Int32 (*getTimepickerUseMilitaryTime)(ArkUINodeHandle node);
    void (*setTimepickerUseMilitaryTime)(ArkUINodeHandle node, ArkUI_Bool isUseMilitaryTime);
    void (*resetTimepickerUseMilitaryTime)(ArkUINodeHandle node);
    void (*setTimepickerDateTimeOptions)(
        ArkUINodeHandle node, ArkUI_Int32 hourType, ArkUI_Int32 minuteType, ArkUI_Int32 secondType);
    void (*resetTimepickerDateTimeOptions)(ArkUINodeHandle node);
};

struct ArkUIVideoModifier {
    void (*setAutoPlay)(ArkUINodeHandle node, ArkUI_Uint32 autoPlay);
    void (*resetAutoPlay)(ArkUINodeHandle node);
    void (*setVideoObjectFit)(ArkUINodeHandle node, ArkUI_Int32 objectFit);
    void (*resetVideoObjectFit)(ArkUINodeHandle node);
    void (*setVideoControls)(ArkUINodeHandle node, ArkUI_Uint32 controlsValue);
    void (*resetVideoControls)(ArkUINodeHandle node);
    void (*setVideoLoop)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetVideoLoop)(ArkUINodeHandle node);
    void (*setVideoMuted)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetVideoMuted)(ArkUINodeHandle node);
    void (*setVideoOpacity)(ArkUINodeHandle node, ArkUI_Float32 value);
    void (*resetVideoOpacity)(ArkUINodeHandle node);
};

struct ArkUIVideoControllerModifier {
    ArkUINodeHandle (*getVideoController)(ArkUINodeHandle node);
    void (*setVideoStart)(ArkUINodeHandle node);
    void (*setVideoStop)(ArkUINodeHandle node);
    void (*setVideoPause)(ArkUINodeHandle node);
};

struct ArkUIGridModifier {
    void (*setGridColumnsTemplate)(ArkUINodeHandle node, ArkUI_CharPtr columnsTemplate);
    void (*resetGridColumnsTemplate)(ArkUINodeHandle node);
    void (*setGridRowsTemplate)(ArkUINodeHandle node, ArkUI_CharPtr rowsTemplate);
    void (*resetGridRowsTemplate)(ArkUINodeHandle node);
    void (*setGridColumnsGap)(ArkUINodeHandle node, const struct ArkUIResourceLength* columnsGap);
    void (*resetGridColumnsGap)(ArkUINodeHandle node);
    void (*setGridRowsGap)(ArkUINodeHandle node, const struct ArkUIResourceLength* rowsGap);
    void (*resetGridRowsGap)(ArkUINodeHandle node);
    void (*setGridScrollBar)(ArkUINodeHandle node, ArkUI_Int32 scrollBar);
    void (*resetGridScrollBar)(ArkUINodeHandle node);
    void (*setGridScrollBarWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetGridScrollBarWidth)(ArkUINodeHandle node);
    void (*setGridScrollBarColor)(ArkUINodeHandle node, ArkUI_Uint32 scrollBarColor);
    void (*resetGridScrollBarColor)(ArkUINodeHandle node);
    void (*setGridCachedCount)(ArkUINodeHandle node, ArkUI_Int32 cachedCount);
    void (*resetGridCachedCount)(ArkUINodeHandle node);
    void (*setGridEditMode)(ArkUINodeHandle node, ArkUI_Bool editMode);
    void (*resetGridEditMode)(ArkUINodeHandle node);
    void (*setGridMultiSelectable)(ArkUINodeHandle node, ArkUI_Bool multiSelectable);
    void (*resetGridMultiSelectable)(ArkUINodeHandle node);
    void (*setGridMaxCount)(ArkUINodeHandle node, ArkUI_Int32 maxCount);
    void (*resetGridMaxCount)(ArkUINodeHandle node);
    void (*setGridMinCount)(ArkUINodeHandle node, ArkUI_Int32 minCount);
    void (*resetGridMinCount)(ArkUINodeHandle node);
    void (*setGridCellLength)(ArkUINodeHandle node, ArkUI_Int32 cellLength);
    void (*resetGridCellLength)(ArkUINodeHandle node);
    void (*setGridLayoutDirection)(ArkUINodeHandle node, ArkUI_Int32 layoutDirection);
    void (*resetGridLayoutDirection)(ArkUINodeHandle node);
    void (*setGridSupportAnimation)(ArkUINodeHandle node, ArkUI_Bool supportAnimation);
    void (*resetGridSupportAnimation)(ArkUINodeHandle node);

    void (*setEdgeEffect)(ArkUINodeHandle node, ArkUI_Int32 edgeEffect, ArkUI_Bool alwaysEnabled);
    void (*resetEdgeEffect)(ArkUINodeHandle node);
    void (*setNestedScroll)(ArkUINodeHandle node, ArkUI_Int32 forward, ArkUI_Int32 backward);
    void (*resetNestedScroll)(ArkUINodeHandle node);
    void (*setEnableScroll)(ArkUINodeHandle node, ArkUI_Bool scrollEnabled);
    void (*resetEnableScroll)(ArkUINodeHandle node);
    void (*setFriction)(ArkUINodeHandle node, ArkUI_Float32 friction);
    void (*resetFriction)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getGridColumnsTemplate)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getGridRowsTemplate)(ArkUINodeHandle node);
    ArkUI_Float32 (*getGridColumnsGap)(ArkUINodeHandle node);
    ArkUI_Float32 (*getGridRowsGap)(ArkUINodeHandle node);
    ArkUI_Int32 (*setNodeAdapter)(ArkUINodeHandle node, ArkUINodeAdapterHandle handle);
    void (*resetNodeAdapter)(ArkUINodeHandle node);
    ArkUINodeAdapterHandle (*getNodeAdapter)(ArkUINodeHandle node);
    void (*setCachedCount)(ArkUINodeHandle node, ArkUI_Int32 cachedCount);
    void (*resetCachedCount)(ArkUINodeHandle node);
    ArkUI_Int32 (*getCachedCount)(ArkUINodeHandle node);
};

struct ArkUIGridItemModifier {
    void (*setGridItemSelectable)(ArkUINodeHandle node, ArkUI_Bool selectable);
    void (*resetGridItemSelectable)(ArkUINodeHandle node);
    void (*setGridItemSelected)(ArkUINodeHandle node, ArkUI_Bool selected);
    void (*resetGridItemSelected)(ArkUINodeHandle node);
    void (*setGridItemRowStart)(ArkUINodeHandle node, ArkUI_Int32 rowStart);
    void (*resetGridItemRowStart)(ArkUINodeHandle node);
    void (*setGridItemRowEnd)(ArkUINodeHandle node, ArkUI_Int32 rowEnd);
    void (*resetGridItemRowEnd)(ArkUINodeHandle node);
    void (*setGridItemColumnStart)(ArkUINodeHandle node, ArkUI_Int32 columnStart);
    void (*resetGridItemColumnStart)(ArkUINodeHandle node);
    void (*setGridItemColumnEnd)(ArkUINodeHandle node, ArkUI_Int32 columnEnd);
    void (*resetGridItemColumnEnd)(ArkUINodeHandle node);
};

struct ArkUIScrollModifier {
    void (*setScrollNestedScroll)(ArkUINodeHandle node, ArkUI_Int32 scrollForward, ArkUI_Int32 scrollBackward);
    void (*resetScrollNestedScroll)(ArkUINodeHandle node);
    ArkUI_Bool (*getScrollEnableScroll)(ArkUINodeHandle node);
    void (*setScrollEnableScroll)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*resetScrollEnableScroll)(ArkUINodeHandle node);
    ArkUI_Float32 (*getScrollFriction)(ArkUINodeHandle node);
    void (*setScrollFriction)(ArkUINodeHandle node, ArkUI_Float32 value);
    void (*resetScrollFriction)(ArkUINodeHandle node);
    ArkUI_Int32 (*getScrollScrollSnap)(ArkUINodeHandle node, ArkUI_Int32* values);
    void (*setScrollScrollSnap)(ArkUINodeHandle node, const ArkUI_Float32* paginationValue, ArkUI_Int32 paginationSize,
        const ArkUI_Int32* paginationParam, ArkUI_Int32 paramSize);
    void (*resetScrollScrollSnap)(ArkUINodeHandle node);
    ArkUI_Int32 (*getScrollScrollBar)(ArkUINodeHandle node);
    void (*setScrollScrollBar)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetScrollScrollBar)(ArkUINodeHandle node);
    ArkUI_Int32 (*getScrollScrollable)(ArkUINodeHandle node);
    void (*setScrollScrollable)(ArkUINodeHandle node, ArkUI_Int32 scrollDirection);
    void (*resetScrollScrollable)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getScrollScrollBarColor)(ArkUINodeHandle node);
    void (*setScrollScrollBarColor)(ArkUINodeHandle node, ArkUI_Uint32 scrollBarColor);
    void (*resetScrollScrollBarColor)(ArkUINodeHandle node);
    ArkUI_Float32 (*getScrollScrollBarWidth)(ArkUINodeHandle node);
    void (*setScrollScrollBarWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetScrollScrollBarWidth)(ArkUINodeHandle node);
    ArkUI_Int32 (*getScrollEdgeEffect)(ArkUINodeHandle node, ArkUI_Int32* values);
    void (*setScrollEdgeEffect)(ArkUINodeHandle node, ArkUI_Int32 edgeEffect, ArkUI_Bool alwaysEnabled);
    void (*resetScrollEdgeEffect)(ArkUINodeHandle node);
    ArkUI_Bool (*getEnableScrollInteraction)(ArkUINodeHandle node);
    void (*setEnableScrollInteraction)(ArkUINodeHandle node, ArkUI_Bool enableScrollInteraction);
    void (*resetEnableScrollInteraction)(ArkUINodeHandle node);
    void (*setScrollTo)(ArkUINodeHandle node, const ArkUI_Float32* values);
    void (*setScrollEdge)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetScrollTo)(ArkUINodeHandle node);
    void (*resetScrollEdge)(ArkUINodeHandle node);
    ArkUI_Int32 (*getScrollEnablePaging)(ArkUINodeHandle node);
    void (*setScrollEnablePaging)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetScrollEnablePaging)(ArkUINodeHandle node);
    void (*getScrollNestedScroll)(ArkUINodeHandle node, ArkUI_Int32* values);
    void (*getScrollOffset)(ArkUINodeHandle node, ArkUI_Float32* values);
    ArkUI_Int32 (*getScrollEdge)(ArkUINodeHandle node);
    void (*setScrollPage)(ArkUINodeHandle node, ArkUI_Int32 next, ArkUI_Int32 animation);
    void (*setScrollBy)(ArkUINodeHandle node, ArkUI_Float64 x, ArkUI_Float64 y);
};

struct ArkUIListItemModifier {
    void (*setListItemSelected)(ArkUINodeHandle node, ArkUI_Bool selected);
    void (*resetListItemSelected)(ArkUINodeHandle node);
    void (*setSelectable)(ArkUINodeHandle node, ArkUI_Bool selectable);
    void (*resetSelectable)(ArkUINodeHandle node);
};

struct ArkUIScrollBarModifier {
    void (*setScrollBarDirection)(ArkUINodeHandle node, ArkUI_Int32 direction);
    void (*resetScrollBarDirection)(ArkUINodeHandle node);
    void (*setScrollBarState)(ArkUINodeHandle node, ArkUI_Int32 state);
    void (*resetScrollBarState)(ArkUINodeHandle node);
    void (*setScrollBarScroller)(ArkUINodeHandle node, ArkUINodeHandle controller);
};

struct ArkUIScrollerModifier {
    ArkUINodeHandle (*getScroller)(ArkUINodeHandle node, ArkUINodeHandle proxy);
    ArkUINodeHandle (*getScrollerProxy)(ArkUINodeHandle node);
    void (*setScrollToIndex)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*scrollBy)(ArkUINodeHandle node, ArkUI_Float32* values, ArkUI_Int32* units);
    void (*getCurrentOffset)(ArkUINodeHandle node, ArkUI_Float32* out);
};

struct ArkUITabsModifier {
    void (*setTabBarMode)(ArkUINodeHandle node, ArkUI_Int32 tabsBarMode);
    void (*setScrollableBarModeOptions)(
        ArkUINodeHandle node, const ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_Int32 layoutStyle);
    void (*setBarGridAlign)(ArkUINodeHandle node, const ArkUI_Float32* values, ArkUI_Int32 valuesLength,
        const ArkUI_Int32* units, ArkUI_Int32 unitsLength);
    void (*setDivider)(ArkUINodeHandle node, ArkUI_Uint32 color, const ArkUI_Float32* values, const ArkUI_Int32* units,
        ArkUI_Int32 length);
    void (*setFadingEdge)(ArkUINodeHandle node, ArkUI_Bool fadingEdge);
    void (*setBarBackgroundColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*setBarOverlap)(ArkUINodeHandle node, ArkUI_Bool overlap);
    void (*setIsVertical)(ArkUINodeHandle node, ArkUI_Bool isVertical);
    void (*setTabBarPosition)(ArkUINodeHandle node, ArkUI_Int32 barVal);
    void (*setScrollable)(ArkUINodeHandle node, ArkUI_Bool scrollable);
    void (*setTabBarWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*setTabBarHeight)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*setBarAdaptiveHeight)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*setAnimationDuration)(ArkUINodeHandle node, ArkUI_Float32 duration);
    void (*resetTabBarMode)(ArkUINodeHandle node);
    void (*resetScrollableBarModeOptions)(ArkUINodeHandle node);
    void (*resetBarGridAlign)(ArkUINodeHandle node);
    void (*resetDivider)(ArkUINodeHandle node);
    void (*resetFadingEdge)(ArkUINodeHandle node);
    void (*resetBarBackgroundColor)(ArkUINodeHandle node);
    void (*resetBarOverlap)(ArkUINodeHandle node);
    void (*resetIsVertical)(ArkUINodeHandle node);
    void (*resetTabBarPosition)(ArkUINodeHandle node);
    void (*resetScrollable)(ArkUINodeHandle node);
    void (*resetTabBarWidth)(ArkUINodeHandle node);
    void (*resetTabBarHeight)(ArkUINodeHandle node);
    void (*resetBarAdaptiveHeight)(ArkUINodeHandle node);
    void (*resetAnimationDuration)(ArkUINodeHandle node);
    void (*setTabClip)(ArkUINodeHandle node, ArkUI_Bool clipEdge);
    void (*resetTabClip)(ArkUINodeHandle node);
    void (*setTabWidthAuto)(ArkUINodeHandle node);
    void (*resetTabWidthAuto)(ArkUINodeHandle node);
    void (*setTabHeightAuto)(ArkUINodeHandle node);
    void (*resetTabHeightAuto)(ArkUINodeHandle node);
};

struct ArkUIStepperItemModifier {
    void (*setNextLabel)(ArkUINodeHandle node, ArkUI_CharPtr rightLabel);
    void (*resetNextLabel)(ArkUINodeHandle node);
};

struct ArkUITabContentModifier {
    void (*setTabContent)(ArkUINodeHandle node, const ArkUIResource* icon, const ArkUIResource* label);
    void (*setTabContentBuilder)(ArkUINodeHandle node, ArkUI_Int32 methodId);
    void (*setTabContentLabel)(ArkUINodeHandle node, ArkUI_CharPtr label);
    void (*setLayoutMode)(ArkUINodeHandle node, ArkUI_Int32 mode);
    void (*setId)(ArkUINodeHandle node, ArkUI_CharPtr id);
};

struct ArkUITabsControllerModifier {
    ArkUINodeHandle (*getTabsController)(ArkUINodeHandle node);
};

struct ArkUIGesture;

struct ArkUIGestureModifier {
    ArkUIGesture* (*createTapGesture)(ArkUI_Int32 count, ArkUI_Int32 fingers);
    ArkUIGesture* (*createLongPressGesture)(ArkUI_Int32 fingers, bool repeat, ArkUI_Int32 duration);
    ArkUIGesture* (*createPanGesture)(ArkUI_Int32 fingers, ArkUI_Int32 direction, ArkUI_Float64 distance);
    ArkUIGesture* (*createPinchGesture)(ArkUI_Int32 fingers, ArkUI_Float64 distance);
    ArkUIGesture* (*createRotationGesture)(ArkUI_Int32 fingers, ArkUI_Float64 angle);
    ArkUIGesture* (*createSwipeGesture)(ArkUI_Int32 fingers, ArkUI_Int32 directions, ArkUI_Float64 speed);
    ArkUIGesture* (*createSwipeGestureByModifier)(ArkUI_Int32 fingers, ArkUI_Int32 direction, ArkUI_Float64 speed);
    ArkUIGesture* (*createGestureGroup)(ArkUI_Int32 mode);
    void (*addGestureToGestureGroup)(ArkUIGesture* group, ArkUIGesture* child);
    void (*removeGestureFromGestureGroup)(ArkUIGesture* group, ArkUIGesture* child);
    void (*dispose)(ArkUIGesture* recognizer);
    // gesture event will received in common async event queue.
    void (*registerGestureEvent)(ArkUIGesture* gesture, ArkUI_Uint32 actionTypeMask, void* extraParam);
    void (*addGestureToNode)(ArkUINodeHandle node, ArkUIGesture* gesture, ArkUI_Int32 priorityNum, ArkUI_Int32 mask);
    void (*removeGestureFromNode)(ArkUINodeHandle node, ArkUIGesture* recognizer);
    void (*removeGestureFromNodeByTag)(ArkUINodeHandle node, ArkUI_CharPtr gestureTag);
    void (*clearGestures)(ArkUINodeHandle node);
};

struct ArkUISliderModifier {
    void (*setShowTips)(ArkUINodeHandle node, ArkUI_Bool isShow, ArkUI_CharPtr value);
    void (*resetShowTips)(ArkUINodeHandle node);
    void (*setSliderStepSize)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetSliderStepSize)(ArkUINodeHandle node);
    void (*setBlockSize)(ArkUINodeHandle node, ArkUI_Float32 widthVal, ArkUI_Int32 widthUnit, ArkUI_Float32 heightVal,
        ArkUI_Int32 heightUnit);
    void (*resetBlockSize)(ArkUINodeHandle node);
    void (*setTrackBorderRadius)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetTrackBorderRadius)(ArkUINodeHandle node);
    void (*setStepColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetStepColor)(ArkUINodeHandle node);
    void (*setBlockBorderColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetBlockBorderColor)(ArkUINodeHandle node);
    void (*setBlockBorderWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetBlockBorderWidth)(ArkUINodeHandle node);
    void (*setBlockColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetBlockColor)(ArkUINodeHandle node);
    void (*setTrackBackgroundColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetTrackBackgroundColor)(ArkUINodeHandle node);
    void (*setSelectColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetSelectColor)(ArkUINodeHandle node);
    void (*setShowSteps)(ArkUINodeHandle node, ArkUI_Bool showSteps);
    void (*resetShowSteps)(ArkUINodeHandle node);
    void (*setThickness)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetThickness)(ArkUINodeHandle node);
    void (*setSliderValue)(ArkUINodeHandle node, ArkUI_Float32 value);
    void (*setMinLabel)(ArkUINodeHandle node, ArkUI_Float32 value);
    void (*setMaxLabel)(ArkUINodeHandle node, ArkUI_Float32 value);
    void (*setDirection)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*setStep)(ArkUINodeHandle node, ArkUI_Float32 value);
    void (*setReverse)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*setSliderStyle)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetSliderValue)(ArkUINodeHandle node);
    void (*resetMinLabel)(ArkUINodeHandle node);
    void (*resetMaxLabel)(ArkUINodeHandle node);
    void (*resetDirection)(ArkUINodeHandle node);
    void (*resetStep)(ArkUINodeHandle node);
    void (*resetReverse)(ArkUINodeHandle node);
    void (*resetSliderStyle)(ArkUINodeHandle node);
    void (*setSliderBlockImage)(ArkUINodeHandle node, ArkUI_CharPtr src, ArkUI_CharPtr bundle, ArkUI_CharPtr module);
    void (*resetSliderBlockImage)(ArkUINodeHandle node);
    void (*setSliderBlockPath)(
        ArkUINodeHandle node, ArkUI_CharPtr type, const ArkUI_Float32* attribute, ArkUI_CharPtr commands);
    void (*setSliderBlockShape)(
        ArkUINodeHandle node, ArkUI_CharPtr type, const ArkUI_Float32* attribute, ArkUI_Int32 length);
    void (*resetSliderBlockShape)(ArkUINodeHandle node);
    void (*setSliderBlockType)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetSliderBlockType)(ArkUINodeHandle node);

    ArkUI_Uint32 (*getBlockColor)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getTrackBackgroundColor)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getSelectColor)(ArkUINodeHandle node);
    ArkUI_Bool (*getShowSteps)(ArkUINodeHandle node);
    ArkUI_Int32 (*getBlockType)(ArkUINodeHandle node);
    ArkUI_Float32 (*getSliderValue)(ArkUINodeHandle node);
    ArkUI_Float32 (*getMinLabel)(ArkUINodeHandle node);
    ArkUI_Float32 (*getMaxLabel)(ArkUINodeHandle node);
    ArkUI_Int32 (*getDirection)(ArkUINodeHandle node);
    ArkUI_Float32 (*getStep)(ArkUINodeHandle node);
    ArkUI_Bool (*getReverse)(ArkUINodeHandle node);
    ArkUI_Int32 (*getSliderStyle)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getBlockImageValue)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getSliderBlockShape)(ArkUINodeHandle node, ArkUI_Float32* value);
    ArkUI_Float32 (*getThickness)(ArkUINodeHandle node, ArkUI_Int32 unit);
};

struct ArkUIProgressModifier {
    void (*setProgressValue)(ArkUINodeHandle node, ArkUI_Float32 value);
    void (*resetProgressValue)(ArkUINodeHandle node);
    void (*setProgressGradientColor)(
        ArkUINodeHandle node, const struct ArkUIGradientType* gradient, ArkUI_Int32 length);
    void (*setProgressColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetProgressColor)(ArkUINodeHandle node);
    void (*setProgressStyle)(ArkUINodeHandle node, ArkUIProgressStyle* value);
    void (*resetProgressStyle)(ArkUINodeHandle node);
    void (*setProgressBackgroundColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetProgressBackgroundColor)(ArkUINodeHandle node);
    void (*setProgressTotal)(ArkUINodeHandle node, ArkUI_Float32 value);
    void (*setProgressType)(ArkUINodeHandle node, ArkUI_Int32 type);
    void (*resetProgressType)(ArkUINodeHandle node);

    ArkUI_Float32 (*getProgressValue)(ArkUINodeHandle node);
    ArkUI_Float32 (*getProgressTotal)(ArkUINodeHandle node);
    ArkUI_Int32 (*getProgressType)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getProgressColor)(ArkUINodeHandle node);
};

struct ArkUIPluginModifier {
    void (*setPluginWidth)(ArkUINodeHandle node, ArkUI_Float32 widthVal, ArkUI_Int32 widthUnit);
    void (*setPluginHeight)(ArkUINodeHandle node, ArkUI_Float32 heightVal, ArkUI_Int32 heightUnit);
    void (*setPluginSize)(ArkUINodeHandle node, ArkUI_Float32 widthVal, ArkUI_Float32 heightVal, ArkUI_Int32 widthUnit,
        ArkUI_Int32 heightUnit);
    void (*resetPluginWidth)(ArkUINodeHandle node);
    void (*resetPluginHeight)(ArkUINodeHandle node);
    void (*resetPluginSize)(ArkUINodeHandle node);
};

struct ArkUINavDestinationModifier {
    void (*setHideTitleBar)(ArkUINodeHandle node, ArkUI_Bool hideTitle);
    void (*resetHideTitleBar)(ArkUINodeHandle node);
};

struct ArkUITextAreaModifier {
    void (*setTextAreaStyle)(ArkUINodeHandle node, ArkUI_Int32 style);
    void (*resetTextAreaStyle)(ArkUINodeHandle node);
    void (*setTextAreaSelectionMenuHidden)(ArkUINodeHandle node, ArkUI_Uint32 contextMenuHidden);
    void (*resetTextAreaSelectionMenuHidden)(ArkUINodeHandle node);
    void (*setTextAreaMaxLines)(ArkUINodeHandle node, ArkUI_Uint32 maxLine);
    void (*resetTextAreaMaxLines)(ArkUINodeHandle node);
    void (*setTextAreaCopyOption)(ArkUINodeHandle node, ArkUI_Int32 copyOptions);
    void (*resetTextAreaCopyOption)(ArkUINodeHandle node);
    void (*setTextAreaPlaceholderColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetTextAreaPlaceholderColor)(ArkUINodeHandle node);
    void (*setTextAreaTextAlign)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetTextAreaTextAlign)(ArkUINodeHandle node);
    void (*setTextAreaPlaceholderFont)(ArkUINodeHandle node, const struct ArkUIResourceLength* size,
        ArkUI_CharPtr weight, ArkUI_CharPtr family, ArkUI_Int32 style);
    void (*resetTextAreaPlaceholderFont)(ArkUINodeHandle node);
    void (*setTextAreaBarState)(ArkUINodeHandle node, ArkUI_Uint32 barStateValue);
    void (*resetTextAreaBarState)(ArkUINodeHandle node);
    void (*setTextAreaEnableKeyboardOnFocus)(ArkUINodeHandle node, ArkUI_Uint32 keyboardOnFocusValue);
    void (*resetTextAreaEnableKeyboardOnFocus)(ArkUINodeHandle node);
    void (*setTextAreaFontFamily)(ArkUINodeHandle node, ArkUI_CharPtr fontFamily);
    void (*resetTextAreaFontFamily)(ArkUINodeHandle node);
    void (*setTextAreaShowCounter)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetTextAreaShowCounter)(ArkUINodeHandle node);
    void (*setTextAreaCaretColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetTextAreaCaretColor)(ArkUINodeHandle node);
    void (*setTextAreaMaxLength)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetTextAreaMaxLength)(ArkUINodeHandle node);
    void (*setTextAreaFontColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetTextAreaFontColor)(ArkUINodeHandle node);
    void (*setTextAreaFontStyle)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetTextAreaFontStyle)(ArkUINodeHandle node);
    void (*setTextAreaFontWeight)(ArkUINodeHandle node, ArkUI_Int32 fontWeight);
    void (*resetTextAreaFontWeight)(ArkUINodeHandle node);
    void (*setTextAreaFontSize)(ArkUINodeHandle node, const struct ArkUIResourceLength* size);
    void (*resetTextAreaFontSize)(ArkUINodeHandle node);
    void (*setCounterType)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*setTextAreaPlaceholderString)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*setTextAreaTextString)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*stopTextAreaTextEditing)(ArkUINodeHandle node);
    void (*setTextAreaFontWeightStr)(ArkUINodeHandle node, ArkUI_CharPtr fontWeight);
    void (*setTextAreaPlaceholderFontEnum)(ArkUINodeHandle node, const struct ArkUIResourceLength* size,
        ArkUI_Int32 weight, ArkUI_CharPtr family, ArkUI_Int32 style);
    ArkUI_CharPtr (*getTextAreaPlaceholder)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getTextAreaText)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getTextAreaCaretColor)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getTextAreaMaxLength)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getTextAreaPlaceholderColor)(ArkUINodeHandle node);
    void (*getTextAreaPlaceholderFont)(ArkUINodeHandle node, ArkUITextFont* font);
    ArkUI_Bool (*getTextAreaEditing)(ArkUINodeHandle node);
    void (*setTextAreaBackgroundColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetTextAreaBackgroundColor)(ArkUINodeHandle node);
    void (*setTextAreaType)(ArkUINodeHandle node, ArkUI_Int32 type);
    void (*resetTextAreaType)(ArkUINodeHandle node);
    ArkUI_Int32 (*getTextAreaType)(ArkUINodeHandle node);
    ArkUI_Int32 (*getTextAreaTextAlign)(ArkUINodeHandle node);
    void (*setTextAreaShowCounterOptions)(
        ArkUINodeHandle node, ArkUI_Int32 open, ArkUI_Int32 thresholdPercentage, ArkUI_Int32 highlightBorder);
    void (*resetTextAreaShowCounterOptions)(ArkUINodeHandle node);
    void (*getTextAreaShowCounterOptions)(ArkUINodeHandle node, ArkUIShowCountOptions* options);
    void (*setTextAreaDecoration)(ArkUINodeHandle node, ArkUI_Int32 decoration, ArkUI_Uint32 color, ArkUI_Int32 style);
    void (*resetTextAreaDecoration)(ArkUINodeHandle node);
    void (*setTextAreaLetterSpacing)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetTextAreaLetterSpacing)(ArkUINodeHandle node);
    void (*setTextAreaLineHeight)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetTextAreaLineHeight)(ArkUINodeHandle node);
    void (*setTextAreaFontFeature)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*resetTextAreaFontFeature)(ArkUINodeHandle node);
    void (*setTextAreaWordBreak)(ArkUINodeHandle node, ArkUI_Uint32 wordBreak);
    void (*resetTextAreaWordBreak)(ArkUINodeHandle node);
    void (*setTextAreaAdaptMinFontSize)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetTextAreaAdaptMinFontSize)(ArkUINodeHandle node);
    void (*setTextAreaAdaptMaxFontSize)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetTextAreaAdaptMaxFontSize)(ArkUINodeHandle node);
    void (*setTextAreaHeightAdaptivePolicy)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetTextAreaHeightAdaptivePolicy)(ArkUINodeHandle node);
    void (*setTextAreaSelectedBackgroundColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetTextAreaSelectedBackgroundColor)(ArkUINodeHandle node);
    void (*setTextAreaCaretStyle)(
        ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_Uint32 caretColor);
    void (*resetTextAreaCaretStyle)(ArkUINodeHandle node);
    void (*setTextAreaTextOverflow)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetTextAreaTextOverflow)(ArkUINodeHandle node);
    void (*setTextAreaTextIndent)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetTextAreaTextIndent)(ArkUINodeHandle node);
    void (*setTextAreaLineSpacing)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetTextAreaLineSpacing)(ArkUINodeHandle node);
    ArkUI_Bool (*getTextAreaSelectionMenuHidden)(ArkUINodeHandle node);
    ArkUI_Float32 (*getTextAreaAdaptMinFontSize)(ArkUINodeHandle node);
    ArkUI_Float32 (*getTextAreaAdaptMaxFontSize)(ArkUINodeHandle node);
    ArkUI_Float32 (*getTextAreaLineHeight)(ArkUINodeHandle node);
    ArkUI_Int32 (*getTextAreaMaxLines)(ArkUINodeHandle node);
    void (*setTextAreaPadding)(ArkUINodeHandle node, const struct ArkUISizeType* top, const struct ArkUISizeType* right,
        const struct ArkUISizeType* bottom, const struct ArkUISizeType* left);
    void (*resetTextAreaPadding)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getTextAreaFontFeature)(ArkUINodeHandle node);
    void (*setTextAreaOnChange)(ArkUINodeHandle node, void* callback);
    void (*resetTextAreaOnChange)(ArkUINodeHandle node);
    void (*setTextAreaEnterKeyType)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetTextAreaEnterKeyType)(ArkUINodeHandle node);
    void (*setTextAreaInputFilter)(ArkUINodeHandle node, ArkUI_CharPtr value, void* callback);
    void (*resetTextAreaInputFilter)(ArkUINodeHandle node);
    void (*setTextAreaOnTextSelectionChange)(ArkUINodeHandle node, void* callback);
    void (*resetTextAreaOnTextSelectionChange)(ArkUINodeHandle node);
    void (*setTextAreaOnContentScroll)(ArkUINodeHandle node, void* callback);
    void (*resetTextAreaOnContentScroll)(ArkUINodeHandle node);
    void (*setTextAreaOnEditChange)(ArkUINodeHandle node, void* callback);
    void (*resetTextAreaOnEditChange)(ArkUINodeHandle node);
    void (*setTextAreaOnCopy)(ArkUINodeHandle node, void* callback);
    void (*resetTextAreaOnCopy)(ArkUINodeHandle node);
    void (*setTextAreaOnCut)(ArkUINodeHandle node, void* callback);
    void (*resetTextAreaOnCut)(ArkUINodeHandle node);
    void (*setTextAreaOnPaste)(ArkUINodeHandle node, void* callback);
    void (*resetTextAreaOnPaste)(ArkUINodeHandle node);
    void (*setTextAreaLineBreakStrategy)(ArkUINodeHandle node, ArkUI_Uint32 lineBreakStrategy);
    void (*resetTextAreaLineBreakStrategy)(ArkUINodeHandle node);
};

struct ArkUITextInputModifier {
    void (*setTextInputCaretColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetTextInputCaretColor)(ArkUINodeHandle node);
    void (*setTextInputType)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetTextInputType)(ArkUINodeHandle node);
    void (*setTextInputMaxLines)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetTextInputMaxLines)(ArkUINodeHandle node);
    void (*setTextInputPlaceholderColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetTextInputPlaceholderColor)(ArkUINodeHandle node);
    void (*setTextInputCaretPosition)(ArkUINodeHandle node, ArkUI_Int32 caretPosition);
    void (*resetTextInputCaretPosition)(ArkUINodeHandle node);
    void (*setTextInputCopyOption)(ArkUINodeHandle node, ArkUI_Int32 copyOption);
    void (*resetTextInputCopyOption)(ArkUINodeHandle node);
    void (*setTextInputShowPasswordIcon)(ArkUINodeHandle node, ArkUI_Uint32 showPasswordIcon);
    void (*resetTextInputShowPasswordIcon)(ArkUINodeHandle node);
    void (*setTextInputPasswordIcon)(ArkUINodeHandle node, const struct ArkUIPasswordIconType* passwordIcon);
    void (*resetTextInputPasswordIcon)(ArkUINodeHandle node);
    void (*setTextInputTextAlign)(ArkUINodeHandle node, ArkUI_Int32 textAlign);
    void (*resetTextInputTextAlign)(ArkUINodeHandle node);
    void (*setTextInputStyle)(ArkUINodeHandle node, ArkUI_Int32 style);
    void (*resetTextInputStyle)(ArkUINodeHandle node);
    void (*setTextInputSelectionMenuHidden)(ArkUINodeHandle node, ArkUI_Uint32 menuHiddenValue);
    void (*resetTextInputSelectionMenuHidden)(ArkUINodeHandle node);
    void (*setTextInputShowUnderline)(ArkUINodeHandle node, ArkUI_Uint32 showUnderLine);
    void (*resetTextInputShowUnderline)(ArkUINodeHandle node);
    void (*setTextInputCaretStyle)(
        ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_Uint32 caretColor);
    void (*resetTextInputCaretStyle)(ArkUINodeHandle node);
    void (*setTextInputEnableKeyboardOnFocus)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetTextInputEnableKeyboardOnFocus)(ArkUINodeHandle node);
    void (*setTextInputBarState)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetTextInputBarState)(ArkUINodeHandle node);
    void (*setTextInputEnterKeyType)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetTextInputEnterKeyType)(ArkUINodeHandle node);
    void (*setTextInputFontWeight)(ArkUINodeHandle node, ArkUI_Int32 fontWeight);
    void (*resetTextInputFontWeight)(ArkUINodeHandle node);
    void (*setTextInputFontSize)(ArkUINodeHandle node, const struct ArkUILengthType* value);
    void (*resetTextInputFontSize)(ArkUINodeHandle node);
    void (*setTextInputMaxLength)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetTextInputMaxLength)(ArkUINodeHandle node);
    void (*setTextInputSelectedBackgroundColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetTextInputSelectedBackgroundColor)(ArkUINodeHandle node);
    void (*setTextInputShowError)(ArkUINodeHandle node, ArkUI_CharPtr error, ArkUI_Uint32 visible);
    void (*resetTextInputShowError)(ArkUINodeHandle node);
    void (*setTextInputPlaceholderFont)(ArkUINodeHandle node, const struct ArkUIPlaceholderFontType* placeholderFont);
    void (*resetTextInputPlaceholderFont)(ArkUINodeHandle node);
    void (*setTextInputFontColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetTextInputFontColor)(ArkUINodeHandle node);
    void (*setTextInputFontStyle)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetTextInputFontStyle)(ArkUINodeHandle node);
    void (*setTextInputFontFamily)(ArkUINodeHandle node, ArkUI_CharPtr* fontFamilies, ArkUI_Uint32 length);
    void (*resetTextInputFontFamily)(ArkUINodeHandle node);
    void (*setTextInputPlaceholderString)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*setTextInputTextString)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*setTextInputFontWeightStr)(ArkUINodeHandle node, ArkUI_CharPtr fontWeight);
    void (*stopTextInputTextEditing)(ArkUINodeHandle node);
    void (*setTextInputCancelButton)(ArkUINodeHandle node, ArkUI_Int32 style, const struct ArkUISizeType* size,
        ArkUI_Uint32 color, ArkUI_CharPtr src);
    void (*resetTextInputCancelButton)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getTextInputPlaceholder)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getTextInputText)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getTextInputCaretColor)(ArkUINodeHandle node);
    ArkUI_Float32 (*getTextInputCaretStyle)(ArkUINodeHandle node, ArkUI_Int32 unit);
    ArkUI_Bool (*getTextInputShowUnderline)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getTextInputMaxLength)(ArkUINodeHandle node);
    ArkUI_Int32 (*getTextInputEnterKeyType)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getTextInputPlaceholderColor)(ArkUINodeHandle node);
    void (*getTextInputPlaceholderFont)(ArkUINodeHandle node, ArkUITextFont* font);
    ArkUI_Bool (*getTextInputRequestKeyboardOnFocus)(ArkUINodeHandle node);
    ArkUI_Int32 (*getTextInputType)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getTextInputSelectedBackgroundColor)(ArkUINodeHandle node);
    ArkUI_Bool (*getTextInputShowPasswordIcon)(ArkUINodeHandle node);
    ArkUI_Bool (*getTextInputEditing)(ArkUINodeHandle node);
    ArkUI_Bool (*getTextInputShowCancelButton)(ArkUINodeHandle node);
    ArkUI_Float32 (*getTextInputCancelIconSize)(ArkUINodeHandle node, ArkUI_Int32 unit);
    ArkUI_CharPtr (*getTextInputTextCancelIconSrc)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getTextInputTextCancelIconColor)(ArkUINodeHandle node);
    ArkUI_Int32 (*getTextInputTextAlign)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getTextInputFontColor)(ArkUINodeHandle node);
    ArkUI_Int32 (*getTextInputFontStyle)(ArkUINodeHandle node);
    ArkUI_Int32 (*getTextInputFontWeight)(ArkUINodeHandle node);
    ArkUI_Float32 (*getTextInputFontSize)(ArkUINodeHandle node, ArkUI_Int32 unit);
    ArkUI_Int32 (*getTextInputCancelButtonStyle)(ArkUINodeHandle node);
    void (*setTextInputBackgroundColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetTextInputBackgroundColor)(ArkUINodeHandle node);
    void (*setTextInputNormalUnderlineColor)(ArkUINodeHandle node, ArkUI_Uint32 typingColor);
    void (*setTextInputUserUnderlineColor)(ArkUINodeHandle node, const ArkUI_Uint32* values, ArkUI_Int32 length);
    void (*resetTextInputUserUnderlineColor)(ArkUINodeHandle node);
    void (*setTextInputTextSelection)(ArkUINodeHandle node, ArkUI_Int32 start, ArkUI_Int32 end);
    ArkUI_Int32 (*getTextInputTextSelectionIndex)(ArkUINodeHandle node, ArkUI_Bool isEnd);
    void (*setTextInputDecoration)(ArkUINodeHandle node, ArkUI_Int32 decoration, ArkUI_Uint32 color, ArkUI_Int32 style);
    void (*resetTextInputDecoration)(ArkUINodeHandle node);
    void (*setTextInputLetterSpacing)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetTextInputLetterSpacing)(ArkUINodeHandle node);
    void (*setTextInputLineHeight)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetTextInputLineHeight)(ArkUINodeHandle node);
    void (*setTextInputFontFeature)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*resetTextInputFontFeature)(ArkUINodeHandle node);
    void (*setTextInputWordBreak)(ArkUINodeHandle node, ArkUI_Uint32 wordBreak);
    void (*resetTextInputWordBreak)(ArkUINodeHandle node);
    void (*setTextInputPasswordRules)(ArkUINodeHandle node, ArkUI_CharPtr passwordRules);
    void (*resetTextInputPasswordRules)(ArkUINodeHandle node);
    void (*setTextInputEnableAutoFill)(ArkUINodeHandle node, ArkUI_Uint32 enableAutoFill);
    void (*resetTextInputEnableAutoFill)(ArkUINodeHandle node);
    void (*setTextInputPadding)(ArkUINodeHandle node, const struct ArkUISizeType* top,
        const struct ArkUISizeType* right, const struct ArkUISizeType* bottom, const struct ArkUISizeType* left);
    void (*resetTextInputPadding)(ArkUINodeHandle node);
    void (*setTextInputAdaptMinFontSize)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetTextInputAdaptMinFontSize)(ArkUINodeHandle node);
    void (*setTextInputAdaptMaxFontSize)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetTextInputAdaptMaxFontSize)(ArkUINodeHandle node);
    void (*setTextInputHeightAdaptivePolicy)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetTextInputHeightAdaptivePolicy)(ArkUINodeHandle node);
    void (*setTextInputPlaceholderFontEnum)(ArkUINodeHandle node, const struct ArkUIResourceLength* size,
        ArkUI_Int32 weight, ArkUI_CharPtr family, ArkUI_Int32 style);

    void (*setTextInputTextOverflow)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetTextInputTextOverflow)(ArkUINodeHandle node);
    void (*setTextInputTextIndent)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetTextInputTextIndent)(ArkUINodeHandle node);
    void (*setTextInputSelectAll)(ArkUINodeHandle node, ArkUI_Uint32 enableSelectAll);
    void (*resetTextInputSelectAll)(ArkUINodeHandle node);
    void (*setTextInputShowCounter)(
        ArkUINodeHandle node, ArkUI_Uint32 open, ArkUI_Int32 thresholdPercentage, ArkUI_Uint32 highlightBorder);
    void (*resetTextInputShowCounter)(ArkUINodeHandle node);
    void (*setTextInputOnEditChange)(ArkUINodeHandle node, void* callback);
    void (*resetTextInputOnEditChange)(ArkUINodeHandle node);
    void (*setTextInputFilter)(ArkUINodeHandle node, ArkUI_CharPtr value, void* callback);
    void (*resetTextInputFilter)(ArkUINodeHandle node);
    void (*setTextInputOnSubmitWithEvent)(ArkUINodeHandle node, void* callback);
    void (*resetTextInputOnSubmitWithEvent)(ArkUINodeHandle node);
    void (*setTextInputOnChange)(ArkUINodeHandle node, void* callback);
    void (*resetTextInputOnChange)(ArkUINodeHandle node);
    void (*setTextInputOnTextSelectionChange)(ArkUINodeHandle node, void* callback);
    void (*resetTextInputOnTextSelectionChange)(ArkUINodeHandle node);
    void (*setTextInputOnContentScroll)(ArkUINodeHandle node, void* callback);
    void (*resetTextInputOnContentScroll)(ArkUINodeHandle node);
    void (*setTextInputOnCopy)(ArkUINodeHandle node, void* callback);
    void (*resetTextInputOnCopy)(ArkUINodeHandle node);
    void (*setTextInputOnCut)(ArkUINodeHandle node, void* callback);
    void (*resetTextInputOnCut)(ArkUINodeHandle node);
    void (*setTextInputOnPaste)(ArkUINodeHandle node, void* callback);
    void (*resetTextInputOnPaste)(ArkUINodeHandle node);
    ArkUI_Bool (*getTextInputSelectionMenuHidden)(ArkUINodeHandle node);
    void (*setTextInputShowPassword)(ArkUINodeHandle node, ArkUI_Uint32 showPassword);
    void (*resetTextInputShowPassword)(ArkUINodeHandle node);
    ArkUI_Bool (*getTextInputShowPassword)(ArkUINodeHandle node);
    ArkUI_Int32 (*getTextInputWordBreak)(ArkUINodeHandle node);
    ArkUI_Int32 (*getTextInputEnableAutoFill)(ArkUINodeHandle node);
    void (*setTextInputContentType)(ArkUINodeHandle node, ArkUI_Uint32 contentType);
    void (*resetTextInputContentType)(ArkUINodeHandle node);
    ArkUI_Int32 (*getTextInputContentType)(ArkUINodeHandle node);
    void (*getTextInputUserUnderlineColor)(ArkUINodeHandle node, ArkUI_Uint32* values);
    ArkUI_CharPtr (*getTextInputPasswordRules)(ArkUINodeHandle node);
    ArkUI_Int32 (*getTextInputSelectAll)(ArkUINodeHandle node);
    void (*setTextInputInputFilter)(ArkUINodeHandle node, ArkUI_CharPtr inputFilter);
    ArkUI_CharPtr (*getTextInputInputFilter)(ArkUINodeHandle node);
    void (*resetTextInputInputFilter)(ArkUINodeHandle node);
    ArkUI_Int32 (*getTextInputCaretIndex)(ArkUINodeHandle node);
    void (*getTextInputCaretOffset)(ArkUINodeHandle node, ArkUI_Float32* values);
    ArkUI_Int32 (*getTextInputStyle)(ArkUINodeHandle node);
    void (*getTextInputContentRect)(ArkUINodeHandle node, ArkUI_Float32* values);
    ArkUI_Int32 (*getTextInputContentLinesNum)(ArkUINodeHandle node);
    void (*setBlurOnSubmit)(ArkUINodeHandle node, ArkUI_Bool blurOnSubmit);
    ArkUI_Bool (*getBlurOnSubmit)(ArkUINodeHandle node);
    ArkUI_Float32 (*getTextInputAdaptMinFontSize)(ArkUINodeHandle node);
    ArkUI_Float32 (*getTextInputAdaptMaxFontSize)(ArkUINodeHandle node);
    ArkUI_Float32 (*getTextInputLineHeight)(ArkUINodeHandle node);
    ArkUI_Int32 (*getTextInputMaxLines)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getTextInputFontFeature)(ArkUINodeHandle node);
    void (*setTextInputCustomKeyboard)(ArkUINodeHandle node, ArkUINodeHandle customKeyboard, bool supportAvoidance);
    ArkUINodeHandle (*getTextInputCustomKeyboard)(ArkUINodeHandle node);
    ArkUI_Int32 (*getTextInputCustomKeyboardOption)(ArkUINodeHandle node);
    void (*resetTextInputCustomKeyboard)(ArkUINodeHandle node);
    void (*setTextInputLineBreakStrategy)(ArkUINodeHandle node, ArkUI_Uint32 lineBreakStrategy);
    void (*resetTextInputLineBreakStrategy)(ArkUINodeHandle node);
};

struct ArkUIWebModifier {
    ArkUINodeHandle (*getWebController)(ArkUINodeHandle node);
    ArkUINodeHandle (*getWebviewController)(ArkUINodeHandle node);
    void (*setWebOptions)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*setWebSrcResources)(ArkUINodeHandle node, ArkUI_Int32 id, ArkUI_Int32 type, ArkUI_CharPtr name,
        ArkUI_CharPtr bundleName, ArkUI_CharPtr moduleName);
    void (*setWebMixedMode)(ArkUINodeHandle node, ArkUI_Int32 value);
};

struct ArkUIBlankModifier {
    void (*setColor)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetColor)(ArkUINodeHandle node);
    void (*setBlankHeight)(ArkUINodeHandle node, ArkUI_Float32 heightValue, ArkUI_Int32 heightUnit);
    void (*resetBlankHeight)(ArkUINodeHandle node);
    void (*setBlankMin)(ArkUINodeHandle node, ArkUI_Float32 minValue, ArkUI_Int32 minUnit);
    void (*resetBlankMin)(ArkUINodeHandle node);
};

struct ArkUICounterModifier {
    void (*setEnableInc)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*resetEnableInc)(ArkUINodeHandle node);
    void (*setEnableDec)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*resetEnableDec)(ArkUINodeHandle node);
    void (*setCounterHeight)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetCounterHeight)(ArkUINodeHandle node);
    void (*setCounterWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetCounterWidth)(ArkUINodeHandle node);
    void (*setCounterBackgroundColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetCounterBackgroundColor)(ArkUINodeHandle node);
};

struct ArkUICheckboxModifier {
    void (*setSelect)(ArkUINodeHandle node, ArkUI_Bool isSelected);
    void (*setSelectedColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*setUnSelectedColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*setCheckboxWidth)(ArkUINodeHandle node, ArkUI_Float32 widthVal, ArkUI_Int32 widthUnit);
    void (*setCheckboxHeight)(ArkUINodeHandle node, ArkUI_Float32 heightVal, ArkUI_Int32 heightUnit);
    void (*setMark)(ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_Float32 sizeValue, ArkUI_Int32 sizeUnit,
        ArkUI_Float32 widthValue, ArkUI_Int32 widthUnit);
    void (*setCheckboxPadding)(
        ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Uint32 length);
    void (*setCheckboxResponseRegion)(
        ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Uint32 length);

    void (*resetSelect)(ArkUINodeHandle node);
    void (*resetSelectedColor)(ArkUINodeHandle node);
    void (*resetUnSelectedColor)(ArkUINodeHandle node);
    void (*resetCheckboxWidth)(ArkUINodeHandle node);
    void (*resetCheckboxHeight)(ArkUINodeHandle node);
    void (*resetMark)(ArkUINodeHandle node);
    void (*setCheckboxShape)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetCheckboxShape)(ArkUINodeHandle node);
    void (*resetCheckboxPadding)(ArkUINodeHandle node);
    void (*resetCheckboxResponseRegion)(ArkUINodeHandle node);

    ArkUI_Bool (*getSelect)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getSelectedColor)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getUnSelectedColor)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getCheckMarkColor)(ArkUINodeHandle node);
    ArkUI_Float64 (*getCheckMarkSize)(ArkUINodeHandle node);
    ArkUI_Float64 (*getCheckMarkWidth)(ArkUINodeHandle node);
    ArkUI_Int32 (*getCheckboxShape)(ArkUINodeHandle node);
};

struct ArkUICheckboxGroupModifier {
    void (*setCheckboxGroupSelectedColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetCheckboxGroupSelectedColor)(ArkUINodeHandle node);
    void (*setCheckboxGroupUnSelectedColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetCheckboxGroupUnSelectedColor)(ArkUINodeHandle node);
    void (*setCheckboxGroupSelectAll)(ArkUINodeHandle node, ArkUI_Bool isSelected);
    void (*resetCheckboxGroupSelectAll)(ArkUINodeHandle node);
    void (*setCheckboxGroupWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue);
    void (*resetCheckboxGroupWidth)(ArkUINodeHandle node);
    void (*setCheckboxGroupHeight)(
        ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue);
    void (*resetCheckboxGroupHeight)(ArkUINodeHandle node);
    void (*setCheckboxGroupMark)(
        ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_Float32 sizeValue, ArkUI_Float32 widthValue);
    void (*resetCheckboxGroupMark)(ArkUINodeHandle node);
    void (*setCheckboxGroupStyle)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetCheckboxGroupStyle)(ArkUINodeHandle node);
};

struct ArkUIImageSpanModifier {
    void (*setImageSpanVerticalAlign)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetImageSpanVerticalAlign)(ArkUINodeHandle node);
    void (*setImageSpanObjectFit)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetImageSpanObjectFit)(ArkUINodeHandle node);
    ArkUI_Int32 (*getImageSpanVerticalAlign)(ArkUINodeHandle node);
    ArkUI_Int32 (*getImageSpanObjectFit)(ArkUINodeHandle node);
    void (*setImageSpanTextBackgroundStyle)(ArkUINodeHandle node, ArkUI_Uint32 color, const ArkUI_Float32* values,
        const ArkUI_Int32* units, ArkUI_Int32 length);
    void (*resetImageSpanTextBackgroundStyle)(ArkUINodeHandle node);
    void (*getImageSpanTextBackgroundStyle)(ArkUINodeHandle node, ArkUITextBackgroundStyleOptions* options);
    void (*setImageSpanBaselineOffset)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetImageSpanBaselineOffset)(ArkUINodeHandle node);
};

struct ArkUIMenuModifier {
    void (*setMenuFontColor)(ArkUINodeHandle node, ArkUI_Uint32 colorVal);
    void (*resetMenuFontColor)(ArkUINodeHandle node);
    void (*setFont)(ArkUINodeHandle node, ArkUI_CharPtr fontInfo, ArkUI_Int32 styleVal);
    void (*resetFont)(ArkUINodeHandle node);
    void (*setRadius)(ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units);
    void (*resetRadius)(ArkUINodeHandle node);
    void (*setMenuWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetMenuWidth)(ArkUINodeHandle node);
};

struct ArkUIWaterFlowModifier {
    void (*resetColumnsTemplate)(ArkUINodeHandle node);
    void (*setColumnsTemplate)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*resetRowsTemplate)(ArkUINodeHandle node);
    void (*setRowsTemplate)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*resetWaterFlowEnableScrollInteraction)(ArkUINodeHandle node);
    void (*setWaterFlowEnableScrollInteraction)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*setColumnsGap)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue);
    void (*resetColumnsGap)(ArkUINodeHandle node);
    void (*setRowsGap)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue);
    void (*resetRowsGap)(ArkUINodeHandle node);
    void (*setItemMinWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue);
    void (*resetItemMinWidth)(ArkUINodeHandle node);
    void (*setItemMaxWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue);
    void (*resetItemMaxWidth)(ArkUINodeHandle node);
    void (*setItemMinHeight)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue);
    void (*resetItemMinHeight)(ArkUINodeHandle node);
    void (*setItemMaxHeight)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue);
    void (*resetItemMaxHeight)(ArkUINodeHandle node);
    void (*setLayoutDirection)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetLayoutDirection)(ArkUINodeHandle node);
    void (*setWaterFlowNestedScroll)(ArkUINodeHandle node, ArkUI_Int32 scrollForward, ArkUI_Int32 scrollBackward);
    void (*resetWaterFlowNestedScroll)(ArkUINodeHandle node);
    void (*setWaterFlowFriction)(ArkUINodeHandle node, ArkUI_Float32 friction);
    void (*resetWaterFlowFriction)(ArkUINodeHandle node);
    ArkUI_Int32 (*getLayoutDirection)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getColumnsTemplate)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getRowsTemplate)(ArkUINodeHandle node);
    ArkUI_Float32 (*getColumnsGap)(ArkUINodeHandle node);
    ArkUI_Float32 (*getRowsGap)(ArkUINodeHandle node);
    void (*getWaterFlowNestedScroll)(ArkUINodeHandle node, ArkUI_Int32* value);
    ArkUI_Int32 (*setNodeAdapter)(ArkUINodeHandle node, ArkUINodeAdapterHandle handle);
    void (*resetNodeAdapter)(ArkUINodeHandle node);
    ArkUINodeAdapterHandle (*getNodeAdapter)(ArkUINodeHandle node);
    void (*setCachedCount)(ArkUINodeHandle node, ArkUI_Int32 cachedCount);
    void (*resetCachedCount)(ArkUINodeHandle node);
    ArkUI_Int32 (*getCachedCount)(ArkUINodeHandle node);
    void (*setEdgeEffect)(ArkUINodeHandle node, ArkUI_Int32 edgeEffect, ArkUI_Bool alwaysEnabled);
    void (*resetEdgeEffect)(ArkUINodeHandle node);
    void (*setWaterFlowScrollBar)(ArkUINodeHandle node, ArkUI_Int32 barState);
    void (*resetWaterFlowScrollBar)(ArkUINodeHandle node);
    ArkUI_Int32 (*getWaterFlowScrollBar)(ArkUINodeHandle node);
    void (*setWaterFlowScrollBarWidth)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*resetWaterFlowScrollBarWidth)(ArkUINodeHandle node);
    ArkUI_Float32 (*getWaterFlowScrollBarWidth)(ArkUINodeHandle node);
    void (*setWaterFlowScrollBarColor)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*resetWaterFlowScrollBarColor)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getWaterFlowScrollBarColor)(ArkUINodeHandle node);
    ArkUI_Int32 (*getEdgeEffect)(ArkUINodeHandle node, ArkUI_Int32* values);
    void (*setSectionOption)(ArkUINodeHandle node, ArkUI_Int32 start, ArkUIWaterFlowSectionOption option);
    void (*resetSectionOption)(ArkUINodeHandle node);
    void (*getSectionOption)(ArkUINodeHandle node, ArkUIWaterFlowSectionOption option);
    ArkUI_Float32 (*getItemMinWidth)(ArkUINodeHandle node, ArkUI_Int32 unit);
    ArkUI_Float32 (*getItemMaxWidth)(ArkUINodeHandle node, ArkUI_Int32 unit);
    ArkUI_Float32 (*getItemMinHeight)(ArkUINodeHandle node, ArkUI_Int32 unit);
    ArkUI_Float32 (*getItemMaxHeight)(ArkUINodeHandle node, ArkUI_Int32 unit);
    ArkUI_Int32 (*getWaterFlowEnableScrollInteraction)(ArkUINodeHandle node);
    ArkUI_Float32 (*getWaterFlowFriction)(ArkUINodeHandle node);
    void (*setScrollToIndex)(ArkUINodeHandle node, ArkUI_Int32 index, ArkUI_Int32 animation, ArkUI_Int32 alignment);
    void (*setWaterflowFooter)(ArkUINodeHandle node, ArkUINodeHandle footer);
    void (*resetWaterflowFooter)(ArkUINodeHandle node);
};

struct ArkUIMenuItemModifier {
    void (*setMenuItemSelected)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*resetMenuItemSelected)(ArkUINodeHandle node);
    void (*setLabelFontColor)(ArkUINodeHandle node, const ArkUI_Uint32 colorVal);
    void (*resetLabelFontColor)(ArkUINodeHandle node);
    void (*setContentFontColor)(ArkUINodeHandle node, const ArkUI_Uint32 colorVal);
    void (*resetContentFontColor)(ArkUINodeHandle node);
    void (*setLabelFont)(ArkUINodeHandle node, ArkUI_CharPtr fontInfo, ArkUI_Int32 styleVal);
    void (*resetLabelFont)(ArkUINodeHandle node);
    void (*setContentFont)(ArkUINodeHandle node, ArkUI_CharPtr fontInfo, ArkUI_Int32 styleVal);
    void (*resetContentFont)(ArkUINodeHandle node);
    void (*setSelectIcon)(ArkUINodeHandle node, ArkUI_Bool showIcon);
    void (*resetSelectIcon)(ArkUINodeHandle node);
    void (*setSelectIconSrc)(ArkUINodeHandle node, ArkUI_CharPtr iconSrc);
    void (*resetSelectIconSrc)(ArkUINodeHandle node);
};

struct ArkUIMenuItemGroupModifier {
    void (*setMenuItemGroupHeader)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*setMenuItemGroupFooter)(ArkUINodeHandle node, ArkUI_CharPtr value);
};

struct ArkUIToggleModifier {
    void (*setToggleSelectedColor)(ArkUINodeHandle node, ArkUI_Uint32 selectedColor);
    void (*resetToggleSelectedColor)(ArkUINodeHandle node);
    void (*setToggleSwitchPointColor)(ArkUINodeHandle node, ArkUI_Uint32 switchPointColor);
    void (*resetToggleSwitchPointColor)(ArkUINodeHandle node);
    void (*setToggleHeight)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetToggleHeight)(ArkUINodeHandle node);
    void (*setToggleResponseRegion)(
        ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Uint32 length);
    void (*resetToggleResponseRegion)(ArkUINodeHandle node);
    void (*setTogglePadding)(ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Uint32 length);
    void (*resetTogglePadding)(ArkUINodeHandle node);
    void (*setToggleBackgroundColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetToggleBackgroundColor)(ArkUINodeHandle node);
    void (*setToggleHoverEffect)(ArkUINodeHandle node, ArkUI_Int32 hoverEffectValue);
    void (*resetToggleHoverEffect)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getToggleSelectedColor)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getToggleSwitchPointColor)(ArkUINodeHandle node);
    void (*setToggleIsOn)(ArkUINodeHandle node, ArkUI_Bool isOn);
    void (*resetToggleIsOn)(ArkUINodeHandle node);
    ArkUI_Int32 (*getToggleIsOn)(ArkUINodeHandle node);
    void (*setTogglePointRadius)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetTogglePointRadius)(ArkUINodeHandle node);
    void (*setToggleUnselectedColor)(ArkUINodeHandle node, ArkUI_Uint32 unselectedColor);
    void (*resetToggleUnselectedColor)(ArkUINodeHandle node);
    void (*setToggleTrackBorderRadius)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetToggleTrackBorderRadius)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getToggleUnselectedColor)(ArkUINodeHandle node);
};

struct ArkUINavigationModifier {
    void (*setHideToolBar)(ArkUINodeHandle node, ArkUI_Bool hide);
    void (*resetHideToolBar)(ArkUINodeHandle node);
    void (*setHideNavBar)(ArkUINodeHandle node, ArkUI_Bool hideNavBar);
    void (*resetHideNavBar)(ArkUINodeHandle node);
    void (*setTitleMode)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetTitleMode)(ArkUINodeHandle node);
    void (*setHideBackButton)(ArkUINodeHandle node, ArkUI_Bool hideBackButton);
    void (*resetHideBackButton)(ArkUINodeHandle node);
    void (*setSubtitle)(ArkUINodeHandle node, ArkUI_CharPtr subtitle);
    void (*resetSubtitle)(ArkUINodeHandle node);
    void (*resetUsrNavigationMode)(ArkUINodeHandle node);
    void (*setUsrNavigationMode)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*setNavHideTitleBar)(ArkUINodeHandle node, ArkUI_Bool hideTitle);
    void (*resetNavHideTitleBar)(ArkUINodeHandle node);
    void (*setNavBarPosition)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetNavBarPosition)(ArkUINodeHandle node);
    void (*setMinContentWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetMinContentWidth)(ArkUINodeHandle node);
    void (*setMaxNavBarWidth)(ArkUINodeHandle node, ArkUI_Float32 maxValue, ArkUI_Int32 maxUnit);
    void (*resetMaxNavBarWidth)(ArkUINodeHandle node);
    void (*setMinNavBarWidth)(ArkUINodeHandle node, ArkUI_Float32 minValue, ArkUI_Int32 minUnit);
    void (*resetMinNavBarWidth)(ArkUINodeHandle node);
    void (*setNavBarWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetNavBarWidth)(ArkUINodeHandle node);
};

struct ArkUINavRouterModifier {
    void (*setNavRouteMode)(ArkUINodeHandle node, ArkUI_Int32 mode);
    void (*resetNavRouteMode)(ArkUINodeHandle node);
};

struct ArkUIGaugeModifier {
    void (*setGaugeValue)(ArkUINodeHandle node, ArkUI_Float32 value);
    void (*resetGaugeValue)(ArkUINodeHandle node);
    void (*setGaugeStartAngle)(ArkUINodeHandle node, ArkUI_Float32 value);
    void (*resetGaugeStartAngle)(ArkUINodeHandle node);
    void (*setGaugeEndAngle)(ArkUINodeHandle node, ArkUI_Float32 value);
    void (*resetGaugeEndAngle)(ArkUINodeHandle node);
    void (*setGaugeStrokeWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetGaugeStrokeWidth)(ArkUINodeHandle node);
    void (*setShadowOptions)(ArkUINodeHandle node, ArkUI_Float32 radius, ArkUI_Float32 offsetX, ArkUI_Float32 offsetY,
        ArkUI_Bool isShadowVisible);
    void (*resetShadowOptions)(ArkUINodeHandle node);
    void (*setIsShowIndicator)(ArkUINodeHandle node, ArkUI_Bool isShowIndicator);
    void (*setIndicatorIconPath)(
        ArkUINodeHandle node, ArkUI_CharPtr iconPath, ArkUI_CharPtr bundleName, ArkUI_CharPtr moduleName);
    void (*resetIndicatorIconPath)(ArkUINodeHandle node);
    void (*setIndicatorSpace)(
        ArkUINodeHandle node, ArkUI_CharPtr spaceStrValue, ArkUI_Float32 spaceValue, ArkUI_Int32 spaceUnit);
    void (*resetIndicatorSpace)(ArkUINodeHandle node);
    void (*setColors)(
        ArkUINodeHandle node, const ArkUI_Uint32* colors, const ArkUI_Float32* weight, ArkUI_Uint32 length);
    void (*resetColors)(ArkUINodeHandle node);
    void (*setGradientColors)(
        ArkUINodeHandle node, const struct ArkUIGradientType* gradient, ArkUI_Uint32 weightLength);
    void (*resetGradientColors)(ArkUINodeHandle node);
};

struct ArkUIBadgeModifier {
    void (*setBadgeParameters)(ArkUINodeHandle node, ArkUI_Int32* intValue, ArkUI_Float32* floatValue);
    void (*setBadgeValue)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*setBadgeCount)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*setBadgeMaxCount)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*setBadgeFontWeight)(ArkUINodeHandle node, ArkUI_Int32 value);
};

struct ArkUIRefreshModifier {
    void (*setRefreshing)(ArkUINodeHandle node, ArkUI_Bool value);
    ArkUI_Bool (*getRefreshing)(ArkUINodeHandle node);
    void (*setRefreshOffset)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetRefreshOffset)(ArkUINodeHandle node);
    void (*setPullToRefresh)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*resetPullToRefresh)(ArkUINodeHandle node);
    void (*setRefreshContent)(ArkUINodeHandle node, ArkUINodeHandle content);
};

struct ArkUIHyperlinkModifier {
    void (*setHyperlinkColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetHyperlinkColor)(ArkUINodeHandle node);
    void (*setHyperlinkDraggable)(ArkUINodeHandle node, ArkUI_Bool draggable);
    void (*resetHyperlinkDraggable)(ArkUINodeHandle node);
};

struct ArkUIAlphabetIndexerModifier {
    void (*setPopupItemFont)(ArkUINodeHandle node, ArkUI_Float32 size, ArkUI_Int32 unit, ArkUI_CharPtr weight);
    void (*resetPopupItemFont)(ArkUINodeHandle node);
    void (*setSelectedFont)(ArkUINodeHandle node, ArkUI_CharPtr fontInfo, ArkUI_Int32 style);
    void (*resetSelectedFont)(ArkUINodeHandle node);
    void (*setPopupFont)(ArkUINodeHandle node, ArkUI_CharPtr fontInfo, ArkUI_Int32 style);
    void (*resetPopupFont)(ArkUINodeHandle node);
    void (*setAlphabetIndexerFont)(ArkUINodeHandle node, ArkUI_CharPtr fontInfo, ArkUI_Int32 style);
    void (*resetAlphabetIndexerFont)(ArkUINodeHandle node);
    void (*setPopupItemBackgroundColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetPopupItemBackgroundColor)(ArkUINodeHandle node);
    void (*setAlphabetIndexerColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetAlphabetIndexerColor)(ArkUINodeHandle node);
    void (*setPopupColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetPopupColor)(ArkUINodeHandle node);
    void (*setAlphabetIndexerSelectedColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetAlphabetIndexerSelectedColor)(ArkUINodeHandle node);
    void (*setPopupBackground)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetPopupBackground)(ArkUINodeHandle node);
    void (*setSelectedBackgroundColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetSelectedBackgroundColor)(ArkUINodeHandle node);
    void (*setPopupUnselectedColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetPopupUnselectedColor)(ArkUINodeHandle node);
    void (*setAlignStyle)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetAlignStyle)(ArkUINodeHandle node);
    void (*setUsingPopup)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*resetUsingPopup)(ArkUINodeHandle node);
    void (*setAlphabetIndexerSelected)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetAlphabetIndexerSelected)(ArkUINodeHandle node);
    void (*setPopupHorizontalSpace)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetPopupHorizontalSpace)(ArkUINodeHandle node);
    void (*setPopupSelectedColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetPopupSelectedColor)(ArkUINodeHandle node);
    void (*setItemSize)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetItemSize)(ArkUINodeHandle node);
    void (*setPopupPosition)(
        ArkUINodeHandle node, ArkUI_Float32 xValue, ArkUI_Int32 xUnit, ArkUI_Float32 yValue, ArkUI_Int32 yUnit);
    void (*resetPopupPosition)(ArkUINodeHandle node);
    void (*setPopupItemBorderRadius)(ArkUINodeHandle node, ArkUI_Float32 radiusValue, ArkUI_Int32 radiusUnit,
        ArkUI_Float32 popupValue, ArkUI_Int32 popupUnit);
    void (*resetPopupItemBorderRadius)(ArkUINodeHandle node);
    void (*setItemBorderRadius)(ArkUINodeHandle node, ArkUI_Float32 radiusValue, ArkUI_Int32 radiusUnit,
        ArkUI_Float32 indexerValue, ArkUI_Int32 indexerUnit);
    void (*resetItemBorderRadius)(ArkUINodeHandle node);
    void (*setPopupBackgroundBlurStyle)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetPopupBackgroundBlurStyle)(ArkUINodeHandle node);
    void (*setPopupTitleBackground)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetPopupTitleBackground)(ArkUINodeHandle node);
    void (*setAdaptiveWidth)(ArkUINodeHandle node);
    void (*resetAdaptiveWidth)(ArkUINodeHandle node);
    void (*setArrayValue)(ArkUINodeHandle node, ArkUI_CharPtr* value, ArkUI_Uint32 length);
    void (*resetArrayValue)(ArkUINodeHandle node);
};

struct ArkUILoadingProgressModifier {
    ArkUI_Uint32 (*getColor)(ArkUINodeHandle node);
    void (*setColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetColor)(ArkUINodeHandle node);
    ArkUI_Bool (*getEnableLoading)(ArkUINodeHandle node);
    void (*setEnableLoading)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*resetEnableLoading)(ArkUINodeHandle node);
    void (*setForegroundColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetForegroundColor)(ArkUINodeHandle node);
};

struct ArkUIImageAnimatorModifier {
    void (*setState)(ArkUINodeHandle node, ArkUI_Int32 state);
    void (*resetState)(ArkUINodeHandle node);
    void (*setDuration)(ArkUINodeHandle node, ArkUI_Int32 duration);
    void (*setFixedSize)(ArkUINodeHandle node, ArkUI_Uint32 fixedSize);
    void (*resetFixedSize)(ArkUINodeHandle node);
    void (*setFillMode)(ArkUINodeHandle node, ArkUI_Int32 fillMode);
    void (*resetFillMode)(ArkUINodeHandle node);
    void (*setReverse)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetReverse)(ArkUINodeHandle node);
    void (*setImages)(ArkUINodeHandle node, struct ArkUIImagePropertiesStruct* images, ArkUI_Int32 length);
    void (*resetImages)(ArkUINodeHandle node);
    void (*setImageAnimatorIteration)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetImageAnimatorIteration)(ArkUINodeHandle node);
};

struct ArkUISideBarContainerModifier {
    void (*setSideBarWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetSideBarWidth)(ArkUINodeHandle node);
    void (*setMinSideBarWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetMinSideBarWidth)(ArkUINodeHandle node);
    void (*setControlButton)(ArkUINodeHandle node, const ArkUI_Float32* values, ArkUI_Int32 valueLength,
        const struct ArkUIIconsStruct* sideBarWidth);
    void (*resetControlButton)(ArkUINodeHandle node);
    void (*setShowControlButton)(ArkUINodeHandle node, ArkUI_Bool isShow);
    void (*resetShowControlButton)(ArkUINodeHandle node);
    void (*setAutoHide)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetAutoHide)(ArkUINodeHandle node);
    void (*setSideBarContainerMaxSideBarWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetSideBarContainerMaxSideBarWidth)(ArkUINodeHandle node);
    void (*setSideBarContainerMinContentWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetSideBarContainerMinContentWidth)(ArkUINodeHandle node);
    void (*setSideBarPosition)(ArkUINodeHandle node, ArkUI_Int32 sideBarPosition);
    void (*resetSideBarPosition)(ArkUINodeHandle node);
    void (*setShowSideBar)(ArkUINodeHandle node, ArkUI_Bool isShow);
    void (*resetShowSideBar)(ArkUINodeHandle node);
    void (*setSideBarContainerDivider)(ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units,
        ArkUI_Int32 length, ArkUI_Uint32 color);
    void (*resetSideBarContainerDivider)(ArkUINodeHandle node);
};

struct ArkUICalendarPickerModifier {
    void (*setHintRadius)(ArkUINodeHandle node, ArkUI_Float32 radius, ArkUI_Int32 unit);
    void (*setSelectDate)(ArkUINodeHandle node, ArkUI_Uint32 year, ArkUI_Uint32 month, ArkUI_Uint32 day);
    void (*resetSelectDate)(ArkUINodeHandle node);
    void (*setTextStyleWithWeightEnum)(
        ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_Float32 fontSize, ArkUI_Int32 unit, ArkUI_Int32 fontWeight);
    void (*setTextStyle)(ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_CharPtr fontSize, ArkUI_CharPtr fontWeight);
    void (*resetTextStyle)(ArkUINodeHandle node);
    void (*setEdgeAlign)(ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 size,
        ArkUI_Int32 alignType);
    void (*resetEdgeAlign)(ArkUINodeHandle node);
    void (*setCalendarPickerPadding)(ArkUINodeHandle node, const struct ArkUISizeType* top,
        const struct ArkUISizeType* right, const struct ArkUISizeType* bottom, const struct ArkUISizeType* left);
    void (*resetCalendarPickerPadding)(ArkUINodeHandle node);
    void (*setCalendarPickerBorder)(ArkUINodeHandle node, const ArkUI_Uint32 color);
    void (*resetCalendarPickerBorder)(ArkUINodeHandle node);
    ArkUI_Float32 (*getHintRadius)(ArkUINodeHandle node);
    ArkUISelectedDateType (*getSelectedDate)(ArkUINodeHandle node);
    ArkUICalendarTextStyleType (*getCalendarPickerTextStyle)(ArkUINodeHandle node);
    ArkUIEdgeAlignType (*getEdgeAlign)(ArkUINodeHandle node);
};

struct ArkUIRatingModifier {
    void (*setStars)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*setRatingStepSize)(ArkUINodeHandle node, ArkUI_Float32 value);
    void (*setStarStyle)(
        ArkUINodeHandle node, ArkUI_CharPtr backgroundUri, ArkUI_CharPtr foregroundUri, ArkUI_CharPtr secondaryUri);
    void (*resetStars)(ArkUINodeHandle node);
    void (*resetRatingStepSize)(ArkUINodeHandle node);
    void (*resetStarStyle)(ArkUINodeHandle node);
};

struct ArkUIRowSplitModifier {
    void (*setRowSplitResizable)(ArkUINodeHandle node, ArkUI_Bool resizable);
    void (*resetRowSplitResizable)(ArkUINodeHandle node);
};

struct ArkUISearchModifier {
    void (*setSearchPlaceholderColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetSearchPlaceholderColor)(ArkUINodeHandle node);
    void (*setSearchTextFont)(ArkUINodeHandle node, const struct ArkUIFontStruct* value);
    void (*resetSearchTextFont)(ArkUINodeHandle node);
    void (*setSearchSelectionMenuHidden)(ArkUINodeHandle node, ArkUI_Uint32 selectionMenuHidden);
    void (*resetSearchSelectionMenuHidden)(ArkUINodeHandle node);
    void (*setSearchCaretStyle)(
        ArkUINodeHandle node, const ArkUI_Float32 number, ArkUI_Int32 unit, ArkUI_Uint32 caretColor);
    void (*resetSearchCaretStyle)(ArkUINodeHandle node);
    void (*setSearchTextAlign)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetSearchTextAlign)(ArkUINodeHandle node);
    void (*setSearchCancelButton)(ArkUINodeHandle node, ArkUI_Int32 style, const struct ArkUISizeType* size,
        ArkUI_Uint32 color, ArkUI_CharPtr src);
    void (*resetSearchCancelButton)(ArkUINodeHandle node);
    void (*setSearchEnableKeyboardOnFocus)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetSearchEnableKeyboardOnFocus)(ArkUINodeHandle node);
    void (*setSearchPlaceholderFont)(ArkUINodeHandle node, const struct ArkUIFontStruct* value);
    void (*resetSearchPlaceholderFont)(ArkUINodeHandle node);
    void (*setSearchSearchIcon)(ArkUINodeHandle node, const struct ArkUIIconOptionsStruct* value);
    void (*resetSearchSearchIcon)(ArkUINodeHandle node);
    void (*setSearchSearchButton)(ArkUINodeHandle node, const struct ArkUISearchButtonOptionsStruct* value);
    void (*resetSearchSearchButton)(ArkUINodeHandle node);
    void (*setSearchFontColor)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetSearchFontColor)(ArkUINodeHandle node);
    void (*setSearchCopyOption)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetSearchCopyOption)(ArkUINodeHandle node);
    void (*setSearchEnterKeyType)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetSearchEnterKeyType)(ArkUINodeHandle node);
    void (*setSearchHeight)(ArkUINodeHandle node, ArkUI_Float32 heightValue, ArkUI_Int32 heightUnit);
    void (*resetSearchHeight)(ArkUINodeHandle node);
    void (*setSearchInspectorId)(ArkUINodeHandle node, ArkUI_CharPtr key);
    void (*resetSearchInspectorId)(ArkUINodeHandle node);
    void (*setSearchDecoration)(ArkUINodeHandle node, ArkUI_Int32 decoration, ArkUI_Uint32 color, ArkUI_Int32 style);
    void (*resetSearchDecoration)(ArkUINodeHandle node);
    void (*setSearchLetterSpacing)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetSearchLetterSpacing)(ArkUINodeHandle node);
    void (*setSearchLineHeight)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetSearchLineHeight)(ArkUINodeHandle node);
    void (*setSearchFontFeature)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*resetSearchFontFeature)(ArkUINodeHandle node);
    void (*setSearchAdaptMinFontSize)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetSearchAdaptMinFontSize)(ArkUINodeHandle node);
    void (*setSearchAdaptMaxFontSize)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetSearchAdaptMaxFontSize)(ArkUINodeHandle node);
    void (*setSearchSelectedBackgroundColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetSearchSelectedBackgroundColor)(ArkUINodeHandle node);
    void (*setSearchTextIndent)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetSearchTextIndent)(ArkUINodeHandle node);
    void (*setSearchValue)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*resetSearchValue)(ArkUINodeHandle node);
    void (*setSearchPlaceholder)(ArkUINodeHandle node, ArkUI_CharPtr placeholder);
    void (*resetSearchPlaceholder)(ArkUINodeHandle node);
    void (*setSearchIcon)(ArkUINodeHandle node, ArkUI_CharPtr icon);
    void (*resetSearchIcon)(ArkUINodeHandle node);
};

struct ArkUISearchControllerModifier {
    ArkUINodeHandle (*getSearchController)(ArkUINodeHandle node);
    void (*setSearchCaretPosition)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*setSearchStopEditing)(ArkUINodeHandle node);
};

struct ArkUITextClockModifier {
    void (*setFormat)(ArkUINodeHandle node, ArkUI_CharPtr format);
    void (*resetFormat)(ArkUINodeHandle node);
    void (*setFontColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetFontColor)(ArkUINodeHandle node);
    void (*setFontSize)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetFontSize)(ArkUINodeHandle node);
    void (*setFontStyle)(ArkUINodeHandle node, ArkUI_Uint32 fontStyle);
    void (*resetFontStyle)(ArkUINodeHandle node);
    void (*setFontWeight)(ArkUINodeHandle node, ArkUI_CharPtr weight);
    void (*resetFontWeight)(ArkUINodeHandle node);
    void (*setFontFamily)(ArkUINodeHandle node, ArkUI_CharPtr fontFamily);
    void (*resetFontFamily)(ArkUINodeHandle node);
};

struct ArkUITextClockControllerModifier {
    ArkUINodeHandle (*getTextClockController)(ArkUINodeHandle node);
    void (*setTextClockStart)(ArkUINodeHandle node);
    void (*setTextClockStop)(ArkUINodeHandle node);
};

struct ArkUITextPickerModifier {
    void (*setTextPickerBackgroundColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*setTextPickerCanLoop)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*getTextPickerSelectedIndex)(ArkUINodeHandle node, ArkUI_Uint32* values, ArkUI_Int32 size);
    void (*setTextPickerSelectedIndex)(ArkUINodeHandle node, ArkUI_Uint32* values, ArkUI_Int32 size);
    ArkUI_CharPtr (*getTextPickerTextStyle)(ArkUINodeHandle node);
    void (*setTextPickerTextStyle)(
        ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_CharPtr fontInfo, ArkUI_Int32 styleVal);
    ArkUI_CharPtr (*getTextPickerSelectedTextStyle)(ArkUINodeHandle node);
    void (*setTextPickerSelectedTextStyle)(
        ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_CharPtr fontInfo, ArkUI_Int32 styleVal);
    ArkUI_CharPtr (*getTextPickerDisappearTextStyle)(ArkUINodeHandle node);
    void (*setTextPickerDisappearTextStyle)(
        ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_CharPtr fontInfo, ArkUI_Int32 styleVal);
    void (*setTextPickerDefaultPickerItemHeight)(ArkUINodeHandle node, ArkUI_Float32 dVal, ArkUI_Int32 dUnit);
    void (*resetTextPickerCanLoop)(ArkUINodeHandle node);
    void (*resetTextPickerSelectedIndex)(ArkUINodeHandle node);
    void (*resetTextPickerTextStyle)(ArkUINodeHandle node);
    void (*resetTextPickerSelectedTextStyle)(ArkUINodeHandle node);
    void (*resetTextPickerDisappearTextStyle)(ArkUINodeHandle node);
    void (*resetTextPickerDefaultPickerItemHeight)(ArkUINodeHandle node);
    void (*resetTextPickerBackgroundColor)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getTextPickerRangeStr)(ArkUINodeHandle node);
    ArkUI_Int32 (*getTextPickerSingleRange)(ArkUINodeHandle node);
    void (*setTextPickerRangeStr)(ArkUINodeHandle node, ArkUI_CharPtr rangeStr, ArkUI_Bool isSingleRange);
    ArkUI_CharPtr (*getTextPickerValue)(ArkUINodeHandle node);
    void (*setTextPickerValue)(ArkUINodeHandle node, ArkUI_CharPtr valueStr);
    void (*setTextPickerDivider)(ArkUINodeHandle node, ArkUI_Uint32 color, const ArkUI_Float32* values,
        const ArkUI_Int32* units, ArkUI_Int32 length);
    void (*resetTextPickerDivider)(ArkUINodeHandle node);
    void (*setTextPickerGradientHeight)(ArkUINodeHandle node, ArkUI_Float32 dVal, ArkUI_Int32 dUnit);
    void (*resetTextPickerGradientHeight)(ArkUINodeHandle node);
    ArkUI_Int32 (*getTextPickerSelectedSize)(ArkUINodeHandle node);
};

struct ArkUITextTimerModifier {
    void (*setFontColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetFontColor)(ArkUINodeHandle node);
    void (*setFontSize)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetFontSize)(ArkUINodeHandle node);
    void (*setFontStyle)(ArkUINodeHandle node, ArkUI_Uint32 fontStyle);
    void (*resetFontStyle)(ArkUINodeHandle node);
    void (*setFontWeight)(ArkUINodeHandle node, ArkUI_CharPtr weight);
    void (*resetFontWeight)(ArkUINodeHandle node);
    void (*setFontFamily)(ArkUINodeHandle node, ArkUI_CharPtr fontFamily);
    void (*resetFontFamily)(ArkUINodeHandle node);
    void (*setFormat)(ArkUINodeHandle node, ArkUI_CharPtr format);
    void (*resetFormat)(ArkUINodeHandle node);
};

struct ArkUISymbolGlyphModifier {
    void (*setFontColor)(ArkUINodeHandle node, ArkUI_Uint32* color, ArkUI_Int32 size);
    void (*resetFontColor)(ArkUINodeHandle node);
    void (*setFontSize)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetFontSize)(ArkUINodeHandle node);
    void (*setFontWeightStr)(ArkUINodeHandle node, ArkUI_CharPtr weight);
    void (*setFontWeight)(ArkUINodeHandle node, ArkUI_Int32 weight);
    void (*resetFontWeight)(ArkUINodeHandle node);
    void (*setRenderingStrategy)(ArkUINodeHandle node, ArkUI_Uint32 renderingStrategy);
    void (*resetRenderingStrategy)(ArkUINodeHandle node);
    void (*setEffectStrategy)(ArkUINodeHandle node, ArkUI_Uint32 effectStrategy);
    void (*resetEffectStrategy)(ArkUINodeHandle node);
    void (*setSymbolId)(ArkUINodeHandle node, ArkUI_Uint32 copyOption);
};

struct ArkUITextTimerControllerModifier {
    ArkUINodeHandle (*getTextTimerController)(ArkUINodeHandle node);
    void (*setTextTimerStart)(ArkUINodeHandle node);
    void (*setTextTimerPause)(ArkUINodeHandle node);
    void (*setTextTimerReset)(ArkUINodeHandle node);
};

struct ArkUIMarqueeModifier {
    void (*setMarqueeFontSize)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetMarqueeFontSize)(ArkUINodeHandle node);
    void (*setMarqueeFontColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetMarqueeFontColor)(ArkUINodeHandle node);
    void (*setMarqueeAllowScale)(ArkUINodeHandle node, ArkUI_Bool allowScale);
    void (*resetMarqueeAllowScale)(ArkUINodeHandle node);
    void (*setMarqueeFontWeight)(ArkUINodeHandle node, ArkUI_CharPtr fontWeight);
    void (*resetMarqueeFontWeight)(ArkUINodeHandle node);
    void (*setMarqueeFontFamily)(ArkUINodeHandle node, ArkUI_CharPtr fontFamily);
    void (*resetMarqueeFontFamily)(ArkUINodeHandle node);
    void (*setMarqueeUpdateStrategy)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetMarqueeUpdateStrategy)(ArkUINodeHandle node);
};

struct ArkUIDatePickerModifier {
    ArkUI_CharPtr (*getSelectedTextStyle)(ArkUINodeHandle node);
    void (*setSelectedTextStyle)(ArkUINodeHandle node, ArkUI_CharPtr fontInfo, ArkUI_Uint32 color, ArkUI_Int32 style);
    void (*resetSelectedTextStyle)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getDatePickerTextStyle)(ArkUINodeHandle node);
    void (*setDatePickerTextStyle)(ArkUINodeHandle node, ArkUI_CharPtr fontInfo, ArkUI_Uint32 color, ArkUI_Int32 style);
    void (*resetDatePickerTextStyle)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getDisappearTextStyle)(ArkUINodeHandle node);
    void (*setDisappearTextStyle)(ArkUINodeHandle node, ArkUI_CharPtr fontInfo, ArkUI_Uint32 color, ArkUI_Int32 style);
    void (*resetDisappearTextStyle)(ArkUINodeHandle node);
    ArkUI_Int32 (*getLunar)(ArkUINodeHandle node);
    void (*setLunar)(ArkUINodeHandle node, ArkUI_Bool isLunar);
    void (*resetLunar)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getStartDate)(ArkUINodeHandle node);
    void (*setStartDate)(ArkUINodeHandle node, ArkUI_Uint32 year, ArkUI_Uint32 month, ArkUI_Uint32 day);
    void (*resetStartDate)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getEndDate)(ArkUINodeHandle node);
    void (*setEndDate)(ArkUINodeHandle node, ArkUI_Uint32 year, ArkUI_Uint32 month, ArkUI_Uint32 day);
    void (*resetEndDate)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getSelectedDate)(ArkUINodeHandle node);
    void (*setSelectedDate)(ArkUINodeHandle node, ArkUI_Uint32 year, ArkUI_Uint32 month, ArkUI_Uint32 day);
    void (*resetSelectedDate)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getDatePickerBackgroundColor)(ArkUINodeHandle node);
    void (*setDatePickerBackgroundColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetDatePickerBackgroundColor)(ArkUINodeHandle node);
};

struct ArkUISpanModifier {
    void (*setSpanSrc)(ArkUINodeHandle node, ArkUI_CharPtr src);
    void (*setContent)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*setSpanTextCase)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetSpanTextCase)(ArkUINodeHandle node);
    void (*setSpanFontWeight)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*resetSpanFontWeight)(ArkUINodeHandle node);
    void (*setSpanLineHeight)(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit);
    void (*resetSpanLineHeight)(ArkUINodeHandle node);
    void (*setSpanFontStyle)(ArkUINodeHandle node, ArkUI_Int32 fontStyle);
    void (*resetSpanFontStyle)(ArkUINodeHandle node);
    void (*setSpanFontSize)(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit);
    void (*resetSpanFontSize)(ArkUINodeHandle node);
    void (*setSpanFontFamily)(ArkUINodeHandle node, ArkUI_CharPtr* fontFamilies, ArkUI_Uint32 length);
    void (*resetSpanFontFamily)(ArkUINodeHandle node);
    void (*setSpanDecoration)(
        ArkUINodeHandle node, ArkUI_Int32 decoration, ArkUI_Uint32 color, const ArkUI_Int32 style);
    void (*resetSpanDecoration)(ArkUINodeHandle node);
    void (*setSpanFontColor)(ArkUINodeHandle node, ArkUI_Uint32 textColor);
    void (*resetSpanFontColor)(ArkUINodeHandle node);
    void (*setSpanLetterSpacing)(ArkUINodeHandle node, const struct ArkUIStringAndFloat* letterSpacingValue);
    void (*resetSpanLetterSpacing)(ArkUINodeHandle node);
    void (*setSpanBaselineOffset)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetSpanBaselineOffset)(ArkUINodeHandle node);
    void (*setSpanFont)(ArkUINodeHandle node, const struct ArkUIFontStruct* fontInfo);
    void (*resetSpanFont)(ArkUINodeHandle node);
    void (*setSpanFontWeightStr)(ArkUINodeHandle node, ArkUI_CharPtr value);
    ArkUI_CharPtr (*getSpanContent)(ArkUINodeHandle node);
    void (*getSpanDecoration)(ArkUINodeHandle node, ArkUITextDecorationType* decorationType);
    ArkUI_Uint32 (*getSpanFontColor)(ArkUINodeHandle node);
    ArkUI_Float32 (*getSpanFontSize)(ArkUINodeHandle node, ArkUI_Int32 unit);
    ArkUI_Int32 (*getSpanFontStyle)(ArkUINodeHandle node);
    ArkUI_Int32 (*getSpanFontWeight)(ArkUINodeHandle node);
    ArkUI_Float32 (*getSpanLineHeight)(ArkUINodeHandle node);
    ArkUI_Int32 (*getSpanTextCase)(ArkUINodeHandle node);
    ArkUI_Float32 (*getSpanLetterSpacing)(ArkUINodeHandle node);
    ArkUI_Float32 (*getSpanBaselineOffset)(ArkUINodeHandle node);
    void (*setSpanTextBackgroundStyle)(ArkUINodeHandle node, ArkUI_Uint32 color, const ArkUI_Float32* values,
        const ArkUI_Int32* units, ArkUI_Int32 length);
    void (*resetSpanTextBackgroundStyle)(ArkUINodeHandle node);
    void (*getSpanTextBackgroundStyle)(ArkUINodeHandle node, ArkUITextBackgroundStyleOptions* options);
    void (*setTextShadow)(ArkUINodeHandle node, struct ArkUITextShadowStruct* shadows, ArkUI_Uint32 length);
    void (*resetTextShadow)(ArkUINodeHandle node);
    void (*getTextShadows)(ArkUINodeHandle node, ArkUITextShadowStruct* textShadow, ArkUI_Uint32 size);
};

struct ArkUISelectModifier {
    void (*setSpace)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*setValue)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*setSelected)(ArkUINodeHandle node, ArkUI_Int32 idx);
    void (*setSelectFontColor)(ArkUINodeHandle node, const ArkUI_Uint32 colorVal);
    void (*setSelectedOptionBgColor)(ArkUINodeHandle node, const ArkUI_Uint32 colorVal);
    void (*setOptionBgColor)(ArkUINodeHandle node, const ArkUI_Uint32 colorVal);
    void (*setOptionFontColor)(ArkUINodeHandle node, const ArkUI_Uint32 colorVal);
    void (*setSelectedOptionFontColor)(ArkUINodeHandle node, const ArkUI_Uint32 colorVal);
    void (*setArrowPosition)(ArkUINodeHandle node, ArkUI_Int32 arrowPosition);
    void (*setMenuAlign)(ArkUINodeHandle node, ArkUI_Int32 alignType, const ArkUI_Float32* values,
        const ArkUI_Int32* units, ArkUI_Int32 size);
    void (*setFont)(ArkUINodeHandle node, ArkUI_CharPtr fontInfo, ArkUI_Int32 style);
    void (*setOptionFont)(ArkUINodeHandle node, ArkUI_CharPtr fontInfo, ArkUI_Int32 style);
    void (*setSelectedOptionFont)(ArkUINodeHandle node, ArkUI_CharPtr fontInfo, ArkUI_Int32 style);
    void (*resetSpace)(ArkUINodeHandle node);
    void (*resetValue)(ArkUINodeHandle node);
    void (*resetSelected)(ArkUINodeHandle node);
    void (*resetSelectFontColor)(ArkUINodeHandle node);
    void (*resetSelectedOptionBgColor)(ArkUINodeHandle node);
    void (*resetOptionBgColor)(ArkUINodeHandle node);
    void (*resetOptionFontColor)(ArkUINodeHandle node);
    void (*resetSelectedOptionFontColor)(ArkUINodeHandle node);
    void (*resetArrowPosition)(ArkUINodeHandle node);
    void (*resetMenuAlign)(ArkUINodeHandle node);
    void (*resetFont)(ArkUINodeHandle node);
    void (*resetOptionFont)(ArkUINodeHandle node);
    void (*resetSelectedOptionFont)(ArkUINodeHandle node);

    void (*setSelectWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue);
    void (*resetSelectWidth)(ArkUINodeHandle node);
    void (*setSelectHeight)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue);
    void (*resetSelectHeight)(ArkUINodeHandle node);
    void (*setSelectSize)(
        ArkUINodeHandle node, const ArkUI_Float32* number, const ArkUI_Int32* unit, ArkUI_CharPtr* calc);
    void (*resetSelectSize)(ArkUINodeHandle node);
    void (*setOptionWidthFitTrigger)(ArkUINodeHandle node, ArkUI_Bool trigger);
    void (*setSelectOptionWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetSelectOptionWidth)(ArkUINodeHandle node);
    void (*setSelectOptionHeight)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetSelectOptionHeight)(ArkUINodeHandle node);
    void (*setControlSize)(ArkUINodeHandle node, ArkUI_Int32 controlSize);
    void (*resetControlSize)(ArkUINodeHandle node);
};

/** Common for all API variants.*/
struct ArkUIAny {
    ArkUI_Int32 version;
    void (*setCallbackMethod)(ArkUIAPICallbackMethod* method);
};

struct ArkUIGridColModifier {
    void (*setSpan)(ArkUINodeHandle node, ArkUI_Int32* containerSizeArray, ArkUI_Int32 size);
    void (*resetSpan)(ArkUINodeHandle node);
    void (*setGridColOffset)(ArkUINodeHandle node, ArkUI_Int32* containerSizeArray, ArkUI_Int32 size);
    void (*resetGridColOffset)(ArkUINodeHandle node);
    void (*setOrder)(ArkUINodeHandle node, ArkUI_Int32* containerSizeArray, ArkUI_Int32 size);
    void (*resetOrder)(ArkUINodeHandle node);
};

struct ArkUIGridRowModifier {
    void (*setAlignItems)(ArkUINodeHandle node, ArkUI_Int32 alignItems);
    void (*resetAlignItems)(ArkUINodeHandle node);
    void (*setDirection)(ArkUINodeHandle node, ArkUI_Int32 direction);
    void (*resetDirection)(ArkUINodeHandle node);
    void (*setBreakpoints)(ArkUINodeHandle node, ArkUI_Int32 reference, const ArkUI_Float32* pointValues,
        ArkUI_CharPtr pointStr[], ArkUI_Int32 size);
    void (*resetBreakpoints)(ArkUINodeHandle node);
    void (*setColumns)(ArkUINodeHandle node, ArkUI_Int32* containerSizeArray, ArkUI_Int32 size);
    void (*resetColumns)(ArkUINodeHandle node);
    void (*setGutter)(ArkUINodeHandle node, ArkUI_Int32* containerSizeArray, ArkUI_Int32 size);
    void (*resetGutter)(ArkUINodeHandle node);
};

struct ArkUIPanelModifier {
    void (*setPanelMode)(ArkUINodeHandle node, ArkUI_Int32 mode);
    void (*resetPanelMode)(ArkUINodeHandle node);
    void (*setPanelFullHeight)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetPanelFullHeight)(ArkUINodeHandle node);
    void (*setPanelHalfHeight)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetPanelHalfHeight)(ArkUINodeHandle node);
    void (*setPanelMiniHeight)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetPanelMiniHeight)(ArkUINodeHandle node);
    void (*setPanelBackgroundMask)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetPanelBackgroundMask)(ArkUINodeHandle node);
    void (*setPanelType)(ArkUINodeHandle node, ArkUI_Int32 type);
    void (*resetPanelType)(ArkUINodeHandle node);
    void (*setPanelCustomHeight)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*setPanelCustomHeightByString)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*resetPanelCustomHeight)(ArkUINodeHandle node);
    void (*setShowCloseIcon)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*resetShowCloseIcon)(ArkUINodeHandle node);
    void (*setDragBar)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*resetDragBar)(ArkUINodeHandle node);
    void (*setShow)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*resetShow)(ArkUINodeHandle node);
};

struct ArkUIRadioModifier {
    void (*setRadioChecked)(ArkUINodeHandle node, ArkUI_Bool isCheck);
    void (*resetRadioChecked)(ArkUINodeHandle node);
    void (*setRadioStyle)(ArkUINodeHandle node, ArkUI_Uint32 checkedBackgroundColor, ArkUI_Uint32 uncheckedBorderColor,
        ArkUI_Uint32 indicatorColor);
    void (*resetRadioStyle)(ArkUINodeHandle node);
    void (*setRadioWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue);
    void (*resetRadioWidth)(ArkUINodeHandle node);
    void (*setRadioHeight)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, ArkUI_CharPtr calcValue);
    void (*resetRadioHeight)(ArkUINodeHandle node);
    void (*setRadioSize)(ArkUINodeHandle node, ArkUI_Float32 widthValue, ArkUI_Int32 widthUnit,
        ArkUI_Float32 heightValue, ArkUI_Int32 heightUnit);
    void (*resetRadioSize)(ArkUINodeHandle node);
    void (*setRadioHoverEffect)(ArkUINodeHandle node, ArkUI_Int32 hoverEffectValue);
    void (*resetRadioHoverEffect)(ArkUINodeHandle node);
    void (*setRadioPadding)(ArkUINodeHandle node, const struct ArkUISizeType* top, const struct ArkUISizeType* right,
        const struct ArkUISizeType* bottom, const struct ArkUISizeType* left);
    void (*resetRadioPadding)(ArkUINodeHandle node);
    void (*setRadioResponseRegion)(
        ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Uint32 length);
    void (*resetRadioResponseRegion)(ArkUINodeHandle node);
    ArkUI_Int32 (*getRadioChecked)(ArkUINodeHandle node);
    void (*getRadioStyle)(ArkUINodeHandle node, ArkUIRadioStyleOption* options);
    void (*setRadioValue)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*resetRadioValue)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getRadioValue)(ArkUINodeHandle node);
    void (*setRadioGroup)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*resetRadioGroup)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getRadioGroup)(ArkUINodeHandle node);
};

struct ArkUIPatternLockControllerModifier {
    ArkUINodeHandle (*getPatternLockController)(ArkUINodeHandle node);
    void (*setPatternLockReset)(ArkUINodeHandle node);
};

struct ArkUIPatternLockModifier {
    void (*setPatternLockActiveColor)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetPatternLockActiveColor)(ArkUINodeHandle node);
    void (*setPatternLockCircleRadius)(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit);
    void (*resetPatternLockCircleRadius)(ArkUINodeHandle node);
    void (*setPatternLockSelectedColor)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetPatternLockSelectedColor)(ArkUINodeHandle node);
    void (*setPatternLockSideLength)(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit);
    void (*resetPatternLockSideLength)(ArkUINodeHandle node);
    void (*setPatternLockAutoReset)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetPatternLockAutoReset)(ArkUINodeHandle node);
    void (*setPatternLockPathStrokeWidth)(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit);
    void (*resetPatternLockPathStrokeWidth)(ArkUINodeHandle node);
    void (*setPatternLockRegularColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetPatternLockRegularColor)(ArkUINodeHandle node);
    void (*setPatternLockPathColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetPatternLockPathColor)(ArkUINodeHandle node);
};

struct ArkUIColumnSplitModifier {
    void (*setColumnSplitDivider)(
        ArkUINodeHandle node, ArkUI_Float32 stVal, ArkUI_Int32 stUnit, ArkUI_Float32 endVal, ArkUI_Int32 endUnit);
    void (*resetColumnSplitDivider)(ArkUINodeHandle node);
    void (*setColumnSplitResizable)(ArkUINodeHandle node, ArkUI_Bool resizable);
    void (*resetColumnSplitResizable)(ArkUINodeHandle node);
};

struct ArkUIRichEditorModifier {
    void (*setRichEditorEnableDataDetector)(ArkUINodeHandle node, ArkUI_Uint32 enableDataDetector);
    void (*resetRichEditorEnableDataDetector)(ArkUINodeHandle node);
    void (*setRichEditorCopyOptions)(ArkUINodeHandle node, ArkUI_Int32 copyOptionsValue);
    void (*resetRichEditorCopyOptions)(ArkUINodeHandle node);
    void (*setRichEditorCaretColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetRichEditorCaretColor)(ArkUINodeHandle node);
    void (*setRichEditorSelectedBackgroundColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetRichEditorSelectedBackgroundColor)(ArkUINodeHandle node);
};

struct ArkUIRichEditorControllerModifier {
    ArkUINodeHandle (*getRichEditorController)(ArkUINodeHandle node);
};

struct ArkUIDataPanelModifier {
    void (*setCloseEffect)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*resetCloseEffect)(ArkUINodeHandle node);
    void (*setDataPanelTrackBackgroundColor)(ArkUINodeHandle node, ArkUI_Uint32 value);
    void (*resetDataPanelTrackBackgroundColor)(ArkUINodeHandle node);
    void (*setDataPanelStrokeWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*resetDataPanelStrokeWidth)(ArkUINodeHandle node);
    void (*setValueColors)(ArkUINodeHandle node, const struct ArkUIGradientType* gradient);
    void (*resetValueColors)(ArkUINodeHandle node);
    void (*setTrackShadow)(ArkUINodeHandle node, const struct ArkUIGradientType* gradient, ArkUI_Float32 radius,
        ArkUI_Float32 offsetX, ArkUI_Float32 offsetY);
    void (*setNullTrackShadow)(ArkUINodeHandle node);
    void (*resetTrackShadow)(ArkUINodeHandle node);
};

struct ArkUIQRCodeModifier {
    void (*setQRColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetQRColor)(ArkUINodeHandle node);
    void (*setQRBackgroundColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetQRBackgroundColor)(ArkUINodeHandle node);
    void (*setContentOpacity)(ArkUINodeHandle node, ArkUI_Float32 opacity);
    void (*resetContentOpacity)(ArkUINodeHandle node);
};

struct ArkUIFormComponentModifier {
    void (*setFormVisibility)(ArkUINodeHandle node, ArkUI_Int32 visible);
    void (*allowUpdate)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*setDimension)(ArkUINodeHandle node, ArkUI_Int32 dimension);
    void (*setModuleName)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*setFormSize)(ArkUINodeHandle node, ArkUI_Float32 widthValue, ArkUI_Int32 widthUnit,
        ArkUI_Float32 heightValue, ArkUI_Int32 heightUnit);
    void (*resetFormVisibility)(ArkUINodeHandle node);
    void (*disallowUpdate)(ArkUINodeHandle node);
    void (*resetDimension)(ArkUINodeHandle node);
    void (*resetModuleName)(ArkUINodeHandle node);
    void (*resetFormSize)(ArkUINodeHandle node);
};

struct ArkUITextAreaControllerModifier {
    ArkUINodeHandle (*getTextAreaController)(ArkUINodeHandle node);
};

struct ArkUICanvasRenderingContext2DModifier {
    ArkUINodeHandle (*getCanvasRenderingContext2D)(ArkUINodeHandle node);
    void (*setCanvasBeginPath)(ArkUINodeHandle node);
    void (*setCanvasClosePath)(ArkUINodeHandle node);
    void (*setCanvasFill)(ArkUINodeHandle node, ArkUI_CharPtr value);
    void (*setCanvasMoveTo)(ArkUINodeHandle node, ArkUI_Float32 x, ArkUI_Float32 y);
    void (*setCanvasArc)(ArkUINodeHandle node, ArkUICanvasArcOptions* options);
    void (*setCanvasLineTo)(ArkUINodeHandle node, ArkUI_Float32 x, ArkUI_Float32 y);
    void (*setCanvasStrokeStyle)(ArkUINodeHandle node, ArkUI_Int32 color);
    ArkUI_Int32 (*getCanvasStrokeStyle)(ArkUINodeHandle node);
    void (*setCanvasLineWidth)(ArkUINodeHandle node, ArkUI_Float32 width);
    ArkUI_Float32 (*getCanvasLineWidth)(ArkUINodeHandle node);
    void (*setCanvasStroke)(ArkUINodeHandle node);
    void (*setCanvasAntiAlias)(ArkUINodeHandle node, ArkUI_Bool antialias);
    void (*setCanvasFillColor)(ArkUINodeHandle node, ArkUI_Int32 color);
    ArkUI_Int32 (*getCanvasFillColor)(ArkUINodeHandle node);
    void (*setCanvasGlobalAlpha)(ArkUINodeHandle node, ArkUI_Float32 value);
    ArkUI_Float32 (*getCanvasGlobalAlpha)(ArkUINodeHandle node);
    void (*setCanvasFillRect)(ArkUINodeHandle node, ArkUI_Float32 x, ArkUI_Float32 y, ArkUI_Float32 w, ArkUI_Float32 h);
    void (*setCanvasFillText)(
        ArkUINodeHandle node, ArkUI_CharPtr value, ArkUI_Float32 x, ArkUI_Float32 y, ArkUI_Float32 maxWidth);
};

struct ArkUIUtilsModifier {
    ArkUI_Float32 (*getDensity)(ArkUI_Int32 deviceId);
    ArkUI_Float32 (*getFontScale)(ArkUI_Int32 deviceId);
    ArkUI_Float32 (*getDesignWidthScale)(ArkUI_Int32 deviceId);
};

struct ArkUISideBarModifier {
    void (*setShowSideBar)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*setControlButton)(ArkUINodeHandle node, ArkUI_Float32* position, ArkUI_Int32 positionArrayLength,
        ArkUI_CharPtr* showIcon, ArkUI_Int32 showArrayLength, ArkUI_CharPtr* hiddenIcon, ArkUI_Int32 hiddenArrayLength,
        ArkUI_CharPtr* switchingIcon, ArkUI_Int32 switchingArrayLength);
    void (*setShowControlButton)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*setSideBarWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*setMinSideBarWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*setMaxSideBarWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
    void (*setAutoHide)(ArkUINodeHandle node, ArkUI_Bool value);
    void (*setSideBarPosition)(ArkUINodeHandle node, ArkUI_Int32 unit);
    void (*setSideBarDivider)(ArkUINodeHandle node, ArkUI_Float32* strokeWidth, ArkUI_Int32 color,
        ArkUI_Float32* startMargin, ArkUI_Float32* endMargin);
    void (*setMinContentWidth)(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit);
};

struct ArkUIXComponentModifier {
    // loadXComponent() returns VM-specific handle produced by
    // ArkNativeEngine::LoadModuleByName(). vmKind parameters allows to
    // differentiate which VM shall be used to load. Embedder code must use kind
    // matching VM we're embedding into. errorCallbackId is invoked if operation
    // cannot be completed.
    ArkUIVMObject (*loadXComponent)(ArkUIVMContext vmContext, ArkUINodeHandle node, ArkUIVMKind vmKind,
        ArkUI_CharPtr libraryName, ArkUI_Int32 errorCallbackId);
    void (*setXComponentOptions)(ArkUINodeHandle node, ArkUI_CharPtr id, ArkUI_CharPtr type, ArkUI_CharPtr libraryName);
    ArkUI_CharPtr (*getXComponentSurfaceId)(ArkUIXComponentControllerHandle controller);
    ArkUIXComponentControllerHandle (*getXComponentController)(ArkUINodeHandle node);

    void (*setXComponentBackgroundColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*resetXComponentBackgroundColor)(ArkUINodeHandle node);
    void (*setXComponentOpacity)(ArkUINodeHandle node, ArkUI_Float32 opacity);
    void (*resetXComponentOpacity)(ArkUINodeHandle node);
    void (*setXComponentId)(ArkUINodeHandle node, ArkUI_CharPtr id);
    void (*setXComponentType)(ArkUINodeHandle node, ArkUI_Uint32 type);
    void (*setXComponentSurfaceSize)(ArkUINodeHandle node, ArkUI_Uint32 width, ArkUI_Uint32 height);
    ArkUI_CharPtr (*getXComponentId)(ArkUINodeHandle node);
    ArkUI_Int32 (*getXComponentType)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getXComponentSurfaceWidth)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getXComponentSurfaceHeight)(ArkUINodeHandle node);
    void* (*getNativeXComponent)(ArkUINodeHandle node);
};

struct ArkUIStateModifier {
    ArkUI_Int64 (*getUIState)(ArkUINodeHandle node);
    void (*setSupportedUIState)(ArkUINodeHandle node, ArkUI_Int64 state);
};

struct ArkUIRenderNodeModifier {
    void (*appendChild)(ArkUINodeHandle node, ArkUINodeHandle child);
    void (*insertChildAfter)(ArkUINodeHandle node, ArkUINodeHandle child, ArkUINodeHandle sibling);
    void (*removeChild)(ArkUINodeHandle node, ArkUINodeHandle child);
    void (*clearChildren)(ArkUINodeHandle node);
    void (*setClipToFrame)(ArkUINodeHandle node, ArkUI_Bool useClip);
    void (*setRotation)(
        ArkUINodeHandle node, ArkUI_Float32 rotationX, ArkUI_Float32 rotationY, ArkUI_Float32 rotationZ);
    void (*setShadowColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*setShadowOffset)(ArkUINodeHandle node, ArkUI_Float32 offsetX, ArkUI_Float32 offsetY);
    void (*setShadowAlpha)(ArkUINodeHandle node, ArkUI_Float32 alpha);
    void (*setShadowElevation)(ArkUINodeHandle node, ArkUI_Float32 elevation);
    void (*setShadowRadius)(ArkUINodeHandle node, ArkUI_Float32 radius);
    void (*invalidate)(ArkUINodeHandle node);
    void (*setScale)(ArkUINodeHandle node, ArkUI_Float32 scaleX, ArkUI_Float32 scaleY);
    void (*setRenderNodeBackgroundColor)(ArkUINodeHandle node, ArkUI_Uint32 colorValue);
    void (*setPivot)(ArkUINodeHandle node, ArkUI_Float32 pivotX, ArkUI_Float32 pivotY);
    void (*setFrame)(ArkUINodeHandle node, ArkUI_Float32 positionX, ArkUI_Float32 positionY, ArkUI_Float32 width,
        ArkUI_Float32 height);
    void (*setSize)(ArkUINodeHandle node, ArkUI_Float32 width, ArkUI_Float32 height);
    void (*setOpacity)(ArkUINodeHandle node, ArkUI_Float32 opacity);
    void (*setTranslate)(
        ArkUINodeHandle node, ArkUI_Float32 translateX, ArkUI_Float32 translateY, ArkUI_Float32 translateZ);
    void (*setBorderStyle)(
        ArkUINodeHandle node, ArkUI_Int32 left, ArkUI_Int32 top, ArkUI_Int32 right, ArkUI_Int32 bottom);
    void (*setBorderWidth)(
        ArkUINodeHandle node, ArkUI_Float32 left, ArkUI_Float32 top, ArkUI_Float32 right, ArkUI_Float32 bottom);
    void (*setBorderColor)(
        ArkUINodeHandle node, ArkUI_Uint32 left, ArkUI_Uint32 top, ArkUI_Uint32 right, ArkUI_Uint32 bottom);
    void (*setBorderRadius)(ArkUINodeHandle node, ArkUI_Float32 topLeft, ArkUI_Float32 topRight,
        ArkUI_Float32 bottomLeft, ArkUI_Float32 bottomRight);
    void (*setRectMask)(ArkUINodeHandle node, ArkUI_Float32 rectX, ArkUI_Float32 rectY, ArkUI_Float32 rectW,
        ArkUI_Float32 rectH, ArkUI_Uint32 fillColor, ArkUI_Uint32 strokeColor, ArkUI_Float32 strokeWidth);
    void (*setCircleMask)(ArkUINodeHandle node, ArkUI_Float32 centerXValue, ArkUI_Float32 centerYValue,
        ArkUI_Float32 radiusValue, ArkUI_Uint32 fillColor, ArkUI_Uint32 strokeColor, ArkUI_Float32 strokeWidth);
    void (*setRoundRectMask)(ArkUINodeHandle node, const ArkUI_Float32* roundRect, const ArkUI_Uint32 roundRectSize,
        ArkUI_Uint32 fillColor, ArkUI_Uint32 strokeColor, ArkUI_Float32 strokeWidth);
    void (*setOvalMask)(ArkUINodeHandle node, ArkUI_Float32 rectX, ArkUI_Float32 rectY, ArkUI_Float32 rectW,
        ArkUI_Float32 rectH, ArkUI_Uint32 fillColor, ArkUI_Uint32 strokeColor, ArkUI_Float32 strokeWidth);
    void (*setCommandPathMask)(ArkUINodeHandle node, ArkUI_CharPtr commands, ArkUI_Uint32 fillColor,
        ArkUI_Uint32 strokeColor, ArkUI_Float32 strokeWidth);
};

struct ArkUIFrameNodeModifier {
    ArkUI_Bool (*isModifiable)(ArkUINodeHandle node);
    ArkUINodeHandle (*createFrameNode)();
    void (*invalidate)(ArkUINodeHandle node);
    ArkUI_Bool (*appendChild)(ArkUINodeHandle node, ArkUINodeHandle child);
    ArkUI_Bool (*insertChildAfter)(ArkUINodeHandle node, ArkUINodeHandle child, ArkUINodeHandle sibling);
    void (*removeChild)(ArkUINodeHandle node, ArkUINodeHandle child);
    void (*clearChildren)(ArkUINodeHandle node);
    ArkUI_Uint32 (*getChildrenCount)(ArkUINodeHandle node);
    ArkUINodeHandle (*getChild)(ArkUINodeHandle node, ArkUI_Int32 index);
    ArkUINodeHandle (*getFirst)(ArkUINodeHandle node);
    ArkUINodeHandle (*getNextSibling)(ArkUINodeHandle node);
    ArkUINodeHandle (*getPreviousSibling)(ArkUINodeHandle node);
    ArkUINodeHandle (*getParent)(ArkUINodeHandle node);
    ArkUI_Int32 (*getIdByNodePtr)(ArkUINodeHandle node);
    void (*getPositionToParent)(ArkUINodeHandle node, ArkUI_Float32* parentOffset);
    void (*getPositionToScreen)(ArkUINodeHandle node, ArkUI_Float32* screenPosition);
    void (*getPositionToWindow)(ArkUINodeHandle node, ArkUI_Float32* windowOffset);
    void (*getPositionToParentWithTransform)(ArkUINodeHandle node, ArkUI_Float32* parentPosition);
    void (*getPositionToScreenWithTransform)(ArkUINodeHandle node, ArkUI_Float32* screenPosition);
    void (*getPositionToWindowWithTransform)(ArkUINodeHandle node, ArkUI_Float32* windowPosition);
    ArkUI_Float32* (*getMeasuredSize)(ArkUINodeHandle node);
    ArkUI_Float32* (*getLayoutPosition)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getInspectorId)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getNodeType)(ArkUINodeHandle node);
    ArkUI_Bool (*isVisible)(ArkUINodeHandle node);
    ArkUI_Bool (*isAttached)(ArkUINodeHandle node);
    ArkUI_CharPtr (*getInspectorInfo)(ArkUINodeHandle node);
    ArkUINodeHandle (*getFrameNodeById)(ArkUI_Int32 nodeId);
    ArkUINodeHandle (*getFrameNodeByUniqueId)(ArkUI_Int32 uniqueId);
    ArkUINodeHandle (*getFrameNodeByKey)(ArkUI_CharPtr key);
    void (*propertyUpdate)(ArkUINodeHandle node);
    ArkUINodeHandle (*getLast)(ArkUINodeHandle node);
};

struct ArkUINodeContentEvent {
    ArkUI_Int32 type;
    void* userData;
};

struct ArkUINodeContentModifier {
    ArkUI_Int32 (*addChild)(ArkUINodeContentHandle content, ArkUINodeHandle child);
    ArkUI_Int32 (*insertChild)(ArkUINodeContentHandle content, ArkUINodeHandle child, ArkUI_Int32 position);
    ArkUI_Int32 (*removeChild)(ArkUINodeContentHandle content, ArkUINodeHandle child);
    ArkUI_Int32 (*registerEvent)(
        ArkUINodeContentHandle content, void* userData, void (*receiver)(ArkUINodeContentEvent* event));
};

struct ArkUIAnimation {
    ArkUI_Int32 (*startAnimation)(const ArkUIAPIAnimationSpec* spec, ArkUI_Int32 callbackId);
    void (*openImplicitAnimation)(
        ArkUIVMContext vmContext, ArkUI_Int32 curve, ArkUI_Float32* options, ArkUI_Int32 callbackId);
    void (*closeImplicitAnimation)();
    void (*animateTo)(ArkUIContext* context, ArkUIAnimateOption option, void* event, void* userData);
};

struct ArkUINavigation {
    void (*popPageToIndex)(ArkUI_Int32 index);
    void (*setNavDestinationBackPressed)(ArkUIVMContext vmContext, ArkUINodeHandle node, ArkUI_Int32 indexerId);
};

struct ArkUIGraphicsCanvas {
    void (*finalize)(ArkUICanvasHandle canvas);

    void (*drawPoint)(ArkUICanvasHandle canvas, ArkUI_Float32 x, ArkUI_Float32 y, ArkUIPaintHandle paint);
    void (*drawPoints)(
        ArkUICanvasHandle canvas, ArkUI_Int32 mode, ArkUI_Float32* coords, ArkUI_Int32 count, ArkUIPaintHandle paint);
    void (*drawLine)(ArkUICanvasHandle canvas, ArkUI_Float32 x0, ArkUI_Float32 y0, ArkUI_Float32 x1, ArkUI_Float32 y1,
        ArkUIPaintHandle paint);
    void (*drawArc)(ArkUICanvasHandle canvas, ArkUI_Float32 left, ArkUI_Float32 top, ArkUI_Float32 right,
        ArkUI_Float32 bottom, ArkUI_Float32 startAngle, ArkUI_Float32 sweepAngle, ArkUI_Bool includeCenter,
        ArkUIPaintHandle paint);
    void (*drawRect)(ArkUICanvasHandle canvas, ArkUI_Float32 left, ArkUI_Float32 top, ArkUI_Float32 right,
        ArkUI_Float32 bottom, ArkUIPaintHandle paint);
    void (*drawOval)(ArkUICanvasHandle canvas, ArkUI_Float32 left, ArkUI_Float32 top, ArkUI_Float32 right,
        ArkUI_Float32 bottom, ArkUIPaintHandle paint);
    void (*drawCircle)(
        ArkUICanvasHandle canvas, ArkUI_Float32 x, ArkUI_Float32 y, ArkUI_Float32 radius, ArkUIPaintHandle paintPtr);
    void (*drawRRect)(ArkUICanvasHandle canvas, ArkUI_Float32 left, ArkUI_Float32 top, ArkUI_Float32 right,
        ArkUI_Float32 bottom, ArkUI_Float32* jradii, ArkUI_Int32 jradiiSize, ArkUIPaintHandle paintPtr);
    void (*drawDRRect)(ArkUICanvasHandle canvas, ArkUI_Float32 ol, ArkUI_Float32 ot, ArkUI_Float32 oright,
        ArkUI_Float32 ob, ArkUI_Float32* ojradii, ArkUI_Int32 ojradiiSize, ArkUI_Float32 il, ArkUI_Float32 it,
        ArkUI_Float32 ir, ArkUI_Float32 ib, ArkUI_Float32* ijradii, ArkUI_Int32 ijradiiSize, ArkUIPaintHandle paint);
    void (*drawString)(ArkUICanvasHandle canvas, ArkUI_CharPtr string, ArkUI_Float32 x, ArkUI_Float32 y,
        ArkUIFontHandle font, ArkUIPaintHandle paint);
};

struct ArkUIGraphicsPaint {
    ArkUIPaintHandle (*make)();
    void (*finalize)(ArkUIPaintHandle handle);

    void (*setColor)(ArkUIPaintHandle paint, ArkUI_Int32 color);
    ArkUI_Int32 (*getColor)(ArkUIPaintHandle paint);
    void (*setAlpha)(ArkUIPaintHandle paint, ArkUI_Float32 alpha);
    ArkUI_Float32 (*getAlpha)(ArkUIPaintHandle paint);
};

struct ArkUIGraphicsFont {
    ArkUIFontHandle (*makeDefault)();
    void (*finalize)(ArkUIPaintHandle handle);
};

struct ArkUIGraphicsAPI {
    ArkUI_Int32 version;
    void (*setCallbackMethod)(ArkUIAPICallbackMethod* method);

    /**
     * Graphics.
     */
    const ArkUIGraphicsCanvas* (*getCanvasAPI)();
    const ArkUIGraphicsPaint* (*getPaintAPI)();
    const ArkUIGraphicsFont* (*getFontAPI)();
};

struct ArkUIRelativeContainerModifier {
    void (*setGuideLine)(ArkUINodeHandle node, ArkUIGuidelineStyle* values, ArkUI_Int32 size);
    void (*setBarrier)(ArkUINodeHandle node, ArkUIBarrierStyle* values, ArkUI_Int32 size);
    void (*getGuideLine)(ArkUINodeHandle node, ArkUIGuidelineStyle* values, ArkUI_Int32* size);
    void (*getBarrier)(ArkUINodeHandle node, ArkUIBarrierStyle* values, ArkUI_Int32* size);
    void (*resetGuideline)(ArkUINodeHandle node);
    void (*resetBarrier)(ArkUINodeHandle node);
};
/**
 * An API to control an implementation. When making changes modifying binary
 * layout, i.e. adding new events - increase ARKUI_API_VERSION above for binary
 * layout checks.
 */
struct ArkUINodeModifiers {
    ArkUI_Int32 version;
    const ArkUICommonModifier* (*getCommonModifier)();
    const ArkUICheckboxGroupModifier* (*getCheckboxGroupModifier)();
    const ArkUICounterModifier* (*getCounterModifier)();
    const ArkUIRowModifier* (*getRowModifier)();
    const ArkUIRowSplitModifier* (*getRowSplitModifier)();
    const ArkUITextModifier* (*getTextModifier)();
    const ArkUIButtonModifier* (*getButtonModifier)();
    const ArkUIToggleModifier* (*getToggleModifier)();
    const ArkUIImageSpanModifier* (*getImageSpanModifier)();
    const ArkUIBlankModifier* (*getBlankModifier)();
    const ArkUISearchModifier* (*getSearchModifier)();
    const ArkUISelectModifier* (*getSelectModifier)();
    const ArkUIRadioModifier* (*getRadioModifier)();
    const ArkUICheckboxModifier* (*getCheckboxModifier)();
    const ArkUITimepickerModifier* (*getTimepickerModifier)();
    const ArkUITextPickerModifier* (*getTextPickerModifier)();
    const ArkUIRatingModifier* (*getRatingModifier)();
    const ArkUISliderModifier* (*getSliderModifier)();
    const ArkUIDividerModifier* (*getDividerModifier)();
    const ArkUIStackModifier* (*getStackModifier)();
    const ArkUINavDestinationModifier* (*getNavDestinationModifier)();
    const ArkUIGridModifier* (*getGridModifier)();
    const ArkUIGridColModifier* (*getGridColModifier)();
    const ArkUIGridRowModifier* (*getGridRowModifier)();
    const ArkUIPanelModifier* (*getPanelModifier)();
    const ArkUITextAreaModifier* (*getTextAreaModifier)();
    const ArkUINavigationModifier* (*getNavigationModifier)();
    const ArkUIColumnModifier* (*getColumnModifier)();
    const ArkUIRichEditorModifier* (*getRichEditorModifier)();
    const ArkUIImageModifier* (*getImageModifier)();
    const ArkUIVideoModifier* (*getVideoModifier)();
    const ArkUIVideoControllerModifier* (*getVideoControllerModifier)();
    const ArkUINavigatorModifier* (*getNavigatorModifier)();
    const ArkUINavRouterModifier* (*getNavRouterModifier)();
    const ArkUINodeContainerModifier* (*getNodeContainerModifier)();
    const ArkUIPatternLockModifier* (*getPatternLockModifier)();
    const ArkUIColumnSplitModifier* (*getColumnSplitModifier)();
    const ArkUILineModifier* (*getLineModifier)();
    const ArkUIPathModifier* (*getPathModifier)();
    const ArkUIPolygonModifier* (*getPolygonModifier)();
    const ArkUIPolylineModifier* (*getPolylineModifier)();
    const ArkUISpanModifier* (*getSpanModifier)();
    const ArkUIImageAnimatorModifier* (*getImageAnimatorModifier)();
    const ArkUISideBarContainerModifier* (*getSideBarContainerModifier)();
    const ArkUICalendarPickerModifier* (*getCalendarPickerModifier)();
    const ArkUITextInputModifier* (*getTextInputModifier)();
    const ArkUITabsModifier* (*getTabsModifier)();
    const ArkUIStepperItemModifier* (*getStepperItemModifier)();
    const ArkUIHyperlinkModifier* (*getHyperlinkModifier)();
    const ArkUIMarqueeModifier* (*getMarqueeModifier)();
    const ArkUIMenuItemModifier* (*getMenuItemModifier)();
    const ArkUIMenuModifier* (*getMenuModifier)();
    const ArkUIDatePickerModifier* (*getDatePickerModifier)();
    const ArkUIWaterFlowModifier* (*getWaterFlowModifier)();
    const ArkUIAlphabetIndexerModifier* (*getAlphabetIndexerModifier)();
    const ArkUIDataPanelModifier* (*getDataPanelModifier)();
    const ArkUIGaugeModifier* (*getGaugeModifier)();
    const ArkUIScrollModifier* (*getScrollModifier)();
    const ArkUIGridItemModifier* (*getGridItemModifier)();
    const ArkUIProgressModifier* (*getProgressModifier)();
    const ArkUICommonShapeModifier* (*getCommonShapeModifier)();
    const ArkUIShapeModifier* (*getShapeModifier)();
    const ArkUIRectModifier* (*getRectModifier)();
    const ArkUISwiperModifier* (*getSwiperModifier)();
    const ArkUIListItemModifier* (*getListItemModifier)();
    const ArkUIListModifier* (*getListModifier)();
    const ArkUIListItemGroupModifier* (*getListItemGroupModifier)();
    const ArkUIQRCodeModifier* (*getQRCodeModifier)();
    const ArkUILoadingProgressModifier* (*getLoadingProgressModifier)();
    const ArkUITextClockModifier* (*getTextClockModifier)();
    const ArkUITextTimerModifier* (*getTextTimerModifier)();
    const ArkUIRenderNodeModifier* (*getRenderNodeModifier)();
    const ArkUIFrameNodeModifier* (*getFrameNodeModifier)();
    const ArkUIPluginModifier* (*getPluginModifier)();
    const ArkUIXComponentModifier* (*getXComponentModifier)();
    const ArkUIStateModifier* (*getUIStateModifier)();
    const ArkUIFormComponentModifier* (*getFormComponentModifier)();
    const ArkUIFlexModifier* (*getFlexModifier)();
    const ArkUIScrollBarModifier* (*getScrollBarModifier)();
    const ArkUIScrollerModifier* (*getScrollerModifier)();
    const ArkUITabContentModifier* (*getTabContentModifier)();
    const ArkUITabsControllerModifier* (*getTabsControllerModifier)();
    const ArkUISwiperControllerModifier* (*getSwiperControllerModifier)();
    const ArkUIGestureModifier* (*getGestureModifier)();
    const ArkUIBadgeModifier* (*getBadgeModifier)();
    const ArkUIWebModifier* (*getWebModifier)();
    const ArkUIRefreshModifier* (*getRefreshModifier)();
    const ArkUIMenuItemGroupModifier* (*getMenuItemGroupModifier)();
    const ArkUISearchControllerModifier* (*getSearchControllerModifier)();
    const ArkUISideBarModifier* (*getSideBarModifier)();
    const ArkUIPatternLockControllerModifier* (*getPatternLockControllerModifier)();
    const ArkUITextTimerControllerModifier* (*getTextTimerControllerModifier)();
    const ArkUITextClockControllerModifier* (*getTextClockControllerModifier)();
    const ArkUIRichEditorControllerModifier* (*getRichEditorControllerModifier)();
    const ArkUITextAreaControllerModifier* (*getTextAreaControllerModifier)();
    const ArkUIRelativeContainerModifier* (*getRelativeContainerModifier)();
    const ArkUIParticleModifier* (*getParticleModifier)();
    const ArkUINodeContentModifier* (*getNodeContentModifier)();
    const ArkUISymbolGlyphModifier* (*getSymbolGlyphModifier)();
};

// same as inner defines in property.h
typedef enum {
    ARKUI_DIRTY_FLAG_MEASURE = 0b1,
    ARKUI_DIRTY_FLAG_LAYOUT = 0b10,
    /** mark the node need to do attribute diff to drive update. */
    ARKUI_DIRTY_FLAG_ATTRIBUTE_DIFF = 0b100,
    ARKUI_DIRTY_FLAG_MEASURE_SELF = 0b1000,
    ARKUI_DIRTY_FLAG_MEASURE_SELF_AND_PARENT = 0b10000,
    ARKUI_DIRTY_FLAG_MEASURE_BY_CHILD_REQUEST = 0b100000,
    ARKUI_DIRTY_FLAG_RENDER = 0b1000000,
    ARKUI_DIRTY_FLAG_MEASURE_SELF_AND_CHILD = 0b1000000000,
} ArkUIDirtyFlag;

typedef void (*EventReceiver)(ArkUINodeEvent* event);

struct ArkUIBasicAPI {
    /// Tree operations.
    ArkUINodeHandle (*createNode)(ArkUINodeType type, ArkUI_Int32 id, ArkUI_Int32 flags);
    ArkUINodeHandle (*getNodeByViewStack)();
    void (*disposeNode)(ArkUINodeHandle node);
    // Returned pointer is valid only till node is alive.
    ArkUI_CharPtr (*getName)(ArkUINodeHandle node);
    void (*dump)(ArkUINodeHandle node);

    ArkUI_Int32 (*addChild)(ArkUINodeHandle parent, ArkUINodeHandle child);
    void (*removeChild)(ArkUINodeHandle parent, ArkUINodeHandle child);
    ArkUI_Int32 (*insertChildAfter)(ArkUINodeHandle parent, ArkUINodeHandle child, ArkUINodeHandle sibling);
    ArkUI_Int32 (*insertChildBefore)(ArkUINodeHandle parent, ArkUINodeHandle child, ArkUINodeHandle sibling);
    ArkUI_Int32 (*insertChildAt)(ArkUINodeHandle parent, ArkUINodeHandle child, ArkUI_Int32 position);

    // Returned pointer is valid only till node is alive.
    ArkUI_CharPtr (*getAttribute)(ArkUINodeHandle node, ArkUI_CharPtr attribute);
    void (*setAttribute)(ArkUINodeHandle node, ArkUI_CharPtr attribute, ArkUI_CharPtr value);
    void (*resetAttribute)(ArkUINodeHandle node, ArkUI_CharPtr attribute);

    /**
     * notify the node to send node event back
     */
    void (*registerNodeAsyncEvent)(ArkUINodeHandle nodePtr, ArkUIEventSubKind kind, ArkUI_Int64 extraParam);
    void (*unRegisterNodeAsyncEvent)(ArkUINodeHandle nodePtr, ArkUIEventSubKind kind);
    /* registerNodeAsyncEventReceiver() must be redesigned */
    void (*registerNodeAsyncEventReceiver)(EventReceiver eventReceiver);
    void (*unRegisterNodeAsyncEventReceiver)();
    ArkUI_Int32 (*checkAsyncEvent)(ArkUINodeEvent* event);

    // Commit attributes updates for node.
    void (*applyModifierFinish)(ArkUINodeHandle nodePtr);
    // the flag can combine different flag like ARKUI_DIRTY_FLAG_MEASURE | ARKUI_DIRTY_FLAG_RENDER
    void (*markDirty)(ArkUINodeHandle nodePtr, ArkUI_Uint32 dirtyFlag);
    ArkUI_Bool (*isBuilderNode)(ArkUINodeHandle node);

    ArkUI_Float64 (*convertLengthMetricsUnit)(ArkUI_Float64 value, ArkUI_Int32 originUnit, ArkUI_Int32 targetUnit);
};

struct ArkUIDialogAPI {
    ArkUIDialogHandle (*create)();
    void (*dispose)(ArkUIDialogHandle handle);
    ArkUI_Int32 (*setContent)(ArkUIDialogHandle handle, ArkUINodeHandle contentNode);
    ArkUI_Int32 (*removeContent)(ArkUIDialogHandle handle);
    ArkUI_Int32 (*setContentAlignment)(
        ArkUIDialogHandle handle, ArkUI_Int32 alignment, ArkUI_Float32 offsetX, ArkUI_Float32 offsetY);
    ArkUI_Int32 (*resetContentAlignment)(ArkUIDialogHandle handle);
    ArkUI_Int32 (*setModalMode)(ArkUIDialogHandle handle, ArkUI_Bool isModal);
    ArkUI_Int32 (*setAutoCancel)(ArkUIDialogHandle handle, ArkUI_Bool autoCancel);
    ArkUI_Int32 (*setMask)(ArkUIDialogHandle handle, ArkUI_Uint32 maskColor, ArkUIRect* rect);
    ArkUI_Int32 (*setBackgroundColor)(ArkUIDialogHandle handle, ArkUI_Uint32 backgroundColor);
    ArkUI_Int32 (*setCornerRadius)(ArkUIDialogHandle handle, ArkUI_Float32 topLeft, ArkUI_Float32 topRight,
        ArkUI_Float32 bottomLeft, ArkUI_Float32 bottomRight);
    ArkUI_Int32 (*setGridColumnCount)(ArkUIDialogHandle handle, ArkUI_Int32 gridCount);
    ArkUI_Int32 (*enableCustomStyle)(ArkUIDialogHandle handle, ArkUI_Bool enableCustomStyle);
    ArkUI_Int32 (*enableCustomAnimation)(ArkUIDialogHandle handle, ArkUI_Bool enableCustomAnimation);
    // show dialog
    ArkUI_Int32 (*show)(ArkUIDialogHandle handle, ArkUI_Bool showInSubWindow);
    ArkUI_Int32 (*close)(ArkUIDialogHandle handle);
    ArkUI_Int32 (*registerOnWillDismiss)(ArkUIDialogHandle handle, bool (*eventHandler)(ArkUI_Int32));
};

struct ArkUIBasicNodeAPI {
    ArkUI_Int32 version;
    void (*setCallbackMethod)(ArkUIAPICallbackMethod* method);
    const ArkUIBasicAPI* (*getBasicModifier)();
};

struct ArkUIExtendedNodeAPI {
    ArkUI_Int32 version;

    const ArkUIUtilsModifier* (*getUtilsModifier)();
    const ArkUICanvasRenderingContext2DModifier* (*getCanvasRenderingContext2DModifier)();

    void (*setCallbackMethod)(ArkUIAPICallbackMethod* method);

    // for ndk side, the custom method is not set in create.
    void (*setCustomMethodFlag)(ArkUINodeHandle node, ArkUI_Int32 flag);
    ArkUI_Int32 (*getCustomMethodFlag)(ArkUINodeHandle node);

    void (*registerCustomNodeAsyncEvent)(ArkUINodeHandle nodePtr, ArkUI_Int32 kind, void* extraParam);
    ArkUI_Int32 (*unregisterCustomNodeAsyncEvent)(ArkUINodeHandle nodePtr, ArkUI_Int32 kind);
    void (*registerCustomNodeAsyncEventReceiver)(void (*eventReceiver)(ArkUICustomNodeEvent* event));

    void (*setCustomCallback)(ArkUIVMContext vmContext, ArkUINodeHandle node, ArkUI_Int32 callbackId);
    ArkUI_Int32 (*measureLayoutAndDraw)(ArkUIVMContext vmContext, ArkUINodeHandle node);
    ArkUI_Int32 (*measureNode)(ArkUIVMContext vmContext, ArkUINodeHandle node, ArkUI_Float32* data);
    ArkUI_Int32 (*layoutNode)(ArkUIVMContext vmContext, ArkUINodeHandle node, ArkUI_Float32* data);
    ArkUI_Int32 (*drawNode)(ArkUIVMContext vmContext, ArkUINodeHandle node, ArkUI_Float32* data);

    void (*setAttachNodePtr)(ArkUINodeHandle node, void* value);
    void* (*getAttachNodePtr)(ArkUINodeHandle node);

    // maybe better to use int in px unit.
    void (*setMeasureWidth)(ArkUINodeHandle node, ArkUI_Int32 value);
    ArkUI_Int32 (*getMeasureWidth)(ArkUINodeHandle node);
    void (*setMeasureHeight)(ArkUINodeHandle node, ArkUI_Int32 value);
    ArkUI_Int32 (*getMeasureHeight)(ArkUINodeHandle node);
    void (*setX)(ArkUINodeHandle node, ArkUI_Int32 value);
    void (*setY)(ArkUINodeHandle node, ArkUI_Int32 value);
    ArkUI_Int32 (*getX)(ArkUINodeHandle node);
    ArkUI_Int32 (*getY)(ArkUINodeHandle node);
    void (*getLayoutConstraint)(ArkUINodeHandle node, ArkUI_Int32* value);
    void (*setAlignment)(ArkUINodeHandle node, ArkUI_Int32 value);
    ArkUI_Int32 (*getAlignment)(ArkUINodeHandle node);
    ArkUI_Int32 (*indexerChecker)(ArkUIVMContext context, ArkUINodeHandle node);
    void (*setRangeUpdater)(ArkUINodeHandle node, ArkUI_Int32 updaterId);
    void (*setLazyItemIndexer)(ArkUIVMContext vmContext, ArkUINodeHandle node, ArkUI_Int32 indexerId);
    /// Vsync support.
    ArkUIPipelineContext (*getPipelineContext)(ArkUINodeHandle node);
    void (*setVsyncCallback)(ArkUIVMContext vmContext, ArkUIPipelineContext pipelineContext, ArkUI_Int32 callbackId);
    void (*unblockVsyncWait)(ArkUIVMContext vmContext, ArkUIPipelineContext pipelineContext);
    /// Events.
    /**
     * Returns != 0 if an event was received,
     * fills in supplied buffer in such a case.
     * Must not block, blocking is performed by
     * ArkoalaHostApi.waitForVsync().
     */
    ArkUI_Int32 (*checkEvent)(ArkUINodeEvent* event);
    /**
     * Add an event to the event queue, so that
     * it will be picked up later by checkEvent().
     */
    void (*sendEvent)(ArkUINodeEvent* event);

    /// Continuations on native side.
    void (*callContinuation)(ArkUI_Int32 continuationId, ArkUI_Int32 argCount, ArkUIEventCallbackArg* args);
    void (*setChildTotalCount)(ArkUINodeHandle node, ArkUI_Int32 totalCount);

    /// Error reporting.
    void (*showCrash)(ArkUI_CharPtr message);
};

typedef enum {
    ON_ATTACH_TO_NODE = 1,
    ON_DETACH_FROM_NODE = 2,
    ON_GET_NODE_ID = 3,
    ON_ADD_NODE_TO_ADAPTER = 4,
    ON_REMOVE_NODE_FROM_ADAPTER = 5,
} ArkUINodeAdapterEventType;

typedef struct {
    ArkUI_Uint32 index;
    ArkUI_Int32 id;
    ArkUI_Int64 extraParam;
    ArkUI_Bool idSet;
    ArkUINodeAdapterEventType type;
    ArkUINodeHandle handle;
    ArkUI_Bool nodeSet;
} ArkUINodeAdapterEvent;

typedef struct {
    ArkUINodeAdapterHandle (*create)();
    void (*dispose)(ArkUINodeAdapterHandle handle);
    ArkUI_Int32 (*setTotalNodeCount)(ArkUINodeAdapterHandle handle, ArkUI_Uint32 size);
    ArkUI_Uint32 (*getTotalNodeCount)(ArkUINodeAdapterHandle handle);
    ArkUI_Int32 (*registerEventReceiver)(
        ArkUINodeAdapterHandle handle, void* userData, void (*receiver)(ArkUINodeAdapterEvent* event));
    void (*unregisterEventReceiver)(ArkUINodeAdapterHandle handle);

    ArkUI_Int32 (*notifyItemReloaded)(ArkUINodeAdapterHandle handle);
    ArkUI_Int32 (*notifyItemChanged)(ArkUINodeAdapterHandle handle, ArkUI_Uint32 startPosition, ArkUI_Uint32 itemCount);
    ArkUI_Int32 (*notifyItemRemoved)(ArkUINodeAdapterHandle handle, ArkUI_Uint32 startPosition, ArkUI_Uint32 itemCount);
    ArkUI_Int32 (*notifyItemInserted)(
        ArkUINodeAdapterHandle handle, ArkUI_Uint32 startPosition, ArkUI_Uint32 itemCount);
    ArkUI_Int32 (*notifyItemMoved)(ArkUINodeAdapterHandle handle, ArkUI_Uint32 from, ArkUI_Uint32 to);
    ArkUI_Int32 (*getAllItem)(ArkUINodeAdapterHandle handle, ArkUINodeHandle** items, ArkUI_Uint32* size);

    void (*attachHostNode)(ArkUINodeAdapterHandle handle, ArkUINodeHandle host);
    void (*detachHostNode)(ArkUINodeHandle host);
    ArkUINodeAdapterHandle (*getNodeAdapter)(ArkUINodeHandle host);
} ArkUINodeAdapterAPI;

/**
 * An API to control an implementation. When making changes modifying binary
 * layout, i.e. adding new events - increase ARKUI_NODE_API_VERSION above for binary
 * layout checks.
 */
struct ArkUIFullNodeAPI {
    ArkUI_Int32 version;
    void (*setCallbackMethod)(ArkUIAPICallbackMethod* method);
    const ArkUIBasicAPI* (*getBasicAPI)();
    const ArkUINodeModifiers* (*getNodeModifiers)();
    const ArkUIAnimation* (*getAnimation)();
    const ArkUINavigation* (*getNavigation)();
    const ArkUIGraphicsAPI* (*getGraphicsAPI)();
    const ArkUIDialogAPI* (*getDialogAPI)();
    const ArkUIExtendedNodeAPI* (*getExtendedAPI)();
    const ArkUINodeAdapterAPI* (*getNodeAdapterAPI)();
};

struct ArkUIAnyAPI {
    ArkUI_Int32 version;
};

#ifdef __cplusplus
};
#endif

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_API_H
