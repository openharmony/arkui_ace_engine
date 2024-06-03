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

import { ButtonOptions } from '@ohos.arkui.advanced.Dialog';
import { BusinessError, Callback } from '@ohos.base';
import display from '@ohos.display';
import hilog from '@ohos.hilog';
import measure from '@ohos.measure';
import resourceManager from '@ohos.resourceManager';
import { CustomColors, CustomTheme, Theme } from '@ohos.arkui.theme';
import bundleManager from '@ohos.bundle.bundleManager';
import { LengthMetrics } from '@ohos.arkui.node';
import common from '@ohos.app.ability.common';

class CustomThemeImpl implements CustomTheme {
  public colors?: CustomColors;

  constructor(colors: CustomColors) {
    this.colors = colors;
  }
}

const TITLE_MAX_LINES: number = 2;
const HORIZON_BUTTON_MAX_COUNT: number = 2;
const VERTICAL_BUTTON_MAX_COUNT: number = 4;
const BUTTON_DEFAULT_HEIGHT: number = 40;
const BUTTON_LAYOUT_WEIGHT: number = 1;
const CHECKBOX_CONTAINER_HEIGHT: number = 48;
const CONTENT_MAX_LINES: number = 2;
const DIVIDER_CONTAINER_WIDTH: number = 16;
const DIVIDER_HEIGHT: number = 24;
const DIVIDER_WIDTH: number = 2;
const LOADING_PROGRESS_WIDTH: number = 40;
const LOADING_PROGRESS_HEIGHT: number = 40;
const ITEM_TEXT_SIZE: number = 14;
const LOADING_MAX_LINES: number = 10;
const LOADING_MAX_LINES_BIG_FONT: number = 4;
const LOADING_TEXT_LAYOUT_WEIGHT: number = 1;
const LOADING_TEXT_MARGIN_LEFT: number = 12;
const LOADING_MIN_HEIGHT: number = 48;
const LIST_MIN_HEIGHT: number = 48;
const CHECKBOX_CONTAINER_LENGTH: number = 20;
const TEXT_MIN_HEIGHT: number = 48;
const DEFAULT_IMAGE_SIZE: number = 64;
const MIN_CONTENT_HEIGHT: number = 100;
const MAX_CONTENT_HEIGHT: number = 30000;
const KEYCODE_UP: number = 2012;
const KEYCODE_DOWN: number = 2013;
const IGNORE_KEY_EVENT_TYPE: number = 1;
const FIRST_ITEM_INDEX: number = 0;
const VERSION_TWELVE: number = 50000012;
const MAX_DIALOG_WIDTH: number = getNumberByResource('alert_container_max_width') ?? 400;
const BUTTON_HORIZONTAL_MARGIN: number = getNumberByResource('alert_right_padding_horizontal') ?? 16;
const BUTTON_HORIZONTAL_PADDING: number = getNumberByResource('padding_level8') ?? 16;
const BUTTON_HORIZONTAL_SPACE: number = getNumberByResource('alert_button_horizontal_space') ?? 8;
const BUTTON_HORIZONTAL_BOTTOM_MARGIN: number = getNumberByResource('alert_button_bottom_padding_horizontal') ?? 16;
const BUTTON_VERTICAL_BOTTOM_MARGIN: number = getNumberByResource('alert_button_bottom_padding_vertical') ?? 8;
const BUTTON_VERTICAL_PADDING: number = getNumberByResource('alert_button_top_padding') ?? 8;
const BUTTON_VERTICAL_SPACE: number = getNumberByResource('alert_button_vertical_space') ?? 4;
const MAX_BIG_BUTTON_SIZE: number = 3;
const MAX_WINDOW_HORIZONTAL_HEIGHT: number = 540;
const MAX_FONT_SCALE: number = 2;
const BODY_L = getNumberByResource('Body_L') ?? 16;
const BODY_M = getNumberByResource('Body_M') ?? 14;
const BODY_S = getNumberByResource('Body_S') ?? 12;
const TITLE_S = getNumberByResource('Title_S') ?? 20;
const SUBTITLE_S = getNumberByResource('Subtitle_S') ?? 14;
const BUTTON_MIN_FONT_SIZE = 9;

@CustomDialog
export struct TipsDialog {
  controller: CustomDialogController;
  imageRes: ResourceStr | PixelMap | null = null;
  @State imageSize?: SizeOptions = { width: DEFAULT_IMAGE_SIZE, height: DEFAULT_IMAGE_SIZE };
  title?: ResourceStr | null = null;
  content?: ResourceStr | null = null;
  checkAction?: (isChecked: boolean) => void;
  onCheckedChange?: Callback<boolean>;
  checkTips?: ResourceStr | null = null;
  @State isChecked?: boolean = false;
  primaryButton?: ButtonOptions | null = null;
  secondaryButton?: ButtonOptions | null = null;
  buttons?: ButtonOptions[] | undefined = undefined;
  @State imageSizeHeight: number = 0;
  @State textAlignment: TextAlign = TextAlign.Start;
  marginOffset: number = 0;
  @State checkBoxHeight: number = 0;
  @State buttonHeight: number = 0;
  // the controller of content area scroll
  contentScroller: Scroller = new Scroller();
  @State fontColorWithTheme: ResourceColor = $r('sys.color.font_primary');
  theme?: Theme | CustomTheme = new CustomThemeImpl({});
  themeColorMode?: ThemeColorMode = ThemeColorMode.SYSTEM;
  @State fontSizeScale: number = 1;
  @State windowSize: Size = { width: 0, height: 0 };
  updateButtonHeight: (height: number) => void = (height: number) => {
    this.buttonHeight = height;
  }

  build() {
    CustomDialogContentComponent({
      controller: this.controller,
      contentBuilder: () => {
        this.contentBuilder();
      },
      buttons: this.buttons,
      theme: this.theme,
      themeColorMode: this.themeColorMode,
      fontSizeScale: this.fontSizeScale,
      windowSize: this.windowSize,
      updateButtonHeight: this.updateButtonHeight
    }).constraintSize({ maxHeight: '100%' });
  }

  @Builder
  contentBuilder(): void {
    Column() {
      this.imagePart();

      if (this.title != null || this.content != null) {
        Column() {
          this.textPart();
        }
        .padding({ top: $r('sys.float.padding_level8') })
        .constraintSize({
          maxHeight: `calc(100% - ${this.checkBoxHeight}vp - ${this.imageSizeHeight}vp - ${this.buttonHeight}vp)`
        })
      }

      if (this.checkTips != null) {
        this.checkBoxPart(this.checkTips);
      }
    }
  }

  @Builder
  checkBoxPart(content: ResourceStr): void {
    Row() {
      Checkbox({ name: 'checkbox', group: 'checkboxGroup' }).select(this.isChecked)
        .onChange((checked: boolean) => {
          this.isChecked = checked;
          if (this.checkAction) {
            this.checkAction(checked);
          }
          if (this.onCheckedChange) {
            this.onCheckedChange(checked);
          }
        })
        .margin({ right: $r('sys.float.padding_level4') })
      Text(content)
        .fontSize(this.getCheckBoxFontSize())
        .fontWeight(FontWeight.Regular)
        .fontColor(this.fontColorWithTheme)
        .maxLines(CONTENT_MAX_LINES)
        .layoutWeight(1)
        .focusable(false)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .onClick(() => {
          this.isChecked = !this.isChecked;
          if (this.checkAction) {
            this.checkAction(this.isChecked);
          }
        })
    }
    .padding({ top: $r('sys.float.padding_level8') })
    .constraintSize({ minHeight: CHECKBOX_CONTAINER_HEIGHT })
    .width('100%')
    .onAreaChange((oldValue: Area, newValue: Area) => {
      this.checkBoxHeight = Number(newValue.height);
    })
  }

  @Builder
  imagePart(): void {
    Column() {
      Image(this.imageRes)
        .size(this.imageSize)
        .objectFit(ImageFit.Contain)
        .borderRadius($r('sys.float.corner_radius_level6'))
        .constraintSize({
          maxWidth: '100%',
          maxHeight:
          `calc(100% - ${this.checkBoxHeight}vp - ${this.buttonHeight}vp - ${TEXT_MIN_HEIGHT}vp + ${this.marginOffset}vp)`
        })
    }
    .width('100%')
    .constraintSize({
      maxHeight:
      `calc(100% - ${this.checkBoxHeight}vp - ${this.buttonHeight}vp - ${TEXT_MIN_HEIGHT}vp + ${this.marginOffset}vp)`
    })
    .onAreaChange((oldValue: Area, newValue: Area) => {
      this.imageSizeHeight = Number(newValue.height);
    })
  }

  @Builder
  textPart(): void {
    Scroll(this.contentScroller) {
      Column() {
        if (this.title != null) {
          Row() {
            Text(this.title)
              .fontSize(this.getTitleFontSize())
              .fontWeight(FontWeight.Medium)
              .fontColor(this.fontColorWithTheme)
              .textAlign(TextAlign.Center)
              .maxLines(CONTENT_MAX_LINES)
              .textOverflow({ overflow: TextOverflow.Ellipsis })
              .width('100%')
          }
          .padding({ bottom: $r('sys.float.padding_level8') })
        }
        if (this.content != null) {
          Row() {
            Text(this.content)
              .focusable(true)
              .defaultFocus(!(this.primaryButton || this.secondaryButton))
              .fontSize(this.getContentFontSize())
              .fontWeight(FontWeight.Medium)
              .fontColor(this.fontColorWithTheme)
              .textAlign(this.textAlignment)
              .width('100%')
              .onKeyEvent((event: KeyEvent) => {
                if (event) {
                  resolveKeyEvent(event, this.contentScroller);
                }
              })
              .onAreaChange((oldValue: Area, newValue: Area) => {
                this.getTextAlign(Number(newValue.width));
              })
          }
        }
      }
      .margin({ right: $r('sys.float.padding_level8') })
    }
    .margin({ right: `${this.marginOffset}vp` })
  }

  aboutToAppear() {
    this.fontColorWithTheme = this.theme?.colors?.fontPrimary ?
    this.theme.colors.fontPrimary : $r('sys.color.font_primary');
    this.initButtons();
    this.initMargin();
  }

  private getTextAlign(maxWidth: number): void {
    let contentFontSize: Length = this.getContentFontSize()
    let contentSize: SizeOptions = measure.measureTextSize({
      textContent: this.content,
      fontSize: contentFontSize,
      constraintWidth: maxWidth,
    });
    let oneLineSize: SizeOptions = measure.measureTextSize({
      textContent: this.content,
      fontSize: contentFontSize,
    });
    if (this.getTextHeight(contentSize) <= this.getTextHeight(oneLineSize)) {
      this.textAlignment = TextAlign.Center;
    }
  }

  getTitleFontSize(): Length {
    if (this.fontSizeScale > MAX_FONT_SCALE && this.windowSize.height < MAX_WINDOW_HORIZONTAL_HEIGHT) {
      return TITLE_S * MAX_FONT_SCALE + 'vp';
    }
    return TITLE_S + 'fp';
  }

  getContentFontSize(): Length {
    if (this.fontSizeScale > MAX_FONT_SCALE && this.windowSize.height < MAX_WINDOW_HORIZONTAL_HEIGHT) {
      return BODY_L * MAX_FONT_SCALE + 'vp';
    }
    return BODY_L + 'fp';
  }

  getCheckBoxFontSize(): Length {
    if (this.fontSizeScale > MAX_FONT_SCALE && this.windowSize.height < MAX_WINDOW_HORIZONTAL_HEIGHT) {
      return BODY_M * MAX_FONT_SCALE + 'vp';
    }
    return BODY_M + 'fp';
  }

  private getTextHeight(textSize: SizeOptions): number {
    if (textSize && textSize.height !== null && textSize.height !== undefined) {
      return Number(textSize.height);
    }
    return 0;
  }

  private initButtons(): void {
    if (!this.primaryButton && !this.secondaryButton) {
      return;
    }
    this.buttons = [];
    if (this.primaryButton) {
      this.buttons.push(this.primaryButton);
    }
    if (this.secondaryButton) {
      this.buttons.push(this.secondaryButton);
    }
  }

  private initMargin(): void {
    this.marginOffset = 0 - getNumberByResource('padding_level8');
  }
}

@CustomDialog
export struct SelectDialog {
  controller: CustomDialogController;
  title: ResourceStr = '';
  content?: ResourceStr = '';
  selectedIndex?: number = -1;
  confirm?: ButtonOptions | null = null;
  radioContent: Array<SheetInfo> = [];
  buttons?: ButtonOptions[] = [];
  contentPadding ?: Padding;
  isFocus: boolean = false;
  currentFocusIndex?: number = -1;
  radioHeight: number = 0;
  itemHeight: number = 0;
  @BuilderParam contentBuilder: () => void = this.buildContent;
  @State fontColorWithTheme: ResourceColor = $r('sys.color.font_primary');
  @State dividerColorWithTheme: ResourceColor = $r('sys.color.comp_divider');
  theme?: Theme | CustomTheme = new CustomThemeImpl({});
  themeColorMode?: ThemeColorMode = ThemeColorMode.SYSTEM;
  // the controller of content list
  contentScroller: Scroller = new Scroller();
  @State fontSizeScale: number = 1;
  @State windowSize: Size = { width: 0, height: 0 };

  @Styles
  paddingContentStyle() {
    .padding({
      left: $r('sys.float.padding_level12'),
      right: $r('sys.float.padding_level12'),
      bottom: $r('sys.float.padding_level4')
    })
  }

  @Styles
  paddingStyle() {
    .padding({
      left: $r('sys.float.padding_level6'),
      right: $r('sys.float.padding_level6')
    })
  }

  @Builder
  buildContent(): void {
    Scroll(this.contentScroller) {
      Column() {
        if (this.content) {
          Row() {
            Text(this.content)
              .fontSize(this.getContentFontSize())
              .fontWeight(FontWeight.Regular)
              .fontColor(this.fontColorWithTheme)
              .textOverflow({ overflow: TextOverflow.Ellipsis })
          }.paddingContentStyle().width('100%')
        }
        List({ space: 1 }) {
          ForEach(this.radioContent, (item: SheetInfo, index: number) => {
            ListItem() {
              Column() {
                Button() {
                  Row() {
                    Text(item.title)
                      .fontSize(this.getListFontSize())
                      .fontWeight(FontWeight.Medium)
                      .fontColor(this.fontColorWithTheme)
                      .layoutWeight(1)
                    Radio({ value: 'item.title', group: 'radioGroup' })
                      .size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH })
                      .checked(this.selectedIndex === index)
                      .hitTestBehavior(HitTestMode.None)
                      .id(String(index))
                      .onFocus(() => {
                        this.isFocus = true;
                        this.currentFocusIndex = index;
                        if (index == FIRST_ITEM_INDEX) {
                          this.contentScroller.scrollEdge(Edge.Top);
                        } else if (index == this.radioContent.length - 1) {
                          this.contentScroller.scrollEdge(Edge.Bottom);
                        }
                      })
                      .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
                        this.radioHeight = Number(newValue.height)
                      })
                  }.constraintSize({ minHeight: LIST_MIN_HEIGHT }).clip(false)
                  .padding({ top: $r('sys.float.padding_level4'), bottom: $r('sys.float.padding_level4') })
                }
                .type(ButtonType.Normal)
                .borderRadius($r('sys.float.corner_radius_level8'))
                .buttonStyle(ButtonStyleMode.TEXTUAL)
                .paddingStyle()
                .onClick(() => {
                  item.action && item.action();
                  this.controller.close();
                })

                if (index < this.radioContent.length - 1) {
                  Divider().color(this.dividerColorWithTheme).paddingStyle();
                }
              }.paddingStyle()
            }
            .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
              this.itemHeight = Number(newValue.height)
            })
          })
        }.width('100%').clip(false)
        .onFocus(() => {
          if (!this.contentScroller.isAtEnd()) {
            this.contentScroller.scrollEdge(Edge.Top);
            focusControl.requestFocus(String(FIRST_ITEM_INDEX));
          }
        })
        .defaultFocus(this.buttons?.length == 0 ? true : false)
      }
    }.scrollBar(BarState.Auto)
    .onDidScroll((xOffset: number, yOffset: number) => {
      let scrollHeight: number = (this.itemHeight - this.radioHeight) / 2
      if (this.isFocus) {
        if (this.currentFocusIndex === this.radioContent.length - 1) {
          this.contentScroller.scrollEdge(Edge.Bottom);
          this.currentFocusIndex = -1;
        } else if (this.currentFocusIndex === FIRST_ITEM_INDEX) {
          this.contentScroller.scrollEdge(Edge.Top);
          this.currentFocusIndex = -1;
        } else {
          if (yOffset > 0) {
            this.contentScroller.scrollBy(0, scrollHeight)
          } else if (yOffset < 0) {
            this.contentScroller.scrollBy(0, 0 - scrollHeight)
          }
        }
        this.isFocus = false;
      }
    })
  }

  build() {
    CustomDialogContentComponent({
      controller: this.controller,
      primaryTitle: this.title,
      contentBuilder: () => {
        this.contentBuilder();
      },
      buttons: this.buttons,
      contentAreaPadding: this.contentPadding,
      theme: this.theme,
      themeColorMode: this.themeColorMode,
      fontSizeScale: this.fontSizeScale,
      windowSize: this.windowSize
    }).constraintSize({ maxHeight: '100%' });
  }

  aboutToAppear(): void {
    this.fontColorWithTheme = this.theme?.colors?.fontPrimary ?
    this.theme.colors.fontPrimary : $r('sys.color.font_primary');
    this.dividerColorWithTheme = this.theme?.colors?.compDivider ?
    this.theme.colors.compDivider : $r('sys.color.comp_divider');
    this.initContentPadding();
    this.initButtons();
  }

  private initContentPadding(): void {
    this.contentPadding = {
      left: $r('sys.float.padding_level0'),
      right: $r('sys.float.padding_level0')
    }

    if (!this.title && !this.confirm) {
      this.contentPadding = {
        top: $r('sys.float.padding_level12'),
        bottom: $r('sys.float.padding_level12')
      }
      return;
    }

    if (!this.title) {
      this.contentPadding = {
        top: $r('sys.float.padding_level12')
      }
    } else if (!this.confirm) {
      this.contentPadding = {
        bottom: $r('sys.float.padding_level12')
      }
    }
  }

  private initButtons(): void {
    this.buttons = [];
    if (this.confirm) {
      this.buttons.push(this.confirm);
    }
  }

  getContentFontSize(): Length {
    if (this.fontSizeScale > MAX_FONT_SCALE && this.windowSize.height < MAX_WINDOW_HORIZONTAL_HEIGHT) {
      return BODY_M * MAX_FONT_SCALE + 'vp';
    }
    return BODY_M + 'fp';
  }

  getListFontSize(): Length {
    if (this.fontSizeScale > MAX_FONT_SCALE && this.windowSize.height < MAX_WINDOW_HORIZONTAL_HEIGHT) {
      return BODY_L * MAX_FONT_SCALE + 'vp';
    }
    return BODY_L + 'fp';
  }
}

@CustomDialog
export struct ConfirmDialog {
  controller: CustomDialogController
  title: ResourceStr = ''
  content?: ResourceStr = ''
  checkTips?: ResourceStr = ''
  @State isChecked?: boolean = false
  primaryButton?: ButtonOptions = { value: "" }
  secondaryButton?: ButtonOptions = { value: "" }
  @State fontColorWithTheme: ResourceColor = $r('sys.color.font_primary');
  theme?: Theme | CustomTheme = new CustomThemeImpl({});
  themeColorMode?: ThemeColorMode = ThemeColorMode.SYSTEM;
  onCheckedChange?: Callback<boolean>;
  contentScroller: Scroller = new Scroller();
  buttons?: ButtonOptions[] | undefined = undefined;
  marginOffset: number = 0;
  @State titleHeight: number = 0;
  @State buttonHeight: number = 0;
  @State checkBoxHeight: number = CHECKBOX_CONTAINER_HEIGHT;
  @State fontSizeScale: number = 1;
  @State windowSize: Size = { width: 0, height: 0 };
  @State maxContentHeight: string =
    `calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
  updateTitleHeight: (height: number) => void = (height: number) => {
    this.titleHeight = height;
    this.maxContentHeight = `calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
  }
  updateButtonHeight: (height: number) => void = (height: number) => {
    this.buttonHeight = height;
    this.maxContentHeight = `calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
  }

  @Builder
  buildContent(): void {
    Column() {
      if (this.content) {
        Row() {
          Scroll(this.contentScroller) {
            Text(this.content)
              .focusable(true)
              .defaultFocus(!(this.primaryButton?.value || this.secondaryButton?.value))
              .fontSize(this.getContentFontSize())
              .fontWeight(FontWeight.Medium)
              .fontColor(this.fontColorWithTheme)
              .textAlign(TextAlign.Start)
              .margin({ right: $r('sys.float.padding_level8') })
              .onKeyEvent((event: KeyEvent) => {
                if (event) {
                  resolveKeyEvent(event, this.contentScroller);
                }
              })
              .width(`calc(100% - ${getNumberByResource('padding_level8')}vp)`)
          }
          .width('100%')
        }
        .padding({ bottom: 8 })
        .margin({ right: `${this.marginOffset}vp` })
        .constraintSize({
          minHeight: 36,
          maxHeight: this.maxContentHeight
        })
      }

      Row() {
        Checkbox({ name: 'checkbox', group: 'checkboxGroup' }).select(this.isChecked)
          .onChange((checked: boolean) => {
            this.isChecked = checked;
            if (this.onCheckedChange) {
              this.onCheckedChange(this.isChecked);
            }
          })
          .hitTestBehavior(HitTestMode.Block)
          .margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(8) })

        Text(this.checkTips)
          .fontSize(this.getCheckBoxFontSize())
          .fontWeight(FontWeight.Medium)
          .fontColor(this.fontColorWithTheme)
          .maxLines(CONTENT_MAX_LINES)
          .focusable(false)
          .layoutWeight(1)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .onClick(() => {
            this.isChecked = !this.isChecked;
          })
      }
      .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
        this.checkBoxHeight = Number(newValue.height);
        this.maxContentHeight = `calc(100% - ${this.checkBoxHeight}vp - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
      })
      .constraintSize({ minHeight: CHECKBOX_CONTAINER_HEIGHT })
      .width('100%')
      .padding({ top: 8, bottom: 8 })
    }
  }

  getContentFontSize(): Length {
    if (this.fontSizeScale > MAX_FONT_SCALE && this.windowSize.height < MAX_WINDOW_HORIZONTAL_HEIGHT) {
      return BODY_L * MAX_FONT_SCALE + 'vp';
    }
    return BODY_L + 'fp';

  }

  getCheckBoxFontSize(): Length {
    if (this.fontSizeScale > MAX_FONT_SCALE && this.windowSize.height < MAX_WINDOW_HORIZONTAL_HEIGHT) {
      return BODY_M * MAX_FONT_SCALE + 'vp';
    }
    return BODY_M + 'fp';
  }

  build() {
    CustomDialogContentComponent({
      primaryTitle: this.title,
      controller: this.controller,
      contentBuilder: () => {
        this.buildContent();
      },
      updateTitleHeight: this.updateTitleHeight,
      updateButtonHeight: this.updateButtonHeight,
      buttons: this.buttons,
      theme: this.theme,
      themeColorMode: this.themeColorMode,
      fontSizeScale: this.fontSizeScale,
      windowSize: this.windowSize
    }).constraintSize({ maxHeight: '100%' });
  }

  aboutToAppear(): void {
    this.fontColorWithTheme = this.theme?.colors?.fontPrimary ?
    this.theme.colors.fontPrimary : $r('sys.color.font_primary');
    this.initButtons();
    this.initMargin();
  }

  private initMargin(): void {
    this.marginOffset = 0 - getNumberByResource('padding_level8');
  }

  private initButtons(): void {
    if (!this.primaryButton && !this.secondaryButton) {
      return;
    }
    this.buttons = [];
    if (this.primaryButton) {
      this.buttons.push(this.primaryButton);
    }
    if (this.secondaryButton) {
      this.buttons.push(this.secondaryButton);
    }
  }
}

@CustomDialog
export struct AlertDialog {
  controller: CustomDialogController;
  primaryTitle?: ResourceStr | undefined = undefined;
  secondaryTitle?: ResourceStr | undefined = undefined;
  content: ResourceStr = '';
  primaryButton?: ButtonOptions | null = null;
  secondaryButton?: ButtonOptions | null = null;
  buttons?: ButtonOptions[] | undefined = undefined;
  @State textAlign: TextAlign = TextAlign.Start;
  // the controller of content area
  contentScroller: Scroller = new Scroller();
  @State fontColorWithTheme: ResourceColor = $r('sys.color.font_primary');
  theme?: Theme | CustomTheme = new CustomThemeImpl({});
  themeColorMode?: ThemeColorMode = ThemeColorMode.SYSTEM;
  @State windowSize: Size = { width: MAX_DIALOG_WIDTH, height: 0 };
  @State fontSizeScale: number = 1;

  build() {
    CustomDialogContentComponent({
      primaryTitle: this.primaryTitle,
      secondaryTitle: this.secondaryTitle,
      controller: this.controller,
      contentBuilder: () => {
        this.AlertDialogContentBuilder();
      },
      buttons: this.buttons,
      theme: this.theme,
      themeColorMode: this.themeColorMode,
      fontSizeScale: this.fontSizeScale,
      windowSize: this.windowSize,
    }).constraintSize({ maxHeight: '100%' });
  }

  @Builder
  AlertDialogContentBuilder(): void {
    Column() {
      Scroll(this.contentScroller) {
        Text(this.content)
          .focusable(true)
          .defaultFocus(!(this.primaryButton || this.secondaryButton))
          .fontSize(this.getContentFontSize())
          .fontWeight(this.getFontWeight())
          .fontColor(this.fontColorWithTheme)
          .margin({ right: $r('sys.float.padding_level8'), })
          .width(`calc(100% - ${getNumberByResource('padding_level8')}vp)`)
          .textAlign(this.textAlign)
          .onAreaChange((oldValue: Area, newValue: Area) => {
            this.getTextAlign(Number(newValue.width));
          })
          .onKeyEvent((event: KeyEvent) => {
            if (event) {
              resolveKeyEvent(event, this.contentScroller);
            }
          })
      }
      .width('100%')
    }
    .margin({ right: `${this.getMargin()}vp`, })
  }

  aboutToAppear(): void {
    this.fontColorWithTheme = this.theme?.colors?.fontPrimary ?
    this.theme.colors.fontPrimary : $r('sys.color.font_primary');
    this.initButtons();
  }

  private getContentFontSize(): Length {
    if (this.fontSizeScale > MAX_FONT_SCALE && this.windowSize.height < MAX_WINDOW_HORIZONTAL_HEIGHT) {
      return BODY_L * MAX_FONT_SCALE + 'vp';
    } else {
      return BODY_L + 'fp';
    }
  }

  private getTextAlign(maxWidth: number): void {
    let fontSize: Length = this.getContentFontSize();
    let contentSize: SizeOptions = measure.measureTextSize({
      textContent: this.content,
      fontSize: fontSize,
      constraintWidth: maxWidth,
    });
    let oneLineSize: SizeOptions = measure.measureTextSize({
      textContent: this.content,
      fontSize: fontSize,
    });
    if (this.getTextHeight(contentSize) <= this.getTextHeight(oneLineSize)) {
      this.textAlign = TextAlign.Center;
    }
  }

  private getTextHeight(textSize: SizeOptions): number {
    if (textSize && textSize.height !== null && textSize.height !== undefined) {
      return Number(textSize.height);
    }
    return 0;
  }

  private initButtons(): void {
    if (!this.primaryButton && !this.secondaryButton) {
      return;
    }
    this.buttons = [];
    if (this.primaryButton) {
      this.buttons.push(this.primaryButton);
    }
    if (this.secondaryButton) {
      this.buttons.push(this.secondaryButton);
    }
  }

  private getMargin(): number {
    return 0 - getNumberByResource('padding_level8');
  }

  private getFontWeight(): number {
    if (this.primaryTitle || this.secondaryTitle) {
      return FontWeight.Regular;
    }
    return FontWeight.Medium;
  }
}

@CustomDialog
export struct CustomContentDialog {
  controller: CustomDialogController;
  primaryTitle?: ResourceStr;
  secondaryTitle?: ResourceStr;
  @BuilderParam contentBuilder: () => void;
  contentAreaPadding?: Padding;
  buttons?: ButtonOptions[];
  theme?: Theme | CustomTheme = new CustomThemeImpl({});
  themeColorMode?: ThemeColorMode = ThemeColorMode.SYSTEM;
  @State fontSizeScale: number = 1;
  @State windowSize: Size = { width: 0, height: 0 };

  build() {
    CustomDialogContentComponent({
      controller: this.controller,
      primaryTitle: this.primaryTitle,
      secondaryTitle: this.secondaryTitle,
      contentBuilder: () => {
        this.contentBuilder();
      },
      contentAreaPadding: this.contentAreaPadding,
      buttons: this.buttons,
      theme: this.theme,
      themeColorMode: this.themeColorMode,
      fontSizeScale: this.fontSizeScale,
      windowSize: this.windowSize
    }).constraintSize({ maxHeight: '100%' });
  }
}

@Component
struct CustomDialogContentComponent {
  controller?: CustomDialogController;
  primaryTitle?: ResourceStr;
  secondaryTitle?: ResourceStr;
  @BuilderParam contentBuilder: () => void = this.defaultContentBuilder;
  buttons?: ButtonOptions[];
  contentAreaPadding?: Padding;
  keyIndex: number = 0;
  theme?: Theme | CustomTheme = new CustomThemeImpl({});
  themeColorMode?: ThemeColorMode = ThemeColorMode.SYSTEM;

  @Builder
  defaultContentBuilder(): void {
  }

  @State titleHeight: number = 0;
  @State buttonHeight: number = 0;
  @State contentMaxHeight: string = `calc(100% - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
  updateTitleHeight?: (height: number) => void;
  updateButtonHeight?: (height: number) => void;
  targetSdk: number = VERSION_TWELVE;
  @Link fontSizeScale: number;
  @Link windowSize: Size;
  @State customStyle: boolean = false;
  @State needResponseScale: boolean = true;
  screenSize: Size = { width: 0, height: 0 };
  initCustomStyle: boolean = false;

  build() {
    WithTheme({ theme: this.theme, colorMode: this.themeColorMode }) {
      Scroll() {
        Column() {
          // title area
          TitleComponent({
            primaryTitle: this.primaryTitle,
            secondaryTitle: this.secondaryTitle,
            windowSize: this.windowSize,
            fontSizeScale: this.fontSizeScale,
            titleHeight: this.titleHeight,
            needResponseScale: this.needResponseScale,
            theme: this.theme
          })
          // content area
          Column() {
            this.contentBuilder();
          }
          .padding(this.getContentPadding())
          .constraintSize({ maxHeight: this.contentMaxHeight })

          ButtonComponent({
            buttons: this.buttons,
            windowSize: this.windowSize,
            fontSizeScale: this.fontSizeScale,
            needResponseScale: this.needResponseScale,
            buttonHeight: this.buttonHeight,
            controller: this.controller,
            theme: this.theme
          })
        }
        .backgroundBlurStyle(this.customStyle ? BlurStyle.Thick : BlurStyle.NONE)
        .borderRadius(this.customStyle ? $r('sys.float.ohos_id_corner_radius_dialog') : 0)
        .margin(this.customStyle ? {
          left: $r('sys.float.ohos_id_dialog_margin_start'),
          right: $r('sys.float.ohos_id_dialog_margin_end'),
          bottom: $r('sys.float.ohos_id_dialog_margin_bottom'),
        } : { left: 0, right: 0, bottom: 0 })
        .backgroundColor(this.customStyle ? $r('sys.color.ohos_id_color_dialog_bg') : Color.Transparent)
      }
      .backgroundColor(this.themeColorMode === ThemeColorMode.SYSTEM || undefined ?
        Color.Transparent : $r('sys.color.comp_background_primary'))
    }
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>,
                constraint: ConstraintSizeOptions): SizeResult {
    let sizeResult: SizeResult = { width: selfLayoutInfo.width, height: selfLayoutInfo.height };
    let maxWidth: number = Number(constraint.maxWidth);
    let maxHeight: number = Number(constraint.maxHeight);
    this.windowSize = { width: maxWidth, height: maxHeight };
    this.updateFontScale();
    this.updateNeedResponseScale();
    this.updateCustomStyle(Number(constraint.maxWidth), Number(constraint.maxHeight));

    children.forEach((child) => {
      let measureResult: MeasureResult = child.measure(constraint);
      if (this.updateButtonHeight) {
        this.updateButtonHeight(this.buttonHeight);
      }
      if (this.updateTitleHeight) {
        this.updateTitleHeight(this.titleHeight);
      }
      if (maxHeight - this.buttonHeight - this.titleHeight < MIN_CONTENT_HEIGHT) {
        this.contentMaxHeight = `${MAX_CONTENT_HEIGHT}vp`;
      } else {
        this.contentMaxHeight = `calc(100% - ${this.titleHeight}vp - ${this.buttonHeight}vp)`;
      }
      measureResult = child.measure(constraint);
      sizeResult.height = measureResult.height;
    });
    sizeResult.width = Number(constraint.maxWidth);
    return sizeResult;
  }

  updateCustomStyle(dialogWidth: number, dialogHeight: number) {
    if (this.initCustomStyle) {
      return;
    }
    if (this.targetSdk >= VERSION_TWELVE) {
      return;
    }
    let marginStart: number = getNumberByResource('ohos_id_dialog_margin_start');
    let marginEnd: number = getNumberByResource('ohos_id_dialog_margin_end');
    if (Math.abs(dialogWidth - this.screenSize.width) < marginStart + marginEnd ||
      Math.abs(dialogHeight - this.screenSize.height) < 1) {
      this.customStyle = true;
    }
    this.initCustomStyle = true;
  }

  updateNeedResponseScale() {
    if (this.buttons && this.buttons.length >= MAX_BIG_BUTTON_SIZE &&
      this.windowSize.height < MAX_WINDOW_HORIZONTAL_HEIGHT) {
      this.needResponseScale = false;
    } else {
      this.needResponseScale = true;
    }
  }

  aboutToAppear(): void {
    this.initEnvInfo();
  }

  private initEnvInfo(): void {
    try {
      let screenSize: display.Display = display.getDefaultDisplaySync();
      this.windowSize = { width: px2vp(screenSize.width), height: px2vp(screenSize.height) };
      this.screenSize = { width: this.windowSize.width, height: this.windowSize.height };
    } catch (exception) {
      let code: number = (exception as BusinessError).code;
      let message: string = (exception as BusinessError).message;
      hilog.error(0x3900, 'Ace', `Faild to init windowsize,cause, code: ${code}, message: ${message}`);
    }
    this.updateFontScale();
    try {
      let bundleFlags = bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_APPLICATION |
      bundleManager.BundleFlag.GET_BUNDLE_INFO_WITH_METADATA;
      this.targetSdk = bundleManager.getBundleInfoForSelfSync(bundleFlags).targetVersion;
    } catch (exception) {
      let code: number = (exception as BusinessError).code;
      let message: string = (exception as BusinessError).message;
      hilog.error(0x3900, 'Ace', `Faild to init bundle info,cause, code: ${code}, message: ${message}`);
    }
  }

  updateFontScale(): void {
    try {
      let context: common.ExtensionContext = this.getUIContext().getHostContext() as common.ExtensionContext;
      this.fontSizeScale = context.config?.fontSizeScale ?? this.fontSizeScale;
    } catch (exception) {
      let code: number = (exception as BusinessError).code;
      let message: string = (exception as BusinessError).message;
      hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${code}, message: ${message}`);
    }
  }

  /**
   * get dialog content padding
   *
   * @returns content padding
   */
  private getContentPadding(): Padding {
    if (this.contentAreaPadding) {
      return this.contentAreaPadding;
    }

    if ((this.primaryTitle || this.secondaryTitle) && this.buttons && this.buttons.length > 0) {
      return {
        top: 0,
        right: $r('sys.float.alert_content_default_padding'),
        bottom: 0,
        left: $r('sys.float.alert_content_default_padding'),
      };
    } else if (this.primaryTitle || this.secondaryTitle) {
      return {
        top: 0,
        right: $r('sys.float.alert_content_default_padding'),
        bottom: $r('sys.float.alert_content_default_padding'),
        left: $r('sys.float.alert_content_default_padding'),
      };
    } else if (this.buttons && this.buttons.length > 0) {
      return {
        top: $r('sys.float.alert_content_default_padding'),
        right: $r('sys.float.alert_content_default_padding'),
        bottom: 0,
        left: $r('sys.float.alert_content_default_padding'),
      };
    } else {
      return {
        top: $r('sys.float.alert_content_default_padding'),
        right: $r('sys.float.alert_content_default_padding'),
        bottom: $r('sys.float.alert_content_default_padding'),
        left: $r('sys.float.alert_content_default_padding'),
      };
    }
  }
}

@Component
struct TitleComponent {
  primaryTitle?: ResourceStr;
  secondaryTitle?: ResourceStr;
  theme?: Theme | CustomTheme = new CustomThemeImpl({});
  @State primaryTitleFontColorWithTheme: ResourceColor = $r('sys.color.font_primary');
  @State secondaryTitleFontColorWithTheme: ResourceColor = $r('sys.color.font_secondary');
  @State titleTextAlign: TextAlign = TextAlign.Center;
  @State primaryTitleMaxFontSize: Length = $r('sys.float.Title_S');
  @State primaryTitleMinFontSize: Length = $r('sys.float.Body_L');
  @State secondaryTitleMaxFontSize: Length = $r('sys.float.Subtitle_S');
  @State secondaryTitleMinFontSize: Length = $r('sys.float.Body_S');
  @Link needResponseScale: boolean;
  @Link fontSizeScale: number;
  @Link windowSize: Size;
  @Link titleHeight: Length;

  build() {
    Column() {
      Row() {
        Text(this.primaryTitle)
          .fontWeight(FontWeight.Bold)
          .fontColor(this.primaryTitleFontColorWithTheme)
          .textAlign(this.titleTextAlign)
          .maxFontSize(this.primaryTitleMaxFontSize)
          .minFontSize(this.primaryTitleMinFontSize)
          .maxLines(TITLE_MAX_LINES)
          .heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .width('100%')
      }
      .width('100%')

      if (this.primaryTitle && this.secondaryTitle) {
        Row() {
          Divider().margin($r('sys.float.padding_level1')).color(Color.Transparent)
        }
      }

      Row() {
        Text(this.secondaryTitle)
          .fontWeight(FontWeight.Regular)
          .fontColor(this.secondaryTitleFontColorWithTheme)
          .textAlign(this.titleTextAlign)
          .maxFontSize(this.secondaryTitleMaxFontSize)
          .minFontSize(this.secondaryTitleMinFontSize)
          .maxLines(TITLE_MAX_LINES)
          .heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .width('100%')
      }
      .width('100%')
    }
    .constraintSize({
      minHeight: this.getTitleAreaMinHeight(),
    })
    .justifyContent(FlexAlign.Center)
    .width('100%')
    .padding(this.getTitleAreaPadding())
  }

  aboutToAppear(): void {
    this.primaryTitleFontColorWithTheme = this.theme?.colors?.fontPrimary ?
    this.theme.colors.fontPrimary : $r('sys.color.font_primary');
    this.secondaryTitleFontColorWithTheme = this.theme?.colors?.fontSecondary ?
    this.theme.colors.fontSecondary : $r('sys.color.font_secondary');
    this.initTitleTextAlign();
    this.updateFontSize();
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>,
                constraint: ConstraintSizeOptions): SizeResult {
    let sizeResult: SizeResult = { width: selfLayoutInfo.width, height: selfLayoutInfo.height };
    this.updateFontSize();
    children.forEach((child) => {
      let measureResult: MeasureResult = child.measure(constraint);
      sizeResult.height = measureResult.height;
    });
    sizeResult.width = Number(constraint.maxWidth);
    this.titleHeight = sizeResult.height;
    return sizeResult;
  }

  updateFontSize(): void {
    if (this.needResponseScale) {
      if (this.fontSizeScale > MAX_FONT_SCALE) {
        this.primaryTitleMaxFontSize = TITLE_S * MAX_FONT_SCALE + 'vp';
        this.primaryTitleMinFontSize = BODY_L * MAX_FONT_SCALE + 'vp';
        this.secondaryTitleMaxFontSize = SUBTITLE_S * MAX_FONT_SCALE + 'vp';
        this.secondaryTitleMinFontSize = BODY_S * MAX_FONT_SCALE + 'vp';
      } else {
        this.primaryTitleMaxFontSize = TITLE_S + 'fp';
        this.primaryTitleMinFontSize = BODY_L + 'fp';
        this.secondaryTitleMaxFontSize = SUBTITLE_S + 'fp';
        this.secondaryTitleMinFontSize = BODY_S + 'fp';
      }
    } else {
      this.primaryTitleMaxFontSize = TITLE_S + 'vp';
      this.primaryTitleMinFontSize = BODY_L + 'vp';
      this.secondaryTitleMaxFontSize = SUBTITLE_S + 'vp';
      this.secondaryTitleMinFontSize = BODY_S + 'vp';
    }
  }

  /**
   * get title area padding
   *
   * @returns padding
   */
  private getTitleAreaPadding(): Padding {
    if (this.primaryTitle || this.secondaryTitle) {
      return {
        top: $r('sys.float.alert_title_padding_top'),
        right: $r('sys.float.alert_title_padding_right'),
        left: $r('sys.float.alert_title_padding_left'),
        bottom: $r('sys.float.alert_title_padding_bottom'),
      };
    }

    return {
      top: 0,
      right: $r('sys.float.alert_title_padding_right'),
      left: $r('sys.float.alert_title_padding_left'),
      bottom: 0,
    };
  }

  /**
   * get tile TextAlign
   * @returns TextAlign
   */
  private initTitleTextAlign(): void {
    let textAlign: number = getEnumNumberByResource('alert_title_alignment');
    if (textAlign === TextAlign.Start) {
      this.titleTextAlign = TextAlign.Start;
    } else if (textAlign === TextAlign.Center) {
      this.titleTextAlign = TextAlign.Center;
    } else if (textAlign === TextAlign.End) {
      this.titleTextAlign = TextAlign.End;
    } else if (textAlign === TextAlign.JUSTIFY) {
      this.titleTextAlign = TextAlign.JUSTIFY;
    } else {
      this.titleTextAlign = TextAlign.Center;
    }
  }

  /**
   * get title area min height
   *
   * @returns min height
   */
  private getTitleAreaMinHeight(): ResourceStr | number {
    if (this.secondaryTitle) {
      return $r('sys.float.alert_title_secondary_height');
    } else if (this.primaryTitle) {
      return $r('sys.float.alert_title_primary_height');
    } else {
      return 0;
    }
  }
}

@Component
struct ButtonComponent {
  controller?: CustomDialogController;
  buttons?: ButtonOptions[];
  @State buttonMaxFontSize: Length = $r('sys.float.Body_L');
  @State buttonMinFontSize: Length = 9;
  keyIndex: number = 0;
  theme?: Theme | CustomTheme = new CustomThemeImpl({});
  @State singleButtonHeight: number = BUTTON_DEFAULT_HEIGHT;
  @State isButtonVertical: boolean = false;
  @Link fontSizeScale: number;
  @Link windowSize: Size;
  @Link buttonHeight: Length;
  @Link needResponseScale: boolean;

  build() {
    Column() {
      if (this.buttons && this.buttons.length > 0) {
        if (this.isButtonVertical) {
          this.buildVerticalAlignButtons();
        } else {
          this.buildHorizontalAlignButtons();
        }
      }
    }
    .width('100%')
    .padding(this.getOperationAreaPadding());
  }

  aboutToAppear(): void {
    this.updateFontSize();
    this.isButtonVertical = this.isVerticalAlignButton(Math.min(this.windowSize.width - BUTTON_HORIZONTAL_MARGIN * 2,
      MAX_DIALOG_WIDTH));
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>,
                constraint: ConstraintSizeOptions): SizeResult {
    let sizeResult: SizeResult = { width: selfLayoutInfo.width, height: selfLayoutInfo.height };
    this.updateFontSize();
    this.isButtonVertical = this.isVerticalAlignButton(Number(constraint.maxWidth));

    children.forEach((child) => {
      let measureResult: MeasureResult = child.measure(constraint);
      sizeResult.height = measureResult.height;
    });
    sizeResult.width = Number(constraint.maxWidth);
    this.buttonHeight = Number(sizeResult.height);
    return sizeResult;
  }

  /**
   * get operation area padding
   *
   * @returns padding
   */
  private getOperationAreaPadding(): Padding {
    if (this.isButtonVertical) {
      return {
        top: $r('sys.float.alert_button_top_padding'),
        right: $r('sys.float.alert_right_padding_vertical'),
        left: $r('sys.float.alert_left_padding_vertical'),
        bottom: $r('sys.float.alert_button_bottom_padding_vertical'),
      };
    }

    return {
      top: $r('sys.float.alert_button_top_padding'),
      right: $r('sys.float.alert_right_padding_horizontal'),
      left: $r('sys.float.alert_left_padding_horizontal'),
      bottom: $r('sys.float.alert_button_bottom_padding_horizontal'),
    };
  }

  @Builder
  buildSingleButton(buttonOptions: ButtonOptions): void {
    if (this.isNewPropertiesHighPriority(buttonOptions)) {
      Button(buttonOptions.value)
        .setButtonProperties(buttonOptions, this.controller)
        .role(buttonOptions.role ?? ButtonRole.NORMAL)
        .key(`advanced_dialog_button_${this.keyIndex++}`)
        .labelStyle({ maxLines: 1, maxFontSize: this.buttonMaxFontSize, minFontSize: this.buttonMinFontSize })
    } else if (buttonOptions.background !== undefined && buttonOptions.fontColor !== undefined) {
      Button(buttonOptions.value)
        .setButtonProperties(buttonOptions, this.controller)
        .backgroundColor(buttonOptions.background)
        .fontColor(buttonOptions.fontColor)
        .key(`advanced_dialog_button_${this.keyIndex++}`)
        .labelStyle({ maxLines: 1, maxFontSize: this.buttonMaxFontSize, minFontSize: this.buttonMinFontSize })
    } else if (buttonOptions.background !== undefined) {
      Button(buttonOptions.value)
        .setButtonProperties(buttonOptions, this.controller)
        .backgroundColor(buttonOptions.background)
        .key(`advanced_dialog_button_${this.keyIndex++}`)
        .labelStyle({ maxLines: 1, maxFontSize: this.buttonMaxFontSize, minFontSize: this.buttonMinFontSize })
    } else {
      Button(buttonOptions.value)
        .setButtonProperties(buttonOptions, this.controller)
        .fontColor(buttonOptions.fontColor)
        .key(`advanced_dialog_button_${this.keyIndex++}`)
        .labelStyle({ maxLines: 1, maxFontSize: this.buttonMaxFontSize, minFontSize: this.buttonMinFontSize })
    }
  }

  @Builder
  buildHorizontalAlignButtons(): void {
    if (this.buttons && this.buttons.length > 0) {
      Row() {
        this.buildSingleButton(this.buttons[0]);
        if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
          Divider()
            .width($r('sys.float.alert_divider_width'))
            .height($r('sys.float.alert_divider_height'))
            .color(this.getDividerColor())
            .vertical(true)
            .margin({
              left: $r('sys.float.alert_button_horizontal_space'),
              right: $r('sys.float.alert_button_horizontal_space'),
            });
          this.buildSingleButton(this.buttons[HORIZON_BUTTON_MAX_COUNT - 1]);
        }
      }
    }
  }

  @Builder
  buildVerticalAlignButtons(): void {
    if (this.buttons) {
      Column() {
        ForEach(this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT), (item: ButtonOptions, index: number) => {
          this.buildButtonWithDivider(index);
        }, (item: ButtonOptions) => item.value.toString());
      }
    }
  }

  /**
   * get divider color
   *
   * @returns divider color
   */
  private getDividerColor(): ResourceColor {
    if (!this.buttons || this.buttons.length === 0 || !getNumberByResource('dialog_divider_show')) {
      return Color.Transparent;
    }

    if (this.buttons[0].buttonStyle === ButtonStyleMode.TEXTUAL || this.buttons[0].buttonStyle === undefined) {
      if (this.buttons[HORIZON_BUTTON_MAX_COUNT - 1].buttonStyle === ButtonStyleMode.TEXTUAL ||
        this.buttons[HORIZON_BUTTON_MAX_COUNT - 1].buttonStyle === undefined) {
        return $r('sys.color.alert_divider_color');
      }
    }
    return Color.Transparent;
  }

  private updateFontSize(): void {
    if (this.needResponseScale) {
      if (this.fontSizeScale > MAX_FONT_SCALE && this.windowSize.height < MAX_WINDOW_HORIZONTAL_HEIGHT) {
        this.buttonMaxFontSize = BODY_L * MAX_FONT_SCALE + 'vp';
        this.buttonMinFontSize = BUTTON_MIN_FONT_SIZE * MAX_FONT_SCALE + 'vp';
      } else {
        this.buttonMaxFontSize = BODY_L + 'fp';
        this.buttonMinFontSize = BUTTON_MIN_FONT_SIZE + 'fp';
      }
    } else {
      this.buttonMaxFontSize = BODY_L + 'vp';
      this.buttonMinFontSize = BUTTON_MIN_FONT_SIZE + 'vp';
    }
  }

  /**
   * is button buttonStyle and role properties high priority
   *
   * @param buttonOptions button properties
   * @returns check result
   */
  private isNewPropertiesHighPriority(buttonOptions: ButtonOptions): boolean {
    if (buttonOptions.role === ButtonRole.ERROR) {
      return true;
    }
    if (buttonOptions.buttonStyle !== undefined &&
      buttonOptions.buttonStyle !== getNumberByResource('alert_button_style')) {
      return true;
    }
    if (buttonOptions.background === undefined && buttonOptions.fontColor === undefined) {
      return true;
    }
    return false;
  }

  @Builder
  buildButtonWithDivider(index: number): void {
    if (this.buttons && this.buttons[index]) {
      Row() {
        this.buildSingleButton(this.buttons[index]);
      }

      if (index < Math.min(this.buttons.length, VERTICAL_BUTTON_MAX_COUNT) - 1) {
        Row() {
        }
        .height($r('sys.float.alert_button_vertical_space'))
      }
    }
  }

  private isVerticalAlignButton(width: number): boolean {
    if (this.buttons) {
      if (this.buttons.length === 1) {
        return false;
      }
      if (this.buttons.length !== HORIZON_BUTTON_MAX_COUNT) {
        return true;
      }
      let isVertical: boolean = false;
      let maxButtonTextSize = vp2px(width / HORIZON_BUTTON_MAX_COUNT - BUTTON_HORIZONTAL_MARGIN -
        BUTTON_HORIZONTAL_SPACE - 2 * BUTTON_HORIZONTAL_PADDING);
      this.buttons.forEach((button) => {
        let contentSize: SizeOptions = measure.measureTextSize({
          textContent: button.value,
          fontSize: this.buttonMaxFontSize
        });
        if (Number(contentSize.width) > maxButtonTextSize) {
          isVertical = true;
        }
      });
      return isVertical;
    }
    return false;
  }
}

@Extend(Button)
function setButtonProperties(buttonOptions: ButtonOptions, controller?: CustomDialogController) {
  .onClick(() => {
    if (buttonOptions.action) {
      buttonOptions.action();
    }
    controller?.close();
  })
  .defaultFocus(true)
  .buttonStyle(buttonOptions.buttonStyle ?? getNumberByResource('alert_button_style'))
  .layoutWeight(BUTTON_LAYOUT_WEIGHT)
}

/**
 * get resource size
 *
 * @param resourceName resource name
 * @returns resource size
 */
function getNumberByResource(resourceName: string): number {
  try {
    return resourceManager.getSystemResourceManager().getNumberByName(resourceName);
  } catch (error) {
    let code: number = (error as BusinessError).code;
    let message: string = (error as BusinessError).message;
    hilog.error(0x3900, 'Ace', `CustomContentDialog getNumberByResource error, code: ${code}, message: ${message}`);
    return 0;
  }
}

/**
 * get enum number
 *
 * @param resourceName resource name
 * @returns number
 */
function getEnumNumberByResource(resourceName: string): number {
  try {
    return getContext().resourceManager.getNumberByName(resourceName);
  } catch (error) {
    let code: number = (error as BusinessError).code;
    let message: string = (error as BusinessError).message;
    hilog.error(0x3900, 'Ace', `getEnumNumberByResource error, code: ${code}, message: ${message}`);
    return -1;
  }
}

/**
 * resolve content area keyEvent
 *
 * @param event keyEvent
 * @param controller the controller of content area
 * @returns undefined
 */
function resolveKeyEvent(event: KeyEvent, controller: Scroller) {
  if (event.type == IGNORE_KEY_EVENT_TYPE) {
    return;
  }

  if (event.keyCode == KEYCODE_UP) {
    controller.scrollPage({ next: false });
    event.stopPropagation();
  } else if (event.keyCode == KEYCODE_DOWN) {
    if (controller.isAtEnd()) {
      return;
    } else {
      controller.scrollPage({ next: true });
      event.stopPropagation();
    }
  }
}

@CustomDialog
export struct LoadingDialog {
  controller: CustomDialogController;
  content?: ResourceStr = '';
  @State fontColorWithTheme: ResourceColor = $r('sys.color.font_primary');
  @State loadingProgressIconColorWithTheme: ResourceColor = $r('sys.color.icon_secondary');
  theme?: Theme | CustomTheme = new CustomThemeImpl({});
  themeColorMode?: ThemeColorMode = ThemeColorMode.SYSTEM;
  @State fontSizeScale: number = 1;
  @State windowSize: Size = { width: 0, height: 0 };

  build() {
    Column() {
      CustomDialogContentComponent({
        controller: this.controller,
        contentBuilder: () => {
          this.contentBuilder();
        },
        theme: this.theme,
        themeColorMode: this.themeColorMode,
        fontSizeScale: this.fontSizeScale,
        windowSize: this.windowSize
      }).constraintSize({ maxHeight: '100%' });
    }
  }

  @Builder
  contentBuilder() {
    Column() {
      Row() {
        Text(this.content)
          .fontSize(this.getFontSize())
          .fontWeight(FontWeight.Regular)
          .fontColor(this.fontColorWithTheme)
          .layoutWeight(LOADING_TEXT_LAYOUT_WEIGHT)
          .maxLines(this.fontSizeScale > MAX_FONT_SCALE ? LOADING_MAX_LINES_BIG_FONT : LOADING_MAX_LINES)
          .focusable(true)
          .defaultFocus(true)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
        LoadingProgress()
          .color(this.loadingProgressIconColorWithTheme)
          .width(LOADING_PROGRESS_WIDTH)
          .height(LOADING_PROGRESS_HEIGHT)
          .margin({ start: LengthMetrics.vp(LOADING_TEXT_MARGIN_LEFT) })
      }
      .constraintSize({ minHeight: LOADING_MIN_HEIGHT })
    }
  }

  getFontSize(): Length {
    if (this.fontSizeScale > MAX_FONT_SCALE && this.windowSize.height < MAX_WINDOW_HORIZONTAL_HEIGHT) {
      return BODY_L * MAX_FONT_SCALE + 'vp';
    } else {
      return BODY_L;
    }
  }

  aboutToAppear(): void {
    this.fontColorWithTheme = this.theme?.colors?.fontPrimary ?
    this.theme.colors.fontPrimary : $r('sys.color.font_primary');
    this.loadingProgressIconColorWithTheme = this.theme?.colors?.iconSecondary ?
    this.theme.colors.iconSecondary : $r('sys.color.icon_secondary');
  }
}

@Component
export struct PopupDialog {
  @Link show: boolean;
  @Prop popup: PopupDialogOptions;
  @BuilderParam targetBuilder: Callback<void>;

  build() {
    Column() {
      this.targetBuilder();
    }
    .onClick(() => {
      this.show = !this.show;
    })
    .bindPopup(this.show, {
      builder: this.popup?.builder,
      placement: this.popup?.placement ?? Placement.Bottom,
      popupColor: this.popup?.popupColor,
      enableArrow: this.popup?.enableArrow ?? true,
      autoCancel: this.popup?.autoCancel,
      onStateChange: this.popup?.onStateChange ?? ((e) => {
        if (!e.isVisible) {
          this.show = false
        }
      }),
      arrowOffset: this.popup?.arrowOffset,
      showInSubWindow: this.popup?.showInSubWindow,
      mask: this.popup?.mask,
      targetSpace: this.popup?.targetSpace,
      offset: this.popup?.offset,
      width: this.popup?.width,
      arrowPointPosition: this.popup?.arrowPointPosition,
      arrowWidth: this.popup?.arrowWidth,
      arrowHeight: this.popup?.arrowHeight,
      radius: this.popup?.radius ?? $r('sys.float.corner_radius_level16'),
      shadow: this.popup?.shadow ?? ShadowStyle.OUTER_DEFAULT_MD,
      backgroundBlurStyle: this.popup?.backgroundBlurStyle ?? BlurStyle.COMPONENT_ULTRA_THICK,
      focusable: this.popup?.focusable,
      transition: this.popup?.transition,
      onWillDismiss: this.popup?.onWillDismiss
    })
  }
}

export declare interface PopupDialogOptions extends CustomPopupOptions {}
