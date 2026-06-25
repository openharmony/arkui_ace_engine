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
struct ImageStyleGallery {
  @State imageSrc: Resource = $r('app.media.startIcon');
  @State borderRadiusValue: number = 0;
  @State borderWidthValue: number = 0;
  @State borderColorValue: ResourceColor = Color.Black;
  @State opacityValue: number = 1.0;
  @State scaleValue: number = 1.0;
  @State rotateValue: number = 0;
  @State translateXValue: number = 0;
  @State translateYValue: number = 0;
  @State blurValue: number = 0;
  @State shadowRadiusValue: number = 0;
  @State fillColorValue: ResourceColor = Color.Transparent;
  @State renderModeValue: ImageRenderMode = ImageRenderMode.Original;
  @State interpolationValue: ImageInterpolation = ImageInterpolation.Low;
  @State objectRepeatValue: ImageRepeat = ImageRepeat.NoRepeat;
  @State imageWidth: number = 250;
  @State imageHeight: number = 180;

  private borderColors: Record<string, ResourceColor> = {
    'Black': Color.Black,
    'Red': Color.Red,
    'Blue': Color.Blue,
    'Green': Color.Green,
    'Gray': Color.Gray
  };

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('Image 样式画廊')
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
            .interpolation(this.interpolationValue)
            .renderMode(this.renderModeValue)
            .objectRepeat(this.objectRepeatValue)
            .fillColor(this.fillColorValue)
            .width(this.imageWidth)
            .height(this.imageHeight)
            .borderRadius(this.borderRadiusValue)
            .border({
              width: this.borderWidthValue,
              color: this.borderColorValue
            })
            .shadow({
              radius: this.shadowRadiusValue,
              color: Color.Grey,
              offsetX: 2,
              offsetY: 2
            })
            .opacity(this.opacityValue)
            .scale({ x: this.scaleValue, y: this.scaleValue })
            .rotate({ x: 0, y: 0, z: 1, angle: this.rotateValue })
            .translate({ x: this.translateXValue, y: this.translateYValue })
            .blur(this.blurValue)
        }
        .padding(20)
        .backgroundColor('#f5f5f5')
        .borderRadius(12)
        .width('100%')
        .alignItems(HorizontalAlign.Center)

        this.buildBorderSection()
        this.buildTransformSection()
        this.buildVisualSection()
        this.buildRenderSection()

        Button('重置所有效果')
          .onClick(() => this.resetAll())
          .width('80%')
          .backgroundColor('#4CAF50')
          .margin({ top: 10 })

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

  @Builder
  buildBorderSection() {
    Column({ space: 10 }) {
      Text('边框与圆角')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 10 }) {
        Text('圆角:')
          .fontSize(14)
          .width(50)
        Slider({
          value: this.borderRadiusValue,
          min: 0,
          max: 125,
          step: 5,
          style: SliderStyle.OutSet
        })
          .onChange((value: number) => {
            this.borderRadiusValue = value;
          })
          .layoutWeight(1)
        Text(`${this.borderRadiusValue}`)
          .fontSize(14)
          .width(30)
      }
      .width('100%')

      Row({ space: 10 }) {
        Text('边框:')
          .fontSize(14)
          .width(50)
        Slider({
          value: this.borderWidthValue,
          min: 0,
          max: 15,
          step: 1,
          style: SliderStyle.OutSet
        })
          .onChange((value: number) => {
            this.borderWidthValue = value;
          })
          .layoutWeight(1)
        Text(`${this.borderWidthValue}`)
          .fontSize(14)
          .width(30)
      }
      .width('100%')

      Row({ space: 8 }) {
        Text('颜色:')
          .fontSize(14)
          .width(50)
        ForEach(Object.keys(this.borderColors), (key: string) => {
          Button(key)
            .onClick(() => {
              this.borderColorValue = this.borderColors[key];
            })
            .fontSize(11)
            .height(28)
            .backgroundColor(this.borderColorValue === this.borderColors[key] ? '#FF9800' : '#e0e0e0')
            .fontColor(this.borderColorValue === this.borderColors[key] ? Color.White : Color.Black)
        })
      }
      .width('100%')

      Row({ space: 10 }) {
        Text('阴影:')
          .fontSize(14)
          .width(50)
        Slider({
          value: this.shadowRadiusValue,
          min: 0,
          max: 30,
          step: 2,
          style: SliderStyle.OutSet
        })
          .onChange((value: number) => {
            this.shadowRadiusValue = value;
          })
          .layoutWeight(1)
        Text(`${this.shadowRadiusValue}`)
          .fontSize(14)
          .width(30)
      }
      .width('100%')
    }
    .padding(15)
    .backgroundColor('#fff')
    .borderRadius(12)
    .width('100%')
  }

  @Builder
  buildTransformSection() {
    Column({ space: 10 }) {
      Text('变换效果')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 10 }) {
        Text('透明度:')
          .fontSize(14)
          .width(55)
        Slider({
          value: this.opacityValue,
          min: 0,
          max: 1,
          step: 0.05,
          style: SliderStyle.OutSet
        })
          .onChange((value: number) => {
            this.opacityValue = value;
          })
          .layoutWeight(1)
        Text(`${this.opacityValue.toFixed(2)}`)
          .fontSize(14)
          .width(40)
      }
      .width('100%')

      Row({ space: 10 }) {
        Text('缩放:')
          .fontSize(14)
          .width(55)
        Slider({
          value: this.scaleValue,
          min: 0.2,
          max: 3.0,
          step: 0.1,
          style: SliderStyle.OutSet
        })
          .onChange((value: number) => {
            this.scaleValue = value;
          })
          .layoutWeight(1)
        Text(`${this.scaleValue.toFixed(1)}`)
          .fontSize(14)
          .width(30)
      }
      .width('100%')

      Row({ space: 10 }) {
        Text('旋转:')
          .fontSize(14)
          .width(55)
        Slider({
          value: this.rotateValue,
          min: 0,
          max: 360,
          step: 5,
          style: SliderStyle.OutSet
        })
          .onChange((value: number) => {
            this.rotateValue = value;
          })
          .layoutWeight(1)
        Text(`${this.rotateValue}°`)
          .fontSize(14)
          .width(40)
      }
      .width('100%')

      Row({ space: 10 }) {
        Text('平移X:')
          .fontSize(14)
          .width(55)
        Slider({
          value: this.translateXValue,
          min: -100,
          max: 100,
          step: 5,
          style: SliderStyle.OutSet
        })
          .onChange((value: number) => {
            this.translateXValue = value;
          })
          .layoutWeight(1)
        Text(`${this.translateXValue}`)
          .fontSize(14)
          .width(40)
      }
      .width('100%')

      Row({ space: 10 }) {
        Text('平移Y:')
          .fontSize(14)
          .width(55)
        Slider({
          value: this.translateYValue,
          min: -100,
          max: 100,
          step: 5,
          style: SliderStyle.OutSet
        })
          .onChange((value: number) => {
            this.translateYValue = value;
          })
          .layoutWeight(1)
        Text(`${this.translateYValue}`)
          .fontSize(14)
          .width(40)
      }
      .width('100%')

      Row({ space: 10 }) {
        Text('模糊:')
          .fontSize(14)
          .width(55)
        Slider({
          value: this.blurValue,
          min: 0,
          max: 20,
          step: 0.5,
          style: SliderStyle.OutSet
        })
          .onChange((value: number) => {
            this.blurValue = value;
          })
          .layoutWeight(1)
        Text(`${this.blurValue.toFixed(1)}`)
          .fontSize(14)
          .width(30)
      }
      .width('100%')
    }
    .padding(15)
    .backgroundColor('#fff')
    .borderRadius(12)
    .width('100%')
  }

  @Builder
  buildVisualSection() {
    Column({ space: 10 }) {
      Text('视觉效果')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .width('100%')

      Row({ space: 8 }) {
        Text('填充色:')
          .fontSize(14)
          .width(55)
        Button('透明')
          .onClick(() => this.fillColorValue = Color.Transparent)
          .fontSize(11)
          .height(28)
          .backgroundColor(this.fillColorValue === Color.Transparent ? '#2196F3' : '#e0e0e0')
          .fontColor(this.fillColorValue === Color.Transparent ? Color.White : Color.Black)
        Button('红色')
          .onClick(() => this.fillColorValue = Color.Red)
          .fontSize(11)
          .height(28)
          .backgroundColor(this.fillColorValue === Color.Red ? '#2196F3' : '#e0e0e0')
          .fontColor(this.fillColorValue === Color.Red ? Color.White : Color.Black)
        Button('蓝色')
          .onClick(() => this.fillColorValue = Color.Blue)
          .fontSize(11)
          .height(28)
          .backgroundColor(this.fillColorValue === Color.Blue ? '#2196F3' : '#e0e0e0')
          .fontColor(this.fillColorValue === Color.Blue ? Color.White : Color.Black)
      }
      .width('100%')

      Row({ space: 8 }) {
        Text('渲染:')
          .fontSize(14)
          .width(55)
        Button('原图')
          .onClick(() => this.renderModeValue = ImageRenderMode.Original)
          .fontSize(11)
          .height(28)
          .backgroundColor(this.renderModeValue === ImageRenderMode.Original ? '#FF9800' : '#e0e0e0')
          .fontColor(this.renderModeValue === ImageRenderMode.Original ? Color.White : Color.Black)
        Button('模板')
          .onClick(() => this.renderModeValue = ImageRenderMode.Template)
          .fontSize(11)
          .height(28)
          .backgroundColor(this.renderModeValue === ImageRenderMode.Template ? '#FF9800' : '#e0e0e0')
          .fontColor(this.renderModeValue === ImageRenderMode.Template ? Color.White : Color.Black)
      }
      .width('100%')

      Row({ space: 8 }) {
        Text('插值:')
          .fontSize(14)
          .width(55)
        ForEach([ImageInterpolation.None, ImageInterpolation.Low, ImageInterpolation.Medium, ImageInterpolation.High],
          (item: ImageInterpolation) => {
            Button(this.getInterpolationName(item))
              .onClick(() => this.interpolationValue = item)
              .fontSize(11)
              .height(28)
              .backgroundColor(this.interpolationValue === item ? '#4CAF50' : '#e0e0e0')
              .fontColor(this.interpolationValue === item ? Color.White : Color.Black)
          })
      }
      .width('100%')

      Row({ space: 8 }) {
        Text('重复:')
          .fontSize(14)
          .width(55)
        ForEach([ImageRepeat.NoRepeat, ImageRepeat.X, ImageRepeat.Y, ImageRepeat.XY],
          (item: ImageRepeat) => {
            Button(this.getRepeatName(item))
              .onClick(() => this.objectRepeatValue = item)
              .fontSize(11)
              .height(28)
              .backgroundColor(this.objectRepeatValue === item ? '#9C27B0' : '#e0e0e0')
              .fontColor(this.objectRepeatValue === item ? Color.White : Color.Black)
          })
      }
      .width('100%')
    }
    .padding(15)
    .backgroundColor('#fff')
    .borderRadius(12)
    .width('100%')
  }

  @Builder
  buildRenderSection() {
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
          max: 380,
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
          max: 300,
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
    }
    .padding(15)
    .backgroundColor('#fff')
    .borderRadius(12)
    .width('100%')
  }

  private getInterpolationName(value: ImageInterpolation): string {
    switch (value) {
      case ImageInterpolation.None:
        return '无';
      case ImageInterpolation.Low:
        return '低';
      case ImageInterpolation.Medium:
        return '中';
      case ImageInterpolation.High:
        return '高';
      default:
        return '';
    }
  }

  private getRepeatName(value: ImageRepeat): string {
    switch (value) {
      case ImageRepeat.NoRepeat:
        return '不重复';
      case ImageRepeat.X:
        return 'X';
      case ImageRepeat.Y:
        return 'Y';
      case ImageRepeat.XY:
        return 'XY';
      default:
        return '';
    }
  }

  private resetAll(): void {
    this.borderRadiusValue = 0;
    this.borderWidthValue = 0;
    this.borderColorValue = Color.Black;
    this.opacityValue = 1.0;
    this.scaleValue = 1.0;
    this.rotateValue = 0;
    this.translateXValue = 0;
    this.translateYValue = 0;
    this.blurValue = 0;
    this.shadowRadiusValue = 0;
    this.fillColorValue = Color.Transparent;
    this.renderModeValue = ImageRenderMode.Original;
    this.interpolationValue = ImageInterpolation.Low;
    this.objectRepeatValue = ImageRepeat.NoRepeat;
    this.imageWidth = 250;
    this.imageHeight = 180;
  }
}
