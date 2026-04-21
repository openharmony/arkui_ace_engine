/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * Image component AI image property examples
 */
@Entry
@Component
struct ImageAIImageExample {
  @State isAIEnabled: boolean = false
  @State aiMode: number = 0
  @State aiImageCount: number = 3

  build() {
    Column({ space: 20 }) {
      Text('AI Image (aiImage) 属性示例')
        .fontSize(20)
        .fontColor(Color.Gray)

      // Toggle 按钮
      Row({ space: 20 }) {
        Text('启用AI图片')
          .fontSize(16)
        Toggle({ type: ToggleType.Switch, isOn: this.isAIEnabled })
          .onChange((value: boolean) => {
            this.isAIEnabled = value
            this.aiMode = value ? 1 : 0
          })
      }

      Divider().strokeWidth(2)

      // AI 模式选择
      Column({ space: 15 }) {
        Text('AI 模式:')
          .fontSize(16)
        Row({ space: 10 }) {
          ForEach([0, 1, 2], (mode: number) => {
            Column({ space: 5 }) {
              Text(mode === 0 ? '模式0' : mode === 1 ? '模式1' : '模式2')
                .fontSize(14)
              Button('选择')
                .onClick(() => {
                  this.aiMode = mode
                })
                .border({ width: 2, color: this.aiMode === mode ? Color.Green : Color.Transparent })
            }
          })
        }
      }

      Divider().strokeWidth(2)

      // AI 图片数量
      Column({ space: 15 }) {
        Text('AI 图片数量:')
          .fontSize(16)
        Row({ space: 10 }) {
          Text('数量:')
            .fontSize(14)
          Slider({ value: this.aiImageCount, min: 0, max: 10, step: 1 })
            .onChange((value: number) => {
              this.aiImageCount = value
            })
        }
      }

      Divider().strokeWidth(2)

      // 说明文字
      Column({ space: 15 }) {
        Text('aiImage 属性控制AI图片功能')
          .fontSize(14)
          .fontColor(Color.Blue)
      }

      // 示例展示
      Column({ space: 15 }) {
        Text('AI 图片示例')
          .fontSize(16)
        Image($r('app.media.sample_ai'))
          .width(200)
          .height(200)
          .aiImage(this.isAIEnabled ? this.aiImageCount : 0)
          .border({ width: 2, color: Color.Green })
      }

      Divider().strokeWidth(2)

      Text('当前AI设置: 模式' + this.aiMode + ' 数量: ' + this.aiImageCount)
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Blue)
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor(Color.White)
  }
}
