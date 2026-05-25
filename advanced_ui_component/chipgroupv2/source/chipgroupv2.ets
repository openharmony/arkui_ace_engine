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

import { SymbolGlyphModifier } from '@ohos.arkui.modifier';
import {
  ChipV2Size,
  ChipV2ImageIconConfig,
  ChipV2SuffixImageIconConfig,
  ChipV2PrefixImageIconConfig,
  ChipV2LabelConfig,
  ChipV2CloseConfig,
  ChipV2SymbolIconConfig,
  ChipV2PrefixSymbolIconConfig,
  ChipV2SuffixSymbolIconConfig,
  ChipV2AccessibilityConfig,
  ChipV2ImageIcon,
  ChipV2SuffixImageIcon,
  ChipV2PrefixImageIcon,
  ChipV2Label,
  ChipV2CloseIcon,
  ChipV2SymbolIcon,
  ChipV2PrefixSymbolIcon,
  ChipV2SuffixSymbolIcon,
  ChipV2,
  ChipV2Options,
  ChipV2AccessibilitySelectedType,
  ChipV2Icon
} from '@kit.ArkUI';
import uiMaterial from '@ohos.arkui.uiMaterial';
import { LengthMetrics, LengthUnit, ColorMetrics } from '@kit.ArkUI';
import deviceInfo from '@ohos.deviceInfo';

interface ChipGroupV2Theme {
  itemStyle: ChipGroupV2ItemStyleConfig;
  chipGroupSpace: ChipGroupV2SpaceConfig;
  chipGroupPadding: ChipGroupV2PaddingConfig;
  itemFillColor: ColorMetrics;
  itemSelectedFillColor: ColorMetrics;
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

const noop = (selectedIndexes: Array<number>) => {
}

const colorStops: ([string, number])[] = [['rgba(0, 0, 0, 1)', 0], ['rgba(0, 0, 0, 0)', 1]];

const defaultTheme: ChipGroupV2Theme = {
  itemStyle: {
    size: ChipV2Size.NORMAL,
    backgroundColor: ColorMetrics.resourceColor($r('sys.color.ohos_id_color_button_normal')),
    fontColor: ColorMetrics.resourceColor($r('sys.color.ohos_id_color_text_primary')),
    selectedFontColor: ColorMetrics.resourceColor($r('sys.color.ohos_id_color_text_primary_contrary')),
    selectedBackgroundColor: ColorMetrics.resourceColor($r('sys.color.ohos_id_color_emphasize')),
  },
  chipGroupSpace: { itemSpace: 8, startSpace: 16, endSpace: 16 },
  chipGroupPadding: { top: 14, bottom: 14 },
  itemFillColor: ColorMetrics.resourceColor($r('sys.color.ohos_id_color_secondary')),
  itemSelectedFillColor: ColorMetrics.resourceColor($r('sys.color.ohos_id_color_text_primary_contrary'))
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

export interface ChipGroupV2ItemConfig {
  prefixIcon?: ChipV2PrefixImageIconConfig;
  prefixSymbolIcon?: ChipV2PrefixSymbolIconConfig;
  label: ChipV2LabelConfig;
  suffixIcon?: ChipV2SuffixImageIconConfig;
  suffixSymbolIcon?: ChipV2SuffixSymbolIconConfig;
  allowClose?: boolean;
  closeIcon?: ChipV2CloseConfig;
  accessibilityDescription?: ResourceStr;
  accessibilityLevel?: string;
}

@ObservedV2
export class ChipGroupV2Item {
  @Trace public prefixIcon?: ChipV2PrefixImageIcon;
  @Trace public prefixSymbolIcon?: ChipV2PrefixSymbolIcon;
  @Trace public label: ChipV2Label;
  @Trace public suffixIcon?: ChipV2SuffixImageIcon;
  @Trace public suffixSymbolIcon?: ChipV2SuffixSymbolIcon;
  @Trace public allowClose?: boolean;
  @Trace public closeIcon?: ChipV2CloseConfig;
  @Trace public accessibilityDescription?: ResourceStr;
  @Trace public accessibilityLevel?: string;

  constructor(config: ChipGroupV2ItemConfig) {
    this.prefixIcon = config.prefixIcon ? new ChipV2PrefixImageIcon(config.prefixIcon) : undefined;
    this.prefixSymbolIcon = config.prefixSymbolIcon ? new ChipV2PrefixSymbolIcon(config.prefixSymbolIcon) : undefined;
    this.label = new ChipV2Label(config.label);
    this.suffixIcon = config.suffixIcon ? new ChipV2SuffixImageIcon(config.suffixIcon) : undefined;
    this.suffixSymbolIcon = config.suffixSymbolIcon ? new ChipV2SuffixSymbolIcon(config.suffixSymbolIcon) : undefined;
    this.allowClose = config.allowClose;
    this.closeIcon = config.closeIcon;
    this.accessibilityDescription = config.accessibilityDescription;
    this.accessibilityLevel = config.accessibilityLevel;
  }
}

@ObservedV2
export class ChipGroupV2Items extends Array<ChipGroupV2Item> {
  constructor(items: ChipGroupV2ItemConfig[]) {
    super();
    items.forEach(item => this.push(new ChipGroupV2Item(item)));
  }
}

export interface ChipGroupV2ItemStyleConfig {
  size?: ChipV2Size | SizeT<LengthMetrics>;
  backgroundColor?: ColorMetrics;
  fontColor?: ColorMetrics;
  selectedFontColor?: ColorMetrics;
  selectedBackgroundColor?: ColorMetrics;
  backgroundSystemMaterial?: uiMaterial.Material;
}

@ObservedV2
export class ChipGroupV2ItemStyle {
  @Trace public size?: ChipV2Size | SizeT<LengthMetrics>;
  @Trace public backgroundColor?: ColorMetrics;
  @Trace public fontColor?: ColorMetrics;
  @Trace public selectedFontColor?: ColorMetrics;
  @Trace public selectedBackgroundColor?: ColorMetrics;
  @Trace public backgroundSystemMaterial?: uiMaterial.Material;

  constructor(config: ChipGroupV2ItemStyleConfig) {
    this.size = config.size;
    this.backgroundColor = config.backgroundColor;
    this.fontColor = config.fontColor;
    this.selectedFontColor = config.selectedFontColor;
    this.selectedBackgroundColor = config.selectedBackgroundColor;
    this.backgroundSystemMaterial = config.backgroundSystemMaterial;
  }
}

export interface ChipGroupV2SpaceConfig {
  itemSpace?: string | number;
  startSpace?: Length;
  endSpace?: Length;
}

@ObservedV2
export class ChipGroupV2Space {
  @Trace public itemSpace?: string | number;
  @Trace public startSpace?: Length;
  @Trace public endSpace?: Length;

  constructor(config: ChipGroupV2SpaceConfig) {
    this.itemSpace = config.itemSpace;
    this.startSpace = config.startSpace;
    this.endSpace = config.endSpace;
  }
}

export interface ChipGroupV2IconItemConfig {
  icon: ChipV2ImageIconConfig;
  action: Callback<void>;
  accessibilityText?: ResourceStr;
  accessibilityDescription?: ResourceStr;
  accessibilityLevel?: string;
}

export interface ChipGroupV2SymbolItemConfig {
  symbol: SymbolGlyphModifier;
  action: VoidCallback;
  accessibilityText?: ResourceStr;
  accessibilityDescription?: ResourceStr;
  accessibilityLevel?: string;
}

export interface ChipGroupV2PaddingConfig {
  top: Length;
  bottom: Length;
}

@ObservedV2
export class ChipGroupV2Padding {
  @Trace public top: Length;
  @Trace public bottom: Length;

  constructor(config: ChipGroupV2PaddingConfig) {
    this.top = config.top;
    this.bottom = config.bottom;
  }
}

@ComponentV2
export struct ChipGroupV2IconGroupSuffix {
  @Require @Param items: Array<ChipGroupV2IconItemConfig | SymbolGlyphModifier | ChipGroupV2SymbolItemConfig> = [];
  @Param iconBackgroundSystemMaterial?: uiMaterial.Material = undefined;
  @Consumer() chipSize: ChipV2Size | SizeT<LengthMetrics> = ChipV2Size.NORMAL;
  @Local symbolEffect: SymbolEffect = new SymbolEffect();

  private getBackgroundSize(): number {
    if (this.chipSize === ChipV2Size.SMALL) {
      return iconGroupSuffixTheme.smallBackgroundSize;
    } else {
      return iconGroupSuffixTheme.normalBackgroundSize;
    }
  }

  private getIconSize(val?: LengthMetrics): Length {
    if (val === undefined) {
      return this.chipSize === ChipV2Size.SMALL ?
        iconGroupSuffixTheme.smallIconSize :
        iconGroupSuffixTheme.normalIconSize;
    }
    let value: Length;
    if (this.chipSize === ChipV2Size.SMALL) {
      value = parseDimension(this.getUIContext(), lengthMetricsToLength(val),
        isValidDimensionString, iconGroupSuffixTheme.smallIconSize);
    } else {
      value = parseDimension(this.getUIContext(), lengthMetricsToLength(val),
        isValidDimensionString, iconGroupSuffixTheme.normalIconSize);
    }
    return value;
  }

  @Builder
  SymbolItemBuilder(item: ChipGroupV2SymbolItemConfig) {
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
  IconItemBuilder(item: ChipGroupV2IconItemConfig) {
    Image(item.icon.src)
      .fillColor(iconGroupSuffixTheme.fillColor)
      .size({
        width: this.getIconSize(item.icon.size?.width),
        height: this.getIconSize(item.icon.size?.height)
      })
      .focusable(true)
  }

  @Builder
  IconButtonsBuilder(material: uiMaterial.Material | undefined) {
    Row({ space: 8 }) {
      ForEach(this.items || [],
        (suffixItem: ChipGroupV2IconItemConfig | SymbolGlyphModifier | ChipGroupV2SymbolItemConfig) => {
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
            this.SymbolItemBuilder(suffixItem as ChipGroupV2SymbolItemConfig)
          } else {
            this.IconItemBuilder(suffixItem as ChipGroupV2IconItemConfig)
          }
        }
        .size({
          width: this.getBackgroundSize(),
          height: this.getBackgroundSize()
        })
        .backgroundColor(iconGroupSuffixTheme.backgroundColor)
        .borderRadius(iconGroupSuffixTheme.borderRadius)
        .systemMaterial(material)
        .accessibilityText(this.getAccessibilityText(suffixItem))
        .accessibilityDescription(this.getAccessibilityDescription(suffixItem))
        .accessibilityLevel(this.getAccessibilityLevel(suffixItem))
        .onClick(() => {
          if (!(suffixItem instanceof SymbolGlyphModifier)) {
            suffixItem.action();
          }
        })
      })
    }
  }

  build() {
    if (deviceInfo.sdkApiVersion >= 26) {
      if (enableEffectComponent(this.iconBackgroundSystemMaterial)) {
        EffectComponent() {
          this.IconButtonsBuilder(createSubECMaterial(this.iconBackgroundSystemMaterial))
        }
        .systemMaterial(createECMaterial(this.iconBackgroundSystemMaterial))
      } else {
        this.IconButtonsBuilder(this.iconBackgroundSystemMaterial)
      }
    } else {
      this.IconButtonsBuilder(undefined)
    }
  }

  private isSymbolItem(item: ChipGroupV2IconItemConfig | ChipGroupV2SymbolItemConfig): boolean {
    return typeof (item as ChipGroupV2SymbolItemConfig).symbol !== 'undefined';
  }

  private getAccessibilityLevel
    (item: ChipGroupV2IconItemConfig | SymbolGlyphModifier | ChipGroupV2SymbolItemConfig): string {
    if (item instanceof SymbolGlyphModifier) {
      return 'auto';
    }
    return item.accessibilityLevel ?? 'auto';
  }

  private getAccessibilityDescription(
    item: ChipGroupV2IconItemConfig | SymbolGlyphModifier | ChipGroupV2SymbolItemConfig
  ): Resource | undefined {
    if (item instanceof SymbolGlyphModifier || typeof item.accessibilityDescription === 'undefined') {
      return undefined;
    }
    return item.accessibilityDescription as ESObject as Resource;
  }

  private getAccessibilityText
    (item: ChipGroupV2IconItemConfig | SymbolGlyphModifier | ChipGroupV2SymbolItemConfig): Resource | undefined {
    if (item instanceof SymbolGlyphModifier || typeof item.accessibilityText === 'undefined') {
      return undefined;
    }
    return item.accessibilityText as ESObject as Resource;
  }
}

@ComponentV2
export struct ChipGroupV2 {
  @Require @Param items: ChipGroupV2Items;
  @Event $items?: Callback<ChipGroupV2Items> = undefined;
  @Param itemStyle?: ChipGroupV2ItemStyle = defaultTheme.itemStyle;
  @Param selectedIndexes?: Array<number> = [0];
  @Event $selectedIndexes?: Callback<Array<number>> = undefined;
  @Param multiple?: boolean = false;
  @Param chipGroupSpace?: ChipGroupV2Space = defaultTheme.chipGroupSpace;
  @Param chipGroupPadding?: ChipGroupV2Padding = defaultTheme.chipGroupPadding;
  @Param backgroundSystemMaterial?: uiMaterial.Material = undefined;
  @Event onChange?: Callback<Array<number>>;
  @BuilderParam suffix?: Callback<void>;
  @Provider() chipSize: ChipV2Size | SizeT<LengthMetrics> = defaultTheme.itemStyle.size!;
  private scroller: Scroller = new Scroller();
  @Local selectedIndexesInternal: Array<number> | undefined = [0];
  @Local isReachEnd: boolean = this.scroller.isAtEnd();
  @Local isRefresh: boolean = true;

  @Monitor('items')
  onItemsChange() {
    this.isRefresh = !this.isRefresh;
  }

  @Monitor('multiple')
  onMultipleChange() {
    this.selectedIndexesOnChange();
    this.selectedIndexesInternal = this.getSelectedIndexes();
  }

  @Monitor('itemStyle')
  itemStyleOnChange() {
    this.chipSize = this.getChipSize();
  }

  @Monitor('selectedIndexes')
  selectedIndexesOnChange() {
    this.selectedIndexesInternal = this.selectedIndexes?.filter(()=>true);
  }

  aboutToAppear() {
    this.itemStyleOnChange();
    this.selectedIndexesOnChange();
    if (this.getSelectedIndexes().length === 0) {
      this.selectedIndexesInternal = [0];
    }
  }

  private getChipSize(): ChipV2Size | SizeT<LengthMetrics> {
    if (this.itemStyle && this.itemStyle.size) {
      if (typeof this.itemStyle.size === 'object') {
        if (!this.itemStyle.size.width?.value || !this.itemStyle.size.height?.value || !this.itemStyle.size) {
          return defaultTheme.itemStyle.size!;
        }
      }
      return this.itemStyle.size;
    }
    return defaultTheme.itemStyle.size!;
  }

  private getFontColor(): ColorMetrics {
    if (this.itemStyle && this.itemStyle.fontColor) {
      return this.itemStyle.fontColor;
    }
    return defaultTheme.itemStyle.fontColor!;
  }

  private getSelectedFontColor(): ColorMetrics {
    if (this.itemStyle && this.itemStyle.selectedFontColor) {
      return this.itemStyle.selectedFontColor;
    }
    return defaultTheme.itemStyle.selectedFontColor!;
  }

  private getFillColor(): ColorMetrics {
    if (this.itemStyle && this.itemStyle.fontColor) {
      return this.itemStyle.fontColor;
    }
    return defaultTheme.itemFillColor;
  }

  private getSelectedFillColor(): ColorMetrics {
    if (this.itemStyle && this.itemStyle.selectedFontColor) {
      return this.itemStyle.selectedFontColor;
    }
    return defaultTheme.itemSelectedFillColor;
  }

  private getBackgroundColor(): ColorMetrics {
    return this.itemStyle?.backgroundColor ?? defaultTheme.itemStyle.backgroundColor!;
  }

  private getSelectedBackgroundColor(): ColorMetrics {
    return this.itemStyle?.selectedBackgroundColor ?? defaultTheme.itemStyle.selectedBackgroundColor!;
  }

  private getSelectedIndexes(): Array<number> {
    let temp: number[] = [];
    temp = (this.selectedIndexesInternal ?? [0]).filter(
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
      if (this.chipSize === ChipV2Size.NORMAL) {
        return ChipGroupHeight.NORMAL;
      } else {
        return ChipGroupHeight.SMALL;
      }
    } else if (typeof this.chipSize === 'object') {
      return lengthMetricsToLength(this.chipSize.height);
    } else {
      return ChipGroupHeight.NORMAL
    }
  }

  @Builder
  ChipItemsBuilder(material: uiMaterial.Material | undefined) {
    Row({ space: this.getChipGroupItemSpace() }) {
      ForEach(this.items || [], (chipItem: ChipGroupV2Item, index) => {
        if (chipItem) {
          ChipV2({ chipV2Options: new ChipV2Options({
            label: this.getLabel(chipItem.label),
            prefixIcon: this.getPrefixIcon(chipItem),
            suffixIcon: this.getSuffixIcon(chipItem),
            allowClose: chipItem.allowClose ?? false,
            closeIcon: chipItem.closeIcon ? new ChipV2CloseIcon(chipItem.closeIcon) : undefined,
            enabled: true,
            activated: this.isSelected(index),
            backgroundColor: this.getBackgroundColor(),
            backgroundSystemMaterial: createSubECMaterial(this.backgroundSystemMaterial),
            size: this.getChipSize(),
            activatedBackgroundColor: this.getSelectedBackgroundColor(),
            accessibilitySelectedType:
              this.multiple ? ChipV2AccessibilitySelectedType.CHECKED : ChipV2AccessibilitySelectedType.SELECTED,
            accessibilityDescription: chipItem.accessibilityDescription,
            accessibilityLevel: chipItem.accessibilityLevel,
            onClicked: () => {
              if (this.isSelected(index)) {
                if (!(!this.isMultiple())) {
                  if (this.getSelectedIndexes().length > 1) {
                    this.selectedIndexesInternal!.splice(this.selectedIndexesInternal!.indexOf(index), 1);
                  }
                }
              } else {
                if (!this.selectedIndexesInternal || this.selectedIndexesInternal.length === 0) {
                  this.selectedIndexesInternal = this.getSelectedIndexes();
                }
                if (!this.isMultiple()) {
                  this.selectedIndexesInternal = [];
                }
                this.selectedIndexesInternal.push(index);
              }
              this.getOnChange()(this.getSelectedIndexes());
              this.$selectedIndexes?.(this.selectedIndexesInternal);
            },
            onClose: () => {
              if (this.$items) {
                this.selectedIndexesInternal?.forEach((element, idx, array) => {
                  if (element > index) {
                    array[idx]--;
                  }
                })
                this.$selectedIndexes?.(this.selectedIndexesInternal);
              }
              this.$items?.(this.items.filter((element) => {
                return element !== chipItem;
              }))
            }
          })})
        }
      }, () => {
        return JSON.stringify(this.isRefresh);
      });
    }
  }

  build() {
    Row() {
      Stack() {
        Scroll(this.scroller) {
          if (deviceInfo.sdkApiVersion >= 26) {
            if (enableEffectComponent(this.backgroundSystemMaterial)) {
              EffectComponent() {
                Row({ space: this.getChipGroupItemSpace() }) {
                  this.ChipItemsBuilder(createSubECMaterial(this.backgroundSystemMaterial))
                }
              }
              .systemMaterial(createECMaterial(this.backgroundSystemMaterial))
            } else {
              this.ChipItemsBuilder(this.backgroundSystemMaterial)
            }
          } else {
            this.ChipItemsBuilder(undefined)
          }
        }
        .padding({
          left: this.getChipGroupStartSpace(),
          right: this.getChipGroupEndSpace()
        })
        .constraintSize({ minWidth: '100%' })
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

  private getLabel(label: ChipV2Label): ChipV2Label {
    if (!label.fontColor) {
      label.fontColor = this.getFontColor();
    }
    if (!label.activatedFontColor) {
      label.activatedFontColor = this.getSelectedFontColor();
    }
    return label;
  }

  private getPrefixIcon(chipItem: ChipGroupV2Item): ChipV2Icon | undefined {
    if (chipItem.prefixSymbolIcon) {
      return chipItem.prefixSymbolIcon;
    }
    if (chipItem.prefixIcon) {
      if (!chipItem.prefixIcon.fillColor) {
        chipItem.prefixIcon.fillColor = this.getFillColor();
      }
      if (!chipItem.prefixIcon.activatedFillColor) {
        chipItem.prefixIcon.activatedFillColor = this.getSelectedFillColor();
      }
      return chipItem.prefixIcon;
    }
    return undefined;
  }

  private getSuffixIcon(chipItem: ChipGroupV2Item): ChipV2Icon | undefined {
    if (chipItem.suffixSymbolIcon) {
      return chipItem.suffixSymbolIcon;
    }
    if (chipItem.suffixIcon) {
      if (!chipItem.suffixIcon.fillColor) {
        chipItem.suffixIcon.fillColor = this.getFillColor();
      }
      if (!chipItem.suffixIcon.activatedFillColor) {
        chipItem.suffixIcon.activatedFillColor = this.getSelectedFillColor();
      }
      return chipItem.suffixIcon;
    }
    return undefined;
  }
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

function enableEffectComponent(material: uiMaterial.Material | undefined) {
  return false;
}

function createECMaterial(material: uiMaterial.Material | undefined): uiMaterial.Material | undefined {
  return undefined;
}

function createSubECMaterial(material: uiMaterial.Material | undefined): uiMaterial.Material | undefined {
  return material;
}

function lengthMetricsToLength(length: LengthMetrics): Length {
  if (length.unit === LengthUnit.PX) {
    return `${length.value}px`;
  } else if (length.unit === LengthUnit.VP) {
    return `${length.value}vp`;
  } else if (length.unit === LengthUnit.FP) {
    return `${length.value}fp`;
  } else if (length.unit === LengthUnit.PERCENT) {
    return `${length.value}%`;
  } else if (length.unit === LengthUnit.LPX) {
    return `${length.value}lpx`;
  }
  return 0;
}