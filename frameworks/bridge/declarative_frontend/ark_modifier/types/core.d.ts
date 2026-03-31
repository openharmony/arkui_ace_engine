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

type KNode = number | null;
type NodePtr = number;

declare interface Resource {
    bundleName: string;
    moduleName: string;
    id: number;
    params?: Array<string | number | Resource>;
    type?: number;
}

declare enum Color {
    White = 0,
    Black = 1,
    Blue = 2,
    Brown = 3,
    Gray = 4,
    Green = 5,
    Grey = 6,
    Orange = 7,
    Pink = 8,
    Red = 9,
    Yellow = 10,
    Transparent = 11
}

type PixelMap = object;

declare enum ModifierType {
    ORIGIN = 0,
    STATE = 1,
    FRAME_NODE = 2,
    EXPOSE_MODIFIER = 3,
}

interface CommonAttribute {}
interface BlankAttribute extends CommonAttribute {}
interface ColumnAttribute extends CommonAttribute {}
interface ColumnSplitAttribute extends CommonAttribute {}
interface DividerAttribute extends CommonAttribute {}
interface FlexAttribute extends CommonAttribute {}
interface GridRowAttribute extends CommonAttribute {}
interface GridAttribute extends CommonAttribute {}
interface GridColAttribute extends CommonAttribute {}
interface ImageAttribute extends CommonAttribute {}
interface ImageAnimatorAttribute extends CommonAttribute {}
interface ImageSpanAttribute extends CommonAttribute {}
interface PatternLockAttribute extends CommonAttribute {}
interface RichEditorAttribute extends CommonAttribute {}
interface RowAttribute extends CommonAttribute {}
interface RowSplitAttribute extends CommonAttribute {}
interface SearchAttribute extends CommonAttribute {}
interface SpanAttribute extends CommonAttribute {}
interface SideBarContainerAttribute extends CommonAttribute {}
interface StackAttribute extends CommonAttribute {}
interface FolderStackAttribute extends CommonAttribute {}
interface TextAttribute extends CommonAttribute {}
interface TextAreaAttribute extends CommonAttribute {}
interface TextInputAttribute extends CommonAttribute {}
interface VideoAttribute extends CommonAttribute {}
interface ButtonAttribute extends CommonAttribute {}
interface LoadingProgressAttribute extends CommonAttribute {}
interface RefreshAttribute extends CommonAttribute {}
interface ScrollAttribute extends CommonAttribute {}
interface ToggleAttribute extends CommonAttribute {}
interface SelectAttribute extends CommonAttribute {}
interface RadioAttribute extends CommonAttribute {}
interface TimePickerAttribute extends CommonAttribute {}
interface TextPickerAttribute extends CommonAttribute {}
interface SliderAttribute extends CommonAttribute {}
interface RatingAttribute extends CommonAttribute {}
interface CheckboxAttribute extends CommonAttribute {}
interface NavDestinationAttribute extends CommonAttribute {}
interface StepperAttribute extends CommonAttribute {}
interface CounterAttribute extends CommonAttribute {}
interface CheckboxGroupAttribute extends CommonAttribute {}
interface PanelAttribute extends CommonAttribute {}
interface NavigationAttribute extends CommonAttribute {}
interface NavRouterAttribute extends CommonAttribute {}
interface NavigatorAttribute extends CommonAttribute {}
interface AlphabetIndexerAttribute extends CommonAttribute {}
interface CalendarPickerAttribute extends CommonAttribute {}
interface DataPanelAttribute extends CommonAttribute {}
interface DatePickerAttribute extends CommonAttribute {}
interface FormComponentAttribute extends CommonAttribute {}
interface EmbeddedComponentAttribute extends CommonAttribute {}
interface IsolatedComponentAttribute extends CommonAttribute {}
interface GaugeAttribute extends CommonAttribute {}
interface MarqueeAttribute extends CommonAttribute {}
interface MenuAttribute extends CommonAttribute {}
interface MenuItemAttribute extends CommonAttribute {}
interface MenuItemGroupAttribute extends CommonAttribute {}
interface PluginComponentAttribute extends CommonAttribute {}
interface ProgressAttribute extends CommonAttribute {}
interface QRCodeAttribute extends CommonAttribute {}
interface RichTextAttribute extends CommonAttribute {}
interface ScrollBarAttribute extends CommonAttribute {}
interface StepperItemAttribute extends CommonAttribute {}
interface TextClockAttribute extends CommonAttribute {}
interface TextTimerAttribute extends CommonAttribute {}
interface WebAttribute extends CommonAttribute {}
interface XComponentAttribute extends CommonAttribute {}
interface BadgeAttribute extends CommonAttribute {}
interface FlowItemAttribute extends CommonAttribute {}
interface FormLinkAttribute extends CommonAttribute {}
interface GridItemAttribute extends CommonAttribute {}
interface HyperlinkAttribute extends CommonAttribute {}
interface ListAttribute extends CommonAttribute {}
interface ListItemAttribute extends CommonAttribute {}
interface ListItemGroupAttribute extends CommonAttribute {}
interface RelativeContainerAttribute extends CommonAttribute {}
interface SwiperAttribute extends CommonAttribute {}
interface TabsAttribute extends CommonAttribute {}
interface TabContentAttribute extends CommonAttribute {}
interface UIExtensionComponentAttribute extends CommonAttribute {}
interface WaterFlowAttribute extends CommonAttribute {}
interface ShapeAttribute extends CommonAttribute {}
interface CommonShapeMethod<T> extends CommonAttribute {}
interface CircleAttribute extends CommonAttribute {}
interface EllipseAttribute extends CommonAttribute {}
interface LineAttribute extends CommonAttribute {}
interface PolylineAttribute extends CommonAttribute {}
interface PolygonAttribute extends CommonAttribute {}
interface PathAttribute extends CommonAttribute {}
interface RectAttribute extends CommonAttribute {}
interface CanvasAttribute extends CommonAttribute {}
interface EffectComponentAttribute extends CommonAttribute {}
interface RemoteWindowAttribute extends CommonAttribute {}
interface ParticleAttribute extends CommonAttribute {}
interface SymbolGlyphAttribute extends CommonAttribute {}
interface SymbolSpanAttribute extends CommonAttribute {}
interface Component3DAttribute extends CommonAttribute {}
interface ContainerSpanAttribute extends CommonAttribute {}
interface LazyVGridLayoutAttribute extends CommonAttribute {}

type ResourceColor = Resource | string | number | Color;
type ResourceStr = string | Resource;
type Length = string | number | Resource;
type Dimension = string | number | Resource;
type Padding = Length | { top?: Length; bottom?: Length; left?: Length; right?: Length };
type Margin = Length | { top?: Length; bottom?: Length; left?: Length; right?: Length };
type SizeOptions = { width?: Length; height?: Length };
type ConstraintSizeOptions = { minWidth?: Length; maxWidth?: Length; minHeight?: Length; maxHeight?: Length };
type Position = { x?: Length; y?: Length } | { x: Length; y: Length };
type TranslateOptions = { x?: number; y?: number; z?: number };
type ScaleOptions = { x?: number; y?: number; z?: number; centerX?: number; centerY?: number };
type RotateOptions = { x?: number; y?: number; z?: number; angle?: number | string; centerX?: number | string; centerY?: number | string };
type OutlineOptions = object;
type EdgeColors = { top?: ResourceColor; bottom?: ResourceColor; left?: ResourceColor; right?: ResourceColor };
type EdgeStyles = { top?: BorderStyle; bottom?: BorderStyle; left?: BorderStyle; right?: BorderStyle };
type EdgeWidths = { top?: Length; bottom?: Length; left?: Length; right?: Length };
type BorderRadiuses = { topLeft?: Length; topRight?: Length; bottomLeft?: Length; bottomRight?: Length };
type OutlineRadiuses = BorderRadiuses;
type BorderOptions = { width?: Length | EdgeWidths; color?: ResourceColor | EdgeColors; style?: BorderStyle | EdgeStyles; radius?: Length | BorderRadiuses };
type BorderImageOption = object;
type BackgroundOptions = { color?: ResourceColor };
type BackgroundEffectOptions = object;
type BackgroundBrightnessOptions = object;
type BrightnessOptions = object;
type ForegroundBlurStyleOptions = object;
type BackgroundBlurStyleOptions = object;
type DragPreviewOptions = object;
type DragInteractionOptions = object;
type Rectangle = { x?: number; y?: number; width?: number; height?: number };
type SafeAreaType = 'system' | 'cutout' | 'keyboard';
type SafeAreaEdge = 'top' | 'bottom' | 'left' | 'right';
type HitTestMode = 'default' | 'block' | 'transparent' | 'none';
type LengthMetrics = object;
type LocalizedPadding = object;
type ImageRepeat = 'noRepeat' | 'repeat' | 'repeatX' | 'repeatY';
type ImageSize = { width?: number; height?: number } | 'cover' | 'contain' | 'auto';
type Alignment = 'topLeft' | 'top' | 'topRight' | 'left' | 'center' | 'right' | 'bottomLeft' | 'bottom' | 'bottomRight';
type BlurStyle = 'thin' | 'regular' | 'thick' | 'backgroundThin' | 'backgroundRegular' | 'backgroundThick' | 'backgroundUltraThick';
type ClickEvent = object;
type HoverEvent = object;
type HoverEffect = 'auto' | 'scale' | 'highlight' | 'none';
type MouseEvent = object;
type TouchEvent = object;
type KeyEvent = object;
type AnimateParam = object;
type TransitionOptions = object;
type TransitionEffect = object;
type GestureType = object;
type GestureMask = 'normal' | 'ignoreInternal';
type LinearGradientBlurOptions = object;
type LinearGradient = object;
type GradientDirection = 'left' | 'right' | 'top' | 'bottom' | 'leftTop' | 'leftBottom' | 'rightTop' | 'rightBottom' | 'none';
type MotionPathOptions = object;
type ShadowOptions = { radius: number; color?: ResourceColor; offsetX?: number; offsetY?: number };
type ShadowStyle = 'outerDefaultXG' | 'outerFloatingSM' | 'outerFloatingMD' | 'outerFloatingLG';
type ProgressMask = object;
type PopupOptions = object;
type CustomPopupOptions = object;
type TipsMessageType = string | Resource;
type TipsOptions = object;
type MenuElement = { value?: string | Resource; icon?: string | Resource; action?: () => void };
type MenuOptions = object;
type ResponseType = 'rightClick' | 'longPress';
type ContextMenuOptions = object;
type ModalTransition = object;
type ContentCoverOptions = object;
type BlendMode = object;
type BlendApplyType = object;
type SheetOptions = object;
type StateStyles = object;
type Visibility = 'visible' | 'hidden' | 'none';
type ItemAlign = 'auto' | 'start' | 'center' | 'end' | 'stretch' | 'baseline';
type Direction = 'ltr' | 'rtl' | 'auto';
type FlexAlign = 'start' | 'center' | 'end' | 'spaceBetween' | 'spaceAround' | 'spaceEvenly';
type HorizontalAlign = 'start' | 'center' | 'end';
type sharedTransitionOptions = object;
type AlignRuleOption = object;
type ClickEffect = object;
type DragEvent = object;
type CustomBuilder = () => object | void;
type DragItemInfo = object;
type SpringLoadingContext = object;
type DragSpringLoadingConfiguration = object;
type DropOptions = object;
type PreDragStatus = object;
type UniformDataType = string;
type PixelStretchEffectOptions = object;
type FunctionKey = object;
type ModifierKey = object;
type ObscuredReasons = object;
type RenderFit = object;
type Area = object;
type GestureInfo = object;
type BaseGestureEvent = object;
type GestureJudgeResult = 'continue' | 'reject' | 'pending';
type BarState = 'off' | 'on' | 'auto';
type ComputedBarAttribute = object;
type ItemDragInfo = object;
type EdgeEffect = 'spring' | 'fade' | 'none';
type EdgeEffectOptions = object;
type GridDirection = 'row' | 'column' | 'rowReverse' | 'columnReverse';
type LineCapStyle = 'butt' | 'round' | 'square';
type PointLightStyle = object;
type ColoringStrategy = 'invert' | 'average' | 'primary';

type TextAlign = 'start' | 'center' | 'end' | 'justify';
type TextOverflow = 'clip' | 'ellipsis' | 'none';
type FontWeight = 'lighter' | 'normal' | 'regular' | 'medium' | 'bold' | 'bolder' | number;
type FontStyle = 'normal' | 'italic';
type TextDecorationType = 'none' | 'underline' | 'lineThrough' | 'overline';
type TextDecorationStyle = 'solid' | 'double' | 'dotted' | 'dashed' | 'wavy';
type TextCase = 'normal' | 'lowerCase' | 'upperCase';
type WordBreak = 'normal' | 'breakAll' | 'breakWord' | 'hyphenation';
type EllipsisMode = 'start' | 'center' | 'end';
type TextHeightAdaptivePolicy = 'maxLinesFirst' | 'minFontSizeFirst' | 'layoutFirst';
type TextShadowOptions = { radius: number; type?: ShadowType; color?: ResourceColor; offsetX?: number; offsetY?: number; fill?: boolean };
type ShadowType = 'color' | 'blur';
type SelectionOptions = object;
type TextDataDetectorType = 'phoneNumber' | 'url' | 'email' | 'address' | 'dateTime' | 'currency';
type TextDataDetectorConfig = object;
type LineSpacingOptions = object;

type VoidCallback = () => void;
type Callback<T = object, R = void> = (value: T) => R;
type PasteEvent = { text: string };

type ImageFit = 'cover' | 'contain' | 'fill' | 'none' | 'scaleDown';
type ImageRenderMode = 'original' | 'template';
type ImageInterpolation = 'none' | 'low' | 'medium' | 'high';
type ImageSpanAlignment = 'baseline' | 'bottom' | 'center' | 'top';

type CopyOptions = 'none' | 'inApp' | 'local' | 'distributed';
type TextInputType = 'text' | 'multiline' | 'number' | 'numberPassword' | 'email' | 'password' | 'phoneNumber' | 'userName' | 'newPassword';
type TextInputAction = 'none' | 'default' | 'go' | 'search' | 'send' | 'next' | 'done' | 'previous';
type TextAreaType = 'text' | 'multiline' | 'number' | 'numberPassword' | 'email' | 'password' | 'phoneNumber' | 'userName' | 'newPassword';
type EnterKeyType = 'go' | 'search' | 'send' | 'next' | 'done' | 'previous';
type InputStyle = 'default' | 'inline';
type TextContentStyle = 'default' | 'inline';
type CancelButtonStyle = 'constant' | 'invoker';
type SearchButtonOptions = { fontSize?: Length; fontColor?: ResourceColor };
type ShowCounterOptions = { showCounter?: boolean; highlightBorder?: boolean; thresholdPercentage?: number };
type PasswordIcon = { onIconSrc?: string | Resource; offIconSrc?: string | Resource };
type CaretStyle = { width?: Length; color?: ResourceColor };
type SearchType = 'normal' | 'search';

type OnTextSelectionChangeCallback = (selectionStart: number, selectionEnd: number) => void;
type OnContentScrollCallback = (offsetX: number, offsetY: number) => void;
type OnPasteCallback = (event: PasteEvent) => void;
type SearchSubmitCallback = (searchText: string) => void;
type EditableTextOnChangeCallback = (value: string) => void;
type OnMenuShowCallback = () => void;
type OnMenuHideCallback = () => void;
type OnMenuItemClickCallback = (index: number) => void;
type OnMenuStateChangeCallback = (state: number) => void;
type OnProgressChangeCallback = (value: number) => void;
type OnScrollCallback = (scrollOffset: number, scrollState: ScrollState) => void;
type OnScrollIndexCallback = (first: number, last: number) => void;
type OnScrollStartCallback = () => void;
type OnScrollStopCallback = () => void;
type OnReachStartCallback = () => void;
type OnReachEndCallback = () => void;
type OnItemDeleteCallback = (index: number) => boolean;
type OnItemMoveCallback = (from: number, to: number) => boolean;
type OnItemDragStartCallback = (event: ItemDragInfo, itemIndex: number) => void | (() => object);
type OnItemDragEnterCallback = (event: ItemDragInfo) => void;
type OnItemDragMoveCallback = (event: ItemDragInfo, itemIndex: number, insertIndex: number) => void;
type OnItemDragLeaveCallback = (event: ItemDragInfo, itemIndex: number) => void;
type OnItemDropCallback = (event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void;
type OnCheckboxChangeCallback = (value: boolean) => void;
type OnCheckboxGroupChangeCallback = (event: CheckboxGroupResult) => void;
type OnRadioChangeCallback = (isChecked: boolean) => void;
type OnRatingChangeCallback = (value: number) => void;
type OnSliderChangeCallback = (value: number, mode: SliderChangeMode) => void;
type OnScrollFrameBeginCallback = (offset: number, state: ScrollState) => { offsetRemain: number };
type OnPatternLockInputCompleteCallback = (input: Array<number>) => void;
type OnPatternLockDotConnectCallback = () => void;

type SliderChangeMode = 'begin' | 'moving' | 'end' | 'click';
type SliderBlockStyle = { type?: SliderBlockType; image?: string | Resource; shape?: CircleAttribute | EllipseAttribute | PathAttribute | RectAttribute };
type SliderBlockType = 'default' | 'image' | 'shape';
type SliderOptions = object;
type ColorMetricsLinearGradient = object;
type SliderShowStepOptions = object;
type SliderInteraction = object;
type SlideRange = object;
type SliderPrefixOptions = object;
type SliderSuffixOptions = object;

type ToggleType = 'checkbox' | 'switch' | 'button';

type ArrowPosition = 'end' | 'start' | 'center';
type OptionWidthMode = 'default' | 'fit_content' | 'fit_trigger';
type DividerStyleOptions = object;

type CalendarAlign = 'start' | 'center' | 'end';
type CalendarTextStyle = object;
type DatePickerResult = { year: number; month: number; day: number };
type PickerTextStyle = object;
type TimePickerResult = { hour: number; minute: number; second: number };

type FormDimension = '1*2' | '2*2' | '2*4' | '4*4' | '2*1' | '1*1';

type GaugeLabelConfig = object;
type GaugeIndicator = object | null;
type GaugeDescription = object | null;
type GaugeShadowOptions = object;

type SwiperDisplayMode = 'stretch' | 'auto_linear';
type ArrowStyle = object | boolean;
type SwiperAnimationEvent = object;
type SwiperContentDidScrollEvent = object;
type SwiperContentWillScrollCallback = object;
type SwiperNestedScrollMode = 'selfOnly' | 'parentFirst';
type BarPosition = 'start' | 'end';
type BarMode = 'fixed' | 'scrollable';
type BarModeOptions = object;
type LayoutStyle = 'alwaysCenter' | 'alwaysAverageSplit' | 'spaceAroundAverage' | 'alwaysScrollable';
type TabsAnimationMode = 'none' | 'content' | 'actionSheet';
type ScrollableBarModeOptions = object;
type BarOverlapOptions = object;
type TabBarOptions = object | CustomBuilder;
type FlexDirection = 'row' | 'rowReverse' | 'column' | 'columnReverse';
type ScrollState = 'idle' | 'scroll' | 'fling';
type ListDividerStyle = object;
type ChainAnimationOptions = object;
type ChainEdgeEffect = 'default' | 'stretch' | 'none' | 'clip';
type ListItemAlign = 'start' | 'center' | 'end';
type ChildrenMainSize = object;
type SelectionStyle = object;
type SwipeActionOptions = object;
type SwipeActionItem = object;
type SwipeEdgeEffect = 'spring' | 'none';
type ListItemGroupDividerStyle = object;

type ProgressStyle = object;
type ProgressConfiguration = object;
type LineJoinStyle = 'miter' | 'round' | 'bevel';
type ColumnSplitDividerStyle = object;
type RowSplitDividerStyle = object;

type NavDestinationCommonTitle = object;
type NavDestinationCustomTitle = object;
type TitleHeight = 'mainOnly' | 'mainWithSub';
type NavMenuItem = object;
type NavDestinationMode = 'standard' | 'dialog';
type NavDestinationInfo = object;
type NavigationCommonTitle = object;
type NavigationCustomTitle = object;
type NavigationTitleMode = 'free' | 'full' | 'mini';
type ToolBarOptions = object;
type ToolBarItemStatus = 'normal' | 'disabled' | 'active';
type SymbolOptions = object;
type SymbolRenderingStrategy = 'single' | 'multiple' | 'hierarchical';
type SymbolEffectStrategy = 'none' | 'scale' | 'hierarchical' | 'appear';
type NavBarPosition = 'start' | 'end';
type NavigationMode = 'stack' | 'split' | 'auto';
type NavigationType = 'push' | 'replace' | 'back';

type PanelMode = 'mini' | 'half' | 'full' | 'temporary';
type CheckboxGroupResult = object;
type ItemState = 'normal' | 'disabled' | 'waiting' | 'skip';
type RadioStyle = object;

type MarqueeUpdateStrategy = object;

type RichEditorParagraphStyle = object;
type RichEditorInsertValue = object;
type RichEditorTextSpanResult = object;
type RichEditorDeleteValue = object;
type RichEditorResponseType = object;
type PlaceholderStyle = object;
type SelectionMenuOptions = object;
type ComponentContent = object;
type CutEvent = object;
type CopyEvent = object;
type EditMenuOptions = object;
type UndoStyle = object;
type ColorMetrics = object;
type SelectedDragPreviewStyle = object;
type KeyboardAppearance = 'default' | 'dark' | 'light';
type TextRange = object;
type IMEClient = object;
type CancelButtonOptions = object;
type CancelButtonSymbolOptions = object;
type TextDirection = 'ltr' | 'rtl' | 'auto';
type SubMenuExpandingMode = object;
type CircleStyleOptions = object;
type LocalizedBorderRadiuses = object;
type LocalizedEdgeColors = object;
type LocalizedPadding = object;
type CrownSensitivity = object;
type InsertValue = object;
type DeleteValue = object;
type AutoCapitalizationMode = 'none' | 'words' | 'sentences' | 'characters';
type EditableTextChangeValue = object;

type CheckboxOptions = object;
type CheckboxGroupOptions = object;
type RadioOptions = object;
type CheckBoxConfiguration = object;
type RadioConfiguration = object;
type DataPanelConfiguration = object;
type DataPanelShadowOptions = object;
type GaugeConfiguration = object;
type GaugeIndicatorOptions = object;
type StarStyleOptions = object;
type ShaderStyle = object;
type ShaderType = object;
type FileSelectorMode = object;
type WebResourceError = object;
type WebResourceRequest = object;
type WebResourceResponse = object;
type JsResult = object;
type SslErrorHandler = object;
type SslError = object;
type X509Cert = object;
type X500DistinguishedName = object;
type ClientAuthenticationHandler = object;
type ProxyConfig = object;
type WebMediaOptions = object;
type FullScreenExitHandler = object;
type PermissionRequest = object;
type ScreenCaptureHandler = object;
type ScreenCaptureResponse = object;
type ContextMenuParam = object;
type ContextMenuResult = object;
type ImageFrameInfo = object;
type TextOverflowOptions = object;
type SideBarPosition = 'start' | 'end';
type ButtonStyle = object;
type DividerStyle = object;
type BadgePosition = object;
type BadgeStyle = object;
type UIPickerComponentAttribute = object;
type IndicatorComponentAttribute = object;
type MediaCachedImageAttribute = object;
type UnionEffectContainerAttribute = object;
type WebDarkMode = 'off' | 'on' | 'auto';
type MixedMode = object;
type CacheMode = object;
type RenderExitReason = object;
type JavaScriptProxy = object;
type WebController = object;
type JsGeolocation = object;
type FileSelectorResult = object;
type FileSelectorParam = object;
type Header = object;
type IndexerAlign = object;
type MenuOffset = object;
type SymbolEffect = object;
type TextClockConfiguration = object;
type TextClockController = object;
type TextTimerController = object;
type UIExtensionProxy = object;
type SliderStyle = 'inSet' | 'outSet' | 'capsule';

type Offset = { dx: number; dy: number } | { x: number; y: number };
type CheckBoxShape = 'circle' | 'square';
type SliderBlockType = 'default' | 'image' | 'shape';
type AnimationStatus = 'initial' | 'running' | 'paused' | 'stopped';
type FillMode = 'forwards' | 'backwards' | 'both' | 'none';

type RatingConfiguration = object;
type RichEditorRange = object;
type PasteEventCallback = object;
type RichEditorSelection = object;
type SubmitCallback = object;
type RichEditorChangeValue = object;
type OnDidChangeCallback = object;
type RichEditorSpanType = object;
type TextDecorationOptions = object;
type SliderConfiguration = object;
type DateTimeOptions = object;
type NestedScrollOptions = object;

declare class ArkLogConsole {
    public static log(...args: unknown[]): void;
    public static debug(...args: unknown[]): void;
    public static info(...args: unknown[]): void;
    public static warn(...args: unknown[]): void;
    public static error(...args: unknown[]): void;
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

declare interface AttributeModifier<T> {
    applyNormalAttribute?(instance: T): void;
    applyPressedAttribute?(instance: T): void;
    applyFocusedAttribute?(instance: T): void;
    applyDisabledAttribute?(instance: T): void;
    applySelectedAttribute?(instance: T): void;
}

declare interface CommonMethod<T> {}

type Optional<T> = T | undefined;

declare class ArkSpanComponent implements CommonMethod<SpanAttribute> {
    _changed: boolean;
    _modifiersWithKeys: Map<Symbol, AttributeModifierWithKey>;
    nativePtr: KNode;
    _weakPtr: JsPointerClass;
    _classType: ModifierType | undefined;
    _nativePtrChanged: boolean;
    constructor(nativePtr: KNode, classType?: ModifierType);
    initialize(...args: unknown[]): void;
    applyModifierPatch(): void;
}
