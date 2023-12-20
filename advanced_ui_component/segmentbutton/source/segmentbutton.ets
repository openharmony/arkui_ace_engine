/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
import curves from '@ohos.curves'
import { KeyCode } from '@ohos.multimodalInput.keyCode'

const MIN_ITEM_COUNT = 2
const MAX_ITEM_COUNT = 5

interface SegmentButtonThemeInterface {
  FONT_COLOR: ResourceColor,
  TAB_SELECTED_FONT_COLOR: ResourceColor,
  CAPSULE_SELECTED_FONT_COLOR: ResourceColor,
  FONT_SIZE: DimensionNoPercentage,
  SELECTED_FONT_SIZE: DimensionNoPercentage,
  BACKGROUND_COLOR: ResourceColor,
  TAB_SELECTED_BACKGROUND_COLOR: ResourceColor,
  CAPSULE_SELECTED_BACKGROUND_COLOR: ResourceColor,
  FOCUS_BORDER_COLOR: ResourceColor,
  HOVER_COlOR: ResourceColor,
  PRESS_COLOR: ResourceColor,
  BACKGROUND_BLUR_STYLE: BlurStyle,
}

const SegmentButtonTheme: SegmentButtonThemeInterface = {
  FONT_COLOR: $r('sys.color.ohos_id_color_text_secondary'),
  TAB_SELECTED_FONT_COLOR: $r('sys.color.ohos_id_color_text_primary'),
  CAPSULE_SELECTED_FONT_COLOR: $r('sys.color.ohos_id_color_foreground_contrary'),
  FONT_SIZE: $r('sys.float.ohos_id_text_size_body2'),
  SELECTED_FONT_SIZE: $r('sys.float.ohos_id_text_size_body2'),
  BACKGROUND_COLOR: $r('sys.color.ohos_id_color_button_normal'),
  TAB_SELECTED_BACKGROUND_COLOR: $r('sys.color.ohos_id_color_foreground_contrary'),
  CAPSULE_SELECTED_BACKGROUND_COLOR: $r('sys.color.ohos_id_color_emphasize'),
  FOCUS_BORDER_COLOR: $r("sys.color.ohos_id_color_focused_outline"),
  HOVER_COlOR: $r("sys.color.ohos_id_color_hover"),
  PRESS_COLOR: $r("sys.color.ohos_id_color_click_effect"),
  BACKGROUND_BLUR_STYLE: BlurStyle.NONE
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
}

interface SegmentButtonIconItem {
  icon: ResourceStr,
  selectedIcon: ResourceStr
}

interface SegmentButtonIconTextItem {
  icon: ResourceStr,
  selectedIcon: ResourceStr,
  text: ResourceStr
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
  backgroundBlurStyle?: BlurStyle
}

type ItemRestriction<T> = [T, T, T?, T?, T?]
type SegmentButtonItemTuple = ItemRestriction<SegmentButtonTextItem> | ItemRestriction<SegmentButtonIconItem> | ItemRestriction<SegmentButtonIconTextItem>
type SegmentButtonItemArray = Array<SegmentButtonTextItem> | Array<SegmentButtonIconItem> | Array<SegmentButtonIconTextItem>

export interface TabSegmentButtonConstructionOptions extends CommonSegmentButtonOptions {
  buttons: ItemRestriction<SegmentButtonTextItem>
}

export interface CapsuleSegmentButtonConstructionOptions extends CommonSegmentButtonOptions {
  buttons: SegmentButtonItemTuple
  multiply?: boolean
}

export interface TabSegmentButtonOptions extends TabSegmentButtonConstructionOptions {
  type: "tab",
}

export interface CapsuleSegmentButtonOptions extends CapsuleSegmentButtonConstructionOptions {
  type: "capsule"
}

interface SegmentButtonItemOptionsConstructorOptions {
  icon?: ResourceStr
  selectedIcon?: ResourceStr
  text?: ResourceStr
}

@Observed
class SegmentButtonItemOptions {
  icon?: ResourceStr
  selectedIcon?: ResourceStr
  text?: ResourceStr

  constructor(options: SegmentButtonItemOptionsConstructorOptions) {
    this.icon = options.icon
    this.selectedIcon = options.selectedIcon
    this.text = options.text
  }
}

@Observed
export class SegmentButtonItemOptionsArray extends Array<SegmentButtonItemOptions> {
  changeStartIndex: number | undefined = void 0
  deleteCount: number | undefined = void 0
  addLength: number | undefined = void 0

  constructor(length: number)

  constructor(elements: SegmentButtonItemTuple)

  constructor(elementsOrLength: SegmentButtonItemTuple | number) {

    super(typeof elementsOrLength === "number" ? elementsOrLength : 0);

    if (typeof elementsOrLength !== "number" && elementsOrLength !== void 0) {
      super.push(...elementsOrLength.map((element?: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem) => new SegmentButtonItemOptions(element as SegmentButtonItemOptionsConstructorOptions)))
    }
  }

  push(...items: SegmentButtonItemArray): number {
    if (this.length + items.length > MAX_ITEM_COUNT) {
      console.warn("Exceeded the maximum number of elements (5).")
      return this.length
    }
    this.changeStartIndex = this.length
    this.deleteCount = 0
    this.addLength = items.length
    return super.push(...items.map((element: SegmentButtonItemOptionsConstructorOptions) => new SegmentButtonItemOptions(element)))
  }

  pop() {
    if (this.length <= MIN_ITEM_COUNT) {
      console.warn("Below the minimum number of elements (2).")
      return void 0
    }
    this.changeStartIndex = this.length - 1
    this.deleteCount = 1
    this.addLength = 0
    return super.pop()
  }

  shift() {
    if (this.length <= MIN_ITEM_COUNT) {
      console.warn("Below the minimum number of elements (2).")
      return void 0
    }
    this.changeStartIndex = 0
    this.deleteCount = 1
    this.addLength = 0
    return super.shift()
  }

  unshift(...items: SegmentButtonItemArray): number {
    if (this.length + items.length > MAX_ITEM_COUNT) {
      console.warn("Exceeded the maximum number of elements (5).")
      return this.length
    }
    if (items.length > 0) {
      this.changeStartIndex = 0
      this.deleteCount = 0
      this.addLength = items.length
    }
    return super.unshift(...items.map((element: SegmentButtonItemOptionsConstructorOptions) => new SegmentButtonItemOptions(element)))
  }

  splice(start: number, deleteCount: number, ...items: SegmentButtonItemOptions[]): SegmentButtonItemOptions[] {
    let length = (this.length - deleteCount) < 0 ? 0 : (this.length - deleteCount)
    length += items.length
    if (length < MIN_ITEM_COUNT) {
      console.warn("Below the minimum number of elements (2).")
      return []
    }
    if (length > MAX_ITEM_COUNT) {
      console.warn("Exceeded the maximum number of elements (5).")
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
  type: "tab" | "capsule"
  multiply: boolean = false
  fontColor: ResourceColor
  selectedFontColor: ResourceColor
  fontSize: DimensionNoPercentage
  selectedFontSize: DimensionNoPercentage
  fontWeight: FontWeight
  selectedFontWeight: FontWeight
  backgroundColor: ResourceColor
  selectedBackgroundColor: ResourceColor
  imageSize: SizeOptions
  buttonPadding: Padding | Dimension
  textPadding: Padding | Dimension
  componentPadding: Padding | Dimension
  showText: boolean = false
  showIcon: boolean = false
  iconTextRadius?: number
  iconTextBackgroundRadius?: number
  backgroundBlurStyle: BlurStyle
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

  onButtonsChange?: () => void

  constructor(options: TabSegmentButtonOptions | CapsuleSegmentButtonOptions) {
    this.fontColor = options.fontColor ?? SegmentButtonTheme.FONT_COLOR
    this.selectedFontColor = options.selectedFontColor ?? SegmentButtonTheme.TAB_SELECTED_FONT_COLOR
    this.fontSize = options.fontSize ?? SegmentButtonTheme.FONT_SIZE
    this.selectedFontSize = options.selectedFontSize ?? SegmentButtonTheme.SELECTED_FONT_SIZE
    this.fontWeight = options.fontWeight ?? FontWeight.Regular
    this.selectedFontWeight = options.selectedFontWeight ?? FontWeight.Medium
    this.backgroundColor = options.backgroundColor ?? SegmentButtonTheme.BACKGROUND_COLOR
    this.selectedBackgroundColor = options.selectedBackgroundColor ?? SegmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR
    this.imageSize = options.imageSize ?? { width: 24, height: 24 }
    this.buttonPadding = options.buttonPadding ?? { top: 4, right: 8, bottom: 4, left: 8 }
    this.textPadding = options.textPadding ?? 0
    this.type = options.type
    this.backgroundBlurStyle = options.backgroundBlurStyle ?? SegmentButtonTheme.BACKGROUND_BLUR_STYLE
    this.buttons = new SegmentButtonItemOptionsArray(options.buttons)
    if (this.type === "capsule") {
      this.multiply = (options as CapsuleSegmentButtonOptions).multiply ?? false
      this.buttons.forEach(button => {
        this.showText ||= button.text !== void 0
        this.showIcon ||= button.icon !== void 0 || button.selectedIcon !== void 0
      })
      if (this.showText && this.showIcon) {
        this.iconTextRadius = 12
        this.buttonPadding = options.buttonPadding ?? { top: 6, right: 8, bottom: 6, left: 8 }
        this.iconTextBackgroundRadius = 14
      }
      this.selectedFontColor = options.selectedFontColor ?? SegmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR
      this.selectedBackgroundColor = options.selectedBackgroundColor ?? SegmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR
    } else {
      this.showText = true
    }
    this.componentPadding = this.multiply ? 0 : 2
  }

  static tab(options: TabSegmentButtonConstructionOptions): SegmentButtonOptions {
    return new SegmentButtonOptions({
      type: "tab",
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
      backgroundBlurStyle: options.backgroundBlurStyle
    })
  }

  static capsule(options: CapsuleSegmentButtonConstructionOptions): SegmentButtonOptions {
    return new SegmentButtonOptions({
      type: "capsule",
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
      backgroundBlurStyle: options.backgroundBlurStyle
    })
  }
}

@Component
struct MultiSelectBackground {
  @ObjectLink optionsArray: SegmentButtonItemOptionsArray
  @ObjectLink options: SegmentButtonOptions
  @Consume buttonBorderRadius: BorderRadiuses[]
  @Consume buttonItemsSize: SizeOptions[]

  build() {
    Row({ space: 1 }) {
      ForEach(this.optionsArray, (_: SegmentButtonItemOptions, index) => {
        if (index < MAX_ITEM_COUNT) {
          Stack()
            .layoutWeight(1)
            .height(this.buttonItemsSize[index].height)
            .backgroundColor(this.options.backgroundColor ?? SegmentButtonTheme.BACKGROUND_COLOR)
            .borderRadius(this.buttonBorderRadius[index])
            .backgroundBlurStyle(this.options.backgroundBlurStyle)
        }
      })
    }
    .padding(this.options.componentPadding)
  }
}

@Component
struct SelectItem {
  @ObjectLink optionsArray: SegmentButtonItemOptionsArray
  @ObjectLink options: SegmentButtonOptions
  @Link selectedIndexes: number[]
  @Consume buttonItemsSize: SizeOptions[]
  @Consume selectedItemPosition: Position
  @Consume zoomScaleArray: number[]
  @Consume buttonBorderRadius: BorderRadiuses[]

  build() {
    if (this.selectedIndexes !== void 0 && this.selectedIndexes.length !== 0) {
      Stack()
        .borderRadius(this.buttonBorderRadius[this.selectedIndexes[0]])
        .size(this.buttonItemsSize[this.selectedIndexes[0]])
        .backgroundColor(this.options.selectedBackgroundColor ??
          (this.options.type === 'tab' ? SegmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR :
          SegmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR))
        .position(this.selectedItemPosition)
        .scale({ x: this.zoomScaleArray[this.selectedIndexes[0]], y: this.zoomScaleArray[this.selectedIndexes[0]] })
        .shadow(ShadowStyle.OUTER_DEFAULT_MD)
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
  @Consume buttonBorderRadius: BorderRadiuses[]
  @State multiColor: ResourceColor[] = Array.from({ length: MAX_ITEM_COUNT }, (_: Object, index) => Color.Transparent)

  onOptionsChange() {
    for (let i = 0; i < this.selectedIndexes.length; i++) {
      this.multiColor[this.selectedIndexes[i]] = this.options.selectedBackgroundColor ?? SegmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR
    }
  }

  onSelectedChange() {
    for (let i = 0; i < MAX_ITEM_COUNT; i++) {
      this.multiColor[i] = Color.Transparent
    }
    for (let i = 0; i < this.selectedIndexes.length; i++) {
      this.multiColor[this.selectedIndexes[i]] = this.options.selectedBackgroundColor ?? SegmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR
    }
  }

  aboutToAppear() {
    for (let i = 0; i < this.selectedIndexes.length; i++) {
      this.multiColor[this.selectedIndexes[i]] = this.options.selectedBackgroundColor ?? SegmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR
    }
  }

  build() {
    Row({ space: 1 }) {
      ForEach(this.optionsArray, (_: SegmentButtonItemOptions, index) => {
        if (index < MAX_ITEM_COUNT) {
          Stack()
            .width(this.buttonItemsSize[index].width)
            .height(this.buttonItemsSize[index].height)
            .backgroundColor(this.multiColor[index])
            .borderRadius(this.buttonBorderRadius[index])
        }
      })
    }
    .padding(this.options.componentPadding)
  }
}

@Component
struct SegmentButtonItem {
  @ObjectLink itemOptions: SegmentButtonItemOptions
  @ObjectLink options: SegmentButtonOptions;
  @ObjectLink property: ItemProperty
  @Prop index: number

  build() {
    Column({ space: 2 }) {
      if (this.options.showIcon) {
        Image(this.property.isSelected ? this.itemOptions.selectedIcon : this.itemOptions.icon)
          .size(this.options.imageSize ?? { width: 24, height: 24 })
          .focusable(this.index == 0)
          .draggable(false)
          .fillColor(this.property.isSelected ? (this.options.selectedFontColor ?? SegmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR) :
            (this.options.fontColor ?? SegmentButtonTheme.FONT_COLOR))
      }
      if (this.options.showText) {
        Text(this.itemOptions.text)
          .fontColor(this.property.fontColor)
          .fontWeight(this.property.fontWeight)
          .fontSize(this.property.fontSize)
          .minFontSize(9)
          .maxFontSize(this.property.fontSize)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .maxLines(1)
          .textAlign(TextAlign.Center)
          .focusable(this.index == 0 && !this.options.showIcon)
          .padding(this.options.textPadding ?? 0)
      }
    }
    .justifyContent(FlexAlign.Center)
    .padding(this.options.buttonPadding ?? ((this.options.type === 'capsule' && this.options.showText && this.options.showIcon) ?
      { top: 6, right: 8, bottom: 6, left: 8 } : { top: 4, right: 8, bottom: 4, left: 8 }))
    .constraintSize({ minHeight: 28 })
  }
}

@Observed
class HoverColorProperty {
  hoverColor: ResourceColor = Color.Transparent
}

@Component
struct PressAndHoverEffect {
  @Consume buttonItemsSize: SizeOptions[]
  @Prop press: boolean
  @ObjectLink colorProperty: HoverColorProperty
  @Consume buttonBorderRadius: BorderRadiuses[]
  pressIndex: number = 0
  pressColor: ResourceColor = SegmentButtonTheme.PRESS_COLOR

  build() {
    Stack()
      .size(this.buttonItemsSize[this.pressIndex])
      .backgroundColor(this.press ? this.pressColor : this.colorProperty.hoverColor)
      .borderRadius(this.buttonBorderRadius[this.pressIndex])
  }
}

@Component
struct SegmentButtonItemArrayComponent {
  @ObjectLink @Watch('onOptionsArrayChange') optionsArray: SegmentButtonItemOptionsArray
  @ObjectLink @Watch('onOptionsChange') options: SegmentButtonOptions
  @Link selectedIndexes: number[]
  @Consume componentSize: SizeOptions
  @Consume buttonBorderRadius: BorderRadiuses[]
  @Consume @Watch('onButtonItemsSizeChange') buttonItemsSize: SizeOptions[]
  @Consume buttonItemsPosition: Position[]
  @Consume focusIndex: number
  @Consume zoomScaleArray: number[]
  @Consume buttonItemProperty: ItemProperty[]
  @Consume buttonItemsSelected: boolean[]
  @State pressArray: boolean[] = Array.from({ length: MAX_ITEM_COUNT }, (_: Object, index) => false)
  @State hoverColorArray: HoverColorProperty[] = Array.from({
    length: MAX_ITEM_COUNT
  }, (_: Object, index) => new HoverColorProperty())
  @State buttonWidth: number[] = Array.from({ length: MAX_ITEM_COUNT }, (_: Object, index) => 0)
  @State buttonHeight: number[] = Array.from({ length: MAX_ITEM_COUNT }, (_: Object, index) => 0)
  private buttonItemsRealHeight: number[] = Array.from({ length: MAX_ITEM_COUNT }, (_: Object, index) => 0)

  onButtonItemsSizeChange() {
    this.buttonItemsSize.forEach((value, index) => {
      this.buttonWidth[index] = value.width as number
      this.buttonHeight[index] = value.height as number
    })
  }

  changeSelectedIndexes(buttonsLength: number) {
    if (this.optionsArray.changeStartIndex === void 0 || this.optionsArray.deleteCount === void 0 || this.optionsArray.addLength === void 0) {
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
        let indexes = saveIndexes.map(value => this.optionsArray.changeStartIndex && (value > this.optionsArray.changeStartIndex) ? value - 1 : value)
        if (deleteIndex !== -1) {
          indexes.splice(deleteIndex, 1)
        }
        saveIndexes = indexes
      }
      for (let i = 0; i < this.optionsArray.addLength; i++) {
        let indexes = saveIndexes.map(value => this.optionsArray.changeStartIndex && (value >= this.optionsArray.changeStartIndex) ? value + 1 : value)
        saveIndexes = indexes
      }
      this.selectedIndexes = saveIndexes
    }

  }

  changeFocusIndex(buttonsLength: number) {
    if (this.optionsArray.changeStartIndex === void 0 || this.optionsArray.deleteCount === void 0 || this.optionsArray.addLength === void 0) {
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
    if (this.optionsArray.changeStartIndex !== void 0 && this.optionsArray.deleteCount !== void 0 && this.optionsArray.addLength !== void 0) {
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

  aboutToAppear() {
    for (let index = 0; index < this.buttonItemsRealHeight.length; index++) {
      this.buttonItemsRealHeight[index] = 0
    }
  }

  @Builder
  focusStack(index: number) {
    Stack() {
      if (index === this.focusIndex) {
        Stack()
          .borderRadius({
            topLeft: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonBorderRadius[index].topLeft as number + 4 : this.buttonBorderRadius[index].topLeft,
            topRight: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonBorderRadius[index].topRight as number + 4 : this.buttonBorderRadius[index].topRight,
            bottomLeft: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonBorderRadius[index].bottomLeft as number + 4 : this.buttonBorderRadius[index].bottomLeft,
            bottomRight: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonBorderRadius[index].bottomRight as number + 4 : this.buttonBorderRadius[index].bottomRight
          })
          .size({
            width: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonWidth[index] + 8 : this.buttonWidth[index],
            height: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ? this.buttonHeight[index] + 8 : this.buttonHeight[index]
          })
          .borderColor(SegmentButtonTheme.FOCUS_BORDER_COLOR)
          .borderWidth(2)
      }
    }
    .size({ width: 1, height: 1 })
    .align(Alignment.Center)
  }

  calculateBorderRadius() {
    let borderRadiusArray: BorderRadiuses[] = Array.from({
      length: MAX_ITEM_COUNT
    }, (_: Object, index): BorderRadiuses => {
      return { topLeft: 0, topRight: 0, bottomLeft: 0, bottomRight: 0 }
    })
    for (let index = 0; index < this.buttonBorderRadius.length; index++) {
      let halfButtonItemsSizeHeight = this.buttonItemsSize[index].height as number / 2
      if (this.options.type === 'tab' || !(this.options.multiply ?? false)) {
        borderRadiusArray[index].topLeft = this.options.iconTextRadius ?? halfButtonItemsSizeHeight
        borderRadiusArray[index].topRight = this.options.iconTextRadius ?? halfButtonItemsSizeHeight
        borderRadiusArray[index].bottomLeft = this.options.iconTextRadius ?? halfButtonItemsSizeHeight
        borderRadiusArray[index].bottomRight = this.options.iconTextRadius ?? halfButtonItemsSizeHeight
      } else {
        if (index === 0) {
          borderRadiusArray[index].topLeft = this.options.iconTextRadius ?? halfButtonItemsSizeHeight
          borderRadiusArray[index].topRight = 0
          borderRadiusArray[index].bottomLeft = this.options.iconTextRadius ?? halfButtonItemsSizeHeight
          borderRadiusArray[index].bottomRight = 0
        } else if (this.options.buttons && index === Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
          borderRadiusArray[index].topLeft = 0
          borderRadiusArray[index].topRight = this.options.iconTextRadius ?? halfButtonItemsSizeHeight
          borderRadiusArray[index].bottomLeft = 0
          borderRadiusArray[index].bottomRight = this.options.iconTextRadius ?? halfButtonItemsSizeHeight
        } else {
          borderRadiusArray[index].topLeft = 0
          borderRadiusArray[index].topRight = 0
          borderRadiusArray[index].bottomLeft = 0
          borderRadiusArray[index].bottomRight = 0
        }
      }
    }
    this.buttonBorderRadius = borderRadiusArray
  }

  build() {
    if (this.optionsArray !== void 0 && this.optionsArray.length > 1) {
      Row({ space: 1 }) {
        ForEach(this.optionsArray, (item: SegmentButtonItemOptions, index) => {
          if (index < MAX_ITEM_COUNT) {
            Stack() {
              PressAndHoverEffect({
                pressIndex: index,
                colorProperty: this.hoverColorArray[index],
                press: this.pressArray[index]
              })
              SegmentButtonItem({
                index: index,
                itemOptions: item,
                options: this.options,
                property: this.buttonItemProperty[index]
              })
                .onAreaChange((_, newValue) => {
                  // Calculate height of items
                  this.buttonItemsRealHeight[index] = newValue.height as number
                  let maxHeight = Math.max(...this.buttonItemsRealHeight.slice(0, this.options.buttons ? this.options.buttons.length : 0))
                  for (let index = 0; index < this.buttonItemsSize.length; index++) {
                    this.buttonItemsSize[index] = { width: this.buttonItemsSize[index].width, height: maxHeight }
                  }
                  this.calculateBorderRadius()
                })
            }
            .borderRadius(this.buttonBorderRadius[index])
            .scale({
              x: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[index],
              y: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1 : this.zoomScaleArray[index]
            })
            .layoutWeight(1)
            .onAreaChange((_, newValue) => {
              this.buttonItemsSize[index] = { width: newValue.width, height: this.buttonItemsSize[index].height }
              this.buttonItemsPosition[index] = newValue.position
            })
            .overlay(this.focusStack(index), {
              align: Alignment.Center
            })
            .onTouch((event: TouchEvent) => {
              if (event.source !== SourceType.TouchScreen) {
                return
              }
              if (event.type === TouchType.Down) {
                animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                  this.zoomScaleArray[index] = 0.95
                })
              } else if (event.type === TouchType.Up) {
                animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
                  this.zoomScaleArray[index] = 1
                })
              }
            })
            .onHover((isHover: boolean) => {
              if (isHover) {
                animateTo({ duration: 250, curve: Curve.Friction }, () => {
                  this.hoverColorArray[index].hoverColor = (SegmentButtonTheme.HOVER_COlOR)
                })
              } else {
                animateTo({ duration: 250, curve: Curve.Friction }, () => {
                  this.hoverColorArray[index].hoverColor = Color.Transparent
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
      .padding(this.options.componentPadding)
      .onAreaChange((_, newValue) => {
        this.componentSize = { width: newValue.width, height: newValue.height }
      })
    }
  }
}

@Observed
class ItemProperty {
  fontColor: ResourceColor = SegmentButtonTheme.FONT_COLOR
  fontSize: DimensionNoPercentage = SegmentButtonTheme.FONT_SIZE
  fontWeight: FontWeight = FontWeight.Regular
  isSelected: boolean = false
}

@Component
export struct SegmentButton {
  @ObjectLink @Watch('onOptionsChange') options: SegmentButtonOptions
  @Link @Watch('onSelectedChange') selectedIndexes: number[]
  @Provide componentSize: SizeOptions = { width: 0, height: 0 }
  @Provide buttonBorderRadius: BorderRadiuses[] = Array.from({
    length: MAX_ITEM_COUNT
  }, (_: Object, index): BorderRadiuses => {
    return { topLeft: 0, topRight: 0, bottomLeft: 0, bottomRight: 0 }
  })
  @Provide buttonItemsSize: SizeOptions[] = Array.from({ length: MAX_ITEM_COUNT }, (_: Object, index): SizeOptions => {
    return {}
  })
  @Provide @Watch('onItemsPositionChange') buttonItemsPosition: Position[] = Array.from({
    length: MAX_ITEM_COUNT
  }, (_: Object, index): Position => {
    return {}
  })
  @Provide buttonItemsSelected: boolean[] = Array.from({ length: MAX_ITEM_COUNT }, (_: Object, index) => false)
  @Provide buttonItemProperty: ItemProperty[] = Array.from({
    length: MAX_ITEM_COUNT
  }, (_: Object, index) => new ItemProperty())
  @Provide focusIndex: number = -1
  @Provide selectedItemPosition: Position = {}
  @Provide zoomScaleArray: number[] = Array.from({ length: MAX_ITEM_COUNT }, (_: Object, index) => 1.0)
  private doSelectedChangeAnimate: boolean = false
  private isCurrentPositionSelected: boolean = false
  private panGestureStartPoint: Point = { x: 0, y: 0 }
  private isPanGestureMoved: boolean = false

  onItemsPositionChange() {
    if (this.options === void 0 || this.options.buttons === void 0) {
      return
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
    this.updateSelectedIndexes()
    this.setItemsSelected()
    this.updateAnimatedProperty(null)
  }

  private isMouseWheelScroll(event: GestureEvent) {
    return event.source === SourceType.Mouse && !this.isPanGestureMoved
  }

  private isMovedFromPanGestureStartPoint(x: number, y: number) {
    return!nearEqual(x, this.panGestureStartPoint.x) || !nearEqual(y, this.panGestureStartPoint.y)
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
          Stack()
            .size(this.componentSize)
            .backgroundColor(this.options.backgroundColor ?? SegmentButtonTheme.BACKGROUND_COLOR)
            .borderRadius(this.options.iconTextBackgroundRadius ?? this.componentSize.height as number / 2)
            .backgroundBlurStyle(this.options.backgroundBlurStyle)
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
        .size(this.componentSize)
        .borderRadius((this.options.type === 'capsule' && (this.options.multiply ?? false) ?
        this.options.iconTextRadius : this.options.iconTextBackgroundRadius) ??
          this.componentSize.height as number / 2)
        .clip(true)

        SegmentButtonItemArrayComponent({
          optionsArray: this.options.buttons,
          options: this.options,
          selectedIndexes: $selectedIndexes,
        })
      }
    }
    .onFocus(() => {
      if (this.options === void 0) {
        return
      }
      if (this.selectedIndexes === void 0 || this.selectedIndexes.length === 0) {
        this.focusIndex = 0
        return
      }
      if (this.options.type === 'tab' || !(this.options.multiply ?? false)) {
        this.focusIndex = this.selectedIndexes[0]
      } else {
        this.focusIndex = Math.min(...this.selectedIndexes)
      }
    })
    .onBlur(() => {
      this.focusIndex = -1
    })
    .onKeyEvent((event: KeyEvent) => {
      if (this.options === void 0 || this.options.buttons === void 0) {
        return
      }
      if (event.type === KeyType.Down) {
        if ((event.keyCode === KeyCode.KEYCODE_DPAD_DOWN || event.keyCode === KeyCode.KEYCODE_DPAD_RIGHT) && this.focusIndex < (Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1)) {
          // Move to next
          this.focusIndex = this.focusIndex + 1
        }
        if ((event.keyCode === KeyCode.KEYCODE_DPAD_UP || event.keyCode === KeyCode.KEYCODE_DPAD_LEFT) && this.focusIndex > 0) {
          // Move to previous
          this.focusIndex = this.focusIndex - 1
        }
        if (event.keyCode === KeyCode.KEYCODE_SPACE || event.keyCode === KeyCode.KEYCODE_ENTER || event.keyCode === KeyCode.KEYCODE_NUMPAD_ENTER) {
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
    .gesture(
      GestureGroup(GestureMode.Parallel,
        TapGesture()
          .onAction((event: GestureEvent) => {
            let fingerInfo = event.fingerList.find(Boolean)
            if (fingerInfo === void 0) {
              return
            }
            if (this.options === void 0 || this.options.buttons === void 0) {
              return
            }
            let selectedInfo = fingerInfo.localX
            for (let i = 0; i < Math.min(this.options.buttons.length, this.buttonItemsSize.length); i++) {
              selectedInfo = selectedInfo - (this.buttonItemsSize[i].width as number)
              if (selectedInfo >= 0) {
                continue
              }
              this.doSelectedChangeAnimate =
                this.selectedIndexes[0] > Math.min(this.options.buttons.length, this.buttonItemsSize.length) ? false : true
              if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                if (this.selectedIndexes.indexOf(i) === -1) {
                  this.selectedIndexes.push(i)
                } else {
                  this.selectedIndexes.splice(this.selectedIndexes.indexOf(i), 1)
                }
              } else {
                this.selectedIndexes[0] = i
              }
              this.doSelectedChangeAnimate = false
              break
            }
          }),
        SwipeGesture()
          .onAction((event: GestureEvent) => {
            if (this.options === void 0 || this.options.buttons === void 0) {
              return
            }
            if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
              // Non swipe gesture in multi-select mode
              return
            }
            if (this.isCurrentPositionSelected) {
              return
            }
            if (event.angle > 0 && this.selectedIndexes[0] !== Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
              // Move to next
              this.doSelectedChangeAnimate = true
              this.selectedIndexes[0] = this.selectedIndexes[0] + 1
              this.doSelectedChangeAnimate = false
            } else if (event.angle < 0 && this.selectedIndexes[0] !== 0) {
              // Move to previous
              this.doSelectedChangeAnimate = true
              this.selectedIndexes[0] = this.selectedIndexes[0] - 1
              this.doSelectedChangeAnimate = false
            }
          }),
        PanGesture()
          .onActionStart((event: GestureEvent) => {
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
            if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(fingerInfo.globalX, fingerInfo.globalY)) {
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
            if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(fingerInfo.globalX, fingerInfo.globalY)) {
              this.isPanGestureMoved = true
            }
            if (this.isMouseWheelScroll(event)) {
              let offset = event.offsetX !== 0 ? event.offsetX : event.offsetY
              this.doSelectedChangeAnimate = true
              if (offset > 0 && this.selectedIndexes[0] > 0) {
                this.selectedIndexes[0] -= 1
              } else if (offset < 0 && this.selectedIndexes[0] < Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
                this.selectedIndexes[0] += 1
              }
              this.doSelectedChangeAnimate = false
            }
            animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
              this.zoomScaleArray[this.selectedIndexes[0]] = 1
            })
            this.isCurrentPositionSelected = false
          })
      )
    )
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
          SegmentButtonTheme.TAB_SELECTED_FONT_COLOR : SegmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR) :
          this.options.fontColor ?? SegmentButtonTheme.FONT_COLOR
      })
    }
    if (curve) {
      animateTo({ curve: curve }, setAnimatedPropertyFunc)
    } else {
      setAnimatedPropertyFunc()
    }
    this.buttonItemsSelected.forEach((selected, index) => {
      this.buttonItemProperty[index].fontSize = selected ? this.options.selectedFontSize ?? SegmentButtonTheme.SELECTED_FONT_SIZE
        : this.options.fontSize ?? SegmentButtonTheme.FONT_SIZE
      this.buttonItemProperty[index].fontWeight = selected ? this.options.selectedFontWeight ?? FontWeight.Medium :
        this.options.fontWeight ?? FontWeight.Regular
      this.buttonItemProperty[index].isSelected = selected
    })
  }
}