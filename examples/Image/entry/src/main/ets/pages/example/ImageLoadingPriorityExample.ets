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
 * Image component loading priority and error handling examples
 */
@Entry
@Component
struct ImageLoadingPriorityExample {
  @State loadingPriority: number = 0
  @State loadSrcSuccess: boolean = false
  @State loadAltSuccess: boolean = false
  @State showProgress: boolean = true

  build() {
    Column({ space: 20 }) {
      Text('加载优先级和错误处理示例')
        .fontSize(20)
        .fontColor(Color.Gray)

      // 优先级滑块
      Column({ space: 15 }) {
        Text('加载优先级 (loadingPriority)')
          .fontSize(16)
        Slider({ value: this.loadingPriority, min: 0, max: 3, step: 1 })
          .onChange((value: number) => {
            this.loadingPriority = value
          })
        Text('0: 低优先级 (默认)')
          .fontSize(14)
        Text('1: 中优先级')
          .fontSize(14)
        Text('2: 高优先级')
          .fontSize(14)
        Text('3: 最高优先级')
          .fontSize(14)
      }

      Divider().strokeWidth(2)

      // 加载状态指示
      Column({ space: 15 }) {
        Text('加载状态')
          .fontSize(16)

        // 主图加载
        Column({ space: 10 }) {
          Text('主图:')
            .fontSize(14)
          Image($r('app.media.app_icon'))
            .width(200)
            .height(100)
            .border({ width: 2, color: this.loadSrcSuccess ? Color.Green : Color.Red })
          Text(this.loadSrcSuccess ? '加载成功' : '加载失败')
            .fontSize(12)
            .fontColor(this.loadSrcSuccess ? Color.Green : Color.Red)
        Button('模拟加载')
          .onClick(() => {
              this.loadSrcSuccess = !this.loadSrcSuccess
            })
        }

        // 备图加载
        Column({ space: 10 }) {
          Text('备图:')
          .fontSize(14)
          Image($r('app.media.app_icon'))
            .width(200)
            .height(100)
            .border({ width: 2, color: this.loadAltSuccess ? Color.Green : Color.Orange })
          Text(this.loadAltSuccess ? '加载成功' : '加载失败')
          .fontSize(12)
          .fontColor(this.loadAltSuccess ? Color.Green : Color.Orange)
        Button('模拟加载')
          .onClick(() => {
              this.loadAltSuccess = !this.loadAltSuccess
            })
        }
      }

      Divider().strokeWidth(2)

      // 进度条
      Column({ space: 15 }) {
        Text('加载进度显示')
          .fontSize(16)
        Text(this.showProgress ? '显示进度' : '隐藏进度')
        Button(this.showProgress ? '隐藏进度' : '显示进度')
          .fontSize(14)
        Column({ space: 5 }) {
          if (this.showProgress) {
            ForEach([0, 25, 50, 75, 100], (progress: number) => {
              Text(progress + '%')
                .fontSize(12)
            })
          }
        }
      }

      Divider().strokeWidth(2)

      Text('loadingPriority 属性控制图片加载优先级和备图加载策略')
        .fontSize(14)
        .fontColor(Color.Blue)
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor(Color.White)
  }
}
