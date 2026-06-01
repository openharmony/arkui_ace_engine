/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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
  PanDirection,
  ScaleOptions,
  LongPressGesture
} from '@ohos.arkui.component';
import {
  Observed,
  ObjectLink,
  Consume,
  Link,
  Watch,
  State,
  Require,
  Provide,
  UIUtils,
  PropRef
} from '@ohos.arkui.stateManagement';
import { EnvironmentCallback } from '@kit.AbilityKit';
import deviceInfo from '@ohos.deviceInfo';
import { Configuration } from '@ohos.app.ability.Configuration';
import AbilityConstant from '@ohos.app.ability.AbilityConstant';

import curves from '@ohos.curves';
import { KeyCode } from '@ohos.multimodalInput.keyCode';
import util from '@ohos.util';
import { LengthMetrics, LengthUnit, FrameNode, LayoutConstraint, Size, NodePosition } from '@ohos.arkui.node';
import I18n from '@ohos.i18n';
import uiMaterial from '@ohos.arkui.uiMaterial';
import { CustomLayoutAlgorithm } from '@ohos.arkui.layoutAlgorithm'
import { DynamicLayout } from '@ohos.arkui.components.ArkDynamicLayout'

const MIN_ITEM_COUNT: int = 2;
const MAX_ITEM_COUNT: int = 5;
const DEFAULT_MAX_FONT_SCALE: double = 1.0;
const MAX_MAX_FONT_SCALE: double = 2.0;
const MIN_MAX_FONT_SCALE: double = 1.0;
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
  ADAPTIVE_ITEM_FONT_SIZE: DimensionNoPercentage,
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
  SEGMENT_FOCUS_STYLE_CUSTOMIZED: Resource
}

const segmentButtonTheme: SegmentButtonThemeInterface = {
  FONT_COLOR: $r('sys.color.segment_button_unselected_text_color'),
  TAB_SELECTED_FONT_COLOR: $r('sys.color.segment_button_checked_text_color'),
  CAPSULE_SELECTED_FONT_COLOR: $r('sys.color.ohos_id_color_foreground_contrary'),
  FONT_SIZE: $r('sys.float.segment_button_unselected_text_size'),
  SELECTED_FONT_SIZE: $r('sys.float.segment_button_checked_text_size'),
  ADAPTIVE_ITEM_FONT_SIZE: $r('sys.float.Caption_M'),
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
  SEGMENT_TEXT_HORIZONTAL_PADDING: $r('sys.float.segment_button_text_l_r_padding'),
  SEGMENT_TEXT_VERTICAL_PADDING: $r('sys.float.segment_button_text_u_d_padding'),
  SEGMENT_TEXT_CAPSULE_VERTICAL_PADDING: $r('sys.float.segment_button_text_capsule_u_d_padding'),
  SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR: $r('sys.color.segment_button_focus_backboard_primary'),
  SEGMENT_FOCUS_STYLE_CUSTOMIZED: $r('sys.float.segment_focus_control')
}

interface Point {
  x: double,
  y: double
}

function nearEqual(first: double, second: double): boolean {
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
  direction?: Direction,
  backgroundSystemMaterial?: uiMaterial.Material,
  borderRadiusMode?: BorderRadiusMode,
  backgroundBorderRadius?: LengthMetrics,
  itemBorderRadius?: LengthMetrics,
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

class LengthMetricsUtils {
  private static instance?: LengthMetricsUtils;

  private constructor() {
  }

  public static getInstance(): LengthMetricsUtils {
    if (!LengthMetricsUtils.instance) {
      LengthMetricsUtils.instance = new LengthMetricsUtils();
    }
    return LengthMetricsUtils.instance!;
  }

  stringify(metrics: LengthMetrics): string | undefined {
    switch (metrics.unit) {
      case LengthUnit.PX:
        return `${metrics.value}px`;
      case LengthUnit.VP:
        return `${metrics.value}vp`;
      case LengthUnit.FP:
        return `${metrics.value}fp`;
      case LengthUnit.PERCENT:
        return `${metrics.value}%`;
      case LengthUnit.LPX:
        return `${metrics.value}lpx`;
    }
    return undefined;
  }

  isNaturalNumber(metrics: LengthMetrics): boolean {
    return metrics.value >= 0;
  }
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
      for (let i: int = 0; i < elementsOrLength as number; i++) {
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

  private createOptions(item: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem): SegmentButtonItemOptions {
    if (item instanceof SegmentButtonTextItem) {
      return new SegmentButtonItemOptions({
        text: item.text,
        accessibilityLevel: item.accessibilityLevel,
        accessibilityDescription: item.accessibilityDescription
      })
    } else if (item instanceof SegmentButtonIconItem) {
      return new SegmentButtonItemOptions({
        icon: item.icon,
        iconAccessibilityText: item.iconAccessibilityText,
        selectedIcon: item.selectedIcon,
        selectedIconAccessibilityText: item.selectedIconAccessibilityText,
        accessibilityLevel: item.accessibilityLevel,
        accessibilityDescription: item.accessibilityDescription
      })
    } else if (item instanceof SegmentButtonIconTextItem) {
      return new SegmentButtonItemOptions({
        icon: item.icon,
        iconAccessibilityText: item.iconAccessibilityText,
        selectedIcon: item.selectedIcon,
        selectedIconAccessibilityText: item.selectedIconAccessibilityText,
        text: item.text,
        accessibilityLevel: item.accessibilityLevel,
        accessibilityDescription: item.accessibilityDescription
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

  push(item1: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem,
    item2: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem): int {
    if (this.length + 2 > MAX_ITEM_COUNT) {
      console.warn('Exceeded the maximum number of elements (5).');
      return this.length;
    }
    this.changeStartIndex = this.length;
    this.deleteCount = 0;
    this.addLength = 2;
    let option1: SegmentButtonItemOptions = this.createOptions(item1);
    let option2: SegmentButtonItemOptions = this.createOptions(item2);
    return this._wrappedArray.push(option1, option2).toInt();
  }

  push(item1: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem,
    item2: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem,
    item3: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem): int {
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
    return this._wrappedArray.push(option1, option2, option3).toInt();
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

  unshift(item1: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem,
    item2: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem): int {
    if (this.length + 2 > MAX_ITEM_COUNT) {
      console.warn('Exceeded the maximum number of elements (5).');
      return this.length;
    }
    this.changeStartIndex = 0;
    this.deleteCount = 0;
    this.addLength = 2;

    let option1: SegmentButtonItemOptions = this.createOptions(item1);
    let option2: SegmentButtonItemOptions = this.createOptions(item2);
    return this._wrappedArray.unshift(option1, option2).toInt();
  }

  unshift(item1: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem,
    item2: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem,
    item3: SegmentButtonTextItem | SegmentButtonIconItem | SegmentButtonIconTextItem): int {
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
    return this._wrappedArray.unshift(option1, option2, option3).toInt();
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
    return this._wrappedArray.splice(start, deleteCount, ...items);
  }

  static create(elements: SegmentButtonItemTuple): SegmentButtonItemOptionsArray {
    return new SegmentButtonItemOptionsArray(elements);
  }
}

export enum BorderRadiusMode {
  /**
   * DEFAULT Mode, the framework automatically calculates the border radius
   */
  DEFAULT = 0,

  /**
   * CUSTOM Mode, the developer sets the border radius
   */
  CUSTOM = 1
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
  public hasFontSize: boolean = false;
  public hasSelectedFontSize: boolean = false;
  public iconTextRadius?: double;
  public iconTextBackgroundRadius?: double;
  public backgroundBlurStyle: BlurStyle = BlurStyle.Thick;
  public direction?: Direction;
  private _buttons: SegmentButtonItemOptionsArray | undefined = undefined;
  public backgroundSystemMaterial?: uiMaterial.Material;
  public borderRadiusMode?: BorderRadiusMode;
  public backgroundBorderRadius?: LengthMetrics;
  public itemBorderRadius?: LengthMetrics;

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
    this.hasFontSize = options.fontSize !== undefined ? true : false;
    this.hasSelectedFontSize = options.selectedFontSize !== undefined ? true : false;
    this.fontWeight = options.fontWeight ?? FontWeight.Regular;
    this.selectedFontWeight = options.selectedFontWeight ?? FontWeight.Medium;
    this.backgroundColor = options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR;
    this.selectedBackgroundColor = options.selectedBackgroundColor ?? segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR;
    this.imageSize = options.imageSize ?? { width: 24.0, height: 24.0 } as SizeOptions;
    this.buttonPadding = options.buttonPadding;
    this.textPadding = options.textPadding;
    this.type = options instanceof TabSegmentButtonOptions ? (options as TabSegmentButtonOptions).type :
      (options as CapsuleSegmentButtonOptions).type;
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
    let themePadding: double = LengthMetrics.resource($r('sys.float.padding_level1')).value;
    this.componentPadding = this.multiply ? 0.0 : themePadding;
    this.backgroundSystemMaterial = options.backgroundSystemMaterial;
    if (options instanceof TabSegmentButtonOptions) {
      this.borderRadiusMode = options.borderRadiusMode ?? BorderRadiusMode.DEFAULT;
      this.backgroundBorderRadius = options.backgroundBorderRadius;
      this.itemBorderRadius = options.itemBorderRadius;
    } else if (options instanceof CapsuleSegmentButtonOptions) {
      this.borderRadiusMode = options.borderRadiusMode ?? BorderRadiusMode.DEFAULT;
      this.backgroundBorderRadius = options.backgroundBorderRadius;
      this.itemBorderRadius = options.itemBorderRadius;
    }
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
      direction: options.direction,
      backgroundSystemMaterial: options.backgroundSystemMaterial,
      borderRadiusMode: options.borderRadiusMode,
      backgroundBorderRadius: options.backgroundBorderRadius,
      itemBorderRadius: options.itemBorderRadius,
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
      direction: options.direction,
      backgroundSystemMaterial: options.backgroundSystemMaterial,
      borderRadiusMode: options.borderRadiusMode,
      backgroundBorderRadius: options.backgroundBorderRadius,
      itemBorderRadius: options.itemBorderRadius,
    } as CapsuleSegmentButtonOptions)
  }
}

@Component
struct MultiSelectBackground {
  @ObjectLink optionsArray: SegmentButtonItemOptionsArray
  @ObjectLink options: SegmentButtonOptions
  @Consume buttonBorderRadius: LocalizedBorderRadiuses[]

  build() {
    Row({ space: 1.0 } as RowOptions) {
      ForEach(this.optionsArray._wrappedArray as Array<SegmentButtonItemOptions>,
        (_: SegmentButtonItemOptions, index: int) => {
          if (index < MAX_ITEM_COUNT) {
            Stack()
              .direction(this.options.direction)
              .layoutWeight(1.0)
              .height('100%')
              .backgroundColor(this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR)
              .borderRadius(this.buttonBorderRadius[index])
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
  @Consume zoomScaleArray: double[]
  @Consume buttonBorderRadius: LocalizedBorderRadiuses[]
  @Consume openSelectedItemSystemMaterial?: boolean = false;
  @Consume selectedItemScale?: ScaleOptions;


  getBackgroundColor(): ResourceColor {
    if (this.options.selectedBackgroundColor) {
      return this.options.selectedBackgroundColor;
    }
    if (this.options.type === 'tab') {
      return segmentButtonTheme.TAB_SELECTED_BACKGROUND_COLOR;
    } else {
      return segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
    }
  }

  getScale(): ScaleOptions | undefined {
    if (this.openSelectedItemSystemMaterial) {
      return this.selectedItemScale;
    } else {
      return {
        x: this.zoomScaleArray[this.selectedIndexes[0]],
        y: this.zoomScaleArray[this.selectedIndexes[0]]
      };
    }
  }

  getOpacity(): double {
    if (this.openSelectedItemSystemMaterial) {
      return 0.7;
    } else {
      return 1;
    }
  }

  build() {
    if (this.selectedIndexes !== undefined && this.selectedIndexes.length > 0) {
      Stack()
        .id("SelectItem")
        .direction(this.options.direction)
        .borderRadius(this.buttonBorderRadius[this.selectedIndexes[0]])
        .width('100%')
        .height('100%')
        .backgroundColor(this.getBackgroundColor())
        .scale(this.getScale())
        .opacity(this.getOpacity())
    }
  }
}

@Component
struct MultiSelectItemArray {
  @ObjectLink optionsArray: SegmentButtonItemOptionsArray;
  @ObjectLink @Watch('onOptionsChange') options: SegmentButtonOptions;
  @Link @Watch('onSelectedChange') selectedIndexes: int[];
  @Consume zoomScaleArray: double[];
  @Consume buttonBorderRadius: LocalizedBorderRadiuses[];
  @State multiColor: ResourceColor[] =
    Array.create<ResourceColor>(MAX_ITEM_COUNT, Color.Transparent as ResourceColor);

  onOptionsChange(a: string): void {
    for (let i: int = 0; i < this.selectedIndexes.length; i++) {
      const selectedIndex = this.selectedIndexes[i];
      if (selectedIndex >= 0 && selectedIndex < this.multiColor.length) {
        this.multiColor[selectedIndex] = this.options.selectedBackgroundColor ??
          segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
      }
    }
  }

  onSelectedChange(a: string): void {
    for (let i: int = 0; i < MAX_ITEM_COUNT; i++) {
      this.multiColor[i] = Color.Transparent;
    }
    for (let i: int = 0; i < this.selectedIndexes.length; i++) {
      const selectedIndex = this.selectedIndexes[i];
      if (selectedIndex >= 0 && selectedIndex < this.multiColor.length) {
        this.multiColor[selectedIndex] = this.options.selectedBackgroundColor ??
          segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
      }
    }
  }

  aboutToAppear(): void {
    for (let i: int = 0; i < this.selectedIndexes.length; i++) {
      const selectedIndex = this.selectedIndexes[i];
      if (selectedIndex >= 0 && selectedIndex < this.multiColor.length) {
        this.multiColor[selectedIndex] = this.options.selectedBackgroundColor ??
          segmentButtonTheme.CAPSULE_SELECTED_BACKGROUND_COLOR;
      }
    }
  }

  build() {
    Row({ space: 1.0 } as RowOptions) {
      ForEach(this.optionsArray._wrappedArray as Array<SegmentButtonItemOptions>,
        (_: SegmentButtonItemOptions, index: int) => {
          if (index < MAX_ITEM_COUNT) {
            Stack()
              .direction(this.options.direction)
              .layoutWeight(1.0)
              .height('100%')
              .backgroundColor(this.multiColor[index])
              .borderRadius(this.buttonBorderRadius[index])
          }
        })
    }
    .id("MultiSelectItemArray")
    .direction(this.options.direction)
    .padding(this.options.componentPadding)
  }
}

export class EnvironmentCallbackSegBtn implements EnvironmentCallback {
  private segmentButton: SegmentButton;

  constructor(segmentButton: SegmentButton) {
    this.segmentButton = segmentButton;
  }

  onConfigurationUpdated(config: Configuration): void {
    this.segmentButton.updateLanguageLineHeight();
    this.segmentButton.updateShouldMirror()
  }

  onMemoryLevel(level: AbilityConstant.MemoryLevel): void {}
}

@Component
struct SegmentButtonItem {
  @Link selectedIndexes: int[];
  @Link @Watch('onFocusIndex') focusIndex: int;
  @State @Require maxFontScale: double | Resource = 0.0;
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
  @Consume useAdaptiveLineHeight: boolean;
  private groupId: string = '';
  @State @Watch('onFocusIndex') hover: boolean = false;
  @Consume buttonItemsSize: SizeOptions[];
  @Consume positionTrigger: int
  @Link buttonItemsRealHeight: double[];
  public onCalculateBorderRadius?: () => void

  aboutToAppear(): void {
    this.isButtonTextFadeout = this.isSegmentFocusStyleCustomized;
  }

  private getTextPadding(): Padding | Dimension | LocalizedPadding {
    if (this.options.localizedTextPadding !== undefined) {
      return this.options.localizedTextPadding as LocalizedPadding;
    }
    if (this.options.textPadding !== undefined) {
      return this.options.textPadding!;
    }
    return 0.0;
  }

  private getButtonPadding(): Padding | Dimension | LocalizedPadding {
    if (this.options.localizedButtonPadding !== undefined) {
      return this.options.localizedButtonPadding! as LocalizedPadding;
    }
    if (this.options.buttonPadding !== undefined) {
      return this.options.buttonPadding!;
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

  isDefaultSelectedFontColor(): boolean {
    const isDefaultTab =
      this.options.type === 'tab' && this.options.selectedFontColor === segmentButtonTheme.TAB_SELECTED_FONT_COLOR;
    const isDefaultCapsule = this.options.type === 'capsule' &&
      this.options.selectedFontColor === segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR;
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
          .includeFontPadding(this.useAdaptiveLineHeight)
          .fallbackLineSpacing(this.useAdaptiveLineHeight)
      }
    }
    .id("SegmentButtonItem")
    .direction(this.options.direction)
    .focusScopePriority(this.groupId,
      Math.min(...this.selectedIndexes.map<double>(num => num.toDouble())) === this.index ? FocusPriority.PREVIOUS :
        FocusPriority.AUTO)
    .justifyContent(FlexAlign.Center)
    .padding(this.getButtonPadding())
    .constraintSize({ minHeight: segmentButtonTheme.CONSTRAINT_SIZE_MIN_HEIGHT })
    .onSizeChange((_: SizeOptions, newValue: SizeOptions) => {
      // Calculate height of items
      this.buttonItemsRealHeight[this.index] = (newValue.height ?? 0) as number;
      let maxHeight: double = Math.max(...this.buttonItemsRealHeight.slice(0, this.options.buttons ?
        this!.options!.buttons!.length : 0));
      for (let index = 0; index < this.buttonItemsSize.length; index++) {
        const currentWidth = (this.buttonItemsSize[index].width ?? 0.0) as number;
        const currentHeight = (this.buttonItemsSize[index].height ?? 0.0) as number;
        this.buttonItemsSize[index] = { width: currentWidth, height: maxHeight };
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
  pressIndex: int = 0
  pressColor: ResourceColor = segmentButtonTheme.PRESS_COLOR

  build() {
    Stack()
      .id("PressAndHoverEffect")
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
  @Consume zoomScaleArray: double[]

  build() {
    Row({ space: 1.0 } as RowOptions) {
      ForEach(this.buttons._wrappedArray as Array<SegmentButtonItemOptions>,
        (item: SegmentButtonItemOptions, index: int) => {
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
            .id("PressAndHoverEffectArray_Stack")
            .direction(this.options.direction)
            .scale({
              x: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1.0 :
                this.zoomScaleArray[index],
              y: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1.0 :
                this.zoomScaleArray[index]
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
  @Consume positionTrigger: int
  @Consume @Watch('onFocusIndex') focusIndex: int;
  @Consume zoomScaleArray: double[];
  @Consume buttonItemProperty: ItemProperty[];
  @Consume buttonItemsSelected: boolean[];
  @Link pressArray: boolean[];
  @Link hoverArray: boolean[];
  @Link hoverColorArray: HoverColorProperty[];
  @State @Require maxFontScale: double | Resource = 0.0;
  @State buttonWidth: double[] = Array.create<double>(MAX_ITEM_COUNT, 0);
  @State buttonHeight: double[] = Array.create<double>(MAX_ITEM_COUNT, 0);
  @State isMarqueeAndFadeout: boolean = false;
  @State buttonItemsRealHeight: double[] = Array.create<double>(MAX_ITEM_COUNT, 0);
  private groupId: string = util.generateRandomUUID(true);
  public onItemClicked?: Callback<int>;
  @State isSegmentFocusStyleCustomized: boolean = false;

  onButtonItemsSizeChange(a: string): void {
    this.buttonItemsSize.forEach((value, index) => {
      this.buttonWidth[index as int] = (value.width ?? 0.0) as number;
      this.buttonHeight[index as int] = (value.height ?? 0.0) as number;
    })
  }

  private changeSelectedIndexes(): void {
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

  private changeFocusIndex(): void {
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

  onOptionsArrayChange(a: string): void {
    if (this.options === undefined || this.options.buttons === undefined) {
      return;
    }
    if (this.optionsArray.changeStartIndex !== undefined && this.optionsArray.deleteCount !== undefined &&
      this.optionsArray.addLength !== undefined) {
      this.changeSelectedIndexes();
      this.changeFocusIndex();
      this.optionsArray.changeStartIndex = undefined;
      this.optionsArray.deleteCount = undefined;
      this.optionsArray.addLength = undefined;
    }
  }

  onOptionsChange(a: string): void {
    if (this.options === undefined || this.options.buttons === undefined) {
      return;
    }
    this.calculateBorderRadius();
  }

  onFocusIndex(a: string): void {
    this.isMarqueeAndFadeout = this.isSegmentFocusStyleCustomized && !this.isMarqueeAndFadeout;
  }

  aboutToAppear(): void {
    for (let index = 0; index < this.buttonItemsRealHeight.length; index++) {
      this.buttonItemsRealHeight[index] = 0.0;
    }
  }

  private getBorderRadius(index: int): LocalizedBorderRadiuses {
    let borderRadius: LocalizedBorderRadiuses = this.buttonBorderRadius[index]
    if (this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex]) {
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
  focusStack(index: int) {
    Stack() {
      Stack()
        .direction(this.options.direction)
        .borderRadius(this.getBorderRadius(index))
        .size({
          width: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ?
            this.buttonWidth[index] + 8.0 : this.buttonWidth[index],
          height: this.options.type === 'capsule' && this.buttonItemsSelected[this.focusIndex] ?
            this.buttonHeight[index] + 8.0 : this.buttonHeight[index]
        })
        .borderColor(segmentButtonTheme.FOCUS_BORDER_COLOR)
        .borderWidth(2.0)
    }
    .direction(this.options.direction)
    .size({ width: 1.0, height: 1.0 })
    .align(Alignment.Center)
  }

  private isMultiply(): boolean {
    return this.options.multiply ?? false;
  }

  private calculateBorderRadius(): void {
    let borderRadiusArray: LocalizedBorderRadiuses[] = new Array<LocalizedBorderRadiuses>(MAX_ITEM_COUNT, (): LocalizedBorderRadiuses => {
      return {
        topStart: LengthMetrics.vp(0),
        topEnd: LengthMetrics.vp(0),
        bottomStart: LengthMetrics.vp(0),
        bottomEnd: LengthMetrics.vp(0)
      }
    })

    const setAllCorners = (array: LocalizedBorderRadiuses[], index: int, lengthMetrics: LengthMetrics) => {
      if (!array || index < 0 || index >= array.length) {
        return;
      }

      const safeLengthMetrics = lengthMetrics.value < 0 ? LengthMetrics.vp(0) : lengthMetrics;
      array[index].topStart = safeLengthMetrics;
      array[index].topEnd = safeLengthMetrics;
      array[index].bottomStart = safeLengthMetrics;
      array[index].bottomEnd = safeLengthMetrics;
    };

    const setLeftCorners = (array: LocalizedBorderRadiuses[], index: int, lengthMetrics: LengthMetrics) => {
      if (!array || index < 0 || index >= array.length) {
        return;
      }
      const safeLengthMetrics = lengthMetrics.value < 0 ? LengthMetrics.vp(0) : lengthMetrics;
      const zeroLengthMetrics = LengthMetrics.vp(0);
      array[index].topStart = safeLengthMetrics;
      array[index].topEnd = zeroLengthMetrics;
      array[index].bottomStart = safeLengthMetrics;
      array[index].bottomEnd = zeroLengthMetrics;
    };

    const setRightCorners = (array: LocalizedBorderRadiuses[], index: int, lengthMetrics: LengthMetrics) => {
      if (!array || index < 0 || index >= array.length) {
        return;
      }
      const safeLengthMetrics = lengthMetrics.value < 0 ? LengthMetrics.vp(0) : lengthMetrics;
      const zeroLengthMetrics = LengthMetrics.vp(0);
      array[index].topStart = zeroLengthMetrics;
      array[index].topEnd = safeLengthMetrics;
      array[index].bottomStart = zeroLengthMetrics;
      array[index].bottomEnd = safeLengthMetrics;
    };

    const setMiddleCorners = (array: LocalizedBorderRadiuses[], index: int) => {
      if (!array || index < 0 || index >= array.length) {
        return;
      }
      array[index].topStart = LengthMetrics.vp(0);
      array[index].topEnd = LengthMetrics.vp(0);
      array[index].bottomStart = LengthMetrics.vp(0);
      array[index].bottomEnd = LengthMetrics.vp(0);
    };

    const buttonsLength = this.optionsArray.length;

    for (let index = 0; index < this.buttonBorderRadius.length; index++) {
      let halfButtonItemsSizeHeight = (this.buttonItemsSize[index].height ?? 0.0) as double / 2.0;
      let radius = this.options.iconTextRadius ?? halfButtonItemsSizeHeight;
      const isCustomMode = this.options.borderRadiusMode === BorderRadiusMode.CUSTOM &&
        this.options.itemBorderRadius !== undefined;

      let radiusLengthMetrics: LengthMetrics;
      if (isCustomMode && !!this.options.itemBorderRadius) {
        // Use custom border radius from options
        radiusLengthMetrics = this.options.itemBorderRadius!;
      } else {
        // Use default calculated radius value
        radiusLengthMetrics = LengthMetrics.vp(radius);
      }

      if (this.isMultiply()) {
        if (index === 0) {
          setLeftCorners(borderRadiusArray, index, radiusLengthMetrics);
        } else if (index === buttonsLength - 1) {
          setRightCorners(borderRadiusArray, index, radiusLengthMetrics);
        } else {
          setMiddleCorners(borderRadiusArray, index);
        }
      } else {
        setAllCorners(borderRadiusArray, index, radiusLengthMetrics);
      }

    }
    this.buttonBorderRadius = borderRadiusArray;
  }

  private getAccessibilityDescription(value?: ResourceStr): Resource | undefined | string {
    return (typeof value !== undefined) ? value : undefined;
  }

  private isDefaultSelectedBgColor(): boolean {
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
          (item: SegmentButtonItemOptions, index: int) => {
            if (index < MAX_ITEM_COUNT) {
              Button({} as ButtonOptions) {
                SegmentButtonItem({
                  isMarqueeAndFadeout: this.isMarqueeAndFadeout,
                  isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized,
                  selectedIndexes: this.selectedIndexes,
                  focusIndex: this.focusIndex,
                  index: index,
                  itemOptions: item,
                  options: this.options,
                  property: this.buttonItemProperty[index],
                  groupId: this.groupId,
                  maxFontScale: this.maxFontScale,
                  hover: this.hoverArray[index],
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
              .accessibilitySelected(this.options.multiply ? undefined : this.selectedIndexes.includes(index))
              .accessibilityChecked(this.options.multiply ? this.selectedIndexes.includes(index) : undefined)
              .accessibilityDescription(this.getAccessibilityDescription(item.accessibilityDescription))
              .direction(this.options.direction)
              .borderRadius(this.buttonBorderRadius[index])
              .scale({
                x: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1.0 :
                  this.zoomScaleArray[index],
                y: this.options.type === 'capsule' && (this.options.multiply ?? false) ? 1.0 :
                  this.zoomScaleArray[index]
              })
              .height(this.buttonItemsSize[index].height)
              .layoutWeight(1.0)
              .padding(0.0)
              .onSizeChange((_: SizeOptions, newValue: SizeOptions) => {
                this.buttonItemsSize[index] =
                  { width: newValue.width, height: this.buttonItemsSize[index].height };
                if (newValue.width) {
                  this.positionTrigger = (this.positionTrigger + 1) & 0xFFFFF // mod 2^20
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
                  this.onItemClicked?.(index);
                }
                if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
                  const currentIndex = this.selectedIndexes.indexOf(index);
                  if (currentIndex === -1.0) {
                    this.selectedIndexes.push(index);
                  } else {
                    this.selectedIndexes.splice(currentIndex, 1)
                  }
                } else {
                  this.selectedIndexes[0] = index;
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
                  this.getUIContext()?.animateTo({
                    curve: curves.interpolatingSpring(10.0, 1.0, 410.0, 38.0) as ICurve
                  }, () => {
                    this.zoomScaleArray[index] = 0.95;
                  })
                } else if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                  this.getUIContext()?.animateTo({
                    curve: curves.interpolatingSpring(10.0, 1.0, 410.0, 38.0) as ICurve
                  }, () => {
                    this.zoomScaleArray[index] = 1.0;
                  })
                } else {
                }
              })
              .onHover((isHover: boolean, event: HoverEvent) => {
                this.hoverArray[index] = isHover
                if (isHover) {
                  this.getUIContext()?.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                    this.hoverColorArray[index].hoverColor =
                      this.isSegmentFocusStyleCustomized && this.focusIndex === index ?
                        segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR : segmentButtonTheme.HOVER_COLOR;
                  })
                } else {
                  this.getUIContext()?.animateTo({ duration: 250, curve: Curve.Friction }, () => {
                    this.hoverColorArray[index].hoverColor =
                      this.isSegmentFocusStyleCustomized && this.focusIndex === index ?
                        segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR : Color.Transparent;
                  })
                }
              })
              .onMouse((event: MouseEvent) => {
                switch (event.action) {
                  case MouseAction.Press:
                    this.getUIContext()?.animateTo({ curve: curves.springMotion(0.347, 0.99) as ICurve }, () => {
                      this.zoomScaleArray[index] = 0.95;
                    })
                    this.getUIContext()?.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                      this.pressArray[index] = true;
                    })
                    break;
                  case MouseAction.Release:
                    this.getUIContext()?.animateTo({ curve: curves.springMotion(0.347, 0.99) as ICurve }, () => {
                      this.zoomScaleArray[index] = 1.0;
                    })
                    this.getUIContext()?.animateTo({ duration: 100, curve: Curve.Sharp }, () => {
                      this.pressArray[index] = false;
                    })
                    break;
                }
              })
            }
          }, (item: SegmentButtonItemOptions, index: int) => JSON.stringify(item) + index)
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
  private customizeSegmentFocusStyle(index: int) {
    if (this.selectedIndexes !== undefined && this.selectedIndexes.length !== 0.0 &&
      this.selectedIndexes[0] === index) { // 选中态
      this.hoverColorArray[index].hoverColor = this.isDefaultSelectedBgColor() ?
        segmentButtonTheme.SEGMENT_BUTTON_FOCUS_CUSTOMIZED_BG_COLOR : this.options.selectedBackgroundColor;
    } else { // 未选中态
      this.hoverColorArray[index].hoverColor =
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
  @State maxFontScale: double | Resource = DEFAULT_MAX_FONT_SCALE
  @Provide componentSize: SizeOptions = { width: 0.0, height: 0.0 } as SizeOptions
  @Provide buttonBorderRadius: LocalizedBorderRadiuses[] = (() => {
    let array = new Array<LocalizedBorderRadiuses>(MAX_ITEM_COUNT, (): LocalizedBorderRadiuses => {
      return {
        topStart: LengthMetrics.vp(0),
        topEnd: LengthMetrics.vp(0),
        bottomStart: LengthMetrics.vp(0),
        bottomEnd: LengthMetrics.vp(0)
      }
    })
    return array;
  })()
  @Provide buttonItemsSize: SizeOptions[] = (() => {
    let arr: SizeOptions[] = [];
    for (let i: int = 0; i < MAX_ITEM_COUNT; i++) {
      arr.push({});
    }
    return arr;
  })()
  @Provide @Watch('onItemsPositionChange') positionTrigger: int = 0
  @Provide buttonItemsSelected: boolean[] = Array.create<boolean>(MAX_ITEM_COUNT, false);
  @Provide buttonItemProperty: ItemProperty[] = (() => {
    let array = new Array<ItemProperty>(MAX_ITEM_COUNT, () => { return new ItemProperty() })
    return array;
  })()
  @Provide focusIndex: int = -1;
  @State selectedItemOffsetX: double = 0
  @Provide zoomScaleArray: double[] = Array.create<double>(MAX_ITEM_COUNT, 1.0);
  @State pressArray: boolean[] = Array.create<boolean>(MAX_ITEM_COUNT, false);
  @State hoverArray: boolean[] = Array.create<boolean>(MAX_ITEM_COUNT, false);
  @State hoverColorArray: HoverColorProperty[] = (() => {
    let arr: HoverColorProperty[] = [];
    for (let i: int = 0; i < MAX_ITEM_COUNT; i++) {
      arr.push(new HoverColorProperty());
    }
    return arr;
  })()
  private doSelectedChangeAnimate: boolean = false;
  private isCurrentPositionSelected: boolean = false;
  private isCurrentPositionPressed: boolean = false;
  private panGestureStartPoint: Point = { x: 0.0, y: 0.0 } as Point;
  private isPanGestureMoved: boolean = false;
  @State shouldMirror: boolean = false;
  private isSegmentFocusStyleCustomized: boolean =
    resourceToNumber(this.getUIContext()?.getHostContext(), segmentButtonTheme.SEGMENT_FOCUS_STYLE_CUSTOMIZED, 1) === 0;
  private isGestureInProgress: boolean = false;
  @PropRef enableStateAnimation: boolean = false;
  @Provide openSelectedItemSystemMaterial?: boolean = false;
  @Provide selectedItemScale?: ScaleOptions = undefined;
  @Provide useAdaptiveLineHeight: boolean = false;
  private environmentCallbackID?: int;
  private environmentCallback: EnvironmentCallbackSegBtn = new EnvironmentCallbackSegBtn(this);
  private layoutAlgorithm: SegmentButtonLayoutAlgorithm = new SegmentButtonLayoutAlgorithm()

  onItemsPositionChange(a: string): void {
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

  private setItemsSelected(): void {
    this.buttonItemsSelected.forEach((_, index) => {
      this.buttonItemsSelected[index as int] = false;
    })
    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
      this.selectedIndexes.forEach((index) => {
        this.buttonItemsSelected[index as int] = true;
      })
    } else {
      if (this.selectedIndexes.length !== 0) {
        this.buttonItemsSelected[this.selectedIndexes[0]] = true;
      }
    }
  }

  private updateSelectedIndexes(): void {
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

  onOptionsChange(a: string): void {
    if (this.options === undefined || this.options.buttons === undefined) {
      return;
    }
    this.shouldMirror = this.isShouldMirror();
    this.updateSelectedIndexes();
    this.setItemsSelected();
    this.layoutAlgorithm.componentPadding = this.getUIContext().vp2px(
      Number.parseFloat(this.options.componentPadding.toString())
    )
    this.layoutAlgorithm.rowSpace = this.getUIContext().vp2px(1)
    this.layoutAlgorithm.selectedIndex = this.selectedIndexes.length > 0 ? this.selectedIndexes[0] : -1
    this.layoutAlgorithm.multiply = this.options.type === 'capsule' && (this.options.multiply ?? false)
    this.layoutAlgorithm.shouldMirror = this.shouldMirror
    this.updateAnimatedProperty(null);
    if (this.environmentCallbackID === undefined && deviceInfo.sdkApiVersion >= 26) {
      let abilityContext = this.getUIContext().getHostContext()
      if (abilityContext) {
        this.environmentCallbackID = abilityContext.getApplicationContext().onEnvironment(this.environmentCallback)
      }
    }
  }

  onSelectedChange(a: string): void {
    if (this.options === undefined || this.options.buttons === undefined) {
      return;
    }
    this.updateSelectedIndexes();
    this.setItemsSelected();

    const oldIndex = this.layoutAlgorithm.selectedIndex
    const newIndex = this.selectedIndexes.length > 0 ? this.selectedIndexes[0] : -1
    if (oldIndex >= 0 && newIndex >= 0 && oldIndex !== newIndex &&
      this.layoutAlgorithm.buttonWidth > 0) {
      const deltaX = this.layoutAlgorithm.getButtonX(oldIndex) - this.layoutAlgorithm.getButtonX(newIndex)
      this.selectedItemOffsetX = this.getUIContext().px2vp(deltaX)
    }

    this.layoutAlgorithm.selectedIndex = newIndex
    if (this.doSelectedChangeAnimate || this.enableStateAnimation) {
      this.updateAnimatedProperty(this.getSelectedChangeCurve());
    } else {
      this.updateAnimatedProperty(null);
    }
  }

  aboutToAppear(): void {
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
    if (deviceInfo.sdkApiVersion >= 26) {
      this.updateLanguageLineHeight();
      let abilityContext = this.getUIContext().getHostContext();
      if (abilityContext) {
        this.environmentCallbackID = abilityContext.getApplicationContext().onEnvironment(this.environmentCallback);
      }
    }
  }

  aboutToDisappear(): void {
    if (deviceInfo.sdkApiVersion >= 26 && this.environmentCallbackID !== undefined) {
      let abilityContext = this.getUIContext().getHostContext();
      if (abilityContext) {
        abilityContext.getApplicationContext().offEnvironment(this.environmentCallbackID as int);
      }
      this.environmentCallbackID = undefined;
    }
  }

  updateShouldMirror(): void {
    this.layoutAlgorithm.shouldMirror = this.isShouldMirror()
  }

  updateLanguageLineHeight(): void {
    const resourceManager = this.getUIContext().getHostContext()?.resourceManager;
    if (!resourceManager) {
      console.error(`[SegmentButton] failed to get resourceManager`);
      return;
    }
    try {
      this.useAdaptiveLineHeight = resourceManager!.getStringByNameSync('text_fallback_line_spacing') === 'true';
    } catch (e) {
      console.error(`[SegmentButton] failed to get text_fallback_line_spacing resource`);
    }
  }

  private isMouseWheelScroll(event: GestureEvent): boolean {
    return event.source === SourceType.Mouse && !this.isPanGestureMoved;
  }

  private isMovedFromPanGestureStartPoint(x: double, y: double): boolean {
    return !nearEqual(x, this.panGestureStartPoint.x) || !nearEqual(y, this.panGestureStartPoint.y);
  }

  private isShouldMirror(): boolean {
    if (this.options.direction == Direction.Rtl) {
      return true;
    }
    // 获取系统语言
    try {
      let appPreferredLanguage: string = I18n.System.getAppPreferredLanguage();
      if (I18n.isRTL(appPreferredLanguage) && this.options.direction != Direction.Ltr) {
        return true;
      }
    } catch (error) {
      console.error(`Ace SegmentButton getSystemLanguage, error: ${error.toString()}`);
    }
    return false;
  }

  private isMultiplyCapsule(): boolean {
    return this.options !== undefined &&
      this.options.type === 'capsule' && (this.options.multiply ?? false);
  }

  private shouldShowBackground(): boolean {
    return !this.isMultiplyCapsule() && this.isBackgroundSystemMaterialEnabled();
  }

  private getButtonBackgroundColor(): ResourceColor | undefined {
    if (!this.shouldShowBackground()) {
      return undefined;
    }
    return this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR;
  }

  private getButtonBorderRadius(): Length | undefined {
    if (!this.shouldShowBackground()) {
      return undefined;
    }
    return this.getBackgroundBorderRadius();
  }

  private getButtonSystemMaterial(): uiMaterial.Material | undefined {
    if (!this.shouldShowBackground()) {
      return undefined;
    }
    return this.options.backgroundSystemMaterial;
  }

  build() {
    Stack() {
      if (this.options !== undefined && this.options.buttons !== undefined) {
        DynamicLayout(this.layoutAlgorithm) {
          if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
            MultiSelectBackground({
              optionsArray: this.options.buttons!,
              options: this.options,
            })
          } else {
            Stack() {
              if (this.options.buttons !== undefined && this!.options!.buttons!.length.toDouble() > 1.0) {
                PressAndHoverEffectArray({
                  options: this.options,
                  buttons: this.options.buttons!,
                  pressArray: this.pressArray,
                  hoverArray: this.hoverArray,
                  hoverColorArray: this.hoverColorArray
                })
              }
            }
            .id("SegmentButton_BackgroundStack")
            .direction(this.options.direction)
            .backgroundColor(this.options.backgroundColor ?? segmentButtonTheme.BACKGROUND_COLOR)
            .borderRadius(this.getBackgroundBorderRadius())
            .backgroundBlurStyle(this.options.backgroundBlurStyle, undefined, { disableSystemAdaptation: true })
            .systemMaterial(this.options.backgroundSystemMaterial)
          }
          Stack() {
            if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
              MultiSelectItemArray({
                optionsArray: this.options.buttons!,
                options: this.options,
                selectedIndexes: this.selectedIndexes
              })
            } else {
              SelectItem({
                optionsArray: this.options.buttons!,
                options: this.options,
                selectedIndexes: this.selectedIndexes
              })
            }
          }
          .id("SegmentButton_ItemStack")
          .direction(this.options.direction)
          .animation({ duration: 0 })
          .borderRadius(this.getBackgroundBorderRadius())
          .translate({ x: this.selectedItemOffsetX })

          SegmentButtonItemArrayComponent({
            pressArray: this.pressArray,
            hoverArray: this.hoverArray,
            hoverColorArray: this.hoverColorArray,
            optionsArray: this.options.buttons!,
            options: this.options,
            selectedIndexes: this.selectedIndexes,
            maxFontScale: this.getMaxFontSize(),
            onItemClicked: this.onItemClicked,
            isSegmentFocusStyleCustomized: this.isSegmentFocusStyleCustomized
          })
        }
      }
    }
    .id("SegmentButton")
    .direction(this.options ? this.options.direction : undefined)
    .backgroundColor(this.getButtonBackgroundColor())
    .borderRadius(this.getButtonBorderRadius())
    .clip(false)
    .systemMaterial(this.getButtonSystemMaterial())
    .onBlur(() => {
      this.focusIndex = -1
    })
    .onKeyEvent((event: KeyEvent) => {
      if (!this.options || !this.options.buttons) {
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
      return true;
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
            let selectedInfo: double = fingerInfo!.localX ?? 0;

            let buttonLength: int =
              this!.options!.buttons!.length < this!.buttonItemsSize!.length ? this!.options!.buttons!.length : this!.buttonItemsSize!.length;

            // 安全检查
            if (!this.buttonItemsSize || buttonLength <= 0) {
              return;
            }

            for (let i: int = 0; i < buttonLength; i++) {
              // 添加安全检查
              if (i >= this.buttonItemsSize.length) {
                break;
              }

              let buttonSize = this.buttonItemsSize[i];
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
                (this.selectedIndexes.length > 0 &&
                  this.selectedIndexes[0] > Math.min(this!.options!.buttons!.length.toDouble(),
                    this!.buttonItemsSize!.length.toDouble())) ? false : true;

              let realClickIndex: int = this.isShouldMirror() ? buttonLength - 1 - i : i;
              if (this.onItemClicked) {
                this.onItemClicked?.(realClickIndex.toInt());
              }
              if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {

                let selectedIndex: int = this.selectedIndexes.indexOf(realClickIndex.toInt(), 0)
                if (selectedIndex === -1.0) {
                  this.selectedIndexes.push(realClickIndex.toInt());
                } else {
                  this.selectedIndexes = this.selectedIndexes.filter((_, index) => index !== selectedIndex);
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
            if (this.options === undefined || this.options.buttons === undefined ||
              event.sourceTool === SourceTool.TOUCHPAD) {
              return;
            }
            if (this.isMultiply()) {
              // Non swipe gesture in multi-select mode
              return;
            }
            if (this.isCurrentPositionSelected) {
              return;
            }
            let isHorizontalSwipe = (Math.abs(event.angle) <= 45) || (Math.abs(event.angle) >= 135);
            if (!isHorizontalSwipe) {
              return;
            }

            let isSwipeRight = Math.abs(event.angle) <= 45; // swipe right
            let isSwipeLeft = Math.abs(event.angle) >= 135; // swipe left

            let isSwipeToNext = this.isShouldMirror() ? isSwipeLeft : isSwipeRight;
            let isSwipeToPrevious = this.isShouldMirror() ? isSwipeRight : isSwipeLeft;

            if (isSwipeToNext && this.selectedIndexes[0] !== Math.min(this.options!.buttons!.length,
              this.buttonItemsSize!.length) - 1) {
              // Move to next
              this.doSelectedChangeAnimate = true
              this.selectedIndexes[0] = this.selectedIndexes[0] + 1
              this.doSelectedChangeAnimate = false
            } else if (isSwipeToPrevious && this.selectedIndexes[0] !== 0) {
              // Move to previous
              this.doSelectedChangeAnimate = true
              this.selectedIndexes[0] = this.selectedIndexes[0] - 1
              this.doSelectedChangeAnimate = false
            }
          }),
        LongPressGesture({ repeat: false, duration: 200 })
          .onAction((event: GestureEvent) => {
            if (!this.isBackgroundSystemMaterialEnabled()) {
              return
            }
            if (this.options === undefined || this.options.buttons === undefined) {
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
            let selectedInfo = fingerInfo.localX

            let buttonLength = Math.min(this.options!.buttons!.length, this.buttonItemsSize!.length);
            for (let i: int = 0; i < buttonLength; i++) {
              selectedInfo = selectedInfo - ((this.buttonItemsSize[i].width ?? 0) as number);
              if (selectedInfo < 0) {
                let realIndex = this.isShouldMirror() ? buttonLength - 1 - i : i;
                this.isCurrentPositionPressed = realIndex === this.selectedIndexes[0] ? true : false;
                break
              }
            }
            if (this.isCurrentPositionPressed && !this.openSelectedItemSystemMaterial) {
              this.startSelectMaterialAnimation();
            }
          })
          .onActionCancel((event: GestureEvent) => {
            if (!this.isBackgroundSystemMaterialEnabled()) {
              return
            }
            if (this.options === undefined || this.options.buttons === undefined) {
              return;
            }
            if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
              // Non drag gesture in multi-select mode
              return;
            }

            if (this.isCurrentPositionPressed && this.openSelectedItemSystemMaterial) {
              this.finishSelectMaterialAnimation();
            }
            this.isCurrentPositionPressed = false;
          })
          .onActionEnd((event: GestureEvent) => {
            if (!this.isBackgroundSystemMaterialEnabled()) {
              return
            }
            if (this.options === undefined || this.options.buttons === undefined) {
              return;
            }
            if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
              // Non drag gesture in multi-select mode
              return;
            }
            if (this.isCurrentPositionPressed && this.openSelectedItemSystemMaterial) {
              this.finishSelectMaterialAnimation();
            }
            this.isCurrentPositionPressed = false;
          }),
        PanGesture({direction: PanDirection.Horizontal})
          .onActionStart((event: GestureEvent) => {
            this.isGestureInProgress = true;
            if (this.options === undefined || this.options.buttons === undefined) {
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
            let selectedInfo: double = (fingerInfo?.localX ?? 0) as double;
            this.panGestureStartPoint =
              { x: (fingerInfo?.globalX ?? 0) as number, y: (fingerInfo?.globalY ?? 0) as number };
            this.isPanGestureMoved = false;

            let buttonLength = Math.min(this.options!.buttons!.length, this.buttonItemsSize!.length);
            for (let i: int = 0; i < buttonLength; i++) {
              selectedInfo = selectedInfo - ((this.buttonItemsSize[i].width ?? 0) as number);
              if (selectedInfo < 0.0) {
                let realIndex = this.isShouldMirror() ? buttonLength - 1 - i : i;
                this.isCurrentPositionSelected = realIndex === this.selectedIndexes[0] ? true : false;
                break;
              }
            }

            if (this.isBackgroundSystemMaterialEnabled() && this.isCurrentPositionSelected) {
              this.getUIContext().animateTo({
                curve: curves.interpolatingSpring(0, 1, 195, 14),
              }, () => {
                this.selectedItemScale = { x: 1.01, y: 0.99 }
              })
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
            let selectedInfo: double = fingerInfo!.localX ?? 0;
            if (!this.isPanGestureMoved && this.isMovedFromPanGestureStartPoint(fingerInfo!.globalX ?? 0,
              fingerInfo!.globalY ?? 0)) {
              this.isPanGestureMoved = true;
            }
            if (this.isBackgroundSystemMaterialEnabled()) {
              const alg = this.layoutAlgorithm
              let buttonLength: int = Math.min(this.options!.buttons!.length, this.buttonItemsSize!.length).toInt();
              const startX = Math.min(alg.getButtonX(0), alg.getButtonX(buttonLength - 1))
              const endX = Math.max(alg.getButtonX(0), alg.getButtonX(buttonLength - 1))

              const fingerOffset = this.getUIContext().vp2px(fingerInfo.globalX - this.panGestureStartPoint.x)
              const currentButtonX = alg.getButtonX(this.selectedIndexes[0])
              let nowX = fingerOffset + currentButtonX
              nowX = Math.max(startX, nowX)
              nowX = Math.min(endX, nowX)

              this.selectedItemOffsetX = this.getUIContext().px2vp(nowX - currentButtonX)
            } else {
              let buttonLength: int = Math.min(this.options!.buttons!.length, this.buttonItemsSize!.length).toInt();
              for (let i: int = 0; i < buttonLength; i++) {
                selectedInfo = selectedInfo - ((this.buttonItemsSize[i].width ?? 0) as number)
                if (selectedInfo < 0.0) {
                  let realIndex: int = this.isShouldMirror() ? buttonLength - 1 - i : i;
                  this.doSelectedChangeAnimate = true;
                  this.selectedIndexes[0] = realIndex;
                  this.doSelectedChangeAnimate = false;
                  break
                }
              }
              this.zoomScaleArray.forEach((_, index) => {
                if (index === this.selectedIndexes[0]) {
                  this.getUIContext()?.animateTo({
                    curve: curves.interpolatingSpring(10.0, 1.0, 410.0, 38.0) as ICurve
                  },
                    () => {
                      this.zoomScaleArray[index] = 0.95;
                    });
                } else {
                  this.getUIContext()?.animateTo({
                    curve: curves.interpolatingSpring(10.0, 1.0, 410.0, 38.0) as ICurve
                  },
                    () => {
                      this.zoomScaleArray[index] = 1.0;
                    });
                }
              })
            }
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

            if (this.isBackgroundSystemMaterialEnabled()) {
              let selectedInfo = fingerInfo.localX
              let buttonLength: int = Math.min(this.options!.buttons!.length, this.buttonItemsSize!.length).toInt();
              let realIndex: int = -1;
              for (let i: int = 0; i < buttonLength; i++) {
                selectedInfo = selectedInfo - (this.buttonItemsSize[i].width as number)
                if (selectedInfo < 0) {
                  realIndex = this.isShouldMirror() ? buttonLength - 1 - i : i;
                  break
                }
              }
              if (realIndex === -1) {
                realIndex = this.isShouldMirror() ? 0 : buttonLength - 1
              }
              this.getUIContext().animateTo({ curve: curves.springMotion(0.347, 0.99) }, () => {
                this.selectedIndexes[0] = realIndex;
                this.selectedItemOffsetX = 0
              })
              this.finishSelectMaterialAnimation();

            } else {
              if (this.isMouseWheelScroll(event)) {
                let offset = event.offsetX !== 0 ? event.offsetX : event.offsetY;
                this.doSelectedChangeAnimate = true;

                // Reverse mouse wheel direction in mirrored layout
                let shouldMoveNext = this.isShouldMirror() ? offset > 0 : offset < 0;
                let shouldMovePrevious = this.isShouldMirror() ? offset < 0 : offset > 0;

                if (shouldMovePrevious && this.selectedIndexes[0] > 0) {
                  this.selectedIndexes[0] -= 1;
                } else if (shouldMoveNext && this.selectedIndexes[0] < Math.min(this.options!.buttons!.length,
                  this.buttonItemsSize!.length) - 1) {
                  this.selectedIndexes[0] += 1;
                }
                this.doSelectedChangeAnimate = false;
              }
              this.getUIContext()?.animateTo({ curve: curves.interpolatingSpring(10.0, 1.0, 410.0, 38.0) as ICurve },
                () => {
                  this.zoomScaleArray[this.selectedIndexes[0]] = 1.0;
                });
            }
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
            this.getUIContext()?.animateTo({ curve: curves.interpolatingSpring(10.0, 1.0, 410.0, 38.0) as ICurve },
              () => {
                this.zoomScaleArray[this.selectedIndexes[0]] = 1.0;
              })
            this.isCurrentPositionSelected = false;
            if (this.isBackgroundSystemMaterialEnabled()) {
              this.finishSelectMaterialAnimation();
            }
          })
      )
    )
  }

  private isBackgroundSystemMaterialEnabled(): boolean {
    return this.options !== undefined &&
      this.options.backgroundSystemMaterial !== undefined;
  }

  startSelectMaterialAnimation(): void {
    if (!this.openSelectedItemSystemMaterial) {
      this.getUIContext().animateTo({
        curve: curves.interpolatingSpring(0, 1, 195, 14),
      }, () => {
        this.selectedItemScale = { x: 1.05, y: 1.18 }
        this.openSelectedItemSystemMaterial = true;
      })
    }
  }

  finishSelectMaterialAnimation(): void {
    if (this.openSelectedItemSystemMaterial) {
      this.getUIContext().animateTo({ curve: curves.interpolatingSpring(0, 1, 195, 14) }, () => {
        this.selectedItemScale = { x: 1.05, y: 1.18 };
      })
      this.getUIContext()
        .animateTo({
          curve: curves.interpolatingSpring(0, 1, 195, 14), delay: 300, onFinish: () => {
          }
        }, () => {
          this.openSelectedItemSystemMaterial = false;
          this.selectedItemScale = undefined;
        })
    }
  }

  private getMaxFontSize(): double {
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

  private isMultiply(): boolean {
    return this.options.multiply ?? false;
  }

  private getBackgroundBorderRadius(): Length | undefined {
    if (this.options.borderRadiusMode === BorderRadiusMode.CUSTOM) {
      // For capsule multi-select buttons, use itemBorderRadius
      if (this.isMultiply() && !!this.options.itemBorderRadius) {
        return LengthMetricsUtils.getInstance().stringify(this.options.itemBorderRadius!);
      } else if (!!this.options.backgroundBorderRadius) {
        return LengthMetricsUtils.getInstance().stringify(this.options.backgroundBorderRadius!);
      }
    }

    const defaultRadius = this.componentSize.height as double / 2;
    if (this.isMultiply()) {
      return this.options.iconTextRadius ?? this.options.iconTextBackgroundRadius ?? defaultRadius;
    }
    return this.options.iconTextBackgroundRadius ?? defaultRadius;
  }

  private getSelectedChangeCurve(): ICurve | null {
    if (this.options.type === 'capsule' && (this.options.multiply ?? false)) {
      return null;
    }
    return curves.springMotion(0.347, 0.99) as ICurve;
  }

  updateAnimatedProperty(curve: ICurve | null) {

    let setAnimatedPropertyFunc = () => {
      this.selectedItemOffsetX = 0

      this.buttonItemsSelected.forEach((selected, index) => {
        const newColor = selected ?
          this.options.selectedFontColor ?? (this.options.type === 'tab' ?
            segmentButtonTheme.TAB_SELECTED_FONT_COLOR : segmentButtonTheme.CAPSULE_SELECTED_FONT_COLOR) :
          this.options.fontColor ?? segmentButtonTheme.FONT_COLOR;
        this.buttonItemProperty[index].fontColor = newColor;
      })
    }
    if (curve) {
      if (this.options.backgroundSystemMaterial) {
        this.getUIContext().animateTo({
          curve: curves.interpolatingSpring(0, 1, 195, 14),
        }, () => {
          this.selectedItemScale = { x: 1.01, y: 0.99 }
          this.openSelectedItemSystemMaterial = true;
        })
        this.getUIContext().animateTo({ curve: curve }, setAnimatedPropertyFunc);
        this.getUIContext().animateTo({
          curve: curves.interpolatingSpring(0, 1, 195, 14),
          delay: 200
        }, () => {
          this.openSelectedItemSystemMaterial = false;
        })
      } else {
      }
      this.getUIContext()?.animateTo({ curve: curve }, setAnimatedPropertyFunc);
    } else {
      setAnimatedPropertyFunc();
    }
    this.updateButtonFont();
  }

  updateButtonFont(): void {
    this.buttonItemsSelected.forEach((selected, index) => {
      const selectedFontSize = this.options.hasSelectedFontSize ? this.options.selectedFontSize :
        (this.useAdaptiveLineHeight ?
          segmentButtonTheme.ADAPTIVE_ITEM_FONT_SIZE :
          segmentButtonTheme.SELECTED_FONT_SIZE);
      const normalFontSize = this.options.hasFontSize ? this.options.fontSize :
        (this.useAdaptiveLineHeight ? segmentButtonTheme.ADAPTIVE_ITEM_FONT_SIZE : segmentButtonTheme.FONT_SIZE);
      this.buttonItemProperty[index].fontSize = selected ? selectedFontSize : normalFontSize;
      this.buttonItemProperty[index].fontWeight =
        selected ? this.options.selectedFontWeight ?? FontWeight.Medium :
          this.options.fontWeight ?? FontWeight.Regular;
      this.buttonItemProperty[index].isSelected = selected;
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
  switch (num) {
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

class SegmentButtonLayoutAlgorithm extends CustomLayoutAlgorithm {
  selectedIndex: int = -1
  componentPadding: double = 0
  multiply: boolean = false
  refHeight: double = 0
  selHeight: double = 0
  buttonWidth: double = 0
  rowSpace: double = 0
  shouldMirror: boolean = false
  buttonCount: int = 0

  getButtonX(index: int): double {
    const effectiveIndex = this.shouldMirror ? this.buttonCount - 1 - index : index
    return this.componentPadding + (this.buttonWidth + this.rowSpace) * effectiveIndex
  }

  onMeasure(self: FrameNode, constraint: LayoutConstraint): void {
    const childCount = self.getChildrenCount()
    if (childCount === 0) {
      self.setMeasuredSize({ width: 0, height: 0 } as Size)
      return
    }
    const buttonLayer = self.getChild(childCount - 1)
    if (buttonLayer) {
      buttonLayer.measure(constraint)
    }
    const refSize: Size = buttonLayer ? buttonLayer.getMeasuredSize() : { width: 0, height: 0 } as Size

    let buttonWidth: double = 0
    if (buttonLayer) {
      this.buttonCount = buttonLayer.getChildrenCount()
      if (this.buttonCount > 0) {
        const contentWidth = refSize.width - 2 * this.componentPadding
        buttonWidth = (contentWidth - (this.buttonCount - 1) * this.rowSpace) / this.buttonCount
        if (buttonWidth < 0) {
          buttonWidth = 0
        }
      }
    }

    this.refHeight = refSize.height
    this.selHeight = Math.max(0, refSize.height - 2 * this.componentPadding)
    this.buttonWidth = buttonWidth

    const fullSizeConstraint: Size = { width: refSize.width, height: refSize.height } as Size

    const bgChild = self.getChild(0)
    if (bgChild) {
      const bgConstraint: LayoutConstraint = {
        maxSize: fullSizeConstraint,
        minSize: fullSizeConstraint,
        percentReference: constraint.percentReference
      }
      bgChild.measure(bgConstraint)
    }

    if (childCount >= 2) {
      const selChild = self.getChild(1)
      if (selChild) {
        if (this.multiply) {
          const fullConstraint: LayoutConstraint = {
            maxSize: fullSizeConstraint,
            minSize: fullSizeConstraint,
            percentReference: constraint.percentReference
          }
          selChild.measure(fullConstraint)
        } else {
          const selConstraint: LayoutConstraint = {
            maxSize: { width: this.buttonWidth, height: this.selHeight } as Size,
            minSize: { width: this.buttonWidth, height: this.selHeight } as Size,
            percentReference: constraint.percentReference
          }
          selChild.measure(selConstraint)
        }
      }
    }

    self.setMeasuredSize(refSize)
  }

  onLayout(self: FrameNode, position: NodePosition): void {
    const childCount = self.getChildrenCount()

    const bgChild = self.getChild(0)
    if (bgChild) {
      bgChild.layout({ x: 0.0, y: 0.0 } as NodePosition)
    }

    if (childCount >= 2) {
      const selChild = self.getChild(1)
      if (selChild) {
        if (this.multiply) {
          selChild.layout({ x: 0.0, y: 0.0 } as NodePosition)
        } else {
          const selIdx: int = this.selectedIndex > 0 ? this.selectedIndex : 0
          selChild.layout({ x: this.getButtonX(selIdx), y: this.componentPadding } as NodePosition)
        }
      }
    }

    const btnLayer = self.getChild(childCount - 1)
    if (btnLayer) {
      btnLayer.layout({ x: 0.0, y: 0.0 } as NodePosition)
    }

    self.setLayoutPosition({ x: position.x, y: position.y } as NodePosition)
  }
}