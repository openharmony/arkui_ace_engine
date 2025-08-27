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
 * ImageAnimator自动暂停功能测试组件
 * 用于测试图片动画在不可见区域自动暂停的特性
 */
@Entry
@Component
struct ImageAnimatorExample009 {
  // 滚动控制器，用于实现页面滚动（当前未使用）
  scroller: Scroller = new Scroller()
  
  // 动画状态管理
  @State state: AnimationStatus = AnimationStatus.Running
  
  // 动画播放方向控制
  @State reverse: boolean = false
  
  // 动画循环次数（-1表示无限循环）
  @State iterations: number = 100
  
  // 自动监控不可见区域标志
  @State autoMonitorInvisibleArea: boolean = false
  
  // 测试用数据数组（当前未使用）
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
  
  // 裁剪功能控制标志
  @State clipValue: boolean = false

  build() {
    Stack({ alignContent: Alignment.TopStart }) {
      // 动画容器（带边框和裁剪功能）
      Column() {
        // 图片动画组件
        ImageAnimator()
          .images([ // 动画帧列表
            { src: $r('app.media.no0') },
            { src: $r('app.media.no1') },
            { src: $r('app.media.no2') },
            { src: $r('app.media.no3') },
            { src: $r('app.media.no4') },
            { src: $r('app.media.no5') },
            { src: $r('app.media.no6') }
          ])
          .borderRadius(10)               // 圆角边框
          .monitorInvisibleArea(this.autoMonitorInvisibleArea) // 自动监控不可见区域
          .clip(true)                     // 启用裁剪
          .duration(4000)                 // 动画周期4秒
          .state(this.state)              // 动画状态控制
          .reverse(this.reverse)          // 反向播放控制
          .fillMode(FillMode.Forwards)    // 动画结束后保持最终状态
          .iterations(this.iterations)    // 循环次数
          .width(340).height(240)         // 动画尺寸
          .margin({ top: 100 })           // 顶部边距
          .id('TestImageAnimator')        // 组件ID
          .position({x:100, y:300})       // 相对定位
          .onStart(() => {                // 动画开始回调
            console.info('ImageAnimator Start')
          })
          .onPause(() => {                // 动画暂停回调
            console.info('ImageAnimator Pause')
          })
          .onRepeat(() => {               // 动画重复回调
            console.info('ImageAnimator Repeat')
          })
          .onCancel(() => {               // 动画取消回调
            console.info('ImageAnimator Cancel')
          })
          .onFinish(() => {               // 动画完成回调
            console.info('ImageAnimator Finish')
          })
      }
      .width(300).height(300)             // 容器尺寸
      .borderWidth(2)                     // 边框宽度
      .clip(this.clipValue)               // 容器裁剪控制

      // 动画控制按钮区域
      Button('start')
      .width(100)
      .padding(5)
      .onClick(() => {
        this.state = AnimationStatus.Running // 启动动画
      }).margin({ top: 60, left: 20 })
      
      Button('pause')
      .width(100)
      .padding(5)
      .onClick(() => {
        this.state = AnimationStatus.Paused // 暂停动画
      }).margin({ top: 110, left: 20 })
      
      Button('stop')
      .width(100)
      .padding(5)
      .onClick(() => {
        this.state = AnimationStatus.Stopped // 停止动画
      }).margin({ top: 160, left: 20 })
      
      Button('Initial')
      .width(100)
      .padding(5)
      .onClick(() => {
        this.state = AnimationStatus.Initial // 重置动画
      }).margin({ top: 210, left: 20 })
      
      Button('reverse')
      .width(100)
      .padding(5)
      .onClick(() => {
        this.reverse = !this.reverse // 切换播放方向
      }).margin({ top: 260, left: 20 })
      
      Button('once')
      .width(100)
      .padding(5)
      .onClick(() => {
        this.iterations = 1 // 设置单次播放
      }).margin({ top: 310, left: 20 })
      
      Button('infinite')
      .width(100)
      .padding(5)
      .onClick(() => {
        this.iterations = -1 // 设置无限循环
      }).margin({ top: 360, left: 20 })
      
      Button('Change AutoMonitorInvisableArea ' + this.autoMonitorInvisibleArea)
        .width(200)
        .padding(5)
        .onClick(() => {
          this.autoMonitorInvisibleArea = !this.autoMonitorInvisibleArea // 切换自动监控状态
        }).margin({ top: 410, left: 20 })
      
      Button('change clip ' + this.clipValue)
        .width(200)
        .padding(5)
        .onClick(() => {
          this.clipValue = !this.clipValue // 切换裁剪状态
        }).margin({ top: 460, left: 20 })
    }
    .width('100%').height('100%')        // 页面占满屏幕
    .backgroundColor(0xDCDCDC)           // 浅灰色背景
  }
}