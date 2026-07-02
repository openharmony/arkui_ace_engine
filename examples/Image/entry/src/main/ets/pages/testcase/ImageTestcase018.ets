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
 * 测试Image组件alt属性
 * 验证占位图/备用图在不同加载场景下的表现
 */

@Entry
@Component
struct ImageAltTestCase018 {
  @State currentImageSource: ResourceStr = ''
  @State altSource: Resource = $r('app.media.startIcon')
  @State loadState: string = 'idle'

  private readonly TEST_SCENARIOS: Array<{ source: ResourceStr; label: string }> = [
    { source: $r('app.media.startIcon'), label: '正常资源' },
    { source: '', label: '空字符串' },
    { source: 'invalid://nonexistent.jpg', label: '无效URL' },
    { source: 'file:///nonexistent/path.png', label: '不存在文件路径' },
    { source: $r('app.media.background'), label: '另一个资源' }
  ]

  build() {
    Column() {
      Text('Image alt属性测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Row() {
        Column() {
          Text('主图加载')
            .fontSize(14)
            .margin({ bottom: 8 })
          Image(this.currentImageSource)
            .width(120)
            .height(120)
            .alt(this.altSource)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
            .onComplete(() => {
              this.loadState = 'onComplete'
            })
            .onError((err: ImageError) => {
              this.loadState = 'onError: ' + (err.message ?? '')
            })
        }
        .margin({ right: 16 })

        Column() {
          Text('备用图(alt)')
            .fontSize(14)
            .margin({ bottom: 8 })
          Image(this.altSource)
            .width(120)
            .height(120)
            .border({ width: 2, color: Color.Gray })
            .borderRadius(8)
        }
      }
      .margin({ bottom: 16 })

      Text(`加载状态: ${this.loadState}`)
        .fontSize(14)
        .fontColor(this.loadState.startsWith('onError') ? Color.Red : Color.Green)
        .margin({ bottom: 16 })

      Grid() {
        ForEach(this.TEST_SCENARIOS, (scenario: { source: ResourceStr; label: string }) => {
          GridItem() {
            Column() {
              Text(scenario.label)
                .fontSize(12)
                .padding(8)
                .backgroundColor('#E3F2FD')
                .borderRadius(4)
            }
            .onClick(() => {
              this.currentImageSource = scenario.source
              this.loadState = 'loading'
            })
          }
        })
      }
      .columnsTemplate('repeat(3, 1fr)')
      .rowsGap(8)
      .columnsGap(8)
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
