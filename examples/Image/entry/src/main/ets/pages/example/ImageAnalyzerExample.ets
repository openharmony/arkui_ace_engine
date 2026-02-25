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
 * Image component analyzer property examples
 */
@Entry
@Component
struct ImageAnalyzerExample {
  @State isAnalyzerEnabled: boolean = false
  @State analyzerResult: string = ''

  build() {
    Column({ space: 20 }) {
      Text('ImageAnalyzer 属性示例')
        .fontSize(20)
        .fontColor(Color.Gray)

      // Toggle 按钮
      Row({ space: 20 }) {
        Text('启用图片分析')
          .fontSize(16)
        Toggle({ type: ToggleType.Switch, isOn: this.isAnalyzerEnabled })
          .onChange((value: boolean) => {
            this.isAnalyzerEnabled = value
            this.analyzerResult = value ? '分析器已启用' : '分析器已禁用'
          })
      }

      Divider().strokeWidth(2)

      // 分析结果展示
      Column({ space: 15 }) {
        Text('分析结果:')
          .fontSize(16)
          Text(this.analyzerResult)
            .fontSize(14)
            .fontColor(this.isAnalyzerEnabled ? Color.Green : Color.Gray)
      }

      // 说明文字
      Column({ space: 15 }) {
        Text('imageAnalyzer 属性启用AI图片分析能力')
          .fontSize(14)
          .fontColor(Color.Blue)
      }

      Divider().strokeWidth(2)

      // 示例：分析图片颜色
      Column({ space: 15 }) {
        Text('图片颜色分析示例')
          .fontSize(16)
        Button('开始分析')
          .onClick(() => {
            this.analyzerResult = '分析中...\n主要颜色: 红色 (65%)'
          })
      }

      // 示例：识别内容
      Column({ space: 15 }) {
        Text('内容识别示例')
          .fontSize(16)
        Button('识别图片内容')
          .onClick(() => {
            this.analyzerResult = '识别结果:\n- 物体: 狗 (95%)\n- 文字: 广告牌 (85%)\n- 场景: 室内 (78%)'
          })
      }

      // 示例：智能裁剪建议
      Column({ space: 15 }) {
        Text('智能裁剪示例')
          .fontSize(16)
        Button('获取裁剪建议')
          .onClick(() => {
            this.analyzerResult = '裁剪建议:\n- 保持主体: 人物\n- 移除背景: 天空\n- 构图比例: 3:4'
          })
      }

      Divider().strokeWidth(2)

      Text('当前分析器状态: ' + (this.isAnalyzerEnabled ? '已启用' : '已禁用'))
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
