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
 * AnimationStopModeTest - AnimationStopMode 用例 (API 24+)
 * ========================================
 *
 * 测试功能说明:
 * 验证 AnimationOptions.stopMode 属性
 * 控制动图停止时的行为（回到首帧或停留在最后一帧）
 *
 * 涉及的 API:
 * 1. AnimationStopMode.FIRST_FRAME - 动图停止时回到首帧
 * 2. AnimationStopMode.LAST_FRAME - 动图停止时停留在最后一帧
 * 3. AnimationOptions.stopMode - 设置停止模式
 *
 * ========================================
 * API 文档说明
 * ========================================
 * AnimationStopMode 枚举:
 *   FIRST_FRAME = 0  动图停止时回到首帧（默认值）
 *   LAST_FRAME = 1   动图停止时停留在最后一帧
 *
 * AnimationOptions.stopMode:
 *   默认值 AnimationStopMode.FIRST_FRAME
 *   此接口仅可在 Stage 模型下使用
 */

import { AnimatedDrawableDescriptor, AnimationStopMode } from '@kit.ArkUI';

@Entry
@Component
struct AnimationStopModeTest {
  @State stopModeName: string = 'FIRST_FRAME';
  @State currentStopMode: AnimationStopMode = AnimationStopMode.FIRST_FRAME;
  @State animationStatus: string = 'Initial';
  @State testResult: string = '等待测试...';

  // FIRST_FRAME 模式: 停止后回到首帧
  private drawableFirstFrame?: AnimatedDrawableDescriptor;
  // LAST_FRAME 模式: 停止后停在最后一帧
  private drawableLastFrame?: AnimatedDrawableDescriptor;

  aboutToAppear() {
    this.createDrawables();
  }

  createDrawables() {
    // 使用 stopMode: FIRST_FRAME (默认)
    this.drawableFirstFrame = new AnimatedDrawableDescriptor(
      $r('app.media.flower'),
      {
        duration: 2000,
        iterations: 1,
        stopMode: AnimationStopMode.FIRST_FRAME,
        autoPlay: false
      }
    );

    // 使用 stopMode: LAST_FRAME
    this.drawableLastFrame = new AnimatedDrawableDescriptor(
      $r('app.media.flower'),
      {
        duration: 2000,
        iterations: 1,
        stopMode: AnimationStopMode.LAST_FRAME,
        autoPlay: false
      }
    );
  }

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('AnimationStopMode 用例 (API 24+)')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        // API 说明
        this.buildApiInfo()

        // 对比展示
        this.buildComparison()

        // 控制面板
        this.buildControlPanel()

        // 测试结果
        this.buildResult()
      }
      .width('100%')
      .padding({ left: 20, right: 20, bottom: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xF5F5F5)
  }

  @Builder
  buildApiInfo() {
    Column({ space: 10 }) {
      Text('AnimationStopMode 枚举')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      Row({ space: 15 }) {
        Column({ space: 5 }) {
          Text('FIRST_FRAME')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .fontColor(0x2196F3)
          Text('值: 0')
            .fontSize(12)
            .fontColor(0x666666)
          Text('停止时回到首帧（默认）')
            .fontSize(12)
            .fontColor(0x999999)
        }
        .padding(10)
        .backgroundColor(0xE3F2FD)
        .borderRadius(10)
        .layoutWeight(1)

        Column({ space: 5 }) {
          Text('LAST_FRAME')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .fontColor(0xFF9800)
          Text('值: 1')
            .fontSize(12)
            .fontColor(0x666666)
          Text('停止时停留在最后一帧')
            .fontSize(12)
            .fontColor(0x999999)
        }
        .padding(10)
        .backgroundColor(0xFFF3E0)
        .borderRadius(10)
        .layoutWeight(1)
      }
      .width('100%')

      Text('注意: 此接口仅可在 Stage 模型下使用')
        .fontSize(12)
        .fontColor(Color.Orange)
        .backgroundColor(0xFFF3E0)
        .padding(10)
        .borderRadius(5)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildComparison() {
    Column({ space: 15 }) {
      Text('效果对比 (点击播放后等待完成)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      Row({ space: 20 }) {
        // FIRST_FRAME
        Column({ space: 8 }) {
          Text('FIRST_FRAME')
            .fontSize(14)
            .fontColor(0x2196F3)
            .fontWeight(FontWeight.Bold)

          if (this.drawableFirstFrame) {
            Image(this.drawableFirstFrame)
              .width(150)
              .height(150)
              .borderRadius(10)
              .border({ width: 2, color: 0x2196F3 })
              .id('FirstFrameImage')
          }

          Text('停止后 → 回到首帧')
            .fontSize(12)
            .fontColor(0x666666)

          Button('播放 1 次')
            .fontSize(12)
            .onClick(() => {
              const controller = this.drawableFirstFrame?.getAnimationController('FirstFrameImage');
              controller?.start();
              this.testResult = 'FIRST_FRAME 模式: 播放中...';
            })
        }
        .padding(10)
        .backgroundColor(0xF8F8F8)
        .borderRadius(10)

        // LAST_FRAME
        Column({ space: 8 }) {
          Text('LAST_FRAME')
            .fontSize(14)
            .fontColor(0xFF9800)
            .fontWeight(FontWeight.Bold)

          if (this.drawableLastFrame) {
            Image(this.drawableLastFrame)
              .width(150)
              .height(150)
              .borderRadius(10)
              .border({ width: 2, color: 0xFF9800 })
              .id('LastFrameImage')
          }

          Text('停止后 → 停在最后帧')
            .fontSize(12)
            .fontColor(0x666666)

          Button('播放 1 次')
            .fontSize(12)
            .onClick(() => {
              const controller = this.drawableLastFrame?.getAnimationController('LastFrameImage');
              controller?.start();
              this.testResult = 'LAST_FRAME 模式: 播放中...';
            })
        }
        .padding(10)
        .backgroundColor(0xF8F8F8)
        .borderRadius(10)
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
    .alignItems(HorizontalAlign.Center)
  }

  @Builder
  buildControlPanel() {
    Column({ space: 15 }) {
      Text('手动停止控制')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      Row({ space: 10 }) {
        Button('Start FIRST_FRAME')
          .fontSize(11)
          .backgroundColor(0x2196F3)
          .onClick(() => {
            this.drawableFirstFrame?.getAnimationController('FirstFrameImage')?.start();
            this.testResult = 'FIRST_FRAME: 播放中';
          })

        Button('Stop FIRST_FRAME')
          .fontSize(11)
          .backgroundColor(Color.Red)
          .onClick(() => {
            this.drawableFirstFrame?.getAnimationController('FirstFrameImage')?.stop();
            this.testResult = 'FIRST_FRAME: 已停止（回到首帧）';
          })
      }

      Row({ space: 10 }) {
        Button('Start LAST_FRAME')
          .fontSize(11)
          .backgroundColor(0xFF9800)
          .onClick(() => {
            this.drawableLastFrame?.getAnimationController('LastFrameImage')?.start();
            this.testResult = 'LAST_FRAME: 播放中';
          })

        Button('Stop LAST_FRAME')
          .fontSize(11)
          .backgroundColor(Color.Red)
          .onClick(() => {
            this.drawableLastFrame?.getAnimationController('LastFrameImage')?.stop();
            this.testResult = 'LAST_FRAME: 已停止（停在最后帧）';
          })
      }

      Row({ space: 10 }) {
        Button('查询状态 FIRST')
          .fontSize(11)
          .backgroundColor(Color.Gray)
          .onClick(() => {
            const status = this.drawableFirstFrame?.getAnimationController('FirstFrameImage')?.getStatus();
            this.testResult = 'FIRST_FRAME 状态: ' + this.statusToString(status);
          })

        Button('查询状态 LAST')
          .fontSize(11)
          .backgroundColor(Color.Gray)
          .onClick(() => {
            const status = this.drawableLastFrame?.getAnimationController('LastFrameImage')?.getStatus();
            this.testResult = 'LAST_FRAME 状态: ' + this.statusToString(status);
          })
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
    .alignItems(HorizontalAlign.Center)
  }

  @Builder
  buildResult() {
    Column({ space: 10 }) {
      Text('测试结果')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      Text(this.testResult)
        .fontSize(14)
        .fontColor(0x2196F3)
        .padding(15)
        .backgroundColor(0xE8F5E9)
        .borderRadius(10)
        .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  statusToString(status?: AnimationStatus): string {
    switch (status) {
      case AnimationStatus.Initial:
        return 'Initial';
      case AnimationStatus.Running:
        return 'Running';
      case AnimationStatus.Paused:
        return 'Paused';
      case AnimationStatus.Stopped:
        return 'Stopped';
      default:
        return 'Unknown';
    }
  }
}
