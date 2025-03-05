/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
export abstract class CustomComponentImpl implements CustomComponent {
    /** @memo */
    build(): void {
    }
    aboutToAppear?(): void {
    }
    aboutToDisappear?(): void {
    }
    aboutToReuse?(params: { [key: string]: unknown; }): void {
    }
    aboutToRecycle?(): void {
    }
    onWillApplyTheme?(theme: Theme): void {
    }
    onLayout?(children: LayoutChild[], constraint: ConstraintSizeOptions): void {
    }
    onPlaceChildren?(selfLayoutInfo: GeometryInfo, children: Layoutable[], constraint: ConstraintSizeOptions): void {
    }
    onMeasure?(children: LayoutChild[], constraint: ConstraintSizeOptions): void {
    }
    onMeasureSize?(selfLayoutInfo: GeometryInfo, children: Measurable[], constraint: ConstraintSizeOptions): SizeResult {
        throw new Error("Unexpected use of base class method")
    }
    onPageShow?(): void {
    }
    onPageHide?(): void {
    }
    onFormRecycle?(): string {
        throw new Error("Unexpected use of base class method")
    }
    onFormRecover?(statusData: string): void {
    }
    /** @memo */
    pageTransition?(): void {
    }
    getUIContext(): UIContext {
        throw new Error("Unexpected use of base class method")
    }
    getUniqueId(): number {
        throw new Error("Unexpected use of base class method")
    }
    queryNavDestinationInfo(): NavDestinationInfo | undefined {
        return undefined
    }
    queryNavigationInfo(): NavigationInfo | undefined {
        return undefined
    }
    queryRouterPageInfo(): RouterPageInfo | undefined {
        return undefined
    }
    onDidBuild?(): void {
    }

    accessibilityDescription: ((value: string) => CommonAttribute) & ((value: Resource) => CommonAttribute) = () => {
        throw new Error("Unexpected use of base class property")
    }

    accessibilityGroup(value: boolean): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    accessibilityLevel(value: string): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    accessibilityText: ((value: string) => CommonAttribute) & ((value: Resource) => CommonAttribute) = () => {
        throw new Error("Unexpected use of base class property")
    }

    accessibilityTextHint(value: string): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    accessibilityVirtualNode(value: CustomBuilder): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    advancedBlendMode(effect: BlendMode | Blender, type: BlendApplyType | undefined): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    align(value: Alignment): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    alignRules(value: AlignRuleOption): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    alignSelf(value: ItemAlign): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    allowDrop(value: UniformDataType[] | undefined): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    animation(value: AnimateParam): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    aspectRatio(value: number): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    attributeModifier(value: AttributeModifier<CommonAttribute>): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    backdropBlur(value: number, options: BlurOptions | undefined): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    background(builder: CustomBuilder, options: { align?: Alignment } | undefined): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    backgroundBlurStyle(value: BlurStyle, options: BackgroundBlurStyleOptions | undefined): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    backgroundBrightness(value: BackgroundBrightnessOptions): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    backgroundColor(value: ResourceColor): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    backgroundEffect(value: BackgroundEffectOptions): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    backgroundFilter(value: Filter): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    backgroundImage(src: ResourceStr | PixelMap, repeat: ImageRepeat | undefined): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    backgroundImagePosition(value: Position | Alignment): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    backgroundImageResizable(value: ResizableOptions): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    backgroundImageSize(value: SizeOptions | ImageSize): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    bindContentCover: ((isShow: (boolean | undefined), builder: CustomBuilder, type?: ModalTransition) => CommonAttribute) & ((isShow: (boolean | undefined), builder: CustomBuilder, options?: ContentCoverOptions) => CommonAttribute) = () => {
        throw new Error("Unexpected use of base class property")
    }
    bindContextMenu: ((content: CustomBuilder, responseType: ResponseType, options?: ContextMenuOptions) => CommonAttribute) & ((isShown: boolean, content: CustomBuilder, options?: ContextMenuOptions) => CommonAttribute) = () => {
        throw new Error("Unexpected use of base class property")
    }
    bindMenu: ((content: (MenuElement[] | CustomBuilder), options?: MenuOptions) => CommonAttribute) & ((isShow: boolean, content: (MenuElement[] | CustomBuilder), options?: MenuOptions) => CommonAttribute) = () => {
        throw new Error("Unexpected use of base class property")
    }

    bindPopup(show: boolean, popup: PopupOptions | CustomPopupOptions): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    bindSheet(isShow: boolean | undefined, builder: CustomBuilder, options: SheetOptions | undefined): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    blendMode(value: BlendMode, type: BlendApplyType | undefined): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    blur(value: number, options: BlurOptions | undefined): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    border(value: BorderOptions): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    borderColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    borderImage(value: BorderImageOption): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    borderStyle(value: BorderStyle | EdgeStyles): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    borderWidth(value: Length | EdgeWidths | LocalizedEdgeWidths): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    brightness(value: number): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    chainMode(direction: Axis, style: ChainStyle): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    clickEffect(value: ClickEffect | undefined): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    clip(value: boolean): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    clipShape(value: CircleShape | EllipseShape | PathShape | RectShape): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    colorBlend(value: Color | string | Resource): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    compositingFilter(value: Filter): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    constraintSize(value: ConstraintSizeOptions): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    contrast(value: number): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    customProperty(name: string, value: Object | undefined): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    defaultFocus(value: boolean): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    direction(value: Direction): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    displayPriority(value: number): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    dragPreview(value: CustomBuilder | DragItemInfo | string): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    dragPreviewOptions(value: DragPreviewOptions, options: DragInteractionOptions | undefined): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    draggable(value: boolean): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    drawModifier(value: DrawModifier | undefined): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    enabled(value: boolean): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    expandSafeArea(types: SafeAreaType[] | undefined, edges: SafeAreaEdge[] | undefined): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    flexBasis(value: number | string): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    flexGrow(value: number): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    flexShrink(value: number): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    focusBox(value: FocusBoxStyle): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    focusOnTouch(value: boolean): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    focusScopeId(id: string, isGroup: boolean | undefined): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    focusScopePriority(scopeId: string, priority: FocusPriority | undefined): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    focusable(value: boolean): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    tabStop(value: boolean): CommonAttribute {
       throw new Error("Unexpected use of base class method")
    }

    foregroundBlurStyle(value: BlurStyle, options: ForegroundBlurStyleOptions | undefined): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    foregroundColor(value: ResourceColor | ColoringStrategy): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    foregroundEffect(value: ForegroundEffectOptions): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    foregroundFilter(value: Filter): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    freeze(value: boolean): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    geometryTransition(value: string): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    gesture(gesture: GestureType, mask: GestureMask | undefined): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    gestureModifier(value: GestureModifier): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    grayscale(value: number): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    gridOffset(value: number): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    gridSpan(value: number): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    groupDefaultFocus(value: boolean): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    height(value: Length): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    hitTestBehavior(value: HitTestMode): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    hoverEffect(value: HoverEffect): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    hueRotate(value: number | string): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    id(value: string): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    invert(value: number | InvertOptions): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    key(value: string): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    keyboardShortcut(value: string | FunctionKey, keys: ModifierKey[], action: (() => void) | undefined): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    layoutWeight(value: number | string): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    chainWeight(value: ChainWeightOptions): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    lightUpEffect(value: number): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    linearGradient(value: {
        angle?: number | string;
        direction?: GradientDirection;
        colors: [ResourceColor, number][];
        repeating?: boolean
    }): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    linearGradientBlur(value: number, options: LinearGradientBlurOptions): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    safeAreaPadding(value: (Padding|LengthMetrics|LocalizedPadding)): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    margin(value: Margin | Length | LocalizedMargin): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    markAnchor(value: Position | LocalizedPosition): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    mask(value: ProgressMask): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    maskShape(value: CircleShape | EllipseShape | PathShape | RectShape): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    monopolizeEvents(value: boolean): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    motionBlur(value: MotionBlurOptions): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    motionPath(value: MotionPathOptions): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    mouseResponseRegion(value: Rectangle[] | Rectangle): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    accessibilityChecked(value: boolean): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    accessibilitySelected(value: boolean): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    obscured(value: ObscuredReasons[]): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    offset(value: Position | Edges | LocalizedEdges): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onAccessibilityHover(value: AccessibilityCallback): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onAppear(value: () => void): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onAreaChange(value: (oldValue: Area, newValue: Area) => void): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onAttach(value: () => void): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onBlur(value: () => void): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onChildTouchTest(value: (value: TouchTestInfo[]) => TouchResult): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onClick(value: (event: ClickEvent) => void): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onDetach(value: () => void): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onDisAppear(value: () => void): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onDragEnd(value: (event: DragEvent, extraParams?: string) => void): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onDragEnter(value: (event: DragEvent, extraParams?: string) => void): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onDragLeave(value: (event: DragEvent, extraParams?: string) => void): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onDragMove(value: (event: DragEvent, extraParams?: string) => void): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onDragStart(value: (event: DragEvent, extraParams?: string) => (CustomBuilder | DragItemInfo)): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onDrop(value: (event: DragEvent, extraParams?: string) => void): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onFocus(value: () => void): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onGestureJudgeBegin(value: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onGestureRecognizerJudgeBegin(value: GestureRecognizerJudgeBeginCallback): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onHover(value: (isHover: boolean, event: HoverEvent) => void): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onKeyEvent(value: (event: KeyEvent) => void): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onKeyPreIme(value: (parameter: KeyEvent) => boolean): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onMouse(value: (event: MouseEvent) => void): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onPreDrag(value: (parameter: PreDragStatus) => void): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onSizeChange(value: SizeChangeCallback): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onTouch(value: (event: TouchEvent) => void): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onTouchIntercept(value: (parameter: TouchEvent) => HitTestMode): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onVisibleAreaChange(ratios: number[], event: VisibleAreaChangeCallback): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    opacity(value: number | Resource): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    outline(value: OutlineOptions): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    outlineColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    outlineRadius(value: Dimension | OutlineRadiuses): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    outlineStyle(value: OutlineStyle | EdgeOutlineStyles): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    outlineWidth(value: Dimension | EdgeOutlineWidths): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    overlay(value: string | CustomBuilder | ComponentContent, options: OverlayOptions | undefined): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    padding(value: Padding | Length | LocalizedPadding): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    parallelGesture(gesture: GestureType, mask: GestureMask | undefined): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    pixelRound(value: PixelRoundPolicy): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    pixelStretchEffect(value: PixelStretchEffectOptions): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    position(value: Position | Edges | LocalizedEdges): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    priorityGesture(gesture: GestureType, mask: GestureMask | undefined): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    radialGradient(value: {
        center: [Length, Length];
        radius: number | string;
        colors: [ResourceColor, number][];
        repeating?: boolean
    }): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    renderFit(value: RenderFit): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    renderGroup(value: boolean): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    responseRegion(value: Rectangle[] | Rectangle): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    restoreId(value: number): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    reuseId(value: string): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    rotate(value: RotateOptions): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    saturate(value: number): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    scale(value: ScaleOptions): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    sepia(value: number): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    shadow(value: ShadowOptions | ShadowStyle): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    sharedTransition(id: string, options: sharedTransitionOptions | undefined): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    shouldBuiltInRecognizerParallelWith(value: ShouldBuiltInRecognizerParallelWithCallback): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    size(value: SizeOptions): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    sphericalEffect(value: number): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    stateStyles(value: StateStyles): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    sweepGradient(value: {
        center: [Length, Length];
        start?: number | string;
        end?: number | string;
        rotation?: number | string;
        colors: [ResourceColor, number][];
        repeating?: boolean
    }): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    systemBarEffect(): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    tabIndex(value: number): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    touchable(value: boolean): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    transform(value: Object): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    transition(value: (TransitionOptions|TransitionEffect)): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    translate(value: TranslateOptions): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    useEffect(value: boolean): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    useShadowBatching(value: boolean): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    useSizeType(value: {
        xs?: number | { span: number; offset: number };
        sm?: number | { span: number; offset: number };
        md?: number | { span: number; offset: number };
        lg?: number | { span: number; offset: number }
    }): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    visibility(value: Visibility): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    visualEffect(value: VisualEffect): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    width(value: Length): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    zIndex(value: number): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    __applyStyle(style: (instance: CommonAttribute, ...args: any) => this, ...args: any): CommonAttribute {
        throw new Error("Unexpected use of base class method")
    }

    onBackPress(): boolean {
        return false
    }
}
