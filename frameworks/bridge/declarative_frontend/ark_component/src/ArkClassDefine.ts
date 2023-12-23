/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

/// <reference path='./import.ts' />

class ArkBorderStyle {
  type: boolean | undefined;
  style: BorderStyle | undefined;
  top: BorderStyle | undefined;
  right: BorderStyle | undefined;
  bottom: BorderStyle | undefined;
  left: BorderStyle | undefined;

  constructor() {
    this.type = undefined;
    this.style = undefined;
    this.top = undefined;
    this.right = undefined;
    this.bottom = undefined;
    this.left = undefined;
  }
  isEqual(another: ArkBorderStyle): boolean {
    return (
      this.type === another.type &&
      this.style === another.style &&
      this.top === another.top &&
      this.right === another.right &&
      this.bottom === another.bottom &&
      this.left === another.left
    );
  }
  parseBorderStyle(value: BorderStyle | EdgeStyles): boolean {
    if (typeof value === 'number') {
      this.style = value;
      this.type = true;
      return true;
    } else if (typeof value === 'object') {
      return this.parseEdgeStyles(value as EdgeStyles);
    }
    return false;
  }
  parseEdgeStyles(options: EdgeStyles): boolean {
    this.top = options.top;
    this.right = options.right;
    this.bottom = options.bottom;
    this.left = options.left;
    this.type = true;
    return true;
  }
}

class ArkBorderColor {
  leftColor: EdgeColors | ResourceColor;
  rightColor: EdgeColors | ResourceColor;
  topColor: EdgeColors | ResourceColor;
  bottomColor: EdgeColors | ResourceColor;

  constructor() {
    this.leftColor = undefined;
    this.rightColor = undefined;
    this.topColor = undefined;
    this.bottomColor = undefined;
  }

  isEqual(another: ArkBorderColor): boolean {
    return (
      this.leftColor === another.leftColor &&
      this.rightColor === another.rightColor &&
      this.topColor === another.topColor &&
      this.bottomColor === another.bottomColor
    );
  }
}

class ArkPosition {
  x: Length;
  y: Length;

  constructor() {
    this.x = undefined;
    this.y = undefined;
  }

  isEqual(another: ArkPosition): boolean {
    return this.x === another.x && this.y === another.y;
  }
}

class ArkBorderWidth {
  left: EdgeWidths | Length;
  right: EdgeWidths | Length;
  top: EdgeWidths | Length;
  bottom: EdgeWidths | Length;

  constructor() {
    this.left = undefined;
    this.right = undefined;
    this.top = undefined;
    this.bottom = undefined;
  }

  isEqual(another: ArkBorderWidth): boolean {
    return (
      this.left === another.left &&
      this.right === another.right &&
      this.top === another.top &&
      this.bottom === another.bottom
    );
  }
}

class ArkBorderRadius {
  topLeft: BorderRadiuses | Length;
  topRight: BorderRadiuses | Length;
  bottomLeft: BorderRadiuses | Length;
  bottomRight: BorderRadiuses | Length;

  constructor() {
    this.topLeft = undefined;
    this.topRight = undefined;
    this.bottomLeft = undefined;
    this.bottomRight = undefined;
  }

  isEqual(another: ArkBorderRadius): boolean {
    return (
      this.topLeft === another.topLeft &&
      this.topRight === another.topRight &&
      this.bottomLeft === another.bottomLeft &&
      this.bottomRight === another.bottomRight
    );
  }
}

class ArkLabelFont {
  size: number | string | undefined | Resource;
  weight: FontWeight | number | string | undefined;
  family: string | undefined | Resource;
  style: FontStyle | number | undefined;
  constructor() {
    this.size = undefined;
    this.weight = undefined;
    this.family = undefined;
    this.style = undefined;
  }

  isEqual(another: ArkLabelFont): boolean {
    return (
      this.size === another.size &&
      this.weight === another.weight &&
      this.family === another.family &&
      this.style === another.style
    );
  }
}

function deepCompareArrays(arr1: Array<any>, arr2: Array<any>): boolean {
  return (
    Array.isArray(arr1) &&
    Array.isArray(arr2) &&
    arr1.length === arr2.length &&
    arr1.every((value, index) => {
      if (Array.isArray(value) && Array.isArray(arr2[index])) {
        return deepCompareArrays(value, arr2[index]);
      } else {
        return value === arr2[index];
      }
    })
  );
}

class ArkLinearGradient {
  angle: number | string | undefined;
  direction: number | undefined;
  colors: Array<any>;
  repeating: boolean | undefined;

  constructor(angle: number | string | undefined,
    direction: number | undefined,
    colors: Array<any>,
    repeating: boolean | undefined) {
    this.angle = angle;
    this.direction = direction;
    this.colors = colors;
    this.repeating = repeating;
  }

  isEqual(another: ArkLinearGradient): boolean {
    return (
      this.angle === another.angle &&
      this.direction === another.direction &&
      deepCompareArrays(this.colors, another.colors) &&
      this.repeating === another.repeating
    );
  }
}

class ArkSweepGradient {
  center: Array<any>;
  start: number | string | undefined;
  end: number | string | undefined;
  rotation: number | string | undefined;
  colors: Array<any>;
  repeating: boolean | undefined;

  constructor(center: Array<any>,
    start: number | string | undefined,
    end: number | string | undefined,
    rotation: number | string | undefined,
    colors: Array<any>,
    repeating: boolean | undefined) {
    this.center = center;
    this.start = start;
    this.end = end;
    this.rotation = rotation;
    this.colors = colors;
    this.repeating = repeating;
  }

  isEqual(another: ArkSweepGradient): boolean {
    return (
      deepCompareArrays(this.center, another.center) &&
      this.start === another.start &&
      this.end === another.end &&
      this.rotation === another.rotation &&
      deepCompareArrays(this.colors, another.colors) &&
      this.repeating === another.repeating
    );
  }
}

class ArkForegroundBlurStyle {
  blurStyle: number | undefined;
  colorMode: number | undefined;
  adaptiveColor: number | undefined;
  scale: number | undefined;

  constructor() {
    this.blurStyle = undefined;
    this.colorMode = undefined;
    this.adaptiveColor = undefined;
    this.scale = undefined;
  }

  isEqual(another: ArkForegroundBlurStyle): boolean {
    return (
      this.blurStyle === another.blurStyle &&
      this.colorMode === another.colorMode &&
      this.adaptiveColor === another.adaptiveColor &&
      this.scale === another.scale
    );
  }
}

class ArkLinearGradientBlur {
  blurRadius: number | undefined;
  fractionStops: FractionStop[] | undefined;
  direction: number | undefined;

  constructor() {
    this.blurRadius = undefined;
    this.fractionStops = undefined;
    this.direction = undefined;
  }

  isEqual(another: ArkLinearGradientBlur): boolean {
    return (
      this.blurRadius === another.blurRadius &&
      deepCompareArrays(this.fractionStops, another.fractionStops) &&
      this.direction === another.direction
    );
  }
}

class ArkOverlay {
  value: string | CustomBuilder | undefined;
  align: number | undefined;
  offsetX: number | undefined;
  offsetY: number | undefined;
  hasOptions: boolean | undefined;
  hasOffset: boolean | undefined;

  constructor() {
    this.value = undefined;
    this.align = undefined;
    this.offsetX = undefined;
    this.offsetY = undefined;
    this.hasOptions = undefined;
    this.hasOffset = undefined;
  }

  private splitOption(options?: { align?: Alignment; offset?: { x?: number; y?: number } }): boolean {
    if (isUndefined(options)) {
      return true;
    }
    this.hasOptions = true;
    this.align = options.align;
    if (isUndefined(options.offset)) {
      return true;
    }
    this.hasOffset = true;
    this.offsetX = options.offset.x;
    this.offsetY = options.offset.y;
    return true;
  }

  splitOverlayValue(value: string | CustomBuilder,
    options?: { align?: Alignment; offset?: { x?: number; y?: number } }): boolean {
    if (typeof value === 'string') {
      this.value = value;
      return this.splitOption(options);
    }
    return false;
  }

  private isEqual(another: ArkOverlay): boolean {
    return ((this.value === another.value) && (this.align === another.align) &&
      (this.offsetX === another.offsetX) && (this.offsetY === another.offsetY) &&
      (this.hasOptions === another.hasOptions) && (this.hasOffset === another.hasOffset));
  }

  checkObjectDiff(another: ArkOverlay): boolean {
    return !this.isEqual(another);
  }
}

class ArkSharedTransition {
  id: string | undefined;
  options: sharedTransitionOptions | undefined;
  constructor() {
    this.id = undefined;
    this.options = undefined;
  }
  isEqual(another: ArkSharedTransition): boolean {
    return (this.id === another.id) && (this.options === another.options);
  }
}

class ArkListEdgeEffect {
  value: EdgeEffect;
  options?: EdgeEffectOptions | undefined;
  constructor() {
    this.value = undefined;
    this.options = undefined;
  }
  isEqual(another: ArkListEdgeEffect): boolean {
    return (this.value === another.value) &&
      (this.options === another.options);
  }
}

class ArkScrollEdgeEffect {
  value: EdgeEffect;
  options?: EdgeEffectOptions | undefined;
  constructor() {
    this.value = undefined;
    this.options = undefined;
  }
  isEqual(another: ArkScrollEdgeEffect): boolean {
    return (this.value === another.value) &&
      (this.options === another.options);
  }
}

class ArkMenuAlignType {
  alignType: number | MenuAlignType;
  dx: Length;
  dy: Length;

  constructor(alignType: MenuAlignType, offset?: Offset) {
    this.alignType = alignType;
    if (!isUndefined(offset) && isObject(offset)) {
      this.dx = offset.dx;
      this.dy = offset.dy;
    }
  }

  isEqual(another: ArkMenuAlignType): boolean {
    return this.alignType === another.alignType && this.dx === another.dx && this.dy === another.dy;
  }
}

class ArkSliderTips {
  showTip: boolean;
  tipText: string | ResourceStr;

  constructor(value: boolean, content?: string | ResourceStr) {
    this.showTip = value;
    this.tipText = content;
  }

  isEqual(another: ArkSliderTips): boolean {
    return this.showTip === another.showTip && this.tipText === another.tipText;
  }
}

class ArkRadioStyle {
  checkedBackgroundColor: number | undefined;
  uncheckedBorderColor: number | undefined;
  indicatorColor: number | undefined;

  constructor() {
    this.checkedBackgroundColor = undefined;
    this.uncheckedBorderColor = undefined;
    this.indicatorColor = undefined;
  }

  isEqual(another: ArkRadioStyle): boolean {
    return (
      this.checkedBackgroundColor === another.checkedBackgroundColor &&
      this.uncheckedBorderColor === another.uncheckedBorderColor &&
      this.indicatorColor === another.indicatorColor
    );
  }
}

class ArkStarStyle {
  backgroundUri: string | undefined;
  foregroundUri: string | undefined;
  secondaryUri: string | undefined;

  constructor() {
    this.backgroundUri = undefined;
    this.foregroundUri = undefined;
    this.secondaryUri = undefined;
  }

  isEqual(another: ArkStarStyle): boolean {
    return (
      this.backgroundUri === another.backgroundUri &&
      this.foregroundUri === another.foregroundUri &&
      this.secondaryUri === another.secondaryUri
    );
  }
}

class ArkBackgroundBlurStyle {
  blurStyle: number | undefined;
  colorMode: number | undefined;
  adaptiveColor: number | undefined;
  scale: number | undefined;

  constructor() {
    this.blurStyle = undefined;
    this.colorMode = undefined;
    this.adaptiveColor = undefined;
    this.scale = undefined;
  }

  isEqual(another: ArkBackgroundBlurStyle): boolean {
    return (
      this.blurStyle === another.blurStyle &&
      this.colorMode === another.colorMode &&
      this.adaptiveColor === another.adaptiveColor &&
      this.scale === another.scale
    );
  }
}


class ArkSelectedIndices {
  selectedValues: number[];

  constructor() {
    this.selectedValues = [];
  }

  compareArrays(arr1: number[], arr2: number[]): boolean {
    return (
      Array.isArray(arr1) &&
      Array.isArray(arr2) &&
      arr1.length === arr2.length &&
      arr1.every((value, index) => value === arr2[index])
    );
  }

  isEqual(another: ArkSelectedIndices): boolean {
    return this.compareArrays(this.selectedValues, another.selectedValues);
  }
}

class ArkBorder {
  arkWidth: ArkBorderWidth;
  arkColor: ArkBorderColor;
  arkRadius: ArkBorderRadius;
  arkStyle: ArkBorderStyle;

  constructor() {
    this.arkWidth = new ArkBorderWidth();
    this.arkColor = new ArkBorderColor();
    this.arkRadius = new ArkBorderRadius();
    this.arkStyle = new ArkBorderStyle();
  }
  isEqual(another: ArkBorder): boolean {
    return (
      this.arkWidth.isEqual(another.arkWidth) &&
      this.arkColor.isEqual(another.arkColor) &&
      this.arkRadius.isEqual(another.arkRadius) &&
      this.arkStyle.isEqual(another.arkStyle)
    );
  }

  checkObjectDiff(another: ArkBorder): boolean {
    return !this.isEqual(another);
  }
}

class ArkBackgroundImageSize {
  imageSize: ImageSize | undefined | SizeOptions;
  width: number | string | undefined | Resource;
  height: number | string | undefined | Resource;
  constructor() {
    this.imageSize = undefined;
    this.width = undefined;
    this.height = undefined;
  }
  isEqual(another: ArkBackgroundImageSize): boolean {
    return this.imageSize === another.imageSize && this.width === another.width && this.height === another.height;
  }
}

class ArkBackgroundImage {
  src: string | undefined | Resource;
  repeat: number | undefined;
  constructor() {
    this.src = undefined;
    this.repeat = undefined;
  }
  isEqual(another: ArkBackgroundImage): boolean {
    return this.src === another.src && this.repeat === another.repeat;
  }
}

class ArkGridColColumnOption implements Equable {
  xs?: number;
  sm?: number;
  md?: number;
  lg?: number;
  xl?: number;
  xxl?: number;
  constructor() {
    this.xs = undefined;
    this.sm = undefined;
    this.md = undefined;
    this.lg = undefined;
    this.xl = undefined;
    this.xxl = undefined;
  }
  isEqual(another: ArkGridColColumnOption): boolean {
    return (this.xs === another.xs &&
      this.sm === another.sm &&
      this.md === another.md &&
      this.lg === another.lg &&
      this.xl === another.xl &&
      this.xxl === another.xxl);
  }
}

class ArkPadding {
  top: Length | undefined;
  right: Length | undefined;
  bottom: Length | undefined;
  left: Length | undefined;
  constructor() {
    this.top = undefined;
    this.right = undefined;
    this.bottom = undefined;
    this.left = undefined;
  }
  isEqual(another: ArkPadding) {
    return (
      this.top === another.top &&
      this.right === another.right &&
      this.bottom === another.bottom &&
      this.left === another.left
    );
  }
}

class ArkBarMode {
  barMode: number;
  options?: ScrollableBarModeOptions | undefined;

  isEqual(another: ArkBarMode): boolean {
    return (this.barMode === another.barMode) && (this.options === another.options);
  }
}

class ArkDivider {
  divider: DividerStyle;

  isEqual(another: ArkDivider): boolean {
    return (this.divider === another.divider);
  }
}

class ArkBarGridAlign {
  barGridAlign: BarGridColumnOptions;

  isEqual(another: ArkBarGridAlign): boolean {
    return (this.barGridAlign === another.barGridAlign);
  }
}


class ArkScrollableBarModeOptions {
  value: ScrollableBarModeOptions;

  isEqual(another: ArkScrollableBarModeOptions): boolean {
    return (this.value === another.value);
  }
}

class ArkAlignRules {
  left: string | undefined;
  middle: string | undefined;
  right: string | undefined;
  top: string | undefined;
  center: string | undefined;
  bottom: string | undefined;
  constructor() {
    this.left = undefined;
    this.middle = undefined;
    this.right = undefined;
    this.top = undefined;
    this.center = undefined;
    this.bottom = undefined;
  }
  isEqual(another: ArkAlignRules) {
    return (
      this.left === another.left &&
      this.middle === another.middle &&
      this.right === another.right &&
      this.top === another.top &&
      this.center === another.center &&
      this.bottom === another.bottom
    );
  }
}

class ArkSafeAreaExpandOpts {
  type: string | number | undefined = undefined;
  edges: string | number | undefined = undefined;
  isEqual(another: ArkSafeAreaExpandOpts): boolean {
    return (this.type === another.type) && (this.edges === another.edges);
  }
}

class ArkButtonStyle {
  left?: number;
  top?: number;
  width?: number;
  height?: number;
  icons?: {
    shown?: string;
    hidden?: string;
    switching?: string;
  };
  constructor() {
    this.left = 16;
    this.top = 48;
    this.width = 24;
    this.height = 24;
    this.icons = {
      shown: undefined,
      hidden: undefined,
      switching: undefined
    };
  }
  isEqual(another: ArkButtonStyle): boolean {
    return (
      this.left === another.left &&
      this.top === another.top &&
      this.width === another.width &&
      this.height === another.height &&
      this.icons === another.icons
    );
  }
}

class ArkShadowInfoToArray {
  radius: (number | string)[];
  type: ShadowType[];
  color: (Color | string | Resource | ColoringStrategy)[];
  offsetX: (number | string)[];
  offsetY: (number | string)[];
  fill: boolean[];
  constructor() {
    this.radius = [];
    this.type = [];
    this.color = [];
    this.offsetX = [];
    this.offsetX = [];
    this.offsetY = [];
    this.fill = [];
  }
  isEqual(another: ArkShadowInfoToArray): boolean {
    return (this.radius === another.radius) &&
      (this.color === another.color) &&
      (this.offsetX === another.offsetX) &&
      (this.offsetY === another.offsetY) &&
      (this.fill === another.fill);
  }

  convertShadowOptions(value: ShadowOptions | Array<ShadowOptions>): boolean {
    if (Object.getPrototypeOf(value).constructor === Object) {
      if ((<ShadowOptions>value).radius === null || (<ShadowOptions>value).radius === undefined) {
        return false;
      } else {
        this.radius.push(<number | string>(<ShadowOptions>value).radius);
        this.type.push((<ShadowOptions>value).type);
        this.color.push((<ShadowOptions>value).color);
        this.offsetX.push(((<ShadowOptions>value).offsetX === undefined ||
          (<ShadowOptions>value).offsetX === null) ? 0 : <number | string>(<ShadowOptions>value).offsetX);
        this.offsetY.push(((<ShadowOptions>value).offsetY === undefined ||
          (<ShadowOptions>value).offsetY === null) ? 0 : <number | string>(<ShadowOptions>value).offsetY);
        this.fill.push(((<ShadowOptions>value).fill === undefined ||
          (<ShadowOptions>value).fill === null) ? false : (<ShadowOptions>value).fill);
        return true;
      }
    } else if (Object.getPrototypeOf(value).constructor === Array) {
      let isFlag: boolean = true;
      for (let item of (value as Array<ShadowOptions>)) {
        if (item.radius === undefined || item.radius === null) {
          isFlag = false;
          break;
        }
      }
      if (isFlag) {
        for (let objValue of (value as Array<ShadowOptions>)) {
          this.radius.push(<number | string>objValue.radius);
          this.type.push(objValue.type);
          this.color.push(objValue.color);
          this.offsetX.push((objValue.offsetX === undefined || objValue.offsetX === null) ? 0 : <number | string>objValue.offsetX);
          this.offsetY.push((objValue.offsetY === undefined || objValue.offsetY === null) ? 0 : <number | string>objValue.offsetY);
          this.fill.push((objValue.fill === undefined || objValue.fill === null) ? false : objValue.fill);
        }
        return true;
      } else {
        return false;
      }
    }
  }

  checkDiff(value: ShadowOptions, stageValue: ShadowOptions): boolean {
    if (!value || !stageValue || !value.radius || !stageValue.radius) {
      return true;
    }
    if (!((isResource(stageValue.radius) && isResource(value.radius) &&
      isResourceEqual(stageValue.radius, value.radius)) ||
      (isNumber(stageValue.radius) && isNumber(value.radius) &&
        stageValue.radius === value.radius))) {
      return true;
    }
    if (!(isNumber(stageValue.type) && isNumber(value.type) &&
      stageValue.type === value.type)) {
      return true;
    }
    if (!((isResource(stageValue.color) && isResource(value.color) &&
      isResourceEqual(stageValue.color, value.color)) ||
      (!isResource(stageValue.color) && !isResource(value.color) &&
        stageValue.color === value.color))) {
      return true;
    }
    if (!((isResource(stageValue.offsetX) && isResource(value.offsetX) &&
      isResourceEqual(stageValue.offsetX, value.offsetX)) ||
      (isNumber(stageValue.offsetX) && isNumber(value.offsetX) &&
        stageValue.offsetX === value.offsetX))) {
      return true;
    }
    if (!((isResource(stageValue.offsetY) && isResource(value.offsetY) &&
      isResourceEqual(stageValue.offsetY, value.offsetY)) ||
      (isNumber(stageValue.offsetY) && isNumber(value.offsetY) &&
        stageValue.offsetY === value.offsetY))) {
      return true;
    }
    if (!(isBoolean(stageValue.fill) && isBoolean(value.fill) &&
      stageValue.fill === value.fill)) {
      return true;
    }
    return false;
  }
}

class ArkSearchButton {
  value: string | undefined;
  fontSize: Length | undefined;
  fontColor: ResourceColor | undefined;
  constructor() {
    this.value = undefined;
    this.fontSize = undefined;
    this.fontColor = undefined;
  }
  isEqual(another: ArkSearchButton): boolean {
    return (this.value === another.value) &&
      (this.fontSize === another.fontSize) &&
      (this.fontColor === another.fontColor);
  }
}
class ArkImageFrameInfoToArray {
  arrSrc: Array<string> | undefined;
  arrWidth: Array<number | string> | undefined;
  arrHeight: Array<number | string> | undefined;
  arrTop: Array<number | string> | undefined;
  arrLeft: Array<number | string> | undefined;
  arrDuration: Array<number> | undefined;
  constructor() {
    this.arrSrc = [];
    this.arrWidth = [];
    this.arrHeight = [];
    this.arrTop = [];
    this.arrLeft = [];
    this.arrDuration = [];
  }
  isEqual(another: ArkImageFrameInfoToArray): boolean {
    return (this.arrSrc.toString() === another.arrSrc.toString()) &&
      (this.arrWidth.toString() === another.arrWidth.toString()) &&
      (this.arrHeight.toString() === another.arrHeight.toString()) &&
      (this.arrTop.toString() === another.arrTop.toString()) &&
      (this.arrLeft.toString() === another.arrLeft.toString()) &&
      (this.arrDuration.toString() === another.arrDuration.toString());
  }
}

class ArkEdgeAlign {
  alignType: number;
  offset?: Offset | undefined;

  constructor() {
    this.alignType = undefined;
    this.offset = undefined;
  }

  isEqual(another: ArkEdgeAlign): boolean {
    return (this.alignType === another.alignType && this.offset === another.offset);
  }
}

class ArkKeyBoardShortCut {
  value: string | number;
  keys: Array<ModifierKey>;
  action: () => void | undefined;

  constructor() {
    this.value = undefined;
    this.keys = undefined;
    this.action = undefined;
  }

  isEqual(another: ArkKeyBoardShortCut): boolean {
    return (this.value === another.value) && (this.keys === another.keys) &&
      (this.action === another.action);
  }
}

class ArkAlignStyle {
  indexerAlign: number;
  offset?: number | string | undefined | Resource;

  constructor() {
    this.indexerAlign = undefined;
    this.offset = undefined;
  }

  isEqual(another: ArkAlignStyle): boolean {
    return (this.indexerAlign === another.indexerAlign && this.offset === another.offset);
  }
}

class ArkNestedScrollOptions {
  scrollForward: NestedScrollMode | undefined;
  scrollBackward: NestedScrollMode | undefined;
  constructor() {
    this.scrollForward = undefined;
    this.scrollBackward = undefined;
  }
  isEqual(another: ArkNestedScrollOptions): boolean {
    return ((this.scrollForward === another.scrollForward) && (this.scrollBackward === another.scrollBackward));
  }
}

class ArkConstraintSizeOptions {
  minWidth?: Length | undefined;
  maxWidth?: Length | undefined;
  minHeight?: Length | undefined;
  maxHeight?: Length | undefined;

  constructor() {
    this.minWidth = undefined;
    this.maxWidth = undefined;
    this.minHeight = undefined;
    this.maxHeight = undefined;
  }

  isEqual(another: ArkConstraintSizeOptions): boolean {
    return (
      this.minWidth === another.minWidth &&
      this.maxWidth === another.maxWidth &&
      this.minHeight === another.minHeight &&
      this.maxHeight === another.maxHeight
    );
  }
}

class ArkTextAreaShowCounter {
  value: boolean;
  options?: any;
  constructor() {
    this.value = undefined;
    this.options = undefined;
  }
  isEqual(another: ArkTextAreaShowCounter): boolean {
    return (this.value === another.value) &&
      (this.options === another.options);
  }
}

class ArkDotIndicator extends DotIndicator {
  type: string | undefined;
  leftValue: Length | undefined;
  topValue: Length | undefined;
  rightValue: Length | undefined;
  bottomValue: Length | undefined;
  itemWidthValue: Length | undefined;
  itemHeightValue: Length | undefined;
  selectedItemWidthValue: Length | undefined;
  selectedItemHeightValue: Length | undefined;
  maskValue: boolean | undefined;
  colorValue: ResourceColor | undefined;
  selectedColorValue: ResourceColor | undefined;

  constructor() {
    super();
    this.type = undefined;
    this.leftValue = undefined;
    this.topValue = undefined;
    this.rightValue = undefined;
    this.bottomValue = undefined;
    this.itemWidthValue = undefined;
    this.itemHeightValue = undefined;
    this.selectedItemWidthValue = undefined;
    this.selectedItemHeightValue = undefined;
    this.maskValue = undefined;
    this.colorValue = undefined;
    this.selectedColorValue = undefined;
  }

  isEqual(another: ArkDotIndicator): boolean {
    return (
      this.type === another.type &&
      this.leftValue === another.leftValue &&
      this.topValue === another.topValue &&
      this.rightValue === another.rightValue &&
      this.bottomValue === another.bottomValue &&
      this.itemWidthValue === another.itemWidthValue &&
      this.itemHeightValue === another.itemHeightValue &&
      this.selectedItemWidthValue === another.selectedItemWidthValue &&
      this.selectedItemHeightValue === another.selectedItemHeightValue &&
      this.maskValue === another.maskValue &&
      this.colorValue === another.colorValue &&
      this.selectedColorValue === another.selectedColorValue
    );
  }
}

class ArkDigitIndicator extends DigitIndicator {
  type: string | undefined;
  leftValue: Length | undefined;
  topValue: Length | undefined;
  rightValue: Length | undefined;
  bottomValue: Length | undefined;
  fontColorValue: ResourceColor | undefined;
  selectedFontColorValue: ResourceColor | undefined;
  digitFontValue: ArkDigitFont | undefined;
  selectedDigitFontValue: ArkDigitFont | undefined;

  constructor() {
    super();
    this.type = undefined;
    this.leftValue = undefined;
    this.topValue = undefined;
    this.rightValue = undefined;
    this.bottomValue = undefined;
    this.fontColorValue = undefined;
    this.selectedFontColorValue = undefined;
    this.digitFontValue = undefined;
    this.selectedDigitFontValue = undefined;
  }

  isEqual(another: ArkDigitIndicator): boolean {
    return (
      this.type === another.type &&
      this.leftValue === another.leftValue &&
      this.topValue === another.topValue &&
      this.rightValue === another.rightValue &&
      this.bottomValue === another.bottomValue &&
      this.digitFontValue === another.digitFontValue &&
      this.selectedDigitFontValue === another.selectedDigitFontValue
    );
  }
}

class ArkDigitFont {
  size: Length | undefined;
  weight: number | FontWeight | string | undefined;

  constructor() {
    this.size = undefined;
    this.weight = undefined;
  }

  isEqual(another: ArkDigitFont): boolean {
    return this.size === another.size && this.weight === another.weight;
  }

  parseFontWeight(value: string | number | undefined) {
    const valueWeightMap = {
      [0]: 'lighter',
      [1]: 'normal',
      [2]: 'regular',
      [3]: 'medium',
      [4]: 'bold',
      [5]: 'bolder'
    };
    if (isUndefined(value)) {
      this.weight = '-';
    } else if (value in valueWeightMap) {
      this.weight = valueWeightMap[value];
    } else {
      this.weight = value.toString();
    }
    return this.weight;
  }
}

class ArkDisplayArrow {
  value: boolean | ArrowStyle;
  isHoverShow: boolean | undefined;

  constructor() {
    this.value = undefined;
    this.isHoverShow = undefined;
  }

  isEqual(another: ArkDisplayArrow): boolean {
    return this.value === another.value && this.isHoverShow === another.isHoverShow;
  }
}

class ArkGridEdgeEffect {
  value: EdgeEffect;
  options?: EdgeEffectOptions | undefined;
  constructor() {
    this.value = undefined;
    this.options = undefined;
  }
  isEqual(another: ArkGridEdgeEffect): boolean {
    return (this.value === another.value) &&
      (this.options === another.options);
  }
}

class ArkMesh {
  value: Array<any> | undefined;
  column: number | undefined;
  row: number | undefined;

  constructor() {
    this.value = undefined;
    this.column = undefined;
    this.row = undefined;
  }
  isEqual(another: ArkMesh): boolean {
    return (
      deepCompareArrays(this.value, another.value) &&
      this.column === another.column &&
      this.row === another.row
    );
  }
}

class ArkLanesOpt {
  lanesNum: number | undefined;
  minLength: Length | undefined;
  maxLength: Length | undefined;
  gutter?: undefined;
  constructor() {
    this.lanesNum = undefined;
    this.minLength = undefined;
    this.maxLength = undefined;
    this.gutter = undefined;
  }

  isEqual(another: ArkLanesOpt): boolean {
    return (this.lanesNum === another.lanesNum && this.minLength === another.minLength
      && this.maxLength === another.maxLength && this.gutter === another.gutter);
  }
}

class ArkScrollSnapOptions {
  snapAlign: ScrollSnapAlign;
  snapPagination: Dimension | Array<Dimension>;
  enableSnapToStart: boolean;
  enableSnapToEnd: boolean;
  constructor() {
    this.snapAlign = undefined;
    this.snapPagination = undefined;
    this.enableSnapToStart = undefined;
    this.enableSnapToEnd = undefined;
  }
  isEqual(another: ArkScrollSnapOptions): boolean {
    return ((this.snapAlign === another.snapAlign)
      && (this.snapPagination === another.snapPagination)
      && (this.enableSnapToStart === another.enableSnapToStart)
      && (this.enableSnapToEnd === another.enableSnapToEnd));
  }
}
