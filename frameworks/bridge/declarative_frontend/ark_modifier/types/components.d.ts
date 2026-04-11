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

interface Object {
    [key: string]: unknown;
}

interface LazyComponentBase {
    _modifiersWithKeys: Map<Symbol, AttributeModifierWithKey>;
    [key: string]: unknown;
}

declare class ArkComponent implements CommonMethod<CommonAttribute> {
    _changed: boolean;
    _modifiersWithKeys: Map<Symbol, AttributeModifierWithKey>;
    nativePtr: KNode;
    _weakPtr: JsPointerClass;
    _classType: ModifierType | undefined;
    _nativePtrChanged: boolean;
    lazyComponent: any;
    constructor(nativePtr: KNode, classType?: ModifierType);
    initialize(...args: unknown[]): void;
    applyModifierPatch(): void;
    width(value: Length): this;
    height(value: Length): this;
    size(value: SizeOptions): this;
    padding(value: Padding | Length): this;
    margin(value: Margin | Length): this;
    backgroundColor(value: ResourceColor): this;
    border(value: BorderOptions): this;
    borderStyle(value: BorderStyle | EdgeStyles): this;
    borderWidth(value: Length | EdgeWidths): this;
    borderColor(value: ResourceColor | EdgeColors): this;
    borderRadius(value: Length | BorderRadiuses): this;
    onClick(event: (event?: ClickEvent) => void): this;
    hoverEffect(value: HoverEffect): this;
    onTouch(event: (event?: TouchEvent) => void): this;
    onAppear(event: () => void): this;
    onDisAppear(event: () => void): this;
    draggable(value: boolean): this;
    key(value: string): this;
    id(value: string): this;
    clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this;
}

declare class ArkScrollable extends ArkComponent {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkBlankComponent extends ArkComponent implements CommonMethod<BlankAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
    color(value: ResourceColor): BlankAttribute;
    height(value: Length): this;
}

declare class ArkColumnComponent extends ArkComponent implements CommonMethod<ColumnAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkColumnSplitComponent extends ArkComponent implements CommonMethod<ColumnSplitAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
    resizeable(value: boolean): ColumnSplitAttribute;
    divider(value: ColumnSplitDividerStyle | null): ColumnSplitAttribute;
    clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this;
}

declare class ArkDividerComponent extends ArkComponent implements DividerAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkFlexComponent extends ArkComponent implements FlexAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkGridRowComponent extends ArkComponent implements CommonMethod<GridRowAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkGridComponent extends ArkComponent implements GridAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkGridColComponent extends ArkComponent implements GridColAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkGridItemComponent extends ArkComponent implements CommonMethod<GridItemAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkListComponent extends ArkComponent implements CommonMethod<ListAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkListItemComponent extends ArkComponent implements CommonMethod<ListItemAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkListItemGroupComponent extends ArkComponent implements CommonMethod<ListItemGroupAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkRelativeContainerComponent extends ArkComponent implements CommonMethod<RelativeContainerAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkRowComponent extends ArkComponent implements CommonMethod<RowAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkRowSplitComponent extends ArkComponent implements CommonMethod<RowSplitAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
    resizeable(value: boolean): RowSplitAttribute;
    clip(value: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute): this;
}

declare class ArkStackComponent extends ArkComponent implements StackAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkLazyVGridLayoutComponent extends ArkComponent implements CommonMethod<LazyVGridLayoutAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkWaterFlowComponent extends ArkScrollable implements CommonMethod<WaterFlowAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkCircleComponent extends ArkComponent implements CommonMethod<CircleAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkEllipseComponent extends ArkComponent implements CommonMethod<EllipseAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkLineComponent extends ArkComponent implements CommonMethod<LineAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkPathComponent extends ArkComponent implements CommonMethod<PathAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkPolygonComponent extends ArkComponent implements CommonMethod<PolygonAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkPolylineComponent extends ArkComponent implements CommonMethod<PolylineAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkRectComponent extends ArkComponent implements CommonMethod<RectAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkShapeComponent extends ArkComponent implements CommonMethod<ShapeAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkImageComponent extends ArkComponent implements ImageAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkImageAnimatorComponent extends ArkComponent implements CommonMethod<ImageAnimatorAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkImageSpanComponent extends ArkComponent implements ImageSpanAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkTextComponent extends ArkComponent implements TextAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkTextAreaComponent extends ArkComponent implements CommonMethod<TextAreaAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkTextInputComponent extends ArkComponent implements CommonMethod<TextInputAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkTextPickerComponent extends ArkComponent implements CommonMethod<TextPickerAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkTextTimerComponent extends ArkComponent implements CommonMethod<TextTimerAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkVideoComponent extends ArkComponent implements CommonMethod<VideoAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
    autoPlay(value: boolean): VideoAttribute;
    controls(value: boolean): VideoAttribute;
    loop(value: boolean): VideoAttribute;
    muted(value: boolean): VideoAttribute;
    objectFit(value: ImageFit): VideoAttribute;
    onStart(callback: () => void): VideoAttribute;
    onPause(callback: () => void): VideoAttribute;
    onFinish(callback: () => void): VideoAttribute;
    onError(callback: () => void): VideoAttribute;
    onPrepared(callback: (event: { duration: number }) => void): VideoAttribute;
    onSeeking(callback: (event: { time: number }) => void): VideoAttribute;
    onSeeked(callback: (event: { time: number }) => void): VideoAttribute;
    onUpdate(callback: (event: { time: number }) => void): VideoAttribute;
    onFullscreenChange(callback: (event: { fullscreen: boolean }) => void): VideoAttribute;
}

declare class ArkLoadingProgressComponent extends ArkComponent implements LoadingProgressAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkProgressComponent extends ArkComponent implements CommonMethod<ProgressAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkQRCodeComponent extends ArkComponent implements CommonMethod<QRCodeAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkMarqueeComponent extends ArkComponent implements CommonMethod<MarqueeAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
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
    onDotConnect(callback: object): PatternLockAttribute;
}

declare class ArkRichEditorComponent extends ArkComponent implements CommonMethod<RichEditorAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
    enableDataDetector(enable: boolean): RichEditorAttribute;
    dataDetectorConfig(config: object): RichEditorAttribute;
    copyOptions(value: CopyOptions): RichEditorAttribute;
    onPaste(callback: (event?: PasteEvent) => void): RichEditorAttribute;
    onReady(callback: () => void): RichEditorAttribute;
    onSelect(callback: (value: object) => void): RichEditorAttribute;
    aboutToIMEInput(callback: (value: object) => boolean): RichEditorAttribute;
    onIMEInputComplete(callback: (value: object) => void): RichEditorAttribute;
    aboutToDelete(callback: (value: object) => boolean): RichEditorAttribute;
    onDeleteComplete(callback: () => void): RichEditorAttribute;
    onWillAttachIME(callback: (Callback<object> | undefined)): RichEditorAttribute;
    bindSelectionMenu(spanType: object, content: CustomBuilder, responseType: ResponseType, options?: object): RichEditorAttribute;
    selectedDragPreviewStyle(value: object): RichEditorAttribute;
    customKeyboard(value: CustomBuilder): RichEditorAttribute;
    barState(value: BarState): RichEditorAttribute;
    maxLength(value: number): RichEditorAttribute;
    maxLines(value: number): RichEditorAttribute;
    enableAutoSpacing(enable: Optional<boolean>): RichEditorAttribute;
    compressLeadingPunctuation(enable: Optional<boolean>): RichEditorAttribute;
}

declare class ArkButtonComponent extends ArkComponent implements ButtonAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    type(value: object): ButtonAttribute;
    stateEffect(value: boolean): ButtonAttribute;
    fontColor(value: ResourceColor): ButtonAttribute;
    fontSize(value: number | string | Resource): ButtonAttribute;
    fontWeight(value: number | FontWeight | string): ButtonAttribute;
    fontStyle(value: FontStyle): ButtonAttribute;
    fontFamily(value: Resource | string): ButtonAttribute;
    labelStyle(value: object): ButtonAttribute;
    fontFeature(value: string): ButtonAttribute;
    size(value: object): ButtonAttribute;
    role(value: object): ButtonAttribute;
    buttonStyle(value: object): ButtonAttribute;
    controlSize(value: object): ButtonAttribute;
    onClick(callback: (event: ClickEvent, result: object) => void): ButtonAttribute;
    minFontSize(value: number | string | Resource): ButtonAttribute;
    maxFontSize(value: number | string | Resource): ButtonAttribute;
    height(value: Length): ButtonAttribute;
    width(value: Length): ButtonAttribute;
    backgroundColor(value: ResourceColor): this;
    border(value: BorderOptions): this;
    borderStyle(value: BorderStyle | EdgeStyles): this;
    borderWidth(value: Length | EdgeWidths): this;
    borderColor(value: ResourceColor | EdgeColors): this;
    borderRadius(value: Length | BorderRadiuses): this;
}

declare class ArkCheckboxComponent extends ArkComponent implements CheckboxAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    shape(value: CheckBoxShape): this;
    width(value: Length): this;
    height(value: Length): this;
    select(value: boolean): this;
    selectedColor(value: ResourceColor): this;
    unselectedColor(value: ResourceColor): this;
    mark(value: object): this;
    padding(value: Padding | Length): this;
    size(value: SizeOptions): this;
    responseRegion(value: Array<Rectangle> | Rectangle): this;
    onChange(callback: OnCheckboxChangeCallback): this;
}

declare class ArkCheckboxGroupComponent extends ArkComponent implements CheckboxGroupAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
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

declare class ArkDatePickerComponent extends ArkComponent implements CommonMethod<DatePickerAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkRadioComponent extends ArkComponent implements RadioAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkRatingComponent extends ArkComponent implements RatingAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    stars(value: number): this;
    stepSize(value: number): this;
    starStyle(value: { backgroundUri: string; foregroundUri: string; secondaryUri?: string | undefined }): this;
    onChange(callback: (value: number) => void): this;
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
    cancelButton(value: { style?: CancelButtonStyle; icon?: object }): SearchAttribute;
    searchIcon(value: object): SearchAttribute;
    fontColor(value: ResourceColor): SearchAttribute;
    placeholderColor(value: ResourceColor): SearchAttribute;
    placeholderFont(value?: object): SearchAttribute;
    textFont(value?: object): SearchAttribute;
    copyOption(value: CopyOptions): SearchAttribute;
    textAlign(value: TextAlign): SearchAttribute;
    height(value: Length): this;
    strokeWidth(value: LengthMetrics): SearchAttribute;
    strokeColor(valeu: ResourceColor): SearchAttribute;
    compressLeadingPunctuation(enable: boolean): SearchAttribute;
    selectedDragPreviewStyle(value: object): SearchAttribute;
}

declare class ArkSelectComponent extends ArkComponent implements SelectAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkSliderComponent extends ArkComponent implements SliderAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    blockColor(value: ResourceColor): this;
    trackColor(value: ResourceColor): this;
    selectedColor(value: ResourceColor): this;
    showSteps(value: boolean, options?: object): this;
    showTips(value: boolean, content?: ResourceStr): this;
    trackThickness(value: Length): this;
    onChange(callback: (value: number, mode: SliderChangeMode) => void): this;
    blockBorderColor(value: ResourceColor): this;
    blockBorderWidth(value: Length): this;
    stepColor(value: ResourceColor): this;
    trackBorderRadius(value: Length): this;
    blockSize(value: SizeOptions): this;
    blockStyle(value: SliderBlockStyle): this;
    stepSize(value: Length): this;
}

declare class ArkTextClockComponent extends ArkComponent implements CommonMethod<TextClockAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkTimePickerComponent extends ArkComponent implements TimePickerAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    loop(value: boolean): this;
    useMilitaryTime(value: boolean): this;
    disappearTextStyle(value: PickerTextStyle): this;
    textStyle(value: PickerTextStyle): this;
    selectedTextStyle(value: PickerTextStyle): this;
    onChange(callback: (value: TimePickerResult) => void): this;
    digitalCrownSensitivity(sensitivity: Optional<object>): this;
}

declare class ArkToggleComponent extends ArkComponent implements ToggleAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkAlphabetIndexerComponent extends ArkComponent {
    constructor(nativePtr: KNode, classType?: ModifierType);
    [key: string]: any;
}

declare class ArkCalendarPickerComponent extends ArkComponent {
    constructor(nativePtr: KNode, classType?: ModifierType);
    edgeAlign(alignType: CalendarAlign, offset?: Offset): this;
    textStyle(value: object): this;
    onChange(callback: (value: Date) => void): this;
    padding(value: Padding | Length | object): this;
    border(value: BorderOptions): this;
    height(value: Length): this;
    borderRadius(value: Length | BorderRadiuses): this;
    borderColor(value: ResourceColor | EdgeColors): this;
    markToday(value: boolean): this;
}

declare class ArkDataPanelComponent extends ArkComponent implements CommonMethod<DataPanelAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkGaugeComponent extends ArkComponent implements CommonMethod<GaugeAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkHyperlinkComponent extends ArkComponent implements CommonMethod<HyperlinkAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkMenuComponent extends ArkComponent implements CommonMethod<MenuAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkMenuItemComponent extends ArkComponent implements CommonMethod<MenuItemAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkNavDestinationComponent extends ArkComponent implements NavDestinationAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkNavigationComponent extends ArkComponent implements CommonMethod<NavigationAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkNavigatorComponent extends ArkComponent implements CommonMethod<NavigatorAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkNavRouterComponent extends ArkComponent implements CommonMethod<NavRouterAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkPanelComponent extends ArkComponent implements CommonMethod<PanelAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkRefreshComponent extends ArkComponent implements RefreshAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkScrollComponent extends ArkComponent implements ScrollAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkSideBarContainerComponent extends ArkComponent implements SideBarContainerAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onChange(callback: (value: boolean) => void): SideBarContainerAttribute;
    autoHide(value: boolean): SideBarContainerAttribute;
    showSideBar(value: boolean): SideBarContainerAttribute;
    maxSideBarWidth(value: number | Length): SideBarContainerAttribute;
    minSideBarWidth(value: number | Length): SideBarContainerAttribute;
    minContentWidth(value: Dimension): SideBarContainerAttribute;
    controlButton(value: object): SideBarContainerAttribute;
    divider(value: object | null): SideBarContainerAttribute;
    sideBarPosition(value: object): SideBarContainerAttribute;
    sideBarWidth(value: number | Length): SideBarContainerAttribute;
    showControlButton(value: boolean): SideBarContainerAttribute;
}

declare class ArkStepperComponent extends ArkComponent implements StepperAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onFinish(callback: () => void): this;
    onSkip(callback: () => void): this;
    onChange(callback: (prevIndex: number, index: number) => void): this;
    onNext(callback: (index: number, pendingIndex: number) => void): this;
    onPrevious(callback: (index: number, pendingIndex: number) => void): this;
}

declare class ArkStepperItemComponent extends ArkComponent implements CommonMethod<StepperItemAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkSwiperComponent extends ArkComponent implements CommonMethod<SwiperAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkSymbolGlyphComponent extends ArkComponent implements CommonMethod<SymbolGlyphAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkSymbolSpanComponent extends ArkComponent implements SymbolSpanAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkTabsComponent extends ArkComponent implements CommonMethod<TabsAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkTabContentComponent extends ArkComponent implements CommonMethod<TabContentAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkContainerPickerComponent extends ArkComponent implements UIPickerComponentAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkContainerSpanComponent extends ArkComponent implements ContainerSpanAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkComponent3DComponent extends ArkComponent implements CommonMethod<Component3DAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkEmbeddedComponent extends ArkComponent implements CommonMethod<EmbeddedComponentAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkFormComponentComponent extends ArkComponent implements CommonMethod<FormComponentAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkIndicatorComponentComponent extends ArkComponent implements CommonMethod<IndicatorComponentAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkMediaCachedImageComponent extends ArkComponent implements CommonMethod<MediaCachedImageAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkParticleComponent extends ArkComponent implements CommonMethod<ParticleAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkPluginComponent extends ArkComponent implements CommonMethod<PluginComponentAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkUnionEffectContainerComponent extends ArkComponent implements CommonMethod<UnionEffectContainerAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

type Font = object;
type IconOptions = object;
type KeyboardOptions = object;
type TextInputStyle = object;
type ContentModifier<T> = { applyContent(): T };
type AlphabetIndexerConfiguration = object;
type CheckboxConfiguration = object;
type MarkStyle = object;
type LabelStyle = object;
type ButtonType = object;
type ButtonSize = object;
type ButtonRole = object;
type ButtonStyleMode = object;
type ControlSize = object;
type ButtonCallbackResult = object;
