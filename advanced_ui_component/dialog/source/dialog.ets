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
 
import { BusinessError } from '@ohos.base';
import hilog from '@ohos.hilog';
import resourceManager from '@ohos.resourceManager';
import measure from '@ohos.measure';

const TITLE_MAX_LINES: number = 2;
const HORIZON_BUTTON_MAX_COUNT: number = 2;
const VERTICAL_BUTTON_MAX_COUNT: number = 4;
const BUTTON_DEFAULT_HEIGHT: number = 40;
const BUTTON_LAYOUT_WEIGHT: number = 1;
const CHECKBOX_CONTAINER_HEIGHT: number = 48
const CONTENT_MAX_LINES: number = 2
const DIVIDER_CONTAINER_WIDTH: number = 16
const DIVIDER_HEIGHT: number = 24
const DIVIDER_WIDTH: number = 2
const LOADING_PROGRESS_WIDTH: number = 40
const LOADING_PROGRESS_HEIGHT: number = 40
const ITEM_TEXT_SIZE: number = 14
const LOADING_MAX_LINES: number = 10;
const LOADING_TEXT_LAYOUT_WEIGHT: number = 1;
const LOADING_TEXT_MARGIN_LEFT: number = 12;
const LOADING_MIN_HEIGHT: number = 48;
const LIST_MIN_HEIGHT: number = 48
const CHECKBOX_CONTAINER_LENGTH: number = 20
export declare type ButtonOptions = {
  value: ResourceStr;
  action?: () => void;
  background?: ResourceColor;
  fontColor?: ResourceColor;
  buttonStyle?: ButtonStyleMode;
  role?: ButtonRole;
}

@CustomDialog
export struct TipsDialog{
  controller: CustomDialogController
  imageRes: Resource
  imageSize: SizeOptions = {width: '100%', height: 180}
  title: ResourceStr = ''
  content?: ResourceStr = ''
  checkTips?: ResourceStr = ''
  @State isChecked?: boolean = false
  primaryButton?: ButtonOptions = {value: ""}
  secondaryButton?: ButtonOptions = {value: ""}

  build() {
    Column() {
      Row() {
        Column() {
          Image(this.imageRes)
            .size(this.imageSize)
            .objectFit(ImageFit.Fill)
        }.layoutWeight(1)
        .clip(true)
      }.width('100%')
      .padding({ left: 24, right: 24})
      .margin({top: 24})
      Row() {
        Text(this.title)
          .fontSize($r('sys.float.ohos_id_text_size_headline8'))
          .fontWeight(FontWeight.Medium)
          .fontColor($r('sys.color.ohos_id_color_text_primary'))
          .textAlign(TextAlign.Center)
          .maxLines(CONTENT_MAX_LINES)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .minFontSize(15)
          .maxFontSize($r('sys.float.ohos_id_text_size_headline8'))
      }.padding({ left: 24, right: 24 })
      .margin({top: 16})
      if (this.content) {
        Row() {
          Text(this.content)
            .fontSize($r('sys.float.ohos_id_text_size_body1'))
            .fontWeight(FontWeight.Regular)
            .fontColor($r('sys.color.ohos_id_color_text_primary'))
            .textAlign(TextAlign.Center)
            .minFontSize($r('sys.float.ohos_id_text_size_body3'))
            .maxLines(CONTENT_MAX_LINES)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
        }.padding({ left: 24, right: 24, top: 8, bottom: 8 })
        .width('100%')
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
          .focusOnTouch(true)
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
export struct SelectDialog{
  title: ResourceStr = '';
  content?: ResourceStr = '';
  selectedIndex?: number = -1;
  confirm?: ButtonOptions = {value: ""};
  radioContent: Array<SheetInfo> = [];
  @BuilderParam contentBuilder: () => void = this.buildContent;
  controller: CustomDialogController = new CustomDialogController({
    builder: CustomContentDialog({
      primaryTitle: this.title,
      contentBuilder: () => {
        this.contentBuilder();
      },
      buttons: (this.confirm === undefined || this.confirm?.value === "") ? [] : [this.confirm],
    })
  });

  @Builder
  buildContent() : void {
    Scroll() {
      Column() {
        if (this.content) {
          Row() {
            Text(this.content)
              .fontSize($r('sys.float.Body_M'))
              .fontWeight(FontWeight.Regular)
              .fontColor($r('sys.color.font_primary'))
              .textOverflow({overflow: TextOverflow.Ellipsis})
          }.padding({bottom: $r('sys.float.padding_level4')})
          .width('100%')
        }
        List({space: 1}) {
          ForEach(this.radioContent, (item: SheetInfo, index?: number) => {
            ListItem() {
              Column() {
                Row() {
                  Text(item.title)
                    .fontSize($r('sys.float.Body_L'))
                    .fontWeight(FontWeight.Medium)
                    .fontColor($r('sys.color.font_primary'))
                    .layoutWeight(1)
                  Radio({value: 'item.title', group: 'radioGroup'})
                    .size({width : CHECKBOX_CONTAINER_LENGTH, height : CHECKBOX_CONTAINER_LENGTH})
                    .checked(this.selectedIndex == index)
                    .onClick(() => {
                      item.action && item.action()
                      this.controller.close()
                    })
                }.constraintSize({minHeight: LIST_MIN_HEIGHT}).clip(false)
                .padding({ top: $r('sys.float.padding_level4'), bottom: $r('sys.float.padding_level4') })
                .onClick(() => {
                  item.action && item.action()
                  this.controller.close()
                })
                if (index < this.radioContent.length - 1) {
                  Divider().color($r('sys.color.comp_divider'))
                }
              }
            }
          })
        }.width('100%').clip(false)
      }.padding({right: $r('sys.float.padding_level8')})
    }.margin({right: -getNumberByResource('padding_level8')})
    .scrollBar(BarState.Auto)
  }

  build() {
    CustomDialogContentComponent({
      controller: this.controller,
      primaryTitle: this.title,
      contentBuilder: () => {
        this.contentBuilder();
      },
      buttons: (this.confirm === undefined || this.confirm.value === "") ? [] : [this.confirm],
    })
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
            .focusOnTouch(true)
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
  content: ResourceStr = '';
  primaryButton?: ButtonOptions | null = null;
  secondaryButton?: ButtonOptions | null = null;
  buttons?: ButtonOptions[] | undefined = undefined;

  build() {
    CustomDialogContentComponent({
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
      Scroll() {
        Text(this.content)
          .fontSize($r('sys.float.Body_L'))
          .fontWeight(FontWeight.Medium)
          .fontColor($r('sys.color.font_primary'))
          .margin({ right: $r('sys.float.padding_level8'), })
          .width(`calc(100% - ${getNumberByResource('padding_level8')}vp)`)
          .textAlign(this.getTextAlign())
      }
      .width('100%')
    }
    .margin({ right: `${this.getMargin()}vp`, })
  }

  aboutToAppear(): void {
    this.initButtons();
  }

  private getTextAlign(): TextAlign {
    let contentSize: SizeOptions = measure.measureTextSize({
      textContent: this.content,
      fontSize: $r('sys.float.Body_L'),
    });
    let oneLineSize: SizeOptions = measure.measureTextSize({
      textContent: '1',
      fontSize: $r('sys.float.Body_L'),
    });

    if (this.getTextHeight(contentSize) <= this.getTextHeight(oneLineSize)) {
      return TextAlign.Center;
    }
    return TextAlign.Start;
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
}

@CustomDialog
export struct CustomContentDialog {
  controller: CustomDialogController;
  primaryTitle?: ResourceStr;
  secondaryTitle?: ResourceStr;
  @BuilderParam contentBuilder: () => void;
  buttons?: ButtonOptions[];

  build() {
    CustomDialogContentComponent({
      controller: this.controller,
      primaryTitle: this.primaryTitle,
      secondaryTitle: this.secondaryTitle,
      contentBuilder: () => {
        this.contentBuilder();
      },
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

  @Builder
  defaultContentBuilder(): void {
  }

  titleHeight: number = 0;
  @State contentMaxHeight: string = '';

  build() {
    Column() {
      // title area
      if (this.primaryTitle || this.secondaryTitle) {
        this.buildTitles();
      }

      // content area
      Column() {
        this.contentBuilder();
      }
      .padding(this.getContentPadding())
      .constraintSize({ maxHeight: this.contentMaxHeight, })

      // operation area
      if (this.buttons && this.buttons.length > 0) {
        this.buildButtons();
      }
    }
    .width('100%')
  }

  @Builder
  buildTitles(): void {
    Column() {
      if (this.primaryTitle) {
        Row() {
          Text(this.primaryTitle)
            .fontWeight(FontWeight.Bold)
            .fontColor($r('sys.color.font_primary'))
            .textAlign(TextAlign.Start)
            .maxFontSize($r('sys.float.Title_S'))
            .minFontSize($r('sys.float.Body_L'))
            .maxLines(TITLE_MAX_LINES)
            .heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
        }
        .width('100%')

        if (this.secondaryTitle) {
          Row() {
            Divider().margin($r('sys.float.padding_level1')).color(Color.Transparent)
          }
        }
      }

      if (this.secondaryTitle) {
        Row() {
          Text(this.secondaryTitle)
            .fontWeight(FontWeight.Regular)
            .fontColor($r('sys.color.font_secondary'))
            .textAlign(TextAlign.Start)
            .maxFontSize($r('sys.float.Subtitle_S'))
            .minFontSize($r('sys.float.Body_S'))
            .maxLines(TITLE_MAX_LINES)
            .heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
        }
        .width('100%')
      }
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
      if (this.buttons && this.buttons.length > 0 && this.buttons.length <= HORIZON_BUTTON_MAX_COUNT) {
        Row() {
          this.buildSingleButton(this.buttons[0]);
          if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
            Divider()
              .width($r('sys.float.alert_divider_width'))
              .height($r('sys.float.alert_divider_height'))
              .color($r('sys.color.alert_divider_color'))
              .vertical(true)
              .margin({
                left: $r('sys.float.alert_button_horizontal_space'),
                right: $r('sys.float.alert_button_horizontal_space'),
              });

            this.buildSingleButton(this.buttons[HORIZON_BUTTON_MAX_COUNT-1]);
          }
        }
      }

      if (this.isVerticalAlignButton()) {
        Column() {
          ForEach(this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT - 1), (item: ButtonOptions, index: number) => {
            this.buildButtonWithDivider(index);
          }, (item: ButtonOptions) => item.value.toString());
          if (this.buttons.length >= VERTICAL_BUTTON_MAX_COUNT) {
            Row() {
              this.buildSingleButton(this.buttons[VERTICAL_BUTTON_MAX_COUNT-1]);
            }
          }
        }
      }
    }
    .width('100%')
    .padding(this.getOperationAreaPadding());
  }

  @Builder
  buildSingleButton(buttonOptions: ButtonOptions): void {
    Button(buttonOptions.value)
      .onClick(() => {
        if (buttonOptions.action) {
          buttonOptions.action();
        }
        this.controller?.close();
      })
      .buttonStyle(buttonOptions.buttonStyle ?? getNumberByResource('alert_button_style'))
      .role(buttonOptions.role ?? ButtonRole.NORMAL)
      .layoutWeight(BUTTON_LAYOUT_WEIGHT)
  }

  @Builder
  buildButtonWithDivider(index: number): void {
    if (this.buttons && this.buttons[index]) {
      Row() {
        this.buildSingleButton(this.buttons[index]);
      }

      if (index < this.buttons.length - 1) {
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
      buttonsHeight += BUTTON_DEFAULT_HEIGHT
        + getNumberByResource('alert_button_bottom_padding_horizontal');
    } else {
      buttonsHeight += BUTTON_DEFAULT_HEIGHT * this.buttons.length
        + (this.buttons.length - 1) * getNumberByResource('alert_button_vertical_space')
        + getNumberByResource('alert_button_bottom_padding_vertical');
    }

    return buttonsHeight;
  }

  /**
   * get dialog content padding
   *
   * @returns content padding
   */
  private getContentPadding(): Padding {
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
    } else {
      return {
        top: 0,
        right: $r('sys.float.alert_title_padding_right'),
        left: $r('sys.float.alert_title_padding_left'),
        bottom: 0,
      };
    }
  }

  /**
   * check button vertical align or not
   *
   * @returns check result
   */
  private isVerticalAlignButton(): boolean {
    return this.buttons && this.buttons.length > HORIZON_BUTTON_MAX_COUNT;
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
    } else {
      return {
        top: $r('sys.float.alert_button_top_padding'),
        right: $r('sys.float.alert_right_padding_horizontal'),
        left: $r('sys.float.alert_left_padding_horizontal'),
        bottom: $r('sys.float.alert_button_bottom_padding_horizontal'),
      };
    }
  }
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

@CustomDialog
export struct LoadingDialog {
  controller: CustomDialogController;
  content?: ResourceStr = '';

  build() {
    Column() {
      CustomDialogContentComponent({
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