/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

declare function $$<T>(value: T): T

declare const Component: ClassDecorator & ((options: ComponentOptions) => ClassDecorator);

declare const ComponentV2: ClassDecorator & ((options: ComponentOptions) => ClassDecorator);

declare type LocalStorageReference = string

declare interface EntryOptions {
    routeName? : string,
    storage? : LocalStorageReference,
    useSharedStorage? : boolean,
}

declare const Entry: ClassDecorator & ((options?: LocalStorageReference | EntryOptions) => ClassDecorator);

declare const Observed: ClassDecorator;

declare const ObservedV2: ClassDecorator;

declare const Preview: ClassDecorator & ((value: PreviewParams) => ClassDecorator);

declare const Require: PropertyDecorator;

declare const BuilderParam: PropertyDecorator;

declare const Local: PropertyDecorator;

declare const Param: PropertyDecorator;

declare const Once: PropertyDecorator;

declare const Event: PropertyDecorator;

declare const State: PropertyDecorator;

declare const Track: PropertyDecorator;

declare const Trace: PropertyDecorator;

declare const Prop: PropertyDecorator;

declare const Link: PropertyDecorator;

declare const ObjectLink: PropertyDecorator;

declare interface ProvideOptions {
    allowOverride?: string,
}

declare const Provide: PropertyDecorator & ((value: string | ProvideOptions) => PropertyDecorator);

declare const Provider: (aliasName?: string) => PropertyDecorator;

declare const Consume: PropertyDecorator & ((value: string) => PropertyDecorator);

declare const Consumer: (aliasName?: string) => PropertyDecorator;

declare const Computed: MethodDecorator;

declare const StorageProp: (value: string) => PropertyDecorator;

declare const StorageLink: (value: string) => PropertyDecorator;

declare const Watch: (value: string) => PropertyDecorator;

declare const Builder: MethodDecorator;

declare const LocalBuilder: MethodDecorator;

declare const Styles: MethodDecorator;

declare const Extend: MethodDecorator & ((value: any) => MethodDecorator);

declare const AnimatableExtend: MethodDecorator & ((value: Object) => MethodDecorator);

declare const Monitor: MonitorDecorator;

declare type MonitorDecorator = (value: string, ...args: string[]) => MethodDecorator;

declare const Concurrent: MethodDecorator;

declare const Sendable: ClassDecorator;

declare const CustomDialog: ClassDecorator;

declare const LocalStorageLink: (value: string) => PropertyDecorator;

declare const LocalStorageProp: (value: string) => PropertyDecorator;

declare const Reusable: ClassDecorator;

declare class ForEachAttribute extends DynamicNode<ForEachAttribute> {
}

interface ForEachInterface {
    (
        arr: Array<any>,
        itemGenerator: (item: any, index: number) => void,
        keyGenerator?: (item: any, index: number) => string,
    ): ForEachAttribute;
}

declare const ForEach: ForEachInterface;

declare interface DataChangeListener {
    onDataReloaded(): void;

    onDataAdded(index: number): void;

    onDataAdd(index: number): void;

    onDataMoved(from: number, to: number): void;

    onDataMove(from: number, to: number): void;

    onDataDeleted(index: number): void;

    onDataDelete(index: number): void;

    onDataChanged(index: number): void;

    onDataChange(index: number): void;

    onDatasetChange(dataOperations: DataOperation[]): void;
}

declare interface IDataSource {
    totalCount(): number;

    getData(index: number): any;

    registerDataChangeListener(listener: DataChangeListener): void;

    unregisterDataChangeListener(listener: DataChangeListener): void;
}

declare class LazyForEachAttribute extends DynamicNode<LazyForEachAttribute> {
}

interface LazyForEachInterface {
    (
        dataSource: IDataSource,
        itemGenerator: (item: any, index: number) => void,
        keyGenerator?: (item: any, index: number) => string,
    ): LazyForEachAttribute;
}

declare const LazyForEach: LazyForEachInterface;

declare class TextEncoder {
    encode(input?: string): Uint8Array;
    encodeInto(input?: string): Uint8Array;
    encodeInto(input: string, dest: Uint8Array): { read: number; written: number };
}

declare class TextDecoder {
    decode(input: Uint8Array, options?: { stream?: false }): string;
}

declare class performance {
    static now(): number;
}




type buffer = ArrayBuffer;

declare const console: {
    assert(value: any, message?: string, ...optionalParams: any[]): void;

    clear(): void;

    count(label?: string): void;

    countReset(label?: string): void;

    debug(message?: any, ...optionalParams: any[]): void;

    // dir(obj: any, options?: InspectOptions): void;

    dirxml(...data: any[]): void;

    error(message?: any, ...optionalParams: any[]): void;

    group(...label: any[]): void;

    groupCollapsed(...label: any[]): void;

    groupEnd(): void;

    info(message?: any, ...optionalParams: any[]): void;

    log(message?: any, ...optionalParams: any[]): void;

    table(tabularData: any, properties?: ReadonlyArray<string>): void;

    time(label?: string): void;

    timeEnd(label?: string): void;

    timeLog(label?: string, ...data: any[]): void;

    trace(message?: any, ...optionalParams: any[]): void;

    warn(message?: any, ...optionalParams: any[]): void;

    profile(label?: string): void;

    profileEnd(label?: string): void;

    timeStamp(label?: string): void;

}

// TODO: these are symbols to help ohos-typescript frontend (aka ets-tsc)
// perform @Styles no-receiver recovery 
// and imitate this.$name struct members

declare interface CommonMethod<T> {
    /**
     * Koala extension
     */
    __applyStyle(style: (instance: T, ...args: any) => this, ...args: any): T

    /**
     * TODO: adding .$fields should be done before the type checker.
     * we workaround that by allowing any fields on structs.
     */
    [key: string]: any;
}



declare interface BusinessError {
    name: string;
    message: string;
    stack?: string;
    code: number;
}
declare type Callback_Extender_OnProgress = ((value: number) => void);
declare type Callback_Extender_OnFinish = (() => void);
declare interface DoubleAnimationParam {
    propertyName: string;
    startValue: number;
    endValue: number;
    duration: number;
    delay: number;
    curve: (Curve|string|ICurve);
    onProgress?: Callback_Extender_OnProgress;
    onFinish?: Callback_Extender_OnFinish;
}
declare class AnimationExtender {
}
declare enum PointerStyle {
    DEFAULT = 0,
    EAST = 1,
    WEST = 2,
    SOUTH = 3,
    NORTH = 4,
    WEST_EAST = 5,
    NORTH_SOUTH = 6,
    NORTH_EAST = 7,
    NORTH_WEST = 8,
    SOUTH_EAST = 9,
    SOUTH_WEST = 10,
    NORTH_EAST_SOUTH_WEST = 11,
    NORTH_WEST_SOUTH_EAST = 12,
    CROSS = 13,
    CURSOR_COPY = 14,
    CURSOR_FORBID = 15,
    COLOR_SUCKER = 16,
    HAND_GRABBING = 17,
    HAND_OPEN = 18,
    HAND_POINTING = 19,
    HELP = 20,
    MOVE = 21,
    RESIZE_LEFT_RIGHT = 22,
    RESIZE_UP_DOWN = 23,
    SCREENSHOT_CHOOSE = 24,
    SCREENSHOT_CURSOR = 25,
    TEXT_CURSOR = 26,
    ZOOM_IN = 27,
    ZOOM_OUT = 28,
    MIDDLE_BTN_EAST = 29,
    MIDDLE_BTN_WEST = 30,
    MIDDLE_BTN_SOUTH = 31,
    MIDDLE_BTN_NORTH = 32,
    MIDDLE_BTN_NORTH_SOUTH = 33,
    MIDDLE_BTN_NORTH_EAST = 34,
    MIDDLE_BTN_NORTH_WEST = 35,
    MIDDLE_BTN_SOUTH_EAST = 36,
    MIDDLE_BTN_SOUTH_WEST = 37,
    MIDDLE_BTN_NORTH_SOUTH_WEST_EAST = 38,
    HORIZONTAL_TEXT_CURSOR = 39,
    CURSOR_CROSS = 40,
    CURSOR_CIRCLE = 41,
    LOADING = 42,
    RUNNING = 43,
}
declare class UnifiedData {
    constructor();
    hasType(UnifiedData_type: string): boolean;
    getTypes(): string[];
}
declare type Callback_RangeUpdate = ((index: number, mark: number|bigint, end: number) => void);
declare class LazyForEachOps {
}
declare class SystemOps {
}
declare class DrawingCanvas {
    constructor(pixelmap: PixelMap);
    drawRect(left: number, top: number, right: number, bottom: number): void;
}
declare class NodeController {
}
declare class TextModifier {
}
declare enum RectWidthStyle {
    TIGHT = 0,
    MAX = 1,
}
declare enum RectHeightStyle {
    TIGHT = 0,
    MAX = 1,
    INCLUDE_LINE_SPACE_MIDDLE = 2,
    INCLUDE_LINE_SPACE_TOP = 3,
    INCLUDE_LINE_SPACE_BOTTOM = 4,
    STRUT = 5,
}
declare class Want {
    bundleName?: string;
    abilityName?: string;
    deviceId?: string;
    uri?: string;
    type?: string;
    flags?: number;
    action?: string;
    parameters?: Map<string,Object>;
    entities?: string[];
    moduleName?: string;
}
declare enum LengthUnit {
    PX = 0,
    VP = 1,
    FP = 2,
    PERCENT = 3,
    LPX = 4,
}
declare class LengthMetrics {
    unit: LengthUnit;
    value: number;
}
declare class ColorMetrics {
    get color(): string;
    get red(): number;
    get green(): number;
    get blue(): number;
    get alpha(): number;
    blendColor(overlayColor: ColorMetrics): ColorMetrics;
}
declare interface WebHeader {
    headerKey: string;
    headerValue: string;
}
declare class WebviewController {
    loadUrl(url: (string|Resource), headers?: WebHeader[]): void;
}
declare interface SnapshotOptions {
    scale?: number;
    waitUntilRenderFinished?: boolean;
}
declare type AsyncCallback_image_PixelMap_Void = ((result: PixelMap) => void);
declare class GlobalScope_ohos_arkui_componentSnapshot {
}
declare enum PerfMonitorActionType {
    LAST_DOWN = 0,
    LAST_UP = 1,
    FIRST_MOVE = 2,
}
declare enum PerfMonitorSourceType {
    PERF_TOUCH_EVENT = 0,
    PERF_MOUSE_EVENT = 1,
    PERF_TOUCHPAD_EVENT = 2,
    PERF_JOYSTICK_EVENT = 3,
    PERF_KEY_EVENT = 4,
}
declare class GlobalScope_ohos_arkui_performanceMonitor {
}
declare type ErrorCallback = ((err: BusinessError) => void);
declare class CommonShape {
    offset(offset: Position): CommonShape;
    fill(color: ResourceColor): CommonShape;
    position(position: Position): CommonShape;
}
declare class BaseShape {
    width(width: Length): BaseShape;
    height(height: Length): BaseShape;
    size(size: SizeOptions): BaseShape;
}
declare interface ShapeSize {
    width?: (number|string);
    height?: (number|string);
}
declare interface RectShapeOptions extends ShapeSize {
    radius?: (number|string|(number|string)[]);
}
declare interface RoundRectShapeOptions extends ShapeSize {
    radiusWidth?: (number|string);
    radiusHeight?: (number|string);
}
declare class RectShape {
    constructor(options?: (RectShapeOptions|RoundRectShapeOptions));
    offset(offset: Position): RectShape;
    fill(color: ResourceColor): RectShape;
    position(position: Position): RectShape;
    width(width: Length): RectShape;
    height(height: Length): RectShape;
    size(size: SizeOptions): RectShape;
    radiusWidth(rWidth: (number|string)): RectShape;
    radiusHeight(rHeight: (number|string)): RectShape;
    radius(radius: (number|string|(number|string)[])): RectShape;
}
declare class CircleShape {
    constructor(options?: ShapeSize);
    offset(offset: Position): CircleShape;
    fill(color: ResourceColor): CircleShape;
    position(position: Position): CircleShape;
    width(width: Length): CircleShape;
    height(height: Length): CircleShape;
    size(size: SizeOptions): CircleShape;
}
declare class EllipseShape {
    constructor(options?: ShapeSize);
    offset(offset: Position): EllipseShape;
    fill(color: ResourceColor): EllipseShape;
    position(position: Position): EllipseShape;
    width(width: Length): EllipseShape;
    height(height: Length): EllipseShape;
    size(size: SizeOptions): EllipseShape;
}
declare interface PathShapeOptions {
    commands?: string;
}
declare class PathShape {
    constructor(options?: PathShapeOptions);
    offset(offset: Position): PathShape;
    fill(color: ResourceColor): PathShape;
    position(position: Position): PathShape;
    commands(commands: string): PathShape;
}
declare interface FontOptions {
    familyName: (string|Resource);
    familySrc: (string|Resource);
}
declare class GlobalScope_ohos_font {
}
declare enum EffectDirection {
    DOWN = 0,
    UP = 1,
}
declare enum EffectScope {
    LAYER = 0,
    WHOLE = 1,
}
declare class SymbolEffect {
}
declare class ScaleSymbolEffect extends SymbolEffect {
    constructor(scope?: EffectScope, direction?: EffectDirection);
    scope?: EffectScope;
    direction?: EffectDirection;
}
declare class ReplaceSymbolEffect extends SymbolEffect {
    constructor(scope?: EffectScope);
    scope?: EffectScope;
}
declare class FrameNode {
    constructor(uiContext: UIContext);
    isModifiable(): boolean;
    appendChild(node: FrameNode): void;
    insertChildAfter(child: FrameNode, sibling: FrameNode): void;
    removeChild(node: FrameNode): void;
    clearChildren(): void;
    getChild?(index: number): FrameNode;
    getFirstChild?(): FrameNode;
    getNextSibling?(): FrameNode;
    getPreviousSibling?(): FrameNode;
    getParent?(): FrameNode;
    getChildrenCount(): number;
    dispose(): void;
    getOpacity(): number;
    getPositionToWindowWithTransform(): Position;
}
declare interface PixelMap {
    readonly isEditable: boolean;
    readonly isStrideAlignment: boolean;
    readPixelsToBufferSync(dst: ArrayBuffer): void;
    writeBufferToPixels(src: ArrayBuffer): void;
}
declare type CustomNodeBuilder = ((parentNode: number|bigint) => number|bigint);
declare type NavExtender_OnUpdateStack = (() => void);
declare class NavExtender {
}
declare interface Point {
    x: number;
    y: number;
}
declare interface Root {
}
declare interface ComponentRoot {
}
declare class EventEmulator {
}
declare type Literal_Want_want = { want: Want }
declare interface AbilityComponentInterface {
    (value: { want: Want }): AbilityComponentAttribute;
}
declare type Callback_Void = (() => void);
declare class AbilityComponentAttribute extends CommonMethod<AbilityComponentAttribute> {
    onConnect(value: (() => void)): AbilityComponentAttribute;
    onDisconnect(value: (() => void)): AbilityComponentAttribute;
}
declare interface SheetInfo {
    title: (string|Resource);
    icon?: (string|Resource);
    action: VoidCallback;
}
declare interface DismissDialogAction {
    dismiss: (() => void);
    reason: DismissReason;
}
declare interface ActionSheetButtonOptions {
    enabled?: boolean;
    defaultFocus?: boolean;
    style?: DialogButtonStyle;
    value: (string|Resource);
    action: VoidCallback;
}
declare interface ActionSheetOffset {
    dx: (number|string|Resource);
    dy: (number|string|Resource);
}
declare type Callback_DismissDialogAction_Void = ((parameter: DismissDialogAction) => void);
declare interface ActionSheetOptions {
    title: (string|Resource);
    subtitle?: ResourceStr;
    message: (string|Resource);
    confirm?: ActionSheetButtonOptions;
    cancel?: VoidCallback;
    sheets: SheetInfo[];
    autoCancel?: boolean;
    alignment?: DialogAlignment;
    offset?: ActionSheetOffset;
    maskRect?: Rectangle;
    showInSubWindow?: boolean;
    isModal?: boolean;
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    onWillDismiss?: ((parameter: DismissDialogAction) => void);
    transition?: TransitionEffect;
    cornerRadius?: (Dimension|BorderRadiuses|LocalizedBorderRadiuses);
    width?: Dimension;
    height?: Dimension;
    borderWidth?: (Dimension|EdgeWidths|LocalizedEdgeWidths);
    borderColor?: (ResourceColor|EdgeColors|LocalizedEdgeColors);
    borderStyle?: (BorderStyle|EdgeStyles);
    shadow?: (ShadowOptions|ShadowStyle);
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
}
declare class ActionSheet {
}
declare enum DialogAlignment {
    TOP = 0,
    Top = 0,
    CENTER = 1,
    Center = 1,
    BOTTOM = 2,
    Bottom = 2,
    DEFAULT = 3,
    Default = 3,
    TOP_START = 4,
    TopStart = 4,
    TOP_END = 5,
    TopEnd = 5,
    CENTER_START = 6,
    CenterStart = 6,
    CENTER_END = 7,
    CenterEnd = 7,
    BOTTOM_START = 8,
    BottomStart = 8,
    BOTTOM_END = 9,
    BottomEnd = 9,
}
declare enum DialogButtonDirection {
    AUTO = 0,
    HORIZONTAL = 1,
    VERTICAL = 2,
}
declare interface AlertDialogButtonBaseOptions {
    enabled?: boolean;
    defaultFocus?: boolean;
    style?: DialogButtonStyle;
    value: ResourceStr;
    fontColor?: ResourceColor;
    backgroundColor?: ResourceColor;
    action: VoidCallback;
}
declare interface AlertDialogButtonOptions extends AlertDialogButtonBaseOptions {
    primary?: boolean;
}
declare interface TextStyle_alert_dialog {
    wordBreak?: WordBreak;
}
declare interface AlertDialogParam {
    title?: ResourceStr;
    subtitle?: ResourceStr;
    message: ResourceStr;
    autoCancel?: boolean;
    cancel?: VoidCallback;
    alignment?: DialogAlignment;
    offset?: Offset;
    gridCount?: number;
    maskRect?: Rectangle;
    showInSubWindow?: boolean;
    isModal?: boolean;
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    onWillDismiss?: ((parameter: DismissDialogAction) => void);
    transition?: TransitionEffect;
    cornerRadius?: (Dimension|BorderRadiuses|LocalizedBorderRadiuses);
    width?: Dimension;
    height?: Dimension;
    borderWidth?: (Dimension|EdgeWidths|LocalizedEdgeWidths);
    borderColor?: (ResourceColor|EdgeColors|LocalizedEdgeColors);
    borderStyle?: (BorderStyle|EdgeStyles);
    shadow?: (ShadowOptions|ShadowStyle);
    textStyle?: TextStyle_alert_dialog;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
}
declare interface AlertDialogParamWithConfirm extends AlertDialogParam {
    confirm?: AlertDialogButtonBaseOptions;
}
declare interface AlertDialogParamWithButtons extends AlertDialogParam {
    primaryButton: AlertDialogButtonBaseOptions;
    secondaryButton: AlertDialogButtonBaseOptions;
}
declare interface AlertDialogParamWithOptions extends AlertDialogParam {
    buttons: AlertDialogButtonOptions[];
    buttonDirection?: DialogButtonDirection;
}
declare class AlertDialog {
}
declare enum IndexerAlign {
    LEFT = 0,
    Left = 0,
    RIGHT = 1,
    Right = 1,
    START = 2,
    END = 3,
}
declare interface AlphabetIndexerOptions {
    arrayValue: string[];
    selected: number;
}
declare interface AlphabetIndexerInterface {
    (options: AlphabetIndexerOptions): AlphabetIndexerAttribute;
}
declare type OnAlphabetIndexerSelectCallback = ((index: number) => void);
declare type OnAlphabetIndexerPopupSelectCallback = ((index: number) => void);
declare type OnAlphabetIndexerRequestPopupDataCallback = ((index: number) => string[]);
declare type Callback_Number_Void = ((index: number) => void);
declare class AlphabetIndexerAttribute extends CommonMethod<AlphabetIndexerAttribute> {
    onSelected(value: ((index: number) => void)): AlphabetIndexerAttribute;
    color(value: ResourceColor): AlphabetIndexerAttribute;
    selectedColor(value: ResourceColor): AlphabetIndexerAttribute;
    popupColor(value: ResourceColor): AlphabetIndexerAttribute;
    selectedBackgroundColor(value: ResourceColor): AlphabetIndexerAttribute;
    popupBackground(value: ResourceColor): AlphabetIndexerAttribute;
    popupSelectedColor(value: ResourceColor): AlphabetIndexerAttribute;
    popupUnselectedColor(value: ResourceColor): AlphabetIndexerAttribute;
    popupItemBackgroundColor(value: ResourceColor): AlphabetIndexerAttribute;
    usingPopup(value: boolean): AlphabetIndexerAttribute;
    selectedFont(value: Font): AlphabetIndexerAttribute;
    popupFont(value: Font): AlphabetIndexerAttribute;
    popupItemFont(value: Font): AlphabetIndexerAttribute;
    itemSize(value: (string|number)): AlphabetIndexerAttribute;
    font(value: Font): AlphabetIndexerAttribute;
    onSelect(value: OnAlphabetIndexerSelectCallback): AlphabetIndexerAttribute;
    onRequestPopupData(value: OnAlphabetIndexerRequestPopupDataCallback): AlphabetIndexerAttribute;
    onPopupSelect(value: OnAlphabetIndexerPopupSelectCallback): AlphabetIndexerAttribute;
    selected(value: number): AlphabetIndexerAttribute;
    popupPosition(value: Position): AlphabetIndexerAttribute;
    autoCollapse(value: boolean): AlphabetIndexerAttribute;
    popupItemBorderRadius(value: number): AlphabetIndexerAttribute;
    itemBorderRadius(value: number): AlphabetIndexerAttribute;
    popupBackgroundBlurStyle(value: BlurStyle): AlphabetIndexerAttribute;
    popupTitleBackground(value: ResourceColor): AlphabetIndexerAttribute;
    enableHapticFeedback(value: boolean): AlphabetIndexerAttribute;
    alignStyle(value: IndexerAlign, offset?: Length): AlphabetIndexerAttribute;
    _onChangeEvent_selected(callback_: ((index: number) => void)): void;
}
declare class SpringProp {
    constructor(mass: number, stiffness: number, damping: number);
}
declare class SpringMotion {
    constructor(start: number, end: number, velocity: number, prop: SpringProp);
}
declare class FrictionMotion {
    constructor(friction: number, position: number, velocity: number);
}
declare class ScrollMotion {
    constructor(position: number, velocity: number, min: number, max: number, prop: SpringProp);
}
declare interface AnimatorInterface {
    (value: string): AnimatorAttribute;
}
declare class AnimatorAttribute extends CommonMethod<AnimatorAttribute> {
    state(value: AnimationStatus): AnimatorAttribute;
    duration(value: number): AnimatorAttribute;
    curve(value: Curve): AnimatorAttribute;
    delay(value: number): AnimatorAttribute;
    fillMode(value: FillMode): AnimatorAttribute;
    iterations(value: number): AnimatorAttribute;
    playMode(value: PlayMode): AnimatorAttribute;
    motion(value: SpringMotion): AnimatorAttribute;
    onStart(value: (() => void)): AnimatorAttribute;
    onPause(value: (() => void)): AnimatorAttribute;
    onRepeat(value: (() => void)): AnimatorAttribute;
    onCancel(value: (() => void)): AnimatorAttribute;
    onFinish(value: (() => void)): AnimatorAttribute;
    onFrame(value: ((index: number) => void)): AnimatorAttribute;
}
declare enum BadgePosition {
    RIGHT_TOP = 0,
    RightTop = 0,
    RIGHT = 1,
    Right = 1,
    LEFT = 2,
    Left = 2,
}
declare interface BadgeStyle {
    color?: ResourceColor;
    fontSize?: (number|string);
    badgeSize?: (number|string);
    badgeColor?: ResourceColor;
    borderColor?: ResourceColor;
    borderWidth?: Length;
    fontWeight?: (number|FontWeight|string);
}
declare interface BadgeParam {
    position?: (BadgePosition|Position);
    style: BadgeStyle;
}
declare interface BadgeParamWithNumber extends BadgeParam {
    count: number;
    maxCount?: number;
}
declare interface BadgeParamWithString extends BadgeParam {
    value: string;
}
declare interface BadgeInterface {
    (value: BadgeParamWithNumber): BadgeAttribute;
    (value: BadgeParamWithString): BadgeAttribute;
}
declare class BadgeAttribute extends CommonMethod<BadgeAttribute> {
}
declare interface BlankInterface {
    (min?: (number|string)): BlankAttribute;
}
declare class BlankAttribute extends CommonMethod<BlankAttribute> {
    color(value: ResourceColor): BlankAttribute;
}
declare enum ButtonType {
    CAPSULE = 0,
    Capsule = 0,
    CIRCLE = 1,
    Circle = 1,
    NORMAL = 2,
    Normal = 2,
    ROUNDED_RECTANGLE = 3,
}
declare enum ButtonStyleMode {
    NORMAL = 0,
    EMPHASIZED = 1,
    TEXTUAL = 2,
}
declare enum ButtonRole {
    NORMAL = 0,
    ERROR = 1,
}
declare type ButtonTriggerClickCallback = ((xPos: number, yPos: number) => void);
declare interface ButtonConfiguration extends CommonConfiguration<ButtonConfiguration> {
    label: string;
    pressed: boolean;
    triggerClick: ButtonTriggerClickCallback;
}
declare enum ControlSize {
    SMALL = "small",
    NORMAL = "normal",
}
declare interface ButtonOptions {
    type?: ButtonType;
    stateEffect?: boolean;
    buttonStyle?: ButtonStyleMode;
    controlSize?: ControlSize;
    role?: ButtonRole;
}
declare interface ButtonInterface {
    (): ButtonAttribute;
    (options: ButtonOptions): ButtonAttribute;
    (label: ResourceStr, options?: ButtonOptions): ButtonAttribute;
}
declare interface LabelStyle {
    overflow?: TextOverflow;
    maxLines?: number;
    minFontSize?: (number|ResourceStr);
    maxFontSize?: (number|ResourceStr);
    heightAdaptivePolicy?: TextHeightAdaptivePolicy;
    font?: Font;
}
declare class ButtonAttribute extends CommonMethod<ButtonAttribute> {
    type(value: ButtonType): ButtonAttribute;
    stateEffect(value: boolean): ButtonAttribute;
    buttonStyle(value: ButtonStyleMode): ButtonAttribute;
    controlSize(value: ControlSize): ButtonAttribute;
    role(value: ButtonRole): ButtonAttribute;
    fontColor(value: ResourceColor): ButtonAttribute;
    fontSize(value: Length): ButtonAttribute;
    fontWeight(value: (number|FontWeight|string)): ButtonAttribute;
    fontStyle(value: FontStyle): ButtonAttribute;
    fontFamily(value: (string|Resource)): ButtonAttribute;
    contentModifier(value: ContentModifier<ButtonConfiguration>): ButtonAttribute;
    labelStyle(value: LabelStyle): ButtonAttribute;
}
declare interface CalendarDay {
    index: number;
    lunarMonth: string;
    lunarDay: string;
    dayMark: string;
    dayMarkValue: string;
    year: number;
    month: number;
    day: number;
    isFirstOfLunar: boolean;
    hasSchedule: boolean;
    markLunarDay: boolean;
}
declare interface MonthData {
    year: number;
    month: number;
    data: CalendarDay[];
}
declare interface CurrentDayStyle {
    dayColor?: ResourceColor;
    lunarColor?: ResourceColor;
    markLunarColor?: ResourceColor;
    dayFontSize?: number;
    lunarDayFontSize?: number;
    dayHeight?: number;
    dayWidth?: number;
    gregorianCalendarHeight?: number;
    dayYAxisOffset?: number;
    lunarDayYAxisOffset?: number;
    underscoreXAxisOffset?: number;
    underscoreYAxisOffset?: number;
    scheduleMarkerXAxisOffset?: number;
    scheduleMarkerYAxisOffset?: number;
    colSpace?: number;
    dailyFiveRowSpace?: number;
    dailySixRowSpace?: number;
    lunarHeight?: number;
    underscoreWidth?: number;
    underscoreLength?: number;
    scheduleMarkerRadius?: number;
    boundaryRowOffset?: number;
    boundaryColOffset?: number;
}
declare interface NonCurrentDayStyle {
    nonCurrentMonthDayColor?: ResourceColor;
    nonCurrentMonthLunarColor?: ResourceColor;
    nonCurrentMonthWorkDayMarkColor?: ResourceColor;
    nonCurrentMonthOffDayMarkColor?: ResourceColor;
}
declare interface TodayStyle {
    focusedDayColor?: ResourceColor;
    focusedLunarColor?: ResourceColor;
    focusedAreaBackgroundColor?: ResourceColor;
    focusedAreaRadius?: number;
}
declare interface WeekStyle {
    weekColor?: ResourceColor;
    weekendDayColor?: ResourceColor;
    weekendLunarColor?: ResourceColor;
    weekFontSize?: number;
    weekHeight?: number;
    weekWidth?: number;
    weekAndDayRowSpace?: number;
}
declare interface WorkStateStyle {
    workDayMarkColor?: ResourceColor;
    offDayMarkColor?: ResourceColor;
    workDayMarkSize?: number;
    offDayMarkSize?: number;
    workStateWidth?: number;
    workStateHorizontalMovingDistance?: number;
    workStateVerticalMovingDistance?: number;
}
declare interface CalendarSelectedDate {
    year: number;
    month: number;
    day: number;
}
declare interface CalendarRequestedData {
    year: number;
    month: number;
    currentYear: number;
    currentMonth: number;
    monthState: number;
}
declare type Literal_Number_day_month_year = { year: number, month: number, day: number }
declare class CalendarController {
    constructor();
    backToToday(): void;
    goTo(value: { year: number, month: number, day: number }): void;
}
declare type Type_CalendarInterface_value = { date: { year: number, month: number, day: number }, currentData: MonthData, preData: MonthData, nextData: MonthData, controller?: CalendarController }
declare interface CalendarInterface {
    (value: { date: { year: number, month: number, day: number }, currentData: MonthData, preData: MonthData, nextData: MonthData, controller?: CalendarController }): CalendarAttribute;
}
declare type Callback_CalendarSelectedDate_Void = ((event: CalendarSelectedDate) => void);
declare type Callback_CalendarRequestedData_Void = ((event: CalendarRequestedData) => void);
declare class CalendarAttribute {
    showLunar(value: boolean): CalendarAttribute;
    showHoliday(value: boolean): CalendarAttribute;
    needSlide(value: boolean): CalendarAttribute;
    startOfWeek(value: number): CalendarAttribute;
    offDays(value: number): CalendarAttribute;
    direction(value: Axis): CalendarAttribute;
    currentDayStyle(value: CurrentDayStyle): CalendarAttribute;
    nonCurrentDayStyle(value: NonCurrentDayStyle): CalendarAttribute;
    todayStyle(value: TodayStyle): CalendarAttribute;
    weekStyle(value: WeekStyle): CalendarAttribute;
    workStateStyle(value: WorkStateStyle): CalendarAttribute;
    onSelectChange(value: ((event: CalendarSelectedDate) => void)): CalendarAttribute;
    onRequestData(value: ((event: CalendarRequestedData) => void)): CalendarAttribute;
}
declare enum CalendarAlign {
    START = 0,
    CENTER = 1,
    END = 2,
}
declare interface CalendarOptions {
    hintRadius?: (number|Resource);
    selected?: Date;
}
declare interface CalendarPickerInterface {
    (options?: CalendarOptions): CalendarPickerAttribute;
}
declare type Callback_Date_Void = ((parameter: Date) => void);
declare class CalendarPickerAttribute extends CommonMethod<CalendarPickerAttribute> {
    textStyle(value: PickerTextStyle): CalendarPickerAttribute;
    onChange(value: ((parameter: Date) => void)): CalendarPickerAttribute;
    edgeAlign(alignType: CalendarAlign, offset?: Offset): CalendarPickerAttribute;
}
declare interface CalendarDialogOptions extends CalendarOptions {
    onAccept?: ((parameter: Date) => void);
    onCancel?: VoidCallback;
    onChange?: ((parameter: Date) => void);
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    acceptButtonStyle?: PickerDialogButtonStyle;
    cancelButtonStyle?: PickerDialogButtonStyle;
    onDidAppear?: VoidCallback;
    onDidDisappear?: VoidCallback;
    onWillAppear?: VoidCallback;
    onWillDisappear?: VoidCallback;
    shadow?: (ShadowOptions|ShadowStyle);
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
}
declare class CalendarPickerDialog {
}
declare type CanvasFillRule = string;
declare type CanvasLineCap = string;
declare type CanvasLineJoin = string;
declare type CanvasDirection = string;
declare type CanvasTextAlign = string;
declare type CanvasTextBaseline = string;
declare type ImageSmoothingQuality = string;
declare class CanvasGradient {
    addColorStop(offset: number, color: string): void;
}
declare class CanvasPath {
    arc(x: number, y: number, radius: number, startAngle: number, endAngle: number, counterclockwise?: boolean): void;
    arcTo(x1: number, y1: number, x2: number, y2: number, radius: number): void;
    bezierCurveTo(cp1x: number, cp1y: number, cp2x: number, cp2y: number, x: number, y: number): void;
    closePath(): void;
    ellipse(x: number, y: number, radiusX: number, radiusY: number, rotation: number, startAngle: number, endAngle: number, counterclockwise?: boolean): void;
    lineTo(x: number, y: number): void;
    moveTo(x: number, y: number): void;
    quadraticCurveTo(cpx: number, cpy: number, x: number, y: number): void;
    rect(x: number, y: number, w: number, h: number): void;
}
declare class Path2D extends CanvasPath {
    constructor();
    constructor(unit: LengthMetricsUnit);
    constructor(path: Path2D);
    constructor(path: Path2D, unit: LengthMetricsUnit);
    constructor(d: string);
    constructor(description: string, unit: LengthMetricsUnit);
    addPath(path: Path2D, transform?: Matrix2D): void;
}
declare interface CanvasPattern {
    setTransform(transform?: Matrix2D): void;
}
declare interface TextMetrics {
    readonly actualBoundingBoxAscent: number;
    readonly actualBoundingBoxDescent: number;
    readonly actualBoundingBoxLeft: number;
    readonly actualBoundingBoxRight: number;
    readonly alphabeticBaseline: number;
    readonly emHeightAscent: number;
    readonly emHeightDescent: number;
    readonly fontBoundingBoxAscent: number;
    readonly fontBoundingBoxDescent: number;
    readonly hangingBaseline: number;
    readonly ideographicBaseline: number;
    readonly width: number;
    readonly height: number;
}
declare class ImageBitmap {
    constructor(src: string);
    constructor(src: string, unit: LengthMetricsUnit);
    constructor(data: PixelMap);
    constructor(data: PixelMap, unit: LengthMetricsUnit);
    readonly height: number;
    readonly width: number;
    close(): void;
}
declare class ImageData {
    constructor(width: number, height: number, data?: ArrayBuffer);
    constructor(width: number, height: number, data?: ArrayBuffer, unit?: LengthMetricsUnit);
    readonly data: ArrayBuffer;
    readonly height: number;
    readonly width: number;
}
declare class RenderingContextSettings {
    constructor(antialias?: boolean);
    antialias?: boolean;
}
declare class CanvasRenderer extends CanvasPath {
    globalAlpha: number;
    globalCompositeOperation: string;
    fillStyle: (string|number|CanvasGradient|CanvasPattern);
    strokeStyle: (string|number|CanvasGradient|CanvasPattern);
    filter: string;
    imageSmoothingEnabled: boolean;
    imageSmoothingQuality: ImageSmoothingQuality;
    lineCap: CanvasLineCap;
    lineDashOffset: number;
    lineJoin: CanvasLineJoin;
    lineWidth: number;
    miterLimit: number;
    shadowBlur: number;
    shadowColor: string;
    shadowOffsetX: number;
    shadowOffsetY: number;
    direction: CanvasDirection;
    font: string;
    textAlign: CanvasTextAlign;
    textBaseline: CanvasTextBaseline;
    drawImage(image: (ImageBitmap|PixelMap), dx: number, dy: number): void;
    drawImage(image: (ImageBitmap|PixelMap), dx: number, dy: number, dw: number, dh: number): void;
    drawImage(image: (ImageBitmap|PixelMap), sx: number, sy: number, sw: number, sh: number, dx: number, dy: number, dw: number, dh: number): void;
    beginPath(): void;
    clip(fillRule?: CanvasFillRule): void;
    clip(path: Path2D, fillRule?: CanvasFillRule): void;
    fill(fillRule?: CanvasFillRule): void;
    fill(path: Path2D, fillRule?: CanvasFillRule): void;
    stroke(): void;
    stroke(path: Path2D): void;
    createLinearGradient(x0: number, y0: number, x1: number, y1: number): CanvasGradient;
    createPattern(image: ImageBitmap, repetition: string | undefined): CanvasPattern | undefined;
    createRadialGradient(x0: number, y0: number, r0: number, x1: number, y1: number, r1: number): CanvasGradient;
    createConicGradient(startAngle: number, x: number, y: number): CanvasGradient;
    createImageData(sw: number, sh: number): ImageData;
    createImageData(imagedata: ImageData): ImageData;
    getImageData(sx: number, sy: number, sw: number, sh: number): ImageData;
    getPixelMap(sx: number, sy: number, sw: number, sh: number): PixelMap;
    putImageData(imagedata: ImageData, dx: (number|string), dy: (number|string)): void;
    putImageData(imagedata: ImageData, dx: (number|string), dy: (number|string), dirtyX: (number|string), dirtyY: (number|string), dirtyWidth: (number|string), dirtyHeight: (number|string)): void;
    getLineDash(): number[];
    setLineDash(segments: number[]): void;
    clearRect(x: number, y: number, w: number, h: number): void;
    fillRect(x: number, y: number, w: number, h: number): void;
    strokeRect(x: number, y: number, w: number, h: number): void;
    restore(): void;
    save(): void;
    fillText(text: string, x: number, y: number, maxWidth?: number): void;
    measureText(text: string): TextMetrics;
    strokeText(text: string, x: number, y: number, maxWidth?: number): void;
    getTransform(): Matrix2D;
    resetTransform(): void;
    rotate(angle: number): void;
    scale(x: number, y: number): void;
    setTransform(a: number, b: number, c: number, d: number, e: number, f: number): void;
    setTransform(transform?: Matrix2D): void;
    transform(a: number, b: number, c: number, d: number, e: number, f: number): void;
    translate(x: number, y: number): void;
    setPixelMap(value?: PixelMap): void;
    transferFromImageBitmap(bitmap: ImageBitmap): void;
    saveLayer(): void;
    restoreLayer(): void;
    reset(): void;
}
declare class CanvasRenderingContext2D extends CanvasRenderer {
    constructor(settings?: RenderingContextSettings);
    constructor(settings?: RenderingContextSettings, unit?: LengthMetricsUnit);
    readonly height: number;
    readonly width: number;
    readonly canvas: FrameNode;
    toDataURL(type?: string | undefined, quality?: number | undefined): string;
    startImageAnalyzer(config: ImageAnalyzerConfig): Promise<void>;
    stopImageAnalyzer(): void;
    on(type: 'onAttach', callback_: (() => void)): void;
    off(type: 'onAttach', callback_?: (() => void)): void;
    on(type: 'onDetach', callback_: (() => void)): void;
    off(type: 'onDetach', callback_?: (() => void)): void;
}
declare class OffscreenCanvasRenderingContext2D extends CanvasRenderer {
    constructor(width: number, height: number, settings?: RenderingContextSettings);
    constructor(width: number, height: number, settings?: RenderingContextSettings, unit?: LengthMetricsUnit);
    toDataURL(type?: string | undefined, quality?: number | undefined): string;
    transferToImageBitmap(): ImageBitmap;
}
declare class OffscreenCanvas {
    constructor(width: number, height: number);
    constructor(width: number, height: number, unit: LengthMetricsUnit);
    height: number;
    width: number;
    transferToImageBitmap(): ImageBitmap;
    getContext(contextType: "2d", options?: RenderingContextSettings): OffscreenCanvasRenderingContext2D;
}
declare interface Size {
    width: number;
    height: number;
}
declare class DrawingRenderingContext {
    constructor(unit?: LengthMetricsUnit);
    get size(): Size;
    get canvas(): DrawingCanvas;
    invalidate(): void;
}
declare interface CanvasInterface {
    (context?: (CanvasRenderingContext2D|DrawingRenderingContext)): CanvasAttribute;
    (context: (CanvasRenderingContext2D|DrawingRenderingContext), imageAIOptions: ImageAIOptions): CanvasAttribute;
}
declare class CanvasAttribute extends CommonMethod<CanvasAttribute> {
    onReady(value: VoidCallback): CanvasAttribute;
    enableAnalyzer(value: boolean): CanvasAttribute;
}
declare interface CheckboxOptions {
    name?: string;
    group?: string;
    indicatorBuilder?: CustomBuilder;
}
declare type Callback_Boolean_Void = ((parameter: boolean) => void);
declare interface CheckBoxConfiguration extends CommonConfiguration<CheckBoxConfiguration> {
    name: string;
    selected: boolean;
    triggerChange: ((parameter: boolean) => void);
}
declare interface CheckboxInterface {
    (options?: CheckboxOptions): CheckboxAttribute;
}
declare type OnCheckboxChangeCallback = ((value: boolean) => void);
declare class CheckboxAttribute extends CommonMethod<CheckboxAttribute> {
    select(value: boolean): CheckboxAttribute;
    selectedColor(value: ResourceColor): CheckboxAttribute;
    shape(value: CheckBoxShape): CheckboxAttribute;
    unselectedColor(value: ResourceColor): CheckboxAttribute;
    mark(value: MarkStyle): CheckboxAttribute;
    onChange(value: OnCheckboxChangeCallback): CheckboxAttribute;
    contentModifier(value: ContentModifier<CheckBoxConfiguration>): CheckboxAttribute;
    _onChangeEvent_select(callback_: ((parameter: boolean) => void)): void;
}
declare enum SelectStatus {
    ALL = 0,
    All = 0,
    PART = 1,
    Part = 1,
    NONE = 2,
    None = 2,
}
declare interface CheckboxGroupOptions {
    group?: string;
}
declare interface CheckboxGroupResult {
    name: string[];
    status: SelectStatus;
}
declare interface CheckboxGroupInterface {
    (options?: CheckboxGroupOptions): CheckboxGroupAttribute;
}
declare type OnCheckboxGroupChangeCallback = ((value: CheckboxGroupResult) => void);
declare class CheckboxGroupAttribute extends CommonMethod<CheckboxGroupAttribute> {
    selectAll(value: boolean): CheckboxGroupAttribute;
    selectedColor(value: ResourceColor): CheckboxGroupAttribute;
    unselectedColor(value: ResourceColor): CheckboxGroupAttribute;
    mark(value: MarkStyle): CheckboxGroupAttribute;
    onChange(value: OnCheckboxGroupChangeCallback): CheckboxGroupAttribute;
    checkboxShape(value: CheckBoxShape): CheckboxGroupAttribute;
    _onChangeEvent_selectAll(callback_: ((parameter: boolean) => void)): void;
}
declare interface CircleOptions {
    width?: (string|number);
    height?: (string|number);
}
declare interface CircleInterface {
    new(value?: CircleOptions): CircleAttribute;
    (value?: CircleOptions): CircleAttribute;
}
declare class CircleAttribute extends CommonShapeMethod<CircleAttribute> {
}
declare interface ColumnOptions {
    space?: (string|number);
}
declare interface ColumnInterface {
    (options?: ColumnOptions): ColumnAttribute;
}
declare class ColumnAttribute extends CommonMethod<ColumnAttribute> {
    alignItems(value: HorizontalAlign): ColumnAttribute;
    justifyContent(value: FlexAlign): ColumnAttribute;
    pointLight(value: PointLightStyle): ColumnAttribute;
    reverse(value: boolean | undefined): ColumnAttribute;
}
declare interface ColumnSplitInterface {
    (): ColumnSplitAttribute;
}
declare interface ColumnSplitDividerStyle {
    startMargin?: Dimension;
    endMargin?: Dimension;
}
declare class ColumnSplitAttribute extends CommonMethod<ColumnSplitAttribute> {
    resizeable(value: boolean): ColumnSplitAttribute;
    divider(value: ColumnSplitDividerStyle | undefined): ColumnSplitAttribute;
}
declare interface ComponentOptions {
    freezeWhenInactive: boolean;
}
declare interface InputCounterOptions {
    thresholdPercentage?: number;
    highlightBorder?: boolean;
}
declare interface TextDecorationOptions {
    type: TextDecorationType;
    color?: ResourceColor;
    style?: TextDecorationStyle;
}
declare interface ProvideOptions {
    allowOverride?: string;
}
declare interface AnimatableArithmetic<T> {
    plus(rhs: AnimatableArithmetic<T>): AnimatableArithmetic<T>;
    subtract(rhs: AnimatableArithmetic<T>): AnimatableArithmetic<T>;
    multiply(scale: number): AnimatableArithmetic<T>;
    equals(rhs: AnimatableArithmetic<T>): boolean;
}
declare function getContext(component?: Object): Context;
declare interface Context {
    _ContextStub: string;
}
declare function postCardAction(component: Object, action: Object): void;
declare interface Configuration {
    readonly colorMode: string;
    readonly fontScale: number;
}
declare interface Rectangle {
    x?: Length;
    y?: Length;
    width?: Length;
    height?: Length;
}
declare interface ExpectedFrameRateRange {
    min: number;
    max: number;
    expected: number;
}
declare function $r(value: string, ...params: any[]): Resource;
declare function $rawfile(value: string): Resource;
declare enum FinishCallbackType {
    REMOVED = 0,
    LOGICALLY = 1,
}
declare enum TouchTestStrategy {
    DEFAULT = 0,
    FORWARD_COMPETITION = 1,
    FORWARD = 2,
}
declare interface AnimateParam {
    duration?: number;
    tempo?: number;
    curve?: (Curve|string|ICurve);
    delay?: number;
    iterations?: number;
    playMode?: PlayMode;
    onFinish?: (() => void);
    finishCallbackType?: FinishCallbackType;
    expectedFrameRateRange?: ExpectedFrameRateRange;
}
declare interface ICurve {
    interpolate(fraction: number): number;
}
declare interface MotionPathOptions {
    path: string;
    from?: number;
    to?: number;
    rotatable?: boolean;
}
declare interface sharedTransitionOptions {
    duration?: number;
    curve?: (Curve|string|ICurve);
    delay?: number;
    motionPath?: MotionPathOptions;
    zIndex?: number;
    type?: SharedTransitionEffectType;
}
declare interface GeometryTransitionOptions {
    follow?: boolean;
    hierarchyStrategy?: TransitionHierarchyStrategy;
}
declare enum TransitionHierarchyStrategy {
    NONE = 0,
    ADAPTIVE = 1,
}
declare interface TranslateOptions {
    x?: (number|string);
    y?: (number|string);
    z?: (number|string);
}
declare interface ScaleOptions {
    x?: number;
    y?: number;
    z?: number;
    centerX?: (number|string);
    centerY?: (number|string);
}
declare type Literal_String_anchor_HorizontalAlign_align = { anchor: string, align: HorizontalAlign }
declare type Literal_String_anchor_VerticalAlign_align = { anchor: string, align: VerticalAlign }
declare interface AlignRuleOption {
    left?: { anchor: string, align: HorizontalAlign };
    right?: { anchor: string, align: HorizontalAlign };
    middle?: { anchor: string, align: HorizontalAlign };
    top?: { anchor: string, align: VerticalAlign };
    bottom?: { anchor: string, align: VerticalAlign };
    center?: { anchor: string, align: VerticalAlign };
    bias?: Bias;
}
declare interface LocalizedHorizontalAlignParam {
    anchor: string;
    align: HorizontalAlign;
}
declare interface LocalizedVerticalAlignParam {
    anchor: string;
    align: VerticalAlign;
}
declare interface LocalizedAlignRuleOptions {
    start?: LocalizedHorizontalAlignParam;
    end?: LocalizedHorizontalAlignParam;
    middle?: LocalizedHorizontalAlignParam;
    top?: LocalizedVerticalAlignParam;
    bottom?: LocalizedVerticalAlignParam;
    center?: LocalizedVerticalAlignParam;
    bias?: Bias;
}
declare enum ChainStyle {
    SPREAD = 0,
    SPREAD_INSIDE = 1,
    PACKED = 2,
}
declare interface RotateOptions {
    x?: number;
    y?: number;
    z?: number;
    centerX?: (number|string);
    centerY?: (number|string);
    centerZ?: number;
    perspective?: number;
    angle: (number|string);
}
declare interface TransitionOptions {
    type?: TransitionType;
    opacity?: number;
    translate?: TranslateOptions;
    scale?: ScaleOptions;
    rotate?: RotateOptions;
}
declare enum TransitionEdge {
    TOP = 0,
    BOTTOM = 1,
    START = 2,
    END = 3,
}
declare type Literal_TransitionEffect_appear_disappear = { appear: TransitionEffect, disappear: TransitionEffect }
declare type TransitionEffects = { identity: undefined, opacity: number, slideSwitch: undefined, move: TransitionEdge, translate: TranslateOptions, rotate: RotateOptions, scale: ScaleOptions, asymmetric: { appear: TransitionEffect, disappear: TransitionEffect } }
declare class DrawModifier {
    drawBehind?(drawContext: DrawContext): void;
    drawContent?(drawContext: DrawContext): void;
    drawFront?(drawContext: DrawContext): void;
    invalidate(): void;
}
declare class TransitionEffect {
    constructor(type: string, effect: TransitionEffects);
    animation(value: AnimateParam): TransitionEffect;
    combine(transitionEffect: TransitionEffect): TransitionEffect;
}
declare interface PreviewParams {
    title?: string;
    width?: number;
    height?: number;
    locale?: string;
    colorMode?: string;
    deviceType?: string;
    dpi?: number;
    orientation?: string;
    roundScreen?: boolean;
}
declare interface ItemDragInfo {
    x: number;
    y: number;
}
declare enum EffectType {
    DEFAULT = 0,
    WINDOW_EFFECT = 1,
}
declare enum PreDragStatus {
    ACTION_DETECTING_STATUS = 0,
    READY_TO_TRIGGER_DRAG_ACTION = 1,
    PREVIEW_LIFT_STARTED = 2,
    PREVIEW_LIFT_FINISHED = 3,
    PREVIEW_LANDING_STARTED = 4,
    PREVIEW_LANDING_FINISHED = 5,
    ACTION_CANCELED_BEFORE_DRAG = 6,
}
declare interface DragItemInfo {
    pixelMap?: PixelMap;
    builder?: CustomBuilder;
    extraInfo?: string;
}
declare function animateTo(value: AnimateParam, event: (() => void)): void;
declare function animateToImmediately(value: AnimateParam, event: (() => void)): void;
declare function vp2px(value: number): number;
declare function px2vp(value: number): number;
declare function fp2px(value: number): number;
declare function px2fp(value: number): number;
declare function lpx2px(value: number): number;
declare function px2lpx(value: number): number;
declare namespace focusControl {
    function requestFocus(value: string): boolean;
}
declare namespace cursorControl {
    function setCursor(value: PointerStyle): void;
}
declare namespace cursorControl {
    function restoreDefault(): void;
}
declare interface EventTarget {
    area: Area;
}
declare enum SourceType {
    UNKNOWN = 0,
    Unknown = 0,
    MOUSE = 1,
    Mouse = 1,
    TOUCH_SCREEN = 2,
    TouchScreen = 2,
}
declare enum SourceTool {
    UNKNOWN = 0,
    Unknown = 0,
    FINGER = 1,
    Finger = 1,
    PEN = 2,
    Pen = 2,
    MOUSE = 3,
    TOUCHPAD = 4,
    JOYSTICK = 5,
}
declare enum RepeatMode {
    REPEAT = 0,
    Repeat = 0,
    STRETCH = 1,
    Stretch = 1,
    ROUND = 2,
    Round = 2,
    SPACE = 3,
    Space = 3,
}
declare enum BlurStyle {
    THIN = 0,
    Thin = 0,
    REGULAR = 1,
    Regular = 1,
    THICK = 2,
    Thick = 2,
    BACKGROUND_THIN = 3,
    BACKGROUND_REGULAR = 4,
    BACKGROUND_THICK = 5,
    BACKGROUND_ULTRA_THICK = 6,
    NONE = 7,
    COMPONENT_ULTRA_THIN = 8,
    COMPONENT_THIN = 9,
    COMPONENT_REGULAR = 10,
    COMPONENT_THICK = 11,
    COMPONENT_ULTRA_THICK = 12,
}
declare enum BlurStyleActivePolicy {
    FOLLOWS_WINDOW_ACTIVE_STATE = 0,
    ALWAYS_ACTIVE = 1,
    ALWAYS_INACTIVE = 2,
}
declare enum ThemeColorMode {
    SYSTEM = 0,
    LIGHT = 1,
    DARK = 2,
}
declare enum AdaptiveColor {
    DEFAULT = 0,
    AVERAGE = 1,
}
declare enum ModalTransition {
    DEFAULT = 0,
    NONE = 1,
    ALPHA = 2,
}
declare interface BackgroundBlurStyleOptions extends BlurStyleOptions {
    policy?: BlurStyleActivePolicy;
    inactiveColor?: ResourceColor;
}
declare interface ForegroundBlurStyleOptions extends BlurStyleOptions {
}
declare type Tuple_Number_Number = [ number, number ]
declare interface BlurOptions {
    grayscale: [ number, number ];
}
declare interface BlurStyleOptions {
    colorMode?: ThemeColorMode;
    adaptiveColor?: AdaptiveColor;
    scale?: number;
    blurOptions?: BlurOptions;
}
declare interface BackgroundEffectOptions {
    radius: number;
    saturation?: number;
    brightness?: number;
    color?: ResourceColor;
    adaptiveColor?: AdaptiveColor;
    blurOptions?: BlurOptions;
    policy?: BlurStyleActivePolicy;
    inactiveColor?: ResourceColor;
}
declare interface ForegroundEffectOptions {
    radius: number;
}
declare interface PickerTextStyle {
    color?: ResourceColor;
    font?: Font;
}
declare interface PickerDialogButtonStyle {
    type?: ButtonType;
    style?: ButtonStyleMode;
    role?: ButtonRole;
    fontSize?: Length;
    fontColor?: ResourceColor;
    fontWeight?: (FontWeight|number|string);
    fontStyle?: FontStyle;
    fontFamily?: (Resource|string);
    backgroundColor?: ResourceColor;
    borderRadius?: (Length|BorderRadiuses);
    primary?: boolean;
}
declare enum ShadowType {
    COLOR = 0,
    BLUR = 1,
}
declare interface ShadowOptions {
    radius: (number|Resource);
    type?: ShadowType;
    color?: (Color|string|Resource|ColoringStrategy);
    offsetX?: (number|Resource);
    offsetY?: (number|Resource);
    fill?: boolean;
}
declare enum ShadowStyle {
    OUTER_DEFAULT_XS = 0,
    OUTER_DEFAULT_SM = 1,
    OUTER_DEFAULT_MD = 2,
    OUTER_DEFAULT_LG = 3,
    OUTER_FLOATING_SM = 4,
    OUTER_FLOATING_MD = 5,
}
declare interface MultiShadowOptions {
    radius?: (number|Resource);
    offsetX?: (number|Resource);
    offsetY?: (number|Resource);
}
declare enum SafeAreaType {
    SYSTEM = 0,
    CUTOUT = 1,
    KEYBOARD = 2,
}
declare enum SafeAreaEdge {
    TOP = 0,
    BOTTOM = 1,
    START = 2,
    END = 3,
}
declare enum LayoutSafeAreaType {
    SYSTEM = 0,
}
declare enum LayoutSafeAreaEdge {
    TOP = 0,
    BOTTOM = 1,
}
declare enum SheetSize {
    MEDIUM = 0,
    LARGE = 1,
    FIT_CONTENT = 2,
}
declare interface BaseEvent {
    target: EventTarget;
    timestamp: number;
    source: SourceType;
    axisHorizontal?: number;
    axisVertical?: number;
    pressure: number;
    tiltX: number;
    tiltY: number;
    sourceTool: SourceTool;
    deviceId?: number;
    getModifierKeyState?(keys: string[]): boolean;
}
declare interface BorderImageOption {
    slice?: (Length|EdgeWidths|LocalizedEdgeWidths);
    repeat?: RepeatMode;
    source?: (string|Resource|LinearGradient_common);
    width?: (Length|EdgeWidths|LocalizedEdgeWidths);
    outset?: (Length|EdgeWidths|LocalizedEdgeWidths);
    fill?: boolean;
}
declare interface ClickEvent extends BaseEvent {
    displayX: number;
    displayY: number;
    windowX: number;
    windowY: number;
    screenX: number;
    screenY: number;
    x: number;
    y: number;
    preventDefault: (() => void);
}
declare interface HoverEvent extends BaseEvent {
    stopPropagation: (() => void);
}
declare interface MouseEvent extends BaseEvent {
    button: MouseButton;
    action: MouseAction;
    displayX: number;
    displayY: number;
    windowX: number;
    windowY: number;
    screenX: number;
    screenY: number;
    x: number;
    y: number;
    stopPropagation: (() => void);
}
declare interface AccessibilityHoverEvent extends BaseEvent {
    type: AccessibilityHoverType;
    x: number;
    y: number;
    displayX: number;
    displayY: number;
    windowX: number;
    windowY: number;
}
declare interface TouchObject {
    type: TouchType;
    id: number;
    displayX: number;
    displayY: number;
    windowX: number;
    windowY: number;
    screenX: number;
    screenY: number;
    x: number;
    y: number;
}
declare interface HistoricalPoint {
    touchObject: TouchObject;
    size: number;
    force: number;
    timestamp: number;
}
declare interface TouchEvent extends BaseEvent {
    type: TouchType;
    touches: TouchObject[];
    changedTouches: TouchObject[];
    stopPropagation: (() => void);
    preventDefault: (() => void);
    getHistoricalPoints(): HistoricalPoint[];
}
declare type SizeChangeCallback = ((oldValue: SizeOptions, newValue: SizeOptions) => void);
declare type GestureRecognizerJudgeBeginCallback = ((event: BaseGestureEvent, current: GestureRecognizer, recognizers: GestureRecognizer[]) => GestureJudgeResult);
declare type ShouldBuiltInRecognizerParallelWithCallback = ((current: GestureRecognizer, others: GestureRecognizer[]) => GestureRecognizer);
declare type TransitionFinishCallback = ((transitionIn: boolean) => void);
declare interface PixelMapMock {
    release(): void;
}
declare enum DragBehavior {
    COPY = 0,
    MOVE = 1,
}
declare interface Summary {
    _SummaryStub: string;
}
declare interface UniformDataType {
    _UniformDataTypeStub: string;
}
declare enum DragResult {
    DRAG_SUCCESSFUL = 0,
    DRAG_FAILED = 1,
    DRAG_CANCELED = 2,
    DROP_ENABLED = 3,
    DROP_DISABLED = 4,
}
declare enum BlendMode {
    NONE = 0,
    CLEAR = 1,
    SRC = 2,
    DST = 3,
    SRC_OVER = 4,
    DST_OVER = 5,
    SRC_IN = 6,
    DST_IN = 7,
    SRC_OUT = 8,
    DST_OUT = 9,
    SRC_ATOP = 10,
    DST_ATOP = 11,
    XOR = 12,
    PLUS = 13,
    MODULATE = 14,
    SCREEN = 15,
    OVERLAY = 16,
    DARKEN = 17,
    LIGHTEN = 18,
    COLOR_DODGE = 19,
    COLOR_BURN = 20,
    HARD_LIGHT = 21,
    SOFT_LIGHT = 22,
    DIFFERENCE = 23,
    EXCLUSION = 24,
    MULTIPLY = 25,
    HUE = 26,
    SATURATION = 27,
    COLOR = 28,
    LUMINOSITY = 29,
}
declare enum BlendApplyType {
    FAST = 0,
    OFFSCREEN = 1,
}
declare interface DragEvent {
    dragBehavior: DragBehavior;
    useCustomDropAnimation: boolean;
    getDisplayX(): number;
    getDisplayY(): number;
    getWindowX(): number;
    getWindowY(): number;
    getX(): number;
    getY(): number;
    setData(unifiedData: UnifiedData): void;
    getData(): UnifiedData;
    getSummary(): Summary;
    setResult(dragResult: DragResult): void;
    getResult(): DragResult;
    getPreviewRect(): Rectangle;
    getVelocityX(): number;
    getVelocityY(): number;
    getVelocity(): number;
    getModifierKeyState?(keys: string[]): boolean;
}
declare interface IntentionCode {
    _IntentionCodeStub: string;
}
declare interface KeyEvent {
    type: KeyType;
    keyCode: number;
    keyText: string;
    keySource: KeySource;
    deviceId: number;
    metaKey: number;
    timestamp: number;
    stopPropagation: (() => void);
    intentionCode: IntentionCode;
    unicode?: number;
    getModifierKeyState?(keys: string[]): boolean;
}
declare interface BindOptions {
    backgroundColor?: ResourceColor;
    onAppear?: (() => void);
    onDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
}
declare interface DismissContentCoverAction {
    dismiss: (() => void);
    reason: DismissReason;
}
declare type Callback_DismissContentCoverAction_Void = ((parameter: DismissContentCoverAction) => void);
declare interface ContentCoverOptions extends BindOptions {
    modalTransition?: ModalTransition;
    onWillDismiss?: ((parameter: DismissContentCoverAction) => void);
    transition?: TransitionEffect;
}
declare interface SheetTitleOptions {
    title: ResourceStr;
    subtitle?: ResourceStr;
}
declare enum SheetType {
    BOTTOM = 0,
    CENTER = 1,
    POPUP = 2,
}
declare enum SheetMode {
    OVERLAY = 0,
    EMBEDDED = 1,
}
declare enum ScrollSizeMode {
    FOLLOW_DETENT = 0,
    CONTINUOUS = 1,
}
declare enum SheetKeyboardAvoidMode {
    NONE = 0,
    TRANSLATE_AND_RESIZE = 1,
    RESIZE_ONLY = 2,
    TRANSLATE_AND_SCROLL = 3,
}
declare interface SheetDismiss {
    dismiss: (() => void);
}
declare interface DismissSheetAction {
    dismiss: (() => void);
    reason: DismissReason;
}
declare interface SpringBackAction {
    springBack: (() => void);
}
declare type Type_SheetOptions_detents = [ (SheetSize|Length), (SheetSize|Length)?, (SheetSize|Length)? ]
declare type Callback_SheetDismiss_Void = ((sheetDismiss: SheetDismiss) => void);
declare type Callback_DismissSheetAction_Void = ((parameter: DismissSheetAction) => void);
declare type Callback_SpringBackAction_Void = ((parameter: SpringBackAction) => void);
declare type Callback_SheetType_Void = ((parameter: SheetType) => void);
declare interface SheetOptions extends BindOptions {
    height?: (SheetSize|Length);
    dragBar?: boolean;
    maskColor?: ResourceColor;
    detents?: [ (SheetSize|Length), (SheetSize|Length)?, (SheetSize|Length)? ];
    blurStyle?: BlurStyle;
    showClose?: (boolean|Resource);
    preferType?: SheetType;
    title?: (SheetTitleOptions|CustomBuilder);
    shouldDismiss?: ((sheetDismiss: SheetDismiss) => void);
    onWillDismiss?: ((parameter: DismissSheetAction) => void);
    onWillSpringBackWhenDismiss?: ((parameter: SpringBackAction) => void);
    enableOutsideInteractive?: boolean;
    width?: Dimension;
    borderWidth?: (Dimension|EdgeWidths|LocalizedEdgeWidths);
    borderColor?: (ResourceColor|EdgeColors|LocalizedEdgeColors);
    borderStyle?: (BorderStyle|EdgeStyles);
    shadow?: (ShadowOptions|ShadowStyle);
    onHeightDidChange?: ((index: number) => void);
    mode?: SheetMode;
    scrollSizeMode?: ScrollSizeMode;
    onDetentsDidChange?: ((index: number) => void);
    onWidthDidChange?: ((index: number) => void);
    onTypeDidChange?: ((parameter: SheetType) => void);
    uiContext?: UIContext;
    keyboardAvoidMode?: SheetKeyboardAvoidMode;
}
declare interface StateStyles {
    normal?: any;
    pressed?: any;
    disabled?: any;
    focused?: any;
    clicked?: any;
    selected?: Object;
}
declare interface PopupMessageOptions {
    textColor?: ResourceColor;
    font?: Font;
}
declare enum DismissReason {
    PRESS_BACK = 0,
    TOUCH_OUTSIDE = 1,
    CLOSE_BUTTON = 2,
    SLIDE_DOWN = 3,
}
declare interface DismissPopupAction {
    dismiss: (() => void);
    reason: DismissReason;
}
declare type Literal_String_value_Callback_Void_action = { value: string, action: (() => void) }
declare type Literal_Boolean_isVisible = { isVisible: boolean }
declare type Callback_Literal_Boolean_isVisible_Void = ((event: { isVisible: boolean }) => void);
declare type Literal_ResourceColor_color = { color: ResourceColor }
declare type Callback_DismissPopupAction_Void = ((parameter: DismissPopupAction) => void);
declare interface PopupOptions {
    message: string;
    placementOnTop?: boolean;
    placement?: Placement;
    primaryButton?: { value: string, action: (() => void) };
    secondaryButton?: { value: string, action: (() => void) };
    onStateChange?: ((event: { isVisible: boolean }) => void);
    arrowOffset?: Length;
    showInSubWindow?: boolean;
    mask?: (boolean|{ color: ResourceColor });
    messageOptions?: PopupMessageOptions;
    targetSpace?: Length;
    enableArrow?: boolean;
    offset?: Position;
    popupColor?: (Color|string|Resource|number);
    autoCancel?: boolean;
    width?: Dimension;
    arrowPointPosition?: ArrowPointPosition;
    arrowWidth?: Dimension;
    arrowHeight?: Dimension;
    radius?: Dimension;
    shadow?: (ShadowOptions|ShadowStyle);
    backgroundBlurStyle?: BlurStyle;
    transition?: TransitionEffect;
    onWillDismiss?: (boolean|((parameter: DismissPopupAction) => void));
    enableHoverMode?: boolean;
    followTransformOfTarget?: boolean;
}
declare interface CustomPopupOptions {
    builder: CustomBuilder;
    placement?: Placement;
    maskColor?: (Color|string|Resource|number);
    popupColor?: (Color|string|Resource|number);
    enableArrow?: boolean;
    autoCancel?: boolean;
    onStateChange?: ((event: { isVisible: boolean }) => void);
    arrowOffset?: Length;
    showInSubWindow?: boolean;
    mask?: (boolean|{ color: ResourceColor });
    targetSpace?: Length;
    offset?: Position;
    width?: Dimension;
    arrowPointPosition?: ArrowPointPosition;
    arrowWidth?: Dimension;
    arrowHeight?: Dimension;
    radius?: Dimension;
    shadow?: (ShadowOptions|ShadowStyle);
    backgroundBlurStyle?: BlurStyle;
    focusable?: boolean;
    transition?: TransitionEffect;
    onWillDismiss?: (boolean|((parameter: DismissPopupAction) => void));
    enableHoverMode?: boolean;
    followTransformOfTarget?: boolean;
}
declare enum MenuPreviewMode {
    NONE = 0,
    IMAGE = 1,
}
declare type AnimationRange<T> = [ from: T, to: T ]
declare type AnimationRange_Number = [ number, number ]
declare interface ContextMenuAnimationOptions {
    scale?: [ number, number ];
    transition?: TransitionEffect;
    hoverScale?: [ number, number ];
}
declare interface ContextMenuOptions {
    offset?: Position;
    placement?: Placement;
    enableArrow?: boolean;
    arrowOffset?: Length;
    preview?: (MenuPreviewMode|CustomBuilder);
    borderRadius?: (Length|BorderRadiuses|LocalizedBorderRadiuses);
    onAppear?: (() => void);
    onDisappear?: (() => void);
    aboutToAppear?: (() => void);
    aboutToDisappear?: (() => void);
    layoutRegionMargin?: Margin;
    previewAnimationOptions?: ContextMenuAnimationOptions;
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    transition?: TransitionEffect;
    enableHoverMode?: boolean;
}
declare interface MenuOptions extends ContextMenuOptions {
    title?: ResourceStr;
    showInSubWindow?: boolean;
}
declare class ProgressMask {
    constructor(value: number, total: number, color: ResourceColor);
    updateProgress(value: number): void;
    updateColor(value: ResourceColor): void;
    enableBreathingAnimation(value: boolean): void;
}
declare class TouchTestInfo {
    windowX: number;
    windowY: number;
    parentX: number;
    parentY: number;
    x: number;
    y: number;
    rect: RectResult;
    id: string;
}
declare class TouchResult {
    strategy: TouchTestStrategy;
    id?: string;
}
declare interface PixelStretchEffectOptions {
    top?: Length;
    bottom?: Length;
    left?: Length;
    right?: Length;
}
declare interface ClickEffect {
    level: ClickEffectLevel;
    scale?: number;
}
declare interface FadingEdgeOptions {
    fadingEdgeLength?: LengthMetrics;
}
declare interface NestedScrollOptions {
    scrollForward: NestedScrollMode;
    scrollBackward: NestedScrollMode;
}
declare interface MenuElement {
    value: ResourceStr;
    icon?: ResourceStr;
    symbolIcon?: SymbolGlyphModifier;
    enabled?: boolean;
    action: (() => void);
}
declare interface AttributeModifier<T> {
    applyNormalAttribute?(instance: T): void;
    applyPressedAttribute?(instance: T): void;
    applyFocusedAttribute?(instance: T): void;
    applyDisabledAttribute?(instance: T): void;
    applySelectedAttribute?(instance: T): void;
}
declare interface ContentModifier<T> {
    stub: string;
}
declare interface CommonConfiguration<T> {
    enabled: boolean;
    contentModifier: ContentModifier<T>;
}
declare enum OutlineStyle {
    SOLID = 0,
    DASHED = 1,
    DOTTED = 2,
}
declare enum DragPreviewMode {
    AUTO = 1,
    DISABLE_SCALE = 2,
    ENABLE_DEFAULT_SHADOW = 3,
    ENABLE_DEFAULT_RADIUS = 4,
}
declare enum MenuPolicy {
    DEFAULT = 0,
    HIDE = 1,
    SHOW = 2,
}
declare interface ImageModifier {
    _ImageModifierStub: string;
}
declare interface SymbolGlyphModifier {
    _SymbolGlyphModifierStub: string;
}
declare interface DragPreviewOptions {
    mode?: (DragPreviewMode|DragPreviewMode[]);
    modifier?: ImageModifier;
    numberBadge?: (boolean|number);
}
declare interface DragInteractionOptions {
    isMultiSelectionEnabled?: boolean;
    defaultAnimationBeforeLifting?: boolean;
}
declare interface InvertOptions {
    low: number;
    high: number;
    threshold: number;
    thresholdRange: number;
}
declare type Optional<T> = T | undefined;
declare type Callback_Array_TouchTestInfo_TouchResult = ((value: TouchTestInfo[]) => TouchResult);
declare type Callback_ClickEvent_Void = ((event: ClickEvent) => void);
declare type Callback_Boolean_HoverEvent_Void = ((isHover: boolean, event: HoverEvent) => void);
declare type Callback_MouseEvent_Void = ((event: MouseEvent) => void);
declare type Callback_TouchEvent_Void = ((event: TouchEvent) => void);
declare type Callback_KeyEvent_Void = ((event: KeyEvent) => void);
declare type Callback_KeyEvent_Boolean = ((parameter: KeyEvent) => boolean);
declare type Callback_Area_Area_Void = ((oldValue: Area, newValue: Area) => void);
declare type Literal_Number_offset_span = { span: number, offset: number }
declare type Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs = { xs?: (number|{ span: number, offset: number }), sm?: (number|{ span: number, offset: number }), md?: (number|{ span: number, offset: number }), lg?: (number|{ span: number, offset: number }) }
declare type Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo = ((event: DragEvent, extraParams?: string) => (CustomBuilder|DragItemInfo));
declare type Callback_DragEvent_String_Void = ((event: DragEvent, extraParams?: string) => void);
declare type Callback_PreDragStatus_Void = ((parameter: PreDragStatus) => void);
declare type Tuple_ResourceColor_Number = [ ResourceColor, number ]
declare type Type_CommonMethod_linearGradient_value = { angle?: (number|string), direction?: GradientDirection, colors: [ ResourceColor, number ][], repeating?: boolean }
declare type Tuple_Length_Length = [ Length, Length ]
declare type Type_CommonMethod_sweepGradient_value = { center: [ Length, Length ], start?: (number|string), end?: (number|string), rotation?: (number|string), colors: [ ResourceColor, number ][], repeating?: boolean }
declare type Type_CommonMethod_radialGradient_value = { center: [ Length, Length ], radius: (number|string), colors: [ ResourceColor, number ][], repeating?: boolean }
declare type Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult = ((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult);
declare type Callback_TouchEvent_HitTestMode = ((parameter: TouchEvent) => HitTestMode);
declare type Literal_Alignment_align = { align?: Alignment }
declare class CommonMethod<T> {
    constructor();
    width(value: Length): T;
    height(value: Length): T;
    drawModifier(value: DrawModifier | undefined): T;
    responseRegion(value: (Rectangle[]|Rectangle)): T;
    mouseResponseRegion(value: (Rectangle[]|Rectangle)): T;
    size(value: SizeOptions): T;
    constraintSize(value: ConstraintSizeOptions): T;
    touchable(value: boolean): T;
    hitTestBehavior(value: HitTestMode): T;
    onChildTouchTest(value: ((value: TouchTestInfo[]) => TouchResult)): T;
    layoutWeight(value: (number|string)): T;
    chainWeight(value: ChainWeightOptions): T;
    padding(value: (Padding|Length|LocalizedPadding)): T;
    safeAreaPadding(value: (Padding|LengthMetrics|LocalizedPadding)): T;
    margin(value: (Margin|Length|LocalizedMargin)): T;
    backgroundColor(value: ResourceColor): T;
    pixelRound(value: PixelRoundPolicy): T;
    backgroundImageSize(value: (SizeOptions|ImageSize)): T;
    backgroundImagePosition(value: (Position|Alignment)): T;
    backgroundEffect(value: BackgroundEffectOptions): T;
    backgroundImageResizable(value: ResizableOptions): T;
    foregroundEffect(value: ForegroundEffectOptions): T;
    visualEffect(value: VisualEffect): T;
    backgroundFilter(value: Filter): T;
    foregroundFilter(value: Filter): T;
    compositingFilter(value: Filter): T;
    opacity(value: (number|Resource)): T;
    border(value: BorderOptions): T;
    borderStyle(value: (BorderStyle|EdgeStyles)): T;
    borderWidth(value: (Length|EdgeWidths|LocalizedEdgeWidths)): T;
    borderColor(value: (ResourceColor|EdgeColors|LocalizedEdgeColors)): T;
    borderRadius(value: (Length|BorderRadiuses|LocalizedBorderRadiuses)): T;
    borderImage(value: BorderImageOption): T;
    outline(value: OutlineOptions): T;
    outlineStyle(value: (OutlineStyle|EdgeOutlineStyles)): T;
    outlineWidth(value: (Dimension|EdgeOutlineWidths)): T;
    outlineColor(value: (ResourceColor|EdgeColors|LocalizedEdgeColors)): T;
    outlineRadius(value: (Dimension|OutlineRadiuses)): T;
    foregroundColor(value: (ResourceColor|ColoringStrategy)): T;
    onClick(value: ((event: ClickEvent) => void)): T;
    onHover(value: ((isHover: boolean, event: HoverEvent) => void)): T;
    onAccessibilityHover(value: AccessibilityCallback): T;
    hoverEffect(value: HoverEffect): T;
    onMouse(value: ((event: MouseEvent) => void)): T;
    onTouch(value: ((event: TouchEvent) => void)): T;
    onKeyEvent(value: ((event: KeyEvent) => void)): T;
    onKeyPreIme(value: ((parameter: KeyEvent) => boolean)): T;
    focusable(value: boolean): T;
    onFocus(value: (() => void)): T;
    onBlur(value: (() => void)): T;
    tabIndex(value: number): T;
    defaultFocus(value: boolean): T;
    groupDefaultFocus(value: boolean): T;
    focusOnTouch(value: boolean): T;
    focusBox(value: FocusBoxStyle): T;
    animation(value: AnimateParam): T;
    transition(value: (TransitionOptions|TransitionEffect)): T;
    motionBlur(value: MotionBlurOptions): T;
    brightness(value: number): T;
    contrast(value: number): T;
    grayscale(value: number): T;
    colorBlend(value: (Color|string|Resource)): T;
    saturate(value: number): T;
    sepia(value: number): T;
    invert(value: (number|InvertOptions)): T;
    hueRotate(value: (number|string)): T;
    useShadowBatching(value: boolean): T;
    useEffect(value: boolean): T;
    renderGroup(value: boolean): T;
    freeze(value: boolean): T;
    translate(value: TranslateOptions): T;
    scale(value: ScaleOptions): T;
    gridSpan(value: number): T;
    gridOffset(value: number): T;
    rotate(value: RotateOptions): T;
    transform(value: Object): T;
    onAppear(value: (() => void)): T;
    onDisAppear(value: (() => void)): T;
    onAttach(value: (() => void)): T;
    onDetach(value: (() => void)): T;
    onAreaChange(value: ((oldValue: Area, newValue: Area) => void)): T;
    visibility(value: Visibility): T;
    flexGrow(value: number): T;
    flexShrink(value: number): T;
    flexBasis(value: (number|string)): T;
    alignSelf(value: ItemAlign): T;
    displayPriority(value: number): T;
    zIndex(value: number): T;
    direction(value: Direction): T;
    align(value: Alignment): T;
    position(value: (Position|Edges|LocalizedEdges)): T;
    markAnchor(value: (Position|LocalizedPosition)): T;
    offset(value: (Position|Edges|LocalizedEdges)): T;
    enabled(value: boolean): T;
    useSizeType(value: { xs?: (number|{ span: number, offset: number }), sm?: (number|{ span: number, offset: number }), md?: (number|{ span: number, offset: number }), lg?: (number|{ span: number, offset: number }) }): T;
    alignRules(value: AlignRuleOption): T;
    alignRules(value: LocalizedAlignRuleOptions): T;
    aspectRatio(value: number): T;
    clickEffect(value: ClickEffect | undefined): T;
    onDragStart(value: ((event: DragEvent, extraParams?: string) => (CustomBuilder|DragItemInfo))): T;
    onDragEnter(value: ((event: DragEvent, extraParams?: string) => void)): T;
    onDragMove(value: ((event: DragEvent, extraParams?: string) => void)): T;
    onDragLeave(value: ((event: DragEvent, extraParams?: string) => void)): T;
    onDrop(value: ((event: DragEvent, extraParams?: string) => void)): T;
    onDragEnd(value: ((event: DragEvent, extraParams?: string) => void)): T;
    allowDrop(value: UniformDataType[] | undefined): T;
    draggable(value: boolean): T;
    dragPreview(value: (CustomBuilder|DragItemInfo|string)): T;
    onPreDrag(value: ((parameter: PreDragStatus) => void)): T;
    linearGradient(value: { angle?: (number|string), direction?: GradientDirection, colors: [ ResourceColor, number ][], repeating?: boolean }): T;
    sweepGradient(value: { center: [ Length, Length ], start?: (number|string), end?: (number|string), rotation?: (number|string), colors: [ ResourceColor, number ][], repeating?: boolean }): T;
    radialGradient(value: { center: [ Length, Length ], radius: (number|string), colors: [ ResourceColor, number ][], repeating?: boolean }): T;
    motionPath(value: MotionPathOptions): T;
    shadow(value: (ShadowOptions|ShadowStyle)): T;
    clip(value: boolean | undefined): T;
    clip(value: boolean | undefined): T;
    clipShape(value: (CircleShape|EllipseShape|PathShape|RectShape)): T;
    mask(value: ProgressMask | undefined): T;
    mask(value: ProgressMask | undefined): T;
    maskShape(value: (CircleShape|EllipseShape|PathShape|RectShape)): T;
    key(value: string): T;
    id(value: string): T;
    geometryTransition(value: string): T;
    stateStyles(value: StateStyles): T;
    restoreId(value: number): T;
    sphericalEffect(value: number): T;
    lightUpEffect(value: number): T;
    pixelStretchEffect(value: PixelStretchEffectOptions): T;
    accessibilityGroup(value: boolean): T;
    accessibilityText(value: string): T;
    accessibilityText(value: Resource): T;
    accessibilityTextHint(value: string): T;
    accessibilityDescription(value: string): T;
    accessibilityDescription(value: Resource): T;
    accessibilityLevel(value: string): T;
    accessibilityVirtualNode(value: CustomBuilder): T;
    accessibilityChecked(value: boolean): T;
    accessibilitySelected(value: boolean): T;
    obscured(value: ObscuredReasons[]): T;
    reuseId(value: string): T;
    renderFit(value: RenderFit): T;
    attributeModifier(value: AttributeModifier<T>): T;
    gestureModifier(value: GestureModifier): T;
    backgroundBrightness(value: BackgroundBrightnessOptions): T;
    onGestureJudgeBegin(value: ((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult)): T;
    onGestureRecognizerJudgeBegin(value: GestureRecognizerJudgeBeginCallback): T;
    shouldBuiltInRecognizerParallelWith(value: ShouldBuiltInRecognizerParallelWithCallback): T;
    monopolizeEvents(value: boolean): T;
    onTouchIntercept(value: ((parameter: TouchEvent) => HitTestMode)): T;
    onSizeChange(value: SizeChangeCallback): T;
    customProperty(name: string, value: Object | undefined): T;
    expandSafeArea(types?: SafeAreaType[], edges?: SafeAreaEdge[]): T;
    background(builder: CustomBuilder, options?: { align?: Alignment }): T;
    backgroundImage(src: (ResourceStr|PixelMap), repeat?: ImageRepeat): T;
    backgroundBlurStyle(value: BlurStyle, options?: BackgroundBlurStyleOptions): T;
    foregroundBlurStyle(value: BlurStyle, options?: ForegroundBlurStyleOptions): T;
    onClick(event: ((event: ClickEvent) => void), distanceThreshold: number): T;
    focusScopeId(id: string, isGroup?: boolean): T;
    focusScopeId(id: string, isGroup?: boolean, arrowStepOut?: boolean): T;
    focusScopePriority(scopeId: string, priority?: FocusPriority): T;
    transition(effect: TransitionEffect, onFinish: TransitionFinishCallback | undefined): T;
    gesture(gesture: GestureType, mask?: GestureMask): T;
    priorityGesture(gesture: GestureType, mask?: GestureMask): T;
    parallelGesture(gesture: GestureType, mask?: GestureMask): T;
    blur(value: number, options?: BlurOptions): T;
    linearGradientBlur(value: number, options: LinearGradientBlurOptions): T;
    systemBarEffect(): T;
    useEffect(useEffect: boolean, effectType: EffectType): T;
    backdropBlur(value: number, options?: BlurOptions): T;
    sharedTransition(id: string, options?: sharedTransitionOptions): T;
    chainMode(direction: Axis, style: ChainStyle): T;
    dragPreviewOptions(value: DragPreviewOptions, options?: DragInteractionOptions): T;
    overlay(value: (string|CustomBuilder|ComponentContent), options?: OverlayOptions): T;
    blendMode(value: BlendMode, type?: BlendApplyType): T;
    advancedBlendMode(effect: (BlendMode|Blender), type?: BlendApplyType): T;
    geometryTransition(id: string, options?: GeometryTransitionOptions): T;
    bindPopup(show: boolean, popup: (PopupOptions|CustomPopupOptions)): T;
    bindMenu(content: (MenuElement[]|CustomBuilder), options?: MenuOptions): T;
    bindMenu(isShow: boolean, content: (MenuElement[]|CustomBuilder), options?: MenuOptions): T;
    bindContextMenu(content: CustomBuilder, responseType: ResponseType, options?: ContextMenuOptions): T;
    bindContextMenu(isShown: boolean, content: CustomBuilder, options?: ContextMenuOptions): T;
    bindContentCover(isShow: boolean | undefined, builder: CustomBuilder, type?: ModalTransition): T;
    bindContentCover(isShow: boolean | undefined, builder: CustomBuilder, options?: ContentCoverOptions): T;
    bindSheet(isShow: boolean | undefined, builder: CustomBuilder, options?: SheetOptions): T;
    onVisibleAreaChange(ratios: number[], event: VisibleAreaChangeCallback): T;
    keyboardShortcut(value: (string|FunctionKey), keys: ModifierKey[], action?: (() => void)): T;
    accessibilityGroup(isGroup: boolean, accessibilityOptions: AccessibilityOptions): T;
    onGestureRecognizerJudgeBegin(callback_: GestureRecognizerJudgeBeginCallback, exposeInnerGesture: boolean): T;
}
declare class CommonAttribute extends CommonMethod<CommonAttribute> {
}
declare interface CommonInterface {
    (): CommonAttribute;
}
declare type CustomBuilder = (() => void);
declare interface OverlayOptions {
    align?: Alignment;
    offset?: OverlayOffset;
}
declare interface OverlayOffset {
    x?: number;
    y?: number;
}
declare type FractionStop = [ number, number ]
declare class CommonShapeMethod<T> extends CommonMethod<T> {
    constructor();
    stroke(value: ResourceColor): T;
    fill(value: ResourceColor): T;
    strokeDashOffset(value: (number|string)): T;
    strokeLineCap(value: LineCapStyle): T;
    strokeLineJoin(value: LineJoinStyle): T;
    strokeMiterLimit(value: (number|string)): T;
    strokeOpacity(value: (number|string|Resource)): T;
    fillOpacity(value: (number|string|Resource)): T;
    strokeWidth(value: Length): T;
    antiAlias(value: boolean): T;
    strokeDashArray(value: Length[]): T;
}
declare interface LinearGradient_common {
    angle?: (number|string);
    direction?: GradientDirection;
    colors: [ ResourceColor, number ][];
    repeating?: boolean;
}
declare interface PixelRoundPolicy {
    start?: PixelRoundCalcPolicy;
    top?: PixelRoundCalcPolicy;
    end?: PixelRoundCalcPolicy;
    bottom?: PixelRoundCalcPolicy;
}
declare interface LinearGradientBlurOptions {
    fractionStops: FractionStop[];
    direction: GradientDirection;
}
declare interface MotionBlurAnchor {
    x: number;
    y: number;
}
declare interface MotionBlurOptions {
    radius: number;
    anchor: MotionBlurAnchor;
}
declare interface LayoutBorderInfo {
    borderWidth: EdgeWidths;
    margin: Margin;
    padding: Padding;
}
declare interface LayoutInfo {
    position: Position;
    constraint: ConstraintSizeOptions;
}
declare interface LayoutChild {
    stub: string;
}
declare interface GeometryInfo extends SizeResult {
    borderWidth: EdgeWidth;
    margin: Margin;
    padding: Padding;
}
declare interface Layoutable {
    stub: string;
}
declare interface Measurable {
    measure(constraint: ConstraintSizeOptions): MeasureResult;
    getMargin(): DirectionalEdgesT;
    getPadding(): DirectionalEdgesT;
    getBorderWidth(): DirectionalEdgesT;
}
declare interface SizeResult {
    width: number;
    height: number;
}
declare interface MeasureResult extends SizeResult {
}
declare interface NavDestinationInfo {
    _NavDestinationInfoStub: string;
}
declare interface NavigationInfo {
    _NavigationInfoStub: string;
}
declare interface RouterPageInfo {
    _RouterPageInfoStub: string;
}
declare interface UIContext {
    _UIContextStub: string;
}
declare interface DrawContext {
    _DrawContextStub: string;
}
declare interface VisualEffect {
    _VisualEffectStub: string;
}
declare interface Filter {
    _FilterStub: string;
}
declare interface Blender {
    _BlenderStub: string;
}
declare interface ComponentContent {
    _ComponentContentStub: string;
}
declare interface Theme {
    _ThemeStub: string;
}
declare type Literal_Empty = {  }
declare class CustomComponent extends CommonAttribute {
    build(): void;
    aboutToAppear?(): void;
    aboutToDisappear?(): void;
    aboutToReuse?(params: {  }): void;
    aboutToRecycle?(): void;
    onWillApplyTheme?(theme: Theme): void;
    onLayout?(children: LayoutChild[], constraint: ConstraintSizeOptions): void;
    onPlaceChildren?(selfLayoutInfo: GeometryInfo, children: Layoutable[], constraint: ConstraintSizeOptions): void;
    onMeasure?(children: LayoutChild[], constraint: ConstraintSizeOptions): void;
    onMeasureSize?(selfLayoutInfo: GeometryInfo, children: Measurable[], constraint: ConstraintSizeOptions): SizeResult;
    onPageShow?(): void;
    onPageHide?(): void;
    onFormRecycle?(): string;
    onFormRecover?(statusData: string): void;
    onBackPress?(): boolean;
    pageTransition?(): void;
    getUIContext(): UIContext;
    getUniqueId(): number;
    queryNavDestinationInfo(): NavDestinationInfo | undefined;
    queryNavigationInfo(): NavigationInfo | undefined;
    queryRouterPageInfo(): RouterPageInfo | undefined;
    onDidBuild?(): void;
}
declare class View {
    create(value: any): any;
}
declare interface RectResult {
    x: number;
    y: number;
    width: number;
    height: number;
}
declare interface CaretOffset {
    index: number;
    x: number;
    y: number;
}
declare class TextContentControllerBase {
    getCaretOffset(): CaretOffset;
    getTextContentRect(): RectResult;
    getTextContentLineCount(): number;
}
declare enum ContentClipMode {
    CONTENT_ONLY = 0,
    BOUNDARY = 1,
    SAFE_AREA = 2,
}
declare class ScrollableCommonMethod<T> extends CommonMethod<T> {
    scrollBar(value: BarState): T;
    scrollBarColor(value: (Color|number|string)): T;
    scrollBarWidth(value: (number|string)): T;
    nestedScroll(value: NestedScrollOptions): T;
    enableScrollInteraction(value: boolean): T;
    friction(value: (number|Resource)): T;
    onScroll(value: ((first: number, last: number) => void)): T;
    onReachStart(value: (() => void)): T;
    onReachEnd(value: (() => void)): T;
    onScrollStart(value: (() => void)): T;
    onScrollStop(value: (() => void)): T;
    flingSpeedLimit(value: number): T;
    clipContent(value: (ContentClipMode|RectShape)): T;
    edgeEffect(edgeEffect: EdgeEffect, options?: EdgeEffectOptions): T;
    fadingEdge(enabled: boolean | undefined, options?: FadingEdgeOptions): T;
}
declare class ScrollResult {
    offsetRemain: number;
}
declare type OnWillScrollCallback = (scrollOffset: number, scrollState: ScrollState, scrollSource: ScrollSource) => ScrollResult;
declare type OnScrollCallback = ((scrollOffset: number, scrollState: ScrollState) => void);
declare type OnMoveHandler = ((from: number, to: number) => void);
declare class DynamicNode<T> {
    onMove(handler: OnMoveHandler | undefined): T;
}
declare interface EdgeEffectOptions {
    alwaysEnabled: boolean;
}
declare class ChildrenMainSize {
    constructor(childDefaultSize: number);
    childDefaultSize: number;
    splice(start: number, deleteCount?: number, childrenSize?: number[]): void;
    update(index: number, childSize: number): void;
}
declare interface BackgroundBrightnessOptions {
    rate: number;
    lightUpDegree: number;
}
declare interface PointLightStyle {
    lightSource?: LightSource;
    illuminated?: IlluminatedType;
    bloom?: number;
}
declare interface LightSource {
    positionX: Dimension;
    positionY: Dimension;
    positionZ: Dimension;
    intensity: number;
    color?: ResourceColor;
}
declare interface KeyframeAnimateParam {
    delay?: number;
    iterations?: number;
    onFinish?: (() => void);
}
declare interface KeyframeState {
    duration: number;
    curve?: (Curve|string|ICurve);
    event: (() => void);
}
declare interface Callback<T,V = void> {
    (data: T): V;
}
declare type HoverCallback = ((isHover: boolean, event: HoverEvent) => void);
declare type AccessibilityCallback = ((isHover: boolean, event: AccessibilityHoverEvent) => void);
declare interface VisibleAreaEventOptions {
    ratios: number[];
    expectedUpdateInterval?: number;
}
declare type VisibleAreaChangeCallback = ((isExpanding: boolean, currentRatio: number) => void);
declare interface UICommonEvent {
    setOnClick(callback_: ((event: ClickEvent) => void) | undefined): void;
    setOnTouch(callback_: ((event: TouchEvent) => void) | undefined): void;
    setOnAppear(callback_: (() => void) | undefined): void;
    setOnDisappear(callback_: (() => void) | undefined): void;
    setOnKeyEvent(callback_: ((event: KeyEvent) => void) | undefined): void;
    setOnFocus(callback_: (() => void) | undefined): void;
    setOnBlur(callback_: (() => void) | undefined): void;
    setOnHover(callback_: HoverCallback | undefined): void;
    setOnMouse(callback_: ((event: MouseEvent) => void) | undefined): void;
    setOnSizeChange(callback_: SizeChangeCallback | undefined): void;
    setOnVisibleAreaApproximateChange(options: VisibleAreaEventOptions, event: VisibleAreaChangeCallback | undefined): void;
}
declare interface UIGestureEvent {
    addGesture<T>(gesture: GestureHandler<T>, priority?: GesturePriority, mask?: GestureMask): void;
    addParallelGesture<T>(gesture: GestureHandler<T>, mask?: GestureMask): void;
    removeGestureByTag(tag: string): void;
    clearGestures(): void;
}
declare interface GestureModifier {
    applyGesture(event: UIGestureEvent): void;
}
declare interface SelectionOptions {
    menuPolicy?: MenuPolicy;
}
declare enum KeyboardAvoidMode {
    DEFAULT = 0,
    NONE = 1,
}
declare enum HoverModeAreaType {
    TOP_SCREEN = 0,
    BOTTOM_SCREEN = 1,
}
declare class AppStorage {
}
declare interface AbstractProperty<T> {
    get(): T;
    set(newValue: T): void;
    info(): string;
}
declare class SubscribedAbstractProperty<T> {
    constructor(subscribeMe?: IPropertySubscriber, info?: string);
    protected subscribers_: number[];
    id(): number;
    info(): string;
    get(): T;
    set(newValue: T): void;
    createTwoWaySync(subscribeMe?: IPropertySubscriber, info?: string): SyncedPropertyTwoWay<T>;
    createOneWaySync(subscribeMe?: IPropertySubscriber, info?: string): SyncedPropertyOneWay<T>;
    unlinkSuscriber(subscriberId: number): void;
    protected notifyHasChanged(newValue: T): void;
    protected notifyPropertyRead(): void;
    numberOfSubscrbers(): number;
    aboutToBeDeleted(): void;
}
declare interface IPropertySubscriber {
    id(): number;
    aboutToBeDeleted(owningView?: IPropertySubscriber): void;
}
declare class SyncedPropertyTwoWay<T> extends SubscribedAbstractProperty<T> implements ISinglePropertyChangeSubscriber<T> {
    constructor(source: SubscribedAbstractProperty<T>, subscribeMe?: IPropertySubscriber, info?: string);
    aboutToBeDeleted(unsubscribeMe?: IPropertySubscriber): void;
    hasChanged(newValue: T): void;
    get(): T;
    set(newValue: T): void;
}
declare class SyncedPropertyOneWay<T> extends SubscribedAbstractProperty<T> implements ISinglePropertyChangeSubscriber<T> {
    constructor(source: SubscribedAbstractProperty<T>, subscribeMe?: IPropertySubscriber, info?: string);
    aboutToBeDeleted(unsubscribeMe?: IPropertySubscriber): void;
    hasChanged(newValue: T): void;
    get(): T;
    set(newValue: T): void;
}
declare interface ISinglePropertyChangeSubscriber<T> extends IPropertySubscriber {
    hasChanged(newValue: T): void;
}
declare class SubscribaleAbstract {
    constructor();
    protected notifyPropertyHasChanged(propName: string, newValue: any): void;
    addOwningProperty(subscriber: IPropertySubscriber): void;
    removeOwningProperty(property: IPropertySubscriber): void;
    removeOwningPropertyById(subscriberId: number): void;
}
declare interface EnvPropsOptions {
    key: string;
    defaultValue: (number|string|boolean);
}
declare type Literal_String_key_Any_defaultValue = { key: string, defaultValue: any }
declare class Environment {
    constructor();
}
declare interface PersistPropsOptions {
    key: string;
    defaultValue: (number|string|boolean|Object);
}
declare class PersistentStorage {
    constructor(appStorage: AppStorage, storage: Storage);
}
declare class LocalStorage {
    constructor(initializingProperties?: Object);
    ref<T>(propName: string): AbstractProperty<T> | undefined;
    setAndRef<T>(propName: string, defaultValue: T): AbstractProperty<T>;
    has(propName: string): boolean;
    keys(): string[];
    size(): number;
    get<T>(propName: string): T | undefined;
    set<T>(propName: string, newValue: T): boolean;
    setOrCreate<T>(propName: string, newValue: T): boolean;
    link<T>(propName: string): SubscribedAbstractProperty<T>;
    setAndLink<T>(propName: string, defaultValue: T): SubscribedAbstractProperty<T>;
    prop<S>(propName: string): SubscribedAbstractProperty<S>;
    setAndProp<S>(propName: string, defaultValue: S): SubscribedAbstractProperty<S>;
    delete(propName: string): boolean;
    clear(): boolean;
}
declare interface Scene {
    _SceneStub: string;
}
declare enum ModelType {
    TEXTURE = 0,
    SURFACE = 1,
}
declare interface SceneOptions {
    scene?: (ResourceStr|Scene);
    modelType?: ModelType;
}
declare interface Component3DInterface {
    (sceneOptions?: SceneOptions): Component3DAttribute;
}
declare class Component3DAttribute extends CommonMethod<Component3DAttribute> {
    environment(value: ResourceStr): Component3DAttribute;
    shader(value: ResourceStr): Component3DAttribute;
    shaderImageTexture(value: ResourceStr): Component3DAttribute;
    shaderInputBuffer(value: number[]): Component3DAttribute;
    renderWidth(value: Dimension): Component3DAttribute;
    renderHeight(value: Dimension): Component3DAttribute;
    customRender(uri: ResourceStr, selfRenderUpdate: boolean): Component3DAttribute;
}
declare interface ContainerSpanInterface {
    (): ContainerSpanAttribute;
}
declare class ContainerSpanAttribute {
    textBackgroundStyle(value: TextBackgroundStyle): ContainerSpanAttribute;
    attributeModifier(value: AttributeModifier<ContainerSpanAttribute>): ContainerSpanAttribute;
}
declare interface Content {
    _ContentStub: string;
}
declare class ContentSlotAttribute {
}
declare interface ContentSlotInterface {
    (content: Content): ContentSlotAttribute;
}
declare class ContextMenu {
}
declare interface CounterInterface {
    (): CounterAttribute;
}
declare class CounterAttribute extends CommonMethod<CounterAttribute> {
    onInc(value: VoidCallback): CounterAttribute;
    onDec(value: VoidCallback): CounterAttribute;
    enableDec(value: boolean): CounterAttribute;
    enableInc(value: boolean): CounterAttribute;
}
declare interface CustomDialogControllerOptions {
    builder: any;
    cancel?: (() => void);
    autoCancel?: boolean;
    alignment?: DialogAlignment;
    offset?: Offset;
    customStyle?: boolean;
    gridCount?: number;
    maskColor?: ResourceColor;
    maskRect?: Rectangle;
    openAnimation?: AnimateParam;
    closeAnimation?: AnimateParam;
    showInSubWindow?: boolean;
    backgroundColor?: ResourceColor;
    cornerRadius?: (Dimension|BorderRadiuses);
    isModal?: boolean;
    onWillDismiss?: ((parameter: DismissDialogAction) => void);
    width?: Dimension;
    height?: Dimension;
    borderWidth?: (Dimension|EdgeWidths);
    borderColor?: (ResourceColor|EdgeColors);
    borderStyle?: (BorderStyle|EdgeStyles);
    shadow?: (ShadowOptions|ShadowStyle);
    backgroundBlurStyle?: BlurStyle;
    keyboardAvoidMode?: KeyboardAvoidMode;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
}
declare class CustomDialogController {
    constructor(value: CustomDialogControllerOptions);
    open(): void;
    close(): void;
}
declare enum DataPanelType {
    LINE = 0,
    Line = 0,
    CIRCLE = 1,
    Circle = 1,
}
declare interface ColorStop {
    color: ResourceColor;
    offset: Length;
}
declare class LinearGradient {
    constructor(colorStops: ColorStop[]);
}
declare interface DataPanelShadowOptions extends MultiShadowOptions {
    colors?: (ResourceColor|LinearGradient)[];
}
declare interface DataPanelOptions {
    values: number[];
    max?: number;
    type?: DataPanelType;
}
declare interface DataPanelInterface {
    (options: DataPanelOptions): DataPanelAttribute;
}
declare interface DataPanelConfiguration extends CommonConfiguration<DataPanelConfiguration> {
    values: number[];
    maxValue: number;
}
declare class DataPanelAttribute extends CommonMethod<DataPanelAttribute> {
    closeEffect(value: boolean): DataPanelAttribute;
    valueColors(value: (ResourceColor|LinearGradient)[]): DataPanelAttribute;
    trackBackgroundColor(value: ResourceColor): DataPanelAttribute;
    strokeWidth(value: Length): DataPanelAttribute;
    trackShadow(value: DataPanelShadowOptions): DataPanelAttribute;
    contentModifier(value: ContentModifier<DataPanelConfiguration>): DataPanelAttribute;
}
declare interface DatePickerResult {
    year?: number;
    month?: number;
    day?: number;
}
declare interface DatePickerOptions {
    start?: Date;
    end?: Date;
    selected?: Date;
}
declare interface DatePickerInterface {
    (options?: DatePickerOptions): DatePickerAttribute;
}
declare type Callback_DatePickerResult_Void = ((value: DatePickerResult) => void);
declare class DatePickerAttribute extends CommonMethod<DatePickerAttribute> {
    lunar(value: boolean): DatePickerAttribute;
    disappearTextStyle(value: PickerTextStyle): DatePickerAttribute;
    textStyle(value: PickerTextStyle): DatePickerAttribute;
    selectedTextStyle(value: PickerTextStyle): DatePickerAttribute;
    onChange(value: ((value: DatePickerResult) => void)): DatePickerAttribute;
    onDateChange(value: ((parameter: Date) => void)): DatePickerAttribute;
    _onChangeEvent_selected(callback_: ((parameter: Date) => void)): void;
}
declare interface LunarSwitchStyle {
    selectedColor?: ResourceColor;
    unselectedColor?: ResourceColor;
    strokeColor?: ResourceColor;
}
declare interface DatePickerDialogOptions extends DatePickerOptions {
    lunar?: boolean;
    lunarSwitch?: boolean;
    lunarSwitchStyle?: LunarSwitchStyle;
    showTime?: boolean;
    useMilitaryTime?: boolean;
    disappearTextStyle?: PickerTextStyle;
    textStyle?: PickerTextStyle;
    acceptButtonStyle?: PickerDialogButtonStyle;
    cancelButtonStyle?: PickerDialogButtonStyle;
    selectedTextStyle?: PickerTextStyle;
    maskRect?: Rectangle;
    alignment?: DialogAlignment;
    offset?: Offset;
    onAccept?: ((value: DatePickerResult) => void);
    onCancel?: VoidCallback;
    onChange?: ((value: DatePickerResult) => void);
    onDateAccept?: ((parameter: Date) => void);
    onDateChange?: ((parameter: Date) => void);
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    onDidAppear?: VoidCallback;
    onDidDisappear?: VoidCallback;
    onWillAppear?: VoidCallback;
    onWillDisappear?: VoidCallback;
    shadow?: (ShadowOptions|ShadowStyle);
    dateTimeOptions?: DateTimeOptions;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
}
declare class DatePickerDialog {
}
declare interface DividerInterface {
    (): DividerAttribute;
}
declare class DividerAttribute extends CommonMethod<DividerAttribute> {
    vertical(value: boolean): DividerAttribute;
    color(value: ResourceColor): DividerAttribute;
    strokeWidth(value: (number|string)): DividerAttribute;
    lineCap(value: LineCapStyle): DividerAttribute;
}
declare interface EffectComponentInterface {
    (): EffectComponentAttribute;
}
declare class EffectComponentAttribute extends CommonMethod<EffectComponentAttribute> {
}
declare interface EllipseOptions {
    width?: (string|number);
    height?: (string|number);
}
declare interface EllipseInterface {
    new(options?: EllipseOptions): EllipseAttribute;
    (options?: EllipseOptions): EllipseAttribute;
}
declare class EllipseAttribute extends CommonShapeMethod<EllipseAttribute> {
}
declare interface EmbeddedComponentInterface {
    (loader: Want, type: EmbeddedType): EmbeddedComponentAttribute;
}
declare interface TerminationInfo {
    code: number;
    want?: Want;
}
declare type Callback_TerminationInfo_Void = ((parameter: TerminationInfo) => void);
declare class EmbeddedComponentAttribute extends CommonMethod<EmbeddedComponentAttribute> {
    onTerminated(value: ((parameter: TerminationInfo) => void)): EmbeddedComponentAttribute;
    onError(value: ErrorCallback): EmbeddedComponentAttribute;
}
declare enum CheckBoxShape {
    CIRCLE = 0,
    ROUNDED_SQUARE = 1,
}
declare enum Color {
    WHITE = 0,
    White = 0,
    BLACK = 1,
    Black = 1,
    BLUE = 2,
    Blue = 2,
    BROWN = 3,
    Brown = 3,
    GRAY = 4,
    Gray = 4,
    GREEN = 5,
    Green = 5,
    GREY = 6,
    Grey = 6,
    ORANGE = 7,
    Orange = 7,
    PINK = 8,
    Pink = 8,
    RED = 9,
    Red = 9,
    YELLOW = 10,
    Yellow = 10,
    TRANSPARENT = 11,
    Transparent = 11,
}
declare enum ColoringStrategy {
    INVERT = "invert",
    AVERAGE = "average",
    PRIMARY = "primary",
}
declare enum ImageFit {
    CONTAIN = 0,
    Contain = 0,
    COVER = 1,
    Cover = 1,
    AUTO = 2,
    Auto = 2,
    FILL = 3,
    Fill = 3,
    SCALE_DOWN = 4,
    ScaleDown = 4,
    NONE = 5,
    None = 5,
    TOP_START = 7,
    TOP = 8,
    TOP_END = 9,
    START = 10,
    CENTER = 11,
    END = 12,
    BOTTOM_START = 13,
    BOTTOM = 14,
    BOTTOM_END = 15,
}
declare enum BorderStyle {
    DOTTED = 0,
    Dotted = 0,
    DASHED = 1,
    Dashed = 1,
    SOLID = 2,
    Solid = 2,
}
declare enum LineJoinStyle {
    MITER = 0,
    Miter = 0,
    ROUND = 1,
    Round = 1,
    BEVEL = 2,
    Bevel = 2,
}
declare enum TouchType {
    DOWN = 0,
    Down = 0,
    UP = 1,
    Up = 1,
    MOVE = 2,
    Move = 2,
    CANCEL = 3,
    Cancel = 3,
}
declare enum MouseButton {
    LEFT = 0,
    Left = 0,
    RIGHT = 1,
    Right = 1,
    MIDDLE = 2,
    Middle = 2,
    BACK = 3,
    Back = 3,
    FORWARD = 4,
    Forward = 4,
    NONE = 5,
    None = 5,
}
declare enum MouseAction {
    PRESS = 0,
    Press = 0,
    RELEASE = 1,
    Release = 1,
    MOVE = 2,
    Move = 2,
    HOVER = 3,
    Hover = 3,
}
declare enum AnimationStatus {
    INITIAL = 0,
    Initial = 0,
    RUNNING = 1,
    Running = 1,
    PAUSED = 2,
    Paused = 2,
    STOPPED = 3,
    Stopped = 3,
}
declare enum Curve {
    LINEAR = 0,
    Linear = 0,
    EASE = 1,
    Ease = 1,
    EASE_IN = 2,
    EaseIn = 2,
    EASE_OUT = 3,
    EaseOut = 3,
    EASE_IN_OUT = 4,
    EaseInOut = 4,
    FAST_OUT_SLOW_IN = 5,
    FastOutSlowIn = 5,
    LINEAR_OUT_SLOW_IN = 6,
    LinearOutSlowIn = 6,
    FAST_OUT_LINEAR_IN = 7,
    FastOutLinearIn = 7,
    EXTREME_DECELERATION = 8,
    ExtremeDeceleration = 8,
    SHARP = 9,
    Sharp = 9,
    RHYTHM = 10,
    Rhythm = 10,
    SMOOTH = 11,
    Smooth = 11,
    FRICTION = 12,
    Friction = 12,
}
declare enum FillMode {
    NONE = 0,
    None = 0,
    FORWARDS = 1,
    Forwards = 1,
    BACKWARDS = 2,
    Backwards = 2,
    BOTH = 3,
    Both = 3,
}
declare enum PlayMode {
    NORMAL = 0,
    Normal = 0,
    REVERSE = 1,
    Reverse = 1,
    ALTERNATE = 2,
    Alternate = 2,
    ALTERNATE_REVERSE = 3,
    AlternateReverse = 3,
}
declare enum KeyType {
    DOWN = 0,
    Down = 0,
    UP = 1,
    Up = 1,
}
declare enum KeySource {
    UNKNOWN = 0,
    Unknown = 0,
    KEYBOARD = 1,
    Keyboard = 1,
}
declare enum Edge {
    TOP = 0,
    Top = 0,
    CENTER = 1,
    Center = 1,
    BOTTOM = 2,
    Bottom = 2,
    BASELINE = 3,
    Baseline = 3,
    START = 4,
    Start = 4,
    MIDDLE = 5,
    Middle = 5,
    END = 6,
    End = 6,
}
declare enum Week {
    MON = 0,
    Mon = 0,
    TUE = 1,
    Tue = 1,
    WED = 2,
    Wed = 2,
    THUR = 3,
    Thur = 3,
    FRI = 4,
    Fri = 4,
    SAT = 5,
    Sat = 5,
    SUN = 6,
    Sun = 6,
}
declare enum Direction {
    LTR = 0,
    Ltr = 0,
    RTL = 1,
    Rtl = 1,
    AUTO = 2,
    Auto = 2,
}
declare enum BarState {
    OFF = 0,
    Off = 0,
    AUTO = 1,
    Auto = 1,
    ON = 2,
    On = 2,
}
declare enum EdgeEffect {
    SPRING = 0,
    Spring = 0,
    FADE = 1,
    Fade = 1,
    NONE = 2,
    None = 2,
}
declare enum Alignment {
    TOP_START = 0,
    TopStart = 0,
    TOP = 1,
    Top = 1,
    TOP_END = 2,
    TopEnd = 2,
    START = 3,
    Start = 3,
    CENTER = 4,
    Center = 4,
    END = 5,
    End = 5,
    BOTTOM_START = 6,
    BottomStart = 6,
    BOTTOM = 7,
    Bottom = 7,
    BOTTOM_END = 8,
    BottomEnd = 8,
}
declare enum TransitionType {
    ALL = 0,
    All = 0,
    INSERT = 1,
    Insert = 1,
    DELETE = 2,
    Delete = 2,
}
declare enum RelateType {
    FILL = 0,
    FIT = 1,
}
declare enum Visibility {
    VISIBLE = 0,
    Visible = 0,
    HIDDEN = 1,
    Hidden = 1,
    NONE = 2,
    None = 2,
}
declare enum LineCapStyle {
    BUTT = 0,
    Butt = 0,
    ROUND = 1,
    Round = 1,
    SQUARE = 2,
    Square = 2,
}
declare enum Axis {
    VERTICAL = 0,
    Vertical = 0,
    HORIZONTAL = 1,
    Horizontal = 1,
}
declare enum HorizontalAlign {
    START = 0,
    Start = 0,
    CENTER = 1,
    Center = 1,
    END = 2,
    End = 2,
}
declare enum FlexAlign {
    START = 0,
    Start = 0,
    CENTER = 1,
    Center = 1,
    END = 2,
    End = 2,
    SPACE_BETWEEN = 3,
    SpaceBetween = 3,
    SPACE_AROUND = 4,
    SpaceAround = 4,
    SPACE_EVENLY = 5,
    SpaceEvenly = 5,
}
declare enum ItemAlign {
    AUTO = 0,
    Auto = 0,
    START = 1,
    Start = 1,
    CENTER = 2,
    Center = 2,
    END = 3,
    End = 3,
    BASELINE = 4,
    Baseline = 4,
    STRETCH = 5,
    Stretch = 5,
}
declare enum FlexDirection {
    ROW = 0,
    Row = 0,
    COLUMN = 1,
    Column = 1,
    ROW_REVERSE = 2,
    RowReverse = 2,
    COLUMN_REVERSE = 3,
    ColumnReverse = 3,
}
declare enum PixelRoundCalcPolicy {
    NO_FORCE_ROUND = 0,
    FORCE_CEIL = 1,
    FORCE_FLOOR = 2,
}
declare enum FlexWrap {
    NO_WRAP = 0,
    NoWrap = 0,
    WRAP = 1,
    Wrap = 1,
    WRAP_REVERSE = 2,
    WrapReverse = 2,
}
declare enum VerticalAlign {
    TOP = 0,
    Top = 0,
    CENTER = 1,
    Center = 1,
    BOTTOM = 2,
    Bottom = 2,
}
declare enum ImageRepeat {
    NO_REPEAT = 0,
    NoRepeat = 0,
    X = 1,
    Y = 2,
    XY = 3,
}
declare enum ImageSize {
    AUTO = 0,
    Auto = 0,
    COVER = 1,
    Cover = 1,
    CONTAIN = 2,
    Contain = 2,
    FILL = 3,
}
declare enum GradientDirection {
    LEFT = 0,
    Left = 0,
    TOP = 1,
    Top = 1,
    RIGHT = 2,
    Right = 2,
    BOTTOM = 3,
    Bottom = 3,
    LEFT_TOP = 4,
    LeftTop = 4,
    LEFT_BOTTOM = 5,
    LeftBottom = 5,
    RIGHT_TOP = 6,
    RightTop = 6,
    RIGHT_BOTTOM = 7,
    RightBottom = 7,
    NONE = 8,
    None = 8,
}
declare enum SharedTransitionEffectType {
    STATIC = 0,
    Static = 0,
    EXCHANGE = 1,
    Exchange = 1,
}
declare enum FontStyle {
    NORMAL = 0,
    Normal = 0,
    ITALIC = 1,
    Italic = 1,
}
declare enum FontWeight {
    LIGHTER = 0,
    Lighter = 0,
    NORMAL = 1,
    Normal = 1,
    REGULAR = 2,
    Regular = 2,
    MEDIUM = 3,
    Medium = 3,
    BOLD = 4,
    Bold = 4,
    BOLDER = 5,
    Bolder = 5,
}
declare enum TextAlign {
    CENTER = 0,
    Center = 0,
    START = 1,
    Start = 1,
    END = 2,
    End = 2,
    JUSTIFY = 3,
}
declare enum TextOverflow {
    NONE = 0,
    None = 0,
    CLIP = 1,
    Clip = 1,
    ELLIPSIS = 2,
    Ellipsis = 2,
    MARQUEE = 3,
}
declare enum TextDecorationType {
    NONE = 0,
    None = 0,
    UNDERLINE = 1,
    Underline = 1,
    OVERLINE = 2,
    Overline = 2,
    LINE_THROUGH = 3,
    LineThrough = 3,
}
declare enum TextCase {
    NORMAL = 0,
    Normal = 0,
    LOWER_CASE = 1,
    LowerCase = 1,
    UPPER_CASE = 2,
    UpperCase = 2,
}
declare enum TextHeightAdaptivePolicy {
    MAX_LINES_FIRST = 0,
    MIN_FONT_SIZE_FIRST = 1,
    LAYOUT_CONSTRAINT_FIRST = 2,
}
declare enum ResponseType {
    RIGHT_CLICK = 0,
    RightClick = 0,
    LONG_PRESS = 1,
    LongPress = 1,
}
declare enum HoverEffect {
    AUTO = 0,
    Auto = 0,
    SCALE = 1,
    Scale = 1,
    HIGHLIGHT = 2,
    Highlight = 2,
    NONE = 3,
    None = 3,
}
declare enum Placement {
    LEFT = 0,
    Left = 0,
    RIGHT = 1,
    Right = 1,
    TOP = 2,
    Top = 2,
    BOTTOM = 3,
    Bottom = 3,
    TOP_LEFT = 4,
    TopLeft = 4,
    TOP_RIGHT = 5,
    TopRight = 5,
    BOTTOM_LEFT = 6,
    BottomLeft = 6,
    BOTTOM_RIGHT = 7,
    BottomRight = 7,
    LEFT_TOP = 8,
    LeftTop = 8,
    LEFT_BOTTOM = 9,
    LeftBottom = 9,
    RIGHT_TOP = 10,
    RightTop = 10,
    RIGHT_BOTTOM = 11,
    RightBottom = 11,
}
declare enum ArrowPointPosition {
    START = "Start",
    CENTER = "Center",
    END = "End",
}
declare enum CopyOptions {
    NONE = 0,
    None = 0,
    IN_APP = 1,
    InApp = 1,
    LOCAL_DEVICE = 2,
    LocalDevice = 2,
    CROSS_DEVICE = 3,
}
declare enum HitTestMode {
    DEFAULT = 0,
    Default = 0,
    BLOCK = 1,
    Block = 1,
    TRANSPARENT = 2,
    Transparent = 2,
    NONE = 3,
    None = 3,
}
declare enum TitleHeight {
    MAIN_ONLY = 0,
    MainOnly = 0,
    MAIN_WITH_SUB = 1,
    MainWithSub = 1,
}
declare enum ModifierKey {
    CTRL = 0,
    SHIFT = 1,
    ALT = 2,
}
declare enum FunctionKey {
    ESC = 0,
    F1 = 1,
    F2 = 2,
    F3 = 3,
    F4 = 4,
    F5 = 5,
    F6 = 6,
    F7 = 7,
    F8 = 8,
    F9 = 9,
    F10 = 10,
    F11 = 11,
    F12 = 12,
    TAB = 13,
    DPAD_UP = 14,
    DPAD_DOWN = 15,
    DPAD_LEFT = 16,
    DPAD_RIGHT = 17,
}
declare enum ImageSpanAlignment {
    BASELINE = 0,
    BOTTOM = 1,
    CENTER = 2,
    TOP = 3,
}
declare enum ObscuredReasons {
    PLACEHOLDER = 0,
}
declare enum TextContentStyle {
    DEFAULT = 0,
    INLINE = 1,
}
declare enum ClickEffectLevel {
    LIGHT = 0,
    MIDDLE = 1,
    HEAVY = 2,
}
declare enum XComponentType {
    SURFACE = 0,
    COMPONENT = 1,
    TEXTURE = 2,
    NODE = 3,
}
declare enum NestedScrollMode {
    SELF_ONLY = 0,
    SELF_FIRST = 1,
    PARENT_FIRST = 2,
    PARALLEL = 3,
}
declare enum ScrollSource {
    DRAG = 0,
    FLING = 1,
    EDGE_EFFECT = 2,
    OTHER_USER_INPUT = 3,
    SCROLL_BAR = 4,
    SCROLL_BAR_FLING = 5,
    SCROLLER = 6,
    SCROLLER_ANIMATION = 7,
}
declare enum RenderFit {
    CENTER = 0,
    TOP = 1,
    BOTTOM = 2,
    LEFT = 3,
    RIGHT = 4,
    TOP_LEFT = 5,
    TOP_RIGHT = 6,
    BOTTOM_LEFT = 7,
    BOTTOM_RIGHT = 8,
    RESIZE_FILL = 9,
    RESIZE_CONTAIN = 10,
    RESIZE_CONTAIN_TOP_LEFT = 11,
    RESIZE_CONTAIN_BOTTOM_RIGHT = 12,
    RESIZE_COVER = 13,
    RESIZE_COVER_TOP_LEFT = 14,
    RESIZE_COVER_BOTTOM_RIGHT = 15,
}
declare enum DialogButtonStyle {
    DEFAULT = 0,
    HIGHLIGHT = 1,
}
declare enum WordBreak {
    NORMAL = 0,
    BREAK_ALL = 1,
    BREAK_WORD = 2,
}
declare enum LineBreakStrategy {
    GREEDY = 0,
    HIGH_QUALITY = 1,
    BALANCED = 2,
}
declare enum EllipsisMode {
    START = 0,
    CENTER = 1,
    END = 2,
}
declare type Nullable<T> = T | undefined;
declare enum OptionWidthMode {
    FIT_CONTENT = "fit_content",
    FIT_TRIGGER = "fit_trigger",
}
declare enum IlluminatedType {
    NONE = 0,
    BORDER = 1,
    CONTENT = 2,
    BORDER_CONTENT = 3,
    BLOOM_BORDER = 4,
    BLOOM_BORDER_CONTENT = 5,
}
declare enum FoldStatus {
    FOLD_STATUS_UNKNOWN = 0,
    FOLD_STATUS_EXPANDED = 1,
    FOLD_STATUS_FOLDED = 2,
    FOLD_STATUS_HALF_FOLDED = 3,
}
declare enum AppRotation {
    ROTATION_0 = 0,
    ROTATION_90 = 1,
    ROTATION_180 = 2,
    ROTATION_270 = 3,
}
declare enum EmbeddedType {
    EMBEDDED_UI_EXTENSION = 0,
}
declare enum MarqueeUpdateStrategy {
    DEFAULT = 0,
    PRESERVE_POSITION = 1,
}
declare enum TextDecorationStyle {
    SOLID = 0,
    DOUBLE = 1,
    DOTTED = 2,
    DASHED = 3,
    WAVY = 4,
}
declare enum TextSelectableMode {
    SELECTABLE_UNFOCUSABLE = 0,
    SELECTABLE_FOCUSABLE = 1,
    UNSELECTABLE = 2,
}
declare enum AccessibilityHoverType {
    HOVER_ENTER = 0,
    HOVER_MOVE = 1,
    HOVER_EXIT = 2,
    HOVER_CANCEL = 3,
}
declare enum WidthBreakpoint {
    WIDTH_XS = 0,
    WIDTH_SM = 1,
    WIDTH_MD = 2,
    WIDTH_LG = 3,
    WIDTH_XL = 4,
}
declare enum HeightBreakpoint {
    HEIGHT_SM = 0,
    HEIGHT_MD = 1,
    HEIGHT_LG = 2,
}
declare interface FlexOptions {
    direction?: FlexDirection;
    wrap?: FlexWrap;
    justifyContent?: FlexAlign;
    alignItems?: ItemAlign;
    alignContent?: FlexAlign;
    space?: FlexSpaceOptions;
}
declare interface FlexSpaceOptions {
    main?: LengthMetrics;
    cross?: LengthMetrics;
}
declare interface FlexInterface {
    (value?: FlexOptions): FlexAttribute;
}
declare class FlexAttribute extends CommonMethod<FlexAttribute> {
    pointLight(value: PointLightStyle): FlexAttribute;
}
declare interface FlowItemInterface {
    (): FlowItemAttribute;
}
declare class FlowItemAttribute extends CommonMethod<FlowItemAttribute> {
}
declare interface FocusBoxStyle {
    margin?: LengthMetrics;
    strokeColor?: ColorMetrics;
    strokeWidth?: LengthMetrics;
}
declare enum FocusPriority {
    AUTO = 0,
    PRIOR = 2000,
    PREVIOUS = 3000,
}
declare interface WindowStatusType {
    _WindowStatusTypeStub: string;
}
declare interface FolderStackOptions {
    upperItems?: string[];
}
declare interface FolderStackInterface {
    (options?: FolderStackOptions): FolderStackAttribute;
}
declare interface OnFoldStatusChangeInfo {
    foldStatus: FoldStatus;
}
declare type OnFoldStatusChangeCallback = ((event: OnFoldStatusChangeInfo) => void);
declare type OnHoverStatusChangeCallback = ((param: HoverEventParam) => void);
declare class FolderStackAttribute extends CommonMethod<FolderStackAttribute> {
    alignContent(value: Alignment): FolderStackAttribute;
    onFolderStateChange(value: OnFoldStatusChangeCallback): FolderStackAttribute;
    onHoverStatusChange(value: OnHoverStatusChangeCallback): FolderStackAttribute;
    enableAnimation(value: boolean): FolderStackAttribute;
    autoHalfFold(value: boolean): FolderStackAttribute;
}
declare interface HoverEventParam {
    foldStatus: FoldStatus;
    isHoverMode: boolean;
    appRotation: AppRotation;
    windowStatusType: WindowStatusType;
}
declare enum FormDimension {
    DIMENSION_1_2 = 0,
    Dimension_1_2 = 0,
    DIMENSION_2_2 = 1,
    Dimension_2_2 = 1,
    DIMENSION_2_4 = 2,
    Dimension_2_4 = 2,
    DIMENSION_4_4 = 3,
    Dimension_4_4 = 3,
    DIMENSION_2_1 = 4,
    Dimension_2_1 = 4,
    DIMENSION_1_1 = 6,
    DIMENSION_6_4 = 7,
}
declare enum FormRenderingMode {
    FULL_COLOR = 0,
    SINGLE_COLOR = 1,
}
declare enum FormShape {
    RECT = 1,
    CIRCLE = 2,
}
declare interface FormInfo {
    id: (number|string);
    name: string;
    bundle: string;
    ability: string;
    module: string;
    dimension?: FormDimension;
    temporary?: boolean;
    want?: Want;
    renderingMode?: FormRenderingMode;
    shape?: FormShape;
}
declare interface FormComponentInterface {
    (value: FormInfo): FormComponentAttribute;
}
declare interface FormCallbackInfo {
    id: number;
    idString: string;
}
declare type Callback_FormCallbackInfo_Void = ((parameter: FormCallbackInfo) => void);
declare type Literal_Number_errcode_String_msg = { errcode: number, msg: string }
declare type Callback_Literal_Number_errcode_String_msg_Void = ((info: { errcode: number, msg: string }) => void);
declare type Callback_Any_Void = ((info: any) => void);
declare class FormComponentAttribute extends CommonMethod<FormComponentAttribute> {
    size(value: SizeOptions): FormComponentAttribute;
    moduleName(value: string): FormComponentAttribute;
    dimension(value: FormDimension): FormComponentAttribute;
    allowUpdate(value: boolean): FormComponentAttribute;
    visibility(value: Visibility): FormComponentAttribute;
    onAcquired(value: ((parameter: FormCallbackInfo) => void)): FormComponentAttribute;
    onError(value: ((info: { errcode: number, msg: string }) => void)): FormComponentAttribute;
    onRouter(value: ((info: any) => void)): FormComponentAttribute;
    onUninstall(value: ((parameter: FormCallbackInfo) => void)): FormComponentAttribute;
    onLoad(value: (() => void)): FormComponentAttribute;
}
declare interface FormLinkOptions {
    action: string;
    moduleName?: string;
    bundleName?: string;
    abilityName?: string;
    uri?: string;
    params?: Object;
}
declare interface FormLinkInterface {
    (options: FormLinkOptions): FormLinkAttribute;
}
declare class FormLinkAttribute extends CommonMethod<FormLinkAttribute> {
}
declare interface GaugeOptions {
    value: number;
    min?: number;
    max?: number;
}
declare interface GaugeInterface {
    (options: GaugeOptions): GaugeAttribute;
}
declare interface GaugeShadowOptions extends MultiShadowOptions {
}
declare interface GaugeIndicatorOptions {
    icon?: ResourceStr;
    space?: Dimension;
}
declare interface GaugeConfiguration extends CommonConfiguration<GaugeConfiguration> {
    value: number;
    min: number;
    max: number;
}
declare type Tuple_Union_ResourceColor_LinearGradient_Number = [ (ResourceColor|LinearGradient), number ]
declare class GaugeAttribute extends CommonMethod<GaugeAttribute> {
    value(value: number): GaugeAttribute;
    startAngle(value: number): GaugeAttribute;
    endAngle(value: number): GaugeAttribute;
    colors(value: (ResourceColor|LinearGradient|[ (ResourceColor|LinearGradient), number ][])): GaugeAttribute;
    strokeWidth(value: Length): GaugeAttribute;
    description(value: CustomBuilder): GaugeAttribute;
    trackShadow(value: GaugeShadowOptions): GaugeAttribute;
    indicator(value: GaugeIndicatorOptions): GaugeAttribute;
    privacySensitive(value: boolean | undefined): GaugeAttribute;
    contentModifier(value: ContentModifier<GaugeConfiguration>): GaugeAttribute;
}
declare enum PanDirection {
    NONE = 0,
    None = 0,
    HORIZONTAL = 1,
    Horizontal = 1,
    LEFT = 2,
    Left = 2,
    RIGHT = 3,
    Right = 3,
    VERTICAL = 4,
    Vertical = 4,
    UP = 5,
    Up = 5,
    DOWN = 6,
    Down = 6,
    ALL = 7,
    All = 7,
}
declare enum SwipeDirection {
    NONE = 0,
    None = 0,
    HORIZONTAL = 1,
    Horizontal = 1,
    VERTICAL = 2,
    Vertical = 2,
    ALL = 3,
    All = 3,
}
declare enum GestureMode {
    SEQUENCE = 0,
    Sequence = 0,
    PARALLEL = 1,
    Parallel = 1,
    EXCLUSIVE = 2,
    Exclusive = 2,
}
declare enum GestureMask {
    NORMAL = 0,
    Normal = 0,
    IGNORE_INTERNAL = 1,
    IgnoreInternal = 1,
}
declare enum GestureJudgeResult {
    CONTINUE = 0,
    REJECT = 1,
}
declare namespace GestureControl {
    enum GestureType {
        TAP_GESTURE = 0,
        LONG_PRESS_GESTURE = 1,
        PAN_GESTURE = 2,
        PINCH_GESTURE = 3,
        SWIPE_GESTURE = 4,
        ROTATION_GESTURE = 5,
        DRAG = 6,
        CLICK = 7,
    }
}
declare interface GestureInfo {
    tag?: string;
    type: GestureControl.GestureType;
    isSystemGesture: boolean;
}
declare interface FingerInfo {
    id: number;
    globalX: number;
    globalY: number;
    localX: number;
    localY: number;
    displayX: number;
    displayY: number;
}
declare type GestureType = (TapGestureInterface|LongPressGestureInterface|PanGestureInterface|PinchGestureInterface|SwipeGestureInterface|RotationGestureInterface|GestureGroupInterface);
declare interface BaseGestureEvent extends BaseEvent {
    fingerList: FingerInfo[];
}
declare interface TapGestureEvent extends BaseGestureEvent {
}
declare interface LongPressGestureEvent extends BaseGestureEvent {
    repeat: boolean;
}
declare interface PanGestureEvent extends BaseGestureEvent {
    offsetX: number;
    offsetY: number;
    velocityX: number;
    velocityY: number;
    velocity: number;
}
declare interface PinchGestureEvent extends BaseGestureEvent {
    scale: number;
    pinchCenterX: number;
    pinchCenterY: number;
}
declare interface RotationGestureEvent extends BaseGestureEvent {
    angle: number;
}
declare interface SwipeGestureEvent extends BaseGestureEvent {
    angle: number;
    speed: number;
}
declare interface GestureEvent extends BaseEvent {
    repeat: boolean;
    fingerList: FingerInfo[];
    offsetX: number;
    offsetY: number;
    angle: number;
    speed: number;
    scale: number;
    pinchCenterX: number;
    pinchCenterY: number;
    velocityX: number;
    velocityY: number;
    velocity: number;
}
declare interface GestureInterface<T> {
    tag(tag: string): T;
    allowedTypes(types: SourceTool[]): T;
}
declare interface TapGestureParameters {
    count?: number;
    fingers?: number;
    distanceThreshold?: number;
}
declare type Callback_GestureEvent_Void = ((event: GestureEvent) => void);
declare interface TapGestureInterface extends GestureInterface<TapGestureInterface> {
    onAction(event: ((event: GestureEvent) => void)): TapGestureInterface;
    (value?: TapGestureParameters): TapGestureInterface;
}
declare type Literal_Number_duration_fingers_Boolean_repeat = { fingers?: number, repeat?: boolean, duration?: number }
declare interface LongPressGestureInterface extends GestureInterface<LongPressGestureInterface> {
    onAction(event: ((event: GestureEvent) => void)): LongPressGestureInterface;
    onActionEnd(event: ((event: GestureEvent) => void)): LongPressGestureInterface;
    onActionCancel(event: (() => void)): LongPressGestureInterface;
    (value?: { fingers?: number, repeat?: boolean, duration?: number }): LongPressGestureInterface;
}
declare type Literal_Number_distance_fingers_PanDirection_direction = { fingers?: number, direction?: PanDirection, distance?: number }
declare class PanGestureOptions {
    constructor(value?: { fingers?: number, direction?: PanDirection, distance?: number });
    setDirection(value: PanDirection): void;
    setDistance(value: number): void;
    setFingers(value: number): void;
    getDirection(): PanDirection;
}
declare interface PanGestureInterface extends GestureInterface<PanGestureInterface> {
    onActionStart(event: ((event: GestureEvent) => void)): PanGestureInterface;
    onActionUpdate(event: ((event: GestureEvent) => void)): PanGestureInterface;
    onActionEnd(event: ((event: GestureEvent) => void)): PanGestureInterface;
    onActionCancel(event: (() => void)): PanGestureInterface;
    (value?: ({ fingers?: number, direction?: PanDirection, distance?: number }|PanGestureOptions)): PanGestureInterface;
}
declare type Literal_Number_fingers_speed_SwipeDirection_direction = { fingers?: number, direction?: SwipeDirection, speed?: number }
declare interface SwipeGestureInterface extends GestureInterface<SwipeGestureInterface> {
    onAction(event: ((event: GestureEvent) => void)): SwipeGestureInterface;
    (value?: { fingers?: number, direction?: SwipeDirection, speed?: number }): SwipeGestureInterface;
}
declare type Literal_Number_distance_fingers = { fingers?: number, distance?: number }
declare interface PinchGestureInterface extends GestureInterface<PinchGestureInterface> {
    onActionStart(event: ((event: GestureEvent) => void)): PinchGestureInterface;
    onActionUpdate(event: ((event: GestureEvent) => void)): PinchGestureInterface;
    onActionEnd(event: ((event: GestureEvent) => void)): PinchGestureInterface;
    onActionCancel(event: (() => void)): PinchGestureInterface;
    (value?: { fingers?: number, distance?: number }): PinchGestureInterface;
}
declare type Literal_Number_angle_fingers = { fingers?: number, angle?: number }
declare interface RotationGestureInterface extends GestureInterface<RotationGestureInterface> {
    onActionStart(event: ((event: GestureEvent) => void)): RotationGestureInterface;
    onActionUpdate(event: ((event: GestureEvent) => void)): RotationGestureInterface;
    onActionEnd(event: ((event: GestureEvent) => void)): RotationGestureInterface;
    onActionCancel(event: (() => void)): RotationGestureInterface;
    (value?: { fingers?: number, angle?: number }): RotationGestureInterface;
}
declare interface GestureGroupInterface {
    onCancel(event: (() => void)): GestureGroupInterface;
    (mode: GestureMode, ...gesture: GestureType[]): GestureGroupInterface;
}
declare class GestureHandler<T> implements GestureInterface<T> {
    tag(tag: string): T;
    allowedTypes(types: SourceTool[]): T;
}
declare interface TapGestureHandlerOptions {
    count?: number;
    fingers?: number;
}
declare class TapGestureHandler extends GestureHandler<TapGestureHandler> {
    constructor(options?: TapGestureHandlerOptions);
    onAction(event: ((event: GestureEvent) => void)): TapGestureHandler;
}
declare interface LongPressGestureHandlerOptions {
    fingers?: number;
    repeat?: boolean;
    duration?: number;
}
declare class LongPressGestureHandler extends GestureHandler<LongPressGestureHandler> {
    constructor(options?: LongPressGestureHandlerOptions);
    onAction(event: ((event: GestureEvent) => void)): LongPressGestureHandler;
    onActionEnd(event: ((event: GestureEvent) => void)): LongPressGestureHandler;
    onActionCancel(event: (() => void)): LongPressGestureHandler;
}
declare interface PanGestureHandlerOptions {
    fingers?: number;
    direction?: PanDirection;
    distance?: number;
}
declare class PanGestureHandler extends GestureHandler<PanGestureHandler> {
    constructor(options?: PanGestureHandlerOptions);
    onActionStart(event: ((event: GestureEvent) => void)): PanGestureHandler;
    onActionUpdate(event: ((event: GestureEvent) => void)): PanGestureHandler;
    onActionEnd(event: ((event: GestureEvent) => void)): PanGestureHandler;
    onActionCancel(event: (() => void)): PanGestureHandler;
}
declare interface SwipeGestureHandlerOptions {
    fingers?: number;
    direction?: SwipeDirection;
    speed?: number;
}
declare class SwipeGestureHandler extends GestureHandler<SwipeGestureHandler> {
    constructor(options?: SwipeGestureHandlerOptions);
    onAction(event: ((event: GestureEvent) => void)): SwipeGestureHandler;
}
declare interface PinchGestureHandlerOptions {
    fingers?: number;
    distance?: number;
}
declare class PinchGestureHandler extends GestureHandler<PinchGestureHandler> {
    constructor(options?: PinchGestureHandlerOptions);
    onActionStart(event: ((event: GestureEvent) => void)): PinchGestureHandler;
    onActionUpdate(event: ((event: GestureEvent) => void)): PinchGestureHandler;
    onActionEnd(event: ((event: GestureEvent) => void)): PinchGestureHandler;
    onActionCancel(event: (() => void)): PinchGestureHandler;
}
declare interface RotationGestureHandlerOptions {
    fingers?: number;
    angle?: number;
}
declare class RotationGestureHandler extends GestureHandler<RotationGestureHandler> {
    constructor(options?: RotationGestureHandlerOptions);
    onActionStart(event: ((event: GestureEvent) => void)): RotationGestureHandler;
    onActionUpdate(event: ((event: GestureEvent) => void)): RotationGestureHandler;
    onActionEnd(event: ((event: GestureEvent) => void)): RotationGestureHandler;
    onActionCancel(event: (() => void)): RotationGestureHandler;
}
declare interface GestureGroupGestureHandlerOptions {
    stub: string;
}
declare class GestureGroupHandler extends GestureHandler<GestureGroupHandler> {
    constructor(options?: GestureGroupGestureHandlerOptions);
    onCancel(event: (() => void)): GestureGroupHandler;
}
declare enum GesturePriority {
    NORMAL = 0,
    PRIORITY = 1,
}
declare enum GestureRecognizerState {
    READY = 0,
    DETECTING = 1,
    PENDING = 2,
    BLOCKED = 3,
    SUCCESSFUL = 4,
    FAILED = 5,
}
declare class ScrollableTargetInfo extends EventTargetInfo {
    isBegin(): boolean;
    isEnd(): boolean;
}
declare class EventTargetInfo {
    getId(): string;
}
declare class GestureRecognizer {
    getTag(): string;
    getType(): GestureControl.GestureType;
    isBuiltIn(): boolean;
    setEnabled(isEnabled: boolean): void;
    isEnabled(): boolean;
    getState(): GestureRecognizerState;
    getEventTargetInfo(): EventTargetInfo;
    isValid(): boolean;
}
declare class PanRecognizer extends GestureRecognizer {
    getPanGestureOptions(): PanGestureOptions;
}
declare type Callback_Number_Tuple_Number_Number = ((index: number) => [ number, number ]);
declare type Tuple_Number_Number_Number_Number = [ number, number, number, number ]
declare type Callback_Number_Tuple_Number_Number_Number_Number = ((index: number) => [ number, number, number, number ]);
declare interface GridLayoutOptions {
    regularSize: [ number, number ];
    irregularIndexes?: number[];
    onGetIrregularSizeByIndex?: ((index: number) => [ number, number ]);
    onGetRectByIndex?: ((index: number) => [ number, number, number, number ]);
}
declare interface GridInterface {
    (scroller?: Scroller, layoutOptions?: GridLayoutOptions): GridAttribute;
}
declare enum GridDirection {
    ROW = 0,
    Row = 0,
    COLUMN = 1,
    Column = 1,
    ROW_REVERSE = 2,
    RowReverse = 2,
    COLUMN_REVERSE = 3,
    ColumnReverse = 3,
}
declare enum GridItemAlignment {
    DEFAULT = 0,
    STRETCH = 1,
}
declare interface ComputedBarAttribute {
    totalOffset: number;
    totalLength: number;
}
declare type Callback_Number_Number_ComputedBarAttribute = ((index: number, offset: number) => ComputedBarAttribute);
declare type Callback_Number_Number_Void = ((first: number, last: number) => void);
declare type onItemDragStart_event_type = ((event: ItemDragInfo, itemIndex: number) => CustomBuilder);
declare type Callback_ItemDragInfo_Void = ((event: ItemDragInfo) => void);
declare type Callback_ItemDragInfo_Number_Number_Void = ((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void);
declare type Callback_ItemDragInfo_Number_Void = ((event: ItemDragInfo, itemIndex: number) => void);
declare type Callback_ItemDragInfo_Number_Number_Boolean_Void = ((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void);
declare type Literal_Number_offsetRemain = { offsetRemain: number }
declare type Callback_Number_ScrollState_Literal_Number_offsetRemain = ((offset: number, state: ScrollState) => { offsetRemain: number });
declare class GridAttribute extends ScrollableCommonMethod<GridAttribute> {
    columnsTemplate(value: string): GridAttribute;
    rowsTemplate(value: string): GridAttribute;
    columnsGap(value: Length): GridAttribute;
    rowsGap(value: Length): GridAttribute;
    scrollBarWidth(value: (number|string)): GridAttribute;
    scrollBarColor(value: (Color|number|string)): GridAttribute;
    scrollBar(value: BarState): GridAttribute;
    onScrollBarUpdate(value: ((index: number, offset: number) => ComputedBarAttribute)): GridAttribute;
    onScrollIndex(value: ((first: number, last: number) => void)): GridAttribute;
    cachedCount(value: number): GridAttribute;
    editMode(value: boolean): GridAttribute;
    multiSelectable(value: boolean): GridAttribute;
    maxCount(value: number): GridAttribute;
    minCount(value: number): GridAttribute;
    cellLength(value: number): GridAttribute;
    layoutDirection(value: GridDirection): GridAttribute;
    supportAnimation(value: boolean): GridAttribute;
    onItemDragStart(value: ((event: ItemDragInfo, itemIndex: number) => CustomBuilder)): GridAttribute;
    onItemDragEnter(value: ((event: ItemDragInfo) => void)): GridAttribute;
    onItemDragMove(value: ((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void)): GridAttribute;
    onItemDragLeave(value: ((event: ItemDragInfo, itemIndex: number) => void)): GridAttribute;
    onItemDrop(value: ((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void)): GridAttribute;
    nestedScroll(value: NestedScrollOptions): GridAttribute;
    enableScrollInteraction(value: boolean): GridAttribute;
    friction(value: (number|Resource)): GridAttribute;
    alignItems(value: GridItemAlignment | undefined): GridAttribute;
    onScroll(value: ((first: number, last: number) => void)): GridAttribute;
    onWillScroll(value: OnWillScrollCallback | undefined): GridAttribute;
    onDidScroll(value: OnScrollCallback | undefined): GridAttribute;
    onReachStart(value: (() => void)): GridAttribute;
    onReachEnd(value: (() => void)): GridAttribute;
    onScrollStart(value: (() => void)): GridAttribute;
    onScrollStop(value: (() => void)): GridAttribute;
    onScrollFrameBegin(value: ((offset: number, state: ScrollState) => { offsetRemain: number })): GridAttribute;
    cachedCount(count: number, show: boolean): GridAttribute;
    edgeEffect(value: EdgeEffect, options?: EdgeEffectOptions): GridAttribute;
}
declare enum GridItemStyle {
    NONE = 0,
    PLAIN = 1,
}
declare interface GridItemOptions {
    style?: GridItemStyle;
}
declare interface GridItemInterface {
    (value?: GridItemOptions): GridItemAttribute;
}
declare class GridItemAttribute extends CommonMethod<GridItemAttribute> {
    rowStart(value: number): GridItemAttribute;
    rowEnd(value: number): GridItemAttribute;
    columnStart(value: number): GridItemAttribute;
    columnEnd(value: number): GridItemAttribute;
    forceRebuild(value: boolean): GridItemAttribute;
    selectable(value: boolean): GridItemAttribute;
    selected(value: boolean): GridItemAttribute;
    onSelect(value: ((parameter: boolean) => void)): GridItemAttribute;
    _onChangeEvent_selected(callback_: ((parameter: boolean) => void)): void;
}
declare interface GridColColumnOption {
    xs?: number;
    sm?: number;
    md?: number;
    lg?: number;
    xl?: number;
    xxl?: number;
}
declare interface GridColOptions {
    span?: (number|GridColColumnOption);
    offset?: (number|GridColColumnOption);
    order?: (number|GridColColumnOption);
}
declare interface GridColInterface {
    (option?: GridColOptions): GridColAttribute;
}
declare class GridColAttribute extends CommonMethod<GridColAttribute> {
    span(value: (number|GridColColumnOption)): GridColAttribute;
    gridColOffset(value: (number|GridColColumnOption)): GridColAttribute;
    order(value: (number|GridColColumnOption)): GridColAttribute;
}
declare enum SizeType {
    AUTO = 0,
    Auto = 0,
    XS = 1,
    SM = 2,
    MD = 3,
    LG = 4,
}
declare interface GridContainerOptions {
    columns?: (number|string);
    sizeType?: SizeType;
    gutter?: (number|string);
    margin?: (number|string);
}
declare interface GridContainerInterface {
    (value?: GridContainerOptions): GridContainerAttribute;
}
declare class GridContainerAttribute extends ColumnAttribute {
}
declare interface GridRowSizeOption {
    xs?: Length;
    sm?: Length;
    md?: Length;
    lg?: Length;
    xl?: Length;
    xxl?: Length;
}
declare interface GridRowColumnOption {
    xs?: number;
    sm?: number;
    md?: number;
    lg?: number;
    xl?: number;
    xxl?: number;
}
declare interface GutterOption {
    x?: (Length|GridRowSizeOption);
    y?: (Length|GridRowSizeOption);
}
declare enum BreakpointsReference {
    WINDOW_SIZE = 0,
    WindowSize = 0,
    COMPONENT_SIZE = 1,
    ComponentSize = 1,
}
declare enum GridRowDirection {
    ROW = 0,
    Row = 0,
    ROW_REVERSE = 1,
    RowReverse = 1,
}
declare interface BreakPoints {
    value?: string[];
    reference?: BreakpointsReference;
}
declare interface GridRowOptions {
    gutter?: (Length|GutterOption);
    columns?: (number|GridRowColumnOption);
    breakpoints?: BreakPoints;
    direction?: GridRowDirection;
}
declare interface GridRowInterface {
    (option?: GridRowOptions): GridRowAttribute;
}
declare type Callback_String_Void = ((breakpoints: string) => void);
declare class GridRowAttribute extends CommonMethod<GridRowAttribute> {
    onBreakpointChange(value: ((breakpoints: string) => void)): GridRowAttribute;
    alignItems(value: ItemAlign): GridRowAttribute;
}
declare interface HyperlinkInterface {
    (address: (string|Resource), content?: (string|Resource)): HyperlinkAttribute;
}
declare class HyperlinkAttribute extends CommonMethod<HyperlinkAttribute> {
    color(value: (Color|number|string|Resource)): HyperlinkAttribute;
}
declare interface DrawableDescriptor {
    _DrawableDescriptorStub: string;
}
declare interface DrawingColorFilter {
    _DrawingColorFilterStub: string;
}
declare interface ResolutionQuality {
    _ResolutionQualityStub: string;
}
declare interface DrawingLattice {
    _DrawingLatticeStub: string;
}
declare enum ImageRenderMode {
    ORIGINAL = 0,
    Original = 0,
    TEMPLATE = 1,
    Template = 1,
}
declare enum ImageContent {
    EMPTY = 0,
}
declare enum DynamicRangeMode {
    HIGH = 0,
    CONSTRAINT = 1,
    STANDARD = 2,
}
declare enum ImageInterpolation {
    NONE = 0,
    None = 0,
    LOW = 1,
    Low = 1,
    MEDIUM = 2,
    Medium = 2,
    HIGH = 3,
    High = 3,
}
declare interface ImageInterface {
    (src: (PixelMap|ResourceStr|DrawableDescriptor)): ImageAttribute;
    (src: (PixelMap|ResourceStr|DrawableDescriptor|ImageContent)): ImageAttribute;
    (src: (PixelMap|ResourceStr|DrawableDescriptor), imageAIOptions: ImageAIOptions): ImageAttribute;
}
declare interface ImageSourceSize {
    width: number;
    height: number;
}
declare type Type_ImageAttribute_onComplete_callback_event = { width: number, height: number, componentWidth: number, componentHeight: number, loadingStatus: number, contentWidth: number, contentHeight: number, contentOffsetX: number, contentOffsetY: number }
declare type Callback_Type_ImageAttribute_onComplete_callback_event_Void = ((event?: { width: number, height: number, componentWidth: number, componentHeight: number, loadingStatus: number, contentWidth: number, contentHeight: number, contentOffsetX: number, contentOffsetY: number }) => void);
declare class ImageAttribute extends CommonMethod<ImageAttribute> {
    alt(value: (string|Resource|PixelMap)): ImageAttribute;
    matchTextDirection(value: boolean): ImageAttribute;
    fitOriginalSize(value: boolean): ImageAttribute;
    fillColor(value: ResourceColor): ImageAttribute;
    objectFit(value: ImageFit): ImageAttribute;
    objectRepeat(value: ImageRepeat): ImageAttribute;
    autoResize(value: boolean): ImageAttribute;
    renderMode(value: ImageRenderMode): ImageAttribute;
    dynamicRangeMode(value: DynamicRangeMode): ImageAttribute;
    interpolation(value: ImageInterpolation): ImageAttribute;
    sourceSize(value: ImageSourceSize): ImageAttribute;
    syncLoad(value: boolean): ImageAttribute;
    colorFilter(value: (ColorFilter|DrawingColorFilter)): ImageAttribute;
    copyOption(value: CopyOptions): ImageAttribute;
    draggable(value: boolean): ImageAttribute;
    pointLight(value: PointLightStyle): ImageAttribute;
    edgeAntialiasing(value: number): ImageAttribute;
    onComplete(value: ((event?: { width: number, height: number, componentWidth: number, componentHeight: number, loadingStatus: number, contentWidth: number, contentHeight: number, contentOffsetX: number, contentOffsetY: number }) => void)): ImageAttribute;
    onError(value: ImageErrorCallback): ImageAttribute;
    onFinish(value: (() => void)): ImageAttribute;
    enableAnalyzer(value: boolean): ImageAttribute;
    analyzerConfig(value: ImageAnalyzerConfig): ImageAttribute;
    resizable(value: ResizableOptions): ImageAttribute;
    privacySensitive(value: boolean): ImageAttribute;
    enhancedImageQuality(value: ResolutionQuality): ImageAttribute;
}
declare type ImageErrorCallback = ((error: ImageError) => void);
declare interface ImageError {
    componentWidth: number;
    componentHeight: number;
    message: string;
}
declare interface ResizableOptions {
    slice?: EdgeWidths;
    lattice?: DrawingLattice;
}
declare interface ImageAnimatorInterface {
    (): ImageAnimatorAttribute;
}
declare interface ImageFrameInfo {
    src: (string|Resource|PixelMap);
    width?: (number|string);
    height?: (number|string);
    top?: (number|string);
    left?: (number|string);
    duration?: number;
}
declare class ImageAnimatorAttribute extends CommonMethod<ImageAnimatorAttribute> {
    images(value: ImageFrameInfo[]): ImageAnimatorAttribute;
    state(value: AnimationStatus): ImageAnimatorAttribute;
    duration(value: number): ImageAnimatorAttribute;
    reverse(value: boolean): ImageAnimatorAttribute;
    fixedSize(value: boolean): ImageAnimatorAttribute;
    preDecode(value: number): ImageAnimatorAttribute;
    fillMode(value: FillMode): ImageAnimatorAttribute;
    iterations(value: number): ImageAnimatorAttribute;
    onStart(value: (() => void)): ImageAnimatorAttribute;
    onPause(value: (() => void)): ImageAnimatorAttribute;
    onRepeat(value: (() => void)): ImageAnimatorAttribute;
    onCancel(value: (() => void)): ImageAnimatorAttribute;
    onFinish(value: (() => void)): ImageAnimatorAttribute;
}
declare enum ImageAnalyzerType {
    SUBJECT = 0,
    TEXT = 1,
    OBJECT_LOOKUP = 2,
}
declare class ImageAnalyzerController {
    constructor();
    getImageAnalyzerSupportTypes(): ImageAnalyzerType[];
}
declare interface ImageAnalyzerConfig {
    types: ImageAnalyzerType[];
}
declare interface ImageAIOptions {
    types?: ImageAnalyzerType[];
    aiController?: ImageAnalyzerController;
}
declare interface ImageSpanInterface {
    (value: (ResourceStr|PixelMap)): ImageSpanAttribute;
}
declare class ImageSpanAttribute extends BaseSpan<ImageSpanAttribute> {
    verticalAlign(value: ImageSpanAlignment): ImageSpanAttribute;
    colorFilter(value: (ColorFilter|DrawingColorFilter)): ImageSpanAttribute;
    objectFit(value: ImageFit): ImageSpanAttribute;
    onComplete(value: ImageCompleteCallback): ImageSpanAttribute;
    onError(value: ImageErrorCallback): ImageSpanAttribute;
    alt(value: PixelMap): ImageSpanAttribute;
}
declare type ImageCompleteCallback = ((result: ImageLoadResult) => void);
declare interface ImageLoadResult {
    width: number;
    height: number;
    componentWidth: number;
    componentHeight: number;
    loadingStatus: number;
    contentWidth: number;
    contentHeight: number;
    contentOffsetX: number;
    contentOffsetY: number;
}
declare enum DataOperationType {
    ADD = "add",
    DELETE = "delete",
    EXCHANGE = "exchange",
    MOVE = "move",
    CHANGE = "change",
    RELOAD = "reload",
}
declare interface DataAddOperation {
    type: DataOperationType;
    index: number;
    count?: number;
    key?: (string|string[]);
}
declare interface DataDeleteOperation {
    type: DataOperationType;
    index: number;
    count?: number;
}
declare interface DataChangeOperation {
    type: DataOperationType;
    index: number;
    key?: string;
}
declare interface MoveIndex {
    from: number;
    to: number;
}
declare interface ExchangeIndex {
    start: number;
    end: number;
}
declare interface ExchangeKey {
    start: string;
    end: string;
}
declare interface DataMoveOperation {
    type: DataOperationType;
    index: MoveIndex;
    key?: string;
}
declare interface DataExchangeOperation {
    type: DataOperationType;
    index: ExchangeIndex;
    key?: ExchangeKey;
}
declare interface DataReloadOperation {
    type: DataOperationType;
}
declare type DataOperation = (DataAddOperation|DataDeleteOperation|DataChangeOperation|DataMoveOperation|DataExchangeOperation|DataReloadOperation);
declare interface DataChangeListener {
    onDataReloaded(): void;
    onDataAdded(index: number): void;
    onDataAdd(index: number): void;
    onDataMoved(from: number, to: number): void;
    onDataMove(from: number, to: number): void;
    onDataDeleted(index: number): void;
    onDataDelete(index: number): void;
    onDataChanged(index: number): void;
    onDataChange(index: number): void;
    onDatasetChange(dataOperations: DataOperation[]): void;
}
declare interface LineOptions {
    width?: (string|number);
    height?: (string|number);
}
declare interface LineInterface {
    new(options?: LineOptions): LineAttribute;
    (options?: LineOptions): LineAttribute;
}
declare class LineAttribute extends CommonShapeMethod<LineAttribute> {
    startPoint(value: Length[]): LineAttribute;
    endPoint(value: Length[]): LineAttribute;
}
declare enum ScrollState {
    IDLE = 0,
    Idle = 0,
    SCROLL = 1,
    Scroll = 1,
    FLING = 2,
    Fling = 2,
}
declare enum ListItemAlign {
    START = 0,
    Start = 0,
    CENTER = 1,
    Center = 1,
    END = 2,
    End = 2,
}
declare enum ListItemGroupArea {
    NONE = 0,
    IN_LIST_ITEM_AREA = 1,
    IN_HEADER_AREA = 2,
    IN_FOOTER_AREA = 3,
}
declare enum StickyStyle {
    NONE = 0,
    None = 0,
    HEADER = 1,
    Header = 1,
    FOOTER = 2,
    Footer = 2,
}
declare enum ChainEdgeEffect {
    DEFAULT = 0,
    STRETCH = 1,
}
declare enum ScrollSnapAlign {
    NONE = 0,
    START = 1,
    CENTER = 2,
    END = 3,
}
declare interface ChainAnimationOptions {
    minSpace: Length;
    maxSpace: Length;
    conductivity?: number;
    intensity?: number;
    edgeEffect?: ChainEdgeEffect;
    stiffness?: number;
    damping?: number;
}
declare interface CloseSwipeActionOptions {
    onFinish?: (() => void);
}
declare interface VisibleListContentInfo {
    index: number;
    itemGroupArea?: ListItemGroupArea;
    itemIndexInGroup?: number;
}
declare type OnScrollVisibleContentChangeCallback = ((start: VisibleListContentInfo, end: VisibleListContentInfo) => void);
declare class ListScroller extends Scroller {
    getItemRectInGroup(index: number, indexInGroup: number): RectResult;
    scrollToItemInGroup(index: number, indexInGroup: number, smooth?: boolean, align?: ScrollAlign): void;
    closeAllSwipeActions(options?: CloseSwipeActionOptions): void;
    getVisibleListContentInfo(x: number, y: number): VisibleListContentInfo;
}
declare interface ListOptions {
    initialIndex?: number;
    space?: (number|string);
    scroller?: Scroller;
}
declare interface ListInterface {
    (options?: ListOptions): ListAttribute;
}
declare interface ListDividerOptions {
    strokeWidth: Length;
    color?: ResourceColor;
    startMargin?: Length;
    endMargin?: Length;
}
declare type Callback_Number_Number_Number_Void = ((start: number, end: number, center: number) => void);
declare type Callback_Number_Boolean = ((index: number) => boolean);
declare type Callback_Number_Number_Boolean = ((from: number, to: number) => boolean);
declare class ListAttribute extends ScrollableCommonMethod<ListAttribute> {
    alignListItem(value: ListItemAlign): ListAttribute;
    listDirection(value: Axis): ListAttribute;
    scrollBar(value: BarState): ListAttribute;
    contentStartOffset(value: number): ListAttribute;
    contentEndOffset(value: number): ListAttribute;
    divider(value: ListDividerOptions | undefined): ListAttribute;
    editMode(value: boolean): ListAttribute;
    multiSelectable(value: boolean): ListAttribute;
    cachedCount(value: number): ListAttribute;
    chainAnimation(value: boolean): ListAttribute;
    chainAnimationOptions(value: ChainAnimationOptions): ListAttribute;
    sticky(value: StickyStyle): ListAttribute;
    scrollSnapAlign(value: ScrollSnapAlign): ListAttribute;
    nestedScroll(value: NestedScrollOptions): ListAttribute;
    enableScrollInteraction(value: boolean): ListAttribute;
    friction(value: (number|Resource)): ListAttribute;
    childrenMainSize(value: ChildrenMainSize): ListAttribute;
    maintainVisibleContentPosition(value: boolean): ListAttribute;
    onScroll(value: ((first: number, last: number) => void)): ListAttribute;
    onScrollIndex(value: ((start: number, end: number, center: number) => void)): ListAttribute;
    onScrollVisibleContentChange(value: OnScrollVisibleContentChangeCallback): ListAttribute;
    onWillScroll(value: OnWillScrollCallback | undefined): ListAttribute;
    onDidScroll(value: OnScrollCallback | undefined): ListAttribute;
    onReachStart(value: (() => void)): ListAttribute;
    onReachEnd(value: (() => void)): ListAttribute;
    onScrollStart(value: (() => void)): ListAttribute;
    onScrollStop(value: (() => void)): ListAttribute;
    onItemDelete(value: ((index: number) => boolean)): ListAttribute;
    onItemMove(value: ((from: number, to: number) => boolean)): ListAttribute;
    onItemDragStart(value: ((event: ItemDragInfo, itemIndex: number) => CustomBuilder)): ListAttribute;
    onItemDragEnter(value: ((event: ItemDragInfo) => void)): ListAttribute;
    onItemDragMove(value: ((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void)): ListAttribute;
    onItemDragLeave(value: ((event: ItemDragInfo, itemIndex: number) => void)): ListAttribute;
    onItemDrop(value: ((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void)): ListAttribute;
    onScrollFrameBegin(value: ((offset: number, state: ScrollState) => { offsetRemain: number })): ListAttribute;
    lanes(value: (number|LengthConstrain), gutter?: Dimension): ListAttribute;
    edgeEffect(value: EdgeEffect, options?: EdgeEffectOptions): ListAttribute;
    cachedCount(count: number, show: boolean): ListAttribute;
}
declare enum Sticky {
    NONE = 0,
    None = 0,
    NORMAL = 1,
    Normal = 1,
    OPACITY = 2,
    Opacity = 2,
}
declare enum EditMode {
    NONE = 0,
    None = 0,
    DELETABLE = 1,
    Deletable = 1,
    MOVABLE = 2,
    Movable = 2,
}
declare enum SwipeEdgeEffect {
    SPRING = 0,
    Spring = 0,
    NONE = 1,
    None = 1,
}
declare enum SwipeActionState {
    COLLAPSED = 0,
    EXPANDED = 1,
    ACTIONING = 2,
}
declare type Callback_SwipeActionState_Void = ((state: SwipeActionState) => void);
declare interface SwipeActionItem {
    builder?: CustomBuilder;
    actionAreaDistance?: Length;
    onAction?: (() => void);
    onEnterActionArea?: (() => void);
    onExitActionArea?: (() => void);
    onStateChange?: ((state: SwipeActionState) => void);
}
declare interface SwipeActionOptions {
    start?: (CustomBuilder|SwipeActionItem);
    end?: (CustomBuilder|SwipeActionItem);
    edgeEffect?: SwipeEdgeEffect;
    onOffsetChange?: ((index: number) => void);
}
declare enum ListItemStyle {
    NONE = 0,
    CARD = 1,
}
declare interface ListItemOptions {
    style?: ListItemStyle;
}
declare interface ListItemInterface {
    (value?: ListItemOptions): ListItemAttribute;
    (value?: string): ListItemAttribute;
}
declare class ListItemAttribute extends CommonMethod<ListItemAttribute> {
    sticky(value: Sticky): ListItemAttribute;
    editable(value: (boolean|EditMode)): ListItemAttribute;
    selectable(value: boolean): ListItemAttribute;
    selected(value: boolean): ListItemAttribute;
    swipeAction(value: SwipeActionOptions): ListItemAttribute;
    onSelect(value: ((parameter: boolean) => void)): ListItemAttribute;
    _onChangeEvent_selected(callback_: ((parameter: boolean) => void)): void;
}
declare enum ListItemGroupStyle {
    NONE = 0,
    CARD = 1,
}
declare interface ListItemGroupOptions {
    header?: CustomBuilder;
    headerComponent?: ComponentContent;
    footer?: CustomBuilder;
    footerComponent?: ComponentContent;
    space?: (number|string);
    style?: ListItemGroupStyle;
}
declare interface ListItemGroupInterface {
    (options?: ListItemGroupOptions): ListItemGroupAttribute;
}
declare class ListItemGroupAttribute extends CommonMethod<ListItemGroupAttribute> {
    divider(value: ListDividerOptions | undefined): ListItemGroupAttribute;
    childrenMainSize(value: ChildrenMainSize): ListItemGroupAttribute;
}
declare enum LoadingProgressStyle {
    DEFAULT = 0,
    Default = 0,
    CIRCULAR = 1,
    Circular = 1,
    ORBITAL = 2,
    Orbital = 2,
}
declare interface LoadingProgressInterface {
    (): LoadingProgressAttribute;
}
declare class LoadingProgressAttribute extends CommonMethod<LoadingProgressAttribute> {
    color(value: ResourceColor): LoadingProgressAttribute;
    enableLoading(value: boolean): LoadingProgressAttribute;
    contentModifier(value: ContentModifier<LoadingProgressConfiguration>): LoadingProgressAttribute;
}
declare interface LoadingProgressConfiguration extends CommonConfiguration<LoadingProgressConfiguration> {
    enableLoading: boolean;
}
declare enum LocationIconStyle {
    FULL_FILLED = 0,
    LINES = 1,
}
declare enum LocationDescription {
    CURRENT_LOCATION = 0,
    ADD_LOCATION = 1,
    SELECT_LOCATION = 2,
    SHARE_LOCATION = 3,
    SEND_LOCATION = 4,
    LOCATING = 5,
    LOCATION = 6,
    SEND_CURRENT_LOCATION = 7,
    RELOCATION = 8,
    PUNCH_IN = 9,
    CURRENT_POSITION = 10,
}
declare interface LocationButtonOptions {
    icon?: LocationIconStyle;
    text?: LocationDescription;
    buttonType?: ButtonType;
}
declare enum LocationButtonOnClickResult {
    SUCCESS = 0,
    TEMPORARY_AUTHORIZATION_FAILED = 1,
}
declare interface LocationButtonInterface {
    (): LocationButtonAttribute;
    (options: LocationButtonOptions): LocationButtonAttribute;
}
declare type Callback_ClickEvent_LocationButtonOnClickResult_Void = ((event: ClickEvent, result: LocationButtonOnClickResult) => void);
declare class LocationButtonAttribute extends SecurityComponentMethod<LocationButtonAttribute> {
    onClick(value: ((event: ClickEvent, result: LocationButtonOnClickResult) => void)): LocationButtonAttribute;
}
declare class Matrix2D {
    constructor();
    constructor(unit: LengthMetricsUnit);
    scaleX?: number;
    rotateY?: number;
    rotateX?: number;
    scaleY?: number;
    translateX?: number;
    translateY?: number;
    identity(): Matrix2D;
    invert(): Matrix2D;
    multiply(other?: Matrix2D): Matrix2D;
    rotate(rx?: number, ry?: number): Matrix2D;
    rotate(degree: number, rx?: number, ry?: number): Matrix2D;
    translate(tx?: number, ty?: number): Matrix2D;
    scale(sx?: number, sy?: number): Matrix2D;
}
declare interface MarqueeOptions {
    start: boolean;
    step?: number;
    loop?: number;
    fromStart?: boolean;
    src: string;
}
declare interface MarqueeInterface {
    (options: MarqueeOptions): MarqueeAttribute;
}
declare class MarqueeAttribute extends CommonMethod<MarqueeAttribute> {
    fontColor(value: ResourceColor): MarqueeAttribute;
    fontSize(value: Length): MarqueeAttribute;
    allowScale(value: boolean): MarqueeAttribute;
    fontWeight(value: (number|FontWeight|string)): MarqueeAttribute;
    fontFamily(value: (string|Resource)): MarqueeAttribute;
    marqueeUpdateStrategy(value: MarqueeUpdateStrategy): MarqueeAttribute;
    onStart(value: (() => void)): MarqueeAttribute;
    onBounce(value: (() => void)): MarqueeAttribute;
    onFinish(value: (() => void)): MarqueeAttribute;
}
declare interface ASTCResource {
    sources: string[];
    column: number;
}
declare interface MediaCachedImageInterface {
    (src: (PixelMap|ResourceStr|DrawableDescriptor|ASTCResource)): MediaCachedImageAttribute;
}
declare class MediaCachedImageAttribute extends ImageAttribute {
}
declare interface MenuInterface {
    (): MenuAttribute;
}
declare enum SubMenuExpandingMode {
    SIDE_EXPAND = 0,
    EMBEDDED_EXPAND = 1,
    STACK_EXPAND = 2,
}
declare class MenuAttribute extends CommonMethod<MenuAttribute> {
    fontSize(value: Length): MenuAttribute;
    font(value: Font): MenuAttribute;
    fontColor(value: ResourceColor): MenuAttribute;
    radius(value: (Dimension|BorderRadiuses)): MenuAttribute;
    menuItemDivider(value: DividerStyleOptions | undefined): MenuAttribute;
    menuItemGroupDivider(value: DividerStyleOptions | undefined): MenuAttribute;
    subMenuExpandingMode(value: SubMenuExpandingMode): MenuAttribute;
}
declare interface MenuItemOptions {
    startIcon?: ResourceStr;
    symbolStartIcon?: SymbolGlyphModifier;
    content?: ResourceStr;
    endIcon?: ResourceStr;
    symbolEndIcon?: SymbolGlyphModifier;
    labelInfo?: ResourceStr;
    builder?: CustomBuilder;
}
declare interface MenuItemInterface {
    (value?: (MenuItemOptions|CustomBuilder)): MenuItemAttribute;
}
declare class MenuItemAttribute extends CommonMethod<MenuItemAttribute> {
    selected(value: boolean): MenuItemAttribute;
    selectIcon(value: (boolean|ResourceStr|SymbolGlyphModifier)): MenuItemAttribute;
    onChange(value: ((parameter: boolean) => void)): MenuItemAttribute;
    contentFont(value: Font): MenuItemAttribute;
    contentFontColor(value: ResourceColor): MenuItemAttribute;
    labelFont(value: Font): MenuItemAttribute;
    labelFontColor(value: ResourceColor): MenuItemAttribute;
    _onChangeEvent_selected(callback_: ((parameter: boolean) => void)): void;
}
declare interface MenuItemGroupOptions {
    header?: (ResourceStr|CustomBuilder);
    footer?: (ResourceStr|CustomBuilder);
}
declare interface MenuItemGroupInterface {
    (value?: MenuItemGroupOptions): MenuItemGroupAttribute;
}
declare class MenuItemGroupAttribute extends CommonMethod<MenuItemGroupAttribute> {
}
declare interface NavDestinationCommonTitle {
    main: (string|Resource);
    sub: (string|Resource);
}
declare interface NavDestinationCustomTitle {
    builder: CustomBuilder;
    height: (TitleHeight|Length);
}
declare enum NavigationSystemTransitionType {
    DEFAULT = 0,
    NONE = 1,
    TITLE = 2,
    CONTENT = 3,
}
declare enum NavDestinationMode {
    STANDARD = 0,
    DIALOG = 1,
}
declare interface NavDestinationInterface {
    (): NavDestinationAttribute;
}
declare interface RouteMapConfig {
    name: string;
    pageSourceFile: string;
    data: Object;
}
declare interface NavDestinationContext {
    pathInfo: NavPathInfo;
    pathStack: NavPathStack;
    navDestinationId?: string;
    getConfigInRouteMap(): RouteMapConfig | undefined;
}
declare type Callback_Boolean = (() => boolean);
declare type Callback_NavDestinationContext_Void = ((parameter: NavDestinationContext) => void);
declare class NavDestinationAttribute extends CommonMethod<NavDestinationAttribute> {
    hideTitleBar(value: boolean): NavDestinationAttribute;
    onShown(value: (() => void)): NavDestinationAttribute;
    onHidden(value: (() => void)): NavDestinationAttribute;
    onBackPressed(value: (() => boolean)): NavDestinationAttribute;
    mode(value: NavDestinationMode): NavDestinationAttribute;
    backButtonIcon(value: (ResourceStr|PixelMap|SymbolGlyphModifier)): NavDestinationAttribute;
    menus(value: (NavigationMenuItem[]|CustomBuilder)): NavDestinationAttribute;
    onReady(value: ((parameter: NavDestinationContext) => void)): NavDestinationAttribute;
    onWillAppear(value: (() => void)): NavDestinationAttribute;
    onWillDisappear(value: (() => void)): NavDestinationAttribute;
    onWillShow(value: (() => void)): NavDestinationAttribute;
    onWillHide(value: (() => void)): NavDestinationAttribute;
    systemBarStyle(value: SystemBarStyle | undefined): NavDestinationAttribute;
    recoverable(value: boolean | undefined): NavDestinationAttribute;
    systemTransition(value: NavigationSystemTransitionType): NavDestinationAttribute;
    title(value: (string|CustomBuilder|NavDestinationCommonTitle|NavDestinationCustomTitle|Resource), options?: NavigationTitleOptions): NavDestinationAttribute;
    hideTitleBar(hide: boolean, animated: boolean): NavDestinationAttribute;
    toolbarConfiguration(toolbarParam: (ToolbarItem[]|CustomBuilder), options?: NavigationToolbarOptions): NavDestinationAttribute;
    hideToolBar(hide: boolean, animated?: boolean): NavDestinationAttribute;
    ignoreLayoutSafeArea(types?: LayoutSafeAreaType[], edges?: LayoutSafeAreaEdge[]): NavDestinationAttribute;
}
declare interface RouteInfo {
    name: string;
    param?: unknown;
}
declare interface NavRouterInterface {
    (): NavRouterAttribute;
    (value: RouteInfo): NavRouterAttribute;
}
declare enum NavRouteMode {
    PUSH_WITH_RECREATE = 0,
    PUSH = 1,
    REPLACE = 2,
}
declare class NavRouterAttribute extends CommonMethod<NavRouterAttribute> {
    onStateChange(value: ((parameter: boolean) => void)): NavRouterAttribute;
    mode(value: NavRouteMode): NavRouterAttribute;
}
declare interface SystemBarStyle {
    _SystemBarStyleStub: string;
}
declare interface NavigationCommonTitle {
    main: (string|Resource);
    sub: (string|Resource);
}
declare interface NavigationCustomTitle {
    builder: CustomBuilder;
    height: (TitleHeight|Length);
}
declare enum NavigationMode {
    STACK = 0,
    Stack = 0,
    SPLIT = 1,
    Split = 1,
    AUTO = 2,
    Auto = 2,
}
declare enum NavBarPosition {
    START = 0,
    Start = 0,
    END = 1,
    End = 1,
}
declare enum NavigationTitleMode {
    FREE = 0,
    Free = 0,
    FULL = 1,
    Full = 1,
    MINI = 2,
    Mini = 2,
}
declare interface NavigationMenuItem {
    value: (string|Resource);
    icon?: (string|Resource);
    symbolIcon?: SymbolGlyphModifier;
    isEnabled?: boolean;
    action?: (() => void);
}
declare interface PopInfo {
    info: NavPathInfo;
    result: Object;
}
declare type Callback_PopInfo_Void = ((parameter: PopInfo) => void);
declare class NavPathInfo {
    constructor(name: string, param: unknown, onPop?: ((parameter: PopInfo) => void), isEntry?: boolean);
    name: string;
    param?: unknown;
    onPop?: ((parameter: PopInfo) => void);
    isEntry?: boolean;
}
declare enum LaunchMode {
    STANDARD = 0,
    MOVE_TO_TOP_SINGLETON = 1,
    POP_TO_SINGLETON = 2,
    NEW_INSTANCE = 3,
}
declare interface NavigationOptions {
    launchMode?: LaunchMode;
    animated?: boolean;
}
declare class NavPathStack {
    constructor();
    pushPath(info: NavPathInfo, animated?: boolean): void;
    pushPath(info: NavPathInfo, options?: NavigationOptions): void;
    pushDestination(info: NavPathInfo, animated?: boolean): Promise<void>;
    pushDestination(info: NavPathInfo, options?: NavigationOptions): Promise<void>;
    pushPathByName(name: string, param: unknown, animated?: boolean): void;
    pushPathByName(name: string, param: Object, onPop: ((parameter: PopInfo) => void), animated?: boolean): void;
    pushDestinationByName(name: string, param: Object, animated?: boolean): Promise<void>;
    pushDestinationByName(name: string, param: Object, onPop: ((parameter: PopInfo) => void), animated?: boolean): Promise<void>;
    replacePath(info: NavPathInfo, animated?: boolean): void;
    replacePath(info: NavPathInfo, options?: NavigationOptions): void;
    replaceDestination(info: NavPathInfo, options?: NavigationOptions): Promise<void>;
    replacePathByName(name: string, param: Object, animated?: boolean): void;
    removeByIndexes(indexes: number[]): number;
    removeByName(name: string): number;
    removeByNavDestinationId(navDestinationId: string): boolean;
    pop(animated?: boolean): NavPathInfo | undefined;
    pop(result: Object, animated?: boolean): NavPathInfo | undefined;
    popToName(name: string, animated?: boolean): number;
    popToName(name: string, result: Object, animated?: boolean): number;
    popToIndex(index: number, animated?: boolean): void;
    popToIndex(index: number, result: Object, animated?: boolean): void;
    moveToTop(name: string, animated?: boolean): number;
    moveIndexToTop(index: number, animated?: boolean): void;
    clear(animated?: boolean): void;
    getAllPathName(): string[];
    getParamByIndex(index: number): unknown | undefined;
    getParamByName(name: string): unknown[];
    getIndexByName(name: string): number[];
    getParent(): NavPathStack | undefined;
    size(): number;
    disableAnimation(value: boolean): void;
    setInterception(interception: NavigationInterception): void;
}
declare type NavBar = string;
declare type InterceptionShowCallback = ((from: (NavDestinationContext|NavBar), to: (NavDestinationContext|NavBar), operation: NavigationOperation, isAnimated: boolean) => void);
declare type InterceptionModeCallback = ((mode: NavigationMode) => void);
declare interface NavigationInterception {
    willShow?: InterceptionShowCallback;
    didShow?: InterceptionShowCallback;
    modeChange?: InterceptionModeCallback;
}
declare interface NavigationInterface {
    (): NavigationAttribute;
    (pathInfos: NavPathStack): NavigationAttribute;
}
declare enum ToolbarItemStatus {
    NORMAL = 0,
    DISABLED = 1,
    ACTIVE = 2,
}
declare enum NavigationOperation {
    PUSH = 1,
    POP = 2,
    REPLACE = 3,
}
declare interface ToolbarItem {
    value: ResourceStr;
    icon?: ResourceStr;
    symbolIcon?: SymbolGlyphModifier;
    action?: (() => void);
    status?: ToolbarItemStatus;
    activeIcon?: ResourceStr;
    activeSymbolIcon?: SymbolGlyphModifier;
}
declare interface NavigationTitleOptions {
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    barStyle?: BarStyle;
    paddingStart?: LengthMetrics;
    paddingEnd?: LengthMetrics;
    mainTitleModifier?: TextModifier;
    subTitleModifier?: TextModifier;
    enableHoverMode?: boolean;
}
declare enum BarStyle {
    STANDARD = 0,
    STACK = 1,
    SAFE_AREA_PADDING = 2,
}
declare interface NavigationToolbarOptions {
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    barStyle?: BarStyle;
}
declare type Tuple_Dimension_Dimension = [ Dimension, Dimension ]
declare type Callback_NavigationTitleMode_Void = ((titleMode: NavigationTitleMode) => void);
declare type Callback_NavigationMode_Void = ((mode: NavigationMode) => void);
declare type Callback_String_Unknown_Void = ((name: string, param: unknown) => void);
declare type Type_NavigationAttribute_customNavContentTransition_delegate = ((from: NavContentInfo, to: NavContentInfo, operation: NavigationOperation) => NavigationAnimatedTransition | undefined);
declare class NavigationAttribute extends CommonMethod<NavigationAttribute> {
    navBarWidth(value: Length): NavigationAttribute;
    navBarPosition(value: NavBarPosition): NavigationAttribute;
    navBarWidthRange(value: [ Dimension, Dimension ]): NavigationAttribute;
    minContentWidth(value: Dimension): NavigationAttribute;
    mode(value: NavigationMode): NavigationAttribute;
    backButtonIcon(value: (string|PixelMap|Resource|SymbolGlyphModifier)): NavigationAttribute;
    hideNavBar(value: boolean): NavigationAttribute;
    subTitle(value: string): NavigationAttribute;
    hideTitleBar(value: boolean): NavigationAttribute;
    hideBackButton(value: boolean): NavigationAttribute;
    titleMode(value: NavigationTitleMode): NavigationAttribute;
    menus(value: (NavigationMenuItem[]|CustomBuilder)): NavigationAttribute;
    toolBar(value: (Object|CustomBuilder)): NavigationAttribute;
    hideToolBar(value: boolean): NavigationAttribute;
    onTitleModeChange(value: ((titleMode: NavigationTitleMode) => void)): NavigationAttribute;
    onNavBarStateChange(value: ((parameter: boolean) => void)): NavigationAttribute;
    onNavigationModeChange(value: ((mode: NavigationMode) => void)): NavigationAttribute;
    navDestination(value: ((name: string, param: unknown) => void)): NavigationAttribute;
    customNavContentTransition(value: ((from: NavContentInfo, to: NavContentInfo, operation: NavigationOperation) => NavigationAnimatedTransition | undefined)): NavigationAttribute;
    systemBarStyle(value: SystemBarStyle | undefined): NavigationAttribute;
    recoverable(value: boolean | undefined): NavigationAttribute;
    enableDragBar(value: boolean | undefined): NavigationAttribute;
    title(value: (ResourceStr|CustomBuilder|NavigationCommonTitle|NavigationCustomTitle), options?: NavigationTitleOptions): NavigationAttribute;
    hideTitleBar(hide: boolean, animated: boolean): NavigationAttribute;
    toolbarConfiguration(value: (ToolbarItem[]|CustomBuilder), options?: NavigationToolbarOptions): NavigationAttribute;
    hideToolBar(hide: boolean, animated: boolean): NavigationAttribute;
    ignoreLayoutSafeArea(types?: LayoutSafeAreaType[], edges?: LayoutSafeAreaEdge[]): NavigationAttribute;
}
declare type Callback_NavigationTransitionProxy_Void = ((transitionProxy: NavigationTransitionProxy) => void);
declare interface NavigationAnimatedTransition {
    onTransitionEnd?: ((parameter: boolean) => void);
    timeout?: number;
    isInteractive?: boolean;
    transition: ((transitionProxy: NavigationTransitionProxy) => void);
}
declare interface NavigationTransitionProxy {
    from: NavContentInfo;
    to: NavContentInfo;
    isInteractive?: boolean;
    finishTransition(): void;
    cancelTransition?(): void;
    updateTransition?(progress: number): void;
}
declare interface NavContentInfo {
    name?: string;
    index: number;
    mode?: NavDestinationMode;
    param?: Object;
    navDestinationId?: string;
}
declare enum NavigationType {
    PUSH = 0,
    Push = 0,
    BACK = 1,
    Back = 1,
    REPLACE = 2,
    Replace = 2,
}
declare type Literal_String_target_NavigationType_type = { target: string, type?: NavigationType }
declare interface NavigatorInterface {
    (value?: { target: string, type?: NavigationType }): NavigatorAttribute;
    (): NavigatorAttribute;
}
declare class NavigatorAttribute extends CommonMethod<NavigatorAttribute> {
    active(value: boolean): NavigatorAttribute;
    type(value: NavigationType): NavigatorAttribute;
    target(value: string): NavigatorAttribute;
    params(value: Object): NavigatorAttribute;
}
declare interface NodeContainerInterface {
    (controller: NodeController): NodeContainerAttribute;
}
declare class NodeContainerAttribute extends CommonMethod<NodeContainerAttribute> {
}
declare enum RouteType {
    NONE = 0,
    None = 0,
    PUSH = 1,
    Push = 1,
    POP = 2,
    Pop = 2,
}
declare enum SlideEffect {
    LEFT = 0,
    Left = 0,
    RIGHT = 1,
    Right = 1,
    TOP = 2,
    Top = 2,
    BOTTOM = 3,
    Bottom = 3,
    START = 5,
    END = 6,
}
declare class CommonTransition<T> {
    constructor();
    slide(value: SlideEffect): T;
    translate(value: TranslateOptions): T;
    scale(value: ScaleOptions): T;
    opacity(value: number): T;
}
declare interface PageTransitionOptions {
    type?: RouteType;
    duration?: number;
    curve?: (Curve|string|ICurve);
    delay?: number;
}
declare type PageTransitionCallback = ((type: RouteType, progress: number) => void);
declare interface PageTransitionEnterInterface extends CommonTransition<PageTransitionEnterInterface> {
    onEnter(event: PageTransitionCallback): PageTransitionEnterInterface;
    (value: PageTransitionOptions): PageTransitionEnterInterface;
}
declare interface PageTransitionExitInterface extends CommonTransition<PageTransitionExitInterface> {
    onExit(event: PageTransitionCallback): PageTransitionExitInterface;
    (value: PageTransitionOptions): PageTransitionExitInterface;
}
declare enum PanelMode {
    MINI = 0,
    Mini = 0,
    HALF = 1,
    Half = 1,
    FULL = 2,
    Full = 2,
}
declare enum PanelType {
    MINIBAR = 0,
    Minibar = 0,
    FOLDABLE = 1,
    Foldable = 1,
    TEMPORARY = 2,
    Temporary = 2,
    CUSTOM = 3,
}
declare enum PanelHeight {
    WRAP_CONTENT = "wrapContent",
}
declare interface PanelInterface {
    (show: boolean): PanelAttribute;
}
declare type Callback_Number_Number_PanelMode_Void = ((width: number, height: number, mode: PanelMode) => void);
declare type Callback_PanelMode_Void = ((mode: PanelMode) => void);
declare class PanelAttribute extends CommonMethod<PanelAttribute> {
    mode(value: PanelMode): PanelAttribute;
    type(value: PanelType): PanelAttribute;
    dragBar(value: boolean): PanelAttribute;
    customHeight(value: (Dimension|PanelHeight)): PanelAttribute;
    fullHeight(value: (number|string)): PanelAttribute;
    halfHeight(value: (number|string)): PanelAttribute;
    miniHeight(value: (number|string)): PanelAttribute;
    show(value: boolean): PanelAttribute;
    backgroundMask(value: ResourceColor): PanelAttribute;
    showCloseIcon(value: boolean): PanelAttribute;
    onChange(value: ((width: number, height: number, mode: PanelMode) => void)): PanelAttribute;
    onHeightChange(value: ((index: number) => void)): PanelAttribute;
    _onChangeEvent_mode(callback_: ((mode: PanelMode) => void)): void;
}
declare type ParticleTuple<T1,T2> = [ T1, T2 ]
declare interface VelocityOptions {
    speed: ParticleTuple<number,number>;
    angle: ParticleTuple<number,number>;
}
declare interface PointParticleParameters {
    radius: VP;
}
declare interface ImageParticleParameters {
    src: ResourceStr;
    size: ParticleTuple<Dimension,Dimension>;
    objectFit?: ImageFit;
}
declare interface ParticleConfigs {
}
declare interface EmitterProperty {
    stub: string;
}
declare interface EmitterParticleOptions<PARTICLE extends ParticleType> {
    type: PARTICLE;
    config: string;
    count: number;
    lifetime?: number;
    lifetimeRange?: number;
}
declare interface ParticlePropertyUpdaterConfigs<T> {
}
declare interface ParticleUpdaterOptions<TYPE,UPDATER extends ParticleUpdater> {
    type: UPDATER;
    config: string;
}
declare interface ParticleColorOptions {
    r: ParticleTuple<number,number>;
    g: ParticleTuple<number,number>;
    b: ParticleTuple<number,number>;
    a: ParticleTuple<number,number>;
}
declare interface ParticleColorUpdaterOptions<UPDATER extends ParticleUpdater> {
    type: UPDATER;
    config: string;
}
declare interface ParticleColorPropertyUpdaterConfigs {
}
declare interface ParticlePropertyAnimation<T> {
    from: T;
    to: T;
    startMillis: number;
    endMillis: number;
    curve?: (Curve|ICurve);
}
declare enum ParticleType {
    POINT = "point",
    IMAGE = "image",
}
declare enum ParticleEmitterShape {
    RECTANGLE = "rectangle",
    CIRCLE = "circle",
    ELLIPSE = "ellipse",
}
declare enum DistributionType {
    UNIFORM = 0,
    GAUSSIAN = 1,
}
declare enum ParticleUpdater {
    NONE = "none",
    RANDOM = "random",
    CURVE = "curve",
}
declare interface SizeT {
    _SizeTStub: string;
}
declare interface PositionT {
    _PositionTStub: string;
}
declare enum DisturbanceFieldShape {
    RECT = 0,
    CIRCLE = 1,
    ELLIPSE = 2,
}
declare enum PasteIconStyle {
    LINES = 0,
}
declare enum PasteDescription {
    PASTE = 0,
}
declare interface PasteButtonOptions {
    icon?: PasteIconStyle;
    text?: PasteDescription;
    buttonType?: ButtonType;
}
declare enum PasteButtonOnClickResult {
    SUCCESS = 0,
    TEMPORARY_AUTHORIZATION_FAILED = 1,
}
declare interface PasteButtonInterface {
    (): PasteButtonAttribute;
    (options: PasteButtonOptions): PasteButtonAttribute;
}
declare type Callback_ClickEvent_PasteButtonOnClickResult_Void = ((event: ClickEvent, result: PasteButtonOnClickResult) => void);
declare class PasteButtonAttribute extends SecurityComponentMethod<PasteButtonAttribute> {
    onClick(value: ((event: ClickEvent, result: PasteButtonOnClickResult) => void)): PasteButtonAttribute;
}
declare interface PathOptions {
    width?: (number|string);
    height?: (number|string);
    commands?: string;
}
declare interface PathInterface {
    new(options?: PathOptions): PathAttribute;
    (options?: PathOptions): PathAttribute;
}
declare class PathAttribute extends CommonShapeMethod<PathAttribute> {
    commands(value: string): PathAttribute;
}
declare enum PatternLockChallengeResult {
    CORRECT = 1,
    WRONG = 2,
}
declare interface CircleStyleOptions {
    color?: ResourceColor;
    radius?: LengthMetrics;
    enableWaveEffect?: boolean;
}
declare class PatternLockController {
    constructor();
    reset(): void;
    setChallengeResult(result: PatternLockChallengeResult): void;
}
declare interface PatternLockInterface {
    (controller?: PatternLockController): PatternLockAttribute;
}
declare type Callback_Array_Number_Void = ((input: number[]) => void);
declare class PatternLockAttribute extends CommonMethod<PatternLockAttribute> {
    sideLength(value: Length): PatternLockAttribute;
    circleRadius(value: Length): PatternLockAttribute;
    backgroundColor(value: ResourceColor): PatternLockAttribute;
    regularColor(value: ResourceColor): PatternLockAttribute;
    selectedColor(value: ResourceColor): PatternLockAttribute;
    activeColor(value: ResourceColor): PatternLockAttribute;
    pathColor(value: ResourceColor): PatternLockAttribute;
    pathStrokeWidth(value: (number|string)): PatternLockAttribute;
    onPatternComplete(value: ((input: number[]) => void)): PatternLockAttribute;
    autoReset(value: boolean): PatternLockAttribute;
    onDotConnect(value: ((index: number) => void)): PatternLockAttribute;
    activateCircleStyle(value: CircleStyleOptions | undefined): PatternLockAttribute;
}
declare interface PluginComponentTemplate {
    source: string;
    bundleName: string;
}
declare interface PluginComponentOptions {
    template: PluginComponentTemplate;
    data: string;
}
declare interface PluginErrorData {
    errcode: number;
    msg: string;
}
declare type PluginErrorCallback = ((info: PluginErrorData) => void);
declare interface PluginComponentInterface {
    (options: PluginComponentOptions): PluginComponentAttribute;
}
declare class PluginComponentAttribute extends CommonMethod<PluginComponentAttribute> {
    onComplete(value: VoidCallback): PluginComponentAttribute;
    onError(value: PluginErrorCallback): PluginComponentAttribute;
}
declare interface PolygonOptions {
    width?: (string|number);
    height?: (string|number);
}
declare interface PolygonInterface {
    new(options?: PolygonOptions): PolygonAttribute;
    (options?: PolygonOptions): PolygonAttribute;
}
declare class PolygonAttribute extends CommonShapeMethod<PolygonAttribute> {
    points(value: Point[]): PolygonAttribute;
}
declare interface PolylineOptions {
    width?: (string|number);
    height?: (string|number);
}
declare interface PolylineInterface {
    new(options?: PolylineOptions): PolylineAttribute;
    (options?: PolylineOptions): PolylineAttribute;
}
declare class PolylineAttribute extends CommonShapeMethod<PolylineAttribute> {
    points(value: Point[]): PolylineAttribute;
}
declare interface ProgressOptions {
    value: number;
    total?: number;
    style?: ProgressStyle;
    type?: ProgressType;
}
declare enum ProgressType {
    LINEAR = 0,
    Linear = 0,
    RING = 1,
    Ring = 1,
    ECLIPSE = 2,
    Eclipse = 2,
    SCALE_RING = 3,
    ScaleRing = 3,
    CAPSULE = 4,
    Capsule = 4,
}
declare enum ProgressStatus {
    LOADING = 0,
    PROGRESSING = 1,
}
declare interface ProgressStyleOptions extends CommonProgressStyleOptions {
    strokeWidth?: Length;
    scaleCount?: number;
    scaleWidth?: Length;
}
declare interface CommonProgressStyleOptions {
    enableSmoothEffect?: boolean;
}
declare interface ScanEffectOptions {
    enableScanEffect?: boolean;
}
declare interface EclipseStyleOptions extends CommonProgressStyleOptions {
}
declare interface ScaleRingStyleOptions extends CommonProgressStyleOptions {
    strokeWidth?: Length;
    scaleWidth?: Length;
    scaleCount?: number;
}
declare interface RingStyleOptions extends ScanEffectOptions, CommonProgressStyleOptions {
    strokeWidth?: Length;
    shadow?: boolean;
    status?: ProgressStatus;
}
declare interface LinearStyleOptions extends ScanEffectOptions, CommonProgressStyleOptions {
    strokeWidth?: Length;
    strokeRadius?: (PX|VP|LPX|Resource);
}
declare interface CapsuleStyleOptions extends ScanEffectOptions, CommonProgressStyleOptions {
    borderColor?: ResourceColor;
    borderWidth?: Length;
    content?: string;
    font?: Font;
    fontColor?: ResourceColor;
    showDefaultPercentage?: boolean;
}
declare enum ProgressStyle {
    LINEAR = 0,
    Linear = 0,
    RING = 1,
    Ring = 1,
    ECLIPSE = 2,
    Eclipse = 2,
    SCALE_RING = 3,
    ScaleRing = 3,
    CAPSULE = 4,
    Capsule = 4,
}
declare interface ProgressStyleMap {
}
declare interface ProgressInterface {
    (options: ProgressOptions): ProgressAttribute;
}
declare class ProgressAttribute extends CommonMethod<ProgressAttribute> {
    value(value: number): ProgressAttribute;
    color(value: (ResourceColor|LinearGradient)): ProgressAttribute;
    style(value: (LinearStyleOptions|RingStyleOptions|CapsuleStyleOptions|ProgressStyleOptions)): ProgressAttribute;
    privacySensitive(value: boolean | undefined): ProgressAttribute;
    contentModifier(value: ContentModifier<ProgressConfiguration>): ProgressAttribute;
}
declare interface ProgressConfiguration extends CommonConfiguration<ProgressConfiguration> {
    value: number;
    total: number;
}
declare interface QRCodeInterface {
    (value: string): QRCodeAttribute;
}
declare class QRCodeAttribute extends CommonMethod<QRCodeAttribute> {
    color(value: ResourceColor): QRCodeAttribute;
    backgroundColor(value: ResourceColor): QRCodeAttribute;
    contentOpacity(value: (number|Resource)): QRCodeAttribute;
}
declare enum RadioIndicatorType {
    TICK = 0,
    DOT = 1,
    CUSTOM = 2,
}
declare interface RadioOptions {
    group: string;
    value: string;
    indicatorType?: RadioIndicatorType;
    indicatorBuilder?: CustomBuilder;
}
declare interface RadioStyle {
    checkedBackgroundColor?: ResourceColor;
    uncheckedBorderColor?: ResourceColor;
    indicatorColor?: ResourceColor;
}
declare interface RadioInterface {
    (options: RadioOptions): RadioAttribute;
}
declare class RadioAttribute extends CommonMethod<RadioAttribute> {
    checked(value: boolean): RadioAttribute;
    onChange(value: ((parameter: boolean) => void)): RadioAttribute;
    radioStyle(value: RadioStyle): RadioAttribute;
    contentModifier(value: ContentModifier<RadioConfiguration>): RadioAttribute;
    _onChangeEvent_checked(callback_: ((parameter: boolean) => void)): void;
}
declare interface RadioConfiguration extends CommonConfiguration<RadioConfiguration> {
    value: string;
    checked: boolean;
    triggerChange: ((parameter: boolean) => void);
}
declare interface RatingOptions {
    rating: number;
    indicator?: boolean;
}
declare interface StarStyleOptions {
    backgroundUri: string;
    foregroundUri: string;
    secondaryUri?: string;
}
declare interface RatingInterface {
    (options?: RatingOptions): RatingAttribute;
}
declare interface RatingConfiguration extends CommonConfiguration<RatingConfiguration> {
    rating: number;
    indicator: boolean;
    stars: number;
    stepSize: number;
    triggerChange: ((index: number) => void);
}
declare class RatingAttribute extends CommonMethod<RatingAttribute> {
    stars(value: number): RatingAttribute;
    stepSize(value: number): RatingAttribute;
    starStyle(value: StarStyleOptions): RatingAttribute;
    onChange(value: ((index: number) => void)): RatingAttribute;
    contentModifier(value: ContentModifier<RatingConfiguration>): RatingAttribute;
    _onChangeEvent_rating(callback_: ((index: number) => void)): void;
}
declare interface RectOptions {
    width?: (number|string);
    height?: (number|string);
    radius?: (number|string|(number|string)[]);
}
declare interface RoundedRectOptions {
    width?: (number|string);
    height?: (number|string);
    radiusWidth?: (number|string);
    radiusHeight?: (number|string);
}
declare interface RectInterface {
    new(options?: (RectOptions|RoundedRectOptions)): RectAttribute;
    (options?: (RectOptions|RoundedRectOptions)): RectAttribute;
}
declare class RectAttribute extends CommonShapeMethod<RectAttribute> {
    radiusWidth(value: (number|string)): RectAttribute;
    radiusHeight(value: (number|string)): RectAttribute;
    radius(value: (number|string|(number|string)[])): RectAttribute;
}
declare enum RefreshStatus {
    INACTIVE = 0,
    Inactive = 0,
    DRAG = 1,
    Drag = 1,
    OVER_DRAG = 2,
    OverDrag = 2,
    REFRESH = 3,
    Refresh = 3,
    DONE = 4,
    Done = 4,
}
declare interface RefreshOptions {
    refreshing: boolean;
    offset?: (number|string);
    friction?: (number|string);
    promptText?: ResourceStr;
    builder?: CustomBuilder;
    refreshingContent?: ComponentContent;
}
declare interface RefreshInterface {
    (value: RefreshOptions): RefreshAttribute;
}
declare type Callback_RefreshStatus_Void = ((state: RefreshStatus) => void);
declare class RefreshAttribute extends CommonMethod<RefreshAttribute> {
    onStateChange(value: ((state: RefreshStatus) => void)): RefreshAttribute;
    onRefreshing(value: (() => void)): RefreshAttribute;
    refreshOffset(value: number): RefreshAttribute;
    pullToRefresh(value: boolean): RefreshAttribute;
    onOffsetChange(value: ((index: number) => void)): RefreshAttribute;
    pullDownRatio(value: number | undefined): RefreshAttribute;
    _onChangeEvent_refreshing(callback_: ((parameter: boolean) => void)): void;
}
declare interface RelativeContainerInterface {
    (): RelativeContainerAttribute;
}
declare interface GuideLinePosition {
    start?: Dimension;
    end?: Dimension;
}
declare interface GuideLineStyle {
    id: string;
    direction: Axis;
    position: GuideLinePosition;
}
declare enum BarrierDirection {
    LEFT = 0,
    RIGHT = 1,
    TOP = 2,
    BOTTOM = 3,
}
declare enum LocalizedBarrierDirection {
    START = 0,
    END = 1,
    TOP = 2,
    BOTTOM = 3,
}
declare interface BarrierStyle {
    id: string;
    direction: BarrierDirection;
    referencedId: string[];
}
declare interface LocalizedBarrierStyle {
    id: string;
    localizedDirection: LocalizedBarrierDirection;
    referencedId: string[];
}
declare class RelativeContainerAttribute extends CommonMethod<RelativeContainerAttribute> {
    guideLine(value: GuideLineStyle[]): RelativeContainerAttribute;
    barrier(value: BarrierStyle[]): RelativeContainerAttribute;
    barrier(value: LocalizedBarrierStyle[]): RelativeContainerAttribute;
}
declare interface VirtualScrollOptions {
    totalCount?: number;
}
declare interface TemplateOptions {
    cachedCount?: number;
}
declare enum RichEditorDeleteDirection {
    BACKWARD = 0,
    FORWARD = 1,
}
declare enum RichEditorSpanType {
    TEXT = 0,
    IMAGE = 1,
    MIXED = 2,
    BUILDER = 3,
}
declare enum RichEditorResponseType {
    RIGHT_CLICK = 0,
    LONG_PRESS = 1,
    SELECT = 2,
}
declare interface RichEditorSpanPosition {
    spanIndex: number;
    spanRange: [ number, number ];
}
declare interface RichEditorTextStyle {
    fontColor?: ResourceColor;
    fontSize?: (Length|number);
    fontStyle?: FontStyle;
    fontWeight?: (number|FontWeight|string);
    fontFamily?: ResourceStr;
    decoration?: DecorationStyleInterface;
    textShadow?: (ShadowOptions|ShadowOptions[]);
    letterSpacing?: (number|string);
    lineHeight?: (number|string|Resource);
    fontFeature?: string;
}
declare interface LeadingMarginPlaceholder {
    pixelMap: PixelMap;
    size: [ Dimension, Dimension ];
}
declare interface RichEditorParagraphStyle {
    textAlign?: TextAlign;
    leadingMargin?: (Dimension|LeadingMarginPlaceholder);
    wordBreak?: WordBreak;
    lineBreakStrategy?: LineBreakStrategy;
}
declare interface PasteEvent {
    preventDefault?: (() => void);
}
declare interface RichEditorTextSpan {
    spanPosition: RichEditorSpanPosition;
    value: string;
    textStyle?: RichEditorTextStyle;
}
declare interface RichEditorLayoutStyle {
    margin?: (Dimension|Margin);
    borderRadius?: (Dimension|BorderRadiuses);
}
declare interface RichEditorImageSpanStyle {
    size?: [ Dimension, Dimension ];
    verticalAlign?: ImageSpanAlignment;
    objectFit?: ImageFit;
    layoutStyle?: RichEditorLayoutStyle;
}
declare interface RichEditorSymbolSpanStyle {
    fontSize?: (number|string|Resource);
    fontColor?: ResourceColor[];
    fontWeight?: (number|FontWeight|string);
    effectStrategy?: SymbolEffectStrategy;
    renderingStrategy?: SymbolRenderingStrategy;
}
declare interface RichEditorTextStyleResult {
    fontColor: ResourceColor;
    fontSize: number;
    fontStyle: FontStyle;
    fontWeight: number;
    fontFamily: string;
    decoration: DecorationStyleResult;
    textShadow?: ShadowOptions[];
    letterSpacing?: number;
    lineHeight?: number;
    fontFeature?: string;
}
declare interface RichEditorParagraphResult {
    style: RichEditorParagraphStyle;
    range: [ number, number ];
}
declare interface RichEditorSymbolSpanStyleResult {
    fontSize: (number|string|Resource);
    fontColor: ResourceColor[];
    fontWeight: (number|FontWeight|string);
    effectStrategy: SymbolEffectStrategy;
    renderingStrategy: SymbolRenderingStrategy;
}
declare interface RichEditorTextSpanResult {
    spanPosition: RichEditorSpanPosition;
    value: string;
    textStyle: RichEditorTextStyleResult;
    offsetInSpan: [ number, number ];
    symbolSpanStyle?: RichEditorSymbolSpanStyle;
    valueResource?: Resource;
    paragraphStyle?: RichEditorParagraphStyle;
    previewText?: string;
}
declare interface RichEditorImageSpanStyleResult {
    size: [ number, number ];
    verticalAlign: ImageSpanAlignment;
    objectFit: ImageFit;
    layoutStyle?: RichEditorLayoutStyle;
}
declare interface RichEditorImageSpanResult {
    spanPosition: RichEditorSpanPosition;
    valuePixelMap?: PixelMap;
    valueResourceStr?: ResourceStr;
    imageStyle: RichEditorImageSpanStyleResult;
    offsetInSpan: [ number, number ];
}
declare interface RichEditorImageSpan {
    spanPosition: RichEditorSpanPosition;
    value: (PixelMap|ResourceStr);
    imageStyle?: RichEditorImageSpanStyle;
}
declare interface RichEditorRange {
    start?: number;
    end?: number;
}
declare interface RichEditorGesture {
    onClick?: ((event: ClickEvent) => void);
    onLongPress?: ((event: GestureEvent) => void);
}
declare interface RichEditorTextSpanOptions {
    offset?: number;
    style?: RichEditorTextStyle;
    paragraphStyle?: RichEditorParagraphStyle;
    gesture?: RichEditorGesture;
}
declare interface KeyboardOptions {
    supportAvoidance?: boolean;
}
declare interface RichEditorImageSpanOptions {
    offset?: number;
    imageStyle?: RichEditorImageSpanStyle;
    gesture?: RichEditorGesture;
}
declare interface RichEditorBuilderSpanOptions {
    offset?: number;
}
declare interface PlaceholderStyle {
    font?: Font;
    fontColor?: ResourceColor;
}
declare interface RichEditorSpanStyleOptions extends RichEditorRange {
}
declare interface RichEditorParagraphStyleOptions extends RichEditorRange {
    style: RichEditorParagraphStyle;
}
declare interface RichEditorUpdateTextSpanStyleOptions extends RichEditorSpanStyleOptions {
    textStyle: RichEditorTextStyle;
}
declare interface RichEditorUpdateImageSpanStyleOptions extends RichEditorSpanStyleOptions {
    imageStyle: RichEditorImageSpanStyle;
}
declare interface RichEditorUpdateSymbolSpanStyleOptions extends RichEditorSpanStyleOptions {
    symbolStyle: RichEditorSymbolSpanStyle;
}
declare interface RichEditorSymbolSpanOptions {
    offset?: number;
    style?: RichEditorSymbolSpanStyle;
}
declare interface RichEditorSelection {
    selection: [ number, number ];
    spans: (RichEditorTextSpanResult|RichEditorImageSpanResult)[];
}
declare interface RichEditorInsertValue {
    insertOffset: number;
    insertValue: string;
    previewText?: string;
}
declare interface RichEditorDeleteValue {
    offset: number;
    direction: RichEditorDeleteDirection;
    length: number;
    richEditorDeleteSpans: (RichEditorTextSpanResult|RichEditorImageSpanResult)[];
}
declare interface RichEditorChangeValue {
    rangeBefore: TextRange;
    replacedSpans: RichEditorTextSpanResult[];
    replacedImageSpans: RichEditorImageSpanResult[];
    replacedSymbolSpans: RichEditorTextSpanResult[];
}
declare interface RichEditorOptions {
    controller: RichEditorController;
}
declare interface RichEditorStyledStringOptions {
    controller: RichEditorStyledStringController;
}
declare interface SelectionMenuOptions {
    onAppear?: MenuOnAppearCallback;
    onDisappear?: (() => void);
    menuType?: MenuType;
}
declare class RichEditorBaseController implements TextEditControllerEx {
    getCaretOffset(): number;
    setCaretOffset(offset: number): boolean;
    closeSelectionMenu(): void;
    getTypingStyle(): RichEditorTextStyle;
    setTypingStyle(value: RichEditorTextStyle): void;
    setSelection(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void;
    isEditing(): boolean;
    stopEditing(): void;
    getLayoutManager(): LayoutManager;
    getPreviewText(): PreviewText;
}
declare class RichEditorController extends RichEditorBaseController {
    addTextSpan(value: string, options?: RichEditorTextSpanOptions): number;
    addImageSpan(value: (PixelMap|ResourceStr), options?: RichEditorImageSpanOptions): number;
    addBuilderSpan(value: CustomBuilder, options?: RichEditorBuilderSpanOptions): number;
    addSymbolSpan(value: Resource, options?: RichEditorSymbolSpanOptions): number;
    updateSpanStyle(value: (RichEditorUpdateTextSpanStyleOptions|RichEditorUpdateImageSpanStyleOptions|RichEditorUpdateSymbolSpanStyleOptions)): void;
    updateParagraphStyle(value: RichEditorParagraphStyleOptions): void;
    deleteSpans(value?: RichEditorRange): void;
    getSpans(value?: RichEditorRange): (RichEditorImageSpanResult|RichEditorTextSpanResult)[];
    getParagraphs(value?: RichEditorRange): RichEditorParagraphResult[];
    getSelection(): RichEditorSelection;
    fromStyledString(value: StyledString): RichEditorSpan[];
    toStyledString(value: RichEditorRange): StyledString;
}
declare type RichEditorSpan = (RichEditorImageSpanResult|RichEditorTextSpanResult);
declare class RichEditorStyledStringController extends RichEditorBaseController implements StyledStringController {
    setStyledString(styledString: StyledString): void;
    getStyledString(): MutableStyledString;
    getSelection(): RichEditorRange;
    onContentChanged(listener: StyledStringChangedListener): void;
}
declare type Callback_RichEditorSelection_Void = ((parameter: RichEditorSelection) => void);
declare type Callback_RichEditorRange_Void = ((parameter: RichEditorRange) => void);
declare type Callback_RichEditorInsertValue_Boolean = ((parameter: RichEditorInsertValue) => boolean);
declare type Callback_RichEditorTextSpanResult_Void = ((parameter: RichEditorTextSpanResult) => void);
declare type Callback_TextRange_Void = ((parameter: TextRange) => void);
declare type Callback_RichEditorDeleteValue_Boolean = ((parameter: RichEditorDeleteValue) => boolean);
declare type Callback_RichEditorChangeValue_Boolean = ((parameter: RichEditorChangeValue) => boolean);
declare type Callback_CutEvent_Void = ((parameter: CutEvent) => void);
declare type Callback_CopyEvent_Void = ((parameter: CopyEvent) => void);
declare class RichEditorAttribute extends CommonMethod<RichEditorAttribute> {
    onReady(value: (() => void)): RichEditorAttribute;
    onSelect(value: ((parameter: RichEditorSelection) => void)): RichEditorAttribute;
    onSelectionChange(value: ((parameter: RichEditorRange) => void)): RichEditorAttribute;
    aboutToIMEInput(value: ((parameter: RichEditorInsertValue) => boolean)): RichEditorAttribute;
    onIMEInputComplete(value: ((parameter: RichEditorTextSpanResult) => void)): RichEditorAttribute;
    onDidIMEInput(value: ((parameter: TextRange) => void)): RichEditorAttribute;
    aboutToDelete(value: ((parameter: RichEditorDeleteValue) => boolean)): RichEditorAttribute;
    onDeleteComplete(value: (() => void)): RichEditorAttribute;
    copyOptions(value: CopyOptions): RichEditorAttribute;
    onPaste(value: PasteEventCallback): RichEditorAttribute;
    enableDataDetector(value: boolean): RichEditorAttribute;
    enablePreviewText(value: boolean): RichEditorAttribute;
    dataDetectorConfig(value: TextDataDetectorConfig): RichEditorAttribute;
    caretColor(value: ResourceColor): RichEditorAttribute;
    selectedBackgroundColor(value: ResourceColor): RichEditorAttribute;
    onEditingChange(value: ((parameter: boolean) => void)): RichEditorAttribute;
    enterKeyType(value: EnterKeyType): RichEditorAttribute;
    onSubmit(value: SubmitCallback): RichEditorAttribute;
    onWillChange(value: ((parameter: RichEditorChangeValue) => boolean)): RichEditorAttribute;
    onDidChange(value: OnDidChangeCallback): RichEditorAttribute;
    onCut(value: ((parameter: CutEvent) => void)): RichEditorAttribute;
    onCopy(value: ((parameter: CopyEvent) => void)): RichEditorAttribute;
    editMenuOptions(value: EditMenuOptions): RichEditorAttribute;
    enableKeyboardOnFocus(value: boolean): RichEditorAttribute;
    enableHapticFeedback(value: boolean): RichEditorAttribute;
    barState(value: BarState): RichEditorAttribute;
    bindSelectionMenu(spanType: RichEditorSpanType, content: CustomBuilder, responseType: (ResponseType|RichEditorResponseType), options?: SelectionMenuOptions): RichEditorAttribute;
    customKeyboard(value: CustomBuilder, options?: KeyboardOptions): RichEditorAttribute;
    placeholder(value: ResourceStr, style?: PlaceholderStyle): RichEditorAttribute;
}
declare interface CutEvent {
    preventDefault?: (() => void);
}
declare interface CopyEvent {
    preventDefault?: (() => void);
}
declare type SubmitCallback = ((enterKey: EnterKeyType, event: SubmitEvent) => void);
declare type MenuOnAppearCallback = ((start: number, end: number) => void);
declare type PasteEventCallback = ((event?: PasteEvent) => void);
declare interface RichEditorInterface {
    (value: RichEditorOptions): RichEditorAttribute;
    (options: RichEditorStyledStringOptions): RichEditorAttribute;
}
declare interface RichTextInterface {
    (content: string): RichTextAttribute;
}
declare class RichTextAttribute extends CommonMethod<RichTextAttribute> {
    onStart(value: (() => void)): RichTextAttribute;
    onComplete(value: (() => void)): RichTextAttribute;
}
declare interface RootSceneSession {
}
declare interface RootSceneInterface {
    (session: RootSceneSession): RootSceneAttribute;
}
declare class RootSceneAttribute extends CommonMethod<RootSceneAttribute> {
}
declare interface RowOptions {
    space?: (string|number);
}
declare interface RowInterface {
    (options?: RowOptions): RowAttribute;
}
declare class RowAttribute extends CommonMethod<RowAttribute> {
    alignItems(value: VerticalAlign): RowAttribute;
    justifyContent(value: FlexAlign): RowAttribute;
    pointLight(value: PointLightStyle): RowAttribute;
    reverse(value: boolean | undefined): RowAttribute;
}
declare interface RowSplitInterface {
    (): RowSplitAttribute;
}
declare class RowSplitAttribute extends CommonMethod<RowSplitAttribute> {
    resizeable(value: boolean): RowSplitAttribute;
}
declare enum SaveIconStyle {
    FULL_FILLED = 0,
    LINES = 1,
    PICTURE = 2,
}
declare enum SaveDescription {
    DOWNLOAD = 0,
    DOWNLOAD_FILE = 1,
    SAVE = 2,
    SAVE_IMAGE = 3,
    SAVE_FILE = 4,
    DOWNLOAD_AND_SHARE = 5,
    RECEIVE = 6,
    CONTINUE_TO_RECEIVE = 7,
    SAVE_TO_GALLERY = 8,
    EXPORT_TO_GALLERY = 9,
    QUICK_SAVE_TO_GALLERY = 10,
    RESAVE_TO_GALLERY = 11,
}
declare interface SaveButtonOptions {
    icon?: SaveIconStyle;
    text?: SaveDescription;
    buttonType?: ButtonType;
}
declare enum SaveButtonOnClickResult {
    SUCCESS = 0,
    TEMPORARY_AUTHORIZATION_FAILED = 1,
}
declare interface SaveButtonInterface {
    (): SaveButtonAttribute;
    (options: SaveButtonOptions): SaveButtonAttribute;
}
declare type Callback_ClickEvent_SaveButtonOnClickResult_Void = ((event: ClickEvent, result: SaveButtonOnClickResult) => void);
declare class SaveButtonAttribute extends SecurityComponentMethod<SaveButtonAttribute> {
    onClick(value: ((event: ClickEvent, result: SaveButtonOnClickResult) => void)): SaveButtonAttribute;
}
declare interface ScreenInterface {
    (screenId: number): ScreenAttribute;
}
declare class ScreenAttribute extends CommonMethod<ScreenAttribute> {
}
declare enum ScrollDirection {
    VERTICAL = 0,
    Vertical = 0,
    HORIZONTAL = 1,
    Horizontal = 1,
    FREE = 2,
    Free = 2,
    NONE = 3,
    None = 3,
}
declare enum ScrollAlign {
    START = 0,
    CENTER = 1,
    END = 2,
    AUTO = 3,
}
declare interface OffsetResult {
    xOffset: number;
    yOffset: number;
}
declare interface ScrollEdgeOptions {
    velocity?: number;
}
declare interface ScrollToIndexOptions {
    extraOffset?: LengthMetrics;
}
declare interface ScrollAnimationOptions {
    duration?: number;
    curve?: (Curve|ICurve);
    canOverScroll?: boolean;
}
declare interface OffsetOptions {
    xOffset?: Dimension;
    yOffset?: Dimension;
}
declare type Literal_Boolean_next_Axis_direction = { next: boolean, direction?: Axis }
declare class Scroller {
    constructor();
    scrollTo(options: ScrollOptions): void;
    scrollEdge(value: Edge, options?: ScrollEdgeOptions): void;
    fling(velocity: number): void;
    scrollPage(value: ScrollPageOptions): void;
    scrollPage(value: { next: boolean, direction?: Axis }): void;
    currentOffset(): OffsetResult;
    scrollToIndex(value: number, smooth?: boolean, align?: ScrollAlign, options?: ScrollToIndexOptions): void;
    scrollBy(dx: Length, dy: Length): void;
    isAtEnd(): boolean;
    getItemRect(index: number): RectResult;
    getItemIndex(x: number, y: number): number;
}
declare interface ScrollOptions {
    xOffset: (number|string);
    yOffset: (number|string);
    animation?: (ScrollAnimationOptions|boolean);
}
declare interface ScrollPageOptions {
    next: boolean;
    animation?: boolean;
}
declare interface ScrollSnapOptions {
    snapAlign: ScrollSnapAlign;
    snapPagination?: (Dimension|Dimension[]);
    enableSnapToStart?: boolean;
    enableSnapToEnd?: boolean;
}
declare interface ScrollInterface {
    (scroller?: Scroller): ScrollAttribute;
}
declare type OnScrollEdgeCallback = ((side: Edge) => void);
declare interface OnScrollFrameBeginHandlerResult {
    offsetRemain: number;
}
declare type OnScrollFrameBeginCallback = ((offset: number, state: ScrollState) => OnScrollFrameBeginHandlerResult);
declare class ScrollAttribute extends ScrollableCommonMethod<ScrollAttribute> {
    scrollable(value: ScrollDirection): ScrollAttribute;
    onScroll(value: ((first: number, last: number) => void)): ScrollAttribute;
    onWillScroll(value: ScrollOnWillScrollCallback | undefined): ScrollAttribute;
    onDidScroll(value: ScrollOnScrollCallback): ScrollAttribute;
    onScrollEdge(value: OnScrollEdgeCallback): ScrollAttribute;
    onScrollStart(value: VoidCallback): ScrollAttribute;
    onScrollEnd(value: (() => void)): ScrollAttribute;
    onScrollStop(value: VoidCallback): ScrollAttribute;
    scrollBar(value: BarState): ScrollAttribute;
    scrollBarColor(value: (Color|number|string)): ScrollAttribute;
    scrollBarWidth(value: (number|string)): ScrollAttribute;
    onScrollFrameBegin(value: OnScrollFrameBeginCallback): ScrollAttribute;
    nestedScroll(value: NestedScrollOptions): ScrollAttribute;
    enableScrollInteraction(value: boolean): ScrollAttribute;
    friction(value: (number|Resource)): ScrollAttribute;
    scrollSnap(value: ScrollSnapOptions): ScrollAttribute;
    enablePaging(value: boolean): ScrollAttribute;
    initialOffset(value: OffsetOptions): ScrollAttribute;
    edgeEffect(edgeEffect: EdgeEffect, options?: EdgeEffectOptions): ScrollAttribute;
}
declare type ScrollOnScrollCallback = ((xOffset: number, yOffset: number, scrollState: ScrollState) => void);
declare type ScrollOnWillScrollCallback = ((xOffset: number, yOffset: number, scrollState: ScrollState, scrollSource: ScrollSource) => OffsetResult);
declare enum ScrollBarDirection {
    VERTICAL = 0,
    Vertical = 0,
    HORIZONTAL = 1,
    Horizontal = 1,
}
declare interface ScrollBarOptions {
    scroller: Scroller;
    direction?: ScrollBarDirection;
    state?: BarState;
}
declare interface ScrollBarInterface {
    (value: ScrollBarOptions): ScrollBarAttribute;
}
declare class ScrollBarAttribute extends CommonMethod<ScrollBarAttribute> {
    enableNestedScroll(value: boolean | undefined): ScrollBarAttribute;
}
declare class SearchController extends TextContentControllerBase {
    constructor();
    caretPosition(value: number): void;
    stopEditing(): void;
    setTextSelection(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void;
}
declare enum CancelButtonStyle {
    CONSTANT = 0,
    INVISIBLE = 1,
    INPUT = 2,
}
declare enum SearchType {
    NORMAL = 0,
    NUMBER = 2,
    PHONE_NUMBER = 3,
    EMAIL = 5,
    NUMBER_DECIMAL = 12,
    URL = 13,
}
declare interface SearchOptions {
    value?: string;
    placeholder?: ResourceStr;
    icon?: string;
    controller?: SearchController;
}
declare interface SearchInterface {
    (options?: SearchOptions): SearchAttribute;
}
declare interface IconOptions {
    size?: Length;
    color?: ResourceColor;
    src?: ResourceStr;
}
declare interface SearchButtonOptions {
    fontSize?: Length;
    fontColor?: ResourceColor;
    autoDisable?: boolean;
}
declare interface CancelButtonOptions {
    style?: CancelButtonStyle;
    icon?: IconOptions;
}
declare interface CancelButtonSymbolOptions {
    style?: CancelButtonStyle;
    icon?: SymbolGlyphModifier;
}
declare type SearchSubmitCallback = ((searchContent: string, event?: SubmitEvent) => void);
declare type Callback_InsertValue_Boolean = ((parameter: InsertValue) => boolean);
declare type Callback_InsertValue_Void = ((parameter: InsertValue) => void);
declare type Callback_DeleteValue_Boolean = ((parameter: DeleteValue) => boolean);
declare type Callback_DeleteValue_Void = ((parameter: DeleteValue) => void);
declare class SearchAttribute extends CommonMethod<SearchAttribute> {
    fontColor(value: ResourceColor): SearchAttribute;
    searchIcon(value: (IconOptions|SymbolGlyphModifier)): SearchAttribute;
    cancelButton(value: (CancelButtonOptions|CancelButtonSymbolOptions)): SearchAttribute;
    textIndent(value: Dimension): SearchAttribute;
    onEditChange(value: ((parameter: boolean) => void)): SearchAttribute;
    selectedBackgroundColor(value: ResourceColor): SearchAttribute;
    caretStyle(value: CaretStyle): SearchAttribute;
    placeholderColor(value: ResourceColor): SearchAttribute;
    placeholderFont(value: Font): SearchAttribute;
    textFont(value: Font): SearchAttribute;
    enterKeyType(value: EnterKeyType): SearchAttribute;
    onSubmit(value: ((breakpoints: string) => void)): SearchAttribute;
    onSubmit(value: SearchSubmitCallback): SearchAttribute;
    onChange(value: EditableTextOnChangeCallback): SearchAttribute;
    onTextSelectionChange(value: OnTextSelectionChangeCallback): SearchAttribute;
    onContentScroll(value: OnContentScrollCallback): SearchAttribute;
    onCopy(value: ((breakpoints: string) => void)): SearchAttribute;
    onCut(value: ((breakpoints: string) => void)): SearchAttribute;
    onPaste(value: OnPasteCallback): SearchAttribute;
    copyOption(value: CopyOptions): SearchAttribute;
    maxLength(value: number): SearchAttribute;
    textAlign(value: TextAlign): SearchAttribute;
    enableKeyboardOnFocus(value: boolean): SearchAttribute;
    selectionMenuHidden(value: boolean): SearchAttribute;
    minFontSize(value: (number|string|Resource)): SearchAttribute;
    maxFontSize(value: (number|string|Resource)): SearchAttribute;
    decoration(value: TextDecorationOptions): SearchAttribute;
    letterSpacing(value: (number|string|Resource)): SearchAttribute;
    lineHeight(value: (number|string|Resource)): SearchAttribute;
    type(value: SearchType): SearchAttribute;
    fontFeature(value: string): SearchAttribute;
    onWillInsert(value: ((parameter: InsertValue) => boolean)): SearchAttribute;
    onDidInsert(value: ((parameter: InsertValue) => void)): SearchAttribute;
    onWillDelete(value: ((parameter: DeleteValue) => boolean)): SearchAttribute;
    onDidDelete(value: ((parameter: DeleteValue) => void)): SearchAttribute;
    editMenuOptions(value: EditMenuOptions): SearchAttribute;
    enablePreviewText(value: boolean): SearchAttribute;
    enableHapticFeedback(value: boolean): SearchAttribute;
    searchButton(value: string, option?: SearchButtonOptions): SearchAttribute;
    inputFilter(value: ResourceStr, error?: ((breakpoints: string) => void)): SearchAttribute;
    customKeyboard(value: CustomBuilder, options?: KeyboardOptions): SearchAttribute;
    _onChangeEvent_value(callback_: ((breakpoints: string) => void)): void;
}
declare enum SecurityComponentLayoutDirection {
    HORIZONTAL = 0,
    VERTICAL = 1,
}
declare class SecurityComponentMethod<T> {
    iconSize(value: Dimension): T;
    layoutDirection(value: SecurityComponentLayoutDirection): T;
    position(value: Position): T;
    markAnchor(value: Position): T;
    offset(value: (Position|Edges|LocalizedEdges)): T;
    fontSize(value: Dimension): T;
    fontStyle(value: FontStyle): T;
    fontWeight(value: (number|FontWeight|string)): T;
    fontFamily(value: (string|Resource)): T;
    fontColor(value: ResourceColor): T;
    iconColor(value: ResourceColor): T;
    backgroundColor(value: ResourceColor): T;
    borderStyle(value: BorderStyle): T;
    borderWidth(value: Dimension): T;
    borderColor(value: ResourceColor): T;
    borderRadius(value: Dimension): T;
    padding(value: (Padding|Dimension)): T;
    textIconSpace(value: Dimension): T;
    key(value: string): T;
    width(value: Length): T;
    height(value: Length): T;
    size(value: SizeOptions): T;
    constraintSize(value: ConstraintSizeOptions): T;
}
declare interface SelectOption {
    value: ResourceStr;
    icon?: ResourceStr;
    symbolIcon?: SymbolGlyphModifier;
}
declare interface SelectInterface {
    (options: SelectOption[]): SelectAttribute;
}
declare enum ArrowPosition {
    END = 0,
    START = 1,
}
declare enum MenuAlignType {
    START = 0,
    CENTER = 1,
    END = 2,
}
declare type Callback_Number_String_Void = ((index: number, value: string) => void);
declare type Callback_Union_Number_Resource_Void = ((selected: (number|Resource)) => void);
declare type Callback_ResourceStr_Void = ((value: ResourceStr) => void);
declare class SelectAttribute extends CommonMethod<SelectAttribute> {
    selected(value: (number|Resource)): SelectAttribute;
    value(value: ResourceStr): SelectAttribute;
    font(value: Font): SelectAttribute;
    fontColor(value: ResourceColor): SelectAttribute;
    selectedOptionBgColor(value: ResourceColor): SelectAttribute;
    selectedOptionFont(value: Font): SelectAttribute;
    selectedOptionFontColor(value: ResourceColor): SelectAttribute;
    optionBgColor(value: ResourceColor): SelectAttribute;
    optionFont(value: Font): SelectAttribute;
    optionFontColor(value: ResourceColor): SelectAttribute;
    onSelect(value: ((index: number, value: string) => void)): SelectAttribute;
    space(value: Length): SelectAttribute;
    arrowPosition(value: ArrowPosition): SelectAttribute;
    optionWidth(value: (Dimension|OptionWidthMode)): SelectAttribute;
    optionHeight(value: Dimension): SelectAttribute;
    menuBackgroundColor(value: ResourceColor): SelectAttribute;
    menuBackgroundBlurStyle(value: BlurStyle): SelectAttribute;
    controlSize(value: ControlSize): SelectAttribute;
    menuItemContentModifier(value: ContentModifier<MenuItemConfiguration>): SelectAttribute;
    divider(value: DividerOptions | undefined): SelectAttribute;
    menuAlign(alignType: MenuAlignType, offset?: Offset): SelectAttribute;
    _onChangeEvent_selected(callback_: ((selected: (number|Resource)) => void)): void;
    _onChangeEvent_value(callback_: ((value: ResourceStr) => void)): void;
}
declare interface MenuItemConfiguration extends CommonConfiguration<MenuItemConfiguration> {
    value: ResourceStr;
    icon?: ResourceStr;
    symbolIcon?: SymbolGlyphModifier;
    selected: boolean;
    index: number;
    triggerSelect(index: number, value: string): void;
}
declare interface ViewportRect {
    x?: (number|string);
    y?: (number|string);
    width?: (number|string);
    height?: (number|string);
}
declare interface ShapeInterface {
    new(value?: PixelMap): ShapeAttribute;
    (value: PixelMap): ShapeAttribute;
    (): ShapeAttribute;
}
declare class ShapeAttribute extends CommonMethod<ShapeAttribute> {
    viewPort(value: ViewportRect): ShapeAttribute;
    stroke(value: ResourceColor): ShapeAttribute;
    fill(value: ResourceColor): ShapeAttribute;
    strokeDashOffset(value: (number|string)): ShapeAttribute;
    strokeDashArray(value: Length[]): ShapeAttribute;
    strokeLineCap(value: LineCapStyle): ShapeAttribute;
    strokeLineJoin(value: LineJoinStyle): ShapeAttribute;
    strokeMiterLimit(value: (number|string)): ShapeAttribute;
    strokeOpacity(value: (number|string|Resource)): ShapeAttribute;
    fillOpacity(value: (number|string|Resource)): ShapeAttribute;
    strokeWidth(value: (number|string)): ShapeAttribute;
    antiAlias(value: boolean): ShapeAttribute;
    mesh(value: number[], column: number, row: number): ShapeAttribute;
}
declare enum SliderStyle {
    OUT_SET = 0,
    OutSet = 0,
    IN_SET = 1,
    InSet = 1,
    NONE = 2,
}
declare enum SliderChangeMode {
    BEGIN = 0,
    Begin = 0,
    MOVING = 1,
    Moving = 1,
    END = 2,
    End = 2,
    CLICK = 3,
    Click = 3,
}
declare enum SliderInteraction {
    SLIDE_AND_CLICK = 0,
    SLIDE_ONLY = 1,
    SLIDE_AND_CLICK_UP = 2,
}
declare interface SlideRange {
    from?: number;
    to?: number;
}
declare interface SliderOptions {
    value?: number;
    min?: number;
    max?: number;
    step?: number;
    style?: SliderStyle;
    direction?: Axis;
    reverse?: boolean;
}
declare enum SliderBlockType {
    DEFAULT = 0,
    IMAGE = 1,
    SHAPE = 2,
}
declare interface SliderBlockStyle {
    type: SliderBlockType;
    image?: ResourceStr;
    shape?: string;
}
declare type SliderTriggerChangeCallback = ((value: number, mode: SliderChangeMode) => void);
declare interface SliderConfiguration extends CommonConfiguration<SliderConfiguration> {
    value: number;
    min: number;
    max: number;
    step: number;
    triggerChange: SliderTriggerChangeCallback;
}
declare interface SliderInterface {
    (options?: SliderOptions): SliderAttribute;
}
declare type Callback_Number_SliderChangeMode_Void = ((value: number, mode: SliderChangeMode) => void);
declare class SliderAttribute extends CommonMethod<SliderAttribute> {
    blockColor(value: ResourceColor): SliderAttribute;
    trackColor(value: (ResourceColor|LinearGradient)): SliderAttribute;
    selectedColor(value: ResourceColor): SliderAttribute;
    minLabel(value: string): SliderAttribute;
    maxLabel(value: string): SliderAttribute;
    showSteps(value: boolean): SliderAttribute;
    trackThickness(value: Length): SliderAttribute;
    onChange(value: ((value: number, mode: SliderChangeMode) => void)): SliderAttribute;
    blockBorderColor(value: ResourceColor): SliderAttribute;
    blockBorderWidth(value: Length): SliderAttribute;
    stepColor(value: ResourceColor): SliderAttribute;
    trackBorderRadius(value: Length): SliderAttribute;
    selectedBorderRadius(value: Dimension): SliderAttribute;
    blockSize(value: SizeOptions): SliderAttribute;
    blockStyle(value: SliderBlockStyle): SliderAttribute;
    stepSize(value: Length): SliderAttribute;
    sliderInteractionMode(value: SliderInteraction): SliderAttribute;
    minResponsiveDistance(value: number): SliderAttribute;
    contentModifier(value: ContentModifier<SliderConfiguration>): SliderAttribute;
    slideRange(value: SlideRange): SliderAttribute;
    showTips(value: boolean, content?: ResourceStr): SliderAttribute;
    _onChangeEvent_value(callback_: ((index: number) => void)): void;
}
declare interface TextBackgroundStyle {
    color?: ResourceColor;
    radius?: (Dimension|BorderRadiuses);
}
declare class BaseSpan<T> extends CommonMethod<T> {
    textBackgroundStyle(value: TextBackgroundStyle): T;
    baselineOffset(value: LengthMetrics): T;
}
declare interface SpanInterface {
    (value: (string|Resource)): SpanAttribute;
}
declare class SpanAttribute extends BaseSpan<SpanAttribute> {
    font(value: Font): SpanAttribute;
    fontColor(value: ResourceColor): SpanAttribute;
    fontSize(value: (number|string|Resource)): SpanAttribute;
    fontStyle(value: FontStyle): SpanAttribute;
    fontWeight(value: (number|FontWeight|string)): SpanAttribute;
    fontFamily(value: (string|Resource)): SpanAttribute;
    decoration(value: DecorationStyleInterface): SpanAttribute;
    letterSpacing(value: (number|string)): SpanAttribute;
    textCase(value: TextCase): SpanAttribute;
    lineHeight(value: Length): SpanAttribute;
    textShadow(value: (ShadowOptions|ShadowOptions[])): SpanAttribute;
}
declare interface StackOptions {
    alignContent?: Alignment;
}
declare interface StackInterface {
    (options?: StackOptions): StackAttribute;
}
declare class StackAttribute extends CommonMethod<StackAttribute> {
    alignContent(value: Alignment): StackAttribute;
    pointLight(value: PointLightStyle): StackAttribute;
}
declare enum ColorMode {
    LIGHT = 0,
    DARK = 1,
}
declare enum LayoutDirection {
    LTR = 0,
    RTL = 1,
    AUTO = 2,
    Auto = 2,
}
declare class Storage {
    constructor(needCrossThread?: boolean, file?: string);
    get(key: string): string | undefined;
    set(key: string, val: any): void;
    clear(): void;
    delete(key: string): void;
}
declare type Literal_Number_index = { index?: number }
declare interface StepperInterface {
    (value?: { index?: number }): StepperAttribute;
}
declare class StepperAttribute extends CommonMethod<StepperAttribute> {
    onFinish(value: (() => void)): StepperAttribute;
    onSkip(value: (() => void)): StepperAttribute;
    onChange(value: ((first: number, last: number) => void)): StepperAttribute;
    onNext(value: ((first: number, last: number) => void)): StepperAttribute;
    onPrevious(value: ((first: number, last: number) => void)): StepperAttribute;
    _onChangeEvent_index(callback_: ((index: number) => void)): void;
}
declare enum ItemState {
    NORMAL = 0,
    Normal = 0,
    DISABLED = 1,
    Disabled = 1,
    WAITING = 2,
    Waiting = 2,
    SKIP = 3,
    Skip = 3,
}
declare interface StepperItemInterface {
    (): StepperItemAttribute;
}
declare class StepperItemAttribute extends CommonMethod<StepperItemAttribute> {
    prevLabel(value: string): StepperItemAttribute;
    nextLabel(value: string): StepperItemAttribute;
    status(value: ItemState): StepperItemAttribute;
}
declare class SwiperController {
    constructor();
    showNext(): void;
    showPrevious(): void;
    changeIndex(index: number, useAnimation?: boolean): void;
    finishAnimation(callback_?: VoidCallback): void;
}
declare class Indicator<T> {
    left(value: Length): T;
    top(value: Length): T;
    right(value: Length): T;
    bottom(value: Length): T;
    start(value: LengthMetrics): T;
    end(value: LengthMetrics): T;
}
declare class DotIndicator extends Indicator<DotIndicator> {
    constructor();
    itemWidth(value: Length): DotIndicator;
    itemHeight(value: Length): DotIndicator;
    selectedItemWidth(value: Length): DotIndicator;
    selectedItemHeight(value: Length): DotIndicator;
    mask(value: boolean): DotIndicator;
    color(value: ResourceColor): DotIndicator;
    selectedColor(value: ResourceColor): DotIndicator;
    maxDisplayCount(maxDisplayCount: number): DotIndicator;
}
declare interface SwiperAutoFill {
    minSize: VP;
}
declare class DigitIndicator extends Indicator<DigitIndicator> {
    constructor();
    fontColor(value: ResourceColor): DigitIndicator;
    selectedFontColor(value: ResourceColor): DigitIndicator;
    digitFont(value: Font): DigitIndicator;
    selectedDigitFont(value: Font): DigitIndicator;
}
declare interface ArrowStyle {
    showBackground?: boolean;
    isSidebarMiddle?: boolean;
    backgroundSize?: Length;
    backgroundColor?: ResourceColor;
    arrowSize?: Length;
    arrowColor?: ResourceColor;
}
declare enum SwiperDisplayMode {
    LEGACY_STRETCH = 0,
    Stretch = 0,
    LEGACY_AUTO_LINEAR = 1,
    AutoLinear = 1,
    STRETCH = 2,
    AUTO_LINEAR = 3,
}
declare interface SwiperInterface {
    (controller?: SwiperController): SwiperAttribute;
}
declare interface IndicatorStyle {
    left?: Length;
    top?: Length;
    right?: Length;
    bottom?: Length;
    size?: Length;
    mask?: boolean;
    color?: ResourceColor;
    selectedColor?: ResourceColor;
}
declare interface SwiperAnimationEvent {
    currentOffset: number;
    targetOffset: number;
    velocity: number;
}
declare enum SwiperNestedScrollMode {
    SELF_ONLY = 0,
    SELF_FIRST = 1,
}
declare type OnSwiperAnimationStartCallback = ((index: number, targetIndex: number, extraInfo: SwiperAnimationEvent) => void);
declare type OnSwiperAnimationEndCallback = ((index: number, extraInfo: SwiperAnimationEvent) => void);
declare type OnSwiperGestureSwipeCallback = ((index: number, extraInfo: SwiperAnimationEvent) => void);
declare class SwiperAttribute extends CommonMethod<SwiperAttribute> {
    index(value: number): SwiperAttribute;
    autoPlay(value: boolean): SwiperAttribute;
    interval(value: number): SwiperAttribute;
    indicator(value: (DotIndicator|DigitIndicator|boolean)): SwiperAttribute;
    indicator(value: IndicatorComponentController): SwiperAttribute;
    loop(value: boolean): SwiperAttribute;
    duration(value: number): SwiperAttribute;
    vertical(value: boolean): SwiperAttribute;
    itemSpace(value: (number|string)): SwiperAttribute;
    displayMode(value: SwiperDisplayMode): SwiperAttribute;
    cachedCount(value: number): SwiperAttribute;
    effectMode(value: EdgeEffect): SwiperAttribute;
    disableSwipe(value: boolean): SwiperAttribute;
    curve(value: (Curve|string|ICurve)): SwiperAttribute;
    onChange(value: ((index: number) => void)): SwiperAttribute;
    indicatorStyle(value: IndicatorStyle): SwiperAttribute;
    onAnimationStart(value: OnSwiperAnimationStartCallback): SwiperAttribute;
    onAnimationEnd(value: OnSwiperAnimationEndCallback): SwiperAttribute;
    onGestureSwipe(value: OnSwiperGestureSwipeCallback): SwiperAttribute;
    nestedScroll(value: SwiperNestedScrollMode): SwiperAttribute;
    customContentTransition(value: SwiperContentAnimatedTransition): SwiperAttribute;
    onContentDidScroll(value: ContentDidScrollCallback): SwiperAttribute;
    indicatorInteractive(value: boolean): SwiperAttribute;
    displayArrow(value: (ArrowStyle|boolean), isHoverShow?: boolean): SwiperAttribute;
    displayCount(value: (number|string|SwiperAutoFill), swipeByGroup?: boolean): SwiperAttribute;
    prevMargin(value: Length, ignoreBlank?: boolean): SwiperAttribute;
    nextMargin(value: Length, ignoreBlank?: boolean): SwiperAttribute;
    _onChangeEvent_index(callback_: ((index: number) => void)): void;
}
declare type Callback_SwiperContentTransitionProxy_Void = ((parameter: SwiperContentTransitionProxy) => void);
declare interface SwiperContentAnimatedTransition {
    timeout?: number;
    transition: ((parameter: SwiperContentTransitionProxy) => void);
}
declare interface SwiperContentTransitionProxy {
    selectedIndex: number;
    index: number;
    position: number;
    mainAxisLength: number;
    finishTransition(): void;
}
declare type ContentDidScrollCallback = ((selectedIndex: number, index: number, position: number, mainAxisLength: number) => void);
declare class IndicatorComponentController {
    constructor();
    showNext(): void;
    showPrevious(): void;
    changeIndex(index: number, useAnimation?: boolean): void;
}
declare interface IndicatorComponentInterface {
    (controller?: IndicatorComponentController): IndicatorComponentAttribute;
}
declare class IndicatorComponentAttribute extends CommonMethod<IndicatorComponentAttribute> {
    initialIndex(value: number): IndicatorComponentAttribute;
    count(value: number): IndicatorComponentAttribute;
    style(value: (DotIndicator|DigitIndicator)): IndicatorComponentAttribute;
    loop(value: boolean): IndicatorComponentAttribute;
    vertical(value: boolean): IndicatorComponentAttribute;
    onChange(value: ((index: number) => void)): IndicatorComponentAttribute;
}
declare interface SymbolGlyphInterface {
    (value?: Resource): SymbolGlyphAttribute;
}
declare enum SymbolRenderingStrategy {
    SINGLE = 0,
    MULTIPLE_COLOR = 1,
    MULTIPLE_OPACITY = 2,
}
declare enum SymbolEffectStrategy {
    NONE = 0,
    SCALE = 1,
    HIERARCHICAL = 2,
}
declare enum EffectFillStyle {
    CUMULATIVE = 0,
    ITERATIVE = 1,
}
declare class HierarchicalSymbolEffect extends SymbolEffect {
    constructor(fillStyle?: EffectFillStyle);
    fillStyle?: EffectFillStyle;
}
declare class AppearSymbolEffect extends SymbolEffect {
    constructor(scope?: EffectScope);
    scope?: EffectScope;
}
declare class DisappearSymbolEffect extends SymbolEffect {
    constructor(scope?: EffectScope);
    scope?: EffectScope;
}
declare class BounceSymbolEffect extends SymbolEffect {
    constructor(scope?: EffectScope, direction?: EffectDirection);
    scope?: EffectScope;
    direction?: EffectDirection;
}
declare class PulseSymbolEffect extends SymbolEffect {
}
declare class SymbolGlyphAttribute extends CommonMethod<SymbolGlyphAttribute> {
    fontSize(value: (number|string|Resource)): SymbolGlyphAttribute;
    fontColor(value: ResourceColor[]): SymbolGlyphAttribute;
    fontWeight(value: (number|FontWeight|string)): SymbolGlyphAttribute;
    effectStrategy(value: SymbolEffectStrategy): SymbolGlyphAttribute;
    renderingStrategy(value: SymbolRenderingStrategy): SymbolGlyphAttribute;
    symbolEffect(symbolEffect: SymbolEffect, isActive?: boolean): SymbolGlyphAttribute;
    symbolEffect(symbolEffect: SymbolEffect, triggerValue?: number): SymbolGlyphAttribute;
}
declare interface SymbolSpanInterface {
    (value: Resource): SymbolSpanAttribute;
}
declare class SymbolSpanAttribute extends CommonMethod<SymbolSpanAttribute> {
    fontSize(value: (number|string|Resource)): SymbolSpanAttribute;
    fontColor(value: ResourceColor[]): SymbolSpanAttribute;
    fontWeight(value: (number|FontWeight|string)): SymbolSpanAttribute;
    effectStrategy(value: SymbolEffectStrategy): SymbolSpanAttribute;
    renderingStrategy(value: SymbolRenderingStrategy): SymbolSpanAttribute;
    attributeModifier(value: AttributeModifier<SymbolSpanAttribute>): SymbolSpanAttribute;
}
declare enum BarMode {
    SCROLLABLE = 0,
    Scrollable = 0,
    FIXED = 1,
    Fixed = 1,
}
declare enum AnimationMode {
    CONTENT_FIRST = 0,
    ACTION_FIRST = 1,
    NO_ANIMATION = 2,
}
declare enum BarPosition {
    START = 0,
    Start = 0,
    END = 1,
    End = 1,
}
declare enum LayoutStyle {
    ALWAYS_CENTER = 0,
    ALWAYS_AVERAGE_SPLIT = 1,
    SPACE_BETWEEN_OR_CENTER = 2,
}
declare class TabsController {
    constructor();
    changeIndex(value: number): void;
    preloadItems(indices: number[] | undefined): Promise<void>;
    setTabBarTranslate(translate: TranslateOptions): void;
    setTabBarOpacity(opacity: number): void;
}
declare interface TabsOptions {
    barPosition?: BarPosition;
    index?: number;
    controller?: TabsController;
}
declare interface TabsInterface {
    (options?: TabsOptions): TabsAttribute;
}
declare interface DividerStyle {
    strokeWidth: Length;
    color?: ResourceColor;
    startMargin?: Length;
    endMargin?: Length;
}
declare interface TabsAnimationEvent {
    currentOffset: number;
    targetOffset: number;
    velocity: number;
}
declare interface BarGridColumnOptions {
    sm?: number;
    md?: number;
    lg?: number;
    margin?: Dimension;
    gutter?: Dimension;
}
declare interface ScrollableBarModeOptions {
    margin?: Dimension;
    nonScrollableLayoutStyle?: LayoutStyle;
}
declare type OnTabsAnimationStartCallback = ((index: number, targetIndex: number, extraInfo: TabsAnimationEvent) => void);
declare type OnTabsAnimationEndCallback = ((index: number, extraInfo: TabsAnimationEvent) => void);
declare type OnTabsGestureSwipeCallback = ((index: number, extraInfo: TabsAnimationEvent) => void);
declare type TabsCustomContentTransitionCallback = ((from: number, to: number) => TabContentAnimatedTransition | undefined);
declare type OnTabsContentWillChangeCallback = ((currentIndex: number, comingIndex: number) => boolean);
declare class TabsAttribute extends CommonMethod<TabsAttribute> {
    vertical(value: boolean): TabsAttribute;
    barPosition(value: BarPosition): TabsAttribute;
    scrollable(value: boolean): TabsAttribute;
    barMode(value: BarMode): TabsAttribute;
    barWidth(value: Length): TabsAttribute;
    barHeight(value: Length): TabsAttribute;
    animationDuration(value: number): TabsAttribute;
    animationMode(value: AnimationMode | undefined): TabsAttribute;
    edgeEffect(value: EdgeEffect | undefined): TabsAttribute;
    onChange(value: ((index: number) => void)): TabsAttribute;
    onTabBarClick(value: ((index: number) => void)): TabsAttribute;
    onAnimationStart(value: OnTabsAnimationStartCallback): TabsAttribute;
    onAnimationEnd(value: OnTabsAnimationEndCallback): TabsAttribute;
    onGestureSwipe(value: OnTabsGestureSwipeCallback): TabsAttribute;
    fadingEdge(value: boolean): TabsAttribute;
    divider(value: DividerStyle | undefined): TabsAttribute;
    barOverlap(value: boolean): TabsAttribute;
    barBackgroundColor(value: ResourceColor): TabsAttribute;
    barGridAlign(value: BarGridColumnOptions): TabsAttribute;
    customContentTransition(value: TabsCustomContentTransitionCallback): TabsAttribute;
    barBackgroundBlurStyle(value: BlurStyle): TabsAttribute;
    barBackgroundEffect(value: BackgroundEffectOptions): TabsAttribute;
    onContentWillChange(value: OnTabsContentWillChangeCallback): TabsAttribute;
    barMode(value: BarMode.SCROLLABLE, options: ScrollableBarModeOptions): TabsAttribute;
    barMode(value: BarMode, options?: ScrollableBarModeOptions): TabsAttribute;
    barBackgroundBlurStyle(style: BlurStyle, options: BackgroundBlurStyleOptions): TabsAttribute;
    _onChangeEvent_index(callback_: ((index: number) => void)): void;
}
declare type Callback_TabContentTransitionProxy_Void = ((parameter: TabContentTransitionProxy) => void);
declare interface TabContentAnimatedTransition {
    timeout?: number;
    transition: ((parameter: TabContentTransitionProxy) => void);
}
declare interface TabContentTransitionProxy {
    from: number;
    to: number;
    finishTransition(): void;
}
declare enum SelectedMode {
    INDICATOR = 0,
    BOARD = 1,
}
declare enum LayoutMode {
    AUTO = 0,
    VERTICAL = 1,
    HORIZONTAL = 2,
}
declare interface BoardStyle {
    borderRadius?: Length;
}
declare interface TabBarIconStyle {
    selectedColor?: ResourceColor;
    unselectedColor?: ResourceColor;
}
declare class TabBarSymbol {
    normal: SymbolGlyphModifier;
    selected?: SymbolGlyphModifier;
}
declare interface TabBarOptions {
    icon?: (string|Resource);
    text?: (string|Resource);
}
declare class SubTabBarStyle {
    constructor(content: ResourceStr);
    constructor(content: (ResourceStr|ComponentContent));
    indicator(value: IndicatorStyle): SubTabBarStyle;
    selectedMode(value: SelectedMode): SubTabBarStyle;
    board(value: BoardStyle): SubTabBarStyle;
    labelStyle(value: LabelStyle): SubTabBarStyle;
    padding(value: (Padding|Dimension)): SubTabBarStyle;
    padding(padding: LocalizedPadding): SubTabBarStyle;
    id(value: string): SubTabBarStyle;
}
declare class BottomTabBarStyle {
    constructor(icon: (ResourceStr|TabBarSymbol), text: ResourceStr);
    labelStyle(value: LabelStyle): BottomTabBarStyle;
    padding(value: (Padding|Dimension|LocalizedPadding)): BottomTabBarStyle;
    layoutMode(value: LayoutMode): BottomTabBarStyle;
    verticalAlign(value: VerticalAlign): BottomTabBarStyle;
    symmetricExtensible(value: boolean): BottomTabBarStyle;
    id(value: string): BottomTabBarStyle;
    iconStyle(style: TabBarIconStyle): BottomTabBarStyle;
}
declare interface TabContentInterface {
    (): TabContentAttribute;
}
declare class TabContentAttribute extends CommonMethod<TabContentAttribute> {
    tabBar(value: (string|Resource|CustomBuilder|TabBarOptions)): TabContentAttribute;
    tabBar(value: (SubTabBarStyle|BottomTabBarStyle)): TabContentAttribute;
    onWillShow(value: VoidCallback): TabContentAttribute;
    onWillHide(value: VoidCallback): TabContentAttribute;
}
declare interface TextOverflowOptions {
    overflow: TextOverflow;
}
declare interface TextInterface {
    (content?: (string|Resource), value?: TextOptions): TextAttribute;
}
declare class TextAttribute extends CommonMethod<TextAttribute> {
    font(value: Font): TextAttribute;
    fontColor(value: ResourceColor): TextAttribute;
    fontSize(value: (number|string|Resource)): TextAttribute;
    minFontSize(value: (number|string|Resource)): TextAttribute;
    maxFontSize(value: (number|string|Resource)): TextAttribute;
    minFontScale(value: (number|Resource)): TextAttribute;
    maxFontScale(value: (number|Resource)): TextAttribute;
    fontStyle(value: FontStyle): TextAttribute;
    fontWeight(value: (number|FontWeight|string)): TextAttribute;
    lineSpacing(value: LengthMetrics): TextAttribute;
    textAlign(value: TextAlign): TextAttribute;
    lineHeight(value: (number|string|Resource)): TextAttribute;
    textOverflow(value: TextOverflowOptions): TextAttribute;
    fontFamily(value: (string|Resource)): TextAttribute;
    maxLines(value: number): TextAttribute;
    decoration(value: DecorationStyleInterface): TextAttribute;
    letterSpacing(value: (number|string)): TextAttribute;
    textCase(value: TextCase): TextAttribute;
    baselineOffset(value: (number|string)): TextAttribute;
    copyOption(value: CopyOptions): TextAttribute;
    draggable(value: boolean): TextAttribute;
    textShadow(value: (ShadowOptions|ShadowOptions[])): TextAttribute;
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy): TextAttribute;
    textIndent(value: Length): TextAttribute;
    wordBreak(value: WordBreak): TextAttribute;
    lineBreakStrategy(value: LineBreakStrategy): TextAttribute;
    onCopy(value: ((breakpoints: string) => void)): TextAttribute;
    caretColor(value: ResourceColor): TextAttribute;
    selectedBackgroundColor(value: ResourceColor): TextAttribute;
    ellipsisMode(value: EllipsisMode): TextAttribute;
    enableDataDetector(value: boolean): TextAttribute;
    dataDetectorConfig(value: TextDataDetectorConfig): TextAttribute;
    onTextSelectionChange(value: ((first: number, last: number) => void)): TextAttribute;
    fontFeature(value: string): TextAttribute;
    privacySensitive(value: boolean): TextAttribute;
    textSelectable(value: TextSelectableMode): TextAttribute;
    editMenuOptions(value: EditMenuOptions): TextAttribute;
    halfLeading(value: boolean): TextAttribute;
    enableHapticFeedback(value: boolean): TextAttribute;
    font(fontValue: Font, options?: FontSettingOptions): TextAttribute;
    fontWeight(weight: (number|FontWeight|string), options?: FontSettingOptions): TextAttribute;
    selection(selectionStart: number, selectionEnd: number): TextAttribute;
    bindSelectionMenu(spanType: TextSpanType, content: CustomBuilder, responseType: TextResponseType, options?: SelectionMenuOptions): TextAttribute;
}
declare enum TextSpanType {
    TEXT = 0,
    IMAGE = 1,
    MIXED = 2,
}
declare enum TextResponseType {
    RIGHT_CLICK = 0,
    LONG_PRESS = 1,
    SELECT = 2,
}
declare interface TextOptions {
    controller: TextController;
}
declare class TextController {
    closeSelectionMenu(): void;
    setStyledString(value: StyledString): void;
    getLayoutManager(): LayoutManager;
}
declare class TextAreaController extends TextContentControllerBase {
    constructor();
    caretPosition(value: number): void;
    setTextSelection(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void;
    stopEditing(): void;
}
declare interface TextAreaOptions {
    placeholder?: ResourceStr;
    text?: ResourceStr;
    controller?: TextAreaController;
}
declare interface TextAreaInterface {
    (value?: TextAreaOptions): TextAreaAttribute;
}
declare enum TextAreaType {
    NORMAL = 0,
    NUMBER = 2,
    PHONE_NUMBER = 3,
    EMAIL = 5,
    NUMBER_DECIMAL = 12,
    URL = 13,
}
declare enum ContentType {
    USER_NAME = 0,
    PASSWORD = 1,
    NEW_PASSWORD = 2,
    FULL_STREET_ADDRESS = 3,
    HOUSE_NUMBER = 4,
    DISTRICT_ADDRESS = 5,
    CITY_ADDRESS = 6,
    PROVINCE_ADDRESS = 7,
    COUNTRY_ADDRESS = 8,
    PERSON_FULL_NAME = 9,
    PERSON_LAST_NAME = 10,
    PERSON_FIRST_NAME = 11,
    PHONE_NUMBER = 12,
    PHONE_COUNTRY_CODE = 13,
    FULL_PHONE_NUMBER = 14,
    EMAIL_ADDRESS = 15,
    BANK_CARD_NUMBER = 16,
    ID_CARD_NUMBER = 17,
    NICKNAME = 23,
    DETAIL_INFO_WITHOUT_STREET = 24,
    FORMAT_ADDRESS = 25,
}
declare type TextAreaSubmitCallback = ((enterKeyType: EnterKeyType, event?: SubmitEvent) => void);
declare type Callback_EnterKeyType_Void = ((enterKey: EnterKeyType) => void);
declare type Callback_String_PasteEvent_Void = ((value: string, event: PasteEvent) => void);
declare class TextAreaAttribute extends CommonMethod<TextAreaAttribute> {
    placeholderColor(value: ResourceColor): TextAreaAttribute;
    placeholderFont(value: Font): TextAreaAttribute;
    enterKeyType(value: EnterKeyType): TextAreaAttribute;
    textAlign(value: TextAlign): TextAreaAttribute;
    caretColor(value: ResourceColor): TextAreaAttribute;
    fontColor(value: ResourceColor): TextAreaAttribute;
    fontSize(value: Length): TextAreaAttribute;
    fontStyle(value: FontStyle): TextAreaAttribute;
    fontWeight(value: (number|FontWeight|string)): TextAreaAttribute;
    fontFamily(value: ResourceStr): TextAreaAttribute;
    textOverflow(value: TextOverflow): TextAreaAttribute;
    textIndent(value: Dimension): TextAreaAttribute;
    caretStyle(value: CaretStyle): TextAreaAttribute;
    selectedBackgroundColor(value: ResourceColor): TextAreaAttribute;
    onSubmit(value: ((enterKey: EnterKeyType) => void)): TextAreaAttribute;
    onSubmit(value: TextAreaSubmitCallback): TextAreaAttribute;
    onChange(value: EditableTextOnChangeCallback): TextAreaAttribute;
    onTextSelectionChange(value: ((first: number, last: number) => void)): TextAreaAttribute;
    onContentScroll(value: ((first: number, last: number) => void)): TextAreaAttribute;
    onEditChange(value: ((parameter: boolean) => void)): TextAreaAttribute;
    onCopy(value: ((breakpoints: string) => void)): TextAreaAttribute;
    onCut(value: ((breakpoints: string) => void)): TextAreaAttribute;
    onPaste(value: ((value: string, event: PasteEvent) => void)): TextAreaAttribute;
    copyOption(value: CopyOptions): TextAreaAttribute;
    enableKeyboardOnFocus(value: boolean): TextAreaAttribute;
    maxLength(value: number): TextAreaAttribute;
    style(value: TextContentStyle): TextAreaAttribute;
    barState(value: BarState): TextAreaAttribute;
    selectionMenuHidden(value: boolean): TextAreaAttribute;
    minFontSize(value: (number|string|Resource)): TextAreaAttribute;
    maxFontSize(value: (number|string|Resource)): TextAreaAttribute;
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy): TextAreaAttribute;
    maxLines(value: number): TextAreaAttribute;
    wordBreak(value: WordBreak): TextAreaAttribute;
    lineBreakStrategy(value: LineBreakStrategy): TextAreaAttribute;
    decoration(value: TextDecorationOptions): TextAreaAttribute;
    letterSpacing(value: (number|string|Resource)): TextAreaAttribute;
    lineSpacing(value: LengthMetrics): TextAreaAttribute;
    lineHeight(value: (number|string|Resource)): TextAreaAttribute;
    type(value: TextAreaType): TextAreaAttribute;
    enableAutoFill(value: boolean): TextAreaAttribute;
    contentType(value: ContentType): TextAreaAttribute;
    fontFeature(value: string): TextAreaAttribute;
    onWillInsert(value: ((parameter: InsertValue) => boolean)): TextAreaAttribute;
    onDidInsert(value: ((parameter: InsertValue) => void)): TextAreaAttribute;
    onWillDelete(value: ((parameter: DeleteValue) => boolean)): TextAreaAttribute;
    onDidDelete(value: ((parameter: DeleteValue) => void)): TextAreaAttribute;
    editMenuOptions(value: EditMenuOptions): TextAreaAttribute;
    enablePreviewText(value: boolean): TextAreaAttribute;
    enableHapticFeedback(value: boolean): TextAreaAttribute;
    inputFilter(value: ResourceStr, error?: ((breakpoints: string) => void)): TextAreaAttribute;
    showCounter(value: boolean, options?: InputCounterOptions): TextAreaAttribute;
    customKeyboard(value: CustomBuilder, options?: KeyboardOptions): TextAreaAttribute;
    _onChangeEvent_text(callback_: ((value: ResourceStr) => void)): void;
}
declare class TextClockController {
    constructor();
    start(): void;
    stop(): void;
}
declare interface TextClockConfiguration extends CommonConfiguration<TextClockConfiguration> {
    timeZoneOffset: number;
    started: boolean;
    timeValue: number;
}
declare interface TextClockOptions {
    timeZoneOffset?: number;
    controller?: TextClockController;
}
declare interface TextClockInterface {
    (options?: TextClockOptions): TextClockAttribute;
}
declare class TextClockAttribute extends CommonMethod<TextClockAttribute> {
    format(value: string): TextClockAttribute;
    onDateChange(value: ((index: number) => void)): TextClockAttribute;
    fontColor(value: ResourceColor): TextClockAttribute;
    fontSize(value: Length): TextClockAttribute;
    fontStyle(value: FontStyle): TextClockAttribute;
    fontWeight(value: (number|FontWeight|string)): TextClockAttribute;
    fontFamily(value: ResourceStr): TextClockAttribute;
    textShadow(value: (ShadowOptions|ShadowOptions[])): TextClockAttribute;
    fontFeature(value: string): TextClockAttribute;
    contentModifier(value: ContentModifier<TextClockConfiguration>): TextClockAttribute;
    dateTimeOptions(value: DateTimeOptions | undefined): TextClockAttribute;
}
declare enum TextDataDetectorType {
    PHONE_NUMBER = 0,
    URL = 1,
    EMAIL = 2,
    ADDRESS = 3,
    DATE_TIME = 4,
}
declare interface TextDataDetectorConfig {
    types: TextDataDetectorType[];
    onDetectResultUpdate?: ((breakpoints: string) => void);
    color?: ResourceColor;
    decoration?: DecorationStyleInterface;
}
declare interface TextRange {
    start?: number;
    end?: number;
}
declare interface InsertValue {
    insertOffset: number;
    insertValue: string;
}
declare enum TextDeleteDirection {
    BACKWARD = 0,
    FORWARD = 1,
}
declare enum MenuType {
    SELECTION_MENU = 0,
    PREVIEW_MENU = 1,
}
declare interface DeleteValue {
    deleteOffset: number;
    direction: TextDeleteDirection;
    deleteValue: string;
}
declare type OnDidChangeCallback = ((rangeBefore: TextRange, rangeAfter: TextRange) => void);
declare type EditableTextOnChangeCallback = ((value: string, previewText?: PreviewText) => void);
declare interface TextBaseController {
    setSelection(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void;
    closeSelectionMenu(): void;
    getLayoutManager(): LayoutManager;
}
declare interface TextEditControllerEx extends TextBaseController {
    isEditing(): boolean;
    stopEditing(): void;
    setCaretOffset(offset: number): boolean;
    getCaretOffset(): number;
    getPreviewText?(): PreviewText;
}
declare interface StyledStringController {
    setStyledString(styledString: StyledString): void;
    getStyledString(): MutableStyledString;
}
declare type Callback_StyledStringChangeValue_Boolean = ((parameter: StyledStringChangeValue) => boolean);
declare interface StyledStringChangedListener {
    onWillChange?: ((parameter: StyledStringChangeValue) => boolean);
    onDidChange?: OnDidChangeCallback;
}
declare interface StyledStringChangeValue {
    range: TextRange;
    replacementString: StyledString;
    previewText?: StyledString;
}
declare interface LayoutManager {
    getLineCount(): number;
    getGlyphPositionAtCoordinate(x: number, y: number): PositionWithAffinity;
    getLineMetrics(lineNumber: number): LineMetrics;
    getRectsForRange(range: TextRange, widthStyle: RectWidthStyle, heightStyle: RectHeightStyle): TextBox[];
}
declare interface PositionWithAffinity {
    position: number;
    affinity: Affinity;
}
declare interface Affinity {
    _AffinityStub: string;
}
declare interface LineMetrics {
    _LineMetricsStub: string;
}
declare interface TextBox {
    _TextBoxStub: string;
}
declare interface CaretStyle {
    width?: Length;
    color?: ResourceColor;
}
declare class TextMenuItemId {
    equals(id: TextMenuItemId): boolean;
}
declare interface PreviewText {
    offset: number;
    value: string;
}
declare interface TextMenuItem {
    content: ResourceStr;
    icon?: ResourceStr;
    id: TextMenuItemId;
}
declare interface EditMenuOptions {
    onCreateMenu(menuItems: TextMenuItem[]): TextMenuItem[];
    onMenuItemClick(menuItem: TextMenuItem, range: TextRange): boolean;
}
declare interface DecorationStyleResult {
    type: TextDecorationType;
    color: ResourceColor;
    style?: TextDecorationStyle;
}
declare interface FontSettingOptions {
    enableVariableFontWeight?: boolean;
}
declare enum InputType {
    NORMAL = 0,
    Normal = 0,
    NUMBER = 1,
    Number = 1,
    PHONE_NUMBER = 2,
    PhoneNumber = 2,
    EMAIL = 3,
    Email = 3,
    PASSWORD = 4,
    Password = 4,
    NUMBER_PASSWORD = 8,
    SCREEN_LOCK_PASSWORD = 9,
    USER_NAME = 10,
    NEW_PASSWORD = 11,
    NUMBER_DECIMAL = 12,
    URL = 13,
}
declare enum EnterKeyType {
    GO = 2,
    Go = 2,
    SEARCH = 3,
    Search = 3,
    SEND = 4,
    Send = 4,
    NEXT = 5,
    Next = 5,
    DONE = 6,
    Done = 6,
    PREVIOUS = 7,
    NEW_LINE = 8,
}
declare interface UnderlineColor {
    typing?: ResourceColor | undefined;
    normal?: ResourceColor | undefined;
    error?: ResourceColor | undefined;
    disable?: ResourceColor | undefined;
}
declare interface SubmitEvent {
    text: string;
    keepEditableState(): void;
}
declare class TextInputController extends TextContentControllerBase {
    constructor();
    caretPosition(value: number): void;
    setTextSelection(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void;
    stopEditing(): void;
}
declare interface TextInputOptions {
    placeholder?: ResourceStr;
    text?: ResourceStr;
    controller?: TextInputController;
}
declare enum TextInputStyle {
    DEFAULT = 0,
    Default = 0,
    INLINE = 1,
    Inline = 1,
}
declare interface TextInputInterface {
    (value?: TextInputOptions): TextInputAttribute;
}
declare interface PasswordIcon {
    onIconSrc?: (string|Resource);
    offIconSrc?: (string|Resource);
}
declare type OnSubmitCallback = ((enterKey: EnterKeyType, event: SubmitEvent) => void);
declare type OnTextSelectionChangeCallback = ((selectionStart: number, selectionEnd: number) => void);
declare type OnContentScrollCallback = ((totalOffsetX: number, totalOffsetY: number) => void);
declare type OnPasteCallback = ((content: string, event: PasteEvent) => void);
declare class TextInputAttribute extends CommonMethod<TextInputAttribute> {
    type(value: InputType): TextInputAttribute;
    contentType(value: ContentType): TextInputAttribute;
    placeholderColor(value: ResourceColor): TextInputAttribute;
    textOverflow(value: TextOverflow): TextInputAttribute;
    textIndent(value: Dimension): TextInputAttribute;
    placeholderFont(value: Font): TextInputAttribute;
    enterKeyType(value: EnterKeyType): TextInputAttribute;
    caretColor(value: ResourceColor): TextInputAttribute;
    onEditChanged(value: ((parameter: boolean) => void)): TextInputAttribute;
    onEditChange(value: ((parameter: boolean) => void)): TextInputAttribute;
    onSubmit(value: OnSubmitCallback): TextInputAttribute;
    onChange(value: EditableTextOnChangeCallback): TextInputAttribute;
    onTextSelectionChange(value: OnTextSelectionChangeCallback): TextInputAttribute;
    onContentScroll(value: OnContentScrollCallback): TextInputAttribute;
    maxLength(value: number): TextInputAttribute;
    fontColor(value: ResourceColor): TextInputAttribute;
    fontSize(value: Length): TextInputAttribute;
    fontStyle(value: FontStyle): TextInputAttribute;
    fontWeight(value: (number|FontWeight|string)): TextInputAttribute;
    fontFamily(value: ResourceStr): TextInputAttribute;
    onCopy(value: ((breakpoints: string) => void)): TextInputAttribute;
    onCut(value: ((breakpoints: string) => void)): TextInputAttribute;
    onPaste(value: OnPasteCallback): TextInputAttribute;
    copyOption(value: CopyOptions): TextInputAttribute;
    showPasswordIcon(value: boolean): TextInputAttribute;
    textAlign(value: TextAlign): TextInputAttribute;
    style(value: (TextInputStyle|TextContentStyle)): TextInputAttribute;
    caretStyle(value: CaretStyle): TextInputAttribute;
    selectedBackgroundColor(value: ResourceColor): TextInputAttribute;
    caretPosition(value: number): TextInputAttribute;
    enableKeyboardOnFocus(value: boolean): TextInputAttribute;
    passwordIcon(value: PasswordIcon): TextInputAttribute;
    showError(value: ResourceStr | undefined): TextInputAttribute;
    showUnit(value: CustomBuilder): TextInputAttribute;
    showUnderline(value: boolean): TextInputAttribute;
    underlineColor(value: (ResourceColor|UnderlineColor) | undefined): TextInputAttribute;
    selectionMenuHidden(value: boolean): TextInputAttribute;
    barState(value: BarState): TextInputAttribute;
    maxLines(value: number): TextInputAttribute;
    wordBreak(value: WordBreak): TextInputAttribute;
    lineBreakStrategy(value: LineBreakStrategy): TextInputAttribute;
    cancelButton(value: CancelButtonOptions): TextInputAttribute;
    cancelButton(value: CancelButtonSymbolOptions): TextInputAttribute;
    selectAll(value: boolean): TextInputAttribute;
    minFontSize(value: (number|string|Resource)): TextInputAttribute;
    maxFontSize(value: (number|string|Resource)): TextInputAttribute;
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy): TextInputAttribute;
    enableAutoFill(value: boolean): TextInputAttribute;
    decoration(value: TextDecorationOptions): TextInputAttribute;
    letterSpacing(value: (number|string|Resource)): TextInputAttribute;
    lineHeight(value: (number|string|Resource)): TextInputAttribute;
    passwordRules(value: string): TextInputAttribute;
    fontFeature(value: string): TextInputAttribute;
    showPassword(value: boolean): TextInputAttribute;
    onSecurityStateChange(value: ((parameter: boolean) => void)): TextInputAttribute;
    onWillInsert(value: ((parameter: InsertValue) => boolean)): TextInputAttribute;
    onDidInsert(value: ((parameter: InsertValue) => void)): TextInputAttribute;
    onWillDelete(value: ((parameter: DeleteValue) => boolean)): TextInputAttribute;
    onDidDelete(value: ((parameter: DeleteValue) => void)): TextInputAttribute;
    editMenuOptions(value: EditMenuOptions): TextInputAttribute;
    enablePreviewText(value: boolean): TextInputAttribute;
    enableHapticFeedback(value: boolean): TextInputAttribute;
    inputFilter(value: ResourceStr, error?: ((breakpoints: string) => void)): TextInputAttribute;
    customKeyboard(value: CustomBuilder, options?: KeyboardOptions): TextInputAttribute;
    showCounter(value: boolean, options?: InputCounterOptions): TextInputAttribute;
    _onChangeEvent_text(callback_: ((value: ResourceStr) => void)): void;
}
declare interface TextPickerRangeContent {
    icon: (string|Resource);
    text?: (string|Resource);
}
declare interface TextCascadePickerRangeContent {
    text: (string|Resource);
    children?: TextCascadePickerRangeContent[];
}
declare interface TextPickerOptions {
    range: (string[]|string[][]|Resource|TextPickerRangeContent[]|TextCascadePickerRangeContent[]);
    value?: (string|string[]);
    selected?: (number|number[]);
}
declare interface TextPickerInterface {
    (options?: TextPickerOptions): TextPickerAttribute;
}
declare interface DividerOptions {
    strokeWidth?: Dimension;
    color?: ResourceColor;
    startMargin?: Dimension;
    endMargin?: Dimension;
}
declare type Callback_String_Number_Void = ((value: string, index: number) => void);
declare type Type_TextPickerAttribute_onChange_callback = ((value: (string|string[]), index: (number|number[])) => void);
declare type Callback_Union_Number_Array_Number_Void = ((selected: (number|number[])) => void);
declare type Callback_Union_String_Array_String_Void = ((value: (string|string[])) => void);
declare class TextPickerAttribute extends CommonMethod<TextPickerAttribute> {
    defaultPickerItemHeight(value: (number|string)): TextPickerAttribute;
    canLoop(value: boolean): TextPickerAttribute;
    disappearTextStyle(value: PickerTextStyle): TextPickerAttribute;
    textStyle(value: PickerTextStyle): TextPickerAttribute;
    selectedTextStyle(value: PickerTextStyle): TextPickerAttribute;
    onAccept(value: ((value: string, index: number) => void)): TextPickerAttribute;
    onCancel(value: (() => void)): TextPickerAttribute;
    onChange(value: ((value: (string|string[]), index: (number|number[])) => void)): TextPickerAttribute;
    selectedIndex(value: (number|number[])): TextPickerAttribute;
    divider(value: DividerOptions | undefined): TextPickerAttribute;
    gradientHeight(value: Dimension): TextPickerAttribute;
    _onChangeEvent_selected(callback_: ((selected: (number|number[])) => void)): void;
    _onChangeEvent_value(callback_: ((value: (string|string[])) => void)): void;
}
declare interface TextPickerResult {
    value: (string|string[]);
    index: (number|number[]);
}
declare type Callback_TextPickerResult_Void = ((value: TextPickerResult) => void);
declare interface TextPickerDialogOptions extends TextPickerOptions {
    defaultPickerItemHeight?: (number|string);
    canLoop?: boolean;
    disappearTextStyle?: PickerTextStyle;
    textStyle?: PickerTextStyle;
    acceptButtonStyle?: PickerDialogButtonStyle;
    cancelButtonStyle?: PickerDialogButtonStyle;
    selectedTextStyle?: PickerTextStyle;
    onAccept?: ((value: TextPickerResult) => void);
    onCancel?: (() => void);
    onChange?: ((value: TextPickerResult) => void);
    maskRect?: Rectangle;
    alignment?: DialogAlignment;
    offset?: Offset;
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    onDidAppear?: (() => void);
    onDidDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
    shadow?: (ShadowOptions|ShadowStyle);
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
}
declare class TextPickerDialog {
}
declare class TextTimerController {
    constructor();
    start(): void;
    pause(): void;
    reset(): void;
}
declare interface TextTimerConfiguration extends CommonConfiguration<TextTimerConfiguration> {
    count: number;
    isCountDown: boolean;
    started: boolean;
    elapsedTime: number;
}
declare interface TextTimerOptions {
    isCountDown?: boolean;
    count?: number;
    controller?: TextTimerController;
}
declare interface TextTimerInterface {
    (options?: TextTimerOptions): TextTimerAttribute;
}
declare class TextTimerAttribute extends CommonMethod<TextTimerAttribute> {
    format(value: string): TextTimerAttribute;
    fontColor(value: ResourceColor): TextTimerAttribute;
    fontSize(value: Length): TextTimerAttribute;
    fontStyle(value: FontStyle): TextTimerAttribute;
    fontWeight(value: (number|FontWeight|string)): TextTimerAttribute;
    fontFamily(value: ResourceStr): TextTimerAttribute;
    onTimer(value: ((first: number, last: number) => void)): TextTimerAttribute;
    textShadow(value: (ShadowOptions|ShadowOptions[])): TextTimerAttribute;
    contentModifier(value: ContentModifier<TextTimerConfiguration>): TextTimerAttribute;
}
declare interface TimePickerResult {
    hour: number;
    minute: number;
    second: number;
}
declare enum TimePickerFormat {
    HOUR_MINUTE = 0,
    HOUR_MINUTE_SECOND = 1,
}
declare interface TimePickerOptions {
    selected?: Date;
    format?: TimePickerFormat;
}
declare interface TimePickerInterface {
    (options?: TimePickerOptions): TimePickerAttribute;
}
declare interface DateTimeOptions {
    _DateTimeOptionsStub: string;
}
declare type Callback_TimePickerResult_Void = ((value: TimePickerResult) => void);
declare class TimePickerAttribute extends CommonMethod<TimePickerAttribute> {
    useMilitaryTime(value: boolean): TimePickerAttribute;
    loop(value: boolean): TimePickerAttribute;
    disappearTextStyle(value: PickerTextStyle): TimePickerAttribute;
    textStyle(value: PickerTextStyle): TimePickerAttribute;
    selectedTextStyle(value: PickerTextStyle): TimePickerAttribute;
    dateTimeOptions(value: DateTimeOptions): TimePickerAttribute;
    onChange(value: ((value: TimePickerResult) => void)): TimePickerAttribute;
    enableHapticFeedback(value: boolean): TimePickerAttribute;
    _onChangeEvent_selected(callback_: ((parameter: Date) => void)): void;
}
declare interface TimePickerDialogOptions extends TimePickerOptions {
    useMilitaryTime?: boolean;
    disappearTextStyle?: PickerTextStyle;
    textStyle?: PickerTextStyle;
    acceptButtonStyle?: PickerDialogButtonStyle;
    cancelButtonStyle?: PickerDialogButtonStyle;
    selectedTextStyle?: PickerTextStyle;
    maskRect?: Rectangle;
    alignment?: DialogAlignment;
    offset?: Offset;
    onAccept?: ((value: TimePickerResult) => void);
    onCancel?: (() => void);
    onChange?: ((value: TimePickerResult) => void);
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    onDidAppear?: (() => void);
    onDidDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
    shadow?: (ShadowOptions|ShadowStyle);
    dateTimeOptions?: DateTimeOptions;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
}
declare class TimePickerDialog {
}
declare enum ToggleType {
    CHECKBOX = 0,
    Checkbox = 0,
    SWITCH = 1,
    Switch = 1,
    BUTTON = 2,
    Button = 2,
}
declare interface SwitchStyle {
    pointRadius?: (number|Resource);
    unselectedColor?: ResourceColor;
    pointColor?: ResourceColor;
    trackBorderRadius?: (number|Resource);
}
declare interface ToggleConfiguration extends CommonConfiguration<ToggleConfiguration> {
    isOn: boolean;
    enabled: boolean;
    triggerChange: ((parameter: boolean) => void);
}
declare interface ToggleOptions {
    type: ToggleType;
    isOn?: boolean;
}
declare interface ToggleInterface {
    (options: ToggleOptions): ToggleAttribute;
}
declare class ToggleAttribute extends CommonMethod<ToggleAttribute> {
    onChange(value: ((parameter: boolean) => void)): ToggleAttribute;
    contentModifier(value: ContentModifier<ToggleConfiguration>): ToggleAttribute;
    selectedColor(value: ResourceColor): ToggleAttribute;
    switchPointColor(value: ResourceColor): ToggleAttribute;
    switchStyle(value: SwitchStyle): ToggleAttribute;
    _onChangeEvent_isOn(callback_: ((parameter: boolean) => void)): void;
}
declare interface CustomTheme {
    _CustomThemeStub: string;
}
declare interface WithThemeOptions {
    theme?: CustomTheme;
    colorMode?: ThemeColorMode;
}
declare type WithThemeInterface = ((options: WithThemeOptions) => WithThemeAttribute);
declare class WithThemeAttribute {
}
declare interface Resource {
    bundleName: string;
    moduleName: string;
    id: number;
    params?: string[];
    type?: number;
}
declare type Length = (string|number|Resource);
declare type PX = string;
declare type VP = (string|number);
declare type FP = string;
declare type LPX = string;
declare type Percentage = string;
declare type Degree = string;
declare type Dimension = (PX|VP|FP|LPX|Percentage|Resource);
declare type ResourceStr = (string|Resource);
declare type Padding = { top?: Length, right?: Length, bottom?: Length, left?: Length }
declare interface LocalizedPadding {
    top?: LengthMetrics;
    end?: LengthMetrics;
    bottom?: LengthMetrics;
    start?: LengthMetrics;
}
declare type Margin = Padding;
declare type EdgeWidth = EdgeWidths;
declare type EdgeWidths = { top?: Length, right?: Length, bottom?: Length, left?: Length }
declare interface LocalizedEdgeWidths {
    top?: LengthMetrics;
    end?: LengthMetrics;
    bottom?: LengthMetrics;
    start?: LengthMetrics;
}
declare type EdgeOutlineWidths = { top?: Dimension, right?: Dimension, bottom?: Dimension, left?: Dimension }
declare type BorderRadiuses = { topLeft?: Length, topRight?: Length, bottomLeft?: Length, bottomRight?: Length }
declare interface LocalizedBorderRadiuses {
    topStart?: LengthMetrics;
    topEnd?: LengthMetrics;
    bottomStart?: LengthMetrics;
    bottomEnd?: LengthMetrics;
}
declare type OutlineRadiuses = { topLeft?: Dimension, topRight?: Dimension, bottomLeft?: Dimension, bottomRight?: Dimension }
declare type EdgeColors = { top?: ResourceColor, right?: ResourceColor, bottom?: ResourceColor, left?: ResourceColor }
declare interface LocalizedEdgeColors {
    top?: ResourceColor;
    end?: ResourceColor;
    bottom?: ResourceColor;
    start?: ResourceColor;
}
declare type LocalizedMargin = LocalizedPadding;
declare type EdgeStyles = { top?: BorderStyle, right?: BorderStyle, bottom?: BorderStyle, left?: BorderStyle }
declare type EdgeOutlineStyles = { top?: OutlineStyle, right?: OutlineStyle, bottom?: OutlineStyle, left?: OutlineStyle }
declare type Offset = { dx: Length, dy: Length }
declare type ResourceColor = (Color|number|string|Resource);
declare type LengthConstrain = { minLength: Length, maxLength: Length }
declare type VoidCallback = (() => void);
declare interface LengthMetricsUnit {
    _LengthMetricsUnitStub: string;
}
declare interface Font {
    size?: Length;
    weight?: (FontWeight|number|string);
    family?: (string|Resource);
    style?: FontStyle;
}
declare interface Area {
    width: Length;
    height: Length;
    position: Position;
    globalPosition: Position;
}
declare interface Position {
    x?: Length;
    y?: Length;
}
declare interface LocalizedPosition {
    start?: LengthMetrics;
    top?: LengthMetrics;
}
declare interface Edges {
    top?: Dimension;
    left?: Dimension;
    bottom?: Dimension;
    right?: Dimension;
}
declare interface LocalizedEdges {
    top?: LengthMetrics;
    start?: LengthMetrics;
    bottom?: LengthMetrics;
    end?: LengthMetrics;
}
declare interface Bias {
    horizontal?: number;
    vertical?: number;
}
declare interface ConstraintSizeOptions {
    minWidth?: Length;
    maxWidth?: Length;
    minHeight?: Length;
    maxHeight?: Length;
}
declare interface SizeOptions {
    width?: Length;
    height?: Length;
}
declare interface BorderOptions {
    width?: (EdgeWidths|Length|LocalizedEdgeWidths);
    color?: (EdgeColors|ResourceColor|LocalizedEdgeColors);
    radius?: (BorderRadiuses|Length|LocalizedBorderRadiuses);
    style?: (EdgeStyles|BorderStyle);
    dashGap?: (EdgeWidths|LengthMetrics|LocalizedEdgeWidths);
    dashWidth?: (EdgeWidths|LengthMetrics|LocalizedEdgeWidths);
}
declare interface OutlineOptions {
    width?: (EdgeOutlineWidths|Dimension);
    color?: (EdgeColors|ResourceColor|LocalizedEdgeColors);
    radius?: (OutlineRadiuses|Dimension);
    style?: (EdgeOutlineStyles|OutlineStyle);
}
declare interface MarkStyle {
    strokeColor?: ResourceColor;
    size?: Length;
    strokeWidth?: Length;
}
declare class ColorFilter {
    constructor(value: number[]);
}
declare interface TouchPoint {
    x: Dimension;
    y: Dimension;
}
declare interface DirectionalEdgesT {
    start: number;
    end: number;
    top: number;
    bottom: number;
}
declare interface DividerStyleOptions {
    strokeWidth?: LengthMetrics;
    color?: ResourceColor;
    startMargin?: LengthMetrics;
    endMargin?: LengthMetrics;
}
declare interface ChainWeightOptions {
    horizontal?: number;
    vertical?: number;
}
declare interface AccessibilityOptions {
    accessibilityPreferred?: boolean;
}
declare enum SeekMode {
    PREVIOUS_KEYFRAME = 0,
    PreviousKeyframe = 0,
    NEXT_KEYFRAME = 1,
    NextKeyframe = 1,
    CLOSEST_KEYFRAME = 2,
    ClosestKeyframe = 2,
    ACCURATE = 3,
    Accurate = 3,
}
declare enum PlaybackSpeed {
    SPEED_FORWARD_0_75_X = 0,
    Speed_Forward_0_75_X = 0,
    SPEED_FORWARD_1_00_X = 1,
    Speed_Forward_1_00_X = 1,
    SPEED_FORWARD_1_25_X = 2,
    Speed_Forward_1_25_X = 2,
    SPEED_FORWARD_1_75_X = 3,
    Speed_Forward_1_75_X = 3,
    SPEED_FORWARD_2_00_X = 4,
    Speed_Forward_2_00_X = 4,
}
declare interface FullscreenInfo {
    fullscreen: boolean;
}
declare interface PreparedInfo {
    duration: number;
}
declare interface PlaybackInfo {
    time: number;
}
declare interface VideoOptions {
    src?: (string|Resource);
    currentProgressRate?: (number|string|PlaybackSpeed);
    previewUri?: (string|PixelMap|Resource);
    controller?: VideoController;
    imageAIOptions?: ImageAIOptions;
}
declare class VideoController {
    constructor();
    start(): void;
    pause(): void;
    stop(): void;
    setCurrentTime(value: number): void;
    requestFullscreen(value: boolean): void;
    exitFullscreen(): void;
    setCurrentTime(value: number, seekMode: SeekMode): void;
    reset(): void;
}
declare interface VideoInterface {
    (value: VideoOptions): VideoAttribute;
}
declare type Callback_FullscreenInfo_Void = ((parameter: FullscreenInfo) => void);
declare type Callback_PreparedInfo_Void = ((parameter: PreparedInfo) => void);
declare type Callback_PlaybackInfo_Void = ((parameter: PlaybackInfo) => void);
declare class VideoAttribute extends CommonMethod<VideoAttribute> {
    muted(value: boolean): VideoAttribute;
    autoPlay(value: boolean): VideoAttribute;
    controls(value: boolean): VideoAttribute;
    loop(value: boolean): VideoAttribute;
    objectFit(value: ImageFit): VideoAttribute;
    onStart(value: VoidCallback): VideoAttribute;
    onPause(value: VoidCallback): VideoAttribute;
    onFinish(value: VoidCallback): VideoAttribute;
    onFullscreenChange(value: ((parameter: FullscreenInfo) => void)): VideoAttribute;
    onPrepared(value: ((parameter: PreparedInfo) => void)): VideoAttribute;
    onSeeking(value: ((parameter: PlaybackInfo) => void)): VideoAttribute;
    onSeeked(value: ((parameter: PlaybackInfo) => void)): VideoAttribute;
    onUpdate(value: ((parameter: PlaybackInfo) => void)): VideoAttribute;
    onError(value: (() => void)): VideoAttribute;
    onStop(value: (() => void)): VideoAttribute;
    enableAnalyzer(value: boolean): VideoAttribute;
    analyzerConfig(value: ImageAnalyzerConfig): VideoAttribute;
}
declare type OnNavigationEntryCommittedCallback = ((loadCommittedDetails: LoadCommittedDetails) => void);
declare type OnSslErrorEventCallback = ((sslErrorEvent: SslErrorEvent) => void);
declare type OnLargestContentfulPaintCallback = ((largestContentfulPaint: LargestContentfulPaint) => void);
declare type OnFirstMeaningfulPaintCallback = ((firstMeaningfulPaint: FirstMeaningfulPaint) => void);
declare type OnOverrideUrlLoadingCallback = ((webResourceRequest: WebResourceRequest) => boolean);
declare type OnIntelligentTrackingPreventionCallback = ((details: IntelligentTrackingPreventionDetails) => void);
declare type OnNativeEmbedVisibilityChangeCallback = ((nativeEmbedVisibilityInfo: NativeEmbedVisibilityInfo) => void);
declare interface NativeMediaPlayerConfig {
    enable: boolean;
    shouldOverlay: boolean;
}
declare type OnRenderProcessNotRespondingCallback = ((data: RenderProcessNotRespondingData) => void);
declare type OnRenderProcessRespondingCallback = (() => void);
declare type OnViewportFitChangedCallback = ((viewportFit: ViewportFit) => void);
declare type OnAdsBlockedCallback = ((details: AdsBlockedDetails) => void);
declare interface AdsBlockedDetails {
    url: string;
    adsBlocked: string[];
}
declare interface WebKeyboardOptions {
    useSystemKeyboard: boolean;
    enterKeyType?: number;
    customKeyboard?: CustomBuilder;
}
declare class WebKeyboardController {
    constructor();
    insertText(text: string): void;
    deleteForward(length: number): void;
    deleteBackward(length: number): void;
    sendFunctionKey(key: number): void;
    close(): void;
}
declare interface WebKeyboardCallbackInfo {
    controller: WebKeyboardController;
    attributes: Map<string,string>;
}
declare type WebKeyboardCallback = ((keyboardCallbackInfo: WebKeyboardCallbackInfo) => WebKeyboardOptions);
declare enum MessageLevel {
    DEBUG = 0,
    Debug = 0,
    ERROR = 1,
    Error = 1,
    INFO = 2,
    Info = 2,
    LOG = 3,
    Log = 3,
    WARN = 4,
    Warn = 4,
}
declare enum MixedMode {
    ALL = 0,
    All = 0,
    COMPATIBLE = 1,
    Compatible = 1,
    NONE = 2,
    None = 2,
}
declare type OnSafeBrowsingCheckResultCallback = ((threatType: ThreatType) => void);
declare enum HitTestType {
    EDIT_TEXT = 0,
    EditText = 0,
    EMAIL = 1,
    Email = 1,
    HTTP_ANCHOR = 2,
    HttpAnchor = 2,
    HTTP_ANCHOR_IMG = 3,
    HttpAnchorImg = 3,
    IMG = 4,
    Img = 4,
    MAP = 5,
    Map = 5,
    PHONE = 6,
    Phone = 6,
    UNKNOWN = 7,
    Unknown = 7,
}
declare enum CacheMode {
    DEFAULT = 0,
    Default = 0,
    NONE = 1,
    None = 1,
    ONLINE = 2,
    Online = 2,
    ONLY = 3,
    Only = 3,
}
declare enum OverScrollMode {
    NEVER = 0,
    ALWAYS = 1,
}
declare enum WebDarkMode {
    OFF = 0,
    Off = 0,
    ON = 1,
    On = 1,
    AUTO = 2,
    Auto = 2,
}
declare enum WebCaptureMode {
    HOME_SCREEN = 0,
}
declare enum ThreatType {
    THREAT_ILLEGAL = 0,
    THREAT_FRAUD = 1,
    THREAT_RISK = 2,
    THREAT_WARNING = 3,
}
declare interface WebMediaOptions {
    resumeInterval?: number;
    audioExclusive?: boolean;
}
declare interface ScreenCaptureConfig {
    captureMode: WebCaptureMode;
}
declare class FullScreenExitHandler {
    constructor();
    exitFullScreen(): void;
}
declare interface FullScreenEnterEvent {
    handler: FullScreenExitHandler;
    videoWidth?: number;
    videoHeight?: number;
}
declare type OnFullScreenEnterCallback = ((event: FullScreenEnterEvent) => void);
declare enum RenderExitReason {
    PROCESS_ABNORMAL_TERMINATION = 0,
    ProcessAbnormalTermination = 0,
    PROCESS_WAS_KILLED = 1,
    ProcessWasKilled = 1,
    PROCESS_CRASHED = 2,
    ProcessCrashed = 2,
    PROCESS_OOM = 3,
    ProcessOom = 3,
    PROCESS_EXIT_UNKNOWN = 4,
    ProcessExitUnknown = 4,
}
declare type OnContextMenuHideCallback = (() => void);
declare enum SslError {
    INVALID = 0,
    Invalid = 0,
    HOST_MISMATCH = 1,
    HostMismatch = 1,
    DATE_INVALID = 2,
    DateInvalid = 2,
    UNTRUSTED = 3,
    Untrusted = 3,
}
declare enum FileSelectorMode {
    FILE_OPEN_MODE = 0,
    FileOpenMode = 0,
    FILE_OPEN_MULTIPLE_MODE = 1,
    FileOpenMultipleMode = 1,
    FILE_OPEN_FOLDER_MODE = 2,
    FileOpenFolderMode = 2,
    FILE_SAVE_MODE = 3,
    FileSaveMode = 3,
}
declare enum WebLayoutMode {
    NONE = 0,
    FIT_CONTENT = 1,
}
declare enum RenderProcessNotRespondingReason {
    INPUT_TIMEOUT = 0,
    NAVIGATION_COMMIT_TIMEOUT = 1,
}
declare class FileSelectorParam {
    constructor();
    getTitle(): string;
    getMode(): FileSelectorMode;
    getAcceptType(): string[];
    isCapture(): boolean;
}
declare class JsResult {
    constructor();
    handleCancel(): void;
    handleConfirm(): void;
    handlePromptConfirm(result: string): void;
}
declare class FileSelectorResult {
    constructor();
    handleFileList(fileList: string[]): void;
}
declare class HttpAuthHandler {
    constructor();
    confirm(userName: string, password: string): boolean;
    cancel(): void;
    isHttpAuthInfoSaved(): boolean;
}
declare class SslErrorHandler {
    constructor();
    handleConfirm(): void;
    handleCancel(): void;
}
declare class ClientAuthenticationHandler {
    constructor();
    confirm(priKeyFile: string, certChainFile: string): void;
    confirm(authUri: string): void;
    cancel(): void;
    ignore(): void;
}
declare enum ProtectedResourceType {
    MIDI_SYSEX = "TYPE_MIDI_SYSEX",
    MidiSysex = "TYPE_MIDI_SYSEX",
    VIDEO_CAPTURE = "TYPE_VIDEO_CAPTURE",
    AUDIO_CAPTURE = "TYPE_AUDIO_CAPTURE",
    SENSOR = "TYPE_SENSOR",
}
declare class PermissionRequest {
    constructor();
    deny(): void;
    getOrigin(): string;
    getAccessibleResource(): string[];
    grant(resources: string[]): void;
}
declare class ScreenCaptureHandler {
    constructor();
    getOrigin(): string;
    grant(config: ScreenCaptureConfig): void;
    deny(): void;
}
declare class DataResubmissionHandler {
    constructor();
    resend(): void;
    cancel(): void;
}
declare class ControllerHandler {
    constructor();
    setWebController(controller: WebviewController): void;
}
declare enum ContextMenuSourceType {
    NONE = 0,
    None = 0,
    MOUSE = 1,
    Mouse = 1,
    LONG_PRESS = 2,
    LongPress = 2,
}
declare enum ContextMenuMediaType {
    NONE = 0,
    None = 0,
    IMAGE = 1,
    Image = 1,
}
declare enum ContextMenuInputFieldType {
    NONE = 0,
    None = 0,
    PLAIN_TEXT = 1,
    PlainText = 1,
    PASSWORD = 2,
    Password = 2,
    NUMBER = 3,
    Number = 3,
    TELEPHONE = 4,
    Telephone = 4,
    OTHER = 5,
    Other = 5,
}
declare enum NativeEmbedStatus {
    CREATE = 0,
    UPDATE = 1,
    DESTROY = 2,
    ENTER_BFCACHE = 3,
    LEAVE_BFCACHE = 4,
}
declare enum ContextMenuEditStateFlags {
    NONE = 0,
    CAN_CUT = 1,
    CAN_COPY = 2,
    CAN_PASTE = 4,
    CAN_SELECT_ALL = 8,
}
declare enum WebNavigationType {
    UNKNOWN = 0,
    MAIN_FRAME_NEW_ENTRY = 1,
    MAIN_FRAME_EXISTING_ENTRY = 2,
    NAVIGATION_TYPE_NEW_SUBFRAME = 4,
    NAVIGATION_TYPE_AUTO_SUBFRAME = 5,
}
declare enum RenderMode {
    ASYNC_RENDER = 0,
    SYNC_RENDER = 1,
}
declare enum ViewportFit {
    AUTO = 0,
    CONTAINS = 1,
    COVER = 2,
}
declare class WebContextMenuParam {
    constructor();
    x(): number;
    y(): number;
    getLinkUrl(): string;
    getUnfilteredLinkUrl(): string;
    getSourceUrl(): string;
    existsImageContents(): boolean;
    getMediaType(): ContextMenuMediaType;
    getSelectionText(): string;
    getSourceType(): ContextMenuSourceType;
    getInputFieldType(): ContextMenuInputFieldType;
    isEditable(): boolean;
    getEditStateFlags(): number;
    getPreviewWidth(): number;
    getPreviewHeight(): number;
}
declare class WebContextMenuResult {
    constructor();
    closeContextMenu(): void;
    copyImage(): void;
    copy(): void;
    paste(): void;
    cut(): void;
    selectAll(): void;
}
declare class ConsoleMessage {
    constructor(message: string, sourceId: string, lineNumber: number, messageLevel: MessageLevel);
    constructor();
    getMessage(): string;
    getSourceId(): string;
    getLineNumber(): number;
    getMessageLevel(): MessageLevel;
}
declare class WebResourceRequest {
    constructor();
    getRequestHeader(): Header[];
    getRequestUrl(): string;
    isRequestGesture(): boolean;
    isMainFrame(): boolean;
    isRedirect(): boolean;
    getRequestMethod(): string;
}
declare class WebResourceResponse {
    constructor();
    getResponseData(): string;
    getResponseDataEx(): (string|number|ArrayBuffer|Resource) | undefined;
    getResponseEncoding(): string;
    getResponseMimeType(): string;
    getReasonMessage(): string;
    getResponseHeader(): Header[];
    getResponseCode(): number;
    setResponseData(data: (string|number|Resource|ArrayBuffer)): void;
    setResponseEncoding(encoding: string): void;
    setResponseMimeType(mimeType: string): void;
    setReasonMessage(reason: string): void;
    setResponseHeader(header: Header[]): void;
    setResponseCode(code: number): void;
    setResponseIsReady(IsReady: boolean): void;
    getResponseIsReady(): boolean;
}
declare interface Header {
    headerKey: string;
    headerValue: string;
}
declare class WebResourceError {
    constructor();
    getErrorInfo(): string;
    getErrorCode(): number;
}
declare class JsGeolocation {
    constructor();
    invoke(origin: string, allow: boolean, retain: boolean): void;
}
declare class WebCookie {
    constructor();
    setCookie(): void;
    saveCookie(): void;
}
declare class EventResult {
    constructor();
    setGestureEventResult(result: boolean): void;
}
declare type Literal_String_script_Callback_String_Void_callback_ = { script: string, callback_?: ((breakpoints: string) => void) }
declare type Literal_String_baseUrl_data_encoding_historyUrl_mimeType = { data: string, mimeType: string, encoding: string, baseUrl?: string, historyUrl?: string }
declare type Literal_Union_String_Resource_url_Array_Header_headers = { url: (string|Resource), headers?: Header[] }
declare type Literal_Object_object__String_name_Array_String_methodList = { object_: Object, name: string, methodList: string[] }
declare class WebController {
    constructor();
    onInactive(): void;
    onActive(): void;
    zoom(factor: number): void;
    clearHistory(): void;
    runJavaScript(options: { script: string, callback_?: ((breakpoints: string) => void) }): void;
    loadData(options: { data: string, mimeType: string, encoding: string, baseUrl?: string, historyUrl?: string }): void;
    loadUrl(options: { url: (string|Resource), headers?: Header[] }): void;
    refresh(): void;
    stop(): void;
    registerJavaScriptProxy(options: { object_: Object, name: string, methodList: string[] }): void;
    deleteJavaScriptRegister(name: string): void;
    getHitTest(): HitTestType;
    requestFocus(): void;
    accessBackward(): boolean;
    accessForward(): boolean;
    accessStep(step: number): boolean;
    backward(): void;
    forward(): void;
    getCookieManager(): WebCookie;
}
declare interface WebOptions {
    src: (string|Resource);
    controller: (WebController|WebviewController);
    renderMode?: RenderMode;
    incognitoMode?: boolean;
    sharedRenderProcessToken?: string;
}
declare interface ScriptItem {
    script: string;
    scriptRules: string[];
}
declare interface LoadCommittedDetails {
    isMainFrame: boolean;
    isSameDocument: boolean;
    didReplaceEntry: boolean;
    navigationType: WebNavigationType;
    url: string;
}
declare interface IntelligentTrackingPreventionDetails {
    host: string;
    trackerHost: string;
}
declare interface WebInterface {
    (value: WebOptions): WebAttribute;
}
declare interface NativeEmbedInfo {
    id?: string;
    type?: string;
    src?: string;
    position?: Position;
    width?: number;
    height?: number;
    url?: string;
    tag?: string;
    params?: Map<string,string>;
}
declare interface NativeEmbedDataInfo {
    status?: NativeEmbedStatus;
    surfaceId?: string;
    embedId?: string;
    info?: NativeEmbedInfo;
}
declare interface NativeEmbedVisibilityInfo {
    visibility: boolean;
    embedId: string;
}
declare interface NativeEmbedTouchInfo {
    embedId?: string;
    touchEvent?: TouchEvent;
    result?: EventResult;
}
declare interface FirstMeaningfulPaint {
    navigationStartTime?: number;
    firstMeaningfulPaintTime?: number;
}
declare interface LargestContentfulPaint {
    navigationStartTime?: number;
    largestImagePaintTime?: number;
    largestTextPaintTime?: number;
    imageBPP?: number;
    largestImageLoadStartTime?: number;
    largestImageLoadEndTime?: number;
}
declare interface RenderProcessNotRespondingData {
    jsStack: string;
    pid: number;
    reason: RenderProcessNotRespondingReason;
}
declare interface OnPageEndEvent {
    url: string;
}
declare interface OnPageBeginEvent {
    url: string;
}
declare interface OnProgressChangeEvent {
    newProgress: number;
}
declare interface OnTitleReceiveEvent {
    title: string;
}
declare interface OnGeolocationShowEvent {
    origin: string;
    geolocation: JsGeolocation;
}
declare interface OnAlertEvent {
    url: string;
    message: string;
    result: JsResult;
}
declare interface OnBeforeUnloadEvent {
    url: string;
    message: string;
    result: JsResult;
}
declare interface OnConfirmEvent {
    url: string;
    message: string;
    result: JsResult;
}
declare interface OnPromptEvent {
    url: string;
    message: string;
    value: string;
    result: JsResult;
}
declare interface OnConsoleEvent {
    message: ConsoleMessage;
}
declare interface OnErrorReceiveEvent {
    request: WebResourceRequest;
    error: WebResourceError;
}
declare interface OnHttpErrorReceiveEvent {
    request: WebResourceRequest;
    response: WebResourceResponse;
}
declare interface OnDownloadStartEvent {
    url: string;
    userAgent: string;
    contentDisposition: string;
    mimetype: string;
    contentLength: number;
}
declare interface OnRefreshAccessedHistoryEvent {
    url: string;
    isRefreshed: boolean;
}
declare interface OnRenderExitedEvent {
    renderExitReason: RenderExitReason;
}
declare interface OnShowFileSelectorEvent {
    result: FileSelectorResult;
    fileSelector: FileSelectorParam;
}
declare interface OnResourceLoadEvent {
    url: string;
}
declare interface OnScaleChangeEvent {
    oldScale: number;
    newScale: number;
}
declare interface OnHttpAuthRequestEvent {
    handler: HttpAuthHandler;
    host: string;
    realm: string;
}
declare interface OnInterceptRequestEvent {
    request: WebResourceRequest;
}
declare interface OnPermissionRequestEvent {
    request: PermissionRequest;
}
declare interface OnScreenCaptureRequestEvent {
    handler: ScreenCaptureHandler;
}
declare interface OnContextMenuShowEvent {
    param: WebContextMenuParam;
    result: WebContextMenuResult;
}
declare interface OnSearchResultReceiveEvent {
    activeMatchOrdinal: number;
    numberOfMatches: number;
    isDoneCounting: boolean;
}
declare interface OnScrollEvent {
    xOffset: number;
    yOffset: number;
}
declare interface OnSslErrorEventReceiveEvent {
    handler: SslErrorHandler;
    error: SslError;
    certChainData?: ArrayBuffer[];
}
declare interface OnClientAuthenticationEvent {
    handler: ClientAuthenticationHandler;
    host: string;
    port: number;
    keyTypes: string[];
    issuers: string[];
}
declare interface OnWindowNewEvent {
    isAlert: boolean;
    isUserTrigger: boolean;
    targetUrl: string;
    handler: ControllerHandler;
}
declare interface OnTouchIconUrlReceivedEvent {
    url: string;
    precomposed: boolean;
}
declare interface OnFaviconReceivedEvent {
    favicon: PixelMap;
}
declare interface OnPageVisibleEvent {
    url: string;
}
declare interface OnDataResubmittedEvent {
    handler: DataResubmissionHandler;
}
declare interface OnAudioStateChangedEvent {
    playing: boolean;
}
declare interface OnFirstContentfulPaintEvent {
    navigationStartTick: number;
    firstContentfulPaintMs: number;
}
declare interface OnLoadInterceptEvent {
    data: WebResourceRequest;
}
declare interface OnOverScrollEvent {
    xOffset: number;
    yOffset: number;
}
declare interface JavaScriptProxy {
    object_: Object;
    name: string;
    methodList: string[];
    controller: (WebController|WebviewController);
    asyncMethodList?: string[];
    permission?: string;
}
declare enum WebKeyboardAvoidMode {
    RESIZE_VISUAL = 0,
    RESIZE_CONTENT = 1,
    OVERLAYS_CONTENT = 2,
}
declare enum WebElementType {
    IMAGE = 1,
}
declare enum WebResponseType {
    LONG_PRESS = 1,
}
declare interface SelectionMenuOptionsExt {
    onAppear?: (() => void);
    onDisappear?: (() => void);
    preview?: CustomBuilder;
    menuType?: MenuType;
}
declare type Callback_OnPageEndEvent_Void = ((parameter: OnPageEndEvent) => void);
declare type Callback_OnPageBeginEvent_Void = ((parameter: OnPageBeginEvent) => void);
declare type Callback_OnProgressChangeEvent_Void = ((parameter: OnProgressChangeEvent) => void);
declare type Callback_OnTitleReceiveEvent_Void = ((parameter: OnTitleReceiveEvent) => void);
declare type Callback_OnGeolocationShowEvent_Void = ((parameter: OnGeolocationShowEvent) => void);
declare type Callback_OnAlertEvent_Boolean = ((parameter: OnAlertEvent) => boolean);
declare type Callback_OnBeforeUnloadEvent_Boolean = ((parameter: OnBeforeUnloadEvent) => boolean);
declare type Callback_OnConfirmEvent_Boolean = ((parameter: OnConfirmEvent) => boolean);
declare type Callback_OnPromptEvent_Boolean = ((parameter: OnPromptEvent) => boolean);
declare type Callback_OnConsoleEvent_Boolean = ((parameter: OnConsoleEvent) => boolean);
declare type Callback_OnErrorReceiveEvent_Void = ((parameter: OnErrorReceiveEvent) => void);
declare type Callback_OnHttpErrorReceiveEvent_Void = ((parameter: OnHttpErrorReceiveEvent) => void);
declare type Callback_OnDownloadStartEvent_Void = ((parameter: OnDownloadStartEvent) => void);
declare type Callback_OnRefreshAccessedHistoryEvent_Void = ((parameter: OnRefreshAccessedHistoryEvent) => void);
declare type Literal_Union_String_WebResourceRequest_data = { data: (string|WebResourceRequest) }
declare type Type_WebAttribute_onUrlLoadIntercept_callback = ((event?: { data: (string|WebResourceRequest) }) => boolean);
declare type Literal_Function_handler_Object_error = { handler: Function, error: Object }
declare type Callback_Literal_Function_handler_Object_error_Void = ((event?: { handler: Function, error: Object }) => void);
declare type Callback_OnRenderExitedEvent_Void = ((parameter: OnRenderExitedEvent) => void);
declare type Callback_OnShowFileSelectorEvent_Boolean = ((parameter: OnShowFileSelectorEvent) => boolean);
declare type Literal_Object_detail = { detail: Object }
declare type Callback_Literal_Object_detail_Boolean = ((event?: { detail: Object }) => boolean);
declare type Literal_Function_callback__Object_fileSelector = { callback_: Function, fileSelector: Object }
declare type Type_WebAttribute_onFileSelectorShow_callback = ((event?: { callback_: Function, fileSelector: Object }) => void);
declare type Callback_OnResourceLoadEvent_Void = ((parameter: OnResourceLoadEvent) => void);
declare type Callback_OnScaleChangeEvent_Void = ((parameter: OnScaleChangeEvent) => void);
declare type Callback_OnHttpAuthRequestEvent_Boolean = ((parameter: OnHttpAuthRequestEvent) => boolean);
declare type Callback_OnInterceptRequestEvent_WebResourceResponse = ((parameter: OnInterceptRequestEvent) => WebResourceResponse);
declare type Callback_OnPermissionRequestEvent_Void = ((parameter: OnPermissionRequestEvent) => void);
declare type Callback_OnScreenCaptureRequestEvent_Void = ((parameter: OnScreenCaptureRequestEvent) => void);
declare type Callback_OnContextMenuShowEvent_Boolean = ((parameter: OnContextMenuShowEvent) => boolean);
declare type Callback_OnSearchResultReceiveEvent_Void = ((parameter: OnSearchResultReceiveEvent) => void);
declare type Callback_OnScrollEvent_Void = ((parameter: OnScrollEvent) => void);
declare type Callback_OnSslErrorEventReceiveEvent_Void = ((parameter: OnSslErrorEventReceiveEvent) => void);
declare type Callback_OnClientAuthenticationEvent_Void = ((parameter: OnClientAuthenticationEvent) => void);
declare type Callback_OnWindowNewEvent_Void = ((parameter: OnWindowNewEvent) => void);
declare type Callback_OnTouchIconUrlReceivedEvent_Void = ((parameter: OnTouchIconUrlReceivedEvent) => void);
declare type Callback_OnFaviconReceivedEvent_Void = ((parameter: OnFaviconReceivedEvent) => void);
declare type Callback_OnPageVisibleEvent_Void = ((parameter: OnPageVisibleEvent) => void);
declare type Callback_OnDataResubmittedEvent_Void = ((parameter: OnDataResubmittedEvent) => void);
declare type Callback_OnAudioStateChangedEvent_Void = ((parameter: OnAudioStateChangedEvent) => void);
declare type Callback_OnFirstContentfulPaintEvent_Void = ((parameter: OnFirstContentfulPaintEvent) => void);
declare type Callback_OnLoadInterceptEvent_Boolean = ((parameter: OnLoadInterceptEvent) => boolean);
declare type Callback_OnOverScrollEvent_Void = ((parameter: OnOverScrollEvent) => void);
declare type Callback_NativeEmbedDataInfo_Void = ((event: NativeEmbedDataInfo) => void);
declare type Callback_NativeEmbedTouchInfo_Void = ((event: NativeEmbedTouchInfo) => void);
declare class WebAttribute extends CommonMethod<WebAttribute> {
    javaScriptAccess(value: boolean): WebAttribute;
    fileAccess(value: boolean): WebAttribute;
    onlineImageAccess(value: boolean): WebAttribute;
    domStorageAccess(value: boolean): WebAttribute;
    imageAccess(value: boolean): WebAttribute;
    mixedMode(value: MixedMode): WebAttribute;
    zoomAccess(value: boolean): WebAttribute;
    geolocationAccess(value: boolean): WebAttribute;
    javaScriptProxy(value: JavaScriptProxy): WebAttribute;
    password(value: boolean): WebAttribute;
    cacheMode(value: CacheMode): WebAttribute;
    darkMode(value: WebDarkMode): WebAttribute;
    forceDarkAccess(value: boolean): WebAttribute;
    mediaOptions(value: WebMediaOptions): WebAttribute;
    tableData(value: boolean): WebAttribute;
    wideViewModeAccess(value: boolean): WebAttribute;
    overviewModeAccess(value: boolean): WebAttribute;
    overScrollMode(value: OverScrollMode): WebAttribute;
    textZoomAtio(value: number): WebAttribute;
    textZoomRatio(value: number): WebAttribute;
    databaseAccess(value: boolean): WebAttribute;
    initialScale(value: number): WebAttribute;
    userAgent(value: string): WebAttribute;
    metaViewport(value: boolean): WebAttribute;
    onPageEnd(value: ((parameter: OnPageEndEvent) => void)): WebAttribute;
    onPageBegin(value: ((parameter: OnPageBeginEvent) => void)): WebAttribute;
    onProgressChange(value: ((parameter: OnProgressChangeEvent) => void)): WebAttribute;
    onTitleReceive(value: ((parameter: OnTitleReceiveEvent) => void)): WebAttribute;
    onGeolocationHide(value: (() => void)): WebAttribute;
    onGeolocationShow(value: ((parameter: OnGeolocationShowEvent) => void)): WebAttribute;
    onRequestSelected(value: (() => void)): WebAttribute;
    onAlert(value: ((parameter: OnAlertEvent) => boolean)): WebAttribute;
    onBeforeUnload(value: ((parameter: OnBeforeUnloadEvent) => boolean)): WebAttribute;
    onConfirm(value: ((parameter: OnConfirmEvent) => boolean)): WebAttribute;
    onPrompt(value: ((parameter: OnPromptEvent) => boolean)): WebAttribute;
    onConsole(value: ((parameter: OnConsoleEvent) => boolean)): WebAttribute;
    onErrorReceive(value: ((parameter: OnErrorReceiveEvent) => void)): WebAttribute;
    onHttpErrorReceive(value: ((parameter: OnHttpErrorReceiveEvent) => void)): WebAttribute;
    onDownloadStart(value: ((parameter: OnDownloadStartEvent) => void)): WebAttribute;
    onRefreshAccessedHistory(value: ((parameter: OnRefreshAccessedHistoryEvent) => void)): WebAttribute;
    onUrlLoadIntercept(value: ((event?: { data: (string|WebResourceRequest) }) => boolean)): WebAttribute;
    onSslErrorReceive(value: ((event?: { handler: Function, error: Object }) => void)): WebAttribute;
    onRenderExited(value: ((parameter: OnRenderExitedEvent) => void)): WebAttribute;
    onShowFileSelector(value: ((parameter: OnShowFileSelectorEvent) => boolean)): WebAttribute;
    onRenderExited(value: ((event?: { detail: Object }) => boolean)): WebAttribute;
    onFileSelectorShow(value: ((event?: { callback_: Function, fileSelector: Object }) => void)): WebAttribute;
    onResourceLoad(value: ((parameter: OnResourceLoadEvent) => void)): WebAttribute;
    onFullScreenExit(value: (() => void)): WebAttribute;
    onFullScreenEnter(value: OnFullScreenEnterCallback): WebAttribute;
    onScaleChange(value: ((parameter: OnScaleChangeEvent) => void)): WebAttribute;
    onHttpAuthRequest(value: ((parameter: OnHttpAuthRequestEvent) => boolean)): WebAttribute;
    onInterceptRequest(value: ((parameter: OnInterceptRequestEvent) => WebResourceResponse)): WebAttribute;
    onPermissionRequest(value: ((parameter: OnPermissionRequestEvent) => void)): WebAttribute;
    onScreenCaptureRequest(value: ((parameter: OnScreenCaptureRequestEvent) => void)): WebAttribute;
    onContextMenuShow(value: ((parameter: OnContextMenuShowEvent) => boolean)): WebAttribute;
    onContextMenuHide(value: OnContextMenuHideCallback): WebAttribute;
    mediaPlayGestureAccess(value: boolean): WebAttribute;
    onSearchResultReceive(value: ((parameter: OnSearchResultReceiveEvent) => void)): WebAttribute;
    onScroll(value: ((parameter: OnScrollEvent) => void)): WebAttribute;
    onSslErrorEventReceive(value: ((parameter: OnSslErrorEventReceiveEvent) => void)): WebAttribute;
    onSslErrorEvent(value: OnSslErrorEventCallback): WebAttribute;
    onClientAuthenticationRequest(value: ((parameter: OnClientAuthenticationEvent) => void)): WebAttribute;
    onWindowNew(value: ((parameter: OnWindowNewEvent) => void)): WebAttribute;
    onWindowExit(value: (() => void)): WebAttribute;
    multiWindowAccess(value: boolean): WebAttribute;
    onInterceptKeyEvent(value: ((parameter: KeyEvent) => boolean)): WebAttribute;
    webStandardFont(value: string): WebAttribute;
    webSerifFont(value: string): WebAttribute;
    webSansSerifFont(value: string): WebAttribute;
    webFixedFont(value: string): WebAttribute;
    webFantasyFont(value: string): WebAttribute;
    webCursiveFont(value: string): WebAttribute;
    defaultFixedFontSize(value: number): WebAttribute;
    defaultFontSize(value: number): WebAttribute;
    minFontSize(value: number): WebAttribute;
    minLogicalFontSize(value: number): WebAttribute;
    defaultTextEncodingFormat(value: string): WebAttribute;
    forceDisplayScrollBar(value: boolean): WebAttribute;
    blockNetwork(value: boolean): WebAttribute;
    horizontalScrollBarAccess(value: boolean): WebAttribute;
    verticalScrollBarAccess(value: boolean): WebAttribute;
    onTouchIconUrlReceived(value: ((parameter: OnTouchIconUrlReceivedEvent) => void)): WebAttribute;
    onFaviconReceived(value: ((parameter: OnFaviconReceivedEvent) => void)): WebAttribute;
    onPageVisible(value: ((parameter: OnPageVisibleEvent) => void)): WebAttribute;
    onDataResubmitted(value: ((parameter: OnDataResubmittedEvent) => void)): WebAttribute;
    pinchSmooth(value: boolean): WebAttribute;
    allowWindowOpenMethod(value: boolean): WebAttribute;
    onAudioStateChanged(value: ((parameter: OnAudioStateChangedEvent) => void)): WebAttribute;
    onFirstContentfulPaint(value: ((parameter: OnFirstContentfulPaintEvent) => void)): WebAttribute;
    onFirstMeaningfulPaint(value: OnFirstMeaningfulPaintCallback): WebAttribute;
    onLargestContentfulPaint(value: OnLargestContentfulPaintCallback): WebAttribute;
    onLoadIntercept(value: ((parameter: OnLoadInterceptEvent) => boolean)): WebAttribute;
    onControllerAttached(value: (() => void)): WebAttribute;
    onOverScroll(value: ((parameter: OnOverScrollEvent) => void)): WebAttribute;
    onSafeBrowsingCheckResult(value: OnSafeBrowsingCheckResultCallback): WebAttribute;
    onNavigationEntryCommitted(value: OnNavigationEntryCommittedCallback): WebAttribute;
    onIntelligentTrackingPreventionResult(value: OnIntelligentTrackingPreventionCallback): WebAttribute;
    javaScriptOnDocumentStart(value: ScriptItem[]): WebAttribute;
    javaScriptOnDocumentEnd(value: ScriptItem[]): WebAttribute;
    layoutMode(value: WebLayoutMode): WebAttribute;
    nestedScroll(value: (NestedScrollOptions|NestedScrollOptionsExt)): WebAttribute;
    enableNativeEmbedMode(value: boolean): WebAttribute;
    onNativeEmbedLifecycleChange(value: ((event: NativeEmbedDataInfo) => void)): WebAttribute;
    onNativeEmbedVisibilityChange(value: OnNativeEmbedVisibilityChangeCallback): WebAttribute;
    onNativeEmbedGestureEvent(value: ((event: NativeEmbedTouchInfo) => void)): WebAttribute;
    copyOptions(value: CopyOptions): WebAttribute;
    onOverrideUrlLoading(value: OnOverrideUrlLoadingCallback): WebAttribute;
    textAutosizing(value: boolean): WebAttribute;
    enableNativeMediaPlayer(value: NativeMediaPlayerConfig): WebAttribute;
    enableSmoothDragResize(value: boolean): WebAttribute;
    onRenderProcessNotResponding(value: OnRenderProcessNotRespondingCallback): WebAttribute;
    onRenderProcessResponding(value: OnRenderProcessRespondingCallback): WebAttribute;
    selectionMenuOptions(value: ExpandedMenuItemOptions[]): WebAttribute;
    onViewportFitChanged(value: OnViewportFitChangedCallback): WebAttribute;
    onInterceptKeyboardAttach(value: WebKeyboardCallback): WebAttribute;
    onAdsBlocked(value: OnAdsBlockedCallback): WebAttribute;
    keyboardAvoidMode(value: WebKeyboardAvoidMode): WebAttribute;
    editMenuOptions(value: EditMenuOptions): WebAttribute;
    enableHapticFeedback(value: boolean): WebAttribute;
    registerNativeEmbedRule(tag: string, type: string): WebAttribute;
    bindSelectionMenu(elementType: WebElementType, content: CustomBuilder, responseType: WebResponseType, options?: SelectionMenuOptionsExt): WebAttribute;
}
declare interface SslErrorEvent {
    handler: SslErrorHandler;
    error: SslError;
    url: string;
    originalUrl: string;
    referrer: string;
    isFatalError: boolean;
    isMainFrame: boolean;
}
declare type Literal_String_plainText = { plainText: string }
declare type Callback_Literal_String_plainText_Void = ((selectedText: { plainText: string }) => void);
declare interface ExpandedMenuItemOptions {
    content: ResourceStr;
    startIcon?: ResourceStr;
    action: ((selectedText: { plainText: string }) => void);
}
declare interface NestedScrollOptionsExt {
    scrollUp?: NestedScrollMode;
    scrollDown?: NestedScrollMode;
    scrollRight?: NestedScrollMode;
    scrollLeft?: NestedScrollMode;
}
declare interface WindowSceneInterface {
    (persistentId: number): WindowSceneAttribute;
}
declare class WindowSceneAttribute extends CommonMethod<WindowSceneAttribute> {
    attractionEffect(destination: Position, fraction: number): WindowSceneAttribute;
}
declare interface SurfaceRect {
    offsetX?: number;
    offsetY?: number;
    surfaceWidth: number;
    surfaceHeight: number;
}
declare interface SurfaceRotationOptions {
    lock?: boolean;
}
declare type Literal_Number_surfaceHeight_surfaceWidth = { surfaceWidth: number, surfaceHeight: number }
declare class XComponentController {
    constructor();
    getXComponentSurfaceId(): string;
    getXComponentContext(): Object;
    setXComponentSurfaceSize(value: { surfaceWidth: number, surfaceHeight: number }): void;
    setXComponentSurfaceRect(rect: SurfaceRect): void;
    getXComponentSurfaceRect(): SurfaceRect;
    setXComponentSurfaceRotation(rotationOptions: SurfaceRotationOptions): void;
    getXComponentSurfaceRotation(): SurfaceRotationOptions;
    onSurfaceCreated(surfaceId: string): void;
    onSurfaceChanged(surfaceId: string, rect: SurfaceRect): void;
    onSurfaceDestroyed(surfaceId: string): void;
    startImageAnalyzer(config: ImageAnalyzerConfig): Promise<void>;
    stopImageAnalyzer(): void;
}
declare interface XComponentOptions {
    type: XComponentType;
    controller: XComponentController;
    imageAIOptions?: ImageAIOptions;
}
declare type Type_XComponentInterface_value = { id: string, type: string, libraryname?: string, controller?: XComponentController }
declare interface XComponentInterface {
    (value: { id: string, type: string, libraryname?: string, controller?: XComponentController }): XComponentAttribute;
    (value: { id: string, type: string, libraryname?: string, controller?: XComponentController }): XComponentAttribute;
    (options: XComponentOptions): XComponentAttribute;
}
declare type OnNativeLoadCallback = ((event?: Object) => void);
declare class XComponentAttribute extends CommonMethod<XComponentAttribute> {
    onLoad(value: OnNativeLoadCallback): XComponentAttribute;
    onDestroy(value: VoidCallback): XComponentAttribute;
    enableAnalyzer(value: boolean): XComponentAttribute;
    enableSecure(value: boolean): XComponentAttribute;
}
declare enum SideBarContainerType {
    EMBED = 0,
    Embed = 0,
    OVERLAY = 1,
    Overlay = 1,
    AUTO = 2,
}
declare enum SideBarPosition {
    START = 0,
    Start = 0,
    END = 1,
    End = 1,
}
declare interface ButtonIconOptions {
    shown: (string|PixelMap|Resource);
    hidden: (string|PixelMap|Resource);
    switching?: (string|PixelMap|Resource);
}
declare interface ButtonStyle {
    left?: number;
    top?: number;
    width?: number;
    height?: number;
    icons?: ButtonIconOptions;
}
declare interface SideBarContainerInterface {
    (type?: SideBarContainerType): SideBarContainerAttribute;
}
declare class SideBarContainerAttribute extends CommonMethod<SideBarContainerAttribute> {
    showSideBar(value: boolean): SideBarContainerAttribute;
    controlButton(value: ButtonStyle): SideBarContainerAttribute;
    showControlButton(value: boolean): SideBarContainerAttribute;
    onChange(value: ((parameter: boolean) => void)): SideBarContainerAttribute;
    sideBarWidth(value: number): SideBarContainerAttribute;
    minSideBarWidth(value: number): SideBarContainerAttribute;
    maxSideBarWidth(value: number): SideBarContainerAttribute;
    sideBarWidth(value: Length): SideBarContainerAttribute;
    minSideBarWidth(value: Length): SideBarContainerAttribute;
    maxSideBarWidth(value: Length): SideBarContainerAttribute;
    autoHide(value: boolean): SideBarContainerAttribute;
    sideBarPosition(value: SideBarPosition): SideBarContainerAttribute;
    divider(value: DividerStyle | undefined): SideBarContainerAttribute;
    minContentWidth(value: Dimension): SideBarContainerAttribute;
    _onChangeEvent_showSideBar(callback_: ((parameter: boolean) => void)): void;
}
declare interface RRect {
    left: number;
    top: number;
    width: number;
    height: number;
    radius: number;
}
declare interface WindowAnimationTarget {
    readonly bundleName: string;
    readonly abilityName: string;
    readonly windowBounds: RRect;
    readonly missionId: number;
}
declare interface RemoteWindowInterface {
    (target: WindowAnimationTarget): RemoteWindowAttribute;
}
declare class RemoteWindowAttribute extends CommonMethod<RemoteWindowAttribute> {
}
declare type GetItemMainSizeByIndex = ((index: number) => number);
declare class SectionOptions {
    itemsCount: number;
    crossCount?: number;
    onGetItemMainSizeByIndex?: GetItemMainSizeByIndex;
    columnsGap?: Dimension;
    rowsGap?: Dimension;
    margin?: (Margin|Dimension);
}
declare class WaterFlowSections {
    constructor();
    splice(start: number, deleteCount?: number, sections?: SectionOptions[]): boolean;
    push(section: SectionOptions): boolean;
    update(sectionIndex: number, section: SectionOptions): boolean;
    values(): SectionOptions[];
    length(): number;
}
declare enum WaterFlowLayoutMode {
    ALWAYS_TOP_DOWN = 0,
    SLIDING_WINDOW = 1,
}
declare interface WaterFlowOptions {
    footer?: CustomBuilder;
    scroller?: Scroller;
    sections?: WaterFlowSections;
    layoutMode?: WaterFlowLayoutMode;
}
declare interface WaterFlowInterface {
    (options?: WaterFlowOptions): WaterFlowAttribute;
}
declare class WaterFlowAttribute extends ScrollableCommonMethod<WaterFlowAttribute> {
    columnsTemplate(value: string): WaterFlowAttribute;
    itemConstraintSize(value: ConstraintSizeOptions): WaterFlowAttribute;
    rowsTemplate(value: string): WaterFlowAttribute;
    columnsGap(value: Length): WaterFlowAttribute;
    rowsGap(value: Length): WaterFlowAttribute;
    layoutDirection(value: FlexDirection): WaterFlowAttribute;
    nestedScroll(value: NestedScrollOptions): WaterFlowAttribute;
    enableScrollInteraction(value: boolean): WaterFlowAttribute;
    friction(value: (number|Resource)): WaterFlowAttribute;
    cachedCount(value: number): WaterFlowAttribute;
    onWillScroll(value: OnWillScrollCallback | undefined): WaterFlowAttribute;
    onDidScroll(value: OnScrollCallback | undefined): WaterFlowAttribute;
    onReachStart(value: (() => void)): WaterFlowAttribute;
    onReachEnd(value: (() => void)): WaterFlowAttribute;
    onScrollFrameBegin(value: ((offset: number, state: ScrollState) => { offsetRemain: number })): WaterFlowAttribute;
    onScrollIndex(value: ((first: number, last: number) => void)): WaterFlowAttribute;
    cachedCount(count: number, show: boolean): WaterFlowAttribute;
}
declare enum DpiFollowStrategy {
    FOLLOW_HOST_DPI = 0,
    FOLLOW_UI_EXTENSION_ABILITY_DPI = 1,
}
declare interface UIExtensionOptions {
    isTransferringCaller?: boolean;
    placeholder?: ComponentContent;
    areaChangePlaceholder?: Map<string,ComponentContent>;
    dpiFollowStrategy?: DpiFollowStrategy;
}
declare interface ReceiveCallback {
    _ReceiveCallbackStub: string;
}
declare type Callback_UIExtensionProxy_Void = ((parameter: UIExtensionProxy) => void);
declare interface UIExtensionProxy {
    send(data: Map<string,Object>): void;
    sendSync(data: Map<string,Object>): Map<string,Object>;
    on(type: 'asyncReceiverRegister', callback_: ((parameter: UIExtensionProxy) => void)): void;
    on(type: 'syncReceiverRegister', callback_: ((parameter: UIExtensionProxy) => void)): void;
    off(type: 'asyncReceiverRegister', callback_?: ((parameter: UIExtensionProxy) => void)): void;
    off(type: 'syncReceiverRegister', callback_?: ((parameter: UIExtensionProxy) => void)): void;
}
declare interface UIExtensionComponentInterface {
    (want: Want, options?: UIExtensionOptions): UIExtensionComponentAttribute;
}
declare type Literal_Number_code_Want_want = { code: number, want?: Want }
declare type Callback_Literal_Number_code_Want_want_Void = ((parameter: { code: number, want?: Want }) => void);
declare class UIExtensionComponentAttribute extends CommonMethod<UIExtensionComponentAttribute> {
    onRemoteReady(value: ((parameter: UIExtensionProxy) => void)): UIExtensionComponentAttribute;
    onReceive(value: ReceiveCallback): UIExtensionComponentAttribute;
    onResult(value: ((parameter: { code: number, want?: Want }) => void)): UIExtensionComponentAttribute;
    onRelease(value: ((index: number) => void)): UIExtensionComponentAttribute;
    onError(value: ErrorCallback): UIExtensionComponentAttribute;
    onTerminated(value: ((parameter: TerminationInfo) => void)): UIExtensionComponentAttribute;
}
declare interface RestrictedWorker {
    _RestrictedWorkerStub: string;
}
declare interface IsolatedOptions {
    want: Want;
    worker: RestrictedWorker;
}
declare type IsolatedComponentInterface = ((options: IsolatedOptions) => IsolatedComponentAttribute);
declare class IsolatedComponentAttribute extends CommonMethod<IsolatedComponentAttribute> {
    onError(value: ErrorCallback): IsolatedComponentAttribute;
}
declare class StyledString {
    constructor(value: (string|ImageAttachment|CustomSpan), styles?: StyleOptions[]);
    readonly length: number;
    getString(): string;
    getStyles(start: number, length: number, styledKey?: StyledStringKey): SpanStyle[];
    equals(other: StyledString): boolean;
    subStyledString(start: number, length?: number): StyledString;
}
declare interface StyleOptions {
    start?: number;
    length?: number;
    styledKey: StyledStringKey;
    styledValue: StyledStringValue;
}
declare interface SpanStyle {
    start: number;
    length: number;
    styledKey: StyledStringKey;
    styledValue: StyledStringValue;
}
declare class TextStyle_styled_string {
    constructor(value?: TextStyleInterface);
    readonly fontColor?: ResourceColor;
    readonly fontFamily?: string;
    readonly fontSize?: number;
    readonly fontWeight?: number;
    readonly fontStyle?: FontStyle;
}
declare interface TextStyleInterface {
    fontColor?: ResourceColor;
    fontFamily?: ResourceStr;
    fontSize?: LengthMetrics;
    fontWeight?: (number|FontWeight|string);
    fontStyle?: FontStyle;
}
declare class DecorationStyle {
    constructor(value: DecorationStyleInterface);
    readonly type: TextDecorationType;
    readonly color?: ResourceColor;
    readonly style?: TextDecorationStyle;
}
declare interface DecorationStyleInterface {
    type: TextDecorationType;
    color?: ResourceColor;
    style?: TextDecorationStyle;
}
declare class BaselineOffsetStyle {
    constructor(value: LengthMetrics);
    readonly baselineOffset: number;
}
declare class LetterSpacingStyle {
    constructor(value: LengthMetrics);
    readonly letterSpacing: number;
}
declare class TextShadowStyle {
    constructor(value: (ShadowOptions|ShadowOptions[]));
    readonly textShadow: ShadowOptions[];
}
declare class BackgroundColorStyle {
    constructor(textBackgroundStyle: TextBackgroundStyle);
    readonly textBackgroundStyle: TextBackgroundStyle;
}
declare class GestureStyle {
    constructor(value?: GestureStyleInterface);
}
declare interface GestureStyleInterface {
    onClick?: ((event: ClickEvent) => void);
    onLongPress?: ((event: GestureEvent) => void);
}
declare class ParagraphStyle {
    constructor(value?: ParagraphStyleInterface);
    readonly textAlign?: TextAlign;
    readonly textIndent?: number;
    readonly maxLines?: number;
    readonly overflow?: TextOverflow;
    readonly wordBreak?: WordBreak;
    readonly leadingMargin?: (number|LeadingMarginPlaceholder);
}
declare interface ParagraphStyleInterface {
    textAlign?: TextAlign;
    textIndent?: LengthMetrics;
    maxLines?: number;
    overflow?: TextOverflow;
    wordBreak?: WordBreak;
    leadingMargin?: (LengthMetrics|LeadingMarginPlaceholder);
}
declare class LineHeightStyle {
    constructor(lineHeight: LengthMetrics);
    readonly lineHeight: number;
}
declare class UrlStyle {
    constructor(url: string);
    readonly url: string;
}
declare type StyledStringValue = (TextStyle_styled_string|DecorationStyle|BaselineOffsetStyle|LetterSpacingStyle|TextShadowStyle|GestureStyle|ImageAttachment|ParagraphStyle|LineHeightStyle|UrlStyle|CustomSpan|UserDataSpan|BackgroundColorStyle);
declare class MutableStyledString extends StyledString {
    replaceString(start: number, length: number, other: string): void;
    insertString(start: number, other: string): void;
    removeString(start: number, length: number): void;
    replaceStyle(spanStyle: SpanStyle): void;
    setStyle(spanStyle: SpanStyle): void;
    removeStyle(start: number, length: number, styledKey: StyledStringKey): void;
    removeStyles(start: number, length: number): void;
    clearStyles(): void;
    replaceStyledString(start: number, length: number, other: StyledString): void;
    insertStyledString(start: number, other: StyledString): void;
    appendStyledString(other: StyledString): void;
}
declare enum StyledStringKey {
    FONT = 0,
    DECORATION = 1,
    BASELINE_OFFSET = 2,
    LETTER_SPACING = 3,
    TEXT_SHADOW = 4,
    LINE_HEIGHT = 5,
    BACKGROUND_COLOR = 6,
    URL = 7,
    GESTURE = 100,
    PARAGRAPH_STYLE = 200,
    IMAGE = 300,
    CUSTOM_SPAN = 400,
    USER_DATA = 500,
}
declare class ImageAttachment {
    constructor(value: ImageAttachmentInterface);
    readonly value: PixelMap;
    readonly size?: SizeOptions;
    readonly verticalAlign?: ImageSpanAlignment;
    readonly objectFit?: ImageFit;
    readonly layoutStyle?: ImageAttachmentLayoutStyle;
}
declare interface ImageAttachmentInterface {
    value: PixelMap;
    size?: SizeOptions;
    verticalAlign?: ImageSpanAlignment;
    objectFit?: ImageFit;
    layoutStyle?: ImageAttachmentLayoutStyle;
}
declare interface ImageAttachmentLayoutStyle {
    margin?: (LengthMetrics|Margin);
    padding?: (LengthMetrics|Padding);
    borderRadius?: (LengthMetrics|BorderRadiuses);
}
declare interface CustomSpanMetrics {
    width: number;
    height?: number;
}
declare interface CustomSpanDrawInfo {
    x: number;
    lineTop: number;
    lineBottom: number;
    baseline: number;
}
declare interface CustomSpanMeasureInfo {
    fontSize: number;
}
declare class CustomSpan {
    onMeasure(measureInfo: CustomSpanMeasureInfo): CustomSpanMetrics;
    onDraw(context: DrawContext, drawInfo: CustomSpanDrawInfo): void;
    invalidate(): void;
}
declare class UserDataSpan {
}
declare class LinearIndicatorController {
    constructor();
    setProgress(index: number, progress: number): void;
    start(options?: LinearIndicatorStartOptions): void;
    pause(): void;
    stop(): void;
}
declare interface LinearIndicatorStartOptions {
    interval?: number;
    duration?: number;
}
declare interface LinearIndicatorStyle {
    space?: LengthMetrics;
    strokeWidth?: LengthMetrics;
    strokeRadius?: LengthMetrics;
    trackBackgroundColor?: ColorMetrics;
    trackColor?: ColorMetrics;
}
declare interface LinearIndicatorInterface {
    (count?: number, controller?: LinearIndicatorController): LinearIndicatorAttribute;
}
declare class LinearIndicatorAttribute extends CommonMethod<LinearIndicatorAttribute> {
    indicatorStyle(value: LinearIndicatorStyle | undefined): LinearIndicatorAttribute;
    indicatorLoop(value: boolean | undefined): LinearIndicatorAttribute;
    onChange(value: OnLinearIndicatorChangeCallback | undefined): LinearIndicatorAttribute;
}
declare type OnLinearIndicatorChangeCallback = ((index: number, progress: number) => void);
declare function getInspectorNodes(): Object;
declare function getInspectorNodeById(id: number): Object;
declare namespace Profiler {
    type Callback_String_Void = ((info: string) => void);
}
declare namespace Profiler {
    function registerVsyncCallback(callback_: ((info: string) => void)): void;
}
declare namespace Profiler {
    function unregisterVsyncCallback(): void;
}
declare function setAppBgColor(value: string): void;
declare interface RawFileDescriptor {
    fd: number;
    offset: number;
    length: number;
}
declare const AbilityComponent: AbilityComponentInterface
declare const AbilityComponentInstance: AbilityComponentAttribute
declare const AlphabetIndexer: AlphabetIndexerInterface
declare const AlphabetIndexerInstance: AlphabetIndexerAttribute
declare const Animator: AnimatorInterface
declare const AnimatorInstance: AnimatorAttribute
declare const Badge: BadgeInterface
declare const BadgeInstance: BadgeAttribute
declare const Blank: BlankInterface
declare const BlankInstance: BlankAttribute
declare const Button: ButtonInterface
declare const ButtonInstance: ButtonAttribute
declare const Calendar: CalendarInterface
declare const CalendarInstance: CalendarAttribute
declare const CalendarPicker: CalendarPickerInterface
declare const CalendarPickerInstance: CalendarPickerAttribute
declare const Canvas: CanvasInterface
declare const CanvasInstance: CanvasAttribute
declare const Checkbox: CheckboxInterface
declare const CheckboxInstance: CheckboxAttribute
declare const CheckboxGroup: CheckboxGroupInterface
declare const CheckboxGroupInstance: CheckboxGroupAttribute
declare const Circle: CircleInterface
declare const CircleInstance: CircleAttribute
declare const Column: ColumnInterface
declare const ColumnInstance: ColumnAttribute
declare const ColumnSplit: ColumnSplitInterface
declare const ColumnSplitInstance: ColumnSplitAttribute
declare const Common: CommonInterface
declare const CommonInstance: CommonAttribute
declare const Component3D: Component3DInterface
declare const Component3DInstance: Component3DAttribute
declare const ContainerSpan: ContainerSpanInterface
declare const ContainerSpanInstance: ContainerSpanAttribute
declare const Counter: CounterInterface
declare const CounterInstance: CounterAttribute
declare const DataPanel: DataPanelInterface
declare const DataPanelInstance: DataPanelAttribute
declare const DatePicker: DatePickerInterface
declare const DatePickerInstance: DatePickerAttribute
declare const Divider: DividerInterface
declare const DividerInstance: DividerAttribute
declare const EffectComponent: EffectComponentInterface
declare const EffectComponentInstance: EffectComponentAttribute
declare const Ellipse: EllipseInterface
declare const EllipseInstance: EllipseAttribute
declare const EmbeddedComponent: EmbeddedComponentInterface
declare const EmbeddedComponentInstance: EmbeddedComponentAttribute
declare const Flex: FlexInterface
declare const FlexInstance: FlexAttribute
declare const FlowItem: FlowItemInterface
declare const FlowItemInstance: FlowItemAttribute
declare const FolderStack: FolderStackInterface
declare const FolderStackInstance: FolderStackAttribute
declare const FormComponent: FormComponentInterface
declare const FormComponentInstance: FormComponentAttribute
declare const FormLink: FormLinkInterface
declare const FormLinkInstance: FormLinkAttribute
declare const Gauge: GaugeInterface
declare const GaugeInstance: GaugeAttribute
declare const Grid: GridInterface
declare const GridInstance: GridAttribute
declare const GridItem: GridItemInterface
declare const GridItemInstance: GridItemAttribute
declare const GridCol: GridColInterface
declare const GridColInstance: GridColAttribute
declare const GridContainer: GridContainerInterface
declare const GridContainerInstance: GridContainerAttribute
declare const GridRow: GridRowInterface
declare const GridRowInstance: GridRowAttribute
declare const Hyperlink: HyperlinkInterface
declare const HyperlinkInstance: HyperlinkAttribute
declare const Image: ImageInterface
declare const ImageInstance: ImageAttribute
declare const ImageAnimator: ImageAnimatorInterface
declare const ImageAnimatorInstance: ImageAnimatorAttribute
declare const ImageSpan: ImageSpanInterface
declare const ImageSpanInstance: ImageSpanAttribute
declare const Line: LineInterface
declare const LineInstance: LineAttribute
declare const List: ListInterface
declare const ListInstance: ListAttribute
declare const ListItem: ListItemInterface
declare const ListItemInstance: ListItemAttribute
declare const ListItemGroup: ListItemGroupInterface
declare const ListItemGroupInstance: ListItemGroupAttribute
declare const LoadingProgress: LoadingProgressInterface
declare const LoadingProgressInstance: LoadingProgressAttribute
declare const LocationButton: LocationButtonInterface
declare const LocationButtonInstance: LocationButtonAttribute
declare const Marquee: MarqueeInterface
declare const MarqueeInstance: MarqueeAttribute
declare const MediaCachedImage: MediaCachedImageInterface
declare const MediaCachedImageInstance: MediaCachedImageAttribute
declare const Menu: MenuInterface
declare const MenuInstance: MenuAttribute
declare const MenuItem: MenuItemInterface
declare const MenuItemInstance: MenuItemAttribute
declare const MenuItemGroup: MenuItemGroupInterface
declare const MenuItemGroupInstance: MenuItemGroupAttribute
declare const NavDestination: NavDestinationInterface
declare const NavDestinationInstance: NavDestinationAttribute
declare const NavRouter: NavRouterInterface
declare const NavRouterInstance: NavRouterAttribute
declare const Navigator: NavigatorInterface
declare const NavigatorInstance: NavigatorAttribute
declare const NodeContainer: NodeContainerInterface
declare const NodeContainerInstance: NodeContainerAttribute
declare const Panel: PanelInterface
declare const PanelInstance: PanelAttribute
declare const PasteButton: PasteButtonInterface
declare const PasteButtonInstance: PasteButtonAttribute
declare const Path: PathInterface
declare const PathInstance: PathAttribute
declare const PatternLock: PatternLockInterface
declare const PatternLockInstance: PatternLockAttribute
declare const PluginComponent: PluginComponentInterface
declare const PluginComponentInstance: PluginComponentAttribute
declare const Polygon: PolygonInterface
declare const PolygonInstance: PolygonAttribute
declare const Polyline: PolylineInterface
declare const PolylineInstance: PolylineAttribute
declare const Progress: ProgressInterface
declare const ProgressInstance: ProgressAttribute
declare const QRCode: QRCodeInterface
declare const QRCodeInstance: QRCodeAttribute
declare const Radio: RadioInterface
declare const RadioInstance: RadioAttribute
declare const Rating: RatingInterface
declare const RatingInstance: RatingAttribute
declare const Rect: RectInterface
declare const RectInstance: RectAttribute
declare const Refresh: RefreshInterface
declare const RefreshInstance: RefreshAttribute
declare const RelativeContainer: RelativeContainerInterface
declare const RelativeContainerInstance: RelativeContainerAttribute
declare const RichEditor: RichEditorInterface
declare const RichEditorInstance: RichEditorAttribute
declare const RichText: RichTextInterface
declare const RichTextInstance: RichTextAttribute
declare const RootScene: RootSceneInterface
declare const RootSceneInstance: RootSceneAttribute
declare const Row: RowInterface
declare const RowInstance: RowAttribute
declare const RowSplit: RowSplitInterface
declare const RowSplitInstance: RowSplitAttribute
declare const SaveButton: SaveButtonInterface
declare const SaveButtonInstance: SaveButtonAttribute
declare const Screen: ScreenInterface
declare const ScreenInstance: ScreenAttribute
declare const Scroll: ScrollInterface
declare const ScrollInstance: ScrollAttribute
declare const ScrollBar: ScrollBarInterface
declare const ScrollBarInstance: ScrollBarAttribute
declare const Search: SearchInterface
declare const SearchInstance: SearchAttribute
declare const Select: SelectInterface
declare const SelectInstance: SelectAttribute
declare const Shape: ShapeInterface
declare const ShapeInstance: ShapeAttribute
declare const Slider: SliderInterface
declare const SliderInstance: SliderAttribute
declare const Span: SpanInterface
declare const SpanInstance: SpanAttribute
declare const Stack: StackInterface
declare const StackInstance: StackAttribute
declare const Stepper: StepperInterface
declare const StepperInstance: StepperAttribute
declare const StepperItem: StepperItemInterface
declare const StepperItemInstance: StepperItemAttribute
declare const Swiper: SwiperInterface
declare const SwiperInstance: SwiperAttribute
declare const IndicatorComponent: IndicatorComponentInterface
declare const IndicatorComponentInstance: IndicatorComponentAttribute
declare const SymbolGlyph: SymbolGlyphInterface
declare const SymbolGlyphInstance: SymbolGlyphAttribute
declare const SymbolSpan: SymbolSpanInterface
declare const SymbolSpanInstance: SymbolSpanAttribute
declare const Tabs: TabsInterface
declare const TabsInstance: TabsAttribute
declare const TabContent: TabContentInterface
declare const TabContentInstance: TabContentAttribute
declare const Text: TextInterface
declare const TextInstance: TextAttribute
declare const TextArea: TextAreaInterface
declare const TextAreaInstance: TextAreaAttribute
declare const TextClock: TextClockInterface
declare const TextClockInstance: TextClockAttribute
declare const TextInput: TextInputInterface
declare const TextInputInstance: TextInputAttribute
declare const TextPicker: TextPickerInterface
declare const TextPickerInstance: TextPickerAttribute
declare const TextTimer: TextTimerInterface
declare const TextTimerInstance: TextTimerAttribute
declare const TimePicker: TimePickerInterface
declare const TimePickerInstance: TimePickerAttribute
declare const Toggle: ToggleInterface
declare const ToggleInstance: ToggleAttribute
declare const Video: VideoInterface
declare const VideoInstance: VideoAttribute
declare const Web: WebInterface
declare const WebInstance: WebAttribute
declare const WindowScene: WindowSceneInterface
declare const WindowSceneInstance: WindowSceneAttribute
declare const XComponent: XComponentInterface
declare const XComponentInstance: XComponentAttribute
declare const SideBarContainer: SideBarContainerInterface
declare const SideBarContainerInstance: SideBarContainerAttribute
declare const RemoteWindow: RemoteWindowInterface
declare const RemoteWindowInstance: RemoteWindowAttribute
declare const WaterFlow: WaterFlowInterface
declare const WaterFlowInstance: WaterFlowAttribute
declare const UIExtensionComponent: UIExtensionComponentInterface
declare const UIExtensionComponentInstance: UIExtensionComponentAttribute
declare const LinearIndicator: LinearIndicatorInterface
declare const LinearIndicatorInstance: LinearIndicatorAttribute