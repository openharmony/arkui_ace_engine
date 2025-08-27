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

/*
 * This code defines a component named 'ImageAnimator' designed to test various properties and events 
 * of the ImageAnimator component. 
 * It includes:
 * - State variables for managing animation status, model data, info display, visibility, and an index for test cases.
 * - Different configurations to validate behavior such as duration handling, fixed size enforcement, reverse 
 * playback, iteration counts, and fill modes.
 * - A 'setParam' method to update the model's properties based on the current test case index.
 * - The 'build' method constructs the UI layout featuring:
 *   - Text components for titles and instructions.
 *   - Two ImageAnimator components demonstrating different settings.
 *   - Buttons for controlling animation states (initial, running, paused, stopped, undefined).
 *   - Controls for navigating through test cases and displaying current parameters.
 * - Helper classes and methods for managing model data and converting enum values to strings for display purposes.
 */

interface PageItemAn00 {
  imagesValue?: Array<ImageFrameInfo> | null
  duration?: number | null
  reverse?: boolean | null
  fillMode?: FillMode | null
  iterations?: number | null
  fixedSize?: boolean | null
}

@Entry
@Component
struct ImageAnimator {
  @State stateVal?: AnimationStatus | null = undefined
  @State model3: Model3 = new Model3()
  @State info?: string | null = undefined
  @State show: boolean = false
  private index: number = 0
  private testCase: PageItemAn00[] = [
    {
      imagesValue: [{
        src: $r('app.media.flower'),
        width: 200,
        height: 100,
        top: 10,
        left: 20
      },
        {
          src: '/common/ic_gif.gif',
          width: 300,
          height: 200,
          top: 0,
          left: 0
        },
        {
          src: $r('app.media.app_icon'),
          width: '50vp',
          height: '50vp',
          top: '50vp',
          left: '50vp'
        },
        {
          src: $r('app.media.ic_svg'),
          width: 100,
          height: 100,
          top: -10,
          left: -10
        },
        {
          src: '/common/ic_bmp.bmp',
          width: 100,
          height: 300,
          top: -10,
          left: -10
        }],
      duration: 6000,
      reverse: false,
      fixedSize: true,
      fillMode: FillMode.Forwards,
      iterations: 2,
    },
    {
      imagesValue: [{
        src: $r('app.media.png_525_539'),
        width: 100,
        height: 200,
        top: 0,
        left: 0,
        duration: 6000
      },
        {
          src: $r('app.media.jpeg_690_669'),
          width: '50vp',
          height: '100vp',
          top: '10vp',
          left: '20vp',
          duration: 6000
        },
        {
          src: '/common/ic_png2.png',
          width: 200,
          height: 100,
          top: -40,
          left: -30,
          duration: 2000
        }],
      duration: 2000,
      reverse: true,
      fixedSize: false,
      fillMode: FillMode.Backwards,
      iterations: -1,
    },
    {
      imagesValue: [{
        src: '/common/png_256_256.png',
        width: '120vp',
        height: '350vp',
        top: '40vp',
        left: '30vp',
        duration: 200000
      },
        {
          src: $r('app.media.png_525_539'),
          width: 100,
          height: 200,
          top: 10,
          left: 20,
          duration: 6000
        },
        {
          src: $r('app.media.jpeg_690_669'),
          width: '50vp',
          height: '100vp',
          top: '5vp',
          left: '5vp',
          duration: -6000
        },
        {
          src: '/common/ic_png2.png',
          width: 200,
          height: 300,
          top: 40,
          left: 30,
          duration: 20
        },
        {
          src: '/common/jpg_240_160.jpg',
          width: -300,
          height: -100,
          top: 40,
          left: 30,
          duration: 2000
        },

        {
          src: $r('app.media.ic_public_refresh'),
          width: 300,
          height: 120,
          top: -400,
          left: -30,
          duration: 2000
        },
        {
          src: $r('app.media.png_608_317'),
          width: 350,
          height: 0,
          top: 40,
          left: 30,
          duration: 6000
        },
        {
          src: '/common/ic_png.png',
          width: '250vp',
          height: 50,
          top: '20%',
          left: '30%',
          duration: 6000
        },
        {
          src: $r('app.media.alt_svg'),
          width: 0,
          height: '250vp',
          top: 40,
          left: 30,
          duration: 6000
        },
        {
          src: '/common/yellowperson.jpg',
          width: '100%',
          height: '20%',
          top: 40,
          left: 30,
          duration: 6000
        }],
      duration: 2000,
      reverse: true,
      fixedSize: false,
      fillMode: FillMode.None,
      iterations: 3,
    },
    {
      imagesValue: [{
        src: '/common/ic_png2.png',
        width: 300,
        height: 100,
        top: 40,
        left: 30,
        duration: 2000
      },
        {
          src: $r('app.media.png_525_539'),
          width: 100,
          height: 200,
          top: 10,
          left: 20,
          duration: 6000
        },
        {
          src: $r('app.media.jpeg_690_669'),
          width: '50vp',
          height: '100vp',
          top: 10,
          left: 20,
          duration: 6000
        }],

      duration: 2000,
      reverse: true,
      fixedSize: false,
      fillMode: FillMode.Backwards,
      iterations: 0,
    },
    {
      imagesValue: [
        {
          src: $r('app.media.png_608_317'),
          width: 300,
          height: 100,
          top: 40,
          left: 30
        },
        {
          src: $r('app.media.png_525_539'),
          width: 100,
          height: 200,
          top: 10,
          left: 20
        },
        {
          src: $r('app.media.jpeg_690_669'),
          width: '50vp',
          height: '100vp',
          top: 10,
          left: 20
        },
        {
          src: '/common/ic_png2.png',
          width: 300,
          height: 100,
          top: 40,
          left: 30
        },
        {
          src: '/common/jpg_240_160.jpg',
          width: 300,
          height: 100,
          top: 40,
          left: 30
        },
        {
          src: '/common/png_256_256.png',
          width: 300,
          height: 100,
          top: 40,
          left: 30
        },
        {
          src: $r('app.media.ic_public_refresh'),
          width: 300,
          height: 100,
          top: 40,
          left: 30
        },
        {
          src: '/common/ic_png.png',
          width: 300,
          height: 100,
          top: 40,
          left: 30
        },
        {
          src: $r('app.media.alt_svg'),
          width: 300,
          height: 100,
          top: 40,
          left: 30
        },
        {
          src: '/common/yellowperson.jpg',
          width: 300,
          height: 100,
          top: 40,
          left: 30
        }
      ],
      duration: 0,
      reverse: false,
      fixedSize: true,
      fillMode: FillMode.Both,
      iterations: 1,
    },
    {
      imagesValue: [{
        src: '/common/ic_png2.png',
        width: 300,
        height: 100,
        top: 40,
        left: 30,
        duration: 2000
      },
        {
          src: $r('app.media.png_525_539'),
          width: 100,
          height: 200,
          top: 10,
          left: 20,
          duration: 6000
        },
        {
          src: $r('app.media.jpeg_690_669'),
          width: '50vp',
          height: '100vp',
          top: 10,
          left: 20,
          duration: 6000
        }],
      duration: 2000,
      reverse: true,
      fixedSize: false,
      fillMode: FillMode.Both,
      iterations: 1.5,
    },
    {
      imagesValue: [{
        src: $r('app.media.png_525_539'),
        width: 100,
        height: 200,
        top: 10,
        left: 20,
        duration: 6000
      },
        {
          src: $r('app.media.jpeg_690_669'),
          width: '50vp',
          height: '100vp',
          top: 10,
          left: 20,
          duration: 6000
        },
        {
          src: '/common/ic_png2.png',
          width: 300,
          height: 100,
          top: 40,
          left: 30,
          duration: 2000
        }],
      duration: undefined,
      reverse: undefined,
      fixedSize: undefined,
      fillMode: undefined,
      iterations: undefined,
    },
  ]

  private setParam(): void {
    this.model3.imagesValue = this.testCase[this.index].imagesValue
    this.model3.duration = this.testCase[this.index].duration
    this.model3.reverse = this.testCase[this.index].reverse
    this.model3.fixedSize = this.testCase[this.index].fixedSize
    this.model3.fillMode = this.testCase[this.index].fillMode
    this.model3.iterations = this.testCase[this.index].iterations

    this.info =
      'Total: ' + this.testCase.length + ', CaseNumber: ' + this.index + ', fixedSize: ' + this.model3.fixedSize +
        '\nimagesValue: ' + this.model3.imagesValue +
        '\nreverse: ' + this.model3.reverse + ', duration: ' + this.model3.duration + ', fillMode: ' +
        [this.model3.fillMode] + ', iterations: ' + this.model3.iterations
  }

  build() {
    Scroll() {
      Column() {
        Column() {
          Text('ImageAnimator组件 属性及事件测试').fontSize(12).fontColor(0xCCCCCC).width('100%').margin({ top: 10 })
          Text('ImageAnimator组件设置宽高').fontSize(9).fontColor(0xCCCCCC).width('100%').margin(10)
          ImageAnimator()
            .images(this.model3.imagesValue)
            .fixedSize(this.model3.fixedSize)
            .duration(this.model3.duration)
            .state(this.stateVal)
            .reverse(this.model3.reverse)
            .fillMode(this.model3.fillMode)
            .iterations(this.model3.iterations)
            .width(200)
            .height(300)
            .borderWidth(1)
            .borderStyle(BorderStyle.Dashed)
            .onStart(() => {
              console.info('hbx imageanimator onStart')
            })
            .onPause(() => {
              console.info('hbx imageanimator onPause')
            })
            .onRepeat(() => {
              console.info('hbx imageanimator onRepeat')
            })
            .onCancel(() => {
              console.info('hbx imageanimator onCancel')
            })
            .onFinish(() => {
              console.info('hbx imageanimator onFinish')
            })
          Text('ImageAnimator组件不设置宽高').fontSize(9).fontColor(0xCCCCCC).width('100%').margin(10)
          ImageAnimator()
            .images(this.model3.imagesValue)
            .fixedSize(this.model3.fixedSize)
            .duration(this.model3.duration)
            .state(this.stateVal)
            .reverse(this.model3.reverse)
            .fillMode(this.model3.fillMode)
            .iterations(this.model3.iterations)
            .borderWidth(1)
            .borderStyle(BorderStyle.Dashed)
        }.width('100%').height('80%')

        Divider()
        Text('控制播放状态：' + this.stateVal).fontSize(9).fontColor(0xCCCCCC).width('100%')
        Row({ space: 2 }) {
          Button('Initial').fontSize(10).onClick(() => {
            this.stateVal = AnimationStatus.Initial
          })
          Button('Running').fontSize(10).onClick(() => {
            this.stateVal = AnimationStatus.Running
          })
          Button('Paused').fontSize(10).onClick(() => {
            this.stateVal = AnimationStatus.Paused
          })
          Button('Stopped').fontSize(10).onClick(() => {
            this.stateVal = AnimationStatus.Stopped
          })
          Button('undefined').fontSize(10).onClick(() => {
            this.stateVal = undefined
          })

        }

        Text('切换参数，显示参数=' + this.show).fontSize(9).fontColor(0xCCCCCC).width('100%').onClick(() => {
          this.show = !this.show
        })

        Row({ space: 2 }) {
          Text('${this.testCase.length}').key('imageanimator00_cycles')
          Text('Test++')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.setParam()
              this.index++
              if (this.index == this.testCase.length) {
                this.index = 0
              }
            })

          Text('Test--')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.index--
              if (this.index == -1) {
                this.index = this.testCase.length - 1
              }
              this.setParam()
            })
        }

        if (this.show) {
          Text(this.info)
        }
      }
    }
  }

  pageTransition() {
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
    PageTransitionExit({ type: RouteType.None, duration: 0 })
  }
}

class Model3 {
  public state?: AnimationStatus | null = undefined
  public duration?: number | null = undefined
  public reverse?: boolean | null = undefined
  public fixedSize?: boolean | null = undefined
  public fillMode?: FillMode | null = undefined
  public iterations?: number | null = undefined
  public imagesValue?: Array<ImageFrameInfo> | null = undefined

  constructor(state?: AnimationStatus | null, duration?: number | null,
    reverse?: boolean | null, fixedSize?: boolean | null,
    fillMode?: FillMode | null, iterations?: number | null,
    imagesValue?: Array<ImageFrameInfo> | null) {
    this.state = state
    this.duration = duration
    this.reverse = reverse
    this.fixedSize = fixedSize
    this.fillMode = fillMode
    this.iterations = iterations
    this.imagesValue = imagesValue
  }
}