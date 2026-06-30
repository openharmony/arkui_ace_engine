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
 * 测试Image组件matchTextDirection和fitOriginalSize属性
 * 验证RTL文本方向适配和原始尺寸显示
 */

@Entry
@Component
struct ImageDirectionTestCase019 {
  @State matchTextDir: boolean = false
  @State fitOriginal: boolean = false
  @State isRtl: boolean = false

  build() {
    Column() {
      Text('Image matchTextDirection/fitOriginalSize测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Row() {
        Column() {
          Text('LTR方向')
            .fontSize(14)
            .margin({ bottom: 8 })
          Image($r('app.media.startIcon'))
            .width(120)
            .height(120)
            .matchTextDirection(this.matchTextDir)
            .fitOriginalSize(this.fitOriginal)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
        }
        .margin({ right: 16 })

        Column() {
          Text('RTL方向')
            .fontSize(14)
            .margin({ bottom: 8 })
          Image($r('app.media.startIcon'))
            .width(120)
            .height(120)
            .matchTextDirection(this.matchTextDir)
            .fitOriginalSize(this.fitOriginal)
            .border({ width: 2, color: Color.Red })
            .borderRadius(8)
        }
      }
      .margin({ bottom: 16 })

      Column({ space: 8 }) {
        Row({ space: 12 }) {
          Button(`matchTextDirection: ${this.matchTextDir}`)
            .onClick(() => {
              this.matchTextDir = !this.matchTextDir
            })
          Button(`fitOriginalSize: ${this.fitOriginal}`)
            .onClick(() => {
              this.fitOriginal = !this.fitOriginal
            })
          Button(`RTL模式: ${this.isRtl}`)
            .onClick(() => {
              this.isRtl = !this.isRtl
            })
        }

        Divider()

        Row() {
          Text('当前配置:')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
          Text(`matchTextDir=${this.matchTextDir}, fitOriginal=${this.fitOriginal}, RTL=${this.isRtl}`)
            .fontSize(12)
            .fontColor(Color.Gray)
            .margin({ left: 8 })
        }
      }

      Divider()
        .margin({ top: 16, bottom: 16 })

      Row() {
        Image($r('app.media.background'))
          .width(80)
          .height(80)
          .matchTextDirection(false)
          .fitOriginalSize(false)
          .objectFit(ImageFit.Contain)
          .border({ width: 1, color: Color.Gray })

        Image($r('app.media.background'))
          .width(80)
          .height(80)
          .matchTextDirection(true)
          .fitOriginalSize(false)
          .objectFit(ImageFit.Contain)
          .border({ width: 1, color: Color.Blue })

        Image($r('app.media.background'))
          .width(80)
          .height(80)
          .matchTextDirection(false)
          .fitOriginalSize(true)
          .objectFit(ImageFit.Contain)
          .border({ width: 1, color: Color.Orange })
      }
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
