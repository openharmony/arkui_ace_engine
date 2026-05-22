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
import { router } from '@kit.ArkUI';

@Entry
@Component
struct ImageAnimatorDemo {
  @State animatorState: AnimationStatus = AnimationStatus.Initial;
  @State isReverse: boolean = false;
  @State durationValue: number = 1000;
  @State iterationsValue: number = 1;
  @State fixedSizeEnabled: boolean = true;
  @State fillModeValue: FillMode = FillMode.Forwards;
  @State eventLog: string = '';
  @State animationCount: number = 0;

  private frameList: ImageFrameInfo[] = [
    { src: $r('app.media.startIcon'), width: 200, height: 150, top: 0, left: 0, duration: 300 },
    { src: $r('app.media.foreground'), width: 200, height: 150, top: 0, left: 0, duration: 300 },
    { src: $r('app.media.background'), width: 200, height: 150, top: 0, left: 0, duration: 300 },
  ];

  private addLog(msg: string): void {
    let timestamp = new Date().toLocaleTimeString();
    this.eventLog = `[${timestamp}] ${msg}\n` + this.eventLog;
    if (this.eventLog.length > 500) {
      this.eventLog = this.eventLog.substring(0, 500);
    }
  }

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('ImageAnimator 动画示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .textAlign(TextAlign.Center)
          .width('100%')
          .margin({ top: 20, bottom: 10 })

        Divider().strokeWidth(1).color(Color.Gray)

        Column() {
          Text('动画展示区域')
            .fontSize(16)
            .fontColor(Color.Gray)
            .margin({ bottom: 10 })

          ImageAnimator()
            .images(this.frameList)
            .state(this.animatorState)
            .reverse(this.isReverse)
            .duration(this.durationValue)
            .iterations(this.iterationsValue)
            .fixedSize(this.fixedSizeEnabled)
            .fillMode(this.fillModeValue)
            .width(220)
            .height(170)
            .borderRadius(12)
            .border({ width: 1, color: '#e0e0e0' })
            .onStart(() => {
              this.animationCount++;
              this.addLog(`动画开始 (第${this.animationCount}次)`);
            })
            .onPause(() => {
              this.addLog('动画暂停');
            })
            .onRepeat(() => {
              this.addLog('动画重复');
            })
            .onCancel(() => {
              this.addLog('动画取消');
            })
            .onFinish(() => {
              this.addLog('动画完成');
            })
        }
        .padding(15)
        .backgroundColor('#f8f8f8')
        .borderRadius(12)
        .width('100%')
        .alignItems(HorizontalAlign.Center)

        Column({ space: 10 }) {
          Text('播放控制')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Row({ space: 10 }) {
            Button('播放')
              .onClick(() => {
                this.animatorState = AnimationStatus.Running;
                this.addLog('点击播放');
              })
              .fontSize(14)
              .layoutWeight(1)
              .backgroundColor('#4CAF50')

            Button('暂停')
              .onClick(() => {
                this.animatorState = AnimationStatus.Paused;
                this.addLog('点击暂停');
              })
              .fontSize(14)
              .layoutWeight(1)
              .backgroundColor('#FF9800')

            Button('停止')
              .onClick(() => {
                this.animatorState = AnimationStatus.Stopped;
                this.addLog('点击停止');
              })
              .fontSize(14)
              .layoutWeight(1)
              .backgroundColor('#F44336')

            Button('重置')
              .onClick(() => {
                this.animatorState = AnimationStatus.Initial;
                this.animationCount = 0;
                this.addLog('重置动画');
              })
              .fontSize(14)
              .layoutWeight(1)
              .backgroundColor('#2196F3')
          }
          .width('100%')
        }
        .padding(15)
        .backgroundColor('#fff')
        .borderRadius(12)
        .width('100%')

        Column({ space: 10 }) {
          Text('动画参数')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Row({ space: 10 }) {
            Text('播放方向:')
              .fontSize(14)
              .width(80)
            Toggle({ type: ToggleType.Switch, isOn: this.isReverse })
              .onChange((value: boolean) => {
                this.isReverse = value;
                this.addLog(`方向: ${value ? '反向' : '正向'}`);
              })
            Text(this.isReverse ? '反向' : '正向')
              .fontSize(14)
              .fontColor(this.isReverse ? Color.Red : Color.Green)
          }
          .width('100%')

          Row({ space: 10 }) {
            Text('固定尺寸:')
              .fontSize(14)
              .width(80)
            Toggle({ type: ToggleType.Switch, isOn: this.fixedSizeEnabled })
              .onChange((value: boolean) => {
                this.fixedSizeEnabled = value;
                this.addLog(`固定尺寸: ${value ? '开' : '关'}`);
              })
            Text(this.fixedSizeEnabled ? '开启' : '关闭')
              .fontSize(14)
          }
          .width('100%')

          Row({ space: 10 }) {
            Text('时长(ms):')
              .fontSize(14)
              .width(80)
            Slider({
              value: this.durationValue,
              min: 200,
              max: 5000,
              step: 100,
              style: SliderStyle.OutSet
            })
              .onChange((value: number) => {
                this.durationValue = value;
              })
              .layoutWeight(1)
            Text(`${this.durationValue}`)
              .fontSize(14)
              .width(50)
          }
          .width('100%')

          Row({ space: 10 }) {
            Text('循环次数:')
              .fontSize(14)
              .width(80)
            Slider({
              value: this.iterationsValue,
              min: 1,
              max: 10,
              step: 1,
              style: SliderStyle.OutSet
            })
              .onChange((value: number) => {
                this.iterationsValue = value;
              })
              .layoutWeight(1)
            Text(this.iterationsValue === 1 ? '1次' : `${this.iterationsValue}次`)
              .fontSize(14)
              .width(40)
          }
          .width('100%')

          Row({ space: 8 }) {
            Text('FillMode:')
              .fontSize(14)
              .width(80)
            ForEach([FillMode.Forwards, FillMode.Backwards, FillMode.None], (mode: FillMode) => {
              Button(this.getFillModeName(mode))
                .onClick(() => {
                  this.fillModeValue = mode;
                  this.addLog(`FillMode: ${this.getFillModeName(mode)}`);
                })
                .fontSize(11)
                .height(28)
                .backgroundColor(this.fillModeValue === mode ? '#9C27B0' : '#e0e0e0')
                .fontColor(this.fillModeValue === mode ? Color.White : Color.Black)
            })
          }
          .width('100%')
        }
        .padding(15)
        .backgroundColor('#fff')
        .borderRadius(12)
        .width('100%')

        Column({ space: 5 }) {
          Text('事件日志')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Scroll() {
            Text(this.eventLog || '暂无事件')
              .fontSize(12)
              .fontColor('#333')
              .width('100%')
          }
          .height(120)
          .width('100%')
          .padding(8)
          .backgroundColor('#f0f0f0')
          .borderRadius(8)

          Button('清除日志')
            .onClick(() => {
              this.eventLog = '';
            })
            .fontSize(12)
            .height(30)
            .backgroundColor('#607D8B')
            .margin({ top: 5 })
        }
        .padding(15)
        .backgroundColor('#fff')
        .borderRadius(12)
        .width('100%')

        Button('返回')
          .onClick(() => {
            router.back();
          })
          .width('80%')
          .margin({ bottom: 30 })
      }
      .padding({ left: 15, right: 15 })
    }
    .height('100%')
    .width('100%')
  }

  private getFillModeName(mode: FillMode): string {
    switch (mode) {
      case FillMode.Forwards:
        return 'Forwards';
      case FillMode.Backwards:
        return 'Backwards';
      case FillMode.None:
        return 'None';
      default:
        return '';
    }
  }
}
