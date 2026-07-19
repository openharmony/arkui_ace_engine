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
 * 测试Image组件colorFilter属性
 * 验证矩阵滤镜和颜色变换效果
 */

@Entry
@Component
struct ImageColorFilterTestCase021 {
  @State currentFilterIndex: number = 0

  private readonly COLOR_FILTERS: Array<{ matrix: number[]; label: string }> = [
    { matrix: [1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0], label: '原图' },
    { matrix: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0], label: '灰度' },
    { matrix: [1.5, 0, 0, 0, 0, 0, 1.5, 0, 0, 0, 0, 0, 1.5, 0, 0, 0, 0, 0, 1, 0], label: '高亮' },
    { matrix: [0.5, 0, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 0, 1, 0], label: '暗化' },
    { matrix: [-1, 0, 0, 0, 1, 0, -1, 0, 0, 1, 0, 0, -1, 0, 0, 1, 0, 0, 0, 1, 0], label: '反色' },
    { matrix: [1, 0, 0, 0, 0.2, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0], label: '偏红' },
    { matrix: [1, 0, 0, 0, 0, 0, 1, 0, 0, 0.2, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0], label: '偏绿' },
    { matrix: [1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0.2, 0, 0, 0, 1, 0], label: '偏蓝' }
  ]

  build() {
    Column() {
      Text('Image colorFilter属性测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Row() {
        Image($r('app.media.startIcon'))
          .width(150)
          .height(150)
          .colorFilter(this.COLOR_FILTERS[this.currentFilterIndex].matrix)
          .objectFit(ImageFit.Cover)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)

        Column() {
          Text(`当前滤镜: ${this.COLOR_FILTERS[this.currentFilterIndex].label}`)
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 8 })
          Text(`矩阵长度: ${this.COLOR_FILTERS[this.currentFilterIndex].matrix.length}`)
            .fontSize(12)
            .fontColor(Color.Gray)
        }
        .margin({ left: 16 })
      }
      .margin({ bottom: 16 })

      Grid() {
        ForEach(this.COLOR_FILTERS, (filter: { matrix: number[]; label: string }, index: number) => {
          GridItem() {
            Column() {
              Image($r('app.media.startIcon'))
                .width(60)
                .height(60)
                .colorFilter(filter.matrix)
                .borderRadius(4)
                .border({
                  width: index === this.currentFilterIndex ? 3 : 1,
                  color: index === this.currentFilterIndex ? Color.Blue : Color.Gray
                })

              Text(filter.label)
                .fontSize(11)
                .margin({ top: 4 })
            }
            .padding(8)
            .backgroundColor(index === this.currentFilterIndex ? '#E3F2FD' : '#FAFAFA')
            .borderRadius(6)
            .onClick(() => {
              this.currentFilterIndex = index
            })
          }
        })
      }
      .columnsTemplate('repeat(4, 1fr)')
      .rowsGap(12)
      .columnsGap(8)
      .padding(16)
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
