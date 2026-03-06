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

import { image } from '@kit.ImageKit';

/**
 * Image 完整功能演示
 * 展示 Image 组件的所有主要功能
 */
@Entry
@Component
struct ImageCompleteDemo {
  @State selectedImageFit: ImageFit = ImageFit.Cover;
  @State selectedRenderMode: ImageRenderMode = ImageRenderMode.Original;
  @State selectedInterpolation: ImageInterpolation = ImageInterpolation.Low;
  @State selectedObjectRepeat: ImageRepeat = ImageRepeat.NoRepeat;
  @State selectedDynamicRangeMode: DynamicRangeMode = DynamicRangeMode.Standard;
  @State selectedRotateOrientation: ImageRotateOrientation = ImageRotateOrientation.AUTO;
  @State isAutoResize: boolean = false;
  @State isSyncLoad: boolean = false;
  @State isMatchTextDirection: boolean = false;
  @State isFitOriginalSize: boolean = false;
  @State isDraggable: boolean = true;
  @State hdrBrightness: number = 1.0;
  @State currentScale: number = 1.0;
  @State currentRotation: number = 0;
  @State currentOpacity: number = 1.0;
  @State pixelMapImage: PixelMap | undefined = undefined;
  @State loadStatus: string = '等待加载';
  @State errorMessage: string = '';
  @State showAdvancedOptions: boolean = false;

  imageFitList: ImageFit[] = [
    ImageFit.Cover,
    ImageFit.Contain,
    ImageFit.Fill,
    ImageFit.None,
    ImageFit.ScaleDown
  ];

  imageFitNames: string[] = ['Cover', 'Contain', 'Fill', 'None', 'ScaleDown'];

  renderModeList: ImageRenderMode[] = [
    ImageRenderMode.Original,
    ImageRenderMode.Template
  ];

  renderModeNames: string[] = ['Original', 'Template'];

  interpolationList: ImageInterpolation[] = [
    ImageInterpolation.None,
    ImageInterpolation.Low,
    ImageInterpolation.Medium,
    ImageInterpolation.High
  ];

  interpolationNames: string[] = ['None', 'Low', 'Medium', 'High'];

  objectRepeatList: ImageRepeat[] = [
    ImageRepeat.NoRepeat,
    ImageRepeat.X,
    ImageRepeat.Y,
    ImageRepeat.XY
  ];

  objectRepeatNames: string[] = ['NoRepeat', 'X', 'Y', 'XY'];

  dynamicRangeModeList: DynamicRangeMode[] = [
    DynamicRangeMode.HIGH,
    DynamicRangeMode.CONSTRAINT,
    DynamicRangeMode.STANDARD
  ];

  dynamicRangeModeNames: string[] = ['HIGH', 'CONSTRAINT', 'STANDARD'];

  rotateOrientationList: ImageRotateOrientation[] = [
    ImageRotateOrientation.AUTO,
    ImageRotateOrientation.UP,
    ImageRotateOrientation.RIGHT,
    ImageRotateOrientation.DOWN,
    ImageRotateOrientation.LEFT
  ];

  rotateOrientationNames: string[] = ['AUTO', 'UP', 'RIGHT', 'DOWN', 'LEFT'];

  aboutToAppear() {
    this.loadPixelMap();
  }

  async loadPixelMap() {
    try {
      const resManager = this.getUIContext().getHostContext()?.resourceManager;
      if (!resManager) {
        return;
      }

      const unit8Array = await resManager.getMediaContent($r('app.media.img').id);
      if (!unit8Array) {
        return;
      }

      const imageSource = image.createImageSource(unit8Array.buffer.slice(0, unit8Array.buffer.byteLength));
      const pixelMap = await imageSource.createPixelMap({
        desiredPixelFormat: image.PixelMapFormat.RGBA_8888
      });
      await imageSource.release();

      this.pixelMapImage = pixelMap;
      this.loadStatus = 'PixelMap 加载成功';
    } catch (error) {
      this.errorMessage = `PixelMap 加载失败: ${error}`;
    }
  }

  @Builder
  ImageControlPanel() {
    Column({ space: 15 }) {
      // objectFit 控制
      Column({ space: 8 }) {
        Text('objectFit: ' + this.imageFitNames[this.imageFitList.indexOf(this.selectedImageFit)])
          .fontSize(14)
          .fontWeight(FontWeight.Medium)

        Flex({ wrap: FlexWrap.Wrap }) {
          ForEach(this.imageFitList, (option: ImageFit, index: number) => {
            Button(this.imageFitNames[index])
              .type(this.selectedImageFit === option ? ButtonType.Capsule : ButtonType.Normal)
              .fontSize(12)
              .backgroundColor(this.selectedImageFit === option ? 0x007DFF : 0xF5F5F5)
              .margin({ right: 8, bottom: 8 })
              .onClick(() => {
                this.selectedImageFit = option;
              })
          })
        }
      }
    }
    .padding(12)
    .backgroundColor(0xFFFFFF)
    .borderRadius(8)
    .shadow({ radius: 4, color: 0x1A000000, offsetX: 0, offsetY: 2 })

    // renderMode 控制
    Column({ space: 8 }) {
      Text('renderMode: ' + this.renderModeNames[this.renderModeList.indexOf(this.selectedRenderMode)])
          .fontSize(14)
          .fontWeight(FontWeight.Medium)

        Row({ space: 10 }) {
          ForEach(this.renderModeList, (option: ImageRenderMode, index: number) => {
            Button(this.renderModeNames[index])
              .type(this.selectedRenderMode === option ? ButtonType.Capsule : ButtonType.Normal)
              .fontSize(12)
              .backgroundColor(this.selectedRenderMode === option ? 0x007DFF : 0xF5F5F5)
              .onClick(() => {
                this.selectedRenderMode = option;
              })
          })
        }
      }
    }
    .padding(12)
    .backgroundColor(0xFFFFFF)
    .borderRadius(8)
    .shadow({ radius: 4, color: 0x1A000000, offsetX: 0, offsetY: 2 })

    // interpolation 控制
    Column({ space: 8 }) {
      Text('interpolation: ' + this.interpolationNames[this.interpolationList.indexOf(this.selectedInterpolation)])
          .fontSize(14)
          .fontWeight(FontWeight.Medium)

        Row({ space: 10 }) {
          ForEach(this.interpolationList, (option: ImageInterpolation, index: number) => {
            Button(this.interpolationNames[index])
              .type(this.selectedInterpolation === option ? ButtonType.Capsule : ButtonType.Normal)
              .fontSize(12)
              .backgroundColor(this.selectedInterpolation === option ? 0x007DFF : 0xF5F5F5)
              .onClick(() => {
                this.selectedInterpolation = option;
              })
          })
        }
      }
    }
    .padding(12)
    .backgroundColor(0xFFFFFF)
    .borderRadius(8)
    .shadow({ radius: 4, color: 0x1A000000, offsetX: 0, offsetY: 2 })

    // objectRepeat 控制
    Column({ space: 8 }) {
      Text('objectRepeat: ' + this.objectRepeatNames[this.objectRepeatList.indexOf(this.selectedObjectRepeat)])
          .fontSize(14)
          .fontWeight(FontWeight.Medium)

        Row({ space: 10 }) {
          ForEach(this.objectRepeatList, (option: ImageRepeat, index: number) => {
            Button(this.objectRepeatNames[index])
              .type(this.selectedObjectRepeat === option ? ButtonType.Capsule : ButtonType.Normal)
              .fontSize(12)
              .backgroundColor(this.selectedObjectRepeat === option ? 0x007DFF : 0xF5F5F5)
              .onClick(() => {
                this.selectedObjectRepeat = option;
              })
          })
        }
      }
    }
    .padding(12)
    .backgroundColor(0xFFFFFF)
    .borderRadius(8)
    .shadow({ radius: 4, color: 0x1A000000, offsetX: 0, offsetY: 2 })

    // dynamicRangeMode 控制
    Column({ space: 8 }) {
      Text('dynamicRangeMode: ' + this.dynamicRangeModeNames[this.dynamicRangeModeList.indexOf(this.selectedDynamicRangeMode)])
          .fontSize(14)
          .fontWeight(FontWeight.Medium)

        Row({ space: 10 }) {
          ForEach(this.dynamicRangeModeList, (option: DynamicRangeMode, index: number) => {
            Button(this.dynamicRangeModeNames[index])
              .type(this.selectedDynamicRangeMode === option ? ButtonType.Capsule : ButtonType.Normal)
              .fontSize(12)
              .backgroundColor(this.selectedDynamicRangeMode === option ? 0x007DFF : 0xF5F5F5)
              .onClick(() => {
                this.selectedDynamicRangeMode = option;
              })
          })
        }
      }
    }
    .padding(12)
    .backgroundColor(0xFFFFFF)
    .borderRadius(8)
    .shadow({ radius: 4, color: 0x1A000000, offsetX: 0, offsetY: 2 })

    // rotateOrientation 控制
    Column({ space: 8 }) {
      Text('rotateOrientation: ' + this.rotateOrientationNames[this.rotateOrientationList.indexOf(this.selectedRotateOrientation)])
          .fontSize(14)
          .fontWeight(FontWeight.Medium)

        Flex({ wrap: FlexWrap.Wrap }) {
          ForEach(this.rotateOrientationList, (option: ImageRotateOrientation, index: number) => {
            Button(this.rotateOrientationNames[index] + '')
              .type(this.selectedRotateOrientation === option ? ButtonType.Capsule : ButtonType.Normal)
              .fontSize(12)
              .backgroundColor(this.selectedRotateOrientation === option ? 0x007DFF : 0xF5F5F5)
              .margin({ right: 8, bottom: 8 })
              .onClick(() => {
                this.selectedRotateOrientation = option;
              })
          })
        }
      }
    }
    .padding(12)
    .backgroundColor(0xFFFFFF)
    .borderRadius(8)
    .shadow({ radius: 4, color: 0x1A000000, offsetX: 0, offsetY: 2 })

    // 布尔开关控制
    Column({ space: 12 }) {
      Text('布尔属性')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)

      Row({ space: 20 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.isAutoResize })
          .onChange((isOn: boolean) => {
            this.isAutoResize = isOn;
          })
        Text('autoResize')
          .fontSize(12)

        Toggle({ type: ToggleType.Switch, isOn: this.isSyncLoad })
          .onChange((isOn: boolean) => {
            this.isSyncLoad = isOn;
          })
        Text('syncLoad')
          .fontSize(12)
      }

      Row({ space: 20 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.isMatchTextDirection })
          .onChange((isOn: boolean) => {
            this.isMatchTextDirection = isOn;
          })
        Text('matchTextDirection')
          .fontSize(12)

        Toggle({ type: ToggleType.Switch, isOn: this.isFitOriginalSize })
          .onChange((isOn: boolean) => {
            this.isFitOriginalSize = isOn;
          })
        Text('fitOriginalSize')
          .fontSize(12)
      }

      Row({ space: 20 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.isDraggable })
          .onChange((isOn: boolean) => {
            this.isDraggable = isOn;
          })
        Text('draggable')
          .fontSize(12)
      }
    }
    .padding(12)
    .backgroundColor(0xFFFFFF)
    .borderRadius(8)
    .shadow({ radius: 4, color: 0x1A000000, offsetX: 0, offsetY: 2 })

    // 滑块控制
    Column({ space: 12 }) {
      Text('数值属性')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)

      Column({ space: 8 }) {
        Text('hdrBrightness: ' + this.hdrBrightness.toFixed(2))
          .fontSize(12)
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

      Column({ space: 8 }) {
        Text('缩放: ' + this.currentScale.toFixed(2))
          .fontSize(12)
        Slider({
          value: this.currentScale,
          min: 0.5,
          max: 2.0,
          step: 0.1
        })
          .width('100%')
          .onChange((value: number) => {
            this.currentScale = value;
          })
      }

      Column({ space: 8 }) {
        Text('旋转: ' + this.currentRotation.toFixed(0) + '°')
          .fontSize(12)
        Slider({
          value: this.currentRotation,
          min: 0,
          max: 360,
          step: 15
        })
          .width('100%')
          .onChange((value: number) => {
            this.currentRotation = value;
          })
      }

      Column({ space: 8 }) {
        Text('透明度: ' + this.currentOpacity.toFixed(2))
          .fontSize(12)
        Slider({
          value: this.currentOpacity,
          min: 0.0,
          max: 1.0,
          step: 0.1
        })
          .width('100%')
          .onChange((value: number) => {
            this.currentOpacity = value;
          })
      }
    }
    .padding(12)
    .backgroundColor(0xFFFFFF)
    .borderRadius(8)
    .shadow({ radius: 4, color: 0x1A000000, offsetX: 0, offsetY: 2 })
  }

  build() {
    Column() {
      Text('Image 完整功能演示')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Row() {
        // 左侧：图片预览
        Column({ space: 15 }) {
          Text('图片预览')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 10 })

          // 主图片
          Column({ space: 10 }) {
            Text('本地资源图片')
              .fontSize(14)
              .fontColor(0x666666)

            Image($r('app.media.img'))
              .width(300)
              .height(300)
              .border({ width: 3, color: Color.Blue, radius: 10 })
              .borderRadius(10)
              .objectFit(this.selectedImageFit)
              .renderMode(this.selectedRenderMode)
              .interpolation(this.selectedInterpolation)
              .objectRepeat(this.selectedObjectRepeat)
              .dynamicRangeMode(this.selectedDynamicRangeMode)
              .autoResize(this.isAutoResize)
              .syncLoad(this.isSyncLoad)
              .matchTextDirection(this.isMatchTextDirection)
              .fitOriginalSize(this.isFitOriginalSize)
              .draggable(this.isDraggable)
              .orientation(this.selectedRotateOrientation)
              .hdrBrightness(this.hdrBrightness)
              .alt($r('app.media.placeholder'))
              .sourceSize({ width: 300, height: 300 })
              .scale({ x: this.currentScale, y: this.currentScale })
              .rotate({ angle: this.currentRotation })
              .opacity(this.currentOpacity)
              .onComplete((event) => {
                this.loadStatus = `加载成功: ${event.width}x${event.height}`;
              })
              .onError((error) => {
                this.errorMessage = `加载失败: ${error.componentCode} - ${error.message}`;
              })

            Text(this.loadStatus)
              .fontSize(12)
              .fontColor(Color.Green)
          }
          .padding(15)
          .backgroundColor(0xF0F0F0)
          .borderRadius(10)

          // PixelMap 图片
          if (this.pixelMapImage) {
            Column({ space: 10 }) {
              Text('PixelMap 图片')
                .fontSize(14)
                .fontColor(0x666666)

              Image(this.pixelMapImage)
                .width(300)
                .height(300)
                .border({ width: 3, color: Color.Green, radius: 10 })
                .borderRadius(10)
                .objectFit(this.selectedImageFit)
                .renderMode(this.selectedRenderMode)
                .interpolation(this.selectedInterpolation)
                .scale({ x: this.currentScale, y: this.currentScale })
                .rotate({ angle: this.currentRotation })
                .opacity(this.currentOpacity)
            }
            .padding(15)
            .backgroundColor(0xF0F0F0)
            .borderRadius(10)
          }

          // 网络图片
          Column({ space: 10 }) {
            Text('网络图片')
              .fontSize(14)
              .fontColor(0x666666)

            Image('https://picsum.photos/300/300')
              .width(300)
              .height(300)
              .border({ width: 3, color: Color.Orange, radius: 10 })
              .borderRadius(10)
              .objectFit(this.selectedImageFit)
              .renderMode(this.selectedRenderMode)
              .interpolation(this.selectedInterpolation)
              .scale({ x: this.currentScale, y: this.currentScale })
              .rotate({ angle: this.currentRotation })
              .opacity(this.currentOpacity)
              .alt($r('app.media.placeholder'))
              .onComplete((event) => {
                console.info(`网络图片加载成功: ${event.width}x${event.height}`);
              })
              .onError((error) => {
                console.error(`网络图片加载失败: ${error.message}`);
              })
          }
          .padding(15)
          .backgroundColor(0xF0F0F0)
          .borderRadius(10)

          // SVG 图片
          Column({ space: 10 }) {
            Text('SVG 图片')
              .fontSize(14)
              .fontColor(0x666666)

            Image($r('app.media.svg'))
              .width(300)
              .height(300)
              .border({ width: 3, color: Color.Pink, radius: 10 })
              .borderRadius(10)
              .objectFit(this.selectedImageFit)
              .interpolation(this.selectedInterpolation)
              .scale({ x: this.currentScale, y: this.currentScale })
              .rotate({ angle: this.currentRotation })
              .opacity(this.currentOpacity)
              .fillColor(Color.Blue)
          }
          .padding(15)
          .backgroundColor(0xF0F0F0)
          .borderRadius(10)
        }
        .layoutWeight(1)
        .padding(10)

        Divider()
          .vertical(true)
          .color(0xDDDDDD)
          .strokeWidth(2)

        // 右侧：控制面板
        Scroll() {
          Column({ space: 15 }) {
            Button(this.showAdvancedOptions ? '收起高级选项' : '展开高级选项')
              .width('100%')
              .onClick(() => {
                this.showAdvancedOptions = !this.showAdvancedOptions;
              })

            this.ImageControlPanel()

            if (this.errorMessage) {
              Text(this.errorMessage)
                .fontSize(12)
                .fontColor(Color.Red)
                .padding(10)
                .backgroundColor(0xFFEBEE)
                .borderRadius(5)
                .width('100%')
            }

            // 重置按钮
            Button('重置所有设置')
              .width('100%')
              .backgroundColor(0xFF5252)
              .onClick(() => {
                this.selectedImageFit = ImageFit.Cover;
                this.selectedRenderMode = ImageRenderMode.Original;
                this.selectedInterpolation = ImageInterpolation.Low;
                this.selectedObjectRepeat = ImageRepeat.NoRepeat;
                this.selectedDynamicRangeMode = DynamicRangeMode.Standard;
                this.selectedRotateOrientation = ImageRotateOrientation.AUTO;
                this.isAutoResize = false;
                this.isSyncLoad = false;
                this.isMatchTextDirection = false;
                this.isFitOriginalSize = false;
                this.isDraggable = true;
                this.hdrBrightness = 1.0;
                this.currentScale = 1.0;
                this.currentRotation = 0;
                this.currentOpacity = 1.0;
                this.errorMessage = '';
              })
          }
          .padding(10)
        }
        .layoutWeight(1)
        .backgroundColor(0xFAFAFA)
      }
      .layoutWeight(1)
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor(0xF5F5F5)
  }
}
