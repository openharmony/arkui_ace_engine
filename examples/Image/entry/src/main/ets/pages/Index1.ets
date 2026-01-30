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
import { matrix4 } from '@kit.ArkUI';

@Entry
@Component
struct Index {
  @State imageSrc: Resource | PixelMap | string = $r('app.media.test1');
  @State currentIndex: number = 0;
  @State imageSrcList: Array<string | Resource | PixelMap> = [
    $r('app.media.test1'),
    $r('app.media.test2'),
    $r('app.media.test3'),
  ];

  // Image布局
  @State imageWidth: number = 300;
  @State imageHeight: number = 200;
  @State aspectRatioValue: number = 1.5;
  @State flexGrowValue: number = 0;
  @State flexShrinkValue: number = 1;
  @State alignSelfValue: ItemAlign = ItemAlign.Auto;

  // Image属性
  @State altSrc: Resource = $r('app.media.test3');
  @State objectFit: ImageFit = ImageFit.Cover;
  @State matrix: ImageMatrix = matrix4.identity();
  @State objectRepeat: ImageRepeat = ImageRepeat.NoRepeat;
  @State interPolation: ImageInterpolation = ImageInterpolation.None;
  @State renderMode: ImageRenderMode = ImageRenderMode.Original;
  @State autoResize: boolean = true;
  @State syncLoad: boolean = false;
  @State copyOption: CopyOptions = CopyOptions.None;
  @State fitOriginalSizeEnabled: boolean = false;
  @State fillColorValue: ResourceColor = Color.Transparent;
  @State copyOptionValue: CopyOptions = CopyOptions.None;
  @State draggableEnabled: boolean = true;
  @State syncLoadEnabled: boolean = false;

  // Image状态
  @State isLoading: boolean = false;
  @State loadError: boolean = false;
  @State loadProgress: number = 0;
  @State imageInfo: string = '';
  @State showOriginalSize: boolean = false;

  // Image样式属性
  @State borderRadiusValue: number = 0;
  @State borderWidthValue: number = 0;
  @State borderColorValue: ResourceColor = Color.Black;
  @State shadowRadiusValue: number = 0;
  @State shadowColorValue: ResourceColor = Color.Grey;
  @State shadowOffsetXValue: number = 0;
  @State shadowOffsetYValue: number = 0;
  @State opacityValue: number = 1.0;
  @State scaleValue: number = 1.0;
  @State rotateValue: number = 0;
  @State translateXValue: number = 0;
  @State translateYValue: number = 0;
  @State blurValue: number = 0;

  // Image交互
  @State enableClick: boolean = true;
  @State enableLongPress: boolean = true;
  @State enableSwipe: boolean = true;
  @State enableZoom: boolean = false;
  @State zoomScale: number = 1.0;
  @State showOverlay: boolean = false;
  @State overlayText: string = 'Image Overlay';
  @State enableAnimation: boolean = false;

  // 事件回调
  private onComplete(message: string = '操作完成'): void {
    console.log('ImageTestDemo: ' + message);
    this.imageInfo = message;
  }

  // 切换图片
  private changeImage(direction: number): void {
    this.currentIndex = (this.currentIndex + direction + this.imageSrcList.length) % this.imageSrcList.length;
    this.imageSrc = this.imageSrcList[this.currentIndex];
    this.resetEffects();
    this.onComplete('切换到图片 ' + (this.currentIndex + 1));
  }

  // 重置所有效果
  private resetEffects(): void {
    this.objectFit = ImageFit.Cover;
    this.objectRepeat = ImageRepeat.NoRepeat;
    this.interPolation = ImageInterpolation.None;
    this.borderRadiusValue = 0;
    this.borderWidthValue = 0;
    this.borderColorValue = Color.Black;
    this.shadowRadiusValue = 0;
    this.opacityValue = 1.0;
    this.scaleValue = 1.0;
    this.rotateValue = 0;
    this.translateXValue = 0;
    this.translateYValue = 0;
    this.blurValue = 0;
    this.zoomScale = 1.0;
    this.showOverlay = false;
    this.enableAnimation = false;
    this.imageWidth = 300;
    this.imageHeight = 200;
  }

  // 加载网络图片
  private loadNetworkImage(): void {
    this.isLoading = true;
    this.loadProgress = 0;
    this.loadError = false;

    // 模拟加载过程
    let interval = setInterval(() => {
      this.loadProgress += 10;
      if (this.loadProgress >= 100) {
        clearInterval(interval);
        this.isLoading = false;
        this.onComplete('网络图片加载完成');
      }
    }, 100);
  }

  // 模拟图片加载错误
  private simulateError(): void {
    this.loadError = true;
    this.imageInfo = '图片加载失败模拟';
    setTimeout(() => {
      this.loadError = false;
    }, 2000);
  }

  // 切换ObjectFit模式
  private changeObjectFit(): void {
    const fits = [
      ImageFit.Cover,
      ImageFit.Contain,
      ImageFit.Fill,
      ImageFit.None,
      ImageFit.ScaleDown
    ];
    const currentIndex = fits.indexOf(this.objectFit);
    this.objectFit = fits[(currentIndex + 1) % fits.length];
    this.onComplete('ObjectFit切换为: ' + this.getObjectFitName(this.objectFit));
  }

  private getObjectFitName(fit: ImageFit): string {
    switch (fit) {
      case ImageFit.Cover: return 'Cover';
      case ImageFit.Contain: return 'Contain';
      case ImageFit.Fill: return 'Fill';
      case ImageFit.None: return 'None';
      case ImageFit.ScaleDown: return 'ScaleDown';
      default: return 'Unknown';
    }
  }

  // 切换重复模式
  private changeObjectRepeat(): void {
    const repeats = [
      ImageRepeat.NoRepeat,
      ImageRepeat.X,
      ImageRepeat.Y,
      ImageRepeat.XY
    ];
    const currentIndex = repeats.indexOf(this.objectRepeat);
    this.objectRepeat = repeats[(currentIndex + 1) % repeats.length];
    this.onComplete('重复模式切换为: ' + this.getObjectRepeatName(this.objectRepeat));
  }

  private getObjectRepeatName(repeat: ImageRepeat): string {
    switch (repeat) {
      case ImageRepeat.NoRepeat: return 'NoRepeat';
      case ImageRepeat.X: return 'X';
      case ImageRepeat.Y: return 'Y';
      case ImageRepeat.XY: return 'XY';
      default: return 'Unknown';
    }
  }

  // 切换插值质量
  private changeInterpolation(): void {
    const interPolations = [
      ImageInterpolation.None,
      ImageInterpolation.Low,
      ImageInterpolation.Medium,
      ImageInterpolation.High
    ];
    const currentIndex = interPolations.indexOf(this.interPolation);
    this.interPolation = interPolations[(currentIndex + 1) % interPolations.length];
    this.onComplete('插值质量切换为: ' + this.getInterpolationName(this.interPolation));
  }

  private getInterpolationName(interpolation: ImageInterpolation): string {
    switch (interpolation) {
      case ImageInterpolation.None: return 'None';
      case ImageInterpolation.Low: return 'Low';
      case ImageInterpolation.Medium: return 'Medium';
      case ImageInterpolation.High: return 'High';
      default: return 'Unknown';
    }
  }

  build() {
    Scroll() {
      Column({ space: 15 }) {
        Text('ArkUI Image组件全面测试Demo')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .textAlign(TextAlign.Center)
          .width('100%')
        Divider().strokeWidth(1).color(Color.Gray).margin({ bottom: 10 })
        // 图片显示区域
        this.buildImageDisplayArea()

        // 控制面板区域
        this.buildControlPanel()

        // 属性设置区域
        this.buildPropertySettings()

        // 样式设置区域
        this.buildStyleSettings()

        // 状态信息区域
        this.buildStatusInfo()
      }
    }
  }

  @Builder
  buildImageDisplayArea() {
    Column() {
      Stack() {
        // 主图片显示
        Image(this.imageSrc)
          .alt(this.altSrc)
          .objectFit(this.objectFit)
          .imageMatrix(this.matrix)
          .objectRepeat(this.objectRepeat)
          .interpolation(this.interPolation)
          .renderMode(this.renderMode)
          .autoResize(this.autoResize)
          .fitOriginalSize(this.fitOriginalSizeEnabled)
          .fillColor(this.fillColorValue)
          .copyOption(this.copyOption)
          .draggable(this.draggableEnabled)
          .syncLoad(this.syncLoad)
          .width(this.imageWidth)
          .height(this.imageHeight)
          .aspectRatio(this.showOriginalSize ? undefined : this.aspectRatioValue)
          .borderRadius(this.borderRadiusValue)
          .border({
            width: this.borderWidthValue,
            color: this.borderColorValue
          })
          .shadow({
            radius: this.shadowRadiusValue,
            color: this.shadowColorValue,
            offsetX: this.shadowOffsetXValue,
            offsetY: this.shadowOffsetYValue
          })
          .opacity(this.opacityValue)
          .scale({ x: this.scaleValue, y: this.scaleValue })
          .rotate({ x: 0, y: 0, z: 1, angle: this.rotateValue })
          .translate({ x: this.translateXValue, y: this.translateYValue })
          .blur(this.blurValue)
          .flexGrow(this.flexGrowValue)
          .flexShrink(this.flexShrinkValue)
          .alignSelf(this.alignSelfValue)
          .overlay(this.showOverlay ? this.buildOverlay() : null)
          .onComplete(() => {
            console.log('Image加载完成');
            this.imageInfo = '图片加载完成';
          })
          .onError(() => {
            console.error('Image加载失败');
            this.imageInfo = '图片加载失败';
            this.loadError = true;
          })
          .onClick(() => {
            if (this.enableClick) {
              console.log('Image被点击');
              this.onComplete('图片被点击');
            }
          })
          .transition({
            type: this.enableAnimation ? TransitionType.All : TransitionType.Delete,
            opacity: this.opacityValue,
            translate: { x: this.translateXValue, y: this.translateYValue },
            scale: { x: this.scaleValue, y: this.scaleValue },
            rotate: { x: 0, y: 0, z: 1, angle: this.rotateValue }
          })

        // 加载状态
        if (this.isLoading) {
          this.buildLoadingIndicator()
        }

        // 错误状态
        if (this.loadError) {
          this.buildErrorIndicator()
        }
      }
      .width('100%')
      .padding(10)
      .backgroundColor('#f5f5f5')
      .borderRadius(10)

      // 图片切换控制
      Row({ space: 20 }) {
        Button('上一张')
          .onClick(() => this.changeImage(-1))
          .width(120)

        Text(`图片 ${this.currentIndex + 1}/${this.imageSrcList.length}`)
          .fontSize(16)
          .fontColor(Color.Black)

        Button('下一张')
          .onClick(() => this.changeImage(1))
          .width(120)
      }
      .margin({ top: 10 })
      .width('100%')
      .justifyContent(FlexAlign.Center)
    }
  }

  @Builder
  buildLoadingIndicator() {
    Column() {
      Progress({ value: this.loadProgress, total: 100 })
        .width(200)
        .height(20)
      Text('加载中... ' + this.loadProgress + '%')
        .fontSize(14)
        .fontColor(Color.Blue)
        .margin({ top: 5 })
    }
    .padding(20)
    .backgroundColor(Color.White)
    .borderRadius(10)
    .opacity(0.9)
  }

  @Builder
  buildErrorIndicator() {
    Column() {
      Image($r('app.media.test4'))
        .width(50)
        .height(50)
      Text('加载失败')
        .fontSize(16)
        .fontColor(Color.Red)
        .margin({ top: 5 })
    }
    .padding(20)
    .backgroundColor(Color.White)
    .borderRadius(10)
    .opacity(0.9)
  }

  @Builder
  buildOverlay() {
    Column() {
      Text(this.overlayText)
        .fontSize(16)
        .fontColor(Color.White)
        .padding(10)
        .backgroundColor('#80000000')
        .borderRadius(5)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
  }

  @Builder
  buildControlPanel() {
    Column({ space: 10 }) {
      Text('控制面板')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .width('100%')
        .textAlign(TextAlign.Start)

      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Start }) {
        Button('重置效果')
          .onClick(() => this.resetEffects())
          .backgroundColor('#4CAF50')
          .fontColor(Color.White)

        Button('加载网络图')
          .onClick(() => this.loadNetworkImage())
          .backgroundColor('#2196F3')
          .fontColor(Color.White)

        Button('模拟错误')
          .onClick(() => this.simulateError())
          .backgroundColor('#F44336')
          .fontColor(Color.White)

        Button('切换ObjectFit')
          .onClick(() => this.changeObjectFit())
          .backgroundColor('#FF9800')
          .fontColor(Color.White)

        Button('切换Repeat')
          .onClick(() => this.changeObjectRepeat())
          .backgroundColor('#9C27B0')
          .fontColor(Color.White)

        Button('切换插值质量')
          .onClick(() => this.changeInterpolation())
          .backgroundColor('#3F51B5')
          .fontColor(Color.White)

        Button(this.showOverlay ? '隐藏遮罩' : '显示遮罩')
          .onClick(() => {
            this.showOverlay = !this.showOverlay;
            this.onComplete(this.showOverlay ? '遮罩已显示' : '遮罩已隐藏');
          })
          .backgroundColor('#607D8B')
          .fontColor(Color.White)

        Button(this.enableAnimation ? '关闭动效' : '开启动效')
          .onClick(() => {
            this.enableAnimation = !this.enableAnimation;
            this.onComplete(this.enableAnimation ? '动效已开启' : '动效已关闭');
          })
          .backgroundColor('#795548')
          .fontColor(Color.White)
      }
      .width('100%')
    }
    .padding(10)
    .backgroundColor('#e8f4f8')
    .borderRadius(10)
    .width('100%')
  }

  private imageFitMap: Record<string, ImageFit> = {
    'Cover': ImageFit.Cover,
    'Contain': ImageFit.Contain,
    'Fill': ImageFit.Fill,
    'None': ImageFit.None,
    'ScaleDown': ImageFit.ScaleDown
  };
  private interpolationMap: Record<string, ImageInterpolation> = {
    'None': ImageInterpolation.None,
    'Low': ImageInterpolation.Low,
    'Medium': ImageInterpolation.Medium,
    'High': ImageInterpolation.High
  };
  private objectRepeatMap: Record<string, ImageRepeat> = {
    'NoRepeat': ImageRepeat.NoRepeat,
    'X': ImageRepeat.X,
    'Y': ImageRepeat.Y,
    'XY': ImageRepeat.XY
  };
  @Builder
  buildPropertySettings() {
    Column({ space: 10 }) {
      Text('属性设置')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .width('100%')
        .textAlign(TextAlign.Start)

      // ObjectFit选择
      Row({ space: 10 }) {
        Text('ObjectFit:')
          .fontSize(14)
          .width(80)

        ForEach(['Cover', 'Contain', 'Fill', 'None', 'ScaleDown'], (item: string) => {
          Button(item)
            .onClick(() => {
              this.objectFit = this.imageFitMap[item];
              this.onComplete('ObjectFit设置为: ' + item);
            })
            .backgroundColor(this.getObjectFitName(this.objectFit) === item ? '#2196F3' : '#e0e0e0')
            .fontColor(this.getObjectFitName(this.objectFit) === item ? Color.White : Color.Black)
            .height(30)
        })
      }
      .width('100%')

      // 插值质量选择
      Row({ space: 10 }) {
        Text('插值质量:')
          .fontSize(14)
          .width(80)
        ForEach(['None', 'Low', 'Medium', 'High'], (item: string) => {
          Button(item)
            .onClick(() => {
              this.interPolation = this.interpolationMap[item];
              this.onComplete('插值质量设置为: ' + item);
            })
            .backgroundColor(this.getInterpolationName(this.interPolation) === item ? '#4CAF50' : '#e0e0e0')
            .fontColor(this.getInterpolationName(this.interPolation) === item ? Color.White : Color.Black)
            .height(30)
        })
      }
      .width('100%')

      // Repeat方式选择
      Row({ space: 10 }) {
        Text('Repeat:')
          .fontSize(14)
          .width(80)
        ForEach(['NoRepeat', 'X', 'Y', 'XY'], (item: string) => {
          Button(item)
            .onClick(() => {
              this.objectRepeat = this.objectRepeatMap[item];
              this.onComplete('Repeat模式为: ' + item);
            })
            .backgroundColor(this.getObjectRepeatName(this.objectRepeat) === item ? '#2196F3' : '#e0e0e0')
            .fontColor(this.getObjectRepeatName(this.objectRepeat) === item ? Color.White : Color.Black)
            .height(30)
        })
      }
      .width('100%')

      // 布尔属性切换
      Row({ space: 10 }) {
        Toggle({ type: ToggleType.Checkbox, isOn: this.autoResize })
          .onChange((value: boolean) => {
            this.autoResize = value;
            this.onComplete('自动调整大小: ' + (value ? '开启' : '关闭'));
          })
        Text('自动调整大小')
          .fontSize(14)
      }
      .width('100%')

      // 尺寸设置
      Row({ space: 10 }) {
        Text('宽度:')
          .fontSize(14)
          .width(50)
        Slider({
          value: this.imageWidth,
          min: 50,
          max: 500,
          step: 10,
          style: SliderStyle.OutSet
        })
          .onChange((value: number) => {
            this.imageWidth = value;
            this.onComplete('宽度设置为: ' + value);
          })
          .width(200)
        Text(this.imageWidth.toString())
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
          min: 50,
          max: 400,
          step: 10,
          style: SliderStyle.OutSet
        })
          .onChange((value: number) => {
            this.imageHeight = value;
            this.onComplete('高度设置为: ' + value);
          })
          .width(200)
        Text(this.imageHeight.toString())
          .fontSize(14)
          .width(40)
      }
      .width('100%')
    }
    .padding(10)
    .backgroundColor('#f9f9f9')
    .borderRadius(10)
    .width('100%')
  }

  @Builder
  buildStyleSettings() {
    Column({ space: 10 }) {
      Text('样式设置')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .width('100%')
        .textAlign(TextAlign.Start)

      // 圆角设置
      Row({ space: 10 }) {
        Text('圆角:')
          .fontSize(14)
          .width(50)
        Slider({
          value: this.borderRadiusValue,
          min: 0,
          max: 100,
          step: 5,
          style: SliderStyle.OutSet
        })
          .onChange((value: number) => {
            this.borderRadiusValue = value;
            this.onComplete('圆角设置为: ' + value);
          })
          .width(200)
        Text(this.borderRadiusValue.toString())
          .fontSize(14)
          .width(40)
      }
      .width('100%')

      // 边框设置
      Row({ space: 10 }) {
        Text('边框:')
          .fontSize(14)
          .width(50)
        Slider({
          value: this.borderWidthValue,
          min: 0,
          max: 20,
          step: 1,
          style: SliderStyle.OutSet
        })
          .onChange((value: number) => {
            this.borderWidthValue = value;
            this.onComplete('边框宽度设置为: ' + value);
          })
          .width(200)
        Text(this.borderWidthValue.toString())
          .fontSize(14)
          .width(40)
      }
      .width('100%')

      // 边框颜色选择
      Row({ space: 10 }) {
        Text('边框颜色:')
          .fontSize(14)
          .width(80)
        ForEach(['Black', 'Red', 'Blue', 'Green', 'Gray'], (item: string) => {
          Button(item)
            .onClick(() => {
              this.borderColorValue = item === 'Black' ? Color.Black :
                item === 'Red' ? Color.Red :
                  item === 'Blue' ? Color.Blue :
                    item === 'Green' ? Color.Green : Color.Gray;
              this.onComplete('边框颜色设置为: ' + item);
            })
            .backgroundColor(this.getColorName(this.borderColorValue) === item ? '#FF9800' : '#e0e0e0')
            .fontColor(this.getColorName(this.borderColorValue) === item ? Color.White : Color.Black)
            .height(30)
        })
      }
      .width('100%')

      // 透明度设置
      Row({ space: 10 }) {
        Text('不透明度:')
          .fontSize(14)
          .width(50)
        Slider({
          value: this.opacityValue,
          min: 0,
          max: 1,
          step: 0.1,
          style: SliderStyle.OutSet
        })
          .onChange((value: number) => {
            this.opacityValue = value;
            this.onComplete('透明度设置为: ' + value.toFixed(1));
          })
          .width(200)
        Text(this.opacityValue.toFixed(1))
          .fontSize(14)
          .width(40)
      }
      .width('100%')

      // 缩放设置
      Row({ space: 10 }) {
        Text('缩放:')
          .fontSize(14)
          .width(50)
        Slider({
          value: this.scaleValue,
          min: 0.1,
          max: 3,
          step: 0.1,
          style: SliderStyle.OutSet
        })
          .onChange((value: number) => {
            this.scaleValue = value;
            this.onComplete('缩放设置为: ' + value.toFixed(1));
          })
          .width(200)
        Text(this.scaleValue.toFixed(1))
          .fontSize(14)
          .width(40)
      }
      .width('100%')

      // 旋转设置
      Row({ space: 10 }) {
        Text('旋转:')
          .fontSize(14)
          .width(50)
        Slider({
          value: this.rotateValue,
          min: 0,
          max: 360,
          step: 10,
          style: SliderStyle.OutSet
        })
          .onChange((value: number) => {
            this.rotateValue = value;
            this.onComplete('旋转角度设置为: ' + value + '°');
          })
          .width(200)
        Text(this.rotateValue + '°')
          .fontSize(14)
          .width(40)
      }
      .width('100%')

      // 模糊设置
      Row({ space: 10 }) {
        Text('模糊:')
          .fontSize(14)
          .width(50)
        Slider({
          value: this.blurValue,
          min: 0,
          max: 20,
          step: 0.5,
          style: SliderStyle.OutSet
        })
          .onChange((value: number) => {
            this.blurValue = value;
            this.onComplete('模糊度设置为: ' + value.toFixed(1));
          })
          .width(200)
        Text(this.blurValue.toFixed(1))
          .fontSize(14)
          .width(40)
      }
      .width('100%')
    }
    .padding(10)
    .backgroundColor('#f0f8ff')
    .borderRadius(10)
    .width('100%')
  }

  // 获取颜色名称
  private getColorName(color: ResourceColor): string {
    if (color === Color.Black) {
      return 'Black';
    }
    if (color === Color.Red) {
      return 'Red';
    }
    if (color === Color.Blue) {
      return 'Blue';
    }
    if (color === Color.Green) {
      return 'Green';
    }
    if (color === Color.Gray) {
      return 'Gray';
    }
    return 'Custom';
  }

  @Builder
  buildStatusInfo() {
    Column({ space: 10 }) {
      Text('状态信息')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Blue)
        .width('100%')
        .textAlign(TextAlign.Start)

      Row({ space: 10 }) {
        Text('当前ObjectFit:')
          .fontSize(14)
          .fontColor(Color.Gray)
        Text(this.getObjectFitName(this.objectFit))
          .fontSize(14)
          .fontColor(Color.Black)
          .fontWeight(FontWeight.Bold)
      }
      .width('100%')

      Row({ space: 10 }) {
        Text('当前Repeat:')
          .fontSize(14)
          .fontColor(Color.Gray)
        Text(this.getObjectRepeatName(this.objectRepeat))
          .fontSize(14)
          .fontColor(Color.Black)
          .fontWeight(FontWeight.Bold)
      }
      .width('100%')

      Row({ space: 10 }) {
        Text('插值质量:')
          .fontSize(14)
          .fontColor(Color.Gray)
        Text(this.getInterpolationName(this.interPolation))
          .fontSize(14)
          .fontColor(Color.Black)
          .fontWeight(FontWeight.Bold)
      }
      .width('100%')

      Row({ space: 10 }) {
        Text('图片尺寸:')
          .fontSize(14)
          .fontColor(Color.Gray)
        Text(`${this.imageWidth} × ${this.imageHeight}`)
          .fontSize(14)
          .fontColor(Color.Black)
          .fontWeight(FontWeight.Bold)
      }
      .width('100%')

      Row({ space: 10 }) {
        Text('圆角半径:')
          .fontSize(14)
          .fontColor(Color.Gray)
        Text(this.borderRadiusValue.toString())
          .fontSize(14)
          .fontColor(Color.Black)
          .fontWeight(FontWeight.Bold)
      }
      .width('100%')

      Row({ space: 10 }) {
        Text('边框宽度:')
          .fontSize(14)
          .fontColor(Color.Gray)
        Text(this.borderWidthValue.toString())
          .fontSize(14)
          .fontColor(Color.Black)
          .fontWeight(FontWeight.Bold)
      }
      .width('100%')

      Row({ space: 10 }) {
        Text('加载状态:')
          .fontSize(14)
          .fontColor(Color.Gray)
        Text(this.isLoading ? '加载中...' : this.loadError ? '加载失败' : '加载完成')
          .fontSize(14)
          .fontColor(this.isLoading ? Color.Blue : this.loadError ? Color.Red : Color.Green)
          .fontWeight(FontWeight.Bold)
      }
      .width('100%')

      if (this.imageInfo) {
        Row({ space: 10 }) {
          Text('最新消息:')
            .fontSize(14)
            .fontColor(Color.Gray)
          Text(this.imageInfo)
            .fontSize(14)
            .fontColor(Color.Black)
        }
        .width('100%')
      }
    }
    .padding(10)
    .backgroundColor('#f5f5f5')
    .borderRadius(10)
    .width('100%')
  }
}