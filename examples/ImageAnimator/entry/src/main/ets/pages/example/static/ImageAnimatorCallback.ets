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
  Entry,$r,FillMode,ImageInterpolation,ImageFit,ImageRenderMode,ImageRepeat,CopyOptions,ImageInterpolation,
  FlexWrap,ImageFit,ImageRenderMode,ImageRepeat,CopyOptions,
  ForEach,
  FlexAlign,
  ItemAlign,
  Flex,
  Text,
  Column,
  Row,
  Scroll,
  Component,
  Button,
  ClickEvent,
  AnimationStatus,
  ImageAnimator,
  AnimationStatus
} from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'
import { forEachItems20, forEachItems100} from '../Utils/Jarvis'
import {ParallelizeUI, ParallelOption} from '@ohos.arkui.Parallelize'

@Entry
@Component
struct ImageTest {
  @State state: AnimationStatus = AnimationStatus.Initial;
  @State reverse: boolean = false;
  @State iterations: number = 1
  build() {
    Scroll() {
      Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
        for (let i = 0; i < forEachItems20.length ; i++) {
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Text('ImageAnimator')
              ImageAnimator()
                .images([
                  {
                    src: $r('app.media.A')
                  },
                  {
                    src: $r('app.media.background')
                  },
                  {
                    src: $r('app.media.star')
                  },
                  {
                    src: $r('app.media.startIcon')
                  }
                ])
                .duration(2000)
                .state(this.state)
                .reverse(this.reverse)
                .fillMode(FillMode.None)
                .iterations(this.iterations)
                .width(340)
                .height(240)
                .onStart(() => {
                  console.info('Test Start')
                })
                .onPause(() => {
                  console.info('Test Pause')
                })
                .onRepeat(() => {
                  console.info('Test Repeat')
                })
                .onCancel(() => {
                  console.info('Test Cancel')
                })
                .onFinish(() => {
                  console.info('Test Finish')
                  this.state = AnimationStatus.Stopped
                })
              Row() {
                Button('start').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Running
                }).margin(5)
                Button('pause').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Paused
                }).margin(5)
                Button('stop').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Stopped
                }).margin(5)
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Text('ImageAnimator')
              ImageAnimator()
                .images([
                  {
                    src: $r('app.media.A')
                  },
                  {
                    src: $r('app.media.background')
                  },
                  {
                    src: $r('app.media.star')
                  },
                  {
                    src: $r('app.media.startIcon')
                  }
                ])
                .duration(2000)
                .state(this.state)
                .reverse(this.reverse)
                .fillMode(FillMode.None)
                .iterations(this.iterations)
                .width(340)
                .height(240)
                .onStart(() => {
                  console.info('Test Start')
                })
                .onPause(() => {
                  console.info('Test Pause')
                })
                .onRepeat(() => {
                  console.info('Test Repeat')
                })
                .onCancel(() => {
                  console.info('Test Cancel')
                })
                .onFinish(() => {
                  console.info('Test Finish')
                  this.state = AnimationStatus.Stopped
                })
              Row() {
                Button('start').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Running
                }).margin(5)
                Button('pause').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Paused
                }).margin(5)
                Button('stop').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Stopped
                }).margin(5)
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Text('ImageAnimator')
              ImageAnimator()
                .images([
                  {
                    src: $r('app.media.A')
                  },
                  {
                    src: $r('app.media.background')
                  },
                  {
                    src: $r('app.media.star')
                  },
                  {
                    src: $r('app.media.startIcon')
                  }
                ])
                .duration(2000)
                .state(this.state)
                .reverse(this.reverse)
                .fillMode(FillMode.None)
                .iterations(this.iterations)
                .width(340)
                .height(240)
                .onStart(() => {
                  console.info('Test Start')
                })
                .onPause(() => {
                  console.info('Test Pause')
                })
                .onRepeat(() => {
                  console.info('Test Repeat')
                })
                .onCancel(() => {
                  console.info('Test Cancel')
                })
                .onFinish(() => {
                  console.info('Test Finish')
                  this.state = AnimationStatus.Stopped
                })
              Row() {
                Button('start').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Running
                }).margin(5)
                Button('pause').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Paused
                }).margin(5)
                Button('stop').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Stopped
                }).margin(5)
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Text('ImageAnimator')
              ImageAnimator()
                .images([
                  {
                    src: $r('app.media.A')
                  },
                  {
                    src: $r('app.media.background')
                  },
                  {
                    src: $r('app.media.star')
                  },
                  {
                    src: $r('app.media.startIcon')
                  }
                ])
                .duration(2000)
                .state(this.state)
                .reverse(this.reverse)
                .fillMode(FillMode.None)
                .iterations(this.iterations)
                .width(340)
                .height(240)
                .onStart(() => {
                  console.info('Test Start')
                })
                .onPause(() => {
                  console.info('Test Pause')
                })
                .onRepeat(() => {
                  console.info('Test Repeat')
                })
                .onCancel(() => {
                  console.info('Test Cancel')
                })
                .onFinish(() => {
                  console.info('Test Finish')
                  this.state = AnimationStatus.Stopped
                })
              Row() {
                Button('start').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Running
                }).margin(5)
                Button('pause').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Paused
                }).margin(5)
                Button('stop').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Stopped
                }).margin(5)
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Text('ImageAnimator')
              ImageAnimator()
                .images([
                  {
                    src: $r('app.media.A')
                  },
                  {
                    src: $r('app.media.background')
                  },
                  {
                    src: $r('app.media.star')
                  },
                  {
                    src: $r('app.media.startIcon')
                  }
                ])
                .duration(2000)
                .state(this.state)
                .reverse(this.reverse)
                .fillMode(FillMode.None)
                .iterations(this.iterations)
                .width(340)
                .height(240)
                .onStart(() => {
                  console.info('Test Start')
                })
                .onPause(() => {
                  console.info('Test Pause')
                })
                .onRepeat(() => {
                  console.info('Test Repeat')
                })
                .onCancel(() => {
                  console.info('Test Cancel')
                })
                .onFinish(() => {
                  console.info('Test Finish')
                  this.state = AnimationStatus.Stopped
                })
              Row() {
                Button('start').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Running
                }).margin(5)
                Button('pause').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Paused
                }).margin(5)
                Button('stop').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Stopped
                }).margin(5)
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Text('ImageAnimator')
              ImageAnimator()
                .images([
                  {
                    src: $r('app.media.A')
                  },
                  {
                    src: $r('app.media.background')
                  },
                  {
                    src: $r('app.media.star')
                  },
                  {
                    src: $r('app.media.startIcon')
                  }
                ])
                .duration(2000)
                .state(this.state)
                .reverse(this.reverse)
                .fillMode(FillMode.None)
                .iterations(this.iterations)
                .width(340)
                .height(240)
                .onStart(() => {
                  console.info('Test Start')
                })
                .onPause(() => {
                  console.info('Test Pause')
                })
                .onRepeat(() => {
                  console.info('Test Repeat')
                })
                .onCancel(() => {
                  console.info('Test Cancel')
                })
                .onFinish(() => {
                  console.info('Test Finish')
                  this.state = AnimationStatus.Stopped
                })
              Row() {
                Button('start').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Running
                }).margin(5)
                Button('pause').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Paused
                }).margin(5)
                Button('stop').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Stopped
                }).margin(5)
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Text('ImageAnimator')
              ImageAnimator()
                .images([
                  {
                    src: $r('app.media.A')
                  },
                  {
                    src: $r('app.media.background')
                  },
                  {
                    src: $r('app.media.star')
                  },
                  {
                    src: $r('app.media.startIcon')
                  }
                ])
                .duration(2000)
                .state(this.state)
                .reverse(this.reverse)
                .fillMode(FillMode.None)
                .iterations(this.iterations)
                .width(340)
                .height(240)
                .onStart(() => {
                  console.info('Test Start')
                })
                .onPause(() => {
                  console.info('Test Pause')
                })
                .onRepeat(() => {
                  console.info('Test Repeat')
                })
                .onCancel(() => {
                  console.info('Test Cancel')
                })
                .onFinish(() => {
                  console.info('Test Finish')
                  this.state = AnimationStatus.Stopped
                })
              Row() {
                Button('start').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Running
                }).margin(5)
                Button('pause').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Paused
                }).margin(5)
                Button('stop').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Stopped
                }).margin(5)
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Text('ImageAnimator')
              ImageAnimator()
                .images([
                  {
                    src: $r('app.media.A')
                  },
                  {
                    src: $r('app.media.background')
                  },
                  {
                    src: $r('app.media.star')
                  },
                  {
                    src: $r('app.media.startIcon')
                  }
                ])
                .duration(2000)
                .state(this.state)
                .reverse(this.reverse)
                .fillMode(FillMode.None)
                .iterations(this.iterations)
                .width(340)
                .height(240)
                .onStart(() => {
                  console.info('Test Start')
                })
                .onPause(() => {
                  console.info('Test Pause')
                })
                .onRepeat(() => {
                  console.info('Test Repeat')
                })
                .onCancel(() => {
                  console.info('Test Cancel')
                })
                .onFinish(() => {
                  console.info('Test Finish')
                  this.state = AnimationStatus.Stopped
                })
              Row() {
                Button('start').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Running
                }).margin(5)
                Button('pause').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Paused
                }).margin(5)
                Button('stop').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Stopped
                }).margin(5)
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Text('ImageAnimator')
              ImageAnimator()
                .images([
                  {
                    src: $r('app.media.A')
                  },
                  {
                    src: $r('app.media.background')
                  },
                  {
                    src: $r('app.media.star')
                  },
                  {
                    src: $r('app.media.startIcon')
                  }
                ])
                .duration(2000)
                .state(this.state)
                .reverse(this.reverse)
                .fillMode(FillMode.None)
                .iterations(this.iterations)
                .width(340)
                .height(240)
                .onStart(() => {
                  console.info('Test Start')
                })
                .onPause(() => {
                  console.info('Test Pause')
                })
                .onRepeat(() => {
                  console.info('Test Repeat')
                })
                .onCancel(() => {
                  console.info('Test Cancel')
                })
                .onFinish(() => {
                  console.info('Test Finish')
                  this.state = AnimationStatus.Stopped
                })
              Row() {
                Button('start').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Running
                }).margin(5)
                Button('pause').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Paused
                }).margin(5)
                Button('stop').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Stopped
                }).margin(5)
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Text('ImageAnimator')
              ImageAnimator()
                .images([
                  {
                    src: $r('app.media.A')
                  },
                  {
                    src: $r('app.media.background')
                  },
                  {
                    src: $r('app.media.star')
                  },
                  {
                    src: $r('app.media.startIcon')
                  }
                ])
                .duration(2000)
                .state(this.state)
                .reverse(this.reverse)
                .fillMode(FillMode.None)
                .iterations(this.iterations)
                .width(340)
                .height(240)
                .onStart(() => {
                  console.info('Test Start')
                })
                .onPause(() => {
                  console.info('Test Pause')
                })
                .onRepeat(() => {
                  console.info('Test Repeat')
                })
                .onCancel(() => {
                  console.info('Test Cancel')
                })
                .onFinish(() => {
                  console.info('Test Finish')
                  this.state = AnimationStatus.Stopped
                })
              Row() {
                Button('start').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Running
                }).margin(5)
                Button('pause').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Paused
                }).margin(5)
                Button('stop').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Stopped
                }).margin(5)
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Text('ImageAnimator')
              ImageAnimator()
                .images([
                  {
                    src: $r('app.media.A')
                  },
                  {
                    src: $r('app.media.background')
                  },
                  {
                    src: $r('app.media.star')
                  },
                  {
                    src: $r('app.media.startIcon')
                  }
                ])
                .duration(2000)
                .state(this.state)
                .reverse(this.reverse)
                .fillMode(FillMode.None)
                .iterations(this.iterations)
                .width(340)
                .height(240)
                .onStart(() => {
                  console.info('Test Start')
                })
                .onPause(() => {
                  console.info('Test Pause')
                })
                .onRepeat(() => {
                  console.info('Test Repeat')
                })
                .onCancel(() => {
                  console.info('Test Cancel')
                })
                .onFinish(() => {
                  console.info('Test Finish')
                  this.state = AnimationStatus.Stopped
                })
              Row() {
                Button('start').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Running
                }).margin(5)
                Button('pause').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Paused
                }).margin(5)
                Button('stop').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Stopped
                }).margin(5)
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Text('ImageAnimator')
              ImageAnimator()
                .images([
                  {
                    src: $r('app.media.A')
                  },
                  {
                    src: $r('app.media.background')
                  },
                  {
                    src: $r('app.media.star')
                  },
                  {
                    src: $r('app.media.startIcon')
                  }
                ])
                .duration(2000)
                .state(this.state)
                .reverse(this.reverse)
                .fillMode(FillMode.None)
                .iterations(this.iterations)
                .width(340)
                .height(240)
                .onStart(() => {
                  console.info('Test Start')
                })
                .onPause(() => {
                  console.info('Test Pause')
                })
                .onRepeat(() => {
                  console.info('Test Repeat')
                })
                .onCancel(() => {
                  console.info('Test Cancel')
                })
                .onFinish(() => {
                  console.info('Test Finish')
                  this.state = AnimationStatus.Stopped
                })
              Row() {
                Button('start').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Running
                }).margin(5)
                Button('pause').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Paused
                }).margin(5)
                Button('stop').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Stopped
                }).margin(5)
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Text('ImageAnimator')
              ImageAnimator()
                .images([
                  {
                    src: $r('app.media.A')
                  },
                  {
                    src: $r('app.media.background')
                  },
                  {
                    src: $r('app.media.star')
                  },
                  {
                    src: $r('app.media.startIcon')
                  }
                ])
                .duration(2000)
                .state(this.state)
                .reverse(this.reverse)
                .fillMode(FillMode.None)
                .iterations(this.iterations)
                .width(340)
                .height(240)
                .onStart(() => {
                  console.info('Test Start')
                })
                .onPause(() => {
                  console.info('Test Pause')
                })
                .onRepeat(() => {
                  console.info('Test Repeat')
                })
                .onCancel(() => {
                  console.info('Test Cancel')
                })
                .onFinish(() => {
                  console.info('Test Finish')
                  this.state = AnimationStatus.Stopped
                })
              Row() {
                Button('start').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Running
                }).margin(5)
                Button('pause').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Paused
                }).margin(5)
                Button('stop').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Stopped
                }).margin(5)
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Text('ImageAnimator')
              ImageAnimator()
                .images([
                  {
                    src: $r('app.media.A')
                  },
                  {
                    src: $r('app.media.background')
                  },
                  {
                    src: $r('app.media.star')
                  },
                  {
                    src: $r('app.media.startIcon')
                  }
                ])
                .duration(2000)
                .state(this.state)
                .reverse(this.reverse)
                .fillMode(FillMode.None)
                .iterations(this.iterations)
                .width(340)
                .height(240)
                .onStart(() => {
                  console.info('Test Start')
                })
                .onPause(() => {
                  console.info('Test Pause')
                })
                .onRepeat(() => {
                  console.info('Test Repeat')
                })
                .onCancel(() => {
                  console.info('Test Cancel')
                })
                .onFinish(() => {
                  console.info('Test Finish')
                  this.state = AnimationStatus.Stopped
                })
              Row() {
                Button('start').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Running
                }).margin(5)
                Button('pause').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Paused
                }).margin(5)
                Button('stop').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Stopped
                }).margin(5)
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Text('ImageAnimator')
              ImageAnimator()
                .images([
                  {
                    src: $r('app.media.A')
                  },
                  {
                    src: $r('app.media.background')
                  },
                  {
                    src: $r('app.media.star')
                  },
                  {
                    src: $r('app.media.startIcon')
                  }
                ])
                .duration(2000)
                .state(this.state)
                .reverse(this.reverse)
                .fillMode(FillMode.None)
                .iterations(this.iterations)
                .width(340)
                .height(240)
                .onStart(() => {
                  console.info('Test Start')
                })
                .onPause(() => {
                  console.info('Test Pause')
                })
                .onRepeat(() => {
                  console.info('Test Repeat')
                })
                .onCancel(() => {
                  console.info('Test Cancel')
                })
                .onFinish(() => {
                  console.info('Test Finish')
                  this.state = AnimationStatus.Stopped
                })
              Row() {
                Button('start').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Running
                }).margin(5)
                Button('pause').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Paused
                }).margin(5)
                Button('stop').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Stopped
                }).margin(5)
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Text('ImageAnimator')
              ImageAnimator()
                .images([
                  {
                    src: $r('app.media.A')
                  },
                  {
                    src: $r('app.media.background')
                  },
                  {
                    src: $r('app.media.star')
                  },
                  {
                    src: $r('app.media.startIcon')
                  }
                ])
                .duration(2000)
                .state(this.state)
                .reverse(this.reverse)
                .fillMode(FillMode.None)
                .iterations(this.iterations)
                .width(340)
                .height(240)
                .onStart(() => {
                  console.info('Test Start')
                })
                .onPause(() => {
                  console.info('Test Pause')
                })
                .onRepeat(() => {
                  console.info('Test Repeat')
                })
                .onCancel(() => {
                  console.info('Test Cancel')
                })
                .onFinish(() => {
                  console.info('Test Finish')
                  this.state = AnimationStatus.Stopped
                })
              Row() {
                Button('start').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Running
                }).margin(5)
                Button('pause').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Paused
                }).margin(5)
                Button('stop').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Stopped
                }).margin(5)
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Text('ImageAnimator')
              ImageAnimator()
                .images([
                  {
                    src: $r('app.media.A')
                  },
                  {
                    src: $r('app.media.background')
                  },
                  {
                    src: $r('app.media.star')
                  },
                  {
                    src: $r('app.media.startIcon')
                  }
                ])
                .duration(2000)
                .state(this.state)
                .reverse(this.reverse)
                .fillMode(FillMode.None)
                .iterations(this.iterations)
                .width(340)
                .height(240)
                .onStart(() => {
                  console.info('Test Start')
                })
                .onPause(() => {
                  console.info('Test Pause')
                })
                .onRepeat(() => {
                  console.info('Test Repeat')
                })
                .onCancel(() => {
                  console.info('Test Cancel')
                })
                .onFinish(() => {
                  console.info('Test Finish')
                  this.state = AnimationStatus.Stopped
                })
              Row() {
                Button('start').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Running
                }).margin(5)
                Button('pause').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Paused
                }).margin(5)
                Button('stop').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Stopped
                }).margin(5)
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Text('ImageAnimator')
              ImageAnimator()
                .images([
                  {
                    src: $r('app.media.A')
                  },
                  {
                    src: $r('app.media.background')
                  },
                  {
                    src: $r('app.media.star')
                  },
                  {
                    src: $r('app.media.startIcon')
                  }
                ])
                .duration(2000)
                .state(this.state)
                .reverse(this.reverse)
                .fillMode(FillMode.None)
                .iterations(this.iterations)
                .width(340)
                .height(240)
                .onStart(() => {
                  console.info('Test Start')
                })
                .onPause(() => {
                  console.info('Test Pause')
                })
                .onRepeat(() => {
                  console.info('Test Repeat')
                })
                .onCancel(() => {
                  console.info('Test Cancel')
                })
                .onFinish(() => {
                  console.info('Test Finish')
                  this.state = AnimationStatus.Stopped
                })
              Row() {
                Button('start').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Running
                }).margin(5)
                Button('pause').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Paused
                }).margin(5)
                Button('stop').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Stopped
                }).margin(5)
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Text('ImageAnimator')
              ImageAnimator()
                .images([
                  {
                    src: $r('app.media.A')
                  },
                  {
                    src: $r('app.media.background')
                  },
                  {
                    src: $r('app.media.star')
                  },
                  {
                    src: $r('app.media.startIcon')
                  }
                ])
                .duration(2000)
                .state(this.state)
                .reverse(this.reverse)
                .fillMode(FillMode.None)
                .iterations(this.iterations)
                .width(340)
                .height(240)
                .onStart(() => {
                  console.info('Test Start')
                })
                .onPause(() => {
                  console.info('Test Pause')
                })
                .onRepeat(() => {
                  console.info('Test Repeat')
                })
                .onCancel(() => {
                  console.info('Test Cancel')
                })
                .onFinish(() => {
                  console.info('Test Finish')
                  this.state = AnimationStatus.Stopped
                })
              Row() {
                Button('start').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Running
                }).margin(5)
                Button('pause').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Paused
                }).margin(5)
                Button('stop').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Stopped
                }).margin(5)
              }
            })
          }
          ParallelizeUI({}as ParallelOption) {
            ForEach(forEachItems100,(item: Int, index:Double)=>{
              Text('ImageAnimator')
              ImageAnimator()
                .images([
                  {
                    src: $r('app.media.A')
                  },
                  {
                    src: $r('app.media.background')
                  },
                  {
                    src: $r('app.media.star')
                  },
                  {
                    src: $r('app.media.startIcon')
                  }
                ])
                .duration(2000)
                .state(this.state)
                .reverse(this.reverse)
                .fillMode(FillMode.None)
                .iterations(this.iterations)
                .width(340)
                .height(240)
                .onStart(() => {
                  console.info('Test Start')
                })
                .onPause(() => {
                  console.info('Test Pause')
                })
                .onRepeat(() => {
                  console.info('Test Repeat')
                })
                .onCancel(() => {
                  console.info('Test Cancel')
                })
                .onFinish(() => {
                  console.info('Test Finish')
                  this.state = AnimationStatus.Stopped
                })
              Row() {
                Button('start').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Running
                }).margin(5)
                Button('pause').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Paused
                }).margin(5)
                Button('stop').width(100).padding(5).onClick(() => {
                  this.state = AnimationStatus.Stopped
                }).margin(5)
              }
            })
          }

        }
      }
    }
  }
}
