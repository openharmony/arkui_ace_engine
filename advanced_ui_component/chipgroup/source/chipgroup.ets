/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
import { SymbolGlyphModifier } from '@ohos.arkui.modifier';
import {
  AccessibilitySelectedType,
  Chip,
  ChipSize,
  ChipSuffixSymbolGlyphOptions,
  ChipSymbolGlyphOptions,
  CloseOptions,
  PrefixIconOptions,
  SuffixIconOptions
} from '@ohos.arkui.advanced.Chip';

interface ChipGroupTheme {
  itemStyle: ChipGroupStyleTheme;
  chipGroupSpace: ChipGroupSpaceOptions;
  chipGroupPadding: ChipGroupPaddingOptions
}

const noop = (selectedIndexes: Array<number>) => {
}
const colorStops: ([string, number])[] = [['rgba(0, 0, 0, 1)', 0], ['rgba(0, 0, 0, 0)', 1]]
const defaultTheme: ChipGroupTheme = {
  itemStyle: {
    size: ChipSize.NORMAL,
    backgroundColor: $r('sys.color.ohos_id_color_button_normal'),
    fontColor: $r('sys.color.ohos_id_color_text_primary'),
    selectedFontColor: $r('sys.color.ohos_id_color_text_primary_contrary'),
    selectedBackgroundColor: $r('sys.color.ohos_id_color_emphasize'),
    fillColor: $r('sys.color.ohos_id_color_secondary'),
    selectedFillColor: $r('sys.color.ohos_id_color_text_primary_contrary'),
  },
  chipGroupSpace: { itemSpace: 8, startSpace: 16, endSpace: 16 },
  chipGroupPadding: { top: 14, bottom: 14 }
}

const iconGroupSuffixTheme: IconGroupSuffixTheme = {
  backgroundColor: $r('sys.color.ohos_id_color_button_normal'),
  borderRadius: $r('sys.float.ohos_id_corner_radius_tips_instant_tip'),
  smallIconSize: 16,
  normalIconSize: 24,
  smallBackgroundSize: 28,
  normalBackgroundSize: 36,
  marginLeft: 8,
  marginRight: 16,
  fillColor: $r('sys.color.ohos_id_color_primary'),
  defaultEffect: -1
}

enum ChipGroupHeight {
  NORMAL = 36,
  SMALL = 28,
}

interface IconOptions {
  src: ResourceStr;
  size?: SizeOptions;
}

interface ChipGroupPaddingOptions {
  top: Length;
  bottom: Length;
}

interface ChipGroupStyleTheme {
  size: ChipSize | SizeOptions;
  backgroundColor: ResourceColor;
  fontColor: ResourceColor;
  selectedFontColor: ResourceColor;
  selectedBackgroundColor: ResourceColor;
  fillColor: ResourceColor;
  selectedFillColor: ResourceColor;
}

interface LabelOptions {
  text: string;
}

export interface SuffixImageIconOptions extends IconOptions {
  action?: VoidCallback;
  accessibilityText?: ResourceStr;
  accessibilityDescription?: ResourceStr;
  accessibilityLevel?: string;
}

export interface ChipGroupItemOptions {
  prefixIcon?: IconOptions;
  prefixSymbol?: ChipSymbolGlyphOptions;
  label: LabelOptions;
  suffixIcon?: IconOptions;
  suffixImageIcon?: SuffixImageIconOptions;
  suffixSymbol?: ChipSymbolGlyphOptions;
  suffixSymbolOptions?: ChipSuffixSymbolGlyphOptions;
  allowClose?: boolean;
  closeOptions?: CloseOptions;
  accessibilityDescription?: ResourceStr;
  accessibilityLevel?: string;
}

export interface ChipItemStyle {
  size?: ChipSize | SizeOptions;
  backgroundColor?: ResourceColor;
  fontColor?: ResourceColor;
  selectedFontColor?: ResourceColor;
  selectedBackgroundColor?: ResourceColor;
}

interface ChipGroupSpaceOptions {
  itemSpace?: number | string;
  startSpace?: Length;
  endSpace?: Length;
}

export interface IconItemOptions {
  icon: IconOptions;
  action: Callback<void>;
  accessibilityText?: ResourceStr;
  accessibilityDescription?: ResourceStr;
  accessibilityLevel?: string;
}

export interface SymbolItemOptions {
  symbol: SymbolGlyphModifier;
  action: VoidCallback;
  accessibilityText?: ResourceStr;
  accessibilityDescription?: ResourceStr;
  accessibilityLevel?: string;
}

interface IconGroupSuffixTheme {
  smallIconSize: number;
  normalIconSize: number;
  backgroundColor: ResourceColor;
  smallBackgroundSize: number;
  normalBackgroundSize: number;
  borderRadius: Dimension;
  marginLeft: number;
  marginRight: number;
  fillColor: ResourceColor;
  defaultEffect: number;
}

function parseDimension<T>(
  uiContext: UIContext,
  value: Dimension | Length | undefined,
  isValid: Callback<string, boolean>,
  defaultValue: T
): T {
  if (value === void (0) || value === null) {
    return defaultValue;
  }
  const resourceManager = uiContext.getHostContext()?.resourceManager;
  if (!resourceManager) {
    return defaultValue;
  }
  if (typeof value === 'object') {
    let temp: Resource = value as Resource;
    if (temp.type === 10002 || temp.type === 10007) {
      if (resourceManager && resourceManager.getNumber(temp.id) >= 0) {
        return value as T;
      }
    } else if (temp.type === 10003) {
      if (resourceManager && isValidDimensionString(resourceManager.getStringSync(temp.id))) {
        return value as T;
      }
    }
  } else if (typeof value === 'number') {
    if (value >= 0) {
      return value as T;
    }
  } else if (typeof value === 'string') {
    if (isValid(value)) {
      return value as T;
    }
  }
  return defaultValue;
}

function isValidString(dimension: string, regex: RegExp): boolean {
  const matches = dimension.match(regex);
  if (!matches || matches.length < 3) {
    return false;
  }
  const value = Number.parseFloat(matches[1]);
  return value >= 0;
}

function isValidDimensionString(dimension: string): boolean {
  return isValidString(dimension, new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$', 'i'));
}

function isValidDimensionNoPercentageString(dimension: string): boolean {
  return isValidString(dimension, new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx)?$', 'i'));
}

@Component
export struct IconGroupSuffix {
  @Consume chipSize: ChipSize | SizeOptions;
  @Prop items: Array<IconItemOptions | SymbolGlyphModifier | SymbolItemOptions> = [];
  symbolEffect: SymbolEffect = new SymbolEffect();

  private getBackgroundSize(): number {
    if (this.chipSize === ChipSize.SMALL) {
      return iconGroupSuffixTheme.smallBackgroundSize;
    } else {
      return iconGroupSuffixTheme.normalBackgroundSize;
    }
  }

  private getIconSize(val?: Length): Length {
    if (val === undefined) {
      return this.chipSize === ChipSize.SMALL ?
      iconGroupSuffixTheme.smallIconSize :
      iconGroupSuffixTheme.normalIconSize;
    }
    let value: Length;
    if (this.chipSize === ChipSize.SMALL) {
      value = parseDimension(this.getUIContext(), val, isValidDimensionString, iconGroupSuffixTheme.smallIconSize);
    } else {
      value = parseDimension(this.getUIContext(), val, isValidDimensionString, iconGroupSuffixTheme.normalIconSize);
    }
    return value;
  }

  @Builder
  SymbolItemBuilder(item: SymbolItemOptions) {
    SymbolGlyph()
      .fontColor([iconGroupSuffixTheme.fillColor])
      .fontSize(this.getIconSize())
      .attributeModifier(item.symbol)
      .focusable(true)
      .effectStrategy(SymbolEffectStrategy.NONE)
      .symbolEffect(this.symbolEffect, false)
      .symbolEffect(this.symbolEffect, iconGroupSuffixTheme.defaultEffect)
  }

  @Builder
  IconItemBuilder(item: IconItemOptions) {
    Image(item.icon.src)
      .fillColor(iconGroupSuffixTheme.fillColor)
      .size({
        width: this.getIconSize(item.icon.size?.width),
        height: this.getIconSize(item.icon.size?.height)
      })
      .focusable(true)
  }

  build() {
    Row({ space: 8 }) {
      ForEach(this.items || [], (suffixItem: IconItemOptions | SymbolGlyphModifier | SymbolItemOptions) => {
        Button() {
          if (suffixItem instanceof SymbolGlyphModifier) {
            SymbolGlyph()
              .fontColor([iconGroupSuffixTheme.fillColor])
              .fontSize(this.getIconSize())
              .attributeModifier(suffixItem)
              .focusable(true)
              .effectStrategy(SymbolEffectStrategy.NONE)
              .symbolEffect(this.symbolEffect, false)
              .symbolEffect(this.symbolEffect, iconGroupSuffixTheme.defaultEffect)
          } else if (this.isSymbolItem(suffixItem)) {
            this.SymbolItemBuilder(suffixItem as SymbolItemOptions)
          } else {
            this.IconItemBuilder(suffixItem as IconItemOptions)
          }
        }
        .size({
          width: this.getBackgroundSize(),
          height: this.getBackgroundSize()
        })
        .backgroundColor(iconGroupSuffixTheme.backgroundColor)
        .borderRadius(iconGroupSuffixTheme.borderRadius)
        .accessibilityText(this.getAccessibilityText(suffixItem))
        .accessibilityDescription(this.getAccessibilityDescription(suffixItem))
        .accessibilityLevel(this.getAccessibilityLevel(suffixItem))
        .onClick(() => {
          if (!(suffixItem instanceof SymbolGlyphModifier)) {
            suffixItem.action();
          }
        })
        .borderRadius(iconGroupSuffixTheme.borderRadius)
      })
    }
  }

  private isSymbolItem(item: IconItemOptions | SymbolItemOptions): boolean {
    return typeof (item as SymbolItemOptions).symbol !== 'undefined';
  }

  private getAccessibilityLevel(item: IconItemOptions | SymbolGlyphModifier | SymbolItemOptions): string {
    if (item instanceof SymbolGlyphModifier) {
      return 'auto';
    }
    return item.accessibilityLevel ?? 'auto';
  }

  private getAccessibilityDescription(
    item: IconItemOptions | SymbolGlyphModifier | SymbolItemOptions
  ): Resource | undefined {
    if (item instanceof SymbolGlyphModifier || typeof item.accessibilityDescription === 'undefined') {
      return undefined;
    }
    return item.accessibilityDescription as ESObject as Resource;
  }

  private getAccessibilityText(item: IconItemOptions | SymbolGlyphModifier | SymbolItemOptions): Resource | undefined {
    if (item instanceof SymbolGlyphModifier || typeof item.accessibilityText === 'undefined') {
      return undefined;
    }
    return item.accessibilityText as ESObject as Resource;
  }
}

@Component
export struct ChipGroup {
  @Prop @Watch('onItemsChange') items: ChipGroupItemOptions[] = [];
  @Prop @Watch('itemStyleOnChange') itemStyle: ChipItemStyle = defaultTheme.itemStyle;
  @Provide chipSize: ChipSize | SizeOptions = defaultTheme.itemStyle.size;
  @Prop selectedIndexes: Array<number> = [0];
  @Prop @Watch('onMultipleChange') multiple: boolean = false;
  @Prop chipGroupSpace: ChipGroupSpaceOptions = defaultTheme.chipGroupSpace;
  @BuilderParam suffix?: Callback<void>;
  public onChange: Callback<Array<number>> = noop;
  private scroller: Scroller = new Scroller();
  @State isReachEnd: boolean = this.scroller.isAtEnd();
  @Prop chipGroupPadding: ChipGroupPaddingOptions = defaultTheme.chipGroupPadding;
  @State isRefresh: boolean = true;

  onItemsChange() {
    this.isRefresh = !this.isRefresh;
  }

  onMultipleChange() {
    this.selectedIndexes = this.getSelectedIndexes();
  }

  itemStyleOnChange() {
    this.chipSize = this.getChipSize();
  }

  aboutToAppear() {
    this.itemStyleOnChange();
    if (this.getSelectedIndexes().length === 0) {
      this.selectedIndexes = [0];
    }
  }

  private getChipSize(): ChipSize | SizeOptions {
    if (this.itemStyle && this.itemStyle.size) {
      if (typeof this.itemStyle.size === 'object') {
        if (!this.itemStyle.size.width || !this.itemStyle.size.height || !this.itemStyle.size) {
          return defaultTheme.itemStyle.size;
        }
      }
      return this.itemStyle.size;
    }
    return defaultTheme.itemStyle.size;
  }

  private getFontColor(): ResourceColor {
    if (this.itemStyle && this.itemStyle.fontColor) {
      if (typeof this.itemStyle.fontColor === 'object') {
        let temp: Resource = this.itemStyle.fontColor as Resource;
        if (temp == undefined || temp == null) {
          return defaultTheme.itemStyle.fontColor;
        }
        if (temp.type === 10001) {
          return this.itemStyle.fontColor;
        }
        return defaultTheme.itemStyle.fontColor;
      }
      return this.itemStyle.fontColor;
    }
    return defaultTheme.itemStyle.fontColor;
  }

  private getSelectedFontColor(): ResourceColor {
    if (this.itemStyle && this.itemStyle.selectedFontColor) {
      if (typeof this.itemStyle.selectedFontColor === 'object') {
        let temp: Resource = this.itemStyle.selectedFontColor as Resource;
        if (temp == undefined || temp == null) {
          return defaultTheme.itemStyle.selectedFontColor;
        }
        if (temp.type === 10001) {
          return this.itemStyle.selectedFontColor;
        }
        return defaultTheme.itemStyle.selectedFontColor;
      }
      return this.itemStyle.selectedFontColor;
    }
    return defaultTheme.itemStyle.selectedFontColor;
  }

  private getFillColor(): ResourceColor {
    if (this.itemStyle && this.itemStyle.fontColor) {
      return this.itemStyle.fontColor;
    }
    return defaultTheme.itemStyle.fillColor;
  }

  private getSelectedFillColor(): ResourceColor {
    if (this.itemStyle && this.itemStyle.selectedFontColor) {
      return this.itemStyle.selectedFontColor;
    }
    return defaultTheme.itemStyle.selectedFillColor;
  }

  private getBackgroundColor(): ResourceColor {
    if (this.itemStyle && this.itemStyle.backgroundColor) {
      if (typeof this.itemStyle.backgroundColor === 'object') {
        let temp: Resource = this.itemStyle.backgroundColor as Resource;
        if (temp == undefined || temp == null) {
          return defaultTheme.itemStyle.backgroundColor;
        }
        if (temp.type === 10001) {
          return this.itemStyle.backgroundColor;
        }
        return defaultTheme.itemStyle.backgroundColor;
      }
      return this.itemStyle.backgroundColor;
    }
    return defaultTheme.itemStyle.backgroundColor;
  }

  private getSelectedBackgroundColor(): ResourceColor {
    if (this.itemStyle && this.itemStyle.selectedBackgroundColor) {
      if (typeof this.itemStyle.selectedBackgroundColor === 'object') {
        let temp: Resource = this.itemStyle.selectedBackgroundColor as Resource;
        if (temp == undefined || temp == null) {
          return defaultTheme.itemStyle.selectedBackgroundColor;
        }
        if (temp.type === 10001) {
          return this.itemStyle.selectedBackgroundColor;
        }
        return defaultTheme.itemStyle.selectedBackgroundColor;
      }
      return this.itemStyle.selectedBackgroundColor;
    }
    return defaultTheme.itemStyle.selectedBackgroundColor;
  }

  private getSelectedIndexes(): Array<number> {
    let temp: number[] = [];
    temp = (this.selectedIndexes ?? [0]).filter(
      (element, index, array) => {
        return (
          element >= 0 &&
            element % 1 == 0 &&
            element != null &&
            element != undefined &&
            array.indexOf(element) === index &&
            element < (this.items || []).length);
      });
    return temp;
  }

  private isMultiple(): boolean {
    return this.multiple ?? false;
  }

  private getChipGroupItemSpace() {
    if (this.chipGroupSpace == undefined) {
      return defaultTheme.chipGroupSpace.itemSpace
    }
    return parseDimension(
      this.getUIContext(),
      this.chipGroupSpace.itemSpace,
      isValidDimensionNoPercentageString,
      defaultTheme.chipGroupSpace.itemSpace
    );
  }

  private getChipGroupStartSpace() {
    if (this.chipGroupSpace == undefined) {
      return defaultTheme.chipGroupSpace.startSpace
    }
    return parseDimension(
      this.getUIContext(),
      this.chipGroupSpace.startSpace,
      isValidDimensionNoPercentageString,
      defaultTheme.chipGroupSpace.startSpace
    );
  }

  private getChipGroupEndSpace() {
    if (this.chipGroupSpace == undefined) {
      return defaultTheme.chipGroupSpace.endSpace
    }
    return parseDimension(
      this.getUIContext(),
      this.chipGroupSpace.endSpace,
      isValidDimensionNoPercentageString,
      defaultTheme.chipGroupSpace.endSpace
    );
  }

  private getOnChange(): (selectedIndexes: Array<number>) => void {
    return this.onChange ?? noop;
  }

  private isSelected(itemIndex: number): boolean {
    if (!this.isMultiple()) {
      return itemIndex == this.getSelectedIndexes()[0];
    } else {
      return this.getSelectedIndexes().some((element, index, array) => {
        return (element == itemIndex);
      })
    }
  }

  private getPaddingTop() {
    if (!this.chipGroupPadding || !this.chipGroupPadding.top) {
      return defaultTheme.chipGroupPadding.top
    }
    return parseDimension(
      this.getUIContext(),
      this.chipGroupPadding.top,
      isValidDimensionNoPercentageString,
      defaultTheme.chipGroupPadding.top
    );
  }

  private getPaddingBottom() {
    if (!this.chipGroupPadding || !this.chipGroupPadding.bottom) {
      return defaultTheme.chipGroupPadding.bottom
    }
    return parseDimension(
      this.getUIContext(),
      this.chipGroupPadding.bottom,
      isValidDimensionNoPercentageString,
      defaultTheme.chipGroupPadding.bottom
    );
  }

  private getChipGroupHeight() {
    if (typeof this.chipSize === 'string') {
      if (this.chipSize === ChipSize.NORMAL) {
        return ChipGroupHeight.NORMAL;
      } else {
        return ChipGroupHeight.SMALL;
      }
    } else if (typeof this.chipSize === 'object') {
      return this.chipSize.height as number
    } else {
      return ChipGroupHeight.NORMAL
    }
  }

  build() {
    Row() {
      Stack() {
        Scroll(this.scroller) {
          Row({ space: this.getChipGroupItemSpace() }) {
            ForEach(this.items || [], (chipItem: ChipGroupItemOptions, index) => {
              if (chipItem) {
                Chip({
                  prefixIcon: this.getPrefixIcon(chipItem),
                  prefixSymbol: chipItem?.prefixSymbol,
                  label: {
                    text: chipItem?.label?.text ?? ' ',
                    fontColor: this.getFontColor(),
                    activatedFontColor: this.getSelectedFontColor(),
                  },
                  suffixIcon: this.getSuffixIcon(chipItem),
                  suffixSymbol: chipItem?.suffixSymbol,
                  suffixSymbolOptions: chipItem.suffixSymbolOptions,
                  allowClose: chipItem.allowClose ?? false,
                  closeOptions: chipItem.closeOptions,
                  enabled: true,
                  activated: this.isSelected(index),
                  backgroundColor: this.getBackgroundColor(),
                  size: this.getChipSize(),
                  activatedBackgroundColor: this.getSelectedBackgroundColor(),
                  accessibilitySelectedType:
                  this.multiple ? AccessibilitySelectedType.CHECKED : AccessibilitySelectedType.SELECTED,
                  accessibilityDescription: chipItem.accessibilityDescription,
                  accessibilityLevel: chipItem.accessibilityLevel,
                  onClicked: () => {
                    if (this.isSelected(index)) {
                      if (!(!this.isMultiple())) {
                        if (this.getSelectedIndexes().length > 1) {
                          this.selectedIndexes.splice(this.selectedIndexes.indexOf(index), 1);
                        }
                      }
                    } else {
                      if (!this.selectedIndexes || this.selectedIndexes.length === 0) {
                        this.selectedIndexes = this.getSelectedIndexes();
                      }
                      if (!this.isMultiple()) {
                        this.selectedIndexes = [];
                      }
                      this.selectedIndexes.push(index);
                    }
                    this.getOnChange()(this.getSelectedIndexes());
                  }
                })
              }
            }, () => {
              return JSON.stringify(this.isRefresh);
            });
          }
          .padding({
            left: this.getChipGroupStartSpace(),
            right: this.getChipGroupEndSpace()
          })
          .constraintSize({ minWidth: '100%' })
        }
        .scrollable(ScrollDirection.Horizontal)
        .scrollBar(BarState.Off)
        .align(Alignment.Start)
        .width('100%')
        .clip(false)
        .onScroll(() => {
          this.isReachEnd = this.scroller.isAtEnd();
        })

        if (this.suffix && !this.isReachEnd) {
          Stack()
            .width(iconGroupSuffixTheme.normalBackgroundSize)
            .height(this.getChipGroupHeight())
            .linearGradient({ angle: 90, colors: colorStops })
            .blendMode(BlendMode.DST_IN, BlendApplyType.OFFSCREEN)
            .hitTestBehavior(HitTestMode.None)
        }
      }
      .padding({ top: this.getPaddingTop(), bottom: this.getPaddingBottom() })
      .layoutWeight(1)
      .blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN)
      .alignContent(Alignment.End)

      if (this.suffix) {
        Row() {
          this.suffix();
        }.padding({
          left: iconGroupSuffixTheme.marginLeft,
          right: iconGroupSuffixTheme.marginRight
        })
      }
    }
    .align(Alignment.End)
    .width('100%')
  }

  getPrefixIcon(chipItem: ChipGroupItemOptions): PrefixIconOptions {
    return {
      src: chipItem.prefixIcon?.src ?? '',
      size: chipItem.prefixIcon?.size ?? undefined,
      fillColor: this.getFillColor(),
      activatedFillColor: this.getSelectedFillColor()
    };
  }

  private getSuffixIcon(chipItem: ChipGroupItemOptions): SuffixIconOptions {
    if (typeof chipItem.suffixImageIcon !== 'undefined') {
      return {
        src: chipItem.suffixImageIcon.src,
        size: chipItem.suffixImageIcon.size,
        fillColor: this.getFillColor(),
        activatedFillColor: this.getSelectedFillColor(),
        action: chipItem.suffixImageIcon.action,
        accessibilityText: chipItem.suffixImageIcon.accessibilityText,
        accessibilityDescription: chipItem.suffixImageIcon.accessibilityDescription,
        accessibilityLevel: chipItem.suffixImageIcon.accessibilityLevel,
      };
    }
    return {
      src: chipItem.suffixIcon?.src ?? '',
      size: chipItem.suffixIcon?.size ?? undefined,
      fillColor: this.getFillColor(),
      activatedFillColor: this.getSelectedFillColor()
    };
  }
}
