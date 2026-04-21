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
 * ========================================
 * ImageAnimatorExample018 - 单帧 duration 专项示例
 * ========================================
 * 
 * 测试功能说明:
 * 本示例测试 ImageAnimator 组件的单帧 duration 功能
 * 
 * 涉及的 ImageAnimator API:
 * 1. ImageFrameInfo.duration - 每帧图片的播放时长 (毫秒)
 * 2. 组件 duration vs 单帧 duration 优先级
 * 3. 混合使用组件 duration 和单帧 duration
 * 
 * ========================================
 * 重要 API 行为
 * ========================================
 * 当 Images 中任意一帧图片设置了单独的 duration 后，
 * 组件的 duration 属性设置无效!
 * 
 * 即：单帧 duration > 组件 duration
 * 
 * ========================================
 * 如何测试
 * ========================================
 * 测试步骤:
 * 1. 进入 "单帧 duration" 页面
 * 2. 观察不同 duration 设置的播放效果
 * 3. 对比组件 duration 和单帧 duration 的差异
 * 4. 测试混合使用的效果
 * 
 * 预期结果:
 * - 单帧 duration 优先于组件 duration
 * - 未设置 duration 的帧使用组件 duration
 * - 所有帧都设置 duration 时，组件 duration 无效
 * 
 * ========================================
 * ImageAnimator API 知识点
 * ========================================
 * 1. duration 优先级:
 *    - 单帧 duration 优先级最高
 *    - 组件 duration 作为默认值
 *    - 只要有一帧设置了 duration，组件 duration 就无效
 * 
 * 2. 使用场景:
 *    - 均匀播放：只设置组件 duration
 *    - 变速播放：为每帧设置不同的 duration
 *    - 强调某帧：为该帧设置更长的 duration
 * 
 * 3. 注意事项:
 *    - duration 不支持负数
 *    - duration 为 0 时，该帧不显示
 *    - 单位：毫秒 (ms)
 * 
 * 4. 性能考虑:
 *    - 过短的 duration 可能导致播放卡顿
 *    - 建议单帧 duration >= 100ms
 */

@Entry
@Component
struct ImageAnimatorExample018 {
  @State animationState: AnimationStatus = AnimationStatus.Initial;
  @State currentStatus: string = 'Initial';
  @State demoMode: number = 1;
  @State componentDuration: number = 2000;

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('单帧 duration 专项示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildDescription()
        this.buildDemo1()
        this.buildDemo2()
        this.buildDemo3()
        this.buildControlPanel()
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
      Text('API 重要说明')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0xFF5722)

      Text('当 Images 中任意一帧图片设置了单独的 duration 后，')
        .fontSize(14)
        .fontColor(0x666666)

      Text('该组件的 duration 属性设置无效。')
        .fontSize(14)
        .fontWeight(FontWeight.Bold)
        .fontColor(0xFF5722)

      Text('优先级：单帧 duration > 组件 duration')
        .fontSize(14)
        .fontColor(0x2196F3)
        .backgroundColor(0xE3F2FD)
        .padding(10)
        .borderRadius(10)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildDemo1() {
    Column({ space: 15 }) {
      Text('示例 1: 只设置组件 duration (均匀播放)')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      Text('所有帧平均分配 2000ms，每帧 500ms')
        .fontSize(12)
        .fontColor(Color.Gray)

      ImageAnimator()
        .images([
          { src: $r('app.media.img1') },
          { src: $r('app.media.img2') },
          { src: $r('app.media.img3') },
          { src: $r('app.media.img4') }
        ])
        // 组件 duration：2000ms / 4 帧 = 每帧 500ms
        .duration(this.componentDuration)
        .state(this.animationState)
        .iterations(-1)
        .width(300)
        .height(200)
        .onStart(() => {
          this.currentStatus = 'Running (均匀播放)';
        })
        .onPause(() => {
          this.currentStatus = 'Paused';
        })

      Row({ space: 10 }) {
        Text('组件 duration:')
          .fontSize(14)
          .fontColor(Color.Gray)
        Text(this.componentDuration + 'ms')
          .fontSize(14)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Blue)
        Text('(每帧 ' + (this.componentDuration / 4) + 'ms)')
          .fontSize(14)
          .fontColor(Color.Gray)
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildDemo2() {
    Column({ space: 15 }) {
      Text('示例 2: 设置单帧 duration (变速播放)')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      Text('每帧单独设置 duration，组件 duration 无效')
        .fontSize(12)
        .fontColor(Color.Orange)

      ImageAnimator()
        .images([
          { src: $r('app.media.img1'), duration: 1000 },  // 1 秒
          { src: $r('app.media.img2'), duration: 500 },   // 0.5 秒
          { src: $r('app.media.img3'), duration: 200 },   // 0.2 秒
          { src: $r('app.media.img4'), duration: 1500 }   // 1.5 秒 (强调)
        ])
        // 组件 duration 无效 (因为有单帧 duration)
        .duration(this.componentDuration)
        .state(this.animationState)
        .iterations(-1)
        .width(300)
        .height(200)
        .onStart(() => {
          this.currentStatus = 'Running (变速播放)';
        })

      Column({ space: 5 }) {
        Text('单帧 duration 设置:')
          .fontSize(12)
          .fontColor(Color.Gray)
        Text('帧 1: 1000ms | 帧 2: 500ms | 帧 3: 200ms | 帧 4: 1500ms')
          .fontSize(12)
          .fontColor(Color.Blue)
        Text('总时长：3200ms (组件 duration 无效)')
          .fontSize(12)
          .fontColor(Color.Orange)
      }
      .padding(10)
      .backgroundColor(0xFFF3E0)
      .borderRadius(10)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildDemo3() {
    Column({ space: 15 }) {
      Text('示例 3: 混合使用 (部分帧设置 duration)')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      Text('只要有一帧设置了 duration，组件 duration 就无效')
        .fontSize(12)
        .fontColor(Color.Red)

      ImageAnimator()
        .images([
          { src: $r('app.media.img1'), duration: 800 },  // 设置
          { src: $r('app.media.img2') },                  // 未设置
          { src: $r('app.media.img3'), duration: 400 },  // 设置
          { src: $r('app.media.img4') }                   // 未设置
        ])
        // 组件 duration 无效 (因为部分帧有 duration)
        .duration(this.componentDuration)
        .state(this.animationState)
        .iterations(-1)
        .width(300)
        .height(200)
        .onStart(() => {
          this.currentStatus = 'Running (混合模式)';
        })

      Column({ space: 5 }) {
        Text('混合模式说明:')
          .fontSize(12)
          .fontColor(Color.Gray)
        Text('帧 1: 800ms (单帧) | 帧 2: 0ms (组件无效)')
          .fontSize(12)
          .fontColor(Color.Blue)
        Text('帧 3: 400ms (单帧) | 帧 4: 0ms (组件无效)')
          .fontSize(12)
          .fontColor(Color.Blue)
        Text('⚠️ 未设置 duration 的帧显示时间为 0')
          .fontSize(12)
          .fontColor(Color.Red)
      }
      .padding(10)
      .backgroundColor(0xFFEBEE)
      .borderRadius(10)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildControlPanel() {
    Column({ space: 15 }) {
      Text('控制面板')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      Row({ space: 10 }) {
        Button('开始')
          .fontSize(14)
          .backgroundColor(Color.Green)
          .onClick(() => {
            this.animationState = AnimationStatus.Running;
            this.currentStatus = 'Running';
          })

        Button('暂停')
          .fontSize(14)
          .backgroundColor(Color.Orange)
          .onClick(() => {
            this.animationState = AnimationStatus.Paused;
            this.currentStatus = 'Paused';
          })

        Button('停止')
          .fontSize(14)
          .backgroundColor(Color.Red)
          .onClick(() => {
            this.animationState = AnimationStatus.Stopped;
            this.currentStatus = 'Stopped';
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)

      Column({ space: 10 }) {
        Text('组件 duration: ' + this.componentDuration + 'ms')
          .fontSize(14)
          .fontColor(Color.Gray)
        Slider({ value: this.componentDuration, min: 400, max: 4000, step: 200 })
          .onChange((value: number) => {
            this.componentDuration = value;
          })
          .width('100%')
        Text('(仅在示例 1 中生效)')
          .fontSize(12)
          .fontColor(Color.Gray)
      }
      .width('100%')
      .padding(10)
      .backgroundColor(0xF5F5F5)
      .borderRadius(10)

      Text('当前状态：' + this.currentStatus)
        .fontSize(14)
        .fontColor(Color.Blue)
        .padding(10)
        .backgroundColor(0xE3F2FD)
        .borderRadius(10)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xE8F5E9)
    .borderRadius(15)
  }
}
