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

import display from '@ohos.display';
import {
  Alignment,
  BarState,
  BorderRadiuses,
  Builder,
  Button,
  ButtonType,
  Color,
  Column,
  ComponentV2,
  ConstraintSizeOptions,
  ColorContent,
  Context,
  Dimension,
  Direction,
  EdgeEffect,
  Flex,
  FlexWrap,
  FontWeight,
  Image,
  ItemAlign,
  Length,
  LocalizedMargin,
  LocalizedPadding,
  Resource,
  ResourceColor,
  ResourceStr,
  Row,
  Scroll,
  ScrollDirection,
  SizeOptions,
  SymbolGlyph,
  Text,
  TextAlign,
  TextOverflow,
  VerticalAlign,
  VoidCallback,
  ButtonStyleMode,
  ControlSize,
  Rectangle,
  $r
} from '@ohos.arkui.component';

import { SymbolGlyphModifier } from '@ohos.arkui.modifier';
import { Theme } from '@ohos.arkui.theme';
import { Computed, Event, Local, ObservedV2, Param, Require, Trace } from '@ohos.arkui.stateManagement'
import { LengthMetrics, LengthUnit } from '@ohos.arkui.node';
import { TextModifier, ImageModifier } from '@ohos.arkui.modifier';
import systemDateTime from '@ohos.systemDateTime';
import resourceManager from '@ohos.resourceManager';
import mediaQuery from '@ohos.mediaquery';
import I18n from '@ohos.i18n';

const RESOURCE_TYPE_STRING = 10003;
const RESOURCE_TYPE_FLOAT = 10002;
const RESOURCE_TYPE_INTEGER = 10007;
const RESOURCE_TYPE_MEDIA = 20000;
const RESOURCE_TYPE_RAWFILE = 30000;
const RESOURCE_TYPE_SYMBOL = 40000;

export interface IconTheme {
  size: SizeOptions;
  margin: LocalizedMargin;
  fillColor: ResourceColor;
  borderRadius: Length;
}

export interface TitleTheme {
  margin: LocalizedMargin;
  minFontSize: number;
  fontWeight: FontWeight;
  fontSize: Resource;
  fontColor: ResourceColor;
}

export interface ButtonTheme {
  margin: LocalizedMargin;
  padding: LocalizedPadding;
  fontSize: Resource;
  fontColor: ResourceColor;
  textMargin: LocalizedMargin;
  minFontSize: number;
  fontWeight: FontWeight;
  hoverColor: ResourceColor;
  backgroundColor: ResourceColor;
  responseRegion: Length;
}

export interface MessageTheme {
  fontSize: Resource;
  fontColor: ResourceColor;
  fontWeight: FontWeight;
  plainFontColor: ResourceColor;
}

export interface CloseButtonTheme {
  size: SizeOptions;
  margin: LocalizedMargin;
  padding: LocalizedPadding;
  fillColor: ResourceColor;
  hoverColor: ResourceColor;
  backgroundColor: ResourceColor;
  symbolStyle: SymbolGlyphModifier;
  symbolSize: string;
  accessibilityMessage: Resource;
  responseRegion: Length;
}

export interface WindowsTheme {
  padding: LocalizedPadding;
}

export interface PopupTheme {
  icon: IconTheme;
  title: TitleTheme;
  button: ButtonTheme;
  message: MessageTheme;
  windows: WindowsTheme;
  closeButton: CloseButtonTheme;
}

export const defaultTheme: PopupTheme = {
  icon: {
    size: { width: 32, height: 32 },
    margin: {
      top: LengthMetrics.vp(12),
      bottom: LengthMetrics.vp(12),
      start: LengthMetrics.vp(12),
      end: LengthMetrics.vp(12)
    },
    fillColor: '',
    borderRadius: $r('sys.float.ohos_id_corner_radius_default_s')

  },
  title: {
    margin: { bottom: LengthMetrics.vp(2) },
    minFontSize: 12,
    fontWeight: FontWeight.Medium,
    fontSize: $r('sys.float.ohos_id_text_size_sub_title2'),
    fontColor: $r('sys.color.font_primary')
  },
  button: {
    margin: {
      top: LengthMetrics.vp(16),
      bottom: LengthMetrics.vp(16),
      start: LengthMetrics.vp(16),
      end: LengthMetrics.vp(16)
    },
    padding: {
      top: LengthMetrics.vp(4),
      bottom: LengthMetrics.vp(4),
      start: LengthMetrics.vp(4),
      end: LengthMetrics.vp(4)
    },
    fontSize: $r('sys.float.ohos_id_text_size_button2'),
    fontColor: $r('sys.color.font_emphasize'),
    textMargin: {
      top: LengthMetrics.vp(8),
      bottom: LengthMetrics.vp(8),
      start: LengthMetrics.vp(8),
      end: LengthMetrics.vp(8)
    },
    minFontSize: 9,
    fontWeight: FontWeight.Medium,
    hoverColor: $r('sys.color.ohos_id_color_hover'),
    backgroundColor: $r('sys.color.ohos_id_color_background_transparent'),
    responseRegion: 32
  },
  message: {
    fontSize: $r('sys.float.ohos_id_text_size_body2'),
    fontColor: $r('sys.color.font_secondary'),
    fontWeight: FontWeight.Regular,
    plainFontColor: $r('sys.color.font_primary')
  },
  windows: {
    padding: {
      top: LengthMetrics.vp(12),
      bottom: LengthMetrics.vp(12),
      start: LengthMetrics.vp(12),
      end: LengthMetrics.vp(12)
    },
  },
  closeButton: {
    size: { width: 22, height: 22 },
    padding: {
      top: LengthMetrics.vp(2),
      bottom: LengthMetrics.vp(2),
      start: LengthMetrics.vp(2),
      end: LengthMetrics.vp(2)
    },
    margin: {
      top: LengthMetrics.vp(12),
      bottom: LengthMetrics.vp(12),
      start: LengthMetrics.vp(12),
      end: LengthMetrics.vp(12)
    },
    symbolStyle: new SymbolGlyphModifier($r('sys.symbol.xmark')),
    fillColor: $r('sys.color.icon_secondary'),
    hoverColor: $r('sys.color.ohos_id_color_hover'),
    backgroundColor: $r('sys.color.ohos_id_color_background_transparent'),
    symbolSize: '18vp',
    accessibilityMessage: $r('sys.string.off_used_for_accessibility_text'),
    responseRegion: 36
  },
};


export interface PopupV2Button {
  text?: ResourceStr;
  action?: VoidCallback;
  buttonTextModifier?: TextModifier
}

export interface PopupV2InitInfo {
  icon?: ResourceStr;
  iconModifier?: ImageModifier
  title?: ResourceStr;
  titleModifier?: TextModifier;
  message?: ResourceStr;
  messageModifier?: TextModifier
  direction?: Direction;
  showClose?: boolean | Resource;
  onClose?: VoidCallback;
  buttons?: [PopupV2Button | undefined, PopupV2Button | undefined];
  maxWidth?: Dimension;
}

const noop = () => {
};

const POPUP_DEFAULT_MAXWIDTH = 400;

@Builder
export function PopupV2(options: PopupV2InitInfo) {
  PopupV2Component({
    icon: options.icon,
    title: options.title,
    message: options.message,
    iconModifier: options.iconModifier,
    titleModifier:  options.titleModifier,
    messageModifier:  options.messageModifier,
    popupDirection: options.direction,
    showClose: options.showClose,
    onClose: options.onClose ?? noop,
    buttons: options.buttons,
    maxWidth: options.maxWidth
  })
}

function isValidString(dimension: string, regex: RegExp): boolean {
  const matches = dimension.match(regex);
  if (!matches || matches.length < 3) {
    return false;
  }
  const value = Number.parseFloat(matches[1] as string);
  return value >= 0;
}

function isValidDimensionString(dimension: string): boolean {
  return isValidString(dimension, new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$', 'i'));
}

function isValidResource(context: Context | undefined, value: Resource) {
  const resourceManager = context?.resourceManager;
  if (value === undefined || value === null || resourceManager === undefined) {
    return false;
  }
  if (value.type !== RESOURCE_TYPE_STRING && value.type !== RESOURCE_TYPE_INTEGER &&
    value.type !== RESOURCE_TYPE_FLOAT) {
    return false;
  }

  if (value.type === RESOURCE_TYPE_INTEGER) {
    if (resourceManager.getInt(value.id) >= 0) {
      return true;
    } else {
      return false;
    }
  }

  if (value.type === RESOURCE_TYPE_FLOAT) {
    if (resourceManager.getDouble(value.id) >= 0) {
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

@ComponentV2
export struct PopupV2Component {
  @Param onClose: () => void = noop;
  private theme: PopupTheme = defaultTheme;
  private applyContentKey: string = 'applyContent' + systemDateTime.getTime(false);
  @Param icon?: ResourceStr = '';
  @Require @Param maxWidth?: Dimension = '400vp';
  @Require @Param iconModifier?: ImageModifier;
  @Require @Param titleModifier?: TextModifier;
  @Require @Param messageModifier?: TextModifier;
  @Local messageMaxWidth ?: number = 0;
  @Param title?: ResourceStr =  '';
  @Param message ?: ResourceStr = '';
  @Param popupDirection ?: Direction = Direction.Auto;
  @Param showClose ?: boolean | Resource = true;
  @Param buttons ?: [PopupV2Button | undefined, PopupV2Button | undefined] =
    [{ text: '' }, { text: '' }] as [PopupV2Button | undefined, PopupV2Button | undefined];
  textHeight: number = 0;
  @Local titleHeight: number = 0;
  @Local applyHeight: number = 0;
  @Local buttonHeight: number = 0;
  @Local messageMaxWeight: number | undefined = 0;
  beforeScreenStatus: boolean | undefined = undefined;
  @Local currentScreenStatus: boolean | undefined = undefined;
  @Local applySizeOptions: ConstraintSizeOptions | undefined = undefined;
  @Local closeButtonBackgroundColor: ResourceColor = $r('sys.color.ohos_id_color_background_transparent');
  @Local firstButtonBackgroundColor: ResourceColor = $r('sys.color.ohos_id_color_background_transparent');
  @Local secondButtonBackgroundColor: ResourceColor = $r('sys.color.ohos_id_color_background_transparent');
  @Local closeButtonFillColorWithTheme: ResourceColor = $r('sys.color.icon_secondary');
  @Local firstButtonHeight: number = 0;
  @Local secondButtonHeight: number = 0;
  private listener ?: mediaQuery.MediaQueryListener =
    this.getUIContext().getMediaQuery().matchMediaSync('(orientation: landscape)')

  private getIconWidth(): Dimension {
    return  this.theme.icon.size.width as number
  }

  private getIconHeight(): Dimension {
    return this.theme.icon.size.height as number
  }

  private getIconFillColor(): ResourceColor {
    return this.theme.icon.fillColor
  }

  private getIconBorderRadius(): Length | BorderRadiuses {
    return this.theme.icon.borderRadius
  }

  private getLengthMetrics(value: number, unit ?: LengthUnit | undefined): LengthMetrics {
    if (unit === undefined || unit === null) {
      unit = LengthUnit.VP;
    }
    switch (unit as LengthUnit) {
      case LengthUnit.PX:
        return LengthMetrics.px(value);
      case LengthUnit.VP:
        return LengthMetrics.vp(value);
      case LengthUnit.FP:
        return LengthMetrics.fp(value);
      case LengthUnit.PERCENT:
        return LengthMetrics.percent(value);
      case LengthUnit.LPX:
        return LengthMetrics.lpx(value);
      default:
        return LengthMetrics.vp(value);
    }
  }

  private getIconMargin(): LocalizedMargin {
    const buttonMarginStart = this.theme.button.margin.start?.value ?? 0;
    const buttonMarginStartUnit = this.theme.button.margin.start?.unit;
    const buttonMarginEnd = this.theme.button.margin.end?.value ?? 0;
    const iconMarginStart = this.theme.icon.margin.start?.value ?? 0;
    const iconMarginStartUnit = this.theme.icon.margin.start?.unit;
    return {
      start: this.getLengthMetrics(buttonMarginStart / 2, buttonMarginStartUnit),
      end: this.getLengthMetrics(iconMarginStart - (buttonMarginEnd / 2), iconMarginStartUnit)
    }
  }

  private getIconImage(): ResourceStr | undefined {
    return this.icon
  }

  private getTitleText(): ResourceStr | undefined {
    return this.title
  }

  private getTitlePadding(): LocalizedPadding {
    return {
      start: this.getLengthMetrics((this.theme.button.margin.start?.value as number || 0) / 2,
        this.theme.button.margin.start?.unit),
      end: this.theme.closeButton.margin.end
    }
  }

  private getTitleMargin(): LocalizedMargin {
    return this.theme.title.margin
  }

  private getTitleMinFontSize(): number | string | Resource {
    return this.theme.title.minFontSize
  }

  private getTitleFontWeight(): int | FontWeight | string {
    return this.theme.title.fontWeight
  }

  private getTitleFontSize(): number | string | Resource {
    return this.theme.title.fontSize
  }

  private getTitleFontColor(): ResourceColor {
    return this.theme.title.fontColor
  }

  private getCloseButtonWidth(): Length | undefined {
    return this.theme.closeButton.size.width
  }

  private getCloseButtonHeight(): Length | undefined {
    return this.theme.closeButton.size.height
  }

  private getCloseButtonFillColor(): ResourceColor {
    return this.closeButtonFillColorWithTheme;
  }

  private getCloseButtonHoverColor(): ResourceColor {
    return this.theme.closeButton.hoverColor
  }

  private getCloseButtonBackgroundColor(): ResourceColor {
    return this.theme.closeButton.backgroundColor
  }

  private getCloseButtonPadding(): LocalizedPadding {
    return this.theme.closeButton.padding
  }

  private getCloseButtonSymbolSize(): string | undefined {
    return this.theme.closeButton.symbolSize
  }

  private getMessageText(): ResourceStr | undefined {
    return this.message ?? ''
  }

  private getMessageFontSize(): number | string | Resource {
    return this.theme.message.fontSize
  }

  private getMessageFontColor(): ResourceColor | undefined {
    let fontColor: ResourceColor | undefined
    if (this.title !== '' && this.title !== undefined) {
      fontColor = this.theme.message.fontColor
    } else {
      fontColor = this.theme.message.plainFontColor
    }
    return fontColor
  }

  private getMessagePadding(): LocalizedPadding {
    let padding: LocalizedPadding
    padding = {
      start: LengthMetrics.vp(this.theme.button.margin.start?.value as number / 2),
      end: LengthMetrics.vp(this.theme.closeButton.margin.end?.value as number)
    }
    return padding
  }

  private getMessageMaxWeight(messageMaxWidth ?: number): number | undefined {
    let textMaxWeight: number = 0;
    let defaultDisplaySync: display.Display | undefined = undefined;
    let defaultDisplaySyncWidth: number = 0;
    try {
      defaultDisplaySync = display.getDefaultDisplaySync()
      defaultDisplaySyncWidth = defaultDisplaySync.width;
    } catch (error) {
      console.error(`Ace PopupV2 getDefaultDisplaySync, error: ${error.toString()}`);
      return textMaxWeight = 400
    }
    if (this.showClose || this.showClose === undefined) {
      if (messageMaxWidth != undefined) {
        if (this.maxWidth != undefined &&
          this.toVp(this.maxWidth) > this.getUIContext().px2vp(defaultDisplaySyncWidth)) {
          textMaxWeight = this.getUIContext().px2vp(defaultDisplaySyncWidth)
        } else {
          textMaxWeight = messageMaxWidth as number
        }
      } else {
        if (defaultDisplaySyncWidth != 0) {
          textMaxWeight = this.getUIContext().px2vp(defaultDisplaySyncWidth)
        } else {
          // The previewer does not support the display interface to use abnormal values
          textMaxWeight = -1
        }
      }
      textMaxWeight -= (this.theme.windows.padding.start?.value as number -
        (this.theme.button.margin.end?.value as number / 2))
      textMaxWeight -= this.theme.windows.padding.end?.value as number
      textMaxWeight -= this.theme.button.margin.start?.value as number / 2
      textMaxWeight -= this.theme.closeButton.margin.end?.value as number
      textMaxWeight -= this.getCloseButtonWidth() as number
    }
    return textMaxWeight
  }

  private getMessageFontWeight(): Int | FontWeight | string | undefined {
    return this.theme.message.fontWeight
  }

  private getButtonMargin(): LocalizedMargin {
    return {
      top: LengthMetrics.vp(this.theme.button.textMargin.top?.value as number / 2 - 4),
      bottom: LengthMetrics.vp(this.theme.button.textMargin.bottom?.value as number / 2 - 4),
      start: LengthMetrics.vp(this.theme.button.margin.start?.value as number / 2 - 4),
      end: LengthMetrics.vp(this.theme.button.margin.end?.value as number / 2 - 4)
    }
  }

  private getButtonTextMargin(): LocalizedMargin {
    return { top: LengthMetrics.vp(this.theme.button.textMargin.bottom?.value as number) }
  }

  private getButtonTextPadding(): LocalizedPadding {
    return this.theme.button.padding
  }

  private getButtonHoverColor(): ResourceColor {
    return this.theme.button.hoverColor
  }

  private getButtonBackgroundColor(): ResourceColor {
    return this.theme.button.backgroundColor
  }

  private getFirstButtonText(): string | Resource | undefined {
    return this.buttons?.[0]?.text
  }

  private getSecondButtonText(): string | Resource | undefined {
    return this.buttons?.[1]?.text
  }

  private getFirstButtonFontSize(): number | string | Resource {
    return this.theme.button.fontSize
  }

  private getSecondButtonFontSize(): number | string | Resource {
    return this.theme.button.fontSize
  }

  private getFirstButtonFontColor(): ResourceColor {
    return this.theme.button.fontColor
  }

  private getSecondButtonFontColor(): ResourceColor {
    return this.theme.button.fontColor
  }

  private getButtonMinFontSize(): Dimension {
    return this.theme.button.minFontSize
  }

  private getButtonFontWeight(): Int | FontWeight | string | undefined {
    return this.theme.button.fontWeight
  }

  private getBtnResponseRegion(actualWidth: number, actualHeight: number, minSizeVp: number): Rectangle | undefined {
    if (actualWidth === 0 || actualHeight === 0 || minSizeVp <= 0) {
      return {} as Rectangle;
    }

    let needExpandWidth = actualWidth === -1 ? false : (actualWidth < minSizeVp);
    let needExpandHeight = actualHeight < minSizeVp;

    if (!needExpandWidth && !needExpandHeight) {
      return {} as Rectangle;
    }

    let regionWidth = needExpandWidth ? minSizeVp : '100%';
    let regionHeight = needExpandHeight ? minSizeVp : '100%';
    let offsetX = needExpandWidth ? (minSizeVp - actualWidth) / 2 : 0;
    let offsetY = needExpandHeight ? (minSizeVp - actualHeight) / 2 : 0;

    return {
      x: -offsetX,
      y: -offsetY,
      width: regionWidth,
      height: regionHeight
    };
  }

  private getCloseBtnResponseRegion(): Rectangle | undefined {
    let responseRegionValue =   this.toVp(this.theme.closeButton.responseRegion);
    return this.getBtnResponseRegion(this.theme.closeButton.size.width as number,
      this.theme.closeButton.size.height as number, responseRegionValue)
  }

  private getNormalBtnResponseRegion(height: number): Rectangle | undefined {
    let responseRegionValue = this.toVp(this.theme.button.responseRegion);
    return this.getBtnResponseRegion(-1, height, responseRegionValue)
  }

  private getWindowsPadding(): LocalizedPadding {
    let top = this.theme.windows.padding.top;
    let bottom =
      LengthMetrics.vp(this.theme.windows.padding.bottom?.value as number -
        (this.theme.button.textMargin.bottom?.value as number / 2));
    let start = LengthMetrics.vp(this.theme.windows.padding.start?.value as number -
      (this.theme.button.margin.end?.value as number / 2));
    let end = this.theme.windows.padding.end;
    let resolvedMaxWidth = this.toVp(this.maxWidth);
    if (resolvedMaxWidth === 0) {
      start = LengthMetrics.vp(0);
      end = LengthMetrics.vp(0);
    }
    return {
      top: top,
      bottom: bottom,
      start: start,
      end: end
    };
  }

  @Builder
  closeButtonBuilderImage() {
    Image(this.showClose as Resource)
      .width(this.getCloseButtonWidth())
      .height(this.getCloseButtonHeight())
      .direction(this.popupDirection)
      .focusable(true)
      .draggable(false)
  }

  @Builder
  closeButtonBuilderSymbolGlyph(symbolGlyphModifier : SymbolGlyphModifier) {
    SymbolGlyph()
      .fontColor([this.getCloseButtonFillColor()])
      .fontSize(this.getCloseButtonSymbolSize())
      .direction(this.popupDirection)
      .attributeModifier(symbolGlyphModifier)
      .focusable(true)
      .draggable(false)
  }

  onWillApplyTheme(theme: Theme): void {
    this.theme.title.fontColor = theme.colors.fontPrimary;
    this.theme.button.fontColor = theme.colors.fontEmphasize;
    this.theme.message.fontColor = theme.colors.fontSecondary;
    this.theme.message.plainFontColor = theme.colors.fontPrimary;
    this.closeButtonFillColorWithTheme = theme.colors.iconSecondary;
  }

  aboutToAppear() {
    this.listener?.onChange((mediaQueryResult) => {
      setTimeout(() => {
        this.currentScreenStatus = mediaQueryResult?.matches as boolean
      }, 10)
    })
  }

  aboutToDisappear() {
    this.listener?.offChange();
  }

  getScrollMaxHeight(): number | undefined {
    let scrollMaxHeight: number = 0;
    if (this.beforeScreenStatus === undefined ||
      this.currentScreenStatus !== this.beforeScreenStatus) {
      this.applySizeOptions = this.getApplyMaxSize();
      this.beforeScreenStatus = this.currentScreenStatus
    }

    scrollMaxHeight = this.getUIContext()
      .px2vp(this.getUIContext().getComponentUtils().getRectangleById(this.applyContentKey)?.size?.height as number)
    scrollMaxHeight -= this.titleHeight
    scrollMaxHeight -= this.buttonHeight
    scrollMaxHeight -= this.theme.windows.padding.top?.value as number
    scrollMaxHeight -= (this.theme.button.textMargin.bottom?.value as number / 2)
    scrollMaxHeight -= this.theme.title.margin.bottom?.value as number
    scrollMaxHeight -= (this.theme.windows.padding.bottom?.value as number -
      (this.theme.button.textMargin.bottom?.value as number / 2))
    if (Math.floor(this.textHeight) > Math.floor(scrollMaxHeight + 1)) {
      return scrollMaxHeight
    } else {
      return undefined
    }
  }

  private getLayoutWeight(): number {
    let layoutWeight: number
    if ((this.icon !== '' && this.icon !== undefined) ||
      (this.title !== '' && this.title !== undefined) ||
      (this.buttons?.[0]?.text !== '' && this.buttons?.[0]?.text !== undefined) ||
      (this.buttons?.[1]?.text !== '' && this.buttons?.[1]?.text !== undefined)) {
      layoutWeight = 1
    } else {
      layoutWeight = 0
    }
    return layoutWeight
  }

  private resourceToVp(value: Resource): number {
    try {
      if ((value as Resource).id !== -1) {
        if ((value?.type?.toInt()) === RESOURCE_TYPE_FLOAT) {
          return this.getUIContext()
            .px2vp(this.getUIContext().getHostContext()?.resourceManager?.getDouble((value as Resource).id) as number);
        }
        if ((value?.type?.toInt()) === RESOURCE_TYPE_INTEGER) {
          return this.getUIContext().px2vp(
            Number(
              this.getUIContext().getHostContext()?.resourceManager?.getInt((value as Resource).id) as int
            ) as number
          )
        }
        return POPUP_DEFAULT_MAXWIDTH
      } else {
        let valueParams: Array<string> = [] as Array<string>;
        if (value.params) {
          (value.params ?? [] as Array<String | Int | Long | Double | Resource>).forEach(
            (item: String | Int | Long | Double | Resource) => {
              if (typeof item === 'string') {
                valueParams.push(item as string);
              }
            });
        }
        return this.getUIContext().px2vp(this.getUIContext().getHostContext()?.resourceManager?.getDoubleByName(
          ((valueParams)[0] as string).split('.')[2] as string) as number
        );
      }
    } catch (error) {
      return POPUP_DEFAULT_MAXWIDTH
    }
  }

  private toVp(value: Dimension | Length | undefined): number {
    let defaultDisplaySync: display.Display | undefined = undefined;
    let defaultDisplaySyncWidth: number = 0;
    try {
      defaultDisplaySync = display.getDefaultDisplaySync()
      defaultDisplaySyncWidth = defaultDisplaySync.width
    } catch (error) {
      console.error(`Ace PopupV2 getDefaultDisplaySync, error: ${error.toString()}`);
      return Number.NEGATIVE_INFINITY;
    }
    if (value === undefined) {
      return Number.NEGATIVE_INFINITY
    }
    switch (typeof (value)) {
      case 'number':
        return value as number
      case 'object':
        try {
          let returnValue = this.resourceToVp(value as Resource);
          if (returnValue === 0 && !isValidResource(this.getUIContext().getHostContext(), value as Resource)
          ) {
            return Number.NEGATIVE_INFINITY;
          }
          return returnValue;
        } catch (error) {
          return Number.NEGATIVE_INFINITY
        }
      case 'string':
        let regex: RegExp = new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$', 'i');
        let matches: RegExpMatchArray | null = (value as string).match(regex) as RegExpMatchArray;
        if (!matches) {
          return Number.NEGATIVE_INFINITY
        }
        let length: number = Number((matches?.[1] as string) ?? '0');
        let unit: string = matches?.[2] ?? 'vp'
        switch (unit.toLowerCase()) {
          case 'px':
            length = this.getUIContext().px2vp(length)
            break
          case 'fp':
            length = this.getUIContext().px2vp(this.getUIContext().fp2px(length))
            break
          case 'lpx':
            length = this.getUIContext().px2vp(this.getUIContext().lpx2px(length))
            break
          case '%':
            length = length / 100 * this.getUIContext().px2vp(defaultDisplaySyncWidth);
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

  private getApplyMaxSize(): ConstraintSizeOptions {
    let applyMaxWidth: number | undefined = undefined;
    let applyMaxHeight: number | undefined = undefined;
    let applyMaxSize: ConstraintSizeOptions | undefined = undefined;
    let defaultDisplaySync: display.Display | undefined = undefined;
    let maxWidthSize: number = 400;
    try {
      defaultDisplaySync = display.getDefaultDisplaySync()
    } catch (error) {
      console.error(`Ace PopupV2 getDefaultDisplaySync, error: ${error.toString()}`);
      this.messageMaxWeight = 400
      return applyMaxSize = { maxWidth: 400, maxHeight: 480 }
    }
    if (this.maxWidth !== undefined) {
      if (typeof this.maxWidth === 'number' && this.maxWidth as number >= 0) {
        maxWidthSize = this.maxWidth as number;
      } else if (typeof this.maxWidth === 'number' && 0 > this.maxWidth as number) {
        maxWidthSize = POPUP_DEFAULT_MAXWIDTH
      } else {
        maxWidthSize = this.toVp(this.maxWidth);
      }
    }
    if (this.getUIContext().px2vp(defaultDisplaySync?.width as Long) > maxWidthSize) {
      applyMaxWidth = maxWidthSize
    } else {
      if (defaultDisplaySync?.width != 0) {
        applyMaxWidth = this.getUIContext().px2vp(defaultDisplaySync?.width as Long)
      } else {
        // The previewer does not support the display interface to use abnormal values
        applyMaxWidth = -1
      }
    }
    if (this.getUIContext().px2vp(defaultDisplaySync?.height as Long) > 480) {
      applyMaxHeight = 480
    } else {
      applyMaxHeight = this.getUIContext().px2vp(defaultDisplaySync?.height as Long) - 40 - 40
    }
    applyMaxSize = { maxWidth: applyMaxWidth, maxHeight: applyMaxHeight }
    this.messageMaxWidth = applyMaxWidth;
    this.messageMaxWeight = this.getMessageMaxWeight(applyMaxWidth)
    return applyMaxSize
  }

  private getTitleTextAlign(): TextAlign {
    let titleAlign = TextAlign.Start;
    try {
      let systemLanguage: string = I18n.System.getSystemLanguage();
      if (I18n.isRTL(systemLanguage) &&
        (this.popupDirection === Direction.Auto || this.popupDirection === undefined)) {
        titleAlign = TextAlign.End;
      }
    } catch (error) {
      console.error(`popup getSystemLanguage, error: ${error.toString()}`);
    }
    return titleAlign
  }

  build() {
    Row() {
      if (this.icon !== '' && this.icon !== undefined) {
        Image(this.getIconImage())
          .direction(this.popupDirection)
          .width(this.getIconWidth())
          .height(this.getIconHeight())
          .margin(this.getIconMargin())
          .fillColor(this.getIconFillColor())
          .borderRadius(this.getIconBorderRadius())
          .draggable(false)
          .attributeModifier(this.iconModifier)
      }
      if (this.title !== '' && this.title !== undefined) {
        Column() {
          Flex({ alignItems: ItemAlign.Start }) {
            Text(this.getTitleText())
              .direction(this.popupDirection)
              .flexGrow(1)
              .maxLines(2)
              .align(Alignment.Start)
              .padding(this.getTitlePadding())
              .minFontSize(this.getTitleMinFontSize())
              .textOverflow({ overflow: TextOverflow.Ellipsis })
              .fontWeight(this.getTitleFontWeight())
              .fontSize(this.getTitleFontSize())
              .fontColor(this.getTitleFontColor())
              .constraintSize({ minHeight: this.getCloseButtonHeight() })
              .textAlign(this.getTitleTextAlign())
              .attributeModifier(this.titleModifier)
            if (this.showClose || this.showClose === undefined) {
              Button() {
                if (typeof this.showClose === 'object' &&
                  ((this.showClose as Resource).type === RESOURCE_TYPE_MEDIA ||
                    (this.showClose as Resource).type === RESOURCE_TYPE_RAWFILE)) {
                  this.closeButtonBuilderImage()
                } else if (typeof this.showClose === 'object' &&
                  ((this.showClose as Resource).type === RESOURCE_TYPE_SYMBOL)) {
                  this.closeButtonBuilderSymbolGlyph(new SymbolGlyphModifier(this.showClose as Resource));
                } else {
                  this.closeButtonBuilderSymbolGlyph(this.theme.closeButton.symbolStyle)
                }
              }
              .direction(this.popupDirection)
              .width(this.getCloseButtonWidth())
              .height(this.getCloseButtonHeight())
              .padding(this.getCloseButtonPadding())
              .backgroundColor(this.closeButtonBackgroundColor)
              .flexShrink(0)
              .accessibilityText(this.theme.closeButton.accessibilityMessage)
              .responseRegion(this.getCloseBtnResponseRegion() as Rectangle)
              .onHover((isHover: boolean) => {
                if (isHover) {
                  this.closeButtonBackgroundColor = this.getCloseButtonHoverColor()
                } else {
                  this.closeButtonBackgroundColor = this.getCloseButtonBackgroundColor()
                }
              })
              .onClick(() => {
                if (this.onClose) {
                  this.onClose();
                }
              })
            }
          }
          .direction(this.popupDirection)
          .width('100%')
          .margin(this.getTitleMargin())
          .onAreaChange((_, rect) => {
            this.titleHeight = rect.height as number
          })

          Scroll() {
            Text(this.getMessageText())
              .textAlign(this.getTitleTextAlign())
              .direction(this.popupDirection)
              .fontSize(this.getMessageFontSize())
              .fontColor(this.getMessageFontColor())
              .fontWeight(this.getMessageFontWeight())
              .constraintSize({ minHeight: this.getCloseButtonHeight() })
              .attributeModifier(this.messageModifier)
              .onAreaChange((_, rect) => {
                this.textHeight = rect.height as number
              })
          }
          .direction(this.popupDirection)
          .width('100%')
          .align(Alignment.TopStart)
          .padding(this.getMessagePadding())
          .scrollBar(BarState.Auto)
          .scrollable(ScrollDirection.Vertical)
          .constraintSize({ maxHeight: this.getScrollMaxHeight() })
          .edgeEffect(EdgeEffect.Spring, { alwaysEnabled: false })

          Flex({ wrap: FlexWrap.Wrap }) {
            if (this.buttons?.[0]?.text !== '' && this.buttons?.[0]?.text !== undefined) {
              Button() {
                Text(this.getFirstButtonText())
                  .direction(this.popupDirection)
                  .maxLines(2)
                  .focusable(true)
                  .fontSize(this.getFirstButtonFontSize())
                  .fontColor(this.getFirstButtonFontColor())
                  .fontWeight(this.getButtonFontWeight())
                  .minFontSize(this.getButtonMinFontSize())
                  .textOverflow({ overflow: TextOverflow.Ellipsis })
                  .attributeModifier(this.buttons?.[0]?.buttonTextModifier)
              }
              .type(ButtonType.Normal)
              .borderRadius($r('sys.float.popup_button_border_radius'))
              .direction(this.popupDirection)
              .margin(this.getButtonMargin())
              .padding(this.getButtonTextPadding())
              .backgroundColor(this.firstButtonBackgroundColor)
              .onHover((isHover: boolean) => {
                if (isHover) {
                  this.firstButtonBackgroundColor = this.getButtonHoverColor()
                } else {
                  this.firstButtonBackgroundColor = this.getButtonBackgroundColor()
                }
              })
              .onClick(this.buttons?.[0]?.action)
              .onAreaChange((_, rect) => {
                this.firstButtonHeight = rect.height as number;
              })
              .responseRegion(this.getNormalBtnResponseRegion(this.firstButtonHeight))
            }

            if (this.buttons?.[1]?.text !== '' && this.buttons?.[1]?.text !== undefined) {
              Button() {
                Text(this.getSecondButtonText())
                  .direction(this.popupDirection)
                  .maxLines(2)
                  .focusable(true)
                  .fontSize(this.getSecondButtonFontSize())
                  .fontColor(this.getSecondButtonFontColor())
                  .fontWeight(this.getButtonFontWeight())
                  .minFontSize(this.getButtonMinFontSize())
                  .textOverflow({ overflow: TextOverflow.Ellipsis })
                  .attributeModifier(this.buttons?.[1]?.buttonTextModifier)
              }
              .type(ButtonType.Normal)
              .borderRadius($r('sys.float.popup_button_border_radius'))
              .direction(this.popupDirection)
              .margin(this.getButtonMargin())
              .padding(this.getButtonTextPadding())
              .backgroundColor(this.secondButtonBackgroundColor)
              .onHover((isHover: boolean) => {
                if (isHover) {
                  this.secondButtonBackgroundColor = this.getButtonHoverColor()
                } else {
                  this.secondButtonBackgroundColor = this.getButtonBackgroundColor()
                }
              })
              .onClick(this.buttons?.[1]?.action)
              .onAreaChange((_, rect) => {
                this.secondButtonHeight = rect.height as number;
              })
              .responseRegion(this.getNormalBtnResponseRegion(this.secondButtonHeight))
            }
          }
          .direction(this.popupDirection)
          .margin(this.getButtonTextMargin())
          .flexGrow(1)
          .onAreaChange((_, rect) => {
            if ((this.buttons?.[0]?.text !== '' && this.buttons?.[0]?.text !== undefined) ||
              (this.buttons?.[1]?.text !== '' && this.buttons?.[1]?.text !== undefined)) {
              this.buttonHeight = rect.height as number
            } else {
              this.buttonHeight = 0
            }
          })
        }
        .direction(this.popupDirection)
        .layoutWeight(this.getLayoutWeight())
      } else {
        Column() {
          Flex().height(0).onAreaChange((_, rect) => {
            this.titleHeight = rect.height as number
          })
          Row() {
            Scroll() {
              Text(this.getMessageText())
                .textAlign(this.getTitleTextAlign())
                .direction(this.popupDirection)
                .fontSize(this.getMessageFontSize())
                .fontColor(this.getMessageFontColor())
                .fontWeight(this.getMessageFontWeight())
                .constraintSize({ maxWidth: this.messageMaxWeight, minHeight: this.getCloseButtonHeight() })
                .attributeModifier(this.messageModifier)
                .onAreaChange((_, rect) => {
                  this.textHeight = rect.height as number
                })
            }
            .direction(this.popupDirection)
            .layoutWeight(this.getLayoutWeight())
            .edgeEffect(EdgeEffect.Spring, { alwaysEnabled: false })
            .align(Alignment.TopStart)
            .padding(this.getMessagePadding())
            .scrollBar(BarState.Auto)
            .scrollable(ScrollDirection.Vertical)
            .constraintSize({ maxHeight: this.getScrollMaxHeight() })

            if (this.showClose || this.showClose === undefined) {
              Button() {
                if (typeof this.showClose === 'object' &&
                  ((this.showClose as Resource).type === RESOURCE_TYPE_MEDIA ||
                    (this.showClose as Resource).type === RESOURCE_TYPE_RAWFILE)) {
                  this.closeButtonBuilderImage()
                } else if (typeof this.showClose === 'object' &&
                  ((this.showClose as Resource).type === RESOURCE_TYPE_SYMBOL)) {
                  this.closeButtonBuilderSymbolGlyph(new SymbolGlyphModifier(this.showClose as Resource));
                } else {
                  this.closeButtonBuilderSymbolGlyph(this.theme.closeButton.symbolStyle)
                }
              }
              .direction(this.popupDirection)
              .width(this.getCloseButtonWidth())
              .height(this.getCloseButtonHeight())
              .padding(this.getCloseButtonPadding())
              .backgroundColor(this.closeButtonBackgroundColor)
              .flexShrink(0)
              .accessibilityText(this.theme.closeButton.accessibilityMessage)
              .responseRegion(this.getCloseBtnResponseRegion())
              .onHover((isHover: boolean) => {
                if (isHover) {
                  this.closeButtonBackgroundColor = this.getCloseButtonHoverColor()
                } else {
                  this.closeButtonBackgroundColor = this.getCloseButtonBackgroundColor()
                }
              })
              .onClick(() => {
                if (this.onClose) {
                  this.onClose();
                }
              })
            }
          }
          .direction(this.popupDirection)
          .alignItems(VerticalAlign.Top)

          Flex({ wrap: FlexWrap.Wrap }) {
            if (this.buttons?.[0]?.text !== '' && this.buttons?.[0]?.text !== undefined) {
              Button() {
                Text(this.getFirstButtonText())
                  .direction(this.popupDirection)
                  .maxLines(2)
                  .focusable(true)
                  .fontSize(this.getFirstButtonFontSize())
                  .fontColor(this.getFirstButtonFontColor())
                  .fontWeight(this.getButtonFontWeight())
                  .minFontSize(this.getButtonMinFontSize())
                  .textOverflow({ overflow: TextOverflow.Ellipsis })
                  .attributeModifier(this.buttons?.[0]?.buttonTextModifier)
              }
              .type(ButtonType.Normal)
              .borderRadius($r('sys.float.popup_button_border_radius'))
              .direction(this.popupDirection)
              .margin(this.getButtonMargin())
              .padding(this.getButtonTextPadding())
              .backgroundColor(this.firstButtonBackgroundColor)
              .onHover((isHover: boolean) => {
                if (isHover) {
                  this.firstButtonBackgroundColor = this.getButtonHoverColor()
                } else {
                  this.firstButtonBackgroundColor = this.getButtonBackgroundColor()
                }
              })
              .onClick(this.buttons?.[0]?.action)
              .onAreaChange((_, rect) => {
                this.firstButtonHeight = rect.height as number;
              })
              .responseRegion(this.getNormalBtnResponseRegion(this.firstButtonHeight))
            }
            if (this.buttons?.[1]?.text !== '' && this.buttons?.[1]?.text !== undefined) {
              Button() {
                Text(this.getSecondButtonText())
                  .direction(this.popupDirection)
                  .maxLines(2)
                  .focusable(true)
                  .fontSize(this.getSecondButtonFontSize())
                  .fontColor(this.getSecondButtonFontColor())
                  .fontWeight(this.getButtonFontWeight())
                  .minFontSize(this.getButtonMinFontSize())
                  .textOverflow({ overflow: TextOverflow.Ellipsis })
                  .attributeModifier(this.buttons?.[1]?.buttonTextModifier)
              }
              .type(ButtonType.Normal)
              .borderRadius($r('sys.float.popup_button_border_radius'))
              .direction(this.popupDirection)
              .margin(this.getButtonMargin())
              .padding(this.getButtonTextPadding())
              .backgroundColor(this.secondButtonBackgroundColor)
              .onHover((isHover: boolean) => {
                if (isHover) {
                  this.secondButtonBackgroundColor = this.getButtonHoverColor()
                } else {
                  this.secondButtonBackgroundColor = this.getButtonBackgroundColor()
                }
              })
              .onClick(this.buttons?.[1]?.action)
              .onAreaChange((_, rect) => {
                this.secondButtonHeight = rect.height as number;
              })
              .responseRegion(this.getNormalBtnResponseRegion(this.secondButtonHeight))
            }
          }
          .direction(this.popupDirection)
          .margin(this.getButtonTextMargin())
          .flexGrow(1)
          .onAreaChange((_, rect) => {
            if ((this.buttons?.[0]?.text !== '' && this.buttons?.[0]?.text !== undefined) ||
              (this.buttons?.[1]?.text !== '' && this.buttons?.[1]?.text !== undefined)) {
              this.buttonHeight = rect.height as number
            } else {
              this.buttonHeight = 0
            }
          })
        }
        .direction(this.popupDirection)
        .layoutWeight(this.getLayoutWeight())
      }
    }
    .direction(this.popupDirection)
    .alignItems(VerticalAlign.Top)
    .padding(this.getWindowsPadding())
    .constraintSize(this.getApplyMaxSize())
    .key(this.applyContentKey)
    .onAreaChange((_, rect) => {
      this.applyHeight = rect.height as number
    })
  }
}
