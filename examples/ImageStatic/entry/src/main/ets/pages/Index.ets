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
/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http:
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
'use static'

import { memo, __memo_context_type, __memo_id_type } from '@ohos.arkui.stateManagement'
import {
  Text,
  Stack,
  TextAttribute,
  PatternLock,
  Column,
  TextPicker,
  Resource,
  Gauge,
  Badge,
  BadgeParamWithString,
  Array,
  Component,
  CapsuleStyleOptions,
  ProgressType,
  Span,
  ImageOnCompleteCallback,
  ImageCompleteEvent,
  ImageSpan,
  TextClock,
  Button,
  CalendarPicker,
  ImageRotateOrientation,
  DynamicRangeMode,
  DrawableDescriptor,
  DataPanel,
  RepeatMode,
  TextTimerAttribute,
  TextTimerController,
  FontWeight,
  FontStyle,
  TextAlign,
  ColorFilter,
  NodeContainer,
  Scroll,
  PixelMap,
  AnimationStatus,
  ColorContent,
  Color,
  ButtonAttribute,
  ImageContent,
  GradientDirection,
  ImageFit,
  QRCodeAttribute,
  Row,
  LinearGradientOptions,
  QRCode,
  LoadingProgress,
  ImageAttribute,
  LoadingProgressAttribute,
  ClickEvent,
  AttributeModifier,
  TextTimer,
  CommonAttribute,
  ProgressAttribute,
  Progress,
  ImageInterpolation,
  UIContext,
  Image,
  ImageMatrix,
  QRCode,
  QRCodeAttribute,
  ImageErrorCallback,
  ImageError,
  FrameNode,
  SizeOptions,
  $r,
  ImageAnimatorAttribute,
  ImageAnimator,
  Entry
} from '@ohos.arkui.component'
import {
  AttributeUpdater,
  CommonModifier,
  ButtonModifier,
  TextModifier,
  ImageModifier,
  ProgressModifier,
  DataPanelModifier
} from '@ohos.arkui.modifier'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'
import common2D from '@ohos.graphics.common2D'
import drawing from '@ohos.graphics.drawing'
import { NodeController, LengthMetrics, LengthUnit, typeNode } from '@ohos.arkui.node'
import image from '@ohos.multimedia.image'
import { matrix4, ColorMetrics } from '@kit.ArkUI';
import {
  DrawableDescriptor,
  LayeredDrawableDescriptor,
  PixelMapDrawableDescriptor,
  AnimatedDrawableDescriptor,
  AnimationOptions
} from '@ohos.arkui.drawableDescriptor'

class MyQRCodeNodeController extends NodeController {
  public uiContext: UIContext | null = null;
  public rootNode: FrameNode | null = null;
  public node01: FrameNode | null = null;

  makeNode(uiContext: UIContext): FrameNode | null {
    this.uiContext = uiContext;
    this.rootNode = new FrameNode(uiContext);

    let node = typeNode.createQRCodeNode(uiContext);
    node.initialize('hello this is a qrcode frame node')
      .color(Color.Black)
      .backgroundColor(Color.Gray)
      .contentOpacity(-10)
      .width(200)
      .height(200)
      .size({ width: 200, height: 50 } as SizeOptions);
    this!.rootNode!.appendChild(node);
    return this.rootNode;
  }
}

class TestQRCodeAttributeModifier implements AttributeModifier<QRCodeAttribute> {
  applyNormalAttribute(instance: QRCodeAttribute): void {
    hilog.info(0x0000, 'testTag', 'wjh applyNormalAttribute 1');
    instance.backgroundColor('#ff1f2d56')
    instance.size({ width: 100, height: 100 })
    instance.zIndex(3)
    instance.color(Color.Red)
    instance.contentOpacity(-10)
    instance.onClick((e: ClickEvent) => {
      hilog.info(0x0000, 'testTag', 'wjh onClick 1');
    })
  }
}

class TestImageAnimatorAttributeModifier implements AttributeModifier<ImageAnimatorAttribute> {
  applyNormalAttribute(instance: ImageAnimatorAttribute): void {
    hilog.info(0x0000, 'testTag', 'wjh applyNormalAttribute 1');
    instance.backgroundColor('#ff1f2d56')
    instance.size({ width: 100, height: 100 })
    instance.zIndex(3)
    instance.images([{
      src: $r('app.media.200both1'),
      width: 150,
      height: 150,
      top: 20,
      left: 20,
    }])
    instance.onClick((e: ClickEvent) => {
      hilog.info(0x0000, 'testTag', 'wjh onClick 1');
    })
  }
}

class TestImageAttributeModifier implements AttributeModifier<ImageAttribute> {
  applyNormalAttribute(instance: ImageAttribute): void {
    hilog.info(0x0000, 'testTag', 'wjh applyNormalAttribute 1');
    instance.backgroundColor('#ff1f2d56')
    instance.size({ width: 100, height: 100 })
    instance.zIndex(3)

    instance.objectFit(ImageFit.Contain)
      .dynamicRangeMode(DynamicRangeMode.HIGH)
      .resizable({
        slice: {
          top: 10,
          left: 10,
          right: 10,
          bottom: 10
        }
      })
    instance.onClick((e: ClickEvent) => {
      hilog.info(0x0000, 'testTag', 'wjh onClick 1');
    })
  }

  applyPressedAttribute(instance: ImageAttribute): void {
    hilog.info(0x0000, 'testTag', 'wjh applyPressedAttribute');
    instance.backgroundColor('#ffff00f2')
  }
}

class TestImageAttributeUpdater extends AttributeUpdater<ImageAttribute> {
  applyNormalAttribute(instance: ImageAttribute): void {
    hilog.info(0x0000, 'testTag', 'wjh applyNormalAttribute');
    instance.backgroundColor('#ff00e1ff')
      .dynamicRangeMode(DynamicRangeMode.HIGH)
      .resizable({
        slice: {
          top: 20,
          left: 10,
          right: 30,
          bottom: 40
        }
      })
    instance.updateConstructorParams($r('app.media.2'))
  }

   initializeModifier(instance: ButtonAttribute): void {
     hilog.info(0x0000, 'testTag', 'wjh initializeModifier');
     instance.backgroundColor('#ff00ff00')
   }
  applyPressedAttribute(instance: ButtonAttribute): void {
    hilog.info(0x0000, 'testTag', 'wjh applyPressedAttribute');
    instance.backgroundColor('#ffff00f2')
  }
}

class MyLoadingProgressModifier implements AttributeModifier<LoadingProgressAttribute> {
  applyNormalAttribute(instance: LoadingProgressAttribute): void {
    instance.size({ width: 100, height: 100 })
    instance.backgroundColor('#ff2f7739')
    instance.color(Color.Red)
    instance.enableLoading(false)
    hilog.info(1, 'wjh ', 'wjh test  applyNormalAttribute');
  }
}

class MyProgressModifier implements AttributeModifier<ProgressAttribute> {
  applyNormalAttribute(instance: ProgressAttribute): void {
    instance.size({ width: 100, height: 100 })
    instance.color(Color.Red)
    instance.backgroundColor('#ff2f7739')
    hilog.info(1, 'wjh ', 'wjh test  applyNormalAttribute');
  }
}

class MyLoadingProgressNodeController extends NodeController {
  public uiContext: UIContext | null = null;
  public rootNode: FrameNode | null = null;

  makeNode(uiContext: UIContext): FrameNode | null {
    this.uiContext = uiContext;
    this.rootNode = new FrameNode(uiContext);
    let node = typeNode.createLoadingProgressNode(uiContext);
    node.initialize()
      .width(100)
      .height(100)
      .color(Color.Red)
      .enableLoading(true)
    this!.rootNode!.appendChild(node);
    return this.rootNode;
  }
}

class MyImageNodeController extends NodeController {
  public uiContext: UIContext | null = null;
  public rootNode: FrameNode | null = null;

  makeNode(uiContext: UIContext): FrameNode | null {
    this.uiContext = uiContext;
    this.rootNode = new FrameNode(uiContext);
    let node = typeNode.createImageNode(uiContext);
    node.initialize('xxxx')
      .width(100)
      .height(100)
    .syncLoad(true)
    this!.rootNode!.appendChild(node);
    return this.rootNode;
  }
}

class TextTimerModifier1 implements AttributeModifier<TextTimerAttribute> {
  applyNormalAttribute(instance: TextTimerAttribute): void {
    instance
      .fontSize(20)
      .fontColor(Color.Pink)
      .format('mm:ss.SS')
      .fontWeight(FontWeight.Normal)
      .fontFamily("cursive")
      .fontStyle(FontStyle.Italic)
  }
}

@Entry
@Component
struct MyStateSample {
  @State stateVar: string = "state var";
  message: string = "var";
  @State widthTest: number = 50;
  @State isDisabled: boolean = false;
  @State testWidth: number = 200;
  testImageAttributeModifier: TestImageAttributeModifier = new TestImageAttributeModifier();
  testImageAnimatorAttributeModifier: TestImageAnimatorAttributeModifier = new TestImageAnimatorAttributeModifier();
  testQRCodeAttributeModifier: TestQRCodeAttributeModifier = new TestQRCodeAttributeModifier();
  proMod: MyProgressModifier = new MyProgressModifier()
  loadMod: MyLoadingProgressModifier = new MyLoadingProgressModifier()

  changeValue() {
    this.stateVar += "~"
  }

   public drawingColorFilterFirst: ColorFilter =
     new ColorFilter([1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0]);
  @State drawingColorFilterThird: drawing.ColorFilter | undefined = drawing.ColorFilter.createBlendModeColorFilter({
    alpha: 255,
    red: 255,
    green: 0,
    blue: 0
  }, drawing.BlendMode.SRC_IN);
  @State testImageAttributeUpdater: TestImageAttributeUpdater = new TestImageAttributeUpdater()

  createPixelMap(path: string | undefined): PixelMap | undefined {
    if (path == undefined) {
      return undefined
    }
    console.log('hello createPixelMap  path:' + path);
    let imageSourceApi: image.ImageSource | undefined = image.createImageSource(path);
    if (imageSourceApi == undefined) {
      console.log('hello createPixelMap  return undefined');
      return undefined
    }
    let pixelMap = imageSourceApi.createPixelMapSync()
    if (pixelMap) {
      console.log('hello createPixelMap pixelMap');
    } else {
      console.log('hello createPixelMap pixelMap is undefined');
    }
    return pixelMap;
  }

  getContextFilesPath(): string {
    let context = this.getUIContext().getHostContext()
    let filesDir: string | undefined = context?.filesDir
    if (filesDir) {
      return 'file:' + filesDir + '/';
    }
    return '';
  }

  resManager = this.getUIContext()?.getHostContext()?.resourceManager!
  @State pixelMap: PixelMap | undefined = undefined;
  @State res: Resource | ImageContent = $r('app.media.200both6');
  @State state: AnimationStatus | undefined = AnimationStatus.Initial;
  @State imageAnimatorFlag: boolean = false;
  @State fillColor: ColorContent | Color | undefined = Color.Blue;
  matrix: ImageMatrix = matrix4.identity().scale({ x: 0.2 });

  @State imageAnimatorFinishCallBack: VoidCallBack = ()=>{};
  aboutToAppear(): void {
     (this.resManager.getDrawableDescriptor($r('app.media.startIcon').id)) as DrawableDescriptor;
    let uiContext = this.getUIContext();
    let resManager = this.getUIContext().getHostContext()?.resourceManager;
    this.drawable = resManager?.getDrawableDescriptor($r('app.media.layered_image').id) as DrawableDescriptor;
    for (let index = 0; index < 100; index++) {
      let loadingProgress = typeNode.createLoadingProgressNode(uiContext);
      loadingProgress.initialize()
        .color(Color.Blue)
        .width(100)
        .height(50)
    }
    ColorMetrics.resourceColor(Color.Red)
  }
  private async getPixmapFromMedia(resource: Resource) : Promise<PixelMap | undefined> {
    let resourceManager = UIContext.getFocusedUIContext()!.getHostContext()?.resourceManager;
    if (resourceManager == undefined) {
      return undefined;
    }
    let unit8Array = await resourceManager.getMediaContent(resource.id);
    if (unit8Array == undefined) {
      return undefined;
    }
    let imageSource = image.createImageSource(unit8Array.buffer.slice(0, unit8Array.buffer.byteLength));
    if (imageSource == undefined) {
      return undefined;
    }
    let createPixelMap: image.PixelMap | undefined = await imageSource.createPixelMap({
      desiredPixelFormat: image.PixelMapFormat.RGBA_8888
    });
    await imageSource.release();
    return createPixelMap;
  }
  filter: ColorFilter = new ColorFilter([1, 1, 0, 0, 0,
    0, 1, 0, 0, 0,
    0, 0, 1, 0, 0,
    0, 0, 0, 1, 0]);
  private drawingLatticeFirst: drawing.Lattice =
    drawing.Lattice.createImageLattice([1, 50, 200], [1, 50, 200], 3, 3);
  @State drawable1: DrawableDescriptor = new PixelMapDrawableDescriptor();
  @State pixmap: DrawableDescriptor = new PixelMapDrawableDescriptor();
  @State drawable: DrawableDescriptor = new PixelMapDrawableDescriptor();
  @State animatedDrawableDescriptor: AnimatedDrawableDescriptor | DrawableDescriptor = new PixelMapDrawableDescriptor()
  errorCallback: ImageErrorCallback | undefined = (error: ImageError) => {
    console.log('hello ImageErrorCallback error1' + error.error + ' a' + error.componentWidth + ' ' +
    error.componentHeight + ' ' + error.message);
    this.stateVar += 'onError';
  };
  completeCallBack: ImageOnCompleteCallback | undefined = (loadEvent?: ImageCompleteEvent) => {

  };
  testImageModifier9: ImageModifier = new ImageModifier()
    .width(200)
    .height(200)
    .dynamicRangeMode(DynamicRangeMode.HIGH)
    .dynamicRangeMode(undefined)
    .resizable({
      slice: {
        left: `10px`,
        right: `10px`,
        top: `10px`,
        bottom: `10px`
      }
    })
  @State textTimerModifier: TextTimerModifier1 = new TextTimerModifier1()
  textTimerController: TextTimerController = new TextTimerController()
  testDataPanelModifier4: DataPanelModifier = new DataPanelModifier()
    .width(200)
    .height(200)
    .strokeWidth(15)
    .strokeWidth(undefined)
  .strokeWidth(-5)
  testProgressModifier: ProgressModifier = new ProgressModifier()
    .width(200)
    .height(20)

    .value(0)
    .value(-10)
    .value(undefined)
    .color($r('app.color.green'))
    .color(Color.Yellow)
    .color(undefined)

    .style({
      borderColor: $r('app.color.green'),
      borderWidth: $r('app.string.borderWidth'),
      content:"进度30%",
      font:{size:$r('app.string.fontsize'), weight:FontWeight.Bold, style:FontStyle.Italic},
      fontColor:$r('app.color.green'),
      borderColor:Color.Yellow,
      showDefaultPercentage: true,
      fontColor: "#FFFF0000"
      enableScanEffect: true,
      content: '80'
      borderRadius: LengthMetrics.vp(1)
    } as CapsuleStyleOptions)
    .value(80)
  private fruits: string[] = ['apple1', 'orange2', 'peach3', 'grape4'];

  build() {
    Scroll() {
      Column(undefined) {
        NodeContainer(new MyImageNodeController()).margin(5)
        NodeContainer(new MyQRCodeNodeController()).margin(5)
        Image(this.drawable)
          .interpolation(ImageInterpolation.High)
          .width(100)
          .height(100)
          .fillColor(Color.Green)
        Image($r('app.media.2'))
          .interpolation(ImageInterpolation.Medium)
          .width(10)
          .height(10)
        Image($r('app.media.2'))
          .interpolation(ImageInterpolation.Low)
          .width(10)
          .height(10)
        Image($r('app.media.2'))
          .interpolation(ImageInterpolation.None)
          .width(10)
          .height(10)
        Badge({value: '123', style: {}} as BadgeParamWithString) {
          Image($r('app.media.onfinish'))
            .borderWidth(1)
            .width(50)
            .height(50)
            .onFinish(()=>{
              this.stateVar += 'onFinish';
            })
        }

        NodeContainer(new MyLoadingProgressNodeController()).margin(5)
        TextTimer({ isCountDown: true, count: 30000, controller: this.textTimerController })
          .key('TextTimerKey1')
          .attributeModifier(this.textTimerModifier)
          .onTimer((utc: long, elapsedTime: long) => {
            console.info('textTimer notCountDown utc is：' + utc + ', elapsedTime: ' + elapsedTime)
          })
        TextPicker({ range: this.fruits, selected: 0 }).canLoop(undefined).width(100).height(100)
          .gradientHeight('110vp')
        Gauge({ value: 40 })
          .colors([[Color.White, 1], [Color.Black, 1]]).width(50).height(50)
        PatternLock().circleRadius(0)
          .width(100).height(100)
        Image($r('app.media.2'))
        .alt(this.pixelMap as PixelMap)
          .borderWidth(1)
          .width(50)
          .blur(5)
          .backdropBlur(5)
          .height(50)
          .onComplete(this.completeCallBack)
          .attributeModifier(this.testImageModifier9)
        Image($r('app.media.2'))
        .alt(this.pixelMap as PixelMap)
          .borderWidth(1)
          .width(50)
          .height(50).attributeModifier(this.testImageModifier9)
        CalendarPicker()
          .textStyle({
            font: {
              size: 20
            }
          })
        TextClock()
          .fontSize(20)
        Progress({ value: 50, type: ProgressType.Capsule })
          .attributeModifier(this.testProgressModifier)
        DataPanel({ values: [1, 2, 3, 4, 5, 6, 7, 8] })
          .attributeModifier(this.testDataPanelModifier4)

        TextTimer({ isCountDown: true, count: 30000, controller: this.textTimerController })
          .fontColor(Color.Pink)
        Image('xx')
          .width(100)
          .height(100)
          .onError(this.errorCallback)

        Text(this.stateVar)
          .linearGradient({
            angle: 90,
            direction: GradientDirection.Left,
            colors: [[0xAEE1E1, 0.0], [0xD3E0DC, 0.3], [0xFCD1D1, 1.0]],
            repeating: false
          } as LinearGradientOptions)
        Text('This is gradient color.').textAlign(TextAlign.Center).height(50).width(200)
          .borderImage({
            source: {
              angle: 90,
              direction: GradientDirection.Left,
              colors: [[Color.Pink, 0.0], [Color.Pink, 0.3], [Color.Pink, 1.0]],
              repeating: false
            },
            slice: {
              top: 10,
              bottom: 10,
              left: 10,
              right: 10
            },
            width: {
              top: "10px",
              bottom: "10px",
              left: "10px",
              right: "10px"
            },
            repeat: RepeatMode.Stretch,
            fill: false
          })
        Button('drawableDescriptor')
          .onClick((e: ClickEvent) => {
            for (let i: number = 0.0; i < 5.0; i++) {
              console.log('hello drawableDescriptor' + i);
              this.pixmap = (this.resManager.getDrawableDescriptor($r('app.media.startIcon').id)) as DrawableDescriptor;
            }
          })
        Image($r('app.media.1'))
          .width(100)
          .height(100).dynamicRangeMode(undefined)
        Image($r('app.media.1'))
          .width(100)
          .height(100)
        Text() {
          Span('xxx')
          ImageSpan($r('app.media.1'))
            .width(100)
            .height(100).colorFilter(this.drawingColorFilterThird)
        }

        Image($r('app.media.1'))
          .width(100)
          .height(100).colorFilter(this.drawingColorFilterThird)
        Image($r('app.media.1'))
          .width(100)
          .height(100) .colorFilter(this.filter)

        Image($r('app.media.1'))
          .width(100)
          .height(100)
          .dynamicRangeMode(DynamicRangeMode.HIGH)
          .resizable({
            slice: {
              top: 20,
              left: 10,
              right: 30,
              bottom: 40
            }
          })
          .orientation(ImageRotateOrientation.RIGHT)
          .colorFilter(this.drawingColorFilterThird)
          .borderWidth(1)
        Image($r('app.media.1'))
          .width(100)
          .height(100)
          .resizable({
            slice: {
              top: 20,
              left: 10,
              right: 30,
              bottom: 40
            },
            lattice: this.drawingLatticeFirst
          })
        Text('Text11')
          .height(100)
          .width(100)
          .borderImage({
            source: {
              angle: 90,
              direction: GradientDirection.Left,
              colors: [[0xAEE1E1, 0.0], [0xD3E0DC, 0.3], [0xFCD1D1, 1.0]]
            },
            slice: 10,
            width: 1
          })

        if (this.pixelMap) {
          ImageAnimator()
            .images([{
              src: this.pixelMap as PixelMap,
              width: 150,
              height: 150,
              top: 20,
              left: 20,
            }, {
              src: $r('app.media.200both2'),
              width: 150,
              height: 150,
              top: 20,
              left: 20,
            }, {
              src: $r('app.media.200both1'),
              width: 150,
              height: 150,
              top: 20,
              left: 20,
            }])
            .width(100)
            .height(100)
            .state(this.state)
            .iterations(2)
            .onStart(this.imageAnimatorFlag ? () => {
              console.log('hello onStart true imageAnimatorFlag:' + this.imageAnimatorFlag);
            } : undefined)
            .onPause(this.imageAnimatorFlag ? () => {
              console.log('hello onPause true imageAnimatorFlag:' + this.imageAnimatorFlag);
            } : undefined)
            .onRepeat(this.imageAnimatorFlag ? () => {
              console.log('hello onRepeat true imageAnimatorFlag:' + this.imageAnimatorFlag);
            } : undefined)
            .onCancel(this.imageAnimatorFlag ? () => {
              console.log('hello onCancel true imageAnimatorFlag:' + this.imageAnimatorFlag);
            } : undefined)
            .onFinish(this.imageAnimatorFlag ? () => {
              console.log('hello onFinish true imageAnimatorFlag:' + this.imageAnimatorFlag);
            } : undefined)
          ImageAnimator()
            .images([{
              src: this.pixelMap as PixelMap,
              width: 150,
              height: 150,
              top: 20,
              left: 20,
            }, {
              src: $r('app.media.200both2'),
              width: 150,
              height: 150,
              top: 20,
              left: 20,
            }, {
              src: $r('app.media.200both1'),
              width: 150,
              height: 150,
              top: 20,
              left: 20,
            }])
            .width(100)
            .height(100)
            .state(this.state)
            .iterations(2)
            .onStart(this.imageAnimatorFlag ? () => {
              console.log('hello onStart true imageAnimatorFlag:' + this.imageAnimatorFlag);
            } : () => {
              console.log('hello onStart false imageAnimatorFlag:' + this.imageAnimatorFlag);
            })
            .onPause(this.imageAnimatorFlag ? () => {
              console.log('hello onPause true imageAnimatorFlag:' + this.imageAnimatorFlag);
            } : () => {
              console.log('hello onPause false imageAnimatorFlag:' + this.imageAnimatorFlag);
            })
            .onRepeat(this.imageAnimatorFlag ? () => {
              console.log('hello onRepeat true imageAnimatorFlag:' + this.imageAnimatorFlag);
            } : () => {
              console.log('hello onRepeat false imageAnimatorFlag:' + this.imageAnimatorFlag);
            })
            .onCancel(this.imageAnimatorFlag ? () => {
              console.log('hello onCancel true imageAnimatorFlag:' + this.imageAnimatorFlag);
            } : () => {
              console.log('hello onCancel false imageAnimatorFlag:' + this.imageAnimatorFlag);
            })
            .onFinish(this.imageAnimatorFlag ? () => {
              console.log('hello onFinish true imageAnimatorFlag:' + this.imageAnimatorFlag);
              this.state = AnimationStatus.Initial
            } : () => {
              console.log('hello onFinish false imageAnimatorFlag:' + this.imageAnimatorFlag);
              this.state = AnimationStatus.Initial
            })
          Row() {
            Button('imageAnimatorFlag').onClick((e: ClickEvent) => {
              this.imageAnimatorFlag = !this.imageAnimatorFlag;
              console.log('hello change imageAnimatorFlag: ' + this.imageAnimatorFlag);
              this.state = AnimationStatus.Initial;
            })
            Button('start').onClick((e: ClickEvent) => {
              this.imageAnimatorFlag = !this.imageAnimatorFlag;
              this.state = AnimationStatus.Running;
            })
            Button('pause').onClick((e: ClickEvent) => {
              this.imageAnimatorFlag = !this.imageAnimatorFlag;
              this.state = AnimationStatus.Paused;
            })
          }

          .attributeModifier(this.testImageAnimatorAttributeModifier)
        }
        Row() {
          Button('fillColor ColorContent.ORIGIN').onClick((e: ClickEvent) => {
            this.imageAnimatorFlag = !this.imageAnimatorFlag;
            this.fillColor = ColorContent.ORIGIN;
          })
          Button('fillColor undefined').onClick((e: ClickEvent) => {
            this.imageAnimatorFlag = !this.imageAnimatorFlag;
            this.fillColor = undefined;
          })
        }

        Image($r('app.media.2'))
          .width(100)
          .height(100)
          .fillColor(this.fillColor)
          .fillColor(ColorMetrics.resourceColor(Color.Red))
          .borderWidth(1)
          .objectFit(ImageFit.MATRIX)
          .imageMatrix(this.matrix)
        Image($r('app.media.2'))
          .width(100)
          .height(100)
          .fillColor(this.fillColor)
          .fillColor(ColorMetrics.resourceColor(Color.Red))
          .borderWidth(1)
          .objectFit(ImageFit.MATRIX)
          .imageMatrix(this.matrix)
          .attributeModifier(this.testImageAttributeUpdater)
          .orientation(ImageRotateOrientation.RIGHT)
          .attributeModifier(this.testImageAttributeModifier)
        if (this.pixelMap != undefined) {
          Text() {
            Span('xxx')
            ImageSpan(this.pixelMap as PixelMap)
              .width(100)
              .height(100).colorFilter(this.drawingColorFilterThird)
            ImageSpan('')
              .width(100)
              .height(100)
              .alt(this.pixelMap)
          }

          Image(this.pixelMap)
            .width(100)
            .height(100)
            .fillColor(Color.Red)
            .borderWidth(1)
          .attributeModifier(this.testImageAttributeModifier)
          Image('xxx')
            .alt(this.pixelMap)
            .width(100)
            .height(100)
            .fillColor(Color.Red)
            .borderWidth(1)
          Image(this.drawable1)
            .width(100)
            .height(100)
            .fillColor(Color.Red)
            .borderWidth(1)
          Image(this.drawable)
            .width(100)
            .height(100)
            .fillColor(Color.Red)
            .borderWidth(1)
          Image(this.animatedDrawableDescriptor)
            .width(100)
            .height(100)
            .fillColor(Color.Red)
            .borderWidth(1)
        }
        Image($r('app.media.svg5'))
          .width(100)
          .height(100)
          .fillColor(ColorContent.ORIGIN)
          .borderWidth(1)
          .attributeModifier(this.testImageAttributeUpdater)
        Button("change text init params").onClick((e: ClickEvent) => {
          this.testImageAttributeUpdater.updateConstructorParams($r('app.media.200both4'));
          this.widthTest++;
          this.res = ImageContent.EMPTY;
          let filesPath = this.getContextFilesPath();
          console.log('hello filesPath:' + filesPath);
          if (filesPath != '') {
            let path = filesPath + '200both1.png';
            this.pixelMap = this.createPixelMap(path);
            pixelMaps.push();
            this.drawable1 = new PixelMapDrawableDescriptor(this.pixelMap as PixelMap);

            let pixelMaps: Array<image.PixelMap> =
              [this.pixelMap as PixelMap, this.createPixelMap(filesPath + '200both1.png') as PixelMap,
                this.createPixelMap(filesPath + '200both2.jpg') as PixelMap,
                this.createPixelMap(filesPath + '200both6.jpg') as PixelMap];
            let options: AnimationOptions = { duration: 1000, iterations: -1 };
            this.animatedDrawableDescriptor = new AnimatedDrawableDescriptor(pixelMaps, options);
          }

          let resManager = this.getUIContext().getHostContext()?.resourceManager;
          this.drawable = resManager?.getDrawableDescriptor($r('app.media.layered_image').id) as DrawableDescriptor;
        })
        Button("change text init params").onClick((e: ClickEvent) => {
          let filesPath = this.getContextFilesPath();
          console.log('hello filesPath:' + filesPath);
          if (filesPath != '') {
            let path = filesPath + '200both2.jpg';
            this.pixelMap = this.createPixelMap(path);
          }
        })
      }
    }
  }
}
