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

const curves = globalThis.requireNativeModule('ohos.curves');
const KeyCode = globalThis.requireNapi("multimodalInput.keyCode").KeyCode;

const MIN_ITEM_COUNT = 2
const MAX_ITEM_COUNT = 5

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

interface CommonSegmentButtonOptions {
  fontColor?: ResourceColor
  selectedFontColor?: ResourceColor
  fontSize?: Dimension
  selectedFontSize?: Dimension
  fontWeight?: FontWeight
  selectedFontWeight?: FontWeight
  backgroundColor?: ResourceColor
  selectedBackgroundColor?: ResourceColor
  imageSize?: SizeOptions
  buttonMargin?: Margin | Dimension
  textMargin?: Margin | Dimension
}

type SegmentButtonItemArray = Array<SegmentButtonTextItem> | Array<SegmentButtonIconItem> | Array<SegmentButtonIconTextItem>

export interface TabSegmentButtonConstructionOptions extends CommonSegmentButtonOptions {
  buttons: Array<SegmentButtonTextItem>
}

export interface CapsuleSegmentButtonConstructionOptions extends CommonSegmentButtonOptions {
  buttons: SegmentButtonItemArray
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
  changeStartIndex: number = void 0
  deleteCount: number = void 0
  addLength: number = void 0

  constructor(elements: SegmentButtonItemArray) {
    super()
    if (elements.length < MIN_ITEM_COUNT) {
      throw new RangeError("Below the minimum number of elements (2).")
    } else if (elements.length > MAX_ITEM_COUNT) {
      throw new RangeError("Exceeded the maximum number of elements (5).")
    }
    super.push(...elements.map(element => new SegmentButtonItemOptions(element)))
  }

  push(...items: SegmentButtonItemArray): number {
    if (this.length + items.length > MAX_ITEM_COUNT) {
      throw new RangeError("Exceeded the maximum number of elements (5).")
    }
    this.changeStartIndex = this.length - 1
    this.deleteCount = 0
    this.addLength = items.length
    return super.push(...items.map(element => new SegmentButtonItemOptions(element)))
  }

  pop() {
    if (this.length <= MIN_ITEM_COUNT) {
      throw new RangeError("Below the minimum number of elements (2).")
    }
    this.changeStartIndex = this.length - 1
    this.deleteCount = 1
    this.addLength = 0
    return super.pop()
  }

  shift() {
    if (this.length <= MIN_ITEM_COUNT) {
      throw new RangeError("Below the minimum number of elements (2).")
    }
    this.changeStartIndex = 0
    this.deleteCount = 1
    this.addLength = 0
    return super.shift()
  }

  unshift(...items: SegmentButtonItemArray): number {
    if (this.length + items.length > MAX_ITEM_COUNT) {
      throw new RangeError("Exceeded the maximum number of elements (5).")
    }
    this.changeStartIndex = 0
    this.deleteCount = 0
    this.addLength = 1
    return super.unshift(...items.map(element => new SegmentButtonItemOptions(element)))
  }

  splice(start: number, deleteCount: number, ...items: SegmentButtonItemOptions[]): SegmentButtonItemOptions[] {
    if (deleteCount > MAX_ITEM_COUNT || this.length - deleteCount + items.length < MIN_ITEM_COUNT) {
      throw new RangeError("Below the minimum number of elements (2).")
    }
    if (this.length - deleteCount + items.length > MAX_ITEM_COUNT) {
      throw new RangeError("Exceeded the maximum number of elements (5).")
    }
    this.changeStartIndex = start
    this.deleteCount = deleteCount
    this.addLength = items.length
    return super.splice(start, deleteCount, ...items)
  }

  static create(elements: SegmentButtonItemArray): SegmentButtonItemOptionsArray {
    return new SegmentButtonItemOptionsArray(elements)
  }
}

@Observed
export class SegmentButtonOptions {
  type: "tab" | "capsule"
  multiply: boolean = false
  buttons: SegmentButtonItemOptionsArray
  fontColor: ResourceColor
  selectedFontColor: ResourceColor
  fontSize: Dimension
  selectedFontSize: Dimension
  fontWeight: FontWeight
  selectedFontWeight: FontWeight
  backgroundColor: ResourceColor
  selectedBackgroundColor: ResourceColor
  imageSize: SizeOptions
  buttonMargin: Margin | Dimension
  textMargin: Margin | Dimension
  componentPadding: Padding | Dimension
  showText: boolean = false
  showIcon: boolean = false
  iconTextRadius?: number
  iconTextBackgroundRadius?: number

  constructor(options: TabSegmentButtonOptions | CapsuleSegmentButtonOptions) {
    this.fontColor = options.fontColor ?? $r('sys.color.ohos_id_color_text_secondary')
    this.selectedFontColor = options.selectedFontColor ?? $r('sys.color.ohos_id_color_text_primary')
    this.fontSize = options.fontSize ?? $r('sys.float.ohos_id_text_size_body2')
    this.selectedFontSize = options.selectedFontSize ?? $r('sys.float.ohos_id_text_size_body2')
    this.fontWeight = options.fontWeight ?? FontWeight.Regular
    this.selectedFontWeight = options.selectedFontWeight ?? FontWeight.Medium
    this.backgroundColor = options.backgroundColor ?? $r('sys.color.ohos_id_color_button_normal')
    this.selectedBackgroundColor = options.selectedBackgroundColor ?? $r('sys.color.ohos_id_color_foreground_contrary')
    this.imageSize = options.imageSize ?? { width: 24, height: 24 }
    this.buttonMargin = options.buttonMargin ?? { top: 4, right: 8, bottom: 4, left: 8 }
    this.textMargin = options.textMargin ?? 0
    this.type = options.type
    this.buttons = new SegmentButtonItemOptionsArray(options.buttons)
    if (this.type === "capsule") {
      this.multiply = (options as CapsuleSegmentButtonOptions).multiply ?? false
      this.buttons.forEach(button => {
        this.showText ||= button.text !== void 0
        this.showIcon ||= button.icon !== void 0 || button.selectedIcon !== void 0
      })
      if (this.showText && this.showIcon) {
        this.iconTextRadius = 12
        this.buttonMargin = options.buttonMargin ?? { top: 6, right: 8, bottom: 6, left: 8 }
        this.iconTextBackgroundRadius = 14
      }
      this.selectedFontColor = options.selectedFontColor ?? $r('sys.color.ohos_id_color_foreground_contrary')
      this.selectedBackgroundColor = options.selectedBackgroundColor ?? $r('sys.color.ohos_id_color_emphasize')
    } else {
      this.showText = true
    }
    this.componentPadding = this.multiply ? 0 : 2
  }

  static tab(options: TabSegmentButtonConstructionOptions): SegmentButtonOptions {
    return new SegmentButtonOptions({ type: "tab", ...options })
  }

  static capsule(options: CapsuleSegmentButtonConstructionOptions): SegmentButtonOptions {
    return new SegmentButtonOptions({ type: "capsule", ...options })
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
      ForEach(this.optionsArray, (_, index) => {
        if (index < MAX_ITEM_COUNT) {
          Stack()
            .layoutWeight(1)
            .height(this.buttonItemsSize[index].height)
            .backgroundColor(this.options.backgroundColor)
            .borderRadius(this.buttonBorderRadius[index])
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
    if (this.selectedIndexes.length !== 0) {
      Stack()
        .borderRadius(this.buttonBorderRadius[this.selectedIndexes[0]])
        .size(this.buttonItemsSize[this.selectedIndexes[0]])
        .backgroundColor(this.options.selectedBackgroundColor)
        .position(this.selectedItemPosition)
        .scale({ x: this.zoomScaleArray[this.selectedIndexes[0]], y: this.zoomScaleArray[this.selectedIndexes[0]] })
        .shadow(ShadowStyle.OUTER_DEFAULT_MD)
    }
  }
}

@Component
struct MultiSelectItemArray {
  @ObjectLink optionsArray: SegmentButtonItemOptionsArray
  @ObjectLink options: SegmentButtonOptions
  @Link @Watch('selectedChange') selectedIndexes: number[]
  @Consume buttonItemsSize: SizeOptions[]
  @Consume zoomScaleArray: number[]
  @Consume buttonBorderRadius: BorderRadiuses[]
  @State multiColor: ResourceColor[] = Array.from({ length: MAX_ITEM_COUNT }, () => Color.Transparent)

  selectedChange() {
    for (let i = 0; i < MAX_ITEM_COUNT; i++) {
      this.multiColor[i] = Color.Transparent
    }
    for (let i = 0; i < this.selectedIndexes.length; i++) {
      this.multiColor[this.selectedIndexes[i]] = this.options.selectedBackgroundColor
    }
  }

  aboutToAppear() {
    for (let i = 0; i < this.selectedIndexes.length; i++) {
      this.multiColor[this.selectedIndexes[i]] = this.options.selectedBackgroundColor
    }
  }

  build() {
    Row({ space: 1 }) {
      ForEach(this.optionsArray, (_, index) => {
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
  public index: number

  build() {
    Column({ space: 2 }) {
      if (this.options.showIcon) {
        Image(this.property.isSelected ? this.itemOptions.selectedIcon : this.itemOptions.icon)
          .size(this.options.imageSize)
          .focusable(this.index == 0)
          .draggable(false)
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
          .padding(this.options.textMargin)
      }
    }
    .justifyContent(FlexAlign.Center)
    .padding(this.options.buttonMargin)
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
  pressColor: ResourceColor = $r("sys.color.ohos_id_color_click_effect")

  build() {
    Stack()
      .size(this.buttonItemsSize[this.pressIndex])
      .backgroundColor(this.press ? this.pressColor : this.colorProperty.hoverColor)
      .borderRadius(this.buttonBorderRadius[this.pressIndex])
  }
}

@Component
struct SegmentButtonItemArrayComponent {
  @ObjectLink @Watch('optionsArrayChange') optionsArray: SegmentButtonItemOptionsArray
  @ObjectLink options: SegmentButtonOptions
  @Link selectedIndexes: number[]
  @Consume componentSize: SizeOptions
  @Consume buttonBorderRadius: BorderRadiuses[]
  @Consume @Watch('buttonItemsSizeChange') buttonItemsSize: SizeOptions[]
  @Consume buttonItemsPosition: Position[]
  @Consume focusIndex: number
  @Consume zoomScaleArray: number[]
  @Consume buttonItemProperty: ItemProperty[]
  @Consume buttonItemsSelected: boolean[]
  @State pressArray: boolean[] = Array.from({ length: MAX_ITEM_COUNT }, () => false)
  @State hoverColorArray: HoverColorProperty[] = Array.from({ length: MAX_ITEM_COUNT }, () => new HoverColorProperty())
  @State buttonWidth: number[] = Array.from({ length: MAX_ITEM_COUNT }, () => 0)
  @State buttonHeight: number[] = Array.from({ length: MAX_ITEM_COUNT }, () => 0)
  private buttonItemsRealHeight: number[] = Array.from({ length: MAX_ITEM_COUNT }, () => 0)

  buttonItemsSizeChange() {
    this.buttonItemsSize.forEach((value, index) => {
      this.buttonWidth[index] = value.width as number
      this.buttonHeight[index] = value.height as number
    })
  }

  changeSelectedIndexes(buttonsLength: number) {
    if (!this.options.multiply) {
      // Multi-select
      if (this.selectedIndexes[0] === void 0) {
        return
      }
      if (this.selectedIndexes[0] < this.optionsArray.changeStartIndex) {
        return
      }
      if (this.selectedIndexes[0] === this.optionsArray.changeStartIndex && this.optionsArray.changeStartIndex + this.optionsArray.deleteCount - this.optionsArray.addLength === this.optionsArray.length) {
        // Last item
        this.selectedIndexes[0] = this.optionsArray.changeStartIndex - 1
        return
      }
      if (this.optionsArray.changeStartIndex + this.optionsArray.deleteCount > this.selectedIndexes[0]) {
        this.selectedIndexes[0] = this.optionsArray.changeStartIndex
      } else {
        this.selectedIndexes[0] = this.selectedIndexes[0] - this.optionsArray.deleteCount + this.optionsArray.addLength
      }
      if (this.selectedIndexes[0] > buttonsLength - 1) {
        this.selectedIndexes[0] = buttonsLength - 1
      }
    } else {
      // Single-select
      let saveIndexes = this.selectedIndexes
      for (let i = 0; i < this.optionsArray.deleteCount; i++) {
        let deleteIndex = saveIndexes.indexOf(this.optionsArray.changeStartIndex)
        let indexes = saveIndexes.map(value => value > this.optionsArray.changeStartIndex ? value - 1 : value)
        if (deleteIndex !== -1) {
          indexes.splice(deleteIndex, 1)
        }
        saveIndexes = indexes
      }
      for (let i = 0; i < this.optionsArray.addLength; i++) {
        let indexes = saveIndexes.map(value => value >= this.optionsArray.changeStartIndex ? value + 1 : value)
        saveIndexes = indexes
      }
      this.selectedIndexes = saveIndexes
    }
  }

  changeFocusIndex(buttonsLength: number) {
    if (this.focusIndex === -1) {
      return
    }
    if (this.focusIndex < this.optionsArray.changeStartIndex) {
      return
    }
    if (this.focusIndex === this.optionsArray.changeStartIndex && this.optionsArray.changeStartIndex + this.optionsArray.deleteCount - this.optionsArray.addLength === this.optionsArray.length) {
      // Last item
      this.focusIndex = this.optionsArray.changeStartIndex - 1
      return
    }
    if (this.optionsArray.changeStartIndex + this.optionsArray.deleteCount > this.focusIndex) {
      this.focusIndex = this.optionsArray.changeStartIndex
    } else {
      this.focusIndex = this.focusIndex - this.optionsArray.deleteCount + this.optionsArray.addLength
    }
    if (this.focusIndex > buttonsLength - 1) {
      this.focusIndex = buttonsLength - 1
    }
  }

  optionsArrayChange() {
    let buttonsLength = Math.min(this.options.buttons.length, this.buttonItemsSize.length)
    if (this.optionsArray.changeStartIndex !== void 0 && this.optionsArray.deleteCount !== void 0 && this.optionsArray.addLength !== void 0) {
      this.changeSelectedIndexes(buttonsLength)
      this.changeFocusIndex(buttonsLength)
      this.optionsArray.changeStartIndex = void 0
      this.optionsArray.deleteCount = void 0
      this.optionsArray.addLength = void 0
    }
  }

  aboutToAppear() {
    for (let index = 0; index < this.buttonItemsRealHeight.length; index++) {
      this.buttonItemsRealHeight[index] = 0
    }
  }

  @Builder focusStack(index: number) {
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
          .borderColor($r("sys.color.ohos_id_color_focused_outline"))
          .borderWidth(2)
      }
    }
    .size({ width: 1, height: 1 })
    .align(Alignment.Center)
  }

  calculateBorderRadius() {
    let borderRadiusArray: BorderRadiuses[] = Array.from({ length: MAX_ITEM_COUNT }, () => {
      return { topLeft: 0, topRight: 0, bottomLeft: 0, bottomRight: 0 }
    })
    for (let index = 0; index < this.buttonBorderRadius.length; index++) {
      let halfButtonItemsSizeHeight = this.buttonItemsSize[index].height as number / 2
      if (!this.options.multiply) {
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
        } else if (index === Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1) {
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
    if (this.optionsArray.length > 1) {
      Row({ space: 1 }) {
        ForEach(this.optionsArray, (item, index) => {
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
                  let maxHeight = Math.max(...this.buttonItemsRealHeight)
                  for (let index = 0; index < this.buttonItemsSize.length; index++) {
                    this.buttonItemsSize[index] = { width: this.buttonItemsSize[index].width, height: maxHeight }
                  }
                  this.calculateBorderRadius()
                })
            }
            .borderRadius(this.buttonBorderRadius[index])
            .scale({ x: this.options.type === 'capsule' && this.options.multiply ? 1 : this.zoomScaleArray[index],
              y: this.options.type === 'capsule' && this.options.multiply ? 1 : this.zoomScaleArray[index] })
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
                  this.hoverColorArray[index].hoverColor = ($r("sys.color.ohos_id_color_hover"))
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
  fontColor: ResourceColor = $r('sys.color.ohos_id_color_text_secondary')
  fontSize: Dimension = $r('sys.float.ohos_id_text_size_body2')
  fontWeight: FontWeight = FontWeight.Regular
  isSelected: boolean = false
}

@Component
export struct SegmentButton {
  @ObjectLink @Watch('optionsChange') options: SegmentButtonOptions
  @Link @Watch('selectedChange') selectedIndexes: number[]
  @Provide componentSize: SizeOptions = { width: 0, height: 0 }
  @Provide buttonBorderRadius: BorderRadiuses[] = Array.from({ length: MAX_ITEM_COUNT }, () => {
    return { topLeft: 0, topRight: 0, bottomLeft: 0, bottomRight: 0 }
  })
  @Provide buttonItemsSize: SizeOptions[] = Array.from({ length: MAX_ITEM_COUNT }, () => {
    return {}
  })
  @Provide @Watch('itemsPositionChange') buttonItemsPosition: Position[] = Array.from({
    length: MAX_ITEM_COUNT
  }, () => {
    return {}
  })
  @Provide buttonItemsSelected: boolean[] = Array.from({ length: MAX_ITEM_COUNT }, () => false)
  @Provide buttonItemProperty: ItemProperty[] = Array.from({ length: MAX_ITEM_COUNT }, () => new ItemProperty())
  @Provide focusIndex: number = -1
  @Provide selectedItemPosition: Position = {}
  @Provide zoomScaleArray: number[] = Array.from({ length: MAX_ITEM_COUNT }, () => 1.0)
  private doSelectedChangeAnimate: boolean = false
  private isCurrentPositionSelected: boolean = false

  itemsPositionChange() {
    if (this.doSelectedChangeAnimate) {
      this.updateAnimatedProperty(this.getSelectedChangeCurve())
    } else {
      this.updateAnimatedProperty(null)
    }
  }

  setItemsSelected() {
    let itemsSelected: boolean[] = Array.from({ length: MAX_ITEM_COUNT }, () => false)
    if (this.options.multiply) {
      this.selectedIndexes.forEach(index => itemsSelected[index] = true)
    } else if (this.selectedIndexes[0] !== void 0) {
      itemsSelected[this.selectedIndexes[0]] = true
    }
    this.buttonItemsSelected = itemsSelected
  }

  optionsChange() {
    this.updateAnimatedProperty(null)
  }

  selectedChange() {
    this.setItemsSelected()
    if (this.doSelectedChangeAnimate) {
      this.updateAnimatedProperty(this.getSelectedChangeCurve())
    } else {
      this.updateAnimatedProperty(null)
    }
  }

  aboutToAppear() {
    if (this.options.type === 'tab' && this.selectedIndexes.length === 0) {
      this.selectedIndexes[0] = 0
      this.buttonItemsSelected[0] = true
    }
    this.setItemsSelected()
    this.updateAnimatedProperty(null)
  }

  build() {
    Stack() {
      if (this.options.type === 'capsule' && this.options.multiply) {
        MultiSelectBackground({
          optionsArray: this.options.buttons,
          options: this.options,
        })
      } else {
        Stack()
          .size(this.componentSize)
          .backgroundColor(this.options.backgroundColor)
          .borderRadius(this.options.iconTextBackgroundRadius ?? this.componentSize.height as number / 2)
          .foregroundBlurStyle(BlurStyle.BACKGROUND_THICK, { colorMode: ThemeColorMode.LIGHT })
      }
      Stack() {
        if (this.options.type === 'capsule' && this.options.multiply) {
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

      SegmentButtonItemArrayComponent({
        optionsArray: this.options.buttons,
        options: this.options,
        selectedIndexes: $selectedIndexes,
      })
    }
    .onFocus(() => {
      if (this.selectedIndexes.length === 0) {
        this.focusIndex = 0
        return
      }
      if (!this.options.multiply) {
        this.focusIndex = this.selectedIndexes[0]
      } else {
        this.focusIndex = Math.min(...this.selectedIndexes)
      }
    })
    .onBlur(() => {
      this.focusIndex = -1
    })
    .onKeyEvent((event: KeyEvent) => {
      if (event.type === KeyType.Down) {
        if ((event.keyCode === KeyCode.KEYCODE_DPAD_DOWN || event.keyCode === KeyCode.KEYCODE_DPAD_RIGHT) && this.focusIndex < (Math.min(this.options.buttons.length, this.buttonItemsSize.length) - 1)) {
          // Move to next
          this.focusIndex = this.focusIndex + 1
        }
        if ((event.keyCode === KeyCode.KEYCODE_DPAD_UP || event.keyCode === KeyCode.KEYCODE_DPAD_LEFT) && this.focusIndex > 0) {
          // Move to previous
          this.focusIndex = this.focusIndex - 1
        }
        if (event.keyCode === KeyCode.KEYCODE_SPACE) {
          if (this.options.multiply) {
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
            let fingerInfo = event.fingerList.find(value => {
              return value !== null
            })
            if (fingerInfo === void 0) {
              return
            }
            let selectedInfo = fingerInfo.localX
            for (let i = 0; i < Math.min(this.options.buttons.length, this.buttonItemsSize.length); i++) {
              selectedInfo = selectedInfo - (this.buttonItemsSize[i].width as number)
              if (selectedInfo >= 0) {
                continue
              }
              this.doSelectedChangeAnimate = true
              if (this.options.type === 'capsule' && this.options.multiply) {
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
            if (this.options.type === 'capsule' && this.options.multiply) {
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
            let fingerInfo = event.fingerList.find(value => {
              return value !== null
            })
            if (fingerInfo === void 0) {
              return
            }
            let selectedInfo = fingerInfo.localX
            for (let i = 0; i < Math.min(this.options.buttons.length, this.buttonItemsSize.length); i++) {
              selectedInfo = selectedInfo - (this.buttonItemsSize[i].width as number)
              if (selectedInfo < 0) {
                this.isCurrentPositionSelected = i === this.selectedIndexes[0] ? true : false
                break
              }
            }
          })
          .onActionUpdate((event: GestureEvent) => {
            if (this.options.type === 'capsule' && this.options.multiply) {
              // Non drag gesture in multi-select mode
              return
            }
            if (!this.isCurrentPositionSelected) {
              return
            }
            let fingerInfo = event.fingerList.find(value => {
              return value !== null
            })
            if (fingerInfo === void 0) {
              return
            }
            let selectedInfo = fingerInfo.localX
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
                this.zoomScaleArray[index] = 0.95
              } else {
                this.zoomScaleArray[index] = 1
              }
            })
          })
          .onActionEnd((_: GestureEvent) => {
            animateTo({ curve: curves.interpolatingSpring(10, 1, 410, 38) }, () => {
              this.zoomScaleArray[this.selectedIndexes[0]] = 1
            })
            this.isCurrentPositionSelected = false
          })
      )
    )
  }

  getSelectedChangeCurve(): ICurve | null {
    if (this.options.type === 'capsule' && this.options.multiply) {
      return null
    }
    return curves.springMotion(0.347, 0.99)
  }

  updateAnimatedProperty(curve: ICurve) {
    let setAnimatedPropertyFunc = () => {
      this.selectedItemPosition = this.selectedIndexes.length === 0 ? {
                                                                      } : this.buttonItemsPosition[this.selectedIndexes[0]]
      this.buttonItemsSelected.forEach((selected, index) => {
        this.buttonItemProperty[index].fontColor = selected ? this.options.selectedFontColor : this.options.fontColor
      })
    }
    if (curve) {
      animateTo({ curve: curve }, setAnimatedPropertyFunc)
    } else {
      setAnimatedPropertyFunc()
    }
    this.buttonItemsSelected.forEach((selected, index) => {
      this.buttonItemProperty[index].fontSize = selected ? this.options.selectedFontSize : this.options.fontSize
      this.buttonItemProperty[index].fontWeight = selected ? this.options.selectedFontWeight : this.options.fontWeight
      this.buttonItemProperty[index].isSelected = selected
    })
  }
}