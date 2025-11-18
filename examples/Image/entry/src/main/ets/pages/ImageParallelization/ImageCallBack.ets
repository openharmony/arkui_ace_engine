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
'use static'

import {
  Entry,
  $r,
  ImageInterpolation,
  ImageFit,
  ImageRenderMode,
  ImageRepeat,
  FlexWrap,
  CopyOptions,
  Image,
  ForEach,
  FlexAlign,
  ItemAlign,
  Flex,
  Resource,
  Visibility,
  ColorFilter,
  Text,
  Column,
  Scroll,
  Component,
  Margin,
  Button,
  ClickEvent,
  Color,
  Row,
  Stack,
  Image,
  ImageRotateOrientation,
  DynamicRangeMode,
  Toggle,
  ToggleType,
  AnimationStatus
} from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'
import { forEachItems20, forEachItems100 } from '../Utils/Jarvis'
import { ParallelizeUI, ParallelOption } from '@ohos.arkui.Parallelize'

@Entry
@Component
struct ImageAnimatorTest {
  @State state: AnimationStatus = AnimationStatus.Initial;
  @State reverse: boolean = false;
  @State iterations: number = 1;
  @State isPrivacySensitive: boolean = false;
  @State isAuthenticated: boolean = false;
  @State top: number = 70;
  @State bottom: number = 70;
  @State left: number = 30;
  @State right: number = 90;
  @State aaa: Double[] = [
    0.39, 0.76, 0.18, 0, 0,
    0.34, 0.68, 0.16, 0, 0,
    0.27, 0.53, 0.13, 0, 0,
    0, 0, 0, 1, 0
  ] as Double[]
  @State moveImg: string[] = ['imageScanEffect'];
  @State moveImgVisible: Visibility = Visibility.Visible;
  @State durationTime: number = 1500;
  @State iterationsTimes: number = -1;
  @State private opacityValue: number = 0.5;
  @State imageWidth: number = 450;
  @State visible: Visibility = Visibility.Hidden;
  @State stackBackgroundColor: string = '#E1E4E9';
  @State linePositionX: number = 0 - this.imageWidth;
  @State linePositionY: number = 0;
  @State imgResource: Resource | undefined = undefined;
  private imageOne: Resource = $r('app.media.no2');
  private imageTwo: Resource = $r('app.media.A');
  private imageThree: Resource = $r('app.media.no5');
  @State src: Resource = this.imageOne;
  @State src2: Resource = this.imageThree;

  startupAnimate() {
    this.moveImg.pop();
    this.moveImg.push('imageScanEffect');
    setTimeout(() => {
      this.imgResource = $r('app.media.no5');
    }, 3000);
    this.getUIContext()?.animateTo({
      duration: this.durationTime,
      tempo: 1,
      iterations: this.iterationsTimes,
      delay: 0
    }, () => {
      this.linePositionX = this.imageWidth;
    })
  }

  build() {
    Scroll() {
      Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
        for (let i = 0; i < forEachItems20.length; i++) {
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Column(undefined) {
                Text("image").fontSize(40)
                Text('---------------------------').fontSize(14)
                Text('事件').fontSize(22).margin({ bottom: 15 } as Margin)

                Image($r('app.media.startIcon'))
                  .width(this.imageWidth)
                  .height(200)
                  .objectFit(ImageFit.Contain)
                  .visibility(this.visible)
                  .onComplete(() => {
                    this.visible = Visibility.Visible;
                    this.moveImg.pop();
                    console.info('Test onComplete')
                  })
                  .onError(() => {
                    setTimeout(() => {
                      this.visible = Visibility.Visible;
                      this.moveImg.pop();
                      console.info('Test onError')
                    }, 2600)
                  })
                Image(this.src2)
                  .width(100)
                  .height(100)
                  .onFinish(() => {
                    this.src2 = this.imageOne;
                    console.info('Test onFinish')
                  })
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Column(undefined) {
                Text("image").fontSize(40)
                Text('---------------------------').fontSize(14)
                Text('事件').fontSize(22).margin({ bottom: 15 } as Margin)

                Image($r('app.media.startIcon'))
                  .width(this.imageWidth)
                  .height(200)
                  .objectFit(ImageFit.Contain)
                  .visibility(this.visible)
                  .onComplete(() => {
                    this.visible = Visibility.Visible;
                    this.moveImg.pop();
                    console.info('Test onComplete')
                  })
                  .onError(() => {
                    setTimeout(() => {
                      this.visible = Visibility.Visible;
                      this.moveImg.pop();
                      console.info('Test onError')
                    }, 2600)
                  })
                Image(this.src2)
                  .width(100)
                  .height(100)
                  .onFinish(() => {
                    this.src2 = this.imageOne;
                    console.info('Test onFinish')
                  })
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Column(undefined) {
                Text("image").fontSize(40)
                Text('---------------------------').fontSize(14)
                Text('事件').fontSize(22).margin({ bottom: 15 } as Margin)

                Image($r('app.media.startIcon'))
                  .width(this.imageWidth)
                  .height(200)
                  .objectFit(ImageFit.Contain)
                  .visibility(this.visible)
                  .onComplete(() => {
                    this.visible = Visibility.Visible;
                    this.moveImg.pop();
                    console.info('Test onComplete')
                  })
                  .onError(() => {
                    setTimeout(() => {
                      this.visible = Visibility.Visible;
                      this.moveImg.pop();
                      console.info('Test onError')
                    }, 2600)
                  })
                Image(this.src2)
                  .width(100)
                  .height(100)
                  .onFinish(() => {
                    this.src2 = this.imageOne;
                    console.info('Test onFinish')
                  })
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Column(undefined) {
                Text("image").fontSize(40)
                Text('---------------------------').fontSize(14)
                Text('事件').fontSize(22).margin({ bottom: 15 } as Margin)

                Image($r('app.media.startIcon'))
                  .width(this.imageWidth)
                  .height(200)
                  .objectFit(ImageFit.Contain)
                  .visibility(this.visible)
                  .onComplete(() => {
                    this.visible = Visibility.Visible;
                    this.moveImg.pop();
                    console.info('Test onComplete')
                  })
                  .onError(() => {
                    setTimeout(() => {
                      this.visible = Visibility.Visible;
                      this.moveImg.pop();
                      console.info('Test onError')
                    }, 2600)
                  })
                Image(this.src2)
                  .width(100)
                  .height(100)
                  .onFinish(() => {
                    this.src2 = this.imageOne;
                    console.info('Test onFinish')
                  })
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Column(undefined) {
                Text("image").fontSize(40)
                Text('---------------------------').fontSize(14)
                Text('事件').fontSize(22).margin({ bottom: 15 } as Margin)

                Image($r('app.media.startIcon'))
                  .width(this.imageWidth)
                  .height(200)
                  .objectFit(ImageFit.Contain)
                  .visibility(this.visible)
                  .onComplete(() => {
                    this.visible = Visibility.Visible;
                    this.moveImg.pop();
                    console.info('Test onComplete')
                  })
                  .onError(() => {
                    setTimeout(() => {
                      this.visible = Visibility.Visible;
                      this.moveImg.pop();
                      console.info('Test onError')
                    }, 2600)
                  })
                Image(this.src2)
                  .width(100)
                  .height(100)
                  .onFinish(() => {
                    this.src2 = this.imageOne;
                    console.info('Test onFinish')
                  })
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Column(undefined) {
                Text("image").fontSize(40)
                Text('---------------------------').fontSize(14)
                Text('事件').fontSize(22).margin({ bottom: 15 } as Margin)

                Image($r('app.media.startIcon'))
                  .width(this.imageWidth)
                  .height(200)
                  .objectFit(ImageFit.Contain)
                  .visibility(this.visible)
                  .onComplete(() => {
                    this.visible = Visibility.Visible;
                    this.moveImg.pop();
                    console.info('Test onComplete')
                  })
                  .onError(() => {
                    setTimeout(() => {
                      this.visible = Visibility.Visible;
                      this.moveImg.pop();
                      console.info('Test onError')
                    }, 2600)
                  })
                Image(this.src2)
                  .width(100)
                  .height(100)
                  .onFinish(() => {
                    this.src2 = this.imageOne;
                    console.info('Test onFinish')
                  })
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Column(undefined) {
                Text("image").fontSize(40)
                Text('---------------------------').fontSize(14)
                Text('事件').fontSize(22).margin({ bottom: 15 } as Margin)

                Image($r('app.media.startIcon'))
                  .width(this.imageWidth)
                  .height(200)
                  .objectFit(ImageFit.Contain)
                  .visibility(this.visible)
                  .onComplete(() => {
                    this.visible = Visibility.Visible;
                    this.moveImg.pop();
                    console.info('Test onComplete')
                  })
                  .onError(() => {
                    setTimeout(() => {
                      this.visible = Visibility.Visible;
                      this.moveImg.pop();
                      console.info('Test onError')
                    }, 2600)
                  })
                Image(this.src2)
                  .width(100)
                  .height(100)
                  .onFinish(() => {
                    this.src2 = this.imageOne;
                    console.info('Test onFinish')
                  })
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Column(undefined) {
                Text("image").fontSize(40)
                Text('---------------------------').fontSize(14)
                Text('事件').fontSize(22).margin({ bottom: 15 } as Margin)

                Image($r('app.media.startIcon'))
                  .width(this.imageWidth)
                  .height(200)
                  .objectFit(ImageFit.Contain)
                  .visibility(this.visible)
                  .onComplete(() => {
                    this.visible = Visibility.Visible;
                    this.moveImg.pop();
                    console.info('Test onComplete')
                  })
                  .onError(() => {
                    setTimeout(() => {
                      this.visible = Visibility.Visible;
                      this.moveImg.pop();
                      console.info('Test onError')
                    }, 2600)
                  })
                Image(this.src2)
                  .width(100)
                  .height(100)
                  .onFinish(() => {
                    this.src2 = this.imageOne;
                    console.info('Test onFinish')
                  })
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Column(undefined) {
                Text("image").fontSize(40)
                Text('---------------------------').fontSize(14)
                Text('事件').fontSize(22).margin({ bottom: 15 } as Margin)

                Image($r('app.media.startIcon'))
                  .width(this.imageWidth)
                  .height(200)
                  .objectFit(ImageFit.Contain)
                  .visibility(this.visible)
                  .onComplete(() => {
                    this.visible = Visibility.Visible;
                    this.moveImg.pop();
                    console.info('Test onComplete')
                  })
                  .onError(() => {
                    setTimeout(() => {
                      this.visible = Visibility.Visible;
                      this.moveImg.pop();
                      console.info('Test onError')
                    }, 2600)
                  })
                Image(this.src2)
                  .width(100)
                  .height(100)
                  .onFinish(() => {
                    this.src2 = this.imageOne;
                    console.info('Test onFinish')
                  })
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Column(undefined) {
                Text("image").fontSize(40)
                Text('---------------------------').fontSize(14)
                Text('事件').fontSize(22).margin({ bottom: 15 } as Margin)

                Image($r('app.media.startIcon'))
                  .width(this.imageWidth)
                  .height(200)
                  .objectFit(ImageFit.Contain)
                  .visibility(this.visible)
                  .onComplete(() => {
                    this.visible = Visibility.Visible;
                    this.moveImg.pop();
                    console.info('Test onComplete')
                  })
                  .onError(() => {
                    setTimeout(() => {
                      this.visible = Visibility.Visible;
                      this.moveImg.pop();
                      console.info('Test onError')
                    }, 2600)
                  })
                Image(this.src2)
                  .width(100)
                  .height(100)
                  .onFinish(() => {
                    this.src2 = this.imageOne;
                    console.info('Test onFinish')
                  })
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Column(undefined) {
                Text("image").fontSize(40)
                Text('---------------------------').fontSize(14)
                Text('事件').fontSize(22).margin({ bottom: 15 } as Margin)

                Image($r('app.media.startIcon'))
                  .width(this.imageWidth)
                  .height(200)
                  .objectFit(ImageFit.Contain)
                  .visibility(this.visible)
                  .onComplete(() => {
                    this.visible = Visibility.Visible;
                    this.moveImg.pop();
                    console.info('Test onComplete')
                  })
                  .onError(() => {
                    setTimeout(() => {
                      this.visible = Visibility.Visible;
                      this.moveImg.pop();
                      console.info('Test onError')
                    }, 2600)
                  })
                Image(this.src2)
                  .width(100)
                  .height(100)
                  .onFinish(() => {
                    this.src2 = this.imageOne;
                    console.info('Test onFinish')
                  })
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Column(undefined) {
                Text("image").fontSize(40)
                Text('---------------------------').fontSize(14)
                Text('事件').fontSize(22).margin({ bottom: 15 } as Margin)

                Image($r('app.media.startIcon'))
                  .width(this.imageWidth)
                  .height(200)
                  .objectFit(ImageFit.Contain)
                  .visibility(this.visible)
                  .onComplete(() => {
                    this.visible = Visibility.Visible;
                    this.moveImg.pop();
                    console.info('Test onComplete')
                  })
                  .onError(() => {
                    setTimeout(() => {
                      this.visible = Visibility.Visible;
                      this.moveImg.pop();
                      console.info('Test onError')
                    }, 2600)
                  })
                Image(this.src2)
                  .width(100)
                  .height(100)
                  .onFinish(() => {
                    this.src2 = this.imageOne;
                    console.info('Test onFinish')
                  })
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Column(undefined) {
                Text("image").fontSize(40)
                Text('---------------------------').fontSize(14)
                Text('事件').fontSize(22).margin({ bottom: 15 } as Margin)

                Image($r('app.media.startIcon'))
                  .width(this.imageWidth)
                  .height(200)
                  .objectFit(ImageFit.Contain)
                  .visibility(this.visible)
                  .onComplete(() => {
                    this.visible = Visibility.Visible;
                    this.moveImg.pop();
                    console.info('Test onComplete')
                  })
                  .onError(() => {
                    setTimeout(() => {
                      this.visible = Visibility.Visible;
                      this.moveImg.pop();
                      console.info('Test onError')
                    }, 2600)
                  })
                Image(this.src2)
                  .width(100)
                  .height(100)
                  .onFinish(() => {
                    this.src2 = this.imageOne;
                    console.info('Test onFinish')
                  })
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Column(undefined) {
                Text("image").fontSize(40)
                Text('---------------------------').fontSize(14)
                Text('事件').fontSize(22).margin({ bottom: 15 } as Margin)

                Image($r('app.media.startIcon'))
                  .width(this.imageWidth)
                  .height(200)
                  .objectFit(ImageFit.Contain)
                  .visibility(this.visible)
                  .onComplete(() => {
                    this.visible = Visibility.Visible;
                    this.moveImg.pop();
                    console.info('Test onComplete')
                  })
                  .onError(() => {
                    setTimeout(() => {
                      this.visible = Visibility.Visible;
                      this.moveImg.pop();
                      console.info('Test onError')
                    }, 2600)
                  })
                Image(this.src2)
                  .width(100)
                  .height(100)
                  .onFinish(() => {
                    this.src2 = this.imageOne;
                    console.info('Test onFinish')
                  })
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Column(undefined) {
                Text("image").fontSize(40)
                Text('---------------------------').fontSize(14)
                Text('事件').fontSize(22).margin({ bottom: 15 } as Margin)

                Image($r('app.media.startIcon'))
                  .width(this.imageWidth)
                  .height(200)
                  .objectFit(ImageFit.Contain)
                  .visibility(this.visible)
                  .onComplete(() => {
                    this.visible = Visibility.Visible;
                    this.moveImg.pop();
                    console.info('Test onComplete')
                  })
                  .onError(() => {
                    setTimeout(() => {
                      this.visible = Visibility.Visible;
                      this.moveImg.pop();
                      console.info('Test onError')
                    }, 2600)
                  })
                Image(this.src2)
                  .width(100)
                  .height(100)
                  .onFinish(() => {
                    this.src2 = this.imageOne;
                    console.info('Test onFinish')
                  })
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Column(undefined) {
                Text("image").fontSize(40)
                Text('---------------------------').fontSize(14)
                Text('事件').fontSize(22).margin({ bottom: 15 } as Margin)

                Image($r('app.media.startIcon'))
                  .width(this.imageWidth)
                  .height(200)
                  .objectFit(ImageFit.Contain)
                  .visibility(this.visible)
                  .onComplete(() => {
                    this.visible = Visibility.Visible;
                    this.moveImg.pop();
                    console.info('Test onComplete')
                  })
                  .onError(() => {
                    setTimeout(() => {
                      this.visible = Visibility.Visible;
                      this.moveImg.pop();
                      console.info('Test onError')
                    }, 2600)
                  })
                Image(this.src2)
                  .width(100)
                  .height(100)
                  .onFinish(() => {
                    this.src2 = this.imageOne;
                    console.info('Test onFinish')
                  })
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Column(undefined) {
                Text("image").fontSize(40)
                Text('---------------------------').fontSize(14)
                Text('事件').fontSize(22).margin({ bottom: 15 } as Margin)

                Image($r('app.media.startIcon'))
                  .width(this.imageWidth)
                  .height(200)
                  .objectFit(ImageFit.Contain)
                  .visibility(this.visible)
                  .onComplete(() => {
                    this.visible = Visibility.Visible;
                    this.moveImg.pop();
                    console.info('Test onComplete')
                  })
                  .onError(() => {
                    setTimeout(() => {
                      this.visible = Visibility.Visible;
                      this.moveImg.pop();
                      console.info('Test onError')
                    }, 2600)
                  })
                Image(this.src2)
                  .width(100)
                  .height(100)
                  .onFinish(() => {
                    this.src2 = this.imageOne;
                    console.info('Test onFinish')
                  })
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Column(undefined) {
                Text("image").fontSize(40)
                Text('---------------------------').fontSize(14)
                Text('事件').fontSize(22).margin({ bottom: 15 } as Margin)

                Image($r('app.media.startIcon'))
                  .width(this.imageWidth)
                  .height(200)
                  .objectFit(ImageFit.Contain)
                  .visibility(this.visible)
                  .onComplete(() => {
                    this.visible = Visibility.Visible;
                    this.moveImg.pop();
                    console.info('Test onComplete')
                  })
                  .onError(() => {
                    setTimeout(() => {
                      this.visible = Visibility.Visible;
                      this.moveImg.pop();
                      console.info('Test onError')
                    }, 2600)
                  })
                Image(this.src2)
                  .width(100)
                  .height(100)
                  .onFinish(() => {
                    this.src2 = this.imageOne;
                    console.info('Test onFinish')
                  })
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Column(undefined) {
                Text("image").fontSize(40)
                Text('---------------------------').fontSize(14)
                Text('事件').fontSize(22).margin({ bottom: 15 } as Margin)

                Image($r('app.media.startIcon'))
                  .width(this.imageWidth)
                  .height(200)
                  .objectFit(ImageFit.Contain)
                  .visibility(this.visible)
                  .onComplete(() => {
                    this.visible = Visibility.Visible;
                    this.moveImg.pop();
                    console.info('Test onComplete')
                  })
                  .onError(() => {
                    setTimeout(() => {
                      this.visible = Visibility.Visible;
                      this.moveImg.pop();
                      console.info('Test onError')
                    }, 2600)
                  })
                Image(this.src2)
                  .width(100)
                  .height(100)
                  .onFinish(() => {
                    this.src2 = this.imageOne;
                    console.info('Test onFinish')
                  })
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Column(undefined) {
                Text("image").fontSize(40)
                Text('---------------------------').fontSize(14)
                Text('事件').fontSize(22).margin({ bottom: 15 } as Margin)

                Image($r('app.media.startIcon'))
                  .width(this.imageWidth)
                  .height(200)
                  .objectFit(ImageFit.Contain)
                  .visibility(this.visible)
                  .onComplete(() => {
                    this.visible = Visibility.Visible;
                    this.moveImg.pop();
                    console.info('Test onComplete')
                  })
                  .onError(() => {
                    setTimeout(() => {
                      this.visible = Visibility.Visible;
                      this.moveImg.pop();
                      console.info('Test onError')
                    }, 2600)
                  })
                Image(this.src2)
                  .width(100)
                  .height(100)
                  .onFinish(() => {
                    this.src2 = this.imageOne;
                    console.info('Test onFinish')
                  })
              }
            })
          }


        }
      }
    }
  }
}
