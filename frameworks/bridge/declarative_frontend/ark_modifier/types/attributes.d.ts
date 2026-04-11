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

interface CommonAttribute {
    width(value: Length): CommonAttribute;
    height(value: Length): CommonAttribute;
    size(value: SizeOptions): CommonAttribute;
    constraintSize(value: ConstraintSizeOptions): CommonAttribute;
    layoutWeight(value: number | string): CommonAttribute;
    padding(value: Padding | Length): CommonAttribute;
    margin(value: Margin | Length): CommonAttribute;
    backgroundColor(value: ResourceColor): CommonAttribute;
    backgroundImage(src: ResourceStr, repeat?: ImageRepeat): CommonAttribute;
    backgroundImageSize(value: SizeOptions | ImageSize): CommonAttribute;
    backgroundImagePosition(value: Position | Alignment): CommonAttribute;
    backgroundBlurStyle(value: BlurStyle, options?: BackgroundBlurStyleOptions): CommonAttribute;
    foregroundBlurStyle(value: BlurStyle, options?: ForegroundBlurStyleOptions): CommonAttribute;
    border(value: BorderOptions): CommonAttribute;
    borderStyle(value: BorderStyle | EdgeStyles): CommonAttribute;
    borderWidth(value: Length | EdgeWidths): CommonAttribute;
    borderColor(value: ResourceColor | EdgeColors): CommonAttribute;
    borderRadius(value: Length | BorderRadiuses): CommonAttribute;
    borderImage(value: BorderImageOption): CommonAttribute;
    foregroundColor(value: ResourceColor | ColoringStrategy): CommonAttribute;
    opacity(value: number | Resource): CommonAttribute;
    blur(value: number): CommonAttribute;
    brightness(value: number): CommonAttribute;
    contrast(value: number): CommonAttribute;
    grayscale(value: number): CommonAttribute;
    saturate(value: number): CommonAttribute;
    sepia(value: number): CommonAttribute;
    invert(value: number): CommonAttribute;
    hueRotate(value: number | string): CommonAttribute;
    backdropBlur(value: number): CommonAttribute;
    shadow(value: ShadowOptions | ShadowStyle): CommonAttribute;
    offset(value: Position): CommonAttribute;
    position(value: Position): CommonAttribute;
    markAnchor(value: Position): CommonAttribute;
    align(value: Alignment): CommonAttribute;
    translate(value: TranslateOptions): CommonAttribute;
    scale(value: ScaleOptions): CommonAttribute;
    rotate(value: RotateOptions): CommonAttribute;
    transform(value: object): CommonAttribute;
    clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): CommonAttribute;
    zIndex(value: number): CommonAttribute;
    visibility(value: Visibility): CommonAttribute;
    flexGrow(value: number): CommonAttribute;
    flexShrink(value: number): CommonAttribute;
    flexBasis(value: number | string): CommonAttribute;
    alignSelf(value: ItemAlign): CommonAttribute;
    displayPriority(value: number): CommonAttribute;
    useEffect(value: boolean): CommonAttribute;
    renderGroup(value: boolean): CommonAttribute;
    direction(value: Direction): CommonAttribute;
    enabled(value: boolean): CommonAttribute;
    reuseId(value: string): CommonAttribute;
    renderFit(fitMode: RenderFit): CommonAttribute;
    geometryTransition(id: string): CommonAttribute;
    sharedTransition(id: string, options?: sharedTransitionOptions): CommonAttribute;
    transition(value: TransitionOptions | TransitionEffect): CommonAttribute;
    motionPath(value: MotionPathOptions): CommonAttribute;
    onClick(event: (event?: ClickEvent) => void): CommonAttribute;
    onHover(event: (isHover?: boolean, event?: HoverEvent) => void): CommonAttribute;
    onMouse(event: (event?: MouseEvent) => void): CommonAttribute;
    onTouch(event: (event?: TouchEvent) => void): CommonAttribute;
    onKeyEvent(event: (event?: KeyEvent) => void): CommonAttribute;
    onFocus(event: () => void): CommonAttribute;
    onBlur(event: () => void): CommonAttribute;
    onAppear(event: () => void): CommonAttribute;
    onDisAppear(event: () => void): CommonAttribute;
    onAreaChange(event: (oldValue: Area, newValue: Area) => void): CommonAttribute;
    focusable(value: boolean): CommonAttribute;
    tabStop(value: boolean): CommonAttribute;
    tabIndex(index: number): CommonAttribute;
    defaultFocus(value: boolean): CommonAttribute;
    groupDefaultFocus(value: boolean): CommonAttribute;
    focusOnTouch(value: boolean): CommonAttribute;
    animation(value: AnimateParam): CommonAttribute;
    hoverEffect(value: HoverEffect): CommonAttribute;
    accessibilityGroup(value: boolean): CommonAttribute;
    accessibilityText(value: string | Resource): CommonAttribute;
    accessibilityDescription(value: string | Resource): CommonAttribute;
    accessibilityLevel(value: string): CommonAttribute;
    attributeModifier(modifier: AttributeModifier<CommonAttribute>): CommonAttribute;
}

interface BlankAttribute extends CommonAttribute {
    color(value: ResourceColor): BlankAttribute;
    height(value: Length): BlankAttribute;
}

interface ColumnAttribute extends CommonAttribute {
    alignItems(value: HorizontalAlign): ColumnAttribute;
    justifyContent(value: FlexAlign): ColumnAttribute;
    pointLight(value: PointLightStyle): ColumnAttribute;
}

interface ColumnSplitAttribute extends CommonAttribute {
    resizeable(value: boolean): ColumnSplitAttribute;
    divider(value: ColumnSplitDividerStyle | null): ColumnSplitAttribute;
}

interface DividerAttribute extends CommonAttribute {
    vertical(value: boolean): DividerAttribute;
    color(value: ResourceColor): DividerAttribute;
    strokeWidth(value: number | string): DividerAttribute;
    lineCap(value: LineCapStyle): DividerAttribute;
}

interface FlexAttribute extends CommonAttribute {
    pointLight(value: PointLightStyle): FlexAttribute;
}

interface GridRowAttribute extends CommonAttribute {
    onBreakpointChange(callback: (breakpoints: string) => void): GridRowAttribute;
    alignItems(value: ItemAlign): GridRowAttribute;
}

interface GridAttribute extends CommonAttribute {
    columnsTemplate(value: string): GridAttribute;
    rowsTemplate(value: string): GridAttribute;
    columnsGap(value: Length): GridAttribute;
    rowsGap(value: Length): GridAttribute;
    scrollBarWidth(value: string | number): GridAttribute;
    scrollBarColor(value: string | number | Color): GridAttribute;
    scrollBar(value: BarState): GridAttribute;
    onScrollBarUpdate(event: (index: number, offset: number) => ComputedBarAttribute): GridAttribute;
    onScrollIndex(event: (first: number, last: number) => void): GridAttribute;
    cachedCount(value: number): GridAttribute;
    editMode(value: boolean): GridAttribute;
    multiSelectable(value: boolean): GridAttribute;
    maxCount(value: number): GridAttribute;
    minCount(value: number): GridAttribute;
    cellLength(value: number): GridAttribute;
    layoutDirection(value: GridDirection): GridAttribute;
    supportAnimation(value: boolean): GridAttribute;
    onItemDragStart(event: (event: ItemDragInfo, itemIndex: number) => void | (() => object)): GridAttribute;
    onItemDragEnter(event: (event: ItemDragInfo) => void): GridAttribute;
    onItemDragMove(event: (event: ItemDragInfo, itemIndex: number, insertIndex: number) => void): GridAttribute;
    onItemDragLeave(event: (event: ItemDragInfo, itemIndex: number) => void): GridAttribute;
    onItemDrop(event: (event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void): GridAttribute;
    edgeEffect(value: EdgeEffect, options?: EdgeEffectOptions): GridAttribute;
}

interface GridColAttribute extends CommonAttribute {
    span(value: number): GridColAttribute;
    offset(value: number): GridColAttribute;
    order(value: number): GridColAttribute;
}

interface RowAttribute extends CommonAttribute {
    alignItems(value: VerticalAlign): RowAttribute;
    justifyContent(value: FlexAlign): RowAttribute;
    pointLight(value: PointLightStyle): RowAttribute;
}

interface RowSplitAttribute extends CommonAttribute {
    resizeable(value: boolean): RowSplitAttribute;
    divider(value: RowSplitDividerStyle | null): RowSplitAttribute;
}

interface SideBarContainerAttribute extends CommonAttribute {
    showSideBar(value: boolean): SideBarContainerAttribute;
    showControlButton(value: boolean): SideBarContainerAttribute;
    sideBarWidth(value: number | Dimension): SideBarContainerAttribute;
    minSideBarWidth(value: number | Dimension): SideBarContainerAttribute;
    maxSideBarWidth(value: number | Dimension): SideBarContainerAttribute;
    autoHide(value: boolean): SideBarContainerAttribute;
    sideBarPosition(value: SideBarPosition): SideBarContainerAttribute;
    onChange(callback: (isShow: boolean) => void): SideBarContainerAttribute;
    divider(value: DividerStyle | null): SideBarContainerAttribute;
    sideBarBackgroundColor(value: ResourceColor): SideBarContainerAttribute;
    sideBarBackgroundBlurStyle(style: BlurStyle, options?: BackgroundBlurStyleOptions): SideBarContainerAttribute;
    sideBarBackgroundImage(image: ResourceStr | PixelMap, repeat?: ImageRepeat): SideBarContainerAttribute;
    sideBarBackgroundImageSize(value: SizeOptions | ImageSize): SideBarContainerAttribute;
    sideBarBackgroundImagePosition(value: Position | Alignment): SideBarContainerAttribute;
    sideBarBorderColor(value: ResourceColor | EdgeColors): SideBarContainerAttribute;
    sideBarBorderWidth(value: Length | EdgeWidths): SideBarContainerAttribute;
    sideBarBorderStyle(value: BorderStyle | EdgeStyles): SideBarContainerAttribute;
    sideBarBorderRadius(value: Length | BorderRadiuses): SideBarContainerAttribute;
    contentBackgroundColor(value: ResourceColor): SideBarContainerAttribute;
    contentBackgroundBlurStyle(style: BlurStyle, options?: BackgroundBlurStyleOptions): SideBarContainerAttribute;
    contentBackgroundImage(image: ResourceStr | PixelMap, repeat?: ImageRepeat): SideBarContainerAttribute;
    contentBackgroundImageSize(value: SizeOptions | ImageSize): SideBarContainerAttribute;
    contentBackgroundImagePosition(value: Position | Alignment): SideBarContainerAttribute;
    contentBorderColor(value: ResourceColor | EdgeColors): SideBarContainerAttribute;
    contentBorderWidth(value: Length | EdgeWidths): SideBarContainerAttribute;
    contentBorderStyle(value: BorderStyle | EdgeStyles): SideBarContainerAttribute;
    contentBorderRadius(value: Length | BorderRadiuses): SideBarContainerAttribute;
    controlButton(value: ButtonStyle): SideBarContainerAttribute;
}

interface StackAttribute extends CommonAttribute {
    alignContent(value: Alignment): StackAttribute;
    align(value: Alignment): StackAttribute;
    pointLight(value: PointLightStyle): StackAttribute;
}

interface FolderStackAttribute extends StackAttribute {
    onFolderStateChange(callback: (event: { folding: boolean }) => void): FolderStackAttribute;
    hoverController(value: HoverController): FolderStackAttribute;
    enableAnimation(value: boolean): FolderStackAttribute;
    enableHover(value: boolean): FolderStackAttribute;
}

interface ImageAttribute extends CommonAttribute {
    alt(value: string | Resource): ImageAttribute;
    matchTextDirection(value: boolean): ImageAttribute;
    fitOriginalSize(value: boolean): ImageAttribute;
    fillColor(value: ResourceColor): ImageAttribute;
    objectFit(value: ImageFit): ImageAttribute;
    objectRepeat(value: ImageRepeat): ImageAttribute;
    autoResize(value: boolean): ImageAttribute;
    renderMode(value: ImageRenderMode): ImageAttribute;
    interpolation(value: ImageInterpolation): ImageAttribute;
    sourceSize(value: { width: number; height: number }): ImageAttribute;
    onComplete(callback: (event: { width: number; height: number; componentWidth: number; componentHeight: number }) => void): ImageAttribute;
    onError(callback: (event: { componentWidth: number; componentHeight: number }) => void): ImageAttribute;
    onFinish(event: () => void): ImageAttribute;
    onProgressLoad(event: (value: { index: number; total: number }) => void): ImageAttribute;
    loadingStatus(value: number): ImageAttribute;
}

interface ImageAnimatorAttribute extends CommonAttribute {
    images(value: Array<ImageFrameInfo>): ImageAnimatorAttribute;
    state(value: AnimationStatus): ImageAnimatorAttribute;
    duration(value: number): ImageAnimatorAttribute;
    reverse(value: boolean): ImageAnimatorAttribute;
    fixedSize(value: boolean): ImageAnimatorAttribute;
    preDecode(value: number): ImageAnimatorAttribute;
    fillMode(value: FillMode): ImageAnimatorAttribute;
    iterations(value: number): ImageAnimatorAttribute;
    onStart(event: () => void): ImageAnimatorAttribute;
    onPause(event: () => void): ImageAnimatorAttribute;
    onRepeat(event: () => void): ImageAnimatorAttribute;
    onCancel(event: () => void): ImageAnimatorAttribute;
    onFinish(event: () => void): ImageAnimatorAttribute;
}

interface ImageSpanAttribute extends CommonAttribute {
    alt(value: string | Resource): ImageSpanAttribute;
    verticalAlign(value: ImageSpanAlignment): ImageSpanAttribute;
    objectFit(value: ImageFit): ImageSpanAttribute;
}

interface TextAttribute extends CommonAttribute {
    fontSize(value: number | string | Resource): TextAttribute;
    fontColor(value: ResourceColor): TextAttribute;
    fontStyle(value: FontStyle): TextAttribute;
    fontWeight(value: number | FontWeight | string): TextAttribute;
    textAlign(value: TextAlign): TextAttribute;
    lineHeight(value: number | string | Resource): TextAttribute;
    textOverflow(value: TextOverflowOptions): TextAttribute;
    fontFamily(value: Resource | string): TextAttribute;
    maxLines(value: number): TextAttribute;
    minFontSize(value: number | string | Resource): TextAttribute;
    maxFontSize(value: number | string | Resource): TextAttribute;
    decoration(value: TextDecorationOptions): TextAttribute;
    letterSpacing(value: number | string): TextAttribute;
    textCase(value: TextCase): TextAttribute;
    baselineOffset(value: number | string): TextAttribute;
    copyOption(value: CopyOptions): TextAttribute;
    draggable(value: boolean): TextAttribute;
    privacySensitive(value: boolean): TextAttribute;
    textShadow(value: TextShadowOptions): TextAttribute;
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy): TextAttribute;
    textIndent(value: number | string): TextAttribute;
    wordBreak(value: WordBreak): TextAttribute;
    lineSpacing(value: LineSpacingOptions): TextAttribute;
    fontFeature(value: string): TextAttribute;
    selection(value: SelectionOptions): TextAttribute;
    ellipsisMode(value: EllipsisMode): TextAttribute;
    enableDataDetectorType(value: TextDataDetectorType | TextDataDetectorType[]): TextAttribute;
    dataDetectorConfig(value: TextDataDetectorConfig): TextAttribute;
    onCopy(callback: () => void): TextAttribute;
    onTextSelectionChange(callback: (selectionStart: number, selectionEnd: number) => void): TextAttribute;
    minFontScale(value: number | Resource): TextAttribute;
    maxFontScale(value: number | Resource): TextAttribute;
}

interface TextAreaAttribute extends CommonAttribute {
    placeholderColor(value: ResourceColor): TextAreaAttribute;
    placeholderFont(value: Font): TextAreaAttribute;
    textAlign(value: TextAlign): TextAreaAttribute;
    caretColor(value: ResourceColor): TextAreaAttribute;
    fontSize(value: number | string | Resource): TextAreaAttribute;
    fontStyle(value: FontStyle): TextAreaAttribute;
    fontWeight(value: number | FontWeight | string): TextAreaAttribute;
    fontFamily(value: Resource | string): TextAreaAttribute;
    inputFilter(value: Resource | string, error?: (value: string) => void): TextAreaAttribute;
    onChange(callback: (value: string) => void): TextAreaAttribute;
    onTextSelectionChange(callback: (selectionStart: number, selectionEnd: number) => void): TextAreaAttribute;
    onEditChange(callback: (isEditing: boolean) => void): TextAreaAttribute;
    copyOption(value: CopyOptions): TextAreaAttribute;
    maxLength(value: number): TextAreaAttribute;
    showCounter(value: boolean | ShowCounterOptions): TextAreaAttribute;
    lineHeight(value: number | string | Resource): TextAreaAttribute;
    letterSpacing(value: number | string): TextAreaAttribute;
    decoration(value: TextDecorationOptions): TextAreaAttribute;
    textCase(value: TextCase): TextAreaAttribute;
    fontFeature(value: string): TextAreaAttribute;
    onCopy(callback: () => void): TextAreaAttribute;
    onCut(callback: () => void): TextAreaAttribute;
    onPaste(callback: (event: PasteEvent) => void): TextAreaAttribute;
    selectionMenuHidden(value: boolean): TextAreaAttribute;
    barState(value: BarState): TextAreaAttribute;
    maxLines(value: number): TextAreaAttribute;
    customKeyboard(value: CustomBuilder | null, options?: KeyboardOptions): TextAreaAttribute;
    enableKeyboardOnFocus(value: boolean): TextAreaAttribute;
    showError(value: string | undefined): TextAreaAttribute;
    style(value: TextContentStyle): TextAreaAttribute;
    padding(value: Padding | LengthMetrics | LocalizedPadding): TextAreaAttribute;
    backgroundColor(value: ResourceColor): TextAreaAttribute;
    height(value: Length): TextAreaAttribute;
    minFontSize(value: number | string | Resource): TextAreaAttribute;
    maxFontSize(value: number | string | Resource): TextAreaAttribute;
    minFontScale(value: number | Resource): TextAreaAttribute;
    maxFontScale(value: number | Resource): TextAreaAttribute;
}

interface TextInputAttribute extends CommonAttribute {
    type(value: TextInputType): TextInputAttribute;
    placeholderColor(value: ResourceColor): TextInputAttribute;
    placeholderFont(value: Font): TextInputAttribute;
    enterKeyType(value: EnterKeyType): TextInputAttribute;
    caretColor(value: ResourceColor): TextInputAttribute;
    maxLength(value: number): TextInputAttribute;
    fontSize(value: number | string | Resource): TextInputAttribute;
    fontStyle(value: FontStyle): TextInputAttribute;
    fontWeight(value: number | FontWeight | string): TextInputAttribute;
    fontFamily(value: Resource | string): TextInputAttribute;
    inputFilter(value: Resource | string, error?: (value: string) => void): TextInputAttribute;
    onChange(callback: (value: string) => void): TextInputAttribute;
    onTextSelectionChange(callback: (selectionStart: number, selectionEnd: number) => void): TextInputAttribute;
    onEditChange(callback: (isEditing: boolean) => void): TextInputAttribute;
    onSubmit(callback: (enterKey: EnterKeyType) => void): TextInputAttribute;
    selectAll(value: boolean): TextInputAttribute;
    copyOption(value: CopyOptions): TextInputAttribute;
    showPasswordIcon(value: boolean): TextInputAttribute;
    textAlign(value: TextAlign): TextInputAttribute;
    style(value: InputStyle | TextInputStyle): TextInputAttribute;
    passwordIcon(value: PasswordIcon): TextInputAttribute;
    showError(value: string | undefined): TextInputAttribute;
    showUnit(value: () => void): TextInputAttribute;
    showUnderline(value: boolean): TextInputAttribute;
    selectionMenuHidden(value: boolean): TextInputAttribute;
    barState(value: BarState): TextInputAttribute;
    maxLines(value: number): TextInputAttribute;
    decoration(value: TextDecorationOptions): TextInputAttribute;
    letterSpacing(value: number | string): TextInputAttribute;
    lineHeight(value: number | string | Resource): TextInputAttribute;
    textCase(value: TextCase): TextInputAttribute;
    fontFeature(value: string): TextInputAttribute;
    wordBreak(value: WordBreak): TextInputAttribute;
    onCopy(callback: () => void): TextInputAttribute;
    onCut(callback: () => void): TextInputAttribute;
    onPaste(callback: (event: PasteEvent) => void): TextInputAttribute;
    padding(value: Padding | LengthMetrics | LocalizedPadding): TextInputAttribute;
    backgroundColor(value: ResourceColor): TextInputAttribute;
    width(value: Length): TextInputAttribute;
    height(value: Length): TextInputAttribute;
    cancelButton(value: CancelButtonStyle | { style?: CancelButtonStyle; icon?: IconOptions }): TextInputAttribute;
    enableKeyboardOnFocus(value: boolean): TextInputAttribute;
    customKeyboard(value: CustomBuilder | null, options?: KeyboardOptions): TextInputAttribute;
    minFontSize(value: number | string | Resource): TextInputAttribute;
    maxFontSize(value: number | string | Resource): TextInputAttribute;
    minFontScale(value: number | Resource): TextInputAttribute;
    maxFontScale(value: number | Resource): TextInputAttribute;
}

interface SearchAttribute extends CommonAttribute {
    searchButton(value: string, option?: SearchButtonOptions): SearchAttribute;
    placeholderColor(value: ResourceColor): SearchAttribute;
    placeholderFont(value: Font): SearchAttribute;
    textFont(value: Font): SearchAttribute;
    textAlign(value: TextAlign): SearchAttribute;
    copyOption(value: CopyOptions): SearchAttribute;
    searchIcon(value: IconOptions): SearchAttribute;
    cancelButton(value: CancelButtonStyle | { style?: CancelButtonStyle; icon?: IconOptions }): SearchAttribute;
    fontColor(value: ResourceColor): SearchAttribute;
    caretStyle(value: CaretStyle): SearchAttribute;
    enableKeyboardOnFocus(value: boolean): SearchAttribute;
    selectionMenuHidden(value: boolean): SearchAttribute;
    customKeyboard(value: CustomBuilder | null, options?: KeyboardOptions): SearchAttribute;
    type(value: SearchType): SearchAttribute;
    maxLength(value: number): SearchAttribute;
    enterKeyType(value: EnterKeyType): SearchAttribute;
    decoration(value: TextDecorationOptions): SearchAttribute;
    letterSpacing(value: number | string): SearchAttribute;
    lineHeight(value: number | string | Resource): SearchAttribute;
    fontFeature(value: string): SearchAttribute;
    minFontSize(value: number | string | Resource): SearchAttribute;
    maxFontSize(value: number | string | Resource): SearchAttribute;
    minFontScale(value: number | Resource): SearchAttribute;
    maxFontScale(value: number | Resource): SearchAttribute;
    fontWeight(value: number | FontWeight | string): SearchAttribute;
    fontStyle(value: FontStyle): SearchAttribute;
    fontFamily(value: Resource | string): SearchAttribute;
    onEditChange(callback: (isEditing: boolean) => void): SearchAttribute;
    onSubmit(callback: (searchText: string) => void): SearchAttribute;
    onChange(callback: (value: string) => void): SearchAttribute;
    onCopy(callback: () => void): SearchAttribute;
    onCut(callback: () => void): SearchAttribute;
    onPaste(callback: (event: PasteEvent) => void): SearchAttribute;
    onTextSelectionChange(callback: (selectionStart: number, selectionEnd: number) => void): SearchAttribute;
    onContentScroll(callback: (offsetX: number, offsetY: number) => void): SearchAttribute;
    height(value: Length): SearchAttribute;
    cancelButtonSymbolStyle(value: SymbolOptions): SearchAttribute;
    searchButtonFontColor(value: ResourceColor): SearchAttribute;
}

interface ButtonAttribute extends CommonAttribute {
    type(value: ButtonType): ButtonAttribute;
    stateEffect(value: boolean): ButtonAttribute;
    fontColor(value: ResourceColor): ButtonAttribute;
    fontSize(value: number | string | Resource): ButtonAttribute;
    fontWeight(value: number | FontWeight | string): ButtonAttribute;
    fontStyle(value: FontStyle): ButtonAttribute;
    fontFamily(value: Resource | string): ButtonAttribute;
    labelStyle(value: LabelStyle): ButtonAttribute;
    fontFeature(value: string): ButtonAttribute;
    size(value: ButtonSize): ButtonAttribute;
    role(value: ButtonRole): ButtonAttribute;
    buttonStyle(value: ButtonStyleMode): ButtonAttribute;
    controlSize(value: ControlSize): ButtonAttribute;
    onClick(callback: (event: ClickEvent, result: ButtonCallbackResult) => void): ButtonAttribute;
    minFontSize(value: number | string | Resource): ButtonAttribute;
    maxFontSize(value: number | string | Resource): ButtonAttribute;
    height(value: Length): ButtonAttribute;
    width(value: Length): ButtonAttribute;
}

type ButtonType = 'capsule' | 'circle' | 'normal' | 'rounded';
type LabelStyle = object;
type ButtonSize = 'auto' | 'mini' | 'small' | 'default' | 'large';
type ButtonRole = 'normal' | 'error';
type ButtonStyleMode = 'emphasized' | 'normal';
type ControlSize = 'small' | 'normal' | 'large';
type ButtonCallbackResult = object;
type VerticalAlign = 'top' | 'center' | 'bottom';
type Font = object;
type IconOptions = object;
type KeyboardOptions = object;
type TextInputStyle = object;
type AnimationStatus = object;
type FillMode = object;
type HoverController = object;
type BorderStyle = object;
