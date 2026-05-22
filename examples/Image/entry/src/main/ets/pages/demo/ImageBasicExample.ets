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
struct ImageBasicExample {
  @State imageSrc: Resource | string = $r('app.media.startIcon');
  @State currentObjectFit: ImageFit = ImageFit.Cover;
  @State imageWidth: number = 300;
  @State imageHeight: number = 200;
  @State altSrc: Resource = $r('app.media.foreground');
  @State syncLoadEnabled: boolean = false;
  @Status autoResizeEnabled: boolean = true;
  @State loadStatus: string = '未加载';
  @State errorMessage: string = '';

  private objectFitList: ImageFit[] = [
    ImageFit.Cover,
    ImageFit.Contain,
    ImageFit.Fill,
    ImageFit.None,
    ImageFit.ScaleDown
  ];
  private objectFitIndex: number = 0;

  private getObjectFitName(fit: ImageFit): string {
    switch (fit) {
      case ImageFit.Cover:
        return 'Cover';
      case ImageFit.Contain:
        return 'Contain';
      case ImageFit.Fill:
        return 'Fill';
      case ImageFit.None:
        return 'None';
      case ImageFit.ScaleDown:
        return 'ScaleDown';
      default:
        return 'Unknown';
    }
  }

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('Image 基础用法示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .textAlign(TextAlign.Center)
          .width('100%')
          .margin({ top: 20, bottom: 10 })

        Divider().strokeWidth(1).color(Color.Gray)

        Column() {
          Text('图片展示区域')
            .fontSize(16)
            .fontColor(Color.Gray)
            .margin({ bottom: 10 })

          Image(this.imageSrc)
            .alt(this.altSrc)
            .objectFit(this.currentObjectFit)
            .autoResize(this.autoResizeEnabled)
            .syncLoad(this.syncLoadEnabled)
            .width(this.imageWidth)
            .height(this.imageHeight)
            .borderRadius(12)
            .border({ width: 1, color: '#e0e0e0' })
            .onComplete((event?) => {
              if (event) {
                this.loadStatus = `加载成功: ${event.width}x${event.height}`;
              }
            })
            .onError((error) => {
              this.errorMessage = `加载失败: ${error.message}`;
              this.loadStatus = '加载失败';
            })
        }
        .padding(15)
        .backgroundColor('#f8f8f8')
        .borderRadius(12)
        .width('100%')
        .alignItems(HorizontalAlign.Center)

        Text(`状态: ${this.loadStatus}`)
          .fontSize(14)
          .fontColor(this.loadStatus === '加载失败' ? Color.Red : Color.Green)
          .width('100%')
          .textAlign(TextAlign.Center)

        if (this.errorMessage) {
          Text(this.errorMessage)
            .fontSize(12)
            .fontColor(Color.Red)
            .width('90%')
            .textAlign(TextAlign.Center)
            .margin({ top: 5 })
        }

        Column({ space: 10 }) {
          Text('图片源选择')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Row({ space: 10 }) {
            Button('资源图片')
              .onClick(() => {
                this.imageSrc = $r('app.media.startIcon');
                this.loadStatus = '切换中...';
                this.errorMessage = '';
              })
              .fontSize(14)
              .layoutWeight(1)

            Button('占位图')
              .onClick(() => {
                this.imageSrc = $r('app.media.foreground');
                this.loadStatus = '切换中...';
                this.errorMessage = '';
              })
              .fontSize(14)
              .layoutWeight(1)
          }
          .width('100%')

          Row({ space: 10 }) {
            Button('错误图片')
              .onClick(() => {
                this.imageSrc = 'invalid_image_path.png';
                this.loadStatus = '加载中...';
                this.errorMessage = '';
              })
              .fontSize(14)
              .layoutWeight(1)
              .backgroundColor('#F44336')

            Button('网络图片')
              .onClick(() => {
                this.imageSrc = 'https://example.com/test.png';
                this.loadStatus = '加载中...';
                this.errorMessage = '';
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
          Text('ObjectFit 模式')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Text(`当前: ${this.getObjectFitName(this.currentObjectFit)}`)
            .fontSize(14)
            .fontColor('#2196F3')
            .width('100%')

          Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Start }) {
            ForEach(this.objectFitList, (fit: ImageFit) => {
              Button(this.getObjectFitName(fit))
                .onClick(() => {
                  this.currentObjectFit = fit;
                })
                .fontSize(12)
                .height(32)
                .margin(3)
                .backgroundColor(this.currentObjectFit === fit ? '#2196F3' : '#e0e0e0')
                .fontColor(this.currentObjectFit === fit ? Color.White : Color.Black)
            })
          }
          .width('100%')
        }
        .padding(15)
        .backgroundColor('#fff')
        .borderRadius(12)
        .width('100%')

        Column({ space: 10 }) {
          Text('尺寸调节')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Row({ space: 10 }) {
            Text('宽度:')
              .fontSize(14)
              .width(50)
            Slider({
              value: this.imageWidth,
              min: 100,
              max: 400,
              step: 10,
              style: SliderStyle.OutSet
            })
              .onChange((value: number) => {
                this.imageWidth = value;
              })
              .layoutWeight(1)
            Text(`${this.imageWidth}`)
              .fontSize(14)
              .width(40)
          }
          .width('100%')

          Row({ space: 10 }) {
            Text('高度:')
              .fontSize(14)
              .width(50)
            Slider({
              value: this.imageHeight,
              min: 80,
              max: 350,
              step: 10,
              style: SliderStyle.OutSet
            })
              .onChange((value: number) => {
                this.imageHeight = value;
              })
              .layoutWeight(1)
            Text(`${this.imageHeight}`)
              .fontSize(14)
              .width(40)
          }
          .width('100%')

          Row({ space: 20 }) {
            Row({ space: 8 }) {
              Toggle({ type: ToggleType.Checkbox, isOn: this.syncLoadEnabled })
                .onChange((value: boolean) => {
                  this.syncLoadEnabled = value;
                })
              Text('同步加载')
                .fontSize(14)
            }

            Row({ space: 8 }) {
              Toggle({ type: ToggleType.Checkbox, isOn: this.autoResizeEnabled })
                .onChange((value: boolean) => {
                  this.autoResizeEnabled = value;
                })
              Text('自动调整')
                .fontSize(14)
            }
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)
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
}
