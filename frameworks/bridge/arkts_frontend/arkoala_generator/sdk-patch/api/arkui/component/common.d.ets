'use static'
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
/**
 * @file
 * @kit ArkUI
 */
import { ComponentBuilder } from './builder';
import OriginalContext from '../../application/Context';
import { Resource } from '../../global/resource';
import pointer from '../../@ohos.multimodalInput.pointer';
import image from '../../@ohos.multimedia.image';
import unifiedDataChannel from '../../@ohos.data.unifiedDataChannel';
import promptAction from '../../@ohos.promptAction';
import uniformTypeDescriptor from '../../@ohos.data.uniformTypeDescriptor';
import Want from '../../@ohos.app.ability.Want';
import { IntentionCode } from '../../@ohos.multimodalInput.intentionCode';
import { SymbolGlyphModifier } from '../../arkui/SymbolGlyphModifier';
import { ImageModifier } from '../../arkui/ImageModifier';
import { CircleShape, EllipseShape, PathShape, RectShape } from '../../@ohos.arkui.shape';
import uiObserver from '@ohos.arkui.observer';
import { UIContext as _UIContext } from '../../@ohos.arkui.UIContext';
import { DrawContext as _DrawContext, LengthMetrics } from '../../arkui/Graphics';
import uiEffect from '../../@ohos.graphics.uiEffect';
import { FocusBoxStyle, FocusPriority } from "./focus";
import { ComponentContent } from '../../arkui/ComponentContent';
import { ResizableOptions } from "./image";
import intl from '../../@ohos.intl';
import { ButtonType, ButtonStyleMode, ButtonRole } from "./button";
import { Area, ResourceColor, Dimension, ResourceStr, Font, Length, EdgeColors, LocalizedEdgeColors, BorderRadiuses, EdgeWidths, LocalizedEdgeWidths, SizeOptions, Bias, EdgeStyles, Position, LocalizedBorderRadiuses, Margin, ChainWeightOptions, Padding, LocalizedPadding, LocalizedMargin, BorderOptions, OutlineOptions, EdgeOutlineStyles, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, AccessibilityOptions, ConstraintSizeOptions, EdgeWidth, DirectionalEdgesT, VoidCallback, ColorMetrics, AccessibilityActionOptions, ScrollBarMargin } from "./units";
import { BaseGestureEvent, GestureRecognizer, TouchRecognizer, GestureJudgeResult, GestureType, GestureMask, GestureHandler, GesturePriority, GestureInfo } from "./gesture";
import { ScrollState } from "./list";
import { AccessibilityHoverType, GestureCollectIntervention, Curve, PlayMode, SharedTransitionEffectType, KeySource, BorderStyle, HorizontalAlign, LocalizedAlignment, RenderStrategy, VerticalAlign, MouseButton, MouseAction, FontWeight, TouchType, FontStyle, Color, ColoringStrategy, Placement, ArrowPointPosition, ClickEffectLevel, NestedScrollMode, HitTestMode, Alignment, ImageRepeat, ImageSize, HoverEffect, Visibility, ItemAlign, Direction, Axis, GradientDirection, FunctionKey, ModifierKey, ObscuredReasons, RenderFit, LineCapStyle, LineJoinStyle, PixelRoundCalcPolicy, TextDecorationType, TextDecorationStyle, KeyType, ResponseType, BarState, EdgeEffect, ScrollSource, InteractionHand, AxisAction, AxisType, AxisModel, CrownAction, FocusDrawLevel, CrownSensitivity, IlluminatedType, ResponseRegionSupportedTool, TipsAnchorType, InputEventInterceptAction } from "./enums";
import { TextRange } from "./textCommon";
import { StyledString } from "./styledString";
import { CustomBuilder, WrappedBuilder, CustomBuilderT } from './builder';
import { RecordData } from '../../@ohos.base';
import curves from '../../@ohos.curves';
import matrix4 from '../../@ohos.matrix4';
import { AvoidanceMode } from './select';
import uiMaterial from '../../@ohos.arkui.uiMaterial';
import { OnScrollFrameBeginCallback } from "./scroll";
import dragController from '../../@ohos.arkui.dragController';
/**
 * Define the ratio of characters entered by the the percentage of InputCounterOptions.
 *
 * @interface InputCounterOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface InputCounterOptions {
    /**
     * It is the numerator bit of the percentage and used as a threshold. If the number of characters input
     * reaches the maximum number of characters multiplied by this threshold, the counter is displayed.
     *
     * <p><strong>NOTE</strong>:
     * <br>Threshold percentage for displaying the character counter.
     * <br>The character counter is displayed when the number of characters that have been entered is greater than
     * the maximum number of characters multiplied by the threshold percentage value.
     * <br>When displayed, the character counter is in the following format:
     * <br>Number of characters that have been entered/Maximum number of characters allowed.
     * <br>It is visible when the number of characters entered is greater than
     * the character limit multiplied by the threshold percentage value.
     * <br>Value range: [1, 100]
     * <br>If the value is not an integer, it is rounded down to the nearest integer.
     * <br>If the value exceeds the valid value range, the character counter is not displayed.
     * <br>If the value is <em>undefined</em>, the character counter is displayed, but this parameter has no effect.
     * </p>
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    thresholdPercentage?: double;
    /**
     * If the current input character count reaches the maximum character count and users want to exceed the
     * normal input, the border will turn red. If this parameter is true, the red border displayed.
     *
     * <p><strong>NOTE</strong>:
     * <br>Whether to highlight the text box border and character counter subscript in red.
     * <br>If options is not set, the text box border and character counter subscript turn red
     * <br>when the number of characters entered reaches the limit.
     * <br>If the character counter is displayed and thresholdPercentage is set to a valid value,
     * the text box border and character counter subscript turn red when the number of entered characters exceeds the limit.
     * <br>The value true (default) means to highlight the text box border and character counter subscript in red.
     * </p>
     *
     * @type { ?boolean }
     * @default true
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    highlightBorder?: boolean;
    /**
     * It is the color of counter when textField hasn't wanted to exceed the maximum character count.
     * 
     * @type { ?ColorMetrics }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 24
     */
    counterTextColor?: ColorMetrics;

    /**
     * It is the color of counter when textField wants to exceed the maximum character count.
     * 
     * @type { ?ColorMetrics }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 24
     */
    counterTextOverflowColor?: ColorMetrics;
}
/**
 * Defines the options of decoration.
 *
 * @interface TextDecorationOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface TextDecorationOptions {
    /**
     * The decoration type.
     *
     * @type { TextDecorationType | undefined }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    type: TextDecorationType | undefined;
    /**
     * Sets the color of decoration.
     *
     * @type { ?ResourceColor }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    color?: ResourceColor;
    /**
     * The style value of decoration.
     *
     * @type { ?TextDecorationStyle }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    style?: TextDecorationStyle;
    /**
     * The scale value of decoration thickness.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 26.0.0
     */
    thicknessScale?: double;
}
/**
 * Provides an interface for the style of an divider including stroke width, color, start margin
 * and end margin
 *
 * @interface DividerStyle
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface DividerStyle {
    /**
     * Define the stroke width of the divider
     *
     * @type { Length | undefined }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    strokeWidth: Length | undefined;
    /**
     * Define the color of the divider
     *
     * @type { ?ResourceColor }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    color?: ResourceColor;
    /**
     * Define the start margin of the divider
     *
     * @type { ?Length }
     * @default 0
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    startMargin?: Length;
    /**
     * Define the end margin of the divider
     *
     * @type { ?Length }
     * @default 0
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    endMargin?: Length;
}
/**
 * The **AnimatableArithmetic** API defines the animation operation rules for
 * non-number data types. To animate non-number data (such as arrays, structs,
 * and colors), implement the addition, subtraction, multiplication, and
 * equality judgment functions in the **AnimatableArithmetic\<T\>** API.
 * In this way, the data can be involved in an interpolation operation of the
 * animation and identify whether the data changes, that is, the non-number data
 * is defined as the types that implement the **AnimatableArithmetic\<T\>** API.
 *
 * @interface AnimatableArithmetic
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface AnimatableArithmetic<T> {
    /**
     * Defines the addition rule of the data type.
     *
     * @param { AnimatableArithmetic<T> } rhs - another value
     * @returns { AnimatableArithmetic<T> } new value which implements AnimatableArithmetic<T> interface
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    plus(rhs: AnimatableArithmetic<T>): AnimatableArithmetic<T>;
    /**
     * Defines the subtraction rule of the data type.
     *
     * @param { AnimatableArithmetic<T> } rhs - another value
     * @returns { AnimatableArithmetic<T> } new value which implements AnimatableArithmetic<T> interface
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    subtract(rhs: AnimatableArithmetic<T>): AnimatableArithmetic<T>;
    /**
     * Defines the multiplication rule of the data type.
     *
     * @param { double } scale - scale value
     * @returns { AnimatableArithmetic<T> } new value which implements AnimatableArithmetic<T> interface
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    multiply(scale: double): AnimatableArithmetic<T>;
    /**
     * Defines the equality judgment rule of the data type.
     *
     * @param { AnimatableArithmetic<T> } rhs - another value
     * @returns { boolean } is equals
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    equals(rhs: AnimatableArithmetic<T>): boolean;
}
/**
  * ReuseId callback type. It is used to compute reuseId.
  *
  * @typedef { function } ReuseIdCallback
  * @returns { string }
  * @syscap SystemCapability.ArkUI.ArkUI.Full
  * @since 23
  */
export type ReuseIdCallback = () => string;
/**
 * Defining the reusable configuration parameters.
 *
 * @interface ReuseOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface ReuseOptions {
    /**
     * Defining reuseId function. The default reuseId is the custom component name.
     *
     * @type { ?ReuseIdCallback }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    reuseId?: ReuseIdCallback;
}
/**
 * Export Context.
 *
 * @typedef { OriginalContext } Context
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 23
 */
export type Context = OriginalContext;
/**
 * Post Card Action.
 *
 * @param { Object } component - indicate the card entry component.
 * @param { Object } action - indicate the router, message or call event.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 23
 */
export declare function postCardAction(component: Object, action: Object): void;
/**
 * Defines the data type of the interface restriction.
 *
 * @interface Configuration
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface Configuration {
    /**
     * Set colorMode.
     *
     * @type { string }
     * @readonly
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    readonly colorMode: string;
    /**
     * Set fontScale.
     *
     * @type { double }
     * @readonly
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    readonly fontScale: double;
}
/**
 * The data type used to describe a rectangular area.
 *
 * @interface Rectangle
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface Rectangle {
    /**
     * x:Horizontal coordinate
     *
     * @type { ?Length }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    x?: Length;
    /**
     * y:Vertical axis coordinate.
     *
     * @type { ?Length }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    y?: Length;
    /**
     * Sets the width of the current touchRect.
     *
     * @type { ?Length }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    width?: Length;
    /**
     * Sets the height of the current touchRect.
     *
     * @type { ?Length }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    height?: Length;
}
/**
 * Defines the response region interface.
 * 
 * @interface ResponseRegion
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface ResponseRegion {
  /**
   *  The event tool type applicable to this response region.
   * 
   * @type { ?ResponseRegionSupportedTool }
   * @default ResponseRegionSupportedTool.ALL
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  tool?: ResponseRegionSupportedTool;

  /**
   * Horizontal axis coordinate
   * 
   * @type { ?LengthMetrics }
   * @default LengthMetrics.vp(0)
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  x?: LengthMetrics;

  /**
   * Vertical axis coordinate.
   * 
   * @type { ?LengthMetrics }
   * @default LengthMetrics.vp(0)
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  y?: LengthMetrics;

  /**
   * Sets the width of the current touchRect.
   * 
   * @type { ?(LengthMetrics | string) }
   * @default LengthMetrics.percent(1)
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  width?: LengthMetrics | string;

  /**
   * Sets the height of the current touchRect.
   * 
   * @type { ?(LengthMetrics | string) }
   * @default LengthMetrics.percent(1)
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  height?: LengthMetrics | string;
}
/**
 * Interface for ExpectedFrameRateRange.
 *
 * @interface ExpectedFrameRateRange
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface ExpectedFrameRateRange {
    /**
     * The minimum animation drawing FPS.
     * The minimum value should be less than or equal to the maximum value.
     * @type { int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    min: int;
    /**
     * The maximum animation drawing FPS.
     * The maximum value should be greater than or equal to the minimum value.
     * @type { int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    max: int;
    /**
     * The expected frame rate of dynamical callback rate range.
     * The value should be between the minimum and maximum value.
     * Otherwise, the actual callback rate will be dynamically
     * adjusted to better align with other animation sources.
     * @type { int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    expected: int;
}
/**
 * global $r function
 *
 * @param { string } value
 * @param { RecordData[] } params
 * @returns { Resource }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare function $r(value: string, ...params: RecordData[]): Resource;
/**
 * global $rawfile function
 *
 * @param { string } value name of the file in the resources/rawfile directory of the project.
 *     When referencing resources of the Resource type, make sure the data type is the same as
 *     that of the attribute method. For example, if an attribute method supports the
 *     string | Resource types, the data type of the Resource type must be string.
 * @returns { Resource }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare function $rawfile(value: string): Resource;
/**
 * Defines the same page mode
 * @enum { int }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum AccessibilitySamePageMode {
    /**
    * the first page and root page event is not send.but if application load new page whith navigation,the page event will be sent.
    * this mode is to solve skipping focus
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    SEMI_SILENT = 0,
    /**
     * the all page event is not send
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    FULL_SILENT = 1
}
/**
 * Enum for accessibility component type
 * @enum { int }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum AccessibilityRoleType {
    /**
    * ActionSheet component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    ACTION_SHEET = 0,
    /**
    * AlertDialog component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    ALERT_DIALOG = 1,
    /**
    * AlphabetIndexer component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    INDEXER_COMPONENT = 2,
    /**
    * badge component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    BADGE_COMPONENT = 3,
    /**
    * blank component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    BLANK = 4,
    /**
    * button component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    BUTTON = 5,
    /**
    * button component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    BACK_BUTTON = 6,
    /**
    * sheet drag bar component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    SHEET_DRAG_BAR = 7,
    /**
    * calendar picker component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    CALENDAR_PICKER = 8,
    /**
    * calendar component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    CALENDAR = 9,
    /**
    * canvas component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    CANVAS = 10,
    /**
    * canvas gradient component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    CANVAS_GRADIENT = 11,
    /**
    * canvas pattern component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    CANVAS_PATTERN = 12,
    /**
    * checkbox component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    CHECKBOX = 13,
    /**
    * checkbox group component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    CHECKBOX_GROUP = 14,
    /**
    * circle component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    CIRCLE = 15,
    /**
    * column split component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    COLUMN_SPLIT = 16,
    /**
    * column component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    COLUMN = 17,
    /**
    * canvas rendering context 2d component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    CANVAS_RENDERING_CONTEXT_2D = 18,
    /**
    * chart component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    CHART = 19,
    /**
    * counter component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
    */
    COUNTER = 20,
    /**
    * counter modal component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    CONTAINER_MODAL = 21,
    /**
    * data panel component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    DATA_PANEL = 22,
    /**
    * data picker component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    DATE_PICKER = 23,
    /**
    * dialog component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    DIALOG = 24,
    /**
    * divider component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    DIVIDER = 25,
    /**
    * drag bar component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    DRAG_BAR = 26,
    /**
    * effect component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    EFFECT_COMPONENT = 27,
    /**
    * ellipse component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    ELLIPSE = 28,
    /**
    * flex component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    FLEX = 29,
    /**
    * flow item component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    FLOW_ITEM = 30,
    /**
    * form component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    FORM_COMPONENT = 31,
    /**
    * form link component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    FORM_LINK = 32,
    /**
    * gauge component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    GAUGE = 33,
    /**
    * grid component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    GRID = 34,
    /**
    * grid col component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    GRID_COL = 35,
    /**
    * grid container component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    GRID_CONTAINER = 36,
    /**
    * grid item component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    GRID_ITEM = 37,
    /**
    * grid row component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    GRID_ROW = 38,
    /**
    * hyperlink component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    HYPERLINK = 39,
    /**
    * image component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    IMAGE = 40,
    /**
    * image animator component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    IMAGE_ANIMATOR = 41,
    /**
    * image bitmap component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    IMAGE_BITMAP = 42,
    /**
    * image data component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    IMAGE_DATA = 43,
    /**
    * image span component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    IMAGE_SPAN = 44,
    /**
    * label component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    LABEL = 45,
    /**
    * line component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    LINE = 46,
    /**
    * list component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    LIST = 47,
    /**
    * list item component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    LIST_ITEM = 48,
    /**
    * list item group component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    LIST_ITEM_GROUP = 49,
    /**
    * loading progress component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    LOADING_PROGRESS = 50,
    /**
    * marquee component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    MARQUEE = 51,
    /**
    * matrix2d component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    MATRIX2D = 52,
    /**
    * menu component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    MENU = 53,
    /**
    * menu item component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    MENU_ITEM = 54,
    /**
    * menu item group component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    MENU_ITEM_GROUP = 55,
    /**
    * navdestination component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    NAV_DESTINATION = 56,
    /**
    * navrouter component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    NAV_ROUTER = 57,
    /**
    * navigation component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    NAVIGATION = 58,
    /**
    * navigation bar component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    NAVIGATION_BAR = 59,
    /**
    * navigation menu component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    NAVIGATION_MENU = 60,
    /**
    * navigator component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    NAVIGATOR = 61,
    /**
    * offscreen canvas component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    OFFSCREEN_CANVAS = 62,
    /**
    * offscreen canvas rendering context2d component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    OFFSCREEN_CANVAS_RENDERING_CONTEXT2D = 63,
    /**
    * option component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    OPTION = 64,
    /**
    * panel component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    PANEL = 65,
    /**
    * paper page component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    PAPER_PAGE = 66,
    /**
    * path component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    PATH = 67,
    /**
    * path 2d component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    PATH2D = 68,
    /**
    * pattern lock component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    PATTERN_LOCK = 69,
    /**
    * picker component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    PICKER = 70,
    /**
    * picker view component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    PICKER_VIEW = 71,
    /**
    * plugin component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    PLUGIN_COMPONENT = 72,
    /**
    * polygon component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    POLYGON = 73,
    /**
    * polyline component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    POLYLINE = 74,
    /**
    * pop up component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    POPUP = 75,
    /**
    * progress component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    PROGRESS = 76,
    /**
    * qr code component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    QRCODE = 77,
    /**
    * radio component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    RADIO = 78,
    /**
    * rating component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    RATING = 79,
    /**
    * rect component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    RECT = 80,
    /**
    * refresh component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    REFRESH = 81,
    /**
    * relative container component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    RELATIVE_CONTAINER = 82,
    /**
    * remote window component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    REMOTE_WINDOW = 83,
    /**
    * rich editor component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    RICH_EDITOR = 84,
    /**
    * rich text component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    RICH_TEXT = 85,
    /**
    * rolepager component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    ROLE_PAGER = 86,
    /**
    * row component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    ROW = 87,
    /**
    * row split component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    ROW_SPLIT = 88,
    /**
    * scroll component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    SCROLL = 89,
    /**
    * scroll bar component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    SCROLL_BAR = 90,
    /**
    * search component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    SEARCH = 91,
    /**
    * search field component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    SEARCH_FIELD = 92,
    /**
    * select component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    SELECT = 93,
    /**
    * shape component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    SHAPE = 94,
    /**
    * sidebar container component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    SIDEBAR_CONTAINER = 95,
    /**
    * slider component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    SLIDER = 96,
    /**
    * span component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    SPAN = 97,
    /**
    * stack component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    STACK = 98,
    /**
    * stepper component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    STEPPER = 99,
    /**
    * stepper item component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    STEPPER_ITEM = 100,
    /**
    * swiper component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    SWIPER = 101,
    /**
    * swiper indicator component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    SWIPER_INDICATOR = 102,
    /**
    * switch component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    SWITCH = 103,
    /**
    * symbol glyph component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    SYMBOL_GLYPH = 104,
    /**
    * tab content component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    TAB_CONTENT = 105,
    /**
    * tab bar component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    TAB_BAR = 106,
    /**
    * tabs component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    TABS = 107,
    /**
    * text component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    TEXT = 108,
    /**
    * text clock component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    TEXT_CLOCK = 109,
    /**
    * text entry component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    TEXT_ENTRY = 110,
    /**
    * text input component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    TEXT_INPUT = 111,
    /**
    * text picker component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    TEXT_PICKER = 112,
    /**
    * text timer component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    TEXT_TIMER = 113,
    /**
    * text area component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    TEXT_AREA = 114,
    /**
    * text field component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    TEXT_FIELD = 115,
    /**
    * time picker component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    TIME_PICKER = 116,
    /**
    * title bar component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    TITLE_BAR = 117,
    /**
    * toggler component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    TOGGLER = 118,
    /**
    * uiextensioncomponent component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    UI_EXTENSION_COMPONENT = 119,
    /**
    * video component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    VIDEO = 120,
    /**
    * water flow component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    WATER_FLOW = 121,
    /**
    * web component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    WEB = 122,
    /**
    * xcomponent component type
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    XCOMPONENT = 123,
    /**
    * none component type: screen reader will not broadcast the component type.
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    ROLE_NONE = 124
}
/**
 * Defines the callback type used in accessibility focus. The value of isFocus indicates whether
 * the current component is focused
 * @typedef {function} AccessibilityFocusCallback
 * @param {boolean} isFocus - if component is focused,isFocus will be true. else isFocus is false.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type AccessibilityFocusCallback = (isFocus: boolean) => void;

/**
 * Enum for accessibility action type
 * @enum { int }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum AccessibilityAction {
  /**
  * undefined action type
  * @syscap SystemCapability.ArkUI.ArkUI.Full
  * @since 23
  */
  UNDEFINED_ACTION = 0,
  /**
  * accessibility click action
  * @syscap SystemCapability.ArkUI.ArkUI.Full
  * @since 23
  */
  ACCESSIBILITY_CLICK = 1,
}

/**
 * Enum for the result of accessibility action intercept function
 * @enum { int }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum AccessibilityActionInterceptResult {
  /**
  * intercept the accessibility action
  * @syscap SystemCapability.ArkUI.ArkUI.Full
  * @since 23
  */
  ACTION_INTERCEPT = 0,
  /**
  * the accessibility action can be continued
  * @syscap SystemCapability.ArkUI.ArkUI.Full
  * @since 23
  */
  ACTION_CONTINUE = 1,
  /**
  * the accessibility action need to bubble up for execution
  * @syscap SystemCapability.ArkUI.ArkUI.Full
  * @since 23
  */
  ACTION_RISE = 2,
}

/**
 * Defines the callback type used in accessibility action intercept.
 * The value of action indicates the accessibility action type.
 * @typedef { function } AccessibilityActionInterceptCallback
 * @param { AccessibilityAction } action - the enum of accessibility action type.
 * @returns { AccessibilityActionInterceptResult } the result of continuing to execute the action or interrupting it or bubbling up
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare type AccessibilityActionInterceptCallback = (action: AccessibilityAction) => AccessibilityActionInterceptResult;

/**
 * Enum for FinishCallbackType.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum FinishCallbackType {
    /**
     * The callback is invoked when the entire animation is removed once it has finished.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    REMOVED = 0,
    /**
      * The callback is invoked when the animation logically enters the falling state,
      * though it may still be in its long tail state.
      *
      * @syscap SystemCapability.ArkUI.ArkUI.Full
      * @since 23
      */
    LOGICALLY = 1
}
/**
 * Defines the touch test strategy object.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum TouchTestStrategy {
    /**
     * Custom dispatch has no effect; the system distributes events based on the hit status of the current node.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DEFAULT = 0,
    /**
     * The specified event is forwarded to a particular child node, and the system determines whether to
     * distribute the event to other sibling nodes.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    FORWARD_COMPETITION = 1,
    /**
     * The specified event is forwarded to a particular child node, and the system no longer distributes
     * the event to other sibling nodes.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    FORWARD = 2
}
/**
 * Defines the animate function params.
 *
 * @interface AnimateParam
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface AnimateParam {
    /**
     * Animation duration, in ms.
     *
     * @type { ?int }
     * @default 1000
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    duration?: int;
    /**
     * Animation playback speed. A larger value indicates faster animation playback, and a smaller value indicates slower
     * animation playback. The value 0 means that there is no animation.
     *
     * @type { ?double }
     * @default 1.0
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    tempo?: double;
    /**
     * Animation curve.
     *
     * @type { ?(Curve | string | ICurve) }
     * @default Curve.EaseInOut
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    curve?: Curve | string | ICurve;
    /**
     * Animation delay time, in ms. By default, the animation has no delay.
     *
     * @type { ?int }
     * @default 0
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    delay?: int;
    /**
     * Number of times that the animation is played. By default, the animation is played once.
     * The value **-1** indicates that the animation is played for an unlimited number of times.
     * The value **0** indicates that there is no animation.
     *
     * @type { ?int }
     * @default 1
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    iterations?: int;
    /**
     * Playback mode. By default, the animation is played from the beginning after the playback is complete.
     *
     * @type { ?PlayMode }
     * @default PlayMode.Normal
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    playMode?: PlayMode;
    /**
     * Callback invoked when the animation playback is complete.
     *
     * @type { ?function }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onFinish?: () => void;
    /**
     * Type of the **onFinish** callback.
     * Default value: FinishCallbackType.REMOVED.
     *
     * @type { ?FinishCallbackType }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    finishCallbackType?: FinishCallbackType;
    /**
     * Expected frame rate range of the animation.
     *
     * @type { ?ExpectedFrameRateRange }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    expectedFrameRateRange?: ExpectedFrameRateRange;
}
/**
 * Interface for curve object.
 *
 * @typedef { curves.ICurve } ICurve
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type ICurve = curves.ICurve;
/**
 * Interface for matrix object.
 *
 * @typedef { matrix4.Matrix4Transit } Matrix4Transit
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type Matrix4Transit = matrix4.Matrix4Transit;
/**
 * Defines the motion path options.
 *
 * @interface MotionPathOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface MotionPathOptions {
    /**
     * Motion path of the translation animation.
     * The **svg** path string is used.
     * In the value, **start** and **end** can be used in place of the start point and end point,
     * for example, **'Mstart.x start.y L50 50 Lend.x end.y Z'**.
     * If this parameter is set to an empty string, the path animation is not set.
     *
     * @type { string }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    path: string;
    /**
     * Start point of the motion path.
     * Value range: [0, 1].
     * A value less than 0 or greater than 1 evaluates to the default value **0**.
     *
     * @type { ?double }
     * @default 0.0
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    from?: double;
    /**
     * End point of the motion path.
     * Value range: [0, 1].
     * A value less than 0 or greater than 1 evaluates to the default value **1**,
     * provided that the value of **to** is greater than or equal to the value of **from**.
     *
     * @type { ?double }
     * @default 1.0
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    to?: double;
    /**
     * Whether to rotate along the path.
     *
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    rotatable?: boolean;
}
/**
 * Defines the shard transition function params.
 *
 * @interface sharedTransitionOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface sharedTransitionOptions {
    /**
     * Animation duration.
     * <br>Default value: **1000**.
     * <br>Unit: ms.
     * <br>Value range: [0, +∞).
     *
     * @type { ?int }
     * @default 1000
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    duration?: int;
    /**
     * Animation curve.<br>You are advised to specify the curve using the **Curve** or
     * ** ICurve** type.<br>For the string type, this parameter indicates an animation
     * interpolation curve. For available values, see the **curve** parameter in
     * AnimateParam.
     * <br>Default value: **Curve.Linear**.
     *
     * @type { ?(Curve | string | ICurve) }
     * @default 1000
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    curve?: Curve | string | ICurve;
    /**
     * Animation delay time, in ms.
     *
     * @type { ?int }
     * @default 0
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    delay?: int;
    /**
     * The motion path info.
     *
     * @type { ?MotionPathOptions }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    motionPath?: MotionPathOptions;
    /**
     * Z index info.
     *
     * @type { ?int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    zIndex?: int;
    /**
     * the animate type.
     *
     * @type { ?SharedTransitionEffectType }
     * @default SharedTransitionEffectType.Exchange
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    type?: SharedTransitionEffectType;
}
/**
 * Defines the options of geometry transition.
 *
 * @interface GeometryTransitionOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface GeometryTransitionOptions {
    /**
     * whether follow target for the component still in the hierarchy, default: false, stay current.
     *
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    follow?: boolean;

    /**
     * Defines movement strategy of source and target in the hierarchy during geometry transition.
     * 
     * @type { ?TransitionHierarchyStrategy }
     * @default TransitionHierarchyStrategy.ADAPTIVE
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @systemapi
     * @since 23
     */
  hierarchyStrategy?: TransitionHierarchyStrategy
}
/**
 * Defines the options of linear gradient.
 *
 * @interface LinearGradientOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface LinearGradientOptions {
    /**
     * Defines starting angle of linear gradient.
     *
     * Anonymous Object Rectification.
     * @type { ?(double | string) }
     * @default 180
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    angle?: double | string;
    /**
     * Defines the direction of linear gradient.
     *
     * Anonymous Object Rectification.
     * @type { ?GradientDirection }
     * @default GradientDirection.Bottom
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    direction?: GradientDirection;
    /**
     * Defines color description for gradients.
     *
     * Anonymous Object Rectification.
     * @type { Array<[ResourceColor, double]> }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    colors: Array<[
        ResourceColor,
        double
    ]>;
    /**
     * Defines gradient colors with repeated coloring.
     *
     * Anonymous Object Rectification.
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    repeating?: boolean;
}

/**
 * Source and target are two matched elements during the geometry transition.
 * The animation starts at the source and ends at the target.
 * TransitionHierarchyStrategy enumeration defines how levels of source and target elements
 * would be changed in the hierarchy during the geometry transition.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @systemapi
 * @since 23
 */
export declare enum TransitionHierarchyStrategy {

  /**
   * None mode.
   * Source and target staty in the original level in the hierarchy during geometry transition.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @systemapi
   * @since 23
   */
  NONE = 0,

  /**
   * ADAPTIVE mode.
   * Lower level one of source and target is elevated to higher level of both,
   * indicating that two elements are in same high level.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @systemapi
   * @since 23
   */
  ADAPTIVE = 1,
}

/**
 * Defines the options of sweep gradient.
 *
 * @interface SweepGradientOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface SweepGradientOptions {
    /**
     * Defines center point for angle gradient.
     *
     * Anonymous Object Rectification.
     * @type { [Length, Length] }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    center: [
        Length,
        Length
    ];
    /**
     * Defines the starting point of angle gradient.
     *
     * Anonymous Object Rectification.
     * @type { ?(double | string) }
     * @default 0
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    start?: double | string;
    /**
     * Defines end point of angle gradient.
     *
     * Anonymous Object Rectification.
     * @type { ?(double | string) }
     * @default 0
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    end?: double | string;
    /**
     * Defines the rotation angle of the gradient.
     *
     * Anonymous Object Rectification.
     * @type { ?(double | string) }
     * @default 0
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    rotation?: double | string;
    /**
     * Defines color description for gradients.
     *
     * Anonymous Object Rectification.
     * @type { Array<[ResourceColor, double]> }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    colors: Array<[
        ResourceColor,
        double
    ]>;
    /**
     * Defines color description in ColorMetrics format for gradients.
     * This parameter takes precedence over colors parameter.
     *
     * @type { ?Array<[ColorMetrics, double]> }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    metricsColors?: Array<[
        ColorMetrics,
        double
    ]>;
    /**
     * Defines gradient colors with repeated coloring.
     *
     * Anonymous Object Rectification.
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    repeating?: boolean;
}
/**
 * Defines the options of radial gradient.
 *
 * @interface RadialGradientOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface RadialGradientOptions {
    /**
     * Defines center point for radial gradient.
     *
     * Anonymous Object Rectification.
     * @type { [Length, Length] }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    center: [
        Length,
        Length
    ];
    /**
     * Defines radius of the radial gradient.
     *
     * Anonymous Object Rectification.
     * @type { Length }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    radius: Length;
    /**
     * Defines color description for gradients.
     *
     * Anonymous Object Rectification.
     * @type { Array<[ResourceColor, double]> }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    colors: Array<[
        ResourceColor,
        double
    ]>;
    /**
     * Defines gradient colors with repeated coloring.
     *
     * Anonymous Object Rectification.
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    repeating?: boolean;
}
/**
 * Defines the options of translate.
 *
 * @interface TranslateOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface TranslateOptions {
    /**
     * Translation distance along the x-axis.
     * For the number type, the unit is VP, and the value range is (-∞, +∞).
     * For the string type, the value follows the format of length string type.
     *
     * @type { ?(double | string) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    x?: double | string;
    /**
     * Translation distance along the y-axis.
     * For the number type, the unit is VP, and the value range is (-∞, +∞).
     * For the string type, the value follows the format of length string type.
     *
     * @type { ?(double | string) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    y?: double | string;
    /**
     * Distance to translate along the z-axis. The value is a floating
     * point number, the default value is 0.0, and the unit is px.
     *
     * @type { ?(double | string) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    z?: double | string;
}
/**
 * Defines the options of scale.
 *
 * @interface ScaleOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface ScaleOptions {
    /**
     * Scale ratio along the x-axis.
     * x > 1: The component is scaled up along the x-axis.
     * 0 < x < 1: The component is scaled down along the x-axis.
     * x < 0: The component is scaled in the reverse direction of the x-axis.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    x?: double;
    /**
     * Scale ratio along the y-axis.
     * y > 1: The component is scaled up along the y-axis.
     * 0 < y < 1: The component is scaled down along the y-axis.
     * y < 0: The component is scaled in the reverse direction of the y-axis.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    y?: double;
    /**
     * Scale ratio along the z-axis. z > 1: The component is scaled up along the z-axis.
     * <br>0 < z < 1: The component is scaled down along the z-axis.
     * <br>z < 0: The component is scaled in the reverse direction of the z-axis.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    z?: double;
    /**
     * X coordinate of the transformation center point (anchor). Unit is vp.
     *
     * @type { ?(double | string) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    centerX?: double | string;
    /**
     * Y coordinate of the transformation center point (anchor). Unit is vp.
     *
     * @type { ?(double | string) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    centerY?: double | string;
}
/**
 * Defines the align rule options of relative container.
 *
 * @interface VerticalAlignParam
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface VerticalAlignParam {
    /**
     * Specifies the anchor component
     *
     * Anonymous Object Rectification
     * @type { string } anchor
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    anchor: string;
    /**
     * Sets the vertical alignment relative to the anchor component.
     *
     * Anonymous Object Rectification
     * @type { VerticalAlign }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    align: VerticalAlign;
}
/**
 * Defines the horizontal align rule options of relative container.
 *
 * @interface HorizontalAlignParam
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface HorizontalAlignParam {

    /**
     * Specifies the anchor component
     *
     * Anonymous Object Rectification
     * @type { string } anchor
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    anchor: string;
    /**
     * Sets the horizontal alignment relative to the anchor component.
     *
     * Anonymous Object Rectification
     * @type { HorizontalAlign } align
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    align: HorizontalAlign;
}
/**
 * Defines the align rule options of relative container.
 *
 * @interface AlignRuleOption
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface AlignRuleOption {
    /**
     * The param of left align.
     *
     * @type { ?HorizontalAlignParam }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    left?: HorizontalAlignParam;
    /**
     * The param of right align.
     *
     * @type { ?HorizontalAlignParam }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    right?: HorizontalAlignParam;
    /**
     * The param of middle align.
     *
     * @type { ?HorizontalAlignParam }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    middle?: HorizontalAlignParam;
    /**
     * The param of top align.
     *
     * @type { ?VerticalAlignParam }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    top?: VerticalAlignParam;
    /**
     * The param of bottom align.
     *
     * @type { ?VerticalAlignParam }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    bottom?: VerticalAlignParam;
    /**
     * The param of center align.
     *
     * @type { ?VerticalAlignParam }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    center?: VerticalAlignParam;
    /**
     * Defines the bias ratio in horizontal and vertical direction.
     *
     * @type { ?Bias }
     * @default {horizontal:0.5,vertical:0.5}
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    bias?: Bias;
}
/**
 * Defines the localized horizontal align param of relative container.
 *
 * @interface LocalizedHorizontalAlignParam
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface LocalizedHorizontalAlignParam {
    /**
     * ID of the component that serves as the anchor.
     *
     * @type { string }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    anchor: string;
    /**
     * Horizontal alignment mode relative to the anchor component.
     *
     * @type { HorizontalAlign }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    align: HorizontalAlign;
}
/**
 * Defines the localized vertical align param of relative container.
 *
 * @interface LocalizedVerticalAlignParam
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface LocalizedVerticalAlignParam {
    /**
     * ID of the component that serves as the anchor.
     *
     * @type { string }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    anchor: string;
    /**
     * Vertical alignment mode relative to the anchor component.
     *
     * @type { VerticalAlign }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    align: VerticalAlign;
}
/**
 * Defines the Localized align rule options of relative container.
 *
 * @interface LocalizedAlignRuleOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface LocalizedAlignRuleOptions {
    /**
     * Left alignment with left-to-right scripts and right alignment with right-to-left scripts in the horizontal direction.
     *
     * @type { ?LocalizedHorizontalAlignParam }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    start?: LocalizedHorizontalAlignParam;
    /**
     * Right alignment with left-to-right scripts and left alignment with right-to-left scripts in the horizontal direction.
     *
     * @type { ?LocalizedHorizontalAlignParam }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    end?: LocalizedHorizontalAlignParam;
    /**
     * Center alignment in the horizontal direction.
     *
     * @type { ?LocalizedHorizontalAlignParam }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    middle?: LocalizedHorizontalAlignParam;
    /**
     * Top alignment in the vertical direction.
     *
     * @type { ?LocalizedVerticalAlignParam }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    top?: LocalizedVerticalAlignParam;
    /**
     * Bottom alignment in the vertical direction.
     *
     * @type { ?LocalizedVerticalAlignParam }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    bottom?: LocalizedVerticalAlignParam;
    /**
     * Center alignment in the vertical direction.
     *
     * @type { ?LocalizedVerticalAlignParam }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    center?: LocalizedVerticalAlignParam;
    /**
     * Offset of the component under the anchor constraints.
     * <br>The value is the ratio of the distance to the left/upper anchor to the total distance between anchors.
     *
     * @type { ?Bias }
     * @default {horizontal:0.5,vertical:0.5}
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    bias?: Bias;
}
/**
 * Enumerates the chain styles in relative container.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum ChainStyle {
    /**
     * Child components are evenly distributed among constraint anchors.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    SPREAD = 0,
    /**
     * All child components except the first and last ones are evenly distributed among constraint anchors.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    SPREAD_INSIDE = 1,
    /**
     * There is no gap between child components in the chain.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    PACKED = 2
}
/**
 * The param of rotate.
 *
 * @interface RotateOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface RotateOptions {
    /**
     * X coordinate of the rotation axis vector.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    x?: double;
    /**
     * Y coordinate of the rotation axis vector.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    y?: double;
    /**
     * Z coordinate of the rotation axis vector.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    z?: double;
    /**
     * X coordinate of the transformation center point (anchor). Unit is vp.
     *
     * @type { ?(double | string) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    centerX?: double | string;
    /**
     * Y coordinate of the transformation center point (anchor). Unit is vp.
     *
     * @type { ?(double | string) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    centerY?: double | string;
    /**
     * Z-axis anchor, that is, the z-component of the 3D rotation center point.
     *
     * @type { ?double }
     * @default 0
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    centerZ?: double;
    /**
     * Distance from the user to the z=0 plane.
     * The axis and center of rotation are set based on the coordinate system,
     * which remains where it is when the component is moved.
     *
     * @type { ?double }
     * @default 0
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    perspective?: double;
    /**
     * The param of angle.
     *
     * @type { double | string }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    angle: double | string;
}
/**
 * The rotation parameters containing multi-axis angle information.
 *
 * @interface RotateAngleOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 23
 */
export declare interface RotateAngleOptions {
  /**
   * the angle of the x-axis direction.
   *
   * @type { ?(double | string) }
   * @default 0
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  angleX?: double | string;

  /**
   * the angle of the y-axis direction.
   *
   * @type { ?(double | string) }
   * @default 0
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  angleY?: double | string;

  /**
   * the angle of the z-axis direction.
   *
   * @type { ?(double | string) }
   * @default 0
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  angleZ?: double | string;

  /**
   * The param of center point of x.
   *
   * @type { ?(double | string) }
   * @default '50%'
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  centerX?: double | string;

  /**
   * The param of center point of y.
   *
   * @type { ?(double | string) }
   * @default '50%'
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  centerY?: double | string;

  /**
   * The param of center point of z.
   *
   * @type { ?double }
   * @default 0
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  centerZ?: double;

  /**
   * The param of camera distance, value range (-∞, ∞).
   * @type { ?double }
   * @default 0
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  perspective?: double;
}
/**
 * Defines the Edge object.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum TransitionEdge {
    /**
     * Top edge
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    TOP = 0,
    /**
     * Bottom edge of the window.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    BOTTOM = 1,
    /**
     * Start edge of the window, which is the left edge for left-to-right
     * scripts and the right edge for right-to-left scripts.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    START = 2,
    /**
     * End edge of the window, which is the right edge for left-to-right scripts
     * and the left edge for right-to-left scripts.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    END = 3
}
/**
 * Defines the option of asymmetric transition.
 *
 * @interface AsymmetricTransitionOption
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface AsymmetricTransitionOption {
    /**
     * TransitionEffect used for appearing
     *
     * @type { TransitionEffect }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    appear: TransitionEffect;
    /**
     * TransitionEffect used for disappearing
     *
     * @type { TransitionEffect }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    disappear: TransitionEffect;
}
/**
 * Defined the draw modifier of node. Provides draw callbacks for the associated Node.
 * Each DrawModifier instance can be set for only one component. Repeated setting is not allowed.
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 23
 */
export declare class DrawModifier {
    /**
     * drawBehind Method. Executed before drawing associated Node.
     *
     * @param { DrawContext } drawContext - The drawContext used to draw.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    drawBehind(drawContext: DrawContext): void;

    /**
     * drawContent Method. Executed when associated Node is drawing, the default drawContent method will be replaced
     * if this method is set.
     *
     * @param { DrawContext } drawContext - The drawContext used to draw.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    drawContent(drawContext: DrawContext): void;

    /**
     * drawFront Method. Executed after drawing associated Node and its children.
     * @param { DrawContext } drawContext - The drawContext used to draw.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
     drawFront(drawContext: DrawContext): void;

    /**
     * Draws content in the overlay layer after the associated Node and all its children have been drawn.
     *
     * Custom drawing consists of five layers: Behind, Content, Front, Foreground, and Overlay.
     * - The Foreground and Overlay layers are drawn after child nodes.
     * - The Overlay layer differs from Foreground in that it can draw outside the bounds of the component.
     * @param { DrawContext } drawContext - The drawContext used to draw
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    drawOverlay(drawContext: DrawContext): void;
    /**
     * Invalidate the component, which will cause a re-render of the component.
     * No overloading is allowed or needed.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    invalidate(): void;
}
/**
 * Defines the transition effect
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare class TransitionEffect {
    /**
     * Disables the transition effect
     *
     * @type { TransitionEffect }
     * @static
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    static get IDENTITY(): TransitionEffect;
    /**
     * Specifies a transition effect with transparency of 0, which is equivalent to TransitionEffect.opacity(0).
     *
     * @type { TransitionEffect }
     * @static
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    static get OPACITY(): TransitionEffect;
    /**
     * Defines a slide transition effect
     *
     * @type { TransitionEffect }
     * @static
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    static get SLIDE(): TransitionEffect;
    /**
     * Specify a transition effect where the element enters by shrinking first and then expanding as it slides in from the right,
     * and exits by shrinking first and then expanding as it slides out to the left, with a minimum scale ratio of 0.8.
     * It comes with default animation parameters, which can also be overridden.
     * The default animation duration is set to 600ms, and the specified animation curve is cubicBezierCurve(0.24, 0.0, 0.50, 1.0).
     *
     * @type { TransitionEffect }
     * @static
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    static get SLIDE_SWITCH(): TransitionEffect;
    /**
     * Creates a translate transition effect
     *
     * @param { TranslateOptions } options - translate options
     * @returns { TransitionEffect }
     * @static
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    static translate(options: TranslateOptions): TransitionEffect;
    /**
     * Creates a rotation transition effect
     *
     * @param { RotateOptions } options - rotate options
     * Set the rotation effect for component transitions when inserting and deleting.
     * The value represents the starting rotation point for the inserting animation and the ending rotation point for the deleting animation.
     * -x: Horizontal component of the rotational vector.
     * -y: Vertical component of the rotational vector.
     * -z: Vertical component of the rotational vector.
     * -centerX, centerY specify the rotation center point, with default values of "50%",
     * meaning that the default rotation center point is the center point of the component.
     * -The center point of (0, 0) represents the upper-left corner of the component.
     * -centerZ refers to the Z-axis anchor point. The default value of centerZ is 0.
     * -perspective indicates the visual distance. The perspective property does not support transition animation.
     * @returns { TransitionEffect }
     * @static
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    static rotate(options: RotateOptions): TransitionEffect;
    /**
     * Creates a scale transition effect
     *
     * @param { ScaleOptions } options - scale options
     * @returns { TransitionEffect }
     * @static
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    static scale(options: ScaleOptions): TransitionEffect;
    /**
     * Creates an opacity transition effect with alpha value
     *
     * @param { number } alpha - opacity alpha value, value range [0, 1].
     * Illegal values less than 0 are treated as 0, and illegal values greater than 1 are treated as 1.
     * @returns { TransitionEffect }
     * @static
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    static opacity(alpha: double): TransitionEffect;
    /**
     * Creates a move transition effect
     *
     * @param { TransitionEdge } edge - the edge that component will move to
     * @returns { TransitionEffect }
     * @static
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    static move(edge: TransitionEdge): TransitionEffect;
    /**
     * Creates an asymmetric transition effect
     *
     * @param { TransitionEffect } appear - the transition which will be attached when the component is appear
     * @param { TransitionEffect } disappear - the transition which will be attached when the component is disappear
     * @returns { TransitionEffect }
     * @static
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    static asymmetric(appear: TransitionEffect, disappear: TransitionEffect): TransitionEffect;
    /**
     * identity or slideSwitch TransitionEffect constructor
     *
     * @param { 'identity' | 'slideSwitch' } type - transition type
     * @param { undefined } effect - transition options
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    constructor(type: 'identity' | 'slideSwitch', effect: undefined);
    /**
     * opacity TransitionEffect constructor
     *
     * @param { 'opacity' } type - transition type
     * @param { number } effect - transition options
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    constructor(type: 'opacity', effect: double);
    /**
     * move TransitionEffect constructor
     *
     * @param { 'move' } type - transition type
     * @param { TransitionEdge } effect - transition options
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    constructor(type: 'move', effect: TransitionEdge);
    /**
     * translate TransitionEffect constructor
     *
     * @param { 'translate' } type - transition type
     * @param { TranslateOptions } effect - transition options
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    constructor(type: 'translate', effect: TranslateOptions);
    /**
     * rotate TransitionEffect constructor
     *
     * @param { 'rotate' } type - transition type
     * @param { RotateOptions } effect - transition options
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    constructor(type: 'rotate', effect: RotateOptions);
    /**
     * scale TransitionEffect constructor
     *
     * @param { 'scale' } type - transition type
     * @param { ScaleOptions } effect - transition options
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    constructor(type: 'scale', effect: ScaleOptions);
    /**
     * asymmetric TransitionEffect constructor
     *
     * @param { 'asymmetric' } type - transition type
     * @param { AsymmetricTransitionOption } effect - transition options
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    constructor(type: 'asymmetric', effect: AsymmetricTransitionOption);
    /**
     * Set the animation of current transition effect
     *
     * @param { AnimateParam } value - animation parameters
     * @returns { TransitionEffect }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    animation(value: AnimateParam): TransitionEffect;
    /**
     * Combines another transition effect
     *
     * @param { TransitionEffect } transitionEffect - transition effect which is be combined
     * @returns { TransitionEffect } combined transition effect
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    combine(transitionEffect: TransitionEffect): TransitionEffect;
}
/**
 * ItemDragInfo object description
 *
 * @interface ItemDragInfo
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface ItemDragInfo {
    /**
     * Obtains the X coordinate of the drag window, in vp.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    x: double;
    /**
     * Obtains the Y coordinate of the drag window, in vp.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    y: double;
}
/**
 * Enum of using the effects template mode.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum EffectType {
    /**
     * Define use the effects template defined by the parent effectComponent.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DEFAULT = 0,
    /**
     * Define use the effects template defined by the window.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    WINDOW_EFFECT = 1
}
/**
 * Defines the drag status before drag action.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum PreDragStatus {
    /**
     * Define the status for user prepare to start long press gesture.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    ACTION_DETECTING_STATUS = 0,
    /**
     * Define the status for user can start drag action.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    READY_TO_TRIGGER_DRAG_ACTION = 1,
    /**
     * Define the status for dragItem lift animation started.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    PREVIEW_LIFT_STARTED = 2,
    /**
     * Define the status for dragItem lift animation finished.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    PREVIEW_LIFT_FINISHED = 3,
    /**
     * Define the status for dragItem landing animation started.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    PREVIEW_LANDING_STARTED = 4,
    /**
     * Define the status for dragItem landing animation finished.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    PREVIEW_LANDING_FINISHED = 5,
    /**
     * Define the status for user cancel drag action.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    ACTION_CANCELED_BEFORE_DRAG = 6,
    /**
     * Define the status for user to sense the availability of drag in advance.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    PREPARING_FOR_DRAG_DETECTION = 7
}
/**
 * DragItemInfo object description
 *
 * @interface DragItemInfo
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface DragItemInfo {
    /**
     * Uses the pixelMap object for drawing.
     *
     * @type { ?PixelMap }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    pixelMap?: PixelMap;
    /**
     * Uses the custom builder for drawing, if pixelMap is set, this value is ignored.
     *
     * @type { ?CustomBuilder }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    builder?: CustomBuilder;
    /**
     * Sets the extra info for drag event.
     *
     * @type { ?string }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    extraInfo?: string;
}

/**
 * Define animation functions for immediate distribution.
 * This interface depends on the UI context and cannot be used when the UI context is unclear. It is recommended to use
 * {@link ohos.arkui.UIContext.UIContext#animateToImmediately} to explicitly specify the UI context.
 *
 * @param { AnimateParam } value - Set animation effect parameters.
 * @param { VoidCallback } processor - Specify the closure function that displays dynamic effects,
 *     and the system will automatically insert transition animations for state changes caused by the closure function.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 23
 */
export declare function animateToImmediately(value: AnimateParam, processor: VoidCallback): void;

/**
 * Defines the namespace of focus controller.
 *
 * @namespace focusControl
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare namespace focusControl {
    /**
     * Request focus to the specific component by param: 'id/key'.
     *
     * @param { string } value
     * @returns { boolean }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    function requestFocus(value: string): boolean;
}
/**
 * Import the PointerStyle type object for setCursor.
 *
 * @typedef { pointer.PointerStyle } PointerStyle
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type PointerStyle = pointer.PointerStyle;
/**
 * CursorControl
 *
 * @namespace cursorControl
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare namespace cursorControl {
    /**
     * Change the mouse cursor style by param: 'PointerStyle'.
     *
     * @param { PointerStyle } value - Cursor style.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    function setCursor(value: PointerStyle): void;
    /**
     * Restore the default mouse cursor style.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    function restoreDefault(): void;
}
/**
 * Defines the event target.
 *
 * @interface EventTarget
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface EventTarget {
    /**
     * Area information of the target element.
     *
     * @type { Area }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    area: Area;
    /**
     * Node id of current target.
     *
     * @type { ?string }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    id?: string;
}
/**
 * Defines the event source type.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum SourceType {
    /**
     * Unknown device type.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    Unknown = 0,
    /**
     * The mouse type.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    Mouse = 1,
    /**
     * The touch screen type.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    TouchScreen = 2,
    /**
     * The key type.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    KEY = 4,
    /**
     * The joystick type.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    JOYSTICK = 5
}
/**
 * Defines the event tool type.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum SourceTool {
    /**
     * Unknown input source.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    Unknown = 0,
    /**
     * The finger type.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    Finger = 1,
    /**
     * The pen type.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    Pen = 2,
    /**
     * The mouse type.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    MOUSE = 7,
    /**
     * The touchpad type.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    TOUCHPAD = 9,
    /**
     * The joystick type.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    JOYSTICK = 10
}
/**
 * Defines the Border Image Repeat Mode.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum RepeatMode {
    /**
     * The source image's slices are tiled. Tiles beyond the border box will be clipped.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    Repeat = 0,
    /**
     * The source image's slices are stretched to fill the border box.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    Stretch = 1,
    /**
     * The source image's slices are tiled to fill the border box. Tiles may be compressed when needed.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    Round = 2,
    /**
     * The source image's slices are tiled to fill the border box. Extra space will be distributed in between tiles.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    Space = 3
}
/**
 * enum Blur style
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum BlurStyle {
    /**
     * Thin material.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    Thin = 0,
    /**
     * Regular material.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    Regular = 1,
    /**
     * Thick material.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    Thick = 2,
    /**
     * Material that creates the minimum depth of field effect.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    BACKGROUND_THIN = 3,
    /**
     * Material that creates a medium shallow depth of field effect.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    BACKGROUND_REGULAR = 4,
    /**
     * Material that creates a high shallow depth of field effect.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    BACKGROUND_THICK = 5,
    /**
     * Material that creates the maximum depth of field effect.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    BACKGROUND_ULTRA_THICK = 6,
    /**
     * No blur.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    NONE = 7,
    /**
     * Component ultra-thin material.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    COMPONENT_ULTRA_THIN = 8,
    /**
     * Component thin material.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    COMPONENT_THIN = 9,
    /**
     * Component regular material.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    COMPONENT_REGULAR = 10,
    /**
     * Defines the thick component material.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    COMPONENT_THICK = 11,
    /**
     * Defines the ultra thick component material.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    COMPONENT_ULTRA_THICK = 12
}
/**
 * Enumerates the policies for activating the blur style.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum BlurStyleActivePolicy {
    /**
     * The component has the blur effect only when the window is focused.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    FOLLOWS_WINDOW_ACTIVE_STATE = 0,
    /**
     * The component always has the blur effect, regardless of whether the window is focused.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    ALWAYS_ACTIVE = 1,
    /**
     * The component does not have the blur effect, regardless of whether the window is focused.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    ALWAYS_INACTIVE = 2
}
/**
 * enum color mode
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum ThemeColorMode {
    /**
     * Defines the mode which is follow up with system.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    SYSTEM = 0,
    /**
     * Defines the light mode.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    LIGHT = 1,
    /**
     * Defines the dark mode.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DARK = 2
}

/**
 * Defines adaptive color
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum AdaptiveColor {
    /**
     * Adaptive color mode is not used.
     * The default color is used as the mask color. Using a mode other than **DEFAULT** can be more time-consuming.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DEFAULT = 0,
    /**
     * Adaptive color mode is used. The average color value of the color picking area is used as the mask color.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    AVERAGE = 1
}
/**
 * Defines modal transition type.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum ModalTransition {
    /**
     * Slide-up and slide-down animation for the modal.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DEFAULT = 0,
    /**
     * No transition animation for the modal.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    NONE = 1,
    /**
     * Opacity gradient animation for the modal.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    ALPHA = 2
}
/**
 * Defines the options of backgroundBlurStyle
 *
 * @extends BlurStyleOptions
 * @interface BackgroundBlurStyleOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface BackgroundBlurStyleOptions extends BlurStyleOptions {
    /**
     * Defines the policy for activating the blur style.
     *
     * @type { ?BlurStyleActivePolicy }
     * @default BlurStyleActivePolicy.ALWAYS_ACTIVE
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    policy?: BlurStyleActivePolicy;
    /**
     * Color of the background effect when the window is not focused.
     *
     * @type { ?ResourceColor }
     * @default Color.Transparent
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    inactiveColor?: ResourceColor;
}
/**
 * Defines the options of ForegroundBlurStyle
 *
 * @extends BlurStyleOptions
 * @interface ForegroundBlurStyleOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface ForegroundBlurStyleOptions extends BlurStyleOptions {
}
/**
 * Defines the options of blur
 *
 * @interface BlurOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface BlurOptions {
    /**
     * Fuzzy gray scale parameter. Undefined value means no grayscale.
     * @type { [double, double] | undefined }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    grayscale: [
        double,
        double
    ] | undefined;
}
/**
 * Defines the SystemAdaptiveOptions interface
 *
 * @interface SystemAdaptiveOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface SystemAdaptiveOptions {
    /**
     * Whether to disable system adaptive.
     *
     * @type { ?boolean }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    disableSystemAdaptation?: boolean;
}
/**
 * Defines the options of blurStyle
 *
 * @interface BlurStyleOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface BlurStyleOptions {
    /**
     * Color mode used for the foreground blur.
     * <br>Default value: **ThemeColorMode.SYSTEM**.
     *
     * @type { ?ThemeColorMode }
     * @default ThemeColorMode.SYSTEM
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    colorMode?: ThemeColorMode;
    /**
     * Adaptive color mode.
     * <br>Default value: **AdaptiveColor.DEFAULT**.
     *
     * @type { ?AdaptiveColor }
     * @default AdaptiveColor.DEFAULT
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    adaptiveColor?: AdaptiveColor;
    /**
     * Foreground blur scale.
     * <br>Default value: **1.0**.
     * <br>Value range: [0.0, 1.0].
     *
     * @type { ?double }
     * @default 1.0
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    scale?: double;
    /**
     * Defines the options of blur
     *
     * @type { ?BlurOptions }
     * @default { grayScale: [0,0] }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    blurOptions?: BlurOptions;
}
/**
 * Defines the options of BackgroundEffect
 *
 * @interface BackgroundEffectOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface BackgroundEffectOptions {
    /**
     * Blur radius. Undefined value means 0.
     * Value range: [0, +∞).
     * Default value: **0**.
     *
     * @type { double | undefined }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    radius: double | undefined;
    /**
     * Saturation.
     * Value range: [0, +∞).
     * Recommended value range: [0, 50].
     *
     * @type { ?double }
     * @default 1
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    saturation?: double;
    /**
     * Brightness.
     * <br>Value range: [0, +∞).
     * <br>Default value: **1** Recommended value range: [0, 2].
     *
     * @type { ?double }
     * @default 1
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    brightness?: double;
    /**
     * Color.
     *
     * @type { ?ResourceColor }
     * @default Color.Transparent
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    color?: ResourceColor;
    /**
     * Define the adaptiveColor of BackgroundEffect.
     *
     * @type { ?AdaptiveColor }
     * @default AdaptiveColor.DEFAULT
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    adaptiveColor?: AdaptiveColor;
    /**
    * Define the blurOptions of BackgroundEffect.
    *
    * @type { ?BlurOptions }
    * @default { grayScale: [0,0] }
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    blurOptions?: BlurOptions;
    /**
     * Defines the policy for activating the blur style.
     *
     * @type { ?BlurStyleActivePolicy }
     * @default BlurStyleActivePolicy.ALWAYS_ACTIVE
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    policy?: BlurStyleActivePolicy;
    /**
     * Color of the background effect when the window is not focused.
     *
     * @type { ?ResourceColor }
     * @default Color.Transparent
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    inactiveColor?: ResourceColor;
}
/**
 * Defines the options of ForegroundEffect
 *
 * @interface ForegroundEffectOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface ForegroundEffectOptions {
    /**
     * Define the radius size of ForegroundEffect.The range of this value is [0, ∞). Undefined means 0.
     *
     * @type { double | undefined }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    radius: double | undefined;
}
/**
 * Provide an interface for the text style of picker
 *
 * @interface PickerTextStyle
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface PickerTextStyle {
    /**
     * Font color.
     *
     * @type { ?ResourceColor }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    color?: ResourceColor;
    /**
     * Text style.
     *
     * @type { ?Font }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    font?: Font;
}
/**
 * Provide an interface for the button style of picker
 *
 * @interface PickerDialogButtonStyle
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface PickerDialogButtonStyle {
    /**
     * Describes the button style.
     *
     * @type { ?ButtonType }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    type?: ButtonType;
    /**
     * Describes the button style.
     *
     * @type { ?ButtonStyleMode }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    style?: ButtonStyleMode;
    /**
     * Describes the button role.
     *
     * @type { ?ButtonRole }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    role?: ButtonRole;
    /**
     * Describes the button text size.
     *
     * @type { ?Length }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    fontSize?: Length;
    /**
     * Describes the button text color.
     *
     * @type { ?ResourceColor }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    fontColor?: ResourceColor;
    /**
     * Describes the button font weight.
     *
     * @type { ?(FontWeight | int | string) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    fontWeight?: FontWeight | int | string;
    /**
     * Describes the button font style.
     *
     * @type { ?FontStyle }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    fontStyle?: FontStyle;
    /**
     * Describes the button font family.
     *
     * @type { ?(Resource | string) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    fontFamily?: Resource | string;
    /**
     * Describes the button background color.
     *
     * @type { ?ResourceColor }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    backgroundColor?: ResourceColor;
    /**
     * Describes the button border radius.
     *
     * @type { ?(Length | BorderRadiuses) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    borderRadius?: Length | BorderRadiuses;
    /**
     * Define whether the button default to responding to the Enter key
     *
     * @type { ?boolean }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    primary?: boolean;
}
/**
 * Define the type of shadow
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum ShadowType {
    /**
     * Define a color type of shadow
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    COLOR = 0,
    /**
     * Blur.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    BLUR = 1
}
/**
 * Define the options of shadow
 *
 * @interface ShadowOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface ShadowOptions {
    /**
     * Blur radius of the shadow.
     * Default value: 0px.
     *
     * @type { double | Resource | undefined }
     *     undefined means setting to default value.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    radius: double | Resource | undefined;
    /**
     * Shadow type.
     * <br>Default value: **COLOR**.
     *
     * @type { ?ShadowType }
     * @default ShadowType.COLOR
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    type?: ShadowType;
    /**
     * Color of the shadow. Default value: **Black**
     *
     * @type { ?(Color | string | Resource| ColoringStrategy) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    color?: Color | string | Resource | ColoringStrategy;
    /**
     * Offset of the shadow along the x-axis. Unit is px. Default value is 0.
     *
     * @type { ?(double | Resource) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    offsetX?: double | Resource;
    /**
     * Offset of the shadow along the y-axis. Unit is px. Default value is 0.
     *
     * @type { ?(double | Resource) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    offsetY?: double | Resource;
    /**
     * Whether to fill the inside of the component with shadow. **true**: Fill
     * the inside of the component with shadow.
     * <br>**false**: Do not fill the inside of the component with shadow.
     * <br>The default value is **false**.
     * <br>**NOTE**<br>This attribute does not take effect in textShadow.
     *
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    fill?: boolean;
}
/**
 * enum Shadow style
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 23
 */
export declare enum ShadowStyle {
    /**
     * Defines the super small default shadow style.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    OUTER_DEFAULT_XS = 0,
    /**
     * Defines the small default shadow style.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    OUTER_DEFAULT_SM = 1,
    /**
     * Defines the medium default shadow style.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    OUTER_DEFAULT_MD = 2,
    /**
     * Defines the large default shadow style.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    OUTER_DEFAULT_LG = 3,
    /**
     * Defines the small floating shadow style.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    OUTER_FLOATING_SM = 4,
    /**
     * Defines the medium floating shadow style.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    OUTER_FLOATING_MD = 5
}
/**
 * Defines the options of Shadow.
 *
 * @interface MultiShadowOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface MultiShadowOptions {
    /**
     * Shadow blur radius.
     * Unit: vp.
     * <p>**NOTE**:
     * <br>A value less than or equal to 0 is handled as the default value.
     * </p>
     *
     * @type { ?(double | Resource) }
     * @default 20
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    radius?: double | Resource;
    /**
     * Offset on the x-axis.
     * Unit: vp.
     *
     * @type { ?(double | Resource) }
     * @default 5
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    offsetX?: double | Resource;
    /**
     * Offset on the y-axis.
     * Unit: vp.
     *
     * @type { ?(double | Resource) }
     * @default 5
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    offsetY?: double | Resource;
}
/**
 * The types of expanded safe areas.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum SafeAreaType {
    /**
     * Default non-safe area of the system, including the status bar and navigation bar.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    SYSTEM = 0,
    /**
     * Non-safe area of the device like Notch or punch hole.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    CUTOUT = 1,
    /**
     * Soft keyboard area.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    KEYBOARD = 2
}
/**
 * Enumerates the safe area edges.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum SafeAreaEdge {
    /**
     * Top edge.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    TOP = 0,
    /**
     * Bottom edge.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    BOTTOM = 1,
    /**
     * Start edge.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    START = 2,
    /**
     * End edge.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    END = 3
}
/**
 * Describe the types for expanding the safe area in layout.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum LayoutSafeAreaType {
    /**
     * Default non-safe area of the system, including the status bar and navigation bar.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    SYSTEM = 0
}
/**
 *  Define the edges for expanding the safe area in layout.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum LayoutSafeAreaEdge {
    /**
     * Top edge.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    TOP = 0,
    /**
     * Bottom edge.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    BOTTOM = 1,
    /**
     * Start edge of the safe area.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    START = 2,
    /**
     * End edge of the safe area.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    END = 3,
    /**
     * Vertical edge of the safe area.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    VERTICAL = 4,
    /**
     * Horizontal edge of the safe area.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    HORIZONTAL = 5,
    /**
     * All edges of the safe area.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    ALL = 6
}
/**
 * Defines sheet size type.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum SheetSize {
    /**
     * The sheet height is half of the screen height.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    MEDIUM = 0,
    /**
     * The sheet height is almost the screen height.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    LARGE = 1,
    /**
     * The sheet height automatically adapts to the content.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    FIT_CONTENT = 2
}
/**
 * The modifier key state query function block.
 *
 * @typedef { function } ModifierKeyStateGetter
 * @param { Array<string> } keys - Indicate the modifier keys to query.
 * @returns { boolean } - the query result
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type ModifierKeyStateGetter = (keys: Array<string>) => boolean;
/**
 * Defines the base event.
 *
 * @interface BaseEvent
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface BaseEvent {
     /**
     * Display area of the element that triggers the gesture event.
     *
     * @type { EventTarget }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    target: EventTarget;
    /**
     * Timestamp of the event.
     *
     * @type { long }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    timestamp: long;
    /**
     * Event input device.
     *
     * @type { SourceType }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    source: SourceType;
    /**
     * the Horizontal axis coordinate.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    axisHorizontal?: double;
    /**
     * the Vertical axis coordinate.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    axisVertical?: double;
    /**
     * Press pressure.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    pressure: double;
    /**
     * Angle between the projection of the stylus on the device plane and the x-axis.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    tiltX: double;
    /**
     * Angle between the projection of the stylus on the device plane and the y-axis.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    tiltY: double;
    /**
     * Indicates the angle at which the stylus rotates around the Z-axis.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    rollAngle?: double;
    /**
     * Event input source.
     *
     * @type { SourceTool }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    sourceTool: SourceTool;
    /**
     * Query the modifier key press state, support 'ctrl'|'alt'|'shift'
     *
     * @type { ?ModifierKeyStateGetter }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getModifierKeyState?: ModifierKeyStateGetter;
    /**
     * Indicates the ID of the input device that triggers the current event.
     *
     * @type { ?int } [deviceId] The ID of the input device that triggers the current event
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    deviceId?: int;
    /**
     * Indicates the screen ID on which the event occurred.
     *
     * @type { ?int } [targetDisplayId] The screen ID on which the event occurred.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    targetDisplayId?: int;
    /**
     * Indicates the Pinch axis coordinate.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    axisPinch?: double;
}
/**
 * Border image option
 *
 * @interface BorderImageOption
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface BorderImageOption {
    /**
     * Slice width of the upper left corner, upper right corner, lower left corner,
     * and lower right corner of the border image.
     *
     * @type { ?(Length | EdgeWidths | LocalizedEdgeWidths) }
     * @default 0
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    slice?: Length | EdgeWidths | LocalizedEdgeWidths;
    /**
     * Repeat mode of the source image's slices on the border.
     *
     * @type { ?RepeatMode }
     * @default RepeatMode.Stretch
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    repeat?: RepeatMode;
    /**
     * Border image source
     *
     * @type { ?(string | Resource | LinearGradientOptions) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    source?: string | Resource | LinearGradientOptions;
    /**
     * Width of the border image.
     *
     * @type { ?(Length | EdgeWidths | LocalizedEdgeWidths) }
     * @default 0
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    width?: Length | EdgeWidths | LocalizedEdgeWidths;
    /**
     * Amount by which the border image is extended beyond the border box.
     *
     * @type { ?(Length | EdgeWidths | LocalizedEdgeWidths) }
     * @default 0
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    outset?: Length | EdgeWidths | LocalizedEdgeWidths;
    /**
     * Whether to fill the center of the border image.
     * true: Fill the center of the border image.
     * false: Do not fill the center of the border image.
     *
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    fill?: boolean;
}
/**
 * Defines the policy of Layout
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare class LayoutPolicy {
    /**
     * The component fills its parent which means its size is as large as its parent.
     *
     * @type { LayoutPolicy }
     * @readonly
     * @static
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    static readonly matchParent: LayoutPolicy;

    /**
     * The component fills its content which means its size is as large as its children but it is constained by its
     *     parent.
     *
     * @type { LayoutPolicy }
     * @readonly
     * @static
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    static readonly wrapContent: LayoutPolicy;

    /**
     * The component fills its content which means its size is as large as its children.
     *
     * @type { LayoutPolicy }
     * @readonly
     * @static
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    static readonly fixAtIdealSize: LayoutPolicy;
}
/**
 * The tap action triggers this method invocation.
 *
 * @extends BaseEvent
 * @interface ClickEvent
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface ClickEvent extends BaseEvent {
    /**
     * X coordinate of the click relative to the upper left corner of the application screen.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    displayX: double;
    /**
     * Y coordinate of the click relative to the upper left corner of the application screen.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    displayY: double;
    /**
     * X coordinate of the click relative to the upper left corner of the application window.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    windowX: double;
    /**
     * Y coordinate of the click relative to the upper left corner of the application window.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    windowY: double;
    /**
     * X coordinate of the click point relative to the left edge of the clicked element.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    x: double;
    /**
     * Y coordinate of the click point relative to the left edge of the clicked element.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    y: double;
    /**
     * Whether the event is triggered by a left-hand or right-hand tap.
     *
     * @type { InteractionHand }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    hand?: InteractionHand;
    /**
     * Prevent the default function.
     *
     * @throws { BusinessError } 100017 - Component does not support prevent function.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    preventDefault(): void;
    /**
     * X coordinate of the point relative to the global display.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    globalDisplayX?: double;
    /**
     * Y coordinate of the point relative to the global display.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    globalDisplayY?: double;
}
/**
 * The hover action triggers this method invocation.
 *
 * @extends BaseEvent
 * @interface HoverEvent
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface HoverEvent extends BaseEvent {
    /**
     * X coordinate of the hover point relative to the left edge of the hover element.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    x?: double;
    /**
     * Y coordinate of the hover point relative to the upper edge of the hover element.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    y?: double;
    /**
     * X coordinate of the hover point relative to the left edge of the current window.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    windowX?: double;
    /**
     * Y coordinate of the hover point relative to the upper edge of the current window.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    windowY?: double;
    /**
     * X coordinate of the hover point relative to the left edge of the device screen.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    displayX?: double;
    /**
     * Y coordinate of the hover point relative to the upper edge of the device screen.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    displayY?: double;
    /**
     * The blocking hover event pops up.
     *
     * @type { function }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    stopPropagation(): void;
    /**
     * X coordinate of the point relative to the global display.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    globalDisplayX?: double;
    /**
     * Y coordinate of the point relative to the global display.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    globalDisplayY?: double;
}
/**
 * The mouse click action triggers this method invocation.
 *
 * @extends BaseEvent
 * @interface MouseEvent
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface MouseEvent extends BaseEvent {
    /**
     * Mouse button of the click event.
     *
     * @type { MouseButton }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    button: MouseButton;
    /**
     * Mouse action of the click event.
     *
     * @type { MouseAction }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    action: MouseAction;
    /**
     * X coordinate of the mouse pointer relative to the upper left corner of the application screen.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    displayX: double;
    /**
     * Y coordinate of the mouse pointer relative to the upper left corner of the application screen.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    displayY: double;
    /**
     * X coordinate of the mouse pointer relative to the upper left corner of the application window.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    windowX: double;
    /**
     * Y coordinate of the mouse pointer relative to the upper left corner of the application window.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    windowY: double;
    /**
     * X coordinate of the mouse pointer relative to the upper left corner of the component being clicked.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    x: double;
    /**
     * Y coordinate of the mouse pointer relative to the upper left corner of the component being clicked.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    y: double;
    /**
     * Stops the event from bubbling upwards or downwards.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    stopPropagation(): void;
    // instructive change start
    getHistoricalPoints(): Array<MouseHistoricalPoint> | undefined;
    // instructive change end
    /**
     * X axis offset relative to the previous reported mouse pointer position. When the mouse pointer is at
     * the edge of the screen, the value may be less than the difference of the X coordinate reported twice.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    rawDeltaX?: double;
    /**
     * Y axis offset relative to the previous reported mouse pointer position. When the mouse pointer is at
     * the edge of the screen, the value may be less than the difference of the Y coordinate reported twice.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    rawDeltaY?: double;
    /**
     * Array of all mouse buttons that are currently pressed.
     *
     * @type { ?MouseButton[] }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    pressedButtons?: MouseButton[];
    /**
     * X coordinate of the point relative to the global display.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    globalDisplayX?: double;

    /**
     * Y coordinate of the point relative to the global display.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    globalDisplayY?: double;
    /**
     * The unique handle for the event processing session. This handle must be used for any further operations on the
     * event. The system ensures that for a given finger, only one event with this handle can be active at a time.
     *
     * @type { ?int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    eventHandleId?: int;
}
/**
 * The accessibility hover action triggers this method invocation.
 *
 * @extends BaseEvent
 * @typedef AccessibilityHoverEvent
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface AccessibilityHoverEvent extends BaseEvent {
    /**
     * Type of the accessibility hover event.
     *
     * @type { AccessibilityHoverType }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    type: AccessibilityHoverType;
    /**
     * X coordinate of the accessibility hover point relative to the left edge of the event hit element.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    x: double;
    /**
     * Y coordinate of the accessibility hover point relative to the upper edge of the event hit element.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    y: double;
    /**
     * X coordinate of the accessibility hover point relative to the left edge of the device screen.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    displayX: double;
    /**
     * Y coordinate of the accessibility hover point relative to the upper edge of the device screen.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    displayY: double;
    /**
     * X coordinate of the accessibility hover point relative to the left edge of the current window.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    windowX: double;
    /**
     * Y coordinate of the accessibility hover point relative to the upper edge of the current window.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    windowY: double;
    /**
     * X coordinate of the point relative to the global display.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    globalDisplayX?: double;

    /**
     * Y coordinate of the point relative to the global display.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    globalDisplayY?: double;
}
// instructive change start
export interface MouseHistoricalPoint {
    x: double;
    y: double;
    displayX: double;
    displayY: double;
    windowX: double;
    windowY: double;
    globalDisplayX: double;
    globalDisplayY: double;
    timestamp: long;
}
// instructive change end
/**
 * Type of the touch event.
 *
 * @interface TouchObject
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface TouchObject {
    /**
     * Type of the touch event.
     *
     * @type { TouchType }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    type: TouchType;
    /**
     * Unique identifier of a finger.
     *
     * @type { int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    id: int;
    /**
     * X coordinate of the touch point relative to the upper left corner of the application screen.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    displayX: double;
    /**
     * Y coordinate of the touch point relative to the upper left corner of the application screen.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    displayY: double;
    /**
     * X coordinate of the touch point relative to the upper left corner of the application window.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    windowX: double;
    /**
     * Y coordinate of the touch point relative to the upper left corner of the application window.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    windowY: double;
    /**
     * X coordinate of the touch point relative to the upper left corner of the event responding component.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    x: double;
    /**
     * Y coordinate of the touch point relative to the upper left corner of the event responding component.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    y: double;
    /**
     * Whether the event is triggered by a left-hand or right-hand tap.
     *
     * @type { InteractionHand }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    hand?: InteractionHand;
    /**
     * Time when the finger is pressed.
     *
     * @type { ?long }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    pressedTime?: long;
    /**
   * Pressure value of the finger press.
   *
   * @type { ?double }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
    pressure?: double;
    /**
     * Width of the area pressed by the finger.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    width?: double;
    /**
     * Height of the area pressed by the finger.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    height?: double;
    /**
     * X coordinate of the point relative to the global display.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    globalDisplayX?: double;

    /**
     * Y coordinate of the point relative to the global display.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    globalDisplayY?: double;
}
/**
 * TouchObject getHistoricalPoints Function Parameters
 *
 * @interface HistoricalPoint
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface HistoricalPoint {
    /**
     * The base touchObject information of historicalPoint
     *
     * @type { TouchObject }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    touchObject: TouchObject;
    /**
     * Contact area between the finger pad and the screen.
     *
     * @type { int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    size: int;
    /**
     * Pressure of the touch event.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    force: double;
    /**
     * Timestamp of the touch event.
     *
     * @type { long }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    timestamp: long;
}
/**
 * Touch Action Function Parameters
 *
 * @extends BaseEvent
 * @interface TouchEvent
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface TouchEvent extends BaseEvent {
    /**
     * Type of the touch event.
     *
     * @type { TouchType }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    type: TouchType;
    /**
     * All finger information.
     *
     * @type { TouchObject[] }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    touches: TouchObject[];
    /**
     * Finger information changed.
     *
     * @type { TouchObject[] }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    changedTouches: TouchObject[];
    /**
     * Stops the event from bubbling upwards or downwards.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    stopPropagation(): void;
    /**
     * Obtains all historical points of the current frame.
     *
     * @returns { Array<HistoricalPoint> | undefined } - return all historical points. Undefined will be returned
     *     if the internal runtime environment is broken.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getHistoricalPoints(): Array<HistoricalPoint> | undefined;
    /**
     * Blocks the default event.
     *
     * @throws { BusinessError } 100017 - Component does not support prevent function.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    preventDefault(): void;
    /**
     * The unique handle for the event processing session. This handle must be used for any further operations on the
     * event. The system ensures that for a given finger, only one event with this handle can be active at a time.
     *
     * @type { ?int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    eventHandleId?: int;
}
/**
 * The axis event triggers this method invocation.
 *
 * @extends BaseEvent
 * @interface AxisEvent
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface AxisEvent extends BaseEvent {
    /**
     * Axis action of the axis event.
     *
     * @type { AxisAction }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    action: AxisAction;
    /**
     * X coordinate of the mouse cursor relative to the left edge of the device screen.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    displayX: double;
    /**
     * Y coordinate of the mouse cursor relative to the upper edge of the device screen.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    displayY: double;
    /**
     * X coordinate of the mouse cursor relative to the left edge of the current window.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    windowX: double;
    /**
     * Y coordinate of the mouse cursor relative to the upper edge of the current window.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    windowY: double;
    /**
     * X coordinate of the mouse cursor relative to the left edge of the axis event hit element.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    x: double;
    /**
     * Y coordinate of the mouse cursor relative to the upper edge of the axis event hit element.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    y: double;
    /**
     * Scroll step configuration which is only mouse wheel has.
     *  *
     * @type { ?int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    scrollStep?: int;
    /**
     * The unique handle for the event processing session. This handle must be used for any further operations on the
     * event. The system ensures that for a given finger, only one event with this handle can be active at a time.
     *
     * @type { ?int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    eventHandleId?: int;
    /**
     * Active event bubbling.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    propagation(): void;
    /**
     * Obtains the value of the horizontal scroll axis for this axis event.
     *
     * @returns { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getHorizontalAxisValue(): double;
    /**
     * Obtains the value of the vertical scroll axis for this axis event.
     *
     * @returns { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getVerticalAxisValue(): double;
    /**
     * Obtains the value of the pinch axis for this axis event.
     *
     * @returns { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getPinchAxisScaleValue(): double;
    /**
     * Checks whether this event contains a specified axis type.
     *
     * @param { AxisType } axisType - Indicates the axis type.
     * @returns { boolean }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    hasAxis(axisType: AxisType): boolean;
    /**
     * X coordinate of the point relative to the global display.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    globalDisplayX?: double;

    /**
     * Y coordinate of the point relative to the global display.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    globalDisplayY?: double;
}
/**
 * Defines the callback type used in onSizeChange.
 *
 * @typedef { function } SizeChangeCallback
 * @param { SizeOptions } oldValue - the width and height of the component before the change.
 * @param { SizeOptions } newValue - the width and height of the component after the change.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type SizeChangeCallback = (oldValue: SizeOptions, newValue: SizeOptions) => void;
/**
 * Defines the callback type used in onGestureRecognizerJudgeBegin.
 *
 * @typedef { function } GestureRecognizerJudgeBeginCallback
 * @param { BaseGestureEvent } event - the event information
 * @param { GestureRecognizer } current - the current gesture recognizer of the component
 * @param { Array<GestureRecognizer> } recognizers - the gesture recognizers of the component on the response chain
 * @param { Array<TouchRecognizer> } [touchRecognizers] - the touch recognizers of the component on the response chain
 * @returns { GestureJudgeResult } the gesture judge result
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 24
 */
export type GestureRecognizerJudgeBeginCallback = (event: BaseGestureEvent, current: GestureRecognizer, recognizers: Array<GestureRecognizer>, touchRecognizers?: Array<TouchRecognizer>) => GestureJudgeResult;
/**
 * Defines the callback type used in shouldBuiltInRecognizerParallelWith.
 *
 * @typedef { function } ShouldBuiltInRecognizerParallelWithCallback
 * @param { GestureRecognizer } current - the current gesture recognizer of the component
 * @param { Array<GestureRecognizer> } others - the gesture recognizers of the component on the response chain
 * @returns { GestureRecognizer } gesture recognizer of the component
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type ShouldBuiltInRecognizerParallelWithCallback = (current: GestureRecognizer, others: Array<GestureRecognizer>) => GestureRecognizer;
/**
 * Defines the finish callback type used in transition.
 *
 * @typedef { function } TransitionFinishCallback
 * @param { boolean } transitionIn - a boolean value indicates whether it is the callback of
 *     transitionIn or transitionOut.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type TransitionFinishCallback = (transitionIn: boolean) => void;
/**
 * Defines the callback type used in onTouchTestDone.
 * When the user touch down, the system performs hit test process to collect all gesture recognizers
 * based on the press location, when the collection is completed, and before gesture begin to be recognizing,
 * the callback is triggered, you can get all recognizer's information from this callback.
 *
 * @typedef { function } TouchTestDoneCallback
 * @param { BaseGestureEvent } event - the event information, basicly is the touch down information
 * @param { Array<GestureRecognizer> } recognizers - the gesture recognizers of the component on the response chain
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type TouchTestDoneCallback = (event: BaseGestureEvent, recognizers: Array<GestureRecognizer>) => void;
/**
 * Defines the callback type used in onGestureCollectIntercept.
 *
 * @typedef { function } GestureCollectInterceptCallback
 * @param { Array<GestureRecognizer> } recognizers - the gesture recognizers of the component on the response chain.
 * @param { Array<TouchRecognizer> } [touchRecognizers] - the touch recognizers of the component on the response chain.
 * @returns { GestureCollectIntervention } the gesture intervention.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 26.0.0
 */
export type GestureCollectInterceptCallback = (recognizers: Array<GestureRecognizer>,
    touchRecognizers?: Array<TouchRecognizer>) => GestureCollectIntervention;
/**
 * Defines the callback type used in onNeedSoftkeyboard.
 * Called when component is focused, the return value indicates whether keyboard is needed.
 *
 * @typedef { function } OnNeedSoftkeyboardCallback
 * @returns { boolean } True means keyboard is needed, false means keyboard is not needed.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 24
 */
export type OnNeedSoftkeyboardCallback = () => boolean;
/**
 * Defines the PixelMap type object for ui component.
 *
 * @typedef { image.PixelMap } PixelMap
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type PixelMap = image.PixelMap;


/**
 * pixelmap object with release function.
 *
 * @interface PixelMapMock
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @systemapi
 * @since 23
 */
declare interface PixelMapMock {
  /**
   * release function.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @systemapi
   * @since 23
   */
  release(): void;
}

/**
 * Enum for Drag Behavior.
 *
 * <strong>NOTE</strong>:<br>
 * DragBehavior serves to inform you about the intended method of data handling,
 * whether it's a copy or a move, but it does not actually dictate the real processing of the data.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum DragBehavior {
    /**
     * If drag use copy event, then set DragBehavior.COPY.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    COPY = 0,
    /**
     * If drag use move event, then set DragBehavior.MOVE.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    MOVE = 1
}
/**
 * Import the UnifiedData type object for ui component.
 *
 * @typedef { unifiedDataChannel.UnifiedData } UnifiedData
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type UnifiedData = unifiedDataChannel.UnifiedData;
/**
 * Import the Summary type object for ui component.
 *
 * @typedef { unifiedDataChannel.Summary } Summary
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type Summary = unifiedDataChannel.Summary;
/**
 * Import the UniformDataType type object for ui component.
 *
 * @typedef { uniformTypeDescriptor.UniformDataType } UniformDataType
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type UniformDataType = uniformTypeDescriptor.UniformDataType;
/**
 * Import the GetDataParams type object for ui component.
 *
 * @typedef { unifiedDataChannel.GetDataParams } GetDataParams
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type DataSyncOptions = unifiedDataChannel.GetDataParams;
/**
 * Import the DataLoadParams type object for ui component.
 *
 * @typedef { unifiedDataChannel.DataLoadParams } DataLoadParams
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 24
 */
export type DataLoadParams = unifiedDataChannel.DataLoadParams;
/**
 * The type for SpringLoadingContext, see the detailed description in dragController.
 *
 * @typedef { dragController.SpringLoadingContext } SpringLoadingContext
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 24
 */
export type SpringLoadingContext = dragController.SpringLoadingContext;
/**
 * The type for DragSpringLoadingConfiguration, see the detailed description in dragController.
 *
 * @typedef { dragController.DragSpringLoadingConfiguration } DragSpringLoadingConfiguration
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 24
 */
export type DragSpringLoadingConfiguration = dragController.DragSpringLoadingConfiguration;
/**
 * Enum for Drag Result.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum DragResult {
    /**
     * If the drag is not finished and the result is not set by receiver, return DragResult.UNKNOWN.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    UNKNOWN = -1,
    /**
     * If the drag is successful, return DragResult.DRAG_SUCCESSFUL.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DRAG_SUCCESSFUL = 0,
    /**
     * If drag fail, return DragResult.DRAG_FAILED.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DRAG_FAILED = 1,
    /**
     * If drag action cancel, return DragResult.DRAG_CANCELED.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DRAG_CANCELED = 2,
    /**
     * If node allow drop in, return DragResult.DROP_ENABLED.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DROP_ENABLED = 3,
    /**
     * If node don't allow drop in, return DragResult.DROP_DISABLED.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DROP_DISABLED = 4
}
/**
 * Enum for BlendMode.
 * Blend modes for compositing current component
 * with overlapping content. Use overlapping content
 * as dst, current component as src.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum BlendMode {
    /**
     * The top image is superimposed on the bottom image without any blending.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    NONE = 0,
    /**
     * The target pixels covered by the source pixels are erased by being turned to completely transparent.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    CLEAR = 1,
    /**
     * r = s: Only the source pixels are displayed.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    SRC = 2,
    /**
     * r = d
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DST = 3,
    /**
     * r = s + (1 - sa) * d: The source pixels are blended based on opacity and cover the target pixels.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    SRC_OVER = 4,
    /**
     * r = d + (1 - da) * s: The target pixels are blended based on opacity and cover on the source pixels.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DST_OVER = 5,
    /**
     * r = s * da: Only the part of the source pixels that overlap with the target pixels is displayed.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    SRC_IN = 6,
    /**
     * r = d * sa: Only the part of the target pixels that overlap with the source pixels is displayed.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DST_IN = 7,
    /**
     * r = s * (1 - da)
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    SRC_OUT = 8,
    /**
     * r = d * (1 - sa), retains the parts of the destination pixels that do not overlap with the source.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DST_OUT = 9,
    /**
     * r = s * da + d * (1 - sa): The part of the source pixels that overlap with the target pixels is displayed
     * and the part of the target pixels that do not overlap with the source pixels are displayed.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    SRC_ATOP = 10,
    /**
     * r = d * sa + s * (1 - da): The part of the target pixels that overlap with the source pixels
     * and the part of the source pixels that do not overlap with the target pixels are displayed.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DST_ATOP = 11,
    /**
     * r = s * (1 - da) + d * (1 - sa)
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    XOR = 12,
    /**
     * r = min(s + d, 1):
     * New pixels resulting from adding the source pixels to the target pixels are displayed.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    PLUS = 13,
    /**
     * r = s * d
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    MODULATE = 14,
    /**
     * r = s + d - s * d
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    SCREEN = 15,
    /**
     * multiply or screen, depending on destination
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    OVERLAY = 16,
    /**
     * rc = s + d - max(s * da, d * sa), ra = kSrcOver
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DARKEN = 17,
    /**
     * rc = s + d - min(s * da, d * sa), ra = kSrcOver
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    LIGHTEN = 18,
    /**
     * brighten destination to reflect source
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    COLOR_DODGE = 19,
    /**
     * darken destination to reflect source
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    COLOR_BURN = 20,
    /**
     * multiply or screen, depending on source
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    HARD_LIGHT = 21,
    /**
     * The LIGHTEN or DARKEN mode is used, depending on the source pixels.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    SOFT_LIGHT = 22,
    /**
     * rc = s + d - 2 * (min(s * da, d * sa)), ra = kSrcOver: The final pixel is the result of subtracting
     * the darker of the two pixels (source and target) from the lighter one.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DIFFERENCE = 23,
    /**
     * rc = s + d - two(s * d), ra = kSrcOver
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    EXCLUSION = 24,
    /**
     * r = s * (1 - da) + d * (1 - sa) + s * d:
     * The final pixel is the result of multiplying the source pixel by the target pixel.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    MULTIPLY = 25,
    /**
     * hue of source with saturation and luminosity of destination
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    HUE = 26,
    /**
     * saturation of source with hue and luminosity of destination
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    SATURATION = 27,
    /**
     * hue and saturation of source with luminosity of destination
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    COLOR = 28,
    /**
     * luminosity of source with hue and saturation of destination
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    LUMINOSITY = 29
}
/**
 * Enum for BlendApplyType.
 * Indicate how to apply specified blend mode to
 * the view's content.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum BlendApplyType {
    /**
     * The content of the view is blended in sequence on the target image.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    FAST = 0,
    /**
     * The content of the component and its child components are drawn on the
     * offscreen canvas, and then blended with the existing content on the canvas.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    OFFSCREEN = 1,
    /**
    * The content of the component and its child components are drawn on the
    * offscreen canvas, and then blended with the existing content on the canvas.
    * The offscreen canvas will copy background to initialize itself when created.
    * 
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @systemapi
    * @since 23
    */
    OFFSCREEN_WITH_BACKGROUND = 2
}
/**
 * DragEvent object description
 *
 * @interface DragEvent
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface DragEvent {
    /**
     * X coordinate of the touch point relative to the left edge of the device screen.
     *
     * @returns { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getDisplayX(): double;
    /**
     * Y coordinate of the touch point relative to the upper edge of the device screen.
     *
     * @returns { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getDisplayY(): double;
    /**
     * X coordinate of the touch point relative to the left edge of the current window.
     *
     * @returns { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getWindowX(): double;
    /**
     * Y coordinate of the touch point relative to the left edge of the current window.
     *
     * @returns { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getWindowY(): double;
    /**
    * If copy is COPY, this DragEvent is a copy event.
    * @type { DragBehavior } Operation, if use copy then set COPY, else set MOVE.
    * @default COPY
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    dragBehavior: DragBehavior;
    /**
     * If useCustomDropAnimation is true, System will not use drop animation.
     *
     * @type { boolean }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    useCustomDropAnimation: boolean;
    /**
     * Set the uniqueId or uniqueId array of components that need to be automatically hidden during dragging.
     * This property takes effect only in onDragStart. After the drag starts successfully, the system hides the
     * target components before the drag preview window is shown. Developers need to restore component visibility
     * in onDragEnd or onDrop based on service requirements.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 26.0.0
     */
    autoHideComponentUniqueIds?: int | int[];
    /**
     * Set dragData into DragEvent.
     *
     * @param { UnifiedData } unifiedData - dragData.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    setData(unifiedData: UnifiedData): void;
    /**
     * Get dragData from DragEvent.
     *
     * @returns { UnifiedData | undefined } - get dragData, undefined will be returned if the internal runtime environment is broken.
     * @throws { BusinessError } 190001 - Data not found.
     * @throws { BusinessError } 190002 - Data error.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getData(): UnifiedData | undefined;
    /**
     * Get dragData summary from DragEvent.
     *
     * @returns { Summary | undefined } - get Summary Data, undefined will be returned if the internal runtime environment is broken.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getSummary(): Summary | undefined;
    /**
     * Set dragEvent result to DragEvent.
     *
     * @param { DragResult } dragResult - the return of dragEvent.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    setResult(dragResult: DragResult): void;
    /**
     * Get dragEvent result from DragEvent.
     *
     * @returns { DragResult } - dragResult Data.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getResult(): DragResult;
    /**
     * Get the rectangle of drag window.
     *
     * @returns { Rectangle } - getPreview rectangle.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getPreviewRect(): Rectangle;
    /**
     * Get the x axis velocity of drag gesture.
     *
     * @returns { double } - get x axis velocity.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getVelocityX(): double;
    /**
     * Get the y axis velocity of drag gesture.
     *
     * @returns { double } - get y axis velocity.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getVelocityY(): double;
    /**
     * Get the velocity of drag gesture.
     *
     * @returns { double } - get velocity.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getVelocity(): double;
    /**
     * Query the modifier key press state, support 'ctrl'|'alt'|'shift'
     *
     * @type { ?ModifierKeyStateGetter }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getModifierKeyState?: ModifierKeyStateGetter;
    /**
     * Setup one drop animation execution callback, which will be triggered by system when user drops.
     * Use this way to implement the custom drop animation instead of doing it in onDrop, as the system
     * will decide when to trigger the callback during the drop handling.
     * [Note]:
     *   1. Please set useCustomDropAnimation to true as well when using this method.
     *   2. Do not implement the animation no-related logics in the callback.
     *
     * @param { VoidCallback } customDropAnimation - the custom drop animation function.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    executeDropAnimation(customDropAnimation: VoidCallback): void;
    /**
     * Request the drag data to be synchronized to caller, can be notified with the synchronization progress.
     * Only can be used in onDrop event processing.
     *
     * @param { DataSyncOptions } options - the data sync options.
     * @returns { string | undefined } The data key returned by system, which can be used as the identify of the request.
     * @throws { BusinessError } 401 - Parameter error.
     * @throws { BusinessError } 190003 - Operation not allowed for current phase.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    startDataLoading(options: DataSyncOptions): string | undefined;
    /**
     * Get the id of display which the drag event is occuring on.
     *
     * @returns { int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
     getDisplayId(): int;
    /**
     * Retrieve the bundle information of the drag source application.
     *
     * @returns { string }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
     getDragSource(): string;
    /**
     * Call this method to determine whether the current drag operation is a cross-device drag.
     *
     * @returns { boolean }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
     isRemote(): boolean;
    /**
     * Use this method to provide a data representation to the system instead of directly providing a complete data
     * object. When the user releases the drag over the target application, the system will use this data
     * representation to request the actual data from drag source. This approach significantly improves the
     * efficiency of initiating drag operations for large volumes of data and enhances the effectiveness of data
     * reception. It is recommended to use this method instead of the setData method.
     *
     * @param { DataLoadParams } dataLoadParams - The data backend representation.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
     setDataLoadParams(dataLoadParams: DataLoadParams): void;
    /**
     * Enable the internal drop animation, which is only avaiable for system applications.
     *
     * The animations' configuration need to be provided through the input paramerter, and it is a string in json format.
     *
     * This method can only be called in onDrop, and please do not use custom drop animation after this method,
     * as it will reset the calling result, and use custom drop animation insteadly.
     *
     * @param { string } configuration - the internal drop animation's configuration.
     * @throws { BusinessError } 202 - Permission verification failed, application which is not a system application uses system API.
     * @throws { BusinessError } 801 - Capability not supported.
     * @throws { BusinessError } 190003 - Operation not allowed for current phase.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @systemapi
     * @stagemodelonly
     * @since 24
     */
    enableInternalDropAnimation(configuration: string): void;
    /**
     * X coordinate of the point relative to the global display.
     *
     * @returns { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    getGlobalDisplayX(): double;

    /**
     * Y coordinate of the point relative to the global display.
     *
     * @returns { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    getGlobalDisplayY(): double;
}
/**
 * The event callback function for drag and drop common interfaces.
 * @typedef { function } OnDragEventCallback
 * @param { DragEvent } event - the event object indicating current drag status.
 * @param { string } [extraParams] - extra information set by user or system.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type OnDragEventCallback = (event: DragEvent, extraParams?: string) => void;
/**
 * Defines the options for the drop handling.
 *
 * @interface DropOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface DropOptions {
    /**
     * Indicating to disable the UDMF data prefetch action by system or not.
     * The system will try to fetch data before calling user's onDrop for some situation,
     * it will retry to get data until the max time limit (2.4s for now) reaches,
     * this's useful for the cross device draging operation, as the system helps to eliminate
     * the communication instability, but it's redundant for startDataLoading method, as this
     * method will take care the data fetching with asynchronous mechanism, so must set this
     * field to true if using startDataLoading in onDrop to avoid the data is fetched before
     * onDrop executing unexpectedly.
     *
     * @type { boolean }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    disableDataPrefetch?: boolean;
}
/**
 * KeyEvent object description:
 *
 * @interface KeyEvent
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface KeyEvent {
    /**
     * Type of a key.
     *
     * @type { KeyType }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    type: KeyType;
    /**
     * Key code of a key
     *
     * @type { int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    keyCode: int;
    /**
     * Key value of a key.
     *
     * @type { string }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    keyText: string;
    /**
     * Type of the input device that triggers the current key, such as the keyboard or handle.
     *
     * @type { KeySource }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    keySource: KeySource;
    /**
     * Indicates the ID of the input device that triggers the current key.
     *
     * @type { int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    deviceId: int;
    /**
     * Indicates the status of the key when the key is pressed.
     * The value 1 indicates the pressed state, and the value 0 indicates the unpressed state.
     *
     * @type { int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    metaKey: int;
    /**
     * Timestamp when the key was pressed.
     *
     * @type { long }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    timestamp: long;
    /**
     * Block event bubbling.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    stopPropagation(): void;
    /**
     * Intention code of a key or modifier keys.
     *
     * @type { IntentionCode }
     * @default IntentionCode.INTENTION_UNKNOWN
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    intentionCode: IntentionCode;
    /**
     * Query the modifier key press state, support 'ctrl'|'alt'|'shift'
     *
     * @type { ?ModifierKeyStateGetter }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getModifierKeyState?: ModifierKeyStateGetter;
    /**
     * Unicode of a key
     *
     * @type { ?long }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    unicode?: long;
    /**
     * Whether Num Lock is on
     *
     * @type { ?boolean }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    isNumLockOn?: boolean;
    /**
     * Whether Caps Lock is on
     *
     * @type { ?boolean }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    isCapsLockOn?: boolean;
    /**
     * Whether Scroll Lock is on
     *
     * @type { ?boolean }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    isScrollLockOn?: boolean;
}
/**
 * Focus axis event object description.
 *
 * @extends BaseEvent
 * @interface FocusAxisEvent
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface FocusAxisEvent extends BaseEvent {
    /**
     * The axis values of axis event.
     *
     * @type { Map<AxisModel, double> }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    axisMap: Map<AxisModel, double>;
    /**
     * The blocking event pops up.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    stopPropagation(): void;
}
/**
 * CrownEvent object description
 *
 * @interface CrownEvent
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface CrownEvent {
    /**
     *The timestamp of the rotating crown event.
     *
     * @type { long }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    timestamp: long;
    /**
     * The angular velocity of a rotating crown.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    angularVelocity: double;
    /**
     * The rotation angle of the rotating crown.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    degree: double;
    /**
     * The behavior of rotating crown.
     *
     * @type { CrownAction }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    action: CrownAction;
    /**
     * The blocking event pops up.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    stopPropagation(): void;
}
/**
 * Overlay module options
 *
 * @interface BindOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface BindOptions {
    /**
     * Background color of the sheet.
     * <br>Default value: **Color.White**.
     *
     * @type { ?ResourceColor }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    backgroundColor?: ResourceColor;
    /**
     * Callback for when the sheet is displayed (after the animation ends).
     *
     * @type { ?VoidCallback }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    onAppear?: VoidCallback;
    /**
     * Callback for when the sheet disappears (after the animation ends).
     *
     * @type { ?VoidCallback }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    onDisappear?: VoidCallback;
    /**
     * Callback for when the sheet is about to be displayed (before the animation starts).
     *
     * @type { ?VoidCallback }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    onWillAppear?: VoidCallback;
    /**
     * Callback function before overlay popAnimation starts.
     *
     * @type { ?VoidCallback }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    onWillDisappear?: VoidCallback;
}
/**
 * Component content cover dismiss
 *
 * @interface DismissContentCoverAction
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 23
 */
export declare interface DismissContentCoverAction {
    /**
     * Defines content cover dismiss function
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    dismiss(): void;
    /**
     * Defines content cover dismiss reason
     *
     * @type { DismissReason }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    reason: DismissReason;
}
/**
 * Component content cover options
 *
 * @extends BindOptions
 * @interface ContentCoverOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface ContentCoverOptions extends BindOptions {
    /**
     * Defines transition type
     *
     * @type { ?ModalTransition }
     * @default ModalTransition.Default
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    modalTransition?: ModalTransition;
    /**
     * Callback function when the content cover interactive dismiss
     *
     * @type { ?Callback<DismissContentCoverAction> }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onWillDismiss?: Callback<DismissContentCoverAction>;
    /**
     * Defines transition effect param
     *
     * @type { ?TransitionEffect }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    transition?: TransitionEffect;
    /**
     * Set contentCover content adapts to safeArea.
     *
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    enableSafeArea?: boolean;
}
/**
 * Component sheet title options
 *
 * @interface SheetTitleOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface SheetTitleOptions {
    /**
     * Defines title text
     *
     * @type { ResourceStr }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    title: ResourceStr;
    /**
     * Defines subtitle text
     *
     * @type { ?ResourceStr }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    subtitle?: ResourceStr;
}
/**
 * Defines the sheet type.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum SheetType {
    /**
     * Bottom sheet.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    BOTTOM = 0,
    /**
     * Center sheet.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    CENTER = 1,
    /**
     * Popup sheet. The popup sheet cannot be dismissed with a pull-down gesture.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    POPUP = 2,
    /**
     * Defines side sheet type.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    SIDE = 3,
    /**
     * Defines content cover type.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    CONTENT_COVER = 4
}
/**
 * Define the display mode of the sheet.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum SheetMode {
    /**
     * The sheet is displayed at the top of the window corresponding to the current **UIContext** instance,
     * above all pages. It is displayed at the same level as dialog boxes.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    OVERLAY = 0,
    /**
     * The sheet is displayed at the top of the current page.
     * <br>**NOTE**<br>Currently, the sheet can only be mounted on a **Page**
     * or **NavDestination** node, with priority given to the **NavDestination**
     * node if it is present. This means that, the sheet can only be displayed at
     * the top of these two types of pages.<br> In this mode, new pages can overlay
     * the sheet, and when the user returns to the previous page, the sheet remains
     * present without losing its content.<br> In this mode, you must ensure that
     * the target page node, such as the **Page** node, has been attached to the tree
     * before bringing up the sheet; otherwise, the sheet will not be able to be
     * attached to the corresponding page node.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    EMBEDDED = 1
}
/**
 * Define the scroll size mode of the sheet.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum ScrollSizeMode {
    /**
     * Sheet change scroll size after the slide ends.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    FOLLOW_DETENT = 0,
    /**
     * Sheet change scroll size during the sliding process.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    CONTINUOUS = 1
}
/**
 * Define the mode of sheet how to avoid keyboard.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum SheetKeyboardAvoidMode {
    /**
     * Sheet will not aovid keyboard.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    NONE = 0,
    /**
     * Firstly sheet will avoid keyboard by changing its height.
     * And then sheet will avoid by resizing after reaching its maximum height.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    TRANSLATE_AND_RESIZE = 1,
    /**
     * Sheet will only avoid keyboard by resizing the content.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    RESIZE_ONLY = 2,
    /**
     * Firstly sheet will avoid keyboard by changing its height.
     * And then sheet will avoid keyboard by scrolling after reaching its maximum height.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    TRANSLATE_AND_SCROLL = 3,
    /**
     * Popup sheet will avoid keyboard by default.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    POPUP_SHEET = 4
}

/**
 * Component sheet dismiss
 *
 * @interface SheetDismiss
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 23
 */
export declare interface SheetDismiss {
    /**
     * Defines sheet dismiss function
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    dismiss(): void;
}
/**
 * Component sheet dismiss
 *
 * @interface DismissSheetAction
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 23
 */
export declare interface DismissSheetAction {
    /**
     * Defines sheet dismiss function
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    dismiss(): void;
    /**
     * Dismiss reason type.
     *
     * @type { DismissReason }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    reason: DismissReason;
}
/**
 * Defines sheet spring back action
 *
 * @interface SpringBackAction
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface SpringBackAction {
    /**
     * Defines spring back function
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    springBack(): void;
}
/**
 * Defines the detent array of a single length.
 *
 * @typedef { [SheetSize | Length] } SingleLengthDetent
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type SingleLengthDetent = [
    SheetSize | Length
];
/**
 * Defines the detent array of a two-length.
 *
 * @typedef { [(SheetSize | Length), SheetSize | Length | undefined] } DoubleLengthDetents
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type DoubleLengthDetents = [
    (SheetSize | Length),
    SheetSize | Length | undefined
];
/**
 * Defines the detent array of a three-length.
 *
 * @typedef { [(SheetSize | Length), SheetSize | Length | undefined, SheetSize | Length | undefined] }
 *     TripleLengthDetents
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type TripleLengthDetents = [
    (SheetSize | Length),
    SheetSize | Length | undefined,
    SheetSize | Length | undefined
];
/**
 * Component sheet options
 *
 * @extends BindOptions
 * @interface SheetOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface SheetOptions extends BindOptions {
    /**
     * Defines sheet height
     *
     * @type { ?(SheetSize | Length) }
     * @default Sheet.LARGE
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    height?: SheetSize | Length;
    /**
     * Whether to display the drag bar.
     * <br>**NOTE**<br>By default, the drag bar is displayed only when the sheet's
     * **detents** attribute is set to multiple heights and the settings take effect.
     *
     * @type { ?boolean }
     * @default true
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    dragBar?: boolean;
    /**
     * Defines whether the sheet dragbar is floating, when it's displayed.
     *
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    enableFloatingDragBar?: boolean;
    /**
     * Defines transition type when preferType is SheetType.CONTENT_COVER.
     *
     * @type { ?ModalTransition }
     * @default ModalTransition.DEFAULT
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    modalTransition?: ModalTransition;
    /**
    * Define strategy for drawing rounded corners.
    * NOTE
    * 1. **RenderStrategy.FAST**: The current component and its child components will be drawn directly
    * onto the canvas with rounded corners applied.
    * 2. **RenderStrategy.OFFSCREEN**: The current component and its child components will first be rendered onto
    * an off-screen canvas, then undergo a rounded corner clipping, and finally be drawn onto the main canvas.
    *
    * @type { ?RenderStrategy }
    * @default RenderStrategy.FAST
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @stagemodelonly
    * @since 23
    */
    radiusRenderStrategy?: RenderStrategy;
    /**
      * Set system-styled materials for sheet. Different materials have different effects, which can influence
      * the backgroundColor, border, shadow, and other visual attributes of sheet.
      *
      * @type { ?SystemUiMaterial }
      * @syscap SystemCapability.ArkUI.ArkUI.Full
      * @systemapi
      * @stagemodelonly
      * @since 26.0.0
      */
    systemMaterial?: SystemUiMaterial;
    /**
     * Mask color of the sheet.
     *
     * @type { ?ResourceColor }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    maskColor?: ResourceColor;
    /**
     * Defines sheet detents
     *
     * @type { ?(SingleLengthDetent | DoubleLengthDetents | TripleLengthDetents) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    detents?: SingleLengthDetent | DoubleLengthDetents | TripleLengthDetents;
    /**
     * Background blur of the sheet. By default, there is no background blur.
     *
     * @type { ?BlurStyle }
     * @default BlurStyle.NONE
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    blurStyle?: BlurStyle;
    /**
     * Defines whether the close icon is displayed
     *
     * @type { ?(boolean | Resource) }
     * @default true
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    showClose?: boolean | Resource;
    /**
    * Type of the sheet.
    * <br>**NOTE**<br>The types supported by the sheet vary by window.
    * <br>1. Width < 600 vp: bottom.
    * <br>2. 600 vp <= Width: bottom, center, and popup (default).
    * <br>3. Width >= 840 vp: bottom, center, and popup (default).
    *
    * @type { ?SheetType }
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    preferType?: SheetType;
    /**
     * Title of the sheet.
     *
     * @type { ?(SheetTitleOptions | CustomBuilder) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    title?: SheetTitleOptions | CustomBuilder;
    /**
     * Callback invoked when the user performs an interactive dismiss operation: pulling down or clicking
     * the back button, the mask, or the close icon.<br>**NOTE**<br>If this callback is registered, the
     * sheet is not dismissed immediately when the user performs the above operations. To dismiss the sheet,
     * you must call **shouldDismiss.dismiss()** in the callback.<br>If this callback is not registered, the
     * sheet is dismissed immediately when the user performs the above operations, without any additional
     * behavior.<br>It is recommended that this API be used in scenarios where a secondary confirmation is required.
     *
     * @type { ?function }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    shouldDismiss?: (sheetDismiss: SheetDismiss) => void;
    /**
     * Callback invoked when the user performs an interactive dismiss operation:
     * pulling down or clicking the back button, the mask, or the close icon,
     * to obtain the type of dismiss operation and decide whether to dismiss the sheet.
     * <p>**NOTE**:
     * <br>If this callback is registered, the sheet is not dismissed immediately when the user performs the above
     * operations.
     * <br>Instead, you can use the DismissSheetAction parameter in the callback to determine the type of
     * dismiss operation and decide whether to dismiss the sheet.
     * <br>If this callback is not registered, the sheet is dismissed immediately when the user performs the above
     * operations, without any additional behavior.
     * <br>No further interception with onWillDismiss is allowed in an onWillDismiss callback.
     * </p>
     *
     * @type { ?Callback<DismissSheetAction> }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onWillDismiss?: Callback<DismissSheetAction>;
    /**
    * Callback invoked when the user performs a pull-down-to-dismiss gesture, to control the bounce effect.
    * <p>**NOTE**:
    * <br>If this callback is registered along with **shouldDismiss** or **onWillDismiss** you can control whether the
    * sheet bounces back during the pull-down-to-dismiss operation by calling **springBack** in the callback.
    * <br>If this callback is not registered but **shouldDismiss** or **onWillDismiss** is registered, the sheet will
    * bounce back before remaining open or being dismissed based on the callback behavior.
    * <br>If neither this callback nor **shouldDismiss** or **onWillDismiss** is registered, the sheet is dismissed by
    * default during the pull-down-to-dismiss operation.
    * </p>
    *
    * @type { ?Callback<SpringBackAction> }
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    onWillSpringBackWhenDismiss?: Callback<SpringBackAction>;
    /**
     * Whether to allow users to interact with the page pertaining to the sheet.
     * <br>**NOTE**<br>The value **true** means that interactions are allowed, in which
     * case no mask is not displayed. The value **false** means that interactions are not
     * allowed, in which case a mask is displayed. If this parameter is not set, interactions
     * are allowed for the popup sheet, but not for bottom and center sheets. If this parameter
     * is set to **true**, the setting of **maskColor** does not take effect.
     *
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    enableOutsideInteractive?: boolean;
    /**
     * Width of the sheet.
     * Percentage parameter method: Set the width of the sheet as a percentage of the width of the parent element.
     *
     * @type { ?Dimension }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    width?: Dimension;
    /**
     * Border width of the sheet.
     * You can set the width for all four sides or set separate widths for individual sides.
     * Default value: **0**.
     * Percentage parameter method:
     * Set the border width of the sheet as a percentage of the width of the parent element.
     * If the left and right border widths of the sheet are greater than the width of the sheet, and the top
     * and bottom border widths are greater than the height of the sheet, the display may not appear as expected.
     * <p>**Note**:
     * <br>For bottom sheets, the bottom border width setting is ineffective.
     * </p>
     *
     * @type { ?(Dimension | EdgeWidths | LocalizedEdgeWidths) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    borderWidth?: Dimension | EdgeWidths | LocalizedEdgeWidths;
    /**
     * Border color of the sheet.
     * **borderColor** must be used with **borderWidth** in pairs.
     * <p>**NOTE**:
     * <br>For bottom sheets, the bottom border color setting is ineffective.
     * </p>
     *
     * @type { ?(ResourceColor | EdgeColors | LocalizedEdgeColors) }
     * @default Color.Black
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    borderColor?: ResourceColor | EdgeColors | LocalizedEdgeColors;
    /**
     * Defines the sheet's border style.
     *
     * @type { ?(BorderStyle | EdgeStyles) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    borderStyle?: BorderStyle | EdgeStyles;
    /**
     * Shadow of the sheet.
     * Default value for 2-in-1 devices: **ShadowStyle.OUTER_FLOATING_SM**.
     *
     * @type { ?(ShadowOptions | ShadowStyle) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    shadow?: ShadowOptions | ShadowStyle;
    /**
     * Callback for changes in the height of the sheet.
     * <p>**Note**:
     * <br>For a bottom sheet, the height of each frame is only returned when there are changes in detents or during drag
     * actions.
     * <br>When the sheet is pulled up or making space for the soft keyboard, only the final height is returned.
     * <br>For other types of sheets, the final height is only returned when the sheet is pulled up.
     * <br>The return value is in px.
     * <p>
     *
     * @type { ?Callback<int> }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onHeightDidChange?: Callback<int>;
    /**
     * Determine the level sheet shows, whether sheet should be displayed within the page.
     *
     * @type { ?SheetMode }
     * @default SheetMode.OVERLAY
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    mode?: SheetMode;
    /**
     * Content update mode of the sheet when it is scrolled.
     *
     * @type { ?ScrollSizeMode }
     * @default ScrollSizeMode.FELLOW_DETEND
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    scrollSizeMode?: ScrollSizeMode;
    /**
     * Callback for changes in the detents of the sheet.
     * <p>**NOTE**:
     * <br>For a bottom sheet, the final height is returned when there are changes in detents.
     * <br>The return value is in px.
     * </p>
     * @type { ?Callback<int> }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onDetentsDidChange?: Callback<int>;
    /**
     * Called when width of the sheet changed
     *
     * @type { ?Callback<int> }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onWidthDidChange?: Callback<int>;
    /**
     * Called when the sheet type changed
     *
     * @type { ?Callback<SheetType> }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onTypeDidChange?: Callback<SheetType>;
    /**
     * The UIContext that the sheet belongs to
     *
     * @type { ?UIContext }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    uiContext?: UIContext;
    /**
     * Determine the mode of sheet how to avoid keyboard.
     *
     * @type { ?SheetKeyboardAvoidMode }
     * @default SheetKeyboardAvoidMode.TRANSLATE_AND_SCROLL
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    keyboardAvoidMode?: SheetKeyboardAvoidMode;
    /**
     * Defines whether to respond to the hover mode.
     *
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    enableHoverMode?: boolean;
    /**
     * Defines the sheet's display area in hover mode.
     *
     * @type { ?HoverModeAreaType }
     * @default HoverModeAreaType.BOTTOM_SCREEN
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    hoverModeArea?: HoverModeAreaType;

     /**
      * Sets the position offset of the bindSheet.
      *
      * @type { ?Position }
      * @syscap SystemCapability.ArkUI.ArkUI.Full
      * @systemapi
      * @since 23
      */
    offset?: Position
    /**
     * Sets whether the sheet edge has spring effect.
     *
     * @type { ?number }
     * @default 3
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    effectEdge?: int;
    /**
     * Defines sheet radius
     *
     * @type { ?(LengthMetrics | BorderRadiuses | LocalizedBorderRadiuses) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    radius?: LengthMetrics | BorderRadiuses | LocalizedBorderRadiuses;
    /**
     * Select a detent from detents property
     *
     * @type { ?(SheetSize | Length) }
     * @default detents[0]
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    detentSelection?: SheetSize | Length;
    /**
     * Whether to display in the sub window
     *
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    showInSubWindow?: boolean;
    /**
     * The placement of popup sheet type.
     * Supports all positions defined in Placement.
     *
     * @type { ?Placement }
     * @default Placement.Bottom
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    placement?: Placement;
    /**
     * placement On target node
     *
     * @type { ?boolean }
     * @default true
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    placementOnTarget?: boolean;
}
/**
 * The custom styles function block.
 *
 * @typedef { function } CustomStyles
 * @param { CommonMethod } instance - The component instance which can be used to set common attributes.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type CustomStyles = (instance: CommonMethod) => void;
/**
 * Component State Styles.
 *
 * @interface StateStyles
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface StateStyles {
    /**
     * Defines normal state styles.
     *
     * @type { ?CustomStyles }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    normal?: CustomStyles;
    /**
     * Defines pressed state styles.
     *
     * @type { ?CustomStyles }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    pressed?: CustomStyles;
    /**
     * Defines disabled state styles.
     *
     * @type { ?CustomStyles }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    disabled?: CustomStyles;
    /**
     * Defines focused state styles.
     *
     * @type { ?CustomStyles }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    focused?: CustomStyles;
    /**
     * Defines clicked state styles.
     *
     * @type { ?CustomStyles }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    clicked?: CustomStyles;
    /**
     * Defines selected state styles.
     *
     * @type { ?CustomStyles }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    selected?: CustomStyles;
}
/**
 * Defines the options of popup message.
 *
 * @interface PopupMessageOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface PopupMessageOptions {
    /**
     * Sets the color of popup text.
     *
     * @type { ?ResourceColor }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    textColor?: ResourceColor;
    /**
     * Sets the font of popup text.
     *
     * @type { ?Font }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    font?: Font;
}
/**
 * Dismiss reason type.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum DismissReason {
    /**
    * Touching the Back button, swiping left or right on the screen, or pressing the Esc key.
    *
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    PRESS_BACK = 0,
    /**
    * Touching the mask.
    *
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    TOUCH_OUTSIDE = 1,
    /**
    * Touching the Close button.
    *
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    CLOSE_BUTTON = 2,
    /**
    * Slide down
    * <p><strong>NOTE</strong>:
    * <br>This API is effective only in sheet transition.
    * </p>
    *
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    SLIDE_DOWN = 3,
    /**
     * Slide, not slide down.
     * Default means slide right, after mirroring it means slide left.
     * Choosing to slide left or slide right is not supported.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    SLIDE = 4
}
/**
 * Component popup dismiss
 *
 * @interface DismissPopupAction
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface DismissPopupAction {
    /**
     * Defines popup dismiss function
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    dismiss(): void;
    /**
     * Defines popup dismiss reason
     *
     * @type { DismissReason }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    reason: DismissReason;
}
/**
 * Popup state change param
 *
 * @interface PopupStateChangeParam
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface PopupStateChangeParam {
    /**
     * is Visible.
     * Anonymous Object Rectification.
     *
     * @type { boolean }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    isVisible: boolean;
}
/**
 * Popup state change callback
 *
 * @typedef { function } PopupStateChangeCallback
 * @param { PopupStateChangeParam } event - The parameter of state change callback.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type PopupStateChangeCallback = (event: PopupStateChangeParam) => void;
/**
 * Popup mask type
 *
 * @interface PopupMaskType
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface PopupMaskType {
    /**
     * Color.
     * Anonymous Object Rectification.
     *
     * @type { ResourceColor }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    color: ResourceColor;
}
/**
 * Popup border LinearGradient
 *
 * @interface PopupBorderLinearGradient
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface PopupBorderLinearGradient {
    /**
     * direction: Direction of Linear Gradient.
     *
     * @type { ?GradientDirection }
     * @default GradientDirection.Bottom
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    direction?: GradientDirection;
    /**
     * Sets the colors and positions of the gradient.
     *
     * When the color setting is undefined, use the default value Color.Black.
     * The position setting ranges from 0 to 1.
     *
     * @type { Array<[ResourceColor | undefined, double]> }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    colors: Array<[ResourceColor | undefined, double]>;
}
/**
 * Popup common options
 *
 * @interface PopupCommonOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface PopupCommonOptions {
    /**
     * placement of popup.
     *
     * @type { ?Placement }
     * @default Placement.Bottom
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    placement?: Placement;
    /**
     * Set the background color of the popup.
     *
     * @type { ?ResourceColor }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    popupColor?: ResourceColor;
    /**
     * whether show arrow
     *
     * @type { ?boolean }
     * @default true
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    enableArrow?: boolean;
    /**
     * Whether hide popup when click mask
     *
     * @type { ?boolean }
     * @default true
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    autoCancel?: boolean;
    /**
     * on State Change
     *
     * @type { ?PopupStateChangeCallback }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onStateChange?: PopupStateChangeCallback;
    /**
     * The offset of the sharp corner of popup.
     *
     * @type { ?Length }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    arrowOffset?: Length;
    /**
     * Whether to display in the sub window.
     *
     * @type { ?boolean }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    showInSubWindow?: boolean;
    /**
     * The mask to block gesture events of popup.
     * When mask is set false, gesture events are not blocked.
     * When mask is set true, gesture events are blocked and mask color is transparent.
     *
     * @type { ?(boolean | PopupMaskType) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    mask?: boolean | PopupMaskType;
    /**
     * Sets the space of between the popup and target.
     *
     * @type { ?Length }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    targetSpace?: Length;
    /**
     * Sets the position offset of the popup.
     *
     * @type { ?Position }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    offset?: Position;
    /**
     * Set the width of the popup.
     *
     * @type { ?Dimension }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    width?: Dimension;
    /**
     * The position of the sharp corner of popup.
     *
     * @type { ?ArrowPointPosition }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    arrowPointPosition?: ArrowPointPosition;
    /**
     * The width of the arrow.
     *
     * @type { ?Dimension }
     * @default 16.0_vp.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    arrowWidth?: Dimension;
    /**
     * The height of the arrow.
     *
     * @type { ?Dimension }
     * @default 8.0_vp.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    arrowHeight?: Dimension;
    /**
     * The round corners of the popup.
     *
     * @type { ?Dimension }
     * @default 20.0_vp.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    radius?: Dimension;
    /**
     * The style of popup Shadow.
     *
     * @type { ?(ShadowOptions | ShadowStyle) }
     * @default ShadowStyle.OUTER_DEFAULT_MD.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    shadow?: ShadowOptions | ShadowStyle;
    /**
     * Defines popup background blur Style
     *
     * @type { ?BlurStyle }
     * @default BlurStyle.COMPONENT_ULTRA_THICK
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    backgroundBlurStyle?: BlurStyle;
    /**
     * Set popup focusable
     *
     * @type { ?boolean }
     * @default true
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    focusable?: boolean;
    /**
     * Defines the transition effect of popup opening and closing
     *
     * @type { ?TransitionEffect }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    transition?: TransitionEffect;
    /**
     * Callback function when the popup interactive dismiss.
     * Use boolean to respond all interactive dismiss event. Use Callback to customize which event should be responded.
     *
     * @type { ?(boolean | Callback<DismissPopupAction>) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onWillDismiss?: boolean | Callback<DismissPopupAction>;
    /**
     * Determine if it is compatible popup's half folded.
     *
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    enableHoverMode?: boolean;
    /**
     * Determine if popup can follow the target node when it has rotation or scale.
     *
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    followTransformOfTarget?: boolean;
    /**
     * Determine if popup can avoid the target when the display space is insufficient.
     *
     * @type { ?AvoidanceMode }
     * @default AvoidanceMode.COVER_TARGET
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    avoidTarget?: AvoidanceMode;
    /**
     * The width of popup's outline.
     *
     * @type { ?Dimension }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    outlineWidth?: Dimension;
    /**
     * The width of popup's border.
     *
     * @type { ?Dimension }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    borderWidth?: Dimension;
    /**
     * The LinearGradient of popup's outline.
     *
     * @type { ?PopupBorderLinearGradient }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    outlineLinearGradient?: PopupBorderLinearGradient;
    /**
     * The LinearGradient of popup's innerline.
     *
     * @type { ?PopupBorderLinearGradient }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    borderLinearGradient?: PopupBorderLinearGradient;
    /**
     * Set system-styled materials for popup. Different materials have different effects, which can influence
     * the backgroundColor, border, shadow, and other visual attributes of popup.
     *
     * @type { ?SystemUiMaterial }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @systemapi
     * @stagemodelonly
     * @since 26.0.0
     */
    systemMaterial?: SystemUiMaterial;

  /**
   * Callback function when the popup disappears.
   *
   * @type { ?VoidCallback }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  onDidDisappear?: VoidCallback;

  /**
   * Callback function before the popup closeAnimation starts.
   *
   * @type { ?VoidCallback }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  onWillDisappear?: VoidCallback;

  /**
   * Callback function before the popup openAnimation starts.
   *
   * @type { ?VoidCallback }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  onWillAppear?: VoidCallback;

  /**
   * Callback function when the popup appears.
   *
   * @type { ?VoidCallback }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  onDidAppear?: VoidCallback;
}
/**
 * Defines the Tips options.
 *
 * @interface TipsOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface TipsOptions {
    /**
     * Defines the delay time for appearing.
     *
     * @type { ?int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    appearingTime?: int;
    /**
     * Defines the delay time for disappearing.
     *
     * @type { ?int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    disappearingTime?: int;
    /**
     * Define the delay time for the appearance of continuous operations.
     *
     * @type { ?int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    appearingTimeWithContinuousOperation?: int;
    /**
     * Define the delay time for the disappearance of continuous operations.
     *
     * @type { ?int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    disappearingTimeWithContinuousOperation?: int;
    /**
     * whether show arrow
     *
     * @type { ?boolean }
     * @default true
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    enableArrow?: boolean;
    /**
     * The position of the sharp corner of Tips.
     *
     * @type { ?ArrowPointPosition }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    arrowPointPosition?: ArrowPointPosition;
    /**
     * The width of the arrow.
     *
     * @type { ?Dimension }
     * @default 16.0_vp.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    arrowWidth?: Dimension;
    /**
     * The height of the arrow.
     *
     * @type { ?Dimension }
     * @default 8.0_vp.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    arrowHeight?: Dimension;
    /**
     * Set the display location mode for tips. Tips can be shown around the component or follow the mouse cursor.
     *
     * @type { ?TipsAnchorType }
     * @default TipsAnchorType.TARGET
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    showAtAnchor?: TipsAnchorType;
}
/**
 * Defines the popup button.
 *
 * @interface PopupButton
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface PopupButton {
    /**
     * Button text value
     *
     * @type { string }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    value: string;
    /**
     * action
     *
     * @type { VoidCallback }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    action: VoidCallback;
}
/**
 * Defines the popup options.
 *
 * @interface PopupOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface PopupOptions {
    /**
     * Content of the popup message.
     *
     * @type { string }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    message: string;
    /**
     * The placement of popup.
     * Supports all positions defined in Placement.
     *
     * @type { ?Placement }
     * @default Placement.Bottom
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    placement?: Placement;
    /**
     * The first button.
     *
     * @type { ?PopupButton }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    primaryButton?: PopupButton;
    /**
     * The second button.
     *
     * @type { ?PopupButton }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    secondaryButton?: PopupButton;
    /**
     * on State Change
     *
     * @type { ?PopupStateChangeCallback }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onStateChange?: PopupStateChangeCallback;
    /**
     * The offset of the sharp corner of popup.
     *
     * @type { ?Length }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    arrowOffset?: Length;
    /**
     * Whether to display in the sub window.
     *
     * @type { ?boolean }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    showInSubWindow?: boolean;
    /**
     * The mask to block gesture events of popup.
     * When mask is set false, gesture events are not blocked.
     * When mask is set true, gesture events are blocked and mask color is transparent.
     *
     * @type { ?(boolean | PopupMaskType) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    mask?: boolean | PopupMaskType;
    /**
     * Parameters of the popup message.
     *
     * @type { ?PopupMessageOptions }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    messageOptions?: PopupMessageOptions;
    /**
     * Sets the space of between the popup and target.
     *
     * @type { ?Length }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    targetSpace?: Length;
    /**
     * whether show arrow
     *
     * @type { ?boolean }
     * @default true
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    enableArrow?: boolean;
    /**
     * Sets the position offset of the popup.
     *
     * @type { ?Position }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    offset?: Position;
    /**
     * Set the background color of the popup.
     *
     * @type { ?(Color | string | Resource | long) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    popupColor?: Color | string | Resource | long;
    /**
     * Whether hide popup when click mask
     *
     * @type { ?boolean }
     * @default true
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    autoCancel?: boolean;
    /**
     * Set the width of the popup.
     *
     * @type { ?Dimension }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    width?: Dimension;
    /**
     * The position of the sharp corner of popup.
     *
     * @type { ?ArrowPointPosition }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    arrowPointPosition?: ArrowPointPosition;
    /**
     * The width of the arrow.
     *
     * @type { ?Dimension }
     * @default 16.0_vp.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    arrowWidth?: Dimension;
    /**
     * The height of the arrow.
     *
     * @type { ?Dimension }
     * @default 8.0_vp.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    arrowHeight?: Dimension;
    /**
     * The round corners of the popup.
     *
     * @type { ?Dimension }
     * @default 20.0_vp.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    radius?: Dimension;
    /**
     * The style of popup Shadow.
     *
     * @type { ?(ShadowOptions | ShadowStyle) }
     * @default ShadowStyle.OUTER_DEFAULT_MD.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    shadow?: ShadowOptions | ShadowStyle;
    /**
     * Defines popup background blur Style
     *
     * @type { ?BlurStyle }
     * @default BlurStyle.COMPONENT_ULTRA_THICK
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    backgroundBlurStyle?: BlurStyle;
    /**
     * Defines the transition effect of popup opening and closing
     *
     * @type { ?TransitionEffect }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    transition?: TransitionEffect;
    /**
     * Callback function when the popup interactive dismiss
     *
     * @type { ?(boolean | Callback<DismissPopupAction>) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onWillDismiss?: boolean | Callback<DismissPopupAction>;
    /**
     * Determine if it is compatible popup's half folded.
     *
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    enableHoverMode?: boolean;
    /**
     * Determine if popup can follow the target node when it has rotation or scale.
     *
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    followTransformOfTarget?: boolean;
    /**
     * Define the popup avoid keyboard mode.
     *
     * @type { ?KeyboardAvoidMode }
     * @default KeyboardAvoidMode.NONE
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    keyboardAvoidMode?: KeyboardAvoidMode;
    /**
     * Determine if popup can avoid the target when the display space is insufficient.
     *
     * @type { ?AvoidanceMode }
     * @default AvoidanceMode.COVER_TARGET
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    avoidTarget?: AvoidanceMode;
    /**
     * The width of popup's outline.
     *
     * @type { ?Dimension }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    outlineWidth?: Dimension;
    /**
     * The width of popup's border.
     *
     * @type { ?Dimension }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    borderWidth?: Dimension;
    /**
     * The LinearGradient of popup's outline.
     *
     * @type { ?PopupBorderLinearGradient }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    outlineLinearGradient?: PopupBorderLinearGradient;
    /**
     * The LinearGradient of popup's innerline.
     *
     * @type { ?PopupBorderLinearGradient }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    borderLinearGradient?: PopupBorderLinearGradient;

    /**
     * Set system-styled materials for popup. Different materials have different effects, which can influence
     * the backgroundColor, border, shadow, and other visual attributes of popup.
     *
     * @type { ?SystemUiMaterial }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @systemapi
     * @stagemodelonly
     * @since 26.0.0
     */
    systemMaterial?: SystemUiMaterial;

  /**
   * Callback function before the popup closeAnimation starts.
   *
   * @type { ?VoidCallback }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  onWillDisappear?: VoidCallback;

  /**
   * Callback function when the popup appears.
   *
   * @type { ?VoidCallback }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  onDidAppear?: VoidCallback;

  /**
   * Callback function before the popup openAnimation starts.
   *
   * @type { ?VoidCallback }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  onWillAppear?: VoidCallback;

  /**
   * Callback function when the popup disappears.
   *
   * @type { ?VoidCallback }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  onDidDisappear?: VoidCallback;
}
/**
 * Defines the custom popup options.
 *
 * @interface CustomPopupOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface CustomPopupOptions {
    /**
     * Popup builder.
     * <p><strong>NOTE</strong>:
     * <br>The popup attribute is a universal attribute. A custom popup does not support display of another popup.
     * <br>The position attribute cannot be used for the first-layer container in the builder.
     * <br>If the position attribute is used, the popup will not be displayed.
     * <br>If a custom component is used in the builder, the aboutToAppear and aboutToDisappear lifecycle callbacks
     * of the custom component are irrelevant to the visibility of the popup. As such, the lifecycle of the
     * custom component cannot be used to determine whether the popup is displayed or not.
     * </p>
     *
     * @type { CustomBuilder }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    builder: CustomBuilder;
    /**
     * Preferred position of the popup. If the set position is insufficient for holding the popup,
     * it will be automatically adjusted.
     *
     * @type { ?Placement }
     * @default Placement.Bottom
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    placement?: Placement;
    /**
     * Color of the popup. To remove the background blur, set backgroundBlurStyle to BlurStyle.NONE.
     *
     * @type { ?(Color | string | Resource | long) }
     * @default TRANSPARENT plus COMPONENT_ULTRA_THICK
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    popupColor?: Color | string | Resource | long;
    /**
     * whether show arrow
     *
     * @type { ?boolean }
     * @default true
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    enableArrow?: boolean;
    /**
     * Whether to automatically dismiss the popup when an operation is performed on the page.
     * <p><strong>NOTE</strong>:
     * <br>To enable the popup to disappear upon a click on it, place a layout component in the builder place the
     * <Popup> component in the layout component, and modify the value of the bindPopup variable (show: boolean)
     * in the onClick event of the layout component.
     * </p>
     *
     * @type { ?boolean }
     * @default true
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    autoCancel?: boolean;
    /**
     * on State Change
     *
     * @type { ?PopupStateChangeCallback }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onStateChange?: PopupStateChangeCallback;
    /**
     * The offset of the sharp corner of popup.
     *
     * Offset of the popup arrow relative to the popup. When the arrow is at the top or bottom of the popup:
     * <br>The value 0 indicates that the arrow is located on the leftmost, and any other value indicates the distance
     * from the arrow to the leftmost; the arrow is centered by default. When the arrow is on the left or right
     * side of the popup: The value indicates the distance from the arrow to the top; the arrow is centered by
     * default. When the popup is displayed on either edge of the screen, it will automatically deviate leftward
     * or rightward to stay within the safe area. When the value is 0, the arrow always points to the bound component.
     *
     * @type { ?Length }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    arrowOffset?: Length;
    /**
     * Whether to display in the sub window.
     *
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    showInSubWindow?: boolean;
    /**
     * The mask to block gesture events of popup.
     * When mask is set false, gesture events are not blocked.
     * When mask is set true, gesture events are blocked and mask color is transparent.
     *
     * @type { ?(boolean | PopupMaskType) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    mask?: boolean | PopupMaskType;
    /**
     * Sets the space of between the popup and target.
     *
     * @type { ?Length }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    targetSpace?: Length;
    /**
     * Sets the position offset of the popup.
     *
     * @type { ?Position }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    offset?: Position;
    /**
     * Width of the popup.
     *
     * @type { ?Dimension }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    width?: Dimension;
    /**
     * Position of the popup arrow relative to its parent component. Available positions are Start, Center, and End,
     * in both vertical and horizontal directions. All these positions are within the parent component area.
     *
     * @type { ?ArrowPointPosition }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    arrowPointPosition?: ArrowPointPosition;
    /**
     * Arrow thickness. If the arrow thickness exceeds the length of the edge minus twice the size of the popup
     * rounded corner, the arrow is not drawn.
     * <p><strong>NOTE</strong>:
     * <br>This parameter cannot be set in percentage.
     * </p>
     *
     * @type { ?Dimension }
     * @default 16.0_vp.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    arrowWidth?: Dimension;
    /**
     * The height of the arrow.
     * <p><strong>NOTE</strong>:
     * <br>This parameter cannot be set in percentage.
     * </p>
     *
     * @type { ?Dimension }
     * @default 8.0_vp.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    arrowHeight?: Dimension;
    /**
     * Rounded corner radius of the popup.
     *
     * @type { ?Dimension }
     * @default 20.0_vp.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    radius?: Dimension;
    /**
     * Popup shadow.
     *
     * @type { ?(ShadowOptions | ShadowStyle) }
     * @default ShadowStyle.OUTER_DEFAULT_MD.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    shadow?: ShadowOptions | ShadowStyle;
    /**
     * Background blur style of the popup.
     *
     * @type { ?BlurStyle }
     * @default BlurStyle.COMPONENT_ULTRA_THICK
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    backgroundBlurStyle?: BlurStyle;
    /**
     * Set popup focusable
     *
     * @type { ?boolean }
     * @default true
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    focusable?: boolean;
    /**
     * Defines the transition effect of popup opening and closing
     *
     * @type { ?TransitionEffect }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    transition?: TransitionEffect;
    /**
     * Whether to perform dismissal event interception and interception callback.
     * 1. If this parameter is set to false, the system does not respond to the dismissal event initiated by
     * touching the Back button, swiping left or right on the screen, or pressing the Esc key; and the system
     * dismisses the popup only when show is set to false. If this parameter is set to true, the system responds
     * to the dismissal event as expected.
     * 2. If this parameter is set to a function, the dismissal event is intercepted and the callback function
     * is executed.
     * <p><strong>NOTE</strong>:
     * <br>No more onWillDismiss callback is allowed in an onWillDismiss callback.
     * </p>
     *
     * @type { ?(boolean | Callback<DismissPopupAction>) }
     * @default true
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onWillDismiss?: boolean | Callback<DismissPopupAction>;
    /**
      * Determine if it is compatible popup's half folded.
      *
      * @type { ?boolean }
      * @default false
      * @syscap SystemCapability.ArkUI.ArkUI.Full
      * @since 23
      */
    enableHoverMode?: boolean;
    /**
     * Determine if popup can follow the target node when it has rotation or scale.
     *
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    followTransformOfTarget?: boolean;
    /**
     * Define the popup avoid keyboard mode.
     *
     * @type { ?KeyboardAvoidMode }
     * @default KeyboardAvoidMode.NONE
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    keyboardAvoidMode?: KeyboardAvoidMode;
    /**
     * Determine if popup can avoid the target when the display space is insufficient.
     *
     * @type { ?AvoidanceMode }
     * @default AvoidanceMode.COVER_TARGET
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    avoidTarget?: AvoidanceMode;
    /**
     * The width of popup's outline.
     *
     * @type { ?Dimension }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    outlineWidth?: Dimension;
    /**
     * The width of popup's border.
     *
     * @type { ?Dimension }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    borderWidth?: Dimension;
    /**
     * The LinearGradient of popup's outline.
     *
     * @type { ?PopupBorderLinearGradient }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    outlineLinearGradient?: PopupBorderLinearGradient;
    /**
     * The LinearGradient of popup's innerline.
     *
     * @type { ?PopupBorderLinearGradient }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    borderLinearGradient?: PopupBorderLinearGradient;

    /**
     * Set system-styled materials for popup. Different materials have different effects, which can influence
     * the backgroundColor, border, shadow, and other visual attributes of popup.
     *
     * @type { ?SystemUiMaterial }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @systemapi
     * @stagemodelonly
     * @since 26.0.0
     */
    systemMaterial?: SystemUiMaterial;

  /**
   * Callback function when the popup appears.
   *
   * @type { ?VoidCallback }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  onDidAppear?: VoidCallback;

  /**
   * Callback function before the popup closeAnimation starts.
   *
   * @type { ?VoidCallback }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  onWillDisappear?: VoidCallback;

  /**
   * Callback function when the popup disappears.
   *
   * @type { ?VoidCallback }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  onDidDisappear?: VoidCallback;

  /**
   * Callback function before the popup openAnimation starts.
   *
   * @type { ?VoidCallback }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  onWillAppear?: VoidCallback;
}

/**
 * Defines the menu preview mode.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum MenuPreviewMode {
    /**
     * No preview content.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    NONE = 0,
    /**
     * The preview is a screenshot of the component on which a long-press triggers the context menu.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    IMAGE = 1
}
/**
 * Defines the animator range of start and end property.
 *
 * @typedef { [double, double] } AnimationNumberRange
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type AnimationNumberRange = [
    double,
    double
];
/**
 * Defines the ContextMenu's preview animator options.
 *
 * @interface ContextMenuAnimationOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export interface ContextMenuAnimationOptions {
    /**
     * Sets the start animator scale and end animator scale.
     *
     * @type { ?AnimationNumberRange }
     * @default -
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    scale?: AnimationNumberRange;
    /**
     * Defines the transition effect of menu preview opening and closing.
     *
     * @type { ?TransitionEffect }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    transition?: TransitionEffect;
    /**
     * Sets the scale start and end animator of the image displayed before the custom builder preview is displayed.
     *
     * @type { ?AnimationNumberRange }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    hoverScale?: AnimationNumberRange;
    /**
     * Sets whether support to interrupt the process of hover scale.
     *
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    hoverScaleInterruption?: boolean;
}
/**
 * Defines the scaling mode for custom preview of contextMenu.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum PreviewScaleMode {
    /**
     * Automatically resize preview based on the layout area.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    AUTO = 0,
    /**
     * Maintain original size of preview content without scaling.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    CONSTANT = 1,
    /**
     * Maintain aspect ratio to scale preview.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    MAINTAIN = 2
}
/**
 * Defines the content transition effect.
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare class ContentTransitionEffect {
  /**
   * When the content changes,there is no animation effect.
   *
   * @type {ContentTransitionEffect}
   * @static
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  static get IDENTITY(): ContentTransitionEffect;

  /**
   * When the content changes,there is a smooth fade-in and fade-out effect.
   *
   * @type {ContentTransitionEffect}
   * @static
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  static get OPACITY(): ContentTransitionEffect;
}
/**
 * Defines the type of border radius.
 *
 * @typedef { Length | BorderRadiuses | LocalizedBorderRadiuses }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type BorderRadiusType = Length | BorderRadiuses | LocalizedBorderRadiuses;
/**
 * Defines the menu haptic feedback mode.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum HapticFeedbackMode {
    /**
     * No haptic feedback.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DISABLED = 0,
    /**
     * Defines menu always haptic feedback.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    ENABLED = 1,
    /**
     * Defines menu automatically haptic feedback.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    AUTO = 2
}

/**
 * Define the mode of menu how to avoid keyboard.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 23
 */
export declare enum MenuKeyboardAvoidMode {
  /**
   * Menu will not avoid keyboard.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @stagemodelonly
   * @since 23
   */
  NONE = 0,

  /**
   * First menu will avoid keyboard by changing its placement.
   * And then menu will avoid by resizing height when new placement is still not high enough.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @stagemodelonly
   * @since 23
   */
  TRANSLATE_AND_RESIZE = 1
}

/**
 * Defines the context menu options.
 *
 * @interface ContextMenuOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface ContextMenuOptions {
    /**
     * Offset for showing the context menu, which should not cause the menu to extend beyond the screen.
     * <p><strong>NOTE</strong>:
     * <br>When the menu is displayed relative to the parent component area, the width or height of the area is
     * automatically counted into the offset based on the placement attribute of the menu. When the menu is
     * displayed above the parent component (that is, placement is set to Placement.TopLeft, Placement.Top, or
     * Placement.TopRight), a positive value of x indicates rightward movement relative to the parent component,
     * and a positive value of y indicates upward movement. When the menu is displayed below the parent component
     * (that is, placement is set to Placement.BottomLeft, Placement.Bottom, or Placement.BottomRight), a positive
     * value of x indicates rightward movement relative to the parent component, and a positive value of y indicates
     * downward movement. When the menu is displayed on the left of the parent component (that is, placement is set
     * to Placement.LeftTop, Placement.Left, or Placement.LeftBottom), a positive value of x indicates leftward
     * movement relative to the parent component, and a positive value of y indicates downward movement. When the
     * menu is displayed on the right of the parent component (that is, placement is set to Placement.RightTop,
     * Placement.Right, or Placement.RightBottom), a positive value of x indicates rightward movement relative to
     * the parent component, and a positive value of y indicates downward movement. If the display position of the
     * menu is adjusted (different from the main direction of the initial placement value), the offset value is invalid.
     * </p>
     *
     * @type { ?Position }
     * @default {x:0,y:0} - Percentage values are not supported.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    offset?: Position;
    /**
     * Preferred position of the context menu. If the set position is insufficient for holding the component, it will be
     * automatically adjusted.
     * <p><strong>NOTE</strong>:
     * <br>If a menu is displayed by pressing and holding or right-clicking, the menu is displayed at the clicked
     * position.
     * </p>
     *
     * @type { ?Placement }
     * @default Placement.BottomLeft
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    placement?: Placement;
    /**
     * whether show arrow belong to the menu.
     * <p><strong>NOTE</strong>:
     * <br>When enableArrow is true, an arrow is displayed in the position specified by placement.
     * <br>If placement is not set or its value is invalid, the arrow is displayed above the target.
     * <br>If the position is insufficient for holding the arrow, it is automatically adjusted.
     * <br>When enableArrow is undefined, no arrow is displayed.
     * <br>This API is supported in bindContextMenu since API version 10 and bindMenu since API version 12.
     * </p>
     *
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    enableArrow?: boolean;
    /**
     * Offset of the arrow relative to the context menu. The offset settings take effect only when the value is valid,
     * can be converted to a number greater than 0, and does not cause the arrow to extend beyond the safe area of
     * the context menu.
     * <p><strong>NOTE</strong>:
     * <br>The safe distance of the arrow from the four sides of the menu is the sum of the menu's corner radius and
     * half the width of the arrow. The value of placement determines whether the offset is horizontal or vertical.
     * When the arrow is in the horizontal direction of the menu, the offset is the distance from the arrow to the
     * leftmost arrow's safe distance. When the arrow is in the vertical direction of the menu, the offset is the
     * distance from the arrow to the topmost arrow's safe distance. The default position where the arrow is
     * displayed varies with the value of placement: Without any avoidance by the menu, when placement is set to
     * Placement.Top or Placement.Bottom, the arrow is displayed horizontally and is centered by default; when
     * placement is set to Placement.Left or Placement.Right, the arrow is displayed vertically and is centered by
     * default; when placement is set to Placement.TopLeft or Placement.BottomLeft, the arrow is displayed
     * horizontally by default, and the distance from the arrow to the left edge of the menu is the arrow's safe
     * distance; when placement is set to Placement.TopRight or Placement.BottomRight, the arrow is displayed
     * horizontally by default, and the distance from the arrow to the right edge of the menu is the arrow's safe
     * distance; when placement is set to Placement.LeftTop or Placement.RightTop, the arrow is displayed vertically
     * by default, and the distance from the arrow to the top edge of the menu is the arrow's safe distance; when
     * placement is set to Placement.LeftBottom or Placement.RightBottom, the arrow is displayed vertically by
     * default, and the distance from the arrow to the bottom edge of the menu is the arrow's safe distance.
     * <br>This API is supported in bindContextMenu since API version 10 and bindMenu since API version 12.
     * </p>
     *
     * @type { ?Length }
     * @default 0vp
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    arrowOffset?: Length;
    /**
     * Preview displayed when the context menu is triggered by a long-press or use the isShown variable of
     * bindContextMenu to display the preview content style of the menu.
     * <p><strong>NOTE</strong>:
     * <br>This parameter has no effect when responseType is set to ResponseType.RightClick.
     * <br>If preview is set to MenuPreviewMode.NONE or is not set, the enableArrow parameter is effective.
     * <br>If preview is set to MenuPreviewMode.IMAGE or CustomBuilder, no arrow will be displayed even when
     * enableArrow is true.
     * </p>
     *
     * @type { ?(MenuPreviewMode | CustomBuilder) }
     * @default MenuPreviewMode.NONE
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    preview?: MenuPreviewMode | CustomBuilder;
    /**
     * Defines the border radius for preview of menu.
     *
     * @type { BorderRadiusType }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    previewBorderRadius?: BorderRadiusType;
    /**
     * Border radius of the menu.
     * <p><strong>NOTE</strong>:
     * <br>The value can be in percentage.
     * <br>If the sum of the two maximum corner radii in the horizontal direction exceeds the menu's width, or if the sum
     * of the two maximum corner radii in the vertical direction exceeds the menu's height, the default corner radius of
     * the menu will be used.
     * </p>
     *
     * @type { ?(Length | BorderRadiuses | LocalizedBorderRadiuses) }
     * @default 8vp for 2-in-1 devices and 20vp for other devices
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    borderRadius?: Length | BorderRadiuses | LocalizedBorderRadiuses;
    /**
     * Callback triggered when the menu is displayed.
     *
     * @type { ?function }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onAppear?: () => void;
    /**
     * Callback function when the context menu disappear.
     *
     * @type { ?function }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onDisappear?: () => void;
    /**
     * Callback triggered when the menu is about to appear.
     *
     * @type { ?function }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    aboutToAppear?: () => void;
    /**
     * Callback triggered when the menu is about to disappear.
     *
     * @type { ?function }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    aboutToDisappear?: () => void;
    /**
     * The margin of menu's layoutRegion.
     *
     * @type { ?Margin }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    layoutRegionMargin?: Margin;
    /**
     * The preview animator options.
     *
     * @type { ?ContextMenuAnimationOptions }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    previewAnimationOptions?: ContextMenuAnimationOptions;
    /**
     * Background color of the menu.
     *
     * @type { ?ResourceColor }
     * @default Color.Transparent
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    backgroundColor?: ResourceColor;
    /**
     * Background blur style of the menu.
     *
     * @type { ?BlurStyle }
     * @default BlurStyle.COMPONENT_ULTRA_THICK
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    backgroundBlurStyle?: BlurStyle;
    /**
     * Defines the menu's background blur style with options
     *
     * @type { ?BackgroundBlurStyleOptions }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    /**
     * Defines the menu's background effect with options
     *
     * @type { ?BackgroundEffectOptions }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    backgroundEffect?: BackgroundEffectOptions;
    /**
     * Defines the transition effect of menu opening and closing.
     *
     * @type { ?TransitionEffect }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    transition?: TransitionEffect;
    /**
      * Determine if it is compatible menu's half folded.
      *
      * @type { ?boolean }
      * @default false
      * @syscap SystemCapability.ArkUI.ArkUI.Full
      * @since 23
      */
    enableHoverMode?: boolean;
    /**
     * Defines the haptic feedback mode of menu.
     *
     * @type { ?HapticFeedbackMode }
     * @default HapticFeedbackMode.DISABLED
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    hapticFeedbackMode?: HapticFeedbackMode;
    /**
     * The color of menu's outer border.
     *
     * @type { ?(ResourceColor | EdgeColors) }
     * @default '#19ffffff'
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    outlineColor?: ResourceColor | EdgeColors;
    /**
     * The width of menu's outer border.
     * If outline effects are required, outlineWidth is required.
     *
     * @type { ?(Dimension | EdgeOutlineWidths) }
     * @default 0vp - Percentage values are not supported.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    outlineWidth?: Dimension | EdgeOutlineWidths;
    /**
     * Whether it is a menu without mask.
     *
     * @type { ?(boolean | MenuMaskType) }
     * @default true when preview is enabled, or is false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    mask?: boolean | MenuMaskType;
    /**
     * Defines modal mode of menu.
     *
     * @type { ?ModalMode }
     * @default ModalMode.AUTO
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    modalMode?: ModalMode;
    /**
     * Callback function when the menu appears.
     *
     * @type { ?VoidCallback }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    onDidAppear?: VoidCallback;
    /**
     * Callback function when the menu disappears.
     *
     * @type { ?VoidCallback }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    onDidDisappear?: VoidCallback;
    /**
     * Callback function before the menu openAnimation starts.
     *
     * @type { ?VoidCallback }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    onWillAppear?: VoidCallback;
    /**
     * Callback function before the menu closeAnimation starts.
     *
     * @type { ?VoidCallback }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    onWillDisappear?: VoidCallback;
    /**
     * Defines the scaling mode for custom preview of contextMenu.
     *
     * @type { ?PreviewScaleMode }
     * @default PreviewScaleMode.AUTO
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    previewScaleMode?: PreviewScaleMode;
    /**
     * Defines the available layout area of preview.
     *
     * @type { ?AvailableLayoutArea }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    availableLayoutArea?: AvailableLayoutArea;
    /**
     * Defines the menu position.
     *
     * @type { ?Position }
     * @default { x: 0, y: 0 }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    anchorPosition?: Position;

    /**
     * Determine the mode of menu how to avoid keyboard.
     *
     * No avoiding by default
     *
     * @type { ?MenuKeyboardAvoidMode }
     * @default MenuKeyboardAvoidMode.NONE
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    keyboardAvoidMode?: MenuKeyboardAvoidMode;

    /**
     * Defines the minimum distance between menu and keyboard.
     *
     * @type { ?LengthMetrics }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    minKeyboardAvoidDistance?: LengthMetrics;
    /**
     * Set system-styled materials for menu. Different materials have different effects, which can influence
     * the backgroundColor, border, shadow, and other visual attributes of menu.
     *
     * Device Behavior Differences:The effect of the same material may vary across different devices depending on
     * their computing power.
     *
     * @type { ?SystemUiMaterial }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @systemapi
     * @stagemodelonly
     * @since 23
     */
    systemMaterial?: SystemUiMaterial;
    /**
     * Defines the scroll bar state of menu.
     *
     * @type { ?BarState }
     * @default BarState.Auto
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 26.0.0
     */
    scrollBar?: BarState;
    /**
     * Defines the max height of menu.
     *
     * @type { ?LengthMetrics }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 26.0.0
     */
    maxHeight?: LengthMetrics;
}
/**
 * Defines the menu options.
 *
 * @extends ContextMenuOptions
 * @interface MenuOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface MenuOptions extends ContextMenuOptions {
    /**
     * Sets the title of the menu window.
     *
     * @type { ?ResourceStr }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    title?: ResourceStr;
    /**
     * Whether to display in the sub window.
     *
     * @type { ?boolean }
     * @default true for 2-in-1 devices and false for other devices
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    showInSubWindow?: boolean;
}
/**
 * Implements a ProgressMask object to set the progress, maximum value, and color of the mask.
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare class ProgressMask {
    /**
     * constructor.
     *
     * @param { double } value - Current value of the progress mask. Value range: [0.0, +∞).
     * @param { double } total - Maximum value of the progress mask. Value range: [0.0, +∞).
     * @param { ResourceColor } color - Color of the progress mask.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    constructor(value: double, total: double, color: ResourceColor);
    /**
     * Updates the progress value of the progress mask.
     *
     * @param { double } value - Current value of the progress mask.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    updateProgress(value: double): void;
    /**
     * Update the color of the mask.
     *
     * @param { ResourceColor } value - Color of the progress mask.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    updateColor(value: ResourceColor): void;
    /**
     * Enable the breathe animation of mask.
     *
     * @param { boolean } value
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    enableBreathingAnimation(value: boolean): void;
}
/**
 * Defines TouchTestInfo class.
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare class TouchTestInfo {
   /**
     * Get the X-coordinate relative to the window.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    windowX: double;
    /**
     * Get the Y-coordinate relative to the window.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    windowY: double;
    /**
     * Get the X-coordinate relative to the current component.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    parentX: double;
    /**
     * Get the Y-coordinate relative to the current component.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    parentY: double;
    /**
     * Get the X-coordinate relative to the sub component.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    x: double;
    /**
     * Get the Y-coordinate relative to the sub component.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    y: double;
    /**
     * Get the rectangle of sub component.
     *
     * @type { RectResult }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    rect: RectResult;
    /**
     * Get the name of sub component.
     *
     * @type { string }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    id: string;
}
/**
 * Defines TouchResult class.
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare class TouchResult {
    /**
     * Defines the touch test strategy.
     *
     * @type { TouchTestStrategy }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    strategy: TouchTestStrategy;
    /**
     * Defines the component's name.
     *
     * @type { ?string }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    id?: string;
}
/**
 * Set the edge blur effect distance of the corresponding defense line of the component
 * When the component expand out, no re-layout is triggered
 *
 * @interface PixelStretchEffectOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface PixelStretchEffectOptions {
    /**
     * top property. value range (-∞, ∞)
     * If value > 0, expand outward elements. Else first shrink by value and then expand outward pixels.
     *
     * @type { ?Length }
     * @default 0
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    top?: Length;
    /**
     * bottom property. value range (-∞, ∞)
     * If value > 0, expand outward elements. Else first shrink by value and then expand outward pixels.
     *
     * @type { ?Length }
     * @default 0
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    bottom?: Length;
    /**
     * left property. value range (-∞, ∞)
     * If value > 0, expand outward elements. Else first shrink by value and then expand outward pixels.
     *
     * @type { ?Length }
     * @default 0
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    left?: Length;
    /**
     * right property. value range (-∞, ∞)
     * If value > 0, expand outward elements. Else first shrink by value and then expand outward pixels.
     *
     * @type { ?Length }
     * @default 0
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    right?: Length;
}
/**
 * Defines the click effect.
 *
 * @interface ClickEffect
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface ClickEffect {
    /**
     * Set the click effect level.
     *
     * @type { ClickEffectLevel }
     * @default ClickEffectLevel.Light
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    level: ClickEffectLevel;
    /**
     * Set scale number.
     * This default scale is same as the scale of click effect level.
     *
     * <p><strong>NOTE</strong>:
     * <br> This parameter works based on the setting of ClickEffectLevel.
     * <br> If level is set to ClickEffectLevel.LIGHT, the default value is 0.90.
     * <br> If level is set to ClickEffectLevel.MIDDLE or ClickEffectLevel.HEAVY, the default value is 0.95.
     * <br> If level is set to undefined or null (both of which evaluate to ClickEffectLevel.LIGHT), the default value is 0.90.
     * <br> If scale is set to undefined or null, the default zoom ratio for the set level will be used.
     * </p>
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    scale?: double;
}
/**
 * Defines the fadingEdge options.
 *
 * @typedef FadingEdgeOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface FadingEdgeOptions {
    /**
     * The length of FadingEdge.
     *
     * @type { LengthMetrics }
     * @default 32vp
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    fadingEdgeLength?: LengthMetrics;
}
/**
 * Define nested scroll options
 *
 * @interface NestedScrollOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface NestedScrollOptions {
    /**
     * Set NestedScrollMode when the scrollable component scrolls forward
     *
     * @type { NestedScrollMode }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    scrollForward: NestedScrollMode;
    /**
     * Set NestedScrollMode when the scrollable component scrolls backward
     *
     * @type { NestedScrollMode }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    scrollBackward: NestedScrollMode;
}
/**
 * Defines the menu element.
 *
 * @interface MenuElement
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface MenuElement {
    /**
     * Sets the value of the menu element.
     *
     * @type { ResourceStr }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    value: ResourceStr;
    /**
     * Sets the icon of the menu element.
     *
     * @type { ?ResourceStr }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    icon?: ResourceStr;
    /**
     * Sets the symbol of the menu element.
     *
     * @type { ?SymbolGlyphModifier }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    symbolIcon?: SymbolGlyphModifier;
    /**
     * If the value is true, the menu element is available and can respond to operations such as clicking.
     * If the value is false, the menu element is not available and click operations are not responded.
     *
     * @type { ?boolean }
     * @default true
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    enabled?: boolean;
    /**
     * Method executed by the callback.
     *
     * @type { function }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    action: () => void;
}

/**
 * Defines the attribute modifier.
 *
 * @interface AttributeModifier<T>
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface AttributeModifier<T> {
  /**
   * Defines the normal update attribute function.
   *
   * @param { T } instance
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  default applyNormalAttribute(instance: T) : void;

  /**
   * Defines the pressed update attribute function.
   *
   * @param { T } instance
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  default applyPressedAttribute(instance: T) : void;

  /**
   * Defines the focused update attribute function.
   *
   * @param { T } instance
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  default applyFocusedAttribute(instance: T) : void;

  /**
   * Defines the disabled update attribute function.
   *
   * @param { T } instance
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  default applyDisabledAttribute(instance: T) : void;

  /**
   * Defines the selected update attribute function.
   *
   * @param { T } instance
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 23
   */
  default applySelectedAttribute(instance: T) : void;

  /**
   * Specifies the states to be monitored.
   * Override this method to specify which states (Normal, Pressed, Focused, Disabled, Selected) should be
   * monitoredby returning a bitmask of ModifierState enum values.
   *
   * @returns { int } - Bitmask combination of states to be monitored
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @FaAndStageModel
   * @since 23
   */
  default monitoredStates(): int;
}
/**
 * Defines the content modifier.
 *
 * @interface ContentModifier
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface ContentModifier<T> {
    /**
     * Defining applyContent function.
     *
     * @returns { WrappedBuilder<CustomBuilderT<T>> }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    applyContent(): WrappedBuilder<CustomBuilderT<T>>;
}
/**
 * Defines the common configuration.
 *
 * @interface CommonConfiguration
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface CommonConfiguration<T> {
    /**
     * If the value is true, the contentModifier is available and can respond to operations such as triggerChange.
     *  If it is set to false, triggerChange operations are not responded.
     *
     * @type { boolean }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    enabled: boolean;
    /**
     * Obtains the contentModifier instance object
     *
     * @type { ContentModifier<T> }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    contentModifier: ContentModifier<T>;
}
/**
 * Outline Style
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum OutlineStyle {
    /**
     * Solid border.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    SOLID = 0,
    /**
     * Dashed border.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DASHED = 1,
    /**
     * Dotted border. The radius of a dot is half of **outlineWidth**.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DOTTED = 2
}
/**
 * Defines the drag preview mode.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum DragPreviewMode {
    /**
     * Default preview mode, let system process preview scale.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    AUTO = 1,
    /**
     * Disable system scale to preview panel
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DISABLE_SCALE = 2,
    /**
     * Enable the default shadow effect of preview.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    ENABLE_DEFAULT_SHADOW = 3,
    /**
     * Enable the default radius effect of preview.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    ENABLE_DEFAULT_RADIUS = 4,
    /**
     * Enable the default gray effect on the dragging item.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    ENABLE_DRAG_ITEM_GRAY_EFFECT = 5,
    /**
     * Enable the tile effect for multi drag, each dragged graph is display in the original relative position.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    ENABLE_MULTI_TILE_EFFECT = 6,
    /**
     * Enable the touch point calculation position based on final preview rect.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    ENABLE_TOUCH_POINT_CALCULATION_BASED_ON_FINAL_PREVIEW = 7
}
/**
 * Define drag start animation effect from drag preview to the handle drag image
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum DraggingSizeChangeEffect {
    /**
     * Default effect, no transition.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DEFAULT = 0,
    /**
     * Only scaled transition, this parameter take effect when PREVIEW_MODE is not DISABLE_SCALE.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    SIZE_TRANSITION = 1,
    /**
     * Scaled and content transition together, this size transition take effect when PREVIEW_MODE is not DISABLE_SCALE.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    SIZE_CONTENT_TRANSITION = 2
}
/**
 * Define the menu pop-up policy
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum MenuPolicy {
    /**
     * Default value. The default logic of whether to pop up a menu depends on the scene.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DEFAULT = 0,
    /**
     * The menu is always hidden.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    HIDE = 1,
    /**
     * The menu is always displayed.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    SHOW = 2
}
/**
 * Defines the preview options.
 *
 * @interface DragPreviewOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface DragPreviewOptions {
    /**
     * Drag preview mode.
     *
     * @type { ?(DragPreviewMode | Array<DragPreviewMode>) }
     * @default DragPreviewMode.AUTO
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    mode?: DragPreviewMode | Array<DragPreviewMode>;
    /**
     * Drag preview modifier.
     *
     * @type { ?ImageModifier }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    modifier?: ImageModifier;
    /**
     * The flag for number showing.
     *
     * @type { ?(boolean | long) }
     * @default true
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    numberBadge?: boolean | long;
    /**
    * Drag start animation effect from drag preview to the handle drag image.
    *
    * @type { ?DraggingSizeChangeEffect }
    * @default DraggingSizeChangeEffect.DEFAULT
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    sizeChangeEffect?: DraggingSizeChangeEffect;
}
/**
 * Defines the drag options.
 *
 * @interface DragInteractionOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface DragInteractionOptions {
    /**
    * Define whether to gather selected nodes in grid or list.
    *
    * @type { ?boolean }
    * @default false
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    isMultiSelectionEnabled?: boolean;
    /**
    * Define whether to execute animation before preview floating.
    *
    * @type { ?boolean }
    * @default false
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    defaultAnimationBeforeLifting?: boolean;
    /**
    * Config if auto scrolling should be triggered when the drag hovered on a scrollable controller's edge.
    *
    * @type { ?boolean }
    * @default true
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    enableEdgeAutoScroll?: boolean;
    /**
    * Define whether to enable the haptic feedback when dragging, the default value is false.
    *
    * @type { ?boolean }
    * @default false
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    enableHapticFeedback?: boolean;
    /**
    * Define whether to lifting trigger drag by finger.
    *
    * @type { ?boolean }
    * @default false
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    isLiftingDisabled?: boolean;
}
/**
 * Defines the drag preview configuration.
 *
 * @interface PreviewConfiguration
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface PreviewConfiguration {
    /**
    * Define whether to only use for lifting.
    *
    * @type { ?boolean }
    * @default false
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    onlyForLifting?: boolean;
    /**
    * Define whether to delay create builder.
    *
    * @type { ?boolean }
    * @default false
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    delayCreating?: boolean;
}
/**
 * Define the options of invert
 *
 * @interface InvertOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface InvertOptions {
    /**
     * Defines the low value of threshold
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    low: double;
    /**
     * Defines the high value of threshold
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    high: double;
    /**
     * Defines the threshold
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    threshold: double;
    /**
     *Defines the threshold range
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    thresholdRange: double;
}
/**
 * Defines the type that can be undefined.
 *
 * @typedef { T | undefined } Optional<T>
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type Optional<T> = T | undefined;
/**
 * Defines the TipsMessageType property with ResourceStr and StyledString.
 *
 * @typedef { ResourceStr | StyledString } TipsMessageType
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type TipsMessageType = ResourceStr | StyledString;
/**
 * Define the modal mode of menu.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum ModalMode {
    /**
     * Modal modal automatically.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    AUTO = 0,
    /**
     * Operation takes effect around menu.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    NONE = 1,
    /**
     * Operation takes no effect around menu in target window.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    TARGET_WINDOW = 2
}
/**
 * Menu mask type
 *
 * @interface MenuMaskType
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface MenuMaskType {
    /**
     * Mask color of menu.
     *
     * @type { ?ResourceColor }
     * @default Color.Transparent
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    color?: ResourceColor;
    /**
     * Set menu mask background blur Style.
     *
     * @type { ?BlurStyle }
     * @default BlurStyle.COMPONENT_ULTRA_THICK
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    backgroundBlurStyle?: BlurStyle;
}
/**
 * Defines the available layout area.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum AvailableLayoutArea {
    /**
     * Size of safe area.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    SAFE_AREA = 0
}
/**
 * Define the options for background image.
 *
 * @interface BackgroundImageOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export interface BackgroundImageOptions {
    /**
     * Sets the synchronous or asynchronous mode for background image loading.
     * The default parameter type is bool, and the default value is false.
     *
     * @type { ?boolean }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    syncLoad?: boolean;
    /**
     * Set the repeat style of the background image.
     *
     * @type { ?ImageRepeat }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    repeat?: ImageRepeat;
}
/**
 * Defines background options.
 *
 * @interface BackgroundOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface BackgroundOptions {
    /**
     * Set the alignment of the custom background and component.
     *
     * Anonymous Object Rectification.
     * @type { ?Alignment }
     * @default Alignment.Center
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    align?: Alignment;
    /**
     * The set of edges for which to ignore layout safe area. To respect safe area insets on all edges,
     * explicitly pass empty edge set.
     *
     * @type { ?Array<LayoutSafeAreaEdge> }
     * @default The default value is LayoutSafeAreaEdge.ALL when background is ResourceColor, otherwise
     *     it is an empty array [].
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
    */
    ignoresLayoutSafeAreaEdges?: Array<LayoutSafeAreaEdge>;
}
/**
 * Defines the value of the custom property..
 *
 * @typedef { undefined | null | Object | Record<string, CustomProperty> | Array<CustomProperty> } CustomProperty
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare type CustomProperty = undefined | null | Object | Record<string, CustomProperty> | Array<CustomProperty>;

/**
 * CommonMethod
 *
 * @interface CommonMethod
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 23
 */
export declare interface CommonMethod {
    /**
     * Sets the width of the component or its horizontal layout policy. By default, the
     * component uses the width required for its content. If the width of the component is
     * greater than that of the parent container, the component will be drawn beyond the
     * parent container scope.
     *
     * @param { Length | LayoutPolicy | undefined } widthValue
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default width(widthValue: Length | LayoutPolicy | undefined): this;
    /**
     * Sets the height of the component or its vertical layout policy. By default, the
     * component uses the height required for its content. If the height of the component
     * is greater than that of the parent container, the component will be drawn beyond
     * the parent container scope.
     *
     * @param { Length | LayoutPolicy | undefined } heightValue
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default height(heightValue: Length | LayoutPolicy | undefined): this;
    /**
     * Sets the drawModifier of the current component.
     *
     * @param { DrawModifier | undefined } modifier - drawModifier used to draw, or undefined if it is not available.
     * Default value: undefined
     * A custom modifier applies only to the FrameNode of the currently bound component, not to its subnodes.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default drawModifier(modifier: DrawModifier | undefined): this;
    /**
     * Sets the custom property of the current component.
     * This API does not work for custom components.
     *
     * @param { string } name - the name of the custom property.
     * @param { CustomProperty } value - the value of the custom property.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default customProperty(name: string, value: CustomProperty): this;
    /**
     * Sets the safe area to be expanded to.
     * <br>default:{types: [SafeAreaType.SYSTEM, SafeAreaType.CUTOUT, SafeAreaType.KEYBOARD],
     * edges: [SafeAreaEdge.TOP, SafeAreaEdge.BOTTOM, SafeAreaEdge.START, SafeAreaEdge.END]}
     *
     * @param { Array<SafeAreaType> } [types] - Indicates the types of the safe area.
     * @param { Array<SafeAreaEdge> } [edges] - Indicates the edges of the safe area.
     * @returns { this } The component instance.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default expandSafeArea(types?: Array<SafeAreaType>, edges?: Array<SafeAreaEdge>): this;
    /**
     * Expands the layout safe area of a component.
     *
     * @param { Array<LayoutSafeAreaType> | undefined } [types] - The region type to expand the component's layout safe area into.
     *     The default value is LayoutSafeAreaType.SYSTEM.
     * @param { Array<LayoutSafeAreaEdge> | undefined } [edges] - The set of edges for which to ignore layout safe area.
     *     The default value is LayoutSafeAreaEdge.ALL.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType> | undefined, edges?: Array<LayoutSafeAreaEdge> | undefined): this;
    /**
     * Sets the response region of the current component.
     *
     * @param { Array<Rectangle> | Rectangle | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default responseRegion(value: Array<Rectangle> | Rectangle | undefined): this;
    /**
     * Sets the mouse response region of current component
     *
     * @param { Array<Rectangle> | Rectangle | undefined } value
     * @returns { this } return the component attribute
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default mouseResponseRegion(value: Array<Rectangle> | Rectangle | undefined): this;
    /**
    * Sets the response region list of the current component.
    * 
    * @param { Array<ResponseRegion> | undefined } regions
    * @returns { this } return the component attribute
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    default responseRegionList(regions: Array<ResponseRegion> | undefined): this;
    /**
     * Sets the size of the component.
     *
     * @param { SizeOptions | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default size(value: SizeOptions | undefined): this;
    /**
     * Sets the constraint size of the component, which is used to limit the size range during component layout.
     * Default value: **{minWidth: 0, maxWidth: Infinity, minHeight: 0, maxHeight: Infinity}**.
     *
     * @param { ConstraintSizeOptions | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default constraintSize(value: ConstraintSizeOptions | undefined): this;
    /**
     * Sets how the component behaves during hit testing.
     *
     * @param { HitTestMode | undefined } value - the hit test mode.
     * @default HitTestMode.default - Both the node and its child nodes respond to the hit test of a touch event,
     *     but its sibling nodes are blocked from the hit test. The hit test for ancestor nodes is not affected.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default hitTestBehavior(value: HitTestMode | undefined): this;
    /**
     * Called to specify how to perform the touch test on the children of this component.
     *
     * @param { ((value: Array<TouchTestInfo>) => TouchResult) | undefined } event
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onChildTouchTest(event: ((value: Array<TouchTestInfo>) => TouchResult) | undefined): this;
    /**
     * Sets the weight of the component during layout. A component with this attribute is allocated space
     * along the main axis of its parent container (Row, Column, or Flex) based on its specified weight.
     * Default value: **0**.
     *
     * @param { double | string | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default layoutWeight(value: double | string | undefined): this;
    /**
     * Sets the weight of the component in a chain, which is used to re-lay out components that form the chain.
     * <br>This API has effect only when the parent container is RelativeContainer.
     *
     * @param { ChainWeightOptions | undefined } chainWeight
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default chainWeight(chainWeight: ChainWeightOptions | undefined): this;
    /**
     * Sets the padding of the component.
     * Default value: **0**.
     *
     * @param { Padding | Length | LocalizedPadding | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default padding(value: Padding | Length | LocalizedPadding | undefined): this;
    /**
     * Sets the safe area padding. It enables a container to add a component-level
     * safe area for child components to expand into.
     * Default value: **LengthMetrics.vp(0)**
     *
     * @param { Padding | LengthMetrics | LocalizedPadding | undefined } paddingValue - Indicates safeArea padding values
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default safeAreaPadding(paddingValue: Padding | LengthMetrics | LocalizedPadding | undefined): this;
    /**
     * Sets the margin of the component.
     * Default value: **0**.
     *
     * @param { Margin | Length | LocalizedMargin | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default margin(value: Margin | Length | LocalizedMargin | undefined): this;
    /**
     * Set the background to a given CustomBuilder, or set it to a specific ResourceColor.
     *
     * @param { CustomBuilder | ResourceColor | undefined } content
     * @param { BackgroundOptions } [options]
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    default background(content: CustomBuilder | ResourceColor | undefined, options?: BackgroundOptions): this;
    /**
     * Background color
     *
     * @param { ResourceColor | ColorMetrics | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    default backgroundColor(value: ResourceColor | ColorMetrics | undefined): this;
    /**
     * Sets the pixel rounding policy for the current component in the specified direction.
     * <br>If a direction is not set, the pixels are rounded to the nearest whole number in that direction.
     *
     * @param { PixelRoundPolicy | undefined } value - indicates the rounding policy for the bounds of the component.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default pixelRound(value: PixelRoundPolicy | undefined): this;
    /**
     * Background image
     *
     * @param { ResourceStr | PixelMap | undefined } src - the background image source
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default backgroundImage(src: ResourceStr | PixelMap | undefined): this;
    /**
     * Background image
     *
     * @param { ResourceStr | PixelMap | undefined } src - the background image source
     * @param { BackgroundImageOptions } options - config the options
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default backgroundImage(src: ResourceStr | PixelMap | undefined, options: BackgroundImageOptions): this;
    /**
     * Background image
     * src:Image address url
     *
     * @param { ResourceStr | PixelMap | undefined } src
     * @param { ImageRepeat } repeat
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default backgroundImage(src: ResourceStr | PixelMap | undefined, repeat: ImageRepeat): this;
    /**
     * Background image size
     *
     * @param { SizeOptions | ImageSize | undefined } value - The width and height of the background image.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default backgroundImageSize(value: SizeOptions | ImageSize | undefined): this;
    /**
     * Background image position
     * x:Horizontal coordinate;y:Vertical axis coordinate.
     *
     * @param { Position | Alignment | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default backgroundImagePosition(value: Position | Alignment | undefined): this;
    /**
     * Defines the blur style to apply between the background and content of a component.
     * It encapsulates various blur radius, mask color, mask opacity, saturation.
     * And brightness values through enum values.
     *
     * @param { BlurStyle | undefined } style - Settings of the background blur style
     *     <br>including the blur radius, mask color, mask opacity, saturation, and brightness.
     * @param { BackgroundBlurStyleOptions } [options]
     * @param { SystemAdaptiveOptions } [sysOptions] - system adaptive options.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default backgroundBlurStyle(style: BlurStyle | undefined, options?: BackgroundBlurStyleOptions, sysOptions?: SystemAdaptiveOptions): this;
    /**
     * options:background effect options.
     * sysOptions: system adaptive options.
     *
     * @param { BackgroundEffectOptions | undefined } options - options indicates the effect options.
     * @param { SystemAdaptiveOptions } [ sysOptions ] - system adaptive options.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default backgroundEffect(options: BackgroundEffectOptions | undefined, sysOptions?: SystemAdaptiveOptions): this;
    /**
     * Background image resizable.
     * value:resizable options
     *
     * @param { ResizableOptions | undefined } value - Indicates the resizable options.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default backgroundImageResizable(value: ResizableOptions | undefined): this;
    /**
     * Foreground effect.
     *
     * @param { ForegroundEffectOptions | undefined } options - options indicates the effect options.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default foregroundEffect(options: ForegroundEffectOptions | undefined): this;
    /**
     * Sets a visual effect that is not a filter effect.
     *
     * @param { VisualEffect | undefined } effect - Visual effect parameters.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default visualEffect(effect: VisualEffect | undefined): this;
    /**
     * Sets the visual effect of the background filter.
     *
     * @param { Filter | undefined } filter - Filter effect parameters.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default backgroundFilter(filter: Filter | undefined): this;
    /**
     * Sets the visual effect of the foreground (content) filter.
     *
     * @param { Filter | undefined } filter - Filter effect parameters.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default foregroundFilter(filter: Filter | undefined): this;
    /**
     * Sets the visual effect of the compositing filter.
     *
     * @param { Filter | undefined } filter - Filter effect parameters.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default compositingFilter(filter: Filter | undefined): this;
    /**
     * Sets the visual effect of the material filter. The effects it contains are rendered at a level before the shadow.
     *
     * @param { Filter | undefined } filter - Filter effect parameters.
     *     Undefined means to none material filter. 
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default materialFilter(filter: Filter | undefined): this;
    /**
     * Applies a foreground blur style to the component.
     *
     * @param { BlurStyle | undefined } style - Settings of the foreground blur style.
     * @param { ForegroundBlurStyleOptions } [options]
     * @param { SystemAdaptiveOptions } [sysOptions] - system adaptive options.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default foregroundBlurStyle(style: BlurStyle | undefined, options?: ForegroundBlurStyleOptions, sysOptions?: SystemAdaptiveOptions): this;
    /**
     * Sets the opacity of the component.
     *
     * @param { double | Resource | undefined } value - Opacity of the component. The value ranges from 0 to 1.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default opacity(value: double | Resource | undefined): this;
    /**
     * Sets the border.
     *
     * @param { BorderOptions | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default border(value: BorderOptions | undefined): this;
    /**
     * Sets the border style.
     * Default value: **BorderStyle.Solid**.
     *
     * @param { BorderStyle | EdgeStyles | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default borderStyle(value: BorderStyle | EdgeStyles | undefined): this;
    /**
     * Sets the border width.
     * Percentage values are not supported.
     *
     * @param { Length | EdgeWidths | LocalizedEdgeWidths | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default borderWidth(value: Length | EdgeWidths | LocalizedEdgeWidths | undefined): this;
    /**
     * Sets the border color.
     * Default value: **Color.Black**.
     * @param { ResourceColor | EdgeColors | LocalizedEdgeColors | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default borderColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): this;
    /**
     * Sets the radius of the border rounded corners.
     *     The radius is restricted by the component size. The maximum value is half of the component width or height.
     * NOTE
     *    1. **RenderStrategy.FAST**: The current component and its child components will be drawn directly
     *        onto the canvas with rounded corners applied.
     *    2. **RenderStrategy.OFFSCREEN**: The current component and its child components will first be rendered onto
     *        an off-screen canvas, then undergo a rounded corner clipping, and finally be drawn onto the main canvas.
     * @param { Length | BorderRadiuses | LocalizedBorderRadiuses | undefined } value
     * @param { RenderStrategy | undefined } [type] - Application types for drawing rounded corners.
     *     Default value: **RenderStrategy.FAST**.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses | undefined, type?: RenderStrategy | undefined): this;
    /**
     * Sets the border image of the component.
     *
     * @param { BorderImageOption | undefined } value - Border image or border gradient.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default borderImage(value: BorderImageOption | undefined): this;
    /**
     * Sets the outline attributes in one declaration.
     *
     * @param { OutlineOptions | undefined } value - Outline attributes.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default outline(value: OutlineOptions | undefined): this;
    /**
     * Sets the style of the outline.
     *
     * @param { OutlineStyle | EdgeOutlineStyles | undefined } value - Outline style.
     *     <br>Default value: **OutlineStyle.SOLID**.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default outlineStyle(value: OutlineStyle | EdgeOutlineStyles | undefined): this;
    /**
     * Sets the thickness of the outline.
     *
     * @param { Dimension | EdgeOutlineWidths | undefined } value - Outline thickness. Percentage values are not supported.
     *     <br>Default value: **0**Outline thickness. Percentage values are not supported.
     *     <br>Default value: **0**.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default outlineWidth(value: Dimension | EdgeOutlineWidths | undefined): this;
    /**
     * Sets the color of the outline.
     *
     * @param { ResourceColor | EdgeColors | LocalizedEdgeColors | undefined } value - Outline color.
     *     <br>Default value: **Color.Black**.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default outlineColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): this;
    /**
     * Sets the radius of the outline corners.
     *
     * @param { Dimension | OutlineRadiuses | undefined } value - adius of the outline corners. Percentage
     *     values are not supported.
     *     <br>Default value: **0**.
     *     <br>Maximum effective value: Component width/2 + outlineWidth or component height/2 + outlineWidth.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default outlineRadius(value: Dimension | OutlineRadiuses | undefined): this;
    /**
     * Sets the foreground color of the component.
     * If the component does not have a foreground color set, it inherits the color from its parent component by default.
     *
     * @param { ResourceColor | ColoringStrategy | undefined } value - Foreground color.
     *     <br>The value can be a specific color or a coloring strategy. Property animations are supported.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default foregroundColor(value: ResourceColor | ColoringStrategy | undefined): this;
    /**
     * Called when a click event occurs.
     *
     * <p><strong>NOTE</strong>:
     * <br> Since API version 9, the following constraints apply when this API is used in service widgets:
     * <br> Click events cannot be triggered if the finger is pressed for more than 800 ms.
     * <br> Click events cannot be triggered if the finger moves more than 20 px after pressing down.
     * </p>
     * @param { ((event: ClickEvent) => void) | undefined } event
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onClick(event: ((event: ClickEvent) => void) | undefined): this;
    /**
     * Trigger a click event when a click is clicked, move distance should smaller than distanceThreshold.
     *
     * <p><strong>NOTE</strong>:
     * <br> If the distanceThreshold value specified is less than or equal to 0 vp, it will be converted
     * to the default value. Since API version 9, the following constraints apply when this API is used
     * in service widgets:
     * <br> Click events cannot be triggered if the finger is pressed for more than 800 ms.
     * <br> Click events cannot be triggered if the finger moves more than 20 px after pressing down.
     * </p>
     * @param { Callback<ClickEvent> | undefined } event - this function callback executed when the click
     *     action is recognized
     * @param { double | undefined } distanceThreshold - the distance threshold of finger's movement when
     *     detecting a click action
     * @default (2^31-1)vp
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onClick(event: Callback<ClickEvent> | undefined, distanceThreshold: double | undefined): this;
    /**
     * Trigger a hover event.
     *
     * @param { ((isHover: boolean, event: HoverEvent) => void) | undefined } event
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onHover(event: ((isHover: boolean, event: HoverEvent) => void) | undefined): this;
    /**
     * Trigger a hover move event.
     *
     * @param { Callback<HoverEvent> | undefined } event
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onHoverMove(event: Callback<HoverEvent> | undefined): this;
    /**
     * Trigger a accessibility hover event.
     *
     * @param { AccessibilityCallback | undefined } callback - A callback instance used when the component is touched after accessibility mode is enabled.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onAccessibilityHover(callback: AccessibilityCallback | undefined): this;

    /**
     * prompt for current component and descendants unable to handle accessibility hover event
     *
     * @param { AccessibilityTransparentCallback | undefined } callback - A callback instance used when current component and 
     * descendants not handled accessibility hover event
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onAccessibilityHoverTransparent(callback: AccessibilityTransparentCallback | undefined): this;
    /**
     * Set hover effect.
     *
     * @param { HoverEffect | undefined } value - Hover effect of the component in hover state.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default hoverEffect(value: HoverEffect | undefined): this;
    /**
     * Triggered when the component is clicked by a mouse button or the mouse pointer moves on the component.
     *
     * @param { ((event: MouseEvent) => void) | undefined } event
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onMouse(event: ((event: MouseEvent) => void) | undefined): this;
    /**
     * Invoked when a touch event is triggered.
     *
     * @param { ((event: TouchEvent) => void) | undefined } event
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onTouch(event: ((event: TouchEvent) => void) | undefined): this;
    /**
     * Keyboard input
     *
     * @param { Callback<KeyEvent, boolean> | undefined } event - Callback for handling the key event.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onKeyEvent(event: Callback<KeyEvent, boolean> | undefined): this;
    /**
     * Digital crown input.
     *
     * @param { Callback<CrownEvent> | undefined } event
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onDigitalCrown(handler: Callback<CrownEvent> | undefined): this;
    /**
     * Handle keyboard events before input method events.
     *
     * @param { Callback<KeyEvent, boolean> | undefined } event - Callback for handling the key event.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onKeyPreIme(event: Callback<KeyEvent, boolean> | undefined): this;
    /**
     * Customize the handling and distribution of key events.
     *
     * @param { Callback<KeyEvent, boolean> | undefined } event
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onKeyEventDispatch(event: Callback<KeyEvent, boolean> | undefined): this;
    /**
     * Trigger a FocusAxisEvent.
     *
     * @param { Callback<FocusAxisEvent> | undefined } event
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onFocusAxisEvent(event: Callback<FocusAxisEvent> | undefined): this;
    /**
     * Handle axis events.
     *
     * @param { Callback<AxisEvent> | undefined } event
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onAxisEvent(event: Callback<AxisEvent> | undefined): this;
    /**
     * Set focusable.
     * Components that have default interaction logic, such as Button and TextInput, are focusable by default. Other
     * components, such as Text and Image, are not focusable by default. Only focusable components can trigger a focus
     * event.
     *
     * @param { boolean | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default focusable(value: boolean | undefined): this;
    /**
     * Set nextFocus.
     *
     * @param { FocusMovement | undefined } nextStep
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default nextFocus(nextStep: FocusMovement | undefined): this;
    /**
     * Set TabStop on component focus
     *
     * @param { boolean | undefined } isTabStop
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default tabStop(isTabStop: boolean | undefined): this;
    /**
     * Trigger a event when got focus.
     *
     * @param { (() => void) | undefined } event
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onFocus(event: (() => void) | undefined): this;
    /**
     * Triggered when the current component loses focus.
     *
     * @param { (() => void) | undefined } event
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onBlur(event: (() => void) | undefined): this;
    /**
     * Set focus index by key tab.
     * The tabIndex and focusScopeId cannot be used together.
     * @param { int | undefined } index
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default tabIndex(index: int | undefined): this;
    /**
     * Set default focused component when a page create.
     *
     * @param { boolean | undefined } value - True means to set the component as the default focus,
     *     and the value false has no effect.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default defaultFocus(value: boolean | undefined): this;
    /**
     * Set default focused component when focus on a focus group.
     *
     * @param { boolean | undefined } value - True means the component is the default focus of the parent container, and
     *     false means the component is not the default focus of the parent container.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default groupDefaultFocus(value: boolean | undefined): this;
    /**
     * Set a component focused when the component be touched.
     *
     * @param { boolean | undefined } value - True means the component is focusable on touch, false means
     *     the component is not focusable on touch.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default focusOnTouch(value: boolean | undefined): this;
    /**
     * Set the component's focusBox style.
     *
     * @param { FocusBoxStyle | undefined } style - Component's focusBox style.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default focusBox(style: FocusBoxStyle | undefined): this;
    /**
    * Set container as a focus group with a specific identifier.
    *
    * @param { string | undefined } id - focus scope identifier.
    * @param { boolean } [isGroup] - whether this scope is a focus group, the default value is false.
    * @param { boolean } [arrowStepOut] - whether the arrow keys can move focus from inside the focus group to outside,
    * only effective when isGroup is true, the default value is true.
    * @returns { this }
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    default focusScopeId(id: string | undefined, isGroup?: boolean, arrowStepOut?: boolean): this;
    /**
    * Set the focus priority of component in a specific focus scope.
    *
    * @param { string | undefined } scopeId
    * @param { FocusPriority } [priority] - the default value is AUTO
    * @returns { this }
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    default focusScopePriority(scopeId: string | undefined, priority?: FocusPriority): this;
    /**
     * animation
     *
     * @param { AnimateParam | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default animation(value: AnimateParam | undefined): this;
    /**
     * Set the transition effect of component when it appears and disappears.
     *
     * @param { TransitionEffect | undefined } value - transition effect
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default transition(value: TransitionEffect | undefined): this;
    /**
     * Set the transition effect of component when it appears and disappears.
     *
     * @param { TransitionEffect | undefined } effect - transition effect
     * @param { TransitionFinishCallback | undefined } onFinish - transition finish callback.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default transition(effect: TransitionEffect | undefined, onFinish: TransitionFinishCallback | undefined): this;
    /**
     * Bind gesture recognition.
     * gesture:Bound Gesture Type,mask:GestureMask;
     *
     * @param { GestureType } gesture
     * @param { GestureMask } [mask]
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default gesture(gesture: GestureType, mask?: GestureMask): this;
    /**
     * Binding Preferential Recognition Gestures
     * gesture:Bound Gesture Type,mask:GestureMask;
     *
     * @param { GestureType } gesture
     * @param { GestureMask } [mask]
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default priorityGesture(gesture: GestureType, mask?: GestureMask): this;
    /**
     * Binding gestures that can be triggered simultaneously with internal component gestures
     * gesture:Bound Gesture Type,mask:GestureMask;
     *
     * @param { GestureType } gesture
     * @param { GestureMask } [mask]
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default parallelGesture(gesture: GestureType, mask?: GestureMask): this;
    /**
     * Adds the content blurring effect for the current component. The input parameter is the blurring radius.
     * The larger the blurring radius, the more blurring the content.
     * If the value is 0, the content blurring effect is not blurring.
     *
     * @param { double | undefined } blurRadius - value indicates radius of backdrop blur.
     * @param { BlurOptions } [options] - options indicates blur options.
     * @param { SystemAdaptiveOptions } [sysOptions] - system adaptive options.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default blur(blurRadius: double | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this;
    /**
     * Applies a linear gradient foreground blur effect to the component.
     *
     * @param { double | undefined } value - the blurring radius. The larger the blurring radius, the more
     *     blurring the content, and if the value is 0, the content blurring effect is not blurring.
     * @param { LinearGradientBlurOptions | undefined } options - the linear gradient blur options.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default linearGradientBlur(value: double | undefined, options: LinearGradientBlurOptions | undefined): this;
    /**
     * Apply a motion blur effect to the component being scaled or moved.
     * 1.Do not use this API in intra-component transitions, shared element transitions,
     * implicit element transitions, or particle animations. Doing so may cause unexpected results.
     * 2.The **radius** parameter of **motionBlur** must be set to **0** for the initial state.
     * Otherwise, there may be unexpected results during a cold start.
     * 3.This API must be used together with the **onFinish** parameter of **AnimateParam**.
     * Its **radius** parameter must be set to **0** when the animation ends; otherwise, there may be unexpected results.
     * 4.When using this API, do not frequently change the blur radius of the same component;
     * otherwise, there may be unexpected results.
     * For example, if you frequently click the image in the example, the blur effect may not work sometimes.
     * 5.To avoid unexpected results, make sure the coordinates of
     * the motion blur anchor point are the same as those of the animation scaling anchor point.
     * 6.To avoid unexpected results, set the blur radius to a value less than 1.
     *
     * @param { MotionBlurOptions | undefined } value - Motion blur options.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default motionBlur(value: MotionBlurOptions | undefined): this;
    /**
     * Applies a brightness effect to the component.
     *
     * @param { double | undefined } value - Brightness of the component. The value **1** indicates no effects.
     *     The value **0** indicates the complete darkness. If the value is less than **1**, the brightness
     *     decreases. If the value is greater than **1**, the brightness increases. A larger value indicates
     *     a higher brightness. A brightness of 2 turns the component completely white.
     *     <br>Default value: **1.0**<br>Recommended value range: [0, 2].
     *     <br>**NOTE**
     *     <br>A value less than 0 evaluates to the value **0**.
     *     <br>**Widget capability**: This API can be used in ArkTS widgets since API version 9.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default brightness(value: double | undefined): this;
    /**
     * Applies a contrast effect to the component.
     *
     * @param { double | undefined } value - Contrast of the component. The input parameter is a
     *     contrast value. If the value is **1**, the source image is displayed. If the
     *     value is greater than 1, a larger value indicates a higher contrast and a clearer
     *     image. If the value is less than 1, a smaller value indicates a lower contrast is.
     *     If the value is **0**, the image becomes all gray. The unit is percentage.
     *     <br>Default value: **1.0**.
     *     <br>Recommended value range: [0, 10).
     *     <br>**NOTE**
     *     <br>A value less than 0 evaluates to the value **0**.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default contrast(value: double | undefined): this;
    /**
     * Applies a grayscale effect to the component.
     *
     * @param { double | undefined } value - Grayscale conversion ratio of the component.
     *     <br>If the value is **1.0**, the component is completely converted to grayscale.
     *     <br>If the value is **0.0**, the component remains unchanged. Between **0** and **1**,
     *     <br>the value applies a linear multiplier on the grayscale effect. The unit is percentage.
     *     <br>Default value: **0.0**.
     *     <br>Value range: [0.0, 1.0].
     *     <p>**NOTE**:
     *     <br>A value less than **0.0** evaluates to the value **0.0**.
     *     <br>A value greater than **1.0** evaluates to the value **1.0**.
     *     </p>
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default grayscale(value: double | undefined): this;
    /**
     * Applies a color blend effect to the component.
     *
     * @param { Color | string | Resource | undefined } value - Color to blend with the component.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default colorBlend(value: Color | string | Resource | undefined): this;
    /**
     * Applies a saturation effect to the component.
     *
     * @param { double | undefined } value - Saturation of the component. The saturation is the ratio of the
     *     chromatic component to the achromatic component (gray) in a color. If the value is **1**,
     *     the original image is displayed. If the value is greater than **1**, a higher percentage of
     *     the chromatic component indicates a higher saturation. If the value is less than **1**, a higher
     *     percentage of the achromatic component indicates a lower saturation. The unit is percentage.
     *     <br>Default value: **1.0**.
     *     <br>Recommended value range: [0, 50).
     *     <br>**NOTE**
     *     <br>A value less than 0 evaluates to the value **0**.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default saturate(value: double | undefined): this;
    /**
     * Sepia conversion ratio of the component.
     *
     * @param { double | undefined } value - Sepia conversion ratio of the component. If the value is **1**, the image
     *     is completely sepia. If the value is **0**, the component remains unchanged. The unit is percentage.
     *     <br> Value range: [0, +∞).
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default sepia(value: double | undefined): this;
    /**
     * Invert the input image. Value defines the scale of the conversion. 100% of the value is a complete reversal.
     * A value of 0% does not change the image. (Percentage)
     *
     * @param { double | InvertOptions | undefined } value - value indicates the scale of the conversion or the options of invert.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default invert(value: double | InvertOptions | undefined): this;
    /**
     * Applies a system bar effect to the component, which means to invert colors based on the background and add a blur.
     *
     * @returns { this } return the component attribute.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default systemBarEffect(): this;
    /**
     * Rotates the hue of the component.
     *
     * @param { double | string | undefined } value - Hue rotation angle of the component.
     *     <br>A rotation of 360 degrees leaves the color unchanged.
     *     <br>A rotation of 180 degrees and then -180 degrees also leaves the color unchanged.
     *     <br>When the data type is number, the value **90** is equivalent to **'90deg'**.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default hueRotate(value: double | string | undefined): this;
    /**
     * Sets whether to draw shadows of child nodes in the component at the same layer,
     * so that the shadows of elements at the same layer overlap.
     *
     * @param { boolean | undefined } value - Whether to draw shadows of child nodes in the component
     *     at the same layer, so that the shadows of elements at the same layer overlap.
     *     <br>Default value: **false**.
     *     <br>**NOTE**
     *     <br>1. When this feature is disabled (default), if the shadow radius of a child node
     *     is large, the shadows of the child nodes may overlap. This overlap issue does not occur
     *     when the feature is enabled.
     *     <br>2. Avoid nesting **useShadowBatching**. When used in nested mode, **useShadowBatching**
     *     takes effect for the current child node only and cannot be recursively used.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default useShadowBatching(value: boolean | undefined): this;
    /**
    * Specifies whether to apply the effect defined by <!--Del-->the parent
    * [EffectComponent](ts-container-effectcomponent-sys.md) or <!--DelEnd-->the window.
    *
    * @param { boolean | undefined } useEffect - Whether to apply the effect defined by <!--Del-->the parent
    *     **EffectComponent** or <!--DelEnd-->the window.
    *     <br>The value **true** means to apply the effect defined by <!--Del-->the parent **EffectComponent**
    *     or <!--DelEnd-->the window.
    *     <br>Default value: **false**.
    * @param { EffectType | undefined } effectType - Type of effect to apply to the component, which is defined by
    *     <!--Del-->the parent **EffectComponent** or <!--DelEnd-->the window.
    *     <br>Default value: **EffectType.DEFAULT**.
    * @returns { this } return the component attribute.
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    default useEffect(useEffect: boolean | undefined, effectType: EffectType | undefined): this;
    /**
     * Specifies whether to combine the drawing of special effects, such as background blur.
     *
     * @param { boolean | undefined } value - Whether the component inherits the special effect settings of the
     *     **EffectComponent** component.<br>The value **true** means that the component inherits the
     *     special effect settings of the **EffectComponent** component, and **false** means the opposite.
     *     <br>Default value: **false**.
     * @returns { this } return the component attribute.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default useEffect(value: boolean | undefined): this;
    /**
     * Specify whether the current component participates in the fusion effect of the ancestor component
     * UnionEffectContainer
     *
     * @param { boolean | undefined } value - Whether the component participates in the fusion effect of
     *     the ancestor component **UnionEffectContainer**.<br>The value **true** means that the component participates
     *     in the fusion effect of the ancestor component **UnionEffectContainer**, and **false** means the opposite.
     *     <br>Default value: **false**. Undefined means to default value.
     * @returns { this } return the component attribute.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @systemapi
     * @stagemodelonly
     * @since 23
     */
    default useUnionEffect(value: boolean | undefined): this;
    /**
     * Adds the background blur effect for the current component. The input parameter is the blur radius.
     * The larger the blur radius, the more blurred the background. If the value is 0, the background blur is not blurred.
     *
     * @param { double | undefined } radius - radius indicates radius of backdrop blur.
     * @param { BlurOptions } [options] - options indicates the backdrop blur options.
     * @param { SystemAdaptiveOptions } [sysOptions] - system adaptive options.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default backdropBlur(radius: double | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this;
    /**
     * Sets whether the component and its child components are rendered off
     * the screen as a whole before being blended with its parent.
     *
     * @param { boolean | undefined } value - Whether the component and its child components are rendered
     *     off the screen as a whole before being blended with its parent. If the opacity of the
     *     component is not 1, the drawing effect may vary depending on the value.
     *     <br>Default value: **false**.
     *     <br> The value **true** means the component and its child components are rendered off
     *     the screen as a whole, and **false** means the opposite.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default renderGroup(value: boolean | undefined): this;
    /**
     * Set the component and its child components not to render off the screen following the parent component.
     * Must be used in conjunction with renderGroup.
     *
     * @param { boolean | undefined } exclude - Whether the component and its child components are not
     *     rendered off the screen following the parent component.
     *     True means to not follow the parent component.
     *     Default value: false.
     *     Undefined means to default value.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @systemapi
     * @stagemodelonly
     * @since 24
     */
    default excludeFromRenderGroup(exclude: boolean | undefined): this;
    /**
     * Sets whether to freeze the component. When frozen, the component and its children are cached for
     * repeated drawing after offscreen rendering, without updating internal attributes.
     *
     * @param { boolean | undefined } value - Whether to freeze the component. When frozen, the component and its children
     *     are cached for repeated drawing after offscreen rendering, without updating internal attributes. If the
     *     opacity of the component is not 1, the drawing effect may vary depending on the value.
     *     <br>Default value: **false**.
     *     <br> **true**: Freeze the component.
     *     <br>**false**: Do not freeze the component.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default freeze(value: boolean | undefined): this;
    /**
     * Sets the translation effect for page transitions.
     *
     * @param { TranslateOptions | undefined } value - Translation effect for page transitions
     *     <br>specifying the start value for entrance and the end value for exit. default:{x:0,y:0,z:0}
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default translate(value: TranslateOptions | undefined): this;
    /**
     * Scales the component.
     *
     * @param { ScaleOptions | undefined } value - Scale ratio along the x-, y-, and z-axis. The default value is **1**.
     *     <br>**centerX** and **centerY** are used to set the scale center point.
     *     <br>default:{x:1,y:1,z:1,centerX:'50%',centerY:'50%'}
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default scale(value: ScaleOptions | undefined): this;
    /**
     * Set component rotation.
     *
     * @param { RotateOptions | RotateAngleOptions |undefined } value
     *     default:{x:0,y:0,z:0,centerX:'50%',centerY:'50%',centerZ:0,perspective:0}
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default rotate(value: RotateOptions | RotateAngleOptions | undefined): this;
    /**
     * Sets the transformation matrix of the component. Set undefined value to reset the transform matrix.
     *
     * @param { Matrix4Transit | undefined } value - Transformation matrix of the component.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default transform(value: Matrix4Transit | undefined): this;
    /**
     * Sets the transformation matrix for the current component.
     * The interface can display the effect of three-dimensional natrix transformation.
     *
     * @param { Matrix4Transit | undefined } transform - transform3D natrix
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default transform3D(transform: Matrix4Transit | undefined): this;
    /**
     * This callback is triggered when a component mounts a display.
     *
     * @param { (() => void) | undefined } event
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onAppear(event: (() => void) | undefined): this;
    /**
     * This callback is triggered when component uninstallation disappears.
     *
     * @param { (() => void) | undefined } event
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onDisAppear(event: (() => void) | undefined): this;
    /**
     * This callback is triggered when a component mounts to view tree.
     *
     * @param { VoidCallback | undefined } callback
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onAttach(callback: VoidCallback | undefined): this;
    /**
     * This callback is triggered when a component is detached from view tree.
     *
     * @param { VoidCallback | undefined } callback
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onDetach(callback: VoidCallback | undefined): this;
    /**
     * This callback is triggered when the size or position of this component change finished.
     *
     * @param { ((oldValue: Area, newValue: Area) => void) | undefined } event - event callback.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onAreaChange(event: ((oldValue: Area, newValue: Area) => void) | undefined): this;
    /**
     * This callback is triggered when the size or position of this component has finished changing.
     * The interval between two area change callbacks will not be less than the expected update interval.
     *
     * @param { AreaChangeCallback } event - Callback invoked when the area of the component changes.
     * @param { AreaChangeOptions } [options] - The options for the area change event.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 26.0.0
     */
    default onAreaChange (event: AreaChangeCallback, options?: AreaChangeOptions): this;
    /**
     * Controls the display or hide of the current component.
     *
     * @param { Visibility | undefined } value - Whether the component is visible.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default visibility(value: Visibility | undefined): this;
    /**
     * Sets the percentage of the parent container's remaining space that is allocated to the component.
     * Default value: **0**.
     *
     * @param { double | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default flexGrow(value: double | undefined): this;
    /**
     * Sets the percentage of the parent container's shrink size that is allocated to the component.
     * Default value: 0 when the parent container is Column or Row, 1 when the parent container is Flex..
     *
     * @param { double | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default flexShrink(value: double | undefined): this;
    /**
     * Sets the base size of the component in the main axis of the parent container.
     * Default value: **'auto'**.
     *
     * @param { double | string | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default flexBasis(value: double | string | undefined): this;
    /**
     * Sets the alignment mode of the child components along the cross axis of the parent container.
     * Default value: **ItemAlign.Auto**.
     *
     * @param { ItemAlign | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default alignSelf(value: ItemAlign | undefined): this;
    /**
     * Defines the align rules of child component in Stack container.
     *
     * @param { LocalizedAlignment | undefined } alignment
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default layoutGravity(alignment: LocalizedAlignment | undefined): this;
    /**
     * Sets the display priority for the component in the layout container.
     * <br>This parameter is only effective in Row, Column, and Flex (single-line) container components.
     *
     * @param { double | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default displayPriority(value: double | undefined): this;
    /**
     * The sibling components in the same container are hierarchically displayed. A larger value of z indicates a higher display level.
     *
     * @param { int | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default zIndex(value: int | undefined): this;
    /**
     * If the components of the two pages are configured with the same ID.
     * The shared element transition is performed during transition.
     * If the parameter is set to an empty string, the shared element transition does not occur.
     * For details about the options parameter, see the options parameter description.
     *
     * @param { string | undefined } id - Transition of the shared element.
     *     <br>If the same **id** value is configured for a component on the two pages,
     *     <br>this component is considered as a shared element of the pages.
     *     <br>If the **id** value is an empty string, no transition will be applied to the component.
     * @param { sharedTransitionOptions } [options] - Parameters of the shared element transition animation.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default sharedTransition(id: string | undefined, options?: sharedTransitionOptions): this;
    /**
     * Sets how elements are laid out along the main axis of the container.
     * Default value: **Direction.Auto**.
     *
     * @param { Direction | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default direction(value: Direction | undefined): this;
    /**
     * Sets the alignment mode of the component content in the drawing area.
     * Default value: **Alignment.Center**.
     *
     * @param { Alignment | LocalizedAlignment | undefined } alignment
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default align(alignment: Alignment | LocalizedAlignment | undefined): this;
    /**
     * Sets the absolute position of the component relative to the position of the parent component.
     * <br>The attribute is not available for a layout container whose width and height are zero.
     *
     * @param { Position | Edges | LocalizedEdges | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default position(value: Position | Edges | LocalizedEdges | undefined): this;
    /**
     * Sets the anchor for locating the component, which is used to move the component
     * further away from the position specified by position or offset.
     *
     * @param { Position | LocalizedPosition | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default markAnchor(value: Position | LocalizedPosition | undefined): this;
    /**
     * Sets the offset of the component relative to its original position.
     * <br>The offset attribute does not affect the layout of the parent container.
     * It adjusts the component position only during drawing.
     *
     * @param { Position | Edges | LocalizedEdges | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default offset(value: Position | Edges | LocalizedEdges | undefined): this;
    /**
     * If the value is true, the component is available and can respond to operations such as clicking.
     * If it is set to false, click operations are not responded.
     *
     * @param { boolean | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default enabled(value: boolean | undefined): this;
    /**
     * Sets the alignment rules in the relative container.
     * <br>This API is valid only when the container is RelativeContainer.
     * <br>LocalizedAlignRuleOptions takes the right-to-left scripts into account, using start and end instead of
     *     left and right for alignment in the horizontal direction. Prioritize this API in aligning
     *     child components in the relative container.
     *
     * @param { AlignRuleOption | LocalizedAlignRuleOptions | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default alignRules(value: AlignRuleOption | LocalizedAlignRuleOptions | undefined): this;
    /**
     * Sets the parameters of the chain in which the component is the head.
     * <br>This parameter has effect only when the parent container is RelativeContainer.
     * <br>The chain head is the first component in the chain that satisfies the chain formation rules.
     * In a horizontal layout, it starts from the left (or from the right in a mirrored language
     * layout). In a vertical layout, it starts from the top.
     *
     * @param { Axis | undefined } direction - indicates direction of the chain
     * @param { ChainStyle | undefined } style - indicates style of the chain
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this;
    /**
     * Sets the aspect ratio of the component, which can be obtained using the following formula: width/height.
     * <br>If only width and aspectRatio are set, the height is calculated using the following formula: width/aspectRatio.
     * <br>If only height and aspectRatio are set, the width is calculated using the following formula: height x aspectRatio.
     * <br>If width, height, and aspectRatio are all set, the explicitly set height is ignored, and the effective height is
     * calculated using the following formula: width/aspectRatio.
     * <br>This parameter takes effect only when a valid value greater than 0 is specified.
     *
     * @param { double | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default aspectRatio(value: double | undefined): this;
    /**
     * The click effect level and scale number.
     *
     * @param { ClickEffect | null | undefined } value
     * @returns { this } return the component attribute.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default clickEffect(value: ClickEffect | null | undefined): this;
    /**
     * Set whether this component should have sound effects enabled for clicking.
     *
     * Sound effects playback is affected by the audio-related settings in the device system settings.
     * When the user sets the device to silent mode, sound effects cannot be played.
     *
     * @param { boolean | undefined } enabled - indicates whether this component should have sound effects
     *     enabled for clicking.
     *     <br>Pass in undefined to reset the default value, default value is true, but
     *     even it's true, the sound effect is only supported in some specific devices.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    default enableClickSoundEffect(enabled: boolean | undefined): this
    /**
     * After a listener is bound, the component can be dragged. After the drag occurs, a callback is triggered.
     * (To be triggered, press and hold for 170 milliseconds (ms))
     *
     * <strong>NOTE</strong>:<br>
     * The global builder is not supported.
     *
     * @param { ((event: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo) | undefined } event
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onDragStart(event: ((event: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo) | undefined): this;
    /**
     * After binding, a callback is triggered when the component is dragged to the range of the component.
     *
     * @param { ((event: DragEvent, extraParams?: string) => void) | undefined } event
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onDragEnter(event: ((event: DragEvent, extraParams?: string) => void) | undefined): this;
    /**
     * After binding, a callback is triggered when the drag moves within the range of a placeable component.
     *
     * @param { ((event: DragEvent, extraParams?: string) => void) | undefined } event
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onDragMove(event: ((event: DragEvent, extraParams?: string) => void) | undefined): this;
    /**
     * After binding, a callback is triggered when the component is dragged out of the component range.
     *
     * @param { ((event: DragEvent, extraParams?: string) => void) | undefined } event
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onDragLeave(event: ((event: DragEvent, extraParams?: string) => void) | undefined): this;
    /**
     * The component bound to this event can be used as the drag release target.
     * This callback is triggered when the drag behavior is stopped within the scope of the component.
     *
     * @param { ((event: DragEvent, extraParams?: string) => void) | undefined } event
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onDrop(event: ((event: DragEvent, extraParams?: string) => void) | undefined): this;
    /**
     * The component bound to this event can be used as the drag release target.
     * This callback is triggered when the drag behavior is stopped within the scope of the component.
     *
     * @param { OnDragEventCallback | undefined } eventCallback - event callback.
     * @param { DropOptions } dropOptions - the drop handling options.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onDrop(eventCallback: OnDragEventCallback | undefined, dropOptions: DropOptions): this;
    /**
     * Enables the component as a drag-and-drop target with spring loading functionality.
     *
     * When a dragged object hovers over the target, it triggers a callback notification. Spring Loading is an enhanced
     * feature for drag-and-drop operations, allowing users to automatically trigger view transitions during dragging
     * by hovering (hover) without needing to use another hand.
     * This feature is primarily designed to enhance the smoothness and efficiency of drag-and-drop operations. Below are
     * some common scenarios suitable for supporting this feature:
     *  - In a file manager, when dragging a file and hovering over a folder, the folder is automatically opened.
     *  - On a desktop launcher, when dragging a file and hovering over an application icon, the application is
     *  automatically opened.
     *
     * @param { Callback<SpringLoadingContext> | null | undefined } callback Registers the callback for spring loading response, or
     *    sets it to null to disable the support for spring loading.
     * @param { DragSpringLoadingConfiguration } [configuration] The initialized spring loading configuration which is
     *    only used when the entire spring detecting.
     * @returns { this } - return the component attribute.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    default onDragSpringLoading(callback: Callback<SpringLoadingContext> | null | undefined, configuration?: DragSpringLoadingConfiguration): this;
    /**
     * This function is called when the drag event is end.
     *
     * @param { ((event: DragEvent, extraParams?: string) => void) | undefined } event - indicates the function to be called.
     * @returns { this } return the component attribute.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onDragEnd(event: ((event: DragEvent, extraParams?: string) => void) | undefined): this;
    /**
     * Allowed drop uniformData type for this node.
     *
     * @param { Array<UniformDataType> | null | Array<string> | undefined } value - the uniformData type for this node.
     * @returns { this } - return the component attribute.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default allowDrop(value: Array<UniformDataType> | null | Array<string> | undefined): this;
    /**
     * Enable the selectable area can be dragged.
     *
     * @param { boolean | undefined } value - true means the area can be dragged, false means the area can't be dragged.
     *     The default value is false.
     * @returns { this } return the component attribute.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default draggable(value: boolean | undefined): this;
    /**
     * Set preview of the component for dragging process
     *
     * @param { CustomBuilder | DragItemInfo | string | undefined } preview - preview of the component for dragging process
     * @param { PreviewConfiguration } [config] - drag preview configuration.
     * @returns { this } return the component attribute.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default dragPreview(preview: CustomBuilder | DragItemInfo | string | undefined, config?: PreviewConfiguration): this;
    /**
     * Set the selectable area drag preview options.
     *
     * @param { DragPreviewOptions | undefined } value - preview options value.
     * @param { DragInteractionOptions } [options] - drag interaction options value.
     * @returns { this } return the component attribute.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default dragPreviewOptions(value: DragPreviewOptions | undefined, options?: DragInteractionOptions): this;
    /**
     * After binding, a callback is triggered when the preDrag status change finished.
     *
     * @param { Callback<PreDragStatus> | undefined } callback callback - The callback will be triggered when the preDrag status change.
     * @returns { this } return the component attribute.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onPreDrag(callback: Callback<PreDragStatus> | undefined): this;
    // instructive change start
    default toolbar(value: CustomBuilder | undefined): this;
    // instructive change end
    /**
     * Add mask text to the current component. The layout is the same as that of the current component.
     *
     * @param { string | CustomBuilder | ComponentContent<T> | undefined } value
     * @param { OverlayOptions } [options]
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    /**
     * Add mask text to the current component. The layout is the same as that of the current component.
     *
     * @param { string | CustomBuilder | ComponentContent<Object> | undefined } value
     * @param { OverlayOptions } [options]
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 26.0.0
     */
    default overlay(value: string | CustomBuilder | ComponentContent<Object> | undefined, options?: OverlayOptions): this;
    /**
     * Linear Gradient
     * angle: Angle of Linear Gradient. The default value is 180;
     * direction: Direction of Linear Gradient. The default value is GradientDirection.Bottom;
     * colors: Color description for gradients.
     * repeating: repeating. The default value is false
     *
     * @param { LinearGradientOptions | undefined } value - Linear gradient.
     *     <br>If **options** is **undefined**, the linear gradient is disabled.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default linearGradient(value: LinearGradientOptions | undefined): this;
    /**
     * Creates a sweep gradient.
     *
     * @param { SweepGradientOptions | undefined } value - Sweep gradient, which can sweep around the specified
     *     center point in the 0–360 degree range. If the rotation angle exceeds the range, a monochrome
     *     color instead of a gradient will be drawn.<br>- **center**: center of the sweep gradient, that
     *     is, the coordinates relative to the upper left corner of the current component.
     *     <br>- **start**: start angle of the sweep gradient.
     *     <br> Default value: **0**<br>If the angle is specified with a string, only the deg, grad, rad,
     *     and turn types are supported.<br>- **end**: end angle of the sweep gradient.
     *     <br> Default value: **0**<br>If the angle is specified with a string, only the deg, grad, rad,
     *     and turn types are supported.<br>- **rotation**: rotation angle of the sweep gradient.
     *     <br> Default value: **0**<br>If the angle is specified with a string, only the deg, grad, rad,
     *     and turn types are supported.<br>- colors: array of color stops,
     *     each of which consists of a color and its stop position. Invalid colors are automatically skipped.
     *     <br>- **repeating**: whether the colors are repeated.
     *     <br>  Default value: **false**.
     *     <br>**NOTE**
     *     <br>A value less than 0 is treated as **0**. A value greater than 360 is treated as **360**.
     *     <br>When **start**, **end**, or **rotation** is specified with a string, the string must be a number
     *     or a number followed by one of the following units: deg, rad, grad, and turn. Valid value examples
     *     are "90", "90deg", and "1.57rad".
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default sweepGradient(value: SweepGradientOptions | undefined): this;
    /**
     * Creates a radial gradient.
     *
     * Anonymous Object Rectification.
     * @param { RadialGradientOptions | undefined } value - Radial gradient.
     *     <br>- **center**: center of the radial gradient, that is, the coordinates relative
     *     to the upper left corner of the current component.
     *     <br>- **radius**: radius of the radial gradient.
     *     <br> Value range: [0, +∞).
     *     <br>**NOTE**
     *     <br>A value less than 0 is treated as **0**.
     *     <br>- colors: array of color stops, each of which consists
     *     of a color and its stop position. Invalid colors are automatically skipped.
     *     <br>- **repeating**: whether the colors are repeated.
     *     <br>  Default value: **false**.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default radialGradient(value: RadialGradientOptions | undefined): this;
    /**
     * Set the motion path of the component.
     *
     * @param { MotionPathOptions | undefined } value - Motion path of the component.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default motionPath(value: MotionPathOptions | undefined): this;
    /**
     * Applies a shadow effect to the component.
     *
     * @param { ShadowOptions | ShadowStyle | undefined } value - Shadow of the component.
     *     <br>When the value type is **ShadowOptions**, the blur radius, shadow color,
     *     and offset along the x-axis and y-axis can be specified.
     *     <br>When the value type is **ShadowStyle**, the shadow style can be specified.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default shadow(value: ShadowOptions | ShadowStyle | undefined): this;
    /**
     * Defines how the component's content (including the content of it child components)
     * is blended with the existing content on the canvas (possibly offscreen canvas) below.
     *
     * @param { BlendMode | undefined } value - Blend mode.
     *     <br>Default value: **BlendMode.NONE**.
     *     <br>**NOTE**
     *     <br>When **BlendMode.NONE** is used, the blend effect is **BlendMode.SRC_OVER**
     *     by default, and **BlendApplyType** does not take effect.
     * @param { BlendApplyType } [type] - Whether the blend mode is implemented offscreen.
     *     <br>Default value: **BlendApplyType.FAST**.
     *     <br>**NOTE**
     *     <br>1. **BlendApplyType.FAST**: The blend mode is not implemented offscreen.
     *     <br>2. **BlendApplyType.OFFSCREEN**: An offscreen canvas of the size of the current component
     *     is created. The content of the current component (including child components) is then drawn
     *     onto the offscreen canvas, and blended with the existing content on the canvas below using
     *     the specified blend mode. This approach may cause issues with screen capture for APIs such
     *     as linearGradientBlur<sup>12+</sup>, backgroundEffect, and brightness.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default blendMode(value: BlendMode | undefined, type?: BlendApplyType): this;


    /**
     * Add a blendMode effect to the current component.Cannot be used together with the blendMode interface.
     *
     * @param { BlendMode | Blender | undefined } effect - When the effect type is BlendMode type, define Different hybrid modes.
     * @param { BlendApplyType } [type] - Different blend apply type
     *     Default value: BlendApplyType.FAST.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @systemapi
     * @since 23
     */
    default advancedBlendMode(effect: BlendMode | Blender | undefined, type?: BlendApplyType): this;
    /**
     * Sets whether to clip the areas of child components that extend beyond this component's boundaries,
     * That is, whether to perform clipping based on the edge contour of the parent container.
     *
     * @param { boolean | undefined } value - Whether to perform clipping based on the edge contour of the parent container.
     *     <br>Default value: **false**.
     *     <br>**true**: Perform clipping. **false**: Do not perform clipping.
     *     <br>If this parameter is set to **true**.
     *     <br>child components exceeding the current component's bounds will not respond to bound gesture events.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default clip(value: boolean | undefined): this;
    /**
    * Clips this component based on the given shape.
    *
    * @param { CircleShape | EllipseShape | PathShape | RectShape | undefined } value - Shape that the
    *     component to be clipped into. The clipped area remains responsive to bound gesture events.
    * @returns { this }
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    default clipShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this;
    /**
     * Adds a mask to the component to indicate the progress.
     *
     * @param { ProgressMask | undefined } value - Mask to add to the component, which allows for dynamic
     *     adjustment of progress, maximum value, and color settings.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default mask(value: ProgressMask | undefined): this;
    /**
     * Adds a mask of the specified shape to the component.
     *
     * @param { CircleShape | EllipseShape | PathShape | RectShape | undefined } value - Mask of the specified
     *     shape to add to the component.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default maskShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this;
    /**
     * Key. User can set an key to the component to identify it.
     *
     * @param { string | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     * @test
     */
    default key(value: string | undefined): this;
    /**
     * Id. User can set an id to the component to identify it.
     *
     * @param { string | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default id(value: string | undefined): this;
    /**
     * Shared geometry transition
     *
     * @param { string | undefined } id - geometry transition id
     * @param { GeometryTransitionOptions } [options] - Indicates the options of geometry transition.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default geometryTransition(id: string | undefined, options?: GeometryTransitionOptions): this;
    /**
    * Tips control
    *
    * @param { TipsMessageType | undefined } message
    * @param { TipsOptions } [options]
    * @returns { this }
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    default bindTips(message: TipsMessageType | undefined, options?: TipsOptions): this;
    /**
     * Popup control
     * <p><strong>NOTE</strong>:
     * <br>The popup can be displayed only after the entire page is fully constructed. Therefore, to avoid incorrect
     * display positions and shapes, do not set this parameter to true while the page is still being constructed.
     * </p>
     *
     * @param { boolean | undefined } show - Whether to show the popup, default is false.
     * @param { PopupOptions | CustomPopupOptions | undefined } popup
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default bindPopup(show: boolean | undefined, popup: PopupOptions | CustomPopupOptions | undefined): this;
    /**
     * Menu control
     *
     * @param { Array<MenuElement> | CustomBuilder | undefined } content - Indicates the content of menu.
     * @param { MenuOptions } [options] - Indicates the options of menu.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default bindMenu(content: Array<MenuElement> | CustomBuilder | undefined, options?: MenuOptions): this;
    /**
     * Menu control
     *
     * @param { boolean | Bindable<boolean> | undefined } isShow - Menu display switch,
     *     supports incoming two-way binding parameters.
     *     true means display menu, false means hide menu, default is false.
     * @param { Array<MenuElement> | CustomBuilder | undefined } content - Indicates the content of menu.
     * @param { MenuOptions } [options] - Indicates the options of menu.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    default bindMenu(isShow: boolean | Bindable<boolean> | undefined, content: Array<MenuElement> | CustomBuilder | undefined, options?: MenuOptions): this;
    /**
     * Binds a context menu to this component, which is displayed when the user long-presses or right-clicks the
     * component. Only custom menu items are supported.
     *
     * @param { CustomBuilder | undefined } content - Indicates the content of context menu.
     * @param { ResponseType | undefined } responseType - Indicates response type of context menu, Long
     *     pressing with a mouse device is not supported.
     * @param { ContextMenuOptions } [options] - Indicates the options of context menu.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default bindContextMenu(content: CustomBuilder | undefined, responseType: ResponseType | undefined, options?: ContextMenuOptions): this;
    /**
     * Binds a context menu to this component, which is displayed when the user long-presses or right-clicks the
     * component. Only custom menu items are supported. Long pressing with a mouse device is not supported.
     *
     * @param { CustomBuilderT<ResponseType> | undefined } content - Indicates the content of context menu. Undefined
     *     means unbinding.
     * @param { ContextMenuOptions } [options] - Indicates the options of context menu.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    default bindContextMenuWithResponse(content: CustomBuilderT<ResponseType> | undefined, options?: ContextMenuOptions): this;
    /**
     * Binds a context menu to the component, whose visibility is subject to the isShow settings.
     *
     * @param { boolean | Bindable<boolean> | undefined } isShow - Menu display switch,
     *     supports incoming twoway binding parameters.
     *     true means display content, false means hide content, default is false.
     *     <p><strong>NOTE</strong>:
     *     <br>The menu can be displayed properly only when the related page has been constructed. If this parameter is set
     *     to true before the construction is complete, display issues, such as misplacement, distortion, or failure to pop
     *     up, may occur. To trigger dragging by long presses is not supported.
     *     </p>
     * @param { CustomBuilder | undefined } content - Indicates the content of context menu.
     * @param { ContextMenuOptions } [options] - Indicates the options of context menu.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    default bindContextMenu(isShow: boolean | Bindable<boolean> | undefined, content: CustomBuilder | undefined, options?: ContextMenuOptions): this;
    /**
     * Binds a modal page to the component, whose visibility is subject to the isShow settings.
     *
     * @param { boolean | Bindable<boolean> | undefined } isShow - true means display content, false means hide content.
     * @param { CustomBuilder | undefined } builder - the content to be displayed.
     * @param { ModalTransition } [type] - transition type.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default bindContentCover(isShow: boolean | Bindable<boolean> | undefined, builder: CustomBuilder | undefined, type?: ModalTransition): this;
    /**
     * Bind content cover
     *
     * @param { boolean | Bindable<boolean> | undefined } isShow - true means display content, false means hide content.
     * @param { CustomBuilder | undefined } builder - the content to be displayed.
     * @param { ContentCoverOptions } [options] - options of content cover.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default bindContentCover(isShow: boolean | Bindable<boolean> | undefined, builder: CustomBuilder | undefined, options?: ContentCoverOptions): this;
    /**
     * Bind sheet
     *
     * @param { boolean | Bindable<boolean> | undefined } isShow - true means display sheet, false means hide sheet.
     * @param { CustomBuilder | undefined } builder - the sheet to be displayed.
     * @param { SheetOptions } [options] - options of sheet.
     * @returns { this } - return the component attribute.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default bindSheet(isShow: boolean | Bindable<boolean> | undefined, builder: CustomBuilder | undefined, options?: SheetOptions): this;
    /**
     * Sets styles for component state.
     *
     * @param { StateStyles | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default stateStyles(value: StateStyles | undefined): this;
    /**
     * id for distribute identification.
     *
     * @param { int | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default restoreId(value: int | undefined): this;
    /**
     * Trigger a visible area change event.
     *
     * @param { Array<double> | undefined } ratios - Threshold array. Each threshold represents a ratio of the
     *     component's visible area to the component's total area. The value range of the threshold is [0.0, 1.0].
     * @param { VisibleAreaChangeCallback | undefined } event - Callback for visible area changes of the component.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    default onVisibleAreaChange(ratios: Array<double> | undefined, event: VisibleAreaChangeCallback | undefined): this;
    /**
     * Set or reset the callback which is triggered when the visibleArea of component changed.
     * The interval between two visible area change callbacks will not be less than the expected update interval.
     *
     * @param { VisibleAreaEventOptions | undefined } options - The options for the visibility event.
     * @param { VisibleAreaChangeCallback | undefined } event - The callback will be triggered when the visibleArea of component changed and get close to any number in ratios defined by options.
     *     If set undefined will reset the target callback.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onVisibleAreaApproximateChange(options: VisibleAreaEventOptions | undefined, event: VisibleAreaChangeCallback | undefined): this;
    /**
     * Applies a spherical effect to the component.
     *
     * @param { double | undefined } value - Spherical degree of the component.
     *     <br>The value ranges from 0 to 1.
     *     <p>**NOTE**:
     *     <br>1. If the value is **0**, the component remains unchanged. If the value is 1, the component is completely
     *     spherical. Between **0** and **1**, a larger value indicates a higher spherical degree. A value less than 0 is
     *     handled as the value **0**. A value greater than 1 is handled as the value **1**.
     *     <br>2. The component's shadow and outer stroke do not support spherical effects.
     *     <br>3. If the value is greater than 0, the component is frozen and not updated, and its content is drawn to the
     *     transparent offscreen buffer. To update the component attributes, set the value to **0**.
     *     </p>
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default sphericalEffect(value: double | undefined): this;
    /**
     * Applies a light up effect to the component.
     *
     * @param { double | undefined } value - Light up degree of the component.
     *     <br>The value ranges from 0 to 1.
     *     <br>If the value is **0**, the component is dark. If the value is **1**, the component is fully illuminated.
     *     <br>Between **0** and **1**, a larger value indicates higher luminance.
     *     <br>A value less than 0 is handled as the value **0**.
     *     <br>A value greater than 1 is handled as the value **1**.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default lightUpEffect(value: double | undefined): this;
    /**
     * Applies a pixel stretch effect to the component.
     *
     * @param { PixelStretchEffectOptions | undefined } options - Pixel stretch effect options.
     *     <br>The value includes the length by which a pixel is stretched toward the four edges.
     *     <p>**NOTE**:
     *     <br>1. If the length is a positive value, the original image is stretched, and the image size increases. The edge
     *     pixels grow by the set length toward the top, bottom, left, and right edges.
     *     <br>2. If the length is a negative value, the original image shrinks as follows, but the image size remains
     *     unchanged:
     *     <br>Shrinking mode:
     *     <br>(1) The image shrinks from the four edges by the absolute value of length set through **options**.
     *     <br>(2) The image is stretched back to the original size with edge pixels.
     *     <br>3. Constraints on **options**:
     *     <br>(1) The length values for the four edges must be all positive or all negative. That is, the four edges are
     *     stretched or shrink at the same time in the same direction.
     *     <br>(2) The length values must all be a percentage or a specific value. Combined use of the percentage and
     *     specific value is not allowed.
     *     <br>(3) If the input value is invalid, the image is displayed as {0, 0, 0, 0}, that is, the image is the same as
     *     the original image.
     *     </p>
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default pixelStretchEffect(options: PixelStretchEffectOptions | undefined): this;
    /**
     * Sets hot keys
     *
     * @param { string | FunctionKey | undefined } value - Character of the combination key.
     * @param { Array<ModifierKey> | undefined } keys - The modifier keys modify the action of key when the key are pressed at the same time.
     * @param { function } [action] - Callback function, triggered when the shortcut keyboard is pressed.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default keyboardShortcut(value: string | FunctionKey | undefined, keys: Array<ModifierKey> | undefined, action?: () => void): this;
    /**
     * Sets whether to enable accessibility grouping.
     *
     * <p><strong>NOTE</strong>
     * <br>Whether to enable accessibility grouping. When accessibility grouping is enabled,
     * <br>the component and all its children are treated as a single selectable unit, and the accessibility
     * <br>service will no longer focus on the individual child components.
     *
     * <br>If accessibility grouping is enabled and the component does not contain a universal text attribute
     * <br>or an accessibility text attribute, the system will concatenate the universal text attributes of
     * <br>its child components to form a merged text for the component. If a child component lacks a universal
     * <br>text attribute, it will be ignored in the concatenation process.
     *
     * <br>When accessibilityPreferred is set to true, the system will prioritize concatenating the accessibility
     * <br>text attributes of the child components to form the merged text. If a child component lacks an
     * <br>accessibility text attribute, the system will continue to concatenate its universal text attribute.
     * <br>If a child component lacks both, it will be ignored.</p>
     *
     * @param { boolean | undefined } isGroup - set group with accessibility, default value is false.
     * @param { ?AccessibilityOptions } [accessibilityOptions] - options for accessibility, default value is false.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default accessibilityGroup(isGroup: boolean | undefined, accessibilityOptions?: AccessibilityOptions): this;
    /**
     * Sets accessibility next focus id
     * @param { string | undefined } nextId - set component next accessibility focus id
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default accessibilityNextFocusId(nextId: string | undefined): this;
    /**
     * Sets the accessibility default foucs flag
     * @param { boolean | undefined } focus - if the component is accessibility default focus,focus set true
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default accessibilityDefaultFocus(focus: boolean | undefined): this;
    /**
     * Sets accessibility same page mode
     * @param { AccessibilitySamePageMode | undefined } pageMode - accessibility same page mode
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default accessibilityUseSamePage(pageMode: AccessibilitySamePageMode | undefined): this;
    /**
     * Sets accessibilityScrollTriggerable
     * @param { boolean | undefined } isTriggerable - set property of supporting scroll in accessibility
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default accessibilityScrollTriggerable(isTriggerable: boolean | undefined): this;
    /**
     * Sets the accessibility text.
     * <p><strong>NOTE</strong>
     * <br>When a component does not contain a text attribute, you can use this API to set an accessibility
     * <br>text attribute, so that accessibility services can announce the specified content for the component.
     * <br>If a component has both text content and accessibility text, only the accessibility text is announced.
     * <br>If a component is grouped for accessibility purposes but lacks both text content and accessibility
     * <br>text, the screen reader will concatenate text from its child components (depth-first traversal).
     * <br>To prioritize accessibility text concatenation, set accessibilityPreferred in accessibilityGroup.
     * </p>
     * @param { Resource | string | undefined } text - set accessibility text, default value is "".
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default accessibilityText(text: Resource | string | undefined): this;
    /**
     * Sets accessibility role,role indicates the custom type of the component
     * @param { AccessibilityRoleType | undefined } role - set accessibility component type
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default accessibilityRole(role: AccessibilityRoleType | undefined): this;
    /**
     * Register accessibility focus callback,when the component is focused or out of focus,the callback will be executed
     * @param { AccessibilityFocusCallback | undefined } callback - accessibility focus callback function
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onAccessibilityFocus(callback: AccessibilityFocusCallback | undefined): this;
    /**
     * Register accessibility action intercept callback,
     * when accessibility action is to be executed,the callback will be executed
     * @param { AccessibilityActionInterceptCallback | undefined } callback - accessibility action intercept callback function
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onAccessibilityActionIntercept(callback: AccessibilityActionInterceptCallback | undefined): this;
    /**
     * Sets accessibilityTextHint
     *
     * @param { string | undefined } value - set accessibility text hint
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default accessibilityTextHint(value: string | undefined): this;
    /**
     * Sets accessibilityDescription
     *
     * with support for resource references using Resource.
     * This property provides additional context or explanation for the component,
     * helping users understand the action or function it performs.
     * <p><strong>NOTE</strong>:
     * <br>Reference resource of the accessibility description. You can specify further explanation
     * <br>of the current component, for example, possible operation consequences, especially those that
     * <br>cannot be learned from component attributes and accessibility text. If a component contains
     * <br>both text information and the accessibility description, the text is read first and then the
     * <br>accessibility description, when the component is selected.</p>
     * @param { Resource | string | undefined } description - set description of accessibility, default value is "".
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default accessibilityDescription(description: Resource | string | undefined): this;
    /**
     * Sets the accessibility level.
     * This property determines whether the component can be recognized by accessibility services.
     * <p>
     * Accessibility level, which is used to decide whether a component can be identified by the accessibility service.
     * <br>The options are as follows:
     * <br>"auto": The component's recognizability is determined by the accessibility grouping service and ArkUI.
     * <br>"yes": The component can be recognized by accessibility services.
     * <br>"no": The component cannot be recognized by accessibility services.
     * <br>"no-hide-descendants": Neither the component nor its child components can be recognized by accessibility services.
     * <strong>NOTE</strong>
     * <br>When accessibilityLevel is set to "auto", the component's recognizability depends on the following factors:
     * <br>1. The accessibility service internally determines whether the component can be recognized.
     * <br>2. If the parent component's accessibilityGroup property has isGroup set to true, the accessibility service will
     * <br>not focus on its child components, making them unrecognizable.
     * <br>3. If the parent component's accessibilityLevel is set to "no-hide-descendants", the component will not be
     * <br>recognized by accessibility services.</p>
     * @param { string | undefined } value - set accessibility level, default value is auto.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default accessibilityLevel(value: string | undefined): this;
    /**
     * Sets accessibilityVirtualNode
     *
     * @param { CustomBuilder | undefined } builder - set virtual node of accessibility
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
   default accessibilityVirtualNode(builder: CustomBuilder | undefined): this;
    /**
     * Sets accessibilityChecked
     *
     * @param { boolean | undefined } isCheck - set accessibility checked status
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default accessibilityChecked(isCheck: boolean | undefined): this;
    /**
     * Sets accessibilitySelected
     *
     * @param { boolean | undefined } isSelect - set accessibility selected status
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default accessibilitySelected(isSelect: boolean | undefined): this;
    /**
     * Sets obscured
     *
     * @param { Array<ObscuredReasons> | undefined } reasons - reasons of obscuration
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default obscured(reasons: Array<ObscuredReasons> | undefined): this;
    /**
     * Reuse id is used for identify the reuse type for each custom node.
     *
     * @param { string | undefined } id - The id for reusable custom node.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default reuseId(id: string | undefined): this;
    /**
    * Reuse id is used for identify the reuse type of each @ComponentV2 custom component, which can give user control of sub-component recycle and reuse.
    *
    * @param { ReuseOptions | undefined } options - The configuration parameter for reusable custom component.
    * @returns { this }
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    default reuse(options: ReuseOptions | undefined): this;
    /**
     * How the final state of the component's content is rendered during its width and height animation process.
     *
     * @param { RenderFit | undefined } fitMode - How the final state of the component's content is rendered during.
     *     <br>its width and height animation process.
     *     <br>If **renderFit** is not set, the default value **RenderFit.TOP_LEFT** is used.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default renderFit(fitMode: RenderFit | undefined): this;
    /**
     * Sets the gesture modifier.
     *
     * @param { GestureModifier | undefined } modifier
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default gestureModifier(modifier: GestureModifier | undefined): this;
    /**
     * Sets the background brightness of the component.
     *
     * @param { BackgroundBrightnessOptions | undefined } params - Parameters for setting the background brightness.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default backgroundBrightness(params: BackgroundBrightnessOptions | undefined): this;
    /**
     * When a gesture bound to this component will be accepted, a user-defined callback is triggered to get the result
     *
     * @param { ((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult) | undefined } callback - A callback
     *     instance used when a gesture bound to this component will be accepted.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onGestureJudgeBegin(callback: ((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult) | undefined): this;
    /**
     * Binds a custom gesture recognizer judgment callback to the component.
     *
     * @param { GestureRecognizerJudgeBeginCallback | undefined } callback - A callback instance used when
     *     a gesture bound to this component will be accepted.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onGestureRecognizerJudgeBegin(callback: GestureRecognizerJudgeBeginCallback | undefined): this;
    /**
     * Binds a custom gesture recognizer judgment callback to the component.
     *
     * <p><strong>NOTE</strong>:
     * <br> For a composite component, setting exposeInnerGesture to true exposes the internal gesture recognizer of the
     * <br> composite component in the current parameter callback. Currently, only the Tabs component is supported.
     *
     * <br> Do not set exposeInnerGesture for other components. When exposeInnerGesture is set to false, this API
     * provides the same functionality
     * <br> as the onGestureRecognizerJudgeBegin API.
     * </p>
     * @param { GestureRecognizerJudgeBeginCallback | undefined } callback - A callback instance used when a gesture
     *     bound to this component will be accepted.
     * @param { boolean | undefined } exposeInnerGesture - This parameter is a flag. This flag determines whether to
     *     expose internal gestures.
     * @default false
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onGestureRecognizerJudgeBegin(callback: GestureRecognizerJudgeBeginCallback | undefined, exposeInnerGesture: boolean | undefined): this;
    /**
     * Provides a callback to set the parallel relationship between built-in gestures and gestures of other components in the response chain.
     *
     * @param { ShouldBuiltInRecognizerParallelWithCallback | undefined } callback - A callback instance used when
     *     a component is doing touch test.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default shouldBuiltInRecognizerParallelWith(callback: ShouldBuiltInRecognizerParallelWithCallback | undefined): this;
    /**
     * Sets whether the component exclusively handles events.
     * true: The component exclusively handles events. false: The component does not exclusively handle events.
     *
     * @param { boolean | undefined } monopolize - indicate the monopoly of events
     * @default false
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default monopolizeEvents(monopolize: boolean | undefined): this;
    /**
     * When the component does a touch test, a user-defined callback is triggered.
     *
     * @param { Callback<TouchEvent, HitTestMode> | undefined } callback - A callback instance used when the component does a touch test.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onTouchIntercept(callback: Callback<TouchEvent, HitTestMode> | undefined): this;
    /**
     * This callback is triggered when the component size changes due to layout updates.
     * This event is not triggered for render attribute changes caused by re-rendering.
     *
     * @param { SizeChangeCallback | undefined } event - event callback.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onSizeChange(event: SizeChangeCallback | undefined): this;
    /**
     * Accessibility focus draw level, and the default value is FocusDrawLevel.SELF.
     *
     * @param { FocusDrawLevel | undefined } drawLevel - indicates accessibility focus draw level.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default accessibilityFocusDrawLevel(drawLevel: FocusDrawLevel | undefined): this;
    /**
     * Register one callback which will be executed when all gesture recognizers are collected done, this happens
     * when user touchs down, the system do hit test process and collect gesture recognizers base on the touch
     * position, after this, before handling any move events, the component can use this interface to know which
     * gesture recognizers will participate in the recognition and competing with each other.
     *
     * @param { TouchTestDoneCallback | undefined } callback - A callback instance used when all gesture recognizers
     *     are collected.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onTouchTestDone(callback: TouchTestDoneCallback | undefined): this;
    /**
     * When the events and gestures on this node and higher-priority nodes have been collected, the callback is executed.
     * This callback is used to intervene in the event and gesture collection results.
     *
     * @param { GestureCollectInterceptCallback } callback - A callback instance used when the component does a touch test.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 26.0.0
     */
    default onGestureCollectIntercept(callback: GestureCollectInterceptCallback): this;
    /**
     * Set system-styled materials for the component. Different materials have different effects, which can influence
     * the backgroundColor, border, shadow, and other visual attributes of the component.
     *
     * Device Behavior Differences:The effect of the same material may vary across different devices depending on
     * their computing power.
     *
     * @param { SystemUiMaterial | undefined } material - System-styled material. Undefined indicates reverting to
     *     the effect of no system material.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @systemapi
     * @stagemodelonly
     * @since 23
     */
    default systemMaterial(material: SystemUiMaterial | undefined): this;
    /**
     * Called when component is focused, the return value indicates whether keyboard is needed.
     *
     * @param { OnNeedSoftkeyboardCallback | undefined } onNeedSoftkeyboardCallback
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    default onNeedSoftkeyboard(onNeedSoftkeyboardCallback: OnNeedSoftkeyboardCallback | undefined): this;
    /**
     * Sets the state anouncement text of the component under accessibility.
     *
     * @param { string | Resource | undefined } description the state anouncement text of the component under accessibility.
     *     if incoming is undefined, it will be processed as empty string.
     * @returns { this } return component instance who call the method.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default accessibilityStateDescription(description: string | Resource | undefined): this;
    /**
     * Sets AccessibilityActionOptions that can affect operation under accessibility.
     *
     * @param { AccessibilityActionOptions | undefined } option - set accessibility specific operation options.
     * @returns { this } return component instance who call the method.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default accessibilityActionOptions(option: AccessibilityActionOptions | undefined): this;
    /**
     * Set the component's source code redirection information. 
     * @param { string } sourceLine - the source code line.
     * @param { string } [moduleName] - module to which the component belongs.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    default debugLine(sourceLine: string, moduleName?: string): this;
}
/**
 * CommonAttribute for ide.
 *
 * @typedef  { CommonMethod } CommonAttribute
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type CommonAttribute = CommonMethod;
/**
 * Defines the OverlayOptions interface.
 *
 * <strong>NOTE</strong>:<br>
 * When both align and offset are set, the effects are combined.
 * The overlay is first aligned relative to the component and then offset from its current upper left corner.
 *
 * @typedef OverlayOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface OverlayOptions {
    /**
     * Defines align type.
     *
     * @type { ?Alignment }
     * @default TopStart
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    align?: Alignment;
    /**
     * Defines offset type.
     *
     * @type { ?OverlayOffset }
     * @default - the overlay is in the upper left corner of the component.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    offset?: OverlayOffset;
}
/**
 * Defines the OverlayOffset.
 *
 * @typedef OverlayOffset
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface OverlayOffset {
    /**
     * Defines x.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    x?: double;
    /**
     * Defines y.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    y?: double;
}
/**
 * Defines the segment of blur.
 * The first element in the tuple means fraction.
 * The range of this value is [0,1]. A value of 1 means opaque and 0 means completely transparent.
 * The second element means the stop position.
 * The range of this value is [0,1]. A value of 1 means region ending position and 0 means region starting position.
 *
 * @typedef { [ double, double ] } FractionStop
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type FractionStop = [
    double,
    double
];

/**
 * CommonShapeMethod
 *
 * @extends CommonMethod
 * @interface CommonShapeMethod
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 * @noninterop
 */
export declare interface CommonShapeMethod extends CommonMethod {
    /**
     * Sets the stroke color.
     * If this attribute is not set, the component does not have any stroke.
     * If the value is invalid, no stroke will be drawn.
     *
     * @param { ResourceColor | undefined } value - Stroke color.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default stroke(value: ResourceColor | undefined): this;
    /**
     * Sets the color of the fill area.
     * An invalid value is handled as the default value.
     * If this attribute and the universal attribute foregroundColor are both set, whichever is set later takes effect.
     *
     * @param { ResourceColor | undefined } value - Color of the fill area. Default value: Color.Black.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default fill(value: ResourceColor | undefined): this;
    /**
     * Sets the offset of the start point for drawing the stroke.
     * An invalid value is handled as the default value.
     *
     * @param { double | string | undefined } value - Offset of the start point for drawing the stroke.
     *     Default value: 0
     *     Default unit: vp
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default strokeDashOffset(value: double | string | undefined): this;
    /**
     * Sets the cap style of the stroke.
     *
     * @param { LineCapStyle | undefined } value - Cap style of the stroke. Default value: LineCapStyle.Butt
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default strokeLineCap(value: LineCapStyle | undefined): this;
    /**
     * Sets the join style of the stroke.
     * This attribute does not work for the Circle component, which does not have corners.
     *
     * @param { LineJoinStyle | undefined } value - Join style of the stroke. Default value: LineJoinStyle.Miter
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default strokeLineJoin(value: LineJoinStyle | undefined): this;
    /**
     * Limits for drawing acute angles as bevels
     *
     * @param { double | string | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default strokeMiterLimit(value: double | string | undefined): this;
    /**
     * Sets the stroke opacity.
     * The value range is [0.0, 1.0].
     * A value less than 0.0 evaluates to the value 0.0. A value greater than 1.0 evaluates to the value 1.0.
     * Any other value evaluates to the value 1.0.
     *
     * @param { double | string | Resource | undefined } value - Stroke opacity. Default value: 1
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default strokeOpacity(value: double | string | Resource | undefined): this;
    /**
     * Sets the opacity of the fill area.
     * The value range is [0.0, 1.0].
     * A value less than 0.0 evaluates to the value 0.0. A value greater than 1.0 evaluates to the value 1.0.
     * Any other value evaluates to the value 1.0.
     *
     * @param { double | string | Resource | undefined } value - Opacity of the fill area. Default value: 1
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default fillOpacity(value: double | string | Resource | undefined): this;
    /**
     * Sets the stroke width.
     * If this attribute is of the string type, percentage values are not supported and will be treated as 1 px.
     *
     * @param { Length | undefined } value - Stroke width.
     *     The value must be greater than or equal to 0.
     *     Default value: 1.
     *     Default unit: vp.
     *     An invalid value is handled as the default value.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default strokeWidth(value: Length | undefined): this;
    /**
     * Specifies whether anti-aliasing is enabled.
     *
     * @param { boolean | undefined } value - Whether anti-aliasing is enabled.
     *     true: Anti-aliasing is enabled.
     *     false: Anti-aliasing is disabled.
     *     Default value: true
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default antiAlias(value: boolean | undefined): this;
    /**
     * Sets the gap for the border.
     *
     * @param { Array<Length> | undefined } value
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default strokeDashArray(value: Array<Length> | undefined): this;
    /**
    * Set whether the component enables the ability to invert colors.
    * This interface needs to be set as the first attribute of the component.
    *
    * @param { boolean } value - value indicates whether the component enables the ability to invert colors.
    *     <br>If set to true, the component will use the inverse color capability.
    *     If set to false, the component and its child components will not use the inverse color capability
    *     and will not be affected by the settings of the parent or ancestor components. The default value is true.
    * @returns { this }
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @stagemodelonly
    * @since 23
    */
    default allowForceDark(value: boolean): this;
}
/**
 * Defines the direction of pixel rounding at the component level.
 *
 * @interface PixelRoundPolicy
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface PixelRoundPolicy {
    /**
     * Rounding for alignment with the start edge.
     *
     * @type { ?PixelRoundCalcPolicy }
     * @default PixelRoundCalcPolicy.NO_FORCE_ROUND
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    start?: PixelRoundCalcPolicy;
    /**
     * Rounding for alignment with the top edge.
     *
     * @type { ?PixelRoundCalcPolicy }
     * @default PixelRoundCalcPolicy.NO_FORCE_ROUND
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    top?: PixelRoundCalcPolicy;
    /**
     * Rounding for alignment with the end edge.
     *
     * @type { ?PixelRoundCalcPolicy }
     * @default PixelRoundCalcPolicy.NO_FORCE_ROUND
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    end?: PixelRoundCalcPolicy;
    /**
     * Rounding for alignment with the bottom edge.
     *
     * @type { ?PixelRoundCalcPolicy }
     * @default PixelRoundCalcPolicy.NO_FORCE_ROUND
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    bottom?: PixelRoundCalcPolicy;
}
/**
 * Linear Gradient Blur Interface
 *
 * @interface LinearGradientBlurOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface LinearGradientBlurOptions {
    /**
     * Percentage of blurring effect. Undefined value means no fractionStops.
     *
     * @type { FractionStop[] | undefined }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    fractionStops: FractionStop[] | undefined;
    /**
     * Direction of linear gradient blur. Undefined value means GradientDirection.Left.
     *
     * @type { GradientDirection | undefined }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    direction: GradientDirection | undefined;
}
/**
 * Define motion blur anchor coordinates.
 *
 * @interface MotionBlurAnchor
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface MotionBlurAnchor {
    /**
     * Define anchor coordinate x-value.Value range [0.0, 1.0]. Undefined value means 0.0.
     *
     * @type { double | undefined }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    x: double | undefined;
    /**
     * Define anchor coordinate y-value.Value range [0.0, 1.0]. Undefined value means 0.0.
     *
     * @type { double | undefined }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    y: double | undefined;
}
/**
 * Define motion blur options.
 *
 * @interface MotionBlurOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface MotionBlurOptions {
    /**
     * Define the size of motion blur radius.The range of this value is  [0.0, ∞). Undefined value means 0.0.
     *
     * @type { double | undefined }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    radius: double | undefined;
    /**
     * Define motion blur anchor coordinates. Undefined value means default MotionBlurAnchor.
     *
     * @type { MotionBlurAnchor | undefined }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    anchor: MotionBlurAnchor | undefined;
}
/**
 * Sub component layout info.
 *
 * @extends SizeResult
 * @interface GeometryInfo
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface GeometryInfo extends SizeResult {
    /**
     * Sub component borderWidth info.
     *
     * @type { EdgeWidth }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    borderWidth: EdgeWidth;
    /**
     * Sub component margin info.
     *
     * @type { Margin }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    margin: Margin;
    /**
     * Sub component padding info.
     *
     * @type { Padding }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    padding: Padding;
}
/**
 * Provides the child component layout information.
 *
 * @interface Layoutable
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface Layoutable {
    /**
     * Measurement result of the child component.
     *
     * @type { MeasureResult }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    measureResult: MeasureResult;
    /**
     * Unique ID of the child component.
     *
     * @type { ?int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    uniqueId?: int;
    /**
     * Applies the specified position information to the child component.
     *
     * @param { Position | undefined } position
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    layout(position: Position | undefined): void;
    /**
     * Obtains the margin of the child component.
     *
     * @returns { DirectionalEdgesT<double> | undefined } the margin of sub component, unit is vp. If some errors
     * occur in the internal runtime environment, returns undefined.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getMargin(): DirectionalEdgesT<double> | undefined;
    /**
     * Call this method to get the padding of sub component.
     *
     * @returns { DirectionalEdgesT<double> | undefined } Padding of the child component, unit is vp. If some errors
     * occur in the internal runtime environment, returns undefined.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getPadding(): DirectionalEdgesT<double> | undefined;
    /**
     * Obtains the border width of the child component.
     *
     * @returns { DirectionalEdgesT<double> | undefined } the borderWidth of sub component, unit is vp. If some errors
     * occur in the internal runtime environment, returns undefined.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getBorderWidth(): DirectionalEdgesT<double> | undefined;
}
/**
 * Sub component info passed from framework when measure happens.
 *
 * @interface Measurable
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface Measurable {
    /**
     * Unique ID that the system assigns to the child component.
     *
     * @type { ?int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    uniqueId?: int;
    /**
     * Applies the size constraint to the child component.
     *
     * @param { ConstraintSizeOptions | undefined } constraint
     * @returns { MeasureResult | undefined } Provides the measurement result of the component. If some errors
     *     occur in the internal runtime environment, returns undefined.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    measure(constraint: ConstraintSizeOptions | undefined): MeasureResult | undefined;
    /**
     * Obtains the margin of the child component.
     *
     * @returns { DirectionalEdgesT<double> | undefined } Margin of the child component, unit is vp. If some errors
     * occur in the internal runtime environment, returns undefined.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getMargin(): DirectionalEdgesT<double> | undefined;
    /**
     * Obtains the padding of the child component.
     *
     * @returns { DirectionalEdgesT<double> | undefined } the padding of sub component, unit is vp. If some errors
     * occur in the internal runtime environment, returns undefined.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getPadding(): DirectionalEdgesT<double> | undefined;
    /**
     * Obtains the border width of the child component.
     *
     * @returns { DirectionalEdgesT<double> | undefined } Border width of the child component, unit is vp. If some errors
     * occur in the internal runtime environment, returns undefined.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getBorderWidth(): DirectionalEdgesT<double> | undefined;
}
/**
 * Provides the component size information.
 *
 * @interface SizeResult
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface SizeResult {
    /**
     * Width obtained from the measurement result. Unit: vp.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    width: double;
    /**
     * Height obtained from the measurement result. Unit: vp.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    height: double;
}
/**
 * Provides the measurement result of the component.
 *
 * @extends SizeResult
 * @interface MeasureResult
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface MeasureResult extends SizeResult {
}
/**
 * The navigation destination information.
 *
 * @typedef {uiObserver.NavDestinationInfo} NavDestinationInfo
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type NavDestinationInfo = uiObserver.NavDestinationInfo;
/**
 * The navigation information.
 *
 * @typedef {  uiObserver.NavigationInfo } NavigationInfo
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type NavigationInfo = uiObserver.NavigationInfo;
/**
 * The router page information.
 *
 * @typedef {uiObserver.RouterPageInfo} RouterPageInfo
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type RouterPageInfo = uiObserver.RouterPageInfo;
/**
 * UIContext.
 *
 * @typedef { _UIContext } UIContext
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 23
 */
export type UIContext = _UIContext;
/**
 * DrawContext.
 *
 * @typedef { _DrawContext } DrawContext
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 23
 */
export type DrawContext = _DrawContext;
/**
 * VisualEffect
 *
 * @typedef { uiEffect.VisualEffect } VisualEffect
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type VisualEffect = uiEffect.VisualEffect;
/**
 * Filter
 *
 * @typedef { uiEffect.Filter } Filter
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type Filter = uiEffect.Filter;
/**
 * SystemUiMaterial
 *
 * @typedef { uiMaterial.Material } SystemUiMaterial
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @systemapi
 * @stagemodelonly
 * @since 23
 */
export type SystemUiMaterial = uiMaterial.Material;

/**
 * Blender
 *
 * @typedef { uiEffect.Blender } Blender
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @systemapi
 * @since 23
 */
export type Blender = uiEffect.Blender;
/**
 * Import the DialogController type from promptAction.
 *
 * @typedef { promptAction.DialogController } PromptActionDialogController
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type PromptActionDialogController = promptAction.DialogController;
/**
 * Describe the position, width, and height of a component.
 *
 * @interface RectResult
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface RectResult {
    /**
     * Horizontal coordinate.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    x: double;
    /**
     * Vertical coordinate.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    y: double;
    /**
     * Content width.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    width: double;
    /**
     * Content height.
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    height: double;
}
/**
 * Defines the options about AreaChangeEvent.
 *
 * @typedef AreaChangeOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 26.0.0
 */
export declare interface AreaChangeOptions {
    /**
     * The value of expectedUpdateInterval indicates the desired update interval (ms).
     *
     * @type { ?int }
     * @default 1000
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 26.0.0
     */
    expectedUpdateInterval?: int;
}
/**
 * Defines the options for the AreaChangeEvent.
 *
 * @typedef { function } AreaChangeCallback
 * @param { Area } oldValue - Component area information before the change.
 * @param { Area } newValue - Component area information after the change.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 26.0.0
 */
export declare type AreaChangeCallback = (oldValue: Area, newValue: Area) => void;
/**
 * CaretOffset info.
 *
 * @interface CaretOffset
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface CaretOffset {
    /**
     * Get the index of the CaretOffset
     *
     * @type { int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    index: int;
    /**
     * Get the x of the relative position.
     *
     * @type { int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    x: int;
    /**
     * Get the y of the relative position.
     *
     * @type { int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    y: int;
}
/**
 * Defines the span options of TextContentController.
 *
 * @interface TextContentControllerOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface TextContentControllerOptions {
    /**
     * the offset that add a text at.
     *
     * @type { ?int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    offset?: int;
}
/**
 * TextContentControllerBase
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare abstract class TextContentControllerBase {
    /**
     * Get the index and relative position of the CaretOffset.
     *
     * <p><strong>NOTE</strong>:
     * <br>If this API is called when the caret position is updated in the current frame, it will not take effect.
     * <br>For the Search component, the returned position information is the offset of the first character
     * relative to the search icon in the component.
     * <br>If no text is entered in the Search component,
     * the return value contains the position information relative to the component.
     * <br>The location information in the return value is the location of the caret relative to the editable component.
     * </p>
     *
     * @returns { CaretOffset | undefined } index and relative position of the CaretOffset.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getCaretOffset(): CaretOffset | undefined;
    /**
     * Get the start and end positions of the text content.
     *
     * <p><strong>NOTE</strong>:
     * <br>If no text is entered, the return value contains the position information, but the size is 0.
     * <br>The position information is the offset of the first character relative to the editable area.
     * <br>For the Search component, the returned position information is the offset of the first character
     * relative to the search icon in the component.
     * <br>If there is input, the width in the return value is the fixed width of the editable area.
     * </p>
     *
     * @returns { RectResult | undefined } Text content rect.The unit of the return value is pixel.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getTextContentRect(): RectResult | undefined;
    /**
     * Get the lines number of the text content.
     * The getTextContentLineCount type is used to obtain the number of lines of the edited text.
     *
     * @returns { int | undefined } Text content line count
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getTextContentLineCount(): int | undefined;
    /**
     * Add a text.
     *
     * @param { string } text - text value.
     * @param { TextContentControllerOptions } [textOperationOptions] - operation info.
     * @returns { int | undefined } caret index
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    addText(text: string, textOperationOptions?: TextContentControllerOptions): int | undefined;
    /**
     * Set the styled placeholder.
     *
     * @param { StyledString } styledString - The styledString for placeholder.
     *     If the parameter is invalid, this method will have no effect.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    setStyledPlaceholder(styledString: StyledString): void;
    /**
     * Delete text in TextRange.
     *
     * @param { TextRange } [range] - range for deleting.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    deleteText(range?: TextRange): void;
    /**
     * Gets the selected range of text content.
     *
     * @returns { TextRange | undefined } range for selecting.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getSelection(): TextRange | undefined;
    /**
     * Clear the content of preview.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    clearPreviewText(): void;
    /**
     * Gets the text content of the selected range.
     *
     * @param { TextRange } [range] - selected range.
     * @returns { string | undefined } text content of the selected range.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @systemapi
     * @since 23
     */
    getText(range?: TextRange): string | undefined;

    /**
     * Delete the last character of the input field component.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    deleteBackward(): void;

    /**
     * Scroll the input field component to make the specified content visible.
     * @param { TextRange } [range] - The visible range.
     *     If the parameter is invalid, this method will have no effect.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    scrollToVisible(range?: TextRange): void
}
/**
 * Enum of scrollable containers' content clip mode.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum ContentClipMode {
    /**
     * Clip to content rect inside margin & padding.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    CONTENT_ONLY = 0,
    /**
     * Clip to scrollable's outer rect, including padding but inside margin.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    BOUNDARY = 1,
    /**
     * Clip to the safeArea of scrollable container.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    SAFE_AREA = 2
}

/**
 * CommonScrollableMethod
 *
 * @extends CommonMethod
 * @interface ScrollableCommonMethod
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 * @noninterop
 */
export declare interface ScrollableCommonMethod extends CommonMethod {
    /**
     * Sets the scrollbar state.
     *
     * @param { BarState | undefined } barState - Scrollbar state.<br>Default value: <em>BarState.Auto</em>
     *     for the <em>List</em>, <em>Grid</em>, and <em>Scroll</em> components and <em>BarState.Off</em>
     *     for the <em>WaterFlow</em> component
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    default scrollBar(barState: BarState | undefined): this;
    /**
     * Sets the scrollbar color.
     *
     * @param { Color | int | string | Resource | undefined } color - Scrollbar color.
     *     <br>Default value: <em>'\#182431'</em> (40% opacity)
     *     <br>A number value indicates a HEX color in RGB or ARGB format, for example, <em>0xffffff</em>.
     *     A string value indicates a color in RGB or ARGB format, for example, <em>'#ffffff'</em>.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    default scrollBarColor(color: Color | int | string | Resource | undefined): this;
    /**
     * Sets the scrollbar width.
     *
     * @param { double | string | undefined } value - Scrollbar width.<br>Default value: <em>4</em>
     *     <br>Unit: vp
     *     <br>If this parameter is set to a value less than or equal to 0, the default value is used.
     *     The value <em>0</em> means not to show the scrollbar.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    default scrollBarWidth(value: double | string | undefined): this;
    /**
     * Margin of the scrollbar.
     *
     * @param { ScrollBarMargin | undefined } margin - Margin of the scrollbar.
     *     <br>Default value: {start: LengthMetrics.vp(0), end: LengthMetrics.vp(0)}.
     *     Passing undefined will restore the default value.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    default scrollBarMargin(margin: ScrollBarMargin | undefined): this;
    /**
     * Set the scroll bar auto adjust the margin to avoid the padding, safeAreaPadding, and
     * contentStartOffset/contentEndOffset of the component.
     *
     * @param { boolean | undefined } enable - Whether to enable automatic adjustment of scroll bar margin.
     *     <br>Default value: false.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 26.0.0
     */
    default autoAdjustScrollBarMargin(enable: boolean | undefined): this;
    /**
     * Sets the effect used when the scroll boundary is reached.
     *
     * @param { EdgeEffect | undefined } edgeEffect - Effect used when the scroll boundary is
     *     reached. The spring and shadow effects are supported. Default value:
     *     <em>EdgeEffect.None</em> for the <em>Grid</em>, <em>Scroll</em>, and <em>WaterFlow</em>
     *     components and <em>EdgeEffect.Spring</em> for the <em>List</em> component
     * @param { EdgeEffectOptions } [options] - Whether to enable the scroll effect when the
     *     component content is smaller than the component itself. The value
     *     <em>{ alwaysEnabled: true }</em> means to enable the scroll effect, and
     *     <em>{ alwaysEnabled: false }</em> means the opposite. Default value:
     *     <em>{ alwaysEnabled: false }</em> for the <em>List</em>, <em>Grid</em>,
     *     and <em>WaterFlow</em> components, and <em>{ alwaysEnabled: true }</em>
     *     for the <em>Scroll</em> component
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    default edgeEffect(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions): this;
    /**
     * Called when setting whether to enable fading Edge effect.
     *
     * @param { boolean | undefined } enabled - Whether to turn on the edge fade effect
     * @param { FadingEdgeOptions } [options] - The options of fadingEdge.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    default fadingEdge(enabled: boolean | undefined, options?: FadingEdgeOptions): this;
    /**
     * Sets the nested scrolling options.
     *
     * @param { NestedScrollOptions | undefined } value - Nested scrolling options.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    default nestedScroll(value: NestedScrollOptions | undefined): this;
    /**
     * Sets whether to support scroll gestures.
     *
     * @param { boolean | undefined } value - Whether to support scroll gestures.<br>Default value: <em>true</em>
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    default enableScrollInteraction(value: boolean | undefined): this;
    /**
     * Sets the friction coefficient.
     *
     * @param { double | Resource | undefined } value - Friction coefficient.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    default friction(value: double | Resource | undefined): this;
    /**
     * Sets the offset from the start of the content to the boundary of the scrollable display area.
     *
     * @param { double | Resource | undefined } offset - Offset from the start of the content to the boundary of
     *     the scrollable display area.
     *     <br>Unit: vp
     *     <br>Unit:Default value: <em>0</em>. Passing undefined will restore the default value.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 24
     */
    default contentStartOffset(offset: double | Resource | undefined): this;
    /**
     * Sets the offset from the end of the content to the boundary of the scrollable display area.
     *
     * @param { double | Resource | undefined } offset - Offset from the end of the content to the boundary of
     *     the scrollable display area.
     *     <br>Unit: vp
     *     <br>Default value: <em>0</em>. Passing undefined will restore the default value.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 24
     */
    default contentEndOffset(offset: double | Resource | undefined): this;
    /**
     * Called when the scrollable will start dragging.
     *
     * @param { VoidCallback | undefined } handler - callback of start dragging.
     *     <br>Passing undefined will unregister the callback.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 24
     */
    default onWillStartDragging(handler: VoidCallback | undefined): this;
    /**
     * Called when the scrollable will end dragging.
     *
     * @param { OnWillStopDraggingCallback | undefined } handler - callback of end dragging.
     *     <br>Passing undefined will unregister the callback.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 24
     */
    default onWillStopDragging(handler: OnWillStopDraggingCallback | undefined): this;
    /**
     * Called when the scrollable did end dragging.
     *
     * @param { OnDidStopDraggingCallback | undefined } handler - callback of end dragging.
     *     <br>Passing undefined will unregister the callback.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 24
     */
    default onDidStopDragging(handler: OnDidStopDraggingCallback | undefined): this;
    /**
     * Called when the scrollable will start fling.
     *
     * @param { VoidCallback | undefined } handler - callback of start fling.
     *     <br>Passing undefined will unregister the callback.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 24
     */
    default onWillStartFling(handler: VoidCallback | undefined): this;
    /**
     * Called when the scrollable did stop fling.
     *
     * @param { VoidCallback | undefined } handler - callback of stop fling.
     *     <br>Passing undefined will unregister the callback.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 24
     */
    default onDidStopFling(handler: VoidCallback | undefined): this;
    /**
     * Enable left mouse button press-and-drag scrolling.
     *
     * @param { boolean | undefined } enabled - Enable left mouse button press-and-drag scrolling.
     *    <br>Default value: false.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 26.0.0
     */
    default enableScrollWithMouse(enabled: boolean | undefined): this;
    /**
     * Triggered when the scrollable component reaches the start position.
     *
     * @param { function | undefined } event - Callback function, triggered when the scrollable reaches
     *     the start position.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    default onReachStart(event: (() => void) | undefined): this;
    /**
     * Triggered when the scrollable component reaches the end position.
     *
     * @param { function | undefined } event - Callback function, triggered when the scrollable reaches the end position.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    default onReachEnd(event: (() => void) | undefined): this;
    /**
     * Triggered when the scrollable component starts scrolling initiated by the user's finger dragging the
     * component or its scrollbar.
     *
     * @param { function | undefined } event - Callback function, triggered when the scrollable starts scrolling.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    default onScrollStart(event: (() => void) | undefined): this;
    /**
     * Triggered when scrolling stops after the user's finger leaves the screen.
     *
     * @param { function | undefined } event - Callback function, triggered when the scrollable stops scrolling.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    default onScrollStop(event: (() => void) | undefined): this;
    /**
     * Sets the maximum initial velocity at the start of the fling animation that occurs after gesture-driven scrolling ends.
     *
     * @param { double | undefined } speedLimit - Maximum initial velocity at the start of the fling animation.
     *     <br>Default value: <em>9000</em>
     *     <br>Unit: vp/s
     *     <br>Value range: (0, +∞). If this parameter is set to a value less than or equal to 0, the default value is used.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    default flingSpeedLimit(speedLimit: double | undefined): this;
    /**
     * Sets the content clipping area for this scrollable component.
     *
     * @param { ContentClipMode | RectShape | undefined } clip - A value from enum ContentClipMode or a customized clip rect.
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    default clipContent(clip: ContentClipMode | RectShape | undefined): this;
    /**
     * Set the sensitivity of rotating crown.
     *
     * @param { CrownSensitivity | undefined } sensitivity - The sensitivity of rotating crown, default value is { MEDIUM }.
     * @returns { this } The component instance.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    default digitalCrownSensitivity(sensitivity: CrownSensitivity | undefined): this;
    /**
     * Sets whether to enable the back-to-top feature for a scrollable component when the status bar is touched.
     *
     * @param { boolean | undefined } backToTop - Whether to enable the backtotop feature for a scrollable
     *     component when the status bar is touched. <br>Default value: <em>false</em>
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    default backToTop(backToTop: boolean | undefined): this;
}
/**
 * The actual offset by which the scrollable scrolls.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare class ScrollResult {
    /**
     * Get the actual offset by which the scrollable scrolls in vp.
     * @returns { double } actual offset by which the scrollable scrolls in vp.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    get offsetRemain(): double;

    /**
     * Set the actual offset by which the scrollable scrolls in vp.
     * @param { double } offsetRemain - actual offset by which the scrollable scrolls in vp.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    set offsetRemain(offsetRemain: double);
}
/**
 * Called before scroll to allow developer to control real offset the Scrollable can scroll.
 *
 * @typedef { function } OnWillScrollCallback
 * @param { double } scrollOffset - offset this frame will scroll, which may or may not be reached.
 * @param { ScrollState } scrollState - current scroll state.
 * @param { ScrollSource } scrollSource - source of current scroll.
 * @returns { undefined | ScrollResult } the remain offset for the scrollable,
 *     same as scrollOffset when no ScrollResult is returned.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type OnWillScrollCallback = (scrollOffset: double, scrollState: ScrollState, scrollSource: ScrollSource) => undefined | ScrollResult;
/**
  * On scroll callback using in scrollable onDidScroll.
  *
  * @typedef { function } OnScrollCallback
  * @param { double } scrollOffset - offset this frame did scroll.
  * @param { ScrollState } scrollState - current scroll state.
  * @syscap SystemCapability.ArkUI.ArkUI.Full
  * @since 23
  */
export type OnScrollCallback = (scrollOffset: double, scrollState: ScrollState) => void;
/**
 * On scroll callback using in scrollable onWillStopDragging.
 *
 * @typedef { function } OnWillStopDraggingCallback
 * @param { double } velocity - The veolicity of the scroll view at the moment the touch was released.
 *     <br>Unit: vp/s.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 24
 */
export type OnWillStopDraggingCallback = (velocity: double) => void;
/**
 * On scroll callback using in scrollable onDidStopDragging.
 *
 * @typedef { function } OnDidStopDraggingCallback
 * @param { boolean } willFling - whether start fling animation.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 24
 */
export type OnDidStopDraggingCallback = (willFling: boolean) => void;
/**
  * Defines the callback type used in onItemDragStart.
  *
  * @typedef { function } OnItemDragStartCallback
  * @param { ItemDragInfo } event - Information about the dragged item.
  * @param { int } itemIndex - The index number of the dragged item.
  * @returns {CustomBuilder | undefined}
  * @syscap SystemCapability.ArkUI.ArkUI.Full
  * @since 23
  */
export type OnItemDragStartCallback = (event: ItemDragInfo, itemIndex: int) => CustomBuilder | undefined;
/**
  * Defines the callback type used in onGetPreviewBadge of EditModeOptions.
  *
  * @typedef { function } OnGetPreviewBadgeCallback
  * @returns { boolean | int }
  * @syscap SystemCapability.ArkUI.ArkUI.Full
  * @stagemodelonly
  * @since 23
  */
export type OnGetPreviewBadgeCallback = () => boolean | int;
/**
 * Defines the callback type used in OnVisibleIndexesChange.
 *
 * @typedef { function } OnVisibleIndexesChangeCallback
 * @param { int } start - the first index in visible content.
 * @param { int } end - the last index in visible content.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 26.0.0
 */
export type OnVisibleIndexesChangeCallback = (start: int, end: int) => void;
/**
 * Defines the onMove callback.
 *
 * @typedef { function } OnMoveHandler
 * @param { int } from - Index number for moving elements.
 * @param { int } to - Target index number for moving elements.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type OnMoveHandler = (from: int, to: int) => void;
/**
 * Define item drag event handler.
 *
 * @interface ItemDragEventHandler
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface ItemDragEventHandler {
    /**
     * This callback is triggered when the item is long pressed.
     *
     * @type { ?Callback<int> }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onLongPress?: Callback<int>;
    /**
     * This callback is triggered when the item is dragged.
     *
     * @type { ?Callback<int> }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onDragStart?: Callback<int>;
    /**
     * This callback is triggered when an item is moved through other items.
     *
     * @type { ?Callback<int> }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onMoveThrough?: OnMoveHandler;
    /**
     * This callback is triggered when the item is dropped.
     *
     * @type { ?Callback<int> }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onDrop?: Callback<int>;
}
/**
 * Define DynamicNode.
 *
 * @typedef DynamicNode
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 23
 */
export declare interface DynamicNode {
    /**
     * Set the move action.
     *
     * @param { OnMoveHandler | undefined } handler
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    onMove(handler: OnMoveHandler | undefined): this;
    /**
     * Set the move action.
     *
     * @param { OnMoveHandler | undefined } handler
     * @param { ItemDragEventHandler } eventHandler
     * @returns { this }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    onMove(handler: OnMoveHandler | undefined, eventHandler: ItemDragEventHandler): this;
}
/**
 * Define EdgeEffect Options.
 *
 * @interface EdgeEffectOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface EdgeEffectOptions {
    /**
     * Enable Sliding effect when component does not full screen.
     *
     * @type { boolean }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    alwaysEnabled: boolean;
    /**
     * Set the effective edge of the edge effect.
     *
     * @type { ?int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    effectEdge?: int;
}
/**
 * Enumerates the effective edge of the edge effect.
 *
 * @enum { int }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum EffectEdge {
    /**
     * Effective only for the starting edge.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    START = 1,
    /**
     * Effective only for the end edge.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    END = 2
}
/**
 * Indicates children main size.
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare class ChildrenMainSize {
    /**
     * Creates an instance of ChildrenMainSize.
     *
     * @param { double } childDefaultSize - default main size, in vp. If the main axis is vertical, it indicates height.
     * If the main axis is horizontal, it indicates width.
     * @throws { BusinessError } 401 - Parameter error. Possible causes:
     *     <br> 1. Mandatory parameters are left unspecified.
     *     <br> 2. Incorrect parameters types.
     *     <br> 3. Parameter verification failed.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    constructor(childDefaultSize: double);
    /**
     * Set default size.
     *
     * @param { double } value - default main size, in vp. If the main axis is vertical, it indicates height.
     * If the main axis is horizontal, it indicates width.
     * @throws { BusinessError } 401 - Parameter error. Possible causes:
     *     <br> 1. Mandatory parameters are left unspecified.
     *     <br> 2. Incorrect parameters types.
     *     <br> 3. Parameter verification failed.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    set childDefaultSize(value: double);
    /**
     * Get default size
     *
     * @returns { double } - default main size, in vp. If the main axis is vertical, it indicates height.
     * If the main axis is horizontal, it indicates width.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    get childDefaultSize(): double;
    /**
     * Changes children main size by removing or replacing existing elements and/or adding new elements in place.
     *
     * @param { int } start - Zero-based index at which to start changing the children main size.
     * @param { int } [deleteCount] - Indicating the number of children main size to remove from start.
     * @param { Array<double> } [childrenSize] - Add the new children main size, beginning from start.
     * @throws { BusinessError } 401 - Parameter error. Possible causes:
     *     <br> 1. Mandatory parameters are left unspecified.
     *     <br> 2. Incorrect parameters types.
     *     <br> 3. Parameter verification failed.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     * @example splice(1, 0, [100]), Insert a child after first child, the child's main size is 100vp.
     * splice(1, 1), Delete the second child.
     * splice(1, 2, [100, 100]), Change the main size of the second and third children to 100vp.
     */
    splice(start: int, deleteCount?: int, childrenSize?: Array<double>): void;
    /**
     * Updates main size for specified child.
     *
     * @param { int } index - index of child to be updated.
     * @param { double } childSize - new section options.
     * @throws { BusinessError } 401 - Parameter error. Possible causes:
     *     <br> 1. Mandatory parameters are left unspecified.
     *     <br> 2. Incorrect parameters types.
     *     <br> 3. Parameter verification failed.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    update(index: int, childSize: double): void;
}

/**
 * Define edit mode options.
 *
 * @interface EditModeOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 23
 */
export declare interface EditModeOptions {
    /**
     * Define whether to gather selected items in grid or list when item is long pressed for context menu.
     *
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    enableGatherSelectedItemsAnimation?: boolean;

    /**
     * Called to return whether to display the number badge or the number displayed on the badge
     * for the context menu preview. If not set, the number of selected items within the display range will be used.
     * Returning false means not displaying the badge.
     * Returning true means using the number of selected items within the display range.
     * Returning a number to include selected items outside the display range.
     *
     * @type { ?OnGetPreviewBadgeCallback } onGetPreviewBadge
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 23
     */
    onGetPreviewBadge?: OnGetPreviewBadgeCallback;
}

/**
 * Define BackgroundBrightness Options.
 *
 * @interface BackgroundBrightnessOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface BackgroundBrightnessOptions {
    /**
     * Brightness change rate. A higher rate means that brightness decreases more quickly.
     * If **rate** is set to **0**, **lightUpDegree** will not take effect, meaning no brightening effect will occur.
     *
     * @type { double } - The default value is 0.0, value range: (0.0, +∞).
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    rate: double;
    /**
     * Light up degree. A greater degree indicates a greater increase in brightness.
     *
     * @type { double } - The default value is 0.0, value range: [-1.0, 1.0].
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    lightUpDegree: double;
}

/**
 * PointLightStyle info
 *
 * @interface PointLightStyle
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @systemapi
 * @since 23
 */
export declare interface PointLightStyle {
  /**
   * Defines the PointLight light intensity and position.
   *
   * @type { ?LightSource }
   * @default undefined
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @systemapi
   * @since 23
   */
  lightSource?: LightSource;
  /**
   * Defines the PointLight illuminated type.
   *
   * @type { ?IlluminatedType }
   * @default IlluminatedType.NONE
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @systemapi
   * @since 23
   */
  illuminated?: IlluminatedType;
  /**
   * Defines the PointLight bloom.
   *
   * @type { ?double }
   * @default 0
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @systemapi
   * @since 23
   */
  bloom?: double;
}

/**
 * LightSource info
 *
 * @interface LightSource
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @systemapi
 * @since 23
 */
declare interface LightSource {
  /**
   * Defines the PointLight light positionX.
   *
   * @type { Dimension }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @systemapi
   * @since 23
   */
  positionX: Dimension;
  /**
   * Defines the PointLight light positionX.
   *
   * @type { Dimension }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @systemapi
   * @since 23
   */
  positionY: Dimension;
  /**
   * Defines the PointLight light positionX.
   *
   * @type { Dimension }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @systemapi
   * @since 23
   */
  positionZ: Dimension;
  /**
   * Defines the PointLight light intensity.
   *
   * @type { double }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @systemapi
   * @since 23
   */
  intensity: double;
  /**
   * Defines the PointLight light color.
   *
   * @type { ?ResourceColor }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @systemapi
   * @since 23
   */
  color?: ResourceColor;
}


/**
 * Defines the overall animation parameters of the keyframe animation.
 *
 * @interface KeyframeAnimateParam
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface KeyframeAnimateParam {
    /**
     * Animation delay time, in ms.
     *
     * @type { ?int }
     * @default 0
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    delay?: int;
    /**
     * Animation iterations. When set to -1, the animation playing it repeatedly. The value range is greater than or equal to -1.
     *
     * @type { ?int }
     * @default 1
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    iterations?: int;
    /**
     * Callback invoked when the whole keyframe animation is complete or the ability is about to enter the background.
     *
     * @type { ?function }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onFinish?: () => void;
    /**
     * Indicates expectedFrameRateRange of keyframe animation.
     *
     * @type { ?ExpectedFrameRateRange }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    expectedFrameRateRange?: ExpectedFrameRateRange;
}
/**
 * Defines a keyframe state.
 *
 * @interface KeyframeState
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface KeyframeState {
    /**
     * Animation duration of this keyframe, in ms.
     *
     * @type { int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    duration: int;
    /**
     * Animation curve of this keyframe.
     *
     * @type { ?(Curve | string | ICurve) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    curve?: Curve | string | ICurve;
    /**
     * The closure function to specify the terminating state of this keyframe.
     *
     * @type { function }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    event: () => void;
}
/**
 * Defines the callback
 *
 * @typedef { function } Callback<T, V = void>
 * @param { T } data
 * @returns { V }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type Callback<T, V = void> = (data: T) => V;
/**
 * Defines the callback type used in hover events.
 * The value of isHover indicates whether the mouse is hovering over the component.
 * The value of event contains information about HoverEvent.
 *
 * @typedef { function } HoverCallback
 * @param { boolean } isHover
 * @param { HoverEvent} event
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type HoverCallback = (isHover: boolean, event: HoverEvent) => void;
/**
 * Defines the callback type used in accessibility hover events.
 * The value of isHover indicates whether the touch is hovering over the component.
 * The value of event contains information about AccessibilityHoverEvent.
 *
 * @typedef { function } AccessibilityCallback
 * @param { boolean } isHover
 * @param { AccessibilityHoverEvent } event
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type AccessibilityCallback = (isHover: boolean, event: AccessibilityHoverEvent) => void;

/**
 * Defines the callback type used in accessibility hover transparent event.
 *
 * @typedef { function } AccessibilityTransparentCallback
 * @param { TouchEvent } event - The value of event contains information about original accessibility hover event.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type AccessibilityTransparentCallback = (event: TouchEvent) => void

/**
 * Defines the options about VisibleAreaEvent.
 *
 * @interface VisibleAreaEventOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface VisibleAreaEventOptions {
    /**
     * Each number in ratios indicates the value of visibility ratio. Each number in the Array value range in [0, 1].
     *
     * @type { Array<double> }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    ratios: Array<double>;
    /**
     * The value of expectedUpdateInterval indicates desired update period(ms).
     *
     * @type { ?int }
     * @default 1000
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    expectedUpdateInterval?: int;
}
/**
 * Defines the callback type used in VisibleAreaChange events.
 *
 * @typedef { function } VisibleAreaChangeCallback
 * @param { boolean } isExpanding - Indicates the ratio of the visible area to its own area compared to the last change.
 * It is true as the ratio increases and false as the ratio decreases.
 * @param { double } currentRatio - The value of currentRatio indicates the visibility ratio of the current component.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type VisibleAreaChangeCallback = (isExpanding: boolean, currentRatio: double) => void;
/**
 * Defines a UICommonEvent which is used to set different common event to target component.
 *
 * @interface UICommonEvent
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface UICommonEvent {
    /**
     * Set or reset the callback which will be triggered a click event when clicked.
     *
     * @param { Callback<ClickEvent> | undefined } callback - The callback about the click event. If set undefined will reset the target callback.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    setOnClick(callback: Callback<ClickEvent> | undefined): void;
    /**
     * Set or reset the callback which will be triggered a touch event when touched.
     *
     * @param { Callback<TouchEvent> | undefined } callback - The callback about the touch event. If set undefined will reset the target callback.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    setOnTouch(callback: Callback<TouchEvent> | undefined): void;
    /**
     * Set or reset the callback is triggered when a component mounts a display.
     *
     * @param { VoidCallback | undefined } callback - The callback will be triggered when a component mounts a display. If set undefined will reset the target callback.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    setOnAppear(callback: VoidCallback | undefined): void;
    /**
     * Set or reset the callback is triggered when component uninstallation disappears.
     *
     * @param { VoidCallback | undefined } callback - The callback will be triggered when component uninstallation disappears. If set undefined will reset the target callback.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    setOnDisappear(callback: VoidCallback | undefined): void;
    /**
     * Set or reset the callback is triggered when component has keyboard input.
     *
     * @param { Callback<KeyEvent> | undefined } callback - The callback will be triggered when has keyboard input. If set undefined will reset the target callback.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    setOnKeyEvent(callback: Callback<KeyEvent> | undefined): void;
    /**
     * Set or reset the callback which is triggered when component get focus.
     *
     * @param { VoidCallback | undefined } callback - The callback will be triggered when a component get focus. If set undefined will reset the target callback.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    setOnFocus(callback: VoidCallback | undefined): void;
    /**
     * Set or reset the callback which is triggered when lose focus.
     *
     * @param { VoidCallback | undefined } callback - The callback will be triggered when a component lose focus. If set undefined will reset the target callback.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    setOnBlur(callback: VoidCallback | undefined): void;
    /**
     * Set or reset the callback which is triggered when has a hover event.
     *
     * @param { HoverCallback | undefined } callback - The callback will be triggered when has a hover event. If set undefined will reset the target callback.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    setOnHover(callback: HoverCallback | undefined): void;
    /**
    * Set or reset the callback which is triggered when has a mouse event.
    *
    * @param { Callback<MouseEvent> | undefined } callback - The callback will be triggered when has mouse input. If set undefined will reset the target callback.
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    setOnMouse(callback: Callback<MouseEvent> | undefined): void;
    /**
    * Sets the callback for the onSizeChange event.
    *
    * @param { SizeChangeCallback | undefined } callback - The callback will be triggered when the size of component changed. If set undefined will reset the target callback.
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    setOnSizeChange(callback: SizeChangeCallback | undefined): void;
    /**
     * Sets the onVisibleAreaChange callback that limits the callback interval.
     *
     * @param { VisibleAreaEventOptions } options - The options for the visibility event.
     * @param { VisibleAreaChangeCallback | undefined } event - The callback will be triggered when the visibleArea of component changed and get close to any number in ratios defined by options.
     * If set undefined will reset the target callback.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    setOnVisibleAreaApproximateChange(options: VisibleAreaEventOptions, event: VisibleAreaChangeCallback | undefined): void;
}
/**
 * Defines a UIScrollableCommonEvent which is used to set event to target component.
 *
 * @extends UICommonEvent
 * @interface UIScrollableCommonEvent
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 24
 */
export declare interface UIScrollableCommonEvent extends UICommonEvent {
  /**
   * Set or reset the callback which is triggered when the scrolling reaches the start position.
   *
   * @param { VoidCallback | undefined } callback - callback function, triggered when the scrolling reaches
   *     the start position.
   *     <br>Passing undefined will unregister the callback.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @stagemodelonly
   * @since 24
   */
  setOnReachStart(callback: VoidCallback | undefined): void;
  /**
   * Set or reset the callback which is triggered when the scrolling reaches the end position.
   *
   * @param { VoidCallback | undefined } callback - callback function, triggered when the
   *     scrolling reaches the end position.
   *     <br>Passing undefined will unregister the callback.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @stagemodelonly
   * @since 24
   */
  setOnReachEnd(callback: VoidCallback | undefined): void;
  /**
   * Set or reset the callback which is triggered when the scrolling started.
   *
   * @param { VoidCallback | undefined } callback - callback function, triggered when the scrolling started.
   *     <br>Passing undefined will unregister the callback.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @stagemodelonly
   * @since 24
   */
  setOnScrollStart(callback: VoidCallback | undefined): void;
  /**
   * Set or reset the callback which is triggered when the scrolling stopped.
   *
   * @param { VoidCallback | undefined } callback - callback function, triggered when the scrolling stopped.
   *     <br>Passing undefined will unregister the callback.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @stagemodelonly
   * @since 24
   */
  setOnScrollStop(callback: VoidCallback | undefined): void;
  /**
   * Set or reset the callback which is triggered when scrolling begin each frame.
   *
   * @param { OnScrollFrameBeginCallback | undefined } callback - callback function, triggered when the
   *     scrolling begin each frame.
   *     <br>Passing undefined will unregister the callback.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @since 24
   */
  setOnScrollFrameBegin(callback: OnScrollFrameBeginCallback | undefined): void;
}
/**
 * Defines a UIGestureEvent which is used to set different gestures to target component.
 *
 * @interface UIGestureEvent
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface UIGestureEvent {
    /**
     * Add a gesture bound to the component.
     *
     * @param { GestureHandler } gesture - gesture indicates the gesture bound to a component.
     * @param { GesturePriority } [priority] - priority indicates the gesture's priority.
     * @param { GestureMask } [mask] - mask indicates the gesture's GestureMask value.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    addGesture(gesture: GestureHandler, priority?: GesturePriority, mask?: GestureMask): void;
    /**
     * Add a parallel gesture bound to the component.
     *
     * @param { GestureHandler } gesture - gesture indicates the gesture bound to a component.
     * @param { GestureMask } [mask] - mask indicates the gesture's GestureMask value.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    addParallelGesture(gesture: GestureHandler, mask?: GestureMask): void;
    /**
     * Remove a gesture from a component that has been bound with a specific tag through a modifier.
     *
     * @param { string } tag - tag indicates the gesture's tag.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    removeGestureByTag(tag: string): void;
    /**
     * Clear gestures bound to the component.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    clearGestures(): void;
}
/**
 * Defines the gesture modifier.
 *
 * @interface GestureModifier
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface GestureModifier {
    /**
     * Defines the gesture update function.
     *
     * @param { UIGestureEvent } event
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    applyGesture(event: UIGestureEvent): void;
}
/**
 * Defines the selection options.
 *
 * @interface SelectionOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface SelectionOptions {
    /**
     * Menu pop-up policy.
     *
     * @type { ?MenuPolicy }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    menuPolicy?: MenuPolicy;
}
/**
 * Defines the next focus item.
 *
 * @interface FocusMovement
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface FocusMovement {
    /**
     * Next focus item's component identifier of forward.
     *
     * @type { ?string }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    forward?: string;
    /**
     * Next focus item's component identifier of backward.
     *
     * @type { ?string }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    backward?: string;
    /**
     * Next focus item's component identifier of up.
     *
     * @type { ?string }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    up?: string;
    /**
     * Next focus item's component identifier of down.
     *
     * @type { ?string }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    down?: string;
    /**
     * Next focus item's component identifier of left.
     *
     * @type { ?string }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    left?: string;
    /**
     * Next focus item's component identifier of right.
     *
     * @type { ?string }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    right?: string;
}
/**
 * enum keyboard avoid mode
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum KeyboardAvoidMode {
    /**
     * Automatically avoids the soft keyboard and compresses the height when reaching the maximum limit.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    DEFAULT = 0,
    /**
     * Does not avoid the soft keyboard.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    NONE = 1
}
/**
 * Enumerates the type of area in hover mode.
 *
 * @enum { number }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare enum HoverModeAreaType {
    /**
     * Layout top half screen when the phone in hover mode.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    TOP_SCREEN = 0,
    /**
     * Layout bottom half screen when the phone in hover mode.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    BOTTOM_SCREEN = 1
}
/**
 * Defines a range of dates.
 *
 * @interface DateRange
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface DateRange {
    /**
     * Defines the start date of the date range.
     *
     * @type { ?Date }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    start?: Date;
    /**
     * Defines the end date of the date range.
     *
     * @type { ?Date }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    end?: Date;
}
/**
 * Indicates the information when the provider of the embedded UI is terminated.
 *
 * @interface TerminationInfo
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface TerminationInfo {
    /**
     * Defines the termination code.
     *
     * @type { int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    code: int;
    /**
     * Defines the additional termination information.
     *
     * @type { ?Want }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    want?: Want;
}
/**
 * Defines the format for displaying dates and times.
 *
 * @typedef { intl.DateTimeOptions } DateTimeOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type DateTimeOptions = intl.DateTimeOptions;

/**
 * Defines a bindable property
 * @interface Bindable<T>
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface Bindable<T> {
    /**
     * Defines value of the bindable property.
     * @type { T }
     * @readonly
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    readonly value: T;
    /**
     * Defines the callback of the bindable property which will be invoked when the property is changed.
     * @type { Callback<T> }
     * @readonly
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    readonly onChange: Callback<T>;
}

/**
 * Create a bindable property instance.
 *
 * @param { T } value - indicates the value of a state property.
 * @param { Callback<T> } onChange - indicates the invoked callback when the property is changed.
 * @returns { Bindable<T> } bindable property instance.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 23
 */
export declare function makeBindable<T>(value: T, onChange: Callback<T>): Bindable<T>;

/**
 * Defines the Two-way binding type of ResourceStr.
 *
 * @typedef { ResourceStr | Bindable<ResourceStr> | Bindable<Resource> | Bindable<string> }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare type BindableResourceStr = ResourceStr | Bindable<ResourceStr> | Bindable<Resource> | Bindable<string>;

/**
 * Defines the Two-way binding type of ResourceStr[].
 *
 * @typedef { ResourceStr[] | Bindable<ResourceStr[]> | Bindable<Resource[]> | Bindable<string[]> }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare type BindableResourceStrArray = ResourceStr[] | Bindable<ResourceStr[]> | Bindable<Resource[]> | Bindable<string[]>;

/**
 * Convert to a bindable property.
 *
 * @param { T } value - indicate the value of a state property.
 * @returns { Bindable<T> }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare function $$<T>(value: T): Bindable<T>;
/**
 * Apply style function on this CommonMethod.
 *
 * @param { T } this
 * @param { CustomStyles } customStyles
 * @returns { T }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare function applyStyles<T extends CommonMethod>(this: T, customStyles: CustomStyles): T;

/**
 * Defines the input event intercept result.
 *
 * @interface InputEventInterceptResult
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 26.0.0
 */
export declare interface InputEventInterceptResult {
  /**
   * Event intercept decision.
   * - CONTINUE: Allows the event to continue to be delivered to the UI framework.
   * - BLOCK: Blocks the event from being delivered, the event will not enter the UI framework.
   *
   * @type { InputEventInterceptAction }
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @stagemodelonly
   * @since 26.0.0
   */
  action: InputEventInterceptAction;
}

/**
 * Defines the input event monitor identifier.
 *
 * **Important Notes**:
 * - This object is created and returned by the system as a unique identifier for the listener.
 * - The object is an empty object with no accessible members.
 * - Developers cannot actively construct this object, it can only be obtained through the registration interface.
 * - Used for subsequent unregistration to verify identity.
 *
 * **Design Purpose**:
 * - Prevents accidental deletion of listeners registered by other modules.
 * - Object references are unique and cannot be forged.
 * - Avoids abuse issues that may be caused by using number type IDs.
 *
 * @interface InputEventMonitor
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 26.0.0
 */
export declare interface InputEventMonitor {
  // Empty interface, no members
  // Used only as an identifier
}

/**
 * Defines the raw input event wrapper.
 *
 * Provides a unified interface to access different types of input events, ensuring type safety and backward compatibility.
 * This class encapsulates raw MouseEvent, TouchEvent, or KeyEvent objects and provides access through type-safe methods.
 *
 * **Important Notes**: This class is an abstract class, developers cannot create instances by themselves.
 * The system automatically creates instances when triggering listener callbacks.
 *
 * @class RawInputEventWrapper
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 26.0.0
 */
export declare abstract class RawInputEventWrapper {
  /**
   * Constructor (internal use).
   *
   * Since this class is abstract, developers cannot directly call the constructor to create instances.
   * The system automatically creates instances when input event listeners are triggered.
   *
   * @param { MouseEvent | TouchEvent | KeyEvent } event - The raw input event.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @stagemodelonly
   * @since 26.0.0
   */
  protected constructor(event: MouseEvent | TouchEvent | KeyEvent);

  /**
   * Checks whether the event is a mouse event.
   *
   * @returns { boolean } - Returns true if the event is a mouse event, otherwise returns false.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @stagemodelonly
   * @since 26.0.0
   */
  isMouseEvent(): boolean;

  /**
   * Checks whether the event is a touch event.
   *
   * @returns { boolean } - Returns true if the event is a touch event, otherwise returns false.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @stagemodelonly
   * @since 26.0.0
   */
  isTouchEvent(): boolean;

  /**
   * Checks whether the event is a keyboard event.
   *
   * @returns { boolean } - Returns true if the event is a keyboard event, otherwise returns false.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @stagemodelonly
   * @since 26.0.0
   */
  isKeyEvent(): boolean;

  /**
   * Attempts to get the mouse event.
   *
   * Returns the event object if it is a mouse event, otherwise returns null.
   *
   * @returns { MouseEvent | null } - The mouse event object or null.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @stagemodelonly
   * @since 26.0.0
   */
  asMouseEvent(): MouseEvent | null;

  /**
   * Attempts to get the touch event.
   *
   * Returns the event object if it is a touch event, otherwise returns null.
   *
   * @returns { TouchEvent | null } - The touch event object or null.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @stagemodelonly
   * @since 26.0.0
   */
  asTouchEvent(): TouchEvent | null;

  /**
   * Attempts to get the keyboard event.
   *
   * Returns the event object if it is a keyboard event, otherwise returns null.
   *
   * @returns { KeyEvent | null } - The keyboard event object or null.
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @stagemodelonly
   * @since 26.0.0
   */
  asKeyEvent(): KeyEvent | null;
}

/**
 * Defines the input event listener callback function type.
 *
 * Parameters:
 * - event: Input event wrapper (automatically created and passed by the system, developers do not need to manually create).
 *
 * Returns:
 * - InputEventInterceptResult: Event intercept result.
 *
 * **Abstract Class Notes**: RawInputEventWrapper is an abstract class, developers cannot use the `new` operator to create instances.
 * The system automatically creates instances and passes them as parameters to callback functions when events are triggered.
 *
 * **Type Safety**: RawInputEventWrapper provides type-safe access methods.
 *
 * **Compatibility Notes**:
 * - Currently supports: MouseEvent, TouchEvent, KeyEvent
 * - Future extensions: AxisEvent, GamepadEvent, etc.
 * - RawInputEventWrapper will automatically support new types without modifying interface definitions
 * - Existing code does not need to be modified to be compatible with new types
 *
 * **Performance Warning**: Do not perform time-consuming operations in the callback, otherwise it may cause the application to freeze\!
 *
 * The listener executes synchronously in the UI thread and will directly block the event processing flow.
 * It is recommended to only perform simple judgments and calculations, avoiding:
 * - Synchronous I/O operations
 * - Complex data processing
 * - Network requests
 * - Massive log output
 *
 * If you need to perform time-consuming operations, please use asynchronous tasks or worker threads.
 *
 * @type { InputEventListener }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 26.0.0
 */
export declare type InputEventListener = (
  event: RawInputEventWrapper
) => InputEventInterceptResult;