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
declare type KNode = number | null;
declare function getUINativeModule(): any;
declare enum ModifierType {
    ORIGIN = 0,
    STATE = 1,
    FRAME_NODE = 2,
    EXPOSE_MODIFIER = 3,
}
declare class ArkLogConsole {
  public static log(...args: Object[]): void;
  public static debug(...args: Object[]): void;
  public static info(...args: Object[]): void;
  public static warn(...args: Object[]): void;
  public static error(...args: Object[]): void;
}
declare class JsPointerClass {
    invalid(): boolean;
}
interface Equable {
    isEqual(value: Equable): boolean;
}
declare type AttributeModifierWithKey = ModifierWithKey<number | string | boolean | object>;
declare class ModifierWithKey<T extends number | string | boolean | object> {
    stageValue?: T;
    value?: T;
    constructor(value: T);
    applyStage(node: KNode): boolean;
    applyPeer(node: KNode, reset: boolean): void;
    checkObjectDiff(): boolean;
}
declare class ArkComponent implements CommonMethod<CommonAttribute> {
    _changed: boolean;
    _modifiersWithKeys: Map<Symbol, AttributeModifierWithKey>;
    nativePtr: KNode;
    _weakPtr: JsPointerClass;
    _classType: ModifierType | undefined;
    _nativePtrChanged: boolean;
    constructor(nativePtr: KNode, classType?: ModifierType);
    initialize(...args: Object[]);
    applyModifierPatch(): void;
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this;
    outline(value: OutlineOptions): this;
    outlineColor(value: ResourceColor | EdgeColors): this;
    outlineRadius(value: Dimension | OutlineRadiuses): this;
    outlineStyle(value: OutlineStyle | EdgeOutlineStyles): this;
    outlineWidth(value: Dimension | EdgeOutlineWidths): this;
    width(value: Length): this;
    height(value: Length): this;
    expandSafeArea(types?: Array<SafeAreaType>, edges?: Array<SafeAreaEdge>): this;
    backgroundEffect(options: BackgroundEffectOptions): this;
    backgroundBrightness(params: BackgroundBrightnessOptions): this;
    backgroundBrightnessInternal(params: BrightnessOptions): this;
    foregroundBrightness(params: BrightnessOptions): this;
    dragPreviewOptions(value: DragPreviewOptions, options?: DragInteractionOptions): this;
    responseRegion(value: Array<Rectangle> | Rectangle): this;
    mouseResponseRegion(value: Array<Rectangle> | Rectangle): this;
    size(value: SizeOptions): this;
    constraintSize(value: ConstraintSizeOptions): this;
    touchable(value: boolean): this;
    hitTestBehavior(value: HitTestMode): this;
    layoutWeight(value: number | string): this;
    padding(value: Padding | Length): this;
    safeAreaPadding(value: Padding | LengthMetrics | LocalizedPadding): this;
    margin(value: Margin | Length): this;
    background(builder: CustomBuilder, options?: {
        align?: Alignment;
    }): this;
    backgroundColor(value: ResourceColor): this;
    backgroundImage(src: ResourceStr, repeat?: ImageRepeat): this;
    backgroundImageSize(value: SizeOptions | ImageSize): this;
    backgroundImagePosition(value: Position | Alignment): this;
    backgroundBlurStyle(value: BlurStyle, options?: BackgroundBlurStyleOptions): this;
    foregroundBlurStyle(value: BlurStyle, options?: ForegroundBlurStyleOptions): this;
    opacity(value: number | Resource): this;
    border(value: BorderOptions): this;
    borderStyle(value: BorderStyle | EdgeStyles): this;
    borderWidth(value: Length | EdgeWidths): this;
    borderColor(value: ResourceColor | EdgeColors): this;
    borderRadius(value: Length | BorderRadiuses): this;
    borderImage(value: BorderImageOption): this;
    foregroundColor(value: ResourceColor | ColoringStrategy): this;
    onClick(event: (event?: ClickEvent) => void): this;
    onHover(event: (isHover?: boolean, event?: HoverEvent) => void): this;
    hoverEffect(value: HoverEffect): this;
    onMouse(event: (event?: MouseEvent) => void): this;
    onTouch(event: (event?: TouchEvent) => void): this;
    onKeyEvent(event: (event?: KeyEvent) => void): this;
    focusable(value: boolean): this;
    tabStop(value: boolean): this;
    onFocus(event: () => void): this;
    onBlur(event: () => void): this;
    tabIndex(index: number): this;
    defaultFocus(value: boolean): this;
    groupDefaultFocus(value: boolean): this;
    focusOnTouch(value: boolean): this;
    animation(value: AnimateParam): this;
    transition(value: TransitionOptions | TransitionEffect): this;
    gesture(gesture: GestureType, mask?: GestureMask): this;
    priorityGesture(gesture: GestureType, mask?: GestureMask): this;
    parallelGesture(gesture: GestureType, mask?: GestureMask): this;
    blur(value: number): this;
    linearGradientBlur(value: number, options: LinearGradientBlurOptions): this;
    brightness(value: number): this;
    contrast(value: number): this;
    grayscale(value: number): this;
    colorBlend(value: Color | string | Resource): this;
    saturate(value: number): this;
    sepia(value: number): this;
    invert(value: number): this;
    hueRotate(value: number | string): this;
    useEffect(value: boolean): this;
    backdropBlur(value: number): this;
    renderGroup(value: boolean): this;
    translate(value: TranslateOptions): this;
    scale(value: ScaleOptions): this;
    gridSpan(value: number): this;
    gridOffset(value: number): this;
    rotate(value: RotateOptions): this;
    transform(value: object): this;
    onAppear(event: () => void): this;
    onDisAppear(event: () => void): this;
    onAreaChange(event: (oldValue: Area, newValue: Area) => void): this;
    visibility(value: Visibility): this;
    flexGrow(value: number): this;
    flexShrink(value: number): this;
    flexBasis(value: number | string): this;
    alignSelf(value: ItemAlign): this;
    displayPriority(value: number): this;
    zIndex(value: number): this;
    sharedTransition(id: string, options?: sharedTransitionOptions): this;
    direction(value: Direction): this;
    align(value: Alignment): this;
    position(value: Position): this;
    markAnchor(value: Position): this;
    offset(value: Position): this;
    enabled(value: boolean): this;
    useShadowBatching(value: boolean): this;
    monopolizeEvents(value: boolean): this;
    useSizeType(value: {
        xs?: number | {
            span: number;
            offset: number;
        };
        sm?: number | {
            span: number;
            offset: number;
        };
        md?: number | {
            span: number;
            offset: number;
        };
        lg?: number | {
            span: number;
            offset: number;
        };
    }): this;
    alignRules(value: AlignRuleOption): this;
    aspectRatio(value: number): this;
    clickEffect(value: ClickEffect | null): this;
    onDragStart(event: (event?: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo): this;
    onDragEnter(event: (event?: DragEvent, extraParams?: string) => void): this;
    onDragSpringLoading(callback: Callback<SpringLoadingContext> | null, configuration?: DragSpringLoadingConfiguration): this;
    onDragMove(event: (event?: DragEvent, extraParams?: string) => void): this;
    onDragLeave(event: (event?: DragEvent, extraParams?: string) => void): this;
    onDrop(event: (event?: DragEvent, extraParams?: string) => void, dropOptions?: DropOptions): this;
    onDragEnd(event: (event: DragEvent, extraParams?: string) => void): this;
    onPreDrag(event: (preDragStatus: PreDragStatus) => void): this;
    allowDrop(value: Array<UniformDataType>): this;
    draggable(value: boolean): this;
    dragPreview(preview: CustomBuilder | DragItemInfo | string): this;
    overlay(value: string | CustomBuilder, options?: {
        align?: Alignment;
        offset?: {
            x?: number;
            y?: number;
        };
    }): this;
    linearGradient(value: {
        angle?: number | string;
        direction?: GradientDirection;
        colors: Array<any>;
        repeating?: boolean;
    }): this;
    sweepGradient(value: {
        center: Array<any>;
        start?: number | string;
        end?: number | string;
        rotation?: number | string;
        colors: Array<any>;
        metricsColors?: Array<any>;
        repeating?: boolean;
    }): this;
    radialGradient(value: {
        center: Array<any>;
        radius: number | string;
        colors: Array<any>;
        repeating?: boolean;
    }): this;
    motionPath(value: MotionPathOptions): this;
    shadow(value: ShadowOptions | ShadowStyle): this;
    mask(value: CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute | ProgressMask): this;
    key(value: string): this;
    id(value: string): this;
    geometryTransition(id: string): this;
    bindPopup(show: boolean, popup: PopupOptions | CustomPopupOptions): this;
    bindTips(message: TipsMessageType, options?: TipsOptions): this;
    bindMenu(content: Array<MenuElement> | CustomBuilder, options?: MenuOptions): this;
    bindContextMenu(content: CustomBuilder, responseType: ResponseType, options?: ContextMenuOptions): this;
    bindContentCover(isShow: boolean, builder: CustomBuilder, type?: ModalTransition | ContentCoverOptions): this;
    blendMode(blendMode: BlendMode, blendApplyType?: BlendApplyType): this;
    clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this;
    bindSheet(isShow: boolean, builder: CustomBuilder, options?: SheetOptions): this;
    stateStyles(value: StateStyles): this;
    restoreId(value: number): this;
    onVisibleAreaChange(ratios: Array<number>, event: (isVisible: boolean, currentRatio: number) => void): this;
    sphericalEffect(value: number): this;
    lightUpEffect(value: number): this;
    pixelStretchEffect(options: PixelStretchEffectOptions): this;
    keyboardShortcut(value: string | FunctionKey, keys: Array<ModifierKey>, action?: () => void): this;
    accessibilityGroup(value: boolean): this;
    accessibilityText(value: string | Resource): this;
    accessibilityDescription(value: string | Resource): this;
    accessibilityLevel(value: string): this;
    obscured(reasons: Array<ObscuredReasons>): this;
    reuseId(id: string): this;
    renderFit(fitMode: RenderFit): this;
    attributeModifier(modifier: AttributeModifier<CommonAttribute>): this;
    systemBarEffect(): this;
}
declare class ArkBlankComponent extends ArkComponent implements CommonMethod<BlankAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
    color(value: ResourceColor): BlankAttribute;
    height(value: Length): this;
}
declare class ArkColumnComponent extends ArkComponent implements CommonMethod<ColumnAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
    alignItems(value: HorizontalAlign): ColumnAttribute;
    justifyContent(value: FlexAlign): ColumnAttribute;
    pointLight(value: PointLightStyle): ColumnAttribute;
}
declare class ArkColumnSplitComponent extends ArkComponent implements CommonMethod<ColumnSplitAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
    resizeable(value: boolean): ColumnSplitAttribute;
    divider(value: ColumnSplitDividerStyle | null): ColumnSplitAttribute;
    clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this;
}
declare class ArkDividerComponent extends ArkComponent implements DividerAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    vertical(value: boolean): DividerAttribute;
    color(value: ResourceColor): DividerAttribute;
    strokeWidth(value: number | string): DividerAttribute;
    lineCap(value: LineCapStyle): DividerAttribute;
}
declare class ArkFlexComponent extends ArkComponent implements FlexAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    pointLight(value: PointLightStyle): this;
}
declare class ArkGridRowComponent extends ArkComponent implements CommonMethod<GridRowAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onBreakpointChange(callback: (breakpoints: string) => void): GridRowAttribute;
    alignItems(value: ItemAlign): GridRowAttribute;
}
declare class ArkGridComponent extends ArkComponent implements GridAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    columnsTemplate(value: string): this;
    rowsTemplate(value: string): this;
    columnsGap(value: Length): this;
    rowsGap(value: Length): this;
    scrollBarWidth(value: string | number): this;
    scrollBarColor(value: string | number | Color): this;
    scrollBar(value: BarState): this;
    onScrollBarUpdate(event: (index: number, offset: number) => ComputedBarAttribute): this;
    onScrollIndex(event: (first: number, last: number) => void): this;
    cachedCount(value: number): this;
    editMode(value: boolean): this;
    multiSelectable(value: boolean): this;
    maxCount(value: number): this;
    minCount(value: number): this;
    cellLength(value: number): this;
    layoutDirection(value: GridDirection): this;
    supportAnimation(value: boolean): this;
    onItemDragStart(event: (event: ItemDragInfo, itemIndex: number) => void | (() => any)): this;
    onItemDragEnter(event: (event: ItemDragInfo) => void): this;
    onItemDragMove(event: (event: ItemDragInfo, itemIndex: number, insertIndex: number) => void): this;
    onItemDragLeave(event: (event: ItemDragInfo, itemIndex: number) => void): this;
    onItemDrop(event: (event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void): this;
    edgeEffect(value: EdgeEffect, options?: EdgeEffectOptions | undefined): this;
    fadingEdge(value: boolean, options?: FadingEdgeOptions | undefined): this;
    nestedScroll(value: NestedScrollOptions): this;
    enableScrollInteraction(value: boolean): this;
    friction(value: number | Resource): this;
    onScroll(event: (scrollOffset: number, scrollState: ScrollState) => void): this;
    onReachStart(event: () => void): this;
    onReachEnd(event: () => void): this;
    onScrollStart(event: () => void): this;
    onScrollStop(event: () => void): this;
    onScrollFrameBegin(event: (offset: number, state: ScrollState) => {
        offsetRemain: number;
    }): this;
    clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this;
    flingSpeedLimit(value: number): this;
    alignItems(value: GridItemAlignment): this;
    onWillScroll(callback: (xOffset: number, yOffset: number,
        scrollState: ScrollState, scrollSource: ScrollSource) => void | OffsetResult): this;
    onDidScroll(callback: (xOffset: number, yOffset: number, scrollState: ScrollState) => void): this;
}
declare class ArkGridColComponent extends ArkComponent implements GridColAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    span(value: number | GridColColumnOption): GridColAttribute;
    gridColOffset(value: number | GridColColumnOption): GridColAttribute;
    order(value: number | GridColColumnOption): GridColAttribute;
}
declare class ImageColorFilterModifier extends ModifierWithKey<ColorFilter | DrawingColorFilter> {
    constructor(value: ColorFilter);
    static identity: Symbol;
    applyPeer(node: KNode, reset: boolean): void;
    checkObjectDiff(): boolean;
}
declare class ArkImageComponent extends ArkComponent implements ImageAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onGestureJudgeBegin(callback: any): this;
    draggable(value: boolean): this;
    edgeAntialiasing(value: number): this;
    alt(value: ResourceStr): this;
    matchTextDirection(value: boolean): this;
    fitOriginalSize(value: boolean): this;
    fillColor(value: ResourceColor): this;
    objectFit(value: ImageFit): this;
    objectRepeat(value: ImageRepeat): this;
    orientation(value: ImageRotateOrientation): this;
    autoResize(value: boolean): this;
    renderMode(value: ImageRenderMode): this;
    interpolation(value: ImageInterpolation): this;
    sourceSize(value: {
        width: number;
        height: number;
    }): this;
    syncLoad(value: boolean): this;
    colorFilter(value: ColorFilter): this;
    copyOption(value: CopyOptions): this;
    borderRadius(value: Length | BorderRadiuses): this;
    onComplete(callback: (event?: {
        width: number;
        height: number;
        componentWidth: number;
        componentHeight: number;
        loadingStatus: number;
        contentWidth: number;
        contentHeight: number;
        contentOffsetX: number;
        contentOffsetY: number;
    }) => void): this;
    onError(callback: (event: {
        componentWidth: number;
        componentHeight: number;
        message: string;
    }) => void): this;
    onFinish(event: () => void): this;
    border(value: BorderOptions): this;
    opacity(value: number | Resource): this;
    transition(value: TransitionOptions | TransitionEffect): this;
    resizable(value: ResizableOptions): this;
}
declare class ImageAnimatorImagesModifier extends ModifierWithKey<Array<ImageFrameInfo>> {
    constructor(value: Array<ImageFrameInfo>);
    static identity: Symbol;
    applyPeer(node: KNode, reset: boolean): void;
    checkObjectDiff(): boolean;
    isEqual(one: ImageFrameInfo, another: ImageFrameInfo): boolean;
    convertImageFrames(value: Array<ImageFrameInfo>): ArkImageFrameInfoToArray;
}
declare class ArkImageAnimatorComponent extends ArkComponent implements CommonMethod<ImageAnimatorAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
    images(value: Array<ImageFrameInfo>): ImageAnimatorAttribute;
    state(value: AnimationStatus): ImageAnimatorAttribute;
    duration(value: number): ImageAnimatorAttribute;
    reverse(value: boolean): ImageAnimatorAttribute;
    fixedSize(value: boolean): ImageAnimatorAttribute;
    preDecode(value: number): ImageAnimatorAttribute;
    fillMode(value: FillMode): ImageAnimatorAttribute;
    iterations(value: number): ImageAnimatorAttribute;
    monitorInvisibleArea(value: boolean): ImageAnimatorAttribute;
    onStart(event: VoidCallback): VideoAttribute;
    onPause(event: VoidCallback): VideoAttribute;
    onFinish(event: VoidCallback): VideoAttribute;
    onFullscreenChange(callback: Callback<FullscreenInfo>): VideoAttribute;
    onPrepared(callback: Callback<PreparedInfo>): VideoAttribute;
    onSeeking(callback: Callback<PlaybackInfo>): VideoAttribute;
    onSeeked(callback: Callback<PlaybackInfo>): VideoAttribute;
    onUpdate(callback: Callback<PlaybackInfo>): VideoAttribute;
    onError(event: VoidCallback | ErrorCallback): VideoAttribute;
    onStop(event: Callback<void>): VideoAttribute;
    enableAnalyzer(enable: boolean): VideoAttribute;
    analyzerConfig(config: ImageAnalyzerConfig): VideoAttribute;
    surfaceBackgroundColor(color: ColorMetrics): VideoAttribute;
    enableShortcutKey(enabled: boolean): VideoAttribute;
}
declare class ArkImageSpanComponent extends ArkComponent implements ImageSpanAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    objectFit(value: ImageFit): ImageSpanAttribute;
    verticalAlign(value: ImageSpanAlignment): ImageSpanAttribute;
    onComplete(callback: (event?: {
        width: number;
        height: number;
        componentWidth: number;
        componentHeight: number;
        loadingStatus: number;
        contentWidth: number;
        contentHeight: number;
        contentOffsetX: number;
        contentOffsetY: number;
    }) => void): ImageSpanAttribute;
    onError(callback: (event: {
        componentWidth: number;
        componentHeight: number;
        message: string;
    }) => void): ImageSpanAttribute;
}
declare class ArkPatternLockComponent extends ArkComponent implements PatternLockAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    sideLength(value: Length): PatternLockAttribute;
    circleRadius(value: Length): PatternLockAttribute;
    regularColor(value: ResourceColor): PatternLockAttribute;
    selectedColor(value: ResourceColor): PatternLockAttribute;
    activeColor(value: ResourceColor): PatternLockAttribute;
    pathColor(value: ResourceColor): PatternLockAttribute;
    pathStrokeWidth(value: number | string): PatternLockAttribute;
    autoReset(value: boolean): PatternLockAttribute;
    onPatternComplete(callback: (input: Array<number>) => void): PatternLockAttribute;
    onDotConnect(callback: any): PatternLockAttribute;
}
declare class ArkRichEditorComponent extends ArkComponent implements CommonMethod<RichEditorAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
    enableDataDetector(enable: boolean): RichEditorAttribute;
    dataDetectorConfig(config: any): RichEditorAttribute;
    copyOptions(value: CopyOptions): RichEditorAttribute;
    onPaste(callback: (event?: PasteEvent) => void): RichEditorAttribute;
    onReady(callback: () => void): RichEditorAttribute;
    onSelect(callback: (value: RichEditorSelection) => void): RichEditorAttribute;
    aboutToIMEInput(callback: (value: RichEditorInsertValue) => boolean): RichEditorAttribute;
    onIMEInputComplete(callback: (value: RichEditorTextSpanResult) => void): RichEditorAttribute;
    aboutToDelete(callback: (value: RichEditorDeleteValue) => boolean): RichEditorAttribute;
    onDeleteComplete(callback: () => void): RichEditorAttribute;
    bindSelectionMenu(spanType: RichEditorSpanType, content: CustomBuilder, responseType: ResponseType, options?: SelectionMenuOptions): RichEditorAttribute;
    customKeyboard(value: CustomBuilder): RichEditorAttribute;
    barState(value: BarState): RichEditorAttribute;
    maxLength(value: number): RichEditorAttribute;
    maxLines(value: number): RichEditorAttribute;
}
declare class ArkRowComponent extends ArkComponent implements RowAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    alignItems(value: VerticalAlign): RowAttribute;
    justifyContent(value: FlexAlign): RowAttribute;
    pointLight(value: PointLightStyle): RowAttribute;
}
declare class ArkRowSplitComponent extends ArkComponent implements RowSplitAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    resizeable(value: boolean): RowSplitAttribute;
    clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this;
}
declare class ArkSearchComponent extends ArkComponent implements CommonMethod<SearchAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onEditChange(callback: (isEditing: boolean) => void): SearchAttribute;
    type(value: SearchType): SearchAttribute;
    maxLength(value: number): SearchAttribute;
    onEditChanged(callback: (isEditing: boolean) => void): SearchAttribute;
    customKeyboard(event: () => void): SearchAttribute;
    showUnit(event: () => void): SearchAttribute;
    onContentScroll(callback: (totalOffsetX: number, totalOffsetY: number) => void): SearchAttribute;
    onChange(callback: (value: string) => void): SearchAttribute;
    onTextSelectionChange(callback: (selectionStart: number, selectionEnd: number) => void): SearchAttribute;
    onCopy(callback: (value: string) => void): SearchAttribute;
    onCut(callback: (value: string) => void): SearchAttribute;
    onSubmit(callback: (value: string) => void): SearchAttribute;
    onPaste(callback: (value: string) => void): SearchAttribute;
    showCounter(value: boolean): SearchAttribute;
    searchButton(value: string, option?: SearchButtonOptions): SearchAttribute;
    selectionMenuHidden(value: boolean): SearchAttribute;
    enableKeyboardOnFocus(value: boolean): SearchAttribute;
    caretStyle(value: CaretStyle): SearchAttribute;
    cancelButton(value: {
        style?: CancelButtonStyle;
        icon?: IconOptions;
    }): SearchAttribute;
    searchIcon(value: IconOptions): SearchAttribute;
    fontColor(value: ResourceColor): SearchAttribute;
    placeholderColor(value: ResourceColor): SearchAttribute;
    placeholderFont(value?: Font): SearchAttribute;
    textFont(value?: Font): SearchAttribute;
    copyOption(value: CopyOptions): SearchAttribute;
    textAlign(value: TextAlign): SearchAttribute;
    height(value: Length): this;
    strokeWidth(value: LengthMetrics): SearchAttribute;
    strokeColor(valeu: ResourceColor): SearchAttribute;
}
declare class ArkSpanComponent implements CommonMethod<SpanAttribute> {
    _changed: boolean;
    _modifiersWithKeys: Map<Symbol, AttributeModifierWithKey>;
    nativePtr: KNode;
    _weakPtr: JsPointerClass;
    _classType: ModifierType | undefined;
    _nativePtrChanged: boolean;
    constructor(nativePtr: KNode, classType?: ModifierType);
    applyModifierPatch(): void;
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this;
    outline(value: OutlineOptions): this;
    outlineColor(value: ResourceColor | EdgeColors): this;
    outlineRadius(value: Dimension | OutlineRadiuses): this;
    outlineStyle(value: OutlineStyle | EdgeOutlineStyles): this;
    outlineWidth(value: Dimension | EdgeOutlineWidths): this;
    width(value: Length): this;
    height(value: Length): this;
    expandSafeArea(types?: Array<SafeAreaType>, edges?: Array<SafeAreaEdge>): this;
    responseRegion(value: Array<Rectangle> | Rectangle): this;
    mouseResponseRegion(value: Array<Rectangle> | Rectangle): this;
    size(value: SizeOptions): this;
    constraintSize(value: ConstraintSizeOptions): this;
    touchable(value: boolean): this;
    hitTestBehavior(value: HitTestMode): this;
    layoutWeight(value: number | string): this;
    padding(value: Padding | Length): this;
    margin(value: Margin | Length): this;
    background(builder: CustomBuilder, options?: {
        align?: Alignment;
    }): this;
    backgroundColor(value: ResourceColor): this;
    backgroundImage(src: ResourceStr, repeat?: ImageRepeat): this;
    backgroundImageSize(value: SizeOptions | ImageSize): this;
    backgroundImagePosition(value: Position | Alignment): this;
    backgroundBlurStyle(value: BlurStyle, options?: BackgroundBlurStyleOptions): this;
    foregroundBlurStyle(value: BlurStyle, options?: ForegroundBlurStyleOptions): this;
    opacity(value: number | Resource): this;
    border(value: BorderOptions): this;
    borderStyle(value: BorderStyle | EdgeStyles): this;
    borderWidth(value: Length | EdgeWidths): this;
    borderColor(value: ResourceColor | EdgeColors): this;
    borderRadius(value: Length | BorderRadiuses): this;
    borderImage(value: BorderImageOption): this;
    foregroundColor(value: ResourceColor | ColoringStrategy): this;
    onClick(event: (event?: ClickEvent) => void): this;
    onHover(event: (isHover?: boolean, event?: HoverEvent) => void): this;
    hoverEffect(value: HoverEffect): this;
    onMouse(event: (event?: MouseEvent) => void): this;
    onTouch(event: (event?: TouchEvent) => void): this;
    onKeyEvent(event: (event?: KeyEvent) => void): this;
    focusable(value: boolean): this;
    onFocus(event: () => void): this;
    onBlur(event: () => void): this;
    tabIndex(index: number): this;
    defaultFocus(value: boolean): this;
    groupDefaultFocus(value: boolean): this;
    focusOnTouch(value: boolean): this;
    animation(value: AnimateParam): this;
    transition(value: TransitionOptions | TransitionEffect): this;
    gesture(gesture: GestureType, mask?: GestureMask): this;
    priorityGesture(gesture: GestureType, mask?: GestureMask): this;
    parallelGesture(gesture: GestureType, mask?: GestureMask): this;
    blur(value: number): this;
    linearGradientBlur(value: number, options: LinearGradientBlurOptions): this;
    brightness(value: number): this;
    contrast(value: number): this;
    grayscale(value: number): this;
    colorBlend(value: Color | string | Resource): this;
    saturate(value: number): this;
    sepia(value: number): this;
    invert(value: number): this;
    hueRotate(value: number | string): this;
    useEffect(value: boolean): this;
    backdropBlur(value: number): this;
    renderGroup(value: boolean): this;
    translate(value: TranslateOptions): this;
    scale(value: ScaleOptions): this;
    gridSpan(value: number): this;
    gridOffset(value: number): this;
    rotate(value: RotateOptions): this;
    transform(value: object): this;
    onAppear(event: () => void): this;
    onDisAppear(event: () => void): this;
    onAreaChange(event: (oldValue: Area, newValue: Area) => void): this;
    visibility(value: Visibility): this;
    flexGrow(value: number): this;
    flexShrink(value: number): this;
    flexBasis(value: number | string): this;
    alignSelf(value: ItemAlign): this;
    displayPriority(value: number): this;
    zIndex(value: number): this;
    sharedTransition(id: string, options?: sharedTransitionOptions): this;
    direction(value: Direction): this;
    align(value: Alignment): this;
    position(value: Position): this;
    markAnchor(value: Position): this;
    offset(value: Position): this;
    enabled(value: boolean): this;
    useSizeType(value: {
        xs?: number | {
            span: number;
            offset: number;
        };
        sm?: number | {
            span: number;
            offset: number;
        };
        md?: number | {
            span: number;
            offset: number;
        };
        lg?: number | {
            span: number;
            offset: number;
        };
    }): this;
    alignRules(value: AlignRuleOption): this;
    aspectRatio(value: number): this;
    clickEffect(value: ClickEffect | null): this;
    onDragStart(event: (event?: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo): this;
    onDragEnter(event: (event?: DragEvent, extraParams?: string) => void): this;
    onDragSpringLoading(callback: Callback<SpringLoadingContext> | null, configuration?: DragSpringLoadingConfiguration): this;
    onDragMove(event: (event?: DragEvent, extraParams?: string) => void): this;
    onDragLeave(event: (event?: DragEvent, extraParams?: string) => void): this;
    onDrop(event: (event?: DragEvent, extraParams?: string) => void): this;
    onDragEnd(event: (event: DragEvent, extraParams?: string) => void): this;
    allowDrop(value: Array<UniformDataType>): this;
    draggable(value: boolean): this;
    overlay(value: string | CustomBuilder, options?: {
        align?: Alignment;
        offset?: {
            x?: number;
            y?: number;
        };
    }): this;
    linearGradient(value: {
        angle?: number | string;
        direction?: GradientDirection;
        colors: Array<any>;
        repeating?: boolean;
    }): this;
    sweepGradient(value: {
        center: Array<any>;
        start?: number | string;
        end?: number | string;
        rotation?: number | string;
        colors: Array<any>;
        repeating?: boolean;
    }): this;
    radialGradient(value: {
        center: Array<any>;
        radius: number | string;
        colors: Array<any>;
        repeating?: boolean;
    }): this;
    motionPath(value: MotionPathOptions): this;
    shadow(value: ShadowOptions | ShadowStyle): this;
    mask(value: CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute | ProgressMask): this;
    key(value: string): this;
    id(value: string): this;
    geometryTransition(id: string): this;
    bindPopup(show: boolean, popup: PopupOptions | CustomPopupOptions): this;
    bindMenu(content: Array<MenuElement> | CustomBuilder, options?: MenuOptions): this;
    bindContextMenu(content: CustomBuilder, responseType: ResponseType, options?: ContextMenuOptions): this;
    bindContentCover(isShow: boolean, builder: CustomBuilder, type?: ModalTransition | ContentCoverOptions): this;
    blendMode(value: BlendMode): this;
    clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this;
    bindSheet(isShow: boolean, builder: CustomBuilder, options?: SheetOptions): this;
    stateStyles(value: StateStyles): this;
    restoreId(value: number): this;
    onVisibleAreaChange(ratios: Array<number>, event: (isVisible: boolean, currentRatio: number) => void): this;
    sphericalEffect(value: number): this;
    lightUpEffect(value: number): this;
    pixelStretchEffect(options: PixelStretchEffectOptions): this;
    keyboardShortcut(value: string | FunctionKey, keys: Array<ModifierKey>, action?: () => void): this;
    accessibilityGroup(value: boolean): this;
    accessibilityText(value: string | Resource): this;
    accessibilityDescription(value: string | Resource): this;
    accessibilityLevel(value: string): this;
    obscured(reasons: Array<ObscuredReasons>): this;
    reuseId(id: string): this;
    renderFit(fitMode: RenderFit): this;
    attributeModifier(modifier: AttributeModifier<CommonAttribute>): this;
    decoration(value: {
        type: TextDecorationType;
        color?: ResourceColor;
    }): SpanAttribute;
    font(value: Font): SpanAttribute;
    lineHeight(value: Length): SpanAttribute;
    fontSize(value: Length): SpanAttribute;
    fontColor(value: ResourceColor): SpanAttribute;
    fontStyle(value: FontStyle): SpanAttribute;
    fontWeight(value: number | FontWeight | string): SpanAttribute;
    fontFamily(value: string | Resource): SpanAttribute;
    letterSpacing(value: number | string): SpanAttribute;
    textCase(value: TextCase): SpanAttribute;
}
declare class ArkSideBarContainerComponent extends ArkComponent implements SideBarContainerAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onChange(callback: (value: boolean) => void): SideBarContainerAttribute;
    autoHide(value: boolean): SideBarContainerAttribute;
    showSideBar(value: boolean): SideBarContainerAttribute;
    maxSideBarWidth(value: number | Length): SideBarContainerAttribute;
    minSideBarWidth(value: number | Length): SideBarContainerAttribute;
    minContentWidth(value: Dimension): SideBarContainerAttribute;
    controlButton(value: ButtonStyle): SideBarContainerAttribute;
    divider(value: DividerStyle | null): SideBarContainerAttribute;
    sideBarPosition(value: SideBarPosition): SideBarContainerAttribute;
    sideBarWidth(value: number | Length): SideBarContainerAttribute;
    showControlButton(value: boolean): SideBarContainerAttribute;
}
declare class ArkStackComponent extends ArkComponent implements StackAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this;
    alignContent(value: Alignment): StackAttribute;
    align(value: Alignment): this;
}
declare class ArkFolderStackComponent extends ArkStackComponent implements FolderStackAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onFolderStateChange(callback: (event: { foldStatus: FoldStatus }) => void): this;
    onHoverStatusChange(handler: (param: HoverEventParam) => void): this;
}
declare class ArkTextComponent extends ArkComponent implements TextAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    enableDataDetector(enable: boolean): this;
    dataDetectorConfig(config: any): this;
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this;
    font(value: Font): TextAttribute;
    fontColor(value: ResourceColor): TextAttribute;
    fontSize(value: any): TextAttribute;
    minFontSize(value: number | string | Resource): TextAttribute;
    maxFontSize(value: number | string | Resource): TextAttribute;
    fontStyle(value: FontStyle): TextAttribute;
    fontWeight(value: number | FontWeight | string): TextAttribute;
    textAlign(value: TextAlign): TextAttribute;
    lineHeight(value: number | string | Resource): TextAttribute;
    textOverflow(value: {
        overflow: TextOverflow;
    }): TextAttribute;
    fontFamily(value: string | Resource): TextAttribute;
    maxLines(value: number): TextAttribute;
    decoration(value: {
        type: TextDecorationType;
        color?: ResourceColor;
    }): TextAttribute;
    letterSpacing(value: number | string): TextAttribute;
    lineSpacing(value: LengthMetrics, options?: LineSpacingOptions): TextAttribute;
    optimizeTrailingSpace(trim: boolean): TextAttribute;
    textCase(value: TextCase): TextAttribute;
    baselineOffset(value: number | string): TextAttribute;
    copyOption(value: CopyOptions): TextAttribute;
    draggable(value: boolean): this;
    textShadow(value: ShadowOptions | Array<ShadowOptions>): TextAttribute;
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy): TextAttribute;
    textIndent(value: Length): TextAttribute;
    wordBreak(value: WordBreak): TextAttribute;
    lineBreakStrategy(value: LineBreakStrategy): TextAttribute;
    onCopy(callback: (value: string) => void): TextAttribute;
    selection(selectionStart: number, selectionEnd: number): TextAttribute;
    textSelectable(value: TextSelectableMode): TextAttribute;
    ellipsisMode(value: EllipsisMode): TextAttribute;
    clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this;
    marqueeOptions(value: MarqueeOptions): TextAttribute;
    onMarqueeStateChange(callback: (value: MarqueeState) => void): TextAttribute;
    shaderStyle(value: {
        center: Array<any>;
        radius: number | string;
        angle?: number | string;
        direction?: GradientDirection;
        colors: Array<any>;
        repeating?: boolean;
    }): this;
}
declare class ArkTextAreaComponent extends ArkComponent implements CommonMethod<TextAreaAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
    type(value: TextAreaType): TextAreaAttribute;
    placeholderColor(value: ResourceColor): TextAreaAttribute;
    placeholderFont(value: Font): TextAreaAttribute;
    textAlign(value: TextAlign): TextAreaAttribute;
    caretColor(value: ResourceColor): TextAreaAttribute;
    fontColor(value: ResourceColor): TextAreaAttribute;
    fontSize(value: Length): TextAreaAttribute;
    fontStyle(value: FontStyle): TextAreaAttribute;
    fontWeight(value: number | FontWeight | string): TextAreaAttribute;
    fontFamily(value: ResourceStr): TextAreaAttribute;
    inputFilter(value: ResourceStr, error?: (value: string) => void): TextAreaAttribute;
    onChange(callback: (value: string) => void): TextAreaAttribute;
    onTextSelectionChange(callback: (selectionStart: number, selectionEnd: number) => void): TextAreaAttribute;
    onContentScroll(callback: (totalOffsetX: number, totalOffsetY: number) => void): TextAreaAttribute;
    onEditChange(callback: (isEditing: boolean) => void): TextAreaAttribute;
    onCopy(callback: (value: string) => void): TextAreaAttribute;
    onCut(callback: (value: string) => void): TextAreaAttribute;
    onPaste(callback: (value: string) => void): TextAreaAttribute;
    copyOption(value: CopyOptions): TextAreaAttribute;
    enableKeyboardOnFocus(value: boolean): TextAreaAttribute;
    maxLength(value: number): TextAreaAttribute;
    showCounter(value: boolean, options?: InputCounterOptions): TextAreaAttribute;
    style(value: TextContentStyle): TextAreaAttribute;
    barState(value: BarState): TextAreaAttribute;
    selectionMenuHidden(value: boolean): TextAreaAttribute;
    maxLines(value: number, options?: MaxLinesOptions): TextAreaAttribute;
    customKeyboard(value: CustomBuilder): TextAreaAttribute;
    ellipsisMode(value: EllipsisMode): TextAreaAttribute;
    strokeWidth(value: LengthMetrics): TextAreaAttribute;
    strokeColor(value: ResourceColor): TextAreaAttribute;
}
declare class ArkTextInputComponent extends ArkComponent implements CommonMethod<TextInputAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
    cancelButton(value: {
        style?: CancelButtonStyle;
        icon?: IconOptions;
    }): TextInputAttribute;
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this;
    selectAll(value: boolean): TextInputAttribute;
    enableAutoFill(value: boolean): TextInputAttribute;
    passwordRules(value: string): TextInputAttribute;
    showCounter(value: boolean): TextInputAttribute;
    type(value: InputType): TextInputAttribute;
    placeholderColor(value: ResourceColor): TextInputAttribute;
    placeholderFont(value?: Font): TextInputAttribute;
    enterKeyType(value: EnterKeyType): TextInputAttribute;
    caretColor(value: ResourceColor): TextInputAttribute;
    onEditChanged(callback: (isEditing: boolean) => void): TextInputAttribute;
    onEditChange(callback: (isEditing: boolean) => void): TextInputAttribute;
    onSubmit(callback: (enterKey: EnterKeyType) => void): TextInputAttribute;
    onChange(callback: (value: string) => void): TextInputAttribute;
    onTextSelectionChange(callback: (selectionStart: number, selectionEnd: number) => void): TextInputAttribute;
    onContentScroll(callback: (totalOffsetX: number, totalOffsetY: number) => void): TextInputAttribute;
    maxLength(value: number): TextInputAttribute;
    fontColor(value: ResourceColor): TextInputAttribute;
    fontSize(value: Length): TextInputAttribute;
    fontStyle(value: FontStyle): TextInputAttribute;
    fontWeight(value: number | FontWeight | string): TextInputAttribute;
    fontFamily(value: ResourceStr): TextInputAttribute;
    inputFilter(value: ResourceStr, error?: (value: string) => void): TextInputAttribute;
    onCopy(callback: (value: string) => void): TextInputAttribute;
    onCut(callback: (value: string) => void): TextInputAttribute;
    onPaste(callback: (value: string) => void): TextInputAttribute;
    copyOption(value: CopyOptions): TextInputAttribute;
    showPasswordIcon(value: boolean): TextInputAttribute;
    textAlign(value: TextAlign): TextInputAttribute;
    style(value: TextInputStyle | TextContentStyle): TextInputAttribute;
    caretStyle(value: CaretStyle): this;
    selectedBackgroundColor(value: ResourceColor): TextInputAttribute;
    caretPosition(value: number): TextInputAttribute;
    enableKeyboardOnFocus(value: boolean): TextInputAttribute;
    passwordIcon(value: PasswordIcon): TextInputAttribute;
    showError(value: string | undefined): TextInputAttribute;
    showUnit(event: () => void): TextInputAttribute;
    showUnderline(value: boolean): TextInputAttribute;
    selectionMenuHidden(value: boolean): TextInputAttribute;
    barState(value: BarState): TextInputAttribute;
    maxLines(value: number): TextInputAttribute;
    customKeyboard(event: () => void): TextInputAttribute;
    ellipsisMode(value: EllipsisMode): TextInputAttribute;
    strokeWidth(value: LengthMetrics): TextInputAttribute;
    strokeColor(value: ResourceColor): TextInputAttribute;
}
declare class ArkVideoComponent extends ArkComponent implements CommonMethod<VideoAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
    muted(value: boolean): VideoAttribute;
    autoPlay(value: boolean): VideoAttribute;
    controls(value: boolean): VideoAttribute;
    loop(value: boolean): VideoAttribute;
    objectFit(value: ImageFit): VideoAttribute;
    onStart(callback: () => void): VideoAttribute;
    onPause(callback: () => void): VideoAttribute;
    onFinish(event: () => void): VideoAttribute;
    onFullscreenChange(callback: (event: {
        fullscreen: boolean;
    }) => void): VideoAttribute;
    onPrepared(callback: (event: {
        duration: number;
    }) => void): VideoAttribute;
    onSeeking(callback: (event: {
        time: number;
    }) => void): VideoAttribute;
    onSeeked(callback: (event: {
        time: number;
    }) => void): VideoAttribute;
    onUpdate(callback: (event: {
        time: number;
    }) => void): VideoAttribute;
    onError(callback: () => void): VideoAttribute;
}
declare class ArkImageFrameInfoToArray {
    arrSrc: Array<string> | undefined;
    arrWidth: Array<number | string> | undefined;
    arrHeight: Array<number | string> | undefined;
    arrTop: Array<number | string> | undefined;
    arrLeft: Array<number | string> | undefined;
    arrDuration: Array<number> | undefined;
    constructor();
    isEqual(another: ArkImageFrameInfoToArray): boolean;
}
declare class ArkButtonComponent extends ArkComponent implements ButtonAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this;
    backgroundColor(value: ResourceColor): this;
    type(value: ButtonType): this;
    stateEffect(value: boolean): this;
    fontColor(value: ResourceColor): this;
    fontSize(value: Length): this;
    fontWeight(value: string | number | FontWeight): this;
    fontStyle(value: FontStyle): this;
    fontFamily(value: string | Resource): this;
    labelStyle(value: LabelStyle): this;
    borderRadius(value: Length | BorderRadiuses): this;
    border(value: BorderOptions): this;
    size(value: SizeOptions): this;
}
declare class ArkLoadingProgressComponent extends ArkComponent implements LoadingProgressAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this;
    color(value: ResourceColor): this;
    enableLoading(value: boolean): this;
    foregroundColor(value: ResourceColor): this;
}
declare class ArkRefreshComponent extends ArkComponent implements RefreshAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this;
    onStateChange(callback: (state: RefreshStatus) => void): this;
    onRefreshing(callback: () => void): this;
    onOffsetChange(callback: Callback<number>): this;
}
declare class ArkScrollComponent extends ArkComponent implements ScrollAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this;
    scrollable(value: ScrollDirection): this;
    onScroll(event: (xOffset: number, yOffset: number) => void): this;
    onScrollEdge(event: (side: Edge) => void): this;
    onScrollStart(event: () => void): this;
    onScrollEnd(event: () => void): this;
    onScrollStop(event: () => void): this;
    enablePaging(value: boolean): this;
    scrollBar(value: BarState): this;
    scrollBarColor(color: ResourceColor): this;
    scrollBarWidth(value: string | number): this;
    edgeEffect(value: EdgeEffect, options?: EdgeEffectOptions): this;
    fadingEdge(value: boolean, options?: FadingEdgeOptions | undefined): this;
    onScrollFrameBegin(event: (offset: number, state: ScrollState) => {
        offsetRemain: number;
    }): this;
    nestedScroll(value: NestedScrollOptions): ScrollAttribute;
    enableScrollInteraction(value: boolean): ScrollAttribute;
    friction(value: number | Resource): ScrollAttribute;
    scrollSnap(value: ScrollSnapOptions): ScrollAttribute;
    clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this;
    initialOffset(value: OffsetOptions): this;
    flingSpeedLimit(value: number): this;
    onReachStart(event: () => void): this;
    onReachEnd(event: () => void): this;
}
declare class ArkToggleComponent extends ArkComponent implements ToggleAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this;
    onChange(callback: (isOn: boolean) => void): this;
    selectedColor(value: ResourceColor): this;
    switchPointColor(value: ResourceColor): this;
    height(value: Length): this;
    responseRegion(value: Rectangle | Rectangle[]): this;
    padding(value: Padding | Length): this;
    backgroundColor(value: ResourceColor): this;
    hoverEffect(value: HoverEffect): this;
}
declare class ArkSelectComponent extends ArkComponent implements SelectAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this;
    optionWidth(value: Dimension | OptionWidthMode): this;
    optionHeight(value: Dimension): this;
    width(value: Length): this;
    height(value: Length): this;
    size(value: SizeOptions): this;
    selected(value: number | Resource): this;
    value(value: ResourceStr): this;
    font(value: Font): this;
    fontColor(value: ResourceColor): this;
    selectedOptionBgColor(value: ResourceColor): this;
    selectedOptionFont(value: Font): this;
    selectedOptionFontColor(value: ResourceColor): this;
    optionBgColor(value: ResourceColor): this;
    optionFont(value: Font): this;
    optionFontColor(value: ResourceColor): this;
    onSelect(callback: (index: number, value: string) => void): this;
    space(value: Length): this;
    arrowPosition(value: ArrowPosition): this;
    menuAlign(alignType: MenuAlignType, offset?: Offset): this;
    avoidance(mode: AvoidanceMode): this;
    menuOutline(outline: MenuOutlineOptions): this;
}
declare class ArkRadioComponent extends ArkComponent implements RadioAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this;
    checked(value: boolean): this;
    onChange(callback: (isChecked: boolean) => void): this;
    radioStyle(value: RadioStyle): this;
    width(value: Length): this;
    height(value: Length): this;
    size(value: {
        width: Length;
        height: Length;
    }): this;
    hoverEffect(value: HoverEffect): this;
    padding(value: Padding | Length): this;
    responseRegion(value: Array<Rectangle> | Rectangle): this;
}
declare class ArkTimePickerComponent extends ArkComponent implements TimePickerAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this;
    loop(value: boolean): this;
    useMilitaryTime(value: boolean): this;
    disappearTextStyle(value: PickerTextStyle): this;
    textStyle(value: PickerTextStyle): this;
    selectedTextStyle(value: PickerTextStyle): this;
    onChange(callback: (value: TimePickerResult) => void): this;
    digitalCrownSensitivity(sensitivity: Optional<CrownSensitivity>): this;
}
declare class ArkTextPickerComponent extends ArkComponent implements TextPickerAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this;
    defaultPickerItemHeight(value: string | number): this;
    canLoop(value: boolean): this;
    disappearTextStyle(value: PickerTextStyle): this;
    textStyle(value: PickerTextStyle): this;
    selectedTextStyle(value: PickerTextStyle): this;
    onAccept(callback: (value: string, index: number) => void): this;
    onCancel(callback: () => void): this;
    onChange(callback: Optional<OnTextPickerChangeCallback>): this;
    selectedIndex(value: number | number[]): this;
    digitalCrownSensitivity(sensitivity: Optional<CrownSensitivity>): this;
    onScrollStop(callback: (value: string | string[], index: number | number[]) => void): this;
}
declare class ArkSliderComponent extends ArkComponent implements SliderAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this;
    blockColor(value: ResourceColor): this;
    trackColor(value: ResourceColor): this;
    selectedColor(value: ResourceColor): this;
    minLabel(value: string): this;
    maxLabel(value: string): this;
    showSteps(value: boolean): this;
    showTips(value: boolean, content?: any): this;
    trackThickness(value: Length): this;
    onChange(callback: (value: number, mode: SliderChangeMode) => void): this;
    blockBorderColor(value: ResourceColor): this;
    blockBorderWidth(value: Length): this;
    stepColor(value: ResourceColor): this;
    trackBorderRadius(value: Length): this;
    blockSize(value: SizeOptions): this;
    blockStyle(value: SliderBlockStyle): this;
    stepSize(value: Length): this;
    prefix(value: CustomBuilder, options?: SliderCustomContentOptions): this;
    suffix(value: CustomBuilder, options?: SliderCustomContentOptions): this;
}
declare class ArkRatingComponent extends ArkComponent implements RatingAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this;
    stars(value: number): this;
    stepSize(value: number): this;
    starStyle(value: {
        backgroundUri: string;
        foregroundUri: string;
        secondaryUri?: string | undefined;
    }): this;
    onChange(callback: (value: number) => void): this;
}
declare class ArkCheckboxComponent extends ArkComponent implements CheckboxAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    shape(value: CheckBoxShape): this;
    width(value: Length): this;
    height(value: Length): this;
    select(value: boolean): this;
    selectedColor(value: ResourceColor): this;
    unselectedColor(value: ResourceColor): this;
    mark(value: MarkStyle): this;
    padding(value: Padding | Length): this;
    size(value: SizeOptions): this;
    responseRegion(value: Array<Rectangle> | Rectangle): this;
    onChange(callback: OnCheckboxChangeCallback): this;
}
declare class ArkNavDestinationComponent extends ArkComponent implements NavDestinationAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    title(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined,
        options?: NavigationTitleOptions): this;
    menus(value: Array<NavigationMenuItem> | undefined): this;
    hideTitleBar(value: boolean): this;
    onShown(callback: () => void): this;
    onHidden(callback: () => void): this;
    onBackPressed(callback: () => boolean): this;
    ignoreLayoutSafeArea(types?: SafeAreaType[], edges?: SafeAreaEdge[]): this;
    recoverable(value: boolean | undefined): this;
}
declare class ArkStepperComponent extends ArkComponent implements StepperAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onFinish(callback: () => void): this;
    onSkip(callback: () => void): this;
    onChange(callback: (prevIndex: number, index: number) => void): this;
    onNext(callback: (index: number, pendingIndex: number) => void): this;
    onPrevious(callback: (index: number, pendingIndex: number) => void): this;
}
declare class ArkCounterComponent extends ArkComponent implements CounterAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onInc(event: () => void): this;
    onDec(event: () => void): this;
    enableDec(value: boolean): this;
    enableInc(value: boolean): this;
    backgroundColor(value: ResourceColor): this;
    width(value: Length): this;
    height(value: Length): this;
    size(value: SizeOptions): this;
}
declare class ArkCheckboxGroupComponent extends ArkComponent implements CheckboxGroupAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    selectAll(value: boolean): this;
    selectedColor(value: ResourceColor): this;
    unselectedColor(value: ResourceColor): this;
    mark(value: MarkStyle): this;
    onChange(callback: OnCheckboxGroupChangeCallback): CheckboxGroupAttribute;
    size(value: SizeOptions): this;
    width(value: Length): this;
    height(value: Length): this;
}
declare class ArkPanelComponent extends ArkComponent implements PanelAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    mode(value: PanelMode): this;
    type(value: PanelType): this;
    dragBar(value: boolean): this;
    customHeight(value: any): this;
    fullHeight(value: string | number): this;
    halfHeight(value: string | number): this;
    miniHeight(value: string | number): this;
    show(value: boolean): this;
    backgroundMask(color: ResourceColor): this;
    showCloseIcon(value: boolean): this;
    onChange(event: (width: number, height: number, mode: PanelMode) => void): this;
    onHeightChange(callback: (value: number) => void): this;
}
declare class ArkNavigationComponent extends ArkComponent implements NavigationAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    navBarWidth(value: Length): NavigationAttribute;
    navBarPosition(value: number): NavigationAttribute;
    navBarWidthRange(value: [Dimension, Dimension]): NavigationAttribute;
    minContentWidth(value: Dimension): NavigationAttribute;
    mode(value: number): NavigationAttribute;
    backButtonIcon(value: any): NavigationAttribute;
    hideNavBar(value: boolean): NavigationAttribute;
    title(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined,
        options?: NavigationTitleOptions): NavigationAttribute;
    subTitle(value: string): NavigationAttribute;
    hideTitleBar(value: boolean): NavigationAttribute;
    enableModeChangeAnimation(value: boolean): NavigationAttribute;
    hideBackButton(value: boolean): NavigationAttribute;
    titleMode(value: NavigationTitleMode): NavigationAttribute;
    menus(value: Array<NavigationMenuItem> | undefined): NavigationAttribute;
    toolBar(value: any): NavigationAttribute;
    toolbarConfiguration(value: any): NavigationAttribute;
    hideToolBar(value: boolean): NavigationAttribute;
    onTitleModeChange(callback: (titleMode: NavigationTitleMode) => void): NavigationAttribute;
    onNavBarStateChange(callback: (isVisible: boolean) => void): NavigationAttribute;
    onNavigationModeChange(callback: (mode: NavigationMode) => void): NavigationAttribute;
    navDestination(builder: (name: string, param: unknown) => void): NavigationAttribute;
    ignoreLayoutSafeArea(types?: SafeAreaType[], edges?: SafeAreaEdge[]): NavigationAttribute;
    recoverable(value: boolean | undefined): NavigationAttribute;
    enableDragBar(value: boolean | undefined): NavigationAttribute;
    splitPlaceholder(placeholder: ComponentContent): NavigationAttribute;
}
declare class ArkNavRouterComponent extends ArkComponent implements NavRouterAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onStateChange(callback: (isActivated: boolean) => void): NavRouterAttribute;
    mode(mode: NavRouteMode): NavRouterAttribute;
}
declare class ArkNavigatorComponent extends ArkComponent implements NavigatorAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    active(value: boolean): this;
    type(value: NavigationType): this;
    target(value: string): this;
    params(value: object): this;
}
declare class ArkAlphabetIndexerComponent extends ArkComponent implements AlphabetIndexerAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onSelected(callback: (index: number) => void): this;
    color(value: ResourceColor): this;
    selectedColor(value: ResourceColor): this;
    popupColor(value: ResourceColor): this;
    selectedBackgroundColor(value: ResourceColor): this;
    popupBackground(value: ResourceColor): this;
    popupSelectedColor(value: ResourceColor): this;
    popupUnselectedColor(value: ResourceColor): this;
    popupItemBackgroundColor(value: ResourceColor): this;
    usingPopup(value: boolean): this;
    selectedFont(value: Font): this;
    popupFont(value: Font): this;
    popupItemFont(value: Font): this;
    itemSize(value: string | number): this;
    font(value: Font): this;
    alignStyle(value: IndexerAlign, offset?: any): this;
    onSelect(callback: (index: number) => void): this;
    onRequestPopupData(callback: (index: number) => string[]): this;
    onPopupSelect(callback: (index: number) => void): this;
    selected(index: number): this;
    popupPosition(value: Position): this;
}
declare class ArkCalendarPickerComponent extends ArkComponent implements CalendarPickerAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    edgeAlign(alignType: CalendarAlign, offset?: Offset | undefined): this;
    textStyle(value: PickerTextStyle): this;
    onChange(callback: Callback<Date>): this;
    padding(value: Padding | Length): this;
    border(value: BorderOptions): this;
}
declare class ArkDataPanelComponent extends ArkComponent implements DataPanelAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    closeEffect(value: boolean): this;
    valueColors(value: Array<ResourceColor | LinearGradient>): this;
    trackBackgroundColor(value: any): this;
    strokeWidth(value: any): this;
    trackShadow(value: DataPanelShadowOptions): this;
}
declare class ArkDatePickerComponent extends ArkComponent implements DatePickerAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    lunar(value: boolean): DatePickerAttribute;
    disappearTextStyle(value: PickerTextStyle): DatePickerAttribute;
    textStyle(value: PickerTextStyle): DatePickerAttribute;
    selectedTextStyle(value: PickerTextStyle): DatePickerAttribute;
    onChange(callback: (value: DatePickerResult) => void): DatePickerAttribute;
    onDateChange(callback: Callback<Date>): this;
    backgroundColor(value: ResourceColor): this;
    digitalCrownSensitivity(sensitivity: Optional<CrownSensitivity>): DatePickerAttribute;
}
declare class ArkFormComponentComponent extends ArkComponent implements FormComponentAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    size(value: {
        width: Length;
        height: Length;
    }): this;
    visibility(value: Visibility): this;
    moduleName(value: string): this;
    dimension(value: FormDimension): this;
    allowUpdate(value: boolean): this;
    onAcquired(callback: (info: {
        id: number;
    }) => void): this;
    onError(callback: (info: {
        errcode: number;
        msg: string;
    }) => void): this;
    onRouter(callback: (info: any) => void): this;
    onUninstall(callback: (info: {
        id: number;
    }) => void): this;
    onLoad(callback: () => void): this;
}
declare class ArkEmbeddedComponent extends ArkComponent implements EmbeddedComponentAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onTerminated(callback: (info: TerminationInfo) => void): this;
    onError(callback: (info: ErrorCallback) => void): this;
}
declare class ArkIsolatedComponent extends ArkComponent implements IsolatedComponentAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onError(callback: any): this;
}
declare class ArkGaugeComponent extends ArkComponent implements GaugeAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    value(value: number): this;
    startAngle(angle: number): this;
    endAngle(angle: number): this;
    colors(colors: ResourceColor | LinearGradient | Array<[ResourceColor | LinearGradient, number]>): this;
    strokeWidth(length: any): this;
    description(value: CustomBuilder): this;
    trackShadow(value: GaugeShadowOptions): this;
    indicator(value: GaugeIndicatorOptions): this;
}
declare class ArkMarqueeComponent extends ArkComponent implements MarqueeAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this;
    fontSize(value: Length): this;
    fontColor(value: ResourceColor): this;
    allowScale(value: boolean): this;
    fontWeight(value: string | number | FontWeight): this;
    fontFamily(value: any): this;
    onStart(event: () => void): this;
    onBounce(event: () => void): this;
    onFinish(event: () => void): this;
}
declare class ArkMenuComponent extends ArkComponent implements MenuAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    width(value: Length): this;
    fontSize(value: Length): this;
    font(value: Font): this;
    fontColor(value: ResourceColor): this;
    radius(value: any): this;
}
declare class ArkMenuItemComponent extends ArkComponent implements MenuItemAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    selected(value: boolean): this;
    selectIcon(value: boolean | ResourceStr): this;
    onChange(callback: (selected: boolean) => void): this;
    contentFont(value: Font): this;
    contentFontColor(value: ResourceColor): this;
    labelFont(value: Font): this;
    labelFontColor(value: ResourceColor): this;
}
declare class ArkMenuItemGroupComponent extends ArkComponent implements MenuItemGroupAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkPluginComponent extends ArkComponent implements PluginComponentAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onComplete(callback: () => void): this;
    onError(callback: (info: {
        errcode: number;
        msg: string;
    }) => void): this;
    size(value: SizeOptions): this;
    width(value: Length): this;
    height(value: Length): this;
}
declare class ArkProgressComponent extends ArkComponent implements ProgressAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    value(value: number): ProgressAttribute<keyof ProgressStyleMap, LinearStyleOptions | ProgressStyleOptions | RingStyleOptions |
        EclipseStyleOptions | ScaleRingStyleOptions | CapsuleStyleOptions>;
    color(value: ResourceColor | LinearGradient): ProgressAttribute<keyof ProgressStyleMap, LinearStyleOptions | ProgressStyleOptions |
        RingStyleOptions | EclipseStyleOptions | ScaleRingStyleOptions | CapsuleStyleOptions>;
    style(value: LinearStyleOptions | ProgressStyleOptions | RingStyleOptions | EclipseStyleOptions | ScaleRingStyleOptions | CapsuleStyleOptions):
        ProgressAttribute<keyof ProgressStyleMap, LinearStyleOptions | ProgressStyleOptions | RingStyleOptions |
        EclipseStyleOptions | ScaleRingStyleOptions | CapsuleStyleOptions>;
    backgroundColor(value: ResourceColor): this;
}
declare class ArkQRCodeComponent extends ArkComponent implements QRCodeAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    color(value: ResourceColor): this;
    backgroundColor(value: ResourceColor): this;
    contentOpacity(value: number | Resource): this;
}
declare class ArkRichTextComponent extends ArkComponent implements CommonMethod<RichTextAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onStart(callback: () => void): RichTextAttribute;
    onComplete(callback: () => void): RichTextAttribute;
}
declare class ArkScrollBarComponent extends ArkComponent implements ScrollBarAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    enableNestedScroll(value: boolean): this;
}
declare class ArkStepperComponent extends ArkComponent implements StepperAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onFinish(callback: () => void): this;
    onSkip(callback: () => void): this;
    onChange(callback: (prevIndex: number, index: number) => void): this;
    onNext(callback: (index: number, pendingIndex: number) => void): this;
    onPrevious(callback: (index: number, pendingIndex: number) => void): this;
}
declare class ArkStepperItemComponent extends ArkComponent implements StepperItemAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    prevLabel(value: string): this;
    nextLabel(value: string): this;
    status(value?: ItemState | undefined): this;
}
declare class ArkTextClockComponent extends ArkComponent implements TextClockAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    format(value: string): this;
    onDateChange(event: (value: number) => void): this;
    fontColor(value: ResourceColor): this;
    fontSize(value: Length): this;
    fontStyle(value: FontStyle): this;
    fontWeight(value: string | number | FontWeight): this;
    fontFamily(value: ResourceStr): this;
    textShadow(value: ShadowOptions): this;
    fontFeature(value: string): this;
}
declare class ArkTextTimerComponent extends ArkComponent implements TextTimerAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    fontColor(value: any): this;
    fontSize(value: any): this;
    fontWeight(value: number | FontWeight | string): this;
    fontStyle(value: FontStyle): this;
    fontFamily(value: string | Resource): this;
    format(value: string): this;
    onTimer(event: (utc: number, elapsedTime: number) => void): this;
}
declare class ArkWebComponent extends ArkComponent implements WebAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    javaScriptAccess(javaScriptAccess: boolean): this;
    fileAccess(fileAccess: boolean): this;
    onlineImageAccess(onlineImageAccess: boolean): this;
    domStorageAccess(domStorageAccess: boolean): this;
    imageAccess(imageAccess: boolean): this;
    mixedMode(mixedMode: MixedMode): this;
    zoomAccess(zoomAccess: boolean): this;
    geolocationAccess(geolocationAccess: boolean): this;
    javaScriptProxy(javaScriptProxy: {
        object: object;
        name: string;
        methodList: string[];
        controller: any;
    }): this;
    password(password: boolean): this;
    cacheMode(cacheMode: CacheMode): this;
    darkMode(mode: WebDarkMode): this;
    forceDarkAccess(access: boolean): this;
    mediaOptions(options: WebMediaOptions): this;
    tableData(tableData: boolean): this;
    wideViewModeAccess(wideViewModeAccess: boolean): this;
    overviewModeAccess(overviewModeAccess: boolean): this;
    overScrollMode(mode: OverScrollMode): this;
    textZoomAtio(textZoomAtio: number): this;
    textZoomRatio(textZoomRatio: number): this;
    databaseAccess(databaseAccess: boolean): this;
    initialScale(percent: number): this;
    userAgent(userAgent: string): this;
    onPageEnd(callback: (event?: {
        url: string;
    } | undefined) => void): this;
    onPageBegin(callback: (event?: {
        url: string;
    } | undefined) => void): this;
    onProgressChange(callback: (event?: {
        newProgress: number;
    } | undefined) => void): this;
    onTitleReceive(callback: (event?: {
        title: string;
    } | undefined) => void): this;
    onGeolocationHide(callback: () => void): this;
    onGeolocationShow(callback: (event?: {
        origin: string;
        geolocation: JsGeolocation;
    } | undefined) => void): this;
    onRequestSelected(callback: () => void): this;
    onAlert(callback: (event?: {
        url: string;
        message: string;
        result: JsResult;
    } | undefined) => boolean): this;
    onBeforeUnload(callback: (event?: {
        url: string;
        message: string;
        result: JsResult;
    } | undefined) => boolean): this;
    onConfirm(callback: (event?: {
        url: string;
        message: string;
        result: JsResult;
    } | undefined) => boolean): this;
    onPrompt(callback: (event?: {
        url: string;
        message: string;
        value: string;
        result: JsResult;
    } | undefined) => boolean): this;
    onConsole(callback: (event?: {
        message: ConsoleMessage;
    } | undefined) => boolean): this;
    onErrorReceive(callback: (event?: {
        request: WebResourceRequest;
        error: WebResourceError;
    } | undefined) => void): this;
    onHttpErrorReceive(callback: (event?: {
        request: WebResourceRequest;
        response: WebResourceResponse;
    } | undefined) => void): this;
    onDownloadStart(callback: (event?: {
        url: string;
        userAgent: string;
        contentDisposition: string;
        mimetype: string;
        contentLength: number;
    } | undefined) => void): this;
    onRefreshAccessedHistory(callback: (event?: {
        url: string;
        isRefreshed: boolean;
    } | undefined) => void): this;
    onUrlLoadIntercept(callback: (event?: {
        data: string | WebResourceRequest;
    } | undefined) => boolean): this;
    onSslErrorReceive(callback: (event?: {
        handler: Function;
        error: object;
    } | undefined) => void): this;
    onRenderExited(callback: (event?: {
        renderExitReason: RenderExitReason;
    } | undefined) => void): this;
    onRenderExited(callback: (event?: {
        detail: object;
    } | undefined) => boolean): this;
    onShowFileSelector(callback: (event?: {
        result: FileSelectorResult;
        fileSelector: FileSelectorParam;
    } | undefined) => boolean): this;
    onFileSelectorShow(callback: (event?: {
        callback: Function;
        fileSelector: object;
    } | undefined) => void): this;
    onResourceLoad(callback: (event: {
        url: string;
    }) => void): this;
    onFullScreenExit(callback: () => void): this;
    onFullScreenEnter(callback: (event: {
        handler: FullScreenExitHandler;
    }) => void): this;
    onScaleChange(callback: (event: {
        oldScale: number;
        newScale: number;
    }) => void): this;
    onHttpAuthRequest(callback: (event?: {
        handler: HttpAuthHandler;
        host: string;
        realm: string;
    } | undefined) => boolean): this;
    onInterceptRequest(callback: (event?: {
        request: WebResourceRequest;
    } | undefined) => WebResourceResponse): this;
    onPermissionRequest(callback: (event?: {
        request: PermissionRequest;
    } | undefined) => void): this;
    onScreenCaptureRequest(callback: (event?: {
        handler: ScreenCaptureHandler;
    } | undefined) => void): this;
    onContextMenuShow(callback: (event?: {
        param: WebContextMenuParam;
        result: WebContextMenuResult;
    } | undefined) => boolean): this;
    mediaPlayGestureAccess(access: boolean): this;
    onSearchResultReceive(callback: (event?: {
        activeMatchOrdinal: number;
        numberOfMatches: number;
        isDoneCounting: boolean;
    } | undefined) => void): this;
    onScroll(callback: (event: {
        xOffset: number;
        yOffset: number;
    }) => void): this;
    onSslErrorEventReceive(callback: (event: {
        handler: SslErrorHandler;
        error: SslError;
    }) => void): this;
    onClientAuthenticationRequest(callback: (event: {
        handler: ClientAuthenticationHandler;
        host: string;
        port: number;
        keyTypes: string[];
        issuers: string[];
    }) => void): this;
    onWindowNew(callback: (event: {
        isAlert: boolean;
        isUserTrigger: boolean;
        targetUrl: string;
        handler: ControllerHandler;
    }) => void): this;
    onWindowExit(callback: () => void): this;
    multiWindowAccess(multiWindow: boolean): this;
    onInterceptKeyEvent(callback: (event: KeyEvent) => boolean): this;
    webStandardFont(family: string): this;
    webSerifFont(family: string): this;
    webSansSerifFont(family: string): this;
    webFixedFont(family: string): this;
    webFantasyFont(family: string): this;
    webCursiveFont(family: string): this;
    defaultFixedFontSize(size: number): this;
    defaultFontSize(size: number): this;
    minFontSize(size: number): this;
    minLogicalFontSize(size: number): this;
    blockNetwork(block: boolean): this;
    horizontalScrollBarAccess(horizontalScrollBar: boolean): this;
    verticalScrollBarAccess(verticalScrollBar: boolean): this;
    onTouchIconUrlReceived(callback: (event: {
        url: string;
        precomposed: boolean;
    }) => void): this;
    onFaviconReceived(callback: (event: {
        favicon: any;
    }) => void): this;
    onPageVisible(callback: (event: {
        url: string;
    }) => void): this;
    onDataResubmitted(callback: (event: {
        handler: DataResubmissionHandler;
    }) => void): this;
    pinchSmooth(isEnabled: boolean): this;
    allowWindowOpenMethod(flag: boolean): this;
    onAudioStateChanged(callback: (event: {
        playing: boolean;
    }) => void): this;
    onFirstContentfulPaint(callback: (event?: {
        navigationStartTick: number;
        firstContentfulPaintMs: number;
    } | undefined) => void): this;
    onLoadIntercept(callback: (event: {
        data: WebResourceRequest;
    }) => boolean): this;
    onControllerAttached(callback: () => void): this;
    onOverScroll(callback: (event: {
        xOffset: number;
        yOffset: number;
    }) => void): this;
    javaScriptOnDocumentStart(scripts: ScriptItem[]): this;
    layoutMode(mode: WebLayoutMode): this;
    nestedScroll(value: NestedScrollOptions): this;
    onRenderProcessNotResponding(callback: (event: {
        data: RenderProcessNotRespondingData;
    }) => void): this;
    onRenderProcessResponding(callback: () => void): this;
    onViewportFitChanged(callback: (event: {
        viewportFit: ViewportFit;
    }) => void): this;
    onAdsBlocked(callback: (details?: AdsBlockedDetails | undefined) => void): this;
    onActivateContent(callback: () => void): this;
}
declare class ArkXComponentComponent implements CommonMethod<XComponentAttribute> {
    _modifiersWithKeys: Map<Symbol, AttributeModifierWithKey>;
    nativePtr: KNode;
    constructor(nativePtr: KNode);
    applyModifierPatch(): void;
    outline(value: OutlineOptions): this;
    outlineColor(value: ResourceColor | EdgeColors): this;
    outlineRadius(value: Dimension | OutlineRadiuses): this;
    outlineStyle(value: OutlineStyle | EdgeOutlineStyles): this;
    outlineWidth(value: Dimension | EdgeOutlineWidths): this;
    width(value: Length): this;
    height(value: Length): this;
    expandSafeArea(types?: SafeAreaType[], edges?: SafeAreaEdge[]): this;
    responseRegion(value: Rectangle | Rectangle[]): this;
    mouseResponseRegion(value: Rectangle | Rectangle[]): this;
    size(value: SizeOptions): this;
    constraintSize(value: ConstraintSizeOptions): this;
    touchable(value: boolean): this;
    hitTestBehavior(value: HitTestMode): this;
    layoutWeight(value: string | number): this;
    padding(value: Length | Padding): this;
    margin(value: Length | Padding): this;
    background(builder: CustomBuilder, options?: {
        align?: Alignment;
    }): this;
    backgroundColor(value: ResourceColor): this;
    backgroundImage(src: ResourceStr, repeat?: ImageRepeat): this;
    backgroundImageSize(value: SizeOptions | ImageSize): this;
    backgroundImagePosition(value: Alignment | Position): this;
    backgroundBlurStyle(value: BlurStyle, options?: BackgroundBlurStyleOptions): this;
    foregroundBlurStyle(value: BlurStyle, options?: ForegroundBlurStyleOptions): this;
    opacity(value: number | Resource): this;
    border(value: BorderOptions): this;
    borderStyle(value: BorderStyle | EdgeStyles): this;
    borderWidth(value: Length | EdgeWidths): this;
    borderColor(value: ResourceColor | EdgeColors): this;
    borderRadius(value: Length | BorderRadiuses): this;
    borderImage(value: BorderImageOption): this;
    foregroundColor(value: string | number | Resource | Color): this;
    onClick(event: (event: ClickEvent) => void): this;
    onHover(event: (isHover: boolean, event: HoverEvent) => void): this;
    hoverEffect(value: HoverEffect): this;
    onMouse(event: (event: MouseEvent) => void): this;
    onTouch(event: (event: TouchEvent) => void): this;
    onKeyEvent(event: (event: KeyEvent) => void): this;
    focusable(value: boolean): this;
    onFocus(event: () => void): this;
    onBlur(event: () => void): this;
    tabIndex(index: number): this;
    defaultFocus(value: boolean): this;
    groupDefaultFocus(value: boolean): this;
    focusOnTouch(value: boolean): this;
    animation(value: AnimateParam): this;
    transition(value: TransitionOptions | TransitionEffect): this;
    gesture(gesture: GestureType, mask?: GestureMask): this;
    priorityGesture(gesture: GestureType, mask?: GestureMask): this;
    parallelGesture(gesture: GestureType, mask?: GestureMask): this;
    blur(value: number): this;
    linearGradientBlur(value: number, options: LinearGradientBlurOptions): this;
    brightness(value: number): this;
    contrast(value: number): this;
    grayscale(value: number): this;
    colorBlend(value: string | Resource | Color): this;
    saturate(value: number): this;
    sepia(value: number): this;
    invert(value: number): this;
    hueRotate(value: string | number): this;
    useEffect(value: boolean): this;
    backdropBlur(value: number): this;
    renderGroup(value: boolean): this;
    translate(value: TranslateOptions): this;
    scale(value: ScaleOptions): this;
    gridSpan(value: number): this;
    gridOffset(value: number): this;
    rotate(value: RotateOptions): this;
    transform(value: object): this;
    onAppear(event: () => void): this;
    onDisAppear(event: () => void): this;
    onAreaChange(event: (oldValue: Area, newValue: Area) => void): this;
    visibility(value: Visibility): this;
    flexGrow(value: number): this;
    flexShrink(value: number): this;
    flexBasis(value: string | number): this;
    alignSelf(value: ItemAlign): this;
    displayPriority(value: number): this;
    zIndex(value: number): this;
    sharedTransition(id: string, options?: sharedTransitionOptions): this;
    direction(value: Direction): this;
    align(value: Alignment): this;
    position(value: Position): this;
    markAnchor(value: Position): this;
    offset(value: Position): this;
    enabled(value: boolean): this;
    useSizeType(value: {
        xs?: number | {
            span: number;
            offset: number;
        };
        sm?: number | {
            span: number;
            offset: number;
        };
        md?: number | {
            span: number;
            offset: number;
        };
        lg?: number | {
            span: number;
            offset: number;
        };
    }): this;
    alignRules(value: AlignRuleOption): this;
    aspectRatio(value: number): this;
    clickEffect(value: ClickEffect): this;
    onDragStart(event: (event: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo): this;
    onDragEnter(event: (event: DragEvent, extraParams?: string) => void): this;
    onDragSpringLoading(callback: Callback<SpringLoadingContext> | null, configuration?: DragSpringLoadingConfiguration): this;
    onDragMove(event: (event: DragEvent, extraParams?: string) => void): this;
    onDragLeave(event: (event: DragEvent, extraParams?: string) => void): this;
    onDrop(event: (event: DragEvent, extraParams?: string) => void): this;
    onDragEnd(event: (event: DragEvent, extraParams?: string) => void): this;
    allowDrop(value: Array<UniformDataType>): this;
    draggable(value: boolean): this;
    overlay(value: string | CustomBuilder, options?: {
        align?: Alignment;
        offset?: {
            x?: number;
            y?: number;
        };
    }): this;
    linearGradient(value: {
        angle?: number | string;
        direction?: GradientDirection;
        colors: Array<any>;
        repeating?: boolean;
    }): this;
    sweepGradient(value: {
        center: Array<any>;
        start?: number | string;
        end?: number | string;
        rotation?: number | string;
        colors: Array<any>;
        repeating?: boolean;
    }): this;
    radialGradient(value: {
        center: Array<any>;
        radius: number | string;
        colors: Array<any>;
        repeating?: boolean;
    }): this;
    motionPath(value: MotionPathOptions): this;
    shadow(value: ShadowOptions | ShadowStyle): this;
    blendMode(value: BlendMode): this;
    clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this;
    mask(value: CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute | ProgressMask): this;
    key(value: string): this;
    id(value: string): this;
    geometryTransition(id: string): this;
    bindPopup(show: boolean, popup: PopupOptions | CustomPopupOptions): this;
    bindMenu(content: CustomBuilder | MenuElement[], options?: MenuOptions): this;
    bindContextMenu(content: CustomBuilder, responseType: ResponseType, options?: ContextMenuOptions): this;
    bindContentCover(isShow: unknown, builder: unknown, options?: unknown): this;
    bindSheet(isShow: boolean, builder: CustomBuilder, options?: SheetOptions): this;
    stateStyles(value: StateStyles): this;
    restoreId(value: number): this;
    onVisibleAreaChange(ratios: number[], event: (isVisible: boolean, currentRatio: number) => void): this;
    sphericalEffect(value: number): this;
    lightUpEffect(value: number): this;
    pixelStretchEffect(options: PixelStretchEffectOptions): this;
    keyboardShortcut(value: string | FunctionKey, keys: ModifierKey[], action?: () => void): this;
    accessibilityGroup(value: boolean): this;
    accessibilityText(value: string | Resource): this;
    accessibilityDescription(value: string | Resource): this;
    accessibilityLevel(value: string): this;
    obscured(reasons: ObscuredReasons[]): this;
    reuseId(id: string): this;
    renderFit(fitMode: RenderFit): this;
    attributeModifier(modifier: AttributeModifier<CommonAttribute>): this;
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this;
    onLoad(callback: (event?: object) => void): this;
    onDestroy(event: () => void): this;
    enableSecure(value: boolean): this;
    hdrBrightness(value: number): this;
    enableTransparentLayer(value: boolean): this;
}
declare class ArkBadgeComponent extends ArkComponent implements BadgeAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkFlowItemComponent extends ArkComponent implements FlowItemAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkFormLinkComponent extends ArkComponent implements FormLinkAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkGridItemComponent extends ArkComponent implements GridItemAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    rowStart(value: number): this;
    rowEnd(value: number): this;
    columnStart(value: number): this;
    columnEnd(value: number): this;
    forceRebuild(value: boolean): this;
    selectable(value: boolean): this;
    selected(value: boolean): this;
    onSelect(event: (isSelected: boolean) => void): this;
}
declare class ArkHyperlinkComponent extends ArkComponent implements HyperlinkAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    color(value: ResourceColor): this;
    draggable(value: boolean): this;
}
declare class ArkListComponent extends ArkComponent implements ListAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    lanes(value: number | LengthConstrain, gutter?: any): this;
    alignListItem(value: ListItemAlign): this;
    listDirection(value: Axis): this;
    scrollBar(value: BarState): this;
    scrollBarWidth(value: string | number): this;
    scrollBarColor(value: string | number | Color): this;
    flingSpeedLimit(value: number): this;
    edgeEffect(value: EdgeEffect, options?: EdgeEffectOptions | undefined): this;
    contentStartOffset(value: number): this;
    contentEndOffset(value: number): this;
    divider(value: {
        strokeWidth: any;
        color?: any;
        startMargin?: any;
        endMargin?: any;
    } | null): this;
    editMode(value: boolean): this;
    multiSelectable(value: boolean): this;
    cachedCount(value: number): this;
    chainAnimation(value: boolean): this;
    chainAnimationOptions(value: ChainAnimationOptions): this;
    sticky(value: StickyStyle): this;
    scrollSnapAlign(value: ScrollSnapAlign): this;
    nestedScroll(value: NestedScrollOptions): this;
    enableScrollInteraction(value: boolean): this;
    friction(value: any): this;
    clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this;
    onScroll(event: (scrollOffset: number, scrollState: ScrollState) => void): this;
    onScrollIndex(event: (start: number, end: number, center: number) => void): this;
    onScrollVisibleContentChange(callback: OnScrollVisibleContentChangeCallback): this;
    onItemDelete(event: (index: number) => boolean): this;
    onItemMove(event: (from: number, to: number) => boolean): this;
    onItemDragStart(event: (event: ItemDragInfo, itemIndex: number) => void | (() => any)): this;
    onItemDragEnter(event: (event: ItemDragInfo) => void): this;
    onItemDragMove(event: (event: ItemDragInfo, itemIndex: number, insertIndex: number) => void): this;
    onItemDragLeave(event: (event: ItemDragInfo, itemIndex: number) => void): this;
    onItemDrop(event: (event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void): this;
    onScrollFrameBegin(event: (offset: number, state: ScrollState) => {
        offsetRemain: number;
    }): this;
    onWillScroll(callback: (xOffset: number, yOffset: number,
        scrollState: ScrollState, scrollSource: ScrollSource) => void | OffsetResult): this;
    onDidScroll(callback: (xOffset: number, yOffset: number, scrollState: ScrollState) => void): this;
    onReachStart(event: () => void): this;
    onReachEnd(event: () => void): this;
    onScrollStart(event: () => void): this;
    onScrollStop(event: () => void): this;
    fadingEdge(value: boolean, options?: FadingEdgeOptions | undefined): this;
    childrenMainSize(value: ChildrenMainSize): this;
}
declare class ArkListItemComponent extends ArkComponent implements ListItemAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    sticky(value: Sticky): this;
    editable(value: boolean | EditMode): this;
    selectable(value: boolean): this;
    selected(value: boolean): this;
    swipeAction(value: SwipeActionOptions): this;
    onSelect(event: (isSelected: boolean) => void): this;
}
declare class ArkListItemGroupComponent extends ArkComponent implements ListItemGroupAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    divider(value: {
        strokeWidth: any;
        color?: any;
        startMargin?: any;
        endMargin?: any;
    } | null): this;
    childrenMainSize(value: ChildrenMainSize): this;
}
declare class ArkRelativeContainerComponent extends ArkComponent implements RelativeContainerAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkSwiperComponent extends ArkComponent implements SwiperAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    index(value: number): this;
    autoPlay(value: boolean): this;
    interval(value: number): this;
    indicator(value: boolean | DotIndicator | DigitIndicator): this;
    displayArrow(value: boolean | ArrowStyle, isHoverShow?: boolean | undefined): this;
    loop(value: boolean): this;
    duration(value: number): this;
    vertical(value: boolean): this;
    itemSpace(value: string | number): this;
    displayMode(value: SwiperDisplayMode): this;
    cachedCount(value: number, isShown?: boolean): this;
    displayCount(value: string | number | SwiperAutoFill, swipeByGroup?: boolean | undefined): this;
    effectMode(value: EdgeEffect): this;
    disableSwipe(value: boolean): this;
    curve(value: string | Curve | ICurve): this;
    onChange(event: (index: number) => void): this;
    onUnselected(event: (index: number) => void): this;
    indicatorStyle(value?: IndicatorStyle | undefined): this;
    prevMargin(value: Length): this;
    nextMargin(value: Length): this;
    enabled(value: boolean): this;
    onAnimationStart(event: (index: number, targetIndex: number, extraInfo: SwiperAnimationEvent) => void): this;
    onAnimationEnd(event: (index: number, extraInfo: SwiperAnimationEvent) => void): this;
    onGestureSwipe(event: (index: number, extraInfo: SwiperAnimationEvent) => void): this;
    nestedScroll(value: SwiperNestedScrollMode): this;
    indicatorInteractive(value: boolean): this;
    customContentTransition(transition: SwiperContentAnimatedTransition): this;
    onContentDidScroll(handler: ContentDidScrollCallback): this;
    pageFlipMode(value: PageFlipMode): this;
    onContentWillScroll(handler: ContentWillScrollCallback): this;
    maintainVisibleContentPosition(value: boolean): this;
}
declare class ArkTabsComponent extends ArkComponent implements TabsAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onAnimationStart(handler: (index: number, targetIndex: number, event: TabsAnimationEvent) => void): TabsAttribute;
    onAnimationEnd(handler: (index: number, event: TabsAnimationEvent) => void): TabsAttribute;
    onGestureSwipe(handler: (index: number, event: TabsAnimationEvent) => void): TabsAttribute;
    vertical(value: boolean): TabsAttribute;
    barPosition(value: BarPosition): TabsAttribute;
    scrollable(value: boolean): TabsAttribute;
    barMode(value: BarMode, options?: ScrollableBarModeOptions | undefined): TabsAttribute;
    barWidth(value: Length): TabsAttribute;
    barHeight(value: Length): TabsAttribute;
    animationCurve(value: Curve | ICurve): TabsAttribute;
    animationDuration(value: number): TabsAttribute;
    animationMode(value: AnimationMode): TabsAttribute;
    onChange(event: (index: number) => void): TabsAttribute;
    onTabBarClick(event: (index: number) => void): TabsAttribute;
    onUnselected(event: (index: number) => void): TabsAttribute;
    fadingEdge(value: boolean): TabsAttribute;
    divider(value: DividerStyle | null): TabsAttribute;
    barOverlap(value: boolean): TabsAttribute;
    barBackgroundColor(value: ResourceColor): TabsAttribute;
    barBackgroundBlurStyle(value: BlurStyle): TabsAttribute;
    barBackgroundBlurStyle(style: BlurStyle, options: BackgroundBlurStyleOptions): TabsAttribute;
    barBackgroundEffect(options: BackgroundEffectOptions): TabsAttribute;
    barGridAlign(value: BarGridColumnOptions): TabsAttribute;
    clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this;
    edgeEffect(value: EdgeEffect): TabsAttribute;
    pageFlipMode(value: PageFlipMode): TabsAttribute;
    cachedMaxCount(count: number, mode: CacheMode): TabsAttribute;
}
declare class ArkTabContentComponent extends ArkComponent implements TabContentAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    tabBar(value: any): this;
    tabBar(value: SubTabBarStyle | BottomTabBarStyle): this;
    size(value: SizeOptions): this;
    width(value: Length): this;
    height(value: Length): this;
}
declare class ArkUIExtensionComponentComponent extends ArkComponent implements UIExtensionComponentAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onRemoteReady(callback: any): UIExtensionComponentAttribute;
    onReceive(callback: any): UIExtensionComponentAttribute;
    onResult(callback: any): UIExtensionComponentAttribute;
    onRelease(callback: any): UIExtensionComponentAttribute;
    onError(callback: any): UIExtensionComponentAttribute;
}
declare class ArkWaterFlowComponent extends ArkComponent implements WaterFlowAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    columnsTemplate(value: string): this;
    rowsTemplate(value: string): this;
    itemConstraintSize(value: ConstraintSizeOptions): this;
    columnsGap(value: Length): this;
    rowsGap(value: Length): this;
    layoutDirection(value: FlexDirection): this;
    nestedScroll(value: NestedScrollOptions): this;
    enableScrollInteraction(value: boolean): this;
    friction(value: number | Resource): this;
    cachedCount(value: number): this;
    onReachStart(event: () => void): this;
    onReachEnd(event: () => void): this;
    onScrollFrameBegin(event: (offset: number, state: ScrollState) => {
        offsetRemain: number;
    }): this;
    clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this;
    edgeEffect(value: EdgeEffect, options?: EdgeEffectOptions | undefined): this;
    fadingEdge(value: boolean, options?: FadingEdgeOptions | undefined): this;
    scrollBarWidth(value: string | number): this;
    scrollBarColor(value: string | number | Color): this;
    scrollBar(value: BarState): this;
    flingSpeedLimit(value: number): this;
    onWillScroll(callback: (xOffset: number, yOffset: number,
        scrollState: ScrollState, scrollSource: ScrollSource) => void | OffsetResult): this;
    onDidScroll(callback: (xOffset: number, yOffset: number, scrollState: ScrollState) => void): this;
    onScrollStart(event: () => void): this;
    onScrollStop(event: () => void): this;
    onScrollIndex(event: (first: number, last: number) => void): this;
}
declare class ArkCommonShapeComponent extends ArkComponent implements CommonShapeMethod<ShapeAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
    viewPort(value: {
        x?: string | number | undefined;
        y?: string | number | undefined;
        width?: string | number | undefined;
        height?: string | number | undefined;
    }): this;
    stroke(value: ResourceColor): this;
    fill(value: ResourceColor): this;
    strokeDashOffset(value: string | number): this;
    strokeLineCap(value: LineCapStyle): this;
    strokeLineJoin(value: LineJoinStyle): this;
    strokeMiterLimit(value: string | number): this;
    strokeOpacity(value: number | string | Resource): this;
    fillOpacity(value: number | string | Resource): this;
    strokeWidth(value: string | number): this;
    antiAlias(value: boolean): this;
    strokeDashArray(value: any[]): this;
    mesh(value: any[], column: number, row: number): this;
    height(value: Length): this;
    width(value: Length): this;
    foregroundColor(value: string | number | Resource | Color): this;
}
declare class ArkCircleComponent extends ArkCommonShapeComponent implements CircleAttribute {
}
declare class ArkEllipseComponent extends ArkCommonShapeComponent implements EllipseAttribute {
}
declare class ArkLineComponent extends ArkCommonShapeComponent implements LineAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    startPoint(value: Array<Length>): this;
    endPoint(value: Array<Length>): this;
}
declare class ArkPolylineComponent extends ArkCommonShapeComponent implements PolylineAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    points(value: Array<any>): this;
}
declare class ArkPolygonComponent extends ArkCommonShapeComponent implements PolygonAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    points(value: Array<any>): this;
}
declare class ArkPathComponent extends ArkCommonShapeComponent implements PathAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    commands(value: string): this;
}
declare class ArkRectComponent extends ArkCommonShapeComponent implements RectAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    radiusWidth(value: string | number): this;
    radiusHeight(value: string | number): this;
    radius(value: string | number | Array<any>): this;
}
declare class ArkShapeComponent extends ArkCommonShapeComponent implements ShapeAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    viewPort(value: {
        x?: string | number | undefined;
        y?: string | number | undefined;
        width?: string | number | undefined;
        height?: string | number | undefined;
    }): this;
    mesh(value: Array<any> | undefined, column: number | undefined, row: number | undefined): this;
    height(value: Length): this;
    width(value: Length): this;
}
declare class ArkCanvasComponent extends ArkComponent implements CanvasAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onReady(event: VoidCallback): this;
    enableAnalyzer(value: boolean): this;
}
declare class ArkGridContainerComponent extends ArkComponent implements ColumnAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    alignItems(value: HorizontalAlign): ColumnAttribute;
    justifyContent(value: FlexAlign): ColumnAttribute;
    pointLight(value: PointLightStyle): ColumnAttribute;
}
declare class ArkEffectComponentComponent extends ArkComponent implements EffectComponentAttribute {
}
declare class ArkRemoteWindowComponent extends ArkComponent implements RemoteWindowAttribute {
}
declare class ArkParticleComponent extends ArkComponent implements ParticleAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    disturbanceFields(fields: Array<DisturbanceFieldsOptions>): ParticleAttribute;
    emitter(fields: Array<EmitterProperty>): ParticleAttribute;
}
declare class CheckboxWidthModifier extends ModifierWithKey<Length> {}
declare class CheckboxHeightModifier extends ModifierWithKey<ResourceColor> {}
declare class TextForegroundColorModifier extends ModifierWithKey<ResourceColor | ColoringStrategy> {}

declare class ArkSymbolGlyphComponent extends ArkComponent implements SymbolGlyphAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    fontColor(value: ResourceColor[]): SymbolGlyphAttribute;
    fontSize(value: number | string | Resource): SymbolGlyphAttribute;
    fontWeight(value: number | FontWeight | string): SymbolGlyphAttribute;
    renderingStrategy(value: SymbolRenderingStrategy): SymbolGlyphAttribute;
    effectStrategy(value: SymbolEffectStrategy): SymbolGlyphAttribute;
    minFontScale(value: Optional<number | Resource>): SymbolGlyphAttribute;
    maxFontScale(value: Optional<number | Resource>): SymbolGlyphAttribute;
}

declare class ArkSymbolSpanComponent extends ArkComponent implements SymbolSpanAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    fontColor(value: ResourceColor[]): SymbolSpanAttribute;
    fontSize(value: number | string | Resource): SymbolSpanAttribute;
    fontWeight(value: number | FontWeight | string): SymbolSpanAttribute;
    renderingStrategy(value: SymbolRenderingStrategy): SymbolSpanAttribute;
    effectStrategy(value: SymbolEffectStrategy): SymbolSpanAttribute;
}

declare class ArkComponent3DComponent extends ArkComponent implements Component3DAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    environment(uri: Resource): Component3DAttribute;
    customRender(uri: Resource, selfRenderUpdate: boolean): Component3DAttribute;
    shader(uri: Resource): Component3DAttribute;
    shaderImageTexture(uri: Resource): Component3DAttribute;
    shaderInputBuffer(buffer: Array<number>): Component3DAttribute;
    renderWidth(value: Dimension): Component3DAttribute;
    renderHeight(value: Dimension): Component3DAttribute;
}

declare class ArkContainerSpanComponent extends ArkComponent implements ContainerSpanAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    textBackgroundStyle(value: TextBackgroundStyle): ContainerSpanAttribute;
}

declare class ArkLazyVGridLayoutComponent extends ArkComponent implements LazyVGridLayoutAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    columnsTemplate(value: string): this;
    columnsGap(value: LengthMetrics): this;
    rowsGap(value: LengthMetrics): this;
}