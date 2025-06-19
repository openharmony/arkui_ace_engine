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

import { getParamsInfo } from './util';
import { ThemeControl } from '@kit.ArkUI';

@Builder
export function SliderLevel0Builder(name: string, param: Object) {
  Slider_Level0_0()
}

ThemeControl.setDefaultTheme(null);

declare interface interface1 {
  value?: number | undefined;
  min?: number | undefined;
  max?: number | undefined;
  step?: number | undefined;
  style?: SliderStyle | undefined;
  direction?: Axis | undefined;
  reverse?: boolean | undefined
}

declare interface selfAttribute1 {
  blockColor?: ResourceColor | undefined;
  trackColor?: ResourceColor | LinearGradient | undefined;
  selectedColor?: ResourceColor | undefined;
  showSteps?: boolean | undefined;
  trackThickness?: Length | undefined;
  blockBorderColor?: ResourceColor | undefined;
  blockBorderWidth?: Length | undefined;
  stepColor?: ResourceColor | undefined;
  trackBorderRadius?: Length | undefined;
  blockStyle?: SliderBlockStyle | undefined;
  blockSize?: SizeOptions | undefined;
  stepSize?: Length | undefined;
  selectedBorderRadius?: Dimension | undefined,
  sliderInteractionMode?: SliderInteraction | undefined,
  minResponsiveDistance?: number | undefined,
  slideRange?: SlideRange | undefined
}

interface showTips {
  value?: boolean | undefined;
  content?: ResourceStr | undefined
}

declare interface testCases1 {
  interface: interface1;
  selfAttribute: selfAttribute1
  showTips: showTips
}

@Entry
@Component
struct Slider_Level0_0 {
  pathStack: NavPathStack = new NavPathStack()
  @State value1: number = 0
  @State reverse: boolean | undefined = undefined
  @State direction1: Axis | undefined = undefined
  @State indexArray: number[] = [0, 0, 0, 0, 0]
  @State show: boolean = false
  @State info: string = ''
  @State currentValue1: number | undefined = 0
  testCases1: testCases1[] = [
  //验证接口属性
    {
      interface: {},
      selfAttribute: {},
      showTips: {}
    },
    {
      interface: {},
      selfAttribute: {
        slideRange: { from: 20, to: 80 }
      },
      showTips: {}
    },
    {
      interface: {
        min: 10,
        max: 110,
        value: -1000,
      },
      selfAttribute: {
        slideRange: { from: 20, to: 80 }
      },
      showTips: {}
    },
    {
      interface: {
        min: 110,
        max: 10,
      },
      selfAttribute: {
        slideRange: { from: 20, to: 80 }
      },
      showTips: {}
    },
    {
      //验证style，direction，reverse三个属性
      interface: {
        value: 20,
        min: 10,
        max: 110,
        step: 2,
        style: SliderStyle.InSet,
        direction: Axis.Vertical,
        reverse: true,
      },
      selfAttribute: {
        sliderInteractionMode: SliderInteraction.SLIDE_AND_CLICK,
        minResponsiveDistance: 0,
        selectedBorderRadius: 6,
        slideRange: { from: 20, to: 80 }
      },
      showTips: {}
    },
    {
      //验证style，direction，reverse三个属性
      interface: {
        value: 20,
        min: 10,
        max: 110,
        step: 2,
        style: SliderStyle.NONE,
        direction: Axis.Vertical,
        reverse: true,
      },
      selfAttribute: {
        selectedBorderRadius: '20%',
        sliderInteractionMode: SliderInteraction.SLIDE_AND_CLICK,
        minResponsiveDistance: -5,
        slideRange: { from: 20 }
      },
      showTips: {}
    },
    {
      //验证style，direction，reverse三个属性
      interface: {
        value: 20,
        min: 10,
        max: 110,
        step: 2,
        style: SliderStyle.OutSet,
        direction: Axis.Horizontal,
        reverse: false,
      },
      selfAttribute: {
        selectedBorderRadius: 12,
        sliderInteractionMode: SliderInteraction.SLIDE_AND_CLICK,
        minResponsiveDistance: 10,
        slideRange: { to: 80 }
      },
      showTips: {}
    },
    {
      //验证min大于max的异常情况
      interface: {
        value: 20,
        min: 110,
        max: 10,
        step: 2,
        style: SliderStyle.OutSet,
        direction: Axis.Horizontal,
        reverse: false,
      },
      selfAttribute: {
        selectedBorderRadius: 24,
        sliderInteractionMode: SliderInteraction.SLIDE_AND_CLICK,
        minResponsiveDistance: 50,
        slideRange: { from: 2, to: 89 }
      },
      showTips: {}
    },
    {
      //验证min，max取值小数（非零点几）的情况
      interface: {
        value: 20,
        min: 0.1,
        max: 11.5,
        step: 2,
        style: SliderStyle.OutSet,
        direction: Axis.Horizontal,
        reverse: false,
      },
      selfAttribute: {
        selectedBorderRadius: 36,
        sliderInteractionMode: SliderInteraction.SLIDE_AND_CLICK,
        minResponsiveDistance: 2,
        slideRange: { from: -10, to: 80 }
      },
      showTips: {}
    },
    {
      //验证min，max取值负数，value不在范围的情况
      interface: {
        value: 20,
        min: -100,
        max: -1,
        step: 2,
        style: SliderStyle.OutSet,
        direction: Axis.Horizontal,
        reverse: false,
      },
      selfAttribute: {
        selectedBorderRadius: '10px',
        sliderInteractionMode: SliderInteraction.SLIDE_AND_CLICK,
        minResponsiveDistance: 1000,
        slideRange: { from: 10000 }
      },
      showTips: {}
    },
    {
      //验证min，max取值负数，value在范围的情况
      interface: {
        value: -20,
        min: -100,
        max: -1,
        step: 2,
        style: SliderStyle.OutSet,
        direction: Axis.Horizontal,
        reverse: false,
      },
      selfAttribute: {
        selectedBorderRadius: '5vp',
        sliderInteractionMode: SliderInteraction.SLIDE_AND_CLICK,
        minResponsiveDistance: 5.5,
        slideRange: { from: 80, to: 20 }
      },
      showTips: {}
    },
    {
      //验证value大于max的情况
      interface: {
        value: 200,
        min: 10,
        max: 110,
        step: 2,
        style: SliderStyle.InSet,
        direction: Axis.Vertical,
        reverse: true,
      },
      selfAttribute: {
        selectedBorderRadius: '10fp',
        sliderInteractionMode: SliderInteraction.SLIDE_ONLY,
        minResponsiveDistance: 0,
        slideRange: { from: 9.99, to: 80 }
      },
      showTips: {}
    },
    {
      //验证value小于min的情况
      interface: {
        value: 5,
        min: 10,
        max: 110,
        step: 2,
        style: SliderStyle.InSet,
        direction: Axis.Vertical,
        reverse: true,
      },
      selfAttribute: {
        selectedBorderRadius: '20lpx',
        sliderInteractionMode: undefined,
        minResponsiveDistance: 10,
        slideRange: { from: 20, to: 81.72165566486322 }
      },
      showTips: {}
    },
    {
      //验证step为负数的情况
      interface: {
        value: 20,
        min: 10,
        max: 110,
        step: -50,
        style: SliderStyle.InSet,
        direction: Axis.Vertical,
        reverse: true,
      },
      selfAttribute: {
        selectedBorderRadius: $r('app.string.rWidth'),
        sliderInteractionMode: SliderInteraction.SLIDE_ONLY,
        minResponsiveDistance: 5,
        slideRange: { from: 20, to: 20 }
      },
      showTips: {}
    },
    {
      //验证step为极大数（超过max）的情况
      interface: {
        value: 20,
        min: 10,
        max: 110,
        step: 10000,
        style: SliderStyle.InSet,
        direction: Axis.Vertical,
        reverse: true,
      },
      selfAttribute: {
        selectedBorderRadius: $r('app.color.rColor3'),
        sliderInteractionMode: SliderInteraction.SLIDE_AND_CLICK,
        minResponsiveDistance: 5.5,
        slideRange: { from: 20, to: undefined }
      },
      showTips: {}
    },
    {
      //验证step为小数（非零点几，且大于1）的情况
      interface: {
        value: 20,
        min: 10,
        max: 110,
        step: 1.5,
        style: SliderStyle.NONE,
        direction: Axis.Vertical,
        reverse: true,
      },
      selfAttribute: {
        sliderInteractionMode: SliderInteraction.SLIDE_AND_CLICK,
        minResponsiveDistance: -5,
        selectedBorderRadius: $r('app.media.app_icon'),
        slideRange: { from: 20, to: 80 },
        blockColor: Color.Red,
        blockSize: {
          width: 20,
          height: 30
        },
        blockStyle: {
          type: SliderBlockType.SHAPE,
          shape: new Ellipse({ width: 20, height: 30 })
        }
      },
      showTips: {}
    },
    {
      //验证step为小数（非零点几，且小于0.01）的情况
      interface: {
        value: 20,
        min: 10,
        max: 110,
        step: 0.001,
        style: SliderStyle.NONE,
        direction: Axis.Vertical,
        reverse: true,
      },
      selfAttribute: {
        sliderInteractionMode: undefined,
        minResponsiveDistance: undefined,
        selectedBorderRadius: undefined,
        slideRange: undefined,
        blockColor: Color.Red,
        blockSize: {
          width: 20,
          height: 20
        },
        blockStyle: {
          type: SliderBlockType.SHAPE,
          shape: new Circle({ width: 20, height: 20 })
        }
      },
      showTips: {}
    },
    //自有属性颜色类
    {
      interface: {},
      selfAttribute: {
        blockColor: Color.Pink,
        trackColor: Color.Yellow,
        selectedColor: Color.Blue,
        showSteps: true,
        trackThickness: 10,
        blockBorderColor: Color.Green,
        blockBorderWidth: 2,
        stepColor: Color.Black,
        trackBorderRadius: 10,
        slideRange: { to: 1000 },
        blockSize: {
          width: 30,
          height: 30
        },
        stepSize: 5
      },
      showTips: {}
    },
    {
      interface: {},
      selfAttribute: {
        sliderInteractionMode: SliderInteraction.SLIDE_AND_CLICK,
        minResponsiveDistance: 10000,
        selectedBorderRadius: 0,
        blockColor: '#808000',
        trackColor: '#ffff00',
        selectedColor: '#00ff00',
        showSteps: true,
        trackThickness: '20',
        blockBorderColor: '#800080',
        blockBorderWidth: '4',
        stepColor: '#ff0000',
        trackBorderRadius: '20',
        slideRange: { from: -10 },
        blockSize: {
          width: '20',
          height: '20'
        },
        blockStyle: {
          type: SliderBlockType.DEFAULT,
        },
        stepSize: '1'
      },
      showTips: {}
    },
    {
      interface: {},
      selfAttribute: {
        sliderInteractionMode: SliderInteraction.SLIDE_AND_CLICK,
        minResponsiveDistance: 4,
        selectedBorderRadius: -100,
        blockColor: 'rgb(255,0,0)',
        trackColor: 'rgb(0,255,0)',
        selectedColor: 'rgb(0,0,255)',
        showSteps: true,
        trackThickness: $r('app.string.rTrackThickness'),
        blockBorderColor: 'rgb(255,165,0)',
        blockBorderWidth: $r('app.string.rBorderWidth'),
        stepColor: 'rgb(255,182,193)',
        trackBorderRadius: $r('app.string.rBorderRadius'),
        blockSize: {
          width: $r('app.string.rWidth'),
          height: $r('app.string.rHeight')
        },
        blockStyle: {
          type: SliderBlockType.SHAPE,
        },
        stepSize: $r('app.string.rStepSize')
      },
      showTips: {}
    },
    {
      interface: {},
      selfAttribute: {
        selectedBorderRadius: 100000,
        blockColor: undefined,
        trackColor: undefined,
        selectedColor: undefined,
        showSteps: true,
        trackThickness: $r('app.string.rTrackThickness'),
        blockBorderColor: undefined,
        blockBorderWidth: $r('sys.float.alert_title_padding_left'),
        stepColor: undefined,
        trackBorderRadius: $r('sys.float.border_small'),
        blockSize: {
          width: $r('app.string.rWidth'),
          height: $r('app.string.rHeight')
        },
        blockStyle: {
          type: SliderBlockType.IMAGE,
          image: 'common/win.png'
        },
        stepSize: $r('app.string.rStepSize')
      },
      showTips: {}
    },
    {
      //颜色属性不设置时的情况
      interface: {},
      selfAttribute: {
        selectedBorderRadius: 10.5,
        showSteps: true,
        trackThickness: '50px',
        blockBorderWidth: $r('app.string.rBorderWidth'),
        trackBorderRadius: '2px',
        blockSize: {
          width: $r('app.string.rWidth'),
          height: $r('app.string.rHeight')
        },
        blockStyle: {
          type: SliderBlockType.IMAGE,
          image: 'common/win.png'
        },
        stepSize: '2%'
      },
      showTips: {}
    },
    {
      //颜色类设置resource类型正常值
      interface: {},
      selfAttribute: {
        blockColor: $r('app.color.start_window_background'),
        trackColor: $r('app.color.rColor'),
        selectedColor: $r('app.color.rColor1'),
        showSteps: true,
        trackThickness: $r('sys.float.titlebar_title_tertiary_size'),
        blockBorderColor: $r('app.color.rColor2'),
        blockBorderWidth: '9px',
        stepColor: $r('app.color.rColor3'),
        trackBorderRadius: '4vp',
        blockSize: {
          width: $r('app.string.rWidth'),
          height: $r('app.string.rHeight')
        },
        blockStyle: {
          type: SliderBlockType.IMAGE,
          image: 'common/win.png'
        },
        stepSize: $r('sys.float.border_small')
      },
      showTips: {}
    },
    {
      //颜色类设置resource类型异常字符串（即非十六进制字符串）
      interface: {},
      selfAttribute: {
        blockColor: $r('app.string.EntryAbility_desc'),
        trackColor: $r('app.string.EntryAbility_desc'),
        selectedColor: $r('app.string.EntryAbility_desc'),
        showSteps: true,
        trackThickness: '60vp',
        blockBorderColor: $r('app.string.EntryAbility_desc'),
        blockBorderWidth: '3vp',
        stepColor: $r('app.string.EntryAbility_desc'),
        trackBorderRadius: '6fp',
        blockSize: {
          width: $r('app.string.rWidth'),
          height: $r('app.string.rHeight')
        },
        blockStyle: {
          type: SliderBlockType.IMAGE,
          image: 'common/win.png'
        },
        stepSize: '10px'
      },
      showTips: {}
    },
    {
      //颜色类设置异常字符串（即非十六进制字符串）
      interface: {},
      selfAttribute: {
        blockColor: 'fjsdkskdks',
        trackColor: 'fjsdkksskk\nskdks',
        selectedColor: 'fjsdkskdsjjdjsjsjjsjdks',
        showSteps: true,
        trackThickness: $r('app.string.rTrackThickness'),
        blockBorderColor: '$jskdk#',
        blockBorderWidth: '5fpx',
        stepColor: 'djsjdnandanmamsmamsmmmsmmjriw3jajsnhahnsnqansnan',
        trackBorderRadius: '3lpx',
        blockSize: {
          width: $r('app.string.rWidth'),
          height: $r('app.string.rHeight')
        },
        blockStyle: {
          type: SliderBlockType.DEFAULT,
        },
        stepSize: '20vp'
      },
      showTips: {}
    },
    //自有属性非颜色类
    {
      //设置步长点大小stepSize超过滑轨粗细trackThickness
      interface: {
        value: 20,
        min: 10,
        max: 110,
      },
      selfAttribute: {
        blockColor: $r('sys.color.ohos_id_select_font_color'),
        trackColor: $r('sys.color.comp_background_gray'),
        selectedColor: $r('sys.color.multi_color_09'),
        showSteps: true,
        trackThickness: 20,
        blockBorderColor: $r('sys.color.background_primary'),
        blockBorderWidth: 3,
        trackBorderRadius: '2%',
        blockSize: {
          width: 50,
          height: 50
        },
        blockStyle: {
          type: SliderBlockType.SHAPE,
          shape: new Rect({ width: 20, height: 20 }).fill(Color.Red)
        },
        stepSize: 25
      },
      showTips: {
        value: false
      }
    },
    {
      interface: {
        value: 20,
        min: 10,
        max: 110,
      },
      selfAttribute: {
        showSteps: true,
        trackThickness: 20,
        blockBorderWidth: '7fp',
        trackBorderRadius: 20,
        blockSize: {
          width: 100000,
          height: 10000
        },
        blockStyle: {
          type: SliderBlockType.IMAGE,
          image: 'common/win.png'
        },
        stepSize: -100
      },
      showTips: {
        value: true,
        content: '世界欠我一个你，是世界欠的，不是你'
      }
    },
    {
      interface: {
        value: 20,
        min: 10,
        max: 110,
      },
      selfAttribute: {
        showSteps: true,
        trackThickness: 20,
        blockBorderWidth: 3,
        trackBorderRadius: 20,
        blockSize: {
          width: -100,
          height: -100
        },
        blockStyle: {
          type: SliderBlockType.SHAPE,
          shape: new Rect({ width: 20, height: 20 }).fill(Color.Red)
        },
        stepSize: 150
      },
      showTips: {
        value: true,
        content: '世界欠我一个你，是世界欠的，不是你'
      }
    },
    {
      interface: {
        value: 20,
        min: 10,
        max: 110,
        direction: Axis.Vertical
      },
      selfAttribute: {
        showSteps: false,
        trackThickness: -100,
        blockBorderWidth: -100,
        trackBorderRadius: -100,
        blockSize: {
          width: 20,
          height: 15
        },
        blockStyle: {
          type: SliderBlockType.DEFAULT,
        },
        stepSize: 110
      },
      showTips: {
        value: false
      }
    },
    {
      interface: {
        value: 20,
        min: 10,
        max: 110,
        direction: Axis.Vertical
      },
      selfAttribute: {
        trackColor: undefined,
        showSteps: true,
        trackThickness: 0,
        blockBorderWidth: 0,
        trackBorderRadius: 0,
        blockSize: {
          width: 15,
          height: 15
        },
        blockStyle: {
          type: SliderBlockType.IMAGE,
          image: 'common/win.png'
        },
        stepSize: 10.5
      },
      showTips: {
        value: true,
        content: $r('app.string.EntryAbility_desc')
      }
    },
    {
      interface: {
        value: 20,
        min: 10,
        max: 110,
        direction: Axis.Horizontal
      },
      selfAttribute: {
        showSteps: true,
        trackColor: new LinearGradient([{ color: Color.White, offset: 0.5 },
          { color: Color.Pink, offset: 0.3 }, { color: Color.Red, offset: 1 }, { color: Color.Green, offset: 0.7 }]),
        trackThickness: 1000,
        blockBorderWidth: 1000,
        trackBorderRadius: 1000,
        blockSize: {
          width: 30,
          height: 30
        },
        blockStyle: {
          type: SliderBlockType.SHAPE,
          shape: new Rect({ width: 20, height: 20 }).fill(Color.Red)
        },
        stepSize: 0
      },
      showTips: {
        value: true,
        content: '世界欠我一个你，是世界欠的，不是你'
      }
    },
    {
      interface: {
        style: SliderStyle.OutSet
      },
      selfAttribute: {
        blockColor: Color.Red,
        trackColor: new LinearGradient([{ color: Color.Pink, offset: 0.5 }]),
        selectedColor: Color.Blue,
        showSteps: true,
        trackThickness: 5000,
        blockBorderColor: Color.Red,
        blockBorderWidth: 2,
        stepColor: Color.Black,
        trackBorderRadius: 10,
        blockSize: { width: '60px', height: '60px' },
        blockStyle: {
          type: SliderBlockType.SHAPE,
          shape: new Path({ commands: 'M30 30 L15 56 L45 56 Z' })
        },
        stepSize: 0
      },
      showTips: {
        value: true,
        content: $r('sys.string.ohos_desc_bundle_active_info')
      }
    },
    {
      interface: {
        style: SliderStyle.InSet
      },
      selfAttribute: {
        blockColor: Color.Red,
        trackColor: new LinearGradient([
          { color: Color.Yellow, offset: 0 },
          { color: Color.Blue, offset: 0.1 },
          { color: Color.Red, offset: 0.2 },
          { color: Color.Green, offset: 0.3 },
          { color: Color.White, offset: 0.4 },
          { color: Color.Brown, offset: 0.5 },
          { color: Color.Orange, offset: 0.6 },
          { color: Color.Pink, offset: 0.7 },
          { color: '#ff1f88c9', offset: 0.8 },
          { color: '#ff9f00d9', offset: 0.9 },
          { color: '#ffcc88c9', offset: 1 }]),
        selectedColor: Color.Blue,
        showSteps: true,
        trackThickness: '5%',
        blockBorderColor: Color.Red,
        blockBorderWidth: 2,
        stepColor: $r('sys.color.multi_color_04'),
        trackBorderRadius: 10,
        stepSize: 0
      },
      showTips: {
        value: true
      }
    },
    {
      interface: {
        style: SliderStyle.InSet,
        direction: Axis.Vertical,
        max: 50,
        reverse: true
      },
      selfAttribute: {
        blockColor: Color.Pink,
        trackColor: new LinearGradient([]),
        selectedColor: Color.Blue,
        showSteps: true,
        trackThickness: 9000,
        blockBorderColor: Color.Green,
        blockBorderWidth: 2,
        stepColor: Color.Black,
        trackBorderRadius: 10,
        stepSize: 5
      },
      showTips: {
        value: true
      }
    },
    {
      interface: {
        step: 0.01,
        style: SliderStyle.InSet
      },
      selfAttribute: {
        blockColor: 0x777666,
        trackColor: new LinearGradient([{ color: Color.White, offset: 0 }, {
          color: Color.Blue,
          offset: 0.5
        }, { color: Color.Red, offset: 1 }]),
        selectedColor: 0x884488,
        showSteps: true,
        trackThickness: '',
        blockBorderColor: 0x33668899,
        blockBorderWidth: 3,
        stepColor: Color.Yellow,
        trackBorderRadius: 20,
        blockSize: {
          width: 15,
          height: 15
        },
        blockStyle: {
          type: SliderBlockType.SHAPE,
          shape: new Rect({ width: 20, height: 20 }).fill(Color.Red)
        },
        stepSize: '5lpx'
      },
      showTips: {
        value: true
      }
    }
  ]

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 10 }) {
          Text('Slider组件接口参数/自有属性测试').fontSize(9).fontColor(0xCCCCCC).width('100%').margin({ top: 10 })
          Row({ space: 10 }) {
            Slider(this.testCases1[this.indexArray[0]].interface)
              .onChange((value: number, mode: SliderChangeMode) => {
                this.currentValue1 = value
                if (this.testCases1[this.indexArray[0]].selfAttribute.sliderInteractionMode ==
                SliderInteraction.SLIDE_ONLY) {
                  console.info('ljx mode:' + mode.toString())
                }
              })
              .onAppear(() => {
                this.currentValue1 = this.testCases1[this.indexArray[0]].interface.value
                console.info(`ljx slider appear`)
              })
              .onDisAppear(() => {
                console.info(`ljx slider disappear`)
              })
              .width('80%')
              .minResponsiveDistance(this.testCases1[this.indexArray[0]].selfAttribute.minResponsiveDistance)
              .sliderInteractionMode(this.testCases1[this.indexArray[0]].selfAttribute.sliderInteractionMode)
              .selectedBorderRadius(this.testCases1[this.indexArray[0]].selfAttribute.selectedBorderRadius)
              .blockColor(this.testCases1[this.indexArray[0]].selfAttribute.blockColor)
              .trackColor(this.testCases1[this.indexArray[0]].selfAttribute.trackColor)
              .selectedColor(this.testCases1[this.indexArray[0]].selfAttribute.selectedColor)
              .showTips(this.testCases1[this.indexArray[0]].showTips.value,
                this.testCases1[this.indexArray[0]].showTips.content)
              .showSteps(this.testCases1[this.indexArray[0]].selfAttribute.showSteps)
              .trackThickness(this.testCases1[this.indexArray[0]].selfAttribute.trackThickness)
              .blockBorderColor(this.testCases1[this.indexArray[0]].selfAttribute.blockBorderColor)
              .blockBorderWidth(this.testCases1[this.indexArray[0]].selfAttribute.blockBorderWidth)
              .stepColor(this.testCases1[this.indexArray[0]].selfAttribute.stepColor)
              .trackBorderRadius(this.testCases1[this.indexArray[0]].selfAttribute.trackBorderRadius)
              .blockSize(this.testCases1[this.indexArray[0]].selfAttribute.blockSize)
              .blockStyle(this.testCases1[this.indexArray[0]].selfAttribute.blockStyle)
              .slideRange(this.testCases1[this.indexArray[0]].selfAttribute.slideRange)
              .borderWidth(2)
              .stepSize(this.testCases1[this.indexArray[0]].selfAttribute.stepSize)
              .key('slider')
            Text(this.currentValue1?.toFixed(2)).fontSize(12).width('15%')

          }
          .width('100%')
          .height(300)
          .justifyContent(FlexAlign.Center)

          Divider()
          Text('切换测试参数,显示参数=' + this.show).fontSize(9).fontColor(0xCCCCCC).width('100%').onClick(() => {
            this.show = !this.show
          })
          Row({ space: 2 }) {
            Text(`${this.indexArray[0] + 1}/`)
              .width(25)
            Text(`${this.testCases1.length}`)
              .key(`totalTest1`)
            Text('Test++')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick(() => {
                this.indexArray[0]++
                if (this.indexArray[0] >= this.testCases1.length) {
                  this.indexArray[0] = 0
                }
                this.currentValue1 = this.testCases1[this.indexArray[0]].interface.value ?? 0
                this.info = getParamsInfo(this.testCases1[this.indexArray[0]])
              })
            Text('Test--')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick(() => {
                this.indexArray[0]--
                if (this.indexArray[0] < 0) {
                  this.indexArray[0] = this.testCases1.length - 1
                }
                this.currentValue1 = this.testCases1[this.indexArray[0]].interface.value ?? 0
                this.info = getParamsInfo(this.testCases1[this.indexArray[0]])

              })
          }

          Divider()
          Text('纵横正反向切换查看滑块').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Slider({
            style: SliderStyle.InSet,
            value: this.value1,
            reverse: this.reverse,
            direction: this.direction1
          })
            .showSteps(true)
            .stepSize(8)
            .stepColor(Color.Yellow)
            .showTips(true)
            .width('60%')
            .height(200)
            .onChange((value: number) => {
              this.value1 = value
            })
            .key('slider01')
          Divider()
          Text('纵横切换查看滑块').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Row({ space: 2 }) {
            Text('纵向')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick(() => {
                this.direction1 = Axis.Vertical
              })
            Text('横向')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick(() => {
                this.direction1 = Axis.Horizontal
              })
            Text('un01')
              .key('direction1')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick(() => {
                this.direction1 = undefined
              })
          }

          Divider()
          Text('正反向切换查看滑块').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Row({ space: 2 }) {
            Text('true')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick(() => {
                this.reverse = true
              })
            Text('false')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick(() => {
                this.reverse = false
              })
            Text('un02')
              .key('reverse1')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick(() => {
                this.reverse = undefined
              })
          }

          if (this.show) {
            Text(this.info)
          }
        }
        .width('100%')
        .borderWidth(2)
      }
      .width('100%')
      .height('100%')
      .align(Alignment.Top)
    }
    .title('SliderLevel0')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}