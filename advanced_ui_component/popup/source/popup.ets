/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
import mediaquery from '@ohos.mediaquery';
import { Theme } from '@ohos.arkui.theme';
import { LengthMetrics } from '@ohos.arkui.node'

interface IconTheme {
  size: SizeOptions;
  margin: LocalizedMargin;
  fillColor: ResourceColor;
  borderRadius: Length;
}

interface TitleTheme {
  margin: LocalizedMargin;
  minFontSize: number;
  fontWeight: FontWeight;
  fontSize: Resource;
  fontColor: ResourceColor;
}

interface ButtonTheme {
  margin: LocalizedMargin;
  padding: LocalizedPadding;
  fontSize: Resource;
  fontColor: ResourceColor;
  textMargin: LocalizedMargin;
  minFontSize: number;
  fontWeight: FontWeight;
  hoverColor: ResourceColor;
  backgroundColor: ResourceColor;
}

interface MessageTheme {
  fontSize: Resource;
  fontColor: ResourceColor;
  fontWeight: FontWeight;
  plainFontColor: ResourceColor;
}

interface CloseButtonTheme {
  size: SizeOptions;
  image: ResourceStr;
  imageSize: SizeOptions;
  margin: LocalizedMargin;
  padding: LocalizedPadding;
  fillColor: ResourceColor;
  hoverColor: ResourceColor;
  backgroundColor: ResourceColor;
}

interface WindowsTheme {
  padding: LocalizedPadding;
}

interface PopupTheme {
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
    backgroundColor: $r('sys.color.ohos_id_color_background_transparent')
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
    imageSize: { width: 18, height: 18 },
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
    image: $r('sys.media.ohos_ic_public_cancel'),
    fillColor: $r('sys.color.icon_secondary'),
    hoverColor: $r('sys.color.ohos_id_color_hover'),
    backgroundColor: $r('sys.color.ohos_id_color_background_transparent')
  },
};

export interface PopupTextOptions {
  text: ResourceStr;
  fontSize?: number | string | Resource;
  fontColor?: ResourceColor;
  fontWeight?: number | FontWeight | string;
}

export interface PopupButtonOptions {
  text: ResourceStr;
  action?: () => void;
  fontSize?: number | string | Resource;
  fontColor?: ResourceColor;
}

export interface PopupIconOptions {
  image: ResourceStr;
  width?: Dimension;
  height?: Dimension;
  fillColor?: ResourceColor;
  borderRadius?: Length | BorderRadiuses;
}

export interface PopupOptions {
  icon?: PopupIconOptions;
  title?: PopupTextOptions;
  message: PopupTextOptions;
  direction?: Direction;
  showClose?: boolean | Resource;
  onClose?: () => void;
  buttons?: [PopupButtonOptions?, PopupButtonOptions?];
  maxWidth?:Dimension;
}

const noop = () => {
};

const POPUP_DEFAULT_MAXWIDTH = 400;

@Builder
export function Popup(options: PopupOptions) {
  PopupComponent({
    icon: options.icon,
    title: options.title,
    message: options.message,
    popupDirection: options.direction,
    showClose: options.showClose,
    onClose: options.onClose,
    buttons: options.buttons,
    maxWidth: options.maxWidth
  })
}

@Component
export struct PopupComponent {
  private onClose: () => void = noop;
  private theme: PopupTheme = defaultTheme;
  @Prop icon: PopupIconOptions = { image: '' };
  @Prop maxWidth?: Dimension;
  @Prop title: PopupTextOptions = { text: '' };
  @Prop message: PopupTextOptions = { text: '' };
  @Prop popupDirection: Direction = Direction.Auto;
  @Prop showClose: boolean | Resource = true;
  @Prop buttons: [PopupButtonOptions?, PopupButtonOptions?] = [{ text: '' }, { text: '' }];
  textHeight: number = 0;
  @State titleHeight: number = 0;
  @State applyHeight: number = 0;
  @State buttonHeight: number = 0;
  @State messageMaxWeight: number | undefined = 0;
  @State beforeScreenStatus: boolean | undefined = undefined;
  @State currentScreenStatus: boolean = true;
  @State applySizeOptions: ConstraintSizeOptions | undefined = undefined;
  @State closeButtonBackgroundColor: ResourceColor = $r('sys.color.ohos_id_color_background_transparent');
  @State firstButtonBackgroundColor: ResourceColor = $r('sys.color.ohos_id_color_background_transparent');
  @State secondButtonBackgroundColor: ResourceColor = $r('sys.color.ohos_id_color_background_transparent');
  @State closeButtonFillColorWithTheme: ResourceColor = $r('sys.color.icon_secondary');
  private listener = mediaquery.matchMediaSync('(orientation: landscape)')

  private getIconWidth(): Dimension {
    return this.icon?.width ?? this.theme.icon.size.width as number
  }

  private getIconHeight(): Dimension {
    return this.icon?.height ?? this.theme.icon.size.height as number
  }

  private getIconFillColor(): ResourceColor {
    return this.icon?.fillColor ?? this.theme.icon.fillColor
  }

  private getIconBorderRadius(): Length | BorderRadiuses {
    return this.icon?.borderRadius ?? this.theme.icon.borderRadius
  }

  private getIconMargin(): LocalizedMargin {
    return {
      start: new LengthMetrics(this.theme.button.margin.start.value / 2, this.theme.button.margin.start.unit),
      end: new LengthMetrics(this.theme.icon.margin.start.value - (this.theme.button.margin.end.value / 2)
        , this.theme.button.margin.start.unit)
    }
  }

  private getIconImage(): ResourceStr | undefined {
    return this.icon?.image
  }

  private getTitleText(): ResourceStr | undefined {
    return this.title?.text
  }

  private getTitlePadding(): LocalizedPadding {
    return {
      start: new LengthMetrics(this.theme.button.margin.start.value / 2, this.theme.button.margin.start.unit),
      end: this.theme.closeButton.margin.end
    }
  }

  private getTitleMargin(): LocalizedMargin {
    return this.theme.title.margin
  }

  private getTitleMinFontSize(): number | string | Resource {
    return this.theme.title.minFontSize
  }

  private getTitleFontWeight(): number | FontWeight | string {
    return this.title?.fontWeight ?? this.theme.title.fontWeight
  }

  private getTitleFontSize(): number | string | Resource {
    return this.title?.fontSize ?? this.theme.title.fontSize
  }

  private getTitleFontColor(): ResourceColor {
    return this.title?.fontColor ?? this.theme.title.fontColor
  }

  private getCloseButtonWidth(): Length | undefined {
    return this.theme.closeButton.size.width
  }

  private getCloseButtonHeight(): Length | undefined {
    return this.theme.closeButton.size.height
  }

  private getCloseButtonImage(): ResourceStr {
    return this.theme.closeButton.image
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

  private getCloseButtonImageWidth(): Length | undefined {
    return this.theme.closeButton.imageSize.width
  }

  private getCloseButtonImageHeight(): Length | undefined {
    return this.theme.closeButton.imageSize.height
  }

  private getMessageText(): string | Resource {
    return this.message.text
  }

  private getMessageFontSize(): number | string | Resource {
    return this.message.fontSize ?? this.theme.message.fontSize
  }

  private getMessageFontColor(): ResourceColor {
    let fontColor: ResourceColor
    if (this.message.fontColor) {
      fontColor = this.message.fontColor
    } else {
      if (this.title.text !== '' && this.title.text !== void (0)) {
        fontColor = this.theme.message.fontColor
      } else {
        fontColor = this.theme.message.plainFontColor
      }
    }
    return fontColor
  }

  private getMessagePadding(): LocalizedPadding {
    let padding: LocalizedPadding
    if (this.title.text !== '' && this.title.text !== void (0)) {
      padding = { start: LengthMetrics.vp(this.theme.button.margin.start.value / 2) }
    } else {
      padding = {
        start: LengthMetrics.vp(this.theme.button.margin.start.value / 2),
        end: LengthMetrics.vp(this.theme.closeButton.margin.end.value)
      }
    }
    return padding
  }

  private getMessageMaxWeight(): number | undefined {
    let textMaxWeight: number | undefined = undefined;
    let defaultDisplaySync: display.Display | undefined = undefined;
    try {
      defaultDisplaySync = display.getDefaultDisplaySync()
    } catch (error) {
      console.error(`Ace Popup getDefaultDisplaySync, error: ${error.toString()}`);
      return textMaxWeight = 400
    }
    if (this.showClose || this.showClose === void (0)) {
      if (this.messageMaxWidth != undefined) {
        if(this.maxWidth > px2vp(defaultDisplaySync.width)) {
          textMaxWeight = px2vp(defaultDisplaySync.width)
        } else {
          textMaxWeight = this.messageMaxWidth
        }
      } else {
        if (defaultDisplaySync.width != 0) {
          textMaxWeight = px2vp(defaultDisplaySync.width)
        } else {
          // The previewer does not support the display interface to use abnormal values
          textMaxWeight = -1
        }
      }
      textMaxWeight -= (this.theme.windows.padding.start.value - (this.theme.button.margin.end.value / 2))
      textMaxWeight -= this.theme.windows.padding.end.value
      textMaxWeight -= this.theme.button.margin.start.value / 2
      textMaxWeight -= this.getCloseButtonWidth() as number
    }
    return textMaxWeight
  }

  private getMessageFontWeight(): number | FontWeight | string {
    return this.theme.message.fontWeight
  }

  private getButtonMargin(): LocalizedMargin {
    return {
      top: LengthMetrics.vp(this.theme.button.textMargin.top.value / 2 - 4),
      bottom: LengthMetrics.vp(this.theme.button.textMargin.bottom.value / 2 - 4),
      start: LengthMetrics.vp(this.theme.button.margin.start.value / 2 - 4),
      end: LengthMetrics.vp(this.theme.button.margin.end.value / 2 - 4)
    }
  }

  private getButtonTextMargin(): LocalizedMargin {
    return { top: LengthMetrics.vp(this.theme.button.textMargin.bottom.value) }
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
    return this.buttons?.[0]?.fontSize ?? this.theme.button.fontSize
  }

  private getSecondButtonFontSize(): number | string | Resource {
    return this.buttons?.[1]?.fontSize ?? this.theme.button.fontSize
  }

  private getFirstButtonFontColor(): ResourceColor {
    return this.buttons?.[0]?.fontColor ?? this.theme.button.fontColor
  }

  private getSecondButtonFontColor(): ResourceColor {
    return this.buttons?.[1]?.fontColor ?? this.theme.button.fontColor
  }

  private getButtonMinFontSize(): Dimension {
    return this.theme.button.minFontSize
  }

  private getButtonFontWeight(): number | FontWeight | string {
    return this.theme.button.fontWeight
  }

  private getWindowsPadding(): LocalizedPadding {
    let top = this.theme.windows.padding.top;
    let bottom = LengthMetrics.vp(this.theme.windows.padding.bottom.value - (this.theme.button.textMargin.bottom.value / 2));
    let start = LengthMetrics.vp(this.theme.windows.padding.start.value - (this.theme.button.margin.end.value / 2));
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

  onWillApplyTheme(theme: Theme): void {
    this.theme.title.fontColor = theme.colors.fontPrimary;
    this.theme.button.fontColor = theme.colors.fontEmphasize;
    this.theme.message.fontColor = theme.colors.fontSecondary;
    this.theme.message.plainFontColor = theme.colors.fontPrimary;
    this.closeButtonFillColorWithTheme = theme.colors.iconSecondary;
  }

  aboutToAppear() {
    this.listener.on("change", (mediaQueryResult: mediaquery.MediaQueryResult) => {
      this.currentScreenStatus = mediaQueryResult.matches
    })
  }

  aboutToDisappear() {
    this.listener.off("change")
  }

  getScrollMaxHeight(): number | undefined {
    let scrollMaxHeight: number | undefined = undefined;
    if (this.currentScreenStatus !== this.beforeScreenStatus) {
      this.applySizeOptions = this.getApplyMaxSize();
      this.beforeScreenStatus = this.currentScreenStatus
      return scrollMaxHeight;
    }
    scrollMaxHeight = this.applyHeight
    scrollMaxHeight -= this.titleHeight
    scrollMaxHeight -= this.buttonHeight
    scrollMaxHeight -= this.theme.windows.padding.top.value
    scrollMaxHeight -= (this.theme.button.textMargin.bottom.value / 2)
    scrollMaxHeight -= this.theme.title.margin.bottom.value
    scrollMaxHeight -= (this.theme.windows.padding.bottom.value -
      (this.theme.button.textMargin.bottom.value / 2))
    if (Math.floor(this.textHeight) > Math.floor(scrollMaxHeight + 1)) {
      return scrollMaxHeight
    } else {
      scrollMaxHeight = undefined
      return scrollMaxHeight
    }
  }

  private getLayoutWeight(): number {
    let layoutWeight: number
    if ((this.icon.image !== '' && this.icon.image !== void (0)) ||
      (this.title.text !== '' && this.title.text !== void (0)) ||
      (this.buttons?.[0]?.text !== '' && this.buttons?.[0]?.text !== void (0)) ||
      (this.buttons?.[1]?.text !== '' && this.buttons?.[1]?.text !== void (0))) {
      layoutWeight = 1
    } else {
      layoutWeight = 0
    }
    return layoutWeight
  }
  private resourceToVp(value: Resource): number {
    try {
      if ((value as Resource).id !== -1) {
        return px2vp(getContext(this).resourceManager.getNumber((value as Resource).id))
      } else {
        return px2vp(getContext(this)
          .resourceManager
          .getNumberByName(((value.params as string[])[0]).split('.')[2]))
      }
    } catch (error) {
      return POPUP_DEFAULT_MAXWIDTH
    }
  }

  private toVp(value: Dimension | Length | undefined): number {
    let defaultDisplaySync: display.Display | undefined = undefined;
    if (value === void (0)) {
      return Number.NEGATIVE_INFINITY
    }
    switch (typeof (value)) {
      case 'number':
        return value as number
      case 'object':
        try {
          let returnValue = this.resourceToVp(value);
          if (returnValue === 0 &&
            !isValidResource(getContext(this), value)) {
            return Number.NEGATIVE_INFINITY;
          }
          return returnValue;
        } catch (error) {
          return Number.NEGATIVE_INFINITY
        }
      case 'string':
        let regex: RegExp = new RegExp('(-?\\d+(?:\\.\\d+)?)_?(fp|vp|px|lpx|%)?$', 'i');
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
            length = length / 100 * px2vp(defaultDisplaySync.width);
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
    let maxWidthSize = 400；
    try {
      defaultDisplaySync = display.getDefaultDisplaySync()
    } catch (error) {
      console.error(`Ace Popup getDefaultDisplaySync, error: ${error.toString()}`);
      this.messageMaxWeight = 400
      return applyMaxSize = { maxWidth: 400, maxHeight: 480 }
    }
    if (this.maxWidth !== undefined) {
      if (typeof this.maxWidth === 'number' && this.maxWidth >= 0) {
          maxWidthSize = px2vp(this.maxWidth);
      } else if (typeof this.maxWidth === 'number' && this.maxWidth < 0) {
         maxWidthSize = POPUP_DEFAULT_MAXWIDTH
      } else {
          maxWidthSize = this.toVp(this.maxWidth);
      }
    } 
    if (px2vp(defaultDisplaySync.width) > maxWidthSize) {
      applyMaxWidth = maxWidthSize
    } else {
      if (defaultDisplaySync.width != 0) {
        applyMaxWidth = px2vp(defaultDisplaySync.width)
      } else {
        // The previewer does not support the display interface to use abnormal values
       applyMaxWidth = -1
     }
    }
    if (px2vp(defaultDisplaySync.height) > 480) {
      applyMaxHeight = 480
    } else {
      applyMaxHeight = px2vp(defaultDisplaySync.height) - 40 - 40
    }
    applyMaxSize = { maxWidth: applyMaxWidth, maxHeight: applyMaxHeight }
    this.messageMaxWidth = applyMaxHeight;
    this.messageMaxWeight = this.getMessageMaxWeight()
    return applyMaxSize
  }

  build() {
    Row() {
      if (this.icon.image !== '' && this.icon.image !== void (0)) {
        Image(this.getIconImage())
          .direction(this.popupDirection)
          .width(this.getIconWidth())
          .height(this.getIconHeight())
          .margin(this.getIconMargin())
          .fillColor(this.getIconFillColor())
          .borderRadius(this.getIconBorderRadius())
          .draggable(false)
      }
      if (this.title.text !== '' && this.title.text !== void (0)) {
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
            if (this.showClose || this.showClose === void (0)) {
              Button() {
                Image(this.getCloseButtonImage())
                  .direction(this.popupDirection)
                  .focusable(true)
                  .width(this.getCloseButtonImageWidth())
                  .height(this.getCloseButtonImageHeight())
                  .fillColor(this.getCloseButtonFillColor())
                  .draggable(false)
              }
              .direction(this.popupDirection)
              .width(this.getCloseButtonWidth())
              .height(this.getCloseButtonHeight())
              .padding(this.getCloseButtonPadding())
              .backgroundColor(this.closeButtonBackgroundColor)
              .flexShrink(0)
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
          .width("100%")
          .margin(this.getTitleMargin())
          .onAreaChange((_, rect) => {
            this.titleHeight = rect.height as number
          })

          Scroll() {
            Text(this.getMessageText())
              .direction(this.popupDirection)
              .fontSize(this.getMessageFontSize())
              .fontColor(this.getMessageFontColor())
              .fontWeight(this.getMessageFontWeight())
              .constraintSize({ minHeight: this.getCloseButtonHeight() })
              .onAreaChange((_, rect) => {
                this.textHeight = rect.height as number
              })
          }
          .direction(this.popupDirection)
          .width("100%")
          .align(Alignment.TopStart)
          .padding(this.getMessagePadding())
          .scrollBar(BarState.Auto)
          .scrollable(ScrollDirection.Vertical)
          .constraintSize({ maxHeight: this.getScrollMaxHeight() })
          .edgeEffect(EdgeEffect.Spring)
          Flex({ wrap: FlexWrap.Wrap }) {
            if (this.buttons?.[0]?.text !== '' && this.buttons?.[0]?.text !== void (0)) {
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
              }
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
              .onClick(() => {
                if (this.buttons?.[0]?.action) {
                  this.buttons?.[0]?.action();
                }
              })
            }
            if (this.buttons?.[1]?.text !== '' && this.buttons?.[1]?.text !== void (0)) {
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
              }
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
              .onClick(() => {
                if (this.buttons?.[1]?.action) {
                  this.buttons?.[1]?.action();
                }
              })
            }
          }
          .direction(this.popupDirection)
          .margin(this.getButtonTextMargin())
          .flexGrow(1)
          .onAreaChange((_, rect) => {
            this.buttonHeight = rect.height as number
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
                .direction(this.popupDirection)
                .fontSize(this.getMessageFontSize())
                .fontColor(this.getMessageFontColor())
                .fontWeight(this.getMessageFontWeight())
                .constraintSize({ maxWidth: this.messageMaxWeight, minHeight: this.getCloseButtonHeight() })
                .onAreaChange((_, rect) => {
                  this.textHeight = rect.height as number
                })
            }
            .direction(this.popupDirection)
            .layoutWeight(this.getLayoutWeight())
            .edgeEffect(EdgeEffect.Spring)
            .align(Alignment.TopStart)
            .padding(this.getMessagePadding())
            .scrollBar(BarState.Auto)
            .scrollable(ScrollDirection.Vertical)
            .constraintSize({ maxHeight: this.getScrollMaxHeight() })

            if (this.showClose || this.showClose === void (0)) {
              Button() {
                Image(this.getCloseButtonImage())
                  .direction(this.popupDirection)
                  .focusable(true)
                  .width(this.getCloseButtonImageWidth())
                  .height(this.getCloseButtonImageHeight())
                  .fillColor(this.getCloseButtonFillColor())
              }
              .direction(this.popupDirection)
              .width(this.getCloseButtonWidth())
              .height(this.getCloseButtonHeight())
              .padding(this.getCloseButtonPadding())
              .backgroundColor(this.closeButtonBackgroundColor)
              .flexShrink(0)
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
            if (this.buttons?.[0]?.text !== '' && this.buttons?.[0]?.text !== void (0)) {
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
              }
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
              .onClick(() => {
                if (this.buttons?.[0]?.action) {
                  this.buttons?.[0]?.action();
                }
              })
            }
            if (this.buttons?.[1]?.text !== '' && this.buttons?.[1]?.text !== void (0)) {
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
              }
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
              .onClick(() => {
                if (this.buttons?.[1]?.action) {
                  this.buttons?.[1]?.action();
                }
              })
            }
          }
          .direction(this.popupDirection)
          .margin(this.getButtonTextMargin())
          .flexGrow(1)
          .onAreaChange((_, rect) => {
            this.buttonHeight = rect.height as number
          })
        }
        .direction(this.popupDirection)
        .layoutWeight(this.getLayoutWeight())
      }
    }
    .direction(this.popupDirection)
    .alignItems(VerticalAlign.Top)
    .padding(this.getWindowsPadding())
    .constraintSize(this.applySizeOptions)
    .constraintSize(this.getApplyMaxSize())
    .onAreaChange((_, rect) => {
      this.applyHeight = rect.height as number
    })
  }
}
