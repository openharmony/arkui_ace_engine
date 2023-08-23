/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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
 
const CHECKBOX_CONTAINER_HEIGHT: number = 48
const CONTENT_MAX_LINES: number = 2
const DIVIDER_CONTAINER_WIDTH: number = 16
const DIVIDER_HEIGHT: number = 24
const DIVIDER_WIDTH: number = 2
const LOADING_PROGRESS_WIDTH: number = 40
const LOADING_PROGRESS_HEIGHT: number = 48
const ITEM_TEXT_SIZE: number = 14
export declare type ButtonOptions = {
  value: ResourceStr;
  action?: () => void;
  background?: ResourceColor;
  fontColor?: ResourceColor;
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
  controller: CustomDialogController
  title: ResourceStr = ''
  content?: ResourceStr = ''
  selectedIndex?: number = -1
  confirm?: ButtonOptions = {value: ""}
  radioContent: Array<SheetInfo> = []

  build() {
      Column() {
        Row() {
          Text(this.title)
            .fontSize($r('sys.float.ohos_id_text_size_dialog_tittle'))
            .fontWeight(FontWeight.Medium)
            .maxLines(CONTENT_MAX_LINES)
            .minFontSize($r('sys.float.ohos_id_text_size_sub_title1'))
            .textOverflow({ overflow: TextOverflow.Ellipsis})
            .fontColor($r('sys.color.ohos_id_color_text_primary'))
            .textAlign(TextAlign.Start)
            .width('100%')
        }.padding({ left: 24, right: 24, top: 24 })
        .constraintSize({minHeight: 56})
        if (this.content) {
          Row() {
            Text(this.content)
              .fontSize($r('sys.float.ohos_id_text_size_body2'))
              .fontWeight(FontWeight.Medium)
              .fontColor($r('sys.color.ohos_id_color_text_primary'))
              .maxLines(CONTENT_MAX_LINES)
              .textOverflow({ overflow: TextOverflow.Ellipsis})
              .minFontSize($r('sys.float.ohos_id_text_size_body3'))
          }.padding({ left: 24, right: 24, top: 8, bottom: 8 })
          .width('100%')
        }
        List({space: 1}) {
          ForEach(this.radioContent, (item: SheetInfo, index?: number) => {
            ListItem() {
              Column() {
                Row() {
                  Text(item.title)
                    .fontSize(ITEM_TEXT_SIZE)
                    .fontWeight(FontWeight.Medium)
                    .maxLines(CONTENT_MAX_LINES)
                    .fontColor($r('sys.color.ohos_id_color_text_primary'))
                    .layoutWeight(1)
                  Radio({ value: 'item.title', group: 'radioGroup'})
                    .size({ width : 20, height : 20})
                    .checked(this.selectedIndex == index)
                    .onChange(() => {
                      item.action && item.action()
                      this.controller.close()
                    })
                    .onClick(() => {
                      item.action && item.action()
                      this.controller.close()
                    })
                }.constraintSize({minHeight: 48}).clip(false)
                .onClick(() => {
                  item.action && item.action()
                  this.controller.close()
                })
                if (index < this.radioContent.length - 1) {
                  Divider().color($r('sys.color.ohos_id_color_list_separator'))
                }
              }
            }
          })
        }.width('100%').padding({ left: 24, right: 24, top: 8, bottom: 8 }).clip(false)
        Row() {
          if (this.confirm.value) {
            Button(this.confirm.value)
              .fontSize($r('sys.float.ohos_id_text_size_button1'))
              .fontWeight(FontWeight.Medium)
              .layoutWeight(1)
              .backgroundColor(this.confirm.background? this.confirm.background: $r('sys.color.ohos_id_color_background_transparent'))
              .fontColor(this.confirm.fontColor ? this.confirm.fontColor: $r('sys.color.ohos_id_color_text_primary_activated'))
              .onClick(() => {
                this.confirm.action && this.confirm.action()
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
            .minFontSize($r('sys.float.ohos_id_text_size_sub_title1'))
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
export struct AlertDialog{
  controller: CustomDialogController
  content: ResourceStr = ''
  primaryButton?: ButtonOptions = {value: ""}
  secondaryButton?: ButtonOptions = {value: ""}
  build() {
    Column() {
      Row() {
        Text(this.content)
          .fontSize($r('sys.float.ohos_id_text_size_body1'))
          .fontWeight(FontWeight.Medium)
          .fontColor($r('sys.color.ohos_id_color_text_primary'))
      }.padding({ left: 24, right: 24, top: 24 })
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
export struct LoadingDialog{
  controller: CustomDialogController
  content?: ResourceStr = ''
  build() {
    Column() {
      Row() {
        Text(this.content)
          .fontSize($r('sys.float.ohos_id_text_size_body1'))
          .fontWeight(FontWeight.Medium)
          .fontColor($r('sys.color.ohos_id_color_text_primary'))
          .layoutWeight(1)
        LoadingProgress().width(LOADING_PROGRESS_WIDTH).height(LOADING_PROGRESS_HEIGHT).margin({ left: 16 })
      }.margin({ left: 24, right: 24, top: 24, bottom: 24 })
      .constraintSize({minHeight: 48})
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