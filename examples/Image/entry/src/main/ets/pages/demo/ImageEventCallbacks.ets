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

interface EventRecord {
  time: string;
  type: string;
  detail: string;
}

@Entry
@Component
struct ImageEventCallbacks {
  @State imageSrc: Resource | string = $r('app.media.startIcon');
  @State eventRecords: EventRecord[] = [];
  @State lastEventType: string = '';
  @State imageLoaded: boolean = false;
  @State imageWidth: number = 0;
  @State imageHeight: number = 0;
  @State componentWidth: number = 0;
  @State componentHeight: number = 0;
  @State contentWidth: number = 0;
  @State contentHeight: number = 0;
  @State svgFinished: boolean = false;
  @State clickCount: number = 0;

  private maxRecords: number = 20;

  private addRecord(type: string, detail: string): void {
    let now = new Date();
    let time = `${now.getHours().toString().padStart(2, '0')}:${now.getMinutes().toString().padStart(2, '0')}:${now.getSeconds().toString().padStart(2, '0')}`;
    this.eventRecords = [{ time, type, detail }, ...this.eventRecords].slice(0, this.maxRecords);
    this.lastEventType = type;
  }

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('Image 事件回调示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .textAlign(TextAlign.Center)
          .width('100%')
          .margin({ top: 20, bottom: 10 })

        Divider().strokeWidth(1).color(Color.Gray)

        Column() {
          Image(this.imageSrc)
            .alt($r('app.media.foreground'))
            .objectFit(ImageFit.Cover)
            .width(280)
            .height(200)
            .borderRadius(12)
            .border({ width: 1, color: '#e0e0e0' })
            .onComplete((event?) => {
              if (event) {
                this.imageLoaded = true;
                this.imageWidth = event.width;
                this.imageHeight = event.height;
                this.componentWidth = event.componentWidth;
                this.componentHeight = event.componentHeight;
                this.contentWidth = event.contentWidth;
                this.contentHeight = event.contentHeight;
                this.addRecord('onComplete',
                  `src:${event.width}x${event.height} component:${event.componentWidth}x${event.componentHeight}`);
              }
            })
            .onError((error) => {
              this.imageLoaded = false;
              this.addRecord('onError', `${error.message} component:${error.componentWidth}x${error.componentHeight}`);
            })
            .onFinish(() => {
              this.svgFinished = true;
              this.addRecord('onFinish', 'SVG动画播放完成');
            })
            .onClick(() => {
              this.clickCount++;
              this.addRecord('onClick', `第${this.clickCount}次点击`);
            })
        }
        .padding(15)
        .backgroundColor('#f8f8f8')
        .borderRadius(12)
        .width('100%')
        .alignItems(HorizontalAlign.Center)

        Column({ space: 8 }) {
          Text('图片信息')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Row() {
            Text('加载状态: ')
              .fontSize(14)
              .fontColor(Color.Gray)
            Text(this.imageLoaded ? '已加载' : '未加载')
              .fontSize(14)
              .fontColor(this.imageLoaded ? Color.Green : Color.Orange)
              .fontWeight(FontWeight.Bold)
          }
          .width('100%')

          if (this.imageLoaded) {
            Row() {
              Text('源图尺寸: ')
                .fontSize(14)
                .fontColor(Color.Gray)
              Text(`${this.imageWidth} x ${this.imageHeight}`)
                .fontSize(14)
                .fontWeight(FontWeight.Bold)
            }
            .width('100%')

            Row() {
              Text('组件尺寸: ')
                .fontSize(14)
                .fontColor(Color.Gray)
              Text(`${this.componentWidth} x ${this.componentHeight}`)
                .fontSize(14)
                .fontWeight(FontWeight.Bold)
            }
            .width('100%')

            Row() {
              Text('绘制尺寸: ')
                .fontSize(14)
                .fontColor(Color.Gray)
              Text(`${this.contentWidth.toFixed(0)} x ${this.contentHeight.toFixed(0)}`)
                .fontSize(14)
                .fontWeight(FontWeight.Bold)
            }
            .width('100%')
          }

          if (this.svgFinished) {
            Row() {
              Text('SVG: ')
                .fontSize(14)
                .fontColor(Color.Gray)
              Text('播放完成')
                .fontSize(14)
                .fontColor(Color.Blue)
                .fontWeight(FontWeight.Bold)
            }
            .width('100%')
          }

          Row() {
            Text('点击次数: ')
              .fontSize(14)
              .fontColor(Color.Gray)
            Text(`${this.clickCount}`)
              .fontSize(14)
              .fontWeight(FontWeight.Bold)
          }
          .width('100%')

          Row() {
            Text('最近事件: ')
              .fontSize(14)
              .fontColor(Color.Gray)
            Text(this.lastEventType || '无')
              .fontSize(14)
              .fontColor('#2196F3')
              .fontWeight(FontWeight.Bold)
          }
          .width('100%')
        }
        .padding(15)
        .backgroundColor('#fff')
        .borderRadius(12)
        .width('100%')

        Column({ space: 10 }) {
          Text('切换图片源')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Row({ space: 10 }) {
            Button('资源图片')
              .onClick(() => {
                this.imageSrc = $r('app.media.startIcon');
                this.imageLoaded = false;
                this.svgFinished = false;
                this.addRecord('切换', '资源图片');
              })
              .fontSize(14)
              .layoutWeight(1)

            Button('占位图片')
              .onClick(() => {
                this.imageSrc = $r('app.media.background');
                this.imageLoaded = false;
                this.addRecord('切换', '占位图片');
              })
              .fontSize(14)
              .layoutWeight(1)
          }
          .width('100%')

          Button('触发错误')
            .onClick(() => {
              this.imageSrc = 'non_existent_image.png';
              this.imageLoaded = false;
              this.addRecord('切换', '无效图片');
            })
            .fontSize(14)
            .width('100%')
            .backgroundColor('#F44336')
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

          List({ space: 4 }) {
            ForEach(this.eventRecords, (record: EventRecord, index?: number) => {
              ListItem() {
                Row({ space: 8 }) {
                  Text(record.time)
                    .fontSize(11)
                    .fontColor(Color.Gray)
                    .width(60)
                  Text(`[${record.type}]`)
                    .fontSize(11)
                    .fontColor(this.getEventColor(record.type))
                    .fontWeight(FontWeight.Bold)
                    .width(80)
                  Text(record.detail)
                    .fontSize(11)
                    .fontColor('#333')
                    .layoutWeight(1)
                }
                .width('100%')
                .padding({ left: 8, right: 8, top: 4, bottom: 4 })
                .backgroundColor(index !== undefined && index % 2 === 0 ? '#f9f9f9' : '#fff')
                .borderRadius(4)
              }
            })
          }
          .height(200)
          .width('100%')

          Row({ space: 10 }) {
            Button('清除日志')
              .onClick(() => {
                this.eventRecords = [];
              })
              .fontSize(12)
              .height(30)
              .backgroundColor('#607D8B')
              .layoutWeight(1)

            Button('重置统计')
              .onClick(() => {
                this.eventRecords = [];
                this.clickCount = 0;
                this.lastEventType = '';
              })
              .fontSize(12)
              .height(30)
              .backgroundColor('#795548')
              .layoutWeight(1)
          }
          .width('100%')
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

  private getEventColor(type: string): ResourceColor {
    switch (type) {
      case 'onComplete':
        return Color.Green;
      case 'onError':
        return Color.Red;
      case 'onClick':
        return '#2196F3';
      case 'onFinish':
        return '#9C27B0';
      case '切换':
        return '#FF9800';
      default:
        return Color.Gray;
    }
  }
}
