/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
import curves from '@ohos.curves';
import { KeyCode } from '@ohos.multimodalInput.keyCode';
import util from '@ohos.util';
import { LengthMetrics } from '@ohos.arkui.node';
import I18n from '@ohos.i18n';

const MIN_ITEM_COUNT = 2
const MAX_ITEM_COUNT = 5
const DEFAULT_MAX_FONT_SCALE: number = 1
const MAX_MAX_FONT_SCALE: number = 2
const MIN_MAX_FONT_SCALE: number = 1
const RESOURCE_TYPE_FLOAT = 10002;
const RESOURCE_TYPE_INTEGER = 10007;

interface SegmentButtonThemeInterface {
  SEGMENT_TEXT_VERTICAL_PADDING: Resource;
  SEGMENT_TEXT_HORIZONTAL_PADDING: Resource;
  SEGMENT_TEXT_CAPSULE_VERTICAL_PADDING: Resource;
  SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR: ResourceColor;
  FONT_COLOR: ResourceColor,
  TAB_SELECTED_FONT_COLOR: ResourceColor,
  CAPSULE_SELECTED_FONT_COLOR: ResourceColor,
  FONT_SIZE: DimensionNoPercentage,
  SELECTED_FONT_SIZE: DimensionNoPercentage,
  BACKGROUND_COLOR: ResourceColor,
  TAB_SELECTED_BACKGROUND_COLOR: ResourceColor,
  CAPSULE_SELECTED_BACKGROUND_COLOR: ResourceColor,
  FOCUS_BORDER_COLOR: ResourceColor,
  HOVER_COLOR: ResourceColor,
  PRESS_COLOR: ResourceColor,
  BACKGROUND_BLUR_STYLE: Resource,
  CONSTRAINT_SIZE_MIN_HEIGHT: DimensionNoPercentage,
  SEGMENT_BUTTON_MIN_FONT_SIZE: DimensionNoPercentage,
  SEGMENT_BUTTON_NORMAL_BORDER_RADIUS: Length | BorderRadiuses | LocalizedBorderRadiuses,
  SEGMENT_ITEM_TEXT_OVERFLOW: Resource,
  SEGMENT_BUTTON_FOCUS_TEXT_COLOR: ResourceColor,
  SEGMENT_BUTTON_SHADOW: Resource,
  SEGMENT_FOCUS_STYLE_CUSTOMIZED: Resource
}

const segmentButtonTheme: SegmentButtonThemeInterface = {
  FONT_COLOR: $r('sys.color.segment_button_unselected_text_color'),
  TAB_SELECTED_FONT_COLOR: $r('sys.color.segment_button_checked_text_color'),
  CAPSULE_SELECTED_FONT_COLOR: $r('sys.color.ohos_id_color_foreground_contrary'),
  FONT_SIZE: $r('sys.float.segment_button_unselected_text_size'),
  SELECTED_FONT_SIZE: $r('sys.float.segment_button_checked_text_size'),
  BACKGROUND_COLOR: $r('sys.color.segment_button_backboard_color'),
  TAB_SELECTED_BACKGROUND_COLOR: $r('sys.color.segment_button_checked_foreground_color'),
  CAPSULE_SELECTED_BACKGROUND_COLOR: $r('sys.color.ohos_id_color_emphasize'),
  FOCUS_BORDER_COLOR: $r('sys.color.ohos_id_color_focused_outline'),
  HOVER_COLOR: $r('sys.color.segment_button_hover_color'),
  PRESS_COLOR: $r('sys.color.segment_button_press_color'),
  BACKGROUND_BLUR_STYLE: $r('sys.float.segment_button_background_blur_style'),
  CONSTRAINT_SIZE_MIN_HEIGHT: $r('sys.float.segment_button_height'),
  SEGMENT_BUTTON_MIN_FONT_SIZE: $r('sys.float.segment_button_min_font_size'),
  SEGMENT_BUTTON_NORMAL_BORDER_RADIUS: $r('sys.float.segment_button_normal_border_radius'),
  SEGMENT_ITEM_TEXT_OVERFLOW: $r('sys.float.segment_marquee'),
  SEGMENT_BUTTON_FOCUS_TEXT_COLOR: $r('sys.color.segment_button_focus_text_primary'),
  SEGMENT_BUTTON_SHADOW: $r('sys.float.segment_button_shadow'),
  SEGMENT_TEXT_HORIZONTAL_PADDING: $r('sys.float.segment_button_text_l_r_padding'),
  SEGMENT_TEXT_VERTICAL_PADDING: $r('sys.float.segment_button_text_u_d_padding'),
  SEGMENT_TEXT_CAPSULE_VERTICAL_PADDING: $r('sys.float.segment_button_text_capsule_u_d_padding'),
  SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR: $r('sys.color.segment_button_focus_backboard_primary'),
  SEGMENT_FOCUS_STYLE_CUSTOMIZED: $r('sys.float.segment_focus_control')
}

interface Point {
  x: number
  y: number
}

function nearEqual(first: number, second: number): boolean {
  return Math.abs(first - second) < 0.001
}

interface SegmentButtonTextItem {
  text: ResourceStr
  accessibilityLevel?: string
  accessibilityDescription?: ResourceStr
}

interface SegmentButtonIconItem {
  icon: ResourceStr,
  iconAccessibilityText?: ResourceStr
  selectedIcon: ResourceStr
  selectedIconAccessibilityText?: ResourceStr
  accessibilityLevel?: string
  accessibilityDescription?: ResourceStr
}

interface SegmentButtonIconTextItem {
  icon: ResourceStr,
  iconAccessibilityText?: ResourceStr
  selectedIcon: ResourceStr,
  selectedIconAccessibilityText?: ResourceStr
  text: ResourceStr
  accessibilityLevel?: string
  accessibilityDescription?: ResourceStr
}

type DimensionNoPercentage = PX | VP | FP | LPX | Resource

interface CommonSegmentButtonOptions {
  fontColor?: ResourceColor
  selectedFontColor?: ResourceColor
  fontSize?: DimensionNoPercentage
  selectedFontSize?: DimensionNoPercentage
  fontWeight?: FontWeight
  selectedFontWeight?: FontWeight
  backgroundColor?: ResourceColor
  selectedBackgroundColor?: ResourceColor
  imageSize?: SizeOptions
  buttonPadding?: Padding | Dimension
  textPadding?: Padding | Dimension
  localizedTextPadding?: LocalizedPadding
  localizedButtonPadding?: LocalizedPadding
  backgroundBlurStyle?: BlurStyle
  direction?: Direction
}

type ItemRestriction<T> = [T, T, T?, T?, T?]
type SegmentButtonItemTuple = ItemRestriction<SegmentButtonTextItem> |
ItemRestriction<SegmentButtonIconItem> | ItemRestriction<SegmentButtonIconTextItem>
type SegmentButtonItemArray = Array<SegmentButtonTextItem> |
Array<SegmentButtonIconItem> | Array<SegmentButtonIconTextItem>

export interface TabSegmentButtonConstructionOptions extends CommonSegmentButtonOptions {
  buttons: ItemRestriction<SegmentButtonTextItem>
}

export interface CapsuleSegmentButtonConstructionOptions extends CommonSegmentButtonOptions {
  buttons: SegmentButtonItemTuple
  multiply?: boolean
}

export interface TabSegmentButtonOptions extends TabSegmentButtonConstructionOptions {
  type: 'tab',
}

export interface CapsuleSegmentButtonOptions extends CapsuleSegmentButtonConstructionOptions {
  type: 'capsule'
}

interface SegmentButtonItemOptionsConstructorOptions {
  icon?: ResourceStr
  iconAccessibilityText?: ResourceStr
  selectedIcon?: ResourceStr
  selectedIconAccessibilityText?: ResourceStr
  text?: ResourceStr
  accessibilityLevel?: string
  accessibilityDescription?: ResourceStr
}

@Observed
class SegmentButtonItemOptions {
  public icon?: ResourceStr
  public iconAccessibilityText?: ResourceStr
  public selectedIcon?: ResourceStr
  public selectedIconAccessibilityText?: ResourceStr
  public text?: ResourceStr
  public accessibilityLevel?: string
  public accessibilityDescription?: ResourceStr

  constructor(options: SegmentButtonItemOptionsConstructorOptions) {
    this.icon = options.icon
    this.selectedIcon = options.selectedIcon
    this.text = options.text
    this.iconAccessibilityText = options.iconAccessibilityText
    this.selectedIconAccessibilityText = options.selectedIconAccessibilityText
    this.accessibilityLevel = options.accessibilityLevel
    this.accessibilityDescription = options.accessibilityDescription
  }
}

@Observed
export class SegmentButtonItemOptionsArray extends Array<SegmentButtonItemOptions> {
  public changeStartIndex: number | undefined = void 0
  public deleteCount: number | undefined = void 0
  public addLength: number | undefined = void 0

  constructor(length: number)

  constructor(elements: SegmentButtonItemTuple)

  constructor(elementsOrLength: SegmentButtonItemTuple | number) {

    super(typeof elementsOrLength === 'number' ? elementsOrLength : 0);

    if (typeof elementsOrLength !== 'number' && elementsOrLength !== void 0) {
      super.push(...elementsOrLength.map((element?: SegmentButtonTextItem | SegmentButtonIconItem |
      SegmentButtonIconTextItem) => new SegmentButtonItemOptions(element as
      SegmentButtonItemOptionsConstructorOptions)))
    }
  }

  push(...items: SegmentButtonItemArray): number {
    if (this.length + items.length > MAX_ITEM_COUNT) {
      console.warn('Exceeded the maximum number of elements (5).')
      return this.length
    }
    this.changeStartIndex = this.length
    this.deleteCount = 0
    this.addLength = items.length
    return super.push(...items.map((element: SegmentButtonItemOptionsConstructorOptions) =>
    new SegmentButtonItemOptions(element)))
  }

  pop() {
    if (this.length <= MIN_ITEM_COUNT) {
      console.warn('Below the minimum number of elements (2).')
      return void 0
    }
    this.changeStartIndex = this.length - 1
    this.deleteCount = 1
    this.addLength = 0
    return super.pop()
  }

  shift() {
    if (this.length <= MIN_ITEM_COUNT) {
      console.warn('Below the minimum number of elements (2).')
      return void 0
    }
    this.changeStartIndex = 0
    this.deleteCount = 1
    this.addLength = 0
    return super.shift()
  }

  unshift(...items: SegmentButtonItemArray): number {
    if (this.length + items.length > MAX_ITEM_COUNT) {
      console.warn('Exceeded the maximum number of elements (5).')
      return this.length
    }
    if (items.length > 0) {
      this.changeStartIndex = 0
      this.deleteCount = 0
      this.addLength = items.length
    }
    return super.unshift(...items.map((element: SegmentButtonItemOptionsConstructorOptions) =>
    new SegmentButtonItemOptions(element)))
  }

  splice(start: number, deleteCount: number, ...items: SegmentButtonItemOptions[]): SegmentButtonItemOptions[] {
    let length = (this.length - deleteCount) < 0 ? 0 : (this.length - deleteCount)
    length += items.length
    if (length < MIN_ITEM_COUNT) {
      console.warn('Below the minimum number of elements (2).')
      return []
    }
    if (length > MAX_ITEM_COUNT) {
      console.warn('Exceeded the maximum number of elements (5).')
      return []
    }
    this.changeStartIndex = start
    this.deleteCount = deleteCount
    this.addLength = items.length
    return super.splice(start, deleteCount, ...items)
  }

  static create(elements: SegmentButtonItemTuple): SegmentButtonItemOptionsArray {
    return new SegmentButtonItemOptionsArray(elements)
  }
}

@Observed
export class SegmentButtonOptions {
  public type: 'tab' | 'capsule'
  public multiply: boolean = false
  public fontColor: ResourceColor
  public selectedFontColor: ResourceColor
  public fontSize: DimensionNoPercentage
  public selectedFontSize: DimensionNoPercentage
  public fontWeight: FontWeight
  public selectedFontWeight: FontWeight
  public backgroundColor: ResourceColor
  public selectedBackgroundColor: ResourceColor
  public imageSize: SizeOptions
  public buttonPadding: Padding | Dimension | undefined
  public textPadding: Padding | Dimension | undefined
  public componentPadding: Padding | Dimension
  public localizedTextPadding?: LocalizedPadding
  public localizedButtonPadding?: LocalizedPadding
  public showText: boolean = false
  public showIcon: boolean = false
  public iconTextRadius?: number
  public iconTextBackgroundRadius?: number
  public backgroundBlurStyle: BlurStyle
  public direction?: Direction
  private _buttons: SegmentButtonItemOptionsArray | undefined = void 0

  get buttons() {
    return this._buttons
  }

  set buttons(val) {
    if (this._buttons !== void 0 && this._buttons !== val) {
      this.onButtonsChange?.()
    }
    this._buttons = val
  }

  public onButtonsChange?: () => void

  constructor(options: TabSegmentButtonOptions | CapsuleSegmentButtonOptions) {
    this.fontColor = options.fontColor ?? segmentButtonTheme.FONT_COLOR
    this.selectedFontColor = options.selectedFontColor ?? segmentButtonTheme.TAB_SELECTED_FONT_COLOR
    this.fontSize = options.fontSize ?? segmentButtonTheme.FONT_SIZE
    this.selectedFontSize = options.selectedFontSize ?? segmentButtonTheme.SELECTED_FONT_SIZE
    this.fontWeight = options.fontWeight ?? FontWeight.Regular
    this.selectedFontWeight = options.selectedFontWeight ?? FontWeight.Medium
    this.backgroundColor = options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR
    this.selectedBackgroundColor = options.selectedBackgroundColor ?? segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR
    this.imageSize = options.imageSize ?? { width: 24, height: 24 }
    this.buttonPadding = options.buttonPadding
    this.textPadding = options.textPadding
    this.type = options.type
    this.backgroundBlurStyle =
      options.backgroundBlurStyle ??
        LengthMetrics.resource(segmentButtonTheme.BACKGROUND_BLUR_STYLE).value as BlurStyle;
    this.localizedTextPadding = options.localizedTextPadding
    this.localizedButtonPadding = options.localizedButtonPadding
    this.direction = options.direction ?? Direction.Auto
    this.buttons = new SegmentButtonItemOptionsArray(options.buttons)
    if (this.type === 'capsule') {
      this.multiply = (options as CapsuleSegmentButtonOptions).multiply ?? false
      this.onButtonsUpdated();
      this.selectedFontColor = options.selectedFontColor ?? segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR
      this.selectedBackgroundColor = options.selectedBackgroundColor ??
      segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR
    } else {
      this.showText = true
    }
    let themePadding = LengthMetrics.resource($r('sys.float.segment_button_baseplate_padding')).value;
    this.componentPadding = this.multiply ? 0 : themePadding;
  }

  public onButtonsUpdated() {
    this.buttons?.forEach(button => {
      this.showText ||= button.text !== void 0;
      this.showIcon ||= button.icon !== void 0 || button.selectedIcon !== void 0;
    })
    if (this.showText && this.showIcon) {
      this.iconTextRadius = 12;
      this.iconTextBackgroundRadius = 14;
    }
  }

  static tab(options: TabSegmentButtonConstructionOptions): SegmentButtonOptions {
    return new SegmentButtonOptions({
      type: 'tab',
      buttons: options.buttons,
      fontColor: options.fontColor,
      selectedFontColor: options.selectedFontColor,
      fontSize: options.fontSize,
      selectedFontSize: options.selectedFontSize,
      fontWeight: options.fontWeight,
      selectedFontWeight: options.selectedFontWeight,
      backgroundColor: options.backgroundColor,
      selectedBackgroundColor: options.selectedBackgroundColor,
      imageSize: options.imageSize,
      buttonPadding: options.buttonPadding,
      textPadding: options.textPadding,
      localizedTextPadding: options.localizedTextPadding,
      localizedButtonPadding: options.localizedButtonPadding,
      backgroundBlurStyle: options.backgroundBlurStyle,
      direction: options.direction
    })
  }

  static capsule(options: CapsuleSegmentButtonConstructionOptions): SegmentButtonOptions {
    return new SegmentButtonOptions({
      type: 'capsule',
      buttons: options.buttons,
      multiply: options.multiply,
      fontColor: options.fontColor,
      selectedFontColor: options.selectedFontColor,
      fontSize: options.fontSize,
      selectedFontSize: options.selectedFontSize,
      fontWeight: options.fontWeight,
      selectedFontWeight: options.selectedFontWeight,
      backgroundColor: options.backgroundColor,
      selectedBackgroundColor: options.selectedBackgroundColor,
      imageSize: options.imageSize,
      buttonPadding: options.buttonPadding,
      textPadding: options.textPadding,
      localizedTextPadding: options.localizedTextPadding,
      localizedButtonPadding: options.localizedButtonPadding,
      backgroundBlurStyle: options.backgroundBlurStyle,
      direction: options.direction
    })
  }
}

@Component
struct MultiSelectBackground {
  @ObjectLink optionsArray: SegmentButtonItemOptionsArray
  @ObjectLink options: SegmentButtonOptions
  @Consume buttonBorderRadius: LocalizedBorderRadiuses[]
  @Consume buttonItemsSize: SizeOptions[]

  build() {
    Row({ space: 1 }) {
      ForEach(this.optionsArray, (_: SegmentButtonItemOptions, index) => {
        if (index < MAX_ITEM_COUNT) {
          Stack()
            .direction(this.options.direction)
            .layoutWeight(1)
            .height(this.buttonItemsSize[index].height)
            .backgroundColor(this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR)
            .borderRadius(this.buttonBorderRadius[index])
            .backgroundBlurStyle(this.options.backgroundBlurStyle, undefined, { disableSystemAdaptation: true })
        }
      })
    }
    .direction(this.options.direction)
    .padding(this.options.componentPadding)
  }
}

@Component
struct SelectItem {
  @ObjectLink optionsArray: SegmentButtonItemOptionsArray
  @ObjectLink options: SegmentButtonOptions
  @Link selectedIndexes: number[]
  @Consume buttonItemsSize: SizeOptions[]
  @Consume selectedItemPosition: LocalizedEdges
  @Consume zoomScaleArray: number[]
  @Consume buttonBorderRadius: LocalizedBorderRadiuses[]

  build() {
    if (this.selectedIndexes !== void 0 && this.selectedIndexes.length !== 0) {
      Stack()
        .direction(this.options.direction)
        .borderRadius(this.buttonBorderRadius[this.selectedIndexes[0]])
        .size(this.buttonItemsSize[this.selectedIndexes[0]])
        .backgroundColor(this.options.selectedBackgroundColor ??
          (this.options.type === 'tab' ? segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR :
          segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR))
        .position(this.selectedItemPosition)
        .scale({ x: this.zoomScaleArray[this.selectedIndexes[0]], y: this.zoomScaleArray[this.selectedIndexes[0]] })
        .shadow(resourceToNumber(this.getUIContext()?.getHostContext(), segmentButtonTheme.SEGMENT_BUTTON_SHADOW,
          0) as ShadowStyle)
    }
  }
}

@Component
struct MultiSelectItemArray {
  @ObjectLink optionsArray: SegmentButtonItemOptionsArray
  @ObjectLink @Watch('onOptionsChange') options: SegmentButtonOptions
  @Link @Watch('onSelectedChange') selectedIndexes: number[]
  @Consume buttonItemsSize: SizeOptions[]
  @Consume zoomScaleArray: number[]
  @Consume buttonBorderRadius: LocalizedBorderRadiuses[]
  @State multiColor: ResourceColor[] = Array.from({ length: MAX_ITEM_COUNT }, (_: Object, index) => Color.Transparent)

  onOptionsChange() {
    for (let i = 0; i < this.selectedIndexes.length; i++) {
      this.multiColor[this.selectedIndexes[i]] = this.options.selectedBackgroundColor ??
      segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR
    }
  }

  onSelectedChange() {
    for (let i = 0; i < MAX_ITEM_COUNT; i++) {
      this.multiColor[i] = Color.Transparent
    }
    for (let i = 0; i < this.selectedIndexes.length; i++) {
      this.multiColor[this.selectedIndexes[i]] = this.options.selectedBackgroundColor ??
      segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR
    }
  }

  aboutToAppear() {
    for (let i = 0; i < this.selectedIndexes.length; i++) {
      this.multiColor[this.selectedIndexes[i]] = this.options.selectedBackgroundColor ??
      segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR
    }
  }

  build() {
    Row({ space: 1 }) {
      ForEach(this.optionsArray, (_: SegmentButtonItemOptions, index) => {
        if (index < MAX_ITEM_COUNT) {
          Stack()
            .direction(this.options.direction)
            .width(this.buttonItemsSize[index].width)
            .height(this.buttonItemsSize[index].height)
            .backgroundColor(this.multiColor[index])
            .borderRadius(this.buttonBorderRadius[index])
        }
      })
    }
    .direction(this.options.direction)
    .padding(this.options.componentPadding)
  }
}

@Component
struct SegmentButtonItem {
  @Link selectedIndexes: number[]
  @Link @Watch('onFocusIndex') focusIndex: number;
  @Prop @Require maxFontScale: number | Resource
  @ObjectLink itemOptions: SegmentButtonItemOptions
  @ObjectLink options: SegmentButtonOptions;
  @ObjectLink property: ItemProperty
  @Prop index: number
  @State isTextSupportMarquee: boolean =
    resourceToNumber(this.getUIContext()?.getHostContext(), segmentButtonTheme.SEGMENT_ITEM_TEXT_OVERFLOW, 1.0) === 0.0;
  @Prop isMarqueeAndFadeout: boolean;
  @Prop isSegmentFocusStyleCustomized: boolean;
  @State isTextInMarqueeCondition: boolean = false;
  @State isButtonTextFadeout?: boolean = false;
  private groupId: string = ''
  @Prop @Watch('onFocusIndex') hover: boolean;

  private getTextPadding(): Padding | Dimension | LocalizedPadding {
    if (this.options.localizedTextPadding) {
      return this.options.localizedTextPadding
    }
    if (this.options.textPadding !== void (0)) {
      return this.options.textPadding
    }
    return 0
  }

  private getButtonPadding(): Padding | Dimension | LocalizedPadding {
    if (this.options.localizedButtonPadding) {
      return this.options.localizedButtonPadding
    }
    if (this.options.buttonPadding !== void (0)) {
      return this.options.buttonPadding
    }
    if (this.options.type === 'capsule' && this.options.showText && this.options.showIcon) {
      return {
        top: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_CAPSULE_VERTICAL_PADDING),
        bottom: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_CAPSULE_VERTICAL_PADDING),
        start: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_HORIZONTAL_PADDING),
        end: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_HORIZONTAL_PADDING)
      }
    }
    return {
      top: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_VERTICAL_PADDING),
      bottom: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_VERTICAL_PADDING),
      start: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_HORIZONTAL_PADDING),
      end: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_HORIZONTAL_PADDING)
    }
  }

  onFocusIndex(): void {
    this.isTextInMarqueeCondition =
      this.isSegmentFocusStyleCustomized && (this.focusIndex === this.index || this.hover);
  }

  aboutToAppear(): void {
    this.isButtonTextFadeout = this.isSegmentFocusStyleCustomized;
  }

  isDefaultSelectedFontColor(): boolean {
    if (this.options.type === 'tab') {
      return this.options.selectedFontColor === segmentButtonTheme.TAB_SELECTED_FONT_COLOR;
    } else if (this.options.type === 'capsule') {
      return this.options.selectedFontColor === segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
    }
    return false;
  }

  private getFontColor(): ResourceColor {
    if (this.property.isSelected) {
      if (this.isDefaultSelectedFontColor() && this.isSegmentFocusStyleCustomized && this.focusIndex === this.index) {
        return segmentButtonTheme.SEGMENT_BUTTON_FOCUS_TEXT_COLOR;
      }
      return this.options.selectedFontColor ?? segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
    } else {
      if (this.options.fontColor === segmentButtonTheme.FONT_COLOR && this.isSegmentFocusStyleCustomized &&
        this.focusIndex === this.index) {
        return segmentButtonTheme.SEGMENT_BUTTON_FOCUS_TEXT_COLOR;
      }
      return this.options.fontColor ?? segmentButtonTheme.FONT_COLOR;
    }
  }

  private getAccessibilityText(): Resource | undefined {
    if (this.selectedIndexes.includes(this.index) &&
      typeof this.itemOptions.selectedIconAccessibilityText !== undefined) {
      return this.itemOptions.selectedIconAccessibilityText as Resource
    } else if (!this.selectedIndexes.includes(this.index) &&
      typeof this.itemOptions.iconAccessibilityText !== undefined) {
      return this.itemOptions.iconAccessibilityText as Resource
    }
    return undefined;
  }

  build() {
    Column({ space: 2 }) {
      if (this.options.showIcon) {
        Image(this.property.isSelected ? this.itemOptions.selectedIcon : this.itemOptions.icon)
          .direction(this.options.direction)
          .size(this.options.imageSize ?? { width: 24, height: 24 })
          .draggable(false)
          .fillColor(this.getFontColor())
          .accessibilityText(this.getAccessibilityText())
      }
      if (this.options.showText) {
        Text(this.itemOptions.text)
          .direction(this.options.direction)
          .fontColor(this.getFontColor())
          .fontWeight(this.property.fontWeight)
          .fontSize(this.property.fontSize)
          .minFontSize(this.isSegmentFocusStyleCustomized ? this.property.fontSize : 9)
          .maxFontSize(this.property.fontSize)
          .maxFontScale(this.maxFontScale)
          .textOverflow({
            overflow: this.isTextSupportMarquee ? TextOverflow.MARQUEE : TextOverflow.Ellipsis
          })
          .marqueeOptions({
            start: this.isTextInMarqueeCondition,
            fadeout: this.isButtonTextFadeout,
            marqueeStartPolicy: MarqueeStartPolicy.DEFAULT
          })
          .maxLines(1)
          .textAlign(TextAlign.Center)
          .padding(this.getTextPadding())
      }
    }
    .direction(this.options.direction)
    .focusScopePriority(this.groupId, Math.min(...this.selectedIndexes) === this.index ? FocusPriority.PREVIOUS : FocusPriority.AUTO)
    .justifyContent(FlexAlign.Center)
    .padding(this.getButtonPadding())
    .constraintSize({ minHeight: segmentButtonTheme.CONSTRAINT_SIZE_MIN_HEIGHT })
  }
}

@Observed
class HoverColorProperty {
  public hoverColor: ResourceColor = Color.Transparent
}

@Component
struct PressAndHoverEffect {
  @Consume buttonItemsSize: SizeOptions[]
  @Prop press: boolean
  @Prop hover: boolean
  @ObjectLink colorProperty: HoverColorProperty
  @Consume buttonBorderRadius: LocalizedBorderRadiuses[]
  @ObjectLink options: SegmentButtonOptions;
  pressIndex: number = 0
  pressColor: ResourceColor = segmentButtonTheme.PRESS_COLOR

  build() {
    Stack()
      .direction(this.options.direction)
      .size(this.buttonItemsSize[this.pressIndex])
      .backgroundColor(this.press && this.hover ? this.pressColor : this.colorProperty.hoverColor)
      .borderRadius(this.buttonBorderRadius[this.pressIndex])
  }
}

@Component
struct PressAndHoverEffectArray {
  @ObjectLink buttons: SegmentButtonItemOptionsArray
  @ObjectLink options: SegmentButtonOptions
  @Link pressArray: boolean[]
  @Link hoverArray: boolean[]
  @Link hoverColorArray: HoverColorProperty[]
  @Consume zoomScaleArray:number[]

  build() {
    Row({ space: 1 }) {
      ForEach(this.buttons, (item: SegmentButtonItemOptions, index) => {
        if (index < MAX_ITEM_COUNT) {
          Stack() {
            PressAndHoverEffect({
              pressIndex: index,
              colorProperty: this.hoverColorArray[index],
              press: this.pressArray[index],
              hover: this.hoverArray[index],
              options: this.options,
            })
          }
          .direction(this.options.direction)
          .scale({
            x: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[index],
            y: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[index]
          })
        }
      })
    }.direction(this.options.direction)
  }
}

@Component
struct SegmentButtonItemArrayComponent {
  @ObjectLink @Watch('onOptionsArrayChange') optionsArray: SegmentButtonItemOptionsArray
  @ObjectLink @Watch('onOptionsChange') options: SegmentButtonOptions
  @Link selectedIndexes: number[]
  @Consume componentSize: SizeOptions
  @Consume buttonBorderRadius: LocalizedBorderRadiuses[]
  @Consume @Watch('onButtonItemsSizeChange') buttonItemsSize: SizeOptions[]
  @Consume buttonItemsPosition: LocalizedEdges[]
  @Consume @Watch('onFocusIndex') focusIndex: number;
  @Consume zoomScaleArray: number[]
  @Consume buttonItemProperty: ItemProperty[]
  @Consume buttonItemsSelected: boolean[]
  @Link pressArray: boolean[]
  @Link hoverArray: boolean[]
  @Link hoverColorArray: HoverColorProperty[]
  @Prop @Require maxFontScale: number | Resource
  @State buttonWidth: number[] = Array.from({ length: MAX_ITEM_COUNT }, (_: Object, index) => 0)
  @State buttonHeight: number[] = Array.from({ length: MAX_ITEM_COUNT }, (_: Object, index) => 0)
  @State isMarqueeAndFadeout: boolean = false;
  private buttonItemsRealHeight: number[] = Array.from({ length: MAX_ITEM_COUNT }, (_: Object, index) => 0)
  private groupId: string = util.generateRandomUUID(true)
  public onItemClicked?: Callback<number>
  @Prop isSegmentFocusStyleCustomized: boolean;

  onButtonItemsSizeChange() {
    this.buttonItemsSize.forEach((value, index) => {
      this.buttonWidth[index] = value.width as number
      this.buttonHeight[index] = value.height as number
    })
  }

  changeSelectedIndexes(buttonsLength: number) {
    if (this.optionsArray.changeStartIndex === void 0 || this.optionsArray.deleteCount === void 0 ||
      this.optionsArray.addLength === void 0) {
      return
    }
    if (!(this.options.multiply ?? false)) {
      // Single-select
      if (this.selectedIndexes[0] === void 0) {
        return
      }
      if (this.selectedIndexes[0] < this.optionsArray.changeStartIndex) {
        return
      }
      if (this.optionsArray.changeStartIndex + this.optionsArray.deleteCount > this.selectedIndexes[0]) {
        if (this.options.type === 'tab') {
          this.selectedIndexes[0] = 0
        } else if (this.options.type === 'capsule') {
          this.selectedIndexes = []
        }
      } else {
        this.selectedIndexes[0] = this.selectedIndexes[0] - this.optionsArray.deleteCount + this.optionsArray.addLength
      }
    } else {
      // Multi-select
      let saveIndexes = this.selectedIndexes
      for (let i = 0; i < this.optionsArray.deleteCount; i++) {
        let deleteIndex = saveIndexes.indexOf(this.optionsArray.changeStartIndex)
        let indexes = saveIndexes.map(value => this.optionsArray.changeStartIndex &&
          (value > this.optionsArray.changeStartIndex) ? value - 1 : value)
        if (deleteIndex !== -1) {
          indexes.splice(deleteIndex, 1)
        }
        saveIndexes = indexes
      }
      for (let i = 0; i < this.optionsArray.addLength; i++) {
        let indexes = saveIndexes.map(value => this.optionsArray.changeStartIndex &&
          (value >= this.optionsArray.changeStartIndex) ? value + 1 : value)
        saveIndexes = indexes
      }
      this.selectedIndexes = saveIndexes
    }

  }

  changeFocusIndex(buttonsLength: number) {
    if (this.optionsArray.changeStartIndex === void 0 || this.optionsArray.deleteCount === void 0 ||
      this.optionsArray.addLength === void 0) {
      return
    }
    if (this.focusIndex === -1) {
      return
    }
    if (this.focusIndex < this.optionsArray.changeStartIndex) {
      return
    }
    if (this.optionsArray.changeStartIndex + this.optionsArray.deleteCount > this.focusIndex) {
      this.focusIndex = 0
    } else {
      this.focusIndex = this.focusIndex - this.optionsArray.deleteCount + this.optionsArray.addLength
    }

  }

  onOptionsArrayChange() {
    if (this.options === void 0 || this.options.buttons === void 0) {
      return
    }
    let buttonsLength = Math.min(this.options.buttons.length, this.buttonItemsSize.length)
    if (this.optionsArray.changeStartIndex !== void 0 && this.optionsArray.deleteCount !== void 0 &&
      this.optionsArray.addLength !== void 0) {
      this.changeSelectedIndexes(buttonsLength)
      this.changeFocusIndex(buttonsLength)
      this.optionsArray.changeStartIndex = void 0
      this.optionsArray.deleteCount = void 0
      this.optionsArray.addLength = void 0
    }
  }

  onOptionsChange() {
    if (this.options === void 0 || this.options.buttons === void 0) {
      return
    }
    this.calculateBorderRadius()
  }

  onFocusIndex(): void {
    this.isMarqueeAndFadeout = this.isSegmentFocusStyleCustomized && !this.isMarqueeAndFadeout;
  }

  aboutToAppear() {
    for (let index = 0; index < this.buttonItemsRealHeight.length; index++) {
      this.buttonItemsRealHeight[index] = 0
    }
  }

  private getBorderRadius(index: number): LocalizedBorderRadiuses {
    let borderRadius: LocalizedBorderRadiuses = this.buttonBorderRadius[index]
    if (this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex]) {
      return {
        topStart: LengthMetrics.vp((borderRadius.topStart?.value ?? 0) + 4),
        topEnd: LengthMetrics.vp((borderRadius.topEnd?.value ?? 0) + 4),
        bottomStart: LengthMetrics.vp((borderRadius.bottomStart?.value ?? 0) + 4),
        bottomEnd: LengthMetrics.vp((borderRadius.bottomEnd?.value ?? 0) + 4)
      }
    }
    return borderRadius
  }

  @Builder
  focusStack(index: number) {
    Stack() {
      Stack()
        .direction(this.options.direction)
        .borderRadius(this.getBorderRadius(index))
        .size({
          width: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonWidth[index] + 8 : this.buttonWidth[index],
          height: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonHeight[index] + 8 : this.buttonHeight[index]
        })
        .borderColor(segmentButtonTheme.FOCUS_BORDER_COLOR)
        .borderWidth(2)
    }
    .direction(this.options.direction)
    .size({ width: 1, height: 1 })
    .align(Alignment.Center)
  }

  calculateBorderRadius() {
    let borderRadiusArray: LocalizedBorderRadiuses[] = Array.from({
      length: MAX_ITEM_COUNT
    }, (_: Object, index): LocalizedBorderRadiuses => {
      return {
        topStart: LengthMetrics.vp(0),
        topEnd: LengthMetrics.vp(0),
        bottomStart: LengthMetrics.vp(0),
        bottomEnd: LengthMetrics.vp(0)
      }
    })
    for (let index = 0; index < this.buttonBorderRadius.length; index++) {
      let halfButtonItemsSizeHeight = this.buttonItemsSize[index].height as number / 2
      if (this.options.type === 'tab' || !(this.options.multiply ?? false)) {
        borderRadiusArray[index].topStart = LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight)
        borderRadiusArray[index].topEnd = LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight)
        borderRadiusArray[index].bottomStart = LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight)
        borderRadiusArray[index].bottomEnd = LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight)
      } else {
        if (index === 0) {
          borderRadiusArray[index].topStart = LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight)
          borderRadiusArray[index].topEnd = LengthMetrics.vp(0)
          borderRadiusArray[index].bottomStart = LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight)
          borderRadiusArray[index].bottomEnd = LengthMetrics.vp(0)
        } else if (this.options.buttons && index === Math.min(this.options.buttons.length,
          this.buttonItemsSize.length) - 1) {
          borderRadiusArray[index].topStart = LengthMetrics.vp(0)
          borderRadiusArray[index].topEnd = LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight)
          borderRadiusArray[index].bottomStart = LengthMetrics.vp(0)
          borderRadiusArray[index].bottomEnd = LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight)
        } else {
          borderRadiusArray[index].topStart = LengthMetrics.vp(0)
          borderRadiusArray[index].topEnd = LengthMetrics.vp(0)
          borderRadiusArray[index].bottomStart = LengthMetrics.vp(0)
          borderRadiusArray[index].bottomEnd = LengthMetrics.vp(0)
        }
      }
    }
    this.buttonBorderRadius = borderRadiusArray
  }

  getAccessibilityDescription(value?: ResourceStr): Resource | undefined {
    return (typeof value !== undefined) ? value as Resource : undefined
  }

  isDefaultSelectedBgColor(): boolean {
    if (this.options.type === 'tab') {
      return this.options.selectedBackgroundColor === segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR;
    } else if (this.options.type === 'capsule') {
      return this.options.selectedBackgroundColor === segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
    }
    return true;
  }

  build() {
    if (this.optionsArray !== void 0 && this.optionsArray.length > 1) {
      Row({ space: 1 }) {
        ForEach(this.optionsArray, (item: SegmentButtonItemOptions, index) => {
          if (index < MAX_ITEM_COUNT) {
            Button() {
              SegmentButtonItem({
                isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized,
                selectedIndexes: $selectedIndexes,
                focusIndex: this.focusIndex,
                index: index,
                itemOptions: item,
                options: this.options,
                property: this.buttonItemProperty[index],
                groupId: this.groupId,
                maxFontScale: this.maxFontScale,
                hover: this.hoverArray[index],
              })
                .onSizeChange((_, newValue) => {
                  // Calculate height of items
                  this.buttonItemsRealHeight[index] = newValue.height as number
                  let maxHeight = Math.max(...this.buttonItemsRealHeight.slice(0, this.options.buttons ?
                  this.options.buttons.length : 0))
                  for (let index = 0; index < this.buttonItemsSize.length; index++) {
                    this.buttonItemsSize[index] = { width: this.buttonItemsSize[index].width, height: maxHeight }
                  }
                  this.calculateBorderRadius()
                })
            }
            .type(ButtonType.Normal)
            .stateEffect(false)
            .hoverEffect(HoverEffect.None)
            .backgroundColor(Color.Transparent)
            .accessibilityLevel(item.accessibilityLevel)
            .accessibilitySelected(this.options.multiply ? undefined : this.selectedIndexes.includes(index))
            .accessibilityChecked(this.options.multiply ? this.selectedIndexes.includes(index) : undefined)
            .accessibilityDescription(this.getAccessibilityDescription(item.accessibilityDescription))
            .direction(this.options.direction)
            .borderRadius(this.buttonBorderRadius[index])
            .scale({
              x: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[index],
              y: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[index]
            })
            .layoutWeight(1)
            .padding(0)
            .onSizeChange((_, newValue) => {
              this.buttonItemsSize[index] = { width: newValue.width, height: this.buttonItemsSize[index].height }
              //measure position
              if (newValue.width) {
                this.buttonItemsPosition[index] = {
                  start: LengthMetrics.vp(Number.parseFloat(this.options.componentPadding.toString()) +
                    (Number.parseFloat(newValue.width.toString()) + 1) * index),
                  top: LengthMetrics.px(Math.floor(this.getUIContext()
                    .vp2px(Number.parseFloat(this.options.componentPadding.toString()))))
                }
              }
            })
            .stateStyles({
              normal: {
                .overlay(undefined)
              },
              focused: {
                .overlay(this.focusStack(index), {
                  align: Alignment.Center
                })
              }
            })
            .onFocus(() => {
              this.focusIndex = index;
              if (this.isSegmentFocusStyleCustomized) {
                this.customizeSegmentFocusStyle(index);
              }
            })
            .onBlur(() => {
              this.focusIndex = -1;
              this.hoverColorArray[index].hoverColor = Color.Transparent;
            })
            .gesture(TapGesture().onAction(() => {
              if (this.onItemClicked) {
                this.onItemClicked(index)
              }
              if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                if (this.selectedIndexes.indexOf(index) === -1) {
                  this.selectedIndexes.push(index)
                } else {
                  this.selectedIndexes.splice(this.selectedIndexes.indexOf(index), 1)
                }
              } else {
                this.selectedIndexes[0] = index
              }
            }))
            .onTouch((event: TouchEvent) => {
              if (this.isSegmentFocusStyleCustomized) {
                this.getUIContext().getFocusController().clearFocus();
              }
              if (event.source !== SourceType.TouchScreen) {
                return
              }
              if (event.type === TouchType.Down) {
                animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                  this.zoomScaleArray[index] = 0.95
                })
              } else if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                  this.zoomScaleArray[index] = 1
                })
              }
            })
            .onHover((isHover: boolean) => {
              this.hoverArray[index] = isHover
              if (isHover) {
                animateTo({ duration: 250, curve: Curve.Friction }, () => {
                  this.hoverColorArray[index].hoverColor =
                    this.isSegmentFocusStyleCustomized && this.focusIndex === index ?
                    segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR : segmentButtonTheme.HOVER_COLOR;
                })
              } else {
                animateTo({ duration: 250, curve: Curve.Friction }, () => {
                  this.hoverColorArray[index].hoverColor =
                    this.isSegmentFocusStyleCustomized && this.focusIndex === index ?
                    segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR : Color.Transparent;
                })
              }
            })
            .onMouse((event: MouseEvent) => {
              switch (event.action) {
                case MouseAction.Press:
                  animateTo({ curve: curves.springMotion(0.347, 0.99) }, () => {
                    this.zoomScaleArray[index] = 0.95
                  })
                  animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                    this.pressArray[index] = true
                  })
                  break;
                case MouseAction.Release:
                  animateTo({ curve: curves.springMotion(0.347, 0.99) }, () => {
                    this.zoomScaleArray[index] = 1
                  })
                  animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                    this.pressArray[index] = false
                  })
                  break;
              }
            })
          }
        })
      }
      .direction(this.options.direction)
      .focusScopeId(this.groupId, true)
      .padding(this.options.componentPadding)
      .onSizeChange((_, newValue) => {
        this.componentSize = { width: newValue.width, height: newValue.height }
      })
    }
  }

  /**
   * 设置segmentbutton获焦时的样式
   * @param index
   */
  private customizeSegmentFocusStyle(index: number) {
    if (this.selectedIndexes !== void 0 && this.selectedIndexes.length !== 0 &&
      this.selectedIndexes[0] === index) { // 选中态
      this.hoverColorArray[index].hoverColor = this.isDefaultSelectedBgColor() ?
      segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR : this.options.selectedBackgroundColor;
    } else { // 未选中态
      this.hoverColorArray[index].hoverColor = this.options.backgroundColor === segmentButtonTheme.BACKGROUND_COLOR ?
      segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR : this.options.backgroundColor;
    }
  }
}

@Observed
class ItemProperty {
  public fontColor: ResourceColor = segmentButtonTheme.FONT_COLOR
  public fontSize: DimensionNoPercentage = segmentButtonTheme.FONT_SIZE
  public fontWeight: FontWeight = FontWeight.Regular
  public isSelected: boolean = false
}

@Component
export struct SegmentButton {
  @ObjectLink @Watch('onOptionsChange') options: SegmentButtonOptions
  @Link @Watch('onSelectedChange') selectedIndexes: number[]
  public onItemClicked?: Callback<number>
  @Prop maxFontScale: number | Resource = DEFAULT_MAX_FONT_SCALE
  @Provide componentSize: SizeOptions = { width: 0, height: 0 }
  @Provide buttonBorderRadius: LocalizedBorderRadiuses[] = Array.from({
    length: MAX_ITEM_COUNT
  }, (_: Object, index): LocalizedBorderRadiuses => {
    return {
      topStart: LengthMetrics.vp(0),
      topEnd: LengthMetrics.vp(0),
      bottomStart: LengthMetrics.vp(0),
      bottomEnd: LengthMetrics.vp(0)
    }
  })
  @Provide buttonItemsSize: SizeOptions[] = Array.from({ length: MAX_ITEM_COUNT }, (_: Object, index): SizeOptions => {
    return {}
  })
  @Provide @Watch('onItemsPositionChange') buttonItemsPosition: LocalizedEdges[] = Array.from({
    length: MAX_ITEM_COUNT
  }, (_: Object, index): LocalizedEdges => {
    return {}
  })
  @Provide buttonItemsSelected: boolean[] = Array.from({ length: MAX_ITEM_COUNT }, (_: Object, index) => false)
  @Provide buttonItemProperty: ItemProperty[] = Array.from({
    length: MAX_ITEM_COUNT
  }, (_: Object, index) => new ItemProperty())
  @Provide focusIndex: number = -1
  @Provide selectedItemPosition: LocalizedEdges = {}
  @Provide zoomScaleArray: number[] = Array.from({ length: MAX_ITEM_COUNT }, (_: Object, index) => 1.0)
  @State pressArray: boolean[] = Array.from({ length: MAX_ITEM_COUNT }, (_: Object, index) => false)
  @State hoverArray: boolean[] = Array.from({ length: MAX_ITEM_COUNT }, (_: Object, index) => false)
  @State hoverColorArray: HoverColorProperty[] = Array.from({
    length: MAX_ITEM_COUNT
  }, (_: Object, index) => new HoverColorProperty())
  private doSelectedChangeAnimate: boolean = false
  private isCurrentPositionSelected: boolean = false
  private panGestureStartPoint: Point = { x: 0, y: 0 }
  private isPanGestureMoved: boolean = false
  @State shouldMirror: boolean = false
  private isSegmentFocusStyleCustomized: boolean =
    resourceToNumber(this.getUIContext()?.getHostContext(), segmentButtonTheme.SEGMENT_FOCUS_STYLE_CUSTOMIZED, 1.0) ===
      0.0;
  private isGestureInProgress: boolean = false;

  onItemsPositionChange() {
    if (this.options === void 0 || this.options.buttons === void 0) {
      return
    }
    if (this.options.type === 'capsule') {
      this.options.onButtonsUpdated();
    }
    if (this.doSelectedChangeAnimate) {
      this.updateAnimatedProperty(this.getSelectedChangeCurve())
    } else {
      this.updateAnimatedProperty(null)
    }
  }

  setItemsSelected() {
    this.buttonItemsSelected.forEach((_, index) => {
      this.buttonItemsSelected[index] = false
    })
    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
      this.selectedIndexes.forEach(index => this.buttonItemsSelected[index] = true)
    } else {
      this.buttonItemsSelected[this.selectedIndexes[0]] = true
    }
  }

  updateSelectedIndexes() {
    if (this.selectedIndexes === void 0) {
      this.selectedIndexes = []
    }
    if (this.options.type === 'tab' && this.selectedIndexes.length === 0) {
      this.selectedIndexes[0] = 0
    }
    if (this.selectedIndexes.length > 1) {
      if (this.options.type === 'tab') {
        this.selectedIndexes = [0]
      }
      if (this.options.type === 'capsule' && !(this.options.multiply ?? false)) {
        this.selectedIndexes = []
      }
    }
    let invalid = this.selectedIndexes.some(index => {
      return (index === void 0 || index < 0 || (this.options.buttons && index >= this.options.buttons.length))
    })
    if (invalid) {
      if (this.options.type === 'tab') {
        this.selectedIndexes = [0]
      } else {
        this.selectedIndexes = []
      }
    }
  }

  onOptionsChange() {
    if (this.options === void 0 || this.options.buttons === void 0) {
      return
    }
    this.shouldMirror = this.isShouldMirror()
    this.updateSelectedIndexes()
    this.setItemsSelected()
    this.updateAnimatedProperty(null)
  }

  onSelectedChange() {
    if (this.options === void 0 || this.options.buttons === void 0) {
      return
    }
    this.updateSelectedIndexes()
    this.setItemsSelected()
    if (this.doSelectedChangeAnimate) {
      this.updateAnimatedProperty(this.getSelectedChangeCurve())
    } else {
      this.updateAnimatedProperty(null)
    }
  }

  aboutToAppear() {
    if (this.options === void 0 || this.options.buttons === void 0) {
      return
    }
    this.options.onButtonsChange = () => {
      if (this.options.type === 'tab') {
        this.selectedIndexes = [0]
      } else {
        this.selectedIndexes = []
      }
    }
    this.shouldMirror = this.isShouldMirror()
    this.updateSelectedIndexes()
    this.setItemsSelected()
    this.updateAnimatedProperty(null)
  }

  private isMouseWheelScroll(event: GestureEvent) {
    return event.source === SourceType.Mouse && !this.isPanGestureMoved
  }

  private isMovedFromPanGestureStartPoint(x: number, y: number) {
    return !nearEqual(x, this.panGestureStartPoint.x) || !nearEqual(y, this.panGestureStartPoint.y)
  }

  private isShouldMirror(): boolean {
    if (this.options.direction == Direction.Rtl) {
      return true
    }
    // 获取系统语言
    try {
      let systemLanguage: string = I18n.System.getSystemLanguage();
      if (I18n.isRTL(systemLanguage) && this.options.direction != Direction.Ltr) {
        return true
      }
    } catch (error) {
      console.error(`Ace SegmentButton getSystemLanguage, error: ${error.toString()}`);
    }
    return false
  }

  build() {
    Stack() {
      if (this.options !== void 0 && this.options.buttons != void 0) {
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
          MultiSelectBackground({
            optionsArray: this.options.buttons,
            options: this.options,
          })
        } else {
          Stack() {
            if (this.options.buttons !== void 0 && this.options.buttons.length > 1) {
              PressAndHoverEffectArray({
                options:this.options,
                buttons:this.options.buttons,
                pressArray:this.pressArray,
                hoverArray:this.hoverArray,
                hoverColorArray:this.hoverColorArray
              })
            }
          }
          .direction(this.options.direction)
          .size(this.componentSize)
          .backgroundColor(this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR)
          .borderRadius(this.options.iconTextBackgroundRadius ?? this.componentSize.height as number / 2)
          .backgroundBlurStyle(this.options.backgroundBlurStyle, undefined, { disableSystemAdaptation: true })
        }
        Stack() {
          if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            MultiSelectItemArray({
              optionsArray: this.options.buttons,
              options: this.options,
              selectedIndexes: $selectedIndexes
            })
          } else {
            SelectItem({
              optionsArray: this.options.buttons,
              options: this.options,
              selectedIndexes: $selectedIndexes
            })
          }
        }
        .direction(this.options.direction)
        .size(this.componentSize)
        .animation({ duration: 0 })
        .borderRadius((this.options.type === 'capsule' && (this.options.multiply ?? false) ?
        this.options.iconTextRadius : this.options.iconTextBackgroundRadius) ??
          this.componentSize.height as number / 2)
        .clip(true)

        SegmentButtonItemArrayComponent({
          pressArray: this.pressArray,
          hoverArray: this.hoverArray,
          hoverColorArray: this.hoverColorArray,
          optionsArray: this.options.buttons,
          options: this.options,
          selectedIndexes: $selectedIndexes,
          maxFontScale: this.getMaxFontSize(),
          onItemClicked: this.onItemClicked,
          isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized
        })
      }
    }
    .direction(this.options ? this.options.direction : undefined)
    .onBlur(() => {
      this.focusIndex = -1
    })
    .onKeyEvent((event: KeyEvent) => {
      if (this.options === void 0 || this.options.buttons === void 0) {
        return
      }
      if (event.type === KeyType.Down) {
        if (event.keyCode === KeyCode.KEYCODE_SPACE || event.keyCode === KeyCode.KEYCODE_ENTER ||
          event.keyCode === KeyCode.KEYCODE_NUMPAD_ENTER) {
          if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            if (this.selectedIndexes.indexOf(this.focusIndex) === -1) {
              // Select
              this.selectedIndexes.push(this.focusIndex)
            } else {
              // Unselect
              this.selectedIndexes.splice(this.selectedIndexes.indexOf(this.focusIndex), 1)
            }
          } else {
            // Pressed
            this.selectedIndexes[0] = this.focusIndex
          }
        }
      }
    })
    .accessibilityLevel('no')
    .priorityGesture(
      GestureGroup(GestureMode.Parallel,
        TapGesture()
          .onAction((event: GestureEvent) => {
            if (this.isGestureInProgress) {
              return;
            }
            let fingerInfo = event.fingerList.find(Boolean)
            if (fingerInfo === void 0) {
              return
            }
            if (this.options === void 0 || this.options.buttons === void 0) {
              return
            }
            let selectedInfo = fingerInfo.localX

            let buttonLength: number = Math.min(this.options.buttons.length, this.buttonItemsSize.length)
            for (let i = 0; i < buttonLength; i++) {
              selectedInfo = selectedInfo - (this.buttonItemsSize[i].width as number)
              if (selectedInfo >= 0) {
                continue
              }
              this.doSelectedChangeAnimate =
                this.selectedIndexes[0] > Math.min(this.options.buttons.length,
                  this.buttonItemsSize.length) ? false : true

              let realClickIndex: number = this.isShouldMirror() ? buttonLength - 1 - i : i
              if (this.onItemClicked) {
                this.onItemClicked(realClickIndex)
              }
              if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                let selectedIndex: number = this.selectedIndexes.indexOf(realClickIndex)
                if (selectedIndex === -1) {
                  this.selectedIndexes.push(realClickIndex)
                } else {
                  this.selectedIndexes.splice(selectedIndex, 1)
                }
              } else {
                this.selectedIndexes[0] = realClickIndex
              }
              this.doSelectedChangeAnimate = false
              break
            }
          }),
        SwipeGesture()
          .onAction((event: GestureEvent) => {
            if (this.options === void 0 || this.options.buttons === void 0 || event.sourceTool === SourceTool.TOUCHPAD) {
              return
            }
            if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
              // Non swipe gesture in multi-select mode
              return
            }
            if (this.isCurrentPositionSelected) {
              return
            }
            if (Math.abs(event.angle) < 90 && this.selectedIndexes[0] !== Math.min(this.options.buttons.length,
              this.buttonItemsSize.length) - 1) {
              // Move to next
              this.doSelectedChangeAnimate = true
              this.selectedIndexes[0] = this.selectedIndexes[0] + 1
              this.doSelectedChangeAnimate = false
            } else if (Math.abs(event.angle) > 90 && this.selectedIndexes[0] !== 0) {
              // Move to previous
              this.doSelectedChangeAnimate = true
              this.selectedIndexes[0] = this.selectedIndexes[0] - 1
              this.doSelectedChangeAnimate = false
            }
          }),
        PanGesture()
          .onActionStart((event: GestureEvent) => {
            this.isGestureInProgress = true;
            if (this.options === void 0 || this.options.buttons === void 0) {
              return
            }
            if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
              // Non drag gesture in multi-select mode
              return
            }
            let fingerInfo = event.fingerList.find(Boolean)
            if (fingerInfo === void 0) {
              return
            }
            let selectedInfo = fingerInfo.localX
            this.panGestureStartPoint = { x: fingerInfo.globalX, y: fingerInfo.globalY }
            this.isPanGestureMoved = false
            for (let i = 0; i < Math.min(this.options.buttons.length, this.buttonItemsSize.length); i++) {
              selectedInfo = selectedInfo - (this.buttonItemsSize[i].width as number)
              if (selectedInfo < 0) {
                this.isCurrentPositionSelected = i === this.selectedIndexes[0] ? true : false
                break
              }
            }
          })
          .onActionUpdate((event: GestureEvent) => {
            if (this.options === void 0 || this.options.buttons === void 0) {
              return
            }
            if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
              // Non drag gesture in multi-select mode
              return
            }
            if (!this.isCurrentPositionSelected) {
              return
            }
            let fingerInfo = event.fingerList.find(Boolean)
            if (fingerInfo === void 0) {
              return
            }
            let selectedInfo = fingerInfo.localX
            if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(fingerInfo.globalX,
              fingerInfo.globalY)) {
              this.isPanGestureMoved = true
            }
            for (let i = 0; i < Math.min(this.options.buttons.length, this.buttonItemsSize.length); i++) {
              selectedInfo = selectedInfo - (this.buttonItemsSize[i].width as number)
              if (selectedInfo < 0) {
                this.doSelectedChangeAnimate = true
                this.selectedIndexes[0] = i
                this.doSelectedChangeAnimate = false
                break
              }
            }
            this.zoomScaleArray.forEach((_, index) => {
              if (index === this.selectedIndexes[0]) {
                animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                  this.zoomScaleArray[index] = 0.95
                })
              } else {
                animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                  this.zoomScaleArray[index] = 1
                })
              }
            })
          })
          .onActionEnd((event: GestureEvent) => {
            this.isGestureInProgress = false;
            if (this.options === void 0 || this.options.buttons === void 0) {
              return
            }
            if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
              // Non drag gesture in multi-select mode
              return
            }
            let fingerInfo = event.fingerList.find(Boolean)
            if (fingerInfo === void 0) {
              return
            }
            if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(fingerInfo.globalX,
              fingerInfo.globalY)) {
              this.isPanGestureMoved = true
            }
            if (this.isMouseWheelScroll(event)) {
              let offset = event.offsetX !== 0 ? event.offsetX : event.offsetY
              this.doSelectedChangeAnimate = true
              if (offset > 0 && this.selectedIndexes[0] > 0) {
                this.selectedIndexes[0] -= 1
              } else if (offset < 0 && this.selectedIndexes[0] < Math.min(this.options.buttons.length,
                this.buttonItemsSize.length) - 1) {
                this.selectedIndexes[0] += 1
              }
              this.doSelectedChangeAnimate = false
            }
            animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
              this.zoomScaleArray[this.selectedIndexes[0]] = 1
            })
            this.isCurrentPositionSelected = false
          })
          .onActionCancel(() => {
            this.isGestureInProgress = false;
            if (this.options === void 0 || this.options.buttons === void 0) {
              return
            }
            if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
              return
            }
            animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
              this.zoomScaleArray[this.selectedIndexes[0]] = 1
            })
            this.isCurrentPositionSelected = false
          })
      )
    )
  }

  getMaxFontSize(): number {
    if (typeof this.maxFontScale === void 0) {
      return DEFAULT_MAX_FONT_SCALE;
    }
    if (typeof this.maxFontScale === 'number') {
      return Math.max(Math.min(this.maxFontScale, MAX_MAX_FONT_SCALE), MIN_MAX_FONT_SCALE);
    }
    const resourceManager = this.getUIContext().getHostContext()?.resourceManager;
    if (!resourceManager) {
      return DEFAULT_MAX_FONT_SCALE;
    }
    try {
      return resourceManager.getNumber(this.maxFontScale.id);
    } catch (error) {
      console.error(`Ace SegmentButton getMaxFontSize, error: ${error.toString()}`);
      return DEFAULT_MAX_FONT_SCALE;
    }
  }

  getSelectedChangeCurve(): ICurve | null {
    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
      return null
    }
    return curves.springMotion(0.347, 0.99)
  }

  updateAnimatedProperty(curve: ICurve | null) {
    let setAnimatedPropertyFunc = () => {
      this.selectedItemPosition = this.selectedIndexes.length === 0 ? {
      } : this.buttonItemsPosition[this.selectedIndexes[0]]
      this.buttonItemsSelected.forEach((selected, index) => {
        this.buttonItemProperty[index].fontColor = selected ?
          this.options.selectedFontColor ?? (this.options.type === 'tab' ?
          segmentButtonTheme.TAB_SELECTED_FONT_COLOR : segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR) :
          this.options.fontColor ?? segmentButtonTheme.FONT_COLOR
      })
    }
    if (curve) {
      animateTo({ curve: curve }, setAnimatedPropertyFunc)
    } else {
      setAnimatedPropertyFunc()
    }
    this.buttonItemsSelected.forEach((selected, index) => {
      this.buttonItemProperty[index].fontSize = selected ? this.options.selectedFontSize ??
      segmentButtonTheme.SELECTED_FONT_SIZE : this.options.fontSize ?? segmentButtonTheme.FONT_SIZE
      this.buttonItemProperty[index].fontWeight = selected ? this.options.selectedFontWeight ?? FontWeight.Medium :
        this.options.fontWeight ?? FontWeight.Regular
      this.buttonItemProperty[index].isSelected = selected
    })
  }
}

function resourceToNumber(context: Context | undefined, resource: Resource, defaultValue: number): number {
  if (!resource || !resource.type || !context) {
    console.error('[SegmentButton] failed: resource get fail.');
    return defaultValue;
  }
  let resourceManager = context?.resourceManager;
  if (!resourceManager) {
    console.error('[SegmentButton] failed to get resourceManager.');
    return defaultValue;
  }
  switch (resource.type) {
    case RESOURCE_TYPE_FLOAT:
    case RESOURCE_TYPE_INTEGER:
      try {
        if (resource.id !== -1) {
          return resourceManager.getNumber(resource);
        }
        return resourceManager.getNumberByName((resource.params as string[])[0].split('.')[2]);
      } catch (error) {
        console.error(`[SegmentButton] get resource error, return defaultValue`);
        return defaultValue;
      }
    default:
      return defaultValue;
  }
}