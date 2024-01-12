/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
import mediaquery from '@ohos.mediaquery'

interface IconTheme {
  size: SizeOptions;
  margin: Margin;
  fillColor: ResourceColor;
  borderRadius: Length;
}

interface TitleTheme {
  margin: Margin;
  minFontSize: number;
  fontWeight: FontWeight;
  fontSize: Resource;
  fontColor: ResourceColor;
}

interface ButtonTheme {
  margin: Margin;
  padding: Padding;
  fontSize: Resource;
  fontColor: ResourceColor;
  textMargin: Margin;
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
  margin: Margin;
  padding: Padding;
  fillColor: ResourceColor;
  hoverColor: ResourceColor;
  backgroundColor: ResourceColor;
}

interface WindowsTheme {
  padding: Padding;
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
    margin: { top: 12, bottom: 12, left: 12, right: 12 },
    fillColor: '',
    borderRadius: $r('sys.float.ohos_id_corner_radius_default_s')

  },
  title: {
    margin: { bottom: 2 },
    minFontSize: 12,
    fontWeight: FontWeight.Medium,
    fontSize: $r('sys.float.ohos_id_text_size_sub_title2'),
    fontColor: $r('sys.color.ohos_id_color_text_primary')
  },
  button: {
    margin: { top: 16, bottom: 16, left: 16, right: 16 },
    padding: { top: 4, bottom: 4, left: 4, right: 4 },
    fontSize: $r('sys.float.ohos_id_text_size_button2'),
    fontColor: $r('sys.color.ohos_id_color_text_primary_activated'),
    textMargin: { top: 8, bottom: 8, left: 8, right: 8 },
    minFontSize: 9,
    fontWeight: FontWeight.Medium,
    hoverColor: $r('sys.color.ohos_id_color_hover'),
    backgroundColor: $r('sys.color.ohos_id_color_background_transparent')
  },
  message: {
    fontSize: $r('sys.float.ohos_id_text_size_body2'),
    fontColor: $r('sys.color.ohos_id_color_text_secondary'),
    fontWeight: FontWeight.Regular,
    plainFontColor: $r('sys.color.ohos_id_color_text_primary')
  },
  windows: {
    padding: { top: 12, bottom: 12, left: 12, right: 12 },
  },
  closeButton: {
    size: { width: 22, height: 22 },
    imageSize: { width: 18, height: 18 },
    padding: { top: 2, bottom: 2, left: 2, right: 2 },
    margin: { top: 12, bottom: 12, left: 12, right: 12 },
    image: $r('sys.media.ohos_ic_public_cancel'),
    fillColor: $r('sys.color.ohos_id_color_secondary'),
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
  image: PixelMap | ResourceStr | DrawableDescriptor;
  width?: Dimension;
  height?: Dimension;
  fillColor?: ResourceColor;
  borderRadius?: Length | BorderRadiuses;
}

export interface PopupOptions {
  icon?: PopupIconOptions;
  title?: PopupTextOptions;
  message: PopupTextOptions;
  showClose?: boolean | Resource;
  onClose?: () => void;
  buttons?: [PopupButtonOptions?, PopupButtonOptions?];
}

const noop = () => {
};

@Builder
export function Popup(options: PopupOptions) {
  PopupComponent({
    icon: options.icon,
    title: options.title,
    message: options.message,
    showClose: options.showClose,
    onClose: options.onClose,
    buttons: options.buttons
  })
}

@Component
export struct PopupComponent {
  private theme: PopupTheme = defaultTheme;
  @Prop icon: PopupIconOptions = { image: '' };
  @Prop title: PopupTextOptions = { text: '' };
  @Prop message: PopupTextOptions = { text: '' };
  @Prop showClose: boolean | Resource = true;
  @Prop buttons: [PopupButtonOptions?, PopupButtonOptions?] = [{ text: '' }, { text: '' }];
  private onClose: () => void = noop;
  @State closeButtonBackgroundColor: ResourceColor = $r('sys.color.ohos_id_color_background_transparent');
  @State firstButtonBackgroundColor: ResourceColor = $r('sys.color.ohos_id_color_background_transparent');
  @State secondButtonBackgroundColor: ResourceColor = $r('sys.color.ohos_id_color_background_transparent');
  @State textHeight: number = 0;
  @State titleHeight: number = 0;
  @State applyHeight: number = 0;
  @State buttonHeight: number = 0;
  @State scrollHeight: number = 0;
  @State beforeScreenStatus: boolean = true;
  @State currentScreenStatus: boolean = true;
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

  private getIconMargin(): Margin {
    return { left: this.theme.button.margin.left as number / 2,
      right: this.theme.icon.margin.right as number - (this.theme.button.margin.right as number / 2) }
  }

  private getIconImage(): PixelMap | ResourceStr | DrawableDescriptor | undefined {
    return this.icon?.image
  }

  private getTitleText(): ResourceStr | undefined {
    return this.title?.text
  }

  private getTitlePadding(): Padding {
    return { left: this.theme.button.margin.left as number / 2, right: this.theme.closeButton.margin.right }
  }

  private getTitleMargin(): Margin {
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

  private getCloseButtonImage(): PixelMap | ResourceStr | DrawableDescriptor {
    return this.theme.closeButton.image
  }

  private getCloseButtonFillColor(): ResourceColor {
    return this.theme.closeButton.fillColor
  }

  private getCloseButtonHoverColor(): ResourceColor {
    return this.theme.closeButton.hoverColor
  }

  private getCloseButtonBackgroundColor(): ResourceColor {
    return this.theme.closeButton.backgroundColor
  }

  private getCloseButtonPadding(): Padding {
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

  private getMessagePadding(): Padding {
    let padding: Padding
    if (this.title.text !== '' && this.title.text !== void (0)) {
      padding = { left: this.theme.button.margin.left as number / 2 }
    }
    else {
      padding = { left: this.theme.button.margin.left as number / 2, right: this.theme.closeButton.margin.right }
    }
    return padding
  }

  private getMessageMaxWeight(): number {
    let textMaxWeight: number = undefined
    if (this.showClose || this.showClose === void (0)) {
      textMaxWeight = 400
      textMaxWeight -= (this.theme.windows.padding.left as number - (this.theme.button.margin.right as number / 2))
      textMaxWeight -= this.theme.windows.padding.right as number
      textMaxWeight -= this.theme.button.margin.left as number / 2
      textMaxWeight -= this.getCloseButtonWidth() as number
    }
    return textMaxWeight
  }

  private getMessageFontWeight(): number | FontWeight | string {
    return this.theme.message.fontWeight
  }

  private getButtonMargin(): Margin {
    return { top: this.theme.button.textMargin.top as number / 2 - 4,
      bottom: this.theme.button.textMargin.bottom as number / 2 - 4,
      left: this.theme.button.margin.left as number / 2 - 4,
      right: this.theme.button.margin.right as number / 2 - 4
    }
  }

  private getButtonTextMargin(): Margin {
    return { top: this.theme.button.textMargin.bottom as number / 2 }
  }

  private getButtonTextPadding(): Padding {
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

  private getWindowsPadding(): Padding {
    return {
      top: this.theme.windows.padding.top,
      bottom: this.theme.windows.padding.bottom as number - (this.theme.button.textMargin.bottom as number / 2),
      left: this.theme.windows.padding.left as number - (this.theme.button.margin.right as number / 2),
      right: this.theme.windows.padding.right
    }
  }

  aboutToAppear() {
    this.listener.on("change", (mediaQueryResult: mediaquery.MediaQueryResult) => {
      this.currentScreenStatus = mediaQueryResult.matches
    })
  }

  aboutToDisappear() {
    this.listener.off("change")
  }

  getScrollMaxHeight(): number {
    let scrollMaxHeight: number = undefined
    if (this.currentScreenStatus !== this.beforeScreenStatus) {
      this.beforeScreenStatus = this.currentScreenStatus
      return scrollMaxHeight;
    }
    scrollMaxHeight = this.applyHeight
    scrollMaxHeight -= this.titleHeight
    scrollMaxHeight -= this.buttonHeight
    scrollMaxHeight -= this.theme.windows.padding.top as number
    scrollMaxHeight -= (this.theme.button.textMargin.bottom as number / 2)
    scrollMaxHeight -= this.theme.title.margin.bottom as number
    scrollMaxHeight -= (this.theme.windows.padding.bottom as number - (this.theme.button.textMargin.bottom as number / 2))
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

  private getApplyMaxSize(): ConstraintSizeOptions {
    let applyMaxWidth: number = undefined
    let applyMaxHeight: number = undefined
    let applyMaxSize: ConstraintSizeOptions = undefined
    let defaultDisplaySync: display.Display = display.getDefaultDisplaySync()
    if (defaultDisplaySync.width > 400) {
      applyMaxWidth = 400
    } else {
      applyMaxWidth = defaultDisplaySync.width - 40 - 40
    }
    if (defaultDisplaySync.height > 480) {
      applyMaxHeight = 480
    } else {
      applyMaxHeight = defaultDisplaySync.height - 40 - 40
    }
    applyMaxSize = { maxWidth: applyMaxWidth, maxHeight: applyMaxHeight }
    return applyMaxSize
  }

  build() {
    Row() {
      if (this.icon.image !== '' && this.icon.image !== void (0)) {
        Image(this.getIconImage())
          .width(this.getIconWidth())
          .height(this.getIconHeight())
          .margin(this.getIconMargin())
          .fillColor(this.getIconFillColor())
          .borderRadius(this.getIconBorderRadius())
      }
      if (this.title.text !== '' && this.title.text !== void (0)) {
        Column() {
          Flex({ alignItems: ItemAlign.Start }) {
            Text(this.getTitleText())
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
                  .focusable(true)
                  .width(this.getCloseButtonImageWidth())
                  .height(this.getCloseButtonImageHeight())
                  .fillColor(this.getCloseButtonFillColor())
              }
              .width(this.getCloseButtonWidth())
              .height(this.getCloseButtonHeight())
              .padding(this.getCloseButtonPadding())
              .backgroundColor(this.closeButtonBackgroundColor)
              .onHover((isHover: boolean) => {
                if (isHover) {
                  this.closeButtonBackgroundColor = this.getCloseButtonHoverColor()
                }
                else {
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
          .width("100%")
          .margin(this.getTitleMargin())
          .onAreaChange((_, rect) => {
            this.titleHeight = rect.height as number
          })

          Scroll() {
            Text(this.getMessageText())
              .fontSize(this.getMessageFontSize())
              .fontColor(this.getMessageFontColor())
              .fontWeight(this.getMessageFontWeight())
              .constraintSize({ maxWidth: this.getMessageMaxWeight(), minHeight: this.getCloseButtonHeight() })
              .onAreaChange((_, rect) => {
                this.textHeight = rect.height as number
              })
          }
          .width("100%")
          .align(Alignment.TopStart)
          .padding(this.getMessagePadding())
          .scrollBar(BarState.Auto)
          .scrollable(ScrollDirection.Vertical)
          .constraintSize({ maxHeight: this.getScrollMaxHeight() })
          .onAreaChange((_, rect) => {
            this.scrollHeight = rect.height as number
          })

          Flex({ wrap: FlexWrap.Wrap }) {
            if (this.buttons?.[0]?.text !== '' && this.buttons?.[0]?.text !== void (0)) {
              Button() {
                Text(this.getFirstButtonText())
                  .maxLines(2)
                  .focusable(true)
                  .fontSize(this.getFirstButtonFontSize())
                  .fontColor(this.getFirstButtonFontColor())
                  .fontWeight(this.getButtonFontWeight())
                  .minFontSize(this.getButtonMinFontSize())
                  .textOverflow({ overflow: TextOverflow.Ellipsis })
              }
              .margin(this.getButtonMargin())
              .padding(this.getButtonTextPadding())
              .backgroundColor(this.firstButtonBackgroundColor)
              .onHover((isHover: boolean) => {
                if (isHover) {
                  this.firstButtonBackgroundColor = this.getButtonHoverColor()
                }
                else {
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
                  .maxLines(2)
                  .focusable(true)
                  .fontSize(this.getSecondButtonFontSize())
                  .fontColor(this.getSecondButtonFontColor())
                  .fontWeight(this.getButtonFontWeight())
                  .minFontSize(this.getButtonMinFontSize())
                  .textOverflow({ overflow: TextOverflow.Ellipsis })
              }
              .margin(this.getButtonMargin())
              .padding(this.getButtonTextPadding())
              .backgroundColor(this.secondButtonBackgroundColor)
              .onHover((isHover: boolean) => {
                if (isHover) {
                  this.secondButtonBackgroundColor = this.getButtonHoverColor()
                }
                else {
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
          .margin(this.getButtonTextMargin())
          .flexGrow(1)
          .onAreaChange((_, rect) => {
            this.buttonHeight = rect.height as number
          })
        }
        .layoutWeight(this.getLayoutWeight())
      }
      else {
        Column() {
          Row() {
            Scroll() {
              Text(this.getMessageText())
                .fontSize(this.getMessageFontSize())
                .fontColor(this.getMessageFontColor())
                .fontWeight(this.getMessageFontWeight())
                .constraintSize({ maxWidth: this.getMessageMaxWeight(), minHeight: this.getCloseButtonHeight() })
                .onAreaChange((_, rect) => {
                  this.textHeight = rect.height as number
                })
            }
            .layoutWeight(this.getLayoutWeight())
            .align(Alignment.TopStart)
            .padding(this.getMessagePadding())
            .scrollBar(BarState.Auto)
            .scrollable(ScrollDirection.Vertical)
            .constraintSize({ maxHeight: this.getScrollMaxHeight() })
            .onAreaChange((_, rect) => {
              this.scrollHeight = rect.height as number
            })

            if (this.showClose || this.showClose === void (0)) {
              Button() {
                Image(this.getCloseButtonImage())
                  .focusable(true)
                  .width(this.getCloseButtonImageWidth())
                  .height(this.getCloseButtonImageHeight())
                  .fillColor(this.getCloseButtonFillColor())
              }
              .width(this.getCloseButtonWidth())
              .height(this.getCloseButtonHeight())
              .padding(this.getCloseButtonPadding())
              .backgroundColor(this.closeButtonBackgroundColor)
              .onHover((isHover: boolean) => {
                if (isHover) {
                  this.closeButtonBackgroundColor = this.getCloseButtonHoverColor()
                }
                else {
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
          .alignItems(VerticalAlign.Top)
          .margin(this.getTitleMargin())

          Flex({ wrap: FlexWrap.Wrap }) {
            if (this.buttons?.[0]?.text !== '' && this.buttons?.[0]?.text !== void (0)) {
              Button() {
                Text(this.getFirstButtonText())
                  .maxLines(2)
                  .focusable(true)
                  .fontSize(this.getFirstButtonFontSize())
                  .fontColor(this.getFirstButtonFontColor())
                  .fontWeight(this.getButtonFontWeight())
                  .minFontSize(this.getButtonMinFontSize())
                  .textOverflow({ overflow: TextOverflow.Ellipsis })
              }
              .margin(this.getButtonMargin())
              .padding(this.getButtonTextPadding())
              .backgroundColor(this.firstButtonBackgroundColor)
              .onHover((isHover: boolean) => {
                if (isHover) {
                  this.firstButtonBackgroundColor = this.getButtonHoverColor()
                }
                else {
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
                  .maxLines(2)
                  .focusable(true)
                  .fontSize(this.getSecondButtonFontSize())
                  .fontColor(this.getSecondButtonFontColor())
                  .fontWeight(this.getButtonFontWeight())
                  .minFontSize(this.getButtonMinFontSize())
                  .textOverflow({ overflow: TextOverflow.Ellipsis })
              }
              .margin(this.getButtonMargin())
              .padding(this.getButtonTextPadding())
              .backgroundColor(this.secondButtonBackgroundColor)
              .onHover((isHover: boolean) => {
                if (isHover) {
                  this.secondButtonBackgroundColor = this.getButtonHoverColor()
                }
                else {
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
          .margin(this.getButtonTextMargin())
          .flexGrow(1)
          .onAreaChange((_, rect) => {
            this.buttonHeight = rect.height as number
          })
        }
        .layoutWeight(this.getLayoutWeight())
      }
    }
    .alignItems(VerticalAlign.Top)
    .padding(this.getWindowsPadding())
    .constraintSize(this.getApplyMaxSize())
    .onAreaChange((_, rect) => {
      this.applyHeight = rect.height as number
    })
  }
}
