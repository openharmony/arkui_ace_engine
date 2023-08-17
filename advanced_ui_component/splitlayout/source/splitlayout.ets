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

@Component
export struct splitlayout {
  @BuilderParam container: () => void
  @State sizeValue: string = ''
  @State areaWidth: number = 0
  @State imageBackgroundColor: string = "#19000000"
  @Prop mainImage: Resource
  @Prop primaryText: string = "新歌推荐"
  secondaryText?: string = "私人订制新歌精选站，为你推荐专属优质新歌;为你推荐专属优质新歌"
  tertiaryText?: string = "每日更新"

  build() {
    Column() {
      if (this.areaWidth < 600) {
        GridRow({
          columns: 4,
          breakpoints: {
            reference: BreakpointsReference.WindowSize },
          direction: GridRowDirection.Row
        }) {
          GridCol({ span: { xs: 4, sm: 4, md: 4, lg: 4 } }) {
            Column() {
              Stack({ alignContent: Alignment.Bottom }) {
                Image(this.mainImage)
				  .height('34%')
				  .width('100%')
                Column() {
                  Text(this.primaryText)
				    .fontWeight(FontWeight.Medium)
                    .textAlign(TextAlign.Center)
                    .fontSize($r('sys.float.ohos_id_text_size_headline7'))
                    .fontColor($r('sys.color.ohos_id_color_text_primary'))
                  Text(this.secondaryText)
                    .textAlign(TextAlign.Center)
                    .fontSize($r('sys.float.ohos_id_text_size_body2'))
                    .fontColor($r('sys.color.ohos_id_color_text_primary'))
                    .margin({ top: 4, bottom: 8 })
                  Text(this.tertiaryText)
                    .textAlign(TextAlign.Center)
                    .fontSize($r('sys.float.ohos_id_text_size_caption'))
                    .fontColor($r('sys.color.ohos_id_color_text_secondary'))
                    .margin({ bottom: 24 })
                }
                .alignItems(HorizontalAlign.Center)
                .margin({
                  left: $r('sys.float.ohos_id_max_padding_start'),
                  right: $r('sys.float.ohos_id_max_padding_end'), })
              }
              .height('34%')
              .width('100%')

              Column() {
                this.container()
              }
              .height('66%')
              .width('100%')
            }
          }
        }
      } else if (600 < this.areaWidth && this.areaWidth < 840) {
        GridRow({
          columns: 8,
          breakpoints: {
            reference: BreakpointsReference.WindowSize },
          direction: GridRowDirection.Row
        }) {
          GridCol({ span: { xs: 8, sm: 8, md: 8, lg: 8 } }) {
            Column() {
              Row() {
                Image(this.mainImage)
                  .margin({ left: 96, right: 36 })
                  .height('60%')
                  .width('20%')
                Column() {
                  Text(this.primaryText)
				    .fontWeight(FontWeight.Medium)
                    .fontSize($r('sys.float.ohos_id_text_size_headline7'))
                    .fontColor($r('sys.color.ohos_id_color_text_primary'))
                  Text(this.secondaryText)
                    .fontSize($r('sys.float.ohos_id_text_size_body2'))
                    .fontColor($r('sys.color.ohos_id_color_text_primary'))
                    .margin({ top: 4, bottom: 8 })
                  Text(this.tertiaryText)
                    .fontSize($r('sys.float.ohos_id_text_size_caption'))
                    .fontColor($r('sys.color.ohos_id_color_text_secondary'))
                }
				.width('42%')
                .alignItems(HorizontalAlign.Start)
                .margin({ right: 96 })
              }
              .backgroundColor(this.imageBackgroundColor)
              .height('34%')

              Column() {
                this.container()
              }
              .height('66%')
            }

          }
        }

      } else if (this.areaWidth > 840) {
        GridRow({
          columns: 12,
          breakpoints: {
            reference: BreakpointsReference.WindowSize },
          direction: GridRowDirection.Row
        }) {
          GridCol({ span: { xs: 4, sm: 4, md: 4, lg: 4 } }) {
            Column() {
              Image(this.mainImage)
                .height('17%')
                .width('34%')
                .margin({ bottom: 36 })
              Text(this.primaryText)
                .textAlign(TextAlign.Center)
				.fontWeight(FontWeight.Medium)
                .fontSize($r('sys.float.ohos_id_text_size_headline7'))
                .fontColor($r('sys.color.ohos_id_color_text_primary'))
                .margin({ left: 48, right: 48 })
              Text(this.secondaryText)
                .textAlign(TextAlign.Center)
                .fontSize($r('sys.float.ohos_id_text_size_body2'))
                .fontColor($r('sys.color.ohos_id_color_text_primary'))
                .margin({ top: 4, bottom: 8, left: 48, right: 48 })
              Text(this.tertiaryText)
                .textAlign(TextAlign.Center)
                .fontSize($r('sys.float.ohos_id_text_size_caption'))
                .fontColor($r('sys.color.ohos_id_color_text_secondary'))
                .margin({ left: 48, right: 48 })
            }
            .height('100%')
            .backgroundColor(this.imageBackgroundColor)
            .justifyContent(FlexAlign.Center)
            .alignItems(HorizontalAlign.Center)
          }
          .height('100%')

          GridCol({ span: { xs: 8, sm: 8, md: 8, lg: 8 } }) {
            this.container()
          }

        }
      }
    }
    .onAreaChange((oldValue: Area, newValue: Area) => {
      console.info(`Ace: on area change, oldValue is ${JSON.stringify(oldValue)} value is ${JSON.stringify(newValue)}`)
      this.sizeValue = JSON.stringify(newValue)
      this.areaWidth = parseInt(newValue.width.toString(), 0);
      console.info(`pingAce: on area change, oldValue is` + this.areaWidth)
      console.info(`pingAce: on area change, oldValue is` + parseInt(newValue.height.toString(), 0))
    })
  }
}
