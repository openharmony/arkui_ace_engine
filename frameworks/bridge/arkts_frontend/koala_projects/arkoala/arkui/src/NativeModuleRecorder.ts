import { RuntimeType } from "./peers/SerializerBase"
import { Deserializer } from "./peers/Deserializer"
import { int32, CustomTextEncoder } from "@koalaui/common"
import { encodeToData, KInt, KPointer, KStringPtr, nullptr, pointer } from "@koalaui/interop"
import { NativeModuleEmpty } from "@koalaui/arkoala"
import { CallbackTransformer } from "./peers/CallbackTransformer"
export interface UIElement {
    nodeId: int32
    kind: string
    children: Array<UIElement>|undefined
    elementId: string|undefined
}
const NULL_POINTER = 0
const FINALIZER_POINTER = 1
export interface MenuAlign {
    type: string
    dx?: string
    dy?: string
}
export interface RootInterface {
}
export interface ComponentRootInterface {
}
export interface AbilityComponentInterface extends CommonMethodInterface,UIElement {
    setAbilityComponentOptions_value?: { want: Want }
    onConnect_value?: (() => void)
    onDisconnect_value?: (() => void)
}
export interface AlphabetIndexerInterface extends CommonMethodInterface,UIElement {
    setAlphabetIndexerOptions_options?: AlphabetIndexerOptions
    onSelected_value?: ((index: number) => void)
    color_value?: ResourceColor
    selectedColor_value?: ResourceColor
    popupColor_value?: ResourceColor
    selectedBackgroundColor_value?: ResourceColor
    popupBackground_value?: ResourceColor
    popupSelectedColor_value?: ResourceColor
    popupUnselectedColor_value?: ResourceColor
    popupItemBackgroundColor_value?: ResourceColor
    usingPopup_value?: boolean
    selectedFont_value?: Font
    popupFont_value?: Font
    popupItemFont_value?: Font
    itemSize_value?: string | number
    font_value?: Font
    onSelect_value?: OnAlphabetIndexerSelectCallback
    onRequestPopupData_value?: OnAlphabetIndexerRequestPopupDataCallback
    onPopupSelect_value?: OnAlphabetIndexerPopupSelectCallback
    selected_value?: number
    popupPosition_value?: Position
    autoCollapse_value?: boolean
    popupItemBorderRadius_value?: number
    itemBorderRadius_value?: number
    popupBackgroundBlurStyle_value?: BlurStyle
    popupTitleBackground_value?: ResourceColor
    enableHapticFeedback_value?: boolean
    alignStyle_value?: IndexerAlign
    alignStyle_offset?: Length | undefined
}
export interface AnimatorInterface extends CommonMethodInterface,UIElement {
    setAnimatorOptions_value?: string
    state_value?: AnimationStatus
    duration_value?: number
    curve_value?: Curve
    delay_value?: number
    fillMode_value?: FillMode
    iterations_value?: number
    playMode_value?: PlayMode
    motion_value?: SpringMotion | FrictionMotion | ScrollMotion
    onStart_value?: (() => void)
    onPause_value?: (() => void)
    onRepeat_value?: (() => void)
    onCancel_value?: (() => void)
    onFinish_value?: (() => void)
    onFrame_value?: ((index: number) => void)
}
export interface BadgeInterface extends CommonMethodInterface,UIElement {
    setBadgeOptions0_value?: BadgeParamWithNumber
    setBadgeOptions1_value?: BadgeParamWithString
}
export interface BlankInterface extends CommonMethodInterface,UIElement {
    setBlankOptions_min?: number | string | undefined
    color_value?: ResourceColor
}
export interface ButtonInterface extends CommonMethodInterface,UIElement {
    setButtonOptions1_options?: ButtonOptions
    setButtonOptions2_label?: ResourceStr
    setButtonOptions2_options?: ButtonOptions | undefined
    type_value?: ButtonType
    stateEffect_value?: boolean
    buttonStyle_value?: ButtonStyleMode
    controlSize_value?: ControlSize
    role_value?: ButtonRole
    fontColor_value?: ResourceColor
    fontSize_value?: Length
    fontWeight_value?: number | FontWeight | string
    fontStyle_value?: FontStyle
    fontFamily_value?: string | Resource
    contentModifier_value?: ContentModifier<any>
    labelStyle_value?: LabelStyle
}
export interface CalendarInterface {
    setCalendarOptions_value?: { date: { year: number, month: number, day: number }, currentData: MonthData, preData: MonthData, nextData: MonthData, controller?: CalendarController }
    showLunar_value?: boolean
    showHoliday_value?: boolean
    needSlide_value?: boolean
    startOfWeek_value?: number
    offDays_value?: number
    direction_value?: Axis
    currentDayStyle_value?: CurrentDayStyle
    nonCurrentDayStyle_value?: NonCurrentDayStyle
    todayStyle_value?: TodayStyle
    weekStyle_value?: WeekStyle
    workStateStyle_value?: WorkStateStyle
    onSelectChange_value?: ((event: CalendarSelectedDate) => void)
    onRequestData_value?: ((event: CalendarRequestedData) => void)
}
export interface CalendarPickerInterface extends CommonMethodInterface,UIElement {
    setCalendarPickerOptions_options?: CalendarOptions | undefined
    textStyle_value?: PickerTextStyle
    onChange_value?: ((parameter: Date) => void)
    edgeAlign_alignType?: CalendarAlign
    edgeAlign_offset?: Offset | undefined
}
export interface CanvasInterface extends CommonMethodInterface,UIElement {
    setCanvasOptions0_context?: CanvasRenderingContext2D | DrawingRenderingContext | undefined
    setCanvasOptions1_context?: CanvasRenderingContext2D | DrawingRenderingContext
    setCanvasOptions1_imageAIOptions?: ImageAIOptions
    onReady_value?: VoidCallback
    enableAnalyzer_value?: boolean
}
export interface CheckboxInterface extends CommonMethodInterface,UIElement {
    setCheckboxOptions_options?: CheckboxOptions | undefined
    select_value?: boolean
    selectedColor_value?: ResourceColor
    shape_value?: CheckBoxShape
    unselectedColor_value?: ResourceColor
    mark_value?: MarkStyle
    onChange_value?: OnCheckboxChangeCallback
    contentModifier_value?: ContentModifier<any>
}
export interface CheckboxGroupInterface extends CommonMethodInterface,UIElement {
    setCheckboxGroupOptions_options?: CheckboxGroupOptions | undefined
    selectAll_value?: boolean
    selectedColor_value?: ResourceColor
    unselectedColor_value?: ResourceColor
    mark_value?: MarkStyle
    onChange_value?: OnCheckboxGroupChangeCallback
    checkboxShape_value?: CheckBoxShape
}
export interface CircleInterface extends CommonShapeMethodInterface,UIElement {
    setCircleOptions_value?: CircleOptions | undefined
}
export interface ColumnInterface extends CommonMethodInterface,UIElement {
    setColumnOptions_options?: ColumnOptions | undefined
    alignItems_value?: HorizontalAlign
    justifyContent_value?: FlexAlign
    pointLight_value?: PointLightStyle
    reverse_value?: boolean | undefined
}
export interface ColumnSplitInterface extends CommonMethodInterface,UIElement {
    resizeable_value?: boolean
    divider_value?: ColumnSplitDividerStyle | undefined
}
export interface CommonMethodInterface {
    width_value?: Length
    height_value?: Length
    drawModifier_value?: DrawModifier | undefined
    responseRegion_value?: Array<Rectangle> | Rectangle
    mouseResponseRegion_value?: Array<Rectangle> | Rectangle
    size_value?: SizeOptions
    constraintSize_value?: ConstraintSizeOptions
    touchable_value?: boolean
    hitTestBehavior_value?: HitTestMode
    onChildTouchTest_value?: ((value: Array<TouchTestInfo>) => TouchResult)
    layoutWeight_value?: number | string
    chainWeight_value?: ChainWeightOptions
    padding_value?: Padding | Length | LocalizedPadding
    safeAreaPadding_value?: Padding | LengthMetrics | LocalizedPadding
    margin_value?: Margin | Length | LocalizedMargin
    backgroundColor_value?: ResourceColor
    pixelRound_value?: PixelRoundPolicy
    backgroundImageSize_value?: SizeOptions | ImageSize
    backgroundImagePosition_value?: Position | Alignment
    backgroundEffect_value?: BackgroundEffectOptions
    backgroundImageResizable_value?: ResizableOptions
    foregroundEffect_value?: ForegroundEffectOptions
    visualEffect_value?: VisualEffect
    backgroundFilter_value?: Filter
    foregroundFilter_value?: Filter
    compositingFilter_value?: Filter
    opacity_value?: number | Resource
    border_value?: BorderOptions
    borderStyle_value?: BorderStyle | EdgeStyles
    borderWidth_value?: Length | EdgeWidths | LocalizedEdgeWidths
    borderColor_value?: ResourceColor | EdgeColors | LocalizedEdgeColors
    borderRadius_value?: Length | BorderRadiuses | LocalizedBorderRadiuses
    borderImage_value?: BorderImageOption
    outline_value?: OutlineOptions
    outlineStyle_value?: OutlineStyle | EdgeOutlineStyles
    outlineWidth_value?: Dimension | EdgeOutlineWidths
    outlineColor_value?: ResourceColor | EdgeColors | LocalizedEdgeColors
    outlineRadius_value?: Dimension | OutlineRadiuses
    foregroundColor_value?: ResourceColor | ColoringStrategy
    onClick0_value?: ((event: ClickEvent) => void)
    onClick1_event?: ((event: ClickEvent) => void)
    onClick1_distanceThreshold?: number
    onHover_value?: ((isHover: boolean, event: HoverEvent) => void)
    onAccessibilityHover_value?: AccessibilityCallback
    hoverEffect_value?: HoverEffect
    onMouse_value?: ((event: MouseEvent) => void)
    onTouch_value?: ((event: TouchEvent) => void)
    onKeyEvent_value?: ((event: KeyEvent) => void)
    onKeyPreIme_value?: ((parameter: KeyEvent) => boolean)
    focusable_value?: boolean
    onFocus_value?: (() => void)
    onBlur_value?: (() => void)
    tabIndex_value?: number
    defaultFocus_value?: boolean
    groupDefaultFocus_value?: boolean
    focusOnTouch_value?: boolean
    focusBox_value?: FocusBoxStyle
    animation_value?: AnimateParam
    transition0_value?: TransitionOptions | TransitionEffect
    transition1_effect?: TransitionEffect
    transition1_onFinish?: TransitionFinishCallback | undefined
    motionBlur_value?: MotionBlurOptions
    brightness_value?: number
    contrast_value?: number
    grayscale_value?: number
    colorBlend_value?: Color | string | Resource
    saturate_value?: number
    sepia_value?: number
    invert_value?: number | InvertOptions
    hueRotate_value?: number | string
    useShadowBatching_value?: boolean
    useEffect0_value?: boolean
    useEffect1_useEffect?: boolean
    useEffect1_effectType?: EffectType
    renderGroup_value?: boolean
    freeze_value?: boolean
    translate_value?: TranslateOptions
    scale_value?: ScaleOptions
    gridSpan_value?: number
    gridOffset_value?: number
    rotate_value?: RotateOptions
    transform_value?: Object
    onAppear_value?: (() => void)
    onDisAppear_value?: (() => void)
    onAttach_value?: (() => void)
    onDetach_value?: (() => void)
    onAreaChange_value?: ((oldValue: Area, newValue: Area) => void)
    visibility_value?: Visibility
    flexGrow_value?: number
    flexShrink_value?: number
    flexBasis_value?: number | string
    alignSelf_value?: ItemAlign
    displayPriority_value?: number
    zIndex_value?: number
    direction_value?: Direction
    align_value?: Alignment
    position_value?: Position | Edges | LocalizedEdges
    markAnchor_value?: Position | LocalizedPosition
    offset_value?: Position | Edges | LocalizedEdges
    enabled_value?: boolean
    useSizeType_value?: { xs?: number | { span: number, offset: number }, sm?: number | { span: number, offset: number }, md?: number | { span: number, offset: number }, lg?: number | { span: number, offset: number } }
    alignRules0_value?: AlignRuleOption
    alignRules1_value?: LocalizedAlignRuleOptions
    aspectRatio_value?: number
    clickEffect_value?: ClickEffect | undefined
    onDragStart_value?: ((event: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo)
    onDragEnter_value?: ((event: DragEvent, extraParams?: string) => void)
    onDragMove_value?: ((event: DragEvent, extraParams?: string) => void)
    onDragLeave_value?: ((event: DragEvent, extraParams?: string) => void)
    onDrop_value?: ((event: DragEvent, extraParams?: string) => void)
    onDragEnd_value?: ((event: DragEvent, extraParams?: string) => void)
    allowDrop_value?: Array<UniformDataType> | undefined
    draggable_value?: boolean
    dragPreview_value?: CustomBuilder | DragItemInfo | string
    onPreDrag_value?: ((parameter: PreDragStatus) => void)
    linearGradient_value?: { angle?: number | string, direction?: GradientDirection, colors: Array<[ ResourceColor, number ]>, repeating?: boolean }
    sweepGradient_value?: { center: [ Length, Length ], start?: number | string, end?: number | string, rotation?: number | string, colors: Array<[ ResourceColor, number ]>, repeating?: boolean }
    radialGradient_value?: { center: [ Length, Length ], radius: number | string, colors: Array<[ ResourceColor, number ]>, repeating?: boolean }
    motionPath_value?: MotionPathOptions
    shadow_value?: ShadowOptions | ShadowStyle
    clip0_value?: boolean
    clip1_value?: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute
    clipShape_value?: CircleShape | EllipseShape | PathShape | RectShape
    mask0_value?: ProgressMask
    mask1_value?: CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute | ProgressMask
    maskShape_value?: CircleShape | EllipseShape | PathShape | RectShape
    key_value?: string
    id_value?: string
    geometryTransition0_value?: string
    geometryTransition1_id?: string
    geometryTransition1_options?: GeometryTransitionOptions | undefined
    stateStyles_value?: StateStyles
    restoreId_value?: number
    sphericalEffect_value?: number
    lightUpEffect_value?: number
    pixelStretchEffect_value?: PixelStretchEffectOptions
    accessibilityGroup0_value?: boolean
    accessibilityGroup1_isGroup?: boolean
    accessibilityGroup1_accessibilityOptions?: AccessibilityOptions
    accessibilityText0_value?: string
    accessibilityText1_value?: Resource
    accessibilityTextHint_value?: string
    accessibilityDescription0_value?: string
    accessibilityDescription1_value?: Resource
    accessibilityLevel_value?: string
    accessibilityVirtualNode_value?: CustomBuilder
    accessibilityChecked_value?: boolean
    accessibilitySelected_value?: boolean
    obscured_value?: Array<ObscuredReasons>
    reuseId_value?: string
    renderFit_value?: RenderFit
    gestureModifier_value?: GestureModifier
    backgroundBrightness_value?: BackgroundBrightnessOptions
    onGestureJudgeBegin_value?: ((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult)
    onGestureRecognizerJudgeBegin0_value?: GestureRecognizerJudgeBeginCallback
    onGestureRecognizerJudgeBegin1_callback?: GestureRecognizerJudgeBeginCallback
    onGestureRecognizerJudgeBegin1_exposeInnerGesture?: boolean
    shouldBuiltInRecognizerParallelWith_value?: ShouldBuiltInRecognizerParallelWithCallback
    monopolizeEvents_value?: boolean
    onTouchIntercept_value?: ((parameter: TouchEvent) => HitTestMode)
    onSizeChange_value?: SizeChangeCallback
    customProperty_name?: string
    customProperty_value?: Object | undefined
    expandSafeArea_types?: Array<SafeAreaType> | undefined
    expandSafeArea_edges?: Array<SafeAreaEdge> | undefined
    background_builder?: CustomBuilder
    background_options?: { align?: Alignment } | undefined
    backgroundImage_src?: ResourceStr | PixelMap
    backgroundImage_repeat?: ImageRepeat | undefined
    backgroundBlurStyle_value?: BlurStyle
    backgroundBlurStyle_options?: BackgroundBlurStyleOptions | undefined
    foregroundBlurStyle_value?: BlurStyle
    foregroundBlurStyle_options?: ForegroundBlurStyleOptions | undefined
    focusScopeId0_id?: string
    focusScopeId0_isGroup?: boolean | undefined
    focusScopeId1_id?: string
    focusScopeId1_isGroup?: boolean | undefined
    focusScopeId1_arrowStepOut?: boolean | undefined
    focusScopePriority_scopeId?: string
    focusScopePriority_priority?: FocusPriority | undefined
    gesture_gesture?: GestureControl.GestureType
    gesture_mask?: GestureMask | undefined
    priorityGesture_gesture?: GestureControl.GestureType
    priorityGesture_mask?: GestureMask | undefined
    parallelGesture_gesture?: GestureControl.GestureType
    parallelGesture_mask?: GestureMask | undefined
    blur_value?: number
    blur_options?: BlurOptions | undefined
    linearGradientBlur_value?: number
    linearGradientBlur_options?: LinearGradientBlurOptions
    backdropBlur_value?: number
    backdropBlur_options?: BlurOptions | undefined
    sharedTransition_id?: string
    sharedTransition_options?: sharedTransitionOptions | undefined
    chainMode_direction?: Axis
    chainMode_style?: ChainStyle
    dragPreviewOptions_value?: DragPreviewOptions
    dragPreviewOptions_options?: DragInteractionOptions | undefined
    overlay_value?: string | CustomBuilder | ComponentContent
    overlay_options?: OverlayOptions | undefined
    blendMode_value?: BlendMode
    blendMode_type?: BlendApplyType | undefined
    advancedBlendMode_effect?: BlendMode | Blender
    advancedBlendMode_type?: BlendApplyType | undefined
    bindPopup_show?: boolean
    bindPopup_popup?: PopupOptions | CustomPopupOptions
    bindMenu0_content?: Array<MenuElement> | CustomBuilder
    bindMenu0_options?: MenuOptions | undefined
    bindMenu1_isShow?: boolean
    bindMenu1_content?: Array<MenuElement> | CustomBuilder
    bindMenu1_options?: MenuOptions | undefined
    bindContextMenu0_content?: CustomBuilder
    bindContextMenu0_responseType?: ResponseType
    bindContextMenu0_options?: ContextMenuOptions | undefined
    bindContextMenu1_isShown?: boolean
    bindContextMenu1_content?: CustomBuilder
    bindContextMenu1_options?: ContextMenuOptions | undefined
    bindContentCover0_isShow?: boolean | undefined
    bindContentCover0_builder?: CustomBuilder
    bindContentCover0_type?: ModalTransition | undefined
    bindContentCover1_isShow?: boolean | undefined
    bindContentCover1_builder?: CustomBuilder
    bindContentCover1_options?: ContentCoverOptions | undefined
    bindSheet_isShow?: boolean | undefined
    bindSheet_builder?: CustomBuilder
    bindSheet_options?: SheetOptions | undefined
    onVisibleAreaChange_ratios?: Array<number>
    onVisibleAreaChange_event?: VisibleAreaChangeCallback
    keyboardShortcut_value?: string | FunctionKey
    keyboardShortcut_keys?: Array<ModifierKey>
    keyboardShortcut_action?: (() => void) | undefined
}
export interface CommonShapeMethodInterface extends CommonMethodInterface,UIElement {
    stroke_value?: ResourceColor
    fill_value?: ResourceColor
    strokeDashOffset_value?: number | string
    strokeLineCap_value?: LineCapStyle
    strokeLineJoin_value?: LineJoinStyle
    strokeMiterLimit_value?: number | string
    strokeOpacity_value?: number | string | Resource
    fillOpacity_value?: number | string | Resource
    strokeWidth_value?: Length
    antiAlias_value?: boolean
    strokeDashArray_value?: Array<any>
}
export interface CommonInterface extends CommonMethodInterface,UIElement {
}
export interface ScrollableCommonMethodInterface extends CommonMethodInterface,UIElement {
    scrollBar_value?: BarState
    scrollBarColor_value?: Color | number | string
    scrollBarWidth_value?: number | string
    nestedScroll_value?: NestedScrollOptions
    enableScrollInteraction_value?: boolean
    friction_value?: number | Resource
    onScroll_value?: ((scrollOffset: number, scrollState: ScrollState) => void)
    onWillScroll_value?: ScrollOnWillScrollCallback | undefined
    onDidScroll_value?: ScrollOnWillScrollCallback | undefined
    onReachStart_value?: (() => void)
    onReachEnd_value?: (() => void)
    onScrollStart_value?: (() => void)
    onScrollStop_value?: (() => void)
    flingSpeedLimit_value?: number
    clipContent_value?: ContentClipMode | RectShape
    edgeEffect_edgeEffect?: EdgeEffect
    edgeEffect_options?: EdgeEffectOptions | undefined
    fadingEdge_enabled?: boolean | undefined
    fadingEdge_options?: FadingEdgeOptions | undefined
}
export interface Component3DInterface extends CommonMethodInterface,UIElement {
    setComponent3DOptions_sceneOptions?: SceneOptions | undefined
    environment_value?: ResourceStr
    shader_value?: ResourceStr
    shaderImageTexture_value?: ResourceStr
    shaderInputBuffer_value?: Array<number>
    renderWidth_value?: Dimension
    renderHeight_value?: Dimension
    customRender_uri?: ResourceStr
    customRender_selfRenderUpdate?: boolean
}
export interface ContainerSpanInterface {
    textBackgroundStyle_value?: TextBackgroundStyle
}
export interface CounterInterface extends CommonMethodInterface,UIElement {
    onInc_value?: VoidCallback
    onDec_value?: VoidCallback
    enableDec_value?: boolean
    enableInc_value?: boolean
}
export interface DataPanelInterface extends CommonMethodInterface,UIElement {
    setDataPanelOptions_options?: DataPanelOptions
    closeEffect_value?: boolean
    valueColors_value?: Array<ResourceColor | LinearGradient_data_panel>
    trackBackgroundColor_value?: ResourceColor
    strokeWidth_value?: Length
    trackShadow_value?: DataPanelShadowOptions
    contentModifier_value?: ContentModifier<any>
}
export interface DatePickerInterface extends CommonMethodInterface,UIElement {
    setDatePickerOptions_options?: DatePickerOptions | undefined
    lunar_value?: boolean
    disappearTextStyle_value?: PickerTextStyle
    textStyle_value?: PickerTextStyle
    selectedTextStyle_value?: PickerTextStyle
    onChange_value?: ((value: DatePickerResult) => void)
    onDateChange_value?: ((parameter: Date) => void)
}
export interface DividerInterface extends CommonMethodInterface,UIElement {
    vertical_value?: boolean
    color_value?: ResourceColor
    strokeWidth_value?: number | string
    lineCap_value?: LineCapStyle
}
export interface EffectComponentInterface extends CommonMethodInterface,UIElement {
}
export interface EllipseInterface extends CommonShapeMethodInterface,UIElement {
    setEllipseOptions_options?: EllipseOptions | undefined
}
export interface EmbeddedComponentInterface extends CommonMethodInterface,UIElement {
    setEmbeddedComponentOptions_loader?: Want
    setEmbeddedComponentOptions_type?: EmbeddedType
    onTerminated_value?: ((parameter: TerminationInfo) => void)
    onError_value?: Object
}
export interface FlexInterface extends CommonMethodInterface,UIElement {
    setFlexOptions_value?: FlexOptions | undefined
    pointLight_value?: PointLightStyle
}
export interface FlowItemInterface extends CommonMethodInterface,UIElement {
}
export interface FolderStackInterface extends CommonMethodInterface,UIElement {
    setFolderStackOptions_options?: FolderStackOptions | undefined
    alignContent_value?: Alignment
    onFolderStateChange_value?: OnFoldStatusChangeCallback
    onHoverStatusChange_value?: OnHoverStatusChangeCallback
    enableAnimation_value?: boolean
    autoHalfFold_value?: boolean
}
export interface FormComponentInterface extends CommonMethodInterface,UIElement {
    setFormComponentOptions_value?: FormInfo
    size_value?: SizeOptions
    moduleName_value?: string
    dimension_value?: FormDimension
    allowUpdate_value?: boolean
    visibility_value?: Visibility
    onAcquired_value?: ((parameter: FormCallbackInfo) => void)
    onError_value?: ((info: { errcode: number, msg: string }) => void)
    onRouter_value?: ((info: any) => void)
    onUninstall_value?: ((parameter: FormCallbackInfo) => void)
    onLoad_value?: (() => void)
}
export interface FormLinkInterface extends CommonMethodInterface,UIElement {
    setFormLinkOptions_options?: FormLinkOptions
}
export interface GaugeInterface extends CommonMethodInterface,UIElement {
    setGaugeOptions_options?: GaugeOptions
    value_value?: number
    startAngle_value?: number
    endAngle_value?: number
    colors_value?: ResourceColor | LinearGradient_common | Array<[ ResourceColor | LinearGradient_common, number ]>
    strokeWidth_value?: Length
    description_value?: CustomBuilder
    trackShadow_value?: GaugeShadowOptions
    indicator_value?: GaugeIndicatorOptions
    privacySensitive_value?: boolean | undefined
    contentModifier_value?: ContentModifier<any>
}
export interface GridInterface extends ScrollableCommonMethodInterface,UIElement {
    setGridOptions_scroller?: Scroller | undefined
    setGridOptions_layoutOptions?: GridLayoutOptions | undefined
    columnsTemplate_value?: string
    rowsTemplate_value?: string
    columnsGap_value?: Length
    rowsGap_value?: Length
    scrollBarWidth_value?: number | string
    scrollBarColor_value?: Color | number | string
    scrollBar_value?: BarState
    onScrollBarUpdate_value?: ((index: number, offset: number) => ComputedBarAttribute)
    onScrollIndex_value?: ((first: number, last: number) => void)
    cachedCount0_value?: number
    cachedCount1_count?: number
    cachedCount1_show?: boolean
    editMode_value?: boolean
    multiSelectable_value?: boolean
    maxCount_value?: number
    minCount_value?: number
    cellLength_value?: number
    layoutDirection_value?: GridDirection
    supportAnimation_value?: boolean
    onItemDragStart_value?: ((event: ItemDragInfo, itemIndex: number) => (() => any))
    onItemDragEnter_value?: ((event: ItemDragInfo) => void)
    onItemDragMove_value?: ((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void)
    onItemDragLeave_value?: ((event: ItemDragInfo, itemIndex: number) => void)
    onItemDrop_value?: ((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void)
    nestedScroll_value?: NestedScrollOptions
    enableScrollInteraction_value?: boolean
    friction_value?: number | Resource
    alignItems_value?: GridItemAlignment | undefined
    onScroll_value?: ((scrollOffset: number, scrollState: ScrollState) => void)
    onReachStart_value?: (() => void)
    onReachEnd_value?: (() => void)
    onScrollStart_value?: (() => void)
    onScrollStop_value?: (() => void)
    onScrollFrameBegin_value?: ((offset: number, state: ScrollState) => { offsetRemain: number })
    edgeEffect_value?: EdgeEffect
    edgeEffect_options?: EdgeEffectOptions | undefined
}
export interface GridItemInterface extends CommonMethodInterface,UIElement {
    setGridItemOptions_value?: GridItemOptions | undefined
    rowStart_value?: number
    rowEnd_value?: number
    columnStart_value?: number
    columnEnd_value?: number
    forceRebuild_value?: boolean
    selectable_value?: boolean
    selected_value?: boolean
    onSelect_value?: ((parameter: boolean) => void)
}
export interface GridColInterface extends CommonMethodInterface,UIElement {
    setGridColOptions_option?: GridColOptions | undefined
    span_value?: number | GridColColumnOption
    gridColOffset_value?: number | GridColColumnOption
    order_value?: number | GridColColumnOption
}
export interface GridContainerInterface extends ColumnInterface,UIElement {
    setGridContainerOptions_value?: GridContainerOptions | undefined
}
export interface GridRowInterface extends CommonMethodInterface,UIElement {
    setGridRowOptions_option?: GridRowOptions | undefined
    onBreakpointChange_value?: ((breakpoints: string) => void)
    alignItems_value?: ItemAlign
}
export interface HyperlinkInterface extends CommonMethodInterface,UIElement {
    setHyperlinkOptions_address?: string | Resource
    setHyperlinkOptions_content?: string | Resource | undefined
    color_value?: Color | number | string | Resource
}
export interface ImageInterface extends CommonMethodInterface,UIElement {
    setImageOptions0_src?: PixelMap | ResourceStr | DrawableDescriptor
    setImageOptions1_src?: PixelMap | ResourceStr | DrawableDescriptor | ImageContent
    setImageOptions2_src?: PixelMap | ResourceStr | DrawableDescriptor
    setImageOptions2_imageAIOptions?: ImageAIOptions
    alt_value?: string | Resource | PixelMap
    matchTextDirection_value?: boolean
    fitOriginalSize_value?: boolean
    fillColor_value?: ResourceColor
    objectFit_value?: ImageFit
    objectRepeat_value?: ImageRepeat
    autoResize_value?: boolean
    renderMode_value?: ImageRenderMode
    dynamicRangeMode_value?: DynamicRangeMode
    interpolation_value?: ImageInterpolation
    sourceSize_value?: ImageSourceSize
    syncLoad_value?: boolean
    colorFilter_value?: ColorFilter | DrawingColorFilter
    copyOption_value?: CopyOptions
    draggable_value?: boolean
    pointLight_value?: PointLightStyle
    edgeAntialiasing_value?: number
    onComplete_value?: ((event?: { width: number, height: number, componentWidth: number, componentHeight: number, loadingStatus: number, contentWidth: number, contentHeight: number, contentOffsetX: number, contentOffsetY: number }) => void)
    onError_value?: ImageErrorCallback
    onFinish_value?: (() => void)
    enableAnalyzer_value?: boolean
    analyzerConfig_value?: ImageAnalyzerConfig
    resizable_value?: ResizableOptions
    privacySensitive_value?: boolean
    enhancedImageQuality_value?: ResolutionQuality
}
export interface ImageAnimatorInterface extends CommonMethodInterface,UIElement {
    images_value?: Array<ImageFrameInfo>
    state_value?: AnimationStatus
    duration_value?: number
    reverse_value?: boolean
    fixedSize_value?: boolean
    preDecode_value?: number
    fillMode_value?: FillMode
    iterations_value?: number
    onStart_value?: (() => void)
    onPause_value?: (() => void)
    onRepeat_value?: (() => void)
    onCancel_value?: (() => void)
    onFinish_value?: (() => void)
}
export interface ImageSpanInterface extends BaseSpanInterface,UIElement {
    setImageSpanOptions_value?: ResourceStr | PixelMap
    verticalAlign_value?: ImageSpanAlignment
    colorFilter_value?: ColorFilter | DrawingColorFilter
    objectFit_value?: ImageFit
    onComplete_value?: ImageCompleteCallback
    onError_value?: ImageErrorCallback
    alt_value?: PixelMap
}
export interface LineInterface extends CommonShapeMethodInterface,UIElement {
    setLineOptions_options?: LineOptions | undefined
    startPoint_value?: Array<any>
    endPoint_value?: Array<any>
}
export interface ListInterface extends ScrollableCommonMethodInterface,UIElement {
    setListOptions_options?: ListOptions | undefined
    alignListItem_value?: ListItemAlign
    listDirection_value?: Axis
    scrollBar_value?: BarState
    contentStartOffset_value?: number
    contentEndOffset_value?: number
    divider_value?: ListDividerOptions | undefined
    editMode_value?: boolean
    multiSelectable_value?: boolean
    cachedCount0_value?: number
    cachedCount1_count?: number
    cachedCount1_show?: boolean
    chainAnimation_value?: boolean
    chainAnimationOptions_value?: ChainAnimationOptions
    sticky_value?: StickyStyle
    scrollSnapAlign_value?: ScrollSnapAlign
    nestedScroll_value?: NestedScrollOptions
    enableScrollInteraction_value?: boolean
    friction_value?: number | Resource
    childrenMainSize_value?: ChildrenMainSize
    maintainVisibleContentPosition_value?: boolean
    onScroll_value?: ((scrollOffset: number, scrollState: ScrollState) => void)
    onScrollIndex_value?: ((start: number, end: number, center: number) => void)
    onScrollVisibleContentChange_value?: OnScrollVisibleContentChangeCallback
    onReachStart_value?: (() => void)
    onReachEnd_value?: (() => void)
    onScrollStart_value?: (() => void)
    onScrollStop_value?: (() => void)
    onItemDelete_value?: ((index: number) => boolean)
    onItemMove_value?: ((from: number, to: number) => boolean)
    onItemDragStart_value?: ((event: ItemDragInfo, itemIndex: number) => (() => any))
    onItemDragEnter_value?: ((event: ItemDragInfo) => void)
    onItemDragMove_value?: ((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void)
    onItemDragLeave_value?: ((event: ItemDragInfo, itemIndex: number) => void)
    onItemDrop_value?: ((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void)
    onScrollFrameBegin_value?: ((offset: number, state: ScrollState) => { offsetRemain: number })
    lanes_value?: number | LengthConstrain
    lanes_gutter?: Dimension | undefined
    edgeEffect_value?: EdgeEffect
    edgeEffect_options?: EdgeEffectOptions | undefined
}
export interface ListItemInterface extends CommonMethodInterface,UIElement {
    setListItemOptions0_value?: ListItemOptions | undefined
    setListItemOptions1_value?: string | undefined
    sticky_value?: Sticky
    editable_value?: boolean | EditMode
    selectable_value?: boolean
    selected_value?: boolean
    swipeAction_value?: SwipeActionOptions
    onSelect_value?: ((parameter: boolean) => void)
}
export interface ListItemGroupInterface extends CommonMethodInterface,UIElement {
    setListItemGroupOptions_options?: ListItemGroupOptions | undefined
    divider_value?: ListDividerOptions | undefined
    childrenMainSize_value?: ChildrenMainSize
}
export interface LoadingProgressInterface extends CommonMethodInterface,UIElement {
    color_value?: ResourceColor
    enableLoading_value?: boolean
    contentModifier_value?: ContentModifier<any>
}
export interface LocationButtonInterface extends SecurityComponentMethodInterface,UIElement {
    setLocationButtonOptions1_options?: LocationButtonOptions
    onClick_value?: ((event: ClickEvent, result: LocationButtonOnClickResult) => void)
}
export interface MarqueeInterface extends CommonMethodInterface,UIElement {
    setMarqueeOptions_options?: MarqueeOptions
    fontColor_value?: ResourceColor
    fontSize_value?: Length
    allowScale_value?: boolean
    fontWeight_value?: number | FontWeight | string
    fontFamily_value?: string | Resource
    marqueeUpdateStrategy_value?: MarqueeUpdateStrategy
    onStart_value?: (() => void)
    onBounce_value?: (() => void)
    onFinish_value?: (() => void)
}
export interface MediaCachedImageInterface extends ImageInterface,UIElement {
    setMediaCachedImageOptions_src?: PixelMap | ResourceStr | DrawableDescriptor | ASTCResource
}
export interface MenuInterface extends CommonMethodInterface,UIElement {
    fontSize_value?: Length
    font_value?: Font
    fontColor_value?: ResourceColor
    radius_value?: Dimension | BorderRadiuses
    menuItemDivider_value?: DividerStyleOptions | undefined
    menuItemGroupDivider_value?: DividerStyleOptions | undefined
    subMenuExpandingMode_value?: SubMenuExpandingMode
}
export interface MenuItemInterface extends CommonMethodInterface,UIElement {
    setMenuItemOptions_value?: MenuItemOptions | CustomBuilder | undefined
    selected_value?: boolean
    selectIcon_value?: boolean | ResourceStr | SymbolGlyphModifier
    onChange_value?: ((parameter: boolean) => void)
    contentFont_value?: Font
    contentFontColor_value?: ResourceColor
    labelFont_value?: Font
    labelFontColor_value?: ResourceColor
}
export interface MenuItemGroupInterface extends CommonMethodInterface,UIElement {
    setMenuItemGroupOptions_value?: MenuItemGroupOptions | undefined
}
export interface NavDestinationInterface extends CommonMethodInterface,UIElement {
    hideTitleBar0_value?: boolean
    hideTitleBar1_hide?: boolean
    hideTitleBar1_animated?: boolean
    onShown_value?: (() => void)
    onHidden_value?: (() => void)
    onBackPressed_value?: (() => boolean)
    mode_value?: NavDestinationMode
    backButtonIcon_value?: ResourceStr | PixelMap | SymbolGlyphModifier
    menus_value?: Array<NavigationMenuItem> | CustomBuilder
    onReady_value?: ((parameter: NavDestinationContext) => void)
    onWillAppear_value?: (() => void)
    onWillDisappear_value?: (() => void)
    onWillShow_value?: (() => void)
    onWillHide_value?: (() => void)
    systemBarStyle_value?: SystemBarStyle | undefined
    recoverable_value?: boolean | undefined
    systemTransition_value?: NavigationSystemTransitionType
    title_value?: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource
    title_options?: NavigationTitleOptions | undefined
    toolbarConfiguration_toolbarParam?: Array<ToolbarItem> | CustomBuilder
    toolbarConfiguration_options?: NavigationToolbarOptions | undefined
    hideToolBar_hide?: boolean
    hideToolBar_animated?: boolean | undefined
    ignoreLayoutSafeArea_types?: Array<LayoutSafeAreaType> | undefined
    ignoreLayoutSafeArea_edges?: Array<LayoutSafeAreaEdge> | undefined
}
export interface NavRouterInterface extends CommonMethodInterface,UIElement {
    setNavRouterOptions1_value?: RouteInfo
    onStateChange_value?: ((parameter: boolean) => void)
    mode_value?: NavRouteMode
}
export interface NavigatorInterface extends CommonMethodInterface,UIElement {
    setNavigatorOptions0_value?: { target: string, type?: NavigationType } | undefined
    active_value?: boolean
    type_value?: NavigationType
    target_value?: string
    params_value?: Object
}
export interface NodeContainerInterface extends CommonMethodInterface,UIElement {
    setNodeContainerOptions_controller?: NodeController
}
export interface PanelInterface extends CommonMethodInterface,UIElement {
    setPanelOptions_show?: boolean
    mode_value?: PanelMode
    type_value?: PanelType
    dragBar_value?: boolean
    customHeight_value?: Dimension | PanelHeight
    fullHeight_value?: number | string
    halfHeight_value?: number | string
    miniHeight_value?: number | string
    show_value?: boolean
    backgroundMask_value?: ResourceColor
    showCloseIcon_value?: boolean
    onChange_value?: ((width: number, height: number, mode: PanelMode) => void)
    onHeightChange_value?: ((index: number) => void)
}
export interface PasteButtonInterface extends SecurityComponentMethodInterface,UIElement {
    setPasteButtonOptions1_options?: PasteButtonOptions
    onClick_value?: ((event: ClickEvent, result: PasteButtonOnClickResult) => void)
}
export interface PathInterface extends CommonShapeMethodInterface,UIElement {
    setPathOptions_options?: PathOptions | undefined
    commands_value?: string
}
export interface PatternLockInterface extends CommonMethodInterface,UIElement {
    setPatternLockOptions_controller?: PatternLockController | undefined
    sideLength_value?: Length
    circleRadius_value?: Length
    backgroundColor_value?: ResourceColor
    regularColor_value?: ResourceColor
    selectedColor_value?: ResourceColor
    activeColor_value?: ResourceColor
    pathColor_value?: ResourceColor
    pathStrokeWidth_value?: number | string
    onPatternComplete_value?: ((input: Array<number>) => void)
    autoReset_value?: boolean
    onDotConnect_value?: ((index: number) => void)
    activateCircleStyle_value?: CircleStyleOptions | undefined
}
export interface PluginComponentInterface extends CommonMethodInterface,UIElement {
    setPluginComponentOptions_options?: PluginComponentOptions
    onComplete_value?: VoidCallback
    onError_value?: PluginErrorCallback
}
export interface PolygonInterface extends CommonShapeMethodInterface,UIElement {
    setPolygonOptions_options?: PolygonOptions | undefined
    points_value?: Array<any>
}
export interface PolylineInterface extends CommonShapeMethodInterface,UIElement {
    setPolylineOptions_options?: PolylineOptions | undefined
    points_value?: Array<any>
}
export interface ProgressInterface extends CommonMethodInterface,UIElement {
    setProgressOptions_options?: ProgressOptions
    value_value?: number
    color_value?: ResourceColor | LinearGradient_common
    style_value?: LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions
    privacySensitive_value?: boolean | undefined
    contentModifier_value?: ContentModifier<any>
}
export interface QRCodeInterface extends CommonMethodInterface,UIElement {
    setQRCodeOptions_value?: string
    color_value?: ResourceColor
    backgroundColor_value?: ResourceColor
    contentOpacity_value?: number | Resource
}
export interface RadioInterface extends CommonMethodInterface,UIElement {
    setRadioOptions_options?: RadioOptions
    checked_value?: boolean
    onChange_value?: ((parameter: boolean) => void)
    radioStyle_value?: RadioStyle | undefined
    contentModifier_value?: ContentModifier<any>
}
export interface RatingInterface extends CommonMethodInterface,UIElement {
    setRatingOptions_options?: RatingOptions | undefined
    stars_value?: number
    stepSize_value?: number
    starStyle_value?: StarStyleOptions
    onChange_value?: ((index: number) => void)
    contentModifier_value?: ContentModifier<any>
}
export interface RectInterface extends CommonShapeMethodInterface,UIElement {
    setRectOptions_options?: RectOptions | RoundedRectOptions | undefined
    radiusWidth_value?: number | string
    radiusHeight_value?: number | string
    radius_value?: number | string | Array<any>
}
export interface RefreshInterface extends CommonMethodInterface,UIElement {
    setRefreshOptions_value?: RefreshOptions
    onStateChange_value?: ((state: RefreshStatus) => void)
    onRefreshing_value?: (() => void)
    refreshOffset_value?: number
    pullToRefresh_value?: boolean
    onOffsetChange_value?: ((index: number) => void)
    pullDownRatio_value?: number | undefined
}
export interface RelativeContainerInterface extends CommonMethodInterface,UIElement {
    guideLine_value?: Array<GuideLineStyle>
    barrier0_value?: Array<BarrierStyle>
    barrier1_value?: Array<LocalizedBarrierStyle>
}
export interface RichEditorInterface extends CommonMethodInterface,UIElement {
    setRichEditorOptions0_value?: RichEditorOptions
    setRichEditorOptions1_options?: RichEditorStyledStringOptions
    onReady_value?: (() => void)
    onSelect_value?: ((parameter: RichEditorSelection) => void)
    onSelectionChange_value?: ((parameter: RichEditorRange) => void)
    aboutToIMEInput_value?: ((parameter: RichEditorInsertValue) => boolean)
    onIMEInputComplete_value?: ((parameter: RichEditorTextSpanResult) => void)
    onDidIMEInput_value?: ((parameter: TextRange) => void)
    aboutToDelete_value?: ((parameter: RichEditorDeleteValue) => boolean)
    onDeleteComplete_value?: (() => void)
    copyOptions_value?: CopyOptions
    onPaste_value?: PasteEventCallback
    enableDataDetector_value?: boolean
    enablePreviewText_value?: boolean
    dataDetectorConfig_value?: TextDataDetectorConfig
    caretColor_value?: ResourceColor
    selectedBackgroundColor_value?: ResourceColor
    onEditingChange_value?: ((parameter: boolean) => void)
    enterKeyType_value?: EnterKeyType
    onSubmit_value?: SubmitCallback
    onWillChange_value?: ((parameter: RichEditorChangeValue) => boolean)
    onDidChange_value?: OnDidChangeCallback
    onCut_value?: ((parameter: CutEvent) => void)
    onCopy_value?: ((parameter: CopyEvent) => void)
    editMenuOptions_value?: EditMenuOptions
    enableKeyboardOnFocus_value?: boolean
    enableHapticFeedback_value?: boolean
    barState_value?: BarState
    bindSelectionMenu_spanType?: RichEditorSpanType
    bindSelectionMenu_content?: CustomBuilder
    bindSelectionMenu_responseType?: ResponseType | RichEditorResponseType
    bindSelectionMenu_options?: SelectionMenuOptions | undefined
    customKeyboard_value?: CustomBuilder
    customKeyboard_options?: KeyboardOptions | undefined
    placeholder_value?: ResourceStr
    placeholder_style?: PlaceholderStyle | undefined
}
export interface RichTextInterface extends CommonMethodInterface,UIElement {
    setRichTextOptions_content?: string
    onStart_value?: (() => void)
    onComplete_value?: (() => void)
}
export interface RootSceneInterface extends CommonMethodInterface,UIElement {
    setRootSceneOptions_session?: RootSceneSession
}
export interface RowInterface extends CommonMethodInterface,UIElement {
    setRowOptions_options?: RowOptions | undefined
    alignItems_value?: VerticalAlign
    justifyContent_value?: FlexAlign
    pointLight_value?: PointLightStyle
    reverse_value?: boolean | undefined
}
export interface RowSplitInterface extends CommonMethodInterface,UIElement {
    resizeable_value?: boolean
}
export interface SaveButtonInterface extends SecurityComponentMethodInterface,UIElement {
    setSaveButtonOptions1_options?: SaveButtonOptions
    onClick_value?: ((event: ClickEvent, result: SaveButtonOnClickResult) => void)
}
export interface ScreenInterface extends CommonMethodInterface,UIElement {
    setScreenOptions_screenId?: number
}
export interface ScrollInterface extends ScrollableCommonMethodInterface,UIElement {
    setScrollOptions_scroller?: Scroller | undefined
    scrollable_value?: ScrollDirection
    onScroll_value?: ((scrollOffset: number, scrollState: ScrollState) => void)
    onWillScroll_value?: ScrollOnWillScrollCallback | undefined
    onDidScroll_value?: ScrollOnWillScrollCallback | undefined
    onScrollEdge_value?: OnScrollEdgeCallback
    onScrollStart_value?: (() => void)
    onScrollEnd_value?: (() => void)
    onScrollStop_value?: (() => void)
    scrollBar_value?: BarState
    scrollBarColor_value?: Color | number | string
    scrollBarWidth_value?: number | string
    onScrollFrameBegin_value?: OnScrollFrameBeginCallback
    nestedScroll_value?: NestedScrollOptions
    enableScrollInteraction_value?: boolean
    friction_value?: number | Resource
    scrollSnap_value?: ScrollSnapOptions
    enablePaging_value?: boolean
    initialOffset_value?: OffsetOptions
    edgeEffect_edgeEffect?: EdgeEffect
    edgeEffect_options?: EdgeEffectOptions | undefined
}
export interface ScrollBarInterface extends CommonMethodInterface,UIElement {
    setScrollBarOptions_value?: ScrollBarOptions
    enableNestedScroll_value?: boolean | undefined
}
export interface SearchInterface extends CommonMethodInterface,UIElement {
    setSearchOptions_options?: SearchOptions | undefined
    fontColor_value?: ResourceColor
    searchIcon_value?: IconOptions | SymbolGlyphModifier
    cancelButton_value?: CancelButtonOptions | CancelButtonSymbolOptions
    textIndent_value?: Dimension
    onEditChange_value?: ((parameter: boolean) => void)
    selectedBackgroundColor_value?: ResourceColor
    caretStyle_value?: CaretStyle
    placeholderColor_value?: ResourceColor
    placeholderFont_value?: Font | undefined
    textFont_value?: Font | undefined
    enterKeyType_value?: EnterKeyType
    onSubmit0_value?: ((breakpoints: string) => void)
    onSubmit1_value?: SearchSubmitCallback
    onChange_value?: EditableTextOnChangeCallback
    onTextSelectionChange_value?: OnTextSelectionChangeCallback
    onContentScroll_value?: OnContentScrollCallback
    onCopy_value?: ((breakpoints: string) => void)
    onCut_value?: ((breakpoints: string) => void)
    onPaste_value?: OnPasteCallback
    copyOption_value?: CopyOptions
    maxLength_value?: number
    textAlign_value?: TextAlign
    enableKeyboardOnFocus_value?: boolean
    selectionMenuHidden_value?: boolean
    minFontSize_value?: number | string | Resource
    maxFontSize_value?: number | string | Resource
    decoration_value?: TextDecorationOptions
    letterSpacing_value?: number | string | Resource
    lineHeight_value?: number | string | Resource
    type_value?: SearchType
    fontFeature_value?: string
    onWillInsert_value?: ((parameter: InsertValue) => boolean)
    onDidInsert_value?: ((parameter: InsertValue) => void)
    onWillDelete_value?: ((parameter: DeleteValue) => boolean)
    onDidDelete_value?: ((parameter: DeleteValue) => void)
    editMenuOptions_value?: EditMenuOptions
    enablePreviewText_value?: boolean
    enableHapticFeedback_value?: boolean
    searchButton_value?: string
    searchButton_option?: SearchButtonOptions | undefined
    inputFilter_value?: ResourceStr
    inputFilter_error?: ((breakpoints: string) => void) | undefined
    customKeyboard_value?: CustomBuilder
    customKeyboard_options?: KeyboardOptions | undefined
}
export interface SecurityComponentMethodInterface {
    iconSize_value?: Dimension
    layoutDirection_value?: SecurityComponentLayoutDirection
    position_value?: Position
    markAnchor_value?: Position
    offset_value?: Position | Edges | LocalizedEdges
    fontSize_value?: Dimension
    fontStyle_value?: FontStyle
    fontWeight_value?: number | FontWeight | string
    fontFamily_value?: string | Resource
    fontColor_value?: ResourceColor
    iconColor_value?: ResourceColor
    backgroundColor_value?: ResourceColor
    borderStyle_value?: BorderStyle
    borderWidth_value?: Dimension
    borderColor_value?: ResourceColor
    borderRadius_value?: Dimension
    padding_value?: Padding | Dimension
    textIconSpace_value?: Dimension
    key_value?: string
    width_value?: Length
    height_value?: Length
    size_value?: SizeOptions
    constraintSize_value?: ConstraintSizeOptions
}
export interface SelectInterface extends CommonMethodInterface,UIElement {
    setSelectOptions_options?: Array<SelectOption>
    selected_value?: number | Resource
    value_value?: ResourceStr
    font_value?: Font
    fontColor_value?: ResourceColor
    selectedOptionBgColor_value?: ResourceColor
    selectedOptionFont_value?: Font
    selectedOptionFontColor_value?: ResourceColor
    optionBgColor_value?: ResourceColor
    optionFont_value?: Font
    optionFontColor_value?: ResourceColor
    onSelect_value?: ((index: number, value: string) => void)
    space_value?: Length
    arrowPosition_value?: ArrowPosition
    optionWidth_value?: Dimension | OptionWidthMode
    optionHeight_value?: Dimension
    menuBackgroundColor_value?: ResourceColor
    menuBackgroundBlurStyle_value?: BlurStyle
    controlSize_value?: ControlSize
    menuItemContentModifier_value?: ContentModifier<any>
    divider_value?: DividerOptions | undefined
    menuAlign_alignType?: MenuAlignType
    menuAlign_offset?: Offset | undefined
}
export interface ShapeInterface extends CommonMethodInterface,UIElement {
    setShapeOptions0_value?: PixelMap
    viewPort_value?: ViewportRect
    stroke_value?: ResourceColor
    fill_value?: ResourceColor
    strokeDashOffset_value?: number | string
    strokeDashArray_value?: Array<any>
    strokeLineCap_value?: LineCapStyle
    strokeLineJoin_value?: LineJoinStyle
    strokeMiterLimit_value?: number | string
    strokeOpacity_value?: number | string | Resource
    fillOpacity_value?: number | string | Resource
    strokeWidth_value?: number | string
    antiAlias_value?: boolean
    mesh_value?: Array<any>
    mesh_column?: number
    mesh_row?: number
}
export interface SliderInterface extends CommonMethodInterface,UIElement {
    setSliderOptions_options?: SliderOptions | undefined
    blockColor_value?: ResourceColor
    trackColor_value?: ResourceColor | LinearGradient_common
    selectedColor_value?: ResourceColor
    minLabel_value?: string
    maxLabel_value?: string
    showSteps_value?: boolean
    trackThickness_value?: Length
    onChange_value?: ((value: number, mode: SliderChangeMode) => void)
    blockBorderColor_value?: ResourceColor
    blockBorderWidth_value?: Length
    stepColor_value?: ResourceColor
    trackBorderRadius_value?: Length
    selectedBorderRadius_value?: Dimension
    blockSize_value?: SizeOptions
    blockStyle_value?: SliderBlockStyle
    stepSize_value?: Length
    sliderInteractionMode_value?: SliderInteraction
    minResponsiveDistance_value?: number
    contentModifier_value?: ContentModifier<any>
    slideRange_value?: SlideRange
    showTips_value?: boolean
    showTips_content?: ResourceStr | undefined
}
export interface BaseSpanInterface extends CommonMethodInterface,UIElement {
    textBackgroundStyle_value?: TextBackgroundStyle
    baselineOffset_value?: LengthMetrics
}
export interface SpanInterface extends BaseSpanInterface,UIElement {
    setSpanOptions_value?: string | Resource
    font_value?: Font
    fontColor_value?: ResourceColor
    fontSize_value?: number | string | Resource
    fontStyle_value?: FontStyle
    fontWeight_value?: number | FontWeight | string
    fontFamily_value?: string | Resource
    decoration_value?: DecorationStyleInterface
    letterSpacing_value?: number | string
    textCase_value?: TextCase
    lineHeight_value?: Length
    textShadow_value?: ShadowOptions | Array<ShadowOptions>
}
export interface StackInterface extends CommonMethodInterface,UIElement {
    setStackOptions_options?: StackOptions | undefined
    alignContent_value?: Alignment
    pointLight_value?: PointLightStyle
}
export interface StepperInterface extends CommonMethodInterface,UIElement {
    setStepperOptions_value?: { index?: number } | undefined
    onFinish_value?: (() => void)
    onSkip_value?: (() => void)
    onChange_value?: ((first: number, last: number) => void)
    onNext_value?: ((first: number, last: number) => void)
    onPrevious_value?: ((first: number, last: number) => void)
}
export interface StepperItemInterface extends CommonMethodInterface,UIElement {
    prevLabel_value?: string
    nextLabel_value?: string
    status_value?: ItemState | undefined
}
export interface SwiperInterface extends CommonMethodInterface,UIElement {
    setSwiperOptions_controller?: SwiperController | undefined
    index_value?: number
    autoPlay_value?: boolean
    interval_value?: number
    indicator0_value?: DotIndicator | DigitIndicator | boolean
    indicator1_value?: IndicatorComponentController
    loop_value?: boolean
    duration_value?: number
    vertical_value?: boolean
    itemSpace_value?: number | string
    displayMode_value?: SwiperDisplayMode
    cachedCount_value?: number
    effectMode_value?: EdgeEffect
    disableSwipe_value?: boolean
    curve_value?: Curve | string | ICurve
    onChange_value?: ((index: number) => void)
    indicatorStyle_value?: IndicatorStyle | undefined
    onAnimationStart_value?: OnSwiperAnimationStartCallback
    onAnimationEnd_value?: OnSwiperAnimationEndCallback
    onGestureSwipe_value?: OnSwiperGestureSwipeCallback
    nestedScroll_value?: SwiperNestedScrollMode
    customContentTransition_value?: SwiperContentAnimatedTransition
    onContentDidScroll_value?: ContentDidScrollCallback
    indicatorInteractive_value?: boolean
    displayArrow_value?: ArrowStyle | boolean
    displayArrow_isHoverShow?: boolean | undefined
    displayCount_value?: number | string | SwiperAutoFill
    displayCount_swipeByGroup?: boolean | undefined
    prevMargin_value?: Length
    prevMargin_ignoreBlank?: boolean | undefined
    nextMargin_value?: Length
    nextMargin_ignoreBlank?: boolean | undefined
}
export interface IndicatorComponentInterface extends CommonMethodInterface,UIElement {
    setIndicatorComponentOptions_controller?: IndicatorComponentController | undefined
    initialIndex_value?: number
    count_value?: number
    style_value?: DotIndicator | DigitIndicator
    loop_value?: boolean
    vertical_value?: boolean
    onChange_value?: ((index: number) => void)
}
export interface SymbolGlyphInterface extends CommonMethodInterface,UIElement {
    setSymbolGlyphOptions_value?: Resource | undefined
    fontSize_value?: number | string | Resource
    fontColor_value?: Array<ResourceColor>
    fontWeight_value?: number | FontWeight | string
    effectStrategy_value?: SymbolEffectStrategy
    renderingStrategy_value?: SymbolRenderingStrategy
    symbolEffect0_symbolEffect?: SymbolEffect
    symbolEffect0_isActive?: boolean | undefined
    symbolEffect1_symbolEffect?: SymbolEffect
    symbolEffect1_triggerValue?: number | undefined
}
export interface SymbolSpanInterface extends CommonMethodInterface,UIElement {
    setSymbolSpanOptions_value?: Resource
    fontSize_value?: number | string | Resource
    fontColor_value?: Array<ResourceColor>
    fontWeight_value?: number | FontWeight | string
    effectStrategy_value?: SymbolEffectStrategy
    renderingStrategy_value?: SymbolRenderingStrategy
}
export interface TabsInterface extends CommonMethodInterface,UIElement {
    setTabsOptions_options?: TabsOptions | undefined
    vertical_value?: boolean
    barPosition_value?: BarPosition
    scrollable_value?: boolean
    barMode0_value?: BarMode
    barMode1_value?: BarMode
    barMode1_options?: ScrollableBarModeOptions | undefined
    barWidth_value?: Length
    barHeight_value?: Length
    animationDuration_value?: number
    animationMode_value?: AnimationMode | undefined
    edgeEffect_value?: EdgeEffect | undefined
    onChange_value?: ((index: number) => void)
    onTabBarClick_value?: ((index: number) => void)
    onAnimationStart_value?: OnTabsAnimationStartCallback
    onAnimationEnd_value?: OnTabsAnimationEndCallback
    onGestureSwipe_value?: OnTabsGestureSwipeCallback
    fadingEdge_value?: boolean
    divider_value?: DividerStyle | undefined
    barOverlap_value?: boolean
    barBackgroundColor_value?: ResourceColor
    barGridAlign_value?: BarGridColumnOptions
    customContentTransition_value?: TabsCustomContentTransitionCallback
    barBackgroundBlurStyle0_value?: BlurStyle
    barBackgroundBlurStyle1_style?: BlurStyle
    barBackgroundBlurStyle1_options?: BackgroundBlurStyleOptions
    barBackgroundEffect_value?: BackgroundEffectOptions
    onContentWillChange_value?: OnTabsContentWillChangeCallback
    barModeScrollable_options?: ScrollableBarModeOptions
}
export interface TabContentInterface extends CommonMethodInterface,UIElement {
    tabBar0_value?: string | Resource | CustomBuilder | TabBarOptions
    tabBar1_value?: SubTabBarStyle | BottomTabBarStyle
    onWillShow_value?: VoidCallback
    onWillHide_value?: VoidCallback
}
export interface TextInterface extends CommonMethodInterface,UIElement {
    setTextOptions_content?: string | Resource | undefined
    setTextOptions_value?: TextOptions | undefined
    font0_value?: Font
    font1_fontValue?: Font
    font1_options?: FontSettingOptions | undefined
    fontColor_value?: ResourceColor
    fontSize_value?: number | string | Resource
    minFontSize_value?: number | string | Resource
    maxFontSize_value?: number | string | Resource
    minFontScale_value?: number | Resource
    maxFontScale_value?: number | Resource
    fontStyle_value?: FontStyle
    fontWeight0_value?: number | FontWeight | string
    fontWeight1_weight?: number | FontWeight | string
    fontWeight1_options?: FontSettingOptions | undefined
    lineSpacing_value?: LengthMetrics
    textAlign_value?: TextAlign
    lineHeight_value?: number | string | Resource
    textOverflow_value?: TextOverflowOptions
    fontFamily_value?: string | Resource
    maxLines_value?: number
    decoration_value?: DecorationStyleInterface
    letterSpacing_value?: number | string
    textCase_value?: TextCase
    baselineOffset_value?: number | string
    copyOption_value?: CopyOptions
    draggable_value?: boolean
    textShadow_value?: ShadowOptions | Array<ShadowOptions>
    heightAdaptivePolicy_value?: TextHeightAdaptivePolicy
    textIndent_value?: Length
    wordBreak_value?: WordBreak
    lineBreakStrategy_value?: LineBreakStrategy
    onCopy_value?: ((breakpoints: string) => void)
    caretColor_value?: ResourceColor
    selectedBackgroundColor_value?: ResourceColor
    ellipsisMode_value?: EllipsisMode
    enableDataDetector_value?: boolean
    dataDetectorConfig_value?: TextDataDetectorConfig
    onTextSelectionChange_value?: ((first: number, last: number) => void)
    fontFeature_value?: string
    privacySensitive_value?: boolean
    textSelectable_value?: TextSelectableMode
    editMenuOptions_value?: EditMenuOptions
    halfLeading_value?: boolean
    enableHapticFeedback_value?: boolean
    selection_selectionStart?: number
    selection_selectionEnd?: number
    bindSelectionMenu_spanType?: TextSpanType
    bindSelectionMenu_content?: CustomBuilder
    bindSelectionMenu_responseType?: TextResponseType
    bindSelectionMenu_options?: SelectionMenuOptions | undefined
}
export interface TextAreaInterface extends CommonMethodInterface,UIElement {
    setTextAreaOptions_value?: TextAreaOptions | undefined
    placeholderColor_value?: ResourceColor
    placeholderFont_value?: Font
    enterKeyType_value?: EnterKeyType
    textAlign_value?: TextAlign
    caretColor_value?: ResourceColor
    fontColor_value?: ResourceColor
    fontSize_value?: Length
    fontStyle_value?: FontStyle
    fontWeight_value?: number | FontWeight | string
    fontFamily_value?: ResourceStr
    textOverflow_value?: TextOverflow
    textIndent_value?: Dimension
    caretStyle_value?: CaretStyle
    selectedBackgroundColor_value?: ResourceColor
    onSubmit0_value?: ((enterKey: EnterKeyType) => void)
    onSubmit1_value?: TextAreaSubmitCallback
    onChange_value?: EditableTextOnChangeCallback
    onTextSelectionChange_value?: ((first: number, last: number) => void)
    onContentScroll_value?: ((first: number, last: number) => void)
    onEditChange_value?: ((parameter: boolean) => void)
    onCopy_value?: ((breakpoints: string) => void)
    onCut_value?: ((breakpoints: string) => void)
    onPaste_value?: ((value: string, event: PasteEvent) => void)
    copyOption_value?: CopyOptions
    enableKeyboardOnFocus_value?: boolean
    maxLength_value?: number
    style_value?: TextContentStyle
    barState_value?: BarState
    selectionMenuHidden_value?: boolean
    minFontSize_value?: number | string | Resource
    maxFontSize_value?: number | string | Resource
    heightAdaptivePolicy_value?: TextHeightAdaptivePolicy
    maxLines_value?: number
    wordBreak_value?: WordBreak
    lineBreakStrategy_value?: LineBreakStrategy
    decoration_value?: TextDecorationOptions
    letterSpacing_value?: number | string | Resource
    lineSpacing_value?: LengthMetrics
    lineHeight_value?: number | string | Resource
    type_value?: TextAreaType
    enableAutoFill_value?: boolean
    contentType_value?: ContentType
    fontFeature_value?: string
    onWillInsert_value?: ((parameter: InsertValue) => boolean)
    onDidInsert_value?: ((parameter: InsertValue) => void)
    onWillDelete_value?: ((parameter: DeleteValue) => boolean)
    onDidDelete_value?: ((parameter: DeleteValue) => void)
    editMenuOptions_value?: EditMenuOptions
    enablePreviewText_value?: boolean
    enableHapticFeedback_value?: boolean
    inputFilter_value?: ResourceStr
    inputFilter_error?: ((breakpoints: string) => void) | undefined
    showCounter_value?: boolean
    showCounter_options?: InputCounterOptions | undefined
    customKeyboard_value?: CustomBuilder
    customKeyboard_options?: KeyboardOptions | undefined
}
export interface TextClockInterface extends CommonMethodInterface,UIElement {
    setTextClockOptions_options?: TextClockOptions | undefined
    format_value?: string
    onDateChange_value?: ((index: number) => void)
    fontColor_value?: ResourceColor
    fontSize_value?: Length
    fontStyle_value?: FontStyle
    fontWeight_value?: number | FontWeight | string
    fontFamily_value?: ResourceStr
    textShadow_value?: ShadowOptions | Array<ShadowOptions>
    fontFeature_value?: string
    contentModifier_value?: ContentModifier<any>
    dateTimeOptions_value?: DateTimeOptions | undefined
}
export interface TextInputInterface extends CommonMethodInterface,UIElement {
    setTextInputOptions_value?: TextInputOptions | undefined
    type_value?: InputType
    contentType_value?: ContentType
    placeholderColor_value?: ResourceColor
    textOverflow_value?: TextOverflow
    textIndent_value?: Dimension
    placeholderFont_value?: Font | undefined
    enterKeyType_value?: EnterKeyType
    caretColor_value?: ResourceColor
    onEditChanged_value?: ((parameter: boolean) => void)
    onEditChange_value?: ((parameter: boolean) => void)
    onSubmit_value?: OnSubmitCallback
    onChange_value?: EditableTextOnChangeCallback
    onTextSelectionChange_value?: OnTextSelectionChangeCallback
    onContentScroll_value?: OnContentScrollCallback
    maxLength_value?: number
    fontColor_value?: ResourceColor
    fontSize_value?: Length
    fontStyle_value?: FontStyle
    fontWeight_value?: number | FontWeight | string
    fontFamily_value?: ResourceStr
    onCopy_value?: ((breakpoints: string) => void)
    onCut_value?: ((breakpoints: string) => void)
    onPaste_value?: OnPasteCallback
    copyOption_value?: CopyOptions
    showPasswordIcon_value?: boolean
    textAlign_value?: TextAlign
    style_value?: TextInputStyle | TextContentStyle
    caretStyle_value?: CaretStyle
    selectedBackgroundColor_value?: ResourceColor
    caretPosition_value?: number
    enableKeyboardOnFocus_value?: boolean
    passwordIcon_value?: PasswordIcon
    showError_value?: ResourceStr | undefined
    showUnit_value?: CustomBuilder
    showUnderline_value?: boolean
    underlineColor_value?: ResourceColor | UnderlineColor | undefined
    selectionMenuHidden_value?: boolean
    barState_value?: BarState
    maxLines_value?: number
    wordBreak_value?: WordBreak
    lineBreakStrategy_value?: LineBreakStrategy
    cancelButton0_value?: CancelButtonOptions
    cancelButton1_value?: CancelButtonSymbolOptions
    selectAll_value?: boolean
    minFontSize_value?: number | string | Resource
    maxFontSize_value?: number | string | Resource
    heightAdaptivePolicy_value?: TextHeightAdaptivePolicy
    enableAutoFill_value?: boolean
    decoration_value?: TextDecorationOptions
    letterSpacing_value?: number | string | Resource
    lineHeight_value?: number | string | Resource
    passwordRules_value?: string
    fontFeature_value?: string
    showPassword_value?: boolean
    onSecurityStateChange_value?: ((parameter: boolean) => void)
    onWillInsert_value?: ((parameter: InsertValue) => boolean)
    onDidInsert_value?: ((parameter: InsertValue) => void)
    onWillDelete_value?: ((parameter: DeleteValue) => boolean)
    onDidDelete_value?: ((parameter: DeleteValue) => void)
    editMenuOptions_value?: EditMenuOptions
    enablePreviewText_value?: boolean
    enableHapticFeedback_value?: boolean
    inputFilter_value?: ResourceStr
    inputFilter_error?: ((breakpoints: string) => void) | undefined
    customKeyboard_value?: CustomBuilder
    customKeyboard_options?: KeyboardOptions | undefined
    showCounter_value?: boolean
    showCounter_options?: InputCounterOptions | undefined
}
export interface TextPickerInterface extends CommonMethodInterface,UIElement {
    setTextPickerOptions_options?: TextPickerOptions | undefined
    defaultPickerItemHeight_value?: number | string
    canLoop_value?: boolean
    disappearTextStyle_value?: PickerTextStyle
    textStyle_value?: PickerTextStyle
    selectedTextStyle_value?: PickerTextStyle
    onAccept_value?: ((value: string, index: number) => void)
    onCancel_value?: (() => void)
    onChange_value?: ((value: string | Array<string>, index: number | Array<number>) => void)
    selectedIndex_value?: number | Array<number>
    divider_value?: DividerOptions | undefined
    gradientHeight_value?: Dimension
}
export interface TextTimerInterface extends CommonMethodInterface,UIElement {
    setTextTimerOptions_options?: TextTimerOptions | undefined
    format_value?: string
    fontColor_value?: ResourceColor
    fontSize_value?: Length
    fontStyle_value?: FontStyle
    fontWeight_value?: number | FontWeight | string
    fontFamily_value?: ResourceStr
    onTimer_value?: ((first: number, last: number) => void)
    textShadow_value?: ShadowOptions | Array<ShadowOptions>
    contentModifier_value?: ContentModifier<any>
}
export interface TimePickerInterface extends CommonMethodInterface,UIElement {
    setTimePickerOptions_options?: TimePickerOptions | undefined
    useMilitaryTime_value?: boolean
    loop_value?: boolean
    disappearTextStyle_value?: PickerTextStyle
    textStyle_value?: PickerTextStyle
    selectedTextStyle_value?: PickerTextStyle
    dateTimeOptions_value?: DateTimeOptions
    onChange_value?: ((value: TimePickerResult) => void)
    enableHapticFeedback_value?: boolean
}
export interface ToggleInterface extends CommonMethodInterface,UIElement {
    setToggleOptions_options?: ToggleOptions
    onChange_value?: ((parameter: boolean) => void)
    contentModifier_value?: ContentModifier<any>
    selectedColor_value?: ResourceColor
    switchPointColor_value?: ResourceColor
    switchStyle_value?: SwitchStyle
}
export interface VideoInterface extends CommonMethodInterface,UIElement {
    setVideoOptions_value?: VideoOptions
    muted_value?: boolean
    autoPlay_value?: boolean
    controls_value?: boolean
    loop_value?: boolean
    objectFit_value?: ImageFit
    onStart_value?: VoidCallback
    onPause_value?: VoidCallback
    onFinish_value?: VoidCallback
    onFullscreenChange_value?: ((parameter: FullscreenInfo) => void)
    onPrepared_value?: ((parameter: PreparedInfo) => void)
    onSeeking_value?: ((parameter: PlaybackInfo) => void)
    onSeeked_value?: ((parameter: PlaybackInfo) => void)
    onUpdate_value?: ((parameter: PlaybackInfo) => void)
    onError_value?: (() => void)
    onStop_value?: (() => void)
    enableAnalyzer_value?: boolean
    analyzerConfig_value?: ImageAnalyzerConfig
}
export interface WebInterface extends CommonMethodInterface,UIElement {
    setWebOptions_value?: WebOptions
    javaScriptAccess_value?: boolean
    fileAccess_value?: boolean
    onlineImageAccess_value?: boolean
    domStorageAccess_value?: boolean
    imageAccess_value?: boolean
    mixedMode_value?: MixedMode
    zoomAccess_value?: boolean
    geolocationAccess_value?: boolean
    javaScriptProxy_value?: JavaScriptProxy
    password_value?: boolean
    cacheMode_value?: CacheMode
    darkMode_value?: WebDarkMode
    forceDarkAccess_value?: boolean
    mediaOptions_value?: WebMediaOptions
    tableData_value?: boolean
    wideViewModeAccess_value?: boolean
    overviewModeAccess_value?: boolean
    overScrollMode_value?: OverScrollMode
    textZoomAtio_value?: number
    textZoomRatio_value?: number
    databaseAccess_value?: boolean
    initialScale_value?: number
    userAgent_value?: string
    metaViewport_value?: boolean
    onPageEnd_value?: ((parameter: OnPageEndEvent) => void)
    onPageBegin_value?: ((parameter: OnPageBeginEvent) => void)
    onProgressChange_value?: ((parameter: OnProgressChangeEvent) => void)
    onTitleReceive_value?: ((parameter: OnTitleReceiveEvent) => void)
    onGeolocationHide_value?: (() => void)
    onGeolocationShow_value?: ((parameter: OnGeolocationShowEvent) => void)
    onRequestSelected_value?: (() => void)
    onAlert_value?: ((parameter: OnAlertEvent) => boolean)
    onBeforeUnload_value?: ((parameter: OnBeforeUnloadEvent) => boolean)
    onConfirm_value?: ((parameter: OnConfirmEvent) => boolean)
    onPrompt_value?: ((parameter: OnPromptEvent) => boolean)
    onConsole_value?: ((parameter: OnConsoleEvent) => boolean)
    onErrorReceive_value?: ((parameter: OnErrorReceiveEvent) => void)
    onHttpErrorReceive_value?: ((parameter: OnHttpErrorReceiveEvent) => void)
    onDownloadStart_value?: ((parameter: OnDownloadStartEvent) => void)
    onRefreshAccessedHistory_value?: ((parameter: OnRefreshAccessedHistoryEvent) => void)
    onUrlLoadIntercept_value?: ((event?: { data: string | WebResourceRequest }) => boolean)
    onSslErrorReceive_value?: ((event?: { handler: Function, error: Object }) => void)
    onRenderExited0_value?: ((parameter: OnRenderExitedEvent) => void)
    onRenderExited1_value?: ((event?: { detail: Object }) => boolean)
    onShowFileSelector_value?: ((parameter: OnShowFileSelectorEvent) => boolean)
    onFileSelectorShow_value?: ((event?: { callback: Function, fileSelector: Object }) => void)
    onResourceLoad_value?: ((parameter: OnResourceLoadEvent) => void)
    onFullScreenExit_value?: (() => void)
    onFullScreenEnter_value?: OnFullScreenEnterCallback
    onScaleChange_value?: ((parameter: OnScaleChangeEvent) => void)
    onHttpAuthRequest_value?: ((parameter: OnHttpAuthRequestEvent) => boolean)
    onInterceptRequest_value?: ((parameter: OnInterceptRequestEvent) => WebResourceResponse)
    onPermissionRequest_value?: ((parameter: OnPermissionRequestEvent) => void)
    onScreenCaptureRequest_value?: ((parameter: OnScreenCaptureRequestEvent) => void)
    onContextMenuShow_value?: ((parameter: OnContextMenuShowEvent) => boolean)
    onContextMenuHide_value?: OnContextMenuHideCallback
    mediaPlayGestureAccess_value?: boolean
    onSearchResultReceive_value?: ((parameter: OnSearchResultReceiveEvent) => void)
    onScroll_value?: ((parameter: OnScrollEvent) => void)
    onSslErrorEventReceive_value?: ((parameter: OnSslErrorEventReceiveEvent) => void)
    onSslErrorEvent_value?: OnSslErrorEventCallback
    onClientAuthenticationRequest_value?: ((parameter: OnClientAuthenticationEvent) => void)
    onWindowNew_value?: ((parameter: OnWindowNewEvent) => void)
    onWindowExit_value?: (() => void)
    multiWindowAccess_value?: boolean
    onInterceptKeyEvent_value?: ((parameter: KeyEvent) => boolean)
    webStandardFont_value?: string
    webSerifFont_value?: string
    webSansSerifFont_value?: string
    webFixedFont_value?: string
    webFantasyFont_value?: string
    webCursiveFont_value?: string
    defaultFixedFontSize_value?: number
    defaultFontSize_value?: number
    minFontSize_value?: number
    minLogicalFontSize_value?: number
    defaultTextEncodingFormat_value?: string
    forceDisplayScrollBar_value?: boolean
    blockNetwork_value?: boolean
    horizontalScrollBarAccess_value?: boolean
    verticalScrollBarAccess_value?: boolean
    onTouchIconUrlReceived_value?: ((parameter: OnTouchIconUrlReceivedEvent) => void)
    onFaviconReceived_value?: ((parameter: OnFaviconReceivedEvent) => void)
    onPageVisible_value?: ((parameter: OnPageVisibleEvent) => void)
    onDataResubmitted_value?: ((parameter: OnDataResubmittedEvent) => void)
    pinchSmooth_value?: boolean
    allowWindowOpenMethod_value?: boolean
    onAudioStateChanged_value?: ((parameter: OnAudioStateChangedEvent) => void)
    onFirstContentfulPaint_value?: ((parameter: OnFirstContentfulPaintEvent) => void)
    onFirstMeaningfulPaint_value?: OnFirstMeaningfulPaintCallback
    onLargestContentfulPaint_value?: OnLargestContentfulPaintCallback
    onLoadIntercept_value?: ((parameter: OnLoadInterceptEvent) => boolean)
    onControllerAttached_value?: (() => void)
    onOverScroll_value?: ((parameter: OnOverScrollEvent) => void)
    onSafeBrowsingCheckResult_value?: OnSafeBrowsingCheckResultCallback
    onNavigationEntryCommitted_value?: OnNavigationEntryCommittedCallback
    onIntelligentTrackingPreventionResult_value?: OnIntelligentTrackingPreventionCallback
    javaScriptOnDocumentStart_value?: Array<ScriptItem>
    javaScriptOnDocumentEnd_value?: Array<ScriptItem>
    layoutMode_value?: WebLayoutMode
    nestedScroll_value?: NestedScrollOptions | NestedScrollOptionsExt
    enableNativeEmbedMode_value?: boolean
    onNativeEmbedLifecycleChange_value?: ((event: NativeEmbedDataInfo) => void)
    onNativeEmbedVisibilityChange_value?: OnNativeEmbedVisibilityChangeCallback
    onNativeEmbedGestureEvent_value?: ((event: NativeEmbedTouchInfo) => void)
    copyOptions_value?: CopyOptions
    onOverrideUrlLoading_value?: OnOverrideUrlLoadingCallback
    textAutosizing_value?: boolean
    enableNativeMediaPlayer_value?: NativeMediaPlayerConfig
    enableSmoothDragResize_value?: boolean
    onRenderProcessNotResponding_value?: OnRenderProcessNotRespondingCallback
    onRenderProcessResponding_value?: OnRenderProcessRespondingCallback
    selectionMenuOptions_value?: Array<ExpandedMenuItemOptions>
    onViewportFitChanged_value?: OnViewportFitChangedCallback
    onInterceptKeyboardAttach_value?: WebKeyboardCallback
    onAdsBlocked_value?: OnAdsBlockedCallback
    keyboardAvoidMode_value?: WebKeyboardAvoidMode
    editMenuOptions_value?: EditMenuOptions
    enableHapticFeedback_value?: boolean
    registerNativeEmbedRule_tag?: string
    registerNativeEmbedRule_type?: string
    bindSelectionMenu_elementType?: WebElementType
    bindSelectionMenu_content?: CustomBuilder
    bindSelectionMenu_responseType?: WebResponseType
    bindSelectionMenu_options?: SelectionMenuOptionsExt | undefined
}
export interface WindowSceneInterface extends CommonMethodInterface,UIElement {
    setWindowSceneOptions_persistentId?: number
    attractionEffect_destination?: Position
    attractionEffect_fraction?: number
}
export interface XComponentInterface extends CommonMethodInterface,UIElement {
    setXComponentOptions0_value?: { id: string, type: string, libraryname?: string, controller?: XComponentController }
    setXComponentOptions1_value?: { id: string, type: string, libraryname?: string, controller?: XComponentController }
    setXComponentOptions2_options?: XComponentOptions
    onLoad_value?: OnNativeLoadCallback
    onDestroy_value?: VoidCallback
    enableAnalyzer_value?: boolean
    enableSecure_value?: boolean
}
export interface SideBarContainerInterface extends CommonMethodInterface,UIElement {
    setSideBarContainerOptions_type?: SideBarContainerType | undefined
    showSideBar_value?: boolean
    controlButton_value?: ButtonStyle
    showControlButton_value?: boolean
    onChange_value?: ((parameter: boolean) => void)
    sideBarWidth0_value?: number
    sideBarWidth1_value?: Length
    minSideBarWidth0_value?: number
    minSideBarWidth1_value?: Length
    maxSideBarWidth0_value?: number
    maxSideBarWidth1_value?: Length
    autoHide_value?: boolean
    sideBarPosition_value?: SideBarPosition
    divider_value?: DividerStyle | undefined
    minContentWidth_value?: Dimension
}
export interface RemoteWindowInterface extends CommonMethodInterface,UIElement {
    setRemoteWindowOptions_target?: WindowAnimationTarget
}
export interface WaterFlowInterface extends ScrollableCommonMethodInterface,UIElement {
    setWaterFlowOptions_options?: WaterFlowOptions | undefined
    columnsTemplate_value?: string
    itemConstraintSize_value?: ConstraintSizeOptions
    rowsTemplate_value?: string
    columnsGap_value?: Length
    rowsGap_value?: Length
    layoutDirection_value?: FlexDirection
    nestedScroll_value?: NestedScrollOptions
    enableScrollInteraction_value?: boolean
    friction_value?: number | Resource
    cachedCount0_value?: number
    cachedCount1_count?: number
    cachedCount1_show?: boolean
    onReachStart_value?: (() => void)
    onReachEnd_value?: (() => void)
    onScrollFrameBegin_value?: ((offset: number, state: ScrollState) => { offsetRemain: number })
    onScrollIndex_value?: ((first: number, last: number) => void)
}
export interface UIExtensionComponentInterface extends CommonMethodInterface,UIElement {
    setUIExtensionComponentOptions_want?: Want
    setUIExtensionComponentOptions_options?: UIExtensionOptions | undefined
    onRemoteReady_value?: ((parameter: UIExtensionProxy) => void)
    onReceive_value?: ReceiveCallback
    onResult_value?: ((parameter: { code: number, want?: Want }) => void)
    onRelease_value?: ((index: number) => void)
    onError_value?: Object
    onTerminated_value?: ((parameter: TerminationInfo) => void)
}
export interface LinearIndicatorInterface extends CommonMethodInterface,UIElement {
    setLinearIndicatorOptions_count?: number | undefined
    setLinearIndicatorOptions_controller?: LinearIndicatorController | undefined
    indicatorStyle_value?: LinearIndicatorStyle | undefined
    indicatorLoop_value?: boolean | undefined
    onChange_value?: OnLinearIndicatorChangeCallback | undefined
}
export class NativeModuleRecorder extends NativeModuleEmpty {
    private pointers = new Array<Object|null>(2)
    private nameByNodeType: (type: int32) => string
    rootElement: UIElement | undefined = undefined
    private static readonly textEncoder = new CustomTextEncoder()
    private nodeById = new Map<string, UIElement>()
     constructor(nameByNodeType: ((type: int32) => string)) {
        super()
        this.nameByNodeType = nameByNodeType
        this.pointers[NULL_POINTER] = null
        this.pointers[FINALIZER_POINTER] = (ptr: pointer) => { this.pointers[ptr as number] = null }
    }
    _ManagedStringWrite(value: string, buffer: Uint8Array, offset: int32): int32 {
        if (typeof value === 'number' || value === null)
            throw "Not implemented"
        if (typeof buffer === 'number' || buffer === null)
            throw "Not implemented"
        const encoded = NativeModuleRecorder.textEncoder.encode(value, false)
        let length = encoded.length + 1 // zero-terminated
        buffer.set([...encoded, 0], offset)
        return length
    }
    _CaptureUIStructure(): KPointer {
        return this.object2ptr(JSON.stringify({
            rootElement: this.rootElement
        }))
    }
    private ptr2object<T>(ptr: KPointer): T {
        return this.pointers[ptr as number] as T
    }
    private object2ptr(object: Object | undefined): KPointer {
        if (object == null) return nullptr
        for (let i = 1; i < this.pointers.length; i++) {
            if (this.pointers[i] == null) {
                this.pointers[i] = object
                return i
            }
        }
        let ptr = this.pointers.length
        this.pointers.push(object)
        return ptr
    }
    _StringLength(ptr: KPointer): int32 {
        return this.ptr2object<string>(ptr).length
    }
    _StringData(ptr: KPointer, buffer: Uint8Array, length: number): void {
        let value = this.ptr2object<string>(ptr);
        (buffer as Uint8Array).set(encodeToData(value))
    }
    _GetStringFinalizer(): KPointer {
        return FINALIZER_POINTER as pointer
    }
    _InvokeFinalizer(ptr: KPointer, finalizer: KPointer): void {
        let finalizerFunc = this.ptr2object<(obj: pointer) => void>(finalizer)
        finalizerFunc(ptr)
    }
    _CreateNode(type: int32, id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: id,
            kind: this.nameByNodeType(type),
            children: [],
            elementId: undefined,
        }
        if (type == 0 /* ArkUINodeType.Root */) {
            this.rootElement = element
        }
        return this.object2ptr(element)
    }
    _DisposeNode(ptr: KPointer): void {
        let node = this.ptr2object<UIElement|null>(ptr)
        console.log("Dispose", node)
        if (node?.elementId) this.nodeById.delete(node.elementId)
    }
    _AddChild(ptr1: KPointer, ptr2: KPointer): number {
        let parent = this.ptr2object<UIElement|null>(ptr1)
        let child = this.ptr2object<UIElement|null>(ptr2)
        parent?.children?.push(child!)
        return 0
    }
    _RemoveChild(parentPtr: KPointer, childPtr: KPointer): void {
        let parent = this.ptr2object<UIElement|null>(parentPtr)
        let child = this.ptr2object<UIElement|null>(childPtr)
        parent?.children?.forEach((element, index) => {
            if (element == child) {
                parent?.children?.splice(index, 1)
            }
        })
    }
    _InsertChildAfter(ptr0: KPointer, ptr1: KPointer, ptr2: KPointer): number {
        let parent = this.ptr2object<UIElement|null>(ptr0)
        let child = this.ptr2object<UIElement|null>(ptr1)
        let sibling = this.ptr2object<UIElement|null>(ptr2)
        if (sibling) {
            let inserted = false
            parent?.children?.forEach((element, index) => {
                if (element == sibling) {
                    inserted = true
                    parent?.children?.splice(index + 1, 0, child!)
                }
            })
            if (!inserted) throw Error("Cannot find sibling to insert")
        } else {
            if (child) parent?.children?.push(child)
        }
        return 0
    }
    _InsertChildBefore(ptr0: KPointer, ptr1: KPointer, ptr2: KPointer): number {
        let parent = this.ptr2object<UIElement|null>(ptr0)
        let child = this.ptr2object<UIElement|null>(ptr1)
        let sibling = this.ptr2object<UIElement|null>(ptr2)
        if (sibling) {
            let inserted = false
            parent?.children?.forEach((element, index) => {
                if (element == sibling) {
                    inserted = true
                    parent?.children?.splice(index - 1, 0, child!)
                }
            })
            if (!inserted) throw Error("Cannot find sibling to insert")
        } else {
            if (child) parent?.children?.push(child)
        }
        return 0
    }
    _InsertChildAt(ptr0: KPointer, ptr1: KPointer, arg: number): number {
        let parent = this.ptr2object<UIElement|null>(ptr0)
        let child = this.ptr2object<UIElement|null>(ptr1)
        let inserted = false
        parent?.children?.forEach((element, index) => {
            if (index == arg) {
                inserted = true
                parent?.children?.splice(index, 0, child!)
            }
        })
        if (!inserted) throw Error("Cannot find sibling to insert")
        return 0
    }
    _Root_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _ComponentRoot_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _AbilityComponent_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _AlphabetIndexer_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Animator_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Badge_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Blank_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Button_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Calendar_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _CalendarPicker_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Canvas_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Checkbox_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _CheckboxGroup_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Circle_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Column_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _ColumnSplit_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _CommonMethod_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _CommonShapeMethod_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Common_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _ScrollableCommonMethod_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Component3D_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _ContainerSpan_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Counter_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _DataPanel_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _DatePicker_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Divider_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _EffectComponent_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Ellipse_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _EmbeddedComponent_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Flex_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _FlowItem_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _FolderStack_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _FormComponent_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _FormLink_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Gauge_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Grid_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _GridItem_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _GridCol_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _GridContainer_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _GridRow_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Hyperlink_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Image_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _ImageAnimator_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _ImageSpan_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Line_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _List_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _ListItem_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _ListItemGroup_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _LoadingProgress_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _LocationButton_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Marquee_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _MediaCachedImage_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Menu_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _MenuItem_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _MenuItemGroup_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _NavDestination_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _NavRouter_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Navigator_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _NodeContainer_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Panel_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _PasteButton_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Path_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _PatternLock_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _PluginComponent_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Polygon_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Polyline_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Progress_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _QRCode_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Radio_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Rating_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Rect_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Refresh_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _RelativeContainer_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _RichEditor_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _RichText_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _RootScene_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Row_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _RowSplit_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _SaveButton_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Screen_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Scroll_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _ScrollBar_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Search_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _SecurityComponentMethod_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Select_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Shape_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Slider_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _BaseSpan_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Span_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Stack_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Stepper_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _StepperItem_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Swiper_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _IndicatorComponent_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _SymbolGlyph_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _SymbolSpan_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Tabs_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _TabContent_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Text_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _TextArea_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _TextClock_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _TextInput_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _TextPicker_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _TextTimer_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _TimePicker_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Toggle_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Video_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _Web_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _WindowScene_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _XComponent_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _SideBarContainer_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _RemoteWindow_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _WaterFlow_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _UIExtensionComponent_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _LinearIndicator_construct(id: int32, flags: int32): KPointer {
        let element: UIElement = {
            nodeId: 0,
            kind: '',
            children: [],
            elementId: undefined,
        }
        return this.object2ptr(element)
    }
    _AbilityComponentInterface_setAbilityComponentOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AbilityComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setAbilityComponentOptions_value_buf_want: Want = thisDeserializer.readWant()
        node.setAbilityComponentOptions_value = ({want: setAbilityComponentOptions_value_buf_want} as { want: Want })
    }
    _AbilityComponentAttribute_onConnect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AbilityComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onConnect_value = thisDeserializer.readCallback_Void()
    }
    _AbilityComponentAttribute_onDisconnect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AbilityComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDisconnect_value = thisDeserializer.readCallback_Void()
    }
    _AlphabetIndexerInterface_setAlphabetIndexerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setAlphabetIndexerOptions_options = thisDeserializer.readAlphabetIndexerOptions()
    }
    _AlphabetIndexerAttribute_onSelected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSelected_value = thisDeserializer.readCallback_Number_Void()
    }
    _AlphabetIndexerAttribute_color(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const color_value_buf_selector: number = thisDeserializer.readInt8()
        let color_value_buf: Color | number | string | Resource | undefined|undefined 
        if (color_value_buf_selector == 0) {
            color_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (color_value_buf_selector == 1) {
            color_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (color_value_buf_selector == 2) {
            color_value_buf = (thisDeserializer.readString() as string)
        }
        else if (color_value_buf_selector == 3) {
            color_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for color_value_buf has to be chosen through deserialisation.")
        }
        node.color_value = (color_value_buf as Color | number | string | Resource)
    }
    _AlphabetIndexerAttribute_selectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const selectedColor_value_buf_selector: number = thisDeserializer.readInt8()
        let selectedColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (selectedColor_value_buf_selector == 0) {
            selectedColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (selectedColor_value_buf_selector == 1) {
            selectedColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (selectedColor_value_buf_selector == 2) {
            selectedColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (selectedColor_value_buf_selector == 3) {
            selectedColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for selectedColor_value_buf has to be chosen through deserialisation.")
        }
        node.selectedColor_value = (selectedColor_value_buf as Color | number | string | Resource)
    }
    _AlphabetIndexerAttribute_popupColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const popupColor_value_buf_selector: number = thisDeserializer.readInt8()
        let popupColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (popupColor_value_buf_selector == 0) {
            popupColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (popupColor_value_buf_selector == 1) {
            popupColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (popupColor_value_buf_selector == 2) {
            popupColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (popupColor_value_buf_selector == 3) {
            popupColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for popupColor_value_buf has to be chosen through deserialisation.")
        }
        node.popupColor_value = (popupColor_value_buf as Color | number | string | Resource)
    }
    _AlphabetIndexerAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const selectedBackgroundColor_value_buf_selector: number = thisDeserializer.readInt8()
        let selectedBackgroundColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (selectedBackgroundColor_value_buf_selector == 0) {
            selectedBackgroundColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (selectedBackgroundColor_value_buf_selector == 1) {
            selectedBackgroundColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (selectedBackgroundColor_value_buf_selector == 2) {
            selectedBackgroundColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (selectedBackgroundColor_value_buf_selector == 3) {
            selectedBackgroundColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for selectedBackgroundColor_value_buf has to be chosen through deserialisation.")
        }
        node.selectedBackgroundColor_value = (selectedBackgroundColor_value_buf as Color | number | string | Resource)
    }
    _AlphabetIndexerAttribute_popupBackground(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const popupBackground_value_buf_selector: number = thisDeserializer.readInt8()
        let popupBackground_value_buf: Color | number | string | Resource | undefined|undefined 
        if (popupBackground_value_buf_selector == 0) {
            popupBackground_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (popupBackground_value_buf_selector == 1) {
            popupBackground_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (popupBackground_value_buf_selector == 2) {
            popupBackground_value_buf = (thisDeserializer.readString() as string)
        }
        else if (popupBackground_value_buf_selector == 3) {
            popupBackground_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for popupBackground_value_buf has to be chosen through deserialisation.")
        }
        node.popupBackground_value = (popupBackground_value_buf as Color | number | string | Resource)
    }
    _AlphabetIndexerAttribute_popupSelectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const popupSelectedColor_value_buf_selector: number = thisDeserializer.readInt8()
        let popupSelectedColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (popupSelectedColor_value_buf_selector == 0) {
            popupSelectedColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (popupSelectedColor_value_buf_selector == 1) {
            popupSelectedColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (popupSelectedColor_value_buf_selector == 2) {
            popupSelectedColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (popupSelectedColor_value_buf_selector == 3) {
            popupSelectedColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for popupSelectedColor_value_buf has to be chosen through deserialisation.")
        }
        node.popupSelectedColor_value = (popupSelectedColor_value_buf as Color | number | string | Resource)
    }
    _AlphabetIndexerAttribute_popupUnselectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const popupUnselectedColor_value_buf_selector: number = thisDeserializer.readInt8()
        let popupUnselectedColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (popupUnselectedColor_value_buf_selector == 0) {
            popupUnselectedColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (popupUnselectedColor_value_buf_selector == 1) {
            popupUnselectedColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (popupUnselectedColor_value_buf_selector == 2) {
            popupUnselectedColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (popupUnselectedColor_value_buf_selector == 3) {
            popupUnselectedColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for popupUnselectedColor_value_buf has to be chosen through deserialisation.")
        }
        node.popupUnselectedColor_value = (popupUnselectedColor_value_buf as Color | number | string | Resource)
    }
    _AlphabetIndexerAttribute_popupItemBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const popupItemBackgroundColor_value_buf_selector: number = thisDeserializer.readInt8()
        let popupItemBackgroundColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (popupItemBackgroundColor_value_buf_selector == 0) {
            popupItemBackgroundColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (popupItemBackgroundColor_value_buf_selector == 1) {
            popupItemBackgroundColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (popupItemBackgroundColor_value_buf_selector == 2) {
            popupItemBackgroundColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (popupItemBackgroundColor_value_buf_selector == 3) {
            popupItemBackgroundColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for popupItemBackgroundColor_value_buf has to be chosen through deserialisation.")
        }
        node.popupItemBackgroundColor_value = (popupItemBackgroundColor_value_buf as Color | number | string | Resource)
    }
    _AlphabetIndexerAttribute_usingPopup(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        node.usingPopup_value = value
    }
    _AlphabetIndexerAttribute_selectedFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.selectedFont_value = thisDeserializer.readFont()
    }
    _AlphabetIndexerAttribute_popupFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.popupFont_value = thisDeserializer.readFont()
    }
    _AlphabetIndexerAttribute_popupItemFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.popupItemFont_value = thisDeserializer.readFont()
    }
    _AlphabetIndexerAttribute_itemSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const itemSize_value_buf_selector: number = thisDeserializer.readInt8()
        let itemSize_value_buf: string | number | undefined|undefined 
        if (itemSize_value_buf_selector == 0) {
            itemSize_value_buf = (thisDeserializer.readString() as string)
        }
        else if (itemSize_value_buf_selector == 1) {
            itemSize_value_buf = (thisDeserializer.readNumber() as number)
        }
        else {
            throw new Error("One of the branches for itemSize_value_buf has to be chosen through deserialisation.")
        }
        node.itemSize_value = (itemSize_value_buf as string | number)
    }
    _AlphabetIndexerAttribute_font(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.font_value = thisDeserializer.readFont()
    }
    _AlphabetIndexerAttribute_onSelect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSelect_value = thisDeserializer.readOnAlphabetIndexerSelectCallback()
    }
    _AlphabetIndexerAttribute_onRequestPopupData(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onRequestPopupData_value = thisDeserializer.readOnAlphabetIndexerRequestPopupDataCallback()
    }
    _AlphabetIndexerAttribute_onPopupSelect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onPopupSelect_value = thisDeserializer.readOnAlphabetIndexerPopupSelectCallback()
    }
    _AlphabetIndexerAttribute_selected(ptr: KPointer, value: number): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        node.selected_value = value
    }
    _AlphabetIndexerAttribute_popupPosition(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.popupPosition_value = thisDeserializer.readPosition()
    }
    _AlphabetIndexerAttribute_autoCollapse(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        node.autoCollapse_value = value
    }
    _AlphabetIndexerAttribute_popupItemBorderRadius(ptr: KPointer, value: number): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        node.popupItemBorderRadius_value = value
    }
    _AlphabetIndexerAttribute_itemBorderRadius(ptr: KPointer, value: number): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        node.itemBorderRadius_value = value
    }
    _AlphabetIndexerAttribute_popupBackgroundBlurStyle(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        node.popupBackgroundBlurStyle_value = value
    }
    _AlphabetIndexerAttribute_popupTitleBackground(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const popupTitleBackground_value_buf_selector: number = thisDeserializer.readInt8()
        let popupTitleBackground_value_buf: Color | number | string | Resource | undefined|undefined 
        if (popupTitleBackground_value_buf_selector == 0) {
            popupTitleBackground_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (popupTitleBackground_value_buf_selector == 1) {
            popupTitleBackground_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (popupTitleBackground_value_buf_selector == 2) {
            popupTitleBackground_value_buf = (thisDeserializer.readString() as string)
        }
        else if (popupTitleBackground_value_buf_selector == 3) {
            popupTitleBackground_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for popupTitleBackground_value_buf has to be chosen through deserialisation.")
        }
        node.popupTitleBackground_value = (popupTitleBackground_value_buf as Color | number | string | Resource)
    }
    _AlphabetIndexerAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        node.enableHapticFeedback_value = value
    }
    _AlphabetIndexerAttribute_alignStyle(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AlphabetIndexerInterface>(ptr)
        node.alignStyle_value = value
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const alignStyle_offset_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let alignStyle_offset_buf: Length | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (alignStyle_offset_buf_runtimeType))
        {
            alignStyle_offset_buf = (thisDeserializer.readLength() as Length)
        }
        node.alignStyle_offset = alignStyle_offset_buf
    }
    _AnimatorInterface_setAnimatorOptions(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<AnimatorInterface>(ptr)
        node.setAnimatorOptions_value = value
    }
    _AnimatorAttribute_state(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<AnimatorInterface>(ptr)
        node.state_value = value
    }
    _AnimatorAttribute_duration(ptr: KPointer, value: number): void {
        let node = this.ptr2object<AnimatorInterface>(ptr)
        node.duration_value = value
    }
    _AnimatorAttribute_curve(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<AnimatorInterface>(ptr)
        node.curve_value = value
    }
    _AnimatorAttribute_delay(ptr: KPointer, value: number): void {
        let node = this.ptr2object<AnimatorInterface>(ptr)
        node.delay_value = value
    }
    _AnimatorAttribute_fillMode(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<AnimatorInterface>(ptr)
        node.fillMode_value = value
    }
    _AnimatorAttribute_iterations(ptr: KPointer, value: number): void {
        let node = this.ptr2object<AnimatorInterface>(ptr)
        node.iterations_value = value
    }
    _AnimatorAttribute_playMode(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<AnimatorInterface>(ptr)
        node.playMode_value = value
    }
    _AnimatorAttribute_motion(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AnimatorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const motion_value_buf_selector: number = thisDeserializer.readInt8()
        let motion_value_buf: SpringMotion | FrictionMotion | ScrollMotion | undefined|undefined 
        if (motion_value_buf_selector == 0) {
            motion_value_buf = thisDeserializer.readSpringMotion()
        }
        else if (motion_value_buf_selector == 1) {
            motion_value_buf = thisDeserializer.readFrictionMotion()
        }
        else if (motion_value_buf_selector == 2) {
            motion_value_buf = thisDeserializer.readScrollMotion()
        }
        else {
            throw new Error("One of the branches for motion_value_buf has to be chosen through deserialisation.")
        }
        node.motion_value = (motion_value_buf as SpringMotion | FrictionMotion | ScrollMotion)
    }
    _AnimatorAttribute_onStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AnimatorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onStart_value = thisDeserializer.readCallback_Void()
    }
    _AnimatorAttribute_onPause(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AnimatorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onPause_value = thisDeserializer.readCallback_Void()
    }
    _AnimatorAttribute_onRepeat(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AnimatorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onRepeat_value = thisDeserializer.readCallback_Void()
    }
    _AnimatorAttribute_onCancel(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AnimatorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onCancel_value = thisDeserializer.readCallback_Void()
    }
    _AnimatorAttribute_onFinish(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AnimatorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onFinish_value = thisDeserializer.readCallback_Void()
    }
    _AnimatorAttribute_onFrame(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<AnimatorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onFrame_value = thisDeserializer.readCallback_Number_Void()
    }
    _BadgeInterface_setBadgeOptions0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<BadgeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setBadgeOptions0_value = thisDeserializer.readBadgeParamWithNumber()
    }
    _BadgeInterface_setBadgeOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<BadgeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setBadgeOptions1_value = thisDeserializer.readBadgeParamWithString()
    }
    _BlankInterface_setBlankOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<BlankInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setBlankOptions_min_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setBlankOptions_min_buf: number | string | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setBlankOptions_min_buf_runtimeType))
        {
            const setBlankOptions_min_buf__selector: number = thisDeserializer.readInt8()
            let setBlankOptions_min_buf_: number | string | undefined|undefined 
            if (setBlankOptions_min_buf__selector == 0) {
                setBlankOptions_min_buf_ = (thisDeserializer.readNumber() as number)
            }
            else if (setBlankOptions_min_buf__selector == 1) {
                setBlankOptions_min_buf_ = (thisDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for setBlankOptions_min_buf_ has to be chosen through deserialisation.")
            }
            setBlankOptions_min_buf = (setBlankOptions_min_buf_ as number | string)
        }
        node.setBlankOptions_min = setBlankOptions_min_buf
    }
    _BlankAttribute_color(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<BlankInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const color_value_buf_selector: number = thisDeserializer.readInt8()
        let color_value_buf: Color | number | string | Resource | undefined|undefined 
        if (color_value_buf_selector == 0) {
            color_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (color_value_buf_selector == 1) {
            color_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (color_value_buf_selector == 2) {
            color_value_buf = (thisDeserializer.readString() as string)
        }
        else if (color_value_buf_selector == 3) {
            color_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for color_value_buf has to be chosen through deserialisation.")
        }
        node.color_value = (color_value_buf as Color | number | string | Resource)
    }
    _ButtonInterface_setButtonOptions0(ptr: KPointer): void {
        let node = this.ptr2object<ButtonInterface>(ptr)
    }
    _ButtonInterface_setButtonOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ButtonInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setButtonOptions1_options = thisDeserializer.readButtonOptions()
    }
    _ButtonInterface_setButtonOptions2(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ButtonInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setButtonOptions2_label_buf_selector: number = thisDeserializer.readInt8()
        let setButtonOptions2_label_buf: string | Resource | undefined|undefined 
        if (setButtonOptions2_label_buf_selector == 0) {
            setButtonOptions2_label_buf = (thisDeserializer.readString() as string)
        }
        else if (setButtonOptions2_label_buf_selector == 1) {
            setButtonOptions2_label_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for setButtonOptions2_label_buf has to be chosen through deserialisation.")
        }
        node.setButtonOptions2_label = (setButtonOptions2_label_buf as string | Resource)
        const setButtonOptions2_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setButtonOptions2_options_buf: ButtonOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setButtonOptions2_options_buf_runtimeType))
        {
            setButtonOptions2_options_buf = thisDeserializer.readButtonOptions()
        }
        node.setButtonOptions2_options = setButtonOptions2_options_buf
    }
    _ButtonAttribute_type(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ButtonInterface>(ptr)
        node.type_value = value
    }
    _ButtonAttribute_stateEffect(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ButtonInterface>(ptr)
        node.stateEffect_value = value
    }
    _ButtonAttribute_buttonStyle(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ButtonInterface>(ptr)
        node.buttonStyle_value = value
    }
    _ButtonAttribute_controlSize(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ButtonInterface>(ptr)
        node.controlSize_value = value
    }
    _ButtonAttribute_role(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ButtonInterface>(ptr)
        node.role_value = value
    }
    _ButtonAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ButtonInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontColor_value_buf_selector: number = thisDeserializer.readInt8()
        let fontColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (fontColor_value_buf_selector == 0) {
            fontColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (fontColor_value_buf_selector == 1) {
            fontColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontColor_value_buf_selector == 2) {
            fontColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontColor_value_buf_selector == 3) {
            fontColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontColor_value_buf has to be chosen through deserialisation.")
        }
        node.fontColor_value = (fontColor_value_buf as Color | number | string | Resource)
    }
    _ButtonAttribute_fontSize(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<ButtonInterface>(ptr)
        node.fontSize_value = value
    }
    _ButtonAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ButtonInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontWeight_value_buf_selector: number = thisDeserializer.readInt8()
        let fontWeight_value_buf: number | FontWeight | string | undefined|undefined 
        if (fontWeight_value_buf_selector == 0) {
            fontWeight_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontWeight_value_buf_selector == 1) {
            fontWeight_value_buf = (thisDeserializer.readInt32() as FontWeight)
        }
        else if (fontWeight_value_buf_selector == 2) {
            fontWeight_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for fontWeight_value_buf has to be chosen through deserialisation.")
        }
        node.fontWeight_value = (fontWeight_value_buf as number | FontWeight | string)
    }
    _ButtonAttribute_fontStyle(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ButtonInterface>(ptr)
        node.fontStyle_value = value
    }
    _ButtonAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ButtonInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontFamily_value_buf_selector: number = thisDeserializer.readInt8()
        let fontFamily_value_buf: string | Resource | undefined|undefined 
        if (fontFamily_value_buf_selector == 0) {
            fontFamily_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontFamily_value_buf_selector == 1) {
            fontFamily_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontFamily_value_buf has to be chosen through deserialisation.")
        }
        node.fontFamily_value = (fontFamily_value_buf as string | Resource)
    }
    _ButtonAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ButtonInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.contentModifier_value = (thisDeserializer.readCustomObject("ContentModifier") as ContentModifier<any>)
    }
    _ButtonAttribute_labelStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ButtonInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.labelStyle_value = thisDeserializer.readLabelStyle()
    }
    _CalendarInterface_setCalendarOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CalendarInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setCalendarOptions_value_buf_date_buf_year: number = (thisDeserializer.readNumber() as number)
        const setCalendarOptions_value_buf_date_buf_month: number = (thisDeserializer.readNumber() as number)
        const setCalendarOptions_value_buf_date_buf_day: number = (thisDeserializer.readNumber() as number)
        const setCalendarOptions_value_buf_date: { year: number, month: number, day: number } = ({year: setCalendarOptions_value_buf_date_buf_year, month: setCalendarOptions_value_buf_date_buf_month, day: setCalendarOptions_value_buf_date_buf_day} as { year: number, month: number, day: number })
        const setCalendarOptions_value_buf_currentData: MonthData = thisDeserializer.readMonthData()
        const setCalendarOptions_value_buf_preData: MonthData = thisDeserializer.readMonthData()
        const setCalendarOptions_value_buf_nextData: MonthData = thisDeserializer.readMonthData()
        const setCalendarOptions_value_buf_controller_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setCalendarOptions_value_buf_controller_buf: CalendarController | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setCalendarOptions_value_buf_controller_buf_runtimeType))
        {
            setCalendarOptions_value_buf_controller_buf = (thisDeserializer.readCalendarController() as CalendarController)
        }
        const setCalendarOptions_value_buf_controller: undefined | CalendarController = setCalendarOptions_value_buf_controller_buf
        node.setCalendarOptions_value = ({date: setCalendarOptions_value_buf_date, currentData: setCalendarOptions_value_buf_currentData, preData: setCalendarOptions_value_buf_preData, nextData: setCalendarOptions_value_buf_nextData, controller: setCalendarOptions_value_buf_controller} as { date: { year: number, month: number, day: number }, currentData: MonthData, preData: MonthData, nextData: MonthData, controller?: CalendarController })
    }
    _CalendarAttribute_showLunar(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CalendarInterface>(ptr)
        node.showLunar_value = value
    }
    _CalendarAttribute_showHoliday(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CalendarInterface>(ptr)
        node.showHoliday_value = value
    }
    _CalendarAttribute_needSlide(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CalendarInterface>(ptr)
        node.needSlide_value = value
    }
    _CalendarAttribute_startOfWeek(ptr: KPointer, value: number): void {
        let node = this.ptr2object<CalendarInterface>(ptr)
        node.startOfWeek_value = value
    }
    _CalendarAttribute_offDays(ptr: KPointer, value: number): void {
        let node = this.ptr2object<CalendarInterface>(ptr)
        node.offDays_value = value
    }
    _CalendarAttribute_direction(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CalendarInterface>(ptr)
        node.direction_value = value
    }
    _CalendarAttribute_currentDayStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CalendarInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.currentDayStyle_value = thisDeserializer.readCurrentDayStyle()
    }
    _CalendarAttribute_nonCurrentDayStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CalendarInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.nonCurrentDayStyle_value = thisDeserializer.readNonCurrentDayStyle()
    }
    _CalendarAttribute_todayStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CalendarInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.todayStyle_value = thisDeserializer.readTodayStyle()
    }
    _CalendarAttribute_weekStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CalendarInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.weekStyle_value = thisDeserializer.readWeekStyle()
    }
    _CalendarAttribute_workStateStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CalendarInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.workStateStyle_value = thisDeserializer.readWorkStateStyle()
    }
    _CalendarAttribute_onSelectChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CalendarInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSelectChange_value = thisDeserializer.readCallback_CalendarSelectedDate_Void()
    }
    _CalendarAttribute_onRequestData(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CalendarInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onRequestData_value = thisDeserializer.readCallback_CalendarRequestedData_Void()
    }
    _CalendarPickerInterface_setCalendarPickerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CalendarPickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setCalendarPickerOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setCalendarPickerOptions_options_buf: CalendarOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setCalendarPickerOptions_options_buf_runtimeType))
        {
            setCalendarPickerOptions_options_buf = thisDeserializer.readCalendarOptions()
        }
        node.setCalendarPickerOptions_options = setCalendarPickerOptions_options_buf
    }
    _CalendarPickerAttribute_textStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CalendarPickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.textStyle_value = thisDeserializer.readPickerTextStyle()
    }
    _CalendarPickerAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CalendarPickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onChange_value = thisDeserializer.readCallback_Date_Void()
    }
    _CalendarPickerAttribute_edgeAlign(ptr: KPointer, alignType: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CalendarPickerInterface>(ptr)
        node.edgeAlign_alignType = alignType
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const edgeAlign_offset_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let edgeAlign_offset_buf: Offset | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (edgeAlign_offset_buf_runtimeType))
        {
            const edgeAlign_offset_buf__dx: Length = (thisDeserializer.readLength() as Length)
            const edgeAlign_offset_buf__dy: Length = (thisDeserializer.readLength() as Length)
            edgeAlign_offset_buf = ({dx: edgeAlign_offset_buf__dx, dy: edgeAlign_offset_buf__dy} as Offset)
        }
        node.edgeAlign_offset = edgeAlign_offset_buf
    }
    _CanvasInterface_setCanvasOptions0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CanvasInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setCanvasOptions0_context_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setCanvasOptions0_context_buf: CanvasRenderingContext2D | DrawingRenderingContext | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setCanvasOptions0_context_buf_runtimeType))
        {
            const setCanvasOptions0_context_buf__selector: number = thisDeserializer.readInt8()
            let setCanvasOptions0_context_buf_: CanvasRenderingContext2D | DrawingRenderingContext | undefined|undefined 
            if (setCanvasOptions0_context_buf__selector == 0) {
                setCanvasOptions0_context_buf_ = (thisDeserializer.readCanvasRenderingContext2D() as CanvasRenderingContext2D)
            }
            else if (setCanvasOptions0_context_buf__selector == 1) {
                setCanvasOptions0_context_buf_ = (thisDeserializer.readDrawingRenderingContext() as DrawingRenderingContext)
            }
            else {
                throw new Error("One of the branches for setCanvasOptions0_context_buf_ has to be chosen through deserialisation.")
            }
            setCanvasOptions0_context_buf = (setCanvasOptions0_context_buf_ as CanvasRenderingContext2D | DrawingRenderingContext)
        }
        node.setCanvasOptions0_context = setCanvasOptions0_context_buf
    }
    _CanvasInterface_setCanvasOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CanvasInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setCanvasOptions1_context_buf_selector: number = thisDeserializer.readInt8()
        let setCanvasOptions1_context_buf: CanvasRenderingContext2D | DrawingRenderingContext | undefined|undefined 
        if (setCanvasOptions1_context_buf_selector == 0) {
            setCanvasOptions1_context_buf = (thisDeserializer.readCanvasRenderingContext2D() as CanvasRenderingContext2D)
        }
        else if (setCanvasOptions1_context_buf_selector == 1) {
            setCanvasOptions1_context_buf = (thisDeserializer.readDrawingRenderingContext() as DrawingRenderingContext)
        }
        else {
            throw new Error("One of the branches for setCanvasOptions1_context_buf has to be chosen through deserialisation.")
        }
        node.setCanvasOptions1_context = (setCanvasOptions1_context_buf as CanvasRenderingContext2D | DrawingRenderingContext)
        node.setCanvasOptions1_imageAIOptions = thisDeserializer.readImageAIOptions()
    }
    _CanvasAttribute_onReady(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CanvasInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onReady_value = thisDeserializer.readVoidCallback()
    }
    _CanvasAttribute_enableAnalyzer(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CanvasInterface>(ptr)
        node.enableAnalyzer_value = value
    }
    _CheckboxInterface_setCheckboxOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CheckboxInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setCheckboxOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setCheckboxOptions_options_buf: CheckboxOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setCheckboxOptions_options_buf_runtimeType))
        {
            setCheckboxOptions_options_buf = thisDeserializer.readCheckboxOptions()
        }
        node.setCheckboxOptions_options = setCheckboxOptions_options_buf
    }
    _CheckboxAttribute_select(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CheckboxInterface>(ptr)
        node.select_value = value
    }
    _CheckboxAttribute_selectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CheckboxInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const selectedColor_value_buf_selector: number = thisDeserializer.readInt8()
        let selectedColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (selectedColor_value_buf_selector == 0) {
            selectedColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (selectedColor_value_buf_selector == 1) {
            selectedColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (selectedColor_value_buf_selector == 2) {
            selectedColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (selectedColor_value_buf_selector == 3) {
            selectedColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for selectedColor_value_buf has to be chosen through deserialisation.")
        }
        node.selectedColor_value = (selectedColor_value_buf as Color | number | string | Resource)
    }
    _CheckboxAttribute_shape(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CheckboxInterface>(ptr)
        node.shape_value = value
    }
    _CheckboxAttribute_unselectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CheckboxInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const unselectedColor_value_buf_selector: number = thisDeserializer.readInt8()
        let unselectedColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (unselectedColor_value_buf_selector == 0) {
            unselectedColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (unselectedColor_value_buf_selector == 1) {
            unselectedColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (unselectedColor_value_buf_selector == 2) {
            unselectedColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (unselectedColor_value_buf_selector == 3) {
            unselectedColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for unselectedColor_value_buf has to be chosen through deserialisation.")
        }
        node.unselectedColor_value = (unselectedColor_value_buf as Color | number | string | Resource)
    }
    _CheckboxAttribute_mark(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CheckboxInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.mark_value = thisDeserializer.readMarkStyle()
    }
    _CheckboxAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CheckboxInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onChange_value = thisDeserializer.readOnCheckboxChangeCallback()
    }
    _CheckboxAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CheckboxInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.contentModifier_value = (thisDeserializer.readCustomObject("ContentModifier") as ContentModifier<any>)
    }
    _CheckboxGroupInterface_setCheckboxGroupOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CheckboxGroupInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setCheckboxGroupOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setCheckboxGroupOptions_options_buf: CheckboxGroupOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setCheckboxGroupOptions_options_buf_runtimeType))
        {
            setCheckboxGroupOptions_options_buf = thisDeserializer.readCheckboxGroupOptions()
        }
        node.setCheckboxGroupOptions_options = setCheckboxGroupOptions_options_buf
    }
    _CheckboxGroupAttribute_selectAll(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CheckboxGroupInterface>(ptr)
        node.selectAll_value = value
    }
    _CheckboxGroupAttribute_selectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CheckboxGroupInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const selectedColor_value_buf_selector: number = thisDeserializer.readInt8()
        let selectedColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (selectedColor_value_buf_selector == 0) {
            selectedColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (selectedColor_value_buf_selector == 1) {
            selectedColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (selectedColor_value_buf_selector == 2) {
            selectedColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (selectedColor_value_buf_selector == 3) {
            selectedColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for selectedColor_value_buf has to be chosen through deserialisation.")
        }
        node.selectedColor_value = (selectedColor_value_buf as Color | number | string | Resource)
    }
    _CheckboxGroupAttribute_unselectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CheckboxGroupInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const unselectedColor_value_buf_selector: number = thisDeserializer.readInt8()
        let unselectedColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (unselectedColor_value_buf_selector == 0) {
            unselectedColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (unselectedColor_value_buf_selector == 1) {
            unselectedColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (unselectedColor_value_buf_selector == 2) {
            unselectedColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (unselectedColor_value_buf_selector == 3) {
            unselectedColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for unselectedColor_value_buf has to be chosen through deserialisation.")
        }
        node.unselectedColor_value = (unselectedColor_value_buf as Color | number | string | Resource)
    }
    _CheckboxGroupAttribute_mark(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CheckboxGroupInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.mark_value = thisDeserializer.readMarkStyle()
    }
    _CheckboxGroupAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CheckboxGroupInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onChange_value = thisDeserializer.readOnCheckboxGroupChangeCallback()
    }
    _CheckboxGroupAttribute_checkboxShape(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CheckboxGroupInterface>(ptr)
        node.checkboxShape_value = value
    }
    _CircleInterface_setCircleOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CircleInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setCircleOptions_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setCircleOptions_value_buf: CircleOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setCircleOptions_value_buf_runtimeType))
        {
            setCircleOptions_value_buf = thisDeserializer.readCircleOptions()
        }
        node.setCircleOptions_value = setCircleOptions_value_buf
    }
    _ColumnInterface_setColumnOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ColumnInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setColumnOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setColumnOptions_options_buf: ColumnOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setColumnOptions_options_buf_runtimeType))
        {
            setColumnOptions_options_buf = thisDeserializer.readColumnOptions()
        }
        node.setColumnOptions_options = setColumnOptions_options_buf
    }
    _ColumnAttribute_alignItems(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ColumnInterface>(ptr)
        node.alignItems_value = value
    }
    _ColumnAttribute_justifyContent(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ColumnInterface>(ptr)
        node.justifyContent_value = value
    }
    _ColumnAttribute_pointLight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ColumnInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.pointLight_value = thisDeserializer.readPointLightStyle()
    }
    _ColumnAttribute_reverse(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ColumnInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const reverse_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let reverse_value_buf: boolean | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (reverse_value_buf_runtimeType))
        {
            reverse_value_buf = thisDeserializer.readBoolean()
        }
        node.reverse_value = reverse_value_buf
    }
    _ColumnSplitInterface_setColumnSplitOptions(ptr: KPointer): void {
        let node = this.ptr2object<ColumnSplitInterface>(ptr)
    }
    _ColumnSplitAttribute_resizeable(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ColumnSplitInterface>(ptr)
        node.resizeable_value = value
    }
    _ColumnSplitAttribute_divider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ColumnSplitInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const divider_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let divider_value_buf: ColumnSplitDividerStyle | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (divider_value_buf_runtimeType))
        {
            divider_value_buf = thisDeserializer.readColumnSplitDividerStyle()
        }
        node.divider_value = divider_value_buf
    }
    _CommonMethod_width(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.width_value = value
    }
    _CommonMethod_height(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.height_value = value
    }
    _CommonMethod_drawModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const drawModifier_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let drawModifier_value_buf: DrawModifier | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (drawModifier_value_buf_runtimeType))
        {
            drawModifier_value_buf = (thisDeserializer.readDrawModifier() as DrawModifier)
        }
        node.drawModifier_value = drawModifier_value_buf
    }
    _CommonMethod_responseRegion(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const responseRegion_value_buf_selector: number = thisDeserializer.readInt8()
        let responseRegion_value_buf: Array<Rectangle> | Rectangle | undefined|undefined 
        if (responseRegion_value_buf_selector == 0) {
            const responseRegion_value_buf_u_length: int32 = thisDeserializer.readInt32()
            let responseRegion_value_buf_u: Array<Rectangle> = new Array<Rectangle>()
            for (let responseRegion_value_buf_u_i = 0; responseRegion_value_buf_u_i < responseRegion_value_buf_u_length; responseRegion_value_buf_u_i++) {
                responseRegion_value_buf_u[responseRegion_value_buf_u_i] = thisDeserializer.readRectangle()
            }
            responseRegion_value_buf = responseRegion_value_buf_u
        }
        else if (responseRegion_value_buf_selector == 1) {
            responseRegion_value_buf = thisDeserializer.readRectangle()
        }
        else {
            throw new Error("One of the branches for responseRegion_value_buf has to be chosen through deserialisation.")
        }
        node.responseRegion_value = (responseRegion_value_buf as Array<Rectangle> | Rectangle)
    }
    _CommonMethod_mouseResponseRegion(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const mouseResponseRegion_value_buf_selector: number = thisDeserializer.readInt8()
        let mouseResponseRegion_value_buf: Array<Rectangle> | Rectangle | undefined|undefined 
        if (mouseResponseRegion_value_buf_selector == 0) {
            const mouseResponseRegion_value_buf_u_length: int32 = thisDeserializer.readInt32()
            let mouseResponseRegion_value_buf_u: Array<Rectangle> = new Array<Rectangle>()
            for (let mouseResponseRegion_value_buf_u_i = 0; mouseResponseRegion_value_buf_u_i < mouseResponseRegion_value_buf_u_length; mouseResponseRegion_value_buf_u_i++) {
                mouseResponseRegion_value_buf_u[mouseResponseRegion_value_buf_u_i] = thisDeserializer.readRectangle()
            }
            mouseResponseRegion_value_buf = mouseResponseRegion_value_buf_u
        }
        else if (mouseResponseRegion_value_buf_selector == 1) {
            mouseResponseRegion_value_buf = thisDeserializer.readRectangle()
        }
        else {
            throw new Error("One of the branches for mouseResponseRegion_value_buf has to be chosen through deserialisation.")
        }
        node.mouseResponseRegion_value = (mouseResponseRegion_value_buf as Array<Rectangle> | Rectangle)
    }
    _CommonMethod_size(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.size_value = thisDeserializer.readSizeOptions()
    }
    _CommonMethod_constraintSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.constraintSize_value = thisDeserializer.readConstraintSizeOptions()
    }
    _CommonMethod_touchable(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.touchable_value = value
    }
    _CommonMethod_hitTestBehavior(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.hitTestBehavior_value = value
    }
    _CommonMethod_onChildTouchTest(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onChildTouchTest_value = thisDeserializer.readCallback_Array_TouchTestInfo_TouchResult()
    }
    _CommonMethod_layoutWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const layoutWeight_value_buf_selector: number = thisDeserializer.readInt8()
        let layoutWeight_value_buf: number | string | undefined|undefined 
        if (layoutWeight_value_buf_selector == 0) {
            layoutWeight_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (layoutWeight_value_buf_selector == 1) {
            layoutWeight_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for layoutWeight_value_buf has to be chosen through deserialisation.")
        }
        node.layoutWeight_value = (layoutWeight_value_buf as number | string)
    }
    _CommonMethod_chainWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.chainWeight_value = thisDeserializer.readChainWeightOptions()
    }
    _CommonMethod_padding(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const padding_value_buf_selector: number = thisDeserializer.readInt8()
        let padding_value_buf: Padding | Length | LocalizedPadding | undefined|undefined 
        if (padding_value_buf_selector == 0) {
            const padding_value_buf_u_top_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let padding_value_buf_u_top_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (padding_value_buf_u_top_buf_runtimeType))
            {
                padding_value_buf_u_top_buf = (thisDeserializer.readLength() as Length)
            }
            const padding_value_buf_u_top: undefined | Length = padding_value_buf_u_top_buf
            const padding_value_buf_u_right_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let padding_value_buf_u_right_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (padding_value_buf_u_right_buf_runtimeType))
            {
                padding_value_buf_u_right_buf = (thisDeserializer.readLength() as Length)
            }
            const padding_value_buf_u_right: undefined | Length = padding_value_buf_u_right_buf
            const padding_value_buf_u_bottom_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let padding_value_buf_u_bottom_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (padding_value_buf_u_bottom_buf_runtimeType))
            {
                padding_value_buf_u_bottom_buf = (thisDeserializer.readLength() as Length)
            }
            const padding_value_buf_u_bottom: undefined | Length = padding_value_buf_u_bottom_buf
            const padding_value_buf_u_left_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let padding_value_buf_u_left_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (padding_value_buf_u_left_buf_runtimeType))
            {
                padding_value_buf_u_left_buf = (thisDeserializer.readLength() as Length)
            }
            const padding_value_buf_u_left: undefined | Length = padding_value_buf_u_left_buf
            padding_value_buf = ({top: padding_value_buf_u_top, right: padding_value_buf_u_right, bottom: padding_value_buf_u_bottom, left: padding_value_buf_u_left} as Padding)
        }
        else if (padding_value_buf_selector == 1) {
            padding_value_buf = (thisDeserializer.readLength() as Length)
        }
        else if (padding_value_buf_selector == 2) {
            padding_value_buf = thisDeserializer.readLocalizedPadding()
        }
        else {
            throw new Error("One of the branches for padding_value_buf has to be chosen through deserialisation.")
        }
        node.padding_value = (padding_value_buf as Padding | Length | LocalizedPadding)
    }
    _CommonMethod_safeAreaPadding(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const safeAreaPadding_value_buf_selector: number = thisDeserializer.readInt8()
        let safeAreaPadding_value_buf: Padding | LengthMetrics | LocalizedPadding | undefined|undefined 
        if (safeAreaPadding_value_buf_selector == 0) {
            const safeAreaPadding_value_buf_u_top_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let safeAreaPadding_value_buf_u_top_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (safeAreaPadding_value_buf_u_top_buf_runtimeType))
            {
                safeAreaPadding_value_buf_u_top_buf = (thisDeserializer.readLength() as Length)
            }
            const safeAreaPadding_value_buf_u_top: undefined | Length = safeAreaPadding_value_buf_u_top_buf
            const safeAreaPadding_value_buf_u_right_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let safeAreaPadding_value_buf_u_right_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (safeAreaPadding_value_buf_u_right_buf_runtimeType))
            {
                safeAreaPadding_value_buf_u_right_buf = (thisDeserializer.readLength() as Length)
            }
            const safeAreaPadding_value_buf_u_right: undefined | Length = safeAreaPadding_value_buf_u_right_buf
            const safeAreaPadding_value_buf_u_bottom_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let safeAreaPadding_value_buf_u_bottom_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (safeAreaPadding_value_buf_u_bottom_buf_runtimeType))
            {
                safeAreaPadding_value_buf_u_bottom_buf = (thisDeserializer.readLength() as Length)
            }
            const safeAreaPadding_value_buf_u_bottom: undefined | Length = safeAreaPadding_value_buf_u_bottom_buf
            const safeAreaPadding_value_buf_u_left_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let safeAreaPadding_value_buf_u_left_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (safeAreaPadding_value_buf_u_left_buf_runtimeType))
            {
                safeAreaPadding_value_buf_u_left_buf = (thisDeserializer.readLength() as Length)
            }
            const safeAreaPadding_value_buf_u_left: undefined | Length = safeAreaPadding_value_buf_u_left_buf
            safeAreaPadding_value_buf = ({top: safeAreaPadding_value_buf_u_top, right: safeAreaPadding_value_buf_u_right, bottom: safeAreaPadding_value_buf_u_bottom, left: safeAreaPadding_value_buf_u_left} as Padding)
        }
        else if (safeAreaPadding_value_buf_selector == 1) {
            safeAreaPadding_value_buf = thisDeserializer.readLengthMetrics()
        }
        else if (safeAreaPadding_value_buf_selector == 2) {
            safeAreaPadding_value_buf = thisDeserializer.readLocalizedPadding()
        }
        else {
            throw new Error("One of the branches for safeAreaPadding_value_buf has to be chosen through deserialisation.")
        }
        node.safeAreaPadding_value = (safeAreaPadding_value_buf as Padding | LengthMetrics | LocalizedPadding)
    }
    _CommonMethod_margin(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const margin_value_buf_selector: number = thisDeserializer.readInt8()
        let margin_value_buf: Margin | Length | LocalizedMargin | undefined|undefined 
        if (margin_value_buf_selector == 0) {
            const margin_value_buf_u_top_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let margin_value_buf_u_top_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (margin_value_buf_u_top_buf_runtimeType))
            {
                margin_value_buf_u_top_buf = (thisDeserializer.readLength() as Length)
            }
            const margin_value_buf_u_top: undefined | Length = margin_value_buf_u_top_buf
            const margin_value_buf_u_right_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let margin_value_buf_u_right_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (margin_value_buf_u_right_buf_runtimeType))
            {
                margin_value_buf_u_right_buf = (thisDeserializer.readLength() as Length)
            }
            const margin_value_buf_u_right: undefined | Length = margin_value_buf_u_right_buf
            const margin_value_buf_u_bottom_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let margin_value_buf_u_bottom_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (margin_value_buf_u_bottom_buf_runtimeType))
            {
                margin_value_buf_u_bottom_buf = (thisDeserializer.readLength() as Length)
            }
            const margin_value_buf_u_bottom: undefined | Length = margin_value_buf_u_bottom_buf
            const margin_value_buf_u_left_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let margin_value_buf_u_left_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (margin_value_buf_u_left_buf_runtimeType))
            {
                margin_value_buf_u_left_buf = (thisDeserializer.readLength() as Length)
            }
            const margin_value_buf_u_left: undefined | Length = margin_value_buf_u_left_buf
            margin_value_buf = ({top: margin_value_buf_u_top, right: margin_value_buf_u_right, bottom: margin_value_buf_u_bottom, left: margin_value_buf_u_left} as Padding)
        }
        else if (margin_value_buf_selector == 1) {
            margin_value_buf = (thisDeserializer.readLength() as Length)
        }
        else if (margin_value_buf_selector == 2) {
            margin_value_buf = thisDeserializer.readLocalizedPadding()
        }
        else {
            throw new Error("One of the branches for margin_value_buf has to be chosen through deserialisation.")
        }
        node.margin_value = (margin_value_buf as Margin | Length | LocalizedMargin)
    }
    _CommonMethod_backgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const backgroundColor_value_buf_selector: number = thisDeserializer.readInt8()
        let backgroundColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (backgroundColor_value_buf_selector == 0) {
            backgroundColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (backgroundColor_value_buf_selector == 1) {
            backgroundColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (backgroundColor_value_buf_selector == 2) {
            backgroundColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (backgroundColor_value_buf_selector == 3) {
            backgroundColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for backgroundColor_value_buf has to be chosen through deserialisation.")
        }
        node.backgroundColor_value = (backgroundColor_value_buf as Color | number | string | Resource)
    }
    _CommonMethod_pixelRound(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.pixelRound_value = thisDeserializer.readPixelRoundPolicy()
    }
    _CommonMethod_backgroundImageSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const backgroundImageSize_value_buf_selector: number = thisDeserializer.readInt8()
        let backgroundImageSize_value_buf: SizeOptions | ImageSize | undefined|undefined 
        if (backgroundImageSize_value_buf_selector == 0) {
            backgroundImageSize_value_buf = thisDeserializer.readSizeOptions()
        }
        else if (backgroundImageSize_value_buf_selector == 1) {
            backgroundImageSize_value_buf = (thisDeserializer.readInt32() as ImageSize)
        }
        else {
            throw new Error("One of the branches for backgroundImageSize_value_buf has to be chosen through deserialisation.")
        }
        node.backgroundImageSize_value = (backgroundImageSize_value_buf as SizeOptions | ImageSize)
    }
    _CommonMethod_backgroundImagePosition(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const backgroundImagePosition_value_buf_selector: number = thisDeserializer.readInt8()
        let backgroundImagePosition_value_buf: Position | Alignment | undefined|undefined 
        if (backgroundImagePosition_value_buf_selector == 0) {
            backgroundImagePosition_value_buf = thisDeserializer.readPosition()
        }
        else if (backgroundImagePosition_value_buf_selector == 1) {
            backgroundImagePosition_value_buf = (thisDeserializer.readInt32() as Alignment)
        }
        else {
            throw new Error("One of the branches for backgroundImagePosition_value_buf has to be chosen through deserialisation.")
        }
        node.backgroundImagePosition_value = (backgroundImagePosition_value_buf as Position | Alignment)
    }
    _CommonMethod_backgroundEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.backgroundEffect_value = thisDeserializer.readBackgroundEffectOptions()
    }
    _CommonMethod_backgroundImageResizable(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.backgroundImageResizable_value = thisDeserializer.readResizableOptions()
    }
    _CommonMethod_foregroundEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.foregroundEffect_value = thisDeserializer.readForegroundEffectOptions()
    }
    _CommonMethod_visualEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.visualEffect_value = thisDeserializer.readVisualEffect()
    }
    _CommonMethod_backgroundFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.backgroundFilter_value = thisDeserializer.readFilter()
    }
    _CommonMethod_foregroundFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.foregroundFilter_value = thisDeserializer.readFilter()
    }
    _CommonMethod_compositingFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.compositingFilter_value = thisDeserializer.readFilter()
    }
    _CommonMethod_opacity(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const opacity_value_buf_selector: number = thisDeserializer.readInt8()
        let opacity_value_buf: number | Resource | undefined|undefined 
        if (opacity_value_buf_selector == 0) {
            opacity_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (opacity_value_buf_selector == 1) {
            opacity_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for opacity_value_buf has to be chosen through deserialisation.")
        }
        node.opacity_value = (opacity_value_buf as number | Resource)
    }
    _CommonMethod_border(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.border_value = thisDeserializer.readBorderOptions()
    }
    _CommonMethod_borderStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const borderStyle_value_buf_selector: number = thisDeserializer.readInt8()
        let borderStyle_value_buf: BorderStyle | EdgeStyles | undefined|undefined 
        if (borderStyle_value_buf_selector == 0) {
            borderStyle_value_buf = (thisDeserializer.readInt32() as BorderStyle)
        }
        else if (borderStyle_value_buf_selector == 1) {
            const borderStyle_value_buf_u_top_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let borderStyle_value_buf_u_top_buf: BorderStyle | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (borderStyle_value_buf_u_top_buf_runtimeType))
            {
                borderStyle_value_buf_u_top_buf = (thisDeserializer.readInt32() as BorderStyle)
            }
            const borderStyle_value_buf_u_top: undefined | BorderStyle = borderStyle_value_buf_u_top_buf
            const borderStyle_value_buf_u_right_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let borderStyle_value_buf_u_right_buf: BorderStyle | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (borderStyle_value_buf_u_right_buf_runtimeType))
            {
                borderStyle_value_buf_u_right_buf = (thisDeserializer.readInt32() as BorderStyle)
            }
            const borderStyle_value_buf_u_right: undefined | BorderStyle = borderStyle_value_buf_u_right_buf
            const borderStyle_value_buf_u_bottom_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let borderStyle_value_buf_u_bottom_buf: BorderStyle | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (borderStyle_value_buf_u_bottom_buf_runtimeType))
            {
                borderStyle_value_buf_u_bottom_buf = (thisDeserializer.readInt32() as BorderStyle)
            }
            const borderStyle_value_buf_u_bottom: undefined | BorderStyle = borderStyle_value_buf_u_bottom_buf
            const borderStyle_value_buf_u_left_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let borderStyle_value_buf_u_left_buf: BorderStyle | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (borderStyle_value_buf_u_left_buf_runtimeType))
            {
                borderStyle_value_buf_u_left_buf = (thisDeserializer.readInt32() as BorderStyle)
            }
            const borderStyle_value_buf_u_left: undefined | BorderStyle = borderStyle_value_buf_u_left_buf
            borderStyle_value_buf = ({top: borderStyle_value_buf_u_top, right: borderStyle_value_buf_u_right, bottom: borderStyle_value_buf_u_bottom, left: borderStyle_value_buf_u_left} as EdgeStyles)
        }
        else {
            throw new Error("One of the branches for borderStyle_value_buf has to be chosen through deserialisation.")
        }
        node.borderStyle_value = (borderStyle_value_buf as BorderStyle | EdgeStyles)
    }
    _CommonMethod_borderWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const borderWidth_value_buf_selector: number = thisDeserializer.readInt8()
        let borderWidth_value_buf: Length | EdgeWidths | LocalizedEdgeWidths | undefined|undefined 
        if (borderWidth_value_buf_selector == 0) {
            borderWidth_value_buf = (thisDeserializer.readLength() as Length)
        }
        else if (borderWidth_value_buf_selector == 1) {
            const borderWidth_value_buf_u_top_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let borderWidth_value_buf_u_top_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (borderWidth_value_buf_u_top_buf_runtimeType))
            {
                borderWidth_value_buf_u_top_buf = (thisDeserializer.readLength() as Length)
            }
            const borderWidth_value_buf_u_top: undefined | Length = borderWidth_value_buf_u_top_buf
            const borderWidth_value_buf_u_right_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let borderWidth_value_buf_u_right_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (borderWidth_value_buf_u_right_buf_runtimeType))
            {
                borderWidth_value_buf_u_right_buf = (thisDeserializer.readLength() as Length)
            }
            const borderWidth_value_buf_u_right: undefined | Length = borderWidth_value_buf_u_right_buf
            const borderWidth_value_buf_u_bottom_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let borderWidth_value_buf_u_bottom_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (borderWidth_value_buf_u_bottom_buf_runtimeType))
            {
                borderWidth_value_buf_u_bottom_buf = (thisDeserializer.readLength() as Length)
            }
            const borderWidth_value_buf_u_bottom: undefined | Length = borderWidth_value_buf_u_bottom_buf
            const borderWidth_value_buf_u_left_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let borderWidth_value_buf_u_left_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (borderWidth_value_buf_u_left_buf_runtimeType))
            {
                borderWidth_value_buf_u_left_buf = (thisDeserializer.readLength() as Length)
            }
            const borderWidth_value_buf_u_left: undefined | Length = borderWidth_value_buf_u_left_buf
            borderWidth_value_buf = ({top: borderWidth_value_buf_u_top, right: borderWidth_value_buf_u_right, bottom: borderWidth_value_buf_u_bottom, left: borderWidth_value_buf_u_left} as EdgeWidths)
        }
        else if (borderWidth_value_buf_selector == 2) {
            borderWidth_value_buf = thisDeserializer.readLocalizedEdgeWidths()
        }
        else {
            throw new Error("One of the branches for borderWidth_value_buf has to be chosen through deserialisation.")
        }
        node.borderWidth_value = (borderWidth_value_buf as Length | EdgeWidths | LocalizedEdgeWidths)
    }
    _CommonMethod_borderColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const borderColor_value_buf_selector: number = thisDeserializer.readInt8()
        let borderColor_value_buf: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined|undefined 
        if (borderColor_value_buf_selector == 0) {
            const borderColor_value_buf_u_selector: number = thisDeserializer.readInt8()
            let borderColor_value_buf_u: Color | number | string | Resource | undefined|undefined 
            if (borderColor_value_buf_u_selector == 0) {
                borderColor_value_buf_u = (thisDeserializer.readInt32() as Color)
            }
            else if (borderColor_value_buf_u_selector == 1) {
                borderColor_value_buf_u = (thisDeserializer.readNumber() as number)
            }
            else if (borderColor_value_buf_u_selector == 2) {
                borderColor_value_buf_u = (thisDeserializer.readString() as string)
            }
            else if (borderColor_value_buf_u_selector == 3) {
                borderColor_value_buf_u = thisDeserializer.readResource()
            }
            else {
                throw new Error("One of the branches for borderColor_value_buf_u has to be chosen through deserialisation.")
            }
            borderColor_value_buf = (borderColor_value_buf_u as Color | number | string | Resource)
        }
        else if (borderColor_value_buf_selector == 1) {
            const borderColor_value_buf_u_top_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let borderColor_value_buf_u_top_buf: ResourceColor | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (borderColor_value_buf_u_top_buf_runtimeType))
            {
                const borderColor_value_buf_u_top_buf__selector: number = thisDeserializer.readInt8()
                let borderColor_value_buf_u_top_buf_: Color | number | string | Resource | undefined|undefined 
                if (borderColor_value_buf_u_top_buf__selector == 0) {
                    borderColor_value_buf_u_top_buf_ = (thisDeserializer.readInt32() as Color)
                }
                else if (borderColor_value_buf_u_top_buf__selector == 1) {
                    borderColor_value_buf_u_top_buf_ = (thisDeserializer.readNumber() as number)
                }
                else if (borderColor_value_buf_u_top_buf__selector == 2) {
                    borderColor_value_buf_u_top_buf_ = (thisDeserializer.readString() as string)
                }
                else if (borderColor_value_buf_u_top_buf__selector == 3) {
                    borderColor_value_buf_u_top_buf_ = thisDeserializer.readResource()
                }
                else {
                    throw new Error("One of the branches for borderColor_value_buf_u_top_buf_ has to be chosen through deserialisation.")
                }
                borderColor_value_buf_u_top_buf = (borderColor_value_buf_u_top_buf_ as Color | number | string | Resource)
            }
            const borderColor_value_buf_u_top: undefined | ResourceColor = borderColor_value_buf_u_top_buf
            const borderColor_value_buf_u_right_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let borderColor_value_buf_u_right_buf: ResourceColor | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (borderColor_value_buf_u_right_buf_runtimeType))
            {
                const borderColor_value_buf_u_right_buf__selector: number = thisDeserializer.readInt8()
                let borderColor_value_buf_u_right_buf_: Color | number | string | Resource | undefined|undefined 
                if (borderColor_value_buf_u_right_buf__selector == 0) {
                    borderColor_value_buf_u_right_buf_ = (thisDeserializer.readInt32() as Color)
                }
                else if (borderColor_value_buf_u_right_buf__selector == 1) {
                    borderColor_value_buf_u_right_buf_ = (thisDeserializer.readNumber() as number)
                }
                else if (borderColor_value_buf_u_right_buf__selector == 2) {
                    borderColor_value_buf_u_right_buf_ = (thisDeserializer.readString() as string)
                }
                else if (borderColor_value_buf_u_right_buf__selector == 3) {
                    borderColor_value_buf_u_right_buf_ = thisDeserializer.readResource()
                }
                else {
                    throw new Error("One of the branches for borderColor_value_buf_u_right_buf_ has to be chosen through deserialisation.")
                }
                borderColor_value_buf_u_right_buf = (borderColor_value_buf_u_right_buf_ as Color | number | string | Resource)
            }
            const borderColor_value_buf_u_right: undefined | ResourceColor = borderColor_value_buf_u_right_buf
            const borderColor_value_buf_u_bottom_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let borderColor_value_buf_u_bottom_buf: ResourceColor | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (borderColor_value_buf_u_bottom_buf_runtimeType))
            {
                const borderColor_value_buf_u_bottom_buf__selector: number = thisDeserializer.readInt8()
                let borderColor_value_buf_u_bottom_buf_: Color | number | string | Resource | undefined|undefined 
                if (borderColor_value_buf_u_bottom_buf__selector == 0) {
                    borderColor_value_buf_u_bottom_buf_ = (thisDeserializer.readInt32() as Color)
                }
                else if (borderColor_value_buf_u_bottom_buf__selector == 1) {
                    borderColor_value_buf_u_bottom_buf_ = (thisDeserializer.readNumber() as number)
                }
                else if (borderColor_value_buf_u_bottom_buf__selector == 2) {
                    borderColor_value_buf_u_bottom_buf_ = (thisDeserializer.readString() as string)
                }
                else if (borderColor_value_buf_u_bottom_buf__selector == 3) {
                    borderColor_value_buf_u_bottom_buf_ = thisDeserializer.readResource()
                }
                else {
                    throw new Error("One of the branches for borderColor_value_buf_u_bottom_buf_ has to be chosen through deserialisation.")
                }
                borderColor_value_buf_u_bottom_buf = (borderColor_value_buf_u_bottom_buf_ as Color | number | string | Resource)
            }
            const borderColor_value_buf_u_bottom: undefined | ResourceColor = borderColor_value_buf_u_bottom_buf
            const borderColor_value_buf_u_left_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let borderColor_value_buf_u_left_buf: ResourceColor | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (borderColor_value_buf_u_left_buf_runtimeType))
            {
                const borderColor_value_buf_u_left_buf__selector: number = thisDeserializer.readInt8()
                let borderColor_value_buf_u_left_buf_: Color | number | string | Resource | undefined|undefined 
                if (borderColor_value_buf_u_left_buf__selector == 0) {
                    borderColor_value_buf_u_left_buf_ = (thisDeserializer.readInt32() as Color)
                }
                else if (borderColor_value_buf_u_left_buf__selector == 1) {
                    borderColor_value_buf_u_left_buf_ = (thisDeserializer.readNumber() as number)
                }
                else if (borderColor_value_buf_u_left_buf__selector == 2) {
                    borderColor_value_buf_u_left_buf_ = (thisDeserializer.readString() as string)
                }
                else if (borderColor_value_buf_u_left_buf__selector == 3) {
                    borderColor_value_buf_u_left_buf_ = thisDeserializer.readResource()
                }
                else {
                    throw new Error("One of the branches for borderColor_value_buf_u_left_buf_ has to be chosen through deserialisation.")
                }
                borderColor_value_buf_u_left_buf = (borderColor_value_buf_u_left_buf_ as Color | number | string | Resource)
            }
            const borderColor_value_buf_u_left: undefined | ResourceColor = borderColor_value_buf_u_left_buf
            borderColor_value_buf = ({top: borderColor_value_buf_u_top, right: borderColor_value_buf_u_right, bottom: borderColor_value_buf_u_bottom, left: borderColor_value_buf_u_left} as EdgeColors)
        }
        else if (borderColor_value_buf_selector == 2) {
            borderColor_value_buf = thisDeserializer.readLocalizedEdgeColors()
        }
        else {
            throw new Error("One of the branches for borderColor_value_buf has to be chosen through deserialisation.")
        }
        node.borderColor_value = (borderColor_value_buf as ResourceColor | EdgeColors | LocalizedEdgeColors)
    }
    _CommonMethod_borderRadius(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const borderRadius_value_buf_selector: number = thisDeserializer.readInt8()
        let borderRadius_value_buf: Length | BorderRadiuses | LocalizedBorderRadiuses | undefined|undefined 
        if (borderRadius_value_buf_selector == 0) {
            borderRadius_value_buf = (thisDeserializer.readLength() as Length)
        }
        else if (borderRadius_value_buf_selector == 1) {
            const borderRadius_value_buf_u_topLeft_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let borderRadius_value_buf_u_topLeft_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (borderRadius_value_buf_u_topLeft_buf_runtimeType))
            {
                borderRadius_value_buf_u_topLeft_buf = (thisDeserializer.readLength() as Length)
            }
            const borderRadius_value_buf_u_topLeft: undefined | Length = borderRadius_value_buf_u_topLeft_buf
            const borderRadius_value_buf_u_topRight_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let borderRadius_value_buf_u_topRight_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (borderRadius_value_buf_u_topRight_buf_runtimeType))
            {
                borderRadius_value_buf_u_topRight_buf = (thisDeserializer.readLength() as Length)
            }
            const borderRadius_value_buf_u_topRight: undefined | Length = borderRadius_value_buf_u_topRight_buf
            const borderRadius_value_buf_u_bottomLeft_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let borderRadius_value_buf_u_bottomLeft_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (borderRadius_value_buf_u_bottomLeft_buf_runtimeType))
            {
                borderRadius_value_buf_u_bottomLeft_buf = (thisDeserializer.readLength() as Length)
            }
            const borderRadius_value_buf_u_bottomLeft: undefined | Length = borderRadius_value_buf_u_bottomLeft_buf
            const borderRadius_value_buf_u_bottomRight_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let borderRadius_value_buf_u_bottomRight_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (borderRadius_value_buf_u_bottomRight_buf_runtimeType))
            {
                borderRadius_value_buf_u_bottomRight_buf = (thisDeserializer.readLength() as Length)
            }
            const borderRadius_value_buf_u_bottomRight: undefined | Length = borderRadius_value_buf_u_bottomRight_buf
            borderRadius_value_buf = ({topLeft: borderRadius_value_buf_u_topLeft, topRight: borderRadius_value_buf_u_topRight, bottomLeft: borderRadius_value_buf_u_bottomLeft, bottomRight: borderRadius_value_buf_u_bottomRight} as BorderRadiuses)
        }
        else if (borderRadius_value_buf_selector == 2) {
            borderRadius_value_buf = thisDeserializer.readLocalizedBorderRadiuses()
        }
        else {
            throw new Error("One of the branches for borderRadius_value_buf has to be chosen through deserialisation.")
        }
        node.borderRadius_value = (borderRadius_value_buf as Length | BorderRadiuses | LocalizedBorderRadiuses)
    }
    _CommonMethod_borderImage(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.borderImage_value = thisDeserializer.readBorderImageOption()
    }
    _CommonMethod_outline(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.outline_value = thisDeserializer.readOutlineOptions()
    }
    _CommonMethod_outlineStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const outlineStyle_value_buf_selector: number = thisDeserializer.readInt8()
        let outlineStyle_value_buf: OutlineStyle | EdgeOutlineStyles | undefined|undefined 
        if (outlineStyle_value_buf_selector == 0) {
            outlineStyle_value_buf = (thisDeserializer.readInt32() as OutlineStyle)
        }
        else if (outlineStyle_value_buf_selector == 1) {
            const outlineStyle_value_buf_u_top_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let outlineStyle_value_buf_u_top_buf: OutlineStyle | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (outlineStyle_value_buf_u_top_buf_runtimeType))
            {
                outlineStyle_value_buf_u_top_buf = (thisDeserializer.readInt32() as OutlineStyle)
            }
            const outlineStyle_value_buf_u_top: undefined | OutlineStyle = outlineStyle_value_buf_u_top_buf
            const outlineStyle_value_buf_u_right_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let outlineStyle_value_buf_u_right_buf: OutlineStyle | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (outlineStyle_value_buf_u_right_buf_runtimeType))
            {
                outlineStyle_value_buf_u_right_buf = (thisDeserializer.readInt32() as OutlineStyle)
            }
            const outlineStyle_value_buf_u_right: undefined | OutlineStyle = outlineStyle_value_buf_u_right_buf
            const outlineStyle_value_buf_u_bottom_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let outlineStyle_value_buf_u_bottom_buf: OutlineStyle | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (outlineStyle_value_buf_u_bottom_buf_runtimeType))
            {
                outlineStyle_value_buf_u_bottom_buf = (thisDeserializer.readInt32() as OutlineStyle)
            }
            const outlineStyle_value_buf_u_bottom: undefined | OutlineStyle = outlineStyle_value_buf_u_bottom_buf
            const outlineStyle_value_buf_u_left_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let outlineStyle_value_buf_u_left_buf: OutlineStyle | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (outlineStyle_value_buf_u_left_buf_runtimeType))
            {
                outlineStyle_value_buf_u_left_buf = (thisDeserializer.readInt32() as OutlineStyle)
            }
            const outlineStyle_value_buf_u_left: undefined | OutlineStyle = outlineStyle_value_buf_u_left_buf
            outlineStyle_value_buf = ({top: outlineStyle_value_buf_u_top, right: outlineStyle_value_buf_u_right, bottom: outlineStyle_value_buf_u_bottom, left: outlineStyle_value_buf_u_left} as EdgeOutlineStyles)
        }
        else {
            throw new Error("One of the branches for outlineStyle_value_buf has to be chosen through deserialisation.")
        }
        node.outlineStyle_value = (outlineStyle_value_buf as OutlineStyle | EdgeOutlineStyles)
    }
    _CommonMethod_outlineWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const outlineWidth_value_buf_selector: number = thisDeserializer.readInt8()
        let outlineWidth_value_buf: Dimension | EdgeOutlineWidths | undefined|undefined 
        if (outlineWidth_value_buf_selector == 0) {
            outlineWidth_value_buf = (thisDeserializer.readLength() as Dimension)
        }
        else if (outlineWidth_value_buf_selector == 1) {
            const outlineWidth_value_buf_u_top_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let outlineWidth_value_buf_u_top_buf: Dimension | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (outlineWidth_value_buf_u_top_buf_runtimeType))
            {
                outlineWidth_value_buf_u_top_buf = (thisDeserializer.readLength() as Dimension)
            }
            const outlineWidth_value_buf_u_top: undefined | Dimension = outlineWidth_value_buf_u_top_buf
            const outlineWidth_value_buf_u_right_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let outlineWidth_value_buf_u_right_buf: Dimension | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (outlineWidth_value_buf_u_right_buf_runtimeType))
            {
                outlineWidth_value_buf_u_right_buf = (thisDeserializer.readLength() as Dimension)
            }
            const outlineWidth_value_buf_u_right: undefined | Dimension = outlineWidth_value_buf_u_right_buf
            const outlineWidth_value_buf_u_bottom_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let outlineWidth_value_buf_u_bottom_buf: Dimension | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (outlineWidth_value_buf_u_bottom_buf_runtimeType))
            {
                outlineWidth_value_buf_u_bottom_buf = (thisDeserializer.readLength() as Dimension)
            }
            const outlineWidth_value_buf_u_bottom: undefined | Dimension = outlineWidth_value_buf_u_bottom_buf
            const outlineWidth_value_buf_u_left_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let outlineWidth_value_buf_u_left_buf: Dimension | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (outlineWidth_value_buf_u_left_buf_runtimeType))
            {
                outlineWidth_value_buf_u_left_buf = (thisDeserializer.readLength() as Dimension)
            }
            const outlineWidth_value_buf_u_left: undefined | Dimension = outlineWidth_value_buf_u_left_buf
            outlineWidth_value_buf = ({top: outlineWidth_value_buf_u_top, right: outlineWidth_value_buf_u_right, bottom: outlineWidth_value_buf_u_bottom, left: outlineWidth_value_buf_u_left} as EdgeOutlineWidths)
        }
        else {
            throw new Error("One of the branches for outlineWidth_value_buf has to be chosen through deserialisation.")
        }
        node.outlineWidth_value = (outlineWidth_value_buf as Dimension | EdgeOutlineWidths)
    }
    _CommonMethod_outlineColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const outlineColor_value_buf_selector: number = thisDeserializer.readInt8()
        let outlineColor_value_buf: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined|undefined 
        if (outlineColor_value_buf_selector == 0) {
            const outlineColor_value_buf_u_selector: number = thisDeserializer.readInt8()
            let outlineColor_value_buf_u: Color | number | string | Resource | undefined|undefined 
            if (outlineColor_value_buf_u_selector == 0) {
                outlineColor_value_buf_u = (thisDeserializer.readInt32() as Color)
            }
            else if (outlineColor_value_buf_u_selector == 1) {
                outlineColor_value_buf_u = (thisDeserializer.readNumber() as number)
            }
            else if (outlineColor_value_buf_u_selector == 2) {
                outlineColor_value_buf_u = (thisDeserializer.readString() as string)
            }
            else if (outlineColor_value_buf_u_selector == 3) {
                outlineColor_value_buf_u = thisDeserializer.readResource()
            }
            else {
                throw new Error("One of the branches for outlineColor_value_buf_u has to be chosen through deserialisation.")
            }
            outlineColor_value_buf = (outlineColor_value_buf_u as Color | number | string | Resource)
        }
        else if (outlineColor_value_buf_selector == 1) {
            const outlineColor_value_buf_u_top_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let outlineColor_value_buf_u_top_buf: ResourceColor | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (outlineColor_value_buf_u_top_buf_runtimeType))
            {
                const outlineColor_value_buf_u_top_buf__selector: number = thisDeserializer.readInt8()
                let outlineColor_value_buf_u_top_buf_: Color | number | string | Resource | undefined|undefined 
                if (outlineColor_value_buf_u_top_buf__selector == 0) {
                    outlineColor_value_buf_u_top_buf_ = (thisDeserializer.readInt32() as Color)
                }
                else if (outlineColor_value_buf_u_top_buf__selector == 1) {
                    outlineColor_value_buf_u_top_buf_ = (thisDeserializer.readNumber() as number)
                }
                else if (outlineColor_value_buf_u_top_buf__selector == 2) {
                    outlineColor_value_buf_u_top_buf_ = (thisDeserializer.readString() as string)
                }
                else if (outlineColor_value_buf_u_top_buf__selector == 3) {
                    outlineColor_value_buf_u_top_buf_ = thisDeserializer.readResource()
                }
                else {
                    throw new Error("One of the branches for outlineColor_value_buf_u_top_buf_ has to be chosen through deserialisation.")
                }
                outlineColor_value_buf_u_top_buf = (outlineColor_value_buf_u_top_buf_ as Color | number | string | Resource)
            }
            const outlineColor_value_buf_u_top: undefined | ResourceColor = outlineColor_value_buf_u_top_buf
            const outlineColor_value_buf_u_right_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let outlineColor_value_buf_u_right_buf: ResourceColor | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (outlineColor_value_buf_u_right_buf_runtimeType))
            {
                const outlineColor_value_buf_u_right_buf__selector: number = thisDeserializer.readInt8()
                let outlineColor_value_buf_u_right_buf_: Color | number | string | Resource | undefined|undefined 
                if (outlineColor_value_buf_u_right_buf__selector == 0) {
                    outlineColor_value_buf_u_right_buf_ = (thisDeserializer.readInt32() as Color)
                }
                else if (outlineColor_value_buf_u_right_buf__selector == 1) {
                    outlineColor_value_buf_u_right_buf_ = (thisDeserializer.readNumber() as number)
                }
                else if (outlineColor_value_buf_u_right_buf__selector == 2) {
                    outlineColor_value_buf_u_right_buf_ = (thisDeserializer.readString() as string)
                }
                else if (outlineColor_value_buf_u_right_buf__selector == 3) {
                    outlineColor_value_buf_u_right_buf_ = thisDeserializer.readResource()
                }
                else {
                    throw new Error("One of the branches for outlineColor_value_buf_u_right_buf_ has to be chosen through deserialisation.")
                }
                outlineColor_value_buf_u_right_buf = (outlineColor_value_buf_u_right_buf_ as Color | number | string | Resource)
            }
            const outlineColor_value_buf_u_right: undefined | ResourceColor = outlineColor_value_buf_u_right_buf
            const outlineColor_value_buf_u_bottom_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let outlineColor_value_buf_u_bottom_buf: ResourceColor | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (outlineColor_value_buf_u_bottom_buf_runtimeType))
            {
                const outlineColor_value_buf_u_bottom_buf__selector: number = thisDeserializer.readInt8()
                let outlineColor_value_buf_u_bottom_buf_: Color | number | string | Resource | undefined|undefined 
                if (outlineColor_value_buf_u_bottom_buf__selector == 0) {
                    outlineColor_value_buf_u_bottom_buf_ = (thisDeserializer.readInt32() as Color)
                }
                else if (outlineColor_value_buf_u_bottom_buf__selector == 1) {
                    outlineColor_value_buf_u_bottom_buf_ = (thisDeserializer.readNumber() as number)
                }
                else if (outlineColor_value_buf_u_bottom_buf__selector == 2) {
                    outlineColor_value_buf_u_bottom_buf_ = (thisDeserializer.readString() as string)
                }
                else if (outlineColor_value_buf_u_bottom_buf__selector == 3) {
                    outlineColor_value_buf_u_bottom_buf_ = thisDeserializer.readResource()
                }
                else {
                    throw new Error("One of the branches for outlineColor_value_buf_u_bottom_buf_ has to be chosen through deserialisation.")
                }
                outlineColor_value_buf_u_bottom_buf = (outlineColor_value_buf_u_bottom_buf_ as Color | number | string | Resource)
            }
            const outlineColor_value_buf_u_bottom: undefined | ResourceColor = outlineColor_value_buf_u_bottom_buf
            const outlineColor_value_buf_u_left_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let outlineColor_value_buf_u_left_buf: ResourceColor | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (outlineColor_value_buf_u_left_buf_runtimeType))
            {
                const outlineColor_value_buf_u_left_buf__selector: number = thisDeserializer.readInt8()
                let outlineColor_value_buf_u_left_buf_: Color | number | string | Resource | undefined|undefined 
                if (outlineColor_value_buf_u_left_buf__selector == 0) {
                    outlineColor_value_buf_u_left_buf_ = (thisDeserializer.readInt32() as Color)
                }
                else if (outlineColor_value_buf_u_left_buf__selector == 1) {
                    outlineColor_value_buf_u_left_buf_ = (thisDeserializer.readNumber() as number)
                }
                else if (outlineColor_value_buf_u_left_buf__selector == 2) {
                    outlineColor_value_buf_u_left_buf_ = (thisDeserializer.readString() as string)
                }
                else if (outlineColor_value_buf_u_left_buf__selector == 3) {
                    outlineColor_value_buf_u_left_buf_ = thisDeserializer.readResource()
                }
                else {
                    throw new Error("One of the branches for outlineColor_value_buf_u_left_buf_ has to be chosen through deserialisation.")
                }
                outlineColor_value_buf_u_left_buf = (outlineColor_value_buf_u_left_buf_ as Color | number | string | Resource)
            }
            const outlineColor_value_buf_u_left: undefined | ResourceColor = outlineColor_value_buf_u_left_buf
            outlineColor_value_buf = ({top: outlineColor_value_buf_u_top, right: outlineColor_value_buf_u_right, bottom: outlineColor_value_buf_u_bottom, left: outlineColor_value_buf_u_left} as EdgeColors)
        }
        else if (outlineColor_value_buf_selector == 2) {
            outlineColor_value_buf = thisDeserializer.readLocalizedEdgeColors()
        }
        else {
            throw new Error("One of the branches for outlineColor_value_buf has to be chosen through deserialisation.")
        }
        node.outlineColor_value = (outlineColor_value_buf as ResourceColor | EdgeColors | LocalizedEdgeColors)
    }
    _CommonMethod_outlineRadius(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const outlineRadius_value_buf_selector: number = thisDeserializer.readInt8()
        let outlineRadius_value_buf: Dimension | OutlineRadiuses | undefined|undefined 
        if (outlineRadius_value_buf_selector == 0) {
            outlineRadius_value_buf = (thisDeserializer.readLength() as Dimension)
        }
        else if (outlineRadius_value_buf_selector == 1) {
            const outlineRadius_value_buf_u_topLeft_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let outlineRadius_value_buf_u_topLeft_buf: Dimension | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (outlineRadius_value_buf_u_topLeft_buf_runtimeType))
            {
                outlineRadius_value_buf_u_topLeft_buf = (thisDeserializer.readLength() as Dimension)
            }
            const outlineRadius_value_buf_u_topLeft: undefined | Dimension = outlineRadius_value_buf_u_topLeft_buf
            const outlineRadius_value_buf_u_topRight_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let outlineRadius_value_buf_u_topRight_buf: Dimension | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (outlineRadius_value_buf_u_topRight_buf_runtimeType))
            {
                outlineRadius_value_buf_u_topRight_buf = (thisDeserializer.readLength() as Dimension)
            }
            const outlineRadius_value_buf_u_topRight: undefined | Dimension = outlineRadius_value_buf_u_topRight_buf
            const outlineRadius_value_buf_u_bottomLeft_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let outlineRadius_value_buf_u_bottomLeft_buf: Dimension | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (outlineRadius_value_buf_u_bottomLeft_buf_runtimeType))
            {
                outlineRadius_value_buf_u_bottomLeft_buf = (thisDeserializer.readLength() as Dimension)
            }
            const outlineRadius_value_buf_u_bottomLeft: undefined | Dimension = outlineRadius_value_buf_u_bottomLeft_buf
            const outlineRadius_value_buf_u_bottomRight_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let outlineRadius_value_buf_u_bottomRight_buf: Dimension | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (outlineRadius_value_buf_u_bottomRight_buf_runtimeType))
            {
                outlineRadius_value_buf_u_bottomRight_buf = (thisDeserializer.readLength() as Dimension)
            }
            const outlineRadius_value_buf_u_bottomRight: undefined | Dimension = outlineRadius_value_buf_u_bottomRight_buf
            outlineRadius_value_buf = ({topLeft: outlineRadius_value_buf_u_topLeft, topRight: outlineRadius_value_buf_u_topRight, bottomLeft: outlineRadius_value_buf_u_bottomLeft, bottomRight: outlineRadius_value_buf_u_bottomRight} as OutlineRadiuses)
        }
        else {
            throw new Error("One of the branches for outlineRadius_value_buf has to be chosen through deserialisation.")
        }
        node.outlineRadius_value = (outlineRadius_value_buf as Dimension | OutlineRadiuses)
    }
    _CommonMethod_foregroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const foregroundColor_value_buf_selector: number = thisDeserializer.readInt8()
        let foregroundColor_value_buf: ResourceColor | ColoringStrategy | undefined|undefined 
        if (foregroundColor_value_buf_selector == 0) {
            const foregroundColor_value_buf_u_selector: number = thisDeserializer.readInt8()
            let foregroundColor_value_buf_u: Color | number | string | Resource | undefined|undefined 
            if (foregroundColor_value_buf_u_selector == 0) {
                foregroundColor_value_buf_u = (thisDeserializer.readInt32() as Color)
            }
            else if (foregroundColor_value_buf_u_selector == 1) {
                foregroundColor_value_buf_u = (thisDeserializer.readNumber() as number)
            }
            else if (foregroundColor_value_buf_u_selector == 2) {
                foregroundColor_value_buf_u = (thisDeserializer.readString() as string)
            }
            else if (foregroundColor_value_buf_u_selector == 3) {
                foregroundColor_value_buf_u = thisDeserializer.readResource()
            }
            else {
                throw new Error("One of the branches for foregroundColor_value_buf_u has to be chosen through deserialisation.")
            }
            foregroundColor_value_buf = (foregroundColor_value_buf_u as Color | number | string | Resource)
        }
        else if (foregroundColor_value_buf_selector == 1) {
            foregroundColor_value_buf = Object.values(ColoringStrategy)[thisDeserializer.readInt32()]
        }
        else {
            throw new Error("One of the branches for foregroundColor_value_buf has to be chosen through deserialisation.")
        }
        node.foregroundColor_value = (foregroundColor_value_buf as ResourceColor | ColoringStrategy)
    }
    _CommonMethod_onClick0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onClick0_value = thisDeserializer.readCallback_ClickEvent_Void()
    }
    _CommonMethod_onClick1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, distanceThreshold: number): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onClick1_event = thisDeserializer.readCallback_ClickEvent_Void()
        node.onClick1_distanceThreshold = thisLength
    }
    _CommonMethod_onHover(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onHover_value = thisDeserializer.readCallback_Boolean_HoverEvent_Void()
    }
    _CommonMethod_onAccessibilityHover(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onAccessibilityHover_value = thisDeserializer.readAccessibilityCallback()
    }
    _CommonMethod_hoverEffect(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.hoverEffect_value = value
    }
    _CommonMethod_onMouse(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onMouse_value = thisDeserializer.readCallback_MouseEvent_Void()
    }
    _CommonMethod_onTouch(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onTouch_value = thisDeserializer.readCallback_TouchEvent_Void()
    }
    _CommonMethod_onKeyEvent(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onKeyEvent_value = thisDeserializer.readCallback_KeyEvent_Void()
    }
    _CommonMethod_onKeyPreIme(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onKeyPreIme_value = thisDeserializer.readCallback_KeyEvent_Boolean()
    }
    _CommonMethod_focusable(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.focusable_value = value
    }
    _CommonMethod_onFocus(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onFocus_value = thisDeserializer.readCallback_Void()
    }
    _CommonMethod_onBlur(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onBlur_value = thisDeserializer.readCallback_Void()
    }
    _CommonMethod_tabIndex(ptr: KPointer, value: number): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.tabIndex_value = value
    }
    _CommonMethod_defaultFocus(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.defaultFocus_value = value
    }
    _CommonMethod_groupDefaultFocus(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.groupDefaultFocus_value = value
    }
    _CommonMethod_focusOnTouch(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.focusOnTouch_value = value
    }
    _CommonMethod_focusBox(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.focusBox_value = thisDeserializer.readFocusBoxStyle()
    }
    _CommonMethod_animation(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.animation_value = thisDeserializer.readAnimateParam()
    }
    _CommonMethod_transition0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const transition0_value_buf_selector: number = thisDeserializer.readInt8()
        let transition0_value_buf: TransitionOptions | TransitionEffect | undefined|undefined 
        if (transition0_value_buf_selector == 0) {
            transition0_value_buf = thisDeserializer.readTransitionOptions()
        }
        else if (transition0_value_buf_selector == 1) {
            transition0_value_buf = (thisDeserializer.readTransitionEffect() as TransitionEffect)
        }
        else {
            throw new Error("One of the branches for transition0_value_buf has to be chosen through deserialisation.")
        }
        node.transition0_value = (transition0_value_buf as TransitionOptions | TransitionEffect)
    }
    _CommonMethod_transition1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.transition1_effect = (thisDeserializer.readTransitionEffect() as TransitionEffect)
        const transition1_onFinish_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let transition1_onFinish_buf: TransitionFinishCallback | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (transition1_onFinish_buf_runtimeType))
        {
            transition1_onFinish_buf = thisDeserializer.readTransitionFinishCallback()
        }
        node.transition1_onFinish = transition1_onFinish_buf
    }
    _CommonMethod_motionBlur(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.motionBlur_value = thisDeserializer.readMotionBlurOptions()
    }
    _CommonMethod_brightness(ptr: KPointer, value: number): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.brightness_value = value
    }
    _CommonMethod_contrast(ptr: KPointer, value: number): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.contrast_value = value
    }
    _CommonMethod_grayscale(ptr: KPointer, value: number): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.grayscale_value = value
    }
    _CommonMethod_colorBlend(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const colorBlend_value_buf_selector: number = thisDeserializer.readInt8()
        let colorBlend_value_buf: Color | string | Resource | undefined|undefined 
        if (colorBlend_value_buf_selector == 0) {
            colorBlend_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (colorBlend_value_buf_selector == 1) {
            colorBlend_value_buf = (thisDeserializer.readString() as string)
        }
        else if (colorBlend_value_buf_selector == 2) {
            colorBlend_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for colorBlend_value_buf has to be chosen through deserialisation.")
        }
        node.colorBlend_value = (colorBlend_value_buf as Color | string | Resource)
    }
    _CommonMethod_saturate(ptr: KPointer, value: number): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.saturate_value = value
    }
    _CommonMethod_sepia(ptr: KPointer, value: number): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.sepia_value = value
    }
    _CommonMethod_invert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const invert_value_buf_selector: number = thisDeserializer.readInt8()
        let invert_value_buf: number | InvertOptions | undefined|undefined 
        if (invert_value_buf_selector == 0) {
            invert_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (invert_value_buf_selector == 1) {
            invert_value_buf = thisDeserializer.readInvertOptions()
        }
        else {
            throw new Error("One of the branches for invert_value_buf has to be chosen through deserialisation.")
        }
        node.invert_value = (invert_value_buf as number | InvertOptions)
    }
    _CommonMethod_hueRotate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const hueRotate_value_buf_selector: number = thisDeserializer.readInt8()
        let hueRotate_value_buf: number | string | undefined|undefined 
        if (hueRotate_value_buf_selector == 0) {
            hueRotate_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (hueRotate_value_buf_selector == 1) {
            hueRotate_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for hueRotate_value_buf has to be chosen through deserialisation.")
        }
        node.hueRotate_value = (hueRotate_value_buf as number | string)
    }
    _CommonMethod_useShadowBatching(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.useShadowBatching_value = value
    }
    _CommonMethod_useEffect0(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.useEffect0_value = value
    }
    _CommonMethod_useEffect1(ptr: KPointer, useEffect: KInt, effectType: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.useEffect1_useEffect = useEffect
        node.useEffect1_effectType = effectType
    }
    _CommonMethod_renderGroup(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.renderGroup_value = value
    }
    _CommonMethod_freeze(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.freeze_value = value
    }
    _CommonMethod_translate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.translate_value = thisDeserializer.readTranslateOptions()
    }
    _CommonMethod_scale(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.scale_value = thisDeserializer.readScaleOptions()
    }
    _CommonMethod_gridSpan(ptr: KPointer, value: number): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.gridSpan_value = value
    }
    _CommonMethod_gridOffset(ptr: KPointer, value: number): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.gridOffset_value = value
    }
    _CommonMethod_rotate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.rotate_value = thisDeserializer.readRotateOptions()
    }
    _CommonMethod_transform(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.transform_value = (thisDeserializer.readCustomObject("Object") as Object)
    }
    _CommonMethod_onAppear(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onAppear_value = thisDeserializer.readCallback_Void()
    }
    _CommonMethod_onDisAppear(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDisAppear_value = thisDeserializer.readCallback_Void()
    }
    _CommonMethod_onAttach(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onAttach_value = thisDeserializer.readCallback_Void()
    }
    _CommonMethod_onDetach(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDetach_value = thisDeserializer.readCallback_Void()
    }
    _CommonMethod_onAreaChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onAreaChange_value = thisDeserializer.readCallback_Area_Area_Void()
    }
    _CommonMethod_visibility(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.visibility_value = value
    }
    _CommonMethod_flexGrow(ptr: KPointer, value: number): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.flexGrow_value = value
    }
    _CommonMethod_flexShrink(ptr: KPointer, value: number): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.flexShrink_value = value
    }
    _CommonMethod_flexBasis(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const flexBasis_value_buf_selector: number = thisDeserializer.readInt8()
        let flexBasis_value_buf: number | string | undefined|undefined 
        if (flexBasis_value_buf_selector == 0) {
            flexBasis_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (flexBasis_value_buf_selector == 1) {
            flexBasis_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for flexBasis_value_buf has to be chosen through deserialisation.")
        }
        node.flexBasis_value = (flexBasis_value_buf as number | string)
    }
    _CommonMethod_alignSelf(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.alignSelf_value = value
    }
    _CommonMethod_displayPriority(ptr: KPointer, value: number): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.displayPriority_value = value
    }
    _CommonMethod_zIndex(ptr: KPointer, value: number): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.zIndex_value = value
    }
    _CommonMethod_direction(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.direction_value = value
    }
    _CommonMethod_align(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.align_value = value
    }
    _CommonMethod_position(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const position_value_buf_selector: number = thisDeserializer.readInt8()
        let position_value_buf: Position | Edges | LocalizedEdges | undefined|undefined 
        if (position_value_buf_selector == 0) {
            position_value_buf = thisDeserializer.readPosition()
        }
        else if (position_value_buf_selector == 1) {
            position_value_buf = thisDeserializer.readEdges()
        }
        else if (position_value_buf_selector == 2) {
            position_value_buf = thisDeserializer.readLocalizedEdges()
        }
        else {
            throw new Error("One of the branches for position_value_buf has to be chosen through deserialisation.")
        }
        node.position_value = (position_value_buf as Position | Edges | LocalizedEdges)
    }
    _CommonMethod_markAnchor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const markAnchor_value_buf_selector: number = thisDeserializer.readInt8()
        let markAnchor_value_buf: Position | LocalizedPosition | undefined|undefined 
        if (markAnchor_value_buf_selector == 0) {
            markAnchor_value_buf = thisDeserializer.readPosition()
        }
        else if (markAnchor_value_buf_selector == 1) {
            markAnchor_value_buf = thisDeserializer.readLocalizedPosition()
        }
        else {
            throw new Error("One of the branches for markAnchor_value_buf has to be chosen through deserialisation.")
        }
        node.markAnchor_value = (markAnchor_value_buf as Position | LocalizedPosition)
    }
    _CommonMethod_offset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const offset_value_buf_selector: number = thisDeserializer.readInt8()
        let offset_value_buf: Position | Edges | LocalizedEdges | undefined|undefined 
        if (offset_value_buf_selector == 0) {
            offset_value_buf = thisDeserializer.readPosition()
        }
        else if (offset_value_buf_selector == 1) {
            offset_value_buf = thisDeserializer.readEdges()
        }
        else if (offset_value_buf_selector == 2) {
            offset_value_buf = thisDeserializer.readLocalizedEdges()
        }
        else {
            throw new Error("One of the branches for offset_value_buf has to be chosen through deserialisation.")
        }
        node.offset_value = (offset_value_buf as Position | Edges | LocalizedEdges)
    }
    _CommonMethod_enabled(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.enabled_value = value
    }
    _CommonMethod_useSizeType(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const useSizeType_value_buf_xs_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let useSizeType_value_buf_xs_buf: number | { span: number, offset: number } | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (useSizeType_value_buf_xs_buf_runtimeType))
        {
            const useSizeType_value_buf_xs_buf__selector: number = thisDeserializer.readInt8()
            let useSizeType_value_buf_xs_buf_: number | { span: number, offset: number } | undefined|undefined 
            if (useSizeType_value_buf_xs_buf__selector == 0) {
                useSizeType_value_buf_xs_buf_ = (thisDeserializer.readNumber() as number)
            }
            else if (useSizeType_value_buf_xs_buf__selector == 1) {
                const useSizeType_value_buf_xs_buf__u_span: number = (thisDeserializer.readNumber() as number)
                const useSizeType_value_buf_xs_buf__u_offset: number = (thisDeserializer.readNumber() as number)
                useSizeType_value_buf_xs_buf_ = ({span: useSizeType_value_buf_xs_buf__u_span, offset: useSizeType_value_buf_xs_buf__u_offset} as { span: number, offset: number })
            }
            else {
                throw new Error("One of the branches for useSizeType_value_buf_xs_buf_ has to be chosen through deserialisation.")
            }
            useSizeType_value_buf_xs_buf = (useSizeType_value_buf_xs_buf_ as number | { span: number, offset: number })
        }
        const useSizeType_value_buf_xs: undefined | number | { span: number, offset: number } = useSizeType_value_buf_xs_buf
        const useSizeType_value_buf_sm_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let useSizeType_value_buf_sm_buf: number | { span: number, offset: number } | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (useSizeType_value_buf_sm_buf_runtimeType))
        {
            const useSizeType_value_buf_sm_buf__selector: number = thisDeserializer.readInt8()
            let useSizeType_value_buf_sm_buf_: number | { span: number, offset: number } | undefined|undefined 
            if (useSizeType_value_buf_sm_buf__selector == 0) {
                useSizeType_value_buf_sm_buf_ = (thisDeserializer.readNumber() as number)
            }
            else if (useSizeType_value_buf_sm_buf__selector == 1) {
                const useSizeType_value_buf_sm_buf__u_span: number = (thisDeserializer.readNumber() as number)
                const useSizeType_value_buf_sm_buf__u_offset: number = (thisDeserializer.readNumber() as number)
                useSizeType_value_buf_sm_buf_ = ({span: useSizeType_value_buf_sm_buf__u_span, offset: useSizeType_value_buf_sm_buf__u_offset} as { span: number, offset: number })
            }
            else {
                throw new Error("One of the branches for useSizeType_value_buf_sm_buf_ has to be chosen through deserialisation.")
            }
            useSizeType_value_buf_sm_buf = (useSizeType_value_buf_sm_buf_ as number | { span: number, offset: number })
        }
        const useSizeType_value_buf_sm: undefined | number | { span: number, offset: number } = useSizeType_value_buf_sm_buf
        const useSizeType_value_buf_md_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let useSizeType_value_buf_md_buf: number | { span: number, offset: number } | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (useSizeType_value_buf_md_buf_runtimeType))
        {
            const useSizeType_value_buf_md_buf__selector: number = thisDeserializer.readInt8()
            let useSizeType_value_buf_md_buf_: number | { span: number, offset: number } | undefined|undefined 
            if (useSizeType_value_buf_md_buf__selector == 0) {
                useSizeType_value_buf_md_buf_ = (thisDeserializer.readNumber() as number)
            }
            else if (useSizeType_value_buf_md_buf__selector == 1) {
                const useSizeType_value_buf_md_buf__u_span: number = (thisDeserializer.readNumber() as number)
                const useSizeType_value_buf_md_buf__u_offset: number = (thisDeserializer.readNumber() as number)
                useSizeType_value_buf_md_buf_ = ({span: useSizeType_value_buf_md_buf__u_span, offset: useSizeType_value_buf_md_buf__u_offset} as { span: number, offset: number })
            }
            else {
                throw new Error("One of the branches for useSizeType_value_buf_md_buf_ has to be chosen through deserialisation.")
            }
            useSizeType_value_buf_md_buf = (useSizeType_value_buf_md_buf_ as number | { span: number, offset: number })
        }
        const useSizeType_value_buf_md: undefined | number | { span: number, offset: number } = useSizeType_value_buf_md_buf
        const useSizeType_value_buf_lg_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let useSizeType_value_buf_lg_buf: number | { span: number, offset: number } | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (useSizeType_value_buf_lg_buf_runtimeType))
        {
            const useSizeType_value_buf_lg_buf__selector: number = thisDeserializer.readInt8()
            let useSizeType_value_buf_lg_buf_: number | { span: number, offset: number } | undefined|undefined 
            if (useSizeType_value_buf_lg_buf__selector == 0) {
                useSizeType_value_buf_lg_buf_ = (thisDeserializer.readNumber() as number)
            }
            else if (useSizeType_value_buf_lg_buf__selector == 1) {
                const useSizeType_value_buf_lg_buf__u_span: number = (thisDeserializer.readNumber() as number)
                const useSizeType_value_buf_lg_buf__u_offset: number = (thisDeserializer.readNumber() as number)
                useSizeType_value_buf_lg_buf_ = ({span: useSizeType_value_buf_lg_buf__u_span, offset: useSizeType_value_buf_lg_buf__u_offset} as { span: number, offset: number })
            }
            else {
                throw new Error("One of the branches for useSizeType_value_buf_lg_buf_ has to be chosen through deserialisation.")
            }
            useSizeType_value_buf_lg_buf = (useSizeType_value_buf_lg_buf_ as number | { span: number, offset: number })
        }
        const useSizeType_value_buf_lg: undefined | number | { span: number, offset: number } = useSizeType_value_buf_lg_buf
        node.useSizeType_value = ({xs: useSizeType_value_buf_xs, sm: useSizeType_value_buf_sm, md: useSizeType_value_buf_md, lg: useSizeType_value_buf_lg} as { xs?: number | { span: number, offset: number }, sm?: number | { span: number, offset: number }, md?: number | { span: number, offset: number }, lg?: number | { span: number, offset: number } })
    }
    _CommonMethod_alignRules0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.alignRules0_value = thisDeserializer.readAlignRuleOption()
    }
    _CommonMethod_alignRules1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.alignRules1_value = thisDeserializer.readLocalizedAlignRuleOptions()
    }
    _CommonMethod_aspectRatio(ptr: KPointer, value: number): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.aspectRatio_value = value
    }
    _CommonMethod_clickEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const clickEffect_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let clickEffect_value_buf: ClickEffect | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (clickEffect_value_buf_runtimeType))
        {
            clickEffect_value_buf = thisDeserializer.readClickEffect()
        }
        node.clickEffect_value = clickEffect_value_buf
    }
    _CommonMethod_onDragStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDragStart_value = thisDeserializer.readCallback_DragEvent_String_Union_CustomBuilder_DragItemInfo()
    }
    _CommonMethod_onDragEnter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDragEnter_value = thisDeserializer.readCallback_DragEvent_String_Void()
    }
    _CommonMethod_onDragMove(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDragMove_value = thisDeserializer.readCallback_DragEvent_String_Void()
    }
    _CommonMethod_onDragLeave(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDragLeave_value = thisDeserializer.readCallback_DragEvent_String_Void()
    }
    _CommonMethod_onDrop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDrop_value = thisDeserializer.readCallback_DragEvent_String_Void()
    }
    _CommonMethod_onDragEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDragEnd_value = thisDeserializer.readCallback_DragEvent_String_Void()
    }
    _CommonMethod_allowDrop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const allowDrop_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let allowDrop_value_buf: Array<UniformDataType> | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (allowDrop_value_buf_runtimeType))
        {
            const allowDrop_value_buf__length: int32 = thisDeserializer.readInt32()
            let allowDrop_value_buf_: Array<UniformDataType> = new Array<UniformDataType>()
            for (let allowDrop_value_buf__i = 0; allowDrop_value_buf__i < allowDrop_value_buf__length; allowDrop_value_buf__i++) {
                allowDrop_value_buf_[allowDrop_value_buf__i] = thisDeserializer.readUniformDataType()
            }
            allowDrop_value_buf = allowDrop_value_buf_
        }
        node.allowDrop_value = allowDrop_value_buf
    }
    _CommonMethod_draggable(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.draggable_value = value
    }
    _CommonMethod_dragPreview(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const dragPreview_value_buf_selector: number = thisDeserializer.readInt8()
        let dragPreview_value_buf: CustomBuilder | DragItemInfo | string | undefined|undefined 
        if (dragPreview_value_buf_selector == 0) {
            dragPreview_value_buf = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
        }
        else if (dragPreview_value_buf_selector == 1) {
            dragPreview_value_buf = thisDeserializer.readDragItemInfo()
        }
        else if (dragPreview_value_buf_selector == 2) {
            dragPreview_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for dragPreview_value_buf has to be chosen through deserialisation.")
        }
        node.dragPreview_value = (dragPreview_value_buf as CustomBuilder | DragItemInfo | string)
    }
    _CommonMethod_onPreDrag(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onPreDrag_value = thisDeserializer.readCallback_PreDragStatus_Void()
    }
    _CommonMethod_linearGradient(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const linearGradient_value_buf_angle_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let linearGradient_value_buf_angle_buf: number | string | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (linearGradient_value_buf_angle_buf_runtimeType))
        {
            const linearGradient_value_buf_angle_buf__selector: number = thisDeserializer.readInt8()
            let linearGradient_value_buf_angle_buf_: number | string | undefined|undefined 
            if (linearGradient_value_buf_angle_buf__selector == 0) {
                linearGradient_value_buf_angle_buf_ = (thisDeserializer.readNumber() as number)
            }
            else if (linearGradient_value_buf_angle_buf__selector == 1) {
                linearGradient_value_buf_angle_buf_ = (thisDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for linearGradient_value_buf_angle_buf_ has to be chosen through deserialisation.")
            }
            linearGradient_value_buf_angle_buf = (linearGradient_value_buf_angle_buf_ as number | string)
        }
        const linearGradient_value_buf_angle: undefined | number | string = linearGradient_value_buf_angle_buf
        const linearGradient_value_buf_direction_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let linearGradient_value_buf_direction_buf: GradientDirection | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (linearGradient_value_buf_direction_buf_runtimeType))
        {
            linearGradient_value_buf_direction_buf = (thisDeserializer.readInt32() as GradientDirection)
        }
        const linearGradient_value_buf_direction: undefined | GradientDirection = linearGradient_value_buf_direction_buf
        const linearGradient_value_buf_colors_buf_length: int32 = thisDeserializer.readInt32()
        let linearGradient_value_buf_colors_buf: Array<[ ResourceColor, number ]> = new Array<[ ResourceColor, number ]>()
        for (let linearGradient_value_buf_colors_buf_i = 0; linearGradient_value_buf_colors_buf_i < linearGradient_value_buf_colors_buf_length; linearGradient_value_buf_colors_buf_i++) {
            const linearGradient_value_buf_colors_buf_buf_value0_buf_selector: number = thisDeserializer.readInt8()
            let linearGradient_value_buf_colors_buf_buf_value0_buf: Color | number | string | Resource | undefined|undefined 
            if (linearGradient_value_buf_colors_buf_buf_value0_buf_selector == 0) {
                linearGradient_value_buf_colors_buf_buf_value0_buf = (thisDeserializer.readInt32() as Color)
            }
            else if (linearGradient_value_buf_colors_buf_buf_value0_buf_selector == 1) {
                linearGradient_value_buf_colors_buf_buf_value0_buf = (thisDeserializer.readNumber() as number)
            }
            else if (linearGradient_value_buf_colors_buf_buf_value0_buf_selector == 2) {
                linearGradient_value_buf_colors_buf_buf_value0_buf = (thisDeserializer.readString() as string)
            }
            else if (linearGradient_value_buf_colors_buf_buf_value0_buf_selector == 3) {
                linearGradient_value_buf_colors_buf_buf_value0_buf = thisDeserializer.readResource()
            }
            else {
                throw new Error("One of the branches for linearGradient_value_buf_colors_buf_buf_value0_buf has to be chosen through deserialisation.")
            }
            const linearGradient_value_buf_colors_buf_buf_value0: ResourceColor = (linearGradient_value_buf_colors_buf_buf_value0_buf as Color | number | string | Resource)
            const linearGradient_value_buf_colors_buf_buf_value1: number = (thisDeserializer.readNumber() as number)
            linearGradient_value_buf_colors_buf[linearGradient_value_buf_colors_buf_i] = ([linearGradient_value_buf_colors_buf_buf_value0, linearGradient_value_buf_colors_buf_buf_value1] as [ ResourceColor, number ])
        }
        const linearGradient_value_buf_colors: Array<[ ResourceColor, number ]> = linearGradient_value_buf_colors_buf
        const linearGradient_value_buf_repeating_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let linearGradient_value_buf_repeating_buf: boolean | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (linearGradient_value_buf_repeating_buf_runtimeType))
        {
            linearGradient_value_buf_repeating_buf = thisDeserializer.readBoolean()
        }
        const linearGradient_value_buf_repeating: undefined | boolean = linearGradient_value_buf_repeating_buf
        node.linearGradient_value = ({angle: linearGradient_value_buf_angle, direction: linearGradient_value_buf_direction, colors: linearGradient_value_buf_colors, repeating: linearGradient_value_buf_repeating} as { angle?: number | string, direction?: GradientDirection, colors: Array<[ ResourceColor, number ]>, repeating?: boolean })
    }
    _CommonMethod_sweepGradient(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const sweepGradient_value_buf_center_buf_value0: Length = (thisDeserializer.readLength() as Length)
        const sweepGradient_value_buf_center_buf_value1: Length = (thisDeserializer.readLength() as Length)
        const sweepGradient_value_buf_center: [ Length, Length ] = ([sweepGradient_value_buf_center_buf_value0, sweepGradient_value_buf_center_buf_value1] as [ Length, Length ])
        const sweepGradient_value_buf_start_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let sweepGradient_value_buf_start_buf: number | string | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (sweepGradient_value_buf_start_buf_runtimeType))
        {
            const sweepGradient_value_buf_start_buf__selector: number = thisDeserializer.readInt8()
            let sweepGradient_value_buf_start_buf_: number | string | undefined|undefined 
            if (sweepGradient_value_buf_start_buf__selector == 0) {
                sweepGradient_value_buf_start_buf_ = (thisDeserializer.readNumber() as number)
            }
            else if (sweepGradient_value_buf_start_buf__selector == 1) {
                sweepGradient_value_buf_start_buf_ = (thisDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for sweepGradient_value_buf_start_buf_ has to be chosen through deserialisation.")
            }
            sweepGradient_value_buf_start_buf = (sweepGradient_value_buf_start_buf_ as number | string)
        }
        const sweepGradient_value_buf_start: undefined | number | string = sweepGradient_value_buf_start_buf
        const sweepGradient_value_buf_end_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let sweepGradient_value_buf_end_buf: number | string | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (sweepGradient_value_buf_end_buf_runtimeType))
        {
            const sweepGradient_value_buf_end_buf__selector: number = thisDeserializer.readInt8()
            let sweepGradient_value_buf_end_buf_: number | string | undefined|undefined 
            if (sweepGradient_value_buf_end_buf__selector == 0) {
                sweepGradient_value_buf_end_buf_ = (thisDeserializer.readNumber() as number)
            }
            else if (sweepGradient_value_buf_end_buf__selector == 1) {
                sweepGradient_value_buf_end_buf_ = (thisDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for sweepGradient_value_buf_end_buf_ has to be chosen through deserialisation.")
            }
            sweepGradient_value_buf_end_buf = (sweepGradient_value_buf_end_buf_ as number | string)
        }
        const sweepGradient_value_buf_end: undefined | number | string = sweepGradient_value_buf_end_buf
        const sweepGradient_value_buf_rotation_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let sweepGradient_value_buf_rotation_buf: number | string | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (sweepGradient_value_buf_rotation_buf_runtimeType))
        {
            const sweepGradient_value_buf_rotation_buf__selector: number = thisDeserializer.readInt8()
            let sweepGradient_value_buf_rotation_buf_: number | string | undefined|undefined 
            if (sweepGradient_value_buf_rotation_buf__selector == 0) {
                sweepGradient_value_buf_rotation_buf_ = (thisDeserializer.readNumber() as number)
            }
            else if (sweepGradient_value_buf_rotation_buf__selector == 1) {
                sweepGradient_value_buf_rotation_buf_ = (thisDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for sweepGradient_value_buf_rotation_buf_ has to be chosen through deserialisation.")
            }
            sweepGradient_value_buf_rotation_buf = (sweepGradient_value_buf_rotation_buf_ as number | string)
        }
        const sweepGradient_value_buf_rotation: undefined | number | string = sweepGradient_value_buf_rotation_buf
        const sweepGradient_value_buf_colors_buf_length: int32 = thisDeserializer.readInt32()
        let sweepGradient_value_buf_colors_buf: Array<[ ResourceColor, number ]> = new Array<[ ResourceColor, number ]>()
        for (let sweepGradient_value_buf_colors_buf_i = 0; sweepGradient_value_buf_colors_buf_i < sweepGradient_value_buf_colors_buf_length; sweepGradient_value_buf_colors_buf_i++) {
            const sweepGradient_value_buf_colors_buf_buf_value0_buf_selector: number = thisDeserializer.readInt8()
            let sweepGradient_value_buf_colors_buf_buf_value0_buf: Color | number | string | Resource | undefined|undefined 
            if (sweepGradient_value_buf_colors_buf_buf_value0_buf_selector == 0) {
                sweepGradient_value_buf_colors_buf_buf_value0_buf = (thisDeserializer.readInt32() as Color)
            }
            else if (sweepGradient_value_buf_colors_buf_buf_value0_buf_selector == 1) {
                sweepGradient_value_buf_colors_buf_buf_value0_buf = (thisDeserializer.readNumber() as number)
            }
            else if (sweepGradient_value_buf_colors_buf_buf_value0_buf_selector == 2) {
                sweepGradient_value_buf_colors_buf_buf_value0_buf = (thisDeserializer.readString() as string)
            }
            else if (sweepGradient_value_buf_colors_buf_buf_value0_buf_selector == 3) {
                sweepGradient_value_buf_colors_buf_buf_value0_buf = thisDeserializer.readResource()
            }
            else {
                throw new Error("One of the branches for sweepGradient_value_buf_colors_buf_buf_value0_buf has to be chosen through deserialisation.")
            }
            const sweepGradient_value_buf_colors_buf_buf_value0: ResourceColor = (sweepGradient_value_buf_colors_buf_buf_value0_buf as Color | number | string | Resource)
            const sweepGradient_value_buf_colors_buf_buf_value1: number = (thisDeserializer.readNumber() as number)
            sweepGradient_value_buf_colors_buf[sweepGradient_value_buf_colors_buf_i] = ([sweepGradient_value_buf_colors_buf_buf_value0, sweepGradient_value_buf_colors_buf_buf_value1] as [ ResourceColor, number ])
        }
        const sweepGradient_value_buf_colors: Array<[ ResourceColor, number ]> = sweepGradient_value_buf_colors_buf
        const sweepGradient_value_buf_repeating_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let sweepGradient_value_buf_repeating_buf: boolean | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (sweepGradient_value_buf_repeating_buf_runtimeType))
        {
            sweepGradient_value_buf_repeating_buf = thisDeserializer.readBoolean()
        }
        const sweepGradient_value_buf_repeating: undefined | boolean = sweepGradient_value_buf_repeating_buf
        node.sweepGradient_value = ({center: sweepGradient_value_buf_center, start: sweepGradient_value_buf_start, end: sweepGradient_value_buf_end, rotation: sweepGradient_value_buf_rotation, colors: sweepGradient_value_buf_colors, repeating: sweepGradient_value_buf_repeating} as { center: [ Length, Length ], start?: number | string, end?: number | string, rotation?: number | string, colors: Array<[ ResourceColor, number ]>, repeating?: boolean })
    }
    _CommonMethod_radialGradient(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const radialGradient_value_buf_center_buf_value0: Length = (thisDeserializer.readLength() as Length)
        const radialGradient_value_buf_center_buf_value1: Length = (thisDeserializer.readLength() as Length)
        const radialGradient_value_buf_center: [ Length, Length ] = ([radialGradient_value_buf_center_buf_value0, radialGradient_value_buf_center_buf_value1] as [ Length, Length ])
        const radialGradient_value_buf_radius_buf_selector: number = thisDeserializer.readInt8()
        let radialGradient_value_buf_radius_buf: number | string | undefined|undefined 
        if (radialGradient_value_buf_radius_buf_selector == 0) {
            radialGradient_value_buf_radius_buf = (thisDeserializer.readNumber() as number)
        }
        else if (radialGradient_value_buf_radius_buf_selector == 1) {
            radialGradient_value_buf_radius_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for radialGradient_value_buf_radius_buf has to be chosen through deserialisation.")
        }
        const radialGradient_value_buf_radius: number | string = (radialGradient_value_buf_radius_buf as number | string)
        const radialGradient_value_buf_colors_buf_length: int32 = thisDeserializer.readInt32()
        let radialGradient_value_buf_colors_buf: Array<[ ResourceColor, number ]> = new Array<[ ResourceColor, number ]>()
        for (let radialGradient_value_buf_colors_buf_i = 0; radialGradient_value_buf_colors_buf_i < radialGradient_value_buf_colors_buf_length; radialGradient_value_buf_colors_buf_i++) {
            const radialGradient_value_buf_colors_buf_buf_value0_buf_selector: number = thisDeserializer.readInt8()
            let radialGradient_value_buf_colors_buf_buf_value0_buf: Color | number | string | Resource | undefined|undefined 
            if (radialGradient_value_buf_colors_buf_buf_value0_buf_selector == 0) {
                radialGradient_value_buf_colors_buf_buf_value0_buf = (thisDeserializer.readInt32() as Color)
            }
            else if (radialGradient_value_buf_colors_buf_buf_value0_buf_selector == 1) {
                radialGradient_value_buf_colors_buf_buf_value0_buf = (thisDeserializer.readNumber() as number)
            }
            else if (radialGradient_value_buf_colors_buf_buf_value0_buf_selector == 2) {
                radialGradient_value_buf_colors_buf_buf_value0_buf = (thisDeserializer.readString() as string)
            }
            else if (radialGradient_value_buf_colors_buf_buf_value0_buf_selector == 3) {
                radialGradient_value_buf_colors_buf_buf_value0_buf = thisDeserializer.readResource()
            }
            else {
                throw new Error("One of the branches for radialGradient_value_buf_colors_buf_buf_value0_buf has to be chosen through deserialisation.")
            }
            const radialGradient_value_buf_colors_buf_buf_value0: ResourceColor = (radialGradient_value_buf_colors_buf_buf_value0_buf as Color | number | string | Resource)
            const radialGradient_value_buf_colors_buf_buf_value1: number = (thisDeserializer.readNumber() as number)
            radialGradient_value_buf_colors_buf[radialGradient_value_buf_colors_buf_i] = ([radialGradient_value_buf_colors_buf_buf_value0, radialGradient_value_buf_colors_buf_buf_value1] as [ ResourceColor, number ])
        }
        const radialGradient_value_buf_colors: Array<[ ResourceColor, number ]> = radialGradient_value_buf_colors_buf
        const radialGradient_value_buf_repeating_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let radialGradient_value_buf_repeating_buf: boolean | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (radialGradient_value_buf_repeating_buf_runtimeType))
        {
            radialGradient_value_buf_repeating_buf = thisDeserializer.readBoolean()
        }
        const radialGradient_value_buf_repeating: undefined | boolean = radialGradient_value_buf_repeating_buf
        node.radialGradient_value = ({center: radialGradient_value_buf_center, radius: radialGradient_value_buf_radius, colors: radialGradient_value_buf_colors, repeating: radialGradient_value_buf_repeating} as { center: [ Length, Length ], radius: number | string, colors: Array<[ ResourceColor, number ]>, repeating?: boolean })
    }
    _CommonMethod_motionPath(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.motionPath_value = thisDeserializer.readMotionPathOptions()
    }
    _CommonMethod_shadow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const shadow_value_buf_selector: number = thisDeserializer.readInt8()
        let shadow_value_buf: ShadowOptions | ShadowStyle | undefined|undefined 
        if (shadow_value_buf_selector == 0) {
            shadow_value_buf = thisDeserializer.readShadowOptions()
        }
        else if (shadow_value_buf_selector == 1) {
            shadow_value_buf = (thisDeserializer.readInt32() as ShadowStyle)
        }
        else {
            throw new Error("One of the branches for shadow_value_buf has to be chosen through deserialisation.")
        }
        node.shadow_value = (shadow_value_buf as ShadowOptions | ShadowStyle)
    }
    _CommonMethod_clip0(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.clip0_value = value
    }
    _CommonMethod_clip1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const clip1_value_buf_selector: number = thisDeserializer.readInt8()
        let clip1_value_buf: boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute | undefined|undefined 
        if (clip1_value_buf_selector == 0) {
            clip1_value_buf = thisDeserializer.readBoolean()
        }
        else if (clip1_value_buf_selector == 1) {
            clip1_value_buf = thisDeserializer.readCircleAttribute()
        }
        else if (clip1_value_buf_selector == 2) {
            clip1_value_buf = thisDeserializer.readEllipseAttribute()
        }
        else if (clip1_value_buf_selector == 3) {
            clip1_value_buf = thisDeserializer.readPathAttribute()
        }
        else if (clip1_value_buf_selector == 4) {
            clip1_value_buf = thisDeserializer.readRectAttribute()
        }
        else {
            throw new Error("One of the branches for clip1_value_buf has to be chosen through deserialisation.")
        }
        node.clip1_value = (clip1_value_buf as boolean | CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute)
    }
    _CommonMethod_clipShape(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const clipShape_value_buf_selector: number = thisDeserializer.readInt8()
        let clipShape_value_buf: CircleShape | EllipseShape | PathShape | RectShape | undefined|undefined 
        if (clipShape_value_buf_selector == 0) {
            clipShape_value_buf = thisDeserializer.readCircleShape()
        }
        else if (clipShape_value_buf_selector == 1) {
            clipShape_value_buf = thisDeserializer.readEllipseShape()
        }
        else if (clipShape_value_buf_selector == 2) {
            clipShape_value_buf = thisDeserializer.readPathShape()
        }
        else if (clipShape_value_buf_selector == 3) {
            clipShape_value_buf = thisDeserializer.readRectShape()
        }
        else {
            throw new Error("One of the branches for clipShape_value_buf has to be chosen through deserialisation.")
        }
        node.clipShape_value = (clipShape_value_buf as CircleShape | EllipseShape | PathShape | RectShape)
    }
    _CommonMethod_mask0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.mask0_value = (thisDeserializer.readProgressMask() as ProgressMask)
    }
    _CommonMethod_mask1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const mask1_value_buf_selector: number = thisDeserializer.readInt8()
        let mask1_value_buf: CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute | ProgressMask | undefined|undefined 
        if (mask1_value_buf_selector == 0) {
            mask1_value_buf = thisDeserializer.readCircleAttribute()
        }
        else if (mask1_value_buf_selector == 1) {
            mask1_value_buf = thisDeserializer.readEllipseAttribute()
        }
        else if (mask1_value_buf_selector == 2) {
            mask1_value_buf = thisDeserializer.readPathAttribute()
        }
        else if (mask1_value_buf_selector == 3) {
            mask1_value_buf = thisDeserializer.readRectAttribute()
        }
        else if (mask1_value_buf_selector == 4) {
            mask1_value_buf = (thisDeserializer.readProgressMask() as ProgressMask)
        }
        else {
            throw new Error("One of the branches for mask1_value_buf has to be chosen through deserialisation.")
        }
        node.mask1_value = (mask1_value_buf as CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute | ProgressMask)
    }
    _CommonMethod_maskShape(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const maskShape_value_buf_selector: number = thisDeserializer.readInt8()
        let maskShape_value_buf: CircleShape | EllipseShape | PathShape | RectShape | undefined|undefined 
        if (maskShape_value_buf_selector == 0) {
            maskShape_value_buf = thisDeserializer.readCircleShape()
        }
        else if (maskShape_value_buf_selector == 1) {
            maskShape_value_buf = thisDeserializer.readEllipseShape()
        }
        else if (maskShape_value_buf_selector == 2) {
            maskShape_value_buf = thisDeserializer.readPathShape()
        }
        else if (maskShape_value_buf_selector == 3) {
            maskShape_value_buf = thisDeserializer.readRectShape()
        }
        else {
            throw new Error("One of the branches for maskShape_value_buf has to be chosen through deserialisation.")
        }
        node.maskShape_value = (maskShape_value_buf as CircleShape | EllipseShape | PathShape | RectShape)
    }
    _CommonMethod_key(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.key_value = value
    }
    _CommonMethod_id(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.id_value = value
    }
    _CommonMethod_geometryTransition0(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.geometryTransition0_value = value
    }
    _CommonMethod_geometryTransition1(ptr: KPointer, id: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.geometryTransition1_id = id
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const geometryTransition1_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let geometryTransition1_options_buf: GeometryTransitionOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (geometryTransition1_options_buf_runtimeType))
        {
            geometryTransition1_options_buf = thisDeserializer.readGeometryTransitionOptions()
        }
        node.geometryTransition1_options = geometryTransition1_options_buf
    }
    _CommonMethod_stateStyles(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.stateStyles_value = thisDeserializer.readStateStyles()
    }
    _CommonMethod_restoreId(ptr: KPointer, value: number): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.restoreId_value = value
    }
    _CommonMethod_sphericalEffect(ptr: KPointer, value: number): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.sphericalEffect_value = value
    }
    _CommonMethod_lightUpEffect(ptr: KPointer, value: number): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.lightUpEffect_value = value
    }
    _CommonMethod_pixelStretchEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.pixelStretchEffect_value = thisDeserializer.readPixelStretchEffectOptions()
    }
    _CommonMethod_accessibilityGroup0(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.accessibilityGroup0_value = value
    }
    _CommonMethod_accessibilityGroup1(ptr: KPointer, isGroup: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.accessibilityGroup1_isGroup = isGroup
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.accessibilityGroup1_accessibilityOptions = thisDeserializer.readAccessibilityOptions()
    }
    _CommonMethod_accessibilityText0(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.accessibilityText0_value = value
    }
    _CommonMethod_accessibilityText1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.accessibilityText1_value = thisDeserializer.readResource()
    }
    _CommonMethod_accessibilityTextHint(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.accessibilityTextHint_value = value
    }
    _CommonMethod_accessibilityDescription0(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.accessibilityDescription0_value = value
    }
    _CommonMethod_accessibilityDescription1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.accessibilityDescription1_value = thisDeserializer.readResource()
    }
    _CommonMethod_accessibilityLevel(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.accessibilityLevel_value = value
    }
    _CommonMethod_accessibilityVirtualNode(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.accessibilityVirtualNode_value = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
    }
    _CommonMethod_accessibilityChecked(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.accessibilityChecked_value = value
    }
    _CommonMethod_accessibilitySelected(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.accessibilitySelected_value = value
    }
    _CommonMethod_obscured(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const obscured_value_buf_length: int32 = thisDeserializer.readInt32()
        let obscured_value_buf: Array<ObscuredReasons> = new Array<ObscuredReasons>()
        for (let obscured_value_buf_i = 0; obscured_value_buf_i < obscured_value_buf_length; obscured_value_buf_i++) {
            obscured_value_buf[obscured_value_buf_i] = (thisDeserializer.readInt32() as ObscuredReasons)
        }
        node.obscured_value = obscured_value_buf
    }
    _CommonMethod_reuseId(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.reuseId_value = value
    }
    _CommonMethod_renderFit(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.renderFit_value = value
    }
    _CommonMethod_gestureModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.gestureModifier_value = (thisDeserializer.readGestureModifier() as GestureModifier)
    }
    _CommonMethod_backgroundBrightness(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.backgroundBrightness_value = thisDeserializer.readBackgroundBrightnessOptions()
    }
    _CommonMethod_onGestureJudgeBegin(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onGestureJudgeBegin_value = thisDeserializer.readCallback_GestureInfo_BaseGestureEvent_GestureJudgeResult()
    }
    _CommonMethod_onGestureRecognizerJudgeBegin0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onGestureRecognizerJudgeBegin0_value = thisDeserializer.readGestureRecognizerJudgeBeginCallback()
    }
    _CommonMethod_onGestureRecognizerJudgeBegin1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, exposeInnerGesture: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onGestureRecognizerJudgeBegin1_callback = thisDeserializer.readGestureRecognizerJudgeBeginCallback()
        node.onGestureRecognizerJudgeBegin1_exposeInnerGesture = thisLength
    }
    _CommonMethod_shouldBuiltInRecognizerParallelWith(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.shouldBuiltInRecognizerParallelWith_value = thisDeserializer.readShouldBuiltInRecognizerParallelWithCallback()
    }
    _CommonMethod_monopolizeEvents(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.monopolizeEvents_value = value
    }
    _CommonMethod_onTouchIntercept(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onTouchIntercept_value = thisDeserializer.readCallback_TouchEvent_HitTestMode()
    }
    _CommonMethod_onSizeChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSizeChange_value = thisDeserializer.readSizeChangeCallback()
    }
    _CommonMethod_customProperty(ptr: KPointer, name: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.customProperty_name = name
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const customProperty_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let customProperty_value_buf: Object | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (customProperty_value_buf_runtimeType))
        {
            customProperty_value_buf = (thisDeserializer.readCustomObject("Object") as Object)
        }
        node.customProperty_value = customProperty_value_buf
    }
    _CommonMethod_expandSafeArea(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const expandSafeArea_types_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let expandSafeArea_types_buf: Array<SafeAreaType> | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (expandSafeArea_types_buf_runtimeType))
        {
            const expandSafeArea_types_buf__length: int32 = thisDeserializer.readInt32()
            let expandSafeArea_types_buf_: Array<SafeAreaType> = new Array<SafeAreaType>()
            for (let expandSafeArea_types_buf__i = 0; expandSafeArea_types_buf__i < expandSafeArea_types_buf__length; expandSafeArea_types_buf__i++) {
                expandSafeArea_types_buf_[expandSafeArea_types_buf__i] = (thisDeserializer.readInt32() as SafeAreaType)
            }
            expandSafeArea_types_buf = expandSafeArea_types_buf_
        }
        node.expandSafeArea_types = expandSafeArea_types_buf
        const expandSafeArea_edges_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let expandSafeArea_edges_buf: Array<SafeAreaEdge> | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (expandSafeArea_edges_buf_runtimeType))
        {
            const expandSafeArea_edges_buf__length: int32 = thisDeserializer.readInt32()
            let expandSafeArea_edges_buf_: Array<SafeAreaEdge> = new Array<SafeAreaEdge>()
            for (let expandSafeArea_edges_buf__i = 0; expandSafeArea_edges_buf__i < expandSafeArea_edges_buf__length; expandSafeArea_edges_buf__i++) {
                expandSafeArea_edges_buf_[expandSafeArea_edges_buf__i] = (thisDeserializer.readInt32() as SafeAreaEdge)
            }
            expandSafeArea_edges_buf = expandSafeArea_edges_buf_
        }
        node.expandSafeArea_edges = expandSafeArea_edges_buf
    }
    _CommonMethod_background(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.background_builder = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
        const background_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let background_options_buf: { align?: Alignment } | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (background_options_buf_runtimeType))
        {
            const background_options_buf__align_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let background_options_buf__align_buf: Alignment | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (background_options_buf__align_buf_runtimeType))
            {
                background_options_buf__align_buf = (thisDeserializer.readInt32() as Alignment)
            }
            const background_options_buf__align: undefined | Alignment = background_options_buf__align_buf
            background_options_buf = ({align: background_options_buf__align} as { align?: Alignment })
        }
        node.background_options = background_options_buf
    }
    _CommonMethod_backgroundImage(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const backgroundImage_src_buf_selector: number = thisDeserializer.readInt8()
        let backgroundImage_src_buf: ResourceStr | PixelMap | undefined|undefined 
        if (backgroundImage_src_buf_selector == 0) {
            const backgroundImage_src_buf_u_selector: number = thisDeserializer.readInt8()
            let backgroundImage_src_buf_u: string | Resource | undefined|undefined 
            if (backgroundImage_src_buf_u_selector == 0) {
                backgroundImage_src_buf_u = (thisDeserializer.readString() as string)
            }
            else if (backgroundImage_src_buf_u_selector == 1) {
                backgroundImage_src_buf_u = thisDeserializer.readResource()
            }
            else {
                throw new Error("One of the branches for backgroundImage_src_buf_u has to be chosen through deserialisation.")
            }
            backgroundImage_src_buf = (backgroundImage_src_buf_u as string | Resource)
        }
        else if (backgroundImage_src_buf_selector == 1) {
            backgroundImage_src_buf = (thisDeserializer.readPixelMap() as PixelMap)
        }
        else {
            throw new Error("One of the branches for backgroundImage_src_buf has to be chosen through deserialisation.")
        }
        node.backgroundImage_src = (backgroundImage_src_buf as ResourceStr | PixelMap)
        const backgroundImage_repeat_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let backgroundImage_repeat_buf: ImageRepeat | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (backgroundImage_repeat_buf_runtimeType))
        {
            backgroundImage_repeat_buf = (thisDeserializer.readInt32() as ImageRepeat)
        }
        node.backgroundImage_repeat = backgroundImage_repeat_buf
    }
    _CommonMethod_backgroundBlurStyle(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.backgroundBlurStyle_value = value
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const backgroundBlurStyle_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let backgroundBlurStyle_options_buf: BackgroundBlurStyleOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (backgroundBlurStyle_options_buf_runtimeType))
        {
            backgroundBlurStyle_options_buf = thisDeserializer.readBackgroundBlurStyleOptions()
        }
        node.backgroundBlurStyle_options = backgroundBlurStyle_options_buf
    }
    _CommonMethod_foregroundBlurStyle(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.foregroundBlurStyle_value = value
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const foregroundBlurStyle_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let foregroundBlurStyle_options_buf: ForegroundBlurStyleOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (foregroundBlurStyle_options_buf_runtimeType))
        {
            foregroundBlurStyle_options_buf = thisDeserializer.readForegroundBlurStyleOptions()
        }
        node.foregroundBlurStyle_options = foregroundBlurStyle_options_buf
    }
    _CommonMethod_focusScopeId0(ptr: KPointer, id: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.focusScopeId0_id = id
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const focusScopeId0_isGroup_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let focusScopeId0_isGroup_buf: boolean | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (focusScopeId0_isGroup_buf_runtimeType))
        {
            focusScopeId0_isGroup_buf = thisDeserializer.readBoolean()
        }
        node.focusScopeId0_isGroup = focusScopeId0_isGroup_buf
    }
    _CommonMethod_focusScopeId1(ptr: KPointer, id: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.focusScopeId1_id = id
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const focusScopeId1_isGroup_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let focusScopeId1_isGroup_buf: boolean | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (focusScopeId1_isGroup_buf_runtimeType))
        {
            focusScopeId1_isGroup_buf = thisDeserializer.readBoolean()
        }
        node.focusScopeId1_isGroup = focusScopeId1_isGroup_buf
        const focusScopeId1_arrowStepOut_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let focusScopeId1_arrowStepOut_buf: boolean | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (focusScopeId1_arrowStepOut_buf_runtimeType))
        {
            focusScopeId1_arrowStepOut_buf = thisDeserializer.readBoolean()
        }
        node.focusScopeId1_arrowStepOut = focusScopeId1_arrowStepOut_buf
    }
    _CommonMethod_focusScopePriority(ptr: KPointer, scopeId: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.focusScopePriority_scopeId = scopeId
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const focusScopePriority_priority_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let focusScopePriority_priority_buf: FocusPriority | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (focusScopePriority_priority_buf_runtimeType))
        {
            focusScopePriority_priority_buf = (thisDeserializer.readInt32() as FocusPriority)
        }
        node.focusScopePriority_priority = focusScopePriority_priority_buf
    }
    _CommonMethod_gesture(ptr: KPointer, gesture: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.gesture_gesture = gesture
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const gesture_mask_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let gesture_mask_buf: GestureMask | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (gesture_mask_buf_runtimeType))
        {
            gesture_mask_buf = (thisDeserializer.readInt32() as GestureMask)
        }
        node.gesture_mask = gesture_mask_buf
    }
    _CommonMethod_priorityGesture(ptr: KPointer, gesture: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.priorityGesture_gesture = gesture
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const priorityGesture_mask_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let priorityGesture_mask_buf: GestureMask | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (priorityGesture_mask_buf_runtimeType))
        {
            priorityGesture_mask_buf = (thisDeserializer.readInt32() as GestureMask)
        }
        node.priorityGesture_mask = priorityGesture_mask_buf
    }
    _CommonMethod_parallelGesture(ptr: KPointer, gesture: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.parallelGesture_gesture = gesture
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const parallelGesture_mask_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let parallelGesture_mask_buf: GestureMask | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (parallelGesture_mask_buf_runtimeType))
        {
            parallelGesture_mask_buf = (thisDeserializer.readInt32() as GestureMask)
        }
        node.parallelGesture_mask = parallelGesture_mask_buf
    }
    _CommonMethod_blur(ptr: KPointer, value: number, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.blur_value = value
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const blur_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let blur_options_buf: BlurOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (blur_options_buf_runtimeType))
        {
            blur_options_buf = thisDeserializer.readBlurOptions()
        }
        node.blur_options = blur_options_buf
    }
    _CommonMethod_linearGradientBlur(ptr: KPointer, value: number, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.linearGradientBlur_value = value
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.linearGradientBlur_options = thisDeserializer.readLinearGradientBlurOptions()
    }
    _CommonMethod_systemBarEffect(ptr: KPointer): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
    }
    _CommonMethod_backdropBlur(ptr: KPointer, value: number, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.backdropBlur_value = value
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const backdropBlur_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let backdropBlur_options_buf: BlurOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (backdropBlur_options_buf_runtimeType))
        {
            backdropBlur_options_buf = thisDeserializer.readBlurOptions()
        }
        node.backdropBlur_options = backdropBlur_options_buf
    }
    _CommonMethod_sharedTransition(ptr: KPointer, id: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.sharedTransition_id = id
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const sharedTransition_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let sharedTransition_options_buf: sharedTransitionOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (sharedTransition_options_buf_runtimeType))
        {
            sharedTransition_options_buf = thisDeserializer.readsharedTransitionOptions()
        }
        node.sharedTransition_options = sharedTransition_options_buf
    }
    _CommonMethod_chainMode(ptr: KPointer, direction: KInt, style: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.chainMode_direction = direction
        node.chainMode_style = style
    }
    _CommonMethod_dragPreviewOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.dragPreviewOptions_value = thisDeserializer.readDragPreviewOptions()
        const dragPreviewOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let dragPreviewOptions_options_buf: DragInteractionOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (dragPreviewOptions_options_buf_runtimeType))
        {
            dragPreviewOptions_options_buf = thisDeserializer.readDragInteractionOptions()
        }
        node.dragPreviewOptions_options = dragPreviewOptions_options_buf
    }
    _CommonMethod_overlay(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const overlay_value_buf_selector: number = thisDeserializer.readInt8()
        let overlay_value_buf: string | CustomBuilder | ComponentContent | undefined|undefined 
        if (overlay_value_buf_selector == 0) {
            overlay_value_buf = (thisDeserializer.readString() as string)
        }
        else if (overlay_value_buf_selector == 1) {
            overlay_value_buf = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
        }
        else if (overlay_value_buf_selector == 2) {
            overlay_value_buf = thisDeserializer.readComponentContent()
        }
        else {
            throw new Error("One of the branches for overlay_value_buf has to be chosen through deserialisation.")
        }
        node.overlay_value = (overlay_value_buf as string | CustomBuilder | ComponentContent)
        const overlay_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let overlay_options_buf: OverlayOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (overlay_options_buf_runtimeType))
        {
            overlay_options_buf = thisDeserializer.readOverlayOptions()
        }
        node.overlay_options = overlay_options_buf
    }
    _CommonMethod_blendMode(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.blendMode_value = value
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const blendMode_type_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let blendMode_type_buf: BlendApplyType | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (blendMode_type_buf_runtimeType))
        {
            blendMode_type_buf = (thisDeserializer.readInt32() as BlendApplyType)
        }
        node.blendMode_type = blendMode_type_buf
    }
    _CommonMethod_advancedBlendMode(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const advancedBlendMode_effect_buf_selector: number = thisDeserializer.readInt8()
        let advancedBlendMode_effect_buf: BlendMode | Blender | undefined|undefined 
        if (advancedBlendMode_effect_buf_selector == 0) {
            advancedBlendMode_effect_buf = (thisDeserializer.readInt32() as BlendMode)
        }
        else if (advancedBlendMode_effect_buf_selector == 1) {
            advancedBlendMode_effect_buf = thisDeserializer.readBlender()
        }
        else {
            throw new Error("One of the branches for advancedBlendMode_effect_buf has to be chosen through deserialisation.")
        }
        node.advancedBlendMode_effect = (advancedBlendMode_effect_buf as BlendMode | Blender)
        const advancedBlendMode_type_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let advancedBlendMode_type_buf: BlendApplyType | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (advancedBlendMode_type_buf_runtimeType))
        {
            advancedBlendMode_type_buf = (thisDeserializer.readInt32() as BlendApplyType)
        }
        node.advancedBlendMode_type = advancedBlendMode_type_buf
    }
    _CommonMethod_bindPopup(ptr: KPointer, show: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.bindPopup_show = show
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const bindPopup_popup_buf_selector: number = thisDeserializer.readInt8()
        let bindPopup_popup_buf: PopupOptions | CustomPopupOptions | undefined|undefined 
        if (bindPopup_popup_buf_selector == 0) {
            bindPopup_popup_buf = thisDeserializer.readPopupOptions()
        }
        else if (bindPopup_popup_buf_selector == 1) {
            bindPopup_popup_buf = thisDeserializer.readCustomPopupOptions()
        }
        else {
            throw new Error("One of the branches for bindPopup_popup_buf has to be chosen through deserialisation.")
        }
        node.bindPopup_popup = (bindPopup_popup_buf as PopupOptions | CustomPopupOptions)
    }
    _CommonMethod_bindMenu0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const bindMenu0_content_buf_selector: number = thisDeserializer.readInt8()
        let bindMenu0_content_buf: Array<MenuElement> | CustomBuilder | undefined|undefined 
        if (bindMenu0_content_buf_selector == 0) {
            const bindMenu0_content_buf_u_length: int32 = thisDeserializer.readInt32()
            let bindMenu0_content_buf_u: Array<MenuElement> = new Array<MenuElement>()
            for (let bindMenu0_content_buf_u_i = 0; bindMenu0_content_buf_u_i < bindMenu0_content_buf_u_length; bindMenu0_content_buf_u_i++) {
                bindMenu0_content_buf_u[bindMenu0_content_buf_u_i] = thisDeserializer.readMenuElement()
            }
            bindMenu0_content_buf = bindMenu0_content_buf_u
        }
        else if (bindMenu0_content_buf_selector == 1) {
            bindMenu0_content_buf = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
        }
        else {
            throw new Error("One of the branches for bindMenu0_content_buf has to be chosen through deserialisation.")
        }
        node.bindMenu0_content = (bindMenu0_content_buf as Array<MenuElement> | CustomBuilder)
        const bindMenu0_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let bindMenu0_options_buf: MenuOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (bindMenu0_options_buf_runtimeType))
        {
            bindMenu0_options_buf = thisDeserializer.readMenuOptions()
        }
        node.bindMenu0_options = bindMenu0_options_buf
    }
    _CommonMethod_bindMenu1(ptr: KPointer, isShow: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.bindMenu1_isShow = isShow
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const bindMenu1_content_buf_selector: number = thisDeserializer.readInt8()
        let bindMenu1_content_buf: Array<MenuElement> | CustomBuilder | undefined|undefined 
        if (bindMenu1_content_buf_selector == 0) {
            const bindMenu1_content_buf_u_length: int32 = thisDeserializer.readInt32()
            let bindMenu1_content_buf_u: Array<MenuElement> = new Array<MenuElement>()
            for (let bindMenu1_content_buf_u_i = 0; bindMenu1_content_buf_u_i < bindMenu1_content_buf_u_length; bindMenu1_content_buf_u_i++) {
                bindMenu1_content_buf_u[bindMenu1_content_buf_u_i] = thisDeserializer.readMenuElement()
            }
            bindMenu1_content_buf = bindMenu1_content_buf_u
        }
        else if (bindMenu1_content_buf_selector == 1) {
            bindMenu1_content_buf = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
        }
        else {
            throw new Error("One of the branches for bindMenu1_content_buf has to be chosen through deserialisation.")
        }
        node.bindMenu1_content = (bindMenu1_content_buf as Array<MenuElement> | CustomBuilder)
        const bindMenu1_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let bindMenu1_options_buf: MenuOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (bindMenu1_options_buf_runtimeType))
        {
            bindMenu1_options_buf = thisDeserializer.readMenuOptions()
        }
        node.bindMenu1_options = bindMenu1_options_buf
    }
    _CommonMethod_bindContextMenu0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, responseType: KInt): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.bindContextMenu0_content = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
        node.bindContextMenu0_responseType = thisLength
        const bindContextMenu0_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let bindContextMenu0_options_buf: ContextMenuOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (bindContextMenu0_options_buf_runtimeType))
        {
            bindContextMenu0_options_buf = thisDeserializer.readContextMenuOptions()
        }
        node.bindContextMenu0_options = bindContextMenu0_options_buf
    }
    _CommonMethod_bindContextMenu1(ptr: KPointer, isShown: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        node.bindContextMenu1_isShown = isShown
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.bindContextMenu1_content = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
        const bindContextMenu1_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let bindContextMenu1_options_buf: ContextMenuOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (bindContextMenu1_options_buf_runtimeType))
        {
            bindContextMenu1_options_buf = thisDeserializer.readContextMenuOptions()
        }
        node.bindContextMenu1_options = bindContextMenu1_options_buf
    }
    _CommonMethod_bindContentCover0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const bindContentCover0_isShow_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let bindContentCover0_isShow_buf: boolean | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (bindContentCover0_isShow_buf_runtimeType))
        {
            bindContentCover0_isShow_buf = thisDeserializer.readBoolean()
        }
        node.bindContentCover0_isShow = bindContentCover0_isShow_buf
        node.bindContentCover0_builder = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
        const bindContentCover0_type_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let bindContentCover0_type_buf: ModalTransition | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (bindContentCover0_type_buf_runtimeType))
        {
            bindContentCover0_type_buf = (thisDeserializer.readInt32() as ModalTransition)
        }
        node.bindContentCover0_type = bindContentCover0_type_buf
    }
    _CommonMethod_bindContentCover1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const bindContentCover1_isShow_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let bindContentCover1_isShow_buf: boolean | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (bindContentCover1_isShow_buf_runtimeType))
        {
            bindContentCover1_isShow_buf = thisDeserializer.readBoolean()
        }
        node.bindContentCover1_isShow = bindContentCover1_isShow_buf
        node.bindContentCover1_builder = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
        const bindContentCover1_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let bindContentCover1_options_buf: ContentCoverOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (bindContentCover1_options_buf_runtimeType))
        {
            bindContentCover1_options_buf = thisDeserializer.readContentCoverOptions()
        }
        node.bindContentCover1_options = bindContentCover1_options_buf
    }
    _CommonMethod_bindSheet(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const bindSheet_isShow_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let bindSheet_isShow_buf: boolean | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (bindSheet_isShow_buf_runtimeType))
        {
            bindSheet_isShow_buf = thisDeserializer.readBoolean()
        }
        node.bindSheet_isShow = bindSheet_isShow_buf
        node.bindSheet_builder = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
        const bindSheet_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let bindSheet_options_buf: SheetOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (bindSheet_options_buf_runtimeType))
        {
            bindSheet_options_buf = thisDeserializer.readSheetOptions()
        }
        node.bindSheet_options = bindSheet_options_buf
    }
    _CommonMethod_onVisibleAreaChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const onVisibleAreaChange_ratios_buf_length: int32 = thisDeserializer.readInt32()
        let onVisibleAreaChange_ratios_buf: Array<number> = new Array<number>()
        for (let onVisibleAreaChange_ratios_buf_i = 0; onVisibleAreaChange_ratios_buf_i < onVisibleAreaChange_ratios_buf_length; onVisibleAreaChange_ratios_buf_i++) {
            onVisibleAreaChange_ratios_buf[onVisibleAreaChange_ratios_buf_i] = (thisDeserializer.readNumber() as number)
        }
        node.onVisibleAreaChange_ratios = onVisibleAreaChange_ratios_buf
        node.onVisibleAreaChange_event = thisDeserializer.readVisibleAreaChangeCallback()
    }
    _CommonMethod_keyboardShortcut(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const keyboardShortcut_value_buf_selector: number = thisDeserializer.readInt8()
        let keyboardShortcut_value_buf: string | FunctionKey | undefined|undefined 
        if (keyboardShortcut_value_buf_selector == 0) {
            keyboardShortcut_value_buf = (thisDeserializer.readString() as string)
        }
        else if (keyboardShortcut_value_buf_selector == 1) {
            keyboardShortcut_value_buf = (thisDeserializer.readInt32() as FunctionKey)
        }
        else {
            throw new Error("One of the branches for keyboardShortcut_value_buf has to be chosen through deserialisation.")
        }
        node.keyboardShortcut_value = (keyboardShortcut_value_buf as string | FunctionKey)
        const keyboardShortcut_keys_buf_length: int32 = thisDeserializer.readInt32()
        let keyboardShortcut_keys_buf: Array<ModifierKey> = new Array<ModifierKey>()
        for (let keyboardShortcut_keys_buf_i = 0; keyboardShortcut_keys_buf_i < keyboardShortcut_keys_buf_length; keyboardShortcut_keys_buf_i++) {
            keyboardShortcut_keys_buf[keyboardShortcut_keys_buf_i] = (thisDeserializer.readInt32() as ModifierKey)
        }
        node.keyboardShortcut_keys = keyboardShortcut_keys_buf
        const keyboardShortcut_action_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let keyboardShortcut_action_buf: (() => void) | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (keyboardShortcut_action_buf_runtimeType))
        {
            keyboardShortcut_action_buf = thisDeserializer.readCallback_Void()
        }
        node.keyboardShortcut_action = keyboardShortcut_action_buf
    }
    _CommonShapeMethod_stroke(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonShapeMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const stroke_value_buf_selector: number = thisDeserializer.readInt8()
        let stroke_value_buf: Color | number | string | Resource | undefined|undefined 
        if (stroke_value_buf_selector == 0) {
            stroke_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (stroke_value_buf_selector == 1) {
            stroke_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (stroke_value_buf_selector == 2) {
            stroke_value_buf = (thisDeserializer.readString() as string)
        }
        else if (stroke_value_buf_selector == 3) {
            stroke_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for stroke_value_buf has to be chosen through deserialisation.")
        }
        node.stroke_value = (stroke_value_buf as Color | number | string | Resource)
    }
    _CommonShapeMethod_fill(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonShapeMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fill_value_buf_selector: number = thisDeserializer.readInt8()
        let fill_value_buf: Color | number | string | Resource | undefined|undefined 
        if (fill_value_buf_selector == 0) {
            fill_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (fill_value_buf_selector == 1) {
            fill_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fill_value_buf_selector == 2) {
            fill_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fill_value_buf_selector == 3) {
            fill_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fill_value_buf has to be chosen through deserialisation.")
        }
        node.fill_value = (fill_value_buf as Color | number | string | Resource)
    }
    _CommonShapeMethod_strokeDashOffset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonShapeMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const strokeDashOffset_value_buf_selector: number = thisDeserializer.readInt8()
        let strokeDashOffset_value_buf: number | string | undefined|undefined 
        if (strokeDashOffset_value_buf_selector == 0) {
            strokeDashOffset_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (strokeDashOffset_value_buf_selector == 1) {
            strokeDashOffset_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for strokeDashOffset_value_buf has to be chosen through deserialisation.")
        }
        node.strokeDashOffset_value = (strokeDashOffset_value_buf as number | string)
    }
    _CommonShapeMethod_strokeLineCap(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonShapeMethodInterface>(ptr)
        node.strokeLineCap_value = value
    }
    _CommonShapeMethod_strokeLineJoin(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonShapeMethodInterface>(ptr)
        node.strokeLineJoin_value = value
    }
    _CommonShapeMethod_strokeMiterLimit(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonShapeMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const strokeMiterLimit_value_buf_selector: number = thisDeserializer.readInt8()
        let strokeMiterLimit_value_buf: number | string | undefined|undefined 
        if (strokeMiterLimit_value_buf_selector == 0) {
            strokeMiterLimit_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (strokeMiterLimit_value_buf_selector == 1) {
            strokeMiterLimit_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for strokeMiterLimit_value_buf has to be chosen through deserialisation.")
        }
        node.strokeMiterLimit_value = (strokeMiterLimit_value_buf as number | string)
    }
    _CommonShapeMethod_strokeOpacity(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonShapeMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const strokeOpacity_value_buf_selector: number = thisDeserializer.readInt8()
        let strokeOpacity_value_buf: number | string | Resource | undefined|undefined 
        if (strokeOpacity_value_buf_selector == 0) {
            strokeOpacity_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (strokeOpacity_value_buf_selector == 1) {
            strokeOpacity_value_buf = (thisDeserializer.readString() as string)
        }
        else if (strokeOpacity_value_buf_selector == 2) {
            strokeOpacity_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for strokeOpacity_value_buf has to be chosen through deserialisation.")
        }
        node.strokeOpacity_value = (strokeOpacity_value_buf as number | string | Resource)
    }
    _CommonShapeMethod_fillOpacity(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonShapeMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fillOpacity_value_buf_selector: number = thisDeserializer.readInt8()
        let fillOpacity_value_buf: number | string | Resource | undefined|undefined 
        if (fillOpacity_value_buf_selector == 0) {
            fillOpacity_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fillOpacity_value_buf_selector == 1) {
            fillOpacity_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fillOpacity_value_buf_selector == 2) {
            fillOpacity_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fillOpacity_value_buf has to be chosen through deserialisation.")
        }
        node.fillOpacity_value = (fillOpacity_value_buf as number | string | Resource)
    }
    _CommonShapeMethod_strokeWidth(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<CommonShapeMethodInterface>(ptr)
        node.strokeWidth_value = value
    }
    _CommonShapeMethod_antiAlias(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CommonShapeMethodInterface>(ptr)
        node.antiAlias_value = value
    }
    _CommonShapeMethod_strokeDashArray(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CommonShapeMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const strokeDashArray_value_buf_length: int32 = thisDeserializer.readInt32()
        let strokeDashArray_value_buf: Array<any> = new Array<any>()
        for (let strokeDashArray_value_buf_i = 0; strokeDashArray_value_buf_i < strokeDashArray_value_buf_length; strokeDashArray_value_buf_i++) {
            strokeDashArray_value_buf[strokeDashArray_value_buf_i] = (thisDeserializer.readCustomObject("Any") as Object)
        }
        node.strokeDashArray_value = strokeDashArray_value_buf
    }
    _CommonInterface_setCommonOptions(ptr: KPointer): void {
        let node = this.ptr2object<CommonInterface>(ptr)
    }
    _ScrollableCommonMethod_scrollBar(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ScrollableCommonMethodInterface>(ptr)
        node.scrollBar_value = value
    }
    _ScrollableCommonMethod_scrollBarColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollableCommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const scrollBarColor_value_buf_selector: number = thisDeserializer.readInt8()
        let scrollBarColor_value_buf: Color | number | string | undefined|undefined 
        if (scrollBarColor_value_buf_selector == 0) {
            scrollBarColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (scrollBarColor_value_buf_selector == 1) {
            scrollBarColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (scrollBarColor_value_buf_selector == 2) {
            scrollBarColor_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for scrollBarColor_value_buf has to be chosen through deserialisation.")
        }
        node.scrollBarColor_value = (scrollBarColor_value_buf as Color | number | string)
    }
    _ScrollableCommonMethod_scrollBarWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollableCommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const scrollBarWidth_value_buf_selector: number = thisDeserializer.readInt8()
        let scrollBarWidth_value_buf: number | string | undefined|undefined 
        if (scrollBarWidth_value_buf_selector == 0) {
            scrollBarWidth_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (scrollBarWidth_value_buf_selector == 1) {
            scrollBarWidth_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for scrollBarWidth_value_buf has to be chosen through deserialisation.")
        }
        node.scrollBarWidth_value = (scrollBarWidth_value_buf as number | string)
    }
    _ScrollableCommonMethod_nestedScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollableCommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.nestedScroll_value = thisDeserializer.readNestedScrollOptions()
    }
    _ScrollableCommonMethod_enableScrollInteraction(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ScrollableCommonMethodInterface>(ptr)
        node.enableScrollInteraction_value = value
    }
    _ScrollableCommonMethod_friction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollableCommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const friction_value_buf_selector: number = thisDeserializer.readInt8()
        let friction_value_buf: number | Resource | undefined|undefined 
        if (friction_value_buf_selector == 0) {
            friction_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (friction_value_buf_selector == 1) {
            friction_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for friction_value_buf has to be chosen through deserialisation.")
        }
        node.friction_value = (friction_value_buf as number | Resource)
    }
    _ScrollableCommonMethod_onScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollableCommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScroll_value = thisDeserializer.readCallback_Number_ScrollState_Void()
    }
    _ScrollableCommonMethod_onWillScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollableCommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const onWillScroll_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let onWillScroll_value_buf: ScrollOnWillScrollCallback | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (onWillScroll_value_buf_runtimeType))
        {
            onWillScroll_value_buf = thisDeserializer.readScrollOnWillScrollCallback()
        }
        node.onWillScroll_value = onWillScroll_value_buf
    }
    _ScrollableCommonMethod_onDidScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollableCommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const onDidScroll_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let onDidScroll_value_buf: ScrollOnWillScrollCallback | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (onDidScroll_value_buf_runtimeType))
        {
            onDidScroll_value_buf = thisDeserializer.readScrollOnWillScrollCallback()
        }
        node.onDidScroll_value = onDidScroll_value_buf
    }
    _ScrollableCommonMethod_onReachStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollableCommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onReachStart_value = thisDeserializer.readCallback_Void()
    }
    _ScrollableCommonMethod_onReachEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollableCommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onReachEnd_value = thisDeserializer.readCallback_Void()
    }
    _ScrollableCommonMethod_onScrollStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollableCommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScrollStart_value = thisDeserializer.readCallback_Void()
    }
    _ScrollableCommonMethod_onScrollStop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollableCommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScrollStop_value = thisDeserializer.readCallback_Void()
    }
    _ScrollableCommonMethod_flingSpeedLimit(ptr: KPointer, value: number): void {
        let node = this.ptr2object<ScrollableCommonMethodInterface>(ptr)
        node.flingSpeedLimit_value = value
    }
    _ScrollableCommonMethod_clipContent(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollableCommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const clipContent_value_buf_selector: number = thisDeserializer.readInt8()
        let clipContent_value_buf: ContentClipMode | RectShape | undefined|undefined 
        if (clipContent_value_buf_selector == 0) {
            clipContent_value_buf = (thisDeserializer.readInt32() as ContentClipMode)
        }
        else if (clipContent_value_buf_selector == 1) {
            clipContent_value_buf = thisDeserializer.readRectShape()
        }
        else {
            throw new Error("One of the branches for clipContent_value_buf has to be chosen through deserialisation.")
        }
        node.clipContent_value = (clipContent_value_buf as ContentClipMode | RectShape)
    }
    _ScrollableCommonMethod_edgeEffect(ptr: KPointer, edgeEffect: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollableCommonMethodInterface>(ptr)
        node.edgeEffect_edgeEffect = edgeEffect
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const edgeEffect_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let edgeEffect_options_buf: EdgeEffectOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (edgeEffect_options_buf_runtimeType))
        {
            edgeEffect_options_buf = thisDeserializer.readEdgeEffectOptions()
        }
        node.edgeEffect_options = edgeEffect_options_buf
    }
    _ScrollableCommonMethod_fadingEdge(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollableCommonMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fadingEdge_enabled_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let fadingEdge_enabled_buf: boolean | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (fadingEdge_enabled_buf_runtimeType))
        {
            fadingEdge_enabled_buf = thisDeserializer.readBoolean()
        }
        node.fadingEdge_enabled = fadingEdge_enabled_buf
        const fadingEdge_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let fadingEdge_options_buf: FadingEdgeOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (fadingEdge_options_buf_runtimeType))
        {
            fadingEdge_options_buf = thisDeserializer.readFadingEdgeOptions()
        }
        node.fadingEdge_options = fadingEdge_options_buf
    }
    _Component3DInterface_setComponent3DOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<Component3DInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setComponent3DOptions_sceneOptions_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setComponent3DOptions_sceneOptions_buf: SceneOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setComponent3DOptions_sceneOptions_buf_runtimeType))
        {
            setComponent3DOptions_sceneOptions_buf = thisDeserializer.readSceneOptions()
        }
        node.setComponent3DOptions_sceneOptions = setComponent3DOptions_sceneOptions_buf
    }
    _Component3DAttribute_environment(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<Component3DInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const environment_value_buf_selector: number = thisDeserializer.readInt8()
        let environment_value_buf: string | Resource | undefined|undefined 
        if (environment_value_buf_selector == 0) {
            environment_value_buf = (thisDeserializer.readString() as string)
        }
        else if (environment_value_buf_selector == 1) {
            environment_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for environment_value_buf has to be chosen through deserialisation.")
        }
        node.environment_value = (environment_value_buf as string | Resource)
    }
    _Component3DAttribute_shader(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<Component3DInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const shader_value_buf_selector: number = thisDeserializer.readInt8()
        let shader_value_buf: string | Resource | undefined|undefined 
        if (shader_value_buf_selector == 0) {
            shader_value_buf = (thisDeserializer.readString() as string)
        }
        else if (shader_value_buf_selector == 1) {
            shader_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for shader_value_buf has to be chosen through deserialisation.")
        }
        node.shader_value = (shader_value_buf as string | Resource)
    }
    _Component3DAttribute_shaderImageTexture(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<Component3DInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const shaderImageTexture_value_buf_selector: number = thisDeserializer.readInt8()
        let shaderImageTexture_value_buf: string | Resource | undefined|undefined 
        if (shaderImageTexture_value_buf_selector == 0) {
            shaderImageTexture_value_buf = (thisDeserializer.readString() as string)
        }
        else if (shaderImageTexture_value_buf_selector == 1) {
            shaderImageTexture_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for shaderImageTexture_value_buf has to be chosen through deserialisation.")
        }
        node.shaderImageTexture_value = (shaderImageTexture_value_buf as string | Resource)
    }
    _Component3DAttribute_shaderInputBuffer(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<Component3DInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const shaderInputBuffer_value_buf_length: int32 = thisDeserializer.readInt32()
        let shaderInputBuffer_value_buf: Array<number> = new Array<number>()
        for (let shaderInputBuffer_value_buf_i = 0; shaderInputBuffer_value_buf_i < shaderInputBuffer_value_buf_length; shaderInputBuffer_value_buf_i++) {
            shaderInputBuffer_value_buf[shaderInputBuffer_value_buf_i] = (thisDeserializer.readNumber() as number)
        }
        node.shaderInputBuffer_value = shaderInputBuffer_value_buf
    }
    _Component3DAttribute_renderWidth(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<Component3DInterface>(ptr)
        node.renderWidth_value = value
    }
    _Component3DAttribute_renderHeight(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<Component3DInterface>(ptr)
        node.renderHeight_value = value
    }
    _Component3DAttribute_customRender(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, selfRenderUpdate: KInt): void {
        let node = this.ptr2object<Component3DInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const customRender_uri_buf_selector: number = thisDeserializer.readInt8()
        let customRender_uri_buf: string | Resource | undefined|undefined 
        if (customRender_uri_buf_selector == 0) {
            customRender_uri_buf = (thisDeserializer.readString() as string)
        }
        else if (customRender_uri_buf_selector == 1) {
            customRender_uri_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for customRender_uri_buf has to be chosen through deserialisation.")
        }
        node.customRender_uri = (customRender_uri_buf as string | Resource)
        node.customRender_selfRenderUpdate = thisLength
    }
    _ContainerSpanInterface_setContainerSpanOptions(ptr: KPointer): void {
        let node = this.ptr2object<ContainerSpanInterface>(ptr)
    }
    _ContainerSpanAttribute_textBackgroundStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ContainerSpanInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.textBackgroundStyle_value = thisDeserializer.readTextBackgroundStyle()
    }
    _CounterInterface_setCounterOptions(ptr: KPointer): void {
        let node = this.ptr2object<CounterInterface>(ptr)
    }
    _CounterAttribute_onInc(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CounterInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onInc_value = thisDeserializer.readVoidCallback()
    }
    _CounterAttribute_onDec(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<CounterInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDec_value = thisDeserializer.readVoidCallback()
    }
    _CounterAttribute_enableDec(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CounterInterface>(ptr)
        node.enableDec_value = value
    }
    _CounterAttribute_enableInc(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<CounterInterface>(ptr)
        node.enableInc_value = value
    }
    _DataPanelInterface_setDataPanelOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<DataPanelInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setDataPanelOptions_options = thisDeserializer.readDataPanelOptions()
    }
    _DataPanelAttribute_closeEffect(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<DataPanelInterface>(ptr)
        node.closeEffect_value = value
    }
    _DataPanelAttribute_valueColors(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<DataPanelInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const valueColors_value_buf_length: int32 = thisDeserializer.readInt32()
        let valueColors_value_buf: Array<ResourceColor | LinearGradient_data_panel> = new Array<ResourceColor | LinearGradient_data_panel>()
        for (let valueColors_value_buf_i = 0; valueColors_value_buf_i < valueColors_value_buf_length; valueColors_value_buf_i++) {
            const valueColors_value_buf_buf_selector: number = thisDeserializer.readInt8()
            let valueColors_value_buf_buf: ResourceColor | LinearGradient_data_panel | undefined|undefined 
            if (valueColors_value_buf_buf_selector == 0) {
                const valueColors_value_buf_buf_u_selector: number = thisDeserializer.readInt8()
                let valueColors_value_buf_buf_u: Color | number | string | Resource | undefined|undefined 
                if (valueColors_value_buf_buf_u_selector == 0) {
                    valueColors_value_buf_buf_u = (thisDeserializer.readInt32() as Color)
                }
                else if (valueColors_value_buf_buf_u_selector == 1) {
                    valueColors_value_buf_buf_u = (thisDeserializer.readNumber() as number)
                }
                else if (valueColors_value_buf_buf_u_selector == 2) {
                    valueColors_value_buf_buf_u = (thisDeserializer.readString() as string)
                }
                else if (valueColors_value_buf_buf_u_selector == 3) {
                    valueColors_value_buf_buf_u = thisDeserializer.readResource()
                }
                else {
                    throw new Error("One of the branches for valueColors_value_buf_buf_u has to be chosen through deserialisation.")
                }
                valueColors_value_buf_buf = (valueColors_value_buf_buf_u as Color | number | string | Resource)
            }
            else if (valueColors_value_buf_buf_selector == 1) {
                valueColors_value_buf_buf = thisDeserializer.readLinearGradient_data_panel()
            }
            else {
                throw new Error("One of the branches for valueColors_value_buf_buf has to be chosen through deserialisation.")
            }
            valueColors_value_buf[valueColors_value_buf_i] = (valueColors_value_buf_buf as ResourceColor | LinearGradient_data_panel)
        }
        node.valueColors_value = valueColors_value_buf
    }
    _DataPanelAttribute_trackBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<DataPanelInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const trackBackgroundColor_value_buf_selector: number = thisDeserializer.readInt8()
        let trackBackgroundColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (trackBackgroundColor_value_buf_selector == 0) {
            trackBackgroundColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (trackBackgroundColor_value_buf_selector == 1) {
            trackBackgroundColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (trackBackgroundColor_value_buf_selector == 2) {
            trackBackgroundColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (trackBackgroundColor_value_buf_selector == 3) {
            trackBackgroundColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for trackBackgroundColor_value_buf has to be chosen through deserialisation.")
        }
        node.trackBackgroundColor_value = (trackBackgroundColor_value_buf as Color | number | string | Resource)
    }
    _DataPanelAttribute_strokeWidth(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<DataPanelInterface>(ptr)
        node.strokeWidth_value = value
    }
    _DataPanelAttribute_trackShadow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<DataPanelInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.trackShadow_value = thisDeserializer.readDataPanelShadowOptions()
    }
    _DataPanelAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<DataPanelInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.contentModifier_value = (thisDeserializer.readCustomObject("ContentModifier") as ContentModifier<any>)
    }
    _DatePickerInterface_setDatePickerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<DatePickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setDatePickerOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setDatePickerOptions_options_buf: DatePickerOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setDatePickerOptions_options_buf_runtimeType))
        {
            setDatePickerOptions_options_buf = thisDeserializer.readDatePickerOptions()
        }
        node.setDatePickerOptions_options = setDatePickerOptions_options_buf
    }
    _DatePickerAttribute_lunar(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<DatePickerInterface>(ptr)
        node.lunar_value = value
    }
    _DatePickerAttribute_disappearTextStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<DatePickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.disappearTextStyle_value = thisDeserializer.readPickerTextStyle()
    }
    _DatePickerAttribute_textStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<DatePickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.textStyle_value = thisDeserializer.readPickerTextStyle()
    }
    _DatePickerAttribute_selectedTextStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<DatePickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.selectedTextStyle_value = thisDeserializer.readPickerTextStyle()
    }
    _DatePickerAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<DatePickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onChange_value = thisDeserializer.readCallback_DatePickerResult_Void()
    }
    _DatePickerAttribute_onDateChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<DatePickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDateChange_value = thisDeserializer.readCallback_Date_Void()
    }
    _DividerInterface_setDividerOptions(ptr: KPointer): void {
        let node = this.ptr2object<DividerInterface>(ptr)
    }
    _DividerAttribute_vertical(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<DividerInterface>(ptr)
        node.vertical_value = value
    }
    _DividerAttribute_color(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<DividerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const color_value_buf_selector: number = thisDeserializer.readInt8()
        let color_value_buf: Color | number | string | Resource | undefined|undefined 
        if (color_value_buf_selector == 0) {
            color_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (color_value_buf_selector == 1) {
            color_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (color_value_buf_selector == 2) {
            color_value_buf = (thisDeserializer.readString() as string)
        }
        else if (color_value_buf_selector == 3) {
            color_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for color_value_buf has to be chosen through deserialisation.")
        }
        node.color_value = (color_value_buf as Color | number | string | Resource)
    }
    _DividerAttribute_strokeWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<DividerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const strokeWidth_value_buf_selector: number = thisDeserializer.readInt8()
        let strokeWidth_value_buf: number | string | undefined|undefined 
        if (strokeWidth_value_buf_selector == 0) {
            strokeWidth_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (strokeWidth_value_buf_selector == 1) {
            strokeWidth_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for strokeWidth_value_buf has to be chosen through deserialisation.")
        }
        node.strokeWidth_value = (strokeWidth_value_buf as number | string)
    }
    _DividerAttribute_lineCap(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<DividerInterface>(ptr)
        node.lineCap_value = value
    }
    _EffectComponentInterface_setEffectComponentOptions(ptr: KPointer): void {
        let node = this.ptr2object<EffectComponentInterface>(ptr)
    }
    _EllipseInterface_setEllipseOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<EllipseInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setEllipseOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setEllipseOptions_options_buf: EllipseOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setEllipseOptions_options_buf_runtimeType))
        {
            setEllipseOptions_options_buf = thisDeserializer.readEllipseOptions()
        }
        node.setEllipseOptions_options = setEllipseOptions_options_buf
    }
    _EmbeddedComponentInterface_setEmbeddedComponentOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, type: KInt): void {
        let node = this.ptr2object<EmbeddedComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setEmbeddedComponentOptions_loader = thisDeserializer.readWant()
        node.setEmbeddedComponentOptions_type = thisLength
    }
    _EmbeddedComponentAttribute_onTerminated(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<EmbeddedComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onTerminated_value = thisDeserializer.readCallback_TerminationInfo_Void()
    }
    _EmbeddedComponentAttribute_onError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<EmbeddedComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onError_value = thisDeserializer.readCustomObject("ErrorCallback")
    }
    _FlexInterface_setFlexOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<FlexInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setFlexOptions_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setFlexOptions_value_buf: FlexOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setFlexOptions_value_buf_runtimeType))
        {
            setFlexOptions_value_buf = thisDeserializer.readFlexOptions()
        }
        node.setFlexOptions_value = setFlexOptions_value_buf
    }
    _FlexAttribute_pointLight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<FlexInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.pointLight_value = thisDeserializer.readPointLightStyle()
    }
    _FlowItemInterface_setFlowItemOptions(ptr: KPointer): void {
        let node = this.ptr2object<FlowItemInterface>(ptr)
    }
    _FolderStackInterface_setFolderStackOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<FolderStackInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setFolderStackOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setFolderStackOptions_options_buf: FolderStackOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setFolderStackOptions_options_buf_runtimeType))
        {
            setFolderStackOptions_options_buf = thisDeserializer.readFolderStackOptions()
        }
        node.setFolderStackOptions_options = setFolderStackOptions_options_buf
    }
    _FolderStackAttribute_alignContent(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<FolderStackInterface>(ptr)
        node.alignContent_value = value
    }
    _FolderStackAttribute_onFolderStateChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<FolderStackInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onFolderStateChange_value = thisDeserializer.readOnFoldStatusChangeCallback()
    }
    _FolderStackAttribute_onHoverStatusChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<FolderStackInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onHoverStatusChange_value = thisDeserializer.readOnHoverStatusChangeCallback()
    }
    _FolderStackAttribute_enableAnimation(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<FolderStackInterface>(ptr)
        node.enableAnimation_value = value
    }
    _FolderStackAttribute_autoHalfFold(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<FolderStackInterface>(ptr)
        node.autoHalfFold_value = value
    }
    _FormComponentInterface_setFormComponentOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<FormComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setFormComponentOptions_value = thisDeserializer.readFormInfo()
    }
    _FormComponentAttribute_size(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<FormComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.size_value = thisDeserializer.readSizeOptions()
    }
    _FormComponentAttribute_moduleName(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<FormComponentInterface>(ptr)
        node.moduleName_value = value
    }
    _FormComponentAttribute_dimension(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<FormComponentInterface>(ptr)
        node.dimension_value = value
    }
    _FormComponentAttribute_allowUpdate(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<FormComponentInterface>(ptr)
        node.allowUpdate_value = value
    }
    _FormComponentAttribute_visibility(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<FormComponentInterface>(ptr)
        node.visibility_value = value
    }
    _FormComponentAttribute_onAcquired(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<FormComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onAcquired_value = thisDeserializer.readCallback_FormCallbackInfo_Void()
    }
    _FormComponentAttribute_onError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<FormComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onError_value = thisDeserializer.readCallback_Literal_Number_errcode_String_msg_Void()
    }
    _FormComponentAttribute_onRouter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<FormComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onRouter_value = thisDeserializer.readCallback_Any_Void()
    }
    _FormComponentAttribute_onUninstall(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<FormComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onUninstall_value = thisDeserializer.readCallback_FormCallbackInfo_Void()
    }
    _FormComponentAttribute_onLoad(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<FormComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onLoad_value = thisDeserializer.readCallback_Void()
    }
    _FormLinkInterface_setFormLinkOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<FormLinkInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setFormLinkOptions_options = thisDeserializer.readFormLinkOptions()
    }
    _GaugeInterface_setGaugeOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GaugeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setGaugeOptions_options = thisDeserializer.readGaugeOptions()
    }
    _GaugeAttribute_value(ptr: KPointer, value: number): void {
        let node = this.ptr2object<GaugeInterface>(ptr)
        node.value_value = value
    }
    _GaugeAttribute_startAngle(ptr: KPointer, value: number): void {
        let node = this.ptr2object<GaugeInterface>(ptr)
        node.startAngle_value = value
    }
    _GaugeAttribute_endAngle(ptr: KPointer, value: number): void {
        let node = this.ptr2object<GaugeInterface>(ptr)
        node.endAngle_value = value
    }
    _GaugeAttribute_colors(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GaugeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const colors_value_buf_selector: number = thisDeserializer.readInt8()
        let colors_value_buf: ResourceColor | LinearGradient_common | Array<[ ResourceColor | LinearGradient_common, number ]> | undefined|undefined 
        if (colors_value_buf_selector == 0) {
            const colors_value_buf_u_selector: number = thisDeserializer.readInt8()
            let colors_value_buf_u: Color | number | string | Resource | undefined|undefined 
            if (colors_value_buf_u_selector == 0) {
                colors_value_buf_u = (thisDeserializer.readInt32() as Color)
            }
            else if (colors_value_buf_u_selector == 1) {
                colors_value_buf_u = (thisDeserializer.readNumber() as number)
            }
            else if (colors_value_buf_u_selector == 2) {
                colors_value_buf_u = (thisDeserializer.readString() as string)
            }
            else if (colors_value_buf_u_selector == 3) {
                colors_value_buf_u = thisDeserializer.readResource()
            }
            else {
                throw new Error("One of the branches for colors_value_buf_u has to be chosen through deserialisation.")
            }
            colors_value_buf = (colors_value_buf_u as Color | number | string | Resource)
        }
        else if (colors_value_buf_selector == 1) {
            colors_value_buf = thisDeserializer.readLinearGradient_common()
        }
        else if (colors_value_buf_selector == 2) {
            const colors_value_buf_u_length: int32 = thisDeserializer.readInt32()
            let colors_value_buf_u: Array<[ ResourceColor | LinearGradient_common, number ]> = new Array<[ ResourceColor | LinearGradient_common, number ]>()
            for (let colors_value_buf_u_i = 0; colors_value_buf_u_i < colors_value_buf_u_length; colors_value_buf_u_i++) {
                const colors_value_buf_u_buf_value0_buf_selector: number = thisDeserializer.readInt8()
                let colors_value_buf_u_buf_value0_buf: ResourceColor | LinearGradient_common | undefined|undefined 
                if (colors_value_buf_u_buf_value0_buf_selector == 0) {
                    const colors_value_buf_u_buf_value0_buf_u_selector: number = thisDeserializer.readInt8()
                    let colors_value_buf_u_buf_value0_buf_u: Color | number | string | Resource | undefined|undefined 
                    if (colors_value_buf_u_buf_value0_buf_u_selector == 0) {
                        colors_value_buf_u_buf_value0_buf_u = (thisDeserializer.readInt32() as Color)
                    }
                    else if (colors_value_buf_u_buf_value0_buf_u_selector == 1) {
                        colors_value_buf_u_buf_value0_buf_u = (thisDeserializer.readNumber() as number)
                    }
                    else if (colors_value_buf_u_buf_value0_buf_u_selector == 2) {
                        colors_value_buf_u_buf_value0_buf_u = (thisDeserializer.readString() as string)
                    }
                    else if (colors_value_buf_u_buf_value0_buf_u_selector == 3) {
                        colors_value_buf_u_buf_value0_buf_u = thisDeserializer.readResource()
                    }
                    else {
                        throw new Error("One of the branches for colors_value_buf_u_buf_value0_buf_u has to be chosen through deserialisation.")
                    }
                    colors_value_buf_u_buf_value0_buf = (colors_value_buf_u_buf_value0_buf_u as Color | number | string | Resource)
                }
                else if (colors_value_buf_u_buf_value0_buf_selector == 1) {
                    colors_value_buf_u_buf_value0_buf = thisDeserializer.readLinearGradient_common()
                }
                else {
                    throw new Error("One of the branches for colors_value_buf_u_buf_value0_buf has to be chosen through deserialisation.")
                }
                const colors_value_buf_u_buf_value0: ResourceColor | LinearGradient_common = (colors_value_buf_u_buf_value0_buf as ResourceColor | LinearGradient_common)
                const colors_value_buf_u_buf_value1: number = (thisDeserializer.readNumber() as number)
                colors_value_buf_u[colors_value_buf_u_i] = ([colors_value_buf_u_buf_value0, colors_value_buf_u_buf_value1] as [ ResourceColor | LinearGradient_common, number ])
            }
            colors_value_buf = colors_value_buf_u
        }
        else {
            throw new Error("One of the branches for colors_value_buf has to be chosen through deserialisation.")
        }
        node.colors_value = (colors_value_buf as ResourceColor | LinearGradient_common | Array<[ ResourceColor | LinearGradient_common, number ]>)
    }
    _GaugeAttribute_strokeWidth(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<GaugeInterface>(ptr)
        node.strokeWidth_value = value
    }
    _GaugeAttribute_description(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GaugeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.description_value = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
    }
    _GaugeAttribute_trackShadow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GaugeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.trackShadow_value = thisDeserializer.readGaugeShadowOptions()
    }
    _GaugeAttribute_indicator(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GaugeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.indicator_value = thisDeserializer.readGaugeIndicatorOptions()
    }
    _GaugeAttribute_privacySensitive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GaugeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const privacySensitive_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let privacySensitive_value_buf: boolean | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (privacySensitive_value_buf_runtimeType))
        {
            privacySensitive_value_buf = thisDeserializer.readBoolean()
        }
        node.privacySensitive_value = privacySensitive_value_buf
    }
    _GaugeAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GaugeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.contentModifier_value = (thisDeserializer.readCustomObject("ContentModifier") as ContentModifier<any>)
    }
    _GridInterface_setGridOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setGridOptions_scroller_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setGridOptions_scroller_buf: Scroller | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setGridOptions_scroller_buf_runtimeType))
        {
            setGridOptions_scroller_buf = (thisDeserializer.readScroller() as Scroller)
        }
        node.setGridOptions_scroller = setGridOptions_scroller_buf
        const setGridOptions_layoutOptions_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setGridOptions_layoutOptions_buf: GridLayoutOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setGridOptions_layoutOptions_buf_runtimeType))
        {
            setGridOptions_layoutOptions_buf = thisDeserializer.readGridLayoutOptions()
        }
        node.setGridOptions_layoutOptions = setGridOptions_layoutOptions_buf
    }
    _GridAttribute_columnsTemplate(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<GridInterface>(ptr)
        node.columnsTemplate_value = value
    }
    _GridAttribute_rowsTemplate(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<GridInterface>(ptr)
        node.rowsTemplate_value = value
    }
    _GridAttribute_columnsGap(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<GridInterface>(ptr)
        node.columnsGap_value = value
    }
    _GridAttribute_rowsGap(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<GridInterface>(ptr)
        node.rowsGap_value = value
    }
    _GridAttribute_scrollBarWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const scrollBarWidth_value_buf_selector: number = thisDeserializer.readInt8()
        let scrollBarWidth_value_buf: number | string | undefined|undefined 
        if (scrollBarWidth_value_buf_selector == 0) {
            scrollBarWidth_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (scrollBarWidth_value_buf_selector == 1) {
            scrollBarWidth_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for scrollBarWidth_value_buf has to be chosen through deserialisation.")
        }
        node.scrollBarWidth_value = (scrollBarWidth_value_buf as number | string)
    }
    _GridAttribute_scrollBarColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const scrollBarColor_value_buf_selector: number = thisDeserializer.readInt8()
        let scrollBarColor_value_buf: Color | number | string | undefined|undefined 
        if (scrollBarColor_value_buf_selector == 0) {
            scrollBarColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (scrollBarColor_value_buf_selector == 1) {
            scrollBarColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (scrollBarColor_value_buf_selector == 2) {
            scrollBarColor_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for scrollBarColor_value_buf has to be chosen through deserialisation.")
        }
        node.scrollBarColor_value = (scrollBarColor_value_buf as Color | number | string)
    }
    _GridAttribute_scrollBar(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<GridInterface>(ptr)
        node.scrollBar_value = value
    }
    _GridAttribute_onScrollBarUpdate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScrollBarUpdate_value = thisDeserializer.readCallback_Number_Number_ComputedBarAttribute()
    }
    _GridAttribute_onScrollIndex(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScrollIndex_value = thisDeserializer.readCallback_Number_Number_Void()
    }
    _GridAttribute_cachedCount0(ptr: KPointer, value: number): void {
        let node = this.ptr2object<GridInterface>(ptr)
        node.cachedCount0_value = value
    }
    _GridAttribute_cachedCount1(ptr: KPointer, count: number, show: KInt): void {
        let node = this.ptr2object<GridInterface>(ptr)
        node.cachedCount1_count = count
        node.cachedCount1_show = show
    }
    _GridAttribute_editMode(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<GridInterface>(ptr)
        node.editMode_value = value
    }
    _GridAttribute_multiSelectable(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<GridInterface>(ptr)
        node.multiSelectable_value = value
    }
    _GridAttribute_maxCount(ptr: KPointer, value: number): void {
        let node = this.ptr2object<GridInterface>(ptr)
        node.maxCount_value = value
    }
    _GridAttribute_minCount(ptr: KPointer, value: number): void {
        let node = this.ptr2object<GridInterface>(ptr)
        node.minCount_value = value
    }
    _GridAttribute_cellLength(ptr: KPointer, value: number): void {
        let node = this.ptr2object<GridInterface>(ptr)
        node.cellLength_value = value
    }
    _GridAttribute_layoutDirection(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<GridInterface>(ptr)
        node.layoutDirection_value = value
    }
    _GridAttribute_supportAnimation(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<GridInterface>(ptr)
        node.supportAnimation_value = value
    }
    _GridAttribute_onItemDragStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onItemDragStart_value = thisDeserializer.readCallback_ItemDragInfo_Number_Callback_Any()
    }
    _GridAttribute_onItemDragEnter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onItemDragEnter_value = thisDeserializer.readCallback_ItemDragInfo_Void()
    }
    _GridAttribute_onItemDragMove(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onItemDragMove_value = thisDeserializer.readCallback_ItemDragInfo_Number_Number_Void()
    }
    _GridAttribute_onItemDragLeave(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onItemDragLeave_value = thisDeserializer.readCallback_ItemDragInfo_Number_Void()
    }
    _GridAttribute_onItemDrop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onItemDrop_value = thisDeserializer.readCallback_ItemDragInfo_Number_Number_Boolean_Void()
    }
    _GridAttribute_nestedScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.nestedScroll_value = thisDeserializer.readNestedScrollOptions()
    }
    _GridAttribute_enableScrollInteraction(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<GridInterface>(ptr)
        node.enableScrollInteraction_value = value
    }
    _GridAttribute_friction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const friction_value_buf_selector: number = thisDeserializer.readInt8()
        let friction_value_buf: number | Resource | undefined|undefined 
        if (friction_value_buf_selector == 0) {
            friction_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (friction_value_buf_selector == 1) {
            friction_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for friction_value_buf has to be chosen through deserialisation.")
        }
        node.friction_value = (friction_value_buf as number | Resource)
    }
    _GridAttribute_alignItems(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const alignItems_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let alignItems_value_buf: GridItemAlignment | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (alignItems_value_buf_runtimeType))
        {
            alignItems_value_buf = (thisDeserializer.readInt32() as GridItemAlignment)
        }
        node.alignItems_value = alignItems_value_buf
    }
    _GridAttribute_onScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScroll_value = thisDeserializer.readCallback_Number_ScrollState_Void()
    }
    _GridAttribute_onReachStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onReachStart_value = thisDeserializer.readCallback_Void()
    }
    _GridAttribute_onReachEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onReachEnd_value = thisDeserializer.readCallback_Void()
    }
    _GridAttribute_onScrollStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScrollStart_value = thisDeserializer.readCallback_Void()
    }
    _GridAttribute_onScrollStop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScrollStop_value = thisDeserializer.readCallback_Void()
    }
    _GridAttribute_onScrollFrameBegin(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScrollFrameBegin_value = thisDeserializer.readCallback_Number_ScrollState_Literal_Number_offsetRemain()
    }
    _GridAttribute_edgeEffect(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridInterface>(ptr)
        node.edgeEffect_value = value
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const edgeEffect_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let edgeEffect_options_buf: EdgeEffectOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (edgeEffect_options_buf_runtimeType))
        {
            edgeEffect_options_buf = thisDeserializer.readEdgeEffectOptions()
        }
        node.edgeEffect_options = edgeEffect_options_buf
    }
    _GridItemInterface_setGridItemOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridItemInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setGridItemOptions_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setGridItemOptions_value_buf: GridItemOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setGridItemOptions_value_buf_runtimeType))
        {
            setGridItemOptions_value_buf = thisDeserializer.readGridItemOptions()
        }
        node.setGridItemOptions_value = setGridItemOptions_value_buf
    }
    _GridItemAttribute_rowStart(ptr: KPointer, value: number): void {
        let node = this.ptr2object<GridItemInterface>(ptr)
        node.rowStart_value = value
    }
    _GridItemAttribute_rowEnd(ptr: KPointer, value: number): void {
        let node = this.ptr2object<GridItemInterface>(ptr)
        node.rowEnd_value = value
    }
    _GridItemAttribute_columnStart(ptr: KPointer, value: number): void {
        let node = this.ptr2object<GridItemInterface>(ptr)
        node.columnStart_value = value
    }
    _GridItemAttribute_columnEnd(ptr: KPointer, value: number): void {
        let node = this.ptr2object<GridItemInterface>(ptr)
        node.columnEnd_value = value
    }
    _GridItemAttribute_forceRebuild(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<GridItemInterface>(ptr)
        node.forceRebuild_value = value
    }
    _GridItemAttribute_selectable(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<GridItemInterface>(ptr)
        node.selectable_value = value
    }
    _GridItemAttribute_selected(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<GridItemInterface>(ptr)
        node.selected_value = value
    }
    _GridItemAttribute_onSelect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridItemInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSelect_value = thisDeserializer.readCallback_Boolean_Void()
    }
    _GridColInterface_setGridColOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridColInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setGridColOptions_option_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setGridColOptions_option_buf: GridColOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setGridColOptions_option_buf_runtimeType))
        {
            setGridColOptions_option_buf = thisDeserializer.readGridColOptions()
        }
        node.setGridColOptions_option = setGridColOptions_option_buf
    }
    _GridColAttribute_span(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridColInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const span_value_buf_selector: number = thisDeserializer.readInt8()
        let span_value_buf: number | GridColColumnOption | undefined|undefined 
        if (span_value_buf_selector == 0) {
            span_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (span_value_buf_selector == 1) {
            span_value_buf = thisDeserializer.readGridColColumnOption()
        }
        else {
            throw new Error("One of the branches for span_value_buf has to be chosen through deserialisation.")
        }
        node.span_value = (span_value_buf as number | GridColColumnOption)
    }
    _GridColAttribute_gridColOffset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridColInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const gridColOffset_value_buf_selector: number = thisDeserializer.readInt8()
        let gridColOffset_value_buf: number | GridColColumnOption | undefined|undefined 
        if (gridColOffset_value_buf_selector == 0) {
            gridColOffset_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (gridColOffset_value_buf_selector == 1) {
            gridColOffset_value_buf = thisDeserializer.readGridColColumnOption()
        }
        else {
            throw new Error("One of the branches for gridColOffset_value_buf has to be chosen through deserialisation.")
        }
        node.gridColOffset_value = (gridColOffset_value_buf as number | GridColColumnOption)
    }
    _GridColAttribute_order(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridColInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const order_value_buf_selector: number = thisDeserializer.readInt8()
        let order_value_buf: number | GridColColumnOption | undefined|undefined 
        if (order_value_buf_selector == 0) {
            order_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (order_value_buf_selector == 1) {
            order_value_buf = thisDeserializer.readGridColColumnOption()
        }
        else {
            throw new Error("One of the branches for order_value_buf has to be chosen through deserialisation.")
        }
        node.order_value = (order_value_buf as number | GridColColumnOption)
    }
    _GridContainerInterface_setGridContainerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridContainerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setGridContainerOptions_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setGridContainerOptions_value_buf: GridContainerOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setGridContainerOptions_value_buf_runtimeType))
        {
            setGridContainerOptions_value_buf = thisDeserializer.readGridContainerOptions()
        }
        node.setGridContainerOptions_value = setGridContainerOptions_value_buf
    }
    _GridRowInterface_setGridRowOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridRowInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setGridRowOptions_option_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setGridRowOptions_option_buf: GridRowOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setGridRowOptions_option_buf_runtimeType))
        {
            setGridRowOptions_option_buf = thisDeserializer.readGridRowOptions()
        }
        node.setGridRowOptions_option = setGridRowOptions_option_buf
    }
    _GridRowAttribute_onBreakpointChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<GridRowInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onBreakpointChange_value = thisDeserializer.readCallback_String_Void()
    }
    _GridRowAttribute_alignItems(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<GridRowInterface>(ptr)
        node.alignItems_value = value
    }
    _HyperlinkInterface_setHyperlinkOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<HyperlinkInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setHyperlinkOptions_address_buf_selector: number = thisDeserializer.readInt8()
        let setHyperlinkOptions_address_buf: string | Resource | undefined|undefined 
        if (setHyperlinkOptions_address_buf_selector == 0) {
            setHyperlinkOptions_address_buf = (thisDeserializer.readString() as string)
        }
        else if (setHyperlinkOptions_address_buf_selector == 1) {
            setHyperlinkOptions_address_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for setHyperlinkOptions_address_buf has to be chosen through deserialisation.")
        }
        node.setHyperlinkOptions_address = (setHyperlinkOptions_address_buf as string | Resource)
        const setHyperlinkOptions_content_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setHyperlinkOptions_content_buf: string | Resource | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setHyperlinkOptions_content_buf_runtimeType))
        {
            const setHyperlinkOptions_content_buf__selector: number = thisDeserializer.readInt8()
            let setHyperlinkOptions_content_buf_: string | Resource | undefined|undefined 
            if (setHyperlinkOptions_content_buf__selector == 0) {
                setHyperlinkOptions_content_buf_ = (thisDeserializer.readString() as string)
            }
            else if (setHyperlinkOptions_content_buf__selector == 1) {
                setHyperlinkOptions_content_buf_ = thisDeserializer.readResource()
            }
            else {
                throw new Error("One of the branches for setHyperlinkOptions_content_buf_ has to be chosen through deserialisation.")
            }
            setHyperlinkOptions_content_buf = (setHyperlinkOptions_content_buf_ as string | Resource)
        }
        node.setHyperlinkOptions_content = setHyperlinkOptions_content_buf
    }
    _HyperlinkAttribute_color(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<HyperlinkInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const color_value_buf_selector: number = thisDeserializer.readInt8()
        let color_value_buf: Color | number | string | Resource | undefined|undefined 
        if (color_value_buf_selector == 0) {
            color_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (color_value_buf_selector == 1) {
            color_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (color_value_buf_selector == 2) {
            color_value_buf = (thisDeserializer.readString() as string)
        }
        else if (color_value_buf_selector == 3) {
            color_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for color_value_buf has to be chosen through deserialisation.")
        }
        node.color_value = (color_value_buf as Color | number | string | Resource)
    }
    _ImageInterface_setImageOptions0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setImageOptions0_src_buf_selector: number = thisDeserializer.readInt8()
        let setImageOptions0_src_buf: PixelMap | ResourceStr | DrawableDescriptor | undefined|undefined 
        if (setImageOptions0_src_buf_selector == 0) {
            setImageOptions0_src_buf = (thisDeserializer.readPixelMap() as PixelMap)
        }
        else if (setImageOptions0_src_buf_selector == 1) {
            const setImageOptions0_src_buf_u_selector: number = thisDeserializer.readInt8()
            let setImageOptions0_src_buf_u: string | Resource | undefined|undefined 
            if (setImageOptions0_src_buf_u_selector == 0) {
                setImageOptions0_src_buf_u = (thisDeserializer.readString() as string)
            }
            else if (setImageOptions0_src_buf_u_selector == 1) {
                setImageOptions0_src_buf_u = thisDeserializer.readResource()
            }
            else {
                throw new Error("One of the branches for setImageOptions0_src_buf_u has to be chosen through deserialisation.")
            }
            setImageOptions0_src_buf = (setImageOptions0_src_buf_u as string | Resource)
        }
        else if (setImageOptions0_src_buf_selector == 2) {
            setImageOptions0_src_buf = thisDeserializer.readDrawableDescriptor()
        }
        else {
            throw new Error("One of the branches for setImageOptions0_src_buf has to be chosen through deserialisation.")
        }
        node.setImageOptions0_src = (setImageOptions0_src_buf as PixelMap | ResourceStr | DrawableDescriptor)
    }
    _ImageInterface_setImageOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setImageOptions1_src_buf_selector: number = thisDeserializer.readInt8()
        let setImageOptions1_src_buf: PixelMap | ResourceStr | DrawableDescriptor | ImageContent | undefined|undefined 
        if (setImageOptions1_src_buf_selector == 0) {
            setImageOptions1_src_buf = (thisDeserializer.readPixelMap() as PixelMap)
        }
        else if (setImageOptions1_src_buf_selector == 1) {
            const setImageOptions1_src_buf_u_selector: number = thisDeserializer.readInt8()
            let setImageOptions1_src_buf_u: string | Resource | undefined|undefined 
            if (setImageOptions1_src_buf_u_selector == 0) {
                setImageOptions1_src_buf_u = (thisDeserializer.readString() as string)
            }
            else if (setImageOptions1_src_buf_u_selector == 1) {
                setImageOptions1_src_buf_u = thisDeserializer.readResource()
            }
            else {
                throw new Error("One of the branches for setImageOptions1_src_buf_u has to be chosen through deserialisation.")
            }
            setImageOptions1_src_buf = (setImageOptions1_src_buf_u as string | Resource)
        }
        else if (setImageOptions1_src_buf_selector == 2) {
            setImageOptions1_src_buf = thisDeserializer.readDrawableDescriptor()
        }
        else if (setImageOptions1_src_buf_selector == 3) {
            setImageOptions1_src_buf = (thisDeserializer.readInt32() as ImageContent)
        }
        else {
            throw new Error("One of the branches for setImageOptions1_src_buf has to be chosen through deserialisation.")
        }
        node.setImageOptions1_src = (setImageOptions1_src_buf as PixelMap | ResourceStr | DrawableDescriptor | ImageContent)
    }
    _ImageInterface_setImageOptions2(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setImageOptions2_src_buf_selector: number = thisDeserializer.readInt8()
        let setImageOptions2_src_buf: PixelMap | ResourceStr | DrawableDescriptor | undefined|undefined 
        if (setImageOptions2_src_buf_selector == 0) {
            setImageOptions2_src_buf = (thisDeserializer.readPixelMap() as PixelMap)
        }
        else if (setImageOptions2_src_buf_selector == 1) {
            const setImageOptions2_src_buf_u_selector: number = thisDeserializer.readInt8()
            let setImageOptions2_src_buf_u: string | Resource | undefined|undefined 
            if (setImageOptions2_src_buf_u_selector == 0) {
                setImageOptions2_src_buf_u = (thisDeserializer.readString() as string)
            }
            else if (setImageOptions2_src_buf_u_selector == 1) {
                setImageOptions2_src_buf_u = thisDeserializer.readResource()
            }
            else {
                throw new Error("One of the branches for setImageOptions2_src_buf_u has to be chosen through deserialisation.")
            }
            setImageOptions2_src_buf = (setImageOptions2_src_buf_u as string | Resource)
        }
        else if (setImageOptions2_src_buf_selector == 2) {
            setImageOptions2_src_buf = thisDeserializer.readDrawableDescriptor()
        }
        else {
            throw new Error("One of the branches for setImageOptions2_src_buf has to be chosen through deserialisation.")
        }
        node.setImageOptions2_src = (setImageOptions2_src_buf as PixelMap | ResourceStr | DrawableDescriptor)
        node.setImageOptions2_imageAIOptions = thisDeserializer.readImageAIOptions()
    }
    _ImageAttribute_alt(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const alt_value_buf_selector: number = thisDeserializer.readInt8()
        let alt_value_buf: string | Resource | PixelMap | undefined|undefined 
        if (alt_value_buf_selector == 0) {
            alt_value_buf = (thisDeserializer.readString() as string)
        }
        else if (alt_value_buf_selector == 1) {
            alt_value_buf = thisDeserializer.readResource()
        }
        else if (alt_value_buf_selector == 2) {
            alt_value_buf = (thisDeserializer.readPixelMap() as PixelMap)
        }
        else {
            throw new Error("One of the branches for alt_value_buf has to be chosen through deserialisation.")
        }
        node.alt_value = (alt_value_buf as string | Resource | PixelMap)
    }
    _ImageAttribute_matchTextDirection(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        node.matchTextDirection_value = value
    }
    _ImageAttribute_fitOriginalSize(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        node.fitOriginalSize_value = value
    }
    _ImageAttribute_fillColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fillColor_value_buf_selector: number = thisDeserializer.readInt8()
        let fillColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (fillColor_value_buf_selector == 0) {
            fillColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (fillColor_value_buf_selector == 1) {
            fillColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fillColor_value_buf_selector == 2) {
            fillColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fillColor_value_buf_selector == 3) {
            fillColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fillColor_value_buf has to be chosen through deserialisation.")
        }
        node.fillColor_value = (fillColor_value_buf as Color | number | string | Resource)
    }
    _ImageAttribute_objectFit(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        node.objectFit_value = value
    }
    _ImageAttribute_objectRepeat(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        node.objectRepeat_value = value
    }
    _ImageAttribute_autoResize(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        node.autoResize_value = value
    }
    _ImageAttribute_renderMode(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        node.renderMode_value = value
    }
    _ImageAttribute_dynamicRangeMode(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        node.dynamicRangeMode_value = value
    }
    _ImageAttribute_interpolation(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        node.interpolation_value = value
    }
    _ImageAttribute_sourceSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.sourceSize_value = thisDeserializer.readImageSourceSize()
    }
    _ImageAttribute_syncLoad(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        node.syncLoad_value = value
    }
    _ImageAttribute_colorFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const colorFilter_value_buf_selector: number = thisDeserializer.readInt8()
        let colorFilter_value_buf: ColorFilter | DrawingColorFilter | undefined|undefined 
        if (colorFilter_value_buf_selector == 0) {
            colorFilter_value_buf = thisDeserializer.readColorFilter()
        }
        else if (colorFilter_value_buf_selector == 1) {
            colorFilter_value_buf = thisDeserializer.readDrawingColorFilter()
        }
        else {
            throw new Error("One of the branches for colorFilter_value_buf has to be chosen through deserialisation.")
        }
        node.colorFilter_value = (colorFilter_value_buf as ColorFilter | DrawingColorFilter)
    }
    _ImageAttribute_copyOption(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        node.copyOption_value = value
    }
    _ImageAttribute_draggable(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        node.draggable_value = value
    }
    _ImageAttribute_pointLight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.pointLight_value = thisDeserializer.readPointLightStyle()
    }
    _ImageAttribute_edgeAntialiasing(ptr: KPointer, value: number): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        node.edgeAntialiasing_value = value
    }
    _ImageAttribute_onComplete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onComplete_value = thisDeserializer.readCallback_Type_ImageAttribute_onComplete_callback_event_Void()
    }
    _ImageAttribute_onError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onError_value = thisDeserializer.readImageErrorCallback()
    }
    _ImageAttribute_onFinish(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onFinish_value = thisDeserializer.readCallback_Void()
    }
    _ImageAttribute_enableAnalyzer(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        node.enableAnalyzer_value = value
    }
    _ImageAttribute_analyzerConfig(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.analyzerConfig_value = thisDeserializer.readImageAnalyzerConfig()
    }
    _ImageAttribute_resizable(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.resizable_value = thisDeserializer.readResizableOptions()
    }
    _ImageAttribute_privacySensitive(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        node.privacySensitive_value = value
    }
    _ImageAttribute_enhancedImageQuality(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.enhancedImageQuality_value = thisDeserializer.readResolutionQuality()
    }
    _ImageAnimatorInterface_setImageAnimatorOptions(ptr: KPointer): void {
        let node = this.ptr2object<ImageAnimatorInterface>(ptr)
    }
    _ImageAnimatorAttribute_images(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageAnimatorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const images_value_buf_length: int32 = thisDeserializer.readInt32()
        let images_value_buf: Array<ImageFrameInfo> = new Array<ImageFrameInfo>()
        for (let images_value_buf_i = 0; images_value_buf_i < images_value_buf_length; images_value_buf_i++) {
            images_value_buf[images_value_buf_i] = thisDeserializer.readImageFrameInfo()
        }
        node.images_value = images_value_buf
    }
    _ImageAnimatorAttribute_state(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ImageAnimatorInterface>(ptr)
        node.state_value = value
    }
    _ImageAnimatorAttribute_duration(ptr: KPointer, value: number): void {
        let node = this.ptr2object<ImageAnimatorInterface>(ptr)
        node.duration_value = value
    }
    _ImageAnimatorAttribute_reverse(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ImageAnimatorInterface>(ptr)
        node.reverse_value = value
    }
    _ImageAnimatorAttribute_fixedSize(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ImageAnimatorInterface>(ptr)
        node.fixedSize_value = value
    }
    _ImageAnimatorAttribute_preDecode(ptr: KPointer, value: number): void {
        let node = this.ptr2object<ImageAnimatorInterface>(ptr)
        node.preDecode_value = value
    }
    _ImageAnimatorAttribute_fillMode(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ImageAnimatorInterface>(ptr)
        node.fillMode_value = value
    }
    _ImageAnimatorAttribute_iterations(ptr: KPointer, value: number): void {
        let node = this.ptr2object<ImageAnimatorInterface>(ptr)
        node.iterations_value = value
    }
    _ImageAnimatorAttribute_onStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageAnimatorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onStart_value = thisDeserializer.readCallback_Void()
    }
    _ImageAnimatorAttribute_onPause(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageAnimatorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onPause_value = thisDeserializer.readCallback_Void()
    }
    _ImageAnimatorAttribute_onRepeat(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageAnimatorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onRepeat_value = thisDeserializer.readCallback_Void()
    }
    _ImageAnimatorAttribute_onCancel(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageAnimatorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onCancel_value = thisDeserializer.readCallback_Void()
    }
    _ImageAnimatorAttribute_onFinish(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageAnimatorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onFinish_value = thisDeserializer.readCallback_Void()
    }
    _ImageSpanInterface_setImageSpanOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageSpanInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setImageSpanOptions_value_buf_selector: number = thisDeserializer.readInt8()
        let setImageSpanOptions_value_buf: ResourceStr | PixelMap | undefined|undefined 
        if (setImageSpanOptions_value_buf_selector == 0) {
            const setImageSpanOptions_value_buf_u_selector: number = thisDeserializer.readInt8()
            let setImageSpanOptions_value_buf_u: string | Resource | undefined|undefined 
            if (setImageSpanOptions_value_buf_u_selector == 0) {
                setImageSpanOptions_value_buf_u = (thisDeserializer.readString() as string)
            }
            else if (setImageSpanOptions_value_buf_u_selector == 1) {
                setImageSpanOptions_value_buf_u = thisDeserializer.readResource()
            }
            else {
                throw new Error("One of the branches for setImageSpanOptions_value_buf_u has to be chosen through deserialisation.")
            }
            setImageSpanOptions_value_buf = (setImageSpanOptions_value_buf_u as string | Resource)
        }
        else if (setImageSpanOptions_value_buf_selector == 1) {
            setImageSpanOptions_value_buf = (thisDeserializer.readPixelMap() as PixelMap)
        }
        else {
            throw new Error("One of the branches for setImageSpanOptions_value_buf has to be chosen through deserialisation.")
        }
        node.setImageSpanOptions_value = (setImageSpanOptions_value_buf as ResourceStr | PixelMap)
    }
    _ImageSpanAttribute_verticalAlign(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ImageSpanInterface>(ptr)
        node.verticalAlign_value = value
    }
    _ImageSpanAttribute_colorFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageSpanInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const colorFilter_value_buf_selector: number = thisDeserializer.readInt8()
        let colorFilter_value_buf: ColorFilter | DrawingColorFilter | undefined|undefined 
        if (colorFilter_value_buf_selector == 0) {
            colorFilter_value_buf = thisDeserializer.readColorFilter()
        }
        else if (colorFilter_value_buf_selector == 1) {
            colorFilter_value_buf = thisDeserializer.readDrawingColorFilter()
        }
        else {
            throw new Error("One of the branches for colorFilter_value_buf has to be chosen through deserialisation.")
        }
        node.colorFilter_value = (colorFilter_value_buf as ColorFilter | DrawingColorFilter)
    }
    _ImageSpanAttribute_objectFit(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ImageSpanInterface>(ptr)
        node.objectFit_value = value
    }
    _ImageSpanAttribute_onComplete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageSpanInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onComplete_value = thisDeserializer.readImageCompleteCallback()
    }
    _ImageSpanAttribute_onError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageSpanInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onError_value = thisDeserializer.readImageErrorCallback()
    }
    _ImageSpanAttribute_alt(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ImageSpanInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.alt_value = (thisDeserializer.readPixelMap() as PixelMap)
    }
    _LineInterface_setLineOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<LineInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setLineOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setLineOptions_options_buf: LineOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setLineOptions_options_buf_runtimeType))
        {
            setLineOptions_options_buf = thisDeserializer.readLineOptions()
        }
        node.setLineOptions_options = setLineOptions_options_buf
    }
    _LineAttribute_startPoint(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<LineInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const startPoint_value_buf_length: int32 = thisDeserializer.readInt32()
        let startPoint_value_buf: Array<any> = new Array<any>()
        for (let startPoint_value_buf_i = 0; startPoint_value_buf_i < startPoint_value_buf_length; startPoint_value_buf_i++) {
            startPoint_value_buf[startPoint_value_buf_i] = (thisDeserializer.readCustomObject("Any") as Object)
        }
        node.startPoint_value = startPoint_value_buf
    }
    _LineAttribute_endPoint(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<LineInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const endPoint_value_buf_length: int32 = thisDeserializer.readInt32()
        let endPoint_value_buf: Array<any> = new Array<any>()
        for (let endPoint_value_buf_i = 0; endPoint_value_buf_i < endPoint_value_buf_length; endPoint_value_buf_i++) {
            endPoint_value_buf[endPoint_value_buf_i] = (thisDeserializer.readCustomObject("Any") as Object)
        }
        node.endPoint_value = endPoint_value_buf
    }
    _ListInterface_setListOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setListOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setListOptions_options_buf: ListOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setListOptions_options_buf_runtimeType))
        {
            setListOptions_options_buf = thisDeserializer.readListOptions()
        }
        node.setListOptions_options = setListOptions_options_buf
    }
    _ListAttribute_alignListItem(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ListInterface>(ptr)
        node.alignListItem_value = value
    }
    _ListAttribute_listDirection(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ListInterface>(ptr)
        node.listDirection_value = value
    }
    _ListAttribute_scrollBar(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ListInterface>(ptr)
        node.scrollBar_value = value
    }
    _ListAttribute_contentStartOffset(ptr: KPointer, value: number): void {
        let node = this.ptr2object<ListInterface>(ptr)
        node.contentStartOffset_value = value
    }
    _ListAttribute_contentEndOffset(ptr: KPointer, value: number): void {
        let node = this.ptr2object<ListInterface>(ptr)
        node.contentEndOffset_value = value
    }
    _ListAttribute_divider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const divider_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let divider_value_buf: ListDividerOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (divider_value_buf_runtimeType))
        {
            divider_value_buf = thisDeserializer.readListDividerOptions()
        }
        node.divider_value = divider_value_buf
    }
    _ListAttribute_editMode(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ListInterface>(ptr)
        node.editMode_value = value
    }
    _ListAttribute_multiSelectable(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ListInterface>(ptr)
        node.multiSelectable_value = value
    }
    _ListAttribute_cachedCount0(ptr: KPointer, value: number): void {
        let node = this.ptr2object<ListInterface>(ptr)
        node.cachedCount0_value = value
    }
    _ListAttribute_cachedCount1(ptr: KPointer, count: number, show: KInt): void {
        let node = this.ptr2object<ListInterface>(ptr)
        node.cachedCount1_count = count
        node.cachedCount1_show = show
    }
    _ListAttribute_chainAnimation(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ListInterface>(ptr)
        node.chainAnimation_value = value
    }
    _ListAttribute_chainAnimationOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.chainAnimationOptions_value = thisDeserializer.readChainAnimationOptions()
    }
    _ListAttribute_sticky(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ListInterface>(ptr)
        node.sticky_value = value
    }
    _ListAttribute_scrollSnapAlign(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ListInterface>(ptr)
        node.scrollSnapAlign_value = value
    }
    _ListAttribute_nestedScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.nestedScroll_value = thisDeserializer.readNestedScrollOptions()
    }
    _ListAttribute_enableScrollInteraction(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ListInterface>(ptr)
        node.enableScrollInteraction_value = value
    }
    _ListAttribute_friction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const friction_value_buf_selector: number = thisDeserializer.readInt8()
        let friction_value_buf: number | Resource | undefined|undefined 
        if (friction_value_buf_selector == 0) {
            friction_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (friction_value_buf_selector == 1) {
            friction_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for friction_value_buf has to be chosen through deserialisation.")
        }
        node.friction_value = (friction_value_buf as number | Resource)
    }
    _ListAttribute_childrenMainSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.childrenMainSize_value = (thisDeserializer.readChildrenMainSize() as ChildrenMainSize)
    }
    _ListAttribute_maintainVisibleContentPosition(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ListInterface>(ptr)
        node.maintainVisibleContentPosition_value = value
    }
    _ListAttribute_onScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScroll_value = thisDeserializer.readCallback_Number_ScrollState_Void()
    }
    _ListAttribute_onScrollIndex(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScrollIndex_value = thisDeserializer.readCallback_Number_Number_Number_Void()
    }
    _ListAttribute_onScrollVisibleContentChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScrollVisibleContentChange_value = thisDeserializer.readOnScrollVisibleContentChangeCallback()
    }
    _ListAttribute_onReachStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onReachStart_value = thisDeserializer.readCallback_Void()
    }
    _ListAttribute_onReachEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onReachEnd_value = thisDeserializer.readCallback_Void()
    }
    _ListAttribute_onScrollStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScrollStart_value = thisDeserializer.readCallback_Void()
    }
    _ListAttribute_onScrollStop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScrollStop_value = thisDeserializer.readCallback_Void()
    }
    _ListAttribute_onItemDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onItemDelete_value = thisDeserializer.readCallback_Number_Boolean()
    }
    _ListAttribute_onItemMove(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onItemMove_value = thisDeserializer.readCallback_Number_Number_Boolean()
    }
    _ListAttribute_onItemDragStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onItemDragStart_value = thisDeserializer.readCallback_ItemDragInfo_Number_Callback_Any()
    }
    _ListAttribute_onItemDragEnter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onItemDragEnter_value = thisDeserializer.readCallback_ItemDragInfo_Void()
    }
    _ListAttribute_onItemDragMove(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onItemDragMove_value = thisDeserializer.readCallback_ItemDragInfo_Number_Number_Void()
    }
    _ListAttribute_onItemDragLeave(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onItemDragLeave_value = thisDeserializer.readCallback_ItemDragInfo_Number_Void()
    }
    _ListAttribute_onItemDrop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onItemDrop_value = thisDeserializer.readCallback_ItemDragInfo_Number_Number_Boolean_Void()
    }
    _ListAttribute_onScrollFrameBegin(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScrollFrameBegin_value = thisDeserializer.readCallback_Number_ScrollState_Literal_Number_offsetRemain()
    }
    _ListAttribute_lanes(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const lanes_value_buf_selector: number = thisDeserializer.readInt8()
        let lanes_value_buf: number | LengthConstrain | undefined|undefined 
        if (lanes_value_buf_selector == 0) {
            lanes_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (lanes_value_buf_selector == 1) {
            const lanes_value_buf_u_minLength: Length = (thisDeserializer.readLength() as Length)
            const lanes_value_buf_u_maxLength: Length = (thisDeserializer.readLength() as Length)
            lanes_value_buf = ({minLength: lanes_value_buf_u_minLength, maxLength: lanes_value_buf_u_maxLength} as LengthConstrain)
        }
        else {
            throw new Error("One of the branches for lanes_value_buf has to be chosen through deserialisation.")
        }
        node.lanes_value = (lanes_value_buf as number | LengthConstrain)
        const lanes_gutter_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let lanes_gutter_buf: Dimension | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (lanes_gutter_buf_runtimeType))
        {
            lanes_gutter_buf = (thisDeserializer.readLength() as Dimension)
        }
        node.lanes_gutter = lanes_gutter_buf
    }
    _ListAttribute_edgeEffect(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListInterface>(ptr)
        node.edgeEffect_value = value
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const edgeEffect_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let edgeEffect_options_buf: EdgeEffectOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (edgeEffect_options_buf_runtimeType))
        {
            edgeEffect_options_buf = thisDeserializer.readEdgeEffectOptions()
        }
        node.edgeEffect_options = edgeEffect_options_buf
    }
    _ListItemInterface_setListItemOptions0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListItemInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setListItemOptions0_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setListItemOptions0_value_buf: ListItemOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setListItemOptions0_value_buf_runtimeType))
        {
            setListItemOptions0_value_buf = thisDeserializer.readListItemOptions()
        }
        node.setListItemOptions0_value = setListItemOptions0_value_buf
    }
    _ListItemInterface_setListItemOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListItemInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setListItemOptions1_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setListItemOptions1_value_buf: string | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setListItemOptions1_value_buf_runtimeType))
        {
            setListItemOptions1_value_buf = (thisDeserializer.readString() as string)
        }
        node.setListItemOptions1_value = setListItemOptions1_value_buf
    }
    _ListItemAttribute_sticky(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ListItemInterface>(ptr)
        node.sticky_value = value
    }
    _ListItemAttribute_editable(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListItemInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const editable_value_buf_selector: number = thisDeserializer.readInt8()
        let editable_value_buf: boolean | EditMode | undefined|undefined 
        if (editable_value_buf_selector == 0) {
            editable_value_buf = thisDeserializer.readBoolean()
        }
        else if (editable_value_buf_selector == 1) {
            editable_value_buf = (thisDeserializer.readInt32() as EditMode)
        }
        else {
            throw new Error("One of the branches for editable_value_buf has to be chosen through deserialisation.")
        }
        node.editable_value = (editable_value_buf as boolean | EditMode)
    }
    _ListItemAttribute_selectable(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ListItemInterface>(ptr)
        node.selectable_value = value
    }
    _ListItemAttribute_selected(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ListItemInterface>(ptr)
        node.selected_value = value
    }
    _ListItemAttribute_swipeAction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListItemInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.swipeAction_value = thisDeserializer.readSwipeActionOptions()
    }
    _ListItemAttribute_onSelect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListItemInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSelect_value = thisDeserializer.readCallback_Boolean_Void()
    }
    _ListItemGroupInterface_setListItemGroupOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListItemGroupInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setListItemGroupOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setListItemGroupOptions_options_buf: ListItemGroupOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setListItemGroupOptions_options_buf_runtimeType))
        {
            setListItemGroupOptions_options_buf = thisDeserializer.readListItemGroupOptions()
        }
        node.setListItemGroupOptions_options = setListItemGroupOptions_options_buf
    }
    _ListItemGroupAttribute_divider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListItemGroupInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const divider_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let divider_value_buf: ListDividerOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (divider_value_buf_runtimeType))
        {
            divider_value_buf = thisDeserializer.readListDividerOptions()
        }
        node.divider_value = divider_value_buf
    }
    _ListItemGroupAttribute_childrenMainSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ListItemGroupInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.childrenMainSize_value = (thisDeserializer.readChildrenMainSize() as ChildrenMainSize)
    }
    _LoadingProgressInterface_setLoadingProgressOptions(ptr: KPointer): void {
        let node = this.ptr2object<LoadingProgressInterface>(ptr)
    }
    _LoadingProgressAttribute_color(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<LoadingProgressInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const color_value_buf_selector: number = thisDeserializer.readInt8()
        let color_value_buf: Color | number | string | Resource | undefined|undefined 
        if (color_value_buf_selector == 0) {
            color_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (color_value_buf_selector == 1) {
            color_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (color_value_buf_selector == 2) {
            color_value_buf = (thisDeserializer.readString() as string)
        }
        else if (color_value_buf_selector == 3) {
            color_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for color_value_buf has to be chosen through deserialisation.")
        }
        node.color_value = (color_value_buf as Color | number | string | Resource)
    }
    _LoadingProgressAttribute_enableLoading(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<LoadingProgressInterface>(ptr)
        node.enableLoading_value = value
    }
    _LoadingProgressAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<LoadingProgressInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.contentModifier_value = (thisDeserializer.readCustomObject("ContentModifier") as ContentModifier<any>)
    }
    _LocationButtonInterface_setLocationButtonOptions0(ptr: KPointer): void {
        let node = this.ptr2object<LocationButtonInterface>(ptr)
    }
    _LocationButtonInterface_setLocationButtonOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<LocationButtonInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setLocationButtonOptions1_options = thisDeserializer.readLocationButtonOptions()
    }
    _LocationButtonAttribute_onClick(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<LocationButtonInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onClick_value = thisDeserializer.readCallback_ClickEvent_LocationButtonOnClickResult_Void()
    }
    _MarqueeInterface_setMarqueeOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<MarqueeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setMarqueeOptions_options = thisDeserializer.readMarqueeOptions()
    }
    _MarqueeAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<MarqueeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontColor_value_buf_selector: number = thisDeserializer.readInt8()
        let fontColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (fontColor_value_buf_selector == 0) {
            fontColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (fontColor_value_buf_selector == 1) {
            fontColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontColor_value_buf_selector == 2) {
            fontColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontColor_value_buf_selector == 3) {
            fontColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontColor_value_buf has to be chosen through deserialisation.")
        }
        node.fontColor_value = (fontColor_value_buf as Color | number | string | Resource)
    }
    _MarqueeAttribute_fontSize(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<MarqueeInterface>(ptr)
        node.fontSize_value = value
    }
    _MarqueeAttribute_allowScale(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<MarqueeInterface>(ptr)
        node.allowScale_value = value
    }
    _MarqueeAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<MarqueeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontWeight_value_buf_selector: number = thisDeserializer.readInt8()
        let fontWeight_value_buf: number | FontWeight | string | undefined|undefined 
        if (fontWeight_value_buf_selector == 0) {
            fontWeight_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontWeight_value_buf_selector == 1) {
            fontWeight_value_buf = (thisDeserializer.readInt32() as FontWeight)
        }
        else if (fontWeight_value_buf_selector == 2) {
            fontWeight_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for fontWeight_value_buf has to be chosen through deserialisation.")
        }
        node.fontWeight_value = (fontWeight_value_buf as number | FontWeight | string)
    }
    _MarqueeAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<MarqueeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontFamily_value_buf_selector: number = thisDeserializer.readInt8()
        let fontFamily_value_buf: string | Resource | undefined|undefined 
        if (fontFamily_value_buf_selector == 0) {
            fontFamily_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontFamily_value_buf_selector == 1) {
            fontFamily_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontFamily_value_buf has to be chosen through deserialisation.")
        }
        node.fontFamily_value = (fontFamily_value_buf as string | Resource)
    }
    _MarqueeAttribute_marqueeUpdateStrategy(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<MarqueeInterface>(ptr)
        node.marqueeUpdateStrategy_value = value
    }
    _MarqueeAttribute_onStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<MarqueeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onStart_value = thisDeserializer.readCallback_Void()
    }
    _MarqueeAttribute_onBounce(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<MarqueeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onBounce_value = thisDeserializer.readCallback_Void()
    }
    _MarqueeAttribute_onFinish(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<MarqueeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onFinish_value = thisDeserializer.readCallback_Void()
    }
    _MediaCachedImageInterface_setMediaCachedImageOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<MediaCachedImageInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setMediaCachedImageOptions_src_buf_selector: number = thisDeserializer.readInt8()
        let setMediaCachedImageOptions_src_buf: PixelMap | ResourceStr | DrawableDescriptor | ASTCResource | undefined|undefined 
        if (setMediaCachedImageOptions_src_buf_selector == 0) {
            setMediaCachedImageOptions_src_buf = (thisDeserializer.readPixelMap() as PixelMap)
        }
        else if (setMediaCachedImageOptions_src_buf_selector == 1) {
            const setMediaCachedImageOptions_src_buf_u_selector: number = thisDeserializer.readInt8()
            let setMediaCachedImageOptions_src_buf_u: string | Resource | undefined|undefined 
            if (setMediaCachedImageOptions_src_buf_u_selector == 0) {
                setMediaCachedImageOptions_src_buf_u = (thisDeserializer.readString() as string)
            }
            else if (setMediaCachedImageOptions_src_buf_u_selector == 1) {
                setMediaCachedImageOptions_src_buf_u = thisDeserializer.readResource()
            }
            else {
                throw new Error("One of the branches for setMediaCachedImageOptions_src_buf_u has to be chosen through deserialisation.")
            }
            setMediaCachedImageOptions_src_buf = (setMediaCachedImageOptions_src_buf_u as string | Resource)
        }
        else if (setMediaCachedImageOptions_src_buf_selector == 2) {
            setMediaCachedImageOptions_src_buf = thisDeserializer.readDrawableDescriptor()
        }
        else if (setMediaCachedImageOptions_src_buf_selector == 3) {
            setMediaCachedImageOptions_src_buf = thisDeserializer.readASTCResource()
        }
        else {
            throw new Error("One of the branches for setMediaCachedImageOptions_src_buf has to be chosen through deserialisation.")
        }
        node.setMediaCachedImageOptions_src = (setMediaCachedImageOptions_src_buf as PixelMap | ResourceStr | DrawableDescriptor | ASTCResource)
    }
    _MenuInterface_setMenuOptions(ptr: KPointer): void {
        let node = this.ptr2object<MenuInterface>(ptr)
    }
    _MenuAttribute_fontSize(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<MenuInterface>(ptr)
        node.fontSize_value = value
    }
    _MenuAttribute_font(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<MenuInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.font_value = thisDeserializer.readFont()
    }
    _MenuAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<MenuInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontColor_value_buf_selector: number = thisDeserializer.readInt8()
        let fontColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (fontColor_value_buf_selector == 0) {
            fontColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (fontColor_value_buf_selector == 1) {
            fontColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontColor_value_buf_selector == 2) {
            fontColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontColor_value_buf_selector == 3) {
            fontColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontColor_value_buf has to be chosen through deserialisation.")
        }
        node.fontColor_value = (fontColor_value_buf as Color | number | string | Resource)
    }
    _MenuAttribute_radius(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<MenuInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const radius_value_buf_selector: number = thisDeserializer.readInt8()
        let radius_value_buf: Dimension | BorderRadiuses | undefined|undefined 
        if (radius_value_buf_selector == 0) {
            radius_value_buf = (thisDeserializer.readLength() as Dimension)
        }
        else if (radius_value_buf_selector == 1) {
            const radius_value_buf_u_topLeft_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let radius_value_buf_u_topLeft_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (radius_value_buf_u_topLeft_buf_runtimeType))
            {
                radius_value_buf_u_topLeft_buf = (thisDeserializer.readLength() as Length)
            }
            const radius_value_buf_u_topLeft: undefined | Length = radius_value_buf_u_topLeft_buf
            const radius_value_buf_u_topRight_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let radius_value_buf_u_topRight_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (radius_value_buf_u_topRight_buf_runtimeType))
            {
                radius_value_buf_u_topRight_buf = (thisDeserializer.readLength() as Length)
            }
            const radius_value_buf_u_topRight: undefined | Length = radius_value_buf_u_topRight_buf
            const radius_value_buf_u_bottomLeft_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let radius_value_buf_u_bottomLeft_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (radius_value_buf_u_bottomLeft_buf_runtimeType))
            {
                radius_value_buf_u_bottomLeft_buf = (thisDeserializer.readLength() as Length)
            }
            const radius_value_buf_u_bottomLeft: undefined | Length = radius_value_buf_u_bottomLeft_buf
            const radius_value_buf_u_bottomRight_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let radius_value_buf_u_bottomRight_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (radius_value_buf_u_bottomRight_buf_runtimeType))
            {
                radius_value_buf_u_bottomRight_buf = (thisDeserializer.readLength() as Length)
            }
            const radius_value_buf_u_bottomRight: undefined | Length = radius_value_buf_u_bottomRight_buf
            radius_value_buf = ({topLeft: radius_value_buf_u_topLeft, topRight: radius_value_buf_u_topRight, bottomLeft: radius_value_buf_u_bottomLeft, bottomRight: radius_value_buf_u_bottomRight} as BorderRadiuses)
        }
        else {
            throw new Error("One of the branches for radius_value_buf has to be chosen through deserialisation.")
        }
        node.radius_value = (radius_value_buf as Dimension | BorderRadiuses)
    }
    _MenuAttribute_menuItemDivider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<MenuInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const menuItemDivider_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let menuItemDivider_value_buf: DividerStyleOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (menuItemDivider_value_buf_runtimeType))
        {
            menuItemDivider_value_buf = thisDeserializer.readDividerStyleOptions()
        }
        node.menuItemDivider_value = menuItemDivider_value_buf
    }
    _MenuAttribute_menuItemGroupDivider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<MenuInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const menuItemGroupDivider_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let menuItemGroupDivider_value_buf: DividerStyleOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (menuItemGroupDivider_value_buf_runtimeType))
        {
            menuItemGroupDivider_value_buf = thisDeserializer.readDividerStyleOptions()
        }
        node.menuItemGroupDivider_value = menuItemGroupDivider_value_buf
    }
    _MenuAttribute_subMenuExpandingMode(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<MenuInterface>(ptr)
        node.subMenuExpandingMode_value = value
    }
    _MenuItemInterface_setMenuItemOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<MenuItemInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setMenuItemOptions_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setMenuItemOptions_value_buf: MenuItemOptions | CustomBuilder | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setMenuItemOptions_value_buf_runtimeType))
        {
            const setMenuItemOptions_value_buf__selector: number = thisDeserializer.readInt8()
            let setMenuItemOptions_value_buf_: MenuItemOptions | CustomBuilder | undefined|undefined 
            if (setMenuItemOptions_value_buf__selector == 0) {
                setMenuItemOptions_value_buf_ = thisDeserializer.readMenuItemOptions()
            }
            else if (setMenuItemOptions_value_buf__selector == 1) {
                setMenuItemOptions_value_buf_ = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
            }
            else {
                throw new Error("One of the branches for setMenuItemOptions_value_buf_ has to be chosen through deserialisation.")
            }
            setMenuItemOptions_value_buf = (setMenuItemOptions_value_buf_ as MenuItemOptions | CustomBuilder)
        }
        node.setMenuItemOptions_value = setMenuItemOptions_value_buf
    }
    _MenuItemAttribute_selected(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<MenuItemInterface>(ptr)
        node.selected_value = value
    }
    _MenuItemAttribute_selectIcon(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<MenuItemInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const selectIcon_value_buf_selector: number = thisDeserializer.readInt8()
        let selectIcon_value_buf: boolean | ResourceStr | SymbolGlyphModifier | undefined|undefined 
        if (selectIcon_value_buf_selector == 0) {
            selectIcon_value_buf = thisDeserializer.readBoolean()
        }
        else if (selectIcon_value_buf_selector == 1) {
            const selectIcon_value_buf_u_selector: number = thisDeserializer.readInt8()
            let selectIcon_value_buf_u: string | Resource | undefined|undefined 
            if (selectIcon_value_buf_u_selector == 0) {
                selectIcon_value_buf_u = (thisDeserializer.readString() as string)
            }
            else if (selectIcon_value_buf_u_selector == 1) {
                selectIcon_value_buf_u = thisDeserializer.readResource()
            }
            else {
                throw new Error("One of the branches for selectIcon_value_buf_u has to be chosen through deserialisation.")
            }
            selectIcon_value_buf = (selectIcon_value_buf_u as string | Resource)
        }
        else if (selectIcon_value_buf_selector == 2) {
            selectIcon_value_buf = thisDeserializer.readSymbolGlyphModifier()
        }
        else {
            throw new Error("One of the branches for selectIcon_value_buf has to be chosen through deserialisation.")
        }
        node.selectIcon_value = (selectIcon_value_buf as boolean | ResourceStr | SymbolGlyphModifier)
    }
    _MenuItemAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<MenuItemInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onChange_value = thisDeserializer.readCallback_Boolean_Void()
    }
    _MenuItemAttribute_contentFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<MenuItemInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.contentFont_value = thisDeserializer.readFont()
    }
    _MenuItemAttribute_contentFontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<MenuItemInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const contentFontColor_value_buf_selector: number = thisDeserializer.readInt8()
        let contentFontColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (contentFontColor_value_buf_selector == 0) {
            contentFontColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (contentFontColor_value_buf_selector == 1) {
            contentFontColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (contentFontColor_value_buf_selector == 2) {
            contentFontColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (contentFontColor_value_buf_selector == 3) {
            contentFontColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for contentFontColor_value_buf has to be chosen through deserialisation.")
        }
        node.contentFontColor_value = (contentFontColor_value_buf as Color | number | string | Resource)
    }
    _MenuItemAttribute_labelFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<MenuItemInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.labelFont_value = thisDeserializer.readFont()
    }
    _MenuItemAttribute_labelFontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<MenuItemInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const labelFontColor_value_buf_selector: number = thisDeserializer.readInt8()
        let labelFontColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (labelFontColor_value_buf_selector == 0) {
            labelFontColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (labelFontColor_value_buf_selector == 1) {
            labelFontColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (labelFontColor_value_buf_selector == 2) {
            labelFontColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (labelFontColor_value_buf_selector == 3) {
            labelFontColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for labelFontColor_value_buf has to be chosen through deserialisation.")
        }
        node.labelFontColor_value = (labelFontColor_value_buf as Color | number | string | Resource)
    }
    _MenuItemGroupInterface_setMenuItemGroupOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<MenuItemGroupInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setMenuItemGroupOptions_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setMenuItemGroupOptions_value_buf: MenuItemGroupOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setMenuItemGroupOptions_value_buf_runtimeType))
        {
            setMenuItemGroupOptions_value_buf = thisDeserializer.readMenuItemGroupOptions()
        }
        node.setMenuItemGroupOptions_value = setMenuItemGroupOptions_value_buf
    }
    _NavDestinationInterface_setNavDestinationOptions(ptr: KPointer): void {
        let node = this.ptr2object<NavDestinationInterface>(ptr)
    }
    _NavDestinationAttribute_hideTitleBar0(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<NavDestinationInterface>(ptr)
        node.hideTitleBar0_value = value
    }
    _NavDestinationAttribute_hideTitleBar1(ptr: KPointer, hide: KInt, animated: KInt): void {
        let node = this.ptr2object<NavDestinationInterface>(ptr)
        node.hideTitleBar1_hide = hide
        node.hideTitleBar1_animated = animated
    }
    _NavDestinationAttribute_onShown(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<NavDestinationInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onShown_value = thisDeserializer.readCallback_Void()
    }
    _NavDestinationAttribute_onHidden(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<NavDestinationInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onHidden_value = thisDeserializer.readCallback_Void()
    }
    _NavDestinationAttribute_onBackPressed(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<NavDestinationInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onBackPressed_value = thisDeserializer.readCallback_Boolean()
    }
    _NavDestinationAttribute_mode(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<NavDestinationInterface>(ptr)
        node.mode_value = value
    }
    _NavDestinationAttribute_backButtonIcon(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<NavDestinationInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const backButtonIcon_value_buf_selector: number = thisDeserializer.readInt8()
        let backButtonIcon_value_buf: ResourceStr | PixelMap | SymbolGlyphModifier | undefined|undefined 
        if (backButtonIcon_value_buf_selector == 0) {
            const backButtonIcon_value_buf_u_selector: number = thisDeserializer.readInt8()
            let backButtonIcon_value_buf_u: string | Resource | undefined|undefined 
            if (backButtonIcon_value_buf_u_selector == 0) {
                backButtonIcon_value_buf_u = (thisDeserializer.readString() as string)
            }
            else if (backButtonIcon_value_buf_u_selector == 1) {
                backButtonIcon_value_buf_u = thisDeserializer.readResource()
            }
            else {
                throw new Error("One of the branches for backButtonIcon_value_buf_u has to be chosen through deserialisation.")
            }
            backButtonIcon_value_buf = (backButtonIcon_value_buf_u as string | Resource)
        }
        else if (backButtonIcon_value_buf_selector == 1) {
            backButtonIcon_value_buf = (thisDeserializer.readPixelMap() as PixelMap)
        }
        else if (backButtonIcon_value_buf_selector == 2) {
            backButtonIcon_value_buf = thisDeserializer.readSymbolGlyphModifier()
        }
        else {
            throw new Error("One of the branches for backButtonIcon_value_buf has to be chosen through deserialisation.")
        }
        node.backButtonIcon_value = (backButtonIcon_value_buf as ResourceStr | PixelMap | SymbolGlyphModifier)
    }
    _NavDestinationAttribute_menus(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<NavDestinationInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const menus_value_buf_selector: number = thisDeserializer.readInt8()
        let menus_value_buf: Array<NavigationMenuItem> | CustomBuilder | undefined|undefined 
        if (menus_value_buf_selector == 0) {
            const menus_value_buf_u_length: int32 = thisDeserializer.readInt32()
            let menus_value_buf_u: Array<NavigationMenuItem> = new Array<NavigationMenuItem>()
            for (let menus_value_buf_u_i = 0; menus_value_buf_u_i < menus_value_buf_u_length; menus_value_buf_u_i++) {
                menus_value_buf_u[menus_value_buf_u_i] = thisDeserializer.readNavigationMenuItem()
            }
            menus_value_buf = menus_value_buf_u
        }
        else if (menus_value_buf_selector == 1) {
            menus_value_buf = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
        }
        else {
            throw new Error("One of the branches for menus_value_buf has to be chosen through deserialisation.")
        }
        node.menus_value = (menus_value_buf as Array<NavigationMenuItem> | CustomBuilder)
    }
    _NavDestinationAttribute_onReady(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<NavDestinationInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onReady_value = thisDeserializer.readCallback_NavDestinationContext_Void()
    }
    _NavDestinationAttribute_onWillAppear(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<NavDestinationInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onWillAppear_value = thisDeserializer.readCallback_Void()
    }
    _NavDestinationAttribute_onWillDisappear(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<NavDestinationInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onWillDisappear_value = thisDeserializer.readCallback_Void()
    }
    _NavDestinationAttribute_onWillShow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<NavDestinationInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onWillShow_value = thisDeserializer.readCallback_Void()
    }
    _NavDestinationAttribute_onWillHide(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<NavDestinationInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onWillHide_value = thisDeserializer.readCallback_Void()
    }
    _NavDestinationAttribute_systemBarStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<NavDestinationInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const systemBarStyle_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let systemBarStyle_value_buf: SystemBarStyle | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (systemBarStyle_value_buf_runtimeType))
        {
            systemBarStyle_value_buf = thisDeserializer.readSystemBarStyle()
        }
        node.systemBarStyle_value = systemBarStyle_value_buf
    }
    _NavDestinationAttribute_recoverable(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<NavDestinationInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const recoverable_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let recoverable_value_buf: boolean | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (recoverable_value_buf_runtimeType))
        {
            recoverable_value_buf = thisDeserializer.readBoolean()
        }
        node.recoverable_value = recoverable_value_buf
    }
    _NavDestinationAttribute_systemTransition(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<NavDestinationInterface>(ptr)
        node.systemTransition_value = value
    }
    _NavDestinationAttribute_title(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<NavDestinationInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const title_value_buf_selector: number = thisDeserializer.readInt8()
        let title_value_buf: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource | undefined|undefined 
        if (title_value_buf_selector == 0) {
            title_value_buf = (thisDeserializer.readString() as string)
        }
        else if (title_value_buf_selector == 1) {
            title_value_buf = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
        }
        else if (title_value_buf_selector == 2) {
            title_value_buf = thisDeserializer.readNavDestinationCommonTitle()
        }
        else if (title_value_buf_selector == 3) {
            title_value_buf = thisDeserializer.readNavDestinationCustomTitle()
        }
        else if (title_value_buf_selector == 4) {
            title_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for title_value_buf has to be chosen through deserialisation.")
        }
        node.title_value = (title_value_buf as string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource)
        const title_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let title_options_buf: NavigationTitleOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (title_options_buf_runtimeType))
        {
            title_options_buf = thisDeserializer.readNavigationTitleOptions()
        }
        node.title_options = title_options_buf
    }
    _NavDestinationAttribute_toolbarConfiguration(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<NavDestinationInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const toolbarConfiguration_toolbarParam_buf_selector: number = thisDeserializer.readInt8()
        let toolbarConfiguration_toolbarParam_buf: Array<ToolbarItem> | CustomBuilder | undefined|undefined 
        if (toolbarConfiguration_toolbarParam_buf_selector == 0) {
            const toolbarConfiguration_toolbarParam_buf_u_length: int32 = thisDeserializer.readInt32()
            let toolbarConfiguration_toolbarParam_buf_u: Array<ToolbarItem> = new Array<ToolbarItem>()
            for (let toolbarConfiguration_toolbarParam_buf_u_i = 0; toolbarConfiguration_toolbarParam_buf_u_i < toolbarConfiguration_toolbarParam_buf_u_length; toolbarConfiguration_toolbarParam_buf_u_i++) {
                toolbarConfiguration_toolbarParam_buf_u[toolbarConfiguration_toolbarParam_buf_u_i] = thisDeserializer.readToolbarItem()
            }
            toolbarConfiguration_toolbarParam_buf = toolbarConfiguration_toolbarParam_buf_u
        }
        else if (toolbarConfiguration_toolbarParam_buf_selector == 1) {
            toolbarConfiguration_toolbarParam_buf = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
        }
        else {
            throw new Error("One of the branches for toolbarConfiguration_toolbarParam_buf has to be chosen through deserialisation.")
        }
        node.toolbarConfiguration_toolbarParam = (toolbarConfiguration_toolbarParam_buf as Array<ToolbarItem> | CustomBuilder)
        const toolbarConfiguration_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let toolbarConfiguration_options_buf: NavigationToolbarOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (toolbarConfiguration_options_buf_runtimeType))
        {
            toolbarConfiguration_options_buf = thisDeserializer.readNavigationToolbarOptions()
        }
        node.toolbarConfiguration_options = toolbarConfiguration_options_buf
    }
    _NavDestinationAttribute_hideToolBar(ptr: KPointer, hide: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<NavDestinationInterface>(ptr)
        node.hideToolBar_hide = hide
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const hideToolBar_animated_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let hideToolBar_animated_buf: boolean | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (hideToolBar_animated_buf_runtimeType))
        {
            hideToolBar_animated_buf = thisDeserializer.readBoolean()
        }
        node.hideToolBar_animated = hideToolBar_animated_buf
    }
    _NavDestinationAttribute_ignoreLayoutSafeArea(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<NavDestinationInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const ignoreLayoutSafeArea_types_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let ignoreLayoutSafeArea_types_buf: Array<LayoutSafeAreaType> | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (ignoreLayoutSafeArea_types_buf_runtimeType))
        {
            const ignoreLayoutSafeArea_types_buf__length: int32 = thisDeserializer.readInt32()
            let ignoreLayoutSafeArea_types_buf_: Array<LayoutSafeAreaType> = new Array<LayoutSafeAreaType>()
            for (let ignoreLayoutSafeArea_types_buf__i = 0; ignoreLayoutSafeArea_types_buf__i < ignoreLayoutSafeArea_types_buf__length; ignoreLayoutSafeArea_types_buf__i++) {
                ignoreLayoutSafeArea_types_buf_[ignoreLayoutSafeArea_types_buf__i] = (thisDeserializer.readInt32() as LayoutSafeAreaType)
            }
            ignoreLayoutSafeArea_types_buf = ignoreLayoutSafeArea_types_buf_
        }
        node.ignoreLayoutSafeArea_types = ignoreLayoutSafeArea_types_buf
        const ignoreLayoutSafeArea_edges_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let ignoreLayoutSafeArea_edges_buf: Array<LayoutSafeAreaEdge> | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (ignoreLayoutSafeArea_edges_buf_runtimeType))
        {
            const ignoreLayoutSafeArea_edges_buf__length: int32 = thisDeserializer.readInt32()
            let ignoreLayoutSafeArea_edges_buf_: Array<LayoutSafeAreaEdge> = new Array<LayoutSafeAreaEdge>()
            for (let ignoreLayoutSafeArea_edges_buf__i = 0; ignoreLayoutSafeArea_edges_buf__i < ignoreLayoutSafeArea_edges_buf__length; ignoreLayoutSafeArea_edges_buf__i++) {
                ignoreLayoutSafeArea_edges_buf_[ignoreLayoutSafeArea_edges_buf__i] = (thisDeserializer.readInt32() as LayoutSafeAreaEdge)
            }
            ignoreLayoutSafeArea_edges_buf = ignoreLayoutSafeArea_edges_buf_
        }
        node.ignoreLayoutSafeArea_edges = ignoreLayoutSafeArea_edges_buf
    }
    _NavRouterInterface_setNavRouterOptions0(ptr: KPointer): void {
        let node = this.ptr2object<NavRouterInterface>(ptr)
    }
    _NavRouterInterface_setNavRouterOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<NavRouterInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setNavRouterOptions1_value = thisDeserializer.readRouteInfo()
    }
    _NavRouterAttribute_onStateChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<NavRouterInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onStateChange_value = thisDeserializer.readCallback_Boolean_Void()
    }
    _NavRouterAttribute_mode(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<NavRouterInterface>(ptr)
        node.mode_value = value
    }
    _NavigatorInterface_setNavigatorOptions0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<NavigatorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setNavigatorOptions0_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setNavigatorOptions0_value_buf: { target: string, type?: NavigationType } | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setNavigatorOptions0_value_buf_runtimeType))
        {
            const setNavigatorOptions0_value_buf__target: string = (thisDeserializer.readString() as string)
            const setNavigatorOptions0_value_buf__type_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let setNavigatorOptions0_value_buf__type_buf: NavigationType | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (setNavigatorOptions0_value_buf__type_buf_runtimeType))
            {
                setNavigatorOptions0_value_buf__type_buf = (thisDeserializer.readInt32() as NavigationType)
            }
            const setNavigatorOptions0_value_buf__type: undefined | NavigationType = setNavigatorOptions0_value_buf__type_buf
            setNavigatorOptions0_value_buf = ({target: setNavigatorOptions0_value_buf__target, type: setNavigatorOptions0_value_buf__type} as { target: string, type?: NavigationType })
        }
        node.setNavigatorOptions0_value = setNavigatorOptions0_value_buf
    }
    _NavigatorInterface_setNavigatorOptions1(ptr: KPointer): void {
        let node = this.ptr2object<NavigatorInterface>(ptr)
    }
    _NavigatorAttribute_active(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<NavigatorInterface>(ptr)
        node.active_value = value
    }
    _NavigatorAttribute_type(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<NavigatorInterface>(ptr)
        node.type_value = value
    }
    _NavigatorAttribute_target(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<NavigatorInterface>(ptr)
        node.target_value = value
    }
    _NavigatorAttribute_params(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<NavigatorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.params_value = (thisDeserializer.readCustomObject("Object") as Object)
    }
    _NodeContainerInterface_setNodeContainerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<NodeContainerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setNodeContainerOptions_controller = thisDeserializer.readNodeController()
    }
    _PanelInterface_setPanelOptions(ptr: KPointer, show: KInt): void {
        let node = this.ptr2object<PanelInterface>(ptr)
        node.setPanelOptions_show = show
    }
    _PanelAttribute_mode(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<PanelInterface>(ptr)
        node.mode_value = value
    }
    _PanelAttribute_type(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<PanelInterface>(ptr)
        node.type_value = value
    }
    _PanelAttribute_dragBar(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<PanelInterface>(ptr)
        node.dragBar_value = value
    }
    _PanelAttribute_customHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PanelInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const customHeight_value_buf_selector: number = thisDeserializer.readInt8()
        let customHeight_value_buf: Dimension | PanelHeight | undefined|undefined 
        if (customHeight_value_buf_selector == 0) {
            customHeight_value_buf = (thisDeserializer.readLength() as Dimension)
        }
        else if (customHeight_value_buf_selector == 1) {
            customHeight_value_buf = Object.values(PanelHeight)[thisDeserializer.readInt32()]
        }
        else {
            throw new Error("One of the branches for customHeight_value_buf has to be chosen through deserialisation.")
        }
        node.customHeight_value = (customHeight_value_buf as Dimension | PanelHeight)
    }
    _PanelAttribute_fullHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PanelInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fullHeight_value_buf_selector: number = thisDeserializer.readInt8()
        let fullHeight_value_buf: number | string | undefined|undefined 
        if (fullHeight_value_buf_selector == 0) {
            fullHeight_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fullHeight_value_buf_selector == 1) {
            fullHeight_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for fullHeight_value_buf has to be chosen through deserialisation.")
        }
        node.fullHeight_value = (fullHeight_value_buf as number | string)
    }
    _PanelAttribute_halfHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PanelInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const halfHeight_value_buf_selector: number = thisDeserializer.readInt8()
        let halfHeight_value_buf: number | string | undefined|undefined 
        if (halfHeight_value_buf_selector == 0) {
            halfHeight_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (halfHeight_value_buf_selector == 1) {
            halfHeight_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for halfHeight_value_buf has to be chosen through deserialisation.")
        }
        node.halfHeight_value = (halfHeight_value_buf as number | string)
    }
    _PanelAttribute_miniHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PanelInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const miniHeight_value_buf_selector: number = thisDeserializer.readInt8()
        let miniHeight_value_buf: number | string | undefined|undefined 
        if (miniHeight_value_buf_selector == 0) {
            miniHeight_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (miniHeight_value_buf_selector == 1) {
            miniHeight_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for miniHeight_value_buf has to be chosen through deserialisation.")
        }
        node.miniHeight_value = (miniHeight_value_buf as number | string)
    }
    _PanelAttribute_show(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<PanelInterface>(ptr)
        node.show_value = value
    }
    _PanelAttribute_backgroundMask(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PanelInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const backgroundMask_value_buf_selector: number = thisDeserializer.readInt8()
        let backgroundMask_value_buf: Color | number | string | Resource | undefined|undefined 
        if (backgroundMask_value_buf_selector == 0) {
            backgroundMask_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (backgroundMask_value_buf_selector == 1) {
            backgroundMask_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (backgroundMask_value_buf_selector == 2) {
            backgroundMask_value_buf = (thisDeserializer.readString() as string)
        }
        else if (backgroundMask_value_buf_selector == 3) {
            backgroundMask_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for backgroundMask_value_buf has to be chosen through deserialisation.")
        }
        node.backgroundMask_value = (backgroundMask_value_buf as Color | number | string | Resource)
    }
    _PanelAttribute_showCloseIcon(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<PanelInterface>(ptr)
        node.showCloseIcon_value = value
    }
    _PanelAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PanelInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onChange_value = thisDeserializer.readCallback_Number_Number_PanelMode_Void()
    }
    _PanelAttribute_onHeightChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PanelInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onHeightChange_value = thisDeserializer.readCallback_Number_Void()
    }
    _PasteButtonInterface_setPasteButtonOptions0(ptr: KPointer): void {
        let node = this.ptr2object<PasteButtonInterface>(ptr)
    }
    _PasteButtonInterface_setPasteButtonOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PasteButtonInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setPasteButtonOptions1_options = thisDeserializer.readPasteButtonOptions()
    }
    _PasteButtonAttribute_onClick(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PasteButtonInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onClick_value = thisDeserializer.readCallback_ClickEvent_PasteButtonOnClickResult_Void()
    }
    _PathInterface_setPathOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PathInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setPathOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setPathOptions_options_buf: PathOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setPathOptions_options_buf_runtimeType))
        {
            setPathOptions_options_buf = thisDeserializer.readPathOptions()
        }
        node.setPathOptions_options = setPathOptions_options_buf
    }
    _PathAttribute_commands(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<PathInterface>(ptr)
        node.commands_value = value
    }
    _PatternLockInterface_setPatternLockOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PatternLockInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setPatternLockOptions_controller_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setPatternLockOptions_controller_buf: PatternLockController | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setPatternLockOptions_controller_buf_runtimeType))
        {
            setPatternLockOptions_controller_buf = (thisDeserializer.readPatternLockController() as PatternLockController)
        }
        node.setPatternLockOptions_controller = setPatternLockOptions_controller_buf
    }
    _PatternLockAttribute_sideLength(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<PatternLockInterface>(ptr)
        node.sideLength_value = value
    }
    _PatternLockAttribute_circleRadius(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<PatternLockInterface>(ptr)
        node.circleRadius_value = value
    }
    _PatternLockAttribute_backgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PatternLockInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const backgroundColor_value_buf_selector: number = thisDeserializer.readInt8()
        let backgroundColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (backgroundColor_value_buf_selector == 0) {
            backgroundColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (backgroundColor_value_buf_selector == 1) {
            backgroundColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (backgroundColor_value_buf_selector == 2) {
            backgroundColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (backgroundColor_value_buf_selector == 3) {
            backgroundColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for backgroundColor_value_buf has to be chosen through deserialisation.")
        }
        node.backgroundColor_value = (backgroundColor_value_buf as Color | number | string | Resource)
    }
    _PatternLockAttribute_regularColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PatternLockInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const regularColor_value_buf_selector: number = thisDeserializer.readInt8()
        let regularColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (regularColor_value_buf_selector == 0) {
            regularColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (regularColor_value_buf_selector == 1) {
            regularColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (regularColor_value_buf_selector == 2) {
            regularColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (regularColor_value_buf_selector == 3) {
            regularColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for regularColor_value_buf has to be chosen through deserialisation.")
        }
        node.regularColor_value = (regularColor_value_buf as Color | number | string | Resource)
    }
    _PatternLockAttribute_selectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PatternLockInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const selectedColor_value_buf_selector: number = thisDeserializer.readInt8()
        let selectedColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (selectedColor_value_buf_selector == 0) {
            selectedColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (selectedColor_value_buf_selector == 1) {
            selectedColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (selectedColor_value_buf_selector == 2) {
            selectedColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (selectedColor_value_buf_selector == 3) {
            selectedColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for selectedColor_value_buf has to be chosen through deserialisation.")
        }
        node.selectedColor_value = (selectedColor_value_buf as Color | number | string | Resource)
    }
    _PatternLockAttribute_activeColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PatternLockInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const activeColor_value_buf_selector: number = thisDeserializer.readInt8()
        let activeColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (activeColor_value_buf_selector == 0) {
            activeColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (activeColor_value_buf_selector == 1) {
            activeColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (activeColor_value_buf_selector == 2) {
            activeColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (activeColor_value_buf_selector == 3) {
            activeColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for activeColor_value_buf has to be chosen through deserialisation.")
        }
        node.activeColor_value = (activeColor_value_buf as Color | number | string | Resource)
    }
    _PatternLockAttribute_pathColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PatternLockInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const pathColor_value_buf_selector: number = thisDeserializer.readInt8()
        let pathColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (pathColor_value_buf_selector == 0) {
            pathColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (pathColor_value_buf_selector == 1) {
            pathColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (pathColor_value_buf_selector == 2) {
            pathColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (pathColor_value_buf_selector == 3) {
            pathColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for pathColor_value_buf has to be chosen through deserialisation.")
        }
        node.pathColor_value = (pathColor_value_buf as Color | number | string | Resource)
    }
    _PatternLockAttribute_pathStrokeWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PatternLockInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const pathStrokeWidth_value_buf_selector: number = thisDeserializer.readInt8()
        let pathStrokeWidth_value_buf: number | string | undefined|undefined 
        if (pathStrokeWidth_value_buf_selector == 0) {
            pathStrokeWidth_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (pathStrokeWidth_value_buf_selector == 1) {
            pathStrokeWidth_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for pathStrokeWidth_value_buf has to be chosen through deserialisation.")
        }
        node.pathStrokeWidth_value = (pathStrokeWidth_value_buf as number | string)
    }
    _PatternLockAttribute_onPatternComplete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PatternLockInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onPatternComplete_value = thisDeserializer.readCallback_Array_Number_Void()
    }
    _PatternLockAttribute_autoReset(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<PatternLockInterface>(ptr)
        node.autoReset_value = value
    }
    _PatternLockAttribute_onDotConnect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PatternLockInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDotConnect_value = thisDeserializer.readCallback_Number_Void()
    }
    _PatternLockAttribute_activateCircleStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PatternLockInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const activateCircleStyle_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let activateCircleStyle_value_buf: CircleStyleOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (activateCircleStyle_value_buf_runtimeType))
        {
            activateCircleStyle_value_buf = thisDeserializer.readCircleStyleOptions()
        }
        node.activateCircleStyle_value = activateCircleStyle_value_buf
    }
    _PluginComponentInterface_setPluginComponentOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PluginComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setPluginComponentOptions_options = thisDeserializer.readPluginComponentOptions()
    }
    _PluginComponentAttribute_onComplete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PluginComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onComplete_value = thisDeserializer.readVoidCallback()
    }
    _PluginComponentAttribute_onError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PluginComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onError_value = thisDeserializer.readPluginErrorCallback()
    }
    _PolygonInterface_setPolygonOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PolygonInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setPolygonOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setPolygonOptions_options_buf: PolygonOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setPolygonOptions_options_buf_runtimeType))
        {
            setPolygonOptions_options_buf = thisDeserializer.readPolygonOptions()
        }
        node.setPolygonOptions_options = setPolygonOptions_options_buf
    }
    _PolygonAttribute_points(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PolygonInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const points_value_buf_length: int32 = thisDeserializer.readInt32()
        let points_value_buf: Array<any> = new Array<any>()
        for (let points_value_buf_i = 0; points_value_buf_i < points_value_buf_length; points_value_buf_i++) {
            points_value_buf[points_value_buf_i] = (thisDeserializer.readCustomObject("Any") as Object)
        }
        node.points_value = points_value_buf
    }
    _PolylineInterface_setPolylineOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PolylineInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setPolylineOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setPolylineOptions_options_buf: PolylineOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setPolylineOptions_options_buf_runtimeType))
        {
            setPolylineOptions_options_buf = thisDeserializer.readPolylineOptions()
        }
        node.setPolylineOptions_options = setPolylineOptions_options_buf
    }
    _PolylineAttribute_points(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<PolylineInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const points_value_buf_length: int32 = thisDeserializer.readInt32()
        let points_value_buf: Array<any> = new Array<any>()
        for (let points_value_buf_i = 0; points_value_buf_i < points_value_buf_length; points_value_buf_i++) {
            points_value_buf[points_value_buf_i] = (thisDeserializer.readCustomObject("Any") as Object)
        }
        node.points_value = points_value_buf
    }
    _ProgressInterface_setProgressOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ProgressInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setProgressOptions_options = thisDeserializer.readProgressOptions()
    }
    _ProgressAttribute_value(ptr: KPointer, value: number): void {
        let node = this.ptr2object<ProgressInterface>(ptr)
        node.value_value = value
    }
    _ProgressAttribute_color(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ProgressInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const color_value_buf_selector: number = thisDeserializer.readInt8()
        let color_value_buf: ResourceColor | LinearGradient_common | undefined|undefined 
        if (color_value_buf_selector == 0) {
            const color_value_buf_u_selector: number = thisDeserializer.readInt8()
            let color_value_buf_u: Color | number | string | Resource | undefined|undefined 
            if (color_value_buf_u_selector == 0) {
                color_value_buf_u = (thisDeserializer.readInt32() as Color)
            }
            else if (color_value_buf_u_selector == 1) {
                color_value_buf_u = (thisDeserializer.readNumber() as number)
            }
            else if (color_value_buf_u_selector == 2) {
                color_value_buf_u = (thisDeserializer.readString() as string)
            }
            else if (color_value_buf_u_selector == 3) {
                color_value_buf_u = thisDeserializer.readResource()
            }
            else {
                throw new Error("One of the branches for color_value_buf_u has to be chosen through deserialisation.")
            }
            color_value_buf = (color_value_buf_u as Color | number | string | Resource)
        }
        else if (color_value_buf_selector == 1) {
            color_value_buf = thisDeserializer.readLinearGradient_common()
        }
        else {
            throw new Error("One of the branches for color_value_buf has to be chosen through deserialisation.")
        }
        node.color_value = (color_value_buf as ResourceColor | LinearGradient_common)
    }
    _ProgressAttribute_style(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ProgressInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const style_value_buf_selector: number = thisDeserializer.readInt8()
        let style_value_buf: LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined|undefined 
        if (style_value_buf_selector == 0) {
            style_value_buf = thisDeserializer.readLinearStyleOptions()
        }
        else if (style_value_buf_selector == 1) {
            style_value_buf = thisDeserializer.readRingStyleOptions()
        }
        else if (style_value_buf_selector == 2) {
            style_value_buf = thisDeserializer.readCapsuleStyleOptions()
        }
        else if (style_value_buf_selector == 3) {
            style_value_buf = thisDeserializer.readProgressStyleOptions()
        }
        else {
            throw new Error("One of the branches for style_value_buf has to be chosen through deserialisation.")
        }
        node.style_value = (style_value_buf as LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions)
    }
    _ProgressAttribute_privacySensitive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ProgressInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const privacySensitive_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let privacySensitive_value_buf: boolean | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (privacySensitive_value_buf_runtimeType))
        {
            privacySensitive_value_buf = thisDeserializer.readBoolean()
        }
        node.privacySensitive_value = privacySensitive_value_buf
    }
    _ProgressAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ProgressInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.contentModifier_value = (thisDeserializer.readCustomObject("ContentModifier") as ContentModifier<any>)
    }
    _QRCodeInterface_setQRCodeOptions(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<QRCodeInterface>(ptr)
        node.setQRCodeOptions_value = value
    }
    _QRCodeAttribute_color(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<QRCodeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const color_value_buf_selector: number = thisDeserializer.readInt8()
        let color_value_buf: Color | number | string | Resource | undefined|undefined 
        if (color_value_buf_selector == 0) {
            color_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (color_value_buf_selector == 1) {
            color_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (color_value_buf_selector == 2) {
            color_value_buf = (thisDeserializer.readString() as string)
        }
        else if (color_value_buf_selector == 3) {
            color_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for color_value_buf has to be chosen through deserialisation.")
        }
        node.color_value = (color_value_buf as Color | number | string | Resource)
    }
    _QRCodeAttribute_backgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<QRCodeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const backgroundColor_value_buf_selector: number = thisDeserializer.readInt8()
        let backgroundColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (backgroundColor_value_buf_selector == 0) {
            backgroundColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (backgroundColor_value_buf_selector == 1) {
            backgroundColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (backgroundColor_value_buf_selector == 2) {
            backgroundColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (backgroundColor_value_buf_selector == 3) {
            backgroundColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for backgroundColor_value_buf has to be chosen through deserialisation.")
        }
        node.backgroundColor_value = (backgroundColor_value_buf as Color | number | string | Resource)
    }
    _QRCodeAttribute_contentOpacity(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<QRCodeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const contentOpacity_value_buf_selector: number = thisDeserializer.readInt8()
        let contentOpacity_value_buf: number | Resource | undefined|undefined 
        if (contentOpacity_value_buf_selector == 0) {
            contentOpacity_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (contentOpacity_value_buf_selector == 1) {
            contentOpacity_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for contentOpacity_value_buf has to be chosen through deserialisation.")
        }
        node.contentOpacity_value = (contentOpacity_value_buf as number | Resource)
    }
    _RadioInterface_setRadioOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RadioInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setRadioOptions_options = thisDeserializer.readRadioOptions()
    }
    _RadioAttribute_checked(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<RadioInterface>(ptr)
        node.checked_value = value
    }
    _RadioAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RadioInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onChange_value = thisDeserializer.readCallback_Boolean_Void()
    }
    _RadioAttribute_radioStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RadioInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const radioStyle_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let radioStyle_value_buf: RadioStyle | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (radioStyle_value_buf_runtimeType))
        {
            radioStyle_value_buf = thisDeserializer.readRadioStyle()
        }
        node.radioStyle_value = radioStyle_value_buf
    }
    _RadioAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RadioInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.contentModifier_value = (thisDeserializer.readCustomObject("ContentModifier") as ContentModifier<any>)
    }
    _RatingInterface_setRatingOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RatingInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setRatingOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setRatingOptions_options_buf: RatingOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setRatingOptions_options_buf_runtimeType))
        {
            setRatingOptions_options_buf = thisDeserializer.readRatingOptions()
        }
        node.setRatingOptions_options = setRatingOptions_options_buf
    }
    _RatingAttribute_stars(ptr: KPointer, value: number): void {
        let node = this.ptr2object<RatingInterface>(ptr)
        node.stars_value = value
    }
    _RatingAttribute_stepSize(ptr: KPointer, value: number): void {
        let node = this.ptr2object<RatingInterface>(ptr)
        node.stepSize_value = value
    }
    _RatingAttribute_starStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RatingInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.starStyle_value = thisDeserializer.readStarStyleOptions()
    }
    _RatingAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RatingInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onChange_value = thisDeserializer.readCallback_Number_Void()
    }
    _RatingAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RatingInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.contentModifier_value = (thisDeserializer.readCustomObject("ContentModifier") as ContentModifier<any>)
    }
    _RectInterface_setRectOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RectInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setRectOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setRectOptions_options_buf: RectOptions | RoundedRectOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setRectOptions_options_buf_runtimeType))
        {
            const setRectOptions_options_buf__selector: number = thisDeserializer.readInt8()
            let setRectOptions_options_buf_: RectOptions | RoundedRectOptions | undefined|undefined 
            if (setRectOptions_options_buf__selector == 0) {
                setRectOptions_options_buf_ = thisDeserializer.readRectOptions()
            }
            else if (setRectOptions_options_buf__selector == 1) {
                setRectOptions_options_buf_ = thisDeserializer.readRoundedRectOptions()
            }
            else {
                throw new Error("One of the branches for setRectOptions_options_buf_ has to be chosen through deserialisation.")
            }
            setRectOptions_options_buf = (setRectOptions_options_buf_ as RectOptions | RoundedRectOptions)
        }
        node.setRectOptions_options = setRectOptions_options_buf
    }
    _RectAttribute_radiusWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RectInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const radiusWidth_value_buf_selector: number = thisDeserializer.readInt8()
        let radiusWidth_value_buf: number | string | undefined|undefined 
        if (radiusWidth_value_buf_selector == 0) {
            radiusWidth_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (radiusWidth_value_buf_selector == 1) {
            radiusWidth_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for radiusWidth_value_buf has to be chosen through deserialisation.")
        }
        node.radiusWidth_value = (radiusWidth_value_buf as number | string)
    }
    _RectAttribute_radiusHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RectInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const radiusHeight_value_buf_selector: number = thisDeserializer.readInt8()
        let radiusHeight_value_buf: number | string | undefined|undefined 
        if (radiusHeight_value_buf_selector == 0) {
            radiusHeight_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (radiusHeight_value_buf_selector == 1) {
            radiusHeight_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for radiusHeight_value_buf has to be chosen through deserialisation.")
        }
        node.radiusHeight_value = (radiusHeight_value_buf as number | string)
    }
    _RectAttribute_radius(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RectInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const radius_value_buf_selector: number = thisDeserializer.readInt8()
        let radius_value_buf: number | string | Array<any> | undefined|undefined 
        if (radius_value_buf_selector == 0) {
            radius_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (radius_value_buf_selector == 1) {
            radius_value_buf = (thisDeserializer.readString() as string)
        }
        else if (radius_value_buf_selector == 2) {
            const radius_value_buf_u_length: int32 = thisDeserializer.readInt32()
            let radius_value_buf_u: Array<any> = new Array<any>()
            for (let radius_value_buf_u_i = 0; radius_value_buf_u_i < radius_value_buf_u_length; radius_value_buf_u_i++) {
                radius_value_buf_u[radius_value_buf_u_i] = (thisDeserializer.readCustomObject("Any") as Object)
            }
            radius_value_buf = radius_value_buf_u
        }
        else {
            throw new Error("One of the branches for radius_value_buf has to be chosen through deserialisation.")
        }
        node.radius_value = (radius_value_buf as number | string | Array<any>)
    }
    _RefreshInterface_setRefreshOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RefreshInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setRefreshOptions_value = thisDeserializer.readRefreshOptions()
    }
    _RefreshAttribute_onStateChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RefreshInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onStateChange_value = thisDeserializer.readCallback_RefreshStatus_Void()
    }
    _RefreshAttribute_onRefreshing(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RefreshInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onRefreshing_value = thisDeserializer.readCallback_Void()
    }
    _RefreshAttribute_refreshOffset(ptr: KPointer, value: number): void {
        let node = this.ptr2object<RefreshInterface>(ptr)
        node.refreshOffset_value = value
    }
    _RefreshAttribute_pullToRefresh(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<RefreshInterface>(ptr)
        node.pullToRefresh_value = value
    }
    _RefreshAttribute_onOffsetChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RefreshInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onOffsetChange_value = thisDeserializer.readCallback_Number_Void()
    }
    _RefreshAttribute_pullDownRatio(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RefreshInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const pullDownRatio_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let pullDownRatio_value_buf: number | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (pullDownRatio_value_buf_runtimeType))
        {
            pullDownRatio_value_buf = (thisDeserializer.readNumber() as number)
        }
        node.pullDownRatio_value = pullDownRatio_value_buf
    }
    _RelativeContainerInterface_setRelativeContainerOptions(ptr: KPointer): void {
        let node = this.ptr2object<RelativeContainerInterface>(ptr)
    }
    _RelativeContainerAttribute_guideLine(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RelativeContainerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const guideLine_value_buf_length: int32 = thisDeserializer.readInt32()
        let guideLine_value_buf: Array<GuideLineStyle> = new Array<GuideLineStyle>()
        for (let guideLine_value_buf_i = 0; guideLine_value_buf_i < guideLine_value_buf_length; guideLine_value_buf_i++) {
            guideLine_value_buf[guideLine_value_buf_i] = thisDeserializer.readGuideLineStyle()
        }
        node.guideLine_value = guideLine_value_buf
    }
    _RelativeContainerAttribute_barrier0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RelativeContainerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const barrier0_value_buf_length: int32 = thisDeserializer.readInt32()
        let barrier0_value_buf: Array<BarrierStyle> = new Array<BarrierStyle>()
        for (let barrier0_value_buf_i = 0; barrier0_value_buf_i < barrier0_value_buf_length; barrier0_value_buf_i++) {
            barrier0_value_buf[barrier0_value_buf_i] = thisDeserializer.readBarrierStyle()
        }
        node.barrier0_value = barrier0_value_buf
    }
    _RelativeContainerAttribute_barrier1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RelativeContainerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const barrier1_value_buf_length: int32 = thisDeserializer.readInt32()
        let barrier1_value_buf: Array<LocalizedBarrierStyle> = new Array<LocalizedBarrierStyle>()
        for (let barrier1_value_buf_i = 0; barrier1_value_buf_i < barrier1_value_buf_length; barrier1_value_buf_i++) {
            barrier1_value_buf[barrier1_value_buf_i] = thisDeserializer.readLocalizedBarrierStyle()
        }
        node.barrier1_value = barrier1_value_buf
    }
    _RichEditorInterface_setRichEditorOptions0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setRichEditorOptions0_value = thisDeserializer.readRichEditorOptions()
    }
    _RichEditorInterface_setRichEditorOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setRichEditorOptions1_options = thisDeserializer.readRichEditorStyledStringOptions()
    }
    _RichEditorAttribute_onReady(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onReady_value = thisDeserializer.readCallback_Void()
    }
    _RichEditorAttribute_onSelect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSelect_value = thisDeserializer.readCallback_RichEditorSelection_Void()
    }
    _RichEditorAttribute_onSelectionChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSelectionChange_value = thisDeserializer.readCallback_RichEditorRange_Void()
    }
    _RichEditorAttribute_aboutToIMEInput(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.aboutToIMEInput_value = thisDeserializer.readCallback_RichEditorInsertValue_Boolean()
    }
    _RichEditorAttribute_onIMEInputComplete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onIMEInputComplete_value = thisDeserializer.readCallback_RichEditorTextSpanResult_Void()
    }
    _RichEditorAttribute_onDidIMEInput(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDidIMEInput_value = thisDeserializer.readCallback_TextRange_Void()
    }
    _RichEditorAttribute_aboutToDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.aboutToDelete_value = thisDeserializer.readCallback_RichEditorDeleteValue_Boolean()
    }
    _RichEditorAttribute_onDeleteComplete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDeleteComplete_value = thisDeserializer.readCallback_Void()
    }
    _RichEditorAttribute_copyOptions(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        node.copyOptions_value = value
    }
    _RichEditorAttribute_onPaste(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onPaste_value = thisDeserializer.readPasteEventCallback()
    }
    _RichEditorAttribute_enableDataDetector(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        node.enableDataDetector_value = value
    }
    _RichEditorAttribute_enablePreviewText(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        node.enablePreviewText_value = value
    }
    _RichEditorAttribute_dataDetectorConfig(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.dataDetectorConfig_value = thisDeserializer.readTextDataDetectorConfig()
    }
    _RichEditorAttribute_caretColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const caretColor_value_buf_selector: number = thisDeserializer.readInt8()
        let caretColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (caretColor_value_buf_selector == 0) {
            caretColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (caretColor_value_buf_selector == 1) {
            caretColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (caretColor_value_buf_selector == 2) {
            caretColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (caretColor_value_buf_selector == 3) {
            caretColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for caretColor_value_buf has to be chosen through deserialisation.")
        }
        node.caretColor_value = (caretColor_value_buf as Color | number | string | Resource)
    }
    _RichEditorAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const selectedBackgroundColor_value_buf_selector: number = thisDeserializer.readInt8()
        let selectedBackgroundColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (selectedBackgroundColor_value_buf_selector == 0) {
            selectedBackgroundColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (selectedBackgroundColor_value_buf_selector == 1) {
            selectedBackgroundColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (selectedBackgroundColor_value_buf_selector == 2) {
            selectedBackgroundColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (selectedBackgroundColor_value_buf_selector == 3) {
            selectedBackgroundColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for selectedBackgroundColor_value_buf has to be chosen through deserialisation.")
        }
        node.selectedBackgroundColor_value = (selectedBackgroundColor_value_buf as Color | number | string | Resource)
    }
    _RichEditorAttribute_onEditingChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onEditingChange_value = thisDeserializer.readCallback_Boolean_Void()
    }
    _RichEditorAttribute_enterKeyType(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        node.enterKeyType_value = value
    }
    _RichEditorAttribute_onSubmit(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSubmit_value = thisDeserializer.readSubmitCallback()
    }
    _RichEditorAttribute_onWillChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onWillChange_value = thisDeserializer.readCallback_RichEditorChangeValue_Boolean()
    }
    _RichEditorAttribute_onDidChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDidChange_value = thisDeserializer.readOnDidChangeCallback()
    }
    _RichEditorAttribute_onCut(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onCut_value = thisDeserializer.readCallback_CutEvent_Void()
    }
    _RichEditorAttribute_onCopy(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onCopy_value = thisDeserializer.readCallback_CopyEvent_Void()
    }
    _RichEditorAttribute_editMenuOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.editMenuOptions_value = (thisDeserializer.readEditMenuOptions() as EditMenuOptions)
    }
    _RichEditorAttribute_enableKeyboardOnFocus(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        node.enableKeyboardOnFocus_value = value
    }
    _RichEditorAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        node.enableHapticFeedback_value = value
    }
    _RichEditorAttribute_barState(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        node.barState_value = value
    }
    _RichEditorAttribute_bindSelectionMenu(ptr: KPointer, spanType: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        node.bindSelectionMenu_spanType = spanType
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.bindSelectionMenu_content = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
        const bindSelectionMenu_responseType_buf_selector: number = thisDeserializer.readInt8()
        let bindSelectionMenu_responseType_buf: ResponseType | RichEditorResponseType | undefined|undefined 
        if (bindSelectionMenu_responseType_buf_selector == 0) {
            bindSelectionMenu_responseType_buf = (thisDeserializer.readInt32() as ResponseType)
        }
        else if (bindSelectionMenu_responseType_buf_selector == 1) {
            bindSelectionMenu_responseType_buf = (thisDeserializer.readInt32() as RichEditorResponseType)
        }
        else {
            throw new Error("One of the branches for bindSelectionMenu_responseType_buf has to be chosen through deserialisation.")
        }
        node.bindSelectionMenu_responseType = (bindSelectionMenu_responseType_buf as ResponseType | RichEditorResponseType)
        const bindSelectionMenu_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let bindSelectionMenu_options_buf: SelectionMenuOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (bindSelectionMenu_options_buf_runtimeType))
        {
            bindSelectionMenu_options_buf = thisDeserializer.readSelectionMenuOptions()
        }
        node.bindSelectionMenu_options = bindSelectionMenu_options_buf
    }
    _RichEditorAttribute_customKeyboard(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.customKeyboard_value = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
        const customKeyboard_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let customKeyboard_options_buf: KeyboardOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (customKeyboard_options_buf_runtimeType))
        {
            customKeyboard_options_buf = thisDeserializer.readKeyboardOptions()
        }
        node.customKeyboard_options = customKeyboard_options_buf
    }
    _RichEditorAttribute_placeholder(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichEditorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const placeholder_value_buf_selector: number = thisDeserializer.readInt8()
        let placeholder_value_buf: string | Resource | undefined|undefined 
        if (placeholder_value_buf_selector == 0) {
            placeholder_value_buf = (thisDeserializer.readString() as string)
        }
        else if (placeholder_value_buf_selector == 1) {
            placeholder_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for placeholder_value_buf has to be chosen through deserialisation.")
        }
        node.placeholder_value = (placeholder_value_buf as string | Resource)
        const placeholder_style_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let placeholder_style_buf: PlaceholderStyle | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (placeholder_style_buf_runtimeType))
        {
            placeholder_style_buf = thisDeserializer.readPlaceholderStyle()
        }
        node.placeholder_style = placeholder_style_buf
    }
    _RichTextInterface_setRichTextOptions(ptr: KPointer, content: KStringPtr): void {
        let node = this.ptr2object<RichTextInterface>(ptr)
        node.setRichTextOptions_content = content
    }
    _RichTextAttribute_onStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichTextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onStart_value = thisDeserializer.readCallback_Void()
    }
    _RichTextAttribute_onComplete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RichTextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onComplete_value = thisDeserializer.readCallback_Void()
    }
    _RootSceneInterface_setRootSceneOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RootSceneInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setRootSceneOptions_session = thisDeserializer.readRootSceneSession()
    }
    _RowInterface_setRowOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RowInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setRowOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setRowOptions_options_buf: RowOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setRowOptions_options_buf_runtimeType))
        {
            setRowOptions_options_buf = thisDeserializer.readRowOptions()
        }
        node.setRowOptions_options = setRowOptions_options_buf
    }
    _RowAttribute_alignItems(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<RowInterface>(ptr)
        node.alignItems_value = value
    }
    _RowAttribute_justifyContent(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<RowInterface>(ptr)
        node.justifyContent_value = value
    }
    _RowAttribute_pointLight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RowInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.pointLight_value = thisDeserializer.readPointLightStyle()
    }
    _RowAttribute_reverse(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RowInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const reverse_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let reverse_value_buf: boolean | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (reverse_value_buf_runtimeType))
        {
            reverse_value_buf = thisDeserializer.readBoolean()
        }
        node.reverse_value = reverse_value_buf
    }
    _RowSplitInterface_setRowSplitOptions(ptr: KPointer): void {
        let node = this.ptr2object<RowSplitInterface>(ptr)
    }
    _RowSplitAttribute_resizeable(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<RowSplitInterface>(ptr)
        node.resizeable_value = value
    }
    _SaveButtonInterface_setSaveButtonOptions0(ptr: KPointer): void {
        let node = this.ptr2object<SaveButtonInterface>(ptr)
    }
    _SaveButtonInterface_setSaveButtonOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SaveButtonInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setSaveButtonOptions1_options = thisDeserializer.readSaveButtonOptions()
    }
    _SaveButtonAttribute_onClick(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SaveButtonInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onClick_value = thisDeserializer.readCallback_ClickEvent_SaveButtonOnClickResult_Void()
    }
    _ScreenInterface_setScreenOptions(ptr: KPointer, screenId: number): void {
        let node = this.ptr2object<ScreenInterface>(ptr)
        node.setScreenOptions_screenId = screenId
    }
    _ScrollInterface_setScrollOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setScrollOptions_scroller_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setScrollOptions_scroller_buf: Scroller | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setScrollOptions_scroller_buf_runtimeType))
        {
            setScrollOptions_scroller_buf = (thisDeserializer.readScroller() as Scroller)
        }
        node.setScrollOptions_scroller = setScrollOptions_scroller_buf
    }
    _ScrollAttribute_scrollable(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ScrollInterface>(ptr)
        node.scrollable_value = value
    }
    _ScrollAttribute_onScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScroll_value = thisDeserializer.readCallback_Number_ScrollState_Void()
    }
    _ScrollAttribute_onWillScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const onWillScroll_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let onWillScroll_value_buf: ScrollOnWillScrollCallback | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (onWillScroll_value_buf_runtimeType))
        {
            onWillScroll_value_buf = thisDeserializer.readScrollOnWillScrollCallback()
        }
        node.onWillScroll_value = onWillScroll_value_buf
    }
    _ScrollAttribute_onDidScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const onDidScroll_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let onDidScroll_value_buf: ScrollOnWillScrollCallback | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (onDidScroll_value_buf_runtimeType))
        {
            onDidScroll_value_buf = thisDeserializer.readScrollOnWillScrollCallback()
        }
        node.onDidScroll_value = onDidScroll_value_buf
    }
    _ScrollAttribute_onScrollEdge(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScrollEdge_value = thisDeserializer.readOnScrollEdgeCallback()
    }
    _ScrollAttribute_onScrollStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScrollStart_value = thisDeserializer.readCallback_Void()
    }
    _ScrollAttribute_onScrollEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScrollEnd_value = thisDeserializer.readCallback_Void()
    }
    _ScrollAttribute_onScrollStop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScrollStop_value = thisDeserializer.readCallback_Void()
    }
    _ScrollAttribute_scrollBar(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ScrollInterface>(ptr)
        node.scrollBar_value = value
    }
    _ScrollAttribute_scrollBarColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const scrollBarColor_value_buf_selector: number = thisDeserializer.readInt8()
        let scrollBarColor_value_buf: Color | number | string | undefined|undefined 
        if (scrollBarColor_value_buf_selector == 0) {
            scrollBarColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (scrollBarColor_value_buf_selector == 1) {
            scrollBarColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (scrollBarColor_value_buf_selector == 2) {
            scrollBarColor_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for scrollBarColor_value_buf has to be chosen through deserialisation.")
        }
        node.scrollBarColor_value = (scrollBarColor_value_buf as Color | number | string)
    }
    _ScrollAttribute_scrollBarWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const scrollBarWidth_value_buf_selector: number = thisDeserializer.readInt8()
        let scrollBarWidth_value_buf: number | string | undefined|undefined 
        if (scrollBarWidth_value_buf_selector == 0) {
            scrollBarWidth_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (scrollBarWidth_value_buf_selector == 1) {
            scrollBarWidth_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for scrollBarWidth_value_buf has to be chosen through deserialisation.")
        }
        node.scrollBarWidth_value = (scrollBarWidth_value_buf as number | string)
    }
    _ScrollAttribute_onScrollFrameBegin(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScrollFrameBegin_value = thisDeserializer.readOnScrollFrameBeginCallback()
    }
    _ScrollAttribute_nestedScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.nestedScroll_value = thisDeserializer.readNestedScrollOptions()
    }
    _ScrollAttribute_enableScrollInteraction(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ScrollInterface>(ptr)
        node.enableScrollInteraction_value = value
    }
    _ScrollAttribute_friction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const friction_value_buf_selector: number = thisDeserializer.readInt8()
        let friction_value_buf: number | Resource | undefined|undefined 
        if (friction_value_buf_selector == 0) {
            friction_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (friction_value_buf_selector == 1) {
            friction_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for friction_value_buf has to be chosen through deserialisation.")
        }
        node.friction_value = (friction_value_buf as number | Resource)
    }
    _ScrollAttribute_scrollSnap(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.scrollSnap_value = thisDeserializer.readScrollSnapOptions()
    }
    _ScrollAttribute_enablePaging(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ScrollInterface>(ptr)
        node.enablePaging_value = value
    }
    _ScrollAttribute_initialOffset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.initialOffset_value = thisDeserializer.readOffsetOptions()
    }
    _ScrollAttribute_edgeEffect(ptr: KPointer, edgeEffect: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollInterface>(ptr)
        node.edgeEffect_edgeEffect = edgeEffect
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const edgeEffect_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let edgeEffect_options_buf: EdgeEffectOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (edgeEffect_options_buf_runtimeType))
        {
            edgeEffect_options_buf = thisDeserializer.readEdgeEffectOptions()
        }
        node.edgeEffect_options = edgeEffect_options_buf
    }
    _ScrollBarInterface_setScrollBarOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollBarInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setScrollBarOptions_value = thisDeserializer.readScrollBarOptions()
    }
    _ScrollBarAttribute_enableNestedScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ScrollBarInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const enableNestedScroll_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let enableNestedScroll_value_buf: boolean | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (enableNestedScroll_value_buf_runtimeType))
        {
            enableNestedScroll_value_buf = thisDeserializer.readBoolean()
        }
        node.enableNestedScroll_value = enableNestedScroll_value_buf
    }
    _SearchInterface_setSearchOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setSearchOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setSearchOptions_options_buf: SearchOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setSearchOptions_options_buf_runtimeType))
        {
            setSearchOptions_options_buf = thisDeserializer.readSearchOptions()
        }
        node.setSearchOptions_options = setSearchOptions_options_buf
    }
    _SearchAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontColor_value_buf_selector: number = thisDeserializer.readInt8()
        let fontColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (fontColor_value_buf_selector == 0) {
            fontColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (fontColor_value_buf_selector == 1) {
            fontColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontColor_value_buf_selector == 2) {
            fontColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontColor_value_buf_selector == 3) {
            fontColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontColor_value_buf has to be chosen through deserialisation.")
        }
        node.fontColor_value = (fontColor_value_buf as Color | number | string | Resource)
    }
    _SearchAttribute_searchIcon(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const searchIcon_value_buf_selector: number = thisDeserializer.readInt8()
        let searchIcon_value_buf: IconOptions | SymbolGlyphModifier | undefined|undefined 
        if (searchIcon_value_buf_selector == 0) {
            searchIcon_value_buf = thisDeserializer.readIconOptions()
        }
        else if (searchIcon_value_buf_selector == 1) {
            searchIcon_value_buf = thisDeserializer.readSymbolGlyphModifier()
        }
        else {
            throw new Error("One of the branches for searchIcon_value_buf has to be chosen through deserialisation.")
        }
        node.searchIcon_value = (searchIcon_value_buf as IconOptions | SymbolGlyphModifier)
    }
    _SearchAttribute_cancelButton(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const cancelButton_value_buf_selector: number = thisDeserializer.readInt8()
        let cancelButton_value_buf: CancelButtonOptions | CancelButtonSymbolOptions | undefined|undefined 
        if (cancelButton_value_buf_selector == 0) {
            cancelButton_value_buf = thisDeserializer.readCancelButtonOptions()
        }
        else if (cancelButton_value_buf_selector == 1) {
            cancelButton_value_buf = thisDeserializer.readCancelButtonSymbolOptions()
        }
        else {
            throw new Error("One of the branches for cancelButton_value_buf has to be chosen through deserialisation.")
        }
        node.cancelButton_value = (cancelButton_value_buf as CancelButtonOptions | CancelButtonSymbolOptions)
    }
    _SearchAttribute_textIndent(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        node.textIndent_value = value
    }
    _SearchAttribute_onEditChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onEditChange_value = thisDeserializer.readCallback_Boolean_Void()
    }
    _SearchAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const selectedBackgroundColor_value_buf_selector: number = thisDeserializer.readInt8()
        let selectedBackgroundColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (selectedBackgroundColor_value_buf_selector == 0) {
            selectedBackgroundColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (selectedBackgroundColor_value_buf_selector == 1) {
            selectedBackgroundColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (selectedBackgroundColor_value_buf_selector == 2) {
            selectedBackgroundColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (selectedBackgroundColor_value_buf_selector == 3) {
            selectedBackgroundColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for selectedBackgroundColor_value_buf has to be chosen through deserialisation.")
        }
        node.selectedBackgroundColor_value = (selectedBackgroundColor_value_buf as Color | number | string | Resource)
    }
    _SearchAttribute_caretStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.caretStyle_value = thisDeserializer.readCaretStyle()
    }
    _SearchAttribute_placeholderColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const placeholderColor_value_buf_selector: number = thisDeserializer.readInt8()
        let placeholderColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (placeholderColor_value_buf_selector == 0) {
            placeholderColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (placeholderColor_value_buf_selector == 1) {
            placeholderColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (placeholderColor_value_buf_selector == 2) {
            placeholderColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (placeholderColor_value_buf_selector == 3) {
            placeholderColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for placeholderColor_value_buf has to be chosen through deserialisation.")
        }
        node.placeholderColor_value = (placeholderColor_value_buf as Color | number | string | Resource)
    }
    _SearchAttribute_placeholderFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const placeholderFont_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let placeholderFont_value_buf: Font | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (placeholderFont_value_buf_runtimeType))
        {
            placeholderFont_value_buf = thisDeserializer.readFont()
        }
        node.placeholderFont_value = placeholderFont_value_buf
    }
    _SearchAttribute_textFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const textFont_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let textFont_value_buf: Font | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (textFont_value_buf_runtimeType))
        {
            textFont_value_buf = thisDeserializer.readFont()
        }
        node.textFont_value = textFont_value_buf
    }
    _SearchAttribute_enterKeyType(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        node.enterKeyType_value = value
    }
    _SearchAttribute_onSubmit0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSubmit0_value = thisDeserializer.readCallback_String_Void()
    }
    _SearchAttribute_onSubmit1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSubmit1_value = thisDeserializer.readSearchSubmitCallback()
    }
    _SearchAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onChange_value = thisDeserializer.readEditableTextOnChangeCallback()
    }
    _SearchAttribute_onTextSelectionChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onTextSelectionChange_value = thisDeserializer.readOnTextSelectionChangeCallback()
    }
    _SearchAttribute_onContentScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onContentScroll_value = thisDeserializer.readOnContentScrollCallback()
    }
    _SearchAttribute_onCopy(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onCopy_value = thisDeserializer.readCallback_String_Void()
    }
    _SearchAttribute_onCut(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onCut_value = thisDeserializer.readCallback_String_Void()
    }
    _SearchAttribute_onPaste(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onPaste_value = thisDeserializer.readOnPasteCallback()
    }
    _SearchAttribute_copyOption(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        node.copyOption_value = value
    }
    _SearchAttribute_maxLength(ptr: KPointer, value: number): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        node.maxLength_value = value
    }
    _SearchAttribute_textAlign(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        node.textAlign_value = value
    }
    _SearchAttribute_enableKeyboardOnFocus(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        node.enableKeyboardOnFocus_value = value
    }
    _SearchAttribute_selectionMenuHidden(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        node.selectionMenuHidden_value = value
    }
    _SearchAttribute_minFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const minFontSize_value_buf_selector: number = thisDeserializer.readInt8()
        let minFontSize_value_buf: number | string | Resource | undefined|undefined 
        if (minFontSize_value_buf_selector == 0) {
            minFontSize_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (minFontSize_value_buf_selector == 1) {
            minFontSize_value_buf = (thisDeserializer.readString() as string)
        }
        else if (minFontSize_value_buf_selector == 2) {
            minFontSize_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for minFontSize_value_buf has to be chosen through deserialisation.")
        }
        node.minFontSize_value = (minFontSize_value_buf as number | string | Resource)
    }
    _SearchAttribute_maxFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const maxFontSize_value_buf_selector: number = thisDeserializer.readInt8()
        let maxFontSize_value_buf: number | string | Resource | undefined|undefined 
        if (maxFontSize_value_buf_selector == 0) {
            maxFontSize_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (maxFontSize_value_buf_selector == 1) {
            maxFontSize_value_buf = (thisDeserializer.readString() as string)
        }
        else if (maxFontSize_value_buf_selector == 2) {
            maxFontSize_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for maxFontSize_value_buf has to be chosen through deserialisation.")
        }
        node.maxFontSize_value = (maxFontSize_value_buf as number | string | Resource)
    }
    _SearchAttribute_decoration(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.decoration_value = thisDeserializer.readTextDecorationOptions()
    }
    _SearchAttribute_letterSpacing(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const letterSpacing_value_buf_selector: number = thisDeserializer.readInt8()
        let letterSpacing_value_buf: number | string | Resource | undefined|undefined 
        if (letterSpacing_value_buf_selector == 0) {
            letterSpacing_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (letterSpacing_value_buf_selector == 1) {
            letterSpacing_value_buf = (thisDeserializer.readString() as string)
        }
        else if (letterSpacing_value_buf_selector == 2) {
            letterSpacing_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for letterSpacing_value_buf has to be chosen through deserialisation.")
        }
        node.letterSpacing_value = (letterSpacing_value_buf as number | string | Resource)
    }
    _SearchAttribute_lineHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const lineHeight_value_buf_selector: number = thisDeserializer.readInt8()
        let lineHeight_value_buf: number | string | Resource | undefined|undefined 
        if (lineHeight_value_buf_selector == 0) {
            lineHeight_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (lineHeight_value_buf_selector == 1) {
            lineHeight_value_buf = (thisDeserializer.readString() as string)
        }
        else if (lineHeight_value_buf_selector == 2) {
            lineHeight_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for lineHeight_value_buf has to be chosen through deserialisation.")
        }
        node.lineHeight_value = (lineHeight_value_buf as number | string | Resource)
    }
    _SearchAttribute_type(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        node.type_value = value
    }
    _SearchAttribute_fontFeature(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        node.fontFeature_value = value
    }
    _SearchAttribute_onWillInsert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onWillInsert_value = thisDeserializer.readCallback_InsertValue_Boolean()
    }
    _SearchAttribute_onDidInsert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDidInsert_value = thisDeserializer.readCallback_InsertValue_Void()
    }
    _SearchAttribute_onWillDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onWillDelete_value = thisDeserializer.readCallback_DeleteValue_Boolean()
    }
    _SearchAttribute_onDidDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDidDelete_value = thisDeserializer.readCallback_DeleteValue_Void()
    }
    _SearchAttribute_editMenuOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.editMenuOptions_value = (thisDeserializer.readEditMenuOptions() as EditMenuOptions)
    }
    _SearchAttribute_enablePreviewText(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        node.enablePreviewText_value = value
    }
    _SearchAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        node.enableHapticFeedback_value = value
    }
    _SearchAttribute_searchButton(ptr: KPointer, value: KStringPtr, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        node.searchButton_value = value
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const searchButton_option_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let searchButton_option_buf: SearchButtonOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (searchButton_option_buf_runtimeType))
        {
            searchButton_option_buf = thisDeserializer.readSearchButtonOptions()
        }
        node.searchButton_option = searchButton_option_buf
    }
    _SearchAttribute_inputFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const inputFilter_value_buf_selector: number = thisDeserializer.readInt8()
        let inputFilter_value_buf: string | Resource | undefined|undefined 
        if (inputFilter_value_buf_selector == 0) {
            inputFilter_value_buf = (thisDeserializer.readString() as string)
        }
        else if (inputFilter_value_buf_selector == 1) {
            inputFilter_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for inputFilter_value_buf has to be chosen through deserialisation.")
        }
        node.inputFilter_value = (inputFilter_value_buf as string | Resource)
        const inputFilter_error_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let inputFilter_error_buf: ((breakpoints: string) => void) | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (inputFilter_error_buf_runtimeType))
        {
            inputFilter_error_buf = thisDeserializer.readCallback_String_Void()
        }
        node.inputFilter_error = inputFilter_error_buf
    }
    _SearchAttribute_customKeyboard(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SearchInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.customKeyboard_value = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
        const customKeyboard_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let customKeyboard_options_buf: KeyboardOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (customKeyboard_options_buf_runtimeType))
        {
            customKeyboard_options_buf = thisDeserializer.readKeyboardOptions()
        }
        node.customKeyboard_options = customKeyboard_options_buf
    }
    _SecurityComponentMethod_iconSize(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<SecurityComponentMethodInterface>(ptr)
        node.iconSize_value = value
    }
    _SecurityComponentMethod_layoutDirection(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SecurityComponentMethodInterface>(ptr)
        node.layoutDirection_value = value
    }
    _SecurityComponentMethod_position(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SecurityComponentMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.position_value = thisDeserializer.readPosition()
    }
    _SecurityComponentMethod_markAnchor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SecurityComponentMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.markAnchor_value = thisDeserializer.readPosition()
    }
    _SecurityComponentMethod_offset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SecurityComponentMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const offset_value_buf_selector: number = thisDeserializer.readInt8()
        let offset_value_buf: Position | Edges | LocalizedEdges | undefined|undefined 
        if (offset_value_buf_selector == 0) {
            offset_value_buf = thisDeserializer.readPosition()
        }
        else if (offset_value_buf_selector == 1) {
            offset_value_buf = thisDeserializer.readEdges()
        }
        else if (offset_value_buf_selector == 2) {
            offset_value_buf = thisDeserializer.readLocalizedEdges()
        }
        else {
            throw new Error("One of the branches for offset_value_buf has to be chosen through deserialisation.")
        }
        node.offset_value = (offset_value_buf as Position | Edges | LocalizedEdges)
    }
    _SecurityComponentMethod_fontSize(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<SecurityComponentMethodInterface>(ptr)
        node.fontSize_value = value
    }
    _SecurityComponentMethod_fontStyle(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SecurityComponentMethodInterface>(ptr)
        node.fontStyle_value = value
    }
    _SecurityComponentMethod_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SecurityComponentMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontWeight_value_buf_selector: number = thisDeserializer.readInt8()
        let fontWeight_value_buf: number | FontWeight | string | undefined|undefined 
        if (fontWeight_value_buf_selector == 0) {
            fontWeight_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontWeight_value_buf_selector == 1) {
            fontWeight_value_buf = (thisDeserializer.readInt32() as FontWeight)
        }
        else if (fontWeight_value_buf_selector == 2) {
            fontWeight_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for fontWeight_value_buf has to be chosen through deserialisation.")
        }
        node.fontWeight_value = (fontWeight_value_buf as number | FontWeight | string)
    }
    _SecurityComponentMethod_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SecurityComponentMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontFamily_value_buf_selector: number = thisDeserializer.readInt8()
        let fontFamily_value_buf: string | Resource | undefined|undefined 
        if (fontFamily_value_buf_selector == 0) {
            fontFamily_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontFamily_value_buf_selector == 1) {
            fontFamily_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontFamily_value_buf has to be chosen through deserialisation.")
        }
        node.fontFamily_value = (fontFamily_value_buf as string | Resource)
    }
    _SecurityComponentMethod_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SecurityComponentMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontColor_value_buf_selector: number = thisDeserializer.readInt8()
        let fontColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (fontColor_value_buf_selector == 0) {
            fontColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (fontColor_value_buf_selector == 1) {
            fontColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontColor_value_buf_selector == 2) {
            fontColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontColor_value_buf_selector == 3) {
            fontColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontColor_value_buf has to be chosen through deserialisation.")
        }
        node.fontColor_value = (fontColor_value_buf as Color | number | string | Resource)
    }
    _SecurityComponentMethod_iconColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SecurityComponentMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const iconColor_value_buf_selector: number = thisDeserializer.readInt8()
        let iconColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (iconColor_value_buf_selector == 0) {
            iconColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (iconColor_value_buf_selector == 1) {
            iconColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (iconColor_value_buf_selector == 2) {
            iconColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (iconColor_value_buf_selector == 3) {
            iconColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for iconColor_value_buf has to be chosen through deserialisation.")
        }
        node.iconColor_value = (iconColor_value_buf as Color | number | string | Resource)
    }
    _SecurityComponentMethod_backgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SecurityComponentMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const backgroundColor_value_buf_selector: number = thisDeserializer.readInt8()
        let backgroundColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (backgroundColor_value_buf_selector == 0) {
            backgroundColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (backgroundColor_value_buf_selector == 1) {
            backgroundColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (backgroundColor_value_buf_selector == 2) {
            backgroundColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (backgroundColor_value_buf_selector == 3) {
            backgroundColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for backgroundColor_value_buf has to be chosen through deserialisation.")
        }
        node.backgroundColor_value = (backgroundColor_value_buf as Color | number | string | Resource)
    }
    _SecurityComponentMethod_borderStyle(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SecurityComponentMethodInterface>(ptr)
        node.borderStyle_value = value
    }
    _SecurityComponentMethod_borderWidth(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<SecurityComponentMethodInterface>(ptr)
        node.borderWidth_value = value
    }
    _SecurityComponentMethod_borderColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SecurityComponentMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const borderColor_value_buf_selector: number = thisDeserializer.readInt8()
        let borderColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (borderColor_value_buf_selector == 0) {
            borderColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (borderColor_value_buf_selector == 1) {
            borderColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (borderColor_value_buf_selector == 2) {
            borderColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (borderColor_value_buf_selector == 3) {
            borderColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for borderColor_value_buf has to be chosen through deserialisation.")
        }
        node.borderColor_value = (borderColor_value_buf as Color | number | string | Resource)
    }
    _SecurityComponentMethod_borderRadius(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<SecurityComponentMethodInterface>(ptr)
        node.borderRadius_value = value
    }
    _SecurityComponentMethod_padding(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SecurityComponentMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const padding_value_buf_selector: number = thisDeserializer.readInt8()
        let padding_value_buf: Padding | Dimension | undefined|undefined 
        if (padding_value_buf_selector == 0) {
            const padding_value_buf_u_top_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let padding_value_buf_u_top_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (padding_value_buf_u_top_buf_runtimeType))
            {
                padding_value_buf_u_top_buf = (thisDeserializer.readLength() as Length)
            }
            const padding_value_buf_u_top: undefined | Length = padding_value_buf_u_top_buf
            const padding_value_buf_u_right_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let padding_value_buf_u_right_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (padding_value_buf_u_right_buf_runtimeType))
            {
                padding_value_buf_u_right_buf = (thisDeserializer.readLength() as Length)
            }
            const padding_value_buf_u_right: undefined | Length = padding_value_buf_u_right_buf
            const padding_value_buf_u_bottom_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let padding_value_buf_u_bottom_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (padding_value_buf_u_bottom_buf_runtimeType))
            {
                padding_value_buf_u_bottom_buf = (thisDeserializer.readLength() as Length)
            }
            const padding_value_buf_u_bottom: undefined | Length = padding_value_buf_u_bottom_buf
            const padding_value_buf_u_left_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let padding_value_buf_u_left_buf: Length | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (padding_value_buf_u_left_buf_runtimeType))
            {
                padding_value_buf_u_left_buf = (thisDeserializer.readLength() as Length)
            }
            const padding_value_buf_u_left: undefined | Length = padding_value_buf_u_left_buf
            padding_value_buf = ({top: padding_value_buf_u_top, right: padding_value_buf_u_right, bottom: padding_value_buf_u_bottom, left: padding_value_buf_u_left} as Padding)
        }
        else if (padding_value_buf_selector == 1) {
            padding_value_buf = (thisDeserializer.readLength() as Dimension)
        }
        else {
            throw new Error("One of the branches for padding_value_buf has to be chosen through deserialisation.")
        }
        node.padding_value = (padding_value_buf as Padding | Dimension)
    }
    _SecurityComponentMethod_textIconSpace(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<SecurityComponentMethodInterface>(ptr)
        node.textIconSpace_value = value
    }
    _SecurityComponentMethod_key(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<SecurityComponentMethodInterface>(ptr)
        node.key_value = value
    }
    _SecurityComponentMethod_width(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<SecurityComponentMethodInterface>(ptr)
        node.width_value = value
    }
    _SecurityComponentMethod_height(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<SecurityComponentMethodInterface>(ptr)
        node.height_value = value
    }
    _SecurityComponentMethod_size(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SecurityComponentMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.size_value = thisDeserializer.readSizeOptions()
    }
    _SecurityComponentMethod_constraintSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SecurityComponentMethodInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.constraintSize_value = thisDeserializer.readConstraintSizeOptions()
    }
    _SelectInterface_setSelectOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SelectInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setSelectOptions_options_buf_length: int32 = thisDeserializer.readInt32()
        let setSelectOptions_options_buf: Array<SelectOption> = new Array<SelectOption>()
        for (let setSelectOptions_options_buf_i = 0; setSelectOptions_options_buf_i < setSelectOptions_options_buf_length; setSelectOptions_options_buf_i++) {
            setSelectOptions_options_buf[setSelectOptions_options_buf_i] = thisDeserializer.readSelectOption()
        }
        node.setSelectOptions_options = setSelectOptions_options_buf
    }
    _SelectAttribute_selected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SelectInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const selected_value_buf_selector: number = thisDeserializer.readInt8()
        let selected_value_buf: number | Resource | undefined|undefined 
        if (selected_value_buf_selector == 0) {
            selected_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (selected_value_buf_selector == 1) {
            selected_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for selected_value_buf has to be chosen through deserialisation.")
        }
        node.selected_value = (selected_value_buf as number | Resource)
    }
    _SelectAttribute_value(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SelectInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const value_value_buf_selector: number = thisDeserializer.readInt8()
        let value_value_buf: string | Resource | undefined|undefined 
        if (value_value_buf_selector == 0) {
            value_value_buf = (thisDeserializer.readString() as string)
        }
        else if (value_value_buf_selector == 1) {
            value_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for value_value_buf has to be chosen through deserialisation.")
        }
        node.value_value = (value_value_buf as string | Resource)
    }
    _SelectAttribute_font(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SelectInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.font_value = thisDeserializer.readFont()
    }
    _SelectAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SelectInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontColor_value_buf_selector: number = thisDeserializer.readInt8()
        let fontColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (fontColor_value_buf_selector == 0) {
            fontColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (fontColor_value_buf_selector == 1) {
            fontColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontColor_value_buf_selector == 2) {
            fontColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontColor_value_buf_selector == 3) {
            fontColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontColor_value_buf has to be chosen through deserialisation.")
        }
        node.fontColor_value = (fontColor_value_buf as Color | number | string | Resource)
    }
    _SelectAttribute_selectedOptionBgColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SelectInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const selectedOptionBgColor_value_buf_selector: number = thisDeserializer.readInt8()
        let selectedOptionBgColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (selectedOptionBgColor_value_buf_selector == 0) {
            selectedOptionBgColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (selectedOptionBgColor_value_buf_selector == 1) {
            selectedOptionBgColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (selectedOptionBgColor_value_buf_selector == 2) {
            selectedOptionBgColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (selectedOptionBgColor_value_buf_selector == 3) {
            selectedOptionBgColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for selectedOptionBgColor_value_buf has to be chosen through deserialisation.")
        }
        node.selectedOptionBgColor_value = (selectedOptionBgColor_value_buf as Color | number | string | Resource)
    }
    _SelectAttribute_selectedOptionFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SelectInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.selectedOptionFont_value = thisDeserializer.readFont()
    }
    _SelectAttribute_selectedOptionFontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SelectInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const selectedOptionFontColor_value_buf_selector: number = thisDeserializer.readInt8()
        let selectedOptionFontColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (selectedOptionFontColor_value_buf_selector == 0) {
            selectedOptionFontColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (selectedOptionFontColor_value_buf_selector == 1) {
            selectedOptionFontColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (selectedOptionFontColor_value_buf_selector == 2) {
            selectedOptionFontColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (selectedOptionFontColor_value_buf_selector == 3) {
            selectedOptionFontColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for selectedOptionFontColor_value_buf has to be chosen through deserialisation.")
        }
        node.selectedOptionFontColor_value = (selectedOptionFontColor_value_buf as Color | number | string | Resource)
    }
    _SelectAttribute_optionBgColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SelectInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const optionBgColor_value_buf_selector: number = thisDeserializer.readInt8()
        let optionBgColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (optionBgColor_value_buf_selector == 0) {
            optionBgColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (optionBgColor_value_buf_selector == 1) {
            optionBgColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (optionBgColor_value_buf_selector == 2) {
            optionBgColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (optionBgColor_value_buf_selector == 3) {
            optionBgColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for optionBgColor_value_buf has to be chosen through deserialisation.")
        }
        node.optionBgColor_value = (optionBgColor_value_buf as Color | number | string | Resource)
    }
    _SelectAttribute_optionFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SelectInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.optionFont_value = thisDeserializer.readFont()
    }
    _SelectAttribute_optionFontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SelectInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const optionFontColor_value_buf_selector: number = thisDeserializer.readInt8()
        let optionFontColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (optionFontColor_value_buf_selector == 0) {
            optionFontColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (optionFontColor_value_buf_selector == 1) {
            optionFontColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (optionFontColor_value_buf_selector == 2) {
            optionFontColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (optionFontColor_value_buf_selector == 3) {
            optionFontColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for optionFontColor_value_buf has to be chosen through deserialisation.")
        }
        node.optionFontColor_value = (optionFontColor_value_buf as Color | number | string | Resource)
    }
    _SelectAttribute_onSelect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SelectInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSelect_value = thisDeserializer.readCallback_Number_String_Void()
    }
    _SelectAttribute_space(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<SelectInterface>(ptr)
        node.space_value = value
    }
    _SelectAttribute_arrowPosition(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SelectInterface>(ptr)
        node.arrowPosition_value = value
    }
    _SelectAttribute_optionWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SelectInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const optionWidth_value_buf_selector: number = thisDeserializer.readInt8()
        let optionWidth_value_buf: Dimension | OptionWidthMode | undefined|undefined 
        if (optionWidth_value_buf_selector == 0) {
            optionWidth_value_buf = (thisDeserializer.readLength() as Dimension)
        }
        else if (optionWidth_value_buf_selector == 1) {
            optionWidth_value_buf = Object.values(OptionWidthMode)[thisDeserializer.readInt32()]
        }
        else {
            throw new Error("One of the branches for optionWidth_value_buf has to be chosen through deserialisation.")
        }
        node.optionWidth_value = (optionWidth_value_buf as Dimension | OptionWidthMode)
    }
    _SelectAttribute_optionHeight(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<SelectInterface>(ptr)
        node.optionHeight_value = value
    }
    _SelectAttribute_menuBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SelectInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const menuBackgroundColor_value_buf_selector: number = thisDeserializer.readInt8()
        let menuBackgroundColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (menuBackgroundColor_value_buf_selector == 0) {
            menuBackgroundColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (menuBackgroundColor_value_buf_selector == 1) {
            menuBackgroundColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (menuBackgroundColor_value_buf_selector == 2) {
            menuBackgroundColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (menuBackgroundColor_value_buf_selector == 3) {
            menuBackgroundColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for menuBackgroundColor_value_buf has to be chosen through deserialisation.")
        }
        node.menuBackgroundColor_value = (menuBackgroundColor_value_buf as Color | number | string | Resource)
    }
    _SelectAttribute_menuBackgroundBlurStyle(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SelectInterface>(ptr)
        node.menuBackgroundBlurStyle_value = value
    }
    _SelectAttribute_controlSize(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SelectInterface>(ptr)
        node.controlSize_value = value
    }
    _SelectAttribute_menuItemContentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SelectInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.menuItemContentModifier_value = (thisDeserializer.readCustomObject("ContentModifier") as ContentModifier<any>)
    }
    _SelectAttribute_divider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SelectInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const divider_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let divider_value_buf: DividerOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (divider_value_buf_runtimeType))
        {
            divider_value_buf = thisDeserializer.readDividerOptions()
        }
        node.divider_value = divider_value_buf
    }
    _SelectAttribute_menuAlign(ptr: KPointer, alignType: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SelectInterface>(ptr)
        node.menuAlign_alignType = alignType
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const menuAlign_offset_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let menuAlign_offset_buf: Offset | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (menuAlign_offset_buf_runtimeType))
        {
            const menuAlign_offset_buf__dx: Length = (thisDeserializer.readLength() as Length)
            const menuAlign_offset_buf__dy: Length = (thisDeserializer.readLength() as Length)
            menuAlign_offset_buf = ({dx: menuAlign_offset_buf__dx, dy: menuAlign_offset_buf__dy} as Offset)
        }
        node.menuAlign_offset = menuAlign_offset_buf
    }
    _ShapeInterface_setShapeOptions0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ShapeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setShapeOptions0_value = (thisDeserializer.readPixelMap() as PixelMap)
    }
    _ShapeInterface_setShapeOptions1(ptr: KPointer): void {
        let node = this.ptr2object<ShapeInterface>(ptr)
    }
    _ShapeAttribute_viewPort(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ShapeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.viewPort_value = thisDeserializer.readViewportRect()
    }
    _ShapeAttribute_stroke(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ShapeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const stroke_value_buf_selector: number = thisDeserializer.readInt8()
        let stroke_value_buf: Color | number | string | Resource | undefined|undefined 
        if (stroke_value_buf_selector == 0) {
            stroke_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (stroke_value_buf_selector == 1) {
            stroke_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (stroke_value_buf_selector == 2) {
            stroke_value_buf = (thisDeserializer.readString() as string)
        }
        else if (stroke_value_buf_selector == 3) {
            stroke_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for stroke_value_buf has to be chosen through deserialisation.")
        }
        node.stroke_value = (stroke_value_buf as Color | number | string | Resource)
    }
    _ShapeAttribute_fill(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ShapeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fill_value_buf_selector: number = thisDeserializer.readInt8()
        let fill_value_buf: Color | number | string | Resource | undefined|undefined 
        if (fill_value_buf_selector == 0) {
            fill_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (fill_value_buf_selector == 1) {
            fill_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fill_value_buf_selector == 2) {
            fill_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fill_value_buf_selector == 3) {
            fill_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fill_value_buf has to be chosen through deserialisation.")
        }
        node.fill_value = (fill_value_buf as Color | number | string | Resource)
    }
    _ShapeAttribute_strokeDashOffset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ShapeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const strokeDashOffset_value_buf_selector: number = thisDeserializer.readInt8()
        let strokeDashOffset_value_buf: number | string | undefined|undefined 
        if (strokeDashOffset_value_buf_selector == 0) {
            strokeDashOffset_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (strokeDashOffset_value_buf_selector == 1) {
            strokeDashOffset_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for strokeDashOffset_value_buf has to be chosen through deserialisation.")
        }
        node.strokeDashOffset_value = (strokeDashOffset_value_buf as number | string)
    }
    _ShapeAttribute_strokeDashArray(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ShapeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const strokeDashArray_value_buf_length: int32 = thisDeserializer.readInt32()
        let strokeDashArray_value_buf: Array<any> = new Array<any>()
        for (let strokeDashArray_value_buf_i = 0; strokeDashArray_value_buf_i < strokeDashArray_value_buf_length; strokeDashArray_value_buf_i++) {
            strokeDashArray_value_buf[strokeDashArray_value_buf_i] = (thisDeserializer.readCustomObject("Any") as Object)
        }
        node.strokeDashArray_value = strokeDashArray_value_buf
    }
    _ShapeAttribute_strokeLineCap(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ShapeInterface>(ptr)
        node.strokeLineCap_value = value
    }
    _ShapeAttribute_strokeLineJoin(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ShapeInterface>(ptr)
        node.strokeLineJoin_value = value
    }
    _ShapeAttribute_strokeMiterLimit(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ShapeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const strokeMiterLimit_value_buf_selector: number = thisDeserializer.readInt8()
        let strokeMiterLimit_value_buf: number | string | undefined|undefined 
        if (strokeMiterLimit_value_buf_selector == 0) {
            strokeMiterLimit_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (strokeMiterLimit_value_buf_selector == 1) {
            strokeMiterLimit_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for strokeMiterLimit_value_buf has to be chosen through deserialisation.")
        }
        node.strokeMiterLimit_value = (strokeMiterLimit_value_buf as number | string)
    }
    _ShapeAttribute_strokeOpacity(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ShapeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const strokeOpacity_value_buf_selector: number = thisDeserializer.readInt8()
        let strokeOpacity_value_buf: number | string | Resource | undefined|undefined 
        if (strokeOpacity_value_buf_selector == 0) {
            strokeOpacity_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (strokeOpacity_value_buf_selector == 1) {
            strokeOpacity_value_buf = (thisDeserializer.readString() as string)
        }
        else if (strokeOpacity_value_buf_selector == 2) {
            strokeOpacity_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for strokeOpacity_value_buf has to be chosen through deserialisation.")
        }
        node.strokeOpacity_value = (strokeOpacity_value_buf as number | string | Resource)
    }
    _ShapeAttribute_fillOpacity(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ShapeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fillOpacity_value_buf_selector: number = thisDeserializer.readInt8()
        let fillOpacity_value_buf: number | string | Resource | undefined|undefined 
        if (fillOpacity_value_buf_selector == 0) {
            fillOpacity_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fillOpacity_value_buf_selector == 1) {
            fillOpacity_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fillOpacity_value_buf_selector == 2) {
            fillOpacity_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fillOpacity_value_buf has to be chosen through deserialisation.")
        }
        node.fillOpacity_value = (fillOpacity_value_buf as number | string | Resource)
    }
    _ShapeAttribute_strokeWidth(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ShapeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const strokeWidth_value_buf_selector: number = thisDeserializer.readInt8()
        let strokeWidth_value_buf: number | string | undefined|undefined 
        if (strokeWidth_value_buf_selector == 0) {
            strokeWidth_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (strokeWidth_value_buf_selector == 1) {
            strokeWidth_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for strokeWidth_value_buf has to be chosen through deserialisation.")
        }
        node.strokeWidth_value = (strokeWidth_value_buf as number | string)
    }
    _ShapeAttribute_antiAlias(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<ShapeInterface>(ptr)
        node.antiAlias_value = value
    }
    _ShapeAttribute_mesh(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, column: number, row: number): void {
        let node = this.ptr2object<ShapeInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const mesh_value_buf_length: int32 = thisDeserializer.readInt32()
        let mesh_value_buf: Array<any> = new Array<any>()
        for (let mesh_value_buf_i = 0; mesh_value_buf_i < mesh_value_buf_length; mesh_value_buf_i++) {
            mesh_value_buf[mesh_value_buf_i] = (thisDeserializer.readCustomObject("Any") as Object)
        }
        node.mesh_value = mesh_value_buf
        node.mesh_column = thisLength
        node.mesh_row = column
    }
    _SliderInterface_setSliderOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SliderInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setSliderOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setSliderOptions_options_buf: SliderOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setSliderOptions_options_buf_runtimeType))
        {
            setSliderOptions_options_buf = thisDeserializer.readSliderOptions()
        }
        node.setSliderOptions_options = setSliderOptions_options_buf
    }
    _SliderAttribute_blockColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SliderInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const blockColor_value_buf_selector: number = thisDeserializer.readInt8()
        let blockColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (blockColor_value_buf_selector == 0) {
            blockColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (blockColor_value_buf_selector == 1) {
            blockColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (blockColor_value_buf_selector == 2) {
            blockColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (blockColor_value_buf_selector == 3) {
            blockColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for blockColor_value_buf has to be chosen through deserialisation.")
        }
        node.blockColor_value = (blockColor_value_buf as Color | number | string | Resource)
    }
    _SliderAttribute_trackColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SliderInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const trackColor_value_buf_selector: number = thisDeserializer.readInt8()
        let trackColor_value_buf: ResourceColor | LinearGradient_common | undefined|undefined 
        if (trackColor_value_buf_selector == 0) {
            const trackColor_value_buf_u_selector: number = thisDeserializer.readInt8()
            let trackColor_value_buf_u: Color | number | string | Resource | undefined|undefined 
            if (trackColor_value_buf_u_selector == 0) {
                trackColor_value_buf_u = (thisDeserializer.readInt32() as Color)
            }
            else if (trackColor_value_buf_u_selector == 1) {
                trackColor_value_buf_u = (thisDeserializer.readNumber() as number)
            }
            else if (trackColor_value_buf_u_selector == 2) {
                trackColor_value_buf_u = (thisDeserializer.readString() as string)
            }
            else if (trackColor_value_buf_u_selector == 3) {
                trackColor_value_buf_u = thisDeserializer.readResource()
            }
            else {
                throw new Error("One of the branches for trackColor_value_buf_u has to be chosen through deserialisation.")
            }
            trackColor_value_buf = (trackColor_value_buf_u as Color | number | string | Resource)
        }
        else if (trackColor_value_buf_selector == 1) {
            trackColor_value_buf = thisDeserializer.readLinearGradient_common()
        }
        else {
            throw new Error("One of the branches for trackColor_value_buf has to be chosen through deserialisation.")
        }
        node.trackColor_value = (trackColor_value_buf as ResourceColor | LinearGradient_common)
    }
    _SliderAttribute_selectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SliderInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const selectedColor_value_buf_selector: number = thisDeserializer.readInt8()
        let selectedColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (selectedColor_value_buf_selector == 0) {
            selectedColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (selectedColor_value_buf_selector == 1) {
            selectedColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (selectedColor_value_buf_selector == 2) {
            selectedColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (selectedColor_value_buf_selector == 3) {
            selectedColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for selectedColor_value_buf has to be chosen through deserialisation.")
        }
        node.selectedColor_value = (selectedColor_value_buf as Color | number | string | Resource)
    }
    _SliderAttribute_minLabel(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<SliderInterface>(ptr)
        node.minLabel_value = value
    }
    _SliderAttribute_maxLabel(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<SliderInterface>(ptr)
        node.maxLabel_value = value
    }
    _SliderAttribute_showSteps(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SliderInterface>(ptr)
        node.showSteps_value = value
    }
    _SliderAttribute_trackThickness(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<SliderInterface>(ptr)
        node.trackThickness_value = value
    }
    _SliderAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SliderInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onChange_value = thisDeserializer.readCallback_Number_SliderChangeMode_Void()
    }
    _SliderAttribute_blockBorderColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SliderInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const blockBorderColor_value_buf_selector: number = thisDeserializer.readInt8()
        let blockBorderColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (blockBorderColor_value_buf_selector == 0) {
            blockBorderColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (blockBorderColor_value_buf_selector == 1) {
            blockBorderColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (blockBorderColor_value_buf_selector == 2) {
            blockBorderColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (blockBorderColor_value_buf_selector == 3) {
            blockBorderColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for blockBorderColor_value_buf has to be chosen through deserialisation.")
        }
        node.blockBorderColor_value = (blockBorderColor_value_buf as Color | number | string | Resource)
    }
    _SliderAttribute_blockBorderWidth(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<SliderInterface>(ptr)
        node.blockBorderWidth_value = value
    }
    _SliderAttribute_stepColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SliderInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const stepColor_value_buf_selector: number = thisDeserializer.readInt8()
        let stepColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (stepColor_value_buf_selector == 0) {
            stepColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (stepColor_value_buf_selector == 1) {
            stepColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (stepColor_value_buf_selector == 2) {
            stepColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (stepColor_value_buf_selector == 3) {
            stepColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for stepColor_value_buf has to be chosen through deserialisation.")
        }
        node.stepColor_value = (stepColor_value_buf as Color | number | string | Resource)
    }
    _SliderAttribute_trackBorderRadius(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<SliderInterface>(ptr)
        node.trackBorderRadius_value = value
    }
    _SliderAttribute_selectedBorderRadius(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<SliderInterface>(ptr)
        node.selectedBorderRadius_value = value
    }
    _SliderAttribute_blockSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SliderInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.blockSize_value = thisDeserializer.readSizeOptions()
    }
    _SliderAttribute_blockStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SliderInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.blockStyle_value = thisDeserializer.readSliderBlockStyle()
    }
    _SliderAttribute_stepSize(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<SliderInterface>(ptr)
        node.stepSize_value = value
    }
    _SliderAttribute_sliderInteractionMode(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SliderInterface>(ptr)
        node.sliderInteractionMode_value = value
    }
    _SliderAttribute_minResponsiveDistance(ptr: KPointer, value: number): void {
        let node = this.ptr2object<SliderInterface>(ptr)
        node.minResponsiveDistance_value = value
    }
    _SliderAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SliderInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.contentModifier_value = (thisDeserializer.readCustomObject("ContentModifier") as ContentModifier<any>)
    }
    _SliderAttribute_slideRange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SliderInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.slideRange_value = thisDeserializer.readSlideRange()
    }
    _SliderAttribute_showTips(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SliderInterface>(ptr)
        node.showTips_value = value
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const showTips_content_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let showTips_content_buf: ResourceStr | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (showTips_content_buf_runtimeType))
        {
            const showTips_content_buf__selector: number = thisDeserializer.readInt8()
            let showTips_content_buf_: string | Resource | undefined|undefined 
            if (showTips_content_buf__selector == 0) {
                showTips_content_buf_ = (thisDeserializer.readString() as string)
            }
            else if (showTips_content_buf__selector == 1) {
                showTips_content_buf_ = thisDeserializer.readResource()
            }
            else {
                throw new Error("One of the branches for showTips_content_buf_ has to be chosen through deserialisation.")
            }
            showTips_content_buf = (showTips_content_buf_ as string | Resource)
        }
        node.showTips_content = showTips_content_buf
    }
    _BaseSpan_textBackgroundStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<BaseSpanInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.textBackgroundStyle_value = thisDeserializer.readTextBackgroundStyle()
    }
    _BaseSpan_baselineOffset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<BaseSpanInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.baselineOffset_value = thisDeserializer.readLengthMetrics()
    }
    _SpanInterface_setSpanOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SpanInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setSpanOptions_value_buf_selector: number = thisDeserializer.readInt8()
        let setSpanOptions_value_buf: string | Resource | undefined|undefined 
        if (setSpanOptions_value_buf_selector == 0) {
            setSpanOptions_value_buf = (thisDeserializer.readString() as string)
        }
        else if (setSpanOptions_value_buf_selector == 1) {
            setSpanOptions_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for setSpanOptions_value_buf has to be chosen through deserialisation.")
        }
        node.setSpanOptions_value = (setSpanOptions_value_buf as string | Resource)
    }
    _SpanAttribute_font(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SpanInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.font_value = thisDeserializer.readFont()
    }
    _SpanAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SpanInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontColor_value_buf_selector: number = thisDeserializer.readInt8()
        let fontColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (fontColor_value_buf_selector == 0) {
            fontColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (fontColor_value_buf_selector == 1) {
            fontColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontColor_value_buf_selector == 2) {
            fontColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontColor_value_buf_selector == 3) {
            fontColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontColor_value_buf has to be chosen through deserialisation.")
        }
        node.fontColor_value = (fontColor_value_buf as Color | number | string | Resource)
    }
    _SpanAttribute_fontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SpanInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontSize_value_buf_selector: number = thisDeserializer.readInt8()
        let fontSize_value_buf: number | string | Resource | undefined|undefined 
        if (fontSize_value_buf_selector == 0) {
            fontSize_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontSize_value_buf_selector == 1) {
            fontSize_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontSize_value_buf_selector == 2) {
            fontSize_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontSize_value_buf has to be chosen through deserialisation.")
        }
        node.fontSize_value = (fontSize_value_buf as number | string | Resource)
    }
    _SpanAttribute_fontStyle(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SpanInterface>(ptr)
        node.fontStyle_value = value
    }
    _SpanAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SpanInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontWeight_value_buf_selector: number = thisDeserializer.readInt8()
        let fontWeight_value_buf: number | FontWeight | string | undefined|undefined 
        if (fontWeight_value_buf_selector == 0) {
            fontWeight_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontWeight_value_buf_selector == 1) {
            fontWeight_value_buf = (thisDeserializer.readInt32() as FontWeight)
        }
        else if (fontWeight_value_buf_selector == 2) {
            fontWeight_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for fontWeight_value_buf has to be chosen through deserialisation.")
        }
        node.fontWeight_value = (fontWeight_value_buf as number | FontWeight | string)
    }
    _SpanAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SpanInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontFamily_value_buf_selector: number = thisDeserializer.readInt8()
        let fontFamily_value_buf: string | Resource | undefined|undefined 
        if (fontFamily_value_buf_selector == 0) {
            fontFamily_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontFamily_value_buf_selector == 1) {
            fontFamily_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontFamily_value_buf has to be chosen through deserialisation.")
        }
        node.fontFamily_value = (fontFamily_value_buf as string | Resource)
    }
    _SpanAttribute_decoration(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SpanInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.decoration_value = thisDeserializer.readDecorationStyleInterface()
    }
    _SpanAttribute_letterSpacing(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SpanInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const letterSpacing_value_buf_selector: number = thisDeserializer.readInt8()
        let letterSpacing_value_buf: number | string | undefined|undefined 
        if (letterSpacing_value_buf_selector == 0) {
            letterSpacing_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (letterSpacing_value_buf_selector == 1) {
            letterSpacing_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for letterSpacing_value_buf has to be chosen through deserialisation.")
        }
        node.letterSpacing_value = (letterSpacing_value_buf as number | string)
    }
    _SpanAttribute_textCase(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SpanInterface>(ptr)
        node.textCase_value = value
    }
    _SpanAttribute_lineHeight(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<SpanInterface>(ptr)
        node.lineHeight_value = value
    }
    _SpanAttribute_textShadow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SpanInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const textShadow_value_buf_selector: number = thisDeserializer.readInt8()
        let textShadow_value_buf: ShadowOptions | Array<ShadowOptions> | undefined|undefined 
        if (textShadow_value_buf_selector == 0) {
            textShadow_value_buf = thisDeserializer.readShadowOptions()
        }
        else if (textShadow_value_buf_selector == 1) {
            const textShadow_value_buf_u_length: int32 = thisDeserializer.readInt32()
            let textShadow_value_buf_u: Array<ShadowOptions> = new Array<ShadowOptions>()
            for (let textShadow_value_buf_u_i = 0; textShadow_value_buf_u_i < textShadow_value_buf_u_length; textShadow_value_buf_u_i++) {
                textShadow_value_buf_u[textShadow_value_buf_u_i] = thisDeserializer.readShadowOptions()
            }
            textShadow_value_buf = textShadow_value_buf_u
        }
        else {
            throw new Error("One of the branches for textShadow_value_buf has to be chosen through deserialisation.")
        }
        node.textShadow_value = (textShadow_value_buf as ShadowOptions | Array<ShadowOptions>)
    }
    _StackInterface_setStackOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<StackInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setStackOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setStackOptions_options_buf: StackOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setStackOptions_options_buf_runtimeType))
        {
            setStackOptions_options_buf = thisDeserializer.readStackOptions()
        }
        node.setStackOptions_options = setStackOptions_options_buf
    }
    _StackAttribute_alignContent(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<StackInterface>(ptr)
        node.alignContent_value = value
    }
    _StackAttribute_pointLight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<StackInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.pointLight_value = thisDeserializer.readPointLightStyle()
    }
    _StepperInterface_setStepperOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<StepperInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setStepperOptions_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setStepperOptions_value_buf: { index?: number } | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setStepperOptions_value_buf_runtimeType))
        {
            const setStepperOptions_value_buf__index_buf_runtimeType = (thisDeserializer.readInt8() as int32)
            let setStepperOptions_value_buf__index_buf: number | undefined|undefined 
            if ((RuntimeType.UNDEFINED) != (setStepperOptions_value_buf__index_buf_runtimeType))
            {
                setStepperOptions_value_buf__index_buf = (thisDeserializer.readNumber() as number)
            }
            const setStepperOptions_value_buf__index: undefined | number = setStepperOptions_value_buf__index_buf
            setStepperOptions_value_buf = ({index: setStepperOptions_value_buf__index} as { index?: number })
        }
        node.setStepperOptions_value = setStepperOptions_value_buf
    }
    _StepperAttribute_onFinish(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<StepperInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onFinish_value = thisDeserializer.readCallback_Void()
    }
    _StepperAttribute_onSkip(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<StepperInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSkip_value = thisDeserializer.readCallback_Void()
    }
    _StepperAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<StepperInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onChange_value = thisDeserializer.readCallback_Number_Number_Void()
    }
    _StepperAttribute_onNext(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<StepperInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onNext_value = thisDeserializer.readCallback_Number_Number_Void()
    }
    _StepperAttribute_onPrevious(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<StepperInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onPrevious_value = thisDeserializer.readCallback_Number_Number_Void()
    }
    _StepperItemInterface_setStepperItemOptions(ptr: KPointer): void {
        let node = this.ptr2object<StepperItemInterface>(ptr)
    }
    _StepperItemAttribute_prevLabel(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<StepperItemInterface>(ptr)
        node.prevLabel_value = value
    }
    _StepperItemAttribute_nextLabel(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<StepperItemInterface>(ptr)
        node.nextLabel_value = value
    }
    _StepperItemAttribute_status(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<StepperItemInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const status_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let status_value_buf: ItemState | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (status_value_buf_runtimeType))
        {
            status_value_buf = (thisDeserializer.readInt32() as ItemState)
        }
        node.status_value = status_value_buf
    }
    _SwiperInterface_setSwiperOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setSwiperOptions_controller_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setSwiperOptions_controller_buf: SwiperController | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setSwiperOptions_controller_buf_runtimeType))
        {
            setSwiperOptions_controller_buf = (thisDeserializer.readSwiperController() as SwiperController)
        }
        node.setSwiperOptions_controller = setSwiperOptions_controller_buf
    }
    _SwiperAttribute_index(ptr: KPointer, value: number): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        node.index_value = value
    }
    _SwiperAttribute_autoPlay(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        node.autoPlay_value = value
    }
    _SwiperAttribute_interval(ptr: KPointer, value: number): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        node.interval_value = value
    }
    _SwiperAttribute_indicator0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const indicator0_value_buf_selector: number = thisDeserializer.readInt8()
        let indicator0_value_buf: DotIndicator | DigitIndicator | boolean | undefined|undefined 
        if (indicator0_value_buf_selector == 0) {
            indicator0_value_buf = thisDeserializer.readDotIndicator()
        }
        else if (indicator0_value_buf_selector == 1) {
            indicator0_value_buf = thisDeserializer.readDigitIndicator()
        }
        else if (indicator0_value_buf_selector == 2) {
            indicator0_value_buf = thisDeserializer.readBoolean()
        }
        else {
            throw new Error("One of the branches for indicator0_value_buf has to be chosen through deserialisation.")
        }
        node.indicator0_value = (indicator0_value_buf as DotIndicator | DigitIndicator | boolean)
    }
    _SwiperAttribute_indicator1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.indicator1_value = (thisDeserializer.readIndicatorComponentController() as IndicatorComponentController)
    }
    _SwiperAttribute_loop(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        node.loop_value = value
    }
    _SwiperAttribute_duration(ptr: KPointer, value: number): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        node.duration_value = value
    }
    _SwiperAttribute_vertical(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        node.vertical_value = value
    }
    _SwiperAttribute_itemSpace(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const itemSpace_value_buf_selector: number = thisDeserializer.readInt8()
        let itemSpace_value_buf: number | string | undefined|undefined 
        if (itemSpace_value_buf_selector == 0) {
            itemSpace_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (itemSpace_value_buf_selector == 1) {
            itemSpace_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for itemSpace_value_buf has to be chosen through deserialisation.")
        }
        node.itemSpace_value = (itemSpace_value_buf as number | string)
    }
    _SwiperAttribute_displayMode(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        node.displayMode_value = value
    }
    _SwiperAttribute_cachedCount(ptr: KPointer, value: number): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        node.cachedCount_value = value
    }
    _SwiperAttribute_effectMode(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        node.effectMode_value = value
    }
    _SwiperAttribute_disableSwipe(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        node.disableSwipe_value = value
    }
    _SwiperAttribute_curve(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const curve_value_buf_selector: number = thisDeserializer.readInt8()
        let curve_value_buf: Curve | string | ICurve | undefined|undefined 
        if (curve_value_buf_selector == 0) {
            curve_value_buf = (thisDeserializer.readInt32() as Curve)
        }
        else if (curve_value_buf_selector == 1) {
            curve_value_buf = (thisDeserializer.readString() as string)
        }
        else if (curve_value_buf_selector == 2) {
            curve_value_buf = (thisDeserializer.readICurve() as ICurve)
        }
        else {
            throw new Error("One of the branches for curve_value_buf has to be chosen through deserialisation.")
        }
        node.curve_value = (curve_value_buf as Curve | string | ICurve)
    }
    _SwiperAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onChange_value = thisDeserializer.readCallback_Number_Void()
    }
    _SwiperAttribute_indicatorStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const indicatorStyle_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let indicatorStyle_value_buf: IndicatorStyle | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (indicatorStyle_value_buf_runtimeType))
        {
            indicatorStyle_value_buf = thisDeserializer.readIndicatorStyle()
        }
        node.indicatorStyle_value = indicatorStyle_value_buf
    }
    _SwiperAttribute_onAnimationStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onAnimationStart_value = thisDeserializer.readOnSwiperAnimationStartCallback()
    }
    _SwiperAttribute_onAnimationEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onAnimationEnd_value = thisDeserializer.readOnSwiperAnimationEndCallback()
    }
    _SwiperAttribute_onGestureSwipe(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onGestureSwipe_value = thisDeserializer.readOnSwiperGestureSwipeCallback()
    }
    _SwiperAttribute_nestedScroll(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        node.nestedScroll_value = value
    }
    _SwiperAttribute_customContentTransition(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.customContentTransition_value = thisDeserializer.readSwiperContentAnimatedTransition()
    }
    _SwiperAttribute_onContentDidScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onContentDidScroll_value = thisDeserializer.readContentDidScrollCallback()
    }
    _SwiperAttribute_indicatorInteractive(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        node.indicatorInteractive_value = value
    }
    _SwiperAttribute_displayArrow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const displayArrow_value_buf_selector: number = thisDeserializer.readInt8()
        let displayArrow_value_buf: ArrowStyle | boolean | undefined|undefined 
        if (displayArrow_value_buf_selector == 0) {
            displayArrow_value_buf = thisDeserializer.readArrowStyle()
        }
        else if (displayArrow_value_buf_selector == 1) {
            displayArrow_value_buf = thisDeserializer.readBoolean()
        }
        else {
            throw new Error("One of the branches for displayArrow_value_buf has to be chosen through deserialisation.")
        }
        node.displayArrow_value = (displayArrow_value_buf as ArrowStyle | boolean)
        const displayArrow_isHoverShow_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let displayArrow_isHoverShow_buf: boolean | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (displayArrow_isHoverShow_buf_runtimeType))
        {
            displayArrow_isHoverShow_buf = thisDeserializer.readBoolean()
        }
        node.displayArrow_isHoverShow = displayArrow_isHoverShow_buf
    }
    _SwiperAttribute_displayCount(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const displayCount_value_buf_selector: number = thisDeserializer.readInt8()
        let displayCount_value_buf: number | string | SwiperAutoFill | undefined|undefined 
        if (displayCount_value_buf_selector == 0) {
            displayCount_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (displayCount_value_buf_selector == 1) {
            displayCount_value_buf = (thisDeserializer.readString() as string)
        }
        else if (displayCount_value_buf_selector == 2) {
            displayCount_value_buf = thisDeserializer.readSwiperAutoFill()
        }
        else {
            throw new Error("One of the branches for displayCount_value_buf has to be chosen through deserialisation.")
        }
        node.displayCount_value = (displayCount_value_buf as number | string | SwiperAutoFill)
        const displayCount_swipeByGroup_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let displayCount_swipeByGroup_buf: boolean | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (displayCount_swipeByGroup_buf_runtimeType))
        {
            displayCount_swipeByGroup_buf = thisDeserializer.readBoolean()
        }
        node.displayCount_swipeByGroup = displayCount_swipeByGroup_buf
    }
    _SwiperAttribute_prevMargin(ptr: KPointer, value: Length, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        node.prevMargin_value = value
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const prevMargin_ignoreBlank_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let prevMargin_ignoreBlank_buf: boolean | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (prevMargin_ignoreBlank_buf_runtimeType))
        {
            prevMargin_ignoreBlank_buf = thisDeserializer.readBoolean()
        }
        node.prevMargin_ignoreBlank = prevMargin_ignoreBlank_buf
    }
    _SwiperAttribute_nextMargin(ptr: KPointer, value: Length, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SwiperInterface>(ptr)
        node.nextMargin_value = value
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const nextMargin_ignoreBlank_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let nextMargin_ignoreBlank_buf: boolean | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (nextMargin_ignoreBlank_buf_runtimeType))
        {
            nextMargin_ignoreBlank_buf = thisDeserializer.readBoolean()
        }
        node.nextMargin_ignoreBlank = nextMargin_ignoreBlank_buf
    }
    _IndicatorComponentInterface_setIndicatorComponentOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<IndicatorComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setIndicatorComponentOptions_controller_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setIndicatorComponentOptions_controller_buf: IndicatorComponentController | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setIndicatorComponentOptions_controller_buf_runtimeType))
        {
            setIndicatorComponentOptions_controller_buf = (thisDeserializer.readIndicatorComponentController() as IndicatorComponentController)
        }
        node.setIndicatorComponentOptions_controller = setIndicatorComponentOptions_controller_buf
    }
    _IndicatorComponentAttribute_initialIndex(ptr: KPointer, value: number): void {
        let node = this.ptr2object<IndicatorComponentInterface>(ptr)
        node.initialIndex_value = value
    }
    _IndicatorComponentAttribute_count(ptr: KPointer, value: number): void {
        let node = this.ptr2object<IndicatorComponentInterface>(ptr)
        node.count_value = value
    }
    _IndicatorComponentAttribute_style(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<IndicatorComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const style_value_buf_selector: number = thisDeserializer.readInt8()
        let style_value_buf: DotIndicator | DigitIndicator | undefined|undefined 
        if (style_value_buf_selector == 0) {
            style_value_buf = thisDeserializer.readDotIndicator()
        }
        else if (style_value_buf_selector == 1) {
            style_value_buf = thisDeserializer.readDigitIndicator()
        }
        else {
            throw new Error("One of the branches for style_value_buf has to be chosen through deserialisation.")
        }
        node.style_value = (style_value_buf as DotIndicator | DigitIndicator)
    }
    _IndicatorComponentAttribute_loop(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<IndicatorComponentInterface>(ptr)
        node.loop_value = value
    }
    _IndicatorComponentAttribute_vertical(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<IndicatorComponentInterface>(ptr)
        node.vertical_value = value
    }
    _IndicatorComponentAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<IndicatorComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onChange_value = thisDeserializer.readCallback_Number_Void()
    }
    _SymbolGlyphInterface_setSymbolGlyphOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SymbolGlyphInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setSymbolGlyphOptions_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setSymbolGlyphOptions_value_buf: Resource | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setSymbolGlyphOptions_value_buf_runtimeType))
        {
            setSymbolGlyphOptions_value_buf = thisDeserializer.readResource()
        }
        node.setSymbolGlyphOptions_value = setSymbolGlyphOptions_value_buf
    }
    _SymbolGlyphAttribute_fontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SymbolGlyphInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontSize_value_buf_selector: number = thisDeserializer.readInt8()
        let fontSize_value_buf: number | string | Resource | undefined|undefined 
        if (fontSize_value_buf_selector == 0) {
            fontSize_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontSize_value_buf_selector == 1) {
            fontSize_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontSize_value_buf_selector == 2) {
            fontSize_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontSize_value_buf has to be chosen through deserialisation.")
        }
        node.fontSize_value = (fontSize_value_buf as number | string | Resource)
    }
    _SymbolGlyphAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SymbolGlyphInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontColor_value_buf_length: int32 = thisDeserializer.readInt32()
        let fontColor_value_buf: Array<ResourceColor> = new Array<ResourceColor>()
        for (let fontColor_value_buf_i = 0; fontColor_value_buf_i < fontColor_value_buf_length; fontColor_value_buf_i++) {
            const fontColor_value_buf_buf_selector: number = thisDeserializer.readInt8()
            let fontColor_value_buf_buf: Color | number | string | Resource | undefined|undefined 
            if (fontColor_value_buf_buf_selector == 0) {
                fontColor_value_buf_buf = (thisDeserializer.readInt32() as Color)
            }
            else if (fontColor_value_buf_buf_selector == 1) {
                fontColor_value_buf_buf = (thisDeserializer.readNumber() as number)
            }
            else if (fontColor_value_buf_buf_selector == 2) {
                fontColor_value_buf_buf = (thisDeserializer.readString() as string)
            }
            else if (fontColor_value_buf_buf_selector == 3) {
                fontColor_value_buf_buf = thisDeserializer.readResource()
            }
            else {
                throw new Error("One of the branches for fontColor_value_buf_buf has to be chosen through deserialisation.")
            }
            fontColor_value_buf[fontColor_value_buf_i] = (fontColor_value_buf_buf as Color | number | string | Resource)
        }
        node.fontColor_value = fontColor_value_buf
    }
    _SymbolGlyphAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SymbolGlyphInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontWeight_value_buf_selector: number = thisDeserializer.readInt8()
        let fontWeight_value_buf: number | FontWeight | string | undefined|undefined 
        if (fontWeight_value_buf_selector == 0) {
            fontWeight_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontWeight_value_buf_selector == 1) {
            fontWeight_value_buf = (thisDeserializer.readInt32() as FontWeight)
        }
        else if (fontWeight_value_buf_selector == 2) {
            fontWeight_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for fontWeight_value_buf has to be chosen through deserialisation.")
        }
        node.fontWeight_value = (fontWeight_value_buf as number | FontWeight | string)
    }
    _SymbolGlyphAttribute_effectStrategy(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SymbolGlyphInterface>(ptr)
        node.effectStrategy_value = value
    }
    _SymbolGlyphAttribute_renderingStrategy(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SymbolGlyphInterface>(ptr)
        node.renderingStrategy_value = value
    }
    _SymbolGlyphAttribute_symbolEffect0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SymbolGlyphInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.symbolEffect0_symbolEffect = thisDeserializer.readSymbolEffect()
        const symbolEffect0_isActive_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let symbolEffect0_isActive_buf: boolean | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (symbolEffect0_isActive_buf_runtimeType))
        {
            symbolEffect0_isActive_buf = thisDeserializer.readBoolean()
        }
        node.symbolEffect0_isActive = symbolEffect0_isActive_buf
    }
    _SymbolGlyphAttribute_symbolEffect1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SymbolGlyphInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.symbolEffect1_symbolEffect = thisDeserializer.readSymbolEffect()
        const symbolEffect1_triggerValue_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let symbolEffect1_triggerValue_buf: number | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (symbolEffect1_triggerValue_buf_runtimeType))
        {
            symbolEffect1_triggerValue_buf = (thisDeserializer.readNumber() as number)
        }
        node.symbolEffect1_triggerValue = symbolEffect1_triggerValue_buf
    }
    _SymbolSpanInterface_setSymbolSpanOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SymbolSpanInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setSymbolSpanOptions_value = thisDeserializer.readResource()
    }
    _SymbolSpanAttribute_fontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SymbolSpanInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontSize_value_buf_selector: number = thisDeserializer.readInt8()
        let fontSize_value_buf: number | string | Resource | undefined|undefined 
        if (fontSize_value_buf_selector == 0) {
            fontSize_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontSize_value_buf_selector == 1) {
            fontSize_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontSize_value_buf_selector == 2) {
            fontSize_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontSize_value_buf has to be chosen through deserialisation.")
        }
        node.fontSize_value = (fontSize_value_buf as number | string | Resource)
    }
    _SymbolSpanAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SymbolSpanInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontColor_value_buf_length: int32 = thisDeserializer.readInt32()
        let fontColor_value_buf: Array<ResourceColor> = new Array<ResourceColor>()
        for (let fontColor_value_buf_i = 0; fontColor_value_buf_i < fontColor_value_buf_length; fontColor_value_buf_i++) {
            const fontColor_value_buf_buf_selector: number = thisDeserializer.readInt8()
            let fontColor_value_buf_buf: Color | number | string | Resource | undefined|undefined 
            if (fontColor_value_buf_buf_selector == 0) {
                fontColor_value_buf_buf = (thisDeserializer.readInt32() as Color)
            }
            else if (fontColor_value_buf_buf_selector == 1) {
                fontColor_value_buf_buf = (thisDeserializer.readNumber() as number)
            }
            else if (fontColor_value_buf_buf_selector == 2) {
                fontColor_value_buf_buf = (thisDeserializer.readString() as string)
            }
            else if (fontColor_value_buf_buf_selector == 3) {
                fontColor_value_buf_buf = thisDeserializer.readResource()
            }
            else {
                throw new Error("One of the branches for fontColor_value_buf_buf has to be chosen through deserialisation.")
            }
            fontColor_value_buf[fontColor_value_buf_i] = (fontColor_value_buf_buf as Color | number | string | Resource)
        }
        node.fontColor_value = fontColor_value_buf
    }
    _SymbolSpanAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SymbolSpanInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontWeight_value_buf_selector: number = thisDeserializer.readInt8()
        let fontWeight_value_buf: number | FontWeight | string | undefined|undefined 
        if (fontWeight_value_buf_selector == 0) {
            fontWeight_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontWeight_value_buf_selector == 1) {
            fontWeight_value_buf = (thisDeserializer.readInt32() as FontWeight)
        }
        else if (fontWeight_value_buf_selector == 2) {
            fontWeight_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for fontWeight_value_buf has to be chosen through deserialisation.")
        }
        node.fontWeight_value = (fontWeight_value_buf as number | FontWeight | string)
    }
    _SymbolSpanAttribute_effectStrategy(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SymbolSpanInterface>(ptr)
        node.effectStrategy_value = value
    }
    _SymbolSpanAttribute_renderingStrategy(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SymbolSpanInterface>(ptr)
        node.renderingStrategy_value = value
    }
    _TabsInterface_setTabsOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setTabsOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setTabsOptions_options_buf: TabsOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setTabsOptions_options_buf_runtimeType))
        {
            setTabsOptions_options_buf = thisDeserializer.readTabsOptions()
        }
        node.setTabsOptions_options = setTabsOptions_options_buf
    }
    _TabsAttribute_vertical(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        node.vertical_value = value
    }
    _TabsAttribute_barPosition(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        node.barPosition_value = value
    }
    _TabsAttribute_scrollable(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        node.scrollable_value = value
    }
    _TabsAttribute_barMode0(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        node.barMode0_value = value
    }
    _TabsAttribute_barMode1(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        node.barMode1_value = value
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const barMode1_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let barMode1_options_buf: ScrollableBarModeOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (barMode1_options_buf_runtimeType))
        {
            barMode1_options_buf = thisDeserializer.readScrollableBarModeOptions()
        }
        node.barMode1_options = barMode1_options_buf
    }
    _TabsAttribute_barWidth(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        node.barWidth_value = value
    }
    _TabsAttribute_barHeight(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        node.barHeight_value = value
    }
    _TabsAttribute_animationDuration(ptr: KPointer, value: number): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        node.animationDuration_value = value
    }
    _TabsAttribute_animationMode(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const animationMode_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let animationMode_value_buf: AnimationMode | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (animationMode_value_buf_runtimeType))
        {
            animationMode_value_buf = (thisDeserializer.readInt32() as AnimationMode)
        }
        node.animationMode_value = animationMode_value_buf
    }
    _TabsAttribute_edgeEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const edgeEffect_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let edgeEffect_value_buf: EdgeEffect | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (edgeEffect_value_buf_runtimeType))
        {
            edgeEffect_value_buf = (thisDeserializer.readInt32() as EdgeEffect)
        }
        node.edgeEffect_value = edgeEffect_value_buf
    }
    _TabsAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onChange_value = thisDeserializer.readCallback_Number_Void()
    }
    _TabsAttribute_onTabBarClick(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onTabBarClick_value = thisDeserializer.readCallback_Number_Void()
    }
    _TabsAttribute_onAnimationStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onAnimationStart_value = thisDeserializer.readOnTabsAnimationStartCallback()
    }
    _TabsAttribute_onAnimationEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onAnimationEnd_value = thisDeserializer.readOnTabsAnimationEndCallback()
    }
    _TabsAttribute_onGestureSwipe(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onGestureSwipe_value = thisDeserializer.readOnTabsGestureSwipeCallback()
    }
    _TabsAttribute_fadingEdge(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        node.fadingEdge_value = value
    }
    _TabsAttribute_divider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const divider_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let divider_value_buf: DividerStyle | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (divider_value_buf_runtimeType))
        {
            divider_value_buf = thisDeserializer.readDividerStyle()
        }
        node.divider_value = divider_value_buf
    }
    _TabsAttribute_barOverlap(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        node.barOverlap_value = value
    }
    _TabsAttribute_barBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const barBackgroundColor_value_buf_selector: number = thisDeserializer.readInt8()
        let barBackgroundColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (barBackgroundColor_value_buf_selector == 0) {
            barBackgroundColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (barBackgroundColor_value_buf_selector == 1) {
            barBackgroundColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (barBackgroundColor_value_buf_selector == 2) {
            barBackgroundColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (barBackgroundColor_value_buf_selector == 3) {
            barBackgroundColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for barBackgroundColor_value_buf has to be chosen through deserialisation.")
        }
        node.barBackgroundColor_value = (barBackgroundColor_value_buf as Color | number | string | Resource)
    }
    _TabsAttribute_barGridAlign(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.barGridAlign_value = thisDeserializer.readBarGridColumnOptions()
    }
    _TabsAttribute_customContentTransition(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.customContentTransition_value = thisDeserializer.readTabsCustomContentTransitionCallback()
    }
    _TabsAttribute_barBackgroundBlurStyle0(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        node.barBackgroundBlurStyle0_value = value
    }
    _TabsAttribute_barBackgroundBlurStyle1(ptr: KPointer, style: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        node.barBackgroundBlurStyle1_style = style
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.barBackgroundBlurStyle1_options = thisDeserializer.readBackgroundBlurStyleOptions()
    }
    _TabsAttribute_barBackgroundEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.barBackgroundEffect_value = thisDeserializer.readBackgroundEffectOptions()
    }
    _TabsAttribute_onContentWillChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onContentWillChange_value = thisDeserializer.readOnTabsContentWillChangeCallback()
    }
    _TabsAttribute_barModeScrollable(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TabsInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.barModeScrollable_options = thisDeserializer.readScrollableBarModeOptions()
    }
    _TabContentInterface_setTabContentOptions(ptr: KPointer): void {
        let node = this.ptr2object<TabContentInterface>(ptr)
    }
    _TabContentAttribute_tabBar0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TabContentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const tabBar0_value_buf_selector: number = thisDeserializer.readInt8()
        let tabBar0_value_buf: string | Resource | CustomBuilder | TabBarOptions | undefined|undefined 
        if (tabBar0_value_buf_selector == 0) {
            tabBar0_value_buf = (thisDeserializer.readString() as string)
        }
        else if (tabBar0_value_buf_selector == 1) {
            tabBar0_value_buf = thisDeserializer.readResource()
        }
        else if (tabBar0_value_buf_selector == 2) {
            tabBar0_value_buf = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
        }
        else if (tabBar0_value_buf_selector == 3) {
            tabBar0_value_buf = thisDeserializer.readTabBarOptions()
        }
        else {
            throw new Error("One of the branches for tabBar0_value_buf has to be chosen through deserialisation.")
        }
        node.tabBar0_value = (tabBar0_value_buf as string | Resource | CustomBuilder | TabBarOptions)
    }
    _TabContentAttribute_tabBar1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TabContentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const tabBar1_value_buf_selector: number = thisDeserializer.readInt8()
        let tabBar1_value_buf: SubTabBarStyle | BottomTabBarStyle | undefined|undefined 
        if (tabBar1_value_buf_selector == 0) {
            tabBar1_value_buf = thisDeserializer.readSubTabBarStyle()
        }
        else if (tabBar1_value_buf_selector == 1) {
            tabBar1_value_buf = thisDeserializer.readBottomTabBarStyle()
        }
        else {
            throw new Error("One of the branches for tabBar1_value_buf has to be chosen through deserialisation.")
        }
        node.tabBar1_value = (tabBar1_value_buf as SubTabBarStyle | BottomTabBarStyle)
    }
    _TabContentAttribute_onWillShow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TabContentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onWillShow_value = thisDeserializer.readVoidCallback()
    }
    _TabContentAttribute_onWillHide(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TabContentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onWillHide_value = thisDeserializer.readVoidCallback()
    }
    _TextInterface_setTextOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setTextOptions_content_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setTextOptions_content_buf: string | Resource | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setTextOptions_content_buf_runtimeType))
        {
            const setTextOptions_content_buf__selector: number = thisDeserializer.readInt8()
            let setTextOptions_content_buf_: string | Resource | undefined|undefined 
            if (setTextOptions_content_buf__selector == 0) {
                setTextOptions_content_buf_ = (thisDeserializer.readString() as string)
            }
            else if (setTextOptions_content_buf__selector == 1) {
                setTextOptions_content_buf_ = thisDeserializer.readResource()
            }
            else {
                throw new Error("One of the branches for setTextOptions_content_buf_ has to be chosen through deserialisation.")
            }
            setTextOptions_content_buf = (setTextOptions_content_buf_ as string | Resource)
        }
        node.setTextOptions_content = setTextOptions_content_buf
        const setTextOptions_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setTextOptions_value_buf: TextOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setTextOptions_value_buf_runtimeType))
        {
            setTextOptions_value_buf = thisDeserializer.readTextOptions()
        }
        node.setTextOptions_value = setTextOptions_value_buf
    }
    _TextAttribute_font0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.font0_value = thisDeserializer.readFont()
    }
    _TextAttribute_font1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.font1_fontValue = thisDeserializer.readFont()
        const font1_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let font1_options_buf: FontSettingOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (font1_options_buf_runtimeType))
        {
            font1_options_buf = thisDeserializer.readFontSettingOptions()
        }
        node.font1_options = font1_options_buf
    }
    _TextAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontColor_value_buf_selector: number = thisDeserializer.readInt8()
        let fontColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (fontColor_value_buf_selector == 0) {
            fontColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (fontColor_value_buf_selector == 1) {
            fontColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontColor_value_buf_selector == 2) {
            fontColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontColor_value_buf_selector == 3) {
            fontColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontColor_value_buf has to be chosen through deserialisation.")
        }
        node.fontColor_value = (fontColor_value_buf as Color | number | string | Resource)
    }
    _TextAttribute_fontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontSize_value_buf_selector: number = thisDeserializer.readInt8()
        let fontSize_value_buf: number | string | Resource | undefined|undefined 
        if (fontSize_value_buf_selector == 0) {
            fontSize_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontSize_value_buf_selector == 1) {
            fontSize_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontSize_value_buf_selector == 2) {
            fontSize_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontSize_value_buf has to be chosen through deserialisation.")
        }
        node.fontSize_value = (fontSize_value_buf as number | string | Resource)
    }
    _TextAttribute_minFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const minFontSize_value_buf_selector: number = thisDeserializer.readInt8()
        let minFontSize_value_buf: number | string | Resource | undefined|undefined 
        if (minFontSize_value_buf_selector == 0) {
            minFontSize_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (minFontSize_value_buf_selector == 1) {
            minFontSize_value_buf = (thisDeserializer.readString() as string)
        }
        else if (minFontSize_value_buf_selector == 2) {
            minFontSize_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for minFontSize_value_buf has to be chosen through deserialisation.")
        }
        node.minFontSize_value = (minFontSize_value_buf as number | string | Resource)
    }
    _TextAttribute_maxFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const maxFontSize_value_buf_selector: number = thisDeserializer.readInt8()
        let maxFontSize_value_buf: number | string | Resource | undefined|undefined 
        if (maxFontSize_value_buf_selector == 0) {
            maxFontSize_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (maxFontSize_value_buf_selector == 1) {
            maxFontSize_value_buf = (thisDeserializer.readString() as string)
        }
        else if (maxFontSize_value_buf_selector == 2) {
            maxFontSize_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for maxFontSize_value_buf has to be chosen through deserialisation.")
        }
        node.maxFontSize_value = (maxFontSize_value_buf as number | string | Resource)
    }
    _TextAttribute_minFontScale(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const minFontScale_value_buf_selector: number = thisDeserializer.readInt8()
        let minFontScale_value_buf: number | Resource | undefined|undefined 
        if (minFontScale_value_buf_selector == 0) {
            minFontScale_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (minFontScale_value_buf_selector == 1) {
            minFontScale_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for minFontScale_value_buf has to be chosen through deserialisation.")
        }
        node.minFontScale_value = (minFontScale_value_buf as number | Resource)
    }
    _TextAttribute_maxFontScale(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const maxFontScale_value_buf_selector: number = thisDeserializer.readInt8()
        let maxFontScale_value_buf: number | Resource | undefined|undefined 
        if (maxFontScale_value_buf_selector == 0) {
            maxFontScale_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (maxFontScale_value_buf_selector == 1) {
            maxFontScale_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for maxFontScale_value_buf has to be chosen through deserialisation.")
        }
        node.maxFontScale_value = (maxFontScale_value_buf as number | Resource)
    }
    _TextAttribute_fontStyle(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInterface>(ptr)
        node.fontStyle_value = value
    }
    _TextAttribute_fontWeight0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontWeight0_value_buf_selector: number = thisDeserializer.readInt8()
        let fontWeight0_value_buf: number | FontWeight | string | undefined|undefined 
        if (fontWeight0_value_buf_selector == 0) {
            fontWeight0_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontWeight0_value_buf_selector == 1) {
            fontWeight0_value_buf = (thisDeserializer.readInt32() as FontWeight)
        }
        else if (fontWeight0_value_buf_selector == 2) {
            fontWeight0_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for fontWeight0_value_buf has to be chosen through deserialisation.")
        }
        node.fontWeight0_value = (fontWeight0_value_buf as number | FontWeight | string)
    }
    _TextAttribute_fontWeight1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontWeight1_weight_buf_selector: number = thisDeserializer.readInt8()
        let fontWeight1_weight_buf: number | FontWeight | string | undefined|undefined 
        if (fontWeight1_weight_buf_selector == 0) {
            fontWeight1_weight_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontWeight1_weight_buf_selector == 1) {
            fontWeight1_weight_buf = (thisDeserializer.readInt32() as FontWeight)
        }
        else if (fontWeight1_weight_buf_selector == 2) {
            fontWeight1_weight_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for fontWeight1_weight_buf has to be chosen through deserialisation.")
        }
        node.fontWeight1_weight = (fontWeight1_weight_buf as number | FontWeight | string)
        const fontWeight1_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let fontWeight1_options_buf: FontSettingOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (fontWeight1_options_buf_runtimeType))
        {
            fontWeight1_options_buf = thisDeserializer.readFontSettingOptions()
        }
        node.fontWeight1_options = fontWeight1_options_buf
    }
    _TextAttribute_lineSpacing(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.lineSpacing_value = thisDeserializer.readLengthMetrics()
    }
    _TextAttribute_textAlign(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInterface>(ptr)
        node.textAlign_value = value
    }
    _TextAttribute_lineHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const lineHeight_value_buf_selector: number = thisDeserializer.readInt8()
        let lineHeight_value_buf: number | string | Resource | undefined|undefined 
        if (lineHeight_value_buf_selector == 0) {
            lineHeight_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (lineHeight_value_buf_selector == 1) {
            lineHeight_value_buf = (thisDeserializer.readString() as string)
        }
        else if (lineHeight_value_buf_selector == 2) {
            lineHeight_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for lineHeight_value_buf has to be chosen through deserialisation.")
        }
        node.lineHeight_value = (lineHeight_value_buf as number | string | Resource)
    }
    _TextAttribute_textOverflow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.textOverflow_value = thisDeserializer.readTextOverflowOptions()
    }
    _TextAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontFamily_value_buf_selector: number = thisDeserializer.readInt8()
        let fontFamily_value_buf: string | Resource | undefined|undefined 
        if (fontFamily_value_buf_selector == 0) {
            fontFamily_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontFamily_value_buf_selector == 1) {
            fontFamily_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontFamily_value_buf has to be chosen through deserialisation.")
        }
        node.fontFamily_value = (fontFamily_value_buf as string | Resource)
    }
    _TextAttribute_maxLines(ptr: KPointer, value: number): void {
        let node = this.ptr2object<TextInterface>(ptr)
        node.maxLines_value = value
    }
    _TextAttribute_decoration(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.decoration_value = thisDeserializer.readDecorationStyleInterface()
    }
    _TextAttribute_letterSpacing(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const letterSpacing_value_buf_selector: number = thisDeserializer.readInt8()
        let letterSpacing_value_buf: number | string | undefined|undefined 
        if (letterSpacing_value_buf_selector == 0) {
            letterSpacing_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (letterSpacing_value_buf_selector == 1) {
            letterSpacing_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for letterSpacing_value_buf has to be chosen through deserialisation.")
        }
        node.letterSpacing_value = (letterSpacing_value_buf as number | string)
    }
    _TextAttribute_textCase(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInterface>(ptr)
        node.textCase_value = value
    }
    _TextAttribute_baselineOffset(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const baselineOffset_value_buf_selector: number = thisDeserializer.readInt8()
        let baselineOffset_value_buf: number | string | undefined|undefined 
        if (baselineOffset_value_buf_selector == 0) {
            baselineOffset_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (baselineOffset_value_buf_selector == 1) {
            baselineOffset_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for baselineOffset_value_buf has to be chosen through deserialisation.")
        }
        node.baselineOffset_value = (baselineOffset_value_buf as number | string)
    }
    _TextAttribute_copyOption(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInterface>(ptr)
        node.copyOption_value = value
    }
    _TextAttribute_draggable(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInterface>(ptr)
        node.draggable_value = value
    }
    _TextAttribute_textShadow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const textShadow_value_buf_selector: number = thisDeserializer.readInt8()
        let textShadow_value_buf: ShadowOptions | Array<ShadowOptions> | undefined|undefined 
        if (textShadow_value_buf_selector == 0) {
            textShadow_value_buf = thisDeserializer.readShadowOptions()
        }
        else if (textShadow_value_buf_selector == 1) {
            const textShadow_value_buf_u_length: int32 = thisDeserializer.readInt32()
            let textShadow_value_buf_u: Array<ShadowOptions> = new Array<ShadowOptions>()
            for (let textShadow_value_buf_u_i = 0; textShadow_value_buf_u_i < textShadow_value_buf_u_length; textShadow_value_buf_u_i++) {
                textShadow_value_buf_u[textShadow_value_buf_u_i] = thisDeserializer.readShadowOptions()
            }
            textShadow_value_buf = textShadow_value_buf_u
        }
        else {
            throw new Error("One of the branches for textShadow_value_buf has to be chosen through deserialisation.")
        }
        node.textShadow_value = (textShadow_value_buf as ShadowOptions | Array<ShadowOptions>)
    }
    _TextAttribute_heightAdaptivePolicy(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInterface>(ptr)
        node.heightAdaptivePolicy_value = value
    }
    _TextAttribute_textIndent(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<TextInterface>(ptr)
        node.textIndent_value = value
    }
    _TextAttribute_wordBreak(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInterface>(ptr)
        node.wordBreak_value = value
    }
    _TextAttribute_lineBreakStrategy(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInterface>(ptr)
        node.lineBreakStrategy_value = value
    }
    _TextAttribute_onCopy(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onCopy_value = thisDeserializer.readCallback_String_Void()
    }
    _TextAttribute_caretColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const caretColor_value_buf_selector: number = thisDeserializer.readInt8()
        let caretColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (caretColor_value_buf_selector == 0) {
            caretColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (caretColor_value_buf_selector == 1) {
            caretColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (caretColor_value_buf_selector == 2) {
            caretColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (caretColor_value_buf_selector == 3) {
            caretColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for caretColor_value_buf has to be chosen through deserialisation.")
        }
        node.caretColor_value = (caretColor_value_buf as Color | number | string | Resource)
    }
    _TextAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const selectedBackgroundColor_value_buf_selector: number = thisDeserializer.readInt8()
        let selectedBackgroundColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (selectedBackgroundColor_value_buf_selector == 0) {
            selectedBackgroundColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (selectedBackgroundColor_value_buf_selector == 1) {
            selectedBackgroundColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (selectedBackgroundColor_value_buf_selector == 2) {
            selectedBackgroundColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (selectedBackgroundColor_value_buf_selector == 3) {
            selectedBackgroundColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for selectedBackgroundColor_value_buf has to be chosen through deserialisation.")
        }
        node.selectedBackgroundColor_value = (selectedBackgroundColor_value_buf as Color | number | string | Resource)
    }
    _TextAttribute_ellipsisMode(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInterface>(ptr)
        node.ellipsisMode_value = value
    }
    _TextAttribute_enableDataDetector(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInterface>(ptr)
        node.enableDataDetector_value = value
    }
    _TextAttribute_dataDetectorConfig(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.dataDetectorConfig_value = thisDeserializer.readTextDataDetectorConfig()
    }
    _TextAttribute_onTextSelectionChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onTextSelectionChange_value = thisDeserializer.readCallback_Number_Number_Void()
    }
    _TextAttribute_fontFeature(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<TextInterface>(ptr)
        node.fontFeature_value = value
    }
    _TextAttribute_privacySensitive(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInterface>(ptr)
        node.privacySensitive_value = value
    }
    _TextAttribute_textSelectable(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInterface>(ptr)
        node.textSelectable_value = value
    }
    _TextAttribute_editMenuOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.editMenuOptions_value = (thisDeserializer.readEditMenuOptions() as EditMenuOptions)
    }
    _TextAttribute_halfLeading(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInterface>(ptr)
        node.halfLeading_value = value
    }
    _TextAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInterface>(ptr)
        node.enableHapticFeedback_value = value
    }
    _TextAttribute_selection(ptr: KPointer, selectionStart: number, selectionEnd: number): void {
        let node = this.ptr2object<TextInterface>(ptr)
        node.selection_selectionStart = selectionStart
        node.selection_selectionEnd = selectionEnd
    }
    _TextAttribute_bindSelectionMenu(ptr: KPointer, spanType: KInt, thisArray: Uint8Array, thisLength: int32, responseType: KInt): void {
        let node = this.ptr2object<TextInterface>(ptr)
        node.bindSelectionMenu_spanType = spanType
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.bindSelectionMenu_content = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
        node.bindSelectionMenu_responseType = thisLength
        const bindSelectionMenu_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let bindSelectionMenu_options_buf: SelectionMenuOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (bindSelectionMenu_options_buf_runtimeType))
        {
            bindSelectionMenu_options_buf = thisDeserializer.readSelectionMenuOptions()
        }
        node.bindSelectionMenu_options = bindSelectionMenu_options_buf
    }
    _TextAreaInterface_setTextAreaOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setTextAreaOptions_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setTextAreaOptions_value_buf: TextAreaOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setTextAreaOptions_value_buf_runtimeType))
        {
            setTextAreaOptions_value_buf = thisDeserializer.readTextAreaOptions()
        }
        node.setTextAreaOptions_value = setTextAreaOptions_value_buf
    }
    _TextAreaAttribute_placeholderColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const placeholderColor_value_buf_selector: number = thisDeserializer.readInt8()
        let placeholderColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (placeholderColor_value_buf_selector == 0) {
            placeholderColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (placeholderColor_value_buf_selector == 1) {
            placeholderColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (placeholderColor_value_buf_selector == 2) {
            placeholderColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (placeholderColor_value_buf_selector == 3) {
            placeholderColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for placeholderColor_value_buf has to be chosen through deserialisation.")
        }
        node.placeholderColor_value = (placeholderColor_value_buf as Color | number | string | Resource)
    }
    _TextAreaAttribute_placeholderFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.placeholderFont_value = thisDeserializer.readFont()
    }
    _TextAreaAttribute_enterKeyType(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        node.enterKeyType_value = value
    }
    _TextAreaAttribute_textAlign(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        node.textAlign_value = value
    }
    _TextAreaAttribute_caretColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const caretColor_value_buf_selector: number = thisDeserializer.readInt8()
        let caretColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (caretColor_value_buf_selector == 0) {
            caretColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (caretColor_value_buf_selector == 1) {
            caretColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (caretColor_value_buf_selector == 2) {
            caretColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (caretColor_value_buf_selector == 3) {
            caretColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for caretColor_value_buf has to be chosen through deserialisation.")
        }
        node.caretColor_value = (caretColor_value_buf as Color | number | string | Resource)
    }
    _TextAreaAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontColor_value_buf_selector: number = thisDeserializer.readInt8()
        let fontColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (fontColor_value_buf_selector == 0) {
            fontColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (fontColor_value_buf_selector == 1) {
            fontColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontColor_value_buf_selector == 2) {
            fontColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontColor_value_buf_selector == 3) {
            fontColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontColor_value_buf has to be chosen through deserialisation.")
        }
        node.fontColor_value = (fontColor_value_buf as Color | number | string | Resource)
    }
    _TextAreaAttribute_fontSize(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        node.fontSize_value = value
    }
    _TextAreaAttribute_fontStyle(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        node.fontStyle_value = value
    }
    _TextAreaAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontWeight_value_buf_selector: number = thisDeserializer.readInt8()
        let fontWeight_value_buf: number | FontWeight | string | undefined|undefined 
        if (fontWeight_value_buf_selector == 0) {
            fontWeight_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontWeight_value_buf_selector == 1) {
            fontWeight_value_buf = (thisDeserializer.readInt32() as FontWeight)
        }
        else if (fontWeight_value_buf_selector == 2) {
            fontWeight_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for fontWeight_value_buf has to be chosen through deserialisation.")
        }
        node.fontWeight_value = (fontWeight_value_buf as number | FontWeight | string)
    }
    _TextAreaAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontFamily_value_buf_selector: number = thisDeserializer.readInt8()
        let fontFamily_value_buf: string | Resource | undefined|undefined 
        if (fontFamily_value_buf_selector == 0) {
            fontFamily_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontFamily_value_buf_selector == 1) {
            fontFamily_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontFamily_value_buf has to be chosen through deserialisation.")
        }
        node.fontFamily_value = (fontFamily_value_buf as string | Resource)
    }
    _TextAreaAttribute_textOverflow(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        node.textOverflow_value = value
    }
    _TextAreaAttribute_textIndent(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        node.textIndent_value = value
    }
    _TextAreaAttribute_caretStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.caretStyle_value = thisDeserializer.readCaretStyle()
    }
    _TextAreaAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const selectedBackgroundColor_value_buf_selector: number = thisDeserializer.readInt8()
        let selectedBackgroundColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (selectedBackgroundColor_value_buf_selector == 0) {
            selectedBackgroundColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (selectedBackgroundColor_value_buf_selector == 1) {
            selectedBackgroundColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (selectedBackgroundColor_value_buf_selector == 2) {
            selectedBackgroundColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (selectedBackgroundColor_value_buf_selector == 3) {
            selectedBackgroundColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for selectedBackgroundColor_value_buf has to be chosen through deserialisation.")
        }
        node.selectedBackgroundColor_value = (selectedBackgroundColor_value_buf as Color | number | string | Resource)
    }
    _TextAreaAttribute_onSubmit0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSubmit0_value = thisDeserializer.readCallback_EnterKeyType_Void()
    }
    _TextAreaAttribute_onSubmit1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSubmit1_value = thisDeserializer.readTextAreaSubmitCallback()
    }
    _TextAreaAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onChange_value = thisDeserializer.readEditableTextOnChangeCallback()
    }
    _TextAreaAttribute_onTextSelectionChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onTextSelectionChange_value = thisDeserializer.readCallback_Number_Number_Void()
    }
    _TextAreaAttribute_onContentScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onContentScroll_value = thisDeserializer.readCallback_Number_Number_Void()
    }
    _TextAreaAttribute_onEditChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onEditChange_value = thisDeserializer.readCallback_Boolean_Void()
    }
    _TextAreaAttribute_onCopy(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onCopy_value = thisDeserializer.readCallback_String_Void()
    }
    _TextAreaAttribute_onCut(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onCut_value = thisDeserializer.readCallback_String_Void()
    }
    _TextAreaAttribute_onPaste(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onPaste_value = thisDeserializer.readCallback_String_PasteEvent_Void()
    }
    _TextAreaAttribute_copyOption(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        node.copyOption_value = value
    }
    _TextAreaAttribute_enableKeyboardOnFocus(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        node.enableKeyboardOnFocus_value = value
    }
    _TextAreaAttribute_maxLength(ptr: KPointer, value: number): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        node.maxLength_value = value
    }
    _TextAreaAttribute_style(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        node.style_value = value
    }
    _TextAreaAttribute_barState(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        node.barState_value = value
    }
    _TextAreaAttribute_selectionMenuHidden(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        node.selectionMenuHidden_value = value
    }
    _TextAreaAttribute_minFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const minFontSize_value_buf_selector: number = thisDeserializer.readInt8()
        let minFontSize_value_buf: number | string | Resource | undefined|undefined 
        if (minFontSize_value_buf_selector == 0) {
            minFontSize_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (minFontSize_value_buf_selector == 1) {
            minFontSize_value_buf = (thisDeserializer.readString() as string)
        }
        else if (minFontSize_value_buf_selector == 2) {
            minFontSize_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for minFontSize_value_buf has to be chosen through deserialisation.")
        }
        node.minFontSize_value = (minFontSize_value_buf as number | string | Resource)
    }
    _TextAreaAttribute_maxFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const maxFontSize_value_buf_selector: number = thisDeserializer.readInt8()
        let maxFontSize_value_buf: number | string | Resource | undefined|undefined 
        if (maxFontSize_value_buf_selector == 0) {
            maxFontSize_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (maxFontSize_value_buf_selector == 1) {
            maxFontSize_value_buf = (thisDeserializer.readString() as string)
        }
        else if (maxFontSize_value_buf_selector == 2) {
            maxFontSize_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for maxFontSize_value_buf has to be chosen through deserialisation.")
        }
        node.maxFontSize_value = (maxFontSize_value_buf as number | string | Resource)
    }
    _TextAreaAttribute_heightAdaptivePolicy(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        node.heightAdaptivePolicy_value = value
    }
    _TextAreaAttribute_maxLines(ptr: KPointer, value: number): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        node.maxLines_value = value
    }
    _TextAreaAttribute_wordBreak(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        node.wordBreak_value = value
    }
    _TextAreaAttribute_lineBreakStrategy(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        node.lineBreakStrategy_value = value
    }
    _TextAreaAttribute_decoration(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.decoration_value = thisDeserializer.readTextDecorationOptions()
    }
    _TextAreaAttribute_letterSpacing(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const letterSpacing_value_buf_selector: number = thisDeserializer.readInt8()
        let letterSpacing_value_buf: number | string | Resource | undefined|undefined 
        if (letterSpacing_value_buf_selector == 0) {
            letterSpacing_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (letterSpacing_value_buf_selector == 1) {
            letterSpacing_value_buf = (thisDeserializer.readString() as string)
        }
        else if (letterSpacing_value_buf_selector == 2) {
            letterSpacing_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for letterSpacing_value_buf has to be chosen through deserialisation.")
        }
        node.letterSpacing_value = (letterSpacing_value_buf as number | string | Resource)
    }
    _TextAreaAttribute_lineSpacing(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.lineSpacing_value = thisDeserializer.readLengthMetrics()
    }
    _TextAreaAttribute_lineHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const lineHeight_value_buf_selector: number = thisDeserializer.readInt8()
        let lineHeight_value_buf: number | string | Resource | undefined|undefined 
        if (lineHeight_value_buf_selector == 0) {
            lineHeight_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (lineHeight_value_buf_selector == 1) {
            lineHeight_value_buf = (thisDeserializer.readString() as string)
        }
        else if (lineHeight_value_buf_selector == 2) {
            lineHeight_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for lineHeight_value_buf has to be chosen through deserialisation.")
        }
        node.lineHeight_value = (lineHeight_value_buf as number | string | Resource)
    }
    _TextAreaAttribute_type(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        node.type_value = value
    }
    _TextAreaAttribute_enableAutoFill(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        node.enableAutoFill_value = value
    }
    _TextAreaAttribute_contentType(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        node.contentType_value = value
    }
    _TextAreaAttribute_fontFeature(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        node.fontFeature_value = value
    }
    _TextAreaAttribute_onWillInsert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onWillInsert_value = thisDeserializer.readCallback_InsertValue_Boolean()
    }
    _TextAreaAttribute_onDidInsert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDidInsert_value = thisDeserializer.readCallback_InsertValue_Void()
    }
    _TextAreaAttribute_onWillDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onWillDelete_value = thisDeserializer.readCallback_DeleteValue_Boolean()
    }
    _TextAreaAttribute_onDidDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDidDelete_value = thisDeserializer.readCallback_DeleteValue_Void()
    }
    _TextAreaAttribute_editMenuOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.editMenuOptions_value = (thisDeserializer.readEditMenuOptions() as EditMenuOptions)
    }
    _TextAreaAttribute_enablePreviewText(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        node.enablePreviewText_value = value
    }
    _TextAreaAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        node.enableHapticFeedback_value = value
    }
    _TextAreaAttribute_inputFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const inputFilter_value_buf_selector: number = thisDeserializer.readInt8()
        let inputFilter_value_buf: string | Resource | undefined|undefined 
        if (inputFilter_value_buf_selector == 0) {
            inputFilter_value_buf = (thisDeserializer.readString() as string)
        }
        else if (inputFilter_value_buf_selector == 1) {
            inputFilter_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for inputFilter_value_buf has to be chosen through deserialisation.")
        }
        node.inputFilter_value = (inputFilter_value_buf as string | Resource)
        const inputFilter_error_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let inputFilter_error_buf: ((breakpoints: string) => void) | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (inputFilter_error_buf_runtimeType))
        {
            inputFilter_error_buf = thisDeserializer.readCallback_String_Void()
        }
        node.inputFilter_error = inputFilter_error_buf
    }
    _TextAreaAttribute_showCounter(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        node.showCounter_value = value
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const showCounter_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let showCounter_options_buf: InputCounterOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (showCounter_options_buf_runtimeType))
        {
            showCounter_options_buf = thisDeserializer.readInputCounterOptions()
        }
        node.showCounter_options = showCounter_options_buf
    }
    _TextAreaAttribute_customKeyboard(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextAreaInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.customKeyboard_value = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
        const customKeyboard_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let customKeyboard_options_buf: KeyboardOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (customKeyboard_options_buf_runtimeType))
        {
            customKeyboard_options_buf = thisDeserializer.readKeyboardOptions()
        }
        node.customKeyboard_options = customKeyboard_options_buf
    }
    _TextClockInterface_setTextClockOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextClockInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setTextClockOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setTextClockOptions_options_buf: TextClockOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setTextClockOptions_options_buf_runtimeType))
        {
            setTextClockOptions_options_buf = thisDeserializer.readTextClockOptions()
        }
        node.setTextClockOptions_options = setTextClockOptions_options_buf
    }
    _TextClockAttribute_format(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<TextClockInterface>(ptr)
        node.format_value = value
    }
    _TextClockAttribute_onDateChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextClockInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDateChange_value = thisDeserializer.readCallback_Number_Void()
    }
    _TextClockAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextClockInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontColor_value_buf_selector: number = thisDeserializer.readInt8()
        let fontColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (fontColor_value_buf_selector == 0) {
            fontColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (fontColor_value_buf_selector == 1) {
            fontColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontColor_value_buf_selector == 2) {
            fontColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontColor_value_buf_selector == 3) {
            fontColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontColor_value_buf has to be chosen through deserialisation.")
        }
        node.fontColor_value = (fontColor_value_buf as Color | number | string | Resource)
    }
    _TextClockAttribute_fontSize(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<TextClockInterface>(ptr)
        node.fontSize_value = value
    }
    _TextClockAttribute_fontStyle(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextClockInterface>(ptr)
        node.fontStyle_value = value
    }
    _TextClockAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextClockInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontWeight_value_buf_selector: number = thisDeserializer.readInt8()
        let fontWeight_value_buf: number | FontWeight | string | undefined|undefined 
        if (fontWeight_value_buf_selector == 0) {
            fontWeight_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontWeight_value_buf_selector == 1) {
            fontWeight_value_buf = (thisDeserializer.readInt32() as FontWeight)
        }
        else if (fontWeight_value_buf_selector == 2) {
            fontWeight_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for fontWeight_value_buf has to be chosen through deserialisation.")
        }
        node.fontWeight_value = (fontWeight_value_buf as number | FontWeight | string)
    }
    _TextClockAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextClockInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontFamily_value_buf_selector: number = thisDeserializer.readInt8()
        let fontFamily_value_buf: string | Resource | undefined|undefined 
        if (fontFamily_value_buf_selector == 0) {
            fontFamily_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontFamily_value_buf_selector == 1) {
            fontFamily_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontFamily_value_buf has to be chosen through deserialisation.")
        }
        node.fontFamily_value = (fontFamily_value_buf as string | Resource)
    }
    _TextClockAttribute_textShadow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextClockInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const textShadow_value_buf_selector: number = thisDeserializer.readInt8()
        let textShadow_value_buf: ShadowOptions | Array<ShadowOptions> | undefined|undefined 
        if (textShadow_value_buf_selector == 0) {
            textShadow_value_buf = thisDeserializer.readShadowOptions()
        }
        else if (textShadow_value_buf_selector == 1) {
            const textShadow_value_buf_u_length: int32 = thisDeserializer.readInt32()
            let textShadow_value_buf_u: Array<ShadowOptions> = new Array<ShadowOptions>()
            for (let textShadow_value_buf_u_i = 0; textShadow_value_buf_u_i < textShadow_value_buf_u_length; textShadow_value_buf_u_i++) {
                textShadow_value_buf_u[textShadow_value_buf_u_i] = thisDeserializer.readShadowOptions()
            }
            textShadow_value_buf = textShadow_value_buf_u
        }
        else {
            throw new Error("One of the branches for textShadow_value_buf has to be chosen through deserialisation.")
        }
        node.textShadow_value = (textShadow_value_buf as ShadowOptions | Array<ShadowOptions>)
    }
    _TextClockAttribute_fontFeature(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<TextClockInterface>(ptr)
        node.fontFeature_value = value
    }
    _TextClockAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextClockInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.contentModifier_value = (thisDeserializer.readCustomObject("ContentModifier") as ContentModifier<any>)
    }
    _TextClockAttribute_dateTimeOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextClockInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const dateTimeOptions_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let dateTimeOptions_value_buf: DateTimeOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (dateTimeOptions_value_buf_runtimeType))
        {
            dateTimeOptions_value_buf = thisDeserializer.readDateTimeOptions()
        }
        node.dateTimeOptions_value = dateTimeOptions_value_buf
    }
    _TextInputInterface_setTextInputOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setTextInputOptions_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setTextInputOptions_value_buf: TextInputOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setTextInputOptions_value_buf_runtimeType))
        {
            setTextInputOptions_value_buf = thisDeserializer.readTextInputOptions()
        }
        node.setTextInputOptions_value = setTextInputOptions_value_buf
    }
    _TextInputAttribute_type(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.type_value = value
    }
    _TextInputAttribute_contentType(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.contentType_value = value
    }
    _TextInputAttribute_placeholderColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const placeholderColor_value_buf_selector: number = thisDeserializer.readInt8()
        let placeholderColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (placeholderColor_value_buf_selector == 0) {
            placeholderColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (placeholderColor_value_buf_selector == 1) {
            placeholderColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (placeholderColor_value_buf_selector == 2) {
            placeholderColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (placeholderColor_value_buf_selector == 3) {
            placeholderColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for placeholderColor_value_buf has to be chosen through deserialisation.")
        }
        node.placeholderColor_value = (placeholderColor_value_buf as Color | number | string | Resource)
    }
    _TextInputAttribute_textOverflow(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.textOverflow_value = value
    }
    _TextInputAttribute_textIndent(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.textIndent_value = value
    }
    _TextInputAttribute_placeholderFont(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const placeholderFont_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let placeholderFont_value_buf: Font | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (placeholderFont_value_buf_runtimeType))
        {
            placeholderFont_value_buf = thisDeserializer.readFont()
        }
        node.placeholderFont_value = placeholderFont_value_buf
    }
    _TextInputAttribute_enterKeyType(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.enterKeyType_value = value
    }
    _TextInputAttribute_caretColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const caretColor_value_buf_selector: number = thisDeserializer.readInt8()
        let caretColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (caretColor_value_buf_selector == 0) {
            caretColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (caretColor_value_buf_selector == 1) {
            caretColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (caretColor_value_buf_selector == 2) {
            caretColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (caretColor_value_buf_selector == 3) {
            caretColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for caretColor_value_buf has to be chosen through deserialisation.")
        }
        node.caretColor_value = (caretColor_value_buf as Color | number | string | Resource)
    }
    _TextInputAttribute_onEditChanged(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onEditChanged_value = thisDeserializer.readCallback_Boolean_Void()
    }
    _TextInputAttribute_onEditChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onEditChange_value = thisDeserializer.readCallback_Boolean_Void()
    }
    _TextInputAttribute_onSubmit(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSubmit_value = thisDeserializer.readOnSubmitCallback()
    }
    _TextInputAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onChange_value = thisDeserializer.readEditableTextOnChangeCallback()
    }
    _TextInputAttribute_onTextSelectionChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onTextSelectionChange_value = thisDeserializer.readOnTextSelectionChangeCallback()
    }
    _TextInputAttribute_onContentScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onContentScroll_value = thisDeserializer.readOnContentScrollCallback()
    }
    _TextInputAttribute_maxLength(ptr: KPointer, value: number): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.maxLength_value = value
    }
    _TextInputAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontColor_value_buf_selector: number = thisDeserializer.readInt8()
        let fontColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (fontColor_value_buf_selector == 0) {
            fontColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (fontColor_value_buf_selector == 1) {
            fontColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontColor_value_buf_selector == 2) {
            fontColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontColor_value_buf_selector == 3) {
            fontColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontColor_value_buf has to be chosen through deserialisation.")
        }
        node.fontColor_value = (fontColor_value_buf as Color | number | string | Resource)
    }
    _TextInputAttribute_fontSize(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.fontSize_value = value
    }
    _TextInputAttribute_fontStyle(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.fontStyle_value = value
    }
    _TextInputAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontWeight_value_buf_selector: number = thisDeserializer.readInt8()
        let fontWeight_value_buf: number | FontWeight | string | undefined|undefined 
        if (fontWeight_value_buf_selector == 0) {
            fontWeight_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontWeight_value_buf_selector == 1) {
            fontWeight_value_buf = (thisDeserializer.readInt32() as FontWeight)
        }
        else if (fontWeight_value_buf_selector == 2) {
            fontWeight_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for fontWeight_value_buf has to be chosen through deserialisation.")
        }
        node.fontWeight_value = (fontWeight_value_buf as number | FontWeight | string)
    }
    _TextInputAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontFamily_value_buf_selector: number = thisDeserializer.readInt8()
        let fontFamily_value_buf: string | Resource | undefined|undefined 
        if (fontFamily_value_buf_selector == 0) {
            fontFamily_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontFamily_value_buf_selector == 1) {
            fontFamily_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontFamily_value_buf has to be chosen through deserialisation.")
        }
        node.fontFamily_value = (fontFamily_value_buf as string | Resource)
    }
    _TextInputAttribute_onCopy(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onCopy_value = thisDeserializer.readCallback_String_Void()
    }
    _TextInputAttribute_onCut(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onCut_value = thisDeserializer.readCallback_String_Void()
    }
    _TextInputAttribute_onPaste(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onPaste_value = thisDeserializer.readOnPasteCallback()
    }
    _TextInputAttribute_copyOption(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.copyOption_value = value
    }
    _TextInputAttribute_showPasswordIcon(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.showPasswordIcon_value = value
    }
    _TextInputAttribute_textAlign(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.textAlign_value = value
    }
    _TextInputAttribute_style(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const style_value_buf_selector: number = thisDeserializer.readInt8()
        let style_value_buf: TextInputStyle | TextContentStyle | undefined|undefined 
        if (style_value_buf_selector == 0) {
            style_value_buf = (thisDeserializer.readInt32() as TextInputStyle)
        }
        else if (style_value_buf_selector == 1) {
            style_value_buf = (thisDeserializer.readInt32() as TextContentStyle)
        }
        else {
            throw new Error("One of the branches for style_value_buf has to be chosen through deserialisation.")
        }
        node.style_value = (style_value_buf as TextInputStyle | TextContentStyle)
    }
    _TextInputAttribute_caretStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.caretStyle_value = thisDeserializer.readCaretStyle()
    }
    _TextInputAttribute_selectedBackgroundColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const selectedBackgroundColor_value_buf_selector: number = thisDeserializer.readInt8()
        let selectedBackgroundColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (selectedBackgroundColor_value_buf_selector == 0) {
            selectedBackgroundColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (selectedBackgroundColor_value_buf_selector == 1) {
            selectedBackgroundColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (selectedBackgroundColor_value_buf_selector == 2) {
            selectedBackgroundColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (selectedBackgroundColor_value_buf_selector == 3) {
            selectedBackgroundColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for selectedBackgroundColor_value_buf has to be chosen through deserialisation.")
        }
        node.selectedBackgroundColor_value = (selectedBackgroundColor_value_buf as Color | number | string | Resource)
    }
    _TextInputAttribute_caretPosition(ptr: KPointer, value: number): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.caretPosition_value = value
    }
    _TextInputAttribute_enableKeyboardOnFocus(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.enableKeyboardOnFocus_value = value
    }
    _TextInputAttribute_passwordIcon(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.passwordIcon_value = thisDeserializer.readPasswordIcon()
    }
    _TextInputAttribute_showError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const showError_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let showError_value_buf: ResourceStr | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (showError_value_buf_runtimeType))
        {
            const showError_value_buf__selector: number = thisDeserializer.readInt8()
            let showError_value_buf_: string | Resource | undefined|undefined 
            if (showError_value_buf__selector == 0) {
                showError_value_buf_ = (thisDeserializer.readString() as string)
            }
            else if (showError_value_buf__selector == 1) {
                showError_value_buf_ = thisDeserializer.readResource()
            }
            else {
                throw new Error("One of the branches for showError_value_buf_ has to be chosen through deserialisation.")
            }
            showError_value_buf = (showError_value_buf_ as string | Resource)
        }
        node.showError_value = showError_value_buf
    }
    _TextInputAttribute_showUnit(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.showUnit_value = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
    }
    _TextInputAttribute_showUnderline(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.showUnderline_value = value
    }
    _TextInputAttribute_underlineColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const underlineColor_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let underlineColor_value_buf: ResourceColor | UnderlineColor | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (underlineColor_value_buf_runtimeType))
        {
            const underlineColor_value_buf__selector: number = thisDeserializer.readInt8()
            let underlineColor_value_buf_: ResourceColor | UnderlineColor | undefined|undefined 
            if (underlineColor_value_buf__selector == 0) {
                const underlineColor_value_buf__u_selector: number = thisDeserializer.readInt8()
                let underlineColor_value_buf__u: Color | number | string | Resource | undefined|undefined 
                if (underlineColor_value_buf__u_selector == 0) {
                    underlineColor_value_buf__u = (thisDeserializer.readInt32() as Color)
                }
                else if (underlineColor_value_buf__u_selector == 1) {
                    underlineColor_value_buf__u = (thisDeserializer.readNumber() as number)
                }
                else if (underlineColor_value_buf__u_selector == 2) {
                    underlineColor_value_buf__u = (thisDeserializer.readString() as string)
                }
                else if (underlineColor_value_buf__u_selector == 3) {
                    underlineColor_value_buf__u = thisDeserializer.readResource()
                }
                else {
                    throw new Error("One of the branches for underlineColor_value_buf__u has to be chosen through deserialisation.")
                }
                underlineColor_value_buf_ = (underlineColor_value_buf__u as Color | number | string | Resource)
            }
            else if (underlineColor_value_buf__selector == 1) {
                underlineColor_value_buf_ = thisDeserializer.readUnderlineColor()
            }
            else {
                throw new Error("One of the branches for underlineColor_value_buf_ has to be chosen through deserialisation.")
            }
            underlineColor_value_buf = (underlineColor_value_buf_ as ResourceColor | UnderlineColor)
        }
        node.underlineColor_value = underlineColor_value_buf
    }
    _TextInputAttribute_selectionMenuHidden(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.selectionMenuHidden_value = value
    }
    _TextInputAttribute_barState(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.barState_value = value
    }
    _TextInputAttribute_maxLines(ptr: KPointer, value: number): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.maxLines_value = value
    }
    _TextInputAttribute_wordBreak(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.wordBreak_value = value
    }
    _TextInputAttribute_lineBreakStrategy(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.lineBreakStrategy_value = value
    }
    _TextInputAttribute_cancelButton0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.cancelButton0_value = thisDeserializer.readCancelButtonOptions()
    }
    _TextInputAttribute_cancelButton1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.cancelButton1_value = thisDeserializer.readCancelButtonSymbolOptions()
    }
    _TextInputAttribute_selectAll(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.selectAll_value = value
    }
    _TextInputAttribute_minFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const minFontSize_value_buf_selector: number = thisDeserializer.readInt8()
        let minFontSize_value_buf: number | string | Resource | undefined|undefined 
        if (minFontSize_value_buf_selector == 0) {
            minFontSize_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (minFontSize_value_buf_selector == 1) {
            minFontSize_value_buf = (thisDeserializer.readString() as string)
        }
        else if (minFontSize_value_buf_selector == 2) {
            minFontSize_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for minFontSize_value_buf has to be chosen through deserialisation.")
        }
        node.minFontSize_value = (minFontSize_value_buf as number | string | Resource)
    }
    _TextInputAttribute_maxFontSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const maxFontSize_value_buf_selector: number = thisDeserializer.readInt8()
        let maxFontSize_value_buf: number | string | Resource | undefined|undefined 
        if (maxFontSize_value_buf_selector == 0) {
            maxFontSize_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (maxFontSize_value_buf_selector == 1) {
            maxFontSize_value_buf = (thisDeserializer.readString() as string)
        }
        else if (maxFontSize_value_buf_selector == 2) {
            maxFontSize_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for maxFontSize_value_buf has to be chosen through deserialisation.")
        }
        node.maxFontSize_value = (maxFontSize_value_buf as number | string | Resource)
    }
    _TextInputAttribute_heightAdaptivePolicy(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.heightAdaptivePolicy_value = value
    }
    _TextInputAttribute_enableAutoFill(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.enableAutoFill_value = value
    }
    _TextInputAttribute_decoration(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.decoration_value = thisDeserializer.readTextDecorationOptions()
    }
    _TextInputAttribute_letterSpacing(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const letterSpacing_value_buf_selector: number = thisDeserializer.readInt8()
        let letterSpacing_value_buf: number | string | Resource | undefined|undefined 
        if (letterSpacing_value_buf_selector == 0) {
            letterSpacing_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (letterSpacing_value_buf_selector == 1) {
            letterSpacing_value_buf = (thisDeserializer.readString() as string)
        }
        else if (letterSpacing_value_buf_selector == 2) {
            letterSpacing_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for letterSpacing_value_buf has to be chosen through deserialisation.")
        }
        node.letterSpacing_value = (letterSpacing_value_buf as number | string | Resource)
    }
    _TextInputAttribute_lineHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const lineHeight_value_buf_selector: number = thisDeserializer.readInt8()
        let lineHeight_value_buf: number | string | Resource | undefined|undefined 
        if (lineHeight_value_buf_selector == 0) {
            lineHeight_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (lineHeight_value_buf_selector == 1) {
            lineHeight_value_buf = (thisDeserializer.readString() as string)
        }
        else if (lineHeight_value_buf_selector == 2) {
            lineHeight_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for lineHeight_value_buf has to be chosen through deserialisation.")
        }
        node.lineHeight_value = (lineHeight_value_buf as number | string | Resource)
    }
    _TextInputAttribute_passwordRules(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.passwordRules_value = value
    }
    _TextInputAttribute_fontFeature(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.fontFeature_value = value
    }
    _TextInputAttribute_showPassword(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.showPassword_value = value
    }
    _TextInputAttribute_onSecurityStateChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSecurityStateChange_value = thisDeserializer.readCallback_Boolean_Void()
    }
    _TextInputAttribute_onWillInsert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onWillInsert_value = thisDeserializer.readCallback_InsertValue_Boolean()
    }
    _TextInputAttribute_onDidInsert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDidInsert_value = thisDeserializer.readCallback_InsertValue_Void()
    }
    _TextInputAttribute_onWillDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onWillDelete_value = thisDeserializer.readCallback_DeleteValue_Boolean()
    }
    _TextInputAttribute_onDidDelete(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDidDelete_value = thisDeserializer.readCallback_DeleteValue_Void()
    }
    _TextInputAttribute_editMenuOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.editMenuOptions_value = (thisDeserializer.readEditMenuOptions() as EditMenuOptions)
    }
    _TextInputAttribute_enablePreviewText(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.enablePreviewText_value = value
    }
    _TextInputAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.enableHapticFeedback_value = value
    }
    _TextInputAttribute_inputFilter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const inputFilter_value_buf_selector: number = thisDeserializer.readInt8()
        let inputFilter_value_buf: string | Resource | undefined|undefined 
        if (inputFilter_value_buf_selector == 0) {
            inputFilter_value_buf = (thisDeserializer.readString() as string)
        }
        else if (inputFilter_value_buf_selector == 1) {
            inputFilter_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for inputFilter_value_buf has to be chosen through deserialisation.")
        }
        node.inputFilter_value = (inputFilter_value_buf as string | Resource)
        const inputFilter_error_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let inputFilter_error_buf: ((breakpoints: string) => void) | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (inputFilter_error_buf_runtimeType))
        {
            inputFilter_error_buf = thisDeserializer.readCallback_String_Void()
        }
        node.inputFilter_error = inputFilter_error_buf
    }
    _TextInputAttribute_customKeyboard(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.customKeyboard_value = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
        const customKeyboard_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let customKeyboard_options_buf: KeyboardOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (customKeyboard_options_buf_runtimeType))
        {
            customKeyboard_options_buf = thisDeserializer.readKeyboardOptions()
        }
        node.customKeyboard_options = customKeyboard_options_buf
    }
    _TextInputAttribute_showCounter(ptr: KPointer, value: KInt, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextInputInterface>(ptr)
        node.showCounter_value = value
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const showCounter_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let showCounter_options_buf: InputCounterOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (showCounter_options_buf_runtimeType))
        {
            showCounter_options_buf = thisDeserializer.readInputCounterOptions()
        }
        node.showCounter_options = showCounter_options_buf
    }
    _TextPickerInterface_setTextPickerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextPickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setTextPickerOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setTextPickerOptions_options_buf: TextPickerOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setTextPickerOptions_options_buf_runtimeType))
        {
            setTextPickerOptions_options_buf = thisDeserializer.readTextPickerOptions()
        }
        node.setTextPickerOptions_options = setTextPickerOptions_options_buf
    }
    _TextPickerAttribute_defaultPickerItemHeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextPickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const defaultPickerItemHeight_value_buf_selector: number = thisDeserializer.readInt8()
        let defaultPickerItemHeight_value_buf: number | string | undefined|undefined 
        if (defaultPickerItemHeight_value_buf_selector == 0) {
            defaultPickerItemHeight_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (defaultPickerItemHeight_value_buf_selector == 1) {
            defaultPickerItemHeight_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for defaultPickerItemHeight_value_buf has to be chosen through deserialisation.")
        }
        node.defaultPickerItemHeight_value = (defaultPickerItemHeight_value_buf as number | string)
    }
    _TextPickerAttribute_canLoop(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextPickerInterface>(ptr)
        node.canLoop_value = value
    }
    _TextPickerAttribute_disappearTextStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextPickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.disappearTextStyle_value = thisDeserializer.readPickerTextStyle()
    }
    _TextPickerAttribute_textStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextPickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.textStyle_value = thisDeserializer.readPickerTextStyle()
    }
    _TextPickerAttribute_selectedTextStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextPickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.selectedTextStyle_value = thisDeserializer.readPickerTextStyle()
    }
    _TextPickerAttribute_onAccept(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextPickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onAccept_value = thisDeserializer.readCallback_String_Number_Void()
    }
    _TextPickerAttribute_onCancel(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextPickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onCancel_value = thisDeserializer.readCallback_Void()
    }
    _TextPickerAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextPickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onChange_value = thisDeserializer.readType_TextPickerAttribute_onChange_callback()
    }
    _TextPickerAttribute_selectedIndex(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextPickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const selectedIndex_value_buf_selector: number = thisDeserializer.readInt8()
        let selectedIndex_value_buf: number | Array<number> | undefined|undefined 
        if (selectedIndex_value_buf_selector == 0) {
            selectedIndex_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (selectedIndex_value_buf_selector == 1) {
            const selectedIndex_value_buf_u_length: int32 = thisDeserializer.readInt32()
            let selectedIndex_value_buf_u: Array<number> = new Array<number>()
            for (let selectedIndex_value_buf_u_i = 0; selectedIndex_value_buf_u_i < selectedIndex_value_buf_u_length; selectedIndex_value_buf_u_i++) {
                selectedIndex_value_buf_u[selectedIndex_value_buf_u_i] = (thisDeserializer.readNumber() as number)
            }
            selectedIndex_value_buf = selectedIndex_value_buf_u
        }
        else {
            throw new Error("One of the branches for selectedIndex_value_buf has to be chosen through deserialisation.")
        }
        node.selectedIndex_value = (selectedIndex_value_buf as number | Array<number>)
    }
    _TextPickerAttribute_divider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextPickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const divider_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let divider_value_buf: DividerOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (divider_value_buf_runtimeType))
        {
            divider_value_buf = thisDeserializer.readDividerOptions()
        }
        node.divider_value = divider_value_buf
    }
    _TextPickerAttribute_gradientHeight(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<TextPickerInterface>(ptr)
        node.gradientHeight_value = value
    }
    _TextTimerInterface_setTextTimerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextTimerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setTextTimerOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setTextTimerOptions_options_buf: TextTimerOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setTextTimerOptions_options_buf_runtimeType))
        {
            setTextTimerOptions_options_buf = thisDeserializer.readTextTimerOptions()
        }
        node.setTextTimerOptions_options = setTextTimerOptions_options_buf
    }
    _TextTimerAttribute_format(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<TextTimerInterface>(ptr)
        node.format_value = value
    }
    _TextTimerAttribute_fontColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextTimerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontColor_value_buf_selector: number = thisDeserializer.readInt8()
        let fontColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (fontColor_value_buf_selector == 0) {
            fontColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (fontColor_value_buf_selector == 1) {
            fontColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontColor_value_buf_selector == 2) {
            fontColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontColor_value_buf_selector == 3) {
            fontColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontColor_value_buf has to be chosen through deserialisation.")
        }
        node.fontColor_value = (fontColor_value_buf as Color | number | string | Resource)
    }
    _TextTimerAttribute_fontSize(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<TextTimerInterface>(ptr)
        node.fontSize_value = value
    }
    _TextTimerAttribute_fontStyle(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TextTimerInterface>(ptr)
        node.fontStyle_value = value
    }
    _TextTimerAttribute_fontWeight(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextTimerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontWeight_value_buf_selector: number = thisDeserializer.readInt8()
        let fontWeight_value_buf: number | FontWeight | string | undefined|undefined 
        if (fontWeight_value_buf_selector == 0) {
            fontWeight_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (fontWeight_value_buf_selector == 1) {
            fontWeight_value_buf = (thisDeserializer.readInt32() as FontWeight)
        }
        else if (fontWeight_value_buf_selector == 2) {
            fontWeight_value_buf = (thisDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for fontWeight_value_buf has to be chosen through deserialisation.")
        }
        node.fontWeight_value = (fontWeight_value_buf as number | FontWeight | string)
    }
    _TextTimerAttribute_fontFamily(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextTimerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const fontFamily_value_buf_selector: number = thisDeserializer.readInt8()
        let fontFamily_value_buf: string | Resource | undefined|undefined 
        if (fontFamily_value_buf_selector == 0) {
            fontFamily_value_buf = (thisDeserializer.readString() as string)
        }
        else if (fontFamily_value_buf_selector == 1) {
            fontFamily_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for fontFamily_value_buf has to be chosen through deserialisation.")
        }
        node.fontFamily_value = (fontFamily_value_buf as string | Resource)
    }
    _TextTimerAttribute_onTimer(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextTimerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onTimer_value = thisDeserializer.readCallback_Number_Number_Void()
    }
    _TextTimerAttribute_textShadow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextTimerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const textShadow_value_buf_selector: number = thisDeserializer.readInt8()
        let textShadow_value_buf: ShadowOptions | Array<ShadowOptions> | undefined|undefined 
        if (textShadow_value_buf_selector == 0) {
            textShadow_value_buf = thisDeserializer.readShadowOptions()
        }
        else if (textShadow_value_buf_selector == 1) {
            const textShadow_value_buf_u_length: int32 = thisDeserializer.readInt32()
            let textShadow_value_buf_u: Array<ShadowOptions> = new Array<ShadowOptions>()
            for (let textShadow_value_buf_u_i = 0; textShadow_value_buf_u_i < textShadow_value_buf_u_length; textShadow_value_buf_u_i++) {
                textShadow_value_buf_u[textShadow_value_buf_u_i] = thisDeserializer.readShadowOptions()
            }
            textShadow_value_buf = textShadow_value_buf_u
        }
        else {
            throw new Error("One of the branches for textShadow_value_buf has to be chosen through deserialisation.")
        }
        node.textShadow_value = (textShadow_value_buf as ShadowOptions | Array<ShadowOptions>)
    }
    _TextTimerAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TextTimerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.contentModifier_value = (thisDeserializer.readCustomObject("ContentModifier") as ContentModifier<any>)
    }
    _TimePickerInterface_setTimePickerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TimePickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setTimePickerOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setTimePickerOptions_options_buf: TimePickerOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setTimePickerOptions_options_buf_runtimeType))
        {
            setTimePickerOptions_options_buf = thisDeserializer.readTimePickerOptions()
        }
        node.setTimePickerOptions_options = setTimePickerOptions_options_buf
    }
    _TimePickerAttribute_useMilitaryTime(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TimePickerInterface>(ptr)
        node.useMilitaryTime_value = value
    }
    _TimePickerAttribute_loop(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TimePickerInterface>(ptr)
        node.loop_value = value
    }
    _TimePickerAttribute_disappearTextStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TimePickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.disappearTextStyle_value = thisDeserializer.readPickerTextStyle()
    }
    _TimePickerAttribute_textStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TimePickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.textStyle_value = thisDeserializer.readPickerTextStyle()
    }
    _TimePickerAttribute_selectedTextStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TimePickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.selectedTextStyle_value = thisDeserializer.readPickerTextStyle()
    }
    _TimePickerAttribute_dateTimeOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TimePickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.dateTimeOptions_value = thisDeserializer.readDateTimeOptions()
    }
    _TimePickerAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<TimePickerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onChange_value = thisDeserializer.readCallback_TimePickerResult_Void()
    }
    _TimePickerAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<TimePickerInterface>(ptr)
        node.enableHapticFeedback_value = value
    }
    _ToggleInterface_setToggleOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ToggleInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setToggleOptions_options = thisDeserializer.readToggleOptions()
    }
    _ToggleAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ToggleInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onChange_value = thisDeserializer.readCallback_Boolean_Void()
    }
    _ToggleAttribute_contentModifier(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ToggleInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.contentModifier_value = (thisDeserializer.readCustomObject("ContentModifier") as ContentModifier<any>)
    }
    _ToggleAttribute_selectedColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ToggleInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const selectedColor_value_buf_selector: number = thisDeserializer.readInt8()
        let selectedColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (selectedColor_value_buf_selector == 0) {
            selectedColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (selectedColor_value_buf_selector == 1) {
            selectedColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (selectedColor_value_buf_selector == 2) {
            selectedColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (selectedColor_value_buf_selector == 3) {
            selectedColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for selectedColor_value_buf has to be chosen through deserialisation.")
        }
        node.selectedColor_value = (selectedColor_value_buf as Color | number | string | Resource)
    }
    _ToggleAttribute_switchPointColor(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ToggleInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const switchPointColor_value_buf_selector: number = thisDeserializer.readInt8()
        let switchPointColor_value_buf: Color | number | string | Resource | undefined|undefined 
        if (switchPointColor_value_buf_selector == 0) {
            switchPointColor_value_buf = (thisDeserializer.readInt32() as Color)
        }
        else if (switchPointColor_value_buf_selector == 1) {
            switchPointColor_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (switchPointColor_value_buf_selector == 2) {
            switchPointColor_value_buf = (thisDeserializer.readString() as string)
        }
        else if (switchPointColor_value_buf_selector == 3) {
            switchPointColor_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for switchPointColor_value_buf has to be chosen through deserialisation.")
        }
        node.switchPointColor_value = (switchPointColor_value_buf as Color | number | string | Resource)
    }
    _ToggleAttribute_switchStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<ToggleInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.switchStyle_value = thisDeserializer.readSwitchStyle()
    }
    _VideoInterface_setVideoOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<VideoInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setVideoOptions_value = thisDeserializer.readVideoOptions()
    }
    _VideoAttribute_muted(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<VideoInterface>(ptr)
        node.muted_value = value
    }
    _VideoAttribute_autoPlay(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<VideoInterface>(ptr)
        node.autoPlay_value = value
    }
    _VideoAttribute_controls(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<VideoInterface>(ptr)
        node.controls_value = value
    }
    _VideoAttribute_loop(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<VideoInterface>(ptr)
        node.loop_value = value
    }
    _VideoAttribute_objectFit(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<VideoInterface>(ptr)
        node.objectFit_value = value
    }
    _VideoAttribute_onStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<VideoInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onStart_value = thisDeserializer.readVoidCallback()
    }
    _VideoAttribute_onPause(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<VideoInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onPause_value = thisDeserializer.readVoidCallback()
    }
    _VideoAttribute_onFinish(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<VideoInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onFinish_value = thisDeserializer.readVoidCallback()
    }
    _VideoAttribute_onFullscreenChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<VideoInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onFullscreenChange_value = thisDeserializer.readCallback_FullscreenInfo_Void()
    }
    _VideoAttribute_onPrepared(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<VideoInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onPrepared_value = thisDeserializer.readCallback_PreparedInfo_Void()
    }
    _VideoAttribute_onSeeking(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<VideoInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSeeking_value = thisDeserializer.readCallback_PlaybackInfo_Void()
    }
    _VideoAttribute_onSeeked(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<VideoInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSeeked_value = thisDeserializer.readCallback_PlaybackInfo_Void()
    }
    _VideoAttribute_onUpdate(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<VideoInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onUpdate_value = thisDeserializer.readCallback_PlaybackInfo_Void()
    }
    _VideoAttribute_onError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<VideoInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onError_value = thisDeserializer.readCallback_Void()
    }
    _VideoAttribute_onStop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<VideoInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onStop_value = thisDeserializer.readCallback_Void()
    }
    _VideoAttribute_enableAnalyzer(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<VideoInterface>(ptr)
        node.enableAnalyzer_value = value
    }
    _VideoAttribute_analyzerConfig(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<VideoInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.analyzerConfig_value = thisDeserializer.readImageAnalyzerConfig()
    }
    _WebInterface_setWebOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setWebOptions_value = thisDeserializer.readWebOptions()
    }
    _WebAttribute_javaScriptAccess(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.javaScriptAccess_value = value
    }
    _WebAttribute_fileAccess(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.fileAccess_value = value
    }
    _WebAttribute_onlineImageAccess(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.onlineImageAccess_value = value
    }
    _WebAttribute_domStorageAccess(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.domStorageAccess_value = value
    }
    _WebAttribute_imageAccess(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.imageAccess_value = value
    }
    _WebAttribute_mixedMode(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.mixedMode_value = value
    }
    _WebAttribute_zoomAccess(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.zoomAccess_value = value
    }
    _WebAttribute_geolocationAccess(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.geolocationAccess_value = value
    }
    _WebAttribute_javaScriptProxy(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.javaScriptProxy_value = thisDeserializer.readJavaScriptProxy()
    }
    _WebAttribute_password(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.password_value = value
    }
    _WebAttribute_cacheMode(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.cacheMode_value = value
    }
    _WebAttribute_darkMode(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.darkMode_value = value
    }
    _WebAttribute_forceDarkAccess(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.forceDarkAccess_value = value
    }
    _WebAttribute_mediaOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.mediaOptions_value = thisDeserializer.readWebMediaOptions()
    }
    _WebAttribute_tableData(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.tableData_value = value
    }
    _WebAttribute_wideViewModeAccess(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.wideViewModeAccess_value = value
    }
    _WebAttribute_overviewModeAccess(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.overviewModeAccess_value = value
    }
    _WebAttribute_overScrollMode(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.overScrollMode_value = value
    }
    _WebAttribute_textZoomAtio(ptr: KPointer, value: number): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.textZoomAtio_value = value
    }
    _WebAttribute_textZoomRatio(ptr: KPointer, value: number): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.textZoomRatio_value = value
    }
    _WebAttribute_databaseAccess(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.databaseAccess_value = value
    }
    _WebAttribute_initialScale(ptr: KPointer, value: number): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.initialScale_value = value
    }
    _WebAttribute_userAgent(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.userAgent_value = value
    }
    _WebAttribute_metaViewport(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.metaViewport_value = value
    }
    _WebAttribute_onPageEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onPageEnd_value = thisDeserializer.readCallback_OnPageEndEvent_Void()
    }
    _WebAttribute_onPageBegin(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onPageBegin_value = thisDeserializer.readCallback_OnPageBeginEvent_Void()
    }
    _WebAttribute_onProgressChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onProgressChange_value = thisDeserializer.readCallback_OnProgressChangeEvent_Void()
    }
    _WebAttribute_onTitleReceive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onTitleReceive_value = thisDeserializer.readCallback_OnTitleReceiveEvent_Void()
    }
    _WebAttribute_onGeolocationHide(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onGeolocationHide_value = thisDeserializer.readCallback_Void()
    }
    _WebAttribute_onGeolocationShow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onGeolocationShow_value = thisDeserializer.readCallback_OnGeolocationShowEvent_Void()
    }
    _WebAttribute_onRequestSelected(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onRequestSelected_value = thisDeserializer.readCallback_Void()
    }
    _WebAttribute_onAlert(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onAlert_value = thisDeserializer.readCallback_OnAlertEvent_Boolean()
    }
    _WebAttribute_onBeforeUnload(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onBeforeUnload_value = thisDeserializer.readCallback_OnBeforeUnloadEvent_Boolean()
    }
    _WebAttribute_onConfirm(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onConfirm_value = thisDeserializer.readCallback_OnConfirmEvent_Boolean()
    }
    _WebAttribute_onPrompt(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onPrompt_value = thisDeserializer.readCallback_OnPromptEvent_Boolean()
    }
    _WebAttribute_onConsole(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onConsole_value = thisDeserializer.readCallback_OnConsoleEvent_Boolean()
    }
    _WebAttribute_onErrorReceive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onErrorReceive_value = thisDeserializer.readCallback_OnErrorReceiveEvent_Void()
    }
    _WebAttribute_onHttpErrorReceive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onHttpErrorReceive_value = thisDeserializer.readCallback_OnHttpErrorReceiveEvent_Void()
    }
    _WebAttribute_onDownloadStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDownloadStart_value = thisDeserializer.readCallback_OnDownloadStartEvent_Void()
    }
    _WebAttribute_onRefreshAccessedHistory(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onRefreshAccessedHistory_value = thisDeserializer.readCallback_OnRefreshAccessedHistoryEvent_Void()
    }
    _WebAttribute_onUrlLoadIntercept(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onUrlLoadIntercept_value = thisDeserializer.readType_WebAttribute_onUrlLoadIntercept_callback()
    }
    _WebAttribute_onSslErrorReceive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSslErrorReceive_value = thisDeserializer.readCallback_Literal_Function_handler_Object_error_Void()
    }
    _WebAttribute_onRenderExited0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onRenderExited0_value = thisDeserializer.readCallback_OnRenderExitedEvent_Void()
    }
    _WebAttribute_onRenderExited1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onRenderExited1_value = thisDeserializer.readCallback_Literal_Object_detail_Boolean()
    }
    _WebAttribute_onShowFileSelector(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onShowFileSelector_value = thisDeserializer.readCallback_OnShowFileSelectorEvent_Boolean()
    }
    _WebAttribute_onFileSelectorShow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onFileSelectorShow_value = thisDeserializer.readCallback_Literal_Function_callback_Object_fileSelector_Void()
    }
    _WebAttribute_onResourceLoad(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onResourceLoad_value = thisDeserializer.readCallback_OnResourceLoadEvent_Void()
    }
    _WebAttribute_onFullScreenExit(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onFullScreenExit_value = thisDeserializer.readCallback_Void()
    }
    _WebAttribute_onFullScreenEnter(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onFullScreenEnter_value = thisDeserializer.readOnFullScreenEnterCallback()
    }
    _WebAttribute_onScaleChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScaleChange_value = thisDeserializer.readCallback_OnScaleChangeEvent_Void()
    }
    _WebAttribute_onHttpAuthRequest(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onHttpAuthRequest_value = thisDeserializer.readCallback_OnHttpAuthRequestEvent_Boolean()
    }
    _WebAttribute_onInterceptRequest(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onInterceptRequest_value = thisDeserializer.readCallback_OnInterceptRequestEvent_WebResourceResponse()
    }
    _WebAttribute_onPermissionRequest(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onPermissionRequest_value = thisDeserializer.readCallback_OnPermissionRequestEvent_Void()
    }
    _WebAttribute_onScreenCaptureRequest(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScreenCaptureRequest_value = thisDeserializer.readCallback_OnScreenCaptureRequestEvent_Void()
    }
    _WebAttribute_onContextMenuShow(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onContextMenuShow_value = thisDeserializer.readCallback_OnContextMenuShowEvent_Boolean()
    }
    _WebAttribute_onContextMenuHide(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onContextMenuHide_value = thisDeserializer.readOnContextMenuHideCallback()
    }
    _WebAttribute_mediaPlayGestureAccess(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.mediaPlayGestureAccess_value = value
    }
    _WebAttribute_onSearchResultReceive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSearchResultReceive_value = thisDeserializer.readCallback_OnSearchResultReceiveEvent_Void()
    }
    _WebAttribute_onScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScroll_value = thisDeserializer.readCallback_OnScrollEvent_Void()
    }
    _WebAttribute_onSslErrorEventReceive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSslErrorEventReceive_value = thisDeserializer.readCallback_OnSslErrorEventReceiveEvent_Void()
    }
    _WebAttribute_onSslErrorEvent(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSslErrorEvent_value = thisDeserializer.readOnSslErrorEventCallback()
    }
    _WebAttribute_onClientAuthenticationRequest(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onClientAuthenticationRequest_value = thisDeserializer.readCallback_OnClientAuthenticationEvent_Void()
    }
    _WebAttribute_onWindowNew(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onWindowNew_value = thisDeserializer.readCallback_OnWindowNewEvent_Void()
    }
    _WebAttribute_onWindowExit(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onWindowExit_value = thisDeserializer.readCallback_Void()
    }
    _WebAttribute_multiWindowAccess(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.multiWindowAccess_value = value
    }
    _WebAttribute_onInterceptKeyEvent(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onInterceptKeyEvent_value = thisDeserializer.readCallback_KeyEvent_Boolean()
    }
    _WebAttribute_webStandardFont(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.webStandardFont_value = value
    }
    _WebAttribute_webSerifFont(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.webSerifFont_value = value
    }
    _WebAttribute_webSansSerifFont(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.webSansSerifFont_value = value
    }
    _WebAttribute_webFixedFont(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.webFixedFont_value = value
    }
    _WebAttribute_webFantasyFont(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.webFantasyFont_value = value
    }
    _WebAttribute_webCursiveFont(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.webCursiveFont_value = value
    }
    _WebAttribute_defaultFixedFontSize(ptr: KPointer, value: number): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.defaultFixedFontSize_value = value
    }
    _WebAttribute_defaultFontSize(ptr: KPointer, value: number): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.defaultFontSize_value = value
    }
    _WebAttribute_minFontSize(ptr: KPointer, value: number): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.minFontSize_value = value
    }
    _WebAttribute_minLogicalFontSize(ptr: KPointer, value: number): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.minLogicalFontSize_value = value
    }
    _WebAttribute_defaultTextEncodingFormat(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.defaultTextEncodingFormat_value = value
    }
    _WebAttribute_forceDisplayScrollBar(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.forceDisplayScrollBar_value = value
    }
    _WebAttribute_blockNetwork(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.blockNetwork_value = value
    }
    _WebAttribute_horizontalScrollBarAccess(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.horizontalScrollBarAccess_value = value
    }
    _WebAttribute_verticalScrollBarAccess(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.verticalScrollBarAccess_value = value
    }
    _WebAttribute_onTouchIconUrlReceived(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onTouchIconUrlReceived_value = thisDeserializer.readCallback_OnTouchIconUrlReceivedEvent_Void()
    }
    _WebAttribute_onFaviconReceived(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onFaviconReceived_value = thisDeserializer.readCallback_OnFaviconReceivedEvent_Void()
    }
    _WebAttribute_onPageVisible(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onPageVisible_value = thisDeserializer.readCallback_OnPageVisibleEvent_Void()
    }
    _WebAttribute_onDataResubmitted(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDataResubmitted_value = thisDeserializer.readCallback_OnDataResubmittedEvent_Void()
    }
    _WebAttribute_pinchSmooth(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.pinchSmooth_value = value
    }
    _WebAttribute_allowWindowOpenMethod(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.allowWindowOpenMethod_value = value
    }
    _WebAttribute_onAudioStateChanged(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onAudioStateChanged_value = thisDeserializer.readCallback_OnAudioStateChangedEvent_Void()
    }
    _WebAttribute_onFirstContentfulPaint(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onFirstContentfulPaint_value = thisDeserializer.readCallback_OnFirstContentfulPaintEvent_Void()
    }
    _WebAttribute_onFirstMeaningfulPaint(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onFirstMeaningfulPaint_value = thisDeserializer.readOnFirstMeaningfulPaintCallback()
    }
    _WebAttribute_onLargestContentfulPaint(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onLargestContentfulPaint_value = thisDeserializer.readOnLargestContentfulPaintCallback()
    }
    _WebAttribute_onLoadIntercept(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onLoadIntercept_value = thisDeserializer.readCallback_OnLoadInterceptEvent_Boolean()
    }
    _WebAttribute_onControllerAttached(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onControllerAttached_value = thisDeserializer.readCallback_Void()
    }
    _WebAttribute_onOverScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onOverScroll_value = thisDeserializer.readCallback_OnOverScrollEvent_Void()
    }
    _WebAttribute_onSafeBrowsingCheckResult(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onSafeBrowsingCheckResult_value = thisDeserializer.readOnSafeBrowsingCheckResultCallback()
    }
    _WebAttribute_onNavigationEntryCommitted(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onNavigationEntryCommitted_value = thisDeserializer.readOnNavigationEntryCommittedCallback()
    }
    _WebAttribute_onIntelligentTrackingPreventionResult(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onIntelligentTrackingPreventionResult_value = thisDeserializer.readOnIntelligentTrackingPreventionCallback()
    }
    _WebAttribute_javaScriptOnDocumentStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const javaScriptOnDocumentStart_value_buf_length: int32 = thisDeserializer.readInt32()
        let javaScriptOnDocumentStart_value_buf: Array<ScriptItem> = new Array<ScriptItem>()
        for (let javaScriptOnDocumentStart_value_buf_i = 0; javaScriptOnDocumentStart_value_buf_i < javaScriptOnDocumentStart_value_buf_length; javaScriptOnDocumentStart_value_buf_i++) {
            javaScriptOnDocumentStart_value_buf[javaScriptOnDocumentStart_value_buf_i] = thisDeserializer.readScriptItem()
        }
        node.javaScriptOnDocumentStart_value = javaScriptOnDocumentStart_value_buf
    }
    _WebAttribute_javaScriptOnDocumentEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const javaScriptOnDocumentEnd_value_buf_length: int32 = thisDeserializer.readInt32()
        let javaScriptOnDocumentEnd_value_buf: Array<ScriptItem> = new Array<ScriptItem>()
        for (let javaScriptOnDocumentEnd_value_buf_i = 0; javaScriptOnDocumentEnd_value_buf_i < javaScriptOnDocumentEnd_value_buf_length; javaScriptOnDocumentEnd_value_buf_i++) {
            javaScriptOnDocumentEnd_value_buf[javaScriptOnDocumentEnd_value_buf_i] = thisDeserializer.readScriptItem()
        }
        node.javaScriptOnDocumentEnd_value = javaScriptOnDocumentEnd_value_buf
    }
    _WebAttribute_layoutMode(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.layoutMode_value = value
    }
    _WebAttribute_nestedScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const nestedScroll_value_buf_selector: number = thisDeserializer.readInt8()
        let nestedScroll_value_buf: NestedScrollOptions | NestedScrollOptionsExt | undefined|undefined 
        if (nestedScroll_value_buf_selector == 0) {
            nestedScroll_value_buf = thisDeserializer.readNestedScrollOptions()
        }
        else if (nestedScroll_value_buf_selector == 1) {
            nestedScroll_value_buf = thisDeserializer.readNestedScrollOptionsExt()
        }
        else {
            throw new Error("One of the branches for nestedScroll_value_buf has to be chosen through deserialisation.")
        }
        node.nestedScroll_value = (nestedScroll_value_buf as NestedScrollOptions | NestedScrollOptionsExt)
    }
    _WebAttribute_enableNativeEmbedMode(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.enableNativeEmbedMode_value = value
    }
    _WebAttribute_onNativeEmbedLifecycleChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onNativeEmbedLifecycleChange_value = thisDeserializer.readCallback_NativeEmbedDataInfo_Void()
    }
    _WebAttribute_onNativeEmbedVisibilityChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onNativeEmbedVisibilityChange_value = thisDeserializer.readOnNativeEmbedVisibilityChangeCallback()
    }
    _WebAttribute_onNativeEmbedGestureEvent(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onNativeEmbedGestureEvent_value = thisDeserializer.readCallback_NativeEmbedTouchInfo_Void()
    }
    _WebAttribute_copyOptions(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.copyOptions_value = value
    }
    _WebAttribute_onOverrideUrlLoading(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onOverrideUrlLoading_value = thisDeserializer.readOnOverrideUrlLoadingCallback()
    }
    _WebAttribute_textAutosizing(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.textAutosizing_value = value
    }
    _WebAttribute_enableNativeMediaPlayer(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.enableNativeMediaPlayer_value = thisDeserializer.readNativeMediaPlayerConfig()
    }
    _WebAttribute_enableSmoothDragResize(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.enableSmoothDragResize_value = value
    }
    _WebAttribute_onRenderProcessNotResponding(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onRenderProcessNotResponding_value = thisDeserializer.readOnRenderProcessNotRespondingCallback()
    }
    _WebAttribute_onRenderProcessResponding(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onRenderProcessResponding_value = thisDeserializer.readOnRenderProcessRespondingCallback()
    }
    _WebAttribute_selectionMenuOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const selectionMenuOptions_value_buf_length: int32 = thisDeserializer.readInt32()
        let selectionMenuOptions_value_buf: Array<ExpandedMenuItemOptions> = new Array<ExpandedMenuItemOptions>()
        for (let selectionMenuOptions_value_buf_i = 0; selectionMenuOptions_value_buf_i < selectionMenuOptions_value_buf_length; selectionMenuOptions_value_buf_i++) {
            selectionMenuOptions_value_buf[selectionMenuOptions_value_buf_i] = thisDeserializer.readExpandedMenuItemOptions()
        }
        node.selectionMenuOptions_value = selectionMenuOptions_value_buf
    }
    _WebAttribute_onViewportFitChanged(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onViewportFitChanged_value = thisDeserializer.readOnViewportFitChangedCallback()
    }
    _WebAttribute_onInterceptKeyboardAttach(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onInterceptKeyboardAttach_value = thisDeserializer.readWebKeyboardCallback()
    }
    _WebAttribute_onAdsBlocked(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onAdsBlocked_value = thisDeserializer.readOnAdsBlockedCallback()
    }
    _WebAttribute_keyboardAvoidMode(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.keyboardAvoidMode_value = value
    }
    _WebAttribute_editMenuOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WebInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.editMenuOptions_value = (thisDeserializer.readEditMenuOptions() as EditMenuOptions)
    }
    _WebAttribute_enableHapticFeedback(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.enableHapticFeedback_value = value
    }
    _WebAttribute_registerNativeEmbedRule(ptr: KPointer, tag: KStringPtr, type: KStringPtr): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.registerNativeEmbedRule_tag = tag
        node.registerNativeEmbedRule_type = type
    }
    _WebAttribute_bindSelectionMenu(ptr: KPointer, elementType: KInt, thisArray: Uint8Array, thisLength: int32, responseType: KInt): void {
        let node = this.ptr2object<WebInterface>(ptr)
        node.bindSelectionMenu_elementType = elementType
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.bindSelectionMenu_content = CallbackTransformer.transformToCustomBuilder(thisDeserializer.readCustomNodeBuilder())
        node.bindSelectionMenu_responseType = thisLength
        const bindSelectionMenu_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let bindSelectionMenu_options_buf: SelectionMenuOptionsExt | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (bindSelectionMenu_options_buf_runtimeType))
        {
            bindSelectionMenu_options_buf = thisDeserializer.readSelectionMenuOptionsExt()
        }
        node.bindSelectionMenu_options = bindSelectionMenu_options_buf
    }
    _WindowSceneInterface_setWindowSceneOptions(ptr: KPointer, persistentId: number): void {
        let node = this.ptr2object<WindowSceneInterface>(ptr)
        node.setWindowSceneOptions_persistentId = persistentId
    }
    _WindowSceneAttribute_attractionEffect(ptr: KPointer, thisArray: Uint8Array, thisLength: int32, fraction: number): void {
        let node = this.ptr2object<WindowSceneInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.attractionEffect_destination = thisDeserializer.readPosition()
        node.attractionEffect_fraction = thisLength
    }
    _XComponentInterface_setXComponentOptions0(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<XComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setXComponentOptions0_value_buf_id: string = (thisDeserializer.readString() as string)
        const setXComponentOptions0_value_buf_type: string = (thisDeserializer.readString() as string)
        const setXComponentOptions0_value_buf_libraryname_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setXComponentOptions0_value_buf_libraryname_buf: string | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setXComponentOptions0_value_buf_libraryname_buf_runtimeType))
        {
            setXComponentOptions0_value_buf_libraryname_buf = (thisDeserializer.readString() as string)
        }
        const setXComponentOptions0_value_buf_libraryname: undefined | string = setXComponentOptions0_value_buf_libraryname_buf
        const setXComponentOptions0_value_buf_controller_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setXComponentOptions0_value_buf_controller_buf: XComponentController | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setXComponentOptions0_value_buf_controller_buf_runtimeType))
        {
            setXComponentOptions0_value_buf_controller_buf = (thisDeserializer.readXComponentController() as XComponentController)
        }
        const setXComponentOptions0_value_buf_controller: undefined | XComponentController = setXComponentOptions0_value_buf_controller_buf
        node.setXComponentOptions0_value = ({id: setXComponentOptions0_value_buf_id, type: setXComponentOptions0_value_buf_type, libraryname: setXComponentOptions0_value_buf_libraryname, controller: setXComponentOptions0_value_buf_controller} as { id: string, type: string, libraryname?: string, controller?: XComponentController })
    }
    _XComponentInterface_setXComponentOptions1(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<XComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setXComponentOptions1_value_buf_id: string = (thisDeserializer.readString() as string)
        const setXComponentOptions1_value_buf_type: string = (thisDeserializer.readString() as string)
        const setXComponentOptions1_value_buf_libraryname_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setXComponentOptions1_value_buf_libraryname_buf: string | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setXComponentOptions1_value_buf_libraryname_buf_runtimeType))
        {
            setXComponentOptions1_value_buf_libraryname_buf = (thisDeserializer.readString() as string)
        }
        const setXComponentOptions1_value_buf_libraryname: undefined | string = setXComponentOptions1_value_buf_libraryname_buf
        const setXComponentOptions1_value_buf_controller_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setXComponentOptions1_value_buf_controller_buf: XComponentController | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setXComponentOptions1_value_buf_controller_buf_runtimeType))
        {
            setXComponentOptions1_value_buf_controller_buf = (thisDeserializer.readXComponentController() as XComponentController)
        }
        const setXComponentOptions1_value_buf_controller: undefined | XComponentController = setXComponentOptions1_value_buf_controller_buf
        node.setXComponentOptions1_value = ({id: setXComponentOptions1_value_buf_id, type: setXComponentOptions1_value_buf_type, libraryname: setXComponentOptions1_value_buf_libraryname, controller: setXComponentOptions1_value_buf_controller} as { id: string, type: string, libraryname?: string, controller?: XComponentController })
    }
    _XComponentInterface_setXComponentOptions2(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<XComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setXComponentOptions2_options = thisDeserializer.readXComponentOptions()
    }
    _XComponentAttribute_onLoad(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<XComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onLoad_value = thisDeserializer.readOnNativeLoadCallback()
    }
    _XComponentAttribute_onDestroy(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<XComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onDestroy_value = thisDeserializer.readVoidCallback()
    }
    _XComponentAttribute_enableAnalyzer(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<XComponentInterface>(ptr)
        node.enableAnalyzer_value = value
    }
    _XComponentAttribute_enableSecure(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<XComponentInterface>(ptr)
        node.enableSecure_value = value
    }
    _SideBarContainerInterface_setSideBarContainerOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SideBarContainerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setSideBarContainerOptions_type_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setSideBarContainerOptions_type_buf: SideBarContainerType | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setSideBarContainerOptions_type_buf_runtimeType))
        {
            setSideBarContainerOptions_type_buf = (thisDeserializer.readInt32() as SideBarContainerType)
        }
        node.setSideBarContainerOptions_type = setSideBarContainerOptions_type_buf
    }
    _SideBarContainerAttribute_showSideBar(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SideBarContainerInterface>(ptr)
        node.showSideBar_value = value
    }
    _SideBarContainerAttribute_controlButton(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SideBarContainerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.controlButton_value = thisDeserializer.readButtonStyle()
    }
    _SideBarContainerAttribute_showControlButton(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SideBarContainerInterface>(ptr)
        node.showControlButton_value = value
    }
    _SideBarContainerAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SideBarContainerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onChange_value = thisDeserializer.readCallback_Boolean_Void()
    }
    _SideBarContainerAttribute_sideBarWidth0(ptr: KPointer, value: number): void {
        let node = this.ptr2object<SideBarContainerInterface>(ptr)
        node.sideBarWidth0_value = value
    }
    _SideBarContainerAttribute_sideBarWidth1(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<SideBarContainerInterface>(ptr)
        node.sideBarWidth1_value = value
    }
    _SideBarContainerAttribute_minSideBarWidth0(ptr: KPointer, value: number): void {
        let node = this.ptr2object<SideBarContainerInterface>(ptr)
        node.minSideBarWidth0_value = value
    }
    _SideBarContainerAttribute_minSideBarWidth1(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<SideBarContainerInterface>(ptr)
        node.minSideBarWidth1_value = value
    }
    _SideBarContainerAttribute_maxSideBarWidth0(ptr: KPointer, value: number): void {
        let node = this.ptr2object<SideBarContainerInterface>(ptr)
        node.maxSideBarWidth0_value = value
    }
    _SideBarContainerAttribute_maxSideBarWidth1(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<SideBarContainerInterface>(ptr)
        node.maxSideBarWidth1_value = value
    }
    _SideBarContainerAttribute_autoHide(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SideBarContainerInterface>(ptr)
        node.autoHide_value = value
    }
    _SideBarContainerAttribute_sideBarPosition(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<SideBarContainerInterface>(ptr)
        node.sideBarPosition_value = value
    }
    _SideBarContainerAttribute_divider(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<SideBarContainerInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const divider_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let divider_value_buf: DividerStyle | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (divider_value_buf_runtimeType))
        {
            divider_value_buf = thisDeserializer.readDividerStyle()
        }
        node.divider_value = divider_value_buf
    }
    _SideBarContainerAttribute_minContentWidth(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<SideBarContainerInterface>(ptr)
        node.minContentWidth_value = value
    }
    _RemoteWindowInterface_setRemoteWindowOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<RemoteWindowInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setRemoteWindowOptions_target = thisDeserializer.readWindowAnimationTarget()
    }
    _WaterFlowInterface_setWaterFlowOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WaterFlowInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setWaterFlowOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setWaterFlowOptions_options_buf: WaterFlowOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setWaterFlowOptions_options_buf_runtimeType))
        {
            setWaterFlowOptions_options_buf = thisDeserializer.readWaterFlowOptions()
        }
        node.setWaterFlowOptions_options = setWaterFlowOptions_options_buf
    }
    _WaterFlowAttribute_columnsTemplate(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<WaterFlowInterface>(ptr)
        node.columnsTemplate_value = value
    }
    _WaterFlowAttribute_itemConstraintSize(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WaterFlowInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.itemConstraintSize_value = thisDeserializer.readConstraintSizeOptions()
    }
    _WaterFlowAttribute_rowsTemplate(ptr: KPointer, value: KStringPtr): void {
        let node = this.ptr2object<WaterFlowInterface>(ptr)
        node.rowsTemplate_value = value
    }
    _WaterFlowAttribute_columnsGap(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<WaterFlowInterface>(ptr)
        node.columnsGap_value = value
    }
    _WaterFlowAttribute_rowsGap(ptr: KPointer, value: Length): void {
        let node = this.ptr2object<WaterFlowInterface>(ptr)
        node.rowsGap_value = value
    }
    _WaterFlowAttribute_layoutDirection(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WaterFlowInterface>(ptr)
        node.layoutDirection_value = value
    }
    _WaterFlowAttribute_nestedScroll(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WaterFlowInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.nestedScroll_value = thisDeserializer.readNestedScrollOptions()
    }
    _WaterFlowAttribute_enableScrollInteraction(ptr: KPointer, value: KInt): void {
        let node = this.ptr2object<WaterFlowInterface>(ptr)
        node.enableScrollInteraction_value = value
    }
    _WaterFlowAttribute_friction(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WaterFlowInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const friction_value_buf_selector: number = thisDeserializer.readInt8()
        let friction_value_buf: number | Resource | undefined|undefined 
        if (friction_value_buf_selector == 0) {
            friction_value_buf = (thisDeserializer.readNumber() as number)
        }
        else if (friction_value_buf_selector == 1) {
            friction_value_buf = thisDeserializer.readResource()
        }
        else {
            throw new Error("One of the branches for friction_value_buf has to be chosen through deserialisation.")
        }
        node.friction_value = (friction_value_buf as number | Resource)
    }
    _WaterFlowAttribute_cachedCount0(ptr: KPointer, value: number): void {
        let node = this.ptr2object<WaterFlowInterface>(ptr)
        node.cachedCount0_value = value
    }
    _WaterFlowAttribute_cachedCount1(ptr: KPointer, count: number, show: KInt): void {
        let node = this.ptr2object<WaterFlowInterface>(ptr)
        node.cachedCount1_count = count
        node.cachedCount1_show = show
    }
    _WaterFlowAttribute_onReachStart(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WaterFlowInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onReachStart_value = thisDeserializer.readCallback_Void()
    }
    _WaterFlowAttribute_onReachEnd(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WaterFlowInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onReachEnd_value = thisDeserializer.readCallback_Void()
    }
    _WaterFlowAttribute_onScrollFrameBegin(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WaterFlowInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScrollFrameBegin_value = thisDeserializer.readCallback_Number_ScrollState_Literal_Number_offsetRemain()
    }
    _WaterFlowAttribute_onScrollIndex(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<WaterFlowInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onScrollIndex_value = thisDeserializer.readCallback_Number_Number_Void()
    }
    _UIExtensionComponentInterface_setUIExtensionComponentOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<UIExtensionComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.setUIExtensionComponentOptions_want = thisDeserializer.readWant()
        const setUIExtensionComponentOptions_options_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setUIExtensionComponentOptions_options_buf: UIExtensionOptions | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setUIExtensionComponentOptions_options_buf_runtimeType))
        {
            setUIExtensionComponentOptions_options_buf = thisDeserializer.readUIExtensionOptions()
        }
        node.setUIExtensionComponentOptions_options = setUIExtensionComponentOptions_options_buf
    }
    _UIExtensionComponentAttribute_onRemoteReady(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<UIExtensionComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onRemoteReady_value = thisDeserializer.readCallback_UIExtensionProxy_Void()
    }
    _UIExtensionComponentAttribute_onReceive(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<UIExtensionComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onReceive_value = thisDeserializer.readReceiveCallback()
    }
    _UIExtensionComponentAttribute_onResult(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<UIExtensionComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onResult_value = thisDeserializer.readCallback_Literal_Number_code_Want_want_Void()
    }
    _UIExtensionComponentAttribute_onRelease(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<UIExtensionComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onRelease_value = thisDeserializer.readCallback_Number_Void()
    }
    _UIExtensionComponentAttribute_onError(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<UIExtensionComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onError_value = thisDeserializer.readCustomObject("ErrorCallback")
    }
    _UIExtensionComponentAttribute_onTerminated(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<UIExtensionComponentInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        node.onTerminated_value = thisDeserializer.readCallback_TerminationInfo_Void()
    }
    _LinearIndicatorInterface_setLinearIndicatorOptions(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<LinearIndicatorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const setLinearIndicatorOptions_count_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setLinearIndicatorOptions_count_buf: number | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setLinearIndicatorOptions_count_buf_runtimeType))
        {
            setLinearIndicatorOptions_count_buf = (thisDeserializer.readNumber() as number)
        }
        node.setLinearIndicatorOptions_count = setLinearIndicatorOptions_count_buf
        const setLinearIndicatorOptions_controller_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let setLinearIndicatorOptions_controller_buf: LinearIndicatorController | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (setLinearIndicatorOptions_controller_buf_runtimeType))
        {
            setLinearIndicatorOptions_controller_buf = (thisDeserializer.readLinearIndicatorController() as LinearIndicatorController)
        }
        node.setLinearIndicatorOptions_controller = setLinearIndicatorOptions_controller_buf
    }
    _LinearIndicatorAttribute_indicatorStyle(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<LinearIndicatorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const indicatorStyle_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let indicatorStyle_value_buf: LinearIndicatorStyle | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (indicatorStyle_value_buf_runtimeType))
        {
            indicatorStyle_value_buf = thisDeserializer.readLinearIndicatorStyle()
        }
        node.indicatorStyle_value = indicatorStyle_value_buf
    }
    _LinearIndicatorAttribute_indicatorLoop(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<LinearIndicatorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const indicatorLoop_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let indicatorLoop_value_buf: boolean | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (indicatorLoop_value_buf_runtimeType))
        {
            indicatorLoop_value_buf = thisDeserializer.readBoolean()
        }
        node.indicatorLoop_value = indicatorLoop_value_buf
    }
    _LinearIndicatorAttribute_onChange(ptr: KPointer, thisArray: Uint8Array, thisLength: int32): void {
        let node = this.ptr2object<LinearIndicatorInterface>(ptr)
        const thisDeserializer = new Deserializer(thisArray.buffer, thisLength)
        const onChange_value_buf_runtimeType = (thisDeserializer.readInt8() as int32)
        let onChange_value_buf: OnLinearIndicatorChangeCallback | undefined|undefined 
        if ((RuntimeType.UNDEFINED) != (onChange_value_buf_runtimeType))
        {
            onChange_value_buf = thisDeserializer.readOnLinearIndicatorChangeCallback()
        }
        node.onChange_value = onChange_value_buf
    }
}