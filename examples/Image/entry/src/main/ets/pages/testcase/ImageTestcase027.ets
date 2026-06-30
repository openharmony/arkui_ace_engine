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

/**
 * 测试Image组件privacySensitive属性
 * 验证隐私敏感标记在截图/录屏场景下的保护效果
 */

@Entry
@Component
struct ImagePrivacySensitiveTestCase027 {
  @State isPrivacySensitive: boolean = true
  @State currentImageSource: Resource = $r('app.media.startIcon')

  build() {
    Column() {
      Text('Image privacySensitive属性测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Row() {
        Column() {
          Text('隐私保护开启')
            .fontSize(14)
            .margin({ bottom: 8 })
          Image(this.currentImageSource)
            .width(150)
            .height(150)
            .privacySensitive(true)
            .objectFit(ImageFit.Cover)
            .border({ width: 3, color: Color.Red })
            .borderRadius(12)
        }
        .margin({ right: 16 })

        Column() {
          Text('隐私保护关闭')
            .fontSize(14)
            .margin({ bottom: 8 })
          Image(this.currentImageSource)
            .width(150)
            .height(150)
            .privacySensitive(false)
            .objectFit(ImageFit.Cover)
            .border({ width: 3, color: Color.Green })
            .borderRadius(12)
        }
      }
      .margin({ bottom: 16 })

      Column() {
        Text(`当前设置: privacySensitive = ${this.isPrivacySensitive}`)
          .fontSize(14)
          .fontColor(this.isPrivacySensitive ? Color.Red : Color.Green)
          .margin({ bottom: 12 })

        Row({ space: 12 }) {
          Button('开启隐私保护')
            .onClick(() => {
              this.isPrivacySensitive = true
            })
            .backgroundColor('#FF4444')

          Button('关闭隐私保护')
            .onClick(() => {
              this.isPrivacySensitive = false
            })
            .backgroundColor('#44BB44')

          Button('切换图片')
            .onClick(() => {
              this.currentImageSource = $r('app.media.background')
            })
        }
      }

      Divider()
        .margin({ top: 16, bottom: 16 })

      Text('隐私保护状态对比')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 8 })

      List() {
        ListItem() {
          Row() {
            Image($r('app.media.startIcon'))
              .width(80)
              .height(80)
              .privacySensitive(true)
              .borderRadius(8)

            Text('隐私保护 = true (截图/录屏时隐藏)')
              .fontSize(12)
              .fontColor(Color.Red)
              .margin({ left: 12 })
          }
          .padding(12)
        }

        ListItem() {
          Row() {
            Image($r('app.media.startIcon'))
              .width(80)
              .height(80)
              .privacySensitive(false)
              .borderRadius(8)

            Text('隐私保护 = false (正常显示)')
              .fontSize(12)
              .fontColor(Color.Green)
              .margin({ left: 12 })
          }
          .padding(12)
        }
      }
      .height(200)
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
