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
 * 测试Image组件enableAnalyzer属性
 * 验证图片分析器在不同场景下的启用/禁用
 */

@Entry
@Component
struct ImageAnalyzerTestCase028 {
  @State analyzerEnabled: boolean = true
  @State currentImageIndex: number = 0

  private readonly TEST_IMAGES: Resource[] = [
    $r('app.media.startIcon'),
    $r('app.media.background'),
    $r('app.media.foreground')
  ]

  build() {
    Column() {
      Text('Image enableAnalyzer属性测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Row() {
        Column() {
          Text('分析器启用')
            .fontSize(14)
            .margin({ bottom: 8 })
          Image(this.TEST_IMAGES[this.currentImageIndex])
            .width(150)
            .height(150)
            .enableAnalyzer(true)
            .objectFit(ImageFit.Cover)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
        }
        .margin({ right: 16 })

        Column() {
          Text('分析器禁用')
            .fontSize(14)
            .margin({ bottom: 8 })
          Image(this.TEST_IMAGES[this.currentImageIndex])
            .width(150)
            .height(150)
            .enableAnalyzer(false)
            .objectFit(ImageFit.Cover)
            .border({ width: 2, color: Color.Gray })
            .borderRadius(8)
        }
      }
      .margin({ bottom: 16 })

      Text(`当前状态: enableAnalyzer = ${this.analyzerEnabled}`)
        .fontSize(14)
        .fontColor(this.analyzerEnabled ? Color.Blue : Color.Gray)
        .margin({ bottom: 12 })

      Row({ space: 12 }) {
        Button('开启分析器')
          .onClick(() => {
            this.analyzerEnabled = true
          })
          .backgroundColor('#2196F3')

        Button('关闭分析器')
          .onClick(() => {
            this.analyzerEnabled = false
          })
          .backgroundColor('#999999')

        Button('切换图片')
          .onClick(() => {
            this.currentImageIndex = (this.currentImageIndex + 1) % this.TEST_IMAGES.length
          })
      }

      Divider()
        .margin({ top: 16, bottom: 16 })

      Text('多图分析器对比')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 8 })

      Row() {
        ForEach(this.TEST_IMAGES, (img: Resource, index: number) => {
          Column() {
            Image(img)
              .width(80)
              .height(80)
              .enableAnalyzer(index === 0)
              .borderRadius(6)
              .border({ width: index === this.currentImageIndex ? 3 : 1, color: Color.Blue })

            Text(`图${index + 1}: ${index === 0 ? '启用' : '禁用'}`)
              .fontSize(10)
              .fontColor(index === 0 ? Color.Blue : Color.Gray)
              .margin({ top: 4 })
          }
          .margin({ left: 8, right: 8 })
        })
      }
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
