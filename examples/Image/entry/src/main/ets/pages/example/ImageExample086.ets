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
 * ImageExample086 - 图片拖拽示例
 * 
 * 功能说明：
 * 1. draggable 属性 - 设置组件默认拖拽效果
 * 2. 设置为 true 时，组件可拖拽，绑定的长按手势不生效
 * 3. API version 9 及之前，默认值为 false
 * 4. API version 10 及之后，默认值为 true
 * 5. 若用户需要设置自定义手势，则需要将 draggable 设置为 false
 */

@Entry
@Component
struct ImageExample086 {
  @State draggableEnabled: boolean = false;
  @State currentMode: string = '不可拖拽';
  @State dragHint: string = '尝试拖拽图片';
  @State dragCount: number = 0;

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片拖拽示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildDescription()
        this.buildNonDraggableDemo()
        this.buildDraggableDemo()
        this.buildComparisonDemo()
        this.buildBestPractices()
        this.buildInteractiveDemo()
      }
      .width('100%')
      .padding({ left: 20, right: 20, bottom: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xF5F5F5)
  }

  @Builder
  buildDescription() {
    Column({ space: 10 }) {
      Text('draggable 属性说明')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('设置组件默认拖拽效果。设置为 true 时，组件可拖拽，绑定的长按手势不生效。')
        .fontSize(14)
        .fontColor(0x666666)

      Text('重要特性：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• true：组件可拖拽，绑定的长按手势不生效')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• false：组件不可拖拽，长按手势可以生效')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• API version 9 及之前，默认值为 false')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• API version 10 及之后，默认值为 true')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 若用户需要设置自定义手势，则需要将 draggable 设置为 false')
        .fontSize(12)
        .fontColor(0x999999)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildNonDraggableDemo() {
    Column({ space: 15 }) {
      Text('不可拖拽模式 (draggable = false)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('组件不可拖拽，长按手势可以生效')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .draggable(false)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(1)
          .backgroundColor(0xF0F0F0)
          .gesture(
            LongPressGesture()
              .onAction(() => {
                this.dragCount++;
              })
          )

        Text('长按次数：' + this.dragCount)
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildDraggableDemo() {
    Column({ space: 15 }) {
      Text('可拖拽模式 (draggable = true)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('组件可拖拽，绑定的长按手势不生效')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .draggable(true)
          .border({ width: 2, color: Color.Green })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('长按手势不生效，可以直接拖拽')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildComparisonDemo() {
    Column({ space: 15 }) {
      Text('模式对比')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Row({ space: 20 }) {
        Column({ space: 10 }) {
          Text('不可拖拽')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(150)
            .height(100)
            .draggable(false)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('长按手势生效')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('可拖拽')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(150)
            .height(100)
            .draggable(true)
            .border({ width: 2, color: Color.Green })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('可以直接拖拽')
            .fontSize(12)
            .fontColor(0x666666)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildBestPractices() {
    Column({ space: 15 }) {
      Text('最佳实践建议')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Text('• 图片分享')
          .fontSize(14)
          .fontColor(0x333333)
        Text('允许用户拖拽图片进行分享')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 自定义手势')
          .fontSize(14)
          .fontColor(0x333333)
        Text('需要自定义手势时，将 draggable 设置为 false')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 长按操作')
          .fontSize(14)
          .fontColor(0x333333)
        Text('需要长按操作时，将 draggable 设置为 false')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 拖拽上传')
          .fontSize(14)
          .fontColor(0x333333)
        Text('支持拖拽图片到其他应用进行上传')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• API 版本兼容')
          .fontSize(14)
          .fontColor(0x333333)
        Text('注意不同 API 版本的默认值差异')
          .fontSize(12)
          .fontColor(0x666666)
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildInteractiveDemo() {
    Column({ space: 15 }) {
      Text('交互式演示')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Text('当前模式：' + this.currentMode)
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .fontColor(0x333333)

        Text(this.dragHint)
          .fontSize(14)
          .fontColor(0x666666)

        if (!this.draggableEnabled) {
          Image($r('app.media.background'))
            .width(350)
            .height(250)
            .draggable(false)
            .border({ width: 2, color: Color.Red })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)
            .gesture(
              LongPressGesture()
                .onAction(() => {
                  this.dragCount++;
                })
            )

          Text('长按次数：' + this.dragCount)
            .fontSize(12)
            .fontColor(0x666666)
        } else {
          Image($r('app.media.background'))
            .width(350)
            .height(250)
            .draggable(true)
            .border({ width: 2, color: Color.Red })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('可以直接拖拽图片')
            .fontSize(12)
            .fontColor(0x666666)
        }
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)

      Row({ space: 10 }) {
        Button('不可拖拽')
          .width(150)
          .onClick(() => {
            this.draggableEnabled = false;
            this.currentMode = '不可拖拽';
            this.dragHint = '长按手势生效，可以长按图片';
            this.dragCount = 0;
          })

        Button('可拖拽')
          .width(150)
          .onClick(() => {
            this.draggableEnabled = true;
            this.currentMode = '可拖拽';
            this.dragHint = '可以直接拖拽图片';
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
      .padding(15)
      .backgroundColor(0xF0F0F0)
      .borderRadius(10)

      Column({ space: 10 }) {
        Text('操作说明')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .fontColor(0x333333)

        Text('• 可拖拽模式：直接拖拽图片到其他位置或应用')
          .fontSize(14)
          .fontColor(0x666666)

        Text('• 不可拖拽模式：长按手势生效，可以添加自定义长按操作')
          .fontSize(14)
          .fontColor(0x666666)

        Text('• 注意：draggable 为 true 时，长按手势不生效')
          .fontSize(14)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }
}
