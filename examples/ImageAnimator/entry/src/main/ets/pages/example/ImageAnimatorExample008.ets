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

// ImageAnimator自动暂停功能测试组件, 全面测试动画在状态切换（运行 / 暂停 / 停止）、反向播放、循环次数调整、
// 填充模式变更及持续时间动态修改等场景下的行为一致性
@Entry
@Component
struct ImageAnimatorExample008 {
  // 滚动控制器（虽然当前代码未使用，但初始化保证编译通过）
  scroller: Scroller = new Scroller()
  
  // 动画状态控制（运行/暂停/停止/初始）
  @State state: AnimationStatus = AnimationStatus.Running
  
  // 动画播放方向控制（是否反向）
  @State reverse: boolean = false
  
  // 动画循环次数（-1表示无限循环）
  @State iterations: number = 100
  
  // 自动监控不可见区域标志位
  @State autoMonitorInvisibleArea: boolean = false
  
  // 测试用数组（当前代码未使用，但保留初始化）
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
  
  // 裁剪标志位（当前代码未使用，但保留声明）
  @State clipValue: boolean = false
  
  // 叠加层尺寸控制变量
  @State posX: number = 200
  @State posY: number = 200
  
  // 自定义叠加层构建器（显示在动画组件中央）
  @Builder OverlayNode() {
    Column() {
      Image($r('app.media.cat'))
        .height(this.posX)
        .width(this.posY)
      Text('This is overlayNode').fontSize(20).fontColor(Color.White)
    }
    .width(this.posX)
    .height(this.posY)
    .alignItems(HorizontalAlign.Center)
  }

  build() {
    Stack({ alignContent: Alignment.TopStart }) {
      // 图片动画组件主体
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
        .height(200)
        .width(200)
        .borderRadius(10)
        .monitorInvisibleArea(this.autoMonitorInvisibleArea) // 监控不可见区域自动暂停
        .clip(true)
        .duration(4000)          // 动画总时长4000ms
        .state(this.state)       // 动画状态控制
        .reverse(this.reverse)   // 反向播放控制
        .fillMode(FillMode.Forwards) // 动画结束后保持最后一帧
        .iterations(this.iterations) // 循环次数
        .width(340)             // 宽度340px
        .height(240)            // 高度240px
        .margin({ top: 100 })    // 顶部边距100px
        .id('TestImageAnimator') // 组件唯一标识
        .onStart(() => {
          console.info('ImageAnimator Start')
        })
        .onPause(() => {
          console.info('ImageAnimator Pause')
        })
        .onRepeat(() => {
          console.info('ImageAnimator Repeat')
        })
        .onCancel(() => {
          console.info('ImageAnimator Cancel')
        })
        .onFinish(() => {
          console.info('ImageAnimator Finish')
        })
        .overlay(this.OverlayNode(), { align: Alignment.Center }) // 中央叠加层
        
      // 动画状态控制按钮组
      Button('start')
      .width(100)
      .padding(5)
      .onClick(() => {
        this.state = AnimationStatus.Running
      }).margin({ top: 60, left: 20 })
      
      Button('pause')
      .width(100)
      .padding(5)
      .onClick(() => {
        this.state = AnimationStatus.Paused // 暂停并显示当前帧
      }).margin({ top: 110, left: 20 })
      
      Button('stop')
      .width(100)
      .padding(5)
      .onClick(() => {
        this.state = AnimationStatus.Stopped // 停止并显示起始帧
      }).margin({ top: 160, left: 20 })
      
      Button('Initial')
      .width(100)
      .padding(5)
      .onClick(() => {
        this.state = AnimationStatus.Initial // 重置为初始状态
      }).margin({ top: 210, left: 20 })
      
      // 动画属性控制按钮组
      Button('reverse')
      .width(100)
      .padding(5)
      .onClick(() => {
        this.reverse = !this.reverse // 切换反向播放状态
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
      
      // 不可见区域监控功能切换按钮
      Button('Change AutoMonitorInvisableArea ' + this.autoMonitorInvisibleArea)
        .width(200)
        .padding(5)
        .onClick(() => {
          this.autoMonitorInvisibleArea = !this.autoMonitorInvisibleArea;
        }).margin({ top: 410, left: 20 })
      
      // 叠加层尺寸控制按钮组
      Button('add posX ' + this.posX)
      .width(200)
      .padding(5)
      .onClick(() => {
        this.posX += 50;
      }).margin({ top: 460, left: 20 })
      
      Button('reduce posX ' + this.posX)
      .width(200)
      .padding(5)
      .onClick(() => {
        this.posX = Math.max(50, this.posX - 50); // 防止尺寸为负
      }).margin({ top: 510, left: 20 })
      
      Button('add posY ' + this.posY)
      .width(200)
      .padding(5)
      .onClick(() => {
        this.posY += 50;
      }).margin({ top: 560, left: 20 })
      
      Button('reduce posY ' + this.posY)
      .width(200)
      .padding(5)
      .onClick(() => {
        this.posY = Math.max(50, this.posY - 50); // 防止尺寸为负
      }).margin({ top: 610, left: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xDCDCDC) // 浅灰色背景
  }
}