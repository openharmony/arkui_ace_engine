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

import { KeyCode } from '@ohos.multimodalInput.keyCode';
import measure from '@ohos.measure';
import mediaquery from '@ohos.mediaquery';
import resourceManager from '@ohos.resourceManager';
import { ColorMetrics, LengthMetrics, LengthUnit } from '@ohos.arkui.node';
import EnvironmentCallback from '@ohos.app.ability.EnvironmentCallback';
import { SymbolGlyphModifier } from '@ohos.arkui.modifier';
import componentUtils from '@ohos.arkui.componentUtils';
import hilog from '@ohos.hilog';
import common from '@ohos.app.ability.common';

const RESOURCE_TYPE_STRING = 10003;
const RESOURCE_TYPE_FLOAT = 10002;
const RESOURCE_TYPE_INTEGER = 10007;

export enum ChipSize {
  NORMAL = "NORMAL",
  SMALL = "SMALL"
}

enum BreakPointsType {
  SM = "SM",
  MD = "MD",
  LG = "LG"
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
    fontFamily: "HarmonyOS Sans",
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

const noop = () => {
};

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

function isValidResource(context: Context | undefined, value: Resource) {
  const resourceManager = context?.resourceManager;
  if (value === void (0) || value === null || resourceManager === void (0)) {
    return false;
  }
  if (value.type !== RESOURCE_TYPE_STRING && value.type !== RESOURCE_TYPE_INTEGER &&
    value.type !== RESOURCE_TYPE_FLOAT) {
    return false;
  }

  if (value.type === RESOURCE_TYPE_INTEGER || value.type === RESOURCE_TYPE_FLOAT) {
    if (resourceManager.getNumber(value.id) >= 0) {
      return true;
    } else {
      return false;
    }
  }

  if (value.type === RESOURCE_TYPE_STRING && !isValidDimensionString(resourceManager.getStringSync(value.id))) {
    return false;
  } else {
    return true;
  }
}

@Component
export struct ChipComponent {
  private theme: ChipTheme = defaultTheme;
  @Prop chipSize: ChipSize | SizeOptions = ChipSize.NORMAL
  @Prop allowClose: boolean = true
  @Prop closeOptions?: CloseOptions
  @Prop chipDirection: Direction = Direction.Auto
  @Prop prefixIcon: PrefixIconOptions = { src: "" }
  @Prop prefixSymbol: ChipSymbolGlyphOptions
  @Prop label: LabelOptions = { text: "" }
  @Prop suffixIcon: SuffixIconOptions = { src: "" }
  @Prop suffixSymbol?: ChipSymbolGlyphOptions
  @Prop suffixSymbolOptions?: ChipSuffixSymbolGlyphOptions
  @Prop chipNodeBackgroundColor: ResourceColor = this.theme.chipNode.backgroundColor
  @Prop chipNodeActivatedBackgroundColor: ResourceColor = this.theme.chipNode.activatedBackgroundColor
  @Prop chipNodeRadius: Dimension | undefined = void (0)
  @Prop chipEnabled: boolean = true
  @Prop chipActivated?: boolean
  @Prop chipAccessibilitySelectedType?: AccessibilitySelectedType
  @Prop chipAccessibilityDescription?: ResourceStr
  @Prop chipAccessibilityLevel?: string
  @State isHover: boolean = false
  @State chipScale: ScaleOptions = { x: 1, y: 1 }
  @State chipOpacity: number = 1
  @State chipBlendColor: ResourceColor = Color.Transparent
  @State deleteChip: boolean = false
  @State chipNodeOnFocus: boolean = false
  @State useDefaultSuffixIcon: boolean = false
  private chipNodeSize: SizeOptions = {}
  private onClose: () => void = noop
  private onClicked: () => void = noop
  @State suffixIconOnFocus: boolean = false
  @State chipBreakPoints: BreakPointsType = BreakPointsType.SM
  private smListener: mediaquery.MediaQueryListener = mediaquery.matchMediaSync('(0vp<width) and (width<600vp)')
  private mdListener: mediaquery.MediaQueryListener = mediaquery.matchMediaSync('(600vp<=width) and (width<840vp)')
  private lgListener: mediaquery.MediaQueryListener = mediaquery.matchMediaSync('(840vp<=width)')
  @State private isShowPressedBackGroundColor: boolean = false
  @State fontSizeScale: number | undefined = 0
  @State fontWeightScale: number | undefined = 0
  private callbacks: EnvironmentCallback = {
    onConfigurationUpdated: (configuration) => {
      this.fontSizeScale = configuration.fontSizeScale;
      this.fontWeightScale = configuration.fontWeightScale;
    }, onMemoryLevel() {
    }
  }
  private callbackId: number | undefined = undefined
  @State prefixSymbolWidth: Length | undefined =
    this.toVp(componentUtils.getRectangleById('PrefixSymbolGlyph')?.size?.width);
  @State suffixSymbolWidth: Length | undefined =
    this.toVp(componentUtils.getRectangleById('SuffixSymbolGlyph')?.size?.width);
  @State allowCloseSymbolWidth: Length | undefined =
    this.toVp(componentUtils.getRectangleById('AllowCloseSymbolGlyph')?.size?.width);
  @State symbolEffect: SymbolEffect = new SymbolEffect();

  private isChipSizeEnum(): boolean {
    return typeof (this.chipSize) === 'string'
  }

  private getLabelFontSize(): Dimension {
    if (this.label?.fontSize !== void (0) && this.toVp(this.label.fontSize) >= 0) {
      return this.label.fontSize
    } else {
      if (this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) {
        try {
          resourceManager.getSystemResourceManager()
            .getNumberByName((((this.theme.label.smallFontSize as Resource).params as string[])[0]).split('.')[2])
          return this.theme.label.smallFontSize
        } catch (error) {
          return this.theme.label.defaultFontSize
        }
      } else {
        try {
          resourceManager.getSystemResourceManager()
            .getNumberByName((((this.theme.label.normalFontSize as Resource).params as string[])[0]).split('.')[2])
          return this.theme.label.normalFontSize
        } catch (error) {
          return this.theme.label.defaultFontSize
        }
      }
    }
  }

  private getLabelFontColor(): ResourceColor {
    if (this.getChipActive()) {
      return this.label?.activatedFontColor ?? this.theme.label.activatedFontColor
    }
    return this.label?.fontColor ?? this.theme.label.fontColor
  }

  private getLabelFontFamily(): string {
    return this.label?.fontFamily ?? this.theme.label.fontFamily
  }

  private getLabelFontWeight(): FontWeight {
    if (this.getChipActive()) {
      return FontWeight.Medium
    }
    return FontWeight.Regular
  }

  private lengthMetricsToVp(lengthMetrics?: LengthMetrics): number {
    let defaultValue: number = 0;
    if (lengthMetrics) {
      switch (lengthMetrics.unit) {
        case LengthUnit.PX:
          return px2vp(lengthMetrics.value)
        case LengthUnit.VP:
          return lengthMetrics.value
        case LengthUnit.FP:
          px2vp(fp2px(lengthMetrics.value))
          break
        case LengthUnit.PERCENT:
          return Number.NEGATIVE_INFINITY
        case LengthUnit.LPX:
          return px2vp(lpx2px(lengthMetrics.value))
      }
    }
    return defaultValue;
  }

  private toVp(value: Dimension | Length | undefined): number {
    if (value === void (0)) {
      return Number.NEGATIVE_INFINITY
    }
    switch (typeof (value)) {
      case 'number':
        return value as number
      case 'object':
        try {
          let returnValue = this.lengthMetricsToVp(LengthMetrics.resource(value));
          if (returnValue === 0 &&
            !isValidResource(getContext(this), value)) {
            return Number.NEGATIVE_INFINITY;
          }
          return returnValue;
        } catch (error) {
          return Number.NEGATIVE_INFINITY
        }
      case 'string':
        let regex: RegExp = new RegExp("(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$", "i");
        let matches: RegExpMatchArray | null = value.match(regex);
        if (!matches) {
          return Number.NEGATIVE_INFINITY
        }
        let length: number = Number(matches?.[1] ?? 0);
        let unit: string = matches?.[2] ?? 'vp'
        switch (unit.toLowerCase()) {
          case 'px':
            length = px2vp(length)
            break
          case 'fp':
            length = px2vp(fp2px(length))
            break
          case 'lpx':
            length = px2vp(lpx2px(length))
            break
          case '%':
            length = Number.NEGATIVE_INFINITY
            break
          case 'vp':
            break
          default:
            break
        }
        return length
      default:
        return Number.NEGATIVE_INFINITY
    }
  }

  private getLabelMargin(): Margin {
    let labelMargin: Margin = { left: 0, right: 0 }
    if (this.label?.labelMargin?.left !== void (0) && this.toVp(this.label.labelMargin.left) >= 0) {
      labelMargin.left = this.label?.labelMargin?.left
    } else if ((this.prefixSymbol?.normal || this.prefixSymbol?.activated) || this.prefixIcon?.src) {
      if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
        labelMargin.left = this.theme.label.smallMargin.left
      } else {
        labelMargin.left = this.theme.label.normalMargin.left
      }
    }
    if (this.label?.labelMargin?.right !== void (0) && this.toVp(this.label.labelMargin.right) >= 0) {
      labelMargin.right = this.label?.labelMargin?.right
    } else if ((this.suffixSymbol?.normal || this.suffixSymbol?.activated) ||
      this.suffixIcon?.src || this.useDefaultSuffixIcon) {
      if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
        labelMargin.right = this.theme.label.smallMargin.right
      } else {
        labelMargin.right = this.theme.label.normalMargin.right
      }
    }
    return labelMargin
  }

  private getLocalizedLabelMargin(): LocalizedMargin {
    let localizedLabelMargin: LocalizedMargin = { start: LengthMetrics.vp(0), end: LengthMetrics.vp(0) }
    if (this.label?.localizedLabelMargin?.start?.value !== void (0) &&
      this.lengthMetricsToVp(this.label.localizedLabelMargin.start) >= 0) {
      localizedLabelMargin.start = this.label?.localizedLabelMargin?.start
    } else if ((this.prefixSymbol?.normal || this.prefixSymbol?.activated) || this.prefixIcon?.src) {
      if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
        localizedLabelMargin.start = this.theme.label.localizedSmallMargin.start
      } else {
        localizedLabelMargin.start = this.theme.label.localizedNormalMargin.start
      }
    }
    if (this.label?.localizedLabelMargin?.end?.value !== void (0) &&
      this.lengthMetricsToVp(this.label.localizedLabelMargin.end) >= 0) {
      localizedLabelMargin.end = this.label?.localizedLabelMargin?.end
    } else if ((this.suffixSymbol?.normal || this.suffixSymbol?.activated) ||
      this.suffixIcon?.src || this.useDefaultSuffixIcon) {
      if (this.isChipSizeEnum() && this.chipSize == ChipSize.SMALL) {
        localizedLabelMargin.end = this.theme.label.localizedSmallMargin.end
      } else {
        localizedLabelMargin.end = this.theme.label.localizedNormalMargin.end
      }
    }
    return localizedLabelMargin
  }

  private getLabelStartEndVp(): LocalizedMargin {
    let labelMargin: LocalizedMargin = this.getLocalizedLabelMargin()
    if (this.label && (this.label.labelMargin !== void (0)) && (this.label.localizedLabelMargin === void (0))) {
      let margin: Margin = this.getLabelMargin()
      return {
        start: LengthMetrics.vp(this.toVp(margin.left)),
        end: LengthMetrics.vp(this.toVp(margin.right))
      }
    }
    return {
      start: LengthMetrics.vp(this.lengthMetricsToVp(labelMargin.start)),
      end: LengthMetrics.vp(this.lengthMetricsToVp(labelMargin.end))
    }
  }

  private getActualLabelMargin(): Margin | LocalizedMargin {
    let localizedLabelMargin: LocalizedMargin = this.getLocalizedLabelMargin()
    if (this.label && this.label.localizedLabelMargin !== void (0)) {
      return localizedLabelMargin
    }
    if (this.label && this.label.labelMargin !== void (0)) {
      return this.getLabelMargin()
    }
    return localizedLabelMargin
  }

  private getSuffixIconSize(): SizeOptions {
    let suffixIconSize: SizeOptions = { width: 0, height: 0 }
    if (this.suffixIcon?.size?.width !== void (0) && this.toVp(this.suffixIcon?.size?.width) >= 0) {
      suffixIconSize.width = this.suffixIcon?.size?.width
    } else {
      if (this.getSuffixIconSrc()) {
        suffixIconSize.width = this.theme.suffixIcon.size.width
      } else {
        suffixIconSize.width = 0
      }
    }
    if (this.suffixIcon?.size?.height !== void (0) && this.toVp(this.suffixIcon?.size?.height) >= 0) {
      suffixIconSize.height = this.suffixIcon?.size?.height
    } else {
      if (this.getSuffixIconSrc()) {
        suffixIconSize.height = this.theme.suffixIcon.size.height
      } else {
        suffixIconSize.height = 0
      }
    }
    return suffixIconSize
  }

  private getPrefixIconSize(): SizeOptions {
    let prefixIconSize: SizeOptions = { width: 0, height: 0 }
    if (this.prefixIcon?.size?.width !== void (0) && this.toVp(this.prefixIcon?.size?.width) >= 0) {
      prefixIconSize.width = this.prefixIcon?.size?.width
    } else {
      if (this.prefixIcon?.src) {
        prefixIconSize.width = this.theme.prefixIcon.size.width
      } else {
        prefixIconSize.width = 0
      }
    }
    if (this.prefixIcon?.size?.height !== void (0) && this.toVp(this.prefixIcon?.size?.height) >= 0) {
      prefixIconSize.height = this.prefixIcon?.size?.height
    } else {
      if (this.prefixIcon?.src) {
        prefixIconSize.height = this.theme.prefixIcon.size.height
      } else {
        prefixIconSize.height = 0
      }
    }
    return prefixIconSize
  }

  private getPrefixIconFilledColor(): ResourceColor {
    if (this.getChipActive()) {
      return this.prefixIcon?.activatedFillColor ?? this.theme.prefixIcon.activatedFillColor
    }
    return this.prefixIcon?.fillColor ?? this.theme.prefixIcon.fillColor
  }

  private getSuffixIconFilledColor(): ResourceColor {
    if (this.getChipActive()) {
      return this.suffixIcon?.activatedFillColor ?? this.theme.suffixIcon.activatedFillColor
    }
    return this.suffixIcon?.fillColor ?? this.theme.suffixIcon.fillColor
  }

  private getDefaultSymbolColor(): Array<ResourceColor> {
    if (this.getChipActive()) {
      return this.theme.defaultSymbol.activatedFontColor
    }
    return this.theme.defaultSymbol.normalFontColor
  }

  private getPrefixSymbolModifier(): SymbolGlyphModifier | undefined {
    if (this.getChipActive()) {
      return this.prefixSymbol?.activated
    }
    return this.prefixSymbol?.normal
  }

  private getSuffixSymbolModifier(): SymbolGlyphModifier | undefined {
    if (this.getChipActive()) {
      return this.suffixSymbol?.activated
    }
    return this.suffixSymbol?.normal
  }

  private getSuffixIconFocusable(): boolean {
    return (this.useDefaultSuffixIcon && (this.allowClose ?? true)) || this.suffixIcon?.action !== void (0)
  }

  private getChipNodePadding(): LocalizedPadding {
    return (this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) ? this.theme.chipNode.localizedSmallPadding :
    this.theme.chipNode.localizedNormalPadding
  }

  private getChipNodeRadius(): Dimension {
    if (this.chipNodeRadius !== void (0) && this.toVp(this.chipNodeRadius) >= 0) {
      return this.chipNodeRadius as Dimension
    } else {
      return ((this.isChipSizeEnum() && this.chipSize === ChipSize.SMALL) ?
      this.theme.chipNode.smallBorderRadius : this.theme.chipNode.normalBorderRadius)
    }
  }

  private getChipNodeBackGroundColor(): ResourceColor {
    let currentColor: ResourceColor;

    if (this.getChipActive()) {
      currentColor = this.chipNodeActivatedBackgroundColor ?? this.theme.chipNode.activatedBackgroundColor
    } else {
      currentColor = this.chipNodeBackgroundColor ?? this.theme.chipNode.backgroundColor
    }

    let sourceColor: ColorMetrics;

    try {
      sourceColor = ColorMetrics.resourceColor(currentColor);
    } catch (err) {
      hilog.error(0x3900, 'Ace', `Chip resourceColor, error: ${err.toString()}`);
      sourceColor = ColorMetrics.resourceColor(Color.Transparent);
    }
    if (!this.isShowPressedBackGroundColor) {
      return sourceColor.color
    }

    return sourceColor
      .blendColor(ColorMetrics.resourceColor("#19000000"))
      .color
  }

  private getChipNodeHeight(): Length {
    if (this.isChipSizeEnum()) {
      return this.chipSize === ChipSize.SMALL ? this.theme.chipNode.smallHeight : this.theme.chipNode.normalHeight
    } else {
      this.chipNodeSize = this.chipSize as SizeOptions
      return (this.chipNodeSize?.height !== void (0) && this.toVp(this.chipNodeSize?.height) >= 0) ?
      this.toVp(this.chipNodeSize?.height) : this.theme.chipNode.normalHeight
    }
  }

  private getLabelWidth(): number {
    return px2vp(measure.measureText({
      textContent: this.label?.text ?? "",
      fontSize: this.getLabelFontSize(),
      fontFamily: this.label?.fontFamily ?? this.theme.label.fontFamily,
      fontWeight: this.getLabelFontWeight(),
      maxLines: 1,
      overflow: TextOverflow.Ellipsis,
      textAlign: TextAlign.Center
    }))
  }

  private getCalculateChipNodeWidth(): number {
    let calWidth: number = 0
    let startEndVp: LocalizedMargin = this.getLabelStartEndVp()
    calWidth += this.getChipNodePadding().start?.value ?? 0
    calWidth += this.toVp(this.getPrefixChipWidth())
    calWidth += this.toVp(startEndVp.start?.value ?? 0)
    calWidth += this.getLabelWidth()
    calWidth += this.toVp(startEndVp.end?.value ?? 0)
    calWidth += this.toVp(this.getSuffixChipWidth())
    calWidth += this.getChipNodePadding().end?.value ?? 0
    return calWidth
  }

  private getPrefixChipWidth(): Length | undefined {
    if (this.prefixSymbol?.normal || this.prefixSymbol?.activated) {
      return this.prefixSymbolWidth
    } else if (this.prefixIcon?.src) {
      return this.getPrefixIconSize().width
    } else {
      return 0
    }
  }

  private getSuffixChipWidth(): Length | undefined {
    if (this.suffixSymbol?.normal || this.suffixSymbol?.activated) {
      return this.suffixSymbolWidth
    } else if (this.suffixIcon?.src) {
      return this.getSuffixIconSize().width
    } else if (!this.suffixIcon?.src && (this.allowClose ?? true)) {
      return this.allowCloseSymbolWidth
    } else {
      return 0
    }
  }

  private getReserveChipNodeWidth(): number {
    return this.getCalculateChipNodeWidth() - this.getLabelWidth() + (this.theme.chipNode.minLabelWidth as number)
  }

  private getChipEnable(): boolean {
    return this.chipEnabled || this.chipEnabled === void (0)
  }

  private getChipActive(): boolean {
    if (typeof this.chipActivated === 'undefined') {
      return false
    }
    return this.chipActivated
  }

  private getChipNodeOpacity(): number {
    return this.chipOpacity
  }

  private handleTouch(event: TouchEvent) {
    if (!this.getChipEnable()) {
      return
    }
    if (this.isHover) {
      if (event.type === TouchType.Down || event.type === TouchType.Move) {
        this.isShowPressedBackGroundColor = true
      } else if (event.type === TouchType.Up) {
        this.isShowPressedBackGroundColor = false
      } else {
        this.isShowPressedBackGroundColor = false
      }
    } else {
      if (event.type === TouchType.Down || event.type === TouchType.Move) {
        this.isShowPressedBackGroundColor = true
      } else if (event.type === TouchType.Up) {
        this.isShowPressedBackGroundColor = false
      } else {
        this.isShowPressedBackGroundColor = false
      }
    }
  }

  private hoverAnimate(isHover: boolean) {
    if (!this.getChipEnable()) {
      return
    }
    this.isHover = isHover
    if (this.isHover) {
      this.isShowPressedBackGroundColor = true
    } else {
      this.isShowPressedBackGroundColor = false
    }
  }

  private deleteChipNodeAnimate() {
    animateTo({ duration: 150, curve: Curve.Sharp }, () => {
      this.chipOpacity = 0
      this.chipBlendColor = Color.Transparent
    })
    animateTo({
      duration: 150, curve: Curve.FastOutLinearIn, onFinish: () => {
        this.deleteChip = true
      }
    },
      () => {
        this.chipScale = { x: 0.85, y: 0.85 }
      })
  }

  private getSuffixIconSrc(): ResourceStr | undefined {
    this.useDefaultSuffixIcon = !this.suffixIcon?.src && (this.allowClose ?? true)
    return this.useDefaultSuffixIcon ? this.theme.suffixIcon.defaultDeleteIcon : (this.suffixIcon?.src ?? void (0))
  }

  private getChipNodeWidth(): Length {
    if (!this.isChipSizeEnum()) {
      this.chipNodeSize = this.chipSize as SizeOptions
      if (this.chipNodeSize?.width !== void (0) && this.toVp(this.chipNodeSize.width) >= 0) {
        return this.toVp(this.chipNodeSize.width)
      }
    }
    let constraintWidth: ConstraintSizeOptions = this.getChipConstraintWidth()
    return Math.min(Math.max(this.getCalculateChipNodeWidth(),
      constraintWidth.minWidth as number), constraintWidth.maxWidth as number);
  }

  private getFocusOverlaySize(): SizeOptions {
    return {
      width: Math.max(this.getChipNodeWidth() as number, this.getChipConstraintWidth().minWidth as number) + 8,
      height: this.getChipNodeHeight() as number + 8
    }
  }

  private getChipConstraintWidth(): ConstraintSizeOptions {
    let calcMinWidth: number = this.getReserveChipNodeWidth()

    let constraintWidth: number = this.getCalculateChipNodeWidth()
    let constraintSize: ConstraintSizeOptions
    switch (this.chipBreakPoints) {
      case BreakPointsType.SM:
        constraintSize = {
          minWidth: calcMinWidth,
          maxWidth: Math.min(constraintWidth, this.theme.chipNode.breakPointConstraintWidth.breakPointSmMaxWidth)
        }
        break
      case BreakPointsType.MD:
        constraintSize = {
          minWidth: Math.max(constraintWidth, this.theme.chipNode.breakPointConstraintWidth.breakPointMinWidth),
          maxWidth: Math.min(constraintWidth, this.theme.chipNode.breakPointConstraintWidth.breakPointMdMaxWidth)
        }
        break
      case BreakPointsType.LG:
        constraintSize = {
          minWidth: Math.max(constraintWidth, this.theme.chipNode.breakPointConstraintWidth.breakPointMinWidth),
          maxWidth: Math.min(constraintWidth, this.theme.chipNode.breakPointConstraintWidth.breakPointLgMaxWidth)
        }
        break
      default:
        constraintSize = { minWidth: calcMinWidth, maxWidth: constraintWidth }
        break
    }
    constraintSize.minWidth = Math.min(Math.max(this.getCalculateChipNodeWidth(),
      constraintSize.minWidth as number), constraintSize.maxWidth as number)
    constraintSize.minHeight = this.getChipNodeHeight()
    if (!this.isChipSizeEnum() && this.chipNodeSize?.height !== void (0) && this.toVp(this.chipNodeSize?.height) >= 0) {
      constraintSize.maxHeight = this.toVp(this.chipNodeSize.height)
      constraintSize.minHeight = this.toVp(this.chipNodeSize.height)
    }
    if (!this.isChipSizeEnum() && this.chipNodeSize?.width !== void (0) && this.toVp(this.chipNodeSize?.width) >= 0) {
      constraintSize.minWidth = this.toVp(this.chipNodeSize.width)
      constraintSize.maxWidth = this.toVp(this.chipNodeSize.width)
    } else if (this.toVp(this.fontSizeScale) >= this.theme.chipNode.suitAgeScale) {
      constraintSize.minWidth = void (0)
      constraintSize.maxWidth = void (0)
    }
    return constraintSize
  }

  @Builder
  focusOverlay() {
    Stack() {
      if (this.chipNodeOnFocus && !this.suffixIconOnFocus) {
        Stack()
          .direction(this.chipDirection)
          .borderRadius(this.toVp(this.getChipNodeRadius()) + 4)
          .size(this.getFocusOverlaySize())
          .borderColor(this.theme.chipNode.focusOutlineColor)
          .borderWidth(this.theme.chipNode.borderWidth)
      }
    }
    .direction(this.chipDirection)
    .size({ width: 1, height: 1 })
    .align(Alignment.Center)
  }

  @Styles
  suffixIconFocusStyles() {
    .borderColor(this.theme.chipNode.focusOutlineColor)
    .borderWidth(this.getSuffixIconFocusable() ? this.theme.chipNode.borderWidth : 0)
  }

  @Styles
  suffixIconNormalStyles() {
    .borderColor(Color.Transparent)
    .borderWidth(0)
  }

  aboutToAppear() {
    let uiContent: UIContext = this.getUIContext();
    this.fontSizeScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
    this.smListener.on("change", (mediaQueryResult: mediaquery.MediaQueryResult) => {
      if (mediaQueryResult.matches) {
        this.chipBreakPoints = BreakPointsType.SM
      }
    })
    this.mdListener.on("change", (mediaQueryResult: mediaquery.MediaQueryResult) => {
      if (mediaQueryResult.matches) {
        this.chipBreakPoints = BreakPointsType.MD
      }
    })
    this.lgListener.on("change", (mediaQueryResult: mediaquery.MediaQueryResult) => {
      if (mediaQueryResult.matches) {
        this.chipBreakPoints = BreakPointsType.LG
      }
    })
    this.callbackId = this.getUIContext()
      .getHostContext()
    ?.getApplicationContext()
    ?.on('environment', this.callbacks);
  }

  private getVisibility(): Visibility {
    if (this.toVp(this.getChipNodeHeight()) > 0) {
      return Visibility.Visible
    } else {
      return Visibility.None
    }
  }

  aboutToDisappear() {
    this.smListener.off("change")
    this.mdListener.off("change")
    this.lgListener.off("change")
    if (this.callbackId) {
      this.getUIContext()
        .getHostContext()
      ?.getApplicationContext()
      ?.off('environment', this.callbackId);
      this.callbackId = void (0)
    }
  }

  @Builder
  chipBuilder() {
    Button() {
      Row() {
        if (this.prefixSymbol?.normal || this.prefixSymbol?.activated) {
          SymbolGlyph()
            .fontSize(this.theme.defaultSymbol.fontSize)
            .fontColor(this.getDefaultSymbolColor())
            .attributeModifier(this.getPrefixSymbolModifier())
            .effectStrategy(SymbolEffectStrategy.NONE)
            .symbolEffect(this.symbolEffect, false)
            .symbolEffect(this.symbolEffect, this.theme.defaultSymbol.defaultEffect)
            .onSizeChange((oldValue, newValue) => {
              this.prefixSymbolWidth = newValue?.width
            })
            .key('PrefixSymbolGlyph')
        } else if (this.prefixIcon?.src !== "") {
          Image(this.prefixIcon?.src)
            .direction(this.chipDirection)
            .opacity(this.getChipNodeOpacity())
            .size(this.getPrefixIconSize())
            .fillColor(this.getPrefixIconFilledColor())
            .enabled(this.getChipEnable())
            .objectFit(ImageFit.Cover)
            .focusable(false)
            .flexShrink(0)
            .visibility(this.getVisibility())
            .draggable(false)
        }

        Text(this.label?.text ?? "")
          .direction(this.chipDirection)
          .opacity(this.getChipNodeOpacity())
          .fontSize(this.getLabelFontSize())
          .fontColor(this.getLabelFontColor())
          .fontFamily(this.getLabelFontFamily())
          .fontWeight(this.getLabelFontWeight())
          .margin(this.getActualLabelMargin())
          .enabled(this.getChipEnable())
          .maxLines(1)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .flexShrink(1)
          .focusable(true)
          .textAlign(TextAlign.Center)
          .visibility(this.getVisibility())
          .draggable(false)

        if (this.suffixSymbol?.normal || this.suffixSymbol?.activated) {
          Button({ type: ButtonType.Normal }) {
            SymbolGlyph()
              .fontSize(this.theme.defaultSymbol.fontSize)
              .fontColor(this.getDefaultSymbolColor())
              .attributeModifier(this.getSuffixSymbolModifier())
              .effectStrategy(SymbolEffectStrategy.NONE)
              .symbolEffect(this.symbolEffect, false)
              .symbolEffect(this.symbolEffect, this.theme.defaultSymbol.defaultEffect)
              .onSizeChange((oldValue, newValue) => {
                this.suffixSymbolWidth = newValue?.width
              })
              .key('SuffixSymbolGlyph')
          }
          .onClick(this.getSuffixSymbolAction())
          .accessibilityText(this.getSuffixSymbolAccessibilityText())
          .accessibilityDescription(this.getSuffixSymbolAccessibilityDescription())
          .accessibilityLevel(this.getSuffixSymbolAccessibilityLevel())
          .backgroundColor(Color.Transparent)
          .borderRadius(0)
          .padding(0)
          .stateEffect(false)
        } else if (this.suffixIcon?.src !== "") {
          Button({ type: ButtonType.Normal }) {
            Image(this.getSuffixIconSrc())
              .direction(this.chipDirection)
              .opacity(this.getChipNodeOpacity())
              .size(this.getSuffixIconSize())
              .fillColor(this.getSuffixIconFilledColor())
              .enabled(this.getChipEnable())
              .objectFit(ImageFit.Cover)
              .flexShrink(0)
              .visibility(this.getVisibility())
              .draggable(false)
              .onFocus(() => {
                this.suffixIconOnFocus = true
              })
              .onBlur(() => {
                this.suffixIconOnFocus = false
              })

          }
          .backgroundColor(Color.Transparent)
          .borderRadius(0)
          .padding(0)
          .accessibilityText(this.getSuffixIconAccessibilityText())
          .accessibilityDescription(this.getSuffixIconAccessibilityDescription())
          .accessibilityLevel(this.getSuffixIconAccessibilityLevel())
          .onClick(() => {
            if (!this.getChipEnable()) {
              return
            }
            if (this.suffixIcon?.action) {
              this.suffixIcon.action()
              return
            }
            if ((this.allowClose ?? true) && this.useDefaultSuffixIcon) {
              this.onClose()
              this.deleteChipNodeAnimate()
              return
            }
            this.onClicked()
          })
          .focusable(this.getSuffixIconFocusable())
        } else if (this.allowClose ?? true) {
          Button({ type: ButtonType.Normal }) {
            SymbolGlyph($r('sys.symbol.xmark'))
              .fontSize(this.theme.defaultSymbol.fontSize)
              .fontColor(this.getDefaultSymbolColor())
              .onSizeChange((oldValue, newValue) => {
                this.allowCloseSymbolWidth = newValue?.width
              })
              .key('AllowCloseSymbolGlyph')
          }
          .backgroundColor(Color.Transparent)
          .borderRadius(0)
          .padding(0)
          .accessibilityText(this.getCloseIconAccessibilityText())
          .accessibilityDescription(this.getCloseIconAccessibilityDescription())
          .accessibilityLevel(this.getCloseIconAccessibilityLevel())
          .onClick(() => {
            if (!this.getChipEnable()) {
              return
            }
            this.onClose()
            this.deleteChipNodeAnimate()
          })
        }

      }
      .direction(this.chipDirection)
      .alignItems(VerticalAlign.Center)
      .justifyContent(FlexAlign.Center)
      .padding(this.getChipNodePadding())
      .constraintSize(this.getChipConstraintWidth())
    }
    .constraintSize(this.getChipConstraintWidth())
    .direction(this.chipDirection)
    .type(ButtonType.Normal)
    .clip(false)
    .backgroundColor(this.getChipNodeBackGroundColor())
    .borderRadius(this.getChipNodeRadius())
    .enabled(this.getChipEnable())
    .scale(this.chipScale)
    .focusable(true)
    .opacity(this.getChipNodeOpacity())
    .padding(0)
    .accessibilityGroup(true)
    .accessibilityDescription(this.getAccessibilityDescription())
    .accessibilityLevel(this.getAccessibilityLevel())
    .accessibilityChecked(this.getAccessibilityChecked())
    .accessibilitySelected(this.getAccessibilitySelected())
    .onFocus(() => {
      this.chipNodeOnFocus = true
    })
    .onBlur(() => {
      this.chipNodeOnFocus = false
    })
    .onTouch((event) => {
      this.handleTouch(event)
    })
    .onHover((isHover: boolean) => {
      if (isHover) {
        this.isShowPressedBackGroundColor = true
      } else {
        if (!this.isShowPressedBackGroundColor && isHover) {
          this.isShowPressedBackGroundColor = true
        } else {
          this.isShowPressedBackGroundColor = false
        }
      }
    })
    .onKeyEvent((event) => {
      if (event.type === KeyType.Down && event.keyCode === KeyCode.KEYCODE_FORWARD_DEL && !this.suffixIconOnFocus) {
        this.deleteChipNodeAnimate()
      }
    })
    .onClick(this.onClicked === noop ? undefined : this.onClicked.bind(this))
  }

  getSuffixSymbolAccessibilityLevel(): string {
    if (this.getChipActive()) {
      if (!this.suffixSymbolOptions?.activatedAccessibility?.accessibilityLevel) {
        return this.suffixSymbolOptions?.action ? 'yes' : 'no';
      }
      return this.suffixSymbolOptions.activatedAccessibility.accessibilityLevel;
    }
    if (!this.suffixSymbolOptions?.normalAccessibility?.accessibilityLevel) {
      return this.suffixSymbolOptions?.action ? 'yes' : 'no';
    }
    return this.suffixSymbolOptions.normalAccessibility.accessibilityLevel;
  }

  getSuffixSymbolAccessibilityDescription(): Resource | undefined {
    if (this.getChipActive()) {
      if (typeof this.suffixSymbolOptions?.activatedAccessibility?.accessibilityDescription !== 'undefined') {
        return this.suffixSymbolOptions.activatedAccessibility.accessibilityDescription as Resource;
      }
      return undefined;
    }
    if (typeof this.suffixSymbolOptions?.normalAccessibility?.accessibilityDescription !== 'undefined') {
      return this.suffixSymbolOptions.normalAccessibility.accessibilityDescription as Resource;
    }
    return undefined;
  }

  getSuffixSymbolAccessibilityText(): Resource | undefined {
    if (this.getChipActive()) {
      if (typeof this.suffixSymbolOptions?.activatedAccessibility?.accessibilityText !== 'undefined') {
        return this.suffixSymbolOptions.activatedAccessibility.accessibilityText as Resource;
      }
      return undefined;
    }
    if (typeof this.suffixSymbolOptions?.normalAccessibility?.accessibilityText !== 'undefined') {
      return this.suffixSymbolOptions.normalAccessibility.accessibilityText as Resource;
    }
    return undefined;
  }

  getSuffixSymbolAction(): Callback<ClickEvent> | undefined {
    if (typeof this.suffixSymbolOptions?.action === 'undefined') {
      return undefined;
    }
    return () => {
      if (!this.getChipEnable()) {
        return;
      }
      this.suffixSymbolOptions?.action?.();
    };
  }

  private getAccessibilitySelected(): boolean | undefined {
    if (this.getChipAccessibilitySelectedType() === AccessibilitySelectedType.SELECTED) {
      return this.getChipActive();
    }
    return undefined;
  }

  private getAccessibilityChecked(): boolean | undefined {
    if (this.getChipAccessibilitySelectedType() === AccessibilitySelectedType.CHECKED) {
      return this.getChipActive();
    }
    return undefined;
  }

  private getChipAccessibilitySelectedType(): AccessibilitySelectedType {
    if (typeof this.chipActivated === 'undefined') {
      return AccessibilitySelectedType.CLICKED;
    }
    return this.chipAccessibilitySelectedType ?? AccessibilitySelectedType.CHECKED;
  }

  private getCloseIconAccessibilityLevel(): string {
    if (this.closeOptions?.accessibilityLevel) {
      return this.closeOptions.accessibilityLevel;
    }
    return 'yes';
  }

  private getCloseIconAccessibilityDescription(): Resource | undefined {
    if (typeof this.closeOptions?.accessibilityDescription === 'undefined') {
      return undefined;
    }
    return this.closeOptions.accessibilityDescription as Resource;
  }

  private getCloseIconAccessibilityText(): Resource {
    if (typeof this.closeOptions?.accessibilityText === 'undefined') {
      return $r('sys.string.delete_used_for_accessibility_text')
    }
    return this.closeOptions.accessibilityText as ESObject as Resource;
  }

  private getSuffixIconAccessibilityLevel(): string {
    if (!this.suffixIcon?.accessibilityLevel) {
      return !this.suffixIcon?.action ? 'no' : 'yes';
    }
    return this.suffixIcon.accessibilityLevel;
  }

  private getSuffixIconAccessibilityDescription(): Resource | undefined {
    if (typeof this.suffixIcon?.accessibilityDescription === 'undefined') {
      return undefined;
    }
    return this.suffixIcon.accessibilityDescription as ESObject as Resource;
  }

  private getSuffixIconAccessibilityText(): Resource | undefined {
    if (typeof this.suffixIcon?.accessibilityText === 'undefined') {
      return undefined;
    }

    return this.suffixIcon.accessibilityText as ESObject as Resource;
  }

  private getAccessibilityLevel(): string | undefined {
    return this.chipAccessibilityLevel;
  }

  private getAccessibilityDescription(): Resource | undefined {
    if (typeof this.chipAccessibilityDescription === 'undefined') {
      return undefined;
    }
    return this.chipAccessibilityDescription as ESObject as Resource;
  }

  build() {
    if (!this.deleteChip) {
      this.chipBuilder()
    }
  }
}
