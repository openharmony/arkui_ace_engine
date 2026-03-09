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
 * Image 综合示例 - 展示 Image 组件的主要接口
 */
@Entry
@Component
struct ImageComprehensiveExample {
  @State currentImageFit: ImageFit = ImageFit.Cover;
  @State currentRenderMode: ImageRenderMode = ImageRenderMode.Original;
  @State currentInterpolation: ImageInterpolation = ImageInterpolation.Low;
  @State currentObjectRepeat: ImageRepeat = ImageRepeat.NoRepeat;
  @State currentDynamicRangeMode: DynamicRangeMode = DynamicRangeMode.Standard;
  @State isAutoResize: boolean = false;
  @State isSyncLoad: boolean = false;
  @State isMatchTextDirection: boolean = false;
  @State isFitOriginalSize: boolean = false;
  @State isDraggable: boolean = true;
  @State hdrBrightness: number = 1.0;
  @State loadStatus: string = '等待加载';
  @State errorMessage: string = '';

  imageFitOptions: ImageFit[] = [
    ImageFit.Cover,
    ImageFit.Contain,
    ImageFit.Fill,
    ImageFit.None,
    ImageFit.ScaleDown
  ];

  imageFitNames: string[] = ['Cover', 'Contain', 'Fill', 'None', 'ScaleDown'];

  renderModeOptions: ImageRenderMode[] = [
    ImageRenderMode.Original,
    ImageRenderMode.Template
  ];

  renderModeNames: string[] = ['Original', 'Template'];

  interpolationOptions: ImageInterpolation[] = [
    ImageInterpolation.None,
    ImageInterpolation.Low,
    ImageInterpolation.Medium,
    ImageInterpolation.High
  ];

  interpolationNames: string[] = ['None', 'Low', 'Medium', 'High'];

  objectRepeatOptions: ImageRepeat[] = [
    ImageRepeat.NoRepeat,
    ImageRepeat.X,
    ImageRepeat.Y,
    ImageRepeat.XY
  ];

  objectRepeatNames: string[] = ['NoRepeat', 'X', 'Y', 'XY'];

  dynamicRangeModeOptions: DynamicRangeMode[] = [
    DynamicRangeMode.HIGH,
    DynamicRangeMode.CONSTRAINT,
    DynamicRangeMode.STANDARD
  ];

  dynamicRangeModeNames: string[] = ['HIGH', 'CONSTRAINT', 'STANDARD'];

  build() {
    Column() {
      Text('Image 综合示例')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Scroll() {
        Column({ space: 20 }) {
          // 图片展示区域
          Column({ space: 10 }) {
            Text('图片预览')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)

            Image($r('app.media.img'))
              .width(300)
              .height(300)
              .border({ width: 2, color: Color.Blue })
              .objectFit(this.currentImageFit)
              .renderMode(this.currentRenderMode)
              .interpolation(this.currentInterpolation)
              .objectRepeat(this.currentObjectRepeat)
              .dynamicRangeMode(this.currentDynamicRangeMode)
              .autoResize(this.isAutoResize)
              .syncLoad(this.isSyncLoad)
              .matchTextDirection(this.isMatchTextDirection)
              .fitOriginalSize(this.isFitOriginalSize)
              .draggable(this.isDraggable)
              .hdrBrightness(this.hdrBrightness)
              .alt($r('app.media.placeholder'))
              .sourceSize({ width: 300, height: 300 })
              .onComplete((event) => {
                this.loadStatus = `加载成功: ${event.width}x${event.height}`;
              })
              .onError((error) => {
                this.errorMessage = `加载失败: ${error.componentCode} - ${error.message}`;
              })

            Text(this.loadStatus)
              .fontSize(14)
              .fontColor(Color.Green)

            if (this.errorMessage) {
              Text(this.errorMessage)
                .fontSize(14)
                .fontColor(Color.Red)
            }
          }
          .padding(15)
          .backgroundColor(0xF0F0F0)
          .borderRadius(10)

          // objectFit 属性
          Column({ space: 10 }) {
            Text('objectFit: ' + this.imageFitNames[this.imageFitOptions.indexOf(this.currentImageFit)])
              .fontSize(16)
              .fontWeight(FontWeight.Medium)

            Row({ space: 10 }) {
              ForEach(this.imageFitOptions, (option: ImageFit, index: number) => {
                Button(this.imageFitNames[index])
                  .type(this.currentImageFit === option ? ButtonType.Capsule : ButtonType.Normal)
                  .backgroundColor(this.currentImageFit === option ? 0x007DFF : 0xE5E5E5)
                  .onClick(() => {
                    this.currentImageFit = option;
                  })
              })
            }
          }
          .padding(15)
          .backgroundColor(0xF9F9F9)
          .borderRadius(10)

          // renderMode 属性
          Column({ space: 10 }) {
            Text('renderMode: ' + this.renderModeNames[this.renderModeOptions.indexOf(this.currentRenderMode)])
              .fontSize(16)
              .fontWeight(FontWeight.Medium)

            Row({ space: 10 }) {
              ForEach(this.renderModeOptions, (option: ImageRenderMode, index: number) => {
                Button(this.renderModeNames[index])
                  .type(this.currentRenderMode === option ? ButtonType.Capsule : ButtonType.Normal)
                  .backgroundColor(this.currentRenderMode === option ? 0x007DFF : 0xE5E5E5)
                  .onClick(() => {
                    this.currentRenderMode = option;
                  })
              })
            }
          }
          .padding(15)
          .backgroundColor(0xF9F9F9)
          .borderRadius(10)

          // interpolation 属性
          Column({ space: 10 }) {
            Text('interpolation: ' + this.interpolationNames[this.interpolationOptions.indexOf(this.currentInterpolation)])
              .fontSize(16)
              .fontWeight(FontWeight.Medium)

            Row({ space: 10 }) {
              ForEach(this.interpolationOptions, (option: ImageInterpolation, index: number) => {
                Button(this.interpolationNames[index])
                  .type(this.currentInterpolation === option ? ButtonType.Capsule : ButtonType.Normal)
                  .backgroundColor(this.currentInterpolation === option ? 0x007DFF : 0xE5E5E5)
                  .onClick(() => {
                    this.currentInterpolation = option;
                  })
              })
            }
          }
          .padding(15)
          .backgroundColor(0xF9F9F9)
          .borderRadius(10)

          // objectRepeat 属性
          Column({ space: 10 }) {
            Text('objectRepeat: ' + this.objectRepeatNames[this.objectRepeatOptions.indexOf(this.currentObjectRepeat)])
              .fontSize(16)
              .fontWeight(FontWeight.Medium)

            Row({ space: 10 }) {
              ForEach(this.objectRepeatOptions, (option: ImageRepeat, index: number) => {
                Button(this.objectRepeatNames[index])
                  .type(this.currentObjectRepeat === option ? ButtonType.Capsule : ButtonType.Normal)
                  .backgroundColor(this.currentObjectRepeat === option ? 0x007DFF : 0xE5E5E5)
                  .onClick(() => {
                    this.currentObjectRepeat = option;
                  })
              })
            }
          }
          .padding(15)
          .backgroundColor(0xF9F9F9)
          .borderRadius(10)

          // dynamicRangeMode 属性
          Column({ space: 10 }) {
            Text('dynamicRangeMode: ' + this.dynamicRangeModeNames[this.dynamicRangeModeOptions.indexOf(this.currentDynamicRangeMode)])
              .fontSize(16)
              .fontWeight(FontWeight.Medium)

            Row({ space: 10 }) {
              ForEach(this.dynamicRangeModeOptions, (option: DynamicRangeMode, index: number) => {
                Button(this.dynamicRangeModeNames[index])
                  .type(this.currentDynamicRangeMode === option ? ButtonType.Capsule : ButtonType.Normal)
                  .backgroundColor(this.currentDynamicRangeMode === option ? 0x007DFF : 0xE5E5E5)
                  .onClick(() => {
                    this.currentDynamicRangeMode = option;
                  })
              })
            }
          }
          .padding(15)
          .backgroundColor(0xF9F9F9)
          .borderRadius(10)

          // 布尔属性
          Column({ space: 10 }) {
            Text('布尔属性')
              .fontSize(16)
              .fontWeight(FontWeight.Medium)

            Row({ space: 20 }) {
              Toggle({ type: ToggleType.Switch, isOn: this.isAutoResize })
                .onChange((isOn: boolean) => {
                  this.isAutoResize = isOn;
                })
              Text('autoResize')

              Toggle({ type: ToggleType.Switch, isOn: this.isSyncLoad })
                .onChange((isOn: boolean) => {
                  this.isSyncLoad = isOn;
                })
              Text('syncLoad')
            }

            Row({ space: 20 }) {
              Toggle({ type: ToggleType.Switch, isOn: this.isMatchTextDirection })
                .onChange((isOn: boolean) => {
                  this.isMatchTextDirection = isOn;
                })
              Text('matchTextDirection')

              Toggle({ type: ToggleType.Switch, isOn: this.isFitOriginalSize })
                .onChange((isOn: boolean) => {
                  this.isFitOriginalSize = isOn;
                })
              Text('fitOriginalSize')
            }

            Row({ space: 20 }) {
              Toggle({ type: ToggleType.Switch, isOn: this.isDraggable })
                .onChange((isOn: boolean) => {
                  this.isDraggable = isOn;
                })
              Text('draggable')
            }
          }
          .padding(15)
          .backgroundColor(0xF9F9F9)
          .borderRadius(10)

          // hdrBrightness 属性
          Column({ space: 10 }) {
            Text('hdrBrightness: ' + this.hdrBrightness.toFixed(2))
              .fontSize(16)
              .fontWeight(FontWeight.Medium)

            Slider({
              value: this.hdrBrightness,
              min: 0.5,
              max: 2.0,
              step: 0.1
            })
              .width('100%')
              .onChange((value: number) => {
                this.hdrBrightness = value;
              })
          }
          .padding(15)
          .backgroundColor(0xF9F9F9)
          .borderRadius(10)
        }
        .padding(20)
      }
      .layoutWeight(1)
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
