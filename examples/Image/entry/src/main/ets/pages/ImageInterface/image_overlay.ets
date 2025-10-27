/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { ImageAnimatorModifier } from "@ohos.arkui.modifier";
import router from '@ohos.router';

export interface TestAttributes {
  iterations?: number;
  fillMode?: FillMode;
  fixedSize?: boolean;
  reverse?: boolean;
  duration?: number;
  state?: AnimationStatus;
  images?: Array<ImageFrameInfo>;
}

export interface Images {
  width: number,
  height: number,
  src: string | Resource
  top: number
  left: number
}

export const TestData: TestAttributes[] = [
  {
    iterations: 1,
    fillMode: FillMode.None,
    fixedSize: true,
    reverse: true,
    duration: 2000,
    state: AnimationStatus.Initial,
    images: [
      {
        src: $r('app.media.flower')
      },
      {
        src: $r('app.media.ic_jpg')
      },
      {
        src: $r('app.media.jpeg_690_669')
      },
      {
        src: $r('app.media.ic_bmp')
      }
    ]
  },
  {
    iterations: 1,
    fillMode: FillMode.None,
    fixedSize: true,
    reverse: true,
    duration: 3000,
    state: AnimationStatus.Running,
    images: [
      {
        src: $r('app.media.webp')
      },
      {
        src: $r('app.media.ic_svg')
      },
      {
        src: $r('app.media.ic_gif')
      },
      {
        src: $r('app.media.app_icon')
      }
    ]
  },
  {
    images: [{
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
    state: AnimationStatus.Initial,
    duration: 2000,
    reverse: false,
    fixedSize: true,
    fillMode: FillMode.Forwards,
    iterations: 2,
  },
  {
    images: [{
      src: $r('app.media.p3'),
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
    state: AnimationStatus.Running,
    duration: 2000,
    reverse: true,
    fixedSize: false,
    fillMode: FillMode.Backwards,
    iterations: -1,
  },
  {
    images: [{
        src: '/common/png_256_256.png',
        width: '120vp',
        height: '350vp',
        top: '40vp',
        left: '30vp',
        duration: 2000
      },
      {
        src: $r('app.media.200flowers'),
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
    state: AnimationStatus.Paused,
    duration: 2000,
    reverse: true,
    fixedSize: false,
    fillMode: FillMode.None,
    iterations: 3,
  },
  {
    images: [{
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
    state: AnimationStatus.Running,
    duration: 2000,
    reverse: true,
    fixedSize: false,
    fillMode: FillMode.Backwards,
    iterations: 0,
  },
  {
    images: [{
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
      }],
    state: AnimationStatus.Stopped,
    duration: 0,
    reverse: false,
    fixedSize: true,
    fillMode: FillMode.Both,
    iterations: 1,
  },
  {
    images: [{
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
    state: AnimationStatus.Initial,
    duration: 2000,
    reverse: true,
    fixedSize: false,
    fillMode: FillMode.Both,
    iterations: 1.5,
  },
  {
    images: [{
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
    state: undefined,
    duration: undefined,
    reverse: undefined,
    fixedSize: undefined,
    fillMode: undefined,
    iterations: undefined,
  },
]

class CustomModifier extends ImageAnimatorModifier {
  applyNormalAttribute(instance: ImageAnimatorAttribute): void {
    super.applyNormalAttribute?.(instance);
  }

  applyChange(testData: TestAttributes): void {
    this
      .iterations(testData.iterations)
      .fillMode(testData.fillMode)
      .fixedSize(testData.fixedSize)
      .reverse(testData.reverse)
      .duration(testData.duration)
      .state(testData.state)
      .images(testData.images)
  }
}

@Component
struct ModifierComponent {
  @Link customModifier: ImageAnimatorModifier

  build() {
    Column({ space: 10 }) {
      ImageAnimator()
        .width(200)
        .height(150)
        .attributeModifier(this.customModifier as CustomModifier)
    }
  }
}

@Component
struct MyCustomComponent {
  @Prop testData: TestAttributes

  build() {
    Column({ space: 10 }) {
      ImageAnimator()
        .width(200)
        .height(150)
        .iterations(this.testData.iterations)
        .fillMode(this.testData.fillMode)
        .fixedSize(this.testData.fixedSize)
        .reverse(this.testData.reverse)
        .duration(this.testData.duration)
        .state(this.testData.state)
        .images(this.testData.images)
    }
  }
}

@Entry
@Component
struct ImageAnimatorLevel1_2 {
  @State index: number = 0
  @State testData: TestAttributes[] = TestData
  @State customModifier: ImageAnimatorAttribute = new CustomModifier()
    .iterations(this.testData[this.index].iterations)
    .fillMode(this.testData[this.index].fillMode)
    .fixedSize(this.testData[this.index].fixedSize)
    .reverse(this.testData[this.index].reverse)
    .duration(this.testData[this.index].duration)
    .state(this.testData[this.index].state)
    .images(this.testData[this.index].images)

  @Builder
  nativeBuilder() {
    Column() {
      MyCustomComponent({
        testData: this.testData[this.index]
      })
    }
  }

  @Builder
  modifierBuilder() {
    Column() {
      ModifierComponent({ customModifier: this.customModifier })
    }
  }

  build() {
    Column() {
      Row() {
        Text("原生属性")
          .height(20)
          .fontWeight(FontWeight.Bold)

        Blank().width('5%')

        Text("Modifier")
          .height(20)
          .fontWeight(FontWeight.Bold)
      }

      Row() {
        Column() {
          this.nativeBuilder()
        }
        .width('50%')
        .height('50%')
        .key('testArea0')
        .clip(true)


        Column() {
          this.modifierBuilder()
        }
        .width('50%')
        .height('50%')
        .key('testArea1')
        .clip(true)
      }
      .key('testArea')
      .width("100%")
      .height("50%")
      .justifyContent(FlexAlign.Center)

      Column() {
        Text(`${this.index + 1} / ${this.testData?.length}`)

        Row({ space: 2 }) {
          Text(`${this.testData.length}`).key('ImageAnimatorLevel12_cycles1')
          Button('Index++')
            .margin({ left: 10, right: 10 })
            .onClick(() => {
              this.index = (this.index + 1) % (this.testData?.length);
              (this.customModifier as CustomModifier).applyChange(this.testData[this.index]);
            }).key('indexLeft')

          Button('Index--')
            .margin({ left: 10, right: 10 })
            .onClick(() => {
              if (this.index <= 0) {
                this.index = this.testData?.length - 1
              } else {
                this.index--
              }
              (this.customModifier as CustomModifier).applyChange(this.testData[this.index]);
            }).key('indexRight')
        }.padding({ top: 20, bottom: 100 })
      }
      .height("40%")
      .alignItems(HorizontalAlign.Center)
      .position({ x: 0, y: "70%" })
      .width('100%')
    }.width('100%')
    .height("100%")
  }

  pageTransition() {
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
    PageTransitionExit({ type: RouteType.None, duration: 0 })
  }
}
