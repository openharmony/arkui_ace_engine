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
  Rectangle
} from '@ohos.arkui.component';
import { ImageModifier, SymbolGlyphModifier, TextModifier } from '@ohos.arkui.modifier';
import { Require, Param, ObservedV2, Trace, Event, Local } from '@ohos.arkui.stateManagement';
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

export enum ChipV2Size {
  NORMAL = 'NORMAL',
  SMALL = 'SMALL'
}

export enum IconType {
  PREFIX_ICON = 'PREFIXICON',
  SUFFIX_ICON = 'SUFFIXICON',
  PREFIX_SYMBOL = 'PREFIXSYMBOL',
  SUFFIX_SYMBOL = 'SUFFIXSYMBOL',
}

export enum BreakPointsType {
  SM = 'SM',
  MD = 'MD',
  LG = 'LG'
}

export enum ChipV2AccessibilitySelectedType {
  CLICKED = 0,
  CHECKED = 1,
  SELECTED = 2,
}

export interface ChipV2ImageIconConfig {
  src: ResourceStr;
  size?: SizeT<LengthMetrics>;
  fillColor?: ColorMetrics;
  activatedFillColor?: ColorMetrics;
  modifier?: ImageModifier;
}

export abstract class ChipV2Icon {
  constructor() {}
}

export class ChipV2ImageIcon extends ChipV2Icon {
  public src: ResourceStr;
  public size?: SizeT<LengthMetrics>;
  public fillColor?: ColorMetrics;
  public activatedFillColor?: ColorMetrics;
  public modifier?: ImageModifier;

  constructor(config: ChipV2ImageIconConfig) {
    super();
    this.src = config.src;
    this.size = config.size;
    this.fillColor = config.fillColor;
    this.activatedFillColor = config.activatedFillColor;
    this.modifier = config.modifier;
  }
}

export interface ChipV2SuffixImageIconConfig extends ChipV2ImageIconConfig, ChipV2AccessibilityConfig {
  accessibilityLevel?: string;
  accessibilityText?: ResourceStr;
  accessibilityDescription?: ResourceStr;
  action?: VoidCallback;
}

@ObservedV2
export class ChipV2SuffixImageIcon extends ChipV2ImageIcon {
  @Trace public accessibilityLevel?: string;
  @Trace public accessibilityText?: ResourceStr;
  @Trace public accessibilityDescription?: ResourceStr;
  @Trace public action?: VoidCallback;

  constructor(config: ChipV2SuffixImageIconConfig) {
    super(config);
    this.accessibilityLevel = config.accessibilityLevel;
    this.accessibilityText = config.accessibilityText;
    this.accessibilityDescription = config.accessibilityDescription;
    this.action = config.action;
  }
}

export interface ChipV2PrefixImageIconConfig extends ChipV2ImageIconConfig {}

@ObservedV2
export class ChipV2PrefixImageIcon extends ChipV2ImageIcon {
  constructor(config: ChipV2PrefixImageIconConfig) {
    super(config);
  }
}

export interface ChipV2AccessibilityConfig {
  accessibilityLevel?: string;
  accessibilityText?: ResourceStr;
  accessibilityDescription?: ResourceStr;
}

export class ChipV2Accessibility {
  public accessibilityLevel?: string;
  public accessibilityText?: ResourceStr;
  public accessibilityDescription?: ResourceStr;

  constructor(config: ChipV2AccessibilityConfig) {
    this.accessibilityLevel = config.accessibilityLevel;
    this.accessibilityText = config.accessibilityText;
    this.accessibilityDescription = config.accessibilityDescription;
  }
}

export interface ChipV2CloseConfig extends ChipV2AccessibilityConfig {
  fontSize?: LengthMetrics;
}

@ObservedV2
export class ChipV2CloseIcon extends ChipV2Accessibility {
  @Trace public fontSize?: LengthMetrics;

  constructor(config: ChipV2CloseConfig) {
    super(config);
    this.fontSize = config.fontSize;
  }
}

export interface ChipV2SymbolIconConfig {
  normal?: SymbolGlyphModifier;
  activated?: SymbolGlyphModifier;
}

export class ChipV2SymbolIcon extends ChipV2Icon {
  public normal?: SymbolGlyphModifier;
  public activated?: SymbolGlyphModifier;

  constructor(config: ChipV2SymbolIconConfig) {
    super();
    this.normal = config.normal;
    this.activated = config.activated;
  }
}

export interface ChipV2PrefixSymbolIconConfig extends ChipV2SymbolIconConfig {}

@ObservedV2
export class ChipV2PrefixSymbolIcon extends ChipV2SymbolIcon {
  constructor(config: ChipV2PrefixSymbolIconConfig) {
    super(config);
  }
}

export interface ChipV2SuffixSymbolIconConfig extends ChipV2SymbolIconConfig {
  normalAccessibility?: ChipV2AccessibilityConfig;
  activatedAccessibility?: ChipV2AccessibilityConfig;
  action?: VoidCallback;
}

@ObservedV2
export class ChipV2SuffixSymbolIcon extends ChipV2SymbolIcon {
  @Trace public normalAccessibility?: ChipV2Accessibility;
  @Trace public activatedAccessibility?: ChipV2Accessibility;
  @Trace public action?: VoidCallback;

  constructor(config: ChipV2SuffixSymbolIconConfig) {
    super(config);
    this.normalAccessibility =
      config.normalAccessibility ? new ChipV2Accessibility(config.normalAccessibility!) : undefined;
    this.activatedAccessibility =
      config.activatedAccessibility ? new ChipV2Accessibility(config.activatedAccessibility!) : undefined;
    this.action = config.action;
  }
}

export interface ChipV2LabelMarginConfig {
  left?: LengthMetrics;
  right?: LengthMetrics;
}

export interface ChipV2LocalizedLabelMarginConfig {
  start?: LengthMetrics;
  end?: LengthMetrics;
}

export interface ChipV2LabelConfig {
  text: string;
  fontSize?: LengthMetrics;
  fontColor?: ColorMetrics;
  activatedFontColor?: ColorMetrics;
  fontFamily?: string;
  labelMargin?: ChipV2LabelMarginConfig;
  localizedLabelMargin?: ChipV2LocalizedLabelMarginConfig;
  modifier?: TextModifier;
}

@ObservedV2
export class ChipV2Label {
  @Trace public text: string;
  @Trace public fontSize?: LengthMetrics;
  @Trace public fontColor?: ColorMetrics;
  @Trace public activatedFontColor?: ColorMetrics;
  @Trace public fontFamily?: string;
  @Trace public labelMargin?: ChipV2LabelMarginConfig;
  @Trace public localizedLabelMargin?: ChipV2LocalizedLabelMarginConfig;
  @Trace public modifier?: TextModifier;

  constructor(config: ChipV2LabelConfig) {
    this.text = config.text;
    this.fontSize = config.fontSize;
    this.fontColor = config.fontColor;
    this.activatedFontColor = config.activatedFontColor;
    this.fontFamily = config.fontFamily;
    this.labelMargin = config.labelMargin;
    this.localizedLabelMargin = config.localizedLabelMargin;
    this.modifier = config.modifier;
  }
}

export interface IconTheme {
  normalSize: SizeOptions;
  smallSize: SizeOptions;
  fillColor: ResourceColor;
  activatedFillColor: ResourceColor;
  focusFillColor: ResourceColor;
  focusActivatedColor: ResourceColor;
}

export interface PrefixIconTheme extends IconTheme {}

export interface SuffixIconTheme extends IconTheme {
  defaultDeleteIcon: ResourceStr;
  focusable: boolean;
  isShowMargin: Resource;
}

export interface DefaultSymbolTheme {
  normalFontColor: Array<ResourceColor>;
  activatedFontColor: Array<ResourceColor>;
  smallSymbolFontSize: Length;
  normalSymbolFontSize: Length;
  defaultEffect: int;
}

export interface LabelTheme {
  normalFontSize: Dimension;
  smallFontSize: Dimension;
  adaptiveItemFontSize: Dimension;
  focusFontColor: ResourceColor;
  focusActiveFontColor: ResourceColor;
  fontColor: ResourceColor;
  activatedFontColor: ResourceColor;
  fontFamily: string;
  normalMargin: Margin;
  localizedNormalMargin: LocalizedMargin;
  smallMargin: Margin;
  localizedSmallMargin: LocalizedMargin;
  defaultFontSize: Dimension;
  fontWeight: Resource;
  activatedFontWeight: Resource;
}

export interface ChipNodeOpacity {
  normal: number;
  hover: number;
  pressed: number;
}

export interface ChipNodeConstraintWidth {
  breakPointMinWidth: number,
  breakPointSmMaxWidth: number,
  breakPointMdMaxWidth: number,
  breakPointLgMaxWidth: number,
}

export interface ChipNodeTheme {
  suitAgeScale: number;
  minLabelWidth: Dimension;
  normalHeight: Dimension;
  smallHeight: Dimension;
  activatedNormalHeight: Dimension;
  activatedSmallHeight: Dimension;
  enabled: boolean;
  activated: boolean;
  backgroundColor: ResourceColor;
  activatedBackgroundColor: ResourceColor;
  backgroundSystemMaterial: uiMaterial.Material;
  activatedBackgroundSystemMaterial: uiMaterial.Material;
  focusOutlineColor: ResourceColor;
  borderColor: ResourceColor,
  defaultBorderWidth: Dimension;
  activatedBorderColor: ResourceColor;
  focusBtnScaleX: Resource;
  focusBtnScaleY: Resource;
  focusBgColor: ResourceColor;
  focusActivatedBgColor: ResourceColor;
  normalShadowStyle: Resource;
  smallShadowStyle: Resource;
  focusOutlineMargin: number;
  normalBorderRadius: Dimension;
  smallBorderRadius: Dimension;
  borderWidth: number;
  activatedBorderWidth: Dimension;
  localizedNormalPadding: LocalizedPadding;
  localizedSmallPadding: LocalizedPadding;
  localizedActivatedNormalPadding: LocalizedPadding;
  localizedActivatedSmallPadding: LocalizedPadding;
  hoverBlendColor: ResourceColor;
  pressedBlendColor: ResourceColor;
  opacity: ChipNodeOpacity;
  breakPointConstraintWidth: ChipNodeConstraintWidth;
}

export interface ChipTheme {
  prefixIcon: PrefixIconTheme;
  label: LabelTheme;
  suffixIcon: SuffixIconTheme;
  defaultSymbol: DefaultSymbolTheme;
  chipNode: ChipNodeTheme;
}

const RESOURCE_TYPE_STRING = 10003;
const RESOURCE_TYPE_FLOAT = 10002;
const RESOURCE_TYPE_INTEGER = 10007;
const HOT_SPOT_MIN_HEIGHT: number = 32;

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

  isNaturalNumber(metrics: LengthMetrics): boolean {
    return metrics.value >= 0;
  }
}

class LengthMetricsCache {
  private static _cache: Map<string, LengthMetrics> = new Map<string, LengthMetrics>();

  public static get(key: string, defaultValue: LengthMetrics): LengthMetrics {
    if (LengthMetricsCache._cache.has(key)) {
      return LengthMetricsCache._cache.get(key)!;
    }
    try {
      const res: Resource = {
        id: -1,
        type: 10002,
        params: [key],
        bundleName: '__harDefaultBundleName__',
        moduleName: '__harDefaultModuleName__',
      };
      const metrics = LengthMetrics.resource(res);
      LengthMetricsCache._cache.set(key, metrics);
      return metrics;
    } catch (error) {
      return defaultValue;
    }
  }
}

export interface IChipV2OptionsConfig {
  label: ChipV2Label;
  prefixIcon?: ChipV2Icon;
  suffixIcon?: ChipV2Icon;
  allowClose?: boolean;
  closeIcon?: ChipV2CloseIcon;
  enabled?: boolean;
  activated?: boolean;
  backgroundColor?: ColorMetrics;
  activatedBackgroundColor?: ColorMetrics;
  borderRadius?: LengthMetrics;
  size?: ChipV2Size | SizeT<LengthMetrics>;
  direction?: Direction;
  accessibilityDescription?: ResourceStr;
  accessibilityLevel?: string;
  accessibilitySelectedType?: ChipV2AccessibilitySelectedType;
  maxFontScale?: number | Resource;
  minFontScale?: number | Resource;
  padding?: LocalizedPadding;
  fontSize?: LengthMetrics;
  backgroundSystemMaterial?: uiMaterial.Material;
  activatedBackgroundSystemMaterial?: uiMaterial.Material;
  onClose?: VoidCallback;
  onClicked?: Callback<void>;
}

@ObservedV2
export class ChipV2Options {
  @Trace public readonly label: ChipV2Label;
  @Trace public readonly prefixIcon?: ChipV2Icon;
  @Trace public readonly suffixIcon?: ChipV2Icon;
  @Trace public readonly allowClose?: boolean;
  @Trace public readonly closeIcon?: ChipV2CloseIcon;
  @Trace public readonly enabled?: boolean;
  @Trace public readonly activated?: boolean;
  @Trace public readonly backgroundColor?: ColorMetrics;
  @Trace public readonly activatedBackgroundColor?: ColorMetrics;
  @Trace public readonly borderRadius?: LengthMetrics;
  @Trace public readonly size?: ChipV2Size | SizeT<LengthMetrics>;
  @Trace public readonly direction?: Direction;
  @Trace public readonly accessibilityDescription?: ResourceStr;
  @Trace public readonly accessibilityLevel?: string;
  @Trace public readonly accessibilitySelectedType?: ChipV2AccessibilitySelectedType;
  @Trace public readonly maxFontScale?: number | Resource;
  @Trace public readonly minFontScale?: number | Resource;
  @Trace public readonly padding?: LocalizedPadding;
  @Trace public readonly fontSize?: LengthMetrics;
  @Trace public readonly backgroundSystemMaterial?: uiMaterial.Material;
  @Trace public readonly activatedBackgroundSystemMaterial?: uiMaterial.Material;
  public onClose?: VoidCallback;
  public onClicked?: Callback<void>;

  constructor(config: IChipV2OptionsConfig) {
    this.label = config.label;
    this.prefixIcon = config.prefixIcon;
    this.suffixIcon = config.suffixIcon;
    this.allowClose = config.allowClose;
    this.closeIcon = config.closeIcon;
    this.enabled = config.enabled ?? true;
    this.activated = config.activated;
    this.backgroundColor = config.backgroundColor;
    this.activatedBackgroundColor = config.activatedBackgroundColor;
    this.borderRadius = config.borderRadius;
    this.size = config.size ?? ChipV2Size.NORMAL;
    this.direction = config.direction ?? Direction.Auto;
    this.accessibilityDescription = config.accessibilityDescription;
    this.accessibilityLevel = config.accessibilityLevel;
    this.accessibilitySelectedType = config.accessibilitySelectedType;
    this.maxFontScale = config.maxFontScale;
    this.minFontScale = config.minFontScale;
    this.padding = config.padding;
    this.fontSize = config.fontSize;
    this.backgroundSystemMaterial = config.backgroundSystemMaterial;
    this.activatedBackgroundSystemMaterial = config.activatedBackgroundSystemMaterial;
    this.onClose = config.onClose;
    this.onClicked = config.onClicked;
  }
}

export class ChipV2EnvironmentCallbackEntry implements EnvironmentCallback {
  private chipv2: ChipV2;

  constructor(chipv2: ChipV2) {
    this.chipv2 = chipv2;
  }

  onConfigurationUpdated(config: Configuration) {
    this.chipv2.fontSizeScale = config.fontSizeScale ?? 1;
    this.chipv2.updateLanguageLineHeight();
  }

  onMemoryLevel(level: AbilityConstant.MemoryLevel) {}
}

@ComponentV2
export struct ChipV2 {
  private theme: ChipTheme = {
    prefixIcon: {
      normalSize: {
        width: $r('sys.float.chip_normal_icon_size'),
        height: $r('sys.float.chip_normal_icon_size')
      },
      smallSize: {
        width: $r('sys.float.chip_small_icon_size'),
        height: $r('sys.float.chip_small_icon_size')
      },
      fillColor: $r('sys.color.chip_usually_icon_color'),
      activatedFillColor: $r('sys.color.chip_active_icon_color'),
      focusFillColor: $r('sys.color.chip_icon_focus_fill'),
      focusActivatedColor: $r('sys.color.chip_icon_activated_focus_color'),
    },
    label: {
      normalFontSize: $r('sys.float.chip_normal_font_size'),
      smallFontSize: $r('sys.float.chip_small_font_size'),
      adaptiveItemFontSize: $r('sys.float.Caption_M'),
      focusFontColor: $r('sys.color.chip_focus_text'),
      focusActiveFontColor: $r('sys.color.chip_activated_focus_font_color'),
      fontColor: $r('sys.color.chip_font_color'),
      activatedFontColor: $r('sys.color.chip_activated_fontcolor'),
      fontFamily: 'HarmonyOS Sans',
      fontWeight: $r('sys.float.chip_text_font_weight'),
      activatedFontWeight: $r('sys.float.chip_activated_text_font_weight'),
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
        start: LengthMetricsCache.get('sys.float.chip_normal_text_margin', LengthMetrics.vp(6)),
        end: LengthMetricsCache.get('sys.float.chip_normal_text_margin', LengthMetrics.vp(6)),
        top: LengthMetrics.vp(0),
        bottom: LengthMetrics.vp(0)
      },
      localizedSmallMargin: {
        start: LengthMetricsCache.get('sys.float.chip_small_text_margin', LengthMetrics.vp(4)),
        end: LengthMetricsCache.get('sys.float.chip_small_text_margin', LengthMetrics.vp(4)),
        top: LengthMetrics.vp(0),
        bottom: LengthMetrics.vp(0),
      }
    },
    suffixIcon: {
      normalSize: {
        width: $r('sys.float.chip_normal_icon_size'),
        height: $r('sys.float.chip_normal_icon_size')
      },
      smallSize: {
        width: $r('sys.float.chip_small_icon_size'),
        height: $r('sys.float.chip_small_icon_size')
      },
      fillColor: $r('sys.color.chip_usually_icon_color'),
      activatedFillColor: $r('sys.color.chip_active_icon_color'),
      focusFillColor: $r('sys.color.chip_icon_focus_fill'),
      focusActivatedColor: $r('sys.color.chip_icon_activated_focus_color'),
      defaultDeleteIcon: $r('sys.media.ohos_ic_public_cancel', 16, 16),
      focusable: false,
      isShowMargin: $r('sys.float.chip_show_close_icon_margin'),
    },
    defaultSymbol: {
      normalFontColor: [$r('sys.color.chip_usually_icon_color')],
      activatedFontColor: [$r('sys.color.chip_active_icon_color')],
      normalSymbolFontSize:
      LengthMetricsCache.get('sys.float.chip_normal_icon_size', LengthMetrics.vp(16)).value as Length,
      smallSymbolFontSize:
      LengthMetricsCache.get('sys.float.chip_small_icon_size', LengthMetrics.vp(16)).value as Length,
      defaultEffect: -1,
    },
    chipNode: {
      suitAgeScale: 1.75,
      minLabelWidth: 12,
      normalHeight: $r('sys.float.chip_normal_height'),
      smallHeight: $r('sys.float.chip_small_height'),
      activatedNormalHeight: $r('sys.float.chip_activated_normal_height'),
      activatedSmallHeight: $r('sys.float.chip_activated_small_height'),
      enabled: true,
      activated: false,
      backgroundColor: $r('sys.color.chip_background_color'),
      activatedBackgroundColor: $r('sys.color.chip_container_activated_color'),
      backgroundSystemMaterial: new uiMaterial.ImmersiveMaterial({
        style: uiMaterial.ImmersiveStyle.ULTRA_THIN
      }),
      activatedBackgroundSystemMaterial: new uiMaterial.ImmersiveMaterial({
        style: uiMaterial.ImmersiveStyle.ULTRA_THIN,
        materialColor: $r('sys.color.comp_background_emphasize')
      }),
      focusOutlineColor: $r('sys.color.ohos_id_color_focused_outline'),
      focusOutlineMargin: 2,
      borderColor: $r('sys.color.chip_border_color'),
      defaultBorderWidth: $r('sys.float.chip_border_width'),
      activatedBorderColor: $r('sys.color.chip_activated_border_color'),
      normalBorderRadius: $r('sys.float.chip_border_radius_normal'),
      smallBorderRadius: $r('sys.float.chip_border_radius_small'),
      activatedBorderWidth: $r('sys.float.chip_activated_border_width'),
      borderWidth: 2,
      focusBtnScaleX: $r('sys.float.chip_focused_btn_scale'),
      focusBtnScaleY: $r('sys.float.chip_focused_btn_scale'),
      localizedNormalPadding: {
        start: LengthMetricsCache.get('sys.float.chip_normal_text_padding', LengthMetrics.vp(16)),
        end: LengthMetricsCache.get('sys.float.chip_normal_text_padding', LengthMetrics.vp(16)),
        top: LengthMetrics.vp(4),
        bottom: LengthMetrics.vp(4)
      },
      localizedSmallPadding: {
        start: LengthMetricsCache.get('sys.float.chip_small_text_padding', LengthMetrics.vp(12)),
        end: LengthMetricsCache.get('sys.float.chip_small_text_padding', LengthMetrics.vp(12)),
        top: LengthMetrics.vp(4),
        bottom: LengthMetrics.vp(4)
      },
      localizedActivatedNormalPadding: {
        start: LengthMetricsCache.get('sys.float.chip_activated_normal_text_padding', LengthMetrics.vp(16)),
        end: LengthMetricsCache.get('sys.float.chip_activated_normal_text_padding', LengthMetrics.vp(16)),
        top: LengthMetrics.vp(4),
        bottom: LengthMetrics.vp(4)
      },
      localizedActivatedSmallPadding: {
        start: LengthMetricsCache.get('sys.float.chip_activated_small_text_padding', LengthMetrics.vp(12)),
        end: LengthMetricsCache.get('sys.float.chip_activated_small_text_padding', LengthMetrics.vp(12)),
        top: LengthMetrics.vp(4),
        bottom: LengthMetrics.vp(4)
      },
      hoverBlendColor: $r('sys.color.chip_hover_color'),
      pressedBlendColor: $r('sys.color.chip_press_color'),
      focusBgColor: $r('sys.color.chip_focus_color'),
      focusActivatedBgColor: $r('sys.color.chip_container_activated_focus_color'),
      opacity: { normal: 1, hover: 0.95, pressed: 0.9 },
      normalShadowStyle: $r('sys.float.chip_normal_shadow_style'),
      smallShadowStyle: $r('sys.float.chip_small_shadow_style'),
      breakPointConstraintWidth: {
        breakPointMinWidth: 128,
        breakPointSmMaxWidth: 156,
        breakPointMdMaxWidth: 280,
        breakPointLgMaxWidth: 400
      },
    }
  };

  @Require @Param chipV2Options: ChipV2Options;

  @Event onClose?: VoidCallback;
  @Event onClicked?: Callback<void>;

  @Local isChipExist: boolean = true;
  @Local chipScale: ScaleOptions = { x: 1, y: 1 };
  @Local chipOpacity: number = 1;
  @Local chipNodeInFocus: boolean = false;
  @Local breakPoint: BreakPointsType = BreakPointsType.SM;
  @Local fontSizeScale: number = 1;
  @Local useAdaptiveLineHeight: boolean = false;

  private smListener: mediaquery.MediaQueryListener =
    this.getUIContext().getMediaQuery().matchMediaSync('(0vp<width) and (width<600vp)');
  private mdListener: mediaquery.MediaQueryListener =
    this.getUIContext().getMediaQuery().matchMediaSync('(600vp<=width) and (width<840vp)');
  private lgListener: mediaquery.MediaQueryListener =
    this.getUIContext().getMediaQuery().matchMediaSync('(840vp<=width)');
  private symbolEffect: SymbolEffect = new SymbolEffect();
  private environmentCallbackID?: int;
  private environmentCallback: ChipV2EnvironmentCallbackEntry = new ChipV2EnvironmentCallbackEntry(this);
  private isSuffixIconFocusStyleCustomized: boolean =
    this.resourceToNumber(this.theme.suffixIcon.isShowMargin, 0) !== 0;
  private isSuffixIconFocusable: boolean = this.resourceToNumber(this.theme.suffixIcon.isShowMargin, 0) !== 1;

  updateLanguageLineHeight(): void {
    if (deviceInfo.sdkApiVersion < 26) {
      return;
    }
    const resourceManager = this.getUIContext().getHostContext()?.resourceManager;
    if (!resourceManager) {
      console.error(`[ChipV2] failed to get resourceManager`);
      return;
    }
    try {
      this.useAdaptiveLineHeight = resourceManager!.getStringByNameSync('text_fallback_line_spacing') === 'true';
    } catch (e) {
      console.error(`[ChipV2] failed to get text_fallback_line_spacing resource`);
    }
  }

  aboutToAppear(): void {
    this.smListener?.onChange((result) => {
      if (result.matches) {
        this.breakPoint = BreakPointsType.SM;
      }
    });
    this.mdListener?.onChange((result) => {
      if (result.matches) {
        this.breakPoint = BreakPointsType.MD;
      }
    });
    this.lgListener?.onChange((result) => {
      if (result.matches) {
        this.breakPoint = BreakPointsType.LG;
      }
    });
    this.updateLanguageLineHeight();
    let abilityContext = this.getUIContext().getHostContext();
    if (abilityContext) {
      this.environmentCallbackID = abilityContext.getApplicationContext().onEnvironment(this.environmentCallback);
    }
    this.onClose = this.chipV2Options.onClose;
    this.onClicked = this.chipV2Options.onClicked;
  }

  aboutToDisappear(): void {
    this.smListener?.offChange();
    this.mdListener?.offChange();
    this.lgListener?.offChange();
    if (this.environmentCallbackID !== undefined) {
      this.getUIContext()?.getHostContext()?.getApplicationContext().offEnvironment(this.environmentCallbackID as int);
      this.environmentCallbackID = undefined;
    }
  }

  private isSetActiveChipBgColor(): boolean {
    if (!this.chipV2Options.activatedBackgroundColor) {
      return false;
    }
    try {
      return (this.chipV2Options.activatedBackgroundColor as ColorMetrics).color !==
        ColorMetrics.resourceColor(this.theme.chipNode.activatedBackgroundColor).color;
    } catch (error) {
      console.error(`[ChipV2] failed to get ColorMetrics.resourceColor`);
      return false;
    }
  }

  private isSetNormalChipBgColor(): boolean {
    if (!this.chipV2Options.backgroundColor) {
      return false;
    }
    try {
      return (this.chipV2Options.backgroundColor as ColorMetrics).color !==
        ColorMetrics.resourceColor(this.theme.chipNode.backgroundColor).color;
    } catch (error) {
      console.error(`[ChipV2] failed to get resourceColor`);
      return false;
    }
  }

  private getShadowStyles(): ShadowStyle | undefined {
    if (!this.chipNodeInFocus) {
      return undefined;
    }
    switch (Double.toInt(this.resourceToNumber(this.isSmallChipSize() ?
      this.theme.chipNode.smallShadowStyle : this.theme.chipNode.normalShadowStyle, -1))) {
      case -1:
        return undefined;
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
        return undefined;
    }
  }

  @Builder
  ChipBuilder() {
    Button({ type: ButtonType.Normal }) {
      Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
        if (this.hasPrefixSymbolIcon()) {
          SymbolGlyph()
            .fontSize(this.getFontSizeForSymbol())
            .maxFontScale(this.chipV2Options.maxFontScale)
            .minFontScale(this.chipV2Options.minFontScale)
            .fontColor(this.getDefaultSymbolColor(IconType.PREFIX_SYMBOL))
            .flexShrink(0)
            .attributeModifier(this.getPrefixSymbolModifier())
            .effectStrategy(SymbolEffectStrategy.NONE)
            .symbolEffect(this.symbolEffect, false)
            .symbolEffect(this.symbolEffect, this.theme.defaultSymbol.defaultEffect)
        } else if (this.hasPrefixImageIcon()) {
          Image(this.getPrefixImageIcon()!.src)
            .direction(this.chipV2Options.direction)
            .size(this.getPrefixIconSize())
            .fillColor(this.getPrefixIconFilledColor())
            .objectFit(ImageFit.Cover)
            .focusable(false)
            .flexShrink(0)
            .draggable(false)
            .attributeModifier(this.getPrefixImageIcon()!.modifier)
        }

        Text(this.chipV2Options.label.text)
          .draggable(false)
          .flexShrink(1)
          .focusable(true)
          .maxLines(1)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .textAlign(TextAlign.Center)
          .direction(this.chipV2Options.direction)
          .fontSize(this.getLabelFontSize())
          .fontColor(this.getLabelFontColor())
          .fontFamily(this.getLabelFontFamily())
          .fontWeight(this.getLabelFontWeight())
          .maxFontScale(this.chipV2Options.maxFontScale)
          .minFontScale(this.chipV2Options.minFontScale)
          .margin(this.getLabelMargin())
          .includeFontPadding(this.useAdaptiveLineHeight)
          .fallbackLineSpacing(this.useAdaptiveLineHeight)
          .attributeModifier(this.chipV2Options.label.modifier)

        if (this.hasSuffixSymbolIcon()) {
          Button({ type: ButtonType.Normal }) {
            SymbolGlyph()
              .fontSize(this.getFontSizeForSymbol())
              .maxFontScale(this.chipV2Options.maxFontScale)
              .minFontScale(this.chipV2Options.minFontScale)
              .fontColor(this.getDefaultSymbolColor(IconType.SUFFIX_SYMBOL))
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
          .focusable(this.isSuffixIconFocusable)
        } else if (this.hasSuffixImageIcon()) {
          Button({ type: ButtonType.Normal }) {
            Image(this.getSuffixImageIcon()!.src)
              .direction(this.chipV2Options.direction)
              .size(this.getSuffixIconSize())
              .fillColor(this.getSuffixIconFilledColor())
              .objectFit(ImageFit.Cover)
              .draggable(false)
              .attributeModifier(this.getSuffixImageIcon()!.modifier)
          }
          .backgroundColor(Color.Transparent)
          .borderRadius(0)
          .padding(0)
          .flexShrink(0)
          .stateEffect(false)
          .hoverEffect(HoverEffect.None)
          .size(this.getSuffixIconSize())
          .accessibilityText(this.getSuffixImageIconAccessibilityText())
          .accessibilityDescription(this.getSuffixImageIconAccessibilityDescription())
          .accessibilityLevel(this.getSuffixImageIconAccessibilityLevel())
          .onClick(this.getSuffixIconAction())
          .focusable(this.isSuffixIconFocusable)
        } else if (this.isClosable()) {
          Button({ type: ButtonType.Normal }) {
            SymbolGlyph($r('sys.symbol.xmark'))
              .fontSize(this.getCloseOptionsFontsize())
              .maxFontScale(this.chipV2Options.maxFontScale)
              .minFontScale(this.chipV2Options.minFontScale)
              .fontColor(this.getDefaultSymbolColor(IconType.SUFFIX_SYMBOL))
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
          .responseRegion({
            x: $r('sys.float.chip_touch_hot_zone_x'),
            y: $r('sys.float.chip_touch_hot_zone_y'),
            width: '100%',
            height: '100%'
          })
          .onClick(() => {
            if (!this.isChipEnabled()) {
              return;
            }
            this.onClose?.();
            this.deleteChip();
          })
          .focusable(this.isSuffixIconFocusable)
        }
      }
      .direction(this.chipV2Options.direction)
      .padding(this.getChipPadding())
      .size(this.getChipSize())
      .constraintSize(this.getChipConstraintSize())
    }
    .clip(false)
    .shadow(this.getShadowStyles())
    .padding(0)
    .focusable(true)
    .size(this.getChipSize())
    .enabled(this.isChipEnabled())
    .direction(this.chipV2Options.direction)
    .systemMaterial(this.getBackgroundSystemMaterial())
    .backgroundColor(this.getChipBackgroundColor())
    .borderWidth(this.getChipNodeBorderWidth())
    .borderColor(this.getChipNodeBorderColor())
    .borderRadius(this.getChipBorderRadius())
    .responseRegion(this.getChipResponseRegion())
    .scale(this.chipScale)
    .opacity(this.chipOpacity)
    .accessibilityGroup(true)
    .accessibilityDescription(this.getAccessibilityDescription())
    .accessibilityLevel(this.chipV2Options.accessibilityLevel)
    .accessibilityChecked(this.getAccessibilityChecked())
    .accessibilitySelected(this.getAccessibilitySelected())
    .onClick(this.getChipOnClicked())
    .onKeyEvent((event: KeyEvent) => {
      if (!event || event.type === null || event.type !== KeyType.Down) {
        return false;
      }
      let isDeleteChip = event.keyCode === KeyCode.KEYCODE_FORWARD_DEL;
      let isEnterDeleteChip = event.keyCode === KeyCode.KEYCODE_ENTER && this.chipV2Options.allowClose !== false &&
        !this.hasSuffixImageIcon() && this.isSuffixIconFocusStyleCustomized;
      if (isDeleteChip || isEnterDeleteChip) {
        this.deleteChip();
      }
    })
    .onFocus(() => {
      if (this.isSuffixIconFocusStyleCustomized) {
        this.chipNodeInFocus = true;
      }
      this.chipZoomIn();
    })
    .onBlur(() => {
      if (this.isSuffixIconFocusStyleCustomized) {
        this.chipNodeInFocus = false;
      }
      this.chipZoomOut();
    })
    .onHover(!this.isSuffixIconFocusStyleCustomized ? undefined : (isHover: boolean) => {
      isHover ? this.chipZoomIn() : this.chipZoomOut();
    })
  }

  // Icon type checking methods
  private hasPrefixImageIcon(): boolean {
    return this.chipV2Options.prefixIcon instanceof ChipV2PrefixImageIcon;
  }

  private hasPrefixSymbolIcon(): boolean {
    return this.chipV2Options.prefixIcon instanceof ChipV2PrefixSymbolIcon &&
      !!((this.chipV2Options.prefixIcon as ChipV2PrefixSymbolIcon).normal ||
        (this.chipV2Options.prefixIcon as ChipV2PrefixSymbolIcon).activated);
  }

  private hasSuffixImageIcon(): boolean {
    return this.chipV2Options.suffixIcon instanceof ChipV2SuffixImageIcon;
  }

  private hasSuffixSymbolIcon(): boolean {
    return this.chipV2Options.suffixIcon instanceof ChipV2SuffixSymbolIcon &&
      !!((this.chipV2Options.suffixIcon as ChipV2SuffixSymbolIcon).normal ||
        (this.chipV2Options.suffixIcon as ChipV2SuffixSymbolIcon).activated);
  }

  private getPrefixImageIcon(): ChipV2PrefixImageIcon | undefined {
    return this.hasPrefixImageIcon() ? this.chipV2Options.prefixIcon as ChipV2PrefixImageIcon : undefined;
  }

  private getSuffixImageIcon(): ChipV2SuffixImageIcon | undefined {
    return this.hasSuffixImageIcon() ? this.chipV2Options.suffixIcon as ChipV2SuffixImageIcon : undefined;
  }

  private getSuffixSymbolIcon(): ChipV2SuffixSymbolIcon | undefined {
    return this.hasSuffixSymbolIcon() ? this.chipV2Options.suffixIcon as ChipV2SuffixSymbolIcon : undefined;
  }

  private getCloseIconAccessibilityLevel(): string {
    const level = this.chipV2Options.closeIcon?.accessibilityLevel;
    if (level === 'no' || level === 'no-hide-descendants') {
      return level!;
    }
    return 'yes';
  }

  private getCloseIconAccessibilityDescription(): ResourceStr | undefined {
    if (typeof this.chipV2Options.closeIcon?.accessibilityDescription === 'undefined') {
      return undefined;
    }
    return this.chipV2Options.closeIcon?.accessibilityDescription as ResourceStr;
  }

  private getCloseIconAccessibilityText(): ResourceStr {
    if (typeof this.chipV2Options.closeIcon?.accessibilityText === 'undefined') {
      return $r('sys.string.delete_used_for_accessibility_text');
    }
    return this.chipV2Options.closeIcon?.accessibilityText as ResourceStr;
  }

  getSuffixIconAction(): Callback<ClickEvent> | undefined {
    if (this.hasSuffixImageIcon()) {
      const suffixImgIcon = this.getSuffixImageIcon()!;
      if (!suffixImgIcon.action) {
        return undefined;
      }
      return () => {
        if (this.isChipEnabled()) {
          suffixImgIcon.action?.();
        }
      };
    }
    return undefined;
  }

  getSuffixIconFilledColor(): ResourceColor | ColorMetrics {
    if (this.isChipActivated()) {
      return this.getSuffixImageIcon()?.activatedFillColor ?? this.getDefaultActiveIconColor(IconType.PREFIX_ICON);
    }
    return this.getSuffixImageIcon()?.fillColor ?? this.getDefaultFillIconColor(IconType.SUFFIX_ICON);
  }

  getSuffixIconSize(): SizeOptions {
    let suffixIconSize: SizeOptions = { width: 0, height: 0 };
    let width: LengthMetrics | undefined = this.getSuffixImageIcon()?.size?.width;
    if (typeof width !== 'undefined' && this.isValidLength(width)) {
      suffixIconSize.width = lengthMetricsToLength(width!);
    } else {
      suffixIconSize.width =
        this.isSmallChipSize() ? this.theme.suffixIcon.smallSize.width : this.theme.suffixIcon.normalSize.width;
    }
    let height: LengthMetrics | undefined = this.getSuffixImageIcon()?.size?.height;
    if (typeof height !== 'undefined' && this.isValidLength(height)) {
      suffixIconSize.height = lengthMetricsToLength(height!);
    } else {
      suffixIconSize.height =
        this.isSmallChipSize() ? this.theme.suffixIcon.smallSize.height : this.theme.suffixIcon.normalSize.height;
    }
    return suffixIconSize;
  }

  getSuffixImageIconAccessibilityLevel(): string {
    const suffixIcon = this.getSuffixImageIcon();
    if (suffixIcon?.accessibilityLevel === 'no' || suffixIcon?.accessibilityLevel === 'no-hide-descendants') {
      return suffixIcon!.accessibilityLevel!;
    }
    return suffixIcon?.action ? 'yes' : 'no';
  }

  getSuffixImageIconAccessibilityDescription(): ResourceStr | undefined {
    const suffixIcon = this.getSuffixImageIcon();
    if (typeof suffixIcon?.accessibilityDescription === 'undefined') {
      return undefined;
    }
    return suffixIcon!.accessibilityDescription as ResourceStr;
  }

  getSuffixImageIconAccessibilityText(): ResourceStr | undefined {
    const suffixIcon = this.getSuffixImageIcon();
    if (typeof suffixIcon?.accessibilityText === 'undefined') {
      return undefined;
    }

    return suffixIcon!.accessibilityText as ResourceStr;
  }

  isClosable(): boolean {
    return this.chipV2Options.allowClose ?? true;
  }

  getSuffixSymbolModifier(): SymbolGlyphModifier | undefined {
    if (this.isChipActivated()) {
      return this.getSuffixSymbolIcon()?.activated;
    }
    return this.getSuffixSymbolIcon()?.normal;
  }

  getSuffixSymbolAccessibilityLevel(): string {
    if (this.isChipActivated()) {
      if (this.getSuffixSymbolIcon()?.activatedAccessibility?.accessibilityLevel === 'no' ||
        this.getSuffixSymbolIcon()?.activatedAccessibility?.accessibilityLevel === 'no-hide-descendants') {
        return this.getSuffixSymbolIcon()!.activatedAccessibility!.accessibilityLevel!;
      }
      return this.getSuffixSymbolIcon()?.action ? 'yes' : 'no';
    }
    if (this.getSuffixSymbolIcon()?.normalAccessibility?.accessibilityLevel === 'no' ||
      this.getSuffixSymbolIcon()?.normalAccessibility?.accessibilityLevel === 'no-hide-descendants') {
      return this.getSuffixSymbolIcon()!.normalAccessibility!.accessibilityLevel!;
    }
    return this.getSuffixSymbolIcon()?.action ? 'yes' : 'no';
  }

  getSuffixSymbolAccessibilityDescription(): ResourceStr | undefined {
    if (this.isChipActivated()) {
      if (typeof this.getSuffixSymbolIcon()?.activatedAccessibility?.accessibilityDescription !== 'undefined') {
        return this.getSuffixSymbolIcon()!.activatedAccessibility!.accessibilityDescription as ResourceStr;
      }
      return undefined;
    }
    if (typeof this.getSuffixSymbolIcon()?.normalAccessibility?.accessibilityDescription !== 'undefined') {
      return this.getSuffixSymbolIcon()!.normalAccessibility!.accessibilityDescription as ResourceStr;
    }
    return undefined;
  }

  getSuffixSymbolAccessibilityText(): ResourceStr | undefined {
    if (this.isChipActivated()) {
      if (typeof this.getSuffixSymbolIcon()?.activatedAccessibility?.accessibilityText !== 'undefined') {
        return this.getSuffixSymbolIcon()!.activatedAccessibility!.accessibilityText as ResourceStr;
      }
      return undefined;
    }
    if (typeof this.getSuffixSymbolIcon()?.normalAccessibility?.accessibilityText !== 'undefined') {
      return this.getSuffixSymbolIcon()!.normalAccessibility!.accessibilityText as ResourceStr;
    }
    return undefined;
  }

  getSuffixSymbolAction(): Callback<ClickEvent> | undefined {
    if (typeof this.getSuffixSymbolIcon()?.action === 'undefined') {
      return undefined;
    }
    return () => {
      if (!this.isChipEnabled()) {
        return;
      }
      this.getSuffixSymbolIcon()?.action?.();
    };
  }

  getPrefixIconFilledColor(): ResourceColor | ColorMetrics {
    if (this.isChipActivated()) {
      return this.getPrefixImageIcon()?.activatedFillColor ?? this.getDefaultActiveIconColor(IconType.PREFIX_ICON);
    }
    return this.getPrefixImageIcon()?.fillColor ?? this.getDefaultFillIconColor(IconType.PREFIX_ICON);
  }

  getPrefixIconSize(): SizeOptions {
    let prefixIconSize: SizeOptions = { width: 0, height: 0 };
    let width: LengthMetrics | undefined = this.getPrefixImageIcon()?.size?.width;
    if (typeof width !== 'undefined' && this.isValidLength(width)) {
      prefixIconSize.width = lengthMetricsToLength(width!);
    } else {
      prefixIconSize.width =
        this.isSmallChipSize() ? this.theme.prefixIcon.smallSize.width : this.theme.prefixIcon.normalSize.width;
    }
    let height: LengthMetrics | undefined = this.getPrefixImageIcon()?.size?.height;
    if (typeof height !== 'undefined' && this.isValidLength(height)) {
      prefixIconSize.height = lengthMetricsToLength(height!);
    } else {
      prefixIconSize.height =
        this.isSmallChipSize() ? this.theme.prefixIcon.smallSize.height : this.theme.prefixIcon.normalSize.height;
    }
    return prefixIconSize;
  }

  getPrefixSymbolModifier(): SymbolGlyphModifier | undefined {
    if (!(this.chipV2Options.prefixIcon instanceof ChipV2PrefixSymbolIcon)) {
      return undefined;
    }
    const prefixSymbol = this.chipV2Options.prefixIcon as ChipV2PrefixSymbolIcon;
    if (this.isChipActivated()) {
      return prefixSymbol.activated;
    }
    return prefixSymbol.normal;
  }

  getDefaultSymbolColor(iconType: IconType): ResourceColor[] {
    return this.isChipActivated() ? this.getSymbolActiveColor(iconType) :
      this.getSymbolFillColor(iconType);
  }

  private getDefaultActiveIconColor(iconType: IconType): ResourceColor {
    if (iconType === IconType.PREFIX_ICON) {
      return this.chipNodeInFocus ? this.theme.prefixIcon.focusActivatedColor :
        this.theme.prefixIcon.activatedFillColor;
    } else {
      return this.chipNodeInFocus ? this.theme.suffixIcon.focusActivatedColor :
        this.theme.suffixIcon.activatedFillColor;
    }
  }

  private getDefaultFillIconColor(iconType: IconType): ResourceColor {
    if (iconType === IconType.PREFIX_ICON) {
      return this.chipNodeInFocus ? this.theme.prefixIcon.focusFillColor : this.theme.prefixIcon.fillColor;
    } else {
      return this.chipNodeInFocus ? this.theme.suffixIcon.focusFillColor : this.theme.suffixIcon.fillColor;
    }
  }

  private getSymbolActiveColor(iconType: IconType): ResourceColor[] {
    if (!this.chipNodeInFocus) {
      return this.theme.defaultSymbol.activatedFontColor;
    }
    if (iconType === IconType.PREFIX_SYMBOL) {
      return [this.theme.prefixIcon.focusActivatedColor];
    }
    if (iconType === IconType.SUFFIX_SYMBOL) {
      return [this.theme.suffixIcon.focusActivatedColor];
    }
    return this.theme.defaultSymbol.activatedFontColor;
  }

  private getSymbolFillColor(iconType?: IconType): ResourceColor[] {
    if (!this.chipNodeInFocus) {
      return this.theme.defaultSymbol.normalFontColor;
    }
    if (iconType === IconType.PREFIX_SYMBOL) {
      return [this.theme.prefixIcon.focusFillColor];
    }
    if (iconType === IconType.SUFFIX_SYMBOL) {
      return [this.theme.suffixIcon.focusFillColor];
    }
    return this.theme.defaultSymbol.normalFontColor;
  }

  getChipConstraintSize(): ConstraintSizeOptions | undefined {
    const constraintSize: ConstraintSizeOptions = {};
    if (typeof this.chipV2Options.size === 'string') {
      constraintSize.maxWidth = this.getChipMaxWidth();
      if (this.chipV2Options.size === ChipV2Size.SMALL) {
        constraintSize.minHeight =
          this.isChipActivated() ? this.theme.chipNode.activatedSmallHeight : this.theme.chipNode.smallHeight;
      } else {
        constraintSize.minHeight =
          this.isChipActivated() ? this.theme.chipNode.activatedNormalHeight : this.theme.chipNode.normalHeight;
      }
    } else {
      if (typeof (this.chipV2Options.size as SizeT<LengthMetrics>)?.width === 'undefined' ||
        !this.isValidLength((this.chipV2Options.size as SizeT<LengthMetrics>)!.width)) {
        constraintSize.maxWidth = this.getChipMaxWidth();
      }
      if (typeof (this.chipV2Options.size as SizeT<LengthMetrics>)?.height === 'undefined' ||
        !this.isValidLength((this.chipV2Options.size as SizeT<LengthMetrics>)!.height)) {
        constraintSize.minHeight =
          this.isChipActivated() ? this.theme.chipNode.activatedNormalHeight : this.theme.chipNode.normalHeight;
      }
    }
    return constraintSize;
  }

  private getChipHeight(): number {
    let height: Length;
    if (typeof this.chipV2Options.size !== 'string') {
      if (typeof (this.chipV2Options.size as SizeT<LengthMetrics>)?.height !== 'undefined' &&
        this.isValidLength((this.chipV2Options.size as SizeT<LengthMetrics>)!.height)) {
        height = lengthMetricsToLength((this.chipV2Options.size as SizeT<LengthMetrics>)!.height);
      } else {
        height = this.isChipActivated() ? this.theme.chipNode.activatedNormalHeight : this.theme.chipNode.normalHeight;
      }
    } else if (this.chipV2Options.size === ChipV2Size.SMALL) {
      height = this.isChipActivated() ? this.theme.chipNode.activatedSmallHeight : this.theme.chipNode.smallHeight;
    } else {
      height = this.isChipActivated() ? this.theme.chipNode.activatedNormalHeight : this.theme.chipNode.normalHeight;
    }
    return this.parseLength(height) ?? HOT_SPOT_MIN_HEIGHT;
  }

  private getChipResponseRegion(): Rectangle | undefined {
    const chipHeight = this.getChipHeight();
    if (chipHeight < HOT_SPOT_MIN_HEIGHT) {
      return {
        x: 0,
        y: (chipHeight - HOT_SPOT_MIN_HEIGHT) / 2,
        width: '100%',
        height: HOT_SPOT_MIN_HEIGHT
      };
    }
    return undefined;
  }

  getChipMaxWidth(): Length | undefined {
    if (this.fontSizeScale >= this.theme.chipNode.suitAgeScale) {
      return undefined;
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
    return undefined;
  }

  getChipSize(): SizeOptions | undefined {
    const chipSize: SizeOptions = {
      width: 'auto',
      height: 'auto'
    };

    if (typeof this.chipV2Options.size !== 'string') {
      if (typeof (this.chipV2Options.size as SizeT<LengthMetrics>)?.width !== 'undefined' &&
        this.isValidLength((this.chipV2Options.size as SizeT<LengthMetrics>)!.width)) {
        chipSize.width = lengthMetricsToLength((this.chipV2Options.size as SizeT<LengthMetrics>)!.width);
      }
      if (typeof (this.chipV2Options.size as SizeT<LengthMetrics>)?.height !== 'undefined' &&
        this.isValidLength((this.chipV2Options.size as SizeT<LengthMetrics>)!.height)) {
        chipSize.height = lengthMetricsToLength((this.chipV2Options.size as SizeT<LengthMetrics>)!.height);
      }
    }
    return chipSize;
  }

  copyPadding(src: LocalizedPadding): LocalizedPadding {
    return {
      top: src.top,
      bottom: src.bottom,
      start: src.start,
      end: src.end
    }
  }

  getChipPadding(): Length | Padding | LocalizedPadding {
    let chipTheme = this.theme.chipNode;
    let res: LocalizedPadding;
    if (this.isSmallChipSize()) {
      res = this.isChipActivated() ? this.copyPadding(chipTheme.localizedActivatedSmallPadding) :
        this.copyPadding(chipTheme.localizedSmallPadding);
    } else {
      res = this.isChipActivated() ? this.copyPadding(chipTheme.localizedActivatedNormalPadding) :
        this.copyPadding(chipTheme.localizedNormalPadding);
    }
    if (this.chipV2Options.padding?.top &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.chipV2Options.padding!.top!)) {
      res.top = this.chipV2Options.padding!.top!;
    }
    if (this.chipV2Options.padding?.bottom &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.chipV2Options.padding!.bottom!)) {
      res.bottom = this.chipV2Options.padding!.bottom!;
    }
    if (this.chipV2Options.padding?.start &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.chipV2Options.padding!.start!)) {
      res.start = this.chipV2Options.padding!.start!;
    }
    if (this.chipV2Options.padding?.end &&
      LengthMetricsUtils.getInstance().isNaturalNumber(this.chipV2Options.padding!.end!)) {
      res.end = this.chipV2Options.padding!.end!;
    }
    return res;
  }

  getLabelMargin(): Length | Padding | LocalizedPadding {
    const localizedLabelMargin: LocalizedMargin = {
      start: LengthMetrics.vp(0),
      end: LengthMetrics.vp(0),
    };
    const defaultLocalizedMargin =
      this.isSmallChipSize() ? this.theme.label.localizedSmallMargin : this.theme.label.localizedNormalMargin;

    if (typeof this.chipV2Options.label?.localizedLabelMargin?.start !== 'undefined' &&
      this.chipV2Options.label!.localizedLabelMargin!.start!.value >= 0) {
      localizedLabelMargin.start = this.chipV2Options.label!.localizedLabelMargin!.start;
    } else if (this.hasPrefix()) {
      localizedLabelMargin.start = defaultLocalizedMargin.start;
    }

    if (typeof this.chipV2Options.label?.localizedLabelMargin?.end !== 'undefined' &&
      this.chipV2Options.label!.localizedLabelMargin!.end!.value >= 0) {
      localizedLabelMargin.end = this.chipV2Options.label!.localizedLabelMargin!.end;
    } else if (this.hasSuffix() || this.isNeedShowCloseIconMargin()) {
      localizedLabelMargin.end = defaultLocalizedMargin.end;
    }
    if (typeof this.chipV2Options.label?.localizedLabelMargin === 'object') {
      return localizedLabelMargin;
    }
    if (typeof this.chipV2Options.label?.labelMargin === 'object') {
      const labelMargin: Margin = { left: 0, right: 0 };
      const defaultLabelMargin: Margin =
        this.isSmallChipSize() ? this.theme.label.smallMargin : this.theme.label.normalMargin;
      if (typeof this.chipV2Options.label?.labelMargin?.left !== 'undefined' &&
        this.isValidLength(this.chipV2Options.label!.labelMargin!.left as LengthMetrics)) {
        labelMargin.left = lengthMetricsToLength(this.chipV2Options.label!.labelMargin!.left!);
      } else if (this.hasPrefix()) {
        labelMargin.left = defaultLabelMargin.left;
      }
      if (typeof this.chipV2Options.label?.labelMargin?.right !== 'undefined' &&
        this.isValidLength(this.chipV2Options.label!.labelMargin!.right as LengthMetrics)) {
        labelMargin.right = lengthMetricsToLength(this.chipV2Options.label!.labelMargin!.right!);
      } else if (this.hasSuffix()) {
        labelMargin.right = defaultLabelMargin.right;
      }
      return labelMargin;
    }
    return localizedLabelMargin;
  }

  hasSuffix(): boolean {
    if (this.hasSuffixImageIcon()) {
      return true;
    }
    if (this.isChipActivated()) {
      return (this.chipV2Options.suffixIcon instanceof ChipV2SuffixSymbolIcon) &&
        (!!((this.chipV2Options.suffixIcon as ChipV2SuffixSymbolIcon)?.activated));
    } else {
      return (this.chipV2Options.suffixIcon instanceof ChipV2SuffixSymbolIcon) &&
        (!!((this.chipV2Options.suffixIcon as ChipV2SuffixSymbolIcon)?.normal));
    }
  }

  private hasPrefix(): boolean {
    if (this.hasPrefixImageIcon()) {
      return true;
    }
    if (!(this.chipV2Options.prefixIcon instanceof ChipV2PrefixSymbolIcon)) {
      return false;
    }
    return this.isChipActivated() ? !!(this.chipV2Options.prefixIcon as ChipV2PrefixSymbolIcon)?.activated :
      !!(this.chipV2Options.prefixIcon as ChipV2PrefixSymbolIcon)?.normal;
    }

  private getLabelFontWeight(): string | int | FontWeight {
    const fontWeight = this.isChipActivated() ?
      this.resourceToNumber(this.theme.label.activatedFontWeight, FontWeight.Medium) :
      this.resourceToNumber(this.theme.label.fontWeight, FontWeight.Regular);
    switch (Double.toInt(fontWeight)) {
      case 0:
        return FontWeight.Lighter
      case 1:
        return FontWeight.Normal
      case 2:
        return FontWeight.Regular
      case 3:
        return FontWeight.Medium
      case 4:
        return FontWeight.Bold
      case 5:
        return FontWeight.Bolder
      default:
        return FontWeight.Regular
    }
  }

  getLabelFontFamily(): ResourceStr {
    return this.chipV2Options.label.fontFamily ?? this.theme.label.fontFamily;
  }

  private getFontSizeForSymbol(): Length | Dimension {
    if (!!this.chipV2Options.fontSize && this.isValidLength(this.chipV2Options.fontSize)) {
      return lengthMetricsToLength(this.chipV2Options.fontSize!);
    }
    return this.isSmallChipSize() ? this.theme.defaultSymbol.smallSymbolFontSize :
      this.theme.defaultSymbol.normalSymbolFontSize;
  }

  private getCloseOptionsFontsize(): Length | Dimension {
    if (!!this.chipV2Options.closeIcon?.fontSize && this.isValidLength(this.chipV2Options.closeIcon?.fontSize)) {
      return lengthMetricsToLength(this.chipV2Options.closeIcon!.fontSize!);
    }
    if (!!this.chipV2Options.fontSize && this.isValidLength(this.chipV2Options.fontSize)) {
      return lengthMetricsToLength(this.chipV2Options.fontSize!);
    }
    return this.isSmallChipSize() ? this.theme.defaultSymbol.smallSymbolFontSize :
      this.theme.defaultSymbol.normalSymbolFontSize;
  }

  private getActiveFontColor(): ResourceColor {
    return this.chipNodeInFocus ? this.theme.label.focusActiveFontColor : this.theme.label.activatedFontColor;
  }

  private getFontColor(): ResourceColor {
    return this.chipNodeInFocus ? this.theme.label.focusFontColor : this.theme.label.fontColor;
  }

  private getChipNodeBorderColor(): ResourceColor | undefined {
    if (this.getBackgroundSystemMaterial()) {
      return undefined;
    }
    let themeChipNode = this.theme.chipNode;
    return this.isChipActivated() ? themeChipNode.activatedBorderColor : themeChipNode.borderColor;
  }

  private getChipNodeBorderWidth(): Dimension | undefined {
    if (this.getBackgroundSystemMaterial()) {
      return undefined;
    }
    let themeChipNode = this.theme.chipNode;
    return this.isChipActivated() ? themeChipNode.activatedBorderWidth : themeChipNode.defaultBorderWidth;
  }

  getLabelFontColor(): ResourceColor {
    if (this.isChipActivated()) {
      return colorMetricsToResourceColor(this.chipV2Options.label.activatedFontColor) ?? this.getActiveFontColor();
    }
    return colorMetricsToResourceColor(this.chipV2Options.label.fontColor) ?? this.getFontColor();
  }

  getLabelFontSize(): Dimension {
    if (typeof this.chipV2Options.label.fontSize !== 'undefined' &&
      this.isValidLength(this.chipV2Options.label.fontSize)) {
      return lengthMetricsToDimension(this.chipV2Options.label.fontSize!);
    }
    if (!!this.chipV2Options.fontSize && this.isValidLength(this.chipV2Options.fontSize)) {
      return lengthMetricsToDimension(this.chipV2Options.fontSize!);
    }
    if (this.isSmallChipSize()) {
      return this.useAdaptiveLineHeight ? this.theme.label.adaptiveItemFontSize : this.theme.label.smallFontSize;
    }
    return this.useAdaptiveLineHeight ? this.theme.label.adaptiveItemFontSize : this.theme.label.normalFontSize;
  }

  deleteChip() {
    this.getUIContext().animateTo({ curve: Curve.Sharp, duration: 150 }, () => {
      this.chipOpacity = 0;
    });
    this.getUIContext().animateTo({
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
      return (event: ClickEvent) => {
        this.onClicked!(undefined);
      }
    }
    return undefined;
  }

  private getAccessibilitySelected(): boolean | undefined {
    if (this.getChipAccessibilitySelectedType() === ChipV2AccessibilitySelectedType.SELECTED) {
      return this.isChipActivated();
    }
    return undefined;
  }

  private getAccessibilityChecked(): boolean | undefined {
    if (this.getChipAccessibilitySelectedType() === ChipV2AccessibilitySelectedType.CHECKED) {
      return this.isChipActivated();
    }
    return undefined;
  }

  private getChipAccessibilitySelectedType(): ChipV2AccessibilitySelectedType {
    if (typeof this.chipV2Options.activated === 'undefined') {
      return ChipV2AccessibilitySelectedType.CLICKED;
    }
    return this.chipV2Options.accessibilitySelectedType ?? ChipV2AccessibilitySelectedType.CHECKED;
  }

  private getAccessibilityDescription(): ResourceStr | undefined {
    if (typeof this.chipV2Options.accessibilityDescription === 'undefined') {
      return undefined;
    }
    return this.chipV2Options.accessibilityDescription as ResourceStr;
  }

  isChipEnabled(): boolean {
    return this.chipV2Options.enabled ?? true;
  }

  getChipBorderRadius(): Dimension {
    if (typeof this.chipV2Options.borderRadius !== 'undefined' && this.isValidLength(this.chipV2Options.borderRadius)) {
      return lengthMetricsToDimension(this.chipV2Options.borderRadius!);
    }
    return this.isSmallChipSize() ? this.theme.chipNode.smallBorderRadius : this.theme.chipNode.normalBorderRadius;
  }

  isSmallChipSize() {
    return typeof this.chipV2Options.size === 'string' && this.chipV2Options.size === ChipV2Size.SMALL;
  }

  getChipBackgroundColor(): ResourceColor {
    let themeChipNode = this.theme.chipNode;
    if (this.isChipActivated()) {
      return this.chipNodeInFocus && !this.isSetActiveChipBgColor() ? themeChipNode.focusActivatedBgColor :
        this.getColor(this.chipV2Options.activatedBackgroundColor, themeChipNode.activatedBackgroundColor);
    }
    return this.chipNodeInFocus && !this.isSetNormalChipBgColor() ? themeChipNode.focusBgColor :
      this.getColor(this.chipV2Options.backgroundColor, this.theme.chipNode.backgroundColor);
  }

  getBackgroundSystemMaterial(): uiMaterial.Material | undefined {
    if (deviceInfo.sdkApiVersion < 26) {
      return undefined;
    }
    if (this.isChipActivated()) {
      return this.chipV2Options.activatedBackgroundSystemMaterial;
    }
    return this.chipV2Options.backgroundSystemMaterial;
  }

  getColor(color: ColorMetrics | undefined, defaultColor: ResourceColor): ResourceColor {
    if (!color) {
      return defaultColor;
    }
    try {
      return color.color;
    } catch (e) {
      console.error(`[ChipV2] failed to get color`);
      return Color.Transparent;
    }
  }

  isChipActivated() {
    return this.chipV2Options.activated ?? false;
  }

  private getResourceNumber(resource: Resource): number | null {
    const resourceManager = this.getUIContext().getHostContext()?.resourceManager;
    if (!resourceManager) {
      console.error('[ChipV2] failed to get resourceManager');
      return null;
    }

    switch (resource.type) {
      case RESOURCE_TYPE_FLOAT:
      case RESOURCE_TYPE_INTEGER:
        try {
          if (resource.id !== -1) {
            return resourceManager.getDouble(resource.id);
          }
          return resourceManager.getDoubleByName((((resource.params!)[0]) as string).split('.')[2]);
        } catch (error) {
          console.error(`[ChipV2] get resource error`);
          return null;
        }
      default:
        return null;
    }
  }

  resourceToNumber(resource: Resource, defaultValue: number): number {
    if (!resource || !resource.type) {
      console.error('[ChipV2] failed: resource get fail');
      return defaultValue;
    }

    const result = this.getResourceNumber(resource);
    return result !== null ? result : defaultValue;
  }

  isValidLength(length: LengthMetrics | undefined): boolean {
    if (!length || length.unit === LengthUnit.PERCENT) {
      return false;
    }
    return length.value >= 0;
  }

  private chipZoomOut() {
    if (this.isSuffixIconFocusStyleCustomized) {
      this.chipScale = {
        x: 1, y: 1
      };
    }
  }

  private chipZoomIn() {
    if (this.isSuffixIconFocusStyleCustomized) {
      this.chipScale = {
        x: this.resourceToNumber(this.theme.chipNode.focusBtnScaleX, 1),
        y: this.resourceToNumber(this.theme.chipNode.focusBtnScaleY, 1),
      };
    }
  }

  private isNeedShowCloseIconMargin(): boolean {
    return this.isClosable() && this.isSuffixIconFocusStyleCustomized;
  }

  private parseLength(length: Length): double | undefined {
    if (typeof length === 'number') {
      return length as double;
    }
    if (typeof length === 'string') {
      const regexp = new RegExp('(\\d+)(vp|px|lpx|fp)?');
      const matches = regexp.match(length as string);
      if (!matches || matches.length < 2) {
        return undefined;
      }
      const value = parseFloat(matches[1] as string);
      const unit = matches.length >= 3 ? matches[2] : '';
      if (unit === 'vp' || unit === '') {
        return value;
      } else if (unit === 'px') {
        return this.getUIContext().px2vp(value);
      } else if (unit === 'fp') {
        return this.getUIContext().px2vp(this.getUIContext().fp2px(value));
      } else if (unit === 'lpx') {
        return this.getUIContext().px2vp(this.getUIContext().lpx2px(value));
      } else {
        return undefined;
      }
    }
    if (typeof length === 'object') {
      try {
        const metrics = LengthMetrics.resource(length as Resource);
        if (metrics.unit === LengthUnit.VP) {
          return metrics.value;
        } else if (metrics.unit === LengthUnit.PX) {
          return this.getUIContext().px2vp(metrics.value);
        } else if (metrics.unit === LengthUnit.FP) {
          return this.getUIContext().px2vp(this.getUIContext().fp2px(metrics.value));
        } else {
          return this.getUIContext().px2vp(this.getUIContext().lpx2px(metrics.value));
        }
      } catch (error) {
        console.error('Failed to parse length because the type of resource is invalid');
        return undefined;
      }
    }
    return undefined;
  }

  build() {
    if (this.isChipExist) {
      this.ChipBuilder()
    } else {
      Row().width(0).height(0)
    }
  }
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

function lengthMetricsToDimension(length: LengthMetrics): Dimension {
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

function colorMetricsToResourceColor(color: ColorMetrics | undefined): ResourceColor | undefined {
  if (!color) {
    return undefined;
  }
  return color.color;
}