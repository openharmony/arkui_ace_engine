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
 * 图片事件回调完整示例
 * 演示onComplete、onError、onSvgPlayFinish、onDownloadProgress四种图片事件回调
 */
@Entry
@Component
struct ImageExample111 {
  @State eventLog: string[] = []
  @State imageUrl: string = ''
  @State isLoading: boolean = false
  @State loadProgress: number = 0
  @State imageWidth: number = 0
  @State imageHeight: number = 0
  @State componentWidth: number = 0
  @State componentHeight: number = 0
  @State currentTestIndex: number = 0

  private maxLogSize: number = 15

  private testCases: { name: string, src: Resource | string }[] = [
    { name: '本地资源(正常加载)', src: $r('app.media.startIcon') },
    { name: 'SVG图片', src: $r('app.media.svg') },
    { name: '空字符串(触发错误)', src: '' },
    { name: '无效路径(触发错误)', src: 'non_existent_path.png' }
  ]

  addLog(tag: string, message: string) {
    const timestamp = new Date().toLocaleTimeString()
    this.eventLog.unshift(`[${tag}] ${timestamp}\n  ${message}`)
    if (this.eventLog.length > this.maxLogSize) {
      this.eventLog.pop()
    }
  }

  clearLog() {
    this.eventLog = []
    this.loadProgress = 0
    this.imageWidth = 0
    this.imageHeight = 0
  }

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片事件回调完整示例')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20 })

        Text('演示onComplete/onError/onSvgPlayFinish/onDownloadProgress四种事件')
          .fontSize(14)
          .fontColor(0x666666)

        Column({ space: 8 }) {
          Text(`测试用例: ${this.testCases[this.currentTestIndex].name}`)
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Image(this.testCases[this.currentTestIndex].src)
            .width(200)
            .height(200)
            .objectFit(ImageFit.Cover)
            .alt($r('app.media.startIcon'))
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)
            .onComplete((event: ImageLoadResult) => {
              if (event) {
                this.imageWidth = event.width
                this.imageHeight = event.height
                this.componentWidth = event.componentWidth
                this.componentHeight = event.componentHeight
                this.isLoading = false
                this.addLog('onComplete',
                  `加载成功! 图片:${event.width}x${event.height}px ` +
                  `组件:${event.componentWidth}x${event.componentHeight}px ` +
                  `偏移:(${event.contentOffsetX}, ${event.contentOffsetY}) ` +
                  `渲染:${event.renderWidth}x${event.renderHeight}px`)
              }
            })
            .onError((error: ImageError) => {
              this.isLoading = false
              this.addLog('onError', `加载失败! 错误码:${error.message}`)
            })
            .onSvgPlayFinish(() => {
              this.addLog('onSvgPlayFinish', 'SVG动画播放完成')
            })
            .onDownloadProgress((progress: number) => {
              this.loadProgress = Math.floor(progress)
              this.addLog('onDownloadProgress', `下载进度: ${Math.floor(progress)}%`)
            })
        }
        .width('100%')
        .alignItems(HorizontalAlign.Center)
        .padding(15)
        .backgroundColor(0xFFFFFF)
        .borderRadius(10)

        if (this.imageWidth > 0) {
          Column({ space: 5 }) {
            Text('图片信息:')
              .fontSize(14)
              .fontWeight(FontWeight.Medium)
            Text(`原始尺寸: ${this.imageWidth} x ${this.imageHeight} px`)
              .fontSize(12)
              .fontColor(0x666666)
            Text(`组件尺寸: ${this.componentWidth} x ${this.componentHeight} px`)
              .fontSize(12)
              .fontColor(0x666666)
          }
          .width('100%')
          .padding(10)
          .backgroundColor(0xE8F5E9)
          .borderRadius(8)
        }

        if (this.isLoading) {
          Progress({ value: this.loadProgress, total: 100, type: ProgressType.Linear })
            .width('100%')
            .color(0x007DFF)
        }

        Column({ space: 10 }) {
          Text('测试用例切换:')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Start }) {
            ForEach(this.testCases, (testCase: { name: string, src: Resource | string }, index: number) => {
              Button(testCase.name)
                .fontSize(11)
                .margin(4)
                .height(36)
                .onClick(() => {
                  this.currentTestIndex = index
                  this.clearLog()
                  this.isLoading = true
                  this.addLog('Switch', `切换到: ${testCase.name}`)
                })
                .backgroundColor(this.currentTestIndex === index ? 0x007DFF : 0xE0E0E0)
                .fontColor(this.currentTestIndex === index ? Color.White : 0x333333)
            })
          }
        }
        .width('100%')
        .padding(15)
        .backgroundColor(0xFFFFFF)
        .borderRadius(10)

        Row({ space: 10 }) {
          Button('清除日志')
            .onClick(() => {
              this.clearLog()
            })
          Button('重新加载')
            .onClick(() => {
              this.clearLog()
              this.isLoading = true
              this.addLog('Reload', '重新加载当前图片')
            })
        }

        Column({ space: 5 }) {
          Text(`事件日志 (共${this.eventLog.length}条):`)
            .fontSize(14)
            .fontWeight(FontWeight.Medium)

          List({ space: 5 }) {
            ForEach(this.eventLog, (log: string, index: number) => {
              ListItem() {
                Text(log)
                  .fontSize(11)
                  .fontColor(0x333333)
                  .width('100%')
                  .padding(8)
                  .backgroundColor(index === 0 ? 0xE3F2FD : 0xF5F5F5)
                  .borderRadius(4)
              }
            })
          }
          .width('100%')
          .height(250)
        }
        .width('100%')
        .padding(10)
        .backgroundColor(0xFFFFFF)
        .borderRadius(8)

        Column({ space: 5 }) {
          Text('事件说明:')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
          Text('• onComplete: 图片加载或解码成功时触发，返回图片和组件尺寸信息')
            .fontSize(12)
            .fontColor(0x666666)
          Text('• onError: 图片加载失败时触发，返回错误信息')
            .fontSize(12)
            .fontColor(0x666666)
          Text('• onSvgPlayFinish: SVG动画播放完成时触发')
            .fontSize(12)
            .fontColor(0x666666)
          Text('• onDownloadProgress: 网络图片下载进度更新时触发')
            .fontSize(12)
            .fontColor(0x666666)
        }
        .width('100%')
        .padding(15)
        .backgroundColor(0xFFFFFF)
        .borderRadius(10)
      }
      .width('100%')
      .padding({ left: 20, right: 20, bottom: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xF5F5F5)
  }
}
