/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import {
  Entry,
  Resource,
  ResourceColor,
  Length,
  BorderRadiuses,
  LocalizedBorderRadiuses,
  ResourceStr,
  PX,
  VP,
  FP,
  LPX,
  FontWeight,
  SizeOptions,
  ButtonOptions,
  Padding,
  Dimension,
  LocalizedPadding,
  BlurStyle,
  Direction,
  Row,
  ForEach,
  Stack,
  LocalizedEdges,
  ShadowStyle,
  Color,
  Column,
  Image,
  Text,
  TextOverflow,
  MarqueeStartPolicy,
  TextAlign,
  FocusPriority,
  FlexAlign,
  Callback,
  Builder,
  Alignment,
  Button,
  CommonMethod,
  ButtonType,
  HoverEffect,
  TapGesture,
  TouchEvent,
  SourceType,
  TouchType,
  animateTo,
  Curve,
  MouseEvent,
  MouseAction,
  GestureEvent,
  KeyEvent,
  KeyType,
  GestureGroup,
  GestureMode,
  SwipeGesture,
  SourceTool,
  PanGesture,
  ICurve,
  Context,
  Component,
  $r,
  ColumnOptions,
  RowOptions,
  SizeChangeCallback,
  HoverEvent,
  OverlayOptions,
  CustomBuilder,
  Position
} from '@ohos.arkui.component';
import { Observed, ObjectLink, Consume, Link, Watch, State, Require, Provide, UIUtils } from '@ohos.arkui.stateManagement';

import curves from '@ohos.curves';
import { KeyCode } from '@ohos.multimodalInput.keyCode';
import util from '@ohos.util';
import { LengthMetrics } from '@ohos.arkui.node';
import I18n from '@ohos.i18n';

const MIN_ITEM_COUNT: int = 2;
const MAX_ITEM_COUNT: int = 5;
const DEFAULT_MAX_FONT_SCALE: number = 1.0;
const MAX_MAX_FONT_SCALE: number = 2.0;
const MIN_MAX_FONT_SCALE: number = 1.0;
const RESOURCE_TYPE_FLOAT: int = 10002;
const RESOURCE_TYPE_INTEGER: int = 10007;

interface SegmentButtonThemeInterface {
  SEGMENT_TEXT_VERTICAL_PADDING: Resource,
  SEGMENT_TEXT_HORIZONTAL_PADDING: Resource,
  SEGMENT_TEXT_CAPSULE_VERTICAL_PADDING: Resource,
  SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR: ResourceColor,
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
  x: number,
  y: number
}

function nearEqual(first: number, second: number): boolean {
  return Math.abs(first - second) < 0.001
}

export interface SegmentButtonTextItem {
  text: ResourceStr,
  accessibilityLevel?: string,
  accessibilityDescription?: ResourceStr
}

export interface SegmentButtonIconItem {
  icon: ResourceStr,
  iconAccessibilityText?: ResourceStr,
  selectedIcon: ResourceStr,
  selectedIconAccessibilityText?: ResourceStr,
  accessibilityLevel?: string,
  accessibilityDescription?: ResourceStr
}

export interface SegmentButtonIconTextItem {
  icon: ResourceStr,
  iconAccessibilityText?: ResourceStr,
  selectedIcon: ResourceStr,
  selectedIconAccessibilityText?: ResourceStr,
  text: ResourceStr,
  accessibilityLevel?: string,
  accessibilityDescription?: ResourceStr
}

type DimensionNoPercentage = PX | VP | FP | LPX | Resource

interface CommonSegmentButtonOptions {
  fontColor?: ResourceColor,
  selectedFontColor?: ResourceColor,
  fontSize?: DimensionNoPercentage,
  selectedFontSize?: DimensionNoPercentage,
  fontWeight?: FontWeight,
  selectedFontWeight?: FontWeight,
  backgroundColor?: ResourceColor,
  selectedBackgroundColor?: ResourceColor,
  imageSize?: SizeOptions,
  buttonPadding?: Padding | Dimension,
  textPadding?: Padding | Dimension,
  localizedTextPadding?: LocalizedPadding,
  localizedButtonPadding?: LocalizedPadding,
  backgroundBlurStyle?: BlurStyle,
  direction?: Direction
}
export type ItemRestriction<T> = Array<T>
export type SegmentButtonItemTuple = ItemRestriction<SegmentButtonTextItem> |
ItemRestriction<SegmentButtonIconItem> | ItemRestriction<SegmentButtonIconTextItem>

export interface TabSegmentButtonConstructionOptions extends CommonSegmentButtonOptions {
  buttons: ItemRestriction<SegmentButtonTextItem>
}

export interface CapsuleSegmentButtonConstructionOptions extends CommonSegmentButtonOptions {
  buttons: SegmentButtonItemTuple,
  multiply?: boolean
}

export interface TabSegmentButtonOptions extends TabSegmentButtonConstructionOptions {
  type: 'tab'
}

export interface CapsuleSegmentButtonOptions extends CapsuleSegmentButtonConstructionOptions {
  type: 'capsule'
}

interface SegmentButtonItemOptionsConstructorOptions {
  icon?: ResourceStr,
  iconAccessibilityText?: ResourceStr,
  selectedIcon?: ResourceStr,
  selectedIconAccessibilityText?: ResourceStr,
  text?: ResourceStr,
  accessibilityLevel?: string,
  accessibilityDescription?: ResourceStr
}

@Observed
export class SegmentButtonItemOptions {
  public icon?: ResourceStr;
  public iconAccessibilityText?: ResourceStr;
  public selectedIcon?: ResourceStr;
  public selectedIconAccessibilityText?: ResourceStr;
  public text?: ResourceStr;
  public accessibilityLevel?: string;
  public accessibilityDescription?: ResourceStr;

  constructor(options: SegmentButtonItemOptionsConstructorOptions) {
    this.icon = options.icon;
    this.selectedIcon = options.selectedIcon;
    this.text = options.text;
    this.iconAccessibilityText = options.iconAccessibilityText;
    this.selectedIconAccessibilityText = options.selectedIconAccessibilityText;
    this.accessibilityLevel = options.accessibilityLevel;
    this.accessibilityDescription = options.accessibilityDescription;
  }
}

@Observed
export class SegmentButtonItemOptionsArray extends Array<SegmentButtonItemOptions> {
  _wrappedArray: SegmentButtonItemOptions[] = UIUtils.makeObserved(new Array<SegmentButtonItemOptions>());

  public changeStartIndex: int | undefined = undefined;
  public deleteCount: int | undefined = undefined;
  public addLength: int | undefined = undefined;

  constructor(elementsOrLength: SegmentButtonItemTuple | number) {
    if (typeof elementsOrLength === 'number') {
      // 如果传入的是数字，创建指定长度的空数组
      for (let i = 0;i < elementsOrLength as number; i++) {
        this._wrappedArray.push(new SegmentButtonItemOptions({}))
      }
    } else if (Array.isArray(elementsOrLength)) {
      // 如果传入的是元素数组，添加元素
      const elements = elementsOrLength as Any as Array<Any>;
      elements.forEach((options: Any) => {
        if (options instanceof SegmentButtonTextItem) {
          this._wrappedArray.push(new SegmentButtonItemOptions({
            text: (options as SegmentButtonTextItem).text,
            accessibilityLevel: (options as SegmentButtonTextItem).accessibilityLevel,
            accessibilityDescription: (options as SegmentButtonTextItem).accessibilityDescription
          }));
        } else if (options instanceof SegmentButtonIconItem) {
          this._wrappedArray.push(new SegmentButtonItemOptions({
            icon: (options as SegmentButtonIconItem).icon,
            iconAccessibilityText: (options as SegmentButtonIconItem).iconAccessibilityText,
            selectedIcon: (options as SegmentButtonIconItem).selectedIcon,
            selectedIconAccessibilityText: (options as SegmentButtonIconItem).selectedIconAccessibilityText,
            accessibilityLevel: (options as SegmentButtonIconItem).accessibilityLevel,
            accessibilityDescription: (options as SegmentButtonIconItem).accessibilityDescription
          }));
        } else if (options instanceof SegmentButtonIconTextItem) {
          this._wrappedArray.push(new SegmentButtonItemOptions({
            icon: (options as SegmentButtonIconTextItem).icon,
            iconAccessibilityText: (options as SegmentButtonIconTextItem).iconAccessibilityText,
            selectedIcon: (options as SegmentButtonIconTextItem).selectedIcon,
            selectedIconAccessibilityText: (options as SegmentButtonIconTextItem).selectedIconAccessibilityText,
            text: (options as SegmentButtonIconTextItem).text,
            accessibilityLevel: (options as SegmentButtonIconTextItem).accessibilityLevel,
            accessibilityDescription: (options as SegmentButtonIconTextItem).accessibilityDescription
          }));
        }
      })
    }
  }
  get length(): int {
    return this._wrappedArray.length;
  }
  private createOptions(item:SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem): SegmentButtonItemOptions {
    if (item instanceof SegmentButtonTextItem) {
      return new SegmentButtonItemOptions({
        text:item.text,
        accessibilityLevel:item.accessibilityLevel,
        accessibilityDescription:item.accessibilityDescription
      })
    } else if (item instanceof SegmentButtonIconItem) {
      return new SegmentButtonItemOptions({
        icon:item.icon,
        iconAccessibilityText:item.iconAccessibilityText,
        selectedIcon:item.selectedIcon,
        selectedIconAccessibilityText:item.selectedIconAccessibilityText,
        accessibilityLevel:item.accessibilityLevel,
        accessibilityDescription:item.accessibilityDescription
      })
    } else if (item instanceof SegmentButtonIconTextItem) {
      return new SegmentButtonItemOptions({
        icon:item.icon,
        iconAccessibilityText:item.iconAccessibilityText,
        selectedIcon:item.selectedIcon,
        selectedIconAccessibilityText:item.selectedIconAccessibilityText,
        text:item.text,
        accessibilityLevel:item.accessibilityLevel,
        accessibilityDescription:item.accessibilityDescription
      })
    } else {
      throw new Error('Unsupported item type')
    }
  }
  push(item1: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem): int {
    if (this.length + 1 > MAX_ITEM_COUNT) {
      console.warn('Exceeded the maximum number of elements (5).');
      return this.length;
    }
    this.changeStartIndex = this.length;
    this.deleteCount = 0;
    this.addLength = 1;
    let option: SegmentButtonItemOptions = this.createOptions(item1);
    return this._wrappedArray.push(option).toInt();
  }
  push(item1: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem, item2: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem): int {
    if (this.length + 2 > MAX_ITEM_COUNT) {
      console.warn('Exceeded the maximum number of elements (5).');
      return this.length;
    }
    this.changeStartIndex = this.length;
    this.deleteCount = 0;
    this.addLength = 2;
    let option1: SegmentButtonItemOptions = this.createOptions(item1);
    let option2: SegmentButtonItemOptions = this.createOptions(item2);
    return this._wrappedArray.push(option1,option2).toInt();
  }
  push(item1: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem, item2: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem,item3: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem): int {
    if (this.length + 3 > MAX_ITEM_COUNT) {
      console.warn('Exceeded the maximum number of elements (5).');
      return this.length;
    }
    this.changeStartIndex = this.length;
    this.deleteCount = 0;
    this.addLength = 3;
    let option1: SegmentButtonItemOptions = this.createOptions(item1);
    let option2: SegmentButtonItemOptions = this.createOptions(item2);
    let option3: SegmentButtonItemOptions = this.createOptions(item3);
    return this._wrappedArray.push(option1,option2,option3).toInt();
  }

  pop(): SegmentButtonItemOptions | undefined {
    if (this.length <= MIN_ITEM_COUNT) {
      console.warn('Below the minimum number of elements (2).');
      return undefined;
    }
    this.changeStartIndex = this.length - 1;
    this.deleteCount = 1;
    this.addLength = 0;
    return this._wrappedArray.pop();
  }

  shift(): SegmentButtonItemOptions | undefined {
    if (this.length <= MIN_ITEM_COUNT) {
      console.warn('Below the minimum number of elements (2).');
      return undefined;
    }
    this.changeStartIndex = 0;
    this.deleteCount = 1;
    this.addLength = 0;
    return this._wrappedArray.shift();
  }

  unshift(item1: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem): int {
    if (this.length + 1 > MAX_ITEM_COUNT) {
      console.warn('Exceeded the maximum number of elements (5).');
      return this.length;
    }
    this.changeStartIndex = 0;
    this.deleteCount = 0;
    this.addLength = 1;

    let option: SegmentButtonItemOptions = this.createOptions(item1);
    return this._wrappedArray.unshift(option).toInt();
  }
  unshift(item1: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem,item2: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem): int {
    if (this.length + 2 > MAX_ITEM_COUNT) {
      console.warn('Exceeded the maximum number of elements (5).');
      return this.length;
    }
    this.changeStartIndex = 0;
    this.deleteCount = 0;
    this.addLength = 2;

    let option1: SegmentButtonItemOptions = this.createOptions(item1);
    let option2: SegmentButtonItemOptions = this.createOptions(item2);
    return this._wrappedArray.unshift(option1,option2).toInt();
  }
  unshift(item1: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem,item2: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem,item3: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem): int {
    if (this.length + 3 > MAX_ITEM_COUNT) {
      console.warn('Exceeded the maximum number of elements (5).');
      return this.length;
    }
    this.changeStartIndex = 0;
    this.deleteCount = 0;
    this.addLength = 3;

    let option1: SegmentButtonItemOptions = this.createOptions(item1);
    let option2: SegmentButtonItemOptions = this.createOptions(item2);
    let option3: SegmentButtonItemOptions = this.createOptions(item3);
    return this._wrappedArray.unshift(option1,option2,option3).toInt();
  }
  splice(start: int, deleteCount: int, ...items: SegmentButtonItemOptions[]): SegmentButtonItemOptions[] {
    let length: int = (this.length - deleteCount) < 0 ? 0 : (this.length - deleteCount);
    length += items.length;
    if (length < MIN_ITEM_COUNT) {
      console.warn('Below the minimum number of elements (2).');
      return [];
    }
    if (length > MAX_ITEM_COUNT) {
      console.warn('Exceeded the maximum number of elements (5).');
      return [];
    }
    this.changeStartIndex = start;
    this.deleteCount = deleteCount;
    this.addLength = items.length;
    return this._wrappedArray.splice(start.toDouble(), deleteCount.toDouble(), ...items);
  }

  static create(elements: SegmentButtonItemTuple): SegmentButtonItemOptionsArray {
    return new SegmentButtonItemOptionsArray(elements);
  }
}

@Observed
export class SegmentButtonOptions {
  public type: 'tab' | 'capsule' = 'tab';
  public multiply: boolean = false;
  public fontColor: ResourceColor = Color.Black;
  public selectedFontColor: ResourceColor = Color.Blue;
  public fontSize: DimensionNoPercentage = 16;
  public selectedFontSize: DimensionNoPercentage = 16;
  public fontWeight: FontWeight = FontWeight.Regular;
  public selectedFontWeight: FontWeight = FontWeight.Medium;
  public backgroundColor: ResourceColor = Color.White;
  public selectedBackgroundColor: ResourceColor = Color.Gray;
  public imageSize: SizeOptions = {} as SizeOptions;
  public buttonPadding: Padding | Dimension | undefined;
  public textPadding: Padding | Dimension | undefined;
  public componentPadding: Padding | Dimension = 0;
  public localizedTextPadding?: LocalizedPadding;
  public localizedButtonPadding?: LocalizedPadding;
  public showText: boolean = false;
  public showIcon: boolean = false;
  public iconTextRadius?: number;
  public iconTextBackgroundRadius?: number;
  public backgroundBlurStyle: BlurStyle = BlurStyle.Thick;
  public direction?: Direction;
  private _buttons: SegmentButtonItemOptionsArray | undefined = undefined;

  get buttons(): SegmentButtonItemOptionsArray | undefined {
    return this._buttons;
  }

  set buttons(val: SegmentButtonItemOptionsArray | undefined) {
    if (this._buttons !== undefined && this._buttons !== val) {
      this.onButtonsChange?.();
    }
    this._buttons = val;
  }

  public onButtonsChange?: () => void;

  constructor(options: TabSegmentButtonOptions | CapsuleSegmentButtonOptions) {
    this.fontColor = options.fontColor ?? segmentButtonTheme.FONT_COLOR;
    this.selectedFontColor = options.selectedFontColor ?? segmentButtonTheme.TAB_SELECTED_FONT_COLOR;
    this.fontSize = options.fontSize ?? segmentButtonTheme.FONT_SIZE;
    this.selectedFontSize = options.selectedFontSize ?? segmentButtonTheme.SELECTED_FONT_SIZE;
    this.fontWeight = options.fontWeight ?? FontWeight.Regular;
    this.selectedFontWeight = options.selectedFontWeight ?? FontWeight.Medium;
    this.backgroundColor = options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR;
    this.selectedBackgroundColor = options.selectedBackgroundColor ?? segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR;
    this.imageSize = options.imageSize ?? { width: 24.0, height: 24.0 } as SizeOptions;
    this.buttonPadding = options.buttonPadding;
    this.textPadding = options.textPadding;
    this.type = options instanceof TabSegmentButtonOptions ? (options as TabSegmentButtonOptions).type : (options as CapsuleSegmentButtonOptions).type;
    if (options.backgroundBlurStyle) {
      this.backgroundBlurStyle = options.backgroundBlurStyle as BlurStyle;
    } else {
      this.backgroundBlurStyle = BlurStyle.NONE;
    }
    this.localizedTextPadding = options.localizedTextPadding;
    this.localizedButtonPadding = options.localizedButtonPadding;
    this.direction = options.direction ?? Direction.Auto;
    this.buttons = new SegmentButtonItemOptionsArray(options instanceof TabSegmentButtonOptions ?
      (options as TabSegmentButtonOptions).buttons : (options as CapsuleSegmentButtonOptions).buttons)
    if (this.type === 'capsule') {
      this.multiply = (options as CapsuleSegmentButtonOptions).multiply ?? false;
      this.onButtonsUpdated();
      this.selectedFontColor = options.selectedFontColor ?? segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
      this.selectedBackgroundColor = options.selectedBackgroundColor ??
      segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
    } else {
      this.showText = true;
    }
    let themePadding: number = LengthMetrics.resource($r('sys.float.segment_button_baseplate_padding')).value;
    this.componentPadding = this.multiply ? 0.0 : themePadding;
  }

  public onButtonsUpdated() {
    this.buttons!._wrappedArray!.forEach(button => {
      this.showText = this.showText || !!button.text;
      this.showIcon = this.showIcon || !!button.icon || !!button.selectedIcon;
    });

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
    } as TabSegmentButtonOptions)
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
    } as CapsuleSegmentButtonOptions)
  }
}

@Component
struct MultiSelectBackground {
  @ObjectLink optionsArray: SegmentButtonItemOptionsArray
  @ObjectLink options: SegmentButtonOptions
  @Consume buttonBorderRadius: LocalizedBorderRadiuses[]
  @Consume buttonItemsSize: SizeOptions[]

  build() {
    Row({ space: 1.0 } as RowOptions) {
      ForEach(this.optionsArray._wrappedArray as Array<SegmentButtonItemOptions>, (_: SegmentButtonItemOptions, index: number) => {
        if (index < MAX_ITEM_COUNT) {
          Stack()
            .direction(this.options.direction)
            .layoutWeight(1.0)
            .height(this.buttonItemsSize[index as int].height)
            .backgroundColor(this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR)
            .borderRadius(this.buttonBorderRadius[index as int])
            .backgroundBlurStyle(this.options.backgroundBlurStyle, undefined, { disableSystemAdaptation: true })
            .id('MultiSelectBackground_Stack')
        }
      })
    }
    .id("MultiSelectBackground")
    .direction(this.options.direction)
    .padding(this.options.componentPadding)
  }
}

@Component
struct SelectItem {
  @ObjectLink optionsArray: SegmentButtonItemOptionsArray
  @ObjectLink options: SegmentButtonOptions
  @Link selectedIndexes: int[]
  @Consume buttonItemsSize: SizeOptions[]
  @Consume selectedItemPosition: LocalizedEdges
  @Consume zoomScaleArray: number[]
  @Consume buttonBorderRadius: LocalizedBorderRadiuses[]

  build() {
    if (this.selectedIndexes !== undefined && this.selectedIndexes.length > 0) {
      Stack()
        .id("SelectItem")
        .direction(this.options.direction)
        .borderRadius(this.buttonBorderRadius[this.selectedIndexes[0]])
        .size(this.buttonItemsSize[this.selectedIndexes[0]])
        .backgroundColor(this.options.selectedBackgroundColor ??
          (this.options.type === 'tab' ? segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR :
            segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR))
        .position(this.selectedItemPosition)
        .scale({
          x: this.zoomScaleArray[this.selectedIndexes[0]],
          y: this.zoomScaleArray[this.selectedIndexes[0]]
        })
        .shadow(numberToShadowStyle(resourceToNumber(this.getUIContext()?.getHostContext(),
          segmentButtonTheme.SEGMENT_BUTTON_SHADOW,
          0)))
    }
  }

}

@Component
struct MultiSelectItemArray {
  @ObjectLink optionsArray: SegmentButtonItemOptionsArray;
  @ObjectLink @Watch('onOptionsChange') options: SegmentButtonOptions;
  @Link @Watch('onSelectedChange') selectedIndexes: int[];
  @Consume buttonItemsSize: SizeOptions[];
  @Consume zoomScaleArray: number[];
  @Consume buttonBorderRadius: LocalizedBorderRadiuses[];
  @State multiColor: ResourceColor[] = new Array<ResourceColor>(MAX_ITEM_COUNT).fill(Color.Transparent as ResourceColor);

  onOptionsChange(a: string) {
    for (let i: number = 0.0; i < this.selectedIndexes.length; i++) {
      const selectedIndex = this.selectedIndexes[i as int] as int;
      if (selectedIndex >= 0 && selectedIndex < this.multiColor.length) {
        this.multiColor[selectedIndex] = this.options.selectedBackgroundColor ??
        segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
      }
    }
  }

  onSelectedChange(a: string) {
    for (let i: number = 0.0; i < MAX_ITEM_COUNT; i++) {
      this.multiColor[i as int] = Color.Transparent;
    }
    for (let i: number = 0.0; i < this.selectedIndexes.length; i++) {
      const selectedIndex = this.selectedIndexes[i as int] as int;
      if (selectedIndex >= 0 && selectedIndex < this.multiColor.length) {
        this.multiColor[selectedIndex] = this.options.selectedBackgroundColor ??
        segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
      }
    }
  }

  aboutToAppear() {
    for (let i: number = 0.0; i < this.selectedIndexes.length; i++) {
      const selectedIndex = this.selectedIndexes[i as int] as int;
      if (selectedIndex >= 0 && selectedIndex < this.multiColor.length) {
        this.multiColor[selectedIndex] = this.options.selectedBackgroundColor ??
        segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
      }
    }
  }

  build() {
    Row({ space: 1.0 } as RowOptions) {
      ForEach(this.optionsArray._wrappedArray as Array<SegmentButtonItemOptions>, (_: SegmentButtonItemOptions, index: number) => {
        if (index < MAX_ITEM_COUNT) {
          Stack()
            .direction(this.options.direction)
            .width(this.buttonItemsSize[index as int].width)
            .height(this.buttonItemsSize[index as int].height)
            .backgroundColor(this.multiColor[index as int])
            .borderRadius(this.buttonBorderRadius[index as int])
        }
      })
    }
    .id("MultiSelectItemArray")
    .direction(this.options.direction)
    .padding(this.options.componentPadding)
  }
}

@Component
struct SegmentButtonItem {
  @Link selectedIndexes: int[];
  @Link @Watch('onFocusIndex') focusIndex: int;
  @State @Require maxFontScale: number | Resource = 0.0;
  @ObjectLink itemOptions: SegmentButtonItemOptions;
  @ObjectLink options: SegmentButtonOptions;
  @ObjectLink property: ItemProperty;
  @State index: int = 0;
  @State isTextSupportMarquee: boolean =
    resourceToNumber(this.getUIContext()?.getHostContext(), segmentButtonTheme.SEGMENT_ITEM_TEXT_OVERFLOW, 1) === 0;
  @State isMarqueeAndFadeout: boolean = false;
  @State isSegmentFocusStyleCustomized: boolean = false;
  @State isTextInMarqueeCondition: boolean = false;
  @State isButtonTextFadeout?: boolean = false;
  private groupId: string = '';
  @State @Watch('onFocusIndex') hover: boolean = false;
  @Consume buttonItemsSize: SizeOptions[];
  @Consume buttonItemsPosition: LocalizedEdges[];
  @Link buttonItemsRealHeight: number[];

  public onCalculateBorderRadius?: () => void
  private getTextPadding(): Padding | Dimension | LocalizedPadding {
    if (this.options.localizedTextPadding) {
      return this.options.localizedTextPadding as LocalizedPadding;
    }
    if (this.options.textPadding !== undefined) {
      return this.options.textPadding as Padding;
    }
    return 0.0;
  }

  private getButtonPadding(): Padding | Dimension | LocalizedPadding {
    if (this.options.localizedButtonPadding) {
      return this.options.localizedButtonPadding as LocalizedPadding;
    }
    if (this.options.buttonPadding !== undefined) {
      return this.options.buttonPadding as Padding;
    }
    if (this.options.type === 'capsule' && this.options.showText && this.options.showIcon) {
      return {
        top: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_CAPSULE_VERTICAL_PADDING),
        bottom: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_CAPSULE_VERTICAL_PADDING),
        start: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_HORIZONTAL_PADDING),
        end: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_HORIZONTAL_PADDING)
      };
    }
    return {
      top: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_VERTICAL_PADDING),
      bottom: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_VERTICAL_PADDING),
      start: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_HORIZONTAL_PADDING),
      end: LengthMetrics.resource(segmentButtonTheme.SEGMENT_TEXT_HORIZONTAL_PADDING)
    };
  }

  onFocusIndex(a: string): void {
    this.isTextInMarqueeCondition =
      this.isSegmentFocusStyleCustomized && (this.focusIndex === this.index || this.hover);
  }

  aboutToAppear(): void {
    this.isButtonTextFadeout = this.isSegmentFocusStyleCustomized;
  }

  isDefaultSelectedFontColor(): boolean {
    const isDefaultTab = this.options.type === 'tab' && this.options.selectedFontColor === segmentButtonTheme.TAB_SELECTED_FONT_COLOR;
    const isDefaultCapsule = this.options.type === 'capsule' && this.options.selectedFontColor === segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
    const result = isDefaultTab || isDefaultCapsule;

    return result;
  }

  private getFontColor(): ResourceColor {
    if (this.property.isSelected) {
      if (this.isDefaultSelectedFontColor() && this.isSegmentFocusStyleCustomized && this.focusIndex === this.index) {
        return segmentButtonTheme.SEGMENT_BUTTON_FOCUS_TEXT_COLOR;
      }
      const selectedColor = this.options.selectedFontColor ?? segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
      return selectedColor;
    } else {
      // 未选中状态：检查是否需要应用焦点颜色
      if (this.options.fontColor === segmentButtonTheme.FONT_COLOR && this.isSegmentFocusStyleCustomized &&
        this.focusIndex === this.index) {
        return segmentButtonTheme.SEGMENT_BUTTON_FOCUS_TEXT_COLOR;
      }
      const normalColor = this.options.fontColor ?? segmentButtonTheme.FONT_COLOR;
      return normalColor;
    }
  }

  private getAccessibilityText(): Resource | undefined | string {
    if (this.selectedIndexes.includes(this.index) &&
      this.itemOptions.selectedIconAccessibilityText !== undefined) {
      return this.itemOptions.selectedIconAccessibilityText;
    } else if (!this.selectedIndexes.includes(this.index) &&
      this.itemOptions.iconAccessibilityText !== undefined) {
      return this.itemOptions.iconAccessibilityText;
    }
    return undefined;
  }

  build() {
    Column({ space: 2.0 } as ColumnOptions) {
      if (this.itemOptions.icon) {
        Image(this.property.isSelected ? this.itemOptions.selectedIcon as ResourceStr :
          this.itemOptions.icon as ResourceStr)
          .direction(this.options.direction)
          .size(this.options.imageSize ?? { width: 24.0, height: 24.0 } as SizeOptions)
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
          .minFontSize(this.isSegmentFocusStyleCustomized ? this.property.fontSize : 9.0)
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
    .id("SegmentButtonItem")
    .direction(this.options.direction)
    .focusScopePriority(this.groupId,
      Math.min(...this.selectedIndexes.map<double>(num=>num.toDouble())) === this.index ? FocusPriority.PREVIOUS : FocusPriority.AUTO)
    .justifyContent(FlexAlign.Center)
    .padding(this.getButtonPadding())
    .constraintSize({ minHeight: segmentButtonTheme.CONSTRAINT_SIZE_MIN_HEIGHT })
    .onSizeChange((_: SizeOptions, newValue: SizeOptions) => {
      // Calculate height of items
      this.buttonItemsRealHeight[this.index as int] = (newValue.height ?? 0) as number;
      let maxHeight: number = Math.max(...this.buttonItemsRealHeight.slice(0.0, this.options.buttons ?
        this!.options!.buttons!.length : 0.0));
      for (let index: number = 0.0; index < this.buttonItemsSize.length; index++) {
        const currentWidth = (this.buttonItemsSize[index as int].width ?? 0.0) as number;
        const currentHeight = (this.buttonItemsSize[index as int].height ?? 0.0) as number;
        this.buttonItemsSize[index as int] = { width: currentWidth, height: maxHeight };
      }
      this.onCalculateBorderRadius?.();
    } as SizeChangeCallback)
  }
}

@Observed
class HoverColorProperty {
  public hoverColor: ResourceColor = Color.Transparent
}

@Component
struct PressAndHoverEffect {
  @Consume buttonItemsSize: SizeOptions[]
  @State press: boolean = false;
  @State hover: boolean = false;
  @ObjectLink colorProperty: HoverColorProperty
  @Consume buttonBorderRadius: LocalizedBorderRadiuses[]
  @ObjectLink options: SegmentButtonOptions;
  pressIndex: number = 0.0
  pressColor: ResourceColor = segmentButtonTheme.PRESS_COLOR

  build() {
    Stack()
      .id("PressAndHoverEffect")
      .direction(this.options.direction)
      .size(this.buttonItemsSize[this.pressIndex as int])
      .backgroundColor(this.press && this.hover ? this.pressColor : this.colorProperty.hoverColor)
      .borderRadius(this.buttonBorderRadius[this.pressIndex as int])
  }
}

@Component
struct PressAndHoverEffectArray {
  @ObjectLink buttons: SegmentButtonItemOptionsArray
  @ObjectLink options: SegmentButtonOptions
  @Link pressArray: boolean[]
  @Link hoverArray: boolean[]
  @Link hoverColorArray: HoverColorProperty[]
  @Consume zoomScaleArray: number[]

  build() {
    Row({ space: 1.0 } as RowOptions) {
      ForEach(this.buttons._wrappedArray as Array<SegmentButtonItemOptions>, (item: SegmentButtonItemOptions, index: number) => {
        if (index < MAX_ITEM_COUNT) {
          Stack() {
            PressAndHoverEffect({
              pressIndex: index,
              colorProperty: this.hoverColorArray[index as int],
              press: this.pressArray[index as int],
              hover: this.hoverArray[index as int],
              options: this.options,
            })
          }
          .id("PressAndHoverEffectArray_Stack")
          .direction(this.options.direction)
          .scale({
            x: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1.0 :
              this.zoomScaleArray[index as int],
            y: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1.0 :
              this.zoomScaleArray[index as int]
          })
        }
      })
    }
    .id("PressAndHoverEffectArray")
    .direction(this.options.direction)
  }
}

@Component
struct SegmentButtonItemArrayComponent {
  @ObjectLink @Watch('onOptionsArrayChange') optionsArray: SegmentButtonItemOptionsArray;
  @ObjectLink @Watch('onOptionsChange') options: SegmentButtonOptions;
  @Link selectedIndexes: int[];
  @Consume componentSize: SizeOptions;
  @Consume buttonBorderRadius: LocalizedBorderRadiuses[];
  @Consume @Watch('onButtonItemsSizeChange') buttonItemsSize: SizeOptions[];
  @Consume buttonItemsPosition: LocalizedEdges[];
  @Consume @Watch('onFocusIndex') focusIndex: int;
  @Consume zoomScaleArray: number[];
  @Consume buttonItemProperty: ItemProperty[];
  @Consume buttonItemsSelected: boolean[];
  @Link pressArray: boolean[];
  @Link hoverArray: boolean[];
  @Link hoverColorArray: HoverColorProperty[];
  @State @Require maxFontScale: number | Resource = 0.0;
  @State buttonWidth: number[] = new Array<number>(MAX_ITEM_COUNT).fill(0);
  @State buttonHeight: number[] = new Array<number>(MAX_ITEM_COUNT).fill(0);
  @State isMarqueeAndFadeout: boolean = false;
  @State buttonItemsRealHeight: number[] = new Array<number>(MAX_ITEM_COUNT).fill(0);
  private groupId: string = util.generateRandomUUID(true);
  public onItemClicked?: Callback<int>;
  @State isSegmentFocusStyleCustomized: boolean = false;

  onButtonItemsSizeChange(a: string) {
    this.buttonItemsSize.forEach((value, index) => {
      this.buttonWidth[index as int] = (value.width ?? 0.0) as number;
      this.buttonHeight[index as int] = (value.height ?? 0.0) as number;
    })
  }

  changeSelectedIndexes(buttonsLength: number) {
    if (this.optionsArray.changeStartIndex === undefined || this.optionsArray.deleteCount === undefined ||
      this.optionsArray.addLength === undefined) {
      return;
    }
    if (!(this.options.multiply ?? false)) {
      // Single-select
      if (this.selectedIndexes.length === 0 || this.selectedIndexes[0] === undefined) {
        return;
      }
      if (this.selectedIndexes[0] < this.optionsArray.changeStartIndex as int) {
        return;
      }
      if (this.optionsArray.changeStartIndex as int + this.optionsArray.deleteCount as int >
      this.selectedIndexes[0]) {
        if (this.options.type === 'tab') {
          this.selectedIndexes[0] = 0;
        } else if (this.options.type === 'capsule') {
          this.selectedIndexes = [];
        }
      } else {
        const oldIndex = this.selectedIndexes[0];
        this.selectedIndexes[0] =
          this.selectedIndexes[0] - (this.optionsArray.deleteCount as int) + (this.optionsArray.addLength as int);
      }
    } else {
      // Multi-select
      let saveIndexes: int[] = this.selectedIndexes;
      for (let i: int = 0; i < this.optionsArray.deleteCount as int; i++) {
        let deleteIndex: int = saveIndexes.indexOf(this.optionsArray.changeStartIndex as int, 0);
        let indexes: int[] = saveIndexes.map<int>(value => (this.optionsArray.changeStartIndex) &&
          (value > this.optionsArray.changeStartIndex as int) ? value - 1 : value);
        if (deleteIndex !== -1) {
          indexes.splice(deleteIndex, 1);
        }
        saveIndexes = indexes;
      }
      for (let i: int = 0; i < this.optionsArray.addLength as int; i++) {
        let indexes: int[] = saveIndexes.map<int>(value => (this.optionsArray.changeStartIndex as int) &&
          (value >= this.optionsArray.changeStartIndex as int) ? value + 1 : value);
        saveIndexes = indexes;
      }
      this.selectedIndexes = saveIndexes;
    }

  }

  changeFocusIndex(buttonsLength: number) {
    if (this.optionsArray.changeStartIndex === undefined || this.optionsArray.deleteCount === undefined ||
      this.optionsArray.addLength === undefined) {
      return;
    }
    if (this.focusIndex === -1) {
      return;
    }
    if (this.focusIndex < this.optionsArray.changeStartIndex as int) {
      return;
    }
    if (this.optionsArray.changeStartIndex as int + this.optionsArray.deleteCount as int > this.focusIndex) {
      this.focusIndex = 0;
    } else {
      this.focusIndex =
        this.focusIndex - (this.optionsArray.deleteCount as int) + (this.optionsArray.addLength as int);
    }

  }

  onOptionsArrayChange(a: string) {
    if (this.options === undefined || this.options.buttons === undefined) {
      return;
    }
    let buttonsLength: number =
      Math.min(this!.options!.buttons!.length as number, this!.buttonItemsSize!.length as number)
    if (this.optionsArray.changeStartIndex !== undefined && this.optionsArray.deleteCount !== undefined &&
      this.optionsArray.addLength !== undefined) {
      this.changeSelectedIndexes(buttonsLength);
      this.changeFocusIndex(buttonsLength);
      this.optionsArray.changeStartIndex = undefined;
      this.optionsArray.deleteCount = undefined;
      this.optionsArray.addLength = undefined;
    }
  }

  onOptionsChange(a: string) {
    if (this.options === undefined || this.options.buttons === undefined) {
      return;
    }
    this.calculateBorderRadius();
  }

  onFocusIndex(a: string): void {
    this.isMarqueeAndFadeout = this.isSegmentFocusStyleCustomized && !this.isMarqueeAndFadeout;
  }

  aboutToAppear() {
    for (let index: number = 0.0; index < this.buttonItemsRealHeight.length; index++) {
      this.buttonItemsRealHeight[index as int] = 0.0;
    }
  }

  private getBorderRadius(index: number): LocalizedBorderRadiuses {
    let borderRadius: LocalizedBorderRadiuses = this.buttonBorderRadius[index as int]
    if (this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex as int]) {
      return {
        topStart: LengthMetrics.vp((borderRadius.topStart?.value ?? 0.0) + 4.0),
        topEnd: LengthMetrics.vp((borderRadius.topEnd?.value ?? 0.0) + 4.0),
        bottomStart: LengthMetrics.vp((borderRadius.bottomStart?.value ?? 0.0) + 4.0),
        bottomEnd: LengthMetrics.vp((borderRadius.bottomEnd?.value ?? 0.0) + 4.0)
      };
    }
    return borderRadius;
  }

  @Builder
  focusStack(index: number) {
    Stack() {
      Stack()
        .direction(this.options.direction)
        .borderRadius(this.getBorderRadius(index))
        .size({
          width: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex as int] ?
            this.buttonWidth[index as int] + 8.0 : this.buttonWidth[index as int],
          height: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex as int] ?
            this.buttonHeight[index as int] + 8.0 : this.buttonHeight[index as int]
        })
        .borderColor(segmentButtonTheme.FOCUS_BORDER_COLOR)
        .borderWidth(2.0)
    }
    .direction(this.options.direction)
    .size({ width: 1.0, height: 1.0 })
    .align(Alignment.Center)
  }

  calculateBorderRadius() {
    let borderRadiusArray: LocalizedBorderRadiuses[] = new Array<LocalizedBorderRadiuses>(MAX_ITEM_COUNT)
    for (let i = 0; i < MAX_ITEM_COUNT; i++) {
      borderRadiusArray[i] = {
        topStart: LengthMetrics.vp(0),
        topEnd: LengthMetrics.vp(0),
        bottomStart: LengthMetrics.vp(0),
        bottomEnd: LengthMetrics.vp(0)
      }
    }

    for (let index: int = 0; index < this.buttonBorderRadius.length; index++) {
      let halfButtonItemsSizeHeight: number = ((this.buttonItemsSize[index].height ?? 0) as number) / 2.0;

      if (this.options.type === 'tab' || !(this.options.multiply ?? false)) {
        borderRadiusArray[index].topStart =
          LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight);
        borderRadiusArray[index].topEnd =
          LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight);
        borderRadiusArray[index].bottomStart =
          LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight);
        borderRadiusArray[index].bottomEnd =
          LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight);
      } else {
        // Capsule多选模式
        const actualButtonsLength = this.options.buttons?.length ?? 0;
        const lastIndex = actualButtonsLength - 1;

        if (index === 0) {
          borderRadiusArray[index].topStart = LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight);
          borderRadiusArray[index].topEnd = LengthMetrics.vp(0.0);
          borderRadiusArray[index].bottomStart =
            LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight);
          borderRadiusArray[index].bottomEnd = LengthMetrics.vp(0.0);
        } else if (index === lastIndex) {
          borderRadiusArray[index].topStart = LengthMetrics.vp(0.0);
          borderRadiusArray[index].topEnd =
            LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight);
          borderRadiusArray[index].bottomStart = LengthMetrics.vp(0.0);
          borderRadiusArray[index].bottomEnd =
            LengthMetrics.vp(this.options.iconTextRadius ?? halfButtonItemsSizeHeight);
        } else {
          borderRadiusArray[index].topStart = LengthMetrics.vp(0.0);
          borderRadiusArray[index].topEnd = LengthMetrics.vp(0.0);
          borderRadiusArray[index].bottomStart = LengthMetrics.vp(0.0);
          borderRadiusArray[index].bottomEnd = LengthMetrics.vp(0.0);
        }
      }

    }
    this.buttonBorderRadius = borderRadiusArray;
  }

  getAccessibilityDescription(value?: ResourceStr): Resource | undefined | string {
    return (typeof value !== undefined) ? value  : undefined;
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
    if (this.optionsArray !== undefined && this.optionsArray._wrappedArray.length > 1.0) {
      Row({ space: 1.0 } as RowOptions) {
        ForEach(this.optionsArray._wrappedArray as Array<SegmentButtonItemOptions>,
          (item: SegmentButtonItemOptions, index: number) => {
            if (index < MAX_ITEM_COUNT) {
              Button({} as ButtonOptions) {
                SegmentButtonItem({
                  isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                  isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized,
                  selectedIndexes: this.selectedIndexes,
                  focusIndex: this.focusIndex,
                  index: index as int,
                  itemOptions: item,
                  options: this.options,
                  property: this.buttonItemProperty[index as int],
                  groupId: this.groupId,
                  maxFontScale: this.maxFontScale,
                  hover: this.hoverArray[index as int],
                  buttonItemsRealHeight: this.buttonItemsRealHeight,
                  onCalculateBorderRadius: () => {
                    this.calculateBorderRadius();
                  }
                })
              }
              .type(ButtonType.Normal)
              .stateEffect(false)
              .hoverEffect(HoverEffect.None)
              .backgroundColor(Color.Transparent)
              .accessibilityLevel(item.accessibilityLevel)
              .accessibilitySelected(this.options.multiply ? undefined : this.selectedIndexes.includes(index as int))
              .accessibilityChecked(this.options.multiply ? this.selectedIndexes.includes(index as int) : undefined)
              .accessibilityDescription(this.getAccessibilityDescription(item.accessibilityDescription))
              .direction(this.options.direction)
              .borderRadius(this.buttonBorderRadius[index as int])
              .scale({
                x: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1.0 :
                  this.zoomScaleArray[index as int],
                y: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1.0 :
                  this.zoomScaleArray[index as int]
              })
              .height(this.buttonItemsSize[index as int].height)
              .layoutWeight(1.0)
              .padding(0.0)
              .onSizeChange((_: SizeOptions, newValue: SizeOptions) => {
                this.buttonItemsSize[index as int] =
                  { width: newValue.width, height: this.buttonItemsSize[index as int].height };
                //measure position
                if (newValue.width) {
                  const componentPadding = Number.parseFloat(this.options.componentPadding.toString());
                  const buttonWidth = Number.parseFloat(newValue!.width!.toString());
                  const startPosition = componentPadding + (buttonWidth + 1.0) * index;
                  const topPosition = Math.floor(this.getUIContext().vp2px(componentPadding));

                  this.buttonItemsPosition[index as int] = {
                    start: LengthMetrics.vp(startPosition),
                    top: LengthMetrics.px(topPosition)
                  }

                }
              } as SizeChangeCallback)
              .stateStyles({
                normal: (instance: CommonMethod): void => {
                  instance.overlay(undefined);
                },
                focused: (instance: CommonMethod): void => {
                  instance.overlay(() => {
                    this.focusStack(index)
                  } as CustomBuilder, {
                    align: Alignment.Center
                  } as OverlayOptions);
                }
              })
              .onFocus(() => {
                this.focusIndex = index as int;
                if (this.isSegmentFocusStyleCustomized) {
                  this.customizeSegmentFocusStyle(index);
                }
              })
              .onBlur(() => {
                this.focusIndex = -1;
                this.hoverColorArray[index as int].hoverColor = Color.Transparent;
              })
              .gesture(TapGesture().onAction(() => {
                if (this.onItemClicked) {
                  this.onItemClicked?.(index as int);
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                  const currentIndex = this.selectedIndexes.indexOf(index as int);
                  if (currentIndex === -1.0) {
                    this.selectedIndexes.push(index.toInt());
                  } else {
                    this.selectedIndexes.splice(currentIndex.toInt(), 1)
                  }
                } else {
                  this.selectedIndexes[0] = index.toInt();
                }
              }))
              .onTouch((event: TouchEvent) => {
                if (this.isSegmentFocusStyleCustomized) {
                  this.getUIContext().getFocusController().clearFocus();
                }
                if (event.source !== SourceType.TouchScreen) {
                  return;
                }
                if (event.type === TouchType.Down) {
                  animateTo({ curve: curves.interpolatingSpring(10.0, 1.0, 410.0, 38.0) as ICurve }, () => {
                    this.zoomScaleArray[index as int] = 0.95;
                  })
                } else if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                  animateTo({ curve: curves.interpolatingSpring(10.0, 1.0, 410.0, 38.0) as ICurve}, () => {
                    this.zoomScaleArray[index as int] = 1.0;
                  })
                } else {
                }
              })
              .onHover((isHover: boolean, event: HoverEvent) => {
                this.hoverArray[index as int] = isHover
                if (isHover) {
                  animateTo({ duration: 250.0, curve: Curve.Friction }, () => {
                    this.hoverColorArray[index as int].hoverColor =
                      this.isSegmentFocusStyleCustomized && this.focusIndex === index ?
                        segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR : segmentButtonTheme.HOVER_COLOR;
                  })
                } else {
                  animateTo({ duration: 250.0, curve: Curve.Friction }, () => {
                    this.hoverColorArray[index as int].hoverColor =
                      this.isSegmentFocusStyleCustomized && this.focusIndex === index ?
                        segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR : Color.Transparent;
                  })
                }
              })
              .onMouse((event: MouseEvent) => {
                switch (event.action) {
                  case MouseAction.Press:
                    animateTo({ curve: curves.springMotion(0.347, 0.99) as ICurve }, () => {
                      this.zoomScaleArray[index as int] = 0.95;
                    })
                    animateTo({ duration: 100.0, curve: Curve.Sharp }, () => {
                      this.pressArray[index as int] = true;
                    })
                    break;
                  case MouseAction.Release:
                    animateTo({ curve: curves.springMotion(0.347, 0.99) as ICurve }, () => {
                      this.zoomScaleArray[index as int] = 1.0;
                    })
                    animateTo({ duration: 100.0, curve: Curve.Sharp }, () => {
                      this.pressArray[index as int] = false;
                    })
                    break;
                }
              })
            }
          },(item:SegmentButtonItemOptions,index:number)=>JSON.stringify(item) + index)
      }
      .id("SegmentButtonItemArrayComponent")
      .direction(this.options.direction)
      .focusScopeId(this.groupId, true)
      .padding(this.options.componentPadding)
      .onSizeChange((_: SizeOptions, newValue: SizeOptions) => {
        this.componentSize = { width: newValue.width, height: newValue.height }
      } as SizeChangeCallback)
    }
  }

  /**
   * 设置segmentbutton获焦时的样式
   * @param index
   */
  private customizeSegmentFocusStyle(index: number) {
    if (this.selectedIndexes !== undefined && this.selectedIndexes.length !== 0.0 &&
      this.selectedIndexes[0] === index) { // 选中态
      this.hoverColorArray[index as int].hoverColor = this.isDefaultSelectedBgColor() ?
        segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR : this.options.selectedBackgroundColor;
    } else { // 未选中态
      this.hoverColorArray[index as int].hoverColor =
        this.options.backgroundColor === segmentButtonTheme.BACKGROUND_COLOR ?
          segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR : this.options.backgroundColor;
    }
  }
}

@Observed
class ItemProperty {
  public fontColor: ResourceColor = segmentButtonTheme.FONT_COLOR;
  public fontSize: DimensionNoPercentage = segmentButtonTheme.FONT_SIZE;
  public fontWeight: FontWeight = FontWeight.Regular;
  public isSelected: boolean = false;
}

@Component
export struct SegmentButton {
  @ObjectLink @Watch('onOptionsChange') options: SegmentButtonOptions
  @Link @Watch('onSelectedChange') selectedIndexes: int[]
  public onItemClicked?: Callback<int>
  @State maxFontScale: number | Resource = DEFAULT_MAX_FONT_SCALE
  @Provide componentSize: SizeOptions = { width: 0.0, height: 0.0 } as SizeOptions
  @Provide buttonBorderRadius: LocalizedBorderRadiuses[] = (() => {
    let array = new Array<LocalizedBorderRadiuses>(MAX_ITEM_COUNT)
    for (let i = 0; i < MAX_ITEM_COUNT; i++) {
      array[i] = {
        topStart: LengthMetrics.vp(0),
        topEnd: LengthMetrics.vp(0),
        bottomStart: LengthMetrics.vp(0),
        bottomEnd: LengthMetrics.vp(0)
      };
    }
    return array;
  })()
  @Provide buttonItemsSize: SizeOptions[] = (() => {
    let arr: SizeOptions[] = [];
    for (let i = 0; i < MAX_ITEM_COUNT; i++) {
      arr.push({});
    }
    return arr;
  })()
  @Provide @Watch('onItemsPositionChange') buttonItemsPosition: LocalizedEdges[] = (() => {
    let array = new Array<LocalizedEdges>(MAX_ITEM_COUNT)
    for (let i = 0; i < MAX_ITEM_COUNT; i++) {
      array[i] = {};
    }
    return array;
  })()
  @Provide buttonItemsSelected: boolean[] = new Array<boolean>(MAX_ITEM_COUNT).fill(false);
  @Provide buttonItemProperty: ItemProperty[] = (() => {
    let array = new Array<ItemProperty>(MAX_ITEM_COUNT)
    for (let i = 0; i < MAX_ITEM_COUNT; i++) {
      array[i] = new ItemProperty();
    }
    return array;
  })()
  @Provide focusIndex: int = -1;
  @Provide selectedItemPosition: LocalizedEdges = {} as LocalizedEdges;
  @Provide zoomScaleArray: number[] = Array<number>(MAX_ITEM_COUNT).fill(1.0);
  @State pressArray: boolean[] = new Array<boolean>(MAX_ITEM_COUNT).fill(false);
  @State hoverArray: boolean[] = new Array<boolean>(MAX_ITEM_COUNT).fill(false);
  @State hoverColorArray: HoverColorProperty[] = (() => {
    let arr: HoverColorProperty[] = [];
    for (let i = 0; i < MAX_ITEM_COUNT; i++) {
      arr.push(new HoverColorProperty());
    }
    return arr;
  })()
  private doSelectedChangeAnimate: boolean = false;
  private isCurrentPositionSelected: boolean = false;
  private panGestureStartPoint: Point = { x: 0.0, y: 0.0 } as Point;
  private isPanGestureMoved: boolean = false;
  @State shouldMirror: boolean = false;
  private isSegmentFocusStyleCustomized: boolean =
    resourceToNumber(this.getUIContext()?.getHostContext(), segmentButtonTheme.SEGMENT_FOCUS_STYLE_CUSTOMIZED, 1) === 0;
  private isGestureInProgress: boolean = false;

  onItemsPositionChange(a: string) {
    if (this.options === undefined || this.options.buttons === undefined) {
      return;
    }
    if (this.options.type === 'capsule') {
      this.options.onButtonsUpdated();
    }
    if (this.doSelectedChangeAnimate) {
      this.updateAnimatedProperty(this.getSelectedChangeCurve());
    } else {
      this.updateAnimatedProperty(null);
    }
  }

  setItemsSelected() {
    this.buttonItemsSelected.forEach((_, index) => {
      this.buttonItemsSelected[index as int] = false;
    })
    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
      this.selectedIndexes.forEach((index)=> {
        this.buttonItemsSelected[index as int] = true;
      })
    } else {
      if(this.selectedIndexes.length !== 0) {
        this.buttonItemsSelected[this.selectedIndexes[0]] = true;
      }
    }
  }

  updateSelectedIndexes() {
    if (this.selectedIndexes === undefined) {
      this.selectedIndexes = [];
    }
    if (this.options.type === 'tab' && this.selectedIndexes.length === 0.0) {
      this.selectedIndexes[0] = 0;
    }
    if (this.selectedIndexes.length > 1.0) {
      if (this.options.type === 'tab') {
        this.selectedIndexes = [0];
      }
      if (this.options.type === 'capsule' && !(this.options.multiply ?? false)) {
        this.selectedIndexes = [];
      }
    }
    let invalid = this.selectedIndexes.some(index => {
      const buttons = this.options.buttons;
      const buttonLength = buttons ? buttons.length : 0;
      return index === undefined || index < 0 || index >= buttonLength;
    })
    if (invalid) {
      if (this.options.type === 'tab') {
        this.selectedIndexes = [0];
      } else {
        this.selectedIndexes = [];
      }
    }
  }

  onOptionsChange(a: string) {
    if (this.options === undefined || this.options.buttons === undefined) {
      return;
    }
    this.shouldMirror = this.isShouldMirror();
    this.updateSelectedIndexes();
    this.setItemsSelected();
    this.updateAnimatedProperty(null);
  }

  onSelectedChange(a: string) {
    if (this.options === undefined || this.options.buttons === undefined) {
      return;
    }
    this.updateSelectedIndexes();
    this.setItemsSelected();
    if (this.doSelectedChangeAnimate) {
      this.updateAnimatedProperty(this.getSelectedChangeCurve());
    } else {
      this.updateAnimatedProperty(null);
    }
  }

  aboutToAppear() {
    if (this.options === undefined || this.options.buttons === undefined) {
      return;
    }
    this.options.onButtonsChange = () => {
      if (this.options.type === 'tab') {
        this.selectedIndexes = [0];
      } else {
        this.selectedIndexes = [];
      }
    }
    this.shouldMirror = this.isShouldMirror();
    this.updateSelectedIndexes();
    this.setItemsSelected();
    this.updateAnimatedProperty(null);
  }

  private isMouseWheelScroll(event: GestureEvent) {
    return event.source === SourceType.Mouse && !this.isPanGestureMoved;
  }

  private isMovedFromPanGestureStartPoint(x: number, y: number) {
    return !nearEqual(x, this.panGestureStartPoint.x) || !nearEqual(y, this.panGestureStartPoint.y);
  }

  private isShouldMirror(): boolean {
    if (this.options.direction == Direction.Rtl) {
      return true;
    }
    // 获取系统语言
    try {
      let systemLanguage: string = I18n.System.getSystemLanguage();
      if (I18n.isRTL(systemLanguage) && this.options.direction != Direction.Ltr) {
        return true;
      }
    } catch (error) {
      console.error(`Ace SegmentButton getSystemLanguage, error: ${error.toString()}`);
    }
    return false;
  }

  build() {
    Stack() {
      if (this.options !== undefined && this.options.buttons !== undefined) {
        if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
          MultiSelectBackground({
            optionsArray: this.options.buttons,
            options: this.options,
          })
        } else {
          Stack() {
            if (this.options.buttons !== undefined && this!.options!.buttons!.length as number > 1.0) {
              PressAndHoverEffectArray({
                options: this.options,
                buttons: this.options.buttons,
                pressArray: this.pressArray,
                hoverArray: this.hoverArray,
                hoverColorArray: this.hoverColorArray
              })
            }
          }
          .id("SegmentButton_BackgroundStack")
          .direction(this.options.direction)
          .size(this.componentSize)
          .backgroundColor(this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR)
          .borderRadius(this.options.iconTextBackgroundRadius ?? ((this.componentSize.height ?? 0) as number) / 2.0)
          .backgroundBlurStyle(this.options.backgroundBlurStyle, undefined, { disableSystemAdaptation: true })
        }
        Stack() {
          if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            MultiSelectItemArray({
              optionsArray: this.options.buttons,
              options: this.options,
              selectedIndexes: this.selectedIndexes
            })
          } else {
            SelectItem({
              optionsArray: this.options.buttons,
              options: this.options,
              selectedIndexes: this.selectedIndexes
            })
          }
        }
        .id("SegmentButton_ItemStack")
        .direction(this.options.direction)
        .size(this.componentSize)
        .animation({ duration: 0.0 })
        .borderRadius((this.options.type === 'capsule' && (this.options.multiply ?? false) ?
          this.options.iconTextRadius : this.options.iconTextBackgroundRadius) ??
          ((this.componentSize.height ?? 0) as number) / 2.0)
        .clip(true)

        SegmentButtonItemArrayComponent({
          pressArray: this.pressArray,
          hoverArray: this.hoverArray,
          hoverColorArray: this.hoverColorArray,
          optionsArray: this.options.buttons,
          options: this.options,
          selectedIndexes: this.selectedIndexes,
          maxFontScale: this.getMaxFontSize(),
          onItemClicked: this.onItemClicked,
          isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized
        })
      }
    }
    .id("SegmentButton")
    .direction(this.options ? this.options.direction : undefined)
    .onBlur(() => {
      this.focusIndex = -1
    })
    .onKeyEvent((event: KeyEvent) => {
      if (!this.options || ! this.options.buttons){
        return false;
      }
      if (event.type === KeyType.Down) {
        if (event.keyCode === KeyCode.KEYCODE_SPACE || event.keyCode === KeyCode.KEYCODE_ENTER ||
          event.keyCode === KeyCode.KEYCODE_NUMPAD_ENTER) {
          if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            if (this.selectedIndexes.indexOf(this.focusIndex) === -1) {
              // Select
              this.selectedIndexes.push(this.focusIndex);
            } else {
              // Unselect
              this.selectedIndexes.splice(this.selectedIndexes.indexOf(this.focusIndex), 1);
            }
          } else {
            // Pressed
            this.selectedIndexes[0] = this.focusIndex;
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
            let fingerInfo = event.fingerList.find(f => Boolean(f))
            if (fingerInfo === undefined) {
              return;
            }
            if (this.options === undefined || this.options.buttons === undefined) {
              return;
            }
            let selectedInfo: number = fingerInfo!.localX ?? 0;

            let buttonLength: number = Math.min(this!.options!.buttons!.length as number, this!.buttonItemsSize!.length as number);

            // 安全检查
            if (!this.buttonItemsSize || buttonLength <= 0) {
              return;
            }

            for (let i = 0.0; i < buttonLength; i++) {
              // 添加安全检查
              if (i >= this.buttonItemsSize.length) {
                break;
              }

              let buttonSize = this.buttonItemsSize[i as int];
              if (!buttonSize) {
                break;
              }

              let buttonWidth = (buttonSize.width ?? 0) as number;

              selectedInfo = selectedInfo - buttonWidth
              if (selectedInfo >= 0.0) {
                continue;
              }

              // 安全检查：确保 selectedIndexes 不为空
              this.doSelectedChangeAnimate =
                (this.selectedIndexes.length > 0 && this.selectedIndexes[0] > Math.min(this!.options!.buttons!.length as number,
                  this!.buttonItemsSize!.length as number)) ? false : true;

              let realClickIndex: number = this.isShouldMirror() ? buttonLength - 1 - i : i;
              if (this.onItemClicked) {
                this.onItemClicked?.(realClickIndex.toInt());
              }
              if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {

                let selectedIndex: int = this.selectedIndexes.indexOf(realClickIndex as int, 0)
                if (selectedIndex === -1.0) {
                  this.selectedIndexes.push(realClickIndex.toInt());
                } else {
                  this.selectedIndexes = this.selectedIndexes.filter((_,index) =>index !== selectedIndex);
                }
              } else {
                // 单选模式，确保数组有足够的元素
                if (this.selectedIndexes.length === 0) {
                  this.selectedIndexes.push(realClickIndex.toInt());
                } else {
                  this.selectedIndexes[0] = realClickIndex.toInt();
                }
              }
              this.doSelectedChangeAnimate = false;
              break
            }
          }),
        SwipeGesture()
          .onAction((event: GestureEvent) => {
            if (this.options === undefined || this.options.buttons === undefined || event.sourceTool === SourceTool.TOUCHPAD) {
              return;
            }
            if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
              // Non swipe gesture in multi-select mode
              return;
            }
            if (this.isCurrentPositionSelected) {
              return;
            }
            if (Math.abs(event.angle) < 90.0 &&
              this.selectedIndexes[0] !== Math.min(this!.options!.buttons!.length as number,
                this.buttonItemsSize.length as number) - 1.0) {
              // Move to next
              this.doSelectedChangeAnimate = true;
              this.selectedIndexes[0] = this.selectedIndexes[0] + 1;
              this.doSelectedChangeAnimate = false;
            } else if (Math.abs(event.angle) > 90.0 && this.selectedIndexes[0] !== 0) {
              // Move to previous
              this.doSelectedChangeAnimate = true;
              this.selectedIndexes[0] = this.selectedIndexes[0] - 1;
              this.doSelectedChangeAnimate = false;
            } else {
            }
          }),
        PanGesture()
          .onActionStart((event: GestureEvent) => {
            this.isGestureInProgress = true;
            if (this.options === undefined|| this.options.buttons === undefined) {
              return;
            }
            if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
              // Non drag gesture in multi-select mode
              return;
            }
            let fingerInfo = event.fingerList.find(f => Boolean(f));
            if (fingerInfo === undefined) {
              return;
            }
            let selectedInfo: number = (fingerInfo?.localX ?? 0) as number;
            this.panGestureStartPoint = { x: (fingerInfo?.globalX ?? 0) as number, y: (fingerInfo?.globalY ?? 0) as number };
            this.isPanGestureMoved = false;
            for (let i: number = 0.0;
              i < Math.min(this!.options!.buttons!.length as number, this!.buttonItemsSize!.length as number); i++) {
              selectedInfo = selectedInfo - ((this.buttonItemsSize[i as int].width ?? 0) as number);
              if (selectedInfo < 0.0) {
                this.isCurrentPositionSelected = i === this.selectedIndexes[0] ? true : false;
                break;
              }
            }
          })
          .onActionUpdate((event: GestureEvent) => {
            if (this.options === undefined || this.options.buttons === undefined) {
              return;
            }
            if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
              // Non drag gesture in multi-select mode
              return;
            }
            if (!this.isCurrentPositionSelected) {
              return;
            }
            let fingerInfo = event.fingerList.find(f => Boolean(f))
            if (fingerInfo === undefined) {
              return;
            }
            let selectedInfo: number = fingerInfo!.localX ?? 0;
            if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(fingerInfo!.globalX ?? 0,
              fingerInfo!.globalY ?? 0)) {
              this.isPanGestureMoved = true;
            }
            for (let i: int = 0;
              i < Math.min(this!.options!.buttons!.length as number, this!.buttonItemsSize!.length as number); i++) {
              selectedInfo = selectedInfo - ((this.buttonItemsSize[i as int].width ?? 0) as number)
              if (selectedInfo < 0.0) {
                this.doSelectedChangeAnimate = true;
                this.selectedIndexes[0] = i;
                this.doSelectedChangeAnimate = false;
                break
              }
            }
            this.zoomScaleArray.forEach((_, index) => {
              if (index === this.selectedIndexes[0]) {
                animateTo({ curve: curves.interpolatingSpring(10.0, 1.0, 410.0, 38.0) as ICurve }, () => {
                  this.zoomScaleArray[index as int] = 0.95;
                });
              } else {
                animateTo({ curve: curves.interpolatingSpring(10.0, 1.0, 410.0, 38.0) as ICurve }, () => {
                  this.zoomScaleArray[index as int] = 1.0;
                });
              }
            })
          })
          .onActionEnd((event: GestureEvent) => {
            this.isGestureInProgress = false;
            if (this.options === undefined || this.options.buttons === undefined) {
              return;
            }
            if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
              // Non drag gesture in multi-select mode
              return;
            }
            let fingerInfo = event.fingerList.find(f => Boolean(f))
            if (fingerInfo === undefined) {
              return;
            }
            if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(fingerInfo!.globalX ?? 0,
              fingerInfo!.globalY ?? 0)) {
              this.isPanGestureMoved = true;
            }
            if (this.isMouseWheelScroll(event)) {
              let offset: number = event.offsetX !== 0.0 ? event.offsetX : event.offsetY
              this.doSelectedChangeAnimate = true;
              if (offset > 0.0 && this.selectedIndexes[0] > 0) {
                this.selectedIndexes[0] -= 1;
              } else if (offset < 0.0 && this.selectedIndexes[0] < Math.min(this!.options!.buttons!.length as number,
                this.buttonItemsSize.length as number) - 1.0) {
                this.selectedIndexes[0] += 1;
              } else {
              }
              this.doSelectedChangeAnimate = false
            }
            animateTo({ curve: curves.interpolatingSpring(10.0, 1.0, 410.0, 38.0) as ICurve }, () => {
              this.zoomScaleArray[this.selectedIndexes[0] as int] = 1.0;
            })
            this.isCurrentPositionSelected = false;
          })
          .onActionCancel(() => {
            this.isGestureInProgress = false;
            if (this.options === undefined || this.options.buttons === undefined) {
              return;
            }
            if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
              return;
            }
            animateTo({ curve: curves.interpolatingSpring(10.0, 1.0, 410.0, 38.0) as ICurve }, () => {
              this.zoomScaleArray[this.selectedIndexes[0] as int] = 1.0;
            })
            this.isCurrentPositionSelected = false;
          })
      )
    )
  }

  getMaxFontSize(): number {
    if (typeof this.maxFontScale === undefined) {
      return DEFAULT_MAX_FONT_SCALE;
    }
    if (typeof this.maxFontScale === 'number') {
      return Math.max(Math.min(this.maxFontScale as number, MAX_MAX_FONT_SCALE), MIN_MAX_FONT_SCALE);
    }
    const resourceManager = this.getUIContext().getHostContext()?.resourceManager;
    if (!resourceManager) {
      return DEFAULT_MAX_FONT_SCALE;
    }
    try {
      return resourceManager.getDouble((this.maxFontScale as Resource).id);
    } catch (error) {
      console.error(`Ace SegmentButton getMaxFontSize, error: ${error.toString()}`);
      return DEFAULT_MAX_FONT_SCALE;
    }
  }

  getSelectedChangeCurve(): ICurve | null {
    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
      return null;
    }
    return curves.springMotion(0.347, 0.99) as ICurve;
  }

  updateAnimatedProperty(curve: ICurve | null) {

    let setAnimatedPropertyFunc = () => {
      if (this.selectedIndexes.length === 0.0) {
        this.selectedItemPosition = {} as LocalizedEdges;
      } else {
        const selectedIndex = this.selectedIndexes[0] as int;
        this.selectedItemPosition = this.buttonItemsPosition[selectedIndex];
      }

      this.buttonItemsSelected.forEach((selected, index) => {
        const newColor = selected ?
          this.options.selectedFontColor ?? (this.options.type === 'tab' ?
            segmentButtonTheme.TAB_SELECTED_FONT_COLOR : segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR) :
          this.options.fontColor ?? segmentButtonTheme.FONT_COLOR;
        this.buttonItemProperty[index as int].fontColor = newColor;
      })
    }
    if (curve) {
      animateTo({ curve: curve }, setAnimatedPropertyFunc);
    } else {
      setAnimatedPropertyFunc();
    }

    this.buttonItemsSelected.forEach((selected, index) => {
      this.buttonItemProperty[index as int].fontSize = selected ? this.options.selectedFontSize ??
      segmentButtonTheme.SELECTED_FONT_SIZE : this.options.fontSize ?? segmentButtonTheme.FONT_SIZE;
      this.buttonItemProperty[index as int].fontWeight =
        selected ? this.options.selectedFontWeight ?? FontWeight.Medium :
          this.options.fontWeight ?? FontWeight.Regular;
      this.buttonItemProperty[index as int].isSelected = selected;
    })
  }
}

function resourceToNumber(context: Context | undefined, resource: Resource, defaultValue: int): int {
  if (!resource || !resource.type || !context) {
    console.error('[SegmentButton] failed: resource get fail.');
    return defaultValue;
  }
  let resourceManager = context?.resourceManager;
  if (!resourceManager) {
    console.error('[SegmentButton] failed to get resourceManager.');
    return defaultValue;
  }
  switch (resource!.type!.toInt()) {
    case RESOURCE_TYPE_FLOAT as int:
    case RESOURCE_TYPE_INTEGER as int:
      try {
        if (resource.id !== -1.0) {
          return resourceManager.getInt(resource.id);
        }
        return resourceManager.getIntByName((((resource.params!)[0]) as string).split('.')[2]);
      } catch (error) {
        console.error(`[SegmentButton] get resource error, return ${defaultValue}`);
        return defaultValue;
      }
    default:
      return defaultValue;
  }
}

function numberToShadowStyle(num: int): ShadowStyle {
  switch(num){
    case 0:
      return ShadowStyle.OUTER_DEFAULT_XS;
    case 1:
      return ShadowStyle.OUTER_DEFAULT_SM;
    case 2:
      return ShadowStyle.OUTER_DEFAULT_MD;
    case 3:
      return ShadowStyle.OUTER_DEFAULT_LG;
    case 4:
      return ShadowStyle.OUTER_FLOATING_SM;
    case 5:
      return ShadowStyle.OUTER_FLOATING_MD;
    default:
      return ShadowStyle.OUTER_DEFAULT_XS;
  }
}