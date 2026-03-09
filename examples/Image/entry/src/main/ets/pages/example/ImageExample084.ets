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
 * ImageExample084 - 图片同步加载示例
 * 
 * 功能说明：
 * 1. syncLoad 属性 - 设置是否同步加载图片
 * 2. 建议加载尺寸较小的本地图片时将 syncLoad 设为 true
 * 3. AnimatedDrawableDescriptor 类型时不生效
 * 4. 阻塞主线程超过 6s 将导致 AppFreeze
 */

@Entry
@Component
struct ImageExample084 {
  @State syncLoadEnabled: boolean = false;
  @State currentMode: string = '异步加载';
  @State loadStatus: string = '准备加载';
  @State showLargeImage: boolean = false;
  @State showSmallImage: boolean = true;

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片同步加载示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildDescription()
        this.buildAsyncLoadDemo()
        this.buildSyncLoadDemo()
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
      Text('syncLoad 属性说明')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('设置是否同步加载图片。建议加载尺寸较小的本地图片时将 syncLoad 设为 true。')
        .fontSize(14)
        .fontColor(0x666666)

      Text('重要特性：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• true：同步加载，在主线程上执行')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• false：异步加载，在后台线程上执行')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• AnimatedDrawableDescriptor 类型时不生效')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 阻塞主线程超过 6s 将导致 AppFreeze')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 默认值为 false')
        .fontSize(12)
        .fontColor(0x999999)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildAsyncLoadDemo() {
    Column({ space: 15 }) {
      Text('异步加载模式 (syncLoad = false)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('图片在后台线程上加载，不会阻塞主线程')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .syncLoad(false)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)
          .onComplete(() => {
            this.loadStatus = '加载完成';
          })
          .onError(() => {
            this.loadStatus = '加载失败';
          })

        Text('状态：异步加载 - 不阻塞主线程')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildSyncLoadDemo() {
    Column({ space: 15 }) {
      Text('同步加载模式 (syncLoad = true)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('图片在主线程上加载，适用于小尺寸本地图片')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .syncLoad(true)
          .border({ width: 2, color: Color.Green })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)
          .onComplete(() => {
            this.loadStatus = '加载完成';
          })
          .onError(() => {
            this.loadStatus = '加载失败';
          })

        Text('状态：同步加载 - 阻塞主线程')
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
          Text('异步加载')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(150)
            .height(100)
            .syncLoad(false)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('后台线程加载')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('同步加载')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(150)
            .height(100)
            .syncLoad(true)
            .border({ width: 2, color: Color.Green })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('主线程加载')
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
        Text('• 小尺寸本地图片')
          .fontSize(14)
          .fontColor(0x333333)
        Text('建议使用同步加载，因为耗时较短')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 大尺寸图片')
          .fontSize(14)
          .fontColor(0x333333)
        Text('必须使用异步加载，避免阻塞主线程')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 网络图片')
          .fontSize(14)
          .fontColor(0x333333)
        Text('必须使用异步加载，网络请求耗时较长')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 性能考虑')
          .fontSize(14)
          .fontColor(0x333333)
        Text('同步加载会阻塞主线程，可能导致界面卡顿')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 超时警告')
          .fontSize(14)
          .fontColor(0x333333)
        Text('阻塞主线程超过 6s 将导致 AppFreeze')
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

        Text('加载状态：' + this.loadStatus)
          .fontSize(14)
          .fontColor(0x666666)

        Image($r('app.media.background'))
          .width(350)
          .height(250)
          .syncLoad(this.syncLoadEnabled)
          .border({ width: 2, color: Color.Red })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)
          .onComplete(() => {
            this.loadStatus = '加载完成';
          })
          .onError(() => {
            this.loadStatus = '加载失败';
          })
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)

      Row({ space: 10 }) {
        Button('异步加载')
          .width(150)
          .onClick(() => {
            this.syncLoadEnabled = false;
            this.currentMode = '异步加载';
            this.loadStatus = '准备加载';
          })

        Button('同步加载')
          .width(150)
          .onClick(() => {
            this.syncLoadEnabled = true;
            this.currentMode = '同步加载';
            this.loadStatus = '准备加载';
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
      .padding(15)
      .backgroundColor(0xF0F0F0)
      .borderRadius(10)

      Column({ space: 10 }) {
        Text('使用场景')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .fontColor(0x333333)

        Text('• 同步加载：适用于小尺寸本地图片（如图标、缩略图）')
          .fontSize(14)
          .fontColor(0x666666)

        Text('• 异步加载：适用于大尺寸图片、网络图片')
          .fontSize(14)
          .fontColor(0x666666)

        Text('• 注意：同步加载会阻塞主线程，谨慎使用')
          .fontSize(14)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }
}
