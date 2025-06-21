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

// 该 Demo 通过定义多组测试数据，全面验证 ImageAnimator 组件在原生属性与 Modifier 两种设置方式下，面对迭代次数、填充模式、
// 尺寸固定、反向播放、持续时间、动画状态及图片资源等多维度属性组合时的行为一致性，支持动态切换测试用例以覆盖正常、边界及异常场景。

//引入需要的Modifier
import { ImageAnimatorModifier } from '@ohos.arkui.modifier';
import router from '@ohos.router';


//定义要测试的属性以及类型
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

//初始化测试数据
export const testData: TestAttributes[] = [
//1
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
        src: $r('app.media.mix_png')
      },
      {
        src: $r('app.media.ic_bmp')
      }
    ]
  },
  //2
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
  //3
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
  // 4 验证images里面全部设置了duration是否走images自身设置的值；验证fixedSize为false
  // images中图片大小是否走自己设置的宽高坐标值；验证reverse设置为true播放效果；验证iterations为负数时效果
  {
    images: [{
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
    state: AnimationStatus.Running,
    duration: 2000, //不生效
    reverse: true,
    fixedSize: false,
    fillMode: FillMode.Backwards,
    iterations: -1,
  },
  //5 预期只播放5张图？
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
      }, //duration走默认值0，不播放
      {
        src: '/common/ic_png2.png',
        width: 200,
        height: 300,
        top: 40,
        left: 30,
        duration: 20
      },
      // duration值很小，播放吗？
      {
        src: '/common/jpg_240_160.jpg',
        width: -300,
        height: -100,
        top: 40,
        left: 30,
        duration: 2000
      }, //width、height为负数，走默认值0，不显示？
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
      }, //height为0，不显示？
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
      }, //width为0，不显示？
      {
        src: '/common/yellowperson.jpg',
        width: '100%',
        height: '20%',
        top: 40,
        left: 30,
        duration: 6000
      }],
    state: AnimationStatus.Paused,
    duration: 2000, //不生效
    reverse: true,
    fixedSize: false,
    fillMode: FillMode.None,
    iterations: 3,
  },
  // 6:验证iterations为0时效果
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
    duration: 2000, //不生效
    reverse: true,
    fixedSize: false,
    fillMode: FillMode.Backwards,
    iterations: 0,
  },
  //7:验证duration为0时效果
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
    duration: 0, //不播放
    reverse: false,
    fixedSize: true,
    fillMode: FillMode.Both,
    iterations: 1,
  },
  //8:验证fillMode为Both时效果
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
    duration: 2000, //不生效
    reverse: true,
    fixedSize: false,
    fillMode: FillMode.Both,
    iterations: 1.5,
  },
  //9:验证动态切换undefined
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
    duration: undefined, //预期走默认值1000
    reverse: undefined, //预期不反转播放
    fixedSize: undefined, //预期图片按照组件大小显示
    fillMode: undefined, //预期效果为forwards
    iterations: undefined, //预期只播放1次
  },
]


//修改基类
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
    //需要替换成自己要测试的组件并设置属性
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
struct ImageAnimatorExample011 {
  @State index: number = 0
  @State testData: TestAttributes[] = testData
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
      //这里是原生属性UI
      MyCustomComponent({
        testData: this.testData[this.index]
      })
    }
  }

  @Builder
  modifierBuilder() {
    Column() {
      //这里是Modifier属性UI
      ModifierComponent({ customModifier: this.customModifier })
    }
  }

  build() {
    Column() {
      Row() {
        Text('原生属性')
          .height(20)
          .fontWeight(FontWeight.Bold)

        Blank().width('5%')

        Text('Modifier')
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
      .width('100%')
      .height('50%')
      .justifyContent(FlexAlign.Center)

      //更新数据按钮
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
      .height('40%')
      .alignItems(HorizontalAlign.Center)
      .position({ x: 0, y: '70%' })
      .width('100%')
    }.width('100%')
    .height('100%')
  }

  pageTransition() {
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
    PageTransitionExit({ type: RouteType.None, duration: 0 })
  }
}