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
  ResourceStr,
  SizeOptions,
  ResourceColor,
  VoidCallback,
  Dimension,
  Resource,
  Length,
  Margin,
  LocalizedMargin,
  LocalizedPadding,
  Direction,
  Builder,
  Component,
  ScaleOptions,
  SymbolEffect,
  ShadowStyle,
  Button,
  ButtonOptions,
  ButtonType,
  Flex,
  FlexAlign,
  ItemAlign,
  SymbolGlyph,
  SymbolEffectStrategy,
  Image,
  ImageFit,
  Text,
  TextOverflow,
  TextAlign,
  Color,
  HoverEffect,
  KeyType,
  CommonMethod,
  Callback,
  ClickEvent,
  ConstraintSizeOptions,
  Padding,
  FontWeight,
  Curve,
  $r,
  KeyEvent,
  SymbolGlyphModifier,
  Column,
  Row
} from '@ohos.arkui.component';
import {
  Consume,
  Link,
  Watch,
  ObjectLink,
  Observed,
  Require,
  State,
  Provide,
  Prop,
  PropRef
} from '@ohos.arkui.stateManagement';
import { ColorMetrics, LengthMetrics } from '@ohos.arkui.node';
import { KeyCode } from '@ohos.multimodalInput.keyCode';
import hilog from '@ohos.hilog';
import resourceManager from '@ohos.resourceManager';
import common from '@ohos.app.ability.common';

export enum ChipSize {
  NORMAL = 'NORMAL',
  SMALL = 'SMALL'
}

enum IconType {
  PREFIX_ICON = 'PREFIXICON',
  SUFFIX_ICON = 'SUFFIXICON',
  PREFIX_SYMBOL = 'PREFIXSYMBOL',
  SUFFIX_SYMBOL = 'SUFFIXSYMBOL',
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
  action?: VoidCallback;
  accessibilityText?: ResourceStr;
  accessibilityDescription?: ResourceStr;
  accessibilityLevel?: string;
}

export interface PrefixIconOptions extends IconCommonOptions {}

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
  normalSize: SizeOptions;
  smallSize: SizeOptions;
  fillColor: ResourceColor;
  activatedFillColor: ResourceColor;
  focusFillColor: ResourceColor;
  focusActivatedColor: ResourceColor;
}

interface PrefixIconTheme extends IconTheme {}

interface SuffixIconTheme extends IconTheme {
  defaultDeleteIcon: ResourceStr;
  focusable: boolean;
  isShowMargin: Resource;
}

interface DefaultSymbolTheme {
  normalFontColor: Array<ResourceColor>;
  activatedFontColor: Array<ResourceColor>;
  smallSymbolFontSize: Length;
  normalSymbolFontSize: Length;
  defaultEffect: int;
}

interface LabelTheme {
  normalFontSize: Dimension;
  smallFontSize: Dimension;
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
}

interface ChipNodeOpacity {
  normal: double;
  hover: double;
  pressed: double;
}

interface ChipNodeConstraintWidth {
  breakPointMinWidth: double,
  breakPointSmMaxWidth: double,
  breakPointMdMaxWidth: double,
  breakPointLgMaxWidth: double,
}

export interface AccessibilityOptions {
  accessibilityLevel?: string;
  accessibilityText?: ResourceStr;
  accessibilityDescription?: ResourceStr;
}

const NO = 'no'
const NO_HIDE = 'no-hide-descendants'

export interface CloseOptions extends AccessibilityOptions {}

interface ChipNodeTheme {
  suitAgeScale: double;
  minLabelWidth: Dimension;
  normalHeight: Dimension;
  smallHeight: Dimension;
  enabled: boolean;
  activated: boolean;
  backgroundColor: ResourceColor;
  activatedBackgroundColor: ResourceColor;
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
  focusOutlineMargin: double;
  normalBorderRadius: Dimension;
  smallBorderRadius: Dimension;
  borderWidth: double;
  localizedNormalPadding: LocalizedPadding;
  localizedSmallPadding: LocalizedPadding;
  hoverBlendColor: ResourceColor;
  pressedBlendColor: ResourceColor;
  opacity: ChipNodeOpacity;
  breakPointConstraintWidth: ChipNodeConstraintWidth;
}

export interface ChipSymbolGlyphOptions {
  normal?: SymbolGlyphModifier;
  activated?: SymbolGlyphModifier;
}

interface ChipTheme {
  prefixIcon: PrefixIconTheme;
  label: LabelTheme;
  suffixIcon: SuffixIconTheme;
  defaultSymbol: DefaultSymbolTheme;
  chipNode: ChipNodeTheme;
}

const RESOURCE_TYPE_STRING: int = 10003;
const RESOURCE_TYPE_FLOAT: int = 10002;
const RESOURCE_TYPE_INTEGER: int = 10007;

function resolveResourceStr(resource: ResourceStr | undefined): string {
  try {
    if (!resource) {
      return '';
    } else if (typeof resource === 'string') {
      return resource as string;
    } else {
      return resourceManager.getSysResourceManager().getStringSync((resource as Resource).id);
    }
  } catch (error) {
    if (error instanceof ClassCastError) {
        let code: number | undefined = (error as ClassCastError).code;
        let message: string | undefined = (error as ClassCastError).message;
        hilog.error(0x3900, 'utils', `resolveResourceStr error, code: ${code}, message: ${message}`);
    }
    return '';
  }
}

export interface ChipOptions {
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
    chipSize: (options.size ??  ChipSize.NORMAL),
    prefixIcon: options.prefixIcon,
    prefixSymbol: options.prefixSymbol,
    label: options.label,
    suffixIcon: options.suffixIcon,
    suffixSymbol: options.suffixSymbol,
    suffixSymbolOptions: options.suffixSymbolOptions,
    allowClose: options.allowClose,
    closeOptions: options.closeOptions,
    chipEnabled: (options.enabled ?? true),
    chipActivated: options.activated,
    chipNodeBackgroundColor: options.backgroundColor,
    chipNodeActivatedBackgroundColor: options.activatedBackgroundColor,
    chipNodeRadius: options.borderRadius,
    chipDirection: (options.direction ?? Direction.Auto),
    chipAccessibilitySelectedType: options.accessibilitySelectedType,
    chipAccessibilityDescription: options.accessibilityDescription,
    chipAccessibilityLevel: options.accessibilityLevel,
    onClose: options.onClose,
    onClicked: options.onClicked,
  })
}

@Component
export struct ChipComponent {
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
      focusFontColor: $r('sys.color.chip_focus_text'),
      focusActiveFontColor: $r('sys.color.chip_activated_focus_font_color'),
      fontColor: $r('sys.color.chip_font_color'),
      activatedFontColor: $r('sys.color.chip_activated_fontcolor'),
      fontFamily: 'HarmonyOS Sans',
      fontWeight: $r('sys.float.chip_text_font_weight'),
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
        start: LengthMetrics.resource($r('sys.float.chip_normal_text_margin')),
        end: LengthMetrics.resource($r('sys.float.chip_normal_text_margin')),
        top: LengthMetrics.vp(0),
        bottom: LengthMetrics.vp(0)
      },
      localizedSmallMargin: {
        start: LengthMetrics.resource($r('sys.float.chip_small_text_margin')),
        end: LengthMetrics.resource($r('sys.float.chip_small_text_margin')),
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
      normalSymbolFontSize: LengthMetrics.resource($r('sys.float.chip_normal_icon_size')).value as Length,
      smallSymbolFontSize: LengthMetrics.resource($r('sys.float.chip_small_icon_size')).value as Length,
      defaultEffect: -1,
    },
    chipNode: {
      suitAgeScale: 1.75,
      minLabelWidth: 12,
      normalHeight: $r('sys.float.chip_normal_height'),
      smallHeight: $r('sys.float.chip_small_height'),
      enabled: true,
      activated: false,
      backgroundColor: $r('sys.color.chip_background_color'),
      activatedBackgroundColor: $r('sys.color.chip_container_activated_color'),
      focusOutlineColor: $r('sys.color.ohos_id_color_focused_outline'),
      focusOutlineMargin: 2,
      borderColor: $r('sys.color.chip_border_color'),
      defaultBorderWidth: $r('sys.float.chip_border_width'),
      activatedBorderColor: $r('sys.color.chip_activated_border_color'),
      normalBorderRadius: $r('sys.float.chip_border_radius_normal'),
      smallBorderRadius: $r('sys.float.chip_border_radius_small'),
      borderWidth: 2,
      focusBtnScaleX: $r('sys.float.chip_focused_btn_scale'),
      focusBtnScaleY: $r('sys.float.chip_focused_btn_scale'),
      localizedNormalPadding: {
        start: LengthMetrics.resource($r('sys.float.chip_normal_text_padding')),
        end: LengthMetrics.resource($r('sys.float.chip_normal_text_padding')),
        top: LengthMetrics.vp(4),
        bottom: LengthMetrics.vp(4)
      },
      localizedSmallPadding: {
        start: LengthMetrics.resource($r('sys.float.chip_small_text_padding')),
        end: LengthMetrics.resource($r('sys.float.chip_small_text_padding')),
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
      }
    }
  } as ChipTheme;
  @PropRef chipSize?: ChipSize | SizeOptions;
  @PropRef allowClose?: boolean;
  @PropRef closeOptions?: CloseOptions;
  @PropRef prefixSymbol?: ChipSymbolGlyphOptions;
  @PropRef chipDirection?: Direction;
  @PropRef prefixIcon?: PrefixIconOptions;
  @Require @PropRef label: LabelOptions;
  @PropRef suffixIcon?: SuffixIconOptions;
  @PropRef suffixSymbol?: ChipSymbolGlyphOptions;
  @PropRef suffixSymbolOptions?: ChipSuffixSymbolGlyphOptions;
  @PropRef chipNodeBackgroundColor?: ResourceColor;
  @PropRef chipNodeActivatedBackgroundColor?: ResourceColor;
  @PropRef chipNodeRadius?: Dimension;
  @PropRef chipEnabled?: boolean;
  @PropRef chipActivated?: boolean;
  @PropRef chipAccessibilitySelectedType?: AccessibilitySelectedType;
  @PropRef chipAccessibilityDescription?: ResourceStr;
  @PropRef chipAccessibilityLevel?: string;
  @State isChipExist: boolean = true;
  @State chipScale: ScaleOptions = { x: 1, y: 1 } as ScaleOptions;
  @State chipOpacity: number = 1;
  @State suffixSymbolHeight: number = 0;
  @State suffixSymbolWidth: number = 0;
  @State breakPoint: BreakPointsType = BreakPointsType.SM;
  @State fontSizeScale: number = 1;
  private isSuffixIconFocusStyleCustomized: boolean =
    this.resourceToNumber(this.theme.suffixIcon.isShowMargin, 0) !== 0;
  private isSuffixIconFocusable: boolean = this.resourceToNumber(this.theme.suffixIcon.isShowMargin, 0) !== 0;
  public onClose?: VoidCallback;
  public onClicked?: VoidCallback;
  @State chipNodeInFocus: boolean = false;
  private symbolEffect: SymbolEffect = new SymbolEffect();

  private isSetActiveChipBgColor(): boolean {
    if (this.chipNodeActivatedBackgroundColor) {
      return false;
    }
    try {
      return ColorMetrics.resourceColor(this.chipNodeActivatedBackgroundColor as ResourceColor).color !==
      ColorMetrics.resourceColor(this.theme.chipNode.activatedBackgroundColor as ResourceColor).color;
    } catch (error) {
      console.error(`[Chip] failed to get ColorMetrics.resourceColor`);
      return false;
    }
  }

  private isSetNormalChipBgColor(): boolean {
    if (this.chipNodeBackgroundColor) {
      return false;
    }
    try {
      return ColorMetrics.resourceColor(this.chipNodeBackgroundColor as ResourceColor).color !==
      ColorMetrics.resourceColor(this.theme.chipNode.backgroundColor as ResourceColor).color;
    } catch (error) {
      console.error(`[Chip] failed to get resourceColor`);
      return false;
    }
  }

  private getShadowStyles(): ShadowStyle | undefined {
    if (!this.chipNodeInFocus) {
      return undefined;
    }
    switch (this.resourceToNumber(this.isSmallChipSize() ? this.theme.chipNode.smallShadowStyle :
      this.theme.chipNode.normalShadowStyle, -1) as int) {
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
    Button({ type: ButtonType.Normal } as ButtonOptions) {
      Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
        if (this.hasPrefixSymbol()) {
          SymbolGlyph()
            .fontSize(this.defaultSymbolFontsize())
            .fontColor(this.getDefaultSymbolColor(IconType.PREFIX_SYMBOL))
            .flexShrink(0)
            .attributeModifier(this.getPrefixSymbolModifier())
            .effectStrategy(SymbolEffectStrategy.NONE)
            .symbolEffect(this.symbolEffect, false)
        } else if (this.prefixIcon?.src) {
          Image(this.prefixIcon!.src)
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
          Button({ type: ButtonType.Normal } as ButtonOptions) {
            SymbolGlyph()
              .fontSize(this.defaultSymbolFontsize())
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
        } else if (this.suffixIcon?.src) {
          Button({ type: ButtonType.Normal } as ButtonOptions) {
            Image(this.suffixIcon!.src)
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
          .focusable(this.isSuffixIconFocusable)
        } else if (this.isClosable()) {
          Button({ type: ButtonType.Normal } as ButtonOptions) {
            SymbolGlyph($r('sys.symbol.xmark'))
              .fontSize(this.defaultSymbolFontsize())
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
          .onClick((e: ClickEvent) => {
            if (!this.isChipEnabled()) {
              return;
            }
            this.onClose?.();
            this.deleteChip();
          })
          .focusable(this.isSuffixIconFocusable)
        }
      }
      .direction(this.chipDirection)
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
    .direction(this.chipDirection)
    .backgroundColor(this.getChipBackgroundColor())
    .borderWidth(this.theme.chipNode.defaultBorderWidth)
    .borderColor(this.getChipNodeBorderColor())
    .borderRadius(this.getChipBorderRadius())
    .accessibilityGroup(true)
    .accessibilityDescription(this.getAccessibilityDescription())
    .accessibilityLevel(this.getAccessibilityLevel())
    .accessibilityChecked(this.getAccessibilityChecked())
    .accessibilitySelected(this.getAccessibilitySelected())
    .onClick(this.onClicked)
    .scale(this.chipScale)
    .opacity(this.chipOpacity)
    .onKeyEvent((event: KeyEvent) => {
      if (!event  || event.type !== KeyType.Down) {
        return false;
      }
      let isDeleteChip = event.keyCode === KeyCode.KEYCODE_FORWARD_DEL;
      let isEnterDeleteChip = event.keyCode === KeyCode.KEYCODE_ENTER && this.allowClose !== false &&
        !this.suffixIcon?.src && this.isSuffixIconFocusStyleCustomized;
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
  }

  getSuffixIconAction(): Callback<ClickEvent> | undefined {
    if (this.suffixIcon?.src) {
      if (!this.suffixIcon?.action) {
        return undefined;
      }
      return () => {
        if (this.isChipEnabled()) {
          this.suffixIcon?.action?.();
        }
      };
    }
    return undefined;
  }

  getSuffixIconFilledColor(): ResourceColor {
    if (this.isChipActivated()) {
      return this.suffixIcon?.activatedFillColor ?? this.getDefaultActiveIconColor(IconType.PREFIX_ICON);
    }
    return this.suffixIcon?.fillColor ?? this.getDefaultFillIconColor(IconType.SUFFIX_ICON);
  }

  getSuffixIconSize(): SizeOptions {
    let suffixIconSize: SizeOptions = { width: 0, height: 0 };
    if (typeof this.suffixIcon?.size?.width !== 'undefined' &&
    this.isValidLength(this.suffixIcon!.size!.width as Length)) {
      suffixIconSize.width = this.suffixIcon!.size!.width;
    } else {
      suffixIconSize.width =
        this.isSmallChipSize() ? this.theme.suffixIcon.smallSize.width : this.theme.suffixIcon.normalSize.width;
    }
    if (typeof this.suffixIcon?.size?.height !== 'undefined' &&
    this.isValidLength(this.suffixIcon!.size!.height as Length)) {
      suffixIconSize.height = this.suffixIcon!.size!.height;
    } else {
      suffixIconSize.height =
        this.isSmallChipSize() ? this.theme.suffixIcon.smallSize.height : this.theme.suffixIcon.normalSize.height;
    }
    return suffixIconSize;
  }

  isClosable(): boolean {
    return this.allowClose ?? true;
  }

  getSuffixSymbolAction(): Callback<ClickEvent> | undefined {
    if (typeof this.suffixSymbolOptions?.action === 'undefined') {
      return (() => {
        0;
        return undefined;
      })();
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
      return this.prefixIcon?.activatedFillColor ?? this.getDefaultActiveIconColor(IconType.PREFIX_ICON);
    }
    return this.prefixIcon?.fillColor ?? this.getDefaultFillIconColor(IconType.PREFIX_ICON);
  }

  getPrefixIconSize(): SizeOptions {
    let prefixIconSize: SizeOptions = { width: 0, height: 0 };
    if (typeof this.prefixIcon?.size?.width !== 'undefined' &&
    this.isValidLength(this.prefixIcon!.size!.width as Length)) {
      prefixIconSize.width = this.prefixIcon!.size!.width;
    } else {
      prefixIconSize.width =
        this.isSmallChipSize() ? this.theme.prefixIcon.smallSize.width : this.theme.prefixIcon.normalSize.width;
    }
    if (typeof this.prefixIcon?.size?.height !== 'undefined' &&
    this.isValidLength(this.prefixIcon!.size!.height as Length)) {
      prefixIconSize.height = this.prefixIcon!.size!.height;
    } else {
      prefixIconSize.height =
        this.isSmallChipSize() ? this.theme.prefixIcon.smallSize.height : this.theme.prefixIcon.normalSize.height;
    }
    return prefixIconSize;
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
      if (typeof (this.chipSize as SizeOptions)?.width === 'undefined' ||
        !this.isValidLength((this.chipSize as SizeOptions)!.width as Length)) {
        constraintSize.maxWidth = this.getChipMaxWidth();
      }
      if (typeof (this.chipSize as SizeOptions)?.height === 'undefined' ||
        !this.isValidLength((this.chipSize as SizeOptions)!.height as Length)) {
        constraintSize.minHeight = this.theme.chipNode.normalHeight;
      }
    }
    return constraintSize;
  }

  getChipMaxWidth(): Length | undefined {
    if (this.fontSizeScale >= this.theme.chipNode.suitAgeScale) {
      return (() => {
        0;
        return undefined;
      })();
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
    return (() => {
      0;
      return undefined;
    })();
  }

  getChipSize(): SizeOptions | undefined {
    const chipSize: SizeOptions = {
      width: 'auto',
      height: 'auto'
    };

    if (typeof this.chipSize !== 'string') {
      if (typeof (this.chipSize as SizeOptions)?.width !== 'undefined' &&
      this.isValidLength((this.chipSize as SizeOptions)!.width as Length)) {
        chipSize.width = (this.chipSize as SizeOptions)!.width;
      }
      if (typeof (this.chipSize as SizeOptions)?.height !== 'undefined' &&
      this.isValidLength((this.chipSize as SizeOptions)!.height as Length)) {
        chipSize.height = (this.chipSize as SizeOptions)!.height;
      }
    }

    return chipSize;
  }

  getChipPadding(): Length | Padding | LocalizedPadding {
    return this.isSmallChipSize() ? this.theme.chipNode.localizedSmallPadding :
      this.theme.chipNode.localizedNormalPadding;
  }

  getPrefixSymbolModifier(): SymbolGlyphModifier | undefined {
    if (this.isChipActivated()) {
      return this.prefixSymbol?.activated;
    }
    return this.prefixSymbol?.normal;
  }

  getLabelMargin(): Length | Padding | LocalizedPadding {
    const localizedLabelMargin: LocalizedMargin = {
      start: LengthMetrics.vp(0),
      end: LengthMetrics.vp(0),
    };
    const defaultLocalizedMargin =
      this.isSmallChipSize() ? this.theme.label.localizedSmallMargin : this.theme.label.localizedNormalMargin;

    if (typeof this.label?.localizedLabelMargin?.start !== 'undefined' &&
      this.label!.localizedLabelMargin!.start!.value >= 0) {
      localizedLabelMargin.start = this.label!.localizedLabelMargin!.start;
    } else if (this.hasPrefix()) {
      localizedLabelMargin.start = defaultLocalizedMargin.start;
    }

    if (typeof this.label?.localizedLabelMargin?.end !== 'undefined' &&
      this.label!.localizedLabelMargin!.end!.value >= 0) {
      localizedLabelMargin.end = this.label!.localizedLabelMargin!.end;
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
      if (typeof this.label?.labelMargin?.left !== 'undefined' &&
      this.isValidLength(this.label!.labelMargin!.left as Length)) {
        labelMargin.left = this.label!.labelMargin!.left;
      } else if (this.hasPrefix()) {
        labelMargin.left = defaultLabelMargin.left;
      }
      if (typeof this.label?.labelMargin?.right !== 'undefined' &&
      this.isValidLength(this.label!.labelMargin!.right as Length)) {
        labelMargin.right = this.label!.labelMargin!.right;
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
    return false;
  }

  private hasPrefix(): boolean {
    if (this.prefixIcon?.src) {
      return true;
    }
    return false;
  }

  getLabelFontWeight(): string | int | FontWeight {
    if (this.isChipActivated()) {
      return FontWeight.Medium;
    }
    switch (this.resourceToNumber(this.theme.label.fontWeight, FontWeight.Regular) as int) {
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
    return this.label?.fontFamily ?? this.theme.label.fontFamily;
  }

  private defaultSymbolFontsize(): Length {
    return this.isSmallChipSize() ? this.theme.defaultSymbol.smallSymbolFontSize :
      this.theme.defaultSymbol.normalSymbolFontSize;
  }

  private getActiveFontColor(): ResourceColor {
    return this.chipNodeInFocus ? this.theme.label.focusActiveFontColor : this.theme.label.activatedFontColor;
  }

  private getFontColor(): ResourceColor {
    return this.chipNodeInFocus ? this.theme.label.focusFontColor : this.theme.label.fontColor;
  }

  private getChipNodeBorderColor(): ResourceColor {
    let themeChipNode = this.theme.chipNode;
    return this.isChipActivated() ? themeChipNode.activatedBorderColor : themeChipNode.borderColor;
  }

  getLabelFontColor(): ResourceColor {
    if (this.isChipActivated()) {
      return this.label?.activatedFontColor ?? this.getActiveFontColor();
    }
    return this.label?.fontColor ?? this.getFontColor();
  }

  getLabelFontSize(): Dimension {
    if (typeof this.label.fontSize !== 'undefined' && this.isValidLength(this.label!.fontSize as Length)) {
      return this.label!.fontSize as Dimension;
    }
    if (this.isSmallChipSize()) {
      return this.theme.label.smallFontSize;
    }
    return this.theme.label.normalFontSize;
  }

  getChipText(): ResourceStr {
    return this.label?.text ?? '';
  }

  deleteChip() {
    this.getUIContext()?.animateTo({ curve: Curve.Sharp, duration: 150 }, () => {
      this.chipOpacity = 0;
    });
    this.getUIContext()?.animateTo({
      curve: Curve.FastOutLinearIn,
      duration: 150,
      onFinish: () => {
        this.isChipExist = false;
      }
    }, () => {
      this.chipScale = { x: 0.85, y: 0.85 };
    })
  }

  isChipEnabled(): boolean {
    return this.chipEnabled ?? true;
  }

  getChipBorderRadius(): Dimension {
    if (typeof this.chipNodeRadius !== 'undefined') {
      return this!.chipNodeRadius as Dimension;
    }
    return this.isSmallChipSize() ? this.theme.chipNode.smallBorderRadius : this.theme.chipNode.normalBorderRadius;
  }

  isSmallChipSize() {
    return typeof this.chipSize === 'string' && this.chipSize === ChipSize.SMALL;
  }

  getChipBackgroundColor(): ResourceColor {
    let themeChipNode = this.theme.chipNode;
    if (this.isChipActivated()) {
      return this.chipNodeInFocus && !this.isSetActiveChipBgColor() ? themeChipNode.focusActivatedBgColor :
        this.getColor(this.chipNodeActivatedBackgroundColor, themeChipNode.activatedBackgroundColor);
    }
    return this.chipNodeInFocus && !this.isSetNormalChipBgColor() ? themeChipNode.focusBgColor :
      this.getColor(this.chipNodeBackgroundColor, this.theme.chipNode.backgroundColor);
  }

  getColor(color: ResourceColor | undefined, defaultColor: ResourceColor): ResourceColor {
    if (!color) {
      return defaultColor;
    }
    try {
      ColorMetrics.resourceColor(color).color;
      return color;
    } catch (e) {
      console.log('[Chip] failed to get color. msg: ', e);
      return Color.Transparent;
    }
  }

  private getCloseIconAccessibilityLevel(): string {
    const level = this.closeOptions?.accessibilityLevel;
    if (level === NO || level === NO_HIDE) {
      return level!;
    }
    return 'yes';
  }

  private getCloseIconAccessibilityDescription(): string {
    return resolveResourceStr(this.closeOptions?.accessibilityDescription);
  }

  private getCloseIconAccessibilityText(): string {
    if (typeof this.closeOptions?.accessibilityText === 'undefined') {
      return resolveResourceStr($r('sys.string.delete_used_for_accessibility_text'));
    }
    return resolveResourceStr(this.closeOptions?.accessibilityText);
  }

  private getSuffixIconAccessibilityLevel(): string {
    const level = this.suffixIcon?.accessibilityLevel;
    if (level === 'no' || level === 'no-hide-descendants') {
      return level!;
    }
    return this.suffixIcon?.action ? 'yes' : 'no';
  }

  private getSuffixIconAccessibilityDescription(): string {
    return resolveResourceStr(this.suffixIcon?.accessibilityDescription);
  }

  private getSuffixIconAccessibilityText(): string {
    return resolveResourceStr(this.suffixIcon?.accessibilityText);
  }

  private getSuffixSymbolAccessibilityLevel(): string {
    if (this.isChipActivated()) {
      const level = this.suffixSymbolOptions?.activatedAccessibility?.accessibilityLevel;
      if (level === 'no' || level === 'no-hide-descendants') {
        return level!;
      }
      return this.suffixSymbolOptions?.action ? 'yes' : 'no';
    }
    const level = this.suffixSymbolOptions?.normalAccessibility?.accessibilityLevel;
    if (level === 'no' || level === 'no-hide-descendants') {
      return level!;
    }
    return this.suffixSymbolOptions?.action ? 'yes' : 'no';
  }

  private getSuffixSymbolAccessibilityDescription(): string {
    if (this.isChipActivated()) {
      return resolveResourceStr(this.suffixSymbolOptions?.activatedAccessibility?.accessibilityDescription);
    }
    return resolveResourceStr(this.suffixSymbolOptions?.normalAccessibility?.accessibilityDescription);
  }

  private getSuffixSymbolAccessibilityText(): string {
    if (this.isChipActivated()) {
      return resolveResourceStr(this.suffixSymbolOptions?.activatedAccessibility?.accessibilityText);
    }
    return resolveResourceStr(this.suffixSymbolOptions?.normalAccessibility?.accessibilityText);
  }

  getSuffixSymbolModifier(): SymbolGlyphModifier | undefined {
    if (this.isChipActivated()) {
      return this.suffixSymbol?.activated;
    }
    return this.suffixSymbol?.normal;
  }

  private getAccessibilityChecked(): boolean | undefined {
    if (this.getChipAccessibilitySelectedType() === AccessibilitySelectedType.CHECKED) {
      return this.isChipActivated();
    }
    return undefined;
  }

  private getAccessibilitySelected(): boolean | undefined {
    if (this.getChipAccessibilitySelectedType() === AccessibilitySelectedType.SELECTED) {
      return this.isChipActivated();
    }
    return undefined;
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

  private getAccessibilityDescription(): string {
    return resolveResourceStr(this.chipAccessibilityDescription);
  }

  isChipActivated() {
    return this.chipActivated ?? false;
  }

  resourceToNumber(resource: Resource, defaultValue: number): number {
    if (!resource || !resource.type) {
      console.error('[Chip] failed: resource get fail');
      return defaultValue;
    }
    const resourceManager = this.getUIContext().getHostContext()?.resourceManager;
    if (!resourceManager) {
      console.error('[Chip] failed to get resourceManager');
      return defaultValue;
    }
    if ((resource?.type?.toInt()) === RESOURCE_TYPE_FLOAT || (resource?.type?.toInt()) === RESOURCE_TYPE_INTEGER) {
      try {
        if (resource.id !== -1) {
          return resourceManager.getDouble(resource.id);
        }
        return resourceManager.getDoubleByName((((resource.params!)[0]) as string).split('.')[2]);
      } catch (error) {
        console.error(`[Chip] get resource error, return defaultValue`);
        return defaultValue;
      }
    } else {
      return defaultValue;
    }
  }

  isValidLength(length: Length): boolean {
    if (typeof length === 'number') {
      return length as number >= 0;
    } else if (typeof length === 'string') {
      return this.isValidLengthString(length as string);
    } else if (typeof length === 'object') {
      const resource = length as Resource;
      const resourceManager = this.getUIContext().getHostContext()?.resourceManager;
      if (!resourceManager) {
        console.error('[Chip] failed to get resourceManager.');
        return false;
      }
      if ((resource?.type?.toInt()) === RESOURCE_TYPE_FLOAT || (resource?.type?.toInt()) === RESOURCE_TYPE_INTEGER) {
        return resourceManager.getDouble(resource.id) >= 0;
      } else if ((resource?.type?.toInt()) === RESOURCE_TYPE_STRING) {
        return this.isValidLengthString(resourceManager.getStringSync(resource.id));
      } else {
        return false;
      }
    }
    return false;
  }

  isValidLengthString(length: string): boolean {
    const matches = length.match(new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx)?$', 'i'));
    if (!matches || matches.length < 3) {
      return false;
    }
    return parseInt(matches[1] as string) >= 0;
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

  build() {
    if (this.isChipExist) {
      this.ChipBuilder()
    } else {
        Row().width(0).height(0)
    }
  }
}
