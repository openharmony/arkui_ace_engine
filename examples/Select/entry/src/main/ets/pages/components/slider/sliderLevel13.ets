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

import { FrameNode, NodeController, SliderModifier, ThemeControl, typeNode } from '@kit.ArkUI';

ThemeControl.setDefaultTheme(null);

@Builder
export function SliderLevel13Builder(name: string, param: Object) {
  Slider_Level1_3()
}

class MyModifier extends SliderModifier {
  // 设置不同样式slider
  public sliderStyle: Array<obj> = [
    {
      stepSize: '1',
      showSteps: true
    },
    {
      stepSize: 10
    },
    {
      stepSize: '10vp'
    },
    {
      stepSize: 50
    },
    {
      showTips: true // 滑动时显示气泡提示
    },
    {
      showTips: false
    },
    {
      blockSize: {
        width: 10,
        height: 10
      }
    },
    {
      blockSize: {
        width: '30vp',
        height: '30vp'
      }
    },
    {
      blockSize: {
        width: '10%',
        height: '10%'
      }
    },
    {
      blockSize: {
        width: 100,
        height: 100
      }
    },
    {
      blockSize: {
        width: 1,
        height: 1
      }
    },
    {
      trackBorderRadius: '10%'
    },
    {
      trackBorderRadius: 10
    },
    {
      trackBorderRadius: '10vp'
    },
    {
      stepColor: Color.Red
    },
    {
      stepColor: 'rgb(0,0,255)'
    },
    {
      stepColor: '#ff182431'
    },
    {
      selectedColor: Color.Red
    },
    {
      selectedColor: 'rgb(0,0,255)'
    },
    {
      selectedColor: '#ff182431'
    },
    {
      trackColor: Color.Red
    },
    {
      trackColor: 'rgb(0,0,255)'
    },
    {
      trackColor: '#ff182431'
    },
    {
      blockColor: Color.Red
    },
    {
      blockColor: 'rgb(0,0,255)'
    },
    {
      blockColor: '#ff182431'
    },
    {
      blockBorderColor: Color.Red,
      blockStyle: {
        type: SliderBlockType.SHAPE,
        shape: new Path({ commands: 'M60 60 M30 30 L15 56 L45 56 Z' })
      }
    },
    {
      blockBorderColor: 'rgb(0,0,255)',
      blockStyle: {
        type: SliderBlockType.SHAPE,
        shape: new Ellipse({ width: 10, height: 10 })
      }
    },
    {
      blockBorderColor: '#ff182431'
    },
    {
      blockBorderWidth: '10%'
    },
    {
      blockBorderWidth: 10
    },
    {
      blockBorderWidth: '10vp'
    },
    {
      showSteps: true
    },
    {
      showSteps: false
    },
    {
      trackThickness: '10%'
    },
    {
      trackThickness: 10
    },
    {
      trackThickness: '10vp'
    },
    {
      slideRange: ({ from: 20, to: 80 })
    },
    {
      slideRange: ({ from: 11, to: 97 }),
      direction: Direction.Rtl
    },
    {
      slideRange: ({ from: 9.99, to: 80 }),
      direction: Direction.Ltr
    },
    {
      slideRange: ({ from: 80, to: 100000 }),
      direction: Direction.Rtl
    },
    {
      slideRange: ({ from: 20 }),
      direction: undefined
    },
    {
      slideRange: ({ to: 80 }),
      enableHapticFeedback: true
    },
    {
      direction: Direction.Auto,
      enableHapticFeedback: true,
      showSteps: true
    },
    {
      direction: undefined,
      enableHapticFeedback: false,
      showSteps: true
    },
    {
      direction: Direction.Rtl,
      enableHapticFeedback: undefined,
      showSteps: true
    },
    {
      direction: Direction.Ltr,
      enableHapticFeedback: false,
      showSteps: true
    }
  ]
  public num: number = 0

  applyNormalAttribute(instance: SliderModifier): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(): void {
    this.stepSize(this.sliderStyle[this.num].stepSize)
    this.showTips(this.sliderStyle[this.num].showTips)
    this.blockStyle(this.sliderStyle[this.num].blockStyle)
    this.blockSize(this.sliderStyle[this.num].blockSize)
    this.trackBorderRadius(this.sliderStyle[this.num].trackBorderRadius)
    this.stepColor(this.sliderStyle[this.num].stepColor)
    this.blockBorderWidth(this.sliderStyle[this.num].blockBorderWidth)
    this.blockBorderColor(this.sliderStyle[this.num].blockBorderColor)
    this.blockColor(this.sliderStyle[this.num].blockColor)
    this.trackColor(this.sliderStyle[this.num].trackColor)
    this.selectedColor(this.sliderStyle[this.num].selectedColor)
    this.showSteps(this.sliderStyle[this.num].showSteps)
    this.trackThickness(this.sliderStyle[this.num].trackThickness)
    this.slideRange(this.sliderStyle[this.num].slideRange)
    this.direction(this.sliderStyle[this.num].direction)
    this.enableHapticFeedback(this.sliderStyle[this.num].enableHapticFeedback)
  }
}

class MyNodeController extends NodeController {
  makeNode(uiContext: UIContext): FrameNode | null {
    let node = new FrameNode(uiContext);
    node.commonAttribute
      .borderColor(Color.Gray)
      .borderWidth(1)
    let col = typeNode.createNode(uiContext, 'Column');
    col.initialize({ space: 5 })
    node.appendChild(col);
    let slider = typeNode.createNode(uiContext, 'Slider');
    slider
      .initialize({
        value: 20,
        min: 0,
        max: 100,
        style: SliderStyle.OutSet,
        step: 5,
        direction: Axis.Horizontal,
        reverse: true
      })
      .key('Slider3')
      .padding(5)
      .margin(5)
      .width(250)
      .height(50)
      .direction(Direction.Rtl)
      .borderWidth(1)
      .showTips(true)
      .blockColor(Color.Green)
      .trackColor('#FFFACD')
      .selectedColor('#FF4500')
      .showSteps(true)
      .trackThickness('30vp')
      .blockBorderColor(Color.White)
      .blockBorderWidth(10)
      .stepColor('#556B2F')
      .trackBorderRadius(25)
      .selectedBorderRadius(8)
      .blockSize({ width: 35, height: 35 })
      .stepSize(5)
      .sliderInteractionMode(SliderInteraction.SLIDE_AND_CLICK)
      .minResponsiveDistance(20)
      .slideRange({ from: 10, to: 80 })
      .onChange((value: number, mode: SliderChangeMode) => {
        console.info('lhg FrameNode Slider value:' + value + ' mode:' + mode.toString())
      })
    col.appendChild(slider);

    let row1 = typeNode.createNode(uiContext, 'Row');
    row1.initialize({ space: 5 })
    col.appendChild(row1);
    let slider1 = typeNode.createNode(uiContext, 'Slider');
    slider1
      .initialize({
        value: 20,
        min: 0,
        max: 100,
        style: SliderStyle.OutSet,
        step: 5
      })
      .width('45%')
      .blockStyle({ type: SliderBlockType.IMAGE, image: $r('sys.media.ohos_app_icon') })
      .key('Slider4')
    let slider2 = typeNode.createNode(uiContext, 'Slider');
    slider2
      .initialize({
        value: 20,
        min: 0,
        max: 100,
        style: SliderStyle.OutSet,
        step: 5
      })
      .width('45%')
      .blockSize({ width: '60px', height: '60px' })
      .blockColor(Color.Red)
      .blockStyle({ type: SliderBlockType.SHAPE, shape: new Path({ commands: 'M60 60 M30 30 L15 56 L45 56 Z' }) })
      .key('Slider5')
    row1.appendChild(slider1);
    row1.appendChild(slider2);

    let row2 = typeNode.createNode(uiContext, 'Row');
    row2.initialize({ space: 5 })
    col.appendChild(row2);
    let slider3 = typeNode.createNode(uiContext, 'Slider');
    slider3
      .initialize({
        value: 30,
        min: 0,
        max: 100,
        style: SliderStyle.InSet,
        step: 5
      })
      .width('45%')
      .blockStyle({ type: SliderBlockType.IMAGE, image: $r('sys.media.ohos_app_icon') })
      .key('Slider6')
    let slider4 = typeNode.createNode(uiContext, 'Slider');
    slider4
      .initialize({
        value: 30,
        min: 0,
        max: 100,
        style: SliderStyle.NONE,
        step: 5
      })
      .width('45%')
      .key('Slider7')
    row2.appendChild(slider3);
    row2.appendChild(slider4);
    return node;
  }
}

interface obj {
  showTips?: boolean,
  stepSize?: Length,
  blockStyle?: SliderBlockStyle,
  blockSize?: SizeOptions,
  trackBorderRadius?: Length,
  stepColor?: ResourceColor,
  blockBorderWidth?: Length,
  blockBorderColor?: ResourceColor,
  blockColor?: ResourceColor,
  trackColor?: ResourceColor,
  selectedColor?: ResourceColor,
  showSteps?: boolean,
  trackThickness?: Length,
  slideRange?: SlideRange,
  direction?: Direction,
  enableHapticFeedback?: boolean
}

@Entry
@Component
struct Slider_Level1_3 {
  pathStack: NavPathStack = new NavPathStack()
  @State mod1: SliderModifier = new MyModifier()
    .stepSize('10%')
    .showTips(undefined)
    .blockStyle(undefined)
    .blockSize(undefined)
    .trackBorderRadius(undefined)
    .stepColor(undefined)
    .blockBorderWidth(undefined)
    .blockBorderColor(undefined)
    .blockColor(undefined)
    .trackColor(undefined)
    .selectedColor(undefined)
    .showSteps(true)
    .trackThickness(undefined)
    .slideRange(undefined)
    .direction(undefined)
    .enableHapticFeedback(undefined)
  private myNodeController: MyNodeController = new MyNodeController();
  @State mod2: SliderModifier = new SliderModifier()
    .padding(5)
    .margin(5)
    .width(250)
    .height(50)
    .direction(Direction.Rtl)
    .borderWidth(1)
    .showTips(true)
    .blockColor(Color.Green)
    .trackColor('#FFFACD')
    .selectedColor('#FF4500')
    .showSteps(true)
    .trackThickness('30vp')
    .blockBorderColor(Color.White)
    .blockBorderWidth(10)
    .stepColor('#556B2F')
    .trackBorderRadius(25)
    .selectedBorderRadius(8)
    .blockSize({ width: 35, height: 35 })
    .stepSize(5)
    .sliderInteractionMode(SliderInteraction.SLIDE_AND_CLICK)
    .minResponsiveDistance(20)
    .slideRange({ from: 10, to: 80 })
    .onChange((value: number, mode: SliderChangeMode) => {
      console.info('lhg SliderModifier value:' + value + ' mode:' + mode.toString())
    })
  @State value1: number = 20

  onPageShow(): void {
    (this.mod1 as MyModifier).setGroup1()
  }

  build() {
    NavDestination() {
      Column({ space: 10 }) {
        Text('SliderStyle属性测试').fontSize(9).fontColor(0xCCCCCC).width('100%')
        Row({ space: 10 }) {
          Slider()
            .width('45%')
            .height(100)
            .key('Slider1')
            .attributeModifier((this.mod1 as MyModifier))
          Slider()
            .key('Slider2')
            .width('45%')
            .height(100)
            .stepSize((this.mod1 as MyModifier).sliderStyle[(this.mod1 as MyModifier).num].stepSize)
            .showTips((this.mod1 as MyModifier).sliderStyle[(this.mod1 as MyModifier).num].showTips)
            .blockStyle((this.mod1 as MyModifier).sliderStyle[(this.mod1 as MyModifier).num].blockStyle)
            .blockSize((this.mod1 as MyModifier).sliderStyle[(this.mod1 as MyModifier).num].blockSize)
            .trackBorderRadius((this.mod1 as MyModifier).sliderStyle[(this.mod1 as MyModifier).num].trackBorderRadius)
            .stepColor((this.mod1 as MyModifier).sliderStyle[(this.mod1 as MyModifier).num].stepColor)
            .blockBorderWidth((this.mod1 as MyModifier).sliderStyle[(this.mod1 as MyModifier).num].blockBorderWidth)
            .blockBorderColor((this.mod1 as MyModifier).sliderStyle[(this.mod1 as MyModifier).num].blockBorderColor)
            .blockColor((this.mod1 as MyModifier).sliderStyle[(this.mod1 as MyModifier).num].blockColor)
            .trackColor((this.mod1 as MyModifier).sliderStyle[(this.mod1 as MyModifier).num].trackColor)
            .selectedColor((this.mod1 as MyModifier).sliderStyle[(this.mod1 as MyModifier).num].selectedColor)
            .showSteps((this.mod1 as MyModifier).sliderStyle[(this.mod1 as MyModifier).num].showSteps)
            .trackThickness((this.mod1 as MyModifier).sliderStyle[(this.mod1 as MyModifier).num].trackThickness)
            .slideRange((this.mod1 as MyModifier).sliderStyle[(this.mod1 as MyModifier).num].slideRange)
            .direction((this.mod1 as MyModifier).sliderStyle[(this.mod1 as MyModifier).num].direction)
            .enableHapticFeedback((this.mod1 as MyModifier).sliderStyle[(this.mod1 as MyModifier).num]
              .enableHapticFeedback)
        }.height(100)

        Row({ space: 2 }) {
          Text(`${(this.mod1 as MyModifier).num + 1}/`)
          Text(`${(this.mod1 as MyModifier).sliderStyle.length}`)
            .key('SliderLevel13')
          Button() {
            Text('Index++')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
          }
          .onClick(() => {
            (this.mod1 as MyModifier).num++
            if ((this.mod1 as MyModifier).num > (this.mod1 as MyModifier).sliderStyle.length - 1) {
              (this.mod1 as MyModifier).num = 0
            }
            (this.mod1 as MyModifier).setGroup1()
          })

          Button() {
            Text('Index--')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
          }
          .onClick(() => {
            (this.mod1 as MyModifier).num--
            if ((this.mod1 as MyModifier).num < 0) {
              (this.mod1 as MyModifier).num = (this.mod1 as MyModifier).sliderStyle.length - 1
            }
            (this.mod1 as MyModifier).setGroup1()
          })
        }

        Column({ space: 5 }) {
          Divider()
          Text('FrameNode').fontSize(15).width('100%')
          NodeContainer(this.myNodeController);
          Divider()
          Text('Modifier').fontSize(15).width('100%')
          Slider({
            value: 20,
            min: 0,
            max: 100,
            style: SliderStyle.OutSet,
            step: 5,
            direction: Axis.Horizontal,
            reverse: true
          })
            .attributeModifier((this.mod2 as SliderModifier))
            .key('Slider8')
          Divider()
          Text('原生' + this.value1).fontSize(15).width('100%')
          Slider({
            value: this.value1!!,
            min: 0,
            max: 100,
            style: SliderStyle.OutSet,
            step: 5,
            direction: Axis.Horizontal,
            reverse: true
          })
            .key('Slider9')
            .padding(5)
            .margin(5)
            .width(250)
            .height(50)
            .direction(Direction.Rtl)
            .borderWidth(1)
            .showTips(true)
            .blockColor(Color.Green)
            .trackColor('#FFFACD')
            .selectedColor('#FF4500')
            .showSteps(true)
            .trackThickness('30vp')
            .blockBorderColor(Color.White)
            .blockBorderWidth(10)
            .stepColor('#556B2F')
            .trackBorderRadius(25)
            .selectedBorderRadius(8)
            .blockSize({ width: 35, height: 35 })
            .stepSize(5)
            .sliderInteractionMode(SliderInteraction.SLIDE_AND_CLICK)
            .minResponsiveDistance(20)
            .slideRange({ from: 10, to: 80 })
            .onChange((value: number, mode: SliderChangeMode) => {
              console.info('lhg Slider native value:' + value + ' mode:' + mode.toString())
            })
        }
        .width('100%')
      }
      .width('100%')
    }
    .title('SliderLevel13')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}