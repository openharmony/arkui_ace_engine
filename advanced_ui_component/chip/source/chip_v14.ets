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

import { ColorMetrics, LengthMetrics } from '@ohos.arkui.node';
import { SymbolGlyphModifier } from '@ohos.arkui.modifier';
import { KeyCode } from '@kit.InputKit';
import mediaquery from '@ohos.mediaquery';
import EnvironmentCallback from '@ohos.app.ability.EnvironmentCallback';
import common from '@ohos.app.ability.common';

export enum ChipSize {
  NORMAL = 'NORMAL',
  SMALL = 'SMALL'
}

enum BreakPointsType {
  SM = 'SM',
  MD = 'MD',
  LG = 'LG'
}

export enum AccessibilitySelectedType {
  CLICKED = 0,
  CHECKED = 1,
  SELECTED = 2,
}

export interface IconCommonOptions {
  src: ResourceStr;
  size?: SizeOptions;
  fillColor?: ResourceColor;
  activatedFillColor?: ResourceColor;
}

export interface SuffixIconOptions extends IconCommonOptions {
  action?: () => void;
  accessibilityText?: ResourceStr;
  accessibilityDescription?: ResourceStr;
  accessibilityLevel?: string;
}

export interface PrefixIconOptions extends IconCommonOptions {}

export interface AccessibilityOptions {
  accessibilityLevel?: string;
  accessibilityText?: ResourceStr;
  accessibilityDescription?: ResourceStr;
}

export interface CloseOptions extends AccessibilityOptions {}

export interface ChipSymbolGlyphOptions {
  normal?: SymbolGlyphModifier;
  activated?: SymbolGlyphModifier;
}

export interface ChipSuffixSymbolGlyphOptions {
  normalAccessibility?: AccessibilityOptions;
  activatedAccessibility?: AccessibilityOptions;
  action?: VoidCallback;
}

export interface LabelMarginOptions {
  left?: Dimension;
  right?: Dimension;
}

export interface LocalizedLabelMarginOptions {
  start?: LengthMetrics;
  end?: LengthMetrics;
}

export interface LabelOptions {
  text: string;
  fontSize?: Dimension;
  fontColor?: ResourceColor;
  activatedFontColor?: ResourceColor;
  fontFamily?: string;
  labelMargin?: LabelMarginOptions;
  localizedLabelMargin?: LocalizedLabelMarginOptions;
}

interface IconTheme {
  size: SizeOptions;
  fillColor: ResourceColor;
  activatedFillColor: ResourceColor;
}

interface PrefixIconTheme extends IconTheme {}

interface SuffixIconTheme extends IconTheme {
  defaultDeleteIcon: ResourceStr;
  focusable: boolean;
}

interface DefaultSymbolTheme {
  normalFontColor: Array<ResourceColor>;
  activatedFontColor: Array<ResourceColor>;
  fontSize: Length;
  defaultEffect: number;
}

interface LabelTheme {
  normalFontSize: Dimension;
  smallFontSize: Dimension;
  fontColor: ResourceColor;
  activatedFontColor: ResourceColor;
  fontFamily: string;
  normalMargin: Margin;
  localizedNormalMargin: LocalizedMargin;
  smallMargin: Margin;
  localizedSmallMargin: LocalizedMargin;
  defaultFontSize: Dimension;
}

interface ChipNodeOpacity {
  normal: number;
  hover: number;
  pressed: number;
}

interface ChipNodeConstraintWidth {
  breakPointMinWidth: number,
  breakPointSmMaxWidth: number,
  breakPointMdMaxWidth: number,
  breakPointLgMaxWidth: number,
}

interface ChipNodeTheme {
  suitAgeScale: number;
  minLabelWidth: Dimension;
  normalHeight: Dimension;
  smallHeight: Dimension;
  enabled: boolean;
  activated: boolean;
  backgroundColor: ResourceColor;
  activatedBackgroundColor: ResourceColor;
  focusOutlineColor: ResourceColor;
  focusOutlineMargin: number;
  normalBorderRadius: Dimension;
  smallBorderRadius: Dimension;
  borderWidth: number;
  localizedNormalPadding: LocalizedPadding;
  localizedSmallPadding: LocalizedPadding;
  hoverBlendColor: ResourceColor;
  pressedBlendColor: ResourceColor;
  opacity: ChipNodeOpacity;
  breakPointConstraintWidth: ChipNodeConstraintWidth;
}

interface ChipTheme {
  prefixIcon: PrefixIconTheme;
  label: LabelTheme;
  suffixIcon: SuffixIconTheme;
  defaultSymbol: DefaultSymbolTheme;
  chipNode: ChipNodeTheme;
}

export const defaultTheme: ChipTheme = {
  prefixIcon: {
    size: { width: 16, height: 16 },
    fillColor: $r('sys.color.ohos_id_color_secondary'),
    activatedFillColor: $r('sys.color.ohos_id_color_text_primary_contrary'),
  },
  label: {
    normalFontSize: $r('sys.float.ohos_id_text_size_button2'),
    smallFontSize: $r('sys.float.ohos_id_text_size_button2'),
    fontColor: $r('sys.color.ohos_id_color_text_primary'),
    activatedFontColor: $r('sys.color.ohos_id_color_text_primary_contrary'),
    fontFamily: 'HarmonyOS Sans',
    normalMargin: {
      left: 6,
      right: 6,
      top: 0,
      bottom: 0
    },
    smallMargin: {
      left: 4,
      right: 4,
      top: 0,
      bottom: 0
    },
    defaultFontSize: 14,
    localizedNormalMargin: {
      start: LengthMetrics.vp(6),
      end: LengthMetrics.vp(6),
      top: LengthMetrics.vp(0),
      bottom: LengthMetrics.vp(0)
    },
    localizedSmallMargin: {
      start: LengthMetrics.vp(4),
      end: LengthMetrics.vp(4),
      top: LengthMetrics.vp(0),
      bottom: LengthMetrics.vp(0),
    }
  },
  suffixIcon: {
    size: { width: 16, height: 16 },
    fillColor: $r('sys.color.ohos_id_color_secondary'),
    activatedFillColor: $r('sys.color.ohos_id_color_text_primary_contrary'),
    defaultDeleteIcon: $r('sys.media.ohos_ic_public_cancel', 16, 16),
    focusable: false,
  },
  defaultSymbol: {
    normalFontColor: [$r('sys.color.ohos_id_color_secondary')],
    activatedFontColor: [$r('sys.color.ohos_id_color_text_primary_contrary')],
    fontSize: 16,
    defaultEffect: -1,
  },
  chipNode: {
    suitAgeScale: 1.75,
    minLabelWidth: 12,
    normalHeight: 36,
    smallHeight: 28,
    enabled: true,
    activated: false,
    backgroundColor: $r('sys.color.ohos_id_color_button_normal'),
    activatedBackgroundColor: $r('sys.color.ohos_id_color_emphasize'),
    focusOutlineColor: $r('sys.color.ohos_id_color_focused_outline'),
    focusOutlineMargin: 2,
    normalBorderRadius: $r('sys.float.chip_border_radius_normal'),
    smallBorderRadius: $r('sys.float.chip_border_radius_small'),
    borderWidth: 2,
    localizedNormalPadding: {
      start: LengthMetrics.vp(16),
      end: LengthMetrics.vp(16),
      top: LengthMetrics.vp(4),
      bottom: LengthMetrics.vp(4)
    },
    localizedSmallPadding: {
      start: LengthMetrics.vp(12),
      end: LengthMetrics.vp(12),
      top: LengthMetrics.vp(4),
      bottom: LengthMetrics.vp(4)
    },
    hoverBlendColor: $r('sys.color.ohos_id_color_hover'),
    pressedBlendColor: $r('sys.color.ohos_id_color_click_effect'),
    opacity: { normal: 1, hover: 0.95, pressed: 0.9 },
    breakPointConstraintWidth: {
      breakPointMinWidth: 128,
      breakPointSmMaxWidth: 156,
      breakPointMdMaxWidth: 280,
      breakPointLgMaxWidth: 400
    }
  }
};

const RESOURCE_TYPE_STRING = 10003;
const RESOURCE_TYPE_FLOAT = 10002;
const RESOURCE_TYPE_INTEGER = 10007;

interface ChipOptions {
  prefixIcon?: PrefixIconOptions;
  prefixSymbol?: ChipSymbolGlyphOptions;
  label: LabelOptions;
  suffixIcon?: SuffixIconOptions;
  suffixSymbol?: ChipSymbolGlyphOptions;
  suffixSymbolOptions?: ChipSuffixSymbolGlyphOptions;
  allowClose?: boolean;
  closeOptions?: CloseOptions;
  enabled?: boolean;
  activated?: boolean;
  backgroundColor?: ResourceColor;
  activatedBackgroundColor?: ResourceColor;
  borderRadius?: Dimension;
  size?: ChipSize | SizeOptions;
  direction?: Direction;
  accessibilitySelectedType?: AccessibilitySelectedType;
  accessibilityDescription?: ResourceStr;
  accessibilityLevel?: string;
  onClose?: () => void
  onClicked?: () => void
}

@Builder
export function Chip(options: ChipOptions) {
  ChipComponent({
    chipSize: options.size,
    prefixIcon: options.prefixIcon,
    prefixSymbol: options.prefixSymbol,
    label: options.label,
    suffixIcon: options.suffixIcon,
    suffixSymbol: options.suffixSymbol,
    suffixSymbolOptions: options.suffixSymbolOptions,
    allowClose: options.allowClose,
    closeOptions: options.closeOptions,
    chipEnabled: options.enabled,
    chipActivated: options.activated,
    chipNodeBackgroundColor: options.backgroundColor,
    chipNodeActivatedBackgroundColor: options.activatedBackgroundColor,
    chipNodeRadius: options.borderRadius,
    chipDirection: options.direction,
    chipAccessibilitySelectedType: options.accessibilitySelectedType,
    chipAccessibilityDescription: options.accessibilityDescription,
    chipAccessibilityLevel: options.accessibilityLevel,
    onClose: options.onClose,
    onClicked: options.onClicked,
  })
}


@Component
export struct ChipComponent {
  private theme: ChipTheme = defaultTheme;
  @Prop chipSize?: ChipSize | SizeOptions = ChipSize.NORMAL;
  @Prop allowClose?: boolean;
  @Prop closeOptions?: CloseOptions;
  @Prop chipDirection?: Direction = Direction.Auto;
  @Prop prefixIcon?: PrefixIconOptions;
  @Prop prefixSymbol?: ChipSymbolGlyphOptions;
  @Require @Prop label: LabelOptions;
  @Prop suffixIcon?: SuffixIconOptions;
  @Prop suffixSymbol?: ChipSymbolGlyphOptions;
  @Prop suffixSymbolOptions?: ChipSuffixSymbolGlyphOptions;
  @Prop chipNodeBackgroundColor?: ResourceColor;
  @Prop chipNodeActivatedBackgroundColor?: ResourceColor;
  @Prop chipNodeRadius?: Dimension;
  @Prop chipEnabled?: boolean = true;
  @Prop chipActivated?: boolean;
  @Prop chipAccessibilitySelectedType?: AccessibilitySelectedType;
  @Prop chipAccessibilityDescription?: ResourceStr;
  @Prop chipAccessibilityLevel?: string;
  @State isChipExist: boolean = true;
  @State chipScale: ScaleOptions = { x: 1, y: 1 };
  @State chipOpacity: number = 1;
  @State suffixSymbolHeight: number = 0;
  @State suffixSymbolWidth: number = 0;
  @State breakPoint: BreakPointsType = BreakPointsType.SM;
  @State fontSizeScale: number = 1;
  public onClose?: VoidCallback;
  public onClicked?: VoidCallback;
  private smListener: mediaquery.MediaQueryListener = mediaquery.matchMediaSync('(0vp<width) and (width<600vp)');
  private mdListener: mediaquery.MediaQueryListener = mediaquery.matchMediaSync('(600vp<=width) and (width<840vp)');
  private lgListener: mediaquery.MediaQueryListener = mediaquery.matchMediaSync('(840vp<=width)');
  private symbolEffect: SymbolEffect = new SymbolEffect();
  private environmentCallbackID?: number = undefined;
  private environmentCallback: EnvironmentCallback = {
    onConfigurationUpdated: (configuration) => {
      this.fontSizeScale = configuration.fontSizeScale ?? 1;
    },
    onMemoryLevel() {
    }
  };

  aboutToAppear(): void {
    this.smListener.on('change', (mediaQueryResult: mediaquery.MediaQueryResult) => {
      if (mediaQueryResult.matches) {
        this.breakPoint = BreakPointsType.SM;
      }
    });
    this.mdListener.on('change', (mediaQueryResult: mediaquery.MediaQueryResult) => {
      if (mediaQueryResult.matches) {
        this.breakPoint = BreakPointsType.MD;
      }
    });
    this.lgListener.on('change', (mediaQueryResult: mediaquery.MediaQueryResult) => {
      if (mediaQueryResult.matches) {
        this.breakPoint = BreakPointsType.LG;
      }
    });
    let abilityContext = this.getUIContext().getHostContext() as common.UIAbilityContext | undefined;
    if (abilityContext) {
      this.fontSizeScale = abilityContext.config?.fontSizeScale ?? 1;
      this.environmentCallbackID = abilityContext.getApplicationContext().on('environment', this.environmentCallback);
    }
  }

  aboutToDisappear(): void {
    this.smListener.off('change');
    this.mdListener.off('change');
    this.lgListener.off('change');
    if (this.environmentCallbackID) {
      this.getUIContext().getHostContext()?.getApplicationContext().off('environment', this.environmentCallbackID);
      this.environmentCallbackID = void 0;
    }
  }

  @Builder
  ChipBuilder() {
    Button({ type: ButtonType.Normal }) {
      Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
        if (this.hasPrefixSymbol()) {
          SymbolGlyph()
            .fontSize(this.theme.defaultSymbol.fontSize)
            .fontColor(this.getDefaultSymbolColor())
            .flexShrink(0)
            .attributeModifier(this.getPrefixSymbolModifier())
            .effectStrategy(SymbolEffectStrategy.NONE)
            .symbolEffect(this.symbolEffect, false)
            .symbolEffect(this.symbolEffect, this.theme.defaultSymbol.defaultEffect)
        } else if (this.prefixIcon?.src) {
          Image(this.prefixIcon.src)
            .direction(this.chipDirection)
            .size(this.getPrefixIconSize())
            .fillColor(this.getPrefixIconFilledColor())
            .objectFit(ImageFit.Cover)
            .focusable(false)
            .flexShrink(0)
            .draggable(false)
        }

        Text(this.getChipText())
          .draggable(false)
          .flexShrink(1)
          .focusable(true)
          .maxLines(1)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .textAlign(TextAlign.Center)
          .direction(this.chipDirection)
          .fontSize(this.getLabelFontSize())
          .fontColor(this.getLabelFontColor())
          .fontFamily(this.getLabelFontFamily())
          .fontWeight(this.getLabelFontWeight())
          .margin(this.getLabelMargin())

        if (this.hasSuffixSymbol()) {
          Button({ type: ButtonType.Normal }) {
            SymbolGlyph()
              .fontSize(this.theme.defaultSymbol.fontSize)
              .fontColor(this.getDefaultSymbolColor())
              .attributeModifier(this.getSuffixSymbolModifier())
              .effectStrategy(SymbolEffectStrategy.NONE)
              .symbolEffect(this.symbolEffect, false)
              .symbolEffect(this.symbolEffect, this.theme.defaultSymbol.defaultEffect)
          }
          .onClick(this.getSuffixSymbolAction())
          .accessibilityText(this.getSuffixSymbolAccessibilityText())
          .accessibilityDescription(this.getSuffixSymbolAccessibilityDescription())
          .accessibilityLevel(this.getSuffixSymbolAccessibilityLevel())
          .flexShrink(0)
          .backgroundColor(Color.Transparent)
          .borderRadius(0)
          .padding(0)
          .stateEffect(false)
          .hoverEffect(HoverEffect.None)
        } else if (this.suffixIcon?.src) {
          Button({ type: ButtonType.Normal }) {
            Image(this.suffixIcon.src)
              .direction(this.chipDirection)
              .size(this.getSuffixIconSize())
              .fillColor(this.getSuffixIconFilledColor())
              .objectFit(ImageFit.Cover)
              .draggable(false)
          }
          .backgroundColor(Color.Transparent)
          .borderRadius(0)
          .padding(0)
          .flexShrink(0)
          .stateEffect(false)
          .hoverEffect(HoverEffect.None)
          .size(this.getSuffixIconSize())
          .accessibilityText(this.getSuffixIconAccessibilityText())
          .accessibilityDescription(this.getSuffixIconAccessibilityDescription())
          .accessibilityLevel(this.getSuffixIconAccessibilityLevel())
          .onClick(this.getSuffixIconAction())
        } else if (this.isClosable()) {
          Button({ type: ButtonType.Normal }) {
            SymbolGlyph($r('sys.symbol.xmark'))
              .fontSize(this.theme.defaultSymbol.fontSize)
              .fontColor(this.getDefaultSymbolColor())
          }
          .backgroundColor(Color.Transparent)
          .borderRadius(0)
          .padding(0)
          .flexShrink(0)
          .stateEffect(false)
          .hoverEffect(HoverEffect.None)
          .accessibilityText(this.getCloseIconAccessibilityText())
          .accessibilityDescription(this.getCloseIconAccessibilityDescription())
          .accessibilityLevel(this.getCloseIconAccessibilityLevel())
          .onClick(() => {
            if (!this.isChipEnabled()) {
              return;
            }
            this.onClose?.();
            this.deleteChip();
          })
        }
      }
      .direction(this.chipDirection)
      .padding(this.getChipPadding())
      .size(this.getChipSize())
      .constraintSize(this.getChipConstraintSize())
    }
    .clip(false)
    .padding(0)
    .focusable(true)
    .size(this.getChipSize())
    .enabled(this.isChipEnabled())
    .direction(this.chipDirection)
    .backgroundColor(this.getChipBackgroundColor())
    .borderRadius(this.getChipBorderRadius())
    .scale(this.chipScale)
    .opacity(this.chipOpacity)
    .accessibilityGroup(true)
    .accessibilityDescription(this.getAccessibilityDescription())
    .accessibilityLevel(this.getAccessibilityLevel())
    .accessibilityChecked(this.getAccessibilityChecked())
    .accessibilitySelected(this.getAccessibilitySelected())
    .onClick(this.getChipOnClicked())
    .onKeyEvent((event) => {
      if (event.type === KeyType.Down && event.keyCode === KeyCode.KEYCODE_FORWARD_DEL) {
        this.deleteChip()
      }
    })
  }

  private getCloseIconAccessibilityLevel(): string {
    if (this.closeOptions?.accessibilityLevel === 'no' || this.closeOptions?.accessibilityLevel === 'no-hide-descendants') {
      return this.closeOptions.accessibilityLevel;
    }
    return 'yes';
  }

  private getCloseIconAccessibilityDescription(): Resource | undefined {
    if (typeof this.closeOptions?.accessibilityDescription === 'undefined') {
      return void 0;
    }
    return this.closeOptions.accessibilityDescription as Resource;
  }

  private getCloseIconAccessibilityText(): Resource {
    if (typeof this.closeOptions?.accessibilityText === 'undefined') {
      return $r('sys.string.delete_used_for_accessibility_text');
    }
    return this.closeOptions.accessibilityText as ESObject as Resource;
  }

  getSuffixIconAction(): Callback<ClickEvent> | undefined {
    if (this.suffixIcon?.src) {
      if (!this.suffixIcon?.action) {
        return void 0;
      }
      return () => {
        if (this.isChipEnabled()) {
          this.suffixIcon?.action?.();
        }
      };
    }
    return void 0;
  }

  getSuffixIconFilledColor(): ResourceColor {
    if (this.isChipActivated()) {
      return this.suffixIcon?.activatedFillColor ?? this.theme.suffixIcon.activatedFillColor;
    }
    return this.suffixIcon?.fillColor ?? this.theme.suffixIcon.fillColor;
  }

  getSuffixIconSize(): SizeOptions {
    let suffixIconSize: SizeOptions = { width: 0, height: 0 };
    if (typeof this.suffixIcon?.size?.width !== 'undefined' && this.isValidLength(this.suffixIcon.size.width)) {
      suffixIconSize.width = this.suffixIcon.size.width;
    } else {
      suffixIconSize.width = this.theme.suffixIcon.size.width;
    }
    if (typeof this.suffixIcon?.size?.height !== 'undefined' && this.isValidLength(this.suffixIcon.size.height)) {
      suffixIconSize.height = this.suffixIcon.size.height;
    } else {
      suffixIconSize.height = this.theme.suffixIcon.size.height;
    }
    return suffixIconSize;
  }

  getSuffixIconAccessibilityLevel(): string {
    if (this.suffixIcon?.accessibilityLevel === 'no' || this.suffixIcon?.accessibilityLevel === 'no-hide-descendants') {
      return this.suffixIcon.accessibilityLevel;
    }
    return this.suffixIcon?.action ? 'yes' : 'no';
  }

  getSuffixIconAccessibilityDescription(): Resource | undefined {
    if (typeof this.suffixIcon?.accessibilityDescription === 'undefined') {
      return void 0;
    }
    return this.suffixIcon.accessibilityDescription as ESObject as Resource;
  }

  getSuffixIconAccessibilityText(): Resource | undefined {
    if (typeof this.suffixIcon?.accessibilityText === 'undefined') {
      return void 0;
    }

    return this.suffixIcon.accessibilityText as ESObject as Resource;
  }

  isClosable(): boolean {
    return this.allowClose ?? true;
  }

  getSuffixSymbolModifier(): SymbolGlyphModifier | undefined {
    if (this.isChipActivated()) {
      return this.suffixSymbol?.activated;
    }
    return this.suffixSymbol?.normal;
  }

  getSuffixSymbolAccessibilityLevel(): string {
    if (this.isChipActivated()) {
      if (this.suffixSymbolOptions?.activatedAccessibility?.accessibilityLevel === 'no' ||
        this.suffixSymbolOptions?.activatedAccessibility?.accessibilityLevel === 'no-hide-descendants') {
        return this.suffixSymbolOptions.activatedAccessibility.accessibilityLevel;
      }
      return this.suffixSymbolOptions?.action ? 'yes' : 'no';
    }
    if (this.suffixSymbolOptions?.normalAccessibility?.accessibilityLevel === 'no' ||
      this.suffixSymbolOptions?.normalAccessibility?.accessibilityLevel === 'no-hide-descendants') {
      return this.suffixSymbolOptions.normalAccessibility.accessibilityLevel;
    }
    return this.suffixSymbolOptions?.action ? 'yes' : 'no';
  }

  getSuffixSymbolAccessibilityDescription(): Resource | undefined {
    if (this.isChipActivated()) {
      if (typeof this.suffixSymbolOptions?.activatedAccessibility?.accessibilityDescription !== 'undefined') {
        return this.suffixSymbolOptions.activatedAccessibility.accessibilityDescription as Resource;
      }
      return void 0;
    }
    if (typeof this.suffixSymbolOptions?.normalAccessibility?.accessibilityDescription !== 'undefined') {
      return this.suffixSymbolOptions.normalAccessibility.accessibilityDescription as Resource;
    }
    return void 0;
  }

  getSuffixSymbolAccessibilityText(): Resource | undefined {
    if (this.isChipActivated()) {
      if (typeof this.suffixSymbolOptions?.activatedAccessibility?.accessibilityText !== 'undefined') {
        return this.suffixSymbolOptions.activatedAccessibility.accessibilityText as Resource;
      }
      return void 0;
    }
    if (typeof this.suffixSymbolOptions?.normalAccessibility?.accessibilityText !== 'undefined') {
      return this.suffixSymbolOptions.normalAccessibility.accessibilityText as Resource;
    }
    return void 0;
  }

  getSuffixSymbolAction(): Callback<ClickEvent> | undefined {
    if (typeof this.suffixSymbolOptions?.action === 'undefined') {
      return void 0;
    }
    return () => {
      if (!this.isChipEnabled()) {
        return;
      }
      this.suffixSymbolOptions?.action?.();
    };
  }

  hasSuffixSymbol(): boolean {
    return !!(this.suffixSymbol?.normal || this.suffixSymbol?.activated);
  }

  getPrefixIconFilledColor(): ResourceColor {
    if (this.isChipActivated()) {
      return this.prefixIcon?.activatedFillColor ?? this.theme.prefixIcon.activatedFillColor;
    }
    return this.prefixIcon?.fillColor ?? this.theme.prefixIcon.fillColor;
  }

  getPrefixIconSize(): SizeOptions {
    let prefixIconSize: SizeOptions = { width: 0, height: 0 };
    if (typeof this.prefixIcon?.size?.width !== 'undefined' && this.isValidLength(this.prefixIcon.size.width)) {
      prefixIconSize.width = this.prefixIcon.size.width;
    } else {
      prefixIconSize.width = this.theme.prefixIcon.size.width
    }
    if (typeof this.prefixIcon?.size?.height !== 'undefined' && this.isValidLength(this.prefixIcon.size.height)) {
      prefixIconSize.height = this.prefixIcon.size.height;
    } else {
      prefixIconSize.height = this.theme.prefixIcon.size.height
    }
    return prefixIconSize;
  }

  getPrefixSymbolModifier(): SymbolGlyphModifier | undefined {
    if (this.isChipActivated()) {
      return this.prefixSymbol?.activated;
    }
    return this.prefixSymbol?.normal;
  }

  getDefaultSymbolColor(): ResourceColor[] {
    return this.isChipActivated() ? this.theme.defaultSymbol.activatedFontColor :
    this.theme.defaultSymbol.normalFontColor;
  }

  hasPrefixSymbol(): boolean {
    return !!(this.prefixSymbol?.normal || this.prefixSymbol?.activated);
  }

  getChipConstraintSize(): ConstraintSizeOptions | undefined {
    const constraintSize: ConstraintSizeOptions = {};
    if (typeof this.chipSize === 'string') {
      constraintSize.maxWidth = this.getChipMaxWidth();
      constraintSize.minHeight =
        this.chipSize === ChipSize.SMALL ? this.theme.chipNode.smallHeight : this.theme.chipNode.normalHeight;
    } else {
      if (typeof this.chipSize?.width === 'undefined' || !this.isValidLength(this.chipSize.width)) {
        constraintSize.maxWidth = this.getChipMaxWidth();
      }
      if (typeof this.chipSize?.height === 'undefined' || !this.isValidLength(this.chipSize.height)) {
        constraintSize.minHeight = this.theme.chipNode.normalHeight;
      }
    }
    return constraintSize;
  }

  getChipMaxWidth(): Length | undefined {
    if (this.fontSizeScale >= this.theme.chipNode.suitAgeScale) {
      return void 0;
    }
    if (this.breakPoint === BreakPointsType.SM) {
      return this.theme.chipNode.breakPointConstraintWidth.breakPointSmMaxWidth;
    }
    if (this.breakPoint === BreakPointsType.MD) {
      return this.theme.chipNode.breakPointConstraintWidth.breakPointMdMaxWidth;
    }
    if (this.breakPoint === BreakPointsType.LG) {
      return this.theme.chipNode.breakPointConstraintWidth.breakPointLgMaxWidth;
    }
    return void 0;
  }

  getChipSize(): SizeOptions | undefined {
    const chipSize: SizeOptions = {
      width: 'auto',
      height: 'auto'
    };

    if (typeof this.chipSize !== 'string') {
      if (typeof this.chipSize?.width !== 'undefined' && this.isValidLength(this.chipSize.width)) {
        chipSize.width = this.chipSize.width;
      }
      if (typeof this.chipSize?.height !== 'undefined' && this.isValidLength(this.chipSize.height)) {
        chipSize.height = this.chipSize.height;
      }
    }

    return chipSize;
  }

  getChipPadding(): Length | Padding | LocalizedPadding {
    return this.isSmallChipSize() ? this.theme.chipNode.localizedSmallPadding :
    this.theme.chipNode.localizedNormalPadding;
  }

  getLabelMargin(): Length | Padding | LocalizedPadding {
    const localizedLabelMargin: LocalizedMargin = {
      start: LengthMetrics.vp(0),
      end: LengthMetrics.vp(0),
    };
    const defaultLocalizedMargin =
      this.isSmallChipSize() ? this.theme.label.localizedSmallMargin : this.theme.label.localizedNormalMargin;

    if (typeof this.label?.localizedLabelMargin?.start !== 'undefined' &&
      this.label.localizedLabelMargin.start.value >= 0) {
      localizedLabelMargin.start = this.label.localizedLabelMargin.start;
    } else if (this.hasPrefix()) {
      localizedLabelMargin.start = defaultLocalizedMargin.start;
    }

    if (typeof this.label?.localizedLabelMargin?.end !== 'undefined' &&
      this.label.localizedLabelMargin.end.value >= 0) {
      localizedLabelMargin.end = this.label.localizedLabelMargin.end;
    } else if (this.hasSuffix()) {
      localizedLabelMargin.end = defaultLocalizedMargin.end;
    }
    if (typeof this.label?.localizedLabelMargin === 'object') {
      return localizedLabelMargin;
    }
    if (typeof this.label.labelMargin === 'object') {
      const labelMargin: Margin = { left: 0, right: 0 };
      const defaultLabelMargin: Margin =
        this.isSmallChipSize() ? this.theme.label.smallMargin : this.theme.label.normalMargin;
      if (typeof this.label?.labelMargin?.left !== 'undefined' && this.isValidLength(this.label.labelMargin.left)) {
        labelMargin.left = this.label.labelMargin.left;
      } else if (this.hasPrefix()) {
        labelMargin.left = defaultLabelMargin.left;
      }
      if (typeof this.label?.labelMargin?.right !== 'undefined' && this.isValidLength(this.label.labelMargin.right)) {
        labelMargin.right = this.label.labelMargin.right;
      } else if (this.hasSuffix()) {
        labelMargin.right = defaultLabelMargin.right;
      }
      return labelMargin;
    }
    return localizedLabelMargin;
  }

  hasSuffix(): boolean {
    if (this.suffixIcon?.src) {
      return true;
    }
    return this.isChipActivated() ? !!this.suffixSymbol?.activated : !!this.suffixSymbol?.normal;
  }

  private hasPrefix(): boolean {
    if (this.prefixIcon?.src) {
      return true;
    }
    return this.isChipActivated() ? !!this.prefixSymbol?.activated : !!this.prefixSymbol?.normal;
  }

  getLabelFontWeight(): string | number | FontWeight {
    return this.isChipActivated() ? FontWeight.Medium : FontWeight.Regular;
  }

  getLabelFontFamily(): ResourceStr {
    return this.label?.fontFamily ?? this.theme.label.fontFamily;
  }

  getLabelFontColor(): ResourceColor {
    if (this.isChipActivated()) {
      return this.label?.activatedFontColor ?? this.theme.label.activatedFontColor;
    }
    return this.label?.fontColor ?? this.theme.label.fontColor;
  }

  getLabelFontSize(): Dimension {
    if (typeof this.label.fontSize !== 'undefined' && this.isValidLength(this.label.fontSize)) {
      return this.label.fontSize;
    }
    if (this.isSmallChipSize()) {
      return this.theme.label.smallFontSize;
    }
    return this.theme.label.defaultFontSize;
  }

  getChipText(): ResourceStr {
    return this.label?.text ?? '';
  }

  deleteChip() {
    animateTo({ curve: Curve.Sharp, duration: 150 }, () => {
      this.chipOpacity = 0;
    });
    animateTo({
      curve: Curve.FastOutLinearIn,
      duration: 150,
      onFinish: () => {
        this.isChipExist = false;
      }
    }, () => {
      this.chipScale = { x: 0.85, y: 0.85 };
    })
  }

  getChipOnClicked(): Callback<ClickEvent> | undefined {
    if (this.onClicked) {
      return this.onClicked.bind(this);
    }
    return void 0;
  }

  private getAccessibilitySelected(): boolean | undefined {
    if (this.getChipAccessibilitySelectedType() === AccessibilitySelectedType.SELECTED) {
      return this.isChipActivated();
    }
    return void 0;
  }

  private getAccessibilityChecked(): boolean | undefined {
    if (this.getChipAccessibilitySelectedType() === AccessibilitySelectedType.CHECKED) {
      return this.isChipActivated();
    }
    return void 0;
  }

  private getChipAccessibilitySelectedType(): AccessibilitySelectedType {
    if (typeof this.chipActivated === 'undefined') {
      return AccessibilitySelectedType.CLICKED;
    }
    return this.chipAccessibilitySelectedType ?? AccessibilitySelectedType.CHECKED;
  }

  private getAccessibilityLevel(): string | undefined {
    return this.chipAccessibilityLevel;
  }

  private getAccessibilityDescription(): Resource | undefined {
    if (typeof this.chipAccessibilityDescription === 'undefined') {
      return void 0;
    }
    return this.chipAccessibilityDescription as ESObject as Resource;
  }

  isChipEnabled(): boolean {
    return this.chipEnabled ?? true;
  }

  getChipBorderRadius(): Dimension {
    if (typeof this.chipNodeRadius !== 'undefined' && this.isValidLength(this.chipNodeRadius)) {
      return this.chipNodeRadius;
    }
    return this.isSmallChipSize() ? this.theme.chipNode.smallBorderRadius : this.theme.chipNode.normalBorderRadius;
  }

  isSmallChipSize() {
    return typeof this.chipSize === 'string' && this.chipSize === ChipSize.SMALL;
  }

  getChipBackgroundColor(): ResourceColor {
    if (this.isChipActivated()) {
      return this.getColor(this.chipNodeActivatedBackgroundColor, this.theme.chipNode.activatedBackgroundColor);
    }
    return this.getColor(this.chipNodeBackgroundColor, this.theme.chipNode.backgroundColor);
  }

  getColor(color: ResourceColor | undefined, defaultColor: ResourceColor): ResourceColor {
    if (!color) {
      return defaultColor;
    }
    try {
      ColorMetrics.resourceColor(color).color;
      return color;
    } catch (e) {
      console.error(`[Chip] failed to get color`);
      return Color.Transparent;
    }
  }

  isChipActivated() {
    return this.chipActivated ?? false;
  }

  isValidLength(length: Length): boolean {
    if (typeof length === 'number') {
      return length >= 0;
    } else if (typeof length === 'string') {
      return this.isValidLengthString(length);
    } else if (typeof length === 'object') {
      const resource = length as Resource;
      const resourceManager = this.getUIContext().getHostContext()?.resourceManager;
      if (!resourceManager) {
        console.error('[Chip] failed to get resourceManager.');
        return false;
      }
      switch (resource.type) {
        case RESOURCE_TYPE_FLOAT:
        case RESOURCE_TYPE_INTEGER:
          return resourceManager.getNumber(resource) >= 0;
        case RESOURCE_TYPE_STRING:
          return this.isValidLengthString(resourceManager.getStringSync(resource));
        default:
          return false;
      }
    }
    return false;
  }

  isValidLengthString(length: string): boolean {
    const matches = length.match(/(-?\d+(?:\.\d+)?)_?(fp|vp|px|lpx)?$/i);
    if (!matches || matches.length < 3) {
      return false;
    }
    return Number.parseInt(matches[1], 10) >= 0;
  }

  build() {
    if (this.isChipExist) {
      this.ChipBuilder()
    }
  }
}
