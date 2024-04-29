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
import { BusinessError } from '@ohos.base';
import display from '@ohos.display';
import hilog from '@ohos.hilog';
import measure from '@ohos.measure';
import resourceManager from '@ohos.resourceManager';

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
const LOADING_TEXT_LAYOUT_WEIGHT: number = 1;
const LOADING_TEXT_MARGIN_LEFT: number = 12;
const LOADING_MIN_HEIGHT: number = 48;
const LIST_MIN_HEIGHT: number = 48;
const CHECKBOX_CONTAINER_LENGTH: number = 20;
const TEXT_MIN_HEIGHT: number = 48;
const DEFAULT_IMAGE_SIZE: number = 64;
const KEYCODE_UP: number = 2012;
const KEYCODE_DOWN: number = 2013;
const IGNORE_KEY_EVENT_TYPE: number = 1;
const FIRST_ITEM_INDEX: number = 0;

@CustomDialog
export struct TipsDialog {
  controller: CustomDialogController;
  imageRes: Resource | null = null;
  @State imageSize?: SizeOptions = { width: DEFAULT_IMAGE_SIZE, height: DEFAULT_IMAGE_SIZE };
  title?: ResourceStr | null = null;
  content?: ResourceStr | null = null;
  checkAction?: (isChecked: boolean) => void;
  checkTips?: ResourceStr | null = null;
  @State isChecked?: boolean = false;
  primaryButton?: ButtonOptions | null = null;
  secondaryButton?: ButtonOptions | null = null;
  buttons?: ButtonOptions[] | undefined = undefined;
  @State imageSizeHeight: number = 0;
  @State textAlignment: TextAlign = TextAlign.Start;
  marginOffset: number = 0;
  @State checkBoxHeight: number = 0;
  buttonHeight: number = 0;
  // the controller of content area scroll
  contentScroller: Scroller = new Scroller();

  build() {
    CustomDialogComponent({
      controller: this.controller,
      contentBuilder: () => {
        this.contentBuilder();
      },
      buttons: this.buttons,
    })
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
        })
        .margin({ right: $r('sys.float.padding_level4') })
      Text(content)
        .fontSize($r('sys.float.Body_M'))
        .fontWeight(FontWeight.Regular)
        .fontColor($r('sys.color.font_primary'))
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
    .constraintSize({minHeight: CHECKBOX_CONTAINER_HEIGHT})
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
              .fontSize($r('sys.float.Title_S'))
              .fontWeight(FontWeight.Medium)
              .fontColor($r('sys.color.font_primary'))
              .textAlign(TextAlign.Center)
              .maxLines(CONTENT_MAX_LINES)
              .textOverflow({ overflow: TextOverflow.Ellipsis })
              .minFontSize($r('sys.float.Body_L'))
              .maxFontSize($r('sys.float.Title_S'))
              .width('100%')
          }
          .padding({ bottom: $r('sys.float.padding_level8') })
        }
        if (this.content != null) {
          Row() {
            Text(this.content)
              .focusable(true)
              .defaultFocus(!(this.primaryButton || this.secondaryButton))
              .fontSize($r('sys.float.Body_L'))
              .fontWeight(FontWeight.Medium)
              .fontColor($r('sys.color.font_primary'))
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
    this.initButtons();
    this.initMargin();
  }

  private getTextAlign(maxWidth: number): void {
    let contentSize: SizeOptions = measure.measureTextSize({
      textContent: this.content,
      fontSize: $r('sys.float.Body_L'),
      constraintWidth: maxWidth,
    });
    let oneLineSize: SizeOptions = measure.measureTextSize({
      textContent: this.content,
      fontSize: $r('sys.float.Body_L'),
    });
    if (this.getTextHeight(contentSize) <= this.getTextHeight(oneLineSize)) {
      this.textAlignment = TextAlign.Center;
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
    this.buttonHeight = this.getButtonsHeight();
  }

  private getButtonsHeight(): number {
    if (!this.buttons || this.buttons.length === 0) {
      return 0;
    }
    let buttonsHeight: number = getNumberByResource('alert_button_top_padding');
    buttonsHeight += BUTTON_DEFAULT_HEIGHT + getNumberByResource('alert_button_bottom_padding_horizontal');
    return buttonsHeight;
  }

  private initMargin(): void {
    this.marginOffset = 0 - getNumberByResource('padding_level8');
  }
}

@CustomDialog
export struct SelectDialog{
  title: ResourceStr = '';
  content?: ResourceStr = '';
  selectedIndex?: number = -1;
  confirm?: ButtonOptions | null = null;
  radioContent: Array<SheetInfo> = [];
  buttons?: ButtonOptions[] = [];
  contentPadding ?: Padding;
  @BuilderParam contentBuilder: () => void = this.buildContent;
  controller: CustomDialogController = new CustomDialogController({
    builder: CustomContentDialog({
      primaryTitle: this.title,
      contentBuilder: () => {
        this.contentBuilder();
      },
      buttons: this.buttons,
    })
  });
  // the controller of content list
  contentScroller: Scroller = new Scroller();
  
  @Styles paddingContentStyle() {
    .padding({
      left: $r('sys.float.padding_level12'),
      right: $r('sys.float.padding_level12'),
      bottom: $r('sys.float.padding_level4')
    })
  }

  @Styles paddingStyle() {
    .padding({
      left: $r('sys.float.padding_level6'),
      right: $r('sys.float.padding_level6')
    })
  }

  @Builder
  buildContent() : void {
    Scroll(this.contentScroller) {
      Column() {
        if (this.content) {
          Row() {
            Text(this.content)
              .fontSize($r('sys.float.Body_M'))
              .fontWeight(FontWeight.Regular)
              .fontColor($r('sys.color.font_primary'))
              .textOverflow({overflow: TextOverflow.Ellipsis})
          }.paddingContentStyle().width('100%')
        }
        List({ space: 1 }) {
          ForEach(this.radioContent, (item: SheetInfo, index?: number) => {
            ListItem() {
              Column() {
                Button() {
                  Row() {
                    Text(item.title)
                      .fontSize($r('sys.float.Body_L'))
                      .fontWeight(FontWeight.Medium)
                      .fontColor($r('sys.color.font_primary'))
                      .layoutWeight(1)
                    Radio({ value: 'item.title', group: 'radioGroup' })
                      .size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH })
                      .checked(this.selectedIndex === index)
                      .hitTestBehavior(HitTestMode.None)
                      .id(String(index))
                      .onFocus(() => {
                        if (index == FIRST_ITEM_INDEX) {
                          this.contentScroller.scrollEdge(Edge.Top);
                        } else if (index == this.radioContent.length - 1) {
                          this.contentScroller.scrollEdge(Edge.Bottom);
                        }
                      })
                  }.constraintSize({ minHeight: LIST_MIN_HEIGHT }).clip(false)
                  .padding({ top: $r('sys.float.padding_level4'), bottom: $r('sys.float.padding_level4') })
                }.type(ButtonType.Normal).borderRadius($r('sys.float.corner_radius_level8'))
                .buttonStyle(ButtonStyleMode.TEXTUAL).paddingStyle()
                .onClick(() => {
                  item.action && item.action();
                  this.controller.close();
                })
                if (index < this.radioContent.length - 1) {
                  Divider().color($r('sys.color.comp_divider')).paddingStyle()
                }
              }.paddingStyle()
            }
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
  }

  build() {
    CustomDialogComponent({
      controller: this.controller,
      primaryTitle: this.title,
      contentBuilder: () => {
        this.contentBuilder();
      },
      buttons: this.buttons,
      contentAreaPadding: this.contentPadding
    })
  }

  aboutToAppear(): void {
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
}

@CustomDialog
export struct ConfirmDialog{
  controller: CustomDialogController
  title: ResourceStr = ''
  content?: ResourceStr = ''
  checkTips?: ResourceStr = ''
  @State isChecked?: boolean = false
  primaryButton?: ButtonOptions = {value: ""}
  secondaryButton?: ButtonOptions = {value: ""}

  build() {
      Column() {
        Row() {
          Text(this.title)
            .fontSize($r('sys.float.ohos_id_text_size_dialog_tittle'))
            .fontWeight(FontWeight.Medium)
            .maxLines(CONTENT_MAX_LINES)
            .minFontSize(15)
            .textOverflow({ overflow: TextOverflow.Ellipsis})
            .fontColor($r('sys.color.ohos_id_color_text_primary'))
            .textAlign(TextAlign.Start)
            .width('100%')
        }.padding({ left: 24, right: 24, top: 24 })
        .constraintSize({minHeight: 56})
        if (this.content) {
          Row() {
            Text(this.content)
              .focusable(true)
              .defaultFocus(!(this.primaryButton?.value || this.secondaryButton?.value))
              .fontSize($r('sys.float.ohos_id_text_size_body1'))
              .fontWeight(FontWeight.Medium)
              .fontColor($r('sys.color.ohos_id_color_text_primary'))
              .maxLines(CONTENT_MAX_LINES)
              .textOverflow({ overflow: TextOverflow.Ellipsis})
              .minFontSize($r('sys.float.ohos_id_text_size_body3'))
          }.padding({ left: 24, right: 24, top: 8, bottom: 8 })
          .width('100%')
          .constraintSize({minHeight: 36})
        }
        Row() {
          Checkbox({ name: 'checkbox', group: 'checkboxGroup' }).select(this.isChecked)
            .onChange((checked: boolean) => {
              this.isChecked = checked
            })
            .margin({ left: 0, right: 8})
          Text(this.checkTips).fontSize($r('sys.float.ohos_id_text_size_body2'))
            .fontWeight(FontWeight.Medium)
            .fontColor($r('sys.color.ohos_id_color_text_primary'))
            .maxLines(CONTENT_MAX_LINES)
            .layoutWeight(1)
            .focusable(false)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .onClick(() => {
              this.isChecked = !this.isChecked
            })
        }.height(CHECKBOX_CONTAINER_HEIGHT).width('100%').padding({ left: 24, right: 24 , top: 8, bottom: 8 })

        Row() {
          if (this.primaryButton.value) {
            Button(this.primaryButton.value)
              .fontSize($r('sys.float.ohos_id_text_size_button1'))
              .fontWeight(FontWeight.Medium)
              .layoutWeight(1)
              .defaultFocus(true)
              .backgroundColor(this.primaryButton.background? this.primaryButton.background: $r('sys.color.ohos_id_color_background_transparent'))
              .fontColor(this.primaryButton.fontColor ? this.primaryButton.fontColor: $r('sys.color.ohos_id_color_text_primary_activated'))
              .onClick(() => {
                if (this.primaryButton.action) this.primaryButton.action()
                this.controller.close()
              })
          }
          if (this.secondaryButton.value && this.primaryButton.value) {
            Column() {
              if (!this.secondaryButton.background) {
                Divider().width(DIVIDER_WIDTH).height(DIVIDER_HEIGHT).color($r('sys.color.ohos_id_color_list_separator')).vertical(true)
              }
            }.width(DIVIDER_CONTAINER_WIDTH).alignItems(HorizontalAlign.Center)
          }
          if (this.secondaryButton.value) {
            Button(this.secondaryButton.value)
              .fontSize($r('sys.float.ohos_id_text_size_button1'))
              .fontWeight(FontWeight.Medium)
              .layoutWeight(1)
              .defaultFocus(true)
              .backgroundColor(this.secondaryButton.background? this.secondaryButton.background: $r('sys.color.ohos_id_color_background_transparent'))
              .fontColor(this.secondaryButton.fontColor ? this.secondaryButton.fontColor: $r('sys.color.ohos_id_color_text_primary_activated'))
              .onClick(() => {
                if (this.secondaryButton.action) this.secondaryButton.action()
                this.controller.close()
              })
          }
        }.width('100%').padding({ left: 16, right: 16, top: 16, bottom: 16 })
      }
      .backgroundBlurStyle(BlurStyle.Thick)
      .borderRadius($r('sys.float.ohos_id_corner_radius_dialog'))
      .margin({
        left: $r('sys.float.ohos_id_dialog_margin_start'),
        right: $r('sys.float.ohos_id_dialog_margin_end'),
        bottom: $r('sys.float.ohos_id_dialog_margin_bottom')
      })
      // 1.backgroundcolor use in blur enable mod mast set this color: colorDialogBgBlur. but now it is not found
      .backgroundColor($r('sys.color.ohos_id_color_dialog_bg'))
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

  build() {
    CustomDialogComponent({
      primaryTitle: this.primaryTitle,
      secondaryTitle: this.secondaryTitle,
      controller: this.controller,
      contentBuilder: () => {
        this.AlertDialogContentBuilder();
      },
      buttons: this.buttons,
    })
  }

  @Builder
  AlertDialogContentBuilder(): void {
    Column() {
      Scroll(this.contentScroller) {
        Text(this.content)
          .focusable(true)
          .defaultFocus(!(this.primaryButton || this.secondaryButton))
          .fontSize($r('sys.float.Body_L'))
          .fontWeight(this.getFontWeight())
          .fontColor($r('sys.color.font_primary'))
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
    this.initButtons();
  }

  private getTextAlign(maxWidth: number): void {
    let contentSize: SizeOptions = measure.measureTextSize({
      textContent: this.content,
      fontSize: $r('sys.float.Body_L'),
      constraintWidth: maxWidth,
    });
    let oneLineSize: SizeOptions = measure.measureTextSize({
      textContent: this.content,
      fontSize: $r('sys.float.Body_L'),
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
    });
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

  @Builder
  defaultContentBuilder(): void {
  }

  titleHeight: number = 0;
  @State contentMaxHeight: string = '';

  build() {
    Column() {
      // title area
      this.buildTitles();

      // content area
      Column() {
        this.contentBuilder();
      }
      .padding(this.getContentPadding())
      .constraintSize({ maxHeight: this.contentMaxHeight, })

      // operation area
      this.buildButtons();
    }
    .width('100%')
  }

  @Builder
  buildTitles(): void {
    Column() {
      Row() {
        Text(this.primaryTitle)
          .fontWeight(FontWeight.Bold)
          .fontColor($r('sys.color.font_primary'))
          .textAlign(this.getTitleTextAlign())
          .maxFontSize($r('sys.float.Title_S'))
          .minFontSize($r('sys.float.Body_L'))
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
          .fontColor($r('sys.color.font_secondary'))
          .textAlign(this.getTitleTextAlign())
          .maxFontSize($r('sys.float.Subtitle_S'))
          .minFontSize($r('sys.float.Body_S'))
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
    .onAreaChange((oldValue: Area, newValue: Area) => {
      this.titleHeight = Number(newValue.height);
      this.contentMaxHeight = `calc(100% - ${this.titleHeight}vp - ${this.getButtonsHeight()}vp)`;
    });
  }

  @Builder
  buildButtons(): void {
    Column() {
      this.buildHorizontalAlignButtons();
      this.buildVerticalAlignButtons();
    }
    .width('100%')
    .padding(this.getOperationAreaPadding());
  }

  @Builder
  buildSingleButton(buttonOptions: ButtonOptions): void {
    if (this.isNewPropertiesHighPriority(buttonOptions)) {
      Button(buttonOptions.value)
        .setButtonProperties(buttonOptions, this.controller)
        .role(buttonOptions.role ?? ButtonRole.NORMAL)
        .key(`advanced_dialog_button_${this.keyIndex++}`)
    } else if (buttonOptions.background !== undefined && buttonOptions.fontColor !== undefined) {
      Button(buttonOptions.value)
        .setButtonProperties(buttonOptions, this.controller)
        .backgroundColor(buttonOptions.background)
        .fontColor(buttonOptions.fontColor)
        .key(`advanced_dialog_button_${this.keyIndex++}`)
    } else if (buttonOptions.background !== undefined) {
      Button(buttonOptions.value)
        .setButtonProperties(buttonOptions, this.controller)
        .backgroundColor(buttonOptions.background)
        .key(`advanced_dialog_button_${this.keyIndex++}`)
    } else {
      Button(buttonOptions.value)
        .setButtonProperties(buttonOptions, this.controller)
        .fontColor(buttonOptions.fontColor)
        .key(`advanced_dialog_button_${this.keyIndex++}`)
    }
  }

  @Builder
  buildHorizontalAlignButtons(): void {
    if (this.buttons && this.buttons.length > 0 && this.buttons.length <= HORIZON_BUTTON_MAX_COUNT) {
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
    if (this.buttons && this.isVerticalAlignButton()) {
      Column() {
        ForEach(this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT), (item: ButtonOptions, index: number) => {
          this.buildButtonWithDivider(index);
        }, (item: ButtonOptions) => item.value.toString());
      }
    }
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

  aboutToAppear(): void {
    if (this.primaryTitle) {
      this.titleHeight = getNumberByResource('alert_title_primary_height');
    }
    if (this.secondaryTitle) {
      this.titleHeight = getNumberByResource('alert_title_secondary_height');
    }
    this.contentMaxHeight = `calc(100% - ${this.titleHeight}vp - ${this.getButtonsHeight()}vp)`;
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

    if (this.buttons[0].buttonStyle !== ButtonStyleMode.TEXTUAL ||
      this.buttons[HORIZON_BUTTON_MAX_COUNT - 1].buttonStyle !== ButtonStyleMode.TEXTUAL) {
      return Color.Transparent;
    } else {
      return $r('sys.color.alert_divider_color');
    }
  }

  /**
   * get dialog buttons total height
   *
   * @returns buttons total height
   */
  private getButtonsHeight(): number {
    if (!this.buttons || this.buttons.length === 0) {
      return 0;
    }
    let buttonsHeight: number = getNumberByResource('alert_button_top_padding');
    if (this.buttons.length <= HORIZON_BUTTON_MAX_COUNT) {
      buttonsHeight += BUTTON_DEFAULT_HEIGHT +
      getNumberByResource('alert_button_bottom_padding_horizontal');
    } else {
      buttonsHeight += BUTTON_DEFAULT_HEIGHT * this.buttons.length +
        (this.buttons.length - 1) * getNumberByResource('alert_button_vertical_space') +
      getNumberByResource('alert_button_bottom_padding_vertical');
    }

    return buttonsHeight;
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
   * check button vertical align or not
   *
   * @returns check result
   */
  private isVerticalAlignButton(): boolean {
    if (this.buttons) {
      return this.buttons.length > HORIZON_BUTTON_MAX_COUNT;
    }
    return false;
  }

  /**
   * get operation area padding
   *
   * @returns padding
   */
  private getOperationAreaPadding(): Padding {
    if (this.isVerticalAlignButton()) {
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

  /**
   * get tile TextAlign
   * @returns TextAlign
   */
  private getTitleTextAlign(): TextAlign {
    let textAlign: number = getEnumNumberByResource('alert_title_alignment');
    if (textAlign === TextAlign.Start) {
      return TextAlign.Start;
    } else if (textAlign === TextAlign.Center) {
      return TextAlign.Center;
    } else if (textAlign === TextAlign.End) {
      return TextAlign.End;
    } else if (textAlign === TextAlign.JUSTIFY) {
      return TextAlign.JUSTIFY;
    } else {
      return TextAlign.Center;
    }
  }
}

@Component
export struct CustomDialogComponent {
  controller?: CustomDialogController;
  primaryTitle?: ResourceStr;
  secondaryTitle?: ResourceStr;
  @BuilderParam contentBuilder: () => void;
  buttons?: ButtonOptions[];
  contentAreaPadding?: Padding;
  screenWidth: number = 0;
  @State columnModifier: ColumnModifier = new ColumnModifier();
  isFirstInit: boolean = true;

  build() {
    Column() {
      Column() {
        CustomDialogContentComponent({
          controller: this.controller,
          primaryTitle: this.primaryTitle,
          secondaryTitle: this.secondaryTitle,
          contentBuilder: () => {
            this.contentBuilder();
          },
          buttons: this.buttons,
          contentAreaPadding: this.contentAreaPadding,
        })
      }
      .attributeModifier(this.columnModifier)
    }
    .onAreaChange((oldValue: Area, newValue: Area) => {
      if (!this.isFirstInit) {
        return;
      }
      if (this.screenWidth > getNumberByResource('alert_container_max_width')) {
        this.columnModifier.customStyle = newValue.width > getNumberByResource('alert_container_max_width');
      } else {
        this.columnModifier.customStyle = newValue.width >= this.screenWidth;
      }
      this.isFirstInit = false;
    })
  }

  aboutToAppear(): void {
    try {
      this.screenWidth = px2vp(display.getDefaultDisplaySync().width);
    } catch (error) {
      hilog.error(0x3900, 'Ace', `CustomDialogComponent getDefaultDisplaySync error: ${JSON.stringify(error)}`);
    }
  }
}

class ColumnModifier implements AttributeModifier<ColumnAttribute> {
  public customStyle: boolean = false;

  applyNormalAttribute(instance: ColumnAttribute): void {
    if (!this.customStyle) {
      return;
    }
    instance.backgroundBlurStyle(BlurStyle.Thick);
    instance.borderRadius($r('sys.float.ohos_id_corner_radius_dialog'));
    instance.margin({
      left: $r('sys.float.ohos_id_dialog_margin_start'),
      right: $r('sys.float.ohos_id_dialog_margin_end'),
      bottom: $r('sys.float.ohos_id_dialog_margin_bottom'),
    });
    instance.backgroundColor($r('sys.color.ohos_id_color_dialog_bg'));
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

  build() {
    Column() {
      CustomDialogComponent({
        controller: this.controller,
        contentBuilder: () => {
          this.contentBuilder();
        },
      })
    }
  }

  @Builder
  contentBuilder() {
    Column() {
      Row() {
        Text(this.content)
          .fontSize($r('sys.float.Body_L'))
          .fontWeight(FontWeight.Regular)
          .fontColor($r('sys.color.font_primary'))
          .layoutWeight(LOADING_TEXT_LAYOUT_WEIGHT)
          .maxLines(LOADING_MAX_LINES)
          .focusable(true)
          .defaultFocus(true)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
        LoadingProgress()
          .color($r('sys.color.icon_secondary'))
          .width(LOADING_PROGRESS_WIDTH)
          .height(LOADING_PROGRESS_HEIGHT)
          .margin({ left: LOADING_TEXT_MARGIN_LEFT })
      }
      .constraintSize({ minHeight: LOADING_MIN_HEIGHT })
    }
  }
}
