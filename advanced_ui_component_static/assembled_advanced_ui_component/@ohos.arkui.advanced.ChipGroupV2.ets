'use static'

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

import {
  $r,
  Builder,
  Button,
  ButtonOptions,
  ButtonType,
  Callback,
  ClickEvent,
  Color,
  ComponentV2,
  ConstraintSizeOptions,
  Curve,
  Dimension,
  Direction,
  Flex,
  FlexAlign,
  FontWeight,
  HoverEffect,
  Image,
  ImageFit,
  ItemAlign,
  KeyEvent,
  KeyType,
  Length,
  LocalizedMargin,
  LocalizedPadding,
  Margin,
  Padding,
  Resource,
  ResourceColor,
  ResourceStr,
  Row,
  ForEach,
  ScaleOptions,
  ShadowStyle,
  SizeOptions,
  SymbolEffect,
  SymbolEffectStrategy,
  SymbolGlyph,
  Text,
  TextAlign,
  TextOverflow,
  VoidCallback,
  Rectangle,
  UIContext,
  RowOptions,
  EffectComponent,
  BuilderParam,
  Scroller,
  Alignment,
  Stack,
  Scroll,
  ScrollDirection,
  BlendMode,
  BlendApplyType,
  BarState,
  HitTestMode
} from '@ohos.arkui.component';
import { ImageModifier, SymbolGlyphModifier, TextModifier } from '@ohos.arkui.modifier';
import {
  Require, Param, ObservedV2, Trace, Event, Local, Consumer, Provider, Monitor
} from '@ohos.arkui.stateManagement';
import { ColorMetrics, LengthMetrics, LengthUnit, SizeT } from '@ohos.arkui.node';
import { KeyCode } from '@ohos.multimodalInput.keyCode';
import hilog from '@ohos.hilog';
import resourceManager from '@ohos.resourceManager';
import common from '@ohos.app.ability.common';
import mediaquery from '@ohos.mediaquery';
import { EnvironmentCallback } from '@kit.AbilityKit';
import deviceInfo from '@ohos.deviceInfo';
import { Configuration } from '@ohos.app.ability.Configuration';
import AbilityConstant from '@ohos.app.ability.AbilityConstant';
import uiMaterial from '@ohos.arkui.uiMaterial';
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
  IChipV2OptionsConfig,
  ChipV2Options,
  ChipV2AccessibilitySelectedType,
  ChipV2Icon
} from '@ohos.arkui.advanced.ChipV2';

interface ChipGroupV2Theme {
  size: ChipV2Size | SizeT<LengthMetrics>;
  backgroundColor: ResourceColor;
  fontColor: ResourceColor;
  selectedFontColor: ResourceColor;
  selectedBackgroundColor: ResourceColor;
  chipGroupSpace: ChipGroupV2SpaceConfig;
  chipGroupPadding: ChipGroupV2PaddingConfig;
  itemFillColor: ResourceColor;
  itemSelectedFillColor: ResourceColor;
  chipBackgroundSystemMaterial: uiMaterial.Material;
  chipSelectedBackgroundSystemMaterial: uiMaterial.Material;
  iconBackgroundSystemMaterial: uiMaterial.Material;
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
  defaultEffect: int;
}

const noop = (selectedIndexes: Array<int>) => {
}

const colorStops: ([ResourceColor, number])[] = [['rgba(0, 0, 0, 1)', 0], ['rgba(0, 0, 0, 0)', 1]];

const defaultTheme: ChipGroupV2Theme = {
  size: ChipV2Size.NORMAL,
  backgroundColor: $r('sys.color.ohos_id_color_button_normal'),
  fontColor: $r('sys.color.ohos_id_color_text_primary'),
  selectedFontColor: $r('sys.color.ohos_id_color_text_primary_contrary'),
  selectedBackgroundColor: $r('sys.color.ohos_id_color_emphasize'),
  chipGroupSpace: { itemSpace: 8, startSpace: 16, endSpace: 16 },
  chipGroupPadding: { top: 14, bottom: 14 },
  itemFillColor: $r('sys.color.ohos_id_color_secondary'),
  itemSelectedFillColor: $r('sys.color.ohos_id_color_text_primary_contrary'),
  chipBackgroundSystemMaterial: new uiMaterial.ImmersiveMaterial({
    style: uiMaterial.ImmersiveStyle.ULTRA_THIN
  }),
  chipSelectedBackgroundSystemMaterial: new uiMaterial.ImmersiveMaterial({
    style: uiMaterial.ImmersiveStyle.ULTRA_THIN,
    materialColor: $r('sys.color.comp_background_emphasize')
  }),
  iconBackgroundSystemMaterial: new uiMaterial.ImmersiveMaterial({
    style: uiMaterial.ImmersiveStyle.ULTRA_THIN
  })
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
    this.prefixIcon = config.prefixIcon ? new ChipV2PrefixImageIcon(config.prefixIcon!) : undefined;
    this.prefixSymbolIcon = config.prefixSymbolIcon ? new ChipV2PrefixSymbolIcon(config.prefixSymbolIcon!) : undefined;
    this.label = new ChipV2Label(config.label);
    this.suffixIcon = config.suffixIcon ? new ChipV2SuffixImageIcon(config.suffixIcon!) : undefined;
    this.suffixSymbolIcon = config.suffixSymbolIcon ? new ChipV2SuffixSymbolIcon(config.suffixSymbolIcon!) : undefined;
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
    items.forEach((item, index) => {
      this.push(new ChipGroupV2Item(item));
    });
  }
}

export interface ChipGroupV2ItemStyleConfig {
  size?: ChipV2Size | SizeT<LengthMetrics>;
  backgroundColor?: ColorMetrics;
  fontColor?: ColorMetrics;
  selectedFontColor?: ColorMetrics;
  selectedBackgroundColor?: ColorMetrics;
  backgroundSystemMaterial?: uiMaterial.Material;
  selectedBackgroundSystemMaterial?: uiMaterial.Material;
}

@ObservedV2
export class ChipGroupV2ItemStyle {
  @Trace public size?: ChipV2Size | SizeT<LengthMetrics>;
  @Trace public backgroundColor?: ColorMetrics;
  @Trace public fontColor?: ColorMetrics;
  @Trace public selectedFontColor?: ColorMetrics;
  @Trace public selectedBackgroundColor?: ColorMetrics;
  @Trace public backgroundSystemMaterial?: uiMaterial.Material;
  @Trace public selectedBackgroundSystemMaterial?: uiMaterial.Material;

  constructor(config: ChipGroupV2ItemStyleConfig) {
    this.size = config.size;
    this.backgroundColor = config.backgroundColor;
    this.fontColor = config.fontColor;
    this.selectedFontColor = config.selectedFontColor;
    this.selectedBackgroundColor = config.selectedBackgroundColor;
    this.backgroundSystemMaterial = config.backgroundSystemMaterial;
    this.selectedBackgroundSystemMaterial = config.selectedBackgroundSystemMaterial;
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
  action: VoidCallback;
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
  @Require @Param items: (ChipGroupV2IconItemConfig | SymbolGlyphModifier | ChipGroupV2SymbolItemConfig)[] =
    new Array<ChipGroupV2IconItemConfig | SymbolGlyphModifier | ChipGroupV2SymbolItemConfig>();
  @Param iconBackgroundSystemMaterial?: uiMaterial.Material = undefined;
  @Consumer chipSize: ChipV2Size | SizeT<LengthMetrics> = ChipV2Size.NORMAL;
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
    let value: Length = lengthMetricsToLength(val);
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
    Row({ space: 8 } as RowOptions) {
      ForEach(this.items,
        (suffixItem: ChipGroupV2IconItemConfig | SymbolGlyphModifier | ChipGroupV2SymbolItemConfig) => {
        Button({ type: ButtonType.Normal } as ButtonOptions) {
          if (suffixItem instanceof SymbolGlyphModifier) {
            SymbolGlyph()
              .fontColor([iconGroupSuffixTheme.fillColor])
              .fontSize(this.getIconSize())
              .attributeModifier(suffixItem as SymbolGlyphModifier)
              .focusable(true)
              .effectStrategy(SymbolEffectStrategy.NONE)
              .symbolEffect(this.symbolEffect, false)
              .symbolEffect(this.symbolEffect, iconGroupSuffixTheme.defaultEffect)
          } else if (suffixItem instanceof ChipGroupV2SymbolItemConfig) {
            this.SymbolItemBuilder(suffixItem as ChipGroupV2SymbolItemConfig)
          } else if (suffixItem instanceof ChipGroupV2IconItemConfig) {
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
        .onClick((event: ClickEvent) => {
          if (suffixItem instanceof ChipGroupV2SymbolItemConfig) {
            (suffixItem as ChipGroupV2SymbolItemConfig).action();
          }
          if (suffixItem instanceof ChipGroupV2IconItemConfig){
            (suffixItem as ChipGroupV2IconItemConfig).action();
          }
        })
      })
    }
  }

  build() {
    if (deviceInfo.sdkApiVersion >= 26) {
      if (enableEffectComponent(this.iconBackgroundSystemMaterial)) {
        EffectComponent() {
          this.IconButtonsBuilder(
            createSubECMaterial(
              withDefaultMaterial(this.iconBackgroundSystemMaterial, defaultTheme.iconBackgroundSystemMaterial)
            )
          )
        }
        .systemMaterial(
          createECMaterial(
            withDefaultMaterial(this.iconBackgroundSystemMaterial, defaultTheme.iconBackgroundSystemMaterial)
          )
        )
      } else {
        this.IconButtonsBuilder(
          withDefaultMaterial(this.iconBackgroundSystemMaterial, defaultTheme.iconBackgroundSystemMaterial)
        )
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
  ): ResourceStr | undefined {
    if (item instanceof SymbolGlyphModifier || typeof item.accessibilityDescription === 'undefined') {
      return undefined;
    }
    return item.accessibilityDescription as ResourceStr;
  }

  private getAccessibilityText
    (item: ChipGroupV2IconItemConfig | SymbolGlyphModifier | ChipGroupV2SymbolItemConfig): ResourceStr | undefined {
    if (item instanceof SymbolGlyphModifier || typeof item.accessibilityText === 'undefined') {
      return undefined;
    }
    return item.accessibilityText as ResourceStr;
  }
}

@Builder
export type ChipGroupV2SuffixBuilder = () => void;

export interface ChipV2ItemsBuilderOptions {
  backgroundSystemMaterial?: uiMaterial.Material;
  activatedBackgroundSystemMaterial?: uiMaterial.Material;
}

@ComponentV2
export struct ChipGroupV2 {
  @Require @Param items: ChipGroupV2Items;
  @Event $items?: Callback<ChipGroupV2Items> = undefined
  @Param itemStyle?: ChipGroupV2ItemStyle = undefined;
  @Param selectedIndexes?: Array<int> = undefined;
  @Event $selectedIndexes?: Callback<Array<int>> = undefined;
  @Param multiple?: boolean = false;
  @Param chipGroupSpace?: ChipGroupV2Space = new ChipGroupV2Space(defaultTheme.chipGroupSpace);
  @Param chipGroupPadding?: ChipGroupV2Padding = new ChipGroupV2Padding(defaultTheme.chipGroupPadding);
  @Event onChange?: Callback<Array<int>>;
  @BuilderParam suffix?: ChipGroupV2SuffixBuilder;
  @Provider chipSize: ChipV2Size | SizeT<LengthMetrics> = defaultTheme.size;
  private scroller: Scroller = new Scroller();
  @Local selectedIndexesInternal?: Array<int> = [0];
  @Local isReachEnd: boolean = this.scroller.isAtEnd();
  @Local isRefresh: boolean = true;

  @Monitor(['items'])
  onItemsChange() {
    this.isRefresh = !this.isRefresh;
  }

  @Monitor(['multiple'])
  onMultipleChange() {
    if (this.selectedIndexes) {
      this.selectedIndexesOnChange();
    }
    this.selectedIndexesInternal = this.getSelectedIndexes();
  }

  @Monitor(['itemStyle'])
  itemStyleOnChange() {
    this.chipSize = this.getChipSize();
  }

  @Monitor(['selectedIndexes'])
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
    if (this.itemStyle && this.itemStyle!.size) {
      if (typeof this.itemStyle!.size !== 'string') {
        if (!(this.itemStyle!.size as SizeT<LengthMetrics>)!.width?.value ||
          !(this.itemStyle!.size as SizeT<LengthMetrics>)!.height?.value || !this.itemStyle!.size) {
          return defaultTheme.size;
        }
      }
      return this.itemStyle!.size!;
    }
    return defaultTheme.size;
  }

  private getFontColor(): ColorMetrics {
    if (this.itemStyle && this.itemStyle!.fontColor) {
      return this.itemStyle!.fontColor!;
    }
    return ColorMetrics.resourceColor(defaultTheme.fontColor);
  }

  private getSelectedFontColor(): ColorMetrics {
    if (this.itemStyle && this.itemStyle!.selectedFontColor) {
      return this.itemStyle!.selectedFontColor!;
    }
    return ColorMetrics.resourceColor(defaultTheme.selectedFontColor);
  }

  private getFillColor(): ColorMetrics {
    if (this.itemStyle && this.itemStyle!.fontColor) {
      return this.itemStyle!.fontColor!;
    }
    return ColorMetrics.resourceColor(defaultTheme.itemFillColor);
  }

  private getSelectedFillColor(): ColorMetrics {
    if (this.itemStyle && this.itemStyle!.selectedFontColor) {
      return this.itemStyle!.selectedFontColor!;
    }
    return ColorMetrics.resourceColor(defaultTheme.itemSelectedFillColor);
  }

  private getBackgroundColor(): ColorMetrics {
    if (this.itemStyle?.backgroundColor) {
      return this.itemStyle!.backgroundColor!;
    }
    return ColorMetrics.resourceColor(defaultTheme.backgroundColor!);
  }

  private getSelectedBackgroundColor(): ColorMetrics {
    if (this.itemStyle?.selectedBackgroundColor) {
      return this.itemStyle!.selectedBackgroundColor!;
    }
    return ColorMetrics.resourceColor(defaultTheme.selectedBackgroundColor!);
  }

  private getSelectedIndexes(): Array<int> {
    let temp: int[] = [];
    temp = (this.selectedIndexesInternal ?? [0]).filter(
      (element, index, array) => {
        return (
          element >= 0 &&
            element % 1 == 0 &&
            element != null &&
            element != undefined &&
            array.indexOf(element) === index &&
            element < (this.items || [] as Array<int>).length);
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
      this.chipGroupSpace!.itemSpace,
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
      this.chipGroupSpace!.startSpace,
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
      this.chipGroupSpace!.endSpace,
      isValidDimensionNoPercentageString,
      defaultTheme.chipGroupSpace.endSpace
    );
  }

  private getOnChange(): (selectedIndexes: Array<int>) => void {
    return this.onChange ?? noop;
  }

  private isSelected(itemIndex: int): boolean {
    if (!this.isMultiple()) {
      const indexes = this.getSelectedIndexes();
      if (indexes.length === 0) {
        return false;
      }
      return itemIndex == indexes[0];
    } else {
      return this.getSelectedIndexes().some((element, index, array) => {
        return (element == itemIndex);
      })
    }
  }

  private getPaddingTop() {
    if (!this.chipGroupPadding || !this.chipGroupPadding!.top) {
      return defaultTheme.chipGroupPadding.top
    }
    return parseDimension(
      this.getUIContext(),
      this.chipGroupPadding!.top,
      isValidDimensionNoPercentageString,
      defaultTheme.chipGroupPadding.top
    );
  }

  private getPaddingBottom() {
    if (!this.chipGroupPadding || !this.chipGroupPadding!.bottom) {
      return defaultTheme.chipGroupPadding.bottom
    }
    return parseDimension(
      this.getUIContext(),
      this.chipGroupPadding!.bottom,
      isValidDimensionNoPercentageString,
      defaultTheme.chipGroupPadding.bottom
    );
  }

  private getChipGroupHeight(): Length {
    if (typeof this.chipSize === 'string') {
      if (this.chipSize === ChipV2Size.NORMAL) {
        return ChipGroupHeight.NORMAL;
      } else {
        return ChipGroupHeight.SMALL;
      }
    } else if (typeof this.chipSize === 'object') {
      return lengthMetricsToLength((this.chipSize as SizeT<LengthMetrics>).height);
    } else {
      return ChipGroupHeight.NORMAL
    }
  }

  private getBackgroundSystemMaterial(): uiMaterial.Material | undefined {
    return withDefaultMaterial(this.itemStyle?.backgroundSystemMaterial, defaultTheme.chipBackgroundSystemMaterial);
  }

  private getSelectedBackgroundSystemMaterial(): uiMaterial.Material | undefined {
    return withDefaultMaterial(
      this.itemStyle?.selectedBackgroundSystemMaterial,
      defaultTheme.chipSelectedBackgroundSystemMaterial
    );
  }

  private getOutsideBlendType(): BlendApplyType | undefined {
    if (!this.suffix && (!!this.getBackgroundSystemMaterial() || !!this.getSelectedBackgroundSystemMaterial())) {
      return undefined;
    }
    return BlendApplyType.OFFSCREEN;
  }

  private getOutsideBlendMode(): BlendMode | undefined {
    if (!this.suffix && (!!this.getBackgroundSystemMaterial() || !!this.getSelectedBackgroundSystemMaterial())) {
      return undefined;
    }
    return BlendMode.SRC_OVER;
  }

  @Builder
  ChipItemsBuilder(options: ChipV2ItemsBuilderOptions) {
    Row({ space: this.getChipGroupItemSpace() } as RowOptions) {
      ForEach(this.items as Array<ChipGroupV2Item>, (chipItem: ChipGroupV2Item, index: int) => {
        if (chipItem) {
          ChipV2({ chipV2Options: new ChipV2Options({
            label: this.getLabel(chipItem.label),
            prefixIcon: this.getPrefixIcon(chipItem),
            suffixIcon: this.getSuffixIcon(chipItem),
            allowClose: chipItem.allowClose ?? false,
            closeIcon: chipItem.closeIcon ? new ChipV2CloseIcon(chipItem.closeIcon!) : undefined,
            enabled: true,
            activated: this.isSelected(index),
            backgroundColor: this.getBackgroundColor(),
            backgroundSystemMaterial: options.backgroundSystemMaterial,
            activatedBackgroundSystemMaterial: options.activatedBackgroundSystemMaterial,
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
                if (!this.selectedIndexesInternal || this.selectedIndexesInternal!.length === 0) {
                  this.selectedIndexesInternal = this.getSelectedIndexes();
                }
                if (!this.isMultiple()) {
                  this.selectedIndexesInternal = [];
                }
                this.selectedIndexesInternal!.push(index);
              }
              this.getOnChange()(this.getSelectedIndexes());
              this.$selectedIndexes?.(this.selectedIndexesInternal!);
            },
            onClose: () => {
              if (this.$items) {
                this.selectedIndexesInternal?.forEach((element, idx, array) => {
                  if (element > index) {
                    array[idx]--;
                  }
                })
                this.$selectedIndexes?.(this.selectedIndexesInternal!);
                let newItems = new ChipGroupV2Items([]);
                (this.items as Array<ChipGroupV2Item>).forEach((element) => {
                  if (element !== chipItem) {
                    newItems.push(element);
                  }
                })
                this.$items?.(newItems);
              }
            }
          } as IChipV2OptionsConfig)})
        }
      }, (chipItem: ChipGroupV2Item, index: int) => {
        return JSON.stringify(this.isRefresh) + index.toString();
      });
    }
  }

  build() {
    Row() {
      Stack() {
        Scroll(this.scroller) {
          if (deviceInfo.sdkApiVersion >= 26) {
            if (enableEffectComponent(this.itemStyle?.backgroundSystemMaterial)) {
              EffectComponent() {
                Row({ space: this.getChipGroupItemSpace() } as RowOptions) {
                  this.ChipItemsBuilder({
                    backgroundSystemMaterial: createSubECMaterial(this.getBackgroundSystemMaterial()),
                    activatedBackgroundSystemMaterial: this.getSelectedBackgroundSystemMaterial()
                  })
                }
              }
              .systemMaterial(createECMaterial(this.getBackgroundSystemMaterial()))
            } else {
              this.ChipItemsBuilder({
                backgroundSystemMaterial: this.getBackgroundSystemMaterial(),
                activatedBackgroundSystemMaterial: this.getSelectedBackgroundSystemMaterial()
              })
            }
          } else {
            this.ChipItemsBuilder({})
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
        .onDidScroll(() => {
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
      .blendMode(this.getOutsideBlendMode(), this.getOutsideBlendType())
      .alignContent(Alignment.End)
      if (this.suffix) {
        Row() {
          this.suffix!();
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
    const result = new ChipV2Label({
      text: label.text,
      fontSize: label.fontSize,
      fontColor: label.fontColor || this.getFontColor(),
      activatedFontColor: label.activatedFontColor || this.getSelectedFontColor(),
      fontFamily: label.fontFamily,
      labelMargin: label.labelMargin,
      localizedLabelMargin: label.localizedLabelMargin,
      modifier: label.modifier
    });
    return result;
  }

  private getPrefixIcon(chipItem: ChipGroupV2Item): ChipV2Icon | undefined {
    if (chipItem.prefixSymbolIcon) {
      return chipItem.prefixSymbolIcon;
    }
    if (chipItem.prefixIcon) {
      return new ChipV2PrefixImageIcon({
        src: chipItem.prefixIcon!.src,
        size: chipItem.prefixIcon!.size,
        fillColor: chipItem.prefixIcon!.fillColor || this.getFillColor(),
        activatedFillColor: chipItem.prefixIcon!.activatedFillColor || this.getSelectedFillColor(),
        modifier: chipItem.prefixIcon!.modifier
      });
    }
    return undefined;
  }

  private getSuffixIcon(chipItem: ChipGroupV2Item): ChipV2Icon | undefined {
    if (chipItem.suffixSymbolIcon) {
      return chipItem.suffixSymbolIcon;
    }
    if (chipItem.suffixIcon) {
      const suffixIcon = new ChipV2SuffixImageIcon({
        src: chipItem.suffixIcon!.src,
        size: chipItem.suffixIcon!.size,
        fillColor: chipItem.suffixIcon!.fillColor || this.getFillColor(),
        activatedFillColor: chipItem.suffixIcon!.activatedFillColor || this.getSelectedFillColor(),
        modifier: chipItem.suffixIcon!.modifier,
        accessibilityLevel: chipItem.suffixIcon!.accessibilityLevel,
        accessibilityText: chipItem.suffixIcon!.accessibilityText,
        accessibilityDescription: chipItem.suffixIcon!.accessibilityDescription,
        action: chipItem.suffixIcon!.action
      });
      return suffixIcon;
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
  if (value === undefined || value === null) {
    return defaultValue;
  }
  const resourceManager = uiContext.getHostContext()?.resourceManager;
  if (!resourceManager) {
    return defaultValue;
  }
  if (typeof value === 'object') {
    let temp: Resource = value as Resource;
    if (temp.type === 10002 || temp.type === 10007) {
      if (resourceManager && resourceManager.getDouble(temp.id) >= 0) {
        return value as T;
      }
    } else if (temp.type === 10003) {
      if (resourceManager && isValidDimensionString(resourceManager.getStringSync(temp.id))) {
        return value as T;
      }
    }
  } else if (typeof value === 'number') {
    if (value as number >= 0) {
      return value as T;
    }
  } else if (typeof value === 'string') {
    if (isValid(value as string)) {
      return value as T;
    }
  }
  return defaultValue;
}

function isValidString(dimension: string, regex: RegExp): boolean {
  const matches = dimension.match(regex);
  if (!matches || matches.length < 3 || !matches[1]) {
    return false;
  }
  const value = Number.parseFloat(matches[1]!);
  return value >= 0;
}

function isValidDimensionString(dimension: string): boolean {
  return isValidString(dimension, new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$', 'i'));
}

function isValidDimensionNoPercentageString(dimension: string): boolean {
  return isValidString(dimension, new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx)?$', 'i'));
}

function withDefaultMaterial(
    material: uiMaterial.Material | undefined, defaultMaterial: uiMaterial.Material
  ): uiMaterial.Material | undefined {
  return material;
}

function enableEffectComponent(material: uiMaterial.Material | undefined) {
  return false;
}

function createECMaterial(material: uiMaterial.Material | undefined): uiMaterial.Material | undefined {
  return material;
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