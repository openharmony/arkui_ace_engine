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

declare interface IDataSource<T> {
    totalCount(): number;

    getData(index: number): T;

    registerDataChangeListener(listener: DataChangeListener): void;

    unregisterDataChangeListener(listener: DataChangeListener): void;
}

declare class LazyForEachAttribute implements DynamicNode {
    onMove(handler: OnMoveHandler | undefined, eventHandler?: ItemDragEventHandler): DynamicNode;
}

interface LazyForEachInterface<T> {
    (
        dataSource: IDataSource<T>,
        itemGenerator: (item: T, index: number) => void,
        keyGenerator?: (item: T, index: number) => string
    ): LazyForEachAttribute;
}

declare function ForEach<T> (
    arr: Array<T>,
    itemGenerator: (item: T, index: number) => void,
    keyGenerator?: (item: T, index: number) => string,
): ForEachAttribute<T>;

declare class ForEachAttribute<T> implements DynamicNode {
    onMove(handler: OnMoveHandler | undefined, eventHandler?: ItemDragEventHandler): DynamicNode;
}

interface ForEachInterface<T> {
    (
        arr: Array<T>,
        itemGenerator: (item: T, index: number) => void,
        keyGenerator?: (item: T, index: number) => string,
    ): ForEachAttribute<T>
// TODO: have overloads for [] and Array
    /*
      (
        arr: T[],
        itemGenerator: (item: T, index: number) => void,
        keyGenerator?: (item: T, index: number) => string,
      ): ForEachAttribute<T>;
    */
}

declare function LazyForEach<T>(
    dataSource: IDataSource<T>,
    itemGenerator: (item: T, index: number) => void,
    keyGenerator?: (item: T, index: number) => string,
): LazyForEachAttribute // extends LazyForEachInterface<T> {}

// Until we have full sdk
declare interface LayoutChild {}

declare interface ComponentOptions {
    freezeWhenInactive : boolean,
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

declare class WrappedBuilder {
    builder: ((arg: Object) => void);
}

declare namespace window {
    enum Orientation {
        UNSPECIFIED = 0,
        PORTRAIT = 1,
        LANDSCAPE = 2,
        PORTRAIT_INVERTED = 3,
        LANDSCAPE_INVERTED = 4,
        AUTO_ROTATION = 5,
        AUTO_ROTATION_PORTRAIT = 6,
        AUTO_ROTATION_LANDSCAPE = 7,
        AUTO_ROTATION_RESTRICTED = 8,
        AUTO_ROTATION_PORTRAIT_RESTRICTED = 9,
        AUTO_ROTATION_LANDSCAPE_RESTRICTED = 10,
        LOCKED = 11,
        AUTO_ROTATION_UNSPECIFIED = 12,
        USER_ROTATION_PORTRAIT = 13,
        USER_ROTATION_LANDSCAPE = 14,
        USER_ROTATION_PORTRAIT_INVERTED = 15,
        USER_ROTATION_LANDSCAPE_INVERTED = 16,
        FOLLOW_DESKTOP = 17
    }
}

declare class GestureGroup {
    static $_instantiate(factory: () => GestureGroup, mode: GestureMode, ...gesture: GestureType[]): GestureGroup;
    onCancel(event: () => void): GestureGroup;
}



// TODO: there should be no buffer in index-full.d.ts
type buffer = ArrayBuffer


declare interface SheetInfo {
    title: (string|Resource);
    icon?: (string|Resource);
    action: VoidCallback;
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
declare type Callback_DismissDialogAction_Void = ((value0: DismissDialogAction) => void);
declare type Callback_Void = (() => void);
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
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    onWillDismiss?: ((value0: DismissDialogAction) => void);
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
    onDidAppear?: (() => void);
    onDidDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
    levelMode?: LevelMode;
    levelUniqueId?: number;
    immersiveMode?: ImmersiveMode;
    levelOrder?: LevelOrder;
}
declare enum DialogAlignment {
    TOP,
    Top,
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
    AUTO,
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
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    onWillDismiss?: ((value0: DismissDialogAction) => void);
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
    onDidAppear?: (() => void);
    onDidDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
    levelMode?: LevelMode;
    levelUniqueId?: number;
    immersiveMode?: ImmersiveMode;
    levelOrder?: LevelOrder;
}
declare interface AlertDialogParamWithConfirm extends AlertDialogParam {
    confirm?: AlertDialogButtonBaseOptions;
}
declare interface DismissDialogAction {
    dismiss: (() => void);
    reason: DismissReason;
}
declare interface AlertDialogParamWithButtons extends AlertDialogParam {
    primaryButton: AlertDialogButtonBaseOptions;
    secondaryButton: AlertDialogButtonBaseOptions;
}
declare interface AlertDialogParamWithOptions extends AlertDialogParam {
    buttons: AlertDialogButtonOptions[];
    buttonDirection?: DialogButtonDirection;
}
declare enum IndexerAlign {
    LEFT,
    Left,
    RIGHT = 1,
    Right = 1,
    START = 2,
    END = 3,
}
declare interface AlphabetIndexerOptions {
    arrayValue: string[];
    selected: number;
}
declare type OnAlphabetIndexerSelectCallback = ((index: number) => void);
declare type OnAlphabetIndexerPopupSelectCallback = ((index: number) => void);
declare type OnAlphabetIndexerRequestPopupDataCallback = ((index: number) => string[]);
declare interface AlphabetIndexerAttribute extends CommonMethod {
    color(value: ResourceColor | undefined): AlphabetIndexerAttribute;
    selectedColor(value: ResourceColor | undefined): AlphabetIndexerAttribute;
    popupColor(value: ResourceColor | undefined): AlphabetIndexerAttribute;
    selectedBackgroundColor(value: ResourceColor | undefined): AlphabetIndexerAttribute;
    popupBackground(value: ResourceColor | undefined): AlphabetIndexerAttribute;
    popupSelectedColor(value: ResourceColor | undefined): AlphabetIndexerAttribute;
    popupUnselectedColor(value: ResourceColor | undefined): AlphabetIndexerAttribute;
    popupItemBackgroundColor(value: ResourceColor | undefined): AlphabetIndexerAttribute;
    usingPopup(value: boolean | undefined): AlphabetIndexerAttribute;
    selectedFont(value: Font | undefined): AlphabetIndexerAttribute;
    popupFont(value: Font | undefined): AlphabetIndexerAttribute;
    popupItemFont(value: Font | undefined): AlphabetIndexerAttribute;
    itemSize(value: (string|number) | undefined): AlphabetIndexerAttribute;
    font(value: Font | undefined): AlphabetIndexerAttribute;
    onSelect(value: OnAlphabetIndexerSelectCallback | undefined): AlphabetIndexerAttribute;
    onRequestPopupData(value: OnAlphabetIndexerRequestPopupDataCallback | undefined): AlphabetIndexerAttribute;
    onPopupSelect(value: OnAlphabetIndexerPopupSelectCallback | undefined): AlphabetIndexerAttribute;
    selected(value: number | undefined): AlphabetIndexerAttribute;
    popupPosition(value: Position | undefined): AlphabetIndexerAttribute;
    autoCollapse(value: boolean | undefined): AlphabetIndexerAttribute;
    popupItemBorderRadius(value: number | undefined): AlphabetIndexerAttribute;
    itemBorderRadius(value: number | undefined): AlphabetIndexerAttribute;
    popupBackgroundBlurStyle(value: BlurStyle | undefined): AlphabetIndexerAttribute;
    popupTitleBackground(value: ResourceColor | undefined): AlphabetIndexerAttribute;
    enableHapticFeedback(value: boolean | undefined): AlphabetIndexerAttribute;
    attributeModifier(value: (AttributeModifier<AlphabetIndexerAttribute>|AttributeModifier<CommonMethod>) | undefined): AlphabetIndexerAttribute;
    alignStyle(value: IndexerAlign | undefined, offset?: Length | undefined): AlphabetIndexerAttribute;
}
declare interface AlphabetIndexerInterface {
    (options: AlphabetIndexerOptions): AlphabetIndexerAttribute;
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
declare type Callback_Number_Void = ((value: number) => void);
declare interface AnimatorAttribute extends CommonMethod {
    state(value: AnimationStatus | undefined): AnimatorAttribute;
    duration(value: number | undefined): AnimatorAttribute;
    curve(value: Curve | undefined): AnimatorAttribute;
    delay(value: number | undefined): AnimatorAttribute;
    fillMode(value: FillMode | undefined): AnimatorAttribute;
    iterations(value: number | undefined): AnimatorAttribute;
    playMode(value: PlayMode | undefined): AnimatorAttribute;
    motion(value: (SpringMotion|FrictionMotion|ScrollMotion) | undefined): AnimatorAttribute;
    onStart(value: (() => void) | undefined): AnimatorAttribute;
    onPause(value: (() => void) | undefined): AnimatorAttribute;
    onRepeat(value: (() => void) | undefined): AnimatorAttribute;
    onCancel(value: (() => void) | undefined): AnimatorAttribute;
    onFinish(value: (() => void) | undefined): AnimatorAttribute;
    onFrame(value: ((value: number) => void) | undefined): AnimatorAttribute;
    attributeModifier(value: (AttributeModifier<AnimatorAttribute>|AttributeModifier<CommonMethod>) | undefined): AnimatorAttribute;
}
declare interface AnimatorInterface {
    (value: string): AnimatorAttribute;
}
declare class BaseContext {
    constructor();
}
declare interface Context {
    new();
}
declare class CommonModifier {
}
declare interface TransitionOptions {
    type?: TransitionType;
    opacity?: number;
    translate?: TranslateOptions;
    scale?: ScaleOptions;
    rotate?: RotateOptions;
}
declare interface LayoutChild {
    name: string;
    id: string;
    position: Position;
    measure(childConstraint: ConstraintSizeOptions): void;
}
declare interface GestureInterface<T> {
    tag(tag: string): T;
    allowedTypes(types: SourceTool[]): T;
}
declare type Callback_GestureEvent_Void = ((event: GestureEvent) => void);
declare interface TapGestureInterface extends GestureInterface<TapGestureInterface> {
    onAction(event: ((event: GestureEvent) => void)): TapGestureInterface;
    (value: TapGestureParameters): TapGestureInterface;
}
declare interface LongPressGestureInterface_Invoke_Literal {
    fingers?: number;
    repeat?: boolean;
    duration?: number;
}
declare interface LongPressGestureInterface extends GestureInterface<LongPressGestureInterface> {
    onAction(event: ((event: GestureEvent) => void)): LongPressGestureInterface;
    onActionEnd(event: ((event: GestureEvent) => void)): LongPressGestureInterface;
    onActionCancel(event: (() => void)): LongPressGestureInterface;
    onActionCancel(event: ((event: GestureEvent) => void)): LongPressGestureInterface;
    (value: LongPressGestureInterface_Invoke_Literal): LongPressGestureInterface;
    (options: LongPressGestureHandlerOptions): LongPressGestureInterface;
}
declare interface PanGestureInterface_Invoke_Literal {
    fingers?: number;
    direction?: PanDirection;
    distance?: number;
}
declare interface PanGestureInterface extends GestureInterface<PanGestureInterface> {
    onActionStart(event: ((event: GestureEvent) => void)): PanGestureInterface;
    onActionUpdate(event: ((event: GestureEvent) => void)): PanGestureInterface;
    onActionEnd(event: ((event: GestureEvent) => void)): PanGestureInterface;
    onActionCancel(event: (() => void)): PanGestureInterface;
    onActionCancel(event: ((event: GestureEvent) => void)): PanGestureInterface;
    (value: (PanGestureInterface_Invoke_Literal|PanGestureOptions)): PanGestureInterface;
    (options: PanGestureHandlerOptions): PanGestureInterface;
}
declare interface PinchGestureInterface_Invoke_Literal {
    fingers?: number;
    distance?: number;
}
declare interface PinchGestureInterface extends GestureInterface<PinchGestureInterface> {
    onActionStart(event: ((event: GestureEvent) => void)): PinchGestureInterface;
    onActionUpdate(event: ((event: GestureEvent) => void)): PinchGestureInterface;
    onActionEnd(event: ((event: GestureEvent) => void)): PinchGestureInterface;
    onActionCancel(event: (() => void)): PinchGestureInterface;
    onActionCancel(event: ((event: GestureEvent) => void)): PinchGestureInterface;
    (value: PinchGestureInterface_Invoke_Literal): PinchGestureInterface;
    (options: PinchGestureHandlerOptions): PinchGestureInterface;
}
declare interface GestureGroupInterface {
    onCancel(event: (() => void)): GestureGroupInterface;
    (mode: GestureMode, gesture: GestureType[]): GestureGroupInterface;
}
declare enum NavigationType {
    PUSH,
    BACK = 1,
    REPLACE = 2,
}
declare class WebCookie {
    setCookie(): void;
    saveCookie(): void;
}
declare class ComponentContent {
    update(args: Object): void;
    reuse(param?: Object): void;
    recycle(): void;
    dispose(): void;
    updateConfiguration(): void;
}
declare class Content {
}
declare interface CrossLanguageOptions {
    attributeSetting?: boolean;
}
declare class FrameNode {
    constructor(uiContext: UIContext);
    isModifiable(): boolean;
    appendChild(node: FrameNode): void;
    insertChildAfter(child: FrameNode, sibling: FrameNode): void;
    removeChild(node: FrameNode): void;
    clearChildren(): void;
    getChild?(index: number, expandMode: number): FrameNode;
    getFirstChild?(): FrameNode;
    getNextSibling?(): FrameNode;
    getPreviousSibling?(): FrameNode;
    getParent?(): FrameNode;
    getChildrenCount(): number;
    dispose(): void;
    getId(): string;
    getUniqueId(): number;
    getOpacity(): number;
    isVisible(): boolean;
    isClipToFrame(): boolean;
    isAttached(): boolean;
    getInspectorInfo(): Object;
    invalidate(): void;
    disposeTree(): void;
    setCrossLanguageOptions(options: CrossLanguageOptions): void;
    getCrossLanguageOptions(): CrossLanguageOptions;
    getPositionToWindowWithTransform(): Position;
    static getFrameNodeByKey(name: string): FrameNode;
    getIdByFrameNode(node: FrameNode): number;
    moveTo(targetParent: FrameNode, index: number): void;
    getFirstChildIndexWithoutExpand(): number;
    getLastChildIndexWithoutExpand(): number;
    static getAttachedFrameNodeById(id: string): FrameNode;
    static getFrameNodeById(id: number): FrameNode;
    static getFrameNodeByUniqueId(id: number): FrameNode;
    reuse(): void;
    recycle(): void;
    static getFrameNodePtr(node: FrameNode): number|bigint;
}
declare interface Size {
    width: number;
    height: number;
}
declare class DrawContext {
    constructor();
    size(): Size;
    sizeInPixel(): Size;
    canvas(): drawing.Canvas;
}
declare interface Vector2 {
    x: number;
    y: number;
}
declare interface Vector2T<T> {
    x: number;
    y: number;
}
declare interface Vector3 {
    x: number;
    y: number;
    z: number;
}
declare type Matrix4 = [ number, number, number, number, number, number, number, number, number, number, number, number, number, number, number, number ]
declare type Offset = Vector2;
declare type Position = Vector2;
declare type PositionT<T> = Vector2T<T>;
declare type Pivot = Vector2;
declare type Scale = Vector2;
declare type Translation = Vector2;
declare type Rotation = Vector3;
declare interface Frame {
    x: number;
    y: number;
    width: number;
    height: number;
}
declare enum LengthUnit {
    PX,
    VP = 1,
    FP = 2,
    PERCENT = 3,
    LPX = 4,
}
declare interface SizeT<T> {
    width: number;
    height: number;
}
declare enum LengthMetricsUnit {
    DEFAULT,
    PX = 1,
}
declare class LengthMetrics {
    constructor(value: number, unit: LengthUnit);
    unit: LengthUnit;
    value: number;
    static px(value: number): LengthMetrics;
    static vp(value: number): LengthMetrics;
    static fp(value: number): LengthMetrics;
    static percent(value: number): LengthMetrics;
    static lpx(value: number): LengthMetrics;
    static resource(value: Resource): LengthMetrics;
}
declare class ColorMetrics {
    constructor();
    static numeric(value: number): ColorMetrics;
    static rgba(red: number, green: number, blue: number, alpha: number): ColorMetrics;
    static resourceColor(color: ResourceColor): ColorMetrics;
    blendColor(overlayColor: ColorMetrics): ColorMetrics;
    color(): string;
    red(): number;
    green(): number;
    blue(): number;
    alpha(): number;
}
declare interface Corners {
    topLeft: number;
    topRight: number;
    bottomLeft: number;
    bottomRight: number;
}
declare type Rect = common2D.Rect;
declare interface CornerRadius {
}
declare interface RoundRect {
    rect: common2D.Rect;
    corners: CornerRadius;
}
declare interface Circle {
    centerX: number;
    centerY: number;
    radius: number;
}
declare interface CommandPath {
    commands: string;
}
declare class ShapeMask {
    constructor();
    fillColor: number;
    strokeColor: number;
    strokeWidth: number;
    setRectShape(rect: common2D.Rect): void;
    setRoundRectShape(roundRect: RoundRect): void;
    setCircleShape(circle: Circle): void;
    setOvalShape(oval: common2D.Rect): void;
    setCommandPath(path: CommandPath): void;
}
declare class ShapeClip {
    constructor();
    setRectShape(rect: common2D.Rect): void;
    setRoundRectShape(roundRect: RoundRect): void;
    setCircleShape(circle: Circle): void;
    setOvalShape(oval: common2D.Rect): void;
    setCommandPath(path: CommandPath): void;
}
declare function edgeColors(all: number): Edges;
declare function edgeWidths(all: number): Edges;
declare function borderStyles(all: BorderStyle): Edges;
declare function borderRadiuses(all: number): BorderRadiuses;
declare interface ImageModifier {
}
declare class NodeContent {
    constructor();
    addFrameNode(node: FrameNode): void;
    removeFrameNode(node: FrameNode): void;
}
declare class NodeController {
}
declare type Offset_graphics = Vector2;
declare interface BorderRadiuses_graphics {
    topLeft: number;
    topRight: number;
    bottomLeft: number;
    bottomRight: number;
}
declare interface RenderNode {
    new();
    backgroundColor: number;
    clipToFrame: boolean;
    opacity: number;
    size: Size;
    position: Vector2;
    frame: Frame;
    pivot: Vector2;
    scale: Vector2;
    translation: Vector2;
    rotation: Vector3;
    transform: [ number, number, number, number, number, number, number, number, number, number, number, number, number, number, number, number ];
    shadowColor: number;
    shadowOffset: Vector2;
    label: string;
    shadowAlpha: number;
    shadowElevation: number;
    shadowRadius: number;
    borderStyle: EdgeStyles;
    borderWidth: Edges;
    borderColor: Edges;
    borderRadius: BorderRadiuses_graphics;
    shapeMask: ShapeMask;
    shapeClip: ShapeClip;
    markNodeGroup: boolean;
    lengthMetricsUnit: LengthMetricsUnit;
    appendChild(node: RenderNode): void;
    insertChildAfter(child: RenderNode, sibling: RenderNode | undefined): void;
    removeChild(node: RenderNode): void;
    clearChildren(): void;
    getChild(index: number): RenderNode | undefined;
    getFirstChild(): RenderNode | undefined;
    getNextSibling(): RenderNode | undefined;
    getPreviousSibling(): RenderNode | undefined;
    draw(context: DrawContext): void;
    invalidate(): void;
    dispose(): void;
}
declare interface ConsumeDecoratedVariable {
}
declare class ProvideDecoratedVariable {
}
declare interface WatchFuncType {
}
declare interface SymbolGlyphModifier {
}
declare interface TextModifier {
}
declare interface AttributeUpdater {
}
declare enum BadgePosition {
    RIGHT_TOP,
    RightTop,
    RIGHT = 1,
    Right = 1,
    LEFT = 2,
    Left = 2,
}
declare interface BadgeStyle {
    color?: ResourceColor;
    fontSize?: (number|ResourceStr);
    badgeSize?: (number|ResourceStr);
    badgeColor?: ResourceColor;
    borderColor?: ResourceColor;
    borderWidth?: Length;
    fontWeight?: (number|FontWeight|ResourceStr);
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
    value: ResourceStr;
}
declare interface BadgeAttribute extends CommonMethod {
    attributeModifier(value: (AttributeModifier<BadgeAttribute>|AttributeModifier<CommonMethod>) | undefined): BadgeAttribute;
}
declare type BadgeParamWithStringType = (string|Resource);
declare type BadgeStyleSizeType = (number|string|Resource);
declare interface BadgeInterface {
    (value: BadgeParamWithNumber): BadgeAttribute;
    (value: BadgeParamWithString): BadgeAttribute;
}
declare interface BlankAttribute extends CommonMethod {
    color(value: ResourceColor | undefined): BlankAttribute;
    attributeModifier(value: (AttributeModifier<BlankAttribute>|AttributeModifier<CommonMethod>) | undefined): BlankAttribute;
}
declare interface BlankInterface {
    (min?: (number|string)): BlankAttribute;
}
declare type CustomBuilder = (() => void);
declare type CustomBuilderT = ((t: T) => void);
declare type PageMapBuilder = ((name: string, param: Object | undefined) => void);
declare enum ButtonType {
    CAPSULE,
    Capsule,
    CIRCLE = 1,
    Circle = 1,
    NORMAL = 2,
    Normal = 2,
    ROUNDED_RECTANGLE = 3,
}
declare enum ButtonStyleMode {
    NORMAL,
    EMPHASIZED = 1,
    TEXTUAL = 2,
}
declare enum ButtonRole {
    NORMAL,
    ERROR = 1,
}
declare type ButtonTriggerClickCallback = ((xPos: number, yPos: number) => void);
declare interface ButtonConfiguration extends CommonConfiguration<ButtonConfiguration> {
    label: string;
    pressed: boolean;
    triggerClick: ButtonTriggerClickCallback;
}
declare enum ControlSize {
    SMALL = "'small'",
    NORMAL = "'normal'",
}
declare interface ButtonOptions {
    type?: ButtonType;
    stateEffect?: boolean;
    buttonStyle?: ButtonStyleMode;
    controlSize?: ControlSize;
    role?: ButtonRole;
}
declare interface ButtonLabelStyle {
    overflow?: TextOverflow;
    maxLines?: number;
    minFontSize?: (number|ResourceStr);
    maxFontSize?: (number|ResourceStr);
    heightAdaptivePolicy?: TextHeightAdaptivePolicy;
    font?: Font;
}
declare interface ButtonAttribute extends CommonMethod {
    type(value: ButtonType | undefined): ButtonAttribute;
    stateEffect(value: boolean | undefined): ButtonAttribute;
    buttonStyle(value: ButtonStyleMode | undefined): ButtonAttribute;
    controlSize(value: ControlSize | undefined): ButtonAttribute;
    role(value: ButtonRole | undefined): ButtonAttribute;
    fontColor(value: ResourceColor | undefined): ButtonAttribute;
    fontSize(value: Length | undefined): ButtonAttribute;
    fontWeight(value: (number|FontWeight|string) | undefined): ButtonAttribute;
    fontStyle(value: FontStyle | undefined): ButtonAttribute;
    fontFamily(value: (string|Resource) | undefined): ButtonAttribute;
    contentModifier(value: ContentModifier<ButtonConfiguration> | undefined): ButtonAttribute;
    labelStyle(value: ButtonLabelStyle | undefined): ButtonAttribute;
    minFontScale(value: (number|Resource) | undefined): ButtonAttribute;
    maxFontScale(value: (number|Resource) | undefined): ButtonAttribute;
    attributeModifier(value: (AttributeModifier<ButtonAttribute>|AttributeModifier<CommonMethod>) | undefined): ButtonAttribute;
}
declare interface ButtonInterface {
    (): ButtonAttribute;
    (options: ButtonOptions): ButtonAttribute;
    (label: ResourceStr, options?: ButtonOptions): ButtonAttribute;
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
declare interface DateOptions {
    year: number;
    month: number;
    day: number;
}
declare class CalendarController {
    constructor();
    backToToday(): void;
    goTo(date: CalendarSelectedDate): void;
}
declare interface CalendarRequestedMonths {
    date: CalendarSelectedDate;
    currentData: MonthData;
    preData: MonthData;
    nextData: MonthData;
    controller?: CalendarController;
}
declare type Callback_CalendarSelectedDate_Void = ((event: CalendarSelectedDate) => void);
declare type Callback_CalendarRequestedData_Void = ((event: CalendarRequestedData) => void);
declare interface CalendarAttribute {
    showLunar(value: boolean | undefined): CalendarAttribute;
    showHoliday(value: boolean | undefined): CalendarAttribute;
    needSlide(value: boolean | undefined): CalendarAttribute;
    startOfWeek(value: number | undefined): CalendarAttribute;
    offDays(value: number | undefined): CalendarAttribute;
    direction(value: Axis | undefined): CalendarAttribute;
    currentDayStyle(value: CurrentDayStyle | undefined): CalendarAttribute;
    nonCurrentDayStyle(value: NonCurrentDayStyle | undefined): CalendarAttribute;
    todayStyle(value: TodayStyle | undefined): CalendarAttribute;
    weekStyle(value: WeekStyle | undefined): CalendarAttribute;
    workStateStyle(value: WorkStateStyle | undefined): CalendarAttribute;
    onSelectChange(value: ((event: CalendarSelectedDate) => void) | undefined): CalendarAttribute;
    onRequestData(value: ((event: CalendarRequestedData) => void) | undefined): CalendarAttribute;
}
declare interface CalendarInterface {
    (value: CalendarRequestedMonths): CalendarAttribute;
}
declare enum CalendarAlign {
    START,
    CENTER = 1,
    END = 2,
}
declare interface CalendarOptions {
    hintRadius?: (number|Resource);
    selected?: Date;
    start?: Date;
    end?: Date;
    disabledDateRange?: DateRange[];
}
declare type Callback_Date_Void = ((value0: Date) => void);
declare interface CalendarPickerAttribute extends CommonMethod {
    textStyle(value: PickerTextStyle | undefined): CalendarPickerAttribute;
    onChange(value: ((value0: Date) => void) | undefined): CalendarPickerAttribute;
    markToday(value: boolean | undefined): CalendarPickerAttribute;
    attributeModifier(value: (AttributeModifier<CalendarPickerAttribute>|AttributeModifier<CommonMethod>) | undefined): CalendarPickerAttribute;
    edgeAlign(alignType: CalendarAlign | undefined, offset?: Offset | undefined): CalendarPickerAttribute;
}
declare interface CalendarDialogOptions extends CalendarOptions {
    onAccept?: ((value0: Date) => void);
    onCancel?: VoidCallback;
    onChange?: ((value0: Date) => void);
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    acceptButtonStyle?: PickerDialogButtonStyle;
    cancelButtonStyle?: PickerDialogButtonStyle;
    onDidAppear?: VoidCallback;
    onDidDisappear?: VoidCallback;
    onWillAppear?: VoidCallback;
    onWillDisappear?: VoidCallback;
    shadow?: (ShadowOptions|ShadowStyle);
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    markToday?: boolean;
}
declare class CalendarPickerDialog {
    constructor();
    static show(options?: CalendarDialogOptions): void;
}
declare interface CalendarPickerInterface {
    (options?: CalendarOptions): CalendarPickerAttribute;
}
declare type CanvasFillRule = string;
declare type CanvasLineCap = string;
declare type CanvasLineJoin = string;
declare type CanvasDirection = string;
declare type CanvasTextAlign = string;
declare type CanvasTextBaseline = string;
declare type ImageSmoothingQuality = string;
declare class CanvasGradient {
    constructor();
    addColorStop(offset: number, color: string): void;
}
declare class CanvasPath {
    constructor();
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
    constructor(src: (image.PixelMap|string), unit?: LengthMetricsUnit);
    get height(): number;
    get width(): number;
    close(): void;
}
declare class ImageData {
    constructor(width: number, height: number, data?: ArrayBuffer, unit?: LengthMetricsUnit);
    get data(): ArrayBuffer;
    get height(): number;
    get width(): number;
}
declare class RenderingContextSettings {
    constructor(antialias?: boolean);
    get antialias(): boolean | undefined;
    set antialias(value: boolean | undefined);
}
declare class CanvasRenderer extends CanvasPath {
    constructor();
    get letterSpacing(): (LengthMetrics|string);
    set letterSpacing(value: (LengthMetrics|string));
    get globalAlpha(): number;
    set globalAlpha(value: number);
    get globalCompositeOperation(): string;
    set globalCompositeOperation(value: string);
    get fillStyle(): (string|number|CanvasGradient|CanvasPattern);
    set fillStyle(value: (string|number|CanvasGradient|CanvasPattern));
    get strokeStyle(): (string|number|CanvasGradient|CanvasPattern);
    set strokeStyle(value: (string|number|CanvasGradient|CanvasPattern));
    get filter(): string;
    set filter(value: string);
    get imageSmoothingEnabled(): boolean;
    set imageSmoothingEnabled(value: boolean);
    get imageSmoothingQuality(): ImageSmoothingQuality;
    set imageSmoothingQuality(value: ImageSmoothingQuality);
    get lineCap(): CanvasLineCap;
    set lineCap(value: CanvasLineCap);
    get lineDashOffset(): number;
    set lineDashOffset(value: number);
    get lineJoin(): CanvasLineJoin;
    set lineJoin(value: CanvasLineJoin);
    get lineWidth(): number;
    set lineWidth(value: number);
    get miterLimit(): number;
    set miterLimit(value: number);
    get shadowBlur(): number;
    set shadowBlur(value: number);
    get shadowColor(): string;
    set shadowColor(value: string);
    get shadowOffsetX(): number;
    set shadowOffsetX(value: number);
    get shadowOffsetY(): number;
    set shadowOffsetY(value: number);
    get direction(): CanvasDirection;
    set direction(value: CanvasDirection);
    get font(): string;
    set font(value: string);
    get textAlign(): CanvasTextAlign;
    set textAlign(value: CanvasTextAlign);
    get textBaseline(): CanvasTextBaseline;
    set textBaseline(value: CanvasTextBaseline);
    drawImage(image: (ImageBitmap|image.PixelMap), dx: number, dy: number): void;
    drawImage(image: (ImageBitmap|image.PixelMap), dx: number, dy: number, dw: number, dh: number): void;
    drawImage(image: (ImageBitmap|image.PixelMap), sx: number, sy: number, sw: number, sh: number, dx: number, dy: number, dw: number, dh: number): void;
    beginPath(): void;
    clip(fillRule?: CanvasFillRule): void;
    clip(path: Path2D, fillRule?: CanvasFillRule): void;
    fill(fillRule?: CanvasFillRule): void;
    fill(path: Path2D, fillRule?: CanvasFillRule): void;
    stroke(path?: Path2D): void;
    createLinearGradient(x0: number, y0: number, x1: number, y1: number): CanvasGradient;
    createPattern(image: ImageBitmap, repetition: string | undefined): CanvasPattern | undefined;
    createRadialGradient(x0: number, y0: number, r0: number, x1: number, y1: number, r1: number): CanvasGradient;
    createConicGradient(startAngle: number, x: number, y: number): CanvasGradient;
    createImageData(sw: number, sh: number): ImageData;
    createImageData(imagedata: ImageData): ImageData;
    getImageData(sx: number, sy: number, sw: number, sh: number): ImageData;
    getPixelMap(sx: number, sy: number, sw: number, sh: number): image.PixelMap;
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
    setPixelMap(value?: image.PixelMap): void;
    transferFromImageBitmap(bitmap: ImageBitmap): void;
    saveLayer(): void;
    restoreLayer(): void;
    reset(): void;
}
declare class CanvasRenderingContext2D extends CanvasRenderer {
    constructor(settings?: RenderingContextSettings, unit?: LengthMetricsUnit);
    get height(): number;
    get width(): number;
    get canvas(): FrameNode;
    toDataURL(type?: string, quality?: number): string;
    startImageAnalyzer(config: ImageAnalyzerConfig): Promise<void>;
    stopImageAnalyzer(): void;
    on(type: 'onAttach', callback_: (() => void)): void;
    off(type: 'onAttach', callback_?: (() => void)): void;
    on(type: 'onDetach', callback_: (() => void)): void;
    off(type: 'onDetach', callback_?: (() => void)): void;
}
declare class OffscreenCanvasRenderingContext2D extends CanvasRenderer {
    constructor(width: number, height: number, settings?: RenderingContextSettings, unit?: LengthMetricsUnit);
    toDataURL(type?: string, quality?: number): string;
    transferToImageBitmap(): ImageBitmap;
}
declare class OffscreenCanvas {
    constructor(width: number, height: number, unit?: LengthMetricsUnit);
    get height(): number;
    set height(value: number);
    get width(): number;
    set width(value: number);
    transferToImageBitmap(): ImageBitmap;
    getContext(contextType: '2d', options?: RenderingContextSettings): OffscreenCanvasRenderingContext2D;
}
declare class DrawingRenderingContext {
    constructor(unit?: LengthMetricsUnit);
    get size(): Size;
    invalidate(): void;
}
declare interface CanvasAttribute extends CommonMethod {
    onReady(value: VoidCallback | undefined): CanvasAttribute;
    enableAnalyzer(value: boolean | undefined): CanvasAttribute;
    attributeModifier(value: (AttributeModifier<CanvasAttribute>|AttributeModifier<CommonMethod>) | undefined): CanvasAttribute;
}
declare interface CanvasInterface {
    (context?: (CanvasRenderingContext2D|DrawingRenderingContext)): CanvasAttribute;
    (context: (CanvasRenderingContext2D|DrawingRenderingContext), imageAIOptions: ImageAIOptions): CanvasAttribute;
}
declare interface CheckboxOptions {
    name?: string;
    group?: string;
    indicatorBuilder?: CustomBuilder;
}
declare type Callback_Boolean_Void = ((value0: boolean) => void);
declare interface CheckBoxConfiguration extends CommonConfiguration<CheckBoxConfiguration> {
    name: string;
    selected: boolean;
    triggerChange: ((value0: boolean) => void);
}
declare type OnCheckboxChangeCallback = ((value: boolean) => void);
declare interface CheckboxAttribute extends CommonMethod {
    select(value: boolean | undefined): CheckboxAttribute;
    selectedColor(value: ResourceColor | undefined): CheckboxAttribute;
    shape(value: CheckBoxShape | undefined): CheckboxAttribute;
    unselectedColor(value: ResourceColor | undefined): CheckboxAttribute;
    mark(value: MarkStyle | undefined): CheckboxAttribute;
    onChange(value: OnCheckboxChangeCallback | undefined): CheckboxAttribute;
    contentModifier(value: ContentModifier<CheckBoxConfiguration> | undefined): CheckboxAttribute;
    attributeModifier(value: (AttributeModifier<CheckboxAttribute>|AttributeModifier<CommonMethod>) | undefined): CheckboxAttribute;
}
declare interface CheckboxInterface {
    (options?: CheckboxOptions): CheckboxAttribute;
}
declare enum SelectStatus {
    ALL,
    All,
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
declare type OnCheckboxGroupChangeCallback = ((value: CheckboxGroupResult) => void);
declare interface CheckboxGroupAttribute extends CommonMethod {
    selectAll(value: boolean | undefined): CheckboxGroupAttribute;
    selectedColor(value: ResourceColor | undefined): CheckboxGroupAttribute;
    unselectedColor(value: ResourceColor | undefined): CheckboxGroupAttribute;
    mark(value: MarkStyle | undefined): CheckboxGroupAttribute;
    onChange(value: OnCheckboxGroupChangeCallback | undefined): CheckboxGroupAttribute;
    checkboxShape(value: CheckBoxShape | undefined): CheckboxGroupAttribute;
    attributeModifier(value: (AttributeModifier<CheckboxGroupAttribute>|AttributeModifier<CommonMethod>) | undefined): CheckboxGroupAttribute;
}
declare interface CheckboxGroupInterface {
    (options?: CheckboxGroupOptions): CheckboxGroupAttribute;
}
declare interface CircleOptions {
    width?: (string|number);
    height?: (string|number);
}
declare interface CircleAttribute extends CommonShapeMethod {
    attributeModifier(value: (AttributeModifier<CircleAttribute>|AttributeModifier<CommonMethod>) | undefined): CircleAttribute;
}
declare interface CircleInterface {
    (value?: CircleOptions): CircleAttribute;
}
declare type SpaceType = (string|number|Resource);
declare interface ColumnOptions {
    space?: SpaceType;
}
declare interface ColumnAttribute extends CommonMethod {
    alignItems(value: HorizontalAlign | undefined): ColumnAttribute;
    justifyContent(value: FlexAlign | undefined): ColumnAttribute;
    pointLight(value: PointLightStyle | undefined): ColumnAttribute;
    reverse(value: boolean | undefined): ColumnAttribute;
    attributeModifier(value: (AttributeModifier<ColumnAttribute>|AttributeModifier<CommonMethod>) | undefined): ColumnAttribute;
}
declare interface ColumnInterface {
    (options?: ColumnOptions): ColumnAttribute;
}
declare interface ColumnSplitDividerStyle {
    startMargin?: Dimension;
    endMargin?: Dimension;
}
declare interface ColumnSplitAttribute extends CommonMethod {
    resizeable(value: boolean | undefined): ColumnSplitAttribute;
    divider(value: ColumnSplitDividerStyle | undefined): ColumnSplitAttribute;
    attributeModifier(value: (AttributeModifier<ColumnSplitAttribute>|AttributeModifier<CommonMethod>) | undefined): ColumnSplitAttribute;
}
declare interface ColumnSplitInterface {
    (): ColumnSplitAttribute;
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
declare interface DividerStyle {
    strokeWidth: Length;
    color?: ResourceColor;
    startMargin?: Length;
    endMargin?: Length;
}
declare type ReuseIdCallback = (() => string);
declare interface ReuseOptions {
    reuseId?: ReuseIdCallback;
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
declare function $r(value: string, params: Object | undefined[]): Resource;
declare function $rawfile(value: string): Resource;
declare enum AccessibilitySamePageMode {
    SEMI_SILENT,
    FULL_SILENT = 1,
}
declare enum AccessibilityRoleType {
    ACTION_SHEET,
    ALERT_DIALOG = 1,
    INDEXER_COMPONENT = 2,
    BADGE_COMPONENT = 3,
    BLANK = 4,
    BUTTON = 5,
    BACK_BUTTON = 6,
    SHEET_DRAG_BAR = 7,
    CALENDAR_PICKER = 8,
    CALENDAR = 9,
    CANVAS = 10,
    CANVAS_GRADIENT = 11,
    CANVAS_PATTERN = 12,
    CHECKBOX = 13,
    CHECKBOX_GROUP = 14,
    CIRCLE = 15,
    COLUMN_SPLIT = 16,
    COLUMN = 17,
    CANVAS_RENDERING_CONTEXT_2D = 18,
    CHART = 19,
    COUNTER = 20,
    CONTAINER_MODAL = 21,
    DATA_PANEL = 22,
    DATE_PICKER = 23,
    DIALOG = 24,
    DIVIDER = 25,
    DRAG_BAR = 26,
    EFFECT_COMPONENT = 27,
    ELLIPSE = 28,
    FLEX = 29,
    FLOW_ITEM = 30,
    FORM_COMPONENT = 31,
    FORM_LINK = 32,
    GAUGE = 33,
    GRID = 34,
    GRID_COL = 35,
    GRID_CONTAINER = 36,
    GRID_ITEM = 37,
    GRID_ROW = 38,
    HYPERLINK = 39,
    IMAGE = 40,
    IMAGE_ANIMATOR = 41,
    IMAGE_BITMAP = 42,
    IMAGE_DATA = 43,
    IMAGE_SPAN = 44,
    LABEL = 45,
    LINE = 46,
    LIST = 47,
    LIST_ITEM = 48,
    LIST_ITEM_GROUP = 49,
    LOADING_PROGRESS = 50,
    MARQUEE = 51,
    MATRIX2D = 52,
    MENU = 53,
    MENU_ITEM = 54,
    MENU_ITEM_GROUP = 55,
    NAV_DESTINATION = 56,
    NAV_ROUTER = 57,
    NAVIGATION = 58,
    NAVIGATION_BAR = 59,
    NAVIGATION_MENU = 60,
    NAVIGATOR = 61,
    OFFSCREEN_CANVAS = 62,
    OFFSCREEN_CANVAS_RENDERING_CONTEXT2D = 63,
    OPTION = 64,
    PANEL = 65,
    PAPER_PAGE = 66,
    PATH = 67,
    PATH2D = 68,
    PATTERN_LOCK = 69,
    PICKER = 70,
    PICKER_VIEW = 71,
    PLUGIN_COMPONENT = 72,
    POLYGON = 73,
    POLYLINE = 74,
    POPUP = 75,
    PROGRESS = 76,
    QRCODE = 77,
    RADIO = 78,
    RATING = 79,
    RECT = 80,
    REFRESH = 81,
    RELATIVE_CONTAINER = 82,
    REMOTE_WINDOW = 83,
    RICH_EDITOR = 84,
    RICH_TEXT = 85,
    ROLE_PAGER = 86,
    ROW = 87,
    ROW_SPLIT = 88,
    SCROLL = 89,
    SCROLL_BAR = 90,
    SEARCH = 91,
    SEARCH_FIELD = 92,
    SELECT = 93,
    SHAPE = 94,
    SIDEBAR_CONTAINER = 95,
    SLIDER = 96,
    SPAN = 97,
    STACK = 98,
    STEPPER = 99,
    STEPPER_ITEM = 100,
    SWIPER = 101,
    SWIPER_INDICATOR = 102,
    SWITCH = 103,
    SYMBOL_GLYPH = 104,
    TAB_CONTENT = 105,
    TAB_BAR = 106,
    TABS = 107,
    TEXT = 108,
    TEXT_CLOCK = 109,
    TEXT_ENTRY = 110,
    TEXT_INPUT = 111,
    TEXT_PICKER = 112,
    TEXT_TIMER = 113,
    TEXT_AREA = 114,
    TEXT_FIELD = 115,
    TIME_PICKER = 116,
    TITLE_BAR = 117,
    TOGGLER = 118,
    UI_EXTENSION_COMPONENT = 119,
    VIDEO = 120,
    WATER_FLOW = 121,
    WEB = 122,
    XCOMPONENT = 123,
    ROLE_NONE = 124,
}
declare type AccessibilityFocusCallback = ((isFocus: boolean) => void);
declare enum FinishCallbackType {
    REMOVED,
    LOGICALLY = 1,
}
declare enum TouchTestStrategy {
    DEFAULT,
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
declare type Tuple_ResourceColor_Number = [ ResourceColor, number ]
declare interface LinearGradientOptions {
    angle?: (number|string);
    direction?: GradientDirection;
    colors: [ ResourceColor, number ][];
    repeating?: boolean;
}
declare type Tuple_Length_Length = [ Length, Length ]
declare interface SweepGradientOptions {
    center: [ Length, Length ];
    start?: (number|string);
    end?: (number|string);
    rotation?: (number|string);
    colors: [ ResourceColor, number ][];
    repeating?: boolean;
}
declare interface RadialGradientOptions {
    center: [ Length, Length ];
    radius: Length;
    colors: [ ResourceColor, number ][];
    repeating?: boolean;
}
declare enum TransitionHierarchyStrategy {
    NONE,
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
declare interface AlignRuleParam<T> {
    anchor: string;
    align: T;
}
declare interface AlignRuleOption {
    _stub: number;
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
    SPREAD,
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
declare enum TransitionEdge {
    TOP,
    BOTTOM = 1,
    START = 2,
    END = 3,
}
declare interface AsymmetricTransitionOption {
    appear: TransitionEffect;
    disappear: TransitionEffect;
}
declare type Callback_DrawContext_Void = ((drawContext: DrawContext) => void);
declare class DrawModifier {
    constructor();
    drawBehind_callback: ((drawContext: DrawContext) => void);
    drawContent_callback: ((drawContext: DrawContext) => void);
    drawFront_callback: ((drawContext: DrawContext) => void);
    invalidate(): void;
}
declare class TransitionEffect {
    constructor(type: string);
    constructor(effect: number);
    constructor(effect: TransitionEdge);
    constructor(effect: TranslateOptions);
    constructor(effect: RotateOptions);
    constructor(effect: ScaleOptions);
    constructor(effect: AsymmetricTransitionOption);
    static readonly IDENTITY: TransitionEffect;
    static readonly OPACITY: TransitionEffect;
    static readonly SLIDE: TransitionEffect;
    static readonly SLIDE_SWITCH: TransitionEffect;
    static translate(options: TranslateOptions): TransitionEffect;
    static rotate(options: RotateOptions): TransitionEffect;
    static scale(options: ScaleOptions): TransitionEffect;
    static opacity(alpha: number): TransitionEffect;
    static move(edge: TransitionEdge): TransitionEffect;
    static asymmetric(appear: TransitionEffect, disappear: TransitionEffect): TransitionEffect;
    animation(value: AnimateParam): TransitionEffect;
    combine(transitionEffect: TransitionEffect): TransitionEffect;
}
declare interface ItemDragInfo {
    x: number;
    y: number;
}
declare enum EffectType {
    DEFAULT,
    WINDOW_EFFECT = 1,
}
declare enum PreDragStatus {
    ACTION_DETECTING_STATUS,
    READY_TO_TRIGGER_DRAG_ACTION = 1,
    PREVIEW_LIFT_STARTED = 2,
    PREVIEW_LIFT_FINISHED = 3,
    PREVIEW_LANDING_STARTED = 4,
    PREVIEW_LANDING_FINISHED = 5,
    ACTION_CANCELED_BEFORE_DRAG = 6,
    PREPARING_FOR_DRAG_DETECTION = 7,
}
declare interface DragItemInfo {
    pixelMap?: image.PixelMap;
    builder?: CustomBuilder;
    extraInfo?: string;
}
declare function animateTo(value: AnimateParam, event: (() => void)): void;
declare function animateToImmediately(value: AnimateParam, event: (() => void)): void;
declare function vp2px(value: number): number;
declare function px2vp(value: number): number;
declare namespace focusControl {
    function requestFocus(value: string): boolean;
}
declare type PointerStyle = pointer.PointerStyle;
declare namespace cursorControl {
    function setCursor(value: pointer.PointerStyle): void;
}
declare namespace cursorControl {
    function restoreDefault(): void;
}
declare interface EventTarget {
    area: Area;
    id?: string;
}
declare enum SourceType {
    UNKNOWN,
    Unknown,
    MOUSE = 1,
    Mouse = 1,
    TOUCH_SCREEN = 2,
    TouchScreen = 2,
}
declare enum SourceTool {
    UNKNOWN,
    Unknown,
    FINGER = 1,
    Finger = 1,
    PEN = 2,
    Pen = 2,
    MOUSE = 3,
    TOUCHPAD = 4,
    JOYSTICK = 5,
}
declare enum RepeatMode {
    REPEAT,
    Repeat,
    STRETCH = 1,
    Stretch = 1,
    ROUND = 2,
    Round = 2,
    SPACE = 3,
    Space = 3,
}
declare enum BlurStyle {
    THIN,
    Thin,
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
    FOLLOWS_WINDOW_ACTIVE_STATE,
    ALWAYS_ACTIVE = 1,
    ALWAYS_INACTIVE = 2,
}
declare enum ThemeColorMode {
    SYSTEM,
    LIGHT = 1,
    DARK = 2,
}
declare enum AdaptiveColor {
    DEFAULT,
    AVERAGE = 1,
}
declare enum ModalTransition {
    DEFAULT,
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
declare interface SystemAdaptiveOptions {
    disableSystemAdaptation?: boolean;
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
    COLOR,
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
    OUTER_DEFAULT_XS,
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
    SYSTEM,
    CUTOUT = 1,
    KEYBOARD = 2,
}
declare enum SafeAreaEdge {
    TOP,
    BOTTOM = 1,
    START = 2,
    END = 3,
}
declare enum LayoutSafeAreaType {
    SYSTEM,
}
declare enum LayoutSafeAreaEdge {
    TOP,
    BOTTOM = 1,
}
declare enum SheetSize {
    MEDIUM,
    LARGE = 1,
    FIT_CONTENT = 2,
}
declare type ModifierKeyStateGetter = ((keys: string[]) => boolean);
declare interface BaseEvent {
    target: EventTarget;
    timestamp: number;
    source: SourceType;
    axisHorizontal?: number;
    axisVertical?: number;
    pressure: number;
    tiltX: number;
    tiltY: number;
    rollAngle?: number;
    sourceTool: SourceTool;
    getModifierKeyState?: ModifierKeyStateGetter;
    deviceId?: number;
    targetDisplayId?: number;
}
declare interface BorderImageOption {
    slice?: (Length|EdgeWidths|LocalizedEdgeWidths);
    repeat?: RepeatMode;
    source?: (string|Resource|LinearGradientOptions);
    width?: (Length|EdgeWidths|LocalizedEdgeWidths);
    outset?: (Length|EdgeWidths|LocalizedEdgeWidths);
    fill?: boolean;
}
declare class LayoutPolicy {
    constructor();
    static readonly matchParent: LayoutPolicy;
}
declare interface ClickEvent extends BaseEvent {
    displayX: number;
    displayY: number;
    windowX: number;
    windowY: number;
    x: number;
    y: number;
    hand?: InteractionHand;
    preventDefault: (() => void);
}
declare interface HoverEvent extends BaseEvent {
    x?: number;
    y?: number;
    windowX?: number;
    windowY?: number;
    displayX?: number;
    displayY?: number;
    stopPropagation: (() => void);
}
declare interface MouseEvent extends BaseEvent {
    button: MouseButton;
    action: MouseAction;
    displayX: number;
    displayY: number;
    windowX: number;
    windowY: number;
    x: number;
    y: number;
    stopPropagation: (() => void);
    rawDeltaX?: number;
    rawDeltaY?: number;
    pressedButtons?: MouseButton[];
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
    x: number;
    y: number;
    hand?: InteractionHand;
    pressedTime?: number;
    pressure?: number;
    width?: number;
    height?: number;
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
declare interface AxisEvent extends BaseEvent {
    action: AxisAction;
    displayX: number;
    displayY: number;
    windowX: number;
    windowY: number;
    x: number;
    y: number;
    scrollStep?: number;
    propagation: (() => void);
    getHorizontalAxisValue(): number;
    getVerticalAxisValue(): number;
}
declare type SizeChangeCallback = ((oldValue: SizeOptions, newValue: SizeOptions) => void);
declare type GestureRecognizerJudgeBeginCallback = ((event: BaseGestureEvent, current: GestureRecognizer, recognizers: GestureRecognizer[]) => GestureJudgeResult);
declare type ShouldBuiltInRecognizerParallelWithCallback = ((current: GestureRecognizer, others: GestureRecognizer[]) => GestureRecognizer);
declare type TransitionFinishCallback = ((transitionIn: boolean) => void);
declare type PixelMap = image.PixelMap;
declare interface PixelMapMock {
    release(): void;
}
declare enum DragBehavior {
    COPY,
    MOVE = 1,
}
declare type UnifiedData = unifiedDataChannel.UnifiedData;
declare type Summary = unifiedDataChannel.Summary;
declare type UniformDataType = uniformTypeDescriptor.UniformDataType;
declare enum DragResult {
    UNKNOWN = -1,
    DRAG_SUCCESSFUL,
    DRAG_FAILED = 1,
    DRAG_CANCELED = 2,
    DROP_ENABLED = 3,
    DROP_DISABLED = 4,
}
declare enum BlendMode {
    NONE,
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
    FAST,
    OFFSCREEN = 1,
}
declare interface DragEvent {
    dragBehavior: DragBehavior;
    useCustomDropAnimation: boolean;
    getModifierKeyState?: ModifierKeyStateGetter;
    getDisplayX(): number;
    getDisplayY(): number;
    getWindowX(): number;
    getWindowY(): number;
    setData(unifiedData: unifiedDataChannel.UnifiedData): void;
    getData(): unifiedDataChannel.UnifiedData;
    getSummary(): unifiedDataChannel.Summary;
    setResult(dragResult: DragResult): void;
    getResult(): DragResult;
    getPreviewRect(): Rectangle;
    getVelocityX(): number;
    getVelocityY(): number;
    getVelocity(): number;
    executeDropAnimation(customDropAnimation: (() => void)): void;
}
declare type OnDragEventCallback = ((event: DragEvent, extraParams?: string) => void);
declare interface DropOptions {
    disableDataPrefetch?: boolean;
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
    getModifierKeyState?: ModifierKeyStateGetter;
    unicode?: number;
}
declare interface FocusAxisEvent extends BaseEvent {
    axisMap: Map<AxisModel,number>;
    stopPropagation: (() => void);
}
declare interface CrownEvent {
    timestamp: number;
    angularVelocity: number;
    degree: number;
    action: CrownAction;
    stopPropagation: (() => void);
}
declare interface BindOptions {
    backgroundColor?: ResourceColor;
    onAppear?: (() => void);
    onDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
}
declare interface DismissContentCoverAction {
    dismiss: VoidCallback;
    reason: DismissReason;
}
declare type Callback_DismissContentCoverAction_Void = ((value0: DismissContentCoverAction) => void);
declare interface ContentCoverOptions extends BindOptions {
    modalTransition?: ModalTransition;
    onWillDismiss?: ((value0: DismissContentCoverAction) => void);
    transition?: TransitionEffect;
}
declare interface SheetTitleOptions {
    title: ResourceStr;
    subtitle?: ResourceStr;
}
declare enum SheetType {
    BOTTOM,
    CENTER = 1,
    POPUP = 2,
}
declare enum SheetMode {
    OVERLAY,
    EMBEDDED = 1,
}
declare enum ScrollSizeMode {
    FOLLOW_DETENT,
    CONTINUOUS = 1,
}
declare enum SheetKeyboardAvoidMode {
    NONE,
    TRANSLATE_AND_RESIZE = 1,
    RESIZE_ONLY = 2,
    TRANSLATE_AND_SCROLL = 3,
}
declare interface SheetDismiss {
    dismiss: VoidCallback;
}
declare interface DismissSheetAction {
    dismiss: VoidCallback;
    reason: DismissReason;
}
declare interface SpringBackAction {
    springBack: VoidCallback;
}
declare type SingleLengthDetent = [ (SheetSize|Length) ]
declare type DoubleLengthDetents = [ (SheetSize|Length), (SheetSize|Length) | undefined ]
declare type TripleLengthDetents = [ (SheetSize|Length), (SheetSize|Length) | undefined, (SheetSize|Length) | undefined ]
declare type Callback_SheetDismiss_Void = ((sheetDismiss: SheetDismiss) => void);
declare type Callback_DismissSheetAction_Void = ((value0: DismissSheetAction) => void);
declare type Callback_SpringBackAction_Void = ((value0: SpringBackAction) => void);
declare type Callback_SheetType_Void = ((value0: SheetType) => void);
declare interface SheetOptions extends BindOptions {
    height?: (SheetSize|Length);
    dragBar?: boolean;
    maskColor?: ResourceColor;
    detents?: TripleLengthDetents;
    blurStyle?: BlurStyle;
    showClose?: (boolean|Resource);
    preferType?: SheetType;
    title?: (SheetTitleOptions|CustomBuilder);
    shouldDismiss?: ((sheetDismiss: SheetDismiss) => void);
    onWillDismiss?: ((value0: DismissSheetAction) => void);
    onWillSpringBackWhenDismiss?: ((value0: SpringBackAction) => void);
    enableOutsideInteractive?: boolean;
    width?: Dimension;
    borderWidth?: (Dimension|EdgeWidths|LocalizedEdgeWidths);
    borderColor?: (ResourceColor|EdgeColors|LocalizedEdgeColors);
    borderStyle?: (BorderStyle|EdgeStyles);
    shadow?: (ShadowOptions|ShadowStyle);
    onHeightDidChange?: ((value0: number) => void);
    mode?: SheetMode;
    scrollSizeMode?: ScrollSizeMode;
    onDetentsDidChange?: ((value0: number) => void);
    onWidthDidChange?: ((value0: number) => void);
    onTypeDidChange?: ((value0: SheetType) => void);
    uiContext?: UIContext;
    keyboardAvoidMode?: SheetKeyboardAvoidMode;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    offset?: Position;
    effectEdge?: number;
    radius?: (LengthMetrics|BorderRadiuses|LocalizedBorderRadiuses);
    detentSelection?: (SheetSize|Length);
    showInSubWindow?: boolean;
    placement?: Placement;
    placementOnTarget?: boolean;
}
declare type CustomStyles = ((instance: string) => void);
declare interface StateStyles {
    normal?: CustomStyles;
    pressed?: CustomStyles;
    disabled?: CustomStyles;
    focused?: CustomStyles;
    clicked?: CustomStyles;
    selected?: CustomStyles;
}
declare interface PopupMessageOptions {
    textColor?: ResourceColor;
    font?: Font;
}
declare enum DismissReason {
    PRESS_BACK,
    TOUCH_OUTSIDE = 1,
    CLOSE_BUTTON = 2,
    SLIDE_DOWN = 3,
}
declare interface DismissPopupAction {
    dismiss: (() => void);
    reason: DismissReason;
}
declare interface PopupStateChangeParam {
    isVisible: boolean;
}
declare type PopupStateChangeCallback = ((event: PopupStateChangeParam) => void);
declare interface PopupMaskType {
    color: ResourceColor;
}
declare type Callback_DismissPopupAction_Void = ((value0: DismissPopupAction) => void);
declare interface PopupCommonOptions {
    placement?: Placement;
    popupColor?: ResourceColor;
    enableArrow?: boolean;
    autoCancel?: boolean;
    onStateChange?: PopupStateChangeCallback;
    arrowOffset?: Length;
    showInSubWindow?: boolean;
    mask?: (boolean|PopupMaskType);
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
    onWillDismiss?: (boolean|((value0: DismissPopupAction) => void));
    enableHoverMode?: boolean;
    followTransformOfTarget?: boolean;
}
declare interface TipsOptions {
    appearingTime?: number;
    disappearingTime?: number;
    appearingTimeWithContinuousOperation?: number;
    disappearingTimeWithContinuousOperation?: number;
    enableArrow?: boolean;
    arrowPointPosition?: ArrowPointPosition;
    arrowWidth?: Dimension;
    arrowHeight?: Dimension;
}
declare interface PopupButton {
    value: string;
    action: (() => void);
}
declare interface PopupOptions {
    message: string;
    placement?: Placement;
    primaryButton?: PopupButton;
    secondaryButton?: PopupButton;
    onStateChange?: PopupStateChangeCallback;
    arrowOffset?: Length;
    showInSubWindow?: boolean;
    mask?: (boolean|PopupMaskType);
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
    onWillDismiss?: (boolean|((value0: DismissPopupAction) => void));
    enableHoverMode?: boolean;
    followTransformOfTarget?: boolean;
    keyboardAvoidMode?: KeyboardAvoidMode;
}
declare interface CustomPopupOptions {
    builder: CustomBuilder;
    placement?: Placement;
    popupColor?: (Color|string|Resource|number);
    enableArrow?: boolean;
    autoCancel?: boolean;
    onStateChange?: PopupStateChangeCallback;
    arrowOffset?: Length;
    showInSubWindow?: boolean;
    mask?: (boolean|PopupMaskType);
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
    onWillDismiss?: (boolean|((value0: DismissPopupAction) => void));
    enableHoverMode?: boolean;
    followTransformOfTarget?: boolean;
    keyboardAvoidMode?: KeyboardAvoidMode;
}
declare enum MenuPreviewMode {
    NONE,
    IMAGE = 1,
}
declare type AnimationNumberRange = [ number, number ]
declare interface ContextMenuAnimationOptions {
    scale?: AnimationNumberRange;
    transition?: TransitionEffect;
    hoverScale?: AnimationNumberRange;
}
declare type BorderRadiusType = (Length|BorderRadiuses|LocalizedBorderRadiuses);
declare enum HapticFeedbackMode {
    DISABLED,
    ENABLED = 1,
    AUTO = 2,
}
declare interface ContextMenuOptions {
    offset?: Position;
    placement?: Placement;
    enableArrow?: boolean;
    arrowOffset?: Length;
    preview?: (MenuPreviewMode|CustomBuilder);
    previewBorderRadius?: BorderRadiusType;
    borderRadius?: (Length|BorderRadiuses|LocalizedBorderRadiuses);
    onAppear?: (() => void);
    onDisappear?: (() => void);
    aboutToAppear?: (() => void);
    aboutToDisappear?: (() => void);
    layoutRegionMargin?: Padding;
    previewAnimationOptions?: ContextMenuAnimationOptions;
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    transition?: TransitionEffect;
    enableHoverMode?: boolean;
    outlineColor?: (ResourceColor|EdgeColors);
    outlineWidth?: (Dimension|EdgeOutlineWidths);
    hapticFeedbackMode?: HapticFeedbackMode;
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
    constructor();
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
    constructor();
    strategy: TouchTestStrategy;
    id?: string | undefined;
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
declare type Callback_T_Void<T> = ((instance: T) => void);
declare interface AttributeModifier<T> {
    applyNormalAttribute?: ((instance: T) => void);
    applyPressedAttribute?: ((instance: T) => void);
    applyFocusedAttribute?: ((instance: T) => void);
    applyDisabledAttribute?: ((instance: T) => void);
    applySelectedAttribute?: ((instance: T) => void);
}
declare interface ContentModifier<T> {
    applyContent(): WrappedBuilder;
}
declare interface CommonConfiguration<T> {
    enabled: boolean;
    contentModifier: ContentModifier<T>;
}
declare enum OutlineStyle {
    SOLID,
    DASHED = 1,
    DOTTED = 2,
}
declare enum DragPreviewMode {
    AUTO = 1,
    DISABLE_SCALE = 2,
    ENABLE_DEFAULT_SHADOW = 3,
    ENABLE_DEFAULT_RADIUS = 4,
    ENABLE_DRAG_ITEM_GRAY_EFFECT = 5,
    ENABLE_MULTI_TILE_EFFECT = 6,
    ENABLE_TOUCH_POINT_CALCULATION_BASED_ON_FINAL_PREVIEW = 7,
}
declare enum DraggingSizeChangeEffect {
    DEFAULT,
    SIZE_TRANSITION = 1,
    SIZE_CONTENT_TRANSITION = 2,
}
declare enum MenuPolicy {
    DEFAULT,
    HIDE = 1,
    SHOW = 2,
}
declare interface DragPreviewOptions {
    mode?: (DragPreviewMode|DragPreviewMode[]);
    numberBadge?: (boolean|number);
    sizeChangeEffect?: DraggingSizeChangeEffect;
}
declare interface DragInteractionOptions {
    isMultiSelectionEnabled?: boolean;
    defaultAnimationBeforeLifting?: boolean;
    enableEdgeAutoScroll?: boolean;
    enableHapticFeedback?: boolean;
    isLiftingDisabled?: boolean;
}
declare interface PreviewConfiguration {
    onlyForLifting?: boolean;
    delayCreating?: boolean;
}
declare interface InvertOptions {
    low: number;
    high: number;
    threshold: number;
    thresholdRange: number;
}
declare type Optional<T> = T | undefined;
declare type TipsMessageType = (ResourceStr|StyledString);
declare interface BackgroundImageOptions {
    syncLoad?: boolean;
    repeat?: ImageRepeat;
}
declare interface BackgroundOptions {
    align?: Alignment;
}
declare type Callback_Array_TouchTestInfo_TouchResult = ((value: TouchTestInfo[]) => TouchResult);
declare type Callback_ClickEvent_Void = ((event: ClickEvent) => void);
declare type Callback_Boolean_HoverEvent_Void = ((isHover: boolean, event: HoverEvent) => void);
declare type Callback_HoverEvent_Void = ((value0: HoverEvent) => void);
declare type Callback_MouseEvent_Void = ((event: MouseEvent) => void);
declare type Callback_TouchEvent_Void = ((event: TouchEvent) => void);
declare type Callback_KeyEvent_Void = ((event: KeyEvent) => void);
declare type Callback_KeyEvent_Boolean = ((value0: KeyEvent) => boolean);
declare type Callback_CrownEvent_Void = ((value0: CrownEvent) => void);
declare type Callback_FocusAxisEvent_Void = ((value0: FocusAxisEvent) => void);
declare type Callback_AxisEvent_Void = ((value0: AxisEvent) => void);
declare type Callback_Area_Area_Void = ((oldValue: Area, newValue: Area) => void);
declare type Type_CommonMethod_onDragStart = ((event: DragEvent, extraParams?: string) => (CustomBuilder|DragItemInfo));
declare type Callback_DragEvent_Opt_String_Void = ((event: DragEvent, extraParams?: string) => void);
declare type Callback_PreDragStatus_Void = ((value0: PreDragStatus) => void);
declare type Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult = ((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult);
declare type Callback_TouchEvent_HitTestMode = ((value0: TouchEvent) => HitTestMode);
declare interface CommonMethod {
    width(value: (Length|LayoutPolicy) | undefined): CommonMethod;
    height(value: (Length|LayoutPolicy) | undefined): CommonMethod;
    drawModifier(value: DrawModifier | undefined): CommonMethod;
    responseRegion(value: (Rectangle[]|Rectangle) | undefined): CommonMethod;
    mouseResponseRegion(value: (Rectangle[]|Rectangle) | undefined): CommonMethod;
    size(value: SizeOptions | undefined): CommonMethod;
    constraintSize(value: ConstraintSizeOptions | undefined): CommonMethod;
    hitTestBehavior(value: HitTestMode | undefined): CommonMethod;
    onChildTouchTest(value: ((value: TouchTestInfo[]) => TouchResult) | undefined): CommonMethod;
    layoutWeight(value: (number|string) | undefined): CommonMethod;
    chainWeight(value: ChainWeightOptions | undefined): CommonMethod;
    padding(value: (Padding|Length|LocalizedPadding) | undefined): CommonMethod;
    safeAreaPadding(value: (Padding|LengthMetrics|LocalizedPadding) | undefined): CommonMethod;
    margin(value: (Padding|Length|LocalizedPadding) | undefined): CommonMethod;
    backgroundColor(value: ResourceColor | undefined): CommonMethod;
    pixelRound(value: PixelRoundPolicy | undefined): CommonMethod;
    backgroundImageSize(value: (SizeOptions|ImageSize) | undefined): CommonMethod;
    backgroundImagePosition(value: (Position|Alignment) | undefined): CommonMethod;
    backgroundEffect(value: BackgroundEffectOptions | undefined): CommonMethod;
    backgroundImageResizable(value: ResizableOptions | undefined): CommonMethod;
    foregroundEffect(value: ForegroundEffectOptions | undefined): CommonMethod;
    visualEffect(value: uiEffect.VisualEffect | undefined): CommonMethod;
    backgroundFilter(value: uiEffect.Filter | undefined): CommonMethod;
    foregroundFilter(value: uiEffect.Filter | undefined): CommonMethod;
    compositingFilter(value: uiEffect.Filter | undefined): CommonMethod;
    opacity(value: (number|Resource) | undefined): CommonMethod;
    border(value: BorderOptions | undefined): CommonMethod;
    borderStyle(value: (BorderStyle|EdgeStyles) | undefined): CommonMethod;
    borderWidth(value: (Length|EdgeWidths|LocalizedEdgeWidths) | undefined): CommonMethod;
    borderColor(value: (ResourceColor|EdgeColors|LocalizedEdgeColors) | undefined): CommonMethod;
    borderRadius(value: (Length|BorderRadiuses|LocalizedBorderRadiuses) | undefined): CommonMethod;
    borderImage(value: BorderImageOption | undefined): CommonMethod;
    outline(value: OutlineOptions | undefined): CommonMethod;
    outlineStyle(value: (OutlineStyle|EdgeOutlineStyles) | undefined): CommonMethod;
    outlineWidth(value: (Dimension|EdgeOutlineWidths) | undefined): CommonMethod;
    outlineColor(value: (ResourceColor|EdgeColors|LocalizedEdgeColors) | undefined): CommonMethod;
    outlineRadius(value: (Dimension|OutlineRadiuses) | undefined): CommonMethod;
    foregroundColor(value: (ResourceColor|ColoringStrategy) | undefined): CommonMethod;
    onClick(value: ((event: ClickEvent) => void) | undefined): CommonMethod;
    onHover(value: ((isHover: boolean, event: HoverEvent) => void) | undefined): CommonMethod;
    onHoverMove(value: ((value0: HoverEvent) => void) | undefined): CommonMethod;
    onAccessibilityHover(value: AccessibilityCallback | undefined): CommonMethod;
    hoverEffect(value: HoverEffect | undefined): CommonMethod;
    onMouse(value: ((event: MouseEvent) => void) | undefined): CommonMethod;
    onTouch(value: ((event: TouchEvent) => void) | undefined): CommonMethod;
    onKeyEvent(value: ((event: KeyEvent) => void) | undefined): CommonMethod;
    onKeyEvent(value: ((value0: KeyEvent) => boolean) | undefined): CommonMethod;
    onDigitalCrown(value: ((value0: CrownEvent) => void) | undefined): CommonMethod;
    onKeyPreIme(value: ((value0: KeyEvent) => boolean) | undefined): CommonMethod;
    onKeyEventDispatch(value: ((value0: KeyEvent) => boolean) | undefined): CommonMethod;
    onFocusAxisEvent(value: ((value0: FocusAxisEvent) => void) | undefined): CommonMethod;
    onAxisEvent(value: ((value0: AxisEvent) => void) | undefined): CommonMethod;
    focusable(value: boolean | undefined): CommonMethod;
    nextFocus(value: FocusMovement | undefined): CommonMethod;
    tabStop(value: boolean | undefined): CommonMethod;
    onFocus(value: (() => void) | undefined): CommonMethod;
    onBlur(value: (() => void) | undefined): CommonMethod;
    tabIndex(value: number | undefined): CommonMethod;
    defaultFocus(value: boolean | undefined): CommonMethod;
    groupDefaultFocus(value: boolean | undefined): CommonMethod;
    focusOnTouch(value: boolean | undefined): CommonMethod;
    focusBox(value: FocusBoxStyle | undefined): CommonMethod;
    animation(value: AnimateParam | undefined): CommonMethod;
    transition(value: TransitionEffect | undefined): CommonMethod;
    motionBlur(value: MotionBlurOptions | undefined): CommonMethod;
    brightness(value: number | undefined): CommonMethod;
    contrast(value: number | undefined): CommonMethod;
    grayscale(value: number | undefined): CommonMethod;
    colorBlend(value: (Color|string|Resource) | undefined): CommonMethod;
    saturate(value: number | undefined): CommonMethod;
    sepia(value: number | undefined): CommonMethod;
    invert(value: (number|InvertOptions) | undefined): CommonMethod;
    hueRotate(value: (number|string) | undefined): CommonMethod;
    useShadowBatching(value: boolean | undefined): CommonMethod;
    useEffect(value: boolean | undefined): CommonMethod;
    renderGroup(value: boolean | undefined): CommonMethod;
    freeze(value: boolean | undefined): CommonMethod;
    translate(value: TranslateOptions | undefined): CommonMethod;
    scale(value: ScaleOptions | undefined): CommonMethod;
    rotate(value: RotateOptions | undefined): CommonMethod;
    transform(value: Object | undefined): CommonMethod;
    onAppear(value: (() => void) | undefined): CommonMethod;
    onDisAppear(value: (() => void) | undefined): CommonMethod;
    onAttach(value: VoidCallback | undefined): CommonMethod;
    onDetach(value: VoidCallback | undefined): CommonMethod;
    onAreaChange(value: ((oldValue: Area, newValue: Area) => void) | undefined): CommonMethod;
    visibility(value: Visibility | undefined): CommonMethod;
    flexGrow(value: number | undefined): CommonMethod;
    flexShrink(value: number | undefined): CommonMethod;
    flexBasis(value: (number|string) | undefined): CommonMethod;
    alignSelf(value: ItemAlign | undefined): CommonMethod;
    displayPriority(value: number | undefined): CommonMethod;
    zIndex(value: number | undefined): CommonMethod;
    direction(value: Direction | undefined): CommonMethod;
    align(value: Alignment | undefined): CommonMethod;
    position(value: (Position|Edges|LocalizedEdges) | undefined): CommonMethod;
    markAnchor(value: (Position|LocalizedPosition) | undefined): CommonMethod;
    offset(value: (Position|Edges|LocalizedEdges) | undefined): CommonMethod;
    enabled(value: boolean | undefined): CommonMethod;
    alignRules(value: AlignRuleOption | undefined): CommonMethod;
    alignRules(value: LocalizedAlignRuleOptions | undefined): CommonMethod;
    aspectRatio(value: number | undefined): CommonMethod;
    clickEffect(value: ClickEffect | undefined): CommonMethod;
    onDragStart(value: ((event: DragEvent, extraParams?: string) => (CustomBuilder|DragItemInfo)) | undefined): CommonMethod;
    onDragEnter(value: ((event: DragEvent, extraParams?: string) => void) | undefined): CommonMethod;
    onDragMove(value: ((event: DragEvent, extraParams?: string) => void) | undefined): CommonMethod;
    onDragLeave(value: ((event: DragEvent, extraParams?: string) => void) | undefined): CommonMethod;
    onDrop(value: ((event: DragEvent, extraParams?: string) => void) | undefined): CommonMethod;
    onDragEnd(value: ((event: DragEvent, extraParams?: string) => void) | undefined): CommonMethod;
    allowDrop(value: uniformTypeDescriptor.UniformDataType[] | undefined): CommonMethod;
    draggable(value: boolean | undefined): CommonMethod;
    dragPreview(value: (CustomBuilder|DragItemInfo|string) | undefined): CommonMethod;
    onPreDrag(value: ((value0: PreDragStatus) => void) | undefined): CommonMethod;
    linearGradient(value: LinearGradientOptions | undefined): CommonMethod;
    sweepGradient(value: SweepGradientOptions | undefined): CommonMethod;
    radialGradient(value: RadialGradientOptions | undefined): CommonMethod;
    motionPath(value: MotionPathOptions | undefined): CommonMethod;
    shadow(value: (ShadowOptions|ShadowStyle) | undefined): CommonMethod;
    clip(value: boolean | undefined): CommonMethod;
    clipShape(value: (CircleShape|EllipseShape|PathShape|RectShape) | undefined): CommonMethod;
    mask(value: ProgressMask | undefined): CommonMethod;
    maskShape(value: (CircleShape|EllipseShape|PathShape|RectShape) | undefined): CommonMethod;
    key(value: string | undefined): CommonMethod;
    id(value: string | undefined): CommonMethod;
    geometryTransition(value: string | undefined): CommonMethod;
    stateStyles(value: StateStyles | undefined): CommonMethod;
    restoreId(value: number | undefined): CommonMethod;
    sphericalEffect(value: number | undefined): CommonMethod;
    lightUpEffect(value: number | undefined): CommonMethod;
    pixelStretchEffect(value: PixelStretchEffectOptions | undefined): CommonMethod;
    accessibilityGroup(value: boolean | undefined): CommonMethod;
    accessibilityText(value: string | undefined): CommonMethod;
    accessibilityNextFocusId(value: string | undefined): CommonMethod;
    accessibilityDefaultFocus(value: boolean | undefined): CommonMethod;
    accessibilityUseSamePage(value: AccessibilitySamePageMode | undefined): CommonMethod;
    accessibilityScrollTriggerable(value: boolean | undefined): CommonMethod;
    accessibilityText(value: Resource | undefined): CommonMethod;
    accessibilityRole(value: AccessibilityRoleType | undefined): CommonMethod;
    onAccessibilityFocus(value: AccessibilityFocusCallback | undefined): CommonMethod;
    accessibilityTextHint(value: string | undefined): CommonMethod;
    accessibilityDescription(value: string | undefined): CommonMethod;
    accessibilityDescription(value: Resource | undefined): CommonMethod;
    accessibilityLevel(value: string | undefined): CommonMethod;
    accessibilityVirtualNode(value: CustomBuilder | undefined): CommonMethod;
    accessibilityChecked(value: boolean | undefined): CommonMethod;
    accessibilitySelected(value: boolean | undefined): CommonMethod;
    obscured(value: ObscuredReasons[] | undefined): CommonMethod;
    reuseId(value: string | undefined): CommonMethod;
    reuse(value: ReuseOptions | undefined): CommonMethod;
    renderFit(value: RenderFit | undefined): CommonMethod;
    gestureModifier(value: GestureModifier | undefined): CommonMethod;
    backgroundBrightness(value: BackgroundBrightnessOptions | undefined): CommonMethod;
    onGestureJudgeBegin(value: ((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult) | undefined): CommonMethod;
    onGestureRecognizerJudgeBegin(value: GestureRecognizerJudgeBeginCallback | undefined): CommonMethod;
    shouldBuiltInRecognizerParallelWith(value: ShouldBuiltInRecognizerParallelWithCallback | undefined): CommonMethod;
    monopolizeEvents(value: boolean | undefined): CommonMethod;
    onTouchIntercept(value: ((value0: TouchEvent) => HitTestMode) | undefined): CommonMethod;
    onSizeChange(value: SizeChangeCallback | undefined): CommonMethod;
    accessibilityFocusDrawLevel(value: FocusDrawLevel | undefined): CommonMethod;
    customProperty(name: string | undefined, value: Object | undefined): CommonMethod;
    expandSafeArea(types?: SafeAreaType[] | undefined, edges?: SafeAreaEdge[] | undefined): CommonMethod;
    background(builder: CustomBuilder | undefined, options?: BackgroundOptions | undefined): CommonMethod;
    backgroundImage(src: (ResourceStr|image.PixelMap) | undefined, repeat?: ImageRepeat | undefined): CommonMethod;
    backgroundImage(src: (ResourceStr|image.PixelMap) | undefined, options?: BackgroundImageOptions | undefined): CommonMethod;
    backgroundBlurStyle(style: BlurStyle | undefined, options?: BackgroundBlurStyleOptions | undefined, sysOptions?: SystemAdaptiveOptions | undefined): CommonMethod;
    backgroundEffect(options: BackgroundEffectOptions | undefined, sysOptions?: SystemAdaptiveOptions | undefined): CommonMethod;
    foregroundBlurStyle(style: BlurStyle | undefined, options?: ForegroundBlurStyleOptions | undefined, sysOptions?: SystemAdaptiveOptions | undefined): CommonMethod;
    onClick(event: ((event: ClickEvent) => void) | undefined, distanceThreshold: number | undefined): CommonMethod;
    focusScopeId(id: string | undefined, isGroup?: boolean | undefined, arrowStepOut?: boolean | undefined): CommonMethod;
    focusScopePriority(scopeId: string | undefined, priority?: FocusPriority | undefined): CommonMethod;
    transition(effect: TransitionEffect | undefined, onFinish: TransitionFinishCallback | undefined): CommonMethod;
    gesture(gesture: GestureType | undefined, mask?: GestureMask | undefined): CommonMethod;
    priorityGesture(gesture: GestureType | undefined, mask?: GestureMask | undefined): CommonMethod;
    parallelGesture(gesture: GestureType | undefined, mask?: GestureMask | undefined): CommonMethod;
    blur(blurRadius: number | undefined, options?: BlurOptions | undefined, sysOptions?: SystemAdaptiveOptions | undefined): CommonMethod;
    linearGradientBlur(value: number | undefined, options: LinearGradientBlurOptions | undefined): CommonMethod;
    systemBarEffect(): CommonMethod;
    useEffect(useEffect: boolean | undefined, effectType: EffectType | undefined): CommonMethod;
    backdropBlur(radius: number | undefined, options?: BlurOptions | undefined, sysOptions?: SystemAdaptiveOptions | undefined): CommonMethod;
    sharedTransition(id: string | undefined, options?: sharedTransitionOptions | undefined): CommonMethod;
    chainMode(direction: Axis | undefined, style: ChainStyle | undefined): CommonMethod;
    onDrop(eventCallback: OnDragEventCallback | undefined, dropOptions?: DropOptions | undefined): CommonMethod;
    dragPreview(preview: (CustomBuilder|DragItemInfo|string) | undefined, config?: PreviewConfiguration | undefined): CommonMethod;
    dragPreviewOptions(value: DragPreviewOptions | undefined, options?: DragInteractionOptions | undefined): CommonMethod;
    overlay(value: (string|CustomBuilder|ComponentContent) | undefined, options?: OverlayOptions | undefined): CommonMethod;
    blendMode(value: BlendMode | undefined, type?: BlendApplyType | undefined): CommonMethod;
    advancedBlendMode(effect: (BlendMode|uiEffect.Blender) | undefined, type?: BlendApplyType | undefined): CommonMethod;
    geometryTransition(id: string | undefined, options?: GeometryTransitionOptions | undefined): CommonMethod;
    bindTips(message: TipsMessageType | undefined, options?: TipsOptions | undefined): CommonMethod;
    bindPopup(show: boolean | undefined, popup: (PopupOptions|CustomPopupOptions) | undefined): CommonMethod;
    bindMenu(content: (MenuElement[]|CustomBuilder) | undefined, options?: MenuOptions | undefined): CommonMethod;
    bindMenu(isShow: boolean | undefined, content: (MenuElement[]|CustomBuilder) | undefined, options?: MenuOptions | undefined): CommonMethod;
    bindContextMenu(content: CustomBuilder | undefined, responseType: ResponseType | undefined, options?: ContextMenuOptions | undefined): CommonMethod;
    bindContextMenu(isShown: boolean | undefined, content: CustomBuilder | undefined, options?: ContextMenuOptions | undefined): CommonMethod;
    bindContentCover(isShow: boolean | undefined, builder: CustomBuilder | undefined, type?: ModalTransition | undefined): CommonMethod;
    bindContentCover(isShow: boolean | undefined, builder: CustomBuilder | undefined, options?: ContentCoverOptions | undefined): CommonMethod;
    bindSheet(isShow: boolean | undefined, builder: CustomBuilder | undefined, options?: SheetOptions | undefined): CommonMethod;
    onVisibleAreaChange(ratios: number[] | undefined, event: VisibleAreaChangeCallback | undefined): CommonMethod;
    onVisibleAreaApproximateChange(options: VisibleAreaEventOptions | undefined, event: VisibleAreaChangeCallback | undefined): CommonMethod;
    keyboardShortcut(value: (string|FunctionKey) | undefined, keys: ModifierKey[] | undefined, action?: (() => void) | undefined): CommonMethod;
    accessibilityGroup(isGroup: boolean | undefined, accessibilityOptions: AccessibilityOptions | undefined): CommonMethod;
    onGestureRecognizerJudgeBegin(callback_: GestureRecognizerJudgeBeginCallback | undefined, exposeInnerGesture: boolean | undefined): CommonMethod;
}
declare type CommonAttribute = CommonMethod;
declare interface OverlayOptions {
    align?: Alignment;
    offset?: OverlayOffset;
}
declare interface OverlayOffset {
    x?: number;
    y?: number;
}
declare type FractionStop = [ number, number ]
declare interface CommonShapeMethod extends CommonMethod {
    stroke(value: ResourceColor | undefined): CommonShapeMethod;
    fill(value: ResourceColor | undefined): CommonShapeMethod;
    strokeDashOffset(value: (number|string) | undefined): CommonShapeMethod;
    strokeLineCap(value: LineCapStyle | undefined): CommonShapeMethod;
    strokeLineJoin(value: LineJoinStyle | undefined): CommonShapeMethod;
    strokeMiterLimit(value: (number|string) | undefined): CommonShapeMethod;
    strokeOpacity(value: (number|string|Resource) | undefined): CommonShapeMethod;
    fillOpacity(value: (number|string|Resource) | undefined): CommonShapeMethod;
    strokeWidth(value: Length | undefined): CommonShapeMethod;
    antiAlias(value: boolean | undefined): CommonShapeMethod;
    strokeDashArray(value: Length[] | undefined): CommonShapeMethod;
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
declare interface GeometryInfo extends SizeResult {
    borderWidth: EdgeWidths;
    margin: Padding;
    padding: Padding;
}
declare interface Layoutable {
    measureResult: MeasureResult;
    uniqueId?: number;
    layout(position: Position): void;
    getMargin(): DirectionalEdgesT;
    getPadding(): DirectionalEdgesT;
    getBorderWidth(): DirectionalEdgesT;
}
declare interface Measurable {
    uniqueId?: number;
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
declare type NavDestinationInfo = observer.NavDestinationInfo;
declare type NavigationInfo = observer.NavigationInfo;
declare type RouterPageInfo = observer.RouterPageInfo;
declare type VisualEffect = uiEffect.VisualEffect;
declare type Filter = uiEffect.Filter;
declare type Blender = uiEffect.Blender;
declare type PromptActionDialogController = promptAction.DialogController;
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
declare interface TextContentControllerOptions {
    offset?: number;
}
declare class TextContentControllerBase {
    constructor();
    getCaretOffset(): CaretOffset;
    getTextContentRect(): RectResult;
    getTextContentLineCount(): number;
    addText(text: string, textOperationOptions?: TextContentControllerOptions): number;
    deleteText(range?: TextRange): void;
    getSelection(): TextRange;
    clearPreviewText(): void;
    getText(range?: TextRange): string;
}
declare enum ContentClipMode {
    CONTENT_ONLY,
    BOUNDARY = 1,
    SAFE_AREA = 2,
}
declare interface ScrollableCommonMethod extends CommonMethod {
    scrollBar(value: BarState | undefined): ScrollableCommonMethod;
    scrollBarColor(value: (Color|number|string) | undefined): ScrollableCommonMethod;
    scrollBarWidth(value: (number|string) | undefined): ScrollableCommonMethod;
    nestedScroll(value: NestedScrollOptions | undefined): ScrollableCommonMethod;
    enableScrollInteraction(value: boolean | undefined): ScrollableCommonMethod;
    friction(value: (number|Resource) | undefined): ScrollableCommonMethod;
    onReachStart(value: (() => void) | undefined): ScrollableCommonMethod;
    onReachEnd(value: (() => void) | undefined): ScrollableCommonMethod;
    onScrollStart(value: (() => void) | undefined): ScrollableCommonMethod;
    onScrollStop(value: (() => void) | undefined): ScrollableCommonMethod;
    flingSpeedLimit(value: number | undefined): ScrollableCommonMethod;
    clipContent(value: (ContentClipMode|RectShape) | undefined): ScrollableCommonMethod;
    digitalCrownSensitivity(value: CrownSensitivity | undefined): ScrollableCommonMethod;
    backToTop(value: boolean | undefined): ScrollableCommonMethod;
    edgeEffect(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions | undefined): ScrollableCommonMethod;
    fadingEdge(enabled: boolean | undefined, options?: FadingEdgeOptions | undefined): ScrollableCommonMethod;
}
declare class ScrollResult {
    constructor();
    offsetRemain: number;
}
declare type OnWillScrollCallback = ((scrollOffset: number, scrollState: ScrollState, scrollSource: ScrollSource) => ScrollResult | undefined);
declare type OnScrollCallback = ((scrollOffset: number, scrollState: ScrollState) => void);
declare type OnItemDragStartCallback = ((event: ItemDragInfo, itemIndex: number) => CustomBuilder | undefined);
declare type OnMoveHandler = ((from: number, to: number) => void);
declare interface ItemDragEventHandler {
    onLongPress?: ((value0: number) => void);
    onDragStart?: ((value0: number) => void);
    onMoveThrough?: OnMoveHandler;
    onDrop?: ((value0: number) => void);
}
declare interface DynamicNode {
    onMove(handler: OnMoveHandler | undefined): DynamicNode;
    onMove(handler: OnMoveHandler | undefined, eventHandler: ItemDragEventHandler): DynamicNode;
}
declare interface EdgeEffectOptions {
    alwaysEnabled: boolean;
    effectEdge?: number;
}
declare enum EffectEdge {
    START = 1,
    END = 2,
}
declare class ChildrenMainSize {
    constructor(childDefaultSize: number);
    set childDefaultSize(value: number);
    get childDefaultSize(): number;
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
    expectedFrameRateRange?: ExpectedFrameRateRange;
}
declare interface KeyframeState {
    duration: number;
    curve?: (Curve|string|ICurve);
    event: (() => void);
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
    addGesture(gesture: GestureHandler, priority?: GesturePriority, mask?: GestureMask): void;
    addParallelGesture(gesture: GestureHandler, mask?: GestureMask): void;
    removeGestureByTag(tag: string): void;
    clearGestures(): void;
}
declare interface GestureModifier {
    applyGesture(event: UIGestureEvent): void;
}
declare interface SelectionOptions {
    menuPolicy?: MenuPolicy;
}
declare interface FocusMovement {
    forward?: string;
    backward?: string;
    up?: string;
    down?: string;
    left?: string;
    right?: string;
}
declare enum KeyboardAvoidMode {
    DEFAULT,
    NONE = 1,
}
declare enum HoverModeAreaType {
    TOP_SCREEN,
    BOTTOM_SCREEN = 1,
}
declare interface DateRange {
    start?: Date;
    end?: Date;
}
declare type DateTimeOptions = intl.DateTimeOptions;
declare interface Bindable<T> {
    readonly value: T;
    readonly onChange: ((instance: T) => void);
}
declare interface ContainerSpanAttribute {
    textBackgroundStyle(value: TextBackgroundStyle | undefined): ContainerSpanAttribute;
    attributeModifier(value: AttributeModifier<ContainerSpanAttribute> | undefined): ContainerSpanAttribute;
}
declare interface ContainerSpanInterface {
    (): ContainerSpanAttribute;
}
declare interface ContentSlotAttribute {
}
declare interface ContentSlotInterface {
    (content: Content): ContentSlotAttribute;
}
declare interface CounterAttribute extends CommonMethod {
    onInc(value: VoidCallback | undefined): CounterAttribute;
    onDec(value: VoidCallback | undefined): CounterAttribute;
    enableDec(value: boolean | undefined): CounterAttribute;
    enableInc(value: boolean | undefined): CounterAttribute;
    attributeModifier(value: (AttributeModifier<CounterAttribute>|AttributeModifier<CommonMethod>) | undefined): CounterAttribute;
}
declare interface CounterInterface {
    (): CounterAttribute;
}
declare class BaseCustomComponent extends ExtendableComponent {
    constructor();
    aboutToRecycle(): void;
}
declare type Callback_T<T> = (() => T);
declare class CustomComponent<T,T_Options> extends BaseCustomComponent {
    constructor();
    static $_instantiate(factory: (() => T), initializers?: T_Options, reuseId?: string, content?: (() => void)): T;
    aboutToReuse(params: Map<string,Object>): void;
}
declare class CustomComponentV2<T,T_Options> extends BaseCustomComponent {
    constructor();
    static $_instantiate(factory: (() => T), initializers?: T_Options, reuseId?: string, content?: (() => void)): T;
    aboutToReuse(): void;
}
declare interface PageLifeCycle {
    onPageShow(): void;
    onPageHide(): void;
    onBackPress(): boolean;
    pageTransition(): void;
    onNewParam(param: Object | undefined): void;
}
declare interface LayoutCallback {
    onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Layoutable[], constraint: ConstraintSizeOptions): void;
    onMeasureSize(selfLayoutInfo: GeometryInfo, children: Measurable[], constraint: ConstraintSizeOptions): SizeResult;
}
declare interface CustomDialogControllerOptions {
    builder: CustomBuilder;
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
    onWillDismiss?: ((value0: DismissDialogAction) => void);
    width?: Dimension;
    height?: Dimension;
    borderWidth?: (Dimension|EdgeWidths);
    borderColor?: (ResourceColor|EdgeColors);
    borderStyle?: (BorderStyle|EdgeStyles);
    shadow?: (ShadowOptions|ShadowStyle);
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    keyboardAvoidMode?: KeyboardAvoidMode;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    onDidAppear?: (() => void);
    onDidDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
    keyboardAvoidDistance?: LengthMetrics;
    levelMode?: LevelMode;
    levelUniqueId?: number;
    immersiveMode?: ImmersiveMode;
    levelOrder?: LevelOrder;
    focusable?: boolean;
}
declare class CustomDialogController {
    constructor(value: CustomDialogControllerOptions);
    open(): void;
    close(): void;
}
declare enum DataPanelType {
    LINE,
    Line,
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
declare interface DataPanelConfiguration extends CommonConfiguration<DataPanelConfiguration> {
    values: number[];
    maxValue: number;
}
declare interface DataPanelAttribute extends CommonMethod {
    closeEffect(value: boolean | undefined): DataPanelAttribute;
    valueColors(value: (ResourceColor|LinearGradient)[] | undefined): DataPanelAttribute;
    trackBackgroundColor(value: ResourceColor | undefined): DataPanelAttribute;
    strokeWidth(value: Length | undefined): DataPanelAttribute;
    trackShadow(value: DataPanelShadowOptions | undefined): DataPanelAttribute;
    contentModifier(value: ContentModifier<DataPanelConfiguration> | undefined): DataPanelAttribute;
    attributeModifier(value: (AttributeModifier<DataPanelAttribute>|AttributeModifier<CommonMethod>) | undefined): DataPanelAttribute;
}
declare interface DataPanelInterface {
    (options: DataPanelOptions): DataPanelAttribute;
}
declare interface DatePickerResult {
    year?: number;
    month?: number;
    day?: number;
}
declare enum DatePickerMode {
    DATE,
    YEAR_AND_MONTH = 1,
    MONTH_AND_DAY = 2,
}
declare interface DatePickerOptions {
    start?: Date;
    end?: Date;
    selected?: Date;
    mode?: DatePickerMode;
}
declare interface DatePickerAttribute extends CommonMethod {
    lunar(value: boolean | undefined): DatePickerAttribute;
    disappearTextStyle(value: PickerTextStyle | undefined): DatePickerAttribute;
    textStyle(value: PickerTextStyle | undefined): DatePickerAttribute;
    selectedTextStyle(value: PickerTextStyle | undefined): DatePickerAttribute;
    onDateChange(value: ((value0: Date) => void) | undefined): DatePickerAttribute;
    digitalCrownSensitivity(value: CrownSensitivity | undefined): DatePickerAttribute;
    enableHapticFeedback(value: boolean | undefined): DatePickerAttribute;
    attributeModifier(value: (AttributeModifier<DatePickerAttribute>|AttributeModifier<CommonMethod>) | undefined): DatePickerAttribute;
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
    onCancel?: VoidCallback;
    onDateAccept?: ((value0: Date) => void);
    onDateChange?: ((value0: Date) => void);
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    onDidAppear?: VoidCallback;
    onDidDisappear?: VoidCallback;
    onWillAppear?: VoidCallback;
    onWillDisappear?: VoidCallback;
    shadow?: (ShadowOptions|ShadowStyle);
    dateTimeOptions?: intl.DateTimeOptions;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    enableHapticFeedback?: boolean;
}
declare class DatePickerDialog {
    constructor();
}
declare interface DatePickerInterface {
    (options?: DatePickerOptions): DatePickerAttribute;
}
declare interface DividerAttribute extends CommonMethod {
    vertical(value: boolean | undefined): DividerAttribute;
    color(value: ResourceColor | undefined): DividerAttribute;
    strokeWidth(value: (number|string) | undefined): DividerAttribute;
    lineCap(value: LineCapStyle | undefined): DividerAttribute;
    attributeModifier(value: (AttributeModifier<DividerAttribute>|AttributeModifier<CommonMethod>) | undefined): DividerAttribute;
}
declare interface DividerInterface {
    (): DividerAttribute;
}
declare interface EffectComponentAttribute extends CommonMethod {
    attributeModifier(value: (AttributeModifier<EffectComponentAttribute>|AttributeModifier<CommonMethod>) | undefined): EffectComponentAttribute;
}
declare interface EffectComponentInterface {
    (): EffectComponentAttribute;
}
declare interface EllipseOptions {
    width?: (string|number);
    height?: (string|number);
}
declare interface EllipseAttribute extends CommonShapeMethod {
    attributeModifier(value: (AttributeModifier<EllipseAttribute>|AttributeModifier<CommonMethod>) | undefined): EllipseAttribute;
}
declare interface EllipseInterface {
    (options?: EllipseOptions): EllipseAttribute;
}
declare interface TerminationInfo {
    code: number;
    want?: Want;
}
declare type Callback_TerminationInfo_Void = ((value0: TerminationInfo) => void);
declare interface EmbeddedComponentAttribute extends CommonMethod {
    onTerminated(value: ((value0: TerminationInfo) => void) | undefined): EmbeddedComponentAttribute;
    onError(value: ErrorCallback | undefined): EmbeddedComponentAttribute;
    attributeModifier(value: (AttributeModifier<EmbeddedComponentAttribute>|AttributeModifier<CommonMethod>) | undefined): EmbeddedComponentAttribute;
}
declare interface EmbeddedComponentInterface {
    (loader: Want, type: EmbeddedType): EmbeddedComponentAttribute;
}
declare enum CheckBoxShape {
    CIRCLE,
    ROUNDED_SQUARE = 1,
}
declare enum Color {
    WHITE,
    White,
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
    INVERT = "'invert'",
    AVERAGE = "'average'",
    PRIMARY = "'primary'",
}
declare enum ImageFit {
    CONTAIN,
    Contain,
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
    MATRIX = 16,
}
declare enum BorderStyle {
    DOTTED,
    Dotted,
    DASHED = 1,
    Dashed = 1,
    SOLID = 2,
    Solid = 2,
}
declare enum LineJoinStyle {
    MITER,
    Miter,
    ROUND = 1,
    Round = 1,
    BEVEL = 2,
    Bevel = 2,
}
declare enum TouchType {
    DOWN,
    Down,
    UP = 1,
    Up = 1,
    MOVE = 2,
    Move = 2,
    CANCEL = 3,
    Cancel = 3,
}
declare enum InteractionHand {
    NONE,
    LEFT = 1,
    RIGHT = 2,
}
declare enum MouseButton {
    LEFT,
    Left,
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
    PRESS,
    Press,
    RELEASE = 1,
    Release = 1,
    MOVE = 2,
    Move = 2,
    HOVER = 3,
    Hover = 3,
    CANCEL = 13,
}
declare enum AnimationStatus {
    INITIAL,
    Initial,
    RUNNING = 1,
    Running = 1,
    PAUSED = 2,
    Paused = 2,
    STOPPED = 3,
    Stopped = 3,
}
declare enum Curve {
    LINEAR,
    Linear,
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
    NONE,
    None,
    FORWARDS = 1,
    Forwards = 1,
    BACKWARDS = 2,
    Backwards = 2,
    BOTH = 3,
    Both = 3,
}
declare enum PlayMode {
    NORMAL,
    Normal,
    REVERSE = 1,
    Reverse = 1,
    ALTERNATE = 2,
    Alternate = 2,
    ALTERNATE_REVERSE = 3,
    AlternateReverse = 3,
}
declare enum KeyType {
    DOWN,
    Down,
    UP = 1,
    Up = 1,
}
declare enum KeySource {
    UNKNOWN,
    Unknown,
    KEYBOARD = 1,
    Keyboard = 1,
    JOYSTICK = 2,
}
declare enum Edge {
    TOP,
    Top,
    BOTTOM = 1,
    Bottom = 1,
    START = 2,
    Start = 2,
    END = 3,
    End = 3,
}
declare enum Week {
    MON,
    Mon,
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
    LTR,
    Ltr,
    RTL = 1,
    Rtl = 1,
    AUTO = 2,
    Auto = 2,
}
declare enum BarState {
    OFF,
    Off,
    AUTO = 1,
    Auto = 1,
    ON = 2,
    On = 2,
}
declare enum EdgeEffect {
    SPRING,
    Spring,
    FADE = 1,
    Fade = 1,
    NONE = 2,
    None = 2,
}
declare enum Alignment {
    TOP_START,
    TopStart,
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
    ALL,
    All,
    INSERT = 1,
    Insert = 1,
    DELETE = 2,
    Delete = 2,
}
declare enum RelateType {
    FILL,
    FIT = 1,
}
declare enum Visibility {
    VISIBLE,
    Visible,
    HIDDEN = 1,
    Hidden = 1,
    NONE = 2,
    None = 2,
}
declare enum LineCapStyle {
    BUTT,
    Butt,
    ROUND = 1,
    Round = 1,
    SQUARE = 2,
    Square = 2,
}
declare enum Axis {
    VERTICAL,
    Vertical,
    HORIZONTAL = 1,
    Horizontal = 1,
}
declare enum HorizontalAlign {
    START,
    Start,
    CENTER = 1,
    Center = 1,
    END = 2,
    End = 2,
}
declare enum FlexAlign {
    START,
    Start,
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
    AUTO,
    Auto,
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
    ROW,
    Row,
    COLUMN = 1,
    Column = 1,
    ROW_REVERSE = 2,
    RowReverse = 2,
    COLUMN_REVERSE = 3,
    ColumnReverse = 3,
}
declare enum PixelRoundCalcPolicy {
    NO_FORCE_ROUND,
    FORCE_CEIL = 1,
    FORCE_FLOOR = 2,
}
declare enum PixelRoundMode {
    PIXEL_ROUND_ON_LAYOUT_FINISH,
    PIXEL_ROUND_AFTER_MEASURE = 1,
}
declare enum FlexWrap {
    NO_WRAP,
    NoWrap,
    WRAP = 1,
    Wrap = 1,
    WRAP_REVERSE = 2,
    WrapReverse = 2,
}
declare enum VerticalAlign {
    TOP,
    Top,
    CENTER = 1,
    Center = 1,
    BOTTOM = 2,
    Bottom = 2,
}
declare enum ImageRepeat {
    NO_REPEAT,
    NoRepeat,
    X = 1,
    Y = 2,
    XY = 3,
}
declare enum ImageSize {
    AUTO,
    Auto,
    COVER = 1,
    Cover = 1,
    CONTAIN = 2,
    Contain = 2,
    FILL = 3,
}
declare enum GradientDirection {
    LEFT,
    Left,
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
    STATIC,
    Static,
    EXCHANGE = 1,
    Exchange = 1,
}
declare enum FontStyle {
    NORMAL,
    Normal,
    ITALIC = 1,
    Italic = 1,
}
declare enum FontWeight {
    LIGHTER,
    Lighter,
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
    CENTER,
    Center,
    START = 1,
    Start = 1,
    END = 2,
    End = 2,
    JUSTIFY = 3,
}
declare enum TextOverflow {
    NONE,
    None,
    CLIP = 1,
    Clip = 1,
    ELLIPSIS = 2,
    Ellipsis = 2,
    MARQUEE = 3,
}
declare enum TextDecorationType {
    NONE,
    None,
    UNDERLINE = 1,
    Underline = 1,
    OVERLINE = 2,
    Overline = 2,
    LINE_THROUGH = 3,
    LineThrough = 3,
}
declare enum TextCase {
    NORMAL,
    Normal,
    LOWER_CASE = 1,
    LowerCase = 1,
    UPPER_CASE = 2,
    UpperCase = 2,
}
declare enum TextHeightAdaptivePolicy {
    MAX_LINES_FIRST,
    MIN_FONT_SIZE_FIRST = 1,
    LAYOUT_CONSTRAINT_FIRST = 2,
}
declare enum ResponseType {
    RIGHT_CLICK,
    RightClick,
    LONG_PRESS = 1,
    LongPress = 1,
}
declare enum HoverEffect {
    AUTO,
    Auto,
    SCALE = 1,
    Scale = 1,
    HIGHLIGHT = 2,
    Highlight = 2,
    NONE = 3,
    None = 3,
}
declare enum Placement {
    LEFT,
    Left,
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
    START = "'Start'",
    CENTER = "'Center'",
    END = "'End'",
}
declare enum CopyOptions {
    NONE,
    None,
    IN_APP = 1,
    InApp = 1,
    LOCAL_DEVICE = 2,
    LocalDevice = 2,
}
declare enum HitTestMode {
    DEFAULT,
    Default,
    BLOCK = 1,
    Block = 1,
    TRANSPARENT = 2,
    Transparent = 2,
    NONE = 3,
    None = 3,
}
declare enum TitleHeight {
    MAIN_ONLY,
    MainOnly,
    MAIN_WITH_SUB = 1,
    MainWithSub = 1,
}
declare enum ModifierKey {
    CTRL,
    SHIFT = 1,
    ALT = 2,
}
declare enum FunctionKey {
    ESC,
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
    BASELINE,
    BOTTOM = 1,
    CENTER = 2,
    TOP = 3,
}
declare enum ObscuredReasons {
    PLACEHOLDER,
}
declare enum TextContentStyle {
    DEFAULT,
    INLINE = 1,
}
declare enum ClickEffectLevel {
    LIGHT,
    MIDDLE = 1,
    HEAVY = 2,
}
declare enum XComponentType {
    SURFACE,
    TEXTURE = 1,
    NODE = 2,
}
declare enum NestedScrollMode {
    SELF_ONLY,
    SELF_FIRST = 1,
    PARENT_FIRST = 2,
    PARALLEL = 3,
}
declare enum ScrollSource {
    DRAG,
    FLING = 1,
    EDGE_EFFECT = 2,
    OTHER_USER_INPUT = 3,
    SCROLL_BAR = 4,
    SCROLL_BAR_FLING = 5,
    SCROLLER = 6,
    SCROLLER_ANIMATION = 7,
}
declare enum RenderFit {
    CENTER,
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
    DEFAULT,
    HIGHLIGHT = 1,
}
declare enum WordBreak {
    NORMAL,
    BREAK_ALL = 1,
    BREAK_WORD = 2,
    HYPHENATION = 3,
}
declare enum LineBreakStrategy {
    GREEDY,
    HIGH_QUALITY = 1,
    BALANCED = 2,
}
declare enum IlluminatedType {
    NONE,
    BORDER = 1,
    CONTENT = 2,
    BORDER_CONTENT = 3,
    BLOOM_BORDER = 4,
    BLOOM_BORDER_CONTENT = 5,
}
declare enum EllipsisMode {
    START,
    CENTER = 1,
    END = 2,
}
declare type Nullable<T> = T | undefined;
declare enum OptionWidthMode {
    FIT_CONTENT = "'fit_content'",
    FIT_TRIGGER = "'fit_trigger'",
}
declare enum FoldStatus {
    FOLD_STATUS_UNKNOWN,
    FOLD_STATUS_EXPANDED = 1,
    FOLD_STATUS_FOLDED = 2,
    FOLD_STATUS_HALF_FOLDED = 3,
}
declare enum AppRotation {
    ROTATION_0,
    ROTATION_90 = 1,
    ROTATION_180 = 2,
    ROTATION_270 = 3,
}
declare enum EmbeddedType {
    EMBEDDED_UI_EXTENSION,
}
declare enum MarqueeUpdateStrategy {
    DEFAULT,
    PRESERVE_POSITION = 1,
}
declare enum TextDecorationStyle {
    SOLID,
    DOUBLE = 1,
    DOTTED = 2,
    DASHED = 3,
    WAVY = 4,
}
declare enum TextSelectableMode {
    SELECTABLE_UNFOCUSABLE,
    SELECTABLE_FOCUSABLE = 1,
    UNSELECTABLE = 2,
}
declare enum AccessibilityHoverType {
    HOVER_ENTER,
    HOVER_MOVE = 1,
    HOVER_EXIT = 2,
    HOVER_CANCEL = 3,
}
declare enum WidthBreakpoint {
    WIDTH_XS,
    WIDTH_SM = 1,
    WIDTH_MD = 2,
    WIDTH_LG = 3,
    WIDTH_XL = 4,
}
declare enum HeightBreakpoint {
    HEIGHT_SM,
    HEIGHT_MD = 1,
    HEIGHT_LG = 2,
}
declare enum AxisModel {
    ABS_X,
    ABS_Y = 1,
    ABS_Z = 2,
    ABS_RZ = 3,
    ABS_GAS = 4,
    ABS_BRAKE = 5,
    ABS_HAT0X = 6,
    ABS_HAT0Y = 7,
}
declare enum PageFlipMode {
    CONTINUOUS,
    SINGLE = 1,
}
declare enum CrownAction {
    BEGIN,
    UPDATE = 1,
    END = 2,
}
declare enum CrownSensitivity {
    LOW,
    MEDIUM = 1,
    HIGH = 2,
}
declare enum AxisAction {
    NONE,
    BEGIN = 1,
    UPDATE = 2,
    END = 3,
    CANCEL = 4,
}
declare enum FocusDrawLevel {
    SELF,
    TOP = 1,
}
declare enum DividerMode {
    FLOATING_ABOVE_MENU,
    EMBEDDED_IN_MENU = 1,
}
declare interface LifeCycle {
    aboutToAppear(): void;
    aboutToDisappear(): void;
    onDidBuild(): void;
    build(): void;
}
declare class ExtendableComponent {
    constructor();
    getUIContext(): UIContext;
    getUniqueId(): number;
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
declare interface FlexAttribute extends CommonMethod {
    pointLight(value: PointLightStyle | undefined): FlexAttribute;
    attributeModifier(value: (AttributeModifier<FlexAttribute>|AttributeModifier<CommonMethod>) | undefined): FlexAttribute;
}
declare interface FlexInterface {
    (value?: FlexOptions): FlexAttribute;
}
declare interface FlowItemAttribute extends CommonMethod {
    attributeModifier(value: (AttributeModifier<FlowItemAttribute>|AttributeModifier<CommonMethod>) | undefined): FlowItemAttribute;
}
declare interface FlowItemInterface {
    (): FlowItemAttribute;
}
declare interface FocusBoxStyle {
    margin?: LengthMetrics;
    strokeColor?: ColorMetrics;
    strokeWidth?: LengthMetrics;
}
declare enum FocusPriority {
    AUTO,
    PRIOR = 2000,
    PREVIOUS = 3000,
}
declare enum KeyProcessingMode {
    FOCUS_NAVIGATION,
    ANCESTOR_EVENT = 1,
}
declare type WindowStatusType = window.WindowStatusType;
declare interface FolderStackOptions {
    upperItems?: string[];
}
declare interface OnFoldStatusChangeInfo {
    foldStatus: FoldStatus;
}
declare type OnFoldStatusChangeCallback = ((event: OnFoldStatusChangeInfo) => void);
declare type OnHoverStatusChangeCallback = ((param: HoverEventParam) => void);
declare interface FolderStackAttribute extends CommonMethod {
    alignContent(value: Alignment | undefined): FolderStackAttribute;
    onFolderStateChange(value: OnFoldStatusChangeCallback | undefined): FolderStackAttribute;
    onHoverStatusChange(value: OnHoverStatusChangeCallback | undefined): FolderStackAttribute;
    enableAnimation(value: boolean | undefined): FolderStackAttribute;
    autoHalfFold(value: boolean | undefined): FolderStackAttribute;
    attributeModifier(value: (AttributeModifier<FolderStackAttribute>|AttributeModifier<CommonMethod>) | undefined): FolderStackAttribute;
}
declare interface HoverEventParam {
    foldStatus: FoldStatus;
    isHoverMode: boolean;
    appRotation: AppRotation;
    windowStatusType: window.WindowStatusType;
}
declare interface FolderStackInterface {
    (options?: FolderStackOptions): FolderStackAttribute;
}
declare enum FormDimension {
    DIMENSION_1_2,
    Dimension_1_2,
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
    DIMENSION_2_3 = 8,
    DIMENSION_3_3 = 9,
    DIMENSION_3_4 = 10,
}
declare enum FormRenderingMode {
    FULL_COLOR,
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
declare interface FormCallbackInfo {
    id: number;
    idString: string;
}
declare interface FormSize {
    width: number;
    height: number;
}
declare interface FormError {
    errcode: number;
    msg: string;
}
declare type Callback_FormCallbackInfo_Void = ((value0: FormCallbackInfo) => void);
declare type Callback_FormError_Void = ((value0: FormError) => void);
declare type Callback_Union_Object_Undefined_Void = ((value0: Object | undefined) => void);
declare interface FormComponentAttribute extends CommonMethod {
    size(value: FormSize | undefined): FormComponentAttribute;
    moduleName(value: string | undefined): FormComponentAttribute;
    dimension(value: FormDimension | undefined): FormComponentAttribute;
    allowUpdate(value: boolean | undefined): FormComponentAttribute;
    visibility(value: Visibility | undefined): FormComponentAttribute;
    onAcquired(value: ((value0: FormCallbackInfo) => void) | undefined): FormComponentAttribute;
    onError(value: ((value0: FormError) => void) | undefined): FormComponentAttribute;
    onRouter(value: ((value0: Object | undefined) => void) | undefined): FormComponentAttribute;
    onUninstall(value: ((value0: FormCallbackInfo) => void) | undefined): FormComponentAttribute;
    onLoad(value: (() => void) | undefined): FormComponentAttribute;
    attributeModifier(value: (AttributeModifier<FormComponentAttribute>|AttributeModifier<CommonMethod>) | undefined): FormComponentAttribute;
}
declare interface FormComponentInterface {
    (value: FormInfo): FormComponentAttribute;
}
declare interface FormLinkOptions {
    action: string;
    moduleName?: string;
    bundleName?: string;
    abilityName?: string;
    uri?: string;
    params?: Object;
}
declare interface FormLinkAttribute extends CommonMethod {
    attributeModifier(value: (AttributeModifier<FormLinkAttribute>|AttributeModifier<CommonMethod>) | undefined): FormLinkAttribute;
}
declare interface FormLinkInterface {
    (options: FormLinkOptions): FormLinkAttribute;
}
declare interface GaugeOptions {
    value: number;
    min?: number;
    max?: number;
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
declare interface GaugeAttribute extends CommonMethod {
    value(value: number | undefined): GaugeAttribute;
    startAngle(value: number | undefined): GaugeAttribute;
    endAngle(value: number | undefined): GaugeAttribute;
    colors(value: (ResourceColor|LinearGradient|[ (ResourceColor|LinearGradient), number ][]) | undefined): GaugeAttribute;
    strokeWidth(value: Length | undefined): GaugeAttribute;
    description(value: CustomBuilder | undefined): GaugeAttribute;
    trackShadow(value: GaugeShadowOptions | undefined): GaugeAttribute;
    indicator(value: GaugeIndicatorOptions | undefined): GaugeAttribute;
    privacySensitive(value: boolean | undefined): GaugeAttribute;
    contentModifier(value: ContentModifier<GaugeConfiguration> | undefined): GaugeAttribute;
    attributeModifier(value: (AttributeModifier<GaugeAttribute>|AttributeModifier<CommonMethod>) | undefined): GaugeAttribute;
}
declare interface GaugeInterface {
    (options: GaugeOptions): GaugeAttribute;
}
declare enum PanDirection {
    NONE,
    None,
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
    NONE,
    None,
    HORIZONTAL = 1,
    Horizontal = 1,
    VERTICAL = 2,
    Vertical = 2,
    ALL = 3,
    All = 3,
}
declare enum GestureMode {
    SEQUENCE,
    Sequence,
    PARALLEL = 1,
    Parallel = 1,
    EXCLUSIVE = 2,
    Exclusive = 2,
}
declare enum GestureMask {
    NORMAL,
    Normal,
    IGNORE_INTERNAL = 1,
    IgnoreInternal = 1,
}
declare enum GestureJudgeResult {
    CONTINUE,
    REJECT = 1,
}
declare namespace GestureControl {
    enum GestureType {
        TAP_GESTURE,
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
    hand?: InteractionHand;
}
declare type GestureType = (Gesture|GestureGroup);
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
declare interface BaseHandlerOptions {
    isFingerCountLimited?: boolean;
}
declare class Gesture {
    constructor();
    tag(tag: string): Gesture;
    allowedTypes(types: SourceTool[]): Gesture;
}
declare interface TapGestureParameters extends BaseHandlerOptions {
    count?: number;
    fingers?: number;
    distanceThreshold?: number;
}
declare class PanGestureOptions {
    constructor(value?: PanGestureHandlerOptions);
    setDirection(value: PanDirection): void;
    setDistance(value: number): void;
    setFingers(value: number): void;
    getDirection(): PanDirection;
    getDistance(): number;
}
declare type Callback_SwipeGesture = (() => SwipeGesture);
declare class SwipeGesture extends Gesture {
    constructor();
    static $_instantiate(factory: (() => SwipeGesture), value?: SwipeGestureHandlerOptions): SwipeGesture;
    onAction(event: ((value0: GestureEvent) => void)): SwipeGesture;
}
declare type Callback_RotationGesture = (() => RotationGesture);
declare class RotationGesture extends Gesture {
    constructor();
    static $_instantiate(factory: (() => RotationGesture), value?: RotationGestureHandlerOptions): RotationGesture;
    onActionStart(event: ((value0: GestureEvent) => void)): RotationGesture;
    onActionUpdate(event: ((value0: GestureEvent) => void)): RotationGesture;
    onActionEnd(event: ((value0: GestureEvent) => void)): RotationGesture;
    onActionCancel(event: ((value0: GestureEvent) => void)): RotationGesture;
}
declare class GestureHandler {
    constructor();
    tag(tag: string): GestureHandler;
    allowedTypes(types: SourceTool[]): GestureHandler;
}
declare interface TapGestureHandlerOptions extends BaseHandlerOptions {
    count?: number;
    fingers?: number;
}
declare class TapGestureHandler extends GestureHandler {
    constructor(options?: TapGestureHandlerOptions);
    onAction(event: ((value0: GestureEvent) => void)): TapGestureHandler;
}
declare interface LongPressGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: number;
    repeat?: boolean;
    duration?: number;
}
declare class LongPressGestureHandler extends GestureHandler {
    constructor(options?: LongPressGestureHandlerOptions);
    onAction(event: ((value0: GestureEvent) => void)): LongPressGestureHandler;
    onActionEnd(event: ((value0: GestureEvent) => void)): LongPressGestureHandler;
    onActionCancel(event: ((value0: GestureEvent) => void)): LongPressGestureHandler;
}
declare interface PanGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: number;
    direction?: PanDirection;
    distance?: number;
}
declare class PanGestureHandler extends GestureHandler {
    constructor(options?: PanGestureHandlerOptions);
    onActionStart(event: ((value0: GestureEvent) => void)): PanGestureHandler;
    onActionUpdate(event: ((value0: GestureEvent) => void)): PanGestureHandler;
    onActionEnd(event: ((value0: GestureEvent) => void)): PanGestureHandler;
    onActionCancel(event: ((value0: GestureEvent) => void)): PanGestureHandler;
}
declare interface SwipeGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: number;
    direction?: SwipeDirection;
    speed?: number;
}
declare class SwipeGestureHandler extends GestureHandler {
    constructor(options?: SwipeGestureHandlerOptions);
    onAction(event: ((value0: GestureEvent) => void)): SwipeGestureHandler;
}
declare interface PinchGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: number;
    distance?: number;
}
declare class PinchGestureHandler extends GestureHandler {
    constructor(options?: PinchGestureHandlerOptions);
    onActionStart(event: ((value0: GestureEvent) => void)): PinchGestureHandler;
    onActionUpdate(event: ((value0: GestureEvent) => void)): PinchGestureHandler;
    onActionEnd(event: ((value0: GestureEvent) => void)): PinchGestureHandler;
    onActionCancel(event: ((value0: GestureEvent) => void)): PinchGestureHandler;
}
declare interface RotationGestureHandlerOptions extends BaseHandlerOptions {
    fingers?: number;
    angle?: number;
}
declare class RotationGestureHandler extends GestureHandler {
    constructor(options?: RotationGestureHandlerOptions);
    onActionStart(event: ((value0: GestureEvent) => void)): RotationGestureHandler;
    onActionUpdate(event: ((value0: GestureEvent) => void)): RotationGestureHandler;
    onActionEnd(event: ((value0: GestureEvent) => void)): RotationGestureHandler;
    onActionCancel(event: ((value0: GestureEvent) => void)): RotationGestureHandler;
}
declare interface GestureGroupGestureHandlerOptions {
    _stub: number;
}
declare class GestureGroupHandler extends GestureHandler {
    constructor(options?: GestureGroupGestureHandlerOptions);
    onCancel(event: (() => void)): GestureGroupHandler;
}
declare enum GesturePriority {
    NORMAL,
    PRIORITY = 1,
}
declare enum GestureRecognizerState {
    READY,
    DETECTING = 1,
    PENDING = 2,
    BLOCKED = 3,
    SUCCESSFUL = 4,
    FAILED = 5,
}
declare class ScrollableTargetInfo extends EventTargetInfo {
    constructor();
    isBegin(): boolean;
    isEnd(): boolean;
}
declare class EventTargetInfo {
    constructor();
    getId(): string;
}
declare class GestureRecognizer {
    constructor();
    getTag(): string;
    getType(): GestureControl.GestureType;
    isBuiltIn(): boolean;
    setEnabled(isEnabled: boolean): void;
    isEnabled(): boolean;
    getState(): GestureRecognizerState;
    getEventTargetInfo(): EventTargetInfo;
    isValid(): boolean;
    getFingerCount(): number;
    isFingerCountLimit(): boolean;
}
declare class TapRecognizer extends GestureRecognizer {
    constructor();
    getTapCount(): number;
}
declare class LongPressRecognizer extends GestureRecognizer {
    constructor();
    isRepeat(): boolean;
    getDuration(): number;
}
declare class SwipeRecognizer extends GestureRecognizer {
    constructor();
    getVelocityThreshold(): number;
    getDirection(): SwipeDirection;
}
declare class PinchRecognizer extends GestureRecognizer {
    constructor();
    getDistance(): number;
}
declare class RotationRecognizer extends GestureRecognizer {
    constructor();
    getAngle(): number;
}
declare class PanRecognizer extends GestureRecognizer {
    constructor();
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
declare enum GridDirection {
    ROW,
    Row,
    COLUMN = 1,
    Column = 1,
    ROW_REVERSE = 2,
    RowReverse = 2,
    COLUMN_REVERSE = 3,
    ColumnReverse = 3,
}
declare enum GridItemAlignment {
    DEFAULT,
    STRETCH = 1,
}
declare interface ComputedBarAttribute {
    totalOffset: number;
    totalLength: number;
}
declare type Callback_Number_Number_ComputedBarAttribute = ((index: number, offset: number) => ComputedBarAttribute);
declare type Callback_Number_Number_Void = ((first: number, last: number) => void);
declare type Callback_ItemDragInfo_Void = ((event: ItemDragInfo) => void);
declare type Callback_ItemDragInfo_Number_Number_Void = ((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void);
declare type Callback_ItemDragInfo_Number_Void = ((event: ItemDragInfo, itemIndex: number) => void);
declare type Callback_ItemDragInfo_Number_Number_Boolean_Void = ((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void);
declare interface GridAttribute extends ScrollableCommonMethod {
    columnsTemplate(value: string | undefined): GridAttribute;
    rowsTemplate(value: string | undefined): GridAttribute;
    columnsGap(value: Length | undefined): GridAttribute;
    rowsGap(value: Length | undefined): GridAttribute;
    onScrollBarUpdate(value: ((index: number, offset: number) => ComputedBarAttribute) | undefined): GridAttribute;
    onScrollIndex(value: ((first: number, last: number) => void) | undefined): GridAttribute;
    cachedCount(value: number | undefined): GridAttribute;
    editMode(value: boolean | undefined): GridAttribute;
    multiSelectable(value: boolean | undefined): GridAttribute;
    maxCount(value: number | undefined): GridAttribute;
    minCount(value: number | undefined): GridAttribute;
    cellLength(value: number | undefined): GridAttribute;
    layoutDirection(value: GridDirection | undefined): GridAttribute;
    supportAnimation(value: boolean | undefined): GridAttribute;
    onItemDragStart(value: OnItemDragStartCallback | undefined): GridAttribute;
    onItemDragEnter(value: ((event: ItemDragInfo) => void) | undefined): GridAttribute;
    onItemDragMove(value: ((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void) | undefined): GridAttribute;
    onItemDragLeave(value: ((event: ItemDragInfo, itemIndex: number) => void) | undefined): GridAttribute;
    onItemDrop(value: ((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void) | undefined): GridAttribute;
    alignItems(value: GridItemAlignment | undefined): GridAttribute;
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): GridAttribute;
    onWillScroll(value: OnWillScrollCallback | undefined): GridAttribute;
    onDidScroll(value: OnScrollCallback | undefined): GridAttribute;
    attributeModifier(value: (AttributeModifier<GridAttribute>|AttributeModifier<CommonMethod>) | undefined): GridAttribute;
    cachedCount(count: number | undefined, show: boolean | undefined): GridAttribute;
}
declare interface GridInterface {
    (scroller?: Scroller, layoutOptions?: GridLayoutOptions): GridAttribute;
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
declare interface GridColAttribute extends CommonMethod {
    span(value: (number|GridColColumnOption) | undefined): GridColAttribute;
    gridColOffset(value: (number|GridColColumnOption) | undefined): GridColAttribute;
    order(value: (number|GridColColumnOption) | undefined): GridColAttribute;
    attributeModifier(value: (AttributeModifier<GridColAttribute>|AttributeModifier<CommonMethod>) | undefined): GridColAttribute;
}
declare interface GridColInterface {
    (option?: GridColOptions): GridColAttribute;
}
declare enum GridItemStyle {
    NONE,
    PLAIN = 1,
}
declare interface GridItemOptions {
    style?: GridItemStyle;
}
declare interface GridItemAttribute extends CommonMethod {
    rowStart(value: number | undefined): GridItemAttribute;
    rowEnd(value: number | undefined): GridItemAttribute;
    columnStart(value: number | undefined): GridItemAttribute;
    columnEnd(value: number | undefined): GridItemAttribute;
    selectable(value: boolean | undefined): GridItemAttribute;
    selected(value: boolean | undefined): GridItemAttribute;
    onSelect(value: ((isSelected: boolean) => void) | undefined): GridItemAttribute;
    attributeModifier(value: (AttributeModifier<GridItemAttribute>|AttributeModifier<CommonMethod>) | undefined): GridItemAttribute;
}
declare interface GridItemInterface {
    (value?: GridItemOptions): GridItemAttribute;
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
    WINDOW_SIZE,
    WindowSize,
    COMPONENT_SIZE = 1,
    ComponentSize = 1,
}
declare enum GridRowDirection {
    ROW,
    Row,
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
declare type Callback_String_Void = ((breakpoints: string) => void);
declare interface GridRowAttribute extends CommonMethod {
    onBreakpointChange(value: ((breakpoints: string) => void) | undefined): GridRowAttribute;
    alignItems(value: ItemAlign | undefined): GridRowAttribute;
    attributeModifier(value: (AttributeModifier<GridRowAttribute>|AttributeModifier<CommonMethod>) | undefined): GridRowAttribute;
}
declare interface GridRowInterface {
    (option?: GridRowOptions): GridRowAttribute;
}
declare interface HyperlinkAttribute extends CommonMethod {
    color(value: (Color|number|string|Resource) | undefined): HyperlinkAttribute;
    attributeModifier(value: (AttributeModifier<HyperlinkAttribute>|AttributeModifier<CommonMethod>) | undefined): HyperlinkAttribute;
}
declare interface HyperlinkInterface {
    (address: (string|Resource), content?: (string|Resource)): HyperlinkAttribute;
}
declare type DrawingColorFilter = drawing.ColorFilter;
declare type ResolutionQuality = image.ResolutionQuality;
declare type DrawingLattice = drawing.Lattice;
declare type ImageMatrix = matrix4.Matrix4Transit;
declare enum ImageRenderMode {
    ORIGINAL,
    Original,
    TEMPLATE = 1,
    Template = 1,
}
declare enum ImageContent {
    EMPTY,
}
declare enum DynamicRangeMode {
    HIGH,
    CONSTRAINT = 1,
    STANDARD = 2,
}
declare enum ImageInterpolation {
    NONE,
    None,
    LOW = 1,
    Low = 1,
    MEDIUM = 2,
    Medium = 2,
    HIGH = 3,
    High = 3,
}
declare enum ImageRotateOrientation {
    AUTO,
    UP = 1,
    RIGHT = 2,
    DOWN = 3,
    LEFT = 4,
    UP_MIRRORED = 5,
    RIGHT_MIRRORED = 6,
    DOWN_MIRRORED = 7,
    LEFT_MIRRORED = 8,
}
declare interface ImageCompleteEvent {
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
declare interface ImageSourceSize {
    width: number;
    height: number;
}
declare class ColorContent {
    constructor();
    static readonly ORIGIN: ColorContent;
}
declare interface ImageAttribute extends CommonMethod {
    alt(value: (string|Resource|image.PixelMap) | undefined): ImageAttribute;
    matchTextDirection(value: boolean | undefined): ImageAttribute;
    fitOriginalSize(value: boolean | undefined): ImageAttribute;
    fillColor(value: (ResourceColor|ColorContent|ColorMetrics) | undefined): ImageAttribute;
    objectFit(value: ImageFit | undefined): ImageAttribute;
    imageMatrix(value: matrix4.Matrix4Transit | undefined): ImageAttribute;
    objectRepeat(value: ImageRepeat | undefined): ImageAttribute;
    autoResize(value: boolean | undefined): ImageAttribute;
    renderMode(value: ImageRenderMode | undefined): ImageAttribute;
    dynamicRangeMode(value: DynamicRangeMode | undefined): ImageAttribute;
    interpolation(value: ImageInterpolation | undefined): ImageAttribute;
    sourceSize(value: ImageSourceSize | undefined): ImageAttribute;
    syncLoad(value: boolean | undefined): ImageAttribute;
    colorFilter(value: (ColorFilter|drawing.ColorFilter) | undefined): ImageAttribute;
    copyOption(value: CopyOptions | undefined): ImageAttribute;
    draggable(value: boolean | undefined): ImageAttribute;
    pointLight(value: PointLightStyle | undefined): ImageAttribute;
    edgeAntialiasing(value: number | undefined): ImageAttribute;
    onComplete(value: ImageOnCompleteCallback | undefined): ImageAttribute;
    onError(value: ImageErrorCallback | undefined): ImageAttribute;
    onFinish(value: (() => void) | undefined): ImageAttribute;
    enableAnalyzer(value: boolean | undefined): ImageAttribute;
    analyzerConfig(value: ImageAnalyzerConfig | undefined): ImageAttribute;
    resizable(value: ResizableOptions | undefined): ImageAttribute;
    privacySensitive(value: boolean | undefined): ImageAttribute;
    enhancedImageQuality(value: image.ResolutionQuality | undefined): ImageAttribute;
    orientation(value: ImageRotateOrientation | undefined): ImageAttribute;
    attributeModifier(value: (AttributeModifier<ImageAttribute>|AttributeModifier<CommonMethod>) | undefined): ImageAttribute;
}
declare type ImageErrorCallback = ((error: ImageError) => void);
declare type ImageOnCompleteCallback = ((loadEvent?: ImageCompleteEvent) => void);
declare interface ImageError {
    componentWidth: number;
    componentHeight: number;
    message: string;
    error?: BusinessError;
}
declare interface ResizableOptions {
    slice?: EdgeWidths;
    lattice?: drawing.Lattice;
}
declare interface ImageInterface {
    (src: (image.PixelMap|ResourceStr|DrawableDescriptor|ImageContent)): ImageAttribute;
    (src: (image.PixelMap|ResourceStr|DrawableDescriptor), imageAIOptions: ImageAIOptions): ImageAttribute;
}
declare interface ImageFrameInfo {
    src: (string|Resource|image.PixelMap);
    width?: (number|string);
    height?: (number|string);
    top?: (number|string);
    left?: (number|string);
    duration?: number;
}
declare interface ImageAnimatorAttribute extends CommonMethod {
    images(value: ImageFrameInfo[] | undefined): ImageAnimatorAttribute;
    state(value: AnimationStatus | undefined): ImageAnimatorAttribute;
    duration(value: number | undefined): ImageAnimatorAttribute;
    reverse(value: boolean | undefined): ImageAnimatorAttribute;
    fixedSize(value: boolean | undefined): ImageAnimatorAttribute;
    fillMode(value: FillMode | undefined): ImageAnimatorAttribute;
    iterations(value: number | undefined): ImageAnimatorAttribute;
    monitorInvisibleArea(value: boolean | undefined): ImageAnimatorAttribute;
    onStart(value: (() => void) | undefined): ImageAnimatorAttribute;
    onPause(value: (() => void) | undefined): ImageAnimatorAttribute;
    onRepeat(value: (() => void) | undefined): ImageAnimatorAttribute;
    onCancel(value: (() => void) | undefined): ImageAnimatorAttribute;
    onFinish(value: (() => void) | undefined): ImageAnimatorAttribute;
    attributeModifier(value: (AttributeModifier<ImageAnimatorAttribute>|AttributeModifier<CommonMethod>) | undefined): ImageAnimatorAttribute;
}
declare interface ImageAnimatorInterface {
    (): ImageAnimatorAttribute;
}
declare enum ImageAnalyzerType {
    SUBJECT,
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
declare interface ImageSpanAttribute extends BaseSpan {
    verticalAlign(value: ImageSpanAlignment | undefined): ImageSpanAttribute;
    objectFit(value: ImageFit | undefined): ImageSpanAttribute;
    onComplete(value: ImageCompleteCallback | undefined): ImageSpanAttribute;
    onError(value: ImageErrorCallback | undefined): ImageSpanAttribute;
    alt(value: image.PixelMap | undefined): ImageSpanAttribute;
    attributeModifier(value: (AttributeModifier<ImageSpanAttribute>|AttributeModifier<CommonMethod>) | undefined): ImageSpanAttribute;
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
declare interface ImageSpanInterface {
    (value: (ResourceStr|image.PixelMap)): ImageSpanAttribute;
}
declare class IndicatorComponentController {
    constructor();
    showNext(): void;
    showPrevious(): void;
    changeIndex(index: number, useAnimation?: boolean): void;
}
declare interface IndicatorComponentAttribute extends CommonMethod {
    initialIndex(value: number | undefined): IndicatorComponentAttribute;
    count(value: number | undefined): IndicatorComponentAttribute;
    style(value: (DotIndicator|DigitIndicator) | undefined): IndicatorComponentAttribute;
    loop(value: boolean | undefined): IndicatorComponentAttribute;
    vertical(value: boolean | undefined): IndicatorComponentAttribute;
    onChange(value: ((value0: number) => void) | undefined): IndicatorComponentAttribute;
    attributeModifier(value: (AttributeModifier<IndicatorComponentAttribute>|AttributeModifier<CommonMethod>) | undefined): IndicatorComponentAttribute;
}
declare interface IndicatorComponentInterface {
    (controller?: IndicatorComponentController): IndicatorComponentAttribute;
}
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
declare interface InteropComponent {
    name: string;
    component: Object;
}
declare type Callback_InteropComponent = (() => InteropComponent);
declare type Callback_Number_ESObject_Void = ((elmtId: number, instance: ESObject) => void);
declare function ArkUICompatible(init: (() => InteropComponent), update: ((elmtId: number, instance: ESObject) => void)): void;
declare enum DataOperationType {
    ADD = "'add'",
    DELETE = "'delete'",
    EXCHANGE = "'exchange'",
    MOVE = "'move'",
    CHANGE = "'change'",
    RELOAD = "'reload'",
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
declare type Callback_T_Number_Void<T> = ((item: T, index: number) => void);
declare type Callback_T_Number_String<T> = ((item: T, index: number) => string);
declare type ShapePoint = [ Length, Length ]
declare interface LineOptions {
    width?: (string|number);
    height?: (string|number);
}
declare interface LineAttribute extends CommonShapeMethod {
    startPoint(value: ShapePoint | undefined): LineAttribute;
    endPoint(value: ShapePoint | undefined): LineAttribute;
    attributeModifier(value: (AttributeModifier<LineAttribute>|AttributeModifier<CommonMethod>) | undefined): LineAttribute;
}
declare interface LineInterface {
    (options?: LineOptions): LineAttribute;
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
declare interface LinearIndicatorAttribute extends CommonMethod {
    indicatorStyle(value: LinearIndicatorStyle | undefined): LinearIndicatorAttribute;
    indicatorLoop(value: boolean | undefined): LinearIndicatorAttribute;
    onChange(value: OnLinearIndicatorChangeCallback | undefined): LinearIndicatorAttribute;
    attributeModifier(value: (AttributeModifier<LinearIndicatorAttribute>|AttributeModifier<CommonMethod>) | undefined): LinearIndicatorAttribute;
}
declare type OnLinearIndicatorChangeCallback = ((index: number, progress: number) => void);
declare interface LinearIndicatorInterface {
    (count?: number, controller?: LinearIndicatorController): LinearIndicatorAttribute;
}
declare enum ScrollState {
    IDLE,
    Idle,
    SCROLL = 1,
    Scroll = 1,
    FLING = 2,
    Fling = 2,
}
declare enum ListItemAlign {
    START,
    Start,
    CENTER = 1,
    Center = 1,
    END = 2,
    End = 2,
}
declare enum ListItemGroupArea {
    NONE,
    IN_LIST_ITEM_AREA = 1,
    IN_HEADER_AREA = 2,
    IN_FOOTER_AREA = 3,
}
declare enum StickyStyle {
    NONE,
    None,
    HEADER = 1,
    Header = 1,
    FOOTER = 2,
    Footer = 2,
}
declare enum ChainEdgeEffect {
    DEFAULT,
    STRETCH = 1,
}
declare enum ScrollSnapAlign {
    NONE,
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
    constructor();
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
declare interface ListDividerOptions {
    strokeWidth: Length;
    color?: ResourceColor;
    startMargin?: Length;
    endMargin?: Length;
}
declare type Callback_Number_Number_Number_Void = ((start: number, end: number, center: number) => void);
declare type Callback_Number_Number_Boolean = ((from: number, to: number) => boolean);
declare interface ListAttribute extends ScrollableCommonMethod {
    alignListItem(value: ListItemAlign | undefined): ListAttribute;
    listDirection(value: Axis | undefined): ListAttribute;
    contentStartOffset(value: number | undefined): ListAttribute;
    contentEndOffset(value: number | undefined): ListAttribute;
    divider(value: ListDividerOptions | undefined): ListAttribute;
    multiSelectable(value: boolean | undefined): ListAttribute;
    cachedCount(value: number | undefined): ListAttribute;
    chainAnimation(value: boolean | undefined): ListAttribute;
    chainAnimationOptions(value: ChainAnimationOptions | undefined): ListAttribute;
    sticky(value: StickyStyle | undefined): ListAttribute;
    scrollSnapAlign(value: ScrollSnapAlign | undefined): ListAttribute;
    childrenMainSize(value: ChildrenMainSize | undefined): ListAttribute;
    maintainVisibleContentPosition(value: boolean | undefined): ListAttribute;
    stackFromEnd(value: boolean | undefined): ListAttribute;
    onScrollIndex(value: ((start: number, end: number, center: number) => void) | undefined): ListAttribute;
    onScrollVisibleContentChange(value: OnScrollVisibleContentChangeCallback | undefined): ListAttribute;
    onItemMove(value: ((from: number, to: number) => boolean) | undefined): ListAttribute;
    onItemDragStart(value: OnItemDragStartCallback | undefined): ListAttribute;
    onItemDragEnter(value: ((event: ItemDragInfo) => void) | undefined): ListAttribute;
    onItemDragMove(value: ((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void) | undefined): ListAttribute;
    onItemDragLeave(value: ((event: ItemDragInfo, itemIndex: number) => void) | undefined): ListAttribute;
    onItemDrop(value: ((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void) | undefined): ListAttribute;
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): ListAttribute;
    onWillScroll(value: OnWillScrollCallback | undefined): ListAttribute;
    onDidScroll(value: OnScrollCallback | undefined): ListAttribute;
    attributeModifier(value: (AttributeModifier<ListAttribute>|AttributeModifier<CommonMethod>) | undefined): ListAttribute;
    lanes(value: (number|LengthConstrain) | undefined, gutter?: Dimension | undefined): ListAttribute;
    cachedCount(count: number | undefined, show: boolean | undefined): ListAttribute;
}
declare interface ListInterface {
    (options?: ListOptions): ListAttribute;
}
declare enum SwipeEdgeEffect {
    SPRING,
    Spring,
    NONE = 1,
    None = 1,
}
declare enum SwipeActionState {
    COLLAPSED,
    EXPANDED = 1,
    ACTIONING = 2,
}
declare type Callback_SwipeActionState_Void = ((state: SwipeActionState) => void);
declare interface SwipeActionItem {
    builder?: CustomBuilder;
    builderComponent?: ComponentContent;
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
    onOffsetChange?: ((offset: number) => void);
}
declare enum ListItemStyle {
    NONE,
    CARD = 1,
}
declare interface ListItemOptions {
    style?: ListItemStyle;
}
declare interface ListItemAttribute extends CommonMethod {
    selectable(value: boolean | undefined): ListItemAttribute;
    selected(value: boolean | undefined): ListItemAttribute;
    swipeAction(value: SwipeActionOptions | undefined): ListItemAttribute;
    onSelect(value: ((isSelected: boolean) => void) | undefined): ListItemAttribute;
    attributeModifier(value: (AttributeModifier<ListItemAttribute>|AttributeModifier<CommonMethod>) | undefined): ListItemAttribute;
}
declare interface ListItemInterface {
    (value?: ListItemOptions): ListItemAttribute;
}
declare enum ListItemGroupStyle {
    NONE,
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
declare interface ListItemGroupAttribute extends CommonMethod {
    divider(value: ListDividerOptions | undefined): ListItemGroupAttribute;
    childrenMainSize(value: ChildrenMainSize | undefined): ListItemGroupAttribute;
    attributeModifier(value: (AttributeModifier<ListItemGroupAttribute>|AttributeModifier<CommonMethod>) | undefined): ListItemGroupAttribute;
}
declare interface ListItemGroupInterface {
    (options?: ListItemGroupOptions): ListItemGroupAttribute;
}
declare enum LoadingProgressStyle {
    DEFAULT,
    Default,
    CIRCULAR = 1,
    Circular = 1,
    ORBITAL = 2,
    Orbital = 2,
}
declare interface LoadingProgressAttribute extends CommonMethod {
    color(value: ResourceColor | undefined): LoadingProgressAttribute;
    enableLoading(value: boolean | undefined): LoadingProgressAttribute;
    contentModifier(value: ContentModifier<LoadingProgressConfiguration> | undefined): LoadingProgressAttribute;
    attributeModifier(value: (AttributeModifier<LoadingProgressAttribute>|AttributeModifier<CommonMethod>) | undefined): LoadingProgressAttribute;
}
declare interface LoadingProgressConfiguration extends CommonConfiguration<LoadingProgressConfiguration> {
    enableLoading: boolean;
}
declare interface LoadingProgressInterface {
    (): LoadingProgressAttribute;
}
declare interface MarqueeOptions {
    start: boolean;
    step?: number;
    loop?: number;
    fromStart?: boolean;
    src: string;
}
declare interface MarqueeAttribute extends CommonMethod {
    fontColor(value: ResourceColor | undefined): MarqueeAttribute;
    fontSize(value: Length | undefined): MarqueeAttribute;
    allowScale(value: boolean | undefined): MarqueeAttribute;
    fontWeight(value: (number|FontWeight|string) | undefined): MarqueeAttribute;
    fontFamily(value: (string|Resource) | undefined): MarqueeAttribute;
    marqueeUpdateStrategy(value: MarqueeUpdateStrategy | undefined): MarqueeAttribute;
    onStart(value: (() => void) | undefined): MarqueeAttribute;
    onBounce(value: (() => void) | undefined): MarqueeAttribute;
    onFinish(value: (() => void) | undefined): MarqueeAttribute;
    attributeModifier(value: (AttributeModifier<MarqueeAttribute>|AttributeModifier<CommonMethod>) | undefined): MarqueeAttribute;
}
declare interface MarqueeInterface {
    (options: MarqueeOptions): MarqueeAttribute;
}
declare class Matrix2D {
    constructor();
    constructor(unit: LengthMetricsUnit);
    scaleX?: number | undefined;
    rotateY?: number | undefined;
    rotateX?: number | undefined;
    scaleY?: number | undefined;
    translateX?: number | undefined;
    translateY?: number | undefined;
    identity(): Matrix2D;
    invert(): Matrix2D;
    rotate(degree: number, rx?: number, ry?: number): Matrix2D;
    translate(tx?: number, ty?: number): Matrix2D;
    scale(sx?: number, sy?: number): Matrix2D;
}
declare interface ASTCResource {
    sources: string[];
    column: number;
}
declare interface MediaCachedImageAttribute extends ImageAttribute {
    attributeModifier(value: (AttributeModifier<MediaCachedImageAttribute>|AttributeModifier<CommonMethod>) | undefined): MediaCachedImageAttribute;
}
declare interface MediaCachedImageInterface {
    (src: (image.PixelMap|ResourceStr|DrawableDescriptor|ASTCResource)): MediaCachedImageAttribute;
}
declare enum SubMenuExpandingMode {
    SIDE_EXPAND,
    EMBEDDED_EXPAND = 1,
    STACK_EXPAND = 2,
}
declare interface MenuAttribute extends CommonMethod {
    font(value: Font | undefined): MenuAttribute;
    fontColor(value: ResourceColor | undefined): MenuAttribute;
    radius(value: (Dimension|BorderRadiuses) | undefined): MenuAttribute;
    menuItemDivider(value: DividerStyleOptions | undefined): MenuAttribute;
    menuItemGroupDivider(value: DividerStyleOptions | undefined): MenuAttribute;
    subMenuExpandingMode(value: SubMenuExpandingMode | undefined): MenuAttribute;
    attributeModifier(value: (AttributeModifier<MenuAttribute>|AttributeModifier<CommonMethod>) | undefined): MenuAttribute;
}
declare interface MenuInterface {
    (): MenuAttribute;
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
declare interface MenuItemAttribute extends CommonMethod {
    selected(value: boolean | undefined): MenuItemAttribute;
    selectIcon(value: (boolean|ResourceStr|SymbolGlyphModifier) | undefined): MenuItemAttribute;
    onChange(value: ((selected: boolean) => void) | undefined): MenuItemAttribute;
    contentFont(value: Font | undefined): MenuItemAttribute;
    contentFontColor(value: ResourceColor | undefined): MenuItemAttribute;
    labelFont(value: Font | undefined): MenuItemAttribute;
    labelFontColor(value: ResourceColor | undefined): MenuItemAttribute;
    attributeModifier(value: (AttributeModifier<MenuItemAttribute>|AttributeModifier<CommonMethod>) | undefined): MenuItemAttribute;
}
declare interface MenuItemInterface {
    (value?: (MenuItemOptions|CustomBuilder)): MenuItemAttribute;
}
declare interface MenuItemGroupOptions {
    header?: (ResourceStr|CustomBuilder);
    footer?: (ResourceStr|CustomBuilder);
}
declare interface MenuItemGroupAttribute extends CommonMethod {
    attributeModifier(value: (AttributeModifier<MenuItemGroupAttribute>|AttributeModifier<CommonMethod>) | undefined): MenuItemGroupAttribute;
}
declare interface MenuItemGroupInterface {
    (value?: MenuItemGroupOptions): MenuItemGroupAttribute;
}
declare type Orientation = window.Orientation;
declare interface NavDestinationCommonTitle {
    main: (string|Resource);
    sub: (string|Resource);
}
declare interface NavDestinationCustomTitle {
    builder: CustomBuilder;
    height: (TitleHeight|Length);
}
declare enum NavigationSystemTransitionType {
    DEFAULT,
    NONE = 1,
    TITLE = 2,
    CONTENT = 3,
    FADE = 4,
    EXPLODE = 5,
    SLIDE_RIGHT = 6,
    SLIDE_BOTTOM = 7,
}
declare enum NavDestinationMode {
    STANDARD,
    DIALOG = 1,
}
declare enum NavDestinationActiveReason {
    TRANSITION,
    CONTENT_COVER = 1,
    SHEET = 2,
    DIALOG = 3,
    OVERLAY = 4,
    APP_STATE = 5,
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
declare interface NestedScrollInfo {
    parent: Scroller;
    child: Scroller;
}
declare interface NavDestinationTransition {
    onTransitionEnd?: (() => void);
    duration?: number;
    curve?: Curve;
    delay?: number;
    event: (() => void);
}
declare type Callback_Boolean = (() => boolean);
declare type Callback_NavDestinationContext_Void = ((value0: NavDestinationContext) => void);
declare type Callback_NavDestinationActiveReason_Void = ((value0: NavDestinationActiveReason) => void);
declare interface NavDestinationAttribute extends CommonMethod {
    hideTitleBar(value: boolean | undefined): NavDestinationAttribute;
    hideBackButton(value: boolean | undefined): NavDestinationAttribute;
    onShown(value: (() => void) | undefined): NavDestinationAttribute;
    onHidden(value: (() => void) | undefined): NavDestinationAttribute;
    onBackPressed(value: (() => boolean) | undefined): NavDestinationAttribute;
    mode(value: NavDestinationMode | undefined): NavDestinationAttribute;
    backButtonIcon(value: (ResourceStr|image.PixelMap|SymbolGlyphModifier) | undefined): NavDestinationAttribute;
    menus(value: (NavigationMenuItem[]|CustomBuilder) | undefined): NavDestinationAttribute;
    onReady(value: ((value0: NavDestinationContext) => void) | undefined): NavDestinationAttribute;
    onWillAppear(value: (() => void) | undefined): NavDestinationAttribute;
    onWillDisappear(value: (() => void) | undefined): NavDestinationAttribute;
    onWillShow(value: (() => void) | undefined): NavDestinationAttribute;
    onWillHide(value: (() => void) | undefined): NavDestinationAttribute;
    systemBarStyle(value: window.SystemBarStyle | undefined): NavDestinationAttribute;
    recoverable(value: boolean | undefined): NavDestinationAttribute;
    systemTransition(value: NavigationSystemTransitionType | undefined): NavDestinationAttribute;
    bindToScrollable(value: Scroller[] | undefined): NavDestinationAttribute;
    bindToNestedScrollable(value: NestedScrollInfo[] | undefined): NavDestinationAttribute;
    onActive(value: ((value0: NavDestinationActiveReason) => void) | undefined): NavDestinationAttribute;
    onInactive(value: ((value0: NavDestinationActiveReason) => void) | undefined): NavDestinationAttribute;
    customTransition(value: NavDestinationTransitionDelegate | undefined): NavDestinationAttribute;
    onNewParam(value: ((value0: Object | undefined) => void) | undefined): NavDestinationAttribute;
    preferredOrientation(value: Orientation | undefined): NavDestinationAttribute;
    enableNavigationIndicator(value: boolean | undefined): NavDestinationAttribute;
    attributeModifier(value: (AttributeModifier<NavDestinationAttribute>|AttributeModifier<CommonMethod>) | undefined): NavDestinationAttribute;
    title(value: (string|CustomBuilder|NavDestinationCommonTitle|NavDestinationCustomTitle|Resource) | undefined, options?: NavigationTitleOptions | undefined): NavDestinationAttribute;
    hideTitleBar(hide: boolean | undefined, animated: boolean | undefined): NavDestinationAttribute;
    backButtonIcon(icon: (ResourceStr|image.PixelMap|SymbolGlyphModifier) | undefined, accessibilityText?: ResourceStr | undefined): NavDestinationAttribute;
    menus(items: (NavigationMenuItem[]|CustomBuilder) | undefined, options?: NavigationMenuOptions | undefined): NavDestinationAttribute;
    toolbarConfiguration(toolbarParam: (ToolbarItem[]|CustomBuilder) | undefined, options?: NavigationToolbarOptions | undefined): NavDestinationAttribute;
    hideToolBar(hide: boolean | undefined, animated?: boolean | undefined): NavDestinationAttribute;
    ignoreLayoutSafeArea(types?: LayoutSafeAreaType[] | undefined, edges?: LayoutSafeAreaEdge[] | undefined): NavDestinationAttribute;
    enableStatusBar(enabled: boolean | undefined, animated?: boolean | undefined): NavDestinationAttribute;
}
declare type NavDestinationTransitionDelegate = ((operation: NavigationOperation, isEnter: boolean) => NavDestinationTransition[] | undefined);
declare interface NavDestinationInterface {
    (): NavDestinationAttribute;
}
declare type SystemBarStyle = window.SystemBarStyle;
declare interface NavigationCommonTitle {
    main: (string|Resource);
    sub: (string|Resource);
}
declare interface NavigationCustomTitle {
    builder: CustomBuilder;
    height: (TitleHeight|Length);
}
declare enum NavigationMode {
    STACK,
    Stack,
    SPLIT = 1,
    Split = 1,
    AUTO = 2,
    Auto = 2,
}
declare enum NavBarPosition {
    START,
    Start,
    END = 1,
    End = 1,
}
declare enum NavigationTitleMode {
    FREE,
    Free,
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
declare type Callback_PopInfo_Void = ((value0: PopInfo) => void);
declare class NavPathInfo {
    constructor(name: string, param: Object | undefined, onPop?: ((value0: PopInfo) => void), isEntry?: boolean);
    name: string;
    param?: Object | undefined;
    onPop?: ((value0: PopInfo) => void) | undefined;
    isEntry?: boolean | undefined;
    navDestinationId?: string | undefined;
}
declare enum LaunchMode {
    STANDARD,
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
    pushPathByName(name: string, param: Object | undefined, animated?: boolean): void;
    pushPathByName(name: string, param: Object, onPop: ((value0: PopInfo) => void), animated?: boolean): void;
    pushDestinationByName(name: string, param: Object, animated?: boolean): Promise<void>;
    pushDestinationByName(name: string, param: Object, onPop: ((value0: PopInfo) => void), animated?: boolean): Promise<void>;
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
    getParamByIndex(index: number): Object | undefined;
    getParamByName(name: string): Object | undefined[];
    getIndexByName(name: string): number[];
    getParent(): NavPathStack | undefined;
    size(): number;
    disableAnimation(value: boolean): void;
    setInterception(interception: NavigationInterception): void;
    getPathStack(): NavPathInfo[];
    setPathStack(pathStack: NavPathInfo[], animated?: boolean): void;
}
declare type NavBar = string;
declare type InterceptionShowCallback = ((from: (NavDestinationContext|NavBar), to: (NavDestinationContext|NavBar), operation: NavigationOperation, isAnimated: boolean) => void);
declare type InterceptionModeCallback = ((mode: NavigationMode) => void);
declare interface NavigationInterception {
    willShow?: InterceptionShowCallback;
    didShow?: InterceptionShowCallback;
    modeChange?: InterceptionModeCallback;
}
declare enum ToolbarItemStatus {
    NORMAL,
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
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    barStyle?: BarStyle;
    paddingStart?: LengthMetrics;
    paddingEnd?: LengthMetrics;
    mainTitleModifier?: TextModifier;
    subTitleModifier?: TextModifier;
    enableHoverMode?: boolean;
}
declare enum BarStyle {
    STANDARD,
    STACK = 1,
    SAFE_AREA_PADDING = 2,
}
declare interface NavigationToolbarOptions {
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    moreButtonOptions?: MoreButtonOptions;
    barStyle?: BarStyle;
    hideItemValue?: boolean;
}
declare interface NavigationMenuOptions {
    moreButtonOptions?: MoreButtonOptions;
}
declare interface MoreButtonOptions {
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
}
declare type Tuple_Dimension_Dimension = [ Dimension, Dimension ]
declare type Callback_NavigationTitleMode_Void = ((titleMode: NavigationTitleMode) => void);
declare type Callback_NavigationMode_Void = ((mode: NavigationMode) => void);
declare type Type_NavigationAttribute_customNavContentTransition = ((from: NavContentInfo, to: NavContentInfo, operation: NavigationOperation) => NavigationAnimatedTransition | undefined);
declare interface NavigationAttribute extends CommonMethod {
    navBarWidth(value: Length | undefined): NavigationAttribute;
    navBarPosition(value: NavBarPosition | undefined): NavigationAttribute;
    navBarWidthRange(value: [ Dimension, Dimension ] | undefined): NavigationAttribute;
    minContentWidth(value: Dimension | undefined): NavigationAttribute;
    mode(value: NavigationMode | undefined): NavigationAttribute;
    backButtonIcon(value: (string|image.PixelMap|Resource|SymbolGlyphModifier) | undefined): NavigationAttribute;
    hideNavBar(value: boolean | undefined): NavigationAttribute;
    hideTitleBar(value: boolean | undefined): NavigationAttribute;
    hideBackButton(value: boolean | undefined): NavigationAttribute;
    titleMode(value: NavigationTitleMode | undefined): NavigationAttribute;
    menus(value: (NavigationMenuItem[]|CustomBuilder) | undefined): NavigationAttribute;
    hideToolBar(value: boolean | undefined): NavigationAttribute;
    enableToolBarAdaptation(value: boolean | undefined): NavigationAttribute;
    onTitleModeChange(value: ((titleMode: NavigationTitleMode) => void) | undefined): NavigationAttribute;
    onNavBarStateChange(value: ((isVisible: boolean) => void) | undefined): NavigationAttribute;
    onNavigationModeChange(value: ((mode: NavigationMode) => void) | undefined): NavigationAttribute;
    navDestination(value: PageMapBuilder | undefined): NavigationAttribute;
    customNavContentTransition(value: ((from: NavContentInfo, to: NavContentInfo, operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined): NavigationAttribute;
    systemBarStyle(value: window.SystemBarStyle | undefined): NavigationAttribute;
    recoverable(value: boolean | undefined): NavigationAttribute;
    enableDragBar(value: boolean | undefined): NavigationAttribute;
    enableModeChangeAnimation(value: boolean | undefined): NavigationAttribute;
    attributeModifier(value: (AttributeModifier<NavigationAttribute>|AttributeModifier<CommonMethod>) | undefined): NavigationAttribute;
    backButtonIcon(icon: (string|image.PixelMap|Resource|SymbolGlyphModifier) | undefined, accessibilityText?: ResourceStr | undefined): NavigationAttribute;
    title(value: (ResourceStr|CustomBuilder|NavigationCommonTitle|NavigationCustomTitle) | undefined, options?: NavigationTitleOptions | undefined): NavigationAttribute;
    hideTitleBar(hide: boolean | undefined, animated: boolean | undefined): NavigationAttribute;
    menus(items: (NavigationMenuItem[]|CustomBuilder) | undefined, options?: NavigationMenuOptions | undefined): NavigationAttribute;
    toolbarConfiguration(value: (ToolbarItem[]|CustomBuilder) | undefined, options?: NavigationToolbarOptions | undefined): NavigationAttribute;
    hideToolBar(hide: boolean | undefined, animated: boolean | undefined): NavigationAttribute;
    ignoreLayoutSafeArea(types?: LayoutSafeAreaType[] | undefined, edges?: LayoutSafeAreaEdge[] | undefined): NavigationAttribute;
}
declare type Callback_NavigationTransitionProxy_Void = ((transitionProxy: NavigationTransitionProxy) => void);
declare interface NavigationAnimatedTransition {
    onTransitionEnd?: ((isVisible: boolean) => void);
    timeout?: number;
    isInteractive?: boolean;
    transition: ((transitionProxy: NavigationTransitionProxy) => void);
}
declare interface NavigationTransitionProxy {
    from: NavContentInfo;
    to: NavContentInfo;
    isInteractive?: boolean;
    cancelTransition?: VoidCallback;
    updateTransition?: UpdateTransitionCallback;
    finishTransition(): void;
}
declare type UpdateTransitionCallback = ((progress: number) => void);
declare interface NavContentInfo {
    name?: string;
    index: number;
    mode?: NavDestinationMode;
    param?: Object;
    navDestinationId?: string;
}
declare interface NavigationInterface {
    (): NavigationAttribute;
    (pathInfos: NavPathStack): NavigationAttribute;
}
declare interface NodeContainerAttribute extends CommonMethod {
    attributeModifier(value: (AttributeModifier<NodeContainerAttribute>|AttributeModifier<CommonMethod>) | undefined): NodeContainerAttribute;
}
declare interface NodeContainerInterface {
    (controller: NodeController): NodeContainerAttribute;
}
declare type Context_getGroupDir_Callback = ((result: string) => void);
declare namespace common {
    class Context extends BaseContext {
        cacheDir: string;
        tempDir: string;
        filesDir: string;
        databaseDir: string;
        preferencesDir: string;
        bundleCodeDir: string;
        distributedFilesDir: string;
        resourceDir: string;
        cloudFileDir: string;
        createBundleContext(bundleName: string): common.Context;
        createModuleContext(moduleName: string): common.Context;
        createModuleContext(bundleName: string, moduleName: string): common.Context;
        getGroupDir(dataGroupID: string, callback_: Context_getGroupDir_Callback): void;
        getGroupDir(dataGroupID: string): Promise<string>;
    }
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
declare class DrawableDescriptor {
    constructor();
    getPixelMap(): image.PixelMap;
}
declare namespace observer {
    interface RouterPageInfo {
    }
}
declare namespace observer {
    interface NavigationInfo {
    }
}
declare namespace observer {
    interface NavDestinationInfo {
    }
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
declare interface RectShape {
    new(options?: (RectShapeOptions|RoundRectShapeOptions));
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
declare interface Theme {
    colors: Colors;
}
declare interface Colors {
    brand: ResourceColor;
    warning: ResourceColor;
    alert: ResourceColor;
    confirm: ResourceColor;
    fontPrimary: ResourceColor;
    fontSecondary: ResourceColor;
    fontTertiary: ResourceColor;
    fontFourth: ResourceColor;
    fontEmphasize: ResourceColor;
    fontOnPrimary: ResourceColor;
    fontOnSecondary: ResourceColor;
    fontOnTertiary: ResourceColor;
    fontOnFourth: ResourceColor;
    iconPrimary: ResourceColor;
    iconSecondary: ResourceColor;
    iconTertiary: ResourceColor;
    iconFourth: ResourceColor;
    iconEmphasize: ResourceColor;
    iconSubEmphasize: ResourceColor;
    iconOnPrimary: ResourceColor;
    iconOnSecondary: ResourceColor;
    iconOnTertiary: ResourceColor;
    iconOnFourth: ResourceColor;
    backgroundPrimary: ResourceColor;
    backgroundSecondary: ResourceColor;
    backgroundTertiary: ResourceColor;
    backgroundFourth: ResourceColor;
    backgroundEmphasize: ResourceColor;
    compForegroundPrimary: ResourceColor;
    compBackgroundPrimary: ResourceColor;
    compBackgroundPrimaryTran: ResourceColor;
    compBackgroundPrimaryContrary: ResourceColor;
    compBackgroundGray: ResourceColor;
    compBackgroundSecondary: ResourceColor;
    compBackgroundTertiary: ResourceColor;
    compBackgroundEmphasize: ResourceColor;
    compBackgroundNeutral: ResourceColor;
    compEmphasizeSecondary: ResourceColor;
    compEmphasizeTertiary: ResourceColor;
    compDivider: ResourceColor;
    compCommonContrary: ResourceColor;
    compBackgroundFocus: ResourceColor;
    compFocusedPrimary: ResourceColor;
    compFocusedSecondary: ResourceColor;
    compFocusedTertiary: ResourceColor;
    interactiveHover: ResourceColor;
    interactivePressed: ResourceColor;
    interactiveFocus: ResourceColor;
    interactiveActive: ResourceColor;
    interactiveSelect: ResourceColor;
    interactiveClick: ResourceColor;
}
declare interface CustomTheme {
    colors?: Colors;
}
declare type CustomColors = Colors;
declare class ThemeControl {
    constructor();
    static setDefaultTheme(theme: CustomTheme): void;
}
declare class UIContext {
    getFont(): drawing.Font;
    getFilteredInspectorTree(filters?: string[]): string;
    getFilteredInspectorTreeById(id: string, depth: number, filters?: string[]): string;
    animateTo(value: AnimateParam, event: (() => void)): void;
    showTextPickerDialog(options: TextPickerDialogOptions): void;
    runScopedTask(callback_: (() => void)): void;
    animateToImmediately(param: AnimateParam, event: (() => void)): void;
    getFrameNodeById(id: string): FrameNode | undefined;
    getAttachedFrameNodeById(id: string): FrameNode | undefined;
    getFrameNodeByUniqueId(id: number): FrameNode | undefined;
    vp2px(value: number): number;
    px2vp(value: number): number;
    fp2px(value: number): number;
    px2fp(value: number): number;
    lpx2px(value: number): number;
    px2lpx(value: number): number;
    getHostContext(): common.Context | undefined;
    setDynamicDimming(id: string, value: number): void;
    getWindowName(): string | undefined;
    getWindowWidthBreakpoint(): WidthBreakpoint;
    getWindowHeightBreakpoint(): HeightBreakpoint;
    openBindSheet<T>(bindSheetContent: ComponentContent, sheetOptions?: SheetOptions, targetId?: number): Promise<void>;
    updateBindSheet<T>(bindSheetContent: ComponentContent, sheetOptions: SheetOptions, partialUpdate?: boolean): Promise<void>;
    closeBindSheet<T>(bindSheetContent: ComponentContent): Promise<void>;
    clearResourceCache(): void;
    isFollowingSystemFontScale(): boolean;
    getMaxFontScale(): number;
}
declare class TextMenuController {
    setMenuOptions(options: TextMenuOptions): void;
}
declare type ErrorCallback = ((error: BusinessError) => void);
declare interface BusinessError {
    name: string;
    message: string;
    stack?: string;
    code: number;
}
declare namespace unifiedDataChannel {
    interface Summary {
        summary: Map<string,number>;
        totalSize: number;
    }
}
declare namespace unifiedDataChannel {
    class UnifiedData {
        constructor();
        hasType(UnifiedData_type: string): boolean;
        getTypes(): string[];
    }
}
declare namespace uniformTypeDescriptor {
    enum UniformDataType {
        ENTITY = "general.entity",
        OBJECT = "general.object",
        COMPOSITE_OBJECT = "general.composite-object",
        TEXT = "general.text",
        PLAIN_TEXT = "general.plain-text",
        HTML = "general.html",
        HYPERLINK = "general.hyperlink",
        XML = "general.xml",
        XHTML = "general.xhtml",
        RSS = "general.rss",
        SMIL = "com.real.smil",
        SOURCE_CODE = "general.source-code",
        SCRIPT = "general.script",
        SHELL_SCRIPT = "general.shell-script",
        CSH_SCRIPT = "general.csh-script",
        PERL_SCRIPT = "general.perl-script",
        PHP_SCRIPT = "general.php-script",
        PYTHON_SCRIPT = "general.python-script",
        RUBY_SCRIPT = "general.ruby-script",
        TYPE_SCRIPT = "general.type-script",
        JAVA_SCRIPT = "general.java-script",
        CSS = "general.css",
        C_HEADER = "general.c-header",
        C_SOURCE = "general.c-source",
        C_PLUS_PLUS_HEADER = "general.c-plus-plus-header",
        C_PLUS_PLUS_SOURCE = "general.c-plus-plus-source",
        JAVA_SOURCE = "general.java-source",
        TEX = "general.tex",
        MARKDOWN = "general.markdown",
        ASC_TEXT = "general.asc-text",
        RICH_TEXT = "general.rich-text",
        DELIMITED_VALUES_TEXT = "general.delimited-values-text",
        COMMA_SEPARATED_VALUES_TEXT = "general.comma-separated-values-text",
        TAB_SEPARATED_VALUES_TEXT = "general.tab-separated-values-text",
        EBOOK = "general.ebook",
        EPUB = "general.epub",
        AZW = "com.amazon.azw",
        AZW3 = "com.amazon.azw3",
        KFX = "com.amazon.kfx",
        MOBI = "com.amazon.mobi",
        MEDIA = "general.media",
        IMAGE = "general.image",
        JPEG = "general.jpeg",
        PNG = "general.png",
        RAW_IMAGE = "general.raw-image",
        TIFF = "general.tiff",
        BMP = "com.microsoft.bmp",
        ICO = "com.microsoft.ico",
        PHOTOSHOP_IMAGE = "com.adobe.photoshop-image",
        AI_IMAGE = "com.adobe.illustrator.ai-image",
        FAX = "general.fax",
        JFX_FAX = "com.j2.jfx-fax",
        EFX_FAX = "com.js.efx-fax",
        XBITMAP_IMAGE = "general.xbitmap-image",
        GIF = "general.gif",
        TGA_IMAGE = "com.truevision.tga-image",
        SGI_IMAGE = "com.sgi.sgi-image",
        OPENEXR_IMAGE = "com.ilm.openexr-image",
        FLASHPIX_IMAGE = "com.kodak.flashpix.image",
        WORD_DOC = "com.microsoft.word.doc",
        EXCEL = "com.microsoft.excel.xls",
        PPT = "com.microsoft.powerpoint.ppt",
        WORD_DOT = "com.microsoft.word.dot",
        POWERPOINT_PPS = "com.microsoft.powerpoint.pps",
        POWERPOINT_POT = "com.microsoft.powerpoint.pot",
        EXCEL_XLT = "com.microsoft.excel.xlt",
        VISIO_VSD = "com.microsoft.visio.vsd",
        PDF = "com.adobe.pdf",
        POSTSCRIPT = "com.adobe.postscript",
        ENCAPSULATED_POSTSCRIPT = "com.adobe.encapsulated-postscript",
        VIDEO = "general.video",
        AVI = "general.avi",
        MPEG = "general.mpeg",
        MPEG4 = "general.mpeg-4",
        VIDEO_3GPP = "general.3gpp",
        VIDEO_3GPP2 = "general.3gpp2",
        TS = "general.ts",
        MPEGURL_VIDEO = "general.mpegurl-video",
        WINDOWS_MEDIA_WM = "com.microsoft.windows-media-wm",
        WINDOWS_MEDIA_WMV = "com.microsoft.windows-media-wmv",
        WINDOWS_MEDIA_WMP = "com.microsoft.windows-media-wmp",
        WINDOWS_MEDIA_WVX = "com.microsoft.windows-media-wvx",
        WINDOWS_MEDIA_WMX = "com.microsoft.windows-media-wmx",
        REALMEDIA = "com.real.realmedia",
        MATROSKA_VIDEO = "org.matroska.mkv",
        FLASH = "com.adobe.flash",
        AUDIO = "general.audio",
        AAC = "general.aac",
        AIFF = "general.aiff",
        ALAC = "general.alac",
        FLAC = "general.flac",
        MP3 = "general.mp3",
        OGG = "general.ogg",
        PCM = "general.pcm",
        WINDOWS_MEDIA_WMA = "com.microsoft.windows-media-wma",
        WAVEFORM_AUDIO = "com.microsoft.waveform-audio",
        WINDOWS_MEDIA_WAX = "com.microsoft.windows-media-wax",
        AU_AUDIO = "general.au-audio",
        AIFC_AUDIO = "general.aifc-audio",
        MPEGURL_AUDIO = "general.mpegurl-audio",
        MPEG_4_AUDIO = "general.mpeg-4-audio",
        MP2 = "general.mp2",
        MPEG_AUDIO = "general.mpeg-audio",
        ULAW_AUDIO = "general.ulaw-audio",
        SD2_AUDIO = "com.digidesign.sd2-audio",
        REALAUDIO = "com.real.realaudio",
        MATROSKA_AUDIO = "org.matroska.mka",
        FILE = "general.file",
        DIRECTORY = "general.directory",
        FOLDER = "general.folder",
        SYMLINK = "general.symlink",
        ARCHIVE = "general.archive",
        BZ2_ARCHIVE = "general.bz2-archive",
        OPG = "general.opg",
        TAZ_ARCHIVE = "general.taz-archive",
        WEB_ARCHIVE = "general.web-archive",
        DISK_IMAGE = "general.disk-image",
        ISO = "general.iso",
        TAR_ARCHIVE = "general.tar-archive",
        ZIP_ARCHIVE = "general.zip-archive",
        JAVA_ARCHIVE = "com.sun.java-archive",
        GNU_TAR_ARCHIVE = "org.gnu.gnu-tar-archive",
        GNU_ZIP_ARCHIVE = "org.gnu.gnu-zip-archive",
        GNU_ZIP_TAR_ARCHIVE = "org.gnu.gnu-zip-tar-archive",
        OPENXML = "org.openxmlformats.openxml",
        WORDPROCESSINGML_DOCUMENT = "org.openxmlformats.wordprocessingml.document",
        SPREADSHEETML_SHEET = "org.openxmlformats.spreadsheetml.sheet",
        PRESENTATIONML_PRESENTATION = "org.openxmlformats.presentationml.presentation",
        DRAWINGML_VISIO = "org.openxmlformats.drawingml.visio",
        DRAWINGML_TEMPLATE = "org.openxmlformats.drawingml.template",
        WORDPROCESSINGML_TEMPLATE = "org.openxmlformats.wordprocessingml.template",
        PRESENTATIONML_TEMPLATE = "org.openxmlformats.presentationml.template",
        PRESENTATIONML_SLIDESHOW = "org.openxmlformats.presentationml.slideshow",
        SPREADSHEETML_TEMPLATE = "org.openxmlformats.spreadsheetml.template",
        OPENDOCUMENT = "org.oasis.opendocument",
        OPENDOCUMENT_TEXT = "org.oasis.opendocument.text",
        OPENDOCUMENT_SPREADSHEET = "org.oasis.opendocument.spreadsheet",
        OPENDOCUMENT_PRESENTATION = "org.oasis.opendocument.presentation",
        OPENDOCUMENT_GRAPHICS = "org.oasis.opendocument.graphics",
        OPENDOCUMENT_FORMULA = "org.oasis.opendocument.formula",
        STUFFIT_ARCHIVE = "com.allume.stuffit-archive",
        RAR_ARCHIVE = "com.rarlab.rar-archive",
        SEVEN_ZIP_ARCHIVE = "org.7-zip.7-zip-archive",
        CALENDAR = "general.calendar",
        VCS = "general.vcs",
        ICS = "general.ics",
        CONTACT = "general.contact",
        DATABASE = "general.database",
        MESSAGE = "general.message",
        EXECUTABLE = "general.executable",
        PORTABLE_EXECUTABLE = "com.microsoft.portable-executable",
        SUN_JAVA_CLASS = "com.sun.java-class",
        VCARD = "general.vcard",
        NAVIGATION = "general.navigation",
        LOCATION = "general.location",
        FONT = "general.font",
        TRUETYPE_FONT = "general.truetype-font",
        TRUETYPE_COLLECTION_FONT = "general.truetype-collection-font",
        OPENTYPE_FONT = "general.opentype-font",
        POSTSCRIPT_FONT = "com.adobe.postscript-font",
        POSTSCRIPT_PFB_FONT = "com.adobe.postscript-pfb-font",
        POSTSCRIPT_PFA_FONT = "com.adobe.postscript-pfa-font",
        OPENHARMONY_FORM = "openharmony.form",
        OPENHARMONY_APP_ITEM = "openharmony.app-item",
        OPENHARMONY_PIXEL_MAP = "openharmony.pixel-map",
        OPENHARMONY_ATOMIC_SERVICE = "openharmony.atomic-service",
        OPENHARMONY_PACKAGE = "openharmony.package",
        OPENHARMONY_HAP = "openharmony.hap",
        OPENHARMONY_HDOC = "openharmony.hdoc",
        OPENHARMONY_HINOTE = "openharmony.hinote",
        OPENHARMONY_STYLED_STRING = "openharmony.styled-string",
        OPENHARMONY_WANT = "openharmony.want",
        OFD = "general.ofd",
        CAD = "general.cad",
        OCTET_STREAM = "general.octet-stream",
    }
}
declare namespace font {
    interface UIFontFallbackInfo {
        language: string;
        family: string;
    }
}
declare namespace font {
    interface UIFontAliasInfo {
        name: string;
        weight: number;
    }
}
declare namespace font {
    interface UIFontAdjustInfo {
        weight: number;
        to: number;
    }
}
declare namespace font {
    interface UIFontGenericInfo {
        family: string;
        alias: font.UIFontAliasInfo[];
        adjust: font.UIFontAdjustInfo[];
    }
}
declare namespace font {
    interface UIFontFallbackGroupInfo {
        fontSetName: string;
        fallback: font.UIFontFallbackInfo[];
    }
}
declare namespace font {
    interface UIFontConfig {
        fontDir: string[];
        generic: font.UIFontGenericInfo[];
        fallbackGroups: font.UIFontFallbackGroupInfo[];
    }
}
declare namespace font {
    function getUIFontConfig(): font.UIFontConfig;
}
declare namespace common2D {
    interface Color {
        alpha: number;
        red: number;
        green: number;
        blue: number;
    }
}
declare namespace common2D {
    interface Rect {
        left: number;
        top: number;
        right: number;
        bottom: number;
    }
}
declare namespace common2D {
    interface Point {
        x: number;
        y: number;
    }
}
declare namespace common2D {
    interface Point3d extends common2D.Point {
        z: number;
    }
}
declare namespace drawing {
    enum BlendMode {
        CLEAR,
        SRC = 1,
        DST = 2,
        SRC_OVER = 3,
        DST_OVER = 4,
        SRC_IN = 5,
        DST_IN = 6,
        SRC_OUT = 7,
        DST_OUT = 8,
        SRC_ATOP = 9,
        DST_ATOP = 10,
        XOR = 11,
        PLUS = 12,
        MODULATE = 13,
        SCREEN = 14,
        OVERLAY = 15,
        DARKEN = 16,
        LIGHTEN = 17,
        COLOR_DODGE = 18,
        COLOR_BURN = 19,
        HARD_LIGHT = 20,
        SOFT_LIGHT = 21,
        DIFFERENCE = 22,
        EXCLUSION = 23,
        MULTIPLY = 24,
        HUE = 25,
        SATURATION = 26,
        COLOR = 27,
        LUMINOSITY = 28,
    }
}
declare namespace drawing {
    enum PathDirection {
        CLOCKWISE,
        COUNTER_CLOCKWISE = 1,
    }
}
declare namespace drawing {
    enum PathFillType {
        WINDING,
        EVEN_ODD = 1,
        INVERSE_WINDING = 2,
        INVERSE_EVEN_ODD = 3,
    }
}
declare namespace drawing {
    enum PathMeasureMatrixFlags {
        GET_POSITION_MATRIX,
        GET_TANGENT_MATRIX = 1,
        GET_POSITION_AND_TANGENT_MATRIX = 2,
    }
}
declare namespace drawing {
    class RoundRect {
        constructor(rect: common2D.Rect, xRadii: number, yRadii: number);
        setCorner(pos: drawing.CornerPos, x: number, y: number): void;
        getCorner(pos: drawing.CornerPos): common2D.Point;
        offset(dx: number, dy: number): void;
    }
}
declare namespace drawing {
    enum PathOp {
        DIFFERENCE,
        INTERSECT = 1,
        UNION = 2,
        XOR = 3,
        REVERSE_DIFFERENCE = 4,
    }
}
declare namespace drawing {
    class Path {
        constructor();
        constructor(path: drawing.Path);
        moveTo(x: number, y: number): void;
        lineTo(x: number, y: number): void;
        arcTo(x1: number, y1: number, x2: number, y2: number, startDeg: number, sweepDeg: number): void;
        quadTo(ctrlX: number, ctrlY: number, endX: number, endY: number): void;
        conicTo(ctrlX: number, ctrlY: number, endX: number, endY: number, weight: number): void;
        cubicTo(ctrlX1: number, ctrlY1: number, ctrlX2: number, ctrlY2: number, endX: number, endY: number): void;
        rMoveTo(dx: number, dy: number): void;
        rLineTo(dx: number, dy: number): void;
        rQuadTo(dx1: number, dy1: number, dx2: number, dy2: number): void;
        rConicTo(ctrlX: number, ctrlY: number, endX: number, endY: number, weight: number): void;
        rCubicTo(ctrlX1: number, ctrlY1: number, ctrlX2: number, ctrlY2: number, endX: number, endY: number): void;
        addPolygon(points: common2D.Point[], close: boolean): void;
        op(path: drawing.Path, pathOp: drawing.PathOp): boolean;
        addArc(rect: common2D.Rect, startAngle: number, sweepAngle: number): void;
        addCircle(x: number, y: number, radius: number, pathDirection: drawing.PathDirection): void;
        addOval(rect: common2D.Rect, start: number, pathDirection: drawing.PathDirection): void;
        addRect(rect: common2D.Rect, pathDirection: drawing.PathDirection): void;
        addRoundRect(roundRect: drawing.RoundRect, pathDirection: drawing.PathDirection): void;
        addPath(path: drawing.Path, matrix: drawing.Matrix | undefined): void;
        transform(matrix: drawing.Matrix): void;
        contains(x: number, y: number): boolean;
        setFillType(pathFillType: drawing.PathFillType): void;
        getBounds(): common2D.Rect;
        close(): void;
        offset(dx: number, dy: number): drawing.Path;
        reset(): void;
        getLength(forceClosed: boolean): number;
        getPositionAndTangent(forceClosed: boolean, distance: number, position: common2D.Point, tangent: common2D.Point): boolean;
        isClosed(): boolean;
        getMatrix(forceClosed: boolean, distance: number, matrix: drawing.Matrix, flags: drawing.PathMeasureMatrixFlags): boolean;
        buildFromSvgString(str: string): boolean;
    }
}
declare namespace drawing {
    enum PointMode {
        POINTS,
        LINES = 1,
        POLYGON = 2,
    }
}
declare namespace drawing {
    enum FilterMode {
        FILTER_MODE_NEAREST,
        FILTER_MODE_LINEAR = 1,
    }
}
declare namespace drawing {
    enum ShadowFlag {
        NONE,
        TRANSPARENT_OCCLUDER = 1,
        GEOMETRIC_ONLY = 2,
        ALL = 3,
    }
}
declare namespace drawing {
    class SamplingOptions {
        constructor();
        constructor(filterMode: drawing.FilterMode);
    }
}
declare namespace drawing {
    class Canvas {
        constructor(pixelmap: image.PixelMap);
        drawRect(rect: common2D.Rect): void;
        drawRect(left: number, top: number, right: number, bottom: number): void;
        drawRoundRect(roundRect: drawing.RoundRect): void;
        drawNestedRoundRect(outer: drawing.RoundRect, inner: drawing.RoundRect): void;
        drawBackground(brush: drawing.Brush): void;
        drawShadow(path: drawing.Path, planeParams: common2D.Point3d, devLightPos: common2D.Point3d, lightRadius: number, ambientColor: common2D.Color, spotColor: common2D.Color, flag: drawing.ShadowFlag): void;
        drawShadow(path: drawing.Path, planeParams: common2D.Point3d, devLightPos: common2D.Point3d, lightRadius: number, ambientColor: number, spotColor: number, flag: drawing.ShadowFlag): void;
        drawCircle(x: number, y: number, radius: number): void;
        drawImage(pixelmap: image.PixelMap, left: number, top: number, samplingOptions: drawing.SamplingOptions): void;
        drawImageRect(pixelmap: image.PixelMap, dstRect: common2D.Rect, samplingOptions: drawing.SamplingOptions): void;
        drawImageRectWithSrc(pixelmap: image.PixelMap, srcRect: common2D.Rect, dstRect: common2D.Rect, samplingOptions: drawing.SamplingOptions, constraint: drawing.SrcRectConstraint): void;
        drawColor(color: common2D.Color, blendMode: drawing.BlendMode): void;
        drawColor(color: number, blendMode: drawing.BlendMode): void;
        drawColor(alpha: number, red: number, green: number, blue: number, blendMode: drawing.BlendMode): void;
        drawOval(oval: common2D.Rect): void;
        drawArc(arc: common2D.Rect, startAngle: number, sweepAngle: number): void;
        drawPoint(x: number, y: number): void;
        drawPoints(points: common2D.Point[], mode: drawing.PointMode): void;
        drawPath(path: drawing.Path): void;
        drawLine(x0: number, y0: number, x1: number, y1: number): void;
        drawSingleCharacter(text: string, font: drawing.Font, x: number, y: number): void;
        drawTextBlob(blob: drawing.TextBlob, x: number, y: number): void;
        drawPixelMapMesh(pixelmap: image.PixelMap, meshWidth: number, meshHeight: number, vertices: number[], vertOffset: number, colors: number[], colorOffset: number): void;
        drawRegion(region: drawing.Region): void;
        attachPen(pen: drawing.Pen): void;
        attachBrush(brush: drawing.Brush): void;
        detachPen(): void;
        detachBrush(): void;
        save(): number;
        saveLayer(rect: common2D.Rect | undefined, brush: drawing.Brush | undefined): number;
        clear(color: common2D.Color): void;
        clear(color: number): void;
        restore(): void;
        restoreToCount(count: number): void;
        getSaveCount(): number;
        getWidth(): number;
        getHeight(): number;
        getLocalClipBounds(): common2D.Rect;
        getTotalMatrix(): drawing.Matrix;
        scale(sx: number, sy: number): void;
        skew(sx: number, sy: number): void;
        rotate(degrees: number, sx: number, sy: number): void;
        translate(dx: number, dy: number): void;
        clipPath(path: drawing.Path, clipOp: drawing.ClipOp, doAntiAlias: boolean): void;
        clipRect(rect: common2D.Rect, clipOp: drawing.ClipOp, doAntiAlias: boolean): void;
        concatMatrix(matrix: drawing.Matrix): void;
        clipRegion(region: drawing.Region, clipOp: drawing.ClipOp): void;
        clipRoundRect(roundRect: drawing.RoundRect, clipOp: drawing.ClipOp, doAntiAlias: boolean): void;
        isClipEmpty(): boolean;
        setMatrix(matrix: drawing.Matrix): void;
        resetMatrix(): void;
    }
}
declare namespace drawing {
    enum ClipOp {
        DIFFERENCE,
        INTERSECT = 1,
    }
}
declare namespace drawing {
    interface TextBlobRunBuffer {
        glyph: number;
        positionX: number;
        positionY: number;
    }
}
declare namespace drawing {
    enum TextEncoding {
        TEXT_ENCODING_UTF8,
        TEXT_ENCODING_UTF16 = 1,
        TEXT_ENCODING_UTF32 = 2,
        TEXT_ENCODING_GLYPH_ID = 3,
    }
}
declare namespace drawing {
    class TextBlob {
        constructor();
        static makeFromString(text: string, font: drawing.Font, encoding: drawing.TextEncoding): drawing.TextBlob;
        static makeFromPosText(text: string, len: number, points: common2D.Point[], font: drawing.Font): drawing.TextBlob;
        static makeFromRunBuffer(pos: drawing.TextBlobRunBuffer[], font: drawing.Font, bounds: common2D.Rect): drawing.TextBlob;
        bounds(): common2D.Rect;
        uniqueID(): number;
    }
}
declare namespace drawing {
    class Typeface {
        constructor();
        getFamilyName(): string;
        static makeFromFile(filePath: string): drawing.Typeface;
    }
}
declare namespace drawing {
    enum FontEdging {
        ALIAS,
        ANTI_ALIAS = 1,
        SUBPIXEL_ANTI_ALIAS = 2,
    }
}
declare namespace drawing {
    enum FontHinting {
        NONE,
        SLIGHT = 1,
        NORMAL = 2,
        FULL = 3,
    }
}
declare namespace drawing {
    class Font {
        constructor();
        enableSubpixel(isSubpixel: boolean): void;
        enableEmbolden(isEmbolden: boolean): void;
        enableLinearMetrics(isLinearMetrics: boolean): void;
        setSize(textSize: number): void;
        getSize(): number;
        setTypeface(typeface: drawing.Typeface): void;
        getTypeface(): drawing.Typeface;
        getMetrics(): drawing.FontMetrics;
        measureSingleCharacter(text: string): number;
        measureText(text: string, encoding: drawing.TextEncoding): number;
        setScaleX(scaleX: number): void;
        setSkewX(skewX: number): void;
        setEdging(edging: drawing.FontEdging): void;
        setHinting(hinting: drawing.FontHinting): void;
        countText(text: string): number;
        setBaselineSnap(isBaselineSnap: boolean): void;
        isBaselineSnap(): boolean;
        setEmbeddedBitmaps(isEmbeddedBitmaps: boolean): void;
        isEmbeddedBitmaps(): boolean;
        setForceAutoHinting(isForceAutoHinting: boolean): void;
        isForceAutoHinting(): boolean;
        getWidths(glyphs: number[]): number[];
        textToGlyphs(text: string, glyphCount: number): number[];
        isSubpixel(): boolean;
        isLinearMetrics(): boolean;
        getSkewX(): number;
        isEmbolden(): boolean;
        getScaleX(): number;
        getHinting(): drawing.FontHinting;
        getEdging(): drawing.FontEdging;
        createPathForGlyph(index: number): drawing.Path;
        getBounds(glyphs: number[]): common2D.Rect[];
        getTextPath(text: string, byteLength: number, x: number, y: number): drawing.Path;
    }
}
declare namespace drawing {
    enum FontMetricsFlags {
        UNDERLINE_THICKNESS_VALID,
        UNDERLINE_POSITION_VALID,
        STRIKETHROUGH_THICKNESS_VALID,
        STRIKETHROUGH_POSITION_VALID,
        BOUNDS_INVALID,
    }
}
declare namespace drawing {
    interface FontMetrics {
        flags?: drawing.FontMetricsFlags;
        top: number;
        ascent: number;
        descent: number;
        bottom: number;
        leading: number;
        avgCharWidth?: number;
        maxCharWidth?: number;
        xMin?: number;
        xMax?: number;
        xHeight?: number;
        capHeight?: number;
        underlineThickness?: number;
        underlinePosition?: number;
        strikethroughThickness?: number;
        strikethroughPosition?: number;
    }
}
declare namespace drawing {
    class Lattice {
        constructor();
        static createImageLattice<T>(xDivs: number[], yDivs: number[], fXCount: number, fYCount: number, fBounds: common2D.Rect | undefined, fRectTypes: drawing.RectType[] | undefined, fColors: T[] | undefined): drawing.Lattice;
    }
}
declare namespace drawing {
    enum RectType {
        DEFAULT,
        TRANSPARENT = 1,
        FIXEDCOLOR = 2,
    }
}
declare namespace drawing {
    class MaskFilter {
        constructor();
        static createBlurMaskFilter(blurType: drawing.BlurType, sigma: number): drawing.MaskFilter;
    }
}
declare namespace drawing {
    class PathEffect {
        constructor();
        static createDashPathEffect(intervals: number[], phase: number): drawing.PathEffect;
        static createCornerPathEffect(radius: number): drawing.PathEffect;
    }
}
declare namespace drawing {
    class ShaderEffect {
        constructor();
        static createColorShader(color: number): drawing.ShaderEffect;
        static createLinearGradient(startPt: common2D.Point, endPt: common2D.Point, colors: number[], mode: drawing.TileMode, pos: number[] | undefined, matrix: drawing.Matrix | undefined): drawing.ShaderEffect;
        static createRadialGradient(centerPt: common2D.Point, radius: number, colors: number[], mode: drawing.TileMode, pos: number[] | undefined, matrix: drawing.Matrix | undefined): drawing.ShaderEffect;
        static createSweepGradient(centerPt: common2D.Point, colors: number[], mode: drawing.TileMode, startAngle: number, endAngle: number, pos: number[] | undefined, matrix: drawing.Matrix | undefined): drawing.ShaderEffect;
        static createConicalGradient(startPt: common2D.Point, startRadius: number, endPt: common2D.Point, endRadius: number, colors: number[], mode: drawing.TileMode, pos: number[] | undefined, matrix: drawing.Matrix | undefined): drawing.ShaderEffect;
    }
}
declare namespace drawing {
    enum TileMode {
        CLAMP,
        REPEAT = 1,
        MIRROR = 2,
        DECAL = 3,
    }
}
declare namespace drawing {
    class ShadowLayer {
        constructor();
        static create(blurRadius: number, x: number, y: number, color: common2D.Color): drawing.ShadowLayer;
        static create(blurRadius: number, x: number, y: number, color: number): drawing.ShadowLayer;
    }
}
declare namespace drawing {
    class ColorFilter {
        constructor();
        static createBlendModeColorFilter(color: common2D.Color, mode: drawing.BlendMode): drawing.ColorFilter;
        static createBlendModeColorFilter(color: number, mode: drawing.BlendMode): drawing.ColorFilter;
        static createComposeColorFilter(outer: drawing.ColorFilter, inner: drawing.ColorFilter): drawing.ColorFilter;
        static createLinearToSRGBGamma(): drawing.ColorFilter;
        static createSRGBGammaToLinear(): drawing.ColorFilter;
        static createLumaColorFilter(): drawing.ColorFilter;
        static createMatrixColorFilter(matrix: number[]): drawing.ColorFilter;
    }
}
declare namespace drawing {
    class ImageFilter {
        constructor();
        static createBlurImageFilter(sigmaX: number, sigmaY: number, tileMode: drawing.TileMode, imageFilter: drawing.ImageFilter | undefined): drawing.ImageFilter;
        static createFromColorFilter(colorFilter: drawing.ColorFilter, imageFilter: drawing.ImageFilter | undefined): drawing.ImageFilter;
    }
}
declare namespace drawing {
    enum JoinStyle {
        MITER_JOIN,
        ROUND_JOIN = 1,
        BEVEL_JOIN = 2,
    }
}
declare namespace drawing {
    enum CapStyle {
        FLAT_CAP,
        SQUARE_CAP = 1,
        ROUND_CAP = 2,
    }
}
declare namespace drawing {
    enum BlurType {
        NORMAL,
        SOLID = 1,
        OUTER = 2,
        INNER = 3,
    }
}
declare namespace drawing {
    class Pen {
        constructor();
        constructor(pen: drawing.Pen);
        setMiterLimit(miter: number): void;
        getMiterLimit(): number;
        setShaderEffect(shaderEffect: drawing.ShaderEffect): void;
        setColor(color: common2D.Color): void;
        setColor(color: number): void;
        setColor(alpha: number, red: number, green: number, blue: number): void;
        getColor(): common2D.Color;
        getHexColor(): number;
        setStrokeWidth(width: number): void;
        getWidth(): number;
        setAntiAlias(aa: boolean): void;
        isAntiAlias(): boolean;
        setAlpha(alpha: number): void;
        getAlpha(): number;
        setColorFilter(filter: drawing.ColorFilter): void;
        getColorFilter(): drawing.ColorFilter;
        setImageFilter(filter: drawing.ImageFilter | undefined): void;
        setMaskFilter(filter: drawing.MaskFilter): void;
        setPathEffect(effect: drawing.PathEffect): void;
        setShadowLayer(shadowLayer: drawing.ShadowLayer): void;
        setBlendMode(mode: drawing.BlendMode): void;
        setDither(dither: boolean): void;
        setJoinStyle(style: drawing.JoinStyle): void;
        getJoinStyle(): drawing.JoinStyle;
        setCapStyle(style: drawing.CapStyle): void;
        getCapStyle(): drawing.CapStyle;
        reset(): void;
        getFillPath(src: drawing.Path, dst: drawing.Path): boolean;
    }
}
declare namespace drawing {
    class Brush {
        constructor();
        constructor(brush: drawing.Brush);
        setColor(color: common2D.Color): void;
        setColor(color: number): void;
        setColor(alpha: number, red: number, green: number, blue: number): void;
        getColor(): common2D.Color;
        getHexColor(): number;
        setAntiAlias(aa: boolean): void;
        isAntiAlias(): boolean;
        setAlpha(alpha: number): void;
        getAlpha(): number;
        setColorFilter(filter: drawing.ColorFilter): void;
        getColorFilter(): drawing.ColorFilter;
        setImageFilter(filter: drawing.ImageFilter | undefined): void;
        setMaskFilter(filter: drawing.MaskFilter): void;
        setShadowLayer(shadowLayer: drawing.ShadowLayer): void;
        setShaderEffect(shaderEffect: drawing.ShaderEffect): void;
        setBlendMode(mode: drawing.BlendMode): void;
        reset(): void;
    }
}
declare namespace drawing {
    class Matrix {
        constructor();
        setRotation(degree: number, px: number, py: number): void;
        setScale(sx: number, sy: number, px: number, py: number): void;
        setTranslation(dx: number, dy: number): void;
        setMatrix(values: number[]): void;
        preConcat(matrix: drawing.Matrix): void;
        isEqual(matrix: drawing.Matrix): boolean;
        invert(matrix: drawing.Matrix): boolean;
        isIdentity(): boolean;
        getValue(index: number): number;
        postRotate(degree: number, px: number, py: number): void;
        postScale(sx: number, sy: number, px: number, py: number): void;
        postTranslate(dx: number, dy: number): void;
        preRotate(degree: number, px: number, py: number): void;
        preScale(sx: number, sy: number, px: number, py: number): void;
        preTranslate(dx: number, dy: number): void;
        reset(): void;
        mapPoints(src: common2D.Point[]): common2D.Point[];
        getAll(): number[];
        mapRect(dst: common2D.Rect, src: common2D.Rect): boolean;
        setRectToRect(src: common2D.Rect, dst: common2D.Rect, scaleToFit: drawing.ScaleToFit): boolean;
        setPolyToPoly(src: common2D.Point[], dst: common2D.Point[], count: number): boolean;
    }
}
declare namespace drawing {
    enum ScaleToFit {
        FILL_SCALE_TO_FIT,
        START_SCALE_TO_FIT = 1,
        CENTER_SCALE_TO_FIT = 2,
        END_SCALE_TO_FIT = 3,
    }
}
declare namespace drawing {
    class Region {
        constructor();
        isPointContained(x: number, y: number): boolean;
        isRegionContained(other: drawing.Region): boolean;
        op(region: drawing.Region, regionOp: drawing.RegionOp): boolean;
        quickReject(left: number, top: number, right: number, bottom: number): boolean;
        setPath(path: drawing.Path, clip: drawing.Region): boolean;
        setRect(left: number, top: number, right: number, bottom: number): boolean;
    }
}
declare namespace drawing {
    enum RegionOp {
        DIFFERENCE,
        INTERSECT = 1,
        UNION = 2,
        XOR = 3,
        REVERSE_DIFFERENCE = 4,
        REPLACE = 5,
    }
}
declare namespace drawing {
    enum CornerPos {
        TOP_LEFT_POS,
        TOP_RIGHT_POS = 1,
        BOTTOM_RIGHT_POS = 2,
        BOTTOM_LEFT_POS = 3,
    }
}
declare namespace drawing {
    enum SrcRectConstraint {
        STRICT,
        FAST = 1,
    }
}
declare namespace text {
    enum TextAlign {
        LEFT,
        RIGHT = 1,
        CENTER = 2,
        JUSTIFY = 3,
        START = 4,
        END = 5,
    }
}
declare namespace text {
    enum TextDirection {
        RTL,
        LTR,
    }
}
declare namespace text {
    enum BreakStrategy {
        GREEDY,
        HIGH_QUALITY,
        BALANCED,
    }
}
declare namespace text {
    enum WordBreak {
        NORMAL,
        BREAK_ALL,
        BREAK_WORD,
    }
}
declare namespace text {
    interface Decoration {
        textDecoration?: text.TextDecorationType;
        color?: common2D.Color;
        decorationStyle?: text.TextDecorationStyle;
        decorationThicknessScale?: number;
    }
}
declare namespace text {
    enum TextDecorationType {
        NONE,
        UNDERLINE,
        OVERLINE,
        LINE_THROUGH,
    }
}
declare namespace text {
    enum TextDecorationStyle {
        SOLID,
        DOUBLE,
        DOTTED,
        DASHED,
        WAVY,
    }
}
declare namespace text {
    enum FontWeight {
        W100,
        W200,
        W300,
        W400,
        W500,
        W600,
        W700,
        W800,
        W900,
    }
}
declare namespace text {
    enum FontStyle {
        NORMAL,
        ITALIC,
        OBLIQUE,
    }
}
declare namespace text {
    enum FontWidth {
        ULTRA_CONDENSED = 1,
        EXTRA_CONDENSED = 2,
        CONDENSED = 3,
        SEMI_CONDENSED = 4,
        NORMAL = 5,
        SEMI_EXPANDED = 6,
        EXPANDED = 7,
        EXTRA_EXPANDED = 8,
        ULTRA_EXPANDED = 9,
    }
}
declare namespace text {
    enum TextHeightBehavior {
        ALL,
        DISABLE_FIRST_ASCENT,
        DISABLE_LAST_ASCENT,
        DISABLE_ALL,
    }
}
declare namespace text {
    enum TextBaseline {
        ALPHABETIC,
        IDEOGRAPHIC,
    }
}
declare namespace text {
    enum EllipsisMode {
        START,
        MIDDLE,
        END,
    }
}
declare namespace text {
    interface TextShadow {
        color?: common2D.Color;
        point?: common2D.Point;
        blurRadius?: number;
    }
}
declare namespace text {
    interface RectStyle {
        color: common2D.Color;
        leftTopRadius: number;
        rightTopRadius: number;
        rightBottomRadius: number;
        leftBottomRadius: number;
    }
}
declare namespace text {
    interface FontFeature {
        name: string;
        value: number;
    }
}
declare namespace text {
    interface FontVariation {
        axis: string;
        value: number;
    }
}
declare namespace text {
    interface TextStyle {
        decoration?: text.Decoration;
        color?: common2D.Color;
        fontWeight?: text.FontWeight;
        fontStyle?: text.FontStyle;
        baseline?: text.TextBaseline;
        fontFamilies?: string[];
        fontSize?: number;
        letterSpacing?: number;
        wordSpacing?: number;
        heightScale?: number;
        halfLeading?: boolean;
        heightOnly?: boolean;
        ellipsis?: string;
        ellipsisMode?: text.EllipsisMode;
        locale?: string;
        baselineShift?: number;
        fontFeatures?: text.FontFeature[];
        textShadows?: text.TextShadow[];
        backgroundRect?: text.RectStyle;
        fontVariations?: text.FontVariation[];
    }
}
declare namespace text {
    class FontCollection {
        constructor();
        static getGlobalInstance(): text.FontCollection;
        loadFontSync(name: string, path: (string|Resource)): void;
        loadFont(name: string, path: (string|Resource)): Promise<void>;
        clearCaches(): void;
    }
}
declare namespace text {
    interface StrutStyle {
        fontFamilies?: string[];
        fontStyle?: text.FontStyle;
        fontWidth?: text.FontWidth;
        fontWeight?: text.FontWeight;
        fontSize?: number;
        height?: number;
        leading?: number;
        forceHeight?: boolean;
        enabled?: boolean;
        heightOverride?: boolean;
        halfLeading?: boolean;
    }
}
declare namespace text {
    interface ParagraphStyle {
        textStyle?: text.TextStyle;
        textDirection?: text.TextDirection;
        align?: text.TextAlign;
        wordBreak?: text.WordBreak;
        maxLines?: number;
        breakStrategy?: text.BreakStrategy;
        strutStyle?: text.StrutStyle;
        textHeightBehavior?: text.TextHeightBehavior;
        tab?: text.TextTab;
    }
}
declare namespace text {
    enum PlaceholderAlignment {
        OFFSET_AT_BASELINE,
        ABOVE_BASELINE,
        BELOW_BASELINE,
        TOP_OF_ROW_BOX,
        BOTTOM_OF_ROW_BOX,
        CENTER_OF_ROW_BOX,
    }
}
declare namespace text {
    interface PlaceholderSpan {
        width: number;
        height: number;
        align: text.PlaceholderAlignment;
        baseline: text.TextBaseline;
        baselineOffset: number;
    }
}
declare namespace text {
    interface Range {
        start: number;
        end: number;
    }
}
declare namespace text {
    enum SystemFontType {
        ALL,
        GENERIC,
        STYLISH,
        INSTALLED,
    }
}
declare namespace text {
    interface FontDescriptor {
        path?: string;
        postScriptName?: string;
        fullName?: string;
        fontFamily?: string;
        fontSubfamily?: string;
        weight?: text.FontWeight;
        width?: number;
        italic?: number;
        monoSpace?: boolean;
        symbolic?: boolean;
    }
}
declare namespace text {
    class Paragraph {
        constructor();
        layoutSync(width: number): void;
        layout(width: number): Promise<void>;
        paint(canvas: drawing.Canvas, x: number, y: number): void;
        paintOnPath(canvas: drawing.Canvas, path: drawing.Path, hOffset: number, vOffset: number): void;
        getMaxWidth(): number;
        getHeight(): number;
        getLongestLine(): number;
        getLongestLineWithIndent(): number;
        getMinIntrinsicWidth(): number;
        getMaxIntrinsicWidth(): number;
        getAlphabeticBaseline(): number;
        getIdeographicBaseline(): number;
        getRectsForRange(range: text.Range, widthStyle: text.RectWidthStyle, heightStyle: text.RectHeightStyle): text.TextBox[];
        getRectsForPlaceholders(): text.TextBox[];
        getGlyphPositionAtCoordinate(x: number, y: number): text.PositionWithAffinity;
        getWordBoundary(offset: number): text.Range;
        getLineCount(): number;
        getLineHeight(line: number): number;
        getLineWidth(line: number): number;
        didExceedMaxLines(): boolean;
        getTextLines(): text.TextLine[];
        getActualTextRange(lineNumber: number, includeSpaces: boolean): text.Range;
        getLineMetrics(): text.LineMetrics[];
        getLineMetrics(lineNumber: number): text.LineMetrics | undefined;
    }
}
declare namespace text {
    class LineTypeset {
        constructor();
        getLineBreak(startIndex: number, width: number): number;
        createLine(startIndex: number, count: number): text.TextLine;
    }
}
declare namespace text {
    interface TextBox {
        rect: common2D.Rect;
        direction: text.TextDirection;
    }
}
declare namespace text {
    interface PositionWithAffinity {
        position: number;
        affinity: text.Affinity;
    }
}
declare namespace text {
    enum RectWidthStyle {
        TIGHT,
        MAX,
    }
}
declare namespace text {
    enum RectHeightStyle {
        TIGHT,
        MAX,
        INCLUDE_LINE_SPACE_MIDDLE,
        INCLUDE_LINE_SPACE_TOP,
        INCLUDE_LINE_SPACE_BOTTOM,
        STRUT,
    }
}
declare namespace text {
    enum Affinity {
        UPSTREAM,
        DOWNSTREAM,
    }
}
declare namespace text {
    class ParagraphBuilder {
        constructor(paragraphStyle: text.ParagraphStyle, fontCollection: text.FontCollection);
        pushStyle(textStyle: text.TextStyle): void;
        popStyle(): void;
        addText(text: string): void;
        addPlaceholder(placeholderSpan: text.PlaceholderSpan): void;
        build(): text.Paragraph;
        buildLineTypeset(): text.LineTypeset;
        addSymbol(symbolId: number): void;
    }
}
declare namespace text {
    interface TypographicBounds {
        ascent: number;
        descent: number;
        leading: number;
        width: number;
    }
}
declare namespace text {
    type Callback_Number_Number_Boolean_Boolean = ((offset: number, index: number, leadingEdge: boolean) => boolean);
}
declare namespace text {
    type CaretOffsetsCallback = ((offset: number, index: number, leadingEdge: boolean) => boolean);
}
declare namespace text {
    class TextLine {
        constructor();
        getGlyphCount(): number;
        getTextRange(): text.Range;
        getGlyphRuns(): text.Run[];
        paint(canvas: drawing.Canvas, x: number, y: number): void;
        createTruncatedLine(width: number, ellipsisMode: text.EllipsisMode, ellipsis: string): text.TextLine;
        getTypographicBounds(): text.TypographicBounds;
        getImageBounds(): common2D.Rect;
        getTrailingSpaceWidth(): number;
        getStringIndexForPosition(point: common2D.Point): number;
        getOffsetForStringIndex(index: number): number;
        enumerateCaretOffsets(callback_: text.CaretOffsetsCallback): void;
        getAlignmentOffset(alignmentFactor: number, alignmentWidth: number): number;
    }
}
declare namespace text {
    class Run {
        constructor();
        getGlyphCount(): number;
        getGlyphs(): number[];
        getGlyphs(range: text.Range): number[];
        getPositions(): common2D.Point[];
        getPositions(range: text.Range): common2D.Point[];
        getOffsets(): common2D.Point[];
        getFont(): drawing.Font;
        paint(canvas: drawing.Canvas, x: number, y: number): void;
        getStringIndices(range: text.Range): number[];
        getStringRange(): text.Range;
        getTypographicBounds(): text.TypographicBounds;
        getImageBounds(): common2D.Rect;
    }
}
declare namespace text {
    interface RunMetrics {
        textStyle: text.TextStyle;
        fontMetrics: drawing.FontMetrics;
    }
}
declare namespace text {
    interface LineMetrics {
        startIndex: number;
        endIndex: number;
        ascent: number;
        descent: number;
        height: number;
        width: number;
        left: number;
        baseline: number;
        lineNumber: number;
        topHeight: number;
        runMetrics: Map<number,text.RunMetrics>;
    }
}
declare namespace text {
    function getSystemFontFullNamesByType(fontType: text.SystemFontType): Promise<string[]>;
}
declare namespace text {
    function getFontDescriptorByFullName(fullName: string, fontType: text.SystemFontType): Promise<text.FontDescriptor>;
}
declare namespace text {
    function matchFontDescriptors(desc: text.FontDescriptor): Promise<text.FontDescriptor[]>;
}
declare namespace text {
    interface TextTab {
        alignment: text.TextAlign;
        location: number;
    }
}
declare namespace uiEffect {
    interface Filter {
    }
}
declare namespace uiEffect {
    interface VisualEffect {
        backgroundColorBlender(blender: uiEffect.BrightnessBlender): uiEffect.VisualEffect;
    }
}
declare namespace uiEffect {
    type Blender = uiEffect.BrightnessBlender;
}
declare namespace uiEffect {
    type Tuple_Number_Number_Number = [ number, number, number ]
}
declare namespace uiEffect {
    interface BrightnessBlender {
        cubicRate: number;
        quadraticRate: number;
        linearRate: number;
        degree: number;
        saturation: number;
        positiveCoefficient: [ number, number, number ];
        negativeCoefficient: [ number, number, number ];
        fraction: number;
    }
}
declare namespace uiEffect {
    function createEffect(): uiEffect.VisualEffect;
}
declare namespace uiEffect {
    function createBrightnessBlender(param: uiEffect.BrightnessBlenderParam): uiEffect.BrightnessBlender;
}
declare namespace uiEffect {
    interface BrightnessBlenderParam {
        cubicRate: number;
        quadraticRate: number;
        linearRate: number;
        degree: number;
        saturation: number;
        positiveCoefficient: [ number, number, number ];
        negativeCoefficient: [ number, number, number ];
        fraction: number;
    }
}
declare namespace intl {
    interface DateTimeOptions {
        locale?: string;
        dateStyle?: string;
        timeStyle?: string;
        hourCycle?: string;
        timeZone?: string;
        numberingSystem?: string;
        hour12?: boolean;
        weekday?: string;
        era?: string;
        year?: string;
        month?: string;
        day?: string;
        hour?: string;
        minute?: string;
        second?: string;
        timeZoneName?: string;
        dayPeriod?: string;
        localeMatcher?: string;
        formatMatcher?: string;
    }
}
declare namespace matrix4 {
    type Matrix4TransformPoint = [ number, number ]
}
declare namespace matrix4 {
    interface PolyToPolyOptions {
        src: common2D.Point[];
        srcIndex?: number;
        dst: common2D.Point[];
        dstIndex?: number;
        pointCount?: number;
    }
}
declare namespace matrix4 {
    interface Matrix4Transit {
        copy(): matrix4.Matrix4Transit;
        invert(): matrix4.Matrix4Transit;
        combine(options: matrix4.Matrix4Transit): matrix4.Matrix4Transit;
        translate(options: TranslateOptions): matrix4.Matrix4Transit;
        scale(options: ScaleOptions): matrix4.Matrix4Transit;
        skew(x: number, y: number): matrix4.Matrix4Transit;
        rotate(options: RotateOptions): matrix4.Matrix4Transit;
        transformPoint(options: [ number, number ]): [ number, number ];
        setPolyToPoly(options: matrix4.PolyToPolyOptions): matrix4.Matrix4Transit;
    }
}
declare namespace image {
    interface PixelMap {
        readonly isEditable: boolean;
        readonly isStrideAlignment: boolean;
        readPixelsToBufferSync(dst: ArrayBuffer): void;
        writeBufferToPixels(src: ArrayBuffer): void;
    }
}
declare namespace image {
    enum ResolutionQuality {
        LOW = 1,
        MEDIUM = 2,
        HIGH = 3,
    }
}
declare enum IntentionCode {
    INTENTION_UNKNOWN = -1,
    INTENTION_UP = 1,
    INTENTION_DOWN = 2,
    INTENTION_LEFT = 3,
    INTENTION_RIGHT = 4,
    INTENTION_SELECT = 5,
    INTENTION_ESCAPE = 6,
    INTENTION_BACK = 7,
    INTENTION_FORWARD = 8,
    INTENTION_MENU = 9,
    INTENTION_PAGE_UP = 11,
    INTENTION_PAGE_DOWN = 12,
    INTENTION_ZOOM_OUT = 13,
    INTENTION_ZOOM_IN = 14,
}
declare namespace pointer {
    enum PointerStyle {
        DEFAULT,
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
}
declare enum LevelMode {
    A,
}
declare enum ImmersiveMode {
    A,
}
declare interface LevelOrder {
}
declare namespace promptAction {
    interface DialogController {
    }
}
declare namespace window {
    enum WindowStatusType {
        UNDEFINED,
        FULL_SCREEN = 1,
        MAXIMIZE = 2,
        MINIMIZE = 3,
        FLOATING = 4,
        SPLIT_SCREEN = 5,
    }
}
declare namespace window {
    interface SystemBarStyle {
        statusBarContentColor?: string;
    }
}
declare enum RouteType {
    NONE,
    None,
    PUSH = 1,
    Push = 1,
    POP = 2,
    Pop = 2,
}
declare enum SlideEffect {
    LEFT,
    Left,
    RIGHT = 1,
    Right = 1,
    TOP = 2,
    Top = 2,
    BOTTOM = 3,
    Bottom = 3,
    START = 5,
    END = 6,
}
declare interface PageTransitionOptions {
    type?: RouteType;
    duration?: number;
    curve?: (Curve|string|ICurve);
    delay?: number;
}
declare type PageTransitionCallback = ((type: RouteType, progress: number) => void);
declare interface VelocityOptions {
    speed: [ number, number ];
    angle: [ number, number ];
}
declare interface PointParticleParameters {
    radius: VP;
}
declare interface ImageParticleParameters {
    src: ResourceStr;
    size: [ Dimension, Dimension ];
    objectFit?: ImageFit;
}
declare type ParticleConfigs = (PointParticleParameters|ImageParticleParameters);
declare interface EmitterProperty {
    _stub: number;
}
declare interface EmitterParticleOptions {
    type: ParticleType;
    config: ParticleConfigs;
    count: number;
    lifetime?: number;
    lifetimeRange?: number;
}
declare type ParticlePropertyUpdaterConfigs = ([ number, number ]|ParticlePropertyAnimation<number>[]) | undefined;
declare interface ParticleUpdaterOptions {
    type: ParticleUpdater;
    config: ParticlePropertyUpdaterConfigs;
}
declare interface ParticleColorOptions {
    r: [ number, number ];
    g: [ number, number ];
    b: [ number, number ];
    a: [ number, number ];
}
declare interface ParticleColorUpdaterOptions {
    type: ParticleUpdater;
    config: ParticleColorPropertyUpdaterConfigs;
}
declare type ParticleColorPropertyUpdaterConfigs = (ParticleColorOptions|ParticlePropertyAnimation<ResourceColor>[]) | undefined;
declare interface ParticlePropertyAnimation<T> {
    from: T;
    to: T;
    startMillis: number;
    endMillis: number;
    curve?: (Curve|ICurve);
}
declare enum ParticleType {
    POINT = "'point'",
    IMAGE = "'image'",
}
declare enum ParticleEmitterShape {
    RECTANGLE = "'rectangle'",
    CIRCLE = "'circle'",
    ELLIPSE = "'ellipse'",
    ANNULUS = "'annulus'",
}
declare enum DistributionType {
    UNIFORM,
    GAUSSIAN = 1,
}
declare enum ParticleUpdater {
    NONE = "'none'",
    RANDOM = "'random'",
    CURVE = "'curve'",
}
declare enum DisturbanceFieldShape {
    RECT,
    CIRCLE = 1,
    ELLIPSE = 2,
}
declare interface ParticleAnnulusRegion {
    center?: Vector2T<LengthMetrics>;
    outerRadius: LengthMetrics;
    innerRadius: LengthMetrics;
    startAngle?: number;
    endAngle?: number;
}
declare enum PasteIconStyle {
    LINES,
}
declare enum PasteDescription {
    PASTE,
}
declare interface PasteButtonOptions {
    icon?: PasteIconStyle;
    text?: PasteDescription;
    buttonType?: ButtonType;
}
declare enum PasteButtonOnClickResult {
    SUCCESS,
    TEMPORARY_AUTHORIZATION_FAILED = 1,
}
declare type PasteButtonCallback = ((event: ClickEvent, result: PasteButtonOnClickResult, error?: BusinessError) => void);
declare interface PasteButtonAttribute extends SecurityComponentMethod {
    onClick(value: PasteButtonCallback | undefined): PasteButtonAttribute;
    attributeModifier(value: (AttributeModifier<PasteButtonAttribute>|AttributeModifier<CommonMethod>) | undefined): PasteButtonAttribute;
}
declare interface PasteButtonInterface {
    (): PasteButtonAttribute;
    (options: PasteButtonOptions): PasteButtonAttribute;
}
declare interface PathOptions {
    width?: (number|string);
    height?: (number|string);
    commands?: string;
}
declare interface PathAttribute extends CommonShapeMethod {
    commands(value: string | undefined): PathAttribute;
    attributeModifier(value: (AttributeModifier<PathAttribute>|AttributeModifier<CommonMethod>) | undefined): PathAttribute;
}
declare interface PathInterface {
    (options?: PathOptions): PathAttribute;
}
declare enum PatternLockChallengeResult {
    CORRECT = 1,
    WRONG = 2,
}
declare interface CircleStyleOptions {
    color?: ResourceColor;
    radius?: LengthMetrics;
    enableWaveEffect?: boolean;
    enableForeground?: boolean;
}
declare class PatternLockController {
    constructor();
    reset(): void;
    setChallengeResult(result: PatternLockChallengeResult): void;
}
declare type Callback_Array_Number_Void = ((input: number[]) => void);
declare interface PatternLockAttribute extends CommonMethod {
    sideLength(value: Length | undefined): PatternLockAttribute;
    circleRadius(value: Length | undefined): PatternLockAttribute;
    backgroundColor(value: ResourceColor | undefined): PatternLockAttribute;
    regularColor(value: ResourceColor | undefined): PatternLockAttribute;
    selectedColor(value: ResourceColor | undefined): PatternLockAttribute;
    activeColor(value: ResourceColor | undefined): PatternLockAttribute;
    pathColor(value: ResourceColor | undefined): PatternLockAttribute;
    pathStrokeWidth(value: (number|string) | undefined): PatternLockAttribute;
    onPatternComplete(value: ((input: number[]) => void) | undefined): PatternLockAttribute;
    autoReset(value: boolean | undefined): PatternLockAttribute;
    onDotConnect(value: ((value0: number) => void) | undefined): PatternLockAttribute;
    activateCircleStyle(value: CircleStyleOptions | undefined): PatternLockAttribute;
    skipUnselectedPoint(value: boolean | undefined): PatternLockAttribute;
    attributeModifier(value: (AttributeModifier<PatternLockAttribute>|AttributeModifier<CommonMethod>) | undefined): PatternLockAttribute;
}
declare interface PatternLockInterface {
    (controller?: PatternLockController): PatternLockAttribute;
}
declare interface PluginComponentTemplate {
    source: string;
    bundleName: string;
}
declare interface PluginComponentOptions {
    template: PluginComponentTemplate;
    data: Object | undefined;
}
declare interface PluginErrorData {
    errcode: number;
    msg: string;
}
declare type PluginErrorCallback = ((info: PluginErrorData) => void);
declare interface PluginComponentAttribute extends CommonMethod {
    onComplete(value: VoidCallback | undefined): PluginComponentAttribute;
    onError(value: PluginErrorCallback | undefined): PluginComponentAttribute;
    attributeModifier(value: (AttributeModifier<PluginComponentAttribute>|AttributeModifier<CommonMethod>) | undefined): PluginComponentAttribute;
}
declare interface PluginComponentInterface {
    (options: PluginComponentOptions): PluginComponentAttribute;
}
declare interface PolygonOptions {
    width?: (string|number);
    height?: (string|number);
}
declare interface PolygonAttribute extends CommonShapeMethod {
    points(value: ShapePoint[] | undefined): PolygonAttribute;
    attributeModifier(value: (AttributeModifier<PolygonAttribute>|AttributeModifier<CommonMethod>) | undefined): PolygonAttribute;
}
declare interface PolygonInterface {
    (options?: PolygonOptions): PolygonAttribute;
}
declare interface PolylineOptions {
    width?: (string|number);
    height?: (string|number);
}
declare interface PolylineAttribute extends CommonShapeMethod {
    points(value: ShapePoint[] | undefined): PolylineAttribute;
    attributeModifier(value: (AttributeModifier<PolylineAttribute>|AttributeModifier<CommonMethod>) | undefined): PolylineAttribute;
}
declare interface PolylineInterface {
    (options?: PolylineOptions): PolylineAttribute;
}
declare interface ProgressOptions {
    value: number;
    total?: number;
    type?: ProgressType;
}
declare enum ProgressType {
    LINEAR,
    Linear,
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
    LOADING,
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
    borderRadius?: LengthMetrics;
}
declare enum ProgressStyle {
    LINEAR,
    Linear,
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
declare interface ProgressAttribute extends CommonMethod {
    value(value: number | undefined): ProgressAttribute;
    color(value: (ResourceColor|LinearGradient) | undefined): ProgressAttribute;
    style(value: (LinearStyleOptions|RingStyleOptions|CapsuleStyleOptions|ProgressStyleOptions) | undefined): ProgressAttribute;
    privacySensitive(value: boolean | undefined): ProgressAttribute;
    contentModifier(value: ContentModifier<ProgressConfiguration> | undefined): ProgressAttribute;
    attributeModifier(value: (AttributeModifier<ProgressAttribute>|AttributeModifier<CommonMethod>) | undefined): ProgressAttribute;
}
declare interface ProgressConfiguration extends CommonConfiguration<ProgressConfiguration> {
    value: number;
    total: number;
}
declare interface ProgressInterface {
    (options: ProgressOptions): ProgressAttribute;
}
declare interface QRCodeAttribute extends CommonMethod {
    color(value: ResourceColor | undefined): QRCodeAttribute;
    backgroundColor(value: ResourceColor | undefined): QRCodeAttribute;
    contentOpacity(value: (number|Resource) | undefined): QRCodeAttribute;
    attributeModifier(value: (AttributeModifier<QRCodeAttribute>|AttributeModifier<CommonMethod>) | undefined): QRCodeAttribute;
}
declare interface QRCodeInterface {
    (value: ResourceStr): QRCodeAttribute;
}
declare enum RadioIndicatorType {
    TICK,
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
declare type OnRadioChangeCallback = ((isChecked: boolean) => void);
declare interface RadioAttribute extends CommonMethod {
    checked(value: boolean | undefined): RadioAttribute;
    onChange(value: OnRadioChangeCallback | undefined): RadioAttribute;
    radioStyle(value: RadioStyle | undefined): RadioAttribute;
    contentModifier(value: ContentModifier<RadioConfiguration> | undefined): RadioAttribute;
    attributeModifier(value: (AttributeModifier<RadioAttribute>|AttributeModifier<CommonMethod>) | undefined): RadioAttribute;
}
declare interface RadioConfiguration extends CommonConfiguration<RadioConfiguration> {
    value: string;
    checked: boolean;
    triggerChange: ((value0: boolean) => void);
}
declare interface RadioInterface {
    (options: RadioOptions): RadioAttribute;
}
declare interface RatingOptions {
    rating: number | undefined;
    indicator?: boolean;
}
declare interface StarStyleOptions {
    backgroundUri: ResourceStr;
    foregroundUri: ResourceStr;
    secondaryUri?: ResourceStr;
}
declare interface RatingConfiguration extends CommonConfiguration<RatingConfiguration> {
    rating: number;
    indicator: boolean;
    stars: number;
    stepSize: number;
    triggerChange: ((value0: number) => void);
}
declare type OnRatingChangeCallback = ((rating: number) => void);
declare interface RatingAttribute extends CommonMethod {
    stars(value: number | undefined): RatingAttribute;
    stepSize(value: number | undefined): RatingAttribute;
    starStyle(value: StarStyleOptions | undefined): RatingAttribute;
    onChange(value: OnRatingChangeCallback | undefined): RatingAttribute;
    contentModifier(value: ContentModifier<RatingConfiguration> | undefined): RatingAttribute;
    attributeModifier(value: (AttributeModifier<RatingAttribute>|AttributeModifier<CommonMethod>) | undefined): RatingAttribute;
}
declare interface RatingInterface {
    (options?: RatingOptions): RatingAttribute;
}
declare type RadiusItem = [ Length, Length ]
declare interface RectOptions {
    width?: Length;
    height?: Length;
    radius?: (Length|RadiusItem[]);
}
declare interface RoundedRectOptions {
    width?: (number|string);
    height?: (number|string);
    radiusWidth?: (number|string);
    radiusHeight?: (number|string);
}
declare interface RectAttribute extends CommonShapeMethod {
    radiusWidth(value: (number|string) | undefined): RectAttribute;
    radiusHeight(value: (number|string) | undefined): RectAttribute;
    radius(value: (number|string|(number|string)[]) | undefined): RectAttribute;
    attributeModifier(value: (AttributeModifier<RectAttribute>|AttributeModifier<CommonMethod>) | undefined): RectAttribute;
}
declare interface RectInterface {
    (options?: (RectOptions|RoundedRectOptions)): RectAttribute;
}
declare enum RefreshStatus {
    INACTIVE,
    Inactive,
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
    promptText?: ResourceStr;
    builder?: CustomBuilder;
    refreshingContent?: ComponentContent;
}
declare type Callback_RefreshStatus_Void = ((state: RefreshStatus) => void);
declare interface RefreshAttribute extends CommonMethod {
    onStateChange(value: ((state: RefreshStatus) => void) | undefined): RefreshAttribute;
    onRefreshing(value: (() => void) | undefined): RefreshAttribute;
    refreshOffset(value: number | undefined): RefreshAttribute;
    pullToRefresh(value: boolean | undefined): RefreshAttribute;
    onOffsetChange(value: ((value0: number) => void) | undefined): RefreshAttribute;
    pullDownRatio(value: number | undefined): RefreshAttribute;
    attributeModifier(value: (AttributeModifier<RefreshAttribute>|AttributeModifier<CommonMethod>) | undefined): RefreshAttribute;
}
declare interface RefreshInterface {
    (value: RefreshOptions): RefreshAttribute;
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
    LEFT,
    RIGHT = 1,
    TOP = 2,
    BOTTOM = 3,
}
declare enum LocalizedBarrierDirection {
    START,
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
declare interface RelativeContainerAttribute extends CommonMethod {
    guideLine(value: GuideLineStyle[] | undefined): RelativeContainerAttribute;
    barrier(value: BarrierStyle[] | undefined): RelativeContainerAttribute;
    barrier(value: LocalizedBarrierStyle[] | undefined): RelativeContainerAttribute;
    attributeModifier(value: (AttributeModifier<RelativeContainerAttribute>|AttributeModifier<CommonMethod>) | undefined): RelativeContainerAttribute;
}
declare interface RelativeContainerInterface {
    (): RelativeContainerAttribute;
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
declare interface RemoteWindowAttribute extends CommonMethod {
    attributeModifier(value: (AttributeModifier<RemoteWindowAttribute>|AttributeModifier<CommonMethod>) | undefined): RemoteWindowAttribute;
}
declare interface RemoteWindowInterface {
    (target: WindowAnimationTarget): RemoteWindowAttribute;
}
declare type RepeatArray<T> = T[];
declare type Callback_Number = (() => number);
declare interface VirtualScrollOptions {
    totalCount?: number;
    reusable?: boolean;
    onLazyLoading?: ((index: number) => void);
    onTotalCount?: (() => number);
}
declare interface TemplateOptions {
    cachedCount?: number;
}
declare interface Resource {
    bundleName: string;
    moduleName: string;
    id: number;
    params?: string[];
    type?: number;
}
declare enum RichEditorDeleteDirection {
    BACKWARD,
    FORWARD = 1,
}
declare enum RichEditorSpanType {
    TEXT,
    IMAGE = 1,
    MIXED = 2,
    BUILDER = 3,
    DEFAULT = 4,
}
declare enum RichEditorResponseType {
    RIGHT_CLICK,
    LONG_PRESS = 1,
    SELECT = 2,
    DEFAULT = 3,
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
    halfLeading?: boolean;
    fontFeature?: string;
    textBackgroundStyle?: TextBackgroundStyle;
}
declare interface LeadingMarginPlaceholder {
    pixelMap: image.PixelMap;
    size: [ Dimension, Dimension ];
}
declare interface RichEditorParagraphStyle {
    textAlign?: TextAlign;
    leadingMargin?: (Dimension|LeadingMarginPlaceholder);
    wordBreak?: WordBreak;
    lineBreakStrategy?: LineBreakStrategy;
    paragraphSpacing?: number;
}
declare interface PasteEvent {
    preventDefault?: VoidCallback;
}
declare interface RichEditorTextSpan {
    spanPosition: RichEditorSpanPosition;
    value: string;
    textStyle?: RichEditorTextStyle;
}
declare interface RichEditorLayoutStyle {
    margin?: (Dimension|Padding);
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
    halfLeading?: boolean;
    fontFeature?: string;
    textBackgroundStyle?: TextBackgroundStyle;
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
    urlStyle?: RichEditorUrlStyle;
}
declare interface RichEditorImageSpanStyleResult {
    size: [ number, number ];
    verticalAlign: ImageSpanAlignment;
    objectFit: ImageFit;
    layoutStyle?: RichEditorLayoutStyle;
}
declare interface RichEditorImageSpanResult {
    spanPosition: RichEditorSpanPosition;
    valuePixelMap?: image.PixelMap;
    valueResourceStr?: ResourceStr;
    imageStyle: RichEditorImageSpanStyleResult;
    offsetInSpan: [ number, number ];
}
declare interface RichEditorImageSpan {
    spanPosition: RichEditorSpanPosition;
    value: (image.PixelMap|ResourceStr);
    imageStyle?: RichEditorImageSpanStyle;
}
declare interface RichEditorRange {
    start?: number;
    end?: number;
}
declare interface RichEditorGesture {
    onClick?: ((value0: ClickEvent) => void);
    onLongPress?: ((value0: GestureEvent) => void);
    onDoubleClick?: ((value0: GestureEvent) => void);
}
declare interface RichEditorTextSpanOptions {
    offset?: number;
    style?: RichEditorTextStyle;
    paragraphStyle?: RichEditorParagraphStyle;
    gesture?: RichEditorGesture;
    urlStyle?: RichEditorUrlStyle;
}
declare interface KeyboardOptions {
    supportAvoidance?: boolean;
}
declare interface RichEditorImageSpanOptions {
    offset?: number;
    imageStyle?: RichEditorImageSpanStyle;
    gesture?: RichEditorGesture;
    onHover?: OnHoverCallback;
}
declare interface RichEditorBuilderSpanOptions {
    offset?: number;
    dragBackgroundColor?: ColorMetrics;
    isDragShadowNeeded?: boolean;
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
    urlStyle?: RichEditorUrlStyle;
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
    onDisappear?: VoidCallback;
    menuType?: MenuType;
    onMenuShow?: MenuCallback;
    onMenuHide?: MenuCallback;
    previewMenuOptions?: PreviewMenuOptions;
}
declare interface PreviewMenuOptions {
    hapticFeedbackMode?: HapticFeedbackMode;
}
declare class RichEditorBaseController {
    constructor();
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
    getCaretRect(): RectResult | undefined;
}
declare class RichEditorController extends RichEditorBaseController {
    constructor();
    addTextSpan(value: string, options?: RichEditorTextSpanOptions): number;
    addImageSpan(value: (image.PixelMap|ResourceStr), options?: RichEditorImageSpanOptions): number;
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
    constructor();
    setStyledString(styledString: StyledString): void;
    getStyledString(): MutableStyledString;
    getSelection(): RichEditorRange;
    onContentChanged(listener: StyledStringChangedListener): void;
}
declare type Callback_RichEditorSelection_Void = ((value0: RichEditorSelection) => void);
declare type Callback_RichEditorRange_Void = ((value0: RichEditorRange) => void);
declare type Callback_RichEditorInsertValue_Boolean = ((value0: RichEditorInsertValue) => boolean);
declare type Callback_RichEditorTextSpanResult_Void = ((value0: RichEditorTextSpanResult) => void);
declare type Callback_TextRange_Void = ((value0: TextRange) => void);
declare type Callback_RichEditorDeleteValue_Boolean = ((value0: RichEditorDeleteValue) => boolean);
declare type Callback_RichEditorChangeValue_Boolean = ((value0: RichEditorChangeValue) => boolean);
declare type Callback_CutEvent_Void = ((value0: CutEvent) => void);
declare type Callback_CopyEvent_Void = ((value0: CopyEvent) => void);
declare interface RichEditorAttribute extends CommonMethod {
    onReady(value: VoidCallback | undefined): RichEditorAttribute;
    onSelect(value: ((value0: RichEditorSelection) => void) | undefined): RichEditorAttribute;
    onSelectionChange(value: ((value0: RichEditorRange) => void) | undefined): RichEditorAttribute;
    aboutToIMEInput(value: ((value0: RichEditorInsertValue) => boolean) | undefined): RichEditorAttribute;
    onIMEInputComplete(value: ((value0: RichEditorTextSpanResult) => void) | undefined): RichEditorAttribute;
    onDidIMEInput(value: ((value0: TextRange) => void) | undefined): RichEditorAttribute;
    aboutToDelete(value: ((value0: RichEditorDeleteValue) => boolean) | undefined): RichEditorAttribute;
    onDeleteComplete(value: VoidCallback | undefined): RichEditorAttribute;
    copyOptions(value: CopyOptions | undefined): RichEditorAttribute;
    onPaste(value: PasteEventCallback | undefined): RichEditorAttribute;
    enableDataDetector(value: boolean | undefined): RichEditorAttribute;
    enablePreviewText(value: boolean | undefined): RichEditorAttribute;
    dataDetectorConfig(value: TextDataDetectorConfig | undefined): RichEditorAttribute;
    caretColor(value: ResourceColor | undefined): RichEditorAttribute;
    selectedBackgroundColor(value: ResourceColor | undefined): RichEditorAttribute;
    onEditingChange(value: ((value0: boolean) => void) | undefined): RichEditorAttribute;
    enterKeyType(value: EnterKeyType | undefined): RichEditorAttribute;
    onSubmit(value: SubmitCallback | undefined): RichEditorAttribute;
    onWillChange(value: ((value0: RichEditorChangeValue) => boolean) | undefined): RichEditorAttribute;
    onDidChange(value: OnDidChangeCallback | undefined): RichEditorAttribute;
    onCut(value: ((value0: CutEvent) => void) | undefined): RichEditorAttribute;
    onCopy(value: ((value0: CopyEvent) => void) | undefined): RichEditorAttribute;
    editMenuOptions(value: EditMenuOptions | undefined): RichEditorAttribute;
    enableKeyboardOnFocus(value: boolean | undefined): RichEditorAttribute;
    enableHapticFeedback(value: boolean | undefined): RichEditorAttribute;
    barState(value: BarState | undefined): RichEditorAttribute;
    maxLength(value: number | undefined): RichEditorAttribute;
    maxLines(value: number | undefined): RichEditorAttribute;
    keyboardAppearance(value: KeyboardAppearance | undefined): RichEditorAttribute;
    stopBackPress(value: boolean | undefined): RichEditorAttribute;
    attributeModifier(value: (AttributeModifier<RichEditorAttribute>|AttributeModifier<CommonMethod>) | undefined): RichEditorAttribute;
    bindSelectionMenu(spanType: RichEditorSpanType | undefined, content: CustomBuilder | undefined, responseType: (ResponseType|RichEditorResponseType) | undefined, options?: SelectionMenuOptions | undefined): RichEditorAttribute;
    customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions | undefined): RichEditorAttribute;
    placeholder(value: ResourceStr | undefined, style?: PlaceholderStyle | undefined): RichEditorAttribute;
}
declare interface CutEvent {
    preventDefault?: VoidCallback;
}
declare interface CopyEvent {
    preventDefault?: VoidCallback;
}
declare interface RichEditorUrlStyle {
    url?: ResourceStr;
}
declare type SubmitCallback = ((enterKey: EnterKeyType, event: SubmitEvent) => void);
declare type MenuOnAppearCallback = ((start: number, end: number) => void);
declare type MenuCallback = ((start: number, end: number) => void);
declare type PasteEventCallback = ((event?: PasteEvent) => void);
declare type OnHoverCallback = ((status: boolean, event: HoverEvent) => void);
declare interface RichEditorInterface {
    (value: RichEditorOptions): RichEditorAttribute;
    (options: RichEditorStyledStringOptions): RichEditorAttribute;
}
declare interface RichTextAttribute extends CommonMethod {
    onStart(value: (() => void) | undefined): RichTextAttribute;
    onComplete(value: (() => void) | undefined): RichTextAttribute;
    attributeModifier(value: (AttributeModifier<RichTextAttribute>|AttributeModifier<CommonMethod>) | undefined): RichTextAttribute;
}
declare interface RichTextInterface {
    (content: string): RichTextAttribute;
}
declare interface RootSceneSession {
}
declare interface RootSceneAttribute extends CommonMethod {
    attributeModifier(value: (AttributeModifier<RootSceneAttribute>|AttributeModifier<CommonMethod>) | undefined): RootSceneAttribute;
}
declare interface RootSceneInterface {
    (session: RootSceneSession): RootSceneAttribute;
}
declare interface RowOptions {
    space?: SpaceType;
}
declare interface RowAttribute extends CommonMethod {
    alignItems(value: VerticalAlign | undefined): RowAttribute;
    justifyContent(value: FlexAlign | undefined): RowAttribute;
    pointLight(value: PointLightStyle | undefined): RowAttribute;
    reverse(value: boolean | undefined): RowAttribute;
    attributeModifier(value: (AttributeModifier<RowAttribute>|AttributeModifier<CommonMethod>) | undefined): RowAttribute;
}
declare interface RowInterface {
    (options?: RowOptions): RowAttribute;
}
declare interface RowSplitAttribute extends CommonMethod {
    resizeable(value: boolean | undefined): RowSplitAttribute;
    attributeModifier(value: (AttributeModifier<RowSplitAttribute>|AttributeModifier<CommonMethod>) | undefined): RowSplitAttribute;
}
declare interface RowSplitInterface {
    (): RowSplitAttribute;
}
declare enum SaveIconStyle {
    FULL_FILLED,
    LINES = 1,
    PICTURE = 2,
}
declare enum SaveDescription {
    DOWNLOAD,
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
    SUCCESS,
    TEMPORARY_AUTHORIZATION_FAILED = 1,
}
declare type SaveButtonCallback = ((event: ClickEvent, result: SaveButtonOnClickResult, error?: BusinessError) => void);
declare interface SaveButtonAttribute extends SecurityComponentMethod {
    onClick(value: SaveButtonCallback | undefined): SaveButtonAttribute;
    attributeModifier(value: (AttributeModifier<SaveButtonAttribute>|AttributeModifier<CommonMethod>) | undefined): SaveButtonAttribute;
}
declare interface SaveButtonInterface {
    (): SaveButtonAttribute;
    (options: SaveButtonOptions): SaveButtonAttribute;
}
declare interface ScreenAttribute extends CommonMethod {
    attributeModifier(value: (AttributeModifier<ScreenAttribute>|AttributeModifier<CommonMethod>) | undefined): ScreenAttribute;
}
declare interface ScreenInterface {
    (screenId: number): ScreenAttribute;
}
declare enum ScrollDirection {
    VERTICAL,
    Vertical,
    HORIZONTAL = 1,
    Horizontal = 1,
    NONE = 2,
    None = 2,
}
declare enum ScrollAlign {
    START,
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
declare class Scroller {
    constructor();
    scrollTo(options: ScrollOptions): void;
    scrollEdge(value: Edge, options?: ScrollEdgeOptions): void;
    fling(velocity: number): void;
    scrollPage(value: ScrollPageOptions): void;
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
declare type OnScrollEdgeCallback = ((side: Edge) => void);
declare interface OnScrollFrameBeginHandlerResult {
    offsetRemain: number;
}
declare type OnScrollFrameBeginCallback = ((offset: number, state: ScrollState) => OnScrollFrameBeginHandlerResult);
declare interface ScrollAttribute extends ScrollableCommonMethod {
    scrollable(value: ScrollDirection | undefined): ScrollAttribute;
    onWillScroll(value: ScrollOnWillScrollCallback | undefined): ScrollAttribute;
    onDidScroll(value: ScrollOnScrollCallback | undefined): ScrollAttribute;
    onScrollEdge(value: OnScrollEdgeCallback | undefined): ScrollAttribute;
    onScrollStart(value: VoidCallback | undefined): ScrollAttribute;
    onScrollStop(value: VoidCallback | undefined): ScrollAttribute;
    scrollBar(value: BarState | undefined): ScrollAttribute;
    scrollBarColor(value: (Color|number|string) | undefined): ScrollAttribute;
    scrollBarWidth(value: (number|string) | undefined): ScrollAttribute;
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): ScrollAttribute;
    nestedScroll(value: NestedScrollOptions | undefined): ScrollAttribute;
    enableScrollInteraction(value: boolean | undefined): ScrollAttribute;
    friction(value: (number|Resource) | undefined): ScrollAttribute;
    scrollSnap(value: ScrollSnapOptions | undefined): ScrollAttribute;
    enablePaging(value: boolean | undefined): ScrollAttribute;
    initialOffset(value: OffsetOptions | undefined): ScrollAttribute;
    attributeModifier(value: (AttributeModifier<ScrollAttribute>|AttributeModifier<CommonMethod>) | undefined): ScrollAttribute;
    edgeEffect(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions | undefined): ScrollAttribute;
}
declare type ScrollOnScrollCallback = ((xOffset: number, yOffset: number, scrollState: ScrollState) => void);
declare type ScrollOnWillScrollCallback = ((xOffset: number, yOffset: number, scrollState: ScrollState, scrollSource: ScrollSource) => OffsetResult | undefined);
declare interface ScrollInterface {
    (scroller?: Scroller): ScrollAttribute;
}
declare enum ScrollBarDirection {
    VERTICAL,
    Vertical,
    HORIZONTAL = 1,
    Horizontal = 1,
}
declare interface ScrollBarOptions {
    scroller: Scroller;
    direction?: ScrollBarDirection;
    state?: BarState;
}
declare interface ScrollBarAttribute extends CommonMethod {
    enableNestedScroll(value: boolean | undefined): ScrollBarAttribute;
    attributeModifier(value: (AttributeModifier<ScrollBarAttribute>|AttributeModifier<CommonMethod>) | undefined): ScrollBarAttribute;
}
declare interface ScrollBarInterface {
    (value: ScrollBarOptions): ScrollBarAttribute;
}
declare class SearchController extends TextContentControllerBase {
    constructor();
    caretPosition(value: number): void;
    stopEditing(): void;
    setTextSelection(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void;
}
declare enum CancelButtonStyle {
    CONSTANT,
    INVISIBLE = 1,
    INPUT = 2,
}
declare enum SearchType {
    NORMAL,
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
declare type Callback_InsertValue_Boolean = ((value0: InsertValue) => boolean);
declare type Callback_InsertValue_Void = ((value0: InsertValue) => void);
declare type Callback_DeleteValue_Boolean = ((value0: DeleteValue) => boolean);
declare type Callback_DeleteValue_Void = ((value0: DeleteValue) => void);
declare type Callback_EditableTextChangeValue_Boolean = ((value0: EditableTextChangeValue) => boolean);
declare interface SearchAttribute extends CommonMethod {
    fontColor(value: ResourceColor | undefined): SearchAttribute;
    searchIcon(value: (IconOptions|SymbolGlyphModifier) | undefined): SearchAttribute;
    cancelButton(value: (CancelButtonOptions|CancelButtonSymbolOptions) | undefined): SearchAttribute;
    textIndent(value: Dimension | undefined): SearchAttribute;
    onEditChange(value: ((value0: boolean) => void) | undefined): SearchAttribute;
    selectedBackgroundColor(value: ResourceColor | undefined): SearchAttribute;
    caretStyle(value: CaretStyle | undefined): SearchAttribute;
    placeholderColor(value: ResourceColor | undefined): SearchAttribute;
    placeholderFont(value: Font | undefined): SearchAttribute;
    textFont(value: Font | undefined): SearchAttribute;
    enterKeyType(value: EnterKeyType | undefined): SearchAttribute;
    onSubmit(value: (((value0: string) => void)|SearchSubmitCallback) | undefined): SearchAttribute;
    onChange(value: EditableTextOnChangeCallback | undefined): SearchAttribute;
    onTextSelectionChange(value: OnTextSelectionChangeCallback | undefined): SearchAttribute;
    onContentScroll(value: OnContentScrollCallback | undefined): SearchAttribute;
    onCopy(value: ((value0: string) => void) | undefined): SearchAttribute;
    onCut(value: ((value0: string) => void) | undefined): SearchAttribute;
    onPaste(value: OnPasteCallback | undefined): SearchAttribute;
    copyOption(value: CopyOptions | undefined): SearchAttribute;
    maxLength(value: number | undefined): SearchAttribute;
    textAlign(value: TextAlign | undefined): SearchAttribute;
    enableKeyboardOnFocus(value: boolean | undefined): SearchAttribute;
    selectionMenuHidden(value: boolean | undefined): SearchAttribute;
    minFontSize(value: (number|string|Resource) | undefined): SearchAttribute;
    maxFontSize(value: (number|string|Resource) | undefined): SearchAttribute;
    minFontScale(value: (number|Resource) | undefined): SearchAttribute;
    maxFontScale(value: (number|Resource) | undefined): SearchAttribute;
    decoration(value: TextDecorationOptions | undefined): SearchAttribute;
    letterSpacing(value: (number|string|Resource) | undefined): SearchAttribute;
    lineHeight(value: (number|string|Resource) | undefined): SearchAttribute;
    type(value: SearchType | undefined): SearchAttribute;
    fontFeature(value: string | undefined): SearchAttribute;
    onWillInsert(value: ((value0: InsertValue) => boolean) | undefined): SearchAttribute;
    onDidInsert(value: ((value0: InsertValue) => void) | undefined): SearchAttribute;
    onWillDelete(value: ((value0: DeleteValue) => boolean) | undefined): SearchAttribute;
    onDidDelete(value: ((value0: DeleteValue) => void) | undefined): SearchAttribute;
    editMenuOptions(value: EditMenuOptions | undefined): SearchAttribute;
    enablePreviewText(value: boolean | undefined): SearchAttribute;
    enableHapticFeedback(value: boolean | undefined): SearchAttribute;
    autoCapitalizationMode(value: AutoCapitalizationMode | undefined): SearchAttribute;
    halfLeading(value: boolean | undefined): SearchAttribute;
    stopBackPress(value: boolean | undefined): SearchAttribute;
    onWillChange(value: ((value0: EditableTextChangeValue) => boolean) | undefined): SearchAttribute;
    keyboardAppearance(value: KeyboardAppearance | undefined): SearchAttribute;
    attributeModifier(value: (AttributeModifier<SearchAttribute>|AttributeModifier<CommonMethod>) | undefined): SearchAttribute;
    searchButton(value: string | undefined, option?: SearchButtonOptions | undefined): SearchAttribute;
    inputFilter(value: ResourceStr | undefined, error?: ((value0: string) => void) | undefined): SearchAttribute;
    customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions | undefined): SearchAttribute;
}
declare interface SearchInterface {
    (options?: SearchOptions): SearchAttribute;
}
declare enum SecurityComponentLayoutDirection {
    HORIZONTAL,
    VERTICAL = 1,
}
declare interface SecurityComponentMethod {
    iconSize(value: Dimension | undefined): SecurityComponentMethod;
    layoutDirection(value: SecurityComponentLayoutDirection | undefined): SecurityComponentMethod;
    position(value: Position | undefined): SecurityComponentMethod;
    markAnchor(value: Position | undefined): SecurityComponentMethod;
    offset(value: (Position|Edges|LocalizedEdges) | undefined): SecurityComponentMethod;
    fontSize(value: Dimension | undefined): SecurityComponentMethod;
    fontStyle(value: FontStyle | undefined): SecurityComponentMethod;
    fontWeight(value: (number|FontWeight|string) | undefined): SecurityComponentMethod;
    fontFamily(value: (string|Resource) | undefined): SecurityComponentMethod;
    fontColor(value: ResourceColor | undefined): SecurityComponentMethod;
    iconColor(value: ResourceColor | undefined): SecurityComponentMethod;
    backgroundColor(value: ResourceColor | undefined): SecurityComponentMethod;
    borderStyle(value: BorderStyle | undefined): SecurityComponentMethod;
    borderWidth(value: Dimension | undefined): SecurityComponentMethod;
    borderColor(value: ResourceColor | undefined): SecurityComponentMethod;
    borderRadius(value: Dimension | undefined): SecurityComponentMethod;
    padding(value: (Padding|Dimension) | undefined): SecurityComponentMethod;
    textIconSpace(value: Dimension | undefined): SecurityComponentMethod;
    key(value: string | undefined): SecurityComponentMethod;
    width(value: Length | undefined): SecurityComponentMethod;
    height(value: Length | undefined): SecurityComponentMethod;
    size(value: SizeOptions | undefined): SecurityComponentMethod;
    constraintSize(value: ConstraintSizeOptions | undefined): SecurityComponentMethod;
    align(alignType: Alignment | undefined): SecurityComponentMethod;
    alignRules(alignRule: AlignRuleOption | undefined): SecurityComponentMethod;
    alignRules(alignRule: LocalizedAlignRuleOptions | undefined): SecurityComponentMethod;
    id(description: string | undefined): SecurityComponentMethod;
    chainMode(direction: Axis | undefined, style: ChainStyle | undefined): SecurityComponentMethod;
    minFontScale(scale: (number|Resource) | undefined): SecurityComponentMethod;
    maxFontScale(scale: (number|Resource) | undefined): SecurityComponentMethod;
    maxLines(line: number | undefined): SecurityComponentMethod;
    minFontSize(minSize: (number|string|Resource) | undefined): SecurityComponentMethod;
    maxFontSize(maxSize: (number|string|Resource) | undefined): SecurityComponentMethod;
    heightAdaptivePolicy(policy: TextHeightAdaptivePolicy | undefined): SecurityComponentMethod;
    enabled(respond: boolean | undefined): SecurityComponentMethod;
}
declare interface SelectOption {
    value: ResourceStr;
    icon?: ResourceStr;
    symbolIcon?: SymbolGlyphModifier;
}
declare enum ArrowPosition {
    END,
    START = 1,
}
declare enum MenuAlignType {
    START,
    CENTER = 1,
    END = 2,
}
declare enum AvoidanceMode {
    COVER_TARGET,
    AVOID_AROUND_TARGET = 1,
}
declare type OnSelectCallback = ((index: number, selectStr: string) => void);
declare interface MenuOutlineOptions {
    width?: (Dimension|EdgeOutlineWidths);
    color?: (ResourceColor|EdgeColors);
}
declare interface SelectAttribute extends CommonMethod {
    selected(value: (number|Resource) | undefined): SelectAttribute;
    value(value: (ResourceStr|string|Resource) | undefined): SelectAttribute;
    font(value: Font | undefined): SelectAttribute;
    fontColor(value: ResourceColor | undefined): SelectAttribute;
    selectedOptionBgColor(value: ResourceColor | undefined): SelectAttribute;
    selectedOptionFont(value: Font | undefined): SelectAttribute;
    selectedOptionFontColor(value: ResourceColor | undefined): SelectAttribute;
    optionBgColor(value: ResourceColor | undefined): SelectAttribute;
    optionFont(value: Font | undefined): SelectAttribute;
    optionFontColor(value: ResourceColor | undefined): SelectAttribute;
    onSelect(value: OnSelectCallback | undefined): SelectAttribute;
    space(value: Length | undefined): SelectAttribute;
    arrowPosition(value: ArrowPosition | undefined): SelectAttribute;
    optionWidth(value: (Dimension|OptionWidthMode) | undefined): SelectAttribute;
    optionHeight(value: Dimension | undefined): SelectAttribute;
    menuBackgroundColor(value: ResourceColor | undefined): SelectAttribute;
    menuBackgroundBlurStyle(value: BlurStyle | undefined): SelectAttribute;
    controlSize(value: ControlSize | undefined): SelectAttribute;
    menuItemContentModifier(value: ContentModifier<MenuItemConfiguration> | undefined): SelectAttribute;
    divider(value: DividerOptions | undefined): SelectAttribute;
    textModifier(value: TextModifier | undefined): SelectAttribute;
    arrowModifier(value: SymbolGlyphModifier | undefined): SelectAttribute;
    optionTextModifier(value: TextModifier | undefined): SelectAttribute;
    selectedOptionTextModifier(value: TextModifier | undefined): SelectAttribute;
    dividerStyle(value: DividerStyleOptions | undefined): SelectAttribute;
    avoidance(value: AvoidanceMode | undefined): SelectAttribute;
    menuOutline(value: MenuOutlineOptions | undefined): SelectAttribute;
    attributeModifier(value: (AttributeModifier<SelectAttribute>|AttributeModifier<CommonMethod>) | undefined): SelectAttribute;
    menuAlign(alignType: MenuAlignType | undefined, offset?: Offset | undefined): SelectAttribute;
}
declare interface MenuItemConfiguration extends CommonConfiguration<MenuItemConfiguration> {
    value: ResourceStr;
    icon?: ResourceStr;
    symbolIcon?: SymbolGlyphModifier;
    selected: boolean;
    index: number;
    triggerSelect(index: number, value: string): void;
}
declare interface SelectInterface {
    (options: SelectOption[]): SelectAttribute;
}
declare interface ViewportRect {
    x?: (number|string);
    y?: (number|string);
    width?: (number|string);
    height?: (number|string);
}
declare interface ShapeAttribute extends CommonMethod {
    viewPort(value: ViewportRect | undefined): ShapeAttribute;
    stroke(value: ResourceColor | undefined): ShapeAttribute;
    fill(value: ResourceColor | undefined): ShapeAttribute;
    strokeDashOffset(value: (number|string) | undefined): ShapeAttribute;
    strokeDashArray(value: Length[] | undefined): ShapeAttribute;
    strokeLineCap(value: LineCapStyle | undefined): ShapeAttribute;
    strokeLineJoin(value: LineJoinStyle | undefined): ShapeAttribute;
    strokeMiterLimit(value: (number|string) | undefined): ShapeAttribute;
    strokeOpacity(value: (number|string|Resource) | undefined): ShapeAttribute;
    fillOpacity(value: (number|string|Resource) | undefined): ShapeAttribute;
    strokeWidth(value: (number|string) | undefined): ShapeAttribute;
    antiAlias(value: boolean | undefined): ShapeAttribute;
    attributeModifier(value: (AttributeModifier<ShapeAttribute>|AttributeModifier<CommonMethod>) | undefined): ShapeAttribute;
    mesh(value: number[] | undefined, column: number | undefined, row: number | undefined): ShapeAttribute;
}
declare interface ShapeInterface {
    (value?: image.PixelMap): ShapeAttribute;
}
declare enum SideBarContainerType {
    EMBED,
    Embed,
    OVERLAY = 1,
    Overlay = 1,
    AUTO = 2,
}
declare enum SideBarPosition {
    START,
    Start,
    END = 1,
    End = 1,
}
declare interface ButtonIconOptions {
    shown: (string|image.PixelMap|Resource);
    hidden: (string|image.PixelMap|Resource);
    switching?: (string|image.PixelMap|Resource);
}
declare interface ButtonStyle {
    left?: number;
    top?: number;
    width?: number;
    height?: number;
    icons?: ButtonIconOptions;
}
declare interface SideBarContainerAttribute extends CommonMethod {
    showSideBar(value: boolean | undefined): SideBarContainerAttribute;
    controlButton(value: ButtonStyle | undefined): SideBarContainerAttribute;
    showControlButton(value: boolean | undefined): SideBarContainerAttribute;
    onChange(value: ((value: boolean) => void) | undefined): SideBarContainerAttribute;
    sideBarWidth(value: number | undefined): SideBarContainerAttribute;
    minSideBarWidth(value: number | undefined): SideBarContainerAttribute;
    maxSideBarWidth(value: number | undefined): SideBarContainerAttribute;
    sideBarWidth(value: Length | undefined): SideBarContainerAttribute;
    minSideBarWidth(value: Length | undefined): SideBarContainerAttribute;
    maxSideBarWidth(value: Length | undefined): SideBarContainerAttribute;
    autoHide(value: boolean | undefined): SideBarContainerAttribute;
    sideBarPosition(value: SideBarPosition | undefined): SideBarContainerAttribute;
    divider(value: DividerStyle | undefined): SideBarContainerAttribute;
    minContentWidth(value: Dimension | undefined): SideBarContainerAttribute;
    attributeModifier(value: (AttributeModifier<SideBarContainerAttribute>|AttributeModifier<CommonMethod>) | undefined): SideBarContainerAttribute;
}
declare interface SideBarContainerInterface {
    (type?: SideBarContainerType): SideBarContainerAttribute;
}
declare enum SliderStyle {
    OUT_SET,
    OutSet,
    IN_SET = 1,
    InSet = 1,
    NONE = 2,
}
declare enum SliderChangeMode {
    BEGIN,
    Begin,
    MOVING = 1,
    Moving = 1,
    END = 2,
    End = 2,
    CLICK = 3,
    Click = 3,
}
declare enum SliderInteraction {
    SLIDE_AND_CLICK,
    SLIDE_ONLY = 1,
    SLIDE_AND_CLICK_UP = 2,
}
declare interface SlideRange {
    from?: number;
    to?: number;
}
declare interface SliderOptions {
    value?: number | undefined;
    min?: number;
    max?: number;
    step?: number;
    style?: SliderStyle;
    direction?: Axis;
    reverse?: boolean;
}
declare enum SliderBlockType {
    DEFAULT,
    IMAGE = 1,
    SHAPE = 2,
}
declare interface SliderBlockStyle {
    type: SliderBlockType;
    image?: ResourceStr;
}
declare type SliderTriggerChangeCallback = ((value: number, mode: SliderChangeMode) => void);
declare interface SliderConfiguration extends CommonConfiguration<SliderConfiguration> {
    value: number;
    min: number;
    max: number;
    step: number;
    triggerChange: SliderTriggerChangeCallback;
}
declare type Callback_Number_SliderChangeMode_Void = ((value: number, mode: SliderChangeMode) => void);
declare interface SliderAttribute extends CommonMethod {
    blockColor(value: ResourceColor | undefined): SliderAttribute;
    trackColor(value: (ResourceColor|LinearGradient) | undefined): SliderAttribute;
    selectedColor(value: (ResourceColor|LinearGradient) | undefined): SliderAttribute;
    showSteps(value: boolean | undefined): SliderAttribute;
    trackThickness(value: Length | undefined): SliderAttribute;
    onChange(value: ((value: number, mode: SliderChangeMode) => void) | undefined): SliderAttribute;
    blockBorderColor(value: ResourceColor | undefined): SliderAttribute;
    blockBorderWidth(value: Length | undefined): SliderAttribute;
    stepColor(value: ResourceColor | undefined): SliderAttribute;
    trackBorderRadius(value: Length | undefined): SliderAttribute;
    selectedBorderRadius(value: Dimension | undefined): SliderAttribute;
    blockSize(value: SizeOptions | undefined): SliderAttribute;
    blockStyle(value: SliderBlockStyle | undefined): SliderAttribute;
    stepSize(value: Length | undefined): SliderAttribute;
    sliderInteractionMode(value: SliderInteraction | undefined): SliderAttribute;
    minResponsiveDistance(value: number | undefined): SliderAttribute;
    contentModifier(value: ContentModifier<SliderConfiguration> | undefined): SliderAttribute;
    slideRange(value: SlideRange | undefined): SliderAttribute;
    digitalCrownSensitivity(value: CrownSensitivity | undefined): SliderAttribute;
    enableHapticFeedback(value: boolean | undefined): SliderAttribute;
    attributeModifier(value: (AttributeModifier<SliderAttribute>|AttributeModifier<CommonMethod>) | undefined): SliderAttribute;
    showTips(value: boolean | undefined, content?: ResourceStr | undefined): SliderAttribute;
}
declare interface SliderInterface {
    (options?: SliderOptions): SliderAttribute;
}
declare interface TextBackgroundStyle {
    color?: ResourceColor;
    radius?: (Dimension|BorderRadiuses);
}
declare interface BaseSpan extends CommonMethod {
    textBackgroundStyle(value: TextBackgroundStyle | undefined): BaseSpan;
    baselineOffset(value: LengthMetrics | undefined): BaseSpan;
}
declare interface SpanAttribute extends BaseSpan {
    font(value: Font | undefined): SpanAttribute;
    fontColor(value: ResourceColor | undefined): SpanAttribute;
    fontSize(value: (number|string|Resource) | undefined): SpanAttribute;
    fontStyle(value: FontStyle | undefined): SpanAttribute;
    fontWeight(value: (number|FontWeight|string) | undefined): SpanAttribute;
    fontFamily(value: (string|Resource) | undefined): SpanAttribute;
    decoration(value: DecorationStyleInterface | undefined): SpanAttribute;
    letterSpacing(value: (number|string) | undefined): SpanAttribute;
    textCase(value: TextCase | undefined): SpanAttribute;
    lineHeight(value: Length | undefined): SpanAttribute;
    textShadow(value: (ShadowOptions|ShadowOptions[]) | undefined): SpanAttribute;
    attributeModifier(value: (AttributeModifier<SpanAttribute>|AttributeModifier<CommonMethod>) | undefined): SpanAttribute;
}
declare interface SpanInterface {
    (value: (string|Resource)): SpanAttribute;
}
declare interface StackOptions {
    alignContent?: Alignment;
}
declare interface StackAttribute extends CommonMethod {
    alignContent(value: Alignment | undefined): StackAttribute;
    pointLight(value: PointLightStyle | undefined): StackAttribute;
    attributeModifier(value: (AttributeModifier<StackAttribute>|AttributeModifier<CommonMethod>) | undefined): StackAttribute;
}
declare interface StackInterface {
    (options?: StackOptions): StackAttribute;
}
declare enum ColorMode {
    LIGHT,
    DARK = 1,
}
declare enum LayoutDirection {
    LTR,
    RTL = 1,
    AUTO = 2,
    Auto = 2,
}
declare class Storage {
    constructor(needCrossThread?: boolean, file?: string);
    get(key: string): string | undefined;
    set(key: string, val: Object | undefined): void;
    clear(): void;
    delete(key: string): void;
}
declare interface StepperOptions {
    index?: number;
}
declare interface StepperAttribute extends CommonMethod {
    onFinish(value: (() => void) | undefined): StepperAttribute;
    onSkip(value: (() => void) | undefined): StepperAttribute;
    onChange(value: ((prevIndex: number, index: number) => void) | undefined): StepperAttribute;
    onNext(value: ((prevIndex: number, index: number) => void) | undefined): StepperAttribute;
    onPrevious(value: ((prevIndex: number, index: number) => void) | undefined): StepperAttribute;
    attributeModifier(value: (AttributeModifier<StepperAttribute>|AttributeModifier<CommonMethod>) | undefined): StepperAttribute;
}
declare interface StepperInterface {
    (value?: StepperOptions): StepperAttribute;
}
declare enum ItemState {
    NORMAL,
    Normal,
    DISABLED = 1,
    Disabled = 1,
    WAITING = 2,
    Waiting = 2,
    SKIP = 3,
    Skip = 3,
}
declare interface StepperItemAttribute extends CommonMethod {
    prevLabel(value: string | undefined): StepperItemAttribute;
    nextLabel(value: string | undefined): StepperItemAttribute;
    status(value: ItemState | undefined): StepperItemAttribute;
    attributeModifier(value: (AttributeModifier<StepperItemAttribute>|AttributeModifier<CommonMethod>) | undefined): StepperItemAttribute;
}
declare interface StepperItemInterface {
    (): StepperItemAttribute;
}
declare type StyledStringMarshallingValue = UserDataSpan;
declare type StyledStringMarshallCallback = ((marshallableVal: UserDataSpan) => ArrayBuffer);
declare type StyledStringUnmarshallCallback = ((buf: ArrayBuffer) => UserDataSpan);
declare class StyledString {
    constructor(value: (string|ImageAttachment|CustomSpan), styles?: StyleOptions[]);
    readonly length: number;
    getString(): string;
    getStyles(start: number, length: number, styledKey?: StyledStringKey): SpanStyle[];
    equals(other: StyledString): boolean;
    subStyledString(start: number, length?: number): StyledString;
    static fromHtml(html: string): Promise<StyledString>;
    static toHtml(styledString: StyledString): string;
    static marshalling(styledString: StyledString, callback_: StyledStringMarshallCallback): ArrayBuffer;
    static unmarshalling(buffer: ArrayBuffer, callback_: StyledStringUnmarshallCallback): Promise<StyledString>;
    static marshalling(styledString: StyledString): ArrayBuffer;
    static unmarshalling(buffer: ArrayBuffer): Promise<StyledString>;
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
declare class TextStyle {
    constructor(value?: TextStyleInterface);
    readonly fontColor?: ResourceColor | undefined;
    readonly fontFamily?: string | undefined;
    readonly fontSize?: number | undefined;
    readonly fontWeight?: number | undefined;
    readonly fontStyle?: FontStyle | undefined;
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
    readonly color?: ResourceColor | undefined;
    readonly style?: TextDecorationStyle | undefined;
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
    onClick?: ((value0: ClickEvent) => void);
    onLongPress?: ((value0: GestureEvent) => void);
}
declare class ParagraphStyle {
    constructor(value?: ParagraphStyleInterface);
    readonly textAlign?: TextAlign | undefined;
    readonly textIndent?: number | undefined;
    readonly maxLines?: number | undefined;
    readonly overflow?: TextOverflow | undefined;
    readonly wordBreak?: WordBreak | undefined;
    readonly leadingMargin?: (number|LeadingMarginPlaceholder) | undefined;
    readonly paragraphSpacing?: number | undefined;
}
declare interface ParagraphStyleInterface {
    textAlign?: TextAlign;
    textIndent?: LengthMetrics;
    maxLines?: number;
    overflow?: TextOverflow;
    wordBreak?: WordBreak;
    leadingMargin?: (LengthMetrics|LeadingMarginPlaceholder);
    paragraphSpacing?: LengthMetrics;
}
declare class LineHeightStyle {
    constructor(lineHeight: LengthMetrics);
    readonly lineHeight: number;
}
declare class UrlStyle {
    constructor(url: string);
    readonly url: string;
}
declare type StyledStringValue = (TextStyle|DecorationStyle|BaselineOffsetStyle|LetterSpacingStyle|TextShadowStyle|GestureStyle|ImageAttachment|ParagraphStyle|LineHeightStyle|UrlStyle|CustomSpan|UserDataSpan|BackgroundColorStyle);
declare class MutableStyledString extends StyledString {
    constructor();
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
    FONT,
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
    constructor(value: (ImageAttachmentInterface|AttachmentType | undefined));
    readonly value: image.PixelMap;
    readonly size?: SizeOptions | undefined;
    readonly verticalAlign?: ImageSpanAlignment | undefined;
    readonly objectFit?: ImageFit | undefined;
    readonly layoutStyle?: ImageAttachmentLayoutStyle | undefined;
    readonly colorFilter?: ColorFilterType | undefined;
}
declare interface ResourceImageAttachmentOptions {
    resourceValue: ResourceStr | undefined;
    size?: SizeOptions;
    verticalAlign?: ImageSpanAlignment;
    objectFit?: ImageFit;
    layoutStyle?: ImageAttachmentLayoutStyle;
    colorFilter?: ColorFilterType;
    syncLoad?: boolean;
}
declare interface ImageAttachmentInterface {
    value: image.PixelMap;
    size?: SizeOptions;
    verticalAlign?: ImageSpanAlignment;
    objectFit?: ImageFit;
    layoutStyle?: ImageAttachmentLayoutStyle;
    colorFilter?: ColorFilterType;
}
declare type AttachmentType = (ImageAttachmentInterface|ResourceImageAttachmentOptions);
declare type ColorFilterType = (ColorFilter|drawing.ColorFilter);
declare interface ImageAttachmentLayoutStyle {
    margin?: (LengthMetrics|Padding);
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
declare type Callback_CustomSpanMeasureInfo_CustomSpanMetrics = ((measureInfo: CustomSpanMeasureInfo) => CustomSpanMetrics);
declare type Callback_DrawContext_CustomSpanDrawInfo_Void = ((context: DrawContext, drawInfo: CustomSpanDrawInfo) => void);
declare class CustomSpan {
    constructor();
    onMeasure: ((measureInfo: CustomSpanMeasureInfo) => CustomSpanMetrics);
    onDraw: ((context: DrawContext, drawInfo: CustomSpanDrawInfo) => void);
    invalidate(): void;
}
declare class UserDataSpan {
    constructor();
}
declare class SwiperController {
    constructor();
    showNext(): void;
    showPrevious(): void;
    changeIndex(index: number, animationMode?: (SwiperAnimationMode|boolean)): void;
    finishAnimation(callback_?: VoidCallback): void;
    preloadItems(indices: number[] | undefined): Promise<void>;
}
declare class Indicator<T> {
    constructor();
    left(value: Length): T;
    top(value: Length): T;
    right(value: Length): T;
    bottom(value: Length): T;
    start(value: LengthMetrics): T;
    end(value: LengthMetrics): T;
    static dot(): DotIndicator;
    static digit(): DigitIndicator;
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
    space(space: LengthMetrics): DotIndicator;
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
    STRETCH,
}
declare interface SwiperAnimationEvent {
    currentOffset: number;
    targetOffset: number;
    velocity: number;
}
declare interface AutoPlayOptions {
    stopWhenTouched: boolean;
}
declare enum SwiperNestedScrollMode {
    SELF_ONLY,
    SELF_FIRST = 1,
}
declare enum SwiperAnimationMode {
    NO_ANIMATION,
    DEFAULT_ANIMATION = 1,
    FAST_ANIMATION = 2,
}
declare type OnSwiperAnimationStartCallback = ((index: number, targetIndex: number, extraInfo: SwiperAnimationEvent) => void);
declare type OnSwiperAnimationEndCallback = ((index: number, extraInfo: SwiperAnimationEvent) => void);
declare type OnSwiperGestureSwipeCallback = ((index: number, extraInfo: SwiperAnimationEvent) => void);
declare interface SwiperAttribute extends CommonMethod {
    index(value: number | undefined): SwiperAttribute;
    interval(value: number | undefined): SwiperAttribute;
    indicator(value: (IndicatorComponentController|DotIndicator|DigitIndicator|boolean) | undefined): SwiperAttribute;
    loop(value: boolean | undefined): SwiperAttribute;
    duration(value: number | undefined): SwiperAttribute;
    vertical(value: boolean | undefined): SwiperAttribute;
    itemSpace(value: (number|string) | undefined): SwiperAttribute;
    displayMode(value: SwiperDisplayMode | undefined): SwiperAttribute;
    cachedCount(value: number | undefined): SwiperAttribute;
    effectMode(value: EdgeEffect | undefined): SwiperAttribute;
    disableSwipe(value: boolean | undefined): SwiperAttribute;
    curve(value: (Curve|string|ICurve) | undefined): SwiperAttribute;
    onChange(value: ((value0: number) => void) | undefined): SwiperAttribute;
    onSelected(value: ((value0: number) => void) | undefined): SwiperAttribute;
    onUnselected(value: ((value0: number) => void) | undefined): SwiperAttribute;
    onAnimationStart(value: OnSwiperAnimationStartCallback | undefined): SwiperAttribute;
    onAnimationEnd(value: OnSwiperAnimationEndCallback | undefined): SwiperAttribute;
    onGestureSwipe(value: OnSwiperGestureSwipeCallback | undefined): SwiperAttribute;
    nestedScroll(value: SwiperNestedScrollMode | undefined): SwiperAttribute;
    customContentTransition(value: SwiperContentAnimatedTransition | undefined): SwiperAttribute;
    onContentDidScroll(value: ContentDidScrollCallback | undefined): SwiperAttribute;
    indicatorInteractive(value: boolean | undefined): SwiperAttribute;
    pageFlipMode(value: PageFlipMode | undefined): SwiperAttribute;
    onContentWillScroll(value: ContentWillScrollCallback | undefined): SwiperAttribute;
    attributeModifier(value: (AttributeModifier<SwiperAttribute>|AttributeModifier<CommonMethod>) | undefined): SwiperAttribute;
    autoPlay(autoPlay: boolean | undefined, options: AutoPlayOptions | undefined): SwiperAttribute;
    displayArrow(value: (ArrowStyle|boolean) | undefined, isHoverShow?: boolean | undefined): SwiperAttribute;
    cachedCount(count: number | undefined, isShown: boolean | undefined): SwiperAttribute;
    displayCount(value: (number|string|SwiperAutoFill) | undefined, swipeByGroup?: boolean | undefined): SwiperAttribute;
    prevMargin(value: Length | undefined, ignoreBlank?: boolean | undefined): SwiperAttribute;
    nextMargin(value: Length | undefined, ignoreBlank?: boolean | undefined): SwiperAttribute;
}
declare type Callback_SwiperContentTransitionProxy_Void = ((value0: SwiperContentTransitionProxy) => void);
declare interface SwiperContentAnimatedTransition {
    timeout?: number;
    transition: ((value0: SwiperContentTransitionProxy) => void);
}
declare interface SwiperContentTransitionProxy {
    selectedIndex: number;
    index: number;
    position: number;
    mainAxisLength: number;
    finishTransition(): void;
}
declare interface SwiperContentWillScrollResult {
    currentIndex: number;
    comingIndex: number;
    offset: number;
}
declare type ContentDidScrollCallback = ((selectedIndex: number, index: number, position: number, mainAxisLength: number) => void);
declare type ContentWillScrollCallback = ((result: SwiperContentWillScrollResult) => boolean);
declare interface SwiperInterface {
    (controller?: SwiperController): SwiperAttribute;
}
declare enum SymbolRenderingStrategy {
    SINGLE,
    MULTIPLE_COLOR = 1,
    MULTIPLE_OPACITY = 2,
}
declare enum SymbolEffectStrategy {
    NONE,
    SCALE = 1,
    HIERARCHICAL = 2,
}
declare enum EffectDirection {
    DOWN,
    UP = 1,
}
declare enum EffectScope {
    LAYER,
    WHOLE = 1,
}
declare enum EffectFillStyle {
    CUMULATIVE,
    ITERATIVE = 1,
}
declare class SymbolEffect {
    constructor();
}
declare class ScaleSymbolEffect extends SymbolEffect {
    constructor(scope?: EffectScope, direction?: EffectDirection);
    scope?: EffectScope | undefined;
    direction?: EffectDirection | undefined;
}
declare class HierarchicalSymbolEffect extends SymbolEffect {
    constructor(fillStyle?: EffectFillStyle);
    fillStyle?: EffectFillStyle | undefined;
}
declare class AppearSymbolEffect extends SymbolEffect {
    constructor(scope?: EffectScope);
    scope?: EffectScope | undefined;
}
declare class DisappearSymbolEffect extends SymbolEffect {
    constructor(scope?: EffectScope);
    scope?: EffectScope | undefined;
}
declare class BounceSymbolEffect extends SymbolEffect {
    constructor(scope?: EffectScope, direction?: EffectDirection);
    scope?: EffectScope | undefined;
    direction?: EffectDirection | undefined;
}
declare class ReplaceSymbolEffect extends SymbolEffect {
    constructor(scope?: EffectScope);
    scope?: EffectScope | undefined;
}
declare class PulseSymbolEffect extends SymbolEffect {
    constructor();
}
declare interface SymbolGlyphAttribute extends CommonMethod {
    fontSize(value: (number|string|Resource) | undefined): SymbolGlyphAttribute;
    fontColor(value: ResourceColor[] | undefined): SymbolGlyphAttribute;
    fontWeight(value: (number|FontWeight|string) | undefined): SymbolGlyphAttribute;
    effectStrategy(value: SymbolEffectStrategy | undefined): SymbolGlyphAttribute;
    renderingStrategy(value: SymbolRenderingStrategy | undefined): SymbolGlyphAttribute;
    minFontScale(value: (number|Resource) | undefined): SymbolGlyphAttribute;
    maxFontScale(value: (number|Resource) | undefined): SymbolGlyphAttribute;
    attributeModifier(value: (AttributeModifier<SymbolGlyphAttribute>|AttributeModifier<CommonMethod>) | undefined): SymbolGlyphAttribute;
    symbolEffect(symbolEffect: SymbolEffect | undefined, triggerValue?: (boolean|number) | undefined): SymbolGlyphAttribute;
}
declare interface SymbolGlyphInterface {
    (value?: Resource): SymbolGlyphAttribute;
}
declare interface SymbolSpanAttribute extends CommonMethod {
    fontSize(value: (number|string|Resource) | undefined): SymbolSpanAttribute;
    fontColor(value: ResourceColor[] | undefined): SymbolSpanAttribute;
    fontWeight(value: (number|FontWeight|string) | undefined): SymbolSpanAttribute;
    effectStrategy(value: SymbolEffectStrategy | undefined): SymbolSpanAttribute;
    renderingStrategy(value: SymbolRenderingStrategy | undefined): SymbolSpanAttribute;
    attributeModifier(value: (AttributeModifier<SymbolSpanAttribute>|AttributeModifier<CommonMethod>) | undefined): SymbolSpanAttribute;
}
declare interface SymbolSpanInterface {
    (value: Resource): SymbolSpanAttribute;
}
declare enum SelectedMode {
    INDICATOR,
    BOARD = 1,
}
declare enum LayoutMode {
    AUTO,
    VERTICAL = 1,
    HORIZONTAL = 2,
}
declare interface SubTabBarIndicatorStyle {
    color?: ResourceColor;
    height?: Length;
    width?: Length;
    borderRadius?: Length;
    marginTop?: Length;
}
declare interface BoardStyle {
    borderRadius?: Length;
}
declare interface TabBarLabelStyle {
    overflow?: TextOverflow;
    maxLines?: number;
    minFontSize?: (number|ResourceStr);
    maxFontSize?: (number|ResourceStr);
    heightAdaptivePolicy?: TextHeightAdaptivePolicy;
    font?: Font;
    selectedColor?: ResourceColor;
    unselectedColor?: ResourceColor;
}
declare interface TabBarIconStyle {
    selectedColor?: ResourceColor;
    unselectedColor?: ResourceColor;
}
declare class TabBarSymbol {
    constructor();
    normal: SymbolGlyphModifier;
    selected?: SymbolGlyphModifier | undefined;
}
declare interface TabBarOptions {
    icon?: (string|Resource);
    text?: (string|Resource);
}
declare class SubTabBarStyle {
    constructor(content: ResourceStr);
    constructor(content: (ResourceStr|ComponentContent));
    static of(content: (ResourceStr|ComponentContent)): SubTabBarStyle;
    indicator(style: SubTabBarIndicatorStyle): SubTabBarStyle;
    selectedMode(value: SelectedMode): SubTabBarStyle;
    board(value: BoardStyle): SubTabBarStyle;
    labelStyle(style: TabBarLabelStyle): SubTabBarStyle;
    padding(value: (Padding|Dimension)): SubTabBarStyle;
    padding(padding: LocalizedPadding): SubTabBarStyle;
    id(value: string): SubTabBarStyle;
}
declare class BottomTabBarStyle {
    constructor(icon: (ResourceStr|TabBarSymbol), text: ResourceStr);
    static of(icon: (ResourceStr|TabBarSymbol), text: ResourceStr): BottomTabBarStyle;
    labelStyle(style: TabBarLabelStyle): BottomTabBarStyle;
    padding(value: (Padding|Dimension|LocalizedPadding)): BottomTabBarStyle;
    layoutMode(value: LayoutMode): BottomTabBarStyle;
    verticalAlign(value: VerticalAlign): BottomTabBarStyle;
    symmetricExtensible(value: boolean): BottomTabBarStyle;
    id(value: string): BottomTabBarStyle;
    iconStyle(style: TabBarIconStyle): BottomTabBarStyle;
}
declare interface TabContentAttribute extends CommonMethod {
    tabBar(value: (ComponentContent|SubTabBarStyle|BottomTabBarStyle|string|Resource|CustomBuilder|TabBarOptions) | undefined): TabContentAttribute;
    onWillShow(value: VoidCallback | undefined): TabContentAttribute;
    onWillHide(value: VoidCallback | undefined): TabContentAttribute;
    attributeModifier(value: (AttributeModifier<TabContentAttribute>|AttributeModifier<CommonMethod>) | undefined): TabContentAttribute;
}
declare interface TabContentInterface {
    (): TabContentAttribute;
}
declare enum BarMode {
    SCROLLABLE,
    Scrollable,
    FIXED = 1,
    Fixed = 1,
}
declare enum AnimationMode {
    CONTENT_FIRST,
    ACTION_FIRST = 1,
    NO_ANIMATION = 2,
    CONTENT_FIRST_WITH_JUMP = 3,
    ACTION_FIRST_WITH_JUMP = 4,
}
declare enum BarPosition {
    START,
    Start,
    END = 1,
    End = 1,
}
declare enum LayoutStyle {
    ALWAYS_CENTER,
    ALWAYS_AVERAGE_SPLIT = 1,
    SPACE_BETWEEN_OR_CENTER = 2,
}
declare enum TabsCacheMode {
    CACHE_BOTH_SIDE,
    CACHE_LATEST_SWITCHED = 1,
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
    barModifier?: CommonModifier;
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
declare interface TabsAttribute extends CommonMethod {
    vertical(value: boolean | undefined): TabsAttribute;
    barPosition(value: BarPosition | undefined): TabsAttribute;
    scrollable(value: boolean | undefined): TabsAttribute;
    barWidth(value: Length | undefined): TabsAttribute;
    barHeight(value: Length | undefined): TabsAttribute;
    animationDuration(value: number | undefined): TabsAttribute;
    animationMode(value: AnimationMode | undefined): TabsAttribute;
    edgeEffect(value: EdgeEffect | undefined): TabsAttribute;
    onChange(value: ((value0: number) => void) | undefined): TabsAttribute;
    onSelected(value: ((value0: number) => void) | undefined): TabsAttribute;
    onTabBarClick(value: ((value0: number) => void) | undefined): TabsAttribute;
    onUnselected(value: ((value0: number) => void) | undefined): TabsAttribute;
    onAnimationStart(value: OnTabsAnimationStartCallback | undefined): TabsAttribute;
    onAnimationEnd(value: OnTabsAnimationEndCallback | undefined): TabsAttribute;
    onGestureSwipe(value: OnTabsGestureSwipeCallback | undefined): TabsAttribute;
    fadingEdge(value: boolean | undefined): TabsAttribute;
    divider(value: DividerStyle | undefined): TabsAttribute;
    barOverlap(value: boolean | undefined): TabsAttribute;
    barBackgroundColor(value: ResourceColor | undefined): TabsAttribute;
    barGridAlign(value: BarGridColumnOptions | undefined): TabsAttribute;
    customContentTransition(value: TabsCustomContentTransitionCallback | undefined): TabsAttribute;
    barBackgroundBlurStyle(value: BlurStyle | undefined): TabsAttribute;
    barBackgroundEffect(value: BackgroundEffectOptions | undefined): TabsAttribute;
    pageFlipMode(value: PageFlipMode | undefined): TabsAttribute;
    onContentWillChange(value: OnTabsContentWillChangeCallback | undefined): TabsAttribute;
    attributeModifier(value: (AttributeModifier<TabsAttribute>|AttributeModifier<CommonMethod>) | undefined): TabsAttribute;
    barMode(value: BarMode | undefined, options?: ScrollableBarModeOptions | undefined): TabsAttribute;
    barBackgroundBlurStyle(style: BlurStyle | undefined, options: BackgroundBlurStyleOptions | undefined): TabsAttribute;
    cachedMaxCount(count: number | undefined, mode: TabsCacheMode | undefined): TabsAttribute;
}
declare type Callback_TabContentTransitionProxy_Void = ((value0: TabContentTransitionProxy) => void);
declare interface TabContentAnimatedTransition {
    timeout?: number;
    transition: ((value0: TabContentTransitionProxy) => void);
}
declare interface TabContentTransitionProxy {
    from: number;
    to: number;
    finishTransition(): void;
}
declare interface TabsInterface {
    (options?: TabsOptions): TabsAttribute;
}
declare interface TextOverflowOptions {
    overflow: TextOverflow;
}
declare type Callback_MarqueeState_Void = ((value0: MarqueeState) => void);
declare interface TextAttribute extends CommonMethod {
    fontColor(value: ResourceColor | undefined): TextAttribute;
    fontSize(value: (number|string|Resource) | undefined): TextAttribute;
    minFontSize(value: (number|string|Resource) | undefined): TextAttribute;
    maxFontSize(value: (number|string|Resource) | undefined): TextAttribute;
    minFontScale(value: (number|Resource) | undefined): TextAttribute;
    maxFontScale(value: (number|Resource) | undefined): TextAttribute;
    fontStyle(value: FontStyle | undefined): TextAttribute;
    lineSpacing(value: LengthMetrics | undefined): TextAttribute;
    textAlign(value: TextAlign | undefined): TextAttribute;
    lineHeight(value: (number|string|Resource) | undefined): TextAttribute;
    textOverflow(value: TextOverflowOptions | undefined): TextAttribute;
    fontFamily(value: (string|Resource) | undefined): TextAttribute;
    maxLines(value: number | undefined): TextAttribute;
    decoration(value: DecorationStyleInterface | undefined): TextAttribute;
    letterSpacing(value: (number|string) | undefined): TextAttribute;
    textCase(value: TextCase | undefined): TextAttribute;
    baselineOffset(value: (number|string) | undefined): TextAttribute;
    copyOption(value: CopyOptions | undefined): TextAttribute;
    draggable(value: boolean | undefined): TextAttribute;
    textShadow(value: (ShadowOptions|ShadowOptions[]) | undefined): TextAttribute;
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): TextAttribute;
    textIndent(value: Length | undefined): TextAttribute;
    wordBreak(value: WordBreak | undefined): TextAttribute;
    lineBreakStrategy(value: LineBreakStrategy | undefined): TextAttribute;
    onCopy(value: ((value: string) => void) | undefined): TextAttribute;
    caretColor(value: ResourceColor | undefined): TextAttribute;
    selectedBackgroundColor(value: ResourceColor | undefined): TextAttribute;
    ellipsisMode(value: EllipsisMode | undefined): TextAttribute;
    enableDataDetector(value: boolean | undefined): TextAttribute;
    dataDetectorConfig(value: TextDataDetectorConfig | undefined): TextAttribute;
    onTextSelectionChange(value: ((selectionStart: number, selectionEnd: number) => void) | undefined): TextAttribute;
    fontFeature(value: string | undefined): TextAttribute;
    marqueeOptions(value: TextMarqueeOptions | undefined): TextAttribute;
    onMarqueeStateChange(value: ((value0: MarqueeState) => void) | undefined): TextAttribute;
    privacySensitive(value: boolean | undefined): TextAttribute;
    textSelectable(value: TextSelectableMode | undefined): TextAttribute;
    editMenuOptions(value: EditMenuOptions | undefined): TextAttribute;
    halfLeading(value: boolean | undefined): TextAttribute;
    enableHapticFeedback(value: boolean | undefined): TextAttribute;
    attributeModifier(value: (AttributeModifier<TextAttribute>|AttributeModifier<CommonMethod>) | undefined): TextAttribute;
    font(fontValue: Font | undefined, options?: FontSettingOptions | undefined): TextAttribute;
    fontWeight(weight: (number|FontWeight|string) | undefined, options?: FontSettingOptions | undefined): TextAttribute;
    selection(selectionStart: number | undefined, selectionEnd: number | undefined): TextAttribute;
    bindSelectionMenu(spanType: TextSpanType | undefined, content: CustomBuilder | undefined, responseType: TextResponseType | undefined, options?: SelectionMenuOptions | undefined): TextAttribute;
}
declare enum TextSpanType {
    TEXT,
    IMAGE = 1,
    MIXED = 2,
    DEFAULT = 3,
}
declare enum TextResponseType {
    RIGHT_CLICK,
    LONG_PRESS = 1,
    SELECT = 2,
    DEFAULT = 3,
}
declare enum MarqueeState {
    START,
    BOUNCE = 1,
    FINISH = 2,
}
declare enum MarqueeStartPolicy {
    DEFAULT,
    ON_FOCUS = 1,
}
declare interface TextOptions {
    controller: TextController;
}
declare interface TextMarqueeOptions {
    start: boolean;
    step?: number;
    loop?: number;
    fromStart?: boolean;
    delay?: number;
    fadeout?: boolean;
    marqueeStartPolicy?: MarqueeStartPolicy;
}
declare class TextController {
    constructor();
    closeSelectionMenu(): void;
    setStyledString(value: StyledString): void;
    getLayoutManager(): LayoutManager;
}
declare interface TextInterface {
    (content?: (string|Resource), value?: TextOptions): TextAttribute;
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
declare enum TextAreaType {
    NORMAL,
    NUMBER = 2,
    PHONE_NUMBER = 3,
    EMAIL = 5,
    NUMBER_DECIMAL = 12,
    URL = 13,
}
declare type TextAreaSubmitCallback = ((enterKeyType: EnterKeyType, event?: SubmitEvent) => void);
declare type Callback_EnterKeyType_Void = ((enterKey: EnterKeyType) => void);
declare type Callback_String_PasteEvent_Void = ((value: string, event: PasteEvent) => void);
declare interface TextAreaAttribute extends CommonMethod {
    placeholderColor(value: ResourceColor | undefined): TextAreaAttribute;
    placeholderFont(value: Font | undefined): TextAreaAttribute;
    enterKeyType(value: EnterKeyType | undefined): TextAreaAttribute;
    textAlign(value: TextAlign | undefined): TextAreaAttribute;
    caretColor(value: ResourceColor | undefined): TextAreaAttribute;
    fontColor(value: ResourceColor | undefined): TextAreaAttribute;
    fontSize(value: Length | undefined): TextAreaAttribute;
    fontStyle(value: FontStyle | undefined): TextAreaAttribute;
    fontWeight(value: (number|FontWeight|string) | undefined): TextAreaAttribute;
    fontFamily(value: ResourceStr | undefined): TextAreaAttribute;
    textOverflow(value: TextOverflow | undefined): TextAreaAttribute;
    textIndent(value: Dimension | undefined): TextAreaAttribute;
    caretStyle(value: CaretStyle | undefined): TextAreaAttribute;
    selectedBackgroundColor(value: ResourceColor | undefined): TextAreaAttribute;
    onSubmit(value: (((enterKey: EnterKeyType) => void)|TextAreaSubmitCallback) | undefined): TextAreaAttribute;
    onChange(value: EditableTextOnChangeCallback | undefined): TextAreaAttribute;
    onTextSelectionChange(value: ((selectionStart: number, selectionEnd: number) => void) | undefined): TextAreaAttribute;
    onContentScroll(value: ((selectionStart: number, selectionEnd: number) => void) | undefined): TextAreaAttribute;
    onEditChange(value: ((isEditing: boolean) => void) | undefined): TextAreaAttribute;
    onCopy(value: ((value: string) => void) | undefined): TextAreaAttribute;
    onCut(value: ((value: string) => void) | undefined): TextAreaAttribute;
    onPaste(value: ((value: string, event: PasteEvent) => void) | undefined): TextAreaAttribute;
    copyOption(value: CopyOptions | undefined): TextAreaAttribute;
    enableKeyboardOnFocus(value: boolean | undefined): TextAreaAttribute;
    maxLength(value: number | undefined): TextAreaAttribute;
    style(value: TextContentStyle | undefined): TextAreaAttribute;
    barState(value: BarState | undefined): TextAreaAttribute;
    selectionMenuHidden(value: boolean | undefined): TextAreaAttribute;
    minFontSize(value: (number|string|Resource) | undefined): TextAreaAttribute;
    maxFontSize(value: (number|string|Resource) | undefined): TextAreaAttribute;
    minFontScale(value: (number|Resource) | undefined): TextAreaAttribute;
    maxFontScale(value: (number|Resource) | undefined): TextAreaAttribute;
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): TextAreaAttribute;
    maxLines(value: number | undefined): TextAreaAttribute;
    wordBreak(value: WordBreak | undefined): TextAreaAttribute;
    lineBreakStrategy(value: LineBreakStrategy | undefined): TextAreaAttribute;
    decoration(value: TextDecorationOptions | undefined): TextAreaAttribute;
    letterSpacing(value: (number|string|Resource) | undefined): TextAreaAttribute;
    lineSpacing(value: LengthMetrics | undefined): TextAreaAttribute;
    lineHeight(value: (number|string|Resource) | undefined): TextAreaAttribute;
    type(value: TextAreaType | undefined): TextAreaAttribute;
    enableAutoFill(value: boolean | undefined): TextAreaAttribute;
    contentType(value: ContentType | undefined): TextAreaAttribute;
    fontFeature(value: string | undefined): TextAreaAttribute;
    onWillInsert(value: ((value0: InsertValue) => boolean) | undefined): TextAreaAttribute;
    onDidInsert(value: ((value0: InsertValue) => void) | undefined): TextAreaAttribute;
    onWillDelete(value: ((value0: DeleteValue) => boolean) | undefined): TextAreaAttribute;
    onDidDelete(value: ((value0: DeleteValue) => void) | undefined): TextAreaAttribute;
    editMenuOptions(value: EditMenuOptions | undefined): TextAreaAttribute;
    enablePreviewText(value: boolean | undefined): TextAreaAttribute;
    enableHapticFeedback(value: boolean | undefined): TextAreaAttribute;
    autoCapitalizationMode(value: AutoCapitalizationMode | undefined): TextAreaAttribute;
    halfLeading(value: boolean | undefined): TextAreaAttribute;
    ellipsisMode(value: EllipsisMode | undefined): TextAreaAttribute;
    stopBackPress(value: boolean | undefined): TextAreaAttribute;
    onWillChange(value: ((value0: EditableTextChangeValue) => boolean) | undefined): TextAreaAttribute;
    keyboardAppearance(value: KeyboardAppearance | undefined): TextAreaAttribute;
    attributeModifier(value: (AttributeModifier<TextAreaAttribute>|AttributeModifier<CommonMethod>) | undefined): TextAreaAttribute;
    inputFilter(value: ResourceStr | undefined, error?: ((value: string) => void) | undefined): TextAreaAttribute;
    showCounter(value: boolean | undefined, options?: InputCounterOptions | undefined): TextAreaAttribute;
    customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions | undefined): TextAreaAttribute;
}
declare interface TextAreaInterface {
    (value?: TextAreaOptions): TextAreaAttribute;
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
declare interface TextClockAttribute extends CommonMethod {
    format(value: ResourceStr | undefined): TextClockAttribute;
    onDateChange(value: ((value: number) => void) | undefined): TextClockAttribute;
    fontColor(value: ResourceColor | undefined): TextClockAttribute;
    fontSize(value: Length | undefined): TextClockAttribute;
    fontStyle(value: FontStyle | undefined): TextClockAttribute;
    fontWeight(value: (number|FontWeight|string) | undefined): TextClockAttribute;
    fontFamily(value: ResourceStr | undefined): TextClockAttribute;
    textShadow(value: (ShadowOptions|ShadowOptions[]) | undefined): TextClockAttribute;
    fontFeature(value: string | undefined): TextClockAttribute;
    contentModifier(value: ContentModifier<TextClockConfiguration> | undefined): TextClockAttribute;
    dateTimeOptions(value: intl.DateTimeOptions | undefined): TextClockAttribute;
    attributeModifier(value: (AttributeModifier<TextClockAttribute>|AttributeModifier<CommonMethod>) | undefined): TextClockAttribute;
}
declare interface TextClockInterface {
    (options?: TextClockOptions): TextClockAttribute;
}
declare enum TextDataDetectorType {
    PHONE_NUMBER,
    URL = 1,
    EMAIL = 2,
    ADDRESS = 3,
    DATE_TIME = 4,
}
declare interface TextDataDetectorConfig {
    types: TextDataDetectorType[];
    onDetectResultUpdate?: ((value0: string) => void);
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
    BACKWARD,
    FORWARD = 1,
}
declare enum MenuType {
    SELECTION_MENU,
    PREVIEW_MENU = 1,
}
declare enum AutoCapitalizationMode {
    NONE,
    WORDS = 1,
    SENTENCES = 2,
    ALL_CHARACTERS = 3,
}
declare interface DeleteValue {
    deleteOffset: number;
    direction: TextDeleteDirection;
    deleteValue: string;
}
declare type OnDidChangeCallback = ((rangeBefore: TextRange, rangeAfter: TextRange) => void);
declare type EditableTextOnChangeCallback = ((value: string, previewText?: PreviewText, options?: TextChangeOptions) => void);
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
    getPreviewText(): PreviewText;
}
declare interface PreviewText {
    offset: number;
    value: string;
}
declare interface StyledStringController {
    setStyledString(styledString: StyledString): void;
    getStyledString(): MutableStyledString;
}
declare type Callback_StyledStringChangeValue_Boolean = ((value0: StyledStringChangeValue) => boolean);
declare interface StyledStringChangedListener {
    onWillChange?: ((value0: StyledStringChangeValue) => boolean);
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
}
declare interface PositionWithAffinity {
    position: number;
}
declare interface CaretStyle {
    width?: Length;
    color?: ResourceColor;
}
declare class TextMenuItemId {
    constructor();
    static readonly CUT: TextMenuItemId;
    static readonly COPY: TextMenuItemId;
    static readonly PASTE: TextMenuItemId;
    static readonly SELECT_ALL: TextMenuItemId;
    static readonly COLLABORATION_SERVICE: TextMenuItemId;
    static readonly CAMERA_INPUT: TextMenuItemId;
    static readonly AI_WRITER: TextMenuItemId;
    static readonly TRANSLATE: TextMenuItemId;
    static readonly SEARCH: TextMenuItemId;
    static readonly SHARE: TextMenuItemId;
    static of(id: ResourceStr): TextMenuItemId;
    equals(id: TextMenuItemId): boolean;
}
declare interface TextMenuItem {
    content: ResourceStr;
    icon?: ResourceStr;
    id: TextMenuItemId;
    labelInfo?: ResourceStr;
}
declare type OnCreateMenuCallback = ((menuItems: TextMenuItem[]) => TextMenuItem[]);
declare type OnMenuItemClickCallback = ((menuItem: TextMenuItem, range: TextRange) => boolean);
declare interface EditMenuOptions {
    onCreateMenu: OnCreateMenuCallback;
    onMenuItemClick: OnMenuItemClickCallback;
}
declare interface DecorationStyleResult {
    type: TextDecorationType;
    color: ResourceColor;
    style?: TextDecorationStyle;
}
declare interface FontSettingOptions {
    enableVariableFontWeight?: boolean;
}
declare interface TextChangeOptions {
    rangeBefore: TextRange;
    rangeAfter: TextRange;
    oldContent: string;
    oldPreviewText: PreviewText;
}
declare interface EditableTextChangeValue {
    content: string;
    previewText?: PreviewText;
    options?: TextChangeOptions;
}
declare enum TextMenuShowMode {
    DEFAULT,
    PREFER_WINDOW = 1,
}
declare interface TextMenuOptions {
    showMode?: TextMenuShowMode;
}
declare enum KeyboardAppearance {
    NONE_IMMERSIVE,
    IMMERSIVE = 1,
    LIGHT_IMMERSIVE = 2,
    DARK_IMMERSIVE = 3,
}
declare enum InputType {
    NORMAL,
    Normal,
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
declare enum ContentType {
    USER_NAME,
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
    PASSPORT_NUMBER = 26,
    VALIDITY = 27,
    ISSUE_AT = 28,
    ORGANIZATION = 29,
    TAX_ID = 30,
    ADDRESS_CITY_AND_STATE = 31,
    FLIGHT_NUMBER = 32,
    LICENSE_NUMBER = 33,
    LICENSE_FILE_NUMBER = 34,
    LICENSE_PLATE = 35,
    ENGINE_NUMBER = 36,
    LICENSE_CHASSIS_NUMBER = 37,
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
    DEFAULT,
    Default,
    INLINE = 1,
    Inline = 1,
}
declare interface PasswordIcon {
    onIconSrc?: (string|Resource);
    offIconSrc?: (string|Resource);
}
declare type OnSubmitCallback = ((enterKey: EnterKeyType, event: SubmitEvent) => void);
declare type OnTextSelectionChangeCallback = ((selectionStart: number, selectionEnd: number) => void);
declare type OnContentScrollCallback = ((totalOffsetX: number, totalOffsetY: number) => void);
declare type OnPasteCallback = ((content: string, event: PasteEvent) => void);
declare interface TextInputAttribute extends CommonMethod {
    type(value: InputType | undefined): TextInputAttribute;
    contentType(value: ContentType | undefined): TextInputAttribute;
    placeholderColor(value: ResourceColor | undefined): TextInputAttribute;
    textOverflow(value: TextOverflow | undefined): TextInputAttribute;
    textIndent(value: Dimension | undefined): TextInputAttribute;
    placeholderFont(value: Font | undefined): TextInputAttribute;
    enterKeyType(value: EnterKeyType | undefined): TextInputAttribute;
    caretColor(value: ResourceColor | undefined): TextInputAttribute;
    onEditChange(value: ((value0: boolean) => void) | undefined): TextInputAttribute;
    onSubmit(value: OnSubmitCallback | undefined): TextInputAttribute;
    onChange(value: EditableTextOnChangeCallback | undefined): TextInputAttribute;
    onTextSelectionChange(value: OnTextSelectionChangeCallback | undefined): TextInputAttribute;
    onContentScroll(value: OnContentScrollCallback | undefined): TextInputAttribute;
    maxLength(value: number | undefined): TextInputAttribute;
    fontColor(value: ResourceColor | undefined): TextInputAttribute;
    fontSize(value: Length | undefined): TextInputAttribute;
    fontStyle(value: FontStyle | undefined): TextInputAttribute;
    fontWeight(value: (number|FontWeight|string) | undefined): TextInputAttribute;
    fontFamily(value: ResourceStr | undefined): TextInputAttribute;
    onCopy(value: ((value0: string) => void) | undefined): TextInputAttribute;
    onCut(value: ((value0: string) => void) | undefined): TextInputAttribute;
    onPaste(value: OnPasteCallback | undefined): TextInputAttribute;
    copyOption(value: CopyOptions | undefined): TextInputAttribute;
    showPasswordIcon(value: boolean | undefined): TextInputAttribute;
    textAlign(value: TextAlign | undefined): TextInputAttribute;
    style(value: (TextInputStyle|TextContentStyle) | undefined): TextInputAttribute;
    caretStyle(value: CaretStyle | undefined): TextInputAttribute;
    selectedBackgroundColor(value: ResourceColor | undefined): TextInputAttribute;
    caretPosition(value: number | undefined): TextInputAttribute;
    enableKeyboardOnFocus(value: boolean | undefined): TextInputAttribute;
    passwordIcon(value: PasswordIcon | undefined): TextInputAttribute;
    showError(value: ResourceStr | undefined): TextInputAttribute;
    showUnit(value: CustomBuilder | undefined): TextInputAttribute;
    showUnderline(value: boolean | undefined): TextInputAttribute;
    underlineColor(value: (ResourceColor|UnderlineColor) | undefined): TextInputAttribute;
    selectionMenuHidden(value: boolean | undefined): TextInputAttribute;
    barState(value: BarState | undefined): TextInputAttribute;
    maxLines(value: number | undefined): TextInputAttribute;
    wordBreak(value: WordBreak | undefined): TextInputAttribute;
    lineBreakStrategy(value: LineBreakStrategy | undefined): TextInputAttribute;
    cancelButton(value: (CancelButtonOptions|CancelButtonSymbolOptions) | undefined): TextInputAttribute;
    selectAll(value: boolean | undefined): TextInputAttribute;
    minFontSize(value: (number|string|Resource) | undefined): TextInputAttribute;
    maxFontSize(value: (number|string|Resource) | undefined): TextInputAttribute;
    minFontScale(value: (number|Resource) | undefined): TextInputAttribute;
    maxFontScale(value: (number|Resource) | undefined): TextInputAttribute;
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): TextInputAttribute;
    enableAutoFill(value: boolean | undefined): TextInputAttribute;
    decoration(value: TextDecorationOptions | undefined): TextInputAttribute;
    letterSpacing(value: (number|string|Resource) | undefined): TextInputAttribute;
    lineHeight(value: (number|string|Resource) | undefined): TextInputAttribute;
    passwordRules(value: string | undefined): TextInputAttribute;
    fontFeature(value: string | undefined): TextInputAttribute;
    showPassword(value: boolean | undefined): TextInputAttribute;
    onSecurityStateChange(value: ((value0: boolean) => void) | undefined): TextInputAttribute;
    onWillInsert(value: ((value0: InsertValue) => boolean) | undefined): TextInputAttribute;
    onDidInsert(value: ((value0: InsertValue) => void) | undefined): TextInputAttribute;
    onWillDelete(value: ((value0: DeleteValue) => boolean) | undefined): TextInputAttribute;
    onDidDelete(value: ((value0: DeleteValue) => void) | undefined): TextInputAttribute;
    editMenuOptions(value: EditMenuOptions | undefined): TextInputAttribute;
    enablePreviewText(value: boolean | undefined): TextInputAttribute;
    enableHapticFeedback(value: boolean | undefined): TextInputAttribute;
    autoCapitalizationMode(value: AutoCapitalizationMode | undefined): TextInputAttribute;
    halfLeading(value: boolean | undefined): TextInputAttribute;
    ellipsisMode(value: EllipsisMode | undefined): TextInputAttribute;
    stopBackPress(value: boolean | undefined): TextInputAttribute;
    onWillChange(value: ((value0: EditableTextChangeValue) => boolean) | undefined): TextInputAttribute;
    keyboardAppearance(value: KeyboardAppearance | undefined): TextInputAttribute;
    attributeModifier(value: (AttributeModifier<TextInputAttribute>|AttributeModifier<CommonMethod>) | undefined): TextInputAttribute;
    inputFilter(value: ResourceStr | undefined, error?: ((value0: string) => void) | undefined): TextInputAttribute;
    customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions | undefined): TextInputAttribute;
    showCounter(value: boolean | undefined, options?: InputCounterOptions | undefined): TextInputAttribute;
}
declare interface TextInputInterface {
    (value?: TextInputOptions): TextInputAttribute;
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
    value?: (ResourceStr|ResourceStr[]);
    selected?: (number|number[]);
    columnWidths?: LengthMetrics[];
}
declare interface DividerOptions {
    strokeWidth?: Dimension;
    color?: ResourceColor;
    startMargin?: Dimension;
    endMargin?: Dimension;
}
declare interface TextPickerTextStyle extends PickerTextStyle {
    minFontSize?: (number|string|Resource);
    maxFontSize?: (number|string|Resource);
    overflow?: TextOverflow;
}
declare type TextPickerScrollStopCallback = ((value: (string|string[]), index: (number|number[])) => void);
declare type OnTextPickerChangeCallback = ((selectItem: (string|string[]), index: (number|number[])) => void);
declare type TextPickerEnterSelectedAreaCallback = ((value: (string|string[]), index: (number|number[])) => void);
declare interface TextPickerAttribute extends CommonMethod {
    defaultPickerItemHeight(value: (number|string) | undefined): TextPickerAttribute;
    canLoop(value: boolean | undefined): TextPickerAttribute;
    disappearTextStyle(value: PickerTextStyle | undefined): TextPickerAttribute;
    textStyle(value: PickerTextStyle | undefined): TextPickerAttribute;
    selectedTextStyle(value: PickerTextStyle | undefined): TextPickerAttribute;
    disableTextStyleAnimation(value: boolean | undefined): TextPickerAttribute;
    defaultTextStyle(value: TextPickerTextStyle | undefined): TextPickerAttribute;
    onChange(value: OnTextPickerChangeCallback | undefined): TextPickerAttribute;
    onScrollStop(value: TextPickerScrollStopCallback | undefined): TextPickerAttribute;
    onEnterSelectedArea(value: TextPickerEnterSelectedAreaCallback | undefined): TextPickerAttribute;
    selectedIndex(value: (number|number[]) | undefined): TextPickerAttribute;
    divider(value: DividerOptions | undefined): TextPickerAttribute;
    gradientHeight(value: Dimension | undefined): TextPickerAttribute;
    enableHapticFeedback(value: boolean | undefined): TextPickerAttribute;
    digitalCrownSensitivity(value: CrownSensitivity | undefined): TextPickerAttribute;
    attributeModifier(value: (AttributeModifier<TextPickerAttribute>|AttributeModifier<CommonMethod>) | undefined): TextPickerAttribute;
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
    disableTextStyleAnimation?: boolean;
    defaultTextStyle?: TextPickerTextStyle;
    onAccept?: ((value: TextPickerResult) => void);
    onCancel?: (() => void);
    onChange?: ((value: TextPickerResult) => void);
    onScrollStop?: ((value: TextPickerResult) => void);
    onEnterSelectedArea?: ((value: TextPickerResult) => void);
    maskRect?: Rectangle;
    alignment?: DialogAlignment;
    offset?: Offset;
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    onDidAppear?: (() => void);
    onDidDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
    shadow?: (ShadowOptions|ShadowStyle);
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    enableHapticFeedback?: boolean;
}
declare class TextPickerDialog {
    constructor();
}
declare interface TextPickerInterface {
    (options?: TextPickerOptions): TextPickerAttribute;
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
declare interface TextTimerAttribute extends CommonMethod {
    format(value: string | undefined): TextTimerAttribute;
    fontColor(value: ResourceColor | undefined): TextTimerAttribute;
    fontSize(value: Length | undefined): TextTimerAttribute;
    fontStyle(value: FontStyle | undefined): TextTimerAttribute;
    fontWeight(value: (number|FontWeight|ResourceStr) | undefined): TextTimerAttribute;
    fontFamily(value: ResourceStr | undefined): TextTimerAttribute;
    onTimer(value: ((utc: number, elapsedTime: number) => void) | undefined): TextTimerAttribute;
    textShadow(value: (ShadowOptions|ShadowOptions[]) | undefined): TextTimerAttribute;
    contentModifier(value: ContentModifier<TextTimerConfiguration> | undefined): TextTimerAttribute;
    attributeModifier(value: (AttributeModifier<TextTimerAttribute>|AttributeModifier<CommonMethod>) | undefined): TextTimerAttribute;
}
declare interface TextTimerInterface {
    (options?: TextTimerOptions): TextTimerAttribute;
}
declare interface TimePickerResult {
    hour: number;
    minute: number;
    second: number;
}
declare enum TimePickerFormat {
    HOUR_MINUTE,
    HOUR_MINUTE_SECOND = 1,
}
declare interface TimePickerOptions {
    selected?: Date;
    format?: TimePickerFormat;
    start?: Date;
    end?: Date;
}
declare type OnTimePickerChangeCallback = ((result: TimePickerResult) => void);
declare type Callback_TimePickerResult_Void = ((value0: TimePickerResult) => void);
declare interface TimePickerAttribute extends CommonMethod {
    useMilitaryTime(value: boolean | undefined): TimePickerAttribute;
    loop(value: boolean | undefined): TimePickerAttribute;
    disappearTextStyle(value: PickerTextStyle | undefined): TimePickerAttribute;
    textStyle(value: PickerTextStyle | undefined): TimePickerAttribute;
    selectedTextStyle(value: PickerTextStyle | undefined): TimePickerAttribute;
    dateTimeOptions(value: intl.DateTimeOptions | undefined): TimePickerAttribute;
    onChange(value: OnTimePickerChangeCallback | undefined): TimePickerAttribute;
    onEnterSelectedArea(value: ((value0: TimePickerResult) => void) | undefined): TimePickerAttribute;
    enableHapticFeedback(value: boolean | undefined): TimePickerAttribute;
    digitalCrownSensitivity(value: CrownSensitivity | undefined): TimePickerAttribute;
    enableCascade(value: boolean | undefined): TimePickerAttribute;
    attributeModifier(value: (AttributeModifier<TimePickerAttribute>|AttributeModifier<CommonMethod>) | undefined): TimePickerAttribute;
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
    onAccept?: ((value0: TimePickerResult) => void);
    onCancel?: (() => void);
    onChange?: ((value0: TimePickerResult) => void);
    onEnterSelectedArea?: ((value0: TimePickerResult) => void);
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    enableCascade?: boolean;
    onDidAppear?: (() => void);
    onDidDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
    shadow?: (ShadowOptions|ShadowStyle);
    dateTimeOptions?: intl.DateTimeOptions;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    enableHapticFeedback?: boolean;
}
declare class TimePickerDialog {
    constructor();
}
declare interface TimePickerInterface {
    (options?: TimePickerOptions): TimePickerAttribute;
}
declare enum ToggleType {
    CHECKBOX,
    Checkbox,
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
    toggleEnabled: boolean;
    triggerChange: ((value0: boolean) => void);
}
declare interface ToggleOptions {
    type: ToggleType;
    isOn?: boolean | undefined;
}
declare interface ToggleAttribute extends CommonMethod {
    onChange(value: ((value0: boolean) => void) | undefined): ToggleAttribute;
    contentModifier(value: ContentModifier<ToggleConfiguration> | undefined): ToggleAttribute;
    selectedColor(value: ResourceColor | undefined): ToggleAttribute;
    switchPointColor(value: ResourceColor | undefined): ToggleAttribute;
    switchStyle(value: SwitchStyle | undefined): ToggleAttribute;
    attributeModifier(value: (AttributeModifier<ToggleAttribute>|AttributeModifier<CommonMethod>) | undefined): ToggleAttribute;
}
declare interface ToggleInterface {
    (options: ToggleOptions): ToggleAttribute;
}
declare enum DpiFollowStrategy {
    FOLLOW_HOST_DPI,
    FOLLOW_UI_EXTENSION_ABILITY_DPI = 1,
}
declare interface UIExtensionOptions {
    isTransferringCaller?: boolean;
    placeholder?: ComponentContent;
    areaChangePlaceholder?: Map<string,ComponentContent>;
    dpiFollowStrategy?: DpiFollowStrategy;
}
declare type Callback_Map_String_Object_Void = ((value0: Map<string,Object>) => void);
declare type ReceiveCallback = ((value0: Map<string,Object>) => void);
declare type Callback_UIExtensionProxy_Void = ((value0: UIExtensionProxy) => void);
declare interface UIExtensionProxy {
    send(data: Map<string,Object>): void;
    sendSync(data: Map<string,Object>): Map<string,Object>;
    on(type: 'asyncReceiverRegister', callback_: ((value0: UIExtensionProxy) => void)): void;
    on(type: 'syncReceiverRegister', callback_: ((value0: UIExtensionProxy) => void)): void;
    off(type: 'asyncReceiverRegister', callback_?: ((value0: UIExtensionProxy) => void)): void;
    off(type: 'syncReceiverRegister', callback_?: ((value0: UIExtensionProxy) => void)): void;
}
declare interface UIExtensionComponentAttribute extends CommonMethod {
    onRemoteReady(value: ((value0: UIExtensionProxy) => void) | undefined): UIExtensionComponentAttribute;
    onReceive(value: ((value0: Map<string,Object>) => void) | undefined): UIExtensionComponentAttribute;
    onError(value: ErrorCallback | undefined): UIExtensionComponentAttribute;
    onTerminated(value: ((value0: TerminationInfo) => void) | undefined): UIExtensionComponentAttribute;
    attributeModifier(value: (AttributeModifier<UIExtensionComponentAttribute>|AttributeModifier<CommonMethod>) | undefined): UIExtensionComponentAttribute;
}
declare interface UIExtensionComponentInterface {
    (want: Want, options?: UIExtensionOptions): UIExtensionComponentAttribute;
}
declare type Length = (string|number|Resource);
declare type PX = string;
declare type VP = (string|number);
declare type FP = string;
declare type LPX = string;
declare type Percentage = string;
declare type Degree = string;
declare type Dimension = (string|number|Resource);
declare type ResourceStr = (string|Resource);
declare interface Padding {
    top?: Length;
    right?: Length;
    bottom?: Length;
    left?: Length;
}
declare interface LocalizedPadding {
    top?: LengthMetrics;
    end?: LengthMetrics;
    bottom?: LengthMetrics;
    start?: LengthMetrics;
}
declare type Margin = Padding;
declare type EdgeWidth = EdgeWidths;
declare interface EdgeWidths {
    top?: Length;
    right?: Length;
    bottom?: Length;
    left?: Length;
}
declare interface LocalizedEdgeWidths {
    top?: LengthMetrics;
    end?: LengthMetrics;
    bottom?: LengthMetrics;
    start?: LengthMetrics;
}
declare interface EdgeOutlineWidths {
    top?: Dimension;
    right?: Dimension;
    bottom?: Dimension;
    left?: Dimension;
}
declare interface BorderRadiuses {
    topLeft?: Length;
    topRight?: Length;
    bottomLeft?: Length;
    bottomRight?: Length;
}
declare interface LocalizedBorderRadiuses {
    topStart?: LengthMetrics;
    topEnd?: LengthMetrics;
    bottomStart?: LengthMetrics;
    bottomEnd?: LengthMetrics;
}
declare interface OutlineRadiuses {
    topLeft?: Dimension;
    topRight?: Dimension;
    bottomLeft?: Dimension;
    bottomRight?: Dimension;
}
declare interface EdgeColors {
    top?: ResourceColor;
    right?: ResourceColor;
    bottom?: ResourceColor;
    left?: ResourceColor;
}
declare interface LocalizedEdgeColors {
    top?: ResourceColor;
    end?: ResourceColor;
    bottom?: ResourceColor;
    start?: ResourceColor;
}
declare type LocalizedMargin = LocalizedPadding;
declare interface EdgeStyles {
    top?: BorderStyle;
    right?: BorderStyle;
    bottom?: BorderStyle;
    left?: BorderStyle;
}
declare interface EdgeOutlineStyles {
    top?: OutlineStyle;
    right?: OutlineStyle;
    bottom?: OutlineStyle;
    left?: OutlineStyle;
}
declare type ResourceColor = (Color|number|string|Resource);
declare interface LengthConstrain {
    minLength: Length;
    maxLength: Length;
}
declare type VoidCallback = (() => void);
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
    mode?: DividerMode;
}
declare interface ChainWeightOptions {
    horizontal?: number;
    vertical?: number;
}
declare interface AccessibilityOptions {
    accessibilityPreferred?: boolean;
}
declare enum SeekMode {
    PREVIOUS_KEYFRAME,
    PreviousKeyframe,
    NEXT_KEYFRAME = 1,
    NextKeyframe = 1,
    CLOSEST_KEYFRAME = 2,
    ClosestKeyframe = 2,
    ACCURATE = 3,
    Accurate = 3,
}
declare enum PlaybackSpeed {
    SPEED_FORWARD_0_75_X,
    Speed_Forward_0_75_X,
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
declare interface PosterOptions {
    showFirstFrame?: boolean;
}
declare interface VideoOptions {
    src?: (string|Resource);
    currentProgressRate?: (number|string|PlaybackSpeed);
    previewUri?: (string|image.PixelMap|Resource);
    controller?: VideoController;
    imageAIOptions?: ImageAIOptions;
    posterOptions?: PosterOptions;
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
declare type Callback_FullscreenInfo_Void = ((value0: FullscreenInfo) => void);
declare type Callback_PreparedInfo_Void = ((value0: PreparedInfo) => void);
declare type Callback_PlaybackInfo_Void = ((value0: PlaybackInfo) => void);
declare interface VideoAttribute extends CommonMethod {
    muted(value: boolean | undefined): VideoAttribute;
    autoPlay(value: boolean | undefined): VideoAttribute;
    controls(value: boolean | undefined): VideoAttribute;
    loop(value: boolean | undefined): VideoAttribute;
    objectFit(value: ImageFit | undefined): VideoAttribute;
    onStart(value: VoidCallback | undefined): VideoAttribute;
    onPause(value: VoidCallback | undefined): VideoAttribute;
    onFinish(value: VoidCallback | undefined): VideoAttribute;
    onFullscreenChange(value: ((value0: FullscreenInfo) => void) | undefined): VideoAttribute;
    onPrepared(value: ((value0: PreparedInfo) => void) | undefined): VideoAttribute;
    onSeeking(value: ((value0: PlaybackInfo) => void) | undefined): VideoAttribute;
    onSeeked(value: ((value0: PlaybackInfo) => void) | undefined): VideoAttribute;
    onUpdate(value: ((value0: PlaybackInfo) => void) | undefined): VideoAttribute;
    onError(value: (() => void) | undefined): VideoAttribute;
    onStop(value: (() => void) | undefined): VideoAttribute;
    enableAnalyzer(value: boolean | undefined): VideoAttribute;
    analyzerConfig(value: ImageAnalyzerConfig | undefined): VideoAttribute;
    surfaceBackgroundColor(value: ColorMetrics | undefined): VideoAttribute;
    enableShortcutKey(value: boolean | undefined): VideoAttribute;
    attributeModifier(value: (AttributeModifier<VideoAttribute>|AttributeModifier<CommonMethod>) | undefined): VideoAttribute;
}
declare interface VideoInterface {
    (value: VideoOptions): VideoAttribute;
}
declare type GetItemMainSizeByIndex = ((index: number) => number);
declare class SectionOptions {
    constructor();
    itemsCount: number;
    crossCount?: number | undefined;
    onGetItemMainSizeByIndex?: GetItemMainSizeByIndex | undefined;
    columnsGap?: Dimension | undefined;
    rowsGap?: Dimension | undefined;
    margin?: (Padding|Dimension) | undefined;
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
    ALWAYS_TOP_DOWN,
    SLIDING_WINDOW = 1,
}
declare interface WaterFlowOptions {
    footer?: CustomBuilder;
    footerContent?: ComponentContent;
    scroller?: Scroller;
    sections?: WaterFlowSections;
    layoutMode?: WaterFlowLayoutMode;
}
declare interface WaterFlowAttribute extends ScrollableCommonMethod {
    columnsTemplate(value: string | undefined): WaterFlowAttribute;
    itemConstraintSize(value: ConstraintSizeOptions | undefined): WaterFlowAttribute;
    rowsTemplate(value: string | undefined): WaterFlowAttribute;
    columnsGap(value: Length | undefined): WaterFlowAttribute;
    rowsGap(value: Length | undefined): WaterFlowAttribute;
    layoutDirection(value: FlexDirection | undefined): WaterFlowAttribute;
    cachedCount(value: number | undefined): WaterFlowAttribute;
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): WaterFlowAttribute;
    onScrollIndex(value: ((first: number, last: number) => void) | undefined): WaterFlowAttribute;
    onWillScroll(value: OnWillScrollCallback | undefined): WaterFlowAttribute;
    onDidScroll(value: OnScrollCallback | undefined): WaterFlowAttribute;
    attributeModifier(value: (AttributeModifier<WaterFlowAttribute>|AttributeModifier<CommonMethod>) | undefined): WaterFlowAttribute;
    cachedCount(count: number | undefined, show: boolean | undefined): WaterFlowAttribute;
}
declare interface WaterFlowInterface {
    (options?: WaterFlowOptions): WaterFlowAttribute;
}
declare interface WindowSceneAttribute extends CommonMethod {
    attributeModifier(value: (AttributeModifier<WindowSceneAttribute>|AttributeModifier<CommonMethod>) | undefined): WindowSceneAttribute;
    attractionEffect(destination: Position | undefined, fraction: number | undefined): WindowSceneAttribute;
}
declare interface WindowSceneInterface {
    (persistentId: number): WindowSceneAttribute;
}
declare interface WithThemeOptions {
    theme?: CustomTheme;
    colorMode?: ThemeColorMode;
}
declare interface WithThemeAttribute {
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
declare type Callback_String_SurfaceRect_Void = ((surfaceId: string, rect: SurfaceRect) => void);
declare class XComponentController {
    constructor();
    onSurfaceCreated: ((surfaceId: string) => void);
    onSurfaceChanged: ((surfaceId: string, rect: SurfaceRect) => void);
    onSurfaceDestroyed: ((surfaceId: string) => void);
    getXComponentSurfaceId(): string;
    getXComponentContext(): Object;
    setXComponentSurfaceRect(rect: SurfaceRect): void;
    getXComponentSurfaceRect(): SurfaceRect;
    setXComponentSurfaceRotation(rotationOptions: SurfaceRotationOptions): void;
    getXComponentSurfaceRotation(): SurfaceRotationOptions;
    startImageAnalyzer(config: ImageAnalyzerConfig): Promise<void>;
    stopImageAnalyzer(): void;
}
declare interface XComponentOptions {
    type: XComponentType;
    controller: XComponentController;
    imageAIOptions?: ImageAIOptions;
    screenId?: number;
}
declare interface NativeXComponentParameters {
    type: XComponentType;
    imageAIOptions?: ImageAIOptions;
}
declare type OnNativeLoadCallback = ((event?: Object) => void);
declare interface XComponentAttribute extends CommonMethod {
    onLoad(value: OnNativeLoadCallback | undefined): XComponentAttribute;
    onDestroy(value: VoidCallback | undefined): XComponentAttribute;
    enableAnalyzer(value: boolean | undefined): XComponentAttribute;
    enableSecure(value: boolean | undefined): XComponentAttribute;
    hdrBrightness(value: number | undefined): XComponentAttribute;
    enableTransparentLayer(value: boolean | undefined): XComponentAttribute;
    attributeModifier(value: (AttributeModifier<XComponentAttribute>|AttributeModifier<CommonMethod>) | undefined): XComponentAttribute;
}
declare interface XComponentParameter {
    id: string;
    type: XComponentType;
    libraryname?: string;
    controller?: XComponentController;
}
declare interface XComponentInterface {
    (value: XComponentParameter): XComponentAttribute;
    (options: XComponentOptions): XComponentAttribute;
    (params: NativeXComponentParameters): XComponentAttribute;
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
    static SetClipRect(node: number|bigint, x: number, y: number, width: number, height: number): void;
    static OpenImplicitAnimation(param: AnimateParam): void;
    static CloseImplicitAnimation(): void;
    static StartDoubleAnimation(node: number|bigint, param: DoubleAnimationParam): void;
    static AnimationTranslate(node: number|bigint, options: TranslateOptions): void;
}
declare interface ComponentInfo {
    size: Size;
    localOffset: Offset_componentutils;
    windowOffset: Offset_componentutils;
    screenOffset: Offset_componentutils;
    translate: TranslateResult;
    scale: ScaleResult;
    rotate: RotateResult;
    transform: Matrix4Result;
}
declare interface Offset_componentutils {
    x: number;
    y: number;
}
declare interface TranslateResult {
    x: number;
    y: number;
    z: number;
}
declare interface ScaleResult {
    x: number;
    y: number;
    z: number;
    centerX: number;
    centerY: number;
}
declare interface RotateResult {
    x: number;
    y: number;
    z: number;
    centerX: number;
    centerY: number;
    angle: number;
}
declare type Matrix4Result = [ number, number, number, number, number, number, number, number, number, number, number, number, number, number, number, number ]
declare function getRectangleById(id: string): ComponentInfo;
declare type ButtonModifierBuilder = ((parentNode: number|bigint, config: ButtonConfiguration) => number|bigint);
declare type CheckBoxModifierBuilder = ((parentNode: number|bigint, config: CheckBoxConfiguration) => number|bigint);
declare type DataPanelModifierBuilder = ((parentNode: number|bigint, config: DataPanelConfiguration) => number|bigint);
declare type GaugeModifierBuilder = ((parentNode: number|bigint, config: GaugeConfiguration) => number|bigint);
declare type LoadingProgressModifierBuilder = ((parentNode: number|bigint, config: LoadingProgressConfiguration) => number|bigint);
declare type ProgressModifierBuilder = ((parentNode: number|bigint, config: ProgressConfiguration) => number|bigint);
declare type RadioModifierBuilder = ((parentNode: number|bigint, config: RadioConfiguration) => number|bigint);
declare type RatingModifierBuilder = ((parentNode: number|bigint, config: RatingConfiguration) => number|bigint);
declare type MenuItemModifierBuilder = ((parentNode: number|bigint, config: MenuItemConfiguration) => number|bigint);
declare type SliderModifierBuilder = ((parentNode: number|bigint, config: SliderConfiguration) => number|bigint);
declare type TextClockModifierBuilder = ((parentNode: number|bigint, config: TextClockConfiguration) => number|bigint);
declare type TextTimerModifierBuilder = ((parentNode: number|bigint, config: TextTimerConfiguration) => number|bigint);
declare type ToggleModifierBuilder = ((parentNode: number|bigint, config: ToggleConfiguration) => number|bigint);
declare class ContentModifierHelper {
    static contentModifierButton(node: number|bigint, contentModifier: ContentModifier<ButtonConfiguration>, builder: ((parentNode: number|bigint, config: ButtonConfiguration) => number|bigint)): void;
    static contentModifierCheckBox(node: number|bigint, contentModifier: ContentModifier<CheckBoxConfiguration>, builder: ((parentNode: number|bigint, config: CheckBoxConfiguration) => number|bigint)): void;
    static contentModifierDataPanel(node: number|bigint, contentModifier: ContentModifier<DataPanelConfiguration>, builder: ((parentNode: number|bigint, config: DataPanelConfiguration) => number|bigint)): void;
    static contentModifierGauge(node: number|bigint, contentModifier: ContentModifier<GaugeConfiguration>, builder: ((parentNode: number|bigint, config: GaugeConfiguration) => number|bigint)): void;
    static contentModifierLoadingProgress(node: number|bigint, contentModifier: ContentModifier<LoadingProgressConfiguration>, builder: ((parentNode: number|bigint, config: LoadingProgressConfiguration) => number|bigint)): void;
    static contentModifierProgress(node: number|bigint, contentModifier: ContentModifier<ProgressConfiguration>, builder: ((parentNode: number|bigint, config: ProgressConfiguration) => number|bigint)): void;
    static contentModifierRadio(node: number|bigint, contentModifier: ContentModifier<RadioConfiguration>, builder: ((parentNode: number|bigint, config: RadioConfiguration) => number|bigint)): void;
    static contentModifierRating(node: number|bigint, contentModifier: ContentModifier<RatingConfiguration>, builder: ((parentNode: number|bigint, config: RatingConfiguration) => number|bigint)): void;
    static contentModifierMenuItem(node: number|bigint, contentModifier: ContentModifier<MenuItemConfiguration>, builder: ((parentNode: number|bigint, config: MenuItemConfiguration) => number|bigint)): void;
    static contentModifierSlider(node: number|bigint, contentModifier: ContentModifier<SliderConfiguration>, builder: ((parentNode: number|bigint, config: SliderConfiguration) => number|bigint)): void;
    static contentModifierTextClock(node: number|bigint, contentModifier: ContentModifier<TextClockConfiguration>, builder: ((parentNode: number|bigint, config: TextClockConfiguration) => number|bigint)): void;
    static contentModifierTextTimer(node: number|bigint, contentModifier: ContentModifier<TextTimerConfiguration>, builder: ((parentNode: number|bigint, config: TextTimerConfiguration) => number|bigint)): void;
    static contentModifierToggle(node: number|bigint, contentModifier: ContentModifier<ToggleConfiguration>, builder: ((parentNode: number|bigint, config: ToggleConfiguration) => number|bigint)): void;
}
declare interface CustomDialogBuildOptions {
    controller?: CustomDialogController;
}
declare interface CustomDialogControllerBuilder {
    buildOptions: CustomDialogBuildOptions;
    build: CustomBuilder;
}
declare type Callback_RangeUpdate = ((start: number, end: number) => void);
declare type Callback_CreateItem = ((index: number) => number|bigint);
declare class LazyForEachOps {
    static Sync(node: number|bigint, totalCount: number, creator: Callback_CreateItem, updater: Callback_RangeUpdate): void;
}
declare class SystemOps {
    static StartFrame(): number|bigint;
    static EndFrame(root: number|bigint): void;
    static syncInstanceId(instanceId: number): void;
    static restoreInstanceId(): void;
    static getResourceId(bundleName: string, moduleName: string, params: string[]): number;
    static resourceManagerReset(): void;
    static setFrameCallback(onFrameCallback: ((value0: number) => void), onIdleCallback: ((value0: number) => void), delayTime: number): void;
}
declare class FocusController {
    static requestFocus(key: string): void;
}
declare class Scene {
    static load(uri?: ResourceStr): Promise<Scene>;
    destroy(): void;
}
declare interface WorkerOptions {
    type?: string;
    name?: string;
    shared?: boolean;
}
declare interface Event {
    readonly type: string;
    readonly timeStamp: number;
}
declare interface ErrorEvent extends Event {
    readonly message: string;
    readonly filename: string;
    readonly lineno: number;
    readonly colno: number;
    readonly error: Object;
}
declare interface MessageEvents extends Event {
    readonly data: any;
}
declare interface WorkerEventListener {
    (event: Event): Promise<void>;
}
declare interface PostMessageOptions {
    transfer?: Object[];
}
declare type RestrictedWorker_onexit_Callback = ((code: number) => void);
declare type RestrictedWorker_onerror_Callback = ((ev: ErrorEvent) => void);
declare type RestrictedWorker_onmessage_Callback = ((event: MessageEvents) => void);
declare class RestrictedWorker {
    constructor(scriptURL: string, options?: WorkerOptions);
    onexit?: RestrictedWorker_onexit_Callback;
    onerror?: RestrictedWorker_onerror_Callback;
    onmessage?: RestrictedWorker_onmessage_Callback;
    onmessageerror?: RestrictedWorker_onmessage_Callback;
    postMessage(message: Object, transfer: ArrayBuffer[]): void;
    postMessage(message: Object, options?: PostMessageOptions): void;
    postMessageWithSharedSendable(message: Object, transfer?: ArrayBuffer[]): void;
    on(Type: string, listener: WorkerEventListener): void;
    once(Type: string, listener: WorkerEventListener): void;
    off(Type: string, listener?: WorkerEventListener): void;
    terminate(): void;
    addEventListener(Type: string, listener: WorkerEventListener): void;
    dispatchEvent(event: Event): boolean;
    removeEventListener(Type: string, callback_?: WorkerEventListener): void;
    removeAllListener(): void;
    registerGlobalCallObject(instanceName: string, globalCallObject: Object): void;
    unregisterGlobalCallObject(instanceName?: string): void;
}
declare type Callback_StateStylesChange = ((currentState: number) => void);
declare class StateStylesOps {
    static onStateStyleChange(node: number|bigint, stateStyleChange: Callback_StateStylesChange): void;
}
declare class UIContextAtomicServiceBar {
    static getBarRect(): Frame;
}
declare interface WebHeader {
    headerKey: string;
    headerValue: string;
}
declare interface SnapshotOptions {
    scale?: number;
    waitUntilRenderFinished?: boolean;
}
declare type AsyncCallback_image_PixelMap_Void = ((result: image.PixelMap) => void);
declare class GlobalScope_ohos_arkui_componentSnapshot {
    static get(id: string, callback_: ((result: image.PixelMap) => void), options?: SnapshotOptions): void;
}
declare enum PerfMonitorActionType {
    LAST_DOWN,
    LAST_UP = 1,
    FIRST_MOVE = 2,
}
declare enum PerfMonitorSourceType {
    PERF_TOUCH_EVENT,
    PERF_MOUSE_EVENT = 1,
    PERF_TOUCHPAD_EVENT = 2,
    PERF_JOYSTICK_EVENT = 3,
    PERF_KEY_EVENT = 4,
}
declare class GlobalScope_ohos_arkui_performanceMonitor {
    static begin(scene: string, startInputType: PerfMonitorActionType, note?: string): void;
    static end(scene: string): void;
    static recordInputEventTime(actionType: PerfMonitorActionType, sourceType: PerfMonitorSourceType, time: number): void;
}
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
declare interface FontOptions {
    familyName: (string|Resource);
    familySrc: (string|Resource);
}
declare class GlobalScope_ohos_font {
    static registerFont(options: FontOptions): void;
    static getSystemFontList(): string[];
    static getFontByName(fontName: string): FontInfo;
}
declare interface MeasureOptions {
    textContent: (string|Resource);
    constraintWidth?: (number|string|Resource);
    fontSize?: (number|string|Resource);
    fontStyle?: (number|FontStyle);
    fontWeight?: (number|string|FontWeight);
    fontFamily?: (string|Resource);
    letterSpacing?: (number|string);
    textAlign?: text.TextAlign;
    overflow?: (number|TextOverflow);
    maxLines?: number;
    lineHeight?: (number|string|Resource);
    baselineOffset?: (number|string);
    textCase?: (number|TextCase);
    textIndent?: (number|string);
    wordBreak?: text.WordBreak;
}
declare class GlobalScope_ohos_measure_utils {
    static measureText(options: MeasureOptions): number;
    static measureTextSize(options: MeasureOptions): SizeOptions;
}
declare interface FontInfo {
    path: string;
    postScriptName: string;
    fullName: string;
    family: string;
    subfamily: string;
    weight: number;
    width: number;
    italic: boolean;
    monoSpace: boolean;
    symbolic: boolean;
}
declare interface IndicatorStyle {
    height?: Length;
    width?: Length;
    borderRadius?: Length;
    marginTop?: Length;
    color?: ResourceColor;
    selectedColor?: ResourceColor;
    left?: Length;
    top?: Length;
    right?: Length;
    bottom?: Length;
    size?: Length;
    mask?: boolean;
}
declare class IUIContext {
    static freezeUINode(id: string, isFrozen: boolean): void;
    static freezeUINode(id: number, isFrozen: boolean): void;
}
declare type CustomNodeBuilder = ((parentNode: number|bigint) => number|bigint);
declare type NavExtender_OnUpdateStack = (() => void);
declare class NavExtender {
    static setNavigationOptions(ptr: number|bigint, pathStack: NavPathStack): void;
    static setUpdateStackCallback(peer: NavPathStack, callback_: NavExtender_OnUpdateStack): void;
    static syncStack(peer: NavPathStack): void;
    static checkNeedCreate(navigation: number|bigint, index: number): boolean;
    static setNavDestinationNode(peer: NavPathStack, index: number, node: number|bigint): void;
    static pushPath(pathStack: NavPathStack, info: NavPathInfo, options: NavigationOptions): void;
    static replacePath(pathStack: NavPathStack, info: NavPathInfo, options: NavigationOptions): void;
    static pop(pathStack: NavPathStack, animated: boolean): string;
    static setOnPopCallback(pathStack: NavPathStack, popCallback: ((breakpoints: string) => void)): void;
    static getIdByIndex(pathStack: NavPathStack, index: number): string;
    static getIdByName(pathStack: NavPathStack, name: string): string[];
    static popToIndex(pathStack: NavPathStack, index: number, animated: boolean): void;
    static popToName(pathStack: NavPathStack, name: string, animated: boolean): number;
}
declare type SearchValueCallback = ((value: string) => void);
declare class SearchOps {
    static registerSearchValueCallback(node: number|bigint, value: string, callback_: SearchValueCallback): number|bigint;
}
declare interface Root {
}
declare interface ComponentRoot {
}
declare type Callback_onMeasureSize_SizeResult = ((selfLayoutInfo: GeometryInfo, children: Measurable[], constraint: ConstraintSizeOptions) => SizeResult);
declare type Callback_onPlaceChildren_Void = ((selfLayoutInfo: GeometryInfo, children: Layoutable[], constraint: ConstraintSizeOptions) => void);
declare interface CustomLayoutRoot {
    subscribeOnMeasureSize(value: Callback_onMeasureSize_SizeResult): CustomLayoutRoot;
    subscribeOnPlaceChildren(value: Callback_onPlaceChildren_Void): CustomLayoutRoot;
}
declare class EventEmulator {
    static emitClickEvent(node: number|bigint, event: ClickEvent): void;
    static emitTextInputEvent(node: number|bigint, text: string): void;
}
declare type TextFieldValueCallback = ((value: ResourceStr) => void);
declare class TextFieldOps {
    static registerTextFieldValueCallback(node: number|bigint, value: ResourceStr, callback_: TextFieldValueCallback): number|bigint;
}
declare interface TransformationMatrix {
    matrix4x4: number[];
}
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
declare const GridCol: GridColInterface
declare const GridColInstance: GridColAttribute
declare const GridItem: GridItemInterface
declare const GridItemInstance: GridItemAttribute
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
declare const IndicatorComponent: IndicatorComponentInterface
declare const IndicatorComponentInstance: IndicatorComponentAttribute
declare const Line: LineInterface
declare const LineInstance: LineAttribute
declare const LinearIndicator: LinearIndicatorInterface
declare const LinearIndicatorInstance: LinearIndicatorAttribute
declare const List: ListInterface
declare const ListInstance: ListAttribute
declare const ListItem: ListItemInterface
declare const ListItemInstance: ListItemAttribute
declare const ListItemGroup: ListItemGroupInterface
declare const ListItemGroupInstance: ListItemGroupAttribute
declare const LoadingProgress: LoadingProgressInterface
declare const LoadingProgressInstance: LoadingProgressAttribute
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
declare const Navigation: NavigationInterface
declare const NavigationInstance: NavigationAttribute
declare const NodeContainer: NodeContainerInterface
declare const NodeContainerInstance: NodeContainerAttribute
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
declare const RemoteWindow: RemoteWindowInterface
declare const RemoteWindowInstance: RemoteWindowAttribute
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
declare const SideBarContainer: SideBarContainerInterface
declare const SideBarContainerInstance: SideBarContainerAttribute
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
declare const SymbolGlyph: SymbolGlyphInterface
declare const SymbolGlyphInstance: SymbolGlyphAttribute
declare const SymbolSpan: SymbolSpanInterface
declare const SymbolSpanInstance: SymbolSpanAttribute
declare const TabContent: TabContentInterface
declare const TabContentInstance: TabContentAttribute
declare const Tabs: TabsInterface
declare const TabsInstance: TabsAttribute
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
declare const UIExtensionComponent: UIExtensionComponentInterface
declare const UIExtensionComponentInstance: UIExtensionComponentAttribute
declare const Video: VideoInterface
declare const VideoInstance: VideoAttribute
declare const WaterFlow: WaterFlowInterface
declare const WaterFlowInstance: WaterFlowAttribute
declare const WindowScene: WindowSceneInterface
declare const WindowSceneInstance: WindowSceneAttribute
declare const XComponent: XComponentInterface
declare const XComponentInstance: XComponentAttribute