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
    _modifiersWithKeys: any;
    nativePtr: KNode;
    _weakPtr: JsPointerClass;
    _classType: ModifierType | undefined;
    _nativePtrChanged: boolean;
    lazyComponent: any;
    constructor(nativePtr: KNode, classType?: ModifierType);
    initialize(...args: Object[]);
    width(value: Length): this;
    height(value: Length): this;
    responseRegion(value: Array<Rectangle> | Rectangle): this;
    size(value: SizeOptions): this;
    padding(value: Padding | Length): this;
    margin(value: Margin | Length): this;
    backgroundColor(value: ResourceColor): this;
    border(value: BorderOptions): this;
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
declare class ArkImageComponent extends ArkComponent implements ImageAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkImageAnimatorComponent extends ArkComponent implements CommonMethod<ImageAnimatorAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkImageSpanComponent extends ArkComponent implements ImageSpanAttribute {
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
    onWillAttachIME(callback: (Callback<IMEClient> | undefined)): RichEditorAttribute;
    bindSelectionMenu(spanType: RichEditorSpanType, content: CustomBuilder, responseType: ResponseType, options?: SelectionMenuOptions): RichEditorAttribute;
    selectedDragPreviewStyle(value: SelectedDragPreviewStyle): RichEditorAttribute;
    customKeyboard(value: CustomBuilder): RichEditorAttribute;
    barState(value: BarState): RichEditorAttribute;
    maxLength(value: number): RichEditorAttribute;
    maxLines(value: number): RichEditorAttribute;
    enableAutoSpacing(enable: Optional<boolean>): RichEditorAttribute;
    compressLeadingPunctuation(enable: Optional<boolean>): RichEditorAttribute;
    undoStyle(style: Optional<UndoStyle>): RichEditorAttribute;
    includeFontPadding(enable: Optional<boolean>): RichEditorAttribute;
    fallbackLineSpacing(enable: Optional<boolean>): RichEditorAttribute;
    singleLine(enable: boolean): RichEditorAttribute;
}
declare class ArkRowComponent extends ArkComponent implements RowAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
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
    compressLeadingPunctuation(enable: boolean): SearchAttribute;
    selectedDragPreviewStyle(value: SelectedDragPreviewStyle): SearchAttribute;
}
declare class ArkSpanComponent implements CommonMethod<SpanAttribute> {
    _changed: boolean;
    _modifiersWithKeys: any;
    nativePtr: KNode;
    _weakPtr: JsPointerClass;
    _classType: ModifierType | undefined;
    _nativePtrChanged: boolean;
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
    controlButton(value: ButtonStyle): SideBarContainerAttribute;
    divider(value: DividerStyle | null): SideBarContainerAttribute;
    sideBarPosition(value: SideBarPosition): SideBarContainerAttribute;
    sideBarWidth(value: number | Length): SideBarContainerAttribute;
    showControlButton(value: boolean): SideBarContainerAttribute;
}
declare class ArkStackComponent extends ArkComponent implements StackAttribute {
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
declare class ArkVideoComponent extends ArkComponent implements CommonMethod<VideoAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
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
}
declare class ArkLoadingProgressComponent extends ArkComponent implements LoadingProgressAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkRefreshComponent extends ArkComponent implements RefreshAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkScrollComponent extends ArkComponent implements ScrollAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkToggleComponent extends ArkComponent implements ToggleAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkSelectComponent extends ArkComponent implements SelectAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkRadioComponent extends ArkComponent implements RadioAttribute {
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
    digitalCrownSensitivity(sensitivity: Optional<CrownSensitivity>): this;
}
declare class ArkTextPickerComponent extends ArkComponent implements TextPickerAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkContainerPicker extends ArkComponent implements UIPickerComponentAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkSliderComponent extends ArkComponent implements SliderAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    blockColor(value: ResourceColor): this;
    trackColor(value: ResourceColor): this;
    selectedColor(value: ResourceColor): this;
    showSteps(value: boolean, options?: SliderShowStepOptions): this;
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
}
declare class ArkNavigationComponent extends ArkComponent implements NavigationAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkNavRouterComponent extends ArkComponent implements NavRouterAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkNavigatorComponent extends ArkComponent implements NavigatorAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
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
}
declare class ArkDatePickerComponent extends ArkComponent implements DatePickerAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkFormComponentComponent extends ArkComponent implements FormComponentAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkEmbeddedComponent extends ArkComponent implements EmbeddedComponentAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkGaugeComponent extends ArkComponent implements GaugeAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkMarqueeComponent extends ArkComponent implements MarqueeAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkMenuComponent extends ArkComponent implements MenuAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkMenuItemComponent extends ArkComponent implements MenuItemAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkPluginComponent extends ArkComponent implements PluginComponentAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkProgressComponent extends ArkComponent implements ProgressAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkQRCodeComponent extends ArkComponent implements QRCodeAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkStepperItemComponent extends ArkComponent implements StepperItemAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkTextClockComponent extends ArkComponent implements TextClockAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkTextTimerComponent extends ArkComponent implements TextTimerAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkGridItemComponent extends ArkComponent implements GridItemAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkHyperlinkComponent extends ArkComponent implements HyperlinkAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkListComponent extends ArkComponent implements ListAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
    onReachEnd(event: () => void): this;
    onScrollStart(event: () => void): this;
    onScrollStop(event: () => void): this;
    fadingEdge(value: boolean, options?: FadingEdgeOptions | undefined): this;
    childrenMainSize(value: ChildrenMainSize): this;
}
declare class ArkListItemComponent extends ArkComponent implements ListItemAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkListItemGroupComponent extends ArkComponent implements ListItemGroupAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkRelativeContainerComponent extends ArkComponent implements RelativeContainerAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkSwiperComponent extends ArkComponent implements SwiperAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkTabsComponent extends ArkComponent implements TabsAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkTabContentComponent extends ArkComponent implements TabContentAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkWaterFlowComponent extends ArkComponent implements WaterFlowAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkCommonShapeComponent extends ArkComponent implements CommonShapeMethod<ShapeAttribute> {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
interface EllipseAttribute extends CommonMethod<EllipseAttribute> {}

interface PolylineAttribute extends CommonMethod<PolylineAttribute> {
    points(value: Array<any>): PolylineAttribute;
}
interface PolygonAttribute extends CommonMethod<PolygonAttribute> {
    points(value: Array<any>): PolygonAttribute;
}

declare class ArkCircleComponent extends ArkCommonShapeComponent implements CircleAttribute {
}
declare class ArkLineComponent extends ArkCommonShapeComponent implements LineAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkPolylineComponent extends ArkCommonShapeComponent implements PolylineAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkPolygonComponent extends ArkCommonShapeComponent implements PolygonAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkPathComponent extends ArkCommonShapeComponent implements PathAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkRectComponent extends ArkCommonShapeComponent implements RectAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class ArkShapeComponent extends ArkCommonShapeComponent implements ShapeAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
interface ParticleAttribute extends CommonMethod<ParticleAttribute> {
    disturbanceFields(fields: Array<DisturbanceFieldsOptions>): ParticleAttribute;
    emitter(fields: Array<EmitterProperty>): ParticleAttribute;
    rippleFields(fields: Array<RippleFieldOptions>): ParticleAttribute;
    velocityFields(fields: Array<VelocityFieldOptions>): ParticleAttribute;
}
declare class ArkParticleComponent extends ArkComponent implements ParticleAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
declare class CheckboxWidthModifier extends ModifierWithKey<Length> {}
declare class CheckboxHeightModifier extends ModifierWithKey<ResourceColor> {}
declare class TextForegroundColorModifier extends ModifierWithKey<ResourceColor | ColoringStrategy> {}

declare class ArkSymbolGlyphComponent extends ArkComponent implements SymbolGlyphAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkSymbolSpanComponent extends ArkComponent implements SymbolSpanAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkComponent3DComponent extends ArkComponent implements Component3DAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkContainerSpanComponent extends ArkComponent implements ContainerSpanAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}

declare class ArkLazyVGridLayoutComponent extends ArkComponent implements LazyVGridLayoutAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType);
}
