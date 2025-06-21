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
 * 图片动画自动暂停功能测试组件
 * 用于测试图片动画在不可见区域自动暂停的特性
 */
@Entry
@Component
struct ImageAnimatorExample010 {
  // 滚动控制器，用于管理页面滚动行为
  scroller: Scroller = new Scroller()
  
  // 动画状态管理（运行/暂停/停止/初始）
  @State state: AnimationStatus = AnimationStatus.Running
  
  // 动画播放方向控制（正向/反向）
  @State reverse: boolean = false
  
  // 动画循环次数（-1表示无限循环）
  @State iterations: number = 100
  
  // 自动监控不可见区域标志位
  @State autoMonitorInvisibleArea: boolean = false
  
  // 第一个动画的状态消息
  @State mes: string = 'Null'
  
  // 第二个动画的状态消息
  @State mes2: string = 'Null'
  
  // 生成填充内容的数组（用于测试滚动效果）
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

  build() {
    Stack({ alignContent: Alignment.TopStart }) {
      // 可滚动区域，包含两个图片动画和填充内容
      Scroll(this.scroller) {
        Column() {
          // 第一个图片动画组件（正向播放）
          ImageAnimator()
            .images([
              { src: $r('app.media.no0') },
              { src: $r('app.media.no1') },
              { src: $r('app.media.no2') },
              { src: $r('app.media.no3') },
              { src: $r('app.media.no4') },
              { src: $r('app.media.no5') },
              { src: $r('app.media.no6') }
            ])
            .borderRadius(10)                 // 圆角边框
            .monitorInvisibleArea(this.autoMonitorInvisibleArea) // 监控不可见区域
            .clip(true)                       // 启用裁剪
            .duration(4000)                   // 动画周期4秒
            .state(this.state)                // 动画状态
            .reverse(this.reverse)            // 播放方向
            .fillMode(FillMode.Forwards)      // 动画结束后保持最终状态
            .iterations(this.iterations)      // 循环次数
            .width(340).height(240)           // 尺寸
            .margin({ top: 100 })             // 边距
            .onStart(() => {                  // 动画开始回调
              this.mes = 'Start'
              console.info('ImageAnimator1 Start')
            })
            .onPause(() => {                  // 动画暂停回调
              this.mes = 'Pause'
              console.info('ImageAnimator1 Pause')
            })
            .onRepeat(() => {                 // 动画重复回调
              console.info('ImageAnimator1 Repeat')
            })
            .onCancel(() => {                 // 动画取消回调
              console.info('ImageAnimator1 Cancel')
            })
            .onFinish(() => {                 // 动画完成回调
              console.info('ImageAnimator1 Finish')
            })
          
          // 第二个图片动画组件（反向播放，帧顺序相反）
          ImageAnimator()
            .images([
              { src: $r('app.media.no6') },
              { src: $r('app.media.no5') },
              { src: $r('app.media.no4') },
              { src: $r('app.media.no3') },
              { src: $r('app.media.no2') },
              { src: $r('app.media.no1') },
              { src: $r('app.media.no0') }
            ])
            .borderRadius(10)                 // 圆角边框
            .monitorInvisibleArea(this.autoMonitorInvisibleArea) // 监控不可见区域
            .clip(true)                       // 启用裁剪
            .duration(4000)                   // 动画周期4秒
            .state(this.state)                // 动画状态
            .reverse(this.reverse)            // 播放方向
            .fillMode(FillMode.Forwards)      // 动画结束后保持最终状态
            .iterations(this.iterations)      // 循环次数
            .width(340).height(240)           // 尺寸
            .margin({ top: 100 })             // 边距
            .onStart(() => {                  // 动画开始回调
              this.mes2 = 'Start'
              console.info('ImageAnimator2 Start')
            })
            .onPause(() => {                  // 动画暂停回调
              this.mes2 = 'Pause'
              console.info('ImageAnimator2 Pause')
            })
            .onRepeat(() => {                 // 动画重复回调
              console.info('ImageAnimator2 Repeat')
            })
            .onCancel(() => {                 // 动画取消回调
              console.info('ImageAnimator2 Cancel')
            })
            .onFinish(() => {                 // 动画完成回调
              console.info('ImageAnimator2 Finish')
            })
          
          // 生成填充内容，用于测试滚动效果
          ForEach(this.arr, (item: number) => {
            Text(item.toString())
              .width('90%')
              .height(150)
              .backgroundColor(0xFFFFFF)
              .borderRadius(15)
              .fontSize(16)
              .textAlign(TextAlign.Center)
              .margin({ top: 10 })
          }, (item: number) => item.toString())
        }.width('100%')
      }
      .scrollable(ScrollDirection.Vertical) // 垂直滚动
      .scrollBar(BarState.On)                // 显示滚动条
      .scrollBarColor(Color.Gray)            // 滚动条颜色
      .scrollBarWidth(10)                    // 滚动条宽度
      .friction(0.6)                          // 滚动摩擦系数
      .edgeEffect(EdgeEffect.None)            // 边缘效果
      .onWillScroll((xOffset: number, yOffset: number, scrollState: ScrollState) => {
        console.info(`Scroll offset: x=${xOffset}, y=${yOffset}`)
      })
      .onScrollEdge((side: Edge) => {
        console.info('Scroll reached edge')
      })
      .onScrollStop(() => {
        console.info('Scroll stopped')
      })
      
      // 动画控制按钮区域
      Button('start')
      .width(100)
      .padding(5)
      .onClick(() => {
        this.state = AnimationStatus.Running  // 启动动画
      }).margin({ top: 60, left: 20 })
      
      Button('pause')
      .width(100)
      .padding(5)
      .onClick(() => {
        this.state = AnimationStatus.Paused   // 暂停动画
      }).margin({ top: 110, left: 20 })
      
      Button('stop')
      .width(100)
      .padding(5)
      .onClick(() => {
        this.state = AnimationStatus.Stopped  // 停止动画
      }).margin({ top: 160, left: 20 })
      
      Button('Initial')
      .width(100)
      .padding(5)
      .onClick(() => {
        this.state = AnimationStatus.Initial  // 重置动画
      }).margin({ top: 210, left: 20 })
      
      Button('reverse')
      .width(100)
      .padding(5)
      .onClick(() => {
        this.reverse = !this.reverse          // 切换播放方向
      }).margin({ top: 260, left: 20 })
      
      Button('once')
      .width(100)
      .padding(5)
      .onClick(() => {
        this.iterations = 1                   // 设置单次播放
      }).margin({ top: 310, left: 20 })
      
      Button('infinite')
      .width(100)
      .padding(5)
      .onClick(() => {
        this.iterations = -1                  // 设置无限循环
      }).margin({ top: 360, left: 20 })
      
      Button('Change AutoMonitorInvisableArea ' + this.autoMonitorInvisibleArea)
        .width(200)
        .padding(5)
        .onClick(() => {
          this.autoMonitorInvisibleArea = !this.autoMonitorInvisibleArea // 切换自动监控状态
        }).margin({ top: 410, left: 20 })
      
      // 显示动画状态的按钮
      Button('Start or Pause : ' + this.mes)
        .width(200)
        .padding(5)
        .margin({ top: 460, left: 20 })
      
      Button('Start or Pause : ' + this.mes2)
        .width(200)
        .padding(5)
        .margin({ top: 510, left: 20 })
    }
    .width('100%').height('100%')           // 占满整个屏幕
    .backgroundColor(0xDCDCDC)              // 浅灰色背景
  }
}